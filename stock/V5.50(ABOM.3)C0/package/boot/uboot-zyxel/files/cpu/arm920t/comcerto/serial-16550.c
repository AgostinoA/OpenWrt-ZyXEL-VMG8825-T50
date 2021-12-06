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

#include <common.h>
#include <asm/io.h>
#include <asm/arch/bsp.h>
#include <asm/hardware.h>

DECLARE_GLOBAL_DATA_PTR;

#if !defined(CONFIG_UART0) && !defined(CONFIG_UART1)
#error must define one of CONFIG_UART0 or CONFIG_UART1
#endif


struct uart_regs {
	volatile u32 data;	/* Receive/Transmit data register */
	volatile u32 ier;	/* Interrupt Enable register */
	volatile u32 iir_fcr;	/* Interrupt Identity register / FIFO Control register */
	volatile u32 lcr;	/* Line Control register */
	volatile u32 mcr;	/* Modem Control register */
	volatile u32 lsr;	/* Line Status register */
	volatile u32 msr;	/* Modem Status register */
	volatile u32 sr;	/* Scratch register */
};

struct uart_dl_regs {
	volatile u32 dll;	/* Divisor Latch (Low) */
	volatile u32 dlh;	/* Divisor Latch (High) */
};


/* Interrupt Enable Register */
/* UART 16550 */
#define IER_RDI			(1 << 0)	/* Enable Received Data Available Interrupt */
#define IER_THRI		(1 << 1)	/* Enable Transmitter holding register Interrupt */
#define IER_RLSI		(1 << 2)	/* Enable receiver line status Interrupt */
#define IER_MSI			(1 << 3)	/* Enable Modem status Interrupt */

#define IIR_FIFOES1		(1 << 7)	/* FIFO Mode Enable Status */
#define IIR_FIFOES0		(1 << 6)	/* FIFO Mode Enable Status */
#define IIR_TOD			(1 << 3)	/* Time Out Detected */
#define IIR_IID2			(1 << 2)	/* Interrupt Source Encoded */
#define IIR_IID1			(1 << 1)	/* Interrupt Source Encoded */
#define IIR_IP				(1 << 0)	/* Interrupt Pending (active low) */

/* UART 16550 FIFO Control Register */
#define FCR_FIFOEN			(1 << 0)
#define FCR_RCVRRES			(1 << 1)
#define FCR_XMITRES			(1 << 2)

#define LCR_CHAR_LEN_5		0x00	  /* default */
#define LCR_CHAR_LEN_6		0x01
#define LCR_CHAR_LEN_7		0x02
#define LCR_CHAR_LEN_8		0x03
#define LCR_TWO_STOP		(1 << 2)  /* Two stop bit! */
#define LCR_PEN			(1 << 3)  /* Parity Enable */
#define LCR_EPS			(1 << 4)  /* Even Parity Select */
#define LCR_PS			(1 << 5)  /* Enable Parity  Stuff */
#define LCR_SBRK		(1 << 6)  /* Start Break */
#define LCR_PSB			(1 << 7)  /* Parity Stuff Bit */
#define LCR_DLAB		(1 << 7)  /* UART 16550 Divisor Latch Assess */

#define LSR_RXFIFO_ERROR		(1 << 7)	/* FIFO Error Status */
#define LSR_TEMT			(1 << 6)	/* Transmitter Empty */
#define LSR_THRE			(1 << 5)	/* Transmit Data Request */
#define LSR_BI			(1 << 4)	/* Break Interrupt */
#define LSR_FE			(1 << 3)	/* Framing Error */
#define LSR_PE			(1 << 2)	/* Parity Error */
#define LSR_OE			(1 << 1)	/* Overrun Error */
#define LSR_DR			(1 << 0)	/* Data Ready */

#ifdef CONFIG_UART0
struct uart_regs *uart = (struct uart_regs *) UART0_BASEADDR;
struct uart_dl_regs *uart_dl = (struct uart_dl_regs *) UART0_BASEADDR;
#else
struct uart_regs * uart = (struct uart_regs *) UART1_BASEADDR;
struct uart_dl_regs * uart_dl = (struct uart_dl_regs *) UART1_BASEADDR;
#endif

void serial_setbrg (void)
{
	int baudrate;
	unsigned int reg;
	unsigned int clk = SoC_clk_amba_get();

	if ((baudrate = gd->baudrate) <= 0)
		baudrate = CONFIG_BAUDRATE;

	reg = clk / (baudrate * 16);
	uart->lcr |= LCR_DLAB;			/* Enable Divisor Latch access */
	uart_dl->dll = reg & 0xFF;		/* Set Divisor Latch Low */
	uart_dl->dlh = (reg >> 8) & 0xFF;	/* Set Divisor Latch high */
	uart->lcr &= ~LCR_DLAB;			/* Disable Divisor Latch access */
}

int serial_init (void)
{
#ifdef CONFIG_UART1
	SoC_ioctrl_cfg(IOCTRL_UART1, 1);
	SoC_ioctrl_cfg(IOCTRL_UART0, 0);
#endif

	uart->ier = 0x00;
	uart->iir_fcr = 0x00;
	uart->lcr = LCR_CHAR_LEN_8;

	serial_setbrg ();

	uart->data = 0;
	uart->iir_fcr = FCR_RCVRRES | FCR_XMITRES | FCR_FIFOEN;

	return (0);
}

void serial_putc (const char c)
{
	/* wait for room in the tx FIFO */
	while ((uart->lsr & LSR_THRE) == 0) ;
	uart->data = c;
	if (c == '\n')
		serial_putc ('\r');
}

void serial_puts (const char *s)
{
	while (*s) {
		serial_putc (*s++);
	}
}

int serial_getc (void)
{
	while ((uart->lsr & LSR_DR) == 0);
		return (char)uart->data & 0xff;
}

int serial_tstc (void)
{
	return uart->lsr & LSR_DR;
}
