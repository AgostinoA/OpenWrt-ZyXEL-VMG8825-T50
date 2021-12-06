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

#ifdef CONFIG_CMD_UC

extern volatile unsigned long uc_trace_num;
extern volatile unsigned long uc_trace_done;

UC_TEXT_SECTION
void UC_NAME(_serial_putc_simple)(const char c)
{
	while (!(readb(RUBY_UART0_LSR) & RUBY_LSR_TX_Empty));
	writeb(c, RUBY_UART0_RBR_THR_DLL);
}

UC_TEXT_SECTION
void UC_NAME(_serial_putc)(const char c)
{
	if (c == '\n') {
		UC_NAME(_serial_putc_simple('\r'));
	}
	UC_NAME(_serial_putc_simple(c));
}

UC_TEXT_SECTION
void UC_NAME(_serial_puts)(const char *s)
{
	while (*s) {
		UC_NAME(_serial_putc)(*s++);
	}
}

UC_TEXT_SECTION
void UC_NAME(_entry_func)(void)
{
	int i;

	++uc_trace_num;

	for (i = 0; i < 30; ++i) {
		UC_NAME(_serial_puts)(UC_PROMPT": hello world ");
		UC_NAME(_serial_putc)(i + '0');
		UC_NAME(_serial_putc)('\n');
		++uc_trace_num;
	}
	UC_NAME(_serial_puts)("DONE!\n");
}

#endif // #ifdef CONFIG_CMD_UC

