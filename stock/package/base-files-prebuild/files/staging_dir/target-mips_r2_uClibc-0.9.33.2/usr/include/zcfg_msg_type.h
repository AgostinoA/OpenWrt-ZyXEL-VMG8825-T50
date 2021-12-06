/*******************************************************************************

    Please read this before change message type
        1. Do _NOT_ use any compile flag here.
        2. The messages are grouped by module. Please find your module to add
           new message. If not found, then just create new module.
        3. Each module can define 1000 messages.
        4. Message attribute is reserved in the first 8 bits, i.e., 0xFF00 0000.
        5. Message naming rule: ZCFG_MSG_<MODULE NAME>_<MSG TYPE>
            ex, ZCFG_MSG_WAN_CONNCTION_READY, where 'WAN' is the module name and
                'CONNCTION_READY' is the message type.
        6. Message numbering rule: find a unique number in your module.
        7. put comment at the tail of line.

    !!! Please keep texts aligned and nice look !!!

*******************************************************************************/
#ifndef _ZCFG_MSG_TYPE_H_
#define _ZCFG_MSG_TYPE_H_

/*******************************************************************************

    Message attribute

*******************************************************************************/
#define ZCFG_NO_WAIT_REPLY                              (1 << 31)
#define ZCFG_BLOCK_MODE_CONFIG_APPLY                    (1 << 30)
#define ZCFG_PARTIAL_OBJECT_SET                         (1 << 29)
#define ZCFG_MSG_RPC_ADDITIONS                          (1 << 28)

#define ZCFG_MSG_ADDITIONAL_BITS	(ZCFG_NO_WAIT_REPLY | ZCFG_BLOCK_MODE_CONFIG_APPLY | ZCFG_PARTIAL_OBJECT_SET | ZCFG_MSG_RPC_ADDITIONS)

#define ZCFG_MSG_TYPE(_t_)          (_t_ & 0x00FFffFF)
#define ZCFG_MSG_WITH_REPLY(_t_)    (!(_t_ & ZCFG_NO_WAIT_REPLY))
#define ZCFG_MSG_WITH_REPLY_S(_t_)  (ZCFG_MSG_WITH_REPLY(_t_) ? "with" : "without")

/*******************************************************************************

    Messgae type

*******************************************************************************/

/*------------------------------------------------------------------------------

    General
        range  : 0 - 999
        prefix : REQUEST_
                 RESPONSE_
                 ZCFG_MSG_<ACTION>_

------------------------------------------------------------------------------*/
#define REQUEST_GET_NEXT_OBJ                               1
#define REQUEST_GET_OBJ                                    2
#define REQUEST_SET_OBJ                                    3
#define REQUEST_SET_MULTI_OBJ                              4
#define REQUEST_ADD_INSTANCE                               5
#define REQUEST_DEL_INSTANCE                               6
#define REQUEST_FIRMWARE_UPGRADE                           7
#define REQUEST_RESTORE_DEFAULT                            8
#define REQUEST_GET_NEXT_SUB                               9
#define REQUEST_GET_PARAM_ATTR                            10
#define REQUEST_SET_PARAM_ATTR                            11
#define REQUEST_SET_WITHOUT_APPLY                         12
#define REQUEST_ROMD_UPGRADE                              13
#define REQUEST_GET_OBJ_WITHOUT_UPDATE                    14
#define REQUEST_CONFIG_BACKUP                             15
#define REQUEST_GET_NEXT_OBJ_WITHOUT_UPDATE               16
#define REQUEST_GET_NEXT_SUB_WITHOUT_UPDATE               17
#define REQUEST_REINIT_MACLESS_PROVISIONING               18
#define REQUEST_FIRMWARE_UPGRADE_CHK                      19
#define REQUEST_RESTORE_DEFAULT_CHK	                      20
#define REQUEST_FIRMWARE_WRITE_ONLY                       21
#define REQUEST_GET_WHOLE_OBJ_BY_NAME                     22
#define REQUEST_SET_WHOLE_OBJ_BY_NAME                     23
#define REQUEST_FIRMWARE_UPGRADE_FWUR                     24

#define ZCFG_MSG_SP_DOMAIN_TIMER_START                (81 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_SP_DOMAIN_TIME_OUT                   (82 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_SFP_POWER_TIMER_START		      (83 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_SFP_POWER_TIME_OUT                  (84 | ZCFG_NO_WAIT_REPLY)

