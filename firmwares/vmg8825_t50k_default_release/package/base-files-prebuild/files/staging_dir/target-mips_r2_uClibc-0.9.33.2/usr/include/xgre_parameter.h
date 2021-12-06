
tr98Parameter_t para_XGRE[] = {
    { "TunnelNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
    { NULL, 0, 0, 0}
};

tr98Parameter_t para_XGRETunnel[] = {
    { "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
    { "VlanId", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
    { "RemoteEndpoints", PARAMETER_ATTR_WRITE, 1025, json_type_string},
    { "ConnectedRemoteEndpoint", PARAMETER_ATTR_READONLY, 257, json_type_string},
    { "BoundWanInterfaces", PARAMETER_ATTR_WRITE, 129, json_type_string},
    { "BoundLanInterfaces", PARAMETER_ATTR_WRITE, 1025, json_type_string},
    //{ "Checksum", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
    //{ "Seq", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
    //{ "Key", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
    { "UpRate", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
    { "DownRate", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
    { "DSCP", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
    { NULL, 0, 0, 0}
};

tr98Parameter_t para_XGRETunnelStats[] = {
    { "BytesSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
    { "BytesReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
    { "PacketsSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
    { "PacketsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
    { "ErrorsSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
    { "ErrorsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
    { "DiscardPacketsSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
    { "DiscardPacketsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
    { NULL, 0, 0, 0}
};

