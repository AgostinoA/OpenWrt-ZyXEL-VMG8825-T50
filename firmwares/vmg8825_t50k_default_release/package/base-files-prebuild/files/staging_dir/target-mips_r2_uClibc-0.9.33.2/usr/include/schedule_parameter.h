tr98Parameter_t para_Schedule[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Name", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "Description", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "Days", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "TimeStartHour", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "TimeStartMin", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "TimeStopHour", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "TimeStopMin", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
 	{ NULL, 0, 0, 0}
};

