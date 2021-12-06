#ifndef __COMCERTO_900_H
#define __COMCERTO_900_H


/* Memory map */
/* Internal Memory */
#define ERAM_BASEADDR			0x08000000
#define ARAM_BASEADDR			0x0A000000
#define CRAM_BASEADDR			0x0B000000

/* Expansion bus */
#define APB_BASEADDR			0x10000000

/* Chip select */
#define EXP_CSBOOT_BASEADDR		0x11000000
#define EXP_CSP0_BASEADDR		0x11400000
#define EXP_CSP1_BASEADDR		0x11800000

#define ERAM_SIZE			0x00300000
#define ARAM_SIZE			0x000A2000
#define CRAM_SIZE			0x00080000
#define APB_SIZE			0x01000000 /* 16M address range */
#define EXP_CSBOOT_SIZE			0x00400000
#define EXP_CSP0_SIZE			0x00400000
#define EXP_CSP1_SIZE			0x00800000

/* Expansion bus peripherals */
#define TDM_BASEADDR			(APB_BASEADDR + 0x000000)
#define PHI_BASEADDR			(APB_BASEADDR + 0x010000)
#define TDMA_BASEADDR			(APB_BASEADDR + 0x020000)
#define SMC_BASEADDR			(APB_BASEADDR + 0x030000)
#define ASA_CM_BASEADDR			(APB_BASEADDR + 0x040000)
#define ASA_ARAM_BASEADDR		(APB_BASEADDR + 0x048000)
#define TIMER_BASEADDR			(APB_BASEADDR + 0x050000)
#define ASD_BASEADDR			(APB_BASEADDR + 0x060000)
#define GPIO_BASEADDR			(APB_BASEADDR + 0x070000)
#define SDC0_BASEADDR			(APB_BASEADDR + 0x080000)
#define UART0_BASEADDR			(APB_BASEADDR + 0x090000)
#define INTC_BASEADDR			(APB_BASEADDR + 0x0A0000)
#define CLKCORE_BASEADDR		(APB_BASEADDR + 0x0B0000)
#define PUI_BASEADDR			(APB_BASEADDR + 0x0C0000)
#define GEMAC_BASEADDR			(APB_BASEADDR + 0x0D0000)
#define IDMA_BASEADDR			(APB_BASEADDR + 0x0E0000)
#define ERAM_CFG_BASEADDR		(APB_BASEADDR + 0x0F0000)
#define ASA_ERAM_BASEADDR		(APB_BASEADDR + 0x100000)
#define ASA_CRAM_BASEADDR		(APB_BASEADDR + 0x108000)
#define SPU0_BASEADDR			(APB_BASEADDR + 0x110000)
#define SPU1_BASEADDR			(APB_BASEADDR + 0x120000)
#define SPU2_BASEADDR			(APB_BASEADDR + 0x130000)
#define SPU3_BASEADDR			(APB_BASEADDR + 0x140000)
#define SPU4_BASEADDR			(APB_BASEADDR + 0x150000)
#define SPU5_BASEADDR			(APB_BASEADDR + 0x160000)
#define SPU6_BASEADDR			(APB_BASEADDR + 0x170000)
#define SPU7_BASEADDR			(APB_BASEADDR + 0x180000)
#define TDMA2_BASEADDR			(APB_BASEADDR + 0x1D0000)
#define MDMA_BASEADDR			(APB_BASEADDR + 0x1E0000)


/* PCI HI (PHI) Control Registers */
#define PHI_FIFO_CTRL			(PHI_BASEADDR + 0x0000)
#define PHI_FIFO_INT_STATUS		(PHI_BASEADDR + 0x0004)
#define PHI_FIFO_INT_ACK		(PHI_BASEADDR + 0x0004)
#define	PHI_TX_FIFO_SIZE		(PHI_BASEADDR + 0x0014)
#define	PHI_TX_FIFO_HIGH_THRESHOLD	(PHI_BASEADDR + 0x0018)
#define	PHI_TX_FIFO_LOW_THRESHOLD	(PHI_BASEADDR + 0x001C)
#define	PHI_RX_FIFO_SIZE		(PHI_BASEADDR + 0x0024)
#define	PHI_RX_FIFO_HIGH_THRESHOLD	(PHI_BASEADDR + 0x0028)
#define	PHI_RX_FIFO_LOW_THRESHOLD	(PHI_BASEADDR + 0x002C)

