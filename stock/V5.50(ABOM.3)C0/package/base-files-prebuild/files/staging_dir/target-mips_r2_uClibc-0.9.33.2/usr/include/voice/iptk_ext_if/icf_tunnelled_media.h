/*******************************************************************************
*                                        
* FILE NAME    : icf_tunnelled_media.h
*                                        
* DESCRIPTION  : This file has the definitions for the structures used by IP
*                Phone Toolkit in tunnelled mode.       
*                                        
* Revision History :    
*                            
*    DATE      NAME                   REFERENCE         REASON
* --------     ------------           ---------         --------
* 9-FEB-2009   Rajiv Kumar            Rel8.1            Initial
*
* Copyright 2009, Aricent.                       
*                                        
*******************************************************************************/
#ifndef __ICF_TUNNELLED_MEDIA_H__
#define __ICF_TUNNELLED_MEDIA_H__

#include "icf_types.h"

#include "sdf_tunnelled_media.h"

/* Prevent Name Mangling By C++ Compilers */
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*Denotes the maximum number of media (m) lines that IPTK is able to process
  in the tunnelled mode.*/
#define ICF_MAX_NO_OF_M_LINES           7 
  
/*Denotes the maximum number of session and media level parameters that IPTK is
  able to process in the tunneled mode.*/    
#define ICF_MAX_NO_OF_ENC_STRING        45   
    
/*-----------------------------------------------------------------------------
*
* NAME : icf_c_line_st
*
* DESCRIPTION  : This data type is used by IP Phone Toolkit for getting and
*                setting the c line in SDP.This structure populate all the
*                information received in c line of SDP as individual element.
*
-----------------------------------------------------------------------------*/    
typedef Sdf_st_cLineInSdp icf_c_line_st;

/*-----------------------------------------------------------------------------
*
* NAME : icf_m_line_st
*
* DESCRIPTION  : This data type is used by IP Phone Toolkit for getting and 
*                setting the m line in SDP.This structure populate all the 
*                information received in m line of SDP as individual element.
*
-----------------------------------------------------------------------------*/
typedef Sdf_st_mLineInSdp icf_m_line_st;

/*-----------------------------------------------------------------------------
*
* NAME : icf_sdf_address_st
*
* DESCRIPTION  : This data type is used to define a structure, which can
*                specifies the address type and connection address
*                (c line in SDP) received or needed to be send in SDP message.
*
-----------------------------------------------------------------------------*/
typedef Sdf_st_address icf_sdf_address_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_sdf_string_st
 *
 * Description: This data type represents a structure, which consists of a 
 *              character array of specified length
 *
 *---------------------------------------------------------------------------*/
typedef Sdf_st_string  icf_sdf_string_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_med_level_desc_st
 *
 * Description: This data type represents a structure that contains Media 
 *              level information 
 *              
 *---------------------------------------------------------------------------*/
typedef struct
{
    /*This bitmask indicates that media level c line is present*/
    #define	ICF_TUNNELLED_SDP_MEDIA_CLINE_PRESENT   	0x01

    /*Indicates that the remaining optional fileds are present or not*/
    icf_uint8_t          bitmask; 
    
    /*This contains the info of media level C line.*/
    icf_c_line_st        med_level_cline;

    /*Contains the m line info.*/
    icf_m_line_st        m_line;

}icf_med_level_desc_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_enc_string_st
 *
 * Description: This data type represents a structure that contains sdp strings
 *              other than m line and c line.  
 *              
 *---------------------------------------------------------------------------*/
typedef struct
{
    /*It contains the sdp attribute line in string format.*/
    icf_sdf_string_st        attr_str; 

    /*This boolean indicates the sdp line is session level/media level
      (1 for session level & 0 for media level)*/
    icf_boolean_t            level;

    /*Position of media line for which this sdp line is associated with.*/
    icf_uint8_t              pos_of_media;
} icf_enc_string_st;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: icf_tunnelled_sdp_st
 *
 * Description: This data type represents a structure that contains the SDP
 *              reported to the application when Tunnell mode is ON.
 *              
 *---------------------------------------------------------------------------*/
typedef struct
{
    /*Bitmask indicating that session level c line is present in SDP*/
    #define	ICF_TUNNELLED_SDP_SESSION_CLINE_PRESENT   	0x01
    
    /*Indicates whether the optional fileds are present or not*/
    /*Only session_level_cline is optional field in this structure*/
    icf_uint8_t               bitmask; 

    /*This structure contains the session level C line structure.*/
    icf_c_line_st             session_level_cline;

    /*Number of m line present in SDP.*/
    icf_uint8_t               num_of_m_line;

    /*If num of m line is 0 then no element will be present in the array
      else it provide the m line in SDP at particular index.*/
    icf_med_level_desc_st     med_level_desc[ICF_MAX_NO_OF_M_LINES];

    /*Number of strings present in SDP other than C and M line.*/
    icf_uint8_t               num_of_encoded_string;

    /*This field contains the attributes information 
      (Session level / media level)*/
    icf_enc_string_st         encoded_string[ICF_MAX_NO_OF_ENC_STRING];
} icf_tunnelled_sdp_info_st;

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /*__ICF_TUNNELLED_MEDIA_H__*/    


