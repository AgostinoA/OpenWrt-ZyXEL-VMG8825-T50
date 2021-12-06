/*
 * This file contains the configuration parameters for the AP135 board.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*-----------------------------------------------------------------------
 * ZyXEL zloader configuration.
 */
#ifdef CONFIG_ZYXEL_ZLOADER
#define CONFIG_ZYXEL_MULTIBOOT
#define CONFIG_QCA955X_GPIO
#define CONFIG_QCA955X_MAX_GPIO_NUM  23
#define CONFIG_ZGPIO_CMD
#define CONFIG_ZFLASH_CMD
#define ZLOADER_EXEC_FAILED_LED_INDICATE \
do { \
        configure_pio(15, ZGPIO_CONFIG_OUTPUT); /* Power LED, Low active */ \
        configure_pio(21, ZGPIO_CONFIG_OUTPUT); /* WPS LED, Low active */\
        set_pio(15, ZGPIO_LEVEL_HIGH);   /* Power LED off */ \
        set_pio(21, ZGPIO_LEVEL_LOW);   /* WPS LED on */ \
} while(0)
#define CONFIG_BOOT_ZLOADER_CMD "bootm 9f030000"
#define FACTORY_RESET_BTN_GPIO_NO           23
#define FACTORY_RESET_BTN_TRIGGER_LEVEL     ZGPIO_LEVEL_LOW
#define UPDATE_RAS_IMG_BTN_GPIO_NO          22 /* WPS button */
#define UPDATE_RAS_IMG_BTN_TRIGGER_LEVEL    ZGPIO_LEVEL_LOW
#define SENAO_FACTORY_BTN_GPIO_NO           14
#define SENAO_FACTORY_BTN_TRIGGER_LEVEL     ZGPIO_LEVEL_LOW
#else
#define CONFIG_BOOTDELAY	3	/* autoboot after 3 seconds	*/
#endif

/*-----------------------------------------------------------------------
 * Atheros Source Code Configuration
 */
/* see see lsdk-10.0.91/boot/u-boot/include/configs/board955x.h */
#undef MTDPARTS_DEFAULT
#undef CFG_HZ

#include <atheros.h>
	
#define CFG_FLASH_SECTOR_SIZE	(64*1024)
#if (FLASH_SIZE == 16)
#define CFG_FLASH_SIZE		0x01000000	/* Total flash size */
#elif (FLASH_SIZE == 8)
#define CFG_FLASH_SIZE		0x00800000	/* max number of sectors on one chip */
#else
#define CFG_FLASH_SIZE		0x00400000	/* Total flash size */
#endif

/* Don't regster PCI functions for u-boot, only init PCI interface.
 * it means that we no need the 'drivers/pci/libpci.a'. */
#define CONFIG_ATH_SKIP_REGISTER_PCI_API

#define CONFIG_PCI_CONFIG_DATA_IN_OTP
#define CFG_DDR_REFRESH_VAL		0x4138

/*
** Parameters defining the location of the calibration/initialization
** information for the two Merlin devices.
** NOTE: **This will change with different flash configurations**
*/

#define WLANCAL				0x9fff1000
#define BOARDCAL			0x9fff0000
#define ATHEROS_PRODUCT_ID		137
#define CAL_SECTOR			(CONFIG_SYS_MAX_FLASH_SECT - 1)

/* For Merlin, both PCI, PCI-E interfaces are valid */
#define ATH_ART_PCICFG_OFFSET		12

#undef CFG_ATHRS26_PHY
#define CFG_MII0_RMII			1
/* Compilation flag: CFG_ATH_SWAP_ETHACT
   Due do Atheros ethernet driver will setup WAN port as 'eth0', 
   LAN port as 'eth1', so using this compilation flag to swap it.
 */
#define CFG_ATH_SWAP_ETHACT		1

//#define CFG_ATHRS17_PHY_DBG_CMD		1

/* for support 256M bytes DDR on our board */
#define CONFIG_TB614

