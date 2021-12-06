 /***************************************************************************************
 *      Copyright(c) 2014 ECONET Incorporation All rights reserved.
 *
 *      This is unpublished proprietary source code of ECONET Incorporation
 *
 *      The copyright notice above does not evidence any actual or intended
 *      publication of such source code.
 ***************************************************************************************
 */

/*======================================================================================
 * MODULE NAME: spi
 * FILE NAME: spi_nand_flash.h
 * DATE: 2014/11/21
 * VERSION: 1.00
 * PURPOSE: To Provide SPI NAND Access interface.
 * NOTES:
 *
 * AUTHOR : Chuck Kuo         REVIEWED by
 *
 * FUNCTIONS  
 *      SPI_NAND_Flash_Init             To provide interface for SPI NAND init. 
 *      SPI_NAND_Flash_Get_Flash_Info   To get system current flash info. 
 *      SPI_NAND_Flash_Write_Nbyte      To provide interface for Write N Bytes into SPI NAND Flash. 
 *      SPI_NAND_Flash_Read_NByte       To provide interface for Read N Bytes from SPI NAND Flash. 
 *      SPI_NAND_Flash_Erase            To provide interface for Erase SPI NAND Flash. 
 *      SPI_NAND_Flash_Read_Byte        To provide interface for read 1 Bytes from SPI NAND Flash. 
 *      SPI_NAND_Flash_Read_DWord       To provide interface for read Double Word from SPI NAND Flash. 
 *
 * DEPENDENCIES
 *
 * * $History: $
 * MODIFICTION HISTORY:
 * Version 1.00 - Date 2014/11/21 By Chuck Kuo
 * ** This is the first versoin for creating to support the functions of
 *    current module.
 *
 *======================================================================================
 */

#ifndef __SPI_NAND_FLASH_H__
    #define __SPI_NAND_FLASH_H__

/* INCLUDE FILE DECLARATIONS --------------------------------------------------------- */
#include "asm/types.h"
#include <linux/version.h>

#if defined(TCSUPPORT_2_6_36_KERNEL) || defined(TCSUPPORT_3_18_21_KERNEL)
#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#endif

/* MACRO DECLARATIONS ---------------------------------------------------------------- */
#define SPI_NAND_FLASH_OOB_FREE_ENTRY_MAX				(32)

#define CACHE_ADDR_INFO_START_ADDR						(0x9FA40000)
/* spi nand info, [31:16] = controllerECC ability, bits[15:0] = spare area size per sector */
#define SPI_NAND_CONTROLLER_ECC_INFO_SRAM_ADDR_INFO		(CACHE_ADDR_INFO_START_ADDR + 0x00)
#define SPI_NAND_CONTROLLER_ECC_INFO_FLASH_ADDR_INFO	(0x28)

/* SPI NAND Size Define */
#define _SPI_NAND_PAGE_SIZE_512				0x0200
#define _SPI_NAND_PAGE_SIZE_2KBYTE			0x0800	
#define _SPI_NAND_PAGE_SIZE_4KBYTE			0x1000
#define _SPI_NAND_OOB_SIZE_64BYTE			0x40
#define _SPI_NAND_OOB_SIZE_120BYTE			0x78
#define _SPI_NAND_OOB_SIZE_128BYTE			0x80
#define _SPI_NAND_OOB_SIZE_256BYTE			0x100
#define _SPI_NAND_BLOCK_SIZE_128KBYTE		0x20000
#define _SPI_NAND_BLOCK_SIZE_256KBYTE		0x40000
#define _SPI_NAND_CHIP_SIZE_512MBIT			0x04000000
#define _SPI_NAND_CHIP_SIZE_1GBIT			0x08000000
#define _SPI_NAND_CHIP_SIZE_2GBIT			0x10000000
#define _SPI_NAND_CHIP_SIZE_4GBIT			0x20000000
#define _SPI_NAND_CHIP_SIZE_8GBIT			0x40000000

