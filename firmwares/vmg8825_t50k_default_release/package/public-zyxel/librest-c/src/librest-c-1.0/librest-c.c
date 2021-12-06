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
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>
#include <assert.h>
#include "librest-c.h"


static size_t 
write_curl_memory(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	request_mem_t *mem = (request_mem_t *)userp;

	mem->memory = realloc(mem->memory, mem->size + realsize + 1);
	if (!mem->memory)
	{
		fprintf(stderr, "[%s:%s] not enough memory (realloc returned NULL)\n", __FILE__, __FUNCTION__ );
		return 0;
	}
#ifdef REST_DEBUG
	printf("%s: size=%d,%d, contents=%s\n",__FUNCTION__,(int)size,(int)nmemb,(char *)contents);
#endif
	memcpy(mem->memory + mem->size, contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}


int
put_rest_data ( char *url, char *user, char *pass, int ssl, char *data, long *http_res, char **response )
{
	CURL *curl = NULL;
	CURLcode result = -1;
	long res;
	request_mem_t *mem = NULL;

	assert ( url != NULL );
	assert ( data != NULL );

	curl = curl_easy_init();
	if ( curl ) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

	#ifdef REST_DEBUG
		printf("%s: url=%s\n data=%s\n", __FUNCTION__, url,data);
	#endif
		
		/* only need response we get the response */
		if ( response ) {
			mem = malloc(sizeof(request_mem_t));
			mem->memory = malloc(1);
			mem->memory[0] = '\0';
			mem->size = 0;
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_curl_memory);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, mem);
		}

		result = curl_easy_perform(curl);
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &res);
		if ( http_res ) {
			*http_res = res;
		}
		
	#ifdef REST_DEBUG
		printf("%s: result=%d, http_res=%ld\n", __FUNCTION__, result, res);
	#endif

		if ( ( result == CURLE_OK ) ) {
			if ( response ) {
				*response = mem->memory;
				free(mem);
			}
		}
		else {
			if ( response ) {
				free(mem->memory);
				free(mem);
			}
		}
		curl_easy_cleanup(curl);
	}
	else {
		printf("%s: curl_easy_init fail \n", __FUNCTION__);
	}	
	return (int)result;
}

int
patch_rest_data ( char *url, char *user, char *pass, int ssl, char *data, long *http_res, char **response )
{
	CURL *curl = NULL;
	CURLcode result = -1;
	long res;
	request_mem_t *mem = NULL;

	assert ( url != NULL );
	assert ( data != NULL );

	curl = curl_easy_init();
	if ( curl ) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
		
	//	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
	//	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);

#ifdef REST_DEBUG
		printf("%s: url=%s\n data=%s\n", __FUNCTION__, url,data);
#endif

		/* only need response we get the response */
		if ( response ) {
			mem = malloc(sizeof(request_mem_t));
			mem->memory = malloc(1);
			mem->memory[0] = '\0';
			mem->size = 0;
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_curl_memory);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, mem);
		}

		result = curl_easy_perform(curl);
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &res);
		if ( http_res ) {
			*http_res = res;
		}
		
#ifdef REST_DEBUG
		printf("%s: result=%d, http_res=%ld\n", __FUNCTION__, result, res);
#endif

		if ( ( result == CURLE_OK ) ) {
			if ( response ) {
				*response = mem->memory;
				free(mem);
			}
		}
		else {
			if ( response ) {
				free(mem->memory);
				free(mem);
			}
		}
		curl_easy_cleanup(curl);
	}
	else {
		printf("%s: curl_easy_init fail \n", __FUNCTION__);
	}
	return (int)result;
}


