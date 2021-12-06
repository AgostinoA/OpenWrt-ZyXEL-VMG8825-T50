
/* Flag1 */
#define HIDE_VOIP						(1 << 0)
#define HIDE_DECT						(1 << 1)
#define HIDE_ETH_WAN_TAB				(1 << 2)
#define HIDE_WLAN_PASSPHRASE			(1 << 3) 
#define SHOW_CONFIG_VOIP_COMFORT_NOISE	(1 << 4) //16 , add for SuperOnLine (SOL) project customize, they want to config silence suppression and comfortnoise separately , yushiuan , 2015/02/10.
#define SHOW_ROMD_TAB					(1 << 5)
#define SHOW_USA_PRODUCT_PAGE			(1 << 6)
#define SHOW_RSA_PAGE					(1 << 7)
#define VOICE_CODEC_G729_SUPPORT		(1 << 8)
#define VOICE_CODEC_PRI_G729_FIRST		(1 << 9)
#define HIDE_TR064						(1 << 10)
#define SHOW_DDNS_myzyxel_th			(1 << 11)
#define HIDE_VD_PAGE					(1 << 12)
#define HIDE_VOICE_SRTP					(1 << 13)
#define HIDE_VOICE_IVR					(1 << 14)
#define DEDICATED_ETH_WAN				(1 << 15)
#define SHOW_NOT_USE_OFTEN_VOIP_SETTING	(1 << 16) //65536 , yushiuan add 2015/12/08 , add for hide some function which not used often for voip related page
#define SINGLE_LOGIN					(1 << 17)
#define ELISA_PAGE_CUSTOMIZE			(1 << 18) //262144
#define HIDE_WLAN_WDS					(1 << 19)
#define HIDE_WLAN_CHANNEL_SCAN			(1 << 20)
#define DSL_BONDING						(1 << 21)
#define TURKEY_LOGO						(1 << 22)
#define VOIP_SIP_PHONE_MAPPING_BY_STD_PHY_REFERENCE_LIST		(1<<23) // 8388608
#define HIDE_DSL                                                        (1<<24) // 16777216
#define VOICE_CODEC_G726_SPECIAL_CASE	(1 << 25) //33554432, Michael.20161005.001: add for (a)supporting G726-32 ONLY first now and (b)reserved for some other special G726 codec case(s) in the future.
#define HIDE_WLAN_ENABLE                (1 << 26) //67108864
#define HIDE_WLAN_CHANNEL_1213          (1 << 27) // 134217728
#define HIDE_WLAN_WEP                   (1 << 28) //For Oi product, WEP setting is needed.
#define SHOW_DHCPv6S_PAGE               (1 << 29) //For Oi product
#define OI_HOTSPOT_HIDE                 (1 << 30) //For Oi product, when hotspot enable WLAN guest#3 will only show if user login as 'supervisor'
//!!!!!!NOTE!!!!!! The Bit (1 << 31) is RESERVED and is BETTER to be Kept as Zero(0) to prevent this 'Flag1' from becoming the Strange & Special value '0x7FFFFFFF' after doing Reset-to-Default!!!
/* End of Flag1*/

/* Flag3 */
#define TR069_PAGE_READ_ONLY			(1 << 0)
#define SHOW_ONU_MODE					(1 << 1)
#define LOGIN_PAGE_URL_MAIN_HTML		(1 << 2)
#define SHOW_USB_PRINTER				(1 << 3)
#define HIDE_WWAN						(1 << 4)
#define HIDE_WLAN						(1 << 5)
#define HIDE_USB						(1 << 6)
/* End of Flag3*/

/*WIFI GUI compile flag, used to AND ZYXEL_WEB_GUI_WIFI_SHOW flag for 32 bits. Every bit means a switch to show or hide feature on webgui*/
#define WIFI_GUI_SHOW_MU_MIMO_24G		(1 << 0)
#define WIFI_GUI_SHOW_MU_MIMO_5G		(1 << 1)
/* End of WIFI GUI compile flag */

/* FlagVoIP1 */
#define SHOW_VOIP_TELEPHONY_PROF_CUSTOM_MENU_FXS_CLID_SIG_PROTO_TYPE        (1 << 0) //1, Jake, 2019-07-11, Caller ID Signal Type
#define SHOW_VOIP_TELEPHONY_PROF_CUSTOM_MENU_FXS_CLID_MODE                  (1 << 1) //2, Jake, 2019-07-19, Caller ID Mode
#define HIDE_VOIP_SIP_OVER_TLS        (1 << 2) //4, Steve, 2019-07-22, SIP over TLS
