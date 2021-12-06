#ifndef _LIBZYWLAN_H
#define _LIBZYWLAN_H
#include "zcfg_common.h"
#include "zywlan_comm.h"

#define CHAN_SCAN_TIME_WAITING 20
#define CHAN_SCAN_TIME_PATH "/tmp/wifiScanTime"
#define WIFI_MODULE_PATH "/usr/lib/wifi_module"

#define MAX_RATE_2G_ANT_1 150
#define MAX_RATE_2G_ANT_2 300
#define MAX_RATE_2G_ANT_3 450
#define MAX_RATE_5G_ANT_1 433
#define MAX_RATE_5G_ANT_2 867
#define MAX_RATE_5G_ANT_3 1300
#define MAX_RATE_5G_ANT_4 1733

#define DE_MAX_WIFI_CLIENTS 32
#define USA_MAX_WIFI_CLIENTS 64

enum {
	WL_1_ANTENNA = 1,
	WL_2_ANTENNA,
	WL_3_ANTENNA,
	WL_4_ANTENNA,

};

typedef enum {
	WLCMD_WPS_CANCEL=0,
	WLCMD_WPS_HWPBC,
	WLCMD_WPS_UPDATECFG,
	WLCMD_WPS_STAPIN,
	WLCMD_GET_STATUS,
	WLCMD_GET_LIST,
	WLCMD_GET_ASSOCLIST,
	WLCMD_GET_LOGLEVEL,
	WLCMD_SET_LOGLEVEL,
	WLCMD_RADIO_SWITCH,
	WLCMD_GET_TEST_MODE,
	WLCMD_SET_TEST_MODE,
	WLCMD_SET_STARTSCAN,
	WLCMD_GET_CHANNELRPT,
	WLCMD_GET_APRPT,
	WLCMD_SET_DISASSOCIATE,

#ifdef SHATEL_CUSTOMIZATION
	WLCMD_GET_POWERTABLE,
	WLCMD_SET_POWERTABLE,
#endif
#ifdef BUILD_SONIQ
	WLCMD_GET_INTF_INFO_GEN,
	WLCMD_GET_INTF_INFO_FAT,
#endif
#ifdef GUEST_SSID_WPS_PBC
	WLCMD_WPS_IPTV,
#endif
	WLCMD_STA_INFO,
	WLCMD_NONE
} WL_CMD_TYPE_t;

enum {
	WL_ST_NOT_INIT = 0,
	WL_ST_INIT,
	WL_ST_INIT_WAIT,
	WL_ST_INIT_FAIL,
	WL_ST_INIT_FIN,
	WL_ST_SETUP,
	WL_ST_SETUP_WAIT,
	WL_ST_SETUP_FAIL,
	WL_ST_SETUP_FIN,
	WL_ST_NO_SETUP,
	WL_ST_RADIO_UP,
	WL_ST_RADIO_DOWN,
	WL_ST_TEST_MODE
};

typedef enum {
	WLMOD_NONE,
	WLMOD_ESS,
	WLMOD_ADHOC
} WL_DEV_MODE;

#define CHECK_WLST_READY(a) \
	( a->status == WL_ST_SETUP_FIN || a->status == WL_ST_INIT_FIN \
	|| a->status == WL_ST_RADIO_UP || a->status == WL_ST_RADIO_DOWN )

#define CHECK_WLST_INIT(a) \
	( a->status != WL_ST_NOT_INIT && a->status != WL_ST_INIT_FAIL \
	&& a->status != WL_ST_TEST_MODE )

#define CHECK_WLST_INIT2(a) \
	( a->status != WL_ST_NOT_INIT && a->status != WL_ST_TEST_MODE )

#define CHECK_WLST_TESTMODE(a) ( a->status == WL_ST_TEST_MODE )

#define CHECK_WLST_FAIL(a) \
	( a->status == WL_ST_INIT_FAIL || a->status == WL_ST_SETUP_FAIL )

#define CHECK_WLST_FIN(a) \
	( a->status == WL_ST_INIT_FIN || a->status == WL_ST_SETUP_FIN \
	|| a->status == WL_ST_RADIO_UP || a->status == WL_ST_RADIO_DOWN )

