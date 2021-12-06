/*
 *  include/asm-arc/arch-arc/platform.h
 *
 *  Copyright (c) Quantenna Communications Incorporated 2007.
 *  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * This file holds only U-Boot specific platform definitions.
 * Definitions that are common to Linux and U-Boot are held
 * in common/ruby_platform.h.
 */

#ifndef __INCLUDE_ASM_ARCH_PLATFORM_H
#define __INCLUDE_ASM_ARCH_PLATFORM_H

/* Dummy architecture number */

#ifndef MACH_TYPE_UMS
	#define MACH_TYPE_UMS (0x4d3)
#endif

#include "ruby_platform.h"

#ifndef __ASSEMBLY__
void io_copy_from(void *dst, void *src, int nbytes);
void io_copy_to(void *dst, void *src, int nbytes);
#endif

#endif

