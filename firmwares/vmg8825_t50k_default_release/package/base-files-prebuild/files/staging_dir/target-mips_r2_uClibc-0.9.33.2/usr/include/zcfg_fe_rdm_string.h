typedef struct multiObjInfo_s {
	uint32_t oid;
	objIndex_t objIid[1];
	struct json_object *setObj;
} multiObjInfo_t;

int zcfgFeObjNameToObjId(char *, objIndex_t *);
int zcfgTr181ObjNameOid(char *objName);
const char *zcfgFeTr181OidToName(zcfg_offset_t oid);
zcfgRet_t zcfgFeObjIdToName(zcfg_offset_t oid, objIndex_t *objIid, char *objName);
zcfgRet_t zcfgFeJsonObjGen(zcfg_offset_t, char *, uint32_t, struct json_object *, void *);
zcfgRet_t zcfgFeJsonObjParamSet(zcfg_offset_t, char *, uint32_t, struct json_object *, char *);
zcfgRet_t zcfgFeObjJsonGetNext(zcfg_offset_t, objIndex_t *, struct json_object **);
zcfgRet_t zcfgFeObjJsonGetNextWithoutUpdate(zcfg_offset_t , objIndex_t *, struct json_object **);
zcfgRet_t zcfgFeObjJsonGet(zcfg_offset_t, objIndex_t *, struct json_object **);
zcfgRet_t zcfgFeObjJsonGetWithoutUpdate(zcfg_offset_t, objIndex_t *, struct json_object **);
zcfgRet_t zcfgFeSubInObjJsonGetNext(zcfg_offset_t oid, objIndex_t *objIid, objIndex_t *insIid, struct json_object **value);
zcfgRet_t zcfgFeSubInObjJsonGetNextWithoutUpdate(zcfg_offset_t , objIndex_t *, objIndex_t *, struct json_object **);
zcfgRet_t zcfgFeObjJsonSet(zcfg_offset_t, objIndex_t *, struct json_object *, char *);
zcfgRet_t zcfgFeObjJsonSetWithoutApply(zcfg_offset_t, objIndex_t *, struct json_object *, char *);
zcfgRet_t zcfgFeObjJsonSetWithAdditions(zcfg_offset_t , objIndex_t *, struct json_object *, char *, uint32_t , struct json_object *);
zcfgRet_t zcfgFeMultiObjJsonRunValid(struct json_object *multiJobj, char *feedbackmsg);
zcfgRet_t zcfgFeMultiObjJsonSet(struct json_object *, char *);
zcfgRet_t zcfgFeObjJsonAdd(zcfg_offset_t, objIndex_t *, char *);
zcfgRet_t zcfgFeObjJsonDelayRdmDel(zcfg_offset_t , objIndex_t *, char *);
zcfgRet_t zcfgFeObjJsonDel(zcfg_offset_t, objIndex_t *, char *);
char* zcfgFeParamValGet(struct json_object *, char *);
json_object* zcfgFeJsonMultiObjAppend(zcfg_offset_t, objIndex_t *, json_object *, json_object *);
#if 1 /* non-blocking config apply, ZyXEL, John */
zcfgRet_t zcfgFeObjJsonBlockedSet(zcfg_offset_t oid, objIndex_t *objIid, struct json_object *jobj, char *fbkMsg);
zcfgRet_t zcfgFeObjJsonBlockedAdd(zcfg_offset_t oid, objIndex_t *objIid, char *feedbackMsg);
zcfgRet_t zcfgFeMultiObjJsonBlockedSet(struct json_object *multiJobj, char *feedbackMsg);
#endif
zcfgRet_t zcfgFeJsonMultiObjAddParam(struct json_object *, zcfg_offset_t , objIndex_t *, const char *, struct json_object *);
zcfgRet_t zcfgFeJsonMultiObjRetrieveParam(struct json_object *, zcfg_offset_t , objIndex_t *, const char *, struct json_object **);
zcfgRet_t zcfgFeJsonMultiObjRetrieve(struct json_object *multiJobj, zcfg_offset_t oid, objIndex_t *objIid, objIndex_t *rtdIid, struct json_object **rtdObj);
zcfgRet_t zcfgFeJsonMultiObjAddObjParam(struct json_object *, zcfg_offset_t , objIndex_t *, const char *, struct json_object *);
zcfgRet_t zcfgFeJsonMultiObjRetrieveObjParam(struct json_object *multiobj, zcfg_offset_t oid, objIndex_t *objIid, const char *parmName, struct json_object **paramObj);

zcfgRet_t zcfgFeWholeObjJsonGet(char *tr181path, struct json_object **);
zcfgRet_t zcfgFeWholeObjJsonSet(char *tr181path, struct json_object *, char *);
zcfgRet_t zcfgObjGetFromInputObj(zcfg_offset_t oid, objIndex_t* objIid, struct json_object **, struct json_object *jobj);
zcfgRet_t zcfgObjGetByNameFromInputObj(char *rdmObjName, objIndex_t* objIid, struct json_object **, struct json_object *jobj);

zcfgRet_t zcfgFeObjJsonQueryExist(zcfg_offset_t , objIndex_t *);


struct json_object *zcfgFeDebugCfgRetrieve(const char *, objIndex_t *);
zcfgRet_t zcfgFeDebugCfgObjInit(const char *);

#define zcfgFeJsonObjNew() json_object_new_object()
#define zcfgFeJsonObjFree(jobj) do{json_object_put(jobj); jobj = NULL;}while(0)
#define zcfgFeParamValForEach(obj, key) char *key; \
		for(struct lh_entry *entry = json_object_get_object(obj)->head; ({ if(entry) { key = (char*)entry->k;} ; entry; }); entry = entry->next )
#define zcfgNotifyListForEachObj(obj, key, paramList) char *key; char *paramList; \
	for(struct lh_entry *entry = json_object_get_object(obj)->head; ({ if(entry) { key = (char*)entry->k; paramList = (char *)json_object_get_string((struct json_object*)entry->v); } ; entry; }); entry = entry->next )
#define zcfgNotifyStrToJsonObj(listStr) json_tokener_parse(listStr)

#define zcfgFeJsonMultiObjSetBlock(multiobj) { if(multiobj) json_object_object_add(multiobj, "block", json_object_new_boolean(true)); }
#define zcfgFeJsonMultiObjSetDelayApply(multiobj) { if(multiobj) json_object_object_add(multiobj, "delayapply", json_object_new_boolean(true)); }
#define zcfgFeJsonMultiObjSetAddFaultObj(multiobj, object) { if(multiobj && object) json_object_object_add(multiobj, "faultobj", object); }
#define zcfgFeJsonMultiObjSetNonDelayApply(multiobj) { if(multiobj) json_object_object_add(multiobj, "nondelayapply", json_object_new_boolean(true)); }
