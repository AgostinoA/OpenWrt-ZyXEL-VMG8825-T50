/**************************************************************************
 *
 *  BRIEF MODULE DESCRIPTION
 *     register definition for Ralink RT-series SoC
 *
 *  Copyright 2007 Ralink Inc.
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
 **************************************************************************
 */

#ifndef __RALINK_MMAP__
#define __RALINK_MMAP__

#if defined (RT2880_FPGA_BOARD) || defined (RT2880_ASIC_BOARD)

#ifdef RT2880_SHUTTLE

#define RALINK_SYSCTL_BASE 		0xA0300000
#define RALINK_TIMER_BASE		0xA0300100
#define RALINK_INTCL_BASE		0xA0300200
#define RALINK_MEMCTRL_BASE		0xA0300300
#define RALINK_UART_BASE		0xA0300500
#define RALINK_PIO_BASE			0xA0300600
#define RALINK_I2C_BASE			0xA0300900
#define RALINK_SPI_BASE			0xA0300B00
#define RALINK_UART_LITE_BASE		0xA0300C00
#define RALINK_FRAME_ENGINE_BASE	0xA0310000
#define RALINK_EMBEDD_ROM_BASE		0xA0400000
#define RALINK_PCI_BASE			0xA0500000
#define RALINK_11N_MAC_BASE		0xA0600000

#else // RT2880_MP

#define RALINK_SYSCTL_BASE 		0xA0300000
#define RALINK_TIMER_BASE		0xA0300100
#define RALINK_INTCL_BASE		0xA0300200
#define RALINK_MEMCTRL_BASE		0xA0300300
#define RALINK_UART_BASE		0xA0300500
#define RALINK_PIO_BASE			0xA0300600
#define RALINK_I2C_BASE			0xA0300900
#define RALINK_SPI_BASE			0xA0300B00
#define RALINK_UART_LITE_BASE		0x00300C00
#define RALINK_FRAME_ENGINE_BASE	0xA0400000
#define RALINK_EMBEDD_ROM_BASE		0xA0410000
#define RALINK_PCI_BASE			0xA0440000
#define RALINK_11N_MAC_BASE		0xA0480000

//Interrupt Controller
#define RALINK_INTCTL_TIMER0		(1<<0)
#define RALINK_INTCTL_WDTIMER		(1<<1)
#define RALINK_INTCTL_UART		(1<<2)
#define RALINK_INTCTL_PIO		(1<<3)
#define RALINK_INTCTL_PCM		(1<<4)
#define RALINK_INTCTL_UARTLITE		(1<<8)
#define RALINK_INTCTL_ILL_ACCESS	(1<<23)

//Reset Control Register
#define RALINK_TIMER_RST		(1<<1)
#define RALINK_INTC_RST			(1<<2)
#define RALINK_MC_RST			(1<<3)
#define RALINK_CPU_RST			(1<<4)
#define RALINK_UART_RST			(1<<5)
#define RALINK_PIO_RST			(1<<6)
#define RALINK_I2C_RST			(1<<9)
#define RALINK_SPI_RST			(1<<11)
#define RALINK_UART2_RST		(1<<12)
#define RALINK_PCI_RST			(1<<16)
#define RALINK_2860_RST			(1<<17)
#define RALINK_FE_RST			(1<<18)
#define RALINK_PCM_RST			(1<<19)

#endif

#elif defined (RT3052_FPGA_BOARD) || defined (RT3052_ASIC_BOARD)

#define RALINK_SYSCTL_BASE		0xB0000000
#define RALINK_TIMER_BASE		0xB0000100
#define RALINK_INTCL_BASE		0xB0000200
#define RALINK_MEMCTRL_BASE		0xB0000300
#define RALINK_PCM_BASE			0xB0000400
#define RALINK_UART_BASE		0xB0000500
#define RALINK_PIO_BASE			0xB0000600
#define RALINK_GDMA_BASE		0xB0000700
#define RALINK_NAND_CTRL_BASE		0xB0000800
#define RALINK_I2C_BASE			0xB0000900
#define RALINK_I2S_BASE			0xB0000A00
#define RALINK_SPI_BASE			0xB0000B00
#define RALINK_UART_LITE_BASE		0xB0000C00
#define RALINK_FRAME_ENGINE_BASE	0xB0100000
#define RALINK_ETH_SW_BASE		0xB0110000
#define RALINK_11N_MAC_BASE		0xB0180000
#define RALINK_USB_OTG_BASE		0xB01C0000

