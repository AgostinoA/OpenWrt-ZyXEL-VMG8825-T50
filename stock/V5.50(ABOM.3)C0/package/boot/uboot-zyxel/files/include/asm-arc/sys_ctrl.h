#ifndef _ARC_SYS_CTRL_H_
#define _ARC_SYS_CTRL_H_

/* register definitions for Aurora SYS_CTRL module 
 * (C) ARC International 2007
 * Amnon Cohen, January 2007 
 */

typedef struct {
    volatile unsigned id;
    volatile unsigned mem_cfg1;
    volatile unsigned bri_ctrl;
    volatile unsigned tp_rst;
    volatile unsigned pio_in;
    volatile unsigned pio_out;
    volatile unsigned pio_ctrl;
    volatile unsigned buttons;
    volatile unsigned dip_switches;
    volatile unsigned leds;
} sys_ctrl_reg_t;

#define SYS_CTRL_DEVICE_ADDRESS (sys_ctrl_reg_t *)0xC0FCF000

#endif

