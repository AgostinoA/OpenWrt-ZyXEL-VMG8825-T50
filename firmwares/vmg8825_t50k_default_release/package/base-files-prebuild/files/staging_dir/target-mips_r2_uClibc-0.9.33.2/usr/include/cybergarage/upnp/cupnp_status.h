/******************************************************************
*
*	CyberLink for C
*
*	Copyright (C) Satoshi Konno 2005
*
*       Copyright (C) 2006 Nokia Corporation. All rights reserved.
*
*       This is licensed under BSD-style license,
*       see file COPYING.
*
*	File: upnp_status.h
*
*	Revision:
*
*	02/13/05
*		- first revision
*
*	10/31/05
*		- Added comments to all functions and structs
*
******************************************************************/

#ifndef _CG_UPNP_CUPNPSTATUS_H_
#define _CG_UPNP_CUPNPSTATUS_H_

#include <cybergarage/typedef.h>
#include <cybergarage/util/cstring.h>

#ifdef  __cplusplus
extern "C" {
#endif

/********************************************************************************
 * Defines
 ********************************************************************************/

#define CG_UPNP_STATUS_INVALID_ACTION 401
#define CG_UPNP_STATUS_INVALID_ARGS 402
#define CG_UPNP_STATUS_OUT_OF_SYNC 403
#define CG_UPNP_STATUS_INVALID_VAR 404
#define CG_UPNP_STATUS_ACTION_FAILED 501
#ifdef ZYXEL_PATCH /* ZyXEL 2013, charisse*/
#define CG_UPNP_STATUS_ARG_VALUE_INVALID 600
#define CG_UPNP_STATUS_ARG_VALUE_OUT_OF_RANGE 601
#define CG_UPNP_STATUS_OPT_NOT_IMPLEMENT 602
#define CG_UPNP_STATUS_OUT_OF_MEMORY 603
#define CG_UPNP_STATUS_HUMAN_INTER_REQUIRED 604
#define CG_UPNP_STATUS_STRING_ARG_TOO_LONG 605
//TR-064
#define CG_UPNP_STATUS_ACTION_NOT_AUTH 		606
#define CG_UPNP_STATUS_VALUE_ALREADY_SPE 	701
#define CG_UPNP_STATUS_VALUE_SPE_INVALID 	702
#define CG_UPNP_STATUS_INACT_CONN_REQUIRE 	703
#define CG_UPNP_STATUS_CONN_SETUP_FAIL 		704
#define CG_UPNP_STATUS_CONN_SETUP_INPROGRESS 705
#define CG_UPNP_STATUS_CONN_NOT_CONFIG 		706
#define CG_UPNP_STATUS_DISCON_INPROGESS 	707
#define CG_UPNP_STATUS_INVALID_L2_ADDR 		708
#define CG_UPNP_STATUS_INTERNET_ACCESS_DISABLE 709
#define CG_UPNP_STATUS_INVALID_CONN_TYPE 	710
#define CG_UPNP_STATUS_CONN_ALREADY_TERM 	711
#define CG_UPNP_STATUS_NULL_VALUE_SPE_ARRAY_IDX 712
#define CG_UPNP_STATUS_SPE_ARRAY_IDX_INVALID 713
#define CG_UPNP_STATUS_NO_SUCH_ENTRY_ARRAU 714
#define CG_UPNP_STATUS_WILD_CARD_NOT_PER_IN_SRCIP 715
#define CG_UPNP_STATUS_WILD_CARD_NOT_PER_IN_EXTPORT 716
#define CG_UPNP_STATUS_CONFLIC_IN_MAPENTRY 718
#define CG_UPNP_STATUS_ACTION_DISALLOW_WHEN_AUTO_CONFIG 719
#define CG_UPNP_STATUS_INVALID_DEVICE_UUID 720
#define CG_UPNP_STATUS_INVALID_SRVID 721
#define CG_UPNP_STATUS_INVALID_CONSRV_SELECT 723
#define CG_UPNP_STATUS_SAME_PORT_VALUE_REQUIRE 724
#define CG_UPNP_STATUS_ONLY_PER_LEAS_SUPPORT 725
#define CG_UPNP_STATUS_REMOTE_HOST_ONLY_SUPPORT_WILDCARD 726
#define CG_UPNP_STATUS_EXTPORT_ONLY_SUPPORT_WILDCARD 727
#define CG_UPNP_STATUS_INVALID_CHANNEL 728
#define CG_UPNP_STATUS_INVALID_MAC_ADDR 729
#define CG_UPNP_STATUS_INVALID_DATA_TRANS_RATE 730
#define CG_UPNP_STATUS_INVALID_WEP_KEY 731
#define CG_UPNP_STATUS_NO_WEP_KEY_SET 732
#define CG_UPNP_STATUS_NO_PSK_KEY_SET 733
#define CG_UPNP_STATUS_NO_EPA_SERVER 734
#define CG_UPNP_STATUS_SET_MAC_NOT_PERMIT 897
#define CG_UPNP_STATUS_WRITE_ACCESS_DISABLE 898
#define CG_UPNP_STATUS_SESSION_ID_EXPIRE 899
#endif

// DeviceProtection
#define CG_UPNP_CODE_ACTION_NOT_AUTH	606
#define CG_UPNP_CODE_AUTH_FAIL	701


// TR-064 U2 CMS2
#define CG_UPNP_CODE_INVALID_XML_ARGUMENT 702
#define CG_UPNP_CODE_NO_SUCH_NAME 703
#define CG_UPNP_CODE_INVALID_VALUE_TYPE 704
#define CG_UPNP_CODE_INVALID_VALUE 705
#define CG_UPNP_CODE_READ_ONLY_VIOLATION 706
#define CG_UPNP_CODE_MULTIPLE_SET 707
#define CG_UPNP_CODE_RESOURCE_TEMP_UNAVAILABLE 708



/****************************************
 * Data Type
 ****************************************/

/**
 * UPnP status struct used in action and state operations
 */
typedef struct _CgUpnpStatus {
	/** Status code */
	int code;
	int zyFaultCode;

	/** Status description */
	CgString *description;
} CgUpnpStatus;

/******************************************************************************
 * Function
 ******************************************************************************/

/**
 * Create a new status struct
 *
 */
CgUpnpStatus *cg_upnp_status_new();

/**
 * Delete a status struct
 *
 * \param upnpStat Status struct to delete
 */
void cg_upnp_status_delete(CgUpnpStatus *upnpStat);

/**
 * Set status code for status struct
 *
 * \param upnpStat Status struct
 * \param value Status code
 */
#define cg_upnp_status_setcode(upnpStat, value) (upnpStat->code = value)

/**
 * Follow the status code then set Zy status fault code in zupnp for status struct
 *
 * \param upnpStat Status struct
 * \param value Status code
 */
#define cg_upnp_status_setzyfaultcode(upnpStat, value) (upnpStat->zyFaultCode = value)

/**
 * Get Status code from a status struct
 *
 * \param upnpStat Status structure
 */
#define cg_upnp_status_getcode(upnpStat) (upnpStat->code)

/**
 * Set status description for a status struct
 *
 * \param upnpStat Status struct
 * \param value Status description
 */
#define cg_upnp_status_setdescription(upnpStat, value) cg_string_setvalue(upnpStat->description, value)

/**
 * Get status description from a status struct
 *
 * \param upnpStat Status struct
 */
#define cg_upnp_status_getdescription(upnpStat) cg_string_getvalue(upnpStat->description)

/**
 * Helper function that converts a status code into a status description
 *
 * \param code Code to convert into a description
 * \return Status description
 */
char *cg_upnp_status_code2string(int code);

#ifdef ZYXEL_CMS2_ENHANCEMENT
char *cg_upnp_cms2_status_code2string(int code);
#else
#define cg_upnp_cms2_status_code2string cg_upnp_status_code2string
#endif

#ifdef  __cplusplus

} /* extern "C" */

#endif

#endif
