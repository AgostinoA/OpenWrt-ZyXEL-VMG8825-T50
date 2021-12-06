/*
   $Id: TR104.h 0.00.0.1 2008/10/21 11:21 ctpan Exp $
*/
/************************************************************************
 *
 *	Copyright (C) 2008 ZyXEL Communications, Corp.
 *	All Rights Reserved.
 *
 * ZyXEL Confidential; Need to Know only.
 * Protected as an unpublished work.
 *
 * The computer program listings, specifications and documentation
 * herein are the property of ZyXEL Communications, Corp. and shall
 * not be reproduced, copied, disclosed, or used in whole or in part
 * for any reason without the prior express written permission of
 * ZyXEL Communications, Corp.
 *
 *************************************************************************/
/*
 * $Log: TR104.h $
*/
 
#ifndef _TR104OBJECT_H_INCLUDE
#define _TR104OBJECT_H_INCLUDE

#include "global.h"
#include "switch.h"
#include "icf_defs.h"

#if ZYXEL_SIP_SUCCESSIVE_REGISTER_SESSION_TIME_GAP_SUPPORT //Michael.20141006.001: Add to support the successive SIP register session gap mechanism.
#include <sys/time.h>
#endif //ZYXEL_SIP_SUCCESSIVE_REGISTER_SESSION_TIME_GAP_SUPPORT.

/********************** VOIP Configuration , Spt_voip.h**********************/

#define  POTS_PORT_NAME_LEN		128
#define  PSTN_LOCAL_CODE_LEN		8
#define  VOIP_PREFIX_CODE_LEN		8
#define  PSTN_PREFIX_CODE_LEN		8
#define  PSTN_PHONE_NUM_LEN		36
#define  FORCE_PSTN_CALL_NUM		40

#define  URL_SIP						0	/* Check with ua_cm.h */
#define  URL_TEL						1	/* Check with ua_cm.h */
#define  URL_SIPS           				2


#define  USERID_LENGTH				128	/* Changed. In order to meet Tr069. Keith */
//Amber.20180628: This is also part of the bugfix of the Redmine issue [#50599][VoIP] Speed Dial cannot accepts send 128 digits number.
#define  MAX_OUTGOING_REMOTE_PEER_SIP_USERID_LEN	64
#define  MAX_OUTGOING_TARGET_SIP_USERID_LEN			MAX_OUTGOING_REMOTE_PEER_SIP_USERID_LEN


#define  INTERFACE_NAME_LEN                        20
#define  SIP_DOMAIN_NAME_LEN                       256 /* Changed. In order to meet Tr069. Keith */
#define  SIP_SERVER_ADDR_LEN                       256 /* Changed. In order to meet Tr069. Keith */
#define  SIP_REGISTER_ADDR_LEN                     256 /* Changed. In order to meet Tr069. Keith */

#define  STUN_SERV_NAME_LEN		128
#define  SIP_FAKE_NAME_LEN			128
#define  SIP_IBAUTH_USERNAME_LEN 	256		
#define  SIP_IBAUTH_PW_LEN 			256

#if ZYXEL_VOICE_REMOTE_CONFERENCE
#define	SIP_REMOTE_CONF_URI_LEN                128
#endif

		

/*********************Form ZyXEL cwmpVoIP.h START*********************/


/*For  VoiceService_ProfileLine -- constant */
#define TR104_CALL_FORWARD_TOTAL_ENTRIES	10

/*For  VoiceService_Tr104Ext -- constant */
#ifdef ZYPRJ_CUSTOMER_SUNRISE
	#define TR104_VSPEED_DIAL_BOOK_LIST_CNT 8
#else
	#define TR104_VSPEED_DIAL_BOOK_LIST_CNT 10
#endif
#define TR104_VCALL_POLICY_BOOK_LIST_CNT	20
#define TR104_VPSTN_CNT						1

			
/************************Form ZyXEL cwmpVoIP.h END**************************/

/* currently only two FXS channel is available, ZyXEL, John */
#ifndef NUM_FXS_CHANNELS
#define NUM_FXS_CHANNELS      2
#endif

#ifndef NUM_FXO_CHANNELS
#define NUM_FXO_CHANNELS      0
#endif



typedef struct tr104LstElmObj_s{
	void*  value_;
	struct tr104LstElmObj_s*          next_;
	struct tr104LstElmObj_s*          pre_;
}tr104LstElm_t;

typedef struct tr104ObjLst_s{
	tr104LstElm_t*  head_;
	tr104LstElm_t*	tail_;
	tr104LstElm_t*	cur_;	//For GetFirst GetNext using 2014-12-22 Steve.
	int            	 size_;
}tr104ObjLst_t;


/*Reffer  cwmpVoIP_Tr104_SignalCodec_e which define in ZyXEL cwmpVoIP.h*/
typedef enum
{
    enum_G711MuLaw = 0,
    enum_G711ALaw,
    enum_G729	
} Tr104_SignalCodec_en;



/*! \brief Obj struct for InternetGatewayDevice.Services.VoiceService.{i}.Capabilities.SIP.*/
/*
SIP-specific capabilities. Applicable only if SIP is
among the list of supported protocols.
R
*/
typedef struct VoiceCapSipObj_st{
	
	char		role[256+1];	/*see TR104_CAPABILITIESSIPROLE , 16+1*/
	/*UserAgent , B2BUA , OutboundProxy*/
	char	extensions[256+1]; /*see  TR104_CAPABILITIESSIPEXTENSIONS*/
	char	transports[256+1]; /*see  TR104_CAPABILITIESSIPTRANSPORTS*/
	char	URISchemes[256+1];/*see TR104_CAPABILITIESSIPURISCHEMES*/
	uint8	eventSubscription;									
	uint8	responseMap;		
	
	char	TLSAuthenticationProtocols[256+1];/*Null , MD5 , SHA-1*/
	char	TLSAuthenticationKeySizes[256+1];				
	char	TLSEncryptionProtocols[256+1]; /*Null , RC4 , RC2 , DES , 3DES	*/
	char	TLSEncryptionKeySizes[256+1];					
	char	TLSKeyExchangeProtocols[256+1]; /*RAS , DSS*/		
	
	/*type : VoiceCapObj_t*/
	void* parent_VoiceCapObj;	
}VoiceCapSipObj_t;

/* The definition for spVoiceSignal_t.primaryCompressType, secondCompressType and thirdCompressType */
/* Also defines RTP Payload Type */
#define ZYNOS_CODEC_PCMU			0
#define ZYNOS_CODEC_GSM			3
#define ZYNOS_CODEC_G723			4
#define ZYNOS_CODEC_PCMA			8
#define ZYNOS_CODEC_G722MODE1	9
#define ZYNOS_CODEC_G728			15
#define ZYNOS_CODEC_G729			18
#define ZYNOS_CODEC_T38			128
#define ZYNOS_CODEC_H_263			34
#define ZYNOS_CODEC_G726_16		96
#define ZYNOS_CODEC_G726_24		97
#define ZYNOS_CODEC_G726_32		98
#define ZYNOS_CODEC_G726_40		99
#define ZYNOS_CODEC_RFC2833		101
#define ZYNOS_CODEC_UNKNOWN		-1
#ifdef CODEC_THIRD_SELECTION
#define ZYNOS_CODEC_NONE			250
#endif

/*Brady.20151112 , The definition for dynamic codec*/
#define DYNAMIC_CODEC_PT_MIN_NUM 96
#define DYNAMIC_CODEC_PT_MAX_NUM 127
#define DYNAMIC_CODEC_PT_ERR_NUM 128

/*SDP payload - rtpmap codec name definitions*/
#define SDP_CODEC_NAME_PCMU	"PCMU"
#define SDP_CODEC_NAME_PCMA	"PCMA"
#define SDP_CODEC_NAME_G722	"G722" //Michael.20130715.001: Add.
#define SDP_CODEC_NAME_G726_16	"G726-16"
#define SDP_CODEC_NAME_G726_24	"G726-24"
#define SDP_CODEC_NAME_G726_32	"G726-32"
#define SDP_CODEC_NAME_G726_40	"G726-40"
#define SDP_CODEC_NAME_G728	"G728" //Michael.20130715.001: Add.
#define SDP_CODEC_NAME_G729	"G729"
#define SDP_CODEC_NAME_T38	"t38"
#define SDP_CODEC_NAME_TELEPHONE_EVENT	"telephone-event"
#define SDP_CODEC_NAME_G7231	"(G723.1)"	// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_X_ZYXEL_BV16		"(BV16)"	// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_X_ZYXEL_BV32		"(BV32)"	// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_X_ZYXEL_LPCM_NB	"(LINPCM128)"	// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_X_ZYXEL_LPCM_WB	"(LINPCM256)"	// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_ILBC	"(iLBC)"		// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_X_ZYXEL_GSM_AMR_12K	"(GSM-AMR-12K)"	// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_X_ZYXEL_GSM_AMR_10K	"(GSM-AMR-10K)"	// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_X_ZYXEL_GSM_AMR_795	"(GSM-AMR-795)"	// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_X_ZYXEL_GSM_AMR_740	"(GSM-AMR-740)"	// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_X_ZYXEL_GSM_AMR_670	"(GSM-AMR-670)"	// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_X_ZYXEL_GSM_AMR_590	"(GSM-AMR-590)"	// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_X_ZYXEL_GSM_AMR_515	"(GSM-AMR-515)"	// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_X_ZYXEL_GSM_AMR_475	"(GSM-AMR-475)"	// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_X_ZYXEL_AMR_WB_66	"(AMR-WB-66)"	// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_X_ZYXEL_AMR_WB_885	"(AMR-WB-885)"	// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_X_ZYXEL_AMR_WB_1265	"(AMR-WB-1265)"	// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_X_ZYXEL_AMR_WB_1425	"(AMR-WB-1425)"	// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_X_ZYXEL_AMR_WB_1585	"(AMR-WB-1585)"	// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_X_ZYXEL_AMR_WB_1825	"(AMR-WB-1825)"	// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_X_ZYXEL_AMR_WB_1985	"(AMR-WB-1985)"	// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_X_ZYXEL_AMR_WB_2305	"(AMR-WB-2305)"	// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_X_ZYXEL_AMR_WB_2385	"(AMR-WB-2385)"	// TODO: FIXME after survey & study!
#define SDP_CODEC_NAME_UNKNOWN	"Unknown"

//Michael.20130715.001.B: Add.
/* TR-104 "Standard" Codec Name defined in IGD.VoiceService.{i}.Capabilities.Codecs.{i}.Codec */
#define TR104_CODEC_NAME_G711MuLaw	"G.711MuLaw"
#define TR104_CODEC_NAME_G711ALaw	"G.711ALaw"
#define TR104_CODEC_NAME_G726		"G.726"
#define TR104_CODEC_NAME_G729		"G.729"
#define TR104_CODEC_NAME_G729a	"G.729a"
#define TR104_CODEC_NAME_G729e	"G.729e"
#define TR104_CODEC_NAME_G728		"G.728"
#define TR104_CODEC_NAME_G7231	"G.723.1"
#define TR104_CODEC_NAME_G722		"G.722"
#define TR104_CODEC_NAME_G7221	"G.722.1"
#define TR104_CODEC_NAME_G7222	"G.722.2"
#define TR104_CODEC_NAME_GSM_FR	"GSM-FR"
#define TR104_CODEC_NAME_GSM_HR	"GSM-HR"
#define TR104_CODEC_NAME_GSM_EFR	"GSM-EFR"
#define TR104_CODEC_NAME_ILBC		"iLBC"

/* TR-104 "ZyXEL eXtended (Private)" Codec Name */
#define TR104_CODEC_NAME_X_ZYXEL_G726_16	"G.726-16"
#define TR104_CODEC_NAME_X_ZYXEL_G726_24	"G.726-24"
#define TR104_CODEC_NAME_X_ZYXEL_G726_32	"G.726-32"
#define TR104_CODEC_NAME_X_ZYXEL_G726_40	"G.726-40"
#define TR104_CODEC_NAME_X_ZYXEL_BV16	"X_ZYXEL_BV16"
#define TR104_CODEC_NAME_X_ZYXEL_BV32	"X_ZYXEL_BV32"
#define TR104_CODEC_NAME_X_ZYXEL_LPCM_NB	"X_ZYXEL_LPCM_NARROWBAND"
#define TR104_CODEC_NAME_X_ZYXEL_LPCM_WB	"X_ZYXEL_LPCM_WIDEBAND"
#define TR104_CODEC_NAME_X_ZYXEL_GSM_AMR_12K	"X_ZYXEL_GSM_AMR_12K"
#define TR104_CODEC_NAME_X_ZYXEL_GSM_AMR_10K	"X_ZYXEL_GSM_AMR_10K"
#define TR104_CODEC_NAME_X_ZYXEL_GSM_AMR_795	"X_ZYXEL_GSM_AMR_795"
#define TR104_CODEC_NAME_X_ZYXEL_GSM_AMR_740	"X_ZYXEL_GSM_AMR_740"
#define TR104_CODEC_NAME_X_ZYXEL_GSM_AMR_670	"X_ZYXEL_GSM_AMR_670"
#define TR104_CODEC_NAME_X_ZYXEL_GSM_AMR_590	"X_ZYXEL_GSM_AMR_590"
#define TR104_CODEC_NAME_X_ZYXEL_GSM_AMR_515	"X_ZYXEL_GSM_AMR_515"
#define TR104_CODEC_NAME_X_ZYXEL_GSM_AMR_475	"X_ZYXEL_GSM_AMR_475"
#define TR104_CODEC_NAME_X_ZYXEL_AMR_WB_66		"X_ZYXEL_AMR_WB_66"
#define TR104_CODEC_NAME_X_ZYXEL_AMR_WB_885	"X_ZYXEL_AMR_WB_885"
#define TR104_CODEC_NAME_X_ZYXEL_AMR_WB_1265	"X_ZYXEL_AMR_WB_1265"
#define TR104_CODEC_NAME_X_ZYXEL_AMR_WB_1425	"X_ZYXEL_AMR_WB_1425"
#define TR104_CODEC_NAME_X_ZYXEL_AMR_WB_1585	"X_ZYXEL_AMR_WB_1585"
#define TR104_CODEC_NAME_X_ZYXEL_AMR_WB_1825	"X_ZYXEL_AMR_WB_1825"
#define TR104_CODEC_NAME_X_ZYXEL_AMR_WB_1985	"X_ZYXEL_AMR_WB_1985"
#define TR104_CODEC_NAME_X_ZYXEL_AMR_WB_2305	"X_ZYXEL_AMR_WB_2305"
#define TR104_CODEC_NAME_X_ZYXEL_AMR_WB_2385	"X_ZYXEL_AMR_WB_2385"
#define TR104_CODEC_NAME_X_ZYXEL_T38		"X_ZYXEL_T38"
#define TR104_CODEC_NAME_X_ZYXEL_NTE		"X_ZYXEL_NTE"
//Michael.20130715.001.E: Add.


