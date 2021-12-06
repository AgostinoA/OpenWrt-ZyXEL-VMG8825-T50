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
#ifndef _EMAC_H
#define _EMAC_H

/********* EMAC registers and masks ******************/

/* Arm side FIFO control registers */
#define EMAC_ARM_FIFO_CONTROL		0x0000
#define EMAC_ARM_FIFO_STATUS		0x0004
#define EMAC_ARM_FIFO_IACK		0x0004
#define EMAC_ARM_BIST			0x0008
#define EMAC_ARM_FIFO_TXSIZE		0x0014
#define EMAC_ARM_FIFO_TXHIGH		0x0018
#define EMAC_ARM_FIFO_TXLOW		0x001C
#define EMAC_ARM_FIFO_RXSIZE		0x0024
#define EMAC_ARM_FIFO_RXHIGH		0x0028
#define EMAC_ARM_FIFO_RXLOW		0x002C
#define EMAC_ARM_TXMAIL0		0x0030
#define EMAC_ARM_TXMAIL1		0x0034
#define EMAC_ARM_TXMAIL2		0x0038
#define EMAC_ARM_TXMAIL3		0x003C
#define EMAC_ARM_RXMAIL0		0x0040
#define EMAC_ARM_RXMAIL1		0x0044
#define EMAC_ARM_RXMAIL2		0x0048
#define EMAC_ARM_RXMAIL3		0x004C

#define EMAC_ARM_FIFO_TXDATABYTE	0x4000
#define EMAC_ARM_FIFO_RXDATABYTE	0x4000
#define EMAC_ARM_FIFO_TXDATAHWORD	0x8000
#define EMAC_ARM_FIFO_RXDATAHWORD	0x8000
#define EMAC_ARM_FIFO_TXDATAWORD	0xC000
#define EMAC_ARM_FIFO_RXDATAWORD	0xC000

/* Host side FIFO control registers */
#define EMAC_HOST_FIFO_CONTROL		0xD000
#define EMAC_HOST_FIFO_STATUS		0xD004
#define EMAC_HOST_FIFO_IACK		0xD004
#define EMAC_HOST_FIFO_TXSIZE		0xD010
#define EMAC_HOST_FIFO_TXHIGH		0xD014
#define EMAC_HOST_FIFO_TXLOW		0xD018
#define EMAC_HOST_FIFO_RXSIZE		0xD020
#define EMAC_HOST_FIFO_RXHIGH		0xD024
#define EMAC_HOST_FIFO_RXLOW		0xD028
#define EMAC_HOST_TXMAIL0		0xD030
#define EMAC_HOST_TXMAIL1		0xD034
#define EMAC_HOST_TXMAIL2		0xD038
#define EMAC_HOST_TXMAIL3		0xD03C
#define EMAC_HOST_RXMAIL0		0xD040
#define EMAC_HOST_RXMAIL1		0xD044
#define EMAC_HOST_RXMAIL2		0xD048
#define EMAC_HOST_RXMAIL3		0xD04C

#define EMAC_HOST_FIFO_TXDATA		0xD100
#define EMAC_HOST_FIFO_RXDATA		0xD100

/* EMAC Interface */
#define EMAC_OCR			0xE000
#define EMAC_ICR			0xE004
#define EMAC_IF_INT			0xE008
#define EMAC_OUTPUT			0xE00C
#define EMAC_RX_STAT_FIFO_DEPTH		0xE010
#define EMAC_RX_STAT_FIFO_DATA		0xE020

/* EMAC ARC Table */
#define EMAC_ARC_TABLE			0xE200


/* EMAC IP Flow Control CSR */
#define EMAC_FLOWCTRL_BASE		0xE330

#define EMAC_FLOWCTRL_PAUSECNT		(EMAC_FLOWCTRL_BASE + 0x00)
#define EMAC_FLOWCTRL_REMPAUSECNT	(EMAC_FLOWCTRL_BASE + 0x04)

/* EMAC IP Control CSR */
#define EMAC_CTRL_BASE			0xE340
#define EMAC_MACCTRL			(EMAC_CTRL_BASE + 0x00)
#define EMAC_ARCCTRL			(EMAC_CTRL_BASE + 0x04)
#define EMAC_TXCTRL			(EMAC_CTRL_BASE + 0x08)
#define EMAC_TXSTATUS			(EMAC_CTRL_BASE + 0x0C)
#define EMAC_RXCTRL			(EMAC_CTRL_BASE + 0x10) 
#define EMAC_RXSTATUS			(EMAC_CTRL_BASE + 0x14)

#define EMAC_MDDATA			(EMAC_CTRL_BASE + 0x18)
#define EMAC_MDCA			(EMAC_CTRL_BASE + 0x1C)

