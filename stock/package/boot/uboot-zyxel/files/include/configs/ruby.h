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


#ifndef __RUBY_UBOOT_CONFIG_H
#define __RUBY_UBOOT_CONFIG_H

#include "ruby_mem.h"
#include "ruby_partitions.h"

/*-----------------------------------------------------------------------
 * ZyXEL zloader configuration.
 */
#ifdef CONFIG_ZYXEL_ZLOADER
#define CONFIG_SYS_SDRAM_BASE       RUBY_DRAM_BEGIN
#define CONFIG_SYS_FLASH_BASE       0
#define CONFIG_ZYXEL_MULTIBOOT
#define CONFIG_RUBY_GPIO
#define CONFIG_ZGPIO_CMD
#define CONFIG_ZFLASH_CMD
#define ZLOADER_EXEC_FAILED_LED_INDICATE \
do { \
        configure_pio(6, ZGPIO_CONFIG_OUTPUT); \
        configure_pio(3, ZGPIO_CONFIG_OUTPUT); \
        set_pio(6, ZGPIO_LEVEL_LOW);   /* Power LED off */ \
        set_pio(3, ZGPIO_LEVEL_HIGH);   /* WPS LED on */ \
} while(0)
#define CONFIG_BOOT_ZLOADER_CMD "zflash read 0x81000000 ${zloader_part_addr} ${zloader_part_size};bootm 81000000"
#define FACTORY_RESET_BTN_GPIO_NO           5
#define FACTORY_RESET_BTN_TRIGGER_LEVEL     ZGPIO_LEVEL_LOW
#define UPDATE_RAS_IMG_BTN_GPIO_NO          4 /* WPS button */
#define UPDATE_RAS_IMG_BTN_TRIGGER_LEVEL    ZGPIO_LEVEL_LOW
#else
#define CONFIG_BOOTDELAY	2	/* autoboot after 2 seconds	*/
#endif


/*-----------------------------------------------------------------------
 * Quantenna Source Code Configuration
 */
/* generic define for RUBY */
#define CONFIG_RUBY_BOARD

/* Define text, stack and heap. */
#define CONFIG_ARC_UBOOT_SIZE		UBOOT_TEXT_PARTITION_SIZE /*128KB. Size occupied by uboot on flash. Please make sure that image does not exceed this value.*/
#define CONFIG_ARC_TEXT_BEGIN		RUBY_SRAM_BEGIN
#define CONFIG_ARC_TEXT_SIZE		0x30000 /*192KB. Size occupied by all uboot sections in memory. Please keep it synchronized with linker script.*/
#define CONFIG_ARC_TEXT_END		(CONFIG_ARC_TEXT_BEGIN + CONFIG_ARC_TEXT_SIZE)
#define CONFIG_ARC_STACK_BEGIN		(RUBY_SRAM_BEGIN + RUBY_SRAM_SIZE - 4 - CONFIG_ARC_MUC_STACK_SIZE) /* Stack grows backward; put stack to the end of SRAM, before the MuC stack */
#define CONFIG_ARC_STACK_SIZE		(8*1024)
#define CONFIG_ARC_HEAP_SIZE		(RUBY_SRAM_SIZE - CONFIG_ARC_TEXT_SIZE - CONFIG_ARC_STACK_SIZE - CONFIG_ARC_MUC_STACK_SIZE)
#define CONFIG_ARC_HEAP_BEGIN		CONFIG_ARC_TEXT_END
#if CONFIG_ARC_HEAP_SIZE + CONFIG_ARC_STACK_SIZE > RUBY_SRAM_SIZE - CONFIG_ARC_TEXT_SIZE
	#error "Too big heap and stack!"
#endif

#define CONFIG_ARC_FREE_BEGIN		RUBY_DRAM_BEGIN
#define CONFIG_ARC_FREE_END		(RUBY_DRAM_BEGIN + RUBY_MIN_DRAM_SIZE)