#define RESPONSE_GET_SUCCESS                            (100 | ZCFG_NO_WAIT_REPLY)
#define RESPONSE_GET_EMPTY                              (101 | ZCFG_NO_WAIT_REPLY)
#define RESPONSE_GET_FAIL                               (102 | ZCFG_NO_WAIT_REPLY)
#define RESPONSE_SUCCESS                                (103 | ZCFG_NO_WAIT_REPLY)
#define RESPONSE_FAIL                                   (104 | ZCFG_NO_WAIT_REPLY)
#define RESPONSE_WRITE_OBJ_SUCCESS                      (105 | ZCFG_NO_WAIT_REPLY)
#define RESPONSE_WRITE_OBJ_FAIL                         (106 | ZCFG_NO_WAIT_REPLY)
#define RESPONSE_NO_MORE_INSTANCE                       (107 | ZCFG_NO_WAIT_REPLY)

#define ZCFG_MSG_DELAY_APPLY                             200
#define ZCFG_MSG_RE_APPLY                                201
#define ZCFG_MSG_UPNP_PORTMAP_GET                        202
#define ZCFG_MSG_GET_TR98_ALL_IGD_NAMES                  203
#define ZCFG_MSG_MCPCTL	                                 204
#define ZCFG_MSG_CLEAN_ROMD	                             205
#define ZCFG_MSG_SAVE_ROMD	                             206
#define ZCFG_MSG_FAKEROOT_COMMAND	                    (207 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_FAKEROOT_SYS_ATSH	                     208  /* Fakeroot for "sys atsh" */
#define ZCFG_MSG_WIFI_WEB_REDIRECT_CHECK                (209 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_PPP_AUTH_FAIL                          (210 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_REQ_REBOOT                             (211 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_REQ_SYNCFLASH                          (212 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_PPP_LCP_ECHO_GET	                     213
#define ZCFG_MSG_DHCP_OPTIONI125_CHK	                 214
#define ZCFG_MSG_LAN_IP_CONNECTION_UP                   (215 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_DHCPC_BOUND                            (216 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_DHCPC_DECONFIG                         (217 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_DHCPC_RELEASE                          (218 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_DHCP6C_STATE_CHANGED                   (219 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_MGABDEV_DETECT                         (220 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_RA_INFO                                (221 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_MGMT_NAT_DETECT                        (222 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_MGMT_NAT_CLEAR                         (223 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_MGMT_UDP_CONNREQ                       (224 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_MGMT_DIAGNOSTIC_COMPLETE               (225 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_NSLOOKUP_MSG                           (226 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_ATM_OAM_F5_COMPLETE                    (227 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_ATM_OAM_F4_COMPLETE                    (228 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_VC_AUTOHUNT_START                      (229 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_VC_AUTOHUNT_STOP                       (230 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_HTTP_TIMEOUT_CONFIG                    (231 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_NTP_SYNC_SUCCESS                       (232 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_STB_VENDOR_ID_FIND                     (233 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_AUTO_PROVISION                         (234 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_INIT_DATAMODEL_FIN                     (235 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_VLAN_AUTOHUNT_START	                (236 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_VLAN_AUTOHUNT_STOP	                    (237 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_VLAN_HUNT_SUCCESS	                    (238 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_VLAN_HUNT_FAIL	                        (239 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_VLAN_HUNT_SET_TIMEOUT	                (240 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_MGMT_CONNECT_UPDATE                    (241 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_DOWNLOAD_DIAG_COMPLETE_EVENT           (242 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_TR64_LAN_DEVICE_UPDATE                 (243 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_DHCPC_RENEW                            (245 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_AUTOHUNT_FINISH	                    (246 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_ETHWAN_TR69_PROVISION_SUCCESS          (247 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_VLAN_HUNT_TERMINATE                    (248 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_AUTO_RSV_IP	                        (249 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_UPLOAD_DIAG_COMPLETE_EVENT             (250 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_DHCPD_OPTION                           (251 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_SIP_WAN_CHK                            (252 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_CLEAN_ROMD_NO_REPLY	                (253 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_SAVE_ROMD_NO_REPLY	                    (254 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_UPGRADING_FW_CHECK_FWID_ON	            (255 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_UPGRADING_FW_CHECK_FWID_OFF	        (256 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_UPGRADING_FW_CHECK_MODEL_ON	        (257 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_UPGRADING_FW_CHECK_MODEL_OFF	        (258 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_PROXIMITY_SENSOR_ON                    (259 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_PROXIMITY_SENSOR_OFF                   (260 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_ZYAUTOPROVISION                        (261 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_POWER_MGMT_LED_ON	                    (262 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_POWER_MGMT_LED_OFF	                    (263 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_REQ_SWITCH_BOOT_PARTITION	             264
#define ZCFG_MSG_RESET_ACCOUNT_DEFAULT                  (265 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_PINGSVRS_RST	                        (266 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_MAIL_SEND_EVENT	                    (267 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_DHCP6S_STATE	                        (268 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_REPLY	                                 269
#define ZCFG_MSG_HELLO	                                 270
#define ZCFG_MSG_NO_REPLY	                            (271 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_PPPD_EVENT                             (272 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_PARAMETER_CHANGED_NOTIFY               (273 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_LAN_MAC_CONTROL_EVENT                  (274 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_INIT_WAN_LINK_INFO                     (275 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_REBOOT_SYSTEM                          (276 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_PING_MSG                               (277 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_TRACERT_MSG                            (278 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_CLEAN_SYSLOG                            279
#define ZCFG_MSG_DHCP6C_CLTSRV                          (280 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_DHCP6C_OPTION                          (281 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_REQ_RTK_SWITCH_PORT_ISOLATE_SET        (282 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_RA_IPV6_LOST                           (283 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_FAKEROOT_SYS_FWUR                      (284 | ZCFG_NO_WAIT_REPLY)  /* Fakeroot for "sys fwur" */
#define ZCFG_MSG_FAKEROOT_ZIGBEE_CMD                    (285 | ZCFG_NO_WAIT_REPLY)  /* Fakeroot for ZIGBEE_CMD */
#define ZCFG_MSG_FAKEROOT_COMMAND_REPLY                  286

