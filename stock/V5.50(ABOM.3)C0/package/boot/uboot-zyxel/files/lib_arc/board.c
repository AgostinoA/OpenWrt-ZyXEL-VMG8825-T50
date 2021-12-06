/*
 *  Copyright Codito Technologies (www.codito.com) Aug 15 , 2005
 *
 *  lib_arc/board.c
 *
 *  Copyright (C) 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 * 
 * Authors : Sandeep Patil (sandeep.patil@codito.com)
 * 			 Pradeep Sawlani (pradeep.sawlani@codito.com)
 */


#include <common.h>		/* Serial functions	*/ 
#include <linux/types.h>	/* ulong typedef    	*/
#include <asm/uboot-arc.h>	/* _start		*/
#include <asm/global_data.h>	/* For global data structre */
#include <version.h>
#include <config.h>
#include <net.h>
#include <malloc.h>
#include <stdio_dev.h>
//#include <devices.h>

const char version_string[] =
	U_BOOT_VERSION" (" __DATE__ " - " __TIME__ ")";

typedef int (init_fnc_t) (void);

int board_init(void);
int board_late_init(void);

init_fnc_t *init_sequence[] = {
	cpu_init,		/* cpu specific initialisations*/
	board_init,
	serial_init,            /* serial communications setup */
	env_init,		/* intialise environment */
	console_init_f,         /* stage 1 init of console */
	NULL,
};


#if 0 // u-boot-2009.11 supported.
/*
 *    Begin and End of memory area for malloc(), and current "brk"
 */
static ulong mem_malloc_start = 0;
static ulong mem_malloc_end = 0;
static ulong mem_malloc_brk = 0;

static void mem_malloc_init (ulong dest_addr)
{
	mem_malloc_start = dest_addr;
	mem_malloc_end = dest_addr + CONFIG_SYS_MALLOC_LEN;
	mem_malloc_brk = mem_malloc_start;
#ifndef CONFIG_ARC_HEAP_MEM_NO_INIT
	memset((void *)mem_malloc_start, 0, mem_malloc_end - mem_malloc_start);
#endif
}

void *sbrk (ptrdiff_t increment)
{
	ulong old = mem_malloc_brk;
	ulong new = old + increment;
	
	if ((new < mem_malloc_start) || (new > mem_malloc_end)) {
		return (NULL);
	}
	mem_malloc_brk = new;
	return ((void *) old);
}
#endif

gd_t *global_data = NULL;
gd_t *gd = NULL;

void start_arcboot(void)
{
	DECLARE_GLOBAL_DATA_PTR;
	static gd_t gd_data;
	static bd_t bd_data;
	init_fnc_t **init_fnc_ptr;

	unsigned stage = 0xf;

	gd = global_data = &gd_data;
	gd->bd = &bd_data;

	for (init_fnc_ptr = init_sequence; *init_fnc_ptr; ++init_fnc_ptr) {
		show_boot_progress(stage--);
		if ((*init_fnc_ptr)() != 0) {
			hang();
		}
	}	

	/* Setup malloc area */
	//mem_malloc_init(CONFIG_ARC_HEAP_BEGIN, CONFIG_SYS_MALLOC_LEN);
	env_relocate((void *)CONFIG_ARC_HEAP_BEGIN);

	/* set up ddr based on board_cfg*/
	board_late_init(); 

    /* Due to SRAM is too small, need to relocate heap to DRAM*/
    mem_malloc_init(CONFIG_ARC_FREE_BEGIN+gd->bd->bi_memsize-CONFIG_SYS_MALLOC_LEN, CONFIG_SYS_MALLOC_LEN);
    env_relocate(NULL);
    printf("heap at 0x%08lX(%d), env at 0x%08lX(%d)\n", CONFIG_ARC_FREE_BEGIN+gd->bd->bi_memsize-CONFIG_SYS_MALLOC_LEN,
            CONFIG_SYS_MALLOC_LEN, gd->env_addr, CONFIG_ENV_SIZE);
#if defined(CONFIG_CMD_NET)
	/*IP Address */
	gd->bd->bi_ip_addr = getenv_IPaddr ("ipaddr");
	/* MAC Address */
	{
		int i;
		ulong reg;
		char *s, *e;
		uchar tmp[64];
		i = getenv_r ("ethaddr", (char *)tmp, sizeof (tmp));
		s = (i > 0) ? (char *)tmp : NULL;
		for (reg = 0; reg < 6; ++reg) {
			gd->bd->bi_enetaddr[reg] = s ? simple_strtoul (s, &e, 16) : 0;
			if (s) {
				s = (*e) ? e + 1 : e;
			}
		}
	}
	/* Boot file */
	{
		char *s;
		if ((s = getenv("bootfile")) != NULL) {
			copy_filename(BootFile, s, sizeof(BootFile));
		}
	}
#endif
	/* Initialize stdio devices */
    stdio_init ();
	jumptable_init();
	console_init_r();
#ifdef CONFIG_CMD_NET
	eth_initialize(gd->bd);
#endif

    for(;;) {
		main_loop();
	}
}

void hang()
{
	printf("please reset....\n");
	for(;;);
}

