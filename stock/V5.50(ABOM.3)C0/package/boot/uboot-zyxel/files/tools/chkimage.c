/*
 * (C) Copyright 2010 Quantenna Communications
 *
 * (C) Copyright 2008 Semihalf
 *
 * (C) Copyright 2000-2004
 * DENX Software Engineering
 * Wolfgang Denk, wd@denx.de
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include "mkimage.h"
#include <image.h>
#include <netinet/in.h>

#define IMAGE_DATA_OFFSET	0x2000

//extern int errno;
#include <errno.h>

#ifndef MAP_FAILED
#define MAP_FAILED (void *)(-1)
#endif

extern	unsigned long	crc32 (unsigned long crc, const char *buf, unsigned int len);
static	void		usage (void);
static	void		image_verify_header (char *, int);

char	*imagefile;
char	*cmdname;

int dflag    = 0;
int eflag    = 0;
int fflag    = 0;
int vflag    = 0;
int check_os = -1;
int check_arch = -1;
int check_type = -1;
int check_comp = -1;
int check_addr = -1;
int check_ep = -1;
int check_name = -1;

image_header_t header;
image_header_t *hdr = &header;

int main (int argc, char **argv)
{
	int ifd = -1;
	uint32_t addr;
	uint32_t ep;
	struct stat sbuf;
	unsigned char *ptr;
	char *name = "";

	cmdname = *argv;

	addr = ep = 0;

	while (--argc > 0 && **++argv == '-') {
		while (*++*argv) {
			switch (**argv) {
				case 'A':
					if ((--argc <= 0) ||
							(check_arch = genimg_get_arch_id (*++argv)) < 0)
						usage ();
					goto NXTARG;
				case 'C':
					if ((--argc <= 0) ||
							(check_comp = genimg_get_comp_id (*++argv)) < 0)
						usage ();
					goto NXTARG;
				case 'O':
					if ((--argc <= 0) ||
							(check_os = genimg_get_os_id (*++argv)) < 0)
						usage ();
					goto NXTARG;
				case 'T':
					if ((--argc <= 0) ||
							(check_type = genimg_get_type_id (*++argv)) < 0)
						usage ();
					goto NXTARG;

				case 'a':
					if (--argc <= 0)
						usage ();
					addr = strtoul (*++argv, (char **)&ptr, 16);
					check_addr = 1;
					if (*ptr) {
						fprintf (stderr,
								"%s: invalid load address %s\n",
								cmdname, *argv);
						exit (EXIT_FAILURE);
					}
					goto NXTARG;
				case 'e':
					if (--argc <= 0)
						usage ();
					ep = strtoul (*++argv, (char **)&ptr, 16);
					check_ep = 1;
					if (*ptr) {
						fprintf (stderr,
								"%s: invalid entry point %s\n",
								cmdname, *argv);
						exit (EXIT_FAILURE);
					}
					eflag = 1;
					goto NXTARG;
				case 'n':
					if (--argc <= 0)
						usage ();
					name = *++argv;
					check_name = 1;
					goto NXTARG;
				case 'v':
					vflag = 1;
					goto NXTARG;
				default:
					usage ();
			}
		}
NXTARG:		;
	}

	if (argc != 1)
		usage();

	if (!eflag) {
		ep = addr;
	}

	imagefile = *argv;

	ifd = open (imagefile, O_RDONLY|O_BINARY);

	if (ifd < 0) {
		fprintf (stderr, "%s: Can't open %s: %s\n",
				cmdname, imagefile, strerror(errno));
		exit (EXIT_FAILURE);
	}

	/*
	 * list header information of existing image
	 */
	if (fstat(ifd, &sbuf) < 0) {
		fprintf (stderr, "%s: Can't stat %s: %s\n",
				cmdname, imagefile, strerror(errno));
		exit (EXIT_FAILURE);
	}

	if ((unsigned)sbuf.st_size < image_get_header_size ()) {
		fprintf (stderr,
				"%s: Bad size: \"%s\" is no valid image\n",
				cmdname, imagefile);
		exit (EXIT_FAILURE);
	}

	ptr = mmap(0, sbuf.st_size, PROT_READ, MAP_SHARED, ifd, 0);
	if (ptr == MAP_FAILED) {
		fprintf (stderr, "%s: Can't read %s: %s\n",
				cmdname, imagefile, strerror(errno));
		exit (EXIT_FAILURE);
	}

	if (fdt_check_header (ptr)) {
		/* old-style image */
		image_header_t *hdr = (image_header_t *)ptr;
		image_verify_header ((char *)ptr, sbuf.st_size);
		if (vflag) {
			image_print_contents (hdr);
		}

		int correct = 1;
		/* go through various options checking that the image parameters are correct */
		if (check_os >= 0 && image_get_os(hdr) != check_os) {
			fprintf (stderr, "%s: incorrect image OS\n", cmdname);
			correct = 0;
		}
		if (check_arch >= 0 && image_get_arch(hdr) != check_arch) {
			fprintf (stderr, "%s: incorrect arch\n", cmdname);
			correct = 0;
		}	
		if (check_type >= 0 && image_get_type(hdr) != check_type) {
			fprintf (stderr, "%s: incorrect image type\n", cmdname);
			correct = 0;
		}
		if (check_comp >= 0 && image_get_comp(hdr) != check_comp) {
			fprintf (stderr, "%s: incorrect compression type\n", cmdname);
			correct = 0;
		}
		if (check_addr >= 0 && image_get_load(hdr) != addr) {
			fprintf (stderr, "%s: incorrect load address\n", cmdname);
			correct = 0;
		}
		if (check_ep >= 0 && image_get_ep(hdr) != ep) {
			fprintf (stderr, "%s: incorrect entry point address\n", cmdname);
			correct = 0;
		}
		if (check_name >= 0 && strcmp(image_get_name(hdr), name)) {
			fprintf (stderr, "%s: incorrect name\n", cmdname);
			correct = 0;
		}
		if (!correct) {
			exit (EXIT_FAILURE);
		}
	} else {
		/* FIT image */
		fit_print_contents (ptr);

		/* FIT option checking not supported */
	}

	(void) munmap((void *)ptr, sbuf.st_size);
	(void) close (ifd);

	exit (EXIT_SUCCESS);
} 

