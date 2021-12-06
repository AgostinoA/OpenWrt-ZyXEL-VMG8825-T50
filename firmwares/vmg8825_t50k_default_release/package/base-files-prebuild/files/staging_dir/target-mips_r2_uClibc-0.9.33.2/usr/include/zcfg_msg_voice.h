#ifndef _ZCFG_MSG_VOICE_H
#define _ZCFG_MSG_VOICE_H
#include "zcfg_common.h"
#include "zcfg_rdm_obj.h"

#define ZCFG_MSG_VOICE_REPLY_WAIT_TIMEOUT 2000 //ms
#define VOICE_SIP_ACCT_MAX	16 //Michael.20140625.001: Add.
#define VOICE_SIP_PROF_MAX	2 //Michael.20170831.001: Add. This value SHOULD refer to the $(X-ZyIMS)/core/common/core/h/switch.h/ZYXEL_SIP_PROFILE_NUM_MAX (2).


//Michael.20140625.001.B: Add.
/************************/
/*** Voice Config Change ***/ //<==> ZCFG_MSG_VOICE_STATIC_CONFIG_CHANGED.
/************************/

//*** Voice Config Change REQuest ***

typedef struct voiceConfigReq_s {
//===== For bitFlag
#define VOICE_CONFIG_REQ_SIP_LINE_ACTIVATE  (1 << 0)
#define VOICE_CONFIG_REQ_SIP_TLS_CONFIG_CHANGE (1 << 1)
//=====
	uint16_t	bitFlag;




//====== For sipLineActivation
#define VOICE_CONFIG_REQ_SIP_ACCT_MAX   VOICE_SIP_ACCT_MAX
#define VOICE_CONFIG_REQ_SIP_LINE_ACTIVATE_NO_ACTION    0
#define VOICE_CONFIG_REQ_SIP_LINE_ACTIVATE_ENABLE       1
#define VOICE_CONFIG_REQ_SIP_LINE_ACTIVATE_DISABLE      2
#define VOICE_CONFIG_REQ_SIP_LINE_ACTIVATE_MASK         0x03
#define VOICE_CONFIG_REQ_SIP_LINE_ACTIVATE_SHIFT_UNIT   2
//======
	uint32_t	sipLineActivation; //bitmap: every successive 2bit (from the LSB) as a set, which can represent 3 action states (Reset/Idle/NoAction, Enable, Disable), is corresponding to one SIP account/line. This can handle 16 SIP accounts/lines - SIP-00 ~ SIP-15.
} voiceConfigReq_t;
//Michael.20140625.001.E: Add.


/*************************************/
/*** Voice Config Change Partial Reload  ***/ //<==> ZCFG_MSG_VOICE_CONFIG_CHANGED_PARTIAL_RELOAD.
/*************************************/
#define VOICE_CONFIG_CHANGED_PARTIAL_RELOAD_PARA_MAX 3

//*** Voice config change partial load types ***
#define VOICE_CONFIG_CHANGED_PARTIAL_RELOAD_TYPE_DECT (1 << 0)

//*** Voice config change partial load flag for DECT ***
#define DECT_PARTIAL_RELOAD_FLAG_BS_FUNCTION_ENABLE 		(1 << 0)
#define DECT_PARTIAL_RELOAD_FLAG_BS_NAME					(1 << 1)
#define DECT_PARTIAL_RELOAD_FLAG_BS_PIN_CODE				(1 << 2)
#define DECT_PARTIAL_RELOAD_FLAG_BS_ENCRYPTION_ENABLE		(1 << 3)
#define DECT_PARTIAL_RELOAD_FLAG_BS_NEMO_ENABLE			(1 << 4)
#define DECT_PARTIAL_RELOAD_FLAG_BS_ECO_MODE_ENABLE		(1 << 5)
#define DECT_PARTIAL_RELOAD_FLAG_BS_RF_STRENGTH			(1 << 6)
#define DECT_PARTIAL_RELOAD_FLAG_BS_REGISTRATION_DURATION	(1 << 7)
#define DECT_PARTIAL_RELOAD_FLAG_BS_PAGING_DURATION		(1 << 8)
//------
#define DECT_PARTIAL_RELOAD_FLAG_HS_NAME					(1 << 9)
#define DECT_PARTIAL_RELOAD_FLAG_HS_INTERNAL_PHONE_NUM	(1 << 10)
#define DECT_PARTIAL_RELOAD_FLAG_HS_LINE_SELECT				(1 << 11)



