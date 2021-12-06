#ifndef __CALL_MGNT_INCLUDE__
#define __CALL_MGNT_INCLUDE__

#include "switch.h" //2014.02.07 Michael.Lin add for 'ZYXEL_PHONE_EACH_TYPE_CH_NUM_MAX'.
#include "event.h"
#include "sys_msg.h"
#include "tr104_object.h"
#include <time.h> //For data type 'time_t' and the standard library function 'time()' to get the system (calendar) time in seconds since the Epoch, 1970-01-01 00:00:00 +0000 (UTC).


/*____________________________________________________________________________*/
/*	macro                                                                                                                         */
/*____________________________________________________________________________*/
//Add internal call event for call status info , yushiuan , 2015/01/14
#ifdef CALL_STATUS_SUPPORT
/* The definition for the CCM centralize log */
#define CCM_LOGS_TYPE_OUTCALL_START				0
#define CCM_LOGS_TYPE_INCALL_START				1
#define CCM_LOGS_TYPE_INTERNALCALL_START			2
#define CCM_LOGS_TYPE_OUTCALL_ESTABLISH			3
#define CCM_LOGS_TYPE_INCALL_ESTABLISH			4
#define CCM_LOGS_TYPE_INTERNALCALL_ESTABLISH	5
#define CCM_LOGS_TYPE_END_CALL					6
#define CCM_LOGS_TYPE_ISDN_CCBS_START			7
#define CCM_LOGS_TYPE_ISDN_CCBS_ESTABLISH		8
#endif //CALL_STATUS_SUPPORT.

#ifdef CALL_STATUS_SUPPORT
/* The definition for the CCM centralize log */
#define CALL_TYPE_IS_NO_CALL 					0
#define CALL_TYPE_IS_EXTERNAL_OUTGOING_CALL	1
#define CALL_TYPE_IS_EXTERNAL_INCOMING_CALL	2
#define CALL_TYPE_IS_INTERNAL_CALL			3
#endif //CALL_STATUS_SUPPORT.


//LOCAL/DL (Downlink) Phone Select Bitmap usage.
//+----------+----------+----------+----------+
//| 31----24 | 23----16 | 15-----8 | 7------0 | (switch.h/ZYXEL_PHONE_EACH_TYPE_CH_NUM_MAX)
//+----------+----------+----------+----------+
//:  ISDN_NT :   DECT   :  ZyPhone :   FXS    : (Ref to the design in: Note (2012.12.03, Mon.)~(2012.12.07, Fri.)Item-2)
//
//Michael.20140820.001.B: Modify.
//#define FXS_SHIFT_BIT 		(0*ZYXEL_PHONE_EACH_TYPE_CH_NUM_MAX)
//#define ZYPHONE_SHIFT_BIT 	(1*ZYXEL_PHONE_EACH_TYPE_CH_NUM_MAX)
//#define DECT_SHIFT_BIT 		(2*ZYXEL_PHONE_EACH_TYPE_CH_NUM_MAX)
//#define ISDN_NT_SHIFT_BIT 	(3*ZYXEL_PHONE_EACH_TYPE_CH_NUM_MAX)
#define LOCAL_PHONE_BITMAP_FXS_SHIFT			(0*ZYXEL_PHONE_EACH_TYPE_CH_NUM_MAX)
#define LOCAL_PHONE_BITMAP_ZYPHONE_SHIFT 	(1*ZYXEL_PHONE_EACH_TYPE_CH_NUM_MAX)
#define LOCAL_PHONE_BITMAP_DECT_SHIFT		(2*ZYXEL_PHONE_EACH_TYPE_CH_NUM_MAX)
#define LOCAL_PHONE_BITMAP_ISDN_NT_SHIFT 	(3*ZYXEL_PHONE_EACH_TYPE_CH_NUM_MAX)
#define LOCAL_PHONE_BITMAP_MASK				0xFF //Michael.20150706.001: Rename from 'LOCAL_PHONE_BIT_MASK' to 'LOCAL_PHONE_BITMAP_MASK'.
//Michael.20140820.001.E: Modify.
#define DOWNLINK_PHONE_PORT_TYPE_MASK		LOCAL_PHONE_BITMAP_MASK //0xFF //Michael.20150706.001: Modify from '0xFF' to 'LOCAL_PHONE_BITMAP_MASK'.

//Michael.20150910.001: Add the definition of the UL(Uplink) Phone (Port Type) Select Bitmap usage.
//UL (Uplink) Phone Select Bitmap usage: this definition is by learning the above one and anticipating the need of the (a)2G(GSM) & (b)3G+4G(LTE)CS-Fallback phone ports.
//+----------+----------+----------+----------+
//| 31----24 | 23----16 | 15-----8 | 7------0 | (switch.h/ZYXEL_PHONE_EACH_TYPE_CH_NUM_MAX)
//+----------+----------+----------+----------+
//:  ISDN_TE : 3G Phone : 2G Phone :   FXO    :
//


//==========================================================================================
/* The definition for the call feature number */
/* for PHONE CONFIG 
if  add call feature define here , please also check
1. modify the CALL_FEATURE_NUMBERS value
2. modify the call feature table for TR104  
*/
#define CALL_FEATURE_IVR						0
#define CALL_FEATURE_INTERNAL_CALL			1
#define CALL_FEATURE_CID_DISPLAY				2	/*enable the caller id for outgoing call*/
#define CALL_FEATURE_CID_HIDDEN				3	/*hidden the caller id for outgoing call*/
#define CALL_FEATURE_CALL_TRANSFER			4
#define CALL_FEATURE_PARK						5	/* CALL_PARK_PICKUP */
#define CALL_FEATURE_PARK_RETRIEVE			6	/* End - CALL_PARK_PICKUP */
#define CALL_FEATURE_RETURN					7	/* redial the last incoming call */
#define CALL_FEATURE_REDIAL					38	/* redial the last outgoing call */
#define CALL_FEATURE_CALL_WAITING_ENABLE			8	/* enable call waiting */
#define CALL_FEATURE_CALL_WAITING_DISABLE			9	/* disable call waiting*/
#define CALL_FEATURE_UNCONDITIONAL_FORWARD_ENABLE		10	/*active call forwarding unconditional */
#define CALL_FEATURE_UNCONDITIONAL_FORWARD_DISABLE	11	/*deactive call forwarding unconditional */
#define CALL_FEATURE_NOANSWER_FORWARD_ENABLE		12	/*active call forwarding no answer */
#define CALL_FEATURE_NOANSWER_FORWARD_DISABLE		13	/*deactive call forwarding no answer */
#define CALL_FEATURE_BUSY_FORWARD_ENABLE			14	/*active call forwarding on busy */
#define CALL_FEATURE_BUSY_FORWARD_DISABLE			15	/*deactive call forwarding on busy */
#define CALL_FEATURE_ONE_SHOT_CID_HIDDEN			16
#define CALL_FEATURE_ONE_SHOT_CID_DISPLAY			17
#define CALL_FEATURE_ONE_SHOT_CALL_WAITING_DISABLE	18
#define CALL_FEATURE_ONE_SHOT_CALL_WAITING_ENABLE	19
#define CALL_FEATURE_ENABLE_WLAN				20	/* enable wlan */
#define CALL_FEATURE_DISABLE_WLAN			21	/* disable wlan */
#define CALL_FEATURE_CALL_PICKUP				22	/* answer someone else¡¦s telephone call. */
#define CALL_FEATURE_ENABLE_DND				23	/* ENABLE DO NOT DISTURB	*/
#define CALL_FEATURE_DISABLE_DND				24	/* DISABLE DO NOT DISTURB	*/
//===(The following feature definitions are mainly from Lantiq/ZyIMS VoIP with patching/merging from Broadcom/ZyIMS VoIP)=========
//Michael.20121023.001.B: Modify to implement the new designed Phone Port CB FSM with the new operation logic
#if 0
#define CALL_FEATURE_CCBS_DEACTIVATE			25	/* CCBS deactivate*/
#define CALL_FEATURE_OUTGOING_SIP				26	/* Use specific SIP for outgoing call, aircheng add */
#define CALL_FEATURE_NUMBERS		27
#endif //0
//Michael.20121023.001.E: Modify to implement the new designed Phone Port CB FSM with the new operation logic
#define CALL_FEATURE_CALL_WAITING_INTERROGATION	25	/* check the Call waiting setting status */
#define CALL_FEATURE_CLIP_INTERROGATION		26	/* check the CLIP setting status */
#define CALL_FEATURE_CLIR_INTERROGATION		27	/* check the CLIR setting status */
//--------------------------------------------------------------------------------------------------------------------
#define CALL_FEATURE_DISABLE_CCBS				28	/* deactive CCBS */
#define CALL_FEATURE_CCBS_DEACTIVATE			28	//25	//from Broadcom/ZyIMS VoIP	/* CCBS deactivate*/
//--------------------------------------------------------------------------------------------------------------------
#define CALL_FEATURE_UNCONDITIONAL_FORWARD_INTERROGATION		29	/* check CFU status */  
#define CALL_FEATURE_NOANSWER_FORWARD_INTERROGATION			30	/* check CFNR status */
#define CALL_FEATURE_BUSY_FORWARD_INTERROGATION				31	/* check CFB status */
#define CALL_FEATURE_SINGLE_INTERNAL_CALL	32	/* Internal call to single port for DT */
#define CALL_FEATURE_OUTGOING_FIX_LINE		33	/* Outgoing call using fix line (FXO/ISDN TE) for DT */
//--------------------------------------------------------------------------------------------------------------------
#define CALL_FEATURE_OUTGOING_SIP				34	/* Outgoing call using SIP for DT */
//#define CALL_FEATURE_OUTGOING_SIP				26	//from Broadcom/ZyIMS VoIP	/* Use specific SIP for outgoing call, aircheng add */
//--------------------------------------------------------------------------------------------------------------------
#define CALL_FEATURE_QUICK_DIAL_VOIP			35	/* SIP quick dial for DT */
#define CALL_FEATURE_FXO_PREFIX				36
#define CALL_FEATURE_HELPDESK_ENABLE			37 	/* Enable HelpDesk by SIP phone */
//--------------------------------------------------------------------------------------------------------------------
#define CALL_FEATURE_NUMBERS		39
//==========================================================================================

