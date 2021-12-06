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

#ifndef _BSP_1000_H
#define _BSP_1000_H

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

void SoC_PLL_init(int n);
void SoC_nand_init(void);
u32 get_ddr_size(void);
void start_training(void);

int SoC_gpio_cfg(int gpio, int mode);

#define SoC_gpio_mask(gpio)		(1 << ((gpio) & 0x1f))

#define SoC_gpio_read(gpiomask)		(__le32_to_cpu(*(volatile u32 *)GPIO_INPUT_REG & (gpiomask)))
#define SoC_gpio_set_0(gpiomask)	(*(volatile u32 *)GPIO_OUTPUT_REG &= __cpu_to_le32(~(gpiomask)))

#define SoC_gpio_set_1(gpiomask)	(*(volatile u32 *)GPIO_OUTPUT_REG |= __cpu_to_le32((gpiomask)))

static inline u32 HAL_get_ahb_clk(void);

extern u32 CFG_HZ_CLOCK;

struct c1000_cfg_clk {
	u32 arm_pll;
	u32 arm_pll_nr;
	u32 arm_pll_od;

	u32 ahb_pll;
	u32 ahb_pll_nr;
	u32 ahb_pll_od;

	u32 phy_pll;
	u32 phy_pll_nr;
	u32 phy_pll_od;

	int arm_from_sclk2;

	u32 arm_clk;

	int ddr_from_fclk;

	u32 ahb_clk;
	u32 ddr_clk;
	u32 ipsec_clk;
};

#define CFG_CLK_650_187_375 0
#define CFG_CLK_600_165_330 1
#define CFG_CLK_534_178_330 2
#define CFG_CLK_450_165_330 3
#define CFG_CLK_400_165_330 4
#define CFG_CLK_650_200_200 5
#define CFG_CLK_650_187_325 6
#define CFG_CLK_610_186_372 7

static inline void HAL_set_arm_pll(u32 fclk, u32 NR, u32 OD)
{
	volatile u32 delay_count;
	u32 NF;
	u32 NB;
	u32 ref_clk = CFG_REFCLKFREQ / 1000000;

	fclk = fclk / 1000000; 
	NF = (fclk * NR * OD) / ref_clk;

	NB = (NF * 2) / 5;

	NR--;OD--;NF--;NB--;

#if 0
	//power up PLL
	*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL &= ~ARM_CLK_CNTRL_PLL_PWDN;

	//set PLL into reset mode
	*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL2 |= ARM_CLK_CNTRL2_PLL_RESET;
#endif

	// set NR / NF
	*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL &= __cpu_to_le32(0xFFC0E000);
	*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL |= __cpu_to_le32((NR << 16) + NF);
	// set OD and NB (NB=NF/2.5)
	*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL2 &= __cpu_to_le32(0x8000FFFF);
        *(volatile u32 *)CLKCORE_ARM_CLK_CNTRL2 |= __cpu_to_le32((OD << 28) + (NB << 16));

	//wait 5 uS.... looks like it is one cycle...
	delay_count = 12000;
//	while (delay_count--);

	*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL2 &= __cpu_to_le32(~ARM_CLK_CNTRL2_PLL_RESET);

	//wait 21 uS.... looks like it is one cycle...
	delay_count = 10;
	while (delay_count--);

	//clear status bit 
	do {
		*(volatile u32 *)CLKCORE_PLL_STATUS &= __cpu_to_le32(~PLL_STATUS_ARM_PLL_STATUS_CLEAR);	
		delay_count = 20;
		while (delay_count--);
	} while ((*(volatile u32 *)CLKCORE_PLL_STATUS & __cpu_to_le32(PLL_STATUS_ARM_PLL_STATUS)));
}

static inline u32 HAL_get_arm_pll(void)
{
	u32 NR;
	u32 OD;
	u32 NF;
	u32 ref_clk = CFG_REFCLKFREQ / 1000000;
	u32 reg = __le32_to_cpu(*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL);
	NR = (reg & 0x003F0000) >> 16;
	NF = (reg & 0x00001FFF);
	reg = __le32_to_cpu(*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL2);
	OD = (reg & 0x70000000) >> 28;

	return ( ref_clk * (NF + 1) / (NR  + 1) / (OD  + 1) ) * 1000000;
}

