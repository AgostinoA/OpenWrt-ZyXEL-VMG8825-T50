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

#include <config.h>
#include <asm/arcregs.h>
#include <asm/arch/platform.h>

#if RUBY_MMAP_FLIP
ruby_flip_mmap:
	.globl ruby_flip_mmap 
	/* Code must be position-independent! */

	/*
	* Flush and invalidate data cache.
	* Please make sure that instructions which touch
	* d-cache are NOT used until flipping is done.
	*/
	/* Set flush mode for invalidate operation */
	lr      r1, [ARC_REG_DC_CTRL]
	bset    r1, r1, 0x6
	sr      r1, [ARC_REG_DC_CTRL]
	/* Start invalidate operation */
	mov     r1, 0x1
	sr      r1, [ARC_REG_DC_IVDC]
	/* Check while cache invalidating will be finished */
dcache_flush_continue:
	lr      r1, [ARC_REG_DC_CTRL]
	and     r1, r1, ARC_DC_FLUSH_STATUS_BIT
	brne    r1, 0x0, dcache_flush_continue

	/* Prepare flipping.
	* After code is finished SRAM will be moved from 0x8000_0000 to 0x8800_0000,
	* and DDR from 0x0 to 0x8000_0000.
	*/
	mov     r1, RUBY_SYS_CTL_BASE_ADDR
	mov     r2, RUBY_SYS_CTL_LINUX_MAP(0x1) | RUBY_SYS_CTL_REMAP(0x3)
	st.di   r2, [r1, RUBY_SYS_CTL_MASK - RUBY_SYS_CTL_BASE_ADDR]
	mov     r2, RUBY_SYS_CTL_LINUX_MAP(0x1)

.align ARC_ICACHE_LINE_LEN
	/* Do flipping.
	* Align to cache line to ensure we don't hit memory during following instructions.
	* Code must fit into 1 cache line (32 bytes).
	*/
	st.di   r2, [r1, RUBY_SYS_CTL_CTRL - RUBY_SYS_CTL_BASE_ADDR]
	ld.di   r2, [r1, RUBY_SYS_CTL_CTRL - RUBY_SYS_CTL_BASE_ADDR] /* read back to clear pipeline */
	sync                                                         /* wait for pipeline to flush */
	j       boot_continue                                        /* jump to absolute addr 0x88xx_xxxx */
	/* Align to cache line so code occupy strictly 1 cache line. */
.align ARC_ICACHE_LINE_LEN

boot_continue:
	/* Finalize flipping. */
	mov     r2, 0x0
	st.di   r2, [r1, RUBY_SYS_CTL_MASK - RUBY_SYS_CTL_BASE_ADDR]

	/* Let's discard instruction cache.
	*/
	mov     r2, 0x1
	sr      r2, [ARC_REG_IC_IVIC] /* invalidate i-cache */
	lr      r2, [ARC_REG_IC_CTRL] /* read will be not completed until i-cache is invalidated */

	/* Done. We are now sitting in different addresses. */
	b	ruby_boot
#endif // #if RUBY_MMAP_FLIP