//Other feature
#define CALL_FEATURE_THREE_WAY_CONFERENCE	CALL_FEATURE_NUMBERS+1
#define CALL_FEATURE_TRANSFER_TRANSFEREE	CALL_FEATURE_NUMBERS+2
#define CALL_FEATURE_TRANSFER_TARGET			CALL_FEATURE_NUMBERS+3
//--------------------------------------------------------------------------------------------------------------------
#define CALL_FEATURE_MAX_KEY_LEN	42	/*follow TR104, length is 42 */
//==========================================================================================


//==========================================================================================
//yushiuan,2014/08/06 , add these definition , it is also referenced by backend  

#define FACILITYACTION_CALL_FEATURE_IVR				"X_ZYXEL_IVR"
#define FACILITYACTION_CALL_FEATURE_INTERNAL_CALL	"X_ZYXEL_INTERNALCALL"
#define FACILITYACTION_CALL_FEATURE_CID_DISPLAY		"CLIR_DEACTIVATE"
#define FACILITYACTION_CALL_FEATURE_CID_HIDDEN		"CLIR_ACTIVATE"
#define FACILITYACTION_CALL_FEATURE_CALL_TRANSFER	"X_ZYXEL_TRANSFER_ACTIVE"
#define FACILITYACTION_CALL_FEATURE_PARK				"X_ZYXEL_CALL_PARK_ACTIVE"
#define FACILITYACTION_CALL_FEATURE_PARK_RETRIEVE	"X_ZYXEL_CALL_PARK_RETRIEVE"
#define FACILITYACTION_CALL_FEATURE_RETURN			"X_ZYXEL_CALL_RETURN"
#define FACILITYACTION_CALL_FEATURE_CALL_WAITING_ENABLE				"CW_ACTIVATE"
#define FACILITYACTION_CALL_FEATURE_CALL_WAITING_DISABLE				"CW_DEACTIVATE"
#define FACILITYACTION_CALL_FEATURE_UNCONDITIONAL_FORWARD_ENABLE	"CFU_ACTIVATE"
#define FACILITYACTION_CALL_FEATURE_UNCONDITIONAL_FORWARD_DISABLE	"CFU_DEACTIVATE"
#define FACILITYACTION_CALL_FEATURE_NOANSWER_FORWARD_ENABLE			"CFNR_ACTIVATE"
#define FACILITYACTION_CALL_FEATURE_NOANSWER_FORWARD_DISABLE		"CFNR_DEACTIVATE"
#define FACILITYACTION_CALL_FEATURE_BUSY_FORWARD_ENABLE				"CFB_ACTIVATE"
#define FACILITYACTION_CALL_FEATURE_BUSY_FORWARD_DISABLE				"CFB_DEACTIVATE"
#define FACILITYACTION_CALL_FEATURE_ONE_SHOT_CID_HIDDEN				"X_ZYXEL_CA_DISABLE"
#define FACILITYACTION_CALL_FEATURE_ONE_SHOT_CID_DISPLAY				"CA_ACTIVATE"
#define FACILITYACTION_CALL_FEATURE_ONE_SHOT_CALL_WAITING_DISABLE	"X_ZYXEL_ONESHOT_CW_DEACTIVATE"
#define FACILITYACTION_CALL_FEATURE_ONE_SHOT_CALL_WAITING_ENABLE		"X_ZYXEL_ONESHOT_CW_ACTIVATE"
#define FACILITYACTION_CALL_FEATURE_ENABLE_DND		"X_ZYXEL_DND_ENABLE"
#define FACILITYACTION_CALL_FEATURE_DISABLE_DND		"X_ZYXEL_DND_DISABLE"
#define FACILITYACTION_CALL_FEATURE_CALL_WAITING_INTERROGATION		"X_CW_INTERROGATION"
#define FACILITYACTION_CALL_FEATURE_CLIP_INTERROGATION					"X_CLIP_INTERROGATION"
#define FACILITYACTION_CALL_FEATURE_CLIR_INTERROGATION					"X_CLIR_INTERROGATION"
#define FACILITYACTION_CALL_FEATURE_CCBS_DEACTIVATE						"CCBS_DEACTIVATE"
#define FACILITYACTION_CALL_FEATURE_UNCONDITIONAL_FORWARD_INTERROGATION	"CFU_INTERROGATION"
#define FACILITYACTION_CALL_FEATURE_NOANSWER_FORWARD_INTERROGATION			"CFNR_INTERROGATION"
#define FACILITYACTION_CALL_FEATURE_BUSY_FORWARD_INTERROGATION				"CFB_INTERROGATION"
#define FACILITYACTION_CALL_FEATURE_SINGLE_INTERNAL_CALL	"X_SINGLE_INTERNAL_CALL"
#define FACILITYACTION_CALL_FEATURE_OUTGOING_FIX_LINE		"X_OUTGOING_FIX_LINE"
#define FACILITYACTION_CALL_FEATURE_OUTGOING_SIP			"X_ZYXEL_OUTGOING_SIP"
#define FACILITYACTION_CALL_FEATURE_QUICK_DIAL_VOIP			"X_QUICK_DIAL_VOIP"
#define FACILITYACTION_CALL_FEATURE_FXO_PREFIX				"X_FXO_PREFIX"
#define FACILITYACTION_CALL_FEATURE_HELPDESK_ENABLE		"X_HELPDESK_ACTIVE"
#define FACILITYACTION_CALL_FEATURE_REDIAL					"X_ZYXEL_CALL_REDIAL"


//==========================================================================================
///*20150901 brady add, Check immediate dial for phone feature key*/
#define FEATURE_KEY_IS_IMMEDIATEDAIL        1
#define FEATURE_KEY_IS_NOT_IMMEDIATEDAIL    0
#define FEATURE_KEY_IS_NOT_FOUND            (-1)
//==========================================================================================

//*****************************************************************************************************
//Michael.20121023.001.B: Modify to implement the new designed Phone Port CB FSM with the new operation logic
/* The definition for the voiceDspCh->dspPortType & ccmConn->origPortType & ccmConn->peerPortTye*/
#if 0
#define DSP_FXS_PORT			0
#define DSP_FXO_PORT		1
#define DSP_FXO_LIFELINE		2
#define SIP_PORT				3
#define ZYXEL_PHONE_PORT	4
#define ISDN_NT_PORT			5
#define ISDN_TE_PORT			6
#define DSP_DECT_PORT		7
#define MAX_PORT_ROUTE		8
#else //0
#define DSP_FXS_PORT			1
#define DSP_FXO_PORT			2
#define DSP_FXO_LIFELINE		3
#define SIP_PORT					0
#define ZYXEL_PHONE_PORT		4
#define ISDN_NT_PORT			6
#define ISDN_TE_PORT			7
#define DSP_DECT_PORT			5
#define MAX_PORT_ROUTE			8
#endif //0
//Michael.20121023.001.E: Modify to implement the new designed Phone Port CB FSM with the new operation logic
//*****************************************************************************************************


/* The definition for the ccmConn_t->connStatus */
#define CCM_ASSO_ST_MIN				0 //Michael.20140223.001: Add for the debug message for the CCM Associator Event handling.
#define CCM_ASSO_ST_IDLE				0
#define CCM_ASSO_ST_CALLOUT			1
#define CCM_ASSO_ST_CALLIN				2
#define CCM_ASSO_ST_CALLRDY			3
#define CCM_ASSO_ST_INTERACTIVE		4
#define CCM_ASSO_ST_INTERCONN			5
#define CCM_ASSO_ST_CONNREL			6
#define CCM_ASSO_ST_MAX				7
const char* ccmAssociatorStateToName(int ccmAssociatorState); //Michael.20140223.001: Add for the debug message for the CCM Associator Event handling.

/* The definition for the ccmConn_t->flags */
#define CALL_CONN_FLAG_PREASSIGN		(1<<0)
#define CALL_CONN_FLAG_ASSIGN			(1<<1)
#define CALL_CONN_FLAG_PREFIX			(1<<2)
#define CALL_CONN_FLAG_ALERT			(1<<3)
#define CALL_CONN_FLAG_REGISTER		(1<<4)
#define CALL_CONN_FLAG_PEERLOCAL		(1<<5)  //Local Peer Call Conference
#define CALL_CONN_FLAG_CALLPARK		(1<<6)  /* CALL_PARK_PICKUP */
#define CALL_CONN_FLAG_CALLPICKUP		(1<<7)  /* End - CALL_PARK_PICKUP */
#if VISUAL_MWI
#define CALL_CONN_FLAG_VMWI			(1<<8) //already no use in new ZyIMS(git , opal trunk) now , if we need create new CCM flag , the new one can replace this flag , yushiuan ,2015/08/24
#endif //VISUAL_MWI.
#ifndef NEW_ZYIMS_VOIP //Michael.20121023.001 *****************************************************************
#if 1 /*Jason , [SPRID # 090624637]*/
#define CALL_CONN_FLAG_HOLD			(1<<9)
#endif
#if CCBS_SUPPORT
#define CALL_CONN_FLAG_WEBDIAL		(1<<10)	
#endif //CCBS_SUPPORT.
#else //NEW_ZYIMS_VOIP ***************************************************************************************
#define CALL_CONN_FLAG_CALLWAITING_DISABLE	(1<<9)
#define CALL_CONN_FLAG_HOLD			(1<<10)  /*Jason , [SPRID # 090624637]*/
#if CCBS_SUPPORT
#define CALL_CONN_FLAG_WEBDIAL		(1<<11)	
#endif //CCBS_SUPPORT.
#endif //NEW_ZYIMS_VOIP. //Michael.20121023.001 *****************************************************************


/* The definition for the ccmConn_t->connType*/
#define CCM_CONN_TYPE_MIN					0 //Michael.20140223.001: Add for the debug message for the CCM Associator Event handling.
#define CCM_CONN_TYPE_FAIL					0
/*modify ccmconn type by yushiuan 2013/04/22*/
#define CCM_CONN_TYPE_OUTGOING_CALL		1
#define CCM_CONN_TYPE_INCOMMING_CALL	2
#define CCM_CONN_TYPE_INTERNAL_CALL		3
#define CCM_CONN_TYPE_WAIT				4  /* CALL_PARK_PICKUP */
#define CCM_CONN_TYPE_NO_CALL				5  /* End - CALL_PARK_PICKUP */
//#ifdef ZLD_GLOB_TELFORT_FEATURE //Michael.20140223.001: Remrked for the debug message for the CCM Associator Event handling.
/* http://msgsw2.zyxel.com/trac/P2812HNU-F1_Telfort/ticket/492 : when no phone map to the sip number, respond 488 */
#define CCM_CONN_TYPE_NO_MAPPED_PHONE	6
//#endif
#define CCM_CONN_TYPE_CALLER_CALLER	7
#define CCM_CONN_TYPE_CALLEE_CALLEE	8
#define CCM_CONN_TYPE_CALLER_CALLEE	9
#define CCM_CONN_TYPE_MAX				10 //Michael.20140223.001: Add for the debug message for the CCM Associator Event handling.
const char* ccmAssociatorConnTypeToName(int ccmAssociatorConnType); //Michael.20140223.001: Add for the debug message for the CCM Associator Event handling.


