/*******************************************************************************
*                                        
* FILE NAME    : icf_types.h
*                                        
* DESCRIPTION  : Contains the global basic datatypes definitions to be used 
*               across the whole IMS Client Framework        
*                                        
* Revision History :    
*                            
*    DATE            NAME       REFERENCE       REASON
* --------    ------------      ---------      --------
* 8-JUL-2005   Ram Narayan        None         Initial
* 02-Feb-2006  Amit Sharma                     CFG merged with ICF 2.0
* 08-Feb-2006  Amit Sharma               Network PDU Logging API from ICF
*
* 27-Nov-2006  Deepti Goyal       ICF Rel 6.2   NAT Feature Support
* 6-Dec-2006   Deepti Goyal       ICF Rel 6.2   Review comments incorporated
* 15-Jan-2007  Abhishek Dhammawat ICF REL 6.3   Additions for Per Line Feature 
* 16-Jan-2008  Neha Gupta	  SPR 18033     Added support for func failure
*						simulation for UT.
* 16-Jan-2008  Amit Sharma       ICF 8.0 LLD   Enhancements for Rel8.0
* 24-Jan-2008  Abhishek Dhammawat ICF 8.0     Modified icf_call_connect_data_st 
* 06-MAR-2008  Vipul Varshney   SPR 18122       Add new state in RGM state machine
* 23-Apr-2008  Kamini Gangwani  SPR 18468       Unused flags removed from
*                                               icf_init_param_st structure
* 27-FEB-2009  Preksha          Rel 8.1         Added func_level field in icf_func_fail_st
* 02-Mar-2009 Kamal Ashraf      IPTK Rel 8.1    structure variables added in
*                                               icf_init_param_st structure for
*                                               open source replacement
* 30-Mar-2009 Anurag Khare     Rel 8.2          Enum icf_prack_values_et added
* 13-Jul-2009 Rajiv Kumar      Rel 8.2          Changes for Openssl Removal.
* 08-Oct-2009 Rajiv Kumar      SPR:20106        Fix for SPR:20106
* Copyright 2009, Aricent.                       
*                                        
*******************************************************************************/



#ifndef __ICF_TYPES_H__
#define __ICF_TYPES_H__


#include "icf_feature_flags.h"
#include "icf_defs.h"

/* Prevent Name Mangling By C++ Compilers */
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


/*
---------------------------- BASIC TYPES -------------------------------------
*/

/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_void_t
 * 
 * Description: Represent the type void.
 *
 *---------------------------------------------------------------------------*/
typedef void icf_void_t;

/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_void_t
 * 
 * Description: Represent the type void *.
 *
 *---------------------------------------------------------------------------*/
typedef void * icf_pvoid_t;


/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_uint8_t
 *
 * Description: This data type represents a 1 byte unsigned integer.
 *
 *---------------------------------------------------------------------------*/
typedef unsigned char icf_uint8_t;

/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_boolean_t
 * 
 * Description: Represent boolean vales
 *
 *---------------------------------------------------------------------------*/
typedef icf_uint8_t icf_boolean_t;


/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_return_t
 * 
 * Description: Represent the  execution status values return by a function.
 *              This type is used in function interface and not in message based
 *              interface.
 *
 *---------------------------------------------------------------------------*/
typedef icf_boolean_t icf_return_t;

/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_uint16_t
 * 
 * Description: This data type represents a 2 byte unsigned integer. 
 * 
 *---------------------------------------------------------------------------*/

typedef unsigned short icf_uint16_t;

/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_uint32_t
 *
 * Description: This data type represents a 4 byte unsigned long integer.
 *  
 *---------------------------------------------------------------------------*/
typedef unsigned int icf_uint32_t;



/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_int8_t
 * 
 * Description: This data type represents a 1 byte signed integer
 *
 *---------------------------------------------------------------------------*/
typedef char icf_int8_t;



/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_int16_t
 *
 * Description: This data type represents a 2 byte-signed integer.
 * 
 *---------------------------------------------------------------------------*/
typedef signed short icf_int16_t; 



/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_int32_t
 *
 * Description: This data type represents a 4 byte signed long integer
 *
 *---------------------------------------------------------------------------*/
typedef signed int icf_int32_t;

/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_uint64_t
 *
 * Description: This data type represents a 8 byte unsigned long integer
 *
 *---------------------------------------------------------------------------*/

typedef unsigned long int icf_uint64_t;

/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_string_st
 * 
 * Description: This data type represents a structure, which consists of a 
 *              character array of specified length
 *
 *---------------------------------------------------------------------------*/
typedef struct        
{
   /* specifies the length of the string including '\0' character */ 
    icf_uint16_t str_len;
    
    /* array of characters */ 
    icf_uint8_t str[ICF_MAX_STR_LEN];
} icf_string_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_large_string_st
 *
 * Description: This data type represents a structure, which consists of a
 *              character array of specified length
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
   /* specifies the length of the string including '\0' character */
    icf_uint16_t str_len;
   
    /* array of characters */
    icf_uint8_t str[ICF_MAX_LARGE_STR_LEN];
} icf_large_string_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_long_string_st
 *
 * Description: This data type represents a structure, which consists of a
 *              character array of specified length. This datatype will be used
 *              to store long strings.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{

    /* specifies the length of the string including '\0' character */
    icf_uint16_t str_len;

    /* array of characters */
    icf_uint8_t   str[ICF_MAX_LONG_STR_LEN];

} icf_long_string_st;

/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_req_uri_st
 * 
 * Description: This data type represents a structure, which consists of a 
 *              character array of specified length, used to hold a long URI 
 *				type. Introduced basically for MPH module.
 *---------------------------------------------------------------------------*/

typedef struct icf_req_uri_st
{
	/* specifies the length of the string including '\0' character */ 
    icf_uint16_t str_len;
    
    /* array of characters */ 
	icf_uint8_t	str[ICF_MAX_REQ_URI_LEN];

}icf_req_uri_st;


/*
------------------------- API RELATED INTERFACE TYPES -------------------------
*/

/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_version_t
 *
 * Description: Used to define the Version of the  APIs being used
 * 
 *---------------------------------------------------------------------------*/

typedef icf_uint8_t icf_version_t;            


/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_api_id_t
 *
 * Description: Used to define unique identifiers to represent APIs on various 
 *              interfaces
 * 
 *---------------------------------------------------------------------------*/
typedef icf_uint16_t icf_api_id_t;            

/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_app_id_t
 *
 * Description: Identifies the application invoking/receiving the API.
 *
 *---------------------------------------------------------------------------*/
typedef icf_uint32_t icf_app_id_t;            

/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_call_id_t
 *
 * Description: Used to define unique identifiers to represent call id
 * 
 *---------------------------------------------------------------------------*/
typedef icf_uint16_t icf_call_id_t;    


/*------------------------------------------------------------------------------
 * 
 * typedef Name: icf_line_id_t
 *
 * Description: Used to define unique identifiers to represent line id
 * 
 *----------------------------------------------------------------------------*/
typedef icf_uint16_t icf_line_id_t;        

/*------------------------------------------------------------------------------
 * 
 * typedef Name: icf_duration_t
 *
 * Description: Indicates the duration of timer in seconds.
 * 
 *----------------------------------------------------------------------------*/
typedef icf_uint32_t icf_duration_t;

/*------------------------------------------------------------------------------
 * 
 * typedef Name: icf_call_type_t
 *
 * Description: defines the call type for an incoming/outgoing call.
 * 
 *----------------------------------------------------------------------------*/
typedef icf_uint8_t icf_call_type_t;


/*------------------------------------------------------------------------------
 * 
 * typedef Name: icf_stream_id_t
 *
 * Description: defines the stream id within a call.
 * 
 *----------------------------------------------------------------------------*/
typedef icf_uint8_t icf_stream_id_t;


/*------------------------------------------------------------------------------
 * 
 * typedef Name: icf_error_t
 *
 * Description: Defines the error cause when the response of an API is failure.
 * 
 *----------------------------------------------------------------------------*/
typedef icf_uint16_t icf_error_t;            


/*------------------------------------------------------------------------------
 * 
 * typedef Name: icf_inband_info_status_t
 *
 * Description: Used as a flag to state who will play the ring back tone
 * 
 *----------------------------------------------------------------------------*/
typedef icf_boolean_t icf_inband_info_status_t;    


/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_module_id_t
 *
 * Description: Used to define unique identifiers to represent various modules
 * 
 *---------------------------------------------------------------------------*/
typedef icf_uint8_t icf_module_id_t;


/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_presentation_indicator_t
 *
 * Description: Used to state if the name of calling party will be displayed
 * 
 *---------------------------------------------------------------------------*/
typedef icf_boolean_t icf_presentation_indicator_t;


/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_result_t
 *
 * Description: Used to show the success or failure
 * 
 *---------------------------------------------------------------------------*/
typedef icf_boolean_t icf_result_t;


/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_service_type_t
 *
 * Description: Shows the type of service in case of call hold 
 * 
 *---------------------------------------------------------------------------*/
typedef icf_uint8_t icf_service_type_t;    


/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_status_t
 *
 * Description: Value indicates the enable/disable status of a flag.
 * 
 *---------------------------------------------------------------------------*/
typedef icf_boolean_t icf_status_t;




/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_transport_mode_t
 *
 * Description: 
 * 
 *---------------------------------------------------------------------------*/
typedef icf_uint8_t icf_transport_mode_t;


/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_address_type_t
 *
 * Description: This data type is used to define type of address format for the
 *              party address information present in the icf_address_st 
 *              structure
 * 
 *---------------------------------------------------------------------------*/
typedef icf_uint8_t icf_address_type_t;

/*-----------------------------------------------------------------------
 * NAME : icf_priority_id_t
 *-----------------------------------------------------------------------*/

