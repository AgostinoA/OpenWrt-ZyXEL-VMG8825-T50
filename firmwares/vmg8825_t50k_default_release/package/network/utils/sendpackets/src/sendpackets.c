
/***********************************************************************
 * <:copyright-BRCM:2011:DUAL/GPL:standard
 * 
 *    Copyright (c) 2011 Broadcom Corporation
 *    All Rights Reserved
 * 
 * Unless you and Broadcom execute a separate written software license
 * agreement governing use of this software, this software is licensed
 * to you under the terms of the GNU General Public License version 2
 * (the "GPL"), available at http://www.broadcom.com/licenses/GPLv2.php,
 * with the following added to such license:
 * 
 *    As a special exception, the copyright holders of this software give
 *    you permission to link this software with independent modules, and
 *    to copy and distribute the resulting executable under terms of your
 *    choice, provided that you also meet, for each linked independent
 *    module, the terms and conditions of the license of that module.
 *    An independent module is a module which is not derived from this
 *    software.  The special exception does not apply to any modifications
 *    of the software.
 * 
 * Not withstanding the above, under no circumstances may you combine
 * this software in any way with any other Broadcom software provided
 * under a license other than the GPL, without Broadcom's express prior
 * written consent.
 * 
 * :>
 ************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#include <pcap.h>

#define MAX_PACKET_BUFFERS 64

/* hexval -- trivial conversion of character to nibble value */
unsigned char
hexval (unsigned char c)
{
  return (0xff & ((c > '9') ? ((c & 0x4f) - 'A' + 0x0a) : (c - '0')));
}


/* data for each stream defined */
struct pstream_t
{
  u_char *pattern;		// pointer to raw packet data
  int patternlen;		// length of raw packet
  struct timeval t;		// during send, the time the next packet should be sent
  int packets;			// packets remaining to be sent
  int delay;			// time in microseconds between packets 
} pstreams[MAX_PACKET_BUFFERS];


void
usage ()
{
  fprintf (stderr, "Usage....\n");
  fprintf (stderr, "-i device (required)\n");
  fprintf (stderr, "-t delay in usec between packets \n");
  fprintf (stderr, "   for all subsequent patterns\n");
  fprintf (stderr, "-c count of packets to send \n");
  fprintf (stderr, "   for all subsequent patterns\n");
  fprintf (stderr, "-p raw hex packet \n\n");
  fprintf (stderr,
	   "sendpackets -i eth1 -t 100000 -c 5 -p aabbccddeeff000102030405060708090a -c 7 -p 112233445566778899aabbccddeeff\n");

}

void
main (int argc, char **argv)
{
  pcap_t *fp;
  char errbuf[PCAP_ERRBUF_SIZE];
  int i;
  int j;
  int nstreams;

  int cnt;
  int tdelay;
  char iface[32];
  int patternlen;
  int opt;
  struct timeval tstart;
  struct timeval t;
  struct timeval tint;
  int pdone;
  int pbusy;

  iface[0] = 0;
  patternlen = 0;
  nstreams = 0;
  tdelay = 0;


  while ((opt = getopt (argc, argv, "i:t:c:p:")) != -1)
    {
      switch (opt)
	{
	case 'i':
	  strncpy (iface, optarg, 32);
	  break;
	case 't':
	  tdelay = atoi (optarg);
	  break;
	case 'c':
	  cnt = atoi (optarg);
	  break;
	case 'p':
	  j = strlen (optarg);
	  pstreams[nstreams].pattern = malloc (j / 2 + 4);
	  for (i = 0; i < j / 2; i++)
	    {
	      pstreams[nstreams].pattern[i] =
		((hexval (optarg[i * 2]) & 0x0f) << 4) |
		(hexval (optarg[i * 2 + 1]) & 0x0f);
	    }
	  pstreams[nstreams].patternlen = j / 2;
	  pstreams[nstreams].t.tv_sec = 0;
	  pstreams[nstreams].t.tv_usec = 0;
	  pstreams[nstreams].delay = tdelay;
	  pstreams[nstreams].packets = cnt;
	  nstreams++;
	  if (nstreams >= MAX_PACKET_BUFFERS)
	    {
	      fprintf (stderr, "Too many packets\n");
	      exit (1);
	    }

	  break;
	default:
	  usage ();
	  exit (1);
	}
    }

  if (nstreams == 0)
    {
      usage ();
      exit (1);
    }

  /* Open the output device */
  if ((fp = pcap_open_live (iface,	// name of the device
			    100,	// portion of the packet to capture (only the first 100 bytes)
			    0, 1000,	// read timeout
			    errbuf	// error buffer
       )) == NULL)
    {
      fprintf (stderr, "\nUnable to open the adapter. %s \n", iface);
      return;
    }

  tint.tv_sec = 0;		// interval time will always be < 1 sec
  gettimeofday (&tstart, NULL);
  for (i = 0; i < nstreams; i++)
    {
      // set initial time for each stream
      tint.tv_usec = pstreams[i].delay;
      timeradd (&tstart, &tint, &pstreams[i].t);
    }

  pdone = 0;
  while (pdone == 0)
    {
      // repeat until no stream has more packets
      pdone = 1;
      pbusy = 0;
      gettimeofday (&t, NULL);
      for (i = 0; i < nstreams; i++)
	{
	  if (pstreams[i].packets > 0)
	    {
	      // not done
	      pdone = 0;
	      if (timercmp (&t, &pstreams[i].t, >))
		{
		  // ready to send
		  pbusy = 1;
		  tint.tv_usec = pstreams[i].delay;
		  timeradd (&pstreams[i].t, &tint, &pstreams[i].t);
		  pstreams[i].packets--;
		  if (pcap_sendpacket
		      (fp, pstreams[i].pattern, pstreams[i].patternlen) != 0)
		    {
		      fprintf (stderr, "\nError sending the packet: \n",
			       pcap_geterr (fp));
		      return;
		    }
		}
	    }
	}
      if (pbusy == 0)
	{
	  // if no stream had anything to send yet, yield for a moment
	  usleep ((unsigned long) 5);
	}
    }

  return;
}