#define RXEIE		0x0100
#define TXM3IE		0x0400
#define RXM3IE		0x0800

#define TXM3IAK		0x04
#define RXEIAK		0x10
#define RXM3IAK		0x40
#define FLUSH_RX	0x80

/* TX Mailbox */
#define PHI_TX_MAIL0			(PHI_BASEADDR + 0x0030)
#define PHI_TX_MAIL1			(PHI_BASEADDR + 0x0034)
#define PHI_TX_MAIL2			(PHI_BASEADDR + 0x0038)
#define PHI_TX_MAIL3			(PHI_BASEADDR + 0x003C)

/* RX Mailbox */
#define PHI_RX_MAIL0			(PHI_BASEADDR + 0x0040)
#define PHI_RX_MAIL1			(PHI_BASEADDR + 0x0044)
#define PHI_RX_MAIL2			(PHI_BASEADDR + 0x0048)
#define PHI_RX_MAIL3			(PHI_BASEADDR + 0x004C)

#define HI_PCI_CNTL			(PHI_BASEADDR + 0x0050)
#define HI_PCI_STATUS			(PHI_BASEADDR + 0x0054)
#define HI_PCI_IAK_REG			(PHI_BASEADDR + 0x0054)
#define HI_PCI_START_ADDR		(PHI_BASEADDR + 0x0060)
#define	HI_PCI_BURST_SIZE		(PHI_BASEADDR + 0x0064)
#define HI_PCI_XFER_LEN			(PHI_BASEADDR + 0x0068)

/* FIFO */
#define PHI_TX_FIFO_DATA_BYTE		(PHI_BASEADDR + 0x4000)
#define PHI_RX_FIFO_DATA_BYTE		(PHI_BASEADDR + 0x4000)
#define PHI_TX_FIFO_DATA_HWORD		(PHI_BASEADDR + 0x8000)
#define PHI_RX_FIFO_DATA_HWORD		(PHI_BASEADDR + 0x8000)
#define PHI_TX_FIFO_DATA_WORD		(PHI_BASEADDR + 0xC000)
#define PHI_RX_FIFO_DATA_WORD		(PHI_BASEADDR + 0xC000)


/* AHB arbiter */
#define ASA_PRIORITY_LEVEL		(ASA_CM_BASEADDR + 0x00)
#define ASA_TERMINAL_COUNT		(ASA_CM_BASEADDR + 0x04)
#define ASA_TERMINAL_COUNT_CFG		(ASA_CM_BASEADDR + 0x08)
#define ASA_TC_REQTDMEN			(1<<10)
#define ASA_TC_REQARM0EN		(1<<11)
#define ASA_TC_REQARM1EN		(1<<12)
#define ASA_TC_REQIDMAEN		(1<<13)
#define ASA_TC_REQSMCEN			(1<<14)
#define ASA_TC_REQTICEN			(1<<15)


////////////////////////////////////////////////////////////
// TIMER block											    //
////////////////////////////////////////////////////////////

#define TIMER0_CNTR_REG		(TIMER_BASEADDR + 0x00)
#define TIMER0_CURR_COUNT	(TIMER_BASEADDR + 0x04)
#define TIMER1_CNTR_REG		(TIMER_BASEADDR + 0x08)
#define TIMER1_CURR_COUNT	(TIMER_BASEADDR + 0x0C)

#define TIMER_MASK			(TIMER_BASEADDR + 0x40)
#define TIMER_STATUS			(TIMER_BASEADDR + 0x50)
#define TIMER_ACK			(TIMER_BASEADDR + 0x50)


/* AHB decoder block */
#define ASD_MBA_EXP_CSSD0		(ASD_BASEADDR + 0x00)
#define ASD_MBA_EXP_CSSD1		(ASD_BASEADDR + 0x04)
#define ASD_CSE				(ASD_BASEADDR + 0x0C)
#define ASD_EXA_EXP_CSSD0		(ASD_BASEADDR + 0x10)
#define ASD_EXA_EXP_CSSD1		(ASD_BASEADDR + 0x14)
#define ASD_MEM_DIVIDER			(ASD_BASEADDR + 0x28)


