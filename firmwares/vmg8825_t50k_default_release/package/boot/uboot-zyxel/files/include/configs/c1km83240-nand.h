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

/*-----------------------------------------------------------------------
 * ZyXEL zloader configuration.
 */
#ifdef CONFIG_ZYXEL_ZLOADER
#define CONFIG_ZYXEL_MULTIBOOT
#define CONFIG_COMCERTO_GPIO
#define CONFIG_COMCERTO_MAX_GPIO_NUM  ??
#define CONFIG_ZGPIO_CMD
#define CONFIG_ZFLASH_CMD
#define ZLOADER_EXEC_FAILED_LED_INDICATE \
do { \
        configure_pio(13, ZGPIO_CONFIG_OUTPUT); \
        configure_pio(17, ZGPIO_CONFIG_OUTPUT); \
        set_pio(13, ZGPIO_LEVEL_HIGH);   /* Power LED off */ \
        set_pio(17, ZGPIO_LEVEL_LOW);   /* WPS LED on */ \
} while(0)
#define CONFIG_BOOT_ZLOADER_CMD "??"
#define FACTORY_RESET_BTN_GPIO_NO           18
#define FACTORY_RESET_BTN_TRIGGER_LEVEL     ZGPIO_LEVEL_LOW
#define UPDATE_RAS_IMG_BTN_GPIO_NO          21 /* WPS button */
#define UPDATE_RAS_IMG_BTN_TRIGGER_LEVEL    ZGPIO_LEVEL_LOW
#else
#define CONFIG_BOOTDELAY	3	/* autoboot after 3 seconds	*/
#endif

/*-----------------------------------------------------------------------
 * Comcerto Source Code Configuration
 */
#define CONFIG_COMCERTO		1
#define CONFIG_COMCERTO_1000	1	/* It's an  SoC */
#include <asm/hardware.h>
/* Mindspeed version */
#define CONFIG_IDENT_STRING	" Mindspeed $Name: uboot_7_00_5 $"

#define CFG_REFCLKFREQ		24000000	/* 24 MHz */

#define CFG_PHY_CLOCK		125000000	/* 125 MHz*/
#define CFG_GEM0_CLOCK		 25000000	/*  25 MHz*/
#define CFG_GEM1_CLOCK		 25000000	/*  25 MHz*/

#define CFG_DDR_16BIT		1

/* DDR Training algorithm */
#define DDR_TRAINING
//#undef DDR_TRAINING
#define DDR_TRAINING_DBG


 /*-----------------------------------------------------------------------
 * Board Configuration
 */
#define CONFIG_BOARD_C1KM83240		1
#define CONFIG_BOARD_NAME           "M83240"
/* Linux boot configuration */
#define CONFIG_CMDLINE_TAG			1	/* enable passing of ATAGs      */
#define CONFIG_SETUP_MEMORY_TAGS	1
//#define CONFIG_INITRD_TAG			1

#define LINUX_BOOTPARAM_ADDR		(PHYS_SDRAM + MSP_BOTTOM_MEMORY_RESERVED_SIZE + 0x100)
/* define one of these to choose the UART0 or UART1 as console */
#define CONFIG_UART0		1
#define BOARD_LATE_INIT
#define MSP_BOTTOM_MEMORY_RESERVED_SIZE	0x800000	/* 8 MiB reserved for MSP */
#define MSP_TOP_MEMORY_RESERVED_SIZE	0x0		/* 0 MiB reserved for MSP */

/* NAND GPIOs config */
#define CFG_NAND_BR_GPIO	6
#define CFG_NAND_CE_GPIO	29
#define CFG_NAND_CLE_GPIO	31
#define CFG_NAND_ALE_GPIO	30

/* Initial stack configuration */
#define CONFIG_SYS_INIT_RAM_ADDR	0x0A000000 /* ARAM_BASEADDR Base address */
#define CONFIG_SYS_INIT_RAM_END		0x00020000 /* 128K */
#define CFG_ARAM_CODE_SIZE			0x00010000 /* 64K */


/*-----------------------------------------------------------------------
 * CPU Core Configuration
 */
#define CONFIG_ARM1136 		1	/* This is an arm1136j-s CPU core */
#undef  CONFIG_USE_IRQ		/* we don't need IRQ/FIQ stuff  */

