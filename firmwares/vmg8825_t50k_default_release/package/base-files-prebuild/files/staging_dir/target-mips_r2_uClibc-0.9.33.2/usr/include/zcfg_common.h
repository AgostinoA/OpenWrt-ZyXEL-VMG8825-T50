#ifndef _ZCFG_COMMON_H
#define _ZCFG_COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

/* return message 
 *  notice: if you want to do any change on this enum table, please synchronous the file "zcfg_ret.h"
 */
typedef enum
{
   ZCFG_RET_OFFSET = -22,
   ZCFG_DELETE_REJECT,
   ZCFG_REQUEST_REJECT,
   ZCFG_REQUEST_POSTPONED,		/*request is postponed*/
   ZCFG_INVALID_OBJECT,			/*invalid object name*/
   ZCFG_INVALID_PARAM_VALUE,
   ZCFG_INVALID_PARAM_VALUE_LENGTH,
   ZCFG_INVALID_IMAGE,
   ZCFG_INVALID_ARGUMENTS,
   ZCFG_SET_READ_ONLY_PARAM,
   ZCFG_EXCEED_MAX_INS_NUM,
   ZCFG_INS_CREATE_ERR,
   ZCFG_NOT_INSTANCE,
   ZCFG_SET_ATTR_ERROR,
   ZCFG_INVALID_FORMAT, 
   ZCFG_NOT_FOUND,
   ZCFG_NO_SUCH_OBJECT,			/*instance not exist*/
   ZCFG_INTERNAL_ERROR,
   ZCFG_NO_SUCH_PARAMETER,
   ZCFG_ERROR_PARAMETER_TYPE,
   ZCFG_INVALID_EID,
   ZCFG_TIMEOUT,
   ZCFG_SUCCESS,
   ZCFG_SUCCESS_AND_NO_REPLY,
   ZCFG_NO_MORE_INSTANCE,
   ZCFG_EMPTY_OBJECT,
   ZCFG_OBJECT_UPDATED,
   ZCFG_OBJECT_WITHOUT_PARAMETER,
   ZCFG_TR98_DATA_MODEL,
   ZCFG_DELAY_APPLY,
   ZCFG_SAME_IMAGE
} zcfgRet_t;

enum object_action{
        ADD_OBJ,
        DEL_OBJ,
        SET_OBJ
};

typedef uint32_t     zcfg_offset_t;

typedef uint32_t  zcfg_name_t;

#ifdef ZCFG_CONFIG_ENCRYPT
#define PASSWD "N3z0y93"
#endif

#define RUNTIME_CONFIG_FILE "/var/zcfg_config.rdm"
#define RUNTIME_PREDEF_FILE "/var/zcfg_predef.rdm"
#define ZCFG_ATTR_MODIFIED_SCHEMA_FILE "/data/zcfg_modified_schema"
#define ZCFG_ATTR_MODIFIED_SCHEMA_FILE_BAK "/data/zcfg_modified_schema.bak"

//#define ZCFG_COMPRESSED_CONFIG_FILE "/tmp/zcfg_config.tar.gz"
#define ZCFG_COMPRESSED_CONFIG_FILE "/tmp/zcfg_config.json"
#define ZCFG_ENCRYPT_CONFIG_FILE "/tmp/zcfg_config.encrypt"

#define ZCFG_CONFIG_DIR "/data"
#define ZCFG_TR98_MAP_PATH  ZCFG_CONFIG_DIR"/zcfg_tr98_map.json"
#define ZCFG_TR181_MAP_PATH  ZCFG_CONFIG_DIR"/zcfg_tr181_map.json"
#define ZCFG_TR98_MAP_ADDOBJNAME  ZCFG_CONFIG_DIR"/zcfg_tr98_map_addobjname.json"
#define ZCFG_TR181_MAP_ADDOBJNAME  ZCFG_CONFIG_DIR"/zcfg_tr181_map_addobjname.json"

#define ZCFG_TR98_MAP_CONVERT_DEBUG ZCFG_CONFIG_DIR"/zcfg_tr98_map_convert_debug"