typedef icf_uint8_t icf_priority_id_t;

/*-----------------------------------------------------------------------
 * NAME : icf_config_action_t
 *-----------------------------------------------------------------------*/
typedef icf_uint8_t icf_config_action_t;

#ifdef ICF_FAX_SUPPORT
/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_fax_pt_codec_t
 *
 * Description: This data type is used to define preferred codec 
 *              for fax pass through 
 * 
 *---------------------------------------------------------------------------*/
	/* FAX pass through PCMA*/
#define   ICF_PREF_CODEC_FAX_PT_PCMA		1
	/* FAX pass through PCMU*/
#define   ICF_PREF_CODEC_FAX_PT_PCMU		2	

typedef icf_uint8_t   icf_fax_pt_codec_t;

/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_fax_start_type_t
 *
 * Description: This data type is used to define various method supported by ICF 
 *              to send fax to remote party
 * 
 *---------------------------------------------------------------------------*/
#define ICF_NO_FAX_CALL							 0
    /* ICF will attempt fax call using fax passthrough
	 * method using G.711 Codec */
#define ICF_FAX_PT_CALL                          1
	/* ICF will attempt fax call using T.38 procedures */
#define ICF_T38_FAX_CALL                         2
	/* ICF shall attempt call on T.38 and in case call attempt using 
	 * T.38 method fails, ICF shall attempt call using fax passthrough method */ 
#define ICF_T38_FAX_CALL_FAILURE_SWITCH_PT_CALL  3       

typedef icf_uint8_t   icf_fax_start_type_t;
#endif


/*----------------------------------------------------------------------------
 *
 *  icf_transport_mode_et These values specifies the mode of
 *   transport as TCP or UDP or both. These enums will be used for the 
 *   transport mode to be set in the SDP/MM messages
 *
 *--------------------------------------------------------------------------*/
typedef enum
{
	ICF_TRANSPORT_MODE_UDP,
	ICF_TRANSPORT_MODE_TCP,
	ICF_TRANSPORT_MODE_RTP_AVP,
#ifdef ICF_FAX_SUPPORT
#ifdef NON_IMS_CLIENT
	ICF_TRANSPORT_MODE_UDPTL,
#endif
#endif
    ICF_TRANSPORT_MODE_RTP_SAVP

}icf_media_transport_mode_et;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_header_st
 *
 * Description: This datatype represents a structure that contains SIP headers.
 *              
 *---------------------------------------------------------------------------*/
typedef struct icf_header_st
{
    /* Specifies the SIP header name. */
    icf_string_st hdr_name;

    /* Contains header value. */
    icf_large_string_st hdr_value;

    /* Contains pointer to the next header in the list, if any. */
    struct icf_header_st *next ;
} icf_header_st;



/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_header_list_st
 *
 * Description: This datatype represents a structure that contains a list
 *                of SIP headers.
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* Specifies the number of SIP headers in the list. */
    icf_uint32_t count;

    /* Contains a pointer to the list of headers. */
    icf_header_st *hdr;
} icf_header_list_st;



/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_msg_body_st
 *
 * Description: This datatype represents a structure that contains message bodies.
 *---------------------------------------------------------------------------*/
typedef struct icf_msg_body_st
{
    /* Specifies the media type of the message-body sent to the recipient. */
    icf_string_st content_type;

    /*Message body header changes*/
    /* Contains the list of headers present per message body
     */
    icf_header_list_st     msg_body_hdr_list;


    /* Contains length of the message-body in the value field. */
    icf_uint32_t length ;
    
    /* Contains the pointer to the message-body buffer. */
    icf_uint8_t *value ;

    /* Contains pointer to the next message-body element in the list, if any. */
    struct icf_msg_body_st *next ;
} icf_msg_body_st;



/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_msg_body_list_st
 *
 * Description: This is a common structure used to return back the response of 
 *              _req APIs.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* Specifies the number of streams information present in the list. */
    icf_uint32_t count;

    /*Message body header changes*/
    /* Contains the content-type header to be set in the SIP message in case of
     * multiple message bodies.
     */
    icf_string_st  content_type;

   /* Contains the stream information. */
    icf_msg_body_st *body;
} icf_msg_body_list_st;

/* ICF rel 6.0 Multiple m-lines */
/*-----------------------------------------------------------------------------
 * typedef Name: icf_media_type_t
 * Description:  This data-type is used to define the media 
 * type defined within ICF and MM. Currently this will contain parameters 
 * for Audio, Video, TBCP (app) and T.38 (Fax). This data type will be enhanced to 
 * support many more media types in future.
 *----------------------------------------------------------------------------*/
#define  ICF_STREAM_TYPE_INVALID  0
#define  ICF_STREAM_TYPE_AUDIO    1
#define  ICF_STREAM_TYPE_VIDEO    2
#define  ICF_STREAM_TYPE_TBCP     3
#define  ICF_STREAM_TYPE_FAX      4

typedef icf_uint8_t   icf_media_type_t;




/* ICF_REL 6.0: multiple m lines
 * this structure is being modified to support multiple streams in the structure */
/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_stream_id_info_st
 *
 * Description: This datatype represents a structure that contains stream
 *              id and the stream type only. 
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* Specifies the stream id of the stream type */
    /* Presently use ICF_STREAM_ID */
    icf_stream_id_t			stream_id;

    /* Specifies the type of stream (audio/video/application/T.38). */
    icf_media_type_t		stream_type;

} icf_stream_id_info_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_tag_st
 *
 * Description: This datatype represents a structure that contains SIP
 *                specific tags or parameters.
 *
 *---------------------------------------------------------------------------*/

typedef struct icf_tag_st
{

/*Invalid Tag*/
#define ICF_TAG_TYPE_INVALID				0x00
/*Tag is a uri parameter*/
#define ICF_TAG_TYPE_SIP_URI_PARAM			0x01
/*Tag is a uri header parameter*/
#define ICF_TAG_TYPE_SIP_URI_HDR_PARAM    	0x02
/*Tag is a header parameter*/
#define ICF_TAG_TYPE_HDR_PARAM	    		0x04

	/*bitmask*/
	icf_uint8_t		tag_type;

    /* Specifies the header for which the parameter or tag is meant for. */
    icf_string_st hdr_name;

    /* Contains a tag value or parameter value. */
    icf_string_st tag_value;

    /* Contains pointer to the next tag/param element in the list, if any. */
    struct icf_tag_st *next ;
} icf_tag_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_tag_list_st
 *
 * Description: This datatype represents a structure that contains a list
 *                of SIP specific tags or parameters.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
    /* Specifies the number of tags/params present in the list. */
    icf_uint32_t count;

    /* Contains a pointer to the list of tags. */
    icf_tag_st *tag;
} icf_tag_list_st;








/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_void_st
 *
 * Description: This datatype is used to represents a generic structure.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* Specifies the length of structure pointed by ptr. */
    icf_uint32_t len;

    /* Contains pointer to a structure. */
    icf_uint8_t* ptr;
} icf_void_st;



/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_api_header_st
 *
 * Description: This is a generic API header used on all interfaces
 *
 *---------------------------------------------------------------------------*/
typedef struct                         
{

    /* a unique identifier for representing API received */
    icf_api_id_t          api_id;

    /* the version of the API being used */
    icf_version_t         version;

    /* a unique identifier to represent Source module of message */
    icf_module_id_t       source_id;

    /* a unique identifier to represent destinatione module of message */
    icf_module_id_t       destination_id;

    /* call ref number of the call for which data is exchanged */
    icf_call_id_t         call_id;

    /* This is application identifier obtained after configuration of 
    IMS Client Framework. */
    icf_app_id_t app_id;

    /* Total length of payload + API header   */
    icf_uint16_t          api_length;
} icf_api_header_st;



/*-----------------------------------------------------------------------------
*
* NAME : icf_msg_st
*
* DESCRIPTION  :ICF messages type 
*
-----------------------------------------------------------------------------*/

typedef struct 
{

      /* API Message header */
      icf_api_header_st   hdr;

      /* This is first byte of the payload. This is a strechable array. 
       * this field can be cast to the API specific structure 
       */ 
      icf_uint8_t         payload[1];
} icf_msg_st;
 


/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_name_st
 * 
 * Description: This data type is used to define a data value of pp_string_st 
 *              type, which contains the name of the calling or called party.
 *
 *---------------------------------------------------------------------------*/

typedef icf_string_st icf_name_st;   


/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_ipv4_int_address_st
 *
 * Description: This data type is used to define a union  
 *              which specifies the IP address
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
    /* Represents first octet of IPV4 address */
    icf_uint8_t octet_1;
    
    /* Represents second octet of IPV4 address */
    icf_uint8_t octet_2;

    /* Represents third octet of IPV4 address */
    icf_uint8_t octet_3;

    /* Represents fourth octet of IPV4 address */
    icf_uint8_t octet_4;
} icf_ipv4_int_address_st;



/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_ipv6_int_address_st
 *
 * Description: This data type is used to define a union  
 *              which specifies the IP address
 *
 *---------------------------------------------------------------------------*/

typedef icf_string_st icf_ipv6_int_address_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_transport_addr_type_t
 *
 * Description: This data type is used to define which transport
 *              address type is used
 *
 *---------------------------------------------------------------------------*/
#define  ICF_TRANSPORT_ADDRESS_INVALID          0
#define  ICF_TRANSPORT_ADDRESS_DOMAIN_NAME    1
#define  ICF_TRANSPORT_ADDRESS_IPV4_ADDR      2
#define  ICF_TRANSPORT_ADDRESS_IPV6_ADDR      3

typedef icf_uint8_t icf_transport_addr_type_t;