/***********************/
/*** Voice Stats Update  ***/ //<==> ZCFG_MSG_VOICE_STATS_GET.
/***********************/

//*** Voice Stats Update REQuest ***
#define VOICE_STATS_REQ_REGISTRATION_STATUS	(1 << 0)
#define VOICE_STATS_REQ_MWI_STATUS			(1 << 1)
#define VOICE_STATS_REQ_CALL_STATE			(1 << 2)
#define VOICE_STATS_REQ_PHONE_HOOK_STATUS	(1 << 3)
#define VOICE_STATS_REQ_VOIP_INUSE			(1 << 4)
#define VOICE_STATS_REQ_ONGOING_CALL_CNT	(1 << 5)
#define VOICE_STATS_REQ_VOICE_LINE_STATS	(1 << 6)
#define VOICE_STATS_REQ_SIP_LINE_CALL_STATE	(1 << 7) //Amber.20170901: Add for support SIP Line CallState info Retrieve via TR069
#define VOICE_STATS_REQ_SIP_ACCT_MAX VOICE_SIP_ACCT_MAX
//======
typedef struct voiceStatsReq_s {
    uint16_t    bitFlag;

    uint16_t    registerStatus; //bitmap: each bit (from the LSB) is corresponding to one SIP account/line. Markup dedicated bit to indicate requesting its corresponding SIP account/line's SIP Registration Status. This is designed to support 16 SIP accounts/lines - SIP-00 ~ SIP-15.
    uint16_t    mwiStatus; //bitmap: each bit (from the LSB) is corresponding to one SIP account/line. Markup dedicated bit to indicate requesting its corresponding SIP account/line's MWI Status. This is designed to support 16 SIP accounts/lines - SIP-00 ~ SIP-15.
    //uint16_t	callState; //bitmap: each bit (from the LSB) is corresponding to one Call. Markup dedicated bit to indicate requesting its corresponding Call's Operation State. This is designed to support 10 Concurrent Calls - SIP-00 ~ SIP-09.
    uint8_t     fxsHookState; //bitmap: each bit (from the LSB) is corresponding to one FXS phone port. Markup dedicated bit to indicate requesting its corresponding FXS phone port's Hood State. This is designed to support 8 FXS phone ports - FXS-00 ~ FXS-07.

    uint16_t    sipLineStats; //SIP Acct Id (NOTE: NOT a bitmap), which you expect to request its corresponding (All) Call(s') Statistics Data (Stats) Info. This is designed to support ONLY One Single SIP accounts/lines.
    uint16_t    sipLineCallState; //SIP Acct Id (NOTE: NOT a bitmap), which you expect to request its (All) corresponding Call(s') Operation State Info. This is designed to support ONLY One Single SIP accounts/lines.

} voiceStatsReq_t;


