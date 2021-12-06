/*
 * This file contains the configuration parameters for the Atheros AP123 board.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*-----------------------------------------------------------------------
 * ZyXEL zloader configuration.
 */
#ifdef CONFIG_ZYXEL_ZLOADER
#define CONFIG_ZYXEL_MULTIBOOT
#define CONFIG_AR7240_GPIO
#define CONFIG_AR7240_MAX_GPIO_NUM  22
#define CONFIG_ZGPIO_CMD
#define CONFIG_ZFLASH_CMD
#define ZLOADER_EXEC_FAILED_LED_INDICATE \
do { \
        configure_pio(4, ZGPIO_CONFIG_OUTPUT); \
        configure_pio(14, ZGPIO_CONFIG_OUTPUT); \
        set_pio(4, ZGPIO_LEVEL_LOW);   /* Power LED off */ \
        set_pio(14, ZGPIO_LEVEL_HIGH);   /* WPS LED on */ \
} while(0)
#define CONFIG_BOOT_ZLOADER_CMD "bootm 9f020000"
#define FACTORY_RESET_BTN_GPIO_NO           18
#define FACTORY_RESET_BTN_TRIGGER_LEVEL     ZGPIO_LEVEL_LOW
#define UPDATE_RAS_IMG_BTN_GPIO_NO          21 /* WPS button */
#define UPDATE_RAS_IMG_BTN_TRIGGER_LEVEL    ZGPIO_LEVEL_LOW
#else
#define CONFIG_BOOTDELAY	3	/* autoboot after 3 seconds	*/
#endif

/*-----------------------------------------------------------------------
 * Atheros Source Code Configuration
 */
/* See cpu/mips/ar7240/Makefile */
#define CONFIG_SOC_AG934X           1
#if !defined(CONFIG_ATH_NAND_FL)
#define FLASH_SIZE 4
#endif
#define CFG_FLASH_SECTOR_SIZE   (64*1024)
#if (FLASH_SIZE == 16)
#define CFG_FLASH_SIZE          0x01000000 /* Total flash size */
#elif (FLASH_SIZE == 8)
#define CFG_FLASH_SIZE          0x00800000    /* max number of sectors on one chip */
#else
#define CFG_FLASH_SIZE          0x00400000 /* Total flash size */
#endif

#ifndef COMPRESSED_UBOOT
#define ENABLE_DYNAMIC_CONF 1
#endif
#define CONFIG_WASP_SUPPORT 1
#undef CFG_ATHRS26_PHY
/* S16 specific defines */
#define CONFIG_AG7240_GE0_IS_CONNECTED 1

// PLL Config for different CPU/DDR/AHB frequencies
#define CFG_PLL_200_200_100		0x00
#define CFG_PLL_300_300_150		0x01
#define CFG_PLL_320_320_160		0x02
#define CFG_PLL_340_340_170		0x03
#define CFG_PLL_350_350_175		0x04
#define CFG_PLL_360_360_180		0x05
#define CFG_PLL_400_400_200		0x06
#define CFG_PLL_300_300_75		0x07
#define CFG_PLL_400_400_100		0x08
#define CFG_PLL_320_320_80		0x09
#define CFG_PLL_410_400_200		0x0a
#define CFG_PLL_420_400_200		0x0b
#define CFG_PLL_80_80_40		0x0c
#define CFG_PLL_64_64_32		0x0d
#define CFG_PLL_48_48_24		0x0e
#define CFG_PLL_32_32_16		0x0f
#define CFG_PLL_333_333_166		0x10
#define CFG_PLL_266_266_133		0x11
#define CFG_PLL_266_266_66		0x12
#define CFG_PLL_240_240_120		0x13
#define CFG_PLL_160_160_80		0x14
#define CFG_PLL_400_200_200		0x15
#define CFG_PLL_500_400_200		0x16
#define CFG_PLL_600_400_200		0x17
#define CFG_PLL_600_500_250		0x18
#define CFG_PLL_600_400_300		0x19
#define CFG_PLL_500_500_250		0x1a
#define CFG_PLL_600_350_175		0x1b
#define CFG_PLL_600_300_150		0x1c
#define CFG_PLL_600_550_1_1G_275	0x1d
#define CFG_PLL_600_500_1G_250		0x1e
#define CFG_PLL_533_400_200		0x1f
#define CFG_PLL_600_450_200		0x20
#define CFG_PLL_533_500_250		0x21
#define CFG_PLL_700_400_200		0x22
#define CFG_PLL_650_600_300		0x23
#define CFG_PLL_600_600_300		0x24
#define CFG_PLL_600_550_275		0x25
#define CFG_PLL_566_475_237		0x26
#define CFG_PLL_566_450_225		0x27
#define CFG_PLL_600_332_166		0x28
#define CFG_PLL_600_575_287		0x29
#define CFG_PLL_600_525_262		0x2a
#define CFG_PLL_566_550_275		0x2b
#define CFG_PLL_566_525_262		0x2c
#define CFG_PLL_600_332_200		0x2d
#define CFG_PLL_600_266_133		0x2e
#define CFG_PLL_600_266_200		0x2f
#define CFG_PLL_600_650_325		0x30
#define CFG_PLL_566_400_200		0x31
#define CFG_PLL_566_500_250		0x32
#define CFG_PLL_600_1_2G_400_200	0x33
#define CFG_PLL_560_480_240		0x34
#define CFG_PLL_333_166_166		0x35
#define CFG_PLL_350_175_175		0x36
#define CFG_PLL_360_180_180		0x37
#define CFG_PLL_380_190_190		0x38
#define CFG_PLL_262_262_131		0x39
#define CFG_PLL_275_275_137		0x3a
#define CFG_PLL_200_200_200		0x3b
#define CFG_PLL_250_250_125		0x3c
#define CFG_PLL_225_225_112		0x3d
#define CFG_PLL_212_212_106		0x3e
#define CFG_PLL_187_187_93		0x3f
#define CFG_PLL_535_400_200		0x40
#define CFG_PLL_560_400_200		0x41
#define CFG_PLL_560_450_225		0x42
#define CFG_PLL_400_480_240		0x43

