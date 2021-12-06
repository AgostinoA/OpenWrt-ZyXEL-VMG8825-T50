/*
 * comcerto_gem.c
 * Mindspeed Comcerto GEMAC driver
 *
 * From TSEC.c 
 *
 * This software may be used and distributed according to the
 * terms of the GNU Public License, Version 2, incorporated
 * herein by reference.
 *
 * Copyright 2004 Freescale Semiconductor.
 * (C) Copyright 2003, Motorola, Inc.
 * author Andy Fleming
 *
 */

#include <common.h>
#include <config.h>
#include <asm/arch/hardware.h>
#include <asm/byteorder.h>
#include <malloc.h>
#include <net.h>
#include <command.h>
#include <miiphy.h>

#if defined(CONFIG_COMCERTO_GEMAC)
#include "comcerto_gem.h"

DECLARE_GLOBAL_DATA_PTR;

static struct gemac_info_struct gemac_info[] = {
#if defined(CONFIG_COMCERTO_900) || defined(CONFIG_COMCERTO_100)
	{GEMAC_BASEADDR, MMGEM0_START, GEMAC0_PHY_ADDR, GEMAC0_CONFIG, GEMAC0_MODE, GEMAC0_PHY_FLAGS, GEMAC0_PHYIDX},
#elif defined(CONFIG_COMCERTO_1000)
	{GEMAC_BASEADDR, GEMAC0_PHY_ADDR, GEMAC0_CONFIG, GEMAC0_MODE, GEMAC0_PHY_FLAGS, GEMAC0_PHYIDX},
#else
	{0, 0, 0},
#endif
#if defined(CONFIG_COMCERTO_100)
	{GEMAC1_BASEADDR, MMGEM1_START, GEMAC1_PHY_ADDR, GEMAC1_CONFIG, GEMAC1_MODE, GEMAC1_PHY_FLAGS, GEMAC1_PHYIDX},
#elif defined(CONFIG_COMCERTO_1000)
	{GEMAC1_BASEADDR, GEMAC1_PHY_ADDR, GEMAC1_CONFIG, GEMAC1_MODE, GEMAC1_PHY_FLAGS, GEMAC1_PHYIDX},
#else
	{0, 0, 0},
#endif
};

#define MAX_GEMACS	2

static struct gemac_dev *gemac_list[MAX_GEMACS];

#define NUM_RX_DESC		16
#define MAX_RX_BUFF_SIZE	2048

static u32 rx_next;

#if defined(CONFIG_COMCERTO_100)
static u8 rx_ring_data_buff[NUM_RX_DESC * MAX_RX_BUFF_SIZE] __attribute((aligned(4)));
static struct fdesc rx_ring[NUM_RX_DESC] __attribute((aligned(16)));
static struct fdesc tx_fdesc __attribute((aligned(16)));
#else
static u8 rx_ring_data_buff[NUM_RX_DESC * MAX_RX_BUFF_SIZE] __attribute((aligned(16)));
static struct rx_desc rx_ring[NUM_RX_DESC] __attribute((aligned(16)));
static struct tx_desc tx_fdesc[2] __attribute((aligned(8)));
#endif

/* Initialize device structure. Returns success if PHY
 * initialization succeeded (i.e. if it recognizes the PHY)
 */

static void default_speed_duplex(struct gemac_dev *gemac, int *speed, int *duplex)
{
	switch (gemac->mode & GEM_CONF_SPEED_MASK) {
	case GEM_CONF_SPEED_GEM_10M:
		*speed = _10BASET;
		break;

	case GEM_CONF_SPEED_GEM_100M:
		*speed = _100BASET;
		break;

	case GEM_CONF_SPEED_GEM_1G:
	default:
		*speed = _1000BASET;
		break;
	}

	if (gemac->mode & GEM_CONF_DUPLEX_GEM_FULL)
		*duplex = FULL;
	else
		*duplex = HALF;
}

