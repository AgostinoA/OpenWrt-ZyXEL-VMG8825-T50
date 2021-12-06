/*
 * (C) Copyright 2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * This file contains the configuration parameters for the RT2880 board.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*-----------------------------------------------------------------------
 * ZyXEL zloader configuration.
 */
#ifdef CONFIG_ZYXEL_ZLOADER
#define CONFIG_ZYXEL_MULTIBOOT
#define CONFIG_RT2880_GPIO
//#define CONFIG_ZGPIO_CMD
#define ZLOADER_EXEC_FAILED_LED_INDICATE \
do { \
        configure_pio(26, ZGPIO_CONFIG_OUTPUT); \
        configure_pio(28, ZGPIO_CONFIG_OUTPUT); \
        set_pio(26, ZGPIO_LEVEL_HIGH);	/* Power LED off */ \
        set_pio(28, ZGPIO_LEVEL_LOW);	/* WPS LED on */ \
} while(0)
#define CONFIG_BOOT_ZLOADER_CMD             "spi read ${loadaddr} 20000 20000;bootm ${loadaddr}"
#define FACTORY_RESET_BTN_GPIO_NO           2
#define FACTORY_RESET_BTN_TRIGGER_LEVEL     ZGPIO_LEVEL_LOW
#define UPDATE_RAS_IMG_BTN_GPIO_NO          6 /* WPS button */
#define UPDATE_RAS_IMG_BTN_TRIGGER_LEVEL    ZGPIO_LEVEL_LOW
#else
#define CONFIG_BOOTDELAY	3	/* autoboot after 3 seconds	*/
#endif

/*-----------------------------------------------------------------------
 * Ralink Source Code Configuration
 */
#define ASIC_BOARD                      1
#define RT6855A_ASIC_BOARD              1
#define RT6855A_MP                      1
#define P5_RGMII_TO_MAC_MODE			1
//#define P5_MAC_TO_PHY_MODE              1
//#define MAC_TO_GIGAPHY_MODE_ADDR        0
//#define ON_BOARD_SPI_FLASH_COMPONENT    1
#define ON_BOARD_DDR2                   1
#define ON_BOARD_1024M_DRAM_COMPONENT	1
#define ON_BOARD_DDR_WIDTH_16           1
#define ON_BOARD_16BIT_DRAM_BUS         1
//#define UBOOT_ROM                       1
//#define RALINK_MDIO_ACCESS_FUN		1

/*-----------------------------------------------------------------------
 * Board Configuration
 */
#define CONFIG_BOARD_AMITSAMPLE  1
#define CONFIG_BOARD_NAME	"AmitSample"

/*-----------------------------------------------------------------------
 * CPU Core Configuration
 */
#define CONFIG_MIPS32		1	/* MIPS 4Kc CPU core	*/

/*-----------------------------------------------------------------------
 * Cache Configuration
 */
#define CONFIG_SYS_DCACHE_SIZE		(32*1024)
#define CONFIG_SYS_ICACHE_SIZE		(64*1024)
#define CONFIG_SYS_CACHELINE_SIZE   32

#define SERIAL_CLOCK_DIVISOR 16

#define CONFIG_BAUDRATE		115200

#define CONFIG_SERVERIP 192.168.1.33
#define CONFIG_IPADDR 192.168.1.1
#define CONFIG_ETHADDR 00:AA:BB:CC:DD:00
/* valid baudrates */
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

#define	CONFIG_TIMESTAMP		/* Print image info with timestamp */


/*
 * Miscellaneous configurable options
 */
#define CONFIG_VERSION_VARIABLE     /* keep u-boot version string in environment */
#define CONFIG_SYS_LONGHELP			        /* undef to save memory	     */
#define CONFIG_SYS_PROMPT           CONFIG_BOARD_NAME "# "		/* Monitor Command Prompt    */
#define CONFIG_SYS_CBSIZE           256		/* Console I/O Buffer Size   */
#define CONFIG_SYS_PBSIZE           (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)  /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS          16		/* max number of command args*/
//#define CONFIG_SYS_HUSH_PARSER
//#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#define CONFIG_SYS_MALLOC_LEN		256*1024

#define CONFIG_SYS_BOOTPARAMS_LEN	128*1024

#define CONFIG_SYS_MIPS_TIMER_FREQ	(mips_cpu_feq/2)

#define CONFIG_SYS_HZ               1000

