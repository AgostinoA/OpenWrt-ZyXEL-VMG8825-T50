/*
 * (C) Copyright Mindspeed Technologies Inc.
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
#include <config.h>
#include <asm/arch/hardware.h>

void reset_emac0_phy(u32 enable)
{
}

void reset_emac1_phy(u32 enable)
{
}

#if defined(CONFIG_GPHY_AR8035_DELAY_TUNING)
#define AR8035_DEBUG_ADDR 0x1d
#define AR8035_DEBUG_DATA 0x1e

#define AR8035_DEBUG_ADDR_RX_DELAY_CTL 0x00
#define AR8035_DEBUG_ADDR_TX_DELAY_CTL 0x05

#define AR8035_DEBUG_DATA_RX_DELAY 0x8000
#define AR8035_DEBUG_DATA_TX_DELAY 0x0100

#define SET_PHY_TX_DELAY(devname, addr, enabled) _set_phy_reg_debug_data(devname, addr, AR8035_DEBUG_ADDR_TX_DELAY_CTL, AR8035_DEBUG_DATA_TX_DELAY, enabled)
#define SET_PHY_RX_DELAY(devname, addr, enabled) _set_phy_reg_debug_data(devname, addr, AR8035_DEBUG_ADDR_RX_DELAY_CTL, AR8035_DEBUG_DATA_RX_DELAY, enabled)

static int _set_phy_reg_debug_data(char *devname, unsigned char addr, unsigned char reg, unsigned short setting, int enabled)
{
	unsigned short data = 0xffff;

	if(0 == miiphy_write(devname, addr, AR8035_DEBUG_ADDR, reg)) {
		if(0 == miiphy_read(devname, addr, AR8035_DEBUG_DATA, &data)) {
			if(enabled) {
				data |= setting;
			}
			else {
				data ^= setting;
			}

			if(0 == miiphy_write(devname, addr, AR8035_DEBUG_DATA, data)) {
				return 0;
			}
		}
	}

	return -1;
}

void config_emac_phy_delay(int phy_addr)
{
	char *gemac0_devname = "comcerto_gemac0";
	char *gemac1_devname = "comcerto_gemac1";

	switch(phy_addr)
	{
		case GEMAC0_PHY_ADDR :
			SET_PHY_TX_DELAY(gemac0_devname, GEMAC0_PHY_ADDR, 1);
			SET_PHY_RX_DELAY(gemac0_devname, GEMAC0_PHY_ADDR, 1);
			break;

		case GEMAC1_PHY_ADDR :

			SET_PHY_TX_DELAY(gemac1_devname, GEMAC1_PHY_ADDR, 1);
			SET_PHY_RX_DELAY(gemac1_devname, GEMAC1_PHY_ADDR, 1);
			break;

		default :
			break;
	}
}
#endif