//*** Voice Stats Update ReSPonse ***
#define VOICE_STATS_RSP_REGISTRATION_STATUS_SET1	(1 << 0)
#define VOICE_STATS_RSP_REGISTRATION_STATUS_SET2	(1 << 1)
#define VOICE_STATS_RSP_MWI_STATUS					(1 << 2)
#define VOICE_STATS_RSP_CALL_STATE					(1 << 3)
#define VOICE_STATS_RSP_PHONE_HOOK_STATUS			(1 << 4)
#define VOICE_STATS_RSP_VOIP_INUSE					(1 << 5)
#define VOICE_STATS_RSP_ONGOING_CALL_CNT			(1 << 6)
#define VOICE_STATS_RSP_VOICE_LINE_STATS			(1 << 7)
#define VOICE_STATS_RSP_SIP_LINE_CALL_STATE			(1 << 8) //Amber.20170901: Add for support SIP Line CallState info Retrieve via TR069
//======
#define VOICE_STATS_RSP_REGISTRATION_STATUS_SET_SIZE	8
#define VOICE_STATS_RSP_REGISTRATION_STATUS_MASK		0x0f
#define VOICE_STATS_RSP_REGISTRATION_STATUS_SHIFT_UNIT	4
#define VOICE_STATS_RSP_CALL_STATE_MASK			0x07
#define VOICE_STATS_RSP_CALL_STATE_SHIFT_UNIT	3
//======
typedef struct voiceStatsRsp_s {
	uint16_t bitFlag;
	uint16_t errorBitFlag;       //2015-02-13 Steve Add. Use RSP bit to indicate error. if all success will be 0

	//Michael.20170831.001.B: Add to Extend the VoIP Stats info-related Data Structure to support VoIP CLI for SIP Registration and MWI Status info Display/Dump.
	uint8_t sipProfCnt;
	uint8_t sipProfLineCnt[VOICE_SIP_PROF_MAX];
	uint8_t sipAcctCnt;
	//Michael.20170831.001.E: Add.

	//NOTE: the following definitions SHOULD sync with those corresponding global variables in the 'vcm.c' of the ZyIMS VoIP's config system.
	uint32_t registerStatusSet1; //bitmap: every successive 4bit (from the LSB) as a set, which can represent 10 statuses, is corresponding to one SIP account/line. This set can handle 8 SIP accounts/lines - SIP-00 ~ SIP-08.
	uint32_t registerStatusSet2; //bitmap: every successive 4bit (from the LSB) as a set, which can represent 10 statuses, is corresponding to one SIP account/line. This set can handle 8 SIP accounts/lines - SIP-08 ~ SIP-15.
	//------
	uint16_t mwiStatus; //bitmap: each bit (from the LSB), which represents NoMWI=0 & IsMWI=1, is corresponding to one SIP account/line. This can handle 16 SIP accounts/lines - SIP-00 ~ SIP-15.
	//------
	//Amber.20170901: Modify for support SIP Line CallState info Retrieve via TR069.
	//uint32_t callState; //bitmap: every successive 3bit (from the LSB) as a set, which can represent 8 states, is corresponding to one Call. This can handle 10 Concurrent Calls - Call-00 ~ Call-09.
	char callState[128+1]; //consider a worst case: 8(call)*("Disconnecting") = 8*(13+1) = 112.
	//------
	uint32_t  phoneHookState; //bitmap: each bit (from the LSB), which represents OnHooked=0 & OffHooked=1, is corresponding to one FXS phone port. This can handle 8 FXS phone ports - FXS-00 ~ FXS-07.
	//------
	//yushiuan add start , for to record the call status information, 2015/01/06
	//char status[64+1];
	char status[128+1]; //Amber.20170901: consider a worst case: 8(call)*("Disconnecting") = 8*(13+1) = 112.
	char callStartTime[128+1];
	char selfNumber[512+1];
	char peerNumber[512+1];
	char codec[64+1];	
	char fromPhonePortType[64+1];
	char toPhonePortType[64+1];
	char callType[128+1];
	//yushiuan add end , for to record the call status information, 2015/01/06
	
	uint32_t voipInUse; //2015-02-10 Steve add.
	//2015-02-13 Steve add.
	uint8_t ongoingSipCallCnt;
	uint8_t ongoingInternelCallCnt;
	//2015-02-13 Steve add. (END)

	//2015-12-09 Brady add
	rdm_VoiceLineStats_t LineStats;
} voiceStatsRsp_t;



/******************/
/*** Voice Control ***/ //<==> ZCFG_MSG_VOICE_CONTROL.
/******************/