/* SPI NAND Manufacturers ID */
#define _SPI_NAND_MANUFACTURER_ID_GIGADEVICE	0xC8
#define _SPI_NAND_MANUFACTURER_ID_WINBOND		0xEF
#define _SPI_NAND_MANUFACTURER_ID_ESMT			0xC8
#define _SPI_NAND_MANUFACTURER_ID_MXIC			0xC2
#define _SPI_NAND_MANUFACTURER_ID_ZENTEL		0xC8
#define _SPI_NAND_MANUFACTURER_ID_ETRON			0xD5
#define _SPI_NAND_MANUFACTURER_ID_TOSHIBA		0x98
#define _SPI_NAND_MANUFACTURER_ID_MICRON		0x2C
#define _SPI_NAND_MANUFACTURER_ID_HEYANG		0xC9
#define _SPI_NAND_MANUFACTURER_ID_PN			0xA1
#define _SPI_NAND_MANUFACTURER_ID_ATO			0x9B
#define _SPI_NAND_MANUFACTURER_ID_FM			0xA1
#define _SPI_NAND_MANUFACTURER_ID_XTX			0x0B
#define _SPI_NAND_MANUFACTURER_ID_MIRA			0xC8

/* SPI NAND Device ID */
#define _SPI_NAND_DEVICE_ID_GD5E1GQ4UBYIG	0x11
#define _SPI_NAND_DEVICE_ID_GD5F1GQ4UAYIG	0xF1
#define _SPI_NAND_DEVICE_ID_GD5F1GQ4UBYIG	0xD1
#define _SPI_NAND_DEVICE_ID_GD5F1GQ4UCYIG	0xB1
#define _SPI_NAND_DEVICE_ID_GD5F2GQ4UBYIG	0xD2
#define _SPI_NAND_DEVICE_ID_GD5F2GQ4UCYIG	0xB2
#define _SPI_NAND_DEVICE_ID_GD5F4GQ4UBYIG	0xD4
#define _SPI_NAND_DEVICE_ID_GD5F4GQ4UCYIG	0xB4
#define _SPI_NAND_DEVICE_ID_F50L512M41A		0x20
#define _SPI_NAND_DEVICE_ID_F50L1G41A0		0x21
#define _SPI_NAND_DEVICE_ID_F50L1G41LB		0x01
#define _SPI_NAND_DEVICE_ID_F50L2G41LB		0x0A
#define _SPI_NAND_DEVICE_ID_W25N01GV		0xAA
#define _SPI_NAND_DEVICE_ID_W25M02GV		0xAB
#define _SPI_NAND_DEVICE_ID_MXIC35LF1GE4AB	0x12
#define _SPI_NAND_DEVICE_ID_MXIC35LF2GE4AB	0x22
#define _SPI_NAND_DEVICE_ID_MXIC35LF2G14AC	0x20
#define _SPI_NAND_DEVICE_ID_MXIC35LF4GE4AB	0x32
#define _SPI_NAND_DEVICE_ID_A5U12A21ASC		0x20
#define _SPI_NAND_DEVICE_ID_A5U1GA21BWS		0x21
#define _SPI_NAND_DEVICE_ID_EM73C044SNA		0x19
#define _SPI_NAND_DEVICE_ID_EM73C044SNB		0x11
#define _SPI_NAND_DEVICE_ID_EM73C044SND		0x1D
#define _SPI_NAND_DEVICE_ID_EM73D044SNA		0x12
#define _SPI_NAND_DEVICE_ID_EM73D044SNC		0x0A
#define _SPI_NAND_DEVICE_ID_EM73D044SND		0x1E
#define _SPI_NAND_DEVICE_ID_EM73D044SNF		0x10
#define _SPI_NAND_DEVICE_ID_EM73E044SNA		0x03
#define _SPI_NAND_DEVICE_ID_EM73F044SNA		0x24
#define _SPI_NAND_DEVICE_ID_TC58CVG0S3H		0xC2
#define _SPI_NAND_DEVICE_ID_TC58CVG1S3H		0xCB
#define _SPI_NAND_DEVICE_ID_TC58CVG2S0H		0xCD
#define _SPI_NAND_DEVICE_ID_MT29F1G01		0x14
#define _SPI_NAND_DEVICE_ID_MT29F2G01		0x24
#define _SPI_NAND_DEVICE_ID_MT29F4G01		0x36
#define _SPI_NAND_DEVICE_ID_HYF1GQ4UAACAE	0x51
#define _SPI_NAND_DEVICE_ID_HYF2GQ4UAACAE	0x52
#define _SPI_NAND_DEVICE_ID_HYF2GQ4UHCCAE	0x5A
#define _SPI_NAND_DEVICE_ID_HYF4GQ4UAACBE	0xD4
#define _SPI_NAND_DEVICE_ID_HYF1GQ4UDACAE	0x21
#define _SPI_NAND_DEVICE_ID_HYF2GQ4UDACAE	0x22
#define _SPI_NAND_DEVICE_ID_PN26G01AWSIUG	0xE1
#define _SPI_NAND_DEVICE_ID_PN26G02AWSIUG	0xE2
#define _SPI_NAND_DEVICE_ID_ATO25D1GA		0x12
#define _SPI_NAND_DEVICE_ID_FM25G01B		0xD1
#define _SPI_NAND_DEVICE_ID_FM25G02B		0xD2
#define _SPI_NAND_DEVICE_ID_FM25G02			0xF2
#define _SPI_NAND_DEVICE_ID_XT26G02B		0xF2
#define _SPI_NAND_DEVICE_ID_PSU1GS20BN		0x21

