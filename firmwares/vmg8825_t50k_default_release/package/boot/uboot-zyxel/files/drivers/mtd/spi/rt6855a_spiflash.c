#include <common.h>
#include <malloc.h>
#include <spi_flash.h>

#include <asm/arch/rt_mmap.h>
#include "rt6855a_spiflash.h"


/* Choose the SPI flash mode */
#define BBU_MODE        // BBU SPI flash controller
#define MORE_BUF_MODE

/******************************************************************************
 * SPI FLASH elementray definition and function
 ******************************************************************************/

#define FLASH_PAGESIZE		256
#define MX_4B_MODE			/* MXIC 4 Byte Mode */

/* Flash opcodes. */
#define OPCODE_WREN		6	/* Write enable */
#define OPCODE_WRDI		4	/* Write disable */
#define OPCODE_RDSR		5	/* Read status register */
#define OPCODE_WRSR		1	/* Write status register */
#define OPCODE_READ		3	/* Read data bytes */
#define OPCODE_PP		2	/* Page program */
#define OPCODE_SE		0xD8	/* Sector erase */
#define OPCODE_RES		0xAB	/* Read Electronic Signature */
#define OPCODE_RDID		0x9F	/* Read JEDEC ID */

#define OPCODE_FAST_READ	0x0B		/* Fast Read */
#define OPCODE_DOR			0x3B	/* Dual Output Read */
#define OPCODE_QOR			0x6B	/* Quad Output Read */
#define OPCODE_DIOR			0xBB	/* Dual IO High Performance Read */
#define OPCODE_QIOR			0xEB	/* Quad IO High Performance Read */
#define OPCODE_READ_ID		0x90	/* Read Manufacturer and Device ID */

#define OPCODE_P4E			0x20	/* 4KB Parameter Sectore Erase */
#define OPCODE_P8E			0x40	/* 8KB Parameter Sectore Erase */
#define OPCODE_BE			0x60	/* Bulk Erase */
#define OPCODE_BE1			0xC7	/* Bulk Erase */
#define OPCODE_QPP			0x32	/* Quad Page Programing */

#define OPCODE_CLSR			0x30
#define OPCODE_RCR			0x35	/* Read Configuration Register */

/* Status Register bits. */
#define SR_WIP			1	/* Write in progress */
#define SR_WEL			2	/* Write enable latch */
#define SR_BP0			4	/* Block protect 0 */
#define SR_BP1			8	/* Block protect 1 */
#define SR_BP2			0x10	/* Block protect 2 */
#define SR_EPE			0x20	/* Erase/Program error */
#define SR_SRWD			0x80	/* SR write protect */

#define ra_dbg(args...)
//#define ra_dbg(args...) do { if (1) printf(args); } while(0)

#define SPI_FIFO_SIZE 16

//#define ADDR_4B		// if all instruction use 4B address mode
//#define RD_MODE_FAST		// use Fast Read instead of normal Read
//#define RD_MODE_DIOR		// use DIOR (0xBB)instead of normal Read
//#define RD_MODE_DOR		// use DOR (0x3B) instead of normal Read
//#define RD_MODE_QIOR		// use QIOR (0xEB) instead of normal Read
//#define RD_MODE_QOR		// use QOR (0x6B) instead of normal Read

#if defined(RD_MODE_QOR) || defined(RD_MODE_QIOR)
#define RD_MODE_QUAD
#endif


#define SPIC_READ_BYTES (1<<0)
#define SPIC_WRITE_BYTES (1<<1)
#define SPIC_USER_MODE (1<<2)
#define SPIC_4B_ADDR (1<<3)

extern unsigned long mips_bus_feq;
struct chip_info {
	char		*name;
	u8		id;
	u32		jedec_id;
	unsigned long	sector_size;
	unsigned int	n_sectors;
	char		addr4b;
};
struct chip_info const *spi_chip_info = NULL;

