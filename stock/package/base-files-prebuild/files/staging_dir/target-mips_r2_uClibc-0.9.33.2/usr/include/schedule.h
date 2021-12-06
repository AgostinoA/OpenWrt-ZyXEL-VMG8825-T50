/*Parameter*/
extern tr98Parameter_t para_Schedule[];

/*Handler Function*/
extern zcfgRet_t scheduleObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t scheduleObjSet(char *, int , struct json_object *, struct json_object *);
extern zcfgRet_t scheduleObjAdd(char *, int *);
extern zcfgRet_t scheduleObjDel(char *);
extern zcfgRet_t scheduleObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int scheduleObjAttrGet(char *, int, char *);
extern zcfgRet_t scheduleObjAttrSet(char *, int, char *, int , struct json_object *);

