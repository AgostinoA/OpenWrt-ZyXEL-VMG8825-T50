/******************************************************************************

*                                        

* FILE NAME    :icf_error_id.h

*                                        

* DESCRIPTION  : This file contains error codes used to indicate the cause of 

*                error for various events.

*                                        

* Revision History :

* DATE          NAME            REFERENCE   REASON

* --------      ------------    --------    ---------------

* 30-Jul-2005  Shekhar/Ashutos   None         Created Original
* 02-Feb-2006  Amit Sharma                    CFG merged with ICF 2.0
* 03-Jan-2007  Amit Mahajan                   INFO confirmation changes
* 09-Jul-2007  Anuradha Gupta    ICF 7.0 LLD  The new error IDs added for 7.0
* 16-Jan-2008  Amit Sharma       ICF 8.0 LLD  Enhancements for Rel8.0
* 24-Jan-2008  Kamini Gangwani   ICF Rel 8.0  Added error IDs
* 27-Jan-2008  Tarun Gupta       IPTK Rel 8.0 LLD Added error IDs 
* 06-MAR-2008  Vipul Varshney   SPR 18122     AKA Enhancement
* 06-Feb-2009  Tarun Gupta       Rel 8.1 LLD  SDP Tunnelling Enhancements
* 30-Mar-2009 Abhishek Dhammawat Rel 8.2      REFER/NOTIFY enhancements
* 31-Mar-2009 Preksha            Rel 8.2      PRACK enhancements
* 22-May-2009 Kamal Ashraf       SPR 19672    CSR_1_6763883 Merged
* 18-Jun-2009 Rajiv Kumar        Rel 8.2      Fix For SPR 19494  
*
* Copyright (c) 2009, Aricent.
*
*                                        

*******************************************************************************/



#ifndef __ICF_ERROR_ID_H__

#define __ICF_ERROR_ID_H__



/* Determine if a C++ compiler is being used.

 * If so, ensure that standard

 * C is used to process the API information.

 */

#include "icf_mm_error_id.h"

#ifdef __cplusplus



/* Yes, C++ compiler is present.

 * Use standard C.

 */



extern "C"

