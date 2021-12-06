extern tr98Parameter_t para_XGRE[];
extern tr98Parameter_t para_XGRETunnel[];
extern tr98Parameter_t para_XGRETunnelStats[];

extern zcfgRet_t zyXGREObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t zyXGRETunnelObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t zyXGRETunnelObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t zyXGRETunnelObjAdd(char *tr98FullPathName, int *idx);
extern zcfgRet_t zyXGRETunnelObjDel(char *tr98FullPathName);
extern zcfgRet_t zyXGRETunnelStatsObjGet(char *, int, struct json_object **, bool);
