/*
 * Copyright Codito Technologies (www.codito.com)
 *
 *  board/aa3/arc_emac.c
 *
 *  Copyright (C) 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 * 
 * Authors : Sandeep Patil (sandeep.patil@codito.com)
 * 			 Pradeep Sawlani (pradeep.sawlani@codito.com)
 */



//#include <cmd_confdefs.h>	/* Command configs	*/
#include <asm/u-boot.h>		/* Board data structure	*/
#include <asm/arc_emac.h>	/* MDIO macros and ARC_EMAC register macros	*/
#include <config.h>		/* ARC700 clock freq.	*/
#include <asm/errno.h>
#include <malloc.h>
#include <common.h>
#include <net.h>
#include <linux/types.h>
/* rx buffer descriptor. We align descriptors to 32 so info and 
 * data lie on the same cache line. This also satisfies the 8 byte 
 * alignment required by the VMAC */
volatile struct aa3_buffer_desc rxbd[RX_BDT_LEN] __attribute__((aligned(32)));

/* tx buffer descriptor */
volatile struct aa3_buffer_desc txbd[RX_BDT_LEN] __attribute__((aligned(32)));

/* transmit buffer counter */
static int txbd_cntr;

char default_addr[10] = { 0x00 ,0x01 ,0x02 ,0x03 ,0x04 ,0x05  };
int arc_eth_rx (struct eth_device * net_current)
{
	unsigned int i,len;
    volatile unsigned char *recv_data;
	volatile unsigned int *stat_reg,*reg_base_addr = VMAC_REG_BASEADDR;
	stat_reg = reg_base_addr + STAT_OFFSET;
    volatile unsigned char *p;
    unsigned int z;

    if (*stat_reg & TXINT_MASK)
    {
        *stat_reg = TXINT_MASK;
    }

//do_ping(1,2,3,4);

    if (!(*stat_reg & RXINT_MASK))
        return;
	*stat_reg = RXINT_MASK;
    flush_cache(1,2);
	
	for (i=0 ; i < RX_BDT_LEN;i++) {
		if( (rxbd[i].info & OWN_MASK) == 0) {
			if( (rxbd[i].info & FRST_MASK) && (rxbd[i].info & LAST_MASK) ) {
				recv_data = (unsigned int *)rxbd[i].data;
				len = rxbd[i].info & LEN_MASK;

				if( !(rxbd[i].data = malloc(ETH_MTU + VMAC_BUFFER_PAD))) {
					printf("Out of memory,dropping packet\n");
					rxbd[i].info = OWN_MASK | (ETH_MTU + VMAC_BUFFER_PAD);
				}
				else {
					rxbd[i].info = OWN_MASK | (ETH_MTU + VMAC_BUFFER_PAD); 
                    flush_cache(1,2);
					NetReceive((uchar *)recv_data,len);
					free(recv_data);
				}					
				
			}
			else {
				printf("Rx chained, Packet bigger than device MTU\n");
				rxbd[i].info = OWN_MASK | (ETH_MTU + VMAC_BUFFER_PAD);
			}
				
		}	
	}
    flush_cache(1,2);

	return (0);
}
int arc_eth_send (struct eth_device *net_current, volatile void *packet, int length)
{

	volatile unsigned int *reg_base_addr = VMAC_REG_BASEADDR;
	volatile unsigned int *stat_reg = reg_base_addr + STAT_OFFSET;
    volatile unsigned int *enable_reg = reg_base_addr + ENABLE_OFFSET;
    volatile unsigned int *control_reg = reg_base_addr + CONTROL_OFFSET;
    volatile unsigned int *tx_ring = reg_base_addr + TXRINGPTR_OFFSET;
    unsigned int z;
    unsigned char *p;

#if 0
printf("Eth_send\n");
printf("ID REG : %x\n", *reg_base_addr);
printf("Enable : %x\n", *enable_reg);
printf("Control: %x\n", *control_reg);
printf("TX Ring: %x\n", *tx_ring);
printf("Packet : %x\n", packet);
#endif 

	if (length > ETH_MTU) {
	     printf("eth_send:packet length greater than MTU\n");  		
	     return -EMSGSIZE;
	}
	if ( length < 64 )
		length = 64;

	if( (txbd[txbd_cntr].info & OWN_MASK) == 0) {
			txbd[txbd_cntr].data = packet;
			txbd[txbd_cntr].info = OWN_MASK | length | FRST_MASK | LAST_MASK;
            flush_cache(1,2);
//			arc_write_uncached_32(txbd[txbd_cntr].data, packet);
//			arc_write_uncached_32(txbd[txbd_cntr].info, OWN_MASK | length | FRST_MASK | LAST_MASK);
			*stat_reg = TXPL_MASK;		

#if 0
            p = (char *) packet;
            printf("Packet length %u\n", length);
            printf("Packet : ");
            for(z=0;z!=length;z++)
                printf("%02x:",p[z]);
            printf("\n");
#endif 
			
	} else {
		printf("Out of Tx Buffers\n");
		return -ENOMEM;
	}

	
	/* Poll for TXINT */
//	while ( !(*(stat_reg) & TXINT_MASK))

	
	*stat_reg = TXINT_MASK;
	txbd[txbd_cntr].data = 0;
	txbd[txbd_cntr].info = 0;
	txbd_cntr = (txbd_cntr + 1)%TX_BDT_LEN;	
	return (0);
}
void arc_eth_halt(struct eth_device * net_current)
{

}

