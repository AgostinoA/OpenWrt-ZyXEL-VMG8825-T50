/*
 * (C) Copyright 2002
 * Wolfgang Denk, DENX Software Engineering, <wd@denx.de>
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Alex Zuepke <azu@sysgo.de>
 *
 * Copyright (C) 1999 2000 2001 Erik Mouw (J.A.K.Mouw@its.tudelft.nl)
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

#include <common.h>
#include "serial.h"
#include <asm/arch/rt_mmap.h>

extern unsigned long mips_bus_feq;

/* this function does not need to know the cpu and bus clock after RT3352. the clock is fix at 40Mhz */
void serial_setbrg (void)
{
	//DECLARE_GLOBAL_DATA_PTR;
	unsigned int clock_divisor = 0;
	u32 reg, cpu_clock __maybe_unused = 0;
#if defined(RT2880_ASIC_BOARD) || defined(RT2883_ASIC_BOARD) || defined(RT3052_ASIC_BOARD) || defined(RT3352_ASIC_BOARD) || defined(RT3883_ASIC_BOARD) || defined (RT5350_ASIC_BOARD) || defined(RT6855_ASIC_BOARD) ||  defined(RT6352_ASIC_BOARD) ||  defined(RT71100_ASIC_BOARD)
	u8	clk_sel;
	u8	clk_sel2;
#endif
	reg = RALINK_REG(RT2880_SYSCFG_REG);

	/* 
	 * CPU_CLK_SEL (bit 21:20)
	 */
#ifdef RT2880_FPGA_BOARD
	cpu_clock = 25 * 1000 * 1000;
	mips_bus_feq = cpu_clock / 2;
#elif defined (RT2883_FPGA_BOARD) || defined (RT3052_FPGA_BOARD) || defined (RT3352_FPGA_BOARD) || defined (RT3883_FPGA_BOARD) || defined (RT5350_FPGA_BOARD) || defined (RT6855_FPGA_BOARD) || defined(RT6352_FPGA_BOARD) ||  defined(RT71100_FPGA_BOARD)
	cpu_clock = 40 * 1000 * 1000;
	mips_bus_feq = cpu_clock / 3;
#elif defined(RT2883_ASIC_BOARD) 
	clk_sel = (reg>>18) & 0x03;
	switch(clk_sel) {
		case 0:
			cpu_clock = (380*1000*1000);
			break;
		case 1:
			cpu_clock = (390*1000*1000);
			break;
		case 2:
			cpu_clock = (400*1000*1000);
			break;
		case 3:
			cpu_clock = (420*1000*1000);
			break;
	}
	mips_bus_feq = cpu_clock / 3;
#elif defined(RT3052_ASIC_BOARD)
#if defined(RT3350_ASIC_BOARD)
       //MA10 is floating
        cpu_clock = (320*1000*1000);
#else
	clk_sel = (reg>>18) & 0x01;
	switch(clk_sel) {
		case 0:
			cpu_clock = (320*1000*1000);
			break;
		case 1:
			cpu_clock = (384*1000*1000);
			break;
	}
#endif
	mips_bus_feq = cpu_clock / 3;
#elif defined(RT3352_ASIC_BOARD)
	clk_sel = (reg>>8) & 0x01;
	switch(clk_sel) {
		case 0:
			cpu_clock = (384*1000*1000);
			break;
		case 1:
			cpu_clock = (400*1000*1000);
			break;
	}
	mips_bus_feq = cpu_clock / 3;
#elif defined(RT5350_ASIC_BOARD)
	clk_sel = (reg>>8) & 0x01;
	clk_sel2 = (reg>>10) & 0x01;
	clk_sel |= (clk_sel2 << 1 );

	switch(clk_sel) {
		case 0:
			cpu_clock = (360*1000*1000);
			mips_bus_feq = (120*1000*1000);
			break;
		case 1:
			//reserved
			break;
		case 2:
			cpu_clock = (320*1000*1000);
			mips_bus_feq = (80*1000*1000);
			break;
		case 3:
			cpu_clock = (300*1000*1000);
			mips_bus_feq = (100*1000*1000);
			break;
	}
#elif defined(RT6855_ASIC_BOARD)
	cpu_clock = (400*1000*1000);
	mips_bus_feq = (133*1000*1000);
#elif defined(RT6352_ASIC_BOARD)
	/*FIXME*/
	cpu_clock = (600*1000*1000);
	mips_bus_feq = (133*1000*1000);
#elif defined(RT71100_ASIC_BOARD)
	/*FIXME*/
	cpu_clock = (800*1000*1000);
	mips_bus_feq = (133*1000*1000);
#elif defined(RT3883_ASIC_BOARD)
	clk_sel = (reg>>8) & 0x03;
	switch(clk_sel) {
		case 0:
			cpu_clock = (250*1000*1000);
			break;
		case 1:
			cpu_clock = (384*1000*1000);
			break;
		case 2:
			cpu_clock = (480*1000*1000);
			break;
		case 3:
			cpu_clock = (500*1000*1000);
			break;
	}
#if defined (CONFIG_ENV_IS_IN_SPI_FLASH)
	if ((reg>>17) & 0x1) { //DDR2
		switch(clk_sel) {
			case 0:
				mips_bus_feq = (125*1000*1000);
				break;
			case 1:
				mips_bus_feq = (128*1000*1000);
				break;
			case 2:
				mips_bus_feq = (160*1000*1000);
				break;
			case 3:
				mips_bus_feq = (166*1000*1000);
				break;
		}
	}
	else {
		switch(clk_sel) {
			case 0:
				mips_bus_feq = (83*1000*1000);
				break;
			case 1:
				mips_bus_feq = (96*1000*1000);
				break;
			case 2:
				mips_bus_feq = (120*1000*1000);
				break;
			case 3:
				mips_bus_feq = (125*1000*1000);
				break;
		}
	}
#elif defined ON_BOARD_SDR
        switch(clk_sel) {
                case 0:
                        mips_bus_feq = (83*1000*1000);
                        break;
                case 1:
                        mips_bus_feq = (96*1000*1000);
                        break;
                case 2:
                        mips_bus_feq = (120*1000*1000);
                        break;
                case 3:
                        mips_bus_feq = (125*1000*1000);
                        break;
        }
#elif defined ON_BOARD_DDR2
        switch(clk_sel) {
                case 0:
                        mips_bus_feq = (125*1000*1000);
                        break;
                case 1:
                        mips_bus_feq = (128*1000*1000);
                        break;
                case 2:
                        mips_bus_feq = (160*1000*1000);
                        break;
                case 3:
                        mips_bus_feq = (166*1000*1000);
                        break;
        }
#else
#error undef SDR or DDR
#endif
#elif defined(RT2880_ASIC_BOARD)
	clk_sel = (reg>>20) & 0x03;
	switch(clk_sel) {
#ifdef RT2880_MP
		case 0:
			cpu_clock = (250*1000*1000);
			break;
		case 1:
			cpu_clock = (266*1000*1000);
			break;
		case 2:
			cpu_clock = (280*1000*1000);
			break;
		case 3:
			cpu_clock = (300*1000*1000);
			break;
#else /* RT2880 SHUTTLE */
			case 0:
			cpu_clock = (233*1000*1000);
			break;
		case 1:
			cpu_clock = (250*1000*1000);
			break;
		case 2:
			cpu_clock = (266*1000*1000);
			break;
		case 3:
			cpu_clock = (280*1000*1000);
			break;

		
#endif
	}
	mips_bus_feq = cpu_clock / 2;
#elif defined(RT6855A_ASIC_BOARD) || defined(RT6855A_FPGA_BOARD)
	//use bbu_init_uart() instead, and this is to avoid the compiling error
#else
#error "undefined Platform"
#endif

   	//RALINK_REG(RT2880_SYSCFG_REG) = reg;

	//reset uart lite and uart full
#if defined(RT2880_ASIC_BOARD) || defined(RT2880_FPGA_BOARD)
	*(unsigned long *)(RALINK_SYSCTL_BASE + 0x0034) = cpu_to_le32(1<<12);
#elif defined(RT2883_ASIC_BOARD) || defined(RT2883_FPGA_BOARD) || \
      defined(RT3052_ASIC_BOARD) || defined(RT3052_FPGA_BOARD) || \
      defined(RT3352_ASIC_BOARD) || defined(RT3352_FPGA_BOARD) || \
      defined(RT5350_ASIC_BOARD) || defined(RT5350_FPGA_BOARD) || \
      defined(RT3883_ASIC_BOARD) || defined(RT3883_FPGA_BOARD) || \
      defined(RT6855_ASIC_BOARD) || defined(RT6855_FPGA_BOARD) || \
      defined(RT6352_ASIC_BOARD) || defined(RT6352_FPGA_BOARD) || \
      defined(RT71100_ASIC_BOARD) || defined(RT71100_FPGA_BOARD)
	*(unsigned long *)(RALINK_SYSCTL_BASE + 0x0034) = cpu_to_le32(1<<19|1<<12);
#elif defined(RT6855A_ASIC_BOARD) || defined(RT6855A_FPGA_BOARD)
	//use bbu_init_uart insead and avoid the compiling error
#else
#error "undefined Platform"
#endif
	/* RST Control change from W1C to W1W0 to reset, update 20080812 */
	*(unsigned long *)(RALINK_SYSCTL_BASE + 0x0034) = 0;
	//clock_divisor = (CPU_CLOCK_RATE / SERIAL_CLOCK_DIVISOR / gd->baudrate);
#if defined(RT3883_ASIC_BOARD) || defined(RT3883_FPGA_BOARD) || \
    defined(RT3352_ASIC_BOARD) || defined(RT3352_FPGA_BOARD) || \
    defined(RT5350_ASIC_BOARD) || defined(RT5350_FPGA_BOARD) || \
    defined(RT6855_ASIC_BOARD) || defined(RT6855_FPGA_BOARD) || \
    defined(RT6352_ASIC_BOARD) || defined(RT6352_FPGA_BOARD) || \
    defined(RT71100_ASIC_BOARD) || defined(RT71100_FPGA_BOARD)
	clock_divisor = (40*1000*1000/ SERIAL_CLOCK_DIVISOR / CONFIG_BAUDRATE);
#else
	clock_divisor = (mips_bus_feq/ SERIAL_CLOCK_DIVISOR / CONFIG_BAUDRATE);
#endif

	IER(CFG_RT2880_CONSOLE) = 0;					/* Disable for now */
	FCR(CFG_RT2880_CONSOLE) = 0;					/* No fifos enabled */

	/* set baud rate */
	LCR(CFG_RT2880_CONSOLE) = LCR_WLS0 | LCR_WLS1 | LCR_DLAB;
	DLL(CFG_RT2880_CONSOLE) = clock_divisor & 0xffff;
	LCR(CFG_RT2880_CONSOLE) = LCR_WLS0 | LCR_WLS1;
}

