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

#ifndef _ESMD_MGABDEV_H_
#define _ESMD_MGABDEV_H_


#define MGAGDEV_DATA "/tmp/mgabdev.data"


/**********************
*	Global Variable
**********************/
enum {
	MGAB_DEV_ADD = 1,
	MGAB_DEV_DELETE
};

/**********************
*	Function List
**********************/
void mgabDevUpdate(const char *, const char *, const char *, const char *, int);

#endif /*_ESMD_MGABDEV_H_*/