static const struct chip_info chips_data [] = {
	/* REVISIT: fill in JEDEC ids, for parts that have them */
	{ "AT25DF321",		0x1f, 0x47000000, 64 * 1024, 64,  0 },
	{ "AT26DF161",		0x1f, 0x46000000, 64 * 1024, 32,  0 },
	{ "FL016AIF",		0x01, 0x02140000, 64 * 1024, 32,  0 },
	{ "FL064AIF",		0x01, 0x02160000, 64 * 1024, 128, 0 },
	{ "MX25L1605D",		0xc2, 0x2015c220, 64 * 1024, 32,  0 },
	{ "MX25L3205D",		0xc2, 0x2016c220, 64 * 1024, 64,  0 },
	{ "MX25L6405D",		0xc2, 0x2017c220, 64 * 1024, 128, 0 },
	{ "MX25L12805D",	0xc2, 0x2018c220, 64 * 1024, 256, 0 },
#ifdef MX_4B_MODE 
	{ "MX25L25635E",	0xc2, 0x2019c220, 64 * 1024, 512, 1 },
#endif
	{ "S25FL128P",		0x01, 0x20180301, 64 * 1024, 256, 0 },
	{ "S25FL129P",		0x01, 0x20184D01, 64 * 1024, 256, 0 },
	{ "S25FL032P",		0x01, 0x02154D00, 64 * 1024, 64,  0 },
	{ "S25FL064P",		0x01, 0x02164D00, 64 * 1024, 128, 0 },
	{ "EN25F16",		0x1c, 0x31151c31, 64 * 1024, 32,  0 },
	{ "EN25F32",		0x1c, 0x31161c31, 64 * 1024, 64,  0 },
	{ "EN25Q32",        0x1c, 0x30161c30, 64 * 1024, 64,  0 },
	{ "EN25F64",		0x1c, 0x20171c20, 64 * 1024, 128,  0 }, //EN25P64
	{ "EN25Q64",		0x1c, 0x30171c30, 64 * 1024, 128,  0 },
	{ "W25Q32BV",		0xef, 0x40160000, 64 * 1024, 64,  0 },
	{ "W25Q64BV",		0xef, 0x40170000, 64 * 1024, 128,  0 }, //S25FL064K
};

/* spi_flash needs to be first so upper layers can free() it */
struct rt6855a_spi_flash {
	struct spi_flash flash;
	const struct chip_info *params;
};

static inline struct rt6855a_spi_flash *to_rt6855a_spi_flash(struct spi_flash *flash)
{
	return container_of(flash, struct rt6855a_spi_flash, flash);
}


static int bbu_spic_busy_wait(void)
{
	int n = 100000;
	do {
		if ((ra_inl(SPI_REG_CTL) & SPI_CTL_BUSY) == 0)
			return 0;
		udelay(1);
	} while (--n > 0);

	printf("%s: fail \n", __func__);
	return -1;
}

void spic_init(void)
{
	// enable SMC bank 0 alias addressing
	ra_or(RALINK_SYSCTL_BASE + 0x38, 0x80000000);
}

#ifdef MORE_BUF_MODE
static int bbu_mb_spic_trans(const u8 code, const u32 addr, u8 *buf, const size_t n_tx, const size_t n_rx, int flag)
{
	u32 reg;
	int i, q, r;
	int rc = -1;

	if (flag != SPIC_READ_BYTES && flag != SPIC_WRITE_BYTES) {
		printf("we currently support more-byte-mode for reading and writing data only\n");
		return -1;
	}

	/* step 0. enable more byte mode */
	ra_or(SPI_REG_MASTER, (1 << 2));

	bbu_spic_busy_wait();

	/* step 1. set opcode & address, and fix cmd bit count to 32 (or 40) */
#ifdef MX_4B_MODE 
	if (spi_chip_info && spi_chip_info->addr4b) {
		ra_and(SPI_REG_CTL, ~SPI_CTL_ADDREXT_MASK);
		ra_or(SPI_REG_CTL, (code << 24) & SPI_CTL_ADDREXT_MASK);
		ra_outl(SPI_REG_OPCODE, addr);
	}
	else
#endif
	{
		ra_outl(SPI_REG_OPCODE, (code << 24) & 0xff000000);
		ra_or(SPI_REG_OPCODE, (addr & 0xffffff));
	}
	ra_and(SPI_REG_MOREBUF, ~SPI_MBCTL_CMD_MASK);
#ifdef MX_4B_MODE 
	if (spi_chip_info && spi_chip_info->addr4b)
		ra_or(SPI_REG_MOREBUF, (40 << 24));
	else
#endif
		ra_or(SPI_REG_MOREBUF, (32 << 24));

	/* step 2. write DI/DO data #0 ~ #7 */
	if (flag & SPIC_WRITE_BYTES) {
		if (buf == NULL) {
			printf("%s: write null buf\n", __func__);
			goto RET_MB_TRANS;
		}
		for (i = 0; i < n_tx; i++) {
			q = i / 4;
			r = i % 4;
			if (r == 0)
				ra_outl(SPI_REG_DATA(q), 0);
			ra_or(SPI_REG_DATA(q), (*(buf + i) << (r * 8)));
		}
	}

	/* step 3. set rx (miso_bit_cnt) and tx (mosi_bit_cnt) bit count */
	ra_and(SPI_REG_MOREBUF, ~SPI_MBCTL_TX_RX_CNT_MASK);
	ra_or(SPI_REG_MOREBUF, (n_rx << 3 << 12));
	ra_or(SPI_REG_MOREBUF, n_tx << 3);

	/* step 4. kick */
	ra_or(SPI_REG_CTL, SPI_CTL_START);

	/* step 5. wait spi_master_busy */
	bbu_spic_busy_wait();
	if (flag & SPIC_WRITE_BYTES) {
		rc = 0;
		goto RET_MB_TRANS;
	}

	/* step 6. read DI/DO data #0 */
	if (flag & SPIC_READ_BYTES) {
		if (buf == NULL) {
			printf("%s: read null buf\n", __func__);
			return -1;
		}
		for (i = 0; i < n_rx; i++) {
			q = i / 4;
			r = i % 4;
			reg = ra_inl(SPI_REG_DATA(q));
			*(buf + i) = (u8)(reg >> (r * 8));
		}
	}

	rc = 0;
RET_MB_TRANS:
	/* step #. disable more byte mode */
	ra_and(SPI_REG_MASTER, ~(1 << 2));
	return rc;
}
#endif // MORE_BUF_MODE //

static int bbu_spic_trans(const u8 code, const u32 addr, u8 *buf, const size_t n_tx, const size_t n_rx, int flag)
{
	u32 reg;

	bbu_spic_busy_wait();

	/* step 1. set opcode & address */
#ifdef MX_4B_MODE 
	if (spi_chip_info && spi_chip_info->addr4b) {
		ra_and(SPI_REG_CTL, ~SPI_CTL_ADDREXT_MASK);
		ra_or(SPI_REG_CTL, addr & SPI_CTL_ADDREXT_MASK);
	}
#endif
	ra_outl(SPI_REG_OPCODE, ((addr & 0xffffff) << 8));
	ra_or(SPI_REG_OPCODE, code);

	/* step 2. write DI/DO data #0 */
	if (flag & SPIC_WRITE_BYTES) {
		if (buf == NULL) {
			printf("%s: write null buf\n", __func__);
			return -1;
		}
		ra_outl(SPI_REG_DATA0, 0);
		switch (n_tx) {
		case 8:
			ra_or(SPI_REG_DATA0, (*(buf+3) << 24));
		case 7:
			ra_or(SPI_REG_DATA0, (*(buf+2) << 16));
		case 6:
			ra_or(SPI_REG_DATA0, (*(buf+1) << 8));
		case 5:
		case 2:
			ra_or(SPI_REG_DATA0, *buf);
			break;
		default:
			printf("%s: fixme, write of length %d\n", __func__, n_tx);
			return -1;
		}
	}

	/* step 3. set mosi_byte_cnt */
	ra_and(SPI_REG_CTL, ~SPI_CTL_TX_RX_CNT_MASK);
	ra_or(SPI_REG_CTL, (n_rx << 4));
#ifdef MX_4B_MODE 
	if (spi_chip_info && spi_chip_info->addr4b && n_tx >= 4)
		ra_or(SPI_REG_CTL, (n_tx + 1));
	else
#endif
		ra_or(SPI_REG_CTL, n_tx);

	/* step 4. kick */
	ra_or(SPI_REG_CTL, SPI_CTL_START);

	/* step 5. wait spi_master_busy */
	bbu_spic_busy_wait();
	if (flag & SPIC_WRITE_BYTES)
		return 0;

	/* step 6. read DI/DO data #0 */
	if (flag & SPIC_READ_BYTES) {
		if (buf == NULL) {
			printf("%s: read null buf\n", __func__);
			return -1;
		}
		reg = ra_inl(SPI_REG_DATA0);
		switch (n_rx) {
		case 4:
			*(buf+3) = (u8)(reg >> 24);
		case 3:
			*(buf+2) = (u8)(reg >> 16);
		case 2:
			*(buf+1) = (u8)(reg >> 8);
		case 1:
			*buf = (u8)reg;
			break;
		default:
			printf("%s: fixme, read of length %d\n", __func__, n_rx);
			return -1;
		}
	}
	return 0;
}

/*
 * read SPI flash device ID
 */
static int raspi_read_devid(u8 *rxbuf, int n_rx)
{
	u8 code = OPCODE_RDID;
	int retval;

	retval = bbu_spic_trans(code, 0, rxbuf, 1, 3, SPIC_READ_BYTES);
	if (!retval)
		retval = n_rx;

    if (retval != n_rx) {
		printf("%s: ret: %x\n", __func__, retval);
		return retval;
	}
	return retval;
}

/*
 * read status register
 */
static int raspi_read_sr(u8 *val)
{
	ssize_t retval;
	u8 code = OPCODE_RDSR;

	retval = bbu_spic_trans(code, 0, val, 1, 1, SPIC_READ_BYTES);
	return retval;

    if (retval != 1) {
		printf("%s: ret: %x\n", __func__, retval);
		return -1;
	}
	return 0;
}

/*
 * write status register
 */
static int raspi_write_sr(u8 *val)
{
	ssize_t retval;
	u8 code = OPCODE_WRSR;

	retval = bbu_spic_trans(code, 0, val, 2, 0, SPIC_WRITE_BYTES);

    if (retval != 1) {
		printf("%s: ret: %x\n", __func__, retval);
		return -1;
	}
	return 0;
}

#if 0
static int raspi_cear_sr(void)
{
	u8 code = OPCODE_CLSR;

	bbu_spic_trans(code, 0, NULL, 1, 0, 0);

    return 0;
}
#endif

#ifdef MX_4B_MODE
static int raspi_read_scur(u8 *val)
{
	ssize_t retval = -1;
	u8 code = 0x2b;

	retval = bbu_spic_trans(code, 0, val, 1, 1, SPIC_READ_BYTES);

    if (retval != 1) {
		printf("%s: ret: %x\n", __func__, retval);
		return -1;
	}
	return 0;
}

static int raspi_4byte_mode(int enable)
{
	ssize_t retval;
	u8 code;

	code = enable? 0xB7 : 0xE9; /* B7: enter 4B, E9: exit 4B */

	if (enable) {
		ra_or(SPI_REG_CTL, 0x3 << 19);
		ra_or(SPI_REG_Q_CTL, 0x3 << 8);
	}
	else {
		ra_and(SPI_REG_CTL, ~SPI_CTL_SIZE_MASK);
		ra_or(SPI_REG_CTL, 0x2 << 19);
		ra_and(SPI_REG_Q_CTL, ~(0x3 << 8));
		ra_or(SPI_REG_Q_CTL, 0x2 << 8);
	}
	retval = bbu_spic_trans(code, 0, NULL, 1, 0, 0);

    if (retval != 0) {
		printf("%s: ret: %x\n", __func__, retval);
		return -1;
	}
	return 0;
}
#endif // MX_4B_MODE //

/*
 * Set write enable latch with Write Enable command.
 * Returns negative if error occurred.
 */
static inline int raspi_write_enable(void)
{
	u8 code = OPCODE_WREN;

	return bbu_spic_trans(code, 0, NULL, 1, 0, 0);
}

static inline int raspi_write_disable(void)
{
	u8 code = OPCODE_WRDI;

	return bbu_spic_trans(code, 0, NULL, 1, 0, 0);
}

/*
 * Set all sectors (global) unprotected if they are protected.
 * Returns negative if error occurred.
 */
static inline int raspi_unprotect(void)
{
	u8 sr = 0;

	if (raspi_read_sr(&sr) < 0) {
		printf("%s: read_sr fail: %x\n", __func__, sr);
		return -1;
	}

	if ((sr & (SR_BP0 | SR_BP1 | SR_BP2)) != 0) {
		sr = 0;
		raspi_write_sr(&sr);
	}
	return 0;
}

/*
 * Service routine to read status register until ready, or timeout occurs.
 * Returns non-zero if error.
 */
static int raspi_wait_ready(int sleep_ms)
{
	int count;
	int sr = 0;

	//udelay(1000 * sleep_ms);

	/* one chip guarantees max 5 msec wait here after page writes,
	 * but potentially three seconds (!) after page erase.
	 */
	for (count = 0; count < ((sleep_ms+1) *1000); count++) {
		if ((raspi_read_sr((u8 *)&sr)) < 0)
			break;
		else if (!(sr & (SR_WIP | SR_EPE | SR_WEL))) {
			return 0;
		}

		udelay(500);
		/* REVISIT sometimes sleeping would be best */
	}

	printf("%s: read_sr fail: %x\n", __func__, sr);
	return -1;
}

/*
 * Erase one sector of flash memory at offset ``offset'' which is any
 * address within the sector which should be erased.
 *
 * Returns 0 if successful, non-zero otherwise.
 */
static int raspi_erase_sector(u32 offset)
{
	/* Wait until finished previous write command. */
	if (raspi_wait_ready(950))
		return -1;

	/* Send write enable, then erase commands. */
	raspi_write_enable();
	raspi_unprotect();

#ifdef MX_4B_MODE 
	if (spi_chip_info->addr4b)
		raspi_4byte_mode(1);
#endif
	bbu_spic_trans(STM_OP_SECTOR_ERASE, offset, NULL, 4, 0, 0);
#ifdef MX_4B_MODE 
	if (spi_chip_info->addr4b)
		raspi_4byte_mode(0);
#endif

    raspi_write_disable();

	return 0;
}

static int raspi_erase(unsigned long offs, unsigned long len, int silent)
{
	ra_dbg("%s: offs:%lx len:%lx\n", __func__, offs, len);

	/* sanity checks */
	if (len == 0)
		return 0;
	if ((offs%spi_chip_info->sector_size) || (len%spi_chip_info->sector_size)) {
		printf("SPI Flash: offset and length must be align to 0x%08lX\n", spi_chip_info->sector_size);
		return -1;
	}
	/* now erase those sectors */
	if (!silent) printf("\nSPI Flash: erase offset 0x%08lX,len %lu\n", offs, len);
	while (len > 0) {
		if (raspi_erase_sector(offs)) {
			if (!silent) printf(" failed.\n");
			return -1;
		}

		offs += spi_chip_info->sector_size;
		len -= spi_chip_info->sector_size;
		if (!silent) putc('.');
	}
	if (!silent) printf(" OK.\n");

	return 0;
}

static unsigned long raspi_read(char *buf, unsigned long from, unsigned long len, int silent)
{
	unsigned long rdlen = 0;

	ra_dbg("%s: from:%lx len:%lx \n", __func__, from, len);

	/* sanity checks */
	if (len == 0)
		return 0;
#ifdef MORE_BUF_MODE
	if ((from%32) || (len%32)) {
		printf("SPI Flash: offset and length must be align to 32\n");
		return 0;
	}
#else
	if ((from%4) || (len%4)) {
		printf("SPI Flash: offset and length must be align to 4\n");
		return 0;
	}
#endif

	/* Wait till previous write/erase is done. */
	if (raspi_wait_ready(1)) {
		/* REVISIT status return?? */
		ra_dbg("%s: SPI bus not ready!\n", __func__);
		return 0;
	}

#ifdef MX_4B_MODE 
	if (spi_chip_info->addr4b)
		raspi_4byte_mode(1);
#endif
	if (!silent) printf("\nSPI Flash: read offset 0x%08lX to memory 0x%p,len %lu\n", from, buf, len);
	do {
		int rc, more;
#ifdef MORE_BUF_MODE
		more = 32;
#else
		more = 4;
#endif
		if (len - rdlen <= more) {
#ifdef MORE_BUF_MODE
			rc = bbu_mb_spic_trans(STM_OP_RD_DATA, from, (u8 *)(buf+rdlen), 0, (len-rdlen), SPIC_READ_BYTES);
#else
			rc = bbu_spic_trans(STM_OP_RD_DATA, from, (buf+rdlen), 4, (len-rdlen), SPIC_READ_BYTES);
#endif
			if (rc != 0) {
				printf("%s: failed\n", __func__);
				break;
			}
			rdlen = len;
			if (!silent) putc('.');
		}
		else {
#ifdef MORE_BUF_MODE
			rc = bbu_mb_spic_trans(STM_OP_RD_DATA, from, (u8 *)(buf+rdlen), 0, more, SPIC_READ_BYTES);
#else
			rc = bbu_spic_trans(STM_OP_RD_DATA, from, (buf+rdlen), 4, more, SPIC_READ_BYTES);
#endif
			if (rc != 0) {
				printf("%s: failed\n", __func__);
				break;
			}
			rdlen += more;
			from += more;
			if (!silent && (rdlen%spi_chip_info->sector_size==0)) putc('.');
		}
	} while (rdlen < len);
#ifdef MX_4B_MODE 
	if (spi_chip_info->addr4b)
		raspi_4byte_mode(0);
#endif

	if (!silent) printf(" %s.\n", rdlen==len?"OK":"failed");
	return rdlen;
}

unsigned long raspi_write(char *buf, unsigned long to, unsigned long len, int silent)
{
	u32 page_offset, page_size;
	int rc = 0, more;
	unsigned long wrto, wrlen, orglen, retlen = 0;
	char *wrbuf;

	ra_dbg("%s: to:%x len:%x \n", __func__, to, len);

	/* sanity checks */
	if (len == 0)
		return 0;
	if (to + len > spi_chip_info->sector_size * spi_chip_info->n_sectors)
		return -1;
#ifdef MORE_BUF_MODE
	if ((to%32) || (len%32)) {
		printf("SPI Flash: offset and length must be align to 32\n");
		return 0;
	}
#else
	if ((to%4) || (len%4)) {
		printf("SPI Flash: offset and length must be align to 4\n");
		return 0;
	}
#endif
	orglen = len;
	/* Wait until finished previous write command. */
	if (raspi_wait_ready(2))
		return 0;

	/* what page do we start with? */
	page_offset = to % FLASH_PAGESIZE;

#ifdef MX_4B_MODE
	if (spi_chip_info->addr4b)
		raspi_4byte_mode(1);
#endif

	if (!silent) printf("\nSPI Flash: write memory 0x%p to offset 0x%08lX,len %lu\n", buf, to, len);
	/* write everything in PAGESIZE chunks */
	while (len > 0) {
		page_size = min(len, FLASH_PAGESIZE-page_offset);
		page_offset = 0;

		/* write the next page to flash */
		raspi_wait_ready(3);
		raspi_write_enable();
		raspi_unprotect();

		wrto = to;
		wrlen = page_size;
		wrbuf = buf;
		do {
#ifdef MORE_BUF_MODE
			more = 32;
#else
			more = 4;
#endif
			if (wrlen <= more) {
#ifdef MORE_BUF_MODE
				bbu_mb_spic_trans(STM_OP_PAGE_PGRM, wrto, (u8 *)wrbuf, wrlen, 0, SPIC_WRITE_BYTES);
#else
				bbu_spic_trans(STM_OP_PAGE_PGRM, wrto, wrbuf, wrlen+4, 0, SPIC_WRITE_BYTES);
#endif
				retlen += wrlen;
				wrlen = 0;
			}
			else {
#ifdef MORE_BUF_MODE
				bbu_mb_spic_trans(STM_OP_PAGE_PGRM, wrto, (u8 *)wrbuf, more, 0, SPIC_WRITE_BYTES);
#else
				bbu_spic_trans(STM_OP_PAGE_PGRM, wrto, wrbuf, more+4, 0, SPIC_WRITE_BYTES);
#endif
				retlen += more;
				wrto += more;
				wrlen -= more;
				wrbuf += more;
			}
			if (wrlen > 0) {
				raspi_write_disable();
				raspi_wait_ready(3);
				raspi_write_enable();
			}
		} while (wrlen > 0);

		//printf("%s:: to:%x page_size:%x ret:%x\n", __func__, to, page_size, rc);
		if ((retlen & 0xffff) == 0)
			if (!silent) printf(".");

		if (rc > 0) {
			retlen += rc;
			if (rc < page_size) {
				printf("%s: rc:%x page_size:%x\n",
						__func__, rc, page_size);
				return retlen;
			}
		}

		len -= page_size;
		to += page_size;
		buf += page_size;
	}
	if (!silent) printf(" %s.\n", retlen==orglen?"OK":"failed");
#ifdef MX_4B_MODE
	if (spi_chip_info->addr4b)
		raspi_4byte_mode(0);
#endif

	raspi_write_disable();

	return retlen;
}

