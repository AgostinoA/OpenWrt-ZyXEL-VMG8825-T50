/*******************************************************************************
*										
* FILE NAME    :imsc_defs.h
*										
* DESCRIPTION  :The file contains constant values used in APIs to define array
*               sizes, parameter lists etc
*										
* Revision History :								
*    DATE            NAME         REFERENCE       	REASON
* --------       ------------     ---------            ---------
* 28-APR-2005   Arvind Bhabhra   ICF App-MM API      Created Origional
*				 ref Manual
*				 FSS:40603506         
* 17-Aug-2005	Kirti/Rohit						      ICF initial
* 
* 27-Nov-2006   Deepti Goyal     ICF Rel 6.2         NAT Feature Support
* 06-Feb-2009   Tarun Gupta      Rel 8.1 LLD         SDP Tunnelling Enhancements
*
* Copyright 2009,Aricent.   					
*										
*******************************************************************************/

#ifndef __ICF_MM_DEFS_H__
#define __ICF_MM_DEFS_H__

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


#ifndef ICF_CALL_TYPE_AUDIO
#define ICF_CALL_TYPE_AUDIO                 0x01 
#endif
#ifndef ICF_CALL_TYPE_VIDIO
#define ICF_CALL_TYPE_VIDEO                 0x02
#endif
#ifndef ICF_CALL_TYPE_TBCP
#define ICF_CALL_TYPE_TBCP					0x04
#endif
#ifndef ICF_CALL_TYPE_T38
#define ICF_CALL_TYPE_T38					0x08
#endif
#ifndef ICF_CALL_TYPE_DEFAULT
#define ICF_CALL_TYPE_DEFAULT               ICF_CALL_TYPE_AUDIO 
#endif
#ifndef ICF_CALL_TYPE_INVALID
#define ICF_CALL_TYPE_INVALID				0xff
#endif


/* Maximum number of codecs in codec list specified by imsc_codec_supp_st */	
#define ICF_MAX_CODEC_SUPPORTD                10


/* Maximum number of digits present in the imsc_dgts_st */
#define ICF_MAX_DGT_LEN                 		20 


/* Maximum number of ringer entries present in the imsc_ringer_tone_st */
#define ICF_MAX_RINGER                 		20    

/* at one instance, we can configure only 4 ringer ID's. MM supports atmost
 * 20 ringer ID mappings in all
 */
#define ICF_MAX_RINGER_LIST			4
    
/* Maximum number of ringer entries present in the imsc_tones_supp_st */
#define ICF_MAX_TONES		                20    


/* Maximum length of short string */
/*#define ICF_MAX_STR_LEN             		 128*/

/* This is version of the API. */
#define ICF_VERSION_1_0                      1 

/* Maximun length of application data in the imsc_app_data_st */
#define ICF_MAX_APP_DATA_LEN                  400


/* Value defined for invalid stream-id */
#define ICF_INVALID_STREAM_ID                0xffff

    /* invalid codec identifier */
#define ICF_CODEC_UNDEFINED			255

/* Maximum Codec Attribute other then rtpmap*/
#define ICF_MAX_CODEC_ATTRIBUTE     2

/* Maximum number of media streams per call used in CMS and MMS req and resp. */	
#define ICF_MAX_MEDIA_STREAMS_PER_CALL               2

/* Maximum length of String to be encoded used in codec_st. */	
#define ICF_MAX_ENCODING_STR_LEN                     16

/* Maximum number of codecs in a single Codec List used in codec_list_st */	
#define ICF_MAX_CODEC_IN_LIST                        20


/* RTP inactivity duration. This duration is in seconds */
#define ICF_RTP_INACTIVITY_DUR					120
		
#define ICF_MAX_NAME_LENGTH           	100
#define ICF_MAX_SIPADDR_LENGTH         100
#define ICF_MAX_FILEPATH_LENGTH        100
#define ICF_MAX_GROUPNAME_LENGTH       100
#define ICF_MAX_EMAIL_LENGTH			100

