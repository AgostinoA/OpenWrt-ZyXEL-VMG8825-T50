/*
 * (C) Copyright Mindspeed Technologies Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/* This code runs from ARM1 and setups the CPU before jumping to
the beginning of the ARM1 image (usually a Linux zImage).
It must be copied to 0x00000000 before releasing ARM1.
Linker script variables (in u-boot.lds) are used to find the
start and end address of this bit of code */

.globl _arm1_start_addr
.globl _arm1_r0
.globl _arm1_r1
.globl _arm1_r2


	ldr	r0, _arm1_r0
	ldr	r1, _arm1_r1
	ldr	r2, _arm1_r2
	ldr	pc, _arm1_start_addr

_arm1_start_addr:
	.word 0x00000000

_arm1_r0:
	.word 0x00000000

_arm1_r1:
	.word 0x00000000

_arm1_r2:
	.word 0x00000000

