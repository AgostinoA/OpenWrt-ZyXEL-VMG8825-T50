/*******************************************************************************
*                                        
* FILE NAME    :icf_defs.h
*                                        
* DESCRIPTION  :The file contains constant values used in APIs to define array
*               sizes, parameter lists etc
*                                        
* Revision History :                
*                
*    DATE            NAME           REFERENCE       REASON
* --------    ------------          ----            ----------
* 8-JUL-2005   Ram Narayan/Shekhar  None            Initial
* 07-Dec-2005  Rohit Aggarwal       ICF Rel 4.0 CDD Added constants for IPSec
*                                           
* 05-Dec-2005	Jyoti Narula		ICF 4.0 	Constants for request_type member of REGISTER_CFM/IND 
*
* 08-Dec-2005	Jyoti Narula		ICF 4.0 	Constants for AUTO_REGISTER
* 13-Jan-2006	Aman Arora			ICF 4.1 	Remved IPSEC feature flags from
* 												wrapper and port files
* 02-Feb-2006  Amit Sharma                      CFG merged with ICF 2.0
* 08-Feb-2006  Amit Sharma               Network PDU Logging API from ICF
* 08-Feb-2006	Puneet Sharma		ICF 4.3		Media manager API id added for 4.3 
* 22-Feb-2005  Amit Sharma                      Added code for auth support
* 30-Mar-2006	Anuradha Gupta		ICF 5.0		Call Modify Feature changes
* 07-Aug-2006  Amit Sharma                      Added call forwarded ind
* 03-Jan-2007  Amit Mahajan                     INFO confirmation changes.
* 15-Jan-2007  Abhishek Dhammawat   ICF 6.3     Addition for Per Line Features 
* 19-Jan-2007  Umang Singh                      Removal of unsupported call hold options
* 26-Mar-2007  Deepti Goyal         ICF 6.4     New API for media connect request.
* 09-Jul-2007  Anuradha Gupta       ICF 7.0 CDD added new APIs for 7.0 
* 16-Jan-2008  Neha Gupta	    SPR 18033	Added support for function
*						failure simulation for UT.
* 16-Jan-2008   Amit Sharma         ICF 8.0 LLD Enhancements for Rel8.0
* 24-Jan-2008   Kamini Gangwani     Rel 8.0     Flag to support NON_IMS_CLIENT defined here
*                                               removed from icf_feature_flags.h 
* 06-MAR-2008   Vipul varshney      SPR 18122   New API for AKA AUTH RESP and new request type in register cfm/ind
* 28-Mar-2008  Sumant Gupta         ICF 8.0    Merging of Publish & Message
* 16-Jun-2008   Tarun Gupta         SPR 18585   Added constants for session refresher method
* 18-Jun-2008   Anurag Khare        SPR 18684   Added error cause for Stop fax and 
*                                               and Warning Header constants
* 05-Jul-2008   Amit Sharma         SPR 18714   Defined new display ID
* 12-Nov-2008   Tarun Gupta         SPR 19189   Merged Rel 7.1.2 SPR 18872
* 08-Dec-2008   Rajiv Kumar         SPR 19218   Merged CSR 1-6431768
* 09-Dec-2008   Ashutosh Mohan      SPR 19218   Merged CSR 1-6239428
* 10-Dec-2008   Tarun Gupta         SPR 19218   Merged CSR 1-6457307
* 30-Jan-2009   Rajiv Kumar         IPTK Rel8.1 Changes done for testing UATK
*                                               API under ICF_UT_TEST flag
* 06-Feb-2009   Tarun Gupta         Rel 8.1 LLD SDP Tunnelling Enhancements
* 03-Mar-2009   Anurag Khare        Rel 8.1     OPTIONS Enhancements
* 13-Mar-2009   Rajiv Kumar         IPTK Rel8.1 Merging CSR-1-6452321
* 30-Mar-2009 Abhishek Dhammawat    Rel 8.2     REFER/NOTIFY enhancements
* 30-Mar-2009  Anurag Khare         Rel 8.2     Prack Enhancements changes
* 02-Apr-2009   Tarun Gupta         Rel 8.2     REFER/NOTIFY Enhancements
* 18-May-2009  Anuradha Gupta    SPR 19672     CSR 1-6347417 merging
* 26-May-2009  Ashutosh Mohan    SPR 19672     Modified icf_display_data_st
* 27-May-2009  Anuradha Gupta    SPR 19672     CSR 1-7009929 merging
* 31-May-2009   Preksha             Rel 8.2     Asynchronus Message Enhancements
* 14-Jun-2009 Abhishek Dhammawat SPR 19590    Modified
*                                             ICF_MAX_API_PAYLOAD_LENGTH
* 19-Jun-2009  Anuradha Gupta    SPR 19746    Modified RETRY_AFTER_DURATION to 10
* 03-Sep-2009 Abhishek Dhammawat SPR 20016    Modified
*                                             ICF_MAX_API_PAYLOAD_LENGTH
* 29-May-2010  Alok Tiwari       SPR 20412    Merged CSR 1-8196703
* 05-Oct-2018  Aashay Chaturvedi CSR00148564  Created a macro for SIP_REGISTER retries
*
* Copyright 2009, Aricent.
*******************************************************************************/







#ifndef __ICF_DEFS_H__

#define __ICF_DEFS_H__






/* Prevent Name Mangling By C++ Compilers */



#ifdef __cplusplus



extern "C"