void usage (void)
{
	fprintf (stderr, "       %s [-x] [-A arch] [-O os] [-T type] [-C comp] "
			"[-a addr] [-e ep] [-n name] image\n"
			"          -A ==> check architecture is 'arch'\n"
			"          -O ==> check operating system is 'os'\n"
			"          -T ==> check image type is 'type'\n"
			"          -C ==> check compression type is 'comp'\n"
			"          -a ==> check load address is 'addr' (hex)\n"
			"          -e ==> check entry point is 'ep' (hex)\n"
			"          -n ==> check image name is 'name'\n",
			cmdname);

	exit (EXIT_FAILURE);
}

static void image_verify_header (char *ptr, int image_size)
{
	int len;
	char *data;
	uint32_t checksum;
	image_header_t header;
	image_header_t *hdr = &header;

	/*
	 * create copy of header so that we can blank out the
	 * checksum field for checking - this can't be done
	 * on the PROT_READ mapped data.
	 */
	memcpy (hdr, ptr, sizeof(image_header_t));

	if (ntohl(hdr->ih_magic) != IH_MAGIC) {
		fprintf (stderr,
				"%s: Bad Magic Number: \"%s\" is no valid image\n",
				cmdname, imagefile);
		exit (EXIT_FAILURE);
	}

	data = (char *)hdr;
	len  = sizeof(image_header_t);

	checksum = ntohl(hdr->ih_hcrc);
	hdr->ih_hcrc = htonl(0);	/* clear for re-calculation */

	if (crc32 (0, data, len) != checksum) {
		fprintf (stderr,
				"%s: ERROR: \"%s\" has bad header checksum!\n",
				cmdname, imagefile);
		exit (EXIT_FAILURE);
	}

	unsigned long data_offset = IMAGE_DATA_OFFSET;
	data = ptr + data_offset;
	len  = image_size - data_offset;

	if (crc32 (0, data, len) != ntohl(hdr->ih_dcrc)) {
		fprintf (stderr,
				"%s: ERROR: \"%s\" has corrupted data!\n",
				cmdname, imagefile);
		exit (EXIT_FAILURE);
	}
}