//Michael.20131125.001.B: Add.
//*** Voice Control REQuest ***
#define VOICE_CONTROL_REQ_CONVENTIONAL_VOIP_CLI		(1 << 0)
//------
#define VOICE_CONTROL_REQ_SIP_REGISTER				(1 << 1)
//------
//Steve.2014-06-11 ADD
#define VOICE_CONTROL_REQ_GET_DEBUG_FLAG			(1 << 2)
#define VOICE_CONTROL_REQ_SET_DEBUG_FLAG			(1 << 3)
#define VOICE_CONTROL_REQ_SET_ICF_DEBUG_FLAG		(1 << 4)
#define VOICE_CONTROL_REQ_SET_MM_DEBUG_FLAG		(1 << 5)
//Steve.2014-11-20 Support Log Dest
#define VOICE_CONTROL_REQ_SET_DEBUG_DEST			(1 << 6)
//------
#if 1 //Michael.20150909.001.B: Add to support the CLI (framework): Tone, Ring, LED and VMWI signal control.
#define VOICE_CONTROL_REQ_PHONE_TONE					(1 << 7)
#define VOICE_CONTROL_REQ_PHONE_RING					(1 << 8)
#define VOICE_CONTROL_REQ_PHONE_LED					(1 << 9)
#define VOICE_CONTROL_REQ_PHONE_VMWI				(1 << 10)
#endif //Michael.20150909.001.E: Add.
#define VOICE_CONTROL_REQ_VOICE_LINE_STATS			(1 << 11)
//======
#define VOICE_CONTROL_REQ_SIP_REGISTER_SIP_ACCT_MAX	VOICE_SIP_ACCT_MAX //Michael.20140625.001: Modify from '16' to 'VOICE_SIP_ACCT_MAX'.
#define VOICE_CONTROL_REQ_SIP_REGISTER_NO_ACTION		0
#define VOICE_CONTROL_REQ_SIP_REGISTER_DO_REGISTER		1
#define VOICE_CONTROL_REQ_SIP_REGISTER_DO_DEREGISTER	2
#define VOICE_CONTROL_REQ_SIP_REGISTER_ACTION_MASK			0x03
#define VOICE_CONTROL_REQ_SIP_REGISTER_ACTION_SHIFT_UNIT	2
//------
//Steve.2014-06-11 ADD to define Debug Flag
#define VOICE_CONTROL_REQ_DEBUG_FLAG_MASK		0x03 //bitmap: every successive 2bit (from the LSB) as a set, which can represent 4 states, is corresponding to 4 debug levels (including the 'Disabled').
#define VOICE_CONTROL_REQ_DEBUG_FLAG_VOICEAPP	0
#define VOICE_CONTROL_REQ_DEBUG_FLAG_CCM		2
#define VOICE_CONTROL_REQ_DEBUG_FLAG_PHONE		4
#define VOICE_CONTROL_REQ_DEBUG_FLAG_SIP		6
#define VOICE_CONTROL_REQ_DEBUG_FLAG_TR104		8
//Steve.2014-09-04 Define MM & ICF Debug Flag
#define VOICE_CONTROL_REQ_MM_DEBUG_FLAG_RM		10 // TODO: SHOULD rename to 'VOICE_CONTROL_REQ_DEBUG_FLAG_MM_RM'!
#define VOICE_CONTROL_REQ_MM_DEBUG_FLAG_RTP	12 // TODO: SHOULD rename to 'VOICE_CONTROL_REQ_DEBUG_FLAG_MM_RTP'!
#define VOICE_CONTROL_REQ_MM_DEBUG_FLAG_DSP	14 // TODO: SHOULD rename to 'VOICE_CONTROL_REQ_DEBUG_FLAG_MM_DSP'!
#define VOICE_CONTROL_REQ_ICF_DEBUG_FLAG		16 // TODO: SHOULD rename to 'VOICE_CONTROL_REQ_DEBUG_FLAG_ICF'!
//Steve.2014-11-20 Support Log Dest
#define VOICE_CONTROL_REQ_DEBUG_FLAG_DEST		18 //Correct from 17 to 18!
//------
#if 1 //Michael.20150909.001.B: Add to support the CLI (framework): Tone, Ring, LED and VMWI signal control.
//+------------+--------+----------+----------+
//| 15------11 | 10---8 | 7------4 | 3------0 |
//+------------+--------+----------+----------+
//:   ToneId   : Action :   Port   :   Port   :
//:   RingId   :        :   PhyId  :   Type   :
#define VOICE_CONTROL_REQ_PHONE_CTRL_DATA_MASK_3BIT		0x07 //0000-0111.
#define VOICE_CONTROL_REQ_PHONE_CTRL_DATA_MASK_4BIT		0x0F //0000-1111.
#define VOICE_CONTROL_REQ_PHONE_CTRL_DATA_MASK_5BIT		0x1F //0001-1111.
#define VOICE_CONTROL_REQ_PHONE_PORT_TYPE_SHIFT_UNIT		0
#define VOICE_CONTROL_REQ_PHONE_PORT_PHYID_SHIFT_UNIT		4
#define VOICE_CONTROL_REQ_PHONE_PORT_ACT_SHIFT_UNIT		8
#define VOICE_CONTROL_REQ_PHONE_TONERING_ID_SHIFT_UNIT	11 //Support Action Cnt: (0x07)=7, Tone/Ring Id Cnt: (0x1F)=31.
#define VOICE_CONTROL_REQ_PHONE_LED_ID_SHIFT_UNIT			12 //Support Action Cnt: (0x0F)=15, LED Id Cnt: (0x0F)=15. //Michael.20151213.001: Add.
//------
#define VOICE_CONTROL_REQ_PHONE_ACT_NONE			0x07
#define VOICE_CONTROL_REQ_PHONE_ACT_NONE2			0x0F //Michael.20151213.001: Add.
//------
#define VOICE_CONTROL_REQ_PHONE_TONERING_PLAY_OFF	0
#define VOICE_CONTROL_REQ_PHONE_TONERING_PLAY_ON	1
//------
#define VOICE_CONTROL_REQ_PHONE_VMWI_OFF	0
#define VOICE_CONTROL_REQ_PHONE_VMWI_ON		1
//------
#define VOICE_CONTROL_REQ_PHONE_LED_OFF				0
#define VOICE_CONTROL_REQ_PHONE_LED_ON				1
#define VOICE_CONTROL_REQ_PHONE_LED_BLINK			2 //Michael.20151213.001: Add.
#define VOICE_CONTROL_REQ_PHONE_LED_SLOW_BLINK		3
#define VOICE_CONTROL_REQ_PHONE_LED_FAST_BLINK		4
#define VOICE_CONTROL_REQ_PHONE_LED_FAIL				5
#define VOICE_CONTROL_REQ_PHONE_LED_AUTO			6 //Michael.20151213.001: Add.
#define VOICE_CONTROL_REQ_PHONE_LED_STATUS_DISP	7 //Michael.20151213.001: Add.
#endif //Michael.20150909.001.E: Add.
//Michael.20150909.001.E: Add.
//======
#ifdef ZYXEL_ZYIMS_CMD_TEST //__ZYXEL__, Mark
typedef enum{
	VOICE_CLI_ZYIMSCMD
}voiceCliType;
#endif //ZYXEL_ZYIMS_CMD_TEST.
//------
typedef struct voiceCtrlReq_s {
	uint32_t	bitFlag;

	//NOTE: No fixed (string-type) parameter for the conventional VoIP CLI command string is defined here, because it will be appended at the end of the structure as a payload.
	uint32_t	sipRegisterAct; //bitmap: every successive 2bit (from the LSB) as a set, which can represent 4 statuses, is corresponding to one SIP account/line's register action. Markup dedicated set to indicate requesting its corresponding SIP account/line's SIP regiter action. This is designed to support 16 SIP accounts/lines - SIP-00 ~ SIP-15.
	//------
	uint32_t	DebugFlag; //Steve.2014-06-11-1013
	uint32_t	DataValue; //Pass the data value to CLI "get" command 2014-06-11 Steve.
	//------
	//Michael.20150909.001.B: Add to support the CLI (framework): Tone, Ring, LED and VMWI signal control.
	//+------------+--------+----------+----------+
	//| 15------11 | 10---8 | 7------4 | 3------0 |
	//+------------+--------+----------+----------+
	//:   ToneId   : Action :   Port   :   Port   :
	//:   RingId   :        :   PhyId  :   Type   :
#define MAX_CLID_NUMBER 40
	uint32_t	phoneToneCtrl;
	char callerId_number_callWait[MAX_CLID_NUMBER+1];

	uint32_t	phoneRingCtrl;
	char callerId_number_ring[MAX_CLID_NUMBER+1];

	uint32_t	phoneLedCtrl;
	uint32_t	phoneVmwiCtrl;
	//Michael.20150909.001.E: Add.

	//------
#ifdef ZYXEL_ZYIMS_CMD_TEST //__ZYXEL__, Mark
	voiceCliType cliType;
	char cmdLine[200];
#endif //ZYXEL_ZYIMS_CMD_TEST.

    uint16_t    sipLineStats; //SIP Acct Id (NOTE: NOT a bitmap), which you expect to request its corresponding (All) Call(s') Statistics Data (Stats) Info. This is designed to support ONLY One Single SIP accounts/lines.

	bool resetLineStats;
} voiceCtrlReq_t;


