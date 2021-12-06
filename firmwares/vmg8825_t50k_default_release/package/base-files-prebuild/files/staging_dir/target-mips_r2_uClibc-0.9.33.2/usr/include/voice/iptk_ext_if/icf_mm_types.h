/******************************************************************************

*                                    

* FILE NAME    :icf_mm_types.h                

*                                    

* DESCRIPTION  : Interface Data types for icf_mm_api.h  

*                

*                                    

* Revision History :                            

*    DATE            NAME           REFERENCE       REASON

* --------      ------------        ----------   ---------------

* 28-JULY-2005   Ashutos Rath           -		Created Origional
* 04-AUG-2005	Rohit Aggarwal					Added ICF-MM defs
* 08-Feb-2006	Puneet Sharma					Added ICF-MM defs for ICF 4.3
* 22-Jun-2006   Deepti Goyal                    Added ICF-MM_AL defs    
* 08-Oct-2009   Rajiv Kumar         SPR:20106   Fix for SPR:20106
* 
* Copyright 2009,Aricent.                   
*                                    
******************************************************************************/



#ifndef __ICF_MM_TYPES_H__

#define __ICF_MM_TYPES_H__









/* Determine if a C++ compiler is being used.

 * If so, ensure that standard

 * C is used to process the API information.

 */
#include "icf_types.h"

#ifdef __cplusplus



/* Yes, C++ compiler is present.

 * Use standard C.

 */



extern "C"