/* pass bootargs through to linux kernel using a tag */
#define CONFIG_CMDLINE_TAG
#define CONFIG_ATAGS_MAX_SIZE		512

/* We have these optimized functions */
#define __HAVE_ARCH_MEMSET
#define __HAVE_ARCH_MEMCPY
#define __HAVE_ARCH_MEMCMP
#ifndef __ASSEMBLY__ 
	#ifdef __KERNEL__ /* required for target userland chkimage to compile */
	extern void* memset(void*, int,unsigned);
	extern void* memcpy(void*, const void*, unsigned);
	extern int memcmp(const void*, const void*, unsigned);
	#endif
#endif

#define QTNBOOT_COPY_DRAM_ADDR		RUBY_KERNEL_LOAD_DRAM_BEGIN
#define CONFIG_ARASAN_GBE		1

#define SAFETY_IMG_ADDR_ARG             "safety_part_addr"
#define SAFETY_IMG_SIZE_ARG             "safety_part_size"
#define LIVE_IMG_ADDR_ARG               "live_part_addr"
#define LIVE_IMG_SIZE_ARG               "live_part_size"

/*-----------------------------------------------------------------------
 * Board Configuration
 */
#define CONFIG_BOARD_RUBY           1
#define CONFIG_BOARD_NAME           "ruby"


/*-----------------------------------------------------------------------
 * Miscellaneous configurable options
 */
/* keep u-boot version string in environment */
#define CONFIG_VERSION_VARIABLE

/* decompression algorithms compressed images */
#define CONFIG_LZMA

/* Memory test */
#define CONFIG_SYS_MEMTEST_START	CONFIG_ARC_FREE_BEGIN
#define CONFIG_SYS_MEMTEST_END		CONFIG_ARC_FREE_END

/* Timer parameters */
#define CONFIG_SYS_HZ               1000

/* Console */
#define CONFIG_SYS_BAUDRATE_TABLE	{ RUBY_SERIAL_BAUD }
//#define CONFIG_BAUDRATE             RUBY_SERIAL_BAUD
#define CONFIG_SYS_MAXARGS		    16 /* Max number of command args */
#define CONFIG_SYS_PROMPT           CONFIG_BOARD_NAME "# "		/* Monitor Command Prompt    */
#define CONFIG_SYS_CBSIZE		    300 /* Size of console buffer */
#define CONFIG_SYS_PBSIZE		    (CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16) /* Print Buffer Size */
//#define CONFIG_SYS_LONGHELP         /* undef to save memory	     */
#define CONFIG_SYS_MALLOC_LEN       (256*1024) //CONFIG_ARC_HEAP_SIZE
#define CONFIG_SYS_CONSOLE_INFO_QUIET
//#define CONFIG_SILENT_CONSOLE
#define CONFIG_DISABLE_CONSOLE

/* Enable verbose boot */
#define CONFIG_SHOW_BOOT_PROGRESS


/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
/* No flash support */
#define CONFIG_SYS_NO_FLASH
#define	CONFIG_ENV_IS_IN_SPI_FLASH  1
#define CONFIG_ENV_SIZE             BOOT_CFG_SIZE
#define	CONFIG_ENV_OVERWRITE
#define CONFIG_ENV_OFFSET           UBOOT_TEXT_PARTITION_SIZE

#define CONFIG_SPI_FLASH_RUBY

#ifndef CONFIG_ZYXEL_ZLOADER
#define CONFIG_RUBY_SPI_FLASH_CMD
#endif

/* Default load address */
#define CONFIG_SYS_LOAD_ADDR		RUBY_KERNEL_LOAD_DRAM_BEGIN /* Default load address for bootm command */
#undef CONFIG_LOADADDR
#undef CONFIG_BOOTARGS

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
#ifndef CONFIG_ZYXEL_ZLOADER
#define __gen_cmd(cmd, offs, file, eraseCmd, writeCmd, eraseSize)	\
	#cmd "=tftp 81000000 ${dir}" #file ";"						\
	#eraseCmd " " #offs " " #eraseSize ";"							\
	#writeCmd " " #offs " ${fileaddr} ${filesize}\0"

