/*Parameter*/
extern tr98Parameter_t para_WanDev[];
extern tr98Parameter_t para_WANDslDiag[];
extern tr98Parameter_t para_WANConnDev[];
extern tr98Parameter_t para_WANCommIfaceCfg[];
extern tr98Parameter_t para_WANDslIfaceCfg[];
extern tr98Parameter_t para_WANDslIfTestParam[];
extern tr98Parameter_t para_WANDslIfaceCfgStatTotal[];
extern tr98Parameter_t para_WANDslIfaceCfgStatSt[];
extern tr98Parameter_t para_WANDslIfaceCfgStatObjs[];
extern tr98Parameter_t para_WANEthIntfConf[];
extern tr98Parameter_t para_WANEthIntfConfStat[];
extern tr98Parameter_t para_WANDslLinkConf[];
extern tr98Parameter_t para_WANPtmLinkConf[];
extern tr98Parameter_t para_WANPtmLinkConfStat[];
extern tr98Parameter_t para_WANEthLinkConf[];
extern tr98Parameter_t para_WANIpConn[];
extern tr98Parameter_t para_DhcpClient[];
extern tr98Parameter_t para_SentDhcpOpt[];
extern tr98Parameter_t para_ReqDhcpOpt[];
extern tr98Parameter_t para_WANIpConnMld[];
extern tr98Parameter_t para_WANIpPortMap[];
extern tr98Parameter_t para_WANIpPortTrigger[];
extern tr98Parameter_t para_WANIpAddrMapping[];
extern tr98Parameter_t para_WANIpConnStat[];
#ifdef IPV6INTERFACE_PROFILE
extern tr98Parameter_t para_WANIpv6Addr[];
extern tr98Parameter_t para_WANIpv6Prefix[];
#endif
#ifdef DHCPV6CLIENT_PROFILE
extern tr98Parameter_t para_WANIpDhcpV6Client[];
#endif
#ifdef IPV6RD_PROFILE
extern tr98Parameter_t para_WANIpv6Rd[];
#endif
#ifdef ROUTEINFO_INTERFACE
extern tr98Parameter_t para_WANIpIntfRouteInfo[];
#endif
extern tr98Parameter_t para_WANPppConn[];
extern tr98Parameter_t para_WANPppPortMap[];
extern tr98Parameter_t para_WANPppPortTrigger[];
extern tr98Parameter_t para_WANPppAddrMapping[];
extern tr98Parameter_t para_WANPppConnStat[];
extern tr98Parameter_t para_WANPppConnMld[];
#ifdef IPV6INTERFACE_PROFILE
extern tr98Parameter_t para_WANPppv6Addr[];
extern tr98Parameter_t para_WANPppv6Prefix[];
#endif
#ifdef DHCPV6CLIENT_PROFILE
extern tr98Parameter_t para_WANPppDhcpV6Client[];
#endif
#ifdef IPV6RD_PROFILE
extern tr98Parameter_t para_WANPppv6Rd[];
#endif
extern tr98Parameter_t para_WanAtmF5LoDiag[];
extern tr98Parameter_t para_WanAtmF4LoDiag[];

#ifdef CONFIG_XPON_SUPPORT
extern tr98Parameter_t para_WANPonIntfConf[];
extern tr98Parameter_t para_WANPonIntfConfStat[];
#endif

extern tr98Parameter_t para_WANWwanIntfConf[];
extern tr98Parameter_t para_WANWwanIntfStatsConf[] ;
extern tr98Parameter_t para_WANWwanEmailConf[] ;

/*Handler Function*/
extern zcfgRet_t WANDeviceObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANDeviceObjSet(char *, int, struct json_object *, struct json_object *);

extern zcfgRet_t WANCommIfaceCfgObjGet(char *, int, struct json_object **, bool);

/*InternetGatewayDevice.WANDevice.i.WANEthernetInterfaceConfig*/
extern zcfgRet_t WANDslIfaceCfgObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANDslIfaceCfgObjSet(char *, int, struct json_object *, struct json_object *);

/*InternetGatewayDevice.WANDevice.i.WANEthernetInterfaceConfig.TestParams*/
extern zcfgRet_t WANDslIfTestParamObjGet(char *, int, struct json_object **, bool);

/*InternetGatewayDevice.WANDevice.i.WANDSLInterfaceConfig.Stats.Total*/
extern zcfgRet_t WANDslIfaceCfgTtlObjGet(char *, int, struct json_object **, bool);
/* InternetGatewayDevice.WANDevice.i.WANDSLInterfaceConfig.Stats.Showtime */
extern zcfgRet_t WANDslIfaceCfgStObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANDslIfaceCfgStatsSubObjGet(char *, int , struct json_object **, bool );