static inline u32 HAL_get_ahb_pll(void)
{
	u32 NR;
	u32 OD;
	u32 NF;
	u32 ref_clk = CFG_REFCLKFREQ / 1000000;
	u32 reg = __le32_to_cpu(*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL);

	NR = (reg & 0x003F0000) >> 16;
	NF = (reg & 0x00001FFF);
	reg = __le32_to_cpu(*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL2);
	OD = (reg & 0x70000000) >> 28;

	return ( ref_clk * (NF + 1) / (NR  + 1) / (OD  + 1) ) * 1000000;
}

static inline void HAL_set_arm_clk(u32 arm0_clk, u32 arm1_clk, int arm_from_sclk2)
{
/*	
 *	This is new in C1000; you can set different clock for ARM0 and ARM1	
 *	In u-boot ARM1 is under reset. We will not configure the ARM1_FCLK. It will be set in by-pass mode.
 */
	u32 pll;

	if (arm_from_sclk2)
		pll = HAL_get_ahb_pll();
	else
		pll = HAL_get_arm_pll();

//setup arm0 clock
	if(arm0_clk == pll)
	{
		*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL2 |= __cpu_to_le32(ARM_CLK_CNTRL2_ARM0_DIV_BYPASS);	
	}
	else
	{
		u32 div0 = pll / arm0_clk;

		*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL2 &= __cpu_to_le32(0xFFFFFFF0);
		// ARM0_FCLK = FCLK / div
		*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL2 |= __cpu_to_le32(div0 & 0xF);
		*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL2 &= __cpu_to_le32(~ARM_CLK_CNTRL2_ARM0_DIV_BYPASS);
	}
//setup arm1 clock
	if(arm1_clk == pll)
	{
		*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL2 |= __cpu_to_le32(ARM_CLK_CNTRL2_ARM1_DIV_BYPASS);	
	}
	else
	{
		u32 div1 = pll / arm1_clk;

		*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL2 &= __cpu_to_le32(0xFFFFF0FF);
		// ARM0_FCLK = FCLK / div
		*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL2 |= __cpu_to_le32((div1 & 0xF) << 8);
		*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL2 &= __cpu_to_le32(~ARM_CLK_CNTRL2_ARM1_DIV_BYPASS);
	}

	if (arm_from_sclk2)
        	*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL2 |= __cpu_to_le32((ARM_CLK_CNTRL2_ARM0_AHB_BYPASS | ARM_CLK_CNTRL2_ARM1_AHB_BYPASS));
	else
		*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL2 &= __cpu_to_le32(~(ARM_CLK_CNTRL2_ARM0_AHB_BYPASS | ARM_CLK_CNTRL2_ARM1_AHB_BYPASS));
}

static inline u32 HAL_get_arm0_clk(void)
{
	u32 mode = __le32_to_cpu(*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL2);
	u32 pll;

	if (mode & ARM_CLK_CNTRL2_ARM0_AHB_BYPASS)
		pll = HAL_get_ahb_pll();
	else
		pll =  HAL_get_arm_pll();

	if (mode & ARM_CLK_CNTRL2_ARM0_DIV_BYPASS)
	{
		return pll;
	}
	else
	{
		u32 div = mode & 0xf;

		return pll / div;
	}
}

static inline u32 HAL_get_arm1_clk(void)
{
	u32 mode = __le32_to_cpu(*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL2);
	u32 pll;

	if (mode & ARM_CLK_CNTRL2_ARM1_AHB_BYPASS)
		pll = HAL_get_ahb_pll();
	else
		pll = HAL_get_arm_pll();

	if (mode & ARM_CLK_CNTRL2_ARM1_DIV_BYPASS)
	{
		return pll;
	}
	else
	{
		u32 div = (mode >> 8) & 0xf;

		return pll / div;
	}
}


