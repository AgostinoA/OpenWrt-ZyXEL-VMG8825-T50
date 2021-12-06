#ifndef __ONECONNECT_PARAMETER_H__
#define __ONECONNECT_PARAMETER_H__
tr98Parameter_t para_OneConnectExt[] = {
	{ "L2DevCtrl_Reboot", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "L2DevCtrl_RebootResult", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ "L2DevCtrl_Reset", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "L2DevCtrl_ResetResult", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ "L2DevCtrl_FWCheck", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "L2DevCtrl_FWDownload", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "L2DevCtrl_FWUpgrade", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "L2DevCtrl_FWURL", PARAMETER_ATTR_WRITE, 256, json_type_string},
	{ "L2DevCtrl_FWUpgradeResult", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ "L2DevCtrl_WiFiPwr", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "L2DevCtrl_MediaType", PARAMETER_ATTR_WRITE, 8, json_type_string},
	/*{ "ModelName", PARAMETER_ATTR_READONLY, 256, json_type_string},
	{ "FWUpgradeState", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "NewFWUpgradeVersion", PARAMETER_ATTR_READONLY, 256, json_type_string},*/
	{ NULL, 0, 0, 0}
};
#endif