{

#endif /* __cplusplus */


#include "icf_feature_flags.h"
#include "icf_mm_defs.h"

/*ZyXEL Portiong for re-design*/
#include "switch.h"





/*

--------------------- API ID's ---------------------------

*/





#define ICF_API_ID_INVALID                        0

   /* Invalid call id */
#define ICF_INVALID_CALL_ID          0xffff   


#define ICF_API_BASE                            1
#define ICF_EXTERNAL_API_START					ICF_API_BASE

#define ICF_APP_SETUP_API_BASE                  ICF_EXTERNAL_API_START

#define ICF_APP_ADD_REQ                         ICF_APP_SETUP_API_BASE 

#define ICF_APP_ADD_CFM                         ICF_APP_SETUP_API_BASE + 1

#define ICF_APP_REMOVE_REQ                      ICF_APP_SETUP_API_BASE + 2

#define ICF_APP_REMOVE_CFM                      ICF_APP_SETUP_API_BASE + 3

#define ICF_RES_UNAVAIL_IND			            ICF_APP_SETUP_API_BASE + 4

#define ICF_APP_SETUP_API_END                   ICF_APP_SETUP_API_BASE +4


#define ICF_NETWORK_API_BASE                    ICF_APP_SETUP_API_END + 1

#ifdef ICF_NW_ACTIVATE
#define ICF_NETWORK_ACTIVATE_REQ                ICF_NETWORK_API_BASE

#define ICF_NETWORK_ACTIVATE_CFM                ICF_NETWORK_API_BASE + 1

#define ICF_NETWORK_DEACTIVATE_REQ              ICF_NETWORK_API_BASE + 2

#define ICF_NETWORK_DEACTIVATE_CFM              ICF_NETWORK_API_BASE + 3

#define ICF_EVENT_INDICATION                    ICF_NETWORK_API_BASE + 4
#endif
#define ICF_NETWORK_API_END                     ICF_NETWORK_API_BASE + 4

/*********** APIs for MPH ***********/

#define ICF_MPH_API_BASE						ICF_NETWORK_API_END + 1

#define ICF_CREATE_SECURE_CONN_REQ              ICF_MPH_API_BASE

#define ICF_CREATE_SECURE_CONN_RESP             ICF_MPH_API_BASE + 1

#define ICF_CLOSE_SECURE_CONN_REQ				ICF_MPH_API_BASE + 2

#define ICF_CLOSE_SECURE_CONN_RESP              ICF_MPH_API_BASE + 3

#define ICF_SECURE_CONN_STATUS_IND              ICF_MPH_API_BASE + 4

#define ICF_XCAP_CREATE_REPLACE_RES             ICF_MPH_API_BASE + 5

#define ICF_XCAP_DELETE_RES						ICF_MPH_API_BASE + 6

#define ICF_XCAP_FETCH_RES						ICF_MPH_API_BASE + 7

#define ICF_SYNCML_SEND_REQ						ICF_MPH_API_BASE + 8

#define ICF_MGMT_PLANE_API_PROC_FAILURE         ICF_MPH_API_BASE + 9

#define ICF_MGMT_PLANE_NW_RESP                  ICF_MPH_API_BASE + 10

#define ICF_MPH_API_END							ICF_MPH_API_BASE + 10

/********** APIs for MPH **********/

#define ICF_CFG_API_BASE                        ICF_MPH_API_END + 1

#define ICF_SET_TRANSPORT_REQ                   ICF_CFG_API_BASE

#define ICF_SET_CALL_PARAM_REQ                  ICF_CFG_API_BASE + 1

#define ICF_SET_SELF_ID_REQ                     ICF_CFG_API_BASE + 2

#define ICF_SET_REGISTRATION_REQ                ICF_CFG_API_BASE + 3

#define ICF_CONFIGURE_CFM                       ICF_CFG_API_BASE + 4

#define ICF_CFG_STATUS_API_START                ICF_CFG_API_BASE + 5     
#define ICF_GET_SYSTEM_SETTINGS_REQ             ICF_CFG_API_BASE + 5    

#define ICF_GET_LINE_SETTINGS_REQ               ICF_CFG_API_BASE + 6    

#define ICF_GET_SYSTEM_SETTINGS_RESP            ICF_CFG_API_BASE + 7    
    
#define ICF_GET_LINE_SETTINGS_RESP              ICF_CFG_API_BASE + 8    
#define ICF_CFG_STATUS_API_END                  ICF_CFG_API_BASE + 9    
#define ICF_SET_SCALE_PARAMS_REQ                ICF_CFG_API_BASE + 10
#define ICF_SET_SERVICE_PARAMS_REQ              ICF_CFG_API_BASE + 11
#define ICF_SET_MGMT_PLANE_AUTH_PARAM           ICF_CFG_API_BASE + 12
#define ICF_SET_LINE_PARAM_REQ   		        ICF_CFG_API_BASE + 13
#define ICF_GET_REGISTER_STATUS_REQ             ICF_CFG_API_BASE + 14
#define ICF_GET_REGISTER_STATUS_RESP            ICF_CFG_API_BASE + 15
#define ICF_CFG_API_END                         ICF_CFG_API_BASE + 15
 
/*Start: Added for Per Line Feature */
/* Values For typedef icf_uint8_t icf_refresher_type_t */
#define ICF_SESSION_REFRESHER_NONE              0
#define ICF_SESSION_REFRESHER_UAC               1
#define ICF_SESSION_REFRESHER_UAS               2
/* End: Added for Per Line Feature */

#define ICF_CONTROL_PLANE_API_BASE              ICF_CFG_API_END + 1

#define ICF_REGISTER_REQ                        ICF_CONTROL_PLANE_API_BASE 

#define ICF_REGISTER_CFM                        ICF_CONTROL_PLANE_API_BASE + 1

#define ICF_REGISTER_STATUS_IND                 ICF_CONTROL_PLANE_API_BASE + 2

#define ICF_CREATE_CALL_REQ                     ICF_CONTROL_PLANE_API_BASE + 3

#define ICF_LOCAL_USER_ALERTED_REQ              ICF_CONTROL_PLANE_API_BASE + 4

#define ICF_TERMINATE_CALL_REQ                  ICF_CONTROL_PLANE_API_BASE + 5

#define ICF_LOCAL_USER_TERMINATE_CALL_RESP      ICF_CONTROL_PLANE_API_BASE + 6

#define ICF_CONNECT_REQ                         ICF_CONTROL_PLANE_API_BASE + 7

#define ICF_SUBSCRIBE_REQ                       ICF_CONTROL_PLANE_API_BASE + 8

#define ICF_PUBLISH_REQ                         ICF_CONTROL_PLANE_API_BASE + 9

#define ICF_MESSAGE_REQ                         ICF_CONTROL_PLANE_API_BASE + 10

#define ICF_OPTIONS_REQ            				ICF_CONTROL_PLANE_API_BASE + 11

#define ICF_REFER_REQ                           ICF_CONTROL_PLANE_API_BASE + 12


#define ICF_INCOMING_CALL_IND                   ICF_CONTROL_PLANE_API_BASE + 13

#define ICF_REMOTE_USER_ALERTED_IND             ICF_CONTROL_PLANE_API_BASE + 14

#define ICF_TERMINATE_CALL_IND                  ICF_CONTROL_PLANE_API_BASE + 15

#define ICF_REMOTE_USER_TERMINATE_CALL_RESP     ICF_CONTROL_PLANE_API_BASE + 16

#define ICF_MEDIA_CONNECTED_IND                 ICF_CONTROL_PLANE_API_BASE + 17

#define ICF_CONNECT_IND                         ICF_CONTROL_PLANE_API_BASE + 18

/*ICF_HANDLE_REINVITE_START*/

#define ICF_INCOMING_CALL_MODIFY_IND			ICF_CONTROL_PLANE_API_BASE + 19

#define ICF_CALL_MODIFY_CFM						ICF_CONTROL_PLANE_API_BASE + 20

#define ICF_INCOMING_CALL_MODIFY_CANCEL_IND		ICF_CONTROL_PLANE_API_BASE + 21

#define ICF_CALL_MODIFY_REQ						ICF_CONTROL_PLANE_API_BASE + 22

#define ICF_CALL_MODIFY_RESP					ICF_CONTROL_PLANE_API_BASE + 23

/*ICF_HANDLE_REINVITE_END*/

#define ICF_SUBSCRIPTION_STATUS_IND             ICF_CONTROL_PLANE_API_BASE + 24

#define ICF_NOTIFY_IND                          ICF_CONTROL_PLANE_API_BASE + 25

#define ICF_PUBLISH_RESP                        ICF_CONTROL_PLANE_API_BASE + 26

#define ICF_MESSAGE_RESP                        ICF_CONTROL_PLANE_API_BASE + 27

#define ICF_OPTIONS_RESP           				ICF_CONTROL_PLANE_API_BASE + 28

#define ICF_MESSAGE_IND                         ICF_CONTROL_PLANE_API_BASE + 29

#define ICF_INC_OPTIONS_IND          			ICF_CONTROL_PLANE_API_BASE + 30

#define ICF_REFER_RESP                          ICF_CONTROL_PLANE_API_BASE + 31

#define ICF_CALL_HOLD_RESP                      ICF_CONTROL_PLANE_API_BASE + 32

#define ICF_CALL_RESUME_RESP              ICF_CONTROL_PLANE_API_BASE + 33

#define ICF_CALL_TRANSFER_ATTENDED_RESP   ICF_CONTROL_PLANE_API_BASE + 34

#define ICF_CALL_TRANSFER_UNATTENDED_RESP   ICF_CONTROL_PLANE_API_BASE + 35

#define ICF_REMOTE_CALL_TRANSFER_INITIATED_IND   ICF_CONTROL_PLANE_API_BASE + 36

#define ICF_CALL_MERGED_IND               ICF_CONTROL_PLANE_API_BASE + 37

#define ICF_CONFERENCE_RESP               ICF_CONTROL_PLANE_API_BASE + 38

#define ICF_INFO_RESP						ICF_CONTROL_PLANE_API_BASE + 39

#define ICF_INFO_REQ                   ICF_CONTROL_PLANE_API_BASE + 40

#define ICF_CONNECT_RESP				ICF_CONTROL_PLANE_API_BASE +41

#define ICF_DISPLAY_IND			 ICF_CONTROL_PLANE_API_BASE + 42

/* This is a utility API that can be used by Phone Application to request 
 * SIP Packet Phone Signaling Toolkit to send data for all the calls 
 * received, dialed and missed. */

#define ICF_GET_CALL_LOG_REQ              ICF_CONTROL_PLANE_API_BASE + 43

#define ICF_CALL_MUTE_REQ                 ICF_CONTROL_PLANE_API_BASE + 44
#define ICF_CALL_UNMUTE_REQ               ICF_CONTROL_PLANE_API_BASE + 45
#define ICF_CALL_HOLD_REQ                 ICF_CONTROL_PLANE_API_BASE + 46
#define ICF_CALL_TRANSFER_ATTENDED_REQ    ICF_CONTROL_PLANE_API_BASE + 47
#define ICF_CALL_RESUME_REQ               ICF_CONTROL_PLANE_API_BASE + 48
#define ICF_CONFERENCE_REQ                ICF_CONTROL_PLANE_API_BASE + 49
#define ICF_CALL_TRANSFER_UNATTENDED_REQ  ICF_CONTROL_PLANE_API_BASE + 50
#define ICF_CALL_REDIRECTION_IND          ICF_CONTROL_PLANE_API_BASE + 51
#define ICF_CALL_HOLD_IND                 ICF_CONTROL_PLANE_API_BASE + 52
#define ICF_CALL_RESUME_IND               ICF_CONTROL_PLANE_API_BASE + 53

#define ICF_CALL_LOG_RESP                 ICF_CONTROL_PLANE_API_BASE + 54
#define ICF_PARTY_REPLACED_IND            ICF_CONTROL_PLANE_API_BASE + 55

#define ICF_START_FAX_REQ				  ICF_CONTROL_PLANE_API_BASE + 56
#define ICF_START_FAX_RESP                ICF_CONTROL_PLANE_API_BASE + 57
#define ICF_START_FAX_IND                 ICF_CONTROL_PLANE_API_BASE + 58

#define ICF_NOTIFY_CFM					  ICF_CONTROL_PLANE_API_BASE + 59
#define ICF_OPTIONS_CFM        		  	  ICF_CONTROL_PLANE_API_BASE + 60
#define ICF_INFO_IND					  ICF_CONTROL_PLANE_API_BASE + 61
#define ICF_CALL_FORWARDED_IND            ICF_CONTROL_PLANE_API_BASE + 62

#define ICF_INFO_CFM                      ICF_CONTROL_PLANE_API_BASE + 63 

/* for early call indication */
#define ICF_EARLY_INC_CALL_IND				ICF_CONTROL_PLANE_API_BASE + 64
#define ICF_EARLY_INC_CALL_CFM				ICF_CONTROL_PLANE_API_BASE + 65
#define ICF_MEDIA_CONNECT_REQ              ICF_CONTROL_PLANE_API_BASE + 66 
#define ICF_STOP_FAX_REQ              	ICF_CONTROL_PLANE_API_BASE + 67 
#define ICF_STOP_FAX_RESP              ICF_CONTROL_PLANE_API_BASE + 68 
#define ICF_STOP_FAX_IND              ICF_CONTROL_PLANE_API_BASE + 69 
#define ICF_UNEXPECTED_MSG_IND            ICF_CONTROL_PLANE_API_BASE + 70 
#define ICF_REMOTE_CALL_TRANSFER_INITIATED_CFM  ICF_CONTROL_PLANE_API_BASE + 71

/* following APIs for cancellaion of call modify / reinvite */
#define ICF_CALL_MODIFY_CANCEL_REQ        ICF_CONTROL_PLANE_API_BASE + 72
#define ICF_CALL_MODIFY_CANCEL_RESP       ICF_CONTROL_PLANE_API_BASE + 73

/* following APIs are for XCONF handling */
#define ICF_CREATE_XCONF_REQ              ICF_CONTROL_PLANE_API_BASE + 74
#define ICF_ADD_XCONF_PARTY_REQ           ICF_CONTROL_PLANE_API_BASE + 75
#define ICF_DELETE_XCONF_PARTY_REQ        ICF_CONTROL_PLANE_API_BASE + 76
#define ICF_RELEASE_XCONF_REQ             ICF_CONTROL_PLANE_API_BASE + 77
#define ICF_RELEASE_XCONF_IND             ICF_CONTROL_PLANE_API_BASE + 78
#define ICF_CREATE_XCONF_RESP             ICF_CONTROL_PLANE_API_BASE + 79
#define ICF_ADD_XCONF_PARTY_RESP          ICF_CONTROL_PLANE_API_BASE + 80
#define ICF_DELETE_XCONF_PARTY_RESP       ICF_CONTROL_PLANE_API_BASE + 81
#define ICF_RELEASE_XCONF_RESP             ICF_CONTROL_PLANE_API_BASE + 82 

/* API from IP Tk to App on receiving provisional response without SDP, 
 * indicating that the call is in progress (incoming 181/182/183 without sdp)
 */
#define ICF_PROGRESS_IND                  ICF_CONTROL_PLANE_API_BASE + 83
#define ICF_UT_SIMULATE                   ICF_CONTROL_PLANE_API_BASE + 84
#define ICF_AKA_AUTH_RESP                 ICF_CONTROL_PLANE_API_BASE + 85
#define ICF_UATK_API_TEST                 ICF_CONTROL_PLANE_API_BASE + 86
/*  This is the new API that will be used by IPTK to send the remote 
    Capabilities (SDP) received in 200 OK of OPTIONS. 
*/
#define ICF_TUNNELLED_OPTIONS_RESP        ICF_CONTROL_PLANE_API_BASE + 87

/*  This is the new API that will be send to application when new incoming 
    out of call OPTIONS received.
*/
#define ICF_EARLY_SESSION_IND             ICF_CONTROL_PLANE_API_BASE + 88

/*  This is the new API that will be received from application as response 
    Of ICF_EARLY_SESSION_IND.
*/
#define ICF_EARLY_SESSION_CFM             ICF_CONTROL_PLANE_API_BASE + 89

/* This is the new API that will be received from application to toggle the
 * session timer functionality in IPTK
 */
#define ICF_SESSION_TIMER_TOGGLE_REQ      ICF_CONTROL_PLANE_API_BASE + 90   

/* This is the new API that will be send to application in response to API
 * ICF_SESSION_TIMER_TOGGLE_REQ
 */
#define ICF_SESSION_TIMER_TOGGLE_RESP     ICF_CONTROL_PLANE_API_BASE + 91  
/* The following 4 are new APIs that will be used to send/receive generic
   messages (requests and responses) from the application and the peer.
*/   
#define ICF_GENERIC_MSG_REQ               ICF_CONTROL_PLANE_API_BASE + 92    
#define ICF_GENERIC_MSG_RESP              ICF_CONTROL_PLANE_API_BASE + 93    
#define ICF_GENERIC_MSG_IND               ICF_CONTROL_PLANE_API_BASE + 94    
#define ICF_GENERIC_MSG_CFM               ICF_CONTROL_PLANE_API_BASE + 95    
/*  New APIs for PRACK enhancements */
#define ICF_PRACK_REQ_RECV_IND           ICF_CONTROL_PLANE_API_BASE + 96
#define ICF_PRACK_RESP_SENT_IND          ICF_CONTROL_PLANE_API_BASE + 97
#define ICF_PRACK_REQ_SENT_IND           ICF_CONTROL_PLANE_API_BASE + 98
#define ICF_PRACK_RESP_RECV_IND          ICF_CONTROL_PLANE_API_BASE + 99

/*  New APIs for ASYNCHRONUS_MESSAGE enhancements */
#define ICF_MESSAGE_CFM                       ICF_CONTROL_PLANE_API_BASE + 100
#define ICF_CONTROL_PLANE_API_END         ICF_CONTROL_PLANE_API_BASE + 101

#define ICF_SM_API_START                  ICF_CONTROL_PLANE_API_END + 1
/* This API is sent by Configuration module to clear all the ongoing 
 * calls and deallocate all the call-related buffers, anytime after the 
 * initial configuration is complete. However the configuration will be
 * retained and phone will not be deregistered. */

#define ICF_RESTART_REQ                ICF_SM_API_START + 1

/* This API is used to delete the previous configuration of the SIP Packet
 * Phone Signaling Toolkit and bring it to idle state. All the ongoing calls
 * would be cleared, buffers for calls would be deallocated and SIP Packet 
 * Phone signaling Toolkit would deregister from Registrar. */

/*#define ICF_DELETE_CONFIG_PARAMS_REQ   ICF_SM_API_START + 2*/
#define ICF_REINITIALISE_REQ             ICF_SM_API_START + 2


/* This API is sent by system administration module to enable or disable 
 * the reporting of traces of a specific level or type, during system 
 * runtime. There is no response for this message. */

#define ICF_SET_TRACE_LEVEL_REQ        ICF_SM_API_START + 3

/* This API is sent by SIP Packet Phone Signaling Toolkit to report a 
 * trace of given level and type.  */

#define ICF_REPORT_TRACE_IND           ICF_SM_API_START + 4

/* This API is sent by system administration module to enable or disable 
 * the reporting of errors of a specific level or type, during system 
 * runtime. There is no response for this message. */

#define ICF_SET_ERROR_REPORT_LEVEL_REQ ICF_SM_API_START + 5

/* This API is sent by SIP Packet Phone Signaling Toolkit to report an 
 * error of given level and type.  */

#define ICF_REPORT_ERROR_IND           ICF_SM_API_START + 6

/* This API is sent by system administration module to enable or disable 
 * the updation of a specific stats or stats group. It also specifies whether 
 * the current stats values in the counters needs to be resetor not. There 
 * is no response for this message. */

#define ICF_SET_STATS_REQ              ICF_SM_API_START + 7

/* This API is sent by system administration module to get the current value 
 * of a specific stats or stats group. It also specifies whether the current
 * stats values in the counters needs to be reset or not. The response to 
 * this API contains the stats value. */

#define ICF_GET_ICF_STATS_REQ               ICF_SM_API_START + 8

/* The API contains the response for ICF_GET_STATS_REQ to 
 * indicate the current value of the requested stats. */

#define ICF_GET_ICF_STATS_RESP             ICF_SM_API_START + 9

/* This API is sent by the Syatem Manager to check the health of the 
 * SIP Packet Phone Signaling Toolkit at regular intervals. */

#define ICF_CHECK_MODULE_STATUS_REQ  ICF_SM_API_START + 10

/* This API is sent in response tp ICF_CHECK_MODULE_STATUS_REQ to
 * indicate that SIP Packet Phone Signaling Toolkit is alive. */

#define ICF_CHECK_MODULE_STATUS_RESP  ICF_SM_API_START + 11
    /* Send Restart response to application */
#define ICF_RESTART_RESP              ICF_SM_API_START + 12
    /*Send Restart indication to applications other then one which
     * sent restart request */
#define ICF_RESTART_IND               ICF_SM_API_START + 13
    /* Send Reinitialise response to application */
#define ICF_REINIT_RESP               ICF_SM_API_START + 14
    /*Send Reinitialise indication to applications other then one which
     * sent reinitialise request */
#define ICF_REINIT_IND                ICF_SM_API_START + 15

     /* Application will send this API to request System Manager to send
      * the current stats value.*/
#define ICF_STATS_REQ         ICF_SM_API_START + 16


     /* This API is sent in response to ICF_GET_STATS_REQ by System Manager
       * to application.*/

#define ICF_STATS_RESP        ICF_SM_API_START + 17

/* This API is sent by system administration module to enable or disable
 * the reporting of traces of a specific level or type, during system
 * runtime. There is no response for this message. */

#define ICF_SET_TRACE_REQ        ICF_SM_API_START + 18

/* This API is sent by IPTK to App whenever the DNS FQDN-IP mapping stored in 
 * the internal buffer changes. This can happen when a new DNS query is done or
 * entry is deleted due to purge timer expiry or txn timeout.
 */
#define ICF_DNS_MAPPING_CHANGE_IND            ICF_SM_API_START + 19

#define ICF_SM_API_END          ICF_SM_API_START + 20

/****************************************************************************
  These API's are used for ICF Testing. Not to be used by external apps.
  **************************************************************************/

#define ICF_TIMER_MSG                                           ICF_SM_API_END + 1
#define ICF_NW_API_MSG_FROM_PEER	ICF_TIMER_MSG + 1
#define ICF_NW_API_OPEN_CONN_IND	ICF_TIMER_MSG + 2
#define ICF_NW_API_CONNECT_SUCCESS	ICF_TIMER_MSG + 3
#define ICF_NW_API_CONNECT_FAILURE	ICF_TIMER_MSG + 4
#define ICF_NW_API_CLOSE_CONN_IND	ICF_TIMER_MSG + 5

#define ICF_MISC_API_START						(ICF_NW_API_CLOSE_CONN_IND + 2000)

#if (defined(ICF_DEBUG_MEMPOOL) || defined (ICF_GL_MM_DEBUG))
#define ICF_MEM_POOL_STATS_PRINT				ICF_MISC_API_START 
#endif
/* These API will only be used for SI testing purposes on windows. 
 * ICF will send these API's towards IAS which will be simulating 
 * GPRS network.
 */

#ifdef ICF_NW_ACTIVATE
#define ICF_GPRS_PRI_PDP_ACTIVATE_REQ			ICF_MISC_API_START + 1
#define ICF_GPRS_PRI_PDP_ACTIVATE_RESP			ICF_MISC_API_START + 12
#define ICF_GPRS_SEC_PDP_ACTIVATE_REQ			ICF_MISC_API_START + 13
#define ICF_GPRS_SEC_PDP_ACTIVATE_RESP			ICF_MISC_API_START + 14
#define ICF_GPRS_PDP_DEACTIVATE_REQ				ICF_MISC_API_START + 15
#define ICF_GPRS_PDP_DEACTIVATE_RESP			ICF_MISC_API_START + 16
#define ICF_GPRS_PDP_MODIFY_IND					ICF_MISC_API_START + 17
#define ICF_GPRS_PDP_DEACTIVATE_IND				ICF_MISC_API_START + 18
#define ICF_GPRS_PLATFORM_EVENT_IND				ICF_MISC_API_START + 19
#endif

#define ICF_MSG_FRM_PLTFM						ICF_MISC_API_START + 20

#define ICF_PORT_PLTFM_API_START				ICF_MSG_FRM_PLTFM						
	
/* -------------------------------------------------------------------------- */
/* API IDs for IPSec */
/* -------------------------------------------------------------------------- */
/* start range for IPSec APIs */
#define ICF_PORT_PLTFM_IPSEC_START			  (ICF_PORT_PLTFM_API_START + 1)
/* SA create request to Wrapper */
#define ICF_PORT_PLTFM_SA_CREATE_REQ          (ICF_PORT_PLTFM_IPSEC_START+1 )
/* SA create response from Wrapper */
#define ICF_PORT_PLTFM_SA_CREATE_RESP         (ICF_PORT_PLTFM_SA_CREATE_REQ + 1)
/* SA modify request to Wrapper */
#define ICF_PORT_PLTFM_SA_MODIFY_REQ          (ICF_PORT_PLTFM_SA_CREATE_RESP + 1)
/* SA modify response from Wrapper */
#define ICF_PORT_PLTFM_SA_MODIFY_RESP         (ICF_PORT_PLTFM_SA_MODIFY_REQ + 1)
/* SA delete request to Wrapper */
#define ICF_PORT_PLTFM_SA_DELETE_REQ          (ICF_PORT_PLTFM_SA_MODIFY_RESP + 1)
/* SA delete response from Wrapper */
#define ICF_PORT_PLTFM_SA_DELETE_RESP         (ICF_PORT_PLTFM_SA_DELETE_REQ + 1)
/* SA expiry indication from Wrapper */
#define ICF_PORT_PLTFM_SA_EXPIRY_IND          (ICF_PORT_PLTFM_SA_DELETE_RESP + 1)
/* Fetch locally supported security Encryption algorithms */
#define ICF_PORT_PLTFM_SA_FETCH_ENC_ALGO_REQ  (ICF_PORT_PLTFM_SA_EXPIRY_IND + 1)
#define ICF_PORT_PLTFM_SA_FETCH_ENC_ALGO_RESP  (ICF_PORT_PLTFM_SA_FETCH_ENC_ALGO_REQ + 1)
/* Fetch locally supported security Authentication algorithms */
#define ICF_PORT_PLTFM_SA_FETCH_AUTH_ALGO_REQ  (ICF_PORT_PLTFM_SA_FETCH_ENC_ALGO_RESP + 1)
#define ICF_PORT_PLTFM_SA_FETCH_AUTH_ALGO_RESP  (ICF_PORT_PLTFM_SA_FETCH_AUTH_ALGO_REQ + 1)
/* end range for IPSec APIs */
#define ICF_PORT_PLTFM_IPSEC_END				(ICF_PORT_PLTFM_SA_FETCH_AUTH_ALGO_RESP)

/* -------------------------------------------------------------------------- */
/* API IDs for PDP context */
/* -------------------------------------------------------------------------- */

#define ICF_PORT_PLTFM_PDP_ACT_START			(ICF_PORT_PLTFM_IPSEC_END + 1)

#define ICF_PORT_PLTFM_PRIM_PDP_ACT_REQ			(ICF_PORT_PLTFM_PDP_ACT_START + 1)
#define ICF_PORT_PLTFM_PRIM_PDP_ACT_RSP			(ICF_PORT_PLTFM_PRIM_PDP_ACT_REQ +1)
#define ICF_PORT_PLTFM_SEC_PDP_ACT_REQ			(ICF_PORT_PLTFM_PRIM_PDP_ACT_RSP + 1)
#define ICF_PORT_PLTFM_SEC_PDP_ACT_RSP			(ICF_PORT_PLTFM_SEC_PDP_ACT_REQ +1)
#define ICF_PORT_PLTFM_PDP_DEACT_REQ			(ICF_PORT_PLTFM_SEC_PDP_ACT_RSP +1)
#define ICF_PORT_PLTFM_PDP_DEACT_RSP			(ICF_PORT_PLTFM_PDP_DEACT_REQ +1)
#define ICF_PORT_PLTFM_PDP_DEACT_IND			(ICF_PORT_PLTFM_PDP_DEACT_RSP +1)
#define ICF_PORT_PLTFM_PDP_MODIFY_IND			(ICF_PORT_PLTFM_PDP_DEACT_IND +1)
/**/
#define ICF_PORT_PLTFM_QOS_RES_REQ				(ICF_PORT_PLTFM_PDP_MODIFY_IND + 1 )
#define ICF_PORT_PLTFM_QOS_REL_REQ				(ICF_PORT_PLTFM_QOS_RES_REQ + 1 )
#define ICF_PORT_PLTFM_QOS_RES_NON_IMS_RESP		(ICF_PORT_PLTFM_QOS_REL_REQ + 1)
#define ICF_PORT_PLTFM_QOS_REL_NON_IMS_RESP		(ICF_PORT_PLTFM_QOS_RES_NON_IMS_RESP + 1)
/**/
#define ICF_PORT_PLTFM_PDP_ACT_END				(ICF_PORT_PLTFM_QOS_REL_NON_IMS_RESP)

/* -------------------------------------------------------------------------- */
/* API IDs for Micellaneous use			 									  */
/* -------------------------------------------------------------------------- */

#define ICF_PORT_PLTFM_MISC_START					(ICF_PORT_PLTFM_PDP_ACT_END + 1)
#define ICF_PORT_PLTFM_GET_DEVICE_PARAMS_REQ		(ICF_PORT_PLTFM_MISC_START + 1)
#define ICF_PORT_PLTFM_GET_DEVICE_PARAMS_RSP		(ICF_PORT_PLTFM_GET_DEVICE_PARAMS_REQ + 1)
#define ICF_PORT_PLTFM_INIT_REQ						(ICF_PORT_PLTFM_GET_DEVICE_PARAMS_RSP + 1)
#define ICF_PORT_PLTFM_INIT_RSP						(ICF_PORT_PLTFM_INIT_REQ + 1)
#define ICF_PORT_PLTFM_DEINIT_REQ					(ICF_PORT_PLTFM_INIT_RSP + 1)
#define ICF_PORT_PLTFM_DEINIT_RSP					(ICF_PORT_PLTFM_DEINIT_REQ + 1)
#define ICF_PORT_PLTFM_GET_ACCESS_NW_INFO_REQ		(ICF_PORT_PLTFM_DEINIT_RSP + 1)
#define ICF_PORT_PLTFM_GET_ACCESS_NW_INFO_RSP		(ICF_PORT_PLTFM_GET_ACCESS_NW_INFO_REQ + 1)
#define ICF_PORT_PLTFM_GET_PCSCF_ADDRESS_REQ		(ICF_PORT_PLTFM_GET_ACCESS_NW_INFO_RSP + 1)
#define ICF_PORT_PLTFM_GET_PCSCF_ADDRESS_RSP		(ICF_PORT_PLTFM_GET_PCSCF_ADDRESS_REQ + 1)
#define ICF_PORT_PLTFM_DNS_SERVICE_REQ				(ICF_PORT_PLTFM_GET_PCSCF_ADDRESS_RSP + 1)
#define ICF_PORT_PLTFM_DNS_SERVICE_RSP				(ICF_PORT_PLTFM_DNS_SERVICE_REQ + 1)
#define ICF_PORT_PLTFM_AKA_CHALLENGE_REQ			(ICF_PORT_PLTFM_DNS_SERVICE_RSP + 1)
#define ICF_PORT_PLTFM_AKA_CHALLENGE_RSP			(ICF_PORT_PLTFM_AKA_CHALLENGE_REQ + 1)
#define ICF_PORT_PLTFM_PLATFORM_EVENT_IND			(ICF_PORT_PLTFM_AKA_CHALLENGE_RSP + 1)
#define ICF_PORT_PLTFM_HOST_TO_IP_REQ				(ICF_PORT_PLTFM_PLATFORM_EVENT_IND + 1)
#define ICF_PORT_PLTFM_HOST_TO_IP_RSP				(ICF_PORT_PLTFM_HOST_TO_IP_REQ + 1)
#define ICF_PORT_PLTFM_MISC_END						(ICF_PORT_PLTFM_HOST_TO_IP_RSP)
	
/* end of api range */
#define ICF_PORT_PLTFM_API_END						(ICF_PORT_PLTFM_MISC_END)

/*API to send PDU trace to application*/
#define ICF_TRACE_NW_BUFF_IND						(ICF_PORT_PLTFM_API_END+1)
/* End of misc APIs */

/* API to send logs to Application */
#define ICF_LOGS_IND		        				(ICF_TRACE_NW_BUFF_IND+1)

#ifdef  ICF_NAT_MEDIA_TRAVERSAL

#define ICF_API_NAT_START                   (ICF_LOGS_IND + 1)
#define ICF_NAT_STUN_INIT_RESP			    ICF_API_NAT_START + 2
#define ICF_NAT_STUN_EXEC_PROC_RESP			ICF_API_NAT_START + 3 
#define ICF_NAT_GET_PUBLIC_IP_PORT_RESP 	ICF_API_NAT_START + 4
#define ICF_NAT_ERROR_IND				    ICF_API_NAT_START + 5
#define ICF_NAT_STUN_PROC_STATUS_IND		ICF_API_NAT_START + 6
#define ICF_NAT_TIMER_EXP_IND               ICF_API_NAT_START + 7
#define ICF_NAT_GET_PUBLIC_IP_PORT_REQ      ICF_API_NAT_START + 8
#define ICF_NAT_STUN_INIT_REQ               ICF_API_NAT_START + 9
#define ICF_NAT_RECV_UDP_DATA_IND           ICF_API_NAT_START + 10
#define ICF_API_NAT_END                     (ICF_API_NAT_START + 8)
#endif

/* End of misc APIs */
#define ICF_MISC_API_END                            (ICF_LOGS_IND+20)

/*Start */

#define ICF_EXTERNAL_API_END						ICF_MISC_API_END
#define ICF_SET_DSCP_BITS				            ICF_EXTERNAL_API_END + 1

/*End */


/*****************************************************************************/

/*

----------------------- COMMON API DEFS ------------------------------

*/



/* Different values for source and destination id's */







#define ICF_MAX_MODULE                                 2


/* Denotes the ICF system. The application should fill this as destination id    */
/* for all API's from App to ICF                                                 */
#define ICF_MODULE_ICF                                 6

/* Generic module id for configuration requests before app_add*/
#define ICF_GENERIC_APP_MODULE_ID                      0xFF

/* Denotes the underlying Platform for ICF                                       */
#define ICF_MODULE_PLATFORM                            10




/* Maximun number of charactersstored in structure icf_string_st */
/* Sdf_co_characterBufferSize defined in sdf_common.h should be
 * equal to ICF_MAX_STR_LEN.
 */
#define ICF_MAX_STR_LEN                            128    

/* Maximun number of characters stored in structure icf_large_string_st.
 * This has been taken as 508 and not 512 so that the block size we 
 * allocate from COMMON pool should be 512 and not 1024 because the next
 * bigger size block which we have in common pool is 1024
*/

#define ICF_MAX_LARGE_STR_LEN						508

/* Deviation in the Header value length allowed to Validate the headers
 * in IPTK. By Default deviation is 0. user can update the deviation as per
 * there requirement.
 * */
#define ICF_DEV_LARGE_STR_LEN						516 //ZyXEL Memo: make the validation on the SIP Header Content Max Length up to 'ICF_MAX_LARGE_STR_LEN(508)' + 516 = 1,024 characters.


/* Maximun number of characters stored in structure icf_req_uri_st */

#define ICF_MAX_REQ_URI_LEN							512

/* Denotes the maximum number of configuration elements present in the 

 * configuration APIs.

 */

#define ICF_MAX_NUM_OF_CONFIG_ELEMENTS            1


/*-----------------------------------------------------------------------------
 ******************************************************************************
 ******************************************************************************
 Supported range of initialization parameters
 ******************************************************************************
 ******************************************************************************
 *---------------------------------------------------------------------------*/

/* Denotes minimum number of applications supported */
#define ICF_MIN_NUM_APPLICATION                     1

/* Denotes maximum number of applications supported */
/*ZyXEL porting*/
#if 0
#define ICF_MAX_NUM_APPLICATION                     64
#else
#define ICF_MAX_NUM_APPLICATION			2
#endif
/*ZyXEL porting end*/

#ifdef ICF_NW_ACTIVATE
/* Denotes maximum number of networks supported */
#define ICF_MAX_NUM_NETWORK                         1
#endif

/* Denotes minimum number of calls supported */
#define ICF_MIN_NUM_CALL                            1

/* Denotes maximum number of calls supported */
/*ZyXEL porting*/
#if 0
#define ICF_MAX_NUM_CALL                            256
#else
#define ICF_MAX_NUM_CALL                            (APPS_ZYIMS_PROFILE_NUM*APPS_ZYIMS_LINE_PER_PROFILE_NUM*2)//ZyXEL  Porting 
#endif
/*ZyXEL porting end*/

/*----------------------------------------------------------------------------- * Macro for Maximum number of SIC Call Contexts. This would be identified
 * by application based on the maximum Numbers of SUbscrition which could be 
 * made by application at a given instance of time.
 *---------------------------------------------------------------------------*/
#define ICF_CMN_SIC_MAX_CALL_CONTEXTS           256


/* Denotes minimum number of uris supported */
#define ICF_MIN_NUM_URI                             1

/* Denotes maximum number of uris supported */
#define ICF_MAX_NUM_URI                             50

/* Denotes minimum number of calls to log supported */
#define ICF_MIN_NUM_OF_CALLS_TO_LOG                 1

/* Denotes maximum number of calls to log supported */
#define ICF_MAX_NUM_OF_CALLS_TO_LOG                 24

/* Maximum number of lines supported */
/*ZyXEL porting*/
#if 0
#define ICF_MAX_NUM_OF_LINES						256
#else
#define ICF_MAX_NUM_OF_LINES						(APPS_ZYIMS_PROFILE_NUM*APPS_ZYIMS_LINE_PER_PROFILE_NUM)//ZyXEL  Porting 
#endif
/*ZyXEL porting end*/

/* Maximum number of registration supported */
/*ZyXEL porting*/
#if 0
#define ICF_MAX_NUM_OF_REGISTRATION 				256
#else
#define ICF_MAX_NUM_OF_REGISTRATION 				(APPS_ZYIMS_PROFILE_NUM*APPS_ZYIMS_LINE_PER_PROFILE_NUM)//ZyXEL  Porting 
#endif
/*ZyXEL porting end*/

#define ICF_MAX_SYS_RESOURCE_LIMIT				    4

#define ICF_MIN_SYS_RESOURCE_LIMIT				    1

/* Default values */
/*ZyXEL porting*/
#if 0
#define ICF_DEFAULT_MAX_LINES                       256
#else
#define ICF_DEFAULT_MAX_LINES                       (APPS_ZYIMS_PROFILE_NUM*APPS_ZYIMS_LINE_PER_PROFILE_NUM)//ZyXEL  Porting 
#endif
/*ZyXEL porting end*/

#define ICF_DEFAULT_MAX_APPLICATIONS                2

/*ZyXEL porting*/
#if 0
#define ICF_DEFAULT_MAX_REGISTRATIONS               256
#else
#define ICF_DEFAULT_MAX_REGISTRATIONS               (APPS_ZYIMS_PROFILE_NUM*APPS_ZYIMS_LINE_PER_PROFILE_NUM)//ZyXEL  Porting 
#endif
/*ZyXEL porting end*/

/*ZyXEL porting*/
#if 0
#define ICF_DEFAULT_MAX_AUDIO_CALLS                       256
#define ICF_DEFAULT_MAX_VIDEO_CALLS                       256
#define ICF_DEFAULT_MAX_SERVICE_CALLS                     256
#else
#define ICF_DEFAULT_MAX_AUDIO_CALLS                       (APPS_ZYIMS_PROFILE_NUM*APPS_ZYIMS_LINE_PER_PROFILE_NUM*2)//ZyXEL  Porting 
#define ICF_DEFAULT_MAX_VIDEO_CALLS                       (APPS_ZYIMS_PROFILE_NUM*APPS_ZYIMS_LINE_PER_PROFILE_NUM*2)//ZyXEL  Porting 
#define ICF_DEFAULT_MAX_SERVICE_CALLS                     (APPS_ZYIMS_PROFILE_NUM*APPS_ZYIMS_LINE_PER_PROFILE_NUM*2)//ZyXEL  Porting 
#endif
/*ZyXEL porting end*/

/*MAX Number of calls per minute per line*/
#define ICF_CALL_RATE_PER_MIN                             1

#ifdef ICF_NW_ACTIVATE
#define ICF_DEFAULT_MAX_NETWORKS                    1
/* Denotes minimum duration for network activate retry timer */
#define ICF_MIN_NET_ACT_RETRY_TIMER_DURATION		1
/* Denotes minimum retry attempts to activate network */
#define ICF_MIN_NET_ACT_RETRY_TIMER_ATTEMPTS		0
#endif

#define ICF_DEFAULT_SYS_RESOURCE_LIMIT              1

#define ICF_DEFAULT_MAX_URIS                        5

#define ICF_DEFAULT_MAX_CALLS_TO_LOG                24

#define ICF_DEFAULT_SIP_PROXY_PORT					5060
	
#define ICF_DEFAULT_SIP_SERVER_PORT					5060

#define ICF_DEFAULT_SIPS_SERVER_PORT				5061

#define ICF_DEFAULT_COMPACT_SIP_HDRS                   0

#ifdef ICF_NW_ACTIVATE
#define ICF_DEFAULT_APN_STR_LEN                     0
#define ICF_DEFAULT_NET_ACT_RETRY_TIMER_DURATION	6000
#define ICF_DEFAULT_NET_ACT_RETRY_TIMER_ATTEMPTS	2
#endif

#define ICF_DEFAULT_SIGCOMP_REQUIRED                1

#define ICF_DEFAULT_AUTH_PASSWD_STR_LEN		    0
/* ICF_4_0_CRM_START*/

#define ICF_MAX_NUM_OF_USERS_PER_LINE           3
/* ICF_4_0_CRM_END*/

/*CSR 5347542 */
#define ICF_ALL_LINES                       65535
/* This is the Invalid line id*/
#define ICF_INVALID_LINE_ID                   0xffff

/*ICF_HANDLE_REINVITE_START*/
#define ICF_CFG_CALL_MODIFY_METHOD_INVITE		0
#define ICF_CFG_CALL_MODIFY_METHOD_UPDATE		1

#define ICF_CFG_SESSION_REFRESH_METHOD_INVITE       0
#define ICF_CFG_SESSION_REFRESH_METHOD_UPDATE       1   

/*ICF_HANDLE_REINVITE_END*/
/*------------------------------------------------------------------------------
 * Constants needed for IPSec Support in ICF Release 4.0
 *----------------------------------------------------------------------------*/

/* This defines the maximum number of integrity algorithms supported by ICF */
#define ICF_MAX_SUPP_I_ALGO                         2

/* This defines the maximum number of encryption algorithms supported by ICF */
#define ICF_MAX_SUPP_E_ALGO                         2

/* This shall be a Boolean value, 0 or 1, indicating whether ICF currently 
 * supports IP Security or not */
#define ICF_DEFAULT_IPSEC_ENABLED                   0

/* This shall be a finite positive number indicating the limit up to which 
 * successive transaction timeouts will be acceptable. In case the number of 
 * consecutive transactions for which no response has been received exceeds this
 * configured value, it shall imply a network failure */
#define ICF_DEFAULT_IPSEC_TXN_THRESHOLD             5

/* This shall be the lower limit of a pre-determined range of port numbers that 
 * will be used as protected server and client ports */
#define ICF_DEFAULT_IPSEC_START_PORT_VAL            18100

/* This shall specify the number of ports that will be used as protected server 
 * and client ports */
#define ICF_DEFAULT_IPSEC_PORT_COUNT               50

/* This shall specify the duration of SA Create Timer in milliseconds */
#define ICF_DEFAULT_IPSEC_SA_CREATE_TIMER           1000

/* This shall specify the duration of SA Modify Timer in milliseconds */
#define ICF_DEFAULT_IPSEC_SA_MODIFY_TIMER           1000

/* This shall specify the duration of SA Delete Timer in milliseconds */
#define ICF_DEFAULT_IPSEC_SA_DELETE_TIMER           1000


/* ------------------ End: Constants for IP Security Support ---------------- */


/* Maximun length of application data in the icf_app_data_st */

#define ICF_MAX_APP_DATA_LEN                  400


/*    This is version of the API. */

#define ICF_VERSION_1_0                            1 





/* Denotes the attributes for a "media" line in SDP */

#define ICF_MAX_ATTRIBUTES_PER_CALL             3





/* Length of the API Header */

#define ICF_API_HEADER_LENGTH      (sizeof(icf_api_header_st))


/* Maximum supported SIP header length */
/* This parameter defines the maximum length of a SIP Header supported by IPTK 
 * and IPTK is tested with the default specified value only. 
 * 
 * 
 * Note::
 * 1. 	This parameter has internal dependencies on other internal parameters 
 *    	like SIP_MAX_HDR_SIZE & should be less than SIP_MAX_MSG_SIZE. Hence, 
 *    	changing this value, requires thorough review/testing. These parameters 
 *		are defined in the following file: 
 *    	ICF/source/stacks/sip_micro_ua/microua_3_0/sip_stack_3_0_src/source/siplib/common/h/microsip_common.h:
 *       #define SIP_MAX_MSG_SIZE (3000)
 *       #define SIP_MAX_HDR_SIZE (1000)
 *    
 *		Tuning requirement: ICF_SSA_MAX_HEADER_VALUE_LEN <= SIP_MAX_HDR_SIZE
 * 
 * 2. 	Changing the default value of this parameter shall also effect the 
 *		functionality when IPTK has to send the correspoding header to 
 *		application (Application has requested the header). The parameter 
 *		ICF_MAX_STR_LEN defines the maximum length of header sent to be sent to 
 *		Application if requested it through header_list of ICF_APP_ADD_REQ.
 *
 *    	The Application can tune ICF_MAX_STR_LEN in the following manner:
 *    	ICF_MAX_STR_LEN < ICF_SSA_MAX_HEADER_VALUE_LEN + 2
 *			- truncated (if it is larger) header is given to App (if requested)
 *		ICF_MAX_STR_LEN = ICF_SSA_MAX_HEADER_VALUE_LEN + 2
 *			- complete header is given to App (if requested)
 * 		ICF_MAX_STR_LEN > ICF_SSA_MAX_HEADER_VALUE_LEN + 2
 *			- complete header is given to App (if requested)
 *
 *    Please note increasing ICF_MAX_STR_LEN shall increase memory requirements.
 */
#define ICF_SIP_MAX_HEADER_VALUE_LEN  1000



/*

 * This is used at Eshell interface while filling the ip address

 * of the source of a received SIP message so that that ICF can further

 * use the IP address

 */
#define ICF_MAX_IPV6_ADDRESS_LENGTH    46
#define ICF_MAX_IPV4_ADDRESS_LENGTH    16



/*----------------------------------------------------------------------------

 * Description: Values for data type  icf_status_t and icf_boolean_t

 *--------------------------------------------------------------------------*/



#define ICF_NULL                0



#define ICF_TRUE                1 

#define ICF_FALSE               0 



    

/*------------------------------------------------------------------------------

 * Description: Values for data type  icf_result_t

 *----------------------------------------------------------------------------*/



#define ICF_SUCCESS              1 

#define ICF_FAILURE              0 



    



/*------------------------------------------------------------------------------

 *

 *  icf_address_type_t values

 *

 *----------------------------------------------------------------------------*/



#define ICF_ADDRESS_PLAN_UNDEFINED                   0 /* Undefined */

#define ICF_ADDRESS_PLAN_NOT_PRESENT                 1 /* Address not present */



/* Address restricted to be presented*/

#define ICF_ADDRESS_PLAN_RESTRICTED_TO_BE_PRESENTED  2 

#define ICF_ADDRESS_PLAN_SIP_URI                     3 /* SIP URI */

#define ICF_ADDRESS_PLAN_E164                        4 /* E.164 */

#define ICF_ADDRESS_PLAN_TEL_URI                     5 /* Telephone URI */

#define ICF_ADDRESS_PLAN_SIPS_URI                     6 /* SIPs URI */


/*----------------------------------------------------------------------------

 *

 *  icf_transport_mode_t These values specifies the mode of

 *   transport as TCP or UDP or both

 *

 *--------------------------------------------------------------------------*/



/* Specifies transport mode is UDP. */

#define ICF_TRANSPORT_TYPE_UDP                                   0    



/* Specifies transport mode is TCP. */

#define ICF_TRANSPORT_TYPE_TCP                                   1    

/* Specifies that transport could be either TCP or UDP. */

#define ICF_TRANSPORT_MODE_BOTH                                   2    

#define ICF_TRANSPORT_TYPE_TLS                                    3    

/*Invalid transport type*/
#define ICF_TRANSPORT_TYPE_INVALID                              127 




/*----------------------------------------------------------------------------

 *

 *  icf_qos_mark_t This data type is used to define a value of type 

 *  icf_uint8_t that indicates the type of service indicator in RTP

 *   payload for the call. 

 *

 *--------------------------------------------------------------------------*/

  

/* This indicate that the quality of service is not to be set in the

 *  RTP payload */ 

#define ICF_QOS_MARK_NONE                0



/*  This is to indicate that the quality of service should be given for 

 *  indicating that it is an audio in the type of service parameter 

 *  of RTP payload*/

#define ICF_QOS_MARK_TOS_AUDIO           1








/*-----------------------------------------------------------------------

 * NAME : icf_interval_type_t

 *        used to define the interval type to report back RTCP stats.

 *-----------------------------------------------------------------------*/



/* Denotes statistics to be reported instantaneously as available. */

#define ICF_INSTANTANEOUS                0 



/* Denotes statistics to be reported when it becomes available from remote end. */

#define ICF_WHEN_RCVD                    1 

/*------------------------------------------------------------------------------
 * 
 * typedef Name: icf_stream_id_t
 *
 * Description: defines the type of media information.
 * 
 *----------------------------------------------------------------------------*/

/* Denotes invalid stream id */
#define ICF_STREAM_ID_INVALID	 0

/* Denotes audio stream id */
#define ICF_AUDIO_STREAM_ID       1 

/* Denotes video stream id */
#define ICF_VIDEO_STREAM_ID       2 

/* Denotes TBCP stream id */
#define ICF_TBCP_STREAM_ID        3 

/* Denotes FAX stream id */
#define ICF_FAX_STREAM_ID         4

/* ICF rel 6.0 Multiple m-lines */
/* Denotes audio call */
#define ICF_CALL_TYPE_AUDIO                 0x01 
/* Denotes video call */
#define ICF_CALL_TYPE_VIDEO					0x02
/* Denotes TBCP call */
#define ICF_CALL_TYPE_TBCP					0x04
/* Denotes T.38 call */
#define ICF_CALL_TYPE_T38		            0x08

#define ICF_CALL_TYPE_DEFAULT               ICF_CALL_TYPE_AUDIO 
/* Denotes invalid call type */
#define ICF_CALL_TYPE_INVALID				0xff


/*-----------------------------------------------------------------------

 * NAME : Values for icf_config_action_t

 *-----------------------------------------------------------------------*/



#define ICF_CONFIG_ACTION_ADD        0       /* Add element */

#define ICF_CONFIG_ACTION_MODIFY     1       /* Modify element */

#define ICF_CONFIG_ACTION_DELETE     2       /* Delete element */







/*-----------------------------------------------------------------------

 * NAME : Values for SIGCOMP options in icf_config_transport_address_st

 *-----------------------------------------------------------------------*/



#define ICF_SIGCOMP_NOT_SUPPORTED       0

#define ICF_SIGCOMP_SUPPORTED           1

#define ICF_SIGCOMP_SUPPORT_UNKNOWN     2







/*----------------------------------------------------------------------------

 *

 *  icf_call_clear_reason_t This data type is used to define a value of type 

 *  icf_uint8_t that indicates the reason for call clear

 *

 *--------------------------------------------------------------------------*/





/* Invalid value */

#define ICF_CALL_CLEAR_REASON_INVALID                     0



/* Sent or received from APP. Specifies an undefined call clear reason. */

#define ICF_CALL_CLEAR_REASON_UNDEFINED                   1



/* Sent to APP. Specifies that BYE is received from the remote user */

#define ICF_CALL_CLEAR_REASON_REMOTE_RELEASED             3



/* Sent to APP. Specifies that CANCEL is received from the remote user in 

 * response to the INVITE sent by local user */

#define ICF_CALL_CLEAR_REASON_REMOTE_REJECTED             4



/* Received from APP. Specifies that the call is cleared by the local user before

 * the call is answered */

#define ICF_CALL_CLEAR_REASON_CALL_ABANDONED              5



/* Sent to APP. Specifies that the call is released because resources are not 

 * available to handle the call.*/

#define ICF_CALL_CLEAR_REASON_RESOURCES_NOT_AVAILABLE     6



/* Sent to APP. Specifies that the SIP proxy or the end user agent is unable to 

 * find the user id specified in to header. ICF use this reason when

 * it receives 300, 301, 404, 410, 480, 485 or 604 response code from network.*/

#define ICF_CALL_CLEAR_REASON_USER_NOT_FOUND              7



/* Sent to APP. Specifies that the INVITE should be sent to correct proxy server.

 * ICF use this reason when it receives 305 response code from network. */

#define ICF_CALL_CLEAR_REASON_CORRECT_PROXY_REQD          8 



/* Sent to APP. Specifies that the payment is required from the user. ICF use

 * this reason when it receives 402 response code from network. */

#define ICF_CALL_CLEAR_REASON_PAYMENT_REQD                9



/* Sent to APP. Specifies that there is no response from remote entity. ICF 

 * use this reason when it receives 408 response code from network. */

#define ICF_CALL_CLEAR_REMOTE_UNREACHABLE                 10



/* Sent to APP. Specifies that an error has happened in network while processing 

 * of this call. ICF use this reason when it receives 380, 400, 413, 414, 

 * 416, 481, 482, 483, 484, 493 and 5xx response code from network. */

#define ICF_CALL_CLEAR_REASON_NW_ERROR                    11



/* Sent to APP. Specifies that the remote user is busy. ICF use this reason 

 * when it receives 486 and 600 response code from network. */

#define ICF_CALL_CLEAR_REMOTE_BUSY                        12



/* Sent to APP. Specifies that the local media parameters sent are not supported 

 * by remote or the remote media parameters received are not supported by local 

 * phone. ICF use this reason when it receives 488 response code from 

 * network or media commit fails at local phone */

#define ICF_CALL_CLEAR_MEDIA_MISMATCH                     13



/* Sent to APP. Specifies that the request message has been rejected by the proxy

 * server. ICF use this reason when it receives 401, 403, 407, 420 and 421 

 * response code from network. */

#define ICF_CALL_CLEAR_REASON_NW_REJECTED                 14



/* Sent to APP. Specifies that the remote or local user has not answered the call

 * before expiry of alerting timer. */

#define ICF_CALL_CLEAR_REASON_NOANSWER                    15



/* Sent to APP. Specifies that some system error has happened in ICF like 

 * memory allocation/deallocation failure, message send failure, timer 

 * start/stop failure etc */

#define ICF_CALL_CLEAR_REASON_SYSTEM_ERROR                16



/* Implies that an empty TBCP stream list was sent by the app for a call 

   that required TBCP support */

#define ICF_CALL_CLEAR_REASON_EMPTY_TBCP_STREAM           17



/* Sent to APP. Specifies that the ICF cannot accept a new call because 

 * number of calls have exceeded calls configured */

#define ICF_CALL_CLEAR_REASON_MAX_CALLS_EXCEEDED          18



/* Sent to APP. Specifies that the system has not yet initialized and hence 

 * cannot handle a new call */

#define ICF_CALL_CLEAR_REASON_SYSTEM_NOT_INITIALIZED      19



/* This is reason code sent by APP when it rejects the incoming call and the user

 * is already busy in other call in some other line or when APP does not want to

 * present the CW call to user and wants to give it a busy treatment */

#define ICF_CALL_CLEAR_REASON_USER_BUSY                   20



/* Implies that a non-empty TBCP stream list was sent by the app for a 

   call that did not support TBCP */

#define ICF_CALL_CLEAR_REASON_CALL_TYPE_MISMATCH          21



/* This is reason code sent to APP when call clear is initiated because there is

 * no proxy address configured for the line and call_thru_proxy is configured */

#define ICF_CALL_CLEAR_REASON_PROXY_ADDRESS_NOT_CONFIGURED 22



/* This is reason code sent to APP specifying that there is no user configured for

 * this line and hence the call cannot be orignated.

 */    

#define ICF_CALL_CLEAR_REASON_SELF_ADDR_NOT_CFGRD_FOR_LINE 24   



/* Indicates that the line corresponding to a given line id is not yet

 * configured */

#define ICF_CALL_CLEAR_REASON_LINE_NOT_CONFIGURED         25


/* Indicates that a user is not registered */

#define ICF_CALL_CLEAR_REASON_USER_NOT_REGISTERED		26


/* Indicates that the first element of stream_list was not tbcp stream */

#define ICF_CALL_CLEAR_REASON_INVALID_TBCP_DATA			27


/* Indicates that the call_type in api was invalid */

#define ICF_CALL_CLEAR_REASON_INVALID_CALL_TYPE			28


/* Indicates that the stream_id or stream_type in api was invalid */

#define ICF_CALL_CLEAR_REASON_INVALID_STREAM			29


#ifdef ICF_SESSION_TIMER
/* Indicates that the session timer has expired */

#define ICF_CALL_CLEAR_REASON_SESSION_TIMER_EXPIRED		30
#endif

#define ICF_CALL_CLEAR_REASON_AUTH_PARAM_NOT_CFGRD      31
#define ICF_CALL_CLEAR_REASON_AUTH_FAILURE              32
#define ICF_CALL_CLEAR_REASON_CALL_FORWARDED			33
#define ICF_CALL_CLEAR_REASON_SERVICE_FAILURE           34
#define ICF_CALL_CLEAR_REASON_CALL_TRANSFERRED			35
#define ICF_CALL_CLEAR_REASON_INCONSISTENT_TRANSPORT_MODE 36
#define ICF_CALL_CLEAR_REASON_ATTEMPT_ON_ALTERNATE_LINE  37
#define ICF_CALL_CLEAR_REASON_GPRS_SUSPENDED            38

/* Indicates that the line is already in use by some other call */

#define ICF_CALL_CLEAR_REASON_LINE_BUSY                 39

/* Indicates that a specific application has rejected the call */
/* This will always result in SIP:480 sent out on the network */

#define ICF_CALL_CLEAR_APP_REJECT                       40

/* Call Clear reson to send 487 on network if the call is not yet
   established */
#define ICF_CALL_CLEAR_REASON_REQUEST_TERMINATED        41
/* Call clear reason to indicate that 200 Ok for Update-Re-Invite not
 * received with SDP , if Update/Re-Invite is send with SDP
*/
#define ICF_CALL_CLEAR_REASON_REMOTE_MEDIA_NOT_RECEIVED    42

/* indicates precondition failure- corresponds to SIP 580*/
#define ICF_CALL_CLEAR_REASON_PRECOND_FAILURE			43

/* if the application attempts a new call after the max licensed calls limit is reached, ICF will
 * use this failure reason to terminate a new call attempt */
#define ICF_CALL_CLEAR_REASON_LICENSE_EXPIRED           44

#define ICF_CALL_CLEAR_REASON_INVALID_SDP_NW            45

/* Call Clear reson to send 487 on network if the call is not yet
   established */
/*SPR 13978 Aman 03-01-07*/
/*when app tries to make a call when server ports are not opened but init complete is done*/
#define ICF_CALL_CLEAR_REASON_OPEN_NW_SERVER_FAILED      46

/* Call Clear reson to send 503 on network if the call is not yet
   established */
#define ICF_CALL_CLEAR_REASON_MEDIA_TRANSPORT_FAILURE    47
#define ICF_CALL_CLEAR_REASON_UNABLE_TO_CREATE_MEDIA     48
/* SPR 17399 : Call Clear reason to send 488, if the Fax addition failure
 * from MM
 */
#define ICF_CALL_CLEAR_REASON_RESOURCES_NOT_AVAILABLE_FOR_T38_FAX   49

/*Call clear reason when public URI is barred*/
#define ICF_CALL_CLEAR_REASON_PUBLIC_URI_BARRED         50
/* 
 *CSR1-5413721 This error code would  be returned on getting a 481 
 *response from remote 
 */
#define ICF_CALL_CLEAR_REASON_CALL_LEG_DELETED_AT_REMOTE   51

/*  spr 17993 Merge */
#define ICF_CALL_CLEAR_REASON_UNSUPPORTED_MEDIA         52

/*Call clear reason when proxy server not responding*/
#define ICF_CALL_CLEAR_REASON_PROXY_SERVER_NOT_RESPONDING  53

/*Call clear reason when DNS server not responding or responding 
 *with failure response*/
#define ICF_CALL_CLEAR_REASON_DNS_SERVER_NOT_RESPONDING    54

/* This change is mentioned in spr 18064 
   but due to dependency it taken for CSR 1-5685130 */
#define ICF_CALL_CLEAR_REASON_AUTH_PARAM_NOT_RCVD       55

#define ICF_CALL_CLEAR_REASON_STOP_FAX_FAILURE          56
/*Call clear reason when DNS server not responding 
 *or responding with failure response*/
#define ICF_CALL_CLEAR_REASON_DNS_QUERY_FAILURE    57

/* Fix for SPR 18884 ------> CSR-1-6239428*/
/* Call clear reason to indicate transaction timeout when message is not received from
 * remote */    
#define ICF_CALL_CLEAR_REASON_NW_TIMEOUT    58
/*  call clear reason to send 420 if 100 rel received in require header of INVITE
 *  and Prack is not supported
 */
#define ICF_CALL_CLEAR_REASON_PRACK_CALL_NOT_ALLOWED    59

/*  call clear reason to send to application 100 rel received in 
 *  require header of INVITE and Prack is not supported
 */
#define ICF_CALL_CLEAR_REASON_NON_PRACK_CALL_NOT_ALLOWED    60
/*   If in ICF_CREATE_CALL_REQ precondition_required is TRUE
 *   and prack_value is ICF_NO_PRACK
 *   then clear the call with this call clear reason
 */
#define ICF_CALL_CLEAR_REASON_PRECONDITION_CALL_NOT_ALLOWED    61

#define ICF_CALL_CLEAR_REASON_END    62

/*----------------------------------------------------------------------------
 *
 *  Following are the values of type icf_uint8_t that indicates 
 *	the reasons for Re-invite error causes
 *
 *--------------------------------------------------------------------------*/
#define ICF_CALL_MODIFY_REASON_START			ICF_CALL_CLEAR_REASON_END + 1

#define ICF_CALL_MODIFY_REASON_USER_BUSY			ICF_CALL_MODIFY_REASON_START + 1
#define ICF_CALL_MODIFY_REASON_REJECT_MEDIA_CHANGE	ICF_CALL_MODIFY_REASON_START + 2
#define ICF_CALL_MODIFY_REASON_REQUEST_TERMINATED	ICF_CALL_MODIFY_REASON_START + 3
#define ICF_CALL_MODIFY_REASON_INVALID_REQUEST      ICF_CALL_MODIFY_REASON_START + 4
#define ICF_CALL_MODIFY_REASON_END					ICF_CALL_MODIFY_REASON_START + 5



/*----------------------------------------------------------------------------
 *
 *  Following are the values of type icf_uint8_t that indicates 
 *	the reasons for fax error
 *
 *--------------------------------------------------------------------------*/
#define ICF_FAX_ERR_REASON_START			ICF_CALL_MODIFY_REASON_END
#define ICF_FAX_ERR_CALL_NOT_ALLOWED		ICF_FAX_ERR_REASON_START + 1
#define ICF_FAX_ERR_INVALID_REQUEST			ICF_FAX_ERR_REASON_START + 2


#ifdef ICF_NW_ACTIVATE

/* This specifies GPRS as an access network type.*/

#define ICF_GPRS    1 

/* Maximum number of network access. */

#define ICF_MAX_NETWORK     3 

/* Maximum number of apns */

#define ICF_MAX_APN     5 

#endif

/* This is the invalid APP ID. */

#define ICF_GENERIC_APP_ID      0
#define ICF_INVALID_APP_ID      0xFFFF	


/* ICF_4_0_CRM_START*/
#define ICF_DUMMY_APP_ID	 0x0FFFE
	
/* ICF_4_0_CRM_END*/
	

/* Indicates call preferences set in ICF_SET_CALL_PARAM_REQ API. */

#define ICF_CALL_CONFIG_CALL_THRU_SIP_PROXY     0x01 



/* Indicates call preferences set in ICF_SET_CALL_PARAM_REQ API. */

/* we are not using this anymore 

  #define ICF_CALL_CONFIG_PRIVACY_HEADER_PRESENT 0x02 */



/* Indicates call preferences set in ICF_SET_CALL_PARAM_REQ API. */

#define ICF_CALL_CONFIG_PRACK_REQD      0x04 





/* Specifies the presentation indication for the outgoingcalls. This is used in 

ICF_SET_SELF_ID_REQ API. */

/*#define ICF_SETTINGS_CONFIG_PRESENTATION_IND    1 */

#define ICF_MAX_MESSAGE_BODY_SIZE     4096



/* This indicates UDP IPC. */

#define ICF_IPC_UDP     0x01 



/* This indicates TCP IPC. */

#define ICF_IPC_TCP     0x02 



/* This indicates Message Queue IPC. */

#define ICF_IPC_MSGQ    0x04 







/* This indicates the ICF shall create TCP server. */

#define ICF_TCP_SERVER 0x01 



/* This indicates the ICF shall create TCP client connection. */

#define ICF_TCP_CLIENT 0x02 

/* ICF_4_0_CRM_START*/
/* These values are being used for request_type member in REGISTER_CFM/IND payload 
 * when the status returned is FAILURE */
	
#define ICF_REQUEST_TYPE_REGISTERING				1
#define ICF_REQUEST_TYPE_AUTHORIZING				2
#define ICF_REQUEST_TYPE_DEREGISTERING				3
#define	ICF_REQUEST_TYPE_DEREGISTER					4
#define ICF_REQUEST_TYPE_REGISTER_ALL_USERS_ON_LINE	5
/* This value will be given to application in the case we receive a 4xx/5xx
 * response to the SUBSCRIBE sent out by IPTK for event package reg
 */
#define ICF_REQUEST_TYPE_REG_EVENT_SUBSCRIBING   	6
#define	ICF_REQUEST_TYPE_AWTING_AUTH_RESP			7

/* ICF_4_0_CRM_END*/


/* ------------------------------------------------------------------------ */
#ifdef ICF_ERROR_ENABLE

/* Maximum number of integer fields present in the icf_error_data_st*/
#define ICF_MAX_INT_ERROR_DATA                4

/* Maximum number of string fields present in the icf_error_data_st */
#define ICF_MAX_STR_ERROR_DATA                2

#endif


#ifdef ICF_TRACE_ENABLE
/* Maximum number of integer fields present in the trace data in the
 * icf_trace_data_st*/
#define ICF_MAX_INT_TRACE_DATA                4

/* Maximum number of string data field present in the trace data in
 * icf_trace_data_st */
#define ICF_MAX_STR_TRACE_DATA                4
#endif
/* Defining ICF_USE_LINE1 */
#define ICF_USE_LINE1			     0


/* ------------------------------------------------------------------------ */
/* Maximun number of characters stored in structure icf_short_string_st */
#define ICF_MAX_SHORT_STR_LEN                  64

/* Maximun number of characters stored in structure icf_long_string_st */
#define ICF_MAX_LONG_STR_LEN                  256


/* ------------------------------------------------------------------------ 
*
* NAME : icf_hold_option_t
*  Description: This data type is used to define a data value of icf_uint8_t
*              type, which identifies the option used by CC to send call hold 
*              indication to remote party.
*		
* ------------------------------------------------------------------------- */

/* Invite with media level c=0 */
#define ICF_CALL_HOLD_OPT_INV_WTH_C_0				1

/* Invite with mode as send only */
#define ICF_CALL_HOLD_OPT_INV_WTH_MODE_SEND_ONLY		2	

/* Update with media level c=0 */
#define ICF_CALL_HOLD_OPT_UPDT_WTH_C_0				3

/* Update with mode as send only */
#define ICF_CALL_HOLD_OPT_UPDT_WTH_MODE_SEND_ONLY		4

/* INVITE with mode=send only and media level c=0 */
#define ICF_CALL_HOLD_OPT_INV_WTH_MODE_SEND_ONLY_N_C_0          5 

/* UPDATE with mode=send only and media level c=0 */
#define ICF_CALL_HOLD_OPT_UPDT_WTH_MODE_SEND_ONLY_N_C_0         6

/*CSR_1-70009929 Fixed: SPR-19506*/

/* Invite with mode as inactive */
#define ICF_CALL_HOLD_OPT_INV_WTH_MODE_INACTIVE        			7

/* Update with mode as inactive */
#define ICF_CALL_HOLD_OPT_UPDT_WTH_MODE_INACTIVE       			8

/* INVITE with mode=send only and session level c=0 */
#define ICF_CALL_HOLD_OPT_INV_WTH_MODE_SEND_ONLY_N_SESSION_C_0      	9

/* UPDATE with mode=send only and session level c=0 */
#define ICF_CALL_HOLD_OPT_UPDT_WTH_MODE_SEND_ONLY_N_SESSION_C_0     	10

/* INVITE with mode=inactive and session level c=0 */
#define ICF_CALL_HOLD_OPT_INV_WTH_MODE_INACTIVE_N_SESSION_C_0      	11

/* UPDATE with mode=inactive and session level c=0 */
#define ICF_CALL_HOLD_OPT_UPDT_WTH_MODE_INACTIVE_N_SESSION_C_0     	12

/*------------------------------------------------------------------------------
 * Description: Values for data type  icf_display_id_t
 *----------------------------------------------------------------------------*/
#define ICF_DISPLAY_UNDEFINED                                                   0
#define ICF_DISPLAY_USER_REGISTERED                                             1
#define ICF_DISPLAY_USER_NOT_REGISTERED                                         2
#define ICF_DISPLAY_USER_DEREGISTERED                                           3
#define ICF_DISPLAY_CALL_MUTE_FAILURE                                           4
#define ICF_DISPLAY_CALL_UNMUTE_FAILURE                                         5
/*ICF_HANDLE_REINVITE_START*/
#define ICF_DISPLAY_INVALID_REQUEST                                             6
/*ICF_HANDLE_REINVITE_END*/
/*Following display ID is sent to application when IPTK could not send SUBSCRIBE
 *request for external conference service*/
#define ICF_DISPLAY_SUBCRIPTION_FAILED_FOR_EXTERNAL_CONFERENCE                  7


/*------------------------------------------------------------------------------
*
* Name :		 icf_display_data_st
*
* Description  : This data type is used to define a structure,
*               which contains display data to be displayed in the API 
*               ICF_DISPLAY_REQ.             
-----------------------------------------------------------------------------*/

#define ICF_MAX_INT_DISPLAY_DATA	4
#define ICF_MAX_STR_DISPLAY_DATA	2

/*----------------------------------------------------------------------------
 *
 *  icf_user_param_t : Used to define a data value of type, 
 *  icf_uint8_t, whose value specifies the values in "user" param in SIP/Tel
 *  URI.
 *
 *--------------------------------------------------------------------------*/

/* Specifies that user=phone should be substitued in the SIP/Tel URI */
#define ICF_USER_PARAM_PHONE   1

#define ICF_MAX_STATS_IN_STATS_GROUP          50

#define ICF_MAX_SUP_PTIME					5

#define ICF_MAX_SUP_CLOCK_RATE              5

#define ICF_MAX_SUP_SAMPLING_RATE            ICF_MAX_SUP_CLOCK_RATE   


/*Duration for which the polling is to be done on sockets*/
#ifndef ICF_PORT_WINCE
#define ICF_SELECT_TIMER                     100
#else
#define ICF_SELECT_TIMER                     1000
#endif

#define ICF_INVALID_AMR_MODE	10

/*Max number of servers opened for listening nw messages*/
#define ICF_MAX_NUM_OF_SERVERS   256

/*Fraction for timer interval to be used for reSubscription Timer */
#define ICF_SUBS_TIMER_INTERVAL_FRACTION		0.50
/* CSR1-5249946 */
#define ICF_NAME_IN_O_LINE    "ICF"


/* CSR1-5285622 */
/*This timer is started when IPTK makes a DNS query.*/
#define ICF_DNS_REQ_TIMEOUT               5000

/* CSR 1-6452321: SPR 19216 */
/* This is the actual duration of system-wide DNS purge timer. This timer 
 * identifies the time boundaries when entries should be checked for purging.
 * The value is specified in minutes.
 */
#define ICF_DNS_PURGE_TIMER_PRECISION_VALUE		1    

/* SPR 17555: Call Direction has defines: Used to indicate to application
 * whether a SIP message is Incoming or Outgoing reported in report_trace_ind
 */
#define ICF_CALL_DIRECTION_OUTGOING       1
#define ICF_CALL_DIRECTION_INCOMING       2



/*-----------------------------------------------------------------
  * What method we would use to start a FAX call. Current we have
  * two methods
  * 1) Add stream for t38 ie send seperate mlines for audio and t38 
  * 2) Replace the audio stream with T38 ie send only a single mline
  *    and that would be T38 
  ------------------------------------------------------------------*/
#define ICF_FAX_METHOD_REPLACE_STREAM 0
#define ICF_FAX_METHOD_ADD_STREAM     1

/*Fix merged for CSR_1_5400409*/    
/*Maximum number of active calls per line when application
  does not configure the max active call per line. */
#define ICF_ACTIVE_CALLS_PER_LINE_DEFAULT  1

/* Limit of maximum number of active calls per line
   that will be suppported. Application can not configure 
   the value of max_active_calls_per_line with more than 
   this value in ICF_SET_CALL_PARAMS API*/ 

#define ICF_MAX_NUM_OF_ACTIVE_CALLS_PER_LINE 8

/*CSR-1-7037536: Specifies the duration of Retry-After header 
  in 486 response.*/
#define ICF_RETRY_AFTER_DURATION          10


/*  WARNING Headers to be send in 488 */

#define ICF_FAX_STOP_WARNING                             "Audio Connection could not be created"
    
#define ICF_FAX_START_WARNING                            "T38 not Supported"


#ifdef ICF_UT_TEST
/* Limit of number of functions which can be asked to return failure at time of
   UT or SI */
#define ICF_MAX_NUM_FUNC_FAIL		5
#endif
    

/*-----------------------------------------------------------------
  * The new Fileds added for DHCP Server
 -----------------------------------------------------------------*/
/* The default timer value for the DHCP Response */
#define	ICF_DHCP_RESPONSE_TIMER		60000

/* The default port for DHCP Server if not configured
   By Application through set_call_params_API ?    */
#define 	ICF_DHCP_CLIENT_PORT		68

/*------------------------------------------------------------------
 *Flag to support NON_IMS_CLIENT moved from icf_feature_flags.h to
 *icf_defs.h and it will remain by default ON.
 ------------------------------------------------------------------*/
/* Flag for NON-IMS Support*/
#define NON_IMS_CLIENT                 1

/*These flags are under umbrella flag IMS_CLIENT*/ 
#ifdef IMS_CLIENT

/* Flag for enabling EmuzedMedia Manager, Make sure to disable MM Stubbing */
/*#define FSS_EMUZED_MEDIA_MANAGER			1*/

#ifdef FSS_EMUZED_MEDIA_MANAGER
/* Comment this flag to disable buffering of MM REQUEST API */
#define ICF_MM_REQUEST_BUFFERING       1
#endif 

/* Flag to Support SIGCOMP in IPPHONETK product */
/* UnComment this Flag to Enable SigComp Support */
/*#define ICF_SIGCOMP_SUPPORT          1*/

/* Flag to Support QoS in IPPHONETK product */
/* Comment this Flag to Disable QOS Support */
/* Qos would be supported if ICF_NETWORK_ACTIVATE is defined -
		check in icf_extif_map_feature_flags.h */

/* Flag to DEBUG MEMORY POOL STATISTICS */
#define ICF_DEBUG_MEMPOOL          		1 
/* Uncomment/Comment these two flags to Enable/disable Memory Pool Statistic */
#define ICF_DETAILED_DEBUG_FILE_TRACE		1
#define ICF_PRINT_DEBUG_STATS			1

/* UnComment this Flag to Enable IPV6 support */
/*#define ICF_IPV6_ENABLED			1*/

/* Flag for enabling IP Security in ICF */
/* Comment this flag to disable IPSec support */
#define ICF_IPSEC_ENABLED               1

#define ICF_IPSEC_STUBBED_OUT	     1
/* Flag to determine whether underlying OS supports SA lifetime modification */
/* Comment this flag if the platform does not allow change in duration of an 
 * already existing SA.
 * This flag should be defined only if ICF_IPSEC_ENABLED is defined */
#define ICF_SA_LIFETIME_MOD_SUPPORT     1

#endif
/*for enabling the QOS functionality this should be defined*/
#define ICF_QOS_SUPPORT    1

/*-----------------------------------------------------------------------
 * NAME : Values for sip_method_name
 *-----------------------------------------------------------------------*/

#define	ICF_METHOD_REGISTER     1
#define	ICF_METHOD_INVITE       2
#define	ICF_METHOD_SUBSCRIBE    3
#define	ICF_METHOD_UPDATE	    4
#define	ICF_METHOD_BYE		    5
#define	ICF_METHOD_MESSAGE	    6
#define	ICF_METHOD_PUBLISH	    7
#define	ICF_METHOD_REFER        8
#define	ICF_METHOD_INFO	        9
#define	ICF_METHOD_OPTIONS      10

/*-----------------------------------------------------------------------
 * This value defines maximum length of API payload can have
 * this value should used by IPTK while sending message to CLIB to
 * encode message and send to application
 * ---------------------------------------------------------------------*/
 /*SPR 19590 - increased payload length for long hdr issue resolution*/
 /*SPR 20016 - To handle the message body of 20K we do require to increase
   the API payload length so making it 30K*/
#define ICF_MAX_API_PAYLOAD_LENGTH  30000

#ifdef ICF_SESSION_TIMER
/*Number of times 491 is accepted for session refresh scenario*/ 
#define ICF_SESSION_REFRESH_NUM_491_RETRY_ALWD           5
#endif
   
/*CSR 00148564*/
#define ICF_MAX_REGISTER_RETRY_LIMIT_ALWD           10
 
#ifdef __cplusplus

}

#endif /* __cplusplus */

#endif /*__ICF_DEFS_H__*/

