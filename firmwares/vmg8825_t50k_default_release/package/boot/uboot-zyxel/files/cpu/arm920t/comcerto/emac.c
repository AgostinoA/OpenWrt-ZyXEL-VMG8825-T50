/*
 * (C) Copyright 2006
 * Mindspeed Technologies
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
#if defined(CONFIG_CMD_NET) && defined(CONFIG_COMCERTO_EMAC)

#if !defined(CONFIG_EMAC0) && !defined(CONFIG_EMAC1)
#error must define one of CONFIG_EMAC0 or CONFIG_EMAC1
#endif

#include <asm/io.h>
#include <asm/hardware.h>
#include <net.h>

#if defined(CONFIG_MII) || defined(CONFIG_CMD_MII)
#include <miiphy.h>
#endif

#define MAX_DEVNAME_SIZE	8

struct bdesc {
	volatile u8 *bptr;
	volatile u32 bcontrol;
	u32 dummy1;
	u32 dummy2;
};

struct fdesc {
	/* Hardware mapped fields */
	void *next;		/* 4 bytes */
	volatile u32 system;	/* 4 bytes */
	volatile u32 fstatus;	/* 4 bytes */
	volatile u32 fcontrol;	/* 4 bytes */
	struct bdesc bdesc;	/* 16 bytes */
};


struct emac_dev {
	char devname[MAX_DEVNAME_SIZE];

	u32 baseaddr;
	u32 idma_baseaddr;

	s8 miifdl;
	s8 mii100l;

	unsigned int md_clk;
	u8 phy_addr;

	u8 mii_mode;
	u8 phyctrldis;
	u8 mii_link_pol;
};


static struct emac_dev emac0 = {
	.devname = "emac0",
	.baseaddr = EMAC0_BASEADDR,
	.idma_baseaddr = IDMA_EMAC0_BASEADDR,

#ifdef CONFIG_EMAC0_MIIFDL
	.miifdl = CONFIG_EMAC0_MIIFDL,
#else
	.miifdl = -1,
#endif

#ifdef CONFIG_EMAC0_MII100L
	.mii100l = CONFIG_EMAC0_MII100L,
#else
	.mii100l = -1,
#endif

#ifdef CONFIG_EMAC0_MII_MODE
	.mii_mode = CONFIG_EMAC0_MII_MODE,
#else
	.mii_mode = EMAC_RMII_SMII_MODE,
#endif

#ifdef CONFIG_EMAC0_PHYCTRLDIS
	.phyctrldis = CONFIG_EMAC0_PHYCTRLDIS,
#else
	.phyctrldis = 0x1,
#endif

#if CONFIG_EMAC0_MII_LINK_POL
	.mii_link_pol = CONFIG_EMAC0_MII_LINK_POL,
#else
	.mii_link_pol = 0x0,
#endif

#ifdef CONFIG_EMAC0_MDCLOCK
	.md_clk = CONFIG_EMAC0_MDCLOCK,
#else
	.md_clk = 2500000,
#endif

#ifdef CONFIG_EMAC0_PHY_ADDR
	.phy_addr = CONFIG_EMAC0_PHY_ADDR,
#else
	.phy_addr = 0x00,
#endif
};

#ifdef CONFIG_COMCERTO_800
static struct emac_dev emac1 = {
	.devname = "emac1",
	.baseaddr = EMAC1_BASEADDR,
	.idma_baseaddr = IDMA_EMAC1_BASEADDR,

#ifdef CONFIG_EMAC1_MIIFDL
	.miifdl = CONFIG_EMAC1_MIIFDL,
#else
	.miifdl = -1,
#endif

#ifdef CONFIG_EMAC1_MII100L
	.mii100l = CONFIG_EMAC1_MII100L,
#else
	.mii100l = -1,
#endif

#ifdef CONFIG_EMAC1_MII_MODE
	.mii_mode = CONFIG_EMAC1_MII_MODE,
#else
	.mii_mode = EMAC_RMII_SMII_MODE,
#endif

#ifdef CONFIG_EMAC1_PHYCTRLDIS
	.phyctrldis = CONFIG_EMAC1_PHYCTRLDIS,
#else
	.phyctrldis = 0x1,
#endif

#if CONFIG_EMAC1_MII_LINK_POL
	.mii_link_pol = CONFIG_EMAC1_MII_LINK_POL,
#else
	.mii_link_pol = 0x0,
#endif

#ifdef CONFIG_EMAC1_MDCLOCK
	.md_clk = CONFIG_EMAC1_MDCLOCK,
#else
	.md_clk = 2500000,
#endif

#ifdef CONFIG_EMAC1_PHY_ADDR
	.phy_addr = CONFIG_EMAC1_PHY_ADDR,
#else
	.phy_addr = 0x00,
#endif
};
#endif /* CONFIG_COMCERTO_800 */

