/******************************************************************************

*                                    

* FILE NAME    : icf_mm_api.h            

*                                    

* DESCRIPTION  : This files contains the User APIs for Media Manager    

*                                    

* Revision History :                            

*    DATE            NAME      REFERENCE       REASON

* --------      ------------   ----------   ---------------

* 

* 29-JULY-2005  Ashutos Rath     -			Create Original
* 04-AUG-2005	Rohit Aggarwal				Added ICF-MM APIs
* 08-Feb-2006	Puneet Sharma				Added ICF-MM API's for ICF4.3
*                                
* 22-Jun-2006   Deepti Goyal                Added ICF-MM_AL API's.
* 03-Jan-2007   Amit Mahajan                Line ID added in Media Manager APIs
* 06-Feb-2009   Tarun Gupta   Rel 8.1 LLD   SDP Tunnelling Enhancements
* 14-Apr-2009   Tarun Gupta   SPR 19435     Modified
*                                           icf_tunnelled_modify_media_session_resp_st,
*                                           icf_tunnelled_create_media_session_resp_st
*
* Copyright 2009,Aricent.
*
*******************************************************************************/





#ifndef __ICF_MM_API_H__

#define __ICF_MM_API_H__



#include "icf_defs.h"

#include "icf_types.h"

#include "icf_mm_types.h"
#include "icf_mm_defs.h"
#include "icf_tunnelled_media.h"

/*#include "icf_mm_api.h"*/



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




/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_msg_resp_st
 *
 * Description: This is a common structure used to return back the response of 
 *              _req APIs.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* result,error_cause and bit_mask are mandatory parameters.*/
    /* Success or failure */
    icf_result_t       result;
    /* Error code when the result is failure */
    icf_error_t        error_cause;

    /* bit_mask field will be used to check whether Line Id is present 
     * in the message resp or not.*/
    icf_uint8_t        bit_mask;   
#define   ICF_MSG_RESP_LINE_ID_PRESENT      0x01   
/*ZYXEL porting Amber 20190423*/
#if ZYXEL_SIP_HDR_FOR_AFTER_CALL_RTP_STATS_SEND_IN_BYE_AND_200OK
#define   ICF_MSG_RESP_RTP_STATISTICS_PRESENT      0x02
#endif
/*ZYXEL porting Amber 20190423*/

    icf_line_id_t      line_id;

/*ZYXEL porting Amber 20190423*/
#if ZYXEL_SIP_HDR_FOR_AFTER_CALL_RTP_STATS_SEND_IN_BYE_AND_200OK
    icf_large_string_st    rtpStatsData;
#endif
/*ZYXEL porting Amber 20190423*/
} icf_msg_resp_st;



/**************************************************************************

*     Configuration - Media Manager APIs
**************************************************************************/




/*----------------------------------------------------------------------------

 * NAME : icf_cfg_codec_info_req_st

 *

 * Description: This structure is used to specifies payload data of

 *               API ICF_CFG_CODEC_INFO_REQ 

 *

 *---------------------------------------------------------------------------*/

typedef struct 

{
	/* Denotes the number of codecs present in message */
	icf_uint8_t					count;

	/* Presents the individual codec with their attributes */
	icf_config_codec_attrib_st	codec_supp [ICF_MAX_CODEC_SUPPORTD];
#if 1 /*ZyXEL porting*/
	/* indicates the line id for which this ringing request is.*/
	icf_line_id_t          line_id;
#endif

} icf_cfg_codec_info_req_st;



/*-----------------------------------------------------------------------------

 *

 * Structure Name: icf_cfg_ringer_tones_req_st 

 *

 * Description: This structure is used to specifies payload data of

 *               API ICF_CFG_RINGER_TONES_REQ 

 *

 *---------------------------------------------------------------------------*/

typedef struct 

{

    icf_uint16_t             num_of_ringer;



    icf_ringer_id_st         ringer[ICF_MAX_RINGER_LIST];


} icf_cfg_ringer_tones_req_st;









/*-----------------------------------------------------------------------------

 *

 * Structure Name: icf_cfg_jbm_mgmt_req_st

 *

 * Description: This structure specifies payload data of Jitter Buffer Management

 *              API ICF_CFG_JBM_MGMT_REQ

 *

 *---------------------------------------------------------------------------*/

typedef struct

{

/* Use the following values for jbm_type */

#define ICF_JBM_TYPE_ADAPTIVE       0x00
#define ICF_JBM_TYPE_FIXED          0x01

     icf_boolean_t            jbm_type;

     icf_uint8_t            jbm_scaling_factor;    
     icf_uint16_t            jbm_initial_size;
     icf_uint16_t            jbm_max_size;
     icf_uint16_t            jbm_min_size;



} icf_cfg_jbm_mgmt_req_st;





/*-----------------------------------------------------------------------------

 *

 * Structure Name: icf_cfg_max_earp_vol_req_st 

 *

 * Description: This structure specifies payload data of earphone volume

 *              API ICF_CFG_MAX_EARP_VOL_REQ 

 *

 *---------------------------------------------------------------------------*/

typedef struct 

{
   icf_uint16_t           max_earp_volume;
} icf_cfg_max_earp_vol_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_cfg_max_speaker_vol_req_st
 *
 * Description: This structure is used as payload of speaker volume API 
 *              ICF_CFG_MAX_SPEAKER_VOL_REQ.
 *
 *---------------------------------------------------------------------------*/



typedef struct

{

     

      icf_uint16_t           max_speaker_volume;

} icf_cfg_max_speaker_vol_req_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_cfg_max_mic_gain_req_st
 *
 * Description: This structure is used as payload of API 
 *              ICF_CFG_MAX_MIC_GAIN_REQ.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
	icf_uint16_t             max_mic_gain;
	
} icf_cfg_max_mic_gain_req_st;



/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_cfg_set_port_range_req_st
 *
 * Description: This structure is used as payload of RTP Port config API
 *              ICF_CFG_PORT_RANGE_REQ.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    icf_uint16_t          start_rtp_port;

    icf_uint16_t          end_rtp_port; 

#if 1 /*ZyXEL porting*/
	/* Parameters are TR104 defined*/
      icf_uint16_t            rtcp_enable;

      icf_uint16_t            rtcp_tx_interval; 

      icf_uint8_t            local_cname[64+1];
#endif
#if 1 /*SRTP_SUPPORT*/
	  icf_line_id_t 	SipAccountId;
	  icf_uint8_t	srtp_enable;
	  icf_uint16_t 	srtp_encryption_key_size;
	  icf_uint8_t	srtp_crypto_suite_name[64+1];
#endif
#if 1 /*ZyXEL porting*/
	//Use Same port in T.38 FAX stream type 2016.01.26 Steve.
	icf_uint8_t rtp_T38_FAX_stream_type_use_same_port;
#endif 

	 /* if the app port is multiplexed with the rtcp port, then the 
	  * app port and the rtcp port shall be rtp port + 1. range for rtp port
	  * is will be as defined by the application
	  */
      icf_boolean_t            is_app_rtcp_port_mux;

    /* This field bitwise contains the presence information of optional
     * fields in this structure */

      icf_uint32_t              bit_mask;
	  /* if the application port is not multiplexed with the rtcp port, we need
	   * to define the app port range as is done for the audio ports
	   */
#define ICF_APP_PORT_RANGE_PRESENT		0x01
#if 1 /*SRTP_SUPPORT*/
#define ICF_APP_SRTP_PARAM_PRESENT		0x02
#endif
      icf_uint16_t             start_app_port;
  
      icf_uint16_t             end_app_port;

} icf_cfg_set_port_range_req_st;


/*----------------------------------------------------------------------------
 * 
 * Structure Name : icf_set_mic_gain_req_st
 *
 * Description: This structure is used to specifies payload data of
 *               API ICF_SET_MIC_GAIN_REQ
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
        icf_uint16_t           gain_level;

} icf_set_mic_gain_req_st;




/* ICF rel 6.0 Multiple m-lines */
/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_media_id_st
 *
 * Description: This datatype is used to define a structure, which specifies the 
 * ringer tones and their ids 
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
    icf_media_id_t		media_id;
    icf_file_name_st	play_file;

} icf_media_id_st;
	
/* ICF rel 6.0 Multiple m-lines */
/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_cfg_media_req_st
 *
 * Description: This structure is used to specifies payload data of 
 *               API ICF_CFG_MEDIA_REQ 
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
    icf_uint16_t	     count;

    icf_media_id_st      media[ICF_MAX_MEDIA];

} icf_cfg_media_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_cfg_set_digit_trans_req_st
 *
 * Description: This structure is used to specifies payload data of 
 *               API ICF_CFG_SET_DIGIT_TRANS_REQ 
 *
 *---------------------------------------------------------------------------*/

typedef struct 
{

    icf_trans_method_t        dgt_trns_method;

} icf_cfg_set_digit_trans_req_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_cfg_set_self_ip_req_st
 *
 * Description: This structure is used as payload of API
 *              ICF_CFG_SET_SELF_IP_REQ.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{

      icf_address_st		self_ip_addr;
//Ssu-Ying, support Multiple Profile
      icf_line_id_t 	SipAccountId;

} icf_cfg_set_self_ip_req_st;


/* ICF rel 6.0 Multiple m-lines */

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_video_display_st
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
	/* Information of the window, a unique reference to display window on the screen */
	icf_window_info_st		window_info;
	/* Starting row for the display of the received video data */
    icf_uint16_t	    top;

	/* Starting column for the display of the received video data */
	icf_uint16_t		left;

	/* Width of the display window for the received video data, in number of pixels */
	icf_uint16_t		width;
	
	/* Height of the display window for the received video data, in number of pixels */
	icf_uint16_t		height;
} icf_video_display_st;


/* ICF rel 6.0 Multiple m-lines */
/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_cfg_set_remote_video_display_st
 *
 * Description: This structure is used to specifies payload data of 
 *               API ICF_CFG_SET_REMOTE_VIDEO_DISPLAY_REQ 
 *
 *---------------------------------------------------------------------------*/
typedef	icf_video_display_st	icf_cfg_set_remote_video_display_st;

/* ICF rel 6.0 Multiple m-lines */
/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_cfg_set_preview_video_display_st
 *
 * Description: This structure is used to specifies payload data of 
 *               API ICF_CFG_SET_PREVIEW_VIDEO_DISPLAY_REQ 
 *
 *---------------------------------------------------------------------------*/
typedef	icf_video_display_st	icf_cfg_set_preview_video_display_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name:icf_cfg_set_video_attrib_st
 *
 * Description: Used in API ICF_CFG_SET_VIDEO_ATTRIB_REQ to set video display attributes
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
	/* Information of the window, a unique reference to display window on the screen */
	icf_window_info_st		window_info;

	/* It is the attribute name for which the value is configured */
#define	ICF_SET_VIDEO_ATTRIB_BRIGHTNESS	 0x01
#define	ICF_SET_VIDEO_ATTRIB_CONTRAST	 0x02  
#define	ICF_SET_VIDEO_ATTRIB_SATURATION  0x04 
#define	ICF_SET_VIDEO_ATTRIB_SCALE		 0x08
	icf_uint8_t			attrib_name;
	
	/*Here the value corresponds to the attribute name:
		Brightness : 0 to 100 
		Contrast :	 0 to 100
		Saturation : -100 to +100
		Scaling :	 -4 to +4 (here -(minus) means the decreasing scale 
							and + means the increasing scale, 
							e.g. -4 means ? -2 means ? */
	icf_int32_t			attrib_value;

} icf_cfg_set_video_attrib_st;



/************************************************************************

 *          Common Application APIs 

 ************************************************************************/



/*----------------------------------------------------------------------------

 * NAME : icf_start_ringing_req_st

 *

 * Description: This structure is used to specifies payload data of

 *               API ICF_START_RINGING_REQ

 *

 *---------------------------------------------------------------------------*/

typedef struct

{



    icf_ringer_id_t        ringer_id;



    icf_play_duration_t       duration;

    /* This field bitwise contains the presence information of optional

     * fields in this structure */

    icf_uint32_t               bit_mask;

    #define ICF_RINGING_TIMER_VAL  0x01
    #define ICF_RINGING_LINE_ID_PRESENT     0x02 

    icf_uint16_t           timer_value;

    /* indicates the line id for which this ringing request is.*/
    icf_line_id_t          line_id; 


} icf_start_ringing_req_st;


/*----------------------------------------------------------------------------

 * NAME : icf_vibration_req_st

 *

 * Description: This structure is used to specifies payload data of

 *               API ICF_VIBRATION_REQ

 *

 *---------------------------------------------------------------------------*/

typedef struct

{
    icf_vibra_id_t        vibration_id;

    icf_duration_t       duration;

    /* This field bitwise contains the presence information of optional

     * fields in this structure */

    icf_uint32_t               bit_mask;

    #define ICF_VIBRATION_TIMER_VAL  0x01

    icf_uint16_t           timer_value;

} icf_vibration_req_st;




/* ICF rel 6.0 Multiple m-lines */
/*----------------------------------------------------------------------------
 * NAME : icf_connect_media_device_req_st
 *
 * Description: This structure is used to specifies payload data of
 *               API ICF_CONNECT_MEDIA_DEVICE_REQ
 *
 *---------------------------------------------------------------------------*/

typedef struct

{
	/* This enumeration will define the media device to be attached for the call */
#define ICF_DEVICE_TYPE_MIC				0x01
#define ICF_DEVICE_TYPE_SPKR			0x02
#define ICF_DEVICE_TYPE_VIDEO			0x04
#define	ICF_DEVICE_TYPE_CAMERA			0x08

	icf_uint32_t	media_device;

	/* This enumeration will define whether a device will be attached for the call 
	 * or whether the device shall be detached with this request. */
#define ICF_MEDIA_DEVICE_STAT_CONNECT		0x01
#define ICF_MEDIA_DEVICE_STAT_DISCONNECT	0x02
	icf_uint32_t	connect_status;

        /*This is a mandatory parameter.Following bit_mask will be 
         indicating presence of optional parameters.*/
        icf_uint8_t     bit_mask;
#define   ICF_LINE_ID_PRESENT           0x01

        icf_line_id_t   line_id;
} icf_connect_media_device_req_st;

/*----------------------------------------------------------------------------
 * NAME : icf_echo_canc_req_st
 *
 * Description: This structure is used to specifies payload data of
 *               API ICF_ECHO_CANC_REQ
 *
 *---------------------------------------------------------------------------*/
typedef struct
{

    icf_boolean_t             echo_cancel;

    /* This field bitwise contains the presence information of optional
     * fields in this structure */

#define ICF_ECHO_CANC_STREAM_ID     0x01

    icf_uint32_t               bit_mask;

    icf_stream_id_t            stream_id;

} icf_echo_canc_req_st;


/*----------------------------------------------------------------------------
 * NAME : icf_vad_ss_cng_req_st
 *
 * Description: This structure is used to specifies payload data of
 *               API ICF_VAD_SS_CNG_REQ
 *
 *---------------------------------------------------------------------------*/
typedef struct
{

    /* This field bitwise contains the presence information of optional
     * fields in this structure */

#define ICF_VAD_STREAM_ID     	0x01
#define ICF_VAD_SUPP    	0x02
#define ICF_VAD_SILENCE_SUPP    0x04
#define ICF_VAD_COMFORT_NOISE   0x08

    icf_uint32_t               bit_mask;

    icf_stream_id_t            stream_id;

    icf_boolean_t              vad_supp;

    icf_boolean_t              silence_supp;

    icf_boolean_t              comfort_noise;

} icf_vad_ss_cng_req_st;




/*----------------------------------------------------------------------------

 * NAME : icf_get_stats_req_st

 *

 * Description: This structure is used to specifies payload data of

 *               API ICF_GET_STATS_REQ

 *

 *---------------------------------------------------------------------------*/

typedef struct

{
        /* denotes the stream id audio/video/tbcp */
        icf_stream_id_t          stream_id;

        /* This denotes the statistics type that application 
		 * requires to report by the MM module. 
		 */
        icf_report_type_t         stats_type;

        /* It indicates type of reporting - instantaneous 
		 * (cumulative statistics on this media channel), 
		 * or as and when it is received.
		 */
        icf_interval_type_t       interval_type;

} icf_get_stats_req_st;





/*----------------------------------------------------------------------------

 * NAME : icf_get_stats_resp_st

 *

 * Description: This structure is used to specifies payload data of

 *               API ICF_GET_STATS_RESP

 *

 *---------------------------------------------------------------------------*/

typedef struct

{
        /* denotes the stream id audio/video/tbcp */
        icf_stream_id_t           stream_id;
        /* It contains the RTCP statistics parameters. */
        icf_rtcp_report_st        rtcp_report;

} icf_get_stats_resp_st;




/*----------------------------------------------------
 * NAME : icf_play_media_req_st
 *
 * Description: This structure is used to specifies payload data of
 *               API ICF_PLAY_MEDIA_REQ
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
	/* This field bitwise contains the presence information of optional fields 
	 * in this structure. */
	
#define ICF_FILE_NAME_PRESENT				0x01
#define ICF_MEDIA_ID_PRESENT				0x02
#define ICF_PLAY_TONE_TIMER_VAL				0x04
#define ICF_PLAY_MEDIA_LINE_ID_PRESENT                  0x08
	icf_uint32_t			is_present;
	
	/* Indicates the of tone/video to be played. This is pre-configured media 
	 * with MM, using the API CONFIGURE_MEDIA */
	icf_media_id_t			media_id;

	/* Indicates the file name with full system path to be played */
	icf_file_name_st		file_name;

	/* Indicates the mode on which tone is to be played towards network, 
	 * speaker/screen or towards the both directions */
    icf_play_mode_t			play_mode;

	/* Indicates the duration for which it shall be played. 
	 * E.g. infinite, file length or timer value as specified */
    icf_play_duration_t		duration;

	/* It is timer value in mille-seconds for which tone is to be played if 
	 * duration indicates the type as timer value */

    icf_uint16_t			timer_value;
		  
    /* indicates the line id on which the tone is to be played.*/ 
    icf_line_id_t                line_id; 
} icf_play_media_req_st;