{

#endif /* __cplusplus */


#define ICF_MAX_TONES		                20 


/*-----------------------------------------------------------------------------

 *

 * Structure Name: icf_file_name_st

 *

 * Description: This data type represents a structure, which consists of a

 *              character array of specified length for file names and path.

 *

 *---------------------------------------------------------------------------*/



typedef struct

{

   

    /* specifies the length of the string including '\0' character */

    icf_uint16_t  str_len;

   

    /* array of characters */

    icf_uint8_t  str[ICF_MAX_LONG_STR_LEN];

   

} icf_file_name_st;









typedef  icf_uint16_t icf_ringer_id_t;



/*-----------------------------------------------------------------------------

 * 

 * Structure Name: icf_ringer_id_st

 *

 * Description: This data type is used to define a structure, which contains 

 *              mapping for ringer and its play file reported in the API 

 *              icf_CFG_RINGER_TONES_REQ

 * 

 *---------------------------------------------------------------------------*/



typedef struct

{
    /* Denotes the id of ringer tone */
    icf_ringer_id_t   ringer_id;     

    /* Denotes the play out file for the corresponding tone. */
    icf_file_name_st  play_file;
} icf_ringer_id_st;






/*-----------------------------------------------------------------------------

 *

 * Structure Name: icf_rtcp_report_st

 *

 * Description: It specifies the RTCP statistics structure.

 *

 *---------------------------------------------------------------------------*/



typedef struct

{
    /* It is the timestamp of the readings taken. */
    icf_uint32_t   time_stamp;

    /* Denotes the number of packets sent.*/
    icf_uint32_t   num_packet_send;

    /* Denotes the number of octets sent.*/
    icf_uint32_t   num_octet_send;

	/* Denotes the number packets recv. */ 
    icf_uint32_t   num_packet_rcvd;

    /* Denotes the number octets received. */
    icf_uint32_t   num_octet_rcvd;

    /* Denotes the cumulative packet loss. */
    icf_uint32_t   cum_packet_loss;

} icf_rtcp_report_st;









/*-----------------------------------------------------------------------------

 *

 * Structure Name: icf_play_output_t

 *

 * Description: This is to define device to be used for media play-out.

 *

 *---------------------------------------------------------------------------*/

#define  ICF_HEADSET                    1

#define  ICF_SPEAKER                      2

#define  ICF_BOTH_HEADSET_SPEAKER       3



typedef icf_uint8_t icf_play_output_t;




/*-----------------------------------------------------------------------------

 *

 * Structure Name: icf_app_data_st;

 *

 * Description:  This is used to define the app data for RTCP.

 *                

 *---------------------------------------------------------------------------*/

typedef struct

{

  

    /* specifies the length of the app_data(str) buffer */

    icf_uint16_t  str_len;


	/* Specifies the subtype to allow a set of APP packets to be 
     * defined under one unique name  (0-31)*/
    icf_uint8_t   sub_type;
        
    /* name chosen by the application defining the set of APP packets 
     * to be unique with respect to other APP packets for this application */
#define ICF_MAX_APP_NAME_LEN 4
    icf_uint8_t   app_name[ICF_MAX_APP_NAME_LEN];

    /* app data buffer */

    icf_uint8_t   str[ICF_MAX_APP_DATA_LEN];



} icf_app_data_st;





/*-----------------------------------------------------------------------

 * NAME : icf_report_type_t

 *        used to define the type of RTCP statistics report.

 *-----------------------------------------------------------------------*/

 

/* Denotes statistics for sender only. */

#define ICF_SENDER_ONLY                       0



/* Denotes statistics for receiver only. */

#define ICF_RECEIVER_ONLY                     1



/* Denotes statistics for both sender and receiver.*/

#define ICF_BOTHWAY_REPORTS                   2 



typedef icf_uint8_t icf_report_type_t;



/*-----------------------------------------------------------------------

 * NAME : icf_interval_type_t

 *        used to define the interval type to report back RTCP stats.

 *-----------------------------------------------------------------------*/

typedef icf_uint8_t icf_interval_type_t;





/*-----------------------------------------------------------------------------

 *

 * Structure Name: icf_play_duration_t

 *

 * Description: This data type is used to define type of duration. 

 *

 *---------------------------------------------------------------------------*/

#define  ICF_PLAY_INDEFINITE    1

#define  ICF_PLAY_FILE_LEN      2

#define  ICF_PLAY_TIMER_VAL     3



typedef icf_uint8_t icf_play_duration_t;







/*-----------------------------------------------------------------------------
*
* icf_codec_t values
*
-----------------------------------------------------------------------------*/

/*#define ICF_CODEC_UNDEFINED     255   Undefined */


/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_codec_t
 * 
 * Description:  This is used to define the identifier for a codec.
 *                                         
 *---------------------------------------------------------------------------*/

typedef icf_uint8_t icf_codec_t;


#ifdef ICF_QOS_SUPPORT
/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_qos_st
 *
 * Description: This data type is used to define a structure, which contains the
 *              Qos parameters for a particular direction.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{   
    /* Following are the values taken by current_status */
#define ICF_RESOURCE_NOT_RESERVED              0
#define ICF_RESOURCE_RESERVED                  1
    icf_uint8_t current_status;
    
    /* Following are the values taken by desired status */
#define ICF_RESOURCE_RESERVATION_MANDATORY     1
#define ICF_RESOURCE_RESERVATION_OPTIONAL      2
#define ICF_RESOURCE_RESERVATION_NONE          3
#define ICF_RESOURCE_RESERVATION_FAILURE       4
#define ICF_RESOURCE_RESERVATION_UNKNOWN       5
    icf_uint8_t desired_status;

    /* Following are the values taken by confirmed status */
#define ICF_RESOURCE_RESERVATION_CONF_NOT_REQ  0
#define ICF_RESOURCE_RESERVATION_CONF_REQ      1
    icf_uint8_t confirmation_status;
    
}icf_qos_st;

/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_local_qos_st
 *
 * Description: This data type is used to define a structure, which contains the
 *              Qos parameters in the local send/recv direction.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{   
    /* Following are the values taken by current_status */
#define ICF_RESOURCE_NOT_RESERVED              0
#define ICF_RESOURCE_RESERVED                  1
    icf_uint8_t current_status;
    
    /* Following are the values taken by desired status */
#define ICF_RESOURCE_RESERVATION_MANDATORY     1
#define ICF_RESOURCE_RESERVATION_OPTIONAL      2
#define ICF_RESOURCE_RESERVATION_NONE          3
#define ICF_RESOURCE_RESERVATION_FAILURE       4
#define ICF_RESOURCE_RESERVATION_UNKNOWN       5
    icf_uint8_t desired_status;
   
}icf_local_qos_st;

#endif


/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_req_stream_st
 *
 * Description: Denotes Media Stream and its associated parameters.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
	
	/* ICF rel 6.0 Multiple m-lines For optional elements */
	
#define ICF_CREATE_MEDIA_REMOTE_SDP_PRESENT				0x01
#define ICF_CREATE_MEDIA_LOCAL_MEDIA_PROFILE_PRESENT	0x02
#define ICF_CREATE_MEDIA_STREAM_MODE_PRESENT			0x04
#define ICF_CREATE_MEDIA_QOS_PARAMS_PRESENT				0x08
#define ICF_CREATE_MEDIA_RTP_DETECTION_PRESENT			0x10
#define ICF_CREATE_MEDIA_ECHO_CAN_PRESENT		        0x20	

    icf_uint16_t		bit_mask;

	icf_stream_id_t		stream_id;

	icf_media_type_t	stream_type;

	icf_sdp_stream_st	remote_sdp;

	icf_sdp_stream_st	local_sdp;

	icf_media_mode_t	mode;

    /*
     * QoS mark to indicate the value to be filled in ToS field
     * in RTP packets
     */
    icf_qos_mark_t      qos_mark;

    /*
     * If true means that MM APP is intereseted in indication from Media Manager 
     * when first RTP packet is received in this RTP session or first RTP packet 
     * is detected after some idle duration.
     */
    icf_boolean_t	rtp_detection_reqd;
    /* Echo cancellation enable/disable for the specified stream */
	icf_boolean_t	      echo_cancellation;

} icf_req_stream_st;