/* The definition for the ccmConn_t->connRole */
#define CCM_CONN_ROLE_UNDEF			0
#define CCM_CONN_ROLE_ORIGINAL		1
#define CCM_CONN_ROLE_PEER			2


#define CCM_CALL_TRANSFER			0x01
#define CCM_CONFERENCE_CALL		0x02


/* The definition for the dialDigits_t */
#define MAX_DIAL_STRING_LENGTH	(128+1)		/* The same as "POTS_PORT_NAME_LEN" at spt.h */
#define MAX_CNAME_LENGTH			50			/* The same as "GG_CID_MAX_CNAME_LENGTH" */

/* The definition for the dialInform.dialDigitNumber.dialDigitFlags */
#define DIAL_DIGITAL_FORCE_PSTN		(1<<0)
#define DIAL_DIGITAL_CALLERID_HIDDEN	(1<<1)
#define DIAL_DIGITAL_ONE_SHOT_CID_HIDDEN		(1<<2)
#define DIAL_DIGITAL_ONE_SHOT_CID_DISPLAY	(1<<3)
#define DIAL_DIGITAL_ONE_SHOT_CALL_WAITING_ENABLE	(1<<4)
#define DIAL_DIGITAL_ONE_SHOT_CALL_WAITING_DISABLE	(1<<5)
#ifdef NEW_ZYIMS_VOIP //Michael.20121023.001 *****************************************************************
#define DIAL_DIGITAL_IGNORE_FIRST_POUND_KEY			(1<<6)
#define DIAL_DIGITAL_SIP_FAIL_FALLBACK_PSTN			(1<<7)
#define DIAL_DIGITAL_SIP_FAIL_BACKUP_DIGITMAP_RESULT	(1<<8)
//Michael.20150309.001.B: Add to Support the Emergency Number Phonebook and Append the SIP header "Priority: high" for an Outgoing Emergency Number Call.
//#if ZYXEL_VOIP_EMERGENCY_NUMBER_PHONEBOOK_SUPPORT
#define DIAL_DIGITAL_EMERGENCY_NUMBER		(1<<9)
#define DIAL_DIGITAL_EMERGENCY_NUMBER_CALL	(1<<9)
//#endif //ZYXEL_VOIP_EMERGENCY_NUMBER_PHONEBOOK_SUPPORT.
//Michael.20150309.001.E: Add.

//Amber.20180907: Add to support 3GPP TS24.615 Communication Waiting.
/* The definition for the dialInform.dialDigitNumber.isWaitingCall */
#define IS_WAITING_CALL_INDICATION_GET_FROM_INVITE_BODY			(1<<0)
#define IS_WAITING_CALL_BY_CCM_CHECK_AVAILABLE_PHONECB	(1<<1)
#define IS_WAITING_CALL_GET_FROM_180RINGING_ALERT_INFO_HEADER	(1<<2)
#endif //NEW_ZYIMS_VOIP //Michael.20121023.001 *****************************************************************


#ifdef NEW_ZYIMS_VOIP //Michael.20121023.001 *****************************************************************
/* CallFallBack, The definition for the ccmConn_t->callFallBack */
#define FALLBACK_NONE					(0)
#define SIP_FAIL_FALLBACK_PSTN			(1<<0)
#define PSTN_FAIL_FALLBACK_SIP			(1<<1)
#define FALLBACK_FORCE_DIALTONE		(1<<2)

#define _3WayCallState_None				0
#define _3WayCallState_Outgoing			1		//when the second call is outgoing, the next flash key will trigger threeWayCalling
#define _3WayCallState_CallWaiting		2
#define _3WayCallState_3WayCalling		3
#endif //NEW_ZYIMS_VOIP //Michael.20121023.001 *****************************************************************

#ifdef NEW_ZYIMS_VOIP

typedef enum ccmAssociator_searchIdxType_es
{
	CCM_ASSOCIATOR_SEARCH_IDX_MIN=0,
	CCM_ASSOCIATOR_SEARCH_IDX_CALL_ID=0,  //search CCM associator by call ID
	CCM_ASSOCIATOR_SEARCH_IDX_LODICAL_ID, //search CCM associator by Logical ID (include src and dst logical ID)
	CCM_ASSOCIATOR_SEARCH_IDX_AUTO,       //search CCM associator by call ID and  Logical ID (call ID  first)
	CCM_ASSOCIATOR_SEARCH_IDX_MAX
} ccmAssociator_searchIdxType_et;

#endif


/*____________________________________________________________________________*/
/*	event                                                                                                                          */
/*____________________________________________________________________________*/
//*****************************************************************************************************
//Michael.20121023.001.B: Modify to implement the new designed Phone Port CB FSM with the new operation logic
#if 0
#define	EVT_CCM_ASSIGN_REQ						EVENT( EVT_VOIP_CCM, 0x00)
#define	EVT_CCM_ASSIGN_CONF						EVENT( EVT_VOIP_CCM, 0x01)
#define	EVT_CCM_ASSIGN_IND							EVENT( EVT_VOIP_CCM, 0x02)
#define	EVT_CCM_ASSIGN_FAIL						EVENT( EVT_VOIP_CCM, 0x03)
#define	EVT_CCM_DIAL_REQ							EVENT( EVT_VOIP_CCM, 0x04)
#define	EVT_CCM_DIAL_IND							EVENT( EVT_VOIP_CCM, 0x05)
#define	EVT_CCM_REL_REQ							EVENT( EVT_VOIP_CCM, 0x06)
#define	EVT_CCM_REL_IND							EVENT( EVT_VOIP_CCM, 0x07)
#define	EVT_CCM_REJ_REQ							EVENT( EVT_VOIP_CCM, 0x08)
#define	EVT_CCM_REJ_IND							EVENT( EVT_VOIP_CCM, 0x09)
#define	EVT_CCM_ALERT_REQ							EVENT( EVT_VOIP_CCM, 0x0A)
#define	EVT_CCM_ALERT_IND							EVENT( EVT_VOIP_CCM, 0x0B)
#define	EVT_CCM_CONN_REQ							EVENT( EVT_VOIP_CCM, 0x0C)
#define	EVT_CCM_CONN_IND							EVENT( EVT_VOIP_CCM, 0x0D)
#define	EVT_CCM_CONN_ACK							EVENT( EVT_VOIP_CCM, 0x0E)
#define	EVT_CCM_CONN_CONF							EVENT( EVT_VOIP_CCM, 0x0F)
#define	EVT_CCM_CONN_REQ_TO						EVENT( EVT_VOIP_CCM, 0x10)
#define	EVT_CCM_DISC_REQ							EVENT( EVT_VOIP_CCM, 0x11)
#define	EVT_CCM_DISC_IND							EVENT( EVT_VOIP_CCM, 0x12)
#define	EVT_CCM_DISC_ACK							EVENT( EVT_VOIP_CCM, 0x13)
#define	EVT_CCM_REM_REQ							EVENT( EVT_VOIP_CCM, 0x14)
#define	EVT_CCM_DIAL_DIGIT							EVENT( EVT_VOIP_CCM, 0x15)
#define	EVT_CCM_REG_SUCC							EVENT( EVT_VOIP_CCM, 0x16)
#define	EVT_CCM_UNREG_SUCC						EVENT( EVT_VOIP_CCM, 0x17)
#define	EVT_CCM_MWI								EVENT( EVT_VOIP_CCM, 0x18)
#define	EVT_CCM_NO_MWI							EVENT( EVT_VOIP_CCM, 0x19)
#define	EVT_CCM_FAX_RELAY							EVENT( EVT_VOIP_CCM, 0x1A)
#define	EVT_CCM_MEDIA_CHANGE						EVENT( EVT_VOIP_CCM, 0x1B)
#define	EVT_CCM_ONHOLD_REQ						EVENT( EVT_VOIP_CCM, 0x1C)
#define	EVT_CCM_ONHOLD_CONF						EVENT( EVT_VOIP_CCM, 0x1D)
#define	EVT_CCM_UNHELD_REQ						EVENT( EVT_VOIP_CCM, 0x1F)
#define	EVT_CCM_UNHELD_CONF						EVENT( EVT_VOIP_CCM, 0x20)
#define	EVT_CCM_UNHELD_IND						EVENT( EVT_VOIP_CCM, 0x21)
#define	EVT_CCM_UNATTEND_CALL_TRANS_REQ			EVENT( EVT_VOIP_CCM, 0x22)
#define	EVT_CCM_ATTEND_CALL_TRANS_REQ			EVENT( EVT_VOIP_CCM, 0x23)
#define	EVT_CCM_CALL_TRANS_IND					EVENT( EVT_VOIP_CCM, 0x24)
#define	EVT_CCM_CALL_TRANS_RSP					EVENT( EVT_VOIP_CCM, 0x25)			/* Send out the result */
#define	EVT_CCM_ATTEND_CALL_TRANS_REPLACE		EVENT( EVT_VOIP_CCM, 0x26)			/* For the Transfer-Target */
#define	EVT_CCM_CALL_TRANS_UPDATE					EVENT( EVT_VOIP_CCM, 0x27)			/* Receive the result */
#define	EVT_PHONE_ZYXEL_ONHOOK					EVENT( EVT_VOIP_CCM, 0x28)
#define	EVT_PHONE_ZYXEL_REMOVE					EVENT( EVT_VOIP_CCM, 0x29)			/* Send the ZyPHONE remove event */
#define	EVT_CCM_CHANGE_ASSIGN						EVENT( EVT_VOIP_CCM, 0x2A)
#define	EVT_CCM_FAX_T38							EVENT( EVT_VOIP_CCM, 0x2B)
#define	EVT_CCM_CONFCALL_MEETROOM_REQ			EVENT( EVT_VOIP_CCM, 0x2C)
#define	EVT_CCM_CONFCALL_MEETROOM_CONF			EVENT( EVT_VOIP_CCM, 0x2D)
#define	EVT_CCM_CONFCALL_MEETROOM_FAIL			EVENT( EVT_VOIP_CCM, 0x2E)
#define	EVT_CCM_CONFCALL_JOIN_MEMBER_REQ			EVENT( EVT_VOIP_CCM, 0x2F)
#define	EVT_CCM_CONFCALL_JOIN_MEMBER_CONF		EVENT( EVT_VOIP_CCM, 0x30)
#define	EVT_CCM_3WAYCALL_REMOVE_BASEPHONE		EVENT( EVT_VOIP_CCM, 0x31)
#define	EVT_CCM_3WAYCALL_REMOVE_NEWPHONE		EVENT( EVT_VOIP_CCM, 0x32)
#define	EVT_CCM_3WAYCALL_MEETROOM_DESTROY_MEMBER_LEAVE_REQ	EVENT( EVT_VOIP_CCM, 0x33)
#define	EVT_CCM_3WAYCALL_MEETROOM_DESTROY_MIXER_LEAVE_REQ		EVENT( EVT_VOIP_CCM, 0x34)
#define	EVT_CCM_3WAYCALL_MEETROOM_DESTROY_MEMBER_LEAVE_CONF	EVENT( EVT_VOIP_CCM, 0x35)
#define	EVT_CCM_3WAYCALL_MEETROOM_DESTROY_MIXER_LEAVE_CONF	EVENT( EVT_VOIP_CCM, 0x36)
#define	EVT_CCM_3WAYCALL_MEETROOM_DESTROY						EVENT( EVT_VOIP_CCM, 0x37)
#define	EVT_CCM_3WAYCALL_SWITCH_ACTIVE_PHONE					EVENT( EVT_VOIP_CCM, 0x38)
#define	EVT_CCM_CALL_PARK							EVENT( EVT_VOIP_CCM, 0x39)			/* CALL_PARK_PICKUP */
#define	EVT_CCM_CALL_RESTART						EVENT( EVT_VOIP_CCM, 0x3A)
#define	EVT_CCM_SIPTOPSTN							EVENT( EVT_VOIP_CCM, 0x3B) //SIP->PSTN
#define	EVT_CCM_SDP_ALERT_IND						EVENT( EVT_VOIP_CCM, 0x3C)
#define	EVT_CCM_CONFERENCE_IND					EVENT( EVT_VOIP_CCM, 0x3D)
#define	EVT_CCM_CONFERENCE_CONF					EVENT( EVT_VOIP_CCM, 0x3E)
#ifdef VISUAL_MWI
#define EVT_CCM_NEW_VOICE_MESSAGE		EVENT( EVT_VOIP_CCM, 0x3F)
#define EVT_CCM_NO_NEW_VOICE_MESSAGE	EVENT( EVT_VOIP_CCM, 0x40)
#endif
#if CCBS_SUPPORT
#define	EVT_CCM_WEBDIAL_CHECK			EVENT( EVT_VOIP_CCM, 0x57)
#define	EVT_CCM_WEBDIAL_CONF				EVENT( EVT_VOIP_CCM, 0x58)
#define	EVT_CCM_WEBDIAL_REMOVE			EVENT( EVT_VOIP_CCM, 0x59)
#define	EVT_CCM_WEBDIAL_FAIL				EVENT( EVT_VOIP_CCM, 0x5A)
#define	EVT_CCM_WEBDIAL_REDIAL			EVENT( EVT_VOIP_CCM, 0x5B)
#define	EVT_CCM_WEBDIAL_REDIAL_STOP		EVENT( EVT_VOIP_CCM, 0x5C)
#endif //CCBS_SUPPORT.

