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

#include <asm/arch/platform.h>

/***********************************************************************************
 * Vectors must be aligned on 1KB boundary.
 */
.section .text

.align 1024

__vectors_start:
.globl __vectors_start

/***********************************************************************************
 * Vectors itself.
 */

j	EV_Reset    ; 0x00, Reset (0x0)
j	EV_MemErr   ; 0x08, Memory error (0x8)
j	EV_InstrErr ; 0x10, Instruction error (0x10)

.rept 29
	j	EV_NotImpl
.endr

j	EV_MachineCheck  ; 0x100, Fatal Machine check (0x20)
j	EV_TLBMissI      ; 0x108, Intruction TLB miss (0x21)
j	EV_TLBMissD      ; 0x110, Data TLB miss (0x22)
j	EV_TLBProtV      ; 0x118, Protection Violation (0x23) or Misaligned Access
j	EV_PrivilegeV    ; 0x120, Privilege Violation (0x24)
j	EV_Trap          ; 0x128, Trap exception (0x25)
j	EV_Extension     ; 0x130, Extn Intruction Excp (0x26)

.rept 24
	j	EV_NotImpl
.endr

/***********************************************************************************
 * Stack and static data to process interrupts.
 * As static data is used, code does not work correctly on SMP systems,
 * or on systems where interrupts can interrupt each other
 * (like in case of ARC's 2 levels of interrupts - this mode
 * must not be used with this code).
 */

	.rept 127
		.word 0x0
	.endr
__vector_stack:
	.word 0
__vector_saved_sp:
	.word 0
__vector_saved_fp:
	.word 0
__vector_saved_cfunc_ptr:
	.word 0

/***********************************************************************************
 * Code to process interrupts.
 */

.macro VECTOR_SAVE_REGS
	st.a r0, [sp, -4]
	st.a r1, [sp, -4]
	st.a r2, [sp, -4]
	st.a r3, [sp, -4]
	st.a r4, [sp, -4]
	st.a r5, [sp, -4]
	st.a r6, [sp, -4]
	st.a r7, [sp, -4]
	st.a r8, [sp, -4]
	st.a r9, [sp, -4]
	st.a r10, [sp, -4]
	st.a r11, [sp, -4]
	st.a r12, [sp, -4]
.endm

.macro VECTOR_RESTORE_REGS
	ld.ab r12, [sp, 4]
	ld.ab r11, [sp, 4]
	ld.ab r10, [sp, 4]
	ld.ab r9, [sp, 4]
	ld.ab r8, [sp, 4]
	ld.ab r7, [sp, 4]
	ld.ab r6, [sp, 4]
	ld.ab r5, [sp, 4]
	ld.ab r4, [sp, 4]
	ld.ab r3, [sp, 4]
	ld.ab r2, [sp, 4]
	ld.ab r1, [sp, 4]
	ld.ab r0, [sp, 4]
.endm

.macro VECTOR_FUNC_HEADER name
	.globl \name
	.align 4
	\name :
.endm

.macro VECTOR_FUNC name ptr
	; please have this macro small as it will be used many times
	VECTOR_FUNC_HEADER \name

	; store pointer to __vector_saved_cfunc_ptr address.
	st r0, [__vector_saved_sp]
	mov r0, \ptr
	st r0, [__vector_saved_cfunc_ptr]
	ld r0, [__vector_saved_sp]

	; go to dispatcher. it never returns back.
	j EV_Dispatcher
.endm

VECTOR_FUNC_HEADER EV_Dispatcher
	; prepare stack
	st sp, [__vector_saved_sp]
	st fp, [__vector_saved_fp]
	mov sp, __vector_stack
	mov fp, sp

	; save registers which C-function can modify to stack
	VECTOR_SAVE_REGS

	; call C-function
	; it must have 'void f(void) prototype
	ld r0, [__vector_saved_cfunc_ptr]
	jl [r0]

	; restore registers from stack
	VECTOR_RESTORE_REGS

	; restore original stack registers
	ld sp, [__vector_saved_sp]
	ld fp, [__vector_saved_fp]

	; return from interrupt
	rtie

VECTOR_FUNC EV_NotImpl      intr_EV_NotImpl
VECTOR_FUNC EV_Reset        intr_EV_Reset
VECTOR_FUNC EV_MemErr       intr_EV_MemErr
VECTOR_FUNC EV_InstrErr     intr_EV_InstrErr
VECTOR_FUNC EV_MachineCheck intr_EV_MachineCheck
VECTOR_FUNC EV_TLBMissI     intr_EV_TLBMissI
VECTOR_FUNC EV_TLBMissD     intr_EV_TLBMissD
VECTOR_FUNC EV_TLBProtV     intr_EV_TLBProtV
VECTOR_FUNC EV_PrivilegeV   intr_EV_PrivilegeV
VECTOR_FUNC EV_Trap         intr_EV_Trap
VECTOR_FUNC EV_Extension    intr_EV_Extension
