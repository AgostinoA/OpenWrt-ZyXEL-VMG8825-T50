#ifndef _ZCFG_FE_TR98_H
#define _ZCFG_FE_TR98_H

#include <json/json.h>

#include <json/json_object.h>
#include "zcfg_common.h"
#include "zcfg_fe_rdm_access.h"
#include "zcmd_schema.h"
#include "zcfg_msg.h"
#include "zcfg_debug.h"
#include "zcfg_fe_schema.h"
#include "zcfg_tr98_common.h"
#include "zcfg_fe_msg.h"

#ifdef ZCFG_PARM_NAMEMAPPING
#define TR98_MAPPING_DEBUG 0
#endif

#define TR98_GET_UPDATE 0
#define TR98_GET_WITHOUT_UPDATE 1
#define NAME_SIZE 256

#define MAX_IP4STR_SIZE 16

#ifndef TR069ERR_E
#define TR069ERR_E
// need to sync to libzcfg_fe_tr98/zcfg_fe_tr98.h
typedef enum
{
	TR069_SOCK_CLOSE = -1,
	TR069_OK = 0,
	TR069_NOK = 1,    			/* common errors */
	TR069_SERVICE_TIME_OUT,
	TR069_BUFFER_OVERFLOW,
	TR069_DNS_ERR,
	TR069_INIT_FAILED,    	/* errors occurs in initialization */
	TR069_SET_NON_APPLY,	/*All Parameter changes have been validated and committed, but some or all are not yet applied*/
	/* RPC Fault Code*/
	TR069_METHOD_NOT_SUPPORTED = 9000,
	TR069_REQUEST_DENIED = 9001,
	TR069_INTERNAL_ERROR = 9002,
	TR069_INVALID_ARGUMENTS = 9003,
	TR069_RESOURCES_EXCEEDED = 9004,
	TR069_INVALID_PARAMETER_NAME = 9005,
	TR069_INVALID_PARAMETER_TYPE = 9006,
	TR069_INVALID_PARAMETER_VALUE = 9007,
	TR069_ATTEMPT_TO_SET_NONWRITABLE_PARAMETER = 9008,
	TR069_NOTIFICATION_REQUEST_REJECTED = 9009,
	TR069_DOWNLOAD_FAILURE = 9010,
	TR069_UPLOAD_FAILURE = 9011,
	TR069_FILE_TRANSFER_SERVER_AUTHENTICATION_FAILURE = 9012,
	TR069_UNSUPPORTED_PROTOCOL_FOR_FILE_TRANSFER = 9013,
	TR069_FILE_TRANSFER_FAILURE = 9014,
	TR069_FILE_TRANSFER_FAILURE_CONTACT_SERVER = 9015,
	TR069_FILE_TRANSFER_FAILURE_ACCESS_FILE = 9016,
	TR069_FILE_TRANSFER_FAILURE_COMPLETE = 9017,
	TR069_FILE_TRANSFER_FAILURE_CORRUPTED = 9018,
	TR069_FILE_TRANSFER_FAILURE_AUTHENTICATION = 9019,
	TR069_FILE_TRANSFER_FAILURE_TIMEOUT = 9020
	/* 9800 - 9899: Vendor defined fault codes */
	/* RPC Fault Code*/
}tr069ERR_e;
#endif


// config zcfg tr98 debug level
//#define ZTR_DEBUG_LEVEL ZCFG_LOG_DEBUG
#define ZTR_DEBUG_LEVEL ZCFG_LOG_WARNING

#ifdef ZCFG_MAPPING_DEBUG_SYSLOG
#define ZCFGTR98_SYSLOG (1 << 8)
#else
#define ZCFGTR98_SYSLOG 0
#endif
#ifdef ZCFG_MAPPING_DEBUG_STDLOG
#define ZCFGTR98_STDLOG (1 << 9)
#else
#define ZCFGTR98_STDLOG 0
#endif

#define LOGLEVEL_MASK ((1 << 3)-1)

