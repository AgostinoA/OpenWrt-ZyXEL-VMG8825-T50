#ifndef _ZCFG_RDM_OBJ_H
#define _ZCFG_RDM_OBJ_H

typedef struct rdm_Device_s {   // RDM_OID_DEVICE 
	char RootDataModelVersion[33];
	char DeviceSummary[257];
	uint32_t InterfaceStackNumberOfEntries;
} rdm_Device_t;

typedef struct rdm_Service_s {   // RDM_OID_SERVICE 
} rdm_Service_t;

typedef struct rdm_Package_s {   // RDM_OID_PACKAGE 
	char Name[33];
	char Version[33];
	char Script[65];
	bool Enable;
	char Data[257];
	char FixCustID[257];
	char Hash[257];
	char Status[65];
} rdm_Package_t;

typedef struct rdm_PackageInstall_s {   // RDM_OID_PACKAGE_INSTALL 
	bool Install;
	bool ForceInstall;
} rdm_PackageInstall_t;

typedef struct rdm_VoiceSrv_s {   // RDM_OID_VOICE_SRV 
	uint32_t VoiceProfileNumberOfEntries;
	uint32_t X_ZYXEL_LoggingLevel;
} rdm_VoiceSrv_t;

typedef struct rdm_VoiceCapb_s {   // RDM_OID_VOICE_CAPB 
	uint32_t MaxProfileCount;
	uint32_t MaxLineCount;
	uint32_t MaxSessionsPerLine;
	uint32_t MaxSessionCount;
	char SignalingProtocols[257];
	char Regions[257];
	bool RTCP;
	bool SRTP;
	char SRTPKeyingMethods[257];
	char SRTPEncryptionKeySizes[257];
	bool RTPRedundancy;
	bool DSCPCoupled;
	bool EthernetTaggingCoupled;
	bool PSTNSoftSwitchOver;
	bool FaxT38;
	bool FaxPassThrough;
	bool ModemPassThrough;
	bool ToneGeneration;
	bool ToneDescriptionsEditable;
	bool PatternBasedToneGeneration;
	bool FileBasedToneGeneration;
	char ToneFileFormats[257];
	bool RingGeneration;
	bool RingDescriptionsEditable;
	bool PatternBasedRingGeneration;
	bool RingPatternEditable;
	bool FileBasedRingGeneration;
	char RingFileFormats[257];
	bool DigitMap;
	bool NumberingPlan;
	bool ButtonMap;
	bool VoicePortTests;
} rdm_VoiceCapb_t;

typedef struct rdm_VoiceCapbSip_s {   // RDM_OID_VOICE_CAPB_SIP 
	char Role[33];
	char Extensions[257];
	char Transports[33];
	char URISchemes[257];
	bool EventSubscription;
	bool ResponseMap;
	char TLSAuthenticationProtocols[33];
	char TLSAuthenticationKeySizes[257];
	char TLSEncryptionProtocols[33];
	char TLSEncryptionKeySizes[257];
	char TLSKeyExchangeProtocols[33];
} rdm_VoiceCapbSip_t;

typedef struct rdm_VoiceCapbMgcp_s {   // RDM_OID_VOICE_CAPB_MGCP 
	char Extensions[257];
} rdm_VoiceCapbMgcp_t;

typedef struct rdm_VoiceCapbH323_s {   // RDM_OID_VOICE_CAPB_H323 
	bool FastStart;
	char H235AuthenticationMethods[257];
} rdm_VoiceCapbH323_t;

typedef struct rdm_VoiceCapbCodec_s {   // RDM_OID_VOICE_CAPB_CODEC 
	char Alias[65];
	uint32_t EntryID;
	char Codec[65];
	uint32_t BitRate;
	char PacketizationPeriod[257];
	bool SilenceSuppression;
} rdm_VoiceCapbCodec_t;

typedef struct rdm_VoiceProf_s {   // RDM_OID_VOICE_PROF 
	uint32_t X_ZYXEL_ProfObjID;
	char Enable[17];
	bool Reset;
	uint32_t NumberOfLines;
	char Name[65];
	char SignalingProtocol[65];
	uint32_t MaxSessions;
	char DTMFMethodG711[33];
	char DTMFMethod[33];
	char X_ZYXEL_HookFlashMethod[33];
	char Region[3];
	char X_ZYXEL_Region_IntlPhoneNumCallingCode[17];
	uint32_t X_ZYXEL_Countrycode;
	char DigitMap[257];
	char X_ZYXEL_DigitMap[513];
	bool DigitMapEnable;
	bool STUNEnable;
	char STUNServer[257];
	uint32_t X_ZYXEL_STUNServerPort;
	uint32_t NonVoiceBandwidthReservedUpstream;
	uint32_t NonVoiceBandwidthReservedDownstream;
	bool PSTNFailOver;
	char FAXPassThrough[33];
	bool X_ZYXEL_FaxPassthroughPCMA;
	char ModemPassThrough[33];
	char X_ZYXEL_VBD_Originator[33];
	char X_ZYXEL_FaxMode[33];
	char X_ZYXEL_LogServer[65];
	uint32_t X_ZYXEL_LogServerPort;
	uint32_t X_ZYXEL_SPNum;
	bool X_ZYXEL_V18_Support;
	char X_ZYXEL_BoundIfName[33];
	char X_ZYXEL_BoundIfList[256];
	char X_ZYXEL_ActiveBoundIfName[33];
	char X_ZYXEL_BoundIpAddr[18];
	char X_ZYXEL_FlashUsageStyle[257];
	uint32_t X_ZYXEL_VoipIOPFlags;
	uint32_t X_ZYXEL_VoipSigIOPFlags;
	uint32_t X_ZYXEL_VoipMediaIOPFlags;
	char X_ZYXEL_P_AccessNetworkInfo[129];
	bool X_ZYXEL_IgnoreDirectIP;
	char X_ZYXEL_DNS_SRV_OperationMode[33];
	char X_ZYXEL_REGISTER_ReqLineURI[33];
} rdm_VoiceProf_t;

typedef struct rdm_VoiceProfSrvProInfo_s {   // RDM_OID_VOICE_PROF_SRV_PRO_INFO 
	char Name[257];
	char URL[257];
	char ContactPhoneNumber[33];
	char EmailAddress[257];
} rdm_VoiceProfSrvProInfo_t;

typedef struct rdm_VoiceProfSip_s {   // RDM_OID_VOICE_PROF_SIP 
	char ProxyServer[257];
	uint32_t ProxyServerPort;
	char ProxyServerTransport[33];
	char RegistrarServer[257];
	uint32_t RegistrarServerPort;
	char RegistrarServerTransport[33];
	char UserAgentDomain[257];
	uint32_t UserAgentPort;
	char UserAgentTransport[33];
	char OutboundProxy[257];
	uint32_t OutboundProxyPort;
	uint32_t X_ZYXEL_OutboundKAIntvl;
	uint32_t X_ZYXEL_KAServer;
	char X_ZYXEL_FakeSipIP[130];
	uint32_t X_ZYXEL_FakeSipPort;
	char X_ZYXEL_RegisterAndOperateBase[25];
	char Organization[257];
	uint32_t RegistrationPeriod;
	uint32_t TimerT1;
	uint32_t TimerT2;
	uint32_t TimerT4;
	uint32_t TimerA;
	uint32_t TimerB;
	uint32_t TimerC;
	uint32_t TimerD;
	uint32_t TimerE;
	uint32_t TimerF;
	uint32_t TimerG;
	uint32_t TimerH;
	uint32_t TimerI;
	uint32_t TimerJ;
	uint32_t TimerK;
	uint32_t InviteExpires;
	uint32_t ReInviteExpires;
	uint32_t X_ZYXEL_MinSE;
	bool X_ZYXEL_SessionRefreshEnable;
	char X_ZYXEL_SessionRefreshMethod[33];
	char X_ZYXEL_SessionRefresher[33];
	uint32_t X_ZYXEL_MwiExpireTime;
	uint32_t RegisterExpires;
	uint32_t RegistersMinExpires;
	uint32_t RegisterRetryInterval;
	char InboundAuth[33];
	char InboundAuthUsername[257];
	char InboundAuthPassword[257];
	bool UseCodecPriorityInSDPResponse;
	uint32_t DSCPMark;
	uint32_t X_ZYXEL_SigVLanTagTPID;
	uint32_t X_ZYXEL_SigVLanTagTCI;
	bool X_ZYXEL_Rfc3325Support;
	bool X_ZYXEL_Rfc3262Support;
	char X_ZYXEL_PRACK_for_InCall[33];
	char X_ZYXEL_PRACK_for_OutCall[33];
	int VLANIDMark;
	int EthernetPriorityMark;
	uint32_t SIPEventSubscribeNumberOfElements;
	uint32_t SIPResponseMapNumberOfElements;
	bool X_ZYXEL_HeartbeatEnable;
	uint32_t X_ZYXEL_RateOfHeartbeat;
	bool X_ZYXEL_Rfc3263Support;
	bool X_ZYXEL_Option120Use;
	char X_ZYXEL_Option120Server[257];
	char X_ZYXEL_BackupServer[257];
	char X_ZYXEL_ConferenceURI[129];
	char X_ZYXEL_ConferenceAddPartyMethod[33];
} rdm_VoiceProfSip_t;

typedef struct rdm_VoiceProfSipSubscribeObj_s {   // RDM_OID_VOICE_PROF_SIP_SUBSCRIBE_OBJ 
	char Event[33];
	char Notifier[257];
	uint32_t NotifierPort;
	char NotifierTransport[33];
	uint32_t ExpireTime;
} rdm_VoiceProfSipSubscribeObj_t;

typedef struct rdm_VoiceProfSipRespMapObj_s {   // RDM_OID_VOICE_PROF_SIP_RESP_MAP_OBJ 
	uint32_t SIPResponseNumber;
	char TextMessage[65];
	uint32_t Tone;
} rdm_VoiceProfSipRespMapObj_t;

typedef struct rdm_VoiceProfRtp_s {   // RDM_OID_VOICE_PROF_RTP 
	uint32_t LocalPortMin;
	uint32_t LocalPortMax;
	uint32_t DSCPMark;
	int VLANIDMark;
	int EthernetPriorityMark;
	uint32_t TelephoneEventPayloadType;
} rdm_VoiceProfRtp_t;

typedef struct rdm_VoiceProfRtpRtcp_s {   // RDM_OID_VOICE_PROF_RTP_RTCP 
	bool Enable;
	uint32_t TxRepeatInterval;
	char LocalCName[65];
} rdm_VoiceProfRtpRtcp_t;

typedef struct rdm_VoiceProfRtpSrtp_s {   // RDM_OID_VOICE_PROF_RTP_SRTP 
	bool Enable;
	char KeyingMethods[257];
	char EncryptionKeySizes[257];
	char X_ZYXEL_Crypto_Suite_Name[65];
} rdm_VoiceProfRtpSrtp_t;

typedef struct rdm_VoiceProfRtpRedundancy_s {   // RDM_OID_VOICE_PROF_RTP_REDUNDANCY 
	bool Enable;
	uint32_t PayloadType;
	uint32_t BlockPayloadType;
	int FaxAndModemRedundancy;
	int ModemRedundancy;
	int DTMFRedundancy;
	int VoiceRedundancy;
	uint32_t MaxSessionsUsingRedundancy;
} rdm_VoiceProfRtpRedundancy_t;

typedef struct rdm_VoiceProfNumPlan_s {   // RDM_OID_VOICE_PROF_NUM_PLAN 
	uint32_t MinimumNumberOfDigits;
	uint32_t MaximumNumberOfDigits;
	uint32_t InterDigitTimerStd;
	uint32_t InterDigitTimerOpen;
	uint32_t X_ZYXEL_DialingLongInterval;
	uint32_t X_ZYXEL_TimerFirstDigitWarmLine;
	uint32_t InvalidNumberTone;
	uint32_t PrefixInfoMaxEntries;
	uint32_t PrefixInfoNumberOfEntries;
} rdm_VoiceProfNumPlan_t;

typedef struct rdm_VoiceProfNumPlanPrefixInfo_s {   // RDM_OID_VOICE_PROF_NUM_PLAN_PREFIX_INFO 
	char PrefixRange[43];
	uint32_t PrefixMinNumberOfDigits;
	uint32_t PrefixMaxNumberOfDigits;
	uint32_t NumberOfDigitsToRemove;
	uint32_t PosOfDigitsToRemove;
	uint32_t DialTone;
	char FacilityAction[65];
	char FacilityActionArgument[257];
} rdm_VoiceProfNumPlanPrefixInfo_t;

typedef struct rdm_VoiceProfTone_s {   // RDM_OID_VOICE_PROF_TONE 
	uint32_t EventNumberOfEntries;
	uint32_t DescriptionNumberOfEntries;
	uint32_t PatternNumberOfEntries;
} rdm_VoiceProfTone_t;

typedef struct rdm_VoiceProfToneEvent_s {   // RDM_OID_VOICE_PROF_TONE_EVENT 
	char Function[33];
	uint32_t ToneID;
} rdm_VoiceProfToneEvent_t;

typedef struct rdm_VoiceProfToneDescription_s {   // RDM_OID_VOICE_PROF_TONE_DESCRIPTION 
	uint32_t EntryID;
	bool ToneEnable;
	char ToneName[65];
	uint32_t TonePattern;
	char ToneFile[257];
	uint32_t ToneRepetitions;
	char ToneText[65];
} rdm_VoiceProfToneDescription_t;

typedef struct rdm_VoiceProfTonePattern_s {   // RDM_OID_VOICE_PROF_TONE_PATTERN 
	uint32_t EntryID;
	bool ToneOn;
	uint32_t Frequency1;
	int Power1;
	uint32_t Frequency2;
	int Power2;
	uint32_t Frequency3;
	int Power3;
	uint32_t Frequency4;
	int Power4;
	uint32_t ModulationFrequency;
	int ModulationPower;
	uint32_t Duration;
	uint32_t NextEntryID;
} rdm_VoiceProfTonePattern_t;

typedef struct rdm_VoiceProfFaxT38_s {   // RDM_OID_VOICE_PROF_FAX_T38 
	bool Enable;
	uint32_t BitRate;
	uint32_t HighSpeedPacketRate;
	uint32_t HighSpeedRedundancy;
	uint32_t LowSpeedRedundancy;
	char TCFMethod[33];
} rdm_VoiceProfFaxT38_t;

typedef struct rdm_VoiceLine_s {   // RDM_OID_VOICE_LINE 
	uint32_t X_ZYXEL_LineID;
	char Enable[17];
	char DirectoryNumber[33];
	char Status[33];
	char CallState[129];
	char PhyReferenceList[33];
	uint32_t X_ZYXEL_PhyReferenceFXSList;
	bool X_ZYXEL_AutoDialEnable;
	char X_ZYXEL_AutoDialNumber[38];
	char X_ZYXEL_P_AccessNetworkInfo[129];
	bool RingMuteStatus;
	uint32_t RingVolumeStatus;
	uint32_t X_ZYXEL_CMAcntNum;
	uint32_t X_ZYXEL_DoRegister;
} rdm_VoiceLine_t;

typedef struct rdm_VoiceLineSip_s {   // RDM_OID_VOICE_LINE_SIP 
	char AuthUserName[129];
	char AuthPassword[129];
	char URI[390];
	char X_ZYXEL_RegistrarType[33];
	char X_ZYXEL_Url_Type[33];
	uint32_t X_ZYXEL_CallFwdTableIndex;
	uint32_t SIPEventSubscribeNumberOfElements;
	char X_ZYXEL_MixerMode[33];
	char X_ZYXEL_RemoteRingbackTone[33];
	char X_ZYXEL_P_AccessNetworkInfo[129];
} rdm_VoiceLineSip_t;

typedef struct rdm_VoiceLineSipEventSubs_s {   // RDM_OID_VOICE_LINE_SIP_EVENT_SUBS 
	char Event[33];
	char AuthUserName[129];
	char AuthPassword[129];
} rdm_VoiceLineSipEventSubs_t;

typedef struct rdm_VoiceLineRinger_s {   // RDM_OID_VOICE_LINE_RINGER 
	uint32_t EventNumberOfEntries;
	uint32_t DescriptionNumberOfEntries;
	uint32_t PatternNumberOfEntries;
} rdm_VoiceLineRinger_t;

typedef struct rdm_VoiceLineRingerEvent_s {   // RDM_OID_VOICE_LINE_RINGER_EVENT 
	char Function[33];
	uint32_t RingID;
} rdm_VoiceLineRingerEvent_t;

typedef struct rdm_VoiceLineRingerDescription_s {   // RDM_OID_VOICE_LINE_RINGER_DESCRIPTION 
	uint32_t EntryID;
	bool RingEnable;
	char RingName[65];
	uint32_t RingPattern;
	char RingFile[257];
} rdm_VoiceLineRingerDescription_t;

typedef struct rdm_VoiceLineRingerPattern_s {   // RDM_OID_VOICE_LINE_RINGER_PATTERN 
	uint32_t EntryID;
	bool RingerOn;
	uint32_t Duration;
	uint32_t NextEntryID;
} rdm_VoiceLineRingerPattern_t;

typedef struct rdm_VoiceLineCallingFeature_s {   // RDM_OID_VOICE_LINE_CALLING_FEATURE 
	bool CallerIDEnable;
	bool CallerIDNameEnable;
	char CallerIDName[257];
	bool CallWaitingEnable;
	bool X_ZYXEL_CallWaitingStart;
	char CallWaitingStatus[33];
	uint32_t X_ZYXEL_CallWaitingRejectTime;
	uint32_t MaxSessions;
	uint32_t ConferenceCallingStatus;
	char X_ZYXEL_ConferenceURI[50];
	uint32_t ConferenceCallingSessionCount;
	bool CallForwardUnconditionalEnable;
	bool X_ZYXEL_CallForwardUnconditionalStart;
	char CallForwardUnconditionalNumber[33];
	bool CallForwardOnBusyEnable;
	bool X_ZYXEL_CallForwardOnBusyStart;
	char CallForwardOnBusyNumber[33];
	bool CallForwardOnNoAnswerEnable;
	bool X_ZYXEL_CallForwardOnNoAnswerStart;
	char CallForwardOnNoAnswerNumber[33];
	uint32_t CallForwardOnNoAnswerRingCount;
	bool CallTransferEnable;
	bool MWIEnable;
	uint32_t X_ZYXEL_MwiExpireTime;
	bool MessageWaiting;
	bool AnonymousCallBlockEnable;
	bool X_ZYXEL_AnonymousCallBlockStart;
	bool AnonymousCallEnable;
	bool X_ZYXEL_AnonymousCallStart;
	bool DoNotDisturbEnable;
	bool X_ZYXEL_DoNotDisturbStart;
	bool CallReturnEnable;
	bool RepeatDialEnable;
	bool X_ZYXEL_CallTransferAfterConference;
	uint32_t X_ZYXEL_TimerFirstDigitWarmLine;
	bool X_ZYXEL_HotLineEnable;
	char X_ZYXEL_HotLineNum[33];
	bool X_ZYXEL_RemoteRingbackTone;
	uint32_t X_ZYXEL_RemoteRingbackToneIndex;
	bool X_ZYXEL_MusicOnHoldTone;
	uint32_t X_ZYXEL_MusicOnHoldToneIndex;
	bool X_ZYXEL_MissedCallEmailEnable;
	char X_ZYXEL_MissedCallEmailEvent[65];
	char X_ZYXEL_MissedCallEmailServerAddr[65];
	char X_ZYXEL_MissedCallEmailToAddr[65];
	char X_ZYXEL_MissedCallEmailTitle[65];
	bool X_ZYXEL_CCBSEnable;
	bool X_ZYXEL_CAllCompletionOnBusyEnable;
	bool X_ZYXEL_SpeedDialEnable;
	bool X_ZYXEL_WarmLineEnable;
	bool X_ZYXEL_WarmLineStart;
	char X_ZYXEL_WarmLineNumber[33];
	bool X_ZYXEL_CallBarringEnable;
	char X_ZYXEL_CallBarringMode[33];
	char X_ZYXEL_CallBarringUserPin[11];
	char X_ZYXEL_CallBarringDigitMap[257];
	bool X_ZYXEL_NetworkPrivacyEnable;
	bool X_ZYXEL_NetworkPrivacyStart;
	bool X_ZYXEL_VMWIEnable;
	bool X_ZYXEL_EnumEnablee;
	bool X_ZYXEL_EnumStart;
} rdm_VoiceLineCallingFeature_t;

typedef struct rdm_VoiceLineProcessing_s {   // RDM_OID_VOICE_LINE_PROCESSING 
	int TransmitGain;
	int ReceiveGain;
	bool EchoCancellationEnable;
	bool EchoCancellationInUse;
	uint32_t EchoCancellationTail;
} rdm_VoiceLineProcessing_t;

typedef struct rdm_VoiceLineCodec_s {   // RDM_OID_VOICE_LINE_CODEC 
	char TransmitCodec[65];
	char ReceiveCodec[65];
	uint32_t TransmitBitRate;
	uint32_t ReceiveBitRate;
	bool TransmitSilenceSuppression;
	bool ReceiveSilenceSuppression;
	uint32_t TransmitPacketizationPeriod;
} rdm_VoiceLineCodec_t;

typedef struct rdm_VoiceLineCodecList_s {   // RDM_OID_VOICE_LINE_CODEC_LIST 
	uint32_t EntryID;
	char Codec[65];
	uint32_t BitRate;
	char X_ZYXEL_PayloadTypeNum[65];
	char PacketizationPeriod[65];
	bool SilenceSuppression;
	bool Enable;
	uint32_t Priority;
	bool X_ZYXEL_ComfortNoise;
	char X_ZYXEL_Codec[65];
} rdm_VoiceLineCodecList_t;

typedef struct rdm_VoiceLineSession_s {   // RDM_OID_VOICE_LINE_SESSION 
	char SessionStartTime[32];
	uint32_t SessionDuration;
	char FarEndIPAddress[65];
	uint32_t FarEndUDPPort;
	uint32_t LocalUDPPort;
} rdm_VoiceLineSession_t;

typedef struct rdm_VoiceLineStats_s {   // RDM_OID_VOICE_LINE_STATS 
	bool ResetStatistics;
	uint32_t PacketsSent;
	uint32_t PacketsReceived;
	uint32_t BytesSent;
	uint32_t BytesReceived;
	uint32_t PacketsLost;
	uint32_t Overruns;
	uint32_t Underruns;
	uint32_t IncomingCallsReceived;
	uint32_t IncomingCallsAnswered;
	uint32_t IncomingCallsConnected;
	uint32_t IncomingCallsFailed;
	uint32_t OutgoingCallsAttempted;
	uint32_t OutgoingCallsAnswered;
	uint32_t OutgoingCallsConnected;
	uint32_t OutgoingCallsFailed;
	uint32_t CallsDropped;
	uint32_t TotalCallTime;
	uint32_t ServerDownTime;
	uint32_t ReceivePacketLossRate;
	uint32_t FarEndPacketLossRate;
	uint32_t ReceiveInterarrivalJitter;
	uint32_t FarEndInterarrivalJitter;
	uint32_t RoundTripDelay;
	uint32_t AverageReceiveInterarrivalJitter;
	uint32_t AverageFarEndInterarrivalJitter;
	uint32_t AverageRoundTripDelay;
	char X_ZYXEL_LastRegistration[65];
	char X_ZYXEL_LastIncommingNumber[65];
	char X_ZYXEL_LastOutgoingNumber[65];
	bool X_ZYXEL_MWIStatus;
} rdm_VoiceLineStats_t;

typedef struct rdm_VoicePhyIntf_s {   // RDM_OID_VOICE_PHY_INTF 
	char PhyPort[3];
	uint32_t InterfaceID;
	char Description[33];
	char X_ZYXEL_PotsType[33];
	char X_ZYXEL_DialingType[33];
	char X_ZYXEL_DialToneType[33];
	char X_ZYXEL_ReceiveToneType[33];
	uint32_t X_ZYXEL_FlashMaxInterval;
	uint32_t X_ZYXEL_FlashMinInterval;
	uint32_t X_ZYXEL_JitterBufSize;
	char X_ZYXEL_CallerIDType[33];
	char X_ZYXEL_CallerIDPayload[33];
	uint32_t X_ZYXEL_TasTimeoutInterval;
	uint32_t X_ZYXEL_TasTimeoutInterval_2;
	uint32_t X_ZYXEL_CallerIDRingTimeout;
	uint32_t X_ZYXEL_FirstRingTimoutInterval;
	char X_ZYXEL_FirstTASType[33];
	char X_ZYXEL_SecondTASType[33];
	uint32_t X_ZYXEL_CallerID_DTAS_ACK_Timeout;
	char X_ZYXEL_LineSelect[256];
	uint32_t X_ZYXEL_MsnIncomingSelect;
	uint32_t X_ZYXEL_MsnOutgoingSelect;
	uint32_t X_ZYXEL_HowlerToneTimeout;
	bool X_ZYXEL_Pound;
	bool X_ZYXEL_HookFlashIgnore;
	char X_ZYXEL_HookState[33];
} rdm_VoicePhyIntf_t;

typedef struct rdm_VoicePstn_s {   // RDM_OID_VOICE_PSTN 
	char OutgoingCallDialPlan[129];
	char IncomingCallRoutingMode[33];
	char IncomingCallRoutingDest[257];
	char ForcePSTNTab[37];
	uint32_t Flags;
	char Reversed[3];
} rdm_VoicePstn_t;

typedef struct rdm_VoiceCommon_s {   // RDM_OID_VOICE_COMMON 
	char IfName[33];
	uint32_t VoipPort;
	bool Ivrsyspermit;
	uint32_t IvrLanguage;
	uint32_t Ivrcodec;
	uint32_t SpecialFlag;
	bool CallFallBack;
	bool Activedialplan;
	char DialPlan[257];
	char DialMethod[257];
	uint32_t VoipIOPFlags;
	bool CustomUserAgentNameEnable;
	char CustomUserAgentName[129];
	char P_AccessNetworkInfo[129];
	char UserAgent_strReplaceRule[257];
	char FxsCIDMode[17];
	char FxsCIDSigProtocol[9];
	uint32_t TLS_Port;
	char TLS_Certificate[257];
	char TLS_CipherSuite[51];
	uint8_t TLS_CertVerifyMode;
} rdm_VoiceCommon_t;

typedef struct rdm_VoicePhoneBook_s {   // RDM_OID_VOICE_PHONE_BOOK 
} rdm_VoicePhoneBook_t;

typedef struct rdm_SpeedDialBook_s {   // RDM_OID_SPEED_DIAL_BOOK 
	uint32_t SpeedDialBookNumberOfEntries;
} rdm_SpeedDialBook_t;

typedef struct rdm_SpeedDialBookList_s {   // RDM_OID_SPEED_DIAL_BOOK_LIST 
	char OrigNumber[129];
	char ForceSipURI[257];
	char SpeedNumber[129];
	char Name[129];
	char Flags[33];
	char Type[33];
} rdm_SpeedDialBookList_t;

typedef struct rdm_CallPolicyBook_s {   // RDM_OID_CALL_POLICY_BOOK 
	uint32_t CallPolicyBookNumberOfEntries;
	char Type[13];
} rdm_CallPolicyBook_t;

typedef struct rdm_CallPolicyBookList_s {   // RDM_OID_CALL_POLICY_BOOK_LIST 
	bool Enable;
	char PhoneNumber[129];
	char Direction[13];
	char Method[16];
	char ForwardToNumber[129];
	char Description[129];
} rdm_CallPolicyBookList_t;

typedef struct rdm_VoiceInternalPhoneNumberBook_s {   // RDM_OID_VOICE_INTERNAL_PHONE_NUMBER_BOOK 
	uint32_t NumberOfInterface;
} rdm_VoiceInternalPhoneNumberBook_t;

typedef struct rdm_VoiceInternalPhoneNumberBookIfList_s {   // RDM_OID_VOICE_INTERNAL_PHONE_NUMBER_BOOK_IF_LIST 
	char NameOfPhonePortType[65];
	uint32_t NumberOfPhonePortType;
} rdm_VoiceInternalPhoneNumberBookIfList_t;

typedef struct rdm_VoiceInternalPhoneNumberBookPortList_s {   // RDM_OID_VOICE_INTERNAL_PHONE_NUMBER_BOOK_PORT_LIST 
	char PhoneNumber[65];
} rdm_VoiceInternalPhoneNumberBookPortList_t;

typedef struct rdm_VoiceFxo_s {   // RDM_OID_VOICE_FXO 
	uint32_t NumberOfPort;
} rdm_VoiceFxo_t;

typedef struct rdm_VoiceFxoPort_s {   // RDM_OID_VOICE_FXO_PORT 
	uint32_t FxoDialLongInterval;
	uint32_t FxoPhoneSelect;
	uint32_t FxoDTMFPauseDuration;
	uint32_t FxoFlashMinInterval;
	uint32_t FxoFlashMaxInterval;
	uint32_t FxoLifeLineStableTime;
	uint32_t FxoDTMFDigitDuration;
	uint32_t Reversed2;
	uint32_t PollingPollarityTime;
	uint32_t DetectCIDInterval;
} rdm_VoiceFxoPort_t;

typedef struct rdm_VoiceDect_s {   // RDM_OID_VOICE_DECT 
	uint32_t NumberOfHandset;
} rdm_VoiceDect_t;

typedef struct rdm_VoiceDectBS_s {   // RDM_OID_VOICE_DECT_B_S 
	bool FunctionEnable;
	char Name[14];
	char PINcode[5];
	bool EncryptionEnable;
	bool NEMoEnable;
	bool ECOModeEnable;
	uint32_t RFStrength;
	char FirmwareVersion[33];
	char EEPROMVersion[33];
	char HardwareVersion[33];
	uint32_t BaseStatus;
	bool DoReset;
	uint32_t DoRegistrationModeOnOff;
	uint32_t RegistrationModeOnDuration;
	uint32_t DoDeregisterHS;
	uint32_t DoPagingHSOnOff;
	uint32_t PagingHSOnDuration;
	bool DoFirmwareUpgrade;
	char FirmwareURL[257];
} rdm_VoiceDectBS_t;

typedef struct rdm_VoiceDectHS_s {   // RDM_OID_VOICE_DECT_H_S 
	bool RegisterStatus;
	char Name[33];
	uint32_t Index;
	uint32_t Type;
	uint32_t ModelId;
	char IPEI[17];
	char IPUI[27];
	char TPUI[7];
	char EMC[5];
	char InternalPhoneNumber[65];
	uint32_t State;
	char LineSelect[257];
} rdm_VoiceDectHS_t;

typedef struct rdm_VoiceCallStatus_s {   // RDM_OID_VOICE_CALL_STATUS 
	char Status[129];
	char CallStartTime[129];
	char SelfNumber[513];
	char PeerNumber[513];
	char Codec[65];
	char FromPhonePortType[65];
	char ToPhonePortType[65];
	char CallType[129];
} rdm_VoiceCallStatus_t;

typedef struct rdm_DevInfo_s {   // RDM_OID_DEV_INFO 
	char Manufacturer[65];
	char ManufacturerOUI[7];
	char FixManufacturerOUI[7];
	char ModelName[65];
	char Description[257];
	char ProductClass[65];
	char SerialNumber[65];
	char HardwareVersion[65];
	char SoftwareVersion[65];
	char AdditionalHardwareVersion[65];
	char AdditionalSoftwareVersion[65];
	char ProvisioningCode[65];
	char X_ZYXEL_ProvisioningCodeIntf[17];
	char X_ZYXEL_ProvisioningKey[65];
	char X_ZYXEL_GponSerialNumber[13];
	char X_ZYXEL_Ploam_Password[76];
	uint32_t UpTime;
	char FirstUseDate[32];
	uint32_t VendorConfigFileNumberOfEntries;
	uint32_t SupportedDataModelNumberOfEntries;
	uint32_t ProcessorNumberOfEntries;
	uint32_t VendorLogFileNumberOfEntries;
	uint32_t LocationNumberOfEntries;
} rdm_DevInfo_t;

typedef struct rdm_DevInfoVendConfFile_s {   // RDM_OID_DEV_INFO_VEND_CONF_FILE 
	char Alias[65];
	char Name[65];
	char Version[17];
	char Date[32];
	char Description[257];
} rdm_DevInfoVendConfFile_t;

typedef struct rdm_DevInfoSupDataModel_s {   // RDM_OID_DEV_INFO_SUP_DATA_MODEL 
	char Alias[65];
	char URL[257];
	char URN[257];
	char Features[257];
} rdm_DevInfoSupDataModel_t;

