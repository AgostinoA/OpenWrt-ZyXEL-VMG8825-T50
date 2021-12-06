#ifndef _ZCFG_FE_DAL_COMMON_H
#define _ZCFG_FE_DAL_COMMON_H

#include <stdbool.h>


#define JSON_RET_OBJ_NAME "_retJobj"


#define JSON_OBJ_COPY(json_object) json_tokener_parse(json_object_to_json_string(json_object))
#define Jget(obj, key) json_object_object_get(obj, key)
#define Jgets(obj, key) json_object_get_string(json_object_object_get(obj, key))
#define Jgeti(obj, key) json_object_get_int(json_object_object_get(obj, key))
#define Jgetb(obj, key) json_object_get_boolean(json_object_object_get(obj, key))
#define Jadds(obj, key, val) json_object_object_add(obj, key, json_object_new_string(val))
#define Jaddi(obj, key, val) json_object_object_add(obj, key, json_object_new_int(val))
#define Jaddb(obj, key, val) json_object_object_add(obj, key, json_object_new_boolean(val))
#define ISSET(key) json_object_object_get(Jobj, key)

#define dal_Add 	1 << 0
#define dal_Edit	1 << 1
#define dal_Delete	1 << 2
#define dal_Get		1 << 3
#define dal_Add_ignore 	1 << 4
#define dal_Edit_ignore	1 << 5
#define dal_ReadOnly	1 << 6
#define dalcmd_Forbid  1 << 7

/*X_ZYXEL_Schedule Days*/
#define DAY_SUN (0x1 << 0)
#define DAY_MON (0x1 << 1)
#define DAY_TUE (0x1 << 2)
#define DAY_WED (0x1 << 3)
#define DAY_THU (0x1 << 4)
#define DAY_FRI (0x1 << 5)
#define DAY_SAT (0x1 << 6)
#define DAY_ALL DAY_SUN|DAY_MON|DAY_TUE|DAY_WED|DAY_THU|DAY_FRI|DAY_SAT

extern bool printDebugMsg;
#ifndef dbg_printf
	#define dbg_printf(fmt, args...) do{if(printDebugMsg)fprintf(stdout, fmt, ## args);else;}while(0)
#endif

typedef struct dal_param_s {
	char		*paraName;
	json_type 	type;
	int			min;  //if min ==0 and max ==0, skip check
	int			max;
	int			(*validate)(int);
	char		*enumeration;
	int			mandatory;
}dal_param_t;

typedef struct dal_handler_s {
	char				*name;
	dal_param_t			*parameter;
	int					(*handler)(const char*, struct json_object *, struct json_object *, char *);
	int					(*showfunc)(struct json_object *);
	char				*method;
	char				*previlege;
}dal_handler_t;

typedef struct dal_voip_region_s {
	char				*simplifyRegion;
	char				*Region;
}dal_voip_region_t;

typedef struct dal_firewall_protocol_s {
	char			*icmptype;
	char			*icmptypecode;
	char			*type;
}dal_firewall_protocol_t;

typedef struct dal_time_zone_s {
	char				*timezone;
	char				*timezoneCLI;
	char				*timezonevalue;
}dal_time_zone_t;



enum { 
	dalType_boolean = 0,
	dalType_int,
	dalType_string,
	dalType_vpivci,
	dalType_v4Addr,
	dalType_v4AddrList,
	dalType_v4Mask,
	dalType_v6Addr,
	dalType_v6AddrPrefix,
	dalType_v4v6Addr,
	dalType_v4v6AddrDomainName,
	dalType_v6AddrIdentifier,
	dalType_IPPrefix,      // e.g 10.10.100.1/32,  192.168.1.0/23, 2001:123::123/128, 2002:1f:dad:12::/64
	dalType_PortRange,     // prot or startPort:endPort
	dalType_AllIntf,      //LAN WAN  WWAN, Include Bridged WAN
	dalType_LanRtWanWWan, //LAN WAN WWAN, not Include Bridged WAN
	dalType_LanRtWan,     //LAN WAN, not Include Bridged WAN 
	dalType_RtWanWWan,    //WAN WWAN,
	dalType_MultiRtWanWWan,    //WAN WWAN,
	dalType_RtWan,	      //Routed WAN
	dalType_BrWan,		  //Bridged WAN
	dalType_Lan,
	dalType_LanName,
	dalType_IntfGrpWanList,
	dalType_IntfGrpLanPortList,
	dalType_IntfGrpLanPortListNoWiFi,	// LAN1, LAN2, LAN3, LAN4
	dalType_LanPortListBr0NoWiFi,		// LAN1, LAN2, LAN3, LAN4, br0
	dalType_VoipRegion,					//VOIP region list
	dalType_VoipLine,
	dalType_VoipProvider,				//Service provider
	dalType_MultiVoipLine,
	dalType_ICMPv6,						//Firewall ICMPv6 list 
	dalType_LocalCert,
	dalType_emailAddr,					//call validateEmailAddr to check email is correct or not
	dalType_emailList,					//list Email account and check email validation
	dalType_ClassList,
	dalType_ClassIntf,
	dalType_RouteIntf,
	dalType_QueueList,
	dalType_MacAddr,
	dalType_MacAddrHyphen,
	dalType_MacAddrList,
	dalType_DayofWeek,
	dalType_TimeRangeList,
	dalType_ParenCtlServiceList,
	dalType_URLFilterList,
	dalType_timezone,
	dalType_HourMin,
	dalType_serveraddr,
	dalType_sambafolder, 
	dalType_usbInfo,
	dalType_usrAccount,
	dalType_intfVlan,					// vlan group name without BrRefKey value
	dalType_wlanMode,					// 802.11b, 802.11g, 802.11n, ...
	dalType_wifiSSID,
    dalType_ShaperIntf
};

bool getSpecificObj(zcfg_offset_t oid, char *key, json_type type, void *value, objIndex_t *outIid, struct json_object **outJobj);
int replaceParam(struct json_object *Jobj1, char *key1, struct json_object *Jobj2, char *key2);
int isDigitString(char *getString);
bool parseTimeRange(const char *timeRange, int *startHour, int *startMin, int *stopHour, int *stopMin);
bool validateMacAddr1(const char *macAddr, const char *delim);
bool parseParenService(const char *service, char *parenCtlService);

#endif