#ifdef CONFIG_EMAC0
static struct emac_dev *emac = &emac0;
#else
static struct emac_dev *emac = &emac1;
#endif

#define NUM_RX_DESC		16
#define MAX_RX_BUFF_SIZE	2048

static u32 rx_next;
static u8 rx_ring_data_buff[NUM_RX_DESC * MAX_RX_BUFF_SIZE];

static struct fdesc buff_aligned[NUM_RX_DESC] __attribute((aligned(16)));

static struct fdesc tx_fdesc __attribute((aligned(16)));

static struct fdesc *rx_ring;

#define EMAC_disable_rx(emac)\
	*(volatile u32 *)((emac)->baseaddr + EMAC_RXCTRL) &= ~RX_EN

#define EMAC_disable_tx(emac)\
	*(volatile u32 *)((emac)->baseaddr + EMAC_TXCTRL) &= ~TX_EN

#define EMAC_enable_rx(emac)\
	*(volatile u32 *)((emac)->baseaddr + EMAC_RXCTRL) |= RX_EN

#define EMAC_enable_tx(emac)\
	*(volatile u32 *)((emac)->baseaddr + EMAC_TXCTRL) |= TX_EN


static int get_mdcckse(int md_clk)
{
	unsigned int div = CFG_HZ_CLOCK / md_clk;

	if (div > 60)
		return 0x3;
	else if (div > 28)
		return 0x2;
	else if (div > 16)
		return 0x1;
	else
		return 0x0;
}

#if defined(CONFIG_MII) || defined(CONFIG_CMD_MII)

static int comcerto_miiphy_write(char *devname, unsigned char addr,
			unsigned char reg, unsigned short value)
{
	struct emac_dev *emac;

	if ((addr > 31) || (reg > 31))
		return 1;

	if (!strcmp(devname, emac0.devname))
		emac = &emac0;
#ifdef CONFIG_COMCERTO_800
	else if (!strcmp(devname, emac1.devname))
		emac = &emac1;
#endif
	else
		return -1;

	if (*(volatile u32 *)(emac->baseaddr + EMAC_MDCA) & EMAC_MDIO_BUSY)
		return 1;

	/* start a write */
	*(volatile u32 *)(emac->baseaddr + EMAC_MDDATA) = value;
	*(volatile u32 *)(emac->baseaddr + EMAC_MDCA) = (reg | (addr << 5) | EMAC_MDIO_WRITE | EMAC_MDIO_BUSY);

	while (*(volatile u32 *)(emac->baseaddr + EMAC_MDCA) & EMAC_MDIO_BUSY) ;

	return 0;
}


static int comcerto_miiphy_read(char *devname, unsigned char addr,
			unsigned char reg, unsigned short *value)
{
	struct emac_dev *emac;

	if ((addr > 31) || (reg > 31))
		return 1;

	if (!strcmp(devname, emac0.devname))
		emac = &emac0;
#ifdef CONFIG_COMCERTO_800
	else if (!strcmp(devname, emac1.devname))
		emac = &emac1;
#endif
	else
		return -1;

	if (*(volatile u32 *)(emac->baseaddr + EMAC_MDCA) & EMAC_MDIO_BUSY)
		return 1;

	*(volatile u32 *)(emac->baseaddr + EMAC_MDCA) = (reg | (addr << 5) | EMAC_MDIO_BUSY);

	while (*(volatile u32 *)(emac->baseaddr + EMAC_MDCA) & EMAC_MDIO_BUSY) ;

	*value = *(volatile u32 *)(emac->baseaddr + EMAC_MDDATA);

	return 0;
}