//*** Voice Control ReSPonse ***
#define VOICE_CONTROL_RSP_CONVENTIONAL_VOIP_CLI		(1 << 0)
//------
#define VOICE_CONTROL_RSP_SIP_REGISTER				(1 << 1)
//------
//Steve.2014-06-11 ADD
#define VOICE_CONTROL_RSP_GET_DEBUG_FLAG			(1 << 2)
#define VOICE_CONTROL_RSP_SET_DEBUG_FLAG			(1 << 3)
#define VOICE_CONTROL_RSP_SET_ICF_DEBUG_FLAG		(1 << 4)
#define VOICE_CONTROL_RSP_SET_MM_DEBUG_FLAG		(1 << 5)
//Steve.2014-11-20 Support Log Dest
#define VOICE_CONTROL_RSP_SET_DEBUG_DEST			(1 << 6)
//------
#if 1 //Michael.20150909.001.B: Add to support the CLI (framework): Tone, Ring, LED and VMWI signal control.
#define VOICE_CONTROL_RSP_PHONE_TONE					(1 << 7)
#define VOICE_CONTROL_RSP_PHONE_RING					(1 << 8)
#define VOICE_CONTROL_RSP_PHONE_LED					(1 << 9)
#define VOICE_CONTROL_RSP_PHONE_VMWI				(1 << 10)
#endif //Michael.20150909.001.E: Add.
//======
#define VOICE_CONTROL_RSP_ACT_SUCCESS	0
#define VOICE_CONTROL_RSP_ACT_FAIL		1
//======
typedef struct voiceCtrlRsp_s {
	uint32_t	bitFlag;

	//NOTE: No fixed (string-type) parameter for the conventional VoIP CLI result string is defined here, because it will be appended at the end of the structure as a payload.
	//------
	uint16_t	sipRegisterActResult; //bitmap: each bit (from the LSB), which represents ActionSuccess=0 & ActionFail=1, is corresponding to one SIP account/line's register action result.
	//------
	uint32_t	DataValue; //Pass the data value to CLI "get" command 2014-06-11 Steve.
	//------
	//Michael.20150909.001.B: Add to support the CLI (framework): Tone, Ring, LED and VMWI signal control.
	uint8_t	phoneToneCtrlResult;
	uint8_t	phoneRingCtrlResult;
	uint8_t	phoneLedCtrlResult;
	uint8_t	phoneVmwiCtrlResult;
	//Michael.20150909.001.E: Add.
} voiceCtrlRsp_t;
//Michael.20131125.001.B: Add.



