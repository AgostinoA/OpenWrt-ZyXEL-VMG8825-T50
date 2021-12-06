#ifndef __AR8237_h__
#define __AR8237_h__
/*
 *  board/ums/ar8237.h
 *
 *  U-Boot driver for the Atheros 8237 switch.
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

////////////////////////////////////////////////////////////////////
// NOTE - we do not check for valid base in mdio access routines
// use must ensure device is initialized and valid prior
// to using MDIO funtions
///////////////////////////////////////////////////////////////////

typedef struct {
    u32 base;
    u32 phy;
}ts8237,*pts8237;

#define MAX_PHY_ADDR 32
/*********************************************************************
 Name:      ar8237_init
 Purpose:   Check for Atheros 8237 switch, return pointer to device
            if found, NULL otherwise 
 Notes:     pass phy addr as -1 to scan for phy
*********************************************************************/
u32 ar8237_init(u32 baseAddr, u32 phy_addr);

/*********************************************************************
 Name:      ar8237_mdio_read
 Purpose:   mdio read routine for AR8237 device
 Notes:     This is a blocking call since we require
            more than one cycle to complete the write.
            checks for completion first
*********************************************************************/
int ar8237_mdio_read(u32 phyAddr, u32 regAddr, u32 *data);

/*********************************************************************
 Name:      ar8237_mdio_write
 Purpose:   mdio write routine for AR8237 device
 Notes:     This is a partial blocking call since we require
            more than one cycle to complete the write.
            checks for completion first
*********************************************************************/
int ar8237_mdio_write(u32 phyAddr, u32 regAddr, u32 data);

/*********************************************************************
 Name:      ar8237_mdio_poll
 Purpose:   mdio poll routine for AR8237 device
 Notes:     Checks for mdio operation complete
*********************************************************************/
int ar8237_mdio_poll(void);

#endif // __AR8237_h__
