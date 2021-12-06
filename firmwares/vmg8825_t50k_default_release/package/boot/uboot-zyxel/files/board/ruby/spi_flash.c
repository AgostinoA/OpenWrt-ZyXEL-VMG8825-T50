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

#include "ruby.h"
#include "ruby_spi_flash_data.h"

#include <environment.h>
#include <malloc.h>

#define SWAP32(x)		((((x) & 0x000000ff) << 24) | (((x) & 0x0000ff00) << 8)| (((x) & 0x00ff0000) >>  8) | (((x) & 0xff000000) >> 24))

#define SPI_WRITE_TIMEOUT	1 /*sec*/
#define SPI_ERASE_TIMEOUT	5 /*sec*/

#define SPI_PAGE_SIZE		256

#define SPI_MEM_ADDR(addr)	(((addr) & 0x00FFFFFF) << 8)

#define SPI_FLASH_UBOOT_ADDR	0

#define SPI_FLASH_FULL_UBOOT_SIZE	(128*1024)	/* Normal Ruby u-boot partition is just under 128k */
#define SPI_FLASH_MINI_UBOOT_SIZE	(20*1024)	/* Ruby mini u-boot is 20k */

#define SPI_FLASH_TEST		1

#define SPI_FLASH_READ_BYPASS	0 /* if setted to 1, then d-cache will be bypassed when read from flash */

#if SPI_FLASH_READ_BYPASS
	#define SPI_FLASH_COPY_FROM(mem_addr, flash_addr, size) \
		io_copy_from(mem_addr, RUBY_SPI_FLASH_ADDR + flash_addr, size)
	#define SPI_FLASH_COPY_TO(flash_addr, mem_addr, size) \
		io_copy_to(RUBY_SPI_FLASH_ADDR + flash_addr, mem_addr, size)
	#define SPI_FLASH_WRITE_PREPARE(start, stop)
#else
	#define SPI_FLASH_COPY_FROM(mem_addr, flash_addr, size) \
		memcpy(mem_addr, (void*)(RUBY_SPI_FLASH_ADDR + flash_addr), size)
	#define SPI_FLASH_COPY_TO(flash_addr, mem_addr, size) \
		io_copy_to(RUBY_SPI_FLASH_ADDR + flash_addr, mem_addr, size)
	#define SPI_FLASH_WRITE_PREPARE(start, stop) \
		spi_flash_cache_inv(RUBY_SPI_FLASH_ADDR + start, RUBY_SPI_FLASH_ADDR + stop)
#endif

/* Global data. Only 1 flash can exist. */
static struct flash_info *g_spi_flash = NULL;
static u8 *g_spi_lock = NULL;

DECLARE_GLOBAL_DATA_PTR;

/* references to names in env_common.c */
extern uchar default_environment[];
extern int default_environment_size;

char * env_name_spec = "SPI Flash";
env_t *env_ptr = NULL;
#if 0
// this is for SPI1
static void spi_gpio_config(void)
{
	gpio_config(RUBY_GPIO_SPI_MISO, RUBY_GPIO_ALT_OUTPUT);
	gpio_config(RUBY_GPIO_SPI_MOSI, RUBY_GPIO_ALT_INPUT);
	gpio_config(RUBY_GPIO_SPI_SCK, RUBY_GPIO_ALT_OUTPUT);
	gpio_config(RUBY_GPIO_SPI_nCS, RUBY_GPIO_ALT_OUTPUT);
}
#endif
static void spi_ctrl_clock_config(u32 val)
{
	writel(RUBY_SYS_CTL_MASK_SPICLK, RUBY_SYS_CTL_MASK);
	writel(RUBY_SYS_CTL_SPICLK(val), RUBY_SYS_CTL_CTRL);
	writel(0x0, RUBY_SYS_CTL_MASK);

#ifdef CONFIG_SHOW_BOOT_PROGRESS
	printf("spi clock: val=0x%x ctl=0x%x\n",
		(unsigned)val,
		(unsigned)readl(RUBY_SYS_CTL_CTRL));
#endif
}

static void spi_clock_config(unsigned freq)
{
	DECLARE_GLOBAL_DATA_PTR;

	if (freq >= (gd->bus_clk / 2)) {
	         spi_ctrl_clock_config(0x0);
	} else if (freq >= (gd->bus_clk / 4)) {
	         spi_ctrl_clock_config(0x1);
	} else if(freq >= (gd->bus_clk / 8)) {
	         spi_ctrl_clock_config(0x2);
	} else {
	         spi_ctrl_clock_config(0x3);
	}
}