void eth_stop(void)
{
	volatile unsigned int *reg_base_addr = VMAC_REG_BASEADDR;
	volatile unsigned int *control_reg = reg_base_addr + CONTROL_OFFSET;
    volatile unsigned int *macl = reg_base_addr + ADDRL_OFFSET;
    volatile unsigned int *mach = reg_base_addr + ADDRH_OFFSET;
    volatile unsigned int *reg;
    volatile unsigned int *stat_reg;
    unsigned int temp;

    reg = reg_base_addr + ENABLE_OFFSET;
    *reg = 0;

    reg = reg_base_addr + STAT_OFFSET;
    *reg = 0xffffffff;

	txbd_cntr = 0;
	(*control_reg) = (*control_reg) & (~EN_MASK)  ;  	 	/* VMAC disabled  */
     *control_reg = 0;
    *macl = 0;
    *mach = 0;
    stat_reg = reg_base_addr + STAT_OFFSET;
    *stat_reg = 0;
 
    printf("EMAC : RESET\n");
    reg = reg_base_addr + MDIO_DATA_OFFSET;
    stat_reg = reg_base_addr + STAT_OFFSET;

	__mdio_write(stat_reg, reg, PHY_ID, LXT970A_CTRL_REG, LXT970A_CTRL_RESET);
    
	do {
		__mdio_read (stat_reg, reg, PHY_ID, LXT970A_CTRL_REG, temp);
	} while (temp & LXT970A_CTRL_RESET);
 
    printf("LXT970A : RESET\n");
}

void aa3_emac_set_address(void *ptr)
{
	char *mac_addr = (char *)ptr ;
        volatile unsigned int *reg;
	volatile unsigned int *reg_base_addr = VMAC_REG_BASEADDR;
	
	reg = reg_base_addr + ADDRL_OFFSET;
	*reg = *((unsigned int *)mac_addr);
	reg = reg_base_addr + ADDRH_OFFSET;
	(*reg) = (*(unsigned int *) (mac_addr+4)) & 0x0000ffff;
}