//Interrupt Controller
#define RALINK_INTCTL_SYSCTL		(1<<0)
#define RALINK_INTCTL_TIMER0		(1<<1)
#define RALINK_INTCTL_WDTIMER		(1<<2)
#define RALINK_INTCTL_ILL_ACCESS	(1<<3)
#define RALINK_INTCTL_PCM		(1<<4)
#define RALINK_INTCTL_UART		(1<<5)
#define RALINK_INTCTL_PIO		(1<<6)
#define RALINK_INTCTL_DMA		(1<<7)
#define RALINK_INTCTL_NAND		(1<<8)
#define RALINK_INTCTL_PC		(1<<9)
#define RALINK_INTCTL_I2S		(1<<10)
#define RALINK_INTCTL_UARTLITE		(1<<12)
#define RALINK_INTCTL_ESW		(1<<17)
#define RALINK_INTCTL_OTG		(1<<18)
#define RALINK_INTCTL_OTG_IRQN		18
#define RALINK_INTCTL_GLOBAL		(1<<31)

//Reset Control Register
#define RALINK_SYS_RST			(1<<0)
#define RALINK_CPU_RST			(1<<1)
#define RALINK_TIMER_RST		(1<<8)
#define RALINK_INTC_RST			(1<<9)
#define RALINK_MC_RST			(1<<10)
#define RALINK_PCM_RST			(1<<11)
#define RALINK_UART_RST			(1<<12)
#define RALINK_PIO_RST			(1<<13)
#define RALINK_DMA_RST			(1<<14)
#define RALINK_I2C_RST			(1<<16)
#define RALINK_I2S_RST			(1<<17)
#define RALINK_SPI_RST			(1<<18)
#define RALINK_UARTL_RST		(1<<19)
#define RALINK_RT2872_RST		(1<<20)
#define RALINK_FE_RST			(1<<21)
#define RALINK_OTG_RST			(1<<22)
#define RALINK_SW_RST			(1<<23)
#define RALINK_EPHY_RST			(1<<24)

#elif defined (RT3352_FPGA_BOARD) || defined (RT3352_ASIC_BOARD) 

#define RALINK_SYSCTL_BASE		0xB0000000
#define RALINK_TIMER_BASE		0xB0000100
#define RALINK_INTCL_BASE		0xB0000200
#define RALINK_MEMCTRL_BASE		0xB0000300
#define RALINK_UART_BASE		0xB0000500
#define RALINK_PIO_BASE			0xB0000600
#define RALINK_I2C_BASE			0xB0000900
#define RALINK_I2S_BASE			0xB0000A00
#define RALINK_SPI_BASE			0xB0000B00
#define RALINK_UART_LITE_BASE		0xB0000C00
#define RALINK_PCM_BASE			0xB0002000
#define RALINK_GDMA_BASE		0xB0002800
#define RALINK_FRAME_ENGINE_BASE	0xB0100000
#define RALINK_ETH_SW_BASE		0xB0110000
#define RALINK_USB_DEV_BASE		0xB0120000
#define RALINK_11N_MAC_BASE		0xB0180000
#define RALINK_USB_OTG_BASE		0xB01C0000

//Interrupt Controller
#define RALINK_INTCTL_SYSCTL		(1<<0)
#define RALINK_INTCTL_TIMER0		(1<<1)
#define RALINK_INTCTL_WDTIMER		(1<<2)
#define RALINK_INTCTL_ILL_ACCESS	(1<<3)
#define RALINK_INTCTL_PCM		(1<<4)
#define RALINK_INTCTL_UART		(1<<5)
#define RALINK_INTCTL_PIO		(1<<6)
#define RALINK_INTCTL_DMA		(1<<7)
#define RALINK_INTCTL_PC		(1<<9)
#define RALINK_INTCTL_I2S		(1<<10)
#define RALINK_INTCTL_UARTLITE		(1<<12)
#define RALINK_INTCTL_ESW		(1<<17)
#define RALINK_INTCTL_UHST		(1<<18)
#define RALINK_INTCTL_UDEV		(1<<19)
#define RALINK_INTCTL_GLOBAL		(1<<31)

//Reset Control Register
#define RALINK_SYS_RST			(1<<0)
#define RALINK_TIMER_RST		(1<<8)
#define RALINK_INTC_RST			(1<<9)
#define RALINK_MC_RST			(1<<10)
#define RALINK_PCM_RST			(1<<11)
#define RALINK_UART_RST			(1<<12)
#define RALINK_PIO_RST			(1<<13)
#define RALINK_DMA_RST			(1<<14)
#define RALINK_I2C_RST			(1<<16)
#define RALINK_I2S_RST			(1<<17)
#define RALINK_SPI_RST			(1<<18)
#define RALINK_UARTL_RST		(1<<19)
#define RALINK_WLAN_RST			(1<<20)
#define RALINK_FE_RST			(1<<21)
#define RALINK_UHST_RST			(1<<22)
#define RALINK_ESW_RST			(1<<23)
#define RALINK_EPHY_RST			(1<<24)
#define RALINK_UDEV_RST			(1<<25)

//Clock Conf Register
#define RALINK_UPHY1_CLK_EN		(1<<20)
#define RALINK_UPHY0_CLK_EN		(1<<18)
#define RALINK_GE1_CLK_EN		(1<<16)


#elif defined (RT6855_FPGA_BOARD) || defined (RT6855_ASIC_BOARD) 

