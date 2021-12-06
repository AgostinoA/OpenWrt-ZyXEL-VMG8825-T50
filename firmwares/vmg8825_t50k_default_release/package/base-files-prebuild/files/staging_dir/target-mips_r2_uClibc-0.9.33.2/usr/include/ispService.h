/*Parameter*/
extern tr98Parameter_t para_IspSrv[];

/*Handler Function*/
extern zcfgRet_t ispSrvObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t ispSrvObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj, char *paramfault);
extern zcfgRet_t ispSrvObjAdd(char *tr98FullPathName, int *idx);
extern zcfgRet_t ispSrvObjDel(char *tr98FullPathName);

void SetParenCtlDisableForce();
