#ifndef _MRD_STRUCTURE_
#define _MRD_STRUCTURE_

/*-------------------------------------------------------------------
 * MRD structdure for Econet SDK/MT7505/MT7520 platform
 */
#define MRD_OFFSET                  0xff00
#define MRD_SIZE                    0x100
#define MRD_SERIAL_NUM_LEN          14
#define MRD_GPON_SERIAL_NUM_LEN     8
#define MRD_VENDOR_NAME_LEN         32
#define MRD_PRODUCT_NAME_LEN        32
#define MRD_MAC_ADDR_LEN            6
#define MRD_FEATUREBITS_LEN         30
#define MRD_SN81_LEN                21

#ifdef ZYXEL_AT_SET_KEY // 20190521 Mike
// if you change MRD_SUPER_PWD_LEN, you have to change size of unused1 below
#define MRD_SUPER_PWD_LEN           10 
#define MRD_ADMIN_PWD_LEN           10
#define MRD_KEYPASSPHRASE_LEN       16
#endif // 20190521 Mike

typedef struct mrd {
    unsigned char SDRAM_CONF_array[4];
    unsigned char VENDOR_NAME[MRD_VENDOR_NAME_LEN];
    unsigned char PRODUCT_NAME[MRD_PRODUCT_NAME_LEN];
    unsigned char FUNC_BYTE[4];
    unsigned char ETHER_ADDR[MRD_MAC_ADDR_LEN];
    unsigned char SNMP_SYSOBJID_array[22];
    unsigned char COUNTRY_array;
    unsigned char ether_gpio;
    unsigned char power_gpio[2];
    unsigned char restore_flag;
    unsigned char SN81[MRD_SN81_LEN];
// 20190521, Mike Chen, alloc memory for supervisor and admin password. Require by T-Mobile NL
#ifdef ZYXEL_AT_SET_KEY // 20190521 Mike
    unsigned char supervisor[MRD_SUPER_PWD_LEN];
    unsigned char unused1[1];
#else // 20190521 Mike
    unsigned char unused1[11];
#endif // 20190521 Mike
    unsigned char dsl_gpio;
    unsigned char internet_gpio;
    unsigned char multi_upgrade_gpio[16];
    unsigned char id_75xx;
    unsigned char onu_type; //byte 0~156
//20150915, TimLiu replace ECONET original define, replace by gpon SN
#if 1
    unsigned char GponSerialNumber[MRD_GPON_SERIAL_NUM_LEN];
// // 20190521 Mike, Mike Chen, alloc memory for supervisor and admin password. Require by T-Mobile NL
#ifdef ZYXEL_AT_SET_KEY // 20190521 Mike Mike
	unsigned char admin[MRD_ADMIN_PWD_LEN];
#else  // 20190521 Mike
    unsigned char unused3[10];
#endif // 20190521 Mike
#else
    unsigned char SN[18];
#endif
/* --- ZyXEL related --- start --- */
    unsigned char SerialNumber[MRD_SERIAL_NUM_LEN];
    unsigned char NumMacAddrs;
    unsigned char MrdVer;
    unsigned char EngDebugFlag;
    unsigned char MainFeatureBit;
    unsigned char FeatureBits[MRD_FEATUREBITS_LEN];
    unsigned char HTP_Switch;
    unsigned char WpaPskKey[16];
    // bootloader related information
    unsigned char BM_VER_MAJ;
    unsigned char BM_VER_MIN;
    unsigned char BM_VER_ECO;
    unsigned char builddate[4];
    unsigned char buildtime[3]; //byte 0~72
/* --- ZyXEL related --- end --- */
#ifdef BOOTROM_LARGE_SIZE	//For ZyXEL project, we always enable "BOOTROM_LARGE_SIZE"
    // mic.conf will located at the end of block 0.
    // tcboot_crc32 will located at the last 4 bytes of block 1.
    unsigned char unused2[6]; // let total structure have 256 bytes.
#else
    // if MRD structure locate at the end of tcboot.bin, need reserve 4 bytes for crc.
    unsigned char unused[2]; // let total structure have 256 bytes.
    unsigned char tcboot_crc32[4]; //filled by trx.c
#endif
} __attribute__((packed)) MRD_DATA, *PMRD_DATA;

#endif
