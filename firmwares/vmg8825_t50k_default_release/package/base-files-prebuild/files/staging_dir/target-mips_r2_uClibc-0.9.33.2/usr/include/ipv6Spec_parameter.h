
tr98Parameter_t para_Ipv6Ppp[] = {
	{ "SupportedNCPs", PARAMETER_ATTR_READONLY, 32, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6PppIntf[] = {
	{ "IPv6CPEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6PppIpv6cp[] = {
	{ "LocalInterfaceIdentifier", PARAMETER_ATTR_READONLY, 45, json_type_string},
	{ "RemoteInterfaceIdentifier", PARAMETER_ATTR_READONLY, 45, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6Router[] = {
	{ "IPv6ForwardingNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6RouterIpv6Fwd[] = {
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

tr98Parameter_t para_Ipv6RouteInfoIntf[] = {
	{ "Status", PARAMETER_ATTR_READONLY, 23, json_type_string},
	{ "Interface", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "SourceRouter", PARAMETER_ATTR_READONLY, 46, json_type_string},
	{ "PreferredRouteFlag", PARAMETER_ATTR_READONLY, 7, json_type_string},
	{ "Prefix", PARAMETER_ATTR_READONLY, 50, json_type_string},
	{ "RouteLifetime", PARAMETER_ATTR_READONLY, 27, json_type_time},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6ND[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "InterfaceSettingNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6RouterAdver[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "InterfaceSettingNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6RouterAdverIntf[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 19, json_type_string},
	{ "Alias", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "Interface", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "ManualPrefixes", PARAMETER_ATTR_WRITE, 41, json_type_string},
	{ "Prefixes", PARAMETER_ATTR_READONLY, 41, json_type_string},
	{ "MaxRtrAdvInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "MinRtrAdvInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "AdvDefaultLifetime", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "AdvManagedFlag", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "AdvOtherConfigFlag", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "AdvMobileAgentFlag", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "AdvPreferredRouterFlag", PARAMETER_ATTR_WRITE, 7, json_type_string},
	{ "AdvNDProxyFlag", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "AdvLinkMTU", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "AdvReachableTime", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "AdvRetransTimer", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "AdvCurHopLimit", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "OptionNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6RouterAdverOpt[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Alias", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "Tag", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Value", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6Ip[] = {
	{ "IPv6Capable", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "IPv6Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "IPv6Status", PARAMETER_ATTR_READONLY, 12, json_type_string},
	{ "ULAPrefix", PARAMETER_ATTR_WRITE, 48, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6IpIntf[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "ULAEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "IPv6Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "IPv6AddressNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "IPv6PrefixNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6IpIntfIpv6Addr[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 24, json_type_string},
	{ "IPAddressStatus", PARAMETER_ATTR_READONLY, 16, json_type_string},
	{ "Alias", PARAMETER_ATTR_WRITE, 64, json_type_string},
	{ "IPAddress", PARAMETER_ATTR_WRITE, 48, json_type_string},
	{ "Origin", PARAMETER_ATTR_READONLY, 24, json_type_string},
	{ "Prefix", PARAMETER_ATTR_WRITE, 128, json_type_string},
	{ "PreferredLifetime", PARAMETER_ATTR_WRITE, 27, json_type_time},
	{ "ValidLifetime", PARAMETER_ATTR_WRITE, 27, json_type_time},
	{ "Anycast", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6IpIntfIpv6Prefix[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 24, json_type_string},
	{ "PrefixStatus", PARAMETER_ATTR_READONLY, 16, json_type_string},
	{ "Alias", PARAMETER_ATTR_WRITE, 64, json_type_string},
	{ "Prefix", PARAMETER_ATTR_WRITE, 24, json_type_string},
	{ "Origin", PARAMETER_ATTR_READONLY, 24, json_type_string},
	{ "StaticType", PARAMETER_ATTR_WRITE, 24, json_type_string},
	{ "ParentPrefix", PARAMETER_ATTR_WRITE, 32, json_type_string},
	{ "ChildPrefixBits", PARAMETER_ATTR_WRITE, 24, json_type_string},
	{ "OnLink", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Autonomous", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "PreferredLifetime", PARAMETER_ATTR_WRITE, 27, json_type_time},
	{ "ValidLifetime", PARAMETER_ATTR_WRITE, 27, json_type_time},
	{ NULL, 0, 0, 0}
};


tr98Parameter_t para_Ipv6NDIntf[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 10, json_type_string},
	{ "Alias", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "Interface", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "RetransTimer", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "RtrSolicitationInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "MaxRtrSolicitations", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "NUDEnable", PARAMETER_ATTR_WRITE, 257, json_type_boolean},
	{ "RSEnable", PARAMETER_ATTR_WRITE, 257, json_type_boolean},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_HostsHost[] = {
	{ "IPAddress", PARAMETER_ATTR_READONLY, 46, json_type_string},
	{ "AddressSource", PARAMETER_ATTR_READONLY, 7, json_type_string},
	{ "DHCPClient", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "LeaseTimeRemaining", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "AssociatedDevice", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "VendorClassID", PARAMETER_ATTR_READONLY, 256, json_type_string},
	{ "ClientID", PARAMETER_ATTR_READONLY, 5, json_type_string},
	{ "UserClassID", PARAMETER_ATTR_READONLY, 5, json_type_string},
	{ "IPv6AddressNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_HostsHostIpv6Addr[] = {
	{ "IPAddress", PARAMETER_ATTR_READONLY, 46, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6DnsSvr[] = {
	{ "DNSServer", PARAMETER_ATTR_WRITE, 46, json_type_string},
	{ "Interface", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "Type", PARAMETER_ATTR_READONLY, 20, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6DnsRly[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6DnsRlyFwd[] = {
	{ "DNSServer", PARAMETER_ATTR_WRITE, 46, json_type_string},
	{ "Interface", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "Type", PARAMETER_ATTR_READONLY, 20, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6Dhcpv6[] = {
	{ "ClientNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6Dhcpv6Client[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Alias", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "Interface", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "Status", PARAMETER_ATTR_READONLY, 10, json_type_string},
	{ "DUID", PARAMETER_ATTR_READONLY, 130, json_type_string},
	{ "RequestAddresses", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "RequestPrefixes", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "RapidCommit", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Renew", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "SuggestedT1", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "SuggestedT2", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "SupportedOptions", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "RequestedOptions", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "ServerNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "SentOptionNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ReceivedOptionNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6Dhcpv6CntSrvAddr[] = {
	{ "SourceAddress", PARAMETER_ATTR_READONLY, 45, json_type_string},
	{ "DUID", PARAMETER_ATTR_READONLY, 130, json_type_string},
	{ "InformationRefreshTime", PARAMETER_ATTR_READONLY, 257, json_type_time},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6Dhcpv6CntSentAddr[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Alias", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "Tag", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Value", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6Dhcpv6CntRrvAddr[] = {
	{ "Tag", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "Value", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "Server", PARAMETER_ATTR_READONLY, 41, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6Dhcpv6Srv[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "PoolNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6Dhcpv6SrvPool[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 10, json_type_string},
	{ "Alias", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "Order", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "Interface", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "DUID", PARAMETER_ATTR_WRITE, 130, json_type_string},
	{ "DUIDExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "VendorClassID", PARAMETER_ATTR_WRITE, 5, json_type_string},
	{ "VendorClassIDExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "UserClassID", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "UserClassIDExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "SourceAddress", PARAMETER_ATTR_WRITE, 45, json_type_string},
	{ "SourceAddressMask", PARAMETER_ATTR_WRITE, 45, json_type_string},
	{ "SourceAddressExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "IANAEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "IANAManualPrefixes", PARAMETER_ATTR_WRITE, 321, json_type_string},
	{ "IANAPrefixes", PARAMETER_ATTR_WRITE, 321, json_type_string},
	{ "IAPDEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "IAPDManualPrefixes", PARAMETER_ATTR_WRITE, 321, json_type_string},
	{ "IAPDPrefixes", PARAMETER_ATTR_WRITE, 321, json_type_string},
	{ "IAPDAddLength", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "ClientNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "OptionNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6Dhcpv6SrvCnt[] = {
	{ "Alias", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "SourceAddress", PARAMETER_ATTR_READONLY, 45, json_type_string},
	{ "Active", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "IPv6AddressNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "OptionNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6Dhcpv6SrvCntV6Addr[] = {
	{ "IPAddress", PARAMETER_ATTR_READONLY, 46, json_type_string},
	{ "PreferredLifetime", PARAMETER_ATTR_READONLY, 27, json_type_time},
	{ "ValidLifetime", PARAMETER_ATTR_READONLY, 27, json_type_time},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6Dhcpv6SrvCntV6Prefix[] = {
	{ "Prefix", PARAMETER_ATTR_READONLY, 50, json_type_string},
	{ "PreferredLifetime", PARAMETER_ATTR_READONLY, 27, json_type_time},
	{ "ValidLifetime", PARAMETER_ATTR_READONLY, 27, json_type_time},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6Dhcpv6SrvCntOpt[] = {
	{ "Tag", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "Value", PARAMETER_ATTR_READONLY, 5, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Ipv6Dhcpv6SrvOpt[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Alias", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "Tag", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Value", PARAMETER_ATTR_WRITE, 65536, json_type_string},
	{ "PassthroughClient", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ NULL, 0, 0, 0}
};
