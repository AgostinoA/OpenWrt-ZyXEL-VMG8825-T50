#ifndef _MRD_ENV_
#define _MRD_ENV_

/* define necessary functions after here for common platform */

#define NVRAM_SHOW_CMD				"/usr/bin/nvram show uboot > /tmp/.uboot-startup; rm /tmp/.nvramcache"
#define NVRAM_FACTORY_SHOW_CMD			"/usr/bin/nvram-factory show Factory > /tmp/.factory-startup; rm /tmp/.factorycache"
#define NVRAM_INIT_CMD				"/usr/bin/nvram show uboot > /tmp/.uboot-startup"
#define NVRAM_SETRO_CMD				"/usr/bin/nvram setro uboot %s %s"
#define NVRAM_COMMIT_CMD			"/usr/bin/nvram commit ; sync"
#define NVRAM_FACTORY_INIT_CMD			"/usr/bin/nvram-factory show Factory > /tmp/.factory-startup"
#define NVRAM_FACTORY_SETRO_CMD			"/usr/bin/nvram-factory setro Factory %s %s"
#define NVRAM_FACTORY_COMMIT_CMD		"/usr/bin/nvram-factory commit ; sync"

#define CONFIG_PARTITON_NAME			"Config"
#define FACTORY_PARTITON_NAME			"Factory"
#define DUAL_IMAGE1_PARTITON_NAME		"Kernel"
#define DUAL_IMAGE2_PARTITON_NAME		"Kernel2"
#define SINGLE_IMAGE1_PARTITON_NAME		"firmware"

#define UBOOT_STARTUP_FILE			"/tmp/.uboot-startup"
#define FACTORY_STARTUP_FILE			"/tmp/.factory-startup"
#define ROMD_PARTITON_NAME			"rom-d"
#define DATA_PARTITON_NAME			"data"
#define BANNER_FILE				"/etc/banner"

// copy the MRD name information from uboot/include/configs/rt2880.h
#define UBOOT_EXTRA_ENV_VENDOR_NAME 		"VendorName"
#define UBOOT_EXTRA_ENV_PRODUCT_NAME 		"ProductName"
#define UBOOT_EXTRA_ENV_MAIN_FEATURE_BIT	"MainFeatureBit"
#define UBOOT_EXTRA_ENV_FEATURE_BITS		"FeatureBits"
#define UBOOT_EXTRA_ENV_MODEL_ID 		"ModelID"
#define UBOOT_EXTRA_ENV_DEBUG_BIT 		"DebugFlag"
#define UBOOT_EXTRA_ENV_COUNTRY_CODE 		"Countrycode"
#define UBOOT_EXTRA_ENV_HARDWARE_VENDOR 	"HWVendor"
#define UBOOT_EXTRA_ENV_HARDWARE_VERSION 	"HWVer"
#define UBOOT_EXTRA_ENV_MACNUMBER 		"MacNumber"
#define UBOOT_EXTRA_ENV_BOOTINGFLAG 		"BootingFlag"
#define UBOOT_EXTRA_ENV_DEFAULT_SN 		"SerialNumber"
#define UBOOT_EXTRA_ENV_HOSTNAME 		"Hostname"
#define UBOOT_EXTRA_ENV_UBOOT_VER 		"UbootVer"
#define UBOOT_EXTRA_ENV_CHECK_BYPASS 		"CheckBypass"

// Define the Factory name information
#define FACTORY_EXTRA_ENV_SN 			"SerialNumber"
#define FACTORY_EXTRA_ENV_BASEMAC 		"BaseMAC"
#define FACTORY_EXTRA_ENV_MACNUMBER 		"MacNumber"

// Define the ENV string max length from trx.h 

#define FACTORY_SN_LEN      		14
#define FACTORY_BASEMAC_LEN        	12
#define FACTORY_MACNUMBER_LEN  		1
#define MAXLEN 64

#endif