int
get_rest_data ( char *url, char *user, char *pass, int ssl, long *http_res, char **response )
{
	CURL *curl = NULL;
	CURLcode result = -1;
	long res;
	request_mem_t *mem = NULL;

	assert ( url != NULL );
//	assert ( response != NULL );

	curl = curl_easy_init();
	if ( curl ) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
		/* only need response we get the response */
		if ( response ) {
			mem = malloc(sizeof(request_mem_t));
			mem->memory = malloc(1);
			mem->memory[0] = '\0';
			mem->size = 0;
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_curl_memory);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, mem);
		}
	#ifdef REST_DEBUG
		printf("%s: url=%s\n, response=%p\n", __FUNCTION__, url, response);
	#endif

		result = curl_easy_perform(curl);
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &res);
		if ( http_res ) {
			*http_res = res;
		}

	#ifdef REST_DEBUG
		printf("%s: result=%d, http_res=%ld\n", __FUNCTION__, result, res);
	#endif

		if ( ( result == CURLE_OK ) ) {
	#ifdef REST_DEBUG
		printf("%s: url=%s\n data=%s\n", __FUNCTION__, url,mem->memory);
	#endif

			if ( response ) {
				*response = mem->memory;
				free(mem);
			}
		}
		else {
	#ifdef REST_DEBUG
		printf("%s: url=%s\n data=NULL\n", __FUNCTION__, url);
	#endif
			if ( response ) {
				free(mem->memory);
				free(mem);
			}
		}
		curl_easy_cleanup(curl);
	}
	else {
		printf("%s: curl_easy_init fail \n", __FUNCTION__);
	}
	return (int)result;
}

int
post_rest_data ( char *url, char *user, char *pass, int ssl, char *data, long *http_res, char **response )
{
	CURL *curl = NULL;
	CURLcode result = -1;
	long res;
	request_mem_t *mem = NULL;

	assert ( url != NULL );
//	assert ( data != NULL );

	curl = curl_easy_init();
	if ( curl ) {

		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
#ifdef REST_DEBUG
		printf("%s: url=%s\n, response=%p\n", __FUNCTION__, url, response);
#endif
		
		if ( data != NULL ) {
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
#ifdef REST_DEBUG
			printf("%s: data=%s\n", __FUNCTION__, data);
#endif
		}

		/* only need response we get the response */
		if ( response ) {
			mem = malloc(sizeof(request_mem_t));
			mem->memory = malloc(1);
			mem->memory[0] = '\0';
			mem->size = 0;
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_curl_memory);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, mem);
		}

		result = curl_easy_perform(curl);
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &res);
		if ( http_res ) {
			*http_res = res;
		}
		
#ifdef REST_DEBUG
		printf("%s: result=%d, http_res=%ld\n", __FUNCTION__, result, res);
#endif

		if ( ( result == CURLE_OK ) ) {
			if ( response ) {
				*response = mem->memory;
				free(mem);
			}
		}
		else {
			if ( response ) {
				free(mem->memory);
				free(mem);
			}
		}
		curl_easy_cleanup(curl);
	}
	else {
		printf("%s: curl_easy_init fail \n", __FUNCTION__);
	}
	return (int)result;
}

int
delete_rest_data ( char *url, char *user, char *pass, int ssl, long *http_res, char **response )
{
	CURL *curl = NULL;
	CURLcode result = -1;
	long res;
	request_mem_t *mem = NULL;

	assert ( url != NULL );

	curl = curl_easy_init();
	if ( curl ) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
#ifdef REST_DEBUG
		printf("%s: url=%s\n", __FUNCTION__, url);
#endif
		/* only need response we get the response */
		if ( response ) {
			mem = malloc(sizeof(request_mem_t));
			mem->memory = malloc(1);
			mem->memory[0] = '\0';
			mem->size = 0;
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_curl_memory);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, mem);
		}

		result = curl_easy_perform(curl);
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &res);
		if ( http_res ) {
			*http_res = res;
		}

#ifdef REST_DEBUG
		printf("%s: result=%d, http_res=%ld\n", __FUNCTION__, result, res);
#endif

		if ( ( result == CURLE_OK ) ) {
			if ( response ) {
				*response = mem->memory;
				free(mem);
			}
		}
		else {
			if ( response ) {
				free(mem->memory);
				free(mem);
			}
		}
		curl_easy_cleanup(curl);
	}
	else {
		printf("%s: curl_easy_init fail \n", __FUNCTION__);
	}
	return (int)result;
}


