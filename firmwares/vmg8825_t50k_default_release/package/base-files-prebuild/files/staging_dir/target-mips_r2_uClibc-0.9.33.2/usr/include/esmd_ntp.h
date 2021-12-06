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

#ifndef _ESMD_NTP_H_
#define _ESMD_NTP_H_




/**********************
*	Global Variable
**********************/


/**********************
*	Function List
**********************/
zcfgRet_t esmd_send_ntp_sync_tr69(int msg_type, int payloadLen, const char *payload);
#ifdef ZYXEL_POWER_MGMT
void pwr_managmnent_rule_update(void);
#endif
void esmdNtpUpdate(char*);

#endif /*_ESMD_MGMT_H_*/


