tr98Parameter_t para_Firewall[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_IPv4_Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_IPv6_Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Config", PARAMETER_ATTR_WRITE, 9, json_type_string},
	{ "AdvancedLevel", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "Type", PARAMETER_ATTR_READONLY, 10, json_type_string},
	{ "Version", PARAMETER_ATTR_READONLY, 17, json_type_string},
	{ "LastChange", PARAMETER_ATTR_READONLY, 21, json_type_time},
	{ "LevelNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ChainNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};


tr98Parameter_t para_FirewallLevel[] = {
	{ "Alias", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "Name", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "Description", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "Order", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Chain", PARAMETER_ATTR_READONLY, 25, json_type_string},
	{ "PortMappingEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "DefaultPolicy", PARAMETER_ATTR_WRITE, 7, json_type_string},
	{ "DefaultLogPolicy", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_DefaultConfig", PARAMETER_ATTR_WRITE, 9, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_FirewallChain[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Alias", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "Name", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "Creator", PARAMETER_ATTR_READONLY, 23, json_type_string},
	{ "RuleNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_FirewallChainRule[] ={
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 20, json_type_string},
	{ "Order", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Alias", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "Description", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "Target", PARAMETER_ATTR_WRITE, 12, json_type_string},
	{ "TargetChain", PARAMETER_ATTR_WRITE, 25, json_type_string},
	{ "Log", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "CreationDate", PARAMETER_ATTR_READONLY, 21, json_type_time},
	{ "ExpiryDate", PARAMETER_ATTR_WRITE, 21, json_type_time},
	{ "SourceInterface", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "SourceInterfaceExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "SourceAllInterfaces", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "DestInterface", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "DestInterfaceExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "DestAllInterfaces", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "IPVersion", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "DestIP", PARAMETER_ATTR_WRITE, 46, json_type_string},
	{ "DestMask", PARAMETER_ATTR_WRITE, 50, json_type_string},
	{ "DestIPExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "SourceIP", PARAMETER_ATTR_WRITE, 46, json_type_string},
	{ "SourceMask", PARAMETER_ATTR_WRITE, 50, json_type_string},
	{ "SourceIPExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Protocol", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "ProtocolExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "DestPort", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "DestPortRangeMax", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "DestPortExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "SourcePort", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "SourcePortRangeMax", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "SourcePortExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "DSCP", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "DSCPExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_Direction", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ "X_ZYXEL_ICMPType", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "X_ZYXEL_ICMPTypeCode", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "X_ZYXEL_TCPFlagMask", PARAMETER_ATTR_WRITE, 24, json_type_string},
	{ "X_ZYXEL_TCPFlagComp", PARAMETER_ATTR_WRITE, 24, json_type_string},
	{ "X_ZYXEL_LimitRate", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_LimitRateUnit", PARAMETER_ATTR_WRITE, 7, json_type_string},
	{ "X_ZYXEL_ScheduleRule", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
