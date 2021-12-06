/*  Copyright (C) 2000-2018 ZyXEL Communications, Corp.
	All Rights Reserved.

	ZyXEL Confidential;
	Protected as an unpublished work, treated as confidential,
	and hold in trust and in strict confidence by receiving party.
	Only the employees who need to know such ZyXEL confidential information
	to carry out the purpose granted under NDA are allowed to access.

	The computer program listings, specifications and documentation
	herein are the property of ZyXEL Communications, Corp. and shall
	not be reproduced, copied, disclosed, or used in whole or in part
	for any reason without the prior express written permission of
	ZyXEL Communications, Corp.
*/
#ifndef _LIBREST_C_H
#define _LIBREST_C_H

/**
  @param  
  @param 
  @param 
  @return 
*/

typedef struct request_mem_s
{
	char *memory;
	size_t size;
} request_mem_t;

extern int put_rest_data ( char *url, char *user, char *pass, int ssl, char *data, long *http_res, char **response );
extern int patch_rest_data ( char *url, char *user, char *pass, int ssl, char *data, long *http_res, char **response );
extern int get_rest_data ( char *url, char *user, char *pass, int ssl, long *http_res, char **response );
extern int post_rest_data ( char *url, char *user, char *pass, int ssl, char *data, long *http_res, char **response );
extern int delete_rest_data ( char *url, char *user, char *pass, int ssl, long *http_res, char **response );



#endif