#define ICF_GUI_APP_START			110
#define ICF_GUI_MAIN_APP			ICF_GUI_APP_START
#define ICF_GUI_VOICE_APP			ICF_GUI_APP_START +1
#define ICF_GUI_PHONEBOOK_APP		ICF_GUI_APP_START +2
#define ICF_GUI_APP_END			ICF_GUI_APP_START +3

/* Log level selected from the GUI */
#define ICF_GUI_LOG_LEVEL_ALL			0
#define ICF_GUI_LOG_LEVEL_DEBUG		1
#define ICF_GUI_LOG_LEVEL_PROTOCOL		2


/*Log level used by the log manager*/

#define ICF_LOG_LEVEL_BRIEF	1
#define ICF_LOG_LEVEL_DETAIL	2
#define ICF_LOG_LEVEL_PROTOCOL	3


#define ICF_PREDEFINED_TEXT_START 0
#define ICF_TEXT_CALL_CALLING ICF_PREDEFINED_TEXT_START
#define ICF_TEXT_CALL_INCOMINGCALL ICF_PREDEFINED_TEXT_START + 1
#define ICF_TEXT_CALL_FAILED ICF_PREDEFINED_TEXT_START + 2
#define ICF_TEXT_RINGING ICF_PREDEFINED_TEXT_START + 3
#define ICF_TEXT_CALL_CONNECTED ICF_PREDEFINED_TEXT_START + 4
#define ICF_TEXT_CALL_ENDED ICF_PREDEFINED_TEXT_START + 5
#define ICF_TEXT_SET_CONFIG_FAILED ICF_PREDEFINED_TEXT_START + 6

#define ICF_TEXT_GUI_ENGINE_INIT_FAILED	ICF_PREDEFINED_TEXT_START + 7
#define ICF_TEXT_CALL_HIST_DEL_SELECTED	ICF_PREDEFINED_TEXT_START + 8
#define ICF_TEXT_CALL_HIST_DEL_ALL_MISSED	ICF_PREDEFINED_TEXT_START + 9
#define ICF_TEXT_CALL_HIST_DEL_ALL_RECEIVED  ICF_PREDEFINED_TEXT_START + 10
#define ICF_TEXT_CALL_HIST_DEL_ALL_DIALED	ICF_PREDEFINED_TEXT_START + 11
#define ICF_TEXT_PHONE_BOOK_DEL_RECORD		ICF_PREDEFINED_TEXT_START + 12
#define ICF_TEXT_PHONE_BOOK_DEL_ALL_RECORDS ICF_PREDEFINED_TEXT_START + 13
#define ICF_TEXT_TOGGLE_MUTE_FAILED		ICF_PREDEFINED_TEXT_START + 14
#define ICF_TEXT_GENERIC_MEDIA_ERROR		ICF_PREDEFINED_TEXT_START + 15
#define ICF_TEXT_SPEED_DIAL_INDEX_INVALID	ICF_PREDEFINED_TEXT_START + 16
#define	ICF_TEXT_SIP_URL_INVALID			ICF_PREDEFINED_TEXT_START + 17
#define	ICF_TEXT_SIPS_URL_INVALID			ICF_PREDEFINED_TEXT_START + 18
#define	ICF_TEXT_TEL_URL_INVALID			ICF_PREDEFINED_TEXT_START + 19
#define	ICF_TEXT_E164_INVALID			ICF_PREDEFINED_TEXT_START + 20
#define	ICF_TEXT_EMAIL_INVALID			ICF_PREDEFINED_TEXT_START + 21
#define	ICF_TEXT_CONTACT_NAME_INVALID	ICF_PREDEFINED_TEXT_START + 22
#define	ICF_TEXT_CONTACT_NAME_DUPLICATE	ICF_PREDEFINED_TEXT_START + 23
#define ICF_TEXT_CONTACT_ALREADY_EXISTS	ICF_PREDEFINED_TEXT_START + 24
#define ICF_TEXT_CALL_ENDED_REMOTE_BUSY	ICF_PREDEFINED_TEXT_START + 25
#define ICF_TEXT_CALL_ENDED_USR_NOT_REGD	ICF_PREDEFINED_TEXT_START + 26
#define ICF_TEXT_CALL_ENDED_NOANSWER	ICF_PREDEFINED_TEXT_START + 27
#define ICF_TEXT_CALL_ENDED_UNDEFINED	ICF_PREDEFINED_TEXT_START + 28
#define ICF_TEXT_USER_NOT_CONFIGURED	ICF_PREDEFINED_TEXT_START + 29
#define ICF_TEXT_CALLING_ADDR_INVALID  ICF_PREDEFINED_TEXT_START + 30

