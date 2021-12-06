/******************************************************************************
*                                    
* FILE NAME    : icf_api.h                
*                                    
* DESCRIPTION  : Contains the definitions for the structures used in IMS CLIENT
*                  FRAMEWORK APIs.    
*                                    
* Revision History :                            
*
*  DATE            NAME                        REFERENCE       REASON        
* ------         ------------                  ---------     ----------
* 22-JUL-2005      Ram Narayan/Shekhar        None           Initial
* 02-Feb-2006      Amit Sharma                               CFG merged with ICF
* 																2.0
* 08-Feb-2006  Amit Sharma               Network PDU Logging API from ICF
* 07-Mar-2006	   Anuradha Gupta							Added new APIs for 
* 															Reinvite Handling
* 30-Mar-2006  Anuradha Gupta				ICF 5.0         Call Modify Feature 
* 															changes
* 02-Apr-2006  Amit Sharma               Updation for API doc3.1
* 07-Aug-2006  Amit Sharma               Added call forwarded ind
*                                        and updated local_user_alerted
*
* 29-Nov-2006  Deepti Goyal         ICF Rel 6.2         Changes for set_call
* 15-Dec-2006  Amit Sharma                              Updation for set_trans_param
*                                                       params API.
* 03-Jan-2007  Amit Mahajan         ICF Rel 6.2         INFO confirmation API added. 
* 04-Jan-2007  Priyanka Dua         ICF 6.3             Changes for set_call
*                                                       params API(multiple_answer_enable).
* 15-Jan-2007  Abhishek Dhammawat   ICF 6.3             Changes for Per Line Feature
* 23-Mar-2007  Deepti Goyal         ICF 6.4             Changes for Media_Connect_Req
*                                                       API
* 24-Mar-2007  Rajat Chandna                            Changes for response code
*                                                       enhancement.
* 26-Mar-2007  Rajat Chandna                            Changes for update/reinvite
*                                                       enhancement.
* 04-Apr-2007  Rajat Chandna                            Changes for wildcarded user
*                                                       enhancement.
* 08-May-2007  Abhishek Dutta                           Changes for remote cta cfm
* 15-May-2007  Sudhesh Singh                            Changes for early call
*                                                       transfer
* 14-Jun-2007  Alok Tiwari                              Changes for get 
*                                                       register status request
*                                                       and response.
* 09-Jul-2007  Anuradha Gupta	   ICF 7.0              Initial release specific changes
* 13-Jul-2007 Abhishek Dhammawat   Rel7.0               Addtion for  xconf ftr.
* 27-Aug-2007  Deepti Goyal     SPR 15997               Line id added in 
*                                                       ICF_CONFIGURE_CFM API
* 16-Jan-2008  Neha Gupta          SPR 18033		New API added for func
*							failure simulation for 
*							UT.
* 16-Jan-2008   Amit Sharma     ICF 8.0 LLD             Enhancements for Rel8.0
* 14-Feb-2008   Tarun Gupta     IPTK Rel 8.0 LLD        Enhancements for Rel8.0
* 14-Feb-2008   Tarun Gupta     IPTK Rel 8.0 LLD        Enhancements for Rel8.0
* 14-Mar-2008   Rajiv Kumar     IPTK Rel 8.0            Enhancements for Rel8.0
*                                                       New field retry-after
*                                                       added in register
*                                                       status indicataion
* 06-Mar-2008  Vipul Varshney       SPR 18122           AKA Enhancements
* 24-Mar-2008   Tarun Gupta     IPTK Rel 8.0            Merged User Param and
*                                                       Dynamic Payload Enhancements
* 28-Mar-2008  Sumant Gupta      ICF 8.0                Merging of Publish & Message
* 25-Apr-2008  Tarun Gupta       SPR 18483              Modified comments.
* 30-May-2008  Tarun Gupta       SPR 18585              Changed name of API from icf_remote_user_term_call_resp to icf_remote_user_term_call_resp_st
* 07-Jun-2008  Amit Sharma       IPTK 8.0 SRTP LLD      SRTP Enhancements
* 13-Jun-2008  Tarun Gupta       SPR 18585              Modified icf_set_line_param_req_st and icf_set_call_params_req_st
* 25-Jun-2008 Abhishek Dhammawat IPTK Rel8.0            Precondition/P-Hdr 
*                                                       Enhancements
* 07-July-2008 Anurag Khare      SPR 18684              Bitmask added in set_call_params 
*                                                       for stale and refresh method
* 26-Nov-2008  Tarun Gupta       SPR 19218              Merged CSR 1-6200296
* 04-Dec-2008  Tarun Gupta       SPR 19218              Merged CSR 1-6178201
* 08-Dec-2008  Rajiv Kumar       SPR 19218              Merged CSR 1-6431768
* 15-Dec-2008  Tarun Gupta       SPR 19218              Merged CSR 1-5478785
* 30-Jan-2009  Rajiv Kumar       IPTK Rel8.1            Changes done for testing UATK
*                                                       API under ICF_UT_TEST flag
* 06-Feb-2009  Tarun Gupta       Rel 8.1 LLD            SDP Tunnelling Enhancements
* 16-Feb-2009  Anurag Khare      Rel 8.1                Call modify Enhancements
* 18-Feb-2009  Anurag Khare      REl 8.1                Call mod enhancements
* 13-Mar-2009  Tarun Gupta       Rel 8.1                Modified icf_early_incoming_call_ind_st
* 15-Mar-2009  Anuradha Gupta    Rel 8.1                API changes for Timer Enhancements
* 18-Mar-2009  Alok Tiwari       Rel 8.1                API changes for REGISTRATION
*                                                       Enhancement(Multiple Contact feature)
* 30-Mar-2009  Anurag Khare      Rel 8.2                API changes for PRACK Enhancements
* 30-Mar-2009  Abhishek Dhammawat Rel 8.2               REFER/NOTIFY enhancements changes
* 30-Mar-2009  Alok Tiwari       Rel 8.2                API changes for 
*                                                       REGISTRATION Enhancement
*                                                       (Security Association)
* 30-Mar-2009  Anuradha Gupta    Rel 8.2                API changes for Reg / Call Enhancements
* 30-Mar-2009  Ashutosh Mohan    Rel 8.2                Modified
*                                                       icf_register_req_st, icf_register_cfm_st, 
*                                                       icf_create_call_req_st
* 14-Apr-2009  Rajiv Kumar       Rel 8.2                Modified
*                                                       icf_register_req_st,icf_prack_resp_recv_ind_st 
* 15-Apr-2009 Abhishek Dhammawat SPR 19441              modified
*                                                       ICF_MEDIA_CONNECT_IND API
* 18-May-2009  Anuradha Gupta    SPR 19672              CSR Merging, modified icf_set_call_param_req
* 21-May-2009  Anuradha Gupta    SPR 19672              CSR Merging, modified icf_set_call_param_req
* 26-May-2009  Anuradha Gupta    SPR 19672              Merged CSR 1-6667668 
* 26-May-2009  Anuradha Gupta    SPR 19672              Merged CSR 1-6727350
* 28-May-2009  Anuradha Gupta    SPR 19672              Merged CSR 1-7047249 
* 28-May-2009  Tarun Gupta       Rel 8.2                Async NOTIFY Support
* 28-May-2009  Ashutosh Mohan    SPR 19672              Merged CSR-1-6976670 
* 29-May-2009  Kamal Ashraf      SPR 19672              CSR_1_7113139 Merged
* 31-May-2009  Preksha           Rel 8.2                Asynchronus Message enh
* 18-Jun-2009  Anuradha Gupta    SPR 19752              modified icf_set_call_param_req
* 19-Jun-2009  Anuradha Gupta    SPR 19746              modified comment in
*                                                        icf_set_call_param_req
* 03-Jul-2009  Anuradha Gupta    SPR 19754              modified 
*                                                        icf_incoming_call_modify_ind_st
* 27-Jul-2009  Tarun Gupta       SPR 19886              Merged CSR 1-7009954
* 03-Aug-2009  Tarun Gupta       SPR 19886              Merged CSR 1-7193955
* 03-Aug-2009  Tarun Gupta       SPR 19886              Merged CSR 1-7334184
* 06-Aug-2009  Tarun Gupta       SPR 19886              Merged CSR 1-7402396
* 04-Sep-2009  Preksha           SPR 19999              Merged CSR 1-7586154
* 08-Sep-2009  Anuradha Gupta    SPR 19999              Merged CSR 1-7533733
* 11-Sep-2009  Rajiv Kumar       SPR 19999              Merged CSR 1-7547597
* 12-Sep-2009  Rajiv Kumar       SPR 19999              Merged CSR 1-7467002
* 16-Sep-2009  Rajiv Kumar       SPR 19999              Merged CSR 1-7615966
* 23-Sep-2009  Tarun Gupta       SPR 20063              Merged CSR 1-7616406
* 23-Oct-2009  Anurag Khare      SPR 20172              Fix for SPR 10172
* 25-May-2010  Preksha           SPR 20412              Merged CSR 1-8389294
* 27-may-2010  Preksha           SPR 20412              Merged CSR 1-8420460
* 29-May-2010  Alok Tiwari       SPR 20412              Merged CSR 1-8223807
* 9-Jul-2010   Udit Gattani      SPR 20517            Added is_sdp_received in
*                  
* 11-Oct-2010  Sachin sharma     SPR 20697             Fix for CSR 1-9012191.                                      icf_remote_user_alerted_ind_st
* 
* Copyright 2010, Aricent.                       
*                                    
*******************************************************************************/

#ifndef __ICF_API_H__
#define __ICF_API_H__

#include "icf_types.h"
#include "icf_defs.h"
#include "icf_mm_api.h"
#include "icf_tunnelled_media.h"


/* Prevent Name Mangling By C++ Compilers */

#ifdef __cplusplus

extern "C"
{
#endif /* __cplusplus */
    
#ifdef ICF_NW_ACTIVATE
/************************
*    NETWORK ACCESS APIs *
************************/
/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_network_activate_req_st
 *
 * Description: This API provides mechanism to activate Network access. For 
 *                example if the access network is a GPRS network, then this 
 *                API shall trigger PDP activation.
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* This specifies the access network type.This can be ICF_GPRS. Options related 
     * to other access network types shall be supported in future.
     */
    icf_uint8_t access_type;

    /* This specifies the parameters for accessing network. For example if access_type 
     * is ICF_GPRS then access_info is APN (Access Point Name).
     */
    icf_string_st access_info;

    icf_uint8_t       bit_mask;
#define ICF_NET_ACT_REQ_ROUTE_INFO_PRESENT	0x01

    /* routing_info contains the IPC information to reach application.*/
    icf_void_st routing_info;

} icf_network_activate_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_network_activate_cfm_st
 *
 * Description: This API is sent by ICF to the application in confirmation to
 *                ICF_NETWORK_ACTIVATE_REQ API.
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* This indicates the presence of the optional parameters. */
    icf_uint8_t bit_mask;

#define ICF_NET_ACT_CFM_ERR_CAUSE_PRESENT 0x01
#define ICF_NET_ACT_CFM_NUM_NW_PRESENT 0x02
#define ICF_NET_ACT_CFM_NW_INFO_PRESENT 0x04

    /* Denotes the Success or Failure status of the execution of the API */
    icf_result_t result;

    /* Denotes the error cause if the status of the API is Failure. */
    icf_error_t error_cause;

    /* Stores the number of network access specified in the nw_info list. */
    icf_uint8_t num_nw;

    /* List of activated network access. */
    icf_network_info_st nw_info[ICF_MAX_APN];

} icf_network_activate_cfm_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_network_deactivate_req_st
 *
 * Description: This API provides mechanism to de-activate Network access. For 
 *              example if the access network is a GPRS network, then this API 
 *              shall trigger PDP deactivation.
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* This is the logical PDP context id. */
    icf_uint32_t ctxt_id;

    icf_uint8_t			bit_mask;
#define ICF_NET_ACT_REQ_ROUTE_INFO_PRESENT	0x01

    /* routing_info contains the IPC information to reach application. */
    icf_void_st routing_info;

} icf_network_deactivate_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_network_deactivate_cfm_st
 *
 * Description: This API is sent by ICF to the application in confirmation to
 *                ICF_NETWORK_DEACTIVATE_REQ API
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* This indicates the presence of the optional parameters. */
    icf_uint8_t bit_mask;

#define ICF_NET_DEACT_CFM_ERR_CAUSE_PRESENT 0x01
#define ICF_NET_DEACT_CFM_NUM_NW_PRESENT 0x02
#define ICF_NET_DEACT_CFM_NW_INFO_PRESENT 0x04

    /* Denotes the Success or Failure status of the execution of the API. */
    icf_result_t result;

    /* Denotes the error cause if the status of the API is Failure. */
    icf_error_t error_cause;

    /* Stores the number of network access specified in the nw_info list. */
    icf_uint8_t num_nw;

    /* List of activated network access. */
    icf_network_info_st nw_info[ICF_MAX_APN];

} icf_network_deactivate_cfm_st;
#endif/*#ifdef ICF_NW_ACTIVATE*/


/************************

* APPLICATION SETUP APIs *

************************/

/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_app_add_req_st
 *
 * Description: This datatype is used to define a structure, which specifies the 
 *                payload data of the ICF_APP_ADD_REQ API.
 *-----------------------------------------------------------------------------*/
typedef struct
{
#define ICF_APP_ADD_MEDIA_PROFILE_PRESENT      0x01
	icf_uint8_t      bit_mask;
    /* This is an Application name, used for tracing purposes. */
    icf_string_st app_name;

    /* routing_info contains the IPC information to reach application. */
    icf_void_st routing_info ;

    /* ICF uses filter to decide the application corresponding to the 
     * message obtained from the network and where call_id field is not 
     * maintained by ICF.    
     */
    icf_filter_list_st filter;

    /* This field is a List of additional headers that the application wants 
     * to receive in the APIs from ICF. If the application doesn't require any 
	 * additional headers from the incoming SIP messages then count should be 
	 * set to zero in the icf_header_name_list_st    
    */
    icf_header_name_list_st header_name_list;

    /* List of SIP Methods which are supported by the application */
    icf_string_list_st  supported_methods;
    
    /* List of Events which are supported by the application */
    icf_string_list_st  supported_events;
    
    /* List of Content Types (Message Bodies) which are supported by the 
	 * application */
    icf_string_list_st  supported_content_types;
    
    /* List of message encodings supported by the application */
    icf_string_list_st  supported_encodings;

    /* List of Languages supported by the application */
    icf_string_list_st  supported_languages;

	/* ICF REL 6.0: multiple m lines
	 * the following structure defines the media profile for an application.
	 * ICF will save this information within its database and it is expected
	 * that the application uses only those codecs in any stream which have 
	 * been configured with MM (by the application). ICF will  not validate 
	 * this as it is not aware of the configured infomration. this is a list
	 * of the data type icf_stream_capab_st. This is an optional parameter
	 * in this structure. The media streams received in the app_profile will 
	 * determine the call_type bitmap in the app_conf within ICF
	 */
	icf_list_st				*p_media_profile;

	/* rtp_detection will be applicable only for the audio streams within the
	 * call */
	icf_boolean_t			rtp_detection_reqd;
    
    /*Application can set this boolean to enable ICF to send merge_media_req
     *before receiving remote media paramaters, if this flag is not set ICF
     *will send merge_media_req when it has received remote SDP*/
    icf_boolean_t                       merge_req_wo_rem_sdp;

} icf_app_add_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_app_add_cfm_st
 *
 * Description: This datatype is used to define a structure, which specifies the 
 *                payload data of the ICF_APP_ADD_CFM API.
 *-----------------------------------------------------------------------------*/
typedef struct
{
    /* This indicates the presence of the optional parameters. */
    icf_uint8_t bit_mask ;

#define ICF_APP_ADD_CFM_ERROR_CAUSE_PRESENT 0x01

#ifdef ICF_NW_ACTIVATE
    #define ICF_APP_ADD_CFM_NUM_NW_PRESENT 0x02
    #define ICF_APP_ADD_CFM_NET_INFO_PRESENT 0x04
#endif
    
    /* Denotes the Success or Failure status of the execution of the API. */
    icf_result_t result;

    /* Denotes the error cause if the status of the API is Failure. */
    icf_error_t error_cause;

#ifdef ICF_NW_ACTIVATE
    /* Stores the number of network access specified in the nw_info list. */
    icf_uint8_t num_nw;

    /* List of activated network access. */
    icf_network_info_st nw_info[ICF_MAX_APN];
#endif
    /* Public uri and P- Associated uri list */
/*    icf_pub_uri_list_node_st   *p_uri_list;*/

} icf_app_add_cfm_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_app_remove_req_st
 *
 * Description: This datatype is used to define a structure, which specifies the 
 *                payload data of the ICF_APP_REMOVE_REQ API.
 *-----------------------------------------------------------------------------*/
typedef struct
{
    /* This is for future use, currently coded as 0. */
    icf_uint32_t option ;

} icf_app_remove_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_app_remove_cfm_st
 *
 *    This datatype is used to define a structure, which specifies the 
 *    payload data of the ICF_APP_REMOVE_CFM API.
 *-----------------------------------------------------------------------------*/
typedef struct
{
    /* Denotes the Success or Failure status of the execution of the API. */
    icf_result_t result;

    /* Denotes the error cause if the status of the API is Failure.*/
    icf_error_t error_cause;

} icf_app_remove_cfm_st;

/************************
*    CONFIGURATION APIs *
************************/
/*-----------------------------------------------------------------------------
 * Structure Name: icf_set_self_id_req_st
 *
 * Description: This structure is used to specify payload data of
 *               API ICF_SET_SELF_ID_REQ
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
     icf_uint32_t                   bit_mask;
#define  ICF_SET_SLF_ID_PRM_ADDR_ACTION         0x01
#define  ICF_SET_SLF_ID_PRM_ADDR                0x02
#define  ICF_SET_SLF_ID_PRM_PRIORITY            0x04
#define  ICF_SET_SLF_ID_PRM_NAME                0x08
#define  ICF_SET_SLF_ID_PRM_DEFAULT_SETTINGS    0x10
#define  ICF_SET_SLF_ID_PRM_AUTH_KEY            0x20
#define  ICF_SET_SLF_ID_PRM_AUTH_PASSWORD       0x40
#define  ICF_SET_SLF_ID_PRM_REALM               0x80
#define  ICF_SET_SLF_ID_PRM_AUTH_PER_USER       0x100
     /* SPR 19886 : CSR_1-7009954 merged */ 
#define  ICF_SET_SLF_ID_PRM_REALM_PER_USER      0x200     

     /* line id for which the parameters present in this struct are applicable */
    icf_line_id_t                  line_id;

     /* action applicable for self_addr and self_name field */
     icf_config_action_t           action;

     /* user address for a line.In IMS mode it maps to public user 
      * identity */
     icf_address_st                self_addr;

     /* user name for a line */
     icf_string_st                 self_name;
     
     /* priority of user for this line */
     icf_priority_id_t             priority;

     /* Settings for a line */

#define ICF_SETTINGS_CONFIG_PRESENTATION_IND           0x01
   /* if ICF_SUPPORT_OUT_OF_DIALOG_NOTIFY_IGNORE_DIALOG_INFO is set then Notify 
    * will be given to application without matching its dialog.*/
#define ICF_SUPPORT_OUT_OF_DIALOG_NOTIFY_IGNORE_DIALOG_INFO 0x02

     icf_uint8_t                   default_settings;

     /* Contains the authentication key configured per line. */
     icf_string_st                 authentication_key;

     /* Contains the authentication password configured per line.*/
     icf_string_st                 authentication_password;

    /* Contains the realm_name configured per line */
     icf_string_st                 configured_realm;

} icf_set_self_id_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_set_transport_req_st 
 *
 * Description: This structure is used to specify payload data of
 *               API ICF_SET_TRANSPORT_REQ 
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
    /* This indicates the presence of the optional parameters. */

    icf_uint32_t                  bit_mask;

#define ICF_SET_TRP_REQ_PROXY_ADDR              0x01
#define ICF_SET_TRP_REQ_SLF_TRANSPORT_ADDRESS   0x02
#define ICF_SET_TRP_REQ_SLF_MODE                0x04
#define ICF_SET_TRP_REQ_SLF_PORT                0x08
    /*Bit will be set if self transport address is per line Once this bit
     *is set, it has to be set every time*/
#define ICF_SET_TRP_REQ_SLF_ADDR_PER_LINE       0x10
/* If this bit is enabled in the bit_mask then it means application wants to configure  
 * DNS port from where DNS queries will be issued.*/
#define ICF_SET_TRP_REQ_DNS_SRC_PORT             0x20

/* This bit will be set if secondary proxy address has been configured */
#define ICF_SET_TRP_REQ_SEC_PROXY_ADDR           0x40

/* This bit will be set if DNS Server address has been configured */
#define ICF_SET_TRP_REQ_DNS_SERVER_ADDR          0x80

/* This bit will be set if secondary DNS Server address has been configured */
#define ICF_SET_TRP_REQ_SEC_DNS_SERVER_ADDR      0x100

/*  If this bit is enabled in the bit_mask then it means
    application wants to configure DHCP Server*/
#define ICF_SET_TRP_REQ_DHCP_SERVER_ADDR         0x200

/*  If this bit is enabled in the bit_mask then it means 
    application wants to configure the DHCP Server port */
#define ICF_SET_TRP_REQ_DHCP_CLIENT_PORT         0x400

    /*SIP proxy IP address, configured per line*/
    icf_config_proxy_transport_address_st   proxy_addr;

    /*Self transport address and port, when transport addr not configured 
     * system call is used to obtain self transport addr*/

    icf_transport_addr_st               self_transport_address;

    /*Transport mode for incoming calls*/
    icf_transport_mode_t                   self_mode;

    /*Transport port for incoming calls*/
    icf_uint16_t                           self_port;

    /*Self transport address per line, will be used only if 
     * ICF_SET_TRP_REQ_SLF_ADDR_PER_LINE bit is set in bit_mask*/
    icf_config_transport_address_st   self_addr_per_line;
     /* Following variable will be containing dns port that application wants to configure. 
     * IPTK will send DNS query using this port.*/  
    icf_uint16_t                      dns_source_port;

    /*SIP secondary proxy address, configured per line*/
    icf_config_sec_transport_address_st   sec_proxy_addr;

    /*DNS server address and port, configured system-wide*/
    icf_transport_address_st               dns_server_addr;

    /*Secondary DNS server address and port, configured system-wide*/
    icf_transport_address_st               sec_dns_server_addr;

    /* Application can configure DHCP server IP and port to which DHCP query to 
    be sent. If this is not configured then IPTK will not do any DHCP query.
    If application wants to broadcast DHCP request then it has to configure 
    DHCP server address as broadcast IP address (255.255.255.255) */
    icf_transport_address_st 	     dhcp_server_addr; 
    
    /* Application can configure DHCP Client Port on which IPTK will listen for 
    DHCP responses. If this field is not configured, then IPTK shall use 
    default configured port  */
    icf_uint16_t		     dhcp_client_port;

} icf_set_transport_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_set_registration_req_st 
 *
 * Description: This structure is used to specify payload data of
 *               API ICF_SET_REGISTRATION_REQ 
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* line id for which the registration params are applicable */
    icf_line_id_t                  line_id;

    /* Action can be add, delete or modify.
     * If action is add then registrar add is mandatory. Other params are
     * optional.
     * If action is modify then registrar add is not present. Other params are
     * optional.
     * If action is delete, then no other param is required. All the reg data
     * for the line is deleted */
    icf_config_action_t            action;

    /* SIP registrar IP address. When action is add this field is mandatory
     * If is not received, the API will be rejected with error cause 
     * ICF_CAUSE_REGISTRAR_ADDR_NOT_RECVD */
    icf_transport_address_st       registrar_addr;

#define ICF_SET_REG_REQ_MODE            0x01
#define ICF_SET_REG_REQ_DURATION        0x02
#define ICF_SET_REG_REQ_ROUTE_ADDR      0x04

/* this bit mask will be used to send the registrion 
 * head start duration */
#define ICF_SET_REG_HS_DURATION		0x08