#else //0

/* NOTE: Any modification (including any conditional compile flag) of this definition MUST be sync to the 'call_mgnt.c/ccmEventName[]' */
typedef enum ccmEvent_es
{
	EVT_CCM_MIN_ID			= EVENT( EVT_VOIP_CCM, 0x00),
	//------------------------------------------------------------------------------------------
	EVT_CCM_ASSIGN_REQ		= EVENT( EVT_VOIP_CCM, 0x00),
	EVT_CCM_ASSIGN_CONF		= EVENT( EVT_VOIP_CCM, 0x01),
	EVT_CCM_ASSIGN_IND		= EVENT( EVT_VOIP_CCM, 0x02),
	EVT_CCM_ASSIGN_FAIL		= EVENT( EVT_VOIP_CCM, 0x03),
	//------------------------------------------------------------------------------------------
	EVT_CCM_DIAL_REQ			= EVENT( EVT_VOIP_CCM, 0x04), //Outgoing Call
	EVT_CCM_DIAL_IND			= EVENT( EVT_VOIP_CCM, 0x05), //Incoming Call
	//------------------------------------------------------------------------------------------
	EVT_CCM_REL_REQ			= EVENT( EVT_VOIP_CCM, 0x06),
	EVT_CCM_REL_IND			= EVENT( EVT_VOIP_CCM, 0x07),
	//------------------------------------------------------------------------------------------
	EVT_CCM_REJ_REQ			= EVENT( EVT_VOIP_CCM, 0x08),
	EVT_CCM_REJ_IND			= EVENT( EVT_VOIP_CCM, 0x09),
	//------------------------------------------------------------------------------------------
	EVT_CCM_ALERT_REQ			= EVENT( EVT_VOIP_CCM, 0x0A),
	EVT_CCM_ALERT_IND			= EVENT( EVT_VOIP_CCM, 0x0B),
	//------------------------------------------------------------------------------------------
	EVT_CCM_CONN_REQ			= EVENT( EVT_VOIP_CCM, 0x0C),
	EVT_CCM_CONN_IND			= EVENT( EVT_VOIP_CCM, 0x0D),
	EVT_CCM_CONN_ACK			= EVENT( EVT_VOIP_CCM, 0x0E),
	EVT_CCM_CONN_CONF		= EVENT( EVT_VOIP_CCM, 0x0F),
	EVT_CCM_CONN_REQ_TO		= EVENT( EVT_VOIP_CCM, 0x10),
	//------------------------------------------------------------------------------------------
	EVT_CCM_DISC_REQ			= EVENT( EVT_VOIP_CCM, 0x11),
	EVT_CCM_DISC_IND			= EVENT( EVT_VOIP_CCM, 0x12),
	EVT_CCM_DISC_ACK			= EVENT( EVT_VOIP_CCM, 0x13),
	//------------------------------------------------------------------------------------------
	EVT_CCM_REM_REQ			= EVENT( EVT_VOIP_CCM, 0x14),
	//------------------------------------------------------------------------------------------
	EVT_CCM_DIAL_DIGIT		= EVENT( EVT_VOIP_CCM, 0x15),
	//------------------------------------------------------------------------------------------
	EVT_CCM_REG_SUCC				= EVENT( EVT_VOIP_CCM, 0x16), //This event is only sent by&from IPTK via the voiceAppIPTKMsgProcess()-->sipEvtToCCM() to the/some SIP/CCM convertor's relative CCM connector, to indicate the corresponding (IPTK) SIP Account is in "Registered" Status!
	EVT_CCM_SIP_STATUS_REG		= EVENT( EVT_VOIP_CCM, 0x16),
	EVT_CCM_UNREG_SUCC			= EVENT( EVT_VOIP_CCM, 0x17), //This event is only sent by&from IPTK via the voiceAppIPTKMsgProcess()-->sipEvtToCCM() to the/some SIP/CCM convertor's relative CCM connector, to indicate the corresponding (IPTK) SIP Account is in "Un-Registered" Status!
	EVT_CCM_SIP_STATUS_UNREG	= EVENT( EVT_VOIP_CCM, 0x17),
	//------------------------------------------------------------------------------------------
	EVT_CCM_MWI			= EVENT( EVT_VOIP_CCM, 0x18),
	EVT_CCM_NO_MWI		= EVENT( EVT_VOIP_CCM, 0x19),
	//------------------------------------------------------------------------------------------
	EVT_CCM_FAX_RELAY					= EVENT( EVT_VOIP_CCM, 0x1A),
	EVT_CCM_FAX_G711_PASSTHROUGH	= EVENT( EVT_VOIP_CCM, 0x1A), //Michael.20130715.002: Add for the feature to Originate a Media Change for FAX service.
	//------------------------------------------------------------------------------------------
	EVT_CCM_MEDIA_CHANGE	= EVENT( EVT_VOIP_CCM, 0x1B),
	//------------------------------------------------------------------------------------------
	EVT_CCM_ONHOLD_REQ		= EVENT( EVT_VOIP_CCM, 0x1C),
	EVT_CCM_ONHOLD_CONF		= EVENT( EVT_VOIP_CCM, 0x1D),
	EVT_CCM_UNHELD_REQ		= EVENT( EVT_VOIP_CCM, 0x1F),
	EVT_CCM_UNHELD_CONF		= EVENT( EVT_VOIP_CCM, 0x20),
	EVT_CCM_UNHELD_IND		= EVENT( EVT_VOIP_CCM, 0x21),
	//------------------------------------------------------------------------------------------
	EVT_CCM_UNATTEND_CALL_TRANS_REQ	= EVENT( EVT_VOIP_CCM, 0x22),
	EVT_CCM_ATTEND_CALL_TRANS_REQ		= EVENT( EVT_VOIP_CCM, 0x23),
	EVT_CCM_CALL_TRANS_IND				= EVENT( EVT_VOIP_CCM, 0x24),
	EVT_CCM_CALL_TRANS_RSP				= EVENT( EVT_VOIP_CCM, 0x25),	/* Send out the result */
	EVT_CCM_ATTEND_CALL_TRANS_REPLACE	= EVENT( EVT_VOIP_CCM, 0x26),	/* For the Transfer-Target */
	EVT_CCM_CALL_TRANS_UPDATE			= EVENT( EVT_VOIP_CCM, 0x27),	/* Receive the result */
	//------------------------------------------------------------------------------------------
	EVT_PHONE_ZYXEL_ONHOOK	= EVENT( EVT_VOIP_CCM, 0x28),
	EVT_PHONE_ZYXEL_REMOVE	= EVENT( EVT_VOIP_CCM, 0x29),	/* Send the ZyPHONE remove event */
	//------------------------------------------------------------------------------------------
	EVT_CCM_CHANGE_ASSIGN	= EVENT( EVT_VOIP_CCM, 0x2A),
	//------------------------------------------------------------------------------------------
	EVT_CCM_FAX_T38			= EVENT( EVT_VOIP_CCM, 0x2B),
	EVT_CCM_FAX_T38_RELAY	= EVENT( EVT_VOIP_CCM, 0x2B), //Michael.20130715.002: Add for the feature to Originate a Media Change for FAX service.
	//------------------------------------------------------------------------------------------
	EVT_CCM_CONFCALL_MEETROOM_REQ			= EVENT( EVT_VOIP_CCM, 0x2C),
	EVT_CCM_CONFCALL_MEETROOM_CONF			= EVENT( EVT_VOIP_CCM, 0x2D),
	EVT_CCM_CONFCALL_MEETROOM_FAIL			= EVENT( EVT_VOIP_CCM, 0x2E),
	EVT_CCM_CONFCALL_JOIN_MEMBER_REQ		= EVENT( EVT_VOIP_CCM, 0x2F),
	EVT_CCM_CONFCALL_JOIN_MEMBER_CONF		= EVENT( EVT_VOIP_CCM, 0x30),
	//------------------------------------------------------------------------------------------
	EVT_CCM_3WAYCALL_REMOVE_BASEPHONE							= EVENT( EVT_VOIP_CCM, 0x31),
	EVT_CCM_3WAYCALL_REMOVE_NEWPHONE							= EVENT( EVT_VOIP_CCM, 0x32),
	EVT_CCM_3WAYCALL_MEETROOM_DESTROY_MEMBER_LEAVE_REQ		= EVENT( EVT_VOIP_CCM, 0x33),
	EVT_CCM_3WAYCALL_MEETROOM_DESTROY_MIXER_LEAVE_REQ		= EVENT( EVT_VOIP_CCM, 0x34),
	EVT_CCM_3WAYCALL_MEETROOM_DESTROY_MEMBER_LEAVE_CONF	= EVENT( EVT_VOIP_CCM, 0x35),
	EVT_CCM_3WAYCALL_MEETROOM_DESTROY_MIXER_LEAVE_CONF		= EVENT( EVT_VOIP_CCM, 0x36),
	EVT_CCM_3WAYCALL_MEETROOM_DESTROY							= EVENT( EVT_VOIP_CCM, 0x37),
	EVT_CCM_3WAYCALL_SWITCH_ACTIVE_PHONE						= EVENT( EVT_VOIP_CCM, 0x38),
	//------------------------------------------------------------------------------------------
	EVT_CCM_CALL_PARK			= EVENT( EVT_VOIP_CCM, 0x39),	/* CALL_PARK_PICKUP */
	EVT_CCM_CALL_RESTART		= EVENT( EVT_VOIP_CCM, 0x3A),
	//------------------------------------------------------------------------------------------
	EVT_CCM_SIPTOPSTN			= EVENT( EVT_VOIP_CCM, 0x3B),	//SIP->PSTN
	//------------------------------------------------------------------------------------------
	EVT_CCM_SDP_ALERT_IND		= EVENT( EVT_VOIP_CCM, 0x3C),
	//------------------------------------------------------------------------------------------
	EVT_CCM_CONFERENCE_IND	= EVENT( EVT_VOIP_CCM, 0x3D),
	EVT_CCM_CONFERENCE_CONF	= EVENT( EVT_VOIP_CCM, 0x3E),
	//------------------------------------------------------------------------------------------
	//#ifdef VISUAL_MWI
		EVT_CCM_NEW_VOICE_MESSAGE		= EVENT( EVT_VOIP_CCM, 0x3F),
		EVT_CCM_NO_NEW_VOICE_MESSAGE	= EVENT( EVT_VOIP_CCM, 0x40),
	//#endif //VISUAL_MWI

	//===(The following is from Lantiq/ZyIMS VoIP)===================================================================
	EVT_CCM_CALL_TRANSFER_FAIL	= EVENT( EVT_VOIP_CCM, 0x41),
	EVT_CCM_CALL_TRANSFER_SUCC	= EVENT( EVT_VOIP_CCM, 0x42),
	//------------------------------------------------------------------------------------------
	//#ifdef APPS_ZYIMS_DYNAMIC_CODEC
		EVT_CCM_CHANGE_CODEC_REQ	= EVENT( EVT_VOIP_CCM, 0x43),
	//#endif //APPS_ZYIMS_DYNAMIC_CODEC
	//------------------------------------------------------------------------------------------
	//#ifdef ZYXEL_PHONE_ISDN_NT_SUPPORT
		EVT_CCM_ISDN_3WAYCALL_START_REQ	= EVENT( EVT_VOIP_CCM, 0x44),
		EVT_CCM_ISDN_3WAYCALL_START_CONF	= EVENT( EVT_VOIP_CCM, 0x45),
		EVT_CCM_ISDN_3WAYCALL_START_IND	= EVENT( EVT_VOIP_CCM, 0x46),
		EVT_CCM_ISDN_3WAYCALL_END_REQ		= EVENT( EVT_VOIP_CCM, 0x47),
		EVT_CCM_ISDN_3WAYCALL_END_CONF		= EVENT( EVT_VOIP_CCM, 0x48),
		EVT_CCM_ISDN_3WAYCALL_END_IND		= EVENT( EVT_VOIP_CCM, 0x49),
		EVT_CCM_ISDN_CALL_TRANS_REQ			= EVENT( EVT_VOIP_CCM, 0x4A),
		EVT_CCM_ISDN_CALL_TRANS_CONF		= EVENT( EVT_VOIP_CCM, 0x4B),
		EVT_CCM_ISDN_MCID_REQ				= EVENT( EVT_VOIP_CCM, 0x4C),
		EVT_CCM_ISDN_MCID_CONF				= EVENT( EVT_VOIP_CCM, 0x4D),
		EVT_CCM_ISDN_AOC_REQ					= EVENT( EVT_VOIP_CCM, 0x4E),
		EVT_CCM_ISDN_AOC_CONF				= EVENT( EVT_VOIP_CCM, 0x4F),
		EVT_CCM_ISDN_HOLDRESPONSE_TIMEOUT	= EVENT( EVT_VOIP_CCM, 0x50),
		EVT_CCM_SIP_TRANSACTION_FAIL		= EVENT( EVT_VOIP_CCM, 0x51),
		EVT_CCM_RSP_ERR_CODE					= EVENT( EVT_VOIP_CCM, 0x52),
	//#endif //ZYXEL_PHONE_ISDN_NT_SUPPORT
	//------------------------------------------------------------------------------------------
	//#ifdef ZYXEL_PHONE_FXO_SUPPORT
		EVT_CCM_BACKUP_DIGITS	= EVENT( EVT_VOIP_CCM, 0x53),
	//#endif //ZYXEL_PHONE_FXO_SUPPORT
	//------------------------------------------------------------------------------------------
	//#ifdef ZLD_GLOB_TELFORT_FEATURE
	/* http://msgsw2.zyxel.com/trac/P2812HNU-F1_Telfort/ticket/492 : when no phone map to the sip number, respond 488 */
		EVT_CCM_ASSIGN_FAIL_NO_MAPPED_PHONE	= EVENT( EVT_VOIP_CCM, 0x54),
	//#endif //ZLD_GLOB_TELFORT_FEATURE

	//===(The following is from Broadcom/ZyIMS VoIP)===================================================================
	//#if CCBS_SUPPORT
		EVT_CCM_WEBDIAL_CHECK		= EVENT( EVT_VOIP_CCM, 0x55),
		EVT_CCM_WEBDIAL_CONF			= EVENT( EVT_VOIP_CCM, 0x56),
		EVT_CCM_WEBDIAL_REMOVE		= EVENT( EVT_VOIP_CCM, 0x57),
		EVT_CCM_WEBDIAL_FAIL			= EVENT( EVT_VOIP_CCM, 0x58),
		EVT_CCM_WEBDIAL_REDIAL		= EVENT( EVT_VOIP_CCM, 0x59),
		EVT_CCM_WEBDIAL_REDIAL_STOP	= EVENT( EVT_VOIP_CCM, 0x5A),
	//#endif //CCBS_SUPPORT
	//------------------------------------------------------------------------------------------
//#if ZYXEL_VOICE_REMOTE_CONFERENCE
		EVT_CCM_CREATE_XCONF_REQ        = EVENT( EVT_VOIP_CCM, 0x5B),
		EVT_CCM_CREATE_XCONF_CONF        = EVENT( EVT_VOIP_CCM, 0x5C),
		EVT_CCM_ADD_XCONF_PARTY_REQ     = EVENT( EVT_VOIP_CCM, 0x5D),
		EVT_CCM_ADD_XCONF_PARTY_CONF     = EVENT( EVT_VOIP_CCM, 0x5E),
		EVT_CCM_DELETE_XCONF_PARTY_REQ  = EVENT( EVT_VOIP_CCM, 0x5F),
		EVT_CCM_DELETE_XCONF_PARTY_CONF  = EVENT( EVT_VOIP_CCM, 0x60),
		EVT_CCM_RELEASE_XCONF_REQ       = EVENT( EVT_VOIP_CCM, 0x61),
//#endif
	//------------------------------------------------------------------------------------------
	//#if ZYXEL_VOIP_SIP_181_CALL_FORWARDED_PLAY_TONE_TO_ALERT_SUPPORT
		EVT_CCM_CALL_PROGRESS_IND		= EVENT( EVT_VOIP_CCM, 0x62),
	//#endif
	//------------------------------------------------------------------------------------------
	EVT_CCM_MAX_ID
} ccmEvent_et;
const char* ccmEventToName(uint16 ccmEvent);
#endif //0.
//Michael.20121023.001.E: Modify to implement the new designed Phone Port CB FSM with the new operation logic
//*****************************************************************************************************


