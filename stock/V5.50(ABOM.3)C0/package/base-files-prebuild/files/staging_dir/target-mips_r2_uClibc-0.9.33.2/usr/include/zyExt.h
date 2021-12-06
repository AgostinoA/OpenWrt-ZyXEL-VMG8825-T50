/*Parameter*/
extern tr98Parameter_t para_extend[];
extern tr98Parameter_t para_Dns[];
extern tr98Parameter_t para_DnsRtEntry[];
extern tr98Parameter_t para_DnsEntry[];
extern tr98Parameter_t para_DDns[];
extern tr98Parameter_t para_Tr064[];
extern tr98Parameter_t para_EmailSrv[];
extern tr98Parameter_t para_EmailEvent[];
extern tr98Parameter_t para_VlanGroup[];
extern tr98Parameter_t para_SysInfo[];
#ifdef ZYXEL_SFP_MODULE_SUPPORT
extern tr98Parameter_t para_GponInfo[];
#endif
extern tr98Parameter_t para_Snmp[];
extern tr98Parameter_t para_SnmpTrap[];
#if defined(ISKON_CUSTOMIZATION) || defined(ZYXEL_SP_DOMAIN_TIMER)
extern tr98Parameter_t para_RemoMgmt[];
#endif
extern tr98Parameter_t para_RemoSrv[];
extern tr98Parameter_t para_SpRemoSrv[];
extern tr98Parameter_t para_8021ag[];
#ifdef ZYXEL_ETHOAM_TMSCTL
extern tr98Parameter_t para_8023ah[];
#endif
extern tr98Parameter_t para_RemoTrustDomain[];
extern tr98Parameter_t para_SpTrustDomain[];
extern tr98Parameter_t para_Igmp[];
#if defined(SUNRISE_RANDOM_PASSWORD) || defined(SOL_TR69_LOGINACCOUNT) || defined(ZYXEL_SUPPORT_TR98_LOGIN_ACCOUNT)
extern tr98Parameter_t para_LogCfgGp[];
extern tr98Parameter_t para_LogCfgGpAccount[];
#endif
extern tr98Parameter_t para_LogSetting[];
extern tr98Parameter_t para_LogClassify[];
extern tr98Parameter_t para_LogCategory[];
extern tr98Parameter_t para_MacFilter[];
extern tr98Parameter_t para_MacFilter_WhiteList[];
extern tr98Parameter_t para_ParenCtl[];
extern tr98Parameter_t para_ParenCtlProf[];
extern tr98Parameter_t para_Sec[];
extern tr98Parameter_t para_SecCert[];
extern tr98Parameter_t para_Samba[];
extern tr98Parameter_t para_Upnp[];

#ifdef ZyXEL_IPP_PRINTSERVER
extern tr98Parameter_t para_Ipp_PrintServer[];
#endif

#ifdef ONECONNECT
extern tr98Parameter_t para_OneConnect[];
extern tr98Parameter_t para_SpeedTestInfo[];
#endif

#ifdef ZYXEL_AP_STEERING
extern tr98Parameter_t para_ApSteering[];
#endif //#ifdef ZYXEL_AP_STEERING

#ifdef PROXIMITY_SENSOR_SUPPORT
extern tr98Parameter_t para_ProximitySensor[];
#endif //#ifdef PROXIMITY_SENSOR_SUPPORT


extern tr98Parameter_t para_Landing_Page[];
extern tr98Parameter_t para_Feature_Flag[];
extern tr98Parameter_t para_GUI_Customization[];

#ifdef BUILD_SONIQ
extern tr98Parameter_t para_Qsteer[];
#endif

#ifdef ZYXEL_EASYMESH
extern tr98Parameter_t para_EasyMesh[];
#endif

#ifdef ZYXEL_ONESSID
extern tr98Parameter_t para_OneSsid[];
#endif

#ifdef ZYXEL_TR69_DATA_USAGE
extern tr98Parameter_t para_DataUsage[];
extern tr98Parameter_t para_DataUsageLan[];
extern tr98Parameter_t para_DataUsageWan[];
#endif