/*-----------------------------------------------------------------------
 * Board Configuration
 */
#define CONFIG_BOARD_NBG6716		1
#define CONFIG_BOARD_NAME		"NBG6716"


/*-----------------------------------------------------------------------
 * CPU Core Configuration
 */
/* see include/955x.h */


/*-----------------------------------------------------------------------
 * Cache Configuration
 */
/* see include/955x.h */


/*-----------------------------------------------------------------------
 * Miscellaneous configurable options
 */
#define CONFIG_VERSION_VARIABLE	/* keep u-boot version string in environment */
//#define CONFIG_SYS_LONGHELP		/* undef to save memory      */
#define CONFIG_SYS_PROMPT           CONFIG_BOARD_NAME "# "              /* Monitor Command Prompt    */
#define CONFIG_SYS_CBSIZE           512         /* Console I/O Buffer Size   */
#define CONFIG_SYS_PBSIZE           (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)  /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS          16          /* max number of command args*/
#define CONFIG_SYS_MALLOC_LEN           256*1024
#define CONFIG_SYS_BOOTPARAMS_LEN       128*1024
#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_SYS_MEMTEST_START	0x80200000
#define CONFIG_SYS_MEMTEST_END		0x83800000
#define CONFIG_LZMA			1
#define CONFIG_SYS_MONITOR_BASE		TEXT_BASE
#define CONFIG_SYS_MONITOR_LEN		CFG_LOADER_PART_SIZE

#define CONFIG_SYS_64BIT_VSPRINTF

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
#ifndef CONFIG_ATH_NAND_SUPPORT
#error "Error!! This configuration is used for NOR+NAND feature on NBG6716"
#endif
#define CONFIG_SYS_NAND_MAX_CHIPS	1
#define CONFIG_SYS_MAX_NAND_DEVICE	1

#define CONFIG_ENV_IS_IN_FLASH		1
#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max number of memory banks */
#if defined(CONFIG_ATH_NAND_BR) && defined(COMPRESSED_UBOOT)
#define CONFIG_SYS_FLASH_BASE			0xa0100000
#else
/* NOR Flash start address */
#define CONFIG_SYS_FLASH_BASE			0x9f000000
#endif
#ifdef COMPRESSED_UBOOT
#define BOOTSTRAP_TEXT_BASE		CONFIG_SYS_FLASH_BASE
#define BOOTSTRAP_CFG_MONITOR_BASE	BOOTSTRAP_TEXT_BASE
#endif
#if (FLASH_SIZE == 16)
#define CONFIG_SYS_MAX_FLASH_SECT	256	/* max number of sectors on one chip */
#elif (FLASH_SIZE == 8)
#define CONFIG_SYS_MAX_FLASH_SECT	128	/* max number of sectors on one chip */
#else
#define CONFIG_SYS_MAX_FLASH_SECT	64	/* max number of sectors on one chip */
#endif

#if (CONFIG_SYS_MAX_FLASH_SECT * CFG_FLASH_SECTOR_SIZE) != CFG_FLASH_SIZE
#	error "Invalid flash configuration"
#endif

#define CONFIG_ENV_SECT_SIZE	CFG_FLASH_SECTOR_SIZE
#define CONFIG_ENV_SIZE		CFG_ENV_PART_SIZE
#define CONFIG_ENV_ADDR		(CONFIG_SYS_FLASH_BASE + CONFIG_SYS_MONITOR_LEN)
#define CONFIG_ENV_OVERWRITE
/* CONFIG_ENV_VERSION
 *   v1.0: initial version
 *   v1.1: add environment variable 'env_readonly' to set partition 'env' as read-only
 *   v1.2: rename environment variable 'env_readonly' to 'readonly' for setting
 *         partition 'env' & 'RFData' as read-only
 *   v1.3: add environment variable 'zld_ver' to record zloader version and put it in
 *         kernel command line
 *   v1.4: set loader partition as ready-only mode, except in HTP mode.
 *         rename some environment variables for reduce code size
 *   v1.5: pass rootfstype=squashfs,jffs2 to kernel, let it can using SQUASHFS filesystem
 */
