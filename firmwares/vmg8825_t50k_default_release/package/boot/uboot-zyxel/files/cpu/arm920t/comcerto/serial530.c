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

#include <common.h>
#include <asm/arch/bsp.h>
#include <asm/hardware.h>

#if defined(CONFIG_UART0)

DECLARE_GLOBAL_DATA_PTR;

#define MCR_RXD_ENABLE		0x80
#define MCR_TXD_ENABLE		0x40
#define MCR_TIMER_SOURCE	0x20

#define LCR_WLEN8		0x03	/* Wordlength: 8 bits */

#define SSR_DR			0x01	/* Receiver data ready */
#define SSR_THRE		0x20	/* Transmit-hold-register empty */

#define FCR_TIMER_DIV_BYPASS	0x04

void serial_setbrg (void)
{
	int baudrate;
	unsigned int reg;
	unsigned int clk = SoC_clk_amba_get();

	if ((baudrate = gd->baudrate) <= 0)
		baudrate = CONFIG_BAUDRATE;

	reg = clk / (baudrate * 16);

	(*(volatile u8 *)UART_RXD) = 0x0F;
	(*(volatile u8 *)UART_TXD) = 0x0F;

	SoC_timer1_set(reg);
}

int serial_init (void)
{
	serial_setbrg ();

	(*(volatile u8 *)UART_FCR) = FCR_TIMER_DIV_BYPASS;
	(*(volatile u8 *)UART_MCR) = MCR_RXD_ENABLE | MCR_TXD_ENABLE | MCR_TIMER_SOURCE;
	(*(volatile u8 *)UART_LCR) = LCR_WLEN8;
	(*(volatile u8 *)UART_IER) = 0x00;

	return (0);
}

void serial_putc (const char c)
{
	/* wait for transmitter to empty */
	while (!((*(volatile u8 *)UART_SSR) & SSR_THRE)) ;

	(*(volatile u8 *)UART_THR) = c;

	if (c == '\n')
		serial_putc ('\r');
}

void serial_puts (const char *s)
{
	while (*s) {
		serial_putc (*s++);
	}
}

int serial_getc (void)
{
	while (!((*(volatile u8 *)UART_SSR) & SSR_DR)) ;

	return ((*(volatile u8 *)UART_RBR) & 0xff);
}

int serial_tstc (void)
{
	return ((*(volatile u8 *)UART_SSR) & SSR_DR);
}

#endif