/*! \brief Obj struct for InternetGatewayDevice.Services.VoiceService.{i}.Capabilities.Codecs.{i}.*/
/*Reffer  cwmpVoIP_Tr104_CodecsTab_s which define in ZyXEL cwmpVoIP.h*/
typedef struct VoiceCapCodecObj_st{		/*R*/
	uint32	entryID; /* ZyXEL : index, R*/
	char		codecName[64+1];
	char		codecAlias[64+1]; //Michael.20130715.001: Add to match the "ZyXEL private(?)" TR-104 data model parameter - IGD.Services.VoiceService.{i}.Capabilities.Codecs.{i}.Alias.
	uint32	bitRate;

	/*Comma-separate list of supported packetization periods,
	in milliseconds, or continuous ranges of packetization periods.*/
	char		packetizationPeriod[64+1];

	/*Indicates support for silence suppression for this codec.*/
	uint8	silenceSuppression;

	/*type : VoiceCapObj_t*/
	void*	parent_VoiceCapObj;
}VoiceCapCodecObj_t;


/*! \brief Obj struct for InternetGatewayDevice.Services.
VoiceService.{i}.Capabilities.*/
/*The overall capabilities of the VoIP CPE.*/
typedef	struct VoiceCapObj_st{/*R*/

	uint32	maxProfileCount;		/* see TR104_MAXPROFILECOUNTOFCAPABILITIES*/
	uint32	maxLineCount;		/*see MaxLineCountOfCapabilities*/
	uint32	maxSessionsPerLine; /*see MaxSessionsPerLineOfCapabilities*/
	uint32	maxSessionCount;	/*see kMaxNumberOfSessions*/
	/*see  CWMPVOIP_TR104_SIGNALINGPROTOCOLLIST*/
	char   	signalingProtocols[256+1];
	/*see TR104_CAPABILITIESREGIONSLIST*/
	char 	regions[256+1];
	uint8	RTCP;	
	uint8	SRTP;
	
/*not show in VoiceCapObject of mdm*/
	/*Comma-separated list , Null,static,SDP,IKE*/
	char 	SRTPKeyingMethods[256+1];		
	/*Comma-separated list , list of unsigned integers,*/
	char 	SRTPEncryptionKeySizes[256+1];	
/*not show in VoiceCapObject of mdm***/
	
	uint8	RTPRedundancy;
	uint8	DSCPCoupled;
	uint8	ethernetTaggingCoupled;
	uint8	PSTNSoftSwitchOver;
	/*Support for T.38 fax.*/
	uint8	faxT38;
	/*Support for fax pass-through.*/
	uint8	faxPassThrough;
	uint8	modemPassThrough;
	uint8	toneGeneration;
	

	uint8	toneDescriptionsEditable;
	uint8	patternBasedToneGeneration;
	uint8	fileBasedToneGeneration;	
	/*G.711MuLaw,G.711ALaw,MP3,WAV,AMR*/
	char	toneFileFormats[256+1];
	uint8	ringGeneration;
	uint8	ringDescriptionsEditable;
	uint8	patternBasedRingGeneration;
	uint8	ringPatternEditable;
	uint8	fileBasedRingGeneration;	
	/*MIDI,SMAF,RTTTL,MP3,WAV,AMR*/
	char 	ringFileFormats[256+1];

	uint8	digitMap;
	uint8	numberingPlan;
	uint8	buttonMap;
	uint8	voicePortTests;
	
	VoiceCapSipObj_t*		CapOfSIP;
	tr104ObjLst_t *	CapCodecsTable ; 	

	/*type : VoiceServiceObj_t*/
	void*	parent_VoiceServiceObj;
}VoiceCapObj_t;



/*reffer ZyXEL , cwmpVoIP_Tr104_ServiceProviderInfoTab_s*/
typedef struct VoiceProfServiceProviderInfoObj_st{	/*W*/
	char    name[256+1];
	char    URL[256+1];
	char    contactPhoneNumber[32+1];
	char    emailAddress[256+1];

	/*type : VoiceProfObj_t*/
	void*	parent_VoiceProfObj;
}VoiceProfServiceProviderInfoObj_t;


/*

Table to specify the SIP events to which the CPE
MUST subscribe.
If this table is supported, the capability
VoiceService.{i}.Capabilities.SIP.Event-
Subscription.{i}. MUST be equal to true and the
parameter SIPEventSubscribeNumberOfElements
in the parent object MUST be present.

*/
typedef struct VoiceProfSipEventSubObj_st{/*W*/

	char	event[32+1];/*Default = <empty>*/
	char	notifier[256+1];/*Default = <empty>*/
	uint32	notifierPort;/*Default = 0,[0:65536]*/
	uint8	notifierTransport;/*Default = "UDP"*/
	/*Subscription refresh timer , s*/
	uint32	expireTime;	

	/*type : VoiceProfSipObj_t*/
	void*	parent_VoiceProfSipObj;
} VoiceProfSipEventSubObj_t;


/*
Each entry in this table specifies the tone and
message to be provided to the user for a particular
SIP Response received (normally 4xx and 5xx).
If this table is supported, the capability
VoiceService.{i}.Capabilities.SIP.ResponseMap.{i}.
MUST be equal to true and the parameter SIPResponseMapNumberOfElements
in the parent object MUST be present.
Applicable only for a VoIP endpoint.

*/
typedef struct VoiceProfSipRespMapObj_st{	/*W*/

	uint32	SIPResponseNumber;/*[100:999]  , Default = 100*/
	char	textMessage[64+1];/* Default = <empty>*/
	/*The value corresponds to EntryID of an entry in the table 
	VoiceService.{i}.VoiceProfile.{i}.Tone.-Description.*/
	uint32	tone;/*Default = 0*/
	/*type : VoiceProfSipObj_t*/
	void*	parent_VoiceProfSipObj;
}VoiceProfSipRespMapObj_t;



/* Corresponding to: struct VoiceProfSipObj_st{...}VoiceProfSipObj_t.inboundAuth */
#define TR104I_INBOUNDAUTH_NONE		0
#define TR104I_INBOUNDAUTH_DIGEST		1

/* Curtis 20140103: Support Register by (SIP Account) User Name */
/* Corresponding to: struct VoiceProfSipObj_st{...}VoiceProfSipObj_t.ZyXEL_RegisterAndOperateBase */
#define TR104I_REGISTER_AND_OPERATE_BASE_DIRECTORY_NUMBER 0
#define TR104I_REGISTER_AND_OPERATE_BASE_AUTH_USER_NAME   1

//Michael.20160803.001.B: Add to support diverse PRACK type as well as fix some PRACK related issue. [Redmine#17963 & #25639, with referring to #3455(eITS#140600827)].
/* Corresponding to: struct VoiceProfSipObj_st{...}VoiceProfSipObj_t.ZyXEL_PRACK_for_InCall & ZyXEL_PRACK_for_OutCall */
typedef enum prack_mode_es
{
	PRACK_DISABLED = 0,
	PRACK_IN_SUPPORTED = 1,
	PRACK_IN_REQUIRE = 2,
	//PRACK_INVALID_VALUE,
	PRACK_OLD_FUNC_ENABLED = 0xFE, //This special PRACK mode terminology is to represent the condition: {((voiceProfSip->ZyXEL_PRACK_for_InCall==PRACK_OLD) || (voiceProfSip->ZyXEL_PRACK_for_OutCall==PRACK_OLD)) && (voiceProfSip->ZyXEL_rfc3262support==TRUE)}. This terminology is defined here in order to ensure it will NOT Value-Conflict with the other four modes, and thus it can be used/referred & (furthermore)ONLY be used/referred in the input parameter of the joint utility function 'checkIfAnyActiveVoiceProfile_PRACKmode_is()'. //Michael.20160808.001: Add to change/improve the Original PRACK operation logic to refer to All "Active" Voice Profiles' PRACK setting (in 'ZyXEL_rfc3262support').
	PRACK_OLD = 0xFF //This special PRACK mode is to go-back to use/activate the Old/Original operation logic. Reserved for Test purpose Only!!
} prack_mode_et;

#define TR104S_PRACK_MODE_DISABLED	"Disabled"
#define TR104S_PRACK_MODE_SUPPORTED	"Supported"
#define TR104S_PRACK_MODE_REQUIRE	"Require"
#define TR104S_PRACK_MODE_ORIGINAL	"Original" //Old/Original operation logic. Reserved for Test purpose Only!!

#if ZYXEL_SIP_PRACK_FOR_INCALL_SUPPORT_SOFT_REQUIRE_MODE_AND_REDEFINE_KEYWORD_SUPPORTED_FOR_IT //Michael.20160807.001: Add to support a Soft-"REQUIRE" PRACK mode for the InCall case to establish a Non-PRACK Call for the condition {InCallPrack:NO_PRACK, LocalPrackCfg:REQUIRE} and Re-define the un-used "SUPPORTED" mode keyword for it. [Redmine#17963 & #25639, with referring to #3455(eITS#140600827)].
#define TR104I_PRACK_FOR_INCALL_DEFAULT		PRACK_IN_SUPPORTED //NOTE: This is our own Extension Design to Re-define/Re-use the 'PRACK_IN_SUPPORTED' as a Soft-"REQUIRE" PRACK mode for the InCall case. However, for InCall case of the IPTK Original Design, NOT support the 'PRACK_IN_SUPPORTED' mode!!
#else
#define TR104I_PRACK_FOR_INCALL_DEFAULT		PRACK_IN_REQUIRE //NOTE: For InCall case of the IPTK Original Design, NOT support the 'PRACK_IN_SUPPORTED' mode!!
#endif //ZYXEL_SIP_PRACK_FOR_INCALL_SUPPORT_SOFT_REQUIRE_MODE_AND_REDEFINE_KEYWORD_SUPPORTED_FOR_IT.
#define TR104I_PRACK_FOR_OUTCALL_DEFAULT		PRACK_IN_SUPPORTED
//Michael.20160803.001.E: Add.

#if ZYXEL_VOICE_REMOTE_CONFERENCE
typedef enum ConferenceAddPartyMethod_e
{
	REMOTE_CONF_ADD_PARTY_BY_SEND_REFER_TO_FOCUS, //"SendReferToFocus"
	REMOTE_CONF_ADD_PARTY_BY_SEND_REFER_TO_USER, //"SendReferToUser"
}ConferenceAddPartyMethod_et; //For ZyXEL_ConferenceAddPartyMethod
#endif //ZYXEL_VOICE_REMOTE_CONFERENCE

/*! \brief Obj struct for InternetGatewayDevice.
Services.VoiceService.{i}.VoiceProfile.{i}.SIP.*/
/*Voice profile parameters that are specific to SIP user agents.*/
/*reffer ZyXEL , */
typedef struct VoiceProfSipObj_st{	/*W*/

	uint8 	ZyXEL_rfc3263support ; /*enable dns srv for proxyServer and registrarServer*/
	char 	proxyServer[SIP_SERVER_ADDR_LEN+1];/*<empty> ,VoiceServiceSignal.signalDestIP*/
	uint16	proxyServerPort;/*[0:65535],def=5060		,VoiceServiceSignal.signalDestPort*/
	uint8	proxyServerTransport;/*def=UDP		,VoiceServiceSignal.transType*/

	char 	registrarServer[SIP_REGISTER_ADDR_LEN+1];/*<empty> ,VoiceServiceSignal.registrarDestIP*/
	uint16	registrarServerPort; /*[0:65535],def=5060		,VoiceServiceSignal.registrarDestPort*/
	uint8	registrarServerTransport;/*def=UDP*/		
	uint32	registrationPeriod;
	uint32	registerExpires;							/*registrarExpireTime*/
	/*Register retry interval, in seconds*/
	uint32	registerRetryInterval;					/*registrarReSendTime*/
	/*Register request Min-Expires header value, in seconds.*/
	uint32	registersMinExpires;							/*registrarExpireTime*/

#if ZYXEL_VOICE_REMOTE_CONFERENCE
	char	ZyXEL_ConferenceURI[SIP_REMOTE_CONF_URI_LEN+1];

#define REMOTE_CONF_ADD_PARTY_BY_SEND_REFER_TO_FOCUS_STR "SendReferToFocus"
#define REMOTE_CONF_ADD_PARTY_BY_SEND_REFER_TO_USER_STR "SendReferToUser"

	ConferenceAddPartyMethod_et ZyXEL_ConferenceAddPartyMethod;
#endif //ZYXEL_VOICE_REMOTE_CONFERENCE

	/*CPE domain string*/
	char 	userAgentDomain[SIP_DOMAIN_NAME_LEN+1];/*<empty> ,VoiceServiceSignal.domain*/
	/*def=0 . broadcom set 5060(default)*/
	uint16	userAgentPort;	/*[0:65535],def=5060	*/			/*VoiceServiceSignal.srcPort*/
	uint8	userAgentTransport;/*UDP*/	
	
	char	outboundProxy[SIP_SERVER_ADDR_LEN+1];/*<empty> ,	outboundDestIP*/
	uint16	outboundProxyPort;/*[0:65535],def=5060, outboundDestPort	*/
	
	/* outbound proxy keep alive interval */
	uint32	ZyXEL_outboundKAIntvl;  	/*outboundKAIntvl*/
	/*keep alive target*/
	uint32	ZyXEL_KAServer;			/*KAServer*/

	char   	ZyXEL_fakeSipIP[SIP_FAKE_NAME_LEN+1]; 		/*VoiceServiceSignal.fakeSipIP*/
	uint16	ZyXEL_fakeSipPort;						/*VoiceServiceSignal.fakeSipPort*/

	/* Curtis 20140103: Support Register by (SIP Account) User Name */
	uint8  ZyXEL_RegisterAndOperateBase;

#if HEARTBEAT_MECHANISM_ENABLE 
	uint8	ZyXEL_HeartbeatEnable ;
	uint32	ZyXEL_RateOfHeartbeat ;
#endif	

#if ZYXEL_SIP_SUCCESSIVE_REGISTER_SESSION_TIME_GAP_SUPPORT //Michael.20141006.001: Add to support the successive SIP register session gap mechanism.
	uint8	ZyXEL_RegSessionTimeGap_Enable; /* Services.VoiceService.{i}.VoiceProfile.{i}.SIP.X_5067F0_RegSessionTimeGap_Enable / X_ZyXEL_COM_RegSessionTimeGap_Enable */
	uint32	ZyXEL_RegSessionTimeGap_Intvl; //msec <--> //switch.h/DEFAULT_TIMER_SUCCESSIVE_SIP_REGISTER_SESSION_TIME_GAP (4) //sec.
	struct timeval last_reg_session_start_time; //SHOULD be inited to zero which representing the Epoch: 1970-01-01 00:00:00 +0000 (UTC).
	pthread_mutex_t mutex_last_reg_session_start_time;
#endif //ZYXEL_SIP_SUCCESSIVE_REGISTER_SESSION_TIME_GAP_SUPPORT.


	/*Text string to be used in the Organization header.*/
	char	organization[256+1];/*<empty>	*/		
	
	uint32	TimerT1;
	uint32	TimerT2;
	uint32	TimerT4;
	uint32	TimerA;
	uint32	TimerB;
	uint32	TimerC;
	uint32	TimerD;
	uint32	TimerE;
	uint32	TimerF;
	uint32	TimerG;
	uint32	TimerH;
	uint32	TimerI;
	uint32	TimerJ;
	uint32	TimerK;
	/*Invite request Expires header value, in seconds.*/
	uint32	inviteExpires;		/*sessionExpireTime*/
	uint32	reInviteExpires;
	uint32	ZyXEL_minSE;		/*minSE*/
	/*period send out SUBSCRIBE SIP message (MWI) */
	uint32  ZyXEL_mwiExpireTime; 

	/*None , Digest*/
	uint8	inboundAuth;/* Default "None"*/
	char	inboundAuthUsername[SIP_IBAUTH_USERNAME_LEN+1];
	char	inboundAuthPassword[SIP_IBAUTH_PW_LEN+1];
	uint8	useCodecPriorityInSDPResponse;

	/*[0:63] , Default = 0  ,only need 8 bits*/
	uint8	DSCPMark; 					/*sip_TOS		*/
	uint16  ZyXEL_sigVLanTagTPID;		/*sigVLanTagTPID*/
	uint16  ZyXEL_sigVLanTagTCI;		/*sigVLanTagTCI*/

	uint8  	ZyXEL_rfc3325support;		/*rfc3325support: Private Extension to SIP for Asserted Identity within Trusted Networks*/

	/*PRACK (100rel)*/
	uint8   ZyXEL_rfc3262support;		/*boolean: FALSE(0), TRUE(1)*/
	//Michael.20160803.001.B: Add to support diverse PRACK type as well as fix some PRACK related issue. [Redmine#17963 & #25639, with referring to #3455(eITS#140600827)].
	uint8   ZyXEL_PRACK_for_InCall;	/*uint: PRACK_IN_REQUIRE(0), PRACK_IN_SUPPORTED(1), PRACK_OLD(99). defined in typedef enum prack_mode_es {...} prack_mode_et*/
	uint8   ZyXEL_PRACK_for_OutCall;	/*uint: PRACK_IN_REQUIRE(0), PRACK_IN_SUPPORTED(1), PRACK_OLD(99). defined in typedef enum prack_mode_es {...} prack_mode_et*/
	//Michael.20160803.001.E: Add.

	/*DNS SRV Arg*/
	uint8 ZyXEL_DNS_SRV_UseAgentDomain; /*2014-10-21 Steve.DNS SRV use userAgentDomain to query*/

	/*SIP REGISTER Arg*/
	/*ZyXEL_Reg_SipField_mode:
	 * Control the REGISTER Packet Request-Line sip field. EX: Request REGISTER sip:AA.BB.CC.com
	 * There are 3 mode to choice (Default:0)
	 * 0: Auto use 'manual' when No DNS SRV or DNS SRV "without" ZyXEL_DNS_SRV_UseAgentDomain set, use 'Domain' when DNS SRV "with" ZyXEL_DNS_SRV_UseAgentDomain set
	 * 1: manual
	 * 2: Domain
	 * 3: Use Selected DNS SRV Response name(DNS SRV only)*/
	uint8 ZyXEL_Reg_SipField_mode;


	/*VOIP_ROUTE_SELECT*/  /* remote node index for VoIP */

	int		VLANIDMark; /*[-1:] , Default = -1*/
	int   	ethernetPriorityMark; /*[-1:] , Default = -1*/
	
	uint32	SIPEventSubscribeNumberOfElements;/* Default = 0	,R*/
	uint32	SIPResponseMapNumberOfElements;/*[0:999] , Default = 0		,R*/
	
	tr104ObjLst_t*	eventsubScribeTab;
	tr104ObjLst_t*	responseMapTab;
	/*VoiceProfSipEventSubObj_t* 	eventsubScribeTab;*/
	/*VoiceProfSipRespMapObj_t*	responseMapTab;*/
	
	/*2014-11-24 Steve. Option 120 support*/
	bool ZYXEL_op120Use;
	char ZYXEL_op120Server[SIP_DOMAIN_NAME_LEN+1];

	//yushiuan add  the three session refresh related parameters for supporting user can config , 2015/02/16
	bool		ZyXEL_SessionRefreshEnable;
	uint8	ZyXEL_SessionRefreshMethod; //TR104I_SESSION_REFRESH_METHOD_INVITE(0):INVITE, _UPDATE_PREFER(1):UPDATE Prefer, _UPDATE_STRICT(2):UPDATE Strict.
	uint8	ZyXEL_SessionRefresher; //ICF_SESSION_REFRESHER_NONE(0):None, _UAC(1):UAC, _UAS(2):UAS.

	//Amber.20180815: Add for 3GPP and XML tag name need to replace to be valid XML tag name.
	char	ZyXEL_3gppSupport[256+1];
	char	ZyXEL_3gppXmlReplaceString[256+1];


	/*type : VoiceProfObj_t*/
	void*	parent_VoiceProfObj;

#ifdef ZYXEL_SIP_SERVER_BACKUP_METHOD_MANUAL_CONFIG_DUAL_FQDN_SERVER_BACKUP_SWITCH
	/*20181030 Ralph: Add Backup Server domain*/
	char ZYXEL_BackupServer[SIP_DOMAIN_NAME_LEN+1];
#endif

}VoiceProfSipObj_t;


