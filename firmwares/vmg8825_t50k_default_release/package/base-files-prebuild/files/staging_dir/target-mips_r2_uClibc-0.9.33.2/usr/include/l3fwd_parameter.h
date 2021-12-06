tr98Parameter_t para_L3Fwd[] = {
	{ "DefaultConnectionService", PARAMETER_ATTR_WRITE, 513, json_type_string},
	{ "ForwardNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "X_ZYXEL_AutoSecureDefaultIface", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_DefaultGwInterface", PARAMETER_ATTR_READONLY, 321, json_type_string},
	{ "X_ZYXEL_IPV6ForwardNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
	
tr98Parameter_t para_Fwd[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 10, json_type_string},
	{ "Alias", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "StaticRoute", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "Type", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 9, json_type_string}, //
	{ "DestIPAddress", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ "DestSubnetMask", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ "SourceIPAddress", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ "SourceSubnetMask", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ "ForwardingPolicy", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "GatewayIPAddress", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ "Interface", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "ForwardingMetric", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "MTU", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 0, json_type_uint32}, //
	{ "X_ZYXEL_SourceMacAddress", PARAMETER_ATTR_WRITE, 18, json_type_string},
	{ "X_ZYXEL_SourceIpAddress", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ "X_ZYXEL_SourceSubnetMask", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ "X_ZYXEL_SourceIfName", PARAMETER_ATTR_WRITE, 13, json_type_string},
	{ "X_ZYXEL_Protocol", PARAMETER_ATTR_WRITE, 33, json_type_int},
	{ "X_ZYXEL_SourcePort", PARAMETER_ATTR_WRITE, 33, json_type_int},
	{ "X_ZYXEL_PolicyRouteName", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_PolicyRoute", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};
#ifdef L3IPV6FWD
tr98Parameter_t para_Ipv6Fwd[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 10, json_type_string},
	{ "Alias", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "DestIPPrefix", PARAMETER_ATTR_WRITE, 50, json_type_string},
	{ "ForwardingPolicy", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "NextHop", PARAMETER_ATTR_WRITE, 46, json_type_string},
	{ "Interface", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "Origin", PARAMETER_ATTR_READONLY, 16, json_type_string},
	{ "ForwardingMetric", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "ExpirationTime", PARAMETER_ATTR_READONLY, 27, json_type_time},
	{ NULL, 0, 0, 0}
};
#endif
