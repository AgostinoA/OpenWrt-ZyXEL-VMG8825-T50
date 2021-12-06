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
 *  Revision 1.2  2007/04/28 	Iurii.Golovach
 *  	the SR status register bits were added
 */

#ifndef _SPI_H
#define _SPI_H

/* SPI registers */
#define SPI_CTRLR0	(SPI_BASEADDR + 0x00)
#define SPI_CTRLR1	(SPI_BASEADDR + 0x04)
#define SPI_SSIENR	(SPI_BASEADDR + 0x08)
#define SPI_MWCR	(SPI_BASEADDR + 0x0c)
#define SPI_SER		(SPI_BASEADDR + 0x10)
#define SPI_BAUDR	(SPI_BASEADDR + 0x14)
#define SPI_TXFTLR	(SPI_BASEADDR + 0x18)
#define SPI_RXFTLR	(SPI_BASEADDR + 0x1c)
#define SPI_TXFLR	(SPI_BASEADDR + 0x20)
#define SPI_RXFLR	(SPI_BASEADDR + 0x24)
#define SPI_SR		(SPI_BASEADDR + 0x28)
#define SPI_IMR		(SPI_BASEADDR + 0x2c)
#define SPI_ISR		(SPI_BASEADDR + 0x30)
#define SPI_RISR	(SPI_BASEADDR + 0x34)
#define SPI_TXOICR	(SPI_BASEADDR + 0x38)
#define SPI_RXOICR	(SPI_BASEADDR + 0x3c)
#define SPI_RXUICR	(SPI_BASEADDR + 0x40)
#define SPI_MSTICR	(SPI_BASEADDR + 0x44)
#define SPI_ICR		(SPI_BASEADDR + 0x48)
#define SPI_IDR		(SPI_BASEADDR + 0x58)
#define SPI_DR		(SPI_BASEADDR + 0x60)

/* SR - status register bits */
#define BUSY		(1 << 0)	/* SSI busy flag, serial transfer in progress */
#define TFNF		(1 << 1)	/* Transmit FIFO not full */
#define TFE		(1 << 2)	/* Transmit FIFO empty */
#define RFNE		(1 << 3)	/* Receive FIFO not empty */
#define RFF		(1 << 4)	/* Receive FIFO full */
#define TXE		(1 << 5)	/* Transmission error */
#define DCOL		(1 << 6)	/* Data collision error */

#endif /* _SPI_H */
