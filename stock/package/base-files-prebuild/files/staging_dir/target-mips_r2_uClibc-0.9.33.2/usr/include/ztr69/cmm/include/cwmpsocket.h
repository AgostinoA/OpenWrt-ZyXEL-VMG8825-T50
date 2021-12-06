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
#ifndef _CWMP_SOCKET_H_
#define _CWMP_SOCKET_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/time.h>
#include <unistd.h>


/* Define Process Socket Receive Data Job Funtion Pointer */
typedef int (*SOCKJOB)(void*);


/*********************** 
*	Function List
***********************/
int filesock_checkservice(char *connectPath);
int filesock_connect(char *connectPath, int *sockFd);
int filesock_open (char *recvPath, int *sockFd);
void filesock_close(int *sockFd);
void filesock_listen(char *recvPath, int sockFd, int blockTimeSec, int blockTimeUsec, int recvBufSize, SOCKJOB funcPtr);
void filesock_send(char *sendPath, int sockFd, void *sendBuf, int sendBufSize);

int filesock_sendwithoptions(char *,  int,  void *,  int, int options);

#endif /*_CWMP_SOCKET_H_*/
