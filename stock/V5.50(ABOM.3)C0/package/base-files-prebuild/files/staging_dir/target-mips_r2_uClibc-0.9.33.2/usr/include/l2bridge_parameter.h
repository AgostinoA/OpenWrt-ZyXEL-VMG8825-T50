tr98Parameter_t para_L2Br[] = {	
	{ "MaxBridgeEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "MaxDBridgeEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "MaxQBridgeEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "MaxVLANEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "MaxFilterEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "MaxMarkingEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "BridgeNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "FilterNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "MarkingNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "AvailableInterfaceNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ NULL, 0, 0, 0}
};
	
tr98Parameter_t para_Br[] = {	
	{ "BridgeKey", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "BridgeStandard", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "BridgeEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "BridgeStatus", PARAMETER_ATTR_READONLY, 10, json_type_string},	
	{ "BridgeName", PARAMETER_ATTR_WRITE, 65, json_type_string},	
	{ "VLANID", PARAMETER_ATTR_WRITE, 0, json_type_uint32},	
	{ "PortNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "VLANNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	//{ "X_ZYXEL_BridgeClear", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Port[] = {	
	{ "PortEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "PortInterface", PARAMETER_ATTR_WRITE, 17, json_type_string},	
	{ "PortState", PARAMETER_ATTR_READONLY, 12, json_type_string},	
	{ "PVID", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "AcceptableFrameTypes", PARAMETER_ATTR_WRITE, 23, json_type_string},	
	{ "IngressFiltering", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Vlan[] = {	
	{ "VLANEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "VLANName", PARAMETER_ATTR_WRITE, 65, json_type_string},	
	{ "VLANID", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Filter[] = {	
	{ "FilterKey", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "FilterEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "FilterStatus", PARAMETER_ATTR_READONLY, 10, json_type_string},	
	{ "FilterBridgeReference", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	//{ "ExclusivityOrder", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "FilterInterface", PARAMETER_ATTR_WRITE, 17, json_type_string},	
	{ "VLANIDFilter", PARAMETER_ATTR_WRITE, 0, json_type_int},
	//{ "AdmitOnlyVLANTagged", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "EthertypeFilterList", PARAMETER_ATTR_WRITE, 257, json_type_string},	
	{ "EthertypeFilterExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "SourceMACAddressFilterList", PARAMETER_ATTR_WRITE, 513, json_type_string},	
	{ "SourceMACAddressFilterExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "DestMACAddressFilterList", PARAMETER_ATTR_WRITE, 513, json_type_string},	
	{ "DestMACAddressFilterExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "SourceMACFromVendorClassIDFilter", PARAMETER_ATTR_WRITE, 257, json_type_string},	
	{ "SourceMACFromVendorClassIDFilterExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "SourceMACFromVendorClassIDMode", PARAMETER_ATTR_WRITE, 11, json_type_string},	
	{ "DestMACFromVendorClassIDFilter", PARAMETER_ATTR_WRITE, 257, json_type_string},	
	{ "DestMACFromVendorClassIDFilterExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "DestMACFromVendorClassIDMode", PARAMETER_ATTR_WRITE, 11, json_type_string},	
	{ "SourceMACFromClientIDFilter", PARAMETER_ATTR_WRITE, 257, json_type_string},	
	{ "SourceMACFromClientIDFilterExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "DestMACFromClientIDFilter", PARAMETER_ATTR_WRITE, 257, json_type_string},	
	{ "DestMACFromClientIDFilterExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "SourceMACFromUserClassIDFilter", PARAMETER_ATTR_WRITE, 257, json_type_string},	
	{ "SourceMACFromUserClassIDFilterExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "DestMACFromUserClassIDFilter", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "DestMACFromUserClassIDFilterExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Mark[] = {	
	{ "MarkingKey", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "MarkingEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "MarkingStatus", PARAMETER_ATTR_READONLY, 10, json_type_string},	
	{ "MarkingReference", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "MarkingInterface", PARAMETER_ATTR_WRITE, 17, json_type_string},	
	{ "VLANIDUntag", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "VLANIDMark", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "VLANIDMarkOverride", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "EthernetPriorityMark", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	{ "EthernetPriorityOverride", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_AvaiIntf[] = {	
	{ "AvailableInterfaceKey", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "InterfaceType", PARAMETER_ATTR_READONLY, 21, json_type_string},	
	{ "InterfaceReference", PARAMETER_ATTR_READONLY, 257, json_type_string},	
	{ NULL, 0, 0, 0}
};
