/******************************************************************************
*									
* FILE NAME    :icf_trace_error_types.h				
*									
* DESCRIPTION  : System management interface data structures other than message 
*                definiton.
*									
* Revision History :							
*    DATE            NAME             REFERENCE       REASON
* --------      ------------          ----------   ---------------
*  09-Aug-2005  Rohit Aggarwal						Initial
*  10-Mar-2006  Amit Sharma                         ICF merging with ICF2.0
*  25-Jan-2008  Abhishek Dhammawat     Rel8.0       precondition trace
*                                                   addition
*  04-Jun-2008  Tarun Gupta            SPR 18585    New fields added in API
*                                                   structure icf_set_trace_req_st
*                                                   to support on/off the 
*                                                   debug traces at run time
*  02-Jun-2009  Preksha Gupta          Rel8.2       Asynchronus Message enhancement
*   									
* Copyright 2008,Aricent.   				
*									
******************************************************************************/

#ifndef __ICF_TRACE_ERROR_TYPES_H__
#define __ICF_TRACE_ERROR_TYPES_H__

#include "icf_types.h"


/* Determine if a C++ compiler is being used.
 * If so, ensure that standard
 * C is used to process the API information.
 */

#ifdef __cplusplus

/* Yes, C++ compiler is present.
 * Use standard C.
 */

extern "C"
{
#endif /* __cplusplus */

    
#ifdef ICF_TRACE_ENABLE

/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_trace_level_t
 *
 * Description: This is used to define the level for the trace set using the 
 *               API ICF_SET_TRACE_LEVEL.
 *  
 *---------------------------------------------------------------------------*/

typedef icf_uint8_t icf_trace_level_t;


/*-----------------------------------------------------------------------------
 *
 *   values for trace_level field in icf_set_trace_level_req_st
 *
 *---------------------------------------------------------------------------*/

#define ICF_TRACE_LEVEL_UNDEFINED     0
#define ICF_TRACE_LEVEL_BRIEF         1
#define ICF_TRACE_LEVEL_DETAILED      2


/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_trace_type_t
 *
 * Description: This is used to define the type of trace to be reported which 
 *              is set using the API ICF_SET_TRACE_REQ
 *  
 *---------------------------------------------------------------------------*/

typedef icf_uint32_t icf_trace_type_t; 


/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_trace_id_t
 *
 * Description: This is used to define the identifier for the trace reported 
 *              in the API ICF_REPORT_TRACE
 * 
 *---------------------------------------------------------------------------*/

typedef icf_uint32_t icf_trace_id_t;


/*-----------------------------------------------------------------------------
 *
 * typedef Name: icf_trace_criteria_t
 *
 * Description: This is used to define the filtering criteria of trace to be reported which
 *              is set using the API ICF_SET_TRACE_REQ
 *
 *---------------------------------------------------------------------------*/

typedef icf_uint32_t icf_trace_criteria_t;

/*-----------------------------------------------------------------------------
 *
 * typedef Name: icf_trace_rule_t
 *
 * Description: This is used to define the rule on which trace are to be filtered
 *              is set using the API ICF_SET_TRACE_REQ, default is AND
 *
 *---------------------------------------------------------------------------*/

typedef icf_uint8_t icf_trace_rule_t;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_trace_var_data_st
 *
 * Description: This data type is used to define a structure, which contains
 *              var trace data reported in the API ICF_REPORT_TRACE.
 *---------------------------------------------------------------------------*/

typedef struct
{
   /* can be type casted to any pointer to a data structure */
   icf_void_t *p_var_data;
}icf_trace_var_data_st;

/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_trace_data_st
 *
 * Description: This data type is used to define a structure, which contains 
 *              trace data reported in the API ICF_REPORT_TRACE. 
 *---------------------------------------------------------------------------*/

typedef struct
{
    /* timestamp*/
    icf_time_stamp_st   trace_timestamp;

    /* number of valid integer values present in the trace data */
    icf_uint8_t      num_of_integer_values; 
    
    /* array of integer values, which will  contain trace data */
    icf_uint32_t      int_val[ICF_MAX_INT_TRACE_DATA];    

    /* number of valid string values present in the trace data */
    icf_uint8_t      number_of_string_values;  
   
    /* array of string values that will contain trace data */  
    icf_string_st    string_val[ICF_MAX_STR_TRACE_DATA]; 

    /* trace string in english describing the trace_id */
    icf_string_st    trc_string; 

    /* variable trace data */
    icf_void_t      *p_var_data;
    
} icf_trace_data_st;




/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_set_trace_level_req_st
 *
 * Description: This is payload of API ICF_SET_TRACE_LEVEL_REQ.
 *              This API is sent by system administration module to enable or  
 *              disable the reporting of traces of a specific level or type,
 *              during system runtime.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{   
    
    /* enable or disable trace */
    icf_status_t          status;   
    
    /* level of the traces to be reported */
    icf_trace_level_t     trace_level;  

    /* type of traces to be reported like media, call_control etc */ 
    icf_trace_type_t      trace_type;   

} icf_set_trace_level_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_set_trace_req_st
 *
 * Description: This is payload of API ICF_SET_TRACE_REQ.
 *              This API is sent by system administration module to enable or
 *              disable the reporting of traces of specific type,
 *              during system runtime.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
    /* bitmask for optional variables */
    icf_uint8_t bitmask;
#define ICF_TRACE_TYPE_PRESENT          0x01
#define ICF_TRACE_CRITERIA_PRESENT      0x02
#define ICF_TRACE_RULE_PRESENT          0x04
#define ICF_TRACE_DEBUG_TRACE_STATUS_PRESENT  0x08
#define ICF_TRACE_DEBUG_TRACE_DEST		0x10

    /* enable or disable trace */
    icf_status_t          status;

    /* type of traces to be reported like media, call_control etc */
    icf_trace_type_t      trace_type;

    /* filtering crteria of the traces to be reported */
    icf_trace_criteria_t     trace_criteria;

    /* rule to be applied on filtering criteria */
    icf_trace_rule_t      trace_rule;
    
     /* enable or disable printing of debug traces */
    icf_status_t          debug_trace_status;

    /*dest of traces/errors to be write 2014-11-20 Steve*/
    icf_uint8_t				dest; //0:console 1:file

} icf_set_trace_req_st;


