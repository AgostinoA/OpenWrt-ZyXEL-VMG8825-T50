/******************************************************************************/
/*
*  Copyright (C) 2013 ZyXEL Communications, Corp.
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

#ifndef _CG_SSL_CSSL_H_
#define _CG_SSL_CSSL_H_

#ifdef ZYXEL_PATCH /*support ssl, ZyXEL 2013*/
#if defined(CG_USE_OPENSSL)
#include <openssl/ssl.h>
#include <openssl/bio.h> // 20160519 Max add

#include <cybergarage/typedef.h>
#include <cybergarage/net/csocket.h>

/****************************************
* Define
****************************************/

/****************************************
* Data Type
****************************************/
typedef int (*verify_callback_func)(int, X509_STORE_CTX *);

typedef struct _Cgctx {
	char *cert_file;
	char *key_file;
	char *CAfile;
	char *CApath;
	int verify_mode;
	verify_callback_func verify_callback;
	char *verify_cn;
} Cgctx;

/****************************************
* Function
****************************************/
BOOL cg_ssl_set_ctx(CgSocket *sock, void *ctxdata);
BOOL cg_ssl_accept(CgSocket *serverSock, CgSocket *clientSock);
void cg_ssl_show_cert(CgSocket *sock);
BOOL cg_ssl_extra_verify(CgSocket * sock);

#endif
#endif
#endif /*_CG_SSL_CSSL_H_*/
