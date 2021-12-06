/************************************************************************
 *
 *	Copyright (C) 2010 Trendchip Technologies, Corp.
 *	All Rights Reserved.
 *
 * Trendchip Confidential; Need to Know only.
 * Protected as an unpublished work.
 *
 * The computer program listings, specifications and documentation
 * herein are the property of Trendchip Technologies, Co. and shall
 * not be reproduced, copied, disclosed, or used in whole or in part
 * for any reason without the prior express written permission of
 * Trendchip Technologeis, Co.
 *
 *************************************************************************/
#ifndef TC_PARTITION_H
#define TC_PARTITION_H
 #ifdef TCSUPPORT_MTD_ENCHANCEMENT
/*
note:		
	1.the read base address of reserve area need to compute by (flash total size -flash erase size * reverse block num) 
		-the base addrass can be obtained by mtd ioctl
		-for example :flash total size is 32 m,flash erase size is 64k,reverse block num is 1,so the read base address of 
		reserve area is 0x3fff0000
	2.reverse block num is according to compile option TCSUPPORT_RESERVEAREA_BLOCK
	TCSUPPORT_RESERVEAREA_BLOCK==1 --------reverse block num is 1
	TCSUPPORT_RESERVEAREA_BLOCK==2 --------reverse block num is 2
	TCSUPPORT_RESERVEAREA_BLOCK==3 --------reverse block num is 3
	TCSUPPORT_RESERVEAREA_BLOCK==4 --------reverse block num is 4
	3.if you modify the size or offset of the certain sector or you add a new sector,you must modify the reserve area table in order to let
	other people be clear.
*/

//********************************
//	operation of  reserve area 	       //
//********************************
#if defined(TCSUPPORT_CPU_EN7512) || defined(TCSUPPORT_CPU_EN7521)
#ifndef __KERNEL__
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <mtd/mtd-user.h>
#endif
#endif


#define TC_FLASH_READ_CMD		"/userfs/bin/mtd readflash %s %lu %lu %s"
#define TC_FLASH_WRITE_CMD	"/userfs/bin/mtd writeflash %s %lu %lu %s"

#define TC_FLASH_ERASE_SECTOR_CMD "/userfs/bin/mtd erasesector %lu %s"

#define RESERVEAREA_NAME "reservearea"

#ifdef TCSUPPORT_MT7570
#if defined (TCSUPPORT_WLAN_MT7615_11N) || defined (TCSUPPORT_DUAL_WLAN_MT7615E) || defined (TCSUPPORT_WLAN_MT7615D)
#if (TCSUPPORT_RESERVEAREA_BLOCK==6)
#ifdef TCSUPPORT_NAND_BMT
#define BOB_RA_OFFSET_OLD_MODE  656896
#else 
#define BOB_RA_OFFSET_OLD_MODE  329216
#endif
#endif 
#else 
#if (TCSUPPORT_RESERVEAREA_BLOCK==4)
#define BOB_RA_OFFSET_OLD_MODE 198144
#else
#define BOB_RA_OFFSET_OLD_MODE  1536
#endif
#endif
#endif

#if defined(TCSUPPORT_CPU_EN7512) || defined(TCSUPPORT_CPU_EN7521)
#ifndef __KERNEL__
static inline int mtd_reservearea_open(const char *mtd, int flags)
{
	FILE *fp = NULL;
	char dev[128];
	int i;

	if ((fp = fopen("/proc/mtd", "r"))) {
		while (fgets(dev, sizeof(dev), fp)) {
			if (sscanf(dev, "mtd%d:", &i) && strstr(dev, mtd)) {
				snprintf(dev, sizeof(dev), "/dev/mtd%d", i);
				fclose(fp);
				return open(dev, flags);
			}
		}
		fclose(fp);
	}

	return -1;
}
#endif

/* the original NAND_FLASH_BLOCK_SIZE is 0x20000 */
#define ORIGINAL_NAND_FLASH_BLOCK_SIZE (0x20000)
static inline unsigned int runtime_flash_block_size(void)
{
#ifndef __KERNEL__
	int fd, ret;
	mtd_info_t mtd_info;
	

	fd = mtd_reservearea_open(RESERVEAREA_NAME, O_RDONLY);
	if(fd < 0) {
		fprintf(stderr, "Couldn't open mtd:%s!\n", RESERVEAREA_NAME);
		return ORIGINAL_NAND_FLASH_BLOCK_SIZE;
	}

	ret = ioctl(fd, MEMGETINFO, &mtd_info);
	close(fd);
	
	if(ret == 0) {
		return mtd_info.erasesize;
	} else {
		fprintf(stderr, "Couldn't ioctl to %s!\n", RESERVEAREA_NAME);
		return ORIGINAL_NAND_FLASH_BLOCK_SIZE;
	}
#else /* __KERNEL__ */
	return ORIGINAL_NAND_FLASH_BLOCK_SIZE;
#endif /* __KERNEL__ */
}
#define NAND_FLASH_BLOCK_SIZE runtime_flash_block_size()  //this define can be changed baccording to type of nandflash (0x10000/0x20000/0x40000)
#else /* defined(TCSUPPORT_CPU_EN7512) || defined(TCSUPPORT_CPU_EN7521) */
#define NAND_FLASH_BLOCK_SIZE (0x20000)  //this define can be changed baccording to type of nandflash (0x10000/0x20000/0x40000)
#endif /* defined(TCSUPPORT_CPU_EN7512) || defined(TCSUPPORT_CPU_EN7521) */

