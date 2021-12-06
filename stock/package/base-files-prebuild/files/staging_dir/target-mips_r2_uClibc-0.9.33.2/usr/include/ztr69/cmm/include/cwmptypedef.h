/******************************************************************************/
/*
*  Copyright (C) 2012 ZyXEL Communications, Corp.
*  All Rights Reserved.
*
* ZyXEL Confidential; Need to Know only.
* Protected as an unpublished work.
*
* The computer program listings, specifications and documentation
* herein are the property of ZyXEL Communications, Corp. and
* shall not be reproduced, copied, disclosed, or used in whole or
* in part for any reason without the prior express written permission of
* ZyXEL Communications, Corp.
*/
/******************************************************************************/

#ifndef _CWMP_TYPEDEF_H_
#define _CWMP_TYPEDEF_H_
#include <stdint.h>
#include <stdbool.h>

#define	STRSIZE(size)	(size+1)	/* include "\0" */
#define	WRITESIZE(size)	(size-1)	/* include "\0" */

#if !defined(TRUE)
#define TRUE (1)
#endif

#if !defined(FALSE)
#define FALSE (0)
#endif


/* Signed.  */
typedef int8_t	int8;			/* 8-bit signed integer		*/
typedef int16_t	int16;			/* 16-bit signed integer	*/
typedef int32_t	int32;			/* 32-bit signed integer	*/

/* Unsigned.  */
typedef uint8_t	uint8;			/* 8-bit unsigned integer	*/
typedef uint16_t uint16;		/* 16-bit unsigned integer	*/
typedef uint32_t uint32;		/* 32-bit unsigned integer	*/
typedef uint64_t uint64;		/* 64-bit unsigned integer	*/
typedef uint32_t ip4a;			/* IPv4 address			*/

#define SIZE_DATETIME	20 		/*0001-01-01T00:00:00Z*/
typedef struct dateTime_s{
	char value[STRSIZE(SIZE_DATETIME)];
}dateTime_t;

#endif /*_CWMP_TYPEDEF_H_*/