#ifdef ZYXEL_SFP_POWER_MGMT
extern tr98Parameter_t para_SfpMgmt[];
#endif


/*Handler Function*/

//InternetGatewayDevice.X_ZYXEL_EXT.
zcfgRet_t zyExtObjGet(char *, int , struct json_object **, bool );
zcfgRet_t zyExtObjSet(char *, int , struct json_object *, struct json_object * );

//InternetGatewayDevice.X_ZYXEL_EXT.DNS
extern zcfgRet_t zyExtDnsObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t zyExtDnsObjSet(char *, int , struct json_object *, struct json_object *);

/*InternetGatewayDevice.X_ZYXEL_EXT.DNSRouteEntry.i*/
extern zcfgRet_t zyExtDnsRtObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t zyExtDnsRtObjSet(char *, int , struct json_object *, struct json_object *);
extern zcfgRet_t zyExtDnsRtObjAdd(char *, int *);
extern zcfgRet_t zyExtDnsRtObjDel(char *);
extern zcfgRet_t zyExtDnsRtObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExtDnsRtObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExtDnsRtObjAttrSet(char *, int, char *, int , struct json_object *);

/*InternetGatewayDevice.X_ZYXEL_EXT.DNSEntry.i*/
extern zcfgRet_t zyExtDnsEntryObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t zyExtDnsEntryObjSet(char *, int , struct json_object *, struct json_object *);
extern zcfgRet_t zyExtDnsEntryObjAdd(char *, int *);
extern zcfgRet_t zyExtDnsEntryObjDel(char *);
extern zcfgRet_t zyExtDnsEntryObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExtDnsEntryObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExtDnsEntryObjAttrSet(char *, int, char *, int , struct json_object *);

/*InternetGatewayDevice.X_ZYXEL_EXT.DynamicDNS*/
extern zcfgRet_t zyExtDDnsObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t zyExtDDnsObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t zyExtDDnsObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExtDDnsObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExtDDnsObjAttrSet(char *, int, char *, int , struct json_object *);

/*InternetGatewayDevice.X_ZYXEL_EXT.TR064*/
extern zcfgRet_t zyExtTr064ObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t zyExtTr064ObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t zyExtTr064ObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExtTr064ObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExtTr064ObjAttrSet(char *, int, char *, int , struct json_object *);

/*InternetGatewayDevice.X_ZYXEL_EXT.VlanGroup.i*/
extern zcfgRet_t zyExtVlanGroupObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t zyExtVlanGroupObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t zyExtVlanGroupObjAdd(char *, int *);
extern zcfgRet_t zyExtVlanGroupObjDel(char *);
extern zcfgRet_t zyExtVlanGroupObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExtVlanGroupObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExtVlanGroupObjAttrSet(char *, int, char *, int , struct json_object *);

/*InternetGatewayDevice.X_ZYXEL_EXT.EmailNotification.EmailService.i*/
extern zcfgRet_t zyExtEmailSrvObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t zyExtEmailSrvObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t zyExtEmailSrvObjAdd(char *, int *);
extern zcfgRet_t zyExtEmailSrvObjDel(char *);
extern zcfgRet_t zyExtEmailSrvObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExtEmailSrvObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExtEmailSrvObjAttrSet(char *, int, char *, int , struct json_object *);

/*InternetGatewayDevice.X_ZYXEL_EXT.EmailNotification.EmailEventConfig.i*/
extern zcfgRet_t zyExtEmailEventObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t zyExtEmailEventObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t zyExtEmailEventObjAdd(char *, int *);
extern zcfgRet_t zyExtEmailEventObjDel(char *);
extern zcfgRet_t zyExtEmailEventObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExtEmailEventObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExtEmailEventObjAttrSet(char *, int, char *, int , struct json_object *);