/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_report_trace_ind_st
 *
 * Description: This is payload of API ICF_REPORT_TRACE_IND. 
 *              This API is sent by call control to report a trace of given
 *              level and type. The API can report upto 4 integer and 2 string  
 *              values.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{

    /* trace identifier. The user needs to map trace id to the trace string. */
    icf_trace_id_t        trace_id;   

    /* type of traces  like media, call_control etc */
    icf_trace_type_t      trace_type;

    /* trace data to be reported in trace */
    icf_trace_data_st     trace_data;  
    
} icf_report_trace_ind_st;


/*------------------------------------------------------------------------
 * NAME:                icf_trace_criteria_data_st
 *
 * Description:         This structure is used to specify data for trace criteria which
 *                      can be used for filtering criteria based on which the
 *                      trace will be invoked.
 *
-------------------------------------------------------------------------*/
typedef struct
{
    /* which of the criteria data present */
    icf_uint32_t                bitmask;
#define ICF_TRACE_CALLING_PARTY_ADDR_PRESENT    0x00000001
#define ICF_TRACE_CALLED_PARTY_ADDR_PRESENT    0x00000002
#define ICF_TRACE_OFFERED_CODEC_PRESENT         0x00000004
#define ICF_TRACE_NEGOTIATED_CODEC_PRESENT      0x00000008
#define ICF_TRACE_LINE_ID_PRESENT               0x00000010
#define ICF_TRACE_CALL_DIR_PRESENT              0x00000020
#define ICF_TRACE_LOCAL_RTP_IP_PRESENT          0x00000040
#define ICF_TRACE_LOCAL_RTP_PORT_PRESENT        0x00000080
#define ICF_TRACE_REMOTE_RTP_IP_PRESENT         0x00000100
#define ICF_TRACE_REMOTE_RTP_PORT_PRESENT       0x00000200
#define ICF_TRACE_LOCAL_SIP_IP_PRESENT          0x00000400
#define ICF_TRACE_LOCAL_SIP_PORT_PRESENT        0x00000800
#define ICF_TRACE_CALL_TYPE_PRESENT             0x00001000
#define ICF_TRACE_IS_SERVICE_CALL_PRESENT       0x00002000
#define ICF_TRACE_TRANSPORT_MODE_PRESENT        0x00004000

    icf_address_st              *p_calling_party_address;
    icf_address_st              *p_called_party_address;

    icf_line_id_t               line_id;
    icf_uint8_t                 call_direction;

        /* following is the linked list of type icf_stream_data_st which
    * has information on per stream basis */
    icf_list_st                 *p_stream_data;

    icf_transport_address_st    *p_local_sip_ip_address;

    icf_uint8_t                  call_transport_mode;

#define ICF_TRACE_CONNECTED_CALL        0x01
#define ICF_TRACE_ALERTED_CALL          0x02
    icf_uint8_t                 call_type;

    icf_boolean_t               is_service_call;
    /* this will be true when its QOS precondition call */
    icf_boolean_t               qos_call;

} icf_trace_criteria_data_st;


/*-----------------------------------------------------------------------------
 *
 *   values for icf_trace_type_t : type of traces to be reported.
 *
 *---------------------------------------------------------------------------*/

#define ICF_TRACE_TYPE_UNDEFINED                 0x0000
#define ICF_TRACE_TYPE_INTERFACE                 0x0002
#define ICF_TRACE_TYPE_SIP                       0x0004
#define ICF_TRACE_TYPE_MEDIA                     0x0010
#define ICF_TRACE_TYPE_CONFIG                    0x0020
#define ICF_TRACE_TYPE_SM                        0x0080
#define ICF_TRACE_TYPE_CALL_HOLD_RESUME          0x0100
#define ICF_TRACE_TYPE_THREE_WAY_CALL            0x0200
#define ICF_TRACE_TYPE_CALL_TRANSFER_UNATTENDED  0x0400
#define ICF_TRACE_TYPE_CALL_TRANSFER_ATTENDED    0x0800
#define ICF_TRACE_TYPE_REFER                     0x1000
#define ICF_TRACE_TYPE_CALL_FORWARDING           0x2000
#define ICF_TRACE_TYPE_CALL_WAITING              0x4000
#define ICF_TRACE_TYPE_MWI                       0x08000
#define ICF_TRACE_TYPE_SUBM                      0x10000
#define ICF_TRACE_TYPE_SSA                       0x20000
#define ICF_TRACE_TYPE_GENERAL                   0x40000
#define ICF_TRACE_TYPE_SIP_STACK                 0x80000
#define ICF_TRACE_TYPE_SIP_STACK_DEBUG           0x00100000


/*-----------------------------------------------------------------------------
 *
 *   values for icf_trace_type_t : new type of traces to be reported to application.
 *
 *---------------------------------------------------------------------------*/

#define ICF_TRACE_TYPE_SYSTEM                    0x0001
#define ICF_TRACE_TYPE_SIP_INTERFACE             0x00200000
#define ICF_TRACE_TYPE_APP_INTERFACE             0x00400000
#define ICF_TRACE_TYPE_MEDIA_INTERFACE           0x00800000
#define ICF_TRACE_TYPE_CALL_CONTROL              0x0008
#define ICF_TRACE_TYPE_MESSAGE_CONTROL           0x0004
#define ICF_TRACE_TYPE_CONFIGURATION             0x01000000
#define ICF_TRACE_TYPE_SUBSCRIPTION              0x02000000
#define ICF_TRACE_TYPE_REGISTRATION              0x0040
#define ICF_TRACE_TYPE_ERROR                     0x04000000


/*-----------------------------------------------------------------------------
 *
 *   values for icf_trace_rule_t : new rules for filtering of traces to be reported.
 *
 *---------------------------------------------------------------------------*/

#define ICF_TRACE_RULE_AND             0x0001
#define ICF_TRACE_RULE_OR              0x0002


/*-----------------------------------------------------------------------------
 *
 *   values for icf_trace_criteria_t : new rules for filtering of traces to be reported.
 *
 *---------------------------------------------------------------------------*/