#define ICF_PREDEFINED_TEXT_END ICF_PREDEFINED_TEXT_START + 30



/*-----------------------------------------------------------------------
 * The follwoing definitions list the API ids for various Interfaces to
 * or from IMS Client.
 * ----------------------------------------------------------------------*/

#define ICF_MEDIA_PLANE_API_BASE		1000

#define ICF_NS_MEDIA_PLANE_API_START	ICF_MEDIA_PLANE_API_BASE

/*NS in ICF_NS_MEDIA_PLANE_API denotes non-session media plane APIs, these
 * are present at both APP and MM APi interfaces*/

#define	ICF_CFG_CODEC_INFO_REQ		ICF_NS_MEDIA_PLANE_API_START +	1
#define	ICF_CFG_CODEC_INFO_RESP		ICF_NS_MEDIA_PLANE_API_START +	2
#define	ICF_CFG_RINGER_TONES_REQ	ICF_NS_MEDIA_PLANE_API_START +	3
#define	ICF_CFG_RINGER_TONES_RESP	ICF_NS_MEDIA_PLANE_API_START +	4
		
#define	ICF_CFG_MEDIA_REQ			ICF_NS_MEDIA_PLANE_API_START +	5
#define	ICF_CFG_MEDIA_RESP			ICF_NS_MEDIA_PLANE_API_START +	6
		
#define	ICF_CFG_JBM_MGMT_REQ			ICF_NS_MEDIA_PLANE_API_START +	7
#define	ICF_CFG_JBM_MGMT_RESP			ICF_NS_MEDIA_PLANE_API_START +	8
#define	ICF_CFG_MAX_EARP_VOL_REQ		ICF_NS_MEDIA_PLANE_API_START +	9
#define	ICF_CFG_MAX_EARP_VOL_RESP		ICF_NS_MEDIA_PLANE_API_START +	10
#define	ICF_CFG_MAX_SPEAKER_VOL_REQ		ICF_NS_MEDIA_PLANE_API_START +	11
#define	ICF_CFG_MAX_SPEAKER_VOL_RESP	ICF_NS_MEDIA_PLANE_API_START +	12
#define	ICF_CFG_SET_PORT_RANGE_REQ		ICF_NS_MEDIA_PLANE_API_START +	13
#define	ICF_CFG_SET_PORT_RANGE_RESP		ICF_NS_MEDIA_PLANE_API_START +	14
#define	ICF_CFG_SET_SELF_IP_REQ			ICF_NS_MEDIA_PLANE_API_START +	15
#define	ICF_CFG_SET_SELF_IP_RESP		ICF_NS_MEDIA_PLANE_API_START +	16
#define	ICF_CFG_SET_DIGIT_TRANS_REQ		ICF_NS_MEDIA_PLANE_API_START +	17
#define	ICF_CFG_SET_DIGIT_TRANS_RESP	ICF_NS_MEDIA_PLANE_API_START +	18

