tr98Parameter_t para_LanDev[] = {	
	{ "LANEthernetInterfaceNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "LANUSBInterfaceNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "LANWLANConfigurationNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ NULL, 0, 0, 0}
};
	
tr98Parameter_t para_LanHostConfMgmt[] = {
	{ "MACAddress", PARAMETER_ATTR_READONLY, 19, json_type_string},
	{ "DHCPServerConfigurable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "DHCPServerEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "DHCPRelay", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "MinAddress", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "MaxAddress", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "ReservedAddresses", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "SubnetMask", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "DNSServers", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "DomainName", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "IPRouters", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "DHCPLeaseTime", PARAMETER_ATTR_WRITE, 0, json_type_int},
	//{ "UseAllocatedWAN", PARAMETER_ATTR_WRITE, 20, json_type_string},
	//{ "AssociatedConnection", PARAMETER_ATTR_WRITE, 257, json_type_string},
	//{ "PassthroughLease", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "PassthroughMACAddress", PARAMETER_ATTR_WRITE, 19, json_type_string},
	//{ "AllowedMACAddress", PARAMETER_ATTR_WRITE, 513, json_type_string},
	{ "IPInterfaceNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "DHCPStaticAddressNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "DHCPOptionNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "DHCPConditionalPoolNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "X_ZYXEL_DNS_Type", PARAMETER_ATTR_WRITE, 16, json_type_string},
#ifdef SUNRISE_STB_PROVISION
	{ "X_ZYXEL_STB_VENDORID", PARAMETER_ATTR_WRITE, 64, json_type_string},
	{ "X_ZYXEL_STB_URL", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "X_ZYXEL_STB_PrCode", PARAMETER_ATTR_WRITE, 64, json_type_string},
	{ "X_ZYXEL_STB_URL_subcode", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_STB_PrCode_subcode", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
#endif
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_IpIntf[] = {	
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "IPInterfaceIPAddress", PARAMETER_ATTR_WRITE, 17, json_type_string},	
	{ "IPInterfaceSubnetMask", PARAMETER_ATTR_WRITE, 17, json_type_string},	
	{ "IPInterfaceAddressingType", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "X_ZYXEL_IfName", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "X_ZYXEL_ConnectionId", PARAMETER_ATTR_WRITE, 17, json_type_int},
	{ "X_ZYXEL_IPR2_MARKING", PARAMETER_ATTR_WRITE, 17, json_type_uint32},
	{ "X_ZYXEL_Group_WAN_IpIface", PARAMETER_ATTR_WRITE, 1500, json_type_string},
#ifdef IPV6INTERFACE_PROFILE
	{ "X_ZYXEL_IPv6Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_IPv6Status", PARAMETER_ATTR_READONLY, 10, json_type_string},
#if 0
	{ "X_ZYXEL_IPv6DNSEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_IPv6LanIdentifierEUI64Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
#endif
	{ "X_ZYXEL_IPv6Origin", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_IPv6IdentifierType", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "X_ZYXEL_IPv6Identifier", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_IPv6AddressNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "X_ZYXEL_IPv6PrefixNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
#endif
	{ "X_ZYXEL_PubLan", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_PubLan_DHCP", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_PubLan_ARP", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_PubLan_IP", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ "X_ZYXEL_PubLan_Mask", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ NULL, 0, 0, 0}
};

#ifdef LANIPALIAS
tr98Parameter_t para_IpAlias[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "IPAddress", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ "SubnetMask", PARAMETER_ATTR_WRITE, 16, json_type_string},
	{ "AddressingType", PARAMETER_ATTR_WRITE, 8, json_type_string},
	{ "X_ZYXEL_IfName", PARAMETER_ATTR_READONLY, 19, json_type_string},
	{ NULL, 0, 0, 0}
};
#endif

#ifdef IPV6INTERFACE_PROFILE
tr98Parameter_t para_IpIntfV6Addr[] = {
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

tr98Parameter_t para_IpIntfV6Prefix[] = {
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
#ifdef ROUTERADVERTISEMENT_PROFILE
tr98Parameter_t para_IpIntfRouterAdver[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 19, json_type_string},
	{ "MaxRtrAdvInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "MinRtrAdvInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "AdvDefaultLifetime", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "AdvManagedFlag", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "AdvOtherConfigFlag", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "AdvLinkMTU", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "AdvReachableTime", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "AdvRetransTimer", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "AdvCurHopLimit", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DNSServers", PARAMETER_ATTR_WRITE, 129, json_type_string},
	{ NULL, 0, 0, 0}
};

#endif
#ifdef IPV6SERVER_PROFILE
tr98Parameter_t para_IpIntfV6Srv[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 19, json_type_string},
	{ "IANAEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "IANAPrefixes", PARAMETER_ATTR_READONLY, 800, json_type_string},//comman separate *8
	{ "IANAManualPrefixes", PARAMETER_ATTR_WRITE, 800, json_type_string},
	{ "X_ZYXEL_DNSServers", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "X_ZYXEL_MinAddress", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_MaxAddress", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ NULL, 0, 0, 0}
};
#endif

tr98Parameter_t para_LanIpFilter[] = {	
	{ "Name", PARAMETER_ATTR_WRITE, 33, json_type_string},	
	{ "SourceAddress", PARAMETER_ATTR_WRITE, 18, json_type_string},	
	{ "DestinationAddress", PARAMETER_ATTR_WRITE, 18, json_type_string},	
	{ "Port", PARAMETER_ATTR_WRITE, 0, json_type_uint32},	
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_LanPortMapp[] = {	
	{ "Enabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "Name", PARAMETER_ATTR_WRITE, 33, json_type_string},	
	{ "ServerIPAddress", PARAMETER_ATTR_WRITE, 18, json_type_string},	
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_DhcpStaticAddr[] = {	
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "Chaddr", PARAMETER_ATTR_WRITE, 19, json_type_string},	
	{ "Yiaddr", PARAMETER_ATTR_WRITE, 19, json_type_string},	
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_DhcpOpt[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Tag", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Value", PARAMETER_ATTR_WRITE, 256+(256/2), json_type_base64},
	//{ "Value", PARAMETER_ATTR_WRITE, 256, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_DhcpCondServPool[] = {	
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "PoolOrder", PARAMETER_ATTR_WRITE, 0, json_type_uint32},	
	{ "SourceInterface", PARAMETER_ATTR_WRITE, 1025, json_type_string},	
	{ "VendorClassID", PARAMETER_ATTR_WRITE, 257, json_type_string},	
	{ "VendorClassIDExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "VendorClassIDMode", PARAMETER_ATTR_WRITE, 11, json_type_string},	
	{ "ClientID", PARAMETER_ATTR_WRITE, 257, json_type_string},	
	{ "ClientIDExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "UserClassID", PARAMETER_ATTR_WRITE, 257, json_type_string},	
	{ "UserClassIDExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "Chaddr", PARAMETER_ATTR_WRITE, 19, json_type_string},	
	{ "ChaddrMask", PARAMETER_ATTR_WRITE, 19, json_type_string},	
	{ "ChaddrExclude", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	//{ "LocallyServed", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "MinAddress", PARAMETER_ATTR_WRITE, 9, json_type_string},	
	{ "MaxAddress", PARAMETER_ATTR_WRITE, 17, json_type_string},	
	{ "ReservedAddresses", PARAMETER_ATTR_WRITE, 513, json_type_string},	
	{ "SubnetMask", PARAMETER_ATTR_WRITE, 17, json_type_string},	
	{ "DNSServers", PARAMETER_ATTR_WRITE, 65, json_type_string},	
	{ "DomainName", PARAMETER_ATTR_WRITE, 65, json_type_string},	
	{ "IPRouters", PARAMETER_ATTR_WRITE, 65, json_type_string},	
	{ "DHCPLeaseTime", PARAMETER_ATTR_WRITE, 0, json_type_int},	
	//{ "UseAllocatedWAN", PARAMETER_ATTR_WRITE, 13, json_type_string},
	//{ "AssociatedConnection", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "DHCPServerIPAddress", PARAMETER_ATTR_WRITE, 17, json_type_string},	
	{ "DHCPStaticAddressNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "DHCPOptionNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_DhcpCondServPoolDhcpStaticAddr[] = {	
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "Chaddr", PARAMETER_ATTR_WRITE, 19, json_type_string},	
	{ "Yiaddr", PARAMETER_ATTR_WRITE, 19, json_type_string},	
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_DhcpCondServPoolDhcpOpt[] = {	
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "Tag", PARAMETER_ATTR_WRITE, 0, json_type_uint32},	
	//{ "Value", PARAMETER_ATTR_WRITE, 256, json_type_string},
	{ "Value", PARAMETER_ATTR_WRITE, 256+(256/2), json_type_base64},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_LanEthIntfConf[] = {	
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ "Status", PARAMETER_ATTR_READONLY, 10, json_type_string},	
	{ "Name", PARAMETER_ATTR_READONLY, 17, json_type_string},	
	{ "MACAddress", PARAMETER_ATTR_READONLY, 19, json_type_string},	
	//{ "MACAddressControlEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "MaxBitRate", PARAMETER_ATTR_WRITE, 7, json_type_string},	
	{ "DuplexMode", PARAMETER_ATTR_WRITE, 6, json_type_string},	
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_LanEthIntfConfStat[] = {	
	{ "BytesSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "BytesReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "PacketsSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
	{ "PacketsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},	
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

tr98Parameter_t para_LanDevWlanCfg[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Status", PARAMETER_ATTR_READONLY, 10, json_type_string},
	{ "Name", PARAMETER_ATTR_READONLY, 17, json_type_string},
	{ "BSSID", PARAMETER_ATTR_READONLY, 19, json_type_string},
	{ "MaxBitRate", PARAMETER_ATTR_WRITE, 5, json_type_string},
	{ "Channel", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "AutoChannelEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "SSID", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "BeaconType", PARAMETER_ATTR_WRITE, 19, json_type_string},
	{ "MACAddressControlEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Standard", PARAMETER_ATTR_READONLY, 8, json_type_string},
	{ "WEPKeyIndex", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "KeyPassphrase", PARAMETER_ATTR_WRITE, 64, json_type_string},
	{ "WEPEncryptionLevel", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "BasicEncryptionModes", PARAMETER_ATTR_WRITE, 15, json_type_string},
	{ "BasicAuthenticationMode", PARAMETER_ATTR_WRITE, 22, json_type_string},
	{ "WPAEncryptionModes", PARAMETER_ATTR_WRITE, 28, json_type_string},
	{ "WPAAuthenticationMode", PARAMETER_ATTR_WRITE, 20, json_type_string},
	{ "IEEE11iEncryptionModes", PARAMETER_ATTR_WRITE, 28, json_type_string},
	{ "IEEE11iAuthenticationMode", PARAMETER_ATTR_WRITE, 26, json_type_string},
	{ "PossibleChannels", PARAMETER_ATTR_READONLY, 1025, json_type_string},
	{ "BasicDataTransmitRates", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "OperationalDataTransmitRates", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "PossibleDataTransmitRates", PARAMETER_ATTR_READONLY, 257, json_type_string},
	//{ "InsecureOOBAccessEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "BeaconAdvertisementEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "SSIDAdvertisementEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "RadioEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "TransmitPowerSupported", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "TransmitPower", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//ZyXEL don't support AutoRateFallBackEnabled in TR098
	//{ "AutoRateFallBackEnabled", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "LocationDescription", PARAMETER_ATTR_WRITE, 4097, json_type_string},
	{ "RegulatoryDomain", PARAMETER_ATTR_WRITE, 4, json_type_string},
	//{ "TotalPSKFailures", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	//{ "TotalIntegrityFailures", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ChannelsInUse", PARAMETER_ATTR_READONLY, 1025, json_type_string},
	//{ "DeviceOperationMode", PARAMETER_ATTR_WRITE, 27, json_type_string},
	//{ "DistanceFromRoot", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "PeerBSSID", PARAMETER_ATTR_WRITE, 19, json_type_string},
	{ "AuthenticationServiceMode", PARAMETER_ATTR_WRITE, 20, json_type_string},
	{ "WMMSupported", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "UAPSDSupported", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "WMMEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "UAPSDEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "TotalBytesSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TotalBytesReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TotalPacketsSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TotalPacketsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TotalAssociations", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "X_ZYXEL_Auto_Channel_Skip", PARAMETER_ATTR_WRITE, 101, json_type_string},
#ifdef ONECONNECT
	{ "X_ZYXEL_AP_AutoConfig", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
#endif
	{ "X_ZYXEL_AutoGenWepKey", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_OperatingFrequencyBand", PARAMETER_ATTR_WRITE, 10, json_type_string},
	{ "X_ZYXEL_OperatingChannelBandwidth", PARAMETER_ATTR_WRITE, 20, json_type_string},
	{ "X_ZYXEL_UpstreamRate", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_DownstreamRate", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_RIFS_Advertisement", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
#ifdef ZYXEL_WIFI_SingleSKU
	{ "X_ZYXEL_SingleSKU", PARAMETER_ATTR_WRITE, 8, json_type_string},
#endif
	{ "X_ZYXEL_SSID_Priority_Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_SSID_Priority", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_Wireless_Mode", PARAMETER_ATTR_WRITE, 8, json_type_string},
#ifdef ELISA_CUSTOMIZATION
	{ "X_ZYXEL_ChanimStats", PARAMETER_ATTR_READONLY, 257, json_type_string},
#endif
#ifdef SUPPORT_WL_WPA_EAP
	{ "X_ZYXEL_RadiusServerIPAddr", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "X_ZYXEL_RadiusServerPort", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_RadiusSecret", PARAMETER_ATTR_WRITE | PARAMETER_ATTR_PASSWORD, 256, json_type_string},
	{ "X_ZYXEL_Preauth", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_ReauthInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_RekeyingInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
#endif
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_LanDevWlanCfgStat[] = {
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


tr98Parameter_t para_LanDevWlanCfgWps[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "DeviceName", PARAMETER_ATTR_READONLY, 33, json_type_string},
	{ "DevicePassword", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "UUID", PARAMETER_ATTR_READONLY, 37, json_type_string},
	//{ "Version", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ConfigMethodsSupported", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "ConfigMethodsEnabled", PARAMETER_ATTR_WRITE, 256, json_type_string},
	//{ "SetupLockedState", PARAMETER_ATTR_READONLY, 26, json_type_string},
	//{ "SetupLock", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "ConfigurationState", PARAMETER_ATTR_READONLY, 16, json_type_string},
	//{ "LastConfigurationError", PARAMETER_ATTR_READONLY, 28, json_type_string},
	//{ "RegistrarNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	//{ "RegistrarEstablished", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
#define WPS_ACCESSPOINT_PIN
#ifdef WPS_ACCESSPOINT_PIN
	{ "X_ZYXEL_WPS_Method", PARAMETER_ATTR_READONLY, 11, json_type_string},
	//{ "X_ZYXEL_WPS_StationPin", PARAMETER_ATTR_WRITE | PARAMETER_ATTR_PASSWORD, 11, json_type_string},
	{ "X_ZYXEL_WPS_Configured", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_WPS_GenDevicePin", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "X_ZYXEL_WPS_DevicePin", PARAMETER_ATTR_READONLY | PARAMETER_ATTR_PASSWORD , 11, json_type_string},
	//
#endif
	{ "X_ZyXEL_TriggerWPSPushButton", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_WPSRunningStatus", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_LanDevWlanCfgAssocDev[] = {
	{ "AssociatedDeviceMACAddress", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "AssociatedDeviceIPAddress", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "AssociatedDeviceAuthenticationState", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "LastRequestedUnicastCipher", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "LastRequestedMulticastCipher", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "LastPMKId", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "LastDataTransmitRate", PARAMETER_ATTR_READONLY, 5, json_type_string},
	{ "SignalStrength", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_LanDevWlanCfgAssocDevStat[] = {
	{ "BytesSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "BytesReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "PacketsSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "PacketsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ErrorsSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "RetransCount", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "FailedRetransCount", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "RetryCount", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "MultipleRetryCount", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_WepKey[] = {
	{ "WEPKey", PARAMETER_ATTR_WRITE | PARAMETER_ATTR_PASSWORD, 129, json_type_string},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Psk[] = {
	{ "PreSharedKey", PARAMETER_ATTR_WRITE | PARAMETER_ATTR_PASSWORD, 65, json_type_string},
	{ "KeyPassphrase", PARAMETER_ATTR_WRITE | PARAMETER_ATTR_PASSWORD, 64, json_type_string},
	//{ "AssociatedDeviceMACAddress", PARAMETER_ATTR_WRITE, 19, json_type_string},
	{ "X_ZYXEL_AutoGenPSK", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_NeiborWifiDiag[] = {
	{ "DiagnosticsState", PARAMETER_ATTR_WRITE, 25, json_type_string},
	{ "ResultNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_NeiborWifiDiagResult[] = {
	{ "Radio", PARAMETER_ATTR_READONLY, 51, json_type_string},
	{ "SSID", PARAMETER_ATTR_READONLY, 33, json_type_string},
	{ "BSSID", PARAMETER_ATTR_READONLY, 17, json_type_string},
	{ "Mode", PARAMETER_ATTR_READONLY, 17, json_type_string},
	{ "Channel", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "SignalStrength", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "SecurityModeEnabled", PARAMETER_ATTR_READONLY, 33, json_type_string},
	{ "EncryptionMode", PARAMETER_ATTR_READONLY, 9, json_type_string},
	{ "OperatingFrequencyBand", PARAMETER_ATTR_READONLY, 9, json_type_string},
	{ "SupportedStandards", PARAMETER_ATTR_READONLY, 13, json_type_string},
	{ "OperatingStandards", PARAMETER_ATTR_READONLY, 13, json_type_string},
	{ "OperatingChannelBandwidth", PARAMETER_ATTR_READONLY, 13, json_type_string},
	{ "BeaconPeriod", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "Noise", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "BasicDataTransferRates", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "SupportedDataTransferRates", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "DTIMPeriod", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Hosts[] = {
#ifdef ZYXEL_ELIMINATE_DHCP_LEASE
	{ "X_ZYXEL_DeleteAllLease", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
#endif
	{ "HostNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

tr98Parameter_t para_Host[] = {
	{ "IPAddress", PARAMETER_ATTR_READONLY, 46, json_type_string},
	{ "AddressSource", PARAMETER_ATTR_READONLY, 7, json_type_string},
	{ "LeaseTimeRemaining", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "MACAddress", PARAMETER_ATTR_READONLY, 18, json_type_string},
	{"Layer2Interface", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "VendorClassID", PARAMETER_ATTR_READONLY, 256, json_type_string},
	{ "ClientID", PARAMETER_ATTR_READONLY, 5, json_type_string},
	{ "UserClassID", PARAMETER_ATTR_READONLY, 5, json_type_string},
	{ "HostName", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "InterfaceType", PARAMETER_ATTR_READONLY, 17, json_type_string},
	{ "Active", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
#ifdef ZYXEL_ELIMINATE_DHCP_LEASE
	{ "X_ZYXEL_DeleteLease", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
#endif
	{ "X_ZYXEL_HostType", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "X_ZYXEL_CapabilityType", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "X_ZYXEL_PhyRate", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "X_ZYXEL_WiFiStatus", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "X_ZYXEL_SignalStrength", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "X_ZYXEL_SNR", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "X_ZYXEL_RSSI", PARAMETER_ATTR_READONLY, 0, json_type_int},
	{ "X_ZYXEL_SoftwareVersion", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "X_ZYXEL_ConnectedAP", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ NULL, 0, 0, 0}
};

#ifdef ZyXEL_DHCP_OPTION125
tr98Parameter_t para_VendorSpecific[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0}
};

tr98Parameter_t para_VendorSpecificProf[] = {
	{ "Option125ManufacturerOUI", PARAMETER_ATTR_WRITE, 255, json_type_string},
	{ "Option125SerialNumber", PARAMETER_ATTR_WRITE, 255, json_type_string},
	{ "Option125ProductClass", PARAMETER_ATTR_WRITE, 255, json_type_string},
	{ "Option125HexBox", PARAMETER_ATTR_WRITE, 0, json_type_boolean},	
	{ NULL, 0, 0}
};
#endif
