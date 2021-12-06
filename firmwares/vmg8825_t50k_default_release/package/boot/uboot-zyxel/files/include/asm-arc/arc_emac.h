/* 
 * Copyright Codito Technologies (www.codito.com)  
 *
 *  include/asm-arc/arc_emac.h
 *
 *  Copyright (C) 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 * 
 * Authors : Sandeep Patil (sandeep.patil@codito.com)
 * 			 Pradeep Sawlani(pradeep.sawlani@codito.com)
 */



#ifndef __ARC_EMAC_H
#define __ARC_EMAC_H
#include <config.h>
/* Mtu */
		
#define ETH_MTU		1500
/* Ethernet frame length	*/
#define ETH_FRAME_LEN	1514
#define ETH_HLEN	14


/* Timeout time for tranmission */
#define TX_TIMEOUT (400*HZ/1000)

/* Buffer descriptors */
#define TX_BDT_LEN	10	/* Number of recieve BD's */
#define RX_BDT_LEN	10	/* Number of transmit BD's */


/* Size of RX buffers, min = 0 (pointless) max = 2048 (MAX_RX_BUFFER_LEN)
 * MAC reference manual recommends a value slightly greater than the 
 * maximum size of the packet expected other wise it will chain
 * a zero size buffer desc if a packet of exactly RX_BUFFER_LEN comes.
 * VMAC will chain buffers if a packet bigger than this arrives.
 */
#define RX_BUFFER_LEN	(ETH_FRAME_LEN + 4)

#define MAX_RX_BUFFER_LEN	0x800	/* 2^11 = 2048 = 0x800 */
#define MAX_TX_BUFFER_LEN	0x800	/* 2^11 = 2048 = 0x800 */

	
/* 14 bytes of ethernet header, 8 bytes pad to prevent buffer chaining 
 * of maximum sized ethernet packets (1514 bytes)
 */
#define	VMAC_BUFFER_PAD ETH_HLEN + 8	

/* VMAC register definitions, offsets in the ref manual are in bytes */


#define ID_OFFSET 0x0/0x4
#define MDIO_DATA_OFFSET 0x34/0x4
#define ADDRL_OFFSET 0x24/0x4
#define ADDRH_OFFSET 0x28/0x4
#define RXRINGPTR_OFFSET 0x20/0x4
#define TXRINGPTR_OFFSET 0x1c/0x4
#define POLLRATE_OFFSET	0x10/0x4	
#define ENABLE_OFFSET	0x08/0x4	
#define STAT_OFFSET	0x04/0x4	
#define CONTROL_OFFSET	0x0c/0x4	
#define LAFL_OFFSET	0x2c/0x4
#define LAFH_OFFSET	0x30/0x4



/* STATUS and ENABLE Register bit masks */
#define TXINT_MASK	(1<<0)	/* Transmit interrupt */
#define RXINT_MASK	(1<<1)	/* Recieve interrupt */
#define ERR_MASK	(1<<2)	/* Error interrupt */
#define TXCH_MASK	(1<<3)	/* Transmit chaining error interrupt */
#define MSER_MASK	(1<<4)	/* Missed packet counter error */
#define RXCR_MASK	(1<<8)	/* RXCRCERR counter rolled over	 */
#define RXFR_MASK	(1<<9)	/* RXFRAMEERR counter rolled over */
#define RXFL_MASK	(1<<10)	/* RXOFLOWERR counter rolled over */
#define MDIO_MASK	(1<<12)	/* MDIO complete */
#define TXPL_MASK	(1<<31)	/* TXPOLL */

/* CONTROL Register bit masks */
#define EN_MASK		(1<<0)	/* VMAC enable */
#define TXRN_MASK	(1<<3)	/* TX enable */
#define RXRN_MASK	(1<<4)	/* RX enable */
#define DSBC_MASK	(1<<8)	/* Disable recieve broadcast */
#define ENFL_MASK	(1<<10)	/* Enable Full Duplex */
#define PROM_MASK	(1<<11)	/* Promiscuous mode */

