/* Copyright (c) 2017, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <asm/system.h>
#include <linux/linkage.h>

ENTRY(secondary_cpu_init)
	/* For us r0 has the arg structure pointer
		struct cpu_entry_arg {
		        void *stack_ptr;
			void *gd_ptr;
			void *arg_ptr;
			int  cpu_up;
			int cmd_complete;
			int cmd_result;
		};
	*/
	ldr sp, [r0] /* stack_ptr */
	bic     sp, sp, #7 /* 8-byte alignment required for stack */
	stmfd sp!, {r0}

	/*
	 * disable interrupts (FIQ and IRQ), also set the cpu to SVC32 mode
	 */
	mrs	r0, cpsr
	bic	r0, r0, #0x1f		@ clear all mode bits
	orr	r0, r0, #0x13		@ set SVC mode
	orr	r0, r0, #0xc0		@ disable FIQ and IRQ
	msr	cpsr,r0

	/* Enable barrier instructions */
	mrc p15, 0, r0, c1, c0, 0	@Read SCTLR to r0
	orr r0, r0, #0x20		@set the cp15 barrier enable bit
	mcr p15, 0, r0, c1, c0, 0	@write back to SCTLR

        /* Vector address setup - going to be same as core0 for secondary cpus */
        mrc p15, 0, r0, c1, c0, 0   @ Read CP15 SCTLR Register
        bic r0, #CR_V               @ V = 0
        mcr p15, 0, r0, c1, c0, 0   @ Write CP15 SCTLR Register

        /* Set vector address in CP15 VBAR register */
        ldr r0, =_start
        mcr p15, 0, r0, c12, c0, 0  @Set VBAR

	bl cpu_init_cp15

	ldmfd sp!, {r0}

	/* gd address is always in r9, but if u-boot changes Tomorrow,
	 * we have to change here. Note :- --> ARM: use r9 for gd
	*/
	ldr r9, [r0, #0x4]
	/* store success in cpu_up */
	mov r3, #1
	str r3, [r0, #0xc]
	add r1, r0, #0x10
	add r2, r0, #0x14
	ldr r0, [r0, #0x8]

	bl secondary_core_entry
self_loop:
	b self_loop
ENDPROC(secondary_cpu_init)


