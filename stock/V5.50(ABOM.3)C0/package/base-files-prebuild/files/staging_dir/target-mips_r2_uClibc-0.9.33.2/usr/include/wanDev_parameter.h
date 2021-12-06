tr98Parameter_t para_WanDev[] = {
	{ "WANConnectionNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "X_ZYXEL_3GEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_PinNumber", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANDslDiag[] = {
	{ "LoopDiagnosticsState", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ "ACTPSDds", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "ACTPSDus", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "ACTATPds", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "ACTATPus", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "HLINSCds", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "HLINSCus", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "HLINGds", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "HLINGus", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "HLOGGds", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "HLOGGus", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "HLOGpsds", PARAMETER_ATTR_READONLY, 2559, json_type_string},
	{ "HLOGpsus", PARAMETER_ATTR_READONLY, 2559, json_type_string},
	{ "HLOGMTds", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "HLOGMTus", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "LATNpbds", PARAMETER_ATTR_READONLY, 24, json_type_string},
	{ "LATNpbus", PARAMETER_ATTR_READONLY, 24, json_type_string},
	{ "SATNds", PARAMETER_ATTR_READONLY, 24, json_type_string},
	{ "SATNus", PARAMETER_ATTR_READONLY, 24, json_type_string},
	{ "HLINpsds", PARAMETER_ATTR_READONLY, 61430, json_type_string},
	{ "HLINpsus", PARAMETER_ATTR_READONLY, 61430, json_type_string},
	{ "QLNGds", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "QLNGus", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "QLNpsds", PARAMETER_ATTR_READONLY, 61430, json_type_string},
	{ "QLNpsus", PARAMETER_ATTR_READONLY, 61430, json_type_string},
	{ "QLNMTds", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "QLNMTus", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "SNRGds", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "SNRGus", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "SNRpsds", PARAMETER_ATTR_READONLY, 61430, json_type_string},
	{ "SNRpsus", PARAMETER_ATTR_READONLY, 61430, json_type_string},
	{ "SNRMTds", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "SNRMTus", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "BITSpsds", PARAMETER_ATTR_READONLY, 61430, json_type_string},
	{ "BITSpsus", PARAMETER_ATTR_READONLY, 61430, json_type_string},
	{ "GAINSpsds", PARAMETER_ATTR_READONLY, 61430, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANConnDev[] = {
	{ "WANIPConnectionNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "WANPPPConnectionNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "X_ZYXEL_WANPPPConnectionSupportedNCPs", PARAMETER_ATTR_READONLY, 33, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANCommIfaceCfg[] = {
	{ "EnabledForInternet", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "WANAccessType", PARAMETER_ATTR_READONLY, 10, json_type_string},
	{ "Layer1UpstreamMaxBitRate", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "Layer1DownstreamMaxBitRate", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "PhysicalLinkStatus", PARAMETER_ATTR_READONLY, 14, json_type_string},
	{ "WANAccessProvider", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "TotalBytesSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TotalBytesReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TotalPacketsSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TotalPacketsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "MaximumActiveConnections", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "NumberOfActiveConnections", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANDslIfaceCfg[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 410, json_type_string},
	{ "LinkEncapsulationSupported", PARAMETER_ATTR_READONLY, 21, json_type_string},
	{ "LinkEncapsulationRequested", PARAMETER_ATTR_WRITE, 21, json_type_string},
	{ "LinkEncapsulationUsed", PARAMETER_ATTR_READONLY, 21, json_type_string},
	{ "ModulationType", PARAMETER_ATTR_READONLY, 18, json_type_string},
	{ "StandardsSupported", PARAMETER_ATTR_READONLY, 17, json_type_string},
	{ "StandardUsed", PARAMETER_ATTR_READONLY, 1, json_type_string},
	{ "LineEncoding", PARAMETER_ATTR_READONLY, 6, json_type_string},
	{ "AllowedProfiles", PARAMETER_ATTR_READONLY, 33, json_type_string},
	{ "CurrentProfile", PARAMETER_ATTR_READONLY, 1, json_type_string},
	{ "PowerManagementState", PARAMETER_ATTR_READONLY, 4, json_type_string},
	{ "SuccessFailureCause", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "LastStateTransmittedDownstream", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "LastStateTransmittedUpstream", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "UPBOKLE", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "LIMITMASK", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "US0MASK", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	//{ "DataPath", PARAMETER_ATTR_READONLY, 13, json_type_string},
	//{ "InterleaveDepth", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "LPATH", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "INTLVDEPTH", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "INTLVBLOCK", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "ActualInterleavingDelay", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ACTINP", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "INPREPORT", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "NFEC", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "RFEC", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "LSYMB", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "TRELLISds", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "TRELLISus", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "ACTSNRMODEds", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ACTSNRMODEus", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ACTUALCE", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "LineNumber", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "UpstreamCurrRate", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "DownstreamCurrRate", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "UpstreamMaxRate", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "DownstreamMaxRate", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "UpstreamNoiseMargin", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "DownstreamNoiseMargin", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "SNRMpbus", PARAMETER_ATTR_READONLY, 25, json_type_string},
	{ "SNRMpbds", PARAMETER_ATTR_READONLY, 25, json_type_string},
	{ "INMIATOds", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "INMIATSds", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "INMCCds", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "INMINPEQMODEds", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "UpstreamAttenuation", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "DownstreamAttenuation", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "UpstreamPower", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "DownstreamPower", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "ATURVendor", PARAMETER_ATTR_READONLY, 9, json_type_string},
	{ "ATURCountry", PARAMETER_ATTR_READONLY, 5, json_type_string},
	{ "ATURANSIStd", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ATURANSIRev", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ATUCVendor", PARAMETER_ATTR_READONLY, 9, json_type_string},
	{ "ATUCCountry", PARAMETER_ATTR_READONLY, 5, json_type_string},
	{ "ATUCANSIStd", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ATUCANSIRev", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TotalStart", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ShowtimeStart", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "LastShowtimeStart", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "CurrentDayStart", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "QuarterHourStart", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "X_ZYXEL_UpstreamCurrRate_2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_BondingLineNumber", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_VDSL_8a", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_VDSL_8b", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_VDSL_8c", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_VDSL_8d", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_VDSL_12a", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_VDSL_12b", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_VDSL_17a", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_VDSL_30a", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_VDSL_US0_8a", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_ADSL2_AnnexM", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_PhoneLinePair", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "X_ZYXEL_Bitswap", PARAMETER_ATTR_WRITE, 9, json_type_string},
	{ "X_ZYXEL_SRA", PARAMETER_ATTR_WRITE, 9, json_type_string},
	{ "X_ZYXEL_TrellisD", PARAMETER_ATTR_WRITE, 9, json_type_string},
	{ "X_ZYXEL_TrellisU", PARAMETER_ATTR_WRITE, 9, json_type_string},
	{ "X_ZYXEL_LinkPowerState", PARAMETER_ATTR_WRITE, 4, json_type_string},
	{ "X_ZYXEL_AdslModulationCfg", PARAMETER_ATTR_WRITE, 129, json_type_string},
	{ "X_ZYXEL_DslCfgParam", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DslTrainingMarginQ4", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "X_ZYXEL_DslShowtimeMarginQ4", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "X_ZYXEL_DslLOMTimeThldSec", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "X_ZYXEL_DslPwmSyncClockFreq", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "X_ZYXEL_DslHsModeSwitchTime", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "X_ZYXEL_DslParam", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DslPhyCfg1Mask", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DslPhyCfg1Value", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DslPhyCfg2Mask", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DslPhyCfg2Value", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DslPhyCfg3Mask", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DslPhyCfg3Value", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DslPhyCfg4Mask", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DslPhyCfg4Value", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DslPhyCfg5Mask", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DslPhyCfg5Value", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DslPhyCfg6Mask", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DslPhyCfg6Value", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DslPhyCfg7Mask", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DslPhyCfg7Value", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DslPhyCfg8Mask", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DslPhyCfg8Value", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DslPhyUsDataRateKbps", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DslPhyDsDataRateKbps", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DslPhyAggrDataRateKbps", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DslPhyMiscCfgParam", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_UpstreamMSGc", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_UpstreamMSGc_2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_DownstreamMSGc", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_DownstreamMSGc_2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_UpstreamB", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_UpstreamB_2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_DownstreamB", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_DownstreamB_2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_UpstreamM", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_UpstreamM_2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_DownstreamM", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_DownstreamM_2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_UpstreamT", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_UpstreamT_2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_DownstreamT", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_DownstreamT_2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_UpstreamR", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_UpstreamR_2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_DownstreamR", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_DownstreamR_2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_UpstreamL", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_UpstreamL_2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_DownstreamL", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_DownstreamL_2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_UpstreamK", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DownstreamK", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_UpstreamS", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_DownstreamS", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_UpstreamR", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DownstreamR", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_ADSL2_UpstreamS", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_ADSL2_UpstreamS_2", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_ADSL2_DownstreamS", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_ADSL2_DownstreamS_2", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_UpstreamDelay", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_UpstreamDelay_2", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_DownstreamDelay", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_DownstreamDelay_2", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_UpstreamINP", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_UpstreamINP_2", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_DownstreamINP", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_DownstreamINP_2", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_UpstreamD", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_UpstreamD_2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DownstreamD", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DownstreamD_2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_VDSL_UpstreamI", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_VDSL_UpstreamI_2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_VDSL_DownstreamI", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_VDSL_DownstreamI_2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_VDSL_UpstreamN", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_VDSL_DownstreamN", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_VDSL_UpstreamN_2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_VDSL_DownstreamN_2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_LinkTypeisATM", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "X_ZYXEL_ModulationType", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANDslIfTestParam[] = {
	{ "HLOGGds", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "HLOGGus", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "HLOGpsds", PARAMETER_ATTR_READONLY, 2560, json_type_string},
	{ "HLOGpsus", PARAMETER_ATTR_READONLY, 2560, json_type_string},
	{ "HLOGMTds", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "HLOGMTus", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "QLNGds", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "QLNGus", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "QLNpsds", PARAMETER_ATTR_READONLY, 2048, json_type_string},
	{ "QLNpsus", PARAMETER_ATTR_READONLY, 2048, json_type_string},
	{ "QLNMTds", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "QLNMTus", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "SNRGds", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "SNRGus", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "SNRpsds", PARAMETER_ATTR_READONLY, 2048, json_type_string},
	{ "SNRpsus", PARAMETER_ATTR_READONLY, 2048, json_type_string},
	{ "SNRMTds", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "SNRMTus", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "LATNds", PARAMETER_ATTR_READONLY, 25, json_type_string},
	{ "LATNus", PARAMETER_ATTR_READONLY, 25, json_type_string},
	{ "SATNds", PARAMETER_ATTR_READONLY, 25, json_type_string},
	{ "SATNus", PARAMETER_ATTR_READONLY, 25, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANDslIfaceCfgStatTotal[] = {
	{ "ReceiveBlocks", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TransmitBlocks", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "CellDelin", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "LinkRetrain", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "InitErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	//{ "LInit", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "InitTimeouts", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "LossOfFraming", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "LOF", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "ErroredSecs", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	//{ "ATUCErroredSecs", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "SeverelyErroredSecs", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	//{ "ATUCSeverelyErroredSecs", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "FECErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ATUCFECErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "HECErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ATUCHECErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "CRCErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ATUCCRCErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANDslIfaceCfgStatSt[] = {
	{ "ReceiveBlocks", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TransmitBlocks", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "CellDelin", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "LinkRetrain", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "InitErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	//{ "LInit", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "InitTimeouts", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "LossOfFraming", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "LOF", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "ErroredSecs", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	//{ "ATUCErroredSecs", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "SeverelyErroredSecs", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	//{ "ATUCSeverelyErroredSecs", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "FECErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ATUCFECErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "HECErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ATUCHECErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "CRCErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ATUCCRCErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANDslIfaceCfgStatObjs[] = {
	{ "ReceiveBlocks", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TransmitBlocks", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "CellDelin", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "LinkRetrain", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "InitErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	//{ "LInit", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "InitTimeouts", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "LossOfFraming", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "LOF", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "ErroredSecs", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	//{ "ATUCErroredSecs", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "SeverelyErroredSecs", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	//{ "ATUCSeverelyErroredSecs", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "FECErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ATUCFECErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "HECErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ATUCHECErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "CRCErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ATUCCRCErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANEthIntfConf[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 10, json_type_string},
	{ "MACAddress", PARAMETER_ATTR_READONLY, 19, json_type_string},
	{ "MaxBitRate", PARAMETER_ATTR_WRITE, 7, json_type_string},
	{ "DuplexMode", PARAMETER_ATTR_WRITE, 6, json_type_string},
	{ "ShapingRate", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "ShapingBurstSize", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_UpTime", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "X_ZYXEL_LastChangeTime", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANEthIntfConfStat[] = {
	{ "BytesSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "BytesReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "PacketsSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "PacketsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANDslLinkConf[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "LinkStatus", PARAMETER_ATTR_READONLY, 14, json_type_string},
	{ "LinkType", PARAMETER_ATTR_WRITE, 14, json_type_string},
	{ "AutoConfig", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	//{ "ModulationType", PARAMETER_ATTR_READONLY, 18, json_type_string},
	{ "DestinationAddress", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "ATMEncapsulation", PARAMETER_ATTR_WRITE, 7, json_type_string},
	{ "FCSPreserved", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "VCSearchList", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "ATMAAL", PARAMETER_ATTR_READONLY, 6, json_type_string},
	{ "ATMTransmittedBlocks", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ATMReceivedBlocks", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ATMQoS", PARAMETER_ATTR_WRITE, 9, json_type_string},
	{ "ATMPeakCellRate", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "ATMMaximumBurstSize", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "ATMSustainableCellRate", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "AAL5CRCErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ATMCRCErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ATMHECErrors", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANPtmLinkConf[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "LinkStatus", PARAMETER_ATTR_READONLY, 14, json_type_string},
	{ "MACAddress", PARAMETER_ATTR_READONLY, 19, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANPtmLinkConfStat[] = {
	{ "BytesSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "BytesReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "FramesSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "FramesReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "OOSNearEnd", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "OOSFarEnd", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "ErrorsSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ErrorsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "UnicastPacketsSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "UnicastPacketsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "DiscardPacketsSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "DiscardPacketsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "MulticastPacketsSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "MulticastPacketsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "BroadcastPacketsSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "BroadcastPacketsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "UnknownProtoPacketsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};


tr98Parameter_t para_WANEthLinkConf[] = {
	{ "EthernetLinkStatus", PARAMETER_ATTR_READONLY, 13, json_type_string},
	{ NULL, 0, 0, 0}
};


tr98Parameter_t para_WANIpConn[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Reset", PARAMETER_ATTR_WRITE | PARAMETER_ATTR_STD_RESET, 0, json_type_boolean},
	{ "ConnectionStatus", PARAMETER_ATTR_READONLY, 19, json_type_string},
	{ "PossibleConnectionTypes", PARAMETER_ATTR_READONLY, 35, json_type_string},
	{ "ConnectionType", PARAMETER_ATTR_WRITE, 35, json_type_string},
	{ "Name", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "Uptime", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "LastConnectionError", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 33, json_type_string},
	{ "AutoDisconnectTime", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "IdleDisconnectTime", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "WarnDisconnectDelay", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "RSIPAvailable", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 0, json_type_boolean},
	{ "NATEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "AddressingType", PARAMETER_ATTR_WRITE, 8, json_type_string},
	{ "ExternalIPAddress", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_ACTIVENOTIFY, 17, json_type_string},
	{ "SubnetMask", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "DefaultGateway", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "DNSEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "DNSOverrideAllowed", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 0, json_type_boolean},
	{ "DNSServers", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "MaxMTUSize", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "MACAddress", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 19, json_type_string},
	{ "MACAddressOverride", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 0, json_type_boolean},
	{ "ConnectionTrigger", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 10, json_type_string},
	{ "RouteProtocolRx", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 7, json_type_string},
	{ "ShapingRate", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 0, json_type_int},
	{ "ShapingBurstSize", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "PortMappingNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "X_ZYXEL_DNSType", PARAMETER_ATTR_WRITE, 19, json_type_string},
	{ "X_ZYXEL_IGMPProxyEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_VlanEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_VlanMux8021p", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "X_ZYXEL_VlanMuxID", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "X_ZYXEL_FullConeEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
#ifdef ZYXEL_SUPPORT_DMZ_MANAGEMENT
	{ "X_ZYXEL_DMZHost_Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
#endif
	{ "X_ZYXEL_DMZHost", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_NAT_ALG", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_SIP_ALG", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_RTSP_ALG", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_PPTP_ALG", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_IPSEC_ALG", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_MaxSessionPerHost", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DefaultGatewayIface", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_IPv4Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_ConcurrentWan", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_PubLan", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_PubLan_DHCP", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_PubLan_ARP", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_PubLan_IP", PARAMETER_ATTR_WRITE, 0, json_type_string},
	{ "X_ZYXEL_PubLan_Mask", PARAMETER_ATTR_WRITE, 0, json_type_string},
#ifdef IPV6RD_PROFILE
#ifndef SUNRISE_TR98_CUSTOMIZATION // Sunrise
	{ "X_ZYXEL_Enable_6RD", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_6RD_Type", PARAMETER_ATTR_WRITE, 8, json_type_string},
	{ "X_ZYXEL_BorderRelayIPv4Addresses", PARAMETER_ATTR_WRITE, 72, json_type_string},
	{ "X_ZYXEL_SPIPv6Prefix", PARAMETER_ATTR_WRITE, 64, json_type_string},
	{ "X_ZYXEL_IPv4MaskLength", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
#endif
#endif
#ifdef IPV6INTERFACE_PROFILE
	{ "X_ZYXEL_IPv6Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_IPv6Status", PARAMETER_ATTR_READONLY, 10, json_type_string},
	{ "X_ZYXEL_IPv6DNSEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_IPv6DNSServers", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "X_ZYXEL_IPv6AddressNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "X_ZYXEL_IPv6PrefixNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "X_ZYXEL_ActiveV6DefaultGateway", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_Enable_DSLite", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_DSLiteRelayIPv6Addresses", PARAMETER_ATTR_WRITE, 73, json_type_string},
#endif
        { "X_ZYXEL_IfName", PARAMETER_ATTR_READONLY, 18, json_type_string},
#ifdef ISKON_CUSTOMIZATION 
	{ "X_ZYXEL_RIPEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
#endif
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_DhcpClient[] = {
	{ "SentDHCPOptionNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ReqDHCPOptionNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};


tr98Parameter_t para_SentDhcpOpt[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Tag", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "Value", PARAMETER_ATTR_WRITE, 256, json_type_string},
	{ "Value", PARAMETER_ATTR_WRITE, 256+(256/2), json_type_base64},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_ReqDhcpOpt[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Order", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Tag", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "Value", PARAMETER_ATTR_READONLY, 256, json_type_uint32},
	{ "Value", PARAMETER_ATTR_READONLY, 256+(256/2), json_type_base64},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANIpConnMld[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "MldVersion", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "QueryInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "QueryResponseInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "LastMemberQueryInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "RobustnessValue", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "LanToLanEnable", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "MaxGroups", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "MaxSources", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "MaxMembers", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "FastLeave", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "SnoopingEnable", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Interface", PARAMETER_ATTR_READONLY, 321, json_type_string},
	{ "ifName", PARAMETER_ATTR_WRITE, 321, json_type_string},
	{ "Status", PARAMETER_ATTR_WRITE, 19, json_type_string},
	{ "SnoopingBridgeIfName", PARAMETER_ATTR_WRITE, 101, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANIpPortMap[] = {
	{ "PortMappingEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "PortMappingLeaseDuration", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "RemoteHost", PARAMETER_ATTR_WRITE, 46, json_type_string},
	{ "ExternalPort", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "ExternalPortEndRange", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "InternalPort", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "PortMappingProtocol", PARAMETER_ATTR_WRITE, 5, json_type_string},
	{ "InternalClient", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "PortMappingDescription", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "X_ZYXEL_WANIP", PARAMETER_ATTR_WRITE, 46, json_type_string},
	{ "X_ZYXEL_InternalPortEndRange", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_OriginatingIpAddress", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "X_ZYXEL_SetOriginatingIP", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANIpPortTrigger[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Name", PARAMETER_ATTR_WRITE, 65, json_type_string},
	//{ "Status", PARAMETER_ATTR_READONLY, 20, json_type_string},
	//{ "Interface", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "TriggerPort", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "TriggerPortEndRange", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "OpenPort", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "OpenPortEndRange", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Protocol", PARAMETER_ATTR_WRITE, 4, json_type_string},
	{ "TriggerProtocol", PARAMETER_ATTR_WRITE, 4, json_type_string},
	{ "Description", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANIpAddrMapping[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Type", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "LocalStartIP", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "LocalEndIP", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "GlobalStartIP", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "GlobalEndIP", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "MappingSet", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "MappingRuleName", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "Description", PARAMETER_ATTR_WRITE, 65, json_type_string},
	//{ "WANIntfName", PARAMETER_ATTR_READONLY, 65, json_type_string},
	//{ "Interface", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANIpConnStat[] = {
	{ "EthernetBytesSent", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetBytesReceived", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetPacketsSent", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetPacketsReceived", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetErrorsSent", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetErrorsReceived", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetUnicastPacketsSent", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetUnicastPacketsReceived", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetDiscardPacketsSent", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetDiscardPacketsReceived", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetMulticastPacketsSent", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetMulticastPacketsReceived", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetBroadcastPacketsSent", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetBroadcastPacketsReceived", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetUnknownProtoPacketsReceived", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

#ifdef IPV6INTERFACE_PROFILE
tr98Parameter_t para_WANIpv6Addr[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 24, json_type_string},
	{ "IPAddressStatus", PARAMETER_ATTR_READONLY, 16, json_type_string},
	{ "IPAddress", PARAMETER_ATTR_WRITE, 48, json_type_string},
	{ "Origin", PARAMETER_ATTR_READONLY, 24, json_type_string},
	{ "Prefix", PARAMETER_ATTR_WRITE, 128, json_type_string},
	{ "PreferredLifetime", PARAMETER_ATTR_WRITE, 0, json_type_time},
	{ "ValidLifetime", PARAMETER_ATTR_WRITE, 0, json_type_time},
	{ "NextHop", PARAMETER_ATTR_WRITE, 48, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANIpv6Prefix[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 24, json_type_string},
	{ "PrefixStatus", PARAMETER_ATTR_READONLY, 16, json_type_string},
	{ "Prefix", PARAMETER_ATTR_WRITE, 24, json_type_string},
	{ "OnLink", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Autonomous", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "PreferredLifetime", PARAMETER_ATTR_WRITE, 0, json_type_time},
	{ "ValidLifetime", PARAMETER_ATTR_WRITE, 0, json_type_time},
	{ NULL, 0, 0, 0}
};

#endif
#ifdef DHCPV6CLIENT_PROFILE
tr98Parameter_t para_WANIpDhcpV6Client[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 24, json_type_string},
	{ "DUID", PARAMETER_ATTR_READONLY, 130, json_type_string},
	{ "RequestAddresses", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "RequestPrefixes", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "RapidCommit", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};

#endif
#ifdef IPV6RD_PROFILE
#ifdef SUNRISE_TR98_CUSTOMIZATION // Sunrise
tr98Parameter_t para_WANIpv6Rd[] = {
	{ "X_ZYXEL_Enable_6RD", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_6RD_Type", PARAMETER_ATTR_WRITE, 8, json_type_string},
	{ "X_ZYXEL_BorderRelayIPv4Addresses", PARAMETER_ATTR_WRITE, 72, json_type_string},
	{ "X_ZYXEL_SPIPv6Prefix", PARAMETER_ATTR_WRITE, 64, json_type_string},
	{ "X_ZYXEL_IPv4MaskLength", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

#else
tr98Parameter_t para_WANIpv6Rd[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 8, json_type_string},
	{ "BorderRelayIPv4Addresses", PARAMETER_ATTR_WRITE, 72, json_type_string},
	{ "AllTrafficToBorderRelay", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "SPIPv6Prefix", PARAMETER_ATTR_WRITE, 64, json_type_string},
	{ "IPv4MaskLength", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "AddressSource", PARAMETER_ATTR_WRITE, 128, json_type_string},
	{ NULL, 0, 0, 0}
};
#endif
#endif
#ifdef ROUTEINFO_INTERFACE
tr98Parameter_t para_WANIpIntfRouteInfo[] = {
	{ "Status", PARAMETER_ATTR_READONLY, 23, json_type_string},
	{ "Interface", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "SourceRouter", PARAMETER_ATTR_READONLY, 46, json_type_string},
	{ "PreferredRouteFlag", PARAMETER_ATTR_READONLY, 7, json_type_string},
	{ "Prefix", PARAMETER_ATTR_READONLY, 50, json_type_string},
	{ "RouteLifetime", PARAMETER_ATTR_READONLY, 27, json_type_time},
	{ NULL, 0, 0, 0}
};
#endif
tr98Parameter_t para_WANPppConn[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Reset", PARAMETER_ATTR_WRITE | PARAMETER_ATTR_STD_RESET, 0, json_type_boolean},
	{ "ConnectionStatus", PARAMETER_ATTR_READONLY, 19, json_type_string},
	{ "PossibleConnectionTypes", PARAMETER_ATTR_READONLY, 85, json_type_string},
	{ "ConnectionType", PARAMETER_ATTR_WRITE, 15, json_type_string},
	{ "PPPoESessionID", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "DefaultGateway", PARAMETER_ATTR_READONLY, 17, json_type_string},
	{ "Name", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "Uptime", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "LastConnectionError", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 33, json_type_string},
	{ "AutoDisconnectTime", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "IdleDisconnectTime", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "WarnDisconnectDelay", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "RSIPAvailable", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 0, json_type_boolean},
	{ "NATEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Username", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "Password", PARAMETER_ATTR_WRITE | PARAMETER_ATTR_PASSWORD, 65, json_type_string},
	{ "PPPEncryptionProtocol", PARAMETER_ATTR_READONLY, 6, json_type_string},
	{ "PPPCompressionProtocol", PARAMETER_ATTR_READONLY, 14, json_type_string},
	{ "PPPAuthenticationProtocol", PARAMETER_ATTR_READONLY, 9, json_type_string},
	{ "ExternalIPAddress", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_ACTIVENOTIFY, 17, json_type_string},
	{ "RemoteIPAddress", PARAMETER_ATTR_READONLY, 17, json_type_string},
	{ "MaxMRUSize", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "CurrentMRUSize", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "DNSEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "DNSOverrideAllowed", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 0, json_type_boolean},
	{ "DNSServers", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "MACAddress", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 19, json_type_string},
	{ "MACAddressOverride", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 0, json_type_boolean},
	{ "TransportType", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 7, json_type_string},
	{ "PPPoEACName", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "PPPoEServiceName", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "ConnectionTrigger", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 10, json_type_string},
	{ "RouteProtocolRx", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 7, json_type_string},
	{ "PPPLCPEcho", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "PPPLCPEchoRetry", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ShapingRate", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 0, json_type_int},
	{ "ShapingBurstSize", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DEFAULTATTR|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST|PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "PortMappingNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "X_ZYXEL_DNSType", PARAMETER_ATTR_WRITE, 19, json_type_string},
	{ "X_ZYXEL_IGMPProxyEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_VlanEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_VlanMux8021p", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "X_ZYXEL_VlanMuxID", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "X_ZYXEL_FullConeEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
#ifdef ZYXEL_SUPPORT_DMZ_MANAGEMENT
	{ "X_ZYXEL_DMZHost_Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
#endif
	{ "X_ZYXEL_DMZHost", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_NAT_ALG", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_SIP_ALG", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_RTSP_ALG", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_PPTP_ALG", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_IPSEC_ALG", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_MaxSessionPerHost", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DefaultGatewayIface", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_IPv4Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_ConcurrentWan", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
#ifdef IPV6RD_PROFILE
#ifndef SUNRISE_TR98_CUSTOMIZATION // Sunrise
	{ "X_ZYXEL_Enable_6RD", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_BorderRelayIPv4Addresses", PARAMETER_ATTR_WRITE, 72, json_type_string},
	{ "X_ZYXEL_SPIPv6Prefix", PARAMETER_ATTR_WRITE, 64, json_type_string},
	{ "X_ZYXEL_IPv4MaskLength", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
#endif
#endif
#ifdef IPV6INTERFACE_PROFILE
	{ "X_ZYXEL_IPv6Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_IPv6Status", PARAMETER_ATTR_READONLY, 10, json_type_string},
	{ "X_ZYXEL_IPv6DNSEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_IPv6DNSServers", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "X_ZYXEL_IPv6AddressNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "X_ZYXEL_IPv6PrefixNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
#endif
#if 1  /* __ZyXEL__, Albert, 20150520, Supports PPPoE Connection Delay and LCP Echo  */
	{ "X_ZYXEL_PPPConnRetryInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_LCPEcho", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_LCPEchoRetry", PARAMETER_ATTR_WRITE, 0, json_type_uint32},	
#endif
    { "X_ZYXEL_IfName", PARAMETER_ATTR_READONLY, 18, json_type_string},
#ifdef ISKON_CUSTOMIZATION	
	{ "X_ZYXEL_RIPEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
#endif
	{ "X_ZYXEL_IPCPEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_IPv6CPEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_LocalInterfaceIdentifier", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_ACTIVENOTIFY, 65, json_type_string},
	{ "X_ZYXEL_RemoteInterfaceIdentifier", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANPppPortMap[] = {
	{ "PortMappingEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "PortMappingLeaseDuration", PARAMETER_ATTR_WRITE|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "RemoteHost", PARAMETER_ATTR_WRITE, 46, json_type_string},
	{ "ExternalPort", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "ExternalPortEndRange", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "InternalPort", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "PortMappingProtocol", PARAMETER_ATTR_WRITE, 5, json_type_string},
	{ "InternalClient", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "PortMappingDescription", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "X_ZYXEL_WANIP", PARAMETER_ATTR_WRITE, 46, json_type_string},
	{ "X_ZYXEL_InternalPortEndRange", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANPppPortTrigger[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Name", PARAMETER_ATTR_WRITE, 60, json_type_string},
	//{ "Status", PARAMETER_ATTR_READONLY, 20, json_type_string},
	//{ "Interface", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "TriggerPort", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "TriggerPortEndRange", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "OpenPort", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "OpenPortEndRange", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Protocol", PARAMETER_ATTR_WRITE, 4, json_type_string},
	{ "TriggerProtocol", PARAMETER_ATTR_WRITE, 4, json_type_string},
	{ "Description", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANPppAddrMapping[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Type", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "LocalStartIP", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "LocalEndIP", PARAMETER_ATTR_READONLY, 17, json_type_string},
	{ "GlobalStartIP", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "GlobalEndIP", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "MappingSet", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "MappingRuleName", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "Description", PARAMETER_ATTR_WRITE, 65, json_type_string},
	//{ "WANIntfName", PARAMETER_ATTR_READONLY, 65, json_type_string},
	//{ "Interface", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANPppConnStat[] = {
#if 0
	{ "EthernetBytesSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "EthernetBytesReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "EthernetPacketsSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "EthernetPacketsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "EthernetErrorsSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "EthernetErrorsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "EthernetUnicastPacketsSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "EthernetUnicastPacketsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "EthernetDiscardPacketsSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "EthernetDiscardPacketsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "EthernetMulticastPacketsSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "EthernetMulticastPacketsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "EthernetBroadcastPacketsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "EthernetUnknownProtoPacketsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
#endif
	{ "EthernetBytesSent", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetBytesReceived", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetPacketsSent", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetPacketsReceived", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetErrorsSent", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetErrorsReceived", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetUnicastPacketsSent", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetUnicastPacketsReceived", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetDiscardPacketsSent", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetDiscardPacketsReceived", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetMulticastPacketsSent", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetMulticastPacketsReceived", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetBroadcastPacketsSent", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetBroadcastPacketsReceived", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ "EthernetUnknownProtoPacketsReceived", PARAMETER_ATTR_READONLY|PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANPppConnMld[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "MldVersion", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "QueryInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "QueryResponseInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "LastMemberQueryInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "RobustnessValue", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "LanToLanEnable", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "MaxGroups", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "MaxSources", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "MaxMembers", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "FastLeave", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "SnoopingEnable", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Interface", PARAMETER_ATTR_READONLY, 321, json_type_string},
	{ "ifName", PARAMETER_ATTR_WRITE, 321, json_type_string},
	{ "Status", PARAMETER_ATTR_WRITE, 19, json_type_string},
	{ "SnoopingBridgeIfName", PARAMETER_ATTR_WRITE, 101, json_type_string},
	{ NULL, 0, 0, 0}
};

#ifdef IPV6INTERFACE_PROFILE
tr98Parameter_t para_WANPppv6Addr[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 24, json_type_string},
	{ "IPAddressStatus", PARAMETER_ATTR_READONLY, 16, json_type_string},
	{ "IPAddress", PARAMETER_ATTR_WRITE, 48, json_type_string},
	{ "Origin", PARAMETER_ATTR_READONLY, 24, json_type_string},
	{ "Prefix", PARAMETER_ATTR_WRITE, 128, json_type_string},
	{ "PreferredLifetime", PARAMETER_ATTR_WRITE, 0, json_type_time},
	{ "ValidLifetime", PARAMETER_ATTR_WRITE, 0, json_type_time},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANPppv6Prefix[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 24, json_type_string},
	{ "PrefixStatus", PARAMETER_ATTR_READONLY, 16, json_type_string},
	{ "Prefix", PARAMETER_ATTR_WRITE, 24, json_type_string},
	{ "OnLink", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Autonomous", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "PreferredLifetime", PARAMETER_ATTR_WRITE, 0, json_type_time},
	{ "ValidLifetime", PARAMETER_ATTR_WRITE, 0, json_type_time},
	{ NULL, 0, 0, 0}
};

#endif
#ifdef DHCPV6CLIENT_PROFILE
tr98Parameter_t para_WANPppDhcpV6Client[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 24, json_type_string},
	{ "DUID", PARAMETER_ATTR_READONLY, 130, json_type_string},
	{ "RequestAddresses", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "RequestPrefixes", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "RapidCommit", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};

#endif
#ifdef IPV6RD_PROFILE
#ifdef SUNRISE_TR98_CUSTOMIZATION // Sunrise
tr98Parameter_t para_WANPppv6Rd[] = {
	{ "X_ZYXEL_Enable_6RD", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_BorderRelayIPv4Addresses", PARAMETER_ATTR_WRITE, 72, json_type_string},
	{ "X_ZYXEL_SPIPv6Prefix", PARAMETER_ATTR_WRITE, 64, json_type_string},
	{ "X_ZYXEL_IPv4MaskLength", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

#else
tr98Parameter_t para_WANPppv6Rd[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 8, json_type_string},
	{ "BorderRelayIPv4Addresses", PARAMETER_ATTR_WRITE, 72, json_type_string},
	{ "AllTrafficToBorderRelay", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "SPIPv6Prefix", PARAMETER_ATTR_WRITE, 64, json_type_string},
	{ "IPv4MaskLength", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "AddressSource", PARAMETER_ATTR_WRITE, 128, json_type_string},
	{ NULL, 0, 0, 0}
};
#endif
#endif

tr98Parameter_t para_WanAtmF5LoDiag[] = {
	{ "DiagnosticsState", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ "NumberOfRepetitions", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Timeout", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "SuccessCount", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "FailureCount", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "AverageResponseTime", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "MinimumResponseTime", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "MaximumResponseTime", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "X_ZYXEL_SegmentLoopback", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_Creator", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WanAtmF4LoDiag[] = {
	{ "DiagnosticsState", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ "NumberOfRepetitions", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Timeout", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "SuccessCount", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "FailureCount", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "AverageResponseTime", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "MinimumResponseTime", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "MaximumResponseTime", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "SegmentLoopback", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Creator", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANWwanIntfConf[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "Status", PARAMETER_ATTR_READONLY, 32, json_type_string},
	//{ "BandSelection", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ "AccessPointName", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ "PhoneNumber", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ "PINCode", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ "PUKCode", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ "Status", PARAMETER_ATTR_WRITE, 32, json_type_string},
	//{ "Ready3g", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "ConnectionUpTime", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "CheckingTime", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "PowerUpTimeout", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANWwanIntfStatsConf[] = {
	{ "ServiceProvider", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "DeviceStatus", PARAMETER_ATTR_READONLY, 32, json_type_string},
	{ "SignalStrength", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ "SignalQuality", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ "DeviceManufacturer", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ "DeviceModelName", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ "DeviceFirmwareVersion", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ "DeviceIMEI", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "SIMCardIMSI", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "DeviceESN", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "ValidErrorPINTimes", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "ValidErrorPUKTimes", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "BytesSent", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "BytesReceived", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "CellsSent", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "CellsReceived", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "ErrorsSent", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "ErrorsReceived", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "DongleMode", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANWwanEmailConf[] = {
	{ "EmailEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "EmailServerAddr", PARAMETER_ATTR_WRITE, 64, json_type_string},
	{ "EmailTo", PARAMETER_ATTR_WRITE, 256, json_type_string},
	{ "EmailTitle", PARAMETER_ATTR_WRITE, 128, json_type_string},
	{ NULL, 0, 0, 0}
};

#ifdef CONFIG_XPON_SUPPORT
tr98Parameter_t para_WANPonIntfConf[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 10, json_type_string},
	//{ "PonType", PARAMETER_ATTR_READONLY, 10, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WANPonIntfConfStat[] = {
	{ "BytesSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "BytesReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "PacketsSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "PacketsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
#endif
