/*
 * Copyright (c) 2009 Quantenna Communications, Inc.
 * All rights reserved.
 *
 *  Initialize DDR
 */

#include <shared_defs.h>
#include "ruby.h"
#include "ddr.h"

u32 ddr_size(void)
{
	unsigned long i, val,start,size;
	const unsigned long test_pattern = 0x12345678;
	volatile unsigned long *pmarker = (volatile unsigned long *)0;
 	printf("test ddr size\n");	
	start = 0x80000000;
	size = 0;
	*pmarker = ~test_pattern;
	
	/* Probe SDRAM to find out how much we have */
	if (*pmarker != ~test_pattern) {
		printf("No DDR detected\n");
		/* If running in SRAM do not flag no SDRAM as a fatal error */
		return 0;
	}
	
	for (i = 0x200000; i < 256 * 1024 * 1024; i <<= 1) {
		if (i < (unsigned long)pmarker) {
			/* Only start testing for memory address wraps
			 * above our current location.
			 */
			continue;
		}
		val = *(volatile unsigned long *)(i + (unsigned long)pmarker);
		*(volatile unsigned long *)(i + (unsigned long)pmarker) = test_pattern;
		if (*pmarker == test_pattern) {
			/* Writes have wrapped */
			size	 = i;
			break;
		}
		*(volatile unsigned long *)(i + (unsigned long)pmarker) = val;
	}
	if (size == 0) {
		printf("Cannot autodetect DDR size\n");
	} else {
		printf("DDR size %d MB\n",(int)size/(1024*1024));
	}
	return size;
}