#define CHECK_WLST_WAIT(a) \
	( a->status == WL_ST_INIT || a->status == WL_ST_INIT_WAIT \
	|| a->status == WL_ST_SETUP || a->status == WL_ST_SETUP_WAIT )

#define CHECK_WLST_NOT_INIT(a) ( a->status == WL_ST_NOT_INIT )


/* Station Filter */
enum{
	WL_STA_MAC_DISABLE=0,
	WL_STA_MAC_DENY,
	WL_STA_MAC_ALLOW,
};

#define WL_STA_MAC_FLT_MAX 25
typedef struct _wlStaMACFltEntry{
	char macAddress[18];
}wlStaMACFltEntry;

/* Channel scan */
struct ChSpec{
	unsigned short chanspec;
	unsigned short channel;
	unsigned int bw;
	unsigned short band;
	int sb;
};
struct ChScanInfo{
	struct ChSpec chspec;
	unsigned char valid;
	int score;
};
struct ApInfo{
	char ifName[16];
	char SSID[101];
	char BSSID[20];
	int Band;
	int Bandwidth;
	int RSSI;
	bool WPS;
	int Channel;
	unsigned int BeaconPeriod;
	unsigned int DTIMPeriod;
	short Noise;
	unsigned short Standards;
	unsigned short SecProtocol;
	unsigned short SecMangement;
	unsigned short SecEncryption;
	WL_DEV_MODE Mode;
	char BasicRates[257];
	char SupportedRates[257];
};

typedef enum {
	WLST_UNKNOW=0,
	WLST_INT,
	WLST_STR,
	WLST_PTR,
	WLST_TRAFFIC_INFO_STRUCT
} WL_ST_TYPE_t;

typedef struct wlStReq_t{
	const char *parmName;
	WL_ST_TYPE_t parmType;
	void *parmValue;
}wlStReq_s;

typedef struct wlLanEntry_t{
	char brObjPath[65];
	char objPath[65];
	char vIfname[33];
	char rIfname[33];
	char status[33];
	unsigned int vlanId;
}wlLanEntry_s;

typedef struct wlLanBr_t {
	char brIfName[33];
	int entryNum;
	char macAddr[18];
	wlLanEntry_s *lanEntry;
}wlLanBr_s;

typedef struct wlLanInfo_t{
	int lanNum;
	wlLanBr_s *lan;
#if 0 //def SUPPORT_WL_QTN_5G
	char _qtn_phy_if[32];
#endif
} wlLanInfo_s;

typedef struct wlcap_if_t{
	char ifname[31];
	//char address[MAC_ADDR_LEN];
} wlcap_if_s;


typedef struct wlcap_t{
	bool supportWme;
	bool supportWmeAPSD;
	bool supportMbss;
	bool supportAmpdu;
	bool supportAmsdu;
	bool supportWmf;
	bool supportRadioPwrsave;
	bool supportRxPwrsave;
	bool supportWDS;
	bool supportWPS;
	bool supportTXBF;
	bool supportATF;
	bool supportMU;
	bool support11ax;
	bool is_dhd; //only for broadcom
	int maxBss;
	wlcap_if_s wlif[WLAN_MAX_BSS];
} wlcap_s;

typedef struct wlinfo_t {
	char ifName[16];
	uint8_t band;
	int status;
	int phytype;//to identify interface is 2.4G or 5G
	unsigned char macaddr[MAC_ADDR_LEN];
	zyWlanRadio_t wlanRadio[WLAN_RADIO_NUM];
	zyWlanSsid_t wlanSsid[WLAN_MAX_BSS];
#ifdef ZYXEL_EASYMESH
	zyWlanEasyMesh_t wlanEasyMesh;
	zyWlanExtBssInfo_t wlanExtBssInfo[WLAN_MAX_BSS];
#endif
	wlcap_s cap;
	time_t csTime;
	struct ChScanInfo *ch_info;
	int chNum;
	struct ApInfo *ap_info;
	int apNum;
	time_t upApInfoTime;
#ifdef ZY_WIFI_WPSHWPBC_5G_FIRST
	int _wps_hw_pbc_delay;
#endif
	int which5gGuest;
}wlinfo_s;

