#ifndef _ZCFG_FE_DAL_H
#define _ZCFG_FE_DAL_H

int zcfgFeDalGetReturnValue(struct json_object *Jobj, const char *key, void* value);
int zcfgFeDalSetReturnValue(struct json_object *Jobj, json_type type, const char *key, void* value);
zcfgRet_t zcfgFeDalHandler(const char *handlerName, const char *method, struct json_object *Jobj, struct json_object *Jarray, char *replyMsg);
zcfgRet_t getWanLanList(struct json_object **Jarray);
int isDigitString(char *getString);
zcfgRet_t insertLoginUserInfo(struct json_object *Jobj, const char *userName, const char *level);
zcfgRet_t getLoginUserInfo(struct json_object *Jobj, char *userName, char *level);
bool isSameSubNet( char *lanIp, char *lansubnetMask, char *staticIP);

#endif