/* SPI NAND register address of command set */
#define _SPI_NAND_ADDR_ECC					0x90	/* Address of ECC Config */
#define _SPI_NAND_ADDR_PROTECTION			0xA0	/* Address of protection */
#define _SPI_NAND_ADDR_FEATURE				0xB0	/* Address of feature */
#define _SPI_NAND_ADDR_STATUS				0xC0	/* Address of status */
#define _SPI_NAND_ADDR_FEATURE_4			0xD0	/* Address of status 4 */
#define _SPI_NAND_ADDR_STATUS_5				0xE0	/* Address of status 5 */

/* TYPE DECLARATIONS ----------------------------------------------------------------- */
typedef enum{
	SPI_NAND_FLASH_READ_DUMMY_BYTE_PREPEND,
	SPI_NAND_FLASH_READ_DUMMY_BYTE_APPEND,
	
	SPI_NAND_FLASH_READ_DUMMY_BYTE_DEF_NO
	
} SPI_NAND_FLASH_READ_DUMMY_BYTE_T;

typedef enum{
	SPI_NAND_FLASH_RTN_NO_ERROR =0,
	SPI_NAND_FLASH_RTN_PROBE_ERROR,
	SPI_NAND_FLASH_RTN_ALIGNED_CHECK_FAIL,
	SPI_NAND_FLASH_RTN_DETECTED_BAD_BLOCK,
	SPI_NAND_FLASH_RTN_ERASE_FAIL,
	SPI_NAND_FLASH_RTN_PROGRAM_FAIL,
	SPI_NAND_FLASH_RTN_NFI_FAIL,
	SPI_NAND_FLASH_RTN_ECC_DECODE_FAIL,


	SPI_NAND_FLASH_RTN_DEF_NO
} SPI_NAND_FLASH_RTN_T;

typedef enum{
	SPI_NAND_FLASH_READ_SPEED_MODE_SINGLE =0,
	SPI_NAND_FLASH_READ_SPEED_MODE_DUAL,
	SPI_NAND_FLASH_READ_SPEED_MODE_QUAD,
	
	SPI_NAND_FLASH_READ_SPEED_MODE_DEF_NO	
} SPI_NAND_FLASH_READ_SPEED_MODE_T;