/*____________________________________________________________________________*/
/*	Data declaration                                                                                                          */
/*____________________________________________________________________________*/
/*Steve. 2014-06-11 Change From dbg_pline_1 to zyPrintf*/
/*
#define CCM_FSM_DBG(fs)						if (ccmDebug & 1)	{	dbg_pline_1((fs));			\
																dbg_pline_1("\n\r"); }
#define CCM_FSM_DBG1(fs, v1)				if (ccmDebug & 1)	{	dbg_plinel_1((fs), (v1));	\
																dbg_pline_1("\n\r"); }
#define CCM_FSM_DBG2(fs, v1, f2, v2)			if (ccmDebug & 1) {	dbg_plinel_1((fs), (v1));	\
																dbg_plinel_1((f2), (v2));	\
																dbg_pline_1("\n\r"); }
#define CCM_FSM_DBG3(fs, v1, f2, v2, f3, v3)	if (ccmDebug & 1) {	dbg_plinel_1((fs), (v1));	\
																dbg_plinel_1((f2), (v2));	\
																dbg_plinel_1((f3), (v3));	\
																dbg_pline_1("\n\r"); }
*/
//Michael.20140815.002.B: Modify to fix the CCM FSM debug message macro function error.
#if 0
#define CCM_FSM_DBG(fs)						if (ccmDebug & 1)	{	zyPrintf((fs));			\
		zyPrintf("\n\r"); }