/* This bit shall be set when secondary registrar address is configured */
#define ICF_SET_REG_SEC_REGISTRAR	0x10

    icf_uint8_t                   bit_mask;
    
    /* transport mode for registration request */
    icf_transport_mode_t           reg_mode;
    
    /* duration, in milliseconds, of registration which is line specific */
    icf_duration_t                registration_duration;
	
	/* Number of seconds prior to expriation of 
 	* registration */
	icf_duration_t			register_head_start_timer;

    /* Indicates the next hop where the REGISTER request should be sent 
     * This will be set in the outgoing Route header.In IMS mode, if this 
     * field is configured, then the API will be rejected with error cause
     * ICF_CAUSE_REG_ROUTE_NOT_REQD.
     */
    icf_transport_address_st  	reg_route_addr;

    /* Secondary SIP registrar, configured per line */
    icf_config_sec_transport_address_st    sec_registrar_addr;

} icf_set_registration_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_set_call_params_req_st 
 *
 * Description: This structure is used to specify payload data of
 *               API ICF_SET_CALL_PARAM_REQ 
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
    /* This indicates the presence of the optional parameters. */
    icf_uint32_t        bit_mask;

#define ICF_SET_CALL_PRM_DEFAULT_SETTINGS                0x01
#define ICF_SET_CALL_PRM_QOS_MARK                        0x02    
#define ICF_SET_CALL_PRM_SETUP_TIMER                     0x04
#define ICF_SET_CALL_PRM_ALERTING_TIMER                  0x08
#define ICF_SET_CALL_PRM_RELEASE_TIMER                   0x10
#define ICF_SET_CALL_PRM_MODIFY_MEDIA_TIMER              0x20
#define ICF_SET_CALL_PRM_REGISTRATION_RESP_DURATION      0x40
#define ICF_SET_CALL_PRM_REGISTRATION_RETRY_DURATION     0x80

#ifdef ICF_SESSION_TIMER
#define ICF_SET_CALL_PRM_SESSION_TIMER_INTERVAL          0x0200
#define ICF_SET_CALL_PRM_MIN_SESSION_TIMER_INTERVAL      0x0400
#endif

#define ICF_SET_CALL_PRM_INFO_TIMER						 0x0800 	
#define ICF_SET_CALL_PRM_PHONE_INFO						 0x1000  
#define ICF_SET_CALL_PRM_OPTIONS_TIMER	            	 0x2000
#ifdef ICF_NAT_RPORT_SUPPORT
#define ICF_SET_BINDING_REFRESH_TIMER                    0x4000
#endif
#define ICF_SET_CALL_PRM_UPDATE_REQD	            	 0x8000
#define ICF_SET_CALL_PRM_EARLY_INC_IND_FOR_ALL_USERS     0x10000
#define ICF_SET_CALL_PRM_MULTIPLE_ANSWER_ENABLE          0x20000
#define ICF_SET_CALL_PRM_DNS_MIN_TIMER                   0x40000
#define ICF_SET_CALL_PRM_DNS_MAX_TIMER                   0x80000
    
#ifdef ICF_SESSION_TIMER
#define ICF_SET_CALL_PRM_SESSION_TIMER_ENABLE            0x100000
#define ICF_SET_CALL_PRM_SESSION_REFRESHER               0x200000
#define ICF_SET_CALL_PRM_SESSION_TIMER_LOGIC             0x400000
#endif

/*  Bit mask to check that Max call per line is present in set call params or not */
#define ICF_SET_CALL_PRM_MAX_ACTIVE_CALLS_PER_LINE       0x800000

/*  If this bit is enabled in the bit_mask it means Application
    wants to configure the DHCP Response timer value   */
#define ICF_SET_CALL_PRM_DHCP_RESPONSE_TIMER	  	0x1000000

/*If this bit is enabled in the bitmask it means Application wants
 *to configure reg_event_subs_reqd*/
#define ICF_SET_CALL_PRM_REG_EVENT_SUBS_REQD            0x2000000

/*If this bit is enabled in the bitmask it means Application wants
 *to configure media_transport_type*/
#define ICF_SET_CALL_PRM_MEDIA_TYPE_REQD                0x4000000

/*Boolean corresponding to precondition_required flag*/ 
#define ICF_SET_CALL_PRM_PRECONDITION_REQD              0x8000000

/*This bitmask is added to check whether IPTK supports the                              
 *header p_access_network_info. */
#define ICF_SET_CALL_PRM_ACCESS_NW_INFO                 0x10000000

/*This bitmask is added to check whether application has
 *configured SRTP fallback flag or not*/
#define ICF_SET_CALL_PRM_SRTP_FALLBACK_FLAG             0x20000000
/*This bitmask is added to configure error response codes 
  which will trigger IPTK to do SRTP Fallback */ 
#define ICF_SET_CALL_PRM_SRTP_FALLBACK_RESP_CODES       0x40000000


/* 
 * The flag would be used by application to indicate that the 
 * the application does not want to modify the ignore_stale_param
 * parameter
 */
#define ICF_SET_CALL_PRM_STALE_PARAM_NOT_SET             0x80000000


/* This indicates the presence of the optional parameters. */
    icf_uint32_t        bit_mask_1;

#ifdef ICF_SESSION_TIMER
/* 
 * The flag would be used by application to indicate that the 
 * the application does not want to modify the session refresher 
 * method 
 */
#define ICF_SET_CALL_PRM_SESSION_REFRESH_METHOD_NOT_SET  0x00000001
#endif
/* This flag would be set by the Application when it wants to set some
 * value for its porting configuration parameter.
 */
#define ICF_SET_CALL_PRM_APP_PORT_CONFIG         		 0x00000002

/*  Bitmask for the optional field added port_to_be_sent_in_from_hdr */
#define ICF_SET_PORT_IN_FROM_HDR                                 0x00000004    
/*  This bitmask denotes presence of optional field early_incoming_session_ind_reqd */
#define ICF_SET_CALL_PRM_EARLY_INC_SESSION_IND_REQD 0x00000008

/* This flag would be used by application to indicate that the
 * application wants to send Re-invite/Update after receiving
 * 491 response of auto-reinvite/update.
 */
#define ICF_SET_CALL_PRM_RETRY_CODEC_COMMIT_REQ         0x00000010 

/*This flag would be set when IPTK should send ReINVITE after codec
 commit REINVITE */
#define ICF_SET_CALL_PRM_UPDATE_FOR_OFFERANSWER_AFTER_CONNECT 0x00000020

/*  Bitmask for the optional parameter app_connect_reqd_for_replaces */
#define ICF_SET_CALL_PRM_APP_CONNECT_REQD_FOR_REPLACES 	     0x00000040

/*  This bit denotes presence of optional field async_notify_support_reqd */
#define ICF_SET_CALL_PRM_ASYNC_NOTIFY_SUPPORT_REQD  0x00000080

/*This flag would be set when application wants IPTK to match newly received codec
 list from remote with the codec list received in previous (last) SDP. 
*/
#define ICF_SET_CALL_PRM_CHECK_REMOTE_CODEC_LIST	 0x00000100

/* CSR_1_7113139 Merged SPR 19672 Start */
/*This flag would be set when application wants IPTK to increment SDP 
version*/
#define ICF_SET_CALL_PRM_INC_SDP_VERSION_WHEN_NO_CHANGE	 0x00000200 
/* CSR_1_7113139 Merged SPR 19672 End */

/*  This bitmask denotes presence of optional field async_message_support_reqd */
#define ICF_SET_CALL_PRM_ASYNC_MESSAGE_SUPPORT_REQD      0x00000400

/* This flag would be set when Application need to receive ICF_OPTIONS_IND API	  directly on receiving out-of-dialog OPTIONS from peer without involving MM */
#define ICF_SET_CALL_PRM_DIRECT_OPTIONS_IND_REQD 	 0x00000800

    icf_uint16_t           default_settings;
#define ICF_CALL_CONFIG_CALL_THRU_SIP_PROXY              0x01
#define ICF_CALL_CONFIG_PRIVACY_HEADER_PRESENT           0x02
#define ICF_CALL_CONFIG_PRACK_REQD                       0x04
#define ICF_CALL_CONFIG_CALL_MODIFY_METHOD_UPDATE        0x08
#define ICF_CALL_CONFIG_EARLY_MEDIA_HDR_SUPPORTED        0x10
#ifdef ICF_SESSION_TIMER
#define ICF_SET_CALL_PRM_SESSION_REFRESHER_NOT_REQUIRED  0x20
#endif
/* This bit indicates whether the stale parameter in the 
   401/407 response has to be ignored or not.
   If it is set,IPTK will simply ignore the stale parameter
   in 401/407 challenge response and recalculate the response
   if there exists a new nonce value.
*/
#define ICF_IGNORE_STALE_PARAM_IN_CHALLENGE              0x40
#define ICF_CALL_CONFIG_SESSION_REFRESH_METHOD_UPDATE    0x80

/* This bit indicates whether application wants to send Update as 
 * session refresh even if allow header is not received from remote
 * this will be used only if ICF_CALL_CONFIG_SESSION_REFRESH_METHOD_UPDATE
 * is set i.e session refresh method as Update is specified by the application
 * either in set call params or in set line params.
 */
#define ICF_CALL_CONFIG_SESSION_REFRESH_METHOD_STRICT_UPDATE    0x0100

/*This bit indicates whether application wants UPDATE/REINVITE
* for fax call. If not set then default is ReINVITE method 
*/ 
#define ICF_CALL_CONFIG_FAX_REQUEST_METHOD_UPDATE        0x0200    

/* This bit indicates whether the headers present in incoming
 * requests should be strictly parse as per grammer defined 
 * in RFC-3261.
 */ 
#define ICF_CALL_CONFIG_ENABLE_STRICT_PARSING            0x0400

/*  This bit indicates whether the non-mandatory headers present in incoming
 *  request/response should be ignored.*/
#define ICF_CALL_CONFIG_HANDLE_NON_MANDATORY_MALFORMED_HEADER            0x0800


    icf_qos_mark_t        qos_mark;

    icf_duration_t        setup_timer ;

    icf_duration_t        alerting_timer ;

    icf_duration_t        release_timer ;

    icf_duration_t        modify_media_timer ;

    icf_duration_t        registration_resp_timer ;

    icf_duration_t        registration_retry_timer ;

	icf_duration_t		  info_timer;

	icf_duration_t		  options_timer;

	icf_string_st		  phone_info;

#ifdef ICF_SESSION_TIMER
     icf_duration_t       session_timer;

     icf_duration_t       min_se;
     
     /* Following boolean 'session_timer_enable is added in this structure that   
      * will be indicate whether session timer needs to be enabled or not. If it is 1 then session  
      *  timer feature should be enabled, if it 0 then session timer needs to be disabled.
      */
     icf_boolean_t               session_timer_enable;

     /*
      * A new variable will be added in that will specify the refresher whether it is uac, uas or    
      * none. Through this, application can configure the refresher. This variable will be   
      * checked only if ICF_SET_CALL_PRM_SESSION_REFRESHER bitmask is set.
      * As this API will be fired, IPTK will update session refresher on each line as specified 
      * by application.  
      */
     icf_refresher_type_t        session_refresher;


     /* This bitmask specifies the timer logic for starting session timer when IPTK is
      * acting as UAS. 
      */
     icf_boolean_t               session_timer_logic; 
#endif
#ifdef ICF_NAT_RPORT_SUPPORT
     icf_duration_t       binding_refresh_timer;
     icf_boolean_t        binding_query_enable;
#endif

     icf_boolean_t        multiple_answer_enable;
     icf_duration_t          dns_min_retrans;
     icf_duration_t          dns_max_retrans;

     icf_uint8_t          update_reqd;
#define ICF_UPDATE_WHN_OFFER_SDP_WITH_MULTIPLE_CODEC_COMMIT     0
#define ICF_NO_UPDATE_WHN_ANSWER_SDP_WITH_SINGLE_CODEC_COMMIT   1
#define ICF_NO_UPDATE                                           2
#define ICF_UPDATE_WHN_OFFER_SDP_WITH_MULTIPLE_CODEC            3
#define ICF_NO_UPDATE_WHN_ANSWER_SDP_WITH_SINGLE_CODEC          4      

    icf_boolean_t         early_inc_ind_for_all_users;
    
    /* Maximum number of calls that can be in active state 
      at a time */
    icf_uint8_t             max_active_calls_per_line;   

/*  The DHCP Response Timer value configured by Application */
    icf_duration_t	    dhcp_response_timer; 

    /* This Boolean is used to indicate whether the application wants 
     * reg event package support. By default it is set to TRUE in case 
     * of IMS mode and is set to FALSE in case of Non IMS mode.
     * This boolean can be set only once during init time.
     * If this boolean is set and this API is fired again
     * to change the value of this boolean, the API will be rejected with
     * error cause ICF_CAUSE_REG_EVENT_SUBS_ALREADY_CONFIGURED.*/
    icf_boolean_t                reg_event_subs_reqd;

    /*THis parameter is used to configure SRTP support in IPTK*/
    icf_media_transport_mode_et  media_transport_type;

    /* Boolean identifies whether QOS precondition is supported at system level or not. 
     *If it is set to 1 then precondition support is ON else OFF.*/
    icf_boolean_t         precondition_required;

    /*This parameter is used to fill access nw info in outgoing messages*/
    icf_string_st         access_network_info;
    
    /*This flag is used to tell IPTK whether application wants to
     *do fallback to RTP_AVP if SRTP media prfoile has been 
     rejected by remote*/
    icf_boolean_t         srtp_fallback_reqd;

    /*This list is used to configure failure response code
     *on which IPTK is required to do SRTP fallback to RTP_AVP*/
    icf_list_st           *p_srtp_fallback_resp_codes;
	/* This parameter specifies an Application desired porting configuration
	 * parameter. IPTK will not use this parameter; it will simply pass this 
	 * parameter to the porting functions at Application's disposal.
	 */
	icf_uint16_t			app_port_config;    

    /*  This field will indicate that self port would be sent in subsequent 
    requests or Not
    True: means port should be sent
    false: Port should not be sent 
*/
    icf_boolean_t          port_to_be_sent_in_from_hdr;

    /* This indicates that the application wants early session indication for
       all incoming INVITE and incoming out of dialog OPTIONS requests. This field
       over rides the existing field early_inc_ind_for_all_users.
    */
    icf_boolean_t early_incoming_session_ind_reqd;



    /* This is an optional field which would be used by application to
    * indicate that the application wants to send Re-invite/Update after
    * receiving 491 response of auto-reinvite/update.
    */
    icf_boolean_t         retry_codec_commit_req;

    /* This parameter specifies that IPTK should send REINVITE 
	 * for the codec committed in case codec negotiation takes place
	 * through a reinvite
     */
	icf_boolean_t 			update_for_offeranswer_after_connect;

    /* This parameter indicates whether IPTK should directly send 200 OK for 
	 * INVITE with Replaces and create the media session, or present INVITE with
	 * Replaces as a normal incoming call and wait for APP request to connect 
	 * the call.
	 * -  ICF_TRUE means call will be connected on getting ICF_CONNECT_REQ.
	 * -  ICF_FALSE means call will be connected by IPTK.
	 * Default value for this boolean is ICF_FALSE.
	 */
	icf_boolean_t			app_connect_reqd_for_replaces;
    
    /* 
       This field indicates that the application wants to enable support of
       asynchronous NOTIFY for SUBSCRIBE.
	   
       -  ICF_TRUE means application wants to enable support of
          asynchronous NOTIFY.
	   -  ICF_FALSE means application wants to disable support of
          asynchronous NOTIFY.
     	  Default value for this boolean is ICF_FALSE.
    */
    icf_boolean_t async_notify_support_reqd;
    
    /*This parmeter specifies whether the newly received codec list 
      from remote needs to be checked against the codec
      list received in previous (last) SDP
     */

    icf_boolean_t    check_remote_codec_list;

    /* CSR_1_7113139 Merged SPR 19672 Start */
    /*This parmeter specifies whether SDP version should be incremented
    by IPTK in case of session refresh Re-INVITE with SDP or in 200 OK 
    with SDP when version number in request was same as previous version
    recieved from peer.*/	

    icf_boolean_t 			inc_sdp_version_when_no_change;
    /* CSR_1_7113139 Merged SPR 19672 End */

    /* New Code for ASYNCHRONUS_MESSAGE enhancements*/
    /* 
       This field indicates that the application wants to enable support of
       asynchronous MESSAGE.
       async_message_support_reqd = 1 : Asynchronus Message Support Enabled
       async_message_support_reqd = 0 : Asynchronus Message Support Disabled
       By default Asynchronus Message Support is Disabled 

     */
    icf_boolean_t async_message_support_reqd;
	/* This parameter specifies when Application need to receive ICF_OPTIONS_IND API    
	     directly on receiving out-of-dialog OPTIONS from peer without involving MM */
	icf_boolean_t direct_options_ind_reqd;     

} icf_set_call_params_req_st;

/*-----------------------------------------------------------------------------
 * 
 * Structure Name:icf_get_system_settings_req_st   
 * Description: This data type is used to define a structure, which contains 
 *              the request by application to fetch system settings.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{

    /* Whether ICF supports PRACK or not */
#define ICF_REQD_PRACK_ENABLED_STATUS                0x00000001
    
    /* Privacy is supported in SIP signaling or not */
#define ICF_REQD_PRIVACY_SUPPORTED                   0x00000004
    
    /* Maximum Lines supported by ICF */
#define ICF_REQD_MAX_LINES                           0x00000008
    
    /* The value of Setup Timer */
#define ICF_REQD_SETUP_TIMER                         0x00000010
    
    /* The value of Alerting Timer */
#define ICF_REQD_ALERTING_TIMER                      0x00000020
    
    /* The value of Release Timer */
#define ICF_REQD_RELEASE_TIMER                       0x00000040
    
    /* The value of Media Modify Timer */
#define ICF_REQD_MODIFY_MEDIA_TIMER                  0x00000080
    
    /* The value of Register response Timer */
#define ICF_REQD_REG_RESP_TIMER                      0x00000100
    
    /* The value of Register retry Timer */
#define ICF_REQD_REG_RETRY_TIMER                     0x00000200
    
    /* The value of Subscribe retry Timer */
#define ICF_REQD_SUBS_RETRY_TIMER                    0x00000400
    
    /* The value of Subscribe response Timer */
#define ICF_REQD_SUBS_RESP_TIMER                     0x00000800
    
    /* Whether signal compression is enabled in ICF */
#define ICF_REQD_SIG_COMP_STATUS                     0x00001000
    
    /* Whether security is enabled in ICF */
#define ICF_REQD_SECURITY_STATUS                     0x00002000
    
    /* What is the IP Address of ICF */
#define ICF_REQD_SELF_IP_ADDRESS                     0x00004000
    
    /* what is the list of Associated URIs list */
#define ICF_REQD_ASSO_URI_LIST                       0x00008000
    
    /* what is the list of APNs list */
#define ICF_REQD_APN_LIST                            0x00010000
    
    /* what is self transport_mode */
#define ICF_REQD_SELF_TRANSPORT_MODE                 0x00020000
    
    /* what is self port */
#define ICF_REQD_SELF_PORT                           0x00040000
    
    /* Whether call to be routed thru proxy */
#define ICF_REQD_CALL_THRU_PROXY_STATUS              0x00080000
    
    /* Whether SIP compact headers to be used */
#define ICF_REQD_SIP_COMPACT_HDR_STATUS              0x00100000
    
    /* what is QOS mark value*/
#define ICF_REQD_QOS_MARK                            0x00200000
    
    /* what is session interval timer duration */
#define ICF_REQD_SESSION_INTERVAL_TIMER              0x00400000
    
    /* what is minimum session interval timer duration */
#define ICF_REQD_MIN_SESSION_INTERVAL_TIMER          0x00800000
    
    icf_uint32_t                    bit_mask;

#ifdef ICF_NAT_RPORT_SUPPORT

#define ICF_REQD_BINDING_QUERY_ENABLED_STATUS         0x1000000
#define ICF_REQD_BINDING_REFRESH_TIMER                0x2000000

#endif
    
    /* Specifies the presence of the routing information */
    /* MSbit WILL BE SET FOR ROUTING info */
#define ICF_GET_SETTINGS_ROUTE_INFO_PRESENT          0x8000000
    icf_void_st                    routing_info;

} icf_get_system_settings_req_st; 

/*-----------------------------------------------------------------------------
 * 
 * Structure Name:icf_get_system_settings_resp_st   
 * Description: This data type is used to define a structure, which contains 
 *              the response to be sent 
 *              to application for system settings requested.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{

    /* Result of this API - Success of failure */
    /* MSbit WILL BE SET For Success  */
#define ICF_API_GET_SYS_STG_RESULT_SUCCESS    0x8000000

    icf_uint32_t                          bit_mask;

    icf_boolean_t                         prack_enabled;
    icf_boolean_t                         privacy_supported;
    icf_uint16_t                          max_lines;
    icf_duration_t                        setup_timer;
    icf_duration_t                        alerting_timer;
    icf_duration_t                        release_timer;
    icf_duration_t                        modify_media_timer;
    icf_duration_t                        registration_resp_timer;
    icf_duration_t                        registration_retry_timer;
    icf_duration_t                        subs_retry_timer;
    icf_duration_t                        subs_resp_timer;
    icf_boolean_t                         sig_comp_enabled;
    icf_boolean_t                         security_enabled;
    icf_transport_address_st              self_ip_address;
    icf_pub_uri_list_node_st              *p_uri_list;
    icf_apn_list_st                       apn_list;
    icf_transport_mode_t                  self_transport_mode;    
    icf_uint16_t                          self_port;            
    icf_boolean_t                         call_thru_proxy;        
    icf_boolean_t                         sip_compact_header;    
    icf_qos_mark_t                        qos_mark;
    icf_duration_t                        session_interval_timer;    
    icf_duration_t                        min_session_interval_timer;
#ifdef ICF_NAT_RPORT_SUPPORT
    icf_duration_t                        binding_refresh_timer;
    icf_boolean_t                         binding_query_enable;
#endif

} icf_get_system_settings_resp_st;

/*############################################################## */

/*-----------------------------------------------------------------------------
 * 
 * Structure Name:icf_get_line_settings_req_st   
 * Description: This data type is used to define a structure, which contains 
 *              the request by applications to fetch line settings of ICF.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* For current line, what is Proxy-CSCF's address */
#define ICF_REQD_PROXY_ADDR                             0x00000001
    
    /* For current line, what is Registrar's address */
#define ICF_REQD_REGISTRAR_ADDR                         0x00000002
    
    /* For current line, what is transfer mode (UDP/TCP/Both) */
#define ICF_REQD_PROXY_TRANSPORT_MODE                   0x00000004
    
    /* For current line, what is self address list */
#define ICF_REQD_SELF_ADDR_LIST                         0x00000008
    
    /* For current line, what is self name */
#define ICF_REQD_SELF_NAME                              0x00000010
    
    /* For current line, whether presentation is allowed */
#define ICF_REQD_PRESENTATION_STATUS                    0x00000020
    
    /* For current line, what is authentication key */
#define ICF_REQD_AUTH_KEY                               0x00000040
    
    /* For current line, what is authentication password */
#define ICF_REQD_AUTH_PASSWD                            0x00000080

    /* For current line, what is registration duration */
#define ICF_REQD_REG_MODE                               0x00000100

    /* For current line, what is registration duration */
#define ICF_REQD_REG_DURATION                           0x00000200

    /* For current line, what is the next hop for registration request */
#define ICF_REQD_REG_ROUTE_ADDR                         0x00000400

    /* what is SIP T1 timer duration */
#define ICF_REQD_SIP_T1_TIMER                           0x00000800

   /* what is SIP B timer duration */
#define ICF_REQD_SIP_B_TIMER                            0x00001000

   /* what is SIP F timer duration */
#define ICF_REQD_SIP_F_TIMER                            0x00002000
    
    /* what is SIP T2 timer duration */
#define ICF_REQD_SIP_T2_TIMER                           0x00004000

    /* what is SIP T4 timer duration */