/*
Voice profile parameters related to RTCP.
If this object is supported, the capability
VoiceService.{i}.Capabilities.RTCP MUST be
equal to true.
Applicable only for a VoIP endpoint.
*/
typedef struct VoiceProfRtpRtcpObj_st{	/*W*/

	uint8	enable;
	uint32	txRepeatInterval;/*[1:] ms	,VoiceServiceRTP.transInterval*/
	char	localCName[64+1];			/*rtp_table.cname	*/
	
	/*type : VoiceProfRtpObj_t*/
	void*	parent_VoiceProfRtpObj;
}VoiceProfRtpRtcpObj_t;


/*
Voice profile parameters for secure voice
transmission via SRTP.
If this object is supported, the capability
VoiceService.{i}.Capabilities.SRTP MUST be
equal to true.
Applicable only for a VoIP endpoint.
*/
typedef struct VoiceProfRtpSrtpObj_st{
	uint8	enable;
	
	char	keyingMethods[256+1];
	char	encryptionKeySizes[256+1];
	char	ZyXEL_CryptoSuiteName[64+1];

/*Reserve	uint8    ZyXEL_primaryRtpCryptoType;	 */ /*VoiceServicesignal.primaryRtpCryptoType	*/
/*Reserve	uint8    ZyXEL_secondRtpCryptoType;	*/	/*VoiceServicesignal.secondRtpCryptoType*/
/*Reserve	uint8    ZyXEL_thirdRtpCryptoType;	*/	/*VoiceServicesignal.thirdRtpCryptoType*/
/*Reserve	uint8    ZyXEL_fourthRtpCryptoType;	*/	/*VoiceServicesignal.fourthRtpCryptoType*/

	/*type : VoiceProfRtpObj_t*/
	void*	parent_VoiceProfRtpObj;
}VoiceProfRtpSrtpObj_t;

/*
Redundancy
Voice profile parameters for RTP payload
redundancy as defined by RFC 2198.
If this object is supported, the capability
VoiceService.{i}.Capabilities.Redundancy MUST
be equal to true.
Applicable only for a VoIP endpoint.

*/
typedef struct VoiceProfRtpRedundancyObj_st{	/*W*/
	uint8	enable;
	uint8	payloadType;/*[0:127] ,default =0*/
	uint8	blockPayloadType;/*[0:127] ,default =0		/*R*/
	int		faxAndModemRedundancy;/*[-1:5] ,default =-1*/
	int		modemRedundancy;/*[-1:5] ,default =-1*/
	int		DTMFRedundancy;/*[-1:5] ,default =-1*/
	int		voiceRedundancy;/*[-1:5] ,default =-1*/
	uint32	maxSessionsUsingRedundancy;

	/*type : VoiceProfRtpObj_t*/
	void*	parent_VoiceProfRtpObj;
}VoiceProfRtpRedundancyObj_t;


/*! \brief Obj struct for InternetGatewayDevice.Services.VoiceService.{i}.VoiceProfile.{i}.RTP.*/
/*Voice profile parameters related to the voice
stream sent via RTP. Applicable only for a VoIP endpoint.*/
typedef struct VoiceProfRtpObj_st{	/*W*/
	/* ZyXEL : RTP Port: 40000~65535 , default 40000 */
	/*Base of port range to be used for incoming RTP streams for this profile.*/
	uint16	localPortMin;/*[0:65535]  , Default = 0 	 ,VoiceServiceSignal.portStart*/
	/*Top of port range to be used for incoming RTP streams for this profile.*/
	uint16	localPortMax;/*[0:65535]  , Default = 0 	,VoiceServicesignal.portEnd*/
	
	uint8	DSCPMark;	/*[0:63]  ,	*/			
	int	VLANIDMark;/*[-1:]  , Default = -1*/
	int	ethernetPriorityMark;/*[-1:]  , Default = -1*/
	uint8	telephoneEventPayloadType;/*[0:128]  ,*/
	
	VoiceProfRtpRtcpObj_t* 	RTCP_Profile;	
	VoiceProfRtpSrtpObj_t* 	SRTP_Profile;
	VoiceProfRtpRedundancyObj_t*	 RTPRedundancy;
	
	/* type : VoiceProfObj_t*/
	void*	parent_VoiceProfObj;
}VoiceProfRtpObj_t;

/*
NumberingPlan.PrefixInfo.{i}.
Each entry in this table contains information
related to an individual prefix in the numbering
plan. The number of prefixes is defined by the
PrefixInfoNumberOfEntries paramter.
It is anticipated that once the minimum number of
digits has been received, the VoIP device will
search this prefix list every time a new digit is
received. If no new entry is found, then the object
that was previously found will be used instead.
If this table is supported, the parameters Prefix-
InfoMaxEntries and PrefixInfoNumberOfEntries in
the parent object MUST be present.
*/
typedef struct VoiceProfNumPlanPrefixInfoObj_st{ /*W*/

	char	prefixRange[42+1];				/*default=<empty>*/
	
	uint8	prefixMinNumberOfDigits;		/*[1:40] , default=1*/
	uint8	prefixMaxNumberOfDigits;	/*[1:40] , default=1*/
	
	uint8	numberOfDigitsToRemove;	/*[0:40] , default=0*/
	uint8	posOfDigitsToRemove;		/*[0:40] , default=0*/
	uint32	dialTone;					/*default=0*/
	
	char	facilityAction[64+1];			/*default=<empty> , appecdixA*/
	char	facilityActionArgument[256+1];	/*default=<empty> ,appecdixA*/

	/*type : VoiceProfNumPlanObj_t*/
	void* 	parent_VoiceProfNumPlanObj;
}VoiceProfNumPlanPrefixInfoObj_t;



/*
NumberingPlan.
This object contains information related the
numbering plan.
This object is applicable only if the device
supports a dialing mechanism for which a number
plan is needed (for example, a device with an
explicit Dial button may not need to be aware of
the dialing plan) and if the device does not already
support a numbering plan mechanism for this
profile (e.g., in-band via MGCP).
If this object is supported, the capability
VoiceService.{i}.Capabilities.NumberingPlan
MUST be equal to true.
Applicable only for a VoIP endpoint.

*/
typedef struct VoiceProfNumPlanObj_st{
/*W*/
	uint8	minimumNumberOfDigits;/*[1:40] ,*/
	uint8	maximumNumberOfDigits;/*[1:40] ,*/
	
	uint16	interDigitTimerStd;/*[1:50000]ms , VoiceServiceFXS.dialingShortInterval*/
	/*This timer is the maximum allowable time (expressed in milliseconds) between the dialing of
	digits once the minimum number of digits defined on a prefix based has been reached.
	This timer is only applicable to "open numbering",where the exact number of digits for a 
	prefix is not known.*/	
	uint16	interDigitTimerOpen;/*[1:50000]ms ,*/ /*183 043 F.4 Timers : Ta1*/
	/* Dial Short Interval before the first dial digit */
	uint8	ZyXEL_dialingLongInterval;/*in sec ,VoiceServiceFXS.dialingLongInterval*/	

	

	/*The value corresponds to EntryID of an entry in
	the table VoiceService.{i}.VoiceProfile.{i}.Tone.-Description.*/
	uint32	invalidNumberTone;
	
	uint32	prefixInfoMaxEntries;/*R*/
	uint32	prefixInfoNumberOfEntries;/*R*/
	
	tr104ObjLst_t* PrefixInfoTab;
	/*VoiceProfNumPlanPrefixInfoObj_t* PrefixInfoTab;*/
	
	/*type : VoiceProfObj_t*/
	void* 	parent_VoiceProfObj;
}VoiceProfNumPlanObj_t;


//The following Tone Event Enum definitions from 0~20 are defined in the TR-104 data model for the object: .VoiceService.{i}.VoiceProfile.{i}.Tone.Event.{i}.Function.
#define TONE_EVENT_BUSY				0
#define TONE_EVENT_CONFIRMATION		1
#define TONE_EVENT_DIAL				2
#define TONE_EVENT_MESSAGEWAITING	3
#define TONE_EVENT_OFFHOOKWARNING	4
#define TONE_EVENT_RINGBACK			5
#define TONE_EVENT_REORDER			6
#define TONE_EVENT_STUTTERDIAL		7
#define TONE_EVENT_CALLWT				21 //Michael.20150909.001: Add to support the CLI (framework): Tone, Ring, LED and VMWI signal control.
#define TONE_EVENT_CW1					8
#define TONE_EVENT_CW2					9
#define TONE_EVENT_CW3					10
#define TONE_EVENT_CW4					11
#define TONE_EVENT_ALERTINGSIGNAL		12
#define TONE_EVENT_SPECIALDIAL		13
#define TONE_EVENT_SPECIALINFO		14
#define TONE_EVENT_RELEASE				15
#define TONE_EVENT_CONGESTION			16
#define TONE_EVENT_USERDEF1			17
#define TONE_EVENT_USERDEF2			18
#define TONE_EVENT_USERDEF3			19
#define TONE_EVENT_USERDEF4			20
//Michael.20150909.001.B: Add to support the CLI (framework): Tone, Ring, LED and VMWI signal control.
#define TONE_EVENT_WARNING			22
#define TONE_EVENT_POSITIVE_ACK		23
#define TONE_EVENT_NEGATIVE_ACK		24
//Michael.20150909.001.E: Add.


/*
Table of events for which a tone is defined. The
table is pre-populated with the list of events for
which the CPE supports definition of tones.
If this table is supported, the parameter Event-
NumberOfEntries in the parent object MUST be
present.
*/
typedef struct VoiceProfToneEventObj_st{/*R*/
	/*busy,confirmation,dial*/
	/*char	function[64+1];*/
	uint8	function;
	uint32	toneID; /*map to the entryID of Tone Description,W*/

	/*type : VoiceProfToneObj_t*/
	void*	parent_VoiceProfToneObj;	
}VoiceProfToneEventObj_t;

/*
Each entry in this table defines the contents of an
individual tone.
If ability to add, delete, and modify entries in this
table is supported, the capability VoiceService.{i}.-
Capabilities.ToneDescriptionsEditable MUST be
equal to true.
If this table is supported, the parameter
DescriptionNumberOfEntries in the parent object
MUST be present.
*/
typedef struct VoiceProfToneDescriptionObj_st{	/*W*/
	
	uint32	entryID;			/*[1:] 	,R*/
	uint8	toneEnable; 		/*default: FALSE*/
	char	toneName[64+1];	/*default: <empty>*/
	uint32	tonePattern;		/*default : 0 ,map to the entryID of Tone Pattern*/
	/*The EntryID of the entry in the Pattern table that begins the tone pattern for this tone.*/
	char	toneFile[256+1];	/*default: <empty>*/
	uint8	toneRepetitions; /*[0:255] ,default : 0*/
	char	toneText[64+1];	/*default :<empty>*/

	/*type : VoiceProfToneObj_t*/
	void*	parent_VoiceProfToneObj;	
}VoiceProfToneDescriptionObj_t;