#define ICF_TRACE_CRITERIA_UNDEFINED                    0x000000
#define ICF_TRACE_CRITERIA_CALLING_PARTY_ADDRESS        0x000001
#define ICF_TRACE_CRITERIA_CALLED_PARTY_ADDRESS         0x000002
#define ICF_TRACE_CRITERIA_LINE_ID                      0x000004
#define ICF_TRACE_CRITERIA_INCOMING_CALL                0x000008
#define ICF_TRACE_CRITERIA_OUTGOING_CALL                0x000010
#define ICF_TRACE_CRITERIA_NEGOTIATED_CODEC             0x000020
#define ICF_TRACE_CRITERIA_OFFERED_CODEC                0x000040
#define ICF_TRACE_CRITERIA_LOCAL_RTP_IP_ADDRESS         0x000080
#define ICF_TRACE_CRITERIA_LOCAL_RTP_PORT               0x000100
#define ICF_TRACE_CRITERIA_REMOTE_RTP_IP_ADDRESS        0x000200
#define ICF_TRACE_CRITERIA_REMOTE_RTP_PORT              0x000400
#define ICF_TRACE_CRITERIA_LOCAL_SIP_IP_ADDRESS         0x000800
#define ICF_TRACE_CRITERIA_LOCAL_SIP_PORT               0x001000
#define ICF_TRACE_CRITERIA_CONNECTED_CALL               0x002000
#define ICF_TRACE_CRITERIA_ALERTED_CALL                 0x004000
#define ICF_TRACE_CRITERIA_CALL_ON_UDP                  0x008000
#define ICF_TRACE_CRITERIA_CALL_ON_TCP                  0x010000
#define ICF_TRACE_CRITERIA_CALL_ON_TLS                  0x020000
#define ICF_TRACE_CRITERIA_SERVICE_CALL                 0x040000
/*  CSR 1-5385208 Merge */
#define ICF_TRACE_CRITERIA_MATCH_COMPLETE_ADDRESS       0x080000


#endif /* #ifdef ICF_TRACE_ENABLE */


#ifdef ICF_ERROR_ENABLE

/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_error_level_t
 *
 * Description: This is used to define the level for the  error set using the 
 *              API ICF_SET_ERROR_REPORT_LEVEL
 *  
 *---------------------------------------------------------------------------*/

typedef icf_uint8_t icf_error_level_t;


/*-----------------------------------------------------------------------------
 *
 *   values for icf_error_level_t : level of the errors to be reported.
 *
 *---------------------------------------------------------------------------*/

#define ICF_ERROR_LEVEL_UNDEFINED     0
#define ICF_ERROR_LEVEL_CRITICAL      1
#define ICF_ERROR_LEVEL_MAJOR         2
#define ICF_ERROR_LEVEL_INFO          3


/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_error_type_t
 *
 * Description: This is used to define the type of error to be reported which is
 *              set using the API ICF_SET_ERROR_REPORT_LEVEL
 *  
 *---------------------------------------------------------------------------*/

typedef icf_uint32_t icf_error_type_t; 


/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_error_id_t
 *
 * Description: This is used to define the identifier for the error reported in
 *              the API ICF_REPORT_ERROR.
 *  
 *---------------------------------------------------------------------------*/

typedef icf_uint32_t icf_error_id_t; 

/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_error_data_st
 *
 * Description: This data type is used to define a structure, which contains 
 *              error data reported in the API ICF_REPORT_ERROR
 * 
 *---------------------------------------------------------------------------*/

typedef struct
{
    
    /* number of valid integer values present in the error data */    
    icf_uint8_t      num_of_integer_values;     
    
    /* array of integer values, which will contain error data */
    icf_int32_t      int_val[ICF_MAX_INT_ERROR_DATA];
    
    /* number of valid string values present in the error data */
    icf_uint8_t      number_of_string_values;   
    
    /* array of string values that will contain error data */
    icf_string_st    string_val[ICF_MAX_STR_ERROR_DATA];   
    
    /* error string in english describing the error_id */
    icf_string_st    err_string; 
    
} icf_error_data_st;