/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_resp_stream_st
 *
 * Description: Contains the media stream parameters returned in response for 
                each stream specified in request.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{


	
	/* ICF rel 6.0 Multiple m-lines */
	icf_stream_id_t		stream_id;

	icf_media_type_t	stream_type;

	/* Contains the local session description parameters such as codec list and 
	 * packetization period for audio/video calls. */
	icf_sdp_stream_st	local_sdp;

} icf_resp_stream_st;


/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_modify_stream_st
 *
 * Description: Denotes Media Stream and its associated parameters.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
 

#define ICF_MODIFY_LOCAL_SDP_STREAM_PRESENT	  0x01
#define ICF_MODIFY_REMOTE_SDP_STREAM_PRESENT  0x02
#define ICF_MODIFY_MEDIA_MODE_PRESENT		  0x04
#define ICF_MODIFY_MEDIA_ECHO_CAN_PRESENT	  0x08
	icf_uint8_t			bit_mask;

	icf_stream_id_t		stream_id;
	icf_media_type_t	stream_type;
	icf_sdp_stream_st	sdp_stream;
	icf_media_mode_t	mode;
    icf_boolean_t	    echo_cancellation;
} icf_modify_stream_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_play_mode_t
 *
 * Description: This data type is used to define play mode. 
 *
 *---------------------------------------------------------------------------*/
#define  ICF_PLAY_LOCAL     1
#define  ICF_PLAY_NW        2
#define  ICF_PLAY_BOTH      3

typedef icf_uint8_t icf_play_mode_t;

/* ICF rel 6.0 Multiple m-lines */
/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_media_id_t
 *
 * Description: 
 * 
 *---------------------------------------------------------------------------*/

typedef icf_uint16_t icf_media_id_t;


/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_line_id_t
 * 
 * Description: This is used to define a data type , whose value uniquely 
 *              identifies a subscriber line.
 *
 *---------------------------------------------------------------------------*/

/* typedef icf_uint8_t icf_line_id_t;*/


 /*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_media_mode_t
 *
 * Description: This is used to define a data type whose value specifies 
 * 	          the direction of an RTP session
 * 
 *---------------------------------------------------------------------------*/

/* typedef icf_uint8_t icf_media_mode_t;*/

 /* Below Values will be used for icf_media_mode_t */

 /* media mode value is invalid */
#define  ICF_MEDIA_MODE_INVALID           0
    /* mode for media session is inactive */
#define  ICF_MEDIA_MODE_INACTIVE          1
    /* mode for media session is send only */
#define  ICF_MEDIA_MODE_SEND_ONLY         2
    /* mode for media session is receive only */
#define  ICF_MEDIA_MODE_RECV_ONLY         3
    /* mode for media session is send-receive */
#define  ICF_MEDIA_MODE_SEND_RECV         4


/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_qos_mark_t
 * Description:  This is used to define a datatype, whose value indicates 
 *               the type of service indicator in the RTP payload for the call. 
 * 
 * Values :      If it is set to ICF_QOS_MARK_NONE, it indicates that the QoS 
 *               is not to be set in the RTP payload. 
 *               
 *               If it is set to ICF_QOS_MARK_TOS_AUDIO, it indicates that it 
 *               is an audio call in the Type of Service (ToS) parameter of the
 *               RTP payload. 
 *
 *----------------------------------------------------------------------------*/
 
#define ICF_QOS_MARK_NONE		0
#define ICF_QOS_MARK_AUDIO		1

/*typedef icf_uint8_t icf_qos_mark_t;*/
/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_dgt_t
 *
 * Description:  This datatype define a data value of 
 *               icf_uint8_t type, which is used to define the type of tone.
 * Values :      
 *
 *----------------------------------------------------------------------------*/
#define ICF_DGT_0               0
#define ICF_DGT_1               1
#define ICF_DGT_2               2
#define ICF_DGT_3               3
#define ICF_DGT_4               4
#define ICF_DGT_5               5
#define ICF_DGT_6               6
#define ICF_DGT_7               7
#define ICF_DGT_8               8
#define ICF_DGT_9               9
#define ICF_DGT_HASH            10
#define ICF_DGT_STAR            11
#define ICF_DGT_HOOK_FLASH      12

typedef icf_uint8_t  icf_dgt_t;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_dgts_st
 *
 * Description: This datatype is used to define a 
 *              structure, which specifies the inband digits to be passed.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
 
    /* Denotes the number of inband digits present in message.*/
    icf_uint8_t      number_of_dgts;

    /* Presents the actual digits.*/
    icf_dgt_t       dgts[ICF_MAX_DGT_LEN];
   
} icf_dgts_st;

/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_file_typ_t
 *
 * Description:  This datatype define a data value of 
 *               icf_uint8_t type, which is used to define the type of file.
 * Values :      
 *
 *----------------------------------------------------------------------------*/
#define ICF_FILE_TYPE_WAV          1
typedef icf_uint8_t  icf_file_typ_t;


/* ICF rel 6.0 Multiple m-lines */
/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_media_src_t
 *
 * Description:  This datatype define a data value of icf_uint8_t type, which is 
 * used to define the media source recording
 * Values :      
 *
 *----------------------------------------------------------------------------*/
/* Denotes voice source as Microphone.*/
#define     ICF_MIC	                0
/* Denotes voice source as network connection attached to speaker. */	
#define     ICF_NW_MEDIA_SESSION	1

#define		ICF_CAMERA				2

typedef icf_uint8_t  icf_media_src_t;


/*-----------------------------------------------------------------------------
 * 
 * typedef Name: icf_trans_method_t
 *
 * Description:  This datatype define a data value of 
 *               icf_uint8_t type, which is used to define the type of 
 *               transport method to send the inband digits.
 * Values :      
 *
 *----------------------------------------------------------------------------*/
/* Denotes inband digits to passed as per RFC 2833*/
#define     ICF_RFC_2833	                1
/* Denotes digits to be passed as inband tones. */	
#define     ICF_INBAND_TONE	                2	

typedef icf_uint8_t  icf_trans_method_t;

typedef icf_uint16_t  icf_vibra_id_t;



/* ICF rel 6.0 Multiple m-lines */
/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_codec_id_st
 *
 * Description: This structure is used to identify codec by ICF.
 *              One of field codec_name of codec_id must be present in this strucuture.   
 *
 *---------------------------------------------------------------------------*/

typedef struct 
{
#define ICF_CODEC_ID_CODEC_NAME_PRESENT   0x01
#define ICF_CODEC_ID_CODEC_ID_PRESENT     0x02

    icf_uint8_t         bit_mask;
	icf_short_string_st	codec_name;
	icf_uint8_t         codec_id;
}icf_codec_id_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_codec_id_st
 *
 * Description: This strucuture is used by MM to fill commit
 *                response for a stream
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
	icf_stream_id_t		stream_id;
	icf_uint8_t			codec_count;
	icf_codec_id_st   	codec[ICF_MAX_CODECS];

} icf_stream_commit_st;


/* ICF rel 6.0 Multiple m-lines */
/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_stream_port_range_st
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
	icf_media_type_t	  stream_type;
    icf_uint16_t          stream_recv_start_port;
    icf_uint16_t          stream_recv_end_port; 
} icf_stream_port_range_st;



/*--------------------------------------------------------------------------- 
 * Structure Name: icf_stream_map_info_st
 *
 * Description:  This structure will contain the local ports allocated for the 
 *               stream id's. 
 *---------------------------------------------------------------------------*/

typedef struct
{

    icf_call_id_t	    call_id;
    icf_stream_id_t		stream_id;
    icf_media_type_t	stream_type;
    icf_uint16_t        port_num;

}icf_stream_map_info_st;

/* ICF rel 6.0 Multiple m-lines */
/*--------------------------------------------------------------------------- 
 * Structure Name: icf_merge_stream_id_st
 *
 * Description:   Stream ids to be merged
 *---------------------------------------------------------------------------*/
typedef struct 
{
icf_uint16_t   stream_id;
icf_uint16_t   merge_stream_id;
} icf_merge_stream_id_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_windows_handle_st
 *
 * Description: This structure specifile the windows handle for MS Window
 *              platform
 *---------------------------------------------------------------------------*/
typedef	struct {
	icf_string_st			window_class_name;
							/*Specifies the class name of the window
							*in which video is to be displayed*/
	icf_string_st			window_title;
							/*Specifies the title of the window
							*in which video is to be displayed*/
} icf_windows_handle_st;
/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_platform_type_t
 *
 * Description: This typdef specifile various platform types
 *              
 *---------------------------------------------------------------------------*/
typedef icf_uint8_t icf_platform_type_t;
/* Below values will be used to specify the platform type*/

/* Platform type for Microsoft windows,WinMobile,WinCE */
#define	ICF_MS_WINDOWS_PLATFORM		1	
/* Platform type for symbian */
#define	ICF_SYMBIAN_PLATFORM		2

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_window_info_st
 *
 * Description: This structure specifile the windows information for MS Window
 *              and Symbian platform
 *---------------------------------------------------------------------------*/
typedef struct {

	union {

		icf_windows_handle_st	ms_windows_handle;
					/*Specifies the window information for 
					 *ICF_MS_WINDOWS_PLATFORM*/
		icf_uint32_t		    handle_id;
					/*Specifies the unique 32bit reference to 
					* display window on the screen for
					* ICF_SYMBIAN_PLATFORM*/
	}handle;
	icf_platform_type_t		platform;
				/*Specifies the platform type */

} icf_window_info_st;

#ifdef __cplusplus

}

#endif /* __cplusplus */

#endif /*__ICF_MM_TYPES_H__*/