#if !defined(TCSUPPORT_CT) 
//********************************
//	sectors define of reserve area 	//
//********************************
#ifdef TCSUPPORT_NAND_BMT
#define RESERVEAREA_ERASE_SIZE NAND_FLASH_BLOCK_SIZE //this define should be changed baccording to  flash erase size  
#else
#define RESERVEAREA_ERASE_SIZE 0x10000 //this define should be changed baccording to  flash erase size
#endif
#define RESERVEAREA_BLOCK_BASE 0

//#if defined( TCSUPPORT_RESERVEAREA_1_BLOCK)

//#elif defined( TCSUPPORT_RESERVEAREA_2_BLOCK)

//#elif defined( TCSUPPORT_RESERVEAREA_3_BLOCK)

#if (TCSUPPORT_RESERVEAREA_BLOCK==1)
/*
---------------------------------------------------------------------------------
@reserve area table@
|sector		name				cover area				note		
|0			eeprom				0x00000~0x003ff			1k(reserve 1k,no use 256 bytes)
|1			cwmppara			0x00400~0x00600			512 Bytes
|2			not use now			0x00601~0x00fff			(4k-1k-512 Bytes)
|3			mrd					0x01000~0x01fff			4k
|4			rom-t				0x02000~0x0ffff			56k
------------------------------------------------------------------------------------
*/
#define RESERVEAREA_TOTAL_SIZE RESERVEAREA_ERASE_SIZE*1

/*eeprom*/
#define EEPROM_RA_SIZE 0x400
#define EEPROM_RA_OFFSET RESERVEAREA_BLOCK_BASE 

/*device information*/
#ifdef TCSUPPORT_PRODUCTIONLINE
#define PROLINE_CWMPPARA_RA_SIZE 0x200
#define PROLINE_CWMPPARA_RA_OFFSET (EEPROM_RA_OFFSET+EEPROM_RA_SIZE)
#else
#define PROLINE_CWMPPARA_RA_SIZE 0x0
#define PROLINE_CWMPPARA_RA_OFFSET (EEPROM_RA_OFFSET+EEPROM_RA_SIZE)
#endif

#ifdef TCSUPPORT_MT7570
#define BOB_RA_SIZE 0xa0
#define BOB_RA_OFFSET (PROLINE_CWMPPARA_RA_OFFSET + 0x200)
#endif

#define MRD_RA_SIZE 0x1000
#define MRD_RA_OFFSET (EEPROM_RA_OFFSET + 0x1000) 

#define ROM_T_RA_SIZE 0xe000
#define ROM_T_RA_OFFSET (MRD_RA_OFFSET+MRD_RA_SIZE)

#elif (TCSUPPORT_RESERVEAREA_BLOCK==2)
/*
---------------------------------------------------------------------------------
@reserve area table@
|sector		name				cover area				note
|0			backupromfile 		0~0xffff					64k
|1			syslog				0x10000~0x10000			
|2			eeprom				0x10000~0x103ff			1k(reserve 1k,no use 256 bytes)
|3			cwmppara			0x00400~0x00600			512 Bytes
|4			not use now			0x00601~0x00fff			(4k-1k-512 Bytes)
|5			mrd				0x01000~0x01fff			4k
|6			rom-t				0x02000~0x0ffff			56k
------------------------------------------------------------------------------------
*/
#define RESERVEAREA_TOTAL_SIZE RESERVEAREA_ERASE_SIZE*2
/*backupromfile*/
#define BACKUPROMFILE_RA_SIZE 0x10000
#define BACKUPROMFILE_RA_OFFSET RESERVEAREA_BLOCK_BASE
/*defaultromfile*/
//#define DEFAULTROMFILE_RA_SIZE 0x0
//#define DEFAULTROMFILE_RA_OFFSET (BACKUPROMFILE_RA_OFFSET+BACKUPROMFILE_RA_SIZE)
/*syslog*/
#define SYSLOG_RA_SIZE 0x0
//#define SYSLOG_RA_OFFSET (DEFAULTROMFILE_RA_OFFSET+DEFAULTROMFILE_RA_SIZE)
#define SYSLOG_RA_OFFSET (BACKUPROMFILE_RA_OFFSET+BACKUPROMFILE_RA_SIZE)
/*eeprom*/
#define EEPROM_RA_SIZE 0x400
#define EEPROM_RA_OFFSET (SYSLOG_RA_OFFSET+SYSLOG_RA_SIZE)

/*device information*/
#ifdef TCSUPPORT_PRODUCTIONLINE
#define PROLINE_CWMPPARA_RA_SIZE 0x200
#define PROLINE_CWMPPARA_RA_OFFSET (EEPROM_RA_OFFSET+EEPROM_RA_SIZE)
#else
#define PROLINE_CWMPPARA_RA_SIZE 0x0
#define PROLINE_CWMPPARA_RA_OFFSET (EEPROM_RA_OFFSET+EEPROM_RA_SIZE)
#endif

#ifdef TCSUPPORT_MT7570
#define BOB_RA_SIZE 0xa0
#define BOB_RA_OFFSET (PROLINE_CWMPPARA_RA_OFFSET + 0x200)
#endif

#define MRD_RA_SIZE 0x1000
#define MRD_RA_OFFSET (EEPROM_RA_OFFSET + 0x1000)

#define ROM_T_RA_SIZE 0xe000
#define ROM_T_RA_OFFSET (MRD_RA_OFFSET+MRD_RA_SIZE)

#elif (TCSUPPORT_RESERVEAREA_BLOCK==3)
/*
---------------------------------------------------------------------------------
@reserve area table@
|sector		name				cover area				note
|0			backupromfile 		0~0xffff					64k
|1			defaultromfile		0x10000~0x1ffff			64k
|2			eeprom			0x20000~0x203ff			1k(reserve 1k,no use 256 bytes)
|3			cwmppara			0x00400~0x00600			384 Bytes
|4			not use now			0x00601~0x00fff			(4k-1k-512 Bytes)
|5			mrd					0x01000~0x01fff			4k
|6			rom-t				0x02000~0x0ffff			56k
------------------------------------------------------------------------------------
*/
#define RESERVEAREA_TOTAL_SIZE RESERVEAREA_ERASE_SIZE*3
/*backupromfile*/
#define BACKUPROMFILE_RA_SIZE 0x10000
#define BACKUPROMFILE_RA_OFFSET RESERVEAREA_BLOCK_BASE
/*defaultromfile*/
#define DEFAULTROMFILE_RA_SIZE 0x10000
#define DEFAULTROMFILE_RA_OFFSET (BACKUPROMFILE_RA_OFFSET+BACKUPROMFILE_RA_SIZE)
/*eeprom*/
#define EEPROM_RA_SIZE 0x400
#define EEPROM_RA_OFFSET (DEFAULTROMFILE_RA_SIZE+DEFAULTROMFILE_RA_OFFSET)

/*device information*/
#ifdef TCSUPPORT_PRODUCTIONLINE
#define PROLINE_CWMPPARA_RA_SIZE 0x200
#define PROLINE_CWMPPARA_RA_OFFSET (EEPROM_RA_OFFSET+EEPROM_RA_SIZE)
#else
#define PROLINE_CWMPPARA_RA_SIZE 0x0
#define PROLINE_CWMPPARA_RA_OFFSET (EEPROM_RA_OFFSET+EEPROM_RA_SIZE)
#endif

#ifdef TCSUPPORT_MT7570
#define BOB_RA_SIZE 0xa0
#define BOB_RA_OFFSET (PROLINE_CWMPPARA_RA_OFFSET + 0x200)
#endif

#define MRD_RA_SIZE 0x1000
#define MRD_RA_OFFSET (EEPROM_RA_OFFSET + 0x1000)

#define ROM_T_RA_SIZE 0xe000
#define ROM_T_RA_OFFSET (MRD_RA_OFFSET+MRD_RA_SIZE)

//#else
#elif (TCSUPPORT_RESERVEAREA_BLOCK==4)
//defined( TCSUPPORT_RESERVEAREA_BLOCK == 4)
#ifdef TCSUPPORT_NAND_BMT

/*
---------------------------------------------------------------------------------
@reserve area table@
|sector		name				cover area				note
|0			backupromfile 		0~0x1ffff					128k
|1			defaultromfile			0x20000~0x3ffff			128k
|2			syslog				0x40000~0x5ffff			128k
|3			eeprom				0x60000~0x603ff			1k(reserve 1k,no use 256 bytes)
|4			cwmppara			0x60400~0x60600			512 Bytes
|5			not use now			0x60601~0x60fff			(4k-1k-512 Bytes)
|6			mrd					0x61000~0x61fff			4k
|7			rom-t				0x62000~0x6ffff			56k
------------------------------------------------------------------------------------
*/
#define RESERVEAREA_TOTAL_SIZE RESERVEAREA_ERASE_SIZE*4
#ifdef TCSUPPORT_WLAN_AC
#define MAX_EEPROM_BIN_FILE_SIZE	512
#endif
/*backupromfile*/
#define BACKUPROMFILE_RA_SIZE RESERVEAREA_ERASE_SIZE
#define BACKUPROMFILE_RA_OFFSET RESERVEAREA_BLOCK_BASE
/*defaultromfile*/
#define DEFAULTROMFILE_RA_SIZE RESERVEAREA_ERASE_SIZE
#define DEFAULTROMFILE_RA_OFFSET (BACKUPROMFILE_RA_OFFSET+BACKUPROMFILE_RA_SIZE)
/*syslog*/
#define SYSLOG_RA_SIZE RESERVEAREA_ERASE_SIZE
#define SYSLOG_RA_OFFSET (DEFAULTROMFILE_RA_OFFSET+DEFAULTROMFILE_RA_SIZE)
/*eeprom*/
#define EEPROM_RA_SIZE 0x400
#define EEPROM_RA_OFFSET (SYSLOG_RA_OFFSET+SYSLOG_RA_SIZE)
#ifdef TCSUPPORT_WLAN_AC
#ifndef TCSUPPORT_EEPROM_ACEXT
#define EEPROM_RA_AC_OFFSET (EEPROM_RA_OFFSET+MAX_EEPROM_BIN_FILE_SIZE)
#endif
#endif