static inline unsigned long spi_flash_align_begin(unsigned long addr, unsigned long step)
{
	return (addr & (~(step - 1)));
}

static inline unsigned long spi_flash_align_end(unsigned long addr, unsigned long step)
{
	return ((addr + step - 1) & (~(step - 1)));
}

static inline void spi_flash_cache_inv(unsigned long begin, unsigned long end)
{
	invalidate_dcache_range(
		spi_flash_align_begin(begin, ARC_DCACHE_LINE_LEN),
		spi_flash_align_end(end, ARC_DCACHE_LINE_LEN));
}

unsigned spi_flash_size(void)
{
	unsigned ret = 0;

	if (g_spi_flash) {
		ret = g_spi_flash->sector_size * g_spi_flash->n_sectors;
	}

	return ret;
}

unsigned spi_flash_sector_size(void) 
{
	unsigned ret = 0;

	if (g_spi_flash) {
		ret = g_spi_flash->sector_size;
	}

	return ret;
}

static unsigned long spi_flash_sector_roundup(unsigned long size)
{
	unsigned long sector_size = spi_flash_sector_size();

	if (!sector_size) {
		return 0;
	}

	size = size + (sector_size - 1);
	size = size - (size % sector_size);

	return size;
}

static unsigned long spi_flash_uboot_size(void)
{
	unsigned long flash_size = spi_flash_size();

	if (!flash_size) {
		return 0;
	}

	/*
	 * Bit of a hack. We don't have partition tables in uboot;
	 * Use flash size as a heuristic to determine how big
	 * u-boot is in flash. If the flash is smaller than u-boot,
	 * we can't be using a full size u-boot.
	 */
	if (flash_size < SPI_FLASH_FULL_UBOOT_SIZE) {
		return SPI_FLASH_MINI_UBOOT_SIZE;
	}

	return SPI_FLASH_FULL_UBOOT_SIZE;
}

static unsigned long spi_flash_env_addr(void)
{
	return SPI_FLASH_UBOOT_ADDR + spi_flash_uboot_size();
}

static inline u32 spi_flash_id(void)
{
	return (SWAP32(readl(RUBY_SPI_READ_ID)) & 0xFFFFFF);
}

static inline void spi_flash_deassert_cs(void)
{
	spi_flash_id();
}

static inline void spi_flash_write_enable(void)
{
	writel(0, RUBY_SPI_WRITE_EN);
}

static inline u32 spi_flash_status(void)
{
	return (SWAP32(readl(RUBY_SPI_READ_STATUS)) & 0xFF);
}

static inline int spi_flash_ready(void)
{
	return !(spi_flash_status() & RUBY_SPI_WR_IN_PROGRESS);
}

static int spi_flash_wait_ready(int sec)
{
	DECLARE_GLOBAL_DATA_PTR;

	int ret = -1;
	int i;

	for(i = 0; i < sec; ++i) {
		ulong stamp = get_timer(0);
		while(1) {
			if(spi_flash_ready()) {
				ret = 0;
				goto done;
			} else if (get_timer(stamp) > CONFIG_SYS_HZ) {
				break;
			}
		}
	}

done:
	return ret;
}

static inline u32 spi_flash_lock_begin_sector(u32 begin)
{
	return begin / g_spi_flash->sector_size + (!!(begin % g_spi_flash->sector_size));
}

static inline u32 spi_flash_lock_end_sector(u32 end)
{
	return min(end, spi_flash_size()) / g_spi_flash->sector_size;
}

static void spi_flash_lock_fill(u32 flash_begin, u32 size, u8 val)
{
	if (g_spi_flash && g_spi_lock) {

		const u32 i_begin = spi_flash_lock_begin_sector(flash_begin);
		const u32 i_end = spi_flash_lock_end_sector(flash_begin + size);

		u32 i;
		for (i = i_begin; i < i_end; ++i) {
			g_spi_lock[i] = val;
		}
	}
}