#undef CFG_PLL_FREQ
#define CFG_PLL_FREQ			CFG_PLL_535_400_200

//#define CONFIG_NR_DRAM_BANKS	2
// Set this to zero, for 16bit ddr2
#define DDR2_32BIT_SUPPORT 	1
/* DDR settings for WASP */
#define CFG_DDR_REFRESH_VAL     0x4270
#define CFG_DDR_CONFIG_VAL      0xc7bc8cd0
#define CFG_DDR_MODE_VAL_INIT   0x133
#define CFG_DDR_EXT_MODE_VAL    0x0
#define CFG_DDR_MODE_VAL        0x33
#define CFG_DDR_TRTW_VAL        0x1f
#define CFG_DDR_TWTR_VAL        0x1e
#define CFG_DDR_CONFIG2_VAL     0x9dd0e6a8
#define CFG_DDR2_RD_DATA_THIS_CYCLE_VAL_32	0xff
#define CFG_DDR2_RD_DATA_THIS_CYCLE_VAL_16	0xffff

#if DDR2_32BIT_SUPPORT
#define CFG_DDR2_RD_DATA_THIS_CYCLE_VAL		CFG_DDR2_RD_DATA_THIS_CYCLE_VAL_32
#else
#define CFG_DDR2_RD_DATA_THIS_CYCLE_VAL		CFG_DDR2_RD_DATA_THIS_CYCLE_VAL_16
#endif

#define CFG_DDR1_RD_DATA_THIS_CYCLE_VAL		0xffff
#define CFG_SDRAM_RD_DATA_THIS_CYCLE_VAL	0xffffffff

/* DDR2 Init values */
#define CFG_DDR2_EXT_MODE_VAL    0x402

#if !defined(CONFIG_WASP) && defined(ENABLE_DYNAMIC_CONF)
#define CFG_DDR_MAGIC           0xaabacada
#define CFG_DDR_MAGIC_F         (UBOOT_ENV_SEC_START + CFG_FLASH_SECTOR_SIZE - 0x30)
#define CFG_DDR_CONFIG_VAL_F    *(volatile int *)(CFG_DDR_MAGIC_F + 4)
#define CFG_DDR_CONFIG2_VAL_F	*(volatile int *)(CFG_DDR_MAGIC_F + 8)
#define CFG_DDR_EXT_MODE_VAL_F  *(volatile int *)(CFG_DDR_MAGIC_F + 12)
#endif
//#define CFG_WAH132 1 

/*
** Parameters defining the location of the calibration/initialization
** information for the two Merlin devices.
** NOTE: **This will change with different flash configurations**
*/
#define WLANCAL                         0x9fff1000
#define BOARDCAL                        0x9fff0000
#define ATHEROS_PRODUCT_ID              137
#define CAL_SECTOR                      (CFG_MAX_FLASH_SECT - 1)