#define CONFIG_ENV_VERSION          "1.5"

/*-----------------------------------------------------------------------
 * Partition Configuration
 */
#undef	CONFIG_BOOTARGS

//#define CFG_ZLD_IN_NAND
#define CFG_RAS_IN_NAND
#define CFG_ROMD_IN_NAND

#define __gen_nand_cmd(cmd, offs, file, eraseCmd, writeCmd, eraseSize)	\
	#cmd "=tftp ${loadaddr} ${dir}" #file ";"						\
	#eraseCmd " " #offs " " #eraseSize ";"							\
	#writeCmd " ${fileaddr} " #offs " ${filesize}\0"

#define gen_nand_cmd(cmd, offs, file, partSize)			\
	__gen_nand_cmd(cmd, offs, file, nand erase, nand write, partSize)

#ifndef CONFIG_ZYXEL_ZLOADER
#define __gen_cmd(cmd, offs, file, eraseCmd, writeCmd, eraseSize)	\
	#cmd "=tftp ${loadaddr} ${dir}" #file ";"						\
	#eraseCmd " " #offs " +" #eraseSize ";"							\
	#writeCmd " ${fileaddr} " #offs " ${filesize}\0"

#define gen_cmd(cmd, offs, file, partSize)							\
	__gen_cmd(cmd, offs, file, erase, cp.b, partSize)
#else
#define __gen_cmd(cmd, offs, file, eraseCmd, writeCmd, eraseSize)	\
	#cmd "=tftp ${loadaddr} ${dir}" #file ";"						\
	#eraseCmd " " #offs " " #eraseSize ";"							\
	#writeCmd " ${fileaddr} " #offs " ${filesize}\0"

#define gen_cmd(cmd, offs, file, partSize)							\
	__gen_cmd(cmd, offs, file, zflash erase, zflash write, partSize)
#endif

#define __gen_img_env_val(name, addr, size)	\
	#name "_paddr=" #addr "\0"			\
	#name "_psize=" #size "\0"

#define gen_img_env_val(name, addr, size)	\
	__gen_img_env_val(name, addr, size)


