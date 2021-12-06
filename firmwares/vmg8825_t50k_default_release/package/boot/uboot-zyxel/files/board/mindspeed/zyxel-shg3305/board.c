/*
 * Copyright (C) 2006 Mindspeed Technologies Inc.
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <common.h>
#include <config.h>
#include <asm/mach-types.h>
#include <asm/arch/bsp.h>
DECLARE_GLOBAL_DATA_PTR;
extern void arm_write64(u64 data,volatile u64 *p);

static void config_board1(void)
{
  // Configure DDR
	*(volatile u64*)(DENALI_CTL_00_DATA) = __cpu_to_le64((u64)DENALI_CTL_00_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_01_DATA) = __cpu_to_le64((u64)DENALI_CTL_01_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_02_DATA) = __cpu_to_le64((u64)DENALI_CTL_02_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_03_DATA) = __cpu_to_le64((u64)DENALI_CTL_03_VAL_CFG1);
//	*(volatile u64*)(DENALI_CTL_04_DATA) = __cpu_to_le64((u64)DENALI_CTL_04_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_05_DATA) = __cpu_to_le64((u64)DENALI_CTL_05_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_06_DATA) = __cpu_to_le64((u64)DENALI_CTL_06_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_07_DATA) = __cpu_to_le64((u64)DENALI_CTL_07_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_08_DATA) = __cpu_to_le64((u64)DENALI_CTL_08_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_09_DATA) = __cpu_to_le64((u64)DENALI_CTL_09_VAL_CFG1);
//	*(volatile u64*)(DENALI_CTL_10_DATA) = __cpu_to_le64((u64)DENALI_CTL_10_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_11_DATA) = __cpu_to_le64((u64)DENALI_CTL_11_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_12_DATA) = __cpu_to_le64((u64)DENALI_CTL_12_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_13_DATA) = __cpu_to_le64((u64)DENALI_CTL_13_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_14_DATA) = __cpu_to_le64((u64)DENALI_CTL_14_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_15_DATA) = __cpu_to_le64((u64)DENALI_CTL_15_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_16_DATA) = __cpu_to_le64((u64)DENALI_CTL_16_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_17_DATA) = __cpu_to_le64((u64)DENALI_CTL_17_VAL_CFG1);
#ifdef CFG_DDR_16BIT
	*(volatile u64*)(DENALI_CTL_18_DATA) = __cpu_to_le64((u64)DENALI_CTL_18_VAL_CFG1 | (1ULL << 24));
#else
	*(volatile u64*)(DENALI_CTL_18_DATA) = __cpu_to_le64((u64)DENALI_CTL_18_VAL_CFG1);
#endif
	*(volatile u64*)(DENALI_CTL_19_DATA) = __cpu_to_le64((u64)DENALI_CTL_19_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_20_DATA) = __cpu_to_le64((u64)DENALI_CTL_20_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_21_DATA) = __cpu_to_le64((u64)DENALI_CTL_21_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_22_DATA) = __cpu_to_le64((u64)DENALI_CTL_22_VAL_CFG1);
//	*(volatile u64*)(DENALI_CTL_23_DATA) = __cpu_to_le64((u64)DENALI_CTL_23_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_24_DATA) = __cpu_to_le64((u64)DENALI_CTL_24_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_25_DATA) = __cpu_to_le64((u64)DENALI_CTL_25_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_26_DATA) = __cpu_to_le64((u64)DENALI_CTL_26_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_27_DATA) = __cpu_to_le64((u64)DENALI_CTL_27_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_28_DATA) = __cpu_to_le64((u64)DENALI_CTL_28_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_29_DATA) = __cpu_to_le64((u64)DENALI_CTL_29_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_30_DATA) = __cpu_to_le64((u64)DENALI_CTL_30_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_31_DATA) = __cpu_to_le64((u64)DENALI_CTL_31_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_32_DATA) = __cpu_to_le64((u64)DENALI_CTL_32_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_33_DATA) = __cpu_to_le64((u64)DENALI_CTL_33_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_34_DATA) = __cpu_to_le64((u64)DENALI_CTL_34_VAL_CFG1);
//	*(volatile u64*)(DENALI_CTL_35_DATA) = __cpu_to_le64((u64)DENALI_CTL_35_VAL_CFG1);
	arm_write64(DENALI_CTL_35_VAL_CFG1,DENALI_CTL_35_DATA);//should be 64bit write
	*(volatile u64*)(DENALI_CTL_36_DATA) = __cpu_to_le64((u64)DENALI_CTL_36_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_37_DATA) = __cpu_to_le64((u64)DENALI_CTL_37_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_38_DATA) = __cpu_to_le64((u64)DENALI_CTL_38_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_39_DATA) = __cpu_to_le64((u64)DENALI_CTL_39_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_40_DATA) = __cpu_to_le64((u64)DENALI_CTL_40_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_41_DATA) = __cpu_to_le64((u64)DENALI_CTL_41_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_42_DATA) = __cpu_to_le64((u64)DENALI_CTL_42_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_43_DATA) = __cpu_to_le64((u64)DENALI_CTL_43_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_44_DATA) = __cpu_to_le64((u64)DENALI_CTL_44_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_45_DATA) = __cpu_to_le64((u64)DENALI_CTL_45_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_46_DATA) = __cpu_to_le64((u64)DENALI_CTL_46_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_47_DATA) = __cpu_to_le64((u64)DENALI_CTL_47_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_48_DATA) = __cpu_to_le64((u64)DENALI_CTL_48_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_49_DATA) = __cpu_to_le64((u64)DENALI_CTL_49_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_50_DATA) = __cpu_to_le64((u64)DENALI_CTL_50_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_51_DATA) = __cpu_to_le64((u64)DENALI_CTL_51_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_52_DATA) = __cpu_to_le64((u64)DENALI_CTL_52_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_53_DATA) = __cpu_to_le64((u64)DENALI_CTL_53_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_54_DATA) = __cpu_to_le64((u64)DENALI_CTL_54_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_55_DATA) = __cpu_to_le64((u64)DENALI_CTL_55_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_56_DATA) = __cpu_to_le64((u64)DENALI_CTL_56_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_57_DATA) = __cpu_to_le64((u64)DENALI_CTL_57_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_58_DATA) = __cpu_to_le64((u64)DENALI_CTL_58_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_59_DATA) = __cpu_to_le64((u64)DENALI_CTL_59_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_60_DATA) = __cpu_to_le64((u64)DENALI_CTL_60_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_61_DATA) = __cpu_to_le64((u64)DENALI_CTL_61_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_62_DATA) = __cpu_to_le64((u64)DENALI_CTL_62_VAL_CFG1);
//	*(volatile u64*)(DENALI_CTL_63_DATA) = __cpu_to_le64((u64)DENALI_CTL_63_VAL_CFG1);
//	*(volatile u64*)(DENALI_CTL_64_DATA) = __cpu_to_le64((u64)DENALI_CTL_64_VAL_CFG1);
//	*(volatile u64*)(DENALI_CTL_65_DATA) = __cpu_to_le64((u64)DENALI_CTL_65_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_66_DATA) = __cpu_to_le64((u64)DENALI_CTL_66_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_67_DATA) = __cpu_to_le64((u64)DENALI_CTL_67_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_68_DATA) = __cpu_to_le64((u64)DENALI_CTL_68_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_69_DATA) = __cpu_to_le64((u64)DENALI_CTL_69_VAL_CFG1);

	// start DDRC
	*(volatile u64*)(DENALI_CTL_02_DATA) = __cpu_to_le64((u64)DENALI_CTL_02_VAL_CFG1 | (1LL << 32));
	//wait int_status[2] (DRAM init complete)
	while(( __le32_to_cpu(*(volatile u32*)(DENALI_CTL_36_DATA+4)) & 0x4) == 0);
//	*(volatile u64*)(DENALI_CTL_11_DATA) = __cpu_to_le64(((u64)DENALI_CTL_11_VAL_CFG1 & ~(0x00007F0000000000LL)) | (wr_dqs_shift << 40));

}

static void config_board2(void)
{
  // Configure DDR
	*(volatile u64*)(DENALI_CTL_00_DATA) = __cpu_to_le64((u64)DENALI_CTL_00_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_01_DATA) = __cpu_to_le64((u64)DENALI_CTL_01_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_02_DATA) = __cpu_to_le64((u64)DENALI_CTL_02_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_03_DATA) = __cpu_to_le64((u64)DENALI_CTL_03_VAL_CFG2);
//	*(volatile u64*)(DENALI_CTL_04_DATA) = __cpu_to_le64((u64)DENALI_CTL_04_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_05_DATA) = __cpu_to_le64((u64)DENALI_CTL_05_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_06_DATA) = __cpu_to_le64((u64)DENALI_CTL_06_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_07_DATA) = __cpu_to_le64((u64)DENALI_CTL_07_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_08_DATA) = __cpu_to_le64((u64)DENALI_CTL_08_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_09_DATA) = __cpu_to_le64((u64)DENALI_CTL_09_VAL_CFG2);
//	*(volatile u64*)(DENALI_CTL_10_DATA) = __cpu_to_le64((u64)DENALI_CTL_10_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_11_DATA) = __cpu_to_le64((u64)DENALI_CTL_11_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_12_DATA) = __cpu_to_le64((u64)DENALI_CTL_12_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_13_DATA) = __cpu_to_le64((u64)DENALI_CTL_13_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_14_DATA) = __cpu_to_le64((u64)DENALI_CTL_14_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_15_DATA) = __cpu_to_le64((u64)DENALI_CTL_15_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_16_DATA) = __cpu_to_le64((u64)DENALI_CTL_16_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_17_DATA) = __cpu_to_le64((u64)DENALI_CTL_17_VAL_CFG2);
#ifdef CFG_DDR_16BIT
	*(volatile u64*)(DENALI_CTL_18_DATA) = __cpu_to_le64((u64)DENALI_CTL_18_VAL_CFG2 | (1ULL << 24));
#else
	*(volatile u64*)(DENALI_CTL_18_DATA) = __cpu_to_le64((u64)DENALI_CTL_18_VAL_CFG2);
#endif
	*(volatile u64*)(DENALI_CTL_19_DATA) = __cpu_to_le64((u64)DENALI_CTL_19_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_20_DATA) = __cpu_to_le64((u64)DENALI_CTL_20_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_21_DATA) = __cpu_to_le64((u64)DENALI_CTL_21_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_22_DATA) = __cpu_to_le64((u64)DENALI_CTL_22_VAL_CFG2);
//	*(volatile u64*)(DENALI_CTL_23_DATA) = __cpu_to_le64((u64)DENALI_CTL_23_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_24_DATA) = __cpu_to_le64((u64)DENALI_CTL_24_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_25_DATA) = __cpu_to_le64((u64)DENALI_CTL_25_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_26_DATA) = __cpu_to_le64((u64)DENALI_CTL_26_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_27_DATA) = __cpu_to_le64((u64)DENALI_CTL_27_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_28_DATA) = __cpu_to_le64((u64)DENALI_CTL_28_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_29_DATA) = __cpu_to_le64((u64)DENALI_CTL_29_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_30_DATA) = __cpu_to_le64((u64)DENALI_CTL_30_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_31_DATA) = __cpu_to_le64((u64)DENALI_CTL_31_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_32_DATA) = __cpu_to_le64((u64)DENALI_CTL_32_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_33_DATA) = __cpu_to_le64((u64)DENALI_CTL_33_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_34_DATA) = __cpu_to_le64((u64)DENALI_CTL_34_VAL_CFG2);
//	*(volatile u64*)(DENALI_CTL_35_DATA) = __cpu_to_le64((u64)DENALI_CTL_35_VAL_CFG2);
	arm_write64(DENALI_CTL_35_VAL_CFG2,DENALI_CTL_35_DATA);//should be 64bit write
	*(volatile u64*)(DENALI_CTL_36_DATA) = __cpu_to_le64((u64)DENALI_CTL_36_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_37_DATA) = __cpu_to_le64((u64)DENALI_CTL_37_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_38_DATA) = __cpu_to_le64((u64)DENALI_CTL_38_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_39_DATA) = __cpu_to_le64((u64)DENALI_CTL_39_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_40_DATA) = __cpu_to_le64((u64)DENALI_CTL_40_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_41_DATA) = __cpu_to_le64((u64)DENALI_CTL_41_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_42_DATA) = __cpu_to_le64((u64)DENALI_CTL_42_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_43_DATA) = __cpu_to_le64((u64)DENALI_CTL_43_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_44_DATA) = __cpu_to_le64((u64)DENALI_CTL_44_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_45_DATA) = __cpu_to_le64((u64)DENALI_CTL_45_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_46_DATA) = __cpu_to_le64((u64)DENALI_CTL_46_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_47_DATA) = __cpu_to_le64((u64)DENALI_CTL_47_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_48_DATA) = __cpu_to_le64((u64)DENALI_CTL_48_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_49_DATA) = __cpu_to_le64((u64)DENALI_CTL_49_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_50_DATA) = __cpu_to_le64((u64)DENALI_CTL_50_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_51_DATA) = __cpu_to_le64((u64)DENALI_CTL_51_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_52_DATA) = __cpu_to_le64((u64)DENALI_CTL_52_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_53_DATA) = __cpu_to_le64((u64)DENALI_CTL_53_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_54_DATA) = __cpu_to_le64((u64)DENALI_CTL_54_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_55_DATA) = __cpu_to_le64((u64)DENALI_CTL_55_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_56_DATA) = __cpu_to_le64((u64)DENALI_CTL_56_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_57_DATA) = __cpu_to_le64((u64)DENALI_CTL_57_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_58_DATA) = __cpu_to_le64((u64)DENALI_CTL_58_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_59_DATA) = __cpu_to_le64((u64)DENALI_CTL_59_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_60_DATA) = __cpu_to_le64((u64)DENALI_CTL_60_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_61_DATA) = __cpu_to_le64((u64)DENALI_CTL_61_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_62_DATA) = __cpu_to_le64((u64)DENALI_CTL_62_VAL_CFG2);
//	*(volatile u64*)(DENALI_CTL_63_DATA) = __cpu_to_le64((u64)DENALI_CTL_63_VAL_CFG2);
//	*(volatile u64*)(DENALI_CTL_64_DATA) = __cpu_to_le64((u64)DENALI_CTL_64_VAL_CFG2);
//	*(volatile u64*)(DENALI_CTL_65_DATA) = __cpu_to_le64((u64)DENALI_CTL_65_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_66_DATA) = __cpu_to_le64((u64)DENALI_CTL_66_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_67_DATA) = __cpu_to_le64((u64)DENALI_CTL_67_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_68_DATA) = __cpu_to_le64((u64)DENALI_CTL_68_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_69_DATA) = __cpu_to_le64((u64)DENALI_CTL_69_VAL_CFG2);

	// start DDRC
	*(volatile u64*)(DENALI_CTL_02_DATA) = __cpu_to_le64((u64)DENALI_CTL_02_VAL_CFG2 | (1LL << 32));
	//wait int_status[2] (DRAM init complete)
	while(( __le32_to_cpu(*(volatile u32*)(DENALI_CTL_36_DATA+4)) & 0x4) == 0);
//	*(volatile u64*)(DENALI_CTL_11_DATA) = __cpu_to_le64(((u64)DENALI_CTL_11_VAL_CFG2 & ~(0x00007F0000000000LL)) | (wr_dqs_shift << 40));

}



void apply_ddr_setting(void)
{		
	switch (CFG_CLK) {
	default:
	case CFG_CLK_650_187_375:
	case CFG_CLK_534_178_330:
	case CFG_CLK_450_165_330:
	        config_board1();
		break;

	case CFG_CLK_650_200_200:
		config_board2();
		break;
	}
	
	/* training is required for 375MHz only,
         * but nice to have for 200MHz also */
