/*
 * (C) Copyright 2011 Quantenna Communications Inc.
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

#include <asm/cache.h>

int lzmaBuffToBuffDecompress (unsigned char *outStream, unsigned long *uncompressedSize,
			      unsigned char *inStream,  unsigned long length);

void start_arcboot(void)
{
	extern unsigned char u_boot_mini_bin_lzma[];
	extern unsigned int u_boot_mini_bin_lzma_len;

	extern unsigned int early_flash_config_start;
	extern unsigned int early_flash_config_end;
	unsigned int *pin;
	unsigned int *pout;

	void *compressed_image = u_boot_mini_bin_lzma;
	unsigned long compressed_image_size = u_boot_mini_bin_lzma_len;
	unsigned long decompression_addr = RUBY_MINI_TEXT_BASE;
	unsigned long uncompressed_size;
	void(*start)(void);

	/* decompress u-boot mini */
	lzmaBuffToBuffDecompress((unsigned char*)decompression_addr, &uncompressed_size,
			compressed_image, compressed_image_size);

	/* copy over early config bytes */
	pin = &early_flash_config_start;
	pout = (unsigned int*)((unsigned long)pin - TEXT_BASE + decompression_addr);
	while (pin < &early_flash_config_end) {
		*pout++ = *pin++;
	}

	start = (void*)decompression_addr;

	flush_and_inv_dcache_all();
	invalidate_icache_all();

	start();
}

typedef unsigned long size_t;

void * memset(void * s,int c,size_t count)
{
	char *xs = (char *) s;

	while (count--)
		*xs++ = c;

	return s;
}

void * memcpy(void * dest,const void *src,size_t count)
{
	char *tmp = (char *) dest, *s = (char *) src;

	while (count--)
		*tmp++ = *s++;

	return dest;
}