#define CONFIG_SYS_SDRAM_BASE		0x80000000
#define CONFIG_NR_DRAM_BANKS        1
#define CONFIG_SYS_LOAD_ADDR		0x80100000	/* default load address */
#define CONFIG_SYS_MEMTEST_START	0x80100000
#define CONFIG_SYS_MEMTEST_END		0x80400000

#define CONFIG_LZMA                 1

#define CONFIG_SYS_INIT_SP_OFFSET	0x400000
#define	CONFIG_SYS_MONITOR_BASE		TEXT_BASE
#define	CONFIG_SYS_MONITOR_LEN		CFG_LOADER_PART_SIZE


/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
#define CONFIG_SYS_NO_FLASH
#define CONFIG_ENV_IS_IN_SPI_FLASH

#ifndef CONFIG_SYS_NO_FLASH
#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max number of memory banks */
#define CONFIG_SYS_MAX_FLASH_SECT	(263)	/* max number of sectors on one chip */
#define CONFIG_FLASH_16BIT
#define PHYS_FLASH_1                0xB0000000
/* The following #defines are needed to get flash environment right */
#define CONFIG_SYS_FLASH_BASE		PHYS_FLASH_1
/* timeout values are in ticks */
#define CONFIG_SYS_FLASH_ERASE_TOUT	(15UL * CONFIG_SYS_HZ) /* Timeout for Flash Erase */
#define CONFIG_SYS_FLASH_WRITE_TOUT	(5 * CONFIG_SYS_HZ) /* Timeout for Flash Write */

//#define CONFIG_SYS_JFFS2_FIRST_BANK   1
//#define CONFIG_SYS_JFFS2_NUM_BANKS	1
#endif

#ifdef CONFIG_ENV_IS_IN_SPI_FLASH // Use SPI Flash
#define CONFIG_SPI_FLASH_RT6855A
#define CONFIG_RT6855A_SPI_FLASH_CMD
#define CONFIG_SYS_FLASH_BASE		0
#if 0   // Could be ignore these setting, 
#define CONFIG_ENV_SPI_BUS          0
#define CONFIG_ENV_SPI_CS		    0
#define CONFIG_ENV_SPI_MAX_HZ       1000000
#define CONFIG_ENV_SPI_MODE         SPI_MODE_3
#endif
#define CONFIG_ENV_OFFSET           CONFIG_SYS_MONITOR_LEN
#endif

#define CONFIG_ENV_SECT_SIZE        0x10000
#define CONFIG_ENV_SIZE             CFG_ENV_PART_SIZE
#define CONFIG_ENV_ADDR             (CONFIG_SYS_FLASH_BASE + CONFIG_SYS_MONITOR_LEN)
#define CONFIG_ENV_OVERWRITE
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
	__gen_cmd(cmd, offs, file, spi erase, spi write, partSize)

#define __gen_img_env_val(name, addr, size)	\
	#name "_part_addr=" #addr "\0"			\
	#name "_part_size=" #size "\0"

#define gen_img_env_val(name, addr, size)	\
	__gen_img_env_val(name, addr, size)


#define CFG_LOADER_PART_ADDR		0
#ifdef CONFIG_EMBEDDED_KERNEL_IN_ROOTFS
  #define CFG_LOADER_PART_SIZE		0x30000
  #define CFG_ENV_PART_ADDR			0x30000
  #define CFG_ENV_PART_SIZE			0x10000
  #define CFG_RFDATA_PART_ADDR      0x40000
  #define CFG_RFDATA_PART_SIZE      0x10000
  #define CFG_ROOTFSDATA_PART_ADDR  0x50000
  #define CFG_ROOTFSDATA_PART_SIZE  0x60000
  #define CFG_HEADER_PART_ADDR      0xb0000
  #define CFG_HEADER_PART_SIZE      0x10000
  #define CFG_ROOTFS_PART_ADDR		0xc0000
  #define CFG_ROOTFS_PART_SIZE		0xF40000
  #define CFG_RAS_PART_ADDR         0xb0000
  #define CFG_RAS_PART_SIZE         0xF50000
#if (CFG_RAS_PART_ADDR!=CFG_HEADER_PART_ADDR) || (CFG_RAS_PART_SIZE!=(CFG_HEADER_PART_SIZE+CFG_ROOTFS_PART_SIZE))
  #error "Wrong address/size of RAS partition!"