#define ICF_REQD_SIP_T4_TIMER                           0x00008000

    /* Note: Do not use 0x10000000, it has been used in response structure */

    icf_uint32_t               bit_mask;

    icf_line_id_t               line_id;
/* Specifies the presence of the routing information */
/* Defined in icf_get_system_settings_req_st, So commented*/
/*#define ICF_GET_SETTINGS_ROUTE_INFO_PRESENT 0x8000000*/

    icf_void_st             routing_info;

} icf_get_line_settings_req_st; 

/*-----------------------------------------------------------------------------
 * 
 * Structure Name:icf_get_line_settings_resp_st   
 * Description: This data type is used to define a structure, which contains 
 *              the request by applications to fetch line settings of ICF.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{

    /* Result of this API - Success of failure */
#define ICF_API_GET_LINE_STG_RESULT_SUCCESS    0x10000000

    icf_uint32_t                    bit_mask;

    icf_transport_address_st        proxy_address;
    icf_transport_address_st        registrar_address;
    icf_transport_mode_t            proxy_transport_mode;
    icf_address_st                  self_address_list;
    icf_string_st                   self_name ;
    icf_boolean_t                   presentation_allowed ;
    icf_string_st                   auth_key ;
    icf_string_st                   auth_password ;
    icf_transport_mode_t            reg_mode ;
    icf_duration_t                  reg_duration ;
    icf_transport_address_st        reg_route_addr;
    icf_duration_t                  sip_T1_timer;
    icf_duration_t                  sip_B_timer;
    icf_duration_t                  sip_F_timer;
    icf_duration_t                  sip_T2_timer;
    icf_duration_t                  sip_T4_timer;

} icf_get_line_settings_resp_st;

/* ############################################################## */

/* ICF_CONF_STATUS_API_END */


/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_configure_cfm_st 
 *
 * Description: This structure is used to specify payload data of
 *               API ICF_CONFIGURE_CFM 
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* Denotes the API identifier for which the response is sent. */
    icf_api_id_t api_id;

    /* SPR 15997 : Line id in configure confirm API */
    /* Denotes the line_id identifier for which the response is sent. */
    icf_line_id_t line_id;

    /* Denotes the Success or Failure status of the execution of the API. */
    icf_result_t result;

    /* Denotes the error cause if the status of the API is Failure.*/
    icf_error_t error_cause;

} icf_configure_cfm_st;


/*********************
* CONTROL PLANE APIs *
* ********************/

/* These hash defines are used for indicating presence of some common optional 
 * parameters in the ICF APIs. These values should be used in the bit_mask if
 * any of the elements is to be included in an API structures containing
 * header/tag/msg-body/privacy-ind/pref-identity 
 */
#define ICF_PRIVACY_IND_PRESENT       0x01000000
#define ICF_PREF_IDENTITY_PRESENT     0x02000000
#define ICF_HDR_LIST_PRESENT          0x04000000
#define ICF_TAG_LIST_PRESENT          0x08000000
#define ICF_BODY_LIST_PRESENT         0x10000000
#define ICF_STREAM_LIST_PRESENT       0x20000000

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_register_req_st
 *
 * Description: This structure is used to specify payload data of
 *               API ICF_REGISTER_REQ 
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* This indicates the presence of the optional parameters. */

    icf_uint32_t bit_mask;

    
#define ICF_REG_REQ_TO_PRESENT                          0X01
#define ICF_REG_REQ_FROM_PRESENT                        0x02
#define ICF_REG_REQ_EXPIRY_PRESENT                      0x04
#define ICF_REG_REQ_CONTACT_LIST_REQD                   0x08
#define ICF_REG_REQ_SECURITY_CLIENT_PRESENT             0x10
#define ICF_REG_REQ_REFRESH_REG_FLAG_PRESENT            0x20
#define ICF_REG_REQ_REG_EVENT_PCKG_SUBS_FLAG_PRESENT    0x40
#define ICF_REG_REQ_REFRESH_MULTIPLIER_PRESENT          0x80
#define ICF_REG_REQ_REFRESH_INDICATIONS_REQD	        0x100
#define ICF_REG_REQ_DEREG_SPECIFIC_CONTACT_PRESENT      0x200


    /* Indicates the line to be used for the outgoing call. Always coded 
     * as ICF_USE_LINE1
     */    
    icf_line_id_t line_id;

    /* This parameter specifies the public-URI to be registered. */
    icf_address_st to;

    /* This parameter specifies the expiry to be sent in the SIP REGISTER 
     * message.
     */
    icf_duration_t expiry ;

    /* List of additional headers that the application wants to send in the API. */
    icf_header_list_st header_list;

    /* List of additional tags that the application wants to send in the API. */
    icf_tag_list_st tag_list;

    /* List of message bodies that the application wants to send in the API. */
    icf_msg_body_list_st body_list ;

    /* This parameter specifies whether the application wants the
     * contact header(s) other than local contact as obtained in the 200 OK
     * response for REGISTER request.
     */
    icf_boolean_t    contact_list_required;

    /*This field indicated whether IPTK or application shall start the refresh timer for reregistration*/
    icf_boolean_t    registration_refresh_required;

    /* This parameter contains the Security-Client parameters provided
     * by application for security association.
     */
    icf_large_string_st   security_client;

    /* This parameter specifies whether the application wants 
     * IPTK to perfomr reg event package subscription on its own and
     * handle the notifications for the same 
     */
    icf_boolean_t   reg_event_pckg_subs_required;

     /* This field is used to start the Regsitration
      * Refresh timer on the bellow mentioened
      * arithmatic:
      * 1.If the value of  refresh_registration_multiplier is more than 0 and less
      *   than 100 then IPTK shall start the Registration Refresh timer of
      *   (refresh_registration_multiplier /100) * (Expiry duration) duration.
      *
      * 2.If the value of  refresh_registration_multiplier is 0 or greater than 
      *   equal to 100 then IPTK shall start the registration refresh timer as 
      *   per the existing behavior.
      *   Existing Behavior:
      *     If register_head_start_timer is configured.
      *       If register_head_start_timer is less than (0.5) * Expiry duration, 
      *               duration = Expiry duration - register_head_start 
      *       Else
      *               duration = (0.5) * Expiry duration.
      *     Else
      *       duration = (0.5) * Expiry duration.
      *
      * 3.If refresh_registration_multiplier is not present in ICF_REGISTER_REQ, 
      *   and it is an initial registration request then IPTK shall start the 
      *   refresh registration timer on basis of existing behavior.
      *
      * 4.If refresh_registration_multiplier is not present in ICF_REGISTER_REQ, 
      *   and it is a refresh registration request then IPTK shall start the 
      *   refresh registration timer with the same arithmetic that was used 
      *   previously, when last time refresh registration timer started for 
      *   this user.
      */

    icf_uint8_t   registration_refresh_multiplier;

    /* If this flag is enabled, then IPTK shall send ICF_REGISTER_STATUS_IND
     * to the application after successful completion of Register Refresh.
     * In case the flag is disabled then no indications will be sent to application
     * on successful auto refresh completion by IPTK.
     */
    icf_boolean_t	  refresh_ind_reqd;
    /* A boolean value used by the application to deregister a specific contact
     * in the API */
    icf_boolean_t dereg_specific_contact;

} icf_register_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_create_call_req_st
 *
 * Description: This structure is used to specify payload data of
 *               API ICF_CREATE_CALL_REQ 
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    icf_uint32_t 			bit_mask;

#define ICF_CALLED_PARTY_NAME_PRESENT  0X00000001
#define ICF_TOGGLE_PRES_IND_PRESENT    0x00000002
#define ICF_QOS_MARK_PRESENT           0x00000004
#define ICF_CALLING_PARTY_ADDR         0x00000010
#define ICF_CALLING_PARTY_NAME         0x00000020
	/* ICF REL 6.0: new bitmask for the pref_media_profile from APP */
#define ICF_PREF_MEDIA_PROFILE_PRESENT 0x00000040
#define ICF_PRIVACY_HDR_FLAG_PRESENT   0x00000080
/* new bitmask for requesting resource reservation at call time */
#define ICF_RESOURCE_RESERV_FLAG_PRESENT	0x00000100

/*This bit indicates SRTP support for this call*/
#define ICF_MEDIA_TYPE_REQD_FLAG_PRESENT  0x00000200

/* Bitmask for requesting QOS precondition support at call level */
#define ICF_PRECONDITION_REQD_FLAG_PRESENT  0x00000400

/* New bitmask req_uri_param from APP */
#define ICF_REQUEST_URI_PARAM_PRESENT       0x00000800

/* New bitmask SRTP fallbeck flag from APP */
#define ICF_SRTP_FALLBACK_FLAG_PRESENT      0x00001000

 /*  This bitmask denotes presence of optional field tunnel_mode */
#define ICF_CREATE_CALL_TUNNEL_MODE_OPERATION_PRESENT 0x00002000

#ifdef ICF_SESSION_TIMER
    /* this bitmask indicates the presence of boolean flag for session timer 
     * control
     */ 
#define ICF_CREATE_CALL_SESSION_TIMER_ENABLE_PRESENT     0x00004000

#endif

    /*  This bitmask denotes presence of optional field prack_in_required */
#define ICF_CREATE_CALL_PRACK_VALUE_PRESENT     0x0008000

/* New bitmask to indicate that Call Setting bitmask are present*/    
#define ICF_CREATE_CALL_SETTINGS_PRESENT        0x00010000
#define ICF_CREATE_CALL_REDIRECT_SUPPORT_REQD   0x00020000
#define ICF_CREATE_CALL_SETUP_TIMER_PRESENT	    0x00040000    


    /* Use common hash defines if header/msg-body/tag/stream 
     * list present in the API. 
     */

    /* Indicates the line to be used for the outgoing call. Always 
     * coded as ICF_USE_LINE1
     */
    icf_line_id_t			line_id;

    /* Indicates the E.164 number or SIP URL of the remote user. */
    icf_address_st 			called_party_addr;
    /* Indicates the name of the remote user entered by local user when
     * dialing the SIP URI
     */
    icf_name_st 			called_party_name;
    /* Indicates whether the local user wants to toggle the presentation
     * indication status for the current call.
     */
    icf_boolean_t 			toggle_presentation_indicator;
    /* Indicates the identifier to be sent for the current call in the
     * type of service flag.
     */
    icf_qos_mark_t 			qos_mark ;
    /* Indicates the Preferred Identity, which shall be used at the
     * P-CSCF for asserted identity in trusted networks.
     */
    icf_address_st 			pref_identity;
    icf_address_st  		calling_party_address;
    icf_string_st  			calling_party_name;

    /* List of additional headers that the application wants to send in the
     * message request
     */
    icf_header_list_st 		header_list;

    /* List of additional tags that the application wants to send in the 
     * message request.
     */
    icf_tag_list_st 		tag_list;

    /* List of message bodies that the application wants to send in the
     * message request.
     */
    icf_msg_body_list_st 	body_list;

	/* ICF REL 6.0: this will contain the preferred media profile for the 
	 * application. This is an optional entity in the request. If the 
	 * app, sends this information, then ICF shall use this info to form 
	 * the SDP in the outgoing Invite. This profile will over-ride the info
	 * from APP as set in the media profile.
	 */
	/* this will be a list of icf_stream_capab_st */
	icf_list_st				*p_pref_media_profile;

    /* In case outgoing INVITE carries Privacy header, this flag indicates
     * whether Privacy header should be sent in BYE, REFER, RE-INVITE also.
     * The default value is ICF_FALSE */
    icf_boolean_t           privacy_hdr_all_req;

	/* indicates whether the local user wants to enable QoS precondition 
	 * feature */
	icf_boolean_t			resource_reservation_reqd;

     /*This parameter indicates that SRTP support is present for this call*/
        icf_media_transport_mode_et  media_transport_type;

    /* Indicates whether the local user wants to enable QOS precondition
     * feature, if this is set to 1 then QOS precondition is required for the call*/
        icf_boolean_t           precondition_required;
   
    /* URI Parameter to be added in the request URI of outgoing INVITE */
    icf_string_st           request_uri_param;
    
    /*This flag is used to tell IPTK whether application wants to
     *do fallback to RTP_AVP on SRTP rejected by remote*/
    icf_boolean_t         srtp_fallback_reqd;

    /* This field indicates that the application wants to enable
       tunnel mode of operation.
    */
    icf_boolean_t         tunnel_mode;

#ifdef ICF_SESSION_TIMER
    /* This field indicates that the application wants to enable / disable
       session timer functionality.
    */
    icf_boolean_t         session_timer_enable;
#endif

    /*This field indicated whether IPTK or application will send the INVITE for 302 response received for the initial INVITE*/
    icf_boolean_t         redirect_support_reqd;

    /* This field indicates prack_support value 
     * 0 No prack neither in supported nor in require 
     * 1 100rel in supported header
     * 2 100rel in require header
     */

    icf_prack_values_et         prack_value;

    /* the new field added for specifying any generic call settings
     */
#define ICF_EMERGENCY_CALL         0x01
   icf_uint32_t             call_settings; 
   /* Duration of initial call setup timer that needs to be started for this 
	* outgoing call. This shall override the default duration or the duration
	* configured through ICF_SET_CALL_PARAMS_REQ.
	* This duration is in seconds.
	*/
    icf_duration_t        		setup_timer;
} icf_create_call_req_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_local_user_alerted_req_st
 *
 * Description: This API is invoked by Application towards the IMS Module
 *                in response to the ICF_INCOMING_CALL_IND API.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
		/* icf REL 6.0: multiple m lines */
#define ICF_USER_ALERTED_DELETED_STREAM_PRESENT		0x01
#define ICF_USER_ALERTED_ALERT_TIMER_PRESENT		0x02
#define ICF_USER_ALERTED_EARLY_MEDIA_SUPPORTED          0x04
#define ICF_USER_ALERTED_MEDIA_MODE_PRESENT             0x08

/*  This bitmask denotes presence of optional field prack_in_required */
#define ICF_LOCAL_USER_ALERTED_PRACK_VALUE_PRESENT     0x10


    icf_uint32_t bit_mask;
    /* Use common hash defines if privacy/header/msg-body/tag/stream 
     * list present in the API. 
     */

	/* if early_media_reqd is ICF_FALSE then ICF will not send
	 * 183 with SDP/180 with SDP
	 */
	icf_boolean_t early_media_reqd;
    
	/* Gives the status of inband info. ICF will ignore this value
	 * If early_media_reqd is ICF_FALSE
	 */
    icf_inband_info_status_t inband_info_status;

    /* Indicates whether privacy is required. */
    icf_boolean_t privacy_ind;

    /*Alert timer duration*/
    icf_duration_t	alert_timer_duration;

    /* List of additional headers that the application wants to send in the
     * message request
     */
    icf_header_list_st header_list;

    /* List of additional tags that the application wants to send in the 
     * message request.
     */
    icf_tag_list_st tag_list;

    /* List of message bodies that the application wants to send in the
     * message request.
     */
    icf_msg_body_list_st body_list;

    /* List of encoded_attributes for a media stream that application wishes 
     * to set in the outgoing response to the remote offer. Node is of type
     * icf_stream_capab_st */
    icf_list_st			*p_stream_list;

	/* icf REL 6.0: multiple m lines */
	/* the application may delete any stream during the call setup. This is 
	 * optional. The application will only return the rejected/deleted stream 
	 * information. The application will not be allowed to change/modify any
	 * codecs or any other parameter within the stream. The application if 
	 * desires can reject a stream only */
	/* the application should not indicate those stream_id's that have been
	 * already deleted in the onging session */
	icf_stream_id_t	         count;
	icf_stream_list_st       deleted_media_streams[ICF_MAX_STREAM_PER_CALL];
           
    /*If the applications wants to send the P-Early-Media Header in 18x 
     * response, then application can specify the mode in this.If this mode is
     * different from the current mode, then IPTK do MMS for the mode.
     */ 
    icf_media_mode_t          early_mode;
    icf_media_mode_t          media_mode;
    /* This field indicates 180 shall be sent reliable on non reliable */
    /* This field indicates prack_support value 
       0  No prack neither in supported nor in require 
       2  100rel in require header
    */
    icf_prack_values_et prack_value;
        
	
} icf_local_user_alerted_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_terminate_call_req_st
 *
 * Description: This API is invoked by Application towards IMS Module
 *                when the local user rejects an incoming call or terminate
 *                an ongoing call.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    icf_uint32_t bit_mask;
    #define ICF_CALL_CLEAR_RESPONSE_CODE_PRESENT      0x00000002

    /* Indicates the reason for terminating the call. */
    icf_call_clear_reason_t call_clear_reason;

    /* Denotes the line ID on which an active call is to be cleared. */
    icf_line_id_t line_id;

    /* Indicates the response code to be sent to peer for terminating the call */
    icf_uint16_t response_code;

    /* List of additional headers that the application wants to send in the
     * message request
     */
    icf_header_list_st header_list;

    /* List of additional tags that the application wants to send in the 
     * message request.
     */
    icf_tag_list_st tag_list;

    /* List of message bodies that the application wants to send in the
     * message request.
     */
    icf_msg_body_list_st body_list;

} icf_terminate_call_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_connect_req_st
 *
 * Description: This API is invoked by Application to IMS Module when the
 *                local user accepts the call.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
	/* icf REL 6.0: multiple m lines */
#define ICF_CONNECT_DELETED_STREAM_PRESENT		0x01

    icf_uint32_t bit_mask;
    /* Use common hash defines if privacy/header/msg-body/tag/stream 
     * list present in the API. 
     */

    /* Indicates whether privacy is required. */
    icf_boolean_t privacy_ind;

    /* List of additional headers that the application wants to send in the
     * message request
     */
    icf_header_list_st header_list;

    /* List of additional tags that the application wants to send in the 
     * message request.
     */
    icf_tag_list_st tag_list;

    /* List of message bodies that the application wants to send in the
     * message request.
     */
    icf_msg_body_list_st body_list;


    /* List of encoded_attributes for a media stream that application wishes 
     * to set in the outgoing response to the remote offer. Node is of type
     * icf_stream_capab_st */
    icf_list_st			*p_stream_list ;

	/* icf REL 6.0: multiple m lines */
	/* the application may delete any stream during the call setup. This is 
	 * optional. The application will only return the rejected/deleted stream 
	 * information. The application will not be allowed to change/modify any
	 * codecs or any other parameter within the stream. The application if 
	 * desires can reject a stream only */
	icf_stream_id_t			count;
	icf_stream_list_st		deleted_media_streams[ICF_MAX_STREAM_PER_CALL];	
} icf_connect_req_st;


/* icf REL 6.0: multiple m lines */
/*-----------------------------------------------------------------------------
 *
 * Structure Name:	icf_connect_resp_st
 *
 * Description: 	This API is invoked by ICF towards the Application to 
 * 					indicate that an ACK has been received for the incoming
 * 					cal. The API shall also inc. the commited media information
 * 					for the call.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
#define ICF_CONNECT_RESP_DELETED_STREAM_PRESENT		0x01
    icf_uint32_t 			bit_mask;

	/* ICF REL 6.0: multiple m lines */
	/* information of the accepted/commited media streams for the received 
	 * INVITE. This is a list of the node type icf_call_modify_media_data__st */
	icf_list_st				*p_accepted_stream_list;

	/* icf REL 6.0: multiple m lines */
	/* the application may delete any stream during the call setup. This is 
	 * optional. The application will only return the rejected/deleted stream 
	 * information. The application will not be allowed to change/modify any
	 * codecs or any other parameter within the stream. The application if 
	 * desires can reject a stream only */
	icf_stream_id_t			count;
	icf_stream_list_st		deleted_media_streams[ICF_MAX_STREAM_PER_CALL];	
             
       /* List of additional headers that the application wants to send in the
        * message request
        */
      icf_header_list_st     header_list;
 
} icf_connect_resp_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_subscribe_req_st
 *
 * Description: This API is used by the application to subscribe to a
 *                particular event package.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    icf_uint32_t bit_mask;

#define ICF_SUB_REQ_DEST_INFO_PRESENT 0X01
#define ICF_SUB_REQ_EVENT_PRESENT 0x02
#define ICF_SUB_REQ_EXPIRES_HDR_NOT_TO_BE_SEND 0x04
#define ICF_SUB_REQ_RESUBSCRIPTION_NOT_REQUIRED 0x08
#define ICF_SUB_REQ_SUBS_HEAD_START_DURATION_PRESENT 0x10    
#define ICF_SUB_REQ_RETRY_NOT_REQUIRED   0x20
#define ICF_SUB_REQ_RETRY_NOT_REQUIRED_FOR_3XX 0x40
     
    /* Use common hash defines if header/msg-body/tag list present */
	icf_line_id_t line_id;

    /* Indicates the SIP URL of the remote entity to which subscription 
     * request has to be sent.
     */
    icf_address_st destination_info;

    /* Package name for which subscription request has to be sent. */
    icf_string_st event_pkg_name;

    /* Defines the duration for this subscription. */
    icf_uint32_t duration;

    /* Indicates the Preferred Identity, which shall be used at the P-CSCF for
     * asserted identity in trusted networks.
     */
    icf_address_st pref_identity;

    /* List of additional headers that the application wants to send in the
     * message request
     */
    icf_header_list_st header_list;

    /* List of additional tags that the application wants to send in the 
     * message request.
     */
    icf_tag_list_st tag_list;

    /* List of message bodies that the application wants to send in the
     * message request.
     */
    icf_msg_body_list_st body_list;

    /* Defines the head start duration for this subscription.*/ 
    icf_duration_t subs_head_start_duration;    

} icf_subscribe_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_publish_req_st
 *
 * Description: This API is used by the application for the publication of
 *                event state to a particular Event State Compositor ( ESC ).
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    icf_uint32_t bit_mask;
    #define ICF_USER_ADDRESS_PRESENT       0x01

    /* Use common hash defines if header/msg-body/tag list present */

    /* Indicates the SIP URL of the remote entity to which publication 
     * request has to be sent.
     */
     icf_line_id_t line_id;
    /* Indicates the user on the line for which publish has to be sent */
    icf_address_st user_address;

    /* indicates the destination URL */
    icf_address_st destination_info;

    /* Package name for which publication request has to be sent. */
    icf_string_st event_pkg_name;

    /* Defines the duration for this publication. */
    icf_uint32_t duration;

    /* Indicates the Preferred Identity, which shall be used at the P-CSCF for
     * asserted identity in trusted networks.
     */
    icf_address_st pref_identity;

    /* List of additional headers that the application wants to send in the
     * message request
     */
    icf_header_list_st header_list;

    /* List of additional tags that the application wants to send in the 
     * message request.
     */
    icf_tag_list_st tag_list;

    /* List of message bodies that the application wants to send in the
     * message request.
     */
    icf_msg_body_list_st body_list;

} icf_publish_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_message_req_st
 *
 * Description: This API is used by the application to send an instant 
 *                message or a group advertisement
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    icf_uint32_t bit_mask;
    /* Use common hash defines if header/msg-body/tag list present */
    #define ICF_USER_ADDRESS_PRESENT       0x01

	icf_line_id_t line_id;

    /* Indicates the user on the line for which message request has to be sent */
    icf_address_st user_address;

    /* Indicates the SIP URL of the remote user to which MESSAGE request has
     *  to be sent.
     */
    icf_address_st destination_info;

    /* Indicates the Preferred Identity, which shall be used at the P-CSCF for
     * asserted identity in trusted networks.
     */
    icf_address_st pref_identity;

    /* List of additional headers that the application wants to send in the
     * message request
     */
    icf_header_list_st header_list;

    /* List of additional tags that the application wants to send in the 
     * message request.
     */
    icf_tag_list_st tag_list;

    /* List of message bodies that the application wants to send in the
     * message request.
     */
    icf_msg_body_list_st body_list;

} icf_message_req_st;

/*-----------------------------------------------------------------------------

 *

 * Structure Name:icf_refer_req_st

 *

 * Description: This API is used by the application to refer an entity 

 *                to a resource .

 *

 *---------------------------------------------------------------------------*/



typedef struct