static void gemt_reinit(struct gemac_dev *gemac, int speed, int duplex)
{
	switch (speed) {
	case _1000BASET:
		printf("PHY 1000Mbit ");
		gem_set_speed(gemac, SPEED_1000M);
		break;

	case _100BASET:
		printf("PHY 100Mbit ");
		gem_set_speed(gemac, SPEED_100M);
		break;

	default:
	case _10BASET:
		printf("PHY 10Mbit ");
		gem_set_speed(gemac, SPEED_10M);
		break;
	}

	switch (duplex) {
	case FULL:
		printf("FD\n");
		gem_full_duplex(gemac);
		break;

	default:
	case HALF:
		printf("HD\n");
		gem_half_duplex(gemac);
		break;
	}
}

#if defined(CONFIG_MII) || defined(CONFIG_CMD_MII)

static int gemt_PHY_timeout(struct gemac_dev *gemac, int timeout)
{
	while (!gem_phy_man_idle(gemac)) {

		if (timeout-- <= 0) {
			printf("PHY MDIO read/write timeout\n");
			return -1;
		}

		udelay(1);
	}

	return 0;
}

static struct gemac_dev *get_gemac(char *devname)
{
	int i;

	for (i = 0; i < MAX_GEMACS; i++) {
		if (!strcmp(gemac_list[i]->dev->name, devname))
			return gemac_list[i];
	}

	return NULL;
}

static int comcerto_miiphy_write(char *devname, unsigned char addr, unsigned char reg, unsigned short value)
{
	struct gemac_dev *gemac = get_gemac(devname);

	if (!gemac) {
		printf("Unknown device %s\n", devname);
		return -1;
	}

	if ((addr > 31) || (reg > 31))
		return -1;

	gem_phy_man_wr(gemac, addr, reg, value);
	if (gemt_PHY_timeout(gemac, MDIO_TIMEOUT))
		return -1;

	return 0;
}

static int comcerto_miiphy_read(char *devname, unsigned char addr, unsigned char reg, unsigned short *value)
{
	struct gemac_dev *gemac = get_gemac(devname);

	if (!gemac) {
		printf("Unknown device %s\n", devname);
		return -1;
	}

	if ((addr > 31) || (reg > 31))
		return -1;

	gem_phy_man_rd(gemac, addr, reg);
	if (gemt_PHY_timeout(gemac, MDIO_TIMEOUT))
		return -1;

	*value = gem_phy_man_data(gemac);

	return 0;
}

/*=============================================================================
 *
 * NAME: gemt_config_PHY
 * 
 * PARAMETERS:   
 *   net_device *dev    -INOUT
 *
 * DESCRIPTION   
 *   Reconfigure PHY
 *   This function will set up the PHY device.  This is a required external
 *   support routine.
 *   The parameters set up the maximum desired advertised ability for the 
 *   device.
 *   TODO - read back negotiated ability and set MAC appropriately.
 *          duplex configuration to be done.
 *
 * ASSUMPTIONS
 *   None
 *
 * SIDE EFFECTS / STATIC DATA USE
 *   None
 *
 * RETURNS:      
 *   int        0       -successful
 *              <0      -failed
 *
 *===========================================================================*/
