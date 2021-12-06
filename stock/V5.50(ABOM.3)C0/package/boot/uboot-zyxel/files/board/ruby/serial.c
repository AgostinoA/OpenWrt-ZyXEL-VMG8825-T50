/*
 * (C) Copyright 2010 Quantenna Communications Inc.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include "ruby.h"

/*****************************************************************************/
/* Ruby UART is compatible with NS16550, but provide extra functionality.    */
/* Let's have our own implementation, not uboot's generic NS16550.           */
/*****************************************************************************/

static int initialized = 0;

inline static int serial_tx_ready(void)
{
	return (readb(RUBY_UART0_LSR) & RUBY_LSR_TX_Empty);
}

inline static int serial_rx_ready(void)
{
	return (readb(RUBY_UART0_LSR) & RUBY_LSR_RX_Ready);
}

inline static void serial_wait_tx(void)
{
	while (!serial_tx_ready());
}

inline static void serial_wait_rx(void)
{
	while (!serial_rx_ready());
}

inline static void serial_putc_simple(const char c)
{
	serial_wait_tx();
	writeb(c, RUBY_UART0_RBR_THR_DLL);
}

void serial_putc(const char c)
{
	if (initialized) {
		if (c == '\n') {
			serial_putc_simple('\r');
		}
		serial_putc_simple(c);
	}
}

int serial_getc(void)
{
	int ret = 'X';
	if (initialized) {
		serial_wait_rx();
		ret = readb(RUBY_UART0_RBR_THR_DLL);
	}
	return ret;
}

int serial_tstc(void)
{
	return initialized ? serial_rx_ready() : 0;
}

void serial_puts(const char *s)
{
	while (*s) {
		serial_putc(*s++);
	}
}

int serial_tx_done(void)
{
	return initialized ? (readb(RUBY_UART0_LSR) & RUBY_LSR_TX_Empty) : 1;
}

void serial_setbrg(void)
{
	DECLARE_GLOBAL_DATA_PTR;

	u32 baud_val = (gd->baudrate * 16);
	u32 div_val = (gd->bus_clk + baud_val / 2) / baud_val;
	u8 lcr_val =
		RUBY_LCR_Data_Word_Length_8 |
		RUBY_LCR_Stop_Bit_1 |
		RUBY_LCR_No_Parity |
		RUBY_LCR_Break_Disable;

	if (!(readb(RUBY_UART0_USR) & RUBY_USR_Busy)) {
		writeb(lcr_val | RUBY_LCR_DLAB, RUBY_UART0_LCR);
		writeb((div_val & 0xff), RUBY_UART0_RBR_THR_DLL);
		writeb((div_val >> 8) & 0xff, RUBY_UART0_DLH_IER);
		writeb(lcr_val, RUBY_UART0_LCR);
	}
}

int serial_init(void)
{
	return 0;
}

void board_serial_init(void)
{
	/* configure GPIOs */
	gpio_config(RUBY_GPIO_UART0_SO, RUBY_GPIO_ALT_OUTPUT);
	gpio_config(RUBY_GPIO_UART0_SI, RUBY_GPIO_ALT_INPUT);

	/* configure baud-rate */
	serial_setbrg();

	/* done */
	initialized = 1;
}