#define RALINK_SYSCTL_BASE		0xB0000000
#define RALINK_TIMER_BASE		0xB0000100
#define RALINK_INTCL_BASE		0xB0000200
#define RALINK_MEMCTRL_BASE		0xB0000300
#define RALINK_UART_BASE		0xB0000500
#define RALINK_PIO_BASE			0xB0000600
#define RALINK_NAND_CTRL_BASE		0xB0000810
#define RALINK_I2C_BASE			0xB0000900
#define RALINK_I2S_BASE			0xB0000A00
#define RALINK_SPI_BASE			0xB0000B00
#define RALINK_UART_LITE_BASE		0xB0000C00
#define RALINK_PCM_BASE			0xB0002000
#define RALINK_GDMA_BASE		0xB0002800
#define RALINK_FRAME_ENGINE_BASE	0xB0100000
#define RALINK_ETH_SW_BASE		0xB0110000
#define RALINK_USB_DEV_BASE		0xB0120000
#define RALINK_PCIE_BASE		0xB0140000
#define RALINK_USB_OTG_BASE		0xB01C0000

//Interrupt Controller
#define RALINK_INTCTL_SYSCTL		(1<<0)
#define RALINK_INTCTL_TIMER0		(1<<1)
#define RALINK_INTCTL_WDTIMER		(1<<2)
#define RALINK_INTCTL_ILL_ACCESS	(1<<3)
#define RALINK_INTCTL_PCM		(1<<4)
#define RALINK_INTCTL_UART		(1<<5)
#define RALINK_INTCTL_PIO		(1<<6)
#define RALINK_INTCTL_DMA		(1<<7)
#define RALINK_INTCTL_PC		(1<<9)
#define RALINK_INTCTL_I2S		(1<<10)
#define RALINK_INTCTL_UARTLITE		(1<<12)
#define RALINK_INTCTL_ESW		(1<<17)
#define RALINK_INTCTL_UHST		(1<<18)
#define RALINK_INTCTL_UDEV		(1<<19)
#define RALINK_INTCTL_GLOBAL		(1<<31)

//Reset Control Register
#define RALINK_SYS_RST			(1<<0)
#define RALINK_TIMER_RST		(1<<8)
#define RALINK_INTC_RST			(1<<9)
#define RALINK_MC_RST			(1<<10)
#define RALINK_PCM_RST			(1<<11)
#define RALINK_UART_RST			(1<<12)
#define RALINK_PIO_RST			(1<<13)
#define RALINK_DMA_RST			(1<<14)
#define RALINK_I2C_RST			(1<<16)
#define RALINK_I2S_RST			(1<<17)
#define RALINK_SPI_RST			(1<<18)
#define RALINK_UARTL_RST		(1<<19)
#define RALINK_FE_RST			(1<<21)
#define RALINK_UHST_RST			(1<<22)
#define RALINK_ESW_RST			(1<<23)
#define RALINK_EPHY_RST			(1<<24)
#define RALINK_UHST0_RST		(1<<25)
#define RALINK_UDEV_RST			(1<<25)
#define RALINK_PCIE0_RST		(1<<26)
#define RALINK_PCIE1_RST		(1<<27)

//Clock Conf Register
#define RALINK_UPHY0_CLK_EN		(1<<25)

#elif defined (RT6352_FPGA_BOARD) || defined (RT6352_ASIC_BOARD) 

#define RALINK_SYSCTL_BASE              0xB0000000
#define RALINK_TIMER_BASE               0xB0000100
#define RALINK_INTCL_BASE               0xB0000200
#define RALINK_MEMCTRL_BASE             0xB0000300
#define RALINK_RBUS_MATRIXCTL_BASE      0xB0000400
#define RALINK_UART_BASE                0x10000500
#define RALINK_PIO_BASE                 0xB0000600
#define RALINK_NAND_CTRL_BASE           0xB0000810
#define RALINK_I2C_BASE                 0xB0000900
#define RALINK_I2S_BASE                 0xB0000A00
#define RALINK_SPI_BASE                 0xB0000B00
#define RALINK_UART_LITE_BASE           0x10000C00
#define RALINK_MIPS_CNT_BASE            0x10000D00
#define RALINK_PCM_BASE                 0xB0002000
#define RALINK_GDMA_BASE                0xB0002800
#define RALINK_CRYPTO_ENGING_BASE       0xB0004000
#define RALINK_FRAME_ENGINE_BASE        0xB0100000
#define RALINK_ETH_SW_BASE              0xB0110000
#define RALINK_USB_DEV_BASE             0x10120000
#define RALINK_PCI_BASE                 0xB0140000
#define RALINK_11N_MAC_BASE             0xB0180000
#define RALINK_USB_HOST_BASE            0x101C0000

#define RALINK_MCNT_CFG                 0xB0000D00
#define RALINK_COMPARE                  0xB0000D04
#define RALINK_COUNT                    0xB0000D08

