/*
 * (C) Copyright 2010 Quantenna Communications Inc.
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


#include <config.h>

#ifdef CONFIG_SHOW_BOOT_PROGRESS
void printf(const char *fmt, ...);
/* Keep function in separated translation module and
 * include as little header files as possible.
 * The reason for it - I need this function
 * to has "strong" reference, while this function
 * is marked as "weak" in uboot header file
 * (as result which function comes to resulted
 * binary depends on linker command line -
 * which is too error prone).
 */
void show_boot_progress(int status)
{
	printf("Boot reached stage %d\n", status);
}
#endif

/* Need for module linking. Keep and call it even if it is empty. */
void board_progress_init(void)
{
}