static int gemt_config_PHY(struct gemac_dev *gemac, int phy_addr, MAC_SPEED speed, u8 duplex)
{
	unsigned short anar, bmcr, btcr;

	if (gemac->phyflags & GEMAC_M88E1111_PHY_RGMII_ADD_DELAY) {
		unsigned short tmp;

		if (!miiphy_read(gemac->dev->name, phy_addr, 20, &tmp)) {
			tmp |= 0x82;
			miiphy_write(gemac->dev->name, phy_addr, 20, tmp);
		}
	}

	if (miiphy_reset(gemac->dev->name, gemac->phyaddr))
		return -1;

	switch (speed) {
	case _10BASET:
		if (duplex == FULL) {
			anar = PHY_ANAR_10FD | PHY_ANAR_10;
			btcr = 0x0;
			bmcr = PHY_BMCR_DPLX | PHY_BMCR_10_MBPS;
		} else {
			anar = PHY_ANAR_10;
			btcr = 0x0;
			bmcr = PHY_BMCR_10_MBPS;
		}

		break;

	case _100BASET:
	default:
		if (duplex == FULL) {
			anar = PHY_ANAR_TXFD | PHY_ANAR_TX | PHY_ANAR_10FD | PHY_ANAR_10;
			btcr = 0x0;
			bmcr = PHY_BMCR_DPLX | PHY_BMCR_100_MBPS;
		} else {
			anar = PHY_ANAR_TX | PHY_ANAR_10;
			btcr = 0x0;
			bmcr = PHY_BMCR_100_MBPS;
		}

		break;

	case _1000BASET:
		if (duplex == FULL) {
			anar = PHY_ANAR_TXFD | PHY_ANAR_TX | PHY_ANAR_10FD | PHY_ANAR_10;
			btcr = PHY_1000BTCR_1000FD | PHY_1000BTCR_1000HD;
			bmcr = PHY_BMCR_DPLX | PHY_BMCR_1000_MBPS;
		} else {
			anar = PHY_ANAR_TX | PHY_ANAR_10;
			btcr = PHY_1000BTCR_1000HD;
			bmcr = PHY_BMCR_1000_MBPS;
		}

		break;
	}

	if (gemac->phyflags & GEMAC_PHY_AUTONEG) {
		if (miiphy_write(gemac->dev->name, phy_addr, PHY_ANAR, anar | PHY_ANAR_PSB_802_3))
			return -1;

		if (miiphy_supports_1000base_t(gemac->dev->name, phy_addr)) {
			if (miiphy_write(gemac->dev->name, phy_addr, PHY_1000BTCR, btcr))
				return -1;
		}

		if (miiphy_write(gemac->dev->name, phy_addr, PHY_BMCR, PHY_BMCR_AUTON | PHY_BMCR_RST_NEG | bmcr))
			return -1;
	} else {
		if (miiphy_write(gemac->dev->name, phy_addr, PHY_BMCR, bmcr))
			return -1;
	}

#if defined(CONFIG_GPHY_AR8035_DELAY_TUNING)
	config_emac_phy_delay(phy_addr);
#endif

	return 0;
}

#endif /* defined(CONFIG_MII) || defined(CONFIG_CMD_MII) */

/*=============================================================================
 *
 * NAME: gemt_reset_gem
 * 
 * PARAMETERS:   
 *   net_device *dev    -INOUT
 *
 * DESCRIPTION   
 *   Reset MAC hardware
 *   This function will reset MAC hardware after stop the MAC for both 
 *   transmission and reception.
 *
 * ASSUMPTIONS
 *   None
 *
 * SIDE EFFECTS / STATIC DATA USE
 *   None
 *
 * RETURNS:      
 *   None
 *
 *===========================================================================*/
static void gemt_reset_gem(struct gemac_dev *gemac)
{
	gem_abort_tx(gemac);
	gem_disable_rx(gemac);

	gem_mask_irq(gemac, GEM_IRQ_ALL);
	gem_get_irq_stat(gemac);

	if (gem_reset(gemac) != 0)
		printf("Failed to reset device!\n");
}

#if defined(CONFIG_COMCERTO_100)
static void gemac_rx_ring_init(struct gemac_dev *gemac)
{
	u32 i;
	u8 *pU8 = rx_ring_data_buff;

	for (i = 0; i < NUM_RX_DESC - 1; i++) {
		rx_ring[i].next = (void *)(__cpu_to_le32((u32)&(rx_ring[i + 1])));
		rx_ring[i].system = __cpu_to_le32(i);
		rx_ring[i].fstatus = __cpu_to_le32(0);
		rx_ring[i].fcontrol = __cpu_to_le32(IDMA_FCONTROL_FREADY);
		rx_ring[i].bdesc.bptr = (volatile u8 *)(__cpu_to_le32((u32)pU8));
		rx_ring[i].bdesc.bcontrol = __cpu_to_le32(0);
		pU8 += MAX_RX_BUFF_SIZE;
	}

	rx_ring[i].next = (void *)(__cpu_to_le32((u32)&(rx_ring[0])));
	rx_ring[i].system = __cpu_to_le32(i);
	rx_ring[i].fstatus = __cpu_to_le32(0);
	rx_ring[i].fcontrol = __cpu_to_le32(0);
	rx_ring[i].bdesc.bptr = (volatile u8 *)(__cpu_to_le32((u32)pU8));
	rx_ring[i].bdesc.bcontrol = __cpu_to_le32(0);

	rx_next = 0;
}