typedef struct wl_sta_info_t{
	char ifName[16];
	char macaddr[18];
	int standard;
	unsigned int bandwidth;
	unsigned short authState;
	unsigned int lastTxRate;
	unsigned int lastRxRate;
	int rssi;
	int snr;
	int noise;
	unsigned int retransmit;
	unsigned int txPackets;
	unsigned long long txBytes;
	unsigned int rxPackets;
	unsigned long long rxBytes;
	unsigned int txErrors;
	unsigned int txRetrans;
	unsigned int txRetransFail;
	unsigned int retryCount;
	unsigned int multipleRetryCount;
	unsigned int LinkRate;
	unsigned int DownLinkRate;
	unsigned int UpLinkRate;
}wl_sta_info_s;

#ifdef BUILD_SONIQ
typedef enum {
   SONiQ_RPE_CAPAB_SUPPORTS_BSS_TRANS = 0,
   SONiQ_RPE_CAPAB_IS_HT,
   SONiQ_RPE_CAPAB_IS_VHT,
   SONiQ_RPE_CAPAB_SUPPORTS_MONITOR
}SONiQ_RPE_intf_bss_capab_t;

/*
 * 802.11n HT Capability IE
 */
typedef struct ieee80211_ie_htcap_t {
	unsigned char	hc_id;			/* element ID */
	unsigned char	hc_len;			/* length in bytes */
	unsigned char	hc_cap[2];			/* HT capabilities */
	unsigned char	hc_ampdu;		/* A-MPDU parameters */
	unsigned char	hc_mcsset[16];		/* supported MCS set */
	unsigned char	hc_extcap[2];		/* extended HT capabilities */
	unsigned char	hc_txbf[4];		/* txbf capabilities */
	unsigned char	hc_antenna;		/* antenna capabilities */
}ieee80211_ie_htcap_s;

/*
 * 802.11n HT Information IE
 */
typedef struct ieee80211_ie_htinfo_t {
	unsigned char	hi_id;			/* element ID */
	unsigned char	hi_len;			/* length in bytes */
	unsigned char	hi_ctrlchannel;	/* control channel */
	unsigned char	hi_byte1;		/* ht ie byte 1 */
	unsigned char	hi_byte2;		/* ht ie byte 2 */
	unsigned char	hi_byte3;		/* ht ie byte 3 */
	unsigned char	hi_byte4;		/* ht ie byte 4 */
	unsigned char	hi_byte5;		/* ht ie byte 5 */
	unsigned char	hi_basicmcsset[16];	/* basic MCS set */
} ieee80211_ie_htinfo_s;

/*
 * 802.11ac VHT Capabilities element
 */
typedef struct ieee80211_ie_vhtcap_t {
	unsigned char	vht_id;			/* element ID */
	unsigned char	vht_len;		/* length in bytes */
	unsigned char	vht_cap[4];		/* VHT capabilities info */
	unsigned char	vht_mcs_nss_set[8];	/* supported MSC and NSS set */
} ieee80211_ie_vhtcap_s;

/* VHT capabilities options */
/*
 * 802.11ac VHT Operation element
 */
typedef struct ieee80211_ie_vhtop_t {
	unsigned char	vhtop_id;		/* element ID */
	unsigned char	vhtop_len;		/* length in bytes */
	unsigned char	vhtop_info[3];		/* VHT Operation info */
	unsigned char	vhtop_bvhtmcs[2];	/* basic VHT MSC and NSS set */
} ieee80211_ie_vhtop_s;

typedef struct wl_intf_info_gen_t {
	unsigned char ifname[16];
	unsigned char ssid[101];
	unsigned char bssid[20];
	unsigned int mdid;
	unsigned char ssid_len;
	unsigned char ifname_size;
	unsigned char channel;
	unsigned char band;
	unsigned int opclass;
	unsigned char phytype;
	unsigned char drivercap;
	unsigned int capinfo;
	unsigned int beacon_interval;
	ieee80211_ie_htcap_s htcap;
	ieee80211_ie_htinfo_s htop;
	ieee80211_ie_vhtcap_s vhtcap;
	ieee80211_ie_vhtop_s vhtop;
} wl_intf_info_gen_s;

typedef struct  wl_intf_info_fat_t {
	unsigned char channel;
	unsigned char band;
	unsigned int avg_fat;
} wl_intf_info_fat_s;
#endif