#define CCM_FSM_DBG1(fs, v1)				if (ccmDebug & 1)	{	zyPrintf((fs), (v1));	\
		zyPrintf("\n\r"); }
#define CCM_FSM_DBG2(fs, v1, f2, v2)			if (ccmDebug & 1) {	zyPrintf((fs), (v1));	\
		zyPrintf((f2), (v2));	\
		zyPrintf("\n\r"); }
#define CCM_FSM_DBG3(fs, v1, f2, v2, f3, v3)	if (ccmDebug & 1) {	zyPrintf((fs), (v1));	\
		zyPrintf((f2), (v2));	\
		zyPrintf((f3), (v3));	\
		zyPrintf("\n\r"); }
#endif
#define CCM_FSM_DBG(fs)						if (ccmDebug & 1)	{	zyPrintf((fs));		\
																zyPrintf("\n\r"); }

#define CCM_FSM_DBG1(fs, v1)				if (ccmDebug & 1)	{	zyPrintf(fs);	\
																zyPrintf("0x%x", v1); \
																zyPrintf("\n\r"); }

#define CCM_FSM_DBG2(fs, v1, f2, v2)			if (ccmDebug & 1)	{	zyPrintf(fs);	\
																zyPrintf("0x%x", v1); \
																zyPrintf(f2); \
																zyPrintf("0x%x", v2); \
																zyPrintf("\n\r"); }

#define CCM_FSM_DBG3(fs, v1, f2, v2, f3, v3)	if (ccmDebug & 1)	{	zyPrintf(fs);	\
																zyPrintf("0x%x", v1); \
																zyPrintf(f2); \
																zyPrintf("0x%x", v2); \
																zyPrintf(f3); \
																zyPrintf("0x%x", v3); \
																zyPrintf("\n\r"); }
//Michael.20140815.002.E: Modify to fix the CCM FSM debug message macro function error.

#define SFILE strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__
#define CCM_PRINTF	if (ccmDebug & 1)	zyPrintf
#define CCM_PRINTF_DTL(...)	if (ccmDebug & 1){zyPrintf("%s:%d:%s()", SFILE, __LINE__, __FUNCTION__); zyPrintf(__VA_ARGS__);}


extern char callFeatureKey[CALL_FEATURE_NUMBERS][CALL_FEATURE_MAX_KEY_LEN];
#if CCBS_SUPPORT
#define ERROR_CAUSE_BUSY_HERE		486
#endif //CCBS_SUPPORT.

//Amber.20180626: To fix PeerNumber of Call Stauts on GUI/CLI only show 32bit Number while remote number is over 32bit. //This is also part of the bugfix of the Redmine issue [#50599][VoIP] Speed Dial cannot accepts send 128 digits number.
//#define WEB_CALLSTATUS_PHONENUM_LENGTH	(32+1)
#define WEB_CALLSTATUS_PHONENUM_LENGTH	(MAX_OUTGOING_REMOTE_PEER_SIP_USERID_LEN+1)
#define WEB_CALLSTATUS_CODEC_LENGTH		(10+1)

/*____________________________________________________________________________*/
/*	type definition                                                                                                             */
/*____________________________________________________________________________*/
typedef struct dialDigitNum_s
{
	uint8 dial_digits[MAX_DIAL_STRING_LENGTH];

#if CCBS_SUPPORT	
	uint8 caller_Dial_Digits_BrforeFilter[MAX_DIAL_STRING_LENGTH];
	uint8 caller_Dial_Digits_BrforeFilter_length;
#endif //CCBS_SUPPORT.

	char force_sipUri[SIP_DOMAIN_NAME_LEN];
	uint16 dial_durations[MAX_DIAL_STRING_LENGTH];
	uint32 dial_timeStampOffsets[MAX_DIAL_STRING_LENGTH];
	uint8 current_length;		/* The dial_digits real length */
	uint8 dialout_length;		/* For the FXO Dialout counter */
	uint16 dialDigitFlags;		/* Dial Digit Flags */
	char dateTime[14];		/* date/time */
	char cname[MAX_CNAME_LENGTH];
	uint8 distinctiveRingId; /* The distinctiveRingId convert form the Incomnig SIP INVITE <Alert-Info> header */
	int isWaitingCall; //Amber.20180907: Add to support 3GPP TS24.615 Communication Waiting.
} dialDigitNum_t;

typedef struct dialInfor_s
{
	dialDigitNum_t	dialDigitNumber;
	uint16 prevLogicId;	/* From which prevLogicId */
} dialInfor_t;

typedef struct dialDigitBuf_s{
	uint8 digitStr;
	uint8 volume;
	uint16 duration;
	uint32 timeStampOffset;
}dialDigitBuf_t;

typedef struct bundleCcm_s
{
	struct ccmConn_s *bundleCcmPrev;
	struct ccmConn_s *bundleCcmNext;
} bundleCcm_t;

/*re-name bundleCcm_s  to bundleCcmConecter_s  , creat a structure : bundleObjDstList_s , yushiuan 2013/04/22*/

typedef struct bundleCcmConecter_s
{
	struct ccmAssociator_s *bundleCcmPrev;
	struct ccmAssociator_s *bundleCcmNext;
} bundleCcmConecter_t;


typedef struct bundleObjDstList_s
{
	struct bundleObjDstList_s *prevObj;
	struct bundleObjDstList_s *nextObj;

	// TODO: SHOULD change the following data type from 'int' to 'uint8' to SYNC the one defined in the 'phfsm.h/typedef struct phonePortCB_s{...}phonePortCB_t' ?!
	int dstPhonePortType; /* destination Port-Type , record the peer side info. ex: FXS to SIP , record the SipCCMConvert PhonePortType */

	uint16 dstPortId; /* destination Port-Id , record the peer side info. ex: FXS to SIP , record the SipCCMConvert LogicalId*/
	uint16 dstFuncId; /* destination Signal , record the peer side info. ex: FXS to SIP , record the SipCCMConvert FuncId*/

	bool newUnattachedPhoneCB;
} bundleObjDstList_t;

/*rename sipCallStatus_t to callStatus_t , generic naming , not only for sip call , yushiuan , 2015/01/14*/
#if 1
typedef struct callStatus_s{
	uint8 status;
	time_t callStartTime;
	char selfNumber[WEB_CALLSTATUS_PHONENUM_LENGTH];
	char peerNumber[WEB_CALLSTATUS_PHONENUM_LENGTH];
	char codec[WEB_CALLSTATUS_CODEC_LENGTH];
	int fromPhonePortType;
	int toPhonePortType;
	int callType;
}callStatus_t;
#endif

typedef struct ccmInternalPhone_s
{
	uint16 peerLogicalId;						/* Record peer ccm's logical ID */
	char phoneNumber[MAX_DIAL_STRING_LENGTH];	/* Internal phone number of this ccm, used to send caller ID */
	char callerName[MAX_CNAME_LENGTH];          /* Internal phone number of this ccm, used to send caller Name */
} ccmInternalPhone_t;


typedef struct ccmConn_s
{
	struct ccmConn_s *prev; 				/* Linked list pointers 	*/
	struct ccmConn_s *next;
	struct ccmConn_s *peerCcmConn;		/* peer ccmConn Linked List pointers*/
	struct bundleCcm_s bundleCcmList;		/* Other bundle ccmConn Link List pointers */
	struct callTransfer_s *callTransferCB;	/* Call transfer control block */
	struct conferencecall_s *ConfCallCB;	/* Call conference control block */ /* CALL_CONFERENCE */
	struct ccmPhoneFeatureCb_s *phoneFeatureCb;
	struct ccmCallRouteCb_s *callRouteCb;
#if CCBS_SUPPORT
	struct webdial_s *WebDialCB;			/*Web Phone Dial block*/
#endif //CCBS_SUPPORT.
	uint16 connSt;						/* connection status */
	uint16 origPortId;						/* original Port-Id */
	uint16 origPortType;					/* original Port-Type */
	uint16 callFeatures;					/* CallFeatures */
	uint16 origFuncId;					/* original Signal */
	uint32 flags;
	dialInfor_t dialInform;					/* Record the dialOut Number */
	uint8   connRole;						/* 0:Not define, 1:original, 2:peer */
	uint8   connType;
	uint8   SipFxsMap;					/* Phone index*/
#ifdef CALLHISTORY_SUPPORT
	uint16 webCallHistoryIndex;	/*[0, MAX_CALL_HISTORY_ENTRY_INCALLS-1] - in calls index range , [MAX_CALL_HISTORY_ENTRY_INCALLS, (MAX_CALL_HISTORY_ENTRY_INCALLS+MAX_CALL_HISTORY_ENTRY_OUTCALLS)-1] - out call index range*/	
#endif //CALLHISTORY_SUPPORT.

	#if 1	/* aircheng add for outgoing sip */
	int outgoingSipAccountId;				/* For outgoing sip phone feature to record outgoing call through specific sip account */
	#endif
} ccmConn_t;

