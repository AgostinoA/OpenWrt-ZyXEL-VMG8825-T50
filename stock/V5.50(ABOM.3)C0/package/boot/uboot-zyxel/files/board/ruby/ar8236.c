/*
 *  board/ums/ar8236.c
 *
 *  U-Boot driver for the Atheros 8236 switch.
 *
 *  Copyright (c) Quantenna Communications Incorporated 2009.
 *  All rights reserved.
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

/********************************************************************
    Atheros 8236 MDIO programming details
    The Arasan MDIO IP on our chip uses two registers to program
    MDIO.
    
    data[16:0]
    control
    1   1111   1    00000   00000   
    5   4321   0    98765   43210
    -   ----   --   -----   -----
    st  xxxx   op   reg     phy
    
    st: 1 - start, poll for completion
    op: 1 - read, 0 write
    
    
    These are encoded into the serial MDIO protocol as follows
    
    IEEE MDIO frame
    33 22   22222   22211   11  1111110000000000
    10 98   76543   21098   76  5432109876543210
    -- --   -----   -----   --  ----------------
    ST OP   PHY     REG     TA  DATA[15:0]
    
    TA and ST are encoded automatically by Arasan IP.
    
    
    This device uses 18 bits to specify register addresses.
    These bits are programmed into the device by paging as follows.
    
    aaaaaaaaa   aaaaaaaa   aa
    111111111   00000000   00
    876543210   98765432   10
    ---------   --------   ------
    page addr   reg addr   ignore
    
    Since the registers are all 32-bit, the lower two address
    bits are discarded.  The page is written first using the
    following format.  Note PHY is limited to three bits.
    
    8213 Page program command
    -----------------------------------------------
    33  22  22   222  22211   11  111111 0000000000
    10  98  76   543  21098   76  543210 9876543210
    --  --  --   ---  -----   --  ------ ----------
    ST  OP  CMD  PHY  xxxxx   TA  xxxxxx page addr      
    
    CMD: 11 - page address write
    CMD: 10 - reg access
    
    The tricky part is the reg access step following page programming
    Since the register format of arasan swaps the order of reg and
    phy, and since our register address spans these two fields, we
    have to swizzle the bits into place.

    8213 Reg read/write command
    ------------------------------------------------
    33  22  22    2222221   1   11  1111110000000000
    10  98  76    5432109   8   76  5432109876543210
    --  --  --    -------   -   --  ----------------
    ST  OP  CMD   reg adr   W   TA  DATA[15:0]      
    
    W: 0 - lower 16 bits, 1: upper 16 bits
    
    Programming this operation into Arasan requires
    
    phy = 'b10 << 3 | regAddr[9:7]
    reg = regAddr[6:2]
    
    mdioCmd = phy | reg << 5 | op | start
    
    
********************************************************************/
////////////////////////////////////////////////////////////////////
// NOTE - we do not check for valid base in mdio access routines
// use must ensure device is initialized and valid prior
// to using MDIO funtions
///////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
//      Includes
////////////////////////////////////////////////////////////////////
#include <common.h>
#include <malloc.h>
#include <net.h>
#include <asm/io.h>
#include <asm/arch/platform.h>
#include <asm/arch/arasan_emac_ahb.h>
#include "ar8236.h"

////////////////////////////////////////////////////////////////////
//      Defines
////////////////////////////////////////////////////////////////////
#define AR8236_MODE_CTRL            (0x04)
#define AR8236_MODE_MII_PHY         (0x80000600)
#define AR8236_MODE_MII_MAC         (0x80000004)
#define AR8236_MASK_CTL             (0)
#define AR8236_MASK_CTL_RESET       (0x80000000)
#define AR8236_FLOOD_MASK           (0x2c)
#define AR8236_FLOOD_MASK_DEF       (0xfe7f007f)
#define AR8236_PORT0_CTRL           (0x100)
#define AR8236_PORT0_CTRL_DEF       (0x7d)
#define AR8236_FLOW_LINK_EN         (0x1000)