{



    icf_uint32_t bit_mask;

    
    #define ICF_REF_REQ_DEST_INFO_PRESENT 0X01
    #define ICF_REF_REQ_SUBS_REQD_PRESENT 0x02

    /* Use common hash defines if header/msg-body/tag list present */

	icf_line_id_t line_id;

    /* Indicates the SIP URL of the remote user to which refer request

     * has to be sent.

     */

    icf_address_st destination_info;



    /* Resource that the addressed user is referred to. */

    icf_address_st refer_to ;



    /* Indicates the Preferred Identity, which shall be used at the P-CSCF for

     * asserted identity in trusted networks.

     */

    icf_address_st pref_identity;



    /* Identifies whether a Subscription needs to be created with this REFER

     * request.

     */

    icf_boolean_t subscription_required ;



    /* List of additional headers that the application wants to send in 

     * the refer request

     */

    icf_header_list_st header_list;



    /* List of additional tags that the application wants to send in the refer

     * request.

     */

    icf_tag_list_st tag_list;



    /* List of message bodies that the application wants to send in the refer

     * request.

     */

    icf_msg_body_list_st body_list;

    

} icf_refer_req_st;











/*-----------------------------------------------------------------------------

 *

 * Structure Name:icf_register_cfm_st

 *

 * Description: This API is used by the ICF to indicate an register confirm event

 *                to the application.

 *

 *---------------------------------------------------------------------------*/



typedef struct

{



    icf_uint32_t bit_mask;

#define   ICF_REG_CFM_ERROR_CAUSE_PRESENT    0x001

#define   ICF_REG_CFM_ASSO_URI_PRESENT       0x002

#define   ICF_REG_CFM_TO_PRESENT             0X004

#define   ICF_REG_CFM_FROM_PRESENT           0x008
    
#define   ICF_REG_CFM_RESP_CODE_PRESENT      0x010

#define   ICF_REG_CFM_CONTACT_LIST_PRESENT   0x020


    /* Use common hash defines if header/msg-body list present */



    /* Indicates the type of ongoing registration procedure, */

    icf_uint8_t request_type ;



    /* Denotes the Failure status only. */

    icf_result_t result;



    /* Denotes the error cause if the status of the API is Failure. */

    icf_error_t error_cause ;



    /* Public uri and P- Associated uri list */
    icf_pub_uri_list_node_st   *p_uri_list;



    /* Indicates the line to be used for the outgoing call. 

     * Always coded as ICF_USE_LINE1

     */

    icf_line_id_t line_id;



    /* This parameter specifies the public-URI that is being registered. */

    icf_address_st to;


    /* List of additional headers that the application wants to send in the API */

    icf_header_list_st header_list;



    /* List of message bodies that the application wants to send in the API. */

    icf_msg_body_list_st body_list ;

    /* This field contains the list of contact header(s) other than local contact
     * as obtained in the 200 OK response for REGISTER request.
     */
    icf_header_list_st   contact_list;

    /*This field will be used to indicate response code to the application for
      the ICF_REGISTER_REQ API*/

    icf_uint16_t  response_code;
    

} icf_register_cfm_st;















/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_register_status_ind_st
 *
 * Description: IMS Client Framework sends unsolicited registration failure
 *                indications to the application for all re-registrations.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    icf_uint32_t bit_mask;
#define   ICF_REG_IND_ERROR_CAUSE_PRESENT           0x001
#define   ICF_REG_IND_ASSO_URI_PRESENT              0x002
#define   ICF_REG_IND_TO_PRESENT                    0X004
#define   ICF_REG_IND_FROM_PRESENT                  0x008
#define   ICF_REG_IND_RETRY_AFTER_DURATION_PRESENT  0x010 
#define   ICF_REG_IND_CONTACT_LIST_PRESENT          0x020  
#define   ICF_REG_IND_RESP_CODE_PRESENT             0x040 
    
    /* Use common hash defines if header list present */
    /* Indicates the type of ongoing registration procedure, */
    icf_uint8_t request_type ;

    /* Denotes the Failure status only. */
    icf_result_t result;

    /* Denotes the error cause if the status of the API is Failure. */
    icf_error_t error_cause ;

    /* Public uri and P- Associated uri list */
    icf_pub_uri_list_node_st   *p_uri_list;

    /* Indicates the line to be used for the outgoing call. */
    icf_line_id_t line_id;

    /* This parameter specifies the public-URI that is being registered. */
    icf_address_st to;

    /* List of additional headers that are of importance to the application.*/
    icf_header_list_st header_list;

    /* duration received in retry-after attribute when the contact of registered
     * public user is terminated with event attribute as probation and
     * retry-after attribute with retry_after_duration.*/
    icf_duration_t    retry_after_duration;

    /* This field contains the list of contact header(s) other than local contact
     * as obtained in the 200 OK response for REGISTER request.
     */
    icf_header_list_st   contact_list;

    /*This field will be used to indicate response code to the application for
      the ICF_REGISTER_REQ API*/

    icf_uint16_t  response_code;
    
} icf_register_status_ind_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_incoming_call_ind_st
 *
 * Description: This API is sent by IMS Module to inform Application about
 *                an incoming call from network, so that Application can update
 *                its UI display to indicate the same to the local user.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    icf_uint32_t bit_mask ;
#define ICF_TYPE_OF_CALL_IND_PRESENT        0x01
#define ICF_CALL_WAITING_IND_PRESENT        0x02
#define ICF_CALLING_ADD_ASRTD_IND_PRESENT   0x04
#define ICF_CALLING_PARTY_ADD_PRESENT       0x08
#define ICF_CALLING_PARTY_NAME_PRESENT      0x10
#define ICF_CALLED_PARTY_ADD_PRESENT        0x20
#define ICF_TRANSF_PARTY_ADD_PRESENT        0x40
#define ICF_TRANSF_PARTY_NAME_PRESENT       0x80
	/* ICF REL 6.0: multiple m lines */
#define ICF_REJECTED_MEDIA_STREAM_PRESENT	0x0100
    /* New bitmask for request_uri_param */
#define ICF_REQ_URI_PARAM_PRESENT           0x0200


    /* Use common hash defines if header/msg-body/stream list present */
    /* Denotes the line ID on which the local user has received the call. */
    icf_line_id_t 				line_id;

	/* For the current ICF release, this field will be a bitmap and not an
	 * enumeration. This is to facilitate the large combination of call types
	 * possible in this release. */
    /* Indicates the type of call. */
	icf_uint8_t					call_type;

    /* Indicates whether the incoming call is in call waiting. */
    icf_boolean_t 				call_waiting_ind;

    /* Indicates whether the originator (calling party) identity is 
     * asserted/verified by registrar. 
     */
    icf_boolean_t 				calling_party_addr_asserted;

    /* Denotes the address of the remote party calling the local user. */
    icf_address_st 				calling_party_addr;

    /* Denotes the name of the remote party calling the local user. */
    icf_name_st 				calling_party_name;

    /* Denotes the address of the local user. */
    icf_address_st 				called_party_addr;

    /* Contains the address of the transferring party if the incoming
     * call is a transferred call.
     */
    icf_address_st 				transferring_party_addr;

    /* Contains the name of the transferring party if the incoming call
     * is a transferred call.
     */
    icf_name_st 				transferring_party_name;

    /* List of additional headers that are of importance to the application. */
    icf_header_list_st 			header_list;

    /* List of additional message bodies that are of importance to the 
	 * application. */
    icf_msg_body_list_st 		body_list ;

	/* ICF REL 6.0: multiple m lines */
	/* information of the accepted/commited media streams for the received 
	 * INVITE. This is a list of the node type icf_stream_capab_st */
	icf_list_st					*p_accepted_stream_list;

	/* this is a list of rejected/deleted streams. The information shared with 
	 * APP here is the stream id and the corresponding stream_type. This is 
	 * an optional field */
	icf_stream_id_t				count;
	icf_stream_list_st			deleted_stream_list[ICF_MAX_STREAM_PER_CALL];

    /*Following field will contain the internal call ID of the call 
     * present in Join Header*/ 
    icf_call_id_t       call_id_to_be_joined;

    /* URI Parameter as recieved in the Request URI of the incoming INVITE */   
    icf_string_st           request_uri_param;

    /* This field indicates prack_support value 
       0 No prack neither in supported nor in require in incoming INVITE 
       1 100rel in supported header in incoming INVITE
       2 100rel in require header in incoming INVITE.
    */
    icf_prack_values_et prack_value;
    
    /* This field indicates to application that it is a precondition call 
       or not */
    icf_boolean_t precondition_call;

} icf_incoming_call_ind_st;



/*-----------------------------------------------------------------------------
*
* NAME :		 icf_info_req_st
*
* DESCRIPTION  : This data type is used to define a structure,
*                which specifies payload data of API
*                ICF_INFO_REQ.
-----------------------------------------------------------------------------*/

typedef struct
{
    icf_uint32_t		bit_mask;
      
#define   ICF_USER_NAME_PRESENT         0x00000001
 
#define   ICF_HDR_LIST_PRESENT   	0x04000000
#define   ICF_TAG_LIST_PRESENT 	        0x08000000
#define   ICF_BODY_LIST_PRESENT    	0x10000000
        
    icf_header_list_st	    header_list;
    icf_tag_list_st		    tag_list;
    icf_msg_body_list_st	body_list;

   /* user name to be used in user part of the request URI
  * of INFO */
    icf_string_st		    username;

} icf_info_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_remote_user_alerted_ind_st
 *
 * Description: This API is sent by IMS Module to inform Application that
 *                the remote party has been alerted. This API is invoked after
 *                ICF receives the 180 ringing response from remote party.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    icf_uint32_t bit_mask;
	/* ICF REL 6.0: multiple m lines */
#define ICF_REM_USER_ALRTED_DELETED_STREAM_PRESENT		0x01

/*  This bit will be set if rel_prov_resp field is present */
#define ICF_REM_USER_ALRTED_REL_PROV_RESP_PRESENT             0x02
    
    /* Use common hash defines if header/msg-body list present */
    /* Gives status of inband info */
    icf_inband_info_status_t inband_info_status;

    /* List of additional headers that are of importance to the application. */
    icf_header_list_st header_list;

    /* List of additional message bodies that are of importance to the 
	 * application. */
    icf_msg_body_list_st body_list ;

	/* ICF REL 6.0: multiple m lines */
	/* information of the accepted/commited media streams for the received 
	 * INVITE. This is a list of the node type icf_stream_capab_st */
	icf_list_st					*p_accepted_stream_list;

	/* this is a list of rejected/deleted streams. The information shared with 
	 * APP here is the stream id and the corresponding stream_type. This is 
	 * an optional field */
	icf_stream_id_t			count;
	icf_stream_list_st		deleted_media_streams[ICF_MAX_STREAM_PER_CALL];	

    /* This Boolean will be set to application whenever in outgoing call
     * Prack is enabled/disabled on per call basis
     */
    icf_boolean_t        rel_prov_resp;
    
    /* A new parameter is_sdp_received of type icf_boolean_t is added 
       to indicate whether received 180 is with SDP or without SDP */
    icf_boolean_t        is_sdp_received;

} icf_remote_user_alerted_ind_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_terminate_call_ind_st
 *
 * Description: This API is invoked by IMS Module towards Application when
 *                IM wants to clear a call on receiving SIP BYE/4xx/5xx/6xx 
 *                request from remote user or due to some local error.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    icf_uint32_t bit_mask ;
#define ICF_ADDNL_INFO_PRESENT 0X01
#define ICF_REMOTE_CALL_CLEAR_RESPONSE_CODE_PRESENT 0x02
#define ICF_RETRY_AFTER_DURATION_PRESENT       0x40000000 
    /* Is used by IM to inform Application about the reason for terminating
     * the call. Application can use this reason to play the appropriate 
     * error tone or message on the UI display.
     */
    icf_call_clear_reason_t call_clear_reason;

    /* Specifies the additional information like display string for 
     * terminating the call.
     */
    icf_string_st additional_info;
   /* response code for peer initiated call clear */
    icf_uint16_t   response_code;

   /* duration received in retry-after header*/
   icf_duration_t    retry_after_duration;

    /* List of additional headers that the application wants to send in the
     * message request
     */
    icf_header_list_st header_list;

    /* List of message bodies that the application wants to send in the
     * message request.
     */
    icf_msg_body_list_st body_list;

} icf_terminate_call_ind_st;


/*-----------------------------------------------------------------------------
 *
 * API Name: ICF_REMOTE_USER_TERMINATE_CALL_RESP
 *
 * Description:  This API is used to indicate the response of 
 * icf_terminate_call_req API.
 *
 *---------------------------------------------------------------------------*/
/*  SPR18064 Merge */
typedef struct{  
icf_uint8_t bitmask;
#define ICF_ERROR_CAUSE_PRESENT 0x01   
icf_error_t error_cause;
}icf_remote_user_term_call_resp_st;


#ifdef ICF_NW_ACTIVATE
/*-----------------------------------------------------------------------------
 *
 * API Name: ICF_EVENT_INDICATION
 *
 * Description:  This API is used to indicate the ICF system/Network events to 
 * 				 the Appplication.  
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
#define ICF_NW_UP                           0x01
#define ICF_NW_DOWN                         0x02
#define ICF_NW_MEMORY_FAILURE               0x04
#define ICF_NW_CURRENTLY_NOT_AVAILABLE      0x08
#define ICF_NW_NOW_AVAILABLE                0x10
#define ICF_NW_SUSPENDED                   0x20
    /* Event code */
    icf_uint32_t    event_code ;

    /* This denotes the event specific data for the application.
       This is for future use */
    icf_void_st     event_data;
} icf_event_indication_st;
#endif
 
 /*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_media_connected_ind_st
 *
 * Description: This API signifies to the application that the media parameters 
 * are committed and media with remote user is connected. 
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
    icf_uint32_t            bit_mask ;
	/* ICF REL 6.0: multiple m lines */
#define ICF_MEDIA_CONECT_DELETED_STREAM_PRESENT		0x01

/*  This bit will be set if rel_prov_resp is present */
#define ICF_MEDIA_CONNECT_IND_REL_PROV_RESP_PRESENT      0x02

	/* ICF REL 6.0: multiple m lines */
	/* information of the accepted/commited media streams for the received 
	 * INVITE. This is a list of the node type icf_stream_capab_st */
	icf_list_st					*p_accepted_stream_list;

	/* this is a list of rejected/deleted streams. The information shared with 
	 * APP here is the stream id and the corresponding stream_type. This is 
	 * an optional field */
	icf_stream_id_t			count;
	icf_stream_list_st		deleted_media_streams[ICF_MAX_STREAM_PER_CALL];	

    /* This Boolean will be set to application whenever in outgoing call
     * Prack is enabled/disabled on per call basis
     */
    icf_boolean_t        rel_prov_resp;

} icf_media_connected_ind_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_connect_ind_st
 *
 * Description: This API is invoked by IMS Module to Application after 
 *                receiving a 200 OK message from the network. This message is 
 *                sent as a response to the INVITE message generated after the 
 *                request for creating a new call is invoked. This API indicates
 *                that the remote user has accepted the call.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    icf_uint32_t bit_mask;

#define ICF_ASSERTED_ID_PRESENT			0x01
#define ICF_CONNECT_IND_DELETED_STREAM_PRESENT		0x02
    /* This bit indicates presence of optional field offer_received */
#define ICF_CONNECT_IND_OFFER_RECEIVED_PRESENT	0x04
    /* This bit indicates presence of optional field tunnelled_sdp_info */
#define ICF_CONNECT_IND_TUNNELLED_SDP_PRESENT	0x08
    
    /* Use common hash defines if header/msg-body/stream list present */

    /* Indicates the Asserted Identity of the remote party. */
    icf_address_st asserted_identity;

    /* List of additional headers that are of importance to the application. */
    icf_header_list_st header_list;

    /* List of additional message bodies that are of importance to the 
	 * application. */
    icf_msg_body_list_st body_list ;

	/* ICF REL 6.0: multiple m lines */
	/* information of the accepted/commited media streams for the received 
	 * INVITE. This is a list of the node type icf_call_modify_media_data_st */
	icf_list_st					*p_accepted_stream_list;

	/* this is a list of rejected/deleted streams. The information shared with 
	 * APP here is the stream id and the corresponding stream_type. This is 
	 * an optional field */
	icf_stream_id_t			count;
	icf_stream_list_st		deleted_media_streams[ICF_MAX_STREAM_PER_CALL];	

    icf_boolean_t	   inband_dtmf_supported;
    /* This field indicates to the application that an offer is expected 
       from it. 
    */   
    icf_boolean_t      offer_received;
    /* This is the tunnelled SDP received from the peer. If forking and multiple
       is disabled, this contains the first answer received from the peer, else
       this contains the last answer received from the peer during outgoing 
       call establishment.
    */
    icf_tunnelled_sdp_info_st    tunnelled_sdp_info;
} icf_connect_ind_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_subscription_status_ind_st
 *
 * Description: This API is used by the framework to inform the application
 *                about the status of the Subscription.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    icf_uint32_t bit_mask;
#define ICF_SUBS_ST_IND_RESP_CODE_PRESENT 0X01
#define ICF_SUBS_ST_IND_ERROR_CODE_PRESENT 0X02

    /* Use common hash defines if header list  present */
    icf_uint32_t error_code ;
    
    /* Indicates the status of the subscription */
#define    ICF_SUBS_ACCEPTED            0
#define    ICF_SUBS_SUBSCRIBED            1
#define    ICF_SUBS_FAIL_RETRY            2
#define    ICF_SUBS_FAIL_NO_RETRY        3
#define    ICF_SUBS_UNSUBSCRIBED        4

    icf_uint8_t status;
    icf_uint32_t duration ;

    /* Response code received for the SUBCRIBE request. */
    icf_uint32_t response_code ;

    /* List of headers received in the subscription response which are of
     * importance to the application.
     */
    icf_header_list_st header_list;

    /* Event package name for which subscribe request was sent */
    icf_string_st 		event_pkg_name;
} icf_subscription_status_ind_st;


















/*NOTIFY_OUT_OF_DIALOG_START*/
/*-----------------------------------------------------------------------------

 *

 * Structure Name:icf_notify_ind_st

 *

 * Description: This API is used by the framework to inform the application

 *                about an incoming NOTIFY.

 *

 *---------------------------------------------------------------------------*/


typedef struct

{

#define ICF_SUBS_DURATION_PRESENT		 0x01000
#define ICF_NOTIFY_IND_SENDER_PRESENT	 0x02000
#define ICF_NOTIFY_IND_OUT_OF_DIALOG	 0x04000
#define ICF_NOTIFY_IND_USER_ADDR_PRESENT 0x08000
#define ICF_NOTIFY_IND_STRAY             0x10000


    icf_uint32_t bit_mask;

	/*line ID on which the user is present */
	icf_line_id_t                  line_id;
        
    /* Package name for which the notification is received. */

    icf_string_st event_pkg_name;


#define ICF_SUBS_STATE_ACTIVE			1
#define ICF_SUBS_STATE_TERMINATED		0

    /* This is the subscription state received in notify */
    icf_uint8_t      subs_state;

#define ICF_NW_INC_NOTIFY_RETRY_IMM		1
#define ICF_NW_INC_NOTIFY_RETRY_AFTER	2
#define ICF_NW_INC_NOTIFY_NO_RETRY		3

    /* Reason code is present in case of terminated state */
    icf_uint8_t      reason_code;

    /* This duration can be the remaining subscription duration
     * in case of active state and retry after duration in case of
     * terminated state
     */
    icf_duration_t   duration;

    /* Denotes the address of the sender.The address of the remote party 
     * can be an E.164 number or a SIP URL.
     */

    icf_address_st sender;

	/* Denotes the address of the User.The address of the  party 
     * can be an E.164 number or a SIP URL.
     */

    icf_address_st user_address;

    /* List of headers received in the notification which are of importance to
     * the application.
     */
     icf_header_list_st header_list;



    /* List of message bodies received in the notification. */

    icf_msg_body_list_st body_list;

    

} icf_notify_ind_st;

/*NOTIFY_OUT_OF_DIALOG_END*/









/*-----------------------------------------------------------------------------

 *

 * Structure Name:icf_publish_resp_st

 *

 * Description: This API is used by the framework to inform the application.

 *                about the result of an earlier publish request issued by 

 *                the application or on PUBLISH timeout.

 *

 *---------------------------------------------------------------------------*/



typedef struct

{



    icf_uint32_t bit_mask;

    #define ICF_PUB_RESP_RESP_CODE_PRESENT 0X01

    #define ICF_PUB_RESP_ERROR_CODE_PRESENT 0x02

   
    /* Use common hash defines if header list  present */



    /* Indicates the result of the publication (success/failure). */

    icf_return_t result;

    icf_uint32_t error_code ;

    icf_uint32_t duration ;



    /* Response code received for the PUBLISH request. */

    icf_uint32_t response_code ;



    /* Entity-tag received from the ESC after a Initial publication. */

    icf_string_st entity_tag;



    /* List of headers received in the subscription response which are of

     * importance to the application.

     */

     icf_header_list_st header_list;

      /* duration received in retry-after header*/
     icf_duration_t    retry_after_duration; 

} icf_publish_resp_st;
















/*-----------------------------------------------------------------------------

 *

 * Structure Name:icf_message_resp_st

 *

 * Description: This API is used by the framework to inform the application 

 *                about the result of an earlier message request issued by 

 *                the application.

 *

 *---------------------------------------------------------------------------*/



typedef struct

{



    icf_uint32_t bit_mask;

#define ICF_MSG_RESP_RESP_CODE_PRESENT          0X01
#define ICF_MSG_RESP_ERROR_CODE_PRESENT        0x02

    /* Use common hash defines if header list  present */



    /* Indicates the result of the message attempt ( success/failure). */

    icf_return_t result ;


    icf_uint32_t error_code ;



    /* Response code received for the MESSAGE request. */

    icf_uint32_t response_code ;



    /* List of headers received in the message response which are of

     * importance to the application.

     */

     icf_header_list_st header_list;

     /* duration received in retry-after header*/
     icf_duration_t    retry_after_duration; 

} icf_message_resp_st;















/*-----------------------------------------------------------------------------

 *

 * Structure Name:icf_message_ind_st

 *

 * Description: This API is used by the framework to inform the 

 *                application about an incoming MESSAGE.

 *

 *---------------------------------------------------------------------------*/



typedef struct

{



    icf_uint32_t bit_mask;

    #define ICF_MSG_IND_SENDER_PRESENT 0X01

    /* Use common hash defines if header/msg-body list  present */



    /* Denotes the address of the local user.The address of the remote party 

     * can be an E.164 number or a SIP URL.

     */

    icf_address_st sender;



    /* List of headers received in the message which are of importance to

     * the application.

     */

    icf_header_list_st header_list;



    /* List of message bodies received in the message. */

    icf_msg_body_list_st body_list;

    

} icf_message_ind_st;















/*-----------------------------------------------------------------------------

 *

 * Structure Name:icf_refer_resp_st

 *

 * Description: This API is used by the framework to inform the application 

 *                about the result of an earlier REFER request issued by the 

 *                application.

 *

 *---------------------------------------------------------------------------*/



typedef struct

{

    

    icf_uint32_t bit_mask;

    
#define ICF_REF_RESP_RESP_CODE_PRESENT          0X01
#define ICF_REF_RESP_ERROR_CODE_PRESENT        0x02

    /* Use common hash defines if header list  present */



    /* Indicates the result of the REFER (success/failure). */

    icf_return_t result ;



    /* Response code received for the REFER request. */

    icf_uint32_t response_code ;


    /* error cause incase the status is Failure */
     icf_uint32_t error_code ;



    /* List of headers received in the REFER response which are 

     * of importance to the application.

     */

    icf_header_list_st header_list;

    /* duration received in retry-after header*/
    icf_duration_t    retry_after_duration; 

} icf_refer_resp_st;