/*-----------------------------------------------------------------------
 * Board Configuration
 */
#define CONFIG_BOARD_AP123		1
#define CONFIG_BOARD_NAME		"AP123"

/*-----------------------------------------------------------------------
 * CPU Core Configuration
 */
#define CONFIG_MIPS32		1	/* MIPS 47Kc CPU core	*/
#define CONFIG_MEMSIZE_IN_BYTES

/*
 * MIPS32 24K Processor Core Family Software User's Manual
 *
 * 6.2.9 Count Register (CP0 Register 9, Select 0)
 * The Count register acts as a timer, incrementing at a constant
 * rate, whether or not an instruction is executed, retired, or
 * any forward progress is made through the pipeline.  The counter
 * increments every other clock, if the DC bit in the Cause register
 * is 0.
 */
/* Since the count is incremented every other tick, divide by 2 */
/* XXX derive this from CFG_PLL_FREQ */
#if (CFG_PLL_FREQ == CFG_PLL_200_200_100)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (200000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_300_300_150)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (300000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_350_350_175)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (350000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_333_333_166)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (333000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_266_266_133)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (266000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_266_266_66)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (266000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_400_400_200) || (CFG_PLL_FREQ == CFG_PLL_400_400_100)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (400000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_320_320_80) || (CFG_PLL_FREQ == CFG_PLL_320_320_160)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (320000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_410_400_200)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (410000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_420_400_200)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (420000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_240_240_120)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (240000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_160_160_80)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (160000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_400_200_200)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (400000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_500_400_200)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (500000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_600_400_200) || (CFG_PLL_FREQ == CFG_PLL_600_450_200) || \
      (CFG_PLL_FREQ == CFG_PLL_600_600_300) || (CFG_PLL_FREQ == CFG_PLL_600_550_275) || \
      (CFG_PLL_FREQ == CFG_PLL_600_332_166) || (CFG_PLL_FREQ == CFG_PLL_600_575_287) || \
      (CFG_PLL_FREQ == CFG_PLL_600_525_262) || (CFG_PLL_FREQ == CFG_PLL_600_332_200) || \
      (CFG_PLL_FREQ == CFG_PLL_600_266_133) || (CFG_PLL_FREQ == CFG_PLL_600_266_200) || \
      (CFG_PLL_FREQ == CFG_PLL_600_650_325) ||  (CFG_PLL_FREQ == CFG_PLL_600_1_2G_400_200)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (600000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_600_1_2G_400_200)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (600000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_600_500_1G_250)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (600000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_600_550_1_1G_275)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (600000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_600_500_250)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (600000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_600_350_175)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (600000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_600_300_150)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (600000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_533_400_200) || (CFG_PLL_FREQ == CFG_PLL_533_500_250)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (533000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_535_400_200)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (535000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_700_400_200)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (700000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_650_600_300)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (650000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_560_480_240)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (560000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_566_475_237) || (CFG_PLL_FREQ == CFG_PLL_566_450_225) || \
      (CFG_PLL_FREQ == CFG_PLL_566_550_275) || (CFG_PLL_FREQ == CFG_PLL_566_525_262) || \
      (CFG_PLL_FREQ == CFG_PLL_566_400_200) || (CFG_PLL_FREQ == CFG_PLL_566_500_250)
#   define CONFIG_SYS_MIPS_TIMER_FREQ          (566000000/2)
#endif

/*-----------------------------------------------------------------------
 * Cache Configuration
 */
#define CONFIG_SYS_DCACHE_SIZE		(32*1024)
#define CONFIG_SYS_ICACHE_SIZE		(64*1024)
#define CONFIG_SYS_CACHELINE_SIZE   32

/*-----------------------------------------------------------------------
 * Miscellaneous configurable options
 */
#define CONFIG_BAUDRATE		115200

#define CONFIG_SERVERIP 192.168.1.33
#define CONFIG_IPADDR 192.168.1.1
#define CONFIG_ETHADDR 00:AA:BB:CC:DD:00
/* valid baudrates */
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

#define	CONFIG_TIMESTAMP		/* Print image info with timestamp */
#define CONFIG_VERSION_VARIABLE     /* keep u-boot version string in environment */
#define CONFIG_SYS_LONGHELP			        /* undef to save memory	     */
#define CONFIG_SYS_PROMPT           CONFIG_BOARD_NAME "# "		/* Monitor Command Prompt    */
#define CONFIG_SYS_CBSIZE           256		/* Console I/O Buffer Size   */
#define CONFIG_SYS_PBSIZE           (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)  /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS          16		/* max number of command args*/
#define CONFIG_SYS_MALLOC_LEN		256*1024