static inline void HAL_set_ahb_pll(u32 sclk, u32 NR, u32 OD)
{
	volatile u32 delay_count;
	u32 NF;
        u32 NB;
	u32 ref_clk = CFG_REFCLKFREQ / 1000000;

	sclk = sclk / 1000000; 
	NF = (sclk * NR * OD) / ref_clk;

	NB = (NF * 2) / 5;
	
	NR--;OD--;NF--;NB--;
#if 0	
	//power up PLL
	*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL &= ~AHB_CLK_CNTRL_PLL_PWDN;

	//set PLL into reset mode
	*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL2 |= AHB_CLK_CNTRL2_PLL_RESET;
#endif

	// set NR / NF
	*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL &= __cpu_to_le32(0xFFC0E000);
	*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL |= __cpu_to_le32((NR << 16) + NF);
	// set OD and NB (NB=NF/2.5)
	*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL2 &= __cpu_to_le32(0x8000FFFF);
	*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL2 |= __cpu_to_le32((OD << 28) + (NB << 16));

	//wait 5 uS.... looks like it is one cycle...
	delay_count = 12000;
//	while (delay_count--);	
	*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL2 &= __cpu_to_le32(~AHB_CLK_CNTRL2_PLL_RESET);
	
	//wait 21 uS.... looks like it is one cycle...
	delay_count = 600;
//	while (delay_count--);	
//clear status bit 
	do {
		*(volatile u32 *)CLKCORE_PLL_STATUS &= __cpu_to_le32(~PLL_STATUS_AHB_PLL_STATUS_CLEAR);	
		delay_count = 600;
		while (delay_count--);
	} while ((*(volatile u32 *)CLKCORE_PLL_STATUS & __cpu_to_le32(PLL_STATUS_AHB_PLL_STATUS)));
	
}

static inline u32 HAL_get_ahb_clk(void)
{
	u32 sync_mode = __le32_to_cpu(*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL);
	
	if (sync_mode & AHB_CLK_CNTRL_SYNC_MODE)
	{//sync mode ahb is sync with fclk
		u32 arm_pll = HAL_get_arm_pll();

		if (sync_mode & AHB_CLK_CNTRL_SYNC_DIV_BYPASS)
		{
			return arm_pll;
		}
		else
		{// ahb = fclk/sync_div
			u32 div = (sync_mode >> 26) & 0x7;

			return arm_pll / div;
		}
	}
	else
	{// not in sync mode
		u32 ahb_pll = HAL_get_ahb_pll();
		u32 mode = __le32_to_cpu(*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL2);
		u32 div = 1;

		if (!(mode & AHB_CLK_CNTRL2_AHB_DIV0_BYPASS))
		{// AHB_DIV0 is used
			div = div * (mode & 0xF);
		}
		
		if (!(mode & AHB_CLK_CNTRL2_AHB_DIV1_BYPASS))
		{// AHB_DIV1 is used
			div = div * ((mode >> 4) & 0xF);
		}

		return ahb_pll / div;
	}
}

static inline u32 HAL_get_ddr_clk(void)
{
	u32 ddr_mux_sel = __le32_to_cpu(*(volatile u32 *)CLKCORE_DDR_PCIE_CLK_CNTRL);
	
	if (ddr_mux_sel & DDR_PCIE_CLK_CNTRL_DDR_MUX_SEL)
	{//ddr is derived from arm pll (fclk)
		u32 arm_pll = HAL_get_arm_pll();

		if (ddr_mux_sel & DDR_PCIE_CLK_CNTRL_DDR_DIV_BYPASS)
		{//bypass ddr clk = fclk
			return arm_pll;
		}
		else
		{// ddr = fclk/ddr_div_val
			u32 div = (ddr_mux_sel >> 4) & 0xf;

			return arm_pll / div;
		}
	}
	else
	{// ddr is derived from ahb pll (sclk1)
		u32 ahb_pll = HAL_get_ahb_pll();
		u32 mode = __le32_to_cpu(*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL2);
		if (mode & AHB_CLK_CNTRL2_AHB_DIV0_BYPASS)
		{// clock switch is syn_mux output (bypass mode enable)
			//should not come here!!!
			return 0;
		}
		else
		{// clock switch output is AHB_DIV0 
			u32 div0 = mode & 0xF;
			return ahb_pll / div0;
		}
	}
}

