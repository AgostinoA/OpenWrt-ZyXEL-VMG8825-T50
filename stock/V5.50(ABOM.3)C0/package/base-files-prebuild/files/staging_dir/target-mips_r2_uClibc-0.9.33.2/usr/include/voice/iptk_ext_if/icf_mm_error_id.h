/*******************************************************************************
*										
* FILE NAME    :icf_error_id.h
*										
* DESCRIPTION  : This file contains the error ids
*										
* Revision History :								
*    DATE            NAME           REFERENCE       REASON			
* --------      ------------        ---------       ------
* 19-MAY-2005   Navneet Gupta					  Re-structuring of extif 
*                                                 header files
* 02-SEPT-2005  Ashutos Rath                      ReviewComments Added
*   										
* Copyright 2006,Aricent.   					
*										
*******************************************************************************/

#ifndef __ICF_MM_ERROR_ID_H__
#define __ICF_MM_ERROR_ID_H__


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

/*******************************************************************************
 *
 * Values of data type icf_error_t. Error cause used in all response API's
 *
*******************************************************************************/


#define ICF_MM_CAUSE_START				501

#define ICF_MM_CAUSE_RING_TONE_NOT_SUPPORTED		ICF_MM_CAUSE_START

#define ICF_MM_CAUSE_INTERNAL_ERROR      		ICF_MM_CAUSE_START + 1             

#define ICF_MM_CAUSE_CONNECTION_FOR_CALLID_NOT_FOUND	ICF_MM_CAUSE_START + 2       

#define ICF_MM_CAUSE_INVALID_VALUE      		ICF_MM_CAUSE_START + 3 

#define ICF_MM_CAUSE_NOT_SUPPORTED           		ICF_MM_CAUSE_START + 4 

#define ICF_MM_CAUSE_FILE_PATH_NOT_FOUND    		ICF_MM_CAUSE_START + 5 

#define ICF_MM_CAUSE_TONE_NOT_SUPPORTED       		ICF_MM_CAUSE_START + 6 

#define ICF_MM_CAUSE_INVALID_ACTION			ICF_MM_CAUSE_START + 7 

#define ICF_MM_CAUSE_INVALID_PLAY_OUT_VAL		ICF_MM_CAUSE_START + 8                   
#define ICF_MM_CAUSE_INVALID_FILE_TYPE     		ICF_MM_CAUSE_START + 9

#define ICF_MM_CAUSE_INVALID_DIGIT       		ICF_MM_CAUSE_START + 10 

#define ICF_MM_CAUSE_OUT_OF_RANGE       		ICF_MM_CAUSE_START + 11 

#define ICF_MM_CAUSE_INVALID_JB_TYPE   		ICF_MM_CAUSE_START + 12 

#define ICF_MM_CAUSE_INVALID_JB_SCALING_FACT 		ICF_MM_CAUSE_START + 13 

#define ICF_MM_CAUSE_INVALID_JB_INIT_SIZE   		ICF_MM_CAUSE_START + 14 

#define ICF_MM_CAUSE_INVALID_JB_MAX_SIZE  		ICF_MM_CAUSE_START + 15 

#define ICF_MM_CAUSE_INVALID_JB_MIN_SIZE 		ICF_MM_CAUSE_START + 16 
    
#define ICF_MM_CAUSE_REQUEST_PENDING   		    ICF_MM_CAUSE_START + 17
/*Already defined in icf_error_id.h
#define ICF_CAUSE_UNABLE_TO_CREATE_MEDIA 		ICF_MM_CAUSE_START + 18
*/
#define ICF_CAUSE_TRANSPORT_LAYER_FAILURE		ICF_MM_CAUSE_START + 19


/* CAUSE codes for GUI ENGINE */
#define ICF_GUI_ENGINE_CAUSE_START				600

/* CAUSE code for gui engine validation text */
# define ICF_CAUSE_GUI_ENGINE_VALIDATE_NO_DATA  ICF_GUI_ENGINE_CAUSE_START + 1

/* CAUSE codes for VALIDATION CODES */
#define ICF_VALIDATION_CAUSE_START                   700

#define ICF_CAUSE_AMR_MODE_COUNT_OUT_OF_RANGE        ICF_VALIDATION_CAUSE_START + 1

#define ICF_CAUSE_STREAM_ID_OUT_OF_RANGE             ICF_VALIDATION_CAUSE_START + 2

#define ICF_CAUSE_INVALID_STREAM_TYPE                ICF_VALIDATION_CAUSE_START + 3 

#define ICF_CAUSE_ENC_QUAL_OUT_OF_RANGE              ICF_VALIDATION_CAUSE_START + 4

#define ICF_CAUSE_CODEC_COUNT_OUT_OF_RANGE           ICF_VALIDATION_CAUSE_START + 5

#define ICF_CAUSE_SUPP_CLK_RATE_COUNT_OUT_OF_RANGE   ICF_VALIDATION_CAUSE_START + 6

#define ICF_CAUSE_INVALID_BITRATE_VALUE              ICF_VALIDATION_CAUSE_START + 7 

#define ICF_CAUSE_INVALID_RATE_MGMT_VALUE            ICF_VALIDATION_CAUSE_START + 8

#define ICF_CAUSE_STREAM_COUNT_MISMATCH              ICF_VALIDATION_CAUSE_START + 9 

#define ICF_CAUSE_STREAM_COUNT_OUT_OF_RANGE          ICF_VALIDATION_CAUSE_START + 10

#define ICF_CAUSE_INVALID_MEDIA_MODE                 ICF_VALIDATION_CAUSE_START+11

#define ICF_CAUSE_INVALID_QOS_MARK                   ICF_VALIDATION_CAUSE_START+12

#define ICF_CAUSE_INVALID_CODEC_COUNT                ICF_VALIDATION_CAUSE_START+13

#define ICF_CAUSE_COUNT_OUT_OF_RANGE                 ICF_VALIDATION_CAUSE_START+14

/*#define ICF_CAUSE_EXTERNAL_MAX_LIMIT               ICF_GUI_ENGINE_CAUSE_START + 100*/

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /*__ICF_MM_ERROR_ID_H__*/
