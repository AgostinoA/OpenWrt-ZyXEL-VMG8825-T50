#ifndef _MRD_STRUCTURE_
#define _MRD_STRUCTURE_

#if 0 
/*-------------------------------------------------------------------
 * MRD structdure reference from Econet platform
 */
#define MRD_OFFSET                  0xff00
#define MRD_SIZE                    0x100
#define MRD_SERIAL_NUM_LEN          14
#define MRD_IMEI_NUM_LEN            18
#define MRD_VENDOR_NAME_LEN         32
#define MRD_PRODUCT_NAME_LEN        32
#define MRD_MAC_ADDR_LEN            6
#define MRD_FEATUREBITS_LEN         30

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
    unsigned char unused1[32];
    unsigned char lte_gpio;
    unsigned char internet_gpio;
    unsigned char multi_upgrade_gpio[16];
    unsigned char id_76xx;
    unsigned char onu_type; //byte 0~156
//IMEI number 
#if 1
    unsigned char IMEI[MRD_IMEI_NUM_LEN];
#else
    unsigned char SN[18];
#endif
/* --- ZyXEL related --- start --- */
    unsigned char SerialNumber[MRD_SERIAL_NUM_LEN];
    unsigned char NumMacAddrs;
    unsigned char MrdVer;
    unsigned char EngDebugFlag;
    unsigned char BootingFlag;
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
    // boot_crc32 will located at the last 4 bytes of block 1.
    unsigned char unused2[6]; // let total structure have 256 bytes.
#else
    // if MRD structure locate at the end of boot.bin, need reserve 4 bytes for crc.
    unsigned char unused[2]; // let total structure have 256 bytes
    unsigned char boot_crc32[4]; //filled by trx.c
#endif
} __attribute__((packed)) MRD_DATA, *PMRD_DATA;

#else

/*-------------------------------------------------------------------
 * MRD structdure from MSTC manufacuring
 */
#define MRD_OFFSET                  0xfe00
#define MRD_SIZE                    0x200


#define MRD_DATA_SIZE			512

#define NUM_OF_NAME_BYTES           32
#define NUM_OF_SERIAL_NUMBER_BYTES	14
#define NUM_OF_MAC_BYTES             6
#define NUM_OF_COUNTRY_CODE_BYTES	 2
#define NUM_OF_FEATURE_BYTES		32
#define NUM_OF_MAGIC_BYTES 	         4
#define NUM_OF_BUILDINFO_BYTES		10
#define NUM_OF_HARDWARE_VER_BYTES    4
#define NUM_OF_RESERVED_BYTES		(MRD_DATA_SIZE - (NUM_OF_NAME_BYTES * 4) - NUM_OF_SERIAL_NUMBER_BYTES - \
						NUM_OF_MAC_BYTES - 2 - NUM_OF_COUNTRY_CODE_BYTES - NUM_OF_FEATURE_BYTES - 1 - \
						NUM_OF_BUILDINFO_BYTES - NUM_OF_HARDWARE_VER_BYTES - 1 - 1 - 1) //- 1 - 1 - 1 - 4 - 3)

typedef struct mrd {
    unsigned char VendorName[NUM_OF_NAME_BYTES];
    unsigned char ProductName[NUM_OF_NAME_BYTES];
    unsigned char NameReserved[NUM_OF_NAME_BYTES];
    unsigned char SerialNumber[NUM_OF_SERIAL_NUMBER_BYTES];
    unsigned char BaseMacAddr[NUM_OF_MAC_BYTES];
    unsigned char MacAddrQuantity;
    unsigned char EngDebugFlag;
    unsigned char CountryCode[NUM_OF_COUNTRY_CODE_BYTES];
    unsigned char FeatureBits[NUM_OF_FEATURE_BYTES];
    unsigned char MainFeatureBits;
    unsigned char BuildInfo[NUM_OF_BUILDINFO_BYTES];
    unsigned char ProductExtName[NUM_OF_NAME_BYTES];
    unsigned char HardwareVersion[NUM_OF_HARDWARE_VER_BYTES];
    unsigned char COUNTRY_array; 
    unsigned char COUNTRY_array_reserve;
    unsigned char BootingFlag;
    //unsigned char BM_VER_MAJ;
    //unsigned char BM_VER_MIN;
    //unsigned char BM_VER_ECO;
    //unsigned char builddate[4];
    //unsigned char buildtime[3];
    unsigned char Reserved[NUM_OF_RESERVED_BYTES];
} __attribute__((packed)) MRD_DATA, *PMRD_DATA;

#endif //ZYXEL or MSTC manufacturing MRD structure.

#endif