/*
Each entry in the table defines a single phase in
an overall tone pattern. Each phase identifies the
entry that corresponds to the next phase.
Each entry in the table refers to the entry that
corresponds to the next phase of the pattern. The
table MAY be set up such that entries form loops,
or MAY end after a finite sequence.
If this object is supported, the capability
VoiceService.{i}.Capabilities.PatternBasedTone-
Generation MUST be equal to true, and the
parameter PatternNumberOfEntries in the parent
object MUST be present.
If ability to add, delete, and modify entries in this
table is supported, the capability VoiceService.{i}.-
Capabilities.ToneDescriptionsEditable MUST be
equal to true.
*/
typedef struct VoiceProfTonePatternObj_st{/*W*/
	uint32	entryID;/*[1:]*/
	uint8	toneOn;/*def = False*/
	uint16	frequency1;/*[0:4095] , def = 0 */
	int		power1;/* def = 0 */
	uint16	frequency2;/*[0:4095] , def = 0 */
	int		power2;/* def = 0 */
	uint16	frequency3;/*[0:4095] , def = 0 */
	int		power3;/* def = 0 */
	uint16	frequency4;/*[0:4095] , def = 0 */
	int		power4;/* def = 0 */
	uint16	modulationFrequency;/*[0:4095] , def = 0 */
	int		modulationPower;/* def = 0 */
	uint32	duration;/* def = 0 */
	/*The EntryID for the next phase of the tone pattern,after 
	the specified Duration of this phase has completed.*/
	uint32	nextEntryID;

	/*type : VoiceProfToneObj_t*/
	void*	parent_VoiceProfToneObj;	
}VoiceProfTonePatternObj_t;


/*
This object defines the contents of the tones and
announcements generated locally by the VoIP
device.
If this object is supported, the capability
VoiceService.{i}.Capabilities.ToneGeneration
MUST be equal to true.
Applicable only for a VoIP endpoint.
*/
typedef struct VoiceProfToneObj_st{/*R*/

	uint32	eventNumberOfEntries;
	uint32	descriptionNumberOfEntries;
	uint32	patternNumberOfEntries;

/*	VoiceProfToneEventObj_t*	 toneEventTab;*/
/*	VoiceProfToneDescriptionObj_t*	toneDescriptionTab;*/
/*	VoiceProfTonePatternObj_t*	tonePatternTab;*/
	
	tr104ObjLst_t*	toneEventTab;	
	tr104ObjLst_t*	toneDescriptionTab;
	tr104ObjLst_t*	tonePatternTab;

	/*type : VoiceProfObj_t*/
	void*	parent_VoiceProfObj;	
}VoiceProfToneObj_t;




/*
Button.{i}.
Each entry in this table specifies the purpose of
each programmable CPE button / function key
and whether the user has permission to
reprogram the button.
*/
typedef struct VoiceProfButtonMapButtonObj_st{/*W*/

	char	ButtonName[16+1];
	char	FacilityAction[64+1];
	char	FacilityActionArgument[256+1]; /* def=False*/
	char	QuickDialNumber[40+1];
	char	ButtonMessage[64+1];
	uint8	UserAccess;

	/*type : VoiceProfButtonMapObj_t*/
	void*	parent_VoiceProfButtonMapObj;	
}VoiceProfButtonMapButtonObj_t;

/*
This object is provided to permit the purpose of
the CPE buttons and function keys to be defined
via the ACS.
Support of this object is appropriate only for a
device that has programmable buttons in its user
interface.
If this object is supported, the capability
VoiceService.{i}.Capabilities.ButtonMap MUST be
equal to true.
Applicable only for a VoIP endpoint.
*/
typedef struct VoiceProfButtonMapobj_st{/*R*/
	uint32	numberOfButtons;
	tr104ObjLst_t*	buttonTab;
	/*VoiceProfButtonMapButtonObj_t*	 buttonTab;*/
	/*type : VoiceProfObj_t*/
	void*	parent_VoiceProfObj;	
}VoiceProfButtonMapObj_t;


/*TCFMethod*/
#define TR104I_TCFMETHOD_LOCAL	0
#define TR104I_TCFMETHOD_NETWORK	1

/*! \brief Obj struct for InternetGatewayDevice.Services.VoiceService.{i}.VoiceProfile.{i}.FaxT38.*/
/*T.38 Fax information for devices that support T.38
relay.
If this object is supported, the capability
VoiceService.{i}.Capabilities.FaxT38 MUST be
equal to true.
Applicable only to a VoIP endpoint.
*/
typedef struct VoiceProfFaxT38Obj_st{	/*W*/
	/*Enable or disable the use of T.38. */
	uint8	enable;	/*VoiceServiceSignal.t38Protocol*/
	/*Maximum data rate for fax. enum :2400,4800,7200,9600,12000,14400,33600*/
	uint16	bitRate;	/*VoiceServiceSignal.t38MaxRate*/
	/*10,20,30,40*/
	uint8	highSpeedPacketRate;/*VoiceServiceSignal.t38HsPktRate*/
	/*[0:3]*/
	uint8	highSpeedRedundancy;/*VoiceServiceSignal.t38HsRedun*/
	/*[0:5]*/
	uint8	lowSpeedRedundancy;/*VoiceServiceSignal.t38LsRedun	*/
	/* enum : "Local" ,"NetWork" */
	uint8	TCFMethod;				

/*reserve	uint8	ZyXEL_t38RateMgnt;	*/
/*reserve	uint8	ZyXEL_t38T30Ecm; */

	/*type : VoiceProfObj_t*/
	void*	parent_VoiceProfObj;	
}VoiceProfFaxT38Obj_t;




/*
EventSubscribe.{i}
Table of SIP Events automatically populated by
the CPE with each of the SIP event subscriptions
in the table VoiceService.{i}.VoiceProfile.{i}.SIP.
EventSubscribe.{i}. This table allows specification
of the authentication credentials needed for each
event subscription.
If this table is supported, the capability
VoiceService.{i}.Capabilities.SIP.Event-
Subscription MUST be equal to true and the
parameter SIPEventSubscribeNumberOfElements
in the parent object MUST be present.
-
*/

typedef struct VoiceProfLineSipEventSubObj_st{/*R*/

	char	event[32+1];/*SIP event name corresponding*/
	/*	Username used to authenticate the connection to the event notify server.	*/
	char	authUserName[128+1]; /*def=<empty>	,W*/
	char	authPassword[128+1];	/*def=<empty>,W*/
	/*type : VoiceProfLineSipObj_t*/
	void*	parent_VoiceProfLineSipObj;	
}VoiceProfLineSipEventSubObj_t;



/*ZyXEL_registrarType*/
#define TR104I_REGTYPE_ON	0
#define TR104I_REGTYPE_OFF	1

/*ZyXEL_mixerMode*/
#define TR104I_MIXMODE_LOCAL	0
#define TR104I_MIXMODE_REMOTE	1

/*ZyXEL_remoteRingbackTone*/
#define TR104I_REMOTE_RINGBACK_INACTIVE	0
#define TR104I_REMOTE_RINGBACK_ACTIVE	1

/*ZyXEL_musicOnHoldTone - aircheng add*/
#define TR104I_MUSIC_ONHOLD_INACTIVE	0
#define TR104I_MUSIC_ONHOLD_ACTIVE	1

/*! \brief Obj struct for InternetGatewayDevice.Services.VoiceService.{i}.VoiceProfile.{i}.Line.{i}.SIP.*/
/*Voice line parameters that are specific to SIP call signaling.*/
typedef struct VoiceProfLineSipObj_st{	/*W*/

	char	authUserName[128+1]; /*def = <empty>	,userId*/
	char	authPassword[128+1]; /*def = <empty>	,password*/
	uint8  	ZyXEL_registrarType;		/* On , Off, default:on */

	/*URI by which the user agent will identify itself for this line.¡§sip:UserName@Domain¡¨ , reffer URIscheme*/
	char	URI[389+1];	
	/*self_addr.addr_type*/
	uint8   ZyXEL_url_type;    	/* VoiceServiceSignal.url_type*/
	uint8	ZyXEL_callFwdTableIndex;		/*VoiceServiceSignal.callFwdTableIndex	*/
	/* Select Mixer Mode for Conference Call Value: Local or Remote*/  /* CALL_CONFERENCE */
	uint8	ZyXEL_mixerMode;		/*VoiceServiceSignal.MixerMode*/

/*	uint8	ZyXEL_vmwiAbbrTone;	*/	/*vmwiAbbrTone*/
/* can Get value from Tone event list*/

	uint32	SIPEventSubscribeNumberOfElements;		/*R	*/
	tr104ObjLst_t*	sipEventSubTab;
	/*VoiceProfLineSipEventSubObj_t*  sipEventSubTab;*/
	
#ifdef ZYXEL_SIP_HDR_P_ACCESS_NETWORK_INFO_SUPPORT
		
	/* Curtis 20140417: Sunrise ==> Make the "P-Access-Network-Info" SIP header (RFC3455) to be per-line based */
	char	ZyXEL_P_AccessNetworkInfo[128+1];
		
#endif

	/*type : VoiceProfLineObj_t*/
	void*	parent_VoiceProfLineObj;
}VoiceProfLineSipObj_t	;


/*Ring Event Function*/
#define RINGER_EVENT_DEFAULT 		0 
#define RINGER_EVENT_RINGSPLASH 	1
/*
Ringer.Event.{i}.
Table of events for which a ring pattern is defined.
The table is pre-populated with the complete list of
events for which the CPE supports definition of
ring patterns.
If this table is supported, the parameter Event-
NumberOfEntries in the parent object MUST be
present.
*/
typedef struct VoiceProfLineRingerEventObj_st{	/*R*/
	/*Default , RingSplash*/
	/*char 	function[64+1];*/
	uint8	function;
	/*The EntryID of the entry in the Description table*/
	uint32	ringID; 	/*W*/
	/*type : VoiceProfLineRingerObj_t*/
	void*	parent_VoiceProfLineRingerObj;	
}VoiceProfLineRingerEventObj_t	;

/*

Ringer.Description.{i}.
Each entry in this table defines the contents of an
individual ring specification.
If ability to add, delete, and modify entries in this
table is supported, the capability VoiceService.{i}.-
Capabilities.RingDescriptionsEditable MUST be
equal to true.
If this table is supported, the parameter
DescriptionNumberOfEntries in the parent object
MUST be present.
*/
typedef struct VoiceProfLineRingerDescriptionObj_st{/*W*/
	uint32	entryID;			/*[1:] */
	uint8	ringEnable; 		/*default: FALSE*/
	char	ringName[64+1];	/*default: <empty>*/
	uint32	ringPattern;		/*default : 0 /*map to the entryID of Tone Pattern*/
	char	ringFile[256+1];	/*default: <empty>*/

	/*type : VoiceProfLineRingerObj_t*/
	void*	parent_VoiceProfLineRingerObj;	
}VoiceProfLineRingerDescriptionObj_t	;

/*
Ringer.Pattern.{i}.
Each entry in the table defines a single phase in
an overall ring pattern. Each phase identifies the
entry that corresponds to the next phase.
Each entry in the table refers to the entry that
corresponds to the next phase of the pattern. The
table MAY be set up such that entries form loops,
or MAY end after a finite sequence.
If this object is supported, the capability
VoiceService.{i}.Capabilities.PatternBasedRing-
Generation MUST be equal to true and the
parameter PatternNumberOfEntries in the parent
object MUST be present.
If ability to add, delete, and modify entries in this
table is supported, the capability VoiceService.{i}.-
Capabilities.RingPatternEditable MUST be equal
to true.
*/
typedef struct VoiceProfLineRingerPatternObj_st{	/*W*/

	uint32	entryID;			/*[1:] */
	uint8	ringerOn;		/*default: FALSE*/
	uint32	duration;	/*default : 0*/
	uint32	nextEntryID;		/*default : 0*/

	/*type : VoiceProfLineRingerObj_t*/
	void*	parent_VoiceProfLineRingerObj;	
}VoiceProfLineRingerPatternObj_t	;


/*
This object defines the ring sequences generated
by the VoIP device.
If this object is supported, the capability
VoiceService.{i}.Capabilities.RingGeneration
MUST be equal to true.
*/
typedef struct VoiceProfLineRingerObj_st{ /*R*/

	uint32 	eventNumberOfEntries	;	 
	uint32	descriptionNumberOfEntries	;
	uint32	patternNumberOfEntries	;
	
	/*type : VoiceProfLineRingerEventObj_t*/
	tr104ObjLst_t* ringerEventTab ;
	/*type : VoiceProfLineRingerDescriptionObj_t*/
	tr104ObjLst_t* ringerDescriptionTab ;
	/*type : VoiceProfLineRingerPatternObj_t*/
	tr104ObjLst_t*	ringerPatternTab ;

	/*type : VoiceProfLineObj_t*/
	void*	parent_VoiceProfLineObj;	
}VoiceProfLineRingerObj_t;





#define CALL_FORWARD_UNCONDITIONAL	0x0
#define CALL_FORWARD_BUSY				0x1
#define CALL_FORWARD_NOANSWER		0x2
#define CALL_FORWARD_BLOCK			0x3
#define CALL_FORWARD_ACCEPT			0x4
#define CALL_FORWARD_MAX				0x5

typedef struct {	
	uint8	callFwdFlag;
	uint8	reserved[3];	
	uint8	caller[POTS_PORT_NAME_LEN];
	uint8	forwardTo[POTS_PORT_NAME_LEN];
}ZyXEL_VoiceCallFwdTable_t;	

 
typedef struct {	

/*	uint32	CallForwardOnNoAnswerRingCount;*/		/*VoiceServiceCallFwd.callFwdNoAnsTime*/
/*	uint8	CallForwardUnconditionalNumber[32];*/	/*VoiceServiceCallFwd.callFwdUnconditional*/
/*	uint8	CallForwardOnNoAnswerNumber[32];*/	/*VoiceServiceCallFwd.callFwdNoAnswer*/
/*	uint8	CallForwardOnBusyNumber[32];*/		/*VoiceServiceCallFwd.callFwdBusy*/
	uint8	ZyXEL_reserved[3];					/*VoiceServiceCallFwd.reserved*/
	ZyXEL_VoiceCallFwdTable_t  ZyXEL_callFwdTable[TR104_CALL_FORWARD_TOTAL_ENTRIES];/*VoiceServiceCallFwd.callFwdTable*/
}ZyXEL_VoiceCallFwd_t;	

/* CallWaitingStatus*/
#define TR104I_CWSTATUS_DISABLED	0
#define TR104I_CWSTATUS_IDLE	1
#define TR104I_CWSTATUS_SECONDARYRINGING		2
#define TR104I_CWSTATUS_SECONDARYCONNECTING		3
#define TR104I_CWSTATUS_SECONDARYCONNECTED		4
/*Conference Calling Status*/
#define TR104I_CCSTATUS_DISABLED	0
#define TR104I_CCSTATUS_IDLE	1
#define TR104I_CCCSTATUS_SECONDARYRINGING	2
#define TR104I_CCSTATUS_SECONDARYCONNECTING	3
#define TR104I_CCSTATUS_SECONDARYCONNECTED	4
#define TR104I_CCSTATUS_INCONFERENCECALL	5