static int spi_flash_locked(u32 flash_begin, u32 size)
{
	int ret = 0;

	if (g_spi_flash && g_spi_lock) {

		const u32 i_begin = spi_flash_lock_begin_sector(flash_begin);
		const u32 i_end = spi_flash_lock_end_sector(flash_begin + size);

		u32 i;
		for (i = i_begin; i < i_end; ++i) {
			if (g_spi_lock[i]) {
				ret = 1;
				break;
			}
		}
	}

	return ret;
}

static inline void spi_flash_lock(u32 flash_addr, u32 size)
{
	spi_flash_lock_fill(flash_addr, size, 1);
}

static inline void spi_flash_unlock(u32 flash_addr, u32 size)
{
	spi_flash_lock_fill(flash_addr, size, 0);
}

static void spi_flash_lock_prepare(void)
{
	if (!g_spi_lock && g_spi_flash) {

		/* Heap is allocated after board is inited.
		 * So this snippet must be called later.
		 */

		g_spi_lock = malloc(g_spi_flash->n_sectors);

		spi_flash_unlock(0, spi_flash_size());
		spi_flash_lock(SPI_FLASH_UBOOT_ADDR, spi_flash_uboot_size());
	}
}

static void spi_flash_probe(void)
{
	int i;
	u32 jedec_id;

	if (g_spi_lock) {
		free(g_spi_lock);
		g_spi_lock = NULL;
	}
	g_spi_flash = NULL;

	spi_clock_config(FREQ_UNKNOWN);

	jedec_id = spi_flash_id();

	for(i = 0; i < ARRAY_SIZE(flash_data); ++i) {
		if(jedec_id == flash_data[i].jedec_id) {
			g_spi_flash = flash_data + i;
			spi_clock_config(g_spi_flash->freq);
			break;
		}
	}
	if(!g_spi_flash) {
		printf("SPI flash JEDEC id is unknown: 0x%x\n", (unsigned)jedec_id);
	}
}

static int spi_flash_read_op_check(u32 flash_addr, u32 size)
{
	int ret = 0;

	if (!g_spi_flash) {
		/* No flash chip detected during probe. */
		ret = -1;
	} else if(flash_addr >= spi_flash_size()) {
		/* Adress beyond flash address space. */
		ret = -2;
	} else if(!spi_flash_ready()) {
		/* Flash is not ready. Why? */
		ret = -3;
	}

	return ret;
}

static int spi_flash_erase_op_check(u32 flash_addr, u32 size)
{
	int ret = spi_flash_read_op_check(flash_addr, size);

	if (ret) {
		/* Already error. */
	} else if (flash_addr % g_spi_flash->sector_size) {
		/* Although it is legal to have erase address
		 * inside sector, it is not very safe.
		 * Simple mistake - and neighbour sector erased.
		 */
		ret = -4;
	} else if (size % g_spi_flash->sector_size) {
		/* Same as previous case - legal but not safe. */
		ret = -5;
	} else if(spi_flash_locked(flash_addr, size)) {
		printf("Erase within locked area is not permitted. Unlock first !\n");
		ret = -6;
	}

	return ret;
}

static int spi_flash_write_op_check(u32 flash_addr, u32 size)
{
	int ret = spi_flash_read_op_check(flash_addr, size);

	if (ret) {
		/* Already error. */
	} else if(spi_flash_locked(flash_addr, size)) {
		printf("Write within locked area is not permitted. Unlock first !\n");
		ret = -4;
	}

	return ret;
}

static int spi_flash_erase(u32 flash_addr, u32 size)
{
	int ret = spi_flash_erase_op_check(flash_addr, size);

	if (!ret) {

		u32 flash_end = min(flash_addr + size, spi_flash_size());

		SPI_FLASH_WRITE_PREPARE(flash_addr, flash_end);

		if ((flash_addr == 0) && (size >= spi_flash_size())) {

			/* Bulk erase */

			spi_flash_write_enable();
			writel(0, RUBY_SPI_BULK_ERASE);

			ret = spi_flash_wait_ready(SPI_ERASE_TIMEOUT * g_spi_flash->n_sectors);

		} else {
			while (flash_addr < flash_end) {

				/* Per-sector erase */
				spi_flash_write_enable();

				if (g_spi_flash->flags & SECTOR_ERASE_OP20) {
					writel(SPI_MEM_ADDR(flash_addr), RUBY_SPI_SECTOR_ERASE_20);
				} else {
					writel(SPI_MEM_ADDR(flash_addr), RUBY_SPI_SECTOR_ERASE_D8);
				}

				flash_addr += g_spi_flash->sector_size;

				ret = spi_flash_wait_ready(SPI_ERASE_TIMEOUT);
				if (ret) {
					break;
				}
			}
		}
	}

	spi_flash_deassert_cs();

	return ret;
}

