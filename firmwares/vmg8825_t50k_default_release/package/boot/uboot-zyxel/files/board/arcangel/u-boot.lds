OUTPUT_FORMAT("elf32-littlearc", "elf32-littlearc", "elf32-littlearc")
OUTPUT_ARCH(arc)
ENTRY(_start)
SECTIONS
{

	. = ALIGN(4);


	.vector :
	{
		*(.vector);
	}
	. = ALIGN(4); 
	.text      :
	{

	 __text_start = .;
	  cpu/arc/start.o	(.text) 
	  *(.text)	
	}
	. = ALIGN(4);
	__text_end = .;

	__data_start = .;
	.rodata : { *(.rodata) }
	
	. = ALIGN(4);
	
	.data : { *(.data) }
	. = ALIGN(4);
	.got : { *(.got) }
	
	. = ALIGN(4);
	__u_boot_cmd_start = .;
	.u_boot_cmd : { *(.u_boot_cmd) }
	__u_boot_cmd_end = .;

	. = ALIGN(4);
	
	__data_end = .;

	__bss_start = .;
	.bss : { *(.bss) }
	__bss_end = .;
}
