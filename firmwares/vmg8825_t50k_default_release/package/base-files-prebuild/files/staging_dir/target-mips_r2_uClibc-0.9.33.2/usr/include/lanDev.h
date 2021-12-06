/*Parameter*/
extern tr98Parameter_t para_LanDev[];
extern tr98Parameter_t para_LanHostConfMgmt[];
extern tr98Parameter_t para_IpIntf[];
#ifdef LANIPALIAS
extern tr98Parameter_t para_IpAlias[];
#endif
#ifdef IPV6INTERFACE_PROFILE
extern tr98Parameter_t para_IpIntfV6Addr[];
extern tr98Parameter_t para_IpIntfV6Prefix[];
#endif
#ifdef ROUTERADVERTISEMENT_PROFILE
extern tr98Parameter_t para_IpIntfRouterAdver[];
#endif
#ifdef IPV6SERVER_PROFILE
extern tr98Parameter_t para_IpIntfV6Srv[];
#endif
extern tr98Parameter_t para_DhcpStaticAddr[];
extern tr98Parameter_t para_DhcpOpt[];
extern tr98Parameter_t para_DhcpCondServPool[];
extern tr98Parameter_t para_DhcpCondServPoolDhcpStaticAddr[];
extern tr98Parameter_t para_DhcpCondServPoolDhcpOpt[];
extern tr98Parameter_t para_LanEthIntfConf[];
extern tr98Parameter_t para_LanEthIntfConfStat[];
extern tr98Parameter_t para_LanDevWlanCfg[];
extern tr98Parameter_t para_LanDevWlanCfgStat[];
extern tr98Parameter_t para_LanDevWlanCfgWps[];
extern tr98Parameter_t para_LanDevWlanCfgAssocDev[];
extern tr98Parameter_t para_LanDevWlanCfgAssocDevStat[];
extern tr98Parameter_t para_WepKey[];
extern tr98Parameter_t para_Psk[];
extern tr98Parameter_t para_NeiborWifiDiag[];
extern tr98Parameter_t para_NeiborWifiDiagResult[];
extern tr98Parameter_t para_Hosts[];
extern tr98Parameter_t para_Host[];

#ifdef ZyXEL_DHCP_OPTION125
extern tr98Parameter_t para_VendorSpecific[];
extern tr98Parameter_t para_VendorSpecificProf[];
#endif

/*Handler Function*/
extern zcfgRet_t lanDevHostsObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t lanDevHostsObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int lanDevHostsObjAttrGet(char *, int, char *);
extern zcfgRet_t lanDevHostsObjAttrSet(char *, int, char *, int , struct json_object *);

extern zcfgRet_t lanDevHostObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
#ifdef ZYXEL_ELIMINATE_DHCP_LEASE
extern zcfgRet_t lanDevHostsObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj, char *paramfault);
extern zcfgRet_t lanDevHostObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj, char *paramfault);
#endif
extern zcfgRet_t lanDevHostObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int lanDevHostObjAttrGet(char *, int, char *);
extern zcfgRet_t lanDevHostObjAttrSet(char *, int, char *, int , struct json_object *);

extern zcfgRet_t lanIfacesObjGet(char *, int , struct json_object **, bool );

extern zcfgRet_t lanDevObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t lanDevObjAdd(char *tr98FullPathName, int *idx);
extern zcfgRet_t lanDevObjDel(char *tr98FullPathName);

extern zcfgRet_t lanHostConfMgmtObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t lanHostConfMgmtObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);

extern zcfgRet_t lanIpIntfObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t lanIpIntfObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
extern zcfgRet_t lanIpIntfObjAdd(char *tr98FullPathName, int *idx);
extern zcfgRet_t lanIpIntfObjDel(char *tr98FullPathName);

#ifdef LANIPALIAS
extern zcfgRet_t lanIpAliasObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t lanIpAliasObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
extern zcfgRet_t lanIpAliasObjAdd(char *tr98FullPathName, int *idx);
//extern zcfgRet_t lanIpAliasObjDel(char *tr98FullPathName);
#endif