static int spi_flash_read(u32 flash_addr, u8 *mem_addr, u32 size, u32 *ret_size)
{
	int ret = spi_flash_read_op_check(flash_addr, size);

	if (!ret) {
		*ret_size = min(size, spi_flash_size() - flash_addr);
		SPI_FLASH_COPY_FROM(mem_addr, flash_addr, *ret_size);
	}

	spi_flash_deassert_cs();

	return ret;
}

static int spi_flash_write(u32 flash_addr, u8 *mem_addr, u32 size, u32 *ret_size)
{
	int ret = spi_flash_write_op_check(flash_addr, size);

	if (!ret) {

		u32 flash_end = min(flash_addr + size, spi_flash_size());

		SPI_FLASH_WRITE_PREPARE(flash_addr, flash_end);

		*ret_size = flash_end - flash_addr;

		while (flash_addr < flash_end) {

			/* Per-page programming */

			u32 write_sz = min(
					SPI_PAGE_SIZE - (flash_addr % SPI_PAGE_SIZE), /* do not exceed page boundary */
					flash_end - flash_addr); /* do not exceed requested range */

			spi_flash_write_enable();
			writel(SPI_MEM_ADDR(flash_addr), RUBY_SPI_PAGE_PROGRAM);
			SPI_FLASH_COPY_TO((void*)flash_addr, mem_addr, write_sz);
			writel(0, RUBY_SPI_COMMIT);

			flash_addr += write_sz;
			mem_addr += write_sz;

			ret = spi_flash_wait_ready(SPI_WRITE_TIMEOUT);
			if (ret) {
				break;
			}
		}
	}

	spi_flash_deassert_cs();

	return ret;
}

static int spi_flash_info(void)
{
	if (!g_spi_flash) {
		printf("No SPI flash.\n");
	} else {
		int i;
		printf("SPI flash info:\n");
		printf("\tname             : %s\n", g_spi_flash->name);
		printf("\tjedec_id         : 0x%x\n", (unsigned)g_spi_flash->jedec_id);
		printf("\tsector size      : %u\n", (unsigned)g_spi_flash->sector_size);
		printf("\tnumber of sector : %u\n", (unsigned)g_spi_flash->n_sectors);
		printf("\tfrequency        : %u\n", (unsigned)g_spi_flash->freq);
		printf("\tflags            : 0x%x\n", (unsigned)g_spi_flash->flags);
		printf("\tlock             : ");
		if (g_spi_lock) {
			for (i = 0; i < g_spi_flash->n_sectors; ++i) {
				putc(g_spi_lock[i] ? '1' : '0');
			}
		}
		putc('\n');
	}

	return 0;
}

#if SPI_FLASH_TEST

static int spi_flash_test_cmp(u32 flash_addr, u32 size, u8 val)
{
	int ret = 0;

	u32 i = 0;
	u8 read_buf[64];
	int check_latch = 1;

	for (i = flash_addr; i < size; i += sizeof(read_buf)) {

		int j;
		u32 ret_size;
		int read_ret;

		u32 read_size = min(sizeof(read_buf), size - i);

		memset(read_buf, ~val, sizeof(read_buf));

		read_ret = spi_flash_read(i, read_buf, read_size, &ret_size);

		if (read_ret) {
			ret = -1;
			printf("Read failed: %d\n", read_ret);
			goto done;
		}

		if (ret_size != read_size) {
			ret = -2;
			printf("Read failed: ret_size=%u, read_size=%u\n",
					(unsigned)ret_size, (unsigned)read_size);
			goto done;
		}

		for (j = 0; j < ret_size; ++j) {
			if (read_buf[j] != val) {
				ret = -3;
				if (check_latch) {
					printf("Byte %u value is wrong: 0x%x (must be 0x%x) (%u cache-line)\n",
							(unsigned)(i + j), (unsigned)read_buf[j],
							(unsigned)val, (unsigned)((i + j) / ARC_DCACHE_LINE_LEN));
					check_latch = 0;
				}
			} else if (!check_latch) {
				printf("Byte %u value is correct: 0x%x (%u cache-line)\n",
						(unsigned)(i + j), (unsigned)val,
						(unsigned)((i + j) / ARC_DCACHE_LINE_LEN));
				check_latch = 1;
			}
		}
	}

done:
	return ret;
}