/*-----------------------------------------------------------------------------
 *
 *   values for icf_error_type_t: Type of errors to be reported.
 *   These can be system, interface, SIP, media, call control etc.
 *
 *---------------------------------------------------------------------------*/

#define ICF_ERROR_TYPE_UNDEFINED                 0x0000
#define ICF_ERROR_TYPE_SYSTEM                    0x0001
#define ICF_ERROR_TYPE_INTERFACE                 0x0002
#define ICF_ERROR_TYPE_SIP                       0x0004
#define ICF_ERROR_TYPE_CALL_CONTROL              0x0008
#define ICF_ERROR_TYPE_MEDIA                     0x0010
#define ICF_ERROR_TYPE_CONFIG                    0x0020
#define ICF_ERROR_TYPE_REGISTRATION              0x0040
#define ICF_ERROR_TYPE_SM                        0x0080
#define ICF_ERROR_TYPE_CALL_HOLD_RESUME          0x0100
#define ICF_ERROR_TYPE_THREE_WAY_CALL            0x0200
#define ICF_ERROR_TYPE_CALL_TRANSFER_UNATTENDED  0x0400
#define ICF_ERROR_TYPE_CALL_TRANSFER_ATTENDED    0x0800
#define ICF_ERROR_TYPE_REFER                     0x1000
#define ICF_ERROR_TYPE_CALL_FORWARDING           0x2000
#define ICF_ERROR_TYPE_CALL_WAITING              0x4000
#define ICF_ERROR_TYPE_MWI                       0x08000
#define ICF_ERROR_TYPE_SUBM                      0x10000
#define ICF_ERROR_TYPE_GENERAL                   0x20000
#define ICF_ERROR_TYPE_STACK_ERROR               0x40000

#endif /* #ifdef ICF_ERROR_ENABLE */

#define ICF_ERROR_TYPE_UNDEFINED                 0x0000

#if defined ICF_TRACE_ENABLE || ICF_ERROR_ENABLE

/*-----------------------------------------------------------------------------
 *
 *   values to be used in field number_of_integer_values of error_data and 
 *   trace_data.
 *
 *---------------------------------------------------------------------------*/

#define ICF_NO_INT_PRESENT           0
#define ICF_ONE_INT_PRESENT          1
#define ICF_TWO_INT_PRESENT          2
#define ICF_THREE_INT_PRESENT        3
#define ICF_FOUR_INT_PRESENT	     4


/*-----------------------------------------------------------------------------
 *
 *   values to be used in field number_of_string_values of error_data and 
 *   trace_data.
 *
 *---------------------------------------------------------------------------*/

#define ICF_NO_STRING_PRESENT        0
#define ICF_ONE_STRING_PRESENT       1
#define ICF_TWO_STRING_PRESENT       2
#define ICF_THREE_STRING_PRESENT     3
#define ICF_FOUR_STRING_PRESENT      4

#endif


#ifdef ICF_ERROR_ENABLE
/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_set_error_report_level_req_st
 *
 * Description: This is payload of API ICF_SET_ERROR_REPORT_LEVEL_REQ.
 *              This API is sent by system administration module to enable or 
 *              disable the reporting of errors of a specific level or type,
 *              during system runtime.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{

    /* Enable or disable error report */
    icf_status_t          status;           
    
    /* Level of the errors to be reported.These can be Critical,Major,Info */
    icf_error_level_t     error_level;     

    /* Type of errors to be reported.These can be System,Interface,SIP,Media or 
     * Call_Control */
    icf_error_type_t      error_type;  
    
} icf_set_error_report_level_req_st;

/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_report_error_ind_st
 *
 * Description: This is payload of API ICF_REPORT_ERROR_IND. 
 *              This API is sent by call control to report a error of given
 *              level and type. The API can report upto 4 integer and 2 string  
 *              values.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{

    /* trace identifier. The user needs to map trace id to the trace string. */
    icf_error_id_t        error_id;   

    /* trace data to be reported in trace */
    icf_error_data_st     error_data;  
    
}icf_report_error_ind_st;

#endif


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __ICF_TRACE_ERROR_TYPES_H__ */
