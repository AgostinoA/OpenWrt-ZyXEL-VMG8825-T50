#ifndef _ZCFG_MSG_DECT_H
#define _ZCFG_MSG_DECT_H
#include "zcfg_common.h"

#define ZCFG_MSG_DECT_REPLY_WAIT_TIMEOUT 2000 //ms


/*************************/
/*** DECT Stats Update ***/
/*************************/

//*** DECT Stats Update REQuest ***
#define DECT_STATS_REQ_HANDSET_REGISTRATION_STATUS	(1 << 0)
#define DECT_STATS_REQ_BASESTATION_BASESTATUS		(1 << 0)

/*typedef struct dectStatsReq_s{
	uint16_t bitFlag;

	uint16_t registerStatus; //bitmap: each bit (from the LSB) is corresponding to one DECT handset. Markup dedicated bit to indicate requesting its corresponding DECT handset's Registration Status. This is designed to support 16 DECT handsets.


} dectStatsReq_t;*/

//Split dectStatsReq_s to dectBS_StatsReq_s and dectHS_StatsReq_s , yushiuan modify ,2014/08/21

typedef struct dectBS_StatsReq_s{
	uint16_t bitFlag;

} dectBS_StatsReq_t;


typedef struct dectHS_StatsReq_s{
	uint16_t bitFlag;
	uint16_t registerStatus; //bitmap: each bit (from the LSB) is corresponding to one DECT handset. Markup dedicated bit to indicate requesting its corresponding DECT handset's Registration Status. This is designed to support 16 DECT handsets.

} dectHS_StatsReq_t;




//*** DECT Stats Update ReSPonse ***
#define DECT_STATS_RSP_HANDSET_REGISTRATION_STATUS	(1 << 0)
#define DECT_STATS_RSP_BASESTATION_BASESTATUS		(1 << 0)

/*typedef struct dectStatsRsp_s{
	uint16_t bitFlag;

	uint16_t registerStatus; //bitmap: each bit (from the LSB) is corresponding to one DECT handset. A bit=1 means the corresponding DECT handset is registered. A bit=0 means otherwise.
	uint32_t baseStatus;
	char FirmwareVersion[33];

} dectStatsRsp_t;*/

//Split dectStatsRsp_s to dectBS_StatsRsp_s and dectHS_StatsRsp_s , yushiuan modify ,2014/08/21

typedef struct dectBS_StatsRsp_s{
	uint16_t bitFlag;
	uint32_t baseStatus;
	char FirmwareVersion[33];

} dectBS_StatsRsp_t;


typedef struct dectHS_StatsRsp_s{
	uint16_t bitFlag;
	uint16_t registerStatus; //bitmap: each bit (from the LSB) is corresponding to one DECT handset. A bit=1 means the corresponding DECT handset is registered. A bit=0 means otherwise.
	
} dectHS_StatsRsp_t;



/******************/
/*** DECT Control ***/
/******************/
typedef enum dectCtrlCmdType_es
{
	DECT_CTRL_CMD_NONE=0,
	DECT_CTRL_CMD_BS,	//Base Station.
	DECT_CTRL_CMD_HS,	//Handset.
	DECT_CTRL_CMD_UNDEFINED
} dectCtrlCmdType_et;
//------
typedef enum dectBSCtrlCmdId_es
{
	DECT_BS_CTRL_NONE=0,
	DECT_BS_CTRL_RESET,	//Parameter: (none).
	DECT_BS_CTRL_REGISTER_MODE_ENABLE,	//Parameter: CmdPara[0]=ON(1)/OFF(0). CmdPara[1]=(none).
	DECT_BS_CTRL_DEREGISTER_HS,		//Parameter: CmdPara[0]=(none), CmdPara[1]=HS selection bitmap(uint16_t).
	DECT_BS_CTRL_PAGING_HS_ENABLE,	//Parameter: CmdPara[0]=ON(1)/OFF(0), CmdPara[1]=HS selection bitmap(uint16_t).
	DECT_BS_CTRL_FIRMWARE_UPGRADE,
	DECT_BS_CTRL_UNDEFINED
} dectBSCtrlCmdId_et;
//------
typedef enum dectHSCtrlCmdId_es
{
	DECT_HS_CTRL_NONE=0,
	DECT_HS_CTRL_UNDEFINED
} dectHSCtrlCmdId_et;
//------

//*** DECT Control REQuest ***
#define DECT_CTRL_CMD_PARA_MAX		2 //NOTE: This value MUST be >= 2 because there has been many quick access for CmdPara[] by CmdPara[0] & CmdPara[1]!!
#define DECT_CTRL_CMD_DO_ACTION_OFF	0
#define DECT_CTRL_CMD_DO_ACTION_ON	1
typedef struct dectCtrlReq_s {
	uint8_t	CmdType;	//dectCtrlCmdType_et.
	uint8_t	CmdId;		//dectBSCtrlCmdId_et or dectHSCtrlCmdId_et.
	uint32_t	CmdPara[DECT_CTRL_CMD_PARA_MAX];
} dectCtrlReq_t;


//*** DECT Control ReSPonse ***
#define DECT_CTRL_CMD_SUCCESS	0
#define DECT_CTRL_CMD_FAIL		1
typedef struct dectCtrlRsp_s {
	uint8_t	CmdType;	//dectCtrlCmdType_et.
	uint8_t	CmdId;		//dectBSCtrlCmdId_et or dectHSCtrlCmdId_et.
	uint8_t	CmdResult;	//Success(0), Fail(1).
} dectCtrlRsp_t;

#endif //_ZCFG_MSG_DECT_H