static int spi_flash_test_set(u32 flash_addr, u32 size, u8 val)
{
	int ret = 0;

	u32 i = 0;
	u8 *page_buf = malloc(SPI_PAGE_SIZE);

	for (i = flash_addr; i < size; i += SPI_PAGE_SIZE) {

		u32 ret_size;
		int write_ret;

		memset(page_buf, val, SPI_PAGE_SIZE);

		write_ret = spi_flash_write(i, page_buf, SPI_PAGE_SIZE, &ret_size);

		if (write_ret) {
			printf("Write failed: %d\n", write_ret);
			ret = -1;
			goto done;
		}

		if (ret_size != SPI_PAGE_SIZE) {
			printf("Write failed: ret_size=%u\n", (unsigned)ret_size);
			ret = -2;
			goto done;
		}
	}

done:
	free(page_buf);
	return ret;
}

static int spi_flash_test_speed(void)
{
	int ret = 0;
	u32 size = spi_flash_size();
	u8 *read_buf = malloc(SPI_PAGE_SIZE);
	unsigned long long time = 0;
	unsigned timestamp = get_timer(0);
	int i;

	for (i = 0; i < size; i += SPI_PAGE_SIZE) {

		u32 ret_size = 0;
		u32 read_size = min(SPI_PAGE_SIZE, size - i);

		ret = spi_flash_read(i, read_buf, read_size, &ret_size);
		if (ret) {
			printf("Read failed: %d\n", ret);
			goto done;
		}

		time += get_timer(timestamp);
		timestamp = get_timer(0);
	}

done:
	printf("Ticks: %llu\n", time);
	free(read_buf);
	return ret;
}

#endif // #if SPI_FLASH_TEST

static int spi_flash_test(void)
{
	int ret = 0;

#if SPI_FLASH_TEST

	int i;

	if (!g_spi_flash) {
		printf("No SPI flash.\n");
		ret = -1;
		goto done;
	}

	printf("TEST POINT 1\n");

	ret = spi_flash_erase(0x0, spi_flash_size());
	if (ret) {
		printf("Bulk erase is failed: %d\n", ret);
		ret = -2;
		goto done;
	}

	printf("TEST POINT 2\n");

	ret = spi_flash_test_cmp(0x0, spi_flash_size(), 0xFF);
	if (ret) {
		printf("Check after bulk erase is failed: %d\n", ret);
		ret = -3;
		goto done;
	}

	printf("TEST POINT 3\n");

	ret = spi_flash_test_set(0x0, spi_flash_size(), 0xAA);
	if (ret) {
		printf("Fill with constant is failed: %d\n", ret);
		ret = -4;
		goto done;
	}

	printf("TEST POINT 4\n");

	ret = spi_flash_test_cmp(0x0, spi_flash_size(), 0xAA);
	if (ret) {
		printf("Check constant filling is failed: %d\n", ret);
		ret = -5;
		goto done;
	}

	printf("TEST POINT 5\n");

	i = 0;
	while(i < g_spi_flash->n_sectors) {
		int num = min(i + 1, g_spi_flash->n_sectors - i);
		ret = spi_flash_erase(i * g_spi_flash->sector_size, num * g_spi_flash->sector_size);
		if (ret) {
			printf("Per-sector erase is failed (%d:%d): %d\n", (int)i, (int)num, ret);
			ret = -6;
			goto done;
		}
		i += num;
	}

	printf("TEST POINT 6\n");

	ret = spi_flash_test_cmp(0x0, spi_flash_size(), 0xFF);
	if (ret) {
		printf("Check after per-sector erase is failed: %d\n", ret);
		ret = -7;
		goto done;
	}

	printf("TEST POINT 7\n");

	for (i = 0; i < 20; ++i) {
		u32 addr = get_timer(0) % (spi_flash_size() - g_spi_flash->sector_size);
		u32 sector_addr = addr / g_spi_flash->sector_size * g_spi_flash->sector_size;
		u32 size = 2 * (sector_addr + g_spi_flash->sector_size - addr);
		if (size) {

			printf("Random test: addr=0x%x size=%u : ", (unsigned)addr, (unsigned)size);

			ret = spi_flash_erase(sector_addr, 2 * g_spi_flash->sector_size);
			if (ret) {
				printf("2 sector erase is failed 0x%x: %d\n", (unsigned)sector_addr, ret);
				ret = -7;
				goto done;
			}

			ret = spi_flash_test_set(addr, size, 0x55);
			if (ret) {
				printf("Fill with constant is failed: %d\n", ret);
				ret = -8;
				goto done;
			}

			ret = spi_flash_test_cmp(addr, size, 0x55);
			if (ret) {
				printf("Check constant filling is failed: %d\n", ret);
				ret = -8;
				goto done;
			}

			ret = spi_flash_test_cmp(sector_addr, addr - sector_addr, 0xFF);
			if (ret) {
				printf("Check that constant filling is not out-of-boundary failed: %d\n", ret);
				ret = -9;
				goto done;
			}

			ret = spi_flash_test_cmp(addr + size,
					sector_addr + 2 * g_spi_flash->sector_size - addr - size, 0xFF);
			if (ret) {
				printf("Check that constant filling is not out-of-boundary failed: %d\n", ret);
				ret = -10;
				goto done;
			}

			printf("OK\n");
		}
	}

	printf("TEST POINT 8\n");

	ret = spi_flash_test_speed();
	if (ret) {
		printf("Speed test failed: %d\n", ret);
		ret = -11;
		goto done;
	}

	printf("TEST POINT 9\n");

done:
	if (ret) {
		printf("Failure: ret=%d\n", ret);
	} else {
		printf("Success!\n");
	}
#endif // #if SPI_FLASH_TEST

	return ret;
}