/* Buffer descriptor INFO bit masks */
#define OWN_MASK	(1<<31)	/* 0-CPU owns buffer, 1-VMAC owns buffer */ 
#define FRST_MASK	(1<<16)	/* First buffer in chain */
#define LAST_MASK	(1<<17)	/* Last buffer in chain */
#define LEN_MASK	0x000007FF	/* last 11 bits */

/* ARCangel board PHY Identifier */
#define PHY_ID	0x3

/* LXT970 register definitions */
#define LXT970A_CTRL_REG               0x00
#define LXT970A_STATUS_REG             0x01
#define LXT970A_AUTONEG_ADV_REG        0x04
#define LXT970A_AUTONEG_LINK_REG       0x05
#define LXT970A_MIRROR_REG             0x10
#define LXT970A_STATUS2_REG            0x11

/* LXT970A control register bit definitions */
#define LXT970A_CTRL_RESET         0x8000
#define LXT970A_CTRL_LOOPBACK      0x4000
#define LXT970A_CTRL_SPEED         0x2000
#define LXT970A_CTRL_AUTONEG       0x1000
#define LXT970A_CTRL_DUPLEX        0x0100
#define LXT970A_CTRL_RESTART_AUTO  0x0200
#define LXT970A_CTRL_COLL          0x0080
#define LXT970A_CTRL_DUPLEX_MODE   0x0100

/* Auto-negatiation advertisement register bit definitions */
#define LXT970A_AUTONEG_ADV_100BTX_FULL     0x100       
#define LXT970A_AUTONEG_ADV_100BTX          0x80      
#define LXT970A_AUTONEG_ADV_10BTX_FULL      0x40  
#define LXT970A_AUTONEG_ADV_10BT            0x20       
#define AUTONEG_ADV_IEEE_8023               0x1

/* Auto-negatiation Link register bit definitions */
#define LXT970A_AUTONEG_LINK_100BTX_FULL     0x100       
#define LXT970A_AUTONEG_LINK_100BTX          0x80      
#define LXT970A_AUTONEG_LINK_10BTX_FULL      0x40  

/* Status register bit definitions */
#define LXT970A_STATUS_COMPLETE     0x20          
#define LXT970A_STATUS_AUTONEG_ABLE 0x04
#define LXT970A_STATUS2_COMPLETE    0x80
          
/* Status2 register bit definitions */
#define LXT970A_STATUS2_POLARITY   0x20
#define LXT970A_STATUS2_FULL       0x200          
#define LXT970A_STATUS2_LINK_UP    0x400          
#define LXT970A_STATUS2_100        0x4000          


//#define ARCTANGENT_EMAC_SETUP 
//#define ARCTANGENT_EMAC_DEBUG 


#define __mdio_write(stat_reg,mdio_data_reg, phy_id, phy_reg, val) do { \
		*(mdio_data_reg) = (0x50020000 | phy_id << 23 | \
					phy_reg << 18 | (val & 0xffff)) ; \
		while (!(*(stat_reg) & MDIO_MASK)); \
		*stat_reg = MDIO_MASK;\
		}while(0)

#define __mdio_read(stat_reg, mdio_data_reg, phy_id, phy_reg, val)	do { \
		*(mdio_data_reg) = (0x60020000 | phy_id << 23 | phy_reg << 18 );\
		while (! ((*stat_reg) & MDIO_MASK) );\
		*stat_reg = MDIO_MASK; \
		val = *(mdio_data_reg) & 0xffff; \
		}while(0)


#define arc_read_uncached_32(ptr)                   \
({                                  \
    unsigned int __ret;                     \
    __asm__ __volatile__ ("ld.di %0, [%1]":"=r"(__ret):"r"(ptr));   \
    __ret;                              \
})

#define arc_write_uncached_32(ptr, data)                \
({                                  \
    __asm__ __volatile__ ("st.di %0, [%1]"::"r"(data), "r"(ptr));   \
})


struct aa3_buffer_desc {
	unsigned int info;
	void *data;
};
#endif /* __ARC_EMAC_H */
