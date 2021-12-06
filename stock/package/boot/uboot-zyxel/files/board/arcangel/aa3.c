/*
 * Copyright Codito Technologies (www.codito.com) 
 *
 *  board/aa3/aa3.c
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

#include <linux/types.h>
#include <config.h>
#include <asm/global_data.h>	/* For global data structre */
#include <asm/sys_ctrl.h>

#define TIMER0_LIMIT 0xffffffff         /* Maximum limit for timer      */

static ulong timestamp;

#ifdef CONFIG_ARC_SYS_CTRL_DEV
static sys_ctrl_reg_t *sys_ctrl_dev = SYS_CTRL_DEVICE_ADDRESS;
#endif

/*      Function to start timer from 'count'    */

void set_timer (ulong count)
{
    /* Set up the LIMIT0 , COUNT0 and CONTROL0 registers for timer 0  without interrupt	*/
    write_new_aux_reg(ARC_REG_TIMER0_CTRL, 0);
    write_new_aux_reg(ARC_REG_TIMER0_LIMIT, TIMER0_LIMIT);
    write_new_aux_reg(ARC_REG_TIMER0_CTRL, 2);
    write_new_aux_reg(ARC_REG_TIMER0_CNT, count);
}

/*      Function to get the current count value         */
ulong get_timer (ulong base)
{
    /* Read the count value from COUNT0     */
    timestamp = read_new_aux_reg(ARC_REG_TIMER0_CNT);
    return timestamp - base;
}

void reset_timer(void)
{
    set_timer(0);
}

void uninit_timer(void)
{
    write_new_aux_reg(ARC_REG_TIMER0_LIMIT,0xffffff);
    write_new_aux_reg(ARC_REG_TIMER0_CNT,0);
    write_new_aux_reg(ARC_REG_TIMER0_CTRL,0);
}

/*      Delay function  */

void udelay (unsigned long usec)
{
    DECLARE_GLOBAL_DATA_PTR;
    ulong uTicks;
    set_timer(0);
    uTicks = (gd->cpu_clk/1000000) * usec;
    /* Continue looping till the timer count is more thean the required delay	*/
    while(get_timer(0) < uTicks); 
}

void show_boot_progress (int status)
{
#ifdef CONFIG_ARC_SYS_CTRL_DEV
    sys_ctrl_dev->leds = status;
#endif
}

#ifdef CONFIG_ARC_SYS_CTRL_DEV
static unsigned read_dip_switches(void)
{
    return sys_ctrl_dev->dip_switches;
}

static unsigned read_clk(void)
{
    int unsigned sw = read_dip_switches();
    static unsigned clk_tbl[4] = { 95, 85, 75, 65};

    sw >>= 2;
    sw &= 0x3;
    return 1000000 * clk_tbl[sw];
}
#else
static unsigned read_clk(void)
{
    return CONFIG_ARC_CLK;
}
#endif

void disable_rom(void)
{
#ifdef CONFIG_ARC_SYS_CTRL_DEV
    sys_ctrl_dev->mem_cfg1 = 0;
#endif
}

int board_init(void)
{
    DECLARE_GLOBAL_DATA_PTR;

    disable_rom();

    gd->cpu_clk = read_clk();
    reset_timer();	/* Intialise the timer */

    gd->bd->bi_boot_params = TEXT_BASE - CONFIG_SYS_MALLOC_LEN + CONFIG_SYS_ENV_SIZE; /* address of kernel parameters */

    return 0;
}