int do_spi_flash(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[])
{
	int ret = 0;

	if (argc < 2) {
		printf("At least one argument to command please.\n");
		ret = -1;
	} else {

		char *cmd = argv[1];

		spi_flash_lock_prepare();

		if (strcmp(cmd, "test") == 0) {

			ret = spi_flash_test();

		} else if (strcmp(cmd, "info") == 0) {

			ret = spi_flash_info();

		} else if (strcmp(cmd, "erase") == 0) {

			u32 flash_addr = (argc >= 3) ? simple_strtoul(argv[2], NULL, 0) : 0;
			u32 size = (argc >= 4) ? simple_strtoul(argv[3], NULL, 0) : spi_flash_size();

			printf("Erase: flash=0x%x size=%u\n", (unsigned)flash_addr, (unsigned)size);

			ret = spi_flash_erase(flash_addr, size);

		} else if (strcmp(cmd, "lock") == 0) {

			u32 flash_addr = (argc >= 3) ? simple_strtoul(argv[2], NULL, 0) : 0;
			u32 size = (argc >= 4) ? simple_strtoul(argv[3], NULL, 0) : spi_flash_size();

			printf("Lock: flash=0x%x size=%u\n", (unsigned)flash_addr, (unsigned)size);

			spi_flash_lock(flash_addr, size);

		} else if (strcmp(cmd, "unlock") == 0) {

			u32 flash_addr = (argc >= 3) ? simple_strtoul(argv[2], NULL, 0) : 0;
			u32 size = (argc >= 4) ? simple_strtoul(argv[3], NULL, 0) : spi_flash_size();

			printf("Unlock: flash=0x%x size=%u\n", (unsigned)flash_addr, (unsigned)size);

			spi_flash_unlock(flash_addr, size);

		} else if (argc != 5) {
			printf("Not enough arguments.\n");
			ret = -2;
		} else {
			u32 ret_size = 0;
			u32 flash_addr = simple_strtoul(argv[2], NULL, 0);
			u8 *mem_addr = (u8*)simple_strtoul(argv[3], NULL, 0);
			u32 size = simple_strtoul(argv[4], NULL, 0);

			if (strcmp(cmd, "read") == 0) {
				printf("Read: ");
				ret = spi_flash_read(flash_addr, mem_addr, size, &ret_size);
			} else if (strcmp(cmd, "write") == 0) {
				printf("Write: ");
				ret = spi_flash_write(flash_addr, mem_addr, size, &ret_size);
			} else {
				printf("Unsupported '%s' command: ", cmd);
				ret = -3;
			}

			if (!ret) {
				printf("flash=0x%x mem=0x%x size=%u ret_size=%u\n",
						(unsigned)flash_addr, (unsigned)mem_addr, (unsigned)size, (unsigned)ret_size);
			}
		}

		if (ret) {
			printf("'%s' : failed : ret=%d\n", cmd, (int)ret);
		}
	}

	return ret;
}

