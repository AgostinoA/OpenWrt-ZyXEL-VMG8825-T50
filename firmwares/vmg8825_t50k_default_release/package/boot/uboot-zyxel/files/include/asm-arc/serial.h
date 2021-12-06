/*
 * Copyright Codito Technologies (www.codito.com) 
 *
 *  include/asm-arc/serial.h
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

#ifndef	_ASM_ARC_SERIAL_H
#define	_ASM_ARC_SERIAL_H

#include <config.h>

typedef volatile struct {
  volatile int id0;
  volatile int id1;
  volatile int id2;
  volatile int id3;
  volatile int data;
  volatile int status;
  volatile int baudl;
  volatile int baudh;
} aa3_uart __attribute__((packed));

/* 
 * Define the number of ports supported and their irqs.
 */
#define NR_PORTS 1

#define UART_RXENB	0x04
#define UART_RXEMPTY	0x20
#define UART_FRAME_ERR	0x01
#define UART_OVERFLOW_ERR  0x02

#define UART_TXENB      0x40
#define UART_TXEMPTY   0x80

/* UART control registers */
#define ARC_UART_CREG_DATATX	UART_BASEADDR + 0x4
#define ARC_UART_CREG_DATARX	UART_BASEADDR + 0x4
#define ARC_UART_CREG_STATUS	UART_BASEADDR + 0x5
#endif	/* _ASM_ARC_SERIAL_H */