static int gemac_send(struct eth_device *dev, volatile void *packet, int length)
{
	struct gemac_dev *gemac = (struct gemac_dev *)dev->priv;
	int i;

	if (length <= 0) {
		printf("Comcerto_Emac: bad packet size: %d\n", length);
		return (-1);
	}

	memset(&tx_fdesc, 0, sizeof(struct fdesc));

	// build the tx frame descriptor here
	tx_fdesc.fcontrol = __cpu_to_le32(IDMA_FCONTROL_FREADY | IDMA_FCONTROL_FLAST);
	tx_fdesc.fstatus = __cpu_to_le32(0);
	tx_fdesc.bdesc.bptr = (volatile u8 *)(__cpu_to_le32((u32)((u8 *)packet)));
	tx_fdesc.bdesc.bcontrol = __cpu_to_le32(length | IDMA_BCONTROL_BLAST);

	// Check if DMA Stopped
	if (!(*(volatile u32 *)(gemac->idma_baseaddr + MMEM_START) & __cpu_to_le32(IDMA_START))) {
		*(volatile u32 *)(gemac->idma_baseaddr + MMEM_HEAD) = __cpu_to_le32((u32) &tx_fdesc);
		*(volatile u32 *)(gemac->idma_baseaddr + MMEM_START) |= __cpu_to_le32(IDMA_START);
	} else {
		printf("Emac: tx EDMA busy!\n");
		return (-1);
	}

	i = 0;
	while ((tx_fdesc.fstatus & __cpu_to_le32(IDMA_FSTATUS_FRAME_DONE_MASK)) == 0) {
		udelay(100);
		i++;
		if (i == 50000) {
			printf("Emac: tx timed out!\n");
			return (-1);
		}
	}

	if (*(volatile u32 *)(gemac->idma_baseaddr + MMEM_START) & __cpu_to_le32(IDMA_START)) {
		printf("Error! Emac: tx did not stop after sending a packet!\n");
	}

	return (length);
}

static int gemac_recv(struct eth_device *dev)
{
	struct gemac_dev *gemac = (struct gemac_dev *)dev->priv;
	int rx_prev;
	int length;
	int total_length = 0;

	// loop thru rx FDescs
	while (1) {
		if ((rx_ring[rx_next].fstatus & __cpu_to_le32(IDMA_FSTATUS_FRAME_DONE_MASK)) == 0)
			break;

		// mark rx_next not usable
		rx_ring[rx_next].fcontrol = __cpu_to_le32(0);

		length = __le32_to_cpu(rx_ring[rx_next].bdesc.bcontrol) & 0x0000ffff;
		if (length > MAX_RX_BUFF_SIZE) {
			printf("Comcerto_Emac: frame too big (%d bytes)!\n", length);
			length = MAX_RX_BUFF_SIZE;
		}

		// Pass the packet up to the protocol layers.
                NetReceive((volatile uchar *)(__le32_to_cpu((u32)(rx_ring[rx_next].bdesc.bptr))), length);
		total_length += length;

		// rx_prev can be used now
		if (rx_next == 0)
			rx_prev = NUM_RX_DESC - 1;
		else
			rx_prev = rx_next - 1;

		rx_ring[rx_prev].fstatus = __cpu_to_le32(0);
		rx_ring[rx_prev].fcontrol = __cpu_to_le32(IDMA_FCONTROL_FREADY);

		rx_next++;
		if (rx_next == NUM_RX_DESC)
			rx_next = 0;
	}

	// Check if DMA Stopped
	// if RX is stopped, restart
	if (!(*(volatile u32 *)(gemac->idma_baseaddr + EMMM_START) & __cpu_to_le32(IDMA_START))) {
		*(volatile u32 *)(gemac->idma_baseaddr + EMMM_HEAD) = __cpu_to_le32((u32) (&(rx_ring[rx_next])));
		*(volatile u32 *)(gemac->idma_baseaddr + EMMM_START) |= __cpu_to_le32(IDMA_START);
	}

	return (total_length);
}