extern zcfgRet_t lanDhcpStaticAddrObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t lanDhcpStaticAddrObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
extern zcfgRet_t lanDhcpStaticAddrObjAdd(char *tr98FullPathName, int *idx);
extern zcfgRet_t lanDhcpStaticAddrObjDel(char *tr98FullPathName);
extern zcfgRet_t lanDhcpStaticAddrObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int lanDhcpStaticAddrObjAttrGet(char *, int, char *);
extern zcfgRet_t lanDhcpStaticAddrObjAttrSet(char *, int, char *, int , struct json_object *);

extern zcfgRet_t lanDhcpOptObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t lanDhcpOptObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
extern zcfgRet_t lanDhcpOptObjAdd(char *tr98FullPathName, int *idx);
extern zcfgRet_t lanDhcpOptObjDel(char *tr98FullPathName);
extern zcfgRet_t lanDhcpOptObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int lanDhcpOptObjAttrGet(char *, int, char *);
extern zcfgRet_t lanDhcpOptObjAttrSet(char *, int, char *, int , struct json_object *);

extern zcfgRet_t lanDhcpCondServPoolObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t lanDhcpCondServPoolObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
extern zcfgRet_t lanDhcpCondServPoolObjAdd(char *tr98FullPathName, int *idx);
extern zcfgRet_t lanDhcpCondServPoolObjDel(char *tr98FullPathName);
extern zcfgRet_t lanDhcpCondServPoolObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int lanDhcpCondServPoolObjAttrGet(char *, int, char *);
extern zcfgRet_t lanDhcpCondServPoolObjAttrSet(char *, int, char *, int , struct json_object *);

extern zcfgRet_t lanDhcpCondServPoolStaticAddrObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t lanDhcpCondServPoolStaticAddrObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
extern zcfgRet_t lanDhcpCondServPoolStaticAddrObjAdd(char *tr98FullPathName, int *idx);
extern zcfgRet_t lanDhcpCondServPoolStaticAddrObjDel(char *tr98FullPathName);
extern zcfgRet_t lanDhcpCondServPoolStaticAddrObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int lanDhcpCondServPoolStaticAddrObjAttrGet(char *, int, char *);
extern zcfgRet_t lanDhcpCondServPoolStaticAddrObjAttrSet(char *, int, char *, int , struct json_object *);

extern zcfgRet_t lanDhcpCondServPoolOptObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t lanDhcpCondServPoolOptObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
extern zcfgRet_t lanDhcpCondServPoolOptObjAdd(char *tr98FullPathName, int *idx);
extern zcfgRet_t lanDhcpCondServPoolOptObjDel(char *tr98FullPathName);
extern zcfgRet_t lanDhcpCondServPoolOptObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int lanDhcpCondServPoolOptObjAttrGet(char *, int, char *);
extern zcfgRet_t lanDhcpCondServPoolOptObjAttrSet(char *, int, char *, int , struct json_object *);

extern zcfgRet_t lanEthIntfConfObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t lanEthIntfConfObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
extern zcfgRet_t lanEthIntfConfObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int lanEthIntfConfObjAttrGet(char *, int, char *);
extern zcfgRet_t lanEthIntfConfObjAttrSet(char *, int, char *, int , struct json_object *);

extern zcfgRet_t lanEthIntfConfStatObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);

/*InternetGatewayDevice.LANDevice.i.WLANConfiguration.i*/
extern zcfgRet_t lanDevWlanCfgObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t lanDevWlanCfgObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t lanDevWlanCfgObjAttrSet(char *, int , char *, int , struct json_object *);
extern int lanDevWlanCfgObjAttrGet(char *, int , char *);
extern zcfgRet_t lanDevWlanCfgObjNotify(char *, char *, struct json_object *, int , struct json_object **);

/*InternetGatewayDevice.LANDevice.i.WLANConfiguration.i.Stats*/
extern zcfgRet_t lanDevWlanCfgStatObjGet(char *, int, struct json_object **, bool);

/*InternetGatewayDevice.LANDevice.i.WLANConfiguration.i.WPS*/
extern zcfgRet_t lanDevWlanCfgWpsObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t lanDevWlanCfgWpsObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);

/*InternetGatewayDevice.LANDevice.i.WLANConfiguration.i.AssociatedDevice.i*/
extern zcfgRet_t lanDevWlanCfgAssocDevObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);