/*! \brief Obj struct for InternetGatewayDevice.Services.VoiceService.{i}.
VoiceProfile.{i}.Line.{i}.CallingFeatures.*/
/*CallingFeatures.
object - Voice line parameters related to optional endpoint
based calling features.*/
typedef struct VoiceProfLineCallingFeaturesObj_st{/*W*/

	uint8	callerIDEnable;
	char	callerIDName[256+1];
	uint8	callerIDNameEnable;
	/* used for use P-Asserted-ID as caller id or not. (only bit 0 is used). */
	/*reserve uint8	ZyXEL_usePAssertID;*/				/* usePAssertID   ?*/

	uint8	callWaitingEnable;
	uint8	callWaitingStatus;  		/*R*/
	uint8   ZyXEL_Call_Waiting_Reject_Time;/*in Sec , VoiceServiceFXS.Call_Waiting_Reject_Time*/
	/*
	Indicates the maximum number of simultaneous sessions that may be 
	conferenced together by the endpoint. This value SHOULD be less than the
	value of VoiceService.{i}.Capabilities.Max-SessionsPerLine.
	*/
	uint32	maxSessions;
	uint8	conferenceCallingStatus;				/*R*/
		/* To configure remote conference URI ,reffer conferencecall in Call_mgnt.h*/
	char	ZyXEL_conferenceURI[48+1];		/* VoiceServiceSignal.conferenceURI*/
	uint8	conferenceCallingSessionCount;		/*R*/

	uint8	callForwardUnconditionalEnable;
	uint8	callForwardOnBusyEnable;
	uint8	callForwardOnNoAnswerEnable;
	
	uint32	callForwardOnNoAnswerRingCount;
	char	callForwardUnconditionalNumber[32+1];
	char	callForwardOnBusyNumber[32+1];
	char	callForwardOnNoAnswerNumber[32+1];
	
	ZyXEL_VoiceCallFwd_t*	ZyXEL_VoiceCallFwdTab;

	uint8	callTransferEnable;
	/* Call Transfer after Call Conference*/ 	/* CALL_CONFERENCE */
	uint8	ZyXEL_callTransferAfterConference;	/*	callTransferAfterConference*/
	uint8	ZyXEL_warmLineEnable;	/*	WARMLINE(No Digits Dialled), ND1021 E2.12*/
	char	ZyXEL_warmLineNum[32+1];	/*	should be "digit_timeout" in ND1021 E2.12*/
	uint32	ZyXEL_timerFirstDigitWarmLine;
	uint8	ZyXEL_hotLineEnable;	/*	HOTLINE, ND1021 E2.11*/
	char	ZyXEL_hotLineNum[32+1];	/*	should be "hotline" in ND1021 E2.11*/
	uint8	ZyXEL_missedCallEmailEnable;
	char	ZyXEL_missedCallEmailEvent[64+1];
	uint8	ZyXEL_missedCallEmailServerAddr[64+1];
	char	ZyXEL_missedCallEmailAddr[64+1];
	char	ZyXEL_missedCallEmailTitle[64+1];
	uint8	ZyXEL_CCBSEnable;

	/* Select to send the music on hold signal */
	uint8	ZyXEL_musicOnHoldTone;		/*VoiceServiceSignal.musicOnHoldTone*/
	uint8	ZyXEL_musicOnHoldToneIndex;
	/* Select to send the remote ringback signal ,IVR-related*/
	uint8	ZyXEL_remoteRingbackTone;
	uint8	ZyXEL_remoteRingbackToneIndex;


	uint8	MWIEnable;
	uint32  ZyXEL_mwiExpireTime;
	
	uint8	messageWaiting;			/*R*/

	uint8	anonymousCallBlockEnable;
	uint8	anonymousCallEnable;			/*VoiceServiceSignal.rejectAnonymousCalls*/
	uint8	doNotDisturbEnable;
	uint8	callReturnEnable;
	uint8	repeatDialEnable;				/*VoiceServicesignalautoRedial*/

	/*type : VoiceProfLineObj_t*/
	void*	parent_VoiceProfLineObj;	
}VoiceProfLineCallingFeaturesObj_t	;


/*! \brief Obj struct for InternetGatewayDevice.Services.VoiceService.{i}.VoiceProfile.{i}.Line.{i}.VoiceProcessing.*/
/*
VoiceProcessing.
Voice line parameters related to voice processing
capabilities.
*/
typedef struct VoiceProfLineVoiceProcessingObj_st{/*R*/

	int	transmitGain;		/*VoiceServiceFXS.outVolumeGain	,W*/
	int	receiveGain;			/*VoiceServiceFXS.inVolumeGain	,W*/

	uint8	echoCancellationEnable;		/*VoiceServiceFXS.echoCancelActive	,W*/
	uint8	echoCancellationInUse;		
	uint32	echoCancellationTail;			
	
	/*type : VoiceProfLineObject_t*/
	void*	parent_VoiceProfLineObj;	
}VoiceProfLineVoiceProcessingObj_t	;


/*! \brief Obj struct for InternetGatewayDevice.Services.VoiceService.{i}.VoiceProfile.{i}.Line.{i}.Codec.List.{i}.*/
/*
Table to describe the set of codecs enabled for
use with this line. Each entry in this table refers to
a distinct combination of codec and bit rate.
When a Line is created, this object MUST be
populated with the set of supported codecs
matching the VoiceService.{i}.Capabilities.Codecs
table. The ACS MAY restrict and/or prioritize the
codec support for this profile using this object.
Applicable only for a VoIP endpoint.
*/
typedef struct VoiceProfLineCodecListObj_st{

	uint32	entryID;		/*[1:]*/
	char	codec[64+1];	
	uint32	bitRate;
	uint32	X_ZyXEL_COM_PayloadTypeNum;
	char	packetizationPeriod[64+1];	/*W*/
	/*Indicates support for silence suppression for this codec. If silence suppression is 
	supported, it can be disabled for this codec/bit-rate by setting this parameter to false.*/
	uint8	silenceSuppression;		/*W*/
	
	/*Enable or disable the use of this combination of codec parameters.*/
	uint8	enable;/*def=True	,W*/
	uint32	priority;/*[1:]	,W*/

	/*type : VoiceProfLineCodecObj_t*/
	void*	parent_VoiceProfLineCodecObj;	
#if SILENCE_SUPPRESSION_AND_COMFORT_NOISE_CNOFIG_SEPARATELY	
	uint8 	ZyXEL_comfortNoise; 
#endif

}VoiceProfLineCodecListObj_t	;

/*! \brief Obj struct for InternetGatewayDevice.Services.VoiceService.{i}.VoiceProfile.{i}.Line.{i}.Codec.*/
/*This object indicates the state of the transmit and
receive codec for this voice line instance.*/
typedef struct VoiceProfLineCodecObj_st{	/*R*/


	char	transmitCodec[64];
	char	receiveCodec[64];
	
	uint32	transmitBitRate;
	uint32	receiveBitRate;
	
	/*Whether or not silence suppression is in use for the outgoing voice stream.*/
	uint8	transmitSilenceSuppression;
	/*Whether or not silence suppression is in use for the incoming voice stream.*/
	uint8	receiveSilenceSuppression;	
	
	uint32	transmitPacketizationPeriod;			
	
	/*Table to describe the set of codecs enabled for use with this line.*/
	/*type : VoiceProfLineCodecListObj_t*/
	tr104ObjLst_t*	codecList;

	/*type : VoiceProfLineObject_t*/
	void*	parent_VoiceProfLineObj;		
} VoiceProfLineCodecObj_t	;



/*
Information on each active session associated
with this voice line instance.
*/
typedef struct VoiceProfLineSessionObj_st{/*R*/

	int		sessionStartTime; /*dataTime*/
	/*Duration time of the current session, in seconds.*/
	uint32	sessionDuration;	
		
	/*The IP address of far end VoIP device.*/
	char	farEndIPAddress[64+1];
	/*The UDP port used for current RTP session in the far end device.*/
	uint16	farEndUDPPort;	/*[0:65535]*/
	uint16	localUDPPort; 	/*[0:65535]*/

	/*type : VoiceProfLineObj_t*/
	void*	parent_VoiceProfLineObj;	
}VoiceProfLineSessionObj_t	;

/*! \brief Obj struct for InternetGatewayDevice.Services.VoiceService.{i}.
 VoiceProfile.{i}.Line.{i}.Stats.*/
/*Statistics for this voice line instance.*/
typedef struct VoiceProfLineStatsObj_st{/*R*/

	uint8	resetStatistics;	/*W*/
	
	uint32	packetsSent;
	uint32	packetsReceived;
	uint32	bytesSent;
	uint32	bytesReceived;
	uint32	packetsLost;
	uint32	overruns;
	uint32	underruns;
	
	uint32	incomingCallsReceived;
	uint32	incomingCallsAnswered;
	uint32	incomingCallsConnected;
	uint32	incomingCallsFailed;
	uint32	outgoingCallsAttempted;
	uint32	outgoingCallsAnswered;
	uint32	outgoingCallsConnected;
	uint32	outgoingCallsFailed;

	
	uint32	callsDropped;
	uint32	totalCallTime;
	uint32	serverDownTime;
	uint8	receivePacketLossRate; /*[0:100]*/
	uint8	farEndPacketLossRate;/*[0:100]*/
	
	uint32	receiveInterarrivalJitter;
	uint32	farEndInterarrivalJitter;
	
	uint32	roundTripDelay;
	
	uint32	averageReceiveInterarrivalJitter;
	uint32	averageFarEndInterarrivalJitter;
	uint32	averageRoundTripDelay;

	char LastRegistration[65];
	char LastIncommingNumber[65];
	char LastOutgoingNumber[65];
	bool MWIStatus;

	/*type : VoiceProfLineObj_t*/
	void*	parent_VoiceProfLineObj;		
}VoiceProfLineStatsObj_t	;


/* the SIP Registration Status of line*/
//NOTE: The following definitions MUST sync with the ones in 'be_voiceLine_config.h' of the ZyIMS VoIP's BE module!
//Michael.20131017.001.B: Modify for the SIP Line/Account's Registration Status in the data model.
#if 0
#define TR104I_STATUS_UNKNOWN	-1 /*ZyXEL defined*///Michael.20130614.004: Add.
#define TR104I_STATUS_UP			0
#define TR104I_STATUS_INITIALIZING	1
#define TR104I_STATUS_REGISTERING	2
#define TR104I_STATUS_UNREGISTERING	3
#define TR104I_STATUS_ERROR 		4
#define TR104I_STATUS_TESTING		5
#define TR104I_STATUS_QUIECCENT	6
#define TR104I_STATUS_DISABLED	7
#define TR104I_STATUS_UNREGISTERED	8 /*ZyXEL defined*/
#define TR104I_STATUS_IDLE			9 /*ZyXEL defined*/
#endif
// TODO: It's recommended to modify the following constant macros' naming rule from 'TR104I_STATUS_XXX' ==to==> 'TR104I_SIP_LINE_STATUS_XXX'.
#define TR104I_STATUS_UNKNOWN	0 /*ZyXEL defined*///Michael.20130614.004: Add.
#define TR104I_STATUS_UP			1
#define TR104I_STATUS_INITIALIZING	2
#define TR104I_STATUS_REGISTERING	3
#define TR104I_STATUS_UNREGISTERING	4
#define TR104I_STATUS_ERROR 		5
#define TR104I_STATUS_TESTING		6
#define TR104I_STATUS_QUIECCENT	7
#define TR104I_STATUS_DISABLED	8
#define TR104I_STATUS_UNREGISTERED	9 /*ZyXEL defined*/
#define TR104I_STATUS_IDLE			10 /*ZyXEL defined*/
//Michael.20131017.001.E: Modify for the SIP Line/Account's Registration Status in the data model.

//Michael.20131017.001.B: Add for the SIP Line/Account's Registration Status in the data model.
// TODO: It's recommended to modify the following constant macros' naming rule from 'TR104S_STATUS_XXX' ==to==> 'TR104S_SIP_LINE_STATUS_XXX'.
#define TR104S_STATUS_UNKNOWN		"Unknown" /*ZyXEL defined*/
#define TR104S_STATUS_UP				"Up"
#define TR104S_STATUS_INITIALIZING		"Initializing"
#define TR104S_STATUS_REGISTERING		"Registering"
#define TR104S_STATUS_UNREGISTERING	"Unregistering"
#define TR104S_STATUS_ERROR 			"Error"
#define TR104S_STATUS_TESTING			"Testing"
#define TR104S_STATUS_QUIECCENT		"Quiescent"
#define TR104S_STATUS_DISABLED		"Disabled"
#define TR104S_STATUS_UNREGISTERED	"Unregistered" /*ZyXEL defined*/
#define TR104S_STATUS_IDLE				"Idle" /*ZyXEL defined*/
//Michael.20131017.001.E: Addfor the SIP Line/Account's Registration Status in the data model.


/* the Call State of line*/
// TODO: It's recommended to modify the following constant macros' naming rule from 'TR104I_STATE_XXX' ==to==> 'TR104I_CALL_STATE_XXX'.
#define TR104I_STATE_IDLE			0
#define TR104I_STATE_CALLING		1
#define TR104I_STATE_RINGING		2
#define TR104I_STATE_CONNECTING	3
#define TR104I_STATE_INCALL		4
#define TR104I_STATE_HOLD		5
#define TR104I_STATE_DISCONNECTING	6

//Amber.20170901: Add for support SIP Line CallState info Retrieve via TR069.
#define TR104S_STATE_IDLE			"Idle"
#define TR104S_STATE_CALLING		"Calling"
#define TR104S_STATE_RINGING		"Ringing"
#define TR104S_STATE_CONNECTING		"Connecting"
#define TR104S_STATE_INCALL			"InCall"
#define TR104S_STATE_HOLD			"Hold"
#define TR104S_STATE_DISCONNECTING	"Disconnecting"
#define TR104S_STATE_UNKNOWN		"Unknown"

#define SUPPORTED_INDEX_LEVEL 6

typedef struct objIdx_s
{
    uint8_t level;
    uint8_t idx[SUPPORTED_INDEX_LEVEL];
} objIdx_t;

/*! \brief Obj struct for InternetGatewayDevice.Services.VoiceService.{i}.VoiceProfile.{i}.Line.{i}.*/
/*Object associated with a distinct voice line.
Support for adding and removing lines is
conditional on whether the CPE supports more
than one line in total as indicated by
VoiceService.{i}.Capabilities.MaxLineCount..*/

