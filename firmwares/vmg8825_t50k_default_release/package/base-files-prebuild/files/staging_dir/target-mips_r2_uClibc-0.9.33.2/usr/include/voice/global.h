#ifndef __ZYIMS_GLOBAL_H__
#define __ZYIMS_GLOBAL_H__

//#include "syscall_wrapper.h" //Michael.20150518.002: Remarked to remove the Redundant Inter-header-file including(s).

//Michael.20150518.002.B: Add for removing the Redundant Inter-header-file including(s).
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
//Michael.20150518.002.E: Add.



/*______________________________________________________________________________
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
**      primitive type definition
**____________________________________________________________________________*/

#ifndef OS_uITRON
//Michael.20150112.001.B: Add to extend the 'Boolean' data type.
#define bool8	unsigned char
#define bool16	unsigned short
#define bool32	unsigned long //Equivalent definitions: (i)unsigned long int, (ii)unsigned int.
//Michael.20150112.001.E: Add.

#ifndef boolean
//Michael.20150112.001.B: Modify to extend the 'Boolean' data type.
//#define boolean unsigned int
#define boolean	bool32
//Michael.20150112.001.E: Modify.
#endif

#define bool		boolean
#endif //#ifndef OS_uITRON.


#if 0 //Remarked to avoid the compile error (i.e. two or more data types in declaration specifiers) due to duplicated definition.

//Michael.20150108.001.MEMO: modification possible history recall:
//	(1)replace the following definition by the one (define by 'typedef') in the 'Endpoint_itf.h'.
//	(2)removed definition in 'Endpoint_itf.h' to 'endpt.h'.
#ifndef UINT8
#define UINT8  unsigned char
#endif

#ifndef UINT16
#define UINT16  unsigned short
#endif

#ifndef UINT32
#define UINT32  unsigned int
#endif

#else //Michael.20150108.001: Add to restore the corresponding data type definition(s) by copying the one(s) in the '$(BRCM SDK Root)/userspace/public/include/linux/os_defs.h' where the '$(STAGING DIR)/toolchain-mips_gcc-4.6.2_uClibc-0.9.32/include/stdint.h' MUST be referred for these data type definition(s) - int{64,32,16,8}_t & uint{64,32,16,8}_t.

#ifndef NUMBER_TYPES_ALREADY_DEFINED
#define NUMBER_TYPES_ALREADY_DEFINED //This is used to avoid the data type definition conflict and/or re-definition with the one(s) in the '$(BRCM SDK Root)/userspace/public/include/linux/os_defs.h'.
//The data type definition conflict and/or re-definition condition MAY happen in the case: '$(ZyIMS)/vcm/src/vcm.c' --> '$(BRCM SDK Root)/userspace/public/include/cms_boardioctl.h' --> 'cms.h' --> 'os_defs.h'.

#include <stdint.h>  /* for the various integer types */
/* Abstract the referred & related definition part in the '$(STAGING DIR)/toolchain-mips_gcc-4.6.2_uClibc-0.9.32/include/stdint.h' as the following:
	// Exact integral types.

	// Signed.
	// There is some amount of overlap with <sys/types.h> as known by inet code.
	#ifndef __int8_t_defined
	# define __int8_t_defined
	typedef signed char             int8_t;
	typedef short int               int16_t;
	typedef int                     int32_t;
	# if __WORDSIZE == 64
	typedef long int                int64_t;
	# else
	__extension__
	typedef long long int           int64_t;
	# endif
	#endif

	// Unsigned.
	typedef unsigned char           uint8_t;
	typedef unsigned short int      uint16_t;
	#ifndef __uint32_t_defined
	typedef unsigned int            uint32_t;
	# define __uint32_t_defined
	#endif
	#if __WORDSIZE == 64
	typedef unsigned long int       uint64_t;
	#else
	__extension__
	typedef unsigned long long int  uint64_t;
	#endif
*/

/** Unsigned 64 bit integer.
 * This data type was introduced in TR-106 Issue 1, Admendment 2, Sept. 2008 */
typedef uint64_t   UINT64;

/** Signed 64 bit integer.
 * This data type was introduced in TR-106 Issue 1, Admendment 2, Sept. 2008 */
typedef int64_t    SINT64;

/** Unsigned 32 bit integer. */
typedef uint32_t   UINT32;

/** Signed 32 bit integer. */
typedef int32_t    SINT32;

/** Unsigned 16 bit integer. */
typedef uint16_t   UINT16;

/** Signed 16 bit integer. */
typedef int16_t    SINT16;

/** Unsigned 8 bit integer. */
typedef uint8_t    UINT8;

