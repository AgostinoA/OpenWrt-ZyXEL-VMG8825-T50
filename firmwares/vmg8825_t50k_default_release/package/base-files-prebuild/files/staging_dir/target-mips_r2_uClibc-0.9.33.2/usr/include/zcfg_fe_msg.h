#ifndef _ZCFG_FE_MSG_H
#define _ZCFG_FE_MSG_H

#include <json/json.h>

#include <json/json_object.h>

#include "zcfg_common.h"
#include "zcmd_schema.h"
#include "zcfg_msg.h"
#include "zcfg_debug.h"
#include "zcfg_fe_schema.h"

#define UNITSIZE   4

typedef struct zcfgFeSetParmAttr_s zcfgFeSetParmAttr_t;
struct zcfgFeSetParmAttr_s {
	zcfgParmSetAttr_t parmSetAttr;
	char parmName[MAX_PARMNAME_LEN];
	char setAttrParmName[MAX_PARMNAME_LEN];
	zcfgFeSetParmAttr_t *next;
};

typedef struct {
	uint16_t n;
	uint16_t parmSetAttrDataLen;
	zcfgFeSetParmAttr_t *start;
} zcfgFeSetParmAttrLst_t;

#define zcfgSetParmAttrLstInit(setParmAttrLst) { \
		setParmAttrLst = (zcfgFeSetParmAttrLst_t *)malloc(sizeof(zcfgFeSetParmAttrLst_t)); \
		memset(setParmAttrLst, 0, sizeof(zcfgFeSetParmAttrLst_t)); }
#define zcfgSetParmAttrAdd(setParmAttrLst, setParmAttr) {setParmAttr->next = setParmAttrLst->start; setParmAttrLst->start = setParmAttr; setParmAttrLst->n++; \
											setParmAttrLst->parmSetAttrDataLen += sizeof(zcfgParmSetAttr_t) + setParmAttr->parmSetAttr.parmNameLen + setParmAttr->parmSetAttr.setAttrParmNameLen; }
#define zcfgSetParmAttrLstFree(setParmAttrLst) \
	{zcfgFeSetParmAttr_t *setParmAttr = (setParmAttrLst) ? setParmAttrLst->start : NULL; \
	 while(setParmAttr) { setParmAttrLst->start = setParmAttr->next; free(setParmAttr); setParmAttr = setParmAttrLst->start; } \
     if(setParmAttrLst) free(setParmAttrLst); }

#define zcfgFeParmUpdateMsgSend() zcfgFeReqSend(ZCFG_MSG_UPDATE_PARAMETER_NOTIFY, NULL)
#define zcfgFeHostsUpdateMsgSend() zcfgFeReqSend(ZCFG_MSG_HOSTS, NULL)

#define zcfgFe98To181ObjMappingGet(seqnum, tr98ObjIid, oid, objIid)  zcfgObjMappingGet(ZCFG_MSG_REQUEST_TR98_OBJMAPPING, seqnum, tr98ObjIid, oid, objIid)
#define zcfgFe181To98ObjMappingGet(oid, objIid, seqnum, tr98ObjIid)  zcfgObjMappingGet(ZCFG_MSG_REQUEST_TR181_OBJMAPPING, oid, objIid, seqnum, tr98ObjIid)

zcfgRet_t zcfg98To181ObjMappingAdd(zcfg_name_t seqnum, objIndex_t *tr98ObjIid, zcfg_offset_t oid, objIndex_t *objIid);
zcfgRet_t zcfgObjMappingGet(uint32_t msgType, uint32_t num_1, objIndex_t *objIdxData_1, uint32_t *num_2, objIndex_t *objIdxData_2);
zcfgRet_t zcfgFeMultiParmAttrSet(zcfgFeSetParmAttrLst_t *setParmAttrLst);
zcfgRet_t zcfgFeTr98ObjValueQry(zcfg_name_t seqnum, objIndex_t *tr98ObjIid, const char *parmName, struct json_object **valueObj, int);
zcfgRet_t zcfgFeParmAttrQry(zcfg_name_t seqnum, objIndex_t *tr98ObjIid, const char *parmName, zcfg_offset_t *oid, objIndex_t *objIid, char *queriedParmName, uint32_t *attr);
zcfgRet_t zcfgFeMsgObjQryInstances(uint32_t type, zcfg_name_t nameSeqNum, objIndex_t *queryObjIid, char **instances);
zcfgRet_t zcfgFeTr181ParmAttrQry(zcfg_offset_t , objIndex_t *, char *, zcfg_name_t *, objIndex_t *, const char *, uint32_t *);
zcfgRet_t zcfgFeObjParamAttrQry(uint32_t , objIndex_t *, struct json_object **, uint32_t );
#endif