/*redefine CCM Associator by yushiuan 2013/04/22*/
typedef struct ccmAssociator_s
{
	struct ccmAssociator_s *prev; 				/* Linked list pointers */
	struct ccmAssociator_s *next;
	//struct bundleCcmConecter_s bundleCcmList;	/* Other bundle ccmConn Link List pointers */ /*for Incoming Call*/

	struct bundleObjDstList_s *bundleObjDstList;	/*
											  * No matter out-going call or in-comming call , we use this link list to record the usage candidate.
											  * For out-going call , we only have one account information in the list , but in-comming call,
											  * it will have multiple candidates in the list (2 account) . The link list is created while settingup call,
											  *
											  * if terminate the call , the link-list space will be free.
											  * P.S. the account information contains (i)Phone Port Type , (ii)LogicalId , and (iii)funcId.
											  */

	struct bundleObjDstList_s *bundleObjFinalDst;	/* Finally, we have to choice one account to use */


	struct callTransfer_s *callTransferCB;	/* Call transfer control block */
	struct conferencecall_s *ConfCallCB;		/* Call conference control block */ /* CALL_CONFERENCE */
	struct ccmCallFeatureCb_s *callFeatureCb;
	struct ccmCallDecisionCb_s *callDecisionCb;	/*determin this call's src type and dst type */

#if ZYXEL_VOICE_REMOTE_CONFERENCE
	struct remoteConferencecall_s *remoteConfCallCB;
#endif //ZYXEL_VOICE_REMOTE_CONFERENCE

#if ZYXEL_VOICE_DELAY_ONHOLD_ACTION
	tm_id_t delayHoldTimerId; /*Use to keep the timer id of delay on hold action. To stop timer when delete ccm. Steve 2018.10.24*/
#endif //ZYXEL_VOICE_DELAY_ONHOLD_ACTION

	int isBundleListBuild;		/* make sure bundleObjDstList is constructed or not*/
	uint16 callId;                      /*Record call id to determine the call is incomming call or outgoing call*/
	uint16 assoSt;					/* connection status , ccm associator FSM */
	uint16 srcPhonePortId;			/* source phone Port-Id */                							
	uint16 srcPhonePortType;			/* source phone PortType */	
	uint16 srcFuncId;					/* source Signal */  
	uint16 callFeatures;				/* CallFeatures */     
	uint32 flags;
	dialInfor_t dialInform;				/* Record the dialOut Number */
	uint8   connRole;					/* 0:Not define, 1:original, 2:peer  , no use for re-design*/
	uint8   connType;					/* To determin the call is out-going call in-comming call, internal call or fail call ... */
	uint32   SipFxsMap;				/* Phone index*///Michael.20130821.002: Extend from 'uint8' to 'uint16' to sync with 'phfsm.h/struct phonePortCB_s{...}phonePortCB_t.uplinkTypeLineSelect' & 'tr104_object.h/struct VoicePhyIntfObj_st{...}VoicePhyIntfObj_t.ZyXEL_LineSelect'. //20140125(VMG5313 R4876): YuShiuan further extended to 'uint32' to support more phone port types (including DECT).
	uint32   alertedPhoneBitmap;		/* To indicate/represent the Real Alerted (local) phone port(s) in a bitmap sense for the Group Ring feature *///Michael.20140820.001: Add to fix the issue that Some Individual Early Negative Response generated from one of the Group RING phone ports would Block the Incoming Call but make the Reset Selected Phone(s) Continuously RING and won't stop.
	ccmInternalPhone_t internalPhone;	/* Used by associate function to bridege single internal call */
	int outgoingSipAccountId;				/* For outgoing sip phone feature to record outgoing call through specific sip account */
	#if 1 /*CALLHISTORY*/
	#ifdef CALLHISTORY_SUPPORT
	uint16 webCallHistoryIndex;	/*[0, MAX_CALL_HISTORY_ENTRY_INCALLS-1] - in calls index range , [MAX_CALL_HISTORY_ENTRY_INCALLS, (MAX_CALL_HISTORY_ENTRY_INCALLS+MAX_CALL_HISTORY_ENTRY_OUTCALLS)-1] - out call index range*/	
	#endif //CALLHISTORY_SUPPORT.
	#endif // 1.

	/*Originally is sipCallStatus_t , under sip/ccm convert , but to modify it to callStatus_t now ,because one ccm represent one call , and we need to record
    	   internal call info , It's better under CCM , yushiuan , 2015/01/14*/
	callStatus_t callStatus;
	#if 0
	#ifdef APPS_ZYIMS_DYNAMIC_CODEC
	int dynamicCodecCount;
	#endif //APPS_ZYIMS_DYNAMIC_CODEC
	#ifdef ZYXEL_PHONE_FXO_SUPPORT
	uint8 callFallBack;
	#endif //ZYXEL_PHONE_FXO_SUPPORT
	#endif // 0.
} ccmAssociator_t;



typedef struct ccmPhoneFeatureCb_s
{
	struct ccmPhoneFeatureCb_s *prev;
	struct ccmPhoneFeatureCb_s *next;
	void (*funcPtr)(ccmConn_t *ccmConn, int *retCode, int *exitFlag);
}ccmPhoneFeatureCb_t;

typedef struct ccmCallRouteCb_s
{
	struct ccmCallRouteCb_s *prev;
	struct ccmCallRouteCb_s *next;
	void (*funcPtr)(ccmConn_t *ccmConn, int *retCode, int phoneFeature, int *exitFlag);
}ccmCallRouteCb_t;

/*re-name ccmPhoneFeatureCb_s and ccmCallRouteCb_s  to ccmCallFeatureCb_s and ccmCallDecisionCb_s , yushiuan 2013/04/22*/
typedef struct ccmCallFeatureCb_s
{
	struct ccmCallFeatureCb_s *prev;
	struct ccmCallFeatureCb_s *next;
	void (*funcPtr)(ccmAssociator_t *ccmAsso, int *retCode, int *exitFlag);
}ccmCallFeatureCb_t;

typedef struct ccmCallDecisionCb_s
{
	struct ccmCallDecisionCb_s *prev;
	struct ccmCallDecisionCb_s *next;
	void (*funcPtr)(ccmAssociator_t *ccmAsso, int *retCode, int phoneFeature, int *exitFlag);
}ccmCallDecisionCb_t;


typedef struct ccmConnCb_s
{
	ccmConn_t* fxsCcmConn;		/* FXS CCM Conn */
	ccmConn_t* fxoCcmConn;		/* FXO CCM Conn */
	ccmConn_t* sipCcmConn;		/* SIP CCM Conn */
	ccmConn_t* zyxelCcmConn;	/* ZYXEL_PHONE CCM Conn */
} ccmConnCb_t;

/*add ccmDialIndEventData_s by Steve. 2014-12-23*/
typedef struct ccmDialIndEventData_s
{
	bool	master;
}ccmDialIndEventData_t;
/*add ccmAssociatorCb_s by yushiuan 2013/04/22*/
typedef struct ccmAssociatorCb_s
{
#ifdef ZYXEL_PHONE_FXS_SUPPORT
	ccmAssociator_t* fxsCcmAsso;			/* FXS CCM Associator */
#endif //ZYXEL_PHONE_FXS_SUPPORT.

#ifdef ZYXEL_PHONE_DECT_SUPPORT
	ccmAssociator_t* dectCcmAsso;			/* DECT CCM Associator */
#endif //ZYXEL_PHONE_DECT_SUPPORT.

#ifdef ZYXEL_PHONE_FXO_SUPPORT
	ccmAssociator_t* fxoCcmAsso;			/* FXO CCM Associator */
#endif //ZYXEL_PHONE_FXO_SUPPORT.

	ccmAssociator_t* sipCcmAsso;			/* SIP CCM Associator */

#ifdef ZYXEL_PHONE_ISDN_NT_SUPPORT
	ccmAssociator_t* isdnNtCcmAsso;		/* ISDN NT CCM Associator */
#endif //ZYXEL_PHONE_ISDN_NT_SUPPORT.

// TODO: #ifdef ZYXEL_PHONE_ISDN_TE_SUPPORT??

	ccmAssociator_t* zyxelCcmAsso;		/* ZYXEL_PHONE CCM Associator */
} ccmAssociatorCb_t;


#define FAXValue 0xBABEFACE
typedef struct T38Info_s
{
	uint32 FAXFlag;
	uint16 MaxRate;
	uint16 RateMgnt;
} T38Info_t;

//typedef int (*associateTable_t)(ccmConn_t *ccmConn_p, int phoneFeature);
typedef int (*callDecisionTable_t)(ccmAssociator_t *ccmAsso_p, int phoneFeature);


#define ERROR_CCM_CONN_FIND	(-1)

#if 1
typedef struct sipCallStatus_s {
	uint8 status;
	time_t callStartTime;
	char selfNumber[WEB_CALLSTATUS_PHONENUM_LENGTH];
	char peerNumber[WEB_CALLSTATUS_PHONENUM_LENGTH];
	char codec[WEB_CALLSTATUS_CODEC_LENGTH];
	int fromPhonePortType;
	int toPhonePortType;
	int callType;
} sipCallStatus_t;
//#define MAX_SIP_CALL_STATUS 4
#endif

//Michael.20170525.002.B: Add to make the IPTK-initiated 'EVT_CCM_REJ_IND' to CCM/Phone carry additional info of both (a)Remote Response Code and (b)Reason/Cause Id.
typedef struct callDropOrClearDetail_s {
	uint16 sourceType; //Reserved & Un-used Now. //a.k.a: originatorType: SIP_Remote(e.g. ICF_TERMINATE_CALL_IND), SIP_Module(IPTK)(e.g. ICF_UNEXPECTED_MSG_IND), CCM, Phone. This info can be and is usually utilized on How to decode the 'reasonId'.
	uint16 eventId; //Reserved & Un-used Now. //Indicate which the-Just-Received Event to trigger this message, e.g. ICF_TERMINATE_CALL_IND, ICF_UNEXPECTED_MSG_IND, ICF_XXXXXX, EVT_CCM_XXXXXX, EVT_PHONE_XXXXXX.
	uint16 orgEventId; //Reserved & Un-used Now. //(Option Value) Indicate which the-Early-Initiated(&SentOut) Event to trigger the above 'eventId'. Now, Only the eventId 'ICF_UNEXPECTED_MSG_IND' would have and can get this info.
	uint16 responseCode; //(Option Value) Only the SIP_Remote-initiated Outgoing SIP REQuest can get this result.
	uint16 reasonId; //a.k.a: causeId.
} callDropOrClearDetail_t;
//Michael.20170525.002.E: Add.


/*____________________________________________________________________________*/
/*	Data declaration                                                                                                          */
/*____________________________________________________________________________*/
extern ccmConnCb_t ccmConnCb;
extern ccmAssociatorCb_t ccmAssociatorCb;
extern int ccmDebug;

/*____________________________________________________________________________*/
/*	function                                                                                                                      */
/*____________________________________________________________________________*/
int callCtrlInit(void);
void initCcmConn(void);
int ccm_associateConn(evtMsg_t*, ccmConn_t*);
/*add ccm_DecideCallRuleAndPeerSideObj for redesign by yushiuan 2013 /04/23*/
int ccm_DecideCallRuleAndPeerSideObj(evtMsg_t*, ccmAssociator_t*);