/* GPIO block */
#define GPIO_OUTPUT			(GPIO_BASEADDR + 0x00)	/* GPIO output register */
#define GPIO_OUTPUT_ENABLE		(GPIO_BASEADDR + 0x04)	/* GPIO output enable register */
#define GPIO_HI_INT_ENABLE		(GPIO_BASEADDR + 0x08)
#define GPIO_LO_INT_ENABLE		(GPIO_BASEADDR + 0x0C)
#define GPIO_INPUT			(GPIO_BASEADDR + 0x10)	/* GPIO input register */
#define GPIO_APB_ACCESS_WS		(GPIO_BASEADDR + 0x14)
#define GPIO_MUX_CONF			(GPIO_BASEADDR + 0x18)
#define GPIO_SYSCONF			(GPIO_BASEADDR + 0x1C)
#define GPIO_LOCK			(GPIO_BASEADDR + 0x38)
#define GPIO_IOCTRL			(GPIO_BASEADDR + 0x44)

#define GPIO_0		0x01
#define GPIO_1		0x02
#define GPIO_2		0x04
#define GPIO_3		0x08
#define GPIO_4		0x10
#define GPIO_5		0x20
#define GPIO_6		0x40
#define GPIO_7		0x80

#define GPIO_RISING_EDGE		1
#define GPIO_FALLING_EDGE		2
#define GPIO_BOTH_EDGES			3


/* SDRAM & SRAM controller block */
#define SDC0_CSSD0_CFG			(SDC0_BASEADDR + 0x00)
#define SDC0_CSSD1_CFG			(SDC0_BASEADDR + 0x04)
#define SDC0_CSBOOT_CFG			(SDC0_BASEADDR + 0x08)
#define SDC0_CSP0_CFG			(SDC0_BASEADDR + 0x0C)
#define SDC0_SDRAM_CFG1			(SDC0_BASEADDR + 0x10)
#define SDC0_SDRAM_CFG2			(SDC0_BASEADDR + 0x14)
#define SDC0_SDRAM_REFRESH		(SDC0_BASEADDR + 0x18)
#define SDC0_SDRAM_POWERON		(SDC0_BASEADDR + 0x1C)
#define SDC0_CSP1_CFG			(SDC0_BASEADDR + 0x20)
#define SDC0_VERSION			(SDC0_BASEADDR + 0x28)
#define SDC0_DEV_ID                     (SDC0_BASEADDR + 0x2C)


/* UART */
#define UART_RBR			(UART0_BASEADDR + 0x00)		/* Receive Buffer Register (R/O) */
#define UART_THR			(UART0_BASEADDR + 0x00)		/* Transmit Holding Register (W/O) */
#define UART_IER			(UART0_BASEADDR + 0x04)		/* Interrupt Enable Register */
#define UART_MCR			(UART0_BASEADDR + 0x08)		/* Mode Control Register */
#define UART_LCR			(UART0_BASEADDR + 0x0C)		/* Line Control Register */
#define UART_SSR			(UART0_BASEADDR + 0x10)		/* Serial Status Register */
#define UART_FCR			(UART0_BASEADDR + 0x14)		/* Form Control Register */
#define UART_RXD			(UART0_BASEADDR + 0x18)		/* Transmiter Divider Latch (R/O) */
#define UART_TXD			(UART0_BASEADDR + 0x1C)		/* Receiver Divider Latch (W/O) */
#define UART_HR				(UART0_BASEADDR + 0x20)		/* Hunt Character */


/* Clock block */
#define CLKCORE_ARM_PLL 		(CLKCORE_BASEADDR + 0x00)
#define CLKCORE_SPU_PLL			(CLKCORE_BASEADDR + 0x04)
#define CLKCORE_AMBA_PLL		(CLKCORE_BASEADDR + 0x08)

#define PLL_POWER			0x04000000	/* PLL power control */
#define PLL_BYPASS			0x02000000	/* PLL bypass */
#define PLL_MUXSEL			0x01000000	/* PLL clock source selection */
#define PLL_RESET			0x00800000	/* PLL reset */