/* Stop the interface */
static void gemac_halt(struct eth_device *dev)
{
	struct gemac_dev *gemac = (struct gemac_dev *)dev->priv;

	*(volatile u32 *)(gemac->idma_baseaddr + MMEM_SOFT_RESET) = __cpu_to_le32(1);
	*(volatile u32 *)(gemac->idma_baseaddr + EMMM_SOFT_RESET) = __cpu_to_le32(1);

	gem_stop_tx(gemac);
	gem_disable_rx(gemac);
}

#else
static void gemac_rx_ring_init(struct gemac_dev *gemac)
{
	u8 *pU8;
	int i;

//	printf("%s()\n", __func__);

	memset(rx_ring, 0, NUM_RX_DESC * sizeof(struct rx_desc));
	pU8 = rx_ring_data_buff;

	for (i = 0; i < NUM_RX_DESC - 1; i++) {
		rx_ring[i].data = (volatile u8 *)(__cpu_to_le32((u32)pU8));
		pU8 += MAX_RX_BUFF_SIZE;
	}

	rx_ring[i].data = (volatile u8 *)(__cpu_to_le32((u32)pU8));
	rx_ring[i].status |= __cpu_to_le32(GEMRX_WRAP);	// last descriptor in the list
	rx_next = 0;
	*(volatile u32 *)(gemac->baseaddr + GEM_IP + GEM_RX_QPTR) = __cpu_to_le32((u32)rx_ring);
}

static int gemac_send(struct eth_device *dev, volatile void *packet, int length)
{
	struct gemac_dev *gemac = (struct gemac_dev *)dev->priv;
	int i, rc = -1;

	if (length <= 0) {
		printf("Comcerto_Emac: bad packet size: %d\n", length);
		return (-1);
	}

	// build the tx frame descriptor here
	memset(&tx_fdesc, 0, 2 * sizeof(struct tx_desc));

	tx_fdesc[0].ctl |= __cpu_to_le32(TX_DESC_WORD1_LAST | TX_DESC_WORD1_FCS);
	tx_fdesc[0].data = (volatile u8 *)(__cpu_to_le32((u32)packet));
	tx_fdesc[0].ctl |= __cpu_to_le32(length & TX_DESC_WORD1_LEGTH_MASK);
	tx_fdesc[1].ctl |= __cpu_to_le32(TX_DESC_WORD1_WRAP | TX_DESC_WORD1_USED);

	// just enable queue0, let the other queues uninitialized
	*(volatile u32 *)(gemac->baseaddr + GEM_IP + GEM_QUEUE_BASE0) = __cpu_to_le32((u32)&tx_fdesc[0]);

	gem_start_tx(gemac);
	// Notify scheduler
	*(volatile u32 *)(gemac->baseaddr + GEM_SCH_PKT_QUEUED) = __cpu_to_le32((u32) length);

	i = 0;
	while ((tx_fdesc[0].ctl & __cpu_to_le32(TX_DESC_WORD1_USED)) == 0) {
		udelay(100);
		i++;
		if (i == 50000) {
			printf("Emac: tx timed out!\n");
			goto out;
		}
	}

	rc = length;
//      printf("gemac_send done \n");
out:

	return rc;
}

static int gemac_recv(struct eth_device *dev)
{
	int length = 0;
	int total_length = 0;
	u32 rx_status;
	u32 rx_data;
	u32 rx_extstatus;

	// loop thru rx FDescs
	while (1) {

		rx_extstatus = rx_ring[rx_next].extstatus;
		if (((rx_extstatus & __cpu_to_le32(GEMRX_OWN)) == 0)) {
//			printf("done %d index %d\n",total_length, rx_next); 
			break;
		}

		rx_data = __le32_to_cpu(rx_ring[rx_next].data);
		rx_status = __le32_to_cpu(rx_ring[rx_next].status);
		length = (rx_status & RX_STA_LEN_MASK) /*>>RX_STA_LEN_POS */ ;

		// Pass the packet up to the protocol layers.
		if (!(rx_status & RX_CHECK_ERROR)) {
			NetReceive((u8 *)rx_data, length);
			total_length += length;
		}

		//clear bits... the buffer can be reused
		rx_ring[rx_next].status &= __cpu_to_le32(GEMRX_WRAP);
		rx_ring[rx_next].extstatus = __cpu_to_le32(0);
		length = 0;

		rx_next++;
		if (rx_next == NUM_RX_DESC)
			rx_next = 0;
	}

	return (total_length);
}