#define gen_cmd(cmd, offs, file, partSize)							\
	__gen_cmd(cmd, offs, file, spi_flash erase, spi_flash write, partSize)
#else
#define __gen_cmd(cmd, offs, file, eraseCmd, writeCmd, eraseSize)	\
	#cmd "=tftp 81000000 ${dir}" #file ";"						\
	#eraseCmd " " #offs " " #eraseSize ";"							\
	#writeCmd " ${fileaddr} " #offs " ${filesize}\0"

#define gen_cmd(cmd, offs, file, partSize)							\
	__gen_cmd(cmd, offs, file, zflash erase, zflash write, partSize)
#endif

#define __gen_img_env_val(name, addr, size)	\
	#name "_part_addr=" #addr "\0"			\
	#name "_part_size=" #size "\0"

#define gen_img_env_val(name, addr, size)	\
	__gen_img_env_val(name, addr, size)

#define CFG_LOADER_PART_ADDR		0
#ifndef CONFIG_EMBEDDED_KERNEL_IN_ROOTFS
#error "Kernel image should be embedded in rootfs"
#endif
#ifdef CONFIG_ZYXEL_ZLOADER
  #define CFG_LOADER_PART_SIZE		UBOOT_TEXT_PARTITION_SIZE   /* 0x20000 */
  #define CFG_ENV_PART_ADDR			UBOOT_ENV_PARTITION_ADDR    /* 0x20000 */
  #define CFG_ENV_PART_SIZE			UBOOT_ENV_PARTITION_SIZE    /* 0x20000 */
  #define CFG_ZLOADER_PART_ADDR     0x40000
  #define CFG_ZLOADER_PART_SIZE     0x10000
  #define CFG_ROOTFSDATA_PART_ADDR  0x50000
  #define CFG_ROOTFSDATA_PART_SIZE  0x60000
  #define CFG_HEADER_PART_ADDR      0xb0000
  #define CFG_HEADER_PART_SIZE      0x10000
  #define CFG_ROOTFS_PART_ADDR		0xc0000
  #define CFG_ROOTFS_PART_SIZE		0x740000
  #define CFG_RAS_PART_ADDR         0xb0000
  #define CFG_RAS_PART_SIZE         0x750000
#if (CFG_RAS_PART_ADDR!=CFG_HEADER_PART_ADDR) || (CFG_RAS_PART_SIZE!=(CFG_HEADER_PART_SIZE+CFG_ROOTFS_PART_SIZE))
  #error "Wrong address/size of RAS partition!"
