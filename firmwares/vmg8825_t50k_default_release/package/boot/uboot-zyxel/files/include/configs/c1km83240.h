/*
 * Copyright (C) 2006 Mindspeed Technologies, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * High Level Configuration Options
 */
#define CONFIG_COMCERTO		1
#define CONFIG_ARM1136 		1	/* This is an arm1136j-s CPU core */
#define CONFIG_COMCERTO_1000	1	/* It's an  SoC */
#define CONFIG_BOARD_C1KM83240	1
#undef  CONFIG_USE_IRQ		/* we don't need IRQ/FIQ stuff  */

#include <asm/hardware.h>

/* Mindspeed version */
#define CONFIG_IDENT_STRING	" Mindspeed $Name: uboot_7_00_5 $"

/*
 * Linux boot configuration
 */

#define CONFIG_CMDLINE_TAG		1	/* enable passing of ATAGs      */
#define CONFIG_SETUP_MEMORY_TAGS	1
//#define CONFIG_INITRD_TAG		1

#define LINUX_BOOTPARAM_ADDR		(PHYS_SDRAM + MSP_BOTTOM_MEMORY_RESERVED_SIZE + 0x100)

/*
 *	Relocation options
 */
//#define CONFIG_SKIP_RELOCATE_UBOOT
//#define CONFIG_SKIP_LOWLEVEL_INIT

/*
 * RAM configuration
 */

/*
 * Memory Mapping
 */

#define CONFIG_NR_DRAM_BANKS	1
#define PHYS_SDRAM		DDR_BASEADDR
#define PHYS_SDRAM_SIZE		0x8000000	/* 128 MB */

/*
 * Hardware drivers
 */

/*
 * UART configuration
 */  
/* define one of these to choose the UART0 or UART1 as console */
#define CONFIG_UART0		1
#define CONFIG_BAUDRATE		115200
#define CONFIG_SYS_BAUDRATE_TABLE	{115200, 19200, 38400, 57600, 9600}

/*
 * Emac Settings
 */
#define CONFIG_COMCERTO_GEMAC	1

// GEMAC mode configured by bootstrap pins or SW
#undef CONFIG_COMCERTO_MII_CFG_BOOTSTRAP
//#define CONFIG_COMCERTO_MII_CFG_BOOTSTRAP

#define GEMAC0_PHY_ADDR		0
#define GEMAC0_CONFIG		CONFIG_COMCERTO_USE_RGMII
#define GEMAC0_MODE		(GEMAC_SW_CONF | GEMAC_SW_FULL_DUPLEX | GEMAC_SW_SPEED_1G)
#define GEMAC0_PHY_FLAGS	(GEMAC_PHY_AUTONEG | GEMAC_GEM_DELAY_DISABLE)
#define GEMAC0_PHYIDX		0

#define GEMAC1_PHY_ADDR		0	//not used
#define GEMAC1_CONFIG		CONFIG_COMCERTO_USE_RGMII
#define GEMAC1_MODE		(GEMAC_SW_CONF | GEMAC_SW_FULL_DUPLEX | GEMAC_SW_SPEED_1G)
#define GEMAC1_PHY_FLAGS	(GEMAC_NO_PHY | GEMAC_GEM_DELAY_DISABLE)
#define GEMAC1_PHYIDX		0	//not used

#define CONFIG_NET_MULTI	1

/*
 * Shell configuration
 */
#define CONFIG_CMD_FLASH
#define CONFIG_CMD_EDITENV
#define CONFIG_CMD_SAVEENV
#define CONFIG_CMD_MEMORY
#define CONFIG_CMD_MII
#define CONFIG_CMD_RUN
#define CONFIG_CMD_NET
#define CONFIG_CMD_JFFS2
#define CONFIG_CMD_PING
#define CONFIG_CMD_NFS
#define CONFIG_CMD_I2C 
#define CONFIG_CMD_EEPROM
#define CONFIG_CMD_ELF

#define	CONFIG_SYS_LONGHELP					/* undef to save memory		*/
#define CONFIG_SYS_PROMPT	"Comcerto-1000 > "	/* Monitor Command Prompt */
#define CONFIG_SYS_CBSIZE	256			/* Console I/O Buffer Size */
#define CONFIG_SYS_MAXARGS	16			/* max number of command args */
#define CONFIG_SYS_PBSIZE	(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)	/* Print Buffer Size */

/*
 * User Interface
 */