#define AR8236_MDIO_START           (1 << 15)
#define AR8236_MDIO_WRITE           (0 << 10)
#define AR8236_MDIO_READ            (1 << 10)
#define AR8236_MDIO_HIGH_WORD       (1 << 0)

#define AR8236_MDIO_TIMEOUT         (0x1000)
#define AR8236_MDIO_PAGE            (0x18)
#define AR8236_MDIO_NORM            (0x10)

#define AR8236_ARP_LEAKY_EN         (1 << 22)
#define AR8236_LEARN_EN             (1 << 14)
#define AR8236_FORWARD              (1 << 2)

#define AR8236_MIN_PHY_NUM          (0)
#define AR8236_MAX_PHY_NUM          (4)

////////////////////////////////////////////////////////////////////
//      Types
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
//      Data
////////////////////////////////////////////////////////////////////
static ts8236 g8236Dev;

////////////////////////////////////////////////////////////////////
//      Functions
////////////////////////////////////////////////////////////////////

inline u32 ar8236_emac_rdreg(int reg)
{
	return *(volatile u32 *)(g8236Dev.base + reg);
}

inline void ar8236_emac_wrreg(int reg, u32 val)
{
	*(volatile u32 *)(g8236Dev.base + reg) = val;
}

/*********************************************************************
 Name:      ar8236_mdio_poll
 Purpose:   mdio poll routine for AR8236 device
 Notes:     Checks for mdio operation complete
*********************************************************************/
int ar8236_mdio_poll(void)
{
	u32 timeout = AR8236_MDIO_TIMEOUT;

	// check for clear MDIO status
	while (timeout--) {
		int status = ar8236_emac_rdreg(EMAC_MAC_MDIO_CTRL);
		if ((status & AR8236_MDIO_START) == 0) {
			break;
		}
	}
	if (timeout == 0) {
		printf("ar8236 mdio timeout\n");
		return -1;
	}
	return 0;
}

/*********************************************************************
 Name:      ar8236_mdio_write
 Purpose:   mdio write routine for AR8236 device
 Notes:     This is a partial blocking call since we require
            more than one cycle to complete the write.
            checks for completion first
*********************************************************************/
int ar8236_mdio_write(u32 phyAddr, u32 regAddr, u32 data)
{
	u32 highAddr = regAddr >> 9;
	// need to swizzle the bits into arasan's fields which are different          
	u32 rg = (regAddr & 0x3c) >> 1;
	u32 ph = (regAddr & 0x1c0) >> 6;

	// check for clear MDIO status
	if (ar8236_mdio_poll() != 0) {
		return -1;
	}

	ar8236_emac_wrreg(EMAC_MAC_MDIO_DATA, highAddr);
	ar8236_emac_wrreg(EMAC_MAC_MDIO_CTRL, (phyAddr & 0x1f) |
			  AR8236_MDIO_START | AR8236_MDIO_PAGE);

	// wait for completion
	if (ar8236_mdio_poll() != 0) {
		return -1;
	}

	ar8236_emac_wrreg(EMAC_MAC_MDIO_DATA, (data >> 16) & 0xffff);
	ar8236_emac_wrreg(EMAC_MAC_MDIO_CTRL,
			  ((rg | AR8236_MDIO_HIGH_WORD) << 5) | ph |
			  AR8236_MDIO_START | AR8236_MDIO_NORM);
	if (ar8236_mdio_poll() != 0) {
		return -1;
	}

	ar8236_emac_wrreg(EMAC_MAC_MDIO_DATA, data & 0xffff);
	ar8236_emac_wrreg(EMAC_MAC_MDIO_CTRL,
			  (rg << 5) | ph | AR8236_MDIO_START |
			  AR8236_MDIO_NORM);
	if (ar8236_mdio_poll() != 0) {
		return -1;
	}

	// return without waiting for final completion
	return 0;
}

