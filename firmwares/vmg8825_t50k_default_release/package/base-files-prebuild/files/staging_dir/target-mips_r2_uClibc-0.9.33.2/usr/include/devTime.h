/*Parameter*/
extern tr98Parameter_t para_Time[];

/*Handler Function*/
extern zcfgRet_t timeObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t timeObjSet(char *, int, struct json_object *, struct json_object *);