/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_transport_addr_st
 *
 * Description: This data type is used to define a union 
 *              which specifies the IP address.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    icf_transport_addr_type_t  addr_type;

    union address
    {
         /* Represent the name of domain on which the address exists */
         icf_long_string_st              domain;

         /* Represent the IPV4 address */
         icf_ipv4_int_address_st    ipv4_addr;
    
         /* Represent the IPV6 address */
         icf_ipv6_int_address_st  ipv6_addr;
    } addr;

} icf_transport_addr_st;


 

/*-----------------------------------------------------------------------------
 * 
 * Structure Name:icf_transport_address_st   
 *
 * Description: This data type is used to define a structure, which contains the
 *              IP address and the port number.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
    
    /* IP Address for the application */
    icf_transport_addr_st     addr;

    /* Port number for the application */
    icf_uint16_t              port_num;

} icf_transport_address_st;


/*----------------------------------------------------------------------------
 *
 *  icf_user_param_t : Used to define a data value of type,
 *  icf_uint8_t, whose value specifies the values in "user" param in SIP/Tel
 *  URI.
 *
 *--------------------------------------------------------------------------*/

typedef icf_uint8_t     icf_user_param_t;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_short_string_st
 *
 * Description: This data type represents a structure, which consists of a
 *              character array of specified length. This datatype will be used
 *              to store shorter strings.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
   
    /* specifies the length of the string including '\0' character */
    icf_uint16_t str_len;
   
    /* array of characters */
    icf_uint8_t   str[ICF_MAX_SHORT_STR_LEN];
   
} icf_short_string_st;



/*-----------------------------------------------------------------------------
*
* NAME : icf_address_st
*
* DESCRIPTION  : This datatype is used to define a structure, which specifies 
*                the payload data of the ICF_SM_CC_SET_STATS API.
*
-----------------------------------------------------------------------------*/
typedef struct
{

    /* specifies the string buffer containing the user address in a format 
     * defined by the addr_type field */
    icf_string_st         addr_val; 

    /* specifies the type of format for the user address information present in 
     * the addr_val parameter*/
    icf_address_type_t    addr_type;

} icf_address_st;





/*-----------------------------------------------------------------------
 * NAME : icf_media_mode_t
 *        This datatype is used to define the mode of the media session.
 *-----------------------------------------------------------------------*/
typedef icf_uint8_t icf_media_mode_t;



/*-----------------------------------------------------------------------
 * NAME : icf_qos_mark_t
 *-----------------------------------------------------------------------*/
typedef icf_uint8_t icf_qos_mark_t;



/*----------------------------------------------------------------------------
 *
 *  icf_call_clear_reason_t This data type is used to define a value of type 
 *  icf_uint8_t that indicates the reason for call clear
 *
 *--------------------------------------------------------------------------*/

typedef icf_uint8_t icf_call_clear_reason_t;    


/*----------------------------------------------------------------------------
 * icf_filter_type_t
 * 
 * This datatype is used to define the type of filter criteria 
 *--------------------------------------------------------------------------*/
typedef icf_uint8_t  icf_filter_type_t;

/*----------------------------------------------------------------------------
 * icf_match_type_t
 * 
 * This datatype is used to define the match type to be used while checking 
 * the filtering criteria value
 *--------------------------------------------------------------------------*/
typedef icf_uint8_t  icf_match_type_t;

/*----------------------------------------------------------------------------
 *
 *  icf_display_id_t This data type is used to define a value of type 
 *					 icf_uint16_t that identifies the display information, 
 *					 which needs to be displayed on phone.  
 *   
 *--------------------------------------------------------------------------*/

typedef icf_uint16_t icf_display_id_t;

/*----------------------------------------------------------------------------
 * icf_codec_type_t
 * 
 * 
 *--------------------------------------------------------------------------*/
typedef icf_uint8_t  icf_codec_type_t;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_config_self_addr_st 
 *
 * Description: This structure contains contains the information of the
 *               self address to be modified 
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
      /*Line id in which the address to be configured */
      icf_line_id_t         line_id;

      /*Specifies whether address to be added or deleted*/
      icf_config_action_t   action;

      /*Address to be added or modified*/
      icf_address_st        addr;
} icf_config_self_addr_st;



/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_uri_list_st 
 *
 * Description: This datatype is used to contain list of URIs
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
    /* Indicates the number of valid elements in the uri array. */
    icf_uint8_t num_of_elements;

    /* Contains the information about the uri to be configured. */
    icf_address_st uri[ICF_MAX_NUM_OF_CONFIG_ELEMENTS];
} icf_uri_list_st;



/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_transport_list_st 
 *
 * Description: This datatype is used to contain list of transport address. 
 *
 *---------------------------------------------------------------------------*/


typedef struct
{
    /* Indicates the number of valid elements in the transport_addr */
    icf_uint8_t num_of_elements;

    /* Contains the information about the uri to be configured. */
    icf_transport_addr_st addr[ICF_MAX_NUM_OF_CONFIG_ELEMENTS];
} icf_transport_list_st;



/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_config_proxy_transport_addr_st 
 *
 * Description: This data type is used to define a structure, which contains
 *              the proxy transport addresses supported by phone.
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
    /* Line id in which the transport address and mode is to be configured. */
    icf_line_id_t          line_id;

    /* Specifies whether address to be added or modified or deleted */
    icf_config_action_t        action;

    /* Transport address to be configured. */
    icf_transport_address_st  transport_addr;

    /* Transport mode to be configured */
    icf_transport_mode_t      transport_mode;

    icf_uint8_t               sigcomp_options ;

} icf_config_proxy_transport_address_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_config_sec_transport_address_st 
 *
 * Description: This data type is used to define a structure, which contains
 *              the secondary transport addresses supported by phone.
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
    /* Line id in which the transport address and mode is to be configured. */
    icf_line_id_t          line_id;

    /* Specifies whether address to be added or modified or deleted */
    icf_config_action_t        action;

    /* Transport address to be configured. */
    icf_transport_address_st  transport_addr;

} icf_config_sec_transport_address_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_config_transport_addr_st
 *
 * Description: This data type is used to define a structure, which contains
 *              the transport addresses supported by phone
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* Line id in which the transport address and mode is to be configured. */
    icf_line_id_t          line_id;

    /* Specifies whether address to be added or deleted, modified is not allowed
     * for self transport address. Address has to be deleted and added again to modify */
    icf_config_action_t        action;

    /* Transport address to be configured. */
    icf_transport_address_st  transport_addr;

    /* Transport mode to be configured */
    icf_transport_mode_t      transport_mode;
} icf_config_transport_address_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_config_transport_addr_list_st 
 *
 * Description: This data type is used to define a structure, which contains
 *              the list of transport addresses supported by phone.
 *
 *---------------------------------------------------------------------------*/

typedef struct 
{
      /*If the value is TRUE, the value contained in the first element 
       *of array is applicable for all lines*/
      icf_boolean_t   all_lines;

      /*Number of valid elements in the array transport_addr*/
      icf_uint8_t     num_of_elements;

      /*The information for the trasnport address to be configured*/
      icf_config_transport_address_st
                         transport_addr[ICF_MAX_NUM_OF_CONFIG_ELEMENTS];

} icf_config_transport_address_list_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_config_self_addr_list_st 
 *
 * Description: This structure contains contains the list of local user
 *               addresses supported by the phone 
 *
 *---------------------------------------------------------------------------*/

typedef struct 
{
      /*If the value is TRUE, the value contained in the first element 
       *of array is applicable for all lines*/
      icf_boolean_t             all_lines;

      /*Number of valid elements in the array self_addr*/
      icf_uint8_t               num_of_elements;

      /*information for the self address to be configured*/
      icf_config_self_addr_st   self_addr[ICF_MAX_NUM_OF_CONFIG_ELEMENTS];
} icf_config_self_addr_list_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_config_self_name_st 
 *
 * Description: This structure contains contains the information of local user
 *               name to be modified 
 *
 *---------------------------------------------------------------------------*/

typedef struct 
{
      /*Line id in which the name to be configured*/
      icf_line_id_t         line_id;

      /*Specifies whether name to be added or deleted*/
      icf_config_action_t   action;

      /*Name to be added or modified*/
      icf_name_st           name;

} icf_config_self_name_st;



/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_config_self_name_list_st 
 *
 * Description: This structure contains contains the list of local user
 *               name supported by the phone 
 *
 *---------------------------------------------------------------------------*/

typedef struct 
{
      /*If the value is TRUE, the value contained in the first element 
       *of array is applicable for all lines*/
      icf_boolean_t             all_lines;

      /*Number of valid elements in the array self_name*/
      icf_uint8_t               num_of_elements;

      /*information for the self name to be configured*/
      icf_config_self_name_st   self_name[ICF_MAX_NUM_OF_CONFIG_ELEMENTS];

} icf_config_self_name_list_st;






/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_config_default_settings_st 
 *
 *  Description: This data type is used to define a structure, which 
 *  contains the default settings for a  line.
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
    /* Line ID for which default_settings is configured */
    icf_line_id_t         line_id;

    /* Address of the party */
    icf_uint8_t          default_settings;

} icf_config_default_settings_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_config_default_settings_list_st 
 *
 *  Description: This data type is used to define a structure, which 
 *               contains the list of default settings supported by phone.
 *
 *---------------------------------------------------------------------------*/

typedef struct 
{
    /*If TRUE, value of first element will be applicable for all lines*/
    icf_boolean_t        all_lines;

    /*Number of valid elements in the array*/
    icf_uint8_t          num_of_elements;

    /* Contains the default settings per line             */
    icf_config_default_settings_st
                            default_settings[ICF_MAX_NUM_OF_CONFIG_ELEMENTS];

} icf_config_default_settings_list_st;