/*********************************************************************
 Name:      ar8236_mdio_read
 Purpose:   mdio read routine for AR8236 device
 Notes:     This is a blocking call since we require
            more than one cycle to complete the write.
            checks for completion first
*********************************************************************/
int ar8236_mdio_read(u32 phyAddr, u32 regAddr, u32 * data)
{
	u32 highAddr = regAddr >> 9;
	// need to swizzle the bits into arasan's fields which are different          
	u32 rg = (regAddr & 0x3c) >> 1;
	u32 ph = (regAddr & 0x1c0) >> 6;

	if (ar8236_mdio_poll() != 0) {
		return -1;
	}

	ar8236_emac_wrreg(EMAC_MAC_MDIO_DATA, highAddr);
	ar8236_emac_wrreg(EMAC_MAC_MDIO_CTRL, phyAddr | AR8236_MDIO_START |
			  AR8236_MDIO_PAGE);
	if (ar8236_mdio_poll() != 0) {
		return -1;
	}

	ar8236_emac_wrreg(EMAC_MAC_MDIO_CTRL, (rg << 5) | AR8236_MDIO_START |
			  AR8236_MDIO_READ | ph | AR8236_MDIO_NORM);
	if (ar8236_mdio_poll() != 0) {
		return -1;
	}

	*data = ar8236_emac_rdreg(EMAC_MAC_MDIO_DATA);

	ar8236_emac_wrreg(EMAC_MAC_MDIO_CTRL,
			  ((rg | AR8236_MDIO_HIGH_WORD) << 5) |
			  AR8236_MDIO_START | AR8236_MDIO_READ | ph |
			  AR8236_MDIO_NORM);
	if (ar8236_mdio_poll() != 0) {
		return -1;
	}

	*data = *data | (ar8236_emac_rdreg(EMAC_MAC_MDIO_DATA) << 16);
	return 0;
}

/*********************************************************************
 Name:      ar8236_init
 Purpose:   Check for Atheros 8236 switch, return pointer to device
            if found, NULL otherwise 
 Notes:     pass phy addr as -1 to scan for phy
*********************************************************************/
u32 ar8236_init(u32 baseAddr, u32 phy_addr)
{
	u32 addr;
	u32 devID;
	g8236Dev.base = baseAddr;

	// need to scan?
	if (phy_addr >=EMAC_PHY_ADDR_SCAN) {
		addr = AR8236_MIN_PHY_NUM;
	} else {
		if (phy_addr >= AR8236_MAX_PHY_NUM) {
			printf("config error: phy addr out of range\n");
			return EMAC_PHY_ADDR_SCAN;
		}
		addr = phy_addr;
	}

	while (addr <  AR8236_MAX_PHY_NUM) {
		int reset = AR8236_MASK_CTL_RESET;
		ar8236_mdio_read(addr, AR8236_MASK_CTL, &devID);
		if ((devID & 0xff00) == 0x300) {
			printf("Detected AR8236 Switch %d:%x - set for MII, 100FD\n",addr,devID);

			// do a softreset
			ar8236_mdio_write(phy_addr, AR8236_MODE_CTRL,
					  AR8236_MODE_MII_PHY);

			// do a clean reset and wait for completion 
			ar8236_mdio_write(phy_addr, AR8236_MASK_CTL,
					  AR8236_MASK_CTL_RESET);
			while (reset & AR8236_MASK_CTL_RESET) {
				ar8236_mdio_read(addr, AR8236_MASK_CTL, &reset);
			}
			ar8236_mdio_write(phy_addr, AR8236_FLOOD_MASK,
					  AR8236_FLOOD_MASK_DEF);
			ar8236_mdio_write(phy_addr, AR8236_PORT0_CTRL,
					  AR8236_PORT0_CTRL_DEF);
			g8236Dev.phy = addr;

			return addr;
		}
		if (phy_addr == MAX_PHY_ADDR) {
			addr++;
		} else {
			// not found on passed addr
			break;
		}
	}
	printf("Error: AR8236 not found\n");
	return EMAC_PHY_ADDR_SCAN;
}
