/*Parameter*/
extern tr98Parameter_t para_L2Br[];
extern tr98Parameter_t para_Br[];
extern tr98Parameter_t para_Port[];
extern tr98Parameter_t para_Vlan[];
extern tr98Parameter_t para_Filter[];
extern tr98Parameter_t para_Mark[];
extern tr98Parameter_t para_AvaiIntf[];

/*Handler Function*/
extern zcfgRet_t l2BridingObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t l2BridingObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int l2BridingObjAttrGet(char *, int, char *);
extern zcfgRet_t l2BridingObjAttrSet(char *, int, char *, int , struct json_object *);

extern zcfgRet_t l2BrObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t l2BrObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
extern zcfgRet_t l2BrObjAdd(char *tr98FullPathName, int *idx);
extern zcfgRet_t l2BrObjDel(char *tr98FullPathName);
extern zcfgRet_t l2BrObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int l2BrObjAttrGet(char *, int, char *);
extern zcfgRet_t l2BrObjAttrSet(char *, int, char *, int , struct json_object *);

extern zcfgRet_t l2BrPortObjGet(char *, int , struct json_object **, bool );
extern zcfgRet_t l2BrPortObjSet(char *, int , struct json_object *, struct json_object *, char *);
extern zcfgRet_t l2BrPortObjAdd(char *, int *);
extern zcfgRet_t l2BrPortObjDel(char *);

extern zcfgRet_t l2BrFilterObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t l2BrFilterObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
extern zcfgRet_t l2BrFilterObjAdd(char *tr98FullPathName, int *idx);
extern zcfgRet_t l2BrFilterObjDel(char *tr98FullPathName);
extern zcfgRet_t l2BrFilterObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int l2BrFilterObjAttrGet(char *, int, char *);
extern zcfgRet_t l2BrFilterObjAttrSet(char *, int, char *, int , struct json_object *);

extern zcfgRet_t l2BrAvailableIntfObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t l2BrAvailableIntfObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int l2BrAvailableIntfObjAttrGet(char *, int, char *);
extern zcfgRet_t l2BrAvailableIntfObjAttrSet(char *, int, char *, int , struct json_object *);

extern zcfgRet_t l2BrVlanObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t l2BrVlanObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
extern zcfgRet_t l2BrVlanObjAdd(char *tr98FullPathName, int *idx);
extern zcfgRet_t l2BrVlanObjDel(char *tr98FullPathName);
extern zcfgRet_t l2BrVlanObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int l2BrVlanObjAttrGet(char *, int, char *);
extern zcfgRet_t l2BrVlanObjAttrSet(char *, int, char *, int , struct json_object *);