/*device information*/
#ifdef TCSUPPORT_PRODUCTIONLINE
#define PROLINE_CWMPPARA_RA_SIZE 0x200
#define PROLINE_CWMPPARA_RA_OFFSET (EEPROM_RA_OFFSET+EEPROM_RA_SIZE)
#else
#define PROLINE_CWMPPARA_RA_SIZE 0x0
#define PROLINE_CWMPPARA_RA_OFFSET (EEPROM_RA_OFFSET+EEPROM_RA_SIZE)
#endif

#ifdef TCSUPPORT_MT7570
#define BOB_RA_SIZE 0xa0
#define BOB_RA_OFFSET (PROLINE_CWMPPARA_RA_OFFSET + 0x200)
#endif

/*for MT7615 use cause the size of MT7615 EEPROM is 1k*/
#ifdef TCSUPPORT_WLAN_AC
#ifdef TCSUPPORT_EEPROM_ACEXT   
#define EEPROM_RA_AC_OFFSET (PROLINE_CWMPPARA_RA_OFFSET+PROLINE_CWMPPARA_RA_SIZE)
#endif
#endif

#define MRD_RA_SIZE 0x1000
#define MRD_RA_OFFSET (EEPROM_RA_OFFSET + 0x1000)

#define ROM_T_RA_SIZE 0xe000
#define ROM_T_RA_OFFSET (MRD_RA_OFFSET+MRD_RA_SIZE)


#else

/*
---------------------------------------------------------------------------------
@reserve area table@
|sector		name				cover area				note
|0			backupromfile 		0~0xffff					64k
|1			defaultromfile			0x10000~0x1ffff			64k
|2			syslog				0x20000~0x2ffff			64k
|3			eeprom				0x30000~0x303ff			1k(reserve 1k,no use 256 bytes)
|4			cwmppara			0x00400~0x00600			512 Bytes
|5			not use now			0x00601~0x00fff			(4k-1k-512 Bytes)
|6			mrd					0x01000~0x01fff			4k
|7			rom-t				0x02000~0x0ffff			56k
------------------------------------------------------------------------------------
*/
#define RESERVEAREA_TOTAL_SIZE RESERVEAREA_ERASE_SIZE*4
#ifdef TCSUPPORT_WLAN_AC
#define MAX_EEPROM_BIN_FILE_SIZE	512
#endif
/*backupromfile*/
#define BACKUPROMFILE_RA_SIZE 0x10000
#define BACKUPROMFILE_RA_OFFSET RESERVEAREA_BLOCK_BASE
/*defaultromfile*/
#define DEFAULTROMFILE_RA_SIZE 0x10000
#define DEFAULTROMFILE_RA_OFFSET (BACKUPROMFILE_RA_OFFSET+BACKUPROMFILE_RA_SIZE)
/*syslog*/
#define SYSLOG_RA_SIZE 0x10000
#define SYSLOG_RA_OFFSET (DEFAULTROMFILE_RA_OFFSET+DEFAULTROMFILE_RA_SIZE)
/*eeprom*/
#define EEPROM_RA_SIZE 0x400
#define EEPROM_RA_OFFSET (SYSLOG_RA_OFFSET+SYSLOG_RA_SIZE)
#ifdef TCSUPPORT_WLAN_AC
#ifndef TCSUPPORT_EEPROM_ACEXT
#define EEPROM_RA_AC_OFFSET (EEPROM_RA_OFFSET+MAX_EEPROM_BIN_FILE_SIZE)
#endif
#endif

/*device information*/
#ifdef TCSUPPORT_PRODUCTIONLINE
#define PROLINE_CWMPPARA_RA_SIZE 0x200
#define PROLINE_CWMPPARA_RA_OFFSET (EEPROM_RA_OFFSET+EEPROM_RA_SIZE)
#else
#define PROLINE_CWMPPARA_RA_SIZE 0x0
#define PROLINE_CWMPPARA_RA_OFFSET (EEPROM_RA_OFFSET+EEPROM_RA_SIZE)
#endif

#ifdef TCSUPPORT_MT7570
#define BOB_RA_SIZE 0xa0
#define BOB_RA_OFFSET (PROLINE_CWMPPARA_RA_OFFSET + 0x200)
#endif

/*for MT7615 use cause the size of MT7615 EEPROM is 1k*/
#ifdef TCSUPPORT_WLAN_AC
#ifdef TCSUPPORT_EEPROM_ACEXT   
#define EEPROM_RA_AC_OFFSET (PROLINE_CWMPPARA_RA_OFFSET+PROLINE_CWMPPARA_RA_SIZE)
#endif
#endif

#define MRD_RA_SIZE 0x1000
#define MRD_RA_OFFSET (EEPROM_RA_OFFSET + 0x1000)

#define ROM_T_RA_SIZE 0xe000
#define ROM_T_RA_OFFSET (MRD_RA_OFFSET+MRD_RA_SIZE)
#endif