#endif
  #define LOADER_IMG_ENV_VAL	gen_img_env_val(loader, CFG_LOADER_PART_ADDR, CFG_LOADER_PART_SIZE)
  #define ENV_IMG_ENV_VAL		gen_img_env_val(env, CFG_ENV_PART_ADDR, CFG_ENV_PART_SIZE)
  #define RFDATA_IMG_ENV_VAL	gen_img_env_val(rfdat, CFG_RFDATA_PART_ADDR, CFG_RFDATA_PART_SIZE)
  #define RTFSDATA_IMG_ENV_VAL	gen_img_env_val(rtfsdat, CFG_ROOTFSDATA_PART_ADDR, CFG_ROOTFSDATA_PART_SIZE)
  #define HEADER_IMG_ENV_VAL    gen_img_env_val(hdr, CFG_HEADER_PART_ADDR, CFG_HEADER_PART_SIZE)
  #define ROOTFS_IMG_ENV_VAL	gen_img_env_val(rootfs, CFG_ROOTFS_PART_ADDR, CFG_ROOTFS_PART_SIZE)
  #define RAS_IMG_ENV_VAL       gen_img_env_val(ras, CFG_RAS_PART_ADDR, CFG_RAS_PART_SIZE)

  #define UPDATE_LOADER_CMD     gen_cmd(lu, ${loader_part_addr}, u-boot.bin, ${loader_part_size})
  #define UPDATE_ROOTFS_CMD     gen_cmd(lf, ${rootfs_part_addr}, ${img_prefix}rootfs.jffs2, ${rootfs_part_size})
  #define UPDATE_RAS_CMD        gen_cmd(lr, ${ras_part_addr}, ras.bin, ${ras_part_size})

  #define IMG_ENV_VAL           LOADER_IMG_ENV_VAL ENV_IMG_ENV_VAL RFDATA_IMG_ENV_VAL \
                                RTFSDATA_IMG_ENV_VAL HEADER_IMG_ENV_VAL ROOTFS_IMG_ENV_VAL RAS_IMG_ENV_VAL
  #define UPGRADE_IMG_CMD		UPDATE_LOADER_CMD UPDATE_ROOTFS_CMD UPDATE_RAS_CMD

  #define ROOTFS_MTD_NO         "root_mtdblock_no=5\0"
  #define MTDPARTS_DEFAULT		"mtdparts=raspi:${loader_part_size}(u-boot),${env_part_size}(env)${readonly},${rfdat_part_size}(RFdata)${readonly},${rtfsdat_part_size}(rootfs_data),${hdr_part_size}(header),${rootfs_part_size}(rootfs)\0"
  #define BOOT_FLASH_CMD		"boot_flash=run setmtdparts flashargs addtty addmtd;fsload ${loadaddr} /boot/vmlinux.lzma.uImage;bootm ${loadaddr}\0"
#else
  #define CFG_LOADER_PART_SIZE		0x30000
  #define CFG_ENV_PART_ADDR			0x30000
  #define CFG_ENV_PART_SIZE			0x10000
  #define CFG_CONFIG_PART_ADDR		0x40000
  #define CFG_CONFIG_PART_SIZE		0x10000
  #define CFG_KERNEL_PART_ADDR		0x50000
  #define CFG_KERNEL_PART_SIZE		0x200000
  #define CFG_ROOTFS_PART_ADDR		0x250000
  #define CFG_ROOTFS_PART_SIZE		0xDB0000

  #define LOADER_IMG_ENV_VAL	gen_img_env_val(loader, CFG_LOADER_PART_ADDR, CFG_LOADER_PART_SIZE)
  #define ENV_IMG_ENV_VAL		gen_img_env_val(env, CFG_ENV_PART_ADDR, CFG_ENV_PART_SIZE)
  #define ROOTFS_IMG_ENV_VAL	gen_img_env_val(rootfs, CFG_ROOTFS_PART_ADDR, CFG_ROOTFS_PART_SIZE)
  #define CONFIG_IMG_ENV_VAL	gen_img_env_val(config, CFG_CONFIG_PART_ADDR, CFG_CONFIG_PART_SIZE)
  #define KERNEL_IMG_ENV_VAL	gen_img_env_val(kernel, CFG_KERNEL_PART_ADDR, CFG_KERNEL_PART_SIZE)

  #define UPDATE_LOADER_CMD     gen_cmd(lu, ${loader_part_addr}, u-boot.bin, ${loader_part_size})
  #define UPDATE_KERNEL_CMD		gen_cmd(lk, ${kernel_part_addr}, ${img_prefix}vmlinux.lzma.uImage, ${kernel_part_size})
  #define UPDATE_ROOTFS_CMD     gen_cmd(lf, ${rootfs_part_addr}, ${img_prefix}rootfs.jffs2, ${rootfs_part_size})

  #define IMG_ENV_VAL           LOADER_IMG_ENV_VAL ENV_IMG_ENV_VAL CONFIG_IMG_ENV_VAL KERNEL_IMG_ENV_VAL ROOTFS_IMG_ENV_VAL
  #define UPGRADE_IMG_CMD		KERNEL_IMG_ENV_VAL UPDATE_LOADER_CMD UPDATE_KERNEL_CMD UPDATE_ROOTFS_CMD

  #define ROOTFS_MTD_NO			"root_mtdblock_no=4\0"
  #define MTDPARTS_DEFAULT		"mtdparts=raspi:${loader_part_size}(u-boot),${env_part_size}(env),${config_part_size}(Config),${kernel_part_size}(kernel),${rootfs_part_size}(fs)\0"
  #define BOOT_FLASH_CMD		"boot_flash=run setmtdparts flashargs addtty addmtd;spi read ${loadaddr} ${kernel_part_addr} ${kernel_part_size};bootm ${loadaddr}\0"
