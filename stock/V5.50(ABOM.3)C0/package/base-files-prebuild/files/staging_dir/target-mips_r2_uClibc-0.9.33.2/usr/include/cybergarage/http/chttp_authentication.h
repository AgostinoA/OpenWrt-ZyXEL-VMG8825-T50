/******************************************************************
*
*	CyberLink for C
*
*	Copyright (C) Satoshi Konno 2005
*
*       Copyright (C) 2006 Nokia Corporation. All rights reserved.
*
*       This is licensed under BSD-style license,
*       see file COPYING.
*
*	File: chttp_authentication.h
*
*	Revision:
*
*	05/31/12
*		- first release  ZyXEL
*
******************************************************************/
#ifndef _CG_HTTP_AUTHENTICATION_H_
#define _CG_HTTP_AUTHENTICATION_H_

#include <cybergarage/http/chttp.h>

/****************************************
* Define
****************************************/
/*authentication status code*/
#define CG_HTTP_STATUS_UNAUTHORIZED 401
/*authentication header*/
#define CG_HTTP_WWW_AUTHENTICATION "WWW-Authenticate"
#define CG_HTTP_AUTHENTICATION "Authorization"
#define CG_HTTP_REALM "realm"
#define CG_HTTP_NONCE "nonce"
#define CG_HTTP_QOP "qop"
#define CG_HTTP_URI "uri"
#define CG_HTTP_NONCE_COUNT "nc"
#define CG_HTTP_OPAQUE "opaque"
#define CG_HTTP_CNONCE "cnonce"
#define CG_HTTP_RESPONSE "response"
#define CG_HTTP_STALE "stale"
#define CG_HTTP_ALGORITHM "algorithm"
#define CG_HTTP_USERNAME "username"


#define CG_HTTP_DEFAULT_OPAQUE "WllYRUwgb3V0cHV0IHRoZSBiZXN0IGhlbHA="


#define CG_HTTP_DEFAULT_REALM "ZyXEL.com"
#define CG_HTTP_DEFAULT_QOP "auth"
#define CG_HTTP_DEFAULT_ALGORITHM "MD5"

typedef enum
{
   HTTP_AUTH_ERROR = -1,
   HTTP_AUTH_SUCCESS = 0,
   HTTP_AUTH_INVALID_USERNAME,
   HTTP_AUTH_INVALID_PASSWORD,
   HTTP_AUTH_NOT_EXIST
} authRet_t;

/*the authentication data storage struct*/
typedef struct authStorage_s{
	struct authStorage_s *prev;
	struct authStorage_s *next;
	char ipaddr[48];
	int port;
	CgSocket *sock;
	CgHttpHeaderList *authHeaderList;
}authStorage_t, authStorageList_t;


/****************************************
* Function
****************************************/

#define cg_http_response_getauth(httpRes) cg_http_packet_getheadervalue((CgHttpPacket*)httpRes,CG_HTTP_WWW_AUTHENTICATION);
#define cg_http_response_getrealm(httpRes) cg_http_packet_getheadervalue((CgHttpPacket*)httpRes,CG_HTTP_REALM);
#define cg_http_response_getnonce(httpRes) cg_http_packet_getheadervalue((CgHttpPacket*)httpRes,CG_HTTP_NONCE);
#define cg_http_response_getqop(httpRes) cg_http_packet_getheadervalue((CgHttpPacket*)httpRes,CG_HTTP_QOP);
#define cg_http_response_getopaque(httpRes) cg_http_packet_getheadervalue((CgHttpPacket*)httpRes,CG_HTTP_OPAQUE);
#define cg_http_response_getstale(httpRes) cg_http_packet_getheadervalue((CgHttpPacket*)httpRes,CG_HTTP_STALE);
#define cg_http_response_getalgorithm(httpRes) cg_http_packet_getheadervalue((CgHttpPacket*)httpRes,CG_HTTP_ALGORITHM);