int ddr_init(u32 type, u32 speed, u32 size)
{
	DECLARE_GLOBAL_DATA_PTR;
	//printf("ddr init %d %d\n",type,speed);
	REG_WRITE(SYS_RST_MASK,SYS_RST_DRAM);
	REG_WRITE(SYS_RST_VEC,SYS_RST_DRAM);

	REG_WRITE(DDR_REG_CONTROL,0x00000200);

	/*
	 * Micron is not supported in general, these tuned
	 * parameters will not work
	 */
	if ((type != DDR_16_MICRON) && (type != DDR_32_MICRON)) {
		switch (speed) {
			case DDR_400:
				REG_WRITE(SYS_CTL_MASK,0x7<<22);
				REG_WRITE(SYS_CTL_VEC,0x0<<22);
				REG_WRITE(DDR_REG_CONFIG,0x00081061);
				break;
			case DDR_320:
				REG_WRITE(SYS_CTL_MASK,0x7<<22);
				REG_WRITE(SYS_CTL_VEC,0x1<<22);
				REG_WRITE(DDR_REG_CONFIG,0x000fd04e);
				REG_WRITE(DDR_REG_PHY_CMD,0x00000289);
				REG_WRITE(DDR_REG_DRAM_PARAM1,0x00040614);
				REG_WRITE(DDR_REG_DRAM_PARAM2,0x03d5484f);
				REG_WRITE(DDR_REG_DRAM_PARAM3,0x14e14ca7);
				REG_WRITE(DDR_REG_MR,0x00220b52);
				REG_WRITE(DDR_REG_DRAM_PARAM4,0x2908528b);
				REG_WRITE(DDR_REG_DRAM_PARAM5,0x0000003c);
				REG_WRITE(DDR_REG_DRAM_INIT,0x008fd004);
				break;
			case DDR_250:
				REG_WRITE(SYS_CTL_MASK,0x7<<22);
				REG_WRITE(SYS_CTL_VEC,0x2<<22);
				REG_WRITE(DDR_REG_CONFIG,0x000fd03c);
				REG_WRITE(DDR_REG_PHY_CMD,0x00000267);
				REG_WRITE(DDR_REG_DRAM_PARAM1,0x000406cf);
				switch(size) {
				 case DDR_128MB:
					REG_WRITE(DDR_REG_DRAM_PARAM1,0x0004080c);
					break;
				 case DDR_64MB:
					REG_WRITE(DDR_REG_DRAM_PARAM1,0x000406cf);
					break;
				 case DDR_32MB:
				 default:
					REG_WRITE(DDR_REG_DRAM_PARAM1,0x000404cf);
				}
				REG_WRITE(DDR_REG_DRAM_PARAM2,0x0311484c);
				REG_WRITE(DDR_REG_DRAM_PARAM3,0x10a140a5);
				REG_WRITE(DDR_REG_MR,0x001e0942);
				REG_WRITE(DDR_REG_DRAM_PARAM4,0x2708426b);
				REG_WRITE(DDR_REG_DRAM_PARAM5,0x0000003c);
				REG_WRITE(DDR_REG_DRAM_INIT,0x008c5004);
				break;
			case DDR_200:
				REG_WRITE(SYS_CTL_MASK,0x7<<22);
				REG_WRITE(SYS_CTL_VEC,0x3<<22);
				REG_WRITE(DDR_REG_CONFIG,0x000fd030);
				REG_WRITE(DDR_REG_PHY_CMD,0x00000256);
				REG_WRITE(DDR_REG_DRAM_PARAM1,0x000403cc);
				REG_WRITE(DDR_REG_DRAM_PARAM2,0x024d484a);
				REG_WRITE(DDR_REG_DRAM_PARAM3,0x0c8124a4);
				REG_WRITE(DDR_REG_MR,0x00160742);
				REG_WRITE(DDR_REG_DRAM_PARAM4,0x2608324b);
				REG_WRITE(DDR_REG_DRAM_PARAM5,0x0000003c);
				REG_WRITE(DDR_REG_DRAM_INIT,0x008a1004);
				break;
			case DDR_160:
				REG_WRITE(SYS_CTL_MASK,0x7<<22);
				REG_WRITE(SYS_CTL_VEC,0x4<<22);
				REG_WRITE(DDR_REG_CONFIG,0x000fd027);
				REG_WRITE(DDR_REG_PHY_CMD,0x00000256);
				switch(size) {
				 case DDR_128MB:
					REG_WRITE(DDR_REG_DRAM_PARAM1,0x0004054a);
					break;
				 case DDR_64MB:
					REG_WRITE(DDR_REG_DRAM_PARAM1,0x0004044a);
					break;
				 case DDR_32MB:
				 default:
					REG_WRITE(DDR_REG_DRAM_PARAM1,0x0004030a);
				}
				REG_WRITE(DDR_REG_DRAM_PARAM2,0x020a484a);
				REG_WRITE(DDR_REG_DRAM_PARAM3,0x0c8124a4);
				REG_WRITE(DDR_REG_MR,0x00160742);
				REG_WRITE(DDR_REG_DRAM_PARAM4,0x2608324b);
				REG_WRITE(DDR_REG_DRAM_PARAM5,0x0000003c);
				REG_WRITE(DDR_REG_DRAM_INIT,0x00881004);
				break;
			default:
				return -1;
		}
	} else {
		/* Micron settings (not supported in general) */
		switch (speed) {
			case DDR_400:
				REG_WRITE(SYS_CTL_MASK,0x7<<22);
				REG_WRITE(SYS_CTL_VEC,0x0<<22);
				REG_WRITE(DDR_REG_CONFIG,0x00081061);
				break;
			case DDR_320:
				REG_WRITE(SYS_CTL_MASK,0x7<<22);
				REG_WRITE(SYS_CTL_VEC,0x1<<22);
				REG_WRITE(DDR_REG_CONFIG,0x0008104e);
				break;
			case DDR_250:
				REG_WRITE(SYS_CTL_MASK,0x7<<22);
				REG_WRITE(SYS_CTL_VEC,0x2<<22);
				REG_WRITE(DDR_REG_CONFIG,0x0008103c);
				switch(size) {
				 case DDR_128MB:
					REG_WRITE(DDR_REG_DRAM_PARAM1,0x0004080c);
					break;
				 case DDR_64MB:
					REG_WRITE(DDR_REG_DRAM_PARAM1,0x000406cf);
					break;
				 case DDR_32MB:
				 default:
					REG_WRITE(DDR_REG_DRAM_PARAM1,0x000404cf);
				}
				break;
			case DDR_200:
				REG_WRITE(SYS_CTL_MASK,0x7<<22);
				REG_WRITE(SYS_CTL_VEC,0x3<<22);
				REG_WRITE(DDR_REG_CONFIG,0x00081030);
				break;
			case DDR_160:
				REG_WRITE(SYS_CTL_MASK,0x7<<22);
				REG_WRITE(SYS_CTL_VEC,0x4<<22);
				REG_WRITE(DDR_REG_CONFIG,0x00081027);
				switch(size) {
				 case DDR_128MB:
					REG_WRITE(DDR_REG_DRAM_PARAM1,0x0004054a);
					break;
				 case DDR_64MB:
					REG_WRITE(DDR_REG_DRAM_PARAM1,0x0004044a);
					break;
				 case DDR_32MB:
				 default:
					REG_WRITE(DDR_REG_DRAM_PARAM1,0x0004030a);
				}
				break;
			default:
				return -1;
		}
		REG_WRITE(DDR_REG_MR,0x00020b42);
	}

	/* ODT off */
	REG_WRITE(SYS_CTL_MASK,SYS_CTL_ODT_MASK | SYS_CTL_DDR_DRIVE_MASK);
	REG_WRITE(SYS_CTL_VEC,SYS_CTL_ODT_OFF | SYS_CTL_DDR_DRIVE_HALF );

	REG_WRITE(DDR_REG_ODT,0x00000000);
	REG_WRITE(DDR_REG_EMR,0x00000000);
	REG_WRITE(DDR_REG_DLL_CAL,0x0001ffff);
	REG_WRITE(DDR_REG_CHE1,0x10300800);

if ((gd->bd->bi_board_id == QTN_RUBY_BRINGUP_BOARD_32_160_ARB) ||
	(gd->bd->bi_board_id == QTN_RUBY_BRINGUP_BOARD_32_160_ARB_1) ||
	(gd->bd->bi_board_id == QTN_RUBY_BRINGUP_BOARD_MICRON_DUALEMAC_MII) ||
	(gd->bd->bi_board_id == QTN_RUBY_BRINGUP_BOARD_MICRON_DUALEMAC_LOOPBACK) ||
	(gd->bd->bi_board_id == QTN_RUBY_OHS711_PCIE_320DDR)) {
	printf("DDR: use high priority reads\n");
	/* new ddr arb programming */
	REG_WRITE(DDR_REG_AHB_PRI0,0x000003ff);
	REG_WRITE(DDR_REG_AHB_PRI1,0x000003ff);
	REG_WRITE(DDR_REG_AHB_PRI2,0x000003ff);
	REG_WRITE(DDR_REG_AHB_PRI3,0x00080000);
	REG_WRITE(DDR_REG_AHB_PRI4,0x000003ff);
	REG_WRITE(DDR_REG_CONTROLLER1,0x00000070);
	REG_WRITE(DDR_REG_DISABLE_DQ,0x00000001);

} else {
	REG_WRITE(DDR_REG_AHB_PRI3,0x00000000);
}


	switch (type) {
		case DDR_16_MICRON:
			REG_WRITE(DDR_REG_WRITE_RATIO,0x00004343);
			REG_WRITE(DDR_REG_READ_RATIO,0x3c3c3c3c);
			REG_WRITE(DDR_REG_ADDR_MAP1,0x00000777);
			REG_WRITE(DDR_REG_ADDR_MAP2,0xfff00000);
			REG_WRITE(DDR_REG_ADDR_MAP3,0x0fff3333);
			REG_WRITE(DDR_REG_PAGE_MASK,0x03fff800);
			REG_WRITE(DDR_REG_CONTROL,0x00000205);
			break;
		case DDR_32_MICRON:
			REG_WRITE(DDR_REG_WRITE_RATIO,0x00004343);
			REG_WRITE(DDR_REG_READ_RATIO,0x3c3c3c3c);
			REG_WRITE(DDR_REG_ADDR_MAP1,0x00000777);
			REG_WRITE(DDR_REG_ADDR_MAP2,0xfff00000);
			REG_WRITE(DDR_REG_ADDR_MAP3,0x0fff3333);
			REG_WRITE(DDR_REG_PAGE_MASK,0x03fff800);
			REG_WRITE(DDR_REG_CONTROL,0x00000201);
			break;
		case DDR_16_ETRON:
			REG_WRITE(DDR_REG_WRITE_RATIO,0x00004343);
			REG_WRITE(DDR_REG_READ_RATIO,0x20202020);
			REG_WRITE(DDR_REG_ADDR_MAP1,0x00000f77);
			REG_WRITE(DDR_REG_ADDR_MAP2,0xfff00000);
			REG_WRITE(DDR_REG_ADDR_MAP3,0x0fff2222);
			REG_WRITE(DDR_REG_PAGE_MASK,0x03fff800);
			REG_WRITE(DDR_REG_CONTROL,0x00000205);
			break;
		case DDR_32_ETRON:
			REG_WRITE(DDR_REG_WRITE_RATIO,0x00004343);
			REG_WRITE(DDR_REG_READ_RATIO,0x20202020);
			REG_WRITE(DDR_REG_ADDR_MAP1,0x00000f77);
			REG_WRITE(DDR_REG_ADDR_MAP2,0xfff00000);
			REG_WRITE(DDR_REG_ADDR_MAP3,0x0fff2222);
			REG_WRITE(DDR_REG_PAGE_MASK,0x03fff800);
			REG_WRITE(DDR_REG_CONTROL,0x00000201);
			break;
		case DDR_16_SAMSUNG:
			REG_WRITE(DDR_REG_WRITE_RATIO,0x00004343);
			REG_WRITE(DDR_REG_READ_RATIO,0x20202020);
			REG_WRITE(DDR_REG_ADDR_MAP2,0xfff00000);

			if (size == DDR_128MB) {
				REG_WRITE(DDR_REG_DRAM_PARAM1,0x0004054a);
				REG_WRITE(DDR_REG_ADDR_MAP1,0x00000777);
				REG_WRITE(DDR_REG_ADDR_MAP3,0x0fff3333);
			} else {
				REG_WRITE(DDR_REG_ADDR_MAP1,0x00000f77);
				REG_WRITE(DDR_REG_ADDR_MAP3,0x0fff2222);
			}

			REG_WRITE(DDR_REG_PAGE_MASK,0x03fff800);
			REG_WRITE(DDR_REG_CONTROL,0x00000205);
			break;
		default:
			return -1;
	}
	return 0;
}