/*----------------------------------------------------------------------------
 * NAME : ICF_cfg_cc_set_scale_params_req_st
 *
 * Description: This structure is used to specifies payload data of
 *               API ICF_CFG_CC_SET_SCALE_PARAMS_REQ 
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
#define ICF_SET_SCALE_PRM_MAX_LINES                    0x0001
#define ICF_SET_SCALE_PRM_MAX_AUDIO_CALLS            0x0002
#define ICF_SET_SCALE_PRM_MAX_VIDEO_CALLS            0x0004
#define ICF_SET_SCALE_PRM_MAX_SERVICE_CALLS            0x0008
#define ICF_SET_SCALE_PRM_MAX_REGISTRATION_CALLS    0x0010
#define ICF_SET_SCALE_PRM_MAX_USERS_PER_LINE        0x0020
#define ICF_SET_SCALE_PRM_NUM_OF_CALLS_TO_LOG        0x0040
#define ICF_SET_SCALE_PRM_MAX_NUM_OF_APPS            0x0080

     icf_uint16_t            bit_mask;

     /*Maximum number of lines supported by phone*/
     icf_line_id_t      max_lines;
     
     /*Max number of simultaneous calls*/
     icf_uint16_t       max_audio_calls;

     /*Max number of simultaneous video calls*/
     icf_uint16_t       max_video_calls;

     /*Max number of simultaneous service calls*/
     icf_uint16_t       max_service_calls;

     /*Max number of simultaneous registration calls done by phone*/
     icf_uint8_t        max_registration_calls;

     /*Max number of users configured per line*/
     icf_uint8_t        max_users_per_line;

    /* Number of calls to be loged in call log history */
    icf_uint8_t                num_of_calls_to_log;

    /*Indicates the maximum number of applications to be 
    supported which can run simultaneously. 
    The default value of this parameter is 2*/
    icf_uint8_t            max_num_of_apps;

} icf_set_scale_params_req_st;


/*----------------------------------------------------------------------------
 * NAME : icf_trace_nw_buff_ind_st
 *
 * Description: This structure is used to specifies payload data of
 *               API ICF_TRACE_NW_BUFF_IND
 *
 *---------------------------------------------------------------------------*/
typedef struct {
    icf_transport_address_st   nw_address;
    icf_generic_string_st       nw_buffer;
}icf_trace_nw_buff_ind_st;


/*-----------------------------------------------------------------------------
*
* NAME : icf_call_transfer_unattended_req_st
*
* DESCRIPTION  : This data type is used to define a structure,
*               which specifies payload data of API
*               ICF_PA_CC_CALL_TRANSFER_UNATTENDED_REQ.
-----------------------------------------------------------------------------*/

typedef struct
{
    
     /* This is the E.164 number or SIP URI of transferred party.*/
    icf_address_st transferred_party_addr;
    
    /* This field bitwise contains the presence information of optional fields 
     * in this structure.*/

#define ICF_CALL_TRANSFER_UNATTENDED_REQ_TOGGLE_PRESENTATION_INDICATOR 0x01

#define ICF_ADDRESS_ADDNL_URI_PARAMTR_PRES 0x02
    icf_uint32_t bit_mask;
    
    /* This parameter indicates whether user wants to toggle the presentation 
     * indication status for rest of the call.This is optional field.
     * presence_flag: 
     * ICF_CALL_TRANSFER_UNATTENDED_REQ_TOGGLE_PRESENTATION_INDICATOR 
     */
    icf_boolean_t           toggle_presentation_indicator;

    icf_header_list_st	    header_list;
    icf_tag_list_st	    tag_list;
    icf_msg_body_list_st    body_list;
    icf_large_string_st     *p_uri_parameter;
} icf_call_transfer_unattended_req_st;

/*-----------------------------------------------------------------------------
*
* NAME : icf_call_transfer_attended_req_st
*
* DESCRIPTION  : This data type is used to define a structure,
*               which specifies payload data of API
*               ICF_CALL_TRANSFER_ATTENDED_REQ.
-----------------------------------------------------------------------------*/

typedef struct
{

    /* This is call id of call put on hold by IP Phone user.*/
    icf_call_id_t transferred_party_id; 

    icf_uint32_t		bit_mask;

    icf_header_list_st	header_list;
    icf_tag_list_st		tag_list;
    icf_msg_body_list_st	body_list;
}icf_call_transfer_attended_req_st;

/*-----------------------------------------------------------------------------
*
* NAME : icf_remote_call_transfer_initiated_ind_st
*
* DESCRIPTION  : This data type is used to define a structure,
*               which specifies payload data of API
*               ICF_REMOTE_CALL_TRANSFER_INITIATED_IND.
-----------------------------------------------------------------------------*/

typedef struct
{

    /* This is the new call id generated when remote party has initiated call 
     * transfer by sending REFER.*/
    icf_call_id_t new_call_id;        

    /* This is the number of the party to which the call transfer is initiated.
     *  This is received in REFER message.                                      
     */
    icf_address_st referred_party_addr;   
    
    /* This field bitwise contains the presence information of optional fields 
     * in this structure.*/

#define ICF_REFER_INITIATED_REFERRED_PARTY_NAME    0x01

    icf_uint32_t bit_mask;        
    
    /* This parameter contain the name of the party in REFER message.This is 
     * optional field.
     * Presence_flag: ICF_REFER_INITIATED_REFERRED_PARTY_NAME (0x1)
     */
    icf_name_st                 referred_party_name;     

    icf_header_list_st	        header_list;
    icf_msg_body_list_st		body_list;
    
} icf_remote_call_transfer_initiated_ind_st;

/*-----------------------------------------------------------------------------
*
* NAME : icf_call_merged_ind_st
*
* DESCRIPTION  : This data type is used to define a structure,
*                which specifies payload data of API
*                ICF_CALL_MERGED_IND.
-----------------------------------------------------------------------------*/

typedef struct
{

   /* This is call id of “referred to party in REFER. This call_id is same as
    * new_call_id in ICF_REFER_INTIATED API.
    */
    icf_call_id_t merge_call_id;   

} icf_call_merged_ind_st; 

/*-----------------------------------------------------------------------------
*
* NAME : icf_conference_req_st
*
* DESCRIPTION  : This data type is used to define a structure,
*              which specifies payload data of API  ICF_CONFERENCE_REQ.
-----------------------------------------------------------------------------*/

typedef struct
{
   icf_uint32_t            bit_mask;

   /* Identifier of second call which need to be merged with the call with 
    * call_id in API header. */
   icf_call_id_t           merge_call_id;   
   icf_header_list_st      header_list;
   icf_tag_list_st         tag_list;
}icf_conference_req_st;



/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_cfg_cc_set_service_params_req_st 
 *
 * Description: This structure specifies payload data of 
 *              API ICF_SET_SERVICE_PARAMS_REQ 
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{

#define ICF_SET_SER_PRM_SUBSCRIPTION_FLAG       0x00000001
#define ICF_SET_SER_PRM_ACTIVATION_FLAG         0x00000002
#define ICF_SET_SER_PRM_GLB_SUBS_FLAG           0x00000004
#define ICF_SET_SER_PRM_GLB_ACT_FLAG            0x00000008
#define ICF_SET_SER_PRM_CALL_HOLD_OPTION        0x00000010
#define ICF_SET_SER_PRM_MAX_NUM_OF_HOPS         0x00000020
#define ICF_SET_SER_PRM_MAX_CALL_WAITING        0x00000040
#define ICF_SET_SER_PRM_CFU_ADDR                0x00000080
#define ICF_SET_SER_PRM_CFB_ADDR                0x00000100
#define ICF_SET_SER_PRM_CFD_ADDR                0x00000200
#define ICF_SET_SER_PRM_CHR_TIMER               0x00000400
#define ICF_SET_SER_PRM_REINVITE_RACE_TIMER     0x00000800
#define ICF_SET_SER_PRM_TWC_TIMER               0x00001000
#define ICF_SET_SER_PRM_CTU_TIMER               0x00002000
#define ICF_SET_SER_PRM_CTA_TIMER               0x00004000
#define ICF_SET_SER_PRM_RNW_TIMER               0x00008000
#define ICF_SET_SER_PRM_CW_ALERT_TIMER          0x00010000
#define ICF_SET_SER_PRM_CND_ALERT_TIMER         0x00020000
#define ICF_SET_SER_PRM_CW_N_CND_ALERT_TIMER    0x00040000
#define ICF_SET_SER_PRM_SUBS_RESP_TIMER         0x00080000
#define ICF_SET_SER_PRM_SUBS_RETRY_TIMER        0x00100000
#define ICF_SET_SER_PRM_CONF_REQD_AT_TRANFEREE            0x00200000
#define ICF_SET_SER_PRM_CONF_CFM_REQD_AT_TRANSFEREE       0x00400000
#define ICF_SET_SER_PRM_SUBSCRIPTION_REQD_IN_EXT_CONF     0x00800000
#define ICF_SET_SER_PRM_CONFERENCE_URI_PRESENT            0x01000000
       
   /* This bitmask should be set if Application wants to over-ride the default
    * behavior of terminating calls if conference request fails
    */
#define ICF_SET_SER_PRM_CONF_FAIL_CALL_CLEAR_NOT_REQD     0x02000000 
      icf_uint32_t                  bit_mask;

     /*Bitmask specifies services subscribed by the user
      *Presence flag:ICF_CFG_CC_SET_SER_PRM_SUBSCRIPTION_FLAG
      */
     
      /*This is a bitmask, which specifies which services are subscribed
       * by the user. Following are the values which can be filled in status
       *  field in icf_config_status_st  
       */

      
#define ICF_SERVICE_SUBS_CALL_HOLD_RESUME              0x0001
#define ICF_SERVICE_SUBS_THREE_WAY_CALL                0x0002
#define ICF_SERVICE_SUBS_CALL_TRF_ATTENDED             0x0004
#define ICF_SERVICE_SUBS_CALL_TRF_UNATTENDED           0x0008
#define ICF_SERVICE_SUBS_INVITE_WITH_REPLACE           0x0010
#define ICF_SERVICE_SUBS_CALL_TRF_FROM_NW              0x0020
#define ICF_SERVICE_SUBS_CALL_FWD_UNCONDITIONAL        0x0040
#define ICF_SERVICE_SUBS_CALL_FWD_BUSY                 0x0080
#define ICF_SERVICE_SUBS_CALL_FWD_NO_ANSWER            0x0100
#define ICF_SERVICE_SUBS_CALL_WAITING                  0x0200
#define ICF_SERVICE_SUBS_EXTERNAL_CONFERENCE           0x0400
#define ICF_SERVICE_SUBS_JOIN_HEADER                   0x0800      
     icf_config_status_st      service_subscription_flag;
   

     /*Bitmask specifies services activated by the user
      *Presence flag:ICF_CFG_CC_SET_SER_PRM_ACTIVATION_FLAG
      */
     
     /* This is a bitmask,which specifies the service activated by user
      *  Following are the values which can be filled in status field
      *  in icf_config_status_st  */

#define ICF_SERVICE_ACT_CALL_HOLD_RESUME              0x0001
#define ICF_SERVICE_ACT_THREE_WAY_CALL                0x0002
#define ICF_SERVICE_ACT_CALL_TRF_ATTENDED             0x0004 
#define ICF_SERVICE_ACT_CALL_TRF_UNATTENDED           0x0008
#define ICF_SERVICE_ACT_INVITE_WITH_REPLACE           0x0010 
#define ICF_SERVICE_ACT_CALL_TRF_FROM_NW              0x0020
#define ICF_SERVICE_ACT_CALL_FWD_UNCONDITIONAL        0x0040
#define ICF_SERVICE_ACT_CALL_FWD_BUSY                 0x0080
#define ICF_SERVICE_ACT_CALL_FORWARDING_NO_ANSWER     0x0100
#define ICF_SERVICE_ACT_CALL_WAITING                  0x0200
#define ICF_SERVICE_ACT_EXTERNAL_CONFERENCE           0x0400
#define ICF_SERVICE_ACT_JOIN_HEADER                   0x0800 
     icf_config_status_st      service_activation_flag;

     /* This flag decide which option should be used by CC to send call
      * hold indciation to remote party
      * presence_flag: ICF_CFG_CC_SET_SER_PRM_CALL_HOLD_OPTION
      */

     /*icf_hold_option_t             call_hold_option;*/
     /* Per Line Feature - Modified the call hold option to structure */ 
     icf_hold_option_st             call_hold_option;
     
     /* Maximum number of hops for which a call can be forwarded.
      * This is optional field. 
      * presence_flag: ICF_SET_SER_PRM_MAX_NUM_OF_HOPS */

     icf_uint8_t		      max_num_of_call_forwarding_hops;

      /* Maximum number of calls in call waiting simultaneously.
       * After this threshold Call Forwarding with Busy Line
       * will be invoked.
       * This is optional field.
       * presence_flag: ICF_SET_SER_PRM_MAX_CALL_WAITING */

     icf_uint8_t                   max_num_of_calls_in_call_waiting;

     /* address to which the call will be forwarded
      * when call forwarding unconditional service is triggered.
      * This is optional field.
      * presence_flag: ICF_CFG_CC_SET_SER_PRM_CFU_ADDR */

     icf_config_address_st          addr_for_cfu;

     /* address to which the call will be forwarded
      * when call forwarding busy service is triggered.
      * This is optional field.
      * presence_flag: ICF_SET_SER_PRM_CFB_ADDR */

     icf_config_address_st          addr_for_cfb;

     /* address to which the call will be forwarded 
      * when call forwarding don't answer service is triggered.
      * This is optional field.
      * presence_flag: ICF_CFG_CC_SET_SER_PRM_CFD_ADDR*/

     icf_config_address_st          addr_for_cfd;

     /*Duration of call hold resume timer in milliseconds.
      *Presence flag: ICF_SET_SER_PRM_CHR_TIMER
      */

     icf_duration_t                 call_hold_resume_timer;

     /* Duration of reinvite race timer in milliseconds.
      * Presence flag: ICF_SET_SER_PRM_REINVITE_RACE_TIMER
      */

      icf_duration_t                reinvite_race_timer;

     /*Duration of twc timerin milliseconds.
      *Presence flag:ICF_CFG_CC_SET_SER_PRM_TWC_TIMER*/

      icf_duration_t                twc_timer;

     /* Duration of ctu timerin milliseconds. 
      * Presence flag: ICF_CFG_CC_SET_SERVICE_PARAMS_CTU_TIMER */

      icf_duration_t                ctu_timer;

      /*Duration of replace release timerin milliseconds.
       *Presence flag: ICF_SET_SERVICE_PARAMS_CTA_TIMER */

      icf_duration_t                cta_timer;

      /*Duration of rnw timerin milliseconds.
       *Presence flag: ICF_CFG_CC_SET_SER_PRM_RNW_TIMER */

      icf_duration_t                rnw_timer;

      /* Duration of cw alert timerin milliseconds.
       * Presence flag: ICF_SET_SER_PRM_CW_ALERT_TIMER
       */

      icf_duration_t                cw_alert_timer;

      /* Duration of cnd alert timerin milliseconds.
       * Presence flag:
       *  ICF_SET_SER_PRM_CND_ALERT_TIMER */

      icf_duration_t                cnd_alert_timer;

      /* Duration of cw and cnd alert timerin milliseconds.
       * Presence flag:
       *  ICF_SET_SER_PRM_CW_N_CND_ALERT_TIMER */

      icf_duration_t                cw_n_cnd_alert_timer;

      /* Duration of subscribe response timer.in milliseconds.
       * Presence flag: ICF_SET_SER_PRM_SUBS_RESP_TIMER */

      icf_duration_t                subs_resp_timer;

      /* Duration of subscribe retry timerin milliseconds..
       * Presence flag: ICF_SET_SER_PRM_SUBS_RETRY_TIMER */

      icf_duration_t                subs_retry_timer;
     /* flag to establish if media merging is required at transferee
        for creating a local conference */
      icf_boolean_t                 conf_reqd_at_transferee;

     /* flag to estabslish if confirmation is required at transferee
       for call transfer request*/
      icf_boolean_t                 conf_cfm_reqd_at_transferee;

     /*Application can configure URI of conference server, this is per line*/
     icf_config_address_st        conference_uri;

    /* subscription duration for external conference case */
     icf_duration_t                 xconf_subs_duration;

     /* Set this parameter Application does not want calls to be cleared
     * in case conference request fails due to merge media failure or
     * twc timer expiry.
     */  
      icf_boolean_t                 conf_fail_call_clear_not_reqd;

/*ZYXEL porting Amber 20190520 for adding IOPFlag from set service param req into LineParameter for each Line/Acct.*/
#if 1 //ZYXEL_VOIP_PROPAGATE_IOP_BITFLAG_TO_IPTK_AT_RUNTIME_CONFIG.
      icf_config_iopflags_st        ZYXEL_lineDataIOPFlags; //Line based.
#endif
/*ZYXEL porting Amber 20190520*/

} icf_set_service_params_req_st;


/*-----------------------------------------------------------------------------
 *
 * NAME : icf_display_ind_st
 *
 * DESCRIPTION  :  This data type is used to define a structure,which specifies
 *                 payload data of API ICF_DISPLAY_IND. 
 *                 
-----------------------------------------------------------------------------*/

typedef struct
{

    
    /* This parameter identifies the display information.*/
    icf_display_id_t     display_id;    

    /* This field bitwise contains the presence information of optional fields 
     * in this structure.
     */

#define ICF_DISPLAY_IND_DISPLAY_DATA               0x01
#define ICF_DISPLAY_IND_TONE                       0x02

    icf_uint8_t                bit_mask;
    
     /* This parameter contains the integer and string display data. It can
      * store upto 4 integers and 2 strings.This is optional field.
      * presence_flag: ICF_DISPLAY_IND_DISPLAY_DATA (0x01)
      */
    icf_display_data_st        display_data;       
    
     /* This parameter identifies the tone to be  played to  the phone user.
      * This is optional field.
      * presence_flag: ICF_DISPLAY_IND_TONE (0x02)
      */
    icf_tone_id_t              tone_id;   
    
} icf_display_ind_st;

/*------------------------------------------------------------------------------
*
*NAME : icf_call_redirection_ind_st
*
*DESCRIPTION : This data type is used to define a structure,
*               which specifies payload data of 
*               API ICF_CALL_REDIRECTION_IND.
*
------------------------------------------------------------------------------*/

typedef struct
{

      /*This bitwise field contains presence information*/
     
#define ICF_CALL_RDR_IND_PTY_ADDR  0x01 
#define ICF_CALL_RDR_IND_PTY_NAME  0x02 

      icf_uint32_t  bit_mask ;

      /*Address to which call is redirected*/
      icf_address_st  redirected_party_addr;

      /*Name of the party to which call is redirected*/
      icf_name_st  redirected_party_name;

      icf_header_list_st	header_list;

} icf_call_redirection_ind_st;
/***********************************
*    MANAGEMENT PLANE HANDLER APIs *
************************************/


/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_set_mgmt_plane_auth_param_req_st
 *
 * Description: This API is used to configure the management plane authentication 
 *				parameters. The application is required to inform ICF about the 
 *				values of certain parameters to be used in processing of a 
 *				challenge received from a XDM or SyncMl server in a HTTP response. 
 *
 *---------------------------------------------------------------------------*/

typedef struct 
{

/* bitmask for indicating valid/invalid values for optional parameters */

#define ICF_MGMT_PLANE_AUTH_DATA_PRESENT 0x01

	icf_uint16_t		bitmask;

/* if true, indicates that the configuration for this server name is to be deleted, 
else this should always be set to FALSE */
	
	icf_boolean_t        remove_flag;

/* indicates whether this configuration is intended for XCAP / SyncMl based operations */

/*
#define ICF_XCAP_USAGE	0x01
#define ICF_SYNCML_USAGE 0x02 */

	icf_uint8_t		server_type;

/* address of management server */

	icf_transport_address_st	server_addr;

/* authentication algorithm is to be used - for future use */

	icf_uint8_t		auth_method;

/* user name to be used in case the server challenges a request sent by ICF */
	
	icf_string_st		auth_username;

/* password to be used in case the server challenges a request sent by ICF */
	
	icf_string_st		auth_password;

} icf_set_mgmt_plane_auth_param_req_st; 



/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_create_secure_conn_req_st
 *
 * Description: This API is used by Application to request ICF to set up a 
 *				secure TCP connection to peer.  This connection can be used 
 *				either for XCAP or for SyncML messages. 
 *
 *---------------------------------------------------------------------------*/

typedef struct
{

/* Unique exchange ID that will be returned by ICF to application when it 
	sends back the result of the API execution to Application */
	
	icf_uint16_t	exchange_id;
	
/* Indicates the type of usage intended of the connection. Currently only 
	connections to SyncMl and XCAP servers are supported */		

#define ICF_XCAP_USAGE	0x01
#define ICF_SYNCML_USAGE 0x02

	icf_uint8_t		server_type;
	
/* Address of the server with which a secure connection is desired */

	icf_transport_address_st	 server_addr;

} icf_create_secure_conn_req_st;
				
				

/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_create_secure_conn_resp_st
 *
 * Description: This API is used by ICF to send a secure connection set-up 
 *				response.
 *
 *---------------------------------------------------------------------------*/
			
typedef struct 
{

/* Unique exchange ID that will be returned by ICF to application when it 
	sends back the result of the API execution to Application */

	icf_uint16_t	exchange_id;

/* result to convey whether the connection set-up was successful or failure */
 	
	icf_result_t	conn_req_status;

/* A 32-bit handle to the connection context created by ICF. This field is 
	checked when conn_req_status is success*/
	
	icf_uint32_t	conn_handle;

/* defines the error cause when conn_req_status is failure */	
	icf_uint32_t	error_cause;

} icf_create_secure_conn_resp_st;



/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_close_secure_conn_req_st
 *
 * Description: This API is used by Application to close an established secure 
 *				connection.
 *
 *---------------------------------------------------------------------------*/

typedef struct 
{

/* Unique exchange ID that will be returned by ICF to application when it 
	sends back the result of the API execution to Application */

	icf_uint16_t	exchange_id;

/* A 32-bit handle to the connection context created by ICF */

	icf_uint32_t	conn_handle;

} icf_close_secure_conn_req_st;



/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_close_secure_conn_resp_st
 *
 * Description: This API is used by ICF to update the application about the 
 *				status of a previously issued Close Connection Request.
 *
 *---------------------------------------------------------------------------*/

typedef struct 
{
	
/* Unique exchange ID that will be returned by ICF to application when it 
	sends back the result of the API execution to Application */

	icf_uint16_t	exchange_id;

/* result to convey whether the connection close was successful or failure */	

	icf_result_t	close_conn_status;

/* A 32-bit handle to the connection for which a close was requested */	

	icf_uint32_t	conn_handle;

/* defines the error cause when close_conn_status is failure */	
	
	icf_uint32_t	error_cause;

} icf_close_secure_conn_resp_st;



/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_secure_conn_status_ind_st
 *
 * Description: This API is used by ICF to update the application about the 
 *				status of an established connection. This is triggered due 
 *				to change in the status of the connection (for e.g closure of 
 *				connection by peer).
 *
 *---------------------------------------------------------------------------*/

typedef struct 
{

/* status field to convey the status of the connection */

#define ICF_SECURE_CONN_CLOSED_BY_PEER		        0x01
#define ICF_SECURE_CONN_TIME_OUT			        0x02
#define	ICF_REATTEMPTING_SECURE_CONNECTION          0x03
#define	ICF_REATTEMPTED_SECURE_CONNECTION_SUCCESS	0x04
#define	ICF_REATTEMPTED_SECURE_CONNECTION_FAILURE	0x05
#define ICF_CONN_STATUS_GPRS_SUSPENDED              0x08

	icf_uint8_t		conn_status;

/* A 32-bit handle to the connection context created by ICF */
	
	icf_uint32_t	conn_handle;

/* A 32-bit handle to the connection context created by ICF */
	icf_uint32_t	old_conn_handle;

} icf_secure_conn_status_ind_st;



/*----------------------------------------------------------------------------
 *
 *  icf_xcap_res_et - This data type is used to define value of type 
 *					  icf_uint8_t that indicates the resource type of 
 *					  MPH request.
 *
 *--------------------------------------------------------------------------*/

typedef enum{

ICF_INVALID_RES,
ICF_XCAP_RES_DOC,
ICF_XCAP_RES_ELEM,
ICF_XCAP_RES_ATTR

}icf_xcap_res_et;



