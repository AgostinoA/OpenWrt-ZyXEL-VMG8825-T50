/*
 * SOC specific setup info
 *
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <config.h>
#include <version.h>
#include <asm/arch/hardware.h>


.globl lowlevel_init
lowlevel_init:
	ldr	sp, TMP_STACK /* set up a temporary stack */

	stmdb	sp!, {ip, lr}
	bl	bsp_init	/* go setup pll, memory */
	ldmia	sp!, {ip, pc}	/* restore registers and return to caller */

	/* the literal pools origin */
	.ltorg
TMP_STACK:
	.word	CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET
