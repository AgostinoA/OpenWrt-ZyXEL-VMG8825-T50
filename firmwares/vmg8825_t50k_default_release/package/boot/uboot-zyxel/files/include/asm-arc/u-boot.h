/*
 * Copyright Codito Technologies (www.codito.com) 
 *
 *  include/asm-arc/u-boot.h
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


#ifndef __U_BOOT_H__
#define __U_BOOT_H__

#ifndef __ASSEMBLY__
#include <linux/types.h>


typedef struct bd_info {
	unsigned long	bi_memsize;	/* size	 of DRAM memory in bytes */
	unsigned long	bi_ip_addr;	/* IP Address */
	unsigned long	bi_boot_params;	/* ATAG parameters address */
	unsigned char	bi_enetaddr[6];	/* Ethernet adress */
	int		bi_board_id;	/* board id for hw config */
} bd_t;

#endif /* __ASSEMBLY__ */
#endif	/* __U_BOOT_H__ */

