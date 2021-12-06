/*
 *  Copyright Codito Technologies (www.codito.com) 
 *
 *  cpu/arc/interrupts.c
 *
 *  Copyright (C) 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 * 
 * Authors : Sandeep Patil (sandeep.patil@codito.com)
 * 			 Pradeep Sawlani (pradeep.sawlani@codito.com)
 */
#include <asm/arcregs.h> 

void disable_interrupts(void)
{
	unsigned int status;
	status = read_new_aux_reg(ARC_REG_STATUS32);
	status &= STATUS_DISABLE_INTERRUPTS;
/*	write_new_aux_reg(ARC_REG_STATUS32,status); */
	__asm__ __volatile__ (
		"FLAG %0"
		:
	       	:"r"(status)
		);

}

void enable_interrupts(void)
{
	unsigned int status ;
	status = read_new_aux_reg(ARC_REG_STATUS32);
	status |= STATUS_E1_MASK;
	status |= STATUS_E2_MASK;
	write_new_aux_reg(ARC_REG_STATUS32,status);
}

