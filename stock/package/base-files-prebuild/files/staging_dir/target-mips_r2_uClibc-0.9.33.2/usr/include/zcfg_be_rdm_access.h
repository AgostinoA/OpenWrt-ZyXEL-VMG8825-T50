#ifndef _ZCFG_BE_RDM_ACCESS_H
#define _ZCFG_BE_RDM_ACCESS_H

#define ZCMD_SET_NORMAL		0
#define ZCMD_SET_WITHOUT_APPLY		1
#define ZCMD_GET_NORMAL		1 << 1
#define ZCMD_GET_WITHOUT_UPDATE	1 << 2
#define ZCMD_ADD_NORMAL		1 << 3
#define ZCMD_ADD_WITHOUT_APPLY		1 << 4
#define ZCMD_PARTIAL_SET		1 << 5

#define ZCMD_QUERY_OBJ_EXIST		1 << 6

#define ZCMD_RPC_REQUEST_ADDITIONS	1 << 8

#define ZCMD_UTILIZE_DISTINCT_VALUE	1 << 11
#define ZCMD_RE_APPLY			1 << 12

zcfgRet_t zcfgBeObjGetNext(zcfg_offset_t, objIndex_t *, void **);
zcfgRet_t zcfgBeObjGetNextWithoutUpdate(zcfg_offset_t, objIndex_t *, void **);
zcfgRet_t zcfgBeObjGet(zcfg_offset_t, objIndex_t *, void **);
zcfgRet_t zcfgBeObjQueryExist(zcfg_offset_t , objIndex_t *);
zcfgRet_t zcfgBeObjGetWithoutUpdate(zcfg_offset_t, objIndex_t *, void **);
zcfgRet_t zcfgBeObjSetWithoutApply(zcfg_offset_t, objIndex_t *, void *, char *);
zcfgRet_t zcfgBeObjSet(zcfg_offset_t, objIndex_t *, void *, char *);
zcfgRet_t zcfgBeObjAdd(zcfg_offset_t, objIndex_t *);
zcfgRet_t zcfgBeObjAddWithoutApply(zcfg_offset_t, objIndex_t *);
zcfgRet_t zcfgBeObjDel(zcfg_offset_t, objIndex_t *, char *);
zcfgRet_t zcfgBeGetNextInSub(zcfg_offset_t , objIndex_t *, objIndex_t *, void **);
zcfgRet_t zcfgBeGetNextInSubWithoutUpdate(zcfg_offset_t, objIndex_t *, objIndex_t *, void **);
zcfgRet_t zcfgBeReqMsgSend(int, int, zcfg_offset_t, objIndex_t *, int, char *);
zcfgRet_t zcfgBeSaveParamValue(zcfg_offset_t, objIndex_t *, char *, void *);
zcfgRet_t zcfgBeObjIdToName(zcfg_offset_t , objIndex_t *, char *);
zcfgRet_t zcfgBeNameToObjId(const char *, objIndex_t *);
zcfgRet_t zcfgBeLowerLayerStatusGet(char *, char *);
#ifdef ZCFG_TR98_TR181_OBJECT_MAPPING_REBUILD
void zcfgBeReqMappingTableRebuild();
#else
#define zcfgBeReqMappingTableRebuild() {}
#endif


zcfgRet_t zcfgBeRdmReqGet(zcfg_offset_t rdmObjId, objIndex_t *objIid, char **jstr, uint8_t op);
zcfgRet_t zcfgBeRdmReqGetNext(zcfg_offset_t rdmObjId, objIndex_t *objIid, char **jstr, uint8_t op);
zcfgRet_t zcfgBeRdmReqSet(zcfg_offset_t , objIndex_t *, void *, uint32_t , char *);
zcfgRet_t zcfgBeRdmReqSetWitoutApply(zcfg_offset_t , objIndex_t *, void *, uint32_t , char *);

zcfgRet_t zcfgBeRdmModuleSet(zcfg_offset_t , objIndex_t *, struct json_object *, uint32_t );
void zcfgBeCheckWifiDiagRunning(uint32_t , int);

zcfgRet_t zcfgBeLanAppySyncDhcp4Server();
zcfgRet_t zcfgBeApplySyncBrSetMacAddrLearning();


struct json_object *zcfgBeApplyObjRetrievePartialObj(void *obj);

zcfgRet_t zcfgBeClearAllTr98WANConnectNumParam(const char *wanConnectNumParam);
zcfgRet_t zcfgBeSyncTr98WANConnectNum(uint32_t oid, objIndex_t *objIid, const char *wanConnectNumParam, struct json_object **replyNotifyObj, int num);
zcfgRet_t zcfgBeNotifyMsgSend(struct json_object *notify);

void zcfgBeCreateConfigSymLink(char *);
void zcfgBeRemoveConfigSymLink(char *);

zcfgRet_t zcfgBeJobjSet(zcfg_offset_t rdmObjId, objIndex_t *objIid, struct json_object *jobj, uint32_t op, char *fbkMsg);

#define zcfgBeObjFree(obj) free(obj); obj = NULL
#endif