/*InternetGatewayDevice.X_ZYXEL_EXT.System_Info*/
extern zcfgRet_t zyExtSysInfoObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t zyExtSysInfoObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t zyExtSysInfoObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExtSysInfoObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExtSysInfoObjAttrSet(char *, int, char *, int , struct json_object *);

#ifdef ZYXEL_SFP_MODULE_SUPPORT
/*InternetGatewayDevice.X_ZYXEL_EXT.Gpon_Info*/
extern zcfgRet_t zyExtGponInfoObjGet(char *, int, struct json_object **, bool);
#endif

/*InternetGatewayDevice.X_ZYXEL_EXT.SNMP*/
extern zcfgRet_t zyExtSnmpObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t zyExtSnmpObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t zyExtSnmpObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExtSnmpObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExtSnmpObjAttrSet(char *, int, char *, int , struct json_object *);

/*InternetGatewayDevice.X_ZYXEL_EXT.SNMP.TrapAddr.i*/
extern zcfgRet_t zyExtSnmpTrapObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t zyExtSnmpTrapObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t zyExtSnmpTrapObjAdd(char *tr98FullPathName, int *idx);
extern zcfgRet_t zyExtSnmpTrapObjDel(char *tr98FullPathName);
extern zcfgRet_t zyExtSnmpTrapObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExtSnmpTrapObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExtSnmpTrapObjAttrSet(char *, int, char *, int , struct json_object *);
#if defined(ISKON_CUSTOMIZATION) || defined(ZYXEL_SP_DOMAIN_TIMER)
/*InternetGatewayDevice.X_ZYXEL_EXT.RemoteManagement.*/
extern zcfgRet_t zyExtRemoteMgmtObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtRemoteMgmtObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
#endif
/*InternetGatewayDevice.X_ZYXEL_EXT.RemoteManagement.Service.i*/
extern zcfgRet_t zyExtRemoteMgmtSrvObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtRemoteMgmtSrvObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
extern zcfgRet_t zyExtRemoteMgmtSrvObjAdd(char *tr98FullPathName, int *idx);
extern zcfgRet_t zyExtRemoteMgmtSrvObjDel(char *tr98FullPathName);
extern zcfgRet_t zyExtRemoteMgmtSrvObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExtRemoteMgmtSrvObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExtRemoteMgmtSrvObjAttrSet(char *, int, char *, int , struct json_object *);

/*InternetGatewayDevice.X_ZYXEL_EXT.RemoteManagement.SpService.i*/
extern zcfgRet_t zyExtSpRemoteMgmtSrvObjAdd(char *tr98FullPathName, int *idx);
extern zcfgRet_t zyExtSpRemoteMgmtSrvObjDelete(char *tr98FullPathName);
extern zcfgRet_t zyExtSpRemoteMgmtSrvObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtSpRemoteMgmtSrvObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);

/*InternetGatewayDevice.X_ZYXEL_EXT.RemoteManagement.TrustDomain.i*/
extern zcfgRet_t zyExtRemoteMgmtTrustDomainObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtRemoteMgmtTrustDomainObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
extern zcfgRet_t zyExtRemoteMgmtTrustDomainObjAdd(char *tr98FullPathName, int *idx);
extern zcfgRet_t zyExtRemoteMgmtTrustDomainObjDel(char *tr98FullPathName);

/*InternetGatewayDevice.X_ZYXEL_EXT.RemoteManagement.SpTrustDomain.i*/
extern zcfgRet_t zyExtSpRemoteMgmtTrustDomainObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtSpRemoteMgmtTrustDomainObjAdd(char *tr98FullPathName, int *idx);
extern zcfgRet_t zyExtSpRemoteMgmtTrustDomainObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
extern zcfgRet_t zyExtSpRemoteMgmtTrustDomainObjDel(char *tr98FullPathName);

extern zcfgRet_t zyExtIgmpObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t zyExtIgmpObjSet(char *, int , struct json_object *, struct json_object *);
extern zcfgRet_t zyExtIgmpObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExtIgmpObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExtIgmpObjAttrSet(char *, int, char *, int , struct json_object *);

