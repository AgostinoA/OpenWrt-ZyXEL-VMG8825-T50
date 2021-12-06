#ifndef _ZCMD_SCHEMA_H
#define _ZCMD_SCHEMA_H
#include <sys/shm.h>
#include <sys/ipc.h>
#include "zcfg_eid.h"

#define ZCFG_SHM_KEY "ZCFG"

/* parameter attribute definition */
#define PARAMETER_ATTR_NOTIFY_MASK                ((1 << 0)|(1 << 1))	/*use for notify off*/
#define PARAMETER_ATTR_PASSIVENOTIFY              (1 << 0)
#define PARAMETER_ATTR_ACTIVENOTIFY               (1 << 1)
#define PARAMETER_ATTR_DENY_ACTIVENOTIFY_REQUEST  (1 << 2)             /*Deny Request for Active Notification*/
#define PARAMETER_ATTR_READONLY                   (1 << 3)
#define PARAMETER_ATTR_CONFIG                     (1 << 4)		/*means this parameter needs to be saved to config.xml*/
#define PARAMETER_ATTR_DEFAULTVALUE               (1 << 5)		/*only run time use, not store at config.xml and add at sysdef.xml, if yes, this parameter has default value*/
#define PARAMETER_ATTR_DEFAULTATTR                (1 << 6)		/*same with PARAMETER_ATTR_DEFAULTVALUE*/
#define PARAMETER_ATTR_FIX_BITS                   ((1 << 0) | (1 << 3) | (1 << 4) | (1 << 5))
#define PARAMETER_ATTR_WRITE                      (1 << 7)            	/*Both Read and Write support is REQUIRED. */
#define PARAMETER_ATTR_SHOW                       ((1 << 3)|(1 << 7)) 	/*Attribute can be showed*/
#define PARAMETER_ATTR_HIDDEN                     (1 << 8)		/* Hide the parameter from tr069 server*/
#define PARAMETER_ATTR_SAVED                      (1 << 9)      /* parameter value should be saved to config file no matter it is writable or not*/
#define PARAMETER_ATTR_DENY_PASSIVENOTIFY_REQUEST (1 << 10)
#define PARAMETER_ATTR_DENY_DISABLENOTIFY_REQUEST (1 << 11)
#define PARAMETER_ATTR_PASSWORD                   (1 << 12)     /* When ACS read, this parameter returns an empty string, regardless of the actual value. */
#define PARAMETER_ATTR_KEEP_DEFAULT               (1 << 13)
#define PARAMETER_ATTR_STD_RESET		  (1 << 14)     /* it's std Reset param */
/* End of parameter attribute definition*/

/* additional attribute utilized on 'set parameter attribute' */
#define PARAMETER_ATTR_ADDITIONAL_MASK (((1 << 16)-1) << 16)
#define PARAMETER_ATTR_TR98              (1 << 16)
#define PARAMETER_ATTR_TR181             ((1 << 1) << 16)
#define PARAMETER_ATTR_ROUTINE_REQ       ((1 << 2) << 16)
#define PARAMETER_ATTR_NOT_APPLIED       ((1 << 3) << 16)
#define PARAMETER_ATTR_NOATTR            (1 << 30)

#define PARAMETER_ATTR_NOTIFY_RETRIEVE(attr) (attr & PARAMETER_ATTR_NOTIFY_MASK)
#define PARAMETER_ATTR_ADDITION_RETRIEVE(attr) (attr & PARAMETER_ATTR_ADDITIONAL_MASK)
#define PARAMETER_ATTR_SET_TR98(attr) (attr | PARAMETER_ATTR_TR98)
#define PARAMETER_ATTR_SET_TR181(attr) (attr & ~PARAMETER_ATTR_TR98)    // default is tr181 attr set

/*Definitions for node attribute*/
#define ATTR_OBJECTNODE                           (1 << 0)		/*run time/compiler time both use, no store at xml*/
#define ATTR_INDEXNODE                            (1 << 1)		/*run time use, compiler time mark, store both xml*/
#define ATTR_INDEXCHILD                           (1 << 2)		/*compiler time use, no store at xml*/
#define ATTR_NODECONFIGURED                       (1 << 3)		/*run time use, no store at xml, means this node has been configured and need to save*/
#define ATTR_ALWAYSACTIVE                         (1 << 4)		/*for some special case, ex. tr069, the index child nodes need to 
                                                                  active at default run time/compiler time both use, no store at xml*/
/* object attribute definition */
#define OBJECT_ATTR_PRESENT                       (1 << 5)      /* The object is REQUIRED to be present. */
#define OBJECT_ATTR_CREATE                        (1 << 6)      /* Creation and deletion of instances of the object via AddObject and DeleteObject is REQUIRED. */
#define OBJECT_ATTR_HIDDEN                        (1 << 7)      /* Hide the object from tr069 server*/
#define OBJECT_ATTR_SAVED                         (1 << 8)      /* object instances only can be Added or Deleted in bakend and need to be saved to config file*/
#define OBJECT_ATTR_DELAY                         (1 << 9)      /* object should be delayed to apply if tr609 requests */

#if 1 /* cpwang, minimize number of writing to flash, 2017-03-17 09:57:19 */

#define _NEW_FLAG_SAVE_TO_FLASH     1

#if _NEW_FLAG_SAVE_TO_FLASH
#define OBJECT_ENABLE_SAVE_TO_FLASH(objInfo)    objInfo->b_save_to_flash = true;
#define OBJECT_CLEAR_SAVE_TO_FLASH(objInfo)     objInfo->b_save_to_flash = false;
#define OBJECT_IF_SAVE_TO_FLASH(objInfo)        (objInfo->b_save_to_flash)
#else
#define OBJECT_ENABLE_SAVE_TO_FLASH(objInfo)    objInfo->attr |= OBJECT_ATTR_SAVED;
#define OBJECT_CLEAR_SAVE_TO_FLASH(objInfo)     objInfo->attr &= (~OBJECT_ATTR_SAVED);
#define OBJECT_IF_SAVE_TO_FLASH(objInfo)        (objInfo->attr & OBJECT_ATTR_SAVED)
#endif

#endif /* cpwang, minimize number of writing to flash, 2017-03-17 09:57:19 */

typedef struct parameterInfo_s {
	uint16_t name;          /*parameter name offset*/
	uint8_t type;
	uint32_t len;
	uint32_t attr;
	int min;
	int max;
	int iniVal;
}parameterInfo_t;

typedef struct objInfo_s {
	uint16_t name;		/*object name offset*/
	uint16_t count;
	uint8_t idxLevel;
	uint8_t maxEntry[SUPPORTED_INDEX_LEVEL];
	uint8_t verification;
	uint32_t attr;
	uint32_t size;		/*rough object structure size*/
	int (*beConfigLoad)(void *, void *, objIndex_t *, zcfgEid_t);
	int (*beStatsUpdate)(void *, objIndex_t *);
	int (*beValidate)(void *, zcfgEid_t, char *);

#if _NEW_FLAG_SAVE_TO_FLASH /* cpwang, minimize number of writing to flash, 2017-03-17 09:57:19 */
    /*
        it is a bool.
        in order to keep 4-byte alignment, assign to 32-bit
    */
    uint32_t    b_save_to_flash;
#endif /* cpwang, minimize number of writing to flash, 2017-03-17 09:57:19 */

}objInfo_t;

#endif // _ZCMD_SCHEMA_H