/*-----------------------------------------------------------------------
 * Miscellaneous configurable options
 */
#define CONFIG_BAUDRATE		115200
#define CONFIG_SYS_BAUDRATE_TABLE	{115200, 19200, 38400, 57600, 9600}
#define CONFIG_SERVERIP 192.168.1.33
#define CONFIG_IPADDR 192.168.1.1
#define CONFIG_ETHADDR 00:AA:BB:CC:DD:00

#define	CONFIG_TIMESTAMP		/* Print image info with timestamp */
#define CONFIG_VERSION_VARIABLE     /* keep u-boot version string in environment */
#define CONFIG_SYS_LONGHELP			        /* undef to save memory	     */
#define CONFIG_SYS_PROMPT           CONFIG_BOARD_NAME "# "		/* Monitor Command Prompt    */
#define CONFIG_SYS_CBSIZE           256		/* Console I/O Buffer Size   */
#define CONFIG_SYS_PBSIZE           (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)  /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS          16		/* max number of command args*/

/* Malloc/stack configuration */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 256 * 1024)
#define CONFIG_SYS_GBL_DATA_SIZE	128	/* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)

#define CONFIG_STACKSIZE	(32 * 1024)	/* regular stack */

#define CONFIG_SYS_HZ			1000

/* Memory Mapping */
#define CONFIG_NR_DRAM_BANKS	1
#define PHYS_SDRAM				DDR_BASEADDR
#define PHYS_SDRAM_SIZE			0x8000000	/* 128 MB */

#define CONFIG_SYS_LOAD_ADDR		(PHYS_SDRAM + 0x01000000)	/* default load address */
#define CONFIG_SYS_MEMTEST_START	CONFIG_SYS_LOAD_ADDR	/* memtest works on */
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + 0x800000)

#define CONFIG_LZMA					1

#define CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET - CFG_ARAM_CODE_SIZE

#define CONFIG_SYS_CONSOLE_INFO_QUIET
//#define CONFIG_SILENT_CONSOLE
#define CONFIG_DISABLE_CONSOLE

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
#define CONFIG_SYS_NAND_BASE		EXP_CS4_BASEADDR
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_MAX_CHIPS	1
#define CONFIG_ENV_IS_NOWHERE		1
#define CONFIG_ENV_SIZE				0x10000
#define CONFIG_SYS_NAND_MAX_CHIPS	1

/* CONFIG_ENV_VERSION
 *   v1.0: initial version
 *   v1.1: add environment variable 'env_readonly' to set partition 'env' as read-only
 *   v1.2: rename environment variable 'env_readonly' to 'readonly' for setting
 *         partition 'env' & 'RFData' as read-only
 *   v1.3: add environment variable 'zld_ver' to record zloader version and put it in
 *         kernel command line
 */
#define CONFIG_ENV_VERSION          "1.3"

/*-----------------------------------------------------------------------
 * Partition Configuration
 */
#undef	CONFIG_BOOTARGS

#define __gen_cmd(cmd, offs, file, eraseCmd, writeCmd, eraseSize)	\
	#cmd "=tftp ${loadaddr} ${dir}" #file ";"						\
	#eraseCmd " " #offs " " #eraseSize ";"							\
	#writeCmd " ${fileaddr} " #offs " ${filesize}\0"

#define gen_cmd(cmd, offs, file, partSize)							\
	__gen_cmd(cmd, offs, file, nand erase, nand write.jffs2, partSize)

#define __gen_img_env_val(name, addr, size)	\
	#name "_part_addr=" #addr "\0"			\
	#name "_part_size=" #size "\0"

#define gen_img_env_val(name, addr, size)	\
	__gen_img_env_val(name, addr, size)

#define CFG_LOADER_PART_ADDR		0
#define CFG_LOADER_PART_SIZE		0x40000
#define CFG_RFDATA_PART_ADDR		0x40000
#define CFG_RFDATA_PART_SIZE		0x20000
#define CFG_ROOTFS_PART_ADDR		0x60000
#define CFG_ROOTFS_PART_SIZE		0xC800000
#define CFG_ROOTFSDATA_PART_ADDR	0xC860000
#define CFG_ROOTFSDATA_PART_SIZE	0xC800000

