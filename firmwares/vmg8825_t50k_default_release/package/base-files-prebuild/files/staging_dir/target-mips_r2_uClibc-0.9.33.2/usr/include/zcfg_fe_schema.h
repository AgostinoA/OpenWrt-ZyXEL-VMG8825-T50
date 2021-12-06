#ifndef _ZCFG_FE_SCHEMA_H
#define _ZCFG_FE_SCHEMA_H

typedef struct zcfgSubObjNameList_s{
	char *objName;
	struct zcfgSubObjNameList_s *next;
}zcfgSubObjNameList_t;

int zcfgFeObjIsSingle(zcfg_offset_t);
int zcfgFeObjAttrGet(zcfg_offset_t);
int zcfgFeObjQueryMaxInstance(zcfg_offset_t rdmObjId);
int zcfgFeParamAttrGetByName(zcfg_offset_t, char *);
int zcfgFeParamTypeGetByName(zcfg_offset_t, char *);
zcfgRet_t zcfgFeGetSchemaParameterByOid(uint32_t oid, struct json_object* defaultJobj);
zcfgRet_t zcfgFeAllParamNameGet(zcfg_offset_t, struct json_object **);
zcfgRet_t zcfgFeParamAttrSet(zcfg_offset_t, char *, uint32_t);
zcfgRet_t zcfgFeMultiParamAttrAppend(zcfg_offset_t, json_object *, char *, int);
zcfgRet_t zcfgFeMultiAttrSet(struct json_object *);
zcfgSubObjNameList_t* zcfgFeSubObjNameListGet(zcfg_offset_t rdmObjId);
void zcfgFeSubObjListFree(zcfgSubObjNameList_t *);

zcfgRet_t zcfgFeObjParamInfoQuery(zcfg_offset_t, struct json_object **);

#define zcfgFeParamNameForEach(obj, paramName) char *paramName; \
	for(struct lh_entry *entry = (obj ? json_object_get_object(obj)->head : NULL); ({ if(entry) { paramName = (char*)entry->k; } ; entry; }); entry = entry->next )
#define zcfgFeNotifyAttrValSet(attr, value) (attr & (~PARAMETER_ATTR_NOTIFY_MASK)) | value

#endif