/*----------------------------------------------------------------------------
 * NAME : icf_stop_media_play_req_st
 *
 * Description: This structure is used to specifies payload data of
 *               API ICF_STOP_MEDIA_PLAY_REQ
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
	icf_uint32_t		is_present;

#define ICF_FILE_NAME_PRESENT				0x01
#define ICF_MEDIA_ID_PRESENT				0x02
#define ICF_STOP_MEDIA_PLAY_REQ_LINE_ID_PRESENT             0x04
	icf_media_id_t		media_id;
	
	/* Indicates the file name with full system path to be played. this is an optional
	 * field */
	icf_file_name_st	file_name;

        /* indicates the line id for which the stop media play request is.*/
        icf_line_id_t           line_id;

} icf_stop_media_play_req_st;

/*----------------------------------------------------------------------------
 * NAME : icf_stop_media_play_ind_st
 *
 * Description: This structure is used to specifies payload data of
 *               API ICF_STOP_MEDIA_PLAY_IND
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
	icf_uint32_t		is_present;

#define ICF_FILE_NAME_PRESENT				0x01
#define ICF_MEDIA_ID_PRESENT				0x02
#define ICF_STOP_MEDIA_PLAY_IND_LINE_ID_PRESENT         0x04
	icf_media_id_t		media_id;
	
	/* Indicates the file name with full system path to be played. this is an optional
	 * field */
	icf_file_name_st	file_name;

        icf_line_id_t           line_id;
} icf_stop_media_play_ind_st;


/*----------------------------------------------------------------------------

 * NAME : icf_stop_ringing_ind_st

 *

 * Description: This structure is used to specifies payload data of

 *               API ICF_STOP_RINGING_IND

 *

 *---------------------------------------------------------------------------*/

typedef struct

{

        icf_ringer_id_t      ringer_id;

        icf_uint8_t          bit_mask;
#define ICF_LINE_ID_PRESENT   0x01

        icf_line_id_t        line_id;  
 
} icf_stop_ringing_ind_st;











/************************************************************************

 *      Voice Application - Media Manager APIs    

 ************************************************************************/



/*----------------------------------------------------------------------------
 * NAME : icf_mute_media_req_st
 *
 * Description: This structure is used to specifies payload data of
 *               API ICF_MUTE_MEDIA_REQ
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
	/* List of stream(s) to be muted for a call */
	icf_stream_id_list_st 		stream_list;

	/* It indicates whether to mute the media path or un-mute it */
	icf_boolean_t	activate_mute;

        /* mandatory parameter, indicates presence of optional parameters.*/
        icf_uint8_t     bit_mask; 
#define ICF_LINE_ID_PRESENT     0x01

        /* optional parameter.*/
        icf_line_id_t    line_id; 
} icf_mute_media_req_st;

/* ICF rel 6.0 Multiple m-lines */
/*----------------------------------------------------------------------------
 * NAME : icf_mute_media_resp_st
 *
 * Description: This structure is used to specifies payload data of
 *               API ICF_MUTE_MEDIA_RESP
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
	icf_result_t	result;

	icf_error_t	error_cause;

        /* bit_mask will decide whether line_id present in mute media resp or not.*/
        icf_uint8_t     bit_mask;
#define    ICF_MUTE_MEDIA_RESP_LINE_ID_PRESENT      0x01

        icf_line_id_t      line_id;

} icf_mute_media_resp_st;

/* ICF rel 6.0 Multiple m-lines */
/*----------------------------------------------------------------------------
 * NAME : icf_set_media_playback_device_req_st
 *
 * Description: This structure is used to specifies payload data of
 *               API ICF_SET_MEDIA_PLAYBACK_DEVICE_REQ
 *
 *---------------------------------------------------------------------------*/
typedef struct
{

        icf_play_output_t        media_play_out_device;

        /* mandatory parameter, indicates presence of optional parameters.*/
        icf_uint8_t              bit_mask;
#define ICF_LINE_ID_PRESENT      0x01

        /* optional parameter.*/  
        icf_line_id_t            line_id; 
} icf_set_media_playback_device_req_st;


/*----------------------------------------------------------------------------

 * NAME : icf_set_earp_volume_req_st

 *

 * Description: This structure is used to specifies payload data of

 *               API ICF_SET_EARP_VOLUME_REQ

 *

 *---------------------------------------------------------------------------*/

typedef struct

{
       icf_uint16_t           level;

       /* mandatory parameter.*/
       icf_uint8_t            bit_mask;
#define ICF_LINE_ID_PRESENT   0x01

       /* optional parameter.*/ 
       icf_line_id_t          line_id;

} icf_set_earp_volume_req_st;







/*----------------------------------------------------------------------------

 * NAME : icf_set_speaker_volume_req_st

 *

 * Description: This structure is used to specifies payload data of

 *               API ICF_SET_SPEAKER_VOLUME_REQ

 *

 *---------------------------------------------------------------------------*/

typedef struct

{
        icf_uint16_t           level;

        icf_uint8_t            bit_mask;  
#define ICF_LINE_ID_PRESENT    0x01

        icf_line_id_t          line_id; 

} icf_set_speaker_volume_req_st;



/* ICF rel 6.0 Multiple m-lines */
/*----------------------------------------------------------------------------
 * NAME : icf_stop_media_record_req_st
 *
 * Description: This structure is used to specifies payload data of
 *               API ICF_STOP_MEDIA_RECORD_REQ
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
	icf_media_src_t		media_source;

	icf_uint32_t		bit_mask;
#define ICF_STREAM_ID_PRESENT	0x01
#define ICF_STOP_MEDIA_RECORD_LINE_ID_PRESENT 0x02
	icf_stream_id_t		stream_id;

        /* optional parameter.*/
        icf_line_id_t           line_id;

}icf_stop_media_record_req_st;


/************************************************************************

 *     RTCP Application Data Media Manager APIs    

 ************************************************************************/







/*----------------------------------------------------------------------------

 * NAME : icf_send_app_data_req_st

 *

 * Description: This structure is used to specifies payload data of

 *               API ICF_SEND_APP_DATA_REQ

 *

 *---------------------------------------------------------------------------*/



typedef struct

{

        /* denotes the stream id audio/video/tbcp */

        icf_stream_id_t                stream_id;



        icf_app_data_st                application_data;



        /* This field bitwise contains the presence information of optional

         * fields in this structure */

         icf_uint32_t                  bit_mask;

         #define  ICF_SEND_APP_DATA_REQ_SEQUENCE_NUMBER 0x01



        /* sequence number for multiple application data packets */

        icf_uint32_t                   sequence_num;



} icf_send_app_data_req_st;







/*----------------------------------------------------------------------------

 * NAME : icf_rcv_app_data_ind_st

 *

 * Description: This structure is used to specifies payload data of

 *               API ICF_MM_PTT_RCV_APP_DATA_IND

 *

 *---------------------------------------------------------------------------*/



typedef struct

{



        /* denotes the stream id audio/video/tbcp */

        icf_stream_id_t         stream_id;

        

        icf_app_data_st            application_data;


		/*The SSRC of the talker. This can be used as an additional information to identify the talker.*/
		icf_uint32_t            ssrc_num;


        /* This field bitwise contains the presence information of optional

         * fields in this structure */

        icf_uint32_t            bit_mask;

        #define  ICF_MM_PTT_RCV_APP_DATA_IND_SEQUENCE_NUMBER  0x01



        /* sequence number for multiple application data packets */

        icf_uint32_t            sequence_num;



} icf_rcv_app_data_ind_st;









/*----------------------------------------------------------------------------

 * NAME : icf_send_stats_req_st

 *

 * Description: This structure is used to specifies payload data of

 *               API ICF_SEND_STATS_REQ

 *

 *---------------------------------------------------------------------------*/



typedef struct

{

       /* denotes the stream id audio/video/tbcp */

        icf_stream_id_t        stream_id;



        /* type of report- sender, receiver or both */

        icf_report_type_t       report_type;

} icf_send_stats_req_st;





/*----------------------------------------------------------------------------

 * NAME : icf_stop_stats_req_st

 *

 * Description: This structure is used to specifies payload data of

 *               API ICF_STOP_STATS_REQ

 *

 *---------------------------------------------------------------------------*/



typedef struct 

{



#define ICF_STOP_STATS_REQ_STREAM_ID    0x01



    /* This field bitwise contains the presence information of optional

     * fields in this structure if any, else ICF_NO_OPTIONAL_ELEM_PRESENT*/ 

     icf_uint32_t           bit_mask;



     /* denotes the stream id audio/video/tbcp */

     icf_stream_id_t         stream_id;

 

} icf_stop_stats_req_st;



/*----------------------------------------------------------------------------

 * NAME :       icf_rtp_start_ind_st

 *

 * Description: This structure is used to specifies payload data of

 *              api ICF_RTP_START_IND

 *

 *---------------------------------------------------------------------------*/

typedef struct
{

    /* stream-id on which RTP is received */
    icf_stream_id_t		stream_id;

    /* ssrc value of the received RTP packet */
    icf_uint32_t		ssrc;

} icf_rtp_start_ind_st;


/*****************************************************************************
* Call Control to Media Manager API
*****************************************************************************/

/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_create_media_session_req_st
 *
 * Description: Used to pass parameters for ICF_CREATE_MEDIA_SESSION_REQ
 *              API      
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
#define ICF_LINE_ID_PRESENT                    0x01

    /* This field bitwise contains the presence information of optional fields
       in this structure */

    icf_uint8_t          bit_mask;



    /* Line identifier on which the new call is being in initiated
     * This is optional field. */ 


    icf_line_id_t          line_id;

    /* Denotes the number of media streams present in the request */

	/* ICF rel 6.0 Multiple m-lines This is a list of media streams and their 
	 * associated parameters. List is type of icf_req_stream_st */
	icf_list_st			*p_stream_list_data;
} icf_create_media_session_req_st;


/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_create_media_session_resp_st
 *
 * Description: Used to pass parameters for 
 *              ICF_CREATE_MEDIA_SESSION_RESP API
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* success or failure */
    icf_result_t          result;

    /* This field bitwise contains the presence information of optional
     * fields in this structure */
#define ICF_CMS_REJECT_STREAM_PRESENT	0x01

    icf_uint8_t	bit_mask;

    /* error code when the result is failure */
    icf_uint16_t           error_cause;


	/* ICF rel 6.0 Multiple m-lines The stream list returns the media streams that 
	 * are accepted by MM. List is type of icf_resp_stream_st */
	icf_list_st				*p_accepted_stream_list;

	/* This is a list of the streams rejected by MM */
	icf_stream_id_list_st	rejected_stream_list;

}icf_create_media_session_resp_st;



/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_modify_media_session_req_st
 *
 * Description: Used to pass parameters for 
 *              ICF_MODIFY_MEDIA_SESSION_REQ
 *
 *---------------------------------------------------------------------------*/

typedef struct
{

	/* ICF rel 6.0 Multiple m-lines Denotes the list of media streams that are 
	 * to be modified. List if type of icf_modify_stream_st */
    icf_list_st				*p_stream_data_list;
       
} icf_modify_media_session_req_st;

/* ICF rel 6.0 Multiple m-lines */
/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_modify_media_session_resp_st
 *
 * Description: Used to pass parameters for 
 *              ICF_MODIFY_MEDIA_SESSION_RESP
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
	icf_uint8_t		bit_mask;
#define ICF_MODIFY_MEDIA_RESP_REJECT_STREAM_PRESENT	0x01

    /* Denotes whether the result of the request API. The result can be either 
	 * Success or Failure */
    icf_result_t result;    

    /* This parameter is used to inform PA about the error cause in handling of 
     * request API. This parameter has valid value only if status is ICF_FAILURE */
    icf_error_t error_cause;

	/* The stream list returns the media streams that are accepted by MM. 
	 * List is type of icf_resp_stream_st */
	icf_list_st				*p_accepted_stream_list;
	
	/* This is a list of the streams rejected by RM */
	icf_stream_id_list_st	rejected_stream_list;
       
} icf_modify_media_session_resp_st;

/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_merge_media_session_req_st
 *
 * Description: Used to pass parameters for ICF_MERGE_MEDIA_SESSION_REQ
 *
 *---------------------------------------------------------------------------*/