#ifndef ZCFG_LOG_USE_DEBUGCFG
enum {
        ZTR_SL_EMERG =  ZCFG_LOG_EMERG | ZCFGTR98_SYSLOG,
        ZTR_SL_ALERT =  ZCFG_LOG_ALERT | ZCFGTR98_SYSLOG,
        ZTR_SL_CRIT =   ZCFG_LOG_CRIT | ZCFGTR98_SYSLOG,
        ZTR_SL_ERR  =   ZCFG_LOG_ERR | ZCFGTR98_SYSLOG,
        ZTR_SL_WARNING = ZCFG_LOG_WARNING | ZCFGTR98_SYSLOG,
        ZTR_SL_NOTICE = ZCFG_LOG_NOTICE | ZCFGTR98_SYSLOG,
        ZTR_SL_INFO  =  ZCFG_LOG_INFO | ZCFGTR98_SYSLOG,
        ZTR_SL_DEBUG =  ZCFG_LOG_DEBUG | ZCFGTR98_SYSLOG,
        ZTR_DL_EMERG =  ZCFG_LOG_EMERG | ZCFGTR98_STDLOG,
        ZTR_DL_ALERT =  ZCFG_LOG_ALERT | ZCFGTR98_STDLOG,
        ZTR_DL_CRIT =   ZCFG_LOG_CRIT | ZCFGTR98_STDLOG,
        ZTR_DL_ERR  =   ZCFG_LOG_ERR | ZCFGTR98_STDLOG,
        ZTR_DL_WARNING = ZCFG_LOG_WARNING | ZCFGTR98_STDLOG,
        ZTR_DL_NOTICE = ZCFG_LOG_NOTICE | ZCFGTR98_STDLOG,
        ZTR_DL_INFO  =  ZCFG_LOG_INFO | ZCFGTR98_STDLOG,
        ZTR_DL_DEBUG =  ZCFG_LOG_DEBUG | ZCFGTR98_STDLOG,
        ZTR_SDL_EMERG =  ZCFG_LOG_EMERG | ZCFGTR98_SYSLOG | ZCFGTR98_STDLOG,
        ZTR_SDL_ALERT =  ZCFG_LOG_ALERT | ZCFGTR98_SYSLOG | ZCFGTR98_STDLOG,
        ZTR_SDL_CRIT =   ZCFG_LOG_CRIT | ZCFGTR98_SYSLOG | ZCFGTR98_STDLOG,
        ZTR_SDL_ERR  =   ZCFG_LOG_ERR | ZCFGTR98_SYSLOG | ZCFGTR98_STDLOG,
        ZTR_SDL_WARNING = ZCFG_LOG_WARNING | ZCFGTR98_SYSLOG | ZCFGTR98_STDLOG,
        ZTR_SDL_NOTICE = ZCFG_LOG_NOTICE | ZCFGTR98_SYSLOG | ZCFGTR98_STDLOG,
        ZTR_SDL_INFO  =  ZCFG_LOG_INFO | ZCFGTR98_SYSLOG | ZCFGTR98_STDLOG,
        ZTR_SDL_DEBUG =  ZCFG_LOG_DEBUG | ZCFGTR98_SYSLOG | ZCFGTR98_STDLOG
};

