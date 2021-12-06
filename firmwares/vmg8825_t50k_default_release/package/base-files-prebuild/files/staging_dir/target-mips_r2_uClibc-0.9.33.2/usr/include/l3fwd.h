/*Parameter*/
extern tr98Parameter_t para_L3Fwd[];
extern tr98Parameter_t para_Fwd[];
#ifdef L3IPV6FWD
extern tr98Parameter_t para_Ipv6Fwd[];
#endif
/*Handler Function*/
extern zcfgRet_t l3fwdObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t l3fwdObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj, char *paramfault);

extern zcfgRet_t l3fwdFwdTbObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t l3fwdFwdTbObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t l3fwdFwdTbObjAdd(char *, int *);
extern zcfgRet_t l3fwdFwdTbObjDel(char *);
extern zcfgRet_t l3fwdFwdTbObjAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);
#ifdef L3IPV6FWD
extern zcfgRet_t l3fwdIpv6FwdTbObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t l3fwdIpv6FwdTbObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t l3fwdIpv6FwdTbObjAdd(char *, int *);
extern zcfgRet_t l3fwdIpv6FwdTbObjDel(char *);
#endif
