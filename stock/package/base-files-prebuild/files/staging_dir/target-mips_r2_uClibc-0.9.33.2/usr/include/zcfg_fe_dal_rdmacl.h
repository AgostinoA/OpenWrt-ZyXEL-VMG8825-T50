#ifndef _ZCFG_FE_DAL_RDMACL_H
#define _ZCFG_FE_DAL_RDMACL_H

//
// on white list,
//  iid null implies no restriction on iid
//  params not null means it would reply only these listed
typedef struct rdmObjectACL_s {
	zcfg_offset_t oid;
	int method;
	const char **iid;
	const char **params;
}rdmObjectACL_t;

typedef zcfgRet_t (*queryRdmObjRout)(zcfg_offset_t objOid, objIndex_t *objIid, struct json_object **response);
typedef zcfgRet_t (*queryRdmSubObjRout)(zcfg_offset_t objOid, objIndex_t *objIid, objIndex_t *childIid, struct json_object **response);

zcfgRet_t zcfgFeDalQueryRdmObjHandler(zcfg_offset_t oid, const char *method, struct json_object *Jobj, struct json_object *Jarray, char *replyMsg);

#endif