extern zcfgRet_t WANEthIfaceCfgObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANEthIfaceCfgObjSet(char *, int, struct json_object *, struct json_object *);

extern zcfgRet_t WANEthIfaceCfgStObjGet(char *, int, struct json_object **, bool);

extern zcfgRet_t WANDslDiagObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANDslDiagObjSet(char *, int, struct json_object *, struct json_object *);

extern zcfgRet_t WANConnDevObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANConnDevObjAdd(char *, int *);
extern zcfgRet_t WANConnDevObjDel(char *);

extern zcfgRet_t WANDslLinkConfObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANDslLinkConfObjSet(char *, int, struct json_object *, struct json_object *);

extern zcfgRet_t WANPtmLinkConfObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANPtmLinkConfObjSet(char *, int, struct json_object *, struct json_object *);

extern zcfgRet_t WANPtmLinkConfStObjGet(char *, int, struct json_object **, bool);

extern zcfgRet_t WANEthLinkConfObjGet(char *, int, struct json_object **, bool);

extern zcfgRet_t WANIpConnObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANIpConnObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t WANIpConnObjAdd(char *, int *);
extern zcfgRet_t WANIpConnObjDel(char *);
extern zcfgRet_t WANIpConnObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int WANIpConnObjAttrGet(char *, int, char *);
extern zcfgRet_t WANIpConnObjAttrSet(char *, int, char *, int , struct json_object *);


/* InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANIPConnection.i.DHCPClient */
extern zcfgRet_t DhcpClientObjGet(char *, int, struct json_object **, bool);
extern int DhcpClientObjAttrGet(char *, int , char *);
extern zcfgRet_t DhcpClientObjAttrSet(char *, int, char *, int , struct json_object *);
extern zcfgRet_t DhcpClientObjNotify(char *, char *, struct json_object *, int , struct json_object **);
extern zcfgRet_t DhcpClientSentOptObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t DhcpClientSentOptObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t DhcpClientSentOptObjAdd(char *, int *);
extern zcfgRet_t DhcpClientSentOptObjDel(char *);
extern zcfgRet_t DhcpClientOptObjNotify(char *, char *, struct json_object *, int , struct json_object **);
extern int DhcpClientSentOptObjAttrGet(char *, int , char *);
extern zcfgRet_t DhcpClientSentOptObjAttrSet(char *, int, char *, int , struct json_object *);
extern zcfgRet_t DhcpClientReqOptObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t DhcpClientReqOptObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t DhcpClientReqOptObjAdd(char *, int *);
extern zcfgRet_t DhcpClientReqOptObjDel(char *);
extern int DhcpClientReqOptObjAttrGet(char *, int , char *);
extern zcfgRet_t DhcpClientReqOptObjAttrSet(char *, int, char *, int , struct json_object *);

extern zcfgRet_t WANPppConnObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANPppConnObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t WANPppConnObjAdd(char *, int *);
extern zcfgRet_t WANPppConnObjDel(char *);
extern zcfgRet_t WANPppConnObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int WANPppConnObjAttrGet(char *, int, char *);
extern zcfgRet_t WANPppConnObjAttrSet(char *, int, char *, int , struct json_object *);
extern zcfgRet_t WANIpPppConnObjAttrSet(char *, int , char *, int , struct json_object *);

/* InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANIPConnection.i.X_ZYXEL_MLD */
/* InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANPPPConnection.i.X_ZYXEL_MLD */
extern zcfgRet_t WANConnMldObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANConnMldObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t WANConnMldObjNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int WANConnMldObjAttrGet(char *, int, char *);
extern zcfgRet_t WANConnMldObjAttrSet(char *, int, char *, int , struct json_object *);

/* InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANIPConnection.i.PortMapping.i */
/* InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANPPPConnection.i.PortMapping.i */
extern zcfgRet_t WANPortMappingObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANPortMappingSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t WANPortMappingAdd(char *, int *);
extern zcfgRet_t WANPortMappingDel(char *);
extern zcfgRet_t WANPortMappingNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int WANPortMappingAttrGet(char *, int, char *);
extern zcfgRet_t WANPortMappingAttrSet(char *, int, char *, int , struct json_object *);

/* InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANIPConnection.i.X_ZYXEL_PortTriggering.i */
/* InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANPPPConnection.i.X_ZYXEL_PortTriggering.i */
extern zcfgRet_t WANPortTriggerObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANPortTriggerSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t WANPortTriggerAdd(char *, int *);
extern zcfgRet_t WANPortTriggerDel(char *);
extern zcfgRet_t WANPortTriggerNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int WANPortTriggerAttrGet(char *, int, char *);
extern zcfgRet_t WANPortTriggerAttrSet(char *, int, char *, int , struct json_object *);

/* InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANIPConnection.i.X_ZYXEL_AddrMapping.i */
/* InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANPPPConnection.i.X_ZYXEL_AddrMapping.i */
extern zcfgRet_t WANAddrMappingObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANAddrMappingSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t WANAddrMappingAdd(char *, int *);
extern zcfgRet_t WANAddrMappingDel(char *);
extern zcfgRet_t WANAddrMappingNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int WANAddrMappingAttrGet(char *, int, char *);
extern zcfgRet_t WANAddrMappingAttrSet(char *, int, char *, int , struct json_object *);

/* InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANIPConnection.i.Stats */
/* InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANPPPConnection.i.Stats */
extern zcfgRet_t WANConnStObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANConnStObjNotify(char *, char *, struct json_object *, int , struct json_object **);
extern int WANConnStObjAttrGet(char *, int , char *);
extern zcfgRet_t WANConnStObjAttrSet(char *, int, char *, int , struct json_object *);

/* InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANATMF5LoopbackDiagnostics*/
extern zcfgRet_t WANAtmF5LoConfObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANAtmF5LoConfObjSet(char *, int, struct json_object *, struct json_object *);

/* InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.X_ZYXEL_WANATMF4LoopbackDiagnostics*/
extern zcfgRet_t WANAtmF4LoConfObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANAtmF4LoConfObjSet(char *, int, struct json_object *, struct json_object *);

/* InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANIPConnection.i.X_ZYXEL_IPv6Address.i.*/
extern zcfgRet_t WANIpv6AddrObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANIpv6AddrObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t WANIpv6AddrObjAdd(char *, int *);
extern zcfgRet_t WANIpv6AddrObjDel(char *);

/* InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANIPConnection.i.X_ZYXEL_IPv6Prefix.i.*/
extern zcfgRet_t WANIpv6PrefixObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANIpv6PrefixObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t WANIpv6PrefixObjAdd(char *, int *);
extern zcfgRet_t WANIpv6PrefixObjDel(char *);

/* InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANIPConnection.i.X_ZYXEL_DHCPv6Client.*/
extern zcfgRet_t WANIpv6DhcpV6ObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANIpv6DhcpV6ObjSet(char *, int, struct json_object *, struct json_object *);

/* InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANIPConnection.i.X_ZYXEL_IPv6rd..*/
extern zcfgRet_t WANIpv6RdObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANIpv6RdObjSet(char *, int, struct json_object *, struct json_object *);

#ifdef ROUTEINFO_INTERFACE
/*InternetGatewayDevice.LANDevice.i.LANHostConfigManagement.IPInterface.i.X_ZYXEL_RouteInformation.*/
extern zcfgRet_t WANIpIntfRouteInfoObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANIpIntfRouteInfoObjSet(char *, int, struct json_object *, struct json_object *);
#endif

/* InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANPPPConnection.i.X_ZYXEL_IPv6Address.i.*/
extern zcfgRet_t WANPppv6AddrObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANPppv6AddrObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t WANPppv6AddrObjAdd(char *, int *);
extern zcfgRet_t WANPppv6AddrObjDel(char *);

/* InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANPPPConnection.i.X_ZYXEL_IPv6Prefix.i.*/
extern zcfgRet_t WANPppv6PrefixObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANPppv6PrefixObjSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t WANPppv6PrefixObjAdd(char *, int *);
extern zcfgRet_t WANPppv6PrefixObjDel(char *);

/* InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANPPPConnection.i.X_ZYXEL_DHCPv6Client.*/
extern zcfgRet_t WANPppv6DhcpV6ObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANPppv6DhcpV6ObjSet(char *, int, struct json_object *, struct json_object *);

/* InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANPPPConnection.i.X_ZYXEL_IPv6rd..*/
extern zcfgRet_t WANPppv6RdObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANPppv6RdObjSet(char *, int, struct json_object *, struct json_object *);


#ifdef CONFIG_XPON_SUPPORT
/* InternetGatewayDevice.WANDevice.i.X_ZYZEL_WANPonInterfaceConfig*/
extern zcfgRet_t WANPonIfaceCfgObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t WANPonIfaceCfgObjSet(char *, int, struct json_object *, struct json_object *);
/* InternetGatewayDevice.WANDevice.i.X_ZYZEL_WANPonInterfaceConfig.Stats*/
extern zcfgRet_t WANPonIfaceCfgStObjGet(char *, int, struct json_object **, bool);
#endif
extern zcfgRet_t wwanObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t wwanObjSet(char *, int, struct json_object *, struct json_object *, char *);
extern zcfgRet_t wwanObjStatsGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t wwanEmailObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t wwanEmailObjSet(char *, int, struct json_object *, struct json_object *, char *);


