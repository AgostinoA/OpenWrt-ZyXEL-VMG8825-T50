/*
 * Copyright Codito Technologies (www.codito.com)
 *
 * cpu/arc/serial.c
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

#include <common.h>
#include <asm/serial.h>

volatile aa3_uart *uart = (aa3_uart *) UART_BASEADDR;

/*
 * Sets baudarate
 */
void serial_setbrg (void)
{
		
	DECLARE_GLOBAL_DATA_PTR;
	int arc_console_baud = gd->cpu_clk/(gd->baudrate*4) - 1;
//	int arc_console_baud = 65000000 /(57600*4) - 1;

	/* Set the baud rate */
	uart->baudl = arc_console_baud & 0xff;
        uart->baudh = (arc_console_baud & 0xff00) >> 8;
}

/*
 * Intialise the serial port with given baudrate
 */
int serial_init (void)
{
	serial_setbrg ();

	return 0;
}

/*
 * Output a single byte to the serial port.
 */
void serial_putc (const char c)
{
//    volatile char * u = 0xc0fc1010;

//    *u = 65;

	if (c == '\n') 
		serial_putc('\r');	       		
	
	/* Wait till dataTx register is empty */
	while (!(uart->status & UART_TXEMPTY));
	
	uart->data = c;
}

/*
 * Read a single byte from the serial port. Returns 1 on success, 0
 * otherwise 0.
 */
int serial_tstc (void)
{
	return !(uart->status & UART_RXEMPTY);
}

/*
 * Read a single byte from the serial port. 
 */
int serial_getc (void)
{
	unsigned char ch;	
	
	/* Wait till character is placed in fifo */
	while (uart->status & UART_RXEMPTY);
	
	/* Also check for overflow errors */
	if (uart->status & UART_OVERFLOW_ERR)
	       return 0;	
	
	ch = uart->data & 0x00ff;
	return ((int)ch);
}

void serial_puts (const char *s)
{
	while (*s) {
		serial_putc (*s++);
	}
}

