/*
 * Copyright (C) 2007 Mindspeed Technologies Inc.
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

static void config_board1(void);
static void config_board2(void);
static void config_board3(void);
static void config_board4(void);
static void config_board5(void);
static void config_board6(void);
static void config_board7(void);
static void config_board8(void);
static void config_board9(void);
static void config_board10(void);

void SoC_Check_Device(void)
{
	// This should run on a M821xx SoC, let's check it
	u32 devicetype = __le32_to_cpu((*(volatile u32*)(GPIO_DEVID_REG)) & __cpu_to_le32(0xFFFF));

	if (devicetype != 0x150)
	{
		//error wrong device
		// TODO: what should we do?
	}
}

void SoC_APB_setup(void)
{
	// Setting APB Bus Wait states to 1, set post write
	(*(volatile u32*)(APB_ACCESS_WS_REG)) = __cpu_to_le32(0x40);
	
}

void SoC_ARAM_setup(void)
{
	// disable pipeline mode in ARAM 
        (*(volatile u32*)(MEMCORE_BASEADDR+0x18)) = __cpu_to_le32(1);
}


void SoC_AHB_setup(void)
{
	// enable all 6 masters for ARAM
        (*(volatile u32*)(ASA_ARAM_TC_CR_REG)) = __cpu_to_le32(ASA_TC_REQIDMAEN |  ASA_TC_REQTDMEN |ASA_TC_REQIPSECUSBEN |ASA_TC_REQARM0EN | ASA_TC_REQARM1EN |ASA_TC_REQMDMAEN);
	// enable all 6 masters for EBUS
	(*(volatile u32*)(ASA_EBUS_TC_CR_REG)) = __cpu_to_le32(ASA_TC_REQIDMAEN |  ASA_TC_REQTDMEN |ASA_TC_REQIPSECUSBEN |ASA_TC_REQARM0EN | ASA_TC_REQARM1EN |ASA_TC_REQMDMAEN);

}


void SoC_PLL_init(void)
{
	HAL_set_amba_clk(CFG_HZ_CLOCK);
	HAL_set_arm_clk(CFG_ARM_CLOCK);

	// set PUI
	*(volatile u32*)(CLKCORE_CLKDIV_CNTRL) &= __cpu_to_le32(~(0x1F << PUI_CLKDIV_RATIO_SHIFT));
	*(volatile u32*)(CLKCORE_CLKDIV_CNTRL) |= __cpu_to_le32(((CFG_ARM_CLOCK / 25000000) << PUI_CLKDIV_RATIO_SHIFT));
	*(volatile u32*)(CLKCORE_CLKDIV_CNTRL) &= __cpu_to_le32(~PUI_CLKDIV_BYPASS);	

	// set pci divider and switch to ref clk
//	*(volatile u32*)(CLKCORE_CLKDIV_CNTRL) &= ~(0x1F << PCI_CLKDIV_RATIO_SHIFT);/
//	*(volatile u32*)(CLKCORE_CLKDIV_CNTRL) |= ((CFG_HZ_CLOCK / 33000000) << PCI_CLKDIV_RATIO_SHIFT);
//	*(volatile u32*)(CLKCORE_CLKDIV_CNTRL) &= ~PCI_CLKDIV_BYPASS;	
}

static void apply_ddr_setting(u32 board_config)
{
	u8 do_training = 0;

	switch (board_config) {
	case BOARD_CFG_1:
		config_board1();
		break;
	case BOARD_CFG_2:
	    	config_board2();
		break;
	case BOARD_CFG_3:
	    	config_board3();
		break;
	case BOARD_CFG_4:
	    	config_board4();
		do_training = 1;
		break;
	case BOARD_CFG_5:
		config_board5();
		do_training = 1;
		break;
	case BOARD_CFG_6:
	    	config_board6();
		break;
	case BOARD_CFG_7:
	    	config_board7();
		break;
	case BOARD_CFG_8:
	    	config_board8();
		break;
	case BOARD_CFG_9:
		config_board9(); /* Packet IAD C50 */
		do_training = 1;
		break;
	case BOARD_CFG_10:
		config_board10(); /* Router C50 */
		break;
	}

