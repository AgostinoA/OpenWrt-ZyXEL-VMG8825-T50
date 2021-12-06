tr98Parameter_t para_qMgmt[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "MaxQueues", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "MaxClassificationEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ClassificationNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "MaxAppEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "AppNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "MaxFlowEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "FlowNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "MaxPolicerEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "PolicerNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "MaxQueueEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "QueueNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "QueueStatsNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "X_ZYXEL_MaxShaperEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "X_ZYXEL_ShaperNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "DefaultForwardingPolicy", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "DefaultTrafficClass", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "DefaultPolicer", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "DefaultQueue", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "DefaultDSCPMark", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "DefaultEthernetPriorityMark", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "AvailableAppList", PARAMETER_ATTR_READONLY, 1024, json_type_string},
	{ "X_ZYXEL_UpRate", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DownRate", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_AutoMapType", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Cls[] = {	
	//{ "ClassificationKey", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "ClassificationEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "ClassificationStatus", PARAMETER_ATTR_READONLY, 10, json_type_string},
	//{ "Alias", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "ClassificationOrder", PARAMETER_ATTR_WRITE, 0, json_type_uint32},	
	{ "ClassInterface", PARAMETER_ATTR_WRITE, 257, json_type_string},	
	{ "DestIP", PARAMETER_ATTR_WRITE, 17, json_type_string},	
	{ "DestMask", PARAMETER_ATTR_WRITE, 17, json_type_string},	
	{ "DestIPExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "SourceIP", PARAMETER_ATTR_WRITE, 17, json_type_string},	
	{ "SourceMask", PARAMETER_ATTR_WRITE, 17, json_type_string},	
	{ "SourceIPExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "Protocol", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "ProtocolExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "DestPort", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "DestPortRangeMax", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "DestPortExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "SourcePort", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "SourcePortRangeMax", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "SourcePortExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "SourceMACAddress", PARAMETER_ATTR_WRITE, 19, json_type_string},	
	{ "SourceMACMask", PARAMETER_ATTR_WRITE, 19, json_type_string},	
	{ "SourceMACExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "DestMACAddress", PARAMETER_ATTR_WRITE, 19, json_type_string},	
	{ "DestMACMask", PARAMETER_ATTR_WRITE, 19, json_type_string},	
	{ "DestMACExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "Ethertype", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "EthertypeExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "SSAP", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "SSAPExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "DSAP", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "DSAPExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "LLCControl", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "LLCControlExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "SNAPOUI", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "SNAPOUIExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "SourceVendorClassID", PARAMETER_ATTR_WRITE, 257, json_type_string},	
	{ "SourceVendorClassIDExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "SourceVendorClassIDMode", PARAMETER_ATTR_WRITE, 11, json_type_string},	
	{ "DestVendorClassID", PARAMETER_ATTR_WRITE, 257, json_type_string},	
	{ "DestVendorClassIDExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "DestVendorClassIDMode", PARAMETER_ATTR_WRITE, 11, json_type_string},	
	{ "SourceClientID", PARAMETER_ATTR_WRITE, 257, json_type_string},	
	{ "SourceClientIDExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "DestClientID", PARAMETER_ATTR_WRITE, 257, json_type_string},	
	{ "DestClientIDExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "SourceUserClassID", PARAMETER_ATTR_WRITE, 257, json_type_string},	
	{ "SourceUserClassIDExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "DestUserClassID", PARAMETER_ATTR_WRITE, 257, json_type_string},	
	{ "DestUserClassIDExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "SourceVendorSpecificInfo", PARAMETER_ATTR_WRITE, 257, json_type_string},	
	{ "SourceVendorSpecificInfoExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "SourceVendorSpecificInfoEnterprise", PARAMETER_ATTR_WRITE, 0, json_type_uint32},	
	{ "SourceVendorSpecificInfoSubOption", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	//{ "SourceVendorSpecificInfoMode", PARAMETER_ATTR_WRITE, 11, json_type_string},	
	{ "DestVendorSpecificInfo", PARAMETER_ATTR_WRITE, 257, json_type_string},	
	{ "DestVendorSpecificInfoExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "DestVendorSpecificInfoEnterprise", PARAMETER_ATTR_WRITE, 0, json_type_uint32},	
	{ "DestVendorSpecificInfoSubOption", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	//{ "DestVendorSpecificInfoMode", PARAMETER_ATTR_WRITE, 11, json_type_string},	
	{ "TCPACK", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "TCPACKExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "IPLengthMin", PARAMETER_ATTR_WRITE, 0, json_type_uint32},	
	{ "IPLengthMax", PARAMETER_ATTR_WRITE, 0, json_type_uint32},	
	{ "IPLengthExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "DSCPCheck", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "DSCPExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "DSCPMark", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "EthernetPriorityCheck", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "EthernetPriorityExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "EthernetPriorityMark", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "VLANIDCheck", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "VLANIDExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "OutOfBandInfo", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "ForwardingPolicy", PARAMETER_ATTR_WRITE, 0, json_type_uint32},	
	{ "TrafficClass", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "ClassPolicer", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	//{ "ClassQueue", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "ClassApp", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "X_ZYXEL_VLANIDAction", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_VLANIDMark", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_Name", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ "X_ZYXEL_SourceClientIDType", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ "X_ZYXEL_DefaultClass", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_Service", PARAMETER_ATTR_WRITE, 129, json_type_string},
	{ "X_ZYXEL_ServiceExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0}
};

tr98Parameter_t para_Policer[] = {
	//{ "PolicerKey", PARAMETER_ATTR_READONLY, 0, json_type_},
	{ "PolicerEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "PolicerStatus", PARAMETER_ATTR_READONLY, 10, json_type_string},
	//{ "Alias", PARAMETER_ATTR_, 0, json_type_},
	{ "CommittedRate", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "CommittedBurstSize", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "ExcessBurstSize", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "PeakRate", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "PeakBurstSize", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "MeterType", PARAMETER_ATTR_WRITE, 21, json_type_string},
	{ "PossibleMeterTypes", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "ConformingAction", PARAMETER_ATTR_WRITE, 13, json_type_string},
	{ "PartialConformingAction", PARAMETER_ATTR_WRITE, 13, json_type_string},
	{ "NonConformingAction", PARAMETER_ATTR_WRITE, 13, json_type_string},
	//{ "CountedPackets", PARAMETER_ATTR_READONLY, 0, json_type_},
	//{ "CountedBytes", PARAMETER_ATTR_READONLY, 0, json_type_},
	{ "TotalCountedPackets", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TotalCountedBytes", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ConformingCountedPackets", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ConformingCountedBytes", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "PartiallyConformingCountedPackets", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "PartiallyConformingCountedBytes", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "NonConformingCountedPackets", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "NonConformingCountedBytes", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "X_ZYXEL_Name", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ NULL, 0, 0}
};

tr98Parameter_t para_Que[] = {	
	//{ "QueueKey", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "QueueEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "QueueStatus", PARAMETER_ATTR_READONLY, 10, json_type_string},
	//{ "Alias", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "TrafficClasses", PARAMETER_ATTR_WRITE, 257, json_type_string},	
	{ "QueueInterface", PARAMETER_ATTR_WRITE, 257, json_type_string},	
	{ "QueueBufferLength", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "QueueWeight", PARAMETER_ATTR_WRITE, 0, json_type_uint32},	
	{ "QueuePrecedence", PARAMETER_ATTR_WRITE, 0, json_type_uint32},	
	{ "REDThreshold", PARAMETER_ATTR_WRITE, 0, json_type_uint32},	
	{ "REDPercentage", PARAMETER_ATTR_WRITE, 0, json_type_uint32},	
	{ "DropAlgorithm", PARAMETER_ATTR_WRITE, 6, json_type_string},	
	{ "SchedulerAlgorithm", PARAMETER_ATTR_WRITE, 5, json_type_string},	
	{ "ShapingRate", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "ShapingBurstSize", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_Name", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ NULL, 0, 0}
};

tr98Parameter_t para_Shaper[] = {	
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "Status", PARAMETER_ATTR_READONLY, 0, json_type_boolean},	
	{ "Alias", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "Interface", PARAMETER_ATTR_WRITE, 257, json_type_string},	
	{ "ShapingRate", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "ShapingBurstSize", PARAMETER_ATTR_WRITE, 0, json_type_uint32},	
	{ NULL, 0, 0}
};

/* InternetGatewayDevice.QueueManagement */
extern zcfgRet_t qMgmtObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t qMgmtSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t qMgmtNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int qMgmtAttrGet(char *, int, char *);
extern zcfgRet_t qMgmtAttrSet(char *, int, char *, int , struct json_object *);

/* InternetGatewayDevice.QueueManagement.Queue.i */
extern zcfgRet_t qMgmtQueObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t qMgmtQueSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t qMgmtQueAdd(char *, int *);
extern zcfgRet_t qMgmtQueDel(char *);
extern zcfgRet_t qMgmtQueNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int qMgmtQueAttrGet(char *, int, char *);
extern zcfgRet_t qMgmtQueAttrSet(char *, int, char *, int , struct json_object *);
extern zcfgRet_t qMgmtQueParmGurd(const char *, const char *, struct json_object *, struct json_object *, char **);

extern zcfgRet_t qMgmtPolicerGet(char *, int , struct json_object **, bool );
extern zcfgRet_t qMgmtPolicerSet(char *, int , struct json_object *, struct json_object *, char *);
extern zcfgRet_t qMgmtPolicerAdd(char *, int *);
extern zcfgRet_t qMgmtPolicerDel(char *);

/* InternetGatewayDevice.QueueManagement.Classification.i */
extern zcfgRet_t qMgmtClsObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t qMgmtClsSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t qMgmtClsAdd(char *, int *);
extern zcfgRet_t qMgmtClsDel(char *);
extern zcfgRet_t qMgmtClsNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int qMgmtClsAttrGet(char *, int, char *);
extern zcfgRet_t qMgmtClsAttrSet(char *, int, char *, int , struct json_object *);
extern zcfgRet_t qMgmtClsParmGurd(const char *, const char *, struct json_object *, struct json_object *, char **);

/* InternetGatewayDevice.QueueManagement.X_ZYXEL_Shaper.i */
extern zcfgRet_t qMgmtShaperObjGet(char *, int, struct json_object **, bool);
extern zcfgRet_t qMgmtShaperSet(char *, int, struct json_object *, struct json_object *);
extern zcfgRet_t qMgmtShaperAdd(char *, int *);
extern zcfgRet_t qMgmtShaperDel(char *);
extern zcfgRet_t qMgmtShaperNotify(char *, char *, struct json_object *, int, struct json_object **);
extern int qMgmtShaperAttrGet(char *, int, char *);
extern zcfgRet_t qMgmtShaperAttrSet(char *, int, char *, int , struct json_object *);




