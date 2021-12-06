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

/*****************************************************************************
 * This module provides several critical functions for a couple of scenarios:
 *	1) For the case of uboot in flash, copy code to target
 *	2) For the case of uboot loaded via serial, make clean copy for subsequent flash ops
 *	3) Initialize ddr
 *	4) Clear BSS
 *****************************************************************************/
  
#include <config.h>
#include <asm/arcregs.h>
#include <asm/arch/platform.h>
#include "ruby.h"
#include <ruby_version.h>

/*****MACROS**********************************************************************************/

#include "start.inl"

/*****TEXT SECTION****************************************************************************/

	.section .text
	.align 4
_start:
	.globl _start
	b	1f
	/* need easily identifiable tag at beginning of file with version */
	.ascii "U-BOOT " RUBY_UBOOT_VERSION "\0"

	/* Early board config metadata can go here, from 32-48 bytes */
	.align	32
early_flash_config_start:
	.globl early_flash_config_start
	.skip	16
early_flash_config_end:
	.globl early_flash_config_end

1:
	M_REMOVE_FROM_RESET
	M_GOTO_IF_EXEC_REMAPPED_SRAM run_c
	M_IF_BOOT_FROM_FLASH
	bne	ruby_flip_mmap /* if we are running not from flash call the flip routine to
				* flip the bit in place; will return to ruby_boot label */
	j	ruby_boot - TEXT_BASE + RUBY_SPI_FLASH_ADDR /* jump to physical spi address */

ruby_boot:
	.globl ruby_boot
	M_IF_BOOT_FROM_FLASH
	bne	run_c
	M_REMAP_MEM
	M_COPY_UBOOT TEXT_BASE RUBY_SPI_FLASH_ADDR
	j	run_c

run_c:
	M_FILL_BSS
#ifdef CONFIG_ARC_MAKE_UBOOT_COPY
	M_COPY_UBOOT CONFIG_ARC_FREE_BEGIN TEXT_BASE
#endif
	M_GOTO_C_CODE

/*********************************************************************************************/