/* GEMAC */

#include "gemac.h"


/* IDMA */
#include "idma.h"


/* Eram */
#define ERAM_BIST_CTRL			(ERAM_CFG_BASEADDR + 0x00)
#define ERAM_SPARE_FAIL			(ERAM_CFG_BASEADDR + 0x04)
#define ERAM_BIST_ADDR			(ERAM_CFG_BASEADDR + 0x08)
#define ERAM_BIST_BCK			(ERAM_CFG_BASEADDR + 0x0C)
#define ERAM_MROW_FAIL			(ERAM_CFG_BASEADDR + 0x10)
#define ERAM_MCOL_FAIL			(ERAM_CFG_BASEADDR + 0x14)
#define ERAM_SHIFT_COL_FAIL		(ERAM_CFG_BASEADDR + 0x18)
#define ERAM_RETN_TIME			(ERAM_CFG_BASEADDR + 0x1C)
#define ERAM_SPCOL_ALLOC		(ERAM_CFG_BASEADDR + 0x20)
#define ERAM_SPROW_ALLOC		(ERAM_CFG_BASEADDR + 0x30)
#define ERAM_FUSE_SPCOL			(ERAM_CFG_BASEADDR + 0x40)
#define ERAM_FUSE_SPROW			(ERAM_CFG_BASEADDR + 0x50)
#define ERAM_IRAM_FAIL			(ERAM_CFG_BASEADDR + 0x60)

/* Eram bus arbiter */
#define ASA_ERAM_PRIORITY		(ASA_ERAM_BASEADDR + 0x00)
#define ASA_ERAM_TERMINAL_COUNT		(ASA_ERAM_BASEADDR + 0x04)
#define ASA_ERAM_TERMINAL_COUNT_CFG	(ASA_ERAM_BASEADDR + 0x08)


#ifndef	__ASSEMBLY__
static inline void HAL_set_arm_clk(u32 fclk)
{
	volatile u32 delay_count;
	u32 clkf = 2 * fclk / CFG_REFCLKFREQ;

	// set PLL into BYPASS mode
	*(volatile u32 *)CLKCORE_ARM_PLL |= PLL_BYPASS;
	*(volatile u32 *)CLKCORE_ARM_PLL &= 0xFFFF0000;

	// reset PLL
	*(volatile u32 *)CLKCORE_ARM_PLL |= PLL_RESET | clkf;

	//wait 5us for PLL to lock
	delay_count = 10;
	while (delay_count--);

	// take PLL out of reset
	*(volatile u32 *)CLKCORE_ARM_PLL &= ~PLL_RESET;

	//wait 500 cycles
	delay_count = 500;
	while (delay_count--);

	// enable PLL
	*(volatile u32 *)CLKCORE_ARM_PLL &= ~PLL_BYPASS;
}


static inline void HAL_set_amba_clk(u32 fclk)
{
	volatile u32 delay_count;
	u32 clkf = 4 * fclk / CFG_REFCLKFREQ;

	// set PLL into BYPASS mode
	*(volatile u32 *)CLKCORE_AMBA_PLL |= PLL_BYPASS;
	*(volatile u32 *)CLKCORE_AMBA_PLL &= 0xFFFF0000;

	// reset PLL
	*(volatile u32 *)CLKCORE_AMBA_PLL |= PLL_RESET | PLL_MUXSEL | clkf;

	//wait 5us for PLL to lock
	delay_count = 10;
	while (delay_count--);

	// take PLL out of reset
	*(volatile u32 *)CLKCORE_AMBA_PLL &= ~PLL_RESET;

	//wait 500 cycles
	delay_count = 500;
	while (delay_count--);

	// enable PLL
	*(volatile u32 *)CLKCORE_AMBA_PLL &= ~PLL_BYPASS;
}
#endif

#define HAL_asb_arbitration(arbitration_mask) (*(volatile u32 *)ASA_TERMINAL_COUNT_CFG |= (arbitration_mask))


#define HAL_get_amba_clk() ((CFG_REFCLKFREQ * (*(volatile u32 *)CLKCORE_AMBA_PLL & 0x7F)) >> 2)


#endif /* __COMCERTO_900_H */