{

#endif /* __cplusplus */



/* No error */

#define ICF_ERROR_NONE   0

    



/*******************************************************************************

 *

 * Error ids used in  different response API's 

 *

*******************************************************************************/





/* Start of Error id */

#define ICF_ERROR_START                             0



/* invalid error id */

#define ICF_ERROR_UNDEFINED                         0



/* memory allocation failure */

#define ICF_ERROR_MEM_ALLOC_FAILURE                 ICF_ERROR_START + 1



/* memory free failure */

#define ICF_ERROR_MEM_FREE_FAILURE                  ICF_ERROR_START + 2



/* timer start failure */

#define ICF_ERROR_TMR_START_FAILURE                 ICF_ERROR_START + 3



/* timer stop failure */

#define ICF_ERROR_TMR_STOP_FAILURE                  ICF_ERROR_START + 4



/* API with invalid id received */

#define ICF_ERROR_INVALID_API_ID                    ICF_ERROR_START + 5



/* call failed because peer SDP was never received */

#define ICF_ERROR_CALL_FAIL_NO_SDP                  ICF_ERROR_START + 6



/*Porting module's receive failure*/

#define ICF_MSG_RECEIVE_ERROR                       ICF_ERROR_START + 7



/*Error for invalid source id is received*/

#define ICF_INVALID_SRC_MODULE_ID                   ICF_ERROR_START + 8

/*Error for failure in Memory Mgr Init*/
#define ICF_ERROR_MEM_INIT							ICF_ERROR_START + 9
    
/*Error for failure in Memory Mgr DeInit*/
#define ICF_ERROR_MEM_DEINIT						ICF_ERROR_START + 10
        
/*Error for failure in Timer Init*/

#define ICF_ERROR_TMR_INIT                          ICF_ERROR_START + 11

    

/*Error for failure in UDP msg TX*/

#define ICF_ERROR_UDP_SEND                          ICF_ERROR_START + 13

    

/*Error for failure in TCP msg TX*/

#define ICF_ERROR_TCP_SEND                          ICF_ERROR_START + 14

    

/*Error for failure socket call*/

#define ICF_ERROR_SOCKET_CREATE                     ICF_ERROR_START + 16

    

/*Error for failure in socket bind*/

#define ICF_ERROR_SOCKET_BIND                       ICF_ERROR_START + 17

    

/*Error for failure in set socket*/

#define ICF_ERROR_SET_SOCKET                        ICF_ERROR_START + 18

    

/*Error for failure in UDP recv */

#define ICF_ERROR_UDP_RECV                          ICF_ERROR_START + 19

    

/* All call context block in DBM pool used up*/

#define ICF_CALL_CTX_BLK_EXHAUSTED                  ICF_ERROR_START + 28



/* All registration context block in DBM pool used up*/

#define ICF_RGN_CTX_BLK_EXHAUSTED                   ICF_ERROR_START + 31



/* No data for the specified module available in DBM's pool*/    

#define ICF_NO_MODULE_DATA_AVAILABLE                ICF_ERROR_START + 32



/*Call context does not exist in global pdb*/

#define ICF_NO_CALL_CTX_EXIST                       ICF_ERROR_START + 33



/*No registration context available for specified user*/

#define ICF_NO_RGN_CTX_EXIST                        ICF_ERROR_START + 35

  

/*If user is not in the list of users on the line*/    

#define ICF_USER_NOT_ADDED                          ICF_ERROR_START + 36



/*For duplicate registration request*/    

#define ICF_DUPLICATE_USER                          ICF_ERROR_START + 37

 

/*Util function for linked array initializtion returns failure*/    

#define ICF_LA_INIT_FAILURE                         ICF_ERROR_START + 38



/* There is no field for the specified type in any structure/union */

#define ICF_MSG_PROC_FIELD_TYPE_MISMATCH            ICF_ERROR_START + 39


/* Invalid operator used for message checking */

#define ICF_MSG_PROC_OPR_MISMATCH                   ICF_ERROR_START + 40


/* Would be raised by CC in case address validation fails for an outgoing call*/
#define ICF_ERROR_INVALID_TRNSPT_ADDR				ICF_ERROR_START + 41

/* Would be returned by DBM when there were no blocks left in pool*/
#define ICF_POOL_EXHAUSTED							ICF_ERROR_START + 42

/* New errors to be raised as alarms.
 */
/*Would be raised when dns query failure response is received from DNS server. */
#define ICF_ERROR_DNS_QUERY_FAILURE                 ICF_ERROR_START + 43

/* Would be raised when unable to make a TCP connection */
#define ICF_ERROR_OPEN_SOCKET                 ICF_ERROR_START + 44

/* Would be raised when unable authentication failure received */
#define ICF_ERROR_AUTHENTICATION_FAILURE                 ICF_ERROR_START + 45

/* Would be raised when requests retransmissions timed out */
#define ICF_ERROR_RETRANSMISSION_TIMEOUT                 ICF_ERROR_START + 46

/*Would be raised when IPTK gets failure response for request*/
#define ICF_ERROR_FAILURE_RESPONSE               ICF_ERROR_START + 47

/* Would be raised when each retransmission of message take place*/
#define ICF_ERROR_INTERMIDIATE_RETRANSMISSION_TIMEOUT    ICF_ERROR_START + 48
/* CSR_1_6763883 Merged SPR 19672 Start */
/* Would be raised when a message from network does not contain header or 
 * parameter that is critical for processing.
 */
#define ICF_ERROR_INCOMPLETE_MSG_FROM_NW    	ICF_ERROR_START + 49
/* CSR_1_6763883 Merged SPR 19672 End */

/*-----------------------------------------------------------------

 * #defines for error IDs raised by CFG 

 * ----------------------------------------------------------------*/



#define ICF_ERROR_START_CFG                         57



/*Indicates that num_of_calls_to_log in API ICF_CFG_CC_SET_CALL_PARAMS

 is greater than ICF_MAX_NUM_OF_CALLS_TO_LOG  */

#define ICF_CAUSE_MAX_CALLS_TO_LOG_OUT_OF_RANGE     ICF_ERROR_START_CFG + 1



/*Indicates that the line corresponding to a given line id is not yet configured  */

#define ICF_CAUSE_LINE_NOT_CONFIGURED               ICF_ERROR_START_CFG + 2



/*Indicates that self_address cannot be configured in domain name format  */

#define ICF_CAUSE_SELF_ADDR_DOMAIN_NAME_NOT_HANDLED ICF_ERROR_START_CFG + 3



/*Indicates that timer value is not valid. Usually used when 

timer duration is configured as 0  */

#define ICF_CAUSE_INVALID_TIMER_VALUE               ICF_ERROR_START_CFG + 4



/*Indicates that the specified configuration action cannot be performed 

during registration or deregistration is ongoing for that user and registrar  */

#define ICF_CAUSE_ACTION_NOT_ALLWD_DURING_REG_ONG   ICF_ERROR_START_CFG + 5



/*Indicates that maximum number of applications are already registered.  */

#define ICF_CAUSE_MAX_NUM_APPLICATION_EXCEEDED      ICF_ERROR_START_CFG + 6



/*Indicates that ICF is not initialised.*/

#define ICF_CAUSE_ICF_NOT_INITIALISED               ICF_ERROR_START_CFG + 7



/* Invalid access_type specified in the ICF_NETWORK_ACTIVATE_REQ API.*/

#define ICF_CAUSE_INVALID_ACCESS_TYPE               ICF_ERROR_START_CFG + 8



/* Invalid access_info specified in the ICF_NETWORK_ACTIVATE_REQ API.*/

#define ICF_CAUSE_INVALID_ACCESS_INFO               ICF_ERROR_START_CFG + 9



/* Indicates the invalid version id.*/

#define ICF_CAUSE_INVALID_VERSION_ID                ICF_ERROR_START_CFG + 10



/* Indicates that the Call ID does not exist.*/

#define ICF_CAUSE_INVALID_CALL_ID                   ICF_ERROR_START_CFG + 11



/* Indicates the invalid source id is specified in the API.*/

#define ICF_CAUSE_INVALID_SOURCE_ID                 ICF_ERROR_START_CFG + 12



/* Indicates the invalid destination id is specified in the API.*/

#define ICF_CAUSE_INVALID_DESTINATION_ID            ICF_ERROR_START_CFG + 13



/* This indicates that application has generated duplicate request.*/

#define ICF_CAUSE_DUPLICATE_REQUEST                 ICF_ERROR_START_CFG + 14



/* This indicates that maximum number of application exceeded.*/

#define ICF_CAUSE_MAX_APP_EXCEEDED                  ICF_ERROR_START_CFG + 15



/* This indicates that maximum number of network supported exceeded.*/

#define ICF_CAUSE_MAX_NETWORK_EXCEEDED              ICF_ERROR_START_CFG + 16



/* Registration procedure ongoing. */

#define ICF_CAUSE_ONGOING_REGISTRATION              ICF_ERROR_START_CFG + 17



/* IMS Client Framework could not obtain public URI. 

(from ISIM/UCIC applications) */

#define ICF_CAUSE_NO_PUBLIC_URI                     ICF_ERROR_START_CFG + 18



/* IMS Client Framework could not obtain private URI. 

(from ISIM/UCIC applications) */

#define ICF_CAUSE_NO_PRIVATE_URI                    ICF_ERROR_START_CFG + 19



/* IMS Client Framework could not obtain authorisation parameters. 

(from ISIM/UCIC applications) */

#define ICF_CAUSE_NO_AUTH_PARAMS                    ICF_ERROR_START_CFG + 20



/* IMS Client Framework could not obtain home network domain. 

(from ISIM/UCIC applications) */

#define ICF_CAUSE_NO_HOME_NETWORK                   ICF_ERROR_START_CFG + 21



/* IMS Client Framework not able to send SIP message on the network. */

#define ICF_CAUSE_TRANSPORT_FAILURE                 ICF_ERROR_START_CFG + 22



/* IMS Client Framework is not able to establish security associations with 

the access network. */

#define ICF_CAUSE_SECUITY_ASSOCIATION_FAILURE       ICF_ERROR_START_CFG + 23



/* Home network has rejected authenticate response. */

#define ICF_CAUSE_AUTH_FAILED                       ICF_ERROR_START_CFG + 24



/* Registration is not successful after sufficient number of re-trials. */

#define ICF_CAUSE_REGISTERATION_RETRY_OVER          ICF_ERROR_START_CFG + 25



/* Network initiated de-registration. */

#define ICF_CAUSE_NETWORK_DEREGISTERED              ICF_ERROR_START_CFG + 26



/* Public-URI is barred. */

#define ICF_CAUSE_PUBLIC_URI_BARRED                 ICF_ERROR_START_CFG + 27



/* ISIM/UCIC has rejected authenticate challenge. */

#define ICF_CAUSE_HOME_NETWORK_NOT_AUTH             ICF_ERROR_START_CFG + 28



/* Invalid PDP context specified in the ICF_NETWORK_DEACTIVATE_REQ API.  */

#define ICF_CAUSE_INVALID_CONTEXT                   ICF_ERROR_START_CFG + 29



/* This error code is returned in Network Deactivate-Confirm. 

This means that the context is not activated because it is 

also being used by some other application. This also indicates that 

ICF shall deactivate the context as soon as all applications deactivate it. */

#define ICF_CAUSE_CONTEXT_BUSY                      ICF_ERROR_START_CFG + 30



/* This indicates invalid app_id. */

#define ICF_CAUSE_INVALID_APP_ID                    ICF_ERROR_START_CFG + 31



/* This indicates invalid option. */

#define ICF_CAUSE_INVALID_OPTION                    ICF_ERROR_START_CFG + 32



/* Indicates that an error response is received from the network. */

#define ICF_CAUSE_NETWORK_ERROR                     ICF_ERROR_START_CFG + 33



/* Is triggered when a response not received within the timeout period. */

#define ICF_CAUSE_TIMER_EXPIRY                      ICF_ERROR_START_CFG + 34



/* Indicates that the call for which call resume is requested is not on hold. */

#define ICF_CAUSE_CALL_ALREADY_ACTIVE               ICF_ERROR_START_CFG + 35



/* Indicates that another call is active on the same line, and as a result, 

another call cannot be activated on that line. */

#define ICF_CAUSE_ANOTHER_CALL_ACTIVE_ON_SAME_LINE  ICF_ERROR_START_CFG + 36



/* Indicates that there is no free audio codec available for the new RTP session, 

or that the audio codec requested for, is unavailable. */

#define ICF_CAUSE_AUDIO_CODEC_NOT_AVAILABLE         ICF_ERROR_START_CFG + 37



/* Indicates that there is no free video codec available for the new RTP session, 

or that the video codec requested for, is unavailable. */

#define ICF_CAUSE_VIDEO_CODEC_NOT_AVAILABLE         ICF_ERROR_START_CFG + 38



/* Indicates that RM is unable to release media resources for the call. */

#define ICF_CAUSE_UNABLE_TO_RELEASE_RESOURCES       ICF_ERROR_START_CFG + 39



/* Indicates that the mode requested for the RTP session is not inline with 

the SDP parameters. For example, the Send Only mode cannot be applied when 

remote RTP and codec information is unavailable. */

#define ICF_CAUSE_MODE_NOT_COMPATIBLE_TO_SDP        ICF_ERROR_START_CFG + 40



/* Indicates that the system is unable to create a new media session. */

#define ICF_CAUSE_UNABLE_TO_CREATE_MEDIA            ICF_ERROR_START_CFG + 41



/* Indicates that insufficient parameters are present in the API. */

#define ICF_CAUSE_INSUFFICIENT_PARAMETERS           ICF_ERROR_START_CFG + 42



/* Indicates that insufficient resources are present to perform the request.*/

#define ICF_CAUSE_INSUFFICIENT_RESOURCES            ICF_ERROR_START_CFG + 43



/* Indicates that MM is unable to delete an ongoing media session. */

#define ICF_CAUSE_UNABLE_TO_DELETE_MEDIA_SESSION    ICF_ERROR_START_CFG + 44



/* Indicates that the ICF  is unable to bind with the self IP address provided 

   in the API. */

#define ICF_CAUSE_SELF_IP_ADDR_BIND_FAILURE         ICF_ERROR_START_CFG + 45



/* Indicates that the stats ID specified in the API does not exist. */

#define ICF_CAUSE_INVALID_STATS_ID                  ICF_ERROR_START_CFG + 46



/* Indicates that the IP port specified in the API is out of range. */

#define ICF_CAUSE_IP_PORT_OUT_OF_RANGE              ICF_ERROR_START_CFG + 47



/* Indicates that a media failure has occurred. */

#define ICF_CAUSE_MEDIA_FAILURE                     ICF_ERROR_START_CFG + 48



/* Indicates that max_lines received in API ICF_CFG_CC_SET_SCALE_PARAMS

   is not in range 1 to 24. */

#define ICF_CAUSE_MAX_LINES_OUT_OF_RANGE            ICF_ERROR_START_CFG + 49



/* Indicates that the line_id received in any of the configuration API 

   is out of the range 1 to max_lines. */

#define ICF_CAUSE_INVALID_LINE_ID                   ICF_ERROR_START_CFG + 50



/* Indicates that because of new registrar added or the new user added 

   to a line, the number of registrations active exceeds he configured 

   value of max_registration_calls. */

#define ICF_CAUSE_MAX_REGISTRATION_CALLS_EXCEEDED   ICF_ERROR_START_CFG + 51



/* Indicates that the because of new user configured, the value of users

   on one of a line has exceeded configured value of max_users_per_line. */

#define ICF_CAUSE_MAX_USERS_PER_LINE_EXCEEDED       ICF_ERROR_START_CFG + 52



/* Indicates that address received in API from Application is in invalid format. */

#define ICF_CAUSE_INVALID_ADDRESS_RECEIVED          ICF_ERROR_START_CFG + 53


/* Indicates that max_audio_calls received is 0 */
#define ICF_CAUSE_MAX_AUDIO_CALLS_OUT_OF_RANGE		ICF_ERROR_START_CFG + 54


/* Indicates that max_registration_calls received in API ICF_CFG_CC_SET_SCALE
 * _PARAMS is 0 */
#define ICF_CAUSE_MAX_REGISTRATION_CALLS_OUT_OF_RANGE  ICF_ERROR_START_CFG + 55


/* Indicates that max_users_per_line is 0 */
#define ICF_CAUSE_MAX_USERS_PER_LINE_OUT_OF_RANGE	ICF_ERROR_START_CFG + 56

/* Indicates that URI is not De-registered */
#define ICF_ERROR_CAUSE_URI_NOT_DEREGISTERED        ICF_ERROR_START_CFG + 57      

/*ICF_CRM_START*/
/* Indicates that network activate request has been denied to the 
 * application */
#define ICF_CAUSE_ACTIVATE_DENIED                   ICF_ERROR_START_CFG + 58

/* Indicates that network could not be activated */
#define ICF_CAUSE_ACTIVATION_FAILURE                ICF_ERROR_START_CFG + 59

/* Indicates that network could not be de-activated */
#define ICF_CAUSE_DEACTIVATION_FAILURE              ICF_ERROR_START_CFG + 60

/* Indicates that given application ID is not entitled to call network de-activation */
#define ICF_CAUSE_ILLEGAL_REQUEST                   ICF_ERROR_START_CFG + 61

/* Indicates that call type in application add request is invalid */
#define ICF_CAUSE_INVALID_CALL_TYPE                 ICF_ERROR_START_CFG + 62

/* Indicates that routing info is invalid(non-UDP) */
#define ICF_CAUSE_INVALID_ROUTING_INFO              ICF_ERROR_START_CFG + 63

/* Indicates filter list parsing failure */
#define ICF_CAUSE_FILTER_PARSE_FAILED               ICF_ERROR_START_CFG + 64

/* Indicates internal Failure */
#define ICF_CAUSE_INTERNAL_FAILURE                  ICF_ERROR_START_CFG + 65


#define ICF_CAUSE_NW_CURRENTLY_NOT_AVAILABLE        ICF_ERROR_START_CFG + 66

/*ICF_4_0_CRM_START*/

/* indicates invalid request: DEREG without REG */
#define ICF_CAUSE_INVALID_REG_REQUEST		   ICF_ERROR_START_CFG	+ 67

/* Indicates that the scheme received in challenge is not supported by ICF */
#define ICF_CAUSE_SCHEME_NOT_SUPPORTED		  ICF_ERROR_START_CFG	+ 68
	
/* Indicates that the algo received in challenge is not supported by ICF */
#define ICF_CAUSE_ALGO_NOT_SUPPORTED		  ICF_ERROR_START_CFG	+ 69

/* Indicates that the algo received in challenge is not supported by ICF */
#define ICF_CAUSE_PROPER_NONCE_NOT_RECD		  ICF_ERROR_START_CFG	+ 70

/* Indicates that the algo received in challenge is not supported by ICF */
#define ICF_CAUSE_SQN_OUT_OF_RANGE		  ICF_ERROR_START_CFG	+ 71

/* to indicate that line id in dereg is different than the line id sent in REG  request */
#define ICF_CAUSE_LINE_ID_MISMATCH		  ICF_ERROR_START_CFG + 72

/* To indicate that the Network is Deactivated and rgm_context is Unregistered */
#define ICF_CAUSE_NW_DEACTIVATED		ICF_ERROR_START_CFG + 73
   
/* To indicate that the Transport mode Inconsister*/
#define ICF_CAUSE_INCONSISTENT_TRANSPORT_MODE       ICF_ERROR_START_CFG + 74
    
/*ICF_4_0_CRM_END*/
/* To indicate the application that it has been deregistered on PROBATION */
#define ICF_CAUSE_NW_PROBATION                      ICF_ERROR_START_CFG + 75

/* To indicate the application that it has been deregistered by Network
 * on Expiration */
#define ICF_CAUSE_NW_EXPIRATION                      ICF_ERROR_START_CFG + 76


 /* To indicate the application that it has been deregistered by network
 * reason=rejected. No re-register entertained for the app's contact  */
#define ICF_CAUSE_NW_REJECTED                      ICF_ERROR_START_CFG + 77

/* To indicate the application that it has been deregistered by network
 * reason=unregistered  */
#define ICF_CAUSE_NW_UNREGISTERED                   ICF_ERROR_START_CFG + 78

/* To indicate that list of supported headers in app_add_request was empty */
#define ICF_CAUSE_EMPTY_SUPP_HDR_LIST               ICF_ERROR_START_CFG + 79

/* To indicate the call modify request is not accepatable */
#define ICF_CAUSE_REJECT_MEDIA_CHANGE_REQ	    ICF_ERROR_START_CFG + 80

#ifdef ICF_IPSEC_ENABLED
/* To indicate that SA creation failed or timed-out */
#define ICF_CAUSE_SA_CREATION_FAILURE               ICF_ERROR_START_CFG + 81

/* To indicate failure for REG req when old and new SAs exist - limitation */
#define ICF_CAUSE_MULTIPLE_SA_EXIST                 ICF_ERROR_START_CFG + 82

/* To indicate general IPSec failure */
#define ICF_CAUSE_IPSEC_FAILURE                     ICF_ERROR_START_CFG + 83
#endif /* ICF_IPSEC_ENABLED */

#ifdef ICF_SERVICE_ENABLE

#define ICF_CAUSE_ADDR_FOR_SERV_NOT_CONFIGURED		ICF_ERROR_START_CFG + 84	
#define ICF_CAUSE_SERVICE_NOT_SUBSCRIBED			ICF_ERROR_START_CFG + 85

#endif

#define ICF_CAUSE_SCALE_PARAMS_NOT_CONFIGURED		ICF_ERROR_START_CFG + 86
#define ICF_CAUSE_SCALE_PARAMS_ALREADY_CONFIGURED	ICF_ERROR_START_CFG + 87

/*ICF_HANDLE_REINVITE_START*/
/* to indicate that request is already pending for a call modify request */
#define ICF_CAUSE_CALL_MODIFY_REQ_PENDING			ICF_ERROR_START_CFG + 88

/* to indicate an invalid request */
#define ICF_CAUSE_INVALID_CALL_MODIFY_REQUEST		ICF_ERROR_START_CFG + 89

#define ICF_CAUSE_REMOTE_RELEASED					ICF_ERROR_START_CFG + 90
/*ICF_HANDLE_REINVITE_END*/

#define ICF_CAUSE_IMPLICITLY_REGISTERED             ICF_ERROR_START_CFG	+ 91

/* failure error_code returned to app when a mandatory header is not received
 * in SIP response from network */
#define ICF_CAUSE_MANDATORY_HDR_NOT_RCVD            ICF_ERROR_START_CFG + 92

/* reject the call modify request for addition of new stream */
#define ICF_CAUSE_STREAM_ADDITION_NOT_ALLOWED		ICF_ERROR_START_CFG + 93

/* if there is no audion call then fax call can not be allowed */
#define ICF_CAUSE_FAX_CALL_NOT_ALLOWED				ICF_ERROR_START_CFG + 94

/* the fax request is invalid */
#define ICF_CAUSE_INVALID_FAX_REQUEST				ICF_ERROR_START_CFG + 95

/*NOTIFY_OUT_OF_DIALOG_START*/

#define ICF_CAUSE_MIME_BODY_DECODE_FAILURE			ICF_ERROR_START_CFG + 96

/*NOTIFY_OUT_OF_DIALOG_END*/

#define	ICF_CAUSE_CALL_SETUP_IN_PROGRESS			ICF_ERROR_START_CFG + 97

#define ICF_CAUSE_FAX_PROFILE_NOT_CONFIGURED        ICF_ERROR_START_CFG + 98

#define ICF_CAUSE_FAX_REQ_PENDING                   ICF_ERROR_START_CFG + 99

#define ICF_CAUSE_FAX_CALL_ONGOING                  ICF_ERROR_START_CFG + 100

#define ICF_CAUSE_SERVICE_ONGOING                   ICF_ERROR_START_CFG + 101

/* Indicates that the realm received in challenge is not supported by ICF */
#define ICF_CAUSE_REALM_MISMATCH		            ICF_ERROR_START_CFG	+ 102

/* Basic Authentication scheme not supported */
#define ICF_CAUSE_BASIC_AUTH_SCHEME_NOT_SUPPORTED	ICF_ERROR_START_CFG + 103

/* generic error cause for indicating license expiry to the application */
#define ICF_CAUSE_LICENSE_EXPIRED                   ICF_ERROR_START_CFG + 104

/* generic error cause for indicating license expiry to the application */
#define ICF_CAUSE_USER_NOT_LICENSED                 ICF_ERROR_START_CFG + 105

#define ICF_CAUSE_INFO_CFM_PENDING                  ICF_ERROR_START_CFG + 106

/* MAXIMUM number of servers are already opened*/
#define ICF_CAUSE_MAX_SERVER_LIMIT_REACHED			ICF_ERROR_START_CFG + 107

/* MODIFY action not supported in self addr per line*/
#define ICF_CAUSE_SELF_ADDR_MODIFY_NOT_SUPP			ICF_ERROR_START_CFG + 108

#define ICF_CAUSE_UNSUPPORTED_METHOD_IN_LIST        ICF_ERROR_START_CFG + 109

/*Error cause for register request for a wildcarded user*/
#define ICF_CAUSE_WILDCARDED_URI                    ICF_ERROR_START_CFG + 110

/* Error Cause for stopping the fax request */
#define ICF_CAUSE_FAX_REQUEST_STOPPED               ICF_ERROR_START_CFG + 111

#define ICF_CAUSE_NO_FAX_CALL_ONGOING				ICF_ERROR_START_CFG + 112

#define ICF_CAUSE_NO_ACTIVE_AUDIO_STREAM_PRESENT 	ICF_ERROR_START_CFG + 113		
#define ICF_CAUSE_STOP_FAX_REQ_ONGOING              ICF_ERROR_START_CFG + 114

#define ICF_CAUSE_USER_INITIATED_CALL_TERM_REQ	 	ICF_ERROR_START_CFG + 115	
#define ICF_CAUSE_INVALID_API_ID		    ICF_ERROR_START_CFG + 116	
#define ICF_CAUSE_REGISTRAR_NOT_CONFIGURED          ICF_ERROR_START_CFG + 117
#define ICF_CAUSE_NO_USER_EXIST_ON_LINE             ICF_ERROR_START_CFG + 118
#define ICF_CAUSE_RES_NOT_AVAILABLE_FOR_T38_FAX     ICF_ERROR_START_CFG + 119
/*Fix merged for CSR_1_5400409*/    
/* This error cause will be sent by IPTK to application
    when the value of max_active_calls_per_line will be Invalid
    in ICF_SET_CALL_PARAMS API */

#define ICF_CAUSE_INVALID_MAX_ACTIVE_CALLS_PER_LINE  ICF_ERROR_START_CFG + 120

#define ICF_ERROR_DIRECT_ROUTED_CALL_NOT_ALWD        ICF_ERROR_START_CFG + 121

#define ICF_CAUSE_SRTP_NEG_FAILURE                  ICF_ERROR_START_CFG + 122
#define ICF_CAUSE_AUTH_PARAM_NOT_RCVD               ICF_ERROR_START_CFG +  123 

#define ICF_ERROR_END_CFG                           ICF_ERROR_START_CFG +  124
    

/* -------------------------------------------------------------------------
 * #defines of Management Plane handler   error ids
 * ------------------------------------------------------------------------*/


/* MPH Error ID Start */

#define ICF_ERROR_START_MPH                         ICF_ERROR_END_CFG

/* caused when connection close fails */

#define ICF_CAUSE_CLOSE_CONN_FAILURE				ICF_ERROR_START_MPH + 1
	
/* caused when a timer expiry mesg is received from MRM by 
icf_mph_process_msg against no response timer */

#define ICF_CAUSE_NO_RESP_FROM_SERVER				ICF_ERROR_START_MPH + 2

/* caused when no empty application node exists in mph_data to 
support a new entry */

#define ICF_CAUSE_MAX_APPLICATION_EXCEEDED			ICF_ERROR_START_MPH + 3

/* caused when no empty server node exists against an application in 
mph_data to support a new connection/server entry */

#define ICF_CAUSE_MAX_CONNECTION_EXCEEDED			ICF_ERROR_START_MPH + 4

/* caused when application tries to overwrite auth data against 
a server connection with pending request */

#define ICF_CAUSE_REQ_PENDING_ON_CURRENT_AUTH_DATA	ICF_ERROR_START_MPH + 5

/* caused when application tries to remove server data which is not actually present */

#define ICF_CAUSE_SERVER_INFO_MISSING				ICF_ERROR_START_MPH + 6

/* caused when all pending/ongoing requests against a server 
	connection are failed when the application issues icf_mph_set_auth_param_hdlr 
	to remove server data */
	
#define ICF_CAUSE_SERVER_INFO_REMOVED				ICF_ERROR_START_MPH + 7

/* caused when connection creation fails */

#define ICF_CAUSE_CONNECTION_FAILURE				ICF_ERROR_START_MPH + 8

/* caused when connection already exists and application issues 
connection create again */

#define ICF_CAUSE_CONNECTION_ALREADY_EXISTS			ICF_ERROR_START_MPH + 9 

/* caused when there is an error related to the connection closure from the port side */
	
#define ICF_CAUSE_FROM_PORT							ICF_ERROR_START_MPH + 10

/* caused when connection closure type bit is anything else except CLOSE or ABORT */
	
#define ICF_CAUSE_INVALID_CONN_CLOSURE_TYPE			ICF_ERROR_START_MPH + 11

/* caused when send_http_req API of the port fails due to any reason */

#define ICF_CAUSE_PORT_SEND_HTTP_REQ				ICF_ERROR_START_MPH + 12
	
/* caused when make_http_req API of the port fails, i.e. it is unable to 
   form a valid HTTP request */

#define ICF_CAUSE_PORT_MAKE_HTTP_REQ				ICF_ERROR_START_MPH + 13
	
/* caused when mandatory SyncML headers are not present in the HTTP message */

#define ICF_CAUSE_SYNCML_HEADERS_NOT_PRESENT		ICF_ERROR_START_MPH + 14
	
/* caused when connection id does not exist */

#define ICF_CAUSE_INVALID_CONNECTION_ID				ICF_ERROR_START_MPH + 15

/* caused when mandatory headers (eg req_uri), required as a must to form a 
HTTP request are not present */

#define ICF_CAUSE_MANDATORY_HEADERS_NOT_PRESENT		ICF_ERROR_START_MPH + 16

/* caused when connection create is re-attempted after a connection close 
indication from peer */

#define ICF_CAUSE_CONNECTION_REATTEMPT_FAILURE		ICF_ERROR_START_MPH + 17

/* caused when WWW-Authenticate header is not present in 401 from server */

#define ICF_CAUSE_WWW_AUTHENTICATE_NOT_PRESENT_IN_401	ICF_ERROR_START_MPH + 18

/* caused when stale bit is set to false in 401	*/

#define ICF_CAUSE_INVALID_USERNAME_PASSWD			ICF_ERROR_START_MPH + 19

/* caused when auth parameters have not been configured and server sends 401 */

#define ICF_CAUSE_AUTH_DATA_NOT_PRESENT				ICF_ERROR_START_MPH + 20

/* caused when auth scheme is not present in 401 */

#define ICF_CAUSE_UNKNOWN_AUTH_SCHEME_IN_401		ICF_ERROR_START_MPH + 21

/* caused when realm is not present in 401 */

#define ICF_CAUSE_REALM_NOT_PRESENT_IN_401			ICF_ERROR_START_MPH + 22

/* caused when nonce is not present in 401 */

#define ICF_CAUSE_NONCE_NOT_PRESENT_IN_401			ICF_ERROR_START_MPH + 23

/* caused when all pending/ongoing requests against an application are 
failed when the application issues application remove */

#define ICF_CAUSE_APPLICATION_REMOVED				ICF_ERROR_START_MPH + 24

/* caused when all pending/ongoing requests against an application are 
failed when network gets deactivated */

#define ICF_CAUSE_NETWORK_DEACTIVATED				ICF_ERROR_START_MPH + 25

/* caused when all pending/ongoing requests against an application are 
failed when the application adds itself again */

#define ICF_CAUSE_APPLICATION_ADDED_AGAIN			ICF_ERROR_START_MPH + 26

/* caused when pending requests on a connection are failed due to conn close req */

#define ICF_CAUSE_CLOSE_CONN_REQ				ICF_ERROR_START_MPH + 27

#define ICF_CAUSE_MAKE_AUTHORISATION_FAILED			ICF_ERROR_START_MPH + 28

#define ICF_CAUSE_INVALID_CONNECTION_USAGE			ICF_ERROR_START_MPH + 29

#define ICF_CAUSE_NW_RESP_FAILED				ICF_ERROR_START_MPH + 30

#define ICF_ERROR_END_MPH					ICF_ERROR_START_MPH + 30

/* -------------------------------------------------------------------------

 * #defines of Media Manager   error ids

 * ------------------------------------------------------------------------*/

/* MM Error ID Start */

#define ICF_ERROR_START_MM                          ICF_ERROR_END_MPH



/*Indicates that ring-tone requested is not supported.*/

#define ICF_CAUSE_RING_TONE_NOT_SUPPORTED           ICF_ERROR_START_MM + 1



/*Indicates that an internal error occured.*/

#define ICF_CAUSE_INTERNAL_ERROR                    ICF_ERROR_START_MM + 2



/*Indicates that no connection is existing for call-id mentioned.*/

#define ICF_CAUSE_CONNECTION_FOR_CALLID_NOT_FOUND   ICF_ERROR_START_MM + 3



/*Indicates that value is invalid passed in API*/

#define ICF_CAUSE_INVALID_VALUE                     ICF_ERROR_START_MM + 4



/*Indicates that the service request is not supported.*/

#define ICF_CAUSE_NOT_SUPPORTED                     ICF_ERROR_START_MM + 5



/*Indicates that the file specified is not found at path given.*/

#define ICF_CAUSE_FILE_PATH_NOT_FOUND               ICF_ERROR_START_MM + 6



/*Indicates that the tone requested to play is not supported.*/

#define ICF_CAUSE_TONE_NOT_SUPPORTED                ICF_ERROR_START_MM + 7



/*Indicates that the requested action is not valid in current scenario.*/

#define ICF_CAUSE_INVALID_ACTION                    ICF_ERROR_START_MM + 8



/*Indicates that the invalid output device for media play out.*/

#define ICF_CAUSE_INVALID_PLAY_OUT_VAL              ICF_ERROR_START_MM + 9



/*Indicates that the file format is not supported/ invalid.*/

#define ICF_CAUSE_INVALID_FILE_TYPE                 ICF_ERROR_START_MM + 10



/*Indicates that the digit is unknown/ invalid.*/

#define ICF_CAUSE_INVALID_DIGIT                     ICF_ERROR_START_MM + 11



/*Indicates that the value requested is out of range. */

#define ICF_CAUSE_OUT_OF_RANGE                      ICF_ERROR_START_MM + 12



/*Indicates that the jitter buffer type is invalid.*/

#define ICF_CAUSE_INVALID_JB_TYPE                   ICF_ERROR_START_MM + 13



/*Indicates that the jitter buffer scaling factor is invalid.*/

#define ICF_CAUSE_INVALID_JB_SCALING_FACT           ICF_ERROR_START_MM + 14



/*Indicates that the jitter buffer init size is invalid.*/

#define ICF_CAUSE_INVALID_JB_INIT_SIZE              ICF_ERROR_START_MM + 15



/*Indicates that the jitter buffer maximum size is invalid*/

#define ICF_CAUSE_INVALID_JB_MAX_SIZE               ICF_ERROR_START_MM + 16



/*Indicates that the jitter buffer minimum size is invalid.*/

#define ICF_CAUSE_INVALID_JB_MIN_SIZE               ICF_ERROR_START_MM + 17



#define ICF_ERROR_END_MM                            ICF_CAUSE_INVALID_JB_MIN_SIZE


/* ---------------------------------------------------------------------------
 * Some more error codes that were used by ICF
 */

#define ICF_MISC_ERROR_START						ICF_ERROR_END_MM

/* Error code when some failure occurs in UATK processing */
#define ICF_ERROR_UATK_FAILURE						ICF_MISC_ERROR_START + 1

/*Error to indicate to IPPTK that a non blocking connect call
 * returned E_INPROGRESS*/
#define ICF_CONNECT_RESP_PENDING					ICF_MISC_ERROR_START + 2

/* Error for failure returned by init nw interface during CFG Init complete */
#define ICF_ERROR_NW_INTERFACE						ICF_MISC_ERROR_START + 3

/* Error for failure returned by RGM Init Complete during CFG Init complete */
#define ICF_ERROR_RGM_INIT_CMPLT					ICF_MISC_ERROR_START + 4

/* Error for failure returned in getting DBM port data during CFG Init complete
 *  */
#define ICF_ERROR_DBM_PORT_DATA						ICF_MISC_ERROR_START + 5

/* Error for failure returned by ES init complete during CFG Init complete */
#define ICF_ERROR_ES_INIT_CMPLT						ICF_MISC_ERROR_START + 6

/* Error if all conditions to perform init complete are not met */
#define ICF_ERROR_INIT_CMPLT						ICF_MISC_ERROR_START + 7

#define ICF_MSG_PROC_INIT_NOT_COMPLETE				ICF_MISC_ERROR_START + 8

#define ICF_INVALID_API_ID_RECD						ICF_MISC_ERROR_START + 9

#define ICF_INVALID_MSG_ID_RECD						ICF_MISC_ERROR_START + 10

#define ICF_MODIFY_USER_FAILED						ICF_MISC_ERROR_START + 11

#define ICF_PROCESS_MODIFY_USER_BLK_FAILED			ICF_MISC_ERROR_START + 12

#define ICF_MODIFY_REGISTRAR_FAILED					ICF_MISC_ERROR_START + 13

#define ICF_PROCESS_MODIFY_REG_BLK_FAILED			ICF_MISC_ERROR_START + 14

#define ICF_MODIFY_DURATION_FAILED					ICF_MISC_ERROR_START + 15

#define ICF_PROCESS_MODIFY_DUR_BLK_FAILED			ICF_MISC_ERROR_START + 16

#define ICF_AUTHENTICATION_INFO_ABSENT				ICF_MISC_ERROR_START + 17

#define ICF_INVALID_NETWORK_RESPONSE				ICF_MISC_ERROR_START + 18

#define ICF_UNABLE_TO_SEND_REG_REQ					ICF_MISC_ERROR_START + 19

#define ICF_UNABLE_TO_SEND_DEREG_REQ				ICF_MISC_ERROR_START + 20

#define ICF_INIT_COMPLETE_FAILED					ICF_MISC_ERROR_START + 21

#define ICF_NO_SRVC_CTX_EXIST					ICF_MISC_ERROR_START + 22

#define ICF_SRVC_CTX_BLK_EXHAUSTED               ICF_MISC_ERROR_START + 23

#define ICF_SRVC_CTX_LGC_BLK_EXHAUSTED           ICF_MISC_ERROR_START + 24

#define ICF_ERROR_SERVICE_NOT_SUBSCRIBED         ICF_MISC_ERROR_START + 25

#define ICF_ERROR_SERVICE_NOT_ACTIVE             ICF_MISC_ERROR_START + 26

#define ICF_ERROR_INVALID_SERVICE_INTERACTION    ICF_MISC_ERROR_START + 27

#define ICF_ERROR_SL_NOT_RUNNING                 ICF_MISC_ERROR_START + 28

#define ICF_ERROR_INV_PAYLOAD_RECVD              ICF_MISC_ERROR_START + 29

#define ICF_ERROR_INVALID_PARAM                  ICF_MISC_ERROR_START + 30

#define ICF_ERROR_FIFO_CREATION					ICF_MISC_ERROR_START + 31

#define ICF_ERROR_FIFO_SEND						ICF_MISC_ERROR_START + 32

#define ICF_ERROR_FIFO_RECV						ICF_MISC_ERROR_START + 33

#define ICF_CAUSE_MM_AL_CONTEXT_NOT_FOUND        ICF_MISC_ERROR_START + 34

#define ICF_CAUSE_MM_AL_NO_FREE_CONTEXT_FOUND    ICF_MISC_ERROR_START + 35

#define ICF_MM_AL_NO_VALID_CODEC_RETURNED        ICF_MISC_ERROR_START + 36

#define ICF_MM_AL_UNKNOWN_REQUEST_FROM_MMI       ICF_MISC_ERROR_START + 37

#define ICF_MM_AL_UNKNOWN_MESSAGE_FROM_RM        ICF_MISC_ERROR_START + 38

#define ICF_TERMINAL_FAILURE_CALL_CLEAR          ICF_MISC_ERROR_START + 39

#define ICF_ERROR_NO_API_HANDLER					ICF_MISC_ERROR_START + 41

#define ICF_ERROR_CALL_WAITING_FAILURE           ICF_MISC_ERROR_START + 42

#define ICF_ERROR_LIC_INTEGRTY					ICF_MISC_ERROR_START + 43

#define ICF_RESPONSE_SEND_FAILURE					ICF_MISC_ERROR_START + 44

#define ICF_ERROR_CALL_LOGGING_FAILURE				ICF_MISC_ERROR_START + 45

#define ICF_CAUSE_MM_AL_MEMORY_FAILURE				ICF_MISC_ERROR_START + 46

#define ICF_CAUSE_INVALID_SERVICE_ACTION			ICF_MISC_ERROR_START + 47

#define ICF_CAUSE_PARTY_ALREADY_ON_LOCAL_HOLD		ICF_MISC_ERROR_START + 48

#define ICF_CAUSE_REMOTE_REJECT_CALL_TRANFER_REQ    ICF_MISC_ERROR_START + 49

#define ICF_CAUSE_CALL_MERGE_FAIL                   ICF_MISC_ERROR_START + 50

#define ICF_CAUSE_SERVICE_NOT_ACTIVATED             ICF_MISC_ERROR_START + 51

#define ICF_CAUSE_PROHIBITED_BY_SERVICE_INTERACTION ICF_MISC_ERROR_START + 52

#define ICF_CAUSE_GPRS_SUSPENDED                    ICF_MISC_ERROR_START + 53

#define ICF_RES_THRESHOLD_REACHED					ICF_MISC_ERROR_START + 54
		
#define ICF_ERROR_NO_PREF_ID_EXISTS                 ICF_MISC_ERROR_START + 55

#define ICF_ERROR_GENERIC                           ICF_MISC_ERROR_START + 56

#define ICF_ERROR_NO_MMI_CONTEXT_FOUND              ICF_MISC_ERROR_START + 57
       
#ifdef ICF_SIGCOMP_SUPPORT
#define ICF_ERROR_INCOMPLETE_MSG_RECEIVED           ICF_MISC_ERROR_START + 58
#define ICF_ERROR_REFER_PENDING			            ICF_MISC_ERROR_START + 59
#else
#define ICF_ERROR_REFER_PENDING			            ICF_MISC_ERROR_START + 58
#endif

#define ICF_ERROR_MISMATCH_IN_ADDR_PLAN	  	    ICF_MISC_ERROR_START + 60	

#define ICF_CAUSE_DNS_QUERY_FAILURE	            ICF_MISC_ERROR_START + 61

#define ICF_CAUSE_REQUEST_ALREADY_PENDING		ICF_MISC_ERROR_START + 62

#define ICF_CAUSE_REMOTE_UNREACHABLE			ICF_MISC_ERROR_START + 63

#define ICF_CAUSE_IN_DIALOG_OTG_OPTIONS_RECEIVED	ICF_MISC_ERROR_START + 64

#define ICF_CAUSE_REFER_TO_ABSENT                   ICF_MISC_ERROR_START + 65

/*SPR 13978 Aman 03-01-07*/
/*When app tries to make a call on a port which is not opened*/
#define ICF_CAUSE_OPEN_NW_SERVER_FAILED        ICF_MISC_ERROR_START + 66

/* Anuradha : error causes moved from icf_common_defs.h */

#define ICF_CAUSE_INFO_ALREADY_PENDING              ICF_MISC_ERROR_START + 67

#define ICF_CAUSE_INFO_REJECTED_BY_REMOTE           ICF_MISC_ERROR_START + 68

#define ICF_CAUSE_LICENCE_VIOLATED                  ICF_MISC_ERROR_START + 69

#define ICF_CAUSE_SDP_MISSING_FOR_PRECONDITION      ICF_MISC_ERROR_START + 70

#define ICF_CAUSE_PRECONDITION_PROV_WITHOUT_100REL  ICF_MISC_ERROR_START + 71

#define ICF_CAUSE_CALL_MERGED_DUE_TO_JOIN           ICF_MISC_ERROR_START + 72

#define ICF_CAUSE_REQUEST_CANCELLED_BY_USER         ICF_MISC_ERROR_START + 73

#define ICF_CAUSE_CALL_MODIFY_METHOD_NOT_INVITE     ICF_MISC_ERROR_START + 74

#define ICF_CAUSE_CALL_MODIFY_TRANSACTION_COMPLETE	ICF_MISC_ERROR_START + 75

#define ICF_CAUSE_ADD_PARTY_RESP_ALREADY_PENDING    ICF_MISC_ERROR_START + 76

#define ICF_CAUSE_DELETE_PARTY_RESP_ALREADY_PENDING ICF_MISC_ERROR_START + 77

#define ICF_CAUSE_INC_CONFERENCE_CANNOT_DO_ADD_PARTY ICF_MISC_ERROR_START + 78

#define ICF_CAUSE_CONF_NOT_CONNECTED_CANNOT_DO_ADD_PARTY ICF_MISC_ERROR_START+79

#define ICF_CAUSE_INTERNAL_REFER_FAILED              ICF_MISC_ERROR_START + 80

#define ICF_CAUSE_INC_CONFERENCE_CANNOT_DO_DEL_PARTY ICF_MISC_ERROR_START + 81

#define ICF_CAUSE_CALL_RELEASED                      ICF_MISC_ERROR_START + 82

#define ICF_CAUSE_EXT_CONFERENCE_VALIDATION_FAILED   ICF_MISC_ERROR_START + 83

#define ICF_CAUSE_INC_CONFERENCE_CANNOT_DO_RELEASE   ICF_MISC_ERROR_START + 84

#define ICF_CAUSE_CONF_TERMINATE_CANNOT_DO_DEL_PARTY ICF_MISC_ERROR_START + 85

#define ICF_CAUSE_INVALID_REQUEST                    ICF_MISC_ERROR_START + 86

#define ICF_CAUSE_CONF_NOT_CONNECTED_CANNOT_DO_DEL_PARTY ICF_MISC_ERROR_START+87

#define ICF_CAUSE_MEDIA_MODIFY_ONGOING               ICF_MISC_ERROR_START + 88

#define ICF_MISC_ERROR_END                           ICF_MISC_ERROR_START + 88
 

/*---------------------------------------------------------------------------*/
/* Add last ecode */
/* Error codes added for API validation */
#define ICF_ERROR_START_VALIDATION                          ICF_MISC_ERROR_END

#define ICF_CAUSE_INVALID_ADDRESS_TYPE              ICF_ERROR_START_VALIDATION+1

#define ICF_CAUSE_HEADER_LIST_NOT_PRESENT           ICF_ERROR_START_VALIDATION+2

#define ICF_CAUSE_HEADER_LIST_COUNT_MISMATCH        ICF_ERROR_START_VALIDATION+3

#define ICF_CAUSE_TAG_LIST_NOT_PRESENT              ICF_ERROR_START_VALIDATION+4

#define ICF_CAUSE_TAG_LIST_COUNT_MISMATCH           ICF_ERROR_START_VALIDATION+5

#define ICF_CAUSE_BODY_LIST_NOT_PRESENT             ICF_ERROR_START_VALIDATION+6

#define ICF_CAUSE_BODY_LIST_COUNT_MISMATCH          ICF_ERROR_START_VALIDATION+7

#define ICF_CAUSE_HEADER_NAME_LIST_NOT_PRESENT      ICF_ERROR_START_VALIDATION+8

#define ICF_CAUSE_HEADER_NAME_LIST_COUNT_MISMATCH   ICF_ERROR_START_VALIDATION+9

#define ICF_CAUSE_STRING_LIST_NOT_PRESENT           ICF_ERROR_START_VALIDATION+10

#define ICF_CAUSE_STRING_LIST_COUNT_MISMATCH        ICF_ERROR_START_VALIDATION+11

#define ICF_CAUSE_PORT_NUM_OUT_OF_RANGE             ICF_ERROR_START_VALIDATION+12


#define ICF_CAUSE_CALL_ID_OUT_OF_RANGE              ICF_ERROR_START_VALIDATION+13

#define ICF_CAUSE_INVALID_CONFIG_ACTION             ICF_ERROR_START_VALIDATION+14

#define ICF_CAUSE_INVALID_VALUE_FOR_BOOLEAN         ICF_ERROR_START_VALIDATION+15

#define ICF_CAUSE_INCORRECT_TRANSPORT_MODE          ICF_ERROR_START_VALIDATION+16


#define ICF_CAUSE_INVALID_SHORT_STR_LEN             ICF_ERROR_START_VALIDATION+17

#define ICF_CAUSE_NULL_SHORT_STRING                 ICF_ERROR_START_VALIDATION+18

#define ICF_CAUSE_INVALID_STR_LEN                   ICF_ERROR_START_VALIDATION+19

#define ICF_CAUSE_NULL_STRING                       ICF_ERROR_START_VALIDATION+20

#define ICF_CAUSE_LINE_ID_OUT_OF_RANGE              ICF_ERROR_START_VALIDATION+21

#define ICF_CAUSE_INVALID_TAG_TYPE                  ICF_ERROR_START_VALIDATION+22

#define ICF_CAUSE_NULL_MSG_BODY_LEN                 ICF_ERROR_START_VALIDATION+23

#define ICF_CAUSE_INVALID_MSG_BODY_LEN              ICF_ERROR_START_VALIDATION+24

#define ICF_CAUSE_TCP_ROUTE_TYPE_OUT_OF_RANGE       ICF_ERROR_START_VALIDATION+25

#define ICF_CAUSE_FAX_VER_OUT_OF_RANGE              ICF_ERROR_START_VALIDATION+26

#define ICF_CAUSE_INVALID_ERROR_CORR_VALUE          ICF_ERROR_START_VALIDATION+27

#define ICF_CAUSE_INVALID_DURATION_VALUE            ICF_ERROR_START_VALIDATION+28

#define ICF_CAUSE_INVALID_CODEC_NUM                 ICF_ERROR_START_VALIDATION+29

#define ICF_CAUSE_INVALID_IPV6_ADDR                 ICF_ERROR_START_VALIDATION+30

#define ICF_CAUSE_INVALID_VALUE_FOR_MATCH_TYPE      ICF_ERROR_START_VALIDATION+31

#define ICF_CAUSE_FILTER_COUNT_MISMATCH             ICF_ERROR_START_VALIDATION+32

#define ICF_CAUSE_INVALID_BUFFER_LEN                ICF_ERROR_START_VALIDATION+33

#define ICF_CAUSE_NULL_BUFFER_LEN                   ICF_ERROR_START_VALIDATION+34

#define ICF_CAUSE_VALUE_NOT_DEFINED                 ICF_ERROR_START_VALIDATION+35

#define ICF_CAUSE_INVALID_DOMAIN_ADDR               ICF_ERROR_START_VALIDATION+36

#define ICF_CAUSE_INVALID_IPV4_ADDR                 ICF_ERROR_START_VALIDATION+37

#define ICF_CAUSE_INVALID_ADDR_TYPE                 ICF_ERROR_START_VALIDATION+38

#define ICF_CAUSE_INVALID_TRANSPORT_MODE            ICF_ERROR_START_VALIDATION+39

#define ICF_CAUSE_INVALID_VALUE_FOR_RESPONSE_CODE ICF_ERROR_START_VALIDATION+40

#define ICF_CAUSE_VALUE_OUT_OF_RANGE               ICF_ERROR_START_VALIDATION+41

#define ICF_CAUSE_INVALID_MEDIA_TYPE               ICF_ERROR_START_VALIDATION+42

#define ICF_CAUSE_INVALID_COUNT                     ICF_ERROR_START_VALIDATION+43

#define ICF_CAUSE_INVALID_REGISTER_HEAD_START_TIMER ICF_ERROR_START_VALIDATION+44 
#define ICF_CAUSE_INVALID_LARGE_STRING_LEN          ICF_ERROR_START_VALIDATION+45
#define ICF_CAUSE_VALIDATION_FAILURE                ICF_ERROR_START_VALIDATION+46
#define ICF_CAUSE_INVALID_ADDR_STRING               ICF_ERROR_START_VALIDATION+47
#define ICF_CAUSE_INVALID_METHOD_TYPE               ICF_ERROR_START_VALIDATION+48
#define ICF_CAUSE_AUTH_RESP_MISSING                 ICF_ERROR_START_VALIDATION+49
#define ICF_CAUSE_ERROR_CAUSE_MISSING               ICF_ERROR_START_VALIDATION+50
#define ICF_CAUSE_AUTS_TOKEN_MISSING                ICF_ERROR_START_VALIDATION+51
#define ICF_CAUSE_INVALID_PRACK_VALUE               ICF_ERROR_START_VALIDATION+52
#define ICF_ERROR_VALIDATION_END                    ICF_ERROR_START_VALIDATION+52

/* This error cause is given to application if the boolean for reg event 
 * subscription support is already configured and ICF_SET_CALL_PARAMS_REQ API
 * is fired again to change its value.
 */

#define ICF_CAUSE_REGISTRATION_PROCEDURE_START         ICF_ERROR_VALIDATION_END  
    
#define ICF_CAUSE_REG_EVENT_SUBS_ALREADY_CONFIGURED    ICF_CAUSE_REGISTRATION_PROCEDURE_START + 1
#define ICF_CAUSE_REG_ROUTE_NOT_REQD                   ICF_CAUSE_REGISTRATION_PROCEDURE_START + 2

/* This error cause is given to application if the challenge parameters
 * are malformed (no nonce parameter received or extraction of
 * RAND/AUTN values fail) in case of AKA challenge method 
 */
#define ICF_CAUSE_INVALID_AUTH_PARAM                    ICF_CAUSE_REGISTRATION_PROCEDURE_START + 3
/*This error code will be set , when in IMS mode user is not registered 
  and we try to make some outgoing or incoming call*/
#define ICF_CAUSE_USER_NOT_REGISTERED                   ICF_CAUSE_REGISTRATION_PROCEDURE_START + 4
/* This error cause will be sent to the application in register_status_ind API
 * to indicate failure of reg event subscription.
 */
#define ICF_CAUSE_REG_EVENT_SUBS_FAILED                 ICF_CAUSE_REGISTRATION_PROCEDURE_START + 5
/* This error cause will be sent to application in subscription_status_ind
 * if implicit reg event subscription is enabled and application sends an explicit SUBSCRIBE
 * request for reg event package.
 */
#define ICF_CAUSE_IMPLICIT_REG_EVENT_SUBS_ENABLED       ICF_CAUSE_REGISTRATION_PROCEDURE_START +6
#define ICF_CAUSE_REGISTRATION_PROCEDURE_END            ICF_CAUSE_REGISTRATION_PROCEDURE_START + 6     
    
/*---------------------------------------------------------------------------*/

/* Error codes for Secondary Server and DHCP Support */

#define ICF_ERROR_START_SEC_SERVER_DHCP	               ICF_CAUSE_REGISTRATION_PROCEDURE_END   
 	
#define ICF_CAUSE_SAME_PRIMARY_AND_SECONDARY_PROXY_ADDR   ICF_ERROR_START_SEC_SERVER_DHCP+1
#define ICF_CAUSE_PROXY_SERVER_NOT_RESPONDING             ICF_ERROR_START_SEC_SERVER_DHCP+2
#define ICF_CAUSE_PRIMARY_PROXY_NOT_CONFIGURED            ICF_ERROR_START_SEC_SERVER_DHCP+3
#define ICF_CAUSE_SECONDARY_PROXY_NOT_CONFIGURED          ICF_ERROR_START_SEC_SERVER_DHCP+4
#define ICF_CAUSE_SECONDARY_PROXY_CONFIGURED              ICF_ERROR_START_SEC_SERVER_DHCP+5
#define ICF_CAUSE_PROXY_ADDR_ALREADY_CONFIGURED           ICF_ERROR_START_SEC_SERVER_DHCP+6
#define ICF_CAUSE_SECONDARY_PROXY_ADDR_ALREADY_CONFIGURED ICF_ERROR_START_SEC_SERVER_DHCP+7
#define ICF_CAUSE_DNS_SERVER_NOT_RESPONDING               ICF_ERROR_START_SEC_SERVER_DHCP+8
#define ICF_CAUSE_PRIMARY_DNS_SERVER_NOT_CONFIGURED       ICF_ERROR_START_SEC_SERVER_DHCP+9
#define ICF_CAUSE_SAME_PRIMARY_AND_SECONDARY_DNS_SERVER_ADDR \
                                                          ICF_ERROR_START_SEC_SERVER_DHCP+10
#define ICF_CAUSE_REGISTRAR_ADDR_NOT_RECVD                ICF_ERROR_START_SEC_SERVER_DHCP+11
#define ICF_CAUSE_SAME_PRIMARY_AND_SECONDARY_REGISTRAR_ADDR \
                                                          ICF_ERROR_START_SEC_SERVER_DHCP+12
#define ICF_CAUSE_REGISTRAR_NOT_RESPONDING                ICF_ERROR_START_SEC_SERVER_DHCP+13
#define ICF_CAUSE_PRIMARY_REGISTRAR_NOT_CONFIGURED        ICF_ERROR_START_SEC_SERVER_DHCP+14
#define ICF_CAUSE_SECONDARY_REGISTRAR_CONFIGURED          ICF_ERROR_START_SEC_SERVER_DHCP+15
#define ICF_CAUSE_FAILURE_RESPONSE_FROM_DHCP_SERVER       ICF_ERROR_START_SEC_SERVER_DHCP+16
#define ICF_CAUSE_DHCP_FAILURE                            ICF_ERROR_START_SEC_SERVER_DHCP+17
#define ICF_CAUSE_DHCP_SERVER_ADDR_ALREADY_CONFIGURED     ICF_ERROR_START_SEC_SERVER_DHCP+18
#define ICF_CAUSE_DHCP_SERVER_NOT_RESPONDING              ICF_ERROR_START_SEC_SERVER_DHCP+19
#define ICF_CAUSE_CANNOT_DELETE_DHCP_SERVER_ADDR          ICF_ERROR_START_SEC_SERVER_DHCP+20
#define ICF_CAUSE_REGISTRAR_ALREADY_CONFIGURED            ICF_ERROR_START_SEC_SERVER_DHCP+21
#define ICF_CAUSE_SEC_REGISTRAR_ALREADY_CONFIGURED        ICF_ERROR_START_SEC_SERVER_DHCP+22
#define ICF_CAUSE_SECONDARY_REGISTRAR_NOT_CONFIGURED      ICF_ERROR_START_SEC_SERVER_DHCP+23
#define ICF_CAUSE_INCONSISTENT_ACTIONS_FOR_PROXY_CONFIGURATION \
                                                          ICF_ERROR_START_SEC_SERVER_DHCP+24
#define ICF_CAUSE_INCONSISTENT_ACTIONS_FOR_REGISTRAR_CONFIGURATION \
                                                          ICF_ERROR_START_SEC_SERVER_DHCP+25
#define ICF_CAUSE_DHCP_CLIENT_PORT_BIND_FAILURE           ICF_ERROR_START_SEC_SERVER_DHCP+26
#define ICF_CAUSE_DHCP_AND_PROXY_COMBINED                 ICF_ERROR_START_SEC_SERVER_DHCP+27

#define ICF_CAUSE_SELF_ADDRESS_NOT_CONFIGURED             ICF_ERROR_START_SEC_SERVER_DHCP+28

#define ICF_CAUSE_DNS_SERVER_ADDRESS_MODIFICATION_NOT_ALLOWED  ICF_ERROR_START_SEC_SERVER_DHCP+29
#define ICF_ERROR_END_SEC_SERVER_DHCP                     ICF_CAUSE_DNS_SERVER_ADDRESS_MODIFICATION_NOT_ALLOWED

#define ICF_MISCELLENEOUS_ERROR_START                     ICF_ERROR_END_SEC_SERVER_DHCP
/* Error to indicate that the port has returned invalid response type (sync or async) for
 * authentication response */
#define ICF_CAUSE_INVALID_AUTH_RESP_STATUS                ICF_MISCELLENEOUS_ERROR_START + 1
/* Rel 8.1: IPTK will reject ICF_CALL_MODFY_REQ API with the following error_cause
   if ICF_CALL_MODIFY_REQ API is received in early dialog and offer answer
   is not yet completed. 
*/   
#define ICF_CAUSE_OFFER_ANSWER_NOT_COMPLETED              ICF_MISCELLENEOUS_ERROR_START + 2
#define ICF_CAUSE_SESSION_TOGGLE_REQ_ALREADY_ISSUED       ICF_MISCELLENEOUS_ERROR_START + 3 
#define ICF_CAUSE_INVALID_SESSION_TOGGLE_REQ              ICF_MISCELLENEOUS_ERROR_START + 4 
    /* This error cause is given to the application when ICF_GENERIC_MSG_REQ
     * API is received and call is not connected or signalling ongoing is not set to invalid 
     */
#define ICF_CAUSE_GENERIC_MSG_REQ_NOT_ALLOWED             ICF_MISCELLENEOUS_ERROR_START + 5
    /* This error cause is given to the application when ICF_GENERIC_MSG_REQ
     * API is received and the previous request is still pending.
     */
#define ICF_CAUSE_GENERIC_MSG_REQ_ALREADY_PENDING         ICF_MISCELLENEOUS_ERROR_START + 6
   
    /* This error cause is given to the application when ICF_GENERIC_MSG_REQ
    * API is received and transaction timeout occurs and generic call clear is
      triggered by SSA towards CC.
    */
#define ICF_CAUSE_GENERIC_MSG_REQ_INTERNAL_FAILURE         ICF_MISCELLENEOUS_ERROR_START + 7

/* This error cause is given to the application when the session expire value
 * in not provided by application in ICF_SESSION_TIMER_TOGGLE_REQ API.*/     
#define ICF_CAUSE_SESSION_EXPIRE_NOT_PRESENT   ICF_MISCELLENEOUS_ERROR_START + 8  
    
/* This error cause is given to the application when the Min-SE value
 * in not provided by application in ICF_SESSION_TIMER_TOGGLE_REQ API.*/     
#define ICF_CAUSE_MINSE_NOT_PRESENT            ICF_MISCELLENEOUS_ERROR_START + 9   
    
/* This error cause is given to the application when the Refresher value
 * in not provided by application in ICF_SESSION_TIMER_TOGGLE_REQ API.*/        
#define ICF_CAUSE_REFRESHER_NOT_PRESENT        ICF_MISCELLENEOUS_ERROR_START + 10   
    
/* This error cause is given to the application when the session expire value
 * provided by application in ICF_SESSION_TIMER_TOGGLE_REQ API is greater than
 * the session expire value in initial request or minse value is greater than
 * Session expire value in TOGGLE API send for incoming call.*/    
#define ICF_CAUSE_INVALID_SESSION_EXPIRE_VALUE ICF_MISCELLENEOUS_ERROR_START + 11   
    
/* This error cause is given to the application when the Min-SE value
 * provided by application in ICF_SESSION_TIMER_TOGGLE_REQ API is greater than
 * the Min-SE value in initial request or minse value is less than 90 when
 * TOGGLE API is send for incoming call.*/      
#define ICF_CAUSE_INVALID_MINSE_VALUE          ICF_MISCELLENEOUS_ERROR_START + 12   

#define ICF_MISCELLENEOUS_ERROR_END            ICF_MISCELLENEOUS_ERROR_START + 13     

/* Add last ecode */
#define ICF_MAX_NUM_OF_ERROR_IDS               ICF_MISCELLENEOUS_ERROR_END


#define ICF_CAUSE_EXTERNAL_MAX_LIMIT           ICF_MAX_NUM_OF_ERROR_IDS


#ifdef __cplusplus

}

#endif /* __cplusplus */

#endif /*__ICF_ERROR_ID_H__*/

