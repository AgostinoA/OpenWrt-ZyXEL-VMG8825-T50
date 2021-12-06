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

#ifndef __START_INL
#define __START_INL

#ifdef __ASSEMBLY__

#include <config.h>
#include <asm/arch/platform.h>

.macro FLUSH_CACHE
	/* flush d-cache */
	mov_s	r0, 0x1
	sr	r0, [ARC_REG_DC_FLSH]
1:
	lr      r1, [ARC_REG_DC_CTRL]
	and     r1, r1, ARC_DC_FLUSH_STATUS_BIT
	brne    r1, 0x0, 1b
	/* invalidate i-cache */
	mov_s	r0, 0x1
	sr	r0, [ARC_REG_IC_IVIC]
	lr      r1, [ARC_REG_DC_CTRL]
.endm

.macro M_COPY_UBOOT to_addr from_addr
	mov_s	r1, \to_addr
	mov_s	r2, \from_addr
	mov_s	r3, \to_addr + __bss_start - TEXT_BASE
1:
	ld.ab	r0, [r2, 4]
	st.ab	r0, [r1, 4]
	brlt	r1, r3, 1b
	FLUSH_CACHE
.endm

.macro M_DELAY_US us
	mov_s	r1, RUBY_FIXED_CPU_CLK
	mov_s	r2, \us
	mpy	r1, r2, r1
	lsr	r1, r1, 20 /* divide by 1024*1024, which is approximately 1000000 */
1:	
	sub.f	r1, r1, 1
	bne	1b
.endm


.macro M_FILL_BSS
	/* Clear bss */
	mov_s	r2, __bss_start
	mov_s	r3, __bss_end
1:
	st.ab	0, [r2, 4]
	brlt	r2, r3, 1b
.endm

.macro M_GOTO_C_CODE
	/* setup stack pointer */
	mov	sp, CONFIG_ARC_STACK_BEGIN
	mov	fp, sp
	/* Start C-code */
	jal	start_arcboot
.endm

.macro M_REMAP_MEM
	/* flip memmap and remap ddr */
	mov	r1, RUBY_SYS_CTL_BASE_ADDR
	mov	r2, RUBY_SYS_CTL_LINUX_MAP(0x1) | RUBY_SYS_CTL_REMAP(0x3)
	st.di	r2, [r1, RUBY_SYS_CTL_MASK - RUBY_SYS_CTL_BASE_ADDR]
	mov	r2, RUBY_SYS_CTL_LINUX_MAP(0x1)
	st.di	r2, [r1, RUBY_SYS_CTL_CTRL - RUBY_SYS_CTL_BASE_ADDR]
	ld.di	r2, [r1, RUBY_SYS_CTL_CTRL - RUBY_SYS_CTL_BASE_ADDR] /* read back to clear pipeline */
	sync                                                         /* wait for pipeline to flush */
.endm

.macro M_GOTO_IF_EXEC_REMAPPED_SRAM tag
	lr	r1, [ARC_REG_PC]
	brlt	r1, RUBY_SRAM_BEGIN, 1f
	brgt	r1, RUBY_SRAM_BEGIN + RUBY_SRAM_SIZE, 1f
	b \tag
1:
.endm

.macro M_BOOTMODE_CMP val
	mov_s	r1, RUBY_SYS_CTL_BASE_ADDR
	ld.di	r2, [r1, RUBY_SYS_CTL_CTRL - RUBY_SYS_CTL_BASE_ADDR]
	and	r2, r2, 0x3
	cmp_s	r2, \val
.endm

.macro M_IF_BOOT_FROM_FLASH
	M_BOOTMODE_CMP 0x2
.endm

// delay/pulse is 200 * 2.5ns (400mhz) = 500 nS, verified on scope
#define PHY_RESET_DELAY 200
.macro M_REMOVE_FROM_RESET
	/* in general case, need to remove ddr and sram from reset 
	 *   We also need to create a reset pulse for external reset pin */
	mov_s	r1, RUBY_SYS_CTL_BASE_ADDR
	mov_s	r2, RUBY_SYS_CTL_RESET_EXT | RUBY_SYS_CTL_RESET_DDR | RUBY_SYS_CTL_RESET_SRAM
	st.di	r2, [r1, RUBY_SYS_CTL_CPU_VEC_MASK - RUBY_SYS_CTL_BASE_ADDR]
	st.di	r2, [r1, RUBY_SYS_CTL_CPU_VEC - RUBY_SYS_CTL_BASE_ADDR]

	mov_s	r2, RUBY_SYS_CTL_RESET_EXT
	st.di	r2, [r1, RUBY_SYS_CTL_CPU_VEC_MASK - RUBY_SYS_CTL_BASE_ADDR]
        /* delay for PHY reset delay */
	mov	%lp_count,PHY_RESET_DELAY
	lp	1f
	nop
1:
	st.di	0, [r1, RUBY_SYS_CTL_CPU_VEC - RUBY_SYS_CTL_BASE_ADDR]
.endm

#endif // #ifdef __ASSEMBLY__

#endif // #ifndef __START_INL

