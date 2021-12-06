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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>
#include <assert.h>
#include <unistd.h>
#include <stdbool.h>
#include "librest-c.h"
#include "zcfg_rdm_obj.h"

char url[256]="";
int debug = 0;
char httpcmd[10]="GET";
char sourcefile[128]="";
rdm_HomeCyberSecurity_t cyberSecCfg={0};

int
get_input ( int argc, char *argv[] ) 
{
	int opt;
	while ((opt = getopt(argc, argv, "hdu:c:s:t:b:")) != -1) {
		printf("%s: %c\n",__FUNCTION__,opt);
		switch (opt) {
		case 'h':
			printf("help\n");
			break;
		case 'u':
			snprintf(url, sizeof(url),"%s",optarg);
			break;
		case 'b':
			cyberSecCfg.BrowsingProtection = atoi(optarg);
			break;
		case 't':
			cyberSecCfg.TrackingProtection = atoi(optarg);
			break;
		case 'd':
			debug = 1;
			printf("debug = %d\n",debug);
			break;
		case 'c':
			snprintf(httpcmd, sizeof(httpcmd),"%s",optarg);
			break;
		case 's':
			snprintf(sourcefile, sizeof(sourcefile),"%s",optarg);
			break;
		default: /* '?' */
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}


int 
read_file ( char *filename, char **filebuf, unsigned long *filesize)
{
	int ret = 0;
	struct stat st;
	int fd = -1;
	unsigned long size = 0;
	
	if ( lstat(filename, &st ) < 0 ) {
		ret = -1;
		goto fail;
	}
	
	size = st.st_size;
	if ( filebuf ) {
		if (( *filebuf = malloc(size+1) ) == NULL ) {
			ret = -2;
			goto fail;
		}
	}
	
	if ( ( fd = open ( filename, O_RDONLY) ) < 0 ) {
		ret = -3;
		goto fail;
	}
	read(fd, *filebuf,size );
	*filesize = size;
	close(fd);
	return ret;
fail: 
	if (filebuf && *filebuf ) {
		free (*filebuf);
	}
	if ( fd >= 0 ) {
		close (fd);
	}
	return ret;
}


int
main ( int argc, char *argv[] )
{
	char *buf=NULL;
	unsigned long size = 0;
	long http_res;
	char *response = NULL;
	char *put_response = NULL;
	int ret = 0;
	struct json_object *payload_obj = NULL;
	struct json_object *json_obj;
	rdm_HomeCyberSecurity_t cyberSec={0};
//	char intbuf[16];

	get_input( argc, argv );
	if ( strlen ( sourcefile ) > 0 ) {
		if ( read_file ( sourcefile, &buf, &size) < 0 ) {
			goto fail;
		}
		if ( ( payload_obj = json_tokener_parse(buf)) == NULL ) {
			goto fail;
		}
		if ( ( json_obj = json_object_object_get(payload_obj, "enabled") ) != NULL ) {
			cyberSecCfg.Enable = json_object_get_boolean(json_obj);
		}
		if ( ( json_obj = json_object_object_get(payload_obj, "browsingProtection") ) != NULL ) {
			cyberSecCfg.BrowsingProtection = json_object_get_boolean(json_obj);
		}
		if ( ( json_obj = json_object_object_get(payload_obj, "trackingProtection") ) != NULL ) {
			cyberSecCfg.TrackingProtection = json_object_get_boolean(json_obj);
		}
		json_object_put(payload_obj);
		payload_obj = NULL;
	}

	printf("%s: cmd=%s, url=%s\n",__FUNCTION__,httpcmd,url);
	if ( strcmp(httpcmd,"GET") == 0 ) {
		ret = get_rest_data ( url,NULL, NULL, 0, &http_res, &response );
		if ( ret == 0 && (http_res >= 200) && http_res <300 ) {
			printf("%s: %s\n",__FUNCTION__,response);
			if ( ( payload_obj = json_tokener_parse(response)) == NULL ) {
				goto fail;
			}
			if ( ( json_obj = json_object_object_get(payload_obj, "browsingProtection") ) != NULL ) {
				cyberSec.BrowsingProtection = json_object_get_boolean(json_obj);
			}
			if ( ( json_obj = json_object_object_get(payload_obj, "trackingProtection") ) != NULL ) {
				cyberSec.TrackingProtection = json_object_get_boolean(json_obj);
			}
			printf("%s: brow=%d, tra=%d\n",__FUNCTION__,cyberSec.BrowsingProtection,cyberSec.TrackingProtection); 

		}
		else {
			printf("%s: ret = %d, http_res=%ld\n",__FUNCTION__,ret,http_res);
		}
	}
	else if ( strcmp(httpcmd,"PUT") == 0 ) {
		payload_obj = json_object_new_object();
		/*fill response object*/
		json_object_object_add(payload_obj, "enabled", json_object_new_boolean(cyberSecCfg.Enable));
		json_object_object_add(payload_obj, "browsingProtection", json_object_new_boolean(cyberSecCfg.BrowsingProtection));
		json_object_object_add(payload_obj, "trackingProtection", json_object_new_boolean(cyberSecCfg.TrackingProtection));

		printf("%s:\n%s\n",__FUNCTION__,(char *)json_object_get_string(payload_obj));
		put_rest_data ( url, NULL, NULL, 0, (char *)json_object_get_string(payload_obj), &http_res, &put_response );
	}

fail:
	if ( put_response ) {
		free(put_response);
	}

	if ( payload_obj ) {
		json_object_put(payload_obj);
	}

	if ( response ) {
		free(response);
	}

	if ( buf ) {
		free(buf);
	}
	return ret;
}