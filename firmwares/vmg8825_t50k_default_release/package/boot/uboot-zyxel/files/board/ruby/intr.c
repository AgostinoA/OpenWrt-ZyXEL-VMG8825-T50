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


#include "ruby.h"

#ifndef CONFIG_CMD_INTR

void board_intr_init(void)
{
}

#else

void board_intr_init(void)
{
	/* Symbol defined in linker script */
	extern unsigned long __vectors_start;

	/* Instruct CPU where vectors are placed */
	write_new_aux_reg(ARC_REG_INTR_VEC_BASE, &__vectors_start);

	/* Disable all interrupts */
	write_new_aux_reg(ARC_REG_INTR_ENABLE, 0);
}

//-------------------------------------------------------

#define read_ilink1() \
	({ unsigned int __ret; \
		__asm__ __volatile__("mov %0, ilink1" : "=r"(__ret));\
		__ret; \
	 })

#define read_ilink2() \
	({ unsigned int __ret; \
		__asm__ __volatile__("mov %0, ilink2" : "=r"(__ret));\
		__ret; \
	})

#define read_eret() \
	({ unsigned int __ret; \
		__asm__ __volatile__("lr %0, [eret]" : "=r"(__ret));\
		__ret;\
	})

//-------------------------------------------------------

static void intr_EV_do_reset(const char *descr)
{
	char s[128]; /* unfortunately uboot does not have snprintf(), so make sure buffer is big enough */
	sprintf(s, "%s: ilink1=0x%x ilink2=0x%x eret=0x%x", descr, read_ilink1(), read_ilink2(), read_eret());
	s[sizeof(s) - 1] = '\0';

	board_reset(s);
}

void intr_EV_NotImpl(void)
{
	intr_EV_do_reset("EV_NotImpl");
}

void intr_EV_Reset(void)
{
	intr_EV_do_reset("EV_Reset");
}

void intr_EV_MemErr(void)
{
	intr_EV_do_reset("EV_MemErr");
}

void intr_EV_InstrErr(void)
{
	intr_EV_do_reset("EV_InstrErr");
}

void intr_EV_MachineCheck(void)
{
	intr_EV_do_reset("EV_MachineCheck");
}

void intr_EV_TLBMissI(void)
{
	intr_EV_do_reset("EV_TLBMissI");
}

void intr_EV_TLBMissD(void)
{
	intr_EV_do_reset("EV_TLBMissD");
}

void intr_EV_TLBProtV(void)
{
	intr_EV_do_reset("EV_TLBProtV");
}

void intr_EV_PrivilegeV(void)
{
	intr_EV_do_reset("EV_PrivilegeV");
}

void intr_EV_Trap(void)
{
	intr_EV_do_reset("EV_Trap");
}

void intr_EV_Extension(void)
{
	intr_EV_do_reset("EV_Extension");
}

//-------------------------------------------------------

#endif // #ifndef CONFIG_CMD_INTR