#if 0
int raspi_erase_write(char *buf, unsigned int offs, int count)
{
	int blocksize = spi_chip_info->sector_size;
	int blockmask = blocksize - 1;

	ra_dbg("%s: offs:%x, count:%x\n", __func__, offs, count);

	if (count > (spi_chip_info->sector_size * spi_chip_info->n_sectors) -
			(CFG_BOOTLOADER_SIZE + CFG_CONFIG_SIZE + CFG_FACTORY_SIZE)) {
		printf("Abort: image size larger than %d!\n\n", (spi_chip_info->sector_size * spi_chip_info->n_sectors) -
				(CFG_BOOTLOADER_SIZE + CFG_CONFIG_SIZE + CFG_FACTORY_SIZE));
		udelay(10*1000*1000);
		return -1;
	}

	while (count > 0) {
#define BLOCK_ALIGNE(a) (((a) & blockmask))
		if (BLOCK_ALIGNE(offs) || (count < blocksize)) {
			char *block;
			unsigned int piece, blockaddr;
			int piece_size;
			char *temp;
		
			block = malloc(blocksize);
			if (!block)
				return -1;
			temp = malloc(blocksize);
			if (!temp)
				return -1;

			blockaddr = offs & ~blockmask;

			if (raspi_read(block, blockaddr, blocksize) != blocksize) {
				free(block);
				free(temp);
				return -2;
			}

			piece = offs & blockmask;
			piece_size = min(count, blocksize - piece);
			memcpy(block + piece, buf, piece_size);

			if (raspi_erase(blockaddr, blocksize) != 0) {
				free(block);
				free(temp);
				return -3;
			}
			if (raspi_write(block, blockaddr, blocksize) != blocksize) {
				free(block);
				free(temp);
				return -4;
			}
#ifdef RALINK_SPI_UPGRADE_CHECK
			if (raspi_read(temp, blockaddr, blocksize) != blocksize) {
				free(block);
				free(temp);
				return -2;
			}


			if(memcmp(block, temp, blocksize) == 0)
			{    
			   // printf("block write ok!\n\r");
			}
			else
			{
				printf("block write incorrect!\n\r");
				free(block);
				free(temp);
				return -2;
			}
#endif
                        free(temp);
			free(block);

			buf += piece_size;
			offs += piece_size;
			count -= piece_size;
		}
		else {
			unsigned int aligned_size = count & ~blockmask;
			char *temp;
			int i;
			temp = malloc(blocksize);
			if (!temp)
				return -1;

			if (raspi_erase(offs, aligned_size) != 0)
			{
				free(temp);
				return -1;
			}
			if (raspi_write(buf, offs, aligned_size) != aligned_size)
			{
				free(temp);
				return -1;
			}

#ifdef RALINK_SPI_UPGRADE_CHECK
			for( i=0; i< (aligned_size/blocksize); i++)
			{
				if (raspi_read(temp, offs+(i*blocksize), blocksize) != blocksize)
				{
					free(temp);
					return -2;
				}
				if(memcmp(buf+(i*blocksize), temp, blocksize) == 0)
				{
				//	printf("blocksize write ok i=%d!\n\r", i);
				}
				else
				{
					printf("blocksize write incorrect block#=%d!\n\r",i);
					free(temp);
					return -2;
				}
			}
#endif
			free(temp);
	
			buf += aligned_size;
			offs += aligned_size;
			count -= aligned_size;
		}
	}
	printf("Done!\n");
	return 0;
}
#endif

