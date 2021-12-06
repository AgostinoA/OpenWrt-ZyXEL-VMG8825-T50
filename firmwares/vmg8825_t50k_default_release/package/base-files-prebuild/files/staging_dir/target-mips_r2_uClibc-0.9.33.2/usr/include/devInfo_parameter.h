tr98Parameter_t para_DevInfo[] = {
	{ "Manufacturer", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "ManufacturerOUI", PARAMETER_ATTR_READONLY, 7, json_type_string},
	{ "ModelName", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "Description", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "ProductClass", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "SerialNumber", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "HardwareVersion", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_PASSIVENOTIFY, 65, json_type_string},
	{ "SoftwareVersion", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_ACTIVENOTIFY, 65, json_type_string},
	{ "ModemFirmwareVersion", PARAMETER_ATTR_READONLY, 65, json_type_string},
	//{ "EnabledOptions", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 1025, json_type_string},
	{ "UpTime", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "AdditionalHardwareVersion", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "AdditionalSoftwareVersion", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "SpecVersion", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_PASSIVENOTIFY, 17, json_type_string},
	{ "ProvisioningCode", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_ACTIVENOTIFY, 65, json_type_string},
	{ "FirstUseDate", PARAMETER_ATTR_READONLY, 21, json_type_time},
	{ "DeviceLog", PARAMETER_ATTR_READONLY, 33, json_type_string},
	{ "VendorConfigFileNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_MemoryStatus[] = {
	{ "Total", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Free", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0}
};


tr98Parameter_t para_DevInfoVendorCfg[] = {
	{ "Alias", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "Name", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "Version", PARAMETER_ATTR_READONLY, 17, json_type_string},
	{ "Date", PARAMETER_ATTR_READONLY, 21, json_type_time},
	{ "Description", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_ProcSt[] = {
	{ "CPUUsage", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ProcessNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_ProcStPs[] = {
	{ "PID", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "Command", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "Size", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "Priority", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "CPUTime", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "State", PARAMETER_ATTR_READONLY, 27, json_type_string},
	{ NULL, 0, 0, 0}
};