#define ICF_CFG_SET_REMOTE_VIDEO_DISPLAY_REQ	ICF_NS_MEDIA_PLANE_API_START+19
#define ICF_CFG_SET_REMOTE_VIDEO_DISPLAY_RESP	ICF_NS_MEDIA_PLANE_API_START+20
#define ICF_CFG_SET_PREVIEW_VIDEO_DISPLAY_REQ	ICF_NS_MEDIA_PLANE_API_START+21
#define ICF_CFG_SET_PREVIEW_VIDEO_DISPLAY_RESP	ICF_NS_MEDIA_PLANE_API_START+22
		
#define	ICF_START_RINGING_REQ	ICF_NS_MEDIA_PLANE_API_START +	23
#define	ICF_START_RINGING_RESP	ICF_NS_MEDIA_PLANE_API_START +	24
#define	ICF_VIBRATION_REQ	ICF_NS_MEDIA_PLANE_API_START +	25
#define	ICF_VIBRATION_RESP	ICF_NS_MEDIA_PLANE_API_START +	26
#define	ICF_MEDIA_SESSION_REQ	ICF_NS_MEDIA_PLANE_API_START +	27
#define	ICF_MEDIA_SESSION_RESP	ICF_NS_MEDIA_PLANE_API_START +	28
#define	ICF_ECHO_CANC_REQ	ICF_NS_MEDIA_PLANE_API_START +	29
#define	ICF_ECHO_CANC_RESP	ICF_NS_MEDIA_PLANE_API_START +	30
#define	ICF_VAD_SS_CNG_REQ	ICF_NS_MEDIA_PLANE_API_START +	31
#define	ICF_VAD_SS_CNG_RESP	ICF_NS_MEDIA_PLANE_API_START +	32
#define	ICF_GET_STATS_REQ	ICF_NS_MEDIA_PLANE_API_START +	33
#define	ICF_GET_STATS_RESP	ICF_NS_MEDIA_PLANE_API_START +	34
		
	
#define	ICF_PLAY_MEDIA_REQ	ICF_NS_MEDIA_PLANE_API_START +	35
#define	ICF_PLAY_MEDIA_RESP	ICF_NS_MEDIA_PLANE_API_START +	36


#define	ICF_STOP_MEDIA_PLAY_REQ		ICF_NS_MEDIA_PLANE_API_START +	37
#define	ICF_STOP_MEDIA_PLAY_RESP	ICF_NS_MEDIA_PLANE_API_START +	38
#define	ICF_STOP_MEDIA_PLAY_IND		ICF_NS_MEDIA_PLANE_API_START +	39
#define	ICF_MUTE_MEDIA_REQ			ICF_NS_MEDIA_PLANE_API_START +	40
#define	ICF_MUTE_MEDIA_RESP			ICF_NS_MEDIA_PLANE_API_START +	41
#define	ICF_SET_MEDIA_PLAYBACK_DEVICE_REQ	ICF_NS_MEDIA_PLANE_API_START +	42
#define	ICF_SET_MEDIA_PLAYBACK_DEVICE_RESP	ICF_NS_MEDIA_PLANE_API_START +	43

#define	ICF_STOP_RINGING_REQ	ICF_NS_MEDIA_PLANE_API_START +	44
#define	ICF_STOP_RINGING_RESP	ICF_NS_MEDIA_PLANE_API_START +	45
#define	ICF_STOP_VIBRATION_REQ	ICF_NS_MEDIA_PLANE_API_START +	46
#define	ICF_STOP_VIBRATION_RESP	ICF_NS_MEDIA_PLANE_API_START +	47
#define	ICF_STOP_TONE_IND		ICF_NS_MEDIA_PLANE_API_START +	48
#define	ICF_STOP_RINGING_IND	ICF_NS_MEDIA_PLANE_API_START +	49
#define	ICF_DGTS_IND			ICF_NS_MEDIA_PLANE_API_START +	50