#define CFG_LOADER_PART_ADDR		CONFIG_SYS_FLASH_BASE
#ifdef CONFIG_EMBEDDED_KERNEL_IN_ROOTFS
  #define CFG_LOADER_PART_SIZE		0x40000
  #define CFG_ENV_PART_ADDR		0x9f040000
  #define CFG_ENV_PART_SIZE		0x10000
  #define CFG_RFDATA_PART_ADDR      	0x9f050000
  #define CFG_RFDATA_PART_SIZE      	0x10000
  #define CFG_ROOTFSDATA_PART_ADDR  	0
  #define CFG_ROOTFSDATA_PART_SIZE  	0x200000
 #ifdef CONFIG_USING_ROMD_PARTITION
  #define CFG_ROMD_PART_ADDR		0x200000
  #define CFG_ROMD_PART_SIZE		0x200000
  #define CFG_ROMDHDR_PART_SIZE     	0x20
  #define CFG_HEADER_PART_ADDR      	0x400000
  #define CFG_HEADER_PART_SIZE      	0x100000
  #define CFG_HEADER_IMG_SIZE		0x20000
  #define CFG_ROOTFS_PART_ADDR		0x500000
  #define CFG_ROOTFS_PART_SIZE		0x1E00000
  #define CFG_HEADER1_PART_ADDR        	0x2300000
  #define CFG_HEADER1_PART_SIZE      	0x100000
  #define CFG_HEADER1_IMG_EXTEND_SIZE	0x20000
  #define CFG_ROOTFS1_PART_ADDR		0x2400000
  #define CFG_ROOTFS1_PART_SIZE		0x1E00000
  #define CFG_BU1_PART_ADDR		0x4200000
  #define CFG_BU1_PART_SIZE		0x200000
 #else
  #error "Must be using ROMD partition for this configuration!"
 #endif /* CONFIG_USING_ROMD_PARTITION */

  #define LOADER_IMG_ENV_VAL	gen_img_env_val(ldr, CFG_LOADER_PART_ADDR, CFG_LOADER_PART_SIZE)
  #define ENV_IMG_ENV_VAL	gen_img_env_val(env, CFG_ENV_PART_ADDR, CFG_ENV_PART_SIZE)
  #define RFDATA_IMG_ENV_VAL	gen_img_env_val(rfdat, CFG_RFDATA_PART_ADDR, CFG_RFDATA_PART_SIZE)
  #define RTFSDATA_IMG_ENV_VAL	gen_img_env_val(rfsdat, CFG_ROOTFSDATA_PART_ADDR, CFG_ROOTFSDATA_PART_SIZE)
  #define HEADER_IMG_ENV_VAL    gen_img_env_val(hdr, CFG_HEADER_PART_ADDR, CFG_HEADER_PART_SIZE)
  #define ROOTFS_IMG_ENV_VAL	gen_img_env_val(rfs, CFG_ROOTFS_PART_ADDR, CFG_ROOTFS_PART_SIZE)
  #define ROMD_IMG_ENV_VAL	gen_img_env_val(romd, CFG_ROMD_PART_ADDR, CFG_ROMD_PART_SIZE)
  #define HEADER1_IMG_ENV_VAL   gen_img_env_val(hdr1, CFG_HEADER1_PART_ADDR, CFG_HEADER1_PART_SIZE)
  #define ROOTFS1_IMG_ENV_VAL	gen_img_env_val(rfs1, CFG_ROOTFS1_PART_ADDR, CFG_ROOTFS1_PART_SIZE)
  #define BU1_IMG_ENV_VAL	gen_img_env_val(bu1, CFG_BU1_PART_ADDR, CFG_BU1_PART_SIZE)

  #define UPDATE_LOADER_CMD     gen_cmd(lu, ${ldr_paddr}, u-boot.bin, ${ldr_psize})
  #define UPDATE_ROOTFS_CMD     gen_nand_cmd(lf, ${rfs_paddr}, ${img_prefix}rootfs.jffs2, ${rootfs_psize})

  #define IMG_ENV_VAL           LOADER_IMG_ENV_VAL ENV_IMG_ENV_VAL RFDATA_IMG_ENV_VAL \
                                RTFSDATA_IMG_ENV_VAL ROMD_IMG_ENV_VAL HEADER_IMG_ENV_VAL \
				ROOTFS_IMG_ENV_VAL HEADER1_IMG_ENV_VAL \
				ROOTFS1_IMG_ENV_VAL BU1_IMG_ENV_VAL
  #define MTDPARTS_DEFAULT      "mtdparts=spi0.0:${ldr_psize}(u-boot)${readonly},${env_psize}(env)${readonly},${rfdat_psize}(RFdata)${readonly},-(nbu)\\;ath79-nand:${rfsdat_psize}(rootfs_data),${romd_psize}(romd),${hdr_psize}(header),${rfs_psize}(rootfs),${hdr1_psize}(header1),${rfs1_psize}(rootfs1),${bu1_psize}(bu1),-(bu2)"
  #define ROOTFS_MTD_NO		"mtdblock7"
  #define UPGRADE_IMG_CMD	UPDATE_LOADER_CMD UPDATE_ROOTFS_CMD

  #define BOOT_FLASH_CMD        "boot_flash=run setmtdparts flashargs addtty addmtd;fsload ${loadaddr} /boot/vmlinux.lzma.uImage;bootm ${loadaddr}\0"
  #define BOOTARG_DEFAULT	"board=" CONFIG_BOARD_NAME " root=/dev/" ROOTFS_MTD_NO " rootfstype=jffs2 noinitrd ${bootmode} ${zld_ver}"
#else
  #error "This configuration must be enable option 'CONFIG_EMBEDDED_KERNEL_IN_ROOTFS'"