#define CONFIG_EXTRA_ENV_SETTINGS               \
    "hostname=comcerto1000\0"                       \
    "netdev=eth0\0"                                 \
    "nfsargs=setenv bootargs init=${init_process} root=/dev/nfs rw "        \
        "nfsroot=${serverip}:${rootpath}\0"             \
	"flashargs=setenv bootargs init=${init_process} root=/dev/mtdblock2 rootfstype=${rootfstype} rw\0"	\
    "rootfstype=jffs2\0" \
    "init_process=/etc/preinit\0" \
    "addip=setenv bootargs ${bootargs} "                \
        "ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}"  \
        ":${hostname}:${netdev}:off\0" \
    "addeth=setenv bootargs ${bootargs} " \
    "hwaddress=${netdev},${ethaddr}\0" \
    "addtty=setenv bootargs ${bootargs} console=ttyS0,${baudrate}\0" \
    "addmtd=setenv bootargs ${bootargs} ${mtdparts}\0" \
    "flash_self=run flashargs addip addtty;"        \
        "bootm ${kernel_addr}\0"                \
    "boot_nfs=nfs 80600000 ${rootpath}/boot/${kernelfile};run nfsargs addeth addip addtty;"     \
            "bootm 80600000\0"                      \
    "boot_flash=run flashargs addeth addtty addmtd; uload /boot/uImage; bootm\0" \
    "boot_flashold=run flashargs addeth addtty addmtd; fsload /boot/uImage; bootm\0" \
    "rootpath=/devel/fs-c1km83240\0" \
    "kernelfile=uImage\0" \
    "mtdids=" MTDIDS_DEFAULT "\0" \
    "mtdparts=" MTDPARTS_DEFAULT "\0" \
    "partition=" MTDPARTITION_DEFAULT "\0" \
    "mtddevnum=2\0" \
    "mtddevname=fs\0" \
    "fsfile=root.jffs2-128k\0" \
	"updatenandfs=tftp 81000000 ${fsfile};nand erase 60000 880000;nand write 81000000 60000 880000\0" \
 	"updatefs=tftp 81000000 ${fsfile};protect off 1:3-255\;erase 1:3-255;cp.b 81000000 20060000 ${filesize}\0" \
	"updateboot=tftp 81000000 u-boot.bin;protect off 1:0-1\;erase 1:0-1;cp.b 81000000 20000000 ${filesize}\0" \
	"eepromfile=eeprom.bin\0" \
	"updateeprom=tftp 81000000 ${eepromfile};eeprom write 81000000 0 ${filesize}\0" \
	""

#define CONFIG_ETHADDR		00:aa:bb:cc:dd:ee
#define CONFIG_IPADDR		192.168.1.1
#define CONFIG_SERVERIP		192.168.1.33
#define CONFIG_BOOTDELAY	3

#define CONFIG_SYS_LOAD_ADDR		(PHYS_SDRAM + 0x01000000)	/* default load address */

#define CONFIG_SYS_MEMTEST_START	CONFIG_SYS_LOAD_ADDR	/* memtest works on */
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + 0x800000)

#define BOARD_LATE_INIT
#define MSP_BOTTOM_MEMORY_RESERVED_SIZE	0x800000	/* 8 MiB reserved for MSP */
#define MSP_TOP_MEMORY_RESERVED_SIZE	0x0		/* 0 MiB reserved for MSP */


/*
 * Network Configuration
 */
#define CONFIG_NET_RETRY_COUNT		3

/*
 * Flash Configuration - Using CFI driver 
 */
//#define CFG_FLASH_AM040_DRIVER	1		/* enable AM040 flash driver */
#undef CFG_FLASH_AM040_DRIVER				/* disable AM040 flash driver */

//#define CFG_FLASH_AMLV640U_DRIVER	1		/* enable AMLV640U flash driver */
#undef CFG_FLASH_AMLV640U_DRIVER			/* disable AMLV640U flash driver */
//#define CFG_FLASH_AMLV640U_SIZE	0x400000	/* (Acessible) Size of the AMLV640U flash device */

#define CONFIG_FLASH_CFI_DRIVER		1	/* enable CFI driver */
//#undef CONFIG_FLASH_CFI_DRIVER			/* disable CFI driver */

#define CONFIG_SYS_MAX_FLASH_SECT		256	/* max # of sectors on one chip */
#undef CONFIG_SYS_FLASH_PROTECTION

#define PHYS_FLASH1			EXP_CS0_BASEADDR	/* Flash Bank #1 */
#define PHYS_FLASH1_SECT_SIZE		0x00020000	/* 128 KiB sectors */

#define CONFIG_SYS_MAX_FLASH_BANKS		1       /* max num of flash banks */
#define CONFIG_SYS_FLASH_BANKS_LIST		{ PHYS_FLASH1 }

#define CONFIG_SYS_FLASH_ERASE_TOUT		(2 * CONFIG_SYS_HZ)	/* Timeout for Flash Erase */
#define CONFIG_SYS_FLASH_WRITE_TOUT		(2 * CONFIG_SYS_HZ)	/* Timeout for Flash Write */

/*
 * CFI driver 
 */
#if defined(CONFIG_FLASH_CFI_DRIVER)
#define CONFIG_SYS_FLASH_CFI			1	/* flash is CFI conformant      */
#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE	1	/* use buffered writes (20x faster) */
#define CONFIG_SYS_FLASH_QUIET_TEST
#undef CFG_FLASH_COMPLEX_MAPPINGS
// #define CFG_FLASH_COMPLEX_MAPPINGS

/*
 * Monitor configuration
 */
#define CONFIG_SYS_MONITOR_BASE        PHYS_FLASH1
#define CONFIG_SYS_MONITOR_LEN         (1 * PHYS_FLASH1_SECT_SIZE)	/* Reserve 128 KiB for Monitor */