/*InternetGatewayDevice.LANDevice.i.WLANConfiguration.i.AssociatedDevice.i.Stats*/
extern zcfgRet_t lanDevWlanCfgAssocDevStatObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t lanDevWlanCfgAssocDevStatObjNotify(char *tr98ObjName, char *tr181ParamName, struct json_object *tr181ParamVal, int handler, struct json_object **tr98NotifyInfo);
extern int lanDevWlanCfgAssocDevStatObjAttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t lanDevWlanCfgAssocDevStatObjAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);

/*InternetGatewayDevice.LANDevice.i.WLANConfiguration.i.PreSharedKey.i*/
extern zcfgRet_t lanDevWlanCfgPskObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t lanDevWlanCfgPskObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);

/*InternetGatewayDevice.LANDevice.i.WLANConfiguration.i.WEPKey.i*/
extern zcfgRet_t lanDevWlanCfgWEPKeyObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool);
extern zcfgRet_t lanDevWlanCfgWEPKeyObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);

/*InternetGatewayDevice.X_ZYXEL_NeighboringWiFiDiagnostic*/
extern zcfgRet_t wifiNeiborDiagObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t wifiNeiborDiagObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj, char *paramfault);
extern zcfgRet_t wifiNeiborDiagObjNotify(char *tr98ObjName, char *tr181ParamName, struct json_object *tr181ParamVal, int handler, struct json_object **tr98NotifyInfo);
extern int wifiNeiborDiagObjAttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t wifiNeiborDiagObjAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);

/*InternetGatewayDevice.X_ZYXEL_NeighboringWiFiDiagnostic.Result.i*/
extern zcfgRet_t wifiNeiborDiagResultObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t wifiNeiborDiagResultObjNotify(char *tr98ObjName, char *tr181ParamName, struct json_object *tr181ParamVal, int handler, struct json_object **tr98NotifyInfo);
extern int wifiNeiborDiagResultObjAttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t wifiNeiborDiagResultObjAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);

/*InternetGatewayDevice.LANDevice.i.LANHostConfigManagement.IPInterface.i.X_ZYXEL_IPv6Address.i*/
extern zcfgRet_t lanIpIntfV6AddrObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t lanIpIntfV6AddrObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t lanIpIntfV6AddrObjAdd(char *, int *);
extern zcfgRet_t lanIpIntfV6AddrObjDel(char *);

/*InternetGatewayDevice.LANDevice.i.LANHostConfigManagement.IPInterface.i.X_ZYXEL_IPv6Prefix.i*/
extern zcfgRet_t lanIpIntfV6PrefixObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t lanIpIntfV6PrefixObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t lanIpIntfV6PrefixObjAdd(char *, int *);
extern zcfgRet_t lanIpIntfV6PrefixObjDel(char *);

/*InternetGatewayDevice.LANDevice.i.LANHostConfigManagement.IPInterface.i.X_ZYXEL_RouterAdvertisement.*/
extern zcfgRet_t lanIpIntfRouterAdverObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t lanIpIntfRouterAdverObjSet(char *, int, struct json_object *, struct json_object *);

/*InternetGatewayDevice.LANDevice.i.LANHostConfigManagement.IPInterface.i.X_ZYXEL_DHCPv6Server.*/
extern zcfgRet_t lanIpIntfV6SrvObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t lanIpIntfV6SrvObjSet(char *, int, struct json_object *, struct json_object *);

#ifdef ZyXEL_DHCP_OPTION125
/*InternetGatewayDevice.X_ZYXEL_EXT.VendorSpecific */
extern zcfgRet_t zyExtVendorSpecObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtVendorSpecObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
/*InternetGatewayDevice.X_ZYXEL_EXT.VendorSpecific.Profile.i */
extern zcfgRet_t zyExtVendorSpecProfObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t zyExtVendorSpecProfObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj);
extern zcfgRet_t zyExtVendorSpecProfObjAdd(char *tr98FullPathName, int *idx);
extern zcfgRet_t zyExtVendorSpecProfObjDel(char *tr98FullPathName);
#endif