#if defined(DDR_TRAINING)
		/* Do training */
		start_training();
#endif
}

u32 get_ddr_size(void)
{
	return PHYS_SDRAM_SIZE;
}


static void nor_hw_init(void)
{
// Reset the exp bus before configuring
	*(volatile u32 *)EX_SWRST_REG = __cpu_to_le32(0x1);
	while (*(volatile u32 *)EX_SWRST_REG) ;
// Set size
	*(volatile u32 *)EX_CS0_SEG_REG = __cpu_to_le32(0xFFF);
// Force NOR CS to 16 bits bus size (needed for recovery with u-boot_aram in some cases)
	*(volatile u32 *)EX_CS0_CFG_REG |= (__cpu_to_le32(CSx_CFG_BUS_SZ_16));
// AHB runs at 187.5MHz , and EXP at 31.25MHz
	*(volatile u32 *)EX_CLOCK_DIV_REG = __cpu_to_le32(0x6);
// Optimized settings
	*(volatile u32 *)EX_CS0_TMG1_REG = __cpu_to_le32(0x03034007);
        *(volatile u32 *)EX_CS0_TMG2_REG = __cpu_to_le32(0x04040502);
}

void bsp_init(void)
{
        /* If MAGIC Number is present, low level initialization is done 
 	*  in eeprom. Just return*/
        if(__le64_to_cpu(*(u64*)(ARAM_BASEADDR+0x10000))  == COMCERTO_PART_MAGIC)
                return;

	SoC_PLL_init(CFG_CLK);
	SoC_APB_setup();
	SoC_AHB_setup();
	SoC_ARAM_setup();

	icache_enable();

	//Apply DENALI DDR configuration
	apply_ddr_setting();
//	SoC_nand_init();
}