static inline void HAL_set_phy_pll(u32 fclk, u32 NR, u32 OD)
{
	volatile u32 delay_count;
	u32 NF;
        u32 NB;
	u32 ref_clk = CFG_REFCLKFREQ / 1000000;

	fclk = fclk / 1000000; 
	NF = (fclk * NR * OD) / ref_clk;

	NB = (NF * 2) / 5;

	NR--;OD--;NF--;NB--;
	
	// set NR / NF
	*(volatile u32 *)CLKCORE_PHY_CLK_CNTRL &= __cpu_to_le32(0xFFC0E000);
	*(volatile u32 *)CLKCORE_PHY_CLK_CNTRL |= __cpu_to_le32((NR << 16) + NF);
	// set OD and NB (NB=NF/2.5)
	*(volatile u32 *)CLKCORE_PHY_CLK_CNTRL2 &= __cpu_to_le32(0x8000FFFF);
        *(volatile u32 *)CLKCORE_PHY_CLK_CNTRL2 |= __cpu_to_le32((OD << 28) + (NB << 16));

	//wait 5 uS.... looks like it is one cycle...
	delay_count = 12000;
//	while (delay_count--);

	//set PLL into reset mode
	*(volatile u32 *)CLKCORE_PHY_CLK_CNTRL2 &= __cpu_to_le32(~PHY_CLK_CNTRL2_PLL_RESET);

	//wait 5 uS.... looks like it is one cycle...
	delay_count = 600;
	while (delay_count--);	
	//clear status bit 
	do {
		*(volatile u32 *)CLKCORE_PLL_STATUS &= __cpu_to_le32(~PLL_STATUS_PHY_PLL_STATUS_CLEAR);	
		delay_count = 600;
		while (delay_count--);
	} while ((*(volatile u32 *)CLKCORE_PLL_STATUS & __cpu_to_le32(PLL_STATUS_PHY_PLL_STATUS)));
}

static inline u32 HAL_get_phy_pll(void)
{
	u32 NR;
	u32 OD;
	u32 NF;
	u32 ref_clk = CFG_REFCLKFREQ / 1000000;
	u32 reg = __le32_to_cpu(*(volatile u32 *)CLKCORE_PHY_CLK_CNTRL);
	NR = (reg & 0x003F0000) >> 16;
	NF = (reg & 0x00001FFF);
	reg = __le32_to_cpu(*(volatile u32 *)CLKCORE_PHY_CLK_CNTRL2);
	OD = (reg & 0x70000000) >> 28;

	return ( ref_clk * (NF + 1) / (NR  + 1) / (OD  + 1) ) * 1000000;
}

static inline void HAL_set_phy_gem_clk(u32 gem0_refclk, u32 gem1_refclk, u32 phy_refclk)
{
	u32 phy_pll = HAL_get_phy_pll();
	u32 div0 = (phy_pll / gem0_refclk) & 0xF;
	u32 div1 = (phy_pll / gem1_refclk) & 0xF;
	u32 div2 = (phy_pll / phy_refclk) & 0xF;

	if (div0 != 1) {
		*(volatile u32 *)CLKCORE_PHY_CLK_CNTRL2 &= __cpu_to_le32(0xFFFFFFF0);
		*(volatile u32 *)CLKCORE_PHY_CLK_CNTRL2 |= __cpu_to_le32(div0);
		*(volatile u32 *)CLKCORE_PHY_CLK_CNTRL2 &= __cpu_to_le32(~PHY_CLK_CNTRL2_PHY_DIV0_BYPASS);
	}
	else
	{
		*(volatile u32 *)CLKCORE_PHY_CLK_CNTRL2 |= __cpu_to_le32(PHY_CLK_CNTRL2_PHY_DIV0_BYPASS);
	}

	if (div1 != 1) {
		*(volatile u32 *)CLKCORE_PHY_CLK_CNTRL2 &= __cpu_to_le32(0xFFFFFF0F);
		*(volatile u32 *)CLKCORE_PHY_CLK_CNTRL2 |= __cpu_to_le32(div1 << 4);
		*(volatile u32 *)CLKCORE_PHY_CLK_CNTRL2 &= __cpu_to_le32(~PHY_CLK_CNTRL2_PHY_DIV1_BYPASS);
	}
	else
	{
		*(volatile u32 *)CLKCORE_PHY_CLK_CNTRL2 |= __cpu_to_le32(PHY_CLK_CNTRL2_PHY_DIV1_BYPASS);	
	}

	if (div2 != 1) {
		*(volatile u32 *)CLKCORE_PHY_CLK_CNTRL2 &= __cpu_to_le32(0xFFFFF0FF);
		*(volatile u32 *)CLKCORE_PHY_CLK_CNTRL2 |= __cpu_to_le32(div2 << 8);
		*(volatile u32 *)CLKCORE_PHY_CLK_CNTRL2 &= __cpu_to_le32(~PHY_CLK_CNTRL2_PHY_DIV2_BYPASS);
	}
	else
	{	
		*(volatile u32 *)CLKCORE_PHY_CLK_CNTRL2 |= __cpu_to_le32(PHY_CLK_CNTRL2_PHY_DIV2_BYPASS);
	}
}