typedef struct wlmodule_s {
	char name[33];
#ifdef BUILD_BRCM_HOSTAPD
	zcfgRet_t (*beWifi_Initial)(wlinfo_s **, int cnt, wlLanInfo_s *);
	zcfgRet_t (*beWifi_Setup)(wlinfo_s **, int cnt, wlLanInfo_s *);
#else
	zcfgRet_t (*beWifi_Initial)(wlinfo_s *, wlLanInfo_s *);
	zcfgRet_t (*beWifi_Setup)(wlinfo_s *, wlLanInfo_s *);
#endif
	zcfgRet_t (*beWifi_StatusUpdate)(wlinfo_s *, wlStReq_s *, int );
	zcfgRet_t (*beWifi_SetIfaceMacAddr)(wlinfo_s *, const unsigned char *);
	zcfgRet_t (*beWifi_UpdateLanInfo)(wlinfo_s **, int , wlLanInfo_s *);
	//Channel Scan
	zcfgRet_t (*beWifi_ChannelScan)(wlinfo_s *);
	zcfgRet_t (*beWifi_GetChanScanRpt)(wlinfo_s *, struct ChScanInfo **, int *, struct ApInfo **, int *);
	//zcfgRet_t (*beWifi_GetChanScanApRpt)(wlinfo_s *, struct ApInfo **, int *);
	//WDS
	zcfgRet_t (*beWifi_WDSSetup)(wlinfo_s *);
	//WPS
#ifdef BUILD_BRCM_HOSTAPD
	zcfgRet_t (*beWifi_WPSSetup)(wlinfo_s **,const char*, int cnt);
#else
	zcfgRet_t (*beWifi_WPSSetup)(wlinfo_s *,const char*);
#endif
	zcfgRet_t (*beWifi_StartWpsSWPBC)(wlinfo_s *);
	zcfgRet_t (*beWifi_StartWpsHWPBC)(wlinfo_s **, int , const char *);
	zcfgRet_t (*beWifi_StartWpsStaPin)(wlinfo_s *, const char *);
	zcfgRet_t (*beWifi_WPSActionCancel)(wlinfo_s *);
#ifdef BUILD_BRCM_HOSTAPD
	zcfgRet_t (*beWifi_WPSUpdateConfig)(wlinfo_s **, int cnt, int update_idx, bool *, bool);
#else
	zcfgRet_t (*beWifi_WPSUpdateConfig)(wlinfo_s *, bool *);
#endif
	//MAC address authentication
	zcfgRet_t (*beWifi_StationFilter)(wlinfo_s *, const char*);
	zcfgRet_t (*beWifi_GetAssocDevList)(wlinfo_s *, int, wl_sta_info_s **, int *);

#ifdef BUILD_SONIQ /* #36467, MAC filter with SONiQ, cpwang, 2017-04-18 10:56:46 */
	zcfgRet_t (*beWifi_BsaMacFilter)(const char*, const char, const char*);
#endif /* #36467, MAC filter with SONiQ, cpwang, 2017-04-18 10:56:46 */

	zcfgRet_t (*beWifi_ConfigTestMode)(wlinfo_s *, int);
	//Disassociate STA
	zcfgRet_t (*beWifi_DisassociateSTA)(const char*, const char*);
#ifdef BUILD_SONIQ
	zcfgRet_t (*beWifi_GetGenIntfInfo)(const char*, int, wl_intf_info_gen_s *);
	zcfgRet_t (*beWifi_GetFatIntfInfo)(const char*, int, unsigned int *);
#endif

	zcfgRet_t (*beWifi_Destory)();
#ifdef PRESET_BACKHAUL_SETTING
	zcfgRet_t (*beWifi_EnablePresetSSID)(const char*, int);
#endif
#ifdef BUILD_SONIQ
	zcfgRet_t (*beWifi_EnableSoniqEvt)(bool);
#endif
#if defined(BUILD_SONIQ) || defined(ZYXEL_EASYMESH)
	zcfgRet_t (*beWifi_GetVlanID)(int, int, int*);
#endif
#ifdef GUEST_SSID_WPS_PBC
	zcfgRet_t (*beWifi_StartWpsIptvPBC)(wlinfo_s *, const char *);
#endif
}wlmodule_t;