/*ZYXEL porting Amber 20190604 for adding IOPFlag from set service param req into LineParameter for each Line/Acct*/
#if 1 //ZYXEL_VOIP_PROPAGATE_IOP_BITFLAG_TO_IPTK_AT_RUNTIME_CONFIG.
/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_config_iopflags_st 
 *
 *  Description: This structure contains the bitmask per line 
 *               for ZYXEL iopflags.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
      /*Line id for which the status is to be configured*/
      icf_line_id_t      line_id;

      /*This is a bitmask which can be used for multiple purposes*/
#define ZYXEL_IOP_FLAG_IGNORE_APPENDED_INFO_IN_REQUEST_URI	(1 << 0) //ZYXEL_SIP_IGNORE_APPENDED_INFOMATION_IN_REQUEST_URI. //Amber.20190527: Mapping to VOIP_SIG_IOP_FLAG_IGNORE_APPENDED_INFO_IN_REQUEST_URI in ZyIMS and this iopflag is to Relax the Validation Logic on the Request URI to accept/tolerate the Non-standard-compliant case: some information (e.g. user=phone, transport=udp) had been appended to the Request URI of SIP CANCEL but NOT append to the Request URI of its coresponding SIP INVITE message.
#define ZYXEL_IOP_FLAG_RTP_STATS_HEADER_USE_X_RTP_STAT	(1 << 1) //ZYXEL_SIP_HDR_FOR_AFTER_CALL_RTP_STATS_SEND_IN_BYE_AND_200OK. //Amber.20190605: Mapping to VOIP_SIG_IOP_FLAG_RTP_STATS_HEADER_USE_X_RTP_STAT and this iopflag is to runtime change the RTP Statistic header name from 'P_RTP_Stat' to 'X_RTP_Stat'.
      icf_uint32_t       iopflags;

} icf_config_iopflags_st;
#endif
/*ZYXEL porting Amber 20190604*/




/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_config_status_st 
 *
 *  Description: This structure contains contains the bitmask per line. 
 *               like service subscr ption, service activation etc 
 *
 *---------------------------------------------------------------------------*/

typedef struct 
{
      /*Line id for which the status is to be configured*/
      icf_line_id_t      line_id;

      /*This is a bitmask which can be used for multiple purposes*/
      icf_uint16_t        status;

} icf_config_status_st;





/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_config_status_list_st 
 *
 * Description: THis structure contains the list of status values for lines
 *
 *---------------------------------------------------------------------------*/

typedef struct 
{
      /*If the value is TRUE, the value contained in the first element 
       *of array is applicable for all lines*/
      icf_boolean_t           all_lines;

      /*Number of valid elements in the array transport_mode_per_line*/
      icf_uint8_t             num_of_elements;
     
      /*Contains the value for the status to be configured for a line*/ 
      icf_config_status_st    status[ICF_MAX_NUM_OF_CONFIG_ELEMENTS];

} icf_config_status_list_st;





/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_config_address_st 
 *
 *  Description: This data type is used to define a structure, which 
 *  contains the party address for a  line.
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
    /* Line ID for which address is configured */
    icf_line_id_t        line_id;

    /* Address of the party */
    icf_address_st        address;

} icf_config_address_st;




/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_config_address_list_st 
 *
 *  Description: This data type is used to define a structure, which 
 *               contains the list of party address.
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
    /*If TRUE, value of first element will be applicable for all lines*/
    icf_boolean_t        all_lines;

    /*Number of valid elements in the array*/
    icf_uint8_t              num_of_elements;

    /* Contains the address to be configured for a line.  */
    icf_config_address_st    address[ICF_MAX_NUM_OF_CONFIG_ELEMENTS];
} icf_config_address_list_st;



/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_config_registration_params_st
 *
 * Description: 
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
    /* This indicates the presence of the optional parameters. */
    icf_uint8_t bit_mask;
    #define ICF_CONFIG_RG_PRM_RG_ADDR                     0x01
    #define ICF_CONFIG_RG_PRM_RG_MODE                     0x02
    #define ICF_CONFIG_RG_PRM_RG_DURATION                 0x04
    #define ICF_CONFIG_RG_PRM_AUTH_KEY                    0x08
    #define ICF_CONFIG_RG_PRM_AUTH_PASSWORD               0x10

#ifdef IMS_CLIENT
#define ICF_CONFIG_RG_PRM_AUTH_REALM                 0x020
#define ICF_CONFIG_RG_PRM_AUTH_NONCE                 0x040
#define ICF_CONFIG_RG_PRM_AUTH_NC                    0x080
#define ICF_CONFIG_RG_PRM_AUTH_CNONCE                0x100
#define ICF_CONFIG_RG_PRM_AUTH_RESPONSE              0x200
#define ICF_CONFIG_RG_PRM_AUTH_OPAQUE                0x400
#endif

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

    /* SIP registrar IP address. When action is add this field is mandatory */
    icf_transport_address_st       registrar_addr;

    /* transport mode for registration request */
    icf_transport_mode_t            reg_mode;

     /* duration of registration which is line specific */
     icf_duration_t                registration_duration;

     /* Contains the list of authentication key configured per line */
     icf_string_st                 authentication_key;

     /* Contains the list of authentication password configured per line */
     icf_string_st                 authentication_password;
#ifdef IMS_CLIENT
    /* The following parameters are configured to support AKA algorithm,
       Shall be removed once Algorithm itself is in place */
     /* Contains the realm */
     icf_string_st                 auth_realm;

     /* Contains the nonce */
     icf_string_st                 auth_nonce;

     /* Contains the nc */
     icf_string_st                 auth_nc;

     /* Contains the cnonce */
     icf_string_st                 auth_cnonce;

     /* Contains the response */
     icf_string_st                 auth_response;

     /* Contains the opaque */
     icf_string_st                 auth_opaque;
#endif
} icf_config_registration_params_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_address_list_node_st
 *
 * Description: This structure represents a node in a list of address
 *---------------------------------------------------------------------------*/
typedef struct icf_address_list_node_st
{
    icf_address_st user_addr;
    struct icf_address_list_node_st *p_next;
}icf_address_list_node_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_pub_uri_list_node_st
 *
 * Description: This structure is a node in the public uri list 
 *                list of SIP headers.
 *
 *---------------------------------------------------------------------------*/


typedef struct icf_pub_uri_list_node_st{
    icf_address_st pub_uri;
    icf_address_list_node_st *p_assoc_uri_list;
    struct icf_pub_uri_list_node_st *p_next;
}icf_pub_uri_list_node_st;
#ifdef ICF_NW_ACTIVATE
/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_network_info_st
 *
 * Description: This datatype is used to define a structure, that IPv4 
 *                addresses in 4-octet format.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
    /* This indicates the presence of the optional parameters. */
    icf_uint8_t bit_mask;
    #define ICF_NET_INFO_CTXT_ID_PRESENT 0x01
    #define ICF_NET_INFO_SELF_IP_PRESENT 0x02
    #define ICF_NET_INFO_ACCESS_TYPE_PRESENT 0x04
    #define ICF_NET_INFO_ACCESS_INFO_PRESENT 0x08
    #define ICF_NET_INFO_ASSO_URI_PRESENT 0x10
    #define ICF_NET_INFO_OUT_PROXY_ADDR_PRESENT 0x20
#ifdef ICF_P_CSCF_DISCOVERY_ENABLED
    #define ICF_NET_INFO_DNS_ADDR_PRESENT 0x40
#endif

    /* This is the logical PDP context id. */
    icf_uint32_t ctxt_id;

    /* This is the IP address associated with the PDP context. */
    icf_transport_addr_st self_ip;

    /* This specifies the access network type. */
    icf_uint8_t access_type;

    /* This specifies the parameters for accessing network. */
    icf_string_st access_info;

    /* Denotes the associated public uri. */
    icf_pub_uri_list_node_st *p_uri_list;

    /* Denotes the known outbound proxy IP addresses. */
    icf_transport_list_st out_proxy_addr;
    
#ifdef ICF_P_CSCF_DISCOVERY_ENABLED
    /* Denotes the known outbound proxy IP addresses. */
    icf_transport_list_st dns_addr;
#endif
} icf_network_info_st;
#endif

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_header_name_st
 *
 * Description: This datatype represents a structure that contains SIP headers.
 *
 *---------------------------------------------------------------------------*/
typedef struct icf_header_name_st

{
    /* Specifies the SIP header name. */
    icf_string_st hdr_name;

    /* Contains pointer to the next header in the list, if any. */
    struct icf_header_name_st *next ;
} icf_header_name_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_header_name_list_st
 *
 * Description: This datatype represents a structure that contains a 
 *                list of SIP headers.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* Specifies the number of SIP headers in the list. */
    icf_uint32_t count;

    /* Contains a pointer to the list of header names. */
    icf_header_name_st *hdr;
} icf_header_name_list_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_udp_st
 *
 * Description: This datatype is used to define a structure, which 
 *                contains the UDP address and port.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* IP address */
    icf_transport_addr_st ip;

    /* UDP Port used */
    icf_uint16_t port ;
} icf_udp_st ;





/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_tcp_st
 *
 * Description: This datatype is used to define a structure, which 
 *                contains the TCP address and port.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{

    icf_uint8_t type; /* ICF_TCP_SERVER, ICF_TCP_CLIENT */

    /* IP address */
    icf_transport_addr_st ip;

    /* TCP Port used */
    icf_uint16_t port ;
} icf_tcp_st ;





/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_msgq_st
 *
 * Description: This datatype is used to define a structure, which 
 *                contains the message queue info.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
    /* Message type */
    icf_int32_t mtype ;

    /* Message Key */
    icf_int32_t mkey ;
} icf_msgq_st ;






