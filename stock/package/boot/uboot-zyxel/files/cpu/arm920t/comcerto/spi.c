/*
 * (C) Copyright 2007
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
 *  Revision 0.3  2007/04/28 	Iurii.Golovach
 */

#include <common.h>
#ifdef CONFIG_CMD_SPI

#include <spi.h>
#include <asm/arch/bsp.h>
#include <asm/arch/spi.h>

spi_chipsel_type spi_chipsel[] = {
	(spi_chipsel_type)1,
	(spi_chipsel_type)2,
	(spi_chipsel_type)4,
	(spi_chipsel_type)8
};

int spi_chipsel_cnt = sizeof(spi_chipsel) / sizeof(spi_chipsel[0]);

void spi_hw_init(void)
{
	volatile u32 delay_count;

	/* enable native SPI (disabled by default) */	
	SoC_ioctrl_cfg(IOCTRL_SPI_BUS, 1);

	/* wait 2 ms SPI to process the data. DON'T REMOVE THIS OTHERWISE SPI WILL NOT BE INITIALIZED */
	delay_count = 4000;
	while (delay_count--)
		;
}

int  spi_xfer(spi_chipsel_type chipsel, int bitlen, uchar *dout, uchar *din)
{
	uchar j;
	u32 tsmode;

	if (bitlen < 1)
		return 1;

	/* checking the din and dout params */
	if (!din && !dout)
		return 2;

	if (!chipsel)
		return 3;

	if (!din) {
		/* transmit only */
		tsmode = 0x1;
	} else if (!dout) {
		/* receive only */
		tsmode = 0x2;
	} else {
		/* transmit & receive */
		tsmode = 0x0;
	}

	/* disable SPI */
	*(volatile u32 *) SPI_SSIENR = 0x0;

	/* select the target chip */
	*(volatile u32 *) SPI_SER = (volatile u32) *chipsel;

	*(volatile u32 *) SPI_CTRLR0 = (((tsmode & 0x3) << 8) |
					((CFG_SPI_CLOCK_POLARITY & 0x1) << 7) |
					((CFG_SPI_CLOCK_PHASE & 0x1) << 6) |
					((CFG_SPI_FRAMESIZE - 1) & 0xf));

	/* set up the ssi_clk divider value */
	*(volatile u32 *) SPI_BAUDR = (CFG_HZ_CLOCK / CFG_SPI_CLOCK_SPEED) & 0xFFFF;

	/* disable SPI interrupts */
	*(volatile u32 *) SPI_IMR = 0x0;

	/* enable SPI */
	*(volatile u32 *) SPI_SSIENR = 0x1;

	switch (tsmode) {
	case 0x1:
		/* transmit only */

		for (j = 0; j < bitlen / CFG_SPI_FRAMESIZE; j++) {
			/* transmit fifo not full */
			while(!((*(volatile u32 *) SPI_SR) & TFNF))
				;

			*(volatile u32 *) SPI_DR = *dout++;
		}

		/* waits while the data will be written (while TX FIFO isn't empty)  */
		while(!((*(volatile u32 *) SPI_SR) & TFE))
			;

		break;

	case 0x2:
		/* receive only */

		/* writing one dummy data word into the transmit FIFO */
		*(volatile u32 *)SPI_DR = 0x00;

		for (j = 0; j < bitlen / CFG_SPI_FRAMESIZE; j++)
		{
			/* check that there is data in the fifo */
			while(!((*(volatile u32 *) SPI_SR) & RFNE))
				;

			*din++ = *(volatile u32 *) SPI_DR;
		}

		break;

	default:
		/* transmit & receive */

		for (j = 0; j < bitlen / CFG_SPI_FRAMESIZE; j++) 
		{
			/* transmit fifo not full */
			while(!((*(volatile u32 *) SPI_SR) & TFNF))
				;

			*(volatile u32 *) SPI_DR = *dout++;

			/* check that there is data in the fifo */
			while(!((*(volatile u32 *) SPI_SR) & RFNE))
				;

			*din++ = *(volatile u32 *) SPI_DR;
		}

		/* waits while the data will be written (while TX FIFO isn't empty)  */
		while(!((*(volatile u32 *) SPI_SR) & TFE))
			;

		break;
	}

	return 0;
}
#endif /* (CONFIG_CMD_SPI) */