typedef struct rdm_DevInfoMemStat_s {   // RDM_OID_DEV_INFO_MEM_STAT 
	uint32_t Total;
	uint32_t Free;
} rdm_DevInfoMemStat_t;

typedef struct rdm_DevInfoPsStat_s {   // RDM_OID_DEV_INFO_PS_STAT 
	uint32_t CPUUsage;
	uint32_t ProcessNumberOfEntries;
} rdm_DevInfoPsStat_t;

typedef struct rdm_DevInfoPsStatPs_s {   // RDM_OID_DEV_INFO_PS_STAT_PS 
	uint32_t PID;
	char Command[257];
	uint32_t Size;
	uint32_t Priority;
	uint32_t CPUTime;
	char State[27];
} rdm_DevInfoPsStatPs_t;

typedef struct rdm_TempStat_s {   // RDM_OID_TEMP_STAT 
	uint32_t TemperatureSensorNumberOfEntries;
} rdm_TempStat_t;

typedef struct rdm_TempStatTempSensor_s {   // RDM_OID_TEMP_STAT_TEMP_SENSOR 
	char Alias[65];
	bool Enable;
	char Status[9];
	bool Reset;
	char ResetTime[32];
	char Name[257];
	int Value;
	char LastUpdate[32];
	int MinValue;
	char MinTime[32];
	int MaxValue;
	char MaxTime[32];
	int LowAlarmValue;
	char LowAlarmTime[32];
	int HighAlarmValue;
	uint32_t PollingInterval;
	char HighAlarmTime[32];
} rdm_TempStatTempSensor_t;

typedef struct rdm_NetworkProp_s {   // RDM_OID_NETWORK_PROP 
	uint32_t MaxTCPWindowSize;
	char TCPImplementation[266];
} rdm_NetworkProp_t;

typedef struct rdm_DevInfoProcessor_s {   // RDM_OID_DEV_INFO_PROCESSOR 
	char Alias[65];
	char Architecture[8];
} rdm_DevInfoProcessor_t;

typedef struct rdm_DevInfoVendorLogFile_s {   // RDM_OID_DEV_INFO_VENDOR_LOG_FILE 
	char Alias[65];
	char Name[65];
	uint32_t MaximumSize;
	bool Persistent;
} rdm_DevInfoVendorLogFile_t;

typedef struct rdm_DevInfoProxierInfo_s {   // RDM_OID_DEV_INFO_PROXIER_INFO 
	char ManufacturerOUI[7];
	char ProductClass[65];
	char SerialNumber[65];
	char ProxyProtocol[65];
} rdm_DevInfoProxierInfo_t;

typedef struct rdm_DevInfoLoc_s {   // RDM_OID_DEV_INFO_LOC 
	char Source[9];
	char AcquiredTime[32];
	char ExternalSource[257];
	char ExternalProtocol[26];
	char DataObject[1201];
} rdm_DevInfoLoc_t;

typedef struct rdm_DevInfoPowerStat_s {   // RDM_OID_DEV_INFO_POWER_STAT 
	uint32_t Max;
	uint32_t Current;
} rdm_DevInfoPowerStat_t;

typedef struct rdm_MgmtSrv_s {   // RDM_OID_MGMT_SRV 
	bool EnableCWMP;
	char URL[257];
	char X_ZYXEL_FallbackURL[257];
	char X_ZYXEL_FallbackURL_op43[257];
	bool X_ZYXEL_URLChangedViaOption43;
	char Username[257];
	char Password[257];
	char authType[33];
	char realm[33];
	bool PeriodicInformEnable;
	uint32_t PeriodicInformInterval;
	char PeriodicInformTime[32];
	char ParameterKey[33];
	char ConnectionRequestURL[257];
	char ConnectionRequestUsername[257];
	char ConnectionRequestPassword[257];
	bool UpgradesManaged;
	char KickURL[257];
	char DownloadProgressURL[257];
	uint32_t DefaultActiveNotificationThrottle;
	uint32_t CWMPRetryMinimumWaitInterval;
	uint32_t CWMPRetryIntervalMultiplier;
	char UDPConnectionRequestAddress[257];
	bool STUNEnable;
	char STUNServerAddress[257];
	uint32_t STUNServerPort;
	char STUNUsername[257];
	char STUNPassword[257];
	int STUNMaximumKeepAlivePeriod;
	uint32_t STUNMinimumKeepAlivePeriod;
	bool NATDetected;
	bool AliasBasedAddressing;
	char InstanceMode[15];
	bool AutoCreateInstances;
	uint32_t ManageableDeviceNumberOfEntries;
	uint32_t EmbeddedDeviceNumberOfEntries;
	uint32_t VirtualDeviceNumberOfEntries;
	char X_ZYXEL_BoundInterface[33];
	char X_ZYXEL_BoundInterfaceList[129];
	char X_ZYXEL_ActiveBoundInterface[33];
	bool X_ZYXEL_DisplaySOAP;
	uint32_t X_ZYXEL_ConnectionRequestUDPPort;
	uint32_t X_ZYXEL_ConnectionRequestPort;
	uint32_t X_ZYXEL_ActiveNotifyUpdateInterval;
	char X_ZYXEL_DataModelSpec[17];
	char X_ZYXEL_Certificate[257];
	uint32_t X_ZYXEL_DebugLevel;
	uint32_t X_ZYXEL_Feature;
	char X_ZYXEL_V4TrustDomain[65];
	char X_ZYXEL_V6TrustDomain[257];
	char X_ZYXEL_ROMD_Action[9];
	bool X_ZYXEL_IPv6_Protocol;
	uint32_t X_ZYXEL_SerialNumber_Type;
	bool X_ZYXEL_IPv4_Protocol;
	char X_ZYXEL_CurrentMode[33];
	char X_ZYXEL_AvailableMode[33];
	char X_ZYXEL_v4ConnectionRequestURL[257];
	char X_ZYXEL_v6ConnectionRequestURL[257];
	char X_ZYXEL_SetConnReqURLMode[33];
	bool X_ZYXEL_UtilizeDelayApply;
	bool X_ZYXEL_SpvOnSessionComplete;
	bool X_ZYXEL_AcsSpvNotifyRequired;
	bool X_ZYXEL_AcsUrlModifyAndClearTransData;
	bool X_ZYXEL_CheckCertificate;
	bool X_ZYXEL_CheckCertificateCN;
	bool X_ZYXEL_TR181SpvPartialSet;
	uint32_t X_ZYXEL_MaxIndexObjectQueryNum;
	bool X_ZYXEL_PreSharedKeyOperation;
	bool X_ZYXEL_Supplemental_EnableCWMP;
	char X_ZYXEL_Supplemental_URL[257];
	char X_ZYXEL_Supplemental_Username[257];
	char X_ZYXEL_Supplemental_Password[257];
	char X_ZYXEL_Supplemental_ConnReqURL[257];
	char X_ZYXEL_Supplemental_ConnReqUsername[257];
	char X_ZYXEL_Supplemental_ConnReqPassword[257];
	uint32_t X_ZYXEL_Supplemental_ConnReqPort;
	char X_ZYXEL_Supplemental_v4ConnReqURL[257];
	char X_ZYXEL_Supplemental_v6ConnReqURL[257];
	bool X_ZYXEL_ReplyAllObjectsWhileRootQuery;
	char X_ZYXEL_QueryRootButNotRepliedObjects[513];
	char X_ZYXEL_QueryButNotRepliedObjects[513];
} rdm_MgmtSrv_t;

typedef struct rdm_MgmtSrvMgabDev_s {   // RDM_OID_MGMT_SRV_MGAB_DEV 
	char Alias[65];
	char ManufacturerOUI[7];
	char SerialNumber[65];
	char ProductClass[65];
	char Host[1025];
	char X_ZYXEL_MacAddress[18];
} rdm_MgmtSrvMgabDev_t;

typedef struct rdm_MgmtSrvAutoTransCompletePol_s {   // RDM_OID_MGMT_SRV_AUTO_TRANS_COMPLETE_POL 
	bool Enable;
	char TransferTypeFilter[9];
	char ResultTypeFilter[8];
	char FileTypeFilter[1025];
} rdm_MgmtSrvAutoTransCompletePol_t;

typedef struct rdm_MgmtSrvDlAvail_s {   // RDM_OID_MGMT_SRV_DL_AVAIL 
} rdm_MgmtSrvDlAvail_t;

typedef struct rdm_MgmtSrvDlAvailAnncmnt_s {   // RDM_OID_MGMT_SRV_DL_AVAIL_ANNCMNT 
	bool Enable;
	char Status[9];
	uint32_t GroupNumberOfEntries;
} rdm_MgmtSrvDlAvailAnncmnt_t;

typedef struct rdm_MgmtSrvDlAvailAnncmntGroup_s {   // RDM_OID_MGMT_SRV_DL_AVAIL_ANNCMNT_GROUP 
	char Alias[65];
	bool Enable;
	char Status[9];
	char URL[257];
} rdm_MgmtSrvDlAvailAnncmntGroup_t;

typedef struct rdm_MgmtSrvDlAvailQuery_s {   // RDM_OID_MGMT_SRV_DL_AVAIL_QUERY 
	bool Enable;
	char Status[9];
	char URL[257];
} rdm_MgmtSrvDlAvailQuery_t;

typedef struct rdm_MgmtSrvDuStateChangeComplPol_s {   // RDM_OID_MGMT_SRV_DU_STATE_CHANGE_COMPL_POL 
	bool Enable;
	char OperationTypeFilter[10];
	char ResultTypeFilter[9];
	char FaultCodeFilter[6];
} rdm_MgmtSrvDuStateChangeComplPol_t;

typedef struct rdm_MgmtSrvEmbededDev_s {   // RDM_OID_MGMT_SRV_EMBEDED_DEV 
	char ControllerID[257];
	char ProxiedDeviceID[257];
	char Reference[257];
	char SupportedDataModel[257];
	char Host[257];
	char ProxyProtocol[65];
	char CommandProcessed[10];
	char CommandProcessingErrMsg[1025];
	char LastSyncTime[32];
} rdm_MgmtSrvEmbededDev_t;

typedef struct rdm_MgmtSrvVirtualDev_s {   // RDM_OID_MGMT_SRV_VIRTUAL_DEV 
	char ManufacturerOUI[7];
	char ProductClass[65];
	char SerialNumber[65];
	char Host[65];
	char ProxyProtocol[65];
} rdm_MgmtSrvVirtualDev_t;

typedef struct rdm_GatewayInfo_s {   // RDM_OID_GATEWAY_INFO 
	char ManufacturerOUI[7];
	char ProductClass[65];
	char SerialNumber[65];
} rdm_GatewayInfo_t;

typedef struct rdm_Time_s {   // RDM_OID_TIME 
	bool Enable;
	char Status[27];
	char NTPServer1[65];
	char NTPServer2[65];
	char NTPServer3[65];
	char NTPServer4[65];
	char NTPServer5[65];
	char CurrentLocalTime[32];
	char LocalTimeZone[257];
	char X_ZYXEL_TimeZone[257];
	char X_ZYXEL_Location[257];
	char X_ZYXEL_DaylightSavingString[33];
	bool X_ZYXEL_DaylightSavings;
	uint32_t X_ZYXEL_StartMonth;
	uint32_t X_ZYXEL_StartWeek;
	uint32_t X_ZYXEL_StartDayOfWeek;
	uint32_t X_ZYXEL_StartDay;
	uint32_t X_ZYXEL_StartHour;
	uint32_t X_ZYXEL_StartMin;
	uint32_t X_ZYXEL_EndMonth;
	uint32_t X_ZYXEL_EndWeek;
	uint32_t X_ZYXEL_EndDayOfWeek;
	uint32_t X_ZYXEL_EndDay;
	uint32_t X_ZYXEL_EndHour;
	uint32_t X_ZYXEL_EndMin;
	uint32_t X_ZYXEL_Sync_Interval;
} rdm_Time_t;

typedef struct rdm_UsrIntf_s {   // RDM_OID_USR_INTF 
	bool PasswordRequired;
	bool PasswordUserSelectable;
	bool PasswordReset;
	bool UpgradeAvailable;
	char WarrantyDate[32];
	char ISPName[65];
	char ISPHelpDesk[33];
	char ISPHomePage[257];
	char ISPHelpPage[257];
	char ISPLogo[4096];
	uint32_t ISPLogoSize;
	char ISPMailServer[257];
	char ISPNewsServer[257];
	char TextColor[7];
	char BackgroundColor[7];
	char ButtonColor[7];
	char ButtonTextColor[7];
	char AutoUpdateServer[257];
	char UserUpdateServer[257];
	char AvailableLanguages[257];
	char CurrentLanguage[17];
	int RememberPassword;
	bool CurrentGUIView;
	int X_ZYXEL_Timeout;
} rdm_UsrIntf_t;

typedef struct rdm_UsrIntfRemoAcess_s {   // RDM_OID_USR_INTF_REMO_ACESS 
	bool Enable;
	uint32_t Port;
	char SupportedProtocols[7];
	char Protocol[257];
} rdm_UsrIntfRemoAcess_t;

typedef struct rdm_UsrIntfLocalDisp_s {   // RDM_OID_USR_INTF_LOCAL_DISP 
	bool Movable;
	bool Resizable;
	int PosX;
	int PosY;
	uint32_t Width;
	uint32_t Height;
	uint32_t DisplayWidth;
	uint32_t DisplayHeight;
} rdm_UsrIntfLocalDisp_t;

typedef struct rdm_IfaceStack_s {   // RDM_OID_IFACE_STACK 
	char Alias[65];
	char HigherLayer[257];
	char LowerLayer[257];
	char HigherAlias[65];
	char LowerAlias[65];
} rdm_IfaceStack_t;

typedef struct rdm_Dsl_s {   // RDM_OID_DSL 
	uint32_t LineNumberOfEntries;
	uint32_t ChannelNumberOfEntries;
	uint32_t BondingGroupNumberOfEntries;
} rdm_Dsl_t;

typedef struct rdm_DslLine_s {   // RDM_OID_DSL_LINE 
	bool Enable;
	char Status[17];
	char Alias[65];
	char Name[65];
	uint32_t LastChange;
	char LowerLayers[1025];
	bool Upstream;
	char FirmwareVersion[65];
	char LinkStatus[25];
	char StandardsSupported[1025];
	char StandardUsed[25];
	char LineEncoding[7];
	char AllowedProfiles[49];
	char CurrentProfile[5];
	char PowerManagementState[4];
	uint32_t SuccessFailureCause;
	uint32_t LastStateTransmittedDownstream;
	uint32_t LastStateTransmittedUpstream;
	uint32_t UPBOKLE;
	char MREFPSDds[146];
	char MREFPSDus[146];
	uint32_t LIMITMASK;
	uint32_t US0MASK;
	int TRELLISds;
	int TRELLISus;
	uint32_t ACTSNRMODEds;
	uint32_t ACTSNRMODEus;
	char VirtualNoisePSDds[98];
	char VirtualNoisePSDus[50];
	uint32_t ACTUALCE;
	int LineNumber;
	uint32_t UpstreamMaxBitRate;
	uint32_t DownstreamMaxBitRate;
	int UpstreamNoiseMargin;
	int DownstreamNoiseMargin;
	char SNRMpbus[25];
	char SNRMpbds[25];
	uint32_t INMIATOds;
	uint32_t INMIATSds;
	uint32_t INMCCds;
	uint32_t INMINPEQMODEds;
	int UpstreamAttenuation;
	int DownstreamAttenuation;
	int UpstreamPower;
	int DownstreamPower;
	uint32_t ACTINPROCds;
	uint32_t ACTINPROCus;
	uint32_t X_ZYXEL_ds_inp;
	uint32_t X_ZYXEL_us_inp;
	uint32_t X_ZYXEL_GinpActShineValue_ds;
	uint32_t X_ZYXEL_GinpActShineValue_us;
	uint32_t X_ZYXEL_GinpActReinValue_ds;
	uint32_t X_ZYXEL_GinpActReinValue_us;
	char XTURVendor[9];
	char XTURCountry[5];
	uint32_t XTURANSIStd;
	uint32_t XTURANSIRev;
	char XTUCVendor[9];
	char XTUCCountry[5];
	uint32_t XTUCANSIStd;
	uint32_t XTUCANSIRev;
	uint32_t X_ZYXEL_UpstreamCurrRate;
	uint32_t X_ZYXEL_DownstreamCurrRate;
	uint32_t X_ZYXEL_UpstreamCurrRate_2;
	uint32_t X_ZYXEL_DownstreamCurrRate_2;
	uint32_t X_ZYXEL_BondingLineNumber;
	bool X_ZYXEL_VDSL_8a;
	bool X_ZYXEL_VDSL_8b;
	bool X_ZYXEL_VDSL_8c;
	bool X_ZYXEL_VDSL_8d;
	bool X_ZYXEL_VDSL_12a;
	bool X_ZYXEL_VDSL_12b;
	bool X_ZYXEL_VDSL_17a;
	bool X_ZYXEL_VDSL_30a;
	bool X_ZYXEL_VDSL_35b;
	bool X_ZYXEL_VDSL_US0_8a;
	bool X_ZYXEL_ADSL2_AnnexM;
	char X_ZYXEL_ADSL2_AnnexA_B[17];
	char X_ZYXEL_PhoneLinePair[17];
	char X_ZYXEL_Bitswap[9];
	char X_ZYXEL_SRA[9];
	char X_ZYXEL_DSLType[9];
	char X_ZYXEL_TrellisD[9];
	char X_ZYXEL_TrellisU[9];
	char X_ZYXEL_LinkPowerState[4];
	char X_ZYXEL_AdslModulationCfg[129];
	uint32_t X_ZYXEL_DslCfgParam;
	int X_ZYXEL_DslTrainingMarginQ4;
	int X_ZYXEL_DslShowtimeMarginQ4;
	int X_ZYXEL_DslLOMTimeThldSec;
	int X_ZYXEL_DslPwmSyncClockFreq;
	int X_ZYXEL_DslHsModeSwitchTime;
	uint32_t X_ZYXEL_DslParam;
	uint32_t X_ZYXEL_DslPhyCfg1Mask;
	uint32_t X_ZYXEL_DslPhyCfg1Value;
	uint32_t X_ZYXEL_DslPhyCfg2Mask;
	uint32_t X_ZYXEL_DslPhyCfg2Value;
	uint32_t X_ZYXEL_DslPhyCfg3Mask;
	uint32_t X_ZYXEL_DslPhyCfg3Value;
	uint32_t X_ZYXEL_DslPhyCfg4Mask;
	uint32_t X_ZYXEL_DslPhyCfg4Value;
	uint32_t X_ZYXEL_DslPhyCfg5Mask;
	uint32_t X_ZYXEL_DslPhyCfg5Value;
	uint32_t X_ZYXEL_DslPhyCfg6Mask;
	uint32_t X_ZYXEL_DslPhyCfg6Value;
	uint32_t X_ZYXEL_DslPhyCfg7Mask;
	uint32_t X_ZYXEL_DslPhyCfg7Value;
	uint32_t X_ZYXEL_DslPhyCfg8Mask;
	uint32_t X_ZYXEL_DslPhyCfg8Value;
	uint32_t X_ZYXEL_DslPhyUsDataRateKbps;
	uint32_t X_ZYXEL_DslPhyDsDataRateKbps;
	uint32_t X_ZYXEL_DslPhyAggrDataRateKbps;
	uint32_t X_ZYXEL_DslPhyMiscCfgParam;
	uint32_t X_ZYXEL_ADSL2_UpstreamMSGc;
	uint32_t X_ZYXEL_ADSL2_UpstreamMSGc_2;
	uint32_t X_ZYXEL_ADSL2_DownstreamMSGc;
	uint32_t X_ZYXEL_ADSL2_DownstreamMSGc_2;
	uint32_t X_ZYXEL_ADSL2_UpstreamB;
	uint32_t X_ZYXEL_ADSL2_UpstreamB_2;
	uint32_t X_ZYXEL_ADSL2_DownstreamB;
	uint32_t X_ZYXEL_ADSL2_DownstreamB_2;
	uint32_t X_ZYXEL_ADSL2_UpstreamM;
	uint32_t X_ZYXEL_ADSL2_UpstreamM_2;
	uint32_t X_ZYXEL_ADSL2_DownstreamM;
	uint32_t X_ZYXEL_ADSL2_DownstreamM_2;
	uint32_t X_ZYXEL_ADSL2_UpstreamT;
	uint32_t X_ZYXEL_ADSL2_UpstreamT_2;
	uint32_t X_ZYXEL_ADSL2_DownstreamT;
	uint32_t X_ZYXEL_ADSL2_DownstreamT_2;
	uint32_t X_ZYXEL_ADSL2_UpstreamR;
	uint32_t X_ZYXEL_ADSL2_UpstreamR_2;
	uint32_t X_ZYXEL_ADSL2_DownstreamR;
	uint32_t X_ZYXEL_ADSL2_DownstreamR_2;
	uint32_t X_ZYXEL_ADSL2_UpstreamL;
	uint32_t X_ZYXEL_ADSL2_UpstreamL_2;
	uint32_t X_ZYXEL_ADSL2_DownstreamL;
	uint32_t X_ZYXEL_ADSL2_DownstreamL_2;
	uint32_t X_ZYXEL_UpstreamK;
	uint32_t X_ZYXEL_DownstreamK;
	char X_ZYXEL_UpstreamS[33];
	char X_ZYXEL_DownstreamS[33];
	uint32_t X_ZYXEL_UpstreamR;
	uint32_t X_ZYXEL_DownstreamR;
	char X_ZYXEL_ADSL2_UpstreamS[33];
	char X_ZYXEL_ADSL2_UpstreamS_2[33];
	char X_ZYXEL_ADSL2_DownstreamS[33];
	char X_ZYXEL_ADSL2_DownstreamS_2[33];
	char X_ZYXEL_UpstreamDelay[33];
	char X_ZYXEL_UpstreamDelay_2[33];
	char X_ZYXEL_DownstreamDelay[33];
	char X_ZYXEL_DownstreamDelay_2[33];
	char X_ZYXEL_UpstreamINP[33];
	char X_ZYXEL_UpstreamINP_2[33];
	char X_ZYXEL_DownstreamINP[33];
	char X_ZYXEL_DownstreamINP_2[33];
	uint32_t X_ZYXEL_UpstreamD;
	uint32_t X_ZYXEL_UpstreamD_2;
	uint32_t X_ZYXEL_DownstreamD;
	uint32_t X_ZYXEL_DownstreamD_2;
	uint32_t X_ZYXEL_VDSL_UpstreamI;
	uint32_t X_ZYXEL_VDSL_UpstreamI_2;
	uint32_t X_ZYXEL_VDSL_DownstreamI;
	uint32_t X_ZYXEL_VDSL_DownstreamI_2;
	uint32_t X_ZYXEL_VDSL_UpstreamN;
	uint32_t X_ZYXEL_VDSL_DownstreamN;
	uint32_t X_ZYXEL_VDSL_UpstreamN_2;
	uint32_t X_ZYXEL_VDSL_DownstreamN_2;
	char X_ZYXEL_ModulationType[17];
	bool X_ZYXEL_LinkTypeisATM;
	char X_ZYXEL_EOC_VENDOR_ID[33];
	char X_ZYXEL_EOC_SERIAL[33];
	char X_ZYXEL_EOC_VERSION[33];
	char X_ZYXEL_DSL_Up_Time[33];
} rdm_DslLine_t;

typedef struct rdm_DslLineSt_s {   // RDM_OID_DSL_LINE_ST 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSent;
	uint64_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t ErrorsReceived;
	uint32_t DiscardPacketsSent;
	uint32_t DiscardPacketsReceived;
	uint32_t TotalStart;
	uint32_t ShowtimeStart;
	uint32_t LastShowtimeStart;
	uint32_t CurrentDayStart;
	uint32_t QuarterHourStart;
} rdm_DslLineSt_t;

typedef struct rdm_DslLineStTotal_s {   // RDM_OID_DSL_LINE_ST_TOTAL 
	uint32_t ErroredSecs;
	uint32_t SeverelyErroredSecs;
	uint32_t X_ZYXEL_ReceiveBlocks;
	uint32_t X_ZYXEL_TransmitBlocks;
	uint32_t X_ZYXEL_superframeserrors_ds;
	uint32_t X_ZYXEL_superframeserrors_us;
	uint32_t X_ZYXEL_CellDelin;
	uint32_t X_ZYXEL_LinkRetrain;
	uint32_t X_ZYXEL_InitErrors;
	bool X_ZYXEL_LInit;
	uint32_t X_ZYXEL_InitTimeouts;
	uint32_t X_ZYXEL_LossOfFraming;
	bool X_ZYXEL_LOF;
	uint32_t X_ZYXEL_ATUCErroredSecs;
	uint32_t X_ZYXEL_ATUCSeverelyErroredSecs;
	uint32_t X_ZYXEL_FECErrors;
	uint32_t X_ZYXEL_ATUCFECErrors;
	uint32_t X_ZYXEL_HECErrors;
	uint32_t X_ZYXEL_ATUCHECErrors;
	uint32_t X_ZYXEL_CRCErrors;
	uint32_t X_ZYXEL_ATUCCRCErrors;
	uint32_t X_ZYXEL_RSWords_ds;
	uint32_t X_ZYXEL_RSWords_us;
	uint32_t X_ZYXEL_DsEs;
	uint32_t X_ZYXEL_UsEs;
	uint32_t X_ZYXEL_DsSes;
	uint32_t X_ZYXEL_UsSes;
	uint32_t X_ZYXEL_RxUAS;
	uint32_t X_ZYXEL_TxUAS;
} rdm_DslLineStTotal_t;

typedef struct rdm_DslLineStShowtime_s {   // RDM_OID_DSL_LINE_ST_SHOWTIME 
	uint32_t ErroredSecs;
	uint32_t SeverelyErroredSecs;
	uint32_t X_ZYXEL_ReceiveBlocks;
	uint32_t X_ZYXEL_TransmitBlocks;
	uint32_t X_ZYXEL_superframeserrors_ds;
	uint32_t X_ZYXEL_superframeserrors_us;
	uint32_t X_ZYXEL_CellDelin;
	uint32_t X_ZYXEL_LinkRetrain;
	uint32_t X_ZYXEL_InitErrors;
	bool X_ZYXEL_LInit;
	uint32_t X_ZYXEL_InitTimeouts;
	uint32_t X_ZYXEL_LossOfFraming;
	bool X_ZYXEL_LOF;
	uint32_t X_ZYXEL_ATUCErroredSecs;
	uint32_t X_ZYXEL_ATUCSeverelyErroredSecs;
	uint32_t X_ZYXEL_FECErrors;
	uint32_t X_ZYXEL_ATUCFECErrors;
	uint32_t X_ZYXEL_HECErrors;
	uint32_t X_ZYXEL_ATUCHECErrors;
	uint32_t X_ZYXEL_CRCErrors;
	uint32_t X_ZYXEL_ATUCCRCErrors;
} rdm_DslLineStShowtime_t;

typedef struct rdm_DslLineStLastShowtime_s {   // RDM_OID_DSL_LINE_ST_LAST_SHOWTIME 
	uint32_t ErroredSecs;
	uint32_t SeverelyErroredSecs;
} rdm_DslLineStLastShowtime_t;

typedef struct rdm_DslLineStLastCurDay_s {   // RDM_OID_DSL_LINE_ST_LAST_CUR_DAY 
	uint32_t ErroredSecs;
	uint32_t SeverelyErroredSecs;
	uint32_t X_ZYXEL_ReceiveBlocks;
	uint32_t X_ZYXEL_TransmitBlocks;
	uint32_t X_ZYXEL_CellDelin;
	uint32_t X_ZYXEL_LinkRetrain;
	uint32_t X_ZYXEL_InitErrors;
	bool X_ZYXEL_LInit;
	uint32_t X_ZYXEL_InitTimeouts;
	uint32_t X_ZYXEL_LossOfFraming;
	bool X_ZYXEL_LOF;
	uint32_t X_ZYXEL_ATUCErroredSecs;
	uint32_t X_ZYXEL_ATUCSeverelyErroredSecs;
	uint32_t X_ZYXEL_FECErrors;
	uint32_t X_ZYXEL_ATUCFECErrors;
	uint32_t X_ZYXEL_HECErrors;
	uint32_t X_ZYXEL_ATUCHECErrors;
	uint32_t X_ZYXEL_CRCErrors;
	uint32_t X_ZYXEL_ATUCCRCErrors;
} rdm_DslLineStLastCurDay_t;

typedef struct rdm_DslLineStLastQuarHr_s {   // RDM_OID_DSL_LINE_ST_LAST_QUAR_HR 
	uint32_t ErroredSecs;
	uint32_t SeverelyErroredSecs;
} rdm_DslLineStLastQuarHr_t;

typedef struct rdm_DslLineTestParams_s {   // RDM_OID_DSL_LINE_TEST_PARAMS 
	uint32_t HLOGGds;
	uint32_t HLOGGus;
	char HLOGpsds[2560];
	char HLOGpsus[2560];
	uint32_t HLOGMTds;
	uint32_t HLOGMTus;
	uint32_t QLNGds;
	uint32_t QLNGus;
	char QLNpsds[2048];
	char QLNpsus[2048];
	uint32_t QLNMTds;
	uint32_t QLNMTus;
	uint32_t SNRGds;
	uint32_t SNRGus;
	char SNRpsds[2048];
	char SNRpsus[2048];
	uint32_t SNRMTds;
	uint32_t SNRMTus;
	char LATNds[25];
	char LATNus[25];
	char SATNds[25];
	char SATNus[25];
} rdm_DslLineTestParams_t;

typedef struct rdm_DslChannel_s {   // RDM_OID_DSL_CHANNEL 
	bool Enable;
	char Status[17];
	char Alias[65];
	char Name[65];
	uint32_t LastChange;
	char LowerLayers[1025];
	char LinkEncapsulationSupported[21];
	char LinkEncapsulationUsed[21];
	uint32_t LPATH;
	uint32_t INTLVDEPTH;
	int INTLVBLOCK;
	uint32_t ActualInterleavingDelay;
	int ACTINP;
	bool INPREPORT;
	int NFEC;
	int RFEC;
	int LSYMB;
	uint32_t UpstreamCurrRate;
	uint32_t DownstreamCurrRate;
	char DSLUpTime[33];
} rdm_DslChannel_t;

typedef struct rdm_DslChannelSt_s {   // RDM_OID_DSL_CHANNEL_ST 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSent;
	uint64_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t ErrorsReceived;
	uint32_t DiscardPacketsSent;
	uint32_t DiscardPacketsReceived;
	uint32_t TotalStart;
	uint32_t ShowtimeStart;
	uint32_t LastShowtimeStart;
	uint32_t CurrentDayStart;
	uint32_t QuarterHourStart;
} rdm_DslChannelSt_t;

typedef struct rdm_DslChannelStTotal_s {   // RDM_OID_DSL_CHANNEL_ST_TOTAL 
	uint32_t XTURFECErrors;
	uint32_t XTUCFECErrors;
	uint32_t XTURHECErrors;
	uint32_t XTUCHECErrors;
	uint32_t XTURCRCErrors;
	uint32_t XTUCCRCErrors;
} rdm_DslChannelStTotal_t;

typedef struct rdm_DslChannelStShowtime_s {   // RDM_OID_DSL_CHANNEL_ST_SHOWTIME 
	uint32_t XTURFECErrors;
	uint32_t XTUCFECErrors;
	uint32_t XTURHECErrors;
	uint32_t XTUCHECErrors;
	uint32_t XTURCRCErrors;
	uint32_t XTUCCRCErrors;
} rdm_DslChannelStShowtime_t;

typedef struct rdm_DslChannelStLastShowtime_s {   // RDM_OID_DSL_CHANNEL_ST_LAST_SHOWTIME 
	uint32_t XTURFECErrors;
	uint32_t XTUCFECErrors;
	uint32_t XTURHECErrors;
	uint32_t XTUCHECErrors;
	uint32_t XTURCRCErrors;
	uint32_t XTUCCRCErrors;
} rdm_DslChannelStLastShowtime_t;

typedef struct rdm_DslChannelStCurDay_s {   // RDM_OID_DSL_CHANNEL_ST_CUR_DAY 
	uint32_t XTURFECErrors;
	uint32_t XTUCFECErrors;
	uint32_t XTURHECErrors;
	uint32_t XTUCHECErrors;
	uint32_t XTURCRCErrors;
	uint32_t XTUCCRCErrors;
} rdm_DslChannelStCurDay_t;

