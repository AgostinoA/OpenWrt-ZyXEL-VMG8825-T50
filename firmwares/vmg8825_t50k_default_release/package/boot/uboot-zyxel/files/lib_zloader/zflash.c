/*****************************************************************************
 * Copyright (C) ZyXEL Communications, Corp.
 * All Rights Reserved.
 *
 * ZyXEL Confidential; Need to Know only.
 * Protected as an unpublished work.
 *
 * The computer program listings, specifications and documentation
 * herein are the property of ZyXEL Communications, Corp. and
 * shall not be reproduced, copied, disclosed, or used in whole or
 * in part for any reason without the prior express written permission of
 * ZyXEL Communications, Corp.
 *****************************************************************************/
/*****************************************************************************
 * Program: flash driver for zloader
 *  Author: Chang-Hsing Lee.(changhsing.lee@zyxel.com.tw), 2012/6/19
 *****************************************************************************/
#include <common.h>
#include <exports.h>
#ifdef CONFIG_ENV_IS_IN_SPI_FLASH
#include <spi_flash.h>
#ifndef CONFIG_ENV_SPI_BUS
# define CONFIG_ENV_SPI_BUS	0
#endif
#ifndef CONFIG_ENV_SPI_CS
# define CONFIG_ENV_SPI_CS		0
#endif
#ifndef CONFIG_ENV_SPI_MAX_HZ
# define CONFIG_ENV_SPI_MAX_HZ	1000000
#endif
#ifndef CONFIG_ENV_SPI_MODE
# define CONFIG_ENV_SPI_MODE	SPI_MODE_3
#endif
static struct spi_flash *flash=NULL;
#elif !defined(CONFIG_SYS_NO_FLASH)
#include <flash.h>
extern flash_info_t  flash_info[]; /* info for FLASH chips */
#endif
#include "zflash.h"

#ifdef CONFIG_CMD_NAND
#include <nand.h>

int znand_init(void)
{
    /* TODO */
    return 0;
}
int znand_read(unsigned long offs, unsigned long len, char *buf)
{
    return nand_read_skip_bad(&nand_info[0], offs, &len, (u_char *)buf);
}

int znand_write(unsigned long offs, unsigned long len, char *buf)
{
    return nand_write_skip_bad(&nand_info[0], offs, &len, (u_char *)buf);
}

int znand_erase(unsigned long offs, unsigned long len)
{
    nand_erase_options_t opts;
    opts.offset = offs;
    opts.length = len;
    opts.quiet = 0;
    opts.jffs2 = 0;
    opts.scrub = 0;

    return nand_erase_opts(&nand_info[0], &opts);
}
#endif

int zflash_init(void)
{
#if defined(CONFIG_ENV_IS_IN_SPI_FLASH)
    /* have SPI NOR flash */
    if (flash==NULL) {
        flash = spi_flash_probe(CONFIG_ENV_SPI_BUS, CONFIG_ENV_SPI_CS,
                CONFIG_ENV_SPI_MAX_HZ, CONFIG_ENV_SPI_MODE);
        if ( flash == NULL ) {
            printf("!!! not found SPI flash !!!\n");
            return -1;
        }
    }
#elif !defined(CONFIG_SYS_NO_FLASH)
    /* have parallel NOR flash */
    /* TODO */
#else
    #error "Unknown NOR flash!"
#endif
    return 0;
}

int zflash_read(unsigned long offs, unsigned long len, char *buf)
{
    DECLARE_GLOBAL_DATA_PTR __maybe_unused;
    if ( buf == NULL ) {
        return -1;
    }
#if defined(CONFIG_ENV_IS_IN_SPI_FLASH)
    if (flash==NULL) {
        return -2;
    }
    return flash->read(flash, offs, len, buf);
#elif !defined(CONFIG_SYS_NO_FLASH) /* parallel NOR flash */
    if ( offs<CONFIG_SYS_FLASH_BASE || offs+len>(CONFIG_SYS_FLASH_BASE+gd->ram_size) ) {
        return -3;
    }
    memcpy(buf, (void *)offs, len);
    flush_cache((unsigned long)buf, len);
#endif
    return 0;
}

int zflash_write(unsigned long offs, unsigned long len, char *buf)
{
    if ( buf == NULL ) {
        return -1;
    }
#if defined(CONFIG_ENV_IS_IN_SPI_FLASH)
    if (flash==NULL) {
        return -2;
    }
    return flash->write(flash, offs, len, buf);
#elif !defined(CONFIG_SYS_NO_FLASH)
    extern int flash_write (char *src, ulong addr, ulong cnt);
    return flash_write (buf, offs, len);
#endif
    return 0;
}

int zflash_erase(unsigned long offs, unsigned long len)
{
#if defined(CONFIG_ENV_IS_IN_SPI_FLASH) /* serial NOR flash */
    if (flash==NULL) {
        return -2;
    }
    return flash->erase(flash, offs, len);
#elif !defined(CONFIG_SYS_NO_FLASH) /* parallel NOR flash */
    extern int flash_sect_erase (ulong addr_first, ulong addr_last);
    return flash_sect_erase(offs, offs+len-1);
#endif
    return 0;
}

#ifdef CONFIG_ZFLASH_CMD
#include <command.h>
static int do_zflash_cmd(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	if ( argc < 4 ) {
		goto zflash_cmd_failed;
	}
	if (argc>=5 && !strncmp(argv[1], "read", 5)) {
		unsigned long addr, offs, len;
		addr = simple_strtoul(argv[2], NULL, 16);
		offs = simple_strtoul(argv[3], NULL, 16);
		len = simple_strtoul(argv[4], NULL, 16);
		if ( zflash_read(offs, len, (char *)addr) ) return -1;
	} else if (argc>=4 && !strncmp(argv[1], "erase", 6)) {
		unsigned int o, l;
		o = simple_strtoul(argv[2], NULL, 16);
		l = simple_strtoul(argv[3], NULL, 16);
		if ( zflash_erase(o, l) ) return -1;
	} else if (argc>=5 && !strncmp(argv[1], "write", 6)) {
		unsigned long addr, offs, len;
		addr = simple_strtoul(argv[2], NULL, 16);
		offs = simple_strtoul(argv[3], NULL, 16);
		len = simple_strtoul(argv[4], NULL, 16);
		if ( zflash_write(offs, len, (char *)addr) ) return -1;
	} else {
zflash_cmd_failed:
	#ifdef	CONFIG_SYS_LONGHELP
		printf("\nUsage:\n%s\n", cmdtp->help);
	#else
		printf("wrong syntax\n");
	#endif
			return -1;
	}
	return 0;
}

U_BOOT_CMD (
	zflash,	5,	0, 	do_zflash_cmd,
	"Flash access commands, length must be align to block/page size",
	"erase <offs> <len>               - erase flash\n"
	"zflash read <addr> <offs> <len>  - read data from flash to memory\n"
	"zflash write <addr> <offs> <len> - write data from memory to flash\n"
    "  <addr>: memory address\n"
    "  <offs>: flash offset/address\n"
);
#endif