/*----------------------------------------------------------------------------
 *
 *  icf_stretchable_hdr_st - This data type is used to define a stretchable 
 *							 header for which length is indicated.
 *
 *--------------------------------------------------------------------------*/

typedef struct
{
icf_uint8_t   hdr_len;
icf_uint8_t  *p_hdr;         
} icf_stretchable_hdr_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_create_replace_res_req_st
 *
 * Description: This API is used by ICF to update the application about the 
 *				status of a previously issued Close Connection Request.
 *				Indicates whether the request pertains to an operation on a
 *				document, element within a document or attribute of an element 
 *				within a document 
 *
 *---------------------------------------------------------------------------*/

typedef struct 
{

/* bitmask for indicating valid/invalid values for optional parameters */

#define ICF_NO_RESP_DURATION_PRESENT	0x01
#define ICF_ACCEPT_PRESENT				0x02
#define ICF_IF_MATCH_PRESENT			0x04
#define ICF_IF_NONE_MATCH_PRESENT		0x08
#define ICF_ACCEPT_ENCODING_PRESENT		0x10
#define ICF_CONTENT_ENCODING_PRESENT	0x20
#define ICF_HIGH_PRIORITY_REQ			0x40

	icf_uint8_t		bitmask;

/* Unique exchange ID that will be returned by ICF to application when it 
	sends back the result of the API execution to Application */

	icf_uint16_t	exchange_id;

/* A 32-bit handle to the connection context created by ICF */

	icf_uint32_t	conn_handle;

/* escape-encoded requested URI to be sent in outgoing HTTP request */

	icf_req_uri_st	request_uri;

/* origin server/host server name to be sent in the outgoing HTTP request */

	icf_transport_address_st	host_name;

/* whether the request pertains to an operation on a document, element 
	within a document or attribute of an element within a document */

	icf_xcap_res_et	res_type;

/* value for content type header in outgoing HTTP request */

	icf_string_st	content_type;

/* duration of time for which ICF will wait for response on connection */

	icf_duration_t	timer_duration;

/* value for Accept header in outgoing HTTP request. This field will be ignored if res_type is ICF_XCAP_RES_DOC */

	icf_stretchable_hdr_st	accept;

/* value for if_match header in outgoing HTTP request.  */

	icf_stretchable_hdr_st	if_match;

/* value for if_none_match header in outgoing HTTP request.  */

	icf_stretchable_hdr_st	if_none_match;

/* value for accept_encoding header in outgoing HTTP request. */

	icf_stretchable_hdr_st	accept_encoding;

/* value for content_encoding header in outgoing HTTP request */

	icf_stretchable_hdr_st	content_encoding;

/* length of the payload  */

	icf_uint32_t		payload_length;

/* stretchable array for the XML payload. This payload will be 
	transparently attached to the outgoing HTTP message as message body. */

	icf_uint8_t 	*payload;

} icf_create_replace_res_req_st;



/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_delete_res_req_st
 *
 * Description: This API is used by the application to delete an XCAP resource 
 *				on the document server. 
 *
 *---------------------------------------------------------------------------*/

typedef struct 
{
/* bitmask for indicating valid/invalid values for optional parameters */
/* 
ICF_IF_MATCH_PRESENT 
ICF_IF_NONE_MATCH_PRESENT
ICF_NO_RESP_DURATION_PRESENT */

	icf_uint8_t		bitmask;

/* Unique exchange ID that will be returned by ICF to application when it 
	sends back the result of the API execution to Application */

	icf_uint16_t	exchange_id;

/* A 32-bit handle to the connection context created by ICF */

	icf_uint32_t	conn_handle;

/* escape-encoded requested URI to be sent in outgoing HTTP request */

	icf_req_uri_st	request_uri;

/* origin server/host server name to be sent in the outgoing HTTP request */

	icf_transport_address_st	host_name;

/* whether the request pertains to an operation on a document, element 
	within a document or attribute of an element within a document */

	icf_xcap_res_et	res_type;

/* duration of time for which ICF will wait for response on connection */

	icf_duration_t	timer_duration;

/* value for Accept header in outgoing HTTP request. This field will be ignored if res_type is ICF_XCAP_RES_DOC */

	icf_stretchable_hdr_st	accept;

/* value for if_match header in outgoing HTTP request.  */

	icf_stretchable_hdr_st	if_match;

/* value for if_none_match header in outgoing HTTP request.  */

	icf_stretchable_hdr_st	if_none_match;

} icf_delete_res_req_st;
	


/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_fetch_res_req_st
 *
 * Description: This API is used by the application to fetch an XCAP resource 
 *				on the document server. 
 *
 *---------------------------------------------------------------------------*/
	
typedef struct 
{
/* bitmask for indicating valid/invalid values for optional parameters */
/* 
ICF_IF_MATCH_PRESENT 
ICF_IF_NONE_MATCH_PRESENT
ICF_NO_RESP_DURATION_PRESENT */

	icf_uint8_t		bitmask;

/* Unique exchange ID that will be returned by ICF to application when it 
	sends back the result of the API execution to Application */

	icf_uint16_t	exchange_id;

/* A 32-bit handle to the connection context created by ICF */

	icf_uint32_t	conn_handle;

/* escape-encoded requested URI to be sent in outgoing HTTP request */

	icf_req_uri_st	request_uri;

/* origin server/host server name to be sent in the outgoing HTTP request */

	icf_transport_address_st	host_name;

/* whether the request pertains to an operation on a document, element 
	within a document or attribute of an element within a document */

	icf_xcap_res_et	res_type;


/* duration of time for which ICF will wait for response on connection */

	icf_duration_t	timer_duration;


/* value for if_match header in outgoing HTTP request */

	icf_stretchable_hdr_st	if_match;

/* value for if_none_match header in outgoing HTTP request */

	icf_stretchable_hdr_st	if_none_match;

} icf_fetch_res_req_st;



/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_syncml_send_req_st
 *
 * Description: This API is used by application to trigger ICF to send a HTTP 
 *				POST request with application supplied SyncMl message body 
 *				to Device Management server. 
 *
 *---------------------------------------------------------------------------*/

typedef struct 
{

/* bitmask for indicating valid/invalid values for optional parameters */

#define ICF_HEADER_LIST_PRESENT 0x80

	icf_uint8_t		bitmask;

/* Unique exchange ID that will be returned by ICF to application when it 
	sends back the result of the API execution to Application */

	icf_uint16_t	exchange_id;

/* A 32-bit handle to the connection context created by ICF */

	icf_uint32_t	conn_handle;

/* content type field for the outgoing message */

	icf_string_st	content_type;

/* value of cache-control header in outgoing HTTP request */

	icf_string_st	cache_control;

/* value of transfer_encoding header in outgoing HTTP request */

	icf_string_st	transfer_encoding;

/* value of user_agent header in outgoing HTTP request */

	icf_string_st	user_agent;

/* value of accept header in outgoing HTTP request */

	icf_string_st	accept;

/* value of accept_char header in outgoing HTTP request */

	icf_string_st	accept_char;

/* duration of time for which ICF will wait for response on connection */

	icf_duration_t	timer_duration;

/* list of additional headers that the application wants to send in the outgoing request */

	icf_header_list_st  header_list;

/* length of the payload  */

	icf_uint32_t		payload_length;

/* stretchable array for the XML payload. This payload will be 
	transparently attached to the outgoing HTTP message as message body. */

	icf_uint8_t 	*payload;

} icf_syncml_send_req_st;



/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_api_proc_failure_st
 *
 * Description: This API is used by ICF to inform the application about 
 *				the failure of processing of an earlier XCAP/SyncML 
 *				APIs. The exchange-id passed by the application is returned 
 *				so as to help application correlate the request and this API.  
 *
 *---------------------------------------------------------------------------*/
	
typedef struct 
{

/* Unique exchange ID that will be returned by ICF to application when it 
	sends back the result of the API execution to Application */

	icf_uint16_t	exchange_id;

/* A 32-bit handle to the connection context created by ICF */

	icf_uint32_t	conn_handle;

/* defines the api_id of the request that failed */

	icf_api_id_t	api_id;

/* defines the error cause */	

	icf_error_t	error_cause;

} icf_api_proc_failure_st;

	

/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_mgmt_plane_nw_resp_st
 *
 * Description: This API is used by ICF to convey a received response from 
 *				server to application.  
 *
 *---------------------------------------------------------------------------*/
	
typedef struct
{

/* bitmask for indicating valid/invalid values for optional parameters */

#define ICF_ENTITY_TAG_PRESENT		            0x01
#define ICF_CONTENT_TYPE_PRESENT	            0x02
#define ICF_CONNECTION_STATUS_PRESENT           0x04

	icf_uint8_t       bitmask;

/* API ID given by application for which the HTTP request was dispatched */
	
	icf_api_id_t      req_api;

/* Unique exchange ID that will be returned by ICF to application when it 
	sends back the result of the API execution to Application */

	icf_uint16_t	exchange_id;

/* reference to the connection (connection handle) on which the 
	message was received */

	icf_uint32_t      conn_handle;

/* entity tag in the received message */
	
	icf_stretchable_hdr_st  entity_tag;

/* content type field in the received message */

	icf_string_st  content_type;

/* Below Values of connection header will be present */
#define ICF_CONN_STATUS_CLOSE_WITH_REATTEMPT       0x01
#define ICF_CONN_STATUS_CLOSE_WITH_NO_REATTEMPT    0x02

/* Specifies the value of connection header if present in the payload */

    icf_uint8_t       connection_status;

/* list of additional headers as per Syncml/XCAP HTTP binding */

	icf_header_list_st  header_list;

/* enumeration value for the response code in the received HTTP response */		

	icf_uint32_t   response_code;
		
/* length of the payload  */

	icf_uint32_t		payload_length;

/* received payload */

	icf_uint8_t		*payload;

} icf_mgmt_plane_nw_resp_st;


/*ICF_HANDLE_REINVITE_START*/


/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_incoming_call_modify_ind_st
 *
 * Description: This API is used by ICF to send the Application an indication 
 * 				for the Media Change Request
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
		/* ICF REL 6.0: multiple m lines */
#define ICF_INC_CALL_ACCEPT_STREAM_LIST_PRESENT		0x01
#define ICF_INC_CALL_MOD_DELETED_STREAM_PRESENT		0x02
/* This indicates presence of optional field offer_required */    
#define ICF_INC_CALL_MOD_OFFER_REQUIRED_PRESENT	    0x04
#define ICF_INC_CALL_MOD_SETTINGS_PRESENT	        0x08
	icf_uint32_t 			bit_mask ;
		
    /* If this flag is TRUE then application needs to send confirmation for the
     call modify indication. If FALSE, no need to send any confirmation and if
     sent, it will be ignored at ICF */
    icf_boolean_t           confirm_required;

    /* List of additional headers that are of importance to the application. */
	icf_header_list_st 		header_list;
		
    /* List of additional message bodies that are of importance to the 
	 * application. */
	icf_msg_body_list_st 	body_list ;

	/* ICF REL 6.0: multiple m lines */
	/* information of the accepted/commited media streams for the received 
	 * INVITE. This is a list of the node type icf_call_modify_media_data_st */
	icf_list_st				*p_active_stream_list;

	/* this is a list of rejected/deleted streams. The information shared with 
	 * APP here is the stream id and the corresponding stream_type. This is 
	 * an optional field */
	icf_stream_id_t			count;
	icf_stream_list_st		deleted_stream_list[ICF_MAX_STREAM_PER_CALL];
    /* This will be set when a ReINVITE without SDP is received from the peer 
       and IPTK is giving this indication to the application.
    */    
    icf_boolean_t			 offer_required;

    /* this field indicates any incoming call modiy genaric settings
     */
    /* this bit indicates that 100rel in received in Require header
     * in the incoming reINVITE
     */ 
#define ICF_INC_CALL_MOD_100REL_IN_REQUIRE         0x01
   icf_uint32_t             call_modify_settings;

} icf_incoming_call_modify_ind_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_call_modify_cfm_st
 *
 * Description: This API is sent by application as the response to the media change request.  
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
	icf_uint32_t			bit_mask;
#define ICF_CALL_MODIFY_RESPONSE_CODE_PRESENT      0x01
#define ICF_CALL_MODIFY_CFM_REJECTED_STREAM_PRESENT  0x02
#define ICF_CALL_MODIFY_RESPONSE_SIGNALING_MODE_PRESENT  0x04

	/* The Accept / Reject response including the SDP*/
	icf_result_t			result;

	/* If reject respose, cause of rejection */
	icf_error_t				cause;

      /* This is the nw_response_code application wants IPTK to send */
        icf_uint16_t            nw_response_code;
		
	/* List of additional headers that are of importance to the application. */
	icf_header_list_st		header_list;

	/* List of additional tags that the application wants to send in the API. */
	icf_tag_list_st			tag_list;

	/* List of additional message bodies that are of importance to the 
	 * application. */
	icf_msg_body_list_st	body_list ;

	/* this is a list of the type: icf_stream_capab_st. This field will be used
     * only to pick the stream level encoded attributes for a stream. Any other
     * field in this structure will be ignored within ICF */
	icf_list_st              *p_stream_list;

	/* this is a list of rejected/deleted streams. The information given by 
	 * APP here is the stream id and the corresponding stream_type. This is 
	 * an optional field */
	icf_stream_id_t	        count;
	icf_stream_list_st      deleted_stream_list[ICF_MAX_STREAM_PER_CALL];

      /* In this field, application can specify the mode to be sent to remove 
       * in 200 ok of REINVITE. Note that this will only be the signaling mode. 
       * IPTK will not change mediamode based on this mode. IPTK will change 
       * the local media mode based on the mode received in answer SDP in ACK */
       icf_media_mode_t	         signaling_mode;
       
} icf_call_modify_cfm_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_call_modify_req_st
 *
 * Description	 : This API is sent by application as the media change 
 * 				   request.  
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
  	icf_uint32_t			bit_mask;
	/* ICF REL 6.0: multiple m lines */
#define ICF_CALL_MOD_REQ_MEDIA_MOD_LIST_PRESENT     0x01
#define ICF_CALL_MOD_REQ_DELETED_STREAM_PRESENT		0x02
/*  Rel 8.1 bitmask for to tag */
#define ICF_CALL_MOD_REQ_TO_TAG_PRESENT             0x04
#define ICF_CALL_MOD_REQ_TUNNELLED_SDP_PRESENT             0x08

	/* List of additional headers that are of importance to the application. */
	icf_header_list_st		header_list;

	/* List of additional tags that the application wants to send in the API. */
	icf_tag_list_st			tag_list;

	/* List of additional message bodies that are of importance to the 
	 * application. */
	icf_msg_body_list_st	body_list ;
	
	/* ICF REL 6.0: multiple m lines */
	/* the information here will be list of streams that the application
	 * wishes to modify (only) during mid-call. the application can only 
	 * modify the codecs or the mode for a stream. Optionally it can also 
	 * modify the encoded attributes for the application stream. 
	 * This is a list of the type icf_call_modify_media_data_st. This 
	 * is an optional field in this structure. the application may decide not 
	 * to change the media infomration for the established call. 
	 */
	icf_list_st				*p_media_modify_list;
	
	/* the application may delete any stream mid-call. This is 
	 * optional. */
	icf_stream_id_t			count;
	icf_stream_list_st	    deleted_media_streams[ICF_MAX_STREAM_PER_CALL];	
    /* Rel 8.1
     * This field shall be used to identify
     * the dialog in case of forking.
     * It shall be ignored once call is connected
     */
    icf_string_st                    to_tag;  
    /*  Rel 8.1
     *  This boolean will indicate that
     *  SDP would be sent in UPDATE/ReInvite
     *  or not
     */
    icf_boolean_t                    tunnelled_sdp_present;
} icf_call_modify_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_call_modify_resp_st
 *
 * Description   : This API is sent to application as the cfm to media change 
 * 				   request.  
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
#define  ICF_RESPONSE_CODE_PRESENT					0x01
	/* ICF REL 6.0: multiple m lines */
#define  ICF_CALL_MOD_ACCEPT_STREAM_LIST_PRESENT	0x02
#define  ICF_CALL_MOD_RESP_REJECT_STREAM_PRESENT	0x04
	icf_uint32_t			bit_mask;
	
	/* The Accept / Reject response */
	icf_result_t			result;

	/* If reject respose, cause of rejection */
	icf_error_t			error_cause ;

	/* The response code of the call modify request*/
	icf_uint32_t		response_code;

	/* List of additional headers that are of importance to the application. */
	icf_header_list_st		header_list;

	/* List of additional message bodies that are of importance to the 
	 * application. */
	icf_msg_body_list_st		body_list ;

	/* ICF REL 6.0: multiple m lines */
	/* information of the accepted/commited media streams for the received 
	 * INVITE. This is a list of the node type icf_call_modify_media_data_st */
	icf_list_st				*p_active_stream_list;

	/* this is a list of rejected/deleted streams. The information shared with 
	 * APP here is the stream id and the corresponding stream_type. This is 
	 * an optional field */
	icf_stream_id_t			count;
	icf_stream_list_st		deleted_stream_list[ICF_MAX_STREAM_PER_CALL];

        /* duration received in retry-after header*/
        icf_duration_t    retry_after_duration;
} icf_call_modify_resp_st;

/************************************************************************
 *
 * DESCRIPTION:  This function would initialize the entire ICF
 *                
 *
 ************************************************************************/

extern icf_return_t 
icf_init(
        	icf_init_param_st	*p_init_param,
			icf_void_t			**p_p_icf_glb_data);


/*ICF_HANDLE_REINVITE_END*/

/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_res_unavail_ind_st
 *
 * Description: This API is sent by ICF to the aplication when ICF is being
 * 				depleted of resources and it is not in a position to handle new
 * 				requests. The retry_after parameter in the payload is an 
 * 				indication for the application to retry after some time.
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
	icf_api_id_t			req_api_id;
	icf_result_t			result;
	icf_error_t				cause;
	
	icf_uint8_t				retry_after;
} icf_res_unavail_ind_st;


/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_call_hold_req_st
 *
 * Description: This is payload of call hold request from application
 *              
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
	icf_uint32_t		bit_mask;
    icf_header_list_st	    header_list;
    icf_tag_list_st		    tag_list;
    icf_msg_body_list_st	body_list;
    icf_stream_id_list_st	    stream_list;

} icf_call_hold_req_st;


/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_call_resume_req_st
 *
 * Description: This is payload of call resume request from application
 *              
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
	icf_uint32_t		bit_mask;
    icf_header_list_st	    header_list;
    icf_tag_list_st		    tag_list;
    icf_msg_body_list_st	body_list;
    icf_stream_id_list_st	    stream_list;

} icf_call_resume_req_st;


/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_api_resp_st
 *
 * Description: This is payload to send common responses to application
 *              
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
	icf_uint32_t		    bit_mask;
    icf_result_t		    result;
    icf_error_t		        error_cause;
    icf_header_list_st	    header_list;
    icf_msg_body_list_st	body_list;
    icf_stream_id_list_st	    stream_list;

    /* duration received in retry-after header*/
    icf_duration_t    retry_after_duration;
} icf_api_resp_st;


/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_ctu_resp_st
 *
 * Description: This is payload to send CTU responses to application
 *              
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
    icf_uint32_t		bit_mask;
    icf_result_t		result;
    icf_error_t			error_cause;
    icf_header_list_st	header_list;
   
    /* duration received in retry-after header*/
    icf_duration_t    retry_after_duration; 

} icf_ctu_resp_st;


/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_cta_resp_st
 *
 * Description: This is payload to send CTA responses to application
 *              
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
    icf_uint32_t		bit_mask;
    icf_result_t		result;
    icf_error_t			error_cause;
    icf_header_list_st	header_list;
   
    /* duration received in retry-after header*/
     icf_duration_t    retry_after_duration;
 
} icf_cta_resp_st;

/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_api_ind_st
 *
 * Description: This is payload to send remote hold indication and resume 
 *              indication
 *              
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
	icf_uint32_t		    bit_mask;
    icf_header_list_st	    header_list;
    icf_msg_body_list_st	body_list;
    icf_stream_id_list_st	    stream_list;
} icf_api_ind_st;


/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_party_replaced_ind_st
 *
 * Description: This is payload to send indication that remote party of the call
 *              has been replaced by the new party
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
    icf_uint32_t		bit_mask ;
    
#define ICF_REPLACING_PARTY_ADDR_PRESENT    0x00000001
#define ICF_PARTY_REPLACED_NAME		        0x00000002
    
    icf_call_id_t		replacing_call_id;
    icf_address_st		replacing_party_addr;
    icf_name_st			replacing_party_name;
    icf_header_list_st	header_list;
    icf_msg_body_list_st    body_list;
    icf_stream_id_list_st	stream_list;
} icf_party_replaced_ind_st;


#ifdef ICF_FAX_SUPPORT
/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_start_fax_req_st
 *
 * Description: This is payload to start fax request from Application
 *              
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
#define ICF_START_FAX_REQ_METHOD_PRESENT 0x01
#define ICF_START_FAX_REQ_PT_PARAM_PRESENT  0x02
/*CSR 1-6200296: New bit in case APP wants the call to be cleared if
  FAX is rejected by 415*/
#define ICF_START_FAX_REQ_CLEAR_CALL_ON_415 0x04
   
      icf_uint8_t bitmask;
      icf_uint8_t         pt_param;
#define ICF_START_FAX_PT_PARAM_SILENCE_SUPP    0x01
#define ICF_START_FAX_PT_PARAM_VBD_GPMD        0x02  
#define ICF_START_FAX_PT_PARAM_ECHO_CANC       0x04

      /* Method to be used to send fax to remote party*/
      icf_fax_start_type_t  fax_type;
	/*Preffered codec for fax pass through */
      icf_fax_pt_codec_t  fax_pt_codec;

      icf_uint8_t fax_method;
}icf_start_fax_req_st;

/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_start_fax_resp_st
 *
 * Description: This is payload to send response to fax start req to Application
 *              
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* bitmask added for retyr after handling */
    icf_uint32_t                 bit_mask;
 
    icf_result_t	     	result;

	/* Error cause is set if result is failure*/
	icf_error_t			   error_cause;

	/* This field will indicate if fax call is running
	 * using T38 or G711PT method */
	icf_fax_start_type_t   fax_type;
   
    /* duration received in retry-after header*/
    icf_duration_t    retry_after_duration;
}icf_start_fax_resp_st;

/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_start_fax_ind_st
 *
 * Description: This is payload to send fax start indication to Application
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
	/* This field will indicate if fax call is running
	 * using T38 or G711PT method 
	 * NOTE: In this release fax_type will be only T38
	 */
	icf_fax_start_type_t   fax_type;

}icf_start_fax_ind_st;
#endif




/*NOTIFY_OUT_OF_DIALOG_START*/
/*-----------------------------------------------------------------------------
 *
 * Structure Name:	icf_notify_cfm_st
 *
 * Description: This API is used by the application to inform the framework.
 *                about the result of an the notify request received  by 
 *                the application.
 *---------------------------------------------------------------------------*/

typedef struct
{
#define ICF_NOTIFY_ERROR_CAUSE_PRESENT		0x10000
#define ICF_NOTIFY_RESP_CODE_PRESENT		0x20000

	icf_uint32_t bit_mask;

    /* Indicates the result of the notify (success/failure). 
		success : 1 and failure : 0 */
    icf_result_t result;

   	icf_error_t error_code ;
	    
	/* Response code to be sent for the NOTIFY request. */
    icf_uint32_t response_code ;
    
    /* List of additional headers that the application wants to send in the
     * notify response.
     */
    icf_header_list_st    header_list;

    /* List of additional tags that the application wants to send in the 
     * notify response.
     */
    icf_tag_list_st       tag_list;

    /* List of additional message bodies that the application wants to send
       in the notify response.
     */
    icf_msg_body_list_st  body_list;
} icf_notify_cfm_st;

/*NOTIFY_OUT_OF_DIALOG_END*/

/*HANDLE_INFO_IND_START*/
/*-----------------------------------------------------------------------------
*
* NAME :		 icf_info_ind_st
*
* DESCRIPTION  : This data type is used to define a structure,
*                which specifies payload data of API
*                ICF_INFO_IND.
-----------------------------------------------------------------------------*/

