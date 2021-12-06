/*
 * (C) Copyright 2006
 * Mindspeed Technologies, Inc. <www.mindspeed.com>
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
#include <config.h>
#include <common.h>
#include <asm/io.h>

#include <nand.h>
#include <asm/hardware.h>
#include <asm/arch/bsp.h>

/* 
 *	hardware specific access to control-lines
*/
static void comcerto_nand_hwcontrol(struct mtd_info *mtd, int cmd, unsigned int ctrl)
{
	struct nand_chip *this = mtd->priv;

	if (ctrl & NAND_CTRL_CHANGE) {
		if ( ctrl & NAND_CLE )
			SoC_gpio_set_1(SoC_gpio_mask(CFG_NAND_CLE_GPIO));
		else
			SoC_gpio_set_0(SoC_gpio_mask(CFG_NAND_CLE_GPIO));
		if ( ctrl & NAND_ALE )
			SoC_gpio_set_1(SoC_gpio_mask(CFG_NAND_ALE_GPIO));
		else
			SoC_gpio_set_0(SoC_gpio_mask(CFG_NAND_ALE_GPIO));
		if ( ctrl & NAND_NCE )
			SoC_gpio_set_0(SoC_gpio_mask(CFG_NAND_CE_GPIO));
		else
			SoC_gpio_set_1(SoC_gpio_mask(CFG_NAND_CE_GPIO));
	}

	if (cmd != NAND_CMD_NONE)
		writeb(cmd, this->IO_ADDR_W);
}

static int comcerto_nand_ready(struct mtd_info *mtd)
{
	return SoC_gpio_read(SoC_gpio_mask(CFG_NAND_BR_GPIO)) ? 1 : 0;
}

int board_nand_init(struct nand_chip *nand)
{
	printf("board_nand_init nand->IO_ADDR_R =%x\n", nand->IO_ADDR_R);

	nand->options = 0;
	nand->ecc.mode = NAND_ECC_SOFT;
	nand->cmd_ctrl = comcerto_nand_hwcontrol;
	nand->dev_ready = comcerto_nand_ready;
	nand->chip_delay = 20;
	return 0;
}
