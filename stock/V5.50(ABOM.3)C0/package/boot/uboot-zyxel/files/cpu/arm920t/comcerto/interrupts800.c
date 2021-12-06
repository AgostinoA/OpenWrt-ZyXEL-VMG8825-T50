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


#define TIMER_LOAD_VAL		0xffffffff
#define CLOCK_COUNT_PER_USEC	(CONFIG_SYS_HZ_CLOCK / 1000 / 1000)
#define USEC_PER_TICK		(1000 * 1000 / CONFIG_SYS_HZ)

#define READ_TIMER SoC_timer0_get()


static ulong ts_count, ts_usec;
static ulong lastinc;

int interrupt_init (void)
{
	SoC_timer0_set(TIMER_LOAD_VAL);

	lastinc = 0;
	ts_count = 0;
	ts_usec = 0;

	return (0);
}

void reset_timer_masked (void)
{
	lastinc = READ_TIMER;
	ts_count = 0;
	ts_usec = 0;
}

void reset_timer (void)
{
	reset_timer_masked ();
}

/* Returns usecs since last timer reset */
ulong get_timer_raw (void)
{
	ulong step;
	ulong now = READ_TIMER;

	if (now > lastinc) {
		/* normal mode */
		step = now - lastinc;
	} else {
		/* we have an overflow ... */
		step = (TIMER_LOAD_VAL - lastinc) + now;
	}

	lastinc = now;

	ts_count += step % CLOCK_COUNT_PER_USEC;
	ts_usec += step / CLOCK_COUNT_PER_USEC;

	if (ts_count >= CLOCK_COUNT_PER_USEC) {
		ts_usec += ts_count / CLOCK_COUNT_PER_USEC;
		ts_count %= CLOCK_COUNT_PER_USEC;
	}

	return ts_usec;
}

/* Returns tick count since last timer reset */
ulong get_timer_masked (void)
{
	return get_timer_raw() / USEC_PER_TICK;
}

ulong get_timer (ulong base)
{
	return get_timer_masked () - base;
}

void udelay_masked (unsigned long usec)
{
	ulong endtime = get_timer_raw () + usec;

	while (get_timer_raw () < endtime)
		;

}

void udelay (unsigned long usec)
{
	udelay_masked(usec);
}

/*
 * This function is derived from PowerPC code (read timebase as long long).
 * On ARM it just returns the timer value.
 */
unsigned long long get_ticks(void)
{
	return get_timer(0);
}

/*
 * This function is derived from PowerPC code (timebase clock frequency).
 * On ARM it returns the number of timer ticks per second.
 */
ulong get_tbclk (void)
{
	ulong tbclk;

	tbclk = CONFIG_SYS_HZ;
	return tbclk;
}

/*
 *
 */
void reset_cpu (ulong ignored)
{
	while (1);
	/* Never reached */
}

/*
 * timer without interrupts
 */


void set_timer (ulong t)
{
	ts_count = 0;
	ts_usec = t * USEC_PER_TICK;
}