//Interrupt Controller
#define RALINK_INTCTL_SYSCTL            (1<<0)
#define RALINK_INTCTL_TIMER0            (1<<1)
#define RALINK_INTCTL_WDTIMER           (1<<2)
#define RALINK_INTCTL_ILL_ACCESS        (1<<3)
#define RALINK_INTCTL_PCM               (1<<4)
#define RALINK_INTCTL_UART              (1<<5)
#define RALINK_INTCTL_PIO               (1<<6)
#define RALINK_INTCTL_DMA               (1<<7)
#define RALINK_INTCTL_PC                (1<<9)
#define RALINK_INTCTL_I2S               (1<<10)
#define RALINK_INTCTL_SPI               (1<<11)
#define RALINK_INTCTL_UARTLITE          (1<<12)
#define RALINK_INTCTL_CRYPTO            (1<<13)
#define RALINK_INTCTL_ESW               (1<<17)
#define RALINK_INTCTL_UHST              (1<<18)
#define RALINK_INTCTL_UDEV              (1<<19)
#define RALINK_INTCTL_GLOBAL            (1<<31)

//Reset Control Register
#define RALINK_SYS_RST                  (1<<0)
#define RALINK_TIMER_RST                (1<<8)
#define RALINK_INTC_RST                 (1<<9)
#define RALINK_MC_RST                   (1<<10)
#define RALINK_PCM_RST                  (1<<11)
#define RALINK_UART_RST                 (1<<12)
#define RALINK_PIO_RST                  (1<<13)
#define RALINK_DMA_RST                  (1<<14)
#define RALINK_I2C_RST                  (1<<16)
#define RALINK_I2S_RST                  (1<<17)
#define RALINK_SPI_RST                  (1<<18)
#define RALINK_UARTL_RST                (1<<19)
#define RALINK_FE_RST                   (1<<21)
#define RALINK_UHST_RST                 (1<<22)
#define RALINK_ESW_RST                  (1<<23)
#define RALINK_EPHY_RST                 (1<<24)
#define RALINK_UDEV_RST                 (1<<25)
#define RALINK_PCIE0_RST                (1<<26)
#define RALINK_PCIE1_RST                (1<<27)
#define RALINK_MIPS_CNT_RST             (1<<28)
#define RALINK_CRYPTO_RST               (1<<29)

#elif defined (RT71100_FPGA_BOARD) || defined (RT71100_ASIC_BOARD) 

#define RALINK_SYSCTL_BASE              0xB0000000
#define RALINK_TIMER_BASE               0xB0000100
#define RALINK_INTCL_BASE               0xB0000200
#define RALINK_MEMCTRL_BASE             0xB0000300
#define RALINK_UART_BASE                0x10000500
#define RALINK_PIO_BASE                 0xB0000600
#define RALINK_I2C_BASE                 0xB0000900
#define RALINK_I2S_BASE                 0xB0000A00
#define RALINK_SPI_BASE                 0xB0000B00
#define RALINK_NAND_CTRL_BASE           0xB0000800
#define RALINK_UART_LITE_BASE           0x10000C00
#define RALINK_PCM_BASE                 0xB0002000
#define RALINK_GDMA_BASE                0xB0002800
#define RALINK_FRAME_ENGINE_BASE        0xB0100000
#define RALINK_ETH_SW_BASE              0xB0110000
#define RALINK_PCI_BASE                 0xB0140000
#define RALINK_USB_DEV_BASE             0x10120000
#define RALINK_11N_MAC_BASE             0xB0180000
#define RALINK_PLC_MAC_BASE             0xB0200000
#define RALINK_USB_HOST_BASE            0x101C0000

#define RALINK_MCNT_CFG                 0xB0000D00
#define RALINK_COMPARE                  0xB0000D04
#define RALINK_COUNT                    0xB0000D08

//Interrupt Controller
#define RALINK_INTCTL_SYSCTL            (1<<0)
#define RALINK_INTCTL_TIMER0            (1<<1)
#define RALINK_INTCTL_WDTIMER           (1<<2)
#define RALINK_INTCTL_ILL_ACCESS        (1<<3)
#define RALINK_INTCTL_PCM               (1<<4)
#define RALINK_INTCTL_UART              (1<<5)
#define RALINK_INTCTL_PIO               (1<<6)
#define RALINK_INTCTL_DMA               (1<<7)
#define RALINK_INTCTL_PC                (1<<9)
#define RALINK_INTCTL_I2S               (1<<10)
#define RALINK_INTCTL_UARTLITE          (1<<12)
#define RALINK_INTCTL_ESW               (1<<17)
#define RALINK_INTCTL_GLOBAL            (1<<31)

