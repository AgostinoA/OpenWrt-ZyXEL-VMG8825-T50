tr98Parameter_t para_IspSrv[] = {
	{ "Name", PARAMETER_ATTR_READONLY, 32, json_type_string},
	{ "Version", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ "Script", PARAMETER_ATTR_WRITE, 64, json_type_string},
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Data", PARAMETER_ATTR_WRITE, 256, json_type_string},
	{ "FixCustID", PARAMETER_ATTR_WRITE, 256, json_type_string},
	{ "Hash", PARAMETER_ATTR_WRITE, 256, json_type_string},
	{ "Status", PARAMETER_ATTR_WRITE, 64, json_type_string},
	{ NULL, 0, 0, 0}
};