#endif

/* ROOTFS_MTD_NO, MTDPARTS_DEFAULT, BOOT_FLASH_CMD, IMG_ENV_VAL, UPGRADE_IMG_CMD */
#define	CONFIG_EXTRA_ENV_SETTINGS					\
    "uboot_env_ver=" CONFIG_ENV_VERSION "\0" \
	"img_prefix=amitsample-\0"	\
	"loadaddr=80400000\0" \
	"init_process=/etc/preinit\0" \
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
	"hostname=AMITSAMPLE\0" \
	""

/*-----------------------------------------------------------------------
 * JFFS2 Filesystem Configuration
 */
#define CONFIG_CMD_JFFS2
//#define CONFIG_CMD_JFFS2_LS
//#define CONFIG_CMD_JFFS2_FSINFO
#define CONFIG_JFFS2_PART_OFFSET	CFG_ROOTFS_PART_ADDR
// Default using remaining flash space if you ignore 'CONFIG_JFFS_PART_SIZE'
#define CONFIG_JFFS2_PART_SIZE		CFG_ROOTFS_PART_SIZE

#ifdef CONFIG_SPI_FLASH_RT6855A
/* To avoid compile failed only, RT6855A SPI flash driver no needs these setting. */
#define CONFIG_JFFS2_SPI_BUS        0
#define CONFIG_JFFS2_SPI_MAX_HZ     1000000
#define CONFIG_JFFS2_SPI_MODE		SPI_MODE_3
#endif


/*-----------------------------------------------------------------------
 * Networking Configuration
 */
#define CONFIG_RT2880_ETH           	1	/* Enable built-in 10/100 Ethernet */
#define CONFIG_RTL8367B_SWITCH			1
//#define CONFIG_RTL8367B_SWITCH_CMD		1
//#define CONFIG_RTL8367B_DUMMY_PHYADDR	MAC_TO_GIGAPHY_MODE_ADDR
#define CONFIG_RTL8367B_DUMMY_PHYADDR	0
#define CONFIG_NET_MULTI
#define CONFIG_SYS_RX_ETH_BUFFER		60

#ifndef CONFIG_ZYXEL_ZLOADER
#define CONFIG_MII
#define CONFIG_CMD_MII
#define CONFIG_PHY_GIGE
#endif

#define CONFIG_SYS_CONSOLE_INFO_QUIET
//#define CONFIG_SILENT_CONSOLE
#define CONFIG_DISABLE_CONSOLE

/*-----------------------------------------------------------------------
 * Command line configuration.
 */
#include <config_cmd_default.h>

#ifndef CONFIG_ZYXEL_ZLOADER
#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_PING
#else
#undef CONFIG_CMD_MEMORY
#undef CONFIG_CMD_MISC
#undef CONFIG_CMD_BDI
#undef CONFIG_CMD_ECHO
#undef CONFIG_CMD_EDITENV
#undef CONFIG_CMD_BOOTD
#endif
#undef CONFIG_CMD_CONSOLE
#undef CONFIG_CMD_FPGA
#undef CONFIG_CMD_IMI
#undef CONFIG_CMD_ITEST
#undef CONFIG_CMD_LOADB
#undef CONFIG_CMD_LOADS
#undef CONFIG_CMD_NFS
#undef CONFIG_CMD_SETGETDCR
#undef CONFIG_CMD_SOURCE
#undef CONFIG_CMD_XIMG


#if TEXT_BASE != 0xBFC00000
#define CONFIG_SKIP_LOWLEVEL_INIIT
#endif

#endif	/* __CONFIG_H */
