/*
 ***************************************************************************
 * Ralink Tech Inc.
 * 4F, No. 2 Technology 5th Rd.
 * Science-based Industrial Park
 * Hsin-chu, Taiwan, R.O.C.
 *
 * (c) Copyright, Ralink Technology, Inc.
 *
 *  This program is free software; you can redistribute  it and/or modify it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License along
 *  with this program; if not, write  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *
 ***************************************************************************
 */

#ifndef __RT2880_GPIO_H__
#define __RT2880_GPIO_H__

#include <asm/arch/rt_mmap.h>

#define RALINK_GPIO_LED_LOW_ACT		1

#define GPIO_TRACE_NONE		0
#define GPIO_TRACE_IO		1
#define GPIO_TRACE_INT		2
#define GPIO_TRACE_ALL		3

/*
 * ioctl commands
 */
#define	RALINK_GPIO_SET_DIR		0x01
#define RALINK_GPIO_SET_DIR_IN		0x11
#define RALINK_GPIO_SET_DIR_OUT		0x12
#define	RALINK_GPIO_READ		0x02
#define	RALINK_GPIO_WRITE		0x03
#define	RALINK_GPIO_SET			0x21
#define	RALINK_GPIO_CLEAR		0x31
#define	RALINK_GPIO_READ_BIT		0x04
#define	RALINK_GPIO_WRITE_BIT		0x05
#define	RALINK_GPIO_READ_BYTE		0x06
#define	RALINK_GPIO_WRITE_BYTE		0x07
#define	RALINK_GPIO_READ_INT		0x02 //same as read
#define	RALINK_GPIO_WRITE_INT		0x03 //same as write
#define	RALINK_GPIO_SET_INT		0x21 //same as set
#define	RALINK_GPIO_CLEAR_INT		0x31 //same as clear
#define RALINK_GPIO_ENABLE_INTP		0x08
#define RALINK_GPIO_DISABLE_INTP	0x09
#define RALINK_GPIO_REG_IRQ		0x0A
#define RALINK_GPIO_LED_SET		0x41
#define	RALINK_GPIO3116_SET_DIR		0x51
#define RALINK_GPIO3116_SET_DIR_IN	0x13
#define RALINK_GPIO3116_SET_DIR_OUT	0x14

/*
 * Address of RALINK_ Registers
 */
#define RALINK_SYSCTL_ADDR		RALINK_SYSCTL_BASE	// system control
#define RALINK_REG_RSTCTRL2		(RALINK_SYSCTL_ADDR + 0x834)	// RSTCTRL2
#define RALINK_REG_GPIOMODE		(RALINK_SYSCTL_ADDR + 0x860)	// GPIO share scheme

#define RALINK_IRQ_ADDR			RALINK_INTCL_BASE
#define RALINK_REG_INTENA		(RALINK_IRQ_ADDR + 0x04)	// IMR
#define RALINK_REG_INTDIS		RALINK_REG_INTENA		// IMR

#define RALINK_PRGIO_ADDR		RALINK_PIO_BASE // Programmable I/O
#define RALINK_REG_PIODIR		(RALINK_PRGIO_ADDR + 0x0)	// GPIOCTRL
#define RALINK_REG_PIODATA		(RALINK_PRGIO_ADDR + 0x04)	// GPIODATA
#define RALINK_REG_PIOINT		(RALINK_PRGIO_ADDR + 0x08)	// GPIOINT
#define RALINK_REG_PIOEDGE		(RALINK_PRGIO_ADDR + 0x0C)	// GPIOINTEDG
#define RALINK_REG_GPIOOE		(RALINK_PRGIO_ADDR + 0x14)
#define RALINK_REG_PIO3116DIR		(RALINK_PRGIO_ADDR + 0x20)	// GPIOCTRL1
#define RALINK_REG_SGPIOLEDDATA		(RALINK_PRGIO_ADDR + 0x24)

/*
 * Values for the GPIOMODE Register
 */
#define RALINK_GPIOMODE_PCM		0x01	// GPIO_PCM
#define RALINK_GPIOMODE_SPICS1		0x02	// GPIO_SPI_CS1_N
#define RALINK_GPIOMODE_SPICS2		0x04	// GPIO_SPI_CS2_N
#define RALINK_GPIOMODE_SPICS3		0x08	// GPIO_SPI_CS3_N
#define RALINK_GPIOMODE_SPICS4		0x10	// GPIO_SPI_CS4_N
#define RALINK_GPIOMODE_SPICS5		0x20	// GPIO_SPI_CS5_N
#define RALINK_GPIOMODE_UARTF		0x40	// GPIO_UART2
#define RALINK_GPIOMODE_I2S		0x80	// GPIO_I2S
#define RALINK_GPIOMODE_NFD		0x100	// GPIO_NFD_DATA_BUS
#define RALINK_GPIOMODE_EPHY0		0x200	// GPIO_EPHY_LED0
#define RALINK_GPIOMODE_EPHY1		0x400	// GPIO_EPHY_LED1
#define RALINK_GPIOMODE_EPHY2		0x800	// GPIO_EPHY_LED2
#define RALINK_GPIOMODE_EPHY3		0x1000	// GPIO_EPHY_LED3
#define RALINK_GPIOMODE_EPHY4		0x2000	// GPIO_EPHY_LED4
#define RALINK_GPIOMODE_I2C		0x8000	// GPIO_I2C

// if you would like to enable GPIO mode for other pins, please modify this value
// !! Warning: changing this value may make other features(MDIO, PCI, etc) lose efficacy
#define RALINK_GPIOMODE_DFT		(RALINK_GPIOMODE_UARTF)

/*
 * bit is the unit of length
 */
#if defined (CONFIG_RT6855A_PCIE_PORT0_ENABLE)
#define RALINK_GPIO_NUMBER		33
#else
#define RALINK_GPIO_NUMBER		32
#endif
#define RALINK_GPIO_DATA_MASK		0x00FFFFFF
#define RALINK_GPIO_DATA_LEN		32
#define RALINK_GPIO_DIR_IN		0
#define RALINK_GPIO_DIR_OUT		1
#define RALINK_GPIO_DIR_ALLIN		0
#define RALINK_GPIO_DIR_ALLOUT		0x00FFFFFF

/*
 * structure used at regsitration
 */
typedef struct {
	unsigned int irq;		//request irq pin number
	pid_t pid;			//process id to notify
} ralink_gpio_reg_info;

#define RALINK_GPIO_LED_INFINITY	4000
typedef struct {
	int gpio;			//gpio number (0 ~ 23)
	unsigned int on;		//interval of led on
	unsigned int off;		//interval of led off
	unsigned int blinks;		//number of blinking cycles
	unsigned int rests;		//number of break cycles
	unsigned int times;		//blinking times
} ralink_gpio_led_info;


#define RALINK_GPIO(x)			(1 << x)

#endif
