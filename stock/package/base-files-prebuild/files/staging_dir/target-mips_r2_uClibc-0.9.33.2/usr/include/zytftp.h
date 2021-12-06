#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <poll.h>
#include <unistd.h>
#include "zos_api.h"

#define SERVER_PORT 69
#define BLKSIZE		512
#define TIMEOUT		5
#define SAP struct sockaddr *

#define	RRQ    01			/* read request */
#define	WRQ    02			/* write request */
#define	DATA   03			/* data packet */
#define	ACK    04			/* acknowledgement */
#define	ERROR  05			/* error code */

typedef struct
{
	short opcode;  //operate code 

	union 
	{
		short block; // block number
		short error; //error code 
	} __attribute__ ((__packed__)) be; //block number  or  error code

	char data[BLKSIZE] ;

} tftp_t ; 

typedef struct
{
	short opcode;
	short blknum;
}ack_t;

/*!
 *  tftp client
 *
 *  @param [in] server_ip       input of ip address
 *  @param [in] filename        input of file name
 *
 *  @return 0  - success
 *			-1 - fail
 */
int zytftp(char *server_ip, char *filename);
