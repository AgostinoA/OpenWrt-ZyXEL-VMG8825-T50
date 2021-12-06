/*Parameter*/
extern tr98Parameter_t para_Firewall[];
extern tr98Parameter_t para_FirewallLevel[];
extern tr98Parameter_t para_FirewallChain[];
extern tr98Parameter_t para_FirewallChainRule[];

/*Handler Function*/
extern zcfgRet_t firewallObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t firewallObjSet(char *, int , struct json_object *, struct json_object *);
extern zcfgRet_t firewallObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int firewallObjAttrGet(char *, int, char *);
extern zcfgRet_t firewallObjAttrSet(char *, int, char *, int , struct json_object *);

extern zcfgRet_t firewallLevelObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t firewallLevelObjSet(char *, int , struct json_object *, struct json_object *);
extern zcfgRet_t firewallLevelObjAdd(char *, int *);
extern zcfgRet_t firewallLevelObjDel(char *);
extern zcfgRet_t firewallLevelObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int firewallLevelObjAttrGet(char *, int, char *);
extern zcfgRet_t firewallLevelObjAttrSet(char *, int, char *, int , struct json_object *);

extern zcfgRet_t firewallChainObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t firewallChainObjSet(char *, int , struct json_object *, struct json_object *);
extern zcfgRet_t firewallChainObjAdd(char *, int *);
extern zcfgRet_t firewallChainObjDel(char *);
extern zcfgRet_t firewallChainObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int firewallChainObjAttrGet(char *, int, char *);
extern zcfgRet_t firewallChainObjAttrSet(char *, int, char *, int , struct json_object *);

extern zcfgRet_t firewallRuleObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t firewallRuleObjSet(char *, int , struct json_object *, struct json_object *);
extern zcfgRet_t firewallRuleObjAdd(char *, int *);
extern zcfgRet_t firewallRuleObjDel(char *);
extern zcfgRet_t firewallRuleObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int firewallRuleObjAttrGet(char *, int, char *);
extern zcfgRet_t firewallRuleObjAttrSet(char *, int, char *, int , struct json_object *);

