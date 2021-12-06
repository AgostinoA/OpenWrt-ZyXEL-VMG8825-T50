/*
 * Copyright Codito Technologies (www.codito.com) 
 *
 * cpu/arc/cpu.c
 *
 * Copyright (C) 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 * 
 * Authors :Sandeep Patil (sandeep.patil@codito.com)
 * 			Pradeep Sawlani (pradeep.sawlani@codito.com)
 */

#include <command.h>
#include <common.h>
#include <asm/arcregs.h>


int do_reset (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	
#if CFG_UBOOT_ON_FLASH  	
	/* if uboot is on flash then boot agian from flash */
	void (*reset)();
	reset = (void (*)())0x0;
	(*reset)();
#endif	

}


void disable_icache(void)
{
	__asm__ __volatile (	"lr  r0,[0x11] \n\t"
				"or  r0,r0,1 \n\t"
				"sr  r0,[0x11] \n\t"
				::
				:"r0");	

}
void dcache_disable(void)
{
	/* Flush D cache */
	__asm__ __volatile (	
			"sr  1, [0x47] \n\t"
			::
			);
	/* Disable D cache */
	__asm__ __volatile (	
			"lr  r0,[0x48] \n\t"
			"or  r0,r0,1 \n\t"
			"sr  r0,[0x48] \n\t"
			::
			:"r0");	
	


}

dcache_enable()
{

}

dcache_status()
{
}



void flush_cache (unsigned long dummy1, unsigned long dummy2)
{
	/* flushing data cache */
	write_new_aux_reg(ARC_REG_DC_FLSH, 1);

	/* poll for completion */
	while (read_new_aux_reg(ARC_REG_DC_CTRL) & (1<<8));

	/* Invalidate instruction cache */
	write_new_aux_reg(ARC_REG_IC_IVIC, 1);
	    
	/* read will only comple when invalidation complete */
	read_new_aux_reg(ARC_REG_IC_CTRL);
}	

/*
 * disable dcache and icahce
 */

int cpu_init(void)
{
	disable_interrupts();
	return 0;
}