#ifdef ZY_WIFI_EVENT_HANDLER
typedef enum {
	WL_EVT_NONE,
	WL_EVT_ASSOC,
	WL_EVT_DEASSOC,
	WL_EVT_REASSOC,
	WL_EVT_WPSDONE,
	WL_EVT_WPSUPAPCFG,
	WL_EVT_KEYFAIL
}WL_EVT_TYPE_t;

typedef struct wlevt_msg_s {
	char ifName[16]; //radio interface
	char mbss_ifName[16]; //bss interface
	WL_EVT_TYPE_t evt_type;
	char buffer[256];
}wlevt_msg_t;

typedef struct wlevthdl_s {
	//WLEVENT
	zcfgRet_t (*beWifi_EvtInit)(int *);
	zcfgRet_t (*beWifi_EvtMsgReceive)(int, wlevt_msg_t **);
	zcfgRet_t (*beWifi_EvtMsgHandle)(wlinfo_s *, wlevt_msg_t *);
	int sock;
	bool is_die;
}wlevthdl_t;

typedef struct wlEvthdlList_s {
	bool headFlag;
	struct wlEvthdlList_s *prev;
	struct wlEvthdlList_s *next;
	char name[33];
	wlevthdl_t *wl_evt;
}wlEvthdlList_t;
#endif

typedef struct wlModuleList_s {
	bool headFlag;
	struct wlModuleList_s *prev;
	struct wlModuleList_s *next;
	wlmodule_t *wl_handle;
	void *dl_handle;
}wlModuleList_t;

typedef struct wlMapList_s {
	bool headFlag;
	struct wlMapList_s *prev;
	struct wlMapList_s *next;
	wlinfo_s *wl_info;
	wlmodule_t *wl_handle;
#ifdef ZY_WIFI_CONFIGTHREAD
	int in_config_thread;
#endif
}wlMapList_t;

typedef enum {
	W_NOTICE = (1 << 1),
	W_ERROR = (1 << 2),
	W_INFO = (1 << 3),
	W_WARRING = (1 << 4),
	W_ALERT = (1 << 5),
	W_DEBUG = (1 << 6),
	W_NONE = 0
} W_LEVEL_t;

typedef int (*W_PRINT_FN)(W_LEVEL_t, const char*, const char*, unsigned int, const char*, ...);

typedef struct wifiModuleInit_s{
	zcfgRet_t (*add_wl_module)(wlmodule_t *, void *);
	zcfgRet_t (*add_wl_info)(wlinfo_s * ,const char *);
#ifdef ZY_WIFI_EVENT_HANDLER
	zcfgRet_t (*add_wl_event)(char *, wlevthdl_t *);
#endif
	W_PRINT_FN w_print;
}wifiModuleInit_t;

typedef struct wlTrafficInfo_s {
	unsigned int ByteSend;
	unsigned int ByteRecv;
	unsigned int PktSendData;
	unsigned int PktSendError;
	unsigned int PktSendDrop;
	unsigned int PktRecvData;
	unsigned int PktRecvError;
	unsigned int PktRecvDrop;
}wlTrafficInfo_t;

#define IEEE80211_WLPROTO_11B	0x0001
#define IEEE80211_WLPROTO_11G	0x0002
#define IEEE80211_WLPROTO_11A	0x0004
#define IEEE80211_WLPROTO_11N	0x0008
#define IEEE80211_WLPROTO_11AC	0x0010
#define IEEE80211_WLPROTO_11AX	0x0020

#define WLSEC_PROTO_NONE	0x0000
#define WLSEC_PROTO_WPA		0x0001
#define WLSEC_PROTO_WPA2	0x0002

#define WLSEC_MGMT_NONE	0x0000
#define WLSEC_MGMT_EAP	0x0001
#define WLSEC_MGMT_PSK	0x0002
#define WLSEC_MGMT_WEP	0x0004

#define WLSEC_ENC_NONE	0x0000
#define WLSEC_ENC_TKIP	0x0001
#define WLSEC_ENC_CCMP	0x0002

#ifdef ZY_WIFI_WPSHWPBC_5G_FIRST
#define WPS_HWPBC_DELAY 15 //sec
#endif

#ifdef BUILD_SONIQ
typedef struct opclass_s {
	unsigned int opclass;
	unsigned char band;
	unsigned int CurBandwidth;
	unsigned int sideband;
	unsigned char chanlist_len;
	unsigned char *chanlist;
}opclass_t;
#endif

#endif
