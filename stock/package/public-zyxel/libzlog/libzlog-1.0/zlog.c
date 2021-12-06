/*!
 *  @file zlog.c
 *      application to generate zlog
 *
 *  @author     Horace Chang
 *  @date       2018-10-24 18:38:46
 *  @copyright  Copyright 2018 Zyxel Communications Corp. All Rights Reserved.
 */
//==============================================================================
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/types.h>
#include <syslog.h>
#include <stdarg.h>
#include <stdint.h>

#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>         // for syscall()
#include <sys/syscall.h>    // for syscall()

#include "zlog_api.h"


#include <errno.h>          // for program_invocation_short_name

#include "zcfg_debug.h"

#define TYPE_SYSLOG			1
#define TYPE_ZCFGLOG_PREFIX 2

int priority = LOG_INFO;
char category[64]="";
int debug = 0;
int type = TYPE_SYSLOG;

void
print_usage(void )
{
	printf("usage [-d] [-p priority] -c category log message\n");
//	printf("      type: syslog (default), zcfgLogPrefix \n");
}

int
get_input ( int argc, char *argv[] ) 
{
	int opt;
	while ((opt = getopt(argc, argv, "hdp:c:f:t:")) != -1) {
//		printf("%s: %c\n",__FUNCTION__,opt);
		switch (opt) {
		case 'h':
			print_usage();
			break;
		case 'p':
			priority = atoi(optarg);
			break;
		case 'c':
			snprintf(category, sizeof(category),"%s",optarg);
			break;
		case 'd':
			debug = 1;
			printf("debug = %d\n",debug);
			break;
		case 't':
			if ( strcmp("zcfgLogPrefix",optarg ) == 0  ) {
				type = TYPE_ZCFGLOG_PREFIX;
			}
			break;
		default: /* '?' */
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}


int
main( int argc, char *argv[] )
{
	int lens = 0;
	char rawbuf[512];
	if ( argc < 1 ) {
		print_usage();
		exit(EXIT_FAILURE);
	}
	get_input ( argc, argv );

	for (; optind < argc; optind++) {
		lens += snprintf (rawbuf + lens, sizeof(rawbuf)-lens,"%s ", argv[optind]);
		rawbuf[lens - 1] = '\n';
	}
	if ( debug ) printf("%d, %s %s, type=%d\n",priority,category, rawbuf,type);
	
	if ( type == TYPE_SYSLOG ) {
		syslog( priority, "%s %s",category, rawbuf);
	}
	
	return 0;
}
