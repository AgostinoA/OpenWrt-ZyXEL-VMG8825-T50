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

#define CONFIG_BOOTDELAY         3

/*-----------------------------------------------------------------------
 * Comcerto Source Code Configuration
 */
#define CONFIG_COMCERTO          1
#define CONFIG_COMCERTO_1000     1
#include <asm/hardware.h>

#define CONFIG_IDENT_STRING     " Mindspeed $Name: uboot_7_00_5 $"
#define CFG_REFCLKFREQ          24000000        /* 24 MHz */
#define CFG_PHY_CLOCK           125000000       /* 125 MHz*/
#define CFG_GEM0_CLOCK           25000000       /*  25 MHz*/
#define CFG_GEM1_CLOCK           25000000       /*  25 MHz*/

#define CFG_DDR_16BIT		1

/* DDR Training algorithm */
#define DDR_TRAINING
//#undef DDR_TRAINING
#define DDR_TRAINING_DBG


 /*-----------------------------------------------------------------------
 * Board Configuration
 */
#define CONFIG_BOARD_SHG3305     1    /* board */
/* Linux boot configuration */
#define CONFIG_CMDLINE_TAG       1    /* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS 1

#define LINUX_BOOTPARAM_ADDR            (PHYS_SDRAM + MSP_BOTTOM_MEMORY_RESERVED_SIZE + 0x100)
/* define one of these to choose the UART0 or UART1 as console */
#define CONFIG_UART0            1
#define BOARD_LATE_INIT
#define MSP_BOTTOM_MEMORY_RESERVED_SIZE 0x800000        /* 8 MiB reserved for MSP */
#define MSP_TOP_MEMORY_RESERVED_SIZE    0x0             /* 0 MiB reserved for MSP */


/* NAND GPIOs config */
#define CFG_NAND_BR_GPIO        6
#define CFG_NAND_CE_GPIO        29
#define CFG_NAND_CLE_GPIO       31
#define CFG_NAND_ALE_GPIO       30

/* Initial stack configuration */
#define CONFIG_SYS_INIT_RAM_ADDR        0x0A000000 /* ARAM_BASEADDR Base address */
#define CONFIG_SYS_INIT_RAM_END         0x00020000 /* 128K */
#define CFG_ARAM_CODE_SIZE                      0x00010000 /* 64K */
/*-----------------------------------------------------------------------
 * CPU Core Configuration
 */
#define CONFIG_ARM1136           1    /* This is an arm1136 CPU core */
#undef CONFIG_USE_IRQ                 /* no support for IRQs */
/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE          1
#define CONFIG_BAUDRATE               115200
#define CONFIG_SYS_BAUDRATE_TABLE     {115200, 19200, 38400, 57600, 9600}
#define CONFIG_SERVERIP          192.168.1.33
#define CONFIG_IPADDR            192.168.1.1
#define CONFIG_ETHADDR           00:aa:bb:cc:dd:ee

#define	CONFIG_TIMESTAMP		/* Print image info with timestamp */
#define CONFIG_VERSION_VARIABLE     /* keep u-boot version string in environment */
#define CONFIG_SYS_LONGHELP             /* undef to save memory */
#define CONFIG_SYS_PROMPT               "Comcerto-1000 > "      /* Monitor Command Prompt */
#define CONFIG_SYS_CBSIZE               256  /* Console I/O Buffer Size */
/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE               (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)
#define CONFIG_SYS_MAXARGS              16          /* max number of command args */

/* Malloc/stack configuration */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 128 * 1024)
#define CONFIG_SYS_GBL_DATA_SIZE        128  /* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_OFFSET      (CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)

/*-----------------------------------------------------------------------
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below
 */
#define CONFIG_STACKSIZE         (32 * 1024)     /* regular stack */
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ     SZ_4K   /* IRQ stack */
#define CONFIG_STACKSIZE_FIQ     SZ_4K   /* FIQ stack */
#endif
#define CONFIG_SYS_HZ           1000

/* Memory Mapping */
#define CONFIG_NR_DRAM_BANKS    1
#define PHYS_SDRAM              DDR_BASEADDR
#define PHYS_SDRAM_SIZE         0x20000000      /* 512 MB */

#define CONFIG_SYS_LOAD_ADDR            (PHYS_SDRAM + 0x01000000)       /* default load address */
#define CONFIG_SYS_MEMTEST_START        CONFIG_SYS_LOAD_ADDR       /* default load address */
#define CONFIG_SYS_MEMTEST_END          (CONFIG_SYS_MEMTEST_START + 0x800000)

#define CONFIG_LZMA					1

#define CONFIG_SYS_INIT_SP_OFFSET       CONFIG_SYS_GBL_DATA_OFFSET - CFG_ARAM_CODE_SIZE

