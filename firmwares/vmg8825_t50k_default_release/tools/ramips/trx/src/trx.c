/*
 * Copyright (C) 2004  Manuel Novoa III  <mjn3@codepoet.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* July 29, 2004
 *
 * This is a hacked replacement for the 'trx' utility used to create
 * wrt54g .trx firmware files.  It isn't pretty, but it does the job
 * for me.
 *
 * As an extension, you can specify a larger maximum length for the
 * .trx file using '-m'.  It will be rounded up to be a multiple of 4K.
 * NOTE: This space will be malloc()'d.
 *
 * August 16, 2004
 *
 * Sigh... Make it endian-neutral.
 *
 * TODO: Support '-b' option to specify offsets for each file.
 *
 * February 19, 2005 - mbm
 *
 * Add -a (align offset) and -b (absolute offset)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#if defined(__APPLE__)
#include <machine/endian.h>
#include <machine/byte_order.h>
#define __BYTE_ORDER BYTE_ORDER
#define __BIG_ENDIAN BIG_ENDIAN
#define bswap_16(x) NXSwapShort(x)
#define bswap_32(x) NXSwapInt(x)
#define bswap_64(x) NXSwapLongLong(x)
#else
#include <endian.h>
#include <byteswap.h>
#endif
#include "trx.h"
#include <sys/stat.h>
/*Reuse and Modify the trx to MTKSOC platform */
#ifndef MTKSOC
#define __BYTE_ORDER __LITTLE_ENDIAN
#if __BYTE_ORDER == __BIG_ENDIAN
#define STORE32_LE(X)		bswap_32(X)
#elif __BYTE_ORDER == __LITTLE_ENDIAN
#define STORE32_LE(X)		(X)
#else
#error unkown endianness!
#endif
#else
#define STORE32_LE(X)		bswap_32(X)
#endif

uint32_t crc32buf(char *buf, size_t len);
int xtoi(const char* xs, int* result);

void get_config(char *key, char *name, int name_size,char *file_path);
/**********************************************************************/
/* from trxhdr.h */

#if 1
#ifdef BOOTROM_LARGE_SIZE
#define BOOT_SIZE     0x80000 //NAND
#else
#define BOOT_SIZE     0x30000 //NOR 
#endif
#else
unsigned long int BOOT_SIZE;
#endif

#define TRX_VERSION	    1
//#define TRX_MAX_LEN	0x5A0000
#define TRX_MAX_LEN     0x2000000

#define TRX_NO_HEADER	1		/* Do not write TRX header */

#ifdef MTKSOC
#define NEED_PADDING 0
#define NO_PADDING 1
#define NO_ALIGN 1
#define ALIGN_4B 4
#define ALIGN_64K 0x1000
unsigned long int padding = NO_PADDING;
#endif

#if 1
#define CRC32_INIT_VALUE 0xffffffff
#define BUF_SIZE        100 * 1024
static char buffer[BUF_SIZE];
#endif
/**********************************************************************/

void usage(void) __attribute__ (( __noreturn__ ));

void usage(void)
{
#if 0
	fprintf(stderr, "Usage: trx [-o outfile] [-m maxlen] [-a align] [-b offset] [-f file] [-f file [-f file]]\n");
#else
	//fprintf(stderr, "Usage: trx [-p] [-k kernellen] [-o outfile] [-m maxlen] [-a align] [-b offset] [-f file] [-f file [-f file]]\n");
//	fprintf(stderr, "Usage: trx [-p] [-o outfile] [-m maxlen] [-a align] [-b offset] [-c config_file] [-f file] [-f file [-f file]] \n");
	//fprintf(stderr, "Usage: trx [-p] [-k kernel_len] [-r rootfs_len] [-o outfile] [-m maxlen] [-a align] [-b offset] [-c config_file] [-f file] [-f file [-f file]] [-t boot_file]\n");
	fprintf(stderr, "Usage: trx [-p] [-k kernel_len] [-U boot_file] [-r rootfs_len] [-o outfile] [-m maxlen] [-a align] [-b offset] [-u start_addr] [-c config_file] [-f file] [-f file [-f file]] [-t boot_file]\n");
#endif
	exit(EXIT_FAILURE);
}