/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_route_info_st
 *
 * Description: This datatype is used to define a structure, which 
 *                contains the route info.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
    /* Indicates the IPC type specified in the ipc parameter. */
    icf_uint8_t type;

    /* Contains IPC related parameters. */
    union ipc_t
    {
        icf_udp_st udp ;
        icf_tcp_st tcp ;
        icf_msgq_st msgq ;
    } ipc ;

} icf_route_info_st;
/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_filter_st
 *
 * Description: This datatype defines a structure for the filter list node,  
 *              which contains filter specification for a single filter and a
 *              pointer to the next filter in the list.
 * Note :       Filter Types can be one of the following -
 *              
 *              ICF_FILTER_BY_HEADER_NAME - The expression in expr_str is 
 *                    evaluated against the headers the SIP message by ICF. 
 *              ICF_FILTER_BY_HEADER_CONTENT - ICF checkes whether the header 
 *                    specified in 'target_header' parameter is present 
 *                    or not in the incoming SIP message. 
 *                    If the header is present then the expression stored in 
 *                    expr_str parameter will be matched with the header value.
 *              ICF_FILTER_BY_METHOD_NAME -In this case expr_str stores the 
 *                    SIP method(s) to be matched. ICF checks whether the 
 *                    method in incoming SIP request is present or not. 
 *              ICF_FILTER_BY_REQ_URI_HDR_PARAM - In this case ICF checks 
 *                    whether the request uri received in SIP message matches 
 *                    with the expression in  expr_str.
 * 	    * For filter_type ICF_FILTER_BY_HEADER_NAME & ICF_FILTER_BY_METHOD_NAME
 *           only ICF_EXACT_STRING_MATCH is supported. 
 *      * target_header field is only used for the filter type 
 *           ICF_FILTER_BY_HEADER_CONTENT. 
 *      * If an application does not specify any filter criteria 
 *           (by setting filter count as 0 in the filter list structure), 
 *           then it will be considered as the default application to which 
 *           requests not matching any app filter criteria are forwarded 
 *              
 *---------------------------------------------------------------------------*/

typedef struct icf_filter_st
{

/*#defines for icf_filter_type_t*/
#define ICF_FILTER_TYPE_INVALID             0
#define ICF_FILTER_BY_HEADER_NAME           1
#define ICF_FILTER_BY_HEADER_CONTENT        2
#define ICF_FILTER_BY_METHOD_NAME           3
#define ICF_FILTER_BY_REQ_URI_HDR_PARAM     4

/* Specifies the filter type */
icf_filter_type_t    filter_type;

/*#defines for icf_match_type_t*/
#define ICF_STRING_MATCH_INVALID         0
#define ICF_EXACT_STRING_MATCH           1
#define ICF_SUB_STRING_MATCH             2

/* Specifies the method to be used while matching the filter */
icf_match_type_t    match_type;
/* Name of sip header on which the filter criteria is to be applied */
icf_string_st        target_header;
/* Specifies the expression string, which has to be matched according to the filter criteria */
icf_string_st        expr_str;
/* Pointer to the next filter node in the list */
struct icf_filter_st       *p_next;

}icf_filter_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_filter_list_st
 *
 * Description: This datatype is used to define a structure, which contains 
 *              a list of filters for ICF to determine the application  
 *              corresponding to the message obtained from the network where 
 *              call_id field is not maintained by ICF 
 *              
 *---------------------------------------------------------------------------*/

typedef struct 
{
    /* Specifies the number of filters in the list */
    icf_uint32_t     count;

    /* This flag is set to TRUE by the application if all the filter 
     * criteria are to be satisfied present in the filter list. 
     * By default ICF will consider this flag as FALSE.
     */
    icf_boolean_t    match_all;

    /*pointer to the list of filters */
    icf_filter_st     *p_filter_list;
    
} icf_filter_list_st;

/*-----------------------------------------------------------------------------
 * 
 * Structure Name:icf_apn_list_st   
 * Description: This data type is used to define a structure, which contains 
 *              the list of APNs .
 *
 *---------------------------------------------------------------------------*/
typedef struct
{

    icf_uint32_t              count;
    icf_string_st     *p_list_of_apn;
} icf_apn_list_st;

/*-----------------------------------------------------------------------------
 * 
 * Structure Name:icf_generic_string_st
 * Description: This data type is used to define a structure, which contains 
 *              string length and pointer to string
 *
 *---------------------------------------------------------------------------*/
typedef struct{
    icf_uint32_t    len;
    icf_uint8_t     *p_buff;
}icf_generic_string_st;
    
      
/*-----------------------------------------------------------------------------
 *
 * Name: icf_hold_option_t 
 *
 * Description: This data type is used to define a data value of icf_uint8_t
 *              type, which identifies the option used by CC to send call hold 
 *              indication to remote party.
 *
 *---------------------------------------------------------------------------*/
typedef icf_uint8_t icf_hold_option_t;


/*------------------------------------------------------------------------------
*
* Name :		 icf_display_data_st
*
* Description  : This data type is used to define a structure,
*               which contains display data to be displayed in the API 
*               ICF_CC_PA_DISPLAY_REQ.             
-----------------------------------------------------------------------------*/

typedef struct
{

    /* Number of valid integer values present in the display data.*/
    icf_uint8_t   num_of_integer_values;
    
    /* Array of integer values, which will contain display data.*/
    icf_int32_t   int_val[ICF_MAX_INT_DISPLAY_DATA];  

    /* Number of valid string values present in the display data.*/
    icf_uint8_t   number_of_string_values;
    
    /* Array of string values that will contain display data.*/
    icf_string_st string_val[ICF_MAX_STR_DISPLAY_DATA];    

} icf_display_data_st;
/*-----------------------------------------------------------------------------
 *
 * Name: icf_tone_id_t 
 *
 * Description: This data type is used to define a data value of icf_uint16_t
 *              type, which identifies the tones
 *
 *---------------------------------------------------------------------------*/

typedef icf_uint16_t icf_tone_id_t;


/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_string_list_node_st
 *
 * Description: This datatype represents a structure that contains SIP headers.
 *
 *---------------------------------------------------------------------------*/
typedef struct icf_string_list_node_st

{
    /* Specifies the SIP header name. */
    icf_string_st str;

    /* Contains pointer to the next header in the list, if any. */
    struct icf_string_list_node_st *p_next ;
} icf_string_list_node_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_string_list_st
 *
 * Description: This datatype represents a structure that contains a 
 *                list of SIP headers.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* Specifies the number of SIP headers in the list. */
    icf_uint32_t count;

    /* Contains a pointer to the list of header strings. */
    icf_string_list_node_st *p_list;
} icf_string_list_st;

/* ------------------------------------------------------------------------
 * Type Name   :  icf_es_init_info_st
 * Description :  This structure contains the init time parameters required
 *				  by ES for its initialising.
 *               
 * ------------------------------------------------------------------------*/

typedef struct
{
    icf_uint8_t           mm_addr[32];
    icf_uint16_t          mm_port;
} icf_es_mm_info_st;

#ifdef ICF_NAT_MEDIA_TRAVERSAL

/* ------------------------------------------------------------------------
 * Type Name   :  icf_es_nat_info_st
 * Description :  This structure contains the nat configured IP and Port
 *				  required by ES for its initialising.
 *               
 * ------------------------------------------------------------------------ */

typedef struct
{
    icf_uint8_t           nat_addr[32];
    icf_uint16_t          nat_port;
}icf_es_nat_info_st;

#endif

/*-----------------------------------------------------------------------------
 *
 *  Structure Name : icf_scalable_info_st
 *
 *  Description :    structure for scalable parameters
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
	icf_uint32_t	num_of_max_lines;
	icf_uint32_t	num_of_max_apps;
#ifdef ICF_NW_ACTIVATE
	icf_uint32_t	num_of_max_nws;
#endif
	icf_uint32_t	num_of_max_uri;
	icf_uint32_t	num_of_max_audio_calls;
	icf_uint32_t	num_of_max_video_calls;
	icf_uint32_t	num_of_max_service_calls;
	icf_uint32_t	num_of_max_call_history;
	icf_uint32_t	num_of_max_reg;
	icf_uint8_t     sys_resource_limit;
    icf_uint8_t	    num_of_calls_to_log;

 } icf_scalable_info_st;

typedef enum
{
    ICF_FILE_FORMAT_INVALID =0,
    ICF_FILE_FORMAT_PEM,
    ICF_FILE_FORMAT_DER
}icf_file_format_et;

/*-----------------------------------------------------------------------------
 *
 *  Structure Name : icf_tls_init_params_st
 *
 *  Description :    structure for TLS parameters
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
	icf_string_st		cert_file;
	icf_file_format_et	cert_format;
	icf_string_st		private_key_file;
	icf_string_st		private_key_passwd;
	icf_string_st		ca_cert_dir_path;
	icf_string_st		cipher_suites;
	icf_string_st		dh_param_file;
	icf_string_st		ca_cert_file;
	icf_file_format_et	dh_param_file_format;
	icf_uint8_t 		cert_verify_mode;
    icf_uint16_t		tls_sip_serv_port_num;

 } icf_tls_init_params_st;

/* --------------------------------------------------------------------
 * Type Name   :  icf_init_param_st
 * Description :  This structure contains the init time parameters 
 *               
 * ------------------------------------------------------------------------*/


typedef struct 
{
	/* the opt_params_bitmask indicates presence of optional parameters as 
	   well as the Flags */
#ifdef ICF_NW_ACTIVATE
	/* first bit indicates presence of type of access network */
    #define ICF_ACCESS_NET_TYPE_PRESENT 0x00000001
	/* second bit indicates presence of the APN string */
    #define ICF_APN_STRING_PRESENT 0x00000002
#endif
	/* third bit indicates presence of the port on which ICF listens
	   to messages from applications */
    #define ICF_DEF_SIP_SERVER_PORT 0x00000004
	/* fourth bit indicates presence of network(P-CSCF) port on which
	   ICF sends network messages */
    #define ICF_DEF_SIP_PROXY_PORT 0x00000008
	/* fifth bit indicates the presence of the mode of transport with network */
    #define ICF_DEF_SIP_TRANSPORT_MODE 0x00000010
	/* sixth bit indicates whether compaction of SIP message headers is required,
	   true if it is required, false otherwise */
    #define ICF_SIP_COMPACT_HDR 0x00000020
	/*  ninth bit indicates whether SIGCOMP is required */
    #define ICF_PACK_PERIOD_PRESENT 0x00000100
 	/* twelfth bit indicates whether log trace to file is enabled */
    #define ICF_NW_TRACE_ENABLED 0x00000800
	/* thirteenth bit indicates if the out of dialog msg handling is required*/
    #define ICF_NON_SUBSCRIBE_NOTIFY_ENABLE	0x00001000
    /* 14th bit indicates whether blocking/non-blocking connect has to be fired */
    #define ICF_BLOCKING_CONNECT            0x00002000

	/* fifteenth bit indicates resource reservation is required */
	#define ICF_QOS_RES_RESERV_SUPPORTED	0x00004000

	icf_uint32_t          bitmask;
    /* the bitmask operation_mode indicates the mode of operation-IMS or Non-IMS */
	/* first bit indicates Non-IMS mode */
    #define ICF_OPERATION_MODE_NON_IMS 0x00
	/* second bit indicates IMS operation */
    #define ICF_OPERATION_MODE_IMS 0x01
	icf_uint8_t           operation_mode;
    icf_void_t            *p_generic_rt_info;
    icf_boolean_t         auto_scale;

    icf_uint16_t		  sip_serv_port_num;
	icf_uint16_t		  sip_proxy_port_num;
	/*	ICF_TRANSPORT_MODE_BOTH	2	
		ICF_TRANSPORT_TYPE_TCP	1
		ICF_TRANSPORT_TYPE_UDP	0
	*/
	icf_transport_mode_t  sip_mode;

    icf_scalable_info_st		*p_scalable_info; /* contains the scalable parameters info */
    icf_tls_init_params_st      *p_tls_init_data; /* contains the TLS parameters info */
/* parameters for dns buffering */
    icf_uint8_t			sip_req_retry;
    icf_uint32_t		dns_purge_timer;	
/* end of the dns buffer code */

#ifdef ICF_PORT_WINCE
	icf_uint8_t         logs_indication;
#endif

#ifdef ICF_DNS_LOOKUP_ENABLED
    /*---- varaible added for open source replacement(IPTK REL 8.1)----start---- */
    icf_transport_address_st        *p_arDnsClient_addr;
    icf_transport_address_st        *p_arDnsClib_addr;
    /*---- varaible added for open source replacement(IPTK REL 8.1)----end----- */
#endif

} icf_init_param_st;


/*-----------------------------------------------------------------------------
 *
 * typedef Name : icf_time_n_date_st
 * 
 *  Description  : This data type is used to define a structure which specifies
 *                 the data and time information.
 *   
 -----------------------------------------------------------------------------*/

typedef struct
{

    icf_uint8_t     seconds;  /* seconds after the minute - [0,61] */
    icf_uint8_t     minutes;  /* minutes after hour - [0,59] */
    icf_uint8_t     hour;     /* hour since midnight - [0,23] */
    icf_uint8_t     date;     /* day of the month - [1,31] */
    icf_uint8_t     month;    /* months after January - [0,11] */
    icf_uint32_t    year;     /* year like 2005 */


} icf_time_n_date_st;

typedef icf_uint8_t  icf_stats_id_t;

/* ICF rel 6.0 Multiple m-lines moved from icf_mm_types.h */
/*-----------------------------------------------------------------------------
*
* Structure Name: icf_amr_params_st
*
* Description: This data type defines parameters for AMR specific codec.
*---------------------------------------------------------------------------*/

typedef struct
{
#define  ICF_AMR_MODE_LIST_PRESENT     0x01
	icf_uint8_t     bit_mask;
    /* Preffered AMR Mode */
    icf_uint8_t 	amr_initial_mode;
    /* List of AMR mode */
    /* Number of valid amr_modes in amr_mode_list*/
    icf_uint8_t     amr_mode_count;
    icf_uint8_t     amr_mode_list[ICF_MAX_AMR_MODE];

#define ICF_OCTET_ALIGNED_MODE 1
#define ICF_BANDWIDTH_EFF_MODE 2
	icf_uint8_t 	codec_mode;

	icf_boolean_t 	crc_enabled; 
} icf_amr_params_st;

/* ICF rel 6.0 Multiple m-lines */
/*--------------------------------------------------------------------------- 
 * Structure Name: icf_config_audio_codec_param_st
 *
 * Description: This datatype is used to define a structure , which specifies 
 * the attributes specific to audio codec.  
 *---------------------------------------------------------------------------*/
typedef struct
{
icf_uint8_t       bit_mask;
#define ICF_AUDIO_CODEC_CHANNEL             0x01 
#define	ICF_AUDIO_CODEC_BANDWIDTH       	0x02
#define ICF_AUDIO_CODEC_PTIME               0x04
#define	ICF_AUDIO_CODEC_SILENCE_SUPPRESSION	0x08
#define	ICF_AUDIO_CODEC_SAMPLING_RATE 	    0x10
#define ICF_AUDIO_CODEC_AMR_PARAM           0x20
/* Channel id is to identify maximul multiple audio
 * channels supported for this codec  */
icf_uint8_t       channels;
/* Max number of ptime supported for this codec */
icf_uint8_t     num_of_supported_ptime;           
/* Array of ptime */
icf_uint8_t     ptime[ICF_MAX_SUP_PTIME];     
#if 1 /*ZyXEL porting*/
icf_uint8_t     pref_ptime;
#endif
/* Max bandwidth req by this codec */
icf_uint32_t    bandwidth; 
/* Denotes the sampling rate supported by audio codec*/
icf_uint8_t     num_of_supp_sampling_rate;
icf_uint16_t    sampling_rate[ICF_MAX_SUP_SAMPLING_RATE];

/* set the value of silence suppression as on or off  */
icf_boolean_t   silence_suppression;
/* Amr Parameters */
icf_amr_params_st amr_params;


} icf_config_audio_codec_param_st;

/*--------------------------------------------------------------------------- 
 * Structure Name: icf_size_st
 *
 * Description: This datatype is used to define a structure , which specifies 
 * the attributes specific size .Required mainly for video screens
 *---------------------------------------------------------------------------*/
typedef struct
{
icf_uint16_t    height;   
icf_uint16_t    width;
}icf_size_st;


/* ICF rel 6.0 Multiple m-lines */
/*--------------------------------------------------------------------------- 
 * Structure Name: icf_config_video_codec_param_st
 *
 * Description: This datatype is used to define a structure , which specifies 
 * the attributes specific to video codec.  
 *---------------------------------------------------------------------------*/
typedef struct
{
#define ICF_VIDEO_CFG_CODEC_FRAME_RATE_PRESENT  0x01
#define ICF_VIDEO_CFG_CODEC_CLOCK_RATE_PRESENT  0x02
#define ICF_VIDEO_CFG_CODEC_FRAMESIZE_PRESENT	0x04
#define ICF_VIDEO_CFG_CODEC_ENC_QUALITY_PRESENT 0x08
#define ICF_VIDEO_CFG_CODEC_BANDWIDTH_PRESENT   0x10
	icf_uint8_t       bit_mask;

icf_uint8_t   frame_rate;
/* This value should be between 0 and 10 with 0 indicatiing lowest quality
 * and 10 indicating highest quality. If this value is not present
 * Default value of 5 should be taken */
icf_uint8_t   encoding_quality;
/* Maximum bandwidth required by the codec */
icf_uint16_t  bandwidth; 
/* Clock rate supported by codec */
icf_uint8_t   num_of_supp_clock_rate;
icf_uint32_t  clock_rate[ICF_MAX_SUP_CLOCK_RATE];
icf_size_st   frame_size;

}icf_config_video_codec_param_st;




/* ICF rel 6.0 Multiple m-lines */
/*--------------------------------------------------------------------------- 
 * Structure Name: icf_config_t38_attrib_param_st
 *
 * Description: This datatype is used to define a structure , which specifies 
 * the attributes specific to audio codec.  
 *---------------------------------------------------------------------------*/
typedef struct
{
#define	ICF_FAX_T38_VERSION          	0x01
#define	ICF_FAX_T38_BITRATE     	    0x02
#define	ICF_FAX_T38_RATE_MANAGEMENT  	0x04
#define	ICF_FAX_T38_UDP_BUFFSIZE     	0x08
#define	ICF_FAX_T38_UDP_PACKETSIZE      0x10
#define	ICF_FAX_T38_ERR_CORRECTION   	0x20

	icf_uint8_t       bit_mask;

#define	ICF_T38_1998	0
#define	ICF_T38_2000	1
#define	ICF_T38_2002	2
	icf_uint8_t           fax_version;

#define	ICF_T38_2400_BIT_PER_SEC	2400
#define	ICF_T38_4800_BIT_PER_SEC	4800
#define	ICF_T38_7200_BIT_PER_SEC	7200
#define ICF_T38_9600_BIT_PER_SEC	9600
#define	ICF_T38_14400_BIT_PER_SEC	14400    
#define	ICF_T38_33600_BIT_PER_SEC	33600
	icf_uint32_t      bitrate;

#define	ICF_T38_RATE_MANAGEMENT_LOCAL		0
#define	ICF_T38_RATE_MANAGEMENT_TRANSFERRED	1
	icf_uint8_t   rate_management;  
	/*maximum buffer  size */
	icf_uint32_t                 udp_buffersize; 
	/*maximum packet size       */
	icf_uint32_t                 udp_packetsize;    
#define ICF_T38_ERROR_CORR_REDUNDANCY  0x01
#define ICF_T38_ERROR_CORR_FEC         0x02
	icf_uint8_t   err_correction_method;
	
}icf_config_t38_attrib_param_st;