static u32 get_ocr_mii_cfg(struct emac_dev *emac, u32 ocr)
{
	unsigned short tmp;

	miiphy_read(emac->devname, emac->phy_addr, PHY_BMSR, &tmp);

#ifdef CFG_FAULT_ECHO_LINK_DOWN
	if (miiphy_link(emac->devname, emac->phy_addr))
		ocr &= ~EMAC_OCR_MII100L;
	else
		ocr |= EMAC_OCR_MII100L;
#else
	ocr &= ~EMAC_OCR_MII100L;
#endif /* CFG_FAULT_ECHO_LINK_DOWN */
	if (emac->miifdl < 0) {
		/* get link duplex from phy */
		if (miiphy_duplex(emac->devname, emac->phy_addr) == HALF)
			ocr |= EMAC_OCR_MIIFDL;
		else
			ocr &= ~EMAC_OCR_MIIFDL;
	} else {
		/* force link duplex */
		if (emac->miifdl)
			ocr |= EMAC_OCR_MIIFDL;
		else
			ocr &= ~EMAC_OCR_MIIFDL;
	}

	if (emac->mii100l < 0) {
		/* get link speed from phy */
		if (miiphy_speed(emac->devname, emac->phy_addr) == _10BASET)
			ocr |= EMAC_OCR_MII100L;
		else
			ocr &= ~EMAC_OCR_MII100L;
	} else {
		/* force link speed */
		if (emac->mii100l)
			ocr |= EMAC_OCR_MII100L;
		else
			ocr &= ~EMAC_OCR_MII100L;
	}

	return ocr;
}

#else

static u32 get_ocr_mii_cfg(struct emac_dev *emac, u32 ocr)
{
	ocr &= ~EMAC_OCR_MII100L;

	if (emac->miifdl < 0) {
		ocr &= ~EMAC_OCR_MIIFDL;
	} else {
		/* force link duplex */
		if (emac->miifdl)
			ocr |= EMAC_OCR_MIIFDL;
		else
			ocr &= ~EMAC_OCR_MIIFDL;
	}

	if (emac->mii100l < 0) {
		ocr &= ~EMAC_OCR_MII100L;
	} else {
		/* force link speed */
		if (emac->mii100l)
			ocr |= EMAC_OCR_MII100L;
		else
			ocr &= ~EMAC_OCR_MII100L;
	}

	return ocr;
}
#endif /* defined(CONFIG_MII) || defined(CONFIG_CMD_MII) */


#ifdef CONFIG_NET_MULTI

#else
int comcerto_miiphy_initialize(bd_t *bis)
{
#if defined(CONFIG_MII) || defined(CONFIG_CMD_MII)
	u32 ocr;

#ifdef CONFIG_EMAC0
	ocr = *(volatile u32 *)(emac0.baseaddr + EMAC_OCR);
	ocr &= ~(0x3 << 2);
	*(volatile u32 *)(emac0.baseaddr + EMAC_OCR) = ocr | (get_mdcckse(emac0.md_clk) << 2);
	miiphy_register(emac0.devname, comcerto_miiphy_read, comcerto_miiphy_write);
#endif

#ifdef CONFIG_EMAC1
	ocr = *(volatile u32 *)(emac1.baseaddr + EMAC_OCR);
	ocr &= ~(0x3 << 2);
	*(volatile u32 *)(emac1.baseaddr + EMAC_OCR) = ocr | (get_mdcckse(emac1.md_clk) << 2);
	miiphy_register(emac1.devname, comcerto_miiphy_read, comcerto_miiphy_write);
#endif

#endif /* defined(CONFIG_MII) || defined(CONFIG_CMD_MII) */

	return 0;
}
#endif /* CONFIG_NET_MULTI */

static int emac_arc_add(struct emac_dev *emac, u8 *mac_addr)
{
	u32 temp;
	u8 offset = 0;

	/* we are in boot loader, even though this EMAC handles more than 20 entries,
	   we only gonna use one (Entry 0) */

	temp = *mac_addr++;
	temp <<= 8;
	temp |= *mac_addr++;
	temp <<= 8;
	temp |= *mac_addr++;
	temp <<= 8;
	temp |= *mac_addr++;
	*(volatile u32 *)(emac->baseaddr + EMAC_ARC_TABLE + offset) = temp;
	offset += 4;
	temp = *mac_addr++;
	temp <<= 8;
	temp |= *mac_addr++;
	temp <<= 16;
	*(volatile u32 *)(emac->baseaddr + EMAC_ARC_TABLE + offset) = ((*(volatile u32 *)(emac->baseaddr + EMAC_ARC_TABLE + offset)) & 0x0000FFFF) | temp;

	*(volatile u32 *)(emac->baseaddr + EMAC_ARCENA) |= 1;
	*(volatile u32 *)(emac->baseaddr + EMAC_ARCCTRL) |= ARC_COMPENA;

	return 1;
}