/**************Voice List Access Msg*******************/
//Types
#define VOICE_LIST_ACCESS_REQ_CALLHISTORY_GET		(1 << 0)
#define VOICE_LIST_ACCESS_REQ_CALLHISTORY_PUT		(1 << 1)
#define VOICE_LIST_ACCESS_REQ_CALLHISTORY_CLEAR		(1 << 2)
#define VOICE_LIST_ACCESS_REQ_CALLHISTORY_BACKUP	(1 << 3)
#define VOICE_LIST_ACCESS_REQ_CALLHISTORY_RESTORE	(1 << 4)
#define VOICE_LIST_ACCESS_REQ_PHONEBOOK_GET			(1 << 5)
#define VOICE_LIST_ACCESS_REQ_PHONEBOOK_PUT			(1 << 6)
#define VOICE_LIST_ACCESS_REQ_PHONEBOOK_CLEAR		(1 << 7)
#define VOICE_LIST_ACCESS_REQ_PHONEBOOK_BACKUP		(1 << 8)
#define VOICE_LIST_ACCESS_REQ_PHONEBOOK_RESTORE	(1 << 9)
//======
typedef struct voiceListAccessReq_s{
	uint16_t Type;
	char *Payload; //Request Data From GUI, Only PUT Method
}voiceListAccessReq_t;
//------
typedef struct voiceListAccessRsp_s{
	char *Payload;
}voiceListAccessRsp_t;
//Steve.2014-09-23



/*********************CAP Get***********************/
#define VOICE_CAP_GET_REGION                         (1 << 0)
#define VOICE_CAP_GET_CODEC                          (1 << 1)

typedef struct voiceCapGetReq_s{
	uint16_t Type;
}voiceCapGetReq_t;
typedef struct voiceCapGetResp_s{
	char *Payload;
}voiceCapGetResp_t;
//Steve.2015-09-17


#endif //_ZCFG_MSG_VOICE_H