#endif
  #define LOADER_IMG_ENV_VAL	gen_img_env_val(loader, CFG_LOADER_PART_ADDR, CFG_LOADER_PART_SIZE)
  #define ENV_IMG_ENV_VAL		gen_img_env_val(env, CFG_ENV_PART_ADDR, CFG_ENV_PART_SIZE)
  #define ZLOADER_IMG_ENV_VAL	gen_img_env_val(zloader, CFG_ZLOADER_PART_ADDR, CFG_ZLOADER_PART_SIZE)
  #define RTFSDATA_IMG_ENV_VAL	gen_img_env_val(rtfsdat, CFG_ROOTFSDATA_PART_ADDR, CFG_ROOTFSDATA_PART_SIZE)
  #define HEADER_IMG_ENV_VAL    gen_img_env_val(hdr, CFG_HEADER_PART_ADDR, CFG_HEADER_PART_SIZE)
  #define ROOTFS_IMG_ENV_VAL	gen_img_env_val(rootfs, CFG_ROOTFS_PART_ADDR, CFG_ROOTFS_PART_SIZE)
  #define RAS_IMG_ENV_VAL       gen_img_env_val(ras, CFG_RAS_PART_ADDR, CFG_RAS_PART_SIZE)

  #define UPDATE_LOADER_CMD     gen_cmd(lu, ${loader_part_addr}, u-boot.bin, ${loader_part_size})
  #define UPDATE_ROOTFS_CMD     gen_cmd(lf, ${rootfs_part_addr}, ${img_prefix}rootfs.jffs2, ${rootfs_part_size})
  #define UPDATE_RAS_CMD        gen_cmd(lr, ${ras_part_addr}, ras.bin, ${ras_part_size})
  #define UPDATE_ZLOADER_CMD    gen_cmd(lz, ${zloader_part_addr}, zloader.bin.lzma.uImage, ${zloader_part_size})

  #define IMG_ENV_VAL           LOADER_IMG_ENV_VAL ENV_IMG_ENV_VAL ZLOADER_IMG_ENV_VAL \
                                RTFSDATA_IMG_ENV_VAL HEADER_IMG_ENV_VAL ROOTFS_IMG_ENV_VAL RAS_IMG_ENV_VAL
  #define UPGRADE_IMG_CMD		UPDATE_LOADER_CMD UPDATE_ROOTFS_CMD UPDATE_RAS_CMD UPDATE_ZLOADER_CMD
  #define ROOTFS_MTD_NO         "rootmtd=5\0"
  #define MTDPARTS_DEFAULT		"mtdparts=spi_flash:${loader_part_size}(u-boot),${env_part_size}(env)${readonly},${zloader_part_size}(zloader)${readonly},${rtfsdat_part_size}(rootfs_data),${hdr_part_size}(header),${rootfs_part_size}(rootfs)\0"
#else
  #define CFG_LOADER_PART_SIZE		0x20000
  #define CFG_ENV_PART_ADDR			0x20000
  #define CFG_ENV_PART_SIZE			0x20000
  #define CFG_ROOTFS_PART_ADDR      0x40000
  #define CFG_ROOTFS_PART_SIZE      0x780000
  #define CFG_DATA_PART_ADDR        0x7C0000
  #define CFG_DATA_PART_SIZE        0x40000

  #define LOADER_IMG_ENV_VAL        gen_img_env_val(loader, CFG_LOADER_PART_ADDR, CFG_LOADER_PART_SIZE)
  #define ENV_IMG_ENV_VAL           gen_img_env_val(env, CFG_ENV_PART_ADDR, CFG_ENV_PART_SIZE)
  #define ROOTFS_IMG_ENV_VAL        gen_img_env_val(rootfs, CFG_ROOTFS_PART_ADDR, CFG_ROOTFS_PART_SIZE)
  #define DATA_IMG_ENV_VAL          gen_img_env_val(data, CFG_DATA_PART_ADDR, CFG_DATA_PART_SIZE)

  #define UPDATE_LOADER_CMD         gen_cmd(lu, ${loader_part_addr}, u-boot.bin, ${loader_part_size})
  #define UPDATE_ROOTFS_CMD         gen_cmd(lf, ${rootfs_part_addr}, ${img_prefix}vmlinux.lzma.uImage, ${rootfs_part_size})

  #define IMG_ENV_VAL               LOADER_IMG_ENV_VAL ENV_IMG_ENV_VAL ROOTFS_IMG_ENV_VAL DATA_IMG_ENV_VAL
  #define UPGRADE_IMG_CMD           UPDATE_LOADER_CMD UPDATE_ROOTFS_CMD
  #define ROOTFS_MTD_NO             "rootmtd=2\0"
  #define MTDPARTS_DEFAULT          "mtdparts=spi_flash:${loader_part_size}(u-boot),${env_part_size}(env)${readonly},${rootfs_part_size}(rootfs),${data_part_size}(data)\0"
#endif

#define BOOT_FLASH_CMD  \
    "boot_flash=run setmtdparts flashargs addmtd;fsload 81000000 /boot/vmlinux.lzma.uImage;bootm 81000000\0"