//#define CONFIG_SYS_CONSOLE_INFO_QUIET
//#define CONFIG_SILENT_CONSOLE
//#define CONFIG_DISABLE_CONSOLE

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
#define CONFIG_SYS_NAND_BASE            EXP_CS4_BASEADDR
#define CONFIG_SYS_MAX_NAND_DEVICE      1
#define CONFIG_SYS_NAND_MAX_CHIPS       1
#define CONFIG_ENV_IS_IN_NAND	1
#define CONFIG_ENV_OFFSET	0x00040000	/* environment starts here  */
#define CONFIG_ENV_SIZE         0x4000

/* CONFIG_ENV_VERSION
 *   v1.0: initial version
 *   v1.1: add environment variable 'env_readonly' to set partition 'env' as read-only
 *   v1.2: rename environment variable 'env_readonly' to 'readonly' for setting
 *         partition 'env' & 'RFData' as read-only
 *   v1.3: add environment variable 'zld_ver' to record zloader version and put it in
 *         kernel command line
 */
#define CONFIG_ENV_VERSION          "1.3"

#define CFG_LOADER_PART_ADDR            0
#define CFG_LOADER_PART_SIZE            0x40000
#define CFG_RFDATA_PART_ADDR            0x40000
#define CFG_RFDATA_PART_SIZE            0x20000
#define CFG_ROOTFS_PART_ADDR            0x60000
#define CFG_ROOTFS_PART_SIZE            0xC800000
#define CFG_ROOTFSDATA_PART_ADDR        0xC860000
#define CFG_ROOTFSDATA_PART_SIZE        0xC800000


/*
 * JFFS2 Configuration
 */
/* mtdparts command line support */
#define CONFIG_JFFS2_CMDLINE
#define MTDIDS_DEFAULT          "nand0=comcertonand"
#define MTDPARTS_DEFAULT        "mtdparts=comcertonand:256k(u-boot),256k(env),256k(header),16384k(bak),204800k(fs),286720k(rootfs_data)"
#define MTDPARTITION_DEFAULT    "nand0,4"
#define ROOT_MTDBLOCK           "/dev/mtdblock4"
#define BOOT_FLASH_CMD        "boot_flash=run setmtdparts flashargs addtty addmtd;fsload ${loadaddr} /boot/uImage;bootm ${loadaddr}\0"
#define INIT_PROCESS_ENV      "/etc/preinit"

#define CONFIG_EXTRA_ENV_SETTINGS               \
    "uboot_env_ver=" CONFIG_ENV_VERSION "\0" \
    "hostname=comcerto1000\0"                       \
    "netdev=eth0\0"                                 \
    "nfsargs=setenv bootargs init=${init_process} root=/dev/nfs rw "        \
        "nfsroot=${serverip}:${rootpath}\0"             \
    "flashargs=setenv bootargs init=${init_process} root="ROOT_MTDBLOCK" rootfstype=${rootfstype} rw\0"  \
    "rootfstype=jffs2\0" \
    "setmtdparts=setenv mtdparts " MTDPARTS_DEFAULT \
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
    BOOT_FLASH_CMD \
    "boot_flashold=run flashargs addeth addtty addmtd; fsload /boot/uImage; bootm\0" \
    "rootpath=/devel/fs-zyxel-shg3305\0" \
    "kernelfile=uImage\0" \
    "mtdids=" MTDIDS_DEFAULT "\0" \
    "mtdparts=" MTDPARTS_DEFAULT "\0" \
    "partition=" MTDPARTITION_DEFAULT "\0" \
    "mtddevnum=2\0" \
    "mtddevname=fs\0" \
    "fsfile=root.jffs2-128k\0" \
        "bootfile=u-boot.bin\0"\
    "updatenandfs=tftp 85000000 ${fsfile};nand erase 10C0000 ${filesize};nand write.jffs2 85000000 10c0000 ${filesize}\0" \
        "updatenandboot=tftp 85000000 ${bootfile};nand erase 0 40000;nand write.jffs2 85000000 0 40000\0" \
        "eepromfile=eeprom.bin\0" \
        "updateeprom=tftp 85000000 ${eepromfile};eeprom write 85000000 0 ${filesize}\0" \
        "bootcmd=run boot_flash\0"\
        "partition=nand0,4\0"\
    ""
/*-----------------------------------------------------------------------
 * JFFS2 Filesystem Configuration
 */
#define CONFIG_JFFS2_NAND                       1
#define CONFIG_JFFS2_DEV                        "nand0"
#define CONFIG_CMD_JFFS2
#define CONFIG_CMD_JFFS2_ULOAD
//#define CONFIG_CMD_JFFS2_LS
//#define CONFIG_CMD_JFFS2_FSINFO
#define CONFIG_JFFS2_PART_OFFSET        CFG_ROOTFS_PART_ADDR
// Default using remaining flash space if you ignore 'CONFIG_JFFS_PART_SIZE'
#define CONFIG_JFFS2_PART_SIZE          CFG_ROOTFS_PART_SIZE


/*-----------------------------------------------------------------------
 * Networking Configuration
 */