int callDecisionFxs2Sip(ccmAssociator_t* ccmAsso_p, int phoneFeature);
int callDecisionSip2Fxs(ccmAssociator_t* ccmAsso_p, int phoneFeature);
int callDecisionFxs2Fxs(ccmAssociator_t* ccmAsso_p, int phoneFeature);
//Michael.20140904.003.B: Modify to patch the CCM module's DECT-2-ZyPhone Association Function to make DECT Phone also support dialing the Feature Key number to config some VoIP Phone/Call features.
//int callDecisionFxs2ZyPhone(ccmAssociator_t* ccmAsso_p, int phoneFeature);
int callDecisionPhyLocalPhone2ZyPhone(ccmAssociator_t* ccmAsso_p, int phoneFeature);
#define callDecisionFxs2ZyPhone callDecisionPhyLocalPhone2ZyPhone
#define callDecisionDect2ZyPhone callDecisionPhyLocalPhone2ZyPhone
//Michael.20140904.003.E: Modify.
int callDecisionDect2Sip(ccmAssociator_t* ccmAsso_p, int phoneFeature);
int callDecisionSip2Dect(ccmAssociator_t* ccmAsso_p, int phoneFeature);
int callDecisionDect2Dect(ccmAssociator_t* ccmAsso_p, int phoneFeature);
int callDecisionFxs2Dect(ccmAssociator_t* ccmAsso_p, int phoneFeature);
int callDecisionDect2Fxs(ccmAssociator_t* ccmAsso_p, int phoneFeature);
int callDecisionZyPhone2Sip(ccmAssociator_t* ccmAsso_p, int phoneFeature);



int callDecisionFxs2FxoLife(ccmConn_t* ccmConn_p, int fxsTranslate);
int callDecisionFxs2Fxo(ccmConn_t* ccmConn_p, int phoneFeature);
int callDecisionFxoLife2Fxs(ccmConn_t* ccmConn_p, int phoneFeature);
int callDecisionFxo2Fxs(ccmConn_t* ccmConn_p, int phoneFeature);

int callDecisionSip2ZyPhone(ccmAssociator_t* ccmAsso_p, int phoneFeature);
int callDecisionZyPhone2Fxs(ccmConn_t* ccmConn_p, int phoneFeature);
int ccm_bundleConn(ccmConn_t* ccmConn_p, ccmConn_t* peerCcmConn_p, uint16 connStatus, uint8 connType);
int ccm_bundleForkConn(ccmConn_t* ccmConn_p, ccmConn_t* peerCcmConn_p, ccmConn_t* prePeerCcmConn_p, uint16 connStatus, uint8 connType);

/*redefine ccm_bundleConn to  ccm_linkPeersidePhonePortTypeObj  by yushiuan 2013/04/23 */
int ccm_linkPeerSidePhonePortTypeObj(ccmAssociator_t* ccmAsso_p, uint16 searchIndex, uint8 dstPhonePortType, uint8 connType);
int ccm_getPhonePortTypeShiftBits_in_localPhoneBitmap(uint8 phonePortType); //Michael.20140820.001: Add to fix the issue that Some Individual Early Negative Response generated from one of the Group RING phone ports would Block the Incoming Call but make the Reset Selected Phone(s) Continuously RING and won't stop.


int ccm_releaseConn(ccmConn_t* ccmConn_p);
int ccm_releaseOtherChann(ccmConn_t* ccmConn_p, ccmConn_t* ccmBundleHead);

/*add ccm_releaseAssociator for re-design by yushiuan 2013/04/25*/
int ccm_releaseAssociator(ccmAssociator_t* ccmAsso_p);

/*add ccm_releaseNoUsePhoneLogicalId by yushiuan 2012/04/25*/
int ccm_releaseNoUsePhoneLogicalId(ccmAssociator_t* ccmAsso_p, uint16 phoneLogicalId);

int createPhoneFeatureCB(ccmConn_t*, dialInfor_t*, int);

void constructCallFeatureCb(ccmConn_t* ccmConn_p);
void createCallFeatureCb(ccmConn_t *ccmConn_p, void (*func_p));
void constructCallRouteCb(ccmConn_t* ccmConn_p);
void createCallRouteCb(ccmConn_t *ccmConn_p, void (*func_p));

/*add constructCallFeatureKeyCb prototype by yushiuan 2013/04/22*/
void constructCallFeatureKeyCb(ccmAssociator_t* ccmAsso_p);
void createCallFeatureKeyCb(ccmAssociator_t *ccmAsso_p, void (*func_p));
void constructCallDecisionCb(ccmAssociator_t* ccmAsso_p);
void createCallDecisionCb(ccmAssociator_t *ccmAsso_p, void (*func_p));

/*20150901 brady add, Check immediate dial for phone feature key*/
int isImmediateDialPhoneFeatureKey(char* tr104FacilityAction);

/*add createbundleObjDstList to record peer side information : porttype , logicalid and funcid  by yushiuan 2013/04/23*/
void createbundleObjDstList(ccmAssociator_t* ccmAsso_p);
/*add ccm_setAssociatorParameters to assign value to ccm associator by yushiuan 2013/04/23*/
int ccm_setAssociatorParameters(ccmAssociator_t* ccmAsso_p, uint8 connType);



#ifdef DIAL_PLAN
void ccmDialPlanRoute(ccmAssociator_t *ccmAsso, int *retCode, int phoneFeature, int *exitFlag);
#endif //DIAL_PLAN.
void checkPSTNPhoneBook(	ccmConn_t *ccmConn, int *retCode, int *exitFlag);

#ifdef SPEED_DIAL
void checkSpeedDialFeature(ccmAssociator_t *ccmAsso, int *retCode, int *exitFlag);
void checkSpeedDialPhBook(dialDigitNum_t *dialDigitNum_p);
#endif //SPEED_DIAL.

//Michael.20150309.001.B: Add to Support the Emergency Number Phonebook and Append the SIP header "Priority: high" for an Outgoing Emergency Number Call.
#if ZYXEL_VOIP_EMERGENCY_NUMBER_PHONEBOOK_SUPPORT
void checkEmergencyNumberCallFeature(ccmAssociator_t *ccmAsso, int *retCode, int *exitFlag);
void checkEmergencyNumberPhBook(dialDigitNum_t *dialDigitNum_p);
#endif //ZYXEL_VOIP_EMERGENCY_NUMBER_PHONEBOOK_SUPPORT.
//Michael.20150309.001.E: Add.

void checkDefaultFeature(ccmAssociator_t *ccmAsso, int *retCode, int *exitFlag);
void ccmDefaultRoute(ccmAssociator_t *ccmAsso, int *retCode, int phoneFeature, int *exitFlag);
#ifdef ZYXEL_PHONE_FXO_SUPPORT
void ccmForceToPstn(ccmAssociator_t *ccmAsso, int *retCode, int phoneFeature, int *exitFlag);
#endif //ZYXEL_PHONE_FXO_SUPPORT
void ccmPhoneFeatureRoute(ccmAssociator_t *ccmAsso, int *retCode, int phoneFeature, int *exitFlag);

//Kenny.20140122.001 *****************************************************************
#ifdef CALL_STATUS_SUPPORT
#ifdef NEW_ZYIMS_VOIP
void ccmCentralizeLog(ccmAssociator_t *ccmAsso_p, uint16 logsType);
#else
void ccmCentralizeLog(ccmConn_t *ccmConn_p, uint16 logsType);
#endif
#endif //CALL_STATUS_SUPPORT.

#ifdef DO_NOT_DISTURB
void checkDNDFeature(ccmAssociator_t *ccmAsso, int *retCode, int *exitFlag);
void ccmDNDRoute(ccmAssociator_t *ccmAsso, int *retCode, int phoneFeature, int *exitFlag) ;
#endif //DO_NOT_DISTURB.

#if CCBS_SUPPORT
void ccmWebDialRoute(ccmConn_t *ccmAsso, int *retCode, int phoneFeature, int *exitFlag) ;
#endif //CCBS_SUPPORT.

ccmConn_t* create_ccmConn(uint8 portType, uint16 chId, uint16  origFuncId, uint8 phoneSelect);

/*add create_ccmAssociator prototype by yushiuan 2013/04/22*/
ccmAssociator_t* construct_ccmAssociator(uint8 phoneportType, uint16 chId, uint16 origFuncObject, uint32 sipPhoneSelectMap); //Michael.20140205.001: Rename from 'phoneSelect' to 'sipPhoneSelectMap' and Extend from 'uint8' to 'uint32' to support more (i)Local(Downlink) & (ii)Uplink Phone Port Types.

ccmConn_t* findOrigCcmConn(uint8 portType, uint16 chId);
/*ccmAssociator_t* findCcmAssociatorByCallId(uint8 portType, uint16 chId);
ccmAssociator_t* findCcmAssociatorByLogicalId(uint8 portType, uint16 chId);
ccmAssociator_t* findCcmAssociatorByDstLogicalId(uint8 portType, uint16 chId);*/
ccmAssociator_t* findCcmAssociator(ccmAssociator_searchIdxType_et searchIdxTypes, uint16 searchIdxValuePtr);


int delete_ccmConn(uint8 portType, uint16 chId);
int delete_ccmAssociator(uint16 srcPhonePortType, uint16 callId);
int ccm_change2ZyPhone(ccmConn_t* ccmConn_p);
int recordLocalConfPeerLocalPhLogicalId(uint16 phLogicalId, dialDigitNum_t *dialDigitNum_p);
uint32 isVoIPInUsed(void);

/*add GetRegStatusByUplinkTypeSide by yushiuan , uplink type means sip or fxs ... ,etc  2013/02/07*/
int GetRegStatusByUplinkTypeSide(uint16 lineId);

#if ZYXEL_VOICE_DELAY_ONHOLD_ACTION
int delayOnholdActionTimerHandler(tm_id_t unused, void *arg);
#endif  //ZYXEL_VOICE_DELAY_ONHOLD_ACTION

//Amber.20181119: Add for re-structure callDecisionSip2Fxs()/notCallTransferCase.
uint32 getPhoneCbBitMapForIncomingCall(ccmAssociator_t* ccmAsso_p, uint8 phonePortType);
int alertIncomingCallToPhoneCB(ccmAssociator_t* ccmAsso_p, uint8 phonePortType, uint32 finalSelectPhoneBitmap);


#endif //__CALL_MGNT_INCLUDE__.
