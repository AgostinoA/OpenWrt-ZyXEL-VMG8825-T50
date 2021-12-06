#ifndef __ONECONNECT_H__
#define __ONECONNECT_H__
/*Parameter*/
extern tr98Parameter_t para_OneConnectExt[];

/* InternetGatewayDevice.LANDevice.i.Hosts.Host.i.X_ZYXEL_EXT */
extern zcfgRet_t oneConnectExtObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
extern zcfgRet_t oneConnectExtObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);

/* InternetGatewayDevice.X_ZYXEL_EXT.SpeedTestInfo */
#endif