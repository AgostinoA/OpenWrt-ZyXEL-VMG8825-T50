tr98Parameter_t para_IpPingDiag[] = {
	{ "DiagnosticsState", PARAMETER_ATTR_WRITE, 29, json_type_string},
	{ "Interface", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "Host", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "NumberOfRepetitions", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Timeout", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "DataBlockSize", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "DSCP", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "SuccessCount", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "FailureCount", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "AverageResponseTime", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "MinimumResponseTime", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "MaximumResponseTime", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_TraceRtDiag[] = {
	{ "DiagnosticsState", PARAMETER_ATTR_WRITE, 29, json_type_string},
	{ "Interface", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "Host", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "NumberOfTries", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Timeout", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "DataBlockSize", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "DSCP", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "MaxHopCount", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "ResponseTime", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "RouteHopsNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_RtHop[] = {
	{ "HopHost", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "HopHostAddress", PARAMETER_ATTR_READONLY, 33, json_type_string},
	{ "HopErrorCode", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "HopRTTimes", PARAMETER_ATTR_READONLY, 17, json_type_string},
	{ NULL, 0, 0}
};

tr98Parameter_t para_PerpDiag[] = {
	{ "DownloadTransports", PARAMETER_ATTR_READONLY, 17, json_type_string},
	{ "UploadTransports", PARAMETER_ATTR_READONLY, 17, json_type_string},
	{ NULL, 0, 0}
};

tr98Parameter_t para_DlDiag[] = {
	{ "DiagnosticsState", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "Interface", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "DownloadURL", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "DSCP", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "EthernetPriority", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_NumOfThreads", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "ROMTime", PARAMETER_ATTR_READONLY, 27, json_type_time},
	{ "BOMTime", PARAMETER_ATTR_READONLY, 27, json_type_time},
	{ "EOMTime", PARAMETER_ATTR_READONLY, 27, json_type_time},
	{ "TestBytesReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TotalBytesReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "X_ZYXEL_TotalBytesSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
#ifdef ZYXEL_DL_DIAG_CALCULATION
	{ "X_ZYXEL_Latency", PARAMETER_ATTR_READONLY, 17, json_type_string},
	{ "X_ZYXEL_RoundTripTime", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "X_ZYXEL_DownloadSpeed", PARAMETER_ATTR_READONLY, 17, json_type_string},
#endif
	{ "TCPOpenRequestTime", PARAMETER_ATTR_READONLY, 27, json_type_time},
	{ "TCPOpenResponseTime", PARAMETER_ATTR_READONLY, 27, json_type_time},
	{ NULL, 0, 0}
};

tr98Parameter_t para_UlDiag[] = {
	{ "DiagnosticsState", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "Interface", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "UploadURL", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "DSCP", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "EthernetPriority", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "TestFileLength", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_NumOfThreads", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "ROMTime", PARAMETER_ATTR_READONLY, 27, json_type_time},
	{ "BOMTime", PARAMETER_ATTR_READONLY, 27, json_type_time},
	{ "EOMTime", PARAMETER_ATTR_READONLY, 27, json_type_time},
	{ "X_ZYXEL_TestBytesSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "X_ZYXEL_TotalBytesReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TotalBytesSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TCPOpenRequestTime", PARAMETER_ATTR_READONLY, 27, json_type_time},
	{ "TCPOpenResponseTime", PARAMETER_ATTR_READONLY, 27, json_type_time},
	{ NULL, 0, 0}
};

tr98Parameter_t para_UdpEchoCfg[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Interface", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "SourceIPAddress", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "UDPPort", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "EchoPlusEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "EchoPlusSupported", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "PacketsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "PacketsResponded", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "BytesReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "BytesResponded", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TimeFirstPacketReceived", PARAMETER_ATTR_READONLY, 27, json_type_time},
	{ "TimeLastPacketReceived", PARAMETER_ATTR_READONLY, 27, json_type_time},
	{ NULL, 0, 0}
};

tr98Parameter_t para_UdpEchoDiag[] = {
	{ "DiagnosticsState", PARAMETER_ATTR_WRITE, 29, json_type_string},
	{ "Interface", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "Host", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "Port", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "NumberOfRepetitions", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Timeout", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "DataBlockSize", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "DSCP", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "InterTransmissionTime", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "ProtocolVersion", PARAMETER_ATTR_WRITE, 9, json_type_string},
	{ "IPAddressUsed", PARAMETER_ATTR_WRITE, 46, json_type_string},
	{ "SuccessCount", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "FailureCount", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "AverageResponseTime", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "MinimumResponseTime", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "MaximumResponseTime", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "EnableIndividualPacketResults", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "IndividualPacketResultNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "UDPEchoDiagnosticsMaxResults", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_UdpEchoDiagPakRst[] = {
	{ "PacketSuccess", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "PacketSendTime", PARAMETER_ATTR_READONLY, 27, json_type_time},
	{ "PacketReceiveTime", PARAMETER_ATTR_READONLY, 27, json_type_time},
	{ "TestGenSN", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TestRespSN", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TestRespRcvTimeStamp", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TestRespReplyTimeStamp", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TestRespReplyFailureCount", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};