#define EMAC_ARCENA			(EMAC_CTRL_BASE + 0x28)

#define EMAC_PROMCTL			(EMAC_CTRL_BASE + 0x2C)
#define EMAC_PROMDATA			(EMAC_CTRL_BASE + 0x30)

#define EMAC_MISSCNT			(EMAC_CTRL_BASE + 0x3C)

#define EMAC_RMON_BASE			0xE400
#define EMAC_CNTDATA			(EMAC_RMON_BASE + 0x00)
#define EMAC_CNTACC			(EMAC_RMON_BASE + 0x04)
#define EMAC_TXRMONIE			(EMAC_RMON_BASE + 0x08)
#define EMAC_RXRMONIE			(EMAC_RMON_BASE + 0x0C)


#define MAX_ARC_ENTRIES 					21

/* ARM fifo control bits */
#define EMAC_ARM_RXDREQWE				0x0004
#define EMAC_ARM_TXDREQRE					0x0008
#define EMAC_ARM_TXCMPLTIE				0x0020
#define EMAC_ARM_TXFIE						0x0040
#define EMAC_ARM_TXTHIE					0x0080
#define EMAC_ARM_RXEIE						0x0100
#define EMAC_ARM_RXTHIE					0x0200
#define EMAC_ARM_TXM3IE					0x0400
#define EMAC_ARM_RXM3IE					0x0800
#define EMAC_ARM_TXFF_RES					0x1000
#define EMAC_ARM_RXFF_RES					0x2000


/* Host fifo control bits */
#define EMAC_HOST_TXFF_EN					0x0001
#define EMAC_HOST_HBTXRQ_EN				0x0002
#define EMAC_HOST_RXFF_EN					0x0008
#define EMAC_HOST_HBRXRQ_EN				0x0010
#define EMAC_HOST_TXCP_INH				0x0020
#define EMAC_HOST_TXEIE					0x0100
#define EMAC_HOST_TXTHIE					0x0200
#define EMAC_HOST_TXM3IE					0x0400
#define EMAC_HOST_RXCMPLTIE				0x0800
#define EMAC_HOST_RXFIE					0x1000
#define EMAC_HOST_RXTHIE					0x2000
#define EMAC_HOST_RXM3IE					0x4000
#define EMAC_HOST_TRGABORTIE				0x8000

/* Memory BIST register masks */
#define EMAC_RXBIST_RESET					0x00000001
#define EMAC_RXBIST_TEST					0x00000002
#define EMAC_RXBIST_DBG					0x00000004
#define EMAC_RXBIST_RESUME_RTN			0x00000008
#define EMAC_RXBIST_DONE					0x00000010
#define EMAC_RXBIST_FAIL					0x00000020
#define EMAC_RXBIST_START_RTN				0x00000040 
#define EMAC_TXBIST_RESET					0x00000100
#define EMAC_TXBIST_TEST					0x00000200
#define EMAC_TXBIST_DBG					0x00000400
#define EMAC_TXBIST_RESUME_RTN			0x00000800
#define EMAC_TXBIST_DONE					0x00001000
#define EMAC_TXBIST_FAIL					0x00002000
#define EMAC_TXBIST_START_RTN				0x00004000

/* EMAC Operation Controling Register masks*/
#define EMAC_OCR_ROMCKSE				0x00000003
#define EMAC_OCR_MDCCKSE				0x0000000C
#define EMAC_OCR_MIIFDL				0x00000010
#define EMAC_OCR_MII100L				0x00000020
#define EMAC_OCR_MIILINKL				0x00000040
#define EMAC_OCR_MIICONN				0x00000080
#define EMAC_OCR_TESTMODE				0x00000100
#define EMAC_OCR_CAMHITL				0x00000200
#define EMAC_OCR_EMACLPBK				0x00000400
#define EMAC_OCR_TOSS_INHIBIT			0x00000800
#define EMAC_OCR_OB_SRESET				0x00001000
#define EMAC_OCR_IB_SRESET				0x00002000
#define EMAC_OCR_IP_HRESET				0x00004000
#define EMAC_OCR_RXPCKSIZE				0x00FF8000
#define EMAC_OCR_RES24					0x01000000
#if defined(CONFIG_COMCERTO_515) || defined(CONFIG_COMCERTO_800)
#define EMAC_OCR_SEL_MII_MODE				0x02000000
#define EMAC_OCR_SW_SMII_OVRD				0x04000000
#define EMAC_OCR_SW_SMII_MODE				0x08000000
#endif
#define EMAC_OCR_STSFFREQIE				0x10000000
#define EMAC_OCR_RXSTATIE				0x20000000
#define EMAC_OCR_TXSTATIE				0x40000000
#define EMAC_OCR_MIIRQIE				0x80000000