#define CONFIG_SYS_BOOTPARAMS_LEN	128*1024

#define CONFIG_SYS_HZ               1000

#define CONFIG_SYS_SDRAM_BASE		0x80000000 /* Cached addr */
#define CONFIG_NR_DRAM_BANKS        1
#define CONFIG_SYS_LOAD_ADDR		0x81000000	/* default load address */
#define CONFIG_SYS_MEMTEST_START	0x80200000
#define CONFIG_SYS_MEMTEST_END		0x83800000
#define CONFIG_LZMA                 1
#define CONFIG_SYS_INIT_SP_OFFSET	0x1000
#define	CONFIG_SYS_MONITOR_BASE		TEXT_BASE
#define	CONFIG_SYS_MONITOR_LEN		CFG_LOADER_PART_SIZE


/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
#define	CONFIG_ENV_IS_IN_FLASH    1
#undef CONFIG_ENV_IS_NOWHERE
#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max number of memory banks */
/* Assuming nand flash wouldn't use compressed u-boot */
#ifdef CONFIG_ATH_NAND_FL
#	define CONFIG_SYS_FLASH_BASE			0
#else
#	define CONFIG_SYS_FLASH_BASE			0x9f000000
#endif
#define CONFIG_SYS_FLASH_ERASE_TOUT	(2 * CFG_HZ) /* Timeout for Flash Erase */
#define CONFIG_SYS_FLASH_WRITE_TOUT	(2 * CFG_HZ) /* Timeout for Flash Write */
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
#define CONFIG_SYS_JFFS2_FIRST_BANK   1
#define CONFIG_SYS_JFFS2_NUM_BANKS	1

#define CONFIG_ENV_SECT_SIZE        CFG_FLASH_SECTOR_SIZE
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
	#name "_part_addr=" #addr "\0"			\
	#name "_part_size=" #size "\0"

#define gen_img_env_val(name, addr, size)	\
	__gen_img_env_val(name, addr, size)


#define CFG_LOADER_PART_ADDR		CONFIG_SYS_FLASH_BASE
#ifdef CONFIG_EMBEDDED_KERNEL_IN_ROOTFS
  #define CFG_LOADER_PART_SIZE		0x30000
  #define CFG_ENV_PART_ADDR			0x9f030000
  #define CFG_ENV_PART_SIZE			0x10000
  #define CFG_RFDATA_PART_ADDR      0x9f040000
  #define CFG_RFDATA_PART_SIZE      0x10000
  #define CFG_ROOTFSDATA_PART_ADDR  0x9f050000
  #define CFG_ROOTFSDATA_PART_SIZE  0x60000
  #define CFG_HEADER_PART_ADDR      0x9f0b0000
  #define CFG_HEADER_PART_SIZE      0x10000
  #define CFG_ROOTFS_PART_ADDR		0x9f0c0000
  #define CFG_ROOTFS_PART_SIZE		0x340000
  #define CFG_RAS_PART_ADDR         0x9f0b0000
  #define CFG_RAS_PART_SIZE         0x350000
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
  #define MTDPARTS_DEFAULT		"mtdparts=ath-nor0:${loader_part_size}(u-boot),${env_part_size}(env)${readonly},${rfdat_part_size}(RFdata)${readonly},${rtfsdat_part_size}(rootfs_data),${hdr_part_size}(header),${rootfs_part_size}(rootfs)\0"
  #define BOOT_FLASH_CMD		"boot_flash=run setmtdparts flashargs addtty addmtd;fsload ${loadaddr} /boot/vmlinux.lzma.uImage;bootm ${loadaddr}\0"
  #define INIT_PROCESS_ENV      "/etc/preinit"
