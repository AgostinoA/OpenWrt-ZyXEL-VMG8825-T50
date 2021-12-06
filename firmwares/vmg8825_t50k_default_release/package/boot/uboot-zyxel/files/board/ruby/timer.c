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

#define TIMER_NO_IN_USE			0x0
#define TIMER_MAX_VALUE			0xFFFFFFFF

#define TIMER_TICK_PER_SYS_TICK		(gd->bus_clk / CONFIG_SYS_HZ)
#define TIMER_TICK_PER_USEC(usec)	(gd->bus_clk * (usec) / 1000000)
#define TIMER_MAX_USEC_PER_ITER()	(0xFFFFFFFF / gd->bus_clk)

/* Monotonic incrementing timer */
static unsigned long long timestamp = 0;

static inline ulong read_timer(void)
{
	return ((TIMER_MAX_VALUE - readl(RUBY_TIMER_VALUE(TIMER_NO_IN_USE))));
}

static unsigned long long tick(void)
{
	/* Internal tick units. Last snapshot. */
	static ulong last_tick = 0;

	ulong now = read_timer();
	if (now >= last_tick) {
		/* normal mode */
		timestamp += now - last_tick;
	} else {
		/* we have an overflow ... */
		timestamp += now + TIMER_MAX_VALUE - last_tick;
	}
	last_tick = now;

	return timestamp;
}

static void setup_timer(ulong val)
{
	writel(0, RUBY_TIMER_CONTROL(TIMER_NO_IN_USE));
	writel(TIMER_MAX_VALUE - val, RUBY_TIMER_LOAD_COUNT(TIMER_NO_IN_USE));
	writel(RUBY_TIMER_ENABLE, RUBY_TIMER_CONTROL(TIMER_NO_IN_USE));
}

ulong get_timer(ulong base)
{
	DECLARE_GLOBAL_DATA_PTR;
	return tick() / TIMER_TICK_PER_SYS_TICK - base;
}

void udelay(unsigned long usec)
{
	DECLARE_GLOBAL_DATA_PTR;

	const unsigned long usec_per_iter = TIMER_MAX_USEC_PER_ITER();
	const unsigned long tick_per_iter = TIMER_TICK_PER_USEC(usec_per_iter);
	const unsigned long remain_tick = TIMER_TICK_PER_USEC(usec % usec_per_iter);

	while(usec) {

		unsigned long long future = tick();

		if (usec < usec_per_iter) {
			future += remain_tick;
			usec = 0;
		} else {
			future += tick_per_iter;
			usec -= usec_per_iter;
		}

		while(tick() < future);
	}
}

void reset_timer(void)
{
	set_timer(0);
}

void set_timer(ulong t)
{
	timestamp = t;
	setup_timer(t);
}

void board_timer_init(void)
{
	reset_timer();
}