#if 0
static unsigned long uclk_20M[13]={ // 65000*(b*16*1)/2000000
	59904,          // Baud rate 115200
	29952,          // Baud rate 57600
	19968,          // Baud rate 38400
	14976,          // Baud rate 28800
	9984,           // Baud rate 19200
	7488,           // Baud rate 14400
	4992,           // Baud rate 9600
	2496,           // Baud rate 4800
	1248,           // Baud rate 2400
	624,            // Baud rate 1200
	312,            // Baud rate 600
	156,            // Baud rate 300
	57              // Baud rate 110
};
#endif

#if defined(RT6855A_ASIC_BOARD) || defined(RT6855A_FPGA_BOARD)
void bbu_uart_init(void)
{
	DECLARE_GLOBAL_DATA_PTR;
	//int i;
	unsigned long div_x, div_y;
	unsigned long word;
	int baudrate;

	if ( gd->baudrate <= 0 ) {
		baudrate = CONFIG_BAUDRATE;
	}

	// Set FIFO controo enable, reset RFIFO, TFIFO, 16550 mode, watermark=0x00 (1 byte)
	ra_outb(CR_UART_FCR, (0x0f|(0x0<<6)));

	// Set modem control to 0
	ra_outb(CR_UART_MCR, 0x0);

	// Disable IRDA, Disable Power Saving Mode, RTS , CTS flow control
	ra_outb(CR_UART_MISCC, 0x0);

	// Set interrupt Enable to, enable Tx, Rx and Line status
	/*ra_outb(CR_UART_IER, 0x01);*/

	/* access the bardrate divider */

	ra_outb(CR_UART_LCR, LCR_DLAB);

	div_y = 65000;
	div_x = 65*(baudrate*16*1)/2000;
//	div_x = uclk_20M[1];
	word = (div_x<<16)|div_y;
	ra_outl(CR_UART_XYD, word);

	/* Set Baud Rate Divisor to 1*16 */
	ra_outb(CR_UART_BRDL, 0x01);
	ra_outb(CR_UART_BRDH, 0x00);

	/* Set DLAB = 0, clength = 8, stop =1, no parity check  */
	ra_outb(CR_UART_LCR, LCR_WLS0 | LCR_WLS1);
}
#endif
/*
 * Initialise the serial port with the given baudrate. The settings
 * are always 8 data bits, no parity, 1 stop bit, no start bits.
 *
 */