/* Stop the interface */
static void gemac_halt(struct eth_device *dev)
{
	struct gemac_dev *gemac = (struct gemac_dev *)dev->priv;

//	printf("%s()\n", __func__);

	gem_stop_tx(gemac);
	gem_abort_tx(gemac);
	gem_disable_rx(gemac);
}
#endif

#if (!defined(CONFIG_COMCERTO_1000) && (defined(CONFIG_MII) || defined(CONFIG_CMD_MII)))
int miiphy_speed_duplex (char *devname, unsigned char addr, int *speed, int *duplex)
{
	*speed = miiphy_speed (devname, addr);
	*duplex = miiphy_duplex (devname, addr);
	return 0;
}
#endif

/* Initializes data structures and registers for the controller,
 * and brings the interface up.	 Returns the link status, meaning
 * that it returns success if the link is up, failure otherwise.
 * This allows u-boot to find the first active controller. */
static int gemac_init(struct eth_device *dev, bd_t * bd)
{
	struct gemac_dev *gemac = (struct gemac_dev *)dev->priv;
	MAC_ADDR enet_addr;
	int speed = _1000BASET, duplex = FULL;

//	printf("%s()\n", __func__);

	/* Make sure the controller is stopped */
	gemac_halt(dev);

	default_speed_duplex(gemac, &speed, &duplex);

#if defined(CONFIG_MII) || defined(CONFIG_CMD_MII)
	if (!(gemac->phyflags & GEMAC_NO_PHY))
		if (miiphy_speed_duplex(gemac->dev->name, gemac->phyaddr, &speed, &duplex))
			return -1;
#endif /* defined(CONFIG_MII) || defined(CONFIG_CMD_MII) */

	gemt_reinit(gemac, speed, duplex);

	gem_disable_copy_all(gemac);
	gem_allow_broadcast(gemac);
	gem_enable_unicast(gemac);
	gem_disable_multicast(gemac);
	gem_disable_fcs_rx(gemac);

	gem_enet_addr_byte_mac(dev->enetaddr, &enet_addr);
	gem_set_laddr1(gemac, &enet_addr);

	gemac_rx_ring_init(gemac);

	/* Ready the device for tx/rx */
	gem_start_tx(gemac);
	gem_enable_rx(gemac);

	return (1);
}

