/******************************************************************************/
/*
*  Copyright (C) 2012 ZyXEL Communications, Corp.
*  All Rights Reserved.
*
* ZyXEL Confidential; Need to Know only.
* Protected as an unpublished work.
*
* The computer program listings, specifications and documentation
* herein are the property of ZyXEL Communications, Corp. and
* shall not be reproduced, copied, disclosed, or used in whole or
* in part for any reason without the prior express written permission of
* ZyXEL Communications, Corp.
*/
/******************************************************************************/

#ifndef _CWMP_LOG_H_
#define _CWMP_LOG_H_

#include <stdio.h>
#include <stdarg.h>

#include "cwmptypedef.h"

#include "zcfg_debug.h"

extern uint32_t TR069_DEBUG_Flag;

#ifndef TR069ERR_E
#define TR069ERR_E
// need to sync to ztr69/cmm/include/cwmplog.h
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
	,TR069_FILE_TRANSFER_FAILURE_SAME_FW = 9800
	,TR069_DOWNLOAD_SCRIPT_RUN_FAIL = 9831
}tr069ERR_e;
#endif

/****************************************
* RPC Fault Code
****************************************/

/* -- ACS Fault Code -- */
#define	CWMPFAULT_8000_METHOD_NOTSUPPORTED		8000
#define	CWMPFAULT_8001_REQUEST_DND				8001
#define	CWMPFAULT_8002_INTERNAL_ERROR			8002
#define	CWMPFAULT_8003_INVALID_ARGUMENTS		8003
#define	CWMPFAULT_8004_RESOURCES_EXCEEDED		8004
#define	CWMPFAULT_8005_RETRY_REQUEST			8005
/* 8800 - 8899: Vendor defined fault codes */


#define TR069_DEBUG_STATUS              0x00001
#define TR069_DEBUG_PACKET              0x00002
#define TR069_DEBUG_ERROR               0x00004
#define TR069_DEBUG_DB               	0x00008
#define TR069_DEBUG_INFO                0x00010
#define TR069_DEBUG_FUNC                0x00020
#define TR069_DEBUG_ALL	TR069_DEBUG_STATUS|TR069_DEBUG_PACKET|TR069_DEBUG_ERROR|TR069_DEBUG_DB|TR069_DEBUG_INFO|TR069_DEBUG_FUNC


#define TR069_DEBUG_STATUS_STR          "[STATUS]"
#define TR069_DEBUG_PACKET_STR          "[PACKET]"
#define TR069_DEBUG_ERROR_STR           "[ERROR ]"
#define TR069_DEBUG_DB_STR           	"[DB    ]"
#define TR069_DEBUG_INFO_STR            "[INFO  ]"
#define TR069_DEBUG_FUNC_STR            "[FUNCT ]"

#define TR069LOG_STR        			"ZTR69"
#ifdef ZYXEL_TR69_SUPPLEMENTAL_ACS
#define TR069SUPLOG_STR			"ZTR69_SUP"	//Supplemental ACS
#endif

#ifdef ZCFG_LOG_USE_DEBUGCFG
#define debugLev2LogLev(debugLev) (debugLev << 8)
const char *debugLev2Str(uint32 debugLev);
// here, it utilizes only additional debug options
#define TR069LOG(debugLev, fmt, ...) zcfgLog(debugLev2LogLev(debugLev), "%s %s(): " fmt "\n", debugLev2Str(debugLev), __FUNCTION__, ##__VA_ARGS__)
#else
#define TR069LOG(f,...)             	TR069LOG2(f , __VA_ARGS__, 0)
#endif

#define TR069LOG2(f, fmt, ...){ \
	uint8 level;    \
	level = f;      \
	switch ( level ){       \
		case TR069_DEBUG_STATUS:				\
			tr069_debug(f, "%s %s(): " fmt "\n", TR069_DEBUG_STATUS_STR, __FUNCTION__, __VA_ARGS__) ;\
			break;	\
		case TR069_DEBUG_PACKET:				\
			tr069_debug(f, "%s %s(): " fmt "\n", TR069_DEBUG_PACKET_STR, __FUNCTION__, __VA_ARGS__) ;\
			break;	\
		case TR069_DEBUG_ERROR: 		\
			tr069_debug(f, "%s %s(): " fmt "\n", TR069_DEBUG_ERROR_STR, __FUNCTION__, __VA_ARGS__) ;\
			break;	\
		case TR069_DEBUG_DB: 		\
			tr069_debug(f, "%s %s(): " fmt "\n", TR069_DEBUG_DB_STR, __FUNCTION__, __VA_ARGS__) ;\
			break;	\
		case TR069_DEBUG_INFO:			\
			tr069_debug(f, "%s %s(): " fmt "\n", TR069_DEBUG_INFO_STR, __FUNCTION__, __VA_ARGS__) ;\
			break;	\
		case TR069_DEBUG_FUNC:			\
			tr069_debug(f, "%s %s(): " fmt "\n", TR069_DEBUG_FUNC_STR, __FUNCTION__, __VA_ARGS__) ;\
			break;	\
	}       \
}

                         
void TR069_DEBUG_OPEN( void );
void TR069_DEBUG_CLOSE( void );
void TR069_DEBUG_CONFIG( uint32 flag );

void cwmp_sync_DEBUGCFGLevel_And_DEBUG_Flag(void *);
void cwmp_sync_DEBUG_Flag_And_DEBUGCFGLevel();

int tr069_debug( uint8 dbgflag, char *fmt, ...);

#endif /*_CWMP_LOG_H_*/