#elif (TCSUPPORT_RESERVEAREA_BLOCK==6)
//defined( TCSUPPORT_RESERVEAREA_BLOCK == 6)
#if defined(MT7615E)|| defined(MT7615_11N)
#ifdef TCSUPPORT_NAND_BMT
/*
---------------------------------------------------------------------------------
@reserve area table@
|sector		name							cover area				note
|0			eeprom(11n part)					0~0x0fff					4k
|1			TRX_SET1_SET2(11n part)			0x1000~0x9fff			36k
|2			Reserved 						0xa000~0x1ffff			88k
																			//0~2 for 11n
|3			eeprom(11ac part)					0x20000~0x20fff			4k
|4			TRX_SET1_SET2(11ac part)			0x21000~0x29fff			36k
|5			Reserved 						0x2a000~0x3ffff			88k
																			//3~5 for 11ac
|6			backupromfile 					0x40000~0x5ffff			128k
|7			defaultromfile						0x60000~0x7ffff			128k
|8			syslog							0x80000~0x9ffff			128k
|9			eeprom							0xa0000~0xa03ff			1k(reserve 1k,no use 256 bytes)
|10			cwmppara						0xa0400~0xa05ff			512 Bytes
|11			not use now						0xa0600~0xa0fff			(4k-1k-512 Bytes)
|12			mrd								0xa1000~0xa1fff			4k
|13			rom-t							0xa2000~0xaffff			56k
------------------------------------------------------------------------------------
*/
#define RESERVEAREA_TOTAL_SIZE RESERVEAREA_ERASE_SIZE*6
#ifdef TCSUPPORT_WLAN_AC
#define MAX_EEPROM_BIN_FILE_SIZE	512
#endif
/*11n part*/
#define EEPROM_761511N_RA_SIZE 0x1000
#define EEPROM_761511N_RA_OFFSET RESERVEAREA_BLOCK_BASE
#define TRX_SET1_SET2_11N_RA_SIZE 0x9000
#define TRX_SET1_SET2_11N_RA_OFFSET (EEPROM_761511N_RA_OFFSET+EEPROM_761511N_RA_SIZE)

/*11ac part*/
#define EEPROM_761511AC_RA_SIZE 0x1000
#define EEPROM_RA_761511AC_OFFSET (EEPROM_761511N_RA_OFFSET+RESERVEAREA_ERASE_SIZE)
#define TRX_SET1_SET2_11AC_RA_SIZE 0x9000
#define TRX_SET1_SET2_11AC_RA_OFFSET (EEPROM_RA_761511AC_OFFSET+EEPROM_761511AC_RA_SIZE)

/*backupromfile*/
#define BACKUPROMFILE_RA_SIZE RESERVEAREA_ERASE_SIZE
#define BACKUPROMFILE_RA_OFFSET (EEPROM_RA_761511AC_OFFSET+RESERVEAREA_ERASE_SIZE)
/*defaultromfile*/
#define DEFAULTROMFILE_RA_SIZE RESERVEAREA_ERASE_SIZE
#define DEFAULTROMFILE_RA_OFFSET (BACKUPROMFILE_RA_OFFSET+BACKUPROMFILE_RA_SIZE)
/*syslog*/
#define SYSLOG_RA_SIZE RESERVEAREA_ERASE_SIZE
#define SYSLOG_RA_OFFSET (DEFAULTROMFILE_RA_OFFSET+DEFAULTROMFILE_RA_SIZE)
/*eeprom*/
#define EEPROM_RA_SIZE 0x400
#define EEPROM_RA_OFFSET (SYSLOG_RA_OFFSET+SYSLOG_RA_SIZE)
#ifdef TCSUPPORT_WLAN_AC
#define EEPROM_RA_AC_OFFSET (EEPROM_RA_OFFSET+MAX_EEPROM_BIN_FILE_SIZE)
#endif

/*device information*/
#ifdef TCSUPPORT_PRODUCTIONLINE
#define PROLINE_CWMPPARA_RA_SIZE 0x200
#define PROLINE_CWMPPARA_RA_OFFSET (EEPROM_RA_OFFSET+EEPROM_RA_SIZE)
#else
#define PROLINE_CWMPPARA_RA_SIZE 0x0
#define PROLINE_CWMPPARA_RA_OFFSET (EEPROM_RA_OFFSET+EEPROM_RA_SIZE)
#endif

#ifdef TCSUPPORT_MT7570
#define BOB_RA_SIZE 0xa0
#define BOB_RA_OFFSET (PROLINE_CWMPPARA_RA_OFFSET + 0x200)
#endif

#define MRD_RA_SIZE 0x1000
#define MRD_RA_OFFSET (EEPROM_RA_OFFSET + 0x1000)

#define ROM_T_RA_SIZE 0xe000
#define ROM_T_RA_OFFSET (MRD_RA_OFFSET+MRD_RA_SIZE)
#else