void nand_hw_init(void)
{
        SoC_gpio_cfg(29, GPIO_TYPE_OUTPUT);
        SoC_gpio_cfg(30, GPIO_TYPE_OUTPUT);
        SoC_gpio_cfg(31, GPIO_TYPE_OUTPUT);
        *(volatile u32 *) GPIO_PIN_SELECT_REG &= __cpu_to_le32(~((1 << 31)|(1 << 30)|(1 << 29)|(1 << 21)|(1 << 20)|(1 << 5)));
        *(volatile u32 *) GPIO_PIN_SELECT_REG |= __cpu_to_le32(1 << 6);
}

void i2c_hw_init(void)
{
        *(volatile u32 *) GPIO_PIN_SELECT_REG &= __cpu_to_le32(~((1 << 19)|(1 << 18)));
}

void spi_hw_init(void)
{
        *(volatile u32 *) GPIO_PIN_SELECT_REG &= __cpu_to_le32(~((1 << 27)|(1 << 26)|(1 << 25)|(1 << 24)|(1 << 13)|(1 << 12)));
}

#define ZYGPIO_TYPE_RESET           0
#define ZYGPIO_TYPE_LED_DEFAULT_ON  1
#define ZYGPIO_TYPE_LED_DEFAULT_OFF 2

void gpio_init(void)
{
	u32 gpios[][3] = {
		{ ZYGPIO_TYPE_LED_DEFAULT_OFF, 26 }, // LED Zwave
		{ ZYGPIO_TYPE_LED_DEFAULT_OFF, 16 }, // LED USB1
		{ ZYGPIO_TYPE_LED_DEFAULT_OFF, 15 }, // LED USB2
		{ ZYGPIO_TYPE_LED_DEFAULT_OFF, 17 }, // LED USB3
		{ ZYGPIO_TYPE_LED_DEFAULT_ON,  28 }, // LED Power
		{ ZYGPIO_TYPE_RESET, 8  }, // Reset USB
		{ ZYGPIO_TYPE_RESET, 9  }, // Reset PHY
		{ ZYGPIO_TYPE_RESET, 10 }, // Reset N Zwave
	};

	int i, gpio_size = sizeof(gpios)/sizeof(gpios[0]);

	for(i = 0; i < gpio_size; i++)
	{
		*(volatile u32 *) GPIO_PIN_SELECT_REG |= (1 << gpios[i][1]);
		SoC_gpio_cfg(gpios[i][1], GPIO_TYPE_OUTPUT);

		if(gpios[i][0] == ZYGPIO_TYPE_RESET || gpios[i][0] == ZYGPIO_TYPE_LED_DEFAULT_OFF)
		{
			SoC_gpio_set_1(SoC_gpio_mask(gpios[i][1]));
		}
	}

	udelay(2000);

	for(i = 0; i < gpio_size; i++)
	{
		if(gpios[i][0] == ZYGPIO_TYPE_RESET || gpios[i][0] == ZYGPIO_TYPE_LED_DEFAULT_ON)
		{
			SoC_gpio_set_0(SoC_gpio_mask(gpios[i][1]));
		}
	}

	udelay(2000);

	for(i = 0; i < gpio_size; i++)
	{
		if(gpios[i][0] == ZYGPIO_TYPE_RESET)
		{
			SoC_gpio_set_1(SoC_gpio_mask(gpios[i][1]));
		}
	}
}