#define ZCFG_TR98_PATHNAME_PVSNEW  ZCFG_CONFIG_DIR"/zcfg_tr98_pvsnew.json"
#define ZCFG_TR181_PATHNAME_PVSNEW  ZCFG_CONFIG_DIR"/zcfg_tr181_pvsnew.json"
#define ZCFG_TR98_MAP_CONVERT ZCFG_CONFIG_DIR"/zcfg_tr98_map_convert.json"
#define ZCFG_TR181_MAP_CONVERT ZCFG_CONFIG_DIR"/zcfg_tr181_map_convert.json"
#define ZCFG_TR98_MAP_CONVERTED ZCFG_CONFIG_DIR"/zcfg_tr98_map_converted.json"
#define ZCFG_TR181_MAP_CONVERTED ZCFG_CONFIG_DIR"/zcfg_tr181_map_converted.json"

#define ZCFG_TR98_MAP_ATTR_LIST_PATH ZCFG_CONFIG_DIR"/zcfg_tr98_map_parmattrlist.json"


#define MAX_TR181_DATA_NUM 3500
#define MAX_TR98_IGD_NUM 3500

#define OBJ_NAME_BUFF_SIZE 256 
#define PARAMETER_NAME_BUFF_SIZE 64
#define SUPPORTED_INDEX_LEVEL 6

#define FEEDBACK_MSG_LENGTH 256

#define MAX_TR181_PATHNAME  OBJ_NAME_BUFF_SIZE

typedef struct objIndex_s {
        uint8_t level;
        uint8_t idx[SUPPORTED_INDEX_LEVEL];
}objIndex_t;

#define MAX_PARMNAME_LEN PARAMETER_NAME_BUFF_SIZE
#define CONCURRENT_WAN_BR_NAME "br_ccw"

typedef struct {
	uint32_t num_1;
	objIndex_t objIdxData_1;
	char mask_1;
	uint32_t num_2;
	objIndex_t objIdxData_2;
	char mask_2;
}zcfgMapData_t;

typedef struct {
	uint32_t objnum;
	objIndex_t objIid;
	uint8_t maskObj;
	uint32_t setAttrObjNum;
	objIndex_t setAttrObjIid;
	uint8_t maskSetAttrObj;
	uint32_t attr;
	uint16_t parmNameLen;
	uint16_t setAttrParmNameLen;
} zcfgParmSetAttr_t;

typedef struct {
	uint32_t objnum;
	objIndex_t objIid;
	uint8_t mask;
	uint32_t parmNameLen;
	uint32_t attr;
} zcfgParmQryAttr_t;

typedef zcfgParmQryAttr_t zcfgParmQryValue_t;

#define IID_INIT(IID) memset(&IID, 0, sizeof(objIndex_t))
#define GET_OBJ_INFO_BY_OID(OID) (objInfo_t *)(schemaShmAddr + OID)
#define GET_FIRST_PARAMETER_INFO(OBJ_INFO) (parameterInfo_t *)(OBJ_INFO+1)
#define GET_PAMAMETERS_IN_OBJECT(objInfo, paramInfo, paramName) int c; parameterInfo_t *paramInfo; char *paramName; \
	for(c = 0, paramInfo = GET_FIRST_PARAMETER_INFO(objInfo), paramName = (char *)(paramNameShmAddr + paramInfo->name); c < objInfo->count; c++, paramInfo++, paramName = (char *)(paramNameShmAddr + paramInfo->name))
#define GET_OBJ_NAME(objInfo) (char *)(objNameShmAddr + objInfo->name)

//certificate
#define CERT_DIR 	"/var/cert"
#define PRIVATE_KEY_FILE	"cert.key"
#define CERT_FILE 				"cert.crt"

#define CA_PATH "/var/cert/ca/"
#define TR69CLIENT_CRT_NAME CERT_DIR"/tr69_cert.crt"
#define TR69CLIENT_KEY_NAME CERT_DIR"/tr69_cert.key"


// Support Feature of Idle Timeout Mechanism for CLI connection
#define IDLE_TIMEOUT_FILE "/var/accountIdleTime"

#define KMOD_LOAD_PATH "/lib/modules/"

#endif
