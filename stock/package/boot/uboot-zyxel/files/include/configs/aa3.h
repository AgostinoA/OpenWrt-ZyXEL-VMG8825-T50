/* 
 * Copyright Codito Technologies (www.codito.com) 
 *
 *  include/configs/aa3.h
 *
 *  Copyright (C) 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 * 
 * Authors : Sandeep Patil (sandeep.patil@codito.com)
 * 			 Pradeep Sawlani (pradeep.sawlani@codito.com)
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <config_cmd_default.h>

#undef CONFIG_IDE_PREINIT
#define CONFIG_CMD_IDE
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_ELF
#define CONFIG_CMD_MEMORY
#define CONFIG_CMD_BOOTD
#define CONFIG_CMD_NET
#define CONFIG_NET_MULTI
#define CONFIG_CMD_PING
#define CONFIG_BOOTARGS "abc123"        // sample Linux cmdline 
  
#define CONFIG_SYS_NO_FLASH
#define CONFIG_PCMCIA_SLOT_A
#define CONFIG_DOS_PARTITION
#define CONFIG_SYS_IDE_MAXDEVICE 1
#define CONFIG_SYS_IDE_MAXBUS 1
#define CONFIG_SYS_LONGHELP 1
#define CONFIG_IDE_PREINIT
#define CONFIG_CRC32_VERIFY
#define CONFIG_SHOW_BOOT_PROGRESS


// Timeouts

#define CONFIG_ARP_TIMEOUT 5000000UL


//#define CONFIG_ARC_SYS_CTRL_DEV   You need special XBF's for this.

//#define CONFIG_LCD   Don't want a display by default.
#ifdef CONFIG_LCD
#    define CONFIG_ARC_PGU
#    define CONFIG_SYS_LCD_AND_SERIAL_CONSOLE
#    define CONFIG_SPLASH_SCREEN
#    define CONFIG_PREBOOT \
    	"ide reset;"\
	"setenv splashimage 0x2000000;"\
	"ext2load ide 0:1 $(splashimage) /boot/logo.bmp;"\
	"bmp info $(splashimage);"\
	"cls;"
#endif

/* Disk stuff */
#define CONFIG_SYS_ATA_BASE_ADDR 0xc0fc9000
#define CONFIG_SYS_ATA_REG_OFFSET 0xA0
#define CONFIG_SYS_ATA_DATA_OFFSET 0xA0
#define CONFIG_SYS_ATA_ALT_OFFSET 0xA0
#define CONFIG_SYS_ATA_STRIDE 4
#undef CONFIG_SYS_DIRECT_FLASH_TFTP

#define CONFIG_BOOTDELAY 10
#define CONFIG_BOOTCOMMAND \
    "ide reset;"\
    "setenv filesize 0;"\
    "ext2load ide 0:1 4000000 /boot/boot.params;"\
    "setenv_mem bootparams 4000000 ${filesize};"\
    "ext2load ide 0:1 4000000 /boot/vmlinux;"\
    "bootelf"


#define CONFIG_ARC					1 			/* This is an ARC cpu */
#undef CONFIG_CMD_IMLS
#undef CONFIG_CMD_FLASH


/*
 *  Size of malloc pool
 */
#define CONFIG_SYS_MALLOC_LEN				0x8000 		/* Malloc size = 32k */


/*
 *  Serial configuartion
 */
#define CONFIG_ARC_SERIAL_BAUD		57600		/* Baudrate for serial port */


/*
 *  Physical memory map
 */

/*Donot edit automatically defined by mkconfig */
#define ARC700				1		//	 For arc 700 	
/*#define ARC5			 		1			 For arc 5 automatically defined by mkconfig */

/*This clock speed is for u-boot */
#define CONFIG_ARC_CLK				80000000	/* 70MHz default clock speed */ 				  
#define CONFIG_NR_DRAM_BANKS    	1          		/* We have 1 bank of DRAM */
#define PHYS_SDRAM_1            	0x00000000 		/* SDRAM Bank #1 */

#if defined ARC5
	#define PHYS_SDRAM_1_SIZE	0x200000		/* 2 MB for arc 5 */
	#define UART_BASEADDR 		0x00FC1000		/* UART base address */
	#define VMAC_REG_BASEADDR 	0x00FC2000		/* EMAC base address */
#endif

#if defined ARC700

	#define PHYS_SDRAM_1_SIZE   0x400000 		/* 4 MB for arc 700*/
	#define UART_BASEADDR 		0xC0FC1000
	#define VMAC_REG_BASEADDR 	0xC0FC2000
#endif


/*
 *  Environment variables
 */
#define CONFIG_AUTO_COMPLETE		1					/* Auto complete commands */
#define CONFIG_HOSTNAME  			arc_aa4				
#define CONFIG_ETHADDR          	00:01:02:03:04:80	/* Ethernet address */
#define CONFIG_IPADDR				172.16.18.99		/* Our ip address */
#define CONFIG_SERVERIP				172.16.18.73		/* Tftp server ip address */
#define CONFIG_NETMASK				255.255.0.0