#ifdef DDR_TRAINING
	if (do_training)
		start_training();  /* training to find optimal ODT values (run from L1 cache) */
#endif
}


void SoC_mem_init(u32 board_config)
{
	volatile u32 delay_count;
	u32 ddr_size;

	// Get the right amount of DDR the board is populated with
	ddr_size = get_ddr_size();
	// Memory setup register
	*(volatile u32*)(MEMORY_MAX_ADDR) = __cpu_to_le32((ddr_size - 1) + MEMORY_BASE_ADDR);
	// disbale ROM remap
	*(volatile u32*)(MEMORY_CR) = __cpu_to_le32(0);
	
	// Take DDR controller out of reset
	*(volatile u32*)(BLOCK_RESET_REG) |= __cpu_to_le32(DDR_RST);
	// 20 ops delay
	delay_count = 20;
	while(delay_count--);

	//Apply DENALI DDR configuration according to the board 
	apply_ddr_setting(board_config);
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

static void config_board1(void)
{
	u64 wr_dqs_shift = 0x40;

	*(volatile u64*)(DENALI_CTL_00_DATA) =  __cpu_to_le64((u64)DENALI_CTL_00_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_01_DATA) =  __cpu_to_le64((u64)DENALI_CTL_01_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_02_DATA) =  __cpu_to_le64((u64)DENALI_CTL_02_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_03_DATA) =  __cpu_to_le64((u64)DENALI_CTL_03_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_04_DATA) =  __cpu_to_le64((u64)DENALI_CTL_04_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_05_DATA) =  __cpu_to_le64((u64)DENALI_CTL_05_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_06_DATA) =  __cpu_to_le64((u64)DENALI_CTL_06_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_07_DATA) =  __cpu_to_le64((u64)DENALI_CTL_07_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_08_DATA) =  __cpu_to_le64((u64)DENALI_CTL_08_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_09_DATA) =  __cpu_to_le64((u64)DENALI_CTL_09_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_10_DATA) =  __cpu_to_le64((u64)DENALI_CTL_10_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_11_DATA) =  __cpu_to_le64((u64)DENALI_CTL_11_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_12_DATA) =  __cpu_to_le64((u64)DENALI_CTL_12_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_13_DATA) =  __cpu_to_le64((u64)DENALI_CTL_13_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_14_DATA) =  __cpu_to_le64((u64)DENALI_CTL_14_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_15_DATA) =  __cpu_to_le64((u64)DENALI_CTL_15_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_16_DATA) =  __cpu_to_le64((u64)DENALI_CTL_16_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_17_DATA) =  __cpu_to_le64((u64)DENALI_CTL_17_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_18_DATA) =  __cpu_to_le64((u64)DENALI_CTL_18_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_19_DATA) =  __cpu_to_le64((u64)DENALI_CTL_19_VAL_CFG1);
	*(volatile u64*)(DENALI_CTL_20_DATA) =  __cpu_to_le64((u64)DENALI_CTL_20_VAL_CFG1);
	
	// start DDRC
	*(volatile u64*)(DENALI_CTL_02_DATA) =  __cpu_to_le64((u64)DENALI_CTL_02_VAL_CFG1 | (1LL << 32));
	//wait int_status[2] (DRAM init complete)
	while(( *(volatile u32*)(DENALI_CTL_08_DATA+4) & __cpu_to_le32(0x040000)) == 0);

	*(volatile u64*)(DENALI_CTL_11_DATA) =  __cpu_to_le64(((u64)DENALI_CTL_11_VAL_CFG1 & ~(0x00007F0000000000LL)) | (wr_dqs_shift << 40));

}


static void config_board2(void)
{
	u64 wr_dqs_shift = 0x40;

	*(volatile u64*)(DENALI_CTL_00_DATA) = __cpu_to_le64((u64)DENALI_CTL_00_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_01_DATA) = __cpu_to_le64((u64)DENALI_CTL_01_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_02_DATA) = __cpu_to_le64((u64)DENALI_CTL_02_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_03_DATA) = __cpu_to_le64((u64)DENALI_CTL_03_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_04_DATA) = __cpu_to_le64((u64)DENALI_CTL_04_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_05_DATA) = __cpu_to_le64((u64)DENALI_CTL_05_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_06_DATA) = __cpu_to_le64((u64)DENALI_CTL_06_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_07_DATA) = __cpu_to_le64((u64)DENALI_CTL_07_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_08_DATA) = __cpu_to_le64((u64)DENALI_CTL_08_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_09_DATA) = __cpu_to_le64((u64)DENALI_CTL_09_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_10_DATA) = __cpu_to_le64((u64)DENALI_CTL_10_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_11_DATA) = __cpu_to_le64((u64)DENALI_CTL_11_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_12_DATA) = __cpu_to_le64((u64)DENALI_CTL_12_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_13_DATA) = __cpu_to_le64((u64)DENALI_CTL_13_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_14_DATA) = __cpu_to_le64((u64)DENALI_CTL_14_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_15_DATA) = __cpu_to_le64((u64)DENALI_CTL_15_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_16_DATA) = __cpu_to_le64((u64)DENALI_CTL_16_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_17_DATA) = __cpu_to_le64((u64)DENALI_CTL_17_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_18_DATA) = __cpu_to_le64((u64)DENALI_CTL_18_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_19_DATA) = __cpu_to_le64((u64)DENALI_CTL_19_VAL_CFG2);
	*(volatile u64*)(DENALI_CTL_20_DATA) = __cpu_to_le64((u64)DENALI_CTL_20_VAL_CFG2);
	
	// start DDRC
	*(volatile u64*)(DENALI_CTL_02_DATA) = __cpu_to_le64((u64)DENALI_CTL_02_VAL_CFG2 | (1LL << 32));
	//wait int_status[2] (DRAM init complete)
	while(( *(volatile u32*)(DENALI_CTL_08_DATA+4) & __cpu_to_le32(0x040000)) == 0);

	*(volatile u64*)(DENALI_CTL_11_DATA) = __cpu_to_le64(((u64)DENALI_CTL_11_VAL_CFG2 & ~(0x00007F0000000000LL)) | (wr_dqs_shift << 40));

}


static void config_board3(void)
{
	u64 wr_dqs_shift = 0x40;

	*(volatile u64*)(DENALI_CTL_00_DATA) = __cpu_to_le64((u64)DENALI_CTL_00_VAL_CFG3);
	*(volatile u64*)(DENALI_CTL_01_DATA) = __cpu_to_le64((u64)DENALI_CTL_01_VAL_CFG3);
	*(volatile u64*)(DENALI_CTL_02_DATA) = __cpu_to_le64((u64)DENALI_CTL_02_VAL_CFG3);
	*(volatile u64*)(DENALI_CTL_03_DATA) = __cpu_to_le64((u64)DENALI_CTL_03_VAL_CFG3);
	*(volatile u64*)(DENALI_CTL_04_DATA) = __cpu_to_le64((u64)DENALI_CTL_04_VAL_CFG3);
	*(volatile u64*)(DENALI_CTL_05_DATA) = __cpu_to_le64((u64)DENALI_CTL_05_VAL_CFG3);
	*(volatile u64*)(DENALI_CTL_06_DATA) = __cpu_to_le64((u64)DENALI_CTL_06_VAL_CFG3);
	*(volatile u64*)(DENALI_CTL_07_DATA) = __cpu_to_le64((u64)DENALI_CTL_07_VAL_CFG3);
	*(volatile u64*)(DENALI_CTL_08_DATA) = __cpu_to_le64((u64)DENALI_CTL_08_VAL_CFG3);
	*(volatile u64*)(DENALI_CTL_09_DATA) = __cpu_to_le64((u64)DENALI_CTL_09_VAL_CFG3);
	*(volatile u64*)(DENALI_CTL_10_DATA) = __cpu_to_le64((u64)DENALI_CTL_10_VAL_CFG3);
	*(volatile u64*)(DENALI_CTL_11_DATA) = __cpu_to_le64((u64)DENALI_CTL_11_VAL_CFG3);
	*(volatile u64*)(DENALI_CTL_12_DATA) = __cpu_to_le64((u64)DENALI_CTL_12_VAL_CFG3);
	*(volatile u64*)(DENALI_CTL_13_DATA) = __cpu_to_le64((u64)DENALI_CTL_13_VAL_CFG3);
	*(volatile u64*)(DENALI_CTL_14_DATA) = __cpu_to_le64((u64)DENALI_CTL_14_VAL_CFG3);
	*(volatile u64*)(DENALI_CTL_15_DATA) = __cpu_to_le64((u64)DENALI_CTL_15_VAL_CFG3);
	*(volatile u64*)(DENALI_CTL_16_DATA) = __cpu_to_le64((u64)DENALI_CTL_16_VAL_CFG3);
	*(volatile u64*)(DENALI_CTL_17_DATA) = __cpu_to_le64((u64)DENALI_CTL_17_VAL_CFG3);
	*(volatile u64*)(DENALI_CTL_18_DATA) = __cpu_to_le64((u64)DENALI_CTL_18_VAL_CFG3);
	*(volatile u64*)(DENALI_CTL_19_DATA) = __cpu_to_le64((u64)DENALI_CTL_19_VAL_CFG3);
	*(volatile u64*)(DENALI_CTL_20_DATA) = __cpu_to_le64((u64)DENALI_CTL_20_VAL_CFG3);
	
	// start DDRC
	*(volatile u64*)(DENALI_CTL_02_DATA) = __cpu_to_le64((u64)DENALI_CTL_02_VAL_CFG3 | (1LL << 32));
	//wait int_status[2] (DRAM init complete)
	while(( *(volatile u32*)(DENALI_CTL_08_DATA+4) & __cpu_to_le32(0x040000)) == 0);

	*(volatile u64*)(DENALI_CTL_11_DATA) = __cpu_to_le64(((u64)DENALI_CTL_11_VAL_CFG3 & ~(0x00007F0000000000LL)) | (wr_dqs_shift << 40));

}

static void config_board4(void)
{
	u64 wr_dqs_shift = 0x40;

	*(volatile u64*)(DENALI_CTL_00_DATA) = __cpu_to_le64((u64)DENALI_CTL_00_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_01_DATA) = __cpu_to_le64((u64)DENALI_CTL_01_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_02_DATA) = __cpu_to_le64((u64)DENALI_CTL_02_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_03_DATA) = __cpu_to_le64((u64)DENALI_CTL_03_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_04_DATA) = __cpu_to_le64((u64)DENALI_CTL_04_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_05_DATA) = __cpu_to_le64((u64)DENALI_CTL_05_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_06_DATA) = __cpu_to_le64((u64)DENALI_CTL_06_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_07_DATA) = __cpu_to_le64((u64)DENALI_CTL_07_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_08_DATA) = __cpu_to_le64((u64)DENALI_CTL_08_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_09_DATA) = __cpu_to_le64((u64)DENALI_CTL_09_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_10_DATA) = __cpu_to_le64((u64)DENALI_CTL_10_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_11_DATA) = __cpu_to_le64((u64)DENALI_CTL_11_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_12_DATA) = __cpu_to_le64((u64)DENALI_CTL_12_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_13_DATA) = __cpu_to_le64((u64)DENALI_CTL_13_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_14_DATA) = __cpu_to_le64((u64)DENALI_CTL_14_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_15_DATA) = __cpu_to_le64((u64)DENALI_CTL_15_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_16_DATA) = __cpu_to_le64((u64)DENALI_CTL_16_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_17_DATA) = __cpu_to_le64((u64)DENALI_CTL_17_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_18_DATA) = __cpu_to_le64((u64)DENALI_CTL_18_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_19_DATA) = __cpu_to_le64((u64)DENALI_CTL_19_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_20_DATA) = __cpu_to_le64((u64)DENALI_CTL_20_VAL_CFG4);
	
	// start DDRC
	*(volatile u64*)(DENALI_CTL_02_DATA) = __cpu_to_le64((u64)DENALI_CTL_02_VAL_CFG4 | (1LL << 32));
	//wait int_status[2] (DRAM init complete)
	while(( *(volatile u32*)(DENALI_CTL_08_DATA+4) & __cpu_to_le32(0x040000)) == 0);

	*(volatile u64*)(DENALI_CTL_11_DATA) = __cpu_to_le64(((u64)DENALI_CTL_11_VAL_CFG4 & ~(0x00007F0000000000LL)) | (wr_dqs_shift << 40));

}


static void config_board5(void)
{
	u64 wr_dqs_shift = 0x40;

	*(volatile u64*)(DENALI_CTL_00_DATA) = __cpu_to_le64((u64)DENALI_CTL_00_VAL_CFG5);
	*(volatile u64*)(DENALI_CTL_01_DATA) = __cpu_to_le64((u64)DENALI_CTL_01_VAL_CFG5);
	*(volatile u64*)(DENALI_CTL_02_DATA) = __cpu_to_le64((u64)DENALI_CTL_02_VAL_CFG5);
	*(volatile u64*)(DENALI_CTL_03_DATA) = __cpu_to_le64((u64)DENALI_CTL_03_VAL_CFG5);
	*(volatile u64*)(DENALI_CTL_04_DATA) = __cpu_to_le64((u64)DENALI_CTL_04_VAL_CFG5);
	*(volatile u64*)(DENALI_CTL_05_DATA) = __cpu_to_le64((u64)DENALI_CTL_05_VAL_CFG5);
	*(volatile u64*)(DENALI_CTL_06_DATA) = __cpu_to_le64((u64)DENALI_CTL_06_VAL_CFG5);
	*(volatile u64*)(DENALI_CTL_07_DATA) = __cpu_to_le64((u64)DENALI_CTL_07_VAL_CFG5);
	*(volatile u64*)(DENALI_CTL_08_DATA) = __cpu_to_le64((u64)DENALI_CTL_08_VAL_CFG5);
	*(volatile u64*)(DENALI_CTL_09_DATA) = __cpu_to_le64((u64)DENALI_CTL_09_VAL_CFG5);
	*(volatile u64*)(DENALI_CTL_10_DATA) = __cpu_to_le64((u64)DENALI_CTL_10_VAL_CFG5);
	*(volatile u64*)(DENALI_CTL_11_DATA) = __cpu_to_le64((u64)DENALI_CTL_11_VAL_CFG5);
	*(volatile u64*)(DENALI_CTL_12_DATA) = __cpu_to_le64((u64)DENALI_CTL_12_VAL_CFG5);
	*(volatile u64*)(DENALI_CTL_13_DATA) = __cpu_to_le64((u64)DENALI_CTL_13_VAL_CFG5);
	*(volatile u64*)(DENALI_CTL_14_DATA) = __cpu_to_le64((u64)DENALI_CTL_14_VAL_CFG5);
	*(volatile u64*)(DENALI_CTL_15_DATA) = __cpu_to_le64((u64)DENALI_CTL_15_VAL_CFG5);
	*(volatile u64*)(DENALI_CTL_16_DATA) = __cpu_to_le64((u64)DENALI_CTL_16_VAL_CFG5);
	*(volatile u64*)(DENALI_CTL_17_DATA) = __cpu_to_le64((u64)DENALI_CTL_17_VAL_CFG5);
	*(volatile u64*)(DENALI_CTL_18_DATA) = __cpu_to_le64((u64)DENALI_CTL_18_VAL_CFG5);
	*(volatile u64*)(DENALI_CTL_19_DATA) = __cpu_to_le64((u64)DENALI_CTL_19_VAL_CFG5);
	*(volatile u64*)(DENALI_CTL_20_DATA) = __cpu_to_le64((u64)DENALI_CTL_20_VAL_CFG5);
	
	// start DDRC
	*(volatile u64*)(DENALI_CTL_02_DATA) = __cpu_to_le64((u64)DENALI_CTL_02_VAL_CFG5 | (1LL << 32));
	//wait int_status[2] (DRAM init complete)
	while(( *(volatile u32*)(DENALI_CTL_08_DATA+4) & __cpu_to_le32(0x040000)) == 0);

	*(volatile u64*)(DENALI_CTL_11_DATA) = __cpu_to_le64(((u64)DENALI_CTL_11_VAL_CFG5 & ~(0x00007F0000000000LL)) | (wr_dqs_shift << 40));

}

static void config_board6(void)
{
	u64 wr_dqs_shift = 0x40;

	*(volatile u64*)(DENALI_CTL_00_DATA) = __cpu_to_le64((u64)DENALI_CTL_00_VAL_CFG6);
	*(volatile u64*)(DENALI_CTL_01_DATA) = __cpu_to_le64((u64)DENALI_CTL_01_VAL_CFG6);
	*(volatile u64*)(DENALI_CTL_02_DATA) = __cpu_to_le64((u64)DENALI_CTL_02_VAL_CFG6);
	*(volatile u64*)(DENALI_CTL_03_DATA) = __cpu_to_le64((u64)DENALI_CTL_03_VAL_CFG6);
	*(volatile u64*)(DENALI_CTL_04_DATA) = __cpu_to_le64((u64)DENALI_CTL_04_VAL_CFG6);
	*(volatile u64*)(DENALI_CTL_05_DATA) = __cpu_to_le64((u64)DENALI_CTL_05_VAL_CFG6);
	*(volatile u64*)(DENALI_CTL_06_DATA) = __cpu_to_le64((u64)DENALI_CTL_06_VAL_CFG6);
	*(volatile u64*)(DENALI_CTL_07_DATA) = __cpu_to_le64((u64)DENALI_CTL_07_VAL_CFG6);
	*(volatile u64*)(DENALI_CTL_08_DATA) = __cpu_to_le64((u64)DENALI_CTL_08_VAL_CFG6);
	*(volatile u64*)(DENALI_CTL_09_DATA) = __cpu_to_le64((u64)DENALI_CTL_09_VAL_CFG6);
	*(volatile u64*)(DENALI_CTL_10_DATA) = __cpu_to_le64((u64)DENALI_CTL_10_VAL_CFG6);
	*(volatile u64*)(DENALI_CTL_11_DATA) = __cpu_to_le64((u64)DENALI_CTL_11_VAL_CFG6);
	*(volatile u64*)(DENALI_CTL_12_DATA) = __cpu_to_le64((u64)DENALI_CTL_12_VAL_CFG6);
	*(volatile u64*)(DENALI_CTL_13_DATA) = __cpu_to_le64((u64)DENALI_CTL_13_VAL_CFG6);
	*(volatile u64*)(DENALI_CTL_14_DATA) = __cpu_to_le64((u64)DENALI_CTL_14_VAL_CFG6);
	*(volatile u64*)(DENALI_CTL_15_DATA) = __cpu_to_le64((u64)DENALI_CTL_15_VAL_CFG6);
	*(volatile u64*)(DENALI_CTL_16_DATA) = __cpu_to_le64((u64)DENALI_CTL_16_VAL_CFG6);
	*(volatile u64*)(DENALI_CTL_17_DATA) = __cpu_to_le64((u64)DENALI_CTL_17_VAL_CFG6);
	*(volatile u64*)(DENALI_CTL_18_DATA) = __cpu_to_le64((u64)DENALI_CTL_18_VAL_CFG6);
	*(volatile u64*)(DENALI_CTL_19_DATA) = __cpu_to_le64((u64)DENALI_CTL_19_VAL_CFG6);
	*(volatile u64*)(DENALI_CTL_20_DATA) = __cpu_to_le64((u64)DENALI_CTL_20_VAL_CFG6);
	
	// start DDRC
	*(volatile u64*)(DENALI_CTL_02_DATA) = __cpu_to_le64((u64)DENALI_CTL_02_VAL_CFG6 | (1LL << 32));
	//wait int_status[2] (DRAM init complete)
	while(( *(volatile u32*)(DENALI_CTL_08_DATA+4) & __cpu_to_le32(0x040000)) == 0);

	*(volatile u64*)(DENALI_CTL_11_DATA) = __cpu_to_le64(((u64)DENALI_CTL_11_VAL_CFG6 & ~(0x00007F0000000000LL)) | (wr_dqs_shift << 40));

}

static void config_board7(void)
{
	config_board5();    /* config 7 is same as config 5 */
}

static void config_board8(void)
{
    /* Dali MoCA EVMs have same memory subsystem as PacketIAD EVM */
    config_board4();
}


/* Similar to Config #4 (Packet IAD) */
static void config_board9(void)
{
	u64 wr_dqs_shift = 0x40;

	*(volatile u64*)(DENALI_CTL_00_DATA) = __cpu_to_le64((u64)DENALI_CTL_00_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_01_DATA) = __cpu_to_le64((u64)DENALI_CTL_01_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_02_DATA) = __cpu_to_le64((u64)DENALI_CTL_02_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_03_DATA) = __cpu_to_le64((u64)DENALI_CTL_03_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_04_DATA) = __cpu_to_le64((u64)DENALI_CTL_04_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_05_DATA) = __cpu_to_le64((u64)DENALI_CTL_05_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_06_DATA) = __cpu_to_le64((u64)DENALI_CTL_06_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_07_DATA) = __cpu_to_le64((u64)DENALI_CTL_07_VAL_CFG4_C50);
	*(volatile u64*)(DENALI_CTL_08_DATA) = __cpu_to_le64((u64)DENALI_CTL_08_VAL_CFG4_C50);
	*(volatile u64*)(DENALI_CTL_09_DATA) = __cpu_to_le64((u64)DENALI_CTL_09_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_10_DATA) = __cpu_to_le64((u64)DENALI_CTL_10_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_11_DATA) = __cpu_to_le64((u64)DENALI_CTL_11_VAL_CFG4_C50);
	*(volatile u64*)(DENALI_CTL_12_DATA) = __cpu_to_le64((u64)DENALI_CTL_12_VAL_CFG4_C50);
	*(volatile u64*)(DENALI_CTL_13_DATA) = __cpu_to_le64((u64)DENALI_CTL_13_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_14_DATA) = __cpu_to_le64((u64)DENALI_CTL_14_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_15_DATA) = __cpu_to_le64((u64)DENALI_CTL_15_VAL_CFG4_C50);
	*(volatile u64*)(DENALI_CTL_16_DATA) = __cpu_to_le64((u64)DENALI_CTL_16_VAL_CFG4_C50);
	*(volatile u64*)(DENALI_CTL_17_DATA) = __cpu_to_le64((u64)DENALI_CTL_17_VAL_CFG4);
	*(volatile u64*)(DENALI_CTL_18_DATA) = __cpu_to_le64((u64)DENALI_CTL_18_VAL_CFG4_C50);
	*(volatile u64*)(DENALI_CTL_19_DATA) = __cpu_to_le64((u64)DENALI_CTL_19_VAL_CFG4_C50);
	*(volatile u64*)(DENALI_CTL_20_DATA) = __cpu_to_le64((u64)DENALI_CTL_20_VAL_CFG4_C50);
	
	// start DDRC
	*(volatile u64*)(DENALI_CTL_02_DATA) = __cpu_to_le64((u64)DENALI_CTL_02_VAL_CFG4 | (1LL << 32));
	//wait int_status[2] (DRAM init complete)
	while(( *(volatile u32*)(DENALI_CTL_08_DATA+4) & __cpu_to_le32(0x040000)) == 0);

	*(volatile u64*)(DENALI_CTL_11_DATA) = __cpu_to_le64(((u64)DENALI_CTL_11_VAL_CFG4_C50 & ~(0x00007F0000000000LL)) | (wr_dqs_shift << 40));

}

/* Board cfg 10 is defined for C50 Router EVM */
static void config_board10(void)
{
        u64 wr_dqs_shift = 0x40;

        *(volatile u64*)(DENALI_CTL_00_DATA) = __cpu_to_le64((u64)DENALI_CTL_00_VAL_CFG10);
        *(volatile u64*)(DENALI_CTL_01_DATA) = __cpu_to_le64((u64)DENALI_CTL_01_VAL_CFG10);
        *(volatile u64*)(DENALI_CTL_02_DATA) = __cpu_to_le64((u64)DENALI_CTL_02_VAL_CFG10);
        *(volatile u64*)(DENALI_CTL_03_DATA) = __cpu_to_le64((u64)DENALI_CTL_03_VAL_CFG10);
        *(volatile u64*)(DENALI_CTL_04_DATA) = __cpu_to_le64((u64)DENALI_CTL_04_VAL_CFG10);
        *(volatile u64*)(DENALI_CTL_05_DATA) = __cpu_to_le64((u64)DENALI_CTL_05_VAL_CFG10);
        *(volatile u64*)(DENALI_CTL_06_DATA) = __cpu_to_le64((u64)DENALI_CTL_06_VAL_CFG10);
        *(volatile u64*)(DENALI_CTL_07_DATA) = __cpu_to_le64((u64)DENALI_CTL_07_VAL_CFG10);
        *(volatile u64*)(DENALI_CTL_08_DATA) = __cpu_to_le64((u64)DENALI_CTL_08_VAL_CFG10);
        *(volatile u64*)(DENALI_CTL_09_DATA) = __cpu_to_le64((u64)DENALI_CTL_09_VAL_CFG10);
        *(volatile u64*)(DENALI_CTL_10_DATA) = __cpu_to_le64((u64)DENALI_CTL_10_VAL_CFG10);
        *(volatile u64*)(DENALI_CTL_11_DATA) = __cpu_to_le64((u64)DENALI_CTL_11_VAL_CFG10);
        *(volatile u64*)(DENALI_CTL_12_DATA) = __cpu_to_le64((u64)DENALI_CTL_12_VAL_CFG10);
        *(volatile u64*)(DENALI_CTL_13_DATA) = __cpu_to_le64((u64)DENALI_CTL_13_VAL_CFG10);
        *(volatile u64*)(DENALI_CTL_14_DATA) = __cpu_to_le64((u64)DENALI_CTL_14_VAL_CFG10);
        *(volatile u64*)(DENALI_CTL_15_DATA) = __cpu_to_le64((u64)DENALI_CTL_15_VAL_CFG10);
        *(volatile u64*)(DENALI_CTL_16_DATA) = __cpu_to_le64((u64)DENALI_CTL_16_VAL_CFG10);
        *(volatile u64*)(DENALI_CTL_17_DATA) = __cpu_to_le64((u64)DENALI_CTL_17_VAL_CFG10);
        *(volatile u64*)(DENALI_CTL_18_DATA) = __cpu_to_le64((u64)DENALI_CTL_18_VAL_CFG10);
        *(volatile u64*)(DENALI_CTL_19_DATA) = __cpu_to_le64((u64)DENALI_CTL_19_VAL_CFG10);
        *(volatile u64*)(DENALI_CTL_20_DATA) = __cpu_to_le64((u64)DENALI_CTL_20_VAL_CFG10);

        // start DDRC
        *(volatile u64*)(DENALI_CTL_02_DATA) = __cpu_to_le64((u64)DENALI_CTL_02_VAL_CFG10 | (1LL << 32));
        //wait int_status[2] (DRAM init complete)
        while(( *(volatile u32*)(DENALI_CTL_08_DATA+4) & __cpu_to_le32(0x040000)) == 0);
        
 	*(volatile u64*)(DENALI_CTL_11_DATA) = __cpu_to_le64(((u64)DENALI_CTL_11_VAL_CFG10 & ~(0x00007F0000000000LL)) | (wr_dqs_shift << 40));

}

