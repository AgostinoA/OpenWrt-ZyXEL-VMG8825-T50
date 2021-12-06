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

#ifndef __CLOCK_INL
#define __CLOCK_INL

#ifdef __ASSEMBLY__

#include <config.h>
#include <asm/arcregs.h>
#include <asm/arch/platform.h>


/**********************************************************/

/* Please make sure that these registers are not touched by other startup code! */
#define RUBY_BUS_CLOCK_REG r23
#define RUBY_CPU_CLOCK_REG r24

.macro M_CLKSEL_ENTRY value constant
	cmp_s      RUBY_BUS_CLOCK_REG, RUBY_SYS_CTL_CLKSEL(\value)
	mov.z      RUBY_BUS_CLOCK_REG, \constant
	bz         read_done
.endm

.macro M_CLOCK_VAR name
	.align 4
	\name:
	.word 0
	.globl \name
.endm

.macro M_CLOCK_VARS
	/* Asm as well as C-code can use this variables to get bus and cpu freq */
	M_CLOCK_VAR ruby_bus_clk
	M_CLOCK_VAR ruby_cpu_clk
.endm

.macro M_CLOCK_SAVE
	/* Store bus freq */
	st         RUBY_BUS_CLOCK_REG, [ruby_bus_clk]
	/* Store cpu freq */
	st         RUBY_CPU_CLOCK_REG, [ruby_cpu_clk]
.endm

.macro M_CLOCK_READ
#if defined(RUBY_FIXED_CLK)
	/* Hard-coded value */
	mov        RUBY_BUS_CLOCK_REG, RUBY_FIXED_BUS_CLK
	mov        RUBY_CPU_CLOCK_REG, RUBY_FIXED_CPU_CLK
#elif defined(RUBY_READ_CLK)
	/* Load clock select bits */
	ld.di      RUBY_BUS_CLOCK_REG, [RUBY_SYS_CTL_CTRL]
	and        RUBY_BUS_CLOCK_REG, RUBY_BUS_CLOCK_REG, RUBY_SYS_CTL_MASK_CLKSEL

	/* Check clock select bits and choose bus freq */
	M_CLKSEL_ENTRY 0 RUBY_SYS_CTL_CLKSEL_00_BUS_FREQ
	M_CLKSEL_ENTRY 1 RUBY_SYS_CTL_CLKSEL_01_BUS_FREQ
	M_CLKSEL_ENTRY 2 RUBY_SYS_CTL_CLKSEL_10_BUS_FREQ
	M_CLKSEL_ENTRY 3 RUBY_SYS_CTL_CLKSEL_11_BUS_FREQ

	/* Ok, let's assign something */
	mov_s      RUBY_BUS_CLOCK_REG, 0

read_done:
	/* ASIC cpu freq is x2 bus freq */
	asl        RUBY_CPU_CLOCK_REG, RUBY_BUS_CLOCK_REG, 1
#else
	#error "Not supported"
#endif // #if defined(RUBY_FIXED_CLK)

.endm

#endif // #ifdef __ASSEMBLY__

#endif // #ifndef __CLOCK_INL