typedef struct rdm_DslChannelStQuarHr_s {   // RDM_OID_DSL_CHANNEL_ST_QUAR_HR 
	uint32_t XTURFECErrors;
	uint32_t XTUCFECErrors;
	uint32_t XTURHECErrors;
	uint32_t XTUCHECErrors;
	uint32_t XTURCRCErrors;
	uint32_t XTUCCRCErrors;
} rdm_DslChannelStQuarHr_t;

typedef struct rdm_DslBondGp_s {   // RDM_OID_DSL_BOND_GP 
	bool Enable;
	char Status[17];
	char Alias[65];
	char Name[65];
	uint32_t LastChange;
	char LowerLayers[1025];
	char GroupStatus[129];
	uint32_t GroupID;
	char BondSchemesSupported[25];
	char BondScheme[25];
	uint32_t GroupCapacity;
	uint32_t RunningTime;
	uint32_t TargetUpRate;
	uint32_t TargetDownRate;
	uint32_t ThreshLowUpRate;
	uint32_t ThreshLowDownRate;
	uint32_t UpstreamDifferentialDelayTolerance;
	uint32_t DownstreamDifferentialDelayTolerance;
	uint32_t BondedChannelNumberOfEntries;
	uint32_t X_ZYXEL_TimeStampLastChange;
} rdm_DslBondGp_t;

typedef struct rdm_DslBondGpBondedChannel_s {   // RDM_OID_DSL_BOND_GP_BONDED_CHANNEL 
	char Alias[65];
	char Channel[257];
} rdm_DslBondGpBondedChannel_t;

typedef struct rdm_DslBondGpBondedChannelEth_s {   // RDM_OID_DSL_BOND_GP_BONDED_CHANNEL_ETH 
} rdm_DslBondGpBondedChannelEth_t;

typedef struct rdm_DslBondGpBondedChannelEthSt_s {   // RDM_OID_DSL_BOND_GP_BONDED_CHANNEL_ETH_ST 
	uint32_t UnderflowErrorsSent;
	uint32_t CRCErrorsReceived;
	uint32_t AlignmentErrorsReceived;
	uint32_t ShortPacketsReceived;
	uint32_t LongPacketsReceived;
	uint32_t OverflowErrorsReceived;
	uint32_t PauseFramesReceived;
	uint32_t FramesDropped;
} rdm_DslBondGpBondedChannelEthSt_t;

typedef struct rdm_DslBondGpSt_s {   // RDM_OID_DSL_BOND_GP_ST 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSent;
	uint64_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t ErrorsReceived;
	uint64_t UnicastPacketsSent;
	uint64_t UnicastPacketsReceived;
	uint32_t DiscardPacketsSent;
	uint32_t DiscardPacketsReceived;
	uint64_t MulticastPacketsSent;
	uint64_t MulticastPacketsReceived;
	uint64_t BroadcastPacketsSent;
	uint64_t BroadcastPacketsReceived;
	uint32_t UnknownProtoPacketsReceived;
	uint32_t TotalStart;
	uint32_t CurrentDayStart;
	uint32_t QuarterHourStart;
} rdm_DslBondGpSt_t;

typedef struct rdm_DslBondGpStTotal_s {   // RDM_OID_DSL_BOND_GP_ST_TOTAL 
	char FailureReasons[20];
	uint32_t UpstreamRate;
	uint32_t DownstreamRate;
	uint32_t UpstreamPacketLoss;
	uint32_t DownstreamPacketLoss;
	uint32_t UpstreamDifferentialDelay;
	uint32_t DownstreamDifferentialDelay;
	uint32_t FailureCount;
	uint32_t ErroredSeconds;
	uint32_t SeverelyErroredSeconds;
	uint32_t UnavailableSeconds;
} rdm_DslBondGpStTotal_t;

typedef struct rdm_DslBondGpStCurrentDay_s {   // RDM_OID_DSL_BOND_GP_ST_CURRENT_DAY 
	char FailureReasons[20];
	uint32_t UpstreamRate;
	uint32_t DownstreamRate;
	uint32_t UpstreamPacketLoss;
	uint32_t DownstreamPacketLoss;
	uint32_t UpstreamDifferentialDelay;
	uint32_t DownstreamDifferentialDelay;
	uint32_t FailureCount;
	uint32_t ErroredSeconds;
	uint32_t SeverelyErroredSeconds;
	uint32_t UnavailableSeconds;
} rdm_DslBondGpStCurrentDay_t;

typedef struct rdm_DslBondGpStQtrHr_s {   // RDM_OID_DSL_BOND_GP_ST_QTR_HR 
	char FailureReasons[20];
	uint32_t UpstreamRate;
	uint32_t DownstreamRate;
	uint32_t UpstreamPacketLoss;
	uint32_t DownstreamPacketLoss;
	uint32_t UpstreamDifferentialDelay;
	uint32_t DownstreamDifferentialDelay;
	uint32_t FailureCount;
	uint32_t ErroredSeconds;
	uint32_t SeverelyErroredSeconds;
	uint32_t UnavailableSeconds;
} rdm_DslBondGpStQtrHr_t;

typedef struct rdm_DslBondGpEth_s {   // RDM_OID_DSL_BOND_GP_ETH 
} rdm_DslBondGpEth_t;

typedef struct rdm_DslBondGpEthSt_s {   // RDM_OID_DSL_BOND_GP_ETH_ST 
	uint32_t PAFErrors;
	uint32_t PAFSmallFragments;
	uint32_t PAFLargeFragments;
	uint32_t PAFBadFragments;
	uint32_t PAFLostFragments;
	uint32_t PAFLateFragments;
	uint32_t PAFLostStarts;
	uint32_t PAFLostEnds;
	uint32_t PAFOverflows;
	uint32_t PauseFramesSent;
	uint32_t CRCErrorsReceived;
	uint32_t AlignmentErrorsReceived;
	uint32_t ShortPacketsReceived;
	uint32_t LongPacketsReceived;
	uint32_t OverflowErrorsReceived;
	uint32_t FramesDropped;
} rdm_DslBondGpEthSt_t;

typedef struct rdm_DslDiag_s {   // RDM_OID_DSL_DIAG 
} rdm_DslDiag_t;

typedef struct rdm_DslDiagAdslLineTest_s {   // RDM_OID_DSL_DIAG_ADSL_LINE_TEST 
	char DiagnosticsState[15];
	char Interface[257];
	int ACTPSDds;
	int ACTPSDus;
	int ACTATPds;
	int ACTATPus;
	int HLINSCds;
	int HLINSCus;
	uint32_t HLINGds;
	uint32_t HLINGus;
	uint32_t HLOGGds;
	uint32_t HLOGGus;
	char HLOGpsds[2560];
	char HLOGpsus[2560];
	uint32_t HLOGMTds;
	uint32_t HLOGMTus;
	char LATNpbds[25];
	char LATNpbus[25];
	char SATNds[25];
	char SATNus[25];
	char HLINpsds[61431];
	char HLINpsus[61431];
	uint32_t QLNGds;
	uint32_t QLNGus;
	char QLNpsds[61431];
	char QLNpsus[61431];
	uint32_t QLNMTds;
	uint32_t QLNMTus;
	uint32_t SNRGds;
	uint32_t SNRGus;
	char SNRpsds[61431];
	char SNRpsus[61431];
	uint32_t SNRMTds;
	uint32_t SNRMTus;
	char BITSpsds[61431];
	char BITSpsus[61431];
} rdm_DslDiagAdslLineTest_t;

typedef struct rdm_Opt_s {   // RDM_OID_OPT 
	uint32_t InterfaceNumberOfEntries;
} rdm_Opt_t;

typedef struct rdm_OptIntf_s {   // RDM_OID_OPT_INTF 
	bool Enable;
	char Status[15];
	char Alias[65];
	char Name[65];
	uint32_t LastChange;
	char LowerLayers[1025];
	bool Upstream;
	int OpticalSignalLevel;
	int LowerOpticalThreshold;
	int UpperOpticalThreshold;
	int TransmitOpticalLevel;
	int LowerTransmitPowerThreshold;
	int UpperTransmitPowerThreshold;
} rdm_OptIntf_t;

typedef struct rdm_OptIntfSt_s {   // RDM_OID_OPT_INTF_ST 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSent;
	uint64_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t ErrorsReceived;
	uint32_t DiscardPacketsSent;
	uint32_t DiscardPacketsReceived;
} rdm_OptIntfSt_t;

typedef struct rdm_Atm_s {   // RDM_OID_ATM 
	uint32_t LinkNumberOfEntries;
} rdm_Atm_t;

typedef struct rdm_AtmLink_s {   // RDM_OID_ATM_LINK 
	bool Enable;
	char Status[17];
	char Alias[65];
	char Name[65];
	uint32_t LastChange;
	char LowerLayers[1025];
	char LinkType[17];
	bool AutoConfig;
	char DestinationAddress[257];
	char Encapsulation[7];
	bool FCSPreserved;
	char VCSearchList[257];
	char AAL[6];
	char X_ZYXEL_IfName[19];
	uint32_t X_ZYXEL_ATMInterfaceId;
	char X_ZYXEL_GrpScheduler[4];
	uint32_t X_ZYXEL_GrpWeight;
	uint32_t X_ZYXEL_GrpPrecedence;
	char X_ZYXEL_SchedulerAlgorithm[4];
	uint32_t X_ZYXEL_QueueWeight;
	uint32_t X_ZYXEL_QueuePrecedence;
} rdm_AtmLink_t;

typedef struct rdm_AtmLinkSt_s {   // RDM_OID_ATM_LINK_ST 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSent;
	uint64_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t ErrorsReceived;
	uint64_t UnicastPacketsSent;
	uint64_t UnicastPacketsReceived;
	uint32_t DiscardPacketsSent;
	uint32_t DiscardPacketsReceived;
	uint64_t MulticastPacketsSent;
	uint64_t MulticastPacketsReceived;
	uint64_t BroadcastPacketsSent;
	uint64_t BroadcastPacketsReceived;
	uint32_t UnknownProtoPacketsReceived;
	uint32_t TransmittedBlocks;
	uint32_t ReceivedBlocks;
	uint32_t CRCErrors;
	uint32_t HECErrors;
	uint32_t X_ZYXEL_SARTimeout;
	uint32_t X_ZYXEL_OversizedSDUs_Tx;
	uint32_t X_ZYXEL_OversizedSDUs_Rx;
	uint32_t X_ZYXEL_ShortPacketerrors_Tx;
	uint32_t X_ZYXEL_ShortPacketerrors_Rx;
} rdm_AtmLinkSt_t;

typedef struct rdm_AtmLinkQos_s {   // RDM_OID_ATM_LINK_QOS 
	char QoSClass[9];
	uint32_t PeakCellRate;
	uint32_t MaximumBurstSize;
	uint32_t SustainableCellRate;
	int X_ZYXEL_ATMMinimumCellRate;
} rdm_AtmLinkQos_t;

typedef struct rdm_AtmDiag_s {   // RDM_OID_ATM_DIAG 
} rdm_AtmDiag_t;

typedef struct rdm_AtmDiagF5Lo_s {   // RDM_OID_ATM_DIAG_F5_LO 
	char DiagnosticsState[17];
	char Interface[257];
	uint32_t NumberOfRepetitions;
	uint32_t Timeout;
	uint32_t SuccessCount;
	uint32_t FailureCount;
	uint32_t AverageResponseTime;
	uint32_t MinimumResponseTime;
	uint32_t MaximumResponseTime;
	char X_ZYXEL_Creator[23];
	bool X_ZYXEL_SegmentLoopback;
} rdm_AtmDiagF5Lo_t;

typedef struct rdm_AtmDiagF4Lo_s {   // RDM_OID_ATM_DIAG_F4_LO 
	char DiagnosticsState[17];
	char Interface[257];
	uint32_t NumberOfRepetitions;
	uint32_t Timeout;
	uint32_t SuccessCount;
	uint32_t FailureCount;
	uint32_t AverageResponseTime;
	uint32_t MinimumResponseTime;
	uint32_t MaximumResponseTime;
	char Creator[23];
	bool SegmentLoopback;
} rdm_AtmDiagF4Lo_t;

typedef struct rdm_Ptm_s {   // RDM_OID_PTM 
	uint32_t LinkNumberOfEntries;
} rdm_Ptm_t;

typedef struct rdm_PtmLink_s {   // RDM_OID_PTM_LINK 
	bool Enable;
	char Status[17];
	char Alias[65];
	char Name[65];
	uint32_t LastChange;
	char LowerLayers[1025];
	char MACAddress[18];
	char X_ZYXEL_IfName[19];
	uint32_t X_ZYXEL_PTMPortId;
	uint32_t X_ZYXEL_QueueShapingBurstSize;
	bool X_ZYXEL_PTMPriorityHigh;
	bool X_ZYXEL_PTMPriorityLow;
	char X_ZYXEL_GrpScheduler[4];
	uint32_t X_ZYXEL_GrpWeight;
	uint32_t X_ZYXEL_GrpPrecedence;
	char X_ZYXEL_SchedulerAlgorithm[4];
	uint32_t X_ZYXEL_QueueWeight;
	uint32_t X_ZYXEL_QueuePrecedence;
	uint32_t X_ZYXEL_QueueShapingRate;
	int X_ZYXEL_QueueMinimumRate;
	char X_ZYXEL_ConnectionMode[19];
	bool X_ZYXEL_EnableADSLPtm;
} rdm_PtmLink_t;

typedef struct rdm_PtmLinkSt_s {   // RDM_OID_PTM_LINK_ST 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSent;
	uint64_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t ErrorsReceived;
	uint64_t UnicastPacketsSent;
	uint64_t UnicastPacketsReceived;
	uint32_t DiscardPacketsSent;
	uint32_t DiscardPacketsReceived;
	uint64_t MulticastPacketsSent;
	uint64_t MulticastPacketsReceived;
	uint64_t BroadcastPacketsSent;
	uint64_t BroadcastPacketsReceived;
	uint32_t UnknownProtoPacketsReceived;
	uint32_t X_ZYXEL_SARTimeout;
	uint32_t X_ZYXEL_OversizedSDUs_Tx;
	uint32_t X_ZYXEL_OversizedSDUs_Rx;
	uint32_t X_ZYXEL_ShortPacketerrors_Tx;
	uint32_t X_ZYXEL_ShortPacketerrors_Rx;
} rdm_PtmLinkSt_t;

typedef struct rdm_Eth_s {   // RDM_OID_ETH 
	uint32_t InterfaceNumberOfEntries;
	uint32_t LinkNumberOfEntries;
	uint32_t VLANTerminationNumberOfEntries;
	uint32_t RMONStatsNumberOfEntries;
} rdm_Eth_t;

typedef struct rdm_EthRmonSt_s {   // RDM_OID_ETH_RMON_ST 
	bool Enable;
	char Status[25];
	char Alias[65];
	char Name[65];
	char Interface[33];
	uint32_t VLANID;
	char Queue[17];
	bool AllQueues;
	uint32_t DropEvents;
	uint64_t Bytes;
	uint64_t Packets;
	uint64_t BroadcastPackets;
	uint64_t MulticastPackets;
	uint32_t CRCErroredPackets;
	uint32_t UndersizePackets;
	uint32_t OversizePackets;
	uint64_t Packets64Bytes;
	uint64_t Packets65to127Bytes;
	uint64_t Packets128to255Bytes;
	uint64_t Packets256to511Bytes;
	uint64_t Packets512to1023Bytes;
	uint64_t Packets1024to1518Bytes;
} rdm_EthRmonSt_t;

typedef struct rdm_EthIface_s {   // RDM_OID_ETH_IFACE 
	bool Enable;
	char Status[17];
	char Alias[65];
	char Name[65];
	uint32_t LastChange;
	char LowerLayers[1025];
	bool Upstream;
	char MACAddress[18];
	bool IntfEnable;
	int MaxBitRate;
	char DuplexMode[6];
	char X_ZYXEL_DuplexMode[6];
	int X_ZYXEL_MaxBitRate;
	char X_ZYXEL_LanPort[65];
	bool X_ZYXEL_SwitchToWAN;
	bool X_ZYXEL_Upstream;
	uint32_t X_ZYXEL_UpTime;
	uint32_t X_ZYXEL_LastChangeTime;
} rdm_EthIface_t;

typedef struct rdm_EthIntfSt_s {   // RDM_OID_ETH_INTF_ST 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSent;
	uint64_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t ErrorsReceived;
	uint64_t UnicastPacketsSent;
	uint64_t UnicastPacketsReceived;
	uint32_t DiscardPacketsSent;
	uint32_t DiscardPacketsReceived;
	uint64_t MulticastPacketsSent;
	uint64_t MulticastPacketsReceived;
	uint64_t BroadcastPacketsSent;
	uint64_t BroadcastPacketsReceived;
	uint32_t UnknownProtoPacketsReceived;
} rdm_EthIntfSt_t;

typedef struct rdm_EthLink_s {   // RDM_OID_ETH_LINK 
	bool Enable;
	char Status[17];
	char Alias[65];
	char Name[65];
	uint32_t LastChange;
	char LowerLayers[1025];
	char MACAddress[18];
	bool PriorityTagging;
	bool X_ZYXEL_OrigEthWAN;
	char X_ZYXEL_WanMacType[17];
	char X_ZYXEL_WanMacAddr[18];
	char X_ZYXEL_WanMacClientIP[16];
} rdm_EthLink_t;

typedef struct rdm_EthLinkSt_s {   // RDM_OID_ETH_LINK_ST 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSent;
	uint64_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t ErrorsReceived;
	uint64_t UnicastPacketsSent;
	uint64_t UnicastPacketsReceived;
	uint32_t DiscardPacketsSent;
	uint32_t DiscardPacketsReceived;
	uint64_t MulticastPacketsSent;
	uint64_t MulticastPacketsReceived;
	uint64_t BroadcastPacketsSent;
	uint64_t BroadcastPacketsReceived;
	uint32_t UnknownProtoPacketsReceived;
} rdm_EthLinkSt_t;

typedef struct rdm_EthVlanTerm_s {   // RDM_OID_ETH_VLAN_TERM 
	bool Enable;
	bool X_ZYXEL_VLANEnable;
	char Status[17];
	char Alias[65];
	char Name[65];
	char X_ZYXEL_VLANName[65];
	uint32_t LastChange;
	char LowerLayers[1025];
	int VLANID;
	int X_ZYXEL_VLANPriority;
	uint32_t X_ZYXEL_MAC_Index;
} rdm_EthVlanTerm_t;

typedef struct rdm_EthVlanTermSt_s {   // RDM_OID_ETH_VLAN_TERM_ST 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSent;
	uint64_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t ErrorsReceived;
	uint64_t UnicastPacketsSent;
	uint64_t UnicastPacketsReceived;
	uint32_t DiscardPacketsSent;
	uint32_t DiscardPacketsReceived;
	uint64_t MulticastPacketsSent;
	uint64_t MulticastPacketsReceived;
	uint64_t BroadcastPacketsSent;
	uint64_t BroadcastPacketsReceived;
	uint32_t UnknownProtoPacketsReceived;
} rdm_EthVlanTermSt_t;

typedef struct rdm_Usb_s {   // RDM_OID_USB 
	uint32_t InterfaceNumberOfEntries;
	uint32_t PortNumberOfEntries;
} rdm_Usb_t;

typedef struct rdm_UsbIntf_s {   // RDM_OID_USB_INTF 
	bool Enable;
	char Status[17];
	char Alias[65];
	char Name[65];
	uint32_t LastChange;
	char LowerLayers[1025];
	bool Upstream;
	char MACAddress[18];
	uint32_t MaxBitRate;
	char Port[257];
	char X_ZYXEL_IfName[33];
} rdm_UsbIntf_t;

typedef struct rdm_UsbIntfStat_s {   // RDM_OID_USB_INTF_STAT 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSent;
	uint64_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t ErrorsReceived;
	uint64_t UnicastPacketsSent;
	uint64_t UnicastPacketsReceived;
	uint32_t DiscardPacketsSend;
	uint32_t DiscardPacketsReceived;
	uint64_t MulticastPacketsSent;
	uint64_t MulticastPacketsReceived;
	uint64_t BroadcastPacketsSent;
	uint64_t BroadcastPacketsReceived;
	uint32_t UnknownProtoPacketsReceived;
} rdm_UsbIntfStat_t;

typedef struct rdm_UsbPort_s {   // RDM_OID_USB_PORT 
	char Alias[65];
	char Name[65];
	char Standard[5];
	char Type[7];
	char Receptacle[11];
	char Rate[55];
	char Power[8];
	char X_ZYXEL_Portnum[6];
} rdm_UsbPort_t;

typedef struct rdm_UsbUsbhosts_s {   // RDM_OID_USB_USBHOSTS 
	uint32_t HostNumberOfEntries;
} rdm_UsbUsbhosts_t;

typedef struct rdm_UsbUsbhostsHost_s {   // RDM_OID_USB_USBHOSTS_HOST 
	char Alias[65];
	bool Enable;
	char Name[65];
	char Type[45];
	bool Reset;
	bool PowerManagementEnable;
	char USBVersion[5];
	uint32_t DeviceNumberOfEntries;
} rdm_UsbUsbhostsHost_t;

typedef struct rdm_UsbUsbhostsHostDev_s {   // RDM_OID_USB_USBHOSTS_HOST_DEV 
	uint32_t DeviceNumber;
	char USBVersion[5];
	char DeviceClass[3];
	char DeviceSubClass[3];
	uint32_t DeviceVersion;
	char DeviceProtocol[3];
	uint32_t ProductID;
	uint32_t VendorID;
	char Manufacturer[65];
	char ProductClass[65];
	char SerialNumber[65];
	uint32_t Port;
	char USBPort[25];
	char Rate[55];
	char Parent[49];
	uint32_t MaxChildren;
	bool IsSuspended;
	bool IsSelfPowered;
	uint32_t ConfigurationNumberOfEntries;
	char X_ZYXEL_MountPoint[257];
} rdm_UsbUsbhostsHostDev_t;

typedef struct rdm_UsbUsbhostsHostDevPar_s {   // RDM_OID_USB_USBHOSTS_HOST_DEV_PAR 
	char PartitionName[17];
	uint32_t Capacity;
	uint32_t UsedSpace;
	char Capacity_GByte[65];
	char UsedSpace_GByte[65];
} rdm_UsbUsbhostsHostDevPar_t;

typedef struct rdm_UsbUsbhostsHostDevCfg_s {   // RDM_OID_USB_USBHOSTS_HOST_DEV_CFG 
	uint32_t ConfigurationNumber;
	uint32_t InterfaceNumberOfEntries;
} rdm_UsbUsbhostsHostDevCfg_t;

typedef struct rdm_UsbUsbhostsHostDevCfgIntf_s {   // RDM_OID_USB_USBHOSTS_HOST_DEV_CFG_INTF 
	uint32_t InterfaceNumber;
	char InterfaceClass[2];
	char InterfaceSubClass[2];
	char InterfaceProtocol[2];
} rdm_UsbUsbhostsHostDevCfgIntf_t;

typedef struct rdm_Cellular_s {   // RDM_OID_CELLULAR 
	bool RoamingEnabled;
	uint32_t InterfaceNumberOfEntries;
	uint32_t AccessPointNumberOfEntries;
} rdm_Cellular_t;

typedef struct rdm_CellularInterface_s {   // RDM_OID_CELLULAR_INTERFACE 
	bool Enable;
	char Status[17];
	char Alias[65];
	char Name[65];
	uint32_t LastChange;
	char LowerLayers[1025];
	char SupportedAccessTechnologies[129];
	char PreferredAccessTechnology[17];
	char CurrentAccessTechnology[17];
	char AvailableNetworks[257];
	char NetworkRequested[65];
	char NetworkInUse[65];
	int RSSI;
} rdm_CellularInterface_t;

typedef struct rdm_CellularIfaceUSIM_s {   // RDM_OID_CELLULAR_IFACE_U_S_I_M 
	char Status[17];
	char IMSI[16];
	char PIN[5];
} rdm_CellularIfaceUSIM_t;

typedef struct rdm_CellularAccessPoint_s {   // RDM_OID_CELLULAR_ACCESS_POINT 
	bool Enable;
	char Alias[65];
	char APN[101];
	char X_ZYXEL_DialString[65];
	char X_ZYXEL_Auth[9];
	char Username[257];
	char Password[257];
	char Interface[33];
} rdm_CellularAccessPoint_t;

typedef struct rdm_Hpna_s {   // RDM_OID_HPNA 
	uint32_t InterfaceNumberOfEntries;
} rdm_Hpna_t;

typedef struct rdm_HpnaIntf_s {   // RDM_OID_HPNA_INTF 
	bool Enable;
	char Status[18];
	char Alias[65];
	char Name[65];
	uint32_t LastChange;
	char LowerLayer[1025];
	bool Upstream;
	char MACAddress[18];
	char FirmwareVersion[65];
	uint32_t NodeID;
	bool ISMaster;
	bool Synced;
	uint32_t TotalSyncTime;
	uint32_t MaxBitRate;
	uint32_t NetworkUtilization;
	char PossibleConnectionTypes[13];
	char ConnectionType[7];
	char PossibleSpectralModes[11];
	char SpectralMode[3];
	uint32_t MTU;
	uint32_t NoiseMargin;
	uint32_t DefaultNonLARQPER;
	bool LARQEnable;
	uint32_t MinMulticastRate;
	uint32_t NegMulticastRate;
	char MasterSelectionMode[59];
	uint32_t AssociatedDeviceNumberOfEntries;
} rdm_HpnaIntf_t;

typedef struct rdm_HpnaIntfSt_s {   // RDM_OID_HPNA_INTF_ST 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSend;
	uint64_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t ErrorsReceived;
	uint64_t UnicastPacketsSent;
	uint64_t UnicastPacketsReceived;
	uint32_t DiscardPacketsSent;
	uint32_t DiscardPacketsReceived;
	uint64_t MulticastPacketsSent;
	uint64_t MulticastPacketsReceived;
	uint64_t BroadcastPacketsSent;
	uint64_t BroadcastPacketsReceived;
	uint32_t UnknownProtoPacketsReceived;
} rdm_HpnaIntfSt_t;

typedef struct rdm_HpnaIntfQos_s {   // RDM_OID_HPNA_INTF_QOS 
	uint32_t FlowSpecNumberOfEntries;
} rdm_HpnaIntfQos_t;

typedef struct rdm_HpnaIntfQosFlowSpec_s {   // RDM_OID_HPNA_INTF_QOS_FLOW_SPEC 
	bool Enable;
	char Status[21];
	char Alias[65];
	char TrafficClasses[257];
	char FlowType[13];
	uint32_t Priority;
	uint32_t Latency;
	uint32_t Jitter;
	uint32_t PacketSize;
	uint32_t MinRate;
	uint32_t AvgRate;
	uint32_t MaxRate;
	uint32_t PER;
	uint32_t Timeout;
} rdm_HpnaIntfQosFlowSpec_t;

typedef struct rdm_HpnaIntfAssocDev_s {   // RDM_OID_HPNA_INTF_ASSOC_DEV 
	char MacAddress[18];
	uint32_t NodeID;
	bool IsMaster;
	bool Synced;
	uint32_t TotalSyncTime;
	uint32_t MaxBitRate;
	bool PHYDiagnosticsEnable;
	bool Active;
} rdm_HpnaIntfAssocDev_t;

typedef struct rdm_HpnaDiag_s {   // RDM_OID_HPNA_DIAG 
} rdm_HpnaDiag_t;

typedef struct rdm_HpnaDiagPhyThroughput_s {   // RDM_OID_HPNA_DIAG_PHY_THROUGHPUT 
	char DiagnosticsState[28];
	char Interface[257];
	uint32_t NumPacketsInBurst;
	uint32_t BurstInterval;
	uint32_t TestPacketPayloadLength;
	uint32_t PayloadEncoding;
	uint32_t PayloadDataGen;
	char PayloadType[14];
	uint32_t PriorityLevel;
	uint32_t ResultNumberOfEntries;
} rdm_HpnaDiagPhyThroughput_t;

typedef struct rdm_HpnaDiagPhyThroughputResult_s {   // RDM_OID_HPNA_DIAG_PHY_THROUGHPUT_RESULT 
	char SrcMACAddress[18];
	char DestMACAddress[18];
	uint32_t PHYRate;
	uint32_t BaudRate;
	uint32_t SNR;
	uint32_t PacketsReceived;
	uint32_t Attenuation;
} rdm_HpnaDiagPhyThroughputResult_t;

typedef struct rdm_HpnaDiagPerfMont_s {   // RDM_OID_HPNA_DIAG_PERF_MONT 
	char DiagnosticsState[28];
	char Interface[257];
	uint32_t SampleInterval;
} rdm_HpnaDiagPerfMont_t;

typedef struct rdm_HpnaDiagPerfMonitorNodes_s {   // RDM_OID_HPNA_DIAG_PERF_MONITOR_NODES 
	char CurrentStat[32];
	char CurrentEnd[32];
	uint32_t NodeNumberOfEntries;
} rdm_HpnaDiagPerfMonitorNodes_t;

typedef struct rdm_HpnaDiagPerfMonitorNodesNode_s {   // RDM_OID_HPNA_DIAG_PERF_MONITOR_NODES_NODE 
	char MACAddress[18];
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSent;
	uint64_t PacketsReceived;
	uint64_t BroadcastPacketsSent;
	uint64_t BroadcastPacketsReceived;
	uint64_t MulticastPacketsSent;
	uint64_t MulticastPacketsReceived;
	uint32_t PacketsCrcErrored;
	uint32_t PacketsShortErrored;
	uint32_t PacketsShortErroredHost;
	uint32_t RxPacketsDropped;
	uint32_t TxPacketsDropped;
	uint32_t ControlRequestLocal;
	uint32_t ControlReplyLocal;
	uint32_t ControlRequestRemote;
	uint32_t ControlReplyRemote;
	uint64_t PacketsSentWire;
	uint64_t MulticastPacketsSentWire;
	uint32_t PacketsInternalControl;
	uint32_t BroadcastPacketsInternalControl;
	uint32_t PacketsReceivedQueued;
	uint32_t PacketsReceivedFowardUnknown;
	uint32_t NodeUtilization;
} rdm_HpnaDiagPerfMonitorNodesNode_t;

typedef struct rdm_HpnaDiagPerfMonitorChannels_s {   // RDM_OID_HPNA_DIAG_PERF_MONITOR_CHANNELS 
	char TimeStamp[32];
	uint32_t ChannelNumberOfEntries;
} rdm_HpnaDiagPerfMonitorChannels_t;

typedef struct rdm_HpnaDiagPerfMonitorChannelsChannel_s {   // RDM_OID_HPNA_DIAG_PERF_MONITOR_CHANNELS_CHANNEL 
	char HostSrcMACAddress[18];
	char HostDestMACAddress[18];
	char HPNASrcMACAddress[18];
	char HPNADestMACAddress[18];
	uint32_t PHYRate;
	uint32_t BaudRate;
	uint32_t SNR;
	uint32_t PacketsSent;
	uint32_t PacketsReceived;
	uint32_t LARQPacketsReceived;
	char FlowSpec[257];
} rdm_HpnaDiagPerfMonitorChannelsChannel_t;

typedef struct rdm_Moca_s {   // RDM_OID_MOCA 
	uint32_t InterfaceNumberOfEntries;
} rdm_Moca_t;

typedef struct rdm_MocaIntf_s {   // RDM_OID_MOCA_INTF 
	bool Enable;
	char Status[17];
	char Alias[65];
	uint32_t LastChange;
	char LowerLayers[1025];
	bool Upstream;
	char MACAddress[18];
	char FirmwareVersion[65];
	uint32_t MaxBitRate;
	uint32_t MaxIngressBW;
	uint32_t MaxEgressBW;
	char HighestVersion[65];
	char CurrentVersion[65];
	uint32_t NetworkCoordinator;
	uint32_t NodeID;
	bool MaxNodes;
	bool PreferredNC;
	uint32_t BackupNC;
	bool PrivacyEnabledSetting;
	bool PrivacyEnabled;
	char FreqCapabilityMask[17];
	char FreqCurrentMaskSetting[17];
	char FreqCurrentMask[17];
	uint32_t CurrentOperFreq;
	uint32_t LastOperFreq;
	char KeyPassphrase[18];
	uint32_t TxPowerLimit;
	uint32_t PowerCntlPhyTarget;
	uint32_t BeaconPowerLimit;
	char NetworkTabooMask[17];
	char NodeTabooMask[17];
	uint32_t TxBcastRate;
	uint32_t TxBcastPowerReduction;
	bool QAM256Capable;
	uint32_t PacketAggregationCapability;
	uint32_t AssociatedDeviceNumberOfEntries;
} rdm_MocaIntf_t;