#if defined(SUNRISE_RANDOM_PASSWORD) || defined(SOL_TR69_LOGINACCOUNT) || defined(ZYXEL_SUPPORT_TR98_LOGIN_ACCOUNT)
extern zcfgRet_t zyExtLogCfgGpObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtLogCfgGpObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj, char *paramfault);
extern zcfgRet_t zyExtLogCfgGpAccountObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtLogCfgGpAccountObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
extern zcfgRet_t zyExtLogCfgGpAccountObjAdd(char *tr98FullPathName, int *idx);
#if defined(ZYXEL_SUPPORT_TR98_LOGIN_ACCOUNT) || defined(SOL_TR69_LOGINACCOUNT)
extern zcfgRet_t zyExtLogCfgGpAccountObjDel(char *tr98FullPathName);
#endif
#endif

/*InternetGatewayDevice.X_ZYXEL_EXT.8021ag*/
extern zcfgRet_t zyExt8021agObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t zyExt8021agObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t zyExt8021agObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExt8021agObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExt8021agObjAttrSet(char *, int, char *, int , struct json_object *);

#ifdef ZYXEL_ETHOAM_TMSCTL
/*InternetGatewayDevice.X_ZYXEL_EXT.8023ah*/
extern zcfgRet_t zyExt8023ahObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t zyExt8023ahObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t zyExt8023ahObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExt8023ahObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExt8023ahObjAttrSet(char *, int, char *, int , struct json_object *);
#endif

/*InternetGatewayDevice.X_ZYXEL_EXT.SAMBA*/
extern zcfgRet_t zyExtSambaObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t zyExtSambaObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t zyExtSambaObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExtSambaObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExtSambaObjAttrSet(char *, int, char *, int , struct json_object *);

/*InternetGatewayDevice.X_ZYXEL_EXT.UPNP*/
extern zcfgRet_t zyExtUPnPObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t zyExtUPnPObjSet(char *, int, struct json_object *, struct json_object *);

/*InternetGatewayDevice.X_ZYXEL_EXT.Log_Setting*/
extern zcfgRet_t zyExtLogSettingObjGet(char *, int , struct json_object **, bool );
extern zcfgRet_t zyExtLogSettingObjSet(char *, int , struct json_object *, struct json_object *);
extern zcfgRet_t zyExtLogSettingObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExtLogSettingObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExtLogSettingObjAttrSet(char *, int, char *, int , struct json_object *);

/*InternetGatewayDevice.X_ZYXEL_EXT.Log_Setting.LogClassify.i*/
extern zcfgRet_t zyExtLogClassifyObjGet(char *, int , struct json_object **, bool );
extern zcfgRet_t zyExtLogClassifyObjAdd(char *tr98FullPathName, int *idx);
extern zcfgRet_t zyExtLogClassifyObjDel(char *tr98FullPathName);
extern zcfgRet_t zyExtLogClassifyObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExtLogClassifyObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExtLogClassifyObjAttrSet(char *, int, char *, int , struct json_object *);

/*InternetGatewayDevice.X_ZYXEL_EXT.Log_Setting.LogClassify.i.Category.i*/
extern zcfgRet_t zyExtLogCategoryObjGet(char *, int , struct json_object **, bool );
extern zcfgRet_t zyExtLogCategoryObjSet(char *, int , struct json_object *, struct json_object *);
extern zcfgRet_t zyExtLogCategoryObjAdd(char *tr98FullPathName, int *idx);
extern zcfgRet_t zyExtLogCategoryObjDel(char *tr98FullPathName);
extern zcfgRet_t zyExtLogCategoryObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExtLogCategoryObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExtLogCategoryObjAttrSet(char *, int, char *, int , struct json_object *);

extern zcfgRet_t zyExtMacFilterObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t zyExtMacFilterObjSet(char *, int , struct json_object *, struct json_object *);
extern zcfgRet_t zyExtMacFilterObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExtMacFilterObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExtMacFilterObjAttrSet(char *, int, char *, int , struct json_object *);

