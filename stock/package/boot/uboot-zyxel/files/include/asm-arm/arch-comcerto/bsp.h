/*
 * (C) Copyright 2006
 * Mindspeed Technologies, Inc. <www.mindspeed.com>
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
 */

#ifndef _BSP_H
#define _BSP_H

#include <config.h>

#if defined(CONFIG_COMCERTO_530)
#include "bsp_530.h"
#elif defined(CONFIG_COMCERTO_515) || defined(CONFIG_COMCERTO_800)
#include "bsp_515.h"
#elif defined(CONFIG_COMCERTO_100)
#include "bsp_100.h"
#elif defined(CONFIG_COMCERTO_1000)
#include "bsp_1000.h"
#else
#error "No architecture selected!!!"
#endif


#endif /* _BSP_H */
