/*
 * Copyright Codito Technologies (www.codito.com)  
 *
 *  include/asm-arc/arcregs.h
 *
 *  Copyright (C) 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Authors: Sandeep Patil (sandeep.patil@codito.com)
 * 			Pradeep Sawlani (pradeep.sawlani@codito.com)
 * Auxiliary register definitions and macros to read and write to them. 
 */

#ifndef	_ASM_ARC_CACHE_H
#define	_ASM_ARC_CACHE_H

#ifndef	__ASSEMBLY__

void invalidate_icache_all(void);
void invalidate_icache_range(unsigned long start, unsigned long stop);
void flush_and_inv_dcache_all(void);
void invalidate_dcache_range(unsigned long start, unsigned long stop);
void flush_and_inv_dcache_range(unsigned long start, unsigned long stop);
void flush_dcache_range(unsigned long start, unsigned long stop);
void dcache_disable(void);
void icache_disable(void);
void dcache_enable(void);
void icache_enable(void);
int dcache_status(void);
int icache_status(void);
void flush_cache(unsigned long start, unsigned long stop);

#endif	/* __ASSEMBLY__ */

#endif	/* _ASM_ARC_CACHE_H */

