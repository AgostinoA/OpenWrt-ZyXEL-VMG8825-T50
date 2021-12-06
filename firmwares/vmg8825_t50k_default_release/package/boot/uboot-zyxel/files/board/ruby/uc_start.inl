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

#include <config.h>

#ifdef CONFIG_CMD_UC

#include <asm/arcregs.h>
#include <asm/arch/platform.h>

#include "ruby.h"

.macro UC_TRACE
	ld.di	r0, [uc_trace_num]
	add	r0, r0, 1
	st.di	r0, [uc_trace_num]
.endm

.macro UC_TRACE_DONE
	mov	r0, 1
	st.di	r0, [uc_trace_done]
.endm

.macro UC_ENABLE_ARC_INTRS
	/*
	 * INT_VECTOR_BASE register on MuC(Ruby) after reset contains 0x0, but internal logic
	 * uses start address for vector base (till INT_VECTOR_BASE is resetted) - no need really to setup.
	 * INT_VECTOR_BASE register on DSP(Ruby) must be setted to have interrupts work.
	 * Having such irregularity it would be better to setup register always.
	 */
	UC_TRACE
	mov	r0, UC_ENTRY_SLOT
	sr	r0, [ARC_REG_INTR_VEC_BASE]
	/*
	 * AUX_IENABLE register after reset has all interrupts enabled - no need to setup,
	 * but for safety let's do it.
	 */
	UC_TRACE
	mov	r0, 0xFFFFFFFF
	sr	r0, [ARC_REG_INTR_ENABLE]
	/* Enable interrupts in STATUS32 register */
	UC_TRACE
	flag	STATUS_E1_MASK | STATUS_E2_MASK
.endm

.macro UC_ENABLE_INTRS_MUC
	/* Enable external interrupts (Ruby specific) */
	UC_TRACE
	mov	r0, 0x0
	st.di	r0, [RUBY_SYS_CTL_MUC_ORINT_EN]
	mov	r0, 0xFFFFFFFF
	st.di	r0, [RUBY_SYS_CTL_MUC_INT_EN]
	/* Enable ARC interrupts */
	UC_ENABLE_ARC_INTRS
.endm

.macro UC_ENABLE_INTRS_DSP
	/* Enable external interrupts (Ruby specific) */
	UC_TRACE
	mov	r0, 0x0
	st.di	r0, [RUBY_SYS_CTL_DSP_ORINT_EN]
	mov	r0, 0xFFFFFFFF
	st.di	r0, [RUBY_SYS_CTL_DSP_INT_EN]
	/* Enable ARC interrupts */
	UC_ENABLE_ARC_INTRS
.endm

.macro UC_DISABLE_DCACHE
	UC_TRACE
	lr	r0, [ARC_REG_DC_CTRL]
	or	r0, r0, ARC_DC_DISABLE
	sr	r0, [ARC_REG_DC_CTRL]
.endm

.macro UC_PREPARE_STACK
	UC_TRACE
	mov	sp, __uc_stack
	mov	fp, sp
.endm

.macro UC_RUN_C name
	UC_TRACE
	mov	r0, \name
	jl	[r0]
.endm

.macro UC_INDEFINITE_LOOP
	UC_TRACE
	UC_TRACE_DONE
1:
	sleep
	UC_TRACE
	b	1b
.endm

.macro UC_CODE func_name
	UC_DISABLE_DCACHE
	UC_PREPARE_STACK
	UC_RUN_C \func_name
	UC_INDEFINITE_LOOP
.endm

.macro UC_EXCEPTIONS_ARC7 p2p_reg
	UC_TRACE
	ld.di	r0, [\p2p_reg]
	st.di	r0, [\p2p_reg]
	ld.di	r0, [\p2p_reg]
	sync
	rtie
.endm

.macro UC_EXCEPTIONS_ARC6 p2p_reg
	UC_TRACE
	ld.di	r0, [\p2p_reg]
	st.di	r0, [\p2p_reg]
	ld.di	r0, [\p2p_reg]
	j.f	[ilink1]
.endm

#endif