extern zcfgRet_t zyExtMacFilterWhiteListObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t zyExtMacFilterWhiteListObjSet(char *, int , struct json_object *, struct json_object *);
extern zcfgRet_t zyExtMacFilterWhiteListObjAdd(char *, int *);
extern zcfgRet_t zyExtMacFilterWhiteListObjDel(char *);
extern zcfgRet_t zyExtMacFilterWhiteListObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExtMacFilterWhiteListObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExtMacFilterWhiteListObjAttrSet(char *, int, char *, int , struct json_object *);

extern zcfgRet_t zyExtParenCtlObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtParenCtlObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
extern zcfgRet_t zyExtParenCtlObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExtParenCtlObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExtParenCtlObjAttrSet(char *, int, char *, int , struct json_object *);

extern zcfgRet_t zyExtParenCtlProfObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtParenCtlProfObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
extern zcfgRet_t zyExtParenCtlProfObjAdd(char *tr98FullPathName, int *idx);
extern zcfgRet_t zyExtParenCtlProfObjDel(char *tr98FullPathName);
extern zcfgRet_t zyExtParenCtlProfObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExtParenCtlProfObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExtParenCtlProfObjAttrSet(char *, int, char *, int , struct json_object *);

extern zcfgRet_t zyExtSecObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtSecObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExtSecObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExtSecObjAttrSet(char *, int, char *, int , struct json_object *);

extern zcfgRet_t zyExtSecCertObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtSecCertObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
extern zcfgRet_t zyExtSecCertObjAdd(char *tr98FullPathName, int *idx);
extern zcfgRet_t zyExtSecCertObjDel(char *tr98FullPathName);
extern zcfgRet_t zyExtSecCertObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int zyExtSecCertObjAttrGet(char *, int, char *);
extern zcfgRet_t zyExtSecCertObjAttrSet(char *, int, char *, int , struct json_object *);

#ifdef ZyXEL_IPP_PRINTSERVER
/*InternetGatewayDevice.X_ZYXEL_EXT.PrintServer */
extern zcfgRet_t zyExtIppPrintServObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtIppPrintServObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
#endif

#ifdef ONECONNECT
extern zcfgRet_t zyExtOneConnectObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtOneConnectObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);

extern zcfgRet_t zyExtSpeedTestInfoObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtSpeedTestInfoObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
#endif

#ifdef ZYXEL_AP_STEERING
extern zcfgRet_t zyExtApSteeringObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtApSteeringObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
#endif //#ifdef ZYXEL_AP_STEERING

#ifdef PROXIMITY_SENSOR_SUPPORT
extern zcfgRet_t zyExtProximitySensorObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtProximitySensorObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
#endif //#ifdef PROXIMITY_SENSOR_SUPPORT


#ifdef ZYXEL_LANDING_PAGE_FEATURE
extern zcfgRet_t zyExtLandingPageObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtLandingPageObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
#endif

extern zcfgRet_t zyExtFeatureFlagObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtFeatureFlagObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);

extern zcfgRet_t zyExtCustomizationObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtCustomizationObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);

#ifdef ZYXEL_EASYMESH
extern zcfgRet_t zyExtEasyMeshObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtEasyMeshObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
#endif

#ifdef BUILD_SONIQ
extern zcfgRet_t zyExtQsteerObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtQsteerObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
#endif

#ifdef ZYXEL_ONESSID
extern zcfgRet_t zyExtOneSsidObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtOneSsidObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
#endif

#ifdef ZYXEL_SFP_POWER_MGMT
extern zcfgRet_t zyExtSfpMgmObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtSfpMgmObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
#endif

#ifdef ZYXEL_TR69_DATA_USAGE
extern zcfgRet_t zyExtDataUsageObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtDataUsageObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
extern zcfgRet_t zyExtDataUsageLanObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtDataUsageWanObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
#endif