#define ICF_CONNECT_MEDIA_DEVICE_REQ	ICF_NS_MEDIA_PLANE_API_START + 51
#define ICF_CONNECT_MEDIA_DEVICE_RESP	ICF_NS_MEDIA_PLANE_API_START + 52
#define	ICF_MEDIA_RECORD_REQ			ICF_NS_MEDIA_PLANE_API_START +	53
#define	ICF_MEDIA_RECORD_RESP			ICF_NS_MEDIA_PLANE_API_START +	54
		
#define	ICF_SEND_DGTS_REQ			ICF_NS_MEDIA_PLANE_API_START +	55
#define	ICF_SEND_DGTS_RESP			ICF_NS_MEDIA_PLANE_API_START +	56
#define	ICF_SET_EARP_VOLUME_REQ		ICF_NS_MEDIA_PLANE_API_START +	57
#define	ICF_SET_EARP_VOLUME_RESP	ICF_NS_MEDIA_PLANE_API_START +	58
#define	ICF_SET_SPEAKER_VOLUME_REQ	ICF_NS_MEDIA_PLANE_API_START +	59
#define	ICF_SET_SPEAKER_VOLUME_RESP	ICF_NS_MEDIA_PLANE_API_START +	60

#define	ICF_STOP_MEDIA_RECORD_REQ	ICF_NS_MEDIA_PLANE_API_START +	61
#define	ICF_STOP_MEDIA_RECORD_RESP	ICF_NS_MEDIA_PLANE_API_START +	62

#define	ICF_SEND_APP_DATA_REQ		ICF_NS_MEDIA_PLANE_API_START +	63
#define	ICF_SEND_APP_DATA_RESP		ICF_NS_MEDIA_PLANE_API_START +	64
#define	ICF_RCV_APP_DATA_IND		ICF_NS_MEDIA_PLANE_API_START +	65
#define	ICF_SEND_STATS_REQ			ICF_NS_MEDIA_PLANE_API_START +	66
#define	ICF_SEND_STATS_RESP			ICF_NS_MEDIA_PLANE_API_START +	67
#define	ICF_STOP_STATS_REQ			ICF_NS_MEDIA_PLANE_API_START +	68
#define	ICF_STOP_STATS_RESP			ICF_NS_MEDIA_PLANE_API_START +	69
#define	ICF_CFG_MAX_MIC_GAIN_REQ	ICF_NS_MEDIA_PLANE_API_START +	70
#define	ICF_CFG_MAX_MIC_GAIN_RESP	ICF_NS_MEDIA_PLANE_API_START +	71
#define	ICF_SET_MIC_GAIN_REQ		ICF_NS_MEDIA_PLANE_API_START +	72
#define	ICF_SET_MIC_GAIN_RESP		ICF_NS_MEDIA_PLANE_API_START +	73
#define ICF_RTP_START_IND			ICF_NS_MEDIA_PLANE_API_START +	74
#define ICF_PAUSE_MEDIA_REQ			ICF_NS_MEDIA_PLANE_API_START + 75
#define ICF_PAUSE_MEDIA_RESP		ICF_NS_MEDIA_PLANE_API_START + 76
/* adding API's for Video Share*/
#define ICF_CFG_SET_VIDEO_ATTRIB_REQ	  ICF_NS_MEDIA_PLANE_API_START + 77	
#define ICF_CFG_SET_VIDEO_ATTRIB_RESP     ICF_NS_MEDIA_PLANE_API_START + 78 


#define ICF_NS_MEDIA_PLANE_API_END		ICF_CFG_SET_VIDEO_ATTRIB_RESP + 1
	/* - new definitions End*/
/*****************************************************************************/
/*
 * The following APIs are used at the ICF(CC)-MM interface and are not exposed
 * to the application
 */
#define ICF_CC_MM_API_START			ICF_NS_MEDIA_PLANE_API_END

/* This API is invoked by ICF towards
 * Media Manager to create media session for a new call. The API may
 * contain the local parameters for the media session like codec and
 * the media direction. The API may also contain the remote media
 * parameters like remote codec, remote RTP port and IP address etc.*/

