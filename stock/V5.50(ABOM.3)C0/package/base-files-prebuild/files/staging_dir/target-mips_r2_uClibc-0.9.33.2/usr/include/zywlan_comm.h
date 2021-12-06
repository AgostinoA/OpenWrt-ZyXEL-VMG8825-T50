#ifndef _ZYWLAN_COMM_H
#define _ZYWLAN_COMM_H

#define MAC_ADDR_LEN 6
typedef struct zyWlanSsid_s {
	bool varEnable;
	bool mainSsid;
	char ssidObjPath[36];
	char apObjPath[36];
	bool enable;
	bool __enable;
	char ifName[65];
	char ssid[33];
	bool hideSsid;
	bool isolation;
	bool bssIsolation;
	bool wmfEnable;
	bool wmmSupported;
	bool wmmEnable;
	bool wmmNoAck;
	bool wmmApsd;
	uint32_t maxAssoc;
	uint32_t ssid_prio;
	char bssMacAddr[18];
	char brIfName[32];
	/*Security*/
	bool preauth;
	char authMode[16];
	char encryption[16];
	uint8_t wepkeyid;
	char wepkey[4][32];
	char psk[65];
	char keyPass[64];
	uint32_t rekeyInterval;
	uint32_t reauthInterval;
	char radiusIp[46];
	uint32_t radiusPort;
	char radiusKey[256];
#ifdef ZYXEL_SUPPORT_8021X
	char secondRadiusIp[46];
	uint32_t secondRadiusPort;
	char secondRadiusKey[256];
#endif
	char macFltMode[10];
	char macFltList[601];
	/*WSC*/
	bool wpsEnable;
	bool wpsConfigured;
	bool version2;
	char WPS_PairingID[256];
	char WPS_PairingID_Mode[12];
#ifdef ZYXEL_INDEPENDENT_WPS_METHODS
	bool enablePBC;
	bool enableStaPin;
	bool enableAPPin;
#endif
//	char wpsConf[12]; 
	unsigned int wpsConfMethod;
	char wpsDevPin[9];
//	char wpsStaPin[12];
	char wpsUuid[40];
	char wpsDevName[61]; //modelName
	char wpsManufacturer[65];
	char wpsSerialNumber[65];
	uint32_t upRate;
	uint32_t downRate;
	uint32_t vlanId;
	// pmf method
	// 0 = disable
	// 1 = capable
	// 2 = req
	unsigned int pmfMethod;
#ifdef PRESET_BACKHAUL_SETTING
	uint8_t attribute;
#endif
#if defined(ONECONNECT) && defined(BUILD_SONIQ)
	uint8_t flags;
#endif
}zyWlanSsid_t;

typedef struct zyWlanRadio_s {
	char objPath[36];
	int8_t radioIdx;
	bool enable;
	bool __enable;
	bool autoChSelect;
	bool apCoex;
	bool frameburst;
	bool atf;
	bool ssid_prio_en;
	uint8_t mu_mimo;
	int8_t obss_coex;
	int8_t protection;
	int8_t nProtection;
	int8_t preamble;
	int8_t htExtCha;
	int8_t rifsAdv;
	int8_t wifiMode;
	uint8_t htBw;
	uint8_t txPwrPcnt;
	uint8_t txbf_bfr;
	uint8_t txbf_bfe;
	uint16_t channel;
	uint32_t autoChPeriod;
	uint32_t autoChPolicy;
	uint32_t bcnPeriod;
	uint32_t dtimPeriod;
	uint32_t ctsRtsThrshld;
	uint32_t fragThrshld;
	uint16_t ssidNum;
	int rxChainPwrSaveEnable;
	int rxChainPwrSaveQuietTime;
	int rxChainPwrSavePps;
	int radioPwrSaveEnable;
	int radioPwrSaveQuietTime;
	int radioPwrSavePps;
	int radioPwrSaveLevel;
	int band;
	int rate;
	int mcs;
	int mrate;
	int RegMode;
	int DfsPreIsm;
	int DfsPostIsm;
	int TpcDb;
	int lazyWds;
	int interferenceMode;
	char acs_autoch_skip[101];
	char wlMode[12];
	char wdsMacList[80];
	char phyType[5];
	char country[11];
	char ifName[65];
	char status[18];
	unsigned char macaddr[MAC_ADDR_LEN];
	unsigned long GPIOOverlays;
	char __inactive_channels[129];
	char inactive_channels[129];
	bool probresp_rw;
        char singleSKU[9];
}zyWlanRadio_t;

#ifdef ZYXEL_EASYMESH
typedef struct zyWlanEasyMesh_s {
	bool enable;
}zyWlanEasyMesh_t;

