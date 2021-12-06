/*
 * Copyright Codito Technologies (www.codito.com) 
 *
 *  include/asm-arc/setup.h
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

#ifndef __ASMARC_SETUP_H
#define __ASMARC_SETUP_H

#include<linux/types.h>

/*
 * The new way of passing information: a list of tagged entries
 */

/* The list ends with an ATAG_NONE node. */

#define ATAG_NONE	0x00000000

struct tag_header {
	u32 size;
	u32 tag;
};

/* The list must start with an ATAG_CORE node */
#define ATAG_CORE	0x54410001

struct tag_core {
};

/* it is allowed to have multiple ATAG_MEM nodes */
#define ATAG_MEM	0x54410002

struct tag_mem32 {
        u32	size;
};


/* clock speed */
#define ATAG_CLK_SPEED  0x5441003

struct tag_clk_speed {
  u32 clk_speed_hz;
};
  


/* describes how the ramdisk will be used in kernel */
#define ATAG_RAMDISK	0x54410004

struct tag_ramdisk {
	u32 flags;	/* bit 0 = load, bit 1 = prompt */
	u32 size;	/* decompressed ramdisk size in _kilo_ bytes */
	u32 start;	/* starting block of floppy-based RAM disk image */
};

/* describes where the compressed ramdisk image lives (virtual address) */
/*
 * this one accidentally used virtual addresses - as such,
 * its depreciated.
 */
#define ATAG_INITRD	0x54410005

/* describes where the compressed ramdisk image lives (physical address) */
#define ATAG_INITRD2	0x54420005

struct tag_initrd {
	u32 start;	/* physical start address */
	u32 size;	/* size of compressed ramdisk image in bytes */
};


/* configuring cache */ 
#define ATAG_CACHE     0x54420006
struct tag_cache {
         u16 icache;
         u16 dcache;  
};



/* describes the configuration of serial controller */


#define ATAG_SERIAL 0x54420007
struct tag_serial {
       u32 serial_nr;
       u32 baudrate;
};

/* describes the configuration of vmac controller */

#define ATAG_VMAC 0x54420008
struct tag_vmac {
       u8 addr[8];
};



/* command line: \0 terminated string */
#define ATAG_CMDLINE	0x54410009

struct tag_cmdline {
	char	cmdline[1];	/* this is the minimum size */
};

/* Quantenna hw_config_id */
#define ATAG_HW_CONFIG_ID	0x54410100
struct tag_hwid {
	uint32_t hwid;
};

struct tag {
	struct tag_header hdr;
	union {
		struct tag_core		core;
		struct tag_mem32	mem;
		struct tag_ramdisk	ramdisk;
		struct tag_initrd	initrd;
		struct tag_cmdline	cmdline;
		struct tag_cache        cache;
		struct tag_clk_speed    clk_speed;
		struct tag_serial       serial;
		struct tag_vmac         vmac;
		struct tag_hwid		hwid;
	} u;
};



#define tag_next(t)	((struct tag *)((u32 *)(t) + (t)->hdr.size))
#define tag_size(type)	((sizeof(struct tag_header) + sizeof(struct type)) >> 2)

#endif /* __ASMARC_SETUP_H */