/* ICF rel 6.0 Multiple m-lines */
/*--------------------------------------------------------------------------- 
 * Structure Name: icf_config_codec_params_ut
 *
 * Description: This datatype is used to define a union, which specifies the 
 * codec attributes.  
 *---------------------------------------------------------------------------*/
union icf_config_codec_params_ut
{
	icf_config_audio_codec_param_st  audio_param;
    icf_config_video_codec_param_st  video_param;
	icf_config_t38_attrib_param_st   t38_param;
};

/* ICF REL 6.0: multiple m lines */
/*-----------------------------------------------------------------------------
*
* Structure Name: icf_list_st
*
* Description: 
*---------------------------------------------------------------------------*/
typedef struct icf_list_s
{

	icf_void_t			*p_data; /* pointer to the list payload */
	struct icf_list_s	*p_next; /* pointer to the next node */
}icf_list_st;

/* ICF rel 6.0 Multiple m-lines */
/*--------------------------------------------------------------------------- 
 * Structure Name: icf_config_codec_attrib_st
 *
 * Description:   
 *---------------------------------------------------------------------------*/
typedef struct{
#define ICF_CODEC_PARAM_PRESENT     0x01
#define ICF_ENCODED_PARAM_PRESENT   0x02
#if 1 /*ZyXEL porting*/
#define ICF_CODEC_NUM_PRESENT   0x04
#endif
	icf_uint8_t      bitmask;

#define ICF_CODEC_TYPE_AUDIO   1
#define ICF_CODEC_TYPE_VIDEO   2
#if 1 /* ZyXEL porting*/
#define ICF_CODEC_TYPE_TBCP   3 
#define ICF_CODEC_TYPE_IMAGE   4 
#else
#define ICF_CODEC_TYPE_IMAGE   3 
#endif
icf_codec_type_t  codec_type;

icf_short_string_st	codec_name;
#if 1 /*ZyXEL porting*/
icf_uint8_t	codec_num;
icf_uint8_t	enable;
#endif

/* List of attributes for the media stream. This is a list of the node
 type icf_string_st */
icf_list_st *p_encoded_params;
	
union icf_config_codec_params_ut   codec_param; 
}icf_config_codec_attrib_st;


/* ICF rel 6.0 Multiple m-lines */
/*--------------------------------------------------------------------------- 
 * Structure Name: icf_audio_codec_param_st
 *
 * Description: This datatype is used to define a structure , which specifies 
 * the attributes specific to audio codec.  
 *---------------------------------------------------------------------------*/
typedef struct
{
	icf_uint8_t       bit_mask;
#define  ICF_AUDIO_CODEC_PARAM_CHANNEL         0x01 
#define  ICF_AUDIO_CODEC_PARAM_AMR_PARAM       0x02
#define  ICF_AUDIO_CODEC_PARAM_SAMPLING_RATE   0x04      
#define  ICF_AUDIO_CODEC_PARAM_VBD_VAL         0x08

  	/* Channel id is to identify multiple audio streams */
	icf_uint8_t       channels;
	icf_uint16_t      sampling_rate;
        icf_amr_params_st amr_params;
        icf_boolean_t     vbd_val;
} icf_audio_codec_param_st;



/* ICF rel 6.0 Multiple m-lines */
/*--------------------------------------------------------------------------- 
 * Structure Name: icf_video_codec_param_st
 *
 * Description: This datatype is used to define a structure , which specifies 
 * the attributes specific to video codec.  
 *---------------------------------------------------------------------------*/
typedef struct
{

#define	ICF_VIDEO_CODEC_CLOCK_RATE_PRESENT    0x01
#define ICF_VIDEO_CODEC_FRAMESIZE_PRESENT	0x02

icf_uint8_t       bit_mask;

icf_uint32_t   clock_rate;
icf_size_st    frame_size;
}icf_video_codec_param_st;


/* ICF rel 6.0 Multiple m-lines */
/*--------------------------------------------------------------------------- 
 * Structure Name: icf_t38_attrib_param_st
 *
 * Description: This datatype is used to define a structure , which specifies 
 * the attributes specific to T38 codec.  
 *---------------------------------------------------------------------------*/
typedef	icf_config_t38_attrib_param_st	icf_t38_attrib_param_st;



/* ICF rel 6.0 Multiple m-lines */
/*--------------------------------------------------------------------------- 
 * Structure Name: icf_codec_params_ut
 *
 * Description: This datatype is used to define a union, which specifies the 
 * codec attributes.  
 *---------------------------------------------------------------------------*/
union icf_codec_params_ut
{
	icf_audio_codec_param_st  audio_param;
	icf_video_codec_param_st  video_param;
	icf_t38_attrib_param_st   t38_param;
};


/* ICF rel 6.0 Multiple m-lines moved from icf_mm_types.h */
/*--------------------------------------------------------------------------- 
 * Structure Name: icf_codec_attrib_st
 *
 * Description: This data type is used to define a structure, which contains 
 *              Codec attributes configured in the API icf_CFG_CODEC_INFO_REQ. 
 *---------------------------------------------------------------------------*/
typedef struct
{
	icf_uint8_t				bit_mask;
#define ICF_CODEC_ATTRIB_CODEC_NUM_PRESENT	    0x01
#define ICF_CODEC_ATTRIB_CODEC_PARAMS_PRESENT	0x02
#define ICF_CODEC_ENC_ATTRIB_PRESENT            0x04
	icf_uint8_t				codec_num;
	icf_short_string_st		codec_name;

	/* This union has parameters specific to codec */
	union icf_codec_params_ut	codec_params;

	/* Node of this list is of type icf_string_st */
    icf_list_st             *p_encoded_attributes;

/* Some of the example values of icf_codec_attrib_st are:
	Codec Name 		Codecnum	Encoding_Name
	G.711 mu-Law		0		"PCMU"
	G.711 A-Law		8			"PCMA"
	G.722 			9			"G722"
	G.729 			18			"G729"
	Comfort Noise	13			"CNG"
	DTMF			96			"audio/telephone-event"
	T.38			128			"T.38"
*/
} icf_codec_attrib_st;

/* ICF rel 6.0 Multiple m-lines */
/*-----------------------------------------------------------------------------
 * typedef Name: icf_codec_info_st
 * Description:  .
 *----------------------------------------------------------------------------*/
typedef struct
{

	icf_uint8_t				codec_count; /* num of audio/video codecs 
										  *	depending on the stream type */
	icf_short_string_st		codec_name[ICF_MAX_CODECS];
	
}icf_codec_info_st;

/* ICF REL 6.0: multiple m lines */
/*-----------------------------------------------------------------------------
*
* Structure Name: icf_audio_profile_st
*
* Description: 
*---------------------------------------------------------------------------*/
typedef struct
{

	icf_uint8_t				bit_mask; /* bitmask to determine the availablity 
										 * of optional information in the 
										 * structure */
#define ICF_AUDIO_PROF_BNDWDTH_PRESENT		0x01
#define ICF_AUDIO_PROF_PTIME_PRESENT		0x02
#define ICF_AUDIO_PROF_SILN_SUPP_PRESENT	0x04
#define ICF_AUDIO_PROF_ECHO_CANC_PRESENT	0x08
 
	icf_uint16_t			bandwidth;
	icf_uint8_t				pref_ptime;	
 	icf_boolean_t			silence_suppression;
            icf_boolean_t                   echo_canc;	
}icf_audio_profile_st;

/* ICF REL 6.0: multiple m lines */
/*-----------------------------------------------------------------------------
*
* Structure Name: icf_video_profile_st
*
* Description: 
*---------------------------------------------------------------------------*/
typedef struct
{
#define ICF_VIDEO_PROFILE_ENC_QUALITY_PRESENT       0x01
#define	ICF_VIDEO_PROFILE_FRAME_RATE_PRESENT   	    0x02
#define ICF_VIDEO_PROFILE_BANDWIDTH_PRESENT         0x04
	icf_uint8_t  bit_mask;

/* This value should be between 0 and 10 with 0 indicatiing lowest quality
 * and 10 indicating highest quality. If this value is not present
 * Default value of 5 should be taken
 */
	icf_uint8_t    encoding_quality;
    icf_uint8_t    frame_rate;
	icf_uint16_t   bandwidth;
}icf_video_profile_st;

/* ICF REL 6.0: multiple m lines */
/*-----------------------------------------------------------------------------
*
* Structure Name: icf_t_38_media_profile_st
*
* Description:  Dummy structure
*---------------------------------------------------------------------------*/
typedef struct
{
	icf_uint32_t		max_bit_rate;	
}icf_t_38_media_profile_st;

/* ICF REL 6.0: multiple m lines */
/*-----------------------------------------------------------------------------
*
* Structure Name: icf_app_stream_profile_st
*
* Description: 
*---------------------------------------------------------------------------*/
typedef struct
{
	icf_string_st			app_name;
	icf_list_st				*p_encoded_params; /* a list of encoded attribute 
											    * lines for the application */
}icf_app_stream_profile_st;

/* ICF rel 6.0 Multiple m-lines */
/*-----------------------------------------------------------------------------
 * typedef Name: icf_stream_id_list_st
 * Description:  This structure will be used to list the deleted streams to
 * 				 MM. MM neednot know the stream_type, since it has all the 
 * 				 information that is mapped on the stream_id as the index.
 *----------------------------------------------------------------------------*/
typedef struct
{
	icf_uint8_t			count;	
	icf_stream_id_t		stream_id[ICF_MAX_STREAM_PER_CALL];
}icf_stream_id_list_st;

/* ICF rel 6.0 Multiple m-lines */
/*-----------------------------------------------------------------------------
 * typedef Name: icf_stream_list_st
 * Description:  This structure will be used to list the deleted streams to the
 * 				 application.It is necessary to indicate the stream_type also
 * 				 since in the case of an incoming call, the app will not know
 * 				 by the stream_id as to which stream is being deleted by ICF
 * 				 internally.
 *----------------------------------------------------------------------------*/
typedef struct
{
	icf_stream_id_t		stream_id;
	icf_media_type_t	stream_type;
}icf_stream_list_st;

/* ICF REL 6.0: multiple m lines
 * Following are the structures added for the new release */
union icf_media_stream_param_ut
{
	icf_audio_profile_st		audio_profile;
	icf_video_profile_st		video_profile;
} ;


typedef struct 
{
	/* this flag will indicate the available information*/
    icf_uint8_t                 bit_mask;
#define	ICF_SDP_STREAM_RTCP_INFO_PRESENT   	0x01
#define ICF_SDP_STREAM_ENCPARAMS_PRESENT	0x02
#define ICF_SDP_STREAM_MEDIA_STREAM_PRESENT 0x04

	/* Linked list of node of type  icf_codec_attrib_st.
	 * Each node contains codec specific attributes.*/

     icf_list_st				*p_codec_info_list;
	
    /* IP address and port number of the RTP session. Incase of the application
	 * stream, this will store the TBCP IP/Port */
	/* When this structure is used to store the local SDP stream information
	 * this will contain the public IP/port as retrieved from STUN (by MMI).
	 * this information will be used by SSA to populate the outgoing SDP on the
	 * n/w. Incase ICF is not behind the NAT, this address will be the same as
	 * the local IP/port */
    icf_transport_address_st   stream_address;    
    
    /* need to define the media stream protocol can be UDP/TCP/RTP/AVP */
	icf_media_transport_mode_et		trans_mode;

	/* The structure defines stream level parameters */
	union icf_media_stream_param_ut	media_stream_param;

	/* peer RTCP address. This information is optional and will be updated
	 * when the peer's RTCP port/IP is received 
	 */
    icf_transport_address_st    rtcp_address;    

	/* This field is a list of the node type icf_string_st. This field stores
	 * the encoded parameter list for any media stream */
	icf_list_st					*p_encoded_attributes;
} icf_sdp_stream_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_stream_capab_st
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
#define ICF_STREAM_CAPAB_CODEC_INFO_PRESENT             0x01
#define ICF_STREAM_CAPAB_MEDIA_STREAM_PARAM_PRESENT     0x02
#define ICF_STREAM_CAPAB_ENC_ATTRIB_PRESENT             0x04

    icf_uint8_t			bit_mask;

	icf_stream_id_t		stream_id;
	icf_media_type_t 	stream_type;
	/* Linked list of node of type  icf_codec_attrib_st.
	 * Each node contains codec specific attributes.*/
    icf_list_st			*p_codec_info_list;
    union icf_media_stream_param_ut   media_stream_param;
    icf_list_st         *p_encoded_attributes;
    icf_uint8_t         qos_mark;
} icf_stream_capab_st;


typedef struct
{

#define ICF_CALL_MOD_CODEC_INFO_PRESENT         0x01
#define ICF_CALL_MOD_MEDIA_STREAM_PARAM_PRESENT 0x02
#define ICF_CALL_MOD_ENC_ATTRIB_PRESENT         0x04
#define ICF_CALL_MOD_MEDIA_MODE_PRESENT		0x08
	/* This bitmask will be set when remote puts
	 * stream on hold by sending mode as INACTIVE/
	 * SENDONLY or sending c line ip as 0.0.0.0 for
	 * this stream. This bit will be set in multiple 
	 * request till remote changes its mode or send
	 * new c line ip address. If this bit is not set
	 * application should assume that media path with 
	 * remote is set.*/
#define ICF_CALL_MOD_STREAM_ON_REMOTE_HOLD	0x10

	icf_uint8_t				bit_mask;	

	icf_stream_id_t		stream_id;
	icf_media_type_t 	stream_type;
	/* Linked list of node of type  icf_codec_attrib_st.
	 * Each node contains codec specific attributes.*/
    icf_list_st			*p_codec_info_list;
    union icf_media_stream_param_ut   media_stream_param;
    icf_list_st         *p_encoded_attributes;
	icf_media_mode_t	media_mode; /* the app. can change the stream 
										 * mode for an established call */
} icf_call_modify_media_data_st;

/* Start: Addition for Per Line Feature */
#ifdef ICF_SESSION_TIMER
typedef     icf_uint8_t     icf_refresher_type_t;
#endif

typedef struct{
    /*Line id for which the hold option is to be configured*/
    icf_line_id_t      line_id;
    icf_hold_option_t  hold_option;
}icf_hold_option_st;    
/* End: Addition for Per Line Feature */ 


/* A new structure defined for PA validation code */
typedef struct
{
icf_error_t     ecode; /*Specifies the error code*/
icf_uint8_t     err_str[ICF_MAX_STR_LEN]; /*Specifies the error string. Specifies the name of the field due to which failure occurred, with most significant field first with respect to functional nesting separated by colons*/
}icf_vldt_err_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_sdp_info_st
 *
 * Description: This datatype represents a structure that contains stream
 *               information for local.remote offer.answer.
 *
 *---------------------------------------------------------------------------*/
typedef icf_call_modify_media_data_st icf_sdp_info_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_stream_data_st
 *
 * Description: This datatype represents a structure that contains stream
 *               information.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
        icf_stream_id_t                         stream_id;
        icf_media_type_t                        stream_type;

        /* following 2 variables are for codec information of type
         *  icf_codec_attrib_st */
        icf_list_st                             *p_offered_codec;
        icf_codec_attrib_st                     *p_negotiated_codec;

        icf_transport_address_st                local_rtp_address;
        icf_transport_address_st                remote_rtp_address;

} icf_stream_data_st;
/*------------------------------------------------------------------------
 * NAME:                icf_call_connect_data_st
 *
 * Description:         consolidated call related information.
 *
*-------------------------------------------------------------------------*/

typedef struct
{
    icf_address_st                        calling_party_address;
    icf_address_st                        called_party_address;

    icf_line_id_t                         line_id;
    /* SPR 17555:Move the Call Direction hash defines to icf_defs.h
     */
    icf_uint8_t                           call_direction;

        /* following is the linked list of type icf_stream_data_st which
        * has information on per stream basis */
        icf_list_st                     *p_stream_data;
    icf_transport_address_st                local_sip_ip_address;

#define ICF_CALL_TRANSPORT_MODE_UDP       0x01
#define ICF_CALL_TRANSPORT_MODE_TCP       0x02
#define ICF_CALL_TRANSPORT_MODE_TLS       0x04
    icf_uint8_t                           call_transport_mode;
    /* this will be true when its QOS precondition call */
    icf_boolean_t               qos_call;
} icf_call_connect_data_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_time_stamp_st
 *
 * Description: This datatype represents a structure that contains timestamp information.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    icf_uint32_t         time_in_secs;
    icf_uint32_t         time_in_millisecs;

} icf_time_stamp_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_user_reg_status_st
 *
 * Description: This structure is used to keep the registration status
 *              corresponding to the user.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{

        icf_address_st                       user;
/* State type starts */

/* This is the initial state of a user before registration request is sent */   
#define ICF_RGM_00_IDLE                  0
/* This is the state when register request is sent on network and response is 
 * awaited for register request
 */
#define ICF_RGM_01_REGISTERING           1
/* This is the state when register request fails */
#define ICF_RGM_02_UNREGISTERED          2
/* This is the state when user is successfully registered with registrar */
#define ICF_RGM_03_REGISTERED            3
/* This is the state when registration request with authentication information
 * is sent on network and response for it is awaited
 */
#define ICF_RGM_04_AUTHORIZING           4
/* This is the state when deregistration request is sent on network and its
 *  response is awaited
 */    
#define ICF_RGM_05_DEREGISTERING         5

/* This is the state in which the ICF send authentication failure to the application 
 *   and the response from the application is awaited
 */
#define ICF_RGM_06_AWT_AUTH_RESP         6

/* State type Ends */
        icf_status_t                         reg_status;

} icf_user_reg_status_st;


/*----------------------------------------------------------------------------
 *
 * icf_prack_values_et  - This data type is used to define value of prack_type
 *                        that cal ne used in ICF_CREATE_CALL_REQ api and 
 *                        ICF_MEDIA_CONNECT_REQ/ICF_LOCAL_USER_ALERTED_REQ 
 *                        Api
 *--------------------------------------------------------------------------*/

typedef enum
{
    ICF_NO_PRACK,
    ICF_PRACK_IN_SUPPORTED,
    ICF_PRACK_IN_REQUIRE,
    ICF_PRACK_INVALID_VALUE
}icf_prack_values_et;



#ifdef ICF_UT_TEST

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_func_fail_st
 *
 * Description: This structure is used to get the function name and the count
 *		at which function has to return failure.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
	icf_string_st			func_name;
	/* on which call func has to return failure */
	icf_uint16_t			count; 
        /* to return failure with given err */
	icf_error_t			ecode;
        /* Function level/Encapsulating function Name */  
        icf_string_st                   func_level_name;
}icf_func_fail_st;

#endif


#ifdef __cplusplus

}

#endif /* __cplusplus */

#endif /*__ICF_TYPES_H__*/