#define LOADER_IMG_ENV_VAL		gen_img_env_val(loader, CFG_LOADER_PART_ADDR, CFG_LOADER_PART_SIZE)
#define RFDATA_IMG_ENV_VAL		gen_img_env_val(rfdat, CFG_RFDATA_PART_ADDR, CFG_RFDATA_PART_SIZE)
#define RTFSDATA_IMG_ENV_VAL	gen_img_env_val(rtfsdat, CFG_ROOTFSDATA_PART_ADDR, CFG_ROOTFSDATA_PART_SIZE)
#define ROOTFS_IMG_ENV_VAL		gen_img_env_val(rootfs, CFG_ROOTFS_PART_ADDR, CFG_ROOTFS_PART_SIZE)

#define UPDATE_LOADER_CMD		gen_cmd(lu, ${loader_part_addr}, u-boot.bin, ${loader_part_size})
#define UPDATE_ROOTFS_CMD		gen_cmd(lf, ${rootfs_part_addr}, ${img_prefix}rootfs.jffs2, ${rootfs_part_size})

#define IMG_ENV_VAL				LOADER_IMG_ENV_VAL RFDATA_IMG_ENV_VAL RTFSDATA_IMG_ENV_VAL ROOTFS_IMG_ENV_VAL 
#define UPGRADE_IMG_CMD			UPDATE_LOADER_CMD UPDATE_ROOTFS_CMD

#define ROOTFS_MTD_NO			"root_mtdblock_no=2\0"
#define MTDIDS_DEFAULT			"nand0=comcertonand"
#define MTDPARTS_DEFAULT		"mtdparts=comcertonand:${loader_part_size}(u-boot),${rfdat_part_size}(RFdata)${readonly},${rootfs_part_size}(rootfs),${rtfsdat_part_size}(rootfs_data)\0"
#define BOOT_FLASH_CMD			"boot_flash=run setmtdparts flashargs addtty addmtd;fsload ${loadaddr} /boot/uImage;bootm ${loadaddr}\0"
#define INIT_PROCESS_ENV      "/etc/preinit"

/* ROOTFS_MTD_NO, MTDPARTS_DEFAULT, BOOT_FLASH_CMD, IMG_ENV_VAL, UPGRADE_IMG_CMD */
#define	CONFIG_EXTRA_ENV_SETTINGS					\
    "uboot_env_ver=" CONFIG_ENV_VERSION "\0" \
	"img_prefix=m83240-\0"	\
	"loadaddr=80400000\0" \
	"init_process=" INIT_PROCESS_ENV "\0" \
	ROOTFS_MTD_NO \
    "readonly=ro\0" \
	"rootfstype=jffs2\0" \
	"setmtdparts=setenv mtdparts " MTDPARTS_DEFAULT \
	"flashargs=setenv bootargs init=${init_process} root=/dev/mtdblock${root_mtdblock_no} rootfstype=${rootfstype} rw ${bootmode} ${zld_ver}\0"  \
	"addtty=setenv bootargs ${bootargs} console=ttyS0,${baudrate}\0" \
	"addmtd=setenv bootargs ${bootargs} ${mtdparts}\0" \
	BOOT_FLASH_CMD \
	"bootcmd=run boot_flash\0" \
	IMG_ENV_VAL \
	UPGRADE_IMG_CMD \
	"countrycode=ff\0" \
	"serialnum=S100Z47000001\0" \
	"hostname=M83240\0"

	
/*-----------------------------------------------------------------------
 * JFFS2 Filesystem Configuration
 */
#define CONFIG_JFFS2_NAND			1
#define CONFIG_JFFS2_DEV			"nand0"
#define CONFIG_CMD_JFFS2
#define CONFIG_CMD_JFFS2_ULOAD
//#define CONFIG_CMD_JFFS2_LS
//#define CONFIG_CMD_JFFS2_FSINFO
#define CONFIG_JFFS2_PART_OFFSET	CFG_ROOTFS_PART_ADDR
// Default using remaining flash space if you ignore 'CONFIG_JFFS_PART_SIZE'
#define CONFIG_JFFS2_PART_SIZE		CFG_ROOTFS_PART_SIZE


/*-----------------------------------------------------------------------
 * Networking Configuration
 */