typedef struct VoiceProfLineObj_st{/*W*/
	
	uint32	ZyXEL_lineId;/*line_id	*/
	uint8	enable;/*def:False	*/
	char	directoryNumber[32+1];/*def:<empty>		,VoiceServiceSignal.portID*/
	uint8	status;	/*def = DISABLE ,R*/
	//Amber.20170901: Add for support SIP Line CallState info Retrieve via TR069.
	//uint8	callState; /* def = IDLE , R*/
	char	callState[128+1]; /* def = IDLE , R*/

	/*A comma separated list of Physical Interface(orignal:FXS list) Identifiers that this Line is associated with.*/
	char	phyReferenceList[32+1];

	/* bit map for SIP_FXS mapping */  /* bit 0 mapping to phone id 0, ... */
	uint32	ZyXEL_phyReferenceFXSList;		/*VoiceServiceSignal.phoneSelect*///Michael.20140205.001: Extend from 'uint8' to 'uint32' to support more Local(Downlink) Phone Port Types.
	uint8   isActive;
	uint8   ZyXEL_AutoDialEnable;			/* Auto Dial Enable/Disable */		
	char	ZyXEL_AutoDialNumber[PSTN_PHONE_NUM_LEN+1];	/* Auto Dial Number */

	uint8	ringMuteStatus;		/*R*/
	uint8	ringVolumeStatus;/*[0:100]	,R*/

	uint8	ZyXEL_CMAcntNum;
	
	VoiceProfLineSipObj_t*  	line_sip;
	VoiceProfLineRingerObj_t*	ringer;
	VoiceProfLineCallingFeaturesObj_t*	callingFeatures;
	VoiceProfLineVoiceProcessingObj_t*	voiceProcessing;
	VoiceProfLineCodecObj_t*	lineCodec;
	tr104ObjLst_t*	sessionLst;
	VoiceProfLineStatsObj_t*	lineStatistics;
/*reserve	ZyXEL_VoicePSTN_t		*voicePSTNPtr;	*/	/* VOIP PSTN */
/*reserve	ZyXEL_VoicePhoneBook_t	*voicePhoneBookPtr;	*/	/* VOIP PhoneBook */

#ifdef ZYXEL_SIP_HDR_P_ACCESS_NETWORK_INFO_SUPPORT
	
		/* Curtis 20140417: Sunrise ==> Make the "P-Access-Network-Info" SIP header (RFC3455) to be per-line based */
		char	ZyXEL_P_AccessNetworkInfo[128+1];
	
#endif

	/*type : VoiceProfObj_t*/
	void*	VoiceProfObjSelect;

    objIdx_t objIid;

}VoiceProfLineObj_t;

/* The definition for VoiceProfObj_st.DTMFMethod , VoiceProfObj_st.DTMFMethodG711 */
#define TR104I_DTMF_NULL		0
#define TR104I_DTMF_INBAND 	1
#define TR104I_DTMF_RFC2833	2
#define TR104I_DTMF_SIPINFO	3
/* PassThrough ( fax , moden)*/
#define TR104I_PASSTHROUGH_DISABLE	0	
#define TR104I_PASSTHROUGH_FORCE		1
#define TR104I_PASSTHROUGH_AUTO		2 /* reserve */

#if 1 /*ZyXEL,Jason ,SIP over TLS*/
#define TR104I_TRANSPORT_UDP		ICF_TRANSPORT_TYPE_UDP	
#define TR104I_TRANSPORT_TCP		ICF_TRANSPORT_TYPE_TCP
#define TR104I_TRANSPORT_TLS		ICF_TRANSPORT_TYPE_TLS
#define TR104I_TRANSPORT_SCTP		TR104I_TRANSPORT_TLS+1
#else
/*Transport*/
#define TR104I_TRANSPORT_UDP		0	
#define TR104I_TRANSPORT_TCP		1
#define TR104I_TRANSPORT_TLS		2
#define TR104I_TRANSPORT_SCTP		3
#endif

//Michael.20130715.002.B: Add to implement the feature to Originate a Media Change for FAX service.
typedef enum zyxelVBDOriginatorType_es
{
	TR104I_VBD_ORIGINATOR_NULL=0,
	TR104I_VBD_ORIGINATOR_UNKNOWN=0,
	TR104I_VBD_ORIGINATOR_DISABLED=0,
	TR104I_VBD_ORIGINATOR_CALLEE, // 1
	TR104I_VBD_ORIGINATOR_CALLER, // 2
	TR104I_VBD_ORIGINATOR_BOTH,	// 3
	TR104I_VBD_ORIGINATOR_AUTO	// 4
	//TR104I_VBD_ORIGINATOR_MAX = TR104I_VBD_ORIGINATOR_AUTO
} zyxelVBDOriginatorType_et;

typedef enum zyxelFaxMode_es
{
	TR104I_FAX_MODE_DISABLE=0,
	TR104I_FAX_MODE_G711PASSTHROUGH, // 1
	TR104I_FAX_MODE_T38RELAY // 2
	//TR104I_FAX_MODE_MAX = TR104I_FAX_MODE_T38RELAY
} zyxelFaxMode_et;
//Michael.20130715.002.E: Add to implement the feature to Originate a Media Change for FAX service.

/*    support Session Refresh Method can config by user , 
	TR104I_SESSION_REFRESH_METHOD_INVITE : session keep alive use INVITE
	TR104I_SESSION_REFRESH_METHOD_UPDATE_PREFER : session keep alive use UPDATE if peer side support UPDATE or use INVITE
	TR104I_SESSION_REFRESH_METHOD_UPDATE_STRICT : session keep alive force to use UPDATE no matter peer side support UPDATE or not
	yushiuan add 2015/01/27 */
typedef enum zyxelSessionRefreshMethod_es
{
	TR104I_SESSION_REFRESH_METHOD_INVITE=0,
	TR104I_SESSION_REFRESH_METHOD_UPDATE_PREFER, // 1
	TR104I_SESSION_REFRESH_METHOD_UPDATE_STRICT // 2
} zyxelSessionRefreshMethod_et;



/*! \brief Obj struct for InternetGatewayDevice.Services.VoiceService.{i}.VoiceProfile.{i}.*/
/* VoiceService_VoiceProfile*/
/*
Object associated with a collection of voice lines
with common uint8acteristics. Support for adding
and removing profiles is conditional on whether
more than one profile is supported as indicated by
VoiceService.{i}.Capabilities.MaxProfileCount. By
default, a single VoiceProfile object SHOULD be
present in a VoiceService, initially in the disabled
state.
*/
/*Reffer cwmpVoIP_Tr104__VoiceProfileInfoTab_s*/
typedef	struct VoiceProfObj_st{/*W*/

	uint32  ZyXEL_ProfObjID;	/*server 1 , server2*/
	uint8	enable;
	/*
	When written as true, forces the all lines in this
	profile to be reset, causing it to re-initialize and
	perform all start-up actions such as registration.
	Always False when read.
	*/
	uint8	reset;
	uint32	numberOfLines;			/*R*/
	char	name[64+1];
	char	signalingProtocol [64+1];
	uint32	maxSessions;
	/* RFC 2388/ PCM / SIP_INFO / RFC_2833_LIKE_SIP_INFO */
	/*char		DTMFMethod[64+1];*/	/*def=<InBand> */
	/*char		DTMFMethodG711[64+1];*/	/*def=<empty>*/
	uint8	DTMFMethod;	/*VoiceServiceSignal.dtmfKeyType*/
	uint8	DTMFMethodG711;

	char	region[2+1]; 				/*Broadcom	:REGION_A3_CHARBUF_SIZE=4 ,ex. "USA"*/
	uint8	ZyXEL_countrycode;			/*VoiceServiceCommon.countrycode*/
#if ZYXEL_VOIP_PLUS_SIGN_BEGINNING_INTL_TELEPHONE_NUM_CLID_DISPLAY_PROCESS_SUPPORT //Michael.20190604.001: Add to support a Manually-Configurable/Customized International PhoneNumber Calling Code parameter for the PlusSign(+)-beginning (International) PhoneNumber CLID Display Process Logic done by 'Michael.20190509.001'.
	char	ZyXEL_region_IntlPhoneNumCallingCode[16+1]; //Designed to store the Country/Region's International Telephone Number's Calling/Dial-In Code (Ref to: https://en.wikipedia.org/wiki/List_of_country_calling_codes). For the (special) config value "0/00/000/0...": is reserved (or regarded as) to indicate: Skip the Rule-1 (<+[CallingCode]:0>), Only do the Phone Number Repalce Rule-2 (<+:00>)!!
#endif //ZYXEL_VOIP_PLUS_SIGN_BEGINNING_INTL_TELEPHONE_NUM_CLID_DISPLAY_PROCESS_SUPPORT.

	char	digitMap[256+1];	
	uint8	digitMapEnable;	

	uint8	STUNEnable;
	char	STUNServer[256+1];   			/*stunServIP*/
	uint16	ZyXEL_stunServPort;			/*stunServPort*/

	uint32	nonVoiceBandwidthReservedUpstream;
	uint32	nonVoiceBandwidthReservedDownstream;

	uint8	PSTNFailOver;/*def=False*/

	/* Voice-Band Data(VBD) service */
	uint8	faxPassThrough;/*VoiceServiceFXS.FAX_Relay*//*Disable,Auto,Force*/
	uint8	ZyXEL_faxPassThroughPCMA; //Michael.20130715.002: This parameter is obsolete!
	uint8	modemPassThrough; /*Disable,Auto,Force*//*def=Auto*/
	//Michael.20130715.002.B: Add to implement the feature to Originate a Media Change for FAX service.
	uint8	ZyXEL_VBD_Originator; /*Disabled,Callee,Caller,Both,Auto*/
	uint8	ZyXEL_FaxMode; /*Disable,G711PassThrough,T38Relay*///FAX Type/Mode Preference for Originating a Media Change for FAX service.
	//Michael.20130715.002.E: Add to implement the feature to Originate a Media Change for FAX service.

	uint8	ZyXEL_SPNum;

#ifdef BUILD_IGNORE_DIRECT_IP
	uint8	ZyXEL_ignoreDirectIP;
#endif //BUILD_IGNORE_DIRECT_IP

	char		ZyXEL_BoundIfName[32+1];	//Candidate Options: "Any_WAN" & "Multi_WAN".
	char		ZyXEL_BoundIfList[255+1];		//Example: "eth4.0, ptm0.1, ppp0.1".
	char		ZyXEL_ActiveBoundIfName[32+1];
#if 1 /* for multiple profile binding multiple wan for ZyIMS, ZyXEL, John */
	uint32	ZyXEL_ActiveBoundIfMark;
#endif
	char		ZyXEL_BoundIpAddr[32+1];	//ZyXEL_'Active'BoundIpAddr.

	/*change name dialMethod (original place X_ZYXEL_Common) to X_ZyXEL_FlashUsageStyle (new place : voiceProf)*/
	uint8	ZyXEL_FlashUsageStyle;

	/*change name voipIOPFlags (original place X_ZYXEL_Common) to ZyXEL_voipIOPFlags (new place : voiceProf)*/
	uint32	ZyXEL_voipIOPFlags;
	//Amber.20180608: Add for new IOPFlags which can be classify IOP functions to (1) Sig(nal): SIP Msg , (2) Media: RTP/T38 Stream.
	uint32	ZyXEL_voipSigIOPFlags;
	uint32	ZyXEL_voipMediaIOPFlags;

	VoiceProfServiceProviderInfoObj_t*	serviceProviderInfo;
	VoiceProfSipObj_t*		SIPObj;
	VoiceProfRtpObj_t*		RTP_Profile;
	VoiceProfNumPlanObj_t*	numberingPlanObj;
	VoiceProfToneObj_t*		toneObj;
	VoiceProfButtonMapObj_t*	buttonMapObj;
	VoiceProfFaxT38Obj_t*	faxT38Obj;

	VoiceProfLineObj_t*	 lineProfPtrLst;

	#if ZYXEL_SIP_DNS_SRV_SUPPORT
	char dnssrvPrimaryServer[SIP_REGISTER_ADDR_LEN+1];
	char dnssrvSecondaryServer[SIP_REGISTER_ADDR_LEN+1];
	#endif //ZYXEL_SIP_DNS_SRV_SUPPORT

	/*type : VoiceServiceObj_t*/
	void*	parent_VoiceServiceObj;
	
#ifdef ZYXEL_SIP_HDR_P_ACCESS_NETWORK_INFO_SUPPORT
	/* Curtis 20131227: Sunrise ==> Support the "P-Access-Network-Info" SIP header (RFC3455) */
	char	ZyXEL_P_AccessNetworkInfo[128+1];
#endif

#if ZYXEL_VOIP_DIAL_PLAN_RULE_LONG_SUPPORT
	char	ZyXEL_digitMap[512+1];
#endif

    objIdx_t objIid;

}VoiceProfObj_t;


#ifdef ZYXEL_PHONE_FXO_SUPPORT
/* reffer from Spt_voip.h*/
typedef  struct ZyXEL_VoiceFXOPort_st{
	uint16	fxoDialLongInterval;
	/* bit map for FXO_FXS mapping. Bit 0: Phone-id 0, ... */
	uint16  	fxoPhoneSelect;			
	
	uint16	fxoDTMFPauseDuration;		/* Duration for DTMF Pause */
	uint16	fxoFlashMinInterval;		/* Flash Min Interval */
	uint16	fxoFlashMaxInterval;		/* Flash Max Interval */
	
	uint16	fxoLifeLineStableTime;		/* The time for the LifeLine becomes stable */
	uint16	fxoDTMFDigitDuration;		/* Duration for DTMF Tone*/
	uint16	reversed2;
	/*polarity reversal*/
	uint32  	pollingPollarityTime;  //for Si3011 polling time
	uint32  	detectCIDInterval;   //for polarity reversal
	/*type :VoiceServiceObj_t*/
	void*	parent_VoiceServiceObj;

} ZyXEL_VoiceFXOPort_t;

/* reffer from Spt_voip.h*/
typedef  struct ZyXEL_VoiceFXO_st{
	uint8 	numberOfPort ;
	ZyXEL_VoiceFXOPort_t* fxoPort;

	/*type :VoiceServiceObj_t*/
	void*	parent_VoiceServiceObj;
} ZyXEL_VoiceFXO_t;
#endif //ZYXEL_PHONE_FXO_SUPPORT


#ifdef ZYXEL_PHONE_DECT_SUPPORT
//for RFStrength
#define	DECT_BS_RF_STRENGTH_LOW		1
#define	DECT_BS_RF_STRENGTH_MID		5
#define	DECT_BS_RF_STRENGTH_HIGH	10
//for baseStatus
#define DECT_BS_BASE_STATUS_ALL_OFF			0
#define DECT_BS_BASE_STATUS_REGISTRATION_ON	1
#define DECT_BS_BASE_STATUS_PAGING_ON		2
#define DECT_BS_BASE_STATUS_BOOTER_MODE		100  //If BS starts up as Booter Mode, it means there are something wrong with its firmware.
#define DECT_BS_BASE_STATUS_DEAD_MODE		200  


typedef struct ZyXEL_VoiceDECT_BaseStation_st {
	uint8	functionEnable;
	char	name[13+1];
	char	PINcode[4+1];
	//===========
	uint8	encryptionEnable;
	uint8	NEMoEnable;
	uint8	ECOModeEnable;
	uint32	RFStrength;	/* 1/5/10--LOW/MID/HIGH */
	//===========	
	char	firmwareVersion[32+1];
	char	EEPROMVersion[32+1];
	char	hardwareVersion[32+1];
	//===========
	uint32	baseStatus;
	//===========
	uint32	registrationModeOnDuration;	//sec
	//===========
	uint32	pagingHSOnDuration; //sec

	
	void*	parent_ZyXEL_DECTObj;
} ZyXEL_VoiceDECT_BaseStation_t;