void debug_info(struct trx_header *p)
{
	int i=0;

	printf("============ZyXEL header information==================\n");
	printf("\theader_magic       : %d(0x%08X)\n", p->magic, STORE32_LE(p->magic));
	printf("\theader_len         : %u(%d)\n", p->header_len, STORE32_LE(p->header_len));
	printf("\tlen                : %u(%d)\n", p->len, STORE32_LE(p->len));
	printf("\tcrc32              : %u(0x%08X)\n", p->crc32, STORE32_LE(p->crc32));
	printf("\tchipId             : %s\n", p->chipId);
	printf("\tboardId            : %s\n", p->boardId);
	printf("\tmodelId            : ");
		for(i=0;i<MODEL_ID_LEN;i++) printf("%02x ", p->modelId[i]);
	printf("\n");
	printf("\tkernel_len         : %u(%d)\n", p->kernel_len, STORE32_LE(p->kernel_len));
	printf("\tbootloader_len     : %u(%d)\n", p->boot_len, STORE32_LE(p->boot_len));
	printf("\trootfs_len         : %u(%d)\n", p->rootfs_len, STORE32_LE(p->rootfs_len));
	printf("\tdefcfg_len         : %u(%d)\n", p->defcfg_len, STORE32_LE(p->defcfg_len));
	printf("\tkernelChksum       : %08x(0x%08X)\n", p->kernelChksum, STORE32_LE(p->kernelChksum));
	printf("\tbootloaderChksum   : %08x(0x%08X)\n", p->bootChksum, STORE32_LE(p->bootChksum));
	printf("\trootfsChksum       : %08x(0x%08X)\n", p->rootfsChksum, STORE32_LE(p->rootfsChksum));
	printf("\tdefcfgChksum       : %08x(0x%08X)\n", p->defcfgChksum, STORE32_LE(p->defcfgChksum));
	printf("\timageSequence      : %d(%d)\n", p->imageSequence, STORE32_LE(p->imageSequence));
	printf("\tswVersionInt       : %s\n", p->swVersionInt);
	printf("\tswVersionExt       : %s\n", p->swVersionExt);
	printf("\theaderChksum       : %08x(0x%08X)\n", p->headerChksum, STORE32_LE(p->headerChksum));
	printf("\n\n\n");
}

