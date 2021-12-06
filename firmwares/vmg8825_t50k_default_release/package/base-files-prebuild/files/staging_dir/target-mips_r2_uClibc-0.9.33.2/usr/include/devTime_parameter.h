tr98Parameter_t para_Time[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 27, json_type_string},
	{ "NTPServer1", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "NTPServer2", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "NTPServer3", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "NTPServer4", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "NTPServer5", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "CurrentLocalTime", PARAMETER_ATTR_READONLY, 21, json_type_time},
	//OBSOLETED{ "LocalTimeZone", PARAMETER_ATTR_WRITE, 7, json_type_string},
	{ "LocalTimeZoneName", PARAMETER_ATTR_WRITE, 65, json_type_string},
	//OBSOLETED{ "DaylightSavingsUsed", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//OBSOLETED{ "DaylightSavingStart", PARAMETER_ATTR_WRITE, 21, json_type_time},
	//OBSOLETED{ "DaylightSavingEnd", PARAMETER_ATTR_WRITE, 21, json_type_time},
	{ NULL, 0, 0, 0}
};