#define	DECT_HS_TYPE_CMBS_HS_TYPE_GAP		0
#define	DECT_HS_TYPE_CMBS_HS_TYPE_CATIQ_1	1
#define	DECT_HS_TYPE_CMBS_HS_TYPE_CATIQ_2	2
#define	DECT_HS_TYPE_CMBS_HS_TYPE_DSPG		3
#define	DECT_HS_TYPE_CMBS_HS_TYPE_HAN		4


typedef struct ZyXEL_VoiceDECT_Handset_st {
	uint8	registerStatus; /* PP_AttachStatus¡Afalse:unregistered, true:registered */
	char	name[32+1];
	uint8	index; //index from '1', the Handset (physical) index/number provided by the DECT module.
	//===========
	uint8	type;  /*CMBS_HS_TYPE_GAP, 
					CMBS_HS_TYPE_CATIQ_1, 
					CMBS_HS_TYPE_CATIQ_2, 
					CMBS_HS_TYPE_DSPG, 
					CMBS_HS_TYPE_HAN*/
	uint32	modelId; /* PP_ModelId */
	//===========
	uint8	IPEI[5];
	uint8	IPUI[13]; /* uint8 PP_IPUI[16] */
	uint8	TPUI[3]; /* uint8 PP_TPUI[12] */
	//===========
	uint8	EMC[2];
	//===========
	char	internalPhoneNumber[64+1];
	uint8	state; /* PP_Status */
	//===========
	uint32	lineSelect; 	/*sipSelect*/

	uint8	PP_AuthKey[48];
	uint8	PP_CipherKey[24];
	uint8	PP_ServiceClass;
	uint8	PP_SupportWideband;
	
	uint16	MsnIncomingSelect; /* 0:all ringing , bit 0 = msn 1 , bit1= msn 2 */
	uint8	MsnOutgoingSelect;	/* which msn number for outgoing call  , 0 is not setting (use default),   msn 1 = 1,  msn 2 = 2*/

	/* outgpoing interface priority route */
	uint32	OutgoingInterfaceNumber;

	void*	parent_ZyXEL_DECTObj;
} ZyXEL_VoiceDECT_Handset_t;
#endif //ZYXEL_PHONE_DECT_SUPPORT


#define	PHYINTF_TESTSTATE_NONE					1
#define	PHYINTF_TESTSTATE_REQUESTED				2	
#define	PHYINTF_TESTSTATE_COMPLETE				3
#define	PHYINTF_TESTSTATE_ERRORTESTSUPPORTED	4
/*
Voice port tests.
If this object is supported, the capability
VoiceService.{i}.Capabilities.VoicePortTests
MUST be equal to true.
*/
typedef 	struct VoicePhyIntfTests_st{	/*R*/
	/*Indicates the current test state.*/
	uint8	TestStat;/*W*/
	char	TestSelector[64];/*W*/
	uint8	PhoneConnectivity;
	/*type : VoicePhyIntfObj_t*/
	void*	parent_VoicePhyIntfObj;	
}VoicePhyIntfTests_t;


/*! \brief Obj struct for InternetGatewayDevice.Services.VoiceService.{i}.PhyInterface.{i}.*/
/*Each instance is associated with a distinct
physical FXS (Foreign eXchange Station) port.
Instances of this object are statically created by
the CPE.Applicable only for a VoIP Endpoint.*/
/*Broadcom example:
      newObj->interfaceID = iiD - 1;
      sprintf( description,"FXS%d",(iiD-1) );
      sprintf( phyPort,"%01d",(iiD-1) );
*/
/*reffer the hardware setting*/
/* The definition for VoiceServiceFXS_t.dialingType */
#define AUTOMATIC		0
#define TONE				1
#define PULSE			2

/* The definition for VoiceServiceFXS_t.dialToneType */
#define NTT_DIAL_TONE		0
#define PRIVATE_DIAL_TONE	1

/* The definition for VoiceServiceFXS_t.receiveToneType */
#define IR			0
#define VOIP_SIR		1

/* The definition for VoiceServiceFXS_t.potsType */
#define LOOP_START  0
#define GROUND_START 1

/* The definition for VoiceServiceFXS_t.FAX_Relay */
/*
#define FAX_RELAY	0x00
#define T38_FAX	0x01
*/

/* The definition for VoiceServiceFXS_t.CidSignallingType */
#define DURING_RING		0
#define PRIOR_RING		1

/* The definition for spVoiceFXS_t.CidPayloadType */
#define MDMF_CID			0
#define SDMF_CID			1
#define ETSI_MDMF_CID		2
#define DTMF_CID			3
#define UK_CID				4

/*TASType*/
#define LINE_REVE  0
#define RP_AS  1
#define DT_AS  2

typedef 	struct VoicePhyIntfObj_st{	/*R*/
	/*The physical port number on the device.*/
	char		phyPort[2+1];
	uint32	interfaceID;/*[1:]	*/
	char		description[32+1];

	/**********ZyXEL  Configure START**********/	
	uint8   	ZyXEL_PotsType;	/* loop start / ground start */			
	uint8   	ZyXEL_DialingType;	/* DTMF / Dial pulse */
	uint8   	ZyXEL_DialToneType;	
	uint8  	ZyXEL_ReceiveToneType;	
	uint16  	ZyXEL_FlashMaxInterval;		/* Flash Max Interval */
	uint16  	ZyXEL_FlashMinInterval;		/* Flash Min Interval */
	uint16  	ZyXEL_JitterBufSize;
	uint8  	ZyXEL_CallerIDType;	/*DURING_RING/PRIOR_RING*/
	uint8  	ZyXEL_CallerIDPayload; 	/*MDMF_CID,SDMF_CID,DTMF_CID*/
	uint16 	ZyXEL_TasTimeoutInterval;
	uint16 	ZyXEL_TasTimeoutInterval_2;
	uint16 	ZyXEL_CallerIDRingTimeout;
	uint16 	ZyXEL_FirstRingTimoutInterval;
	uint8  	ZyXEL_FirstTASType;	
	uint8 	ZyXEL_SecondTASType;
	uint16  	ZyXEL_CallerID_DTAS_ACK_Timeout;	/* OffHook CallerID DTAS ACK timeout */

	/* bit map for FXS_SIP mapping */ /* bit 0 mapping to SIP-0, ... */
	uint16 	ZyXEL_LineSelect;		/*sipSelect*/
	uint16  	ZyXEL_MsnIncomingSelect; /* 0:all ringing , bit 0 = msn 1 , bit1= msn 2 */
	uint8   	ZyXEL_MsnOutgoingSelect;	/* which msn number for outgoing call  , 0 is not setting (use default),   msn 1 = 1,  msn 2 = 2*/
	uint8   	ZyXEL_HowlerToneTimeout;  /* timeout for howler tone, in seconds */

	/*support for "#" ,VoiceServicePhyInterface.pound*/
	uint8	ZyXEL_pound; /*Boolean*/

#if (ZYXEL_VOIP_PHYINTF_LEVEL_PHONE_HOOK_FLASH_EVENT_IGNORE_SUPPORT) //Michael.20190301.002: Add to Support to Disable/Remove the Phone Hook Flash function by Using a (PhyInterface-level dedicated) Parameter 'X_ZYXEL_HookFlashIgnore' to Ignore the Phone Hook Flash Event. Related Tickets: [eITS#170700466][#39697][HTC], [eITS#180901009][Altibox] and [eITS#181100069][#68892][EU Generic].
	uint8	ZyXEL_HookFlashIgnore; /*Boolean*/
#endif //(ZYXEL_VOIP_PHYINTF_LEVEL_PHONE_HOOK_FLASH_EVENT_IGNORE_SUPPORT).
	/**********ZyXEL Configure END**********/				

	VoicePhyIntfTests_t*   PhyInterfaceTest;

}VoicePhyIntfObj_t;


#ifdef ZYXEL_PHONE_DECT_SUPPORT
typedef struct ZyXEL_VoiceDECT_s {	
	uint32  numberOfHandset;
	ZyXEL_VoiceDECT_BaseStation_t *ZyXEL_DECTBaseStation;
	ZyXEL_VoiceDECT_Handset_t *ZyXEL_DECTHandset;

	/*type :VoiceServiceObj_t*/
	void*	parent_VoiceServiceObj;
} ZyXEL_VoiceDECT_t;
#endif //ZYXEL_PHONE_DECT_SUPPORT


/* VoiceServiceCommon_t.specialFlag */
#if 0 //Old definition and some of them can be replaced by the following 'VoiceProfObj_t.ZyXEL_voipIOPFlags' (was: 'VoiceProfObj_t.voipIOPFlags')!!
#define SPT_SPECIAL_RTP				(1 << 0)	/* bit1: 0/1 disable/enable voice after receiving ACK */
#define SPT_SPECIAL_RFC3265		(1 << 1)	/* bit2: 0/1 disable/enable RFC3265 */
#define SPT_SPECIAL_WALKERSUN 	(1 << 2)	/* bit3: 0/1 enable/disable to quote the auth for qop */
#define SPT_SPECIAL_SENTBY_CHK	(1 << 3)	/* bit4: 0/1 enable/disable sentby check for call ourself */
#define SPT_SPECIAL_T38_REINVITE	(1 << 4) /* BIT5: 0/1 disable/enable send T.38 re-Invite message by caller */
#endif
#define SPT_SPECIAL_REPLACEHASH_ASCII			(1 << 0)	/* bit0: 0/1 disable/enable Replace # to %23 */
#define SPT_SPECIAL_IF_TELENOR					(1 << 1)	/* bit1: 0/1 disable/enable support TELENOR dialplan */
#define SPT_SPECIAL_TERMINAL_PORTABILITY		(1 << 2)	/* bit2: 0/1 disable/enable support Terminal Portability *///#ifdef NORWAY_VOIP_CUSTOMIZATION
#define SPT_SPECIAL_CALLWAITING_TEMPORARILY	(1 << 3)	/* bit3: 0/1 disable/enable support callwaiting temporarily*/


/* VoiceServiceCommon_t.CallFallBack */
#define SPT_FALLBACK_FXOLIFE_FAIL_SIP		(1<<0)
#define SPT_FALLBACK_SIP_FAIL_FXOLIFE		(1<<1)
#define SPT_FALLBACK_FORCE_DIALTONE		(1<<2)

#if 0
/* VoiceServiceCommon_t.dailMethod */
#define CALL_FEATURE_DIAL_METHOD_EUROP		0
#define CALL_FEATURE_DIAL_METHOD_USA		1
#endif
/* VoiceServiceProf_t.FlashUsageStyle */
#define CALL_FEATURE_FLASH_USAGE_STYLE_EUROP	0
#define CALL_FEATURE_FLASH_USAGE_STYLE_USA		1

/*VoiceServiceCommon_t.loggingLevel*/
#define ZyXEL_LOG_ERROR 	3
#define ZyXEL_LOG_NOTICE	5
#define ZyXEL_LOG_DEBUG	7

/*VoiceProfObj_t.ZyXEL_voipIOPFlags (was: VoiceProf_t.voipIOPFlags)*/
#define VOIP_IOP_FLAG_REPLACE_DIGIT								(1 << 0)
#define VOIP_IOP_FLAG_REMOVE_DEFAULT_PORT_IN_REQUEST_URI		(1 << 1)
#define VOIP_IOP_FLAG_REMOVE_ROUTE_HEADER						(1 << 2)
#define VOIP_IOP_FLAG_UPDATE_REQD_NO_UPDATE					(1 << 3)
//#ifdef NEW_ZYIMS_VOIP //Michael.20121023.001: Remarked to be Always Enabled!
#define VOIP_IOP_FLAG_REMOVE_AUTHORIZAION_HEADER_IN_ACK		(1 << 4)
#define VOIP_IOP_FLAG_183_RTP_BIDIRECTION						(1 << 5)
#define VOIP_IOP_FLAG_T38_FAX_STREAM_DO_NOT_CHANGE_PORT		(1 << 6) /*To let T.38 FAX stream use same port as audio stream. Steve 2016-02-01 Add*/
#define VOIP_IOP_FLAG_SUPPORT_OOD_MWI_NOTIFY_WO_SUBSCRIBE	(1 << 7) /*ZYXEL_VOIP_MWI_OOD_NOTIFY_WO_SUBSCRIBE_SUPPORT*/ //Michael.20170914.001: Add to Reserve an VoIP IOP BitFlag '(1 << 7)' to Support the Out-of-Dialog (OOD) NOTIFY for MWI withOut sending SUBSCRIBE first.
#define VOIP_IOP_FLAG_DEREGISTER_LOCAL_CONTACT_ONLY			(1 << 8) /*ZYXEL_SIP_DEREGISTER_LOCAL_CONTACT_ONLY_SUPPORT*/ //Michael.20170926.001: Add to Reserve an VoIP IOP BitFlag '(1 << 8)' to Support to DeRegister Local Contact Only.
#define VOIP_IOP_FLAG_SEND_FORCED_REGISTER_WHEN_OFFHOOK_FROM_IDLE	(1 << 9) /*ZYXEL_VOICE_PHONE_OFFHOOK_TO_FORCE_SIP_REGISTER_SUPPORT*/ //Steve.2018.10.11: [Mobile][Q15] Send forced register when off-hook to make call
#define VOIP_IOP_FLAG_IGNORE_ASSOCIATED_PHONE_HOOK_FLASH_EVENT		(1 << 10) /*ZYXEL_VOIP_PROFILE_LEVEL_PHONE_HOOK_FLASH_EVENT_IGNORE_SUPPORT*/ //Michael.20190301.001: Add to Reserve an (VoiceProfile-level) VoIP IOP BitFlag '(1 << 10)' to Ignore the Phone Hook Flash Event. This is targeted to Support to Disable/Remove the Phone Hook Flash function. Related Tickets: [eITS#170700466][#39697][HTC], [eITS#180901009][Altibox] and [eITS#181100069][#68892][EU Generic].
// TODO: <<NOTE>> Once you Add a New VoIP IOP BitFlag Definition here, you MUST also Add the corresponding 'VoIP IOP BitFlag Detail info Illustration/Dump' action in the function $(ZyIMS)/port/config_sys/$(CONFIG_SYS)/cli_fe/voicecli_config.c/config_showVoipIOPBitFlag_Detail() !!

//Amber.20180608: Add for new IOPFlags which can be classify IOP functions to (1) Sig(nal): SIP Msg , (2) Media: RTP/T38 Stream. 
/*VoiceProfObj_t.ZyXEL_voipSigIOPFlags*/
#define VOIP_SIG_IOP_FLAG_IGNORE_STALE_PARAM_THEN_ONLY_REF_NONCE_DIFF	(1 << 0) //Amber.20190213: Add for authentication header only refer to the different of Nonce and ignore stale parameter.
#define VOIP_SIG_IOP_FLAG_IGNORE_APPENDED_INFO_IN_REQUEST_URI	(1 << 1) //ZYXEL_SIP_IGNORE_APPENDED_INFOMATION_IN_REQUEST_URI. //Amber.20190527: Add to Relax the Validation Logic on the Request URI to accept/tolerate the Non-standard-compliant case: some information (e.g. user=phone, transport=udp) had been appended to the Request URI of SIP CANCEL but NOT append to the Request URI of its coresponding SIP INVITE message.
#define VOIP_SIG_IOP_FLAG_RTP_STATS_HEADER_USE_X_RTP_STAT	(1 << 2) //ZYXEL_SIP_HDR_FOR_AFTER_CALL_RTP_STATS_SEND_IN_BYE_AND_200OK. //Amber.20190521: Add to change default RTP stat header name 'P_RTP_Stat' to 'X_RTP_Stat'.
// TODO: <<NOTE>> Once you Add a New 'Signaling-related' VoIP IOP BitFlag Definition here, you MUST also Add the corresponding '(Signaling-related) VoIP IOP BitFlag Detail info Illustration/Dump' action in the function $(ZyIMS)/port/config_sys/$(CONFIG_SYS)/cli_fe/voicecli_config.c/config_showVoipSigIOPBitFlag_Detail() !!