//Reset Control Register
#define RALINK_SYS_RST                  (1<<0)
#define RALINK_TIMER_RST                (1<<8)
#define RALINK_INTC_RST                 (1<<9)
#define RALINK_MC_RST                   (1<<10)
#define RALINK_PCM_RST                  (1<<11)
#define RALINK_UART_RST                 (1<<12)
#define RALINK_PIO_RST                  (1<<13)
#define RALINK_DMA_RST                  (1<<14)
#define RALINK_I2C_RST                  (1<<16)
#define RALINK_I2S_RST                  (1<<17)
#define RALINK_SPI_RST                  (1<<18)
#define RALINK_UARTL_RST                (1<<19)
#define RALINK_FE_RST                   (1<<21)
#define RALINK_UHST_RST                 (1<<22)
#define RALINK_ESW_RST                  (1<<23)
#define RALINK_EPHY_RST                 (1<<24)
#define RALINK_UDEV_RST                 (1<<25)
#define RALINK_PCIE0_RST                (1<<26)
#define RALINK_PCIE1_RST                (1<<27)

#elif defined (RT2883_FPGA_BOARD) || defined (RT2883_ASIC_BOARD)

#define RALINK_SYSCTL_BASE		0xB0000000
#define RALINK_TIMER_BASE		0xB0000100
#define RALINK_INTCL_BASE		0xB0000200
#define RALINK_MEMCTRL_BASE		0xB0000300
#define RALINK_PCM_BASE			0xB0000400
#define RALINK_UART_BASE		0xB0000500
#define RALINK_PIO_BASE			0xB0000600
#define RALINK_GDMA_BASE		0xB0000700
#define RALINK_NAND_CTRL_BASE		0xB0000800
#define RALINK_I2C_BASE			0xB0000900
#define RALINK_I2S_BASE			0xB0000A00
#define RALINK_SPI_BASE			0xB0000B00
#define RALINK_UART_LITE_BASE		0xB0000C00
#define RALINK_FRAME_ENGINE_BASE	0xB0100000
#define RALINK_PCI_BASE			0xB0140000
#define RALINK_11N_MAC_BASE		0xB0180000
#define RALINK_USB_OTG_BASE		0xB01C0000

//Interrupt Controller
#define RALINK_INTCTL_SYSCTL		(1<<0)
#define RALINK_INTCTL_TIMER0		(1<<1)
#define RALINK_INTCTL_WDTIMER		(1<<2)
#define RALINK_INTCTL_ILL_ACCESS	(1<<3)
#define RALINK_INTCTL_PCM		(1<<4)
#define RALINK_INTCTL_UART		(1<<5)
#define RALINK_INTCTL_PIO		(1<<6)
#define RALINK_INTCTL_DMA		(1<<7)
#define RALINK_INTCTL_NAND		(1<<8)
#define RALINK_INTCTL_PC		(1<<9)
#define RALINK_INTCTL_I2S		(1<<10)
#define RALINK_INTCTL_UARTLITE		(1<<12)
#define RALINK_INTCTL_OTG		(1<<18)
#define RALINK_INTCTL_OTG_IRQN		18
#define RALINK_INTCTL_GLOBAL		(1<<31)

//Reset Control Register
#define RALINK_SYS_RST			(1<<0)
#define RALINK_CPU_RST			(1<<1)
#define RALINK_TIMER_RST		(1<<8)
#define RALINK_INTC_RST			(1<<9)
#define RALINK_MC_RST			(1<<10)
#define RALINK_PCM_RST			(1<<11)
#define RALINK_UART_RST			(1<<12)
#define RALINK_PIO_RST			(1<<13)
#define RALINK_DMA_RST			(1<<14)
#define RALINK_I2C_RST			(1<<16)
#define RALINK_I2S_RST			(1<<17)
#define RALINK_SPI_RST			(1<<18)
#define RALINK_UARTL_RST		(1<<19)
#define RALINK_WLAN_RST			(1<<20)
#define RALINK_FE_RST			(1<<21)
#define RALINK_OTG_RST			(1<<22)
#define RALINK_PCIE_RST			(1<<23)


#elif defined (RT3883_FPGA_BOARD) || defined (RT3883_ASIC_BOARD) 

#define RALINK_SYSCTL_BASE		0xB0000000
#define RALINK_TIMER_BASE		0xB0000100
#define RALINK_INTCL_BASE		0xB0000200
#define RALINK_MEMCTRL_BASE		0xB0000300
#define RALINK_UART_BASE		0xB0000500
#define RALINK_PIO_BASE			0xB0000600
#define RALINK_NOR_CTRL_BASE		0xB0000700
#define RALINK_NAND_CTRL_BASE		0xB0000810
#define RALINK_I2C_BASE			0xB0000900
#define RALINK_I2S_BASE			0xB0000A00
#define RALINK_SPI_BASE			0xB0000B00
#define RALINK_UART_LITE_BASE		0xB0000C00
#define RALINK_PCM_BASE			0xB0002000
#define RALINK_GDMA_BASE		0xB0002800
#define RALINK_CODEC1_BASE		0xB0003000
#define RALINK_CODEC2_BASE		0xB0003800
#define RALINK_FRAME_ENGINE_BASE	0xB0100000
#define RALINK_USB_DEV_BASE		0xB0120000
#define RALINK_PCI_BASE			0xB0140000
#define RALINK_11N_MAC_BASE		0xB0180000
#define RALINK_USB_HOST_BASE		0xB01C0000
#define RALINK_PCIE_BASE		0xB0200000

