#ifndef ZCFG_TR98_COMMON_H
#define ZCFG_TR98_COMMON_H

#define IS_SEQNUM_RIGHT(seqnum) ((seqnum >= e_TR98_START) && (seqnum <= e_TR98_LAST))
#define ARRAY_SEQNUM(seqnum) (seqnum-e_TR98_START)

enum {
	PARMATTR_TR98 = 1,
	PARMATTR_TR181 = (1 << 1)
};

// Tr98 sequence num
typedef enum {
	e_TR98_START = 100,
	e_TR98_IGD = e_TR98_START,
#ifdef CONFIG_PACKAGE_ZyIMS
	e_TR98_SERVICE                             ,
	e_TR98_VOICE_SRV                           ,
	e_TR98_VOICE_CAPB                          ,
	e_TR98_VOICE_CAPB_SIP                      ,
//	e_TR98_VOICE_CAPB_MGCP                     ,
//	e_TR98_VOICE_CAPB_H323                     ,
	e_TR98_VOICE_CAPB_CODEC                    ,
	e_TR98_VOICE_PROF                          ,
//	e_TR98_VOICE_PROF_SRV_PRO_INFO             ,
	e_TR98_VOICE_PROF_SIP                      ,
//	e_TR98_VOICE_PROF_SIP_SUBSCRIBE_OBJ        ,
//	e_TR98_VOICE_PROF_SIP_RESP_MAP_OBJ         ,
	e_TR98_VOICE_PROF_RTP                      ,
	e_TR98_VOICE_PROF_RTP_RTCP                 ,
	e_TR98_VOICE_PROF_RTP_SRTP                 ,
//	e_TR98_VOICE_PROF_RTP_REDUNDANCY           ,
	e_TR98_VOICE_PROF_NUM_PLAN                 ,
	e_TR98_VOICE_PROF_NUM_PLAN_PREFIX_INFO     ,
//	e_TR98_VOICE_PROF_TONE                     ,
//	e_TR98_VOICE_PROF_TONE_EVENT               ,
//	e_TR98_VOICE_PROF_TONE_DESCRIPTION         ,
//	e_TR98_VOICE_PROF_TONE_PATTERN             ,
	e_TR98_VOICE_PROF_FAX_T38                  ,
	e_TR98_VOICE_LINE                          ,
	e_TR98_VOICE_LINE_SIP                      ,
//	e_TR98_VOICE_LINE_SIP_EVENT_SUBS           ,
//	e_TR98_VOICE_LINE_RINGER                   ,
//	e_TR98_VOICE_LINE_RINGER_EVENT             ,
//	e_TR98_VOICE_LINE_RINGER_DESCRIPTION       ,
//	e_TR98_VOICE_LINE_RINGER_PATTERN           ,
	e_TR98_VOICE_LINE_CALLING_FEATURE          ,
	e_TR98_VOICE_LINE_PROCESSING               ,
	e_TR98_VOICE_LINE_CODEC                    ,
	e_TR98_VOICE_LINE_CODEC_LIST               ,
//	e_TR98_VOICE_LINE_SESSION                  ,
	e_TR98_VOICE_LINE_STATS                    ,
	e_TR98_VOICE_PHY_INTF                      ,
//	e_TR98_VOICE_PSTN                          ,
	e_TR98_VOICE_COMMON                        ,
//	e_TR98_VOICE_PHONE_BOOK                    ,
//	e_TR98_VOICE_FXO                           ,
//	e_TR98_VOICE_FXO_PORT                      ,
#endif
#ifdef AVAST_AGENT_PACKAGE
	e_TR98_ISP_SERVICE             ,
#endif
	e_TR98_CAPB                    ,
	e_TR98_PERF_DIAG               ,
	e_TR98_DEV_INFO                ,
	e_TR98_MemoryStatus            ,
	e_TR98_VEND_CONF_FILE          ,
	e_TR98_DEV_INFO_PS_STAT         ,
	e_TR98_DEV_INFO_PS_STAT_PS      ,
//	e_TR98_DEV_CONF                ,
	e_TR98_MGMT_SRV                ,
	e_TR98_MGAB_DEV                ,
	e_TR98_TIME                    ,
//	e_TR98_USR_INTF                ,
//	e_TR98_CAPT_PORTAL             ,
	e_TR98_L3_FWD                  ,
	e_TR98_FWD                     ,
#ifdef L3IPV6FWD
	e_TR98_IPV6FWD                 ,
#endif
	e_TR98_L2_BR                   ,
	e_TR98_BR                      ,
	e_TR98_PORT                    ,
	e_TR98_VLAN                    ,
	e_TR98_FILTER                  ,
	e_TR98_MARK                    ,
	e_TR98_AVAI_INTF               ,
	e_TR98_QUE_MGMT                ,
	e_TR98_CLS                     ,
//	e_TR98_APP                     ,
//	e_TR98_FLOW                    ,
	e_TR98_POLICER                 ,
	e_TR98_QUE                     ,
	e_TR98_SHAPER                  ,
//	e_TR98_QUE_STAT                ,
	e_TR98_LAN_CONF_SEC            ,
	e_TR98_IP_PING_DIAG            ,
	e_TR98_TRA_RT_DIAG             ,
	e_TR98_RT_HOP                  ,
	e_TR98_DL_DIAG                 ,
	e_TR98_UL_DIAG                 ,
	e_TR98_UDP_ECHO_CONF           ,
	e_TR98_UDP_ECHO_DIAG           ,
	e_TR98_UDP_ECHO_DIAG_PAK_RST,
	e_TR98_LAN_DEV                 ,
	e_TR98_LAN_HOST_CONF_MGMT      ,
	e_TR98_IP_INTF                 ,
#ifdef LANIPALIAS
	e_TR98_IP_ALIAS                ,
#endif
#ifdef IPV6INTERFACE_PROFILE
	e_TR98_IP_INTF_IPV6ADDR        ,
	e_TR98_IP_INTF_IPV6PREFIX      ,
#endif
#ifdef ROUTERADVERTISEMENT_PROFILE
	e_TR98_IP_INTF_ROUTERADVER     ,
#endif
#ifdef IPV6SERVER_PROFILE
	e_TR98_IP_INTF_DHCPV6SRV       ,
#endif
	e_TR98_DHCP_STATIC_ADDR        ,
	e_TR98_DHCP_OPT                ,
#ifdef ZyXEL_DHCP_OPTION125
	e_TR98_VENDOR_SPECIFIC,
	e_TR98_VENDOR_SPECIFIC_PROF,	
#endif	
	e_TR98_DHCP_COND_SERVPOOL      ,
	e_TR98_SERVPOOL_DHCP_STATICADDR,
	e_TR98_SERVPOOL_DHCP_OPT       ,
	e_TR98_LAN_ETH_INTF_CONF       ,
	e_TR98_LAN_ETH_INTF_CONF_STAT  ,
//	e_TR98_LAN_USB_INTF_CONF       ,
//	e_TR98_LAN_USB_INTF_CONF_STAT  ,
	e_TR98_LAN_DEV_WLAN_CFG        ,
	e_TR98_WLAN_CFG_STAT           ,
	e_TR98_WPS                     ,
//	e_TR98_REG                     ,
	e_TR98_ASSOC_DEV               ,
	e_TR98_ASSOC_DEV_STAT          ,
	e_TR98_WEP_KEY                 ,
	e_TR98_PSK                     ,
#ifdef ZYXEL_SUPPORT_8021X
	e_TR98_RADIUS                  ,
#endif
//	e_TR98_AP_WMM_PARAM            ,
//	e_TR98_STA_WMM_PARAM           ,
	e_TR98_HOSTS                   ,
	e_TR98_HOST                    ,
#ifdef ONECONNECT
	e_TR98_ONECONNECT_EXT          ,
#endif
	e_TR98_NEIBOR_WIFI_DIAG        ,
	e_TR98_NEIBOR_WIFI_DIAG_RESULT ,
	e_TR98_LAN_INTF                ,
//	e_TR98_LAN_INTF_ETH_INTF_CONF  ,
//	e_TR98_USB_INTF_CONF           ,
//	e_TR98_LAN_INTF_WLAN_CFG       ,
	e_TR98_WAN_DEV                 ,
	e_TR98_WAN_COMM_INTF_CONF      ,
//	e_TR98_WAN_COMM_INTF_CONNECT   ,
	e_TR98_WAN_DSL_INTF_CONF       ,
	e_TR98_WAN_DSL_INTF_TEST_PARAM ,
	e_TR98_WAN_DSL_INTF_CONF_STAT  ,
	e_TR98_TTL                     ,
	e_TR98_ST                      ,
//	e_TR98_LST_SHOWTIME            ,
	e_TR98_CURRENT_DAY             ,
//	e_TR98_QTR_HR                  ,
	e_TR98_WAN_ETH_INTF_CONF       ,
	e_TR98_WAN_ETH_INTF_CONF_STAT  ,
	e_TR98_WAN_DSL_DIAG            ,
	e_TR98_WAN_CONN_DEV            ,
	e_TR98_WAN_DSL_LINK_CONF       ,
	e_TR98_WAN_ATM_F5_LO_DIAG      ,
	e_TR98_WAN_ATM_F4_LO_DIAG      ,
	e_TR98_WAN_PTM_LINK_CONF       ,
	e_TR98_WAN_PTM_LINK_CONF_STAT  ,
	e_TR98_WAN_ETH_LINK_CONF       ,
//	e_TR98_WAN_POTS_LINK_CONF      ,
	e_TR98_WAN_IP_CONN             ,
	e_TR98_WAN_IP_CONN_MLD		   , 
	e_TR98_DHCP_CLIENT             ,
	e_TR98_SENT_DHCP_OPT           ,
	e_TR98_REQ_DHCP_OPT            ,
	e_TR98_WAN_IP_PORT_MAP         ,
	e_TR98_WAN_IP_PORT_TRIGGER     ,
	e_TR98_WAN_IP_ADDR_MAPPING     ,
	e_TR98_WAN_IP_CONN_STAT        ,
#ifdef IPV6INTERFACE_PROFILE
	e_TR98_WAN_IP_CONN_IPV6ADDR    ,
	e_TR98_WAN_IP_CONN_IPV6PREFIX	 ,
#endif
#ifdef DHCPV6CLIENT_PROFILE
	e_TR98_WAN_IP_CONN_DHCPV6CLIENT,
#endif
#ifdef IPV6RD_PROFILE
	e_TR98_WAN_IP_CONN_IPV6RD	     ,
#endif
#ifdef ROUTEINFO_INTERFACE
	e_TR98_WAN_IP_CONN_ROUTEINFO	 ,
#endif
	e_TR98_WAN_PPP_CONN            ,
	e_TR98_WAN_PPP_PORT_MAP        ,
	e_TR98_WAN_PPP_PORT_TRIGGER    ,
	e_TR98_WAN_PPP_ADDR_MAPPING    ,
	e_TR98_WAN_PPP_CONN_STAT       ,
	e_TR98_WAN_PPP_CONN_MLD		   ,
#ifdef IPV6INTERFACE_PROFILE
	e_TR98_WAN_PPP_CONN_IPV6ADDR    ,
	e_TR98_WAN_PPP_CONN_IPV6PREFIX  ,
#endif
#ifdef DHCPV6CLIENT_PROFILE
	e_TR98_WAN_PPP_CONN_DHCPV6CLIENT,
#endif
#ifdef IPV6RD_PROFILE
	e_TR98_WAN_PPP_CONN_IPV6RD      ,
#endif
	e_TR98_WWAN_INTERFACE_CONFIG ,
	e_TR98_WWAN_INTERFACE_CONFIG_STATUS,
	e_TR98_WWAN_EMAIL_CONFIG ,
#ifdef CONFIG_XPON_SUPPORT
	e_TR98_WAN_PON_INTF_CONF       ,
	e_TR98_WAN_PON_INTF_CONF_STAT  ,
#endif
	e_TR98_FIREWALL                ,
	e_TR98_FIREWALL_LEVEL          ,
	e_TR98_FIREWALL_CHAIN          ,
	e_TR98_FIREWALL_CHAIN_RULE     ,
	e_TR98_STD_UPNP		           ,
	e_TR98_STD_UPNP_DEV		       ,
#ifdef ZYXEL_IPV6SPEC
	e_TR98_IPV6SPEC					,
	e_TR98_IPV6_PPP					,
	e_TR98_IPV6_PPP_INTF			,
	e_TR98_IPV6_PPP_INTF_IPV6CP		,
	e_TR98_IPV6_IP					,
	e_TR98_IPV6_IP_INTF				,
	e_TR98_IPV6_IP_INTF_IPV6ADDR	,
	e_TR98_IPV6_IP_INTF_IPV6PREFIX	,
	e_TR98_ROUTING					,
	e_TR98_ROUTER					,
	e_TR98_ROUTER_IPV6FWD			,
	e_TR98_ROUTEINFO				,
	e_TR98_ROUTEINFO_INTF			,
	e_TR98_ND						,
	e_TR98_ND_INTF					,
	e_TR98_RTADR					,
	e_TR98_RTADR_INTF				,
	e_TR98_RTADR_INTF_OPT			,
	e_TR98_IPV6_HOSTS				,
	e_TR98_IPV6_HOSTS_HOST			,
	e_TR98_IPV6_HOSTS_IPV6ADR		,
	e_TR98_IPV6_DNS					,
	e_TR98_IPV6_DNS_CLIENT			,
	e_TR98_IPV6_DNS_SERVER			,
	e_TR98_IPV6_DNS_RELAY			,
	e_TR98_IPV6_DNS_RELAYFWD		,
	e_TR98_IPV6_DHCPV6				,
	e_TR98_IPV6_DHCPV6_CLIENT		,
	e_TR98_IPV6_DHCPV6_CLIENT_SRV	,
	e_TR98_IPV6_DHCPV6_CLIENT_SENT	,
	e_TR98_IPV6_DHCPV6_CLIENT_RCV	,
	e_TR98_IPV6_DHCPV6_SERVER		,
	e_TR98_IPV6_DHCPV6_SERVER_POOL	,
	e_TR98_IPV6_DHCPV6_SERVER_CNT	,
	e_TR98_IPV6_DHCPV6_SERVER_CNT_V6ADDR	,
	e_TR98_IPV6_DHCPV6_SERVER_CNT_V6PREFIX	,
	e_TR98_IPV6_DHCPV6_SERVER_CNT_OPT	,
	e_TR98_IPV6_DHCPV6_SERVER_OPT	,
#endif
#ifdef ZYXEL_GRE_SUPPORT
	e_TR98_GRE              		,
	e_TR98_GRE_TUNNEL				,
	e_TR98_GRE_TUNNEL_STATS			,
#endif
#if ZYXEL_EXT
	e_TR98_ZYXEL_EXT               ,
#ifdef ZYXEL_LANDING_PAGE_FEATURE
	e_TR98_LANDING_PAGE 		   ,
#endif
	e_TR98_FEATURE_FLAG 		   ,
	e_TR98_DNS                     ,
	e_TR98_DNS_RT_ENTRY            ,
	e_TR98_DNS_ENTRY			   ,
	e_TR98_D_DNS                   ,
#ifdef ZCFG_TR64
	e_TR98_TR064				   ,
#endif
	e_TR98_VLAN_GROUP			   ,
	e_TR98_EMAIL_NOTIFY			   ,
	e_TR98_EMAIL_SERVICE		   ,
	e_TR98_EMAIL_EVENT_CFG		   ,
	e_TR98_SYS_INFO				   ,
#ifdef ZYXEL_SFP_MODULE_SUPPORT
    e_TR98_GPON_INFO               ,
#endif	
	e_TR98_SNMP					   ,
	e_TR98_SNMP_TRAP			   ,
	e_TR98_SCHEDULE                ,
	e_TR98_REMO_MGMT               ,
	e_TR98_REMO_SRV                ,
	e_TR98_SP_REMO_SRV               ,
	e_TR98_REMO_TRUSTDOMAIN        ,
	e_TR98_SP_TRUSTDOMAIN        ,
	e_TR98_IEEE8021AG              ,
#ifdef ZYXEL_ETHOAM_TMSCTL
	e_TR98_IEEE8023AH              ,
#endif
	e_TR98_SAMBA		           ,
	e_TR98_UPNP		           ,
	e_TR98_IGMP                    ,
#ifdef ZYXEL_TR69_DATA_USAGE
	e_TR98_DATA_USAGE                   ,
	e_TR98_DATA_USAGE_LAN               ,
	e_TR98_DATA_USAGE_WAN               ,
#endif
#if defined(SUNRISE_RANDOM_PASSWORD) || defined(SOL_TR69_LOGINACCOUNT) || defined(ZYXEL_SUPPORT_TR98_LOGIN_ACCOUNT)
	e_TR98_LOG_CFG           		 ,
	e_TR98_LOG_CFG_GP           	 ,
	e_TR98_LOG_CFG_GP_ACCOUNT       ,
#endif
	e_TR98_LOG_SETTING             ,
	e_TR98_LOG_CLASSIFY            ,
	e_TR98_LOG_CATEGORY	     ,
	e_TR98_MACFILTER				,
	e_TR98_MACFILTER_WHITELIST		,
	e_TR98_PAREN_CTL			   ,
	e_TR98_PAREN_CTL_PROF 		   ,
	e_TR98_SEC			 		   ,
	e_TR98_SEC_CERT		 		   ,
	e_TR98_GUI_CUSTOMIZATION		,
#ifdef ONECONNECT
	e_TR98_ONECONNECT,
	e_TR98_ONECONNECT_SPEEDTESTINFO,
#endif
#ifdef ZYXEL_AP_STEERING
	e_TR98_AP_STEERING              ,
#endif 
#ifdef PROXIMITY_SENSOR_SUPPORT
	e_TR98_PROXIMITY_SENSOR         ,
#endif
#endif
#if OBSOLETED
#else
//	e_TR98_WAN_DSL_CONN_MGMT       ,
//	e_TR98_WAN_DSL_CONN_SRVC       ,
#endif
#ifdef ZyXEL_IPP_PRINTSERVER
	e_TR98_PRINT_SERVER,
#endif
#ifdef ZYXEL_EASYMESH
	e_TR98_EasyMesh	,
#endif
#ifdef BUILD_SONIQ
	e_TR98_Qsteer		,
#endif	
#ifdef ZYXEL_ONESSID
       e_TR98_ONESSID          ,
#endif
#ifdef ZYXEL_SFP_POWER_MGMT
       e_TR98_SFP_MGMT          ,
#endif
	e_TR98_LAST
} zcfg98sn_t;
#endif