static inline void HAL_set_ahb_ddr_clk(u32 ahbclk, u32 ddr_clk, int flags)
{
	u32 ahb_pll = HAL_get_ahb_pll();
	u32 arm_pll = HAL_get_arm_pll();
	u32 ahb_div0, ahb_div1, ddr_div;

	if (flags)
	{
		// DDR uses FLCK
		// AHB uses SCLK1
		ddr_div = arm_pll / ddr_clk;

		ahb_div0 = ahb_pll / ahbclk;
		ahb_div1 = 1;		

		// DDR MUX from ARM PLL
		*(volatile u32 *)CLKCORE_DDR_PCIE_CLK_CNTRL |= __cpu_to_le32(DDR_PCIE_CLK_CNTRL_DDR_MUX_SEL);
	}
	else
	{
		// DDR uses SCLK2
		// AHB uses SCLK1
		ddr_div = 1;
		ahb_div0 = ahb_pll / ddr_clk;
		ahb_div1 = ddr_clk / ahbclk;

		// DDR MUX from AHB PLL
		*(volatile u32 *)CLKCORE_DDR_PCIE_CLK_CNTRL &= __cpu_to_le32(~DDR_PCIE_CLK_CNTRL_DDR_MUX_SEL);
	}

	if (ddr_div != 1)
	{
		
		*(volatile u32 *)CLKCORE_DDR_PCIE_CLK_CNTRL &= __cpu_to_le32(0xFFFFFF0F);
		*(volatile u32 *)CLKCORE_DDR_PCIE_CLK_CNTRL |= __cpu_to_le32((ddr_div & 0xF) << 4);
		// DDR DIV Bypass disable
		*(volatile u32 *)CLKCORE_DDR_PCIE_CLK_CNTRL &=  __cpu_to_le32(~DDR_PCIE_CLK_CNTRL_DDR_DIV_BYPASS);
	}
	else
	{	// DDR DIV Bypass enable
		*(volatile u32 *)CLKCORE_DDR_PCIE_CLK_CNTRL |= __cpu_to_le32(DDR_PCIE_CLK_CNTRL_DDR_DIV_BYPASS);
	} 


	if (ahb_div0 != 1)
	{
		
		*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL2 &= __cpu_to_le32(0xFFFFFFF0);
		*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL2 |= __cpu_to_le32(ahb_div0 & 0xF);
		// AHB DIV0 Bypass disable
		*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL2 &=  __cpu_to_le32(~(AHB_CLK_CNTRL2_AHB_DIV0_BYPASS));
	}
	else
	{	// AHB DIV0 Bypass enable
		*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL2 |= __cpu_to_le32(AHB_CLK_CNTRL2_AHB_DIV0_BYPASS);
	} 

	if (ahb_div1 != 1)
	{
		
		*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL2 &= __cpu_to_le32(0xFFFFFF0F);
		*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL2 |= __cpu_to_le32((ahb_div1 & 0xF) << 4);
		// AHB DIV1 Bypass disable
		*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL2 &=  __cpu_to_le32(~(AHB_CLK_CNTRL2_AHB_DIV1_BYPASS));
	}
	else
	{	// AHB DIV1 Bypass enable
		*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL2 |= __cpu_to_le32(AHB_CLK_CNTRL2_AHB_DIV1_BYPASS);
	}
}