typedef struct rdm_MocaIntfSt_s {   // RDM_OID_MOCA_INTF_ST 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSent;
	uint64_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t ErrorsReceived;
	uint64_t UnicastPacketsSent;
	uint64_t UnicastPacketsReceived;
	uint32_t DiscardPacketsSent;
	uint32_t DiscardPacketsReceived;
	uint64_t MulticastPacketsSent;
	uint64_t MulticastPacketsReceived;
	uint64_t BroadcastPacketsSent;
	uint64_t BroadcastPacketsReceived;
	uint32_t UnknownProtoPacketsReceived;
} rdm_MocaIntfSt_t;

typedef struct rdm_MocaIntfQos_s {   // RDM_OID_MOCA_INTF_QOS 
	uint32_t EgressNumFlows;
	uint32_t IngressNumFlows;
	uint32_t FlowStatsNumberOfEntries;
} rdm_MocaIntfQos_t;

typedef struct rdm_MocaIntfQosFlowSt_s {   // RDM_OID_MOCA_INTF_QOS_FLOW_ST 
	uint32_t FlowID;
	char PacketDA[18];
	uint32_t MaxRate;
	uint32_t MaxBurstSize;
	uint32_t LeaseTimeLeft;
	uint32_t FlowPackets;
} rdm_MocaIntfQosFlowSt_t;

typedef struct rdm_MocaIntfAssocDev_s {   // RDM_OID_MOCA_INTF_ASSOC_DEV 
	char MACAddress[18];
	uint32_t NodeID;
	bool PreferredNC;
	char HighestVersion[65];
	uint32_t PHYTxRate;
	uint32_t PHYRxRate;
	uint32_t TxPowerControlReduction;
	uint32_t RxPowerLevel;
	uint32_t TxBcastRate;
	uint32_t RxBcastPowerLevel;
	uint32_t TxPackets;
	uint32_t RxPackets;
	uint32_t RxErroredAndMissedPackets;
	bool QAM256Capable;
	uint32_t PacketAggregationCapability;
	uint32_t RxSNR;
	bool Active;
} rdm_MocaIntfAssocDev_t;

typedef struct rdm_Ghn_s {   // RDM_OID_GHN 
	uint32_t InterfaceNumberOfEntries;
} rdm_Ghn_t;

typedef struct rdm_GhnIntf_s {   // RDM_OID_GHN_INTF 
	bool Enable;
	char Status[18];
	char Alias[65];
	char Name[65];
	uint32_t LastChange;
	char LowerLayers[1025];
	bool Upstream;
	char MACAddress[18];
	char FirmwareVersion[65];
	char ConnectionType[10];
	char TargetDomainNames[1025];
	char DomainName[33];
	uint32_t DomainNameIdentifier;
	uint32_t DomainId;
	uint32_t DeviceId;
	uint32_t MaxBitRate;
	bool NodeTypeDMCapable;
	bool NodeTypeSCCapable;
	bool NodeTypeDMConfig;
	bool NodeTypeDMStatus;
	bool NodeTypeSCStatus;
	uint32_t AssociatedDeviceNumberOfEntries;
} rdm_GhnIntf_t;

typedef struct rdm_GhnIntfSt_s {   // RDM_OID_GHN_INTF_ST 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSent;
	uint64_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t ErrorsReceived;
	uint64_t UnicastPacketsSent;
	uint64_t UnicastPacketsReceived;
	uint32_t DiscardPacketsSent;
	uint32_t DiscardPacketsReceived;
	uint64_t MulticastPacketsSent;
	uint64_t MulticastPacketsReceived;
	uint64_t BroadicastPacketsSent;
	uint64_t BroadcastPacketsReceived;
	uint32_t UnknownProtoPacketsReceived;
} rdm_GhnIntfSt_t;

typedef struct rdm_GhnIntfAssocDev_s {   // RDM_OID_GHN_INTF_ASSOC_DEV 
	char MACAddress[18];
	uint32_t DeviceId;
	uint32_t TxPhyRate;
	uint32_t RxPhyRate;
	bool Active;
} rdm_GhnIntfAssocDev_t;

typedef struct rdm_HomePlug_s {   // RDM_OID_HOME_PLUG 
	uint32_t InterfaceNumberOfEntries;
} rdm_HomePlug_t;

typedef struct rdm_HomeplugIntf_s {   // RDM_OID_HOMEPLUG_INTF 
	bool Enable;
	char Status[18];
	char Alias[65];
	char Name[65];
	uint32_t LastChange;
	char LowerLayers[1025];
	bool Upstream;
	char MACAddress[18];
	char LogicalNetwork[65];
	char Version[17];
	char FirmwareVersion[65];
	bool ForceCCo;
	char NetworkPassword[33];
	char OtherNetworksPresent[65];
	uint32_t MaxBitRate;
	uint32_t AssociatedDeviceNumberOfEntries;
} rdm_HomeplugIntf_t;

typedef struct rdm_HomeplugIntfSt_s {   // RDM_OID_HOMEPLUG_INTF_ST 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSent;
	uint64_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t ErrorsReceived;
	uint64_t UnicastPacketsSent;
	uint64_t UnicastPacketsReceived;
	uint32_t DiscardPacketsSent;
	uint32_t DiscardPacketsReceived;
	uint64_t MulticastPacketsSent;
	uint64_t MulticastPacketsReceived;
	uint64_t BroadicastPacketsSent;
	uint64_t BroadcastPacketsReceived;
	uint32_t UnknownProtoPacketsReceived;
	uint64_t MPDUTxAck;
	uint64_t MPDUTxCol;
	uint64_t MPDUTxFailed;
	uint64_t MPDURxAck;
	uint64_t MPDURxFailed;
} rdm_HomeplugIntfSt_t;

typedef struct rdm_HomeplugIntfAssocDev_s {   // RDM_OID_HOMEPLUG_INTF_ASSOC_DEV 
	char MACAdress[18];
	uint32_t TxPhyRate;
	uint32_t RxPhyRate;
	char SNRPerTone[2049];
	uint32_t AvgAttenuation;
	char EndStationMACs[18];
	bool Active;
} rdm_HomeplugIntfAssocDev_t;

typedef struct rdm_Upa_s {   // RDM_OID_UPA 
	uint32_t InterfaceNumberOfEntries;
} rdm_Upa_t;

typedef struct rdm_UpaIntf_s {   // RDM_OID_UPA_INTF 
	bool Enable;
	char Status[18];
	char Alias[65];
	char Name[65];
	uint32_t LastChange;
	char LowerLayers[1025];
	bool Upstream;
	char MACAddress[18];
	char FirmwareVersion[65];
	uint32_t MaxBitRate;
	char NodeType[3];
	char LogicalNetwork[21];
	char EncryptionMethod[7];
	char EncryptionKey[37];
	bool PowerBackoffEnabled;
	bool PowerBackoffMechanismActive;
	uint32_t EstApplicationThroughput;
	bool ActiveNotchEnable;
	uint32_t ActiveNotchNumberOfEntries;
	uint32_t AssociatedDeviceNumberOfEntries;
	uint32_t BridgeForNumberOfEntries;
} rdm_UpaIntf_t;

typedef struct rdm_UpaIntfSt_s {   // RDM_OID_UPA_INTF_ST 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSent;
	uint64_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t ErrorsReceived;
	uint64_t UnicastPacketsSent;
	uint64_t UnicastPacketsReceived;
	uint32_t DiscardPacketsSent;
	uint32_t DiscardPacketsReceived;
	uint64_t MulticastPacketsSent;
	uint64_t MulticastPacketsReceived;
	uint64_t BroadicastPacketsSent;
	uint64_t BroadcastPacketsReceived;
	uint32_t UnknownProtoPacketsReceived;
} rdm_UpaIntfSt_t;

typedef struct rdm_UpaIntfAssocDev_s {   // RDM_OID_UPA_INTF_ASSOC_DEV 
	char MACAddress[18];
	uint32_t Port;
	char LogicalNetwork[21];
	uint32_t PhyTxThroughput;
	uint32_t PhyRxThroughput;
	uint32_t RealPhyRxThroughput;
	uint32_t EstimatedPLR;
	uint32_t MeanEstimatedAtt;
	char SmartRouteIntermediatePLCMAC[18];
	bool DirectRoute;
	bool Active;
} rdm_UpaIntfAssocDev_t;

typedef struct rdm_UpaIntfActiveNotch_s {   // RDM_OID_UPA_INTF_ACTIVE_NOTCH 
	bool Enable;
	char Alias[65];
	uint32_t StartFreq;
	uint32_t StopFreq;
	uint32_t Depth;
} rdm_UpaIntfActiveNotch_t;

typedef struct rdm_UpaIntfBridgeFor_s {   // RDM_OID_UPA_INTF_BRIDGE_FOR 
	char Alias[65];
	char MACAddress[18];
	uint32_t Port;
} rdm_UpaIntfBridgeFor_t;

typedef struct rdm_UpaDiag_s {   // RDM_OID_UPA_DIAG 
} rdm_UpaDiag_t;

typedef struct rdm_UpaDiagIntfMeasurement_s {   // RDM_OID_UPA_DIAG_INTF_MEASUREMENT 
	char DiagnosticsState[18];
	char Type[4];
	char Interface[257];
	uint32_t Port;
	char Measurements[3073];
	int RxGain;
} rdm_UpaDiagIntfMeasurement_t;

typedef struct rdm_Wifi_s {   // RDM_OID_WIFI 
	uint32_t RadioNumberOfEntries;
	uint32_t SSIDNumberOfEntries;
	uint32_t AccessPointNumberOfEntries;
	uint32_t EndPointNumberOfEntries;
	char X_ZYXEL_SSIDType[5];
	uint32_t X_ZYXEL_SSIDStartMacSeq;
	uint32_t X_ZYXEL_WpsBut_Event;
} rdm_Wifi_t;

typedef struct rdm_WifiOneSsid_s {   // RDM_OID_WIFI_ONE_SSID 
	bool Enable;
} rdm_WifiOneSsid_t;

typedef struct rdm_WifiRadio_s {   // RDM_OID_WIFI_RADIO 
	bool Enable;
	char Status[18];
	char Alias[65];
	char Name[65];
	uint32_t LastChange;
	char LowerLayers[1025];
	bool Upstream;
	uint32_t MaxBitRate;
	char SupportedFrequencyBands[7];
	char OperatingFrequencyBand[9];
	char SupportedStandards[17];
	char OperatingStandards[17];
	char PossibleChannels[1025];
	char ChannelsInUse[1025];
	uint32_t Channel;
	bool AutoChannelSupported;
	bool AutoChannelEnable;
	uint32_t AutoChannelRefreshPeriod;
	char OperatingChannelBandwidth[18];
	char ExtensionChannel[20];
	char GuardInterval[8];
	int MCS;
	char TransmitPowerSupported[65];
	int TransmitPower;
	bool IEEE80211hSupported;
	bool EEE80211hEnabled;
	char RegulatoryDomain[4];
	char BasicDataTransmitRates[257];
	char OperationalDataTransmitRates[257];
	char SupportedDataTransmitRates[257];
	char X_ZYXEL_Auto_Channel_Skip[101];
	char X_ZYXEL_CountryCode[129];
	uint32_t X_ZYXEL_AutoChannel_Policy;
	uint32_t X_ZYXEL_RTS_CTS_Threshold;
	uint32_t X_ZYXEL_Fragment_Threshold;
	uint32_t X_ZYXEL_Beacon_Interval;
	uint32_t X_ZYXEL_DTIM_Interval;
	char X_ZYXEL_Wireless_Mode[17];
	char X_ZYXEL_ChanimStats[257];
	bool X_ZYXEL_Protection;
	char X_ZYXEL_Preamble[9];
	bool X_ZYXEL_RIFS_Advertisement;
	int X_ZYXEL_Rxchain_Pwrsave_Enable;
	int X_ZYXEL_Rxchain_Pwrsave_Quiet_Time;
	int X_ZYXEL_Rxchain_Pwrsave_Pps;
	int X_ZYXEL_Radio_Pwrsave_Enable;
	int X_ZYXEL_Radio_Pwrsave_Quiet_Time;
	int X_ZYXEL_Radio_Pwrsave_Pps;
	int X_ZYXEL_Radio_Pwrsave_Level;
	bool X_ZYXEL_Frameburst;
	char X_ZYXEL_UpperChannels[513];
	char X_ZYXEL_LowerChannels[513];
	char X_ZYXEL_AC80_Channels[513];
	char X_ZYXEL_AX160_Channels[513];
	int X_ZYXEL_RegMode;
	char X_ZYXEL_IfName[19];
	int X_ZYXEL_DfsPreIsm;
	int X_ZYXEL_DfsPostIsm;
	bool X_ZYXEL_OBSS_coex;
	int X_ZYXEL_TpcDb;
	char X_ZYXEL_WlMode[13];
	int X_ZYXEL_LazyWds;
	char X_ZYXEL_WdsMacList[81];
	bool X_ZYXEL_AP_AutoConfig;
	int X_ZYXEL_Interference_Override;
	char X_ZYXEL_InActiveChannels[129];
	bool X_ZYXEL_AirtimeFairness;
	bool X_ZYXEL_Support_ATF;
	char X_ZYXEL_SingleSKU[9];
	char X_ZYXEL_MaxBitRate[7];
	bool X_ZYXEL_SSID_Priority_Enable;
	char X_ZYXEL_Manual_Channels_Skip[129];
	bool X_ZYXEL_MU_MIMO_Enabled;
} rdm_WifiRadio_t;

typedef struct rdm_WifiRadioSt_s {   // RDM_OID_WIFI_RADIO_ST 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSent;
	uint64_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t ErrorsReceived;
	uint32_t DiscardPacketsSent;
	uint32_t DiscardPacketsReceived;
	char X_ZYXEL_Rate[17];
} rdm_WifiRadioSt_t;

typedef struct rdm_WifiSsid_s {   // RDM_OID_WIFI_SSID 
	bool Enable;
	char Status[18];
	char Alias[65];
	char Name[65];
	uint32_t LastChange;
	char LowerLayers[1025];
	char BSSID[18];
	char MACAddress[18];
	char SSID[33];
	bool X_ZYXEL_Multicast_Fwd;
	uint32_t X_ZYXEL_UpstreamRate;
	uint32_t X_ZYXEL_DownstreamRate;
	char X_ZYXEL_SSIDPrefix[33];
	uint32_t X_ZYXEL_SuffixLength;
	bool X_ZYXEL_SSIDSuffixEnable;
	char X_ZYXEL_SSIDSuffix[33];
	bool X_ZYXEL_MainSSID;
	char X_ZYXEL_GuestAPs[257];
	uint8_t X_ZYXEL_Attribute;
	uint32_t X_ZYXEL_GuestEnableTime;
	bool X_ZYXEL_MasterMain;
	bool X_ZYXEL_MasterGuest;
	bool X_ZYXEL_Autoconfig;
	char X_ZYXEL_MasterMainSSID[33];
	char X_ZYXEL_MasterMainPassword[64];
	char X_ZYXEL_MasterGuestSSID[33];
	char X_ZYXEL_MasterGuestPassword[64];
	uint32_t X_ZYXEL_SSID_Priority;
} rdm_WifiSsid_t;

typedef struct rdm_WifiSsidStat_s {   // RDM_OID_WIFI_SSID_STAT 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSent;
	uint64_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t ErrorsReceived;
	uint64_t UnicastPacketsSent;
	uint64_t UnicastPacketsReceived;
	uint32_t DiscardPacketsSent;
	uint32_t DiscardPacketsReceived;
	uint64_t MulticastPacketsSent;
	uint64_t MulticastPacketsReceived;
	uint64_t BroadcastPacketsSent;
	uint64_t BroadcastPacketsReceived;
	uint32_t UnknownProtoPacketsReceived;
} rdm_WifiSsidStat_t;

typedef struct rdm_WifiAccessPoint_s {   // RDM_OID_WIFI_ACCESS_POINT 
	bool Enable;
	char Status[20];
	char Alias[65];
	char SSIDReference[257];
	bool SSIDAdvertisementEnabled;
	uint32_t RetryLimit;
	bool WMMCapability;
	bool UAPSDCapability;
	bool WMMEnable;
	bool UAPSDEnable;
	uint32_t AssociatedDeviceNumberOfEntries;
	uint32_t MaxAssociatedDevices;
	bool IsolationEnable;
	bool X_ZYXEL_BssIdIsolation;
} rdm_WifiAccessPoint_t;

typedef struct rdm_WifiAccessPointSec_s {   // RDM_OID_WIFI_ACCESS_POINT_SEC 
	bool Reset;
	char ModesSupported[201];
	char ModeEnabled[25];
	char WEPKey[27];
	char X_ZYXEL_WEPKey2[27];
	char X_ZYXEL_WEPKey3[27];
	char X_ZYXEL_WEPKey4[27];
	char X_ZYXEL_WEP64Key1[11];
	char X_ZYXEL_WEP64Key2[11];
	char X_ZYXEL_WEP64Key3[11];
	char X_ZYXEL_WEP64Key4[11];
	uint32_t X_ZYXEL_DefaultKeyID;
	char X_ZYXEL_WepModeSelect[31];
	char PreSharedKey[66];
	char KeyPassphrase[64];
	char X_HAWATEL_WifiKey[64];
	uint32_t RekeyingInterval;
	char RadiusServerIPAddr[46];
	char SecondaryRadiusServerIPAddr[46];
	uint32_t RadiusServerPort;
	uint32_t SecondaryRadiusServerPort;
	char RadiusSecret[129];
	char SecondaryRadiusSecret[129];
	bool EnableManagementFrameProtection;
	uint32_t X_ZYXEL_PmfMethod;
	bool X_ZYXEL_AutoGenPSK;
	char X_ZYXEL_Auto_PSK[66];
	uint32_t X_ZYXEL_Auto_PSK_Length;
	uint32_t X_ZYXEL_AutoGenPSK_algorithm;
	bool X_ZYXEL_AutoGenWepKey;
	char X_ZYXEL_Auto_WepKey26[33];
	char X_ZYXEL_Auto_WepKey10[17];
	uint32_t X_ZYXEL_PassphraseType;
	char X_ZYXEL_WEPAuthentication[26];
	char X_ZYXEL_WEPEncryption[21];
	char X_ZYXEL_WPAAuthentication[21];
	char X_ZYXEL_11iAuthentication[21];
	char X_ZYXEL_Encryption[9];
	char X_ZYXEL_WPAEncryption[26];
	char X_ZYXEL_11iEncryption[26];
	bool X_ZYXEL_Preauth;
	uint32_t X_ZYXEL_ReauthInterval;
} rdm_WifiAccessPointSec_t;

typedef struct rdm_WifiAccessPointAccounting_s {   // RDM_OID_WIFI_ACCESS_POINT_ACCOUNTING 
	bool Enable;
	char ServerIPAddr[46];
	char SecondaryServerIPAddr[46];
	uint32_t ServerPort;
	uint32_t SecondaryServerPort;
	char Secret[129];
	char SecondarySecret[129];
	uint32_t InterimInterval;
} rdm_WifiAccessPointAccounting_t;

typedef struct rdm_WifiAccessPointWps_s {   // RDM_OID_WIFI_ACCESS_POINT_WPS 
	bool Enable;
	char ConfigMethodsSupported[65];
	char ConfigMethodsEnabled[256];
	bool X_ZYXEL_WPS_Configured;
	char X_ZYXEL_WPS_Method[11];
	char X_ZYXEL_WPS_StationPin[11];
	char X_ZYXEL_WPS_UUID[37];
	bool X_ZYXEL_WPS_GenDevicePin;
	char X_ZYXEL_WPS_DevicePin[11];
	bool X_ZYXEL_WPS_V2;
	bool X_ZYXEL_WPS_EnablePBC;
	bool X_ZYXEL_WPS_EnableStaPin;
	bool X_ZYXEL_WPS_EnableAPPin;
	char X_ZYXEL_WPS_PairingID[257];
	char X_ZYXEL_WPS_PairingID_Mode[7];
	bool X_ZyXEL_TriggerWPSPushButton;
	char X_ZYXEL_WPSRunningStatus[257];
} rdm_WifiAccessPointWps_t;

typedef struct rdm_WifiAccessPointAssocDev_s {   // RDM_OID_WIFI_ACCESS_POINT_ASSOC_DEV 
	char MACAddress[18];
	char OperatingStandard[13];
	bool AuthenticationState;
	uint32_t LastDataDownlinkRate;
	uint32_t LastDataUplinkRate;
	int SignalStrength;
	uint32_t Retransmissions;
	int X_ZYXEL_SNR;
	int X_ZYXEL_SNRLevel;
	bool Active;
} rdm_WifiAccessPointAssocDev_t;

typedef struct rdm_WifiAccessPointAssocDevSt_s {   // RDM_OID_WIFI_ACCESS_POINT_ASSOC_DEV_ST 
	uint32_t BytesSent;
	uint32_t BytesReceived;
	uint32_t PacketsSent;
	uint32_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t RetransCount;
	uint32_t FailedRetransCount;
	uint32_t RetryCount;
	uint32_t MultipleRetryCount;
} rdm_WifiAccessPointAssocDevSt_t;

typedef struct rdm_WifiStaFilter_s {   // RDM_OID_WIFI_STA_FILTER 
	uint32_t FilterMode;
	char FilterLists[501];
} rdm_WifiStaFilter_t;

typedef struct rdm_WifiEndPoint_s {   // RDM_OID_WIFI_END_POINT 
	bool Enable;
	char Status[20];
	char Alias[65];
	char ProfileReference[257];
	char SSIDReference[257];
	uint32_t ProfileNumberOfEntries;
} rdm_WifiEndPoint_t;

typedef struct rdm_WifiEndPointSt_s {   // RDM_OID_WIFI_END_POINT_ST 
	uint32_t LastDataDownlinkRate;
	uint32_t LastDataUplinkRate;
	uint32_t SignalStrength;
	uint32_t Retransmissions;
} rdm_WifiEndPointSt_t;

typedef struct rdm_WifiEndPointSec_s {   // RDM_OID_WIFI_END_POINT_SEC 
	char ModesSupported[20];
} rdm_WifiEndPointSec_t;

typedef struct rdm_WifiEndPointProfile_s {   // RDM_OID_WIFI_END_POINT_PROFILE 
	bool Enable;
	char Status[17];
	char Alias[65];
	char SSID[33];
	char Location[37];
	uint32_t Priority;
} rdm_WifiEndPointProfile_t;

typedef struct rdm_WifiEndPointProfileSec_s {   // RDM_OID_WIFI_END_POINT_PROFILE_SEC 
	char ModeEnabled[25];
	char WEPKey[14];
	char PreSharedKey[33];
	char KeyPassphrase[64];
} rdm_WifiEndPointProfileSec_t;

typedef struct rdm_Wps_s {   // RDM_OID_WPS 
	bool Enable;
	char ConfigMethodsSupported[65];
	char ConfigMethodsEnabled[256];
} rdm_Wps_t;

typedef struct rdm_WifiDiagnostic_s {   // RDM_OID_WIFI_DIAGNOSTIC 
	char DiagnosticsState[25];
	uint32_t ResultNumberOfEntries;
	char X_ZYXEL_Creator[23];
} rdm_WifiDiagnostic_t;

typedef struct rdm_WifiDiagnosticResults_s {   // RDM_OID_WIFI_DIAGNOSTIC_RESULTS 
	char Radio[51];
	char SSID[33];
	char BSSID[18];
	char Mode[17];
	uint32_t Channel;
	int SignalStrength;
	char SecurityModeEnabled[33];
	char EncryptionMode[9];
	char OperatingFrequencyBand[9];
	char SupportedStandards[13];
	char OperatingStandards[13];
	char OperatingChannelBandwidth[13];
	uint32_t BeaconPeriod;
	int Noise;
	char BasicDataTransferRates[257];
	char SupportedDataTransferRates[257];
	uint32_t DTIMPeriod;
} rdm_WifiDiagnosticResults_t;

typedef struct rdm_WifiApSteering_s {   // RDM_OID_WIFI_AP_STEERING 
	bool Enable;
	uint32_t WiFi_24G_NormalToBad_Threshold;
	uint32_t WiFi_24G_NormalToGood_Threshold;
	uint32_t WiFi_24G_Upgrade_Threshold;
	uint32_t WiFi_5G_NormalToBad_Threshold;
	uint32_t WiFi_5G_NormalToGood_Threshold;
	uint32_t RE_Threshold_Adjustment;
	uint32_t Idle_Pkt_Threshold;
	uint32_t STA_Num_Difference_Threshold;
	uint32_t SteeringTime;
	uint32_t ProhibitAfterSteering;
	uint32_t ClearSteeringStatus;
	uint32_t ScanOtherAPsInterval;
	uint32_t LoadBalancingInterval;
	uint32_t LogLevel;
	bool Prohibit_Steering_OverWDS_AP;
	bool DisableSteering;
} rdm_WifiApSteering_t;

typedef struct rdm_WlanScheduler_s {   // RDM_OID_WLAN_SCHEDULER 
	bool Enable;
	char Name[33];
	char Description[257];
	char SSID[257];
	uint32_t Interface;
	uint32_t Days;
	char TimeStartDate[17];
	uint32_t TimeStartHour;
	uint32_t TimeStartMin;
	char TimeStopDate[17];
	uint32_t TimeStopHour;
	uint32_t TimeStopMin;
} rdm_WlanScheduler_t;

typedef struct rdm_Bridging_s {   // RDM_OID_BRIDGING 
	uint32_t MaxBridgeEntries;
	uint32_t MaxDBridgeEntries;
	uint32_t MaxQBridgeEntries;
	uint32_t MaxVLANEntries;
	uint32_t MaxFilterEntries;
	uint32_t BridgeNumberOfEntries;
	uint32_t FilterNumberOfEntries;
	uint32_t X_ZYXEL_MaxMarkingEntries;
	uint32_t X_ZYXEL_MarkingNumberOfEntries;
	uint32_t X_ZYXEL_AvailableInterfaceNumberOfEntries;
} rdm_Bridging_t;

typedef struct rdm_BridgingBr_s {   // RDM_OID_BRIDGING_BR 
	bool Enable;
	char Status[9];
	char Alias[65];
	char Standard[13];
	uint32_t PortNumberOfEntries;
	uint32_t VLANNumberOfEntries;
	uint32_t VLANPortNumberOfEntries;
	char X_ZYXEL_BridgeName[33];
	uint32_t X_ZYXEL_VLANID;
	uint32_t X_ZYXEL_ConcurrentWan;
	bool X_ZYXEL_BridgeClear;
	char X_ZXYEL_MacLearningIfaces[1057];
} rdm_BridgingBr_t;

typedef struct rdm_BridgingBrPort_s {   // RDM_OID_BRIDGING_BR_PORT 
	bool Enable;
	char Status[17];
	char Alias[65];
	char Name[65];
	uint32_t LastChange;
	char LowerLayers[1025];
	bool ManagementPort;
	uint32_t DefaultUserPriority;
	char PriorityRegeneration[16];
	char PortState[11];
	int PVID;
	char AcceptableFrameTypes[25];
	bool IngressFiltering;
	bool PriorityTagging;
	uint32_t X_ZYXEL_AvailableInterfaceKey;
	uint32_t X_ZYXEL_DoNotSwitchBridge;
	char X_ZYXEL_InterfaceType[33];
	char X_ZYXEL_IfName[19];
} rdm_BridgingBrPort_t;

typedef struct rdm_BridgingBrPortSt_s {   // RDM_OID_BRIDGING_BR_PORT_ST 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSent;
	uint64_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t ErrorsReceived;
	uint64_t UnicastPacketsSent;
	uint64_t UnicastPacketsReceived;
	uint32_t DiscardPacketsSent;
	uint32_t DiscardPacketsReceived;
	uint64_t MulticastPacketsSent;
	uint64_t MulticastPacketsReceived;
	uint64_t BroadcastPacketsSent;
	uint64_t BroadcastPacketsReceived;
	uint32_t UnknownProtoPacketsReceived;
} rdm_BridgingBrPortSt_t;

typedef struct rdm_BridgingBrVlan_s {   // RDM_OID_BRIDGING_BR_VLAN 
	bool Enable;
	char Alias[65];
	char Name[65];
	int VLANID;
} rdm_BridgingBrVlan_t;

typedef struct rdm_BridgingBrVlanport_s {   // RDM_OID_BRIDGING_BR_VLANPORT 
	bool Enable;
	char Alias[65];
	char VLAN[257];
	char Port[257];
	bool Untagged;
} rdm_BridgingBrVlanport_t;

typedef struct rdm_BridgingFilter_s {   // RDM_OID_BRIDGING_FILTER 
	bool Enable;
	char Alias[65];
	char Status[21];
	char Bridge[257];
	uint32_t Order;
	char Interface[257];
	char DHCPType[7];
	uint32_t VLANIDFilter;
	char EthertypeFilterList[257];
	bool EthertypeFilterExclude;
	char SourceMACAddressFilterList[513];
	bool SourceMACAddressFilterExclude;
	char DestMACAddressFilterList[513];
	bool DestMACAddressFilterExclude;
	char SourceMACFromVendorClassIDFilter[256];
	char SourceMACFromVendorClassIDFilterv6[5];
	bool SourceMACFromVendorClassIDFilterExclude;
	char SourceMACFromVendorClassIDMode[11];
	char DestMACFromVendorClassIDFilter[256];
	char DestMACFromVendorClassIDFilterv6[5];
	bool DestMACFromVendorClassIDFilterExclude;
	char DestMACFromVendorClassIDMode[11];
	char SourceMACFromClientIDFilter[256];
	bool SourceMACFromClientIDFilterExclude;
	char DestMACFromClientIDFilter[5];
	bool DestMACFromClientIDFilterExclude;
	char SourceMACFromUserClassIDFilter[5];
	bool SourceMACFromUserClassIDFilterExclude;
	char DestMACFromUserClassIDFilter[5];
	bool DestMACFromUserClassIDFilterExclude;
	char X_ZYXEL_SourceMACFromVSIFilter[256];
	char X_ZYXEL_PreIfaceGroup[129];
	bool X_ZYXEL_Enable_Criteria;
} rdm_BridgingFilter_t;

typedef struct rdm_Ppp_s {   // RDM_OID_PPP 
	uint32_t InterfaceNumberOfEntries;
	char SupportedNCPs[33];
} rdm_Ppp_t;

typedef struct rdm_PppIface_s {   // RDM_OID_PPP_IFACE 
	bool Enable;
	char Status[17];
	char Alias[65];
	char Name[65];
	uint32_t LastChange;
	char LowerLayers[1025];
	bool Reset;
	char ConnectionStatus[21];
	char LastConnectionError[33];
	uint32_t AutoDisconnectTime;
	uint32_t IdleDisconnectTime;
	uint32_t WarnDisconnectDelay;
	char Username[65];
	char Password[65];
	char EncryptionProtocol[5];
	char CompressionProtocol[13];
	char AuthenticationProtocol[9];
	uint32_t MaxMRUSize;
	uint32_t CurrentMRUSize;
	char ConnectionTrigger[9];
	uint32_t LCPEcho;
	uint32_t LCPEchoRetry;
	bool IPCPEnable;
	bool IPv6CPEnable;
	char X_ZYXEL_IfName[19];
	char X_ZYXEL_BaseIfName[19];
	int X_ZYXEL_ConnectionId;
	uint32_t X_ZYXEL_IPR2_MARKING;
	char X_ZYXEL_PppdPidFileName[33];
	char X_ZYXEL_PossibleConnectionTypes[37];
	char X_ZYXEL_ConnectionType[19];
	char X_ZYXEL_AuthenticationProtocol[13];
	uint32_t X_ZYXEL_LastConnectionUpTime;
	uint32_t X_ZYXEL_LastChangeTime;
	char X_ZYXEL_LocalIPAddress[65];
	uint32_t X_ZYXEL_PPPConnRetryInterval;
	uint32_t X_ZYXEL_LCPEcho;
	uint32_t X_ZYXEL_LCPEchoRetry;
} rdm_PppIface_t;

typedef struct rdm_PppIfacePppoa_s {   // RDM_OID_PPP_IFACE_PPPOA 
} rdm_PppIfacePppoa_t;

typedef struct rdm_PppIfacePppoe_s {   // RDM_OID_PPP_IFACE_PPPOE 
	uint32_t SessionID;
	char ACName[257];
	char ServiceName[257];
	char X_ZYXEL_SessionID[33];
} rdm_PppIfacePppoe_t;