/*
---------------------------------------------------------------------------------
@reserve area table@
|sector		name							cover area				note
|0			eeprom(11n part)					0~0x0fff					4k
|1			TRX_SET1_SET2(11n part)			0x1000~0x9fff			36k
|2			Reserved 						0xa000~0xffff				24k
																			//0~2 for 11n
|3			eeprom(11ac part)					0x10000~0x10fff			4k
|4			TRX_SET1_SET2(11ac part)			0x11000~0x19fff			36k
|5			Reserved							0x1a000~0x1ffff			24k
																			//3~5 for 11ac
|6			backupromfile 					0x20000~0x2ffff			64k
|7			defaultromfile						0x30000~0x3ffff			64k
|8			syslog							0x40000~0x5ffff			64k
|9			eeprom							0x60000~0x603ff			1k(reserve 1k,no use 256 bytes)
|10			cwmppara						0x60400~0x605ff			512 Bytes
|11			not use now						0x60600~0x60fff			(4k-1k-512 Bytes)
|12			mrd								0x61000~0x61fff			4k
|13			rom-t							0x62000~0x6ffff			56k
------------------------------------------------------------------------------------
*/
#define RESERVEAREA_TOTAL_SIZE RESERVEAREA_ERASE_SIZE*6
#ifdef TCSUPPORT_WLAN_AC
#define MAX_EEPROM_BIN_FILE_SIZE	512
#endif

/*11n part*/
#define EEPROM_761511N_RA_SIZE 0x1000
#define EEPROM_761511N_RA_OFFSET RESERVEAREA_BLOCK_BASE
#define TRX_SET1_SET2_11N_RA_SIZE 0x9000
#define TRX_SET1_SET2_11N_RA_OFFSET (EEPROM_761511N_RA_OFFSET+EEPROM_761511N_RA_SIZE)
	
/*11ac part*/
#define EEPROM_761511AC_RA_SIZE 0x1000
#define EEPROM_RA_761511AC_OFFSET (EEPROM_761511N_RA_OFFSET+0x10000)
#define TRX_SET1_SET2_11AC_RA_SIZE 0x9000
#define TRX_SET1_SET2_11AC_RA_OFFSET (EEPROM_RA_761511AC_OFFSET+EEPROM_761511AC_RA_SIZE)

	
/*backupromfile*/
#define BACKUPROMFILE_RA_SIZE 0x10000
#define BACKUPROMFILE_RA_OFFSET (EEPROM_RA_761511AC_OFFSET+0x10000)
/*defaultromfile*/
#define DEFAULTROMFILE_RA_SIZE 0x10000
#define DEFAULTROMFILE_RA_OFFSET (BACKUPROMFILE_RA_OFFSET+BACKUPROMFILE_RA_SIZE)
/*syslog*/
#define SYSLOG_RA_SIZE 0x10000
#define SYSLOG_RA_OFFSET (DEFAULTROMFILE_RA_OFFSET+DEFAULTROMFILE_RA_SIZE)
/*eeprom*/
#define EEPROM_RA_SIZE 0x400
#define EEPROM_RA_OFFSET (SYSLOG_RA_OFFSET+SYSLOG_RA_SIZE)
#ifdef TCSUPPORT_WLAN_AC
#define EEPROM_RA_AC_OFFSET (EEPROM_RA_OFFSET+MAX_EEPROM_BIN_FILE_SIZE)
#endif
	
/*device information*/
#ifdef TCSUPPORT_PRODUCTIONLINE
#define PROLINE_CWMPPARA_RA_SIZE 0x200
#define PROLINE_CWMPPARA_RA_OFFSET (EEPROM_RA_OFFSET+EEPROM_RA_SIZE)
#else
#define PROLINE_CWMPPARA_RA_SIZE 0x0
#define PROLINE_CWMPPARA_RA_OFFSET (EEPROM_RA_OFFSET+EEPROM_RA_SIZE)
#endif

#ifdef TCSUPPORT_MT7570
#define BOB_RA_SIZE 0xa0
#define BOB_RA_OFFSET (PROLINE_CWMPPARA_RA_OFFSET + 0x200)
#endif
	
#define MRD_RA_SIZE 0x1000
#define MRD_RA_OFFSET (EEPROM_RA_OFFSET + 0x1000)
	
#define ROM_T_RA_SIZE 0xe000
#define ROM_T_RA_OFFSET (MRD_RA_OFFSET+MRD_RA_SIZE)
#endif
#endif
#elif (TCSUPPORT_RESERVEAREA_BLOCK==7)
//defined( TCSUPPORT_RESERVEAREA_BLOCK == 7)
#if defined(MT7615E)|| defined(MT7615_11N)
#ifdef TCSUPPORT_NAND_BMT
/*
---------------------------------------------------------------------------------
@reserve area table@
|sector		name				cover area				note
|0			eeprom(11n part)					0~0x0fff					4k
|1			TRX_SET1_SET2(11n part)			0x1000~0x9fff			36k
|2			Reserved 						0xa000~0x1ffff			88k
																			//0~2 for 11n
|3			eeprom(11ac part)					0x20000~0x20fff			4k
|4			TRX_SET1_SET2(11ac part)			0x21000~0x29fff			36k
|5			Reserved for WiFi					0x2a000~0x3ffff			88k
																			//3~5 for 11ac
|6			backupromfile						0x40000~0x7ffff			256k
|7			gpon_bob						0x80000~0x9ffff			128k
|8			syslog							0xa0000~0xbffff			128k
|9			eeprom							0xc0000~0xc03ff			1k(reserve 1k,no use 256 bytes)
|10			cerm1							0xc0400~0xc13ff			4k
|11			cerm2							0xc1400~0xc823ff			4k
|12			cerm3							0xc2400~0xc33ff			4k
|13			cerm4							0xc3400~0xc43ff			4k
|14			username/passwd					0xc4400~0xc47ff			1K
|15			mrd								0xc0000~0xc0fff			4k
|16			imgbootflag						0xc5800~0xc5801			

------------------------------------------------------------------------------------
*/