typedef enum{
	SPI_NAND_FLASH_WRITE_SPEED_MODE_SINGLE =0,
	SPI_NAND_FLASH_WRITE_SPEED_MODE_QUAD,
	
	SPI_NAND_FLASH_WRITE_SPEED_MODE_DEF_NO	
} SPI_NAND_FLASH_WRITE_SPEED_MODE_T;

typedef enum{
	SPI_NAND_FLASH_WRITE_LOAD_FIRST =0,
	SPI_NAND_FLASH_WRITE_EN_FIRST,
} SPI_NAND_FLASH_WRITE_EN_TYPE_T;

typedef enum{
	SPI_NAND_FLASH_DEBUG_LEVEL_0 =0,
	SPI_NAND_FLASH_DEBUG_LEVEL_1,
	SPI_NAND_FLASH_DEBUG_LEVEL_2,
	
	SPI_NAND_FLASH_DEBUG_LEVEL_DEF_NO	
} SPI_NAND_FLASH_DEBUG_LEVEL_T;

/* Bitwise */
#define SPI_NAND_FLASH_FEATURE_NONE			( 0x00 )
#define SPI_NAND_FLASH_PLANE_SELECT_HAVE	( 0x01 << 0 )
#define SPI_NAND_FLASH_DIE_SELECT_1_HAVE	( 0x01 << 1 )
#define SPI_NAND_FLASH_DIE_SELECT_2_HAVE	( 0x01 << 2 )
#define SPI_NAND_FLASH_NO_ECC_STATUS_HAVE	( 0x01 << 3 )

struct spi_nand_flash_oobfree{
	unsigned long	offset;
	unsigned long	len;
};

struct spi_nand_flash_ooblayout
{	unsigned long	oobsize;
	struct spi_nand_flash_oobfree oobfree[SPI_NAND_FLASH_OOB_FREE_ENTRY_MAX];
};	

struct SPI_NAND_ECC_FAIL_CHECK_INFO_T {
	u8	ecc_check_mask;
	u8	ecc_uncorrected_value;
};

struct SPI_NAND_UNLOCK_BLOCK_INFO_T {
	u8	unlock_block_mask;
	u8	unlock_block_value;
};

struct SPI_NAND_QUAD_EN_INFO_T {
	u8	quad_en_mask;
	u8	quad_en_value;
};

struct SPI_NAND_ECC_EN_INFO_T {
	u8	ecc_en_addr;
	u8	ecc_en_mask;
	u8	ecc_en_value;
};

struct SPI_NAND_FLASH_INFO_T {
	const u8								mfr_id;
	const u8								dev_id;
	const u8								*ptr_name;
	u32										device_size;	/* Flash total Size */
	u32										page_size;		/* Page Size 		*/
	u32										erase_size;		/* Block Size 		*/
	u32										oob_size;		/* Spare Area (OOB) Size */
	SPI_NAND_FLASH_READ_DUMMY_BYTE_T		dummy_mode;
	SPI_NAND_FLASH_READ_SPEED_MODE_T		read_mode;
	struct spi_nand_flash_ooblayout			*oob_free_layout;
	u8										die_num;
	SPI_NAND_FLASH_WRITE_SPEED_MODE_T		write_mode;
	u32										feature;
	struct SPI_NAND_ECC_FAIL_CHECK_INFO_T	ecc_fail_check_info;
	SPI_NAND_FLASH_WRITE_EN_TYPE_T			write_en_type;
	struct SPI_NAND_UNLOCK_BLOCK_INFO_T		unlock_block_info;
	struct SPI_NAND_QUAD_EN_INFO_T			quad_en;
	struct SPI_NAND_ECC_EN_INFO_T			ecc_en;
};

extern const struct SPI_NAND_FLASH_INFO_T spi_nand_flash_tables[];
extern SPI_NAND_FLASH_RTN_T scan_spi_nand_table(struct SPI_NAND_FLASH_INFO_T *ptr_rtn_device_t);
extern struct spi_nand_flash_ooblayout ooblayout_spi_controller_ecc;

struct nand_info {
	int mfr_id;
	int dev_id;
	char *name;
	int numchips;
	int chip_shift;
	int page_shift;
	int erase_shift;
	int oob_shift;
	int badblockpos;
	int opcode_type;
};

struct ra_nand_chip {
	struct nand_info *flash;
};

#if defined(TCSUPPORT_2_6_36_KERNEL) || defined(TCSUPPORT_3_18_21_KERNEL)
	struct spinand_info {
	        struct nand_ecclayout	*ecclayout;
	        struct spi_device		*spi;
	        void					*priv;
	};

	struct spinand_state {
	        uint32_t        col;
	        uint32_t        row;
	        int             buf_idx;
	        u8              *buf;
			uint32_t		buf_len;
			int				oob_idx;
			u8 				*oob_buf;
			uint32_t		oob_buf_len;
			uint32_t		command;
	};

	struct en7512_spinand_host
	{
		struct nand_chip		nand_chip;
		struct mtd_info			mtd;
		struct nand_ecclayout	*ecclayout;
		struct spinand_state	state;
		void					*priv;
	};
#endif

typedef struct
{
   unsigned short id;          
   unsigned int ext_id; 
   unsigned char  addr_cycle;
   unsigned char  iowidth;
   unsigned short totalsize;   
   unsigned short blocksize;
   unsigned short pagesize;
   unsigned int timmingsetting;
   char devciename[14];
   unsigned int advancedmode;   
}flashdev_info;




/* EXPORTED SUBPROGRAM SPECIFICATION ------------------------------------------------- */

/*------------------------------------------------------------------------------------
 * FUNCTION: SPI_NAND_FLASH_RTN_T SPI_NAND_Flash_Init( long  rom_base )
 * PURPOSE : To provide interface for SPI NAND init.
 * AUTHOR  : Chuck Kuo
 * CALLED BY
 *   -
 * CALLS
 *   -
 * PARAMs  :
 *   INPUT : rom_base - The rom_base variable of this function.
 *   OUTPUT: None
 * RETURN  : SPI_RTN_NO_ERROR - Successful.   Otherwise - Failed.
 * NOTES   :
 * MODIFICTION HISTORY:
 * Date 2014/12/12 by Chuck Kuo - The first revision for this function.
 *

 *------------------------------------------------------------------------------------
 */
SPI_NAND_FLASH_RTN_T SPI_NAND_Flash_Init( u32   rom_base );

/*------------------------------------------------------------------------------------
 * FUNCTION: SPI_NAND_FLASH_RTN_T SPI_NAND_Flash_Get_Flash_Info( struct SPI_NAND_FLASH_INFO_T    *ptr_rtn_into_t )
 * PURPOSE : To get system current flash info.
 * AUTHOR  : Chuck Kuo
 * CALLED BY
 *   -
 * CALLS
 *   -
 * PARAMs  :
 *   INPUT : None
 *   OUTPUT: ptr_rtn_into_t  - A pointer to the structure of the ptr_rtn_into_t variable.
 * RETURN  : SPI_RTN_NO_ERROR - Successful.   Otherwise - Failed.
 * NOTES   :
 * MODIFICTION HISTORY:
 * Date 2015/01/14 by Chuck Kuo - The first revision for this function.
 *
 *------------------------------------------------------------------------------------
 */
#if !defined(BOOTROM_EXT)
SPI_NAND_FLASH_RTN_T SPI_NAND_Flash_Get_Flash_Info( struct SPI_NAND_FLASH_INFO_T *ptr_rtn_into_t);

SPI_NAND_FLASH_RTN_T SPI_NAND_Flash_Set_Flash_Info( struct SPI_NAND_FLASH_INFO_T *ptr_rtn_into_t);
#endif

/*------------------------------------------------------------------------------------
 * FUNCTION: SPI_NAND_FLASH_RTN_T SPI_NAND_Flash_Write_Nbyte( u32    dst_addr,
 *                                                            u32    len,
 *                                                            u32    *ptr_rtn_len,
 *                                                            u8*    ptr_buf      )
 * PURPOSE : To provide interface for Write N Bytes into SPI NAND Flash.
 * AUTHOR  : Chuck Kuo
 * CALLED BY
 *   -
 * CALLS
 *   -
 * PARAMs  :
 *   INPUT : dst_addr - The dst_addr variable of this function.
 *           len      - The len variable of this function.
 *           buf      - The buf variable of this function.
 *   OUTPUT: rtn_len  - The rtn_len variable of this function.
 * RETURN  : SPI_RTN_NO_ERROR - Successful.   Otherwise - Failed.
 * NOTES   :
 * MODIFICTION HISTORY:
 * Date 2014/12/15 by Chuck Kuo - The first revision for this function.
 *

 *------------------------------------------------------------------------------------
 */
SPI_NAND_FLASH_RTN_T SPI_NAND_Flash_Write_Nbyte( u32								dst_addr,
                                                 u32    							len,
                                                 u32    							*ptr_rtn_len,
                                                 u8									*ptr_buf,      
                                                 SPI_NAND_FLASH_WRITE_SPEED_MODE_T 	speed_mode	);

/*------------------------------------------------------------------------------------
 * FUNCTION: int SPI_NAND_Flash_Read_NByte( long     addr,
 *                                          long     len,
 *                                          long     *retlen,
 *                                          char     *buf    )
 * PURPOSE : To provide interface for Read N Bytes from SPI NAND Flash.
 * AUTHOR  : Chuck Kuo
 * CALLED BY
 *   -
 * CALLS
 *   -
 * PARAMs  :
 *   INPUT : addr    - The addr variable of this function.
 *           len     - The len variable of this function.
 *           retlen  - The retlen variable of this function.
 *           buf     - The buf variable of this function.
 *   OUTPUT: None
 * RETURN  : SPI_RTN_NO_ERROR - Successful.   Otherwise - Failed.
 * NOTES   :
 * MODIFICTION HISTORY:
 * Date 2014/12/12 by Chuck Kuo - The first revision for this function.
 *

 *------------------------------------------------------------------------------------
 */
u32 SPI_NAND_Flash_Read_NByte(	
							#if defined(TCSUPPORT_2_6_36_KERNEL) || defined(TCSUPPORT_3_18_21_KERNEL)
								u64 							addr,
							#else
								u32 							addr,
							#endif
								u32								 len, 
								u32								 *retlen, 
								u8								 *buf, 
								SPI_NAND_FLASH_READ_SPEED_MODE_T speed_mode,
								SPI_NAND_FLASH_RTN_T *status);


/*------------------------------------------------------------------------------------
 * FUNCTION: SPI_NAND_FLASH_RTN_T SPI_NAND_Flash_Erase( u32  dst_addr,
 *                                                      u32  len      )
 * PURPOSE : To provide interface for Erase SPI NAND Flash.
 * AUTHOR  : Chuck Kuo
 * CALLED BY
 *   -
 * CALLS
 *   -
 * PARAMs  :
 *   INPUT : dst_addr - The dst_addr variable of this function.
 *           len      - The len variable of this function.
 *   OUTPUT: None
 * RETURN  : SPI_RTN_NO_ERROR - Successful.   Otherwise - Failed.
 * NOTES   :
 * MODIFICTION HISTORY:
 * Date 2014/12/17 by Chuck Kuo - The first revision for this function.
 *

 *------------------------------------------------------------------------------------
 */
SPI_NAND_FLASH_RTN_T SPI_NAND_Flash_Erase( u32  dst_addr,
                                           u32  len      );

/*------------------------------------------------------------------------------------
 * FUNCTION: char SPI_NAND_Flash_Read_Byte( long     addr )
 * PURPOSE : To provide interface for read 1 Bytes from SPI NAND Flash.
 * AUTHOR  : Chuck Kuo
 * CALLED BY
 *   -
 * CALLS
 *   -
 * PARAMs  :
 *   INPUT : addr - The addr variable of this function.
 *   OUTPUT: None
 * RETURN  : SPI_RTN_NO_ERROR - Successful.   Otherwise - Failed.
 * NOTES   :
 * MODIFICTION HISTORY:
 * Date 2014/12/12 by Chuck Kuo - The first revision for this function.
 *

 *------------------------------------------------------------------------------------
 */
unsigned char SPI_NAND_Flash_Read_Byte(
									#if defined(TCSUPPORT_2_6_36_KERNEL) || defined(TCSUPPORT_3_18_21_KERNEL)
										u64 addr,
									#else
										u32 addr,
									#endif
										SPI_NAND_FLASH_RTN_T *status);


/*------------------------------------------------------------------------------------
 * FUNCTION: long SPI_NAND_Flash_Read_DWord( long    addr )
 * PURPOSE : To provide interface for read Double Word from SPI NAND Flash.
 * AUTHOR  : Chuck Kuo
 * CALLED BY
 *   -
 * CALLS
 *   -
 * PARAMs  :
 *   INPUT : addr - The addr variable of this function.
 *   OUTPUT: None
 * RETURN  : SPI_RTN_NO_ERROR - Successful.   Otherwise - Failed.
 * NOTES   :
 * MODIFICTION HISTORY:
 * Date 2014/12/12 by Chuck Kuo - The first revision for this function.
 *

 *------------------------------------------------------------------------------------
 */
unsigned long SPI_NAND_Flash_Read_DWord(
									#if defined(TCSUPPORT_2_6_36_KERNEL) || defined(TCSUPPORT_3_18_21_KERNEL)
										u64 addr,
									#else
										u32 addr,
									#endif
										SPI_NAND_FLASH_RTN_T *status);

/*------------------------------------------------------------------------------------
 * FUNCTION: void SPI_NAND_Flash_Clear_Read_Cache_Data( void )
 * PURPOSE : To clear the cache data for read. 
 *           (The next time to read data will get data from flash chip certainly.)
 * AUTHOR  : Chuck Kuo
 * CALLED BY
 *   -
 * CALLS
 *   -
 * PARAMs  :
 *   INPUT : None
 *   OUTPUT: None
 * RETURN  : SPI_RTN_NO_ERROR - Successful.   Otherwise - Failed.
 * NOTES   :
 * MODIFICTION HISTORY:
 * Date 2015/01/21 by Chuck Kuo - The first revision for this function.
 *
 *------------------------------------------------------------------------------------
 */
void SPI_NAND_Flash_Clear_Read_Cache_Data( void );

void SPI_NAND_Flash_Set_DmaMode( u32 input );
void SPI_NAND_Flash_Get_DmaMode( u32 *val );
SPI_NAND_FLASH_RTN_T SPI_NAND_Flash_Enable_OnDie_ECC( void );
SPI_NAND_FLASH_RTN_T SPI_NAND_Flash_Disable_OnDie_ECC( void );

#if	defined(TCSUPPORT_NAND_BMT) && !defined(LZMA_IMG) && !defined(BOOTROM_EXT)
int en7512_nand_exec_read_page(u32 page, u8* date, u8* oob);
int en7512_nand_check_block_bad(u32 offset, u32 bmt_block);
int en7512_nand_erase(u32 offset);
int en7512_nand_mark_badblock(u32 offset, u32 bmt_block);
int en7512_nand_exec_write_page(u32 page, u8 *dat, u8 *oob);
#endif

#endif /* ifndef __SPI_NAND_FLASH_H__ */
/* End of [spi_nand_flash.h] package */