typedef struct
{
    icf_uint32_t		bit_mask;
                
    icf_header_list_st	    header_list;
    icf_msg_body_list_st	body_list;

} icf_info_ind_st;

/*HANDLE_INFO_IND_END*/

/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_info_resp_st
 *
 * Description: This is payload of API (ICF_INFO_RESP)  to send 
 *				INFO responses to application
 *              
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
    icf_uint32_t			bit_mask;
    icf_result_t			result;
    icf_error_t				error_cause;
	icf_uint32_t			response_code;
    icf_header_list_st		header_list;
	icf_msg_body_list_st    body_list;
    
} icf_info_resp_st;

/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_call_forwarded_ind_st
 *
 * Description: This is payload of API (ICF_CALL_FORWARDED_IND)  to send 
 *				call forwarded indication to application that an incoming call
 *              has been forwarded.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* This is the address of remote party of the call which is forwarded*/
    icf_address_st remote_party_addr;   
    
    /* This field bitwise contains the presence information of optional fields 
     * in this structure.*/

#define ICF_REMOTE_PARTY_NAME    0x01

    icf_uint32_t bit_mask;
    
    icf_name_st                 remote_party_name;

#define ICF_CALL_FORWARD_TYPE_UNCOND        1
#define ICF_CALL_FORWARD_TYPE_NO_ANSWER     2
#define ICF_CALL_FORWARD_TYPE_BUSY_LINE     3
    icf_uint8_t                 call_forwarded_type;
} icf_call_forwarded_ind_st;


/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_options_req_st
 *
 * Description: This API is used by the application to send an OPTIONS request 
 *				to query the capabilities of peer.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* Use common hash defines if header/msg-body/tag list present */
	icf_uint32_t bit_mask;
    /* This bit indicates presence of optional field tunnel_mode */
    #define   ICF_OPTIONS_TUNNEL_MODE_OPERATION_PRESENT  0x01
    /* This bitmask is set when Application mentions the list of headers
     * which need not to be send on network in OPTIONS request.
     */ 
    #define  ICF_OPTIONS_REQ_REMOVE_HDR_LIST_PRESENT     0x02

	/*Line-id that has been used for outgoing request*/
	icf_line_id_t line_id;

    /* Indicates the SIP URL of the remote user to which OPTIONS request has
     * to be sent.
     */
    icf_address_st destination_info;

    /* Indicates the Preferred Identity, which shall be used at the P-CSCF for
     * asserted identity in trusted networks.
     */
    icf_address_st pref_identity;

    /* List of additional headers that the application wants to send in the
     * OPTIONS request
     */
    icf_header_list_st header_list;

    /* List of additional tags that the application wants to send in the 
     * OPTIONS request.
     */
    icf_tag_list_st tag_list;

    /* List of message bodies that the application wants to send in the
     * OPTIONS request.
     */
    icf_msg_body_list_st body_list;
    /* This field indicates that the application wants to enable 
       tunnel mode of operation.
    */   
    icf_boolean_t	tunnel_mode;
    /* This field is a list of non-madatory headers that the application wants 
     * to remove form out of dialog OPTIONS sip message before sending on
     * network.
     */
    icf_header_name_list_st remove_hdr_list;

} icf_options_req_st;


/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_options_resp_st
 *
 * Description: This API is used by ICF to inform the application about the
 *              result of an earlier OPTIONS request issued by the
 *              application.
 *---------------------------------------------------------------------------*/
typedef struct 
{
	icf_uint32_t			bit_mask;
#define  ICF_OPTIONS_RESP_CODE_PRESENT		             0x01
#define  ICF_OPTIONS_ERROR_CODE_PRESENT					 0x02
#define  ICF_OPTIONS_REMOTE_STREAM_LIST_PRESENT	         0x04

	/* The Accept / Reject response */
	icf_result_t			result;

	/* If reject respose, cause of rejection */
	icf_error_t				error_code_for_options;

	/* The response code of the OPTIONS request*/
	icf_uint32_t			response_code_for_options;

	/* List of additional headers that are of importance to the application. */
	icf_header_list_st		header_list;
	/* List of additional message bodies that are of importance to the 
	 * application. */
	icf_msg_body_list_st	body_list;

	/*This is a list of the node type icf_stream_capab_st */
	/*This contains the media capabilities of the peer as received in response 
	 *to OPTIONS request
	 */
	icf_list_st				*p_remote_stream_list;

} icf_options_resp_st;


/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_inc_options_ind_st
 *
 * Description: This API is used by ICF to inform the application about the 
 *		incoming OPTIONS request.Moreover, it tells about the currently 
 *		supported capabilities of that application by Media Manager.
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* Use common hash defines if header/msg-body/tag list present */
	icf_uint32_t 		bit_mask;
#define ICF_INC_OPTIONS_IND_MEDIA_PRESENT		0x01

    /* List of additional headers that the application currently supports in its profile
     */
    icf_header_list_st 	header_list;

    /* List of additional tags that the application currently supports in its profile
     */
    icf_tag_list_st 	tag_list;

    /* List of message bodies that the application currently supports in its profile
    */
    icf_msg_body_list_st body_list;

	/* 
	 * This is a list of the node type icf_stream_capab_st */
	/* This structure contains capabilities present in the application profile.
	 * This contains the capabilities that are returned by the Media Manager for 
	 * that application.
	 */
	icf_list_st			*p_app_sdp_list;
    icf_line_id_t                     line_id;
} icf_inc_options_ind_st;

/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_options_cfm_st
 *
 * Description: This API is used by the application to confirm incoming OPTIONS 
 * 		request indication. This will tell the final response to be sent
 * 		on the network for incoming OPTIONS.
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* Use common hash defines if header/msg-body/tag list present */
	icf_uint32_t 			bit_mask;
#define ICF_OPTIONS_CFM_MEDIA_PRESENT		0x01
#define ICF_OPTIONS_CFM_DEL_MEDIA_PRESENT	0x02
#define ICF_OPTIONS_CFM_FAILURE_RESP_PRESENT    0x04

	/* the application can decide to accept or reject a call following the
	 * OPTIONS request that has been received. If the application returns
	 * failure in the CFM, ICF will respond to the received OPTIONS with a 
	 * 486 */
	icf_result_t			result;

	/* List of additional headers that the application wants to send in the
     * OPTIONS request
     */
    icf_header_list_st 		header_list;

    /* List of additional tags that the application wants to send in the 
     * OPTIONS request.
     */
    icf_tag_list_st 		tag_list;

    /* List of message bodies that the application wants to send in the
     * OPTIONS request.
     */
    icf_msg_body_list_st 	body_list;

	/* This is a list of the node type icf_stream_capab_st */ 
	/* This structure contains capabilities modified by the application
	 * If Incoming OPTIONS contains Accept Header with value as application/sdp, 
	 * then this is set and contains SDP that is to be sent in 200ok.
	 * Application can modify the attributes of the streams and can add only 
	 * encoded attributes of the stream. However, it can add only application 
	 * based streams. 
     * The application can add a media stream to this list only if the media stream
     * is already configured by the application in the media profile in app_conf
     * during ICF_APP_ADD 
	 */
     icf_list_st			*p_app_sdp_list;

	/* the application can reject a complete media stream it it desires */
	icf_stream_id_t			count;
	icf_stream_list_st		deleted_media_streams[ICF_MAX_STREAM_PER_CALL];	
    /* response code for sending options resp on network.
    * This would be taken care if application set result as FAILURE. 
    */
    icf_uint32_t   response_code;

} icf_options_cfm_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_set_line_param_req_st
 *
 * Description: This API is used by the application to set  
 * sip timers duration (t1, t2,B and F), registration head start 
 * duration and subscription head start duration. on a line. 
 *-----------------------------------------------------------------------------*/


typedef struct 
{
	/* Mandatory Parameters */

	icf_line_id_t			line_id;
	icf_uint32_t			bitmask;

	/* This Bit mask will be set when sending subscribe
 	* head start duration */

#define ICF_SET_LINE_PRM_SUBS_HS_TIMER	    	 0x01

   	/* This Bit Mastk will be set when sending t1 timer 
 	* duration */

#define ICF_SET_LINE_PRM_T1_TIMER				0x02

	/* This Bit Mastk will be set when sending t2 timer 
	 * duration */

#define ICF_SET_LINE_PRM_T2_TIMER		     	0x04

       /* This Bit Mastk will be set when sending B timer 
 	* duration */

#define ICF_SET_LINE_PRM_INV_TIMER		     	0x08

       /* This Bit Mastk will be set when sending F timer 
 	* duration */

#define ICF_SET_LINE_PRM_NON_INV_TIMER	     	0x10

/*Start : Per Line Feature */
#define ICF_SET_LINE_SIP_DSCP                   0x20

#define ICF_SET_LINE_RTP_DSCP                   0x40

#ifdef ICF_SESSION_TIMER
#define ICF_SET_LINE_MIN_SE                     0x80
#define ICF_SET_LINE_SESSION_TIMER              0x0100
#define ICF_SET_LINE_SESSION_TIMER_REFRESHER    0x0200
#endif
#define ICF_SET_LINE_AUDIO_CODEC 				0x0400
#define ICF_SET_LINE_VIDEO_CODEC 				0x0800
#define ICF_SET_LINE_CONTACT_USER_INFO	    	0x1000
/*This bitmask indicates that application wants the handling
  for ignoring/not ignoring the stale params in challenge.
  If this bitmask is set then IPTK checks in ignore_stale_param
  whether to ignore stale params or not*/
#define ICF_STALE_PARAM_HANDLING_PRESENT   	              0x2000

/*This bitmask indicates that application wants to define the
  handling for session refresh method. 
  If this bitmask is set then IPTK checks in session_refresh_method
  whether to use update or invite*/
#define ICF_LINE_CONFIG_SESSION_REFRESH_METHOD_PRESENT	  0x4000
/* End: Per Line Feature */
#define ICF_SET_LINE_PRM_ACCESS_NW_INFO    0x8000

/* This Bit Mastk will be set when sending t4 timer 
	 * duration */
#define ICF_SET_LINE_PRM_T4_TIMER		     	0x00010000
  /*This bitmask  will be set when application configures the
  remove_route_hdr field.*/
#define ICF_SET_LINE_REMOVE_ROUTE_HDR           0x00020000

/* This bitmask  will be set when application configures 
   session_refresh_method_strict_update field.*/
#define ICF_SET_LINE_SESSION_REFRESH_METHOD_STRICT_UPDATE  0x00040000

/* This bitmask will be set when application configures
   strip_req_uri_param field */
#define ICF_SET_LINE_STRIP_REQ_URI_PARAM   0x00080000   

	/* Optional Parameters */
	/* Number of seconds prior to expriation of 
 	* subscription */

	icf_duration_t			subscribe_head_start_timer;

	/* SIP T1 Timer duration value in milliseconds*/

	icf_duration_t			sip_timer_t1 ;

	/* SIP T2 Timer duration value in milliseconds*/

	icf_duration_t			sip_timer_t2 ;

	/* SIP B Timer duration value in milliseconds*/

	icf_duration_t			sip_timer_invite ;

	/* SIP F Timer duration value in milliseconds*/

	icf_duration_t			sip_timer_noninvite ;

    /*Start : Per Line Feature */
    /* The Differentiated Services Codepoint (DSCP) value that should populate the 
    DS field of SIP packets sent by the User Agent.*/
    icf_uint8_t             sip_dscp;
   
    /* The Differentiated Services Codepoint (DSCP) value that should populate the 
    DS field of RTP packets sent by the User Agent.*/
    icf_uint8_t             rtp_dscp;

    #ifdef ICF_SESSION_TIMER
    /* The minimum acceptable value, in seconds, 
    for the RFC session timer interval. */
    icf_duration_t          min_se;

    /* The maximum acceptable value, in seconds, 
    for the RFC session timer interval. */
    icf_duration_t          session_timer;

    /* A value of 'none,' 'uas,' or 'uac' specifying the refresher to be specified 
    by the UA when it has a choice. A value of 'none' specifies that the UA SHALL NOT 
    request session expiration; any other value specifies that the UA SHALL request 
    session expiration. The default value SHALL be 'uas'*/
    icf_refresher_type_t    session_timer_refresher; 
    #endif
    icf_list_st     *p_codec_attributes_audio;
    icf_list_st     *p_codec_attributes_video;
	icf_string_st	contact_user_info;
    
    /*This field indicates whether stale param in challenge 
      is to be ignored or not. If TRUE IPTK will ignore stale
      params, if FALSE it will not ignore.IPTK will check this feild
      only when ICF_IGNORE_STALE_PARAM_HANDLING_PRESENT bitmask is set*/
    icf_boolean_t   ignore_stale_param;

    /*This field indicates which type of session refresh method is
      required by application. IPTK will check this feild only when 
      ICF_LINE_CONFIG_SESSION_REFRESH_METHOD_PRESENT bitmask is set.
      Values are ICF_CFG_SESSION_REFRESH_METHOD_INVITE, 
      ICF_CFG_SESSION_REFRESH_METHOD_UPDATE */
    icf_uint8_t     session_refresh_method;

    /* End : Per Line Feature */
    /*This parameter is used to fill access nw info in outgoing messages*/
    icf_string_st   access_network_info;

   /* SIP T4 Timer duration value in milliseconds*/
	icf_duration_t	sip_timer_t4 ;

   /*This field indicates whether the route header from outgoing
     requests will be stripped or not.*/
   icf_boolean_t   remove_route_hdr;

   /* This field indicates whether application wants to send Update as 
    * session refresh even if allow header is not received from remote
    * this will be used only if ICF_CFG_SESSION_REFRESH_METHOD_UPDATE
    * is set i.e session refresh method as Update is specified by the application
    * either in set call params or in set line params.
    */
   icf_boolean_t   session_refresh_method_strict_update;   

   /* This parameter indicates whether transport param and port info( if 5060 )
    * received in 200 OK is to be send in Request URI of further outgoing request
    * if TRUE IPTK will not send transport and port info in Request URI, if FALSE 
    * IPTK will send PORT and transport info in Request URI.  
    */
   icf_boolean_t   strip_req_uri_param;       

} icf_set_line_param_req_st;


/*----------------------------------------------------------------------------
 * NAME : icf_logs_ind_st
 *
 * Description: This structure is used to specify payload data of
 *               API ICF_LOGS_IND
 *
 *---------------------------------------------------------------------------*/
typedef struct {
    icf_long_string_st  	trace_string;
}icf_logs_ind_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name:	icf_info_cfm_st
 *
 * Description: This API is used by the application to inform the framework.
 *                about the result of an the info request received  by 
 *                the application.
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* Mandatory Parameters */
    icf_result_t		result;
    icf_uint8_t			bit_mask;

#define ICF_INFO_CFM_ERROR_CAUSE_PRESENT          0x01
#define ICF_INFO_CFM_RESPONSE_CODE_PRESENT        0x02
#define ICF_INFO_CFM_HEADER_LIST_PRESENT          0x04
#define ICF_INFO_CFM_TAG_LIST_PRESENT             0x08
#define ICF_INFO_CFM_BODY_LIST_PRESENT            0x10

    /* Optionsl Parameters */
    icf_uint32_t 		response_code;  
    icf_error_t			error_cause;
    icf_header_list_st		header_list;
    icf_tag_list_st		tag_list;
    icf_msg_body_list_st	body_list;

} icf_info_cfm_st;

typedef struct
{ 
    icf_uint8_t         dscp_bits;

} icf_set_dscp_bits_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_early_call_ind_st
 *
 * Description:	  This API is sent by IMS Module to inform Application about
 *                an early call indication, so that Application can look whether
 *                it has to accept the call or reject the call.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{

    /* Modified bitmask from icf_uint8_t to icf_uint32_t to
       incorporate header list.
    */   
icf_uint32_t			bit_mask ;

#define ICF_EARLY_CALL_CLG_PTY_ADDR      0x01
#define ICF_EARLY_CALL_CLG_PTY_NAME		 0x02
#define ICF_EARLY_CALL_CALLED_PTY_ADDR	 0x04

    /* Denotes the address of the remote party calling the local user. */
    icf_address_st 				calling_party_addr;

    /* Denotes the name of the remote party calling the local user. */
    icf_name_st 				calling_party_name;

    /* Denotes the address of the local user. */
    icf_address_st 				called_party_addr;

    /* List of additional headers that are of importance to the application. */
    icf_header_list_st 			header_list;

} icf_early_incoming_call_ind_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_early_call_cfm_st
 *
 * Description:	  This is the response of the early call indication API sent
 *				   to the application earlier. The line id must be valid in case
 *					response is Success.
 *                
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* Bitmask for optional fields */
    icf_uint32_t bit_mask;
    
    /* This bit indicates presence of tunnel_mode field */
#define ICF_EARLY_CALL_CFM_TUNNEL_MODE_OPERATION_PRESENT 0x00000001
    /* This bit indicates presence of response code field */ 
#define ICF_EARLY_CALL_CFM_RESPONSE_CODE_PRESENT 0x00000002

#ifdef ICF_SESSION_TIMER    
    /* this bit indicates the presence of session timer enable flag */
#define  ICF_EARLY_CALL_CFM_SESSION_TIMER_ENABLE_PRESENT       0x00000004
#endif

	/* response for the early call indication*/
	icf_result_t			result;
	/*line id must be specified by the APP in case response is Success */
	icf_line_id_t			line_id;

    /* This field indicates that the application wants to enable 
        tunnel mode of operation.
    */
    icf_boolean_t tunnel_mode;
    /* This field contains the response code to be sent to the incoming
       INVITE received in case of API failure.
    */
    icf_uint16_t  response_code;

#ifdef ICF_SESSION_TIMER
    /* this field indicates whether to enable or disable the session timer
     * functionality in IPTK
     */ 
    icf_boolean_t                    session_timer_enable;
#endif
}icf_early_incoming_call_cfm_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_unexpected_msg_ind_st
 *
 * Description: This API is invoked by ICF towards the Application
 *              to convey to application that the message which was 
 *              sent to ICF by Application,was an invalid(unexpected) message.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
   /* Denotes the error cause */
   icf_error_t          error_cause;   
   
   /* Denotes the API identifier for which the indication is sent. */
   icf_api_id_t         api_id;
}icf_unexpected_msg_ind_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_stop_fax_resp_st
 *
 * Description: This API is send by IPTK  to notify the application for stop
 * 		fax response.
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* bitmask added for retyr after handling */
    icf_uint32_t                 bit_mask;

    /* result of the request */
    icf_result_t result;

    /* in case of failure, the error cause */
    icf_error_t error_cause;
    
    /* duration received in retry-after header*/
    icf_duration_t    retry_after_duration;

}icf_stop_fax_resp_st; 


/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_stop_fax_ind_st
 *
 * Description: This API is send by IPTK  to notify the application for stop
 * 		fax indication.
 *---------------------------------------------------------------------------*/
typedef struct
{
	/* This field will indicate which fax call is stopped
	 * by remote */
	icf_fax_start_type_t   fax_type;
}icf_stop_fax_ind_st; 


/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_media_connect_req_st
 *
 * Description: This API is invoked by Application towards the IMS Module
 *              in response to the ICF_INCOMING_CALL_IND API to send 183 with.
 *              SDP on network.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
		/* icf REL 6.0: multiple m lines */
#define ICF_MEDIA_CONNECT_DELETED_STREAM_PRESENT	0x00000001
#define ICF_MEDIA_CONNECT_MEDIA_MODE_PRESENT		0x00000002

/*  This bitmask denotes presence of optional field prack_value */
#define ICF_MEDIA_CONNECT_REQ_PRACK_VALUE_PRESENT     0x00000004

    icf_uint32_t bit_mask;
    /* Use common hash defines if privacy/header/msg-body/tag/stream 
     * list present in the API. 
     */

    /* Indicates whether privacy is required. */
    icf_boolean_t privacy_ind;

    /* List of additional headers that the application wants to send in the
     * message request
     */
    icf_header_list_st header_list;

    /* List of additional tags that the application wants to send in the 
     * message request.
     */
    icf_tag_list_st tag_list;

    /* List of message bodies that the application wants to send in the
     * message request.
     */
    icf_msg_body_list_st body_list;

    /* List of encoded_attributes for a media stream that application wishes 
     * to set in the outgoing response to the remote offer. Node is of type
     * icf_stream_capab_st */
    icf_list_st			*p_stream_list;

	/* icf REL 6.0: multiple m lines */
	/* the application may delete any stream during the call setup. This is 
	 * optional. The application will only return the rejected/deleted stream 
	 * information. The application will not be allowed to change/modify any
	 * codecs or any other parameter within the stream. The application if 
	 * desires can reject a stream only */
	/* the application should not indicate those stream_id's that have been
	 * already deleted in the onging session */
	icf_stream_id_t				count;
	icf_stream_list_st		deleted_media_streams[ICF_MAX_STREAM_PER_CALL];	
    icf_media_mode_t        media_mode;

    /* Indicates whether the SIP message needs to be sent with or without SDP.
     * To send 183 without SDP, set send_without_sdp = ICF_TRUE
     * Else To send 183 with SDP, set send_without_sdp = ICF_FALSE
	 * If set to true, ICF will not process the deleted streams and media mode
	 * parameters in this api.
	 */
    icf_boolean_t			send_without_sdp;

    /* This field indicates 183 shall be sent reliable on non reliable */
    /* This field indicates prack_support value 
       0 No prack neither in supported nor in require 
       2 100rel in require header
    */
    icf_prack_values_et prack_value;
} icf_media_connect_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_remote_call_transfer_initiated_cfm_st
 *
 * Description: This API is send to IPTK  for confirmation by the application 
 * 		        for remote call transfer.
 *---------------------------------------------------------------------------*/

typedef struct
{
#define ICF_CALL_TRANS_INIT_ERROR_CAUSE_PRESENT         0x40000000
#define ICF_CALL_TRANS_INIT_CFM_CODE_PRESENT            0x80000000


    icf_uint32_t bit_mask;

    /* Indicates the result of the call transfer req (success/failure).
success : 1 and failure : 0 */
    icf_result_t result;

    icf_error_t error_code ;

    /* Response code to be sent for the call transfer request. */
    /* This variable is for future use */
    icf_uint32_t response_code ;
   
    /* SPR 19218 : Merged CSR 1-5478785 */
    /* List of additional headers that the application wants to send in the API. */
    icf_header_list_st		header_list;

} icf_remote_call_transfer_initiated_cfm_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_get_register_status_req_st
 *
 * Description: This is payload of API ICF_GET_REGISTER_STATUS_REQ.
 *              This API can be sent by application to request for user REGISTER
 *              status.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{

        icf_line_id_t           line_id;

} icf_get_register_status_req_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_get_register_status_resp_st
 *
 * Description: This is payload of API ICF_GET_REGISTER_STATUS_RESP.
 *              This API is sent by IPTK to PA in response to API
 *              ICF_GET_REGISTER_STATUS_REQ.
 *
 *---------------------------------------------------------------------------*/


typedef struct
{

        /* This will be a list of icf_user_reg_status_st*/
        icf_list_st                     *p_user_reg_status;

        icf_transport_address_st        registrar_address;

        icf_duration_t                  expires_duration;

        icf_result_t                    result;

        icf_error_t                     error_cause;

}icf_get_register_status_resp_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_call_modify_cancel_resp_st
 *
 * Description: This is payload of API ICF_CALL_MODIFY_CANCEL_RESP.
 *              This API is sent by IPTK to Application to indicate that the 
 *              call modify cancellation was successful or not.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* result of the request */
    icf_result_t             result;

    /* in case of failure, the error cause */
    icf_error_t              error_cause;

}icf_call_modify_cancel_resp_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_progress_ind_st
 *
 * Description: This API is invoked by IMS Module towards Application when
 *		the SIP peer sends non-alerting provisional response 
 *		without sdp indicating that the call is in progress. It is 
 *		sent with the api id ICF_PROGRESS_IND.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
   	/* status code received in the progress message from peer */
    icf_uint16_t   					response_code;

} icf_progress_ind_st;