typedef struct rdm_PppIfaceIpcp_s {   // RDM_OID_PPP_IFACE_IPCP 
	char LocalIPAddress[16];
	char RemoteIPAddress[16];
	char DNSServers[257];
	bool PassthroughEnable;
	char PassthroughDHCPPool[257];
} rdm_PppIfaceIpcp_t;

typedef struct rdm_PppIntfIpv6cp_s {   // RDM_OID_PPP_INTF_IPV6CP 
	char LocalInterfaceIdentifier[46];
	char RemoteInterfaceIdentifier[46];
} rdm_PppIntfIpv6cp_t;

typedef struct rdm_PppIfaceStat_s {   // RDM_OID_PPP_IFACE_STAT 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSent;
	uint64_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t ErrorsReceived;
	uint64_t UnicastPacketsSent;
	uint64_t UnicastPacketsReceived;
	uint32_t DiscardPacketsSent;
	uint32_t DiscardPacketsReceived;
	uint64_t MulticastPacketsSent;
	uint64_t MulticastPacketsReceived;
	uint64_t BroadcastPacketsSent;
	uint64_t BroadcastPacketsReceived;
	uint32_t UnknownProtoPacketsReceived;
} rdm_PppIfaceStat_t;

typedef struct rdm_Ip_s {   // RDM_OID_IP 
	bool IPv4Capable;
	bool IPv4Enable;
	char IPv4Status[11];
	bool IPv6Capable;
	bool IPv6Enable;
	char IPv6Status[11];
	char ULAPrefix[49];
	uint32_t InterfaceNumberOfEntries;
	uint32_t ActivePortNumberOfEntries;
} rdm_Ip_t;

typedef struct rdm_IpIface_s {   // RDM_OID_IP_IFACE 
	bool Enable;
	bool IPv4Enable;
	bool IPv6Enable;
	bool ULAEnable;
	char Status[17];
	char Alias[65];
	char Name[65];
	uint32_t LastChange;
	char LowerLayers[1025];
	char Router[257];
	bool Reset;
	uint32_t MaxMTUSize;
	char Type[11];
	bool Loopback;
	uint32_t IPv4AddressNumberOfEntries;
	uint32_t IPv6AddressNumberOfEntries;
	uint32_t IPv6PrefixNumberOfEntries;
	bool AutoIPEnable;
	uint32_t X_ZYXEL_UpTime;
	uint32_t X_ZYXEL_LastChangeTime;
	uint32_t X_ZYXEL_WANIPConnectionTime;
	char X_ZYXEL_PossibleConnectionTypes[37];
	uint32_t X_ZYXEL_PortMappingNumberOfEntries;
	char X_ZYXEL_ConnectionType[19];
	char X_ZYXEL_IfName[19];
	bool X_ZYXEL_DefaultGatewayIface;
	int X_ZYXEL_ConnectionId;
	uint32_t X_ZYXEL_IPR2_MARKING;
	char X_ZYXEL_Group_WAN_IpIface[1025];
	bool X_ZYXEL_Enable_6RD;
	bool X_ZYXEL_6RD_Assigned;
	uint32_t X_ZYXEL_6RD_LeaseTime;
	char X_ZYXEL_6RD_Type[9];
	char X_ZYXEL_BorderRelayIPv4Addresses[73];
	bool X_ZYXEL_AllTrafficToBorderRelay;
	char X_ZYXEL_SPIPv6Prefix[65];
	char X_ZYXEL_IPv6Prefix[65];
	char X_ZYXEL_IPv6LocalAddress[129];
	char X_ZYXEL_IPv6Origin[65];
	char X_ZYXEL_IPv6PrefixDelegateWAN[65];
	uint32_t X_ZYXEL_IPv4MaskLength;
	bool X_ZYXEL_Enable_DSLite;
	uint32_t X_ZYXEL_AdvManagedFlag;
	uint32_t X_ZYXEL_AdvOtherConfigFlag;
	bool X_ZYXEL_AdvManagedFlag_Manual;
	bool X_ZYXEL_AdvOtherConfigFlag_Manual;
	char X_ZYXEL_DSLiteRelayIPv6Addresses[73];
	char X_ZYXEL_DSLite_Type[9];
	char X_ZYXEL_SrvName[33];
	int X_ZYXEL_SipPriority;
	char X_ZYXEL_IPv6IdentifierType[17];
	char X_ZYXEL_IPv6Identifier[33];
	uint32_t X_ZYXEL_ConcurrentWan;
	bool X_ZYXEL_PubLan;
	char X_ZYXEL_PubLan_IP[16];
	char X_ZYXEL_PubLan_Mask[16];
	bool X_ZYXEL_PubLan_DHCP;
	bool X_ZYXEL_PubLan_ARP;
	bool X_ZYXEL_Enable_Firewall;
	char X_ZYXEL_AccessDescription[257];
	bool X_ZYXEL_Global_IPv6Enable;
} rdm_IpIface_t;

typedef struct rdm_IpIfaceV4Addr_s {   // RDM_OID_IP_IFACE_V4_ADDR 
	bool Enable;
	char Status[25];
	char Alias[65];
	char IPAddress[16];
	char SubnetMask[16];
	char AddressingType[7];
	char X_ZYXEL_IfName[19];
	bool X_ZYXEL_Alias;
	char X_ZYXEL_Dhcp4Subnet_Ref[257];
} rdm_IpIfaceV4Addr_t;

typedef struct rdm_IpIfaceV6Addr_s {   // RDM_OID_IP_IFACE_V6_ADDR 
	bool Enable;
	char Status[25];
	char IPAddressStatus[17];
	char Alias[65];
	char IPAddress[49];
	char Origin[25];
	char Prefix[33];
	char PreferredLifetime[32];
	char ValidLifetime[32];
	bool Anycast;
	char X_ZYXEL_LinkLocalAddrType[25];
	uint32_t X_ZYXEL_PreferredLifetime;
	uint32_t X_ZYXEL_ValidLifetime;
	uint32_t X_ZYXEL_CurrentTime;
} rdm_IpIfaceV6Addr_t;

typedef struct rdm_IpIfaceV6Prefix_s {   // RDM_OID_IP_IFACE_V6_PREFIX 
	bool Enable;
	char Status[25];
	char PrefixStatus[17];
	char Alias[65];
	char Prefix[25];
	char Origin[25];
	char StaticType[25];
	char ParentPrefix[33];
	char ChildPrefixBits[25];
	bool OnLink;
	bool Autonomous;
	char PreferredLifetime[32];
	char ValidLifetime[32];
	uint32_t X_ZYXEL_PreferredLifetime;
	uint32_t X_ZYXEL_ValidLifetime;
	char X_ZYXEL_RouteInfoPrefixes[129];
	uint32_t X_ZYXEL_CurrentTime;
} rdm_IpIfaceV6Prefix_t;

typedef struct rdm_IpIfaceStat_s {   // RDM_OID_IP_IFACE_STAT 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSent;
	uint64_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t ErrorsReceived;
	uint64_t UnicastPacketsSent;
	uint64_t UnicastPacketsReceived;
	uint32_t DiscardPacketsSent;
	uint32_t DiscardPacketsReceived;
	uint64_t MulticastPacketsSent;
	uint64_t MulticastPacketsReceived;
	uint64_t BroadcastPacketsSent;
	uint64_t BroadcastPacketsReceived;
	uint32_t UnknownProtoPacketsReceived;
} rdm_IpIfaceStat_t;

typedef struct rdm_IpActivePort_s {   // RDM_OID_IP_ACTIVE_PORT 
	char LocalIPAddress[46];
	uint32_t LocalPort;
	char RemoteIPAddress[46];
	uint32_t RemotePort;
	char Status[13];
} rdm_IpActivePort_t;

typedef struct rdm_IpDiag_s {   // RDM_OID_IP_DIAG 
} rdm_IpDiag_t;

typedef struct rdm_IpDiagIpping_s {   // RDM_OID_IP_DIAG_IPPING 
	char DiagnosticsState[29];
	char Interface[257];
	char ProtocolVersion[17];
	char Host[257];
	uint32_t NumberOfRepetitions;
	uint32_t Timeout;
	uint32_t DataBlockSize;
	uint32_t DSCP;
	uint32_t SuccessCount;
	uint32_t FailureCount;
	uint32_t AverageResponseTime;
	uint32_t MinimumResponseTime;
	uint32_t MaximumResponseTime;
	uint32_t AverageResponseTimeDetailed;
	uint32_t MinimumResponseTimeDetailed;
	uint32_t MaximumResponseTimeDetailed;
	char X_ZYXEL_Creator[23];
} rdm_IpDiagIpping_t;

typedef struct rdm_IpDiagTraceRt_s {   // RDM_OID_IP_DIAG_TRACE_RT 
	char DiagnosticsState[29];
	char Interface[257];
	char ProtocolVersion[17];
	char Host[257];
	uint32_t NumberOfTries;
	uint32_t Timeout;
	uint32_t DataBlockSize;
	uint32_t DSCP;
	uint32_t MaxHopCount;
	uint32_t ResponseTime;
	uint32_t RouteHopsNumberOfEntries;
	char X_ZYXEL_Creator[23];
} rdm_IpDiagTraceRt_t;

typedef struct rdm_IpDiagTracertRtHops_s {   // RDM_OID_IP_DIAG_TRACERT_RT_HOPS 
	char Host[257];
	char HostAddress[25];
	uint32_t ErrorCode;
	char RTTimes[273];
} rdm_IpDiagTracertRtHops_t;

typedef struct rdm_IpDiagDlDiag_s {   // RDM_OID_IP_DIAG_DL_DIAG 
	char DiagnosticsState[29];
	char Interface[257];
	char DownloadURL[257];
	char DownloadTransports[11];
	uint32_t DSCP;
	uint32_t EthernetPriority;
	char ROMTime[32];
	char BOMTime[32];
	char EOMTime[32];
	uint32_t TestBytesReceived;
	uint32_t TotalBytesReceived;
	uint32_t TotalBytesSent;
	char X_ZYXEL_Latency[18];
	uint32_t X_ZYXEL_RoundTripTime;
	char X_ZYXEL_DownloadSpeed[18];
	char TCPOpenRequestTime[32];
	char TCPOpenResponseTime[32];
	char X_ZYXEL_Creator[23];
	uint32_t X_ZYXEL_NumOfThreads;
} rdm_IpDiagDlDiag_t;

typedef struct rdm_IpDiagUlDiag_s {   // RDM_OID_IP_DIAG_UL_DIAG 
	char DiagnosticsState[29];
	char Interface[257];
	char UploadURL[257];
	char UploadTransports[11];
	uint32_t DSCP;
	uint32_t EthernetPriority;
	uint32_t TestFileLength;
	char ROMTime[32];
	char BOMTime[32];
	char EOMTime[32];
	uint32_t TestBytesSent;
	uint32_t TotalBytesReceived;
	uint32_t TotalBytesSent;
	char TCPOpenRequestTime[32];
	char TCPOpenResponseTime[32];
	char X_ZYXEL_Creator[23];
	uint32_t X_ZYXEL_NumOfThreads;
} rdm_IpDiagUlDiag_t;

typedef struct rdm_IpDiagUdpEchoCfg_s {   // RDM_OID_IP_DIAG_UDP_ECHO_CFG 
	bool Enable;
	char Interface[257];
	char SourceIPAddress[46];
	uint32_t UDPPort;
	bool EchoPlusEnabled;
	bool EchoPlusSupported;
	uint32_t PacketsReceived;
	uint32_t PacketsResponded;
	uint32_t BytesReceived;
	uint32_t BytesResponded;
	char TimeFirstPacketReceived[32];
	char TimeLastPacketReceived[32];
} rdm_IpDiagUdpEchoCfg_t;

typedef struct rdm_IpDiagUdpEchoDiag_s {   // RDM_OID_IP_DIAG_UDP_ECHO_DIAG 
	char DiagnosticsState[29];
	char Interface[257];
	char Host[257];
	uint32_t Port;
	uint32_t NumberOfRepetitions;
	uint32_t Timeout;
	uint32_t DataBlockSize;
	uint32_t DSCP;
	uint32_t InterTransmissionTime;
	char ProtocolVersion[9];
	char IPAddressUsed[46];
	uint32_t SuccessCount;
	uint32_t FailureCount;
	uint32_t AverageResponseTime;
	uint32_t MinimumResponseTime;
	uint32_t MaximumResponseTime;
	bool EnableIndividualPacketResults;
	uint32_t IndividualPacketResultNumberOfEntries;
	uint32_t UDPEchoDiagnosticsMaxResults;
	char X_ZYXEL_Creator[23];
} rdm_IpDiagUdpEchoDiag_t;

typedef struct rdm_IpDiagUdpEchoPakRst_s {   // RDM_OID_IP_DIAG_UDP_ECHO_PAK_RST 
	bool PacketSuccess;
	char PacketSendTime[32];
	char PacketReceiveTime[32];
	uint32_t TestGenSN;
	uint32_t TestRespSN;
	uint32_t TestRespRcvTimeStamp;
	uint32_t TestRespReplyTimeStamp;
	uint32_t TestRespReplyFailureCount;
} rdm_IpDiagUdpEchoPakRst_t;

typedef struct rdm_IpDiagSvrSelectDiag_s {   // RDM_OID_IP_DIAG_SVR_SELECT_DIAG 
	char DiagnosticsState[29];
	char Interface[257];
	char ProtocolVersion[9];
	char Protocol[11];
	char HostList[2601];
	uint32_t NumberOfRepetitions;
	uint32_t Timeout;
	char FastestHost[257];
	uint32_t MinimumResponseTime;
	uint32_t AverageResponseTime;
	uint32_t MaximumResponseTime;
	char IPAddressUsed[46];
} rdm_IpDiagSvrSelectDiag_t;

typedef struct rdm_Ipsec_s {   // RDM_OID_IPSEC 
	bool Enable;
	char Status[17];
	bool AHSupported;
	char IKEv2SupportedEncryptionAlgorithms[13];
	char ESPSupportedEncryptionAlgorithms[19];
	char IKEv2SupportedPseudoRandomFunctions[15];
	char SupportedIntegrityAlgorithms[18];
	char SupportedDiffieHellmanGroupTransforms[513];
	uint32_t MaxFilterEntries;
	uint32_t MaxProfileEntries;
	uint32_t FilterNumberOfEntries;
	uint32_t ProfileNumberOfEntries;
	uint32_t TunnelNumberOfEntries;
	uint32_t IKEv2SANumberOfEntries;
	char X_ZYXEL_TunnelPrecedence[4097];
	char X_ZYXEL_WizardTunnel[4097];
	uint32_t X_ZYXEL_IKEDPDTimeout;
	uint32_t X_ZYXEL_IKEDPDRetryLimit;
	bool X_ZYXEL_IgnoreIPv4DF;
} rdm_Ipsec_t;

typedef struct rdm_IpsecStat_s {   // RDM_OID_IPSEC_STAT 
	uint32_t NegotiationFailures;
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint32_t PacketsSent;
	uint32_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t UnknownSPIErrors;
	uint32_t DecryptionErrors;
	uint32_t IntegrityErrors;
	uint32_t ReplayErrors;
	uint32_t PolicyErrors;
	uint32_t OtherReceiveErrors;
} rdm_IpsecStat_t;

typedef struct rdm_IpsecFilter_s {   // RDM_OID_IPSEC_FILTER 
	bool Enable;
	char Status[17];
	uint32_t Order;
	char Alias[65];
	char Interface[257];
	bool AllInterfaces;
	char DestIP[46];
	char DestMask[46];
	bool DestIPExclude;
	char SourceIP[46];
	char SourceMask[46];
	bool SourceIPExclude;
	int Protocol;
	bool ProtocolExclude;
	int DestPort;
	int DestPortRangeMax;
	bool DestPortExclude;
	int SourcePort;
	int SourcePortRangeMax;
	bool SourcePortExclude;
	char ProcessingChoice[8];
	char Profile[65];
	uint32_t X_ZYXEL_Identifier;
	uint32_t X_ZYXEL_IPVersion;
	uint32_t X_ZYXEL_DestIPType;
	char X_ZYXEL_DestIPRangeMax[46];
	uint32_t X_ZYXEL_SourceIPType;
	char X_ZYXEL_SourceIPRangeMax[46];
	uint32_t X_ZYXEL_MyAddressType;
	char X_ZYXEL_MyInterface[16];
	char X_ZYXEL_MyInterfaceUI[33];
	char X_ZYXEL_MyDomainIP[128];
	char X_ZYXEL_MyAddressIP[46];
	uint32_t X_ZYXEL_PeerAddressType;
	char X_ZYXEL_PeerStaticPrimary[128];
	char X_ZYXEL_PeerStaticSecondary[128];
	char X_ZYXEL_PeerIPPrimary[46];
	char X_ZYXEL_PeerIPSecondary[46];
	bool X_ZYXEL_ForceSelfToTunnel;
	bool X_ZYXEL_FullTunnel;
} rdm_IpsecFilter_t;

typedef struct rdm_IpsecProfile_s {   // RDM_OID_IPSEC_PROFILE 
	char Alias[65];
	uint32_t MaxChildSAs;
	char RemoteEndpoints[65];
	uint32_t ForwardingPolicy;
	char Protocol[4];
	char IKEv2AuthenticationMethod[41];
	char IKEv2AllowedEncryptionAlgorithms[193];
	char ESPAllowedEncryptionAlgorithms[433];
	char IKEv2AllowedPseudoRandomFunctions[105];
	char IKEv2AllowedIntegrityAlgorithms[256];
	char AHAllowedIntegrityAlgorithms[256];
	char ESPAllowedIntegrityAlgorithms[433];
	char IKEv2AllowedDiffieHellmanGroupTransforms[325];
	uint32_t IKEv2DeadPeerDetectionTimeout;
	uint32_t IKEv2NATTKeepaliveTimeout;
	uint32_t AntiReplayWindowSize;
	char DoNotFragment[6];
	int DSCPMarkPolicy;
	uint64_t IKEv2SATrafficLimit;
	uint32_t IKEv2SATimeLimit;
	char IKEv2SAExpiryAction[12];
	uint64_t ChildSATrafficLimit;
	uint32_t ChildSATimeLimit;
	char ChildSAExpiryAction[12];
	uint32_t SentCPAttrNumberOfEntries;
	uint32_t X_ZYXEL_IKEVersion;
	uint32_t X_ZYXEL_PeerFallbackInterval;
	uint32_t X_ZYXEL_AuthType;
	uint32_t X_ZYXEL_AuthLocalIDType;
	uint32_t X_ZYXEL_AuthPeerIDType;
	uint32_t X_ZYXEL_IKEv1NegoMethod;
	uint32_t X_ZYXEL_IKEv1XAuthMode;
	uint32_t X_ZYXEL_IKEv2EAPMode;
	uint32_t X_ZYXEL_IKEv2EAPType;
	bool X_ZYXEL_PeerFallback;
	char X_ZYXEL_AuthPreSharedKey[33];
	bool X_ZYXEL_AuthPSKUnmasked;
	char X_ZYXEL_AuthCertificate[64];
	char X_ZYXEL_AuthLocalContent[64];
	char X_ZYXEL_AuthPeerContent[256];
	bool X_ZYXEL_IKEv1NATTSupported;
	bool X_ZYXEL_IKEv1DPDSupported;
	bool X_ZYXEL_IKEv1XAuthSupported;
	char X_ZYXEL_IKEv1XAuthServerAAAMethod[81];
	char X_ZYXEL_IKEv1XAuthClientUser[32];
	char X_ZYXEL_IKEv1XAuthClientPassword[32];
	bool X_ZYXEL_IKEv2EAPSupported;
	char X_ZYXEL_IKEv2EAPServerAAAMethod[81];
	char X_ZYXEL_IKEv2EAPServerAllowedUser[32];
	char X_ZYXEL_IKEv2EAPClientUser[32];
	char X_ZYXEL_IKEv2EAPClientPassword[32];
} rdm_IpsecProfile_t;

typedef struct rdm_IpsecProfileSentCpAttr_s {   // RDM_OID_IPSEC_PROFILE_SENT_CP_ATTR 
	bool Enable;
	char Alias[65];
	uint32_t Type;
	char Value[129];
} rdm_IpsecProfileSentCpAttr_t;

typedef struct rdm_IpsecTunnel_s {   // RDM_OID_IPSEC_TUNNEL 
	char Alias[65];
	char TunnelInterface[25];
	char TunneledInterface[25];
	char Filters[129];
	uint32_t X_ZYXEL_TunnelAction;
	uint32_t X_ZYXEL_TunnelType;
	bool X_ZYXEL_NailedUp;
	bool X_ZYXEL_EnableReplayDetection;
	bool X_ZYXEL_EnableNetBIOS;
	uint32_t X_ZYXEL_MSSAdjustType;
	int X_ZYXEL_MSSAdjustSize;
	bool X_ZYXEL_IKEv2Narrowed;
	uint32_t X_ZYXEL_GatewayMode;
	char X_ZYXEL_TunnelGateway[65];
	bool X_ZYXEL_EnableGRE;
	bool X_ZYXEL_EnablePolicyEnforce;
	uint32_t X_ZYXEL_Encapsulation;
	char X_ZYXEL_Zone[16];
	bool X_ZYXEL_IKEv1ModeConfigSupported;
	bool X_ZYXEL_IKEv2CPSupported;
	bool X_ZYXEL_EnableConnectCheck;
	uint32_t X_ZYXEL_CheckMode;
	int X_ZYXEL_CheckPort;
	uint32_t X_ZYXEL_CheckPeriod;
	uint32_t X_ZYXEL_CheckTimeout;
	uint32_t X_ZYXEL_CheckFailTolerance;
	uint32_t X_ZYXEL_CheckAddressType;
	char X_ZYXEL_CheckAddress[64];
	bool X_ZYXEL_EnableCheckLog;
} rdm_IpsecTunnel_t;

typedef struct rdm_IpsecTunnelStat_s {   // RDM_OID_IPSEC_TUNNEL_STAT 
	uint32_t DecryptionErrors;
	uint32_t IntegrityErrors;
	uint32_t ReplayErrors;
	uint32_t PolicyErrors;
	uint32_t OtherReceiveErrors;
} rdm_IpsecTunnelStat_t;

typedef struct rdm_IpsecIkev2sa_s {   // RDM_OID_IPSEC_IKEV2SA 
	char Status[17];
	char Alias[65];
	char Tunnel[33];
	char LocalAddress[46];
	char RemoteAddress[46];
	char EncryptionAlgorithm[65];
	uint32_t EncryptionKeyLength;
	char PseudoRandomFunction[65];
	char IntegrityAlgorithm[65];
	char DiffieHellmanGroupTransform[65];
	char CreationTime[32];
	uint32_t ReceivedCPAttrNumberOfEntries;
	uint32_t ChildSANumberOfEntriess;
} rdm_IpsecIkev2sa_t;

typedef struct rdm_IpsecIkev2saStat_s {   // RDM_OID_IPSEC_IKEV2SA_STAT 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint32_t PacketsSent;
	uint32_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t DecryptionErrors;
	uint32_t IntegrityErrors;
	uint32_t OtherReceiveErrors;
} rdm_IpsecIkev2saStat_t;

typedef struct rdm_IpsecIkev2saReceivedCpAttr_s {   // RDM_OID_IPSEC_IKEV2SA_RECEIVED_CP_ATTR 
	uint32_t Type;
	char Value[129];
} rdm_IpsecIkev2saReceivedCpAttr_t;

typedef struct rdm_IpsecIkev2saChildSa_s {   // RDM_OID_IPSEC_IKEV2SA_CHILD_SA 
	char Status[17];
	char Alias[65];
	uint32_t InboundSPI;
	uint32_t OutboundSPI;
	char CreationTime[32];
} rdm_IpsecIkev2saChildSa_t;

typedef struct rdm_IpsecIkev2saChildSaStat_s {   // RDM_OID_IPSEC_IKEV2SA_CHILD_SA_STAT 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint32_t PacketsSent;
	uint32_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t DecryptionErrors;
	uint32_t IntegrityErrors;
	uint32_t ReplayErrors;
	uint32_t PolicyErrors;
	uint32_t OtherReceiveErrors;
} rdm_IpsecIkev2saChildSaStat_t;

typedef struct rdm_ZyIpsecXmlReload_s {   // RDM_OID_ZY_IPSEC_XML_RELOAD 
	bool Enable;
} rdm_ZyIpsecXmlReload_t;

typedef struct rdm_Gre_s {   // RDM_OID_GRE 
	uint32_t TunnelNumberOfEntries;
	uint32_t FilterNumberOfEntries;
} rdm_Gre_t;

typedef struct rdm_GreTunnel_s {   // RDM_OID_GRE_TUNNEL 
	bool Enable;
	char Status[17];
	char Alias[65];
	char RemoteEndpoints[1025];
	char KeepAlivePolicy[9];
	uint32_t KeepAliveTimeout;
	uint32_t KeepAliveThreshold;
	char DeliveryHeaderProtocol[9];
	uint32_t DefaultDSCPMark;
	char ConnectedRemoteEndpoint[257];
	uint32_t InterfaceNumberOfEntries;
	char X_ZYXEL_IfName[33];
	char X_ZYXEL_BoundIfList[129];
	char X_ZYXEL_ActiveBoundIfName[33];
	char X_ZYXEL_BoundBridge[33];
	char X_ZYXEL_BoundBridgeIfName[33];
	uint32_t X_ZYXEL_UpRate;
	uint32_t X_ZYXEL_DownRate;
	uint32_t X_ZYXEL_DSCP;
	uint32_t X_ZYXEL_VLANID;
} rdm_GreTunnel_t;

typedef struct rdm_GreTunnelStat_s {   // RDM_OID_GRE_TUNNEL_STAT 
	uint32_t KeepAliveSent;
	uint32_t KeepAliveReceived;
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSent;
	uint64_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t ErrorsReceived;
	uint32_t X_ZYXEL_DiscardPacketsSent;
	uint32_t X_ZYXEL_DiscardPacketsReceived;
} rdm_GreTunnelStat_t;

typedef struct rdm_GreTunnelIface_s {   // RDM_OID_GRE_TUNNEL_IFACE 
	bool Enable;
	char Status[17];
	char Alias[65];
	char Name[65];
	uint32_t LastChange;
	char LowerLayers[1025];
	uint32_t ProtocolIdOverride;
	bool UseChecksum;
	char KeyIdentifierGenerationPolicy[17];
	uint32_t KeyIdentifier;
	bool UseSequenceNumber;
} rdm_GreTunnelIface_t;

typedef struct rdm_GreTunnelIfaceStat_s {   // RDM_OID_GRE_TUNNEL_IFACE_STAT 
	uint64_t BytesSent;
	uint64_t BytesReceived;
	uint64_t PacketsSent;
	uint64_t PacketsReceived;
	uint32_t ErrorsSent;
	uint32_t ErrorsReceived;
	uint32_t DiscardChecksumReceived;
	uint32_t DiscardSequenceNumberReceived;
} rdm_GreTunnelIfaceStat_t;

typedef struct rdm_GreFilter_s {   // RDM_OID_GRE_FILTER 
	bool Enable;
	char Status[33];
	uint32_t Order;
	char Alias[65];
	char Interface[257];
	bool AllInterfaces;
	int VLANIDCheck;
	bool VLANIDExclude;
	int DSCPMarkPolicy;
} rdm_GreFilter_t;

typedef struct rdm_CaptPortal_s {   // RDM_OID_CAPT_PORTAL 
	bool Enable;
	char Status[17];
	char AllowedList[10001];
	char URL[2001];
} rdm_CaptPortal_t;

typedef struct rdm_Routing_s {   // RDM_OID_ROUTING 
	uint32_t RouterNumberOfEntries;
} rdm_Routing_t;

typedef struct rdm_RoutingRouter_s {   // RDM_OID_ROUTING_ROUTER 
	bool Enable;
	char Status[17];
	char Alias[65];
	uint32_t IPv4ForwardingNumberOfEntries;
	uint32_t IPv6ForwardingNumberOfEntries;
	char X_ZYXEL_ActiveDefaultGateway[513];
	char X_ZYXEL_ActiveV6DefaultGateway[513];
	bool X_ZYXEL_AutoSecureDefaultIface;
} rdm_RoutingRouter_t;

typedef struct rdm_RoutingRouterV4Fwd_s {   // RDM_OID_ROUTING_ROUTER_V4_FWD 
	bool Enable;
	char Status[20];
	char Alias[65];
	bool StaticRoute;
	char DestIPAddress[16];
	char DestSubnetMask[16];
	int ForwardingPolicy;
	char GatewayIPAddress[16];
	char Interface[257];
	char Origin[7];
	int ForwardingMetric;
	char X_ZYXEL_SourceMacAddress[18];
	char X_ZYXEL_SourceIpAddress[16];
	char X_ZYXEL_SourceSubnetMask[16];
	char X_ZYXEL_SourceIfName[13];
	int X_ZYXEL_Protocol;
	int X_ZYXEL_SourcePort;
	char X_ZYXEL_PolicyRouteName[33];
	bool X_ZYXEL_PolicyRoute;
	char X_ZYXEL_RoutAdder[21];
} rdm_RoutingRouterV4Fwd_t;

typedef struct rdm_RoutingRouterV6Fwd_s {   // RDM_OID_ROUTING_ROUTER_V6_FWD 
	bool Enable;
	char Status[20];
	char Alias[65];
	char DestIPPrefix[41];
	int ForwardingPolicy;
	char NextHop[47];
	char Interface[257];
	char Origin[7];
	int ForwardingMetric;
	char ExpirationTime[32];
} rdm_RoutingRouterV6Fwd_t;

typedef struct rdm_RoutingRip_s {   // RDM_OID_ROUTING_RIP 
	bool Enable;
	char SupportedModes[8];
	uint32_t InterfaceSettingNumberOfEntries;
} rdm_RoutingRip_t;

typedef struct rdm_RoutingRipIntfSet_s {   // RDM_OID_ROUTING_RIP_INTF_SET 
	bool Enable;
	char Status[20];
	char Alias[65];
	char Interface[257];
	bool AcceptRA;
	bool SendRA;
	char X_ZYXEL_Version[8];
	char X_ZYXEL_RipOpMode[8];
	bool X_ZYXEL_DisableDefaultGw;
} rdm_RoutingRipIntfSet_t;

typedef struct rdm_RoutingRtInfo_s {   // RDM_OID_ROUTING_RT_INFO 
	bool Enable;
	uint32_t InterfaceSettingNumberOfEntries;
} rdm_RoutingRtInfo_t;

typedef struct rdm_RoutingRtInfoIntfSet_s {   // RDM_OID_ROUTING_RT_INFO_INTF_SET 
	char Status[23];
	char Interface[257];
	char SourceRouter[47];
	char PreferredRouteFlag[7];
	char Prefix[47];
	char RouteLifeTime[32];
	uint32_t X_ZYXEL_RouterLifetime;
	uint32_t X_ZYXEL_RouterLifetimeReal;
	int X_ZYXEL_RA_MFlag;
	int X_ZYXEL_RA_OFlag;
} rdm_RoutingRtInfoIntfSet_t;

typedef struct rdm_NeighborDiscovery_s {   // RDM_OID_NEIGHBOR_DISCOVERY 
	bool Enable;
	uint32_t InterfaceSettingNumberOfEntries;
} rdm_NeighborDiscovery_t;

typedef struct rdm_NeighborDiscoveryIntfSet_s {   // RDM_OID_NEIGHBOR_DISCOVERY_INTF_SET 
	bool Enable;
	char Status[20];
	char Alias[65];
	char Interface[33];
	uint32_t RetransTimer;
	uint32_t RtrSolicitationInterval;
	uint32_t MaxRtrSolicitations;
	bool NUDEnable;
	bool RSEnable;
	bool X_ZYXEL_NDEnable;
	char X_ZYXEL_Ifname[33];
} rdm_NeighborDiscoveryIntfSet_t;

typedef struct rdm_RtAdv_s {   // RDM_OID_RT_ADV 
	bool Enable;
	uint32_t InterfaceSettingNumberOfEntries;
} rdm_RtAdv_t;

