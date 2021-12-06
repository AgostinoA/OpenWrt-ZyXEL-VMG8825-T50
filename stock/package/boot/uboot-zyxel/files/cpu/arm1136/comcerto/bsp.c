/*
 * Copyright (C) 2006 Mindspeed Technologies Inc.
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
#include <common.h>
#include <asm/hardware.h>
#include <asm/arch/bsp.h>

#if defined(CONFIG_COMCERTO_900)
#include "bsp900.c"
#elif defined(CONFIG_COMCERTO_100)
#include "bsp100.c"
#elif defined(CONFIG_COMCERTO_1000)
#include "bsp1000.c"
#else
#error "No Architecture selected!!@" 
#endif

#if defined(CONFIG_M8326XG) || defined(CONFIG_M8325XG) || defined(CONFIG_M8324XG)
extern unsigned char comcerto_part_no[8];
#define FPP_ENABLED 1 /* Default Mode is FPP Enabled */
#define FPP_DISABLED 0 /* FPP Enabled */

#if defined(CONFIG_NOFPP_MODE)
#define FPP_MODE FPP_DISABLED
#endif
#if !defined(CONFIG_NOFPP_MODE)
#define FPP_MODE FPP_ENABLED
#endif
void arch_preboot_os(void)
{
	char buf[256]; 
	char partno[32]; 
	char fppmode[32]; 
	char *cmdline = getenv ("bootargs");

	sprintf (partno, " partno=%s", comcerto_part_no);
	sprintf (fppmode, " fppmode=%d", FPP_MODE);
	if (cmdline) {
		strcpy(buf, cmdline);
		strcat(buf, partno);
		strcat(buf, fppmode);

	} else {
		strcpy(buf, partno);
		strcat(buf, fppmode);
	}
	
	setenv ("bootargs", buf);
}
#endif

