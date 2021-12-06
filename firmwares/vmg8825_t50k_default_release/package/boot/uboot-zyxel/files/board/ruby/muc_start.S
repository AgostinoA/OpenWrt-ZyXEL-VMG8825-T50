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

#include "uc_start.inl"

#ifdef CONFIG_CMD_UC

	/* MuC code entry point. Code will be moved and so must be position-independent! */
	.section .text
	.align 4
__muc_start_begin:
.globl __muc_start_begin
	/* Vectors */
	j	1f
.rept 31
	j	2f
.endr
1:
	UC_ENABLE_INTRS_MUC
	UC_CODE muc_entry_func
2:
	UC_EXCEPTIONS_ARC7 RUBY_SYS_CTL_L2M_INT
__muc_start_end:
.globl __muc_start_end

#endif