//Interrupt Controller
#define RALINK_INTCTL_SYSCTL		(1<<0)
#define RALINK_INTCTL_TIMER0		(1<<1)
#define RALINK_INTCTL_WDTIMER		(1<<2)
#define RALINK_INTCTL_ILL_ACCESS	(1<<3)
#define RALINK_INTCTL_PCM		(1<<4)
#define RALINK_INTCTL_UART		(1<<5)
#define RALINK_INTCTL_PIO		(1<<6)
#define RALINK_INTCTL_DMA		(1<<7)
#define RALINK_INTCTL_NAND		(1<<8)
#define RALINK_INTCTL_PC		(1<<9)
#define RALINK_INTCTL_I2S		(1<<10)
#define RALINK_INTCTL_UARTLITE		(1<<12)
#define RALINK_INTCTL_UHST		(1<<18)
#define RALINK_INTCTL_UDEV		(1<<19)

//Reset Control Register
#define RALINK_SYS_RST			(1<<0)
#define RALINK_TIMER_RST		(1<<8)
#define RALINK_INTC_RST			(1<<9)
#define RALINK_MC_RST			(1<<10)
#define RALINK_PCM_RST			(1<<11)
#define RALINK_UART_RST			(1<<12)
#define RALINK_PIO_RST			(1<<13)
#define RALINK_DMA_RST			(1<<14)
#define RALINK_NAND_RST			(1<<15)
#define RALINK_I2C_RST			(1<<16)
#define RALINK_I2S_RST			(1<<17)
#define RALINK_SPI_RST			(1<<18)
#define RALINK_UARTL_RST		(1<<19)
#define RALINK_WLAN_RST			(1<<20)
#define RALINK_FE_RST			(1<<21)
#define RALINK_UHST_RST			(1<<22)
#define RALINK_PCIE_RST			(1<<23)
#define RALINK_PCI_RST			(1<<24)
#define RALINK_UDEV_RST			(1<<25)
#define RALINK_FLASH_RST		(1<<26)

//Clock Conf Register
#define RALINK_UPHY1_CLK_EN		(1<<20)
#define RALINK_UPHY0_CLK_EN		(1<<18)
#define RALINK_GE1_CLK_EN		(1<<16)


#elif defined (RT5350_FPGA_BOARD) || defined (RT5350_ASIC_BOARD) 

#define RALINK_SYSCTL_BASE		0xB0000000
#define RALINK_TIMER_BASE		0xB0000100
#define RALINK_INTCL_BASE		0xB0000200
#define RALINK_MEMCTRL_BASE		0xB0000300
#define RALINK_UART_BASE		0xB0000500
#define RALINK_PIO_BASE			0xB0000600
#define RALINK_I2C_BASE			0xB0000900
#define RALINK_I2S_BASE			0xB0000A00
#define RALINK_SPI_BASE			0xB0000B00
#define RALINK_UART_LITE_BASE		0xB0000C00
#define RALINK_PCM_BASE			0xB0002000
#define RALINK_GDMA_BASE		0xB0002800
#define RALINK_FRAME_ENGINE_BASE	0xB0100000
#define RALINK_ETH_SW_BASE		0xB0110000
#define RALINK_USB_DEV_BASE		0xB0120000
#define RALINK_11N_MAC_BASE		0xB0180000
#define RALINK_USB_HOST_BASE		0xB01C0000

//Interrupt Controller
#define RALINK_INTCTL_SYSCTL		(1<<0)
#define RALINK_INTCTL_TIMER0		(1<<1)
#define RALINK_INTCTL_WDTIMER		(1<<2)
#define RALINK_INTCTL_ILL_ACCESS	(1<<3)
#define RALINK_INTCTL_PCM		(1<<4)
#define RALINK_INTCTL_UART		(1<<5)
#define RALINK_INTCTL_PIO		(1<<6)
#define RALINK_INTCTL_DMA		(1<<7)
#define RALINK_INTCTL_PC		(1<<9)
#define RALINK_INTCTL_I2S		(1<<10)
#define RALINK_INTCTL_UARTLITE		(1<<12)
#define RALINK_INTCTL_ESW		(1<<17)
#define RALINK_INTCTL_UHST		(1<<18)
#define RALINK_INTCTL_UDEV		(1<<19)
#define RALINK_INTCTL_GLOBAL		(1<<31)