#define ZCFG_MSG_FAKEROOT_ZYCLI_COMMAND                 (287 | ZCFG_NO_WAIT_REPLY)  /* Fakeroot for zycli command */
#define ZCFG_MSG_GET_ROMD                                288
#define ZCFG_MSG_ROOT_QURY_OBJECT_PATH_LIST             (289 | ZCFG_NO_WAIT_REPLY)

#define ZCFG_MSG_OMCI_GPON_WAN_SERVICE_STATUS_CHANGE    (290 | ZCFG_NO_WAIT_REPLY)


#define ZCFG_MSG_GUI_CUSTOMIZATION_OBJ_SYNC             (291 | ZCFG_NO_WAIT_REPLY)

#define ZCFG_MSG_DEL_INTFGUP_PORT_EVENT					(292 | ZCFG_NO_WAIT_REPLY)

#define ZCFG_MSG_RDM_MAP_ATTR_SYNC                      (293 | ZCFG_NO_WAIT_REPLY)

/*------------------------------------------------------------------------------

    WAN
        range  : 1000 - 1999
        prefix : ZCFG_MSG_WAN_

------------------------------------------------------------------------------*/
#define ZCFG_MSG_WAN_CONNCTION_READY	                (1000 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_WAN_CONNCTION_LOST	                    (1001 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_WAN_PPP_DISCONNECT                      1002
#define ZCFG_MSG_WAN_PPP_CONNECT                         1003
#define ZCFG_MSG_WAN_IP_RELEASE                          1004
#define ZCFG_MSG_WAN_IP_RENEW                            1005
#define ZCFG_MSG_WAN_IP_CONNECTION_UP                   (1006 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_WAN_LINK_STATUS                        (1007 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_WAN_PPP_CONNECTION_UP                  (1009 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_WAN_CONNECTION_READY                   (1010 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_WAN_CONNECTION_LOST                    (1011 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_WAN_PPP_DISCONNECTED                   (1012 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_WAN_PPP_CONNECTING                     (1013 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_WAN_INTERNET_LED_UPDATE                (1014 | ZCFG_NO_WAIT_REPLY)
/* __ZyXEL__, Albert, 20180209,Support IPv6 option IA_NA and IA_PD  */
#define ZCFG_MSG_WAN_IPV6_CLIENT_RELOAD                 (1015  | ZCFG_NO_WAIT_REPLY)
/*------------------------------------------------------------------------------

    VOIP
        range  : 2000 - 2999
        prefix : ZCFG_MSG_VOICE_

------------------------------------------------------------------------------*/
#define ZCFG_MSG_VOICE_CONTROL                           2000
#define ZCFG_MSG_VOICE_DEBUG_AND_TEST                    2001
#define ZCFG_MSG_VOICE_STATS_GET                         2002
#define ZCFG_MSG_VOICE_LIST_ACCESS                       2003
#define ZCFG_MSG_VOICE_CAP_GET                           2004
#define ZCFG_MSG_VOICE_CONNECTION_CHANGE                (2005 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_VOICE_CONNECTION_LOST                  (2006 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_VOICE_DYNAMIC_INSTANCE_CHANGED         (2007 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_VOICE_STATIC_CONFIG_CHANGED            (2008 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_VOICE_CONFIG_SAVED                     (2009 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_VOICE_CONFIG_CHANGED_PARTIAL_RELOAD	(2010 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_DECT_CONTROL                            2011
#define ZCFG_MSG_DECT_STATS_GET                          2012
#define ZCFG_MSG_VOICE_AUTO_TEST                          2013