#define CONFIG_NET_MULTI
#define CONFIG_NET_RETRY_COUNT		3
#define CONFIG_COMCERTO_GEMAC	1
// GEMAC mode configured by bootstrap pins or SW
#undef CONFIG_COMCERTO_MII_CFG_BOOTSTRAP
//#define CONFIG_COMCERTO_MII_CFG_BOOTSTRAP
#define GEMAC0_PHY_ADDR		0
#define GEMAC0_CONFIG		CONFIG_COMCERTO_USE_RGMII
#define GEMAC0_MODE			(GEMAC_SW_CONF | GEMAC_SW_FULL_DUPLEX | GEMAC_SW_SPEED_1G)
#define GEMAC0_PHY_FLAGS	(GEMAC_PHY_AUTONEG | GEMAC_GEM_DELAY_DISABLE)
#define GEMAC0_PHYIDX		0
#define GEMAC1_PHY_ADDR		0	//not used
#define GEMAC1_CONFIG		CONFIG_COMCERTO_USE_RGMII
#define GEMAC1_MODE			(GEMAC_SW_CONF | GEMAC_SW_FULL_DUPLEX | GEMAC_SW_SPEED_1G)
#define GEMAC1_PHY_FLAGS	(GEMAC_NO_PHY | GEMAC_GEM_DELAY_DISABLE)
#define GEMAC1_PHYIDX		0	//not used

#ifndef CONFIG_ZYXEL_ZLOADER
#define CONFIG_MII
#define CONFIG_CMD_MII
#define CONFIG_PHY_GIGE
#endif

/*-----------------------------------------------------------------------
 * I2C support
 */
#define CONFIG_HARD_I2C
#define CONFIG_SYS_TCLK                CFG_HZ_CLOCK
#define CONFIG_SYS_I2C_SPEED           40000
#define CONFIG_SYS_I2C_SLAVE           0

#define CONFIG_SYS_I2C_EEPROM_ADDR            0x50
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN        2 /* Bytes of address */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS     6 /* max 64 byte */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS 10
#define CONFIG_SYS_EEPROM_PAGE_WRITE_ENABLE



#if 0
/*
 * Flash Configuration - Using CFI driver 
 */
//#define CFG_FLASH_AM040_DRIVER	1		/* enable AM040 flash driver */
#undef CFG_FLASH_AM040_DRIVER				/* disable AM040 flash driver */

//#define CFG_FLASH_AMLV640U_DRIVER	1		/* enable AMLV640U flash driver */
#undef CFG_FLASH_AMLV640U_DRIVER			/* disable AMLV640U flash driver */
//#define CFG_FLASH_AMLV640U_SIZE	0x400000	/* (Acessible) Size of the AMLV640U flash device */

//#define CONFIG_FLASH_CFI_DRIVER		1	/* enable CFI driver */
#undef CONFIG_FLASH_CFI_DRIVER			/* disable CFI driver */

#define CONFIG_SYS_MAX_FLASH_SECT		256	/* max # of sectors on one chip */
#undef CONFIG_SYS_FLASH_PROTECTION

#define PHYS_FLASH1						EXP_CS0_BASEADDR	/* Flash Bank #1 */
#define PHYS_FLASH1_SECT_SIZE			0x00020000	/* 128 KiB sectors */

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
#endif
#endif

#ifdef CONFIG_USE_IRQ
#error CONFIG_USE_IRQ not supported
#endif


/*-----------------------------------------------------------------------
 * Command line configuration.
 */
#define CONFIG_SYS_NO_FLASH
#include <config_cmd_default.h>
#define CONFIG_CMD_MII
#define CONFIG_CMD_NAND
#define CONFIG_CMD_PING
#define CONFIG_CMD_I2C 
#define CONFIG_CMD_EEPROM
#define CONFIG_CMD_ELF

#undef CONFIG_CMD_BOOTD
#undef CONFIG_CMD_LOADS
#undef CONFIG_CMD_FPGA
#undef CONFIG_CMD_EDITENV
#undef CONFIG_CMD_SAVEENV


 /* Relocation options */
//#define CONFIG_SKIP_RELOCATE_UBOOT
#define CONFIG_SKIP_LOWLEVEL_INIT

#endif /* __CONFIG_H */
