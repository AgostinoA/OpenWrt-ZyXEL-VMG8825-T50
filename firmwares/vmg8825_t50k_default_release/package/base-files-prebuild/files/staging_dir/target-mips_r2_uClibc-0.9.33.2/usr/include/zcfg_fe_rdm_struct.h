#ifndef _LIBZCFG_FE_RDM_STRUCT_H
#define _LIBZCFG_FE_RDM_STRUCT_H

zcfgRet_t zcfgFeObjStructGetNext(zcfg_offset_t, objIndex_t *, void **);
zcfgRet_t zcfgFeObjStructGetNextWithoutUpdate(zcfg_offset_t , objIndex_t *, void **);
zcfgRet_t zcfgFeObjStructGet(zcfg_offset_t, objIndex_t *, void **);
zcfgRet_t zcfgFeObjStructGetWithoutUpdate(zcfg_offset_t, objIndex_t *, void **);
zcfgRet_t zcfgFeSubInStructGetNext(zcfg_offset_t, objIndex_t *, objIndex_t *, void **);
zcfgRet_t zcfgFeSubInStructGetNextWithoutUpdate(zcfg_offset_t, objIndex_t *, objIndex_t *, void **);
zcfgRet_t zcfgFeObjStructSet(zcfg_offset_t, objIndex_t *, void *, char *);
zcfgRet_t zcfgFeObjStructSetWithoutApply(zcfg_offset_t, objIndex_t *, void *, char *);
zcfgRet_t zcfgFeObjStructAdd(zcfg_offset_t, objIndex_t *, char *);
zcfgRet_t zcfgFeObjStructDel(zcfg_offset_t, objIndex_t *, char *);
#if 1 /* non-blocking config apply, ZyXEL, John */
zcfgRet_t zcfgFeObjStructBlockedSet(zcfg_offset_t oid, objIndex_t *objIid, void *requestStruct, char *feedbackMsg);
zcfgRet_t zcfgFeObjStructBlockedAdd(zcfg_offset_t oid, objIndex_t *objIid, char *feedbackMsg);
zcfgRet_t zcfgFeObjStructBlockedDel(zcfg_offset_t oid, objIndex_t *objIid, char *feedbackMsg);
#endif

#define zcfgFeObjStructFree(obj) free(obj); obj = NULL

#endif