typedef struct rdm_RtAdvIntfSet_s {   // RDM_OID_RT_ADV_INTF_SET 
	bool Enable;
	char Status[20];
	char Alias[65];
	char Interface[33];
	char ManualPrefixes[41];
	char Prefixes[41];
	uint32_t MaxRtrAdvInterval;
	uint32_t MinRtrAdvInterval;
	uint32_t AdvDefaultLifetime;
	bool AdvManagedFlag;
	bool AdvOtherConfigFlag;
	bool AdvMobileAgentFlag;
	char AdvPreferredRouterFlag[7];
	bool AdvNDProxyFlag;
	uint32_t AdvLinkMTU;
	uint32_t AdvReachableTime;
	uint32_t AdvRetransTimer;
	uint32_t AdvCurHopLimit;
	char X_ZYXEL_DNSServers[257];
	char X_ZYXEL_DNSList[33];
	bool X_ZYXEL_RAandDHCP6S;
	char X_ZYXEL_DNSSearchList[129];
	uint32_t OptionNumberOfEntries;
} rdm_RtAdvIntfSet_t;

typedef struct rdm_RtAdvIntfSetOpt_s {   // RDM_OID_RT_ADV_INTF_SET_OPT 
	bool Enable;
	char Alias[65];
	uint32_t Tag;
	char Value[257];
} rdm_RtAdvIntfSetOpt_t;

typedef struct rdm_Ipv6rd_s {   // RDM_OID_IPV6RD 
	bool Enable;
	uint32_t InterfaceSettingNumberOfEntries;
} rdm_Ipv6rd_t;

typedef struct rdm_Ipv6rdIntf_s {   // RDM_OID_IPV6RD_INTF 
	bool Enable;
	char Status[9];
	char Alias[65];
	char BorderRelayIPv4Addresses[73];
	bool AllTrafficToBorderRelay;
	char SPIPv6Prefix[65];
	uint32_t IPv4MaskLength;
	char AddressSource[41];
	char TunnelInterface[33];
	char TunneledInterface[33];
	char X_ZYXEL_Interface[33];
} rdm_Ipv6rdIntf_t;

typedef struct rdm_DsLite_s {   // RDM_OID_DS_LITE 
	bool Enable;
	uint32_t InterfaceSettingNumberOfEntries;
} rdm_DsLite_t;

typedef struct rdm_DsLiteIntfSet_s {   // RDM_OID_DS_LITE_INTF_SET 
	bool Enable;
	char Status[9];
	char Alias[65];
	char EndpointAssignmentPrecedence[7];
	char EndpointAddressTypePrecedence[12];
	char EndpointAddressInUse[41];
	char EndpointName[257];
	char EndpointAddress[41];
	char Origin[14];
	char TunnelInterface[257];
	char TunneledInterface[257];
	char X_ZYXEL_Interface[33];
	char X_ZYXEL_IPv6AddressSource[51];
} rdm_DsLiteIntfSet_t;

typedef struct rdm_Qos_s {   // RDM_OID_QOS 
	uint32_t MaxClassificationEntries;
	uint32_t ClassificationNumberOfEntries;
	uint32_t MaxAppEntries;
	uint32_t AppNumberOfEntries;
	uint32_t MaxFlowEntries;
	uint32_t FlowNumberOfEntries;
	uint32_t MaxPolicerEntries;
	uint32_t PolicerNumberOfEntries;
	uint32_t MaxQueueEntries;
	uint32_t QueueNumberOfEntries;
	uint32_t QueueStatsNumberOfEntries;
	uint32_t MaxShaperEntries;
	uint32_t ShaperNumberOfEntries;
	uint32_t DefaultForwardingPolicy;
	uint32_t DefaultTrafficClass;
	char DefaultPolicer[257];
	char DefaultQueue[257];
	int DefaultDSCPMark;
	int DefaultEthernetPriorityMark;
	char AvailableAppList[1025];
	bool X_ZYXEL_Enabled;
	uint32_t X_ZYXEL_UpRate;
	uint32_t X_ZYXEL_DownRate;
	char X_ZYXEL_AutoMapType[17];
} rdm_Qos_t;

typedef struct rdm_QosCls_s {   // RDM_OID_QOS_CLS 
	bool Enable;
	char Status[20];
	uint32_t Order;
	char Alias[65];
	char DHCPType[7];
	char Interface[257];
	bool AllInterfaces;
	char DestIP[46];
	char DestMask[50];
	bool DestIPExclude;
	char SourceIP[46];
	char SourceMask[50];
	bool SourceIPExclude;
	int Protocol;
	bool ProtocolExclude;
	int DestPort;
	int DestPortRangeMax;
	bool DestPortExclude;
	int SourcePort;
	int SourcePortRangeMax;
	bool SourcePortExclude;
	char SourceMACAddress[18];
	char SourceMACMask[18];
	bool SourceMACExclude;
	char DestMACAddress[18];
	char DestMACMask[18];
	bool DestMACExclude;
	int Ethertype;
	bool EthertypeExclude;
	int SSAP;
	bool SSAPExclude;
	int DSAP;
	bool DSAPExclude;
	int LLCControl;
	bool LLCControlExclude;
	int SNAPOUI;
	bool SNAPOUIExclude;
	char SourceVendorClassID[256];
	char SourceVendorClassIDv6[5];
	bool SourceVendorClassIDExclude;
	char SourceVendorClassIDMode[10];
	char DestVendorClassID[256];
	char DestVendorClassIDv6[5];
	bool DestVendorClassIDExclude;
	char DestVendorClassIDMode[10];
	char SourceClientID[256];
	bool SourceClientIDExclude;
	char DestClientID[256];
	bool DestClientIDExclude;
	char SourceUserClassID[256];
	bool SourceUserClassIDExclude;
	char DestUserClassID[256];
	bool DestUserClassIDExclude;
	char SourceVendorSpecificInfo[256];
	bool SourceVendorSpecificInfoExclude;
	uint32_t SourceVendorSpecificInfoEnterprise;
	int SourceVendorSpecificInfoSubOption;
	char DestVendorSpecificInfo[256];
	bool DestVendorSpecificInfoExclude;
	uint32_t DestVendorSpecificInfoEnterprise;
	int DestVendorSpecificInfoSubOption;
	bool TCPACK;
	bool TCPACKExclude;
	uint32_t IPLengthMin;
	uint32_t IPLengthMax;
	bool IPLengthExclude;
	int DSCPCheck;
	bool DSCPExclude;
	int DSCPMark;
	int EthernetPriorityCheck;
	bool EthernetPriorityExclude;
	int EthernetPriorityMark;
	int VLANIDCheck;
	bool VLANIDExclude;
	int OutOfBandInfo;
	uint32_t ForwardingPolicy;
	int TrafficClass;
	char Policer[257];
	char App[257];
	uint32_t X_ZYXEL_VLANIDAction;
	uint32_t X_ZYXEL_VLANIDMark;
	char X_ZYXEL_Name[33];
	char X_ZYXEL_SourceClientIDType[33];
	char X_ZYXEL_DefaultClass[33];
	char X_ZYXEL_Service[129];
	bool X_ZYXEL_ServiceExclude;
	char X_ZYXEL_TargetInterface[257];
} rdm_QosCls_t;

typedef struct rdm_QosApp_s {   // RDM_OID_QOS_APP 
	bool Enable;
	char Status[9];
	char Alias[65];
	char ProtocolIdentifier[257];
	char Name[65];
	uint32_t DefaultForwardingPolicy;
	uint32_t DefaultTrafficClass;
	char DefaultPolicer[257];
	int DefaultDSCPMark;
	int DefaultEthernetPriorityMark;
} rdm_QosApp_t;

typedef struct rdm_QosFlow_s {   // RDM_OID_QOS_FLOW 
	bool Enable;
	char Status[9];
	char Alias[65];
	char Type[257];
	char TypeParameters[257];
	char Name[65];
	char App[257];
	uint32_t ForwardingPolicy;
	uint32_t TrafficClass;
	char Policer[257];
	int DSCPMark;
	int EthernetPriorityMark;
} rdm_QosFlow_t;

typedef struct rdm_QosPolicer_s {   // RDM_OID_QOS_POLICER 
	bool Enable;
	char X_ZYXEL_Name[65];
	char Status[9];
	char Alias[65];
	uint32_t CommittedRate;
	uint32_t CommittedBurstSize;
	uint32_t ExcessBurstSize;
	uint32_t PeakRate;
	uint32_t PeakBurstSize;
	char MeterType[21];
	char PossibleMeterTypes[65];
	char ConformingAction[13];
	char PartialConformingAction[13];
	char NonConformingAction[13];
	uint32_t TotalCountedPackets;
	uint32_t TotalCountedBytes;
	uint32_t ConformingCountedPackets;
	uint32_t ConformingCountedBytes;
	uint32_t PartiallyConformingCountedPackets;
	uint32_t PartiallyConformingCountedBytes;
	uint32_t NonConformingCountedPackets;
	uint32_t NonConformingCountedBytes;
} rdm_QosPolicer_t;

typedef struct rdm_QosQue_s {   // RDM_OID_QOS_QUE 
	bool Enable;
	char Status[20];
	char Alias[65];
	char TrafficClasses[257];
	char Interface[257];
	bool AllInterfaces;
	bool HardwareAssisted;
	uint32_t BufferLength;
	uint32_t Weight;
	uint32_t Precedence;
	uint32_t REDThreshold;
	uint32_t REDPercentage;
	char DropAlgorithm[5];
	char SchedulerAlgorithm[4];
	int ShapingRate;
	uint32_t ShapingBurstSize;
	char X_ZYXEL_Name[33];
	uint32_t X_ZYXEL_HwQueueId;
	int X_ZYXEL_DslLatency;
	int X_ZYXEL_PtmPriority;
	bool X_ZYXEL_DefaultQueue;
} rdm_QosQue_t;

typedef struct rdm_QosQueStat_s {   // RDM_OID_QOS_QUE_STAT 
	bool Enable;
	char Status[9];
	char Alias[65];
	char Queue[257];
	char Interface[257];
	uint32_t OutputPackets;
	uint32_t OutputBytes;
	uint32_t DroppedPackets;
	uint32_t DroppedBytes;
	uint32_t QueueOccupancyPackets;
	uint32_t QueueOccupancyPercentage;
} rdm_QosQueStat_t;

typedef struct rdm_QosShaper_s {   // RDM_OID_QOS_SHAPER 
	bool Enable;
	char Status[20];
	char Alias[65];
	char Interface[257];
	int ShapingRate;
	uint32_t ShapingBurstSize;
} rdm_QosShaper_t;

typedef struct rdm_LanConfSec_s {   // RDM_OID_LAN_CONF_SEC 
	char ConfigPassword[65];
} rdm_LanConfSec_t;

typedef struct rdm_Hosts_s {   // RDM_OID_HOSTS 
	uint32_t HostNumberOfEntries;
	bool X_ZYXEL_DeleteAllLease;
} rdm_Hosts_t;

typedef struct rdm_HostsHost_s {   // RDM_OID_HOSTS_HOST 
	char Alias[65];
	char PhysAddress[65];
	char IPAddress[49];
	char IPAddress6[49];
	char IPLinkLocalAddress6[49];
	char AddressSource[7];
	char DHCPClient[65];
	int LeaseTimeRemaining;
	char AssociatedDevice[257];
	char Layer1Interface[257];
	char Layer3Interface[257];
	char VendorClassID[256];
	char ClientID[5];
	char UserClassID[5];
	char HostName[65];
	bool Active;
	bool X_ZYXEL_DeleteLease;
	char X_ZYXEL_ConnectionType[17];
	char X_ZYXEL_ConnectedAP[65];
	char X_ZYXEL_HostType[65];
	char X_ZYXEL_CapabilityType[65];
	uint32_t X_ZYXEL_PhyRate;
	bool X_ZYXEL_WiFiStatus;
	uint32_t X_ZYXEL_SignalStrength;
	int X_ZYXEL_SNR;
	int X_ZYXEL_RSSI;
	char X_ZYXEL_SoftwareVersion[65];
	uint32_t X_ZYXEL_LastUpdate;
	char X_ZYXEL_Address6Source[7];
	char X_ZYXEL_DHCP6Client[65];
	uint32_t X_ZYXEL_BytesSent;
	uint32_t X_ZYXEL_BytesReceived;
	char X_ZYXEL_OperatingStandard[13];
	uint32_t X_ZYXEL_LastDataDownlinkRate;
	uint32_t X_ZYXEL_LastDataUplinkRate;
	uint32_t IPv4AddressNumberOfEntries;
	uint32_t IPv6AddressNumberOfEntries;
	char ClientDuid[48];
	char ExpireTime[20];
} rdm_HostsHost_t;

typedef struct rdm_HostsHostV4Addr_s {   // RDM_OID_HOSTS_HOST_V4_ADDR 
	char IPAddress[16];
} rdm_HostsHostV4Addr_t;

typedef struct rdm_HostsHostV6Addr_s {   // RDM_OID_HOSTS_HOST_V6_ADDR 
	char IPAddress[49];
} rdm_HostsHostV6Addr_t;

typedef struct rdm_ZyHostsHostExt_s {   // RDM_OID_ZY_HOSTS_HOST_EXT 
	bool L2DevCtrl_Reboot;
	char L2DevCtrl_RebootResult[65];
	bool L2DevCtrl_Reset;
	char L2DevCtrl_ResetResult[65];
	bool L2DevCtrl_FWCheck;
	bool L2DevCtrl_FWDownload;
	bool L2DevCtrl_FWUpgrade;
	char L2DevCtrl_FWURL[257];
	char L2DevCtrl_FWUpgradeResult[65];
	char L2DevCtrl_MediaType[7];
	bool L2DevCtrl_WiFiPwr;
} rdm_ZyHostsHostExt_t;

typedef struct rdm_Dns_s {   // RDM_OID_DNS 
	char SupportedRecordTypes[15];
	char X_ZYXEL_BoundInterfaceList[257];
	bool X_ZYXEL_RedirectLANSideDNSQuery;
	char X_ZYXEL_ActiveDNSServers[257];
	uint32_t X_ZYXEL_DNSQueryScenario;
} rdm_Dns_t;

typedef struct rdm_DnsClient_s {   // RDM_OID_DNS_CLIENT 
	bool Enable;
	char Status[9];
	uint32_t ServerNumberOfEntries;
	bool X_ZYXEL_Dnssec;
} rdm_DnsClient_t;

typedef struct rdm_DnsClientSrv_s {   // RDM_OID_DNS_CLIENT_SRV 
	bool Enable;
	char Status[9];
	char Alias[65];
	char DNSServer[193];
	char Interface[257];
	char Type[20];
	char X_ZYXEL_Type[20];
	char X_ZYXEL_Ifname[33];
	char X_ZYXEL_GwAddr[65];
	char X_ZYXEL_DNSSearchList[129];
} rdm_DnsClientSrv_t;

typedef struct rdm_DnsRelay_s {   // RDM_OID_DNS_RELAY 
	bool Enable;
	char Status[9];
	uint32_t ForwardNumberOfEntries;
	bool X_ZYXEL_Dnssec;
} rdm_DnsRelay_t;

typedef struct rdm_DnsRelayFwd_s {   // RDM_OID_DNS_RELAY_FWD 
	bool Enable;
	char Status[9];
	char Alias[65];
	char DNSServer[46];
	char Interface[257];
	char Type[20];
} rdm_DnsRelayFwd_t;

typedef struct rdm_DnsDiag_s {   // RDM_OID_DNS_DIAG 
} rdm_DnsDiag_t;

typedef struct rdm_DnsDiagNsLookupDiag_s {   // RDM_OID_DNS_DIAG_NS_LOOKUP_DIAG 
	char DiagnosticsState[27];
	char Interface[257];
	char HostName[257];
	char DNSServer[257];
	uint32_t Timeout;
	uint32_t NumberOfRepetitions;
	uint32_t SuccessCount;
	uint32_t ResultNumberOfEntries;
	char X_ZYXEL_Creator[23];
} rdm_DnsDiagNsLookupDiag_t;

typedef struct rdm_DnsDiagNsLookupDiagResult_s {   // RDM_OID_DNS_DIAG_NS_LOOKUP_DIAG_RESULT 
	char Status[28];
	char AnswerType[17];
	char HostNameReturned[257];
	char IPAddresses[1601];
	char DNSServerIP[46];
	uint32_t ResponseTime;
} rdm_DnsDiagNsLookupDiagResult_t;

typedef struct rdm_Nat_s {   // RDM_OID_NAT 
	uint32_t InterfaceSettingNumberOfEntries;
	uint32_t PortMappingNumberOfEntries;
	bool X_ZYXEL_DMZHost_Enable;
	char X_ZYXEL_DMZHost[33];
	bool X_ZYXEL_NAT_ALG;
	bool X_ZYXEL_SIP_ALG;
	bool X_ZYXEL_RTSP_ALG;
	bool X_ZYXEL_PPTP_ALG;
	bool X_ZYXEL_IPSEC_ALG;
	char X_ZYXEL_RTSP_ALG_Ports[97];
} rdm_Nat_t;

typedef struct rdm_NatIntfSetting_s {   // RDM_OID_NAT_INTF_SETTING 
	bool Enable;
	char Status[28];
	char Alias[65];
	char Interface[257];
	bool X_ZYXEL_FullConeEnabled;
} rdm_NatIntfSetting_t;

typedef struct rdm_NatPortMapping_s {   // RDM_OID_NAT_PORT_MAPPING 
	bool Enable;
	char Status[20];
	char Alias[65];
	char Interface[257];
	char X_ZYXEL_WANIP[46];
	char OriginatingIpAddress[46];
	bool AllInterfaces;
	uint32_t LeaseDuration;
	char RemoteHost[46];
	uint32_t ExternalPort;
	uint32_t ExternalPortEndRange;
	uint32_t InternalPort;
	uint32_t X_ZYXEL_InternalPortEndRange;
	char X_ZYXEL_StartTime[32];
	char X_ZYXEL_StopTime[32];
	bool X_ZYXEL_AutoDetectWanStatus;
	bool X_ZYXEL_SetOriginatingIP;
	char Protocol[4];
	char InternalClient[257];
	char Description[257];
} rdm_NatPortMapping_t;

typedef struct rdm_NatPortTriggering_s {   // RDM_OID_NAT_PORT_TRIGGERING 
	bool Enable;
	char Name[65];
	char Status[20];
	char Interface[257];
	bool X_ZYXEL_AutoDetectWanStatus;
	uint32_t TriggerPort;
	uint32_t TriggerPortEndRange;
	uint32_t OpenPort;
	uint32_t OpenPortEndRange;
	char Protocol[4];
	char TriggerProtocol[4];
	char Description[257];
} rdm_NatPortTriggering_t;

typedef struct rdm_NatAddrMapping_s {   // RDM_OID_NAT_ADDR_MAPPING 
	bool Enable;
	char Type[17];
	char LocalStartIP[17];
	char LocalEndIP[17];
	char GlobalStartIP[17];
	char GlobalEndIP[17];
	char MappingSet[7];
	char MappingRuleName[33];
	char Description[65];
	char WANIntfName[65];
	char Interface[65];
	bool X_ZYXEL_AutoDetectWanStatus;
} rdm_NatAddrMapping_t;

typedef struct rdm_NatSessionCtl_s {   // RDM_OID_NAT_SESSION_CTL 
	uint32_t MaxSessionPerSystem;
	uint32_t MaxSessionPerHost;
	uint32_t TcpEstablishedConnectionTimeout;
	uint32_t UdpConnectionTimeout;
	uint32_t UdpCustomizedPort;
	uint32_t UdpCustomizedTimeout;
} rdm_NatSessionCtl_t;

typedef struct rdm_Dhcpv4_s {   // RDM_OID_DHCPV4 
	uint32_t ClientNumberOfEntries;
} rdm_Dhcpv4_t;

typedef struct rdm_Dhcpv4Client_s {   // RDM_OID_DHCPV4_CLIENT 
	bool Enable;
	char Alias[65];
	char Interface[257];
	char Status[20];
	char DHCPStatus[11];
	bool Renew;
	char IPAddress[16];
	char SubnetMask[16];
	char IPRouters[16];
	char DNSServers[257];
	int LeaseTimeRemaining;
	char DHCPServer[16];
	bool PassthroughEnable;
	char PassthroughDHCPPool[257];
	uint32_t SentOptionNumberOfEntries;
	uint32_t ReqOptionNumberOfEntries;
	char X_ZYXEL_DhcpcPidFilePath[33];
	char X_ZYXEL_RenewKey[129];
} rdm_Dhcpv4Client_t;

typedef struct rdm_Dhcpv4SentOpt_s {   // RDM_OID_DHCPV4_SENT_OPT 
	bool Enable;
	char Alias[65];
	uint32_t Tag;
	char Value[256];
} rdm_Dhcpv4SentOpt_t;

typedef struct rdm_Dhcpv4ReqOpt_s {   // RDM_OID_DHCPV4_REQ_OPT 
	bool Enable;
	uint32_t Order;
	char Alias[65];
	uint32_t Tag;
	char Value[513];
} rdm_Dhcpv4ReqOpt_t;

typedef struct rdm_Dhcpv4Srv_s {   // RDM_OID_DHCPV4_SRV 
	bool Enable;
	bool X_ZYXEL_Reset;
	uint32_t PoolNumberOfEntries;
} rdm_Dhcpv4Srv_t;

typedef struct rdm_Dhcpv4SrvPool_s {   // RDM_OID_DHCPV4_SRV_POOL 
	bool Enable;
	bool X_ZYXEL_SetEnable;
	bool X_ZYXEL_AutoReserveLanIp;
	char Status[20];
	char Alias[65];
	uint32_t Order;
	char Interface[257];
	char VendorClassID[256];
	bool VendorClassIDExclude;
	char VendorClassIDMode[10];
	char ClientID[256];
	bool ClientIDExclude;
	char UserClassID[256];
	bool ChaddrExclude;
	char Chaddr[18];
	char ChaddrMask[18];
	char MinAddress[16];
	char MaxAddress[16];
	char ReservedAddresses[16];
	char SubnetMask[16];
	char DNSServers[257];
	bool X_ZYXEL_ServerConfigurable;
	char X_ZYXEL_DNS_Type[17];
	char DomainName[65];
	char IPRouters[16];
	int LeaseTime;
	char X_ZYXEL_STB_VENDORID[65];
	char X_ZYXEL_STB_URL[257];
	char X_ZYXEL_STB_PrCode[65];
	uint32_t X_ZYXEL_STB_URL_subcode;
	uint32_t X_ZYXEL_STB_PrCode_subcode;
	uint32_t StaticAddressNumberOfEntries;
	uint32_t OptionNumberOfEntries;
	uint32_t ClientNumberOfEntries;
} rdm_Dhcpv4SrvPool_t;

typedef struct rdm_Dhcpv4SrvPoolStaticAddr_s {   // RDM_OID_DHCPV4_SRV_POOL_STATIC_ADDR 
	bool Enable;
	char Alias[65];
	char Chaddr[18];
	char Yiaddr[16];
} rdm_Dhcpv4SrvPoolStaticAddr_t;

typedef struct rdm_Dhcpv4SrvPoolOpt_s {   // RDM_OID_DHCPV4_SRV_POOL_OPT 
	bool Enable;
	char Alias[65];
	uint32_t Tag;
	char Value[256];
} rdm_Dhcpv4SrvPoolOpt_t;

typedef struct rdm_Dhcpv4SrvPoolClient_s {   // RDM_OID_DHCPV4_SRV_POOL_CLIENT 
	char Alias[65];
	char Chadder[18];
	bool Active;
	uint32_t IPv4AddressNumberOfEntries;
	uint32_t OptionNumberOfEntries;
} rdm_Dhcpv4SrvPoolClient_t;

typedef struct rdm_Dhcpv4SrvPoolClientV4Addr_s {   // RDM_OID_DHCPV4_SRV_POOL_CLIENT_V4_ADDR 
	char IPAddress[16];
	char LeaseTimeRemaining[32];
} rdm_Dhcpv4SrvPoolClientV4Addr_t;

typedef struct rdm_Dhcpv4SrvPoolClientOpt_s {   // RDM_OID_DHCPV4_SRV_POOL_CLIENT_OPT 
	uint32_t Tag;
	char Value[256];
} rdm_Dhcpv4SrvPoolClientOpt_t;

typedef struct rdm_Dhcpv4SrvSubnet_s {   // RDM_OID_DHCPV4_SRV_SUBNET 
	bool Enable;
	char Interface[257];
	char MinAddress[16];
	char MaxAddress[16];
	char SubnetMask[16];
	char LANIP[16];
} rdm_Dhcpv4SrvSubnet_t;

typedef struct rdm_Dhcpv4Relay_s {   // RDM_OID_DHCPV4_RELAY 
	bool Enable;
	char Status[9];
	uint32_t ForwardingNumberOfEntries;
} rdm_Dhcpv4Relay_t;

typedef struct rdm_Dhcpv4RelayFwd_s {   // RDM_OID_DHCPV4_RELAY_FWD 
	bool Enable;
	char Status[20];
	char Alias[65];
	uint32_t Order;
	char Interface[257];
	char VendorClassID[256];
	bool VendorClassIDExclude;
	char VendorClassIDMode[10];
	char ClientID[256];
	bool ClientIDExclude;
	char UserClassID[256];
	bool UserClassIDExclude;
	char Chaddr[18];
	char ChaddrMask[18];
	bool ChaddrExclude;
	bool LocallyServed;
	char DHCPServerIPAddress[16];
} rdm_Dhcpv4RelayFwd_t;

typedef struct rdm_Dhcpv6_s {   // RDM_OID_DHCPV6 
	uint32_t ClientNumberOfEntries;
} rdm_Dhcpv6_t;

typedef struct rdm_Dhcpv6Client_s {   // RDM_OID_DHCPV6_CLIENT 
	bool Enable;
	char Alias[65];
	char Interface[257];
	char Status[20];
	char DUID[131];
	bool RequestAddresses;
	bool RequestPrefixes;
	bool RapidCommit;
	bool Renew;
	int SuggestedT1;
	int SuggestedT2;
	char SupportedOptions[257];
	char RequestedOptions[257];
	uint32_t ServerNumberOfEntries;
	uint32_t SentOptionNumberOfEntries;
	uint32_t ReqOptionNumberOfEntries;
	char X_ZYXEL_DhcpcPidFilePath[33];
} rdm_Dhcpv6Client_t;

typedef struct rdm_Dhcpv6ClientSrv_s {   // RDM_OID_DHCPV6_CLIENT_SRV 
	char SourceAddress[33];
	char DUID[131];
	char InformationRefreshTime[32];
} rdm_Dhcpv6ClientSrv_t;

typedef struct rdm_Dhcpv6ClientSentOpt_s {   // RDM_OID_DHCPV6_CLIENT_SENT_OPT 
	bool Enable;
	char Alias[65];
	uint32_t Tag;
	char Value[257];
} rdm_Dhcpv6ClientSentOpt_t;

typedef struct rdm_Dhcpv6ClientReceivedOpt_s {   // RDM_OID_DHCPV6_CLIENT_RECEIVED_OPT 
	uint32_t Tag;
	char Value[257];
	char Server[41];
} rdm_Dhcpv6ClientReceivedOpt_t;

typedef struct rdm_Dhcpv6Srv_s {   // RDM_OID_DHCPV6_SRV 
	bool Enable;
	uint32_t PoolNumberOfEntries;
} rdm_Dhcpv6Srv_t;

typedef struct rdm_Dhcpv6SrvPool_s {   // RDM_OID_DHCPV6_SRV_POOL 
	bool Enable;
	char Status[20];
	char Alias[65];
	uint32_t Order;
	char Interface[257];
	char DUID[131];
	bool DUIDExclude;
	char VendorClassID[5];
	bool VendorClassIDExclude;
	char UserClassID[5];
	bool UserClassIDExclude;
	char SourceAddress[33];
	char SourceAddressMask[33];
	bool SourceAddressExclude;
	bool IANAEnable;
	char IANAManualPrefixes[321];
	char IANAPrefixes[321];
	bool IAPDEnable;
	char IAPDManualPrefixes[321];
	char IAPDPrefixes[321];
	uint32_t IAPDAddLength;
	uint32_t ClientNumberOfEntries;
	uint32_t OptionNumberOfEntries;
	char X_ZYXEL_MinAddress[129];
	char X_ZYXEL_MaxAddress[129];
	char X_ZYXEL_DNSServers[257];
	char X_ZYXEL_DNSList[33];
	char X_ZYXEL_DNSSuffix[65];
	bool X_ZYXEL_RAandDHCP6S;
	char X_ZYXEL_SrvPoolName[65];
} rdm_Dhcpv6SrvPool_t;

typedef struct rdm_Dhcpv6SrvPoolClient_s {   // RDM_OID_DHCPV6_SRV_POOL_CLIENT 
	char Alias[65];
	char SourceAddress[33];
	bool Active;
	uint32_t IPv6AddressNumberOfEntries;
	uint32_t IPv6PrefixNumberOfEntries;
	uint32_t OptionNumberOfEntries;
} rdm_Dhcpv6SrvPoolClient_t;

typedef struct rdm_Dhcpv6SrvPoolClientV6Addr_s {   // RDM_OID_DHCPV6_SRV_POOL_CLIENT_V6_ADDR 
	char IPAddress[49];
	char PreferredLifetime[32];
	char ValidLifetime[32];
} rdm_Dhcpv6SrvPoolClientV6Addr_t;

typedef struct rdm_Dhcpv6SrvPoolClientV6Prefix_s {   // RDM_OID_DHCPV6_SRV_POOL_CLIENT_V6_PREFIX 
	char Prefix[33];
	char PreferredLifetime[32];
	char ValidLifetime[32];
} rdm_Dhcpv6SrvPoolClientV6Prefix_t;

typedef struct rdm_Dhcpv6SrvPoolClientOpt_s {   // RDM_OID_DHCPV6_SRV_POOL_CLIENT_OPT 
	uint32_t Tag;
	char Value[256];
} rdm_Dhcpv6SrvPoolClientOpt_t;

typedef struct rdm_Dhcpv6SrvPoolOpt_s {   // RDM_OID_DHCPV6_SRV_POOL_OPT 
	bool Enable;
	char Alias[65];
	uint32_t Tag;
	char Value[65536];
	char PassthroughClient[257];
} rdm_Dhcpv6SrvPoolOpt_t;

typedef struct rdm_Ieee8021x_s {   // RDM_OID_IEEE8021X 
	uint32_t SupplicantNumberOfEntries;
} rdm_Ieee8021x_t;

typedef struct rdm_Ieee8021xSupplicant_s {   // RDM_OID_IEEE8021X_SUPPLICANT 
	bool Enable;
	char Status[20];
	char Alias[65];
	char Interface[257];
	char PAEState[15];
	char EAPIdentity[257];
	uint32_t MaxStart;
	uint32_t StartPeriod;
	uint32_t HeldPeriod;
	uint32_t AuthPeriod;
	char AuthenticationCapabilities[8];
	char StartFailurePolicy[21];
	char AuthenticationSuccessPolicy[16];
	bool Reset;
	bool Disconnect;
	bool X_ZYXEL_BiDirectional;
	char X_ZYXEL_Certificate[257];
	char X_ZYXEL_trustCA[257];
} rdm_Ieee8021xSupplicant_t;

typedef struct rdm_Ieee8021xSupplicantStat_s {   // RDM_OID_IEEE8021X_SUPPLICANT_STAT 
	uint32_t ReceivedFrames;
	uint32_t TransmittedFrames;
	uint32_t TransmittedStartFrames;
	uint32_t TransmittedLogoffFrames;
	uint32_t TransmittedResponseIdFrames;
	uint32_t TransmittedResponseFrames;
	uint32_t ReceivedRequestIdFrames;
	uint32_t ReceivedInvalidFrames;
	uint32_t ReceivedLengthErrorFrames;
	uint32_t LastFrameVersion;
	char LastFrameSourceMACAddress[18];
} rdm_Ieee8021xSupplicantStat_t;

typedef struct rdm_Ieee8021xSupplicantEapmd5_s {   // RDM_OID_IEEE8021X_SUPPLICANT_EAPMD5 
	bool Enable;
	char SharedSecret[257];
} rdm_Ieee8021xSupplicantEapmd5_t;

typedef struct rdm_Ieee8021xSupplicantEaptls_s {   // RDM_OID_IEEE8021X_SUPPLICANT_EAPTLS 
	bool Enable;
	bool MutualAuthenticationEnable;
} rdm_Ieee8021xSupplicantEaptls_t;

typedef struct rdm_Usrs_s {   // RDM_OID_USRS 
	uint32_t UserNumberOfEntries;
} rdm_Usrs_t;

typedef struct rdm_UsrsUsr_s {   // RDM_OID_USRS_USR 
	char Alias[65];
	bool Enable;
	bool RemoteAccessCapable;
	char Username[65];
	char Password[65];
	char Language[17];
} rdm_UsrsUsr_t;