int board_init(void)
{
	CFG_HZ_CLOCK = HAL_get_ahb_clk();

        /* Call nor_hw_init() only when low level initialization is not done */
        /* If MAGIC Number is present, low level initialization is done */
        if(__le64_to_cpu(*(u64*)(ARAM_BASEADDR+0x10000))  != COMCERTO_PART_MAGIC)
                nor_hw_init();

#ifdef CONFIG_CMD_NAND
	nand_hw_init();
#endif
	i2c_hw_init();

	spi_hw_init();

	/* Setup External reset*/
	SoC_gpio_cfg(17, GPIO_TYPE_OUTPUT);
	udelay(10);
	SoC_gpio_set_0(SoC_gpio_mask(17));
	udelay(10);
	SoC_gpio_set_1(SoC_gpio_mask(17));
	gpio_init();

	/* arch number of Mindspeed Comcerto */
	gd->bd->bi_arch_number = MACH_TYPE_M825XX;

	/* adress of boot parameters */
	gd->bd->bi_boot_params = LINUX_BOOTPARAM_ADDR;

        /* Enable ARM0 hardware support for non aligned accesses */
        *(volatile u32 *) GPIO_UP_ALIGN_ACCESS_LOGIC |= __cpu_to_le32(1);

	*(volatile u32 *) USB_PHY_CONF_REG = __cpu_to_le32(0x002D64C2);

	return 0;
}