#define RESERVEAREA_TOTAL_SIZE RESERVEAREA_ERASE_SIZE*7

#ifdef TCSUPPORT_WLAN_AC
#define MAX_EEPROM_BIN_FILE_SIZE	512
#endif
/*11n part*/
#define EEPROM_761511N_RA_SIZE 0x1000
#define EEPROM_761511N_RA_OFFSET RESERVEAREA_BLOCK_BASE
#define TRX_SET1_SET2_11N_RA_SIZE 0x9000
#define TRX_SET1_SET2_11N_RA_OFFSET (EEPROM_761511N_RA_OFFSET+EEPROM_761511N_RA_SIZE)

/*11ac part*/
#define EEPROM_761511AC_RA_SIZE 0x1000
#define EEPROM_RA_761511AC_OFFSET (EEPROM_761511N_RA_OFFSET+NAND_FLASH_BLOCK_SIZE)
#define TRX_SET1_SET2_11AC_RA_SIZE 0x9000
#define TRX_SET1_SET2_11AC_RA_OFFSET (EEPROM_RA_761511AC_OFFSET+EEPROM_761511AC_RA_SIZE)

/*backupromfile*/
#define BACKUPROMFILE_RA_SIZE NAND_FLASH_BLOCK_SIZE*2
#define BACKUPROMFILE_RA_OFFSET (EEPROM_RA_761511AC_OFFSET+NAND_FLASH_BLOCK_SIZE)

/*defaultromfile*/
#define BOB_RA_SIZE NAND_FLASH_BLOCK_SIZE
#define BOB_RA_OFFSET (BACKUPROMFILE_RA_OFFSET+BACKUPROMFILE_RA_SIZE)
/*syslog*/
#define SYSLOG_RA_SIZE NAND_FLASH_BLOCK_SIZE
#define SYSLOG_RA_OFFSET (GPON_BOB_OFFSET+BOB_RA_SIZE)
/*eeprom*/
#define EEPROM_RA_SIZE 0x400
#define EEPROM_RA_OFFSET (SYSLOG_RA_OFFSET+SYSLOG_RA_SIZE)
/*cerm1*/
#define CERM1_RA_SIZE 0x1000
#define CERM1_RA_OFFSET (EEPROM_RA_SIZE+EEPROM_RA_OFFSET)
/*cerm2*/
#define CERM2_RA_SIZE 0x1000
#define CERM2_RA_OFFSET (CERM1_RA_SIZE+CERM1_RA_OFFSET)
/*cerm3*/
#define CERM3_RA_SIZE 0x1000
#define CERM3_RA_OFFSET (CERM2_RA_SIZE+CERM2_RA_OFFSET)
/*cerm4*/
#define CERM4_RA_SIZE 0x1000
#define CERM4_RA_OFFSET (CERM3_RA_SIZE+CERM3_RA_OFFSET)
#if !defined(TCSUPPORT_CT_BOOTLOADER_UPGRADE) 
#define USERNAMEPASSWD_RA_SIZE 0x0
#define USERNAMEPASSWD_RA_OFFSET (CERM4_RA_SIZE+CERM4_RA_OFFSET)
#endif
#ifdef TCSUPPORT_PRODUCTIONLINE
#define PROLINE_CWMPPARA_RA_SIZE 0x180
#define PROLINE_CWMPPARA_RA_OFFSET (USERNAMEPASSWD_RA_SIZE+USERNAMEPASSWD_RA_OFFSET)
#else
#define PROLINE_CWMPPARA_RA_SIZE 0x0
#define PROLINE_CWMPPARA_RA_OFFSET (USERNAMEPASSWD_RA_SIZE+USERNAMEPASSWD_RA_OFFSET)
#endif

#ifdef TCSUPPORT_MT7570
#define BOB_RA_SIZE 0xa0
#define BOB_RA_OFFSET (PROLINE_CWMPPARA_RA_OFFSET + 0x200)
#endif

#define MRD_RA_SIZE 0x1000
#define MRD_RA_OFFSET (EEPROM_RA_OFFSET + 0x1000)

/*image boot flag*/
#define IMG_BOOT_FLAG_SIZE 	1
#define IMG_BOOT_FLAG_OFFSET  	(PROLINE_CWMPPARA_RA_SIZE+PROLINE_CWMPPARA_RA_OFFSET)
#endif
#endif

