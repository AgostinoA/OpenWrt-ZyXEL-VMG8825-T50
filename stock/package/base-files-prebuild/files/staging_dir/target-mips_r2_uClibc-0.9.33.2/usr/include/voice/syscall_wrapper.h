#ifndef __SYS_CALL_WRAPPER_H__
#define __SYS_CALL_WRAPPER_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <pthread.h>
#include "icf_types.h"


/*____________________________________________________________________________*/
/*	functions                                                                                                                     */
/*____________________________________________________________________________*/
icf_void_t* icf_memget(icf_uint32_t size);
icf_void_t icf_memfree(icf_void_t* buffer);
icf_void_t* icf_memcpy(icf_void_t* s1, icf_void_t* s2, icf_uint32_t size);



/*
======================================================================
== Platform-DEPEND Candidate functions:
== the following functions SHOULD be moved to the corresponding Platform-DEPEND part (i.e. sys_itf.c)
== for All Platforms, Once there is any different implement case in some Platform!
======================================================================
*/

void *zyMemcpy(void *p_destination, const void *p_source, unsigned int num_bytes_to_copy);
void *zyMemset(void *p_mem_block, unsigned int value_to_set, unsigned int num);
void *zyMalloc(unsigned int size);
void zyFree(void *ptr);

char *zyStrcpy(char *p_destination, const char *p_source);
char *zyStrncpy(char *p_destination, const char *p_source, unsigned int max_num_bytes);
char *zyStrcat(char *p_destination, const char *p_source);
char *zyStrncat(char *p_destination, const char *p_source, unsigned int max_num_bytes); //Michael.20171225.004: Add to support additional proprietary-encapsulated string-related functions 'zyStrncat()', 'zyStrncmp()' and 'zyStrncasecmp()' in the 'syscall_wrapper.c'.
char *zyStrtok(char *p_source, const char *p_delimiters);
#define STRCMP_ERROR 32767 //Michael.20171225.002: Add to enhance all proprietary-encapsulated string-related functions 'zyStrXXX()' in syscall_wrapper.c to handle the input NULL pointer.
int zyStrcmp(const char *p_string_1, const char *p_string_2); //Michael.20171225.003: Modify to correct the return value of functions 'syscall_wrapper.c/zyStrcmp() & zyStrcasecmp()' from 'unsigned int' to 'int'.
int zyStrncmp(const char *p_string_1, const char *p_string_2, unsigned int max_num_bytes); //Michael.20171225.004: Add to support additional proprietary-encapsulated string-related functions 'zyStrncat()', 'zyStrncmp()' and 'zyStrncasecmp()' in the 'syscall_wrapper.c'.
int zyStrcasecmp(const char *p_string_1, const char *p_string_2); //Michael.20171225.003: Modify to correct the return value of functions 'syscall_wrapper.c/zyStrcmp() & zyStrcasecmp()' from 'unsigned int' to 'int'.
int zyStrncasecmp(const char *p_string_1, const char *p_string_2, unsigned int max_num_bytes); //Michael.20171225.004: Add to support additional proprietary-encapsulated string-related functions 'zyStrncat()', 'zyStrncmp()' and 'zyStrncasecmp()' in the 'syscall_wrapper.c'.
unsigned int zyStrlen(const char *p_string);
int zyAtoi(const char *p_string, int *resultNumber); //Amber.20181206: Add for atoi() cannot compare string (1)just zero or (2)is non-numeric string or (3)not pure number string which start from zero.


int zyMutexInit(pthread_mutex_t *mutex);
int zyMutexLock(pthread_mutex_t *mutex);
int zyMutexUnlock(pthread_mutex_t *mutex);
int zyMutexDestroy(pthread_mutex_t *mutex);


/* Redirect Debug message for ZyIMS to setting direction., __P876__, Klose, 20130128 */
void zyPrintf( const char *fmt, ...);
int zySnprintf(char *p_destination, unsigned int max_num_bytes /*<<NOTE>> including the String Terminating NULL Byte ('\0')!!*/, const char *fmt, ...); //Michael.20190526.002: Add to support the Generic/Common Utility function - 'syscall_wrapper.c/zySnprintf()', whihc is a proprietary-encapsulated/wrapped function for the system standard library function 'snprintf()'.


#define SleepMs(x) usleep(1000*x) //Michael.20150521.003: Add by moving the macro function 'SleepMs(x)' from 'Endpoint_itf.h' & 'vcm.c' to be centralized in the 'syscall_wrapper.h'.

#endif //__SYS_CALL_WRAPPER_H__.