/*
 * Enviroment in flash
 */
#define CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_SIZE          0x4000  /* Total Size of Environment 16KiB */
#endif

/*
 * I2C support
 */
#if defined(CONFIG_CMD_I2C)
#define CONFIG_HARD_I2C
#define CONFIG_SYS_TCLK                CONFIG_SYS_HZ_CLOCK
#define CONFIG_SYS_I2C_SPEED           40000
#define CONFIG_SYS_I2C_SLAVE           0
#if defined(CONFIG_CMD_EEPROM)
#define CONFIG_SYS_I2C_EEPROM_ADDR            0x50
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN        2 /* Bytes of address */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS     6 /* max 64 byte */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS 10
#define CONFIG_SYS_EEPROM_PAGE_WRITE_ENABLE
#endif
#endif

#if defined(CONFIG_ENV_IS_IN_FLASH)
#define CONFIG_ENV_ADDR		(PHYS_FLASH1 + 2 * PHYS_FLASH1_SECT_SIZE)	/* Keep 2 sectors for U-boot image */
#define CONFIG_ENV_SECT_SIZE	PHYS_FLASH1_SECT_SIZE
//#define CONFIG_ENV_ADDR_REDUND	(CONFIG_ENV_ADDR + CONFIG_ENV_SECT_SIZE)
#endif

#define CONFIG_ENV_OVERWRITE	1



/*
 * NAND Configuration
 */
#ifdef CONFIG_CMD_NAND

#define CONFIG_SYS_NAND_BASE			EXP_CS4_BASEADDR
#define CONFIG_SYS_MAX_NAND_DEVICE		1
#define CONFIG_SYS_NAND_MAX_CHIPS			1
#define CONFIG_JFFS2_NAND		1

#ifdef  CONFIG_CMD_FLASH
//TODO
#else
/*
 *EEPORM boot loader does the relocate and lowlevel init work
 */
#define CONFIG_SKIP_RELOCATE_UBOOT
#define CONFIG_SKIP_LOWLEVEL_INIT
/* Environment is in NAND */
#define CONFIG_ENV_IS_IN_NAND	1
#define CONFIG_ENV_OFFSET		0x00040000	/* Offset of Environment Sector */
#define CONFIG_SYS_NAND_MAX_CHIPS          1
#define CONFIG_ENV_SIZE		0x20000	/* Total Size of Environment 128KiB */
#endif

#endif

/* NAND GPIOs config */
#define CFG_NAND_BR_GPIO	6
#define CFG_NAND_CE_GPIO	29
#define CFG_NAND_CLE_GPIO	31
#define CFG_NAND_ALE_GPIO	30

/*
 * JFFS2 Configuration
 */
/* mtdparts command line support */
#define CONFIG_JFFS2_CMDLINE
#ifdef CONFIG_CMD_JFFS2
//#define CONFIG_SYS_JFFS2_SORT_FRAGMENTS
#endif /* CONFIG_CMD_JFFS2 */

#ifdef CONFIG_CMD_NAND
#define MTDIDS_DEFAULT		"nand0=comcertonand"
#define MTDPARTS_DEFAULT	"mtdparts=comcertonand:256k(u-boot),128k(env),32384k(fs)"
#define MTDPARTITION_DEFAULT	"nand0,2"
#define ROOT_MTDBLOCK		"/dev/mtdblock3"
#else
#define MTDIDS_DEFAULT		"nor0=comcertoflash.0"
#define MTDPARTS_DEFAULT	"mtdparts=comcertoflash.0:256k(u-boot),128k(env),32384k(fs)"
#define MTDPARTITION_DEFAULT	"nor0,2"
#define ROOT_MTDBLOCK		"/dev/mtdblock2"
#endif

#define CFG_REFCLKFREQ		24000000	/* 24 MHz */

#define CONFIG_SYS_HZ			1000
#define CFG_PHY_CLOCK		125000000	/* 125 MHz*/
#define CFG_GEM0_CLOCK		 25000000	/*  25 MHz*/
#define CFG_GEM1_CLOCK		 25000000	/*  25 MHz*/

#define CFG_DDR_16BIT		1

/*
 * Initial stack configuration
 */
#define CONFIG_SYS_INIT_RAM_ADDR	0x0A000000 /* ARAM_BASEADDR Base address */
#define CONFIG_SYS_INIT_RAM_END		0x00020000 /* 128K */
#define CFG_ARAM_CODE_SIZE			0x00010000 /* 64K */

#define CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET - CFG_ARAM_CODE_SIZE



/*
 * Malloc/stack configuration
 */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 128 * 1024)
#define CONFIG_SYS_GBL_DATA_SIZE	128	/* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)

#define CONFIG_STACKSIZE	(32 * 1024)	/* regular stack */

#ifdef CONFIG_USE_IRQ
#error CONFIG_USE_IRQ not supported
#endif

/*
* DDR Training algorithm
*/
#define DDR_TRAINING
//#undef DDR_TRAINING
#define DDR_TRAINING_DBG



#endif /* __CONFIG_H */
