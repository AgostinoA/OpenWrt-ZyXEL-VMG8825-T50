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

static inline void board_reset_watchdog(unsigned long delay)
{
	writel(RUBY_WDT_ENABLE, RUBY_WDT_CTL);
	writel(delay, RUBY_WDT_TIMEOUT_RANGE);
	writel(RUBY_WDT_MAGIC_NUMBER, RUBY_WDT_COUNTER_RESTART);
}

static inline void board_reset_sysctrl(unsigned long mask)
{
	writel(mask, RUBY_SYS_CTL_CPU_VEC_MASK);
	writel(0x0, RUBY_SYS_CTL_CPU_VEC);
	writel(0x0, RUBY_SYS_CTL_CPU_VEC_MASK);
}

void board_reset(const char *reason)
{
	/* Postponed reset using watchdog - make sure that serial output will take place and be finished. */
	board_reset_watchdog(RUBY_WDT_RESET_TIMEOUT);

	/* Serial output. */
	puts(reason);
	while(!serial_tx_done());

	/* Force reset. */
	board_reset_sysctrl(RUBY_SYS_CTL_RESET_ALL);

	/* Board must be resetted before this point! */
	while(1);
}

int do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	board_reset("reset command\n");
	return 0;
}