//Reset Control Register
#define RALINK_SYS_RST			(1<<0)
#define RALINK_TIMER_RST		(1<<8)
#define RALINK_INTC_RST			(1<<9)
#define RALINK_MC_RST			(1<<10)
#define RALINK_PCM_RST			(1<<11)
#define RALINK_UART_RST			(1<<12)
#define RALINK_PIO_RST			(1<<13)
#define RALINK_DMA_RST			(1<<14)
#define RALINK_I2C_RST			(1<<16)
#define RALINK_I2S_RST			(1<<17)
#define RALINK_SPI_RST			(1<<18)
#define RALINK_UARTL_RST		(1<<19)
#define RALINK_WLAN_RST			(1<<20)
#define RALINK_FE_RST			(1<<21)
#define RALINK_UHST_RST			(1<<22)
#define RALINK_ESW_RST			(1<<23)
#define RALINK_EPHY_RST			(1<<24)
#define RALINK_UDEV_RST			(1<<25)
#define RALINK_MIPS_RST			(1<<26)

//Clock Conf Register
#define RALINK_UPHY0_CLK_EN		(1<<18)
#define RALINK_GE1_CLK_EN		(1<<16)

#elif defined (RT6855A_FPGA_BOARD) || defined (RT6855A_ASIC_BOARD) 

#define RALINK_SYSCTL_BASE		0xBFB00000
#define RALINK_TIMER_BASE		0xBFBF0100
#define RALINK_INTCL_BASE		0xBFB40000
#define RALINK_MEMCTRL_BASE		0xBFB20000
#define RALINK_PIO_BASE			0xBFBF0200
#define RALINK_NAND_CTRL_BASE		0xBFBE0010
#define RALINK_I2C_BASE			0xBFBF8000
#define RALINK_I2S_BASE			0xBFBF8100
#define RALINK_SPI_BASE			0xBFBC0B00
#define RALINK_UART_LITE_BASE		0xBFBF0000
#define RALINK_UART_LITE2_BASE		0xBFBF0300
#define RALINK_PCM_BASE			0xBFBD0000
#define RALINK_GDMA_BASE		0xBFB30000
#define RALINK_FRAME_ENGINE_BASE	0xBFB50000
#define RALINK_ETH_SW_BASE		0xBFB58000
//#define RALINK_USB_DEV_BASE		0xB0120000
#define RALINK_PCI_BASE			0xBFB80000
//#define RALINK_USB_HOST_BASE		0xB01C0000
#define RALINK_PCIE_BASE		0xBFB81000

//Interrupt Controller
#define RALINK_INTCTL_UARTLITE		(1<<0)
#define RALINK_INTCTL_PIO		(1<<10)
#define RALINK_INTCTL_PCM		(1<<11)
#define RALINK_INTCTL_DMA		(1<<14)
#define RALINK_INTCTL_GMAC2		(1<<15)
#define RALINK_INTCTL_PCI		(1<<17)
#define RALINK_INTCTL_UHST2		(1<<20)
#define RALINK_INTCTL_GMAC1		(1<<21)
#define RALINK_INTCTL_UHST1		(1<<23)
#define RALINK_INTCTL_PCIE		(1<<24)
#define RALINK_INTCTL_NAND		(1<<25)
#define RALINK_INTCTL_SPI		(1<<27)

//Reset Control Register
//#define RALINK_SYS_RST			(1<<0)
#define RALINK_TIMER_RST		(1<<8)
#define RALINK_INTC_RST			(1<<9)
#define RALINK_MC_RST			(1<<10)
#define RALINK_PCM_RST			(1<<11)
#define RALINK_UART_RST			(1<<12)
#define RALINK_PIO_RST			(1<<13)
#define RALINK_DMA_RST			(1<<14)
#define RALINK_I2C_RST			(1<<16)
#define RALINK_I2S_RST			(1<<17)
#define RALINK_SPI_RST			(1<<18)
#define RALINK_UARTL_RST		(1<<19)
#define RALINK_WLAN_RST			(1<<20)
#define RALINK_FE_RST			(1<<21)
#define RALINK_UHST_RST			(1<<22)
#define RALINK_ESW_RST			(1<<23)
#define RALINK_EPHY_RST			(1<<24)
#define RALINK_UDEV_RST			(1<<25)
//#define RALINK_MIPS_RST			(1<<26)

#endif


/*kurtis:define DDR parameter here for better performance*/
#ifdef ON_BOARD_DDR2
/*define ddr module here to choose proper setting or use default setting*/
//#define W9751G6IB_25

#define DDR_CFG0_REG	RALINK_MEMCTRL_BASE+0x40
#define RAS_OFFSET	23
#define TRFC_OFFSET	13
#define TRFI_OFFSET	0
#ifdef  ON_BOARD_32BIT_DRAM_BUS
#define BL_VALUE	2//BL=4
#else
#define BL_VALUE	3 //BL=8
#endif

#define CAS_OFFSET	4
#define BL_OFFSET	0
#define AdditiveLatency_OFFSET 3

#if defined (W9751G6IB_25)
#define RAS_VALUE	7
#define TRFC_VALUE	9
#define TRFI_VALUE	650
#define CAS_VALUE	3
#define AdditiveLatency_VALUE  0
#endif //W9751G6IB_25

