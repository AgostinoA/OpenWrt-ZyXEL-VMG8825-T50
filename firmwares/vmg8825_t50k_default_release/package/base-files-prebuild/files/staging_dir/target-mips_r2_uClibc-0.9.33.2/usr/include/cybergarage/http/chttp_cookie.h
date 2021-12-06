/******************************************************************
*
*	File: chttp_cookie.h
*
*	Revision:
*
*	07/19/12
*		- first release  ZyXEL
*
******************************************************************/

#ifndef _CG_HTTP_COOKIE_H_
#define _CG_HTTP_COOKIE_H_

#include <cybergarage/http/chttp.h>

/****************************************
* Define
****************************************/
#define CG_HTTP_SETCOOKIE "Set-Cookie"
#define CG_HTTP_SETCOOKIE2 "Set-Cookie2"
#define CG_HTTP_COOKIE "Cookie"

/*set-cookie set-cookie2*/
#define MAX_NUM_COOKIES		20
#define SIZE_COOKIE			4096 /*RFC2965: at least 4096 bytes per cookie */
#define SIZE_COOKIE_NAME	64
#define SIZE_COOKIE_VALUE	512
#define SIZE_COOKIE_COMMENT	512
#define SIZE_COOKIE_URL		256
#define SIZE_COOKIE_DOMAIN	256
#define SIZE_COOKIE_MAXAGE	16
#define SIZE_COOKIE_PATH	256
#define SIZE_COOKIE_PORT	512
#define SIZE_COOKIE_VERSION	16
#define SIZE_COOKIE_EXPIRES	32
#define SIZE_COOKIE_SESSIONID 32
#define SIZE_COOKIE_AUTH 256

#define CG_HTTP_COOKIE_COMMENT	"Comment"
#define CG_HTTP_COOKIE_URL		"CommentURL"
#define CG_HTTP_COOKIE_DISCARD	"Discard"
#define CG_HTTP_COOKIE_DOMAIN	"Domain"
#define CG_HTTP_COOKIE_MAXAGE	"Max-Age"
#define CG_HTTP_COOKIE_PATH		"Path"
#define CG_HTTP_COOKIE_PORT		"Port"
#define CG_HTTP_COOKIE_SECURE	"Secure"
#define CG_HTTP_COOKIE_VERSION	"Version"
#define CG_HTTP_COOKIE_SESSIONID "Session"
#define CG_HTTP_COOKIE_AUTH "Authentication"
/*set-cookie set-cookie2*/

typedef struct _CgHttpCookieData
{
	char			name[SIZE_COOKIE_NAME+1];
	char			value[SIZE_COOKIE_VALUE+1];
	/* <- RFC2965 set-cookie2 ->*/
	char			comment[SIZE_COOKIE_COMMENT+1];
	char			commentURL[SIZE_COOKIE_URL+1];
	BOOL			discard;
	char			domain[SIZE_COOKIE_DOMAIN+1];/*Domain=.example.com*/
	char			maxAge[SIZE_COOKIE_MAXAGE+1]; /*1*DIGIT*/
	char			path[SIZE_COOKIE_PATH+1];
	char			port[SIZE_COOKIE_PORT+1];
	BOOL			secure;
	char			version[SIZE_COOKIE_VERSION+1];
	char			sessionid[SIZE_COOKIE_SESSIONID+1];
	char			authentication[SIZE_COOKIE_AUTH+1];
	/* <-RFC2965 set-cookie2 ->*/
} CgHttpCookieData;

/****************************************
* Function
****************************************/
/**** Cookie ****/
#define cg_http_request_setcookie(httpReq,value) cg_http_packet_setheadervalue((CgHttpPacket*)httpReq,CG_HTTP_COOKIE,value)
#define cg_http_request_setcookie_multi(httpReq,value) cg_http_packet_setheadervalue_multi((CgHttpPacket*)httpReq,CG_HTTP_COOKIE,value)
#define cg_http_request_getcookie(httpReq) cg_http_packet_getheadervalue((CgHttpPacket*)httpReq,CG_HTTP_COOKIE)

#define cg_http_response_setcookie(httpRes,value) cg_http_packet_setheadervalue((CgHttpPacket*)httpRes,CG_HTTP_SETCOOKIE,value)
#define cg_http_response_setcookie_multi(httpRes,value) cg_http_packet_setheadervalue_multi((CgHttpPacket*)httpRes,CG_HTTP_SETCOOKIE,value)
#define cg_http_response_setcookie2(httpRes,value) cg_http_packet_setheadervalue((CgHttpPacket*)httpRes,CG_HTTP_SETCOOKIE2,value)
#define cg_http_response_getcookie(httpRes) cg_http_packet_getheadervalue((CgHttpPacket*)httpRes,CG_HTTP_SETCOOKIE)
#define cg_http_response_getcookie2(httpRes) cg_http_packet_getheadervalue((CgHttpPacket*)httpRes,CG_HTTP_SETCOOKIE2)

void cg_http_cookie_header_parse(char * cookie,CgHttpCookieData * cookiedata);
void cg_http_cookie_content_parse(CgHttpRequest *httpReq, CgHttpCookieData *cookiedata);
CgHttpCookieData *cg_http_cookie_new();

#endif /*_CG_HTTP_COOKIE_H_*/