#endif

/* ROOTFS_MTD_NO, MTDPARTS_DEFAULT, BOOT_FLASH_CMD, IMG_ENV_VAL, UPGRADE_IMG_CMD */
#define	CONFIG_EXTRA_ENV_SETTINGS					\
    "uboot_env_ver=" CONFIG_ENV_VERSION "\0" \
    "img_prefix=nbg6716-\0"	\
    "loadaddr=80400000\0" \
    "readonly=ro\0" \
    "setmtdparts=setenv mtdparts " MTDPARTS_DEFAULT "\0" \
    "flashargs=setenv bootargs " BOOTARG_DEFAULT "\0"  \
    "addtty=setenv bootargs ${bootargs} console=ttyS0,${baudrate}\0" \
    "addmtd=setenv bootargs ${bootargs} ${mtdparts}\0" \
    BOOT_FLASH_CMD \
    "bootcmd=run boot_flash\0" \
    IMG_ENV_VAL \
    UPGRADE_IMG_CMD \
    "countrycode=ff\0" \
    "serialnum=S100Z47000001\0" \
    "hostname=NBG6716\0"


/*-----------------------------------------------------------------------
 * JFFS2 Filesystem Configuration
 */
#define CONFIG_CMD_JFFS2
#define CONFIG_CMD_JFFS2_ULOAD
#define CONFIG_JFFS2_SUMMARY
//#define CONFIG_CMD_JFFS2_LS
//#define CONFIG_CMD_JFFS2_FSINFO
#if defined(CFG_RAS_IN_NAND)
#define CONFIG_JFFS2_NAND
#define CONFIG_JFFS2_PART_OFFSET	CFG_ROOTFS_PART_ADDR
// Default using remaining flash space if you ignore 'CONFIG_JFFS_PART_SIZE'
#define CONFIG_JFFS2_PART_SIZE		CFG_ROOTFS_PART_SIZE
#define CONFIG_JFFS2_DEV		"nand0"
#else
#define CONFIG_JFFS2_PART_OFFSET	(CFG_ROOTFS_PART_ADDR-CONFIG_SYS_FLASH_BASE)
// Default using remaining flash space if you ignore 'CONFIG_JFFS_PART_SIZE'
#define CONFIG_JFFS2_PART_SIZE		CFG_ROOTFS_PART_SIZE
#endif


/*-----------------------------------------------------------------------
 * Networking Configuration
 */
#define CONFIG_SERVERIP 192.168.1.33
#define CONFIG_IPADDR 192.168.1.1
#define CONFIG_ETHADDR 00:AA:BB:CC:DD:00

#define CONFIG_NET_MULTI

#ifndef CONFIG_ZYXEL_ZLOADER
#define CONFIG_MII
#define CONFIG_CMD_MII
#define CONFIG_PHY_GIGE
#endif

#define CONFIG_SYS_CONSOLE_INFO_QUIET
//#define CONFIG_SILENT_CONSOLE
#define CONFIG_DISABLE_CONSOLE


/*-----------------------------------------------------------------------
 * PCI Configuration
 */
#define CONFIG_PCI

/*-----------------------------------------------------------------------
 * Command line configuration.
 */
#include <config_cmd_default.h>

#define CONFIG_CMD_NAND

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
#undef CONFIG_CMD_LOADB
#undef CONFIG_CMD_IMI
//#undef CONFIG_TIMESTAMP
#endif
#undef CONFIG_CMD_CONSOLE
#undef CONFIG_CMD_FPGA
#undef CONFIG_CMD_ITEST
#undef CONFIG_CMD_LOADS
#undef CONFIG_CMD_NFS
#undef CONFIG_CMD_SETGETDCR
#undef CONFIG_CMD_SOURCE
#undef CONFIG_CMD_XIMG


#if TEXT_BASE != 0x9F000000
#define CONFIG_SKIP_LOWLEVEL_INIT
#endif

#endif	/* __CONFIG_H */