#ifdef CONFIG_RT6855A_SPI_FLASH_DBG_CMD
static int ralink_spi_command(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	if (!strncmp(argv[1], "id", 3)) {
		u8 buf[5];
		raspi_read_devid(buf, 5);
		printf("device id: %x %x %x %x %x\n", buf[0], buf[1], buf[2], buf[3], buf[4]);
	}
	else if (!strncmp(argv[1], "read", 5)) {
		unsigned int addr, len;
		u8 *p;
		int i;

		addr = simple_strtoul(argv[2], NULL, 16);
		len = simple_strtoul(argv[3], NULL, 16);
		p = (u8 *)malloc(len);
		if (!p) {
			printf("malloc error\n");
			return 0;
		}
		len = raspi_read(p, addr, len); //reuse len
		printf("read len: %d\n", len);
		for (i = 0; i < len; i++) {
			printf("%x ", p[i]);
		}
		printf("\n");
		free(p);
	}
	else if (!strncmp(argv[1], "erase", 6)) {
		unsigned int o, l;
		o = simple_strtoul(argv[2], NULL, 16);
		l = simple_strtoul(argv[3], NULL, 16);
		printf("erase offs 0x%x, len 0x%x\n", o, l);
		raspi_erase(o, l);
	}
	else if (!strncmp(argv[1], "write", 6)) {
		unsigned int o, l;
		u8 *p, t[3] = {0};
		int i;

		o = simple_strtoul(argv[2], NULL, 16);
		l = strlen(argv[3]) / 2;
		p = (u8 *)malloc(l);
		if (!p) {
			printf("malloc error\n");
			return 0;
		}
		for (i = 0; i < l; i++) {
			t[0] = argv[3][2*i];
			t[1] = argv[3][2*i+1];
			*(p + i) = simple_strtoul(t, NULL, 16);
		}
		printf("write offs 0x%x, len 0x%x\n", o, l);
		raspi_write(p, o, l);
		free(p);
	}
	else if (!strncmp(argv[1], "sr", 3)) {
		u8 sr;
		if (!strncmp(argv[2], "read", 5)) {
			if (raspi_read_sr(&sr) < 0)
				printf("read sr failed\n");
			else
				printf("sr %x\n", sr);
		}
		else if (!strncmp(argv[2], "write", 6)) {
			sr = (u8)simple_strtoul(argv[3], NULL, 16);
			printf("trying write sr %x\n", sr);
			if (raspi_write_sr(&sr) < 0)
				printf("write sr failed\n");
			else {
				if (raspi_read_sr(&sr) < 0)
					printf("read sr failed\n");
				else
					printf("sr %x\n", sr);
			}
		}
	}
#ifdef MX_4B_MODE
	else if (!strncmp(argv[1], "scur", 2)) {
		u8 scur;
		if (argv[2][0] == 'r') {
			if (raspi_read_scur(&scur) < 0)
				printf("read scur failed\n");
			else
				printf("scur %d\n", scur);
		}
	}
#endif
	else
		printf("Usage:\n%s\n use \"help spi\" for detail!\n", cmdtp->usage);
	return 0;
}

U_BOOT_CMD(
	spi,	4,	0, 	ralink_spi_command,
	"spi	- spi command\n",
	"spi usage:\n"
	"  spi id\n"
	"  spi sr read\n"
	"  spi sr write <value>\n"
	"  spi read <addr> <len>\n"
	"  spi erase <offs> <len>\n"
	"  spi write <offs> <hex_str_value>\n"
);
#endif

// ----- SPI Flash Driver -------
static int rt6855a_spi_flash_write(struct spi_flash *flash, u32 offset, size_t len, const void *buf)
{
    struct rt6855a_spi_flash *stm = to_rt6855a_spi_flash(flash);

    spi_chip_info = stm->params;
    return (raspi_write((char *)buf, offset, len, 1)<len);
}

static int rt6855a_spi_flash_erase(struct spi_flash *flash, u32 offset, size_t len)
{
    struct rt6855a_spi_flash *stm = to_rt6855a_spi_flash(flash);

    spi_chip_info = stm->params;
    return raspi_erase(offset, len, 1);
}

static int rt6855a_spi_flash_read(struct spi_flash *flash, u32 offset, size_t len, void *buf)
{
    struct rt6855a_spi_flash *stm = to_rt6855a_spi_flash(flash);

    spi_chip_info = stm->params;
    return (raspi_read(buf, offset, len, 1)<len);
}

static int spi_initialize=0;

static struct spi_flash *spi_flash_probe_rt6855a(struct spi_slave *spi, u8 *idcode)
{
    const struct chip_info *params;
    struct rt6855a_spi_flash *stm;
    unsigned int i;

    if (!spi_initialize) {
        spic_init();
        spi_initialize = 1;
    }

    for (i = 0; i < ARRAY_SIZE(chips_data); i++) {
        params = &chips_data[i];
        if (((params->jedec_id>>16) == ((idcode[1] << 8) | idcode[2])) && params->id == idcode[0])
            break;
    }

    if (i == ARRAY_SIZE(chips_data)) {
        printf("RT6855A_SPI_FLASH: Unsupported SPI Flash ID %02x%02x\n",
                idcode[1], idcode[2]);
        return NULL;
    } else {
		printf("SPI FLASH: %s size=%luMB\n", params->name, params->n_sectors*params->sector_size>>20);
	}