int comcerto_gemac_initialize(bd_t * bis, int index, char *devname)
{
	struct eth_device *dev;
	struct gemac_dev *gemac;
	int i;

	dev = (struct eth_device *)malloc(sizeof(struct eth_device));
	if (!dev)
		return -1;

	memset(dev, 0, sizeof(struct eth_device));

	gemac = (struct gemac_dev *)malloc(sizeof(struct gemac_dev));
	if (!gemac)
		return -1;

	gemac_list[index] = gemac;
	gemac->baseaddr = (void *)gemac_info[index].baseaddr;
	gemac->registers = (void *)(gemac_info[index].baseaddr + GEM_IP);
	gemac->phyregisters = (void *)(gemac_info[gemac_info[index].phyregidx].baseaddr + GEM_IP);
	gemac->phyaddr = gemac_info[index].phyaddr;
	gemac->mode = gemac_info[index].mode;

#if defined(CONFIG_COMCERTO_100)
	gemac->idma_baseaddr = (void *)(gemac_info[index].idma_baseaddr);
#endif
	gemac->phyflags = gemac_info[index].phyflags;
	sprintf(dev->name, devname);
	dev->iobase = 0;
	dev->priv = gemac;
	gemac->dev = dev;
	dev->init = gemac_init;
	dev->halt = gemac_halt;
	dev->send = gemac_send;
	dev->recv = gemac_recv;

	/* Tell u-boot to get the addr from the env */
	for (i = 0; i < 6; i++)
		dev->enetaddr[i] = 0;

	eth_register(dev);

	/* put gemac out of reset */
#if defined(CONFIG_COMCERTO_100)
	{
// TODO: please cleanup need centralize the reset bock
		volatile int delay_count;

		// get GEMAC out of reset
		*(volatile u32 *)(BLOCK_RESET_REG) |= __cpu_to_le32(GEMAC0_RST << index);
		// 20 ops delay
		delay_count = 20;
		while (delay_count--) ;
	}
#else
	{
		// TODO: please cleanup need centralize the reset bock
		volatile int delay_count;

		// get GEMAC out of reset
		*(volatile u32 *)(CLKCORE_BLK_RESET) |=
		    __cpu_to_le32((BLK_RESET_GEMAC0_AHB_RESET_N << index) | (BLK_RESET_GEMAC0_REF_RESET_N << index));
		// 20 ops delay
		delay_count = 20;
		while (delay_count--) ;
	}
#endif

#if !defined(CONFIG_COMCERTO_MII_CFG_BOOTSTRAP)
	// software config
	switch (gemac_info[index].gemacconfig) {
	case CONFIG_COMCERTO_USE_GMII:
		*(volatile u32 *)(gemac->baseaddr + GEM_CFG) = __cpu_to_le32(gemac->mode | GEM_CONF_MODE_SEL_GEM | GEM_CONF_MODE_GEM_GMII);
		break;
	case CONFIG_COMCERTO_USE_RGMII:
		*(volatile u32 *)(gemac->baseaddr + GEM_CFG) = __cpu_to_le32(gemac->mode | GEM_CONF_MODE_SEL_GEM | GEM_CONF_MODE_GEM_RGMII);
		break;
	case CONFIG_COMCERTO_USE_RMII:
		*(volatile u32 *)(gemac->baseaddr + GEM_CFG) = __cpu_to_le32(gemac->mode | GEM_CONF_MODE_SEL_GEM | GEM_CONF_MODE_GEM_RMII);
		break;
	case CONFIG_COMCERTO_USE_MII:
		*(volatile u32 *)(gemac->baseaddr + GEM_CFG) = __cpu_to_le32(gemac->mode | GEM_CONF_MODE_SEL_GEM | GEM_CONF_MODE_GEM_MII);
		break;
	default:
		printf("comcerto gemac software config requires one MII mode defined %d\n");
		return (-1);
	}
#else
	*(volatile u32 *)(gemac->baseaddr + GEM_CFG) = __cpu_to_le32(gemac->mode);
#endif

#if defined(CONFIG_COMCERTO_1000)
	if ((gemac->phyflags & GEMAC_GEM_DELAY_DISABLE))
		*(volatile u32 *)(gemac->baseaddr + GEM_DELAY_ELEMENT_CTRL) = __cpu_to_le32(0);
#endif

#if defined(CONFIG_COMCERTO_100)
	*(volatile u32 *)(gemac->baseaddr + GEM_TX_CTRL) = __cpu_to_le32(GEM_TXCTRL_DMAIF_EN | GEM_TXCTRL_CRC_EN | GEM_TXCTRL_RETR_EN);
	*(volatile u32 *)(gemac->baseaddr + GEM_RX_CTRL) = __cpu_to_le32(GEM_RXCTRL_DMAIF_EN);
	*(volatile u32 *)(gemac->baseaddr + GEM_RX_STAT_PKTSIZE) = __cpu_to_le32(0x100);
	*(volatile u32 *)(gemac->baseaddr + GEM_ARM_FIFO_CTRL) = __cpu_to_le32(ARM_FIFO_RXDREQWE | ARM_FIFO_TXDREQRE);
	*(volatile u32 *)(gemac->baseaddr + GEM_ARM_RX_FIFO_HIGH) = __cpu_to_le32(0x1D0);
	*(volatile u32 *)(gemac->baseaddr + GEM_ARM_RX_FIFO_LOW) = __cpu_to_le32(0x180);
	*(volatile u32 *)(gemac->baseaddr + GEM_RX_FIFO_HIGH) = __cpu_to_le32(0x1CD);
	*(volatile u32 *)(gemac->baseaddr + GEM_FIFO_CTRL) = __cpu_to_le32(GEM_FIFO_CTRL_TXFF_EN | GEM_FIFO_CTRL_HBTXRQ_EN | GEM_FIFO_CTRL_RXFF_EN | GEM_FIFO_CTRL_HBRXRQ_EN);
#else
	/* configure DMA register */
	/* enable scheduler */
	*(volatile u32 *)(gemac->baseaddr + GEM_IP + GEM_DMA_CONFIG) |= __cpu_to_le32((1UL << 31));

	/* Master enable scheduler block*/
	*(volatile u32 *)(gemac->baseaddr + GEM_SCH_CTL) |= __cpu_to_le32(1UL);

	/* enable 16 bytes aligned bursts */
	*(volatile u32 *)(gemac->baseaddr + GEM_IP + GEM_DMA_CONFIG) |= __cpu_to_le32((1UL << 27));

	/* enable software buffer allocation (legacy mode) */
	*(volatile u32 *)(gemac->baseaddr + GEM_IP + GEM_DMA_CONFIG) |= __cpu_to_le32((1UL << 26));
	*(volatile u32 *)(gemac->baseaddr + GEM_IP + GEM_DMA_CONFIG) |= __cpu_to_le32((1UL << 25));

	*(volatile u32 *)(gemac->baseaddr + GEM_IP + GEM_DMA_CONFIG) &= __cpu_to_le32(~(0x00FF001F));

	/* set buffer size to 2048 bytes */
	*(volatile u32 *)(gemac->baseaddr + GEM_IP + GEM_DMA_CONFIG) |= __cpu_to_le32(0x00200000);

	/* attempt to use INCR16 AHB bursts */
	*(volatile u32 *)(gemac->baseaddr + GEM_IP + GEM_DMA_CONFIG) |= __cpu_to_le32(0x00000010);

	/* disable admittance manager */
	*(volatile u32 *)(gemac->baseaddr + GEM_IP + GEM_DMA_CONFIG) &= __cpu_to_le32(~(1UL << 12));

 	/* disable admittance master config bit */
 	*(volatile u32 *)(gemac->baseaddr + ADMITTANCE + ADM_CFG) &= ~(1UL);

#endif
	/* Reset the MAC */
	gemt_reset_gem(gemac);

	if (index == 0) {
#if defined(CONFIG_COMCERTO_100)
/* todo remove this from this file */
		// set ephy divider and switch to ref clk (25Mhz)
		*(volatile u32 *)(CLKCORE_CLKDIV_CNTRL) &= __cpu_to_le32(~(0x1F << EPHY_CLKDIV_RATIO_SHIFT));
		*(volatile u32 *)(CLKCORE_CLKDIV_CNTRL) |= __cpu_to_le32(((CFG_ARM_CLOCK / 25000000) << EPHY_CLKDIV_RATIO_SHIFT));
		*(volatile u32 *)(CLKCORE_CLKDIV_CNTRL) &= __cpu_to_le32(~EPHY_CLKDIV_BYPASS);
#endif
		reset_emac0_phy(1);
	}

	if (index == 1) {
		reset_emac1_phy(1);
	}

#if defined(CONFIG_MII) || defined(CONFIG_CMD_MII)
	gem_enable_MDIO(gemac);

	if (!(gemac->phyflags & GEMAC_NO_PHY)) {
		int speed, duplex;

		miiphy_register(dev->name, comcerto_miiphy_read, comcerto_miiphy_write);

		default_speed_duplex(gemac, &speed, &duplex);

		if (gemt_config_PHY(gemac, gemac->phyaddr, speed, duplex))
			return -1;
	}
#endif

	return 0;
}

#endif /* CONFIG_COMCERTO_GEMAC */