typedef struct rdm_SmartCardReaders_s {   // RDM_OID_SMART_CARD_READERS 
	uint32_t SmartCardReaderNumberOfEntries;
} rdm_SmartCardReaders_t;

typedef struct rdm_SmartCardReadersScr_s {   // RDM_OID_SMART_CARD_READERS_SCR 
	char Alias[65];
	bool Enable;
	char status[9];
	char Name[257];
	bool Reset;
	char ResetTime[32];
	uint32_t DecryptionFailedCounter;
	uint32_t DecryptionFailedNoKeyCounter;
} rdm_SmartCardReadersScr_t;

typedef struct rdm_SmartCardReadersScrSc_s {   // RDM_OID_SMART_CARD_READERS_SCR_SC 
	char Status[8];
	char Type[5];
	char Application[14];
	char SerialNumber[257];
	char ATR[1025];
} rdm_SmartCardReadersScrSc_t;

typedef struct rdm_Upnp_s {   // RDM_OID_UPNP 
} rdm_Upnp_t;

typedef struct rdm_UpnpDev_s {   // RDM_OID_UPNP_DEV 
	bool Enable;
	char X_ZYXEL_Status[9];
	bool X_ZYXEL_NATTEnable;
	bool UPnPMediaServer;
	bool UPnPMediaRenderer;
	bool UPnPWLANAccessPoint;
	bool UPnPQoSDevice;
	bool UPnPQoSPolicyHolder;
	bool UPnPIGD;
	bool UPnPDMBasicMgmt;
	bool UPnPDMConfigurationMgmt;
	bool UPnPDMSoftwareMgmt;
} rdm_UpnpDev_t;

typedef struct rdm_UpnpDevCapb_s {   // RDM_OID_UPNP_DEV_CAPB 
	uint32_t UPnPArchitecture;
	uint32_t UPnPArchitectureMinorVer;
	uint32_t UPnPMediaServer;
	uint32_t UPnPMediaRenderer;
	uint32_t UPnPWLANAccessPoint;
	uint32_t UPnPBasicDevice;
	uint32_t UPnPQoSDevice;
	uint32_t UPnPQoSPolicyHolder;
	uint32_t UPnPIGD;
	uint32_t UPnPDMBasicMgmt;
	uint32_t UPnPDMConfigurationMgmt;
	uint32_t UPnPDMSoftwareMgmt;
} rdm_UpnpDevCapb_t;

typedef struct rdm_UpnpDisc_s {   // RDM_OID_UPNP_DISC 
	uint32_t RootDeviceNumberOfEntries;
	uint32_t DeviceNumberOfEntries;
	uint32_t ServiceNumberOfEntries;
} rdm_UpnpDisc_t;

typedef struct rdm_UpnpDiscRootDev_s {   // RDM_OID_UPNP_DISC_ROOT_DEV 
	char Status[15];
	char UUID[37];
	char USN[257];
	uint32_t LeaseTime;
	char Location[257];
	char Server[257];
	char Host[1025];
} rdm_UpnpDiscRootDev_t;

typedef struct rdm_UpnpDiscDev_s {   // RDM_OID_UPNP_DISC_DEV 
	char Status[15];
	char UUID[37];
	char USN[37];
	uint32_t LeaseTime;
	char Location[257];
	char Server[257];
	char Host[1025];
} rdm_UpnpDiscDev_t;

typedef struct rdm_UpnpDiscService_s {   // RDM_OID_UPNP_DISC_SERVICE 
	char Status[15];
	char USN[257];
	uint32_t LeaseTime;
	char Location[257];
	char Server[257];
	char Host[1025];
} rdm_UpnpDiscService_t;

typedef struct rdm_Dlna_s {   // RDM_OID_DLNA 
	bool X_ZYXEL_Enable;
	char X_ZYXEL_Status[9];
	char X_ZYXEL_MediaPrePath[33];
	char X_ZYXEL_MediaRelativePath[257];
	char X_ZYXEL_LastPath[257];
	char X_ZYXEL_Interface[129];
} rdm_Dlna_t;

typedef struct rdm_DlnaCapb_s {   // RDM_OID_DLNA_CAPB 
	char HNDDeviceClass[257];
	char DeviceCapability[257];
	char HIDDeviceClass[257];
	char ImageClassProfileID[257];
	char AudioClassProfileID[257];
	char AVClassProfileID[257];
	char MediaCollectionProfileID[257];
	char PrinterClassProfileID[257];
} rdm_DlnaCapb_t;

typedef struct rdm_SelfTestDiag_s {   // RDM_OID_SELF_TEST_DIAG 
	char DiagnosticsState[15];
	char Results[1025];
} rdm_SelfTestDiag_t;

typedef struct rdm_Firewall_s {   // RDM_OID_FIREWALL 
	bool Enable;
	bool IPv4_Enable;
	bool IPv6_Enable;
	bool X_ZYXEL_Dos_Enable;
	bool X_ZYXEL_DenyPing;
	char Config[9];
	char AdvancedLevel[33];
	char Type[10];
	char Version[17];
	char LastChange[32];
	uint32_t LevelNumberOfEntries;
	uint32_t ChainNumberOfEntries;
} rdm_Firewall_t;

typedef struct rdm_FirewallLevel_s {   // RDM_OID_FIREWALL_LEVEL 
	char Alias[65];
	char Name[65];
	char Description[257];
	uint32_t Order;
	char Chain[25];
	bool PortMappingEnabled;
	char DefaultPolicy[7];
	bool DefaultLogPolicy;
	char X_ZYXEL_DefaultConfig[9];
} rdm_FirewallLevel_t;

typedef struct rdm_FirewallChain_s {   // RDM_OID_FIREWALL_CHAIN 
	bool Enable;
	char Alias[65];
	char Name[65];
	char Creator[23];
	uint32_t RuleNumberOfEntries;
} rdm_FirewallChain_t;

typedef struct rdm_FirewallChainRule_s {   // RDM_OID_FIREWALL_CHAIN_RULE 
	bool Enable;
	char Status[20];
	uint32_t Order;
	char Alias[65];
	char Description[257];
	char Target[12];
	char TargetChain[25];
	bool Log;
	char CreationDate[32];
	char ExpiryDate[32];
	char SourceInterface[257];
	bool SourceInterfaceExclude;
	bool SourceAllInterfaces;
	char DestInterface[257];
	bool DestInterfaceExclude;
	bool DestAllInterfaces;
	int IPVersion;
	char DestIP[46];
	char DestMask[50];
	bool DestIPExclude;
	char SourceIP[46];
	char SourceMask[50];
	bool SourceIPExclude;
	int Protocol;
	bool ProtocolExclude;
	int DestPort;
	int DestPortRangeMax;
	bool DestPortExclude;
	int SourcePort;
	int SourcePortRangeMax;
	bool SourcePortExclude;
	int DSCP;
	bool DSCPExclude;
	char X_ZYXEL_Direction[16];
	int X_ZYXEL_ICMPType;
	int X_ZYXEL_ICMPTypeCode;
	char X_ZYXEL_TCPFlagMask[24];
	char X_ZYXEL_TCPFlagComp[24];
	uint32_t X_ZYXEL_LimitRate;
	char X_ZYXEL_LimitRateUnit[7];
	uint32_t X_ZYXEL_ScheduleRule;
	uint32_t X_ZYXEL_ServiceIndex;
} rdm_FirewallChainRule_t;

typedef struct rdm_PerdStatistics_s {   // RDM_OID_PERD_STATISTICS 
	uint32_t MinSampleInterval;
	uint32_t MaxReportSamples;
	uint32_t SampleSetNumberOfEntries;
} rdm_PerdStatistics_t;

typedef struct rdm_PerdStatisticsSampleSet_s {   // RDM_OID_PERD_STATISTICS_SAMPLE_SET 
	char Alias[65];
	bool Enable;
	char Status[9];
	char Name[129];
	uint32_t SampleInterval;
	uint32_t ReportSamples;
	char TimeReference[32];
	uint32_t FetchSamples;
	bool ForceSample;
	char ReportStartTime[32];
	char ReportEndTime[32];
	char SampleSeconds[33];
	uint32_t ParameterNumberOfEntries;
} rdm_PerdStatisticsSampleSet_t;

typedef struct rdm_PerdStatisticsSampleSetParam_s {   // RDM_OID_PERD_STATISTICS_SAMPLE_SET_PARAM 
	char Alias[65];
	bool Enable;
	char Reference[257];
	char SampleMode[8];
	char CalculationMode[8];
	int LowThreshold;
	int HighThreshold;
	char SampleSeconds[33];
	char SuspectData[33];
	char Values[17];
	uint32_t Failures;
} rdm_PerdStatisticsSampleSetParam_t;

typedef struct rdm_SwModule_s {   // RDM_OID_SW_MODULE 
	uint32_t ExecEnvNumberOfEntries;
	uint32_t DeploymentUnitNumberOfEntries;
	uint32_t ExecutionUnitNumberOfEntries;
} rdm_SwModule_t;

typedef struct rdm_SwModuleExecEnv_s {   // RDM_OID_SW_MODULE_EXEC_ENV 
	bool Enable;
	char Status[9];
	bool Reset;
	char Alias[65];
	char Name[33];
	char Type[65];
	uint32_t InitialRunLevel;
	int RequestedRunLevel;
	int CurrentRunLevel;
	int InitialExecutionUnitRunLevel;
	char Vendor[129];
	char Version[33];
	char ParentExecEnv[37];
	int AllocatedDiskSpace;
	int AvailableDiskSpace;
	int AllocatedMemory;
	int AvailableMemory;
	char ActiveExecutionUnits[337];
	char ProcessorRefList[289];
} rdm_SwModuleExecEnv_t;

typedef struct rdm_SwModuleDeploymentUnit_s {   // RDM_OID_SW_MODULE_DEPLOYMENT_UNIT 
	char UUID[37];
	char DUID[65];
	char Alias[65];
	char Name[65];
	char Status[13];
	bool Resolved;
	char URL[1025];
	char Description[257];
	char Vendor[129];
	char Version[33];
	char VendorLogList[337];
	char VendorconfigList[337];
	char ExecutionUnitList[337];
	char ExecutionEnvRef[37];
} rdm_SwModuleDeploymentUnit_t;

typedef struct rdm_SwModuleExecUnit_s {   // RDM_OID_SW_MODULE_EXEC_UNIT 
	char EUID[65];
	char Alias[65];
	char Name[33];
	char ExecEnvLabel[65];
	char Status[9];
	char RequestedState[7];
	char ExecutionFaultCode[19];
	char ExecutionFaultMessage[257];
	bool AutoStart;
	uint32_t RunLevel;
	char Vendor[129];
	char Version[33];
	char Description[257];
	int DiskSpaceInUse;
	int MemoryInUse;
	char References[337];
	char AssociatedProcessList[385];
	char VendorLogList[337];
	char VendorConfigList[337];
	char SupportedDataModelList[337];
	char ExecutionEnvRef[37];
} rdm_SwModuleExecUnit_t;

typedef struct rdm_SwModuleExecUnitExt_s {   // RDM_OID_SW_MODULE_EXEC_UNIT_EXT 
} rdm_SwModuleExecUnitExt_t;

typedef struct rdm_FaultMgmt_s {   // RDM_OID_FAULT_MGMT 
	uint32_t SupportedAlarmNumberOfEntries;
	uint32_t MaxCurrentAlarmEntries;
	uint32_t CurrentAlarmNumberOfEntries;
	uint32_t HistoryEventNumberOfEntries;
	uint32_t ExpeditedEventNumberOfEntries;
	uint32_t QueuedEventNumberOfEntries;
} rdm_FaultMgmt_t;

typedef struct rdm_FaultMgmtSuptAlarm_s {   // RDM_OID_FAULT_MGMT_SUPT_ALARM 
	char EventType[65];
	char ProbableCause[65];
	char SpecificProblem[129];
	char PerceivedSeverity[14];
	char ReportingMechanism[12];
} rdm_FaultMgmtSuptAlarm_t;

typedef struct rdm_FaultMgmtCurrentAlarm_s {   // RDM_OID_FAULT_MGMT_CURRENT_ALARM 
	char AlarmIdentifier[65];
	char AlarmRaisedTime[32];
	char AlarmChangedTime[32];
	char ManagedObjectInstance[513];
	char EventType[65];
	char ProbableCause[65];
	char SpecificProblem[129];
	char PerceivedSeverity[14];
	char AdditionalText[257];
	char AdditionalInformation[257];
} rdm_FaultMgmtCurrentAlarm_t;

typedef struct rdm_FaultMgmtHistoryEvent_s {   // RDM_OID_FAULT_MGMT_HISTORY_EVENT 
	char EventTime[32];
	char AlarmIdentifier[65];
	char NotificationType[13];
	char ManagedObjectInstance[513];
	char EventType[65];
	char ProbableCause[65];
	char SpecificProblem[129];
	char PerceivedSeverity[14];
	char AdditionalText[257];
	char AdditionalInformation[257];
} rdm_FaultMgmtHistoryEvent_t;

typedef struct rdm_FaultMgmtExpeditedEvent_s {   // RDM_OID_FAULT_MGMT_EXPEDITED_EVENT 
	char EventTime[32];
	char AlarmIdentifier[65];
	char NotificationType[13];
	char ManagedObjectInstance[513];
	char EventType[65];
	char ProbableCause[65];
	char SpecificProblem[129];
	char PerceivedSeverity[14];
	char AdditionalText[257];
	char AdditionalInformation[257];
} rdm_FaultMgmtExpeditedEvent_t;

typedef struct rdm_FaultMgmtQuedEvent_s {   // RDM_OID_FAULT_MGMT_QUED_EVENT 
	char EventTime[32];
	char AlarmIdentifier[65];
	char NotificationType[13];
	char ManagedObjectInstance[513];
	char EventType[65];
	char ProbableCause[65];
	char SpecificProblem[129];
	char PerceivedSeverity[14];
	char AdditionalText[257];
	char AdditionalInformation[257];
} rdm_FaultMgmtQuedEvent_t;

typedef struct rdm_DevSec_s {   // RDM_OID_DEV_SEC 
	uint32_t CertificateNumberOfEntries;
} rdm_DevSec_t;

typedef struct rdm_DevSecCert_s {   // RDM_OID_DEV_SEC_CERT 
	char X_ZYXEL_Name[33];
	char X_ZYXEL_Type[33];
	char X_ZYXEL_Certificate[4097];
	char X_ZYXEL_PrivateKey[4097];
	char X_ZYXEL_SigningRequest[4097];
	char X_ZYXEL_CommonName[65];
	char X_ZYXEL_OrgName[33];
	char X_ZYXEL_StateName[33];
	char X_ZYXEL_CountryName[3];
	bool Enable;
	char LastModif[32];
	char SerialNumber[65];
	char Issuer[257];
	char NotBefore[32];
	char NotAfter[32];
	char Subject[257];
	char SubjectAlt[257];
	char SignatureAlgorithm[257];
} rdm_DevSecCert_t;

typedef struct rdm_Fap_s {   // RDM_OID_FAP 
} rdm_Fap_t;

typedef struct rdm_FapGps_s {   // RDM_OID_FAP_GPS 
	bool ScanOnBoot;
	bool ScanPeriodically;
	uint32_t PeriodicInterval;
	char PeriodicTime[32];
	bool ContinuousGPS;
	uint32_t ScanTimeout;
	char ScanStatus[14];
	char ErrorDetails[257];
	char LastScanTime[32];
	char LastSuccessfulScanTime[32];
	int LockedLatitude;
	int LockedLongitude;
	uint32_t NumberOfSatellites;
	bool GPSReset;
} rdm_FapGps_t;

typedef struct rdm_FapGpsContsGpsStatus_s {   // RDM_OID_FAP_GPS_CONTS_GPS_STATUS 
	bool CurrentFix;
	bool GotFix;
	bool TimingGood;
	int Latitude;
	int Longitude;
	int Elevation;
	char LastFixTime[32];
	uint32_t LastFixDuration;
	int FirstFixTimeout;
	uint32_t SatellitesTracked;
	uint32_t SatelliteTrackingInterval;
	char ReceiverStatus[257];
	char LocationType[10];
	uint32_t LockTimeOutDuration;
} rdm_FapGpsContsGpsStatus_t;

typedef struct rdm_FapGpsAgpsSrvConf_s {   // RDM_OID_FAP_GPS_AGPS_SRV_CONF 
	bool Enable;
	char ServerURL[257];
	uint32_t ServerPort;
	char Username[65];
	char Password[65];
	int ReferenceLatitude;
	int ReferenceLongitude;
	bool ServerInUse;
} rdm_FapGpsAgpsSrvConf_t;

typedef struct rdm_FapPerfMgmt_s {   // RDM_OID_FAP_PERF_MGMT 
	uint32_t ConfigNumberOfEntries;
} rdm_FapPerfMgmt_t;

typedef struct rdm_FapPerfMgmtConf_s {   // RDM_OID_FAP_PERF_MGMT_CONF 
	bool Enable;
	char Alias[65];
	char URL[257];
	char Username[257];
	char Password[257];
	uint32_t PeriodicUploadInterval;
	char PeriodicUploadTime[32];
} rdm_FapPerfMgmtConf_t;

typedef struct rdm_FapAppPlatf_s {   // RDM_OID_FAP_APP_PLATF 
	char Version[65];
	bool Enable;
	char Status[13];
	uint32_t MaxNumberOfApplications;
	uint32_t CurrentNumberofApplications;
} rdm_FapAppPlatf_t;

typedef struct rdm_FapAppPlatfCapb_s {   // RDM_OID_FAP_APP_PLATF_CAPB 
	bool PresenceApplicationSupport;
	bool FemtoAwarenessAPISupport;
	bool SMSAPISupport;
	bool SubscribeToNotificationsOfSMSSentToApplicationSupport;
	bool QuerySMSDeliveryStatusSupport;
	bool MMSAPISupport;
	bool QueryMMSDeliveryStatusSupport;
	bool SubscribeToNotificationsOfMMSSentToApplicationSupport;
	bool TerminalLocationAPISupport;
	char AuthenticationMethodsSupported[16];
	char AccessLevelsSupported[16];
	char SendSMSTargetAddressType[19];
	char SendMMSTargetAddressType[19];
} rdm_FapAppPlatfCapb_t;

typedef struct rdm_FapAppPlatfCtrl_s {   // RDM_OID_FAP_APP_PLATF_CTRL 
	char AuthenticationMethod[257];
	char TunnelInst[257];
} rdm_FapAppPlatfCtrl_t;

typedef struct rdm_FapAppPlatfCtrlFemtoAware_s {   // RDM_OID_FAP_APP_PLATF_CTRL_FEMTO_AWARE 
	bool APIEnable;
	bool QueueEnable;
	char Queueing[9];
	uint32_t MaxAPIUsersNumber;
	char FemtozoneID[257];
	bool NotificationsUserIdentifierMSISDN;
	bool SubscribeToNotificationsResponseCallbackData;
	bool QueryFemtocellResponseTimezone;
} rdm_FapAppPlatfCtrlFemtoAware_t;

typedef struct rdm_FapAppPlatfCtrlSms_s {   // RDM_OID_FAP_APP_PLATF_CTRL_SMS 
	bool APIEnable;
	bool QueueEnable;
	char Queueing[9];
	uint32_t MaxAPIUsersNumber;
	uint32_t MinSendSMSTimeInterval;
	bool EnableQuerySMSDeliveryStatus;
	bool EnableSubscribeToNotificationsOfMessageSentToApplication;
} rdm_FapAppPlatfCtrlSms_t;

typedef struct rdm_FapAppPlatfCtrlMms_s {   // RDM_OID_FAP_APP_PLATF_CTRL_MMS 
	bool APIEnable;
	bool QueueEnable;
	char Queueing[9];
	uint32_t MaxAPIUsersNumber;
	uint32_t MinSendSMSTimeInterval;
	bool EnableQueryMMSDeliveryStatus;
	bool EnableSubscribeToNotificationsOfMessageSentToApplication;
} rdm_FapAppPlatfCtrlMms_t;

typedef struct rdm_FapAppPlatfCtrlTermLoc_s {   // RDM_OID_FAP_APP_PLATF_CTRL_TERM_LOC 
	bool APIEnable;
	bool QueueEnable;
	char Queueing[9];
	uint32_t MaxAPIUsersNumber;
	uint32_t QueryMobileLocationResponseAddress;
	bool QueryMobileLocationResponseLongitudeLatitude;
	bool QueryMobileLocationResponseAltitude;
	uint32_t QueryMobileLocationResponseTimestamp;
} rdm_FapAppPlatfCtrlTermLoc_t;

typedef struct rdm_FapAppPlatfMont_s {   // RDM_OID_FAP_APP_PLATF_MONT 
	bool Enable;
	uint32_t MonitoringInterval;
	uint32_t AuthenticationRequestsReceived;
	uint32_t AuthenticationRequestsRejected;
} rdm_FapAppPlatfMont_t;

typedef struct rdm_FapAppPlatfMontFemtoAware_s {   // RDM_OID_FAP_APP_PLATF_MONT_FEMTO_AWARE 
	bool APIAvailable;
	uint32_t APIUsers;
	char QueueState[9];
	uint32_t QueueNum;
	uint32_t QueueReceived;
	uint32_t QueueDiscarded;
} rdm_FapAppPlatfMontFemtoAware_t;

typedef struct rdm_FapAppPlatfMontSms_s {   // RDM_OID_FAP_APP_PLATF_MONT_SMS 
	bool APIAvailable;
	uint32_t APIUsers;
	char QueueState[9];
	uint32_t QueueNum;
	uint32_t QueueReceived;
	uint32_t QueueDiscarded;
} rdm_FapAppPlatfMontSms_t;

typedef struct rdm_FapAppPlatfMontMms_s {   // RDM_OID_FAP_APP_PLATF_MONT_MMS 
	bool APIAvailable;
	uint32_t APIUsers;
	char QueueState[9];
	uint32_t QueueNum;
	uint32_t QueueReceived;
	uint32_t QueueDiscarded;
} rdm_FapAppPlatfMontMms_t;

typedef struct rdm_FapAppPlatfMontTermLoc_s {   // RDM_OID_FAP_APP_PLATF_MONT_TERM_LOC 
	bool APIAvailable;
	uint32_t APIUsers;
	char QueueState[9];
	uint32_t QueueNum;
	uint32_t QueueReceived;
	uint32_t QueueDiscarded;
} rdm_FapAppPlatfMontTermLoc_t;

typedef struct rdm_BulkData_s {   // RDM_OID_BULK_DATA 
	bool Enable;
	char Status[9];
	uint32_t MinReportingInterval;
	char Protocols[10];
	char EncodingTypes[4];
	int MaxNumberOfProfiles;
	int MaxNumberOfParameterReferences;
	uint32_t ProfileNumberOfEntries;
} rdm_BulkData_t;

typedef struct rdm_BulkDataProf_s {   // RDM_OID_BULK_DATA_PROF 
	bool Enable;
	char Alias[65];
	char Protocol[10];
	char EncodingType[4];
	uint32_t ReportingInterval;
	char TimeReference[32];
	char StreamingHost[257];
	uint32_t StreamingPort;
	uint32_t StreamingSessionID;
	char FileTransferURL[257];
	char FileTransferUsername[65];
	char FileTransferPassword[65];
	char ControlFileFormat[129];
	uint32_t ParameterNumberOfEntries;
} rdm_BulkDataProf_t;

typedef struct rdm_BulkDataProfParam_s {   // RDM_OID_BULK_DATA_PROF_PARAM 
	char Reference[257];
} rdm_BulkDataProfParam_t;

typedef struct rdm_RomConvert_s {   // RDM_OID_ROM_CONVERT 
	int ConvertBit;
} rdm_RomConvert_t;

typedef struct rdm_Schedule_s {   // RDM_OID_SCHEDULE 
	bool Enable;
	char Name[33];
	char Description[257];
	uint32_t Days;
	char TimeStartDate[17];
	uint32_t TimeStartHour;
	uint32_t TimeStartMin;
	char TimeStopDate[17];
	uint32_t TimeStopHour;
	uint32_t TimeStopMin;
} rdm_Schedule_t;

typedef struct rdm_EmailNotify_s {   // RDM_OID_EMAIL_NOTIFY 
} rdm_EmailNotify_t;

typedef struct rdm_MailService_s {   // RDM_OID_MAIL_SERVICE 
	bool Enable;
	char SMTPServerAddress[65];
	uint32_t SMTPServerPort;
	char AuthUser[65];
	char AuthPass[65];
	char EmailAddress[129];
	char SMTPSecurity[17];
	bool RequiresTLS;
} rdm_MailService_t;

typedef struct rdm_MailEventCfg_s {   // RDM_OID_MAIL_EVENT_CFG 
	bool Enable;
	char Event[65];
	char EmailTo[257];
	char EmailSubject[129];
	char EmailBody[1025];
	char SericeRef[129];
} rdm_MailEventCfg_t;

typedef struct rdm_ParenCtl_s {   // RDM_OID_PAREN_CTL 
	bool Enable;
} rdm_ParenCtl_t;

typedef struct rdm_ParenCtlProf_s {   // RDM_OID_PAREN_CTL_PROF 
	bool Enable;
	char Name[65];
	bool WebRedirect;
	char ServicePolicy[12];
	uint32_t Type;
	char MACAddressList[129];
	char IPAddressList[129];
	char ScheduleRuleList[65];
	char URLFilter[581];
	char NetworkServiceList[1025];
	char ContentFilterList[65];
	char Id[65];
} rdm_ParenCtlProf_t;

typedef struct rdm_Ieee8021ag_s {   // RDM_OID_IEEE8021AG 
	bool Enabled;
	bool Y1731Mode;
	char Interface[23];
	char MDName[129];
	char MAID[129];
	uint32_t LMPID;
	uint32_t RMPID;
	bool CCMEnabled;
	int MDLevel;
	uint32_t CCMInterval;
	bool IsPtmLink;
	int VLANID;
	char DestMacAddress[18];
	bool SendLoopBack;
	int LoopBackResult;
	int LinkTraceTTL;
	bool SendLinkTrace;
	char LinkTraceResult[321];
	uint32_t TmsPid;
} rdm_Ieee8021ag_t;

typedef struct rdm_Ieee8023ah_s {   // RDM_OID_IEEE8023AH 
	bool Enabled;
	char Interface[23];
	bool VariableRetrievalEnabled;
	bool LinkEventsEnabled;
	bool RemoteLoopbackEnabled;
	bool ActiveModeEnabled;
	bool AutoEventEnabled;
	uint32_t OAMID;
	uint32_t TmsPid;
} rdm_Ieee8023ah_t;

typedef struct rdm_ZyExt_s {   // RDM_OID_ZY_EXT 
	bool WPSRunning;
	uint32_t WPSApIndex;
	char WPSRunningStatus[257];
} rdm_ZyExt_t;

typedef struct rdm_DnsRtEntry_s {   // RDM_OID_DNS_RT_ENTRY 
	bool Enable;
	char DomainName[257];
	char RouteInterface[33];
	char Interface[257];
	char DNSServers[65];
	char SubnetMask[17];
	uint32_t RouteMARK;
	char Adder[257];
} rdm_DnsRtEntry_t;

typedef struct rdm_DnsEntry_s {   // RDM_OID_DNS_ENTRY 
	char HostName[257];
	char IPv4Address[17];
} rdm_DnsEntry_t;

typedef struct rdm_DDns_s {   // RDM_OID_D_DNS 
	bool Enable;
	char ServiceProvider[33];
	char DDNSType[9];
	char HostName[257];
	char UserName[257];
	char Password[65];
	uint32_t IPAddressPolicy;
	char UserIPAddress[17];
	char Interface[33];
	bool Wildcard;
	bool Offline;
	char AuthenticationResult[17];
	char UpdatedTime[17];
	char DynamicIP[129];
	char UpdateURL[257];
	char ConnectionType[13];
} rdm_DDns_t;

typedef struct rdm_AutoProv_s {   // RDM_OID_AUTO_PROV 
	bool Enable;
	char ServerIP[65];
	uint32_t ServerPort;
	char Directory[65];
	uint32_t RetryTimer;
	uint32_t ExpireTimer;
	uint32_t KeyType;
	char Key[65];
} rdm_AutoProv_t;

typedef struct rdm_SpeedTest_s {   // RDM_OID_SPEED_TEST 
	bool Start;
	char UploadSpeedResult[17];
	char DownloadSpeedResult[17];
} rdm_SpeedTest_t;

typedef struct rdm_WifiQsteer_s {   // RDM_OID_WIFI_QSTEER 
	bool Enable;
	uint32_t MinPhyRate;
	uint32_t MaxPhyRate;
	uint32_t WPS_Mode;
} rdm_WifiQsteer_t;

typedef struct rdm_ZyHostNameReplace_s {   // RDM_OID_ZY_HOST_NAME_REPLACE 
	bool Enable;
} rdm_ZyHostNameReplace_t;

typedef struct rdm_PptpCfg_s {   // RDM_OID_PPTP_CFG 
	bool pptpEnable;
	char pptpName[65];
	char pptpServer[65];
	char pptpUsername[257];
	char pptpPassword[65];
	char pptpLanInf[257];
	char pptpSecurity[257];
	int pptpStatus;
	char pptpLocalIP[129];
	char pptpRemoteIP[129];
	bool pptpOriAlgStatus;
} rdm_PptpCfg_t;

typedef struct rdm_EogreCfg_s {   // RDM_OID_EOGRE_CFG 
	bool Enable;
	char Name[65];
	char RemoteIP[16];
	char LanInf[257];
	char LocalIP[16];
	char LocalMac[18];
} rdm_EogreCfg_t;

typedef struct rdm_LanDev_s {   // RDM_OID_LAN_DEV 
	uint32_t HostNumberOfEntries;
	char LinkInterface[257];
	char IpInterface[257];
} rdm_LanDev_t;

typedef struct rdm_EasyMesh_s {   // RDM_OID_EASY_MESH 
	bool Enable;
} rdm_EasyMesh_t;

typedef struct rdm_MacAddressTable_s {   // RDM_OID_MAC_ADDRESS_TABLE 
	char Interface[257];
	bool Upstream;
	char Type[57];
	uint32_t MaxAddrNum;
	char AddrList[1601];
	uint32_t AddrNum;
} rdm_MacAddressTable_t;

typedef struct rdm_ZyIgmp_s {   // RDM_OID_ZY_IGMP 
	bool Enable;
	uint32_t IgmpVersion;
	uint32_t QueryInterval;
	uint32_t QueryResponseInterval;
	uint32_t LastMemberQueryInterval;
	uint32_t RobustnessValue;
	uint32_t MaxGroups;
	uint32_t MaxSources;
	uint32_t MaxMembers;
	uint32_t LanToLanEnable;
	uint32_t FastLeave;
	uint32_t JoinImmediate;
	uint32_t BridgeAdmissionFilter;
	uint32_t SnoopingEnable;
	char Interface[513];
	char ifName[321];
	char Status[19];
	char SnoopingBridgeIfName[101];
	bool NoIpSrcAddressEnable;
} rdm_ZyIgmp_t;

typedef struct rdm_ZySnmp_s {   // RDM_OID_ZY_SNMP 
	bool Enable;
	uint32_t Port;
	char ROCommunity[51];
	char RWCommunity[51];
	char TrapCommunity[51];
} rdm_ZySnmp_t;

typedef struct rdm_TrapAddr_s {   // RDM_OID_TRAP_ADDR 
	char Host[256];
	uint32_t Port;
	uint32_t TarpVer;
} rdm_TrapAddr_t;

typedef struct rdm_ZyMld_s {   // RDM_OID_ZY_MLD 
	bool Enable;
	uint32_t MldVersion;
	uint32_t QueryInterval;
	uint32_t QueryResponseInterval;
	uint32_t LastMemberQueryInterval;
	uint32_t RobustnessValue;
	uint32_t LanToLanEnable;
	uint32_t MaxGroups;
	uint32_t MaxSources;
	uint32_t MaxMembers;
	uint32_t FastLeave;
	uint32_t SnoopingEnable;
	char Interface[513];
	char ifName[321];
	char Status[19];
	char SnoopingBridgeIfName[101];
} rdm_ZyMld_t;

typedef struct rdm_ZyLogCfg_s {   // RDM_OID_ZY_LOG_CFG 
	uint32_t LoginGroupNumberOfEntries;
	bool LoginGroupConfigurable;
	uint32_t MaxiumLoginAccountNumber;
} rdm_ZyLogCfg_t;

