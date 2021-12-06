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


#ifndef __RUBY_UBOOT_CONFIG_H
#define __RUBY_UBOOT_CONFIG_H

#include "ruby_mem.h"
#include "ruby_partitions.h"

/* generic define for RUBY */
#define CONFIG_RUBY_BOARD

/* Commands */
#define CONFIG_CMD_NET
#define CONFIG_CMD_PING
#define CONFIG_CMD_INTR

//#define CONFIG_BOOTP_RANDOM_DELAY

/* Suppress inclusion of unwanted functions by pretending we have them */
#define __HAVE_ARCH_STRDUP

/* No flash support */
#define CONFIG_SYS_NO_FLASH

#define CONFIG_ARC_STACK_BEGIN		(RUBY_SRAM_BEGIN + RUBY_SRAM_SIZE - 4 - CONFIG_ARC_MUC_STACK_SIZE) /* Stack grows backward; put stack to the end of SRAM, before the MuC stack */

/* Misc parameters */
#define CONFIG_SYS_HZ			1000
#define CONFIG_SYS_BAUDRATE_TABLE	{ RUBY_SERIAL_BAUD }
#define CONFIG_BAUD_RATE		RUBY_SERIAL_BAUD

/* Console */
#define CONFIG_SYS_MAXARGS		16 /* Max number of command args */

/* Environment */
#define	CONFIG_ENV_IS_NOWHERE
#define CONFIG_ENV_SIZE			512

#define __MK_STR(_x)	#_x
#define MKSTR(_x)	__MK_STR(_x)

/* Ethernet */
#ifdef CONFIG_CMD_NET
	#define CONFIG_NET_MULTI		1
	#define CONFIG_ARASAN_GBE		1
	#define CONFIG_ETHADDR			00:26:86:00:00:00	/* Quantenna OUI */
	#define CONFIG_IPADDR			1.1.1.2
	#define CONFIG_SERVERIP			1.1.1.1
	#define CONFIG_BOOTFILE			"u-boot.bin"
	#define CONFIG_NET_RETRY_COUNT		2
	#define CONFIG_BOOTP_QTN_VENDORINFO
#endif


#ifndef __ASSEMBLY__

#include <linux/types.h>

#endif	// __ASSEMBLY__

/* Reduce the MTU size to 1460 because in vlan mode, the packets will be
 * 1518 bytes which exceed the EMAC's capability and these packets will
 * be discard silently.
 */
#define CONFIG_TFTP_BLOCKSIZE   1460

#endif // #ifndef __RUBY_UBOOT_CONFIG_H

