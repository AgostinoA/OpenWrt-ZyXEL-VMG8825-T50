#ifndef _WANDEV_API_H_
#define _WANDEV_API_H_

int portMappingNumGet(char *);
zcfgRet_t natInfoSet(char *, struct json_object *);
zcfgRet_t natIntfGetJobj(const char *, objIndex_t *, struct json_object **);
zcfgRet_t defaultRtGetObj(const char *, objIndex_t *, struct json_object **, const char *);
char *activeDefaultGt_Strip(const char *, const char *);
char *activeDefaultGt_Add(const char *, const char *);
zcfgRet_t defaultGwInfoSet(char *, struct json_object *);
zcfgRet_t retrieveJobjWithIpIface(const char *, zcfg_offset_t , objIndex_t *, struct json_object **);
#if 0
zcfgRet_t dnsInfoSet(char *, struct json_object *);
#else
zcfgRet_t dnsInfoGetJobj(char *, objIndex_t *, struct json_object **, bool, bool);
zcfgRet_t dnsAddJobj(char *, objIndex_t *, struct json_object **);
#endif
bool isIGMPProxyEnable(char *ipIface);
zcfgRet_t multiObjEthLinkAdd(char *, char *, struct json_object *);
zcfgRet_t multiObjVlanTermAdd(char *, char *, struct json_object *);
zcfgRet_t multiObjIpIfaceAdd(char *, char *, struct json_object *);
zcfgRet_t multiObjPppIfaceAdd(char *, char *, struct json_object *);
zcfgRet_t ethLinkAdd(char *, char *);
zcfgRet_t vlanTermAdd(char *vlanTermPathName, char *lowerLayer);
zcfgRet_t ipIfaceAdd(char *, char *);
zcfgRet_t pppIfaceAdd(char *, char *);
zcfgRet_t addDhcpObj(char *, struct json_object *);
zcfgRet_t setDhcpObj(char *, bool, struct json_object *);
zcfgRet_t ipaddrSet(char *, objIndex_t *, struct json_object **, const char *, struct json_object *, struct json_object *);
zcfgRet_t DhcpcIidGet(char *, objIndex_t *);
#ifdef ISKON_CUSTOMIZATION 
bool getSpecificObj(zcfg_offset_t, char *, json_type , void *, objIndex_t *, struct json_object **);
#endif
#endif