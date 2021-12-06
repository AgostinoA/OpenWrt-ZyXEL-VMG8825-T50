/*
 * Ruby platform.
 *
 * flip memmap configuration.
 *
 * Unfortunately passing linker script through preprocessor is not implemented,
 * so let's hard-code all values.
 */

OUTPUT_FORMAT("elf32-littlearc", "elf32-littlearc", "elf32-littlearc")
OUTPUT_ARCH(arc)

ENTRY(hello_world)

MEMORY
{
	/*
	 * SRAM size is 256KB.
	 * SRAM from LHOST seen starting from 0x88000000 address.
	 * SRAM from MuC/DSP seen starting from 0x80000000 address.
	 * Let's reserve 64KB at the end of SRAM for stack and heap.
	 * Please keep it synchronized with include/configs/ruby.h
	 */
	sram : ORIGIN = 0x80000000, LENGTH = 256K - 64K
}

SECTIONS
{
	.text :
	{

		*(.text)
	} > sram
	. = ALIGN(4);

	.rodata :
	{
		*(.rodata)
		*(.rodata.str*)
	} > sram
	. = ALIGN(4);

	.data :
	{
		*(.data)
	} > sram
	. = ALIGN(4);

	
	__bss_start = .;
	.bss ABSOLUTE(.) :
	{
		*(.bss)
	} > sram
	. = ALIGN(4);
	__bss_end = .;

	.stack :
	{
		. += 16384;
		*(.data)
	} > sram
	.heap :
	{
		*(.data)
	} > sram
	. = ALIGN(4);
	uboot_end = .;
	_end = .;
}

