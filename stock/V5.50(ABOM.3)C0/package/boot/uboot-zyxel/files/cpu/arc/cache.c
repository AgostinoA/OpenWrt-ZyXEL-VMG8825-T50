/*
 * (C) Copyright 2010 Quantenna Communications Inc.
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

/******************************************************************************
 * Copyright ARC International (www.arc.com) 2007-2009
 *
 *****************************************************************************/
/******************************************************************************
 * Copyright Codito Technologies (www.codito.com) Oct 01, 2004
 * 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *****************************************************************************/
/*
 *  linux/arch/arc/mm/cache_arc700.c
 *
 *  Copyright (C) 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Authors: Amit Bhor, Rahul Trivedi
 * I-Cache and D-cache control functionality. 
 * Ashwin Chaugule <ashwin.chaugule@codito.com>
 */

#include <command.h>
#include <common.h>
#include <asm/arcregs.h>
#include <asm/cache.h>

//---------------------------------------------------------------------------------

/* Please keep it always inlined - it should be safer to use with disable cache function */
__attribute__((always_inline))
static inline void _invalidate_icache_all(void)
{
	/* Invoke Cache INV CMD */
	write_new_aux_reg(ARC_REG_IC_IVIC, 0x1);
	/* read will not complete till the icache inv operation is not over */
	read_new_aux_reg(ARC_REG_IC_CTRL);
}

/* Please keep it always inlined - it should be safer to use with disable cache function */
__attribute__((always_inline))
static inline void _flush_and_inv_dcache_all(void)
{
	/* Set the Invalidate mode to FLUSH BEFORE INV */
	write_new_aux_reg(ARC_REG_DC_CTRL, read_new_aux_reg(ARC_REG_DC_CTRL) | ARC_INV_MODE_FLUSH);

	/* Invoke Cache INV CMD */
	write_new_aux_reg(ARC_REG_DC_IVDC, 0x1);

	/* wait for the flush to complete, poll on the FS Bit */
	while(read_new_aux_reg(ARC_REG_DC_CTRL) & ARC_DC_FLUSH_STATUS_BIT);
}

//---------------------------------------------------------------------------------

void invalidate_icache_all(void)
{
	_invalidate_icache_all();
}

void invalidate_icache_range(unsigned long start, unsigned long stop)
{
	while (start < stop) {
		write_new_aux_reg(ARC_REG_IC_IVIL, start);
		start += ARC_ICACHE_LINE_LEN;
	}
}

//---------------------------------------------------------------------------------

void flush_and_inv_dcache_all(void)
{
	_flush_and_inv_dcache_all();
}

void invalidate_dcache_range(unsigned long start, unsigned long stop)
{
	/* make sure we do not flush here, just invalidate */
	write_new_aux_reg(ARC_REG_DC_CTRL, read_new_aux_reg(ARC_REG_DC_CTRL) & (~ARC_INV_MODE_FLUSH));
	while (start < stop) {
		write_new_aux_reg(ARC_REG_DC_IVDL, start);
		start += ARC_DCACHE_LINE_LEN;
	}
}

void flush_and_inv_dcache_range(unsigned long start, unsigned long stop)
{
	/* make sure we do flush here */
	write_new_aux_reg(ARC_REG_DC_CTRL, read_new_aux_reg(ARC_REG_DC_CTRL) | ARC_INV_MODE_FLUSH);
	while (start < stop) {
		write_new_aux_reg(ARC_REG_DC_IVDL, start);
		start += ARC_DCACHE_LINE_LEN;
	}
	/* wait for the flush to complete, poll on the FS Bit */
	while(read_new_aux_reg(ARC_REG_DC_CTRL) & ARC_DC_FLUSH_STATUS_BIT);
}

void flush_dcache_range(unsigned long start, unsigned long stop)
{
	while (start < stop) {
		write_new_aux_reg(ARC_REG_DC_FLDL, start);
		start += ARC_DCACHE_LINE_LEN;
	}
	/* wait for the flush to complete, poll on the FS Bit */
	while(read_new_aux_reg(ARC_REG_DC_CTRL) & ARC_DC_FLUSH_STATUS_BIT);
}

//---------------------------------------------------------------------------------

void dcache_disable(void)
{
	/* Prepare cache for switching off. */
	_flush_and_inv_dcache_all();
	/* Switch cache off */
	write_new_aux_reg(ARC_REG_DC_CTRL, read_new_aux_reg(ARC_REG_DC_CTRL) | ARC_DC_DISABLE);
}

void icache_disable(void)
{
	/* Prepare cache for switching off. */
	_invalidate_icache_all();
	/* Switch cache off */
	write_new_aux_reg(ARC_REG_IC_CTRL, read_new_aux_reg(ARC_REG_IC_CTRL) | ARC_IC_DISABLE);
}

//---------------------------------------------------------------------------------

void dcache_enable(void)
{
	write_new_aux_reg(ARC_REG_DC_CTRL, read_new_aux_reg(ARC_REG_DC_CTRL) & ~ARC_DC_DISABLE);
}

void icache_enable(void)
{
	write_new_aux_reg(ARC_REG_IC_CTRL, read_new_aux_reg(ARC_REG_IC_CTRL) & ~ARC_IC_DISABLE);
}

//---------------------------------------------------------------------------------

int dcache_status(void)
{
	return !(read_new_aux_reg(ARC_REG_DC_CTRL) & ARC_DC_DISABLE);
}

int icache_status(void)
{
	return !(read_new_aux_reg(ARC_REG_IC_CTRL) & ARC_IC_DISABLE);
}

//---------------------------------------------------------------------------------

void flush_cache(unsigned long start, unsigned long len)
{
	unsigned long stop = start+len;
	flush_and_inv_dcache_range(start, stop);
	invalidate_icache_range(start, stop);
}

//---------------------------------------------------------------------------------