/* EMAC Input Controlled Register masks */
#define EMAC_ICR_TXFRMOPT				0x00000007
#if defined(CONFIG_COMCERTO_515) || defined(CONFIG_COMCERTO_800)
#define EMAC_ICR_MII100L_POL				0x00000100
#define EMAC_ICR_MIIFDL_POL				0x00000200
#define EMAC_ICR_MIILINK_POL				0x00000400
#define EMAC_ICR_PHYCTRLDIS				0x00008000
#endif

/* EMAC I/F Interrupt Register Status masks */
#define EMAC_INPUT_STSFFREQIRQ			0x10000000	// Read Only
#define EMAC_INPUT_RXSTATIRQ				0x20000000
#define EMAC_INPUT_TXSTATIRQ				0x40000000
#define EMAC_INPUT_MIIRQIRQ				0x80000000
// EMAC I/F Interrupt Acknowledge Register (same as previsous)
#define EMAC_INPUT_STSFFREQIAK			0x10000000   // Write Only
#define EMAC_INPUT_RXSTATIAK				0x20000000
#define EMAC_INPUT_TXSTATIAK				0x40000000

/* EMAC Output Status masks */
#define EMAC_OUT_REV_ID					0x0000000F
#define REV_SIM								0x0000000E

#define EMAC_OUT_INTLINK					0x00000010
#define EMAC_OUT_CAMLOAD					0x00000020


/* EMAC RX status FIFO data masks */

#define EMAC_RX_STAT_TYPE					0x18000000
#define EMAC_RX_STAT_PKTCNT				0x000000FF
#define EMAC_RX_STAT_IPSTA					0x03FFFFFF



/* EMAC_MACCTRL  bits */
#define MAC_HALTREQ		0x0001
#define MAC_HALTIMM		0x0002
#define MAC_RESET			0x0004
#define MAC_FULLDUP		0x0008
#define MAC_LOOPBACK		0x0010

#define MAC_CONN_MSK		0x0060
#define MAC_AUTORATE		0x0000
#define MAC_10MBITS			0x0020
#define MAC_MIIRATE			0x0040

#define MAC_LOOP10			0x0080
#define MAC_LNKCHG			0x0100
#define MAC_RES9			0x0200
#define MAC_MISSROLL		0x0400
#define MAC_RES11			0x0800
#define MAC_RES12			0x1000
#define MAC_ENMISSROLL		0x2000
#define MAC_RES14			0x4000
#define MAC_LINK10			0x8000

/* EMAC_ARCCTRL bits */

#define ARC_STATIONACC		0x0001
#define ARC_GROUPACC		0x0002
#define ARC_BROADACC		0x0004
#define ARC_NEGARC			0x0008
#define ARC_COMPENA		0x0010
#define ARC_RESERVED		0xFFE0

/* EMAC_TXCTRL bits */
#define TX_EN				0x0001
#define TX_HALT				0x0002
#define TX_NOPAD			0x0004
#define TX_NOCRC			0x0008
#define TX_FBACK			0x0010
#define TX_NOEXDEF			0x0020
#define TX_SDPAUSE			0x0040
#define TX_MII10				0x0080

#define TX_EN_UNDER		0x0100
#define TX_EN_EXDEF			0x0200
#define TX_EN_LCARR			0x0400
#define TX_EN_EXCOLL		0x0800
#define TX_EN_LATECOLL		0x1000
#define TX_EN_TXPAR			0x2000
#define TX_EN_COMP			0x4000

/* EMAC_RXCTRL bits */
#define RX_EN				0x0001
#define RX_HALT				0x0002
#define RX_LONGEN			0x0004
#define RX_SHORTEN			0x0008
#define RX_STRIPCRC			0x0010
#define RX_PASSCTL			0x0020
#define RX_IGNORECRC		0x0040
#define RX_RES7				0x0080 // reserved

#define RX_EN_ALIGN			0x0100
#define RX_EN_CRCERR		0x0200
#define RX_EN_OVERFLOW		0x0400
#define RX_EN_LONGERR		0x0800
#define RX_RES12			0x1000 // reserved
#define RX_EN_RXPAR			0x2000
#define RX_EN_GOOD			0x4000
#define RX_RES15			0x8000 // reserved


#define EMAC_MDIO_WRITE					0x400
#define EMAC_MDIO_BUSY					0x800
#define EMAC_MDIO_PRESUP				0x1000
#define EMAC_MDIO_OPERATION_TIMEOUT		10


#define EMAC_MII_MODE		0
#define EMAC_FORCE_RMII_MODE	1
#define EMAC_FORCE_SMII_MODE	2
#define	EMAC_RMII_SMII_MODE	3

#endif /* _EMAC_H */