int dram_init(void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_SIZE;

	return 0;
}

int misc_init_r(void)
{
	return 0;
}

#ifdef BOARD_LATE_INIT
int board_late_init(void)
{
#ifdef DDR_TRAINING_DBG
	u8 dll_adj0 = 0;
	u8 dll_adj1 = 0;
	u8 dll_adj2 = 0;
	u8 dll_adj3 = 0;
	u8 dqs_delay0 = 0;
	u8 dqs_delay1 = 0;
	u8 dqs_delay2 = 0;
	u8 dqs_delay3 = 0;
#endif

	printf("Reserve MSP memory\n");
	gd->bd->bi_dram[0].start += MSP_BOTTOM_MEMORY_RESERVED_SIZE;
	gd->bd->bi_dram[0].size -= MSP_BOTTOM_MEMORY_RESERVED_SIZE + MSP_TOP_MEMORY_RESERVED_SIZE;

#ifdef DDR_TRAINING_DBG
	dll_adj0 = DENALI_DLL_ADJ1_DS0_L;
	dll_adj1 = DENALI_DLL_ADJ1_DS1_H;
	dll_adj2 = DENALI_DLL_ADJ1_DS2_L;
	dll_adj3 = DENALI_DLL_ADJ1_DS3_H;
	dqs_delay0 = DENALI_WR_DQS_DELAY0;
	dqs_delay1 = DENALI_WR_DQS_DELAY1;
	dqs_delay2 = DENALI_WR_DQS_DELAY2;
	dqs_delay3 = DENALI_WR_DQS_DELAY3;

#ifdef DDR_TRAINING
	printf("DDR Training : ");
#else
	printf("DDR default settings : ");
#endif

	printf("\nDLL_ADJ(0,1,2,3): 0x%x,0x%x,0x%x,0x%x\n", dll_adj0,dll_adj1,dll_adj2,dll_adj3);
	printf("WR_DQS:delay0 0x%x, delay1 0x%x, delay2 0x%x, delay3 0x%x\n", dqs_delay0,dqs_delay1,dqs_delay2,dqs_delay3);

#endif
	return 0;
}

#endif