typedef struct
{

    /* call identifier of the second media session to be merged */
    icf_call_id_t merge_call_id;

	/* ICF rel 6.0 Multiple m-lines no of streams to be merged */
	icf_uint8_t		count;
	/* ICF rel 6.0 Multiple m-lines stream id's which need to be merged */
    icf_merge_stream_id_st	merge_stream_id[ICF_MAX_STREAM_PER_CALL];

} icf_merge_media_session_req_st;

/* ICF rel 6.0 Multiple m-lines */
/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_delete_media_session_req_st 
 *
 * Description: Used to pass parameters for
 *              ICF_DELETE_MEDIA_SESSION_REQ 
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
	/* This is a list of streams which contain the  codecs that are to be released */
    icf_stream_id_list_st    stream_list;
} icf_delete_media_session_req_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_close_media_channel_req_st 
 *
 * Description: Used to pass parameters for
 *              ICF_CLOSE_MEDIA_CHANNEL_REQ 
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
	/* This is a list of stream ids for which UDP socket for the 
  	 * RTP and RTCP port need to be closed. Node of list is type 
	 * of icf_channel_st
	 */
    icf_list_st    *p_channel_list;
} icf_close_media_channel_req_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name:  icf_delete_media_session_ind_st 
 *
 * Description: Used to pass parameters for
 *              ICF_DELETE_MEDIA_SESSION_IND 
 *
 *---------------------------------------------------------------------------*/
typedef struct 
{
	/* ICF rel 6.0 Multiple m-lines This is a list of streams which contain the
	 * codecs that are to be released */
	icf_stream_id_list_st stream_list;
    
#define ICF_DEL_MEDIA_SESSION_ERR_CAUSE_PRESENT  0x01
	icf_uint8_t     bit_mask;
    /* Media delete cause */
     icf_error_t    error_cause;

} icf_delete_media_session_ind_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_media_capabilities_req_st
 *
 * Description: Used to pass parameters for
 *              ICF_MEDIA_CAPABILITIES_REQ
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
    icf_uint8_t bit_mask;
#define ICF_MED_CAP_STREAM_PRSNT	0x01

	 /* List is type of icf_stream_capab_st 
	  * This st contains the capabilities of that application
	  * defined in its profile.
	  */
	icf_list_st		*p_req_stream_list;
    	/* Line identifier of the line where the OPTIONS is received */
	icf_line_id_t  line_id;

} icf_media_capabilities_req_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_media_capabilities_resp_st
 *
 * Description: Used to pass parameters for
 *              ICF_MEDIA_CAPABILITIES_RESP
 *
 *---------------------------------------------------------------------------*/

typedef struct
{

    /* success or failure */
    icf_result_t        result;

    /* error code when the result is failure */
    icf_error_t        error_cause;


	/* ICF rel 6.0 Multiple m-lines The stream list returns the media 
	 * streams from MM. List is type of icf_resp_stream_st */
	icf_list_st		*p_resp_stream_list;
    /* Line identifier of the line where the OPTIONS is received */
  	icf_line_id_t  line_id; 
    


} icf_media_capabilities_resp_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_send_udp_data_req_st
 *
 * Description: Used to pass parameters for
 *              ICF_SEND_UDP_DATA_REQ
 *
 *---------------------------------------------------------------------------*/

typedef struct
{

    /* This is the local port from which UDP packet need to be sent.*/
    icf_uint16_t                source_port;

    /* This is the destination IP addr and port where UDP packet is to be sent*/
    icf_transport_address_st    dest_addr;


	/* This contains length of the application data to be sent. */
	icf_uint16_t		            app_data_len;

	/* This contains a pointer to the start of the application buffer.*/
	icf_uint8_t                 *p_app_data;

} icf_send_udp_data_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_recv_udp_data_ind_st
 *
 * Description: Used to pass parameters for
 *              ICF_RECV_UDP_DATA_IND
 *
 *---------------------------------------------------------------------------*/

typedef struct
{

    /* This is the local port on which UDP packet is received*/
    icf_uint16_t                dest_port;

    /* This is the source IP address and port from where UDP packet has been 
	 * received.*/
    icf_transport_address_st    source_addr;


	/* This contains length of the application data to be sent. */
	icf_uint16_t		            app_data_len;

	/* This contains a pointer to the start of the application buffer.*/
	icf_uint8_t                 *p_app_data;

} icf_recv_udp_data_ind_st;



/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_get_codec_list_req_st
 *
 * Description: Used to pass parameters for ICF_GET_CODEC_LIST_REQ API
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
    /* To check whether local codec list need to be sent 
     Used in case of forking requirement*/
#define ICF_LOCAL_STREAM_CAPAB_INFO_PRESENT         0x01
    icf_uint8_t    bit_mask;
    
    /* Line identifier on which the new call is being initiated */
    icf_line_id_t line_id;     


	/* ICF rel 6.0 Multiple m-lines List of the streams that will constitute
	 * the media set for the call. Element of list is type of 
	 * icf_stream_capab_st
	 */
	icf_list_st		*p_stream_capab_list;
    
    icf_list_st     *p_local_stream_capab_list;

} icf_get_codec_list_req_st;


/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_codec_list_resp_st
 *
 * Description: Used to pass parameters for ICF_GET_CODEC_LIST_RESP API
 *
 *---------------------------------------------------------------------------*/

typedef struct
{


    /*This parameter is used by RM to inform the CC about the result of request
     * API. If request API is handled successfully, result will be 
     * ICF_SUCCESS, otherwise it will be ICF_FAILURE */
    icf_result_t result;    

	/*This field bitwise contains the presence information of 
     *optional fields in this structure*/
#define ICF_CODEC_LIST_REJECTED_STREAM_LIST 0x01
    icf_uint8_t    bit_mask;

    /* This parameter is used to inform PA about the error cause in handling of 
     * request API. This parameter has valid value only if status is 
     * ICF_FAILURE */
    icf_error_t error_cause;


	/* ICF rel 6.0 Multiple m-lines The stream list returns the reserved media
	 * streams within RM. This structure returns a list of codecs and there 
	 * parameters for the selected streams in RM. The same list shall be used
	 * to return capabilities of the audio, video or T.38 streams. List is 
	 * type of icf_stream_capab_st
	 */
	icf_list_st				*p_reserved_stream_list;
	
	/* This is a list of the streams rejected by RM
	 */
	icf_stream_id_list_st	rejected_stream_list;
} icf_get_codec_list_resp_st;