#define ICF_CREATE_MEDIA_SESSION_REQ			ICF_CC_MM_API_START + 1

/* This API is sent in response to ICF_CREATE_MEDIA_SESSION_REQ
 * to inform that the media session has been created. It also informs
 * the list of local media parameters for this media session in this API. */

#define ICF_CREATE_MEDIA_SESSION_RESP			ICF_CC_MM_API_START + 2

/* This API is invoked by ICF towards
 * Media Manager to modify the media session parameters for a existing call.
 * */

#define ICF_MODIFY_MEDIA_SESSION_REQ			ICF_CC_MM_API_START + 3

/* This API is sent in response to ICF_MODIFY_MEDIA_SESSION_REQ
 * to inform that the media session has been modified.*/

#define ICF_MODIFY_MEDIA_SESSION_RESP			ICF_CC_MM_API_START + 4

/* This API is invoked by ICF towards
 * Media Manager to delete an existing media session. */

#define ICF_DELETE_MEDIA_SESSION_REQ			ICF_CC_MM_API_START + 5

/* This API is sent in response to ICF_DELETE_MEDIA_SESSION_REQ
 * to inform that the media session has been deleted. */

#define ICF_DELETE_MEDIA_SESSION_RESP			ICF_CC_MM_API_START + 6

/* This API is sent by Media Manager to ICF
 * to indicate any media failure and that the media session for an
 * existing call has been deleted. This API has no response. */

#define ICF_DELETE_MEDIA_SESSION_IND			ICF_CC_MM_API_START + 7

/* This API is invoked by ICF towards
 * Media Manager to merge two pre existing media sessions. The two media
 * sessions are identified by their respective call id. */

#define ICF_MERGE_MEDIA_SESSION_REQ			ICF_CC_MM_API_START + 8

/* This API is sent in response to ICF_MERGE_MEDIA_SESSION_REQ
 * to indicate that the merging of the media sessions was successful. */

#define ICF_MERGE_MEDIA_SESSION_RESP			ICF_CC_MM_API_START + 9

/* This API is invoked by ICF towards MM to
 * get the list of codecs available for the new call and reserve them.
 * It can be used without a list of remote codecs in which case the
 * MM needs to reserve all list of available codecs or it can be sent
 * with remote codecs in which case MM needs to reserve one - the best
 * possible - codec. */

#define ICF_GET_CODEC_LIST_REQ					ICF_CC_MM_API_START + 10

/* This API is sent in response to ICF_GET_CODEC_LIST_REQ with
 * list of local codecs allocated for the current media session. */

#define ICF_GET_CODEC_LIST_RESP				ICF_CC_MM_API_START + 11

/* This API is invoked by ICF towards
 * Resource manager to commit one of the codec among the list of codecs
 * that were earlier reserved by MM. */

#define ICF_CODEC_COMMIT_REQ					ICF_CC_MM_API_START + 12

/* This API is sent in response to ICF_CODEC_COMMIT_REQ to
 * inform that the codec has been committed and all other reserved codecs
 * have been unreserved. */

#define ICF_CODEC_COMMIT_RESP					ICF_CC_MM_API_START + 13

/* This API is invoked by ICF towards
 * Resource manager to release all reserved codecs for this media
 * session. */

#define ICF_REL_RES_REQ						ICF_CC_MM_API_START + 14

#define ICF_MEDIA_CAPABILITIES_REQ       ICF_CC_MM_API_START + 15

#define ICF_MEDIA_CAPABILITIES_RESP      ICF_CC_MM_API_START + 16

/* This API is invoked by ICF towards Media manager to open udp port for a stream */
#define ICF_OPEN_MEDIA_CHANNEL_REQ             ICF_CC_MM_API_START + 17