#else
//defined( TCSUPPORT_RESERVEAREA_BLOCK == 5)
#ifdef TCSUPPORT_NAND_BMT
/*
---------------------------------------------------------------------------------
@reserve area table@
|sector		name				cover area				note
|0			backupromfile			0~0x3ffff					256k
|1			gpon_bob			0x40000~0x5ffff			128k
|2			syslog				0x60000~0x7ffff			128k
|3			eeprom				0x80000~0x803ff			1k(reserve 1k,no use 256 bytes)
|4			cerm1				0x80400~0x813ff			4k
|5			cerm2				0x81400~0x823ff			4k
|6			cerm3				0x82400~0x833ff			4k
|7			cerm4				0x83400~0x843ff			4k
|8			username/passwd		0x84400~0x847ff			1K
|9			mrd					0x80000~0x80fff			4k
|10			imgbootflag			0x85800~0x85801			

------------------------------------------------------------------------------------
*/
#define RESERVEAREA_TOTAL_SIZE RESERVEAREA_ERASE_SIZE*5
/*backupromfile*/
#define BACKUPROMFILE_RA_SIZE NAND_FLASH_BLOCK_SIZE*2
#define BACKUPROMFILE_RA_OFFSET RESERVEAREA_BLOCK_BASE
/*defaultromfile*/
#define BOB_RA_SIZE NAND_FLASH_BLOCK_SIZE
#define BOB_RA_OFFSET (BACKUPROMFILE_RA_OFFSET+BACKUPROMFILE_RA_SIZE)
/*syslog*/
#define SYSLOG_RA_SIZE NAND_FLASH_BLOCK_SIZE
#define SYSLOG_RA_OFFSET (GPON_BOB_OFFSET+BOB_RA_SIZE)
/*eeprom*/
#define EEPROM_RA_SIZE 0x400
#define EEPROM_RA_OFFSET (SYSLOG_RA_OFFSET+SYSLOG_RA_SIZE)
/*cerm1*/
#define CERM1_RA_SIZE 0x1000
#define CERM1_RA_OFFSET (EEPROM_RA_SIZE+EEPROM_RA_OFFSET)
/*cerm2*/
#define CERM2_RA_SIZE 0x1000
#define CERM2_RA_OFFSET (CERM1_RA_SIZE+CERM1_RA_OFFSET)
/*cerm3*/
#define CERM3_RA_SIZE 0x1000
#define CERM3_RA_OFFSET (CERM2_RA_SIZE+CERM2_RA_OFFSET)
/*cerm4*/
#define CERM4_RA_SIZE 0x1000
#define CERM4_RA_OFFSET (CERM3_RA_SIZE+CERM3_RA_OFFSET)
#if !defined(TCSUPPORT_CT_BOOTLOADER_UPGRADE) 
#define USERNAMEPASSWD_RA_SIZE 0x0
#define USERNAMEPASSWD_RA_OFFSET (CERM4_RA_SIZE+CERM4_RA_OFFSET)
#endif
#ifdef TCSUPPORT_PRODUCTIONLINE
#define PROLINE_CWMPPARA_RA_SIZE 0x180
#define PROLINE_CWMPPARA_RA_OFFSET (USERNAMEPASSWD_RA_SIZE+USERNAMEPASSWD_RA_OFFSET)
#else
#define PROLINE_CWMPPARA_RA_SIZE 0x0
#define PROLINE_CWMPPARA_RA_OFFSET (USERNAMEPASSWD_RA_SIZE+USERNAMEPASSWD_RA_OFFSET)
#endif

#ifdef TCSUPPORT_MT7570
#define BOB_RA_SIZE 0xa0
#define BOB_RA_OFFSET (PROLINE_CWMPPARA_RA_OFFSET + 0x200)
#endif

#define MRD_RA_SIZE 0x1000
#define MRD_RA_OFFSET (EEPROM_RA_OFFSET + 0x1000)

/*image boot flag*/
#define IMG_BOOT_FLAG_SIZE 	1
#define IMG_BOOT_FLAG_OFFSET  	(PROLINE_CWMPPARA_RA_SIZE+PROLINE_CWMPPARA_RA_OFFSET)

#endif



#endif

#ifdef TCSUPPORT_NAND_BADBLOCK_CHECK
/*syslog*/
#define SYSLOG_RA_SIZE 0x20000
#define SYSLOG_RA_OFFSET RESERVEAREA_BLOCK_BASE

/*backupromfile*/
#define BACKUPROMFILE_RA_SIZE 0x20000
#define BACKUPROMFILE_RA_OFFSET (SYSLOG_RA_OFFSET + SYSLOG_RA_SIZE * 11)

/*eeprom*/
#define EEPROM_RA_SIZE 0x400
#define EEPROM_RA_OFFSET (BACKUPROMFILE_RA_OFFSET + BACKUPROMFILE_RA_SIZE * 15)
#endif

#endif
#endif

/* This bolck used to check BOB_RA_OFFSET is NOT big than RESERVEAREA_TOTAL_SIZE */
#ifdef TCSUPPORT_MT7570
#if defined(TCSUPPORT_CPU_EN7512) || defined(TCSUPPORT_CPU_EN7521)
#define runtime_flash_block_size() 0x10000
#endif
#if BOB_RA_OFFSET > RESERVEAREA_TOTAL_SIZE
#undef BOB_RA_OFFSET
#endif
#if defined(TCSUPPORT_CPU_EN7512) || defined(TCSUPPORT_CPU_EN7521)
#undef runtime_flash_block_size()
#endif
#endif
/* check block end */

#endif
