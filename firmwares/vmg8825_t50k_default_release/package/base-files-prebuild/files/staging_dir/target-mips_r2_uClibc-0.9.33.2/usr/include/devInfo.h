/*Parameter*/
extern tr98Parameter_t para_DevInfo[];
extern tr98Parameter_t para_DevInfoVendorCfg[];
extern tr98Parameter_t para_ProcSt[];
extern tr98Parameter_t para_ProcStPs[];
extern tr98Parameter_t para_MemoryStatus[];

/*Handler Function*/
extern zcfgRet_t devInfoObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t devInfoObjSet(char *, int , struct json_object *, struct json_object *);
extern zcfgRet_t devInfoObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int devInfoObjAttrGet(char *, int , char *);
extern zcfgRet_t devInfoObjAttrSet(char *, int , char *, int , struct json_object *);
extern zcfgRet_t devInfoVendorCfgObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t devInfoVendorCfgObjSet(char *, int , struct json_object *, struct json_object *);
extern zcfgRet_t devProcStGet(char *, int, struct json_object **, bool);
extern zcfgRet_t devProcStPsGet(char *, int, struct json_object **, bool);
/*InternetGatewayDevice.DeviceInfo.MemoryStatus*/
extern zcfgRet_t memoryStatusObjGet(char *, int, struct json_object **, bool);