/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_codec_commit_req_st
 *
 * Description: Used to pass parameters for ICF_CODEC_COMMIT_REQ
 *
 *---------------------------------------------------------------------------*/

typedef struct
{

	/* ICF rel 6.0 Multiple m-lines This is a list of streams and the 
	 * corresponding codecs (per stream) that need to be committed for a call. 
	 * Node in List is type icf_stream_capab_st
	 */
	icf_list_st	*p_stream_commit_list;
} icf_codec_commit_req_st;







/* ICF rel 6.0 Multiple m-lines */
/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_codec_commit_resp_st
 *
 * Description: Used to pass parameters for ICF_CODEC_COMMIT_RESP
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
	/* This field bitwise contains the presence information of optional fields 
	 * in this structure */

#define	ICF_CODEC_COMMIT_RESP_REJ_STREAM_LIST_PRESENT	0x01
	icf_uint8_t				bit_mask;
	
	/* Denotes the result of the request API. The status can either be Success 
	 * or Failure*/
	icf_result_t			result;
	
	/* Contains the cause of the error generated when the status is Failure.
	 * Value of presence flag: ICF_MSG_RESP_ERROR   0x01 */
	icf_error_t				error_cause;

	/* This is a list of streams which contain only those codecs which are 
	 * commited. 
	 * Node of list is type of icf_stream_commit_st */
	icf_list_st				*p_commited_stream_list;

	/* This is a list of streams which contain the  codecs that are rejected */
	icf_stream_id_list_st	rejected_stream_list;
} icf_codec_commit_resp_st;

/* ICF rel 6.0 Multiple m-lines */
/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_rel_res_req_st
 *
 * Description: Used to pass parameters for ICF_REL_RES_REQ
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
	/* This is a list of streams which contain the  codecs that are to be released */
	icf_stream_id_list_st	stream_list;
} icf_rel_res_req_st;


/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_open_media_channel_req_st
 *
 * Description: Used to pass parameters for ICF_OPEN_MEDIA_CHANNEL_REQ
 *
 *---------------------------------------------------------------------------*/

typedef struct
{

	/*  ICF will provide the list of streams and stream type
	 * (audio, video, TBCP) for which ports need to be allocated.
	 * MM should allocate free ports for RTP and RTCP. Node of
	 * list is type of icf_channel_st. 
	 */
	icf_list_st	*p_channel_list;
} icf_open_media_channel_req_st;

/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_channel_st
 *
 * Description: Parameters for channel. 
 *
 *---------------------------------------------------------------------------*/

typedef struct
{

    /*Denotes the stream type identifier, */
	icf_media_type_t	stream_type;
	/* Denotes the stream id within a call. This is used to identify a 
	 * stream if multiple streams are associated with a call.
     */
	icf_stream_id_t     stream_id;
} icf_channel_st;


/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_open_media_channel_resp_st
 *
 * Description: Used to pass parameters for ICF_OPEN_MEDIA_CHANNEL_RESP
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
    /* Denotes the result of the request API. The result
	 * can either be Success or Failure. 
	 */
	icf_result_t    result;
	/* Denotes the cause of the error generated when the
	 * result is Failure. This field is not to be used 
	 * when result is success. 
	 */
	icf_uint16_t     error_cause;

	/* This is a list of stream ids and their respective RTP ports
	 * allocated by MM. Node of list is type of icf_channel_addr_st 
	 */
	icf_list_st	   *p_channel_addr_list;
} icf_open_media_channel_resp_st;

/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_channel_addr_st
 *
 * Description: This field is used by MM in providing opened port for a stream
 *
 *---------------------------------------------------------------------------*/

typedef struct
{

    /*Denotes the stream type identifier, */
	icf_media_type_t         stream_type;
	/* Denotes the stream id within a call. This is used to identify a 
	 * stream if multiple streams are associated with a call. */
	icf_stream_id_t           stream_id;
	/* Specifies the stream IP and  port allocated for the stream. Incase
	 * of the application stream, this will contain the port of the application.
	 */
	icf_transport_address_st   stream_address;    

} icf_channel_addr_st;

/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_dgts_ind_st
 *
 * Description: Used to pass parameters for ICF_DGTS_IND
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
    /* SIP stream-id is the key to identify unique stream of data. */ 
    icf_stream_id_t stream_id;

    /* It contains the digit received from network. */
    icf_dgts_st  digits;   

    icf_uint8_t       bit_mask;
#define ICF_LINE_ID_PRESENT    0x01 

    icf_line_id_t     line_id;  

} icf_dgts_ind_st;

/* ICF rel 6.0 Multiple m-lines */
/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_media_record_req_st
 *
 * Description: Used to pass parameters for ICF_MEDIA_RECORD_REQ
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    /*It indicates the source of the voice/video to be recorded, 
     can be either from network or locally generated voice.*/ 
    icf_media_src_t media_source;

    /*Indicates type of file for recording. E.g wav file format.*/
   icf_file_typ_t  file_type;

    /*Indicates the file name to store the 
      recorded voice with full system path.*/
    icf_file_name_st file_name;

    icf_uint32_t	bit_mask;

#define ICF_STREAM_ID_PRESENT 0x01
#define ICF_MEDIA_RECORD_LINE_ID_PRESENT 0x02
    /*SIP stream-id is the key to identify unique stream of data.
     * Optional parameter */ 
    icf_stream_id_t stream_id;

    /* optional parameter.*/ 
    icf_line_id_t       line_id;

} icf_media_record_req_st;



/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_send_dgts_st
 *
 * Description: Used to pass parameters for ICF_SEND_DGTS_REQ
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
#define ICF_SEND_DGT_TRANSPORT_METHOD_PRESENT  0x01
    icf_uint8_t     bit_mask;

    /*SIP stream-id is the key to identify unique stream of data. */ 
    icf_stream_id_t stream_id;

    /*It indicates the source of the voice to be recorded, 
     can be either from network or locally generated voice.*/ 
    icf_trans_method_t transport_method;

    /*Indicates type of file for recording. E.g wav file format.*/
   icf_dgt_t  digits;
    

} icf_send_dgts_st;

/* ICF rel 6.0 Multiple m-lines */
/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_pause_media_req_st
 *
 * Description: Used to pass parameters for ICF_PAUSE_MEDIA_REQ
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
	/* This field indicates the number of stream(s) to be paused/un-paused for 
	 * a call */
	icf_stream_id_list_st	stream_id;

	/* It indicates whether to pause the media path or un-mute it */
	icf_boolean_t	activate_pause;

        icf_uint8_t     bit_mask;
#define ICF_LINE_ID_PRESENT    0x01 

        icf_line_id_t   line_id;

} icf_pause_media_req_st;
/*-----------------------------------------------------------------------------
 * 
 * Structure Name: icf_nw_status_st
 *
 * Description: Used to pass parameters for ICF_MM_SET_NW_STATUS
 *
 *---------------------------------------------------------------------------*/

typedef struct 
{
	icf_uint8_t	nw_id;
	icf_uint8_t	nw_status;
	icf_transport_addr_st nw_ip;
}icf_nw_status_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_mm_unexpected_msg_ind_st
 *
 * Description: This API is invoked by ICF towards the Media Manager
 *              to convey to it that the message which was
 *              sent to ICF by MM,was an invalid(unexpected) message.
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
   /* Denotes the error cause */
   icf_error_t          error_cause;
  
   /* Denotes the API identifier for which the indication is sent. */
   icf_api_id_t         api_id;
}icf_mm_unexpected_msg_ind_st;


/* New APIs for SDP tunnelling enhancements */
/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_tunnelled_media_capabilities_resp_st
 *
 * Description: This API is sent by MM in response to ICF_MEDIA_CAPABILITIES_REQ API.
 *
 *---------------------------------------------------------------------------*/


typedef struct 
{
    /* Bitmask for optional fields */
	icf_uint32_t			bit_mask;
    /* This indicates presence of optional parameter error_cause */
#define ICF_TUNNELLED_MED_CAP_RESP_ERROR_CAUSE_PRESENT 0x01
    /* This indicates presence of optional parameter tunneled_sdp_info */
#define ICF_TUNNELLED_MED_CAP_RESP_SDP_INFO_PRESENT    0x02    
	icf_result_t			result;
	icf_error_t			error_cause;	
    /*  This is the tunnelled SDP which is given to the application. */
	icf_tunnelled_sdp_info_st tunnelled_sdp_info;
}icf_tunnelled_media_capabilities_resp_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_tunnelled_create_media_session_req_st
 *
 * Description: Used to pass parameters for ICF_TUNNELLED_CREATE_MEDIA_SESSION_REQ
 *              API.
 *
 *---------------------------------------------------------------------------*/


typedef struct
{
    /* This field bitwise contains the presence information of optional fields
       in this structure.
    */
    icf_uint8_t          bit_mask;
    /* This indicates presence of optional parameter line_id */
#define ICF_TUNNELLED_CMS_REQ_LINE_ID_PRESENT                    0x01
    /* This indicates presence of optional parameter tunnelled_sdp_info */
#define ICF_TUNNELLED_CMS_REQ_SDP_INFO_PRESENT                   0x02    

    /* Line identifier on which the new call is being in initiated.
       This is optional field.
    */ 
    icf_line_id_t          line_id;
    /* This is the tunnelled SDP which is given to the application. */
    icf_tunnelled_sdp_info_st tunnelled_sdp_info;
}icf_tunnelled_create_media_session_req_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_tunnelled_create_media_session_resp_st
 *
 * Description: Used to pass parameters for ICF_TUNNELLED_CREATE_MEDIA_SESSION_RESP
 *              API.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
    /* success or failure */
    icf_result_t          result;
    /* This field bitwise contains the presence information of optional
       fields in this structure.
    */
    icf_uint8_t	bit_mask;
    /* This indicates presence of optional parameter error_cause */
#define ICF_TUNNELLED_CMS_RESP_ERROR_CAUSE_PRESENT 0x01
    /* This indicates presence of optional parameter tunnelled_sdp_info */
#define ICF_TUNNELLED_CMS_RESP_SDP_INFO_PRESENT  0x02

    /* error code when the result is failure */
    icf_error_t           error_cause;
    /* This is the tunnelled SDP which is given to the application. */
    icf_tunnelled_sdp_info_st tunnelled_sdp_info;
}icf_tunnelled_create_media_session_resp_st;


/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_tunnelled_modify_media_session_req_st
 *
 * Description: Used to pass parameters for ICF_TUNNELLED_MODIFY_MEDIA_SESSION_REQ
 *              API.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
    /* This field bitwise contains the presence information of optional fields
       in this structure.
    */
    icf_uint8_t          bit_mask;
    /* This indicates presence of optional parameter tunnelled_sdp_info */
#define ICF_TUNNELLED_MMS_REQ_SDP_INFO_PRESENT  0x01
    
    /* This field indicates when local SDP is required in the response to this API. */
    icf_boolean_t local_sdp_reqd;

    /* This is the tunnelled SDP which is given to the application. */
    icf_tunnelled_sdp_info_st tunnelled_sdp_info;
}icf_tunnelled_modify_media_session_req_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_tunnelled_modify_media_session_resp_st
 *
 * Description: Used to pass parameters for ICF_TUNNELLED_MODIFY_MEDIA_SESSION_RESP
 *              API.
 *
 *---------------------------------------------------------------------------*/

typedef struct
{
    /* success or failure */
    icf_result_t          result;
    /* This field bitwise contains the presence information of optional
       fields in this structure.
    */
    icf_uint8_t	bit_mask;
    /* This indicates presence of optional parameter error_cause */
#define ICF_TUNNELLED_MMS_RESP_ERROR_CAUSE_PRESENT 0x01
    /* This indicates presence of optional parameter tunnelled_sdp_info */
#define ICF_TUNNELLED_MMS_RESP_SDP_INFO_PRESENT  0x02

    /* error code when the result is failure */
    icf_error_t           error_cause;
    /* This is the tunnelled SDP which is given to the application. */
    icf_tunnelled_sdp_info_st tunnelled_sdp_info;
}icf_tunnelled_modify_media_session_resp_st;




#ifdef __cplusplus

}

#endif /* __cplusplus */



#endif /*__ICF_MM_API_H__*/

