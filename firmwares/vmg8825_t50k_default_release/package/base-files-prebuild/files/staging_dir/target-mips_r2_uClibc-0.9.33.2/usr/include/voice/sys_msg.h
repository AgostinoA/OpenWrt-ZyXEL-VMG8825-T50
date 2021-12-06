#ifndef __SYS_MSG_INCLUDE__
#define __SYS_MSG_INCLUDE__

#define	MAX_SIZE_MSG_SEND	1536

typedef struct evtMsg_s{
	uint16	event;			/* event				*/
	uint16	chann_id;		/* channel id 			*/
	uint16	dev_type;		/* device type		*/
	uint32	data_p[1536/4+1]; /* data payload. Space capacity = (1,536/4)+1 = 385 DWORD = 1,540 bytes */
	uint16	data_size;		/* data size of valid data	*/
}evtMsg_t;

typedef struct rtpPortMsg_s{
	#if 1 /* MSTC porting by Andylin, bind interface , Iproute2 */
	uint32	src_addr;
	uint32	src_port;
	uint32	dst_port;
	#else
	uint32	addr;
	uint32	port;
	#endif
	uint8	enable;
#if 1 //Ssu-Ying, support Multiple Profile
	uint16 	SipAccoundId;
#endif
}rtpPortMsg_t;

#endif
