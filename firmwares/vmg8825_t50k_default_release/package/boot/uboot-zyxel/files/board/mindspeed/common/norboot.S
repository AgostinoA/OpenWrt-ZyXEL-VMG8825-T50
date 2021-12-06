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

/* This code is used to setup the boot CS to 16bit so that 
the U-boot image can be read from NOR flash. It is compiled into
a special section (and format) using the u-boot.lds linker script and
u16_to_u8.c application */

#include <config.h>
#include <asm/arch/hardware.h>

.globl _start
_start:
	adr	r0, iram_code_start
	ldr	r1, iram_addr
	adr	r2, iram_code_end

copy:
	ldmia	r0!, {r3-r6}	/* copy from source address [r0]    */
	stmia	r1!, {r3-r6}	/* copy to   target address [r1]    */
	cmp	r0, r2		/* until source end address [r2]    */
	ble	copy

	/* Calculate return address, offset is multiplied by 2 */
	adr     r0, _start
	add     r1, r2, r2
	sub     lr, r1, r0

	/* Jump to internal RAM */
	ldr	pc, iram_addr

iram_addr:
	.word	IRAM_BASEADDR


	/* This codes runs from internal RAM and
	   sets the boot chip select */
iram_code_start:
	ldr	r0, cs_reg
	ldr	r1, cs_val
	strh	r1, [r0]

	/* Jump back to flash, now running in 16 bit */
	mov	pc, lr

cs_reg:
	.word	SDC0_CSBOOT_CFG

cs_val:
	.word	0x081E

iram_code_end:
