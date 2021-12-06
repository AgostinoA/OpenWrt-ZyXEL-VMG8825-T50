/*
 * trx.h
 *
 *  Created on: Mar 19, 2009
 *      Author: pork
 */

#ifndef TRX_H_
#define TRX_H_

#if 1//defined(ZYXEL)
#define ECONET_TRX_HEADER_LENGTH	0x100
#define ZYXEL_TRX_HEADER_LENGTH		0x174	//sizeof(struct trx_header)
#define CHIP_ID_LEN 		8
#define BOARD_ID_LEN 		16
#define SW_VERSION_LEN 		32
#define MODEL_ID_LEN		4

#define ZY_MODELID_PREFIX 		0x5a590000 /* prefix must be ZY */
#endif

#if 1
//using for romfile partition with ZyXEL style
#define ROMFILE_MAGIC			0x5a00
#define ROMFILE_TYPE_RAW_FILE	(ROMFILE_MAGIC | 0x01)
struct romfile_header
{
	unsigned char magic;	//should be ROMFILE_MAGIC
	unsigned char type;
	unsigned int length;
	unsigned short total_crc;	//should be 2 bytes, caculate crc with total_crc=0
	unsigned char data[0];
};
struct romd_header
{
	unsigned int length;
	unsigned short data_crc;	//should be 2 bytes
	unsigned char data[0];
};
#endif

struct trx_header {
	unsigned int magic;			/* "HDR0" */
	unsigned int header_len;    /*Length of trx header*/
	unsigned int len;			/* Length of file including header */
	unsigned int crc32;			/* 32-bit CRC from flag_version to end of file */
	unsigned char version[32];  /*firmware version number*/
	unsigned char customerversion[32];  /*firmware version number*/
//	unsigned int flag_version;	/* 0:15 flags, 16:31 version */
#if 0
	unsigned int reserved[44];	/* Reserved field of header */
#else
	unsigned int kernel_len;	//kernel length
	unsigned int rootfs_len;	//rootfs length
	unsigned int romfile_len;	//romfile length
	#if 0
	unsigned int reserved[42];  /* Reserved field of header */
	#else
	unsigned char Model[32];
	unsigned int decompAddr;//kernel decompress address
	unsigned int reserved[32];  /* Reserved field of header */
	#endif
#endif
#if 1//defined(ZYXEL)
	unsigned char chipId[CHIP_ID_LEN];		/* Provided by Makefile */
	unsigned char boardId[BOARD_ID_LEN];		/* Provided by Makefile */
	unsigned char modelId[MODEL_ID_LEN];			/* Provided by Makefile */
	unsigned int defcfg_len;	//default config length
	unsigned int imageSequence;
	unsigned char swVersionInt[SW_VERSION_LEN];	/* Provided by Makefile */
	unsigned char swVersionExt[SW_VERSION_LEN];	/* Provided by Makefile */
 	unsigned int rootfsChksum;
	unsigned int kernelChksum;
	unsigned int defcfgChksum;
    unsigned int headerChksum;
#endif
};
#define TRX_MAGIC	0x30524448	/* "HDR0" */
#define TRX_MAGIC1	0x31524448	/* "HDR1" */
#define TRX_MAGIC2	0x32524448	/* "for tclinux" */
#define TRX_MAGIC3	0x33524448	/* "for romfile" */
#endif /* TRX_H_ */
