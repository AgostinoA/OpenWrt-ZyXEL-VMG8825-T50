/*
 * Copyright (C) 2007-2008 Mindspeed Technologies Inc.
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
#include <asm/hardware.h>

u32 CFG_HZ_CLOCK;	/* Allow for AHB clock frequency to be chosen at run time */


void SoC_Check_Device(void)
{
	// This should run on a M83xxx SoC, let's check it
	u32 devicetype = __le32_to_cpu((*(volatile u32*)(GPIO_DEVID_REG)) & __cpu_to_le32(0xFFFF));

	if (devicetype != 0x170)
	{
		//error wrong device
		// TODO: what should we do?
	}
}

void SoC_APB_setup(void)
{
	// Setting APB Bus Wait states to 0, set post write
	*(volatile u32*)(APB_ACCESS_WS_REG) = __cpu_to_le32(0x40);
}

void SoC_ARAM_setup(void)
{
	// enable ARAM collision detection
	// read mod write to set bit 2 to enable.  Keep default of 32 byte mask
	*(volatile u32*)(MEMCORE_BASEADDR+0x4) |= __cpu_to_le32(4);
	// disable ARAM pipeline mode
	*(volatile u32*)(MEMCORE_BASEADDR+0x38) = __cpu_to_le32(0);
	// set ARAM port/fbp priority to 1 
	*(volatile u32*)(MEMCORE_BASEADDR+0x0C) = __cpu_to_le32(3); 
}


void SoC_AHB_setup(void)
{
	// DDR size 512MB, starting from 80000000
	*(volatile u32*) AHB_HIGHMEM_ADDR_TRANSLATION = __cpu_to_le32(0x9FFF); 	//(AHB_BASEADDR + 0x04)
	// Disable REMAP (Low Mem region is mapped to DDR base)
	*(volatile u32*) AHB_LOWMEM_REMAP_CTRL = __cpu_to_le32(0x0);		//(AHB_BASEADDR + 0x00)
	// 2nd stage level muxs are configured to round-robin
	*(volatile u32*) AHB_STAGE2_ARBITER_CFG	= __cpu_to_le32(0x0);	//(AHB_BASEADDR + 0x08)
}


