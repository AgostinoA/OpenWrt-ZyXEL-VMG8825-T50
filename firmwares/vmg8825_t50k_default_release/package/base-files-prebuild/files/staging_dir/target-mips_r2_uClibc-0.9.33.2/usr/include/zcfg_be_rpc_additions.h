
#ifndef _ZCFG_BE_RPC_ADDITIONS_H
#define _ZCFG_BE_RPC_ADDITIONS_H

struct json_object *zcfgBeRpcReqRetrieveInternalAttrParams(void *obj);

#ifdef ZCFG_RPC_REQUEST_ADDITIONS
bool zcfgBeRpcApplyAskAttrRunAdditionsOnly(struct json_object *);
bool zcfgBeRpcApplyAskAttrSetWithoutApply(struct json_object *);

struct json_object *zcfgBeRpcReqRetrieveRequestAttrs(void *obj);
struct json_object *zcfgBeRpcReqRetrieveEvents(void *obj);
struct json_object *zcfgBeRpcReqRetrieveMethods(void *obj);
struct json_object *zcfgBeRpcReqRetrieveRpcAdditionsReply(void *obj);
struct json_object *zcfgBeRpcReqRetrieveReplyAttrs(void *obj);

int zcfgBeRpcReqQuerySpecificRequestAttr(struct json_object *, const char *);
int zcfgBeRpcReqQuerySpecificReplyAttr(struct json_object *, const char *);
bool zcfgBeRpcAdditionsAskMethod(struct json_object *, const char *, struct json_object **);
zcfgRet_t zcfgBeRpcReqAddMethodReplyRst(struct json_object *, struct json_object *, const char *, zcfgRet_t );
zcfgRet_t zcfgBeRpcReqAddMethodReply(struct json_object *, struct json_object *, const char *, const char *, struct json_object *);

#else

#define zcfgBeRpcApplyAskAttrRunAdditionsOnly(_obj) false
#define zcfgBeRpcApplyAskAttrSetWithoutApply(_obj) false

#define zcfgBeRpcReqRetrieveRequestAttrs(_obj) NULL
#define zcfgBeRpcReqRetrieveMethods(_obj) NULL
#define zcfgBeRpcReqRetrieveRpcAdditionsReply(_obj) NULL
#define zcfgBeRpcReqRetrieveReplyAttrs(_obj) NULL

#define zcfgBeRpcReqQuerySpecificRequestAttr(_rpcRequestAttrs, _attrName) 0
#define zcfgBeRpcReqQuerySpecificReplyAttr(_rpcReplyAttrs, _attrName) 0
#define zcfgBeRpcAdditionsAskMethod(_rpcAdditionMethods, _methodName, _methodParamsObj) false
#define zcfgBeRpcReqAddMethodReplyRst(_rpcReplyAttrs, _rpcAdditionsReply, _methodName, _rst) ZCFG_SUCCESS
#define zcfgBeRpcReqAddMethodReply(_rpcReplyAttrs, _rpcAdditionsReply, _methodName, _parmNameReply, _value) json_object_put(_value)
#endif

#endif