int main(int argc, char **argv)
{
	FILE *out = stdout;
	FILE *in;
	char *ofn = NULL;
	unsigned char *buf;
	char *e;
	char config_file[128];
	int c, i;
	size_t n;
	uint32_t cur_len;
	uint32_t round;
	uint32_t boot_crc32;
	unsigned long maxlen = TRX_MAX_LEN;
	struct trx_header *p;
	struct stat stbuf;

	uint32_t allinone_crc32;
	unsigned long count = 0;
	unsigned char * crc_ptr = NULL;
#if 1
	int flag_ZYXEL = 0;
	int flag_boot = 0;
	char kernel_fileName[256], rootfs_fileName[256], defcfg_fileName[256], boot_fileName[256];
	FILE *fp_kernel=NULL, *fp_rootfs=NULL, *fp_defcfg=NULL, *fp_boot=NULL;
	u_int32_t rootfs_size, kernel_size, defcfg_size, boot_size, kernelCrc, rootfsCrc, defcfgCrc, bootCrc;
	rootfs_size =  kernel_size =  defcfg_size = boot_size=0;
	kernelCrc = rootfsCrc = defcfgCrc = bootCrc = CRC32_INIT_VALUE;
	int isSupportDefcfg=0;
	int isSupportrootfs=0;
#endif

	fprintf(stderr, "mjn3's trx replacement - v0.81.1\n");

	if (!(buf = malloc(maxlen))) {
		fprintf(stderr, "malloc failed\n");
		return EXIT_FAILURE;
	}

	p = (struct trx_header *) buf;
#ifndef MTKSOC
	p->magic = STORE32_LE(TRX_MAGIC);
#endif
	cur_len = sizeof(struct trx_header);
	//p->flag_version = STORE32_LE((TRX_VERSION << 16));

	in = NULL;
	i = 0;

#if 1//zyxel
	while ((c = getopt(argc, argv, "-:k:r:o:m:a:b:u:c:d:f:p:t:gh:T:U:K:G:R:C:P:B:I:S:s:")) != -1) {
#else
	while ((c = getopt(argc, argv, "-:k:r:o:m:a:b:u:c:d:f:p:t:gh:")) != -1) {
#endif
		switch (c) {
			/*pork 20090313 added*/
#ifdef MTKSOC
			//case 'k':
			//	p->kernel_len = STORE32_LE(atoi(optarg));
			//	break;
			case 'k':
                fprintf(stderr, "kernel size = %d\r\n", atoi(optarg));
                p->kernel_len = STORE32_LE(atoi(optarg));
                break;
            case 'r':
                fprintf(stderr, "rootfs size = %d\r\n", atoi(optarg));
                p->rootfs_len = STORE32_LE(atoi(optarg));
                break;
            case 'd':
               fprintf(stderr, "ctromfile size = %d\r\n", atoi(optarg));
               p->romfile_len = STORE32_LE(atoi(optarg));
                break;
#if 1//zyxel
            case 'T':
                if(strcmp(optarg,"ZYXEL") == 0)
                    flag_ZYXEL = 1;
                break;
            case 'U':
            	if(strcmp(optarg,"BOOT") == 0)
                    flag_boot = 1;	//Use this option for LTE7xx0 bootloader.
                break;
            case 'K':
                strcpy(kernel_fileName, optarg);
                break;
            case 'G':
                strcpy(boot_fileName, optarg);
                break;
            case 'R':
                strcpy(rootfs_fileName, optarg);
				isSupportrootfs = 1;	
                break;
            case 'C':
                strcpy(defcfg_fileName, optarg);
                isSupportDefcfg = 1;
                break;
            case 'P':
                if (strlen(optarg) >= CHIP_ID_LEN)
                    printf("\n*** WARNING *** Input Chip ID is oversized. Only %d bytes will be stored.\n", CHIP_ID_LEN - 1);
                strncpy((char *)p->chipId, optarg, CHIP_ID_LEN - 1);
                break;
            case 'B':
                if (strlen(optarg) >= BOARD_ID_LEN)
                    printf("\n*** WARNING *** Input Board ID is oversized. Only %d bytes will be stored.\n", BOARD_ID_LEN - 1);
                strncpy((char *)p->boardId, optarg, BOARD_ID_LEN - 1);
                break;
            case 'I':
                if (strlen(optarg) != MODEL_ID_LEN)
                    printf("\n*** WARNING *** The length of Model ID is not equal to %d.\n", MODEL_ID_LEN);
                int byte=0;
                char addr_str[3];
                for(i=0;i<MODEL_ID_LEN;i++) {
                    memset( addr_str, 0, 3 );
                    memcpy( addr_str+1, optarg+i, 1 );
                    xtoi(addr_str, &byte);
                    optarg[i]=(byte & 0xff);
                }
                memcpy((char *)p->modelId, optarg, MODEL_ID_LEN);
                break;
            case 'S':
                if (strlen(optarg) >= SW_VERSION_LEN)
                    printf("\n*** WARNING *** Input internal SW Version is oversized. Only %d bytes will be stored.\n", SW_VERSION_LEN - 1);
                strncpy((char *)p->swVersionInt, optarg, SW_VERSION_LEN - 1);
                break;
            case 's':
                if (strlen(optarg) >= SW_VERSION_LEN)
                    printf("\n*** WARNING *** Input external SW Version is oversized. Only %d bytes will be stored.\n", SW_VERSION_LEN - 1);
                strncpy((char *)p->swVersionExt, optarg, SW_VERSION_LEN - 1);
                break;
#endif
            case 'p':
                padding = NEED_PADDING;
                break;
                /*use config file*/
            case 'c':
                //	fprintf(stderr,"11 %s %d\n",optarg,sizeof(struct trx_header));
                if(optarg != NULL){
                    strncpy(config_file,optarg,sizeof(config_file));
                }
                break;
            /* frankliao 20100510 added over*/
            case 't':
                if (!(in = fopen(argv[2], "rb"))) {
                    fprintf(stderr, "can not open \"%s\" for reading\n", optarg);
                    usage();
                }

                //if (!(out = fopen("boot.bin", "wb"))) {
                if (!(out = fopen(boot_fileName, "wb"))) {
                    fprintf(stderr, "can not open file boot.bin for writing\n");
                    usage();
                }
#if 0
                {
                    char *str;
                    str = getenv("BOOT_SIZE");
                    if (str) {
                        BOOT_SIZE=strtoul(str, NULL, 0);
                    } else {
                        BOOT_SIZE=0x10000; //64K
                    }
                    //fprintf(stdout, "Max. boot size is 0x%04X\n", BOOT_SIZE);
                }
#endif
                n = fread(buf, 1, BOOT_SIZE + 1, in);
                if (!feof(in)) {
                    fprintf(stderr, "fread failure or file \"%s\" too large\n",optarg);
                    fclose(in);
                    return EXIT_FAILURE;
                }

                fclose(in);
                boot_crc32 = crc32buf((char *)buf, BOOT_SIZE-4);
                boot_crc32 = STORE32_LE(boot_crc32);

                *(unsigned int*)(buf+BOOT_SIZE-4) = boot_crc32;
                fwrite(buf, BOOT_SIZE, 1, out);

                return 0;

#endif
			/*pork 20090313 added over*/
			case 'f':
			case 1:
			#ifdef MTKSOC
#if 0
				if(strcmp(optarg,"linux.7z") == 0)
				{
					p->magic = STORE32_LE(TRX_MAGIC);
				}
				else if(strcmp(optarg,"rootfs") == 0)
				{
					p->magic = STORE32_LE(TRX_MAGIC1);
				}
#else
				if(strstr(optarg,"linux.7z"))
				{
					p->magic = STORE32_LE(TRX_MAGIC);
				}
#endif
				else if(strstr(optarg,"rootfs"))
				{
					p->magic = STORE32_LE(TRX_MAGIC1);
				}
				else if(strstr(optarg,"mtklinux")){
					p->magic = STORE32_LE(TRX_MAGIC2);
				}
				else if(strstr(optarg,"romfile.cfg") || strstr(optarg,"romfile_f.cfg") || strstr(optarg,"romfile_epon.cfg") || strstr(optarg,"romfile_")){
					p->magic = STORE32_LE(TRX_MAGIC3);
				}
				else if(strstr(optarg,"zld_notrx.bin"))
				{
					p->magic = STORE32_LE(TRX_MAGIC_BOOT);	// Add uboot magic information
				}
				else 
					p->magic = STORE32_LE(TRX_MAGIC);
			#endif
#if 0
				p->offsets[i++] = STORE32_LE(cur_len);
#endif
				if (!(in = fopen(optarg, "r"))) {
					fprintf(stderr, "can not open \"%s\" for reading\n", optarg);
					usage();
				}
				n = fread(buf + cur_len, 1, maxlen - cur_len, in);
				if (!feof(in)) {
					fprintf(stderr, "fread failure or file \"%s\" too large\n",optarg);
					fclose(in);
					return EXIT_FAILURE;
				}
				fclose(in);
				if(padding == NO_PADDING){
					round = NO_ALIGN;
				}
				else{
					round = ALIGN_4B;
				}
				if (n & (round-1)) {
					memset(buf + cur_len + n, 0, round - (n & (round-1)));
					n += round - (n & (round-1));
				}
				cur_len += n;

				break;
			case 'o':
				ofn = optarg;
				if (ofn && !(out = fopen(ofn, "w"))) {
					fprintf(stderr, "can not open \"%s\" for writing\n", ofn);
					usage();
				}
				break;
			case 'm':
				errno = 0;
				maxlen = strtoul(optarg, &e, 0);
				if (errno || (e == optarg) || *e) {
					fprintf(stderr, "illegal numeric string\n");
					usage();
				}
				round = ALIGN_4B;
				if (maxlen & (round-1)) {
					maxlen += (round - (maxlen & (round-1)));
				}
				if (maxlen < round) {
					fprintf(stderr, "maxlen too small (or wrapped)\n");
					usage();
				}
				if (maxlen > TRX_MAX_LEN) {
					fprintf(stderr, "WARNING: maxlen exceeds default maximum!  Beware of overwriting nvram!\n");
				}
				if (!(buf = realloc(buf,maxlen))) {
					fprintf(stderr, "realloc failed");
					return EXIT_FAILURE;
				}
				break;
			case 'a':
				errno = 0;
				n = strtoul(optarg, &e, 0);
				if (errno || (e == optarg) || *e) {
					fprintf(stderr, "illegal numeric string\n");
					usage();
				}
				if (cur_len & (n-1)) {
					n = n - (cur_len & (n-1));
					memset(buf + cur_len, 0, n);
					cur_len += n;
				}
				break;
			case 'b':
				errno = 0;
				n = strtoul(optarg, &e, 0);
				if (errno || (e == optarg) || *e) {
					fprintf(stderr, "illegal numeric string\n");
					usage();
				}
				if (n < cur_len) {
					fprintf(stderr, "WARNING: current length exceeds -b %d offset\n",n);
				} else {
					memset(buf + cur_len, 0, n - cur_len);
					cur_len = n;
				}
				break;
			case 'u':
				errno = 0;
				n = strtoul(optarg, &e, 0);
				if (errno || (e == optarg) || *e) {
					fprintf(stderr, "illegal numeric string\n");
					usage();
				}
				p->decompAddr= STORE32_LE(n);
				break;
			case 'g':
				if (!(in = fopen("linux_allinone", "r+"))) {
					fprintf(stderr, "can not open file linux_allinone for writing\n");
					usage();
					return 0;
				}

				fseek(in,0, SEEK_END);
				count = ftell(in);
				fseek(in,0, SEEK_SET);

				cur_len = fread(buf, 1, count, in);
				allinone_crc32 = crc32buf((char *)buf, count);
				allinone_crc32 = STORE32_LE(allinone_crc32);  
				crc_ptr = buf+count;

				*crc_ptr = (allinone_crc32 & 0xff000000)>>24;
				*(crc_ptr+1) = (allinone_crc32 & 0x00ff0000)>>16;
				*(crc_ptr+2) = (allinone_crc32 & 0x0000ff00)>>8;
				*(crc_ptr+3) = (allinone_crc32 & 0x000000ff);  

				fwrite(buf+count, 4, 1, in);					
				fclose(in);
				return 0;		
			case 'h':
				if (!(in = fopen("linux_allinone_nand", "r+"))) {
					fprintf(stderr, "can not open file linux_allinone_nand for writing\n");
					usage();
					return 0;
				}

				fseek(in,0, SEEK_END);
				count = ftell(in);
				fseek(in,0, SEEK_SET); 

				cur_len = fread(buf, 1, count, in);
				allinone_crc32 = crc32buf((char *)buf, count);
				allinone_crc32 = STORE32_LE(allinone_crc32);  
				crc_ptr = buf+count;

				*crc_ptr = (allinone_crc32 & 0xff000000)>>24;
				*(crc_ptr+1) = (allinone_crc32 & 0x00ff0000)>>16;
				*(crc_ptr+2) = (allinone_crc32 & 0x0000ff00)>>8;
				*(crc_ptr+3) = (allinone_crc32 & 0x000000ff);  
				
				fwrite(buf+count, 4, 1, in);					
				fclose(in);
				return 0;		
			default:
				usage();
		}
	}

	if (!in) {
		fprintf(stderr, "we require atleast one filename\n");
		usage();
	}
#if 1
	if(flag_ZYXEL) {
		/* Kernel */
		if ((fp_kernel = fopen(kernel_fileName, "rb")) == NULL){
			fprintf(stderr, "fopen '%s' error: %s (errno %d)\n", kernel_fileName, strerror(errno), errno);
			return errno;
		}

		/* Rootfs */
		if(isSupportrootfs) {
			if ((fp_rootfs = fopen(rootfs_fileName, "rb")) == NULL){
				fprintf(stderr, "fopen '%s' error: %s (errno %d)\n", rootfs_fileName, strerror(errno), errno);
				fclose(fp_kernel);
				isSupportrootfs=0;
				return errno;
			}
		}

		/* defcfg */
		if(isSupportDefcfg) {
			if ((fp_defcfg = fopen(defcfg_fileName, "rb")) == NULL){
				fprintf(stderr, "fopen '%s' error: %s (errno %d)\n", defcfg_fileName, strerror(errno), errno);
				fclose(fp_kernel);
				fclose(fp_rootfs);
				isSupportDefcfg=0;
				return errno;
			}
		}

		/* kernel CRC, size and total size */
		while (!feof(fp_kernel)) {
			count = fread(buffer, sizeof(char), BUF_SIZE, fp_kernel);
			if (ferror(fp_kernel)) {
				perror("ZyXEL header: Read kernel image  error");
				return errno;
			}
			kernelCrc = crc32buf(buffer, count);
			kernel_size += count;
		}

		/* rootfs CRC, size and total size */
		if(isSupportrootfs) {
			while (!feof(fp_rootfs)) {
				count = fread(buffer, sizeof(char), BUF_SIZE, fp_rootfs);
				if (ferror(fp_rootfs)) {
					perror( "ZyXEL header: Read rootfs image error" );
					return errno;
				}
				rootfsCrc = crc32buf(buffer, count);
				rootfs_size += count;
			}
		}else {
				rootfsCrc = STORE32_LE(0);
				rootfs_size = STORE32_LE(0);
		}
		/* defcfg CRC, size and total size */
		if(isSupportDefcfg) {
			while (!feof(fp_defcfg)) {
				count = fread(buffer, sizeof(char), BUF_SIZE, fp_defcfg);
				if (ferror(fp_defcfg)) {
					perror( "ZyXEL header: Read error" );
					return errno;
				}
				defcfgCrc = crc32buf(buffer, count);
				defcfg_size += count;
			}
		}else {
			defcfg_size = STORE32_LE(0);
			defcfgCrc = STORE32_LE(0);
		}

		fclose(fp_kernel);
		if(isSupportrootfs)
			fclose(fp_rootfs);
		if(isSupportDefcfg)
			fclose(fp_defcfg);

		p->kernel_len = STORE32_LE(kernel_size);
		p->rootfs_len = STORE32_LE(rootfs_size);
		p->defcfg_len = STORE32_LE(defcfg_size);
		p->kernelChksum = STORE32_LE(kernelCrc);
		p->rootfsChksum = STORE32_LE(rootfsCrc);
		p->defcfgChksum = STORE32_LE(defcfgCrc);

		p->imageSequence = 0;
	}

	if (flag_boot)
	{
		/* Bootloader */
		if ((fp_boot = fopen(boot_fileName, "rb")) == NULL){
			fprintf(stderr, "fopen '%s' error: %s (errno %d)\n", boot_fileName, strerror(errno), errno);
			return errno;
		}
		/* bootloader CRC, size and total size */
		while (!feof(fp_boot)) {
			count = fread(buffer, sizeof(char), BUF_SIZE, fp_boot);
			if (ferror(fp_boot)) {
				perror("ZyXEL header: Read uboot image error");
				return errno;
			}
			bootCrc = crc32buf(buffer, count);
			boot_size += count;
		}

		fclose(fp_boot);

		p->boot_len = STORE32_LE(boot_size);
		p->bootChksum = STORE32_LE(bootCrc);
	}
#endif
	if(padding == NO_PADDING){
		round = NO_ALIGN;
	}
	else{
		round = ALIGN_64K;
	}
	n = cur_len & (round-1);
	if (n) {
		memset(buf + cur_len, 0, round - n);
		cur_len += round - n;
	}
	//p->crc32 = crc32buf((char *) &p->flag_version,
	//					cur_len - offsetof(struct trx_header, flag_version));
		
	p->crc32 = crc32buf((char *)(buf+sizeof(struct trx_header)), (cur_len-sizeof(struct trx_header)));
	p->crc32 = STORE32_LE(p->crc32);
	p->header_len = STORE32_LE(sizeof(struct trx_header));
	//load config value from config file
	if(stat(config_file,&stbuf) == 0){
		#if 1
		get_config("Model",(char *)p->Model,sizeof(p->Model),config_file);
		fprintf(stderr,"Model %s \n",p->Model);
		#endif
		get_config("version",(char *)p->version,sizeof(p->version),config_file);
		fprintf(stderr,"version %s \n",p->version);
		get_config("customerversion",(char *)p->customerversion,sizeof(p->customerversion),config_file);
		fprintf(stderr,"customerversion %s \n",p->customerversion);
	}else{
		fprintf(stderr,"no config file\n");	
	}	
	p->len = STORE32_LE(cur_len);
#if 1
	if(flag_ZYXEL || flag_boot) {
		p->headerChksum = 0;
		p->headerChksum = STORE32_LE( crc32buf((char *)p, sizeof(struct trx_header)) );
	}
	debug_info(p);
	flag_ZYXEL = flag_boot=0;
#endif
	if (!fwrite(buf, cur_len, 1, out) || fflush(out)) {
		fprintf(stderr, "fwrite failed\n");
		return EXIT_FAILURE;
	}

	free(buf);
	fclose(out);

	return EXIT_SUCCESS;
}

void get_config(char *key, char *name, int name_size, char *file_path){

	FILE *fp;
	char buf[256], buf2[256];
	char *point1;

	sprintf(buf2,"%s=",key);
	fp = fopen(file_path,"r");
	if(fp != NULL){
		while(fgets(buf,sizeof(buf),fp) > 0 ){
			point1=strstr(buf,buf2);
			if(point1 != NULL){
				strncpy(name,(point1+strlen(buf2)),name_size);
				break;
			}else{
				continue;	
			}
		}	
	}else{
		fprintf(stderr,"can not open config file\n");	
	}
}
/**********************************************************************/
/* The following was grabbed and tweaked from the old snippets collection
 * of public domain C code. */

/**********************************************************************\
|* Demonstration program to compute the 32-bit CRC used as the frame  *|
|* check sequence in ADCCP (ANSI X3.66, also known as FIPS PUB 71     *|
|* and FED-STD-1003, the U.S. versions of CCITT's X.25 link-level     *|
|* protocol).  The 32-bit FCS was added via the Federal Register,     *|
|* 1 June 1982, p.23798.  I presume but don't know for certain that   *|
|* this polynomial is or will be included in CCITT V.41, which        *|
|* defines the 16-bit CRC (often called CRC-CCITT) polynomial.  FIPS  *|
|* PUB 78 says that the 32-bit FCS reduces otherwise undetected       *|
|* errors by a factor of 10^-5 over 16-bit FCS.                       *|
\**********************************************************************/

/* Copyright (C) 1986 Gary S. Brown.  You may use this program, or
   code or tables extracted from it, as desired without restriction.*/

/* First, the polynomial itself and its table of feedback terms.  The  */
/* polynomial is                                                       */
/* X^32+X^26+X^23+X^22+X^16+X^12+X^11+X^10+X^8+X^7+X^5+X^4+X^2+X^1+X^0 */
/* Note that we take it "backwards" and put the highest-order term in  */
/* the lowest-order bit.  The X^32 term is "implied"; the LSB is the   */
/* X^31 term, etc.  The X^0 term (usually shown as "+1") results in    */
/* the MSB being 1.                                                    */

/* Note that the usual hardware shift register implementation, which   */
/* is what we're using (we're merely optimizing it by doing eight-bit  */
/* chunks at a time) shifts bits into the lowest-order term.  In our   */
/* implementation, that means shifting towards the right.  Why do we   */
/* do it this way?  Because the calculated CRC must be transmitted in  */
/* order from highest-order term to lowest-order term.  UARTs transmit */
/* characters in order from LSB to MSB.  By storing the CRC this way,  */
/* we hand it to the UART in the order low-byte to high-byte; the UART */
/* sends each low-bit to hight-bit; and the result is transmission bit */
/* by bit from highest- to lowest-order term without requiring any bit */
/* shuffling on our part.  Reception works similarly.                  */

/* The feedback terms table consists of 256, 32-bit entries.  Notes:   */
/*                                                                     */
/*  1. The table can be generated at runtime if desired; code to do so */
/*     is shown later.  It might not be obvious, but the feedback      */
/*     terms simply represent the results of eight shift/xor opera-    */
/*     tions for all combinations of data and CRC register values.     */
/*                                                                     */
/*  2. The CRC accumulation logic is the same for all CRC polynomials, */
/*     be they sixteen or thirty-two bits wide.  You simply choose the */
/*     appropriate table.  Alternatively, because the table can be     */
/*     generated at runtime, you can start by generating the table for */
/*     the polynomial in question and use exactly the same "updcrc",   */
/*     if your application needn't simultaneously handle two CRC       */
/*     polynomials.  (Note, however, that XMODEM is strange.)          */
/*                                                                     */
/*  3. For 16-bit CRCs, the table entries need be only 16 bits wide;   */
/*     of course, 32-bit entries work OK if the high 16 bits are zero. */
/*                                                                     */
/*  4. The values must be right-shifted by eight bits by the "updcrc"  */
/*     logic; the shift must be unsigned (bring in zeroes).  On some   */
/*     hardware you could probably optimize the shift in assembler by  */
/*     using byte-swap instructions.                                   */

static const uint32_t crc_32_tab[] = { /* CRC polynomial 0xedb88320 */
0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,
0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,
0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

#define UPDC32(octet,crc) (crc_32_tab[((crc) ^ (octet)) & 0xff] ^ ((crc) >> 8))

uint32_t crc32buf(char *buf, size_t len)
{
      uint32_t crc;

      crc = 0xFFFFFFFF;

      for ( ; len; --len, ++buf)
      {
            crc = UPDC32(*buf, crc);
      }

      return crc;
}

// Converts a hexadecimal string to integer
int xtoi(const char* xs, int* result)
{
 size_t szlen = 2;
 int i, xv, fact;

 if (szlen > 0)
 {
  // Converting more than 32bit hexadecimal value?
  if (szlen>8) return 2; // exit

  // Begin conversion here
  *result = 0;
  fact = 1;

  // Run until no more character to convert
  for(i=szlen-1; i>=0 ;i--)
  {
   if (isxdigit(*(xs+i)))
   {
    if (*(xs+i)>=97)
    {
     xv = ( *(xs+i) - 97) + 10;
    }
    else if ( *(xs+i) >= 65)
    {
     xv = (*(xs+i) - 65) + 10;
    }
    else
    {
     xv = *(xs+i) - 48;
    }
    *result += (xv * fact);
    fact *= 16;
   }
   else
   {
    // Conversion was abnormally terminated
    // by non hexadecimal digit, hence
    // returning only the converted with
    // an error value 4 (illegal hex character)
    return 4;
   }
  }
 }

 // Nothing to convert
 return 1;
}