static void emac_rx_ring_init(void)
{
	u32 i;
	u8 *pU8;

	pU8 = rx_ring_data_buff;
	rx_ring = buff_aligned;

	for (i = 0; i < NUM_RX_DESC - 1; i++) {
		rx_ring[i].next = &rx_ring[i + 1];
		rx_ring[i].system = i;
		rx_ring[i].fstatus = 0;
		rx_ring[i].fcontrol = IDMA_FCONTROL_FREADY;
		rx_ring[i].bdesc.bptr = pU8;
		rx_ring[i].bdesc.bcontrol = 0;
		pU8 += MAX_RX_BUFF_SIZE;
	}

	rx_ring[i].next = &rx_ring[0];
	rx_ring[i].system = i;
	rx_ring[i].fstatus = 0;
	rx_ring[i].fcontrol = 0;
	rx_ring[i].bdesc.bptr = pU8;
	rx_ring[i].bdesc.bcontrol = 0;

	rx_next = 0;
}

static void emac_ip_init(struct emac_dev *emac)
{
	u32 i;

	/* EMAC_MACCTRL register : set FullDup (as MII_Conn is high), Conn as Force MII, and Soft reset */
	*(volatile u32 *)(emac->baseaddr + EMAC_MACCTRL) = MAC_FULLDUP | MAC_MIIRATE | MAC_RESET;

	/* wait reset done */
	while (*(volatile u32 *)(emac->baseaddr + EMAC_MACCTRL) & MAC_RESET) ;

	/* EMAC_ARC_TABLE init */
	for (i = 0; i < (6 * MAX_ARC_ENTRIES); i += 4)
		*(volatile u32 *)((emac->baseaddr + EMAC_ARC_TABLE) + i) = 0;

	/* EMAC_ARCENA : set to 0 as no ARC entry yet */
	*(volatile u32 *)(emac->baseaddr + EMAC_ARCENA) = 0;

	/* EMAC_ARCCTRL : accept BroadCast only (Local MAC address no yet defined) */
	*(volatile u32 *)(emac->baseaddr + EMAC_ARCCTRL) = ARC_BROADACC;

	/* EMAC_TXCTRL  : set Tx_en */
	*(volatile u32 *)(emac->baseaddr + EMAC_TXCTRL) = TX_EN;

	/* EMAC_RXCTRL  : set Rx_en, Strip CRC, ShortEn, */
	*(volatile u32 *)(emac->baseaddr + EMAC_RXCTRL) = RX_EN | RX_STRIPCRC | RX_SHORTEN;
}