#endif //DDR
#if defined (RT6855A_ASIC_BOARD) || defined (RT6855A_FPGA_BOARD)
#define RALINK_SDRAM_CFG0_REG 	(RALINK_MEMCTRL_BASE)
#define RALINK_SDRAM_CFG1_REG 	(RALINK_MEMCTRL_BASE+0x4)
#define RALINK_DDR_CFG0		(RALINK_MEMCTRL_BASE+0x40)
#define RALINK_DDR_CFG1		(RALINK_MEMCTRL_BASE+0x44)
#define RALINK_DDR_CFG2		(RALINK_MEMCTRL_BASE+0x48)
#define RALINK_DDR_CFG3		(RALINK_MEMCTRL_BASE+0x4c)
#define RALINK_DDR_CFG4		(RALINK_MEMCTRL_BASE+0x50)
#define RALINK_DDR_CFG9		(RALINK_MEMCTRL_BASE+0x64)
#endif

/* Timer related */
#if defined (RT6855A_ASIC_BOARD) || defined (RT6855A_FPGA_BOARD)
#define RALINK_TIMER_CTL	(RALINK_TIMER_BASE + 0x00)
#define RALINK_TIMER5_LDV	(RALINK_TIMER_BASE + 0x2C)
#endif

#if defined (RT6855A_ASIC_BOARD) || defined (RT6855A_FPGA_BOARD)
#define RALINK_HIR_REG	(RALINK_SYSCTL_BASE + 0x64)
#endif


#define RT2880_REGS_BASE			0xA0000000
/*
 * System Controller	(0x00300000)
 *   Offset
 *   0x10  -- SYSCFG		System Configuration Register
 *   0x30  -- CLKCFG1		Clock Configuration Register
 *   0x34  -- RSTCTRL		Reset Control Register
 *   0x38  -- RSTSTAT		Reset Status Register 
 *   0x60  -- GPIOMODE		GPIO Mode Control Register 
 */
#define RT2880_SYS_CNTL_BASE			(RALINK_SYSCTL_BASE)
#if defined (RT6855A_FPGA_BOARD) || defined (RT6855A_ASIC_BOARD)
#define RT2880_SYSCFG_REG                       (RT2880_SYS_CNTL_BASE+0x8c)
#define RT2880_RSTCTRL_REG                      (RT2880_SYS_CNTL_BASE+0x834)
#define RT2880_RSTSTAT_REG                      (RT2880_SYS_CNTL_BASE+0x38)
#define RT2880_GPIOMODE_REG                     (RT2880_SYS_CNTL_BASE+0x860)
#else
#define RT2880_SYSCFG_REG			(RT2880_SYS_CNTL_BASE+0x10)
#define RT2880_SYSCFG1_REG			(RT2880_SYS_CNTL_BASE+0x14)
#define RT2880_CLKCFG1_REG			(RT2880_SYS_CNTL_BASE+0x30)
#define RT2880_RSTCTRL_REG			(RT2880_SYS_CNTL_BASE+0x34)
#define RT2880_RSTSTAT_REG			(RT2880_SYS_CNTL_BASE+0x38)
#define RT2880_GPIOMODE_REG			(RT2880_SYS_CNTL_BASE+0x60)
#endif

#define RT2880_PRGIO_ADDR       (RALINK_SYSCTL_BASE + 0x600) // Programmable I/O
#define RT2880_REG_PIOINT       (RT2880_PRGIO_ADDR + 0)
#define RT2880_REG_PIOEDGE      (RT2880_PRGIO_ADDR + 0x04)
#define RT2880_REG_PIORENA      (RT2880_PRGIO_ADDR + 0x08)
#define RT2880_REG_PIOFENA      (RT2880_PRGIO_ADDR + 0x0C)
#define RT2880_REG_PIODATA      (RT2880_PRGIO_ADDR + 0x20)
#define RT2880_REG_PIODIR       (RT2880_PRGIO_ADDR + 0x24)

#define RALINK_REG(x)		(*((volatile u32 *)(x)))	
#if defined (RT6855A_FPGA_BOARD) || defined (RT6855A_ASIC_BOARD)
#define ra_inb(offset)		(*(volatile unsigned char *)(offset))
#define ra_inw(offset)		(*(volatile unsigned short *)(offset))
#define ra_inl(offset)		(*(volatile unsigned long *)(offset))

#define ra_outb(offset,val)	(*(volatile unsigned char *)(offset) = val)
#define ra_outw(offset,val)	(*(volatile unsigned short *)(offset) = val)
#define ra_outl(offset,val)	(*(volatile unsigned long *)(offset) = val)

#define ra_and(addr, value) ra_outl(addr, (ra_inl(addr) & (value)))
#define ra_or(addr, value) ra_outl(addr, (ra_inl(addr) | (value)))
#endif
#define RT2880_WDRST            (1<<1)
#define RT2880_SWSYSRST         (1<<2)
#define RT2880_SWCPURST         (1<<3)

#define RT2880_UPHY0_CLK_EN		(1<<18)
#define RT2880_UPHY1_CLK_EN		(1<<20)


#endif // __RALINK_MMAP__
