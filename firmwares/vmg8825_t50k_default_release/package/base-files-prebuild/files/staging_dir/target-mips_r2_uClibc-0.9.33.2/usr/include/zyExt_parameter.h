
tr98Parameter_t para_extend[] = {
#ifdef ZYXEL_ACS_WPS_ACTIVATION
	{ "WPSRunning", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "WPSApIndex", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "WPSRunningStatus", PARAMETER_ATTR_READONLY, 257, json_type_string},
#endif
	{ NULL, 0, 0}
};

tr98Parameter_t para_Dns[] = {
	{ "SupportedRecordTypes", PARAMETER_ATTR_READONLY, 14, json_type_string},
	{ "X_ZYXEL_BoundInterfaceList", PARAMETER_ATTR_WRITE, 256, json_type_string},
	{ "X_ZYXEL_RedirectLANSideDNSQuery", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_ActiveDNSServers", PARAMETER_ATTR_READONLY, 256, json_type_string},
	{ "X_ZYXEL_DNSQueryScenario", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0}
};

tr98Parameter_t para_DnsRtEntry[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "DomainName", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "Interface", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "RouteInterface", PARAMETER_ATTR_READONLY, 33, json_type_string},
	{ "DNSServers", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "SubnetMask", PARAMETER_ATTR_WRITE, 18, json_type_string},
	{ NULL, 0, 0}
};

tr98Parameter_t para_DnsEntry[] = {
	{ "HostName", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "IPv4Address", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ NULL, 0, 0}
};

tr98Parameter_t para_DDns[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "ServiceProvider", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "DDNSType", PARAMETER_ATTR_WRITE, 9, json_type_string},
	{ "HostName", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "UserName", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "Password", PARAMETER_ATTR_WRITE | PARAMETER_ATTR_PASSWORD, 65, json_type_string},
	{ "IPAddressPolicy", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "UserIPAddress", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "Wildcard", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Offline", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "AuthenticationResult", PARAMETER_ATTR_READONLY, 17, json_type_string},
	{ "UpdatedTime", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "DynamicIP", PARAMETER_ATTR_WRITE, 129, json_type_string},
	{ "UpdateURL", PARAMETER_ATTR_WRITE, 256, json_type_string},
	{ "ConnectionType", PARAMETER_ATTR_WRITE, 12, json_type_string},
	{ NULL, 0, 0}
};
#if defined(ISKON_CUSTOMIZATION) || defined(ZYXEL_SP_DOMAIN_TIMER)
tr98Parameter_t para_RemoMgmt[] = {
#ifdef ISKON_CUSTOMIZATION
	{ "BoundWANInterfaceList", PARAMETER_ATTR_WRITE, 257, json_type_string},
#endif
#ifdef ZYXEL_SP_DOMAIN_TIMER
	{ "SPRemoteTimer", PARAMETER_ATTR_WRITE, 0, json_type_int},
#endif
	{ NULL, 0, 0}
};
#endif
tr98Parameter_t para_RemoSrv[] = {
	{ "Name", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Protocol", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "Port", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "Mode", PARAMETER_ATTR_WRITE, 11, json_type_string},
	{ "OldMode", PARAMETER_ATTR_WRITE, 11, json_type_string},
	{ "RestartDeamon", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "BoundInterfaceList", PARAMETER_ATTR_WRITE, 129, json_type_string},
	{ "TrustAll", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "DisableSshPasswordLogin", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0}
};

tr98Parameter_t para_SpRemoSrv[] = {
	{ "Name", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
#ifdef ZYXEL_SP_DOMAIN_TIMER
	{ "TimerEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
#endif
	{ "Port", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ NULL, 0, 0}
};

tr98Parameter_t para_RemoTrustDomain[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "IPAddress", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "SubnetMask", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ NULL, 0, 0}
};

tr98Parameter_t para_SpTrustDomain[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "IPAddress", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "SubnetMask", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ NULL, 0, 0}
};

tr98Parameter_t para_Igmp[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "IgmpVersion", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "QueryInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "QueryResponseInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "LastMemberQueryInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "RobustnessValue", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "MaxGroups", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "MaxSources", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "MaxMembers", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "LanToLanEnable", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "FastLeave", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "JoinImmediate", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "SnoopingEnable", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Interface", PARAMETER_ATTR_READONLY, TR98_MAX_OBJ_NAME_LENGTH*5, json_type_string},
	{ "ifName", PARAMETER_ATTR_READONLY, 321, json_type_string},
	{ "Status", PARAMETER_ATTR_READONLY, 19, json_type_string},
	{ "SnoopingBridgeIfName", PARAMETER_ATTR_READONLY, 101, json_type_string},
	{ NULL, 0, 0}
};