/* This API is invoked by MM towards ICF in response to ICF_OPEN_CHANNEL_REQ*/
#define ICF_OPEN_MEDIA_CHANNEL_RESP      ICF_CC_MM_API_START + 18

/* This API is invoked by ICF toward MM to close media channel */
#define ICF_CLOSE_MEDIA_CHANNEL_REQ      ICF_CC_MM_API_START + 19

/* This API is invoked by ICF towards MM to send UDP data */
#define ICF_SEND_UDP_DATA_REQ            ICF_CC_MM_API_START + 20

/* This API is invoked by MM toward ICF on receiving udp data */
#define ICF_RECV_UDP_DATA_IND            ICF_CC_MM_API_START + 21

/* This API is invoked towards MM on receiving network failure indication */
#define ICF_MM_SET_NW_STATUS			 ICF_CC_MM_API_START + 22

/* This API is invoked towards MM on receiving a unexpected mess. from MM */
#define ICF_MM_UNEXPECTED_MSG_IND        ICF_CC_MM_API_START + 23

#ifdef ICF_PATCH_FOR_OFFER_IN_200

#define ICF_UPDATE_MEDIA_FOR_REINVITE_ACK ICF_CC_MM_API_START + 24

#define ICF_CC_MM_API_END  		  ICF_UPDATE_MEDIA_FOR_REINVITE_ACK 

#else
/* New APIs to exchange icf_tunnelled_sdp_info_st with the application */
#define ICF_TUNNELLED_CREATE_MEDIA_SESSION_REQ        ICF_CC_MM_API_START + 24
#define ICF_TUNNELLED_CREATE_MEDIA_SESSION_RESP       ICF_CC_MM_API_START + 25
#define ICF_TUNNELLED_MODIFY_MEDIA_SESSION_REQ        ICF_CC_MM_API_START + 26
#define ICF_TUNNELLED_MODIFY_MEDIA_SESSION_RESP       ICF_CC_MM_API_START + 27
#define ICF_TUNNELLED_MEDIA_CAPABILITIES_RESP         ICF_CC_MM_API_START + 28
#define ICF_CC_MM_API_END  		         ICF_TUNNELLED_MEDIA_CAPABILITIES_RESP        
#endif

/*****************************************************************************/

   
	
/* This is a separate API to indicate completion of the MM initialization 
 * procedureICF_MISC_API_END
 */
#define ICF_MM_INIT_COMPLETE		ICF_CC_MM_API_END + 1



/*------------------------------------------------------------------------------
 * Description: Values for data type  imsc_module_id_t  
 *----------------------------------------------------------------------------*/


/* Denotes Media Manager module. Application should fill this as destination for */
/* all media manager related APIs.                                               */ 

#define ICF_MODULE_MM                                  1

/* Denotes the Application module. The application should fill this as source id */
/* for all API's from App to IMS Client FrameWork                                */

#define ICF_MODULE_APP                                 2

/* Denotes the External Configuration Manager Module, if any.                    */
#define ICF_MODULE_CFG                                 4

/* Denotes the ICF system. The application should fill this as destination id    */
/* for all API's from App to ICF                                                 */

#define ICF_MODULE_ICF                                 6


/* Module Mapping for Media Manager */
#define ICF_MODULE_RM              ICF_MODULE_MM
/* Module Mapping for PA, This is a temporary fix for MMI
   which uses the src and dest module-id for routing */
#define ICF_MODULE_PA              ICF_MODULE_APP

/* Denotes the External SM Module, if any.                    */
#define ICF_MODULE_SM                                 8

/* Denotes the NAT Module ID
 */
#define ICF_MODULE_NAT                                50 

/* ICF rel 6.0 Multiple m-lines */
#define ICF_MAX_CODECS					10

#define ICF_MAX_MEDIA			10

#define ICF_MAX_STREAM_PER_CALL			10

#define ICF_MAX_AMR_MODE         4

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /*__ICF_MM_DEFS_H__*/
