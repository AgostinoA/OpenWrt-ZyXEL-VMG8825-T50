/*
 * (C) Copyright 2011 Quantenna Communications Inc.
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

OUTPUT_FORMAT("elf32-littlearc", "elf32-littlearc", "elf32-littlearc")
OUTPUT_ARCH(arc)

ENTRY(_start)

MEMORY
{
	/*
	 * Mini U-Boot and mini-piggy will fit into ~40k.
	 * Stack is always end of SRAM.
	 */
	sram : ORIGIN = TEXT_BASE, LENGTH = 64K
}

SECTIONS
{
	.text :
	{
		__uboot_begin = .;
		*(.text)
		*(.text.*)
	} > sram
	. = ALIGN(4);

	.rodata :
	{
		*(.rodata)
		*(.rodata.str*)
		*(.rodata.*)
	} > sram
	. = ALIGN(4);

	.data :
	{
		*(.data)
		*(.data.*)
	} > sram
	. = ALIGN(4);

	__bss_start = .;
	.bss ABSOLUTE(.) :
	{
		*(.bss)
		*(.bss.*)
	} > sram
	. = ALIGN(4);
	__bss_end = .;

	__uboot_end = .;

	/DISCARD/ : {
		*(.u_boot_cmd)
	}
}