    stm = (struct rt6855a_spi_flash*)malloc(sizeof(struct rt6855a_spi_flash));
    if (!stm) {
        printf("RT6855A_SPI_FLASH: Failed to allocate memory\n");
        return NULL;
    }

    stm->params = params;
    stm->flash.spi = spi;
    stm->flash.name = params->name;

    stm->flash.write = rt6855a_spi_flash_write;
    stm->flash.erase = rt6855a_spi_flash_erase;
    stm->flash.read = rt6855a_spi_flash_read;
    stm->flash.size = params->n_sectors * params->sector_size;
#ifdef CONFIG_CMD_JFFS2
	stm->flash.sector_size = params->sector_size;
#endif

    debug("RT6855A_SPI_FLASH: Detected %s with sector size %u, total %u bytes\n",
            params->name, params->sector_size, stm->flash.size);

    return &stm->flash;
}

static struct spi_flash *flash=NULL;
struct spi_flash *spi_flash_probe(unsigned int bus, unsigned int cs,
		unsigned int max_hz, unsigned int spi_mode)
{
	if (!flash) {
		u8 idcode[5];
		raspi_read_devid(idcode, 5);
		flash = spi_flash_probe_rt6855a(NULL, idcode);
	}
	return flash;
}

void spi_flash_free(struct spi_flash *flash)
{
    struct rt6855a_spi_flash *stm = to_rt6855a_spi_flash(flash);
    free(stm);
}

#if defined(CONFIG_RT6855A_SPI_FLASH_CMD)
static int ralink_spi_command(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	static int silent = 0;
	if ( argc <2 ) {
		goto ralink_spi_command_failed;
	}
	if (!strncmp(argv[1], "id", 3)) {
		u8 buf[5];
		raspi_read_devid(buf, 5);
		printf("device id: %x %x %x %x %x\n", buf[0], buf[1], buf[2], buf[3], buf[4]);
	} else if (!strncmp(argv[1],"silent", 7)) {
		silent = !silent;
		printf("Silent mode is %s\n", silent?"on":"off");
	} else if (argc>=5 && !strncmp(argv[1], "read", 5)) {
		unsigned long addr, offs, len;
		addr = simple_strtoul(argv[2], NULL, 16);
		offs = simple_strtoul(argv[3], NULL, 16);
		len = simple_strtoul(argv[4], NULL, 16);
		if ( raspi_read((char *)addr, offs, len, silent) != len ) return 1;
	} else if (argc>=4 && !strncmp(argv[1], "erase", 6)) {
		unsigned int o, l;
		o = simple_strtoul(argv[2], NULL, 16);
		l = simple_strtoul(argv[3], NULL, 16);
		if ( raspi_erase(o, l, silent) ) return 1;
	} else if (argc>=5 && !strncmp(argv[1], "write", 6)) {
		unsigned long addr, offs, len;
		addr = simple_strtoul(argv[2], NULL, 16);
		offs = simple_strtoul(argv[3], NULL, 16);
		len = simple_strtoul(argv[4], NULL, 16);
		if ( raspi_write((char *)addr, offs, len, silent)!=len ) return 1;
	} else if (argc>=3 && !strncmp(argv[1], "sr", 3)) {
		u8 sr;
		if (!strncmp(argv[2], "read", 5)) {
			if (raspi_read_sr(&sr) < 0)
				printf("read sr failed\n");
			else
				printf("sr %x\n", sr);
		} else if (argc>=4 && !strncmp(argv[2], "write", 6)) {
			sr = (u8)simple_strtoul(argv[3], NULL, 16);
			printf("trying write sr %x\n", sr);
			if (raspi_write_sr(&sr) < 0)
				printf("write sr failed\n");
			else {
				if (raspi_read_sr(&sr) < 0)
					printf("read sr failed\n");
				else
					printf("sr %x\n", sr);
			}
		}
	}
#ifdef MX_4B_MODE
	else if (!strncmp(argv[1], "scur", 2)) {
		u8 scur;
		if (argv[2][0] == 'r') {
			if (raspi_read_scur(&scur) < 0)
				printf("read scur failed\n");
			else
				printf("scur %d\n", scur);
		}
	}
#endif
	else {
ralink_spi_command_failed:
	#ifdef	CONFIG_SYS_LONGHELP
		printf("\nUsage:\n%s\n", cmdtp->help);
	#else
		printf("wrong syntax\n");
	#endif
			return 1;
	}
	return 0;
}

U_BOOT_CMD(
	spi,	5,	0, 	ralink_spi_command,
	"SPI flash access commands",
	"spi id\n"
	"spi silent\n"
	"spi sr read\n"
	"spi sr write <value>\n"
	"spi erase <offs> <len>\n"
	"spi read <addr> <offs> <len>\n"
	"spi write <addr> <offs> <len>\n"
);
#endif
