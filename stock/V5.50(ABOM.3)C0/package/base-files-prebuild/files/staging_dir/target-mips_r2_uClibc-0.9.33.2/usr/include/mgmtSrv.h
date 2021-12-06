/*Parameter*/
extern tr98Parameter_t para_MgmtSrv[];
extern tr98Parameter_t para_MgabDev[];

/*Handler Function*/
extern zcfgRet_t mgmtSrvObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t mgmtSrvObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t mgmtSrvObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int mgmtSrvObjAttrGet(char *, int , char *);
extern zcfgRet_t mgmtSrvObjAttrSet(char *, int , char *, int , struct json_object *);

extern zcfgRet_t mgabDevObjGet(char *, int, struct json_object **, bool);

