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

#ifndef _CWMP_TIME_H_
#define _CWMP_TIME_H_

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "cwmplog.h"
#include "cwmptypedef.h"

#define UNKNOWTIMEVALUE "0001-01-01T00:00:00Z"

#define IDLE_TIME 500*1000 /* 1ms idle time */
#define TIME_UINT 1000 /* Now Define unit : 1ms */
#define TIME_INTERVAL 1000000000 /* 1 secound = 1000000 nano-secound */

typedef tr069ERR_e (*TMRFUNC)(void *);


tr069ERR_e cwmp_timer_init( /*pthread_attr_t pthreadAttr*/void);
void cwmp_timer_deinit( void );
uint16 cwmp_timer_add(uint32 timerIntv /*ms*/,dateTime_t * absdateTimeStr,TMRFUNC timefn,void * privdata,int periodicFlag);
tr069ERR_e cwmp_timer_delete(uint16 id);
tr069ERR_e cwmp_timer_deleteall(void);

#define cwmp_timer_start(timerIntv,abstime,timefn,privdata) \
	cwmp_timer_add(timerIntv,abstime,timefn,privdata,0)
#define cwmp_timer_stop(id) \
	cwmp_timer_delete(id)
#define cwmp_timer_periodic_start(timerIntv,abstime,timefn,privdata) \
	cwmp_timer_add(timerIntv,abstime,timefn,privdata,1)
#define cwmp_timer_periodic_stop(id) \
	cwmp_timer_delete(id)
#define cwmp_timer_stopall() \
	cwmp_timer_deleteall()

tr069ERR_e cwmp_time_get_currentime(dateTime_t * dateTimeStr);
void cwmp_time_utcstr2timep(dateTime_t * dateTimeStr,time_t * timep);
void cwmp_time_timep2utcstr(time_t * timep,dateTime_t * dateTimeStr);

tr069ERR_e cwmp_timer_synctime(uint16 tmId, dateTime_t *absdatetime);

#endif /*_CWMP_TIME_H_*/