/*------------------------------------------------------------------------------

    TR-069
        range  : 3000 - 3999
        prefix : ZCFG_MSG_TR069_

------------------------------------------------------------------------------*/
#define ZCFG_MSG_REQUEST_TR98_OBJMAPPING                 3000
#define ZCFG_MSG_REQUEST_TR181_OBJMAPPING                3001
#define ZCFG_MSG_NOTIFY_TR69_TR98                       (3002 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_ADD_TR98_MAPPING                        3003
#define ZCFG_MSG_UPDATE_PARAMETER_NOTIFY                (3004 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_HOSTS	                                 3005
#define ZCFG_MSG_REQUEST_DELAY_DELETE	                 3006
#define ZCFG_MSG_UPGRADING_FW_CHECK_FWID_STATUS	         3007
#define ZCFG_MSG_UPGRADING_FW_CHECK_MODEL_STATUS	     3008
#define ZCFG_MSG_REQUEST_GET_PARAM_ATTR_LIST	         3009
#define REQUEST_QUERY_OBJ_PARAM_ATTR	                 3010
#define REQUEST_QUERY_OBJ_EXIST                          3011
#define ZCFG_MSG_LOG_SETTING_CONFIG                     (3012 | ZCFG_NO_WAIT_REPLY)
#define REQUEST_QUERY_TR98_OBJ_INSTANCE_ARRAY	         3013
#define REQUEST_QUERY_TR181_OBJ_INSTANCE_ARRAY	         3014
#define ZCFG_MSG_REQUEST_TR98_MAPPING                    3015   /* Request for tr181 object name related with tr98 */
#define ZCFG_MSG_REQUEST_TR181_MAPPING                   3016   /* Request for tr98 object name related with tr181 */
#define ZCFG_MSG_TR64_DEVICE_UPDATE                     (3017 | ZCFG_NO_WAIT_REPLY)
#define REQUEST_SET_MULTI_OBJ_RUN_VALID_ONLY             3020
#define REQUEST_SET_PARAMETERKEY                         3021
#define REQUEST_QUERY_OBJ_PARAM_VALUE                    3022
/*------------------------------------------------------------------------------

    WIFI
        range  : 4000 - 4999
        prefix : ZCFG_MSG_WIFI_

------------------------------------------------------------------------------*/
#define ZCFG_MSG_WIFI_INIT	                            (4000 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_WIFI_RELOAD	                        (4001 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_WIFI_UPDATE_LANINFO	                (4002 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_WIFI_GET_LIST	                         4003
#define ZCFG_MSG_WPS_RELOAD	                            (4004 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_WPS_HWBTN_PRESS	                     4005
#define ZCFG_MSG_WPS_SWBTN_PRESS	                     4006
#define ZCFG_MSG_WPS_START_STAPIN	                     4007
#define ZCFG_MSG_WDS_SCAN	                             4008
#define ZCFG_MSG_WIFI_STA_FILTER	                    (4009 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_CHANNEL_SCAN	                         4010
#define ZCFG_MSG_GET_CHANNEL_INFO	                     4011
#define ZCFG_MSG_WIFI_ST_UPDATE	                         4012
#define ZCFG_MSG_WIFI_RELOAD_CHECK	                     4013
#define ZCFG_MSG_WIFI_LED_ENABLE	                    (4014 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_WPS_ACTION_CANCEL	                     4015
#define ZCFG_MSG_WPS_UPDATE_CONFIG	                     4016
#define ZCFG_MSG_WLAN_GET_CMD	                         4017
#define ZCFG_MSG_WLAN_SET_CMD	                         4018
#define ZCFG_MSG_WIFI_RELOAD_DELAY	                    (4019 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_BSA_STA_FILTER	                        (4020 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_ENABLE_SONiQ                           (4021 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_PRESET_SSID_EN                         (4022 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_PRESET_SSID_DIS                        (4023 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_UPDATE_ONE_CONNECT                     (4024 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_PRESET_SSID_MODE                       (4025 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_APP_SOCKET_CLOSE                       (4026 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_WPSRUN_ESMD_TIME_OUT                   (4027 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_WPSRUN_UPDATE_CONFIG                   (4028 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_WPSRUN_STOP                            (4029 | ZCFG_NO_WAIT_REPLY)
#define ZCFG_MSG_WPS_IPTV_PBC				 4030
#define ZCFG_MSG_WPSRUN_ESMD_ZHTTPD			(4031 | ZCFG_NO_WAIT_REPLY)

#define ZCFG_MSG_ZCMD_MODULE_CONFIG			(4032 | ZCFG_NO_WAIT_REPLY)

//==============================================================================
#endif // _ZCFG_MSG_TYPE_H_