void SoC_PLL_init(int cfg)
{
	struct c1000_cfg_clk c1000_cfg_clk_table[] =
	{
		[CFG_CLK_650_187_375] = {650000000, 3, 4, 750000000, 2, 2, 250000000, 3, 8, 0, 650000000, 0, 187500000, 375000000, 250000000}, /* M8326x, 375MHz */
		[CFG_CLK_600_165_330] = {600000000, 1, 4, 660000000, 1, 4, 250000000, 3, 8, 0, 600000000, 0, 165000000, 330000000, 110000000}, /* M83160 */
		[CFG_CLK_534_178_330] = {660000000, 1, 4, 534000000, 1, 4, 250000000, 3, 8, 1, 534000000, 1, 178000000, 330000000, 178000000}, /* M8325x */
		[CFG_CLK_450_165_330] = {450000000, 1, 4, 660000000, 1, 4, 250000000, 3, 8, 0, 450000000, 0, 165000000, 330000000, 110000000}, /* M8324x */
		[CFG_CLK_400_165_330] = {400000000, 2, 6, 660000000, 1, 4, 250000000, 3, 8, 0, 400000000, 0, 165000000, 330000000, 110000000}, /* M83240 */
		[CFG_CLK_650_200_200] = {650000000, 3, 4, 800000000, 3, 2, 250000000, 3, 8, 0, 650000000, 0, 200000000, 200000000, 266666666}, /* M8326x, 200MHz */
		[CFG_CLK_650_187_325] = {650000000, 3, 4, 750000000, 2, 2, 250000000, 3, 8, 0, 650000000, 1, 187500000, 325000000, 250000000}, /* Asic */
		[CFG_CLK_610_186_372] = {610000000, 3, 4, 744000000, 2, 2, 250000000, 3, 8, 0, 610000000, 0, 186000000, 372000000, 248000000} /* Asic */
	};
	struct c1000_cfg_clk *cfg_clk = &c1000_cfg_clk_table[cfg];

	// *(volatile u32*)(GPIO_ARM_MEMORY_SENSE_REGS) = __cpu_to_le32(0x1B6DB6DB); /* Margin = 3 */
	//*(volatile u32*)(GPIO_ARM_MEMORY_SENSE_REGS) = __cpu_to_le32(0x24924924); /* Margin = 4 */
	*(volatile u32*)(GPIO_ARM_MEMORY_SENSE_REGS) = __cpu_to_le32(0x2DB6DB6D);       /* Margin = 5 */

	// Make sure DDR controller is reset
	*(volatile u32*)(CLKCORE_BLK_RESET) &= __cpu_to_le32(~(BLK_RESET_DDR_REF_RESET_N | BLK_RESET_DDR_AHB_RESET_N));

	HAL_all_pll_bypass();

	// Take DDR controller out of reset
	*(volatile u32*)(CLKCORE_BLK_RESET) |= __cpu_to_le32(BLK_RESET_DDR_REF_RESET_N | BLK_RESET_DDR_AHB_RESET_N);

	HAL_set_arm_pll(cfg_clk->arm_pll, cfg_clk->arm_pll_nr, cfg_clk->arm_pll_od);
	HAL_set_ahb_pll(cfg_clk->ahb_pll, cfg_clk->ahb_pll_nr, cfg_clk->ahb_pll_od);
	HAL_set_phy_pll(cfg_clk->phy_pll, cfg_clk->phy_pll_nr, cfg_clk->phy_pll_od);

	HAL_set_arm_clk(cfg_clk->arm_clk, cfg_clk->arm_clk, cfg_clk->arm_from_sclk2);
	HAL_set_ahb_ddr_clk(cfg_clk->ahb_clk, cfg_clk->ddr_clk, cfg_clk->ddr_from_fclk);
	HAL_set_phy_gem_clk(CFG_GEM0_CLOCK, CFG_GEM1_CLOCK, CFG_PHY_CLOCK);
	HAL_set_ipsec_clk(cfg_clk->ipsec_clk);

	HAL_all_pll_remove_bypass();
}

void SoC_nand_init(void)
{
	// TODO: verify timings

	// Configure CS4 - 8 bits - NAND
	*(volatile u32*)(EX_CS4_CFG_REG) = __cpu_to_le32(EX_MEM_BUS_8 | EX_NAND_MODE);
	// timings (CSw = 9, RE WE 9), 
	*(volatile u32*)(EX_CS4_TMG1_REG) = __cpu_to_le32(9 | 9<<16 | 9<<24) ;
	*(volatile u32*)(EX_CSEN_REG)  |= __cpu_to_le32(EX_CS4_EN);	
}

/*
* SoC_gpio_cfg - configure GPIO pins as input or output pins
*
* gpio - gpio pin
*
* mode - gpio pin mode
*	GPIO_TYPE_OUTPUT = output
*	GPIO_TYPE_INPUT = input
*
*/
int SoC_gpio_cfg(int gpio, int mode)
{
	if ((gpio < 0) || (gpio > 31))
		goto err;

	switch (mode) {
	case GPIO_TYPE_INPUT:
	default:
		*(volatile u32 *) GPIO_OE_REG &= __cpu_to_le32(~(1 << gpio));
		break;

	case GPIO_TYPE_OUTPUT:
		*(volatile u32 *) GPIO_OE_REG |= __cpu_to_le32(1 << gpio);
		break;
	}

	return 0;

err:
	return -1;
}

void arm_write64(u64 data,volatile u64 *p)
{
        int *tptr = &data;
        register int reg_0 __asm__ ("r3");
        register int reg_1 __asm__ ("r4");

        __asm__ __volatile__ (
                "ldmia     %0, {%1,%2}     \n\t"
                : "+r" (tptr), "=r" (reg_0), "=r" (reg_1)
        );
        __asm__ __volatile__ (
                "stmia     %0, {%1,%2}     \n\t"
                : "+r" (p), "=r" (reg_0), "=r" (reg_1)
        );
}