U_BOOT_CMD(spi_flash, 5, 0, do_spi_flash,
		"SPI flash sub-system",
		"spi_flash info                           - show available SPI flash\n"
		"spi_flash test                           - test flash (DESTROY ALL DATA ON FLASH!)\n"
		"spi_flash read flash_addr mem_addr size  - read data from flash to memory\n"
		"spi_flash write flash_addr mem_addr size - write data from memory to flash\n"
		"spi_flash erase [flash_addr len]         - erase flash\n"
		"spi_flash lock [flash_addr len]          - lock flash (granularity is sector size)\n"
		"spi_flash unlock [flash_addr len]        - unlock flash (granularity is sector size)\n"
	  );

void board_spi_flash_init(void)
{
	spi_flash_probe();

#ifdef CONFIG_SHOW_BOOT_PROGRESS
	(void)spi_flash_info();
#endif
}

int saveenv(void)
{
	u32 size, flash_addr, ret_size;
	int ret;

	if ((gd->env_valid == 0) || (env_ptr == NULL)) {
		puts("Environment SPI flash not initialized properly!!!\n");
		return 1;
	}

	flash_addr = spi_flash_env_addr();
	size = spi_flash_sector_roundup(CONFIG_ENV_SIZE);

	printf("Erasing SPI flash env, %d bytes at 0x%x...", size, flash_addr);
	ret = spi_flash_erase( flash_addr, size );
	if ( ret ) {
		printf("Error along the way #1 - %d\n", ret);
		goto done;
	}
	size = CONFIG_ENV_SIZE;
	printf("Writing to SPI flash...");
	ret = spi_flash_write( flash_addr, (u8 *)env_ptr, size, &ret_size );
	if ( ret ) {
		printf("Error along the way #2 - %d\n", ret);
		goto done;
	}
	ret = 0;
	puts("done\n");
done:
	return ret;
}

void env_relocate_spec (void)
{
	u32 len, flash_addr = spi_flash_env_addr();

	spi_flash_read( flash_addr, (u8 *)env_ptr, CONFIG_ENV_SIZE, &len);
}

uchar env_get_char_spec (int index)
{
	return ( *((uchar *)(gd->env_addr + index)) );
}

/************************************************************************
 * Initialize Environment use
 *
 * We are still running from ROM, so data use is limited
 */
int  env_init(void)
{
	u32 crc, len, ret_len, new, flash_addr;
	unsigned off;
	uchar buf[64];

	if (gd->env_valid == 0) {
		len = sizeof(ulong);
		flash_addr = spi_flash_env_addr();
		flash_addr += offsetof(env_t,crc);
		/* read old CRC */
		spi_flash_read( flash_addr, (u8 *)&crc, len, &ret_len);
		new = 0;
		len = ENV_SIZE;
		printf("env size = 0x%x\n", len);
		flash_addr = spi_flash_env_addr();
		off = offsetof(env_t,data);
		while (len > 0) {
			int n = (len > sizeof(buf)) ? sizeof(buf) : len;
			spi_flash_read( flash_addr+off, buf, n, &ret_len);
			new = crc32 (new, buf, n);
			len -= n;
			off += n;
		}
		if (crc == new) {
			printf("Valid CRC found in flash restoring env...\n");
			// gd->env_addr  = offsetof(env_t,data); - malloced later...
			gd->env_valid = 1;
		} else {
			printf("Invalid CRC in flash using default env...\n");
			gd->env_addr  = (ulong)&default_environment[0];
			gd->env_valid = 0;
		}
	}
	return (0);
}

// one-time env upgrade code
int do_updateenv (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	env_relocate_spec();
	env_ptr->crc = crc32(0, env_ptr->data, ENV_SIZE);
	gd->env_valid = 1;
	printf ("Upgrading Environment ...\n");
	saveenv();

	return 0;
}

U_BOOT_CMD(
	upgradeenv, 1, 0,	do_updateenv,
	"upgrade environment",
	NULL
);

int do_updatecrc(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	env_crc_update();
	gd->env_valid = 1;

	return 0;
}

U_BOOT_CMD(
	updatecrc, 1, 0, do_updatecrc,
	"update CRC",
	NULL
);
