/*
 * Copyright Codito Technologies (www.codito.com) 
 *
 *  include/asm-arc/global_data.h
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

#ifndef	__ASM_GBL_DATA_H
#define __ASM_GBL_DATA_H

#include<asm/u-boot.h> 

typedef	struct	 {
	bd_t		*bd;
	unsigned long	flags;
	
	unsigned long	baudrate;
	unsigned long	have_console;	/* serial_init() was called */

	unsigned long	reloc_off;	/* Relocation Offset */

	unsigned long	env_addr;	/* Address  of Environment struct */
	unsigned long	env_valid;	/* Checksum of Environment valid? */

	unsigned long	cpu_clk;	/* CPU clock in Hz!		*/
	unsigned long	bus_clk;	/* Bus clock in Hz!		*/

	void		**jt;		/* jump table */
} gd_t;
extern gd_t *global_data;

/*
 * Global Data Flags
 */
#define	GD_FLG_RELOC	0x00001		/* Code was relocated to RAM		*/
#define	GD_FLG_DEVINIT	0x00002		/* Devices have been initialized	*/
#define	GD_FLG_SILENT	0x00004		/* Silent mode				*/
#define	GD_FLG_POSTFAIL	0x00008		/* Critical POST test failed	 */
#define	GD_FLG_POSTSTOP	0x00010		/* POST seqeunce aborted	 */
#define	GD_FLG_LOGINIT	0x00020		/* Log Buf has been initialized	 */
#define GD_FLG_DISABLE_CONSOLE	0x00040		/* Disable console (in & out)	 */

#define DECLARE_GLOBAL_DATA_PTR      extern gd_t *gd  /* defined in lib_arc/board.c */ 

#endif /* __ASM_GBL_DATA_H */