static void emac_ipif_init(struct emac_dev *emac)
{
	u32 ocr, icr;

#ifdef CONFIG_COMCERTO_530
	ocr = 0x00200200 | (get_mdcckse(emac->md_clk) << 2);	/* force 100Mbit, full duplex, link up */
	icr = 0x00000000;

	ocr = get_ocr_mii_cfg(emac, ocr);
#else
	ocr = 0x00200200 | (get_mdcckse(emac->md_clk) << 2);	/* force 100Mbit, full duplex, link up */
	icr = 0x00008000;					/* use software settings */

	switch (emac->mii_mode) {
	case EMAC_MII_MODE:
		ocr |= EMAC_OCR_SEL_MII_MODE;
		break;

	case EMAC_FORCE_RMII_MODE:
		ocr &= ~EMAC_OCR_SEL_MII_MODE;
		ocr |= EMAC_OCR_SW_SMII_OVRD;
		ocr &= ~EMAC_OCR_SW_SMII_MODE;
		break;

	case EMAC_FORCE_SMII_MODE:
		ocr &= ~EMAC_OCR_SEL_MII_MODE;
		ocr |= EMAC_OCR_SW_SMII_OVRD;
		ocr |= EMAC_OCR_SW_SMII_MODE;
		break;

	case EMAC_RMII_SMII_MODE:
	default:
		ocr &= ~EMAC_OCR_SEL_MII_MODE;
		ocr &= ~EMAC_OCR_SW_SMII_OVRD;
		break;
	}

	switch (emac->mii_mode) {
	case EMAC_MII_MODE:
		ocr = get_ocr_mii_cfg(emac, ocr);
		break;

	case EMAC_FORCE_RMII_MODE:
	case EMAC_FORCE_SMII_MODE:
	case EMAC_RMII_SMII_MODE:
	default:
		if (emac->phyctrldis) {
			icr |= EMAC_ICR_PHYCTRLDIS;

			ocr = get_ocr_mii_cfg(emac, ocr);

		} else {
			icr &= ~EMAC_ICR_PHYCTRLDIS;
			icr &= ~(EMAC_ICR_MII100L_POL | EMAC_ICR_MIIFDL_POL | EMAC_ICR_MIILINK_POL);
			icr |= (emac->mii_link_pol & 0x7) << 8;
		}

		break;
	}
#endif

	/* Init EMAC Operation Controlling Register */
	*(volatile u32 *)(emac->baseaddr + EMAC_OCR) = ocr;
	*(volatile u32 *)(emac->baseaddr + EMAC_ICR) = icr;

	/* init DMA TX/RX Data FIFO Config Registers */
	*(volatile u32 *)(emac->baseaddr + EMAC_HOST_FIFO_CONTROL) = EMAC_HOST_HBTXRQ_EN | EMAC_HOST_RXFF_EN | EMAC_HOST_HBTXRQ_EN | EMAC_HOST_TXFF_EN;

	/* TX threshold  Host =EMAC */
	*(volatile u32 *)(emac->baseaddr + EMAC_HOST_FIFO_TXHIGH) = 0x000F3;

	*(volatile u32 *)(emac->baseaddr + EMAC_HOST_FIFO_TXLOW) = 0x00F0;

	/* RX threshold */
	*(volatile u32 *)(emac->baseaddr + EMAC_HOST_FIFO_RXHIGH) = 0x0013;
	*(volatile u32 *)(emac->baseaddr + EMAC_HOST_FIFO_RXLOW) = 0x0012;

	/* arm side */

	*(volatile u32 *)(emac->baseaddr + EMAC_ARM_FIFO_TXHIGH) = 0x00C0;
	*(volatile u32 *)(emac->baseaddr + EMAC_ARM_FIFO_TXLOW) = 0x0020;

	/* RX threshold */
	*(volatile u32 *)(emac->baseaddr + EMAC_ARM_FIFO_RXHIGH) = 0x00E0;
	*(volatile u32 *)(emac->baseaddr + EMAC_ARM_FIFO_RXLOW) = 0x0040;
	*(volatile u32 *)(emac->baseaddr + EMAC_ARM_FIFO_CONTROL) = EMAC_ARM_RXDREQWE | EMAC_ARM_TXDREQRE;

	*(volatile u32 *)ASA_TERMINAL_COUNT_CFG |= ASA_TC_REQIDMAEN;

}


static void emac_dma_init(struct emac_dev *emac)
{
	/* Init IDMA */
	/* Memory to EMAC (Tx) */
	*(volatile u32 *)(emac->idma_baseaddr + MMEM_BURST) = (IDMA_BURST_MASK & 0xFF) | (IDMA_PRTY_MASK & 0x0200);	/* burst size 255, priority 1 */
	*(volatile u32 *)(emac->idma_baseaddr + MMEM_START) = 0;

	/* EMAC to Memory (Rx) */
	*(volatile u32 *)(emac->idma_baseaddr + EMMM_BURST) = (IDMA_BURST_MASK & 0xFF) | (IDMA_PRTY_MASK & 0x0100);	/* burst size 255, priority 1 */  
	*(volatile u32 *)(emac->idma_baseaddr + EMMM_START) = 0;
}


static int emac_init(struct emac_dev *emac, u8 *mac_addr)
{
	*(volatile u32 *)(emac->idma_baseaddr + EMMM_SOFT_RESET) = 0x1;
	*(volatile u32 *)(emac->idma_baseaddr + MMEM_SOFT_RESET) = 0x1;

	*(volatile u32 *)(emac->baseaddr + EMAC_OCR) |= EMAC_OCR_IP_HRESET;
	udelay(100);
	*(volatile u32 *)(emac->baseaddr + EMAC_OCR) &= ~EMAC_OCR_IP_HRESET;

	emac_ipif_init(emac);
	emac_ip_init(emac);
	emac_dma_init(emac);

	/* Add Mac Address in the ARC table */
	emac_arc_add(emac, mac_addr);

	/* Init Ehternet buffers */
	emac_rx_ring_init();

	/* Start Rx EDMA */
	*(volatile u32 *)(emac->idma_baseaddr + EMMM_HEAD) = (u32) &rx_ring[rx_next];
	*(volatile u32 *)(emac->idma_baseaddr + EMMM_START) |= IDMA_START;

	return 0;
}