#if defined(SUNRISE_RANDOM_PASSWORD) || defined(SOL_TR69_LOGINACCOUNT) || defined(ZYXEL_SUPPORT_TR98_LOGIN_ACCOUNT)
tr98Parameter_t para_LogCfgGp[] = {
	{ "Level", PARAMETER_ATTR_READONLY, 17, json_type_string},
	{ "Page", PARAMETER_ATTR_WRITE, 2049, json_type_string},
	{ NULL, 0, 0}
};
tr98Parameter_t para_LogCfgGpAccount[] = {
	{ "Enabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "EnableQuickStart", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Username", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "Password", PARAMETER_ATTR_WRITE | PARAMETER_ATTR_PASSWORD, 257, json_type_string},
	{ "AutoShowQuickStart", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Page", PARAMETER_ATTR_WRITE, 2049, json_type_string},
	{ "DefaultPassword", PARAMETER_ATTR_WRITE | PARAMETER_ATTR_PASSWORD, 257, json_type_string},
	{ "ResetDefaultPassword", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "PasswordHash", PARAMETER_ATTR_READONLY | PARAMETER_ATTR_PASSWORD, 17, json_type_string},
	{ "AccountCreateTime", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "AccountRetryTime", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "AccountIdleTime", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "AccountLockTime", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "RemoHostAddress", PARAMETER_ATTR_WRITE, 49, json_type_string},
	{ "DotChangeDefPwd", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "AutoGenPwdBySn", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "GetConfigByFtp", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Privilege", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "SshKeyBaseAuthPublicKey", PARAMETER_ATTR_WRITE | PARAMETER_ATTR_PASSWORD, 4097, json_type_string},
	{ NULL, 0, 0}
};
#endif

tr98Parameter_t para_LogSetting[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "LogServer", PARAMETER_ATTR_WRITE, 128, json_type_string},
	{ "UDPPort", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "ZCFG_LOG_Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "LogMode", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "Interval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "RemoteLogFormat", PARAMETER_ATTR_WRITE, 256, json_type_string},
	{ NULL, 0, 0}
};

tr98Parameter_t para_LogClassify[] = {
	{ "Name", PARAMETER_ATTR_READONLY, 30, json_type_string},
	{ "Describe", PARAMETER_ATTR_READONLY, 51, json_type_string},
	{ "File", PARAMETER_ATTR_READONLY, 51, json_type_string},
	{ NULL, 0, 0}
};

tr98Parameter_t para_LogCategory[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Name", PARAMETER_ATTR_READONLY, 30, json_type_string},
	{ "Describe", PARAMETER_ATTR_READONLY, 50, json_type_string},
	{ "Level", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Filter", PARAMETER_ATTR_WRITE, 256, json_type_string},
	{ "LocalLogFormat", PARAMETER_ATTR_WRITE, 256, json_type_string},
	{ NULL, 0, 0}
};

tr98Parameter_t para_MacFilter[] = {
	{ "MaxNumberOfEntries", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Restrict", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_MacFilter_WhiteList[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "MACAddress", PARAMETER_ATTR_WRITE, 18, json_type_string},
	{ "HostName", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_ParenCtl[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0}
};

tr98Parameter_t para_ParenCtlProf[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Name", PARAMETER_ATTR_WRITE, 64, json_type_string},
	{ "WebRedirect", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "ServicePolicy", PARAMETER_ATTR_WRITE, 11, json_type_string},
	{ "Type", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "MACAddressList", PARAMETER_ATTR_WRITE, 128, json_type_string},
	{ "ScheduleRuleList", PARAMETER_ATTR_WRITE, 64, json_type_string},
	{ "URLFilter", PARAMETER_ATTR_WRITE, 580, json_type_string},
	{ "NetworkServiceList", PARAMETER_ATTR_WRITE, 1024, json_type_string},
	{ NULL, 0, 0}
};

#ifdef ZyXEL_IPP_PRINTSERVER
tr98Parameter_t para_Ipp_PrintServer[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "IppName", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ "IppMake", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ NULL, 0, 0}
};
#endif

#ifdef ONECONNECT
tr98Parameter_t para_OneConnect[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_SpeedTestInfo[] = {
	{ "Start", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "UploadSpeedResult", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ "DownloadSpeedResult", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ NULL, 0, 0, 0}
};
#endif

#ifdef ZYXEL_AP_STEERING
tr98Parameter_t para_ApSteering[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "WiFi_24G_NormalToBad_Threshold", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "WiFi_24G_NormalToGood_Threshold", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "WiFi_24G_Upgrade_Threshold", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "WiFi_5G_NormalToBad_Threshold", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "WiFi_5G_NormalToGood_Threshold", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "RE_Threshold_Adjustment", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "Idle_Pkt_Threshold", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "STA_Num_Difference_Threshold", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "SteeringTime", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "ProhibitAfterSteering", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "ClearSteeringStatus", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "ScanOtherAPsInterval", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "LoadBalancingInterval", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "LogLevel", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "Prohibit_Steering_OverWDS_AP", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "DisableSteering", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};
#endif //#ifdef ZYXEL_AP_STEERING

#ifdef PROXIMITY_SENSOR_SUPPORT
tr98Parameter_t para_ProximitySensor[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};
#endif //#ifdef PROXIMITY_SENSOR_SUPPORT

tr98Parameter_t para_SysInfo[] = {
	{ "HostName", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "IsHostNameModify", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "DomainName", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "Contact", PARAMETER_ATTR_WRITE, 101, json_type_string},
	{ "Location", PARAMETER_ATTR_WRITE, 51, json_type_string},
	{ "OnlineGuide", PARAMETER_ATTR_WRITE, 129, json_type_string},
#ifdef CBT_CUSTOMIZATION
	{ "CBT_AccountReset", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
#endif
	{ NULL, 0, 0, 0}
};

#ifdef ZYXEL_SFP_MODULE_SUPPORT

tr98Parameter_t para_GponInfo[] = {
	{ "RxPowerSignal", PARAMETER_ATTR_READONLY, 16, json_type_string},
	{ "TxPowerSignal", PARAMETER_ATTR_READONLY, 16, json_type_string},
	{ "Temperature", PARAMETER_ATTR_READONLY, 16, json_type_string},
	{ "SFP_Vendor", PARAMETER_ATTR_READONLY, 16, json_type_string},
	{ "SFP_Model", PARAMETER_ATTR_READONLY, 16, json_type_string},
	{ "SFP_Serial", PARAMETER_ATTR_READONLY, 16, json_type_string},
	{ "SFP_Presence", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};
#endif

tr98Parameter_t para_Snmp[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Port", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "ROCommunity", PARAMETER_ATTR_WRITE, 51, json_type_string},
	{ "RWCommunity", PARAMETER_ATTR_WRITE, 51, json_type_string},
	{ "TrapCommunity", PARAMETER_ATTR_WRITE, 51, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_SnmpTrap[] = {
	{ "Host", PARAMETER_ATTR_WRITE, 256, json_type_string},
	{ "Port", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "TarpVer", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Tr064[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_EmailSrv[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "SMTPServerAddress", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "SMTPServerPort", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "AuthUser", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "AuthPass", PARAMETER_ATTR_WRITE | PARAMETER_ATTR_PASSWORD, 65, json_type_string},
	{ "EmailAddress", PARAMETER_ATTR_WRITE, 129, json_type_string},
	{ "SMTPSecurity", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "RequiresTLS", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_EmailEvent[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Event", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "EmailTo", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "EmailSubject", PARAMETER_ATTR_WRITE, 129, json_type_string},
	{ "EmailBody", PARAMETER_ATTR_WRITE, 1025, json_type_string},
	{ "SericeRef", PARAMETER_ATTR_WRITE, 129, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_VlanGroup[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "GroupName", PARAMETER_ATTR_WRITE, 129, json_type_string},
	{ "VlanId", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "BrRefKey", PARAMETER_ATTR_WRITE, 9, json_type_string},
	{ "IntfList", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "TagList", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_8021ag[] = {
	{ "MDLevel", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "IsPtmLink", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "VLANID", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "DestMacAddress", PARAMETER_ATTR_WRITE, 18, json_type_string},
	{ "SendLoopBack", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "LoopBackResult", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "SendLinkTrace", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "LinkTraceResult", PARAMETER_ATTR_WRITE, 321, json_type_string},
#ifdef ZYXEL_ETHOAM_TMSCTL
	{ "Enabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Y1731Mode", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Interface", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "MDName", PARAMETER_ATTR_WRITE, 129, json_type_string},
	{ "MAID", PARAMETER_ATTR_WRITE, 129, json_type_string},
	{ "LMPID", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "RMPID", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "CCMEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "CCMInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "LinkTraceTTL", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "TmsPid", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
#endif
	{ NULL, 0, 0, 0}
};

#ifdef ZYXEL_ETHOAM_TMSCTL
tr98Parameter_t para_8023ah[] = {
	{ "Enabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Interface", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "VariableRetrievalEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "LinkEventsEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "RemoteLoopbackEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "ActiveModeEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "AutoEventEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "OAMID", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "TmsPid", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
#endif

tr98Parameter_t para_Sec[] = {
	{ "CertificateNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_SecCert[] = {
	{ "X_ZYXEL_Name", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_Type", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_Certificate", PARAMETER_ATTR_WRITE, 4097, json_type_string},
	{ "X_ZYXEL_PrivateKey", PARAMETER_ATTR_WRITE, 4097, json_type_string},
	{ "X_ZYXEL_SigningRequest", PARAMETER_ATTR_WRITE, 4097, json_type_string},
	{ "X_ZYXEL_CommonName", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "X_ZYXEL_OrgName", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_StateName", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_CountryName", PARAMETER_ATTR_WRITE, 3, json_type_string},
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "LastModif", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ "SerialNumber", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "Issuer", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "NotBefore", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ "NotAfter", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ "Subject", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "SubjectAlt", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "SignatureAlgorithm", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Samba[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "PidFileName", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Upnp[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_NATTEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};

#ifdef ZYXEL_LANDING_PAGE_FEATURE
tr98Parameter_t para_Landing_Page[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "URL", PARAMETER_ATTR_WRITE, 256, json_type_string},
	{ NULL, 0, 0, 0}
};
#endif

tr98Parameter_t para_Feature_Flag[] = {
	{ "Customer", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "checkDuplicateVlan", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "WANPriority", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ "SfpDelayTimes", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "SipDelayTimes", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	// altibox request
	{ "DownloadScriptTR69", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "FactoryResetOnUpgrade", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_GUI_Customization[] = {
	{ "Flag1", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "Flag2", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "BlockSpecialChar", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "BlockChar", PARAMETER_ATTR_WRITE, 128, json_type_string},
	{ "AllowFilter", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "AllowCharList", PARAMETER_ATTR_WRITE, 128, json_type_string},
	{ "EthWanAsLan", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "HideChangeDefault", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "HideSkipPassword", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};

#ifdef ZYXEL_EASYMESH
tr98Parameter_t para_EasyMesh[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};
#endif //#ifdef ZYXEL_ONESSID

#ifdef BUILD_SONIQ
tr98Parameter_t para_Qsteer[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "MinPhyRate", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "MaxPhyRate", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "WPS_Mode", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
#endif //#ifdef BUILD_SONIQ

#ifdef ZYXEL_ONESSID
tr98Parameter_t para_OneSsid[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};
#endif //#ifdef ZYXEL_ONESSID

#ifdef ZYXEL_SFP_POWER_MGMT
tr98Parameter_t para_SfpMgmt[] = {
	{ "Status", PARAMETER_ATTR_READONLY, 32, json_type_string},
	{ "Timer", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
#endif //#ifdef ZYXEL_SFP_POWER_MGMT

#ifdef ZYXEL_TR69_DATA_USAGE
tr98Parameter_t para_DataUsage[] = {
	{ "DataUsageUpdate", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_DataUsageLan[] = {
	{ "Timestamp", PARAMETER_ATTR_WRITE, 64, json_type_string},
	{ "Upload_Mbps", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ "Download_Mbps", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_DataUsageWan[] = {
	{ "Timestamp", PARAMETER_ATTR_WRITE, 64, json_type_string},
	{ "Upload_Mbps", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ "Download_Mbps", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ NULL, 0, 0, 0}
};
#endif
