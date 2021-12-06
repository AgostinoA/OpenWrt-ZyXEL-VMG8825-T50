/*******************************************************************************
*										
* FILE NAME    :icf_clib.h
*										
* DESCRIPTION  :The wrapper header file to the client library
*										
* Revision History :				
*				
*    DATE            NAME         REFERENCE       REASON
* --------    ------------        ----         ----------
* 8-JUL-2005   Ram Narayan        None         Initial
*   										
* Copyright 2006, Aricent.   					
*										
*******************************************************************************/



#ifndef __ICF_CLIB_H__
#define __ICF_CLIB_H__



/* Prevent Name Mangling By C++ Compilers */

#ifdef __cplusplus

extern "C"
{
#endif /* __cplusplus */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "icf_types.h"








/* A version of malloc to provide the memory nedded by the application */
#define ICF_CLIB_MEMGET(n) icf_memget(n);

/* A version of free to release the memory allocated using icf_memget */
#define ICF_CLIB_MEMFREE(ptr) icf_memfree(ptr);

/* A wrapper around the standard C library memcpy function */
#define ICF_CLIB_MEMCPY(dst, src, n) icf_memcpy(dst, src, n);



/* These are the porting function  to be implemented by the client */
icf_void_t* icf_memget(icf_uint32_t size);

icf_void_t icf_memfree(icf_void_t* ptr);

icf_void_t* icf_memcpy(icf_void_t* dst, icf_void_t* src, icf_uint32_t len);



/****************************************************************************
*	This function is used to encode icf_msg_st into a byte buffer  
* The pointer to input buffer is provided as an argument.          
* The memory associated with the input buffer is released by ICF.  
* The memory allocated by the ICF for encoded_buffer(output) has   
* to be released by the Application.								
*****************************************************************************/

icf_return_t icf_encode_msg(icf_msg_st* p_msg, /* Input*/
							icf_uint8_t** p_p_encoded_buf,
							icf_uint32_t* p_encoded_buf_length,
							icf_error_t* p_ecode,
                                                        icf_vldt_err_st*  p_vldt_err);






/****************************************************************************
* This function releases the memory associated with the encoded buffer. 
*****************************************************************************/ 

icf_return_t icf_free_encoded_msg(icf_uint8_t* p_encoded_buf, icf_error_t* p_ecode);





/****************************************************************************
* This function is used to convert the byte buffer received from the		
* ICF to appropriate icf_message_type (User API).							
* The memory for icf_message_st is allocated by ICF which has to be freed	
* by the Application.														
* The encoded buffer (p_encoded_buf) is freed by ICF after decoding.		
*****************************************************************************/
icf_return_t icf_decode_msg(icf_msg_st**  p_p_msg, /* Output*/
							icf_uint8_t*  p_encoded_buf,
							icf_uint32_t  p_encoded_buf_length,
							icf_error_t*  p_ecode);





/******************************************************************************
* this function frees the memory allocated to icf_message_st in the function 
* icf_decode_message                                                         
*****************************************************************************/

icf_return_t icf_free_decoded_msg(icf_msg_st* p_msg, icf_error_t* p_ecode);



/*******************************************************************************
*
* FUNCTION:        icf_vldt_api
*
* DESCRIPTION:     This function is invoked to validate each API field 
*                  depending on the api-id 
*
*
******************************************************************************/
icf_return_t icf_vldt_api(
                 icf_msg_st* p_msg,
                 icf_vldt_err_st *p_vldt_err);

#ifdef __cplusplus
}
#endif /* __cplusplus */



#endif /*__ICF_LIB_H__*/ 