static int emac_send(struct emac_dev *emac, volatile void *packet, int length)
{
	int i;

	memset(&tx_fdesc, 0, sizeof(struct fdesc));

	/* build the tx frame descriptor here */
	tx_fdesc.fcontrol = IDMA_FCONTROL_FREADY | IDMA_FCONTROL_FLAST;
	tx_fdesc.fstatus = 0;
	tx_fdesc.bdesc.bptr = packet;
	tx_fdesc.bdesc.bcontrol = length | IDMA_BCONTROL_BLAST;

	/* Check if DMA Stopped */
	if (!(*(volatile u32 *)(emac->idma_baseaddr + MMEM_START) & IDMA_START)) {
		*(volatile u32 *)(emac->idma_baseaddr + MMEM_HEAD) = (u32) &tx_fdesc;
		*(volatile u32 *)(emac->idma_baseaddr + MMEM_START) |= IDMA_START;
	} else {
		printf("Emac: tx EDMA busy!\n");
		return (-1);
	}

	i = 0;
	while ((tx_fdesc.fstatus & IDMA_FSTATUS_FRAME_DONE_MASK) == 0) {
		udelay(100);
		i++;
		if (i == 50000) {
			printf("Emac: tx timed out! %x\n", tx_fdesc.fstatus);
			return (-1);
		}
	}

	if (*(volatile u32 *)(emac->idma_baseaddr + MMEM_START) & IDMA_START) {
		printf("Emac: tx did not stop after sending a packet!\n");
	}

	return (length);
}


static int emac_rx(struct emac_dev *emac)
{
	int rx_prev;
	int length;
	int total_length = 0;

	/* loop thru rx FDescs */
	while (1) {
		if ((rx_ring[rx_next].fstatus & IDMA_FSTATUS_FRAME_DONE_MASK) == 0)
			break;

		/* mark rx_next not usable */
		rx_ring[rx_next].fcontrol = 0;

		if (rx_ring[rx_next].fstatus & (1 << 10)) {

			length = rx_ring[rx_next].bdesc.bcontrol & IDMA_BCONTROL_BLEN_MASK;
			if (length > MAX_RX_BUFF_SIZE) {
				printf("Emac: frame too big (%d bytes)!\n", length);
				length = MAX_RX_BUFF_SIZE;
			}

			/* Pass the packet up to the protocol layers. */
			NetReceive(rx_ring[rx_next].bdesc.bptr, length);
			total_length += length;
		}

		/* rx_prev can be used now */
		if (rx_next == 0)
			rx_prev = NUM_RX_DESC - 1;
		else
			rx_prev = rx_next - 1;

		rx_ring[rx_prev].fstatus = 0;
		rx_ring[rx_prev].fcontrol = IDMA_FCONTROL_FREADY;

		rx_next++;
		if (rx_next == NUM_RX_DESC)
			rx_next = 0;
	}

	/* Check if DMA Stopped, if RX is stopped, restart */
	if (!(*(volatile u32 *)(emac->idma_baseaddr + EMMM_START) & IDMA_START)) {
		*(volatile u32 *)(emac->idma_baseaddr + EMMM_HEAD) = (u32) &rx_ring[rx_next];
		*(volatile u32 *)(emac->idma_baseaddr + EMMM_START) |= IDMA_START;
	}

	return (total_length);
}


static void emac_halt(struct emac_dev *emac)
{
	/* stop EMAC */
	EMAC_disable_rx(emac);
	EMAC_disable_tx(emac);

	*(volatile u32 *)(emac->idma_baseaddr + EMMM_SOFT_RESET) = 0x1;
	*(volatile u32 *)(emac->idma_baseaddr + MMEM_SOFT_RESET) = 0x1;
}

#ifdef CONFIG_NET_MULTI

#else
int eth_send(volatile void *packet, int length)
{
	if (length <= 0) {
		printf("Emac: bad packet size: %d\n", length);
		return (-1);
	}

	return emac_send(emac, packet, length);
}

int eth_init(bd_t * bd)
{
	return emac_init(emac, bd->bi_enetaddr);
}


int eth_rx(void)
{
	return emac_rx(emac);
}

void eth_halt(void)
{
	emac_halt(emac);
}

#endif /* CONFIG_NET_MULTI */
#endif /* CFG_CMD_NET && defined(CONFIG_COMCERTO_EMAC) */