int arc_eth_init(bd_t *bd)
{	
	volatile unsigned int *reg;
	volatile unsigned int *stat_reg;
	volatile unsigned int *reg_base_addr;
	int i;
	unsigned int temp,duplex ;
	static int initialised = 0 ;
    struct eth_device *dev;


	reg_base_addr	= (unsigned int *) (VMAC_REG_BASEADDR);
	if(initialised) {
	  reg = reg_base_addr + CONTROL_OFFSET;
	  goto out;	
	}
	reg = reg_base_addr + ENABLE_OFFSET;	
	(*reg) = 0;	/* Disable all interrupts as we are not handling */

	reg =  reg_base_addr + MDIO_DATA_OFFSET;
	stat_reg = reg_base_addr + STAT_OFFSET;

	/* Reset the PHY */
	__mdio_write(stat_reg, reg, PHY_ID, LXT970A_CTRL_REG, LXT970A_CTRL_RESET);

	/* Wait till the PHY has finished resetting */
	do {
		__mdio_read (stat_reg, reg, PHY_ID, LXT970A_CTRL_REG, temp);
	} while (temp & LXT970A_CTRL_RESET);


 
	/* Advertize capabilities */
	temp = LXT970A_AUTONEG_ADV_10BTX_FULL | 
			LXT970A_AUTONEG_ADV_10BT | AUTONEG_ADV_IEEE_8023;
	
	/* If the system clock is greater than 25Mhz then advertize 100 */
#if (CONFIG_ARC_CLK > 25000000)
	temp = LXT970A_AUTONEG_ADV_100BTX_FULL | LXT970A_AUTONEG_ADV_100BTX;
#endif
	__mdio_write(stat_reg, reg, PHY_ID, LXT970A_AUTONEG_ADV_REG, temp);

	/* Start Auto-Negotioation */
	__mdio_write(stat_reg, reg, PHY_ID, LXT970A_CTRL_REG,
			 (LXT970A_CTRL_AUTONEG | LXT970A_CTRL_RESTART_AUTO));
	
	/* Wait for Auto Negotiation to complete */
	do {
		__mdio_read(stat_reg, reg, PHY_ID, LXT970A_STATUS2_REG, temp);
	} while (!(temp & LXT970A_STATUS2_COMPLETE));

// Check polarity 

    if (temp & LXT970A_STATUS2_POLARITY)
    {
        printf("EMAC : LXT Polarity bit set\n");
        temp = ~temp; // invert it
    }

	/* Check if full duplex is supported and set the vmac accordingly */
	if (temp & LXT970A_STATUS2_FULL) 
    {
        printf("EMAC : Full duplex\n");
		duplex = ENFL_MASK;
    }
	else
    {
        printf("EMAC : Half duplex\n");
		duplex = 0;
    }

	 
								 

								 
	/* Allocate and set buffers for rx BD's */
	for ( i=0 ; i<RX_BDT_LEN ; i++) {
		rxbd[i].data = malloc(ETH_MTU +VMAC_BUFFER_PAD);
		rxbd[i].info = OWN_MASK | (ETH_MTU + VMAC_BUFFER_PAD);
	}
	
	/* All TX BD's owned by CPU */
	for ( i=0 ; i<TX_BDT_LEN ; i++) {
		txbd[i].data = 0;
		txbd[i].info = 0;
	}
	
	/* Set EMAC hardware address */
	aa3_emac_set_address((void *)&default_addr);	

	/* Initialize logical address filter */
	reg = reg_base_addr + LAFL_OFFSET;
	(*reg ) = 0x0;
	reg = reg_base_addr + LAFH_OFFSET;
	(*reg ) = 0x0;

	/* Set rx BD ring pointer */
	reg = reg_base_addr + RXRINGPTR_OFFSET;
	(*reg) = (unsigned int )rxbd;

	/* Set tx BD ring pointer */
	reg = reg_base_addr + TXRINGPTR_OFFSET;
	(*reg) = (unsigned int )txbd;

	/* Set Poll rate so that it polls every 1 ms*/
	reg = reg_base_addr + POLLRATE_OFFSET;
	(*reg) = (CONFIG_ARC_CLK/1000000); 	


	/* Set CONTROL */
	reg = reg_base_addr + CONTROL_OFFSET;
	(*reg) = (RX_BDT_LEN << 24) |	/* RX buffer desc table len */
		 (TX_BDT_LEN << 16) |	/* TX buffer des tabel len */
		 TXRN_MASK |		/* TX enable */
		 RXRN_MASK |		/* RX enable */
        PROM_MASK | 
		 duplex;		/* Full Duplex enable */

    dev = (struct eth_device *) malloc(sizeof(*dev)); 
    sprintf(dev->name,"ARC EMAC");
    dev->init = arc_eth_init;
    dev->halt = arc_eth_halt;
    dev->send = arc_eth_send;
    dev->recv = arc_eth_rx;
    eth_register(dev);
 out:
	(*reg) |= EN_MASK;  	 	/* VMAC enable */
	initialised = 1;
	return (0);
}

