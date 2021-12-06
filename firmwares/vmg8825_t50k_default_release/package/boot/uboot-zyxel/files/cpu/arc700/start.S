/* 
 * Copyright Codito Technologies (www.codito.com) 
 *
 *  cpu/arc/start.S
 *
 *  Copyright (C) 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 * 
 * Authors : Sandeep Patil (sandeep.patil@codito.com)
 *  		 Pradeep Sawlani (pradeep.sawlani@codito.com)
 */

#include <asm/arcregs.h>	/* required for STATUS_H_SET */
#include <config.h>

	/* .text section loaded at TEXT_BASE defined in board/aa3/config.mk */
	.section .text , "ax" , @progbits
	.type _start, @function
	.align 4
	.globl _start

.globl _TEXT_BASE
_TEXT_BASE:
	.word TEXT_BASE
	
.globl _bss_start
_bss_start:
	.word __bss_start

.globl _bss_end
_bss_end:
	.word __bss_end

.globl _arcboot_start
_arcboot_start:
	.word _start		

_start:
	/* Disable interrupts */
/*	lr    r2,[ARC_REG_STATUS32]	
	and   r2,r2,STATUS_DISABLE_INTERRUPTS
	sr    r2,[ARC_REG_STATUS32]
*/	

#if CONFIG_SYS_UBOOT_ON_FLASH
	/* For relocation following registers are used : 
	*  r1 : destination
	*  r2 : source 
	*  r3 : till
	*  r4 : jump to next loop
	*  r5 : temporary storage
	*  r6 : jump to same loop   
	*/

	/* Relocate vector table if necessary */
#if CONFIG_SYS_FLASH_BASE
				
	mov r1,0x0	
	mov r2,CONFIG_SYS_FLASH_BASE	        /* vector table start address in flash is (__vector_start + flash base - text base) since vector start and text base
					   are same we move only CONFIG_SYS_FLASH_BASE */

 
	mov r3,__vector_end		/* vector end table address in flash is (__vector_end + flash base - text base) */
	add r3,r3,CONFIG_SYS_FLASH_BASE-TEXT_BASE

	mov r4,relocate_text 			/* address of relocate text in flash = relocate text + flash base - text base */
	add r4,r4,CONFIG_SYS_FLASH_BASE-TEXT_BASE
	
	mov r6,copy_vector_table
	add r6,r6,CONFIG_SYS_FLASH_BASE-TEXT_BASE
copy_vector_table :
		cmp r2,r3
		JEQ [r4]
	
		/* copy from r2 to dest i.e in r1 register which point to 0x0 */	
		ld.ab r5,[r2,4]
		st.ab r5,[r1,4]
		
		j [r6]
		
#endif /* CONFIG_SYS_FLASH_BASE */

	/* Relocate text section */
relocate_text:
	mov r1,__text_start
	
	mov r2,__text_start
	add r2,r2,CONFIG_SYS_FLASH_BASE-TEXT_BASE

	mov r3,__text_end
	add r3,r3,CONFIG_SYS_FLASH_BASE-TEXT_BASE


	mov r4,relocate_data 	
	add r4,r4,CONFIG_SYS_FLASH_BASE-TEXT_BASE

	mov r6,copy_text_section
	add r6,r6,CONFIG_SYS_FLASH_BASE-TEXT_BASE

copy_text_section :
		cmp r2,r3
		JEQ [r4]
	
		/* copy from r2 to dest i.e in r1 register */	
		ld.ab r5,[r2,4]
		st.ab r5,[r1,4]
		
		j [r6]
			

	/* Relocate data section */
relocate_data:
	mov r1,__data_start

	mov r2,__data_start
	add r2,r2,CONFIG_SYS_FLASH_BASE-TEXT_BASE

	mov r3,__data_end
	add r3,r3,CONFIG_SYS_FLASH_BASE-TEXT_BASE

	mov r4,fill_bss
	
	mov r6,copy_data_section
	add r6,r6,CONFIG_SYS_FLASH_BASE-TEXT_BASE

copy_data_section :
	
		cmp r2,r3
		JEQ [r4]
	
		/* copy from r2 to dest i.e in r1 register */	
		ld.ab r5,[r2,4]
		st.ab r5,[r1,4]
		
		j [r6]


#endif /* FLASH */
/* This code will be executed from ram */	
	.globl fill_bass
fill_bss:
	/* Clear bss */
	mov_s r2, __bss_start
	mov_s r3, __bss_end

_clear_bss:
	st.ab 0,[r2,4]
	brlt  r2,r3,_clear_bss
	
	/* setup stack pointer */
	mov sp,TEXT_BASE - CONFIG_SYS_MALLOC_LEN - 4 
	mov fp,sp	
	jal start_arcboot

	/* Interrupt service routines */
res_service	:	
mem_service	:
instr_service	:
handle_interrupt:
EV_MachineCheck	:

EV_TLBMissI	:
EV_TLBMissD	:
EV_TLBProtV	:
EV_PrivilegeV	:
EV_Trap		:
EV_Extension	:
reserved	:
			FLAG STATUS_H_SET
			NOP
			NOP
			NOP	