/***************************************************************************
*                   XCONF APIs
***************************************************************************/

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_create_xconf_req_st 
 *
 * Description: This is payload of API ICF_CREATE_XCONF_REQ.
 *              This API is sent by Application to IPTK to initiate external
 *              conference
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    icf_uint32_t             bitmask;
    /* The bitmask ordering is important as it has mapping 
       with create_call_req API */
#define ICF_CREATE_XCONF_CONF_URI_PRESENT            0x0001
#define ICF_CREATE_XCONF_TOGGLE_PRES_IND_PRESENT     0x0002    
#define ICF_CREATE_XCONF_PREF_MEDIA_PROFILE_PRESENT  0x0004
#define ICF_CREATE_XCONF_EXIST_CALL_ID_PRESENT       0x0008
#define ICF_CREATE_XCONF_CALLING_PARTY_ADDR_PRESENT  0x0010
#define ICF_CREATE_XCONF_CALLING_PARTY_NAME_PRESENT  0x0020
/* Bitmask for requesting QOS precondition support at conference call level */
#define ICF_CREATE_XCONF_PRECONDITION_REQD_PRESENT   0x0040

/* Bitmask for requesting preferred media transport type for XCONF call*/
#define ICF_CREATE_XCONF_MEDIA_TYPE_PRESENT          0x0080

/*Bitmask for requesting SRTP fallback option for XCONF call*/
#define ICF_CREATE_XCONF_SRTP_FALLBACK_REQD_PRESENT  0x0100



    /* the line_id on which the xconf needs to be established */
    icf_line_id_t            line_id;

    /*Address of conference server*/
    icf_address_st           conference_uri;

    /*The call id of the ingoing call for transferring it on to the Conference*/
    icf_call_id_t            existing_call_id;

    /* List of additional headers that the application wants to send in the
     * message request
     */
    icf_header_list_st       header_list;

    /* List of additional tags that the application wants to send in the
     * message request.
     */
     icf_tag_list_st         tag_list;

     /* this will be a list of icf_stream_capab_st */
     icf_list_st             *p_pref_media_profile;
    
     icf_address_st          calling_party_address;
    
     icf_string_st           calling_party_name;

     /* Indicates whether the local user wants to toggle the presentation
     * indication status for the current call.
     */
     icf_boolean_t           toggle_presentation_indicator;

    /* Indicates whether the local user wants to enable QOS precondition
     * feature, if this is set to 1 then QOS precondition is required for 
     * the external conference call  */
     icf_boolean_t           precondition_required;

     /*This parameter is used to configure SRTP support in IPTK*/
    icf_media_transport_mode_et  media_transport_type;

     /*This flag is used to tell IPTK whether application wants to
     *do fallback to RTP_AVP on SRTP rejected by remote*/
     icf_boolean_t         srtp_fallback_reqd;

    
} icf_create_ext_xconf_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_add_xconf_party_req_st 
 *
 * Description: This is payload of API ICF_ADD_XCONF_PARTY_REQ
 *              This API is sent by Application to IPTK to add a party to 
 *              existing XCONF conference
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
     icf_uint32_t             bitmask;

    /* List of additional headers that the application wants to send in the
     * message request
     */
     icf_header_list_st      header_list;

    /* List of additional tags that the application wants to send in the
     * message request.
     */
     icf_tag_list_st         tag_list;

     /* call id of call between host party and new party to be added to conference */
     icf_call_id_t          add_party_id;

}icf_add_xconf_party_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_delete_xconf_party_req_st
 *
 * Description: This is payload of API ICF_DELETE_XCONF_PARTY_REQ
 *              This API is sent by Application to IPTK to delete a party from 
 *              existing XCONF conference
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
     icf_uint32_t             bitmask;

    /* List of additional headers that the application wants to send in the
     * message request
     */
     icf_header_list_st      header_list;

    /* List of additional tags that the application wants to send in the
     * message request.
     */
     icf_tag_list_st tag_list;

     /* URI of party to be deleted from the conference */
     icf_address_st          del_party_uri;

}icf_delete_xconf_party_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_release_xconf_req_st
 *
 * Description: This is payload of API ICF_RELEASE_XCONF_REQ
 *              This API is sent by Application to IPTK to release / delete
 *              existing XCONF conference
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
     icf_uint32_t             bitmask;

    /* List of additional headers that the application wants to send in the
     * message request
     */
     icf_header_list_st      header_list;

    /* List of additional tags that the application wants to send in the
     * message request.
     */
     icf_tag_list_st tag_list;

}icf_release_xconf_req_st;

/*-----------------------------------------------------------------------------
*
* NAME : icf_release_xconf_resp_st
*
* DESCRIPTION  : This data type is used to define a structure,
*               which specifies payload data of API
*               ICF_RELEASE_XCONF_RESP.
-----------------------------------------------------------------------------*/
typedef struct
{
    /* Denotes the Failure status only. */
    icf_boolean_t result;

    /* Denotes the error cause if the status of the API is Failure. */
    icf_error_t   error_code;
}icf_release_xconf_resp_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_create_xconf_resp_st
 *
 * Description: This is payload of API ICF_CREATE_EXT_XCONF_RESP
 *              This API is sent by IPTK to Application to indicate that the 
 *              conference is initiated successfully or not
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
     icf_uint8_t             bitmask;

     icf_result_t            result;

     /* Denotes the error cause if the status of the API is Failure. */
     icf_error_t             error_cause;

}icf_create_ext_xconf_resp_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_add_xconf_party_resp_st
 *
 * Description: This is payload of API ICF_ADD_XCONF_PARTY_RESP
 *              This API is sent by IPTK to Application to indicate that the
 *              party is added successfully
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
     icf_result_t         result;

     /* Denotes the error cause if the status of the API is Failure. */
     icf_error_t          error_cause;

}icf_add_xconf_party_resp_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_delete_xconf_party_resp_st
 *
 * Description: This is payload of API ICF_DELETE_XCONF_PARTY_RESP
 *              This API is sent by IPTK to Application to indicate that the
 *              party is deleted successfully
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
     icf_result_t         result;

     /* Denotes the error cause if the status of the API is Failure. */
     icf_error_t          error_code;

     /* URI of party to be deleted from the conference */
     icf_address_st       deleted_party_uri;
}icf_delete_xconf_party_resp_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_xconf_release_ind_st
 *
 * Description: This is payload of API ICF_RELEASE_XCONF_IND
 *              This API is sent by IPTK to Application to indicate that the
 *              external conference is released
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    icf_call_clear_reason_t call_clear_reason;
}icf_xconf_release_ind_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_aka_auth_resp_st
 *
 * Description: This API is used by the application to send the authentication 
 *              response to ICF.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
    

    icf_uint32_t		bit_mask;
    
    #define ICF_AKA_AUTH_RESP_ERROR_PRESENT		0x01
    #define ICF_AKA_AUTH_RESPONSE_PRESENT		0x02
    #define ICF_AKA_AUTH_AUTS_PRESENT			0x04
    #define ICF_AKA_AUTH_IK_PRESENT			    0x08
    #define ICF_AKA_AUTH_CK_PRESENT				0x10
    #define ICF_AKA_AUTH_SEQ_NUM_PRESENT		0x20
    #define ICF_AKA_AUTH_SECURITY_ASSOCIATION_REQD_PRESENT 0x40

    /*Denotes the SIP method name for which the authentication response is provided by phone application.*/
    icf_uint8_t		sip_method_name;
    
    /*Denotes the line id on which the user is present */
    icf_line_id_t		line_id;

    /*Denotes the user address for which the authentication challenge is received*/
    icf_address_st		user_address;

    /*Indicates the success or failure status of the processing*/
    icf_boolean_t		result;
    
    /*Denotes the error cause in case the result is failure*/
    icf_error_t		error_cause;

    /*Denotes the response string to be sent in authorization header*/
    icf_string_st		auth_response;

    /*Denotes the AUTS string in case of SQN failure*/
    icf_string_st		auts_token;
    
    /*denotes the integrity key*/
    icf_string_st		Ik;

    /*denotes the cipher key*/
    icf_string_st		Ck;

    /*denotes the sequence no */
    icf_uint32_t		sequence_num;

   /*indicates whether IPTK should negotiate security
    *association parameters.
    */
    icf_boolean_t       security_association_reqd;

} icf_aka_auth_resp_st;

#ifdef ICF_UT_TEST

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_ut_simulate_st
 *
 * Description: This structure is to give the total number of functions
 *              to be failed and function related info for API ICF_UT_SIMULATE 
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
	icf_uint16_t			func_num; /*num of funcs to be failed*/
	icf_func_fail_st		func_fail[ICF_MAX_NUM_FUNC_FAIL];
}icf_ut_simulate_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_uatk_api_test_st
 *
 * Description: This structure is used by application(ims) to populate the
 *              various parameters which are used by IPTK while testing any
 *              micro SIP STACK API.Currently only three parameter are defined
 *              one of type string and two of type integer.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    icf_uint32_t            dVar1;
    icf_uint32_t            dVar2;
    icf_string_st           string1;
}icf_uatk_api_test_st;

#endif


#ifdef ICF_DNS_LOOKUP_ENABLED
/*-----------------------------------------------------------------------------
 *
 * Structure Name:	icf_dns_mapping_change_ind_st
 *
 * Description: 	This API is send by IPTK to Application whenever the stored 
 *			DNS mapping for proxy, registrar or reg-route address changes 
 *			due to new DNS query or entry deletion on purge or txn timeout.
 *---------------------------------------------------------------------------*/
typedef struct
{
	/* Indicates the peer for which entry is stored. This is a bitmask and
	 * multiple bits can be set if same address is configured as proxy and 
     * registrar etc.
	 */
#define ICF_DNS_RECORD_TYPE_INVALID			0x00
#define ICF_DNS_RECORD_TYPE_PROXY			0x01
#define ICF_DNS_RECORD_TYPE_REGISTRAR		0x02
#define ICF_DNS_RECORD_TYPE_REG_ROUTE		0x04
	icf_uint8_t					record_type;

	/* Indicates the domain name for which mapping is stored */
	icf_string_st				fqdn;

	/* Indicates the IP address corresponding to the domain name. This will be
	 * set to 0.0.0.0 when the DNS entry is deleted.
	 */
	icf_string_st 				ip;

	/* Indicates the reason for FQDN-IP mapping creation or deletion */

/* Initializer set to NULL */
#define ICF_DNS_MAP_CHANGE_INVALID								0

/* New mapping created after a new successful DNS query and SIP response 
 * received from peer */
#define ICF_DNS_MAP_CHANGE_QUERY_INVOCATION_SUCCESS				1

/* Mapping not created when failure response received from DNS server */
#define ICF_DNS_MAP_CHANGE_QUERY_INVOCATION_FAILURE				2

/* Mapping not created when no response received from DNS server */
#define ICF_DNS_MAP_CHANGE_QUERY_INVOCATION_TIMEOUT				3

/* Existing mapping deleted on system re-initialization. Processing for this
 * should be done in the porting function as indication for this cause is not
 * sent to APP. Only reinit response is sent to App.  */
#define ICF_DNS_MAP_CHANGE_SYSTEM_REINIT						4

/* Existing mapping deleted on SIP transaction timeout when no response received
 * from peer */
#define ICF_DNS_MAP_CHANGE_TXN_TIMEOUT							5

/* Existing mapping deleted on configured purge timer expiry */
#define ICF_DNS_MAP_CHANGE_PURGE_EXPIRY							6

/* Existing mapping deleted as TTL duration elapsed */
#define ICF_DNS_MAP_CHANGE_TTL_EXPIRY							7

/* Existing mapping deleted as fresh entry is created on getting SIP response 
 * for another request to the same FQDN */
#define ICF_DNS_MAP_CHANGE_ENTRY_REFRESH						8
	icf_uint8_t					cause;

} icf_dns_mapping_change_ind_st;
#endif /* ICF_DNS_LOOKUP_ENABLED */

/*-----------------------------------------------------------------------------
 *
 * Structure Name:	icf_tunnelled_options_resp_st
 *
 * Description: 	This API is send by IPTK to the application whenever 200 ok
 *                  response is received for an outgoing OPTIONS request sent.
 *---------------------------------------------------------------------------*/

typedef struct 
{
    /* Bitmask for optional parameters */
	icf_uint32_t			bit_mask;
    /* This indicates presence of optional field response_code_for_options */
#define  ICF_TUNNELLED_OPTIONS_RESP_CODE_PRESENT		0x01
    /* This indicates presence of optional field error_code_for_options */
#define  ICF_TUNNELLED_OPTIONS_ERROR_CODE_PRESENT		0x02
    /* This indicates presence of remote SDP in this API */
#define  ICF_TUNNELLED_OPTIONS_REMOTE_SDP_PRESENT	    0x04
	icf_result_t			result;
    /* This indicates the cause of failure for the OPTIONS request, if a failure
       occurs within IPTK.
    */   
	icf_error_t			error_code_for_options;
    /* The response code of the OPTIONS request as received from the network. */
    icf_uint32_t			response_code_for_options;
	icf_header_list_st		header_list;
	icf_msg_body_list_st	body_list;
    /* This contains the media capabilities of the peer as received in
       response to OPTIONS request.
    */  
	icf_tunnelled_sdp_info_st	tunnelled_remote_sdp;
} icf_tunnelled_options_resp_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name:	icf_early_session_ind_st
 *
 * Description: 	This API is sent by IPTK to the application when out of 
 *                  dialog OPTIONS is received from the network.
 *---------------------------------------------------------------------------*/

typedef struct 
{
    /* Bitmask for optional parameters */
	icf_uint32_t 			bit_mask;
    /* This indicates presence of optional field calling_party_addr */
#define ICF_EARLY_SESSION_CLG_PTY_ADDR      0x01
    /* This indicates presence of optional field called_party_addr */
#define ICF_EARLY_SESSION_CALLED_PTY_ADDR	 0x02

    icf_header_list_st 		header_list;
    /*  Indicates the line-id for the incoming OPTIONS request. */
    icf_line_id_t			line_id;
    /* Indicates the address of remote party calling the local user. */
    icf_address_st 				calling_party_addr;
    /* Indicates the address of the local user. */
    icf_address_st 				called_party_addr;
} icf_early_session_ind_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:	icf_early_session_cfm_st
 *
 * Description: 	This API is send by the application to IPTK in response
 *                  to API ICF_EARLY_SESSION_IND.
 *
 --------------------------------------------------------------------------*/

typedef struct 
{
    /* Bitmask for optional parameters */
	icf_uint32_t 			bit_mask;
    /* This indicates presence of optional field tunnel_mode */
#define  ICF_EARLY_SESSION_CFM_TUNNEL_MODE_PRESENT 0x01
    /* This indicates presence of optional field response_code */
#define  ICF_EARLY_SESSION_CFM_RESPONSE_CODE_PRESENT 0x02
    /* This indicates presence of optional field line_id */
#define  ICF_EARLY_SESSION_CFM_LINE_ID_PRESENT 0x04

    icf_result_t			result;
    /* This field is not used in the current release. */
	icf_line_id_t			line_id;
    /* This field indicates that the application wants to enable
       tunnel mode of operation.
    */
    icf_boolean_t tunnel_mode;
    /* This indicates the response code to be sent to the peer for
       an incoming OPTIONS request in case of API failure.
    */   
    icf_uint16_t  response_code;
}icf_early_session_cfm_st;

#ifdef ICF_SESSION_TIMER
/*-----------------------------------------------------------------------------
 *
 * Structure Name:	icf_session_timer_toggle_req_st
 *
 * Description: 	This API is send by the application to IPTK to toggle the 
 *                  session timer functionality.
 *
 --------------------------------------------------------------------------*/
typedef struct 
{
    icf_uint32_t                    bit_mask;
#define ICF_SESS_TOGG_REQ_TIMER_PRESENT         0x00000001
#define ICF_SESS_TOGG_REQ_MINSE_PRESENT         0x00000002
#define ICF_SESS_TOGG_REQ_REFRESHER_PRESENT     0x00000004

    /* session timer duration, in case toggling to enable the functionality */
    icf_duration_t                 session_timer;

    /* the min-se value */
    icf_duration_t                 min_se;

    /* the refresher for the session as per the negotiated value */
    icf_refresher_type_t           session_refresher;

} icf_session_timer_toggle_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:	icf_session_timer_toggle_resp_st
 *
 * Description: 	This API is send by the IPTK to application in resposne to  
 *                  the API ICF_SESSION_TIMER_TOGGLE_REQ.
 *
 --------------------------------------------------------------------------*/
typedef struct 
{
    icf_uint32_t                    bit_mask;
#define ICF_SESSION_TOGG_RESP_ERROR_PRESENT    0x00000001
    icf_result_t                    result;
    icf_error_t                     error_cause;
} icf_session_timer_toggle_resp_st;
#endif

/*-----------------------------------------------------------------------------
 *
 * Structure Name:	icf_prack_req_recv_ind_st
 *
 * Description: 	This API is send by the IPTK to application when PRACK   
 *                  received from peer.
 *
 --------------------------------------------------------------------------*/
typedef struct 
{
    icf_uint32_t              bit_mask;
    icf_uint32_t              settings;
#define ICF_PRACK_REQ_RECV_SDP_PRESENT    		0x00000001

    icf_header_list_st		header_list;
    icf_msg_body_list_st	body_list;
}icf_prack_req_recv_ind_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:	icf_prack_resp_sent_ind_st
 *
 * Description: 	This API is send by the IPTK to application when IPTK sends
 *                  Final response of received PRACK.
 *
 --------------------------------------------------------------------------*/
typedef struct 
{
    icf_uint32_t              bit_mask;
    icf_uint32_t              settings;
#define ICF_PRACK_RESP_SENT_SDP_PRESENT      0x00000001

    icf_uint32_t			response_code;
    icf_header_list_st		header_list;    
}icf_prack_resp_sent_ind_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:	icf_prack_req_sent_ind_st
 *
 * Description:         This API is send by the IPTK to application when IPTK sends
 *                      PRACK.
 *
 --------------------------------------------------------------------------*/
typedef struct 
{
    icf_uint32_t               bit_mask;
    icf_header_list_st	       header_list;    
}icf_prack_req_sent_ind_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:	icf_prack_resp_recv_ind_st
 *
 * Description: 	This API is send by the IPTK to application when IPTK receives
 *                  final response for outgoing PRACK
 *
 --------------------------------------------------------------------------*/
typedef struct 
{
    icf_uint32_t			bit_mask;
    icf_uint32_t              settings;
#define ICF_PRACK_RESP_RECV_SDP_PRESENT      0x00000001
    icf_uint32_t			response_code;
    icf_header_list_st		header_list;
    icf_msg_body_list_st	body_list;
}icf_prack_resp_recv_ind_st;



/*-----------------------------------------------------------------------------
 *
 * Structure Name:	icf_generic_msg_req_st
 *
 * Description: 	This API is send by the application to IPTK for sending
 *                  the in-call REQUEST  message over the network. This is 
 *                  currently supported for REFER/NOTIFY methods in tunnel
 *                  mode.
 *
 --------------------------------------------------------------------------*/
typedef struct 
{
    /*This fields shall be used for the presence of optional parameters
      present in the API. Currently used for header, tag and body list.*/
    icf_uint32_t          bit_mask;

    /*This field shall be used by application to indicate IPTK which 
      method request needs to be send to network. Currently REFER/NOTIFY
      shall be the valid methods.*/
    icf_string_st         method_name;

    /* List of additional headers that the application wants to send in the
     * message request
     */
    icf_header_list_st    header_list;

    /* List of additional message bodies that the application wants to send in the API. */
    icf_msg_body_list_st  body_list;

    /* List of additional tags that the application wants to send in the 
     * message request.
     */
    icf_tag_list_st       tag_list;
} icf_generic_msg_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:	icf_generic_msg_resp_st
 *
 * Description: 	This API is send by IPTK to application for sending
 *                  the response to ICF_GENERIC_MSG_REQ API. The success
 *                  response is issued when SIP response message corresponding
 *                  to SIP request message (sent using ICF_GENERIC_MSG_REQ
 *                  API) is received from network. This is currently supported
 *                  for in-call REFER/NOTIFY methods in tunnel mode. 
 --------------------------------------------------------------------------*/
typedef struct 
{
    icf_uint32_t     bit_mask; 

    /* Bitmasks for optional fields */
    #define   ICF_GENERIC_MSG_RESP_ERROR_CAUSE_PRESENT      0x01
    /* This bit is set whenever response_code field is filled */
    #define ICF_GENERIC_MSG_RESP_RESPONSE_CODE_PRESENT      0x02

    /* This is the method name that is received in the response from the network,
       */
    icf_string_st    method_name;
    
    /*This field denotes the network response code for the SIP message
     * received.*/
    icf_uint16_t      response_code;

    /* This field denotes whether the response is success or failure */
    icf_result_t     result; 

    /* Error code to be filled in case result is failure */
    icf_error_t      error_cause;
    
    /* This field is used to indicate application for the headers received
       in the SIP response message. */
    icf_header_list_st  header_list;

    /* This field is used to indicate application with the message bodies 
       received in the SIP response message. */
    icf_msg_body_list_st  body_list;
} icf_generic_msg_resp_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name:	icf_generic_msg_ind_st
 *
 * Description: 	This API is send IPTK to application on receiving   
 *                  the in-call REQUEST  message from the network. This is 
 *                  currently supported for REFER/NOTIFY methods in tunnel
 *                  mode.
 --------------------------------------------------------------------------*/
typedef struct 
{
    icf_uint32_t         bit_mask; 

    /* This is the method name that is received in the request from the network,
       */
    icf_string_st         method_name;
    
    /* This field is used to indicate application for the headers received
       in the SIP request message. */
    icf_header_list_st   header_list;
   
    /* This field is used to indicate application with the message bodies 
       received in the SIP request message. */
    icf_msg_body_list_st body_list;
} icf_generic_msg_ind_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:	icf_generic_msg_cfm_st
 *
 * Description: 	This API is send by application to IPTK on receiving   
 *                  the ICF_GENERIC_MSG_IND API and is used to send response 
 *                  message over network corresponding to the REQUEST message
 *                  received in ICF_GENERIC_MSG_IND API. This is currently
 *                  for REFER/NOTIFY methods in tunnel mode.
 --------------------------------------------------------------------------*/

typedef struct 
{
    icf_uint32_t               bit_mask;

    /* This is the method name for which the application wants to send
       the response. */
    icf_string_st              method_name;

    /*This is the network response code for the SIP response message */
    icf_uint16_t                response_code;

    /* List of additional headers that the application wants to send in the
     * SIP response message. */ 
    icf_header_list_st         header_list;

    /* List of additional message bodies that the application wants to send in the API. */
    icf_msg_body_list_st       body_list;
    
    /* List of additional tags that the application wants to send in the 
     * SIP response message.*/
    icf_tag_list_st            tag_list;
}icf_generic_msg_cfm_st;

/* New Structure for ASYNCHRONUS_MESSAGE enhancements*/
/*-----------------------------------------------------------------------------
 *
 * Structure Name:	icf_app_confirmation_st
 *
 * Description: 	This API is send by application to IPTK on receiving   
 *                  the messsage indication and is used to send response 
 *                  message over network corresponding to the REQUEST message
 *                  received .This is currently used for 
 *                  for incoming MESSAGE request method..
 --------------------------------------------------------------------------*/

typedef struct 
{
    icf_uint32_t               bit_mask;

    /* This bit is set whenever response_code field is filled */
    #define ICF_APP_CONFIRMATION_RESP_CODE_PRESENT 0x00000001
    /*This field denotes the network response code for the SIP message
     * received.*/
    icf_uint16_t      response_code;

    /* This field denotes whether the response is success or failure */
    icf_result_t     result; 


    /* List of additional headers that the application wants to send in the
     * SIP response message. */ 
    icf_header_list_st         header_list;

    /* List of additional tags that the application wants to send in the 
     * SIP response message.*/
    icf_tag_list_st            tag_list;
}icf_app_confirmation_st;

typedef icf_app_confirmation_st icf_message_cfm_st;

#ifdef __cplusplus

}

#endif /* __cplusplus */





#endif /* __ICF_API_H__ */