#ifndef CONFIG_EXTRA_ENV_SETTINGS
/* ROOTFS_MTD_NO, MTDPARTS_DEFAULT, BOOT_FLASH_CMD, IMG_ENV_VAL, UPGRADE_IMG_CMD */
#define	CONFIG_EXTRA_ENV_SETTINGS				\
    "uboot_env_ver=" CONFIG_ENV_VERSION "\0"    \
	"img_prefix=ruby-\0"	\
	"loadaddr=0x81000000\0" \
	"init_process=/etc/preinit\0" \
	ROOTFS_MTD_NO \
    "readonly=ro\0" \
	"rootfstype=jffs2\0" \
	"setmtdparts=setenv mtdparts " MTDPARTS_DEFAULT \
	"flashargs=setenv bootargs console=ttyS0,115200n8 earlyprintk=1 hw_config_id=${hw_config_id} " \
         "init=${init_process} root=/dev/mtdblock${rootmtd} rootfstype=${rootfstype} rw " \
         "${bootmode} ${zld_ver}\0" \
	"addmtd=setenv bootargs ${bootargs} ${mtdparts}\0" \
	BOOT_FLASH_CMD \
	"bootcmd=run boot_flash\0" \
	IMG_ENV_VAL \
	UPGRADE_IMG_CMD \
	"countrycode=ff\0" \
	"serialnum=S100Z47000001\0" \
	"hostname=RUBY\0"
#endif


/*-----------------------------------------------------------------------
 * Networking Configuration
 */
#define CONFIG_NET_RETRY_COUNT	2
#define CONFIG_NET_MULTI
#define CONFIG_IPADDR			192.168.1.1
#define CONFIG_SERVERIP			192.168.1.33
#define CONFIG_ETHADDR			30:46:9a:25:be:e4


/*-----------------------------------------------------------------------
 * JFFS2 Filesystem Configuration
 */
#ifdef CONFIG_EMBEDDED_KERNEL_IN_ROOTFS
#define CONFIG_CMD_JFFS2
//#define CONFIG_CMD_JFFS2_LS
//#define CONFIG_CMD_JFFS2_FSINFO
#define CONFIG_JFFS2_PART_OFFSET	CFG_ROOTFS_PART_ADDR
// Default using remaining flash space if you ignore 'CONFIG_JFFS_PART_SIZE'
#define CONFIG_JFFS2_PART_SIZE		CFG_ROOTFS_PART_SIZE
#endif
#ifdef CONFIG_SPI_FLASH_RUBY
/* To avoid compile failed only, Ruby SPI flash driver no needs these setting. */
#define CONFIG_JFFS2_SPI_BUS        0
#define CONFIG_JFFS2_SPI_MAX_HZ     1000000
#define CONFIG_JFFS2_SPI_MODE		SPI_MODE_3
#endif

/*-----------------------------------------------------------------------
 * Command line configuration.
 */
/* Quantenna only */
#define CONFIG_CMD_INTR
//#define CONFIG_CMD_ETHLOOP
//#define CONFIG_CMD_UC
/* */
#define CONFIG_CMD_RUN
#define CONFIG_CMD_CACHE
#define CONFIG_CMD_NET
#define CONFIG_CMD_PING
#define CONFIG_CMD_UC
#define CONFIG_CMD_INTR
#define CONFIG_CMD_SAVEENV
#define CONFIG_CMD_MEMORY

#ifndef CONFIG_ZYXEL_ZLOADER
//#define CONFIG_CMD_CONSOLE
#define CONFIG_CMD_ECHO
#define CONFIG_CMD_MISC
//#define CONFIG_CMD_IMI
//#define CONFIG_CMD_BOOTD
#define CONFIG_CMD_LOADB
//#define CONFIG_CMD_QTNBOOT
//#define CONFIG_CMD_PCIEBOOT
#endif

/* Reduce the MTU size to 1460 because in vlan mode, the packets will be
 * 1518 bytes which exceed the EMAC's capability and these packets will
 * be discard silently.
 */
#define CONFIG_TFTP_BLOCKSIZE   1460

#endif // #ifndef __RUBY_UBOOT_CONFIG_H