/** Signed 8 bit integer. */
typedef int8_t     SINT8;
#endif /* NUMBER_TYPES_ALREADY_DEFINED */

#endif //0



//---(Un-signed Int)---
#ifndef uint8
#define uint8  unsigned char
#endif

#ifndef uint16
#define uint16  unsigned short int
#endif

#ifndef uint32
#define uint32  unsigned long int
#endif


//---(Special)---
#ifndef ip4a
#define ip4a	unsigned long int
#endif

#ifndef sint15
#define sint15	signed short
#endif


//---(Signed Int)---
#ifndef int8
#define int8  char
#endif

#ifndef int16
#define int16  signed short int
#endif

#ifndef int32
#define int32  signed long int
#endif

//Michael.20130620.001.B: Add.
#ifndef int64
#define int64 signed long long
#endif
//Michael.20130620.001.E: Add.


/*______________________________________________________________________________
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
**      constant
**____________________________________________________________________________*/
/*----- Define null object pointer in case stdio.h isn't included ----------------*/
#ifndef NULL
#define NULL		0
#endif
/*----- standard boolean constants -------------------------------------*/
#define FALSE	0
#define TRUE		1

//Michael.20130716.001.B: Add.
enum {
	OFF = 0,
	DISABLE = 0,
	DISABLED = 0,
	ON = 1,
	ENABLE = 1,
	ENABLED = 1
};
//Michael.20130716.001.E: Add.


/*______________________________________________________________________________
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
**      macro
**____________________________________________________________________________*/

/* General purpose function macros already defined in turbo C 
**----------------------------------------------------------------------*/
#ifndef min
        #define min(x,y)        ((x)<(y)?(x):(y))       /* Lesser of two args */
#endif
#ifndef max
        #define max(x,y)        ((x)>(y)?(x):(y))       /* Greater of two args */
#endif

/* From ras\inc\Timer.h */
typedef	int	tm_id_t;		/* timer ID			*/



#ifdef OLD_ZYIMS_VOIP_AGE_1 //Michael.20121023.001 *****************************************************************
/* From ras\inc\Chann.h */
/*______________________________________________________________________*/
/*              chann_sig_t
**______________________________________________________________________*/
typedef struct {
        uint16  func_id;                                /* function-ID                                  */
} chann_sig_t;
#endif //OLD_ZYIMS_VOIP_AGE_1 //Michael.20121023.001 *****************************************************************



/* From ras\inc\UDP.H */
typedef struct udp_cb udp_cb_t;

typedef enum {
	MSG_SEND_TO_CCMCONN,
	MSG_SEND_TO_PHONE,
	MSG_SEND_TO_SIP,
	ORIG_FUNC_CCMCONN,
	ORIG_FUNC_PHONE,
	ORIG_FUNC_SIP
}MsgDest;


//*** Function Return Value Type.
#define RET_SUCCESS	1
#define RET_FAILURE	0
//Michael.20121023.001.B: Add to implement the new designed Phone Port CB FSM with the new operation logic
#define RET_SUCCESS_ONE	1
#define RET_SUCCESS_ZERO	0
#define RET_WARNING	0
#define RET_FAILURE_ZERO	0
#define RET_FAILURE_NEG	-1
#define RET_ERROR			-1
//Michael.20150911.001: Add three special return values: 'RET_FAILURE_ONE', 'RET_ERROR_ONE' & 'RET_ERROR_ZERO'.
#define RET_FAILURE_ONE	1
#define RET_ERROR_ONE		1
#define RET_ERROR_ZERO		0


//*** Constant for String Array Length.
#define TMP_STRING_32		32
#define TMP_STRING_64		64
#define TMP_STRING_128		128
#define TMP_STRING_256		256
#define TMP_STRING_512		512


#define set_bit(flag, operate_bit) ((flag) = (flag) | (1<<(operate_bit)))
#define clean_bit(flag, operate_bit) ((flag) = (flag) & (~(1<<(operate_bit))))
#define check_bit(flag, operate_bit) (1<<(operate_bit)) == ((flag) & (1<<(operate_bit)))
#define bit_flag(operate_bit) (1<<(operate_bit)) //Signle-bit markup bitmap
//Michael.MEMO.20121206.001: other bitmap/bitmask operation functions or macros:
//(1)sys_misc.c/get1stMarkBitIdx_of_32Bitmap(uint32 Bitmap, uint8 startLowBitIdx, uint8 endHighBitIdx)
//Michael.20121023.001.E: Add to implement the new designed Phone Port CB FSM with the new operation logic

#include "global_defs.h" //Michael.20150518.001: Add to include the new created header file 'global_defs.h' which is dedicated for some (misc) global & common defines.

#endif //__ZYIMS_GLOBAL_H__