typedef struct zyWlanExtBssInfo_s {
	uint8_t bandIndex;
	uint8_t attribute;
	uint16_t MDID;
	uint16_t TCI;
}zyWlanExtBssInfo_t;
#endif

enum {
	CTLSB_NONE=0,
	CTLSB_LOWER,
	CTLSB_UPPER,
	CTLSB_80_LL,
	CTLSB_80_LU,
	CTLSB_80_UL,
	CTLSB_80_UU,
	CTLSB_160_LLL,
	CTLSB_160_LLU,
	CTLSB_160_LUL,
	CTLSB_160_LUU,
	CTLSB_160_ULL,
	CTLSB_160_ULU,
	CTLSB_160_UUL,
	CTLSB_160_UUU
};

#define WLAN_RADIO_NUM 1
#define WLAN_MAX_BSS ((TOTAL_INTERFACE_24G < TOTAL_INTERFACE_5G)? TOTAL_INTERFACE_5G : TOTAL_INTERFACE_24G) //Ron, def in project.defconfig

#define WL_PHYTYPE_A      0
#define WL_PHYTYPE_B      1
#define WL_PHYTYPE_G      2
#define WL_PHYTYPE_N      4
#define WL_PHYTYPE_LP     5
#define WL_PHYTYPE_SSN    6
#define WL_PHYTYPE_HT     7
#define WL_PHYTYPE_LCN    8
#define WL_PHYTYPE_LCN40  10
#define WL_PHYTYPE_AC     11

#define WL_PHY_TYPE_A    "a"
#define WL_PHY_TYPE_B    "b"
#define WL_PHY_TYPE_G    "g"
#define WL_PHY_TYPE_N    "n"
#define WL_PHY_TYPE_LP   "l"
#define WL_PHY_TYPE_H    "h"
#define WL_PHY_TYPE_AC   "v"

/* authentication mode */
#define WL_AUTH_OPEN                    "open"
#define WL_AUTH_SHARED                  "shared"
#define WL_AUTH_RADIUS                  "radius"
#define WL_AUTH_WPA                     "wpa"
#define WL_AUTH_WPA_PSK                 "psk"
#define WL_AUTH_WPA2                    "wpa2"
#define WL_AUTH_WPA2_PSK                "psk2"
#define WL_AUTH_WPA2_MIX                "wpa wpa2"
#define WL_AUTH_WPA2_PSK_MIX            "psk psk2"

#define REG_MODE_OFF             0 /* disabled 11h/d mode */
#define REG_MODE_H               1 /* use 11h mode */
#define REG_MODE_D               2 /* use 11d mode */

#define REG_MODE_OFF_STR			"off"
#define REG_MODE_H_STR			"h"
#define REG_MODE_D_STR			"d"

#define BAND_A                  1
#define BAND_B                  2

/* mimo */
#define WL_CTL_SB_LOWER         -1
#define WL_CTL_SB_NONE           0
#define WL_CTL_SB_UPPER          1

/* Config methods */
#define WPS_CONFMET_USBA            0x0001	/* Deprecated in WSC 2.0 */
#define WPS_CONFMET_ETHERNET        0x0002	/* Deprecated in WSC 2.0 */
#define WPS_CONFMET_LABEL           0x0004
#define WPS_CONFMET_DISPLAY         0x0008
#define WPS_CONFMET_EXT_NFC_TOK     0x0010
#define WPS_CONFMET_INT_NFC_TOK     0x0020
#define WPS_CONFMET_NFC_INTF        0x0040
#define WPS_CONFMET_PBC             0x0080
#define WPS_CONFMET_KEYPAD          0x0100
/* WSC 2.0 */
#define WPS_CONFMET_VIRT_PBC        0x0280
#define WPS_CONFMET_PHY_PBC         0x0480
#define WPS_CONFMET_VIRT_DISPLAY    0x2008
#define WPS_CONFMET_PHY_DISPLAY     0x4008

#if defined(ONECONNECT)
#define ZYWLSSID_FLAGS_AUTOCONFIG	(1<<0)
#endif

#define MAX_SUPPORT_RADIO			2

typedef enum {
	ZY_WPS_INIT = 0,
	ZY_WPS_ASSOCIATED,
	ZY_WPS_OK,
	ZY_WPS_MSG_ERR,
	ZY_WPS_TIMEOUT,
	ZY_WPS_SENDM2,
	ZY_WPS_SENDM7,
	ZY_WPS_MSGDONE,
	ZY_WPS_PBCOVERLAP,
	ZY_WPS_FIND_PBC_AP,
	ZY_WPS_ASSOCIATING
} ZYWIFID_WPS_SCSTATE;