int serial_init (void)
{
#if defined(RT6855A_ASIC_BOARD) || defined(RT6855A_FPGA_BOARD)
	bbu_uart_init();
#else
	serial_setbrg ();
#endif
	return (0);
}


/*
 * Output a single byte to the serial port.
 */
void serial_putc (const char c)
{
#if defined (RT6855A_FPGA_BOARD) || defined (RT6855A_ASIC_BOARD) 
	while (!(ra_inb(CR_UART_LSR) & LSR_TEMT));
	ra_outb(CR_UART_THR, c);
	if (c == '\n')
		serial_putc ('\r');
#else
	/* wait for room in the tx FIFO on UART */
	while ((LSR(CFG_RT2880_CONSOLE) & LSR_TEMT) == 0);

	TBR(CFG_RT2880_CONSOLE) = c;

	/* If \n, also do \r */
	if (c == '\n')
		serial_putc ('\r');
#endif
}

/*
 * Read a single byte from the serial port. Returns 1 on success, 0
 * otherwise. When the function is succesfull, the character read is
 * written into its argument c.
 */
int serial_tstc (void)
{
#if defined (RT6855A_FPGA_BOARD) || defined (RT6855A_ASIC_BOARD) 
	return (ra_inb(CR_UART_LSR) & LSR_DR);
#else
	return LSR(CFG_RT2880_CONSOLE) & LSR_DR;
#endif
}

/*
 * Read a single byte from the serial port. Returns 1 on success, 0
 * otherwise. When the function is succesfull, the character read is
 * written into its argument c.
 */
int serial_getc (void)
{
#if defined (RT6855A_FPGA_BOARD) || defined (RT6855A_ASIC_BOARD) 
	while (!(ra_inb(CR_UART_LSR) & LSR_DR));
	return (char) (ra_inb(CR_UART_RBR) & 0xff);
#else
	while (!(LSR(CFG_RT2880_CONSOLE) & LSR_DR));
	return (char) RBR(CFG_RT2880_CONSOLE) & 0xff;
#endif
}

void
serial_puts (const char *s)
{
	while (*s) {
		serial_putc (*s++);
	}
}
