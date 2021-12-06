/*
 * (C) Copyright 2011 Quantenna Communications Inc.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <config.h>
#include <command.h>
#include <asm/types.h>
#include <net.h>
#include "ruby.h"

#define UBOOT_ENV_IPADDR	"ipaddr"
#define UBOOT_ENV_SERVERIP	"serverip"
#define UBOOT_ENV_BOOTFILE	"bootfile"
#define UBOOT_ENV_NETRETRY	"netretry"
#define UBOOT_ENV_STR_MAX	32

int do_bootp(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);
int do_tftpb(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);

static char prev_netretry[UBOOT_ENV_STR_MAX] = {0};
static char prev_serverip[UBOOT_ENV_STR_MAX] = {0};
static char prev_bootfile[UBOOT_ENV_STR_MAX] = {0};
static char prev_ipaddr[UBOOT_ENV_STR_MAX] = {0};

#if defined(CONFIG_CMD_BOOTP)
static int get_stage2_bootp(void)
{
	setenv(UBOOT_ENV_IPADDR, NULL);
	setenv(UBOOT_ENV_SERVERIP, NULL);
	setenv(UBOOT_ENV_BOOTFILE, prev_bootfile);
	return do_bootp(NULL, 0, 1, NULL);
}
#endif

static int get_stage2_tftp(void)
{
	setenv(UBOOT_ENV_IPADDR, prev_ipaddr);
	setenv(UBOOT_ENV_SERVERIP, prev_serverip);
	setenv(UBOOT_ENV_BOOTFILE, prev_bootfile);
	return do_tftpb(NULL, 0, 1, NULL);
}

int get_stage2_image(uint32_t method_req, uint32_t *method_used)
{
	int ret;
	const char *prev_netretry_env;
	const char *p;

	/*
	 * temporary copies of ipaddr etc
	 * bootp needs these to be blank, tftp needs these set
	 */
	if ((p = getenv(UBOOT_ENV_IPADDR)) != NULL) {
		strcpy(prev_ipaddr, p);
	}
	if ((p = getenv(UBOOT_ENV_SERVERIP)) != NULL) {
		strcpy(prev_serverip, p);
	}
	if ((p = getenv(UBOOT_ENV_BOOTFILE)) != NULL) {
		strcpy(prev_bootfile, p);
	}
	if ((prev_netretry_env = getenv(UBOOT_ENV_NETRETRY)) != NULL) {
		strcpy(prev_netretry, prev_netretry_env);
	}

	switch (method_req) {
#if defined(CONFIG_CMD_BOOTP)
		case RUBY_BOOT_METHOD_BOOTP:
			ret = get_stage2_bootp();
			if (ret == 0) {
				*method_used = RUBY_BOOT_METHOD_BOOTP;
			}
			break;
#endif
		case RUBY_BOOT_METHOD_TFTP:
			ret = get_stage2_tftp();
			if (ret == 0) {
				*method_used = RUBY_BOOT_METHOD_TFTP;
			}
			break;
		case RUBY_BOOT_METHOD_TRYLOOP:
		default:
			setenv(UBOOT_ENV_NETRETRY, "no");
			while (1) {
				ret = get_stage2_tftp();
				if (ret == 0) {
					*method_used = RUBY_BOOT_METHOD_TFTP;
					break;
				} else if (had_ctrlc()) {
					ret = -1;
					break;
				}
#if defined(CONFIG_CMD_BOOTP)
				ret = get_stage2_bootp();
				if (ret == 0) {
					*method_used = RUBY_BOOT_METHOD_BOOTP;
					break;
				} else if (had_ctrlc()) {
					ret = -1;
					break;
				}
#endif
			}
	}

	setenv(UBOOT_ENV_NETRETRY, prev_netretry_env ? prev_netretry : NULL);

	return ret;
}

void qtn_parse_early_flash_config(int overwrite)
{
	struct early_flash_config *ef = get_early_flash_config(TEXT_BASE);
	char tmp[20];
	if (ef->ipaddr) {
		if (overwrite || getenv(UBOOT_ENV_IPADDR) == NULL) {
			ip_to_string(ef->ipaddr, tmp);
			setenv(UBOOT_ENV_IPADDR, tmp);
			printf("Using '%s' from early config: %s\n", UBOOT_ENV_IPADDR, getenv(UBOOT_ENV_IPADDR));
		}
	}
	if (ef->serverip) {
		if (overwrite || getenv(UBOOT_ENV_SERVERIP) == NULL) {
			ip_to_string(ef->serverip, tmp);
			setenv(UBOOT_ENV_SERVERIP, tmp);
			printf("Using '%s' from early config: %s\n", UBOOT_ENV_SERVERIP, getenv(UBOOT_ENV_SERVERIP));
		}
	}
}

#ifndef RUBY_MINI

static const char *qtn_netboot_method_str(uint32_t method) {
	switch (method) {
		case RUBY_BOOT_METHOD_TFTP:
			return "tftp";
		case RUBY_BOOT_METHOD_BOOTP:
			return "bootp";
		case RUBY_BOOT_METHOD_TRYLOOP:
			return "loop";
		default:
			return "unknown";
	}
}

int do_qtn_netboot (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	uint32_t method_req = RUBY_BOOT_METHOD_TRYLOOP;
	uint32_t this_method_used = 0;
	int run = 1;

	if (argc >= 2) {
		uint32_t i;
		for (i = 0; i < RUBY_BOOT_METHOD_MAX; i++) {
			if (strcmp(argv[1], qtn_netboot_method_str(i)) == 0) {
				method_req = i;
			}
		}
		if (strcmp(argv[1], "tftps1") == 0) {
			method_req = RUBY_BOOT_METHOD_TFTP;
			qtn_parse_early_flash_config(1);
		} else if (strcmp(argv[1], "stage1") == 0) {
			struct early_flash_config *ef = get_early_flash_config(TEXT_BASE);
			method_req = ef->method;
			qtn_parse_early_flash_config(1);
		} else if (strcmp(argv[1], "loops1") == 0) {
			method_req = RUBY_BOOT_METHOD_TRYLOOP;
			qtn_parse_early_flash_config(1);
		} else if (strcmp(argv[1], "loadvars") == 0) {
			run = 0;
			qtn_parse_early_flash_config(1);
		}
	}

	if (run) {
		return get_stage2_image(method_req, &this_method_used);
	} else {
		return 0;
	}
}

U_BOOT_CMD(qtn_netboot, CONFIG_SYS_MAXARGS, 0, do_qtn_netboot,
		"boot with tftp/bootp loop",
		"Optional argument specifies the method. Alternatives are:\n"
		"  tftp     - use tftp to load image\n"
		"  bootp    - use bootp to load image\n"
		"  loop     - use tftp/bootp loop, starting with tftp\n"
		"  tftps1   - use 'ipaddr' and 'serverip' from start of text area\n"
		"              (possibly set by the 1st stage bootloader, or\n"
		"              hard-coded into the image), then use tftp to load image\n"
		"  loops1   - like tftps1, but uses tftp/bootp loop \n"
		"  stage1   - like tftps1, but uses the method specified in start\n"
		"              of text area\n"
		"  loadvars - load 'ipaddr' 'serverip' from text area, without loading\n"
	  );

#endif