/*VoiceProfObj_t.ZyXEL_voipMediaIOPFlags*/
// TODO: <<NOTE>> Once you Add a New 'Media-related' VoIP IOP BitFlag Definition here, you MUST also Add the corresponding '(Media-related) VoIP IOP BitFlag Detail info Illustration/Dump' action in the function $(ZyIMS)/port/config_sys/$(CONFIG_SYS)/cli_fe/voicecli_config.c/config_showVoipMediaIOPBitFlag_Detail() !!
//#ifdef NEW_ZYIMS_VOIP //Michael.20121023.001: Remarked to be Always Enabled!


#if ZYXEL_PHONE_CUSTOMIZED_FXS_CLID_PARAMS_SUPPORT //Michael.20190516.002.B: Add two parameters (1)'FxsCIDMode' and (2)'FxsCIDSigProtocol' in the TR-104 data model branch '~.Services.VoiceService.{i}.X_ZYXEL_Common.' to support the feature done by 'Michael.20190516.001' to Manually-Configure/Customize the Caller-ID (CLID) Operation Mode.
typedef enum
{
	FXS_CID_MODE_ONHOOK_RING,
	FXS_CID_MODE_ONHOOK_RPAS,
	FXS_CID_MODE_ONHOOK_DTAS,
	FXS_CID_MODE_ONHOOK_LRAS, //LR+DTAS.
	FXS_CID_MODE_ONHOOK_LRCARIR, //Japan Only.
	FXS_CID_MODE_OFFHOOK, //DTAS Only for the Type-2 (OffHook state) Caller-ID.
	FXS_CID_MODE_OFFHOOK_DTAS = FXS_CID_MODE_OFFHOOK,
} FXS_CID_MODE_e; //Relative to the 'telephonyProfile.h/PSTN_DT_CID_MODE_e'.

#define FXS_CID_MODE_ONHOOK_RING_STR	"onhook_ring"
#define FXS_CID_MODE_ONHOOK_RPAS_STR	"onhook_RPAS"
#define FXS_CID_MODE_ONHOOK_DTAS_STR	"onhook_DTAS"
#define FXS_CID_MODE_ONHOOK_LRAS_STR	"onhook_LRAS"
#define FXS_CID_MODE_ONHOOK_LRCARIR_STR	"onhook_LRCARIR"
#define FXS_CID_MODE_OFFHOOK_STR	"offhook"

typedef enum
{
	FXS_ONHOOK_CID_MODE_DEFAULT,
	//----------------------------------------------------------------
	FXS_ONHOOK_CID_MODE_RING,
	FXS_ONHOOK_CID_MODE_DURING_RING = FXS_ONHOOK_CID_MODE_RING,
	FXS_ONHOOK_CID_MODE_AFTER_RING = FXS_ONHOOK_CID_MODE_RING,
	//----------------------------------------------------------------
	FXS_ONHOOK_CID_MODE_RPAS,
	FXS_ONHOOK_CID_MODE_BEFORE_RING_RPAS = FXS_ONHOOK_CID_MODE_RPAS,
	//----------------------------------------------------------------
	FXS_ONHOOK_CID_MODE_DTAS,
	FXS_ONHOOK_CID_MODE_BEFORE_RING_DTAS = FXS_ONHOOK_CID_MODE_DTAS,
	//----------------------------------------------------------------
	FXS_ONHOOK_CID_MODE_LRAS, //LR+DTAS.
	FXS_ONHOOK_CID_MODE_LRDTAS = FXS_ONHOOK_CID_MODE_LRAS,
	FXS_ONHOOK_CID_MODE_LR_DTAS = FXS_ONHOOK_CID_MODE_LRAS,
	FXS_ONHOOK_CID_MODE_BEFORE_RING_LRAS = FXS_ONHOOK_CID_MODE_LRAS,
	FXS_ONHOOK_CID_MODE_BEFORE_RING_LRDTAS = FXS_ONHOOK_CID_MODE_LRAS,
	FXS_ONHOOK_CID_MODE_BEFORE_RING_LR_DTAS = FXS_ONHOOK_CID_MODE_LRAS,
	//----------------------------------------------------------------
	FXS_ONHOOK_CID_MODE_LRCARIR //Japan Only.
} FXS_ONHOOK_CID_MODE_e;

#define FXS_TYPE1_CID_MODE_e FXS_ONHOOK_CID_MODE_e

typedef enum
{
	FXS_CID_SIG_PROTO_DEFAULT,
	FXS_CID_SIG_PROTO_FSK,
	FXS_CID_SIG_PROTO_DTMF
} FXS_CID_SIG_PROTO_TYPE_e; //Relative to the 'telephonyProfile.h/PSTN_DT_SIG_TYPE_e'.

#define FXS_CID_SIG_PROTO_FSK_STR	"FSK"
#define FXS_CID_SIG_PROTO_DTMF_STR	"DTMF"
#endif //ZYXEL_PHONE_CUSTOMIZED_FXS_CLID_PARAMS_SUPPORT. //Michael.20190516.002.E: Add.


typedef struct ZyXEL_VoiceCommon_st
{
	char 	softwareVersion[128];

	/* Used for User-Agent SIP header */
	char    defaultUserAgentName[128];
	uint8   customUserAgentNameEnable;
	char    customUserAgentName[128];

	char	ifName[INTERFACE_NAME_LEN];/*NW interface*/

/*	char	loggingLevel[24] ;   */ /*ref from  BRCM*/
	uint8	loggingLevel;

	uint8	voipPort;

	uint8	ivrsyspermit;	/*0:not permit, 1: permit*/
	uint8	ivrLanguage;	/* IVR Language */
	uint8	ivrcodec;		/* Codec Used for IVR Record */
	/* Use for the special case about SIP. Bit1: 0/1 disable/enable voice after receiving ACK */
	uint8	specialFlag;
	uint8	callFallBack;

	//uint8	activedialplan; /* dial plan active flag */
	//char	dial_plan[256+1]; /* store area for user defined dial plan */
	//uint8	dialMethod;
	//uint8	voipIOPFlags;

	/*type :VoiceServiceObj_t*/
	void*	parent_VoiceServiceObj;

#ifdef ZYXEL_SIP_HDR_P_ACCESS_NETWORK_INFO_SUPPORT
	/* Curtis 20131227: Sunrise ==> Support the "P-Access-Network-Info" SIP header (RFC3455) */
	char	P_AccessNetworkInfo[128+1];
#endif

    char    userAgent_strReplaceRule[257];

#if ZYXEL_PHONE_CUSTOMIZED_FXS_CLID_PARAMS_SUPPORT //Michael.20190516.002.B: Add two parameters (1)'FxsCIDMode' and (2)'FxsCIDSigProtocol' in the TR-104 data model branch '~.Services.VoiceService.{i}.X_ZYXEL_Common.' to support the feature done by 'Michael.20190516.001' to Manually-Configure/Customize the Caller-ID (CLID) Operation Mode.
	uint8	fxsCIDMode; //corresponding to the above Enum 'FXS_ONHOOK_CID_MODE_e' value.
	uint8	fxsCIDSigProtocol; //corresponding to the above Enum 'FXS_CID_SIG_PROTO_TYPE_e' value.
#endif //ZYXEL_PHONE_CUSTOMIZED_FXS_CLID_PARAMS_SUPPORT. //Michael.20190516.002.E: Add.

	uint16 TLS_Port; //Steve 20190722. Load TLS local port for iptables rule

} ZyXEL_VoiceCommon_t;


/* The definition for VoicePhoneBookSpeedDialBookList_t.name */
#define SPEED_DIAL_NAME_LEN	128

/* The definition for VoicePhoneBookSpeedDialBookList_t.flags */
#define SPEED_DIAL_CONFIGURE		(1<<0)
#define SPEED_DIAL_ACTIVE			(1<<1)

/* The definition for VoicePhoneBookSpeedDialBookList_t.type */
#define SPEED_DIAL_SIP_PROXY		0
#define SPEED_DIAL_SIP_NONPROXY	1

/* Curtis 20140117: Change the ZyXEL_VoicePhoneBook_t and related structures */
typedef struct VoicePhoneBookSpeedDialBookList_s {
	char	origNumber[POTS_PORT_NAME_LEN];
	char	forceSipURI[SIP_DOMAIN_NAME_LEN];
	char	speedNumber[POTS_PORT_NAME_LEN];
	char	name[SPEED_DIAL_NAME_LEN];
	uint16	flags;
	uint16	type;
} VoicePhoneBookSpeedDialBookList_t;

typedef struct VoicePhoneBookSpeedDialBook_s {
	uint32 speedDialBookNumberOfEntries;
	VoicePhoneBookSpeedDialBookList_t *list;
} VoicePhoneBookSpeedDialBook_t;

/* Curtis 20140122: Add Call Policy Book */
/* The definition for VoicePhoneBookCallPolicyBookList_t.direction */
#define CALL_POLICY_BOOK_LIST_DIRECTION_INCOMING	0
#define CALL_POLICY_BOOK_LIST_DIRECTION_OUTGOING	1
/*call block need to add "Both" option , yushiuan 2014/07/22*/
#define CALL_POLICY_BOOK_LIST_DIRECTION_BOTH		2

/* The definition for VoicePhoneBookCallPolicyBookList_t.method */
#define CALL_POLICY_BOOK_LIST_METHOD_UNCONDITIONAL	0
#define CALL_POLICY_BOOK_LIST_METHOD_BUSY			1
#define CALL_POLICY_BOOK_LIST_METHOD_NO_ANSWER		2
#define CALL_POLICY_BOOK_LIST_METHOD_BLOCK			3
#define CALL_POLICY_BOOK_LIST_METHOD_ACCEPT			4
/* The definition for VoicePhoneBookCallPolicyBook_t.type */
#define CALL_POLICY_BOOK_TYPE_BLACKLIST	0
#define CALL_POLICY_BOOK_TYPE_WHITELIST	1

typedef struct VoicePhoneBookCallPolicyBookList_s {
	uint8	enable;
	char	phoneNumber[128+1];
	uint8	direction;
	uint8	method;
	char	forwardToNumber[128+1];
	char	description[128+1];
} VoicePhoneBookCallPolicyBookList_t;

typedef struct VoicePhoneBookCallPolicyBook_s {
	uint32	callPolicyBookNumberOfEntries;
	uint8	type;
	VoicePhoneBookCallPolicyBookList_t *list;
} VoicePhoneBookCallPolicyBook_t;


#if ZYXEL_INTERNAL_PHONEBOOK_SUPPORT

typedef struct VoiceInternalPhoneNumberBookPortList_st{
	int logicalId;										/* Used to recognize ccm, should bind it after ccm initialized */
	int physicalId;										/* Physical ID of phoneCB */
	char PhoneNumber[64+1];								/* Internal phone number get from ccc */
	/*type: VoiceInternalPhoneNumberBookItfList_t*/
	void*	parent_InternalPhoneNumberBookItf;					/* Parent in TR104 */
}VoiceInternalPhoneNumberBookPortList_t;

typedef struct VoiceInternalPhoneNumberBookItfList_st{
	VoiceInternalPhoneNumberBookPortList_t* portList;	/* Port list for this interface */
	uint32 NumberOfPhonePortType;	/* Port number of this interface */ // TODO: SHOULD rename to 'NumberOfPhonePort'!
	char NameOfPhonePortType[64+1];									/* Port type: [X_FXS | X_ISDN_NT | X_DECT] */
	/*type: VoiceInternalPhoneNumberBook_t*/
	void*	parent_InternalPhoneNumberBook;					/* Parent in TR104 */
}VoiceInternalPhoneNumberBookItfList_t;

typedef struct VoiceInternalPhoneNumberBook_st{
	VoiceInternalPhoneNumberBookItfList_t* itfList;		/* Interface list for internal phone */
	uint32 NumberOfInterface;				/* Internal phone interface number */
	/*type: ZyXEL_VoicePhoneBook_t*/
	void*	parent_VoicePhoneBook;						/* Parent in TR104 */
}VoiceInternalPhoneNumberBook_t;

#endif

typedef struct ZyXEL_VoicePhoneBook_s {
	VoicePhoneBookSpeedDialBook_t *speedDialBook;
	VoicePhoneBookCallPolicyBook_t *callPolicyBook;
#if ZYXEL_INTERNAL_PHONEBOOK_SUPPORT
	VoiceInternalPhoneNumberBook_t *internalPhoneNumberBook;
#endif

} ZyXEL_VoicePhoneBook_t;


/* The definition for VoiceServicePSTN_t.flags */
#define PSTN_PREFIX_CODE			(1<<0)
#define PSTN_PHBOOK_ACTIVE			(1<<1)
#define PSTN_PHBOOK_CONFIGURE		(1<<2)
#define SIP_SELECT_NEW				(1<<0)

typedef struct ZyXEL_VoicePSTN_s {
	char	forcePSTNTab[PSTN_PHONE_NUM_LEN];
	uint16	flags;
	char	reversed[2];
} ZyXEL_VoicePSTN_t;

#if 1
/*! \brief Obj struct for InternetGatewayDevice.Services.VoiceService.{i}.typedef ServicesObj _ServicesObject;*/
/*reffer Msm_object.h , VoiceObject*/
typedef struct VoiceServiceObj_st{	/*R*/
	uint32  voiceProfileNumberOfEntries ; /*see TR104_MAXNUMBEROFVOICESERVICE*/
	VoiceCapObj_t* 	voiceCapabilities;
	VoiceProfObj_t*	voiceProfObjArray;
	VoicePhyIntfObj_t*	phyInterface;	//FXS phone port

	//---ZyXEL Private eXtension---
	ZyXEL_VoiceCommon_t*	ZyXEL_voiceCommon;
#ifdef ZYXEL_PHONE_FXO_SUPPORT
	ZyXEL_VoiceFXO_t* ZyXEL_VoiceFXO;
#endif //ZYXEL_PHONE_FXO_SUPPORT
	ZyXEL_VoicePSTN_t* ZyXEL_VoicePSTN;
#ifdef ZYXEL_PHONE_DECT_SUPPORT
	ZyXEL_VoiceDECT_t* ZyXEL_VoiceDECT;
#endif //ZYXEL_PHONE_DECT_SUPPORT
	ZyXEL_VoicePhoneBook_t* ZyXEL_VoicePhoneBook;

}VoiceServiceObj_t;


typedef struct ZyXEL_VoiceSipAccount_st{
uint8	enable;
uint8	sipAccountId;
uint8	SPId;
uint32	LineItr;
uint32	VpItr;
uint8	flag;
VoiceProfObj_t*		ptrProf;
VoiceProfLineObj_t*	ptrLine;
} ZyXEL_VoiceSipAccount_t ;
#endif


#endif //_TR104OBJECT_H_INCLUDE