typedef struct rdm_ZyLogCfgGp_s {   // RDM_OID_ZY_LOG_CFG_GP 
	char Level[9];
	char GP_Privilege[65];
	char Page[2049];
	char BasicPage[2049];
	char HiddenPage[2049];
} rdm_ZyLogCfgGp_t;

typedef struct rdm_ZyLogCfgGpAccount_s {   // RDM_OID_ZY_LOG_CFG_GP_ACCOUNT 
	bool Enabled;
	bool EnableQuickStart;
	char Page[2049];
	char Username[17];
	char Password[257];
	char DefaultPassword[257];
	char DefaultGuiPassword[257];
	bool ResetDefaultPassword;
	char shadow[513];
	char smbpasswd[513];
	bool ConfigAccountFromWAN;
	char PasswordHash[17];
	uint32_t DefPwLength;
	uint32_t AccountCreateTime;
	uint32_t AccountRetryTime;
	uint32_t AccountIdleTime;
	uint32_t AccountLockTime;
	char RemoHostAddress[49];
	bool DotChangeDefPwd;
	bool ShowSkipBtnInChgDefPwdPage;
	bool AutoGenPwdBySn;
	bool AutoShowQuickStart;
	bool GetConfigByFtp;
	char Privilege[65];
	char Stored[65];
	char Salt[65];
	char RoleList[33];
	char RemoteAccessPrivilege[65];
	char OldDefaultPassword[257];
	char CardOrder[513];
	char ThemeColor[17];
	char HiddenPage[2049];
	char SshKeyBaseAuthPublicKey[4097];
} rdm_ZyLogCfgGpAccount_t;

typedef struct rdm_ZyMacFilter_s {   // RDM_OID_ZY_MAC_FILTER 
	uint32_t MaxNumberOfEntries;
	bool Enable;
	bool Restrict;
} rdm_ZyMacFilter_t;

typedef struct rdm_ZyMacFilterWhiteList_s {   // RDM_OID_ZY_MAC_FILTER_WHITE_LIST 
	bool Enable;
	char MACAddress[18];
	char HostName[33];
} rdm_ZyMacFilterWhiteList_t;

typedef struct rdm_WlanSchedulerAccess_s {   // RDM_OID_WLAN_SCHEDULER_ACCESS 
	bool Enable;
	bool AutoSwitchWiFiRadio;
	bool MasterShip;
} rdm_WlanSchedulerAccess_t;

typedef struct rdm_VcAutoHunt_s {   // RDM_OID_VC_AUTO_HUNT 
	bool Enable;
	bool DebugEnable;
	uint32_t SendPatternPeriod;
	uint32_t SendPatternExpire;
	uint32_t NumPvcSet;
} rdm_VcAutoHunt_t;

typedef struct rdm_VcHuntInfo_s {   // RDM_OID_VC_HUNT_INFO 
	int PvcId;
	uint32_t NumHuntRule;
} rdm_VcHuntInfo_t;

typedef struct rdm_VcHuntRule_s {   // RDM_OID_VC_HUNT_RULE 
	char HuntAddrs[33];
	uint32_t HuntServices;
} rdm_VcHuntRule_t;

typedef struct rdm_VlanAutoHunt_s {   // RDM_OID_VLAN_AUTO_HUNT 
	bool Enable;
	bool DebugEnable;
	uint32_t MaxNumOfRetry;
	uint32_t NumHuntInfo;
} rdm_VlanAutoHunt_t;

typedef struct rdm_VlanHuntInfo_s {   // RDM_OID_VLAN_HUNT_INFO 
	uint32_t NumHuntRule;
	char Interface[33];
} rdm_VlanHuntInfo_t;

typedef struct rdm_VlanHuntRule_s {   // RDM_OID_VLAN_HUNT_RULE 
	uint32_t HuntVlanId;
	uint32_t HuntService;
} rdm_VlanHuntRule_t;

typedef struct rdm_Lang_s {   // RDM_OID_LANG 
	char Language[17];
} rdm_Lang_t;

typedef struct rdm_RemoMgmt_s {   // RDM_OID_REMO_MGMT 
	uint32_t ServiceNumberOfEntries;
	char BoundWANInterfaceList[257];
	int SPRemoteTimer;
} rdm_RemoMgmt_t;

typedef struct rdm_RemoSrv_s {   // RDM_OID_REMO_SRV 
	char Name[33];
	bool Enable;
	int Protocol;
	int Port;
	char Mode[21];
	char OldMode[21];
	bool RestartDeamon;
	uint32_t LifeTime;
	char BoundInterfaceList[129];
	bool TrustAll;
	bool DisableSshPasswordLogin;
} rdm_RemoSrv_t;

typedef struct rdm_RemoSrvTrustDomain_s {   // RDM_OID_REMO_SRV_TRUST_DOMAIN 
	bool Enable;
	char IPAddress[49];
	char SubnetMask[16];
} rdm_RemoSrvTrustDomain_t;

typedef struct rdm_SpRemoSrv_s {   // RDM_OID_SP_REMO_SRV 
	char Name[33];
	bool Enable;
	bool TimerEnable;
	int Protocol;
	int Port;
	char Mode[11];
	char OldMode[11];
	bool RestartDeamon;
	uint32_t LifeTime;
	char BoundInterfaceList[129];
	bool TrustAll;
} rdm_SpRemoSrv_t;

typedef struct rdm_SpRemoSrvTrustDomain_s {   // RDM_OID_SP_REMO_SRV_TRUST_DOMAIN 
	bool Enable;
	char IPAddress[49];
	char SubnetMask[16];
	char WebDoaminName[65];
} rdm_SpRemoSrvTrustDomain_t;

typedef struct rdm_RemoMgmtTrustDomain_s {   // RDM_OID_REMO_MGMT_TRUST_DOMAIN 
	bool Enable;
	char IPAddress[49];
	char SubnetMask[16];
} rdm_RemoMgmtTrustDomain_t;

typedef struct rdm_SpTrustDomain_s {   // RDM_OID_SP_TRUST_DOMAIN 
	bool Enable;
	char IPAddress[49];
	char SubnetMask[16];
	char WebDomainName[65];
} rdm_SpTrustDomain_t;

typedef struct rdm_NetworkSrv_s {   // RDM_OID_NETWORK_SRV 
	uint32_t ServiceNumberOfEntries;
} rdm_NetworkSrv_t;

typedef struct rdm_NetworkSrvGp_s {   // RDM_OID_NETWORK_SRV_GP 
	char Name[33];
	char Description[257];
	int Protocol;
	int SourcePort;
	int SourcePortRangeMax;
	int DestPort;
	int DestPortRangeMax;
	int ICMPType;
	int ICMPTypeCode;
} rdm_NetworkSrvGp_t;

typedef struct rdm_SystemInfo_s {   // RDM_OID_SYSTEM_INFO 
	char HostName[65];
	bool IsHostNameModify;
	char DomainName[65];
	char Contact[101];
	char Location[51];
	bool CBT_AccountReset;
	char OnlineGuide[129];
	char X_ZYXEL_LoginBanner[513];
	bool ledAllEnable;
	bool wanledEnable;
} rdm_SystemInfo_t;

typedef struct rdm_GponInfo_s {   // RDM_OID_GPON_INFO 
	char RxPowerSignal[17];
	char TxPowerSignal[17];
	char Temperature[17];
	char SFP_Vendor[17];
	char SFP_Model[17];
	char SFP_Serial[17];
	bool SFP_Presence;
} rdm_GponInfo_t;

typedef struct rdm_LogSetting_s {   // RDM_OID_LOG_SETTING 
	bool Enable;
	bool ZCFG_LOG_Enable;
	char LogMode[33];
	char LogServer[129];
	uint32_t UDPPort;
	uint32_t Interval;
	char RemoteLogFormat[256];
} rdm_LogSetting_t;

typedef struct rdm_LogClassify_s {   // RDM_OID_LOG_CLASSIFY 
	char Name[31];
	char Describe[51];
	char File[51];
} rdm_LogClassify_t;

typedef struct rdm_LogCategory_s {   // RDM_OID_LOG_CATEGORY 
	bool Enable;
	char Name[31];
	char Describe[51];
	char Filter[256];
	uint32_t Level;
	char LocalLogFormat[256];
} rdm_LogCategory_t;

typedef struct rdm_ChangeIconName_s {   // RDM_OID_CHANGE_ICON_NAME 
	char HostName[65];
	char MacAddress[65];
	char DeviceIcon[33];
	bool Internet_Blocking_Enable;
	bool BrowsingProtection;
	bool TrackingProtection;
	bool IOTProtection;
	uint32_t X_ZYXEL_FirstSeen;
	uint32_t X_ZYXEL_LastSeen;
	char SourceVendorClassID[256];
	char IPAddress[49];
	char IPAddress6[49];
} rdm_ChangeIconName_t;

typedef struct rdm_PortMirror_s {   // RDM_OID_PORT_MIRROR 
	char MonitorInterface[65];
	char MirrorInterface[65];
	bool Direction;
	bool Status;
} rdm_PortMirror_t;

typedef struct rdm_VlanGroup_s {   // RDM_OID_VLAN_GROUP 
	bool Enable;
	char GroupName[129];
	uint32_t VlanId;
	char BrRefKey[9];
	char IntfList[65];
	char TagList[65];
} rdm_VlanGroup_t;

typedef struct rdm_STBVendorID_s {   // RDM_OID_S_T_B_VENDOR_I_D 
	char STBVendorID1[65];
	char STBVendorID2[65];
	char STBVendorID3[65];
	char STBVendorID4[65];
	char STBVendorID5[65];
} rdm_STBVendorID_t;

typedef struct rdm_TFTPSrvName_s {   // RDM_OID_T_F_T_P_SRV_NAME 
	char TFTPServerName[65];
} rdm_TFTPSrvName_t;

typedef struct rdm_Tr064_s {   // RDM_OID_TR064 
	bool Enable;
	uint32_t Issue;
	char DataModels[33];
	char HttpProtocols[33];
	uint32_t HttpDescriptPort;
	uint32_t HttpsDescriptPort;
} rdm_Tr064_t;

typedef struct rdm_Acl_s {   // RDM_OID_ACL 
} rdm_Acl_t;

typedef struct rdm_ControlPoint_s {   // RDM_OID_CONTROL_POINT 
	char Name[33];
	char Alias[129];
	char ID[65];
	char RoleList[33];
} rdm_ControlPoint_t;

typedef struct rdm_Actions_s {   // RDM_OID_ACTIONS 
	char Name[33];
	char RoleList[33];
	char RestrictedRoleList[33];
} rdm_Actions_t;

typedef struct rdm_ZyWWANBackup_s {   // RDM_OID_ZY_W_W_A_N_BACKUP 
	bool Enable;
	char Status[33];
	char PackageVersion[33];
	char Interface[257];
	char PPPInterface[257];
	char ETHInterface[257];
	char DeviceNumber[9];
	char VID[9];
	char PID[9];
	char StartTime[33];
	char FinishTime[33];
	char Manufacturer[129];
	char DialNumber[33];
	char APN[101];
	char PIN[33];
	char PUK[33];
	char NewPIN[33];
} rdm_ZyWWANBackup_t;

typedef struct rdm_ZyWWANPingCheck_s {   // RDM_OID_ZY_W_W_A_N_PING_CHECK 
	bool Enable;
	uint32_t Interval;
	uint32_t FailLimit;
	bool DefaultGateway;
	char Destination[65];
} rdm_ZyWWANPingCheck_t;

typedef struct rdm_ZyWWANBudgetControl_s {   // RDM_OID_ZY_W_W_A_N_BUDGET_CONTROL 
	bool Enable;
	char IMSI[33];
	uint32_t SaveTimeValue;
	uint32_t SaveTxByteValue;
	uint32_t SaveRxByteValue;
	uint32_t SaveTxPktValue;
	uint32_t SaveRxPktValue;
	bool TimeEnable;
	uint32_t TimeValue;
	bool ByteEnable;
	uint32_t ByteValue;
	char ByteMode[33];
	bool PktEnable;
	uint32_t PktValue;
	char PktMode[33];
	uint32_t ResetDay;
	bool NeedAutoReset;
	bool ResetNow;
	bool TimeActionEnable;
	uint32_t TimeActionValue;
	bool ByteActionEnable;
	uint32_t ByteActionValue;
	bool PktActionEnable;
	uint32_t PktActionValue;
	bool DropWWAN;
	bool LogEnable;
	uint32_t LogInterval;
} rdm_ZyWWANBudgetControl_t;

typedef struct rdm_ZyWWANStat_s {   // RDM_OID_ZY_W_W_A_N_STAT 
	char ServiceProvider[33];
	char SignalStrength[33];
	char RemainingPIN[33];
	char ConnectionUptime[33];
	char Manufacturer[33];
	char Model[33];
	char FWVersion[33];
	char SIMIMSI[33];
	char Technology[33];
} rdm_ZyWWANStat_t;

typedef struct rdm_ZySamba_s {   // RDM_OID_ZY_SAMBA 
	bool Enable;
	char PidFileName[257];
	uint32_t MaxProcesses;
} rdm_ZySamba_t;

typedef struct rdm_ZySambaDir_s {   // RDM_OID_ZY_SAMBA_DIR 
	bool X_ZYXEL_Public;
	bool X_ZYXEL_Browseable;
	char X_ZYXEL_Hostname[65];
	char X_ZYXEL_FolderName[129];
	char X_ZYXEL_ValidUsers[65];
	char X_ZYXEL_Comment[129];
	char X_ZYXEL_RootPath[65];
	char X_ZYXEL_Path[257];
	char X_ZYXEL_Portnum[6];
} rdm_ZySambaDir_t;

typedef struct rdm_GuiCustomization_s {   // RDM_OID_GUI_CUSTOMIZATION 
	uint32_t Flag1;
	uint32_t Flag2;
	uint32_t Flag3;
	uint32_t FlagVoIP1;
	uint32_t CbtGuestWifi;
	uint32_t WANmacOffset;
	bool BlockSpecialChar;
	char BlockChar[129];
	bool AllowFilter;
	char AllowCharList[129];
	bool HideAutoOnlineFWUpgradeGUI;
	bool EthWanAsLan;
	bool HidePasswordUnmask;
	bool HideCCWan;
	bool HideChangeDefault;
	bool HideSkipPassword;
	bool USB30Support;
} rdm_GuiCustomization_t;

typedef struct rdm_InputCheckList_s {   // RDM_OID_INPUT_CHECK_LIST 
	char inputID[129];
	char BlockChar[129];
	char RuleString[257];
	int minLength;
	int maxLength;
	char passwordStrength[129];
} rdm_InputCheckList_t;

typedef struct rdm_FeatureFlag_s {   // RDM_OID_FEATURE_FLAG 
	uint32_t Flag;
	char Customer[33];
	uint32_t WebRedirect;
	uint32_t DisableWifiHWButton;
	char DHCPClientOption42ConfigOptions[257];
	bool checkDuplicateVlan;
	bool DownloadScriptTR69;
	char WANPriority[17];
	char DHCPOption61Mode[31];
	char DefaultRoutSelectMethod[31];
	uint32_t SfpDelayTimes;
	uint32_t SipDelayTimes;
	bool AdminRandomPassword;
	uint32_t AdminRandomPasswordMode;
	bool FactoryResetOnUpgrade;
	bool InternetLEDBlinking;
} rdm_FeatureFlag_t;

typedef struct rdm_ZyOption125_s {   // RDM_OID_ZY_OPTION125 
	bool Enable;
} rdm_ZyOption125_t;

typedef struct rdm_ZyVendorSpecific_s {   // RDM_OID_ZY_VENDOR_SPECIFIC 
	char Option125ManufacturerOUI[256];
	char Option125SerialNumber[256];
	char Option125ProductClass[256];
	bool Option125HexBox;
} rdm_ZyVendorSpecific_t;

typedef struct rdm_ZyIppCfg_s {   // RDM_OID_ZY_IPP_CFG 
	bool Enable;
	char IppMake[33];
	char IppDevice[33];
	char IppName[33];
} rdm_ZyIppCfg_t;

typedef struct rdm_Gpon_s {   // RDM_OID_GPON 
} rdm_Gpon_t;

typedef struct rdm_Onu_s {   // RDM_OID_ONU 
	char Version[65];
	char VendorId[26];
	char SerialNumber[65];
	char OnuType[9];
	char Password[26];
	char TMOption[65];
	char ONUSurvivalTime[65];
	char ExtendedTClayer[65];
	char EquipmentId[65];
	char OMCCVersion[26];
	char VendorProCode[65];
	char SecurityCap[65];
	char TotalPQNum[65];
	char TotalTSNum[65];
	char TotalGEMPortNum[65];
	char ConnectivityCap[65];
	char QosConfFlex[65];
	char MaxPorts[65];
	char PortList1[65];
	char EnhancedPSK[53];
	char ModelName[17];
	char SecurityMode[33];
	char OperationalState[33];
	char temperature[9];
	char voltage[6];
	char txPower[6];
	char rxPower[6];
	char EmergencyState[33];
} rdm_Onu_t;

typedef struct rdm_Ani_s {   // RDM_OID_ANI 
	char TotalTCONTNum[65];
	char SRIndication[65];
	char GEMBlockLength[65];
	char PiggybackDBA[65];
	char SFThd[26];
	char SDThd[26];
	char ONUResponseTime[65];
	char LowerRxOpticalThd[65];
	char UpperRxOpticalThd[65];
	char LowerTxOpticalThd[65];
	char UpperTxOpticalThd[65];
	char LowerTemperatureThd[33];
	char UpperTemperatureThd[33];
	char LowerLaserBiasThd[33];
	char UpperLaserBiasThd[33];
	char LowerVoltageThd[33];
	char UpperVoltageThd[33];
	char PhyTransParameters[129];
} rdm_Ani_t;

typedef struct rdm_Olt_s {   // RDM_OID_OLT 
	char VendorId[65];
	char EquipmentId[65];
	char Version[17];
	char ToD[65];
} rdm_Olt_t;

typedef struct rdm_Capability_s {   // RDM_OID_CAPABILITY 
	char OperatorID[26];
	char SpecVersion[26];
	char ONU_PowerCtr[26];
} rdm_Capability_t;

typedef struct rdm_Loidauth_s {   // RDM_OID_LOIDAUTH 
	char LOID[65];
	char Password[65];
	char AuthStatus[3];
} rdm_Loidauth_t;

typedef struct rdm_Softimage_s {   // RDM_OID_SOFTIMAGE 
	char Version[65];
	char Committed[9];
	char Active[9];
	char Valid[9];
} rdm_Softimage_t;

typedef struct rdm_Pm_s {   // RDM_OID_PM 
	char classId[17];
	char portId[17];
	char dataFlag[17];
	char attrIndex[17];
	char attrData[65];
} rdm_Pm_t;

typedef struct rdm_Common_s {   // RDM_OID_COMMON 
	char Enable[17];
	char CurrentAttribute[33];
} rdm_Common_t;

typedef struct rdm_Xpon_s {   // RDM_OID_XPON 
	char phyStatus[17];
	char trafficStatus[17];
	char GponBindIfc[17];
	char StartXpon[17];
	char LanVidTransparent[17];
} rdm_Xpon_t;

typedef struct rdm_Linkcfg_s {   // RDM_OID_LINKCFG 
	char Mode[65];
	char LinkState[65];
} rdm_Linkcfg_t;

typedef struct rdm_Iphost_s {   // RDM_OID_IPHOST 
	char WanIf[33];
	char commitWan[9];
} rdm_Iphost_t;

typedef struct rdm_OmciCfg_s {   // RDM_OID_OMCI_CFG 
} rdm_OmciCfg_t;

typedef struct rdm_Omci_s {   // RDM_OID_OMCI 
	char Ready[65];
	char interface[65];
	char gemportlist[65];
	char handleifc[65];
	char totalGemPort[65];
	char TransferFlag[17];
	char macBridgePort[33];
} rdm_Omci_t;

typedef struct rdm_Gemport_s {   // RDM_OID_GEMPORT 
	char AllocId[65];
	char PortId[65];
	char PQPointerDown[65];
	char Number[9];
	char EncryptionState[9];
} rdm_Gemport_t;

typedef struct rdm_Tcont_s {   // RDM_OID_TCONT 
	char Policy[65];
	char Number[9];
} rdm_Tcont_t;

typedef struct rdm_Trtcm_s {   // RDM_OID_TRTCM 
	char channel[65];
	char cir[65];
	char pir[65];
	char cbs[65];
	char pbs[65];
} rdm_Trtcm_t;

typedef struct rdm_Qoscfg_s {   // RDM_OID_QOSCFG 
	char QOS[65];
	char QOSType[65];
	char QOSCfg[65];
	char QOSMask[65];
	char WeightType[65];
	char WeightScale[65];
} rdm_Qoscfg_t;

typedef struct rdm_QosValue_s {   // RDM_OID_QOS_VALUE 
	char Value[65];
} rdm_QosValue_t;

typedef struct rdm_Cngstcfg_s {   // RDM_OID_CNGSTCFG 
	char Congest[65];
	char CongestCfg[65];
	char CongestMask[65];
	char CongestTrtcmMode[65];
	char CongestDeiDropMode[65];
	char CongestThredMode[65];
	char CongestScale[65];
	char CongestDropProbability[65];
} rdm_Cngstcfg_t;

typedef struct rdm_CongestThredValue_s {   // RDM_OID_CONGEST_THRED_VALUE 
	char Value[65];
} rdm_CongestThredValue_t;

typedef struct rdm_Trtcmcfg_s {   // RDM_OID_TRTCMCFG 
	char TrtcmParam[65];
	char TrtcmMask[65];
	char TrtcmCfg[65];
	char TrtcmScale[65];
} rdm_Trtcmcfg_t;

typedef struct rdm_TrtcmValue_s {   // RDM_OID_TRTCM_VALUE 
	char Value[65];
} rdm_TrtcmValue_t;

typedef struct rdm_Queue_s {   // RDM_OID_QUEUE 
	char DropMode[9];
} rdm_Queue_t;

typedef struct rdm_OntGeneric_s {   // RDM_OID_ONT_GENERIC 
	char ConfigStatus[9];
} rdm_OntGeneric_t;

typedef struct rdm_ZyOneConnect_s {   // RDM_OID_ZY_ONE_CONNECT 
	bool Enable;
	bool X_ZYXEL_AP_Approve_Flag;
	char X_ZYXEL_APP_Customer[17];
} rdm_ZyOneConnect_t;

typedef struct rdm_OneConnectInternetAccessMasterSwitch_s {   // RDM_OID_ONE_CONNECT_INTERNET_ACCESS_MASTER_SWITCH 
	bool Enable;
	int Count;
} rdm_OneConnectInternetAccessMasterSwitch_t;

typedef struct rdm_OneConnectInternetAccessRule_s {   // RDM_OID_ONE_CONNECT_INTERNET_ACCESS_RULE 
	bool Enable;
	char Name[65];
	char NetAccess[9];
	char BlockMAC[18];
} rdm_OneConnectInternetAccessRule_t;

typedef struct rdm_OneConnectPCGeneral_s {   // RDM_OID_ONE_CONNECT_P_C_GENERAL 
	bool Enable;
	bool PCMode;
	int Count;
} rdm_OneConnectPCGeneral_t;

typedef struct rdm_OneConnectPCRule_s {   // RDM_OID_ONE_CONNECT_P_C_RULE 
	bool Enable;
	char Name[65];
	char Mode[9];
	char BlockMAC[18];
	char BlockIP[18];
	uint32_t StartHour;
	uint32_t StartMin;
	uint32_t StopHour;
	uint32_t StopMin;
	char Days[33];
} rdm_OneConnectPCRule_t;

typedef struct rdm_OnlineFWUpgrade_s {   // RDM_OID_ONLINE_F_W_UPGRADE 
	bool Enable;
	char SystemModelName[65];
	char FWInfoURL[1025];
	char FWFileName[65];
	char FWVersion[65];
	char FWReleaseDate[32];
	char FWSize[1025];
	uint32_t HttpSevrPort;
	char FWURL[1025];
} rdm_OnlineFWUpgrade_t;

typedef struct rdm_LandingPage_s {   // RDM_OID_LANDING_PAGE 
	bool Enable;
	char URL[257];
} rdm_LandingPage_t;

typedef struct rdm_PowerMgmt_s {   // RDM_OID_POWER_MGMT 
	bool Enable;
	bool curDSL;
	bool curETH;
	bool curLAN1;
	bool curLAN2;
	bool curLAN3;
	bool curLAN4;
	bool curLED;
	bool DSL;
	bool ETH;
	bool LAN1;
	bool LAN2;
	bool LAN3;
	bool LAN4;
	bool LED;
} rdm_PowerMgmt_t;

typedef struct rdm_PowerSchedule_s {   // RDM_OID_POWER_SCHEDULE 
	bool Enable;
	char Name[65];
	char Ref[65];
	char job[1025];
	int count;
} rdm_PowerSchedule_t;

typedef struct rdm_ZyLoopGuard_s {   // RDM_OID_ZY_LOOP_GUARD 
	bool Enable;
	char RecoveryTime[17];
	bool RebootAfterRecovery;
} rdm_ZyLoopGuard_t;

typedef struct rdm_ZyProximitySensor_s {   // RDM_OID_ZY_PROXIMITY_SENSOR 
	bool Enable;
} rdm_ZyProximitySensor_t;

typedef struct rdm_ZySfpManagement_s {   // RDM_OID_ZY_SFP_MANAGEMENT 
	char Status[33];
	uint32_t Timer;
} rdm_ZySfpManagement_t;

typedef struct rdm_ZyResetAdmin_s {   // RDM_OID_ZY_RESET_ADMIN 
	char ResetPassword[257];
} rdm_ZyResetAdmin_t;

typedef struct rdm_OiWizard_s {   // RDM_OID_OI_WIZARD 
	uint32_t Status;
	char Region[9];
	char CorporateRegion[33];
	char Username[65];
	char Password[65];
	uint32_t OiWifiEnable;
	int OiWifiVLANID;
} rdm_OiWizard_t;

typedef struct rdm_ZyDataUsage_s {   // RDM_OID_ZY_DATA_USAGE 
	char DataUsageUpdate[17];
} rdm_ZyDataUsage_t;

typedef struct rdm_ZyDataUsageLan_s {   // RDM_OID_ZY_DATA_USAGE_LAN 
	char Timestamp[65];
	char Upload_Mbps[17];
	char Download_Mbps[17];
} rdm_ZyDataUsageLan_t;

typedef struct rdm_ZyDataUsageWan_s {   // RDM_OID_ZY_DATA_USAGE_WAN 
	char Timestamp[65];
	char Upload_Mbps[17];
	char Download_Mbps[17];
} rdm_ZyDataUsageWan_t;

typedef struct rdm_Iperf_s {   // RDM_OID_IPERF 
	bool Enable;
	char Status[33];
	char Protocol[257];
	uint32_t Port;
} rdm_Iperf_t;

typedef struct rdm_ZlogConfig_s {   // RDM_OID_ZLOG_CONFIG 
	bool Enable;
	char Status[21];
} rdm_ZlogConfig_t;

typedef struct rdm_ZlogCategory_s {   // RDM_OID_ZLOG_CATEGORY 
	bool Enable;
	uint32_t Severity;
	bool Console;
	bool UsbFile;
	char Filename[129];
	bool SyslogServer;
	char SyslogServerIp[129];
	uint32_t SyslogServerPort;
	bool Userdefinefile;
	char FullPath[129];
	char Name[31];
	char Describe[51];
	char Filter[256];
} rdm_ZlogCategory_t;

typedef struct rdm_HomeCyberSecurity_s {   // RDM_OID_HOME_CYBER_SECURITY 
	bool Enable;
	bool BrowsingProtection;
	bool TrackingProtection;
	bool IoTProtection;
	char URLFilterList[65];
} rdm_HomeCyberSecurity_t;

typedef struct rdm_ContentFilter_s {   // RDM_OID_CONTENT_FILTER 
	bool Enable;
	char Name[33];
	char Description[257];
	bool AdultContent;
	bool Drugs;
	bool AlcoholandTobacco;
	bool Disturbing;
	bool Gambling;
	bool Illegal;
	bool IllegalDownloads;
	bool Violence;
	bool Hate;
	bool Weapons;
	bool Dating;
	bool TimeShoppingandAuctions;
	bool VideoStreamingServices;
	bool SocialNetworks;
	bool Anonymizers;
	bool Unknown;
} rdm_ContentFilter_t;

typedef struct rdm_URLFilter_s {   // RDM_OID_U_R_L_FILTER 
	bool Enable;
	char Name[33];
	char Description[257];
	char FilterIndex[257];
} rdm_URLFilter_t;

typedef struct rdm_WhiteURLFilter_s {   // RDM_OID_WHITE_U_R_L_FILTER 
	char Name[33];
	char FilterIndex[257];
	char Whitelist[65];
} rdm_WhiteURLFilter_t;

typedef struct rdm_BlackURLFilter_s {   // RDM_OID_BLACK_U_R_L_FILTER 
	char Name[33];
	char FilterIndex[257];
	char Blacklist[65];
} rdm_BlackURLFilter_t;

typedef struct rdm_ZyLicnse_s {   // RDM_OID_ZY_LICNSE 
	bool Cyber_Security_FSC;
} rdm_ZyLicnse_t;

typedef struct rdm_Mos_s {   // RDM_OID_MOS 
} rdm_Mos_t;

typedef struct rdm_MosUsrCfg_s {   // RDM_OID_MOS_USR_CFG 
	uint32_t PotsPortCount;
	uint32_t EthPortCount;
	uint32_t XgEthPortCount;
	uint32_t EthPhyPort1;
	uint32_t EthPhyPort2;
	uint32_t EthPhyPort3;
	uint32_t EthPhyPort4;
	uint32_t PonPortCount;
	char OnuVersion[26];
	uint32_t ImageCount;
	uint32_t VeipCount;
	uint32_t LctCount;
	uint32_t WlanPortCount;
	uint32_t VideoCount;
	uint32_t TcontCount;
	uint32_t GemPortCount;
	uint32_t PriorityQueueCount;
	uint32_t TrafficSchedulerCount;
	uint32_t PriorityQueueCountPerTcont;
	uint32_t PriorityQueueCountPerEthPort;
	uint32_t FlowCount;
	bool CaptureCmd;
	bool CaptureRaw;
	bool CaptureRxtx;
	bool FakeOk;
	bool NextOn;
	bool HuaweiR11IpHostTr69Type;
	bool McastDsForceRmVlan;
	bool HuaweiR11AclFormatExtend;
	bool FastLeaveForceEnable;
	bool HuaweiOlt;
	bool ZteOlt;
	bool MGTS2014;
	bool CHT2015;
	bool SING2015;
	bool TEF2016;
	bool TefXgpon2017;
	bool C424G2016;
	bool AluOlt;
	bool ADTRANOlt;
	bool UntagFirst;
	bool TestTr247;
	uint32_t IpHostCount;
	uint32_t WindowSize;
	bool ManagedEntitySupport;
	uint32_t SlotNoPon;
	uint32_t SlotTypePon;
	uint32_t SlotNoEth;
	uint32_t SlotTypeEth;
	uint32_t SlotNoXGEth;
	uint32_t SlotTypeXGEth;
	uint32_t SlotNoVeip;
	uint32_t SlotTypeVeip;
	uint32_t SlotNoPots;
	uint32_t SlotTypePots;
	uint32_t SlotNoLct;
	uint32_t SlotTypeLct;
	uint32_t SlotNoWlan;
	uint32_t SlotTypeWlan;
	uint32_t TimeoutToExecuteBackendActions;
	uint32_t PmPollingInterval;
	uint32_t AlarmPollingInterval;
	uint32_t OnuOperationMode;
	uint32_t GemBlockLength;
	uint32_t IgmpQueryGemMode;
	char OntVendorId[11];
	char PreOltVendor[9];
	uint32_t OntVendorProductCode;
	bool XgponProject;
} rdm_MosUsrCfg_t;

typedef struct rdm_OmciVlanInfo_s {   // RDM_OID_OMCI_VLAN_INFO 
	int UniVlanId;
	int AniVlanId;
	int UniPbitMappingAni_0;
	int UniPbitMappingAni_1;
	int UniPbitMappingAni_2;
	int UniPbitMappingAni_3;
	int UniPbitMappingAni_4;
	int UniPbitMappingAni_5;
	int UniPbitMappingAni_6;
	int UniPbitMappingAni_7;
} rdm_OmciVlanInfo_t;

#endif // _ZCFG_RDM_OBJ_H
