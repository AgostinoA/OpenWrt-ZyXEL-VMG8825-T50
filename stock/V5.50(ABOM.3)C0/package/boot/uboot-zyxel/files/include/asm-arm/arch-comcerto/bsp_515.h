/*
 * (C) Copyright 2006
 * Mindspeed Technologies, Inc. <www.mindspeed.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef _BSP_515_H
#define _BSP_515_H

/* Chip Select Enable Register */
#define EXP_CSSD0	0		/* Y17 */
#define EXP_CSSD1	1		/* AB03 */
#define EXP_CSBOOT	2
#define EXP_CSP0	3
#define EXP_CSP1	5
#define EXP_CSP2	6
#define SDR_CSSD0	13
#define SDR_CSSD1	14

#define CS_DISABLE		0
#define CS_ENABLE		1

#define CS_MEMTYPE_SRAM		0
#define CS_MEMTYPE_SDRAM	1

#define CS_ACTIVE_LOW		0
#define CS_ACTIVE_HIGH		1

#define CS_BUSWIDTH_8BIT	0x0
#define CS_BUSWIDTH_16BIT	0x1
#define CS_BUSWIDTH_32BIT	0x2

#define CS_DQMMODE_NORMAL	0x0
#define CS_DQMMODE_FOLLOW_WE	0x1

#define CLK_MODE_SYNC	0
#define CLK_MODE_ASYNC	1

#define GPIO_TYPE_INPUT		0
#define GPIO_TYPE_OUTPUT	1

#define IOCTRL_SPI_BUS		0
#define IOCTRL_UART0		1
#define IOCTRL_UART1		2
#define IOCTRL_EXPA21_A22	3


#define BELLOW_MEM_SDC0		0
#define BELLOW_MEM_SDC1		1

struct cs_cfg {

	u8 memtype; 		/* 1 = SDRAM or 0 = SRAM CS select */
				/* only xxx_CSSD0 can be SDRAM */

	u32 baseaddr;		/* only valid for xxx_CSSD0 or  xxx_CSSD1 */
	u32 size;		/* only valid for xxx_CSSD0 or xxx_CSSD1 */ /* segment size? */

	u8 buswidth;	/* Data Bus Width */

	/* SRAM config, only valid if memtype = SDRAM; Chip Select Register Setting for SRAMs  */
	u8 level;	/* CS Level */
	u8 cmdwidth;	/* Command Width Index */
	u8 addrsetup;	/* Address Setup */
	u8 dqm_mode;	/* DQM Mode */

	/* SDRAM_CFG1 SDRAM Timing Configuration Register 1, only valid if memtype = SDRAM */
	u8 tras;	/* RAS to Precharge cycle time. (Number of CLK cycles.) */
	u8 trc;		/* REF to REF/RAS cycle time. (Number of CLK cycles.) */
	u8 trcd;	/* Row active to Column Active. (Number of CLK cycles.) */
	u8 trp;		/* Precharge to Row active. (Number of CLK cycles.) */
	u8 cl;		/* CAS Latency. (Number of CLK cycles.) */

	/* SDRAM_CFG2 SDRAM Timing Configuration Register 2, only valid if memtype = SDRAM */
	u8 memchip_dtype;	/* Memory Chip Data Size Type */
	u8 twr;			/* Write Recovery Time (Number of CLK cycles.) */
	u8 tmrd;		/* Mode register set to active or refresh command. (Number of CLK cycles.) */
	u8 trrd;		/* RAS to RAS of opposite banks. (Number of CLK cycles.) */

	/* SDRAM_REFRESH SDRAM Refresh Register, only valid if memtype = SDRAM */
	u16 refcnt;		/* Refresh period count (Number of CLK Cycles). */

	u16 pwroncnt;		/* Power on cycle count */
};

int SoC_cs_cfg(int cs, int enable, struct cs_cfg *cfg);
int SoC_pll_cfg (int mode, unsigned int arm_clk, unsigned int bus_clk);

int SoC_high_mem_cfg (int cs);
int SoC_mem_divider_cfg (u32 address, int sdc);

int SoC_gpio_cfg(int gpio, int mode);
int SoC_ioctrl_cfg(int resource, int enable);

#define SoC_gpio_mask(gpio)		(1 << ((gpio) & 0x1f))

#define SoC_gpio_read(gpiomask)		(*(volatile u32 *)GPIO_INPUT & (gpiomask))
#define SoC_gpio_set_0(gpiomask)	(*(volatile u32 *)GPIO_OUTPUT &= ~(gpiomask))

#define SoC_gpio_set_1(gpiomask)	(*(volatile u32 *)GPIO_OUTPUT |= (gpiomask))

#define SoC_timer0_set(val)		(*(volatile u32 *)TIMER0_COUNT = (val))
#define SoC_timer0_get()		(*(volatile u32 *)TIMER0_CURR_COUNT)

#define SoC_timer1_set(val)		(*(volatile u32 *)TIMER1_COUNT = (val))
#define SoC_timer1_get()		(*(volatile u32 *)TIMER1_CURR_COUNT)

#define SoC_clk_arm_get()		((CFG_REFCLKFREQ * (*(volatile u32 *)CLKCORE_ARM_PLL & 0x7F)) >> 1)

#define SoC_clk_amba_get()		((*(volatile u32 *)CLKCORE_AMBA_PLL & (PLL_POWER | PLL_BYPASS)) ? \
					(SoC_clk_arm_get() >> 1) : \
					((CFG_REFCLKFREQ * (*(volatile u32 *)CLKCORE_AMBA_PLL & 0x7F)) >> 2))

#endif /* _BSP_515_H */