// zcfg tr98 debug message
#ifdef ZCFG_MAPPING_DEBUG_SYSLOG
#define zsyslog(logLev, format, ...) \
               { if((ZCFGTR98_SYSLOG & logLev) && (ZTR_DEBUG_LEVEL >= (logLev & LOGLEVEL_MASK))) \
                    syslog((logLev & LOGLEVEL_MASK), format, ##__VA_ARGS__); }
#else
#define zsyslog(logLev, format, ...)  do {}while(0)
#endif

#ifdef ZCFG_MAPPING_DEBUG_STDLOG
#define zstdlog(logLev, format, ...) \
               { if((ZCFGTR98_STDLOG & logLev) && (ZTR_DEBUG_LEVEL >= (logLev & LOGLEVEL_MASK))) \
                    printf(format, ##__VA_ARGS__); }
#else
#define zstdlog(logLev, format, ...)  do {}while(0)
#endif

#define ztrdbg(logLev, format, ...) do{\
		zsyslog(logLev, format, ##__VA_ARGS__); \
		zstdlog(logLev, format, ##__VA_ARGS__); \
	} while(0)
#else
enum {
        ZTR_SL_EMERG = ZCFG_SL_EMERG, // ZCFG_LOG_EMERG | ZCFGTR98_SYSLOG,
        ZTR_SL_ALERT = ZCFG_SL_ALERT, // ZCFG_LOG_ALERT | ZCFGTR98_SYSLOG,
        ZTR_SL_CRIT =  ZCFG_SL_CRIT, // ZCFG_LOG_CRIT | ZCFGTR98_SYSLOG,
        ZTR_SL_ERR  =  ZCFG_SL_ERR, // ZCFG_LOG_ERR | ZCFGTR98_SYSLOG,
        ZTR_SL_WARNING = ZCFG_SL_WARNING, // ZCFG_LOG_WARNING | ZCFGTR98_SYSLOG,
        ZTR_SL_NOTICE = ZCFG_SL_NOTICE, // ZCFG_LOG_NOTICE | ZCFGTR98_SYSLOG,
        ZTR_SL_INFO  = ZCFG_SL_INFO, // ZCFG_LOG_INFO | ZCFGTR98_SYSLOG,
        ZTR_SL_DEBUG = ZCFG_SL_DEBUG, // ZCFG_LOG_DEBUG | ZCFGTR98_SYSLOG,
        ZTR_DL_EMERG = ZCFG_DL_EMERG, // ZCFG_LOG_EMERG | ZCFGTR98_STDLOG,
        ZTR_DL_ALERT = ZCFG_DL_ALERT, // ZCFG_LOG_ALERT | ZCFGTR98_STDLOG,
        ZTR_DL_CRIT = ZCFG_DL_CRIT, // ZCFG_LOG_CRIT | ZCFGTR98_STDLOG,
        ZTR_DL_ERR  = ZCFG_DL_ERR, // ZCFG_LOG_ERR | ZCFGTR98_STDLOG,
        ZTR_DL_WARNING = ZCFG_DL_WARNING, // ZCFG_LOG_WARNING | ZCFGTR98_STDLOG,
        ZTR_DL_NOTICE = ZCFG_DL_NOTICE, // ZCFG_LOG_NOTICE | ZCFGTR98_STDLOG,
        ZTR_DL_INFO  = ZCFG_DL_INFO, // ZCFG_LOG_INFO | ZCFGTR98_STDLOG,
        ZTR_DL_DEBUG = ZCFG_DL_DEBUG, // ZCFG_LOG_DEBUG | ZCFGTR98_STDLOG,
        ZTR_SDL_EMERG = ZCFG_SDL_EMERG, // ZCFG_LOG_EMERG | ZCFGTR98_SYSLOG | ZCFGTR98_STDLOG,
        ZTR_SDL_ALERT = ZCFG_SDL_ALERT, // ZCFG_LOG_ALERT | ZCFGTR98_SYSLOG | ZCFGTR98_STDLOG,
        ZTR_SDL_CRIT = ZCFG_SDL_CRIT, // ZCFG_LOG_CRIT | ZCFGTR98_SYSLOG | ZCFGTR98_STDLOG,
        ZTR_SDL_ERR  = ZCFG_SDL_ERR, // ZCFG_LOG_ERR | ZCFGTR98_SYSLOG | ZCFGTR98_STDLOG,
        ZTR_SDL_WARNING = ZCFG_SDL_WARNING, // ZCFG_LOG_WARNING | ZCFGTR98_SYSLOG | ZCFGTR98_STDLOG,
        ZTR_SDL_NOTICE = ZCFG_SDL_NOTICE, // ZCFG_LOG_NOTICE | ZCFGTR98_SYSLOG | ZCFGTR98_STDLOG,
        ZTR_SDL_INFO  = ZCFG_SDL_INFO, // ZCFG_LOG_INFO | ZCFGTR98_SYSLOG | ZCFGTR98_STDLOG,
        ZTR_SDL_DEBUG = ZCFG_SDL_DEBUG // ZCFG_LOG_DEBUG | ZCFGTR98_SYSLOG | ZCFGTR98_STDLOG
};

#define ztrdbg(logLev, format, ...) zcfgLog(logLev, format, ##__VA_ARGS__)
#endif

#define MSG_EMPTY(msg) ((msg != NULL && msg[0] != '\0') ? msg : "(empty)")


#define TRANS_WANIPIFACE_98TO181   1
#define TRANS_WANIPIFACE_181TO98   2


extern int myEid; /*use source Eid to know who use this library*/
typedef struct tr98Parameter_s {
	char 			*name;			/*parameter name*/
	int 			attr;			/*parameter attribute*/
	int			len;			/*parameter length*/
	json_type		type;			/*parameter type*/
}tr98Parameter_t;

typedef struct tr98Object_s {
	char			*name;			   /*object full path name*/
	int 			attr;			   /*object attribute*/
	struct tr98Parameter_s 	*parameter;		   /*next level parameters*/
	int (*getObj)(char *, int, struct json_object **, bool);
	int (*setObj)(char *, int, struct json_object *, struct json_object *, char *);
	int (*addObj)(char *, int *);
	int (*delObj)(char *);
	int (*notify)(char *, char *, struct json_object *, int, struct json_object **);
	int (*getAttr)(char *, int , char *);
	int (*setAttr)(char *, int , char *, int , struct json_object *);
}tr98Object_t;

typedef struct tr98NameObj_s {
	zcfg98sn_t nameSeqNum;
	tr98Object_t *tr98Obj;
}tr98NameObj_t;

typedef zcfgRet_t (*parmGurdRout)(const char *objpath, const char *parmname, struct json_object *spvobj, struct json_object *parmGurdObj, char **faultString);
typedef zcfgRet_t (*rpcSubRout)(const char *, objIndex_t *, struct json_object *, struct json_object *);

#define ZCFG_TR98_PARMGURD "/etc/zcfg_tr98_parmgurd.json"
typedef struct tr98ParmRout_s {
	zcfg98sn_t nameSeqNum;
	parmGurdRout rout;
}tr98ParmRout_t;

typedef struct tr98RpcSubRout_s {
	zcfg98sn_t nameSeqNum;
	rpcSubRout rout;
}tr98RpcSubRout_t;


typedef zcfgRet_t (*tr98QryHandleRout)(const char *, int, objIndex_t *, struct json_object **, void *data);
typedef struct tr98QueryHandleRout_s {
	zcfg98sn_t nameSeqNum;
	tr98QryHandleRout rout;
}tr98QueryHandleRout_t;

#ifdef ZCFG_TR181_RPC_OBJECT_HANDLE_ROUT
typedef zcfgRet_t (*spvHandleRout)(uint32_t , objIndex_t *, struct json_object *, struct json_object *, char *);

typedef struct tr181SpvHandleRout_s {
	uint32_t oid;
	spvHandleRout rout;
}tr181SpvHandleRout_t;

typedef zcfgRet_t (*qryHandleRout)(uint32_t , objIndex_t *, struct json_object *, void *data);
typedef struct tr181QueryHandleRout_s {
	uint32_t oid;
	qryHandleRout rout;
}tr181QueryHandleRout_t;

#endif


typedef struct objPathIdx_s {
	uint32_t objnum;
	int16_t idx[SUPPORTED_INDEX_LEVEL];
	char objpath[256+2];
}objPathIdx_t;

void zcfgEnableRootQuryBlackObjPath(int);
//bool zcfgObjectPathListToStruct(const char *objectPathList, int);
//bool zcfgObjectPathListPickObjPath(const char *objectPathName);
int zcfgFeTr98QryRootPath();
void zcfgFeTr98SetQryRootPath(int );

bool zcfgSetRootQueryNotReplyObjects(const char *, int);
bool zcfgSetQueryNotReplyObjects(const char *, int);
void zcfgSetRunningDataModelSpec(const char *);
zcfgRet_t zcfgQueryPathNameNotReplied(const char *);
zcfgRet_t zcfgQueryObjectNotReplied(zcfg_offset_t , objIndex_t *);

struct json_object *zcfgFeTr181QueryHandleRoutAddDataObjParamInfo(struct json_object *);
struct json_object *zcfgFeTr181QueryHandleRoutPullDataObjParamInfo(struct json_object *);


#define TR98_MAX_OBJ_NAME_LENGTH 257
#define _isdigit(c) ((c >= 0x30) && (c <= 0x39))

zcfgRet_t zcfgFeTr98AllIGDNameGet();

void zcfgFe98BondingTag(bool);

zcfgRet_t zcfgFeTr98ObjGet(char *, struct json_object **);
zcfgRet_t zcfgFe98StaticNameTableInit(void);
zcfgRet_t zcfgFe98InfoDataSetInit(void);
zcfgRet_t ReplaceStaticWANDeviceIndex(const char *tr98ObjName, char *pathname);
#ifdef ZCFG_RUNNING_WANDEV_INDEX_CUSTOMIZATION
zcfgRet_t zcfgFeTr98StaticWANDevSync(void *);
bool zcfgFe98StaticWanDevStatus(void);
#else
#define zcfgFeTr98StaticWANDevSync(param) do{}while(0)
#endif
zcfgRet_t zcfgFe98To181ObjMappingNameAdd(const char *tr98PathName, const char *tr181PathName, zcfg_name_t *nameSeqNum, objIndex_t *tr98ObjIid);
zcfgRet_t zcfgFe98To181ObjMappingNameGet(const char *tr98PathName, char *tr181PathName);
zcfgRet_t zcfgFe181To98ObjMappingNameGet(const char *tr181PathName, char *tr98PathName);
zcfgRet_t zcfgFe98NameToSeqnum(const char *tr98PathName, zcfg_name_t *seqnum, objIndex_t *tr98ObjIid);
zcfgRet_t zcfgFe98SeqnumToName(zcfg_name_t seqnum, objIndex_t *objIid, char *tr98PathName);
char *zcfgFeTr98ObjQueryInstanceArray(const char *tr98PathName);
zcfgRet_t zcfgFe98ParmMappingToName(const char *notifyName, char *tr98NotifyName);
zcfgRet_t zcfgTr98MapAddObjName();
zcfgRet_t zcfgTr181MapAddObjName();
#ifdef TR098181_OBJECT_MAPPING_NUM_NAME_CONVERT
void zcfgMappingConvertDataOutput(int enable);
struct json_object *zcfgTr98CreatePvsNewMapping();
struct json_object *zcfgTr181CreatePvsNewMapping();
zcfgRet_t zcfgTr98MappingConvert(struct json_object *, struct json_object *);
zcfgRet_t zcfgTr181MappingConvert(struct json_object *, struct json_object *);
#endif

int charHex2Int(char );
int hexStr2AscStr(const char *, char *);
int ascStr2HexStr(const char *, char *);
bool base64Char(char );
char *base64StrParticularCharHandle(const char *);

zcfgRet_t zcfgFeTr98QueryObjParamNames(const char *, struct json_object **, struct json_object *);
void zcfgFeTr98GpnQueryHandleRoutInit();

#ifdef ZCFG_TR181_RPC_OBJECT_HANDLE_ROUT
void zcfgFeTr181SpvHandleRoutInit();
zcfgRet_t zcfgFeMultiObjJsonSpvHandleRout(struct json_object *multiJobj, char *faultString);
void zcfgFeTr181QueryHandleRoutInit();
zcfgRet_t zcfgFeTr181QueryHandleRout(uint32_t oid, objIndex_t *objIid, struct json_object *qryObj, void *data);
#else
#define zcfgFeTr181SpvHandleRoutInit() { }
#define zcfgFeMultiObjJsonSpvHandleRout(multiJobj, faultString) ZCFG_SUCCESS
#define zcfgFeTr181QueryHandleRoutInit() { }
#define zcfgFeTr181QueryHandleRout(oid, objIid, qryObj, data) ZCFG_SUCCESS
#endif
char *csvStringStripTerm(const char *csv, const char *term);
zcfgRet_t zcfgFeTr98ObjNameGet(char *, struct  json_object** );
zcfgRet_t zcfgFeTr98ObjNameObjGet(char *, struct json_object **);
zcfgRet_t zcfgFeTr98ObjParamSet(char *, uint32_t , struct json_object *, char *);
zcfgRet_t zcfgFeTr98ObjSet(char *, struct json_object *, char *paramfault);
zcfgRet_t zcfgFeTr98MultiObjSet(char *, struct json_object *, struct json_object *, char *paramfault);
zcfgRet_t zcfgFeTr98ObjAdd(char *, int *);
zcfgRet_t zcfgFeTr98ObjDel(char *);
zcfgRet_t zcfgFeTr98DefaultValueSet(struct json_object *, char *, int);
int zcfgFeTr98ObjAttrGet(char *);
zcfgRet_t zcfgFeTr98Notify(struct json_object *, struct json_object **);
zcfgRet_t zcfgFeTr98ParamList(char *);

int zcfgFeTr98ParamAttrChk(int , int);
#ifdef ZCFG_QUERY_TR98_PARM_ATTR_LIST
zcfgRet_t zcfgFeTr98QueryAttrObjExist(const char *, struct json_object **);
zcfgRet_t zcfgFeTr98QueryAttrObjName(const char *, struct json_object **);

void zcfgTr98AttrListEnable();
void *zcfgTr98AttrListSync(struct json_object *);
void zcfgTr98AttrListClear();
bool zcfgTr98AttrListUtilized();
zcfgRet_t zcfgTr98AttrListMultiParmAttrSetSync(zcfgFeSetParmAttrLst_t *);

zcfgRet_t zcfgSetParmAttrLstAddTr98ObjParmAttr(zcfgFeSetParmAttrLst_t *, const char *, const char *, int );

#else
#define zcfgFeTr98QueryAttrObjExist(name, parm) zcfgFeTr98ObjNameGet(name, parm)
#define zcfgFeTr98QueryAttrObjName(name, parm) zcfgFeTr98ObjNameGet(name, parm)

#define zcfgTr98AttrListEnable() { }
#define zcfgTr98AttrListSync(obj) obj
#define zcfgTr98AttrListClear() { }
#define zcfgTr98AttrListUtilized() 0
#define zcfgTr98AttrListMultiParmAttrSetSync(obj) { }

#define zcfgSetParmAttrLstAddTr98ObjParmAttr(obj, parm1, parm2, parm3) { }

#endif
int zcfgFeTr98ParamAttrGetByName(char *, char *);
zcfgRet_t zcfgFeTr98AllParamAttrGetByObjName(const char *, struct json_object *);
int zcfgFeTr98ObjParamAttrGetByName(const char *tr98ObjName, const char *name);
#ifdef ZCFG_PARM_NAMEMAPPING
zcfgFeSetParmAttr_t *zcfgFeTr98ParamAttrSetByName(uint32_t objnum, objIndex_t *objIid, const char *parmName, uint32_t setAttrObjNum, objIndex_t *setAttrObjIid, const char *setAttrParmName, uint32_t attr);
int zcfgFeTr98ParamAttrMultiSetByName(char *tr98ObjName, char *name, int notify, zcfgFeSetParmAttrLst_t *setParmAttrLst);
#else
int zcfgFeTr98ParamAttrMultiSetByName(char *, char *, int , struct json_object *);
#endif
zcfgRet_t zcfgFeTr98QueryParamListUnit(const char *, const char *, tr98Parameter_t *);
int zcfgFeTr98ParamTypeGetByName(char *, char *);
int zcfgFeTr98ParamAttrContentGetByName(char *, char *);
zcfgRet_t zcfgFeTr98ParamChk(char *, char *, char *);
zcfgSubObjNameList_t* zcfgFeTr98SubObjNameListGet(char *);

#ifdef ZCFG_TR98_PARAM_GUARD
zcfgRet_t zcfgTr98ParmGurdInit(void);
zcfgRet_t zcfgTr98ParmGurdScan(const char *, const char *, struct json_object *, struct json_object *, char **);
struct json_object *zcfgTr98RetrieveParmGurdObj(const char *);
#else
#define zcfgTr98ParmGurdInit() {}
#define zcfgTr98ParmGurdScan(p, a, r, m, t) ZCFG_SUCCESS
#define zcfgTr98RetrieveParmGurdObj(n) NULL
#endif

#ifdef ZCFG_APPLY_RPC_METHOD_AND_SUBSEQUENT_ROUT
bool zcfgAddSpvSubsequent(struct json_object *tr98SpvObj);
#else

#define zcfgAddSpvSubsequent(obj) (0)

#endif

zcfgRet_t zcfgFeTr98ObjSpvGet(const char *, struct json_object **, int);
zcfgRet_t zcfgFeTr98ObjSpvDelete(const char *);
struct json_object *zcfgFeSessionTr98SpvObjRetrieve();
void zcfgFeSessionTr98SpvObjSet(struct json_object *);
zcfgRet_t zcfgFeSessionTr98SpvObjectClear();

struct json_object *zcfgFeNewTr98SpvObject();
bool zcfgTr98StatusRunSpvValid(struct json_object *);
bool zcfgFeTr98SpvAndApplyOnSessionComplete(struct json_object *multiobj);
zcfgRet_t zcfgFeAddTr98SpvObject(struct json_object *, const char *, struct json_object *, struct json_object *);
zcfgRet_t zcfgFeDeleteTr98SpvObject(struct json_object *, const char *);
struct json_object *zcfgFeRetrieveTr98SpvObject(struct json_object *tr98SpvObj, const char *objpath, struct json_object **);
zcfgRet_t zcfgFeTr98SpvObjectAppendReplace(struct json_object *, struct json_object *);

struct json_object *zcfgFe98ParamGuardInit(const char *, void *);
zcfgRet_t zcfgFe98ParamGuard(struct json_object *, const char *, struct json_object *);
void zcfgFe98ParamGuardRelease(struct json_object *);

char *translateWanIpIface(int dataTransType, const char *wanIpIfaces);
zcfgRet_t zcfgFe98To181IpIface(const char *tr98IfaceName, char *ipIface);
zcfgRet_t zcfgFeTr181IpIfaceRunning(const char *iface, char *paramfault);
zcfg_offset_t zcfgFeTr181WanSetLink(char *wanLinkName, bool set, void **retObj, objIndex_t *retObjIndex, int *applied);

zcfgRet_t zcfgFeTr181IfaceStackLowerLayerGet(char *higherLayer, char *result);
zcfgRet_t zcfgFeTr181IfaceStackHigherLayerGet(char *lowerLayer, char *result);

#define JSON_OBJ_COPY(json_object) json_tokener_parse(json_object_to_json_string(json_object))

#define JSON_OBJ_EMPTY(obj) (!obj || (obj && (json_object_get_object(obj)->count == 0)))

zcfgRet_t feObjStructGet(zcfg_offset_t , objIndex_t *, void **, bool);
zcfgRet_t feObjStructGetNext(zcfg_offset_t , objIndex_t *, void **, bool);
zcfgRet_t feObjStructGetSubNext(zcfg_offset_t ,objIndex_t * ,objIndex_t * , void ** ,bool );
zcfgRet_t feObjJsonGet(zcfg_offset_t , objIndex_t *, struct json_object **, bool);
zcfgRet_t feObjJsonGetNext(zcfg_offset_t , objIndex_t *, struct json_object **, bool);
zcfgRet_t feObjJsonSubNext(zcfg_offset_t ,objIndex_t * ,objIndex_t * , struct json_object ** ,bool );

#define zcfgFeRetrieveSpv(objpath) zcfgFeHandRoutRetrieveTr98Spv(objpath, tr98Jobj, multiJobj)

#ifdef ZCFG_APPLY_MULTIOBJSET_ON_SESSIONCOMPLETE
void zcfgFeSessMultiObjSet();
void zcfgFeSessMultiObjSetClear();
struct json_object *zcfgFeSessMultiObjSetRetrieve();
void zcfgFeSessMultiObjSetSave(struct json_object *multiobj);
struct json_object *zcfgFeSessMultiObjSetUtilize(struct json_object *multiobj);
void zcfgFeJsonMultiObjSetParamk(const char *);
struct json_object *zcfgFeJsonMultiObjParamkRetrieve();
#else
#define zcfgFeSessMultiObjSet() { }
#define zcfgFeSessMultiObjSetClear() { }
#define zcfgFeSessMultiObjSetRetrieve() NULL
#define zcfgFeSessMultiObjSetSave(obj) { }
#define zcfgFeSessMultiObjSetUtilize(obj) obj
#define zcfgFeJsonMultiObjSetParamk(paramk) { }
#define zcfgFeJsonMultiObjParamkRetrieve() NULL
#endif

#ifdef ZCFG_RPC_REQUEST_ADDITIONS
struct json_object *zcfgFeRpcRequestAdditionNew();
#else
#define zcfgFeRpcRequestAdditionNew() NULL
#endif

void zcfgRpcTr98GpnSpeedObjsEnable();
void zcfgRpcTr98GpnSpeedObjsClear();
bool zcfgRpcTr98GpnSpeedObjsUtilized();

void zcfgRpcTr98GpvSpeedObjsEnable();
void zcfgRpcTr98GpvSpeedObjsClear();
bool zcfgRpcTr98GpvSpeedObjsUtilized();

void zcfgFeTr98GuiCustomizationSet(char *, void *);

void zcfgRpcSpeedObjsRpcObjectListInit();
void zcfgRpcSpeedObjsAddRpcObject(const char *);


// utilize GpnSpeedObjs to sync the same objects/params
#define zcfgRpcTr98GpaSpeedEnable() zcfgRpcTr98GpnSpeedObjsEnable()
#define zcfgRpcTr98GpaSpeedClear() zcfgRpcTr98GpnSpeedObjsClear()
#define zcfgRpcTr98GpaSpeedUtilized() zcfgRpcTr98GpnSpeedObjsUtilized()

#define zcfgFeRpcRequestAddRpcDelayApply(_rpcObjAddition, _value) zcfgFeRpcRequestAddRpcApplyAttr(_rpcObjAddition, "delayapply", json_object_new_boolean(_value))
#define zcfgFeRpcRequestAdditionRelease json_object_put

zcfgRet_t zcfgFeRpcRequestAddAttr(struct json_object *, const char *, struct json_object *, bool );
zcfgRet_t zcfgFeRpcRequestAddReplyAttr(struct json_object *, const char *, struct json_object *);
zcfgRet_t zcfgFeRpcRequestAddRpcApplyAttr(struct json_object *, const char *, struct json_object *);
zcfgRet_t zcfgFeRpcRequestAddMethod(struct json_object *, const char *, bool);
zcfgRet_t zcfgFeRpcRequestSpecifyMethodParam(struct json_object *, const char *, const char *, struct json_object *);

zcfgRet_t zcfgFeRpcObjectRetrieveMethodReply(struct json_object *, const char *, struct json_object **);
struct json_object *zcfgFeRpcRequestRetrieveMethodReplyParam(struct json_object *, const char *);

#endif