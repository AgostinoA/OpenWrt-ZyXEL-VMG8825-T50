/*
 * (C) Copyright 2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <command.h>
#include <asm/addrspace.h>
#include <asm/arch/rt_mmap.h>
//#include "LzmaDecode.h"

//#define MAX_SDRAM_SIZE	(64*1024*1024)
//#define MIN_SDRAM_SIZE	(8*1024*1024)
#define MAX_SDRAM_SIZE	(256*1024*1024)
#define MIN_SDRAM_SIZE	(8*1024*1024)

#ifdef SDRAM_CFG_USE_16BIT
#define MIN_RT2880_SDRAM_SIZE	(16*1024*1024)
#else
#define MIN_RT2880_SDRAM_SIZE	(32*1024*1024)
#endif

phys_size_t initdram(int board_type)
{
	ulong size, max_size       = MAX_SDRAM_SIZE;
	ulong our_address;
  
	asm volatile ("move %0, $25" : "=r" (our_address) :);

	/* Can't probe for RAM size unless we are running from Flash.
	 */
#if 0	 
	#if defined(CFG_RUN_CODE_IN_RAM)

	printf("\n In RAM run \n"); 
    return MIN_SDRAM_SIZE;
	#else

	printf("\n In FLASH run \n"); 
    return MIN_RT2880_SDRAM_SIZE;
	#endif
#endif 
    
#if defined (RT2880_FPGA_BOARD) || defined (RT2880_ASIC_BOARD)
	if (PHYSADDR(our_address) < PHYSADDR(PHYS_FLASH_1))
	{
	    
		//return MIN_SDRAM_SIZE;
		//fixed to 32MB
		printf("\n In RAM run \n");
		return MIN_SDRAM_SIZE;
	}
#endif
	 


	size = get_ram_size((volatile long *)CONFIG_SYS_SDRAM_BASE, MAX_SDRAM_SIZE);
	if (size > max_size)
	{
		max_size = size;
	//	printf("\n Return MAX size!! \n");
		return max_size;
	}
//	printf("\n Return Real size =%d !! \n",size);
	return size;
	
}

#define RALINK_REG_GPIOMODE		(RALINK_SYSCTL_BASE + 0x860)	// GPIO share scheme
#define RALINK_GPIOMODE_EPHY0		0x200	// GPIO_EPHY_LED0
#define RALINK_GPIOMODE_EPHY1		0x400	// GPIO_EPHY_LED1
#define RALINK_GPIOMODE_EPHY2		0x800	// GPIO_EPHY_LED2
#define RALINK_GPIOMODE_EPHY3		0x1000	// GPIO_EPHY_LED3
#define RALINK_GPIOMODE_EPHY4		0x2000	// GPIO_EPHY_LED4
#define RALINK_REG_GPIOMODE_CLR_BITS(bits) \
    *(volatile unsigned long *)(RALINK_REG_GPIOMODE)=cpu_to_le32( \
        le32_to_cpu(*(volatile unsigned long *)(RALINK_REG_GPIOMODE))&(~(bits)))

int checkboard (void)
{
	puts("Board: " CONFIG_BOARD_NAME "\n");
  { /* Due to we not use RT6856's internal switch, 
     * so release share PIO pin 7, 8, 9, 10, 11; 
     */
    RALINK_REG_GPIOMODE_CLR_BITS(RALINK_GPIOMODE_EPHY0|RALINK_GPIOMODE_EPHY1|RALINK_GPIOMODE_EPHY2| \
                                 RALINK_GPIOMODE_EPHY3|RALINK_GPIOMODE_EPHY4);
  }
	return 0;
}


#if defined (RT6855A_ASIC_BOARD) || defined(RT6855A_FPGA_BOARD)	
static int watchdog_reset(void)
{
	unsigned int word;
	//unsigned int i;

	/* check if do watch dog reset */
	if ((RALINK_REG(RALINK_HIR_REG) & 0xffff0000) == 0x40000) {
		if (!(RALINK_REG(0xbfb00080) >> 31)) {
			/* set delay counter */
			RALINK_REG(RALINK_TIMER5_LDV) = 1000;
			/* enable watch dog timer */
			word = RALINK_REG(RALINK_TIMER_CTL);
			word |= ((1 << 5) | (1 << 25));
			RALINK_REG(RALINK_TIMER_CTL) = word;
			while(1);
		}
	}

	return 0;
}
#endif

int board_early_init_f(void)
{
#if defined (RT6855A_ASIC_BOARD) || defined(RT6855A_FPGA_BOARD)	
	watchdog_reset();
#endif
    return 0;
}

int board_last_init_f(void)
{
    ulong value;
    /* reset Frame engine */
    value = le32_to_cpu(*(volatile u_long *)(RALINK_SYSCTL_BASE + 0x0034));
    udelay(100);    
#if defined (RT2880_FPGA_BOARD) || defined (RT2880_ASIC_BOARD)
    value |= (1 << 18);
#else
    //2880 -> 3052 reset Frame Engine from 18 to 21
    value |= (1 << 21);
#endif
    *(volatile u_long *)(RALINK_SYSCTL_BASE + 0x0034) = cpu_to_le32(value);	
#if defined (RT2880_FPGA_BOARD) || defined (RT2880_ASIC_BOARD)
    value &= ~(1 << 18);
#else
    value &= ~(1 << 21);
#endif
    *(volatile u_long *)(RALINK_SYSCTL_BASE + 0x0034) = cpu_to_le32(value);	
    udelay(200);      
    return 0;
}

#ifdef CONFIG_RT2880_ETH
extern int rt2880_eth_initialize(bd_t *bis);
int board_eth_init(bd_t *bis)
{
#ifdef CONFIG_RTL8367B_SWITCH
extern int rtl8367b_initialize(char *);
	if ( rt2880_eth_initialize(bis) ) {
		return -1;
	}
	return rtl8367b_initialize(NULL);
#else
	return rt2880_eth_initialize(bis);
#endif
}
#endif