static inline void HAL_all_pll_bypass(void)
{
	*(volatile u32 *)CLKCORE_PHY_CLK_CNTRL |= __cpu_to_le32(PHY_CLK_CNTRL_PHY_REF_BYPASS);
	*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL |= __cpu_to_le32(AHB_CLK_CNTRL_AHB_REF_BYPASS);

	*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL |= __cpu_to_le32(ARM_CLK_CNTRL_ARM_REF_BYPASS);

	//AHB sync mode disable we will take the clock from AHB pll
	*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL &= __cpu_to_le32(~AHB_CLK_CNTRL_SYNC_MODE);

	// ARM DIV Bypass
	*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL2 |= __cpu_to_le32(ARM_CLK_CNTRL2_ARM0_DIV_BYPASS \
						| ARM_CLK_CNTRL2_ARM1_DIV_BYPASS);
	// AHB DIV Bypass
	*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL2 |=  __cpu_to_le32(AHB_CLK_CNTRL2_AHB_DIV0_BYPASS \
						| AHB_CLK_CNTRL2_AHB_DIV1_BYPASS) ;
}

static inline void HAL_set_ipsec_clk(u32 ipsec_clk)
{
	u32 ahb_pll = HAL_get_ahb_pll();
	u32 div;

	div = ahb_pll / ipsec_clk;

	div = div << 12;
	*(volatile u32 *)CLKCORE_DDR_PCIE_CLK_CNTRL = (*(volatile u32 *)CLKCORE_DDR_PCIE_CLK_CNTRL & __cpu_to_le32(~0xf000UL)) | __cpu_to_le32(div);

	*(volatile u32 *)CLKCORE_DDR_PCIE_CLK_CNTRL &= __cpu_to_le32(~DDR_PCIE_CLK_CNTRL_IPsec_DIV0_BYPASS);

	*(volatile u32 *)CLKCORE_DDR_PCIE_CLK_CNTRL &= __cpu_to_le32(~DDR_PCIE_CLK_CNTRL_IPsecMUX_SEL);
}

static inline u32 HAL_get_ipsec_clk(void)
{
        u32 ipsec_mux_sel = __le32_to_cpu(*(volatile u32 *)CLKCORE_DDR_PCIE_CLK_CNTRL);

        if (ipsec_mux_sel & DDR_PCIE_CLK_CNTRL_IPsecMUX_SEL)
        {
                u32 arm_pll = HAL_get_arm_pll();

                if (ipsec_mux_sel & DDR_PCIE_CLK_CNTRL_IPsec_DIV1_BYPASS)
                        return arm_pll;
                else
                {
                        u32 div = (ipsec_mux_sel >> 16) & 0xf;

                        return arm_pll / div;
                }
        }
        else
        {
                u32 ahb_pll = HAL_get_ahb_pll();

                if (ipsec_mux_sel & DDR_PCIE_CLK_CNTRL_IPsec_DIV0_BYPASS)
                        return ahb_pll;
                else
                {
                        u32 div = (ipsec_mux_sel >> 12) & 0xf;

                        return ahb_pll / div;
                }
        }
}


static inline void HAL_all_pll_remove_bypass(void)
{
	*(volatile u32 *)CLKCORE_ARM_CLK_CNTRL &= __cpu_to_le32(~ARM_CLK_CNTRL_ARM_REF_BYPASS);
	*(volatile u32 *)CLKCORE_AHB_CLK_CNTRL &= __cpu_to_le32(~AHB_CLK_CNTRL_AHB_REF_BYPASS);
	*(volatile u32 *)CLKCORE_PHY_CLK_CNTRL &= __cpu_to_le32(~PHY_CLK_CNTRL_PHY_REF_BYPASS);
}
#define HAL_get_amba_clk HAL_get_ahb_clk
#define HAL_get_arm_clk HAL_get_arm0_clk
#endif /* _BSP_1000_H */