typedef enum {
	ZY_MODE_80211_G=0,
	ZY_MODE_80211_B,
	ZY_MODE_80211_BG,
	ZY_MODE_80211_N,
	ZY_MODE_80211_BGN,
	ZY_MODE_80211_GN,
	ZY_MODE_80211_BGNAX,
	ZY_MODE_80211_A,
	ZY_MODE_80211_AN,
	ZY_MODE_80211_AC,
	ZY_MODE_80211_NAC,
	ZY_MODE_80211_ANAC,
	ZY_MODE_80211_ANACAX,
	ZY_MODE_80211_NONE,
} ZYWIFID_80211_MODE;

// protection management frame
enum {
	ZY_PMF_DISABLE=0,
	ZY_PMF_CAPABLE,
	ZY_PMF_REQ
};

enum {
	HT_20_1SS = 0,
	HT_20_2SS,
	HT_20_3SS,
	HT_20_4SS,
	HT_40_1SS,
	HT_40_2SS,
	HT_40_3SS,
	HT_40_4SS,
	VHT_20_1SS,
	VHT_20_2SS,
	VHT_20_3SS,
	VHT_20_4SS,
	VHT_40_1SS,
	VHT_40_2SS,
	VHT_40_3SS,
	VHT_40_4SS,
	VHT_80_1SS,
	VHT_80_2SS,
	VHT_80_3SS,
	VHT_80_4SS,
};

/*802.11n, bw = 20~40, antenna_number = 1~4*/
#define HT20_1SS_RATES "7.2,14.4,21.7,28.9,43.3,57.8,65,72.2"     //bw = 20 with 1 antenna
#define HT20_2SS_RATES "7.2,14.4,21.7,28.9,43.3,57.8,65,72.2,86.7,115.6,130,144.4"//+HT20_1SS_RATES
#define HT20_3SS_RATES "7.2,14.4,21.7,28.9,43.3,57.8,65,72.2,86.7,115.6,130,144.4,173.3,195,216.7" //+HT20_1SS_RATES+HT20_2SS_RATES
#define HT20_4SS_RATES "7.2,14.4,21.7,28.9,43.3,57.8,65,72.2,86.7,\
115.6,130,144.4,173.3,195,216.7,231.1,260,288.9"

#define HT40_1SS_RATES "15,30,45,60,90,120,135,150"
#define HT40_2SS_RATES "15,30,45,60,90,120,135,150,180,240,270,300"
#define HT40_3SS_RATES "15,30,45,60,90,120,135,150,180,240,270,300,360,405,450"
#define HT40_4SS_RATES "15,30,45,60,90,120,135,150,180,240,270,300,\
360,405,450,480,540,600"

/*802.11ac, bw = 20~80, antenna_number = 1~4*/
#define VHT20_1SS_RATES "7.2,14.4,21.7,28.9,43.3,57.8,65,72.2,86.7"
#define VHT20_2SS_RATES "115.6,130,144.4,173.3" //VHT20_2SS_RATES contains VHT20_1SS_RATES
#define VHT20_3SS_RATES "195,216.7,260,288.9"   //VHT20_3SS_RATES contains VHT20_2SS_RATES and VHT20_1SS_RATES
#define VHT20_4SS_RATES "231.2,260,288.8,346.8" //VHT20_4SS_RATES contains VHT20_3SS_RATES, VHT20_2SS_RATES and VHT20_1SS_RATES

#define VHT40_1SS_RATES "15,30,45,60,90,120,135,150,180,200"
#define VHT40_2SS_RATES "240,270,300,360,400"
#define VHT40_3SS_RATES "405,450,540,600"
#define VHT40_4SS_RATES "480,780,800"

#define VHT80_1SS_RATES "32.5,65,97.5,130,195,260,292.5,325,390,433.3"
#define VHT80_2SS_RATES "520,585,650,780,866.7"
#define VHT80_3SS_RATES "585,975,1170,1300"
#define VHT80_4SS_RATES "1040,1560,1733.2"

#define VHT160_1SS_RATES "65,130,195,260,390,520,585,650,780,886.7"
#define VHT160_2SS_RATES "1040,1170,1300,1560,1733.3"
#define VHT160_3SS_RATES "1170,1950,2340,2600"
#define VHT160_4SS_RATES "2080,3120,3466.8"

/*802.11b, 802.11g, 802.11a, BasicDataTxRates for 2.4GHz, 5GHz*/
#define B2G_RATES "1,2,5.5,11"//Basic
#define WL_B_RATES "1,2,5.5,11"
#define WL_G_RATES "1,2,5.5,6,9,11,12,18,24,36,48,54"
#define B5G_RATES "6,12,24"//Basic
#define WL_A_RATES "6,9,12,18,24,36,48,54"

#endif
