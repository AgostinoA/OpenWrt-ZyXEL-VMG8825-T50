
#ifdef CONFIG_PACKAGE_ZyIMS
tr98Parameter_t para_Service[] = {
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceSrv[] = {
	{ "VoiceProfileNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	//{ "X_ZYXEL_LoggingLevel", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceCapb[] = {
	{ "MaxProfileCount", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "MaxLineCount", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "MaxSessionsPerLine", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "MaxSessionCount", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "SignalingProtocols", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "Regions", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "RTCP", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "SRTP", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "SRTPKeyingMethods", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "SRTPEncryptionKeySizes", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "RTPRedundancy", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "DSCPCoupled", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "EthernetTaggingCoupled", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "PSTNSoftSwitchOver", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "FaxT38", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "FaxPassThrough", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "ModemPassThrough", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "ToneGeneration", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "ToneDescriptionsEditable", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "PatternBasedToneGeneration", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "FileBasedToneGeneration", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "ToneFileFormats", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "RingGeneration", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "RingDescriptionsEditable", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "PatternBasedRingGeneration", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "RingPatternEditable", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "FileBasedRingGeneration", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "RingFileFormats", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "DigitMap", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "NumberingPlan", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "ButtonMap", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "VoicePortTests", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	//{ "X_ZYXEL_Pound", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceCapbSip[] = {
	{ "Role", PARAMETER_ATTR_READONLY, 33, json_type_string},
	{ "Extensions", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "Transports", PARAMETER_ATTR_READONLY, 33, json_type_string},
	{ "URISchemes", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "EventSubscription", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "ResponseMap", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "TLSAuthenticationProtocols", PARAMETER_ATTR_READONLY, 33, json_type_string},
	{ "TLSAuthenticationKeySizes", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "TLSEncryptionProtocols", PARAMETER_ATTR_READONLY, 33, json_type_string},
	{ "TLSEncryptionKeySizes", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "TLSKeyExchangeProtocols", PARAMETER_ATTR_READONLY, 33, json_type_string},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceCapbMgcp[] = {
	{ "Extensions", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceCapbH323[] = {
	{ "FastStart", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "H235AuthenticationMethods", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceCapbCodec[] = {
	{ "Alias", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "EntryID", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "Codec", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "BitRate", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "PacketizationPeriod", PARAMETER_ATTR_READONLY, 257, json_type_string},
	{ "SilenceSuppression", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceProf[] = {
	//{ "X_ZYXEL_ProfObjID", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "Enable", PARAMETER_ATTR_WRITE, 17, json_type_string},
	//{ "Reset", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "NumberOfLines", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "Name", PARAMETER_ATTR_WRITE, 65, json_type_string},
	//{ "SignalingProtocol", PARAMETER_ATTR_WRITE, 65, json_type_string},
	//{ "MaxSessions", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "DTMFMethodG711", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "DTMFMethod", PARAMETER_ATTR_WRITE, 33, json_type_string},
	//{ "X_ZYXEL_HookFlashMethod", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "Region", PARAMETER_ATTR_WRITE, 3, json_type_string},
	{ "X_ZYXEL_Region_IntlPhoneNumCallingCode", PARAMETER_ATTR_WRITE, 17, json_type_string}, //Michael.20190604.001: Add to support a Manually-Configurable/Customized International PhoneNumber Calling Code parameter for the PlusSign(+)-beginning (International) PhoneNumber CLID Display Process Logic. Related Tickets: [#190400265][#105337][VMG8825-B60B][Generic][DE], [#190401061][#105665][VMG8825-T50K][T-Mobile-NL].
#ifdef USE_OLD_VOIP_PREFIX
	//{ "X_ZyXEL_COM_Countrycode", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
#else
	//{ "X_ZYXEL_Countrycode", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
#endif
	{ "DigitMap", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "DigitMapEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "STUNEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "STUNServer", PARAMETER_ATTR_WRITE, 257, json_type_string},
	//{ "X_ZYXEL_STUNServerPort", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "NonVoiceBandwidthReservedUpstream", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "NonVoiceBandwidthReservedDownstream", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "PSTNFailOver", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "FAXPassThrough", PARAMETER_ATTR_WRITE, 33, json_type_string},
	//{ "X_ZYXEL_FaxPassthroughPCMA", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "ModemPassThrough", PARAMETER_ATTR_WRITE, 33, json_type_string},
#ifdef USE_OLD_VOIP_PREFIX
	{ "X_ZyXEL_COM_FaxMode", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZyXEL_COM_BoundIfName", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZyXEL_COM_BoundIfList", PARAMETER_ATTR_WRITE, 513, json_type_string},
	{ "X_ZyXEL_COM_ActiveBoundIfName", PARAMETER_ATTR_READONLY, 33, json_type_string},
	{ "X_ZyXEL_COM_BoundIpAddr", PARAMETER_ATTR_READONLY, 18, json_type_string},
	{ "X_ZyXEL_COM_FlashUsageStyle", PARAMETER_ATTR_WRITE, 257, json_type_string},
#else
	{ "X_ZYXEL_FaxMode", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_BoundIfName", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_BoundIfList", PARAMETER_ATTR_WRITE, 513, json_type_string},
	{ "X_ZYXEL_ActiveBoundIfName", PARAMETER_ATTR_READONLY, 33, json_type_string},
	{ "X_ZYXEL_BoundIpAddr", PARAMETER_ATTR_READONLY, 18, json_type_string},
	{ "X_ZYXEL_FlashUsageStyle", PARAMETER_ATTR_WRITE, 257, json_type_string},
#endif
	//{ "X_ZYXEL_LogServer", PARAMETER_ATTR_WRITE, 65, json_type_string},
	//{ "X_ZYXEL_LogServerPort", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "X_ZYXEL_SPNum", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "X_ZYXEL_V18_Support", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_VoipIOPFlags", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_VoipSigIOPFlags", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_VoipMediaIOPFlags", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "X_ZYXEL_P_AccessNetworkInfo", PARAMETER_ATTR_WRITE, 128, json_type_string},
	//{ "X_ZYXEL_BoundIfName", PARAMETER_ATTR_WRITE, 33, json_type_string},
	//{ "X_ZYXEL_BoundIfList", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceProfSrvProInfo[] = {
	{ "Name", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "URL", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "ContactPhoneNumber", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "EmailAddress", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceProfSip[] = {
	{ "ProxyServer", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "ProxyServerPort", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "ProxyServerTransport", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "RegistrarServer", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "RegistrarServerPort", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "RegistrarServerTransport", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "UserAgentDomain", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "UserAgentPort", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "UserAgentTransport", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "OutboundProxy", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "OutboundProxyPort", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "X_ZYXEL_OutboundKAIntvl", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "X_ZYXEL_KAServer", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "X_ZYXEL_FakeSipIP", PARAMETER_ATTR_WRITE, 130, json_type_string},
	//{ "X_ZYXEL_FakeSipPort", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "Organization", PARAMETER_ATTR_WRITE, 257, json_type_string},
	//{ "RegistrationPeriod", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "TimerT1", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "TimerT2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "TimerT4", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "TimerA", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "TimerB", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "TimerC", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "TimerD", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "TimerE", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "TimerF", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "TimerG", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "TimerH", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "TimerI", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "TimerJ", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "TimerK", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "InviteExpires", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "ReInviteExpires", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
#ifdef USE_OLD_VOIP_PREFIX
	{ "X_ZyXEL_COM_MinSE", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
#else
	{ "X_ZYXEL_MinSE", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
#endif
	//{ "X_ZYXEL_MwiExpireTime", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "RegisterExpires", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "RegistersMinExpires", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "RegisterRetryInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "InboundAuth", PARAMETER_ATTR_WRITE, 33, json_type_string},
	//{ "InboundAuthUsername", PARAMETER_ATTR_WRITE, 257, json_type_string},
	//{ "InboundAuthPassword", PARAMETER_ATTR_WRITE | PARAMETER_ATTR_PASSWORD, 257, json_type_string},
	//{ "UseCodecPriorityInSDPResponse", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "DSCPMark", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "X_ZYXEL_SigVLanTagTPID", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "X_ZYXEL_SigVLanTagTCI", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "X_ZYXEL_Rfc3325Support", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
#ifdef USE_OLD_VOIP_PREFIX
	{ "X_ZyXEL_COM_Rfc3262Support", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
#else
	{ "X_ZYXEL_Rfc3262Support", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
#endif
	//{ "VLANIDMark", PARAMETER_ATTR_WRITE, 0, json_type_int},
	//{ "EthernetPriorityMark", PARAMETER_ATTR_WRITE, 0, json_type_int},
	//{ "SIPEventSubscribeNumberOfElements", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	//{ "SIPResponseMapNumberOfElements", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	//{ "X_ZYXEL_HeartbeatEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "X_ZYXEL_RateOfHeartbeat", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
#ifdef USE_OLD_VOIP_PREFIX
	{ "X_ZyXEL_COM_Rfc3263Support", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
#else
	{ "X_ZYXEL_Rfc3263Support", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
#endif
	{ "X_ZYXEL_BackupServer", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceProfSipSubscribeObj[] = {
	{ "Event", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "Notifier", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "NotifierPort", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "NotifierTransport", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "ExpireTime", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceProfSipRespMapObj[] = {
	{ "SIPResponseNumber", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "TextMessage", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "Tone", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceProfRtp[] = {
	{ "LocalPortMin", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "LocalPortMax", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "DSCPMark", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "VLANIDMark", PARAMETER_ATTR_WRITE, 0, json_type_int},
	//{ "EthernetPriorityMark", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "TelephoneEventPayloadType", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceProfRtpRtcp[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "TxRepeatInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "LocalCName", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceProfRtpSrtp[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "KeyingMethods", PARAMETER_ATTR_WRITE, 257, json_type_string},
	//{ "EncryptionKeySizes", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "X_ZYXEL_Crypto_Suite_Name", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceProfRtpRedundancy[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "PayloadType", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "BlockPayloadType", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "FaxAndModemRedundancy", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "ModemRedundancy", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "DTMFRedundancy", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "VoiceRedundancy", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "MaxSessionsUsingRedundancy", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceProfNumPlan[] = {
	//{ "MinimumNumberOfDigits", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "MaximumNumberOfDigits", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "InterDigitTimerStd", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "InterDigitTimerOpen", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
#ifdef USE_OLD_VOIP_PREFIX
	{ "X_ZyXEL_COM_DialingLongInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
#else
	{ "X_ZYXEL_DialingLongInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
#endif
	//{ "X_ZYXEL_TimerFirstDigitWarmLine", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "InvalidNumberTone", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "PrefixInfoMaxEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "PrefixInfoNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceProfNumPlanPrefixInfo[] = {
	{ "PrefixRange", PARAMETER_ATTR_WRITE, 43, json_type_string},
	{ "PrefixMinNumberOfDigits", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "PrefixMaxNumberOfDigits", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "NumberOfDigitsToRemove", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "PosOfDigitsToRemove", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "DialTone", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "FacilityAction", PARAMETER_ATTR_READONLY, 65, json_type_string},
	//{ "FacilityActionArgument", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceProfTone[] = {
	{ "EventNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "DescriptionNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "PatternNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceProfToneEvent[] = {
	{ "Function", PARAMETER_ATTR_READONLY, 33, json_type_string},
	{ "ToneID", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceProfToneDescription[] = {
	{ "EntryID", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ToneEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "ToneName", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "TonePattern", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "ToneFile", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "ToneRepetitions", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "ToneText", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceProfTonePattern[] = {
	{ "EntryID", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "ToneOn", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Frequency1", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Power1", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "Frequency2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Power2", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "Frequency3", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Power3", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "Frequency4", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Power4", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "ModulationFrequency", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "ModulationPower", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "Duration", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "NextEntryID", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceProfFaxT38[] = {
	{ "Enable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "BitRate", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "HighSpeedPacketRate", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "LowSpeedRedundancy", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "HighSpeedRedundancy", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TCFMethod", PARAMETER_ATTR_READONLY, 33, json_type_string},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceLine[] = {
	//{ "X_ZYXEL_LineID", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Enable", PARAMETER_ATTR_WRITE, 17, json_type_string},
	{ "DirectoryNumber", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "Status", PARAMETER_ATTR_READONLY, 33, json_type_string},
	{ "CallState", PARAMETER_ATTR_READONLY, 129, json_type_string},
	{ "PhyReferenceList", PARAMETER_ATTR_WRITE, 33, json_type_string},
#ifdef USE_OLD_VOIP_PREFIX
	{ "X_ZyXEL_COM_PhyReferenceFXSList", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
#else
	{ "X_ZYXEL_PhyReferenceFXSList", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
#endif
	//{ "X_ZYXEL_AutoDialEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "X_ZYXEL_AutoDialNumber", PARAMETER_ATTR_WRITE, 38, json_type_string},
	{ "RingMuteStatus", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "RingVolumeStatus", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	//{ "X_ZYXEL_CMAcntNum", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceLineSip[] = {
	{ "AuthUserName", PARAMETER_ATTR_WRITE, 129, json_type_string},
	{ "AuthPassword", PARAMETER_ATTR_WRITE | PARAMETER_ATTR_PASSWORD, 129, json_type_string},
	{ "URI", PARAMETER_ATTR_WRITE, 390, json_type_string},
	//{ "X_ZYXEL_RegistrarType", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_Url_Type", PARAMETER_ATTR_WRITE, 33, json_type_string},
	//{ "X_ZYXEL_CallFwdTableIndex", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "SIPEventSubscribeNumberOfElements", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	//{ "X_ZYXEL_RemoteRingbackTone", PARAMETER_ATTR_WRITE, 33, json_type_string},
#ifdef USE_OLD_VOIP_PREFIX
	{ "X_ZyXEL_COM_MixerMode", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZyXEL_COM_P_AccessNetworkInfo", PARAMETER_ATTR_WRITE, 129, json_type_string},
#else
	{ "X_ZYXEL_MixerMode", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_P_AccessNetworkInfo", PARAMETER_ATTR_WRITE, 129, json_type_string},
#endif
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceLineSipEventSubs[] = {
	{ "Event", PARAMETER_ATTR_READONLY, 33, json_type_string},
	{ "AuthUserName", PARAMETER_ATTR_WRITE, 129, json_type_string},
	{ "AuthPassword", PARAMETER_ATTR_WRITE | PARAMETER_ATTR_PASSWORD, 129, json_type_string},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceLineRinger[] = {
	{ "EventNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "DescriptionNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "PatternNumberOfEntries", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceLineRingerEvent[] = {
	{ "Function", PARAMETER_ATTR_READONLY, 33, json_type_string},
	{ "RingID", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceLineRingerDescription[] = {
	{ "EntryID", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "RingEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "RingName", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "RingPattern", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "RingFile", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceLineRingerPattern[] = {
	{ "EntryID", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "RingerOn", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "Duration", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "NextEntryID", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceLineCallingFeature[] = {
	{ "CallerIDEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "CallerIDNameEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "CallerIDName", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "CallWaitingEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "X_ZYXEL_CallWaitingStart", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "CallWaitingStatus", PARAMETER_ATTR_READONLY, 33, json_type_string},
	{ "X_ZYXEL_CallWaitingRejectTime", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "MaxSessions", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "ConferenceCallingStatus", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	//{ "X_ZYXEL_ConferenceURI", PARAMETER_ATTR_WRITE, 50, json_type_string},
	{ "ConferenceCallingSessionCount", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "CallForwardUnconditionalEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "X_ZYXEL_CallForwardUnconditionalStart", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "CallForwardUnconditionalNumber", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "CallForwardOnBusyEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "X_ZYXEL_CallForwardOnBusyStart", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "CallForwardOnBusyNumber", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "CallForwardOnNoAnswerEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "X_ZYXEL_CallForwardOnNoAnswerStart", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "CallForwardOnNoAnswerNumber", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "CallForwardOnNoAnswerRingCount", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "CallTransferEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "MWIEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_MwiExpireTime", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "MessageWaiting", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "AnonymousCallBlockEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "X_ZYXEL_AnonymousCallBlockStart", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "AnonymousCalEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "X_ZYXEL_AnonymousCallStart", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "DoNotDisturbEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "X_ZYXEL_DoNotDisturbStart", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "CallReturnEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "RepeatDialEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "X_ZYXEL_CallTransferAfterConference", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_TimerFirstDigitWarmLine", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_HotLineEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_HotLineNum", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "X_ZYXEL_RemoteRingbackTone", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_RemoteRingbackToneIndex", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_MusicOnHoldTone", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_MusicOnHoldToneIndex", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_MissedCallEmailEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_MissedCallEmailServerAddr", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "X_ZYXEL_MissedCallEmailToAddr", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "X_ZYXEL_MissedCallEmailTitle", PARAMETER_ATTR_WRITE, 65, json_type_string},
	{ "X_ZYXEL_CCBSEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "X_ZYXEL_CAllCompletionOnBusyEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "X_ZYXEL_SpeedDialEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_WarmLineEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "X_ZYXEL_WarmLineStart", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_WarmLineNumber", PARAMETER_ATTR_WRITE, 33, json_type_string},
	//{ "X_ZYXEL_CallBarringEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "X_ZYXEL_CallBarringMode", PARAMETER_ATTR_WRITE, 33, json_type_string},
	//{ "X_ZYXEL_CallBarringUserPin", PARAMETER_ATTR_WRITE, 11, json_type_string},
	//{ "X_ZYXEL_CallBarringDigitMap", PARAMETER_ATTR_WRITE, 257, json_type_string},
	//{ "X_ZYXEL_NetworkPrivacyEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "X_ZYXEL_NetworkPrivacyStart", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "X_ZYXEL_VMWIEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "X_ZYXEL_EnumEnablee", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "X_ZYXEL_EnumStart", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceLineProcessing[] = {
	{ "TransmitGain", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "ReceiveGain", PARAMETER_ATTR_WRITE, 0, json_type_int},
	{ "EchoCancellationEnable", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "EchoCancellationInUse", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	//{ "EchoCancellationTail", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceLineCodec[] = {
	{ "TransmitCodec", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "ReceiveCodec", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "TransmitBitRate", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ReceiveBitRate", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TransmitSilenceSuppression", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "ReceiveSilenceSuppression", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "TransmitPacketizationPeriod", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceLineCodecList[] = {
	{ "EntryID", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "Codec", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "BitRate", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "PacketizationPeriod", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "SilenceSuppression", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
#ifdef USE_OLD_VOIP_PREFIX
	{ "X_ZyXEL_COM_ComfortNoise", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
#else
	{ "X_ZYXEL_ComfortNoise", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
#endif
	{ "Enable", PARAMETER_ATTR_READONLY, 0, json_type_boolean},
	{ "Priority", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceLineSession[] = {
	{ "SessionStartTime", PARAMETER_ATTR_READONLY, 0, json_type_time},
	{ "SessionDuration", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "FarEndIPAddress", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "FarEndUDPPort", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "LocalUDPPort", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceLineStats[] = {
	{ "ResetStatistics", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "PacketsSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "PacketsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "BytesSent", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "BytesReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "PacketsLost", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "Overruns", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "Underruns", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "IncomingCallsReceived", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "IncomingCallsAnswered", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "IncomingCallsConnected", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "IncomingCallsFailed", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "OutgoingCallsAttempted", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "OutgoingCallsAnswered", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "OutgoingCallsConnected", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "OutgoingCallsFailed", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "CallsDropped", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "TotalCallTime", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	//{ "ServerDownTime", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ReceivePacketLossRate", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "FarEndPacketLossRate", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "ReceiveInterarrivalJitter", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "FarEndInterarrivalJitter", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "RoundTripDelay", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "AverageReceiveInterarrivalJitter", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "AverageFarEndInterarrivalJitter", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "AverageRoundTripDelay", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
#ifdef USE_OLD_VOIP_PREFIX
	{ "X_ZyXEL_LastIncommingNumber", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "X_ZyXEL_LastOutgoingNumber", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "X_ZyXEL_LastRegistration", PARAMETER_ATTR_READONLY, 65, json_type_string},
#else
	{ "X_ZYXEL_LastIncommingNumber", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "X_ZYXEL_LastOutgoingNumber", PARAMETER_ATTR_READONLY, 65, json_type_string},
	{ "X_ZYXEL_LastRegistration", PARAMETER_ATTR_READONLY, 65, json_type_string},
#endif
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoicePhyIntf[] = {
	{ "PhyPort", PARAMETER_ATTR_READONLY, 3, json_type_string},
	{ "InterfaceID", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ "Description", PARAMETER_ATTR_READONLY, 33, json_type_string},
	//{ "X_ZYXEL_PotsType", PARAMETER_ATTR_WRITE, 33, json_type_string},
	//{ "X_ZYXEL_DialingType", PARAMETER_ATTR_WRITE, 33, json_type_string},
	//{ "X_ZYXEL_DialToneType", PARAMETER_ATTR_WRITE, 33, json_type_string},
	//{ "X_ZYXEL_ReceiveToneType", PARAMETER_ATTR_WRITE, 33, json_type_string},
	//{ "X_ZYXEL_FlashMaxInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "X_ZYXEL_FlashMinInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "X_ZYXEL_JitterBufSize", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "X_ZYXEL_CallerIDType", PARAMETER_ATTR_WRITE, 33, json_type_string},
	//{ "X_ZYXEL_CallerIDPayload", PARAMETER_ATTR_WRITE, 33, json_type_string},
	//{ "X_ZYXEL_TasTimeoutInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "X_ZYXEL_TasTimeoutInterval_2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "X_ZYXEL_CallerIDRingTimeout", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "X_ZYXEL_FirstRingTimoutInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "X_ZYXEL_FirstTASType", PARAMETER_ATTR_WRITE, 33, json_type_string},
	//{ "X_ZYXEL_SecondTASType", PARAMETER_ATTR_WRITE, 33, json_type_string},
	//{ "X_ZYXEL_CallerID_DTAS_ACK_Timeout", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
#ifdef USE_OLD_VOIP_PREFIX
	{ "X_ZyXEL_COM_LineSelect", PARAMETER_ATTR_WRITE, 256, json_type_string},
#else
	{ "X_ZYXEL_LineSelect", PARAMETER_ATTR_WRITE, 256, json_type_string},
#endif
	{ "X_ZYXEL_HookState", PARAMETER_ATTR_READONLY, 32, json_type_string},
	//{ "X_ZYXEL_MsnIncomingSelect", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "X_ZYXEL_MsnOutgoingSelect", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "X_ZYXEL_HowlerToneTimeout", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "X_ZYXEL_Pound", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	{ "X_ZYXEL_HookFlashIgnore", PARAMETER_ATTR_WRITE, 0, json_type_boolean}, //Michael.20190301.002: Add to Support to Disable/Remove the Phone Hook Flash function by Using a (PhyInterface-level dedicated) Parameter 'X_ZYXEL_HookFlashIgnore' to Ignore the Phone Hook Flash Event. Related Tickets: [eITS#170700466][#39697][HTC], [eITS#180901009][Altibox] and [eITS#181100069][#68892][EU Generic].
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoicePstn[] = {
	{ "OutgoingCallDialPlan", PARAMETER_ATTR_WRITE, 129, json_type_string},
	{ "IncomingCallRoutingMode", 33, json_type_string},
	{ "IncomingCallRoutingDest", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "ForcePSTNTab", PARAMETER_ATTR_WRITE, 37, json_type_string},
	{ "Flags", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Reversed", PARAMETER_ATTR_WRITE, 3, json_type_string},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceCommon[] = {
	//{ "IfName", PARAMETER_ATTR_READONLY, 33, json_type_string},
	//{ "VoipPort", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "Ivrsyspermit", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "IvrLanguage", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "Ivrcodec", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "SpecialFlag", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	//{ "CallFallBack", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "Activedialplan", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "DialPlan", PARAMETER_ATTR_WRITE, 257, json_type_string},
	//{ "DialMethod", PARAMETER_ATTR_WRITE, 257, json_type_string},
	//{ "X_ZYXEL_Pound", PARAMETER_ATTR_WRITE, 0, json_type_boolean},
	//{ "VoipIOPFlags", PARAMETER_ATTR_WRITE, 0, json_type_uint32}, //Michael.20190616.001: Remarked to disabled the parameter '~.Services.VoiceService.{i}.X_ZYXEL_Common.VoipIOPFlags' from being accessed via the ACS/TR-069.
	{ "P_AccessNetworkInfo", PARAMETER_ATTR_WRITE, 129, json_type_string},
	{ "UserAgent_strReplaceRule", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "FxsCIDMode", PARAMETER_ATTR_WRITE, 17, json_type_string}, //Michael.20190516.002: Add two parameters (1)'FxsCIDMode' and (2)'FxsCIDSigProtocol' in the TR-104 data model branch '~.Services.VoiceService.{i}.X_ZYXEL_Common.' to support the feature done by 'Michael.20190516.001' to Manually-Configure/Customize the Caller-ID (CLID) Operation Mode.
	{ "FxsCIDSigProtocol", PARAMETER_ATTR_WRITE, 9, json_type_string}, //Michael.20190516.002: Add two parameters (1)'FxsCIDMode' and (2)'FxsCIDSigProtocol' in the TR-104 data model branch '~.Services.VoiceService.{i}.X_ZYXEL_Common.' to support the feature done by 'Michael.20190516.001' to Manually-Configure/Customize the Caller-ID (CLID) Operation Mode.
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoicePhoneBook[] = {
	{ "OrigNumber", PARAMETER_ATTR_READONLY, 129, json_type_string},
	{ "ForceSipURI", PARAMETER_ATTR_WRITE, 257, json_type_string},
	{ "SpeedNumber", PARAMETER_ATTR_WRITE, 129, json_type_string},
	{ "Name", PARAMETER_ATTR_WRITE, 129, json_type_string},
	{ "Flags", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ "Type", PARAMETER_ATTR_WRITE, 33, json_type_string},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceFxo[] = {
	{ "NumberOfPort", PARAMETER_ATTR_READONLY, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};
tr98Parameter_t para_VoiceFxoPort[] = {
	{ "FxoDialLongInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "FxoPhoneSelect", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "FxoDTMFPauseDuration", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "FxoFlashMinInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "FxoFlashMaxInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "FxoLifeLineStableTime", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "FxoDTMFDigitDuration", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "Reversed2", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "PollingPollarityTime", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ "DetectCIDInterval", PARAMETER_ATTR_WRITE, 0, json_type_uint32},
	{ NULL, 0, 0, 0}
};

/* InternetGatewayDevice.Services.VoiceService.i */
extern zcfgRet_t voiceSrvObjGet(char * tr98FullPathName,int handler,struct json_object * * tr98Jobj,bool updateFlag);
extern zcfgRet_t voiceNotify(char *tr98ObjName, struct json_object *tr181ParamObj, int handler, struct json_object **tr98NotifyInfo);
extern int voiceSrvAttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t voiceSrvAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);

/* InternetGatewayDevice.Services.VoiceService.i.Capabilities */
extern zcfgRet_t voiceCapbObjGet(char * tr98FullPathName,int handler,struct json_object * * tr98Jobj,bool updateFlag);
extern int voiceCapbAttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t voiceCapbAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);

/* InternetGatewayDevice.Services.VoiceService.i.X_ZYXEL_Common */
extern zcfgRet_t voiceCommonObjGet(char * tr98FullPathName,int handler,struct json_object * * tr98Jobj,bool updateFlag);
extern zcfgRet_t voiceCommonSet(char * tr98FullPathName,int handler,struct json_object * tr98Jobj,struct json_object * multiJobj);
#if 0
extern int voiceCommonAttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t voiceCommonAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);
#endif

/* InternetGatewayDevice.Services.VoiceService.i.Capabilities.SIP */
extern zcfgRet_t voiceCapbSipObjGet(char * tr98FullPathName,int handler,struct json_object * * tr98Jobj,bool updateFlag);
extern int voiceCapbSipAttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t voiceCapbSipAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);

/* InternetGatewayDevice.Services.VoiceService.i.Capabilities.Codec.i */
extern zcfgRet_t voiceCapbCodecObjGet(char * tr98FullPathName,int handler,struct json_object * * tr98Jobj,bool updateFlag);
extern int voiceCapbCodecAttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t voiceCapbCodecAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);

/* InternetGatewayDevice.Services.VoiceService.i.voiceProfile.i */
extern zcfgRet_t voiceProfObjGet(char * tr98FullPathName,int handler,struct json_object * * tr98Jobj,bool updateFlag);
extern zcfgRet_t voiceProfSet(char * tr98FullPathName,int handler,struct json_object * tr98Jobj,struct json_object * multiJobj);
extern zcfgRet_t voiceProfAdd(char * tr98FullPathName,int * idx);
extern zcfgRet_t voiceProfDel(char * tr98FullPathName);
extern int voiceProfAttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t voiceProfAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);

/* InternetGatewayDevice.Services.VoiceService.i.voiceProfile.i.SIP */
extern zcfgRet_t voiceProfSipObjGet(char * tr98FullPathName,int handler,struct json_object * * tr98Jobj,bool updateFlag);
extern zcfgRet_t voiceProfSipSet(char * tr98FullPathName,int handler,struct json_object * tr98Jobj,struct json_object * multiJobj);
extern int voiceProfSipAttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t voiceProfSipAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);

/* InternetGatewayDevice.Services.VoiceService.i.VoiceProfile.i.RTP*/
extern zcfgRet_t voiceProfRtpObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t voiceProfRtpObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj, char *paramfault);
extern int voiceProfRtpAttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t voiceProfRtpAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);

/* InternetGatewayDevice.Services.VoiceService.i.VoiceProfile.i.RTP.RTCP*/
extern zcfgRet_t voiceProfRtpRtcpObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t voiceProfRtpRtcpObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj, char *paramfault);
extern int voiceProfRtpRtcpAttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t voiceProfRtpRtcpAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);

/* InternetGatewayDevice.Services.VoiceService.i.VoiceProfile.i.RTP.SRTP*/
extern zcfgRet_t voiceProfRtpSrtpObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t voiceProfRtpSrtpObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj, char *paramfault);
extern int voiceProfRtpSrtpAttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t voiceProfRtpSrtpAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);

/* InternetGatewayDevice.Services.VoiceService.i.voiceProfile.i.NumberingPlan.*/
extern zcfgRet_t voiceProfNumPlanObjGet(char * tr98FullPathName,int handler,struct json_object * * tr98Jobj,bool updateFlag);
extern zcfgRet_t voiceProfNumPlanObjSet(char * tr98FullPathName,int handler,struct json_object * tr98Jobj,struct json_object * multiJobj);
extern int voiceProfNumPlanAttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t voiceProfNumPlanAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);

/*Device.Services.VoiceService.i.VoiceProfile.i.NumberingPlan.PrefixInfo.i*/
zcfgRet_t voiceProfNumPlanPrefixInfoObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
zcfgRet_t voiceProfNumPlanPrefixInfoObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj, char *paramfault);
int voiceProfNumPlanPrefixInfoAttrGet(char *tr98FullPathName, int handler, char *paramName);
zcfgRet_t voiceProfNumPlanPrefixInfoAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);

/* InternetGatewayDevice.Services.VoiceService.i.voiceProfile.i.FaxT38.*/
/*yushiuan add for FaxT38 Object 2015/11/27*/
extern zcfgRet_t voiceProfFaxT38ObjGet(char * tr98FullPathName,int handler,struct json_object * * tr98Jobj,bool updateFlag);
extern zcfgRet_t voiceProfFaxT38ObjSet(char * tr98FullPathName,int handler,struct json_object * tr98Jobj,struct json_object * multiJobj);
extern int voiceProfFaxT38AttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t voiceProfFaxT38AttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);

/* InternetGatewayDevice.Services.VoiceService.i.voiceProfile.i.Line.i */
extern zcfgRet_t voiceLineObjGet(char * tr98FullPathName,int handler,struct json_object * * tr98Jobj,bool updateFlag);
extern zcfgRet_t voiceLineSet(char * tr98FullPathName,int handler,struct json_object * tr98Jobj,struct json_object * multiJobj);
extern zcfgRet_t voiceLineAdd(char * tr98FullPathName,int * idx);
extern zcfgRet_t voiceLineDel(char * tr98FullPathName);
extern int voiceLineAttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t voiceLineAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);

/* InternetGatewayDevice.Services.VoiceService.i.voiceProfile.i.Line.i.SIP */
extern zcfgRet_t voiceLineSipObjGet(char * tr98FullPathName,int handler,struct json_object * * tr98Jobj,bool updateFlag);
extern zcfgRet_t voiceLineSipSet(char * tr98FullPathName,int handler,struct json_object * tr98Jobj,struct json_object * multiJobj);
extern int voiceLineSipAttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t voiceLineSipAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);

/* InternetGatewayDevice.Services.VoiceService.i.voiceProfile.i.Line.i.CallingFeatures */
extern zcfgRet_t  voiceLineCallingFeatureObjGet(char * tr98FullPathName,int handler,struct json_object * * tr98Jobj,bool updateFlag);
extern zcfgRet_t voiceLineCallingFeatureObjSet(char * tr98FullPathName,int handler,struct json_object * tr98Jobj,struct json_object * multiJobj);
extern int voiceLineCallingFeatureAttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t voiceLineCallingFeatureAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);


/* InternetGatewayDevice.Services.VoiceService.i.voiceProfile.i.Line.i.Processing */
extern zcfgRet_t voiceLineProcObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t voiceLineProcSet(char * tr98FullPathName,int handler,struct json_object * tr98Jobj,struct json_object * multiJobj);
extern int voiceLineProcAttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t voiceLineProcAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);

/* InternetGatewayDevice.Services.VoiceService.i.voiceProfile.i.Line.i.Codec */
extern zcfgRet_t voiceLineCodecObjGet(char * tr98FullPathName,int handler,struct json_object ** tr98Jobj,bool updateFlag);
extern int voiceLineCodecAttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t voiceLineCodecAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);

/* InternetGatewayDevice.Services.VoiceService.i.voiceProfile.i.Line.i.Codec.List.i */
extern zcfgRet_t voiceLineCodecListObjGet(char * tr98FullPathName,int handler,struct json_object * * tr98Jobj, bool updateFlag);
extern zcfgRet_t voiceLineCodecListObjSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);
extern int voiceLineCodecListAttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t voiceLineCodecListAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);

/* InternetGatewayDevice.Services.VoiceService.i.VoiceProfile.i.Line.i.Stats */
extern zcfgRet_t voiceLineStatsObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag);
extern zcfgRet_t voiceLineStatsObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj, char *paramfault);
extern int voiceLineStatsAttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t voiceLineStatsAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);


/* InternetGatewayDevice.Services.VoiceService.i.PhyInterface.i */
extern zcfgRet_t voicePhyIntfObjGet(char * tr98FullPathName,int handler,struct json_object * * tr98Jobj,bool updateFlag);
extern zcfgRet_t voicePhyIntfSet(char * tr98FullPathName,int handler,struct json_object * tr98Jobj,struct json_object * multiJobj);
extern int voicePhyIntfAttrGet(char *tr98FullPathName, int handler, char *paramName);
extern zcfgRet_t voicePhyIntfAttrSet(char *tr98FullPathName, int handler, char *paramName, int newNotify, struct json_object *multiAttrJobj);

#endif