#define cg_http_request_getauth(httpReq) cg_http_packet_getheadervalue((CgHttpPacket*)httpReq,CG_HTTP_AUTHENTICATION);
#define cg_http_request_getresponse(httpReq) cg_http_packet_getheadervalue((CgHttpPacket*)httpReq,CG_HTTP_RESPONSE);
#define cg_http_request_getrealm(httpReq) cg_http_packet_getheadervalue((CgHttpPacket*)httpReq,CG_HTTP_REALM);
#define cg_http_request_getnonce(httpReq) cg_http_packet_getheadervalue((CgHttpPacket*)httpReq,CG_HTTP_NONCE);
#define cg_http_request_getcnonce(httpReq) cg_http_packet_getheadervalue((CgHttpPacket*)httpReq,CG_HTTP_CNONCE);
#define cg_http_request_getqop(httpReq) cg_http_packet_getheadervalue((CgHttpPacket*)httpReq,CG_HTTP_QOP);
#define cg_http_request_getopaque(httpReq) cg_http_packet_getheadervalue((CgHttpPacket*)httpReq,CG_HTTP_OPAQUE);
#define cg_http_request_getalgorithm(httpReq) cg_http_packet_getheadervalue((CgHttpPacket*)httpReq,CG_HTTP_ALGORITHM);
#define cg_http_request_getnc(httpReq) cg_http_packet_getheadervalue((CgHttpPacket*)httpReq,CG_HTTP_NONCE_COUNT);
#define cg_http_request_getusername(httpReq) cg_http_packet_getheadervalue((CgHttpPacket*)httpReq,CG_HTTP_USERNAME);


CgHttpResponse *cg_http_request_post_with_auth(CgHttpRequest *httpReq, char *ipaddr, int port, char *user, char *passwd, authStorageList_t *authStorageList);
void cg_http_auth_header_parse(CgHttpPacket *httpPkt);

/*basic authentication*/
/*note: please free the return pointer after using*/
char *cg_http_base64encode(char *user, char *passwd);
char *cg_http_base64decode(char *base64Str);
void sendBasicChallenge(CgHttpRequest *httpReq, char *realm);
authRet_t cg_http_request_check_basic_auth(CgHttpRequest *httpReq, char *user, char *passwd, BOOL cookieAuthentication);

/*digest authentication*/
void initDigestInfo(CgHttpAuth **digest);
char *generateCnonce();
void generateNonce(char nonce[]);
void sendDigestChallenge(CgHttpRequest *httpReq, char *realm);
authRet_t cg_http_request_check_digest_auth(CgHttpRequest *httpReq, char *user, char *passwd);

/*url encode and decode*/
/*note: please free the return pointer after using*/
char *cg_http_url_encode(char *str);
char *cg_http_url_decode(char *str);

char* cg_http_request_generate_basicHeader( char *user, char *passwd);
char *cg_http_request_generate_digestHeader(CgHttpRequest *httpReq, CgHttpResponse *httpRes, char *user, char *passwd);
CgHttpHeaderList *cg_http_response_auth_header_backup( CgHttpResponse *httpRes);
void cg_http_response_auth_header_copy( CgHttpPacket *httpPkt, CgHttpHeaderList *headerList);

/*authentication data storage*/
authStorage_t *cg_http_auth_storage_new(void);
void cg_http_auth_storage_delete(authStorage_t *storage);
authStorageList_t *cg_http_auth_storagelist_new(void);
void cg_http_auth_storagelist_delete(authStorageList_t *storageList);
int cg_http_auth_storagelist_add(authStorageList_t *storageList, authStorage_t *storage );
void cg_http_auth_storagelist_remove(authStorageList_t *storageList, authStorage_t *storage );
authStorage_t *cg_http_auth_storagelist_getbyaddr(authStorageList_t *storageList, char* ipaddr,  int port);
authStorage_t *cg_http_auth_storagelist_getbysock(authStorageList_t * storageList,CgSocket * sock);

#endif /*_CG_HTTP_AUTHENTICATION_H_*/