#else
  #define CFG_LOADER_PART_SIZE		0x40000
  #define CFG_ENV_PART_ADDR			0x9f040000
  #define CFG_ENV_PART_SIZE			0x10000
  #define CFG_ROOTFS_PART_ADDR		0x9f050000
  #define CFG_ROOTFS_PART_SIZE		0x230000
  #define CFG_KERNEL_PART_ADDR		0x9f280000
  #define CFG_KERNEL_PART_SIZE		0x160000
  #define CFG_MIB0_PART_ADDR		0x9f3E0000
  #define CFG_MIB0_PART_SIZE		0x10000
  #define CFG_ART_PART_ADDR         0x9f3F0000
  #define CFG_ART_PART_SIZE         0x10000

  #define LOADER_IMG_ENV_VAL	gen_img_env_val(loader, CFG_LOADER_PART_ADDR, CFG_LOADER_PART_SIZE)
  #define ENV_IMG_ENV_VAL		gen_img_env_val(env, CFG_ENV_PART_ADDR, CFG_ENV_PART_SIZE)
  #define ROOTFS_IMG_ENV_VAL	gen_img_env_val(rootfs, CFG_ROOTFS_PART_ADDR, CFG_ROOTFS_PART_SIZE)
  #define KERNEL_IMG_ENV_VAL	gen_img_env_val(kernel, CFG_KERNEL_PART_ADDR, CFG_KERNEL_PART_SIZE)
  #define MIB0_IMG_ENV_VAL      gen_img_env_val(mib0, CFG_MIB0_PART_ADDR, CFG_MIB0_PART_SIZE)
  #define ART_IMG_ENV_VAL       gen_img_env_val(art, CFG_ART_PART_ADDR, CFG_ART_PART_SIZE)

  #define UPDATE_LOADER_CMD     gen_cmd(lu, ${loader_part_addr}, u-boot.bin, ${loader_part_size})
  #define UPDATE_KERNEL_CMD		gen_cmd(lk, ${kernel_part_addr}, ${img_prefix}vmlinux.lzma.uImage, ${kernel_part_size})
  #define UPDATE_ROOTFS_CMD     gen_cmd(lf, ${rootfs_part_addr}, ${img_prefix}rootfs.jffs2, ${rootfs_part_size})

  #define IMG_ENV_VAL           LOADER_IMG_ENV_VAL ENV_IMG_ENV_VAL KERNEL_IMG_ENV_VAL ROOTFS_IMG_ENV_VAL MIB0_IMG_ENV_VAL ART_IMG_ENV_VAL
  #define UPGRADE_IMG_CMD		KERNEL_IMG_ENV_VAL UPDATE_LOADER_CMD UPDATE_KERNEL_CMD UPDATE_ROOTFS_CMD

  #define ROOTFS_MTD_NO			"root_mtdblock_no=2\0"
  #define MTDPARTS_DEFAULT		"mtdparts=ath-nor0:${loader_part_size}(u-boot),${env_part_size}(env),${rootfs_part_size}(rootfs),${kernel_part_size}(kernel),${mib0_part_size}(mib0),${art_part_size}(ART)\0"
  #define BOOT_FLASH_CMD		"boot_flash=run setmtdparts flashargs addtty addmtd;bootm ${kernel_part_addr}\0"
  #define INIT_PROCESS_ENV      "/sbin/init"
#endif
#if CONFIG_ENV_ADDR != CFG_ENV_PART_ADDR
    #error "Wrong address of u-boot environment partition"
#endif

/* ROOTFS_MTD_NO, MTDPARTS_DEFAULT, BOOT_FLASH_CMD, IMG_ENV_VAL, UPGRADE_IMG_CMD */
#define	CONFIG_EXTRA_ENV_SETTINGS					\
    "uboot_env_ver=" CONFIG_ENV_VERSION "\0" \
	"img_prefix=pla4231-\0"	\
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
	"hostname=AP123\0" \


/*-----------------------------------------------------------------------
 * JFFS2 Filesystem Configuration
 */
#define CONFIG_CMD_JFFS2
//#define CONFIG_CMD_JFFS2_LS
//#define CONFIG_CMD_JFFS2_FSINFO
#define CONFIG_JFFS2_PART_OFFSET	(CFG_ROOTFS_PART_ADDR-CONFIG_SYS_FLASH_BASE)
// Default using remaining flash space if you ignore 'CONFIG_JFFS_PART_SIZE'
#define CONFIG_JFFS2_PART_SIZE		CFG_ROOTFS_PART_SIZE


/*-----------------------------------------------------------------------
 * Networking Configuration
 */
#define CONFIG_NET_MULTI
#define CONFIG_SYS_RX_ETH_BUFFER   16
//#define CFG_PHY_ADDR 0 
//#define CFG_GMII     0
#define CFG_MII0_RMII             1
#define CFG_AG7100_GE0_RMII             1

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
#undef CONFIG_PCI
#ifdef CONFIG_PCI
#define CONFIG_SHUTDOWN_PCIE_USB 1
/* For Merlin, both PCI, PCI-E interfaces are valid */
#define AR7240_ART_PCICFG_OFFSET        12
#endif


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
#undef CONFIG_CMD_LOADB
#undef CONFIG_CMD_IMI
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