#define CONFIG_NET_MULTI        1
#define CONFIG_NET_RETRY_COUNT		3
#define CONFIG_COMCERTO_GEMAC   1
#define CONFIG_GPHY_AR8035_DELAY_TUNING 1
// GEMAC mode configured by bootstrap pins or SW
#undef CONFIG_COMCERTO_MII_CFG_BOOTSTRAP
//#define CONFIG_COMCERTO_MII_CFG_BOOTSTRAP
#define GEMAC0_PHY_ADDR         4
#define GEMAC0_CONFIG           CONFIG_COMCERTO_USE_RGMII
#define GEMAC0_MODE             (GEMAC_SW_CONF | GEMAC_SW_FULL_DUPLEX | GEMAC_SW_SPEED_1G)
#define GEMAC0_PHY_FLAGS        (GEMAC_PHY_AUTONEG | GEMAC_GEM_DELAY_DISABLE)
#define GEMAC0_PHYIDX           0
#define GEMAC1_PHY_ADDR         5
#define GEMAC1_CONFIG           CONFIG_COMCERTO_USE_RGMII
#define GEMAC1_MODE             (GEMAC_SW_CONF | GEMAC_SW_FULL_DUPLEX | GEMAC_SW_SPEED_1G)
#define GEMAC1_PHY_FLAGS        (GEMAC_PHY_AUTONEG | GEMAC_GEM_DELAY_DISABLE)
#define GEMAC1_PHYIDX           0

#define CONFIG_MII
#define CONFIG_CMD_MII
#define CONFIG_PHY_GIGE

 /*
  * I2C configuration
  */
#define CONFIG_HARD_I2C
#define CONFIG_SYS_TCLK                CFG_HZ_CLOCK
#define CONFIG_SYS_I2C_SPEED          40000
#define CONFIG_SYS_I2C_SLAVE          0

#define CONFIG_SYS_I2C_EEPROM_ADDR            0x50
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN        2 /* Bytes of address */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS     6 /* max 64 byte */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS 10
#define CONFIG_SYS_EEPROM_PAGE_WRITE_ENABLE


#if 0

/*-----------------------------------------------------------------------
 * CFI FLASH driver setup
 */
//#define CONFIG_SYS_FLASH_CFI		1	/* Flash memory is CFI compliant */
//#define CONFIG_FLASH_CFI_DRIVER         1	/* Use drivers/mtd/cfi_flash.c */
//#define CONFIG_MAX_FLASH_SECT              128     /* max # of sectors on one chip */
#undef CONFIG_FLASH_AM040_DRIVER                           /* disable AM040 flash driver */

//#define CFG_FLASH_AMLV640U_DRIVER     1               /* enable AMLV640U flash driver */
#undef CONFIG_FLASH_AMLV640U_DRIVER                        /* disable AMLV640U flash driver */

#undef CONFIG_FLASH_CFI_DRIVER 
#define CONFIG_SYS_MAX_FLASH_SECT         0x00020000      /* 128 KiB sectors */
#undef CONFIG_FLASH_PROTECTION

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
#define PHYS_FLASH_1                     EXP_CS0_BASEADDR        /* Flash Bank #1 */
#define PHYS_FLASH1_SECT_SIZE           0x00020000      /* 128 KiB sectors */

#define CONFIG_SYS_FLASH_BASE           PHYS_FLASH_1
#define CONFIG_SYS_MAX_FLASH_BANKS      1           /* max number of memory banks */
#define CONFIG_SYS_MONITOR_BASE	        CONFIG_SYS_FLASH_BASE /* Monitor at beginning of flash */
#define CONFIG_SYS_MONITOR_LEN		(1 * PHYS_FLASH1_SECT_SIZE)     /* Reserve 128 KiB for Monitor */
//#define CONFIG_SYS_FLASH_BANKS_LIST	{ CONFIG_SYS_FLASH_BASE, CONFIG_SYS_FLASH_BASE + PHYS_FLASH_SIZE_1 }

//#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE 1	/* Use buffered writes (~10x faster) */


/* timeout values are in ticks */
#define CONFIG_SYS_FLASH_ERASE_TOUT     (2*CONFIG_SYS_HZ)
#define CONFIG_SYS_FLASH_WRITE_TOUT     (2*CONFIG_SYS_HZ) /* Timeout for Flash Write */

#define CONFIG_SYS_JFFS2_MEM_NAND


#endif

/*-----------------------------------------------------------------------
 * Command line configuration.
 */
#define CONFIG_SYS_NO_FLASH
#include <config_cmd_default.h>
//=----------
#define CONFIG_CMD_ENV
#define CONFIG_CMD_MEMORY
#define CONFIG_CMD_MEMTEST
#define CONFIG_CMD_RUN
#define CONFIG_CMD_NET
//#define CONFIG_CMD_JFFS2
//#define CONFIG_CMD_NFS
//----------
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

#endif							/* __CONFIG_H */
