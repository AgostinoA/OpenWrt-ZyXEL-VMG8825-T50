#ifndef __DDR_H__
#define __DDR_H__
/*
 * Copyright (c) 2010 Quantenna Communications, Inc.
 * All rights reserved.SYS_CTL_ODT_OFF
 *
 *  IRQ driver
 */


///////////////////////////////////////////////////////////////////////////////
//             Includes
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//             Defines
///////////////////////////////////////////////////////////////////////////////
#define BIT(x)    	(1L << (x))
//typedef unsigned long		u32;

#define DDR_BASE_ADDR               (0xf6000000)     
#define DDR_REG_CONTROL             (DDR_BASE_ADDR + 0x00)
#define DDR_REG_CONFIG              (DDR_BASE_ADDR + 0x04)
#define DDR_REG_HPR                 (DDR_BASE_ADDR + 0x08)
#define DDR_REG_LPR                 (DDR_BASE_ADDR + 0x0C)
#define DDR_REG_WR                  (DDR_BASE_ADDR + 0x10)
#define DDR_REG_DRAM_PARAM1         (DDR_BASE_ADDR + 0x14)
#define DDR_REG_DRAM_PARAM2         (DDR_BASE_ADDR + 0x18)
#define DDR_REG_DRAM_PARAM3         (DDR_BASE_ADDR + 0x1C)
#define DDR_REG_DRAM_PARAM4         (DDR_BASE_ADDR + 0x20)
#define DDR_REG_DRAM_PARAM5         (DDR_BASE_ADDR + 0x24)
#define DDR_REG_DRAM_INIT           (DDR_BASE_ADDR + 0x28)
#define DDR_REG_EMR                 (DDR_BASE_ADDR + 0x2C)
#define DDR_REG_MR                  (DDR_BASE_ADDR + 0x30)
#define DDR_MR_REDUCE_DRIVE		(BIT(17))
#define DDR_MR_ODT_75			(BIT(18))
#define DDR_MR_ODT_150			(BIT(22))
#define DDR_MR_ODT_50			(BIT(22) | BIT(18))

#define DDR_REG_BURST8              (DDR_BASE_ADDR + 0x34)
#define DDR_REG_DISABLE_DQ          (DDR_BASE_ADDR + 0x38)
#define DDR_REG_ADDR_MAP1           (DDR_BASE_ADDR + 0x3C)
#define DDR_REG_ADDR_MAP2           (DDR_BASE_ADDR + 0x40)
#define DDR_REG_ADDR_MAP3           (DDR_BASE_ADDR + 0x44)
#define DDR_REG_ODT                 (DDR_BASE_ADDR + 0x48)
#define DDR_REG_PHY_DEBUG           (DDR_BASE_ADDR + 0x4C)
#define DDR_REG_PHY_CMD             (DDR_BASE_ADDR + 0x50)
#define DDR_REG_STATUS              (DDR_BASE_ADDR + 0x54)
#define DDR_REG_DLL_CAL             (DDR_BASE_ADDR + 0x58)
#define DDR_REG_ODT_DELAY           (DDR_BASE_ADDR + 0x5C)
#define DDR_REG_CONTROLLER1         (DDR_BASE_ADDR + 0x60)
#define DDR_REG_CONTROLLER2         (DDR_BASE_ADDR + 0x64)
#define DDR_REG_WRITE_DLL1          (DDR_BASE_ADDR + 0x68)
#define DDR_REG_WRITE_DLL2          (DDR_BASE_ADDR + 0x6C)
#define DDR_REG_READ_DLL1           (DDR_BASE_ADDR + 0x70)
#define DDR_REG_READ_DLL2           (DDR_BASE_ADDR + 0x74)
#define DDR_REG_WRITE_RATIO         (DDR_BASE_ADDR + 0x78)
#define DDR_REG_READ_RATIO          (DDR_BASE_ADDR + 0x7C)
#define DDR_REG_DLL_STATUS0         (DDR_BASE_ADDR + 0x80)
#define DDR_REG_OF_STATUS0          (DDR_BASE_ADDR + 0x84)
#define DDR_REG_DLL_STATUS1         (DDR_BASE_ADDR + 0x88)
#define DDR_REG_OF_STATUS1          (DDR_BASE_ADDR + 0x8C)
#define DDR_REG_READ_STATUS0        (DDR_BASE_ADDR + 0x90)
#define DDR_REG_READ_STATUS1        (DDR_BASE_ADDR + 0x94)
#define DDR_REG_REFRESH             (DDR_BASE_ADDR + 0xA0)
#define DDR_REG_CHE1                (DDR_BASE_ADDR + 0xA4)
#define DDR_REG_CHE2                (DDR_BASE_ADDR + 0xA8)
#define DDR_REG_AHBID               (DDR_BASE_ADDR + 0x200)
#define DDR_REG_PAGE_MASK           (DDR_BASE_ADDR + 0x204)
#define DDR_REG_AHB_PRI0            (DDR_BASE_ADDR + 0x244)
#define DDR_REG_AHB_PRI1            (DDR_BASE_ADDR + 0x248)
#define DDR_REG_AHB_PRI2            (DDR_BASE_ADDR + 0x24C)
#define DDR_REG_AHB_PRI3            (DDR_BASE_ADDR + 0x250)
#define DDR_REG_AHB_PRI4            (DDR_BASE_ADDR + 0x254)

#define SYS_CTL_ADDR		(0xe0000000)
#define SYS_RST_MASK		(SYS_CTL_ADDR + 0x00)
#define SYS_RST_VEC 	    	(SYS_CTL_ADDR + 0x04)
#define SYS_CTL_MASK		(SYS_CTL_ADDR + 0x08)
#define SYS_CTL_VEC		(SYS_CTL_ADDR + 0x0c)
#define SYS_RST_LH  	 	(0x00000001)
#define SYS_RST_EBI 	 	(0x00000002)
#define SYS_RST_DRAM	 	(0x00000004)
#define SYS_RST_SRAM	 	(0x00000008)
#define SYS_CTL_ODT_MASK		(0x3 << 8)
#define SYS_CTL_ODT_OFF			(0x0 << 8)
#define SYS_CTL_ODT_75_OHM		(0x1 << 8)
#define SYS_CTL_ODT_150_OHM		(0x2 << 8)
#define SYS_CTL_DDR_DRIVE_MASK		(BIT(7))
#define SYS_CTL_DDR_DRIVE_HALF		(BIT(7))
#define SYS_CTL_DDR_DRIVE_FULL		(0)
#define REG_WRITE(x,y)  		(*(volatile u32 *)(x) = (u32)(y))
#define REG_READ(x)     		(*(volatile u32 *)(x))


int ddr_init(u32 mode,u32 speed,u32 size);
u32 ddr_size(void);

///////////////////////////////////////////////////////////////////////////////
//             Globals
///////////////////////////////////////////////////////////////////////////////

#endif //__DDR_H__
