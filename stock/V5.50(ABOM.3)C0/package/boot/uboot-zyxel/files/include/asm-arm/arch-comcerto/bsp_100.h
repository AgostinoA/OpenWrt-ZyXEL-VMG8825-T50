/*
 * Copyright (C) 2006 Mindspeed Technologies, Inc.
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

#ifndef _BSP_100_H
#define _BSP_100_H

#include <asm/arch/hardware.h>
#ifndef __ASSEMBLY__
#include <asm/byteorder.h>
#endif

#define GPIO_TYPE_INPUT		0
#define GPIO_TYPE_OUTPUT	1

#define COMCERTO_PART_MAGIC 0x4D535044

void SoC_Check_Device(void);
void SoC_APB_setup(void);
void SoC_AHB_setup(void);
void SoC_ARAM_setup(void);

void SoC_PLL_init(void);
void SoC_mem_init(u32 board_config);
void SoC_nand_init(void);
u32 get_ddr_size(void);
void start_training(void);

int SoC_gpio_cfg(int gpio, int mode);

#define SoC_gpio_mask(gpio)		(1 << ((gpio) & 0x1f))

#define SoC_gpio_read(gpiomask)		(__le32_to_cpu(*(volatile u32 *)GPIO_INPUT_REG & (gpiomask)))
#define SoC_gpio_set_0(gpiomask)	(*(volatile u32 *)GPIO_OUTPUT_REG &= __cpu_to_le32(~(gpiomask)))

#define SoC_gpio_set_1(gpiomask)	(*(volatile u32 *)GPIO_OUTPUT_REG |= __cpu_to_le32((gpiomask)))


static inline void HAL_set_arm_clk(u32 fclk)
{
	volatile u32 delay_count;
#ifdef M82134G
	u32 w = 2; 
#else
	u32 w = 1; 
#endif 
	u32 x = 0;
	u32 y = (fclk * ((w + 1) * (x + 1) * 2)) / CFG_REFCLKFREQ;

	// set PLL into BYPASS mode using MUX
	*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL |= __cpu_to_le32(PLL_CLK_BYPASS);
	// do an internal PLL bypass
	*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL |= __cpu_to_le32(ARM_PLL_BY_CTRL);
	// wait 500us 
	delay_count = 12000;
	while (delay_count--);
	// disable the PLL
	*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL |= __cpu_to_le32(PLL_DISABLE);
	// wait 500us 
	delay_count = 12000;
	while (delay_count--);
	// enable the PLL
	*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL &= __cpu_to_le32(~PLL_DISABLE);
	// wait 500us 
	delay_count = 12000;
	while (delay_count--);
	// set X, W and X
	*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL &= __cpu_to_le32(0xFF000000) ;
	*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL |= __cpu_to_le32((x << 16) + (w << 8) + y);
	// wait for PLL to lock
	while( (*(volatile u32 *)CLKCORE_PLL_STATUS & __cpu_to_le32(FCLK_PLL_LOCK)) == 0);

	// remove the internal PLL bypass
	*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL &= __cpu_to_le32(~ARM_PLL_BY_CTRL);
	// remove PLL from BYPASS mode using MUX
	*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL &= __cpu_to_le32(~PLL_CLK_BYPASS);

}

static inline int HAL_get_arm_clk(void)
{
	u32 w;
	u32 x;
	u32 y ;
	u32 reg;

	reg = __le32_to_cpu(*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL);
	x = (reg & 0x0001F0000) >> 16;
	y = (reg & 0x00000007F);
	w = (reg & 0x000000300) >> 8;

	return (CFG_REFCLKFREQ * y /((w + 1) * (x + 1) * 2));
}

static inline void HAL_set_amba_clk(u32 fclk)
{
	volatile u32 delay_count;
	u32 w = 1;
	u32 x = 1;
	u32 y = (fclk *((w + 1) * (x + 1) * 2)) / CFG_REFCLKFREQ;

	// set PLL into BYPASS mode using MUX
	*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL |= __cpu_to_le32(PLL_CLK_BYPASS);
	// do an internal PLL bypass
	*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL |= __cpu_to_le32(AHB_PLL_BY_CTRL);
	// wait 500us (ARM running @24Mhz -> 12000 cycles => 500us)
	delay_count = 12000;
	while (delay_count--);
	// disable the PLL
	*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL |= __cpu_to_le32(PLL_DISABLE);
	// wait 500us 
	delay_count = 12000;
	while (delay_count--);
	// enable the PLL
	*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL &= __cpu_to_le32(~PLL_DISABLE);
	// wait 500us 
	delay_count = 12000;
	while (delay_count--);
	// set X, W and X
	*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL &= __cpu_to_le32(0xFF000000) ;
	*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL |= __cpu_to_le32((x << 16) + (w << 8) + y);
	// wait for PLL to lock
	while( (*(volatile u32 *)CLKCORE_PLL_STATUS & __cpu_to_le32(AHBCLK_PLL_LOCK)) == 0);

	// remove the internal PLL bypass
	*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL &= __cpu_to_le32(~AHB_PLL_BY_CTRL);
	// remove PLL from BYPASS mode using MUX
	*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL &= __cpu_to_le32(~PLL_CLK_BYPASS);
}



static inline int HAL_get_amba_clk(void)
{
	u32 w;
	u32 x;
	u32 y ;
	u32 reg;

	reg = __le32_to_cpu(*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL);
	x = (reg & 0x0001F0000) >> 16;
	y = (reg & 0x00000007F) ;
	w = (reg & 0x000000300) >> 8;
	return (CFG_REFCLKFREQ * y / ((w + 1) * (x + 1) * 2));
}


#endif /* _BSP_100_H */