#if defined ARC700
	#define CONFIG_LOADADDR			0x80000000			/* Default load address for net commands */	
#else 
	#define CONFIG_LOADADDR			0x0
#endif

/* Following macros are used for autoboot */
/*#define CONFIG_BOOTDELAY 		5			
#define  CONFIG_BOOTFILE		arclinux 		
#define CONFIG_BOOTCOMMAND		\
	"tftpboot \"arclinux\";"			\
	"go 0x80002000"				*/


/*
 * Miscellaneous configurable options
 */
//#define CONFIG_SYS_LONGHELP
#define CONFIG_SYS_HZ 				CONFIG_ARC_CLK
#define CONFIG_SYS_PROMPT	 		"ArcAngel4 # "
#define CONFIG_SYS_CBSIZE			256 								/* Size of console buffer */
#define CONFIG_SYS_PBSIZE 			(CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)	/* Print Buffer Size */
#define CONFIG_SYS_MAXARGS         16              					/* Max number of command args   */
#define CONFIG_SYS_BARGSIZE        CONFIG_SYS_CBSIZE      					/* Boot Argument Buffer Size    */
#define CONFIG_SYS_LOAD_ADDR		CONFIG_LOADADDR						/* Default load address	for bootm command */ 
#define CONFIG_SYS_BAUDRATE_TABLE 	{ 57600 }
#define CONFIG_SYS_MEMTEST_START   0x200 						/* Exception table starts at 0x0 */ /* memtest works on */
#define CONFIG_SYS_MEMTEST_END     (PHYS_SDRAM_1_SIZE - (350 << 10)/* code + stack area */ - (CONFIG_SYS_MALLOC_LEN << 10)/* malloc area */ )/* size of memory (not accurate)*/   
#if defined ARC5			/* As for now flash works only with ARC5 */	
	#define CONFIG_SYS_DIRECT_FLASH_TFTP	1			/* Directly TFTP writes to flash memory */			
#endif


/*
 *  Flash options
 */
/*#define CONFIG_SYS_UBOOT_ON_FLASH 		0			 If flash memory is present and uboot is on the flash then flash = 1 automatically defined by mkconfig*/
#define CONFIG_SYS_MAX_FLASH_BANKS     	1     			/* Max number of memory banks */
#define CONFIG_SYS_MAX_FLASH_SECT      	256  	 		/* Max number of sectors on one chip */
#define CONFIG_SYS_FLASH_BASE			0x800000  		    /* Flash base address */ 

#define CONFIG_ENV_SIZE            	1024
#define CONFIG_SYS_ENV_SIZE            	1024
#define CONFIG_ENV_IS_NOWHERE    1
#define CONFIG_SYS_ENV_ADDR			(CONFIG_SYS_FLASH_BASE + 0x40000) /* 256k i.e first sector occupied by u-boot second sector contains environment*/	

/* 
 * Kernel Parameters 
 */

#define CONFIG_SYS_ENV_IS_NOWHERE
#define CONFIG_SYS_KERN_PARM           0 		/* 		O - disable kernel parameters
												1 - enable kernel parameters 
										 */  

#if CONFIG_SYS_KERN_PARM


#if defined ARC700  				/* Only ARC700 kernel accepts parameters from u-boot*/

#define CONFIG_CLK_SPEED_TAG         CONFIG_ARC_CLK    /* clock speed */

#define CONFIG_SETUP_MEMORY_TAGS     1                 /* configuring bank */
#ifdef CONFIG_SETUP_MEMORY_TAGS  						/* Memory size  */
#define CONFIG_MEMORY_SIZE  0x400000
#endif /* CONFIG_SETUP_MEMORY_TAGS */

#if 0
# define CONFIG_CACHE_TAG         1
#ifdef CONFIG_CACHE_TAG
	#define CONFIG_ICACHE        1
	#define CONFIG_DCACHE        1
#endif /* CONFIG_CACHE_TAG */
#endif

# define CONFIG_SERIAL_TAG 1
#ifdef CONFIG_SERIAL_TAG
	#define CONFIG_UART0_BAUDRATE  CONFIG_ARC_SERIAL_BAUD
#endif /* CONFIG_SERIAL_TAG */

# define CONFIG_VMAC_TAG 1
#ifdef CONFIG_VMAC_TAG
	#define CONFIG_VMAC_ADDR   "00:01:02:03:04:26"
#endif /* CONFIG_VMAC_TAG */
#endif /* ARC700*/
#endif /* CONFIG_SYS_KERN_PARM */

/* Reduce the MTU size to 1460 because in vlan mode, the packets will be
 * 1518 bytes which exceed the EMAC's capability and these packets will
 * be discard silently.
 */
#define CONFIG_TFTP_BLOCKSIZE	1460

#endif /* __CONFIG_H */



