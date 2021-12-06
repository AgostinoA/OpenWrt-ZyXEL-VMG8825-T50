/*Parameter*/
extern tr98Parameter_t para_LanConfSec[];

/*Handler Function*/
extern zcfgRet_t lanConfSecObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t lanConfSecObjSet(char *, int , struct json_object *, struct json_object *);
extern zcfgRet_t lanConfSecObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int lanConfSecObjAttrGet(char *, int, char *);
extern zcfgRet_t lanConfSecObjAttrSet(char *, int, char *, int , struct json_object *);

