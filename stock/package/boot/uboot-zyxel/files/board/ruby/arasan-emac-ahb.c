/*
 *  board/ums/arasan-emac-ahb.c
 *
 *  U-Boot driver for the Arasan EMAC-AHB Gigabit Ethernet controller.
 *
 *  Copyright (c) Quantenna Communications Incorporated 2007.
 *  All rights reserved.
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
#include <malloc.h>
#include <net.h>
#include <asm/io.h>
#include <command.h>
#include <asm/cache.h>

#ifdef CONFIG_ARASAN_GBE

#include <asm/arch/platform.h>
#include "ar8236.h"
#include "ar8237.h"
#include "ruby_board_cfg.h"
#include "board_cfg.h"
#include <asm/arch/arasan_emac_ahb.h>
#include "ruby.h"

#ifdef UBOOT_ENABLE_ETHERNET_DEBUG
#define DPRINTF(x...) printf(x)
#else
#define DPRINTF(x...)
#endif

static inline unsigned long emac_align_begin(unsigned long addr)
{
	return (addr & (~(ARC_DCACHE_LINE_LEN - 1)));
}

static inline unsigned long emac_align_end(unsigned long addr)
{
	unsigned long aligned = (addr & (~(ARC_DCACHE_LINE_LEN - 1)));
	if (aligned != addr) {
		aligned += ARC_DCACHE_LINE_LEN;
	}
	return aligned;
}

static inline void emac_cache_inv(unsigned long begin, unsigned long end)
{
	invalidate_dcache_range(
		emac_align_begin(begin),
		emac_align_end(end));
}

static inline void emac_cache_flush(unsigned long begin, unsigned long end)
{
	flush_and_inv_dcache_range( /* flush _and_ invalidate to free few cache entries as we are not going to read them back */
		emac_align_begin(begin),
		emac_align_end(end));
}

/* Taken from Linux MII driver */
#define LPA_100FULL             0x0100  /* Can do 100mbps full-duplex  */
#define LPA_100BASE4            0x0200  /* Can do 100mbps 4k packets   */
#define LPA_100HALF             0x0080  /* Can do 100mbps half-duplex  */
#define LPA_10FULL              0x0040  /* Can do 10mbps full-duplex   */
#define LPA_10HALF              0x0020  /* Can do 10mbps half-duplex   */
#define LPA_1000FULL            0x0800  /* Link partner 1000BASE-T full duplex */
#define LPA_1000HALF            0x0400  /* Link partner 1000BASE-T half duplex */

#define ADVERTISE_10FULL        0x0040  /* Try for 10mbps full-duplex  */
#define ADVERTISE_100FULL       0x0100  /* Try for 100mbps full-duplex */
#define ADVERTISE_100HALF       0x0080  /* Try for 100mbps half-duplex */
#define ADVERTISE_1000HALF      0x0100  /* Advertise 1000BASE-T half duplex */
#define ADVERTISE_CSMA          0x0001  /* Only selector supported     */

#define ADVERTISE_FULL          (ADVERTISE_100FULL | ADVERTISE_10FULL | ADVERTISE_CSMA)

#define PHY_MAX_ADDR            32

#define ARASAN_MDIO_BASE        RUBY_ENET0_BASE_ADDR

enum DP83865PhyRegVals {
	/* Basic mode control register */
	PhySoftReset = (1 << 15),
	PhyLoopback = (1 << 14),
	PhySetSpeed1G = ((1 << 6) | (0 << 13)),
	PhySetSpeed100M = ((0 << 6) | (1 << 13)),
	PhySetSpeed10M = ((0 << 6) | (0 << 13)),
	PhyAutoNegEnable = (1 << 12),
	PhyPowerDown = (1 << 11),
	PhyIsolate = (1 << 10),
	PhyRestartAutoNeg = (1 << 9),
	PhyFullDuplex = (1 << 8),
	PhyColTest = (1 << 7),
	/* Basic mode status register */
	PhyAutoNegComplete = (1 << 5),
	/* Link and AutoNegotiation register */
	PhySpeedMask = (3 << 3),
	PhySpeed10M = (0 << 3),
	PhySpeed100M = (1 << 3),
	PhySpeed1G = (2 << 3),
	PhyLinkIsUp = (1 << 2),
	PhyLinkIsFullDuplex = (1 << 1),
	PhyInMasterMode = (1 << 0),
};

enum DP83865RegOffset {
	PhyBMCR = 0,
	PhyBMSR = 1,
	PhyPhysID1 = 2,
	PhyPhysID2 = 3,
	PhyAdvertise = 4,
	PhyLpa = 5,
	PhyStat1000 = 10,
};


/* 8 byte alignment required as DMA is operating in 64 bit mode.
   ARC_DCACHE_LINE_LEN alignment used to have safe cache invalidate/flush.
   As ARC_DCACHE_LINE_LEN is 32, both requirements are satisfied.
*/
static volatile struct emac_desc tx_ring[2] __attribute__ ((aligned (ARC_DCACHE_LINE_LEN)));
static volatile struct emac_desc rx_ring[NUM_RX_BUFS] __attribute__ ((aligned (ARC_DCACHE_LINE_LEN)));
static volatile u8 tx_buf[TX_BUF_SIZE] __attribute__ ((aligned (ARC_DCACHE_LINE_LEN)));
static volatile u8 rx_bufs[NUM_RX_BUFS * RX_BUF_SIZE] __attribute__ ((aligned (ARC_DCACHE_LINE_LEN)));

#undef ENABLE_LOOPBACK
#ifdef ENABLE_LOOPBACK
static u32 loopback = 0 ;
#endif

static struct emac_private priv = {
	.tx_ring_elements = 1,
	.rx_ring_elements = NUM_RX_BUFS,
	.tx_bufs = (u32)&tx_buf,
	.rx_bufs = (u32)&rx_bufs[0],
	.tx_descs = &tx_ring[0],
	.rx_descs = &rx_ring[0],
	.tx_buf_size = TX_BUF_SIZE,
	.rx_buf_size = RX_BUF_SIZE,
	.tx_index = 0,
	.rx_index = 0,
	.ar8236dev = NULL,
	.phy_addr = 0,
	.phy_flags = 0,
};

/* Utility functions for reading/writing registers in the Ethernet MAC */

static u32 emac_rdreg(u32 base, int reg)
{
	return readl(base + reg);
}

static void emac_wrreg(u32 base, int reg, u32 val)
{
	writel(val, base + reg);
}

static void emac_setbits(u32 base, int reg, u32 val)
{
	emac_wrreg(base, reg, emac_rdreg(base, reg) | val);
}

static void emac_clrbits(u32 base, int reg, u32 val)
{
	emac_wrreg(base, reg, emac_rdreg(base, reg) & ~val);
}

/* Utility functions for driving the MDIO interface to the PHY from the MAC */

static int mdio_operation_complete(u32 base)
{
	return !(emac_rdreg(base, EMAC_MAC_MDIO_CTRL) & 0x8000);
}

static void mdio_postrd(u32 base, int phy, int reg)
{
	int i = 0;
	while (!mdio_operation_complete(base)) {
		udelay(1000);
		if (++i >= 2000) {
			return;
		}
	}
	emac_wrreg(base, EMAC_MAC_MDIO_CTRL, (phy & 31) |
			((reg & 31) << 5) | (1 << 10) | (1 << 15));
}

static int mdio_postwr(u32 base, int phy, int reg, u16 val)
{
	int i = 0;

	while (!mdio_operation_complete(base)) {
		udelay(100);
		if (++i >= 20000) {
			return -1;
		}
	}
	emac_wrreg(base, EMAC_MAC_MDIO_DATA, val);
	emac_wrreg(base, EMAC_MAC_MDIO_CTRL, (phy & 31) |
			((reg & 31) << 5) | (1 << 15));
	return 0;
}

/* Check to see if an MDIO posted read command (mdio_postrd) has completed.
 * Returns the u16 data from the read, or (u32)-1 if the data is not available.
 * Setting "wait" to TRUE makes the command poll until the data is available
 * or the command times-out.  Setting "wait" to FALSE stops the command
 * from polling; it only checks if the data is available once.
 */
static u32 mdio_rdval(u32 base, int wait)
{
	int i = 0;
	if (wait) {
		while (!mdio_operation_complete(base)) {
			udelay(100);
			if (++i >= 20000) {
				break;
			}
		}
	}
	if (!mdio_operation_complete(base)) {
		printf("GMII: MDIO read timed out (%08x)\n",
				emac_rdreg(base, EMAC_MAC_MDIO_CTRL));
		return (u32)-1;
	}
	return (u32)emac_rdreg(base, EMAC_MAC_MDIO_DATA);
}

/* Taken from Linux MII support.  Return the link speed based on
 * the IEEE register values from the Ethernet PHY.
 */
static inline unsigned int mii_nway_result(unsigned int negotiated)
{
	unsigned int ret;

	if (negotiated & LPA_100FULL)
		ret = LPA_100FULL;
	else if (negotiated & LPA_100BASE4)
		ret = LPA_100BASE4;
	else if (negotiated & LPA_100HALF)
		ret = LPA_100HALF;
	else if (negotiated & LPA_10FULL)
		ret = LPA_10FULL;
	else
		ret = LPA_10HALF;

	return ret;
}

static void emac_reset_dma(u32 base)
{
	int i = 0;
	u32 val;

	/* Attempt to stop the DMA tx and rx in an orderly fashion */
	emac_clrbits(base, EMAC_DMA_CTRL, DmaStartTx | DmaStartRx);
	do {
		udelay(10000);
		val = emac_rdreg(base, EMAC_DMA_STATUS_IRQ);
		if (++i >= 100) {
			printf("GMII: Failed to stop DMA\n");
			break;
		}
	} while (val & (DmaTxStateMask | DmaRxStateMask));

	/* Don't read any registers whilst the block is reset (it hangs) */
	emac_wrreg(base, EMAC_DMA_CONFIG, DmaSoftReset);
	emac_wrreg(base, EMAC_DMA_CONFIG, 0);
}

static int rx_stats[] = { 0, 1, 2, 3, 4, 5, 6 };
#define NUM_RX_STATS (sizeof(rx_stats) / sizeof(int))

static int tx_stats[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
#define NUM_TX_STATS (sizeof(tx_stats) / sizeof(int))

static void emac_stats(struct eth_device *dev)
{
	int i;
	u32 val;
	int base = dev->iobase;
	int counter;
	int n;

	for(n = 0; n < NUM_RX_STATS; n++)
	{
		counter = rx_stats[n];
		emac_wrreg(base, EMAC_MAC_RXSTAT_CTRL, 0);
		emac_wrreg(base, EMAC_MAC_RXSTAT_CTRL, RxStatReadBusy | counter);
		i = 0;
		do
		{
			if(++i > 10000)
			{
				printf("GMII: Rx Stat timeout for %d\n", counter);
				return;
			}
		}
		while ((val = emac_rdreg(base, EMAC_MAC_RXSTAT_CTRL)) & RxStatReadBusy);
		val = emac_rdreg(base, EMAC_MAC_RXSTAT_DATA_HIGH) << 16;
		val |= (emac_rdreg(base, EMAC_MAC_RXSTAT_DATA_LOW) & 0xffff);
		printf("%d: Rx Stat %d = 0x%08x\n", n, rx_stats[n], val);
	}

	for(n = 0; n < NUM_TX_STATS; n++)
	{
		counter = tx_stats[n];
		emac_wrreg(base, EMAC_MAC_TXSTAT_CTRL, 0);
		emac_wrreg(base, EMAC_MAC_TXSTAT_CTRL, TxStatReadBusy | counter);
		i = 0;
		do
		{
			if(++i > 10000)
			{
				printf("GMII: Tx Stat timeout for %d 0x%08x\n", counter, val);
				return;
			}
		}
		while ((val = emac_rdreg(base, EMAC_MAC_TXSTAT_CTRL)) & TxStatReadBusy);
		val = emac_rdreg(base, EMAC_MAC_TXSTAT_DATA_HIGH) << 16;
		val |= (emac_rdreg(base, EMAC_MAC_TXSTAT_DATA_LOW) & 0xffff);
		printf("%d: Tx Stat %d = 0x%08x\n", n, tx_stats[n], val);
	}

	return;
}

static int emac_reset(struct eth_device *dev, bd_t *bd)
{
	int i;
	u32 base, mdio_base;
	struct emac_private *priv;
	u32 val, x;
	u32 lpa2, media, duplex;

	if (!dev || !dev->priv) {
		return 0;
	}
	priv = (struct emac_private *)dev->priv;
	base = dev->iobase;
	mdio_base = ARASAN_MDIO_BASE;

	emac_reset_dma(base);

	/* Initialise the buffer descriptors for Tx */
	tx_ring[0].status = 0;
	tx_ring[0].control = TxDescEndOfRing;
	tx_ring[0].bufaddr1 = virt_to_bus(&tx_buf);
	tx_ring[0].bufaddr2 = 0;

	/* Initialise the buffer descriptors for Rx */
	for (i = 0; i < sizeof(rx_ring)/sizeof(struct emac_desc); i++) {
		rx_ring[i].status = RxDescOwn;
		rx_ring[i].control = (RX_BUF_SIZE & RxDescBuf1SizeMask)
						<< RxDescBuf1SizeShift;
		rx_ring[i].bufaddr1 = virt_to_bus((void*)(unsigned long)&rx_bufs[i * RX_BUF_SIZE]);
		rx_ring[i].bufaddr2 = 0;
	}
	if (i > 0) {
		rx_ring[i - 1].control |= RxDescEndOfRing;
	}

	priv->rx_index = 0;
	priv->tx_index = 0;

	/* We assume that all registers are in their default states from
	 * reset, so we only update those ones that are necessary.
	 */
	 // !!! FIXME_UMS - do we need Robin+Wait flags here?  | DmaWait4Done
	emac_wrreg(base, EMAC_DMA_CONFIG, Dma16WordBurst | Dma64BitMode |
				DmaRoundRobin );
	emac_wrreg(base, EMAC_DMA_TX_AUTO_POLL, 16);
	emac_wrreg(base, EMAC_DMA_TX_BASE_ADDR, virt_to_bus((void*)(unsigned long)tx_ring));
	emac_wrreg(base, EMAC_DMA_RX_BASE_ADDR, virt_to_bus((void*)(unsigned long)rx_ring));
	(void)emac_rdreg(base, EMAC_DMA_MISSED_FRAMES);
	(void)emac_rdreg(base, EMAC_DMA_STOP_FLUSHES);

	emac_wrreg(base, EMAC_MAC_ADDR_CTRL, MacAddr1Enable);
	emac_wrreg(base, EMAC_MAC_ADDR1_HIGH, *(u16 *)&dev->enetaddr[0]);
	emac_wrreg(base, EMAC_MAC_FLOW_SA_HIGH, *(u16 *)&dev->enetaddr[0]);
	emac_wrreg(base, EMAC_MAC_ADDR1_MED, *(u16 *)&dev->enetaddr[2]);
	emac_wrreg(base, EMAC_MAC_FLOW_SA_MED, *(u16 *)&dev->enetaddr[2]);
	emac_wrreg(base, EMAC_MAC_ADDR1_LOW, *(u16 *)&dev->enetaddr[4]);
	emac_wrreg(base, EMAC_MAC_FLOW_SA_LOW, *(u16 *)&dev->enetaddr[4]);

	/* !!! FIXME_UMS - whether or not we need this depends on whether
	 * the auto-pause generation uses it.  The auto function may just
	 * use 0xffff val to stop sending & then 0 to restart it.
	 */
	//!!!FIXME_UMS emac_wrreg(base, EMAC_MAC_FLOW_PAUSE_TIMEVAL, 0xffff);
	emac_wrreg(base, EMAC_MAC_FLOW_PAUSE_TIMEVAL, 0);

	/* Required by the datasheet */
	// emac_wrreg(base, EMAC_MAC_TX_ALMOST_FULL, 0x8);
	emac_wrreg(base, EMAC_MAC_TX_ALMOST_FULL, 0x1f8);

	/* Use safe store & forward value - valid for all speeds */
	emac_wrreg(base, EMAC_MAC_TX_START_THRESHOLD, 1518);

	emac_wrreg(base, EMAC_MAC_FLOW_CTRL, MacFlowDecodeEnable |
			MacFlowGenerationEnable | MacAutoFlowGenerationEnable |
			MacFlowMulticastMode | MacBlockPauseFrames);

	if (!(priv->phy_flags & EMAC_PHY_NOT_IN_USE)) {
		if (priv->phy_flags & EMAC_PHY_RESET) {
			/* Reset the PHY and wait for autonegotiation to complete.  Set MII or
			 * GMII mode based on the result.
			 */
			mdio_postwr(mdio_base, priv->phy_addr, PhyBMCR, PhySoftReset);
			i = 0;
			printf("Resetting PHY...\n");
			do {
				/* Wait for PHY reset to complete */
				udelay(100000);
				mdio_postrd(mdio_base, priv->phy_addr, PhyBMCR);
				if ((val = mdio_rdval(mdio_base, 1)) == (u32)-1) {
					return 0;
				}
				if (i++ == 50) {
					printf("GMII: PHY Reset stuck");
					return 0;
				}
			} while (val & PhySoftReset);

			printf("GMII: PHY reset complete\n");
			/* Post-reset delay before any other register access allowed
			 * on vitesse PHY.
			 */
			udelay(4);
		}
		if ((priv->phy_flags & EMAC_PHY_AUTO_MASK) == 0) {
			/* Vitesse VSC8641 has a bug regarding writes to register 4 or 9
			* after a soft reset unless an MDIO access occurs in between.
			* We avoid this bug implicitly by the polling loop here.
			*/
			printf("Autonegotiating\n");

			i = 0;
			do {
				/* Wait for autonegotiation to complete */
				udelay(500);
				mdio_postrd(mdio_base, priv->phy_addr, PhyBMSR);
				if ((val = mdio_rdval(mdio_base, 1)) == (u32)-1) {
					return 0;
				}
				if (i++ == 30000) {
					printf("GMII: Autonegotiation timed out\n");
					return 0;
				}
			} while (!(val & PhyAutoNegComplete));

			printf("Autonegotiation complete (BMSR=%08x)\n", val);

			/* Work out autonegotiation result using only IEEE registers */
			{
				u32 advertise, lpa;

				mdio_postrd(mdio_base, priv->phy_addr, PhyAdvertise);
				if ((advertise = mdio_rdval(mdio_base, 1)) == (u32)-1) {
					printf("GMII: Failed to read Advertise reg\n");
					return 0;
				}

				mdio_postrd(mdio_base, priv->phy_addr, PhyLpa);
				if ((lpa = mdio_rdval(mdio_base, 1)) == (u32)-1) {
					printf("GMII: Failed to read Lpa reg\n");
					return 0;
				}

				mdio_postrd(mdio_base, priv->phy_addr, PhyStat1000);
				if ((lpa2 = mdio_rdval(mdio_base, 1)) == (u32)-1) {
					printf("GMII: Failed to read Lpa2 reg\n");
					return 0;
				}

				//printf("Autoneg status: Advertise=%08x, Lpa=%08x, Lpa2=%08x\n",
				//	PhyAdvertise, PhyLpa, PhyStat1000);
				printf("Autoneg status: Advertise=%08x, Lpa=%08x, Lpa2=%08x\n",
						advertise, lpa, lpa2);

				media = mii_nway_result(lpa & advertise);
				duplex = (media & ADVERTISE_FULL) ? 1 : 0;
				if (lpa2 & LPA_1000FULL) {
					duplex = 1;
				}
			}
			printf("GMII: Link speed is ");
		} else {
			duplex = 0;
			lpa2 = 0;
			media = 0;
			if (priv->phy_flags & EMAC_PHY_FORCE_1000MB) {
				i = 0x0040; /* Force 1G */
				lpa2 = LPA_1000FULL;
			} else if (priv->phy_flags & EMAC_PHY_FORCE_100MB) {
				i = 0x2000; /* Force 100M */
				media = ADVERTISE_100FULL;
			} else {
				i = 0x0000; /* Force 10M */
				if (priv->phy_flags & EMAC_PHY_FORCE_10MB ) {
					printf("GMII: ethlink not 10, 100 or 1000 - forcing 10Mbps\n");
				}
			}
			if (!(priv->phy_flags & EMAC_PHY_FORCE_HDX)) {
				i |= 0x100; /* Full duplex */
				duplex = 1;
			}

			mdio_postwr(mdio_base, priv->phy_addr, PhyBMCR, i); /* Force link speed & duplex */
			printf("GMII: Forced link speed is ");
		}
	} else {  // no phy
		duplex = 0;
		lpa2 = 0;
		media = 0;
		if (priv->phy_flags & EMAC_PHY_FORCE_1000MB) {
			i = 0x0040; /* Force 1G */
			lpa2 = LPA_1000FULL;
		} else if (priv->phy_flags & EMAC_PHY_FORCE_100MB) {
			i = 0x2000; /* Force 100M */
			media = ADVERTISE_100FULL;
		} else {
			i = 0x0000; /* Force 10M */
			if (priv->phy_flags & EMAC_PHY_FORCE_10MB ) {
				printf("GMII: ethlink not 10, 100 or 1000 - forcing 10Mbps\n");
			}
		}
		if (!(priv->phy_flags & EMAC_PHY_FORCE_HDX)) {
			i |= 0x100; /* Full duplex */
			duplex = 1;
		}
	}
	x = 0;

	emac_wrreg(RUBY_SYS_CTL_BASE_ADDR, SYSCTRL_CTRL_MASK,
				RUBY_SYS_CTL_MASK_GMII0_TXCLK|RUBY_SYS_CTL_MASK_GMII1_TXCLK);

	if (lpa2 & (LPA_1000FULL | LPA_1000HALF)) {
		x |= MacSpeed1G;
		printf("1G");
		emac_wrreg(RUBY_SYS_CTL_BASE_ADDR, SYSCTRL_CTRL,
			RUBY_SYS_CTL_MASK_GMII0_1000M|RUBY_SYS_CTL_MASK_GMII1_1000M);
	}
	else if (media & (ADVERTISE_100FULL | ADVERTISE_100HALF)) {
		x |= MacSpeed100M;
		printf("100M");
		emac_wrreg(RUBY_SYS_CTL_BASE_ADDR, SYSCTRL_CTRL,
			RUBY_SYS_CTL_MASK_GMII0_100M|RUBY_SYS_CTL_MASK_GMII1_100M);
	}
	else {
		x |= MacSpeed10M;
		printf("10M");
		emac_wrreg(RUBY_SYS_CTL_BASE_ADDR, SYSCTRL_CTRL,
			RUBY_SYS_CTL_MASK_GMII0_10M|RUBY_SYS_CTL_MASK_GMII0_10M);
	}
	emac_wrreg(RUBY_SYS_CTL_BASE_ADDR, SYSCTRL_CTRL_MASK, 0);

	if (duplex) {
		x |= MacFullDuplex;
		printf("-FD\n");
	} else {
		printf("-HD\n");
	}

	/* Flush descriptors */
	emac_cache_flush((unsigned long)tx_ring, (unsigned long)tx_ring + sizeof(tx_ring));
	emac_cache_flush((unsigned long)rx_ring, (unsigned long)rx_ring + sizeof(rx_ring));

	/* Setup speed and run! */
	emac_wrreg(base, EMAC_MAC_GLOBAL_CTRL, x);
	emac_wrreg(base, EMAC_MAC_TX_CTRL, MacTxEnable | MacTxAutoRetry);
	emac_wrreg(base, EMAC_MAC_RX_CTRL, MacRxEnable | MacRxStoreAndForward);
	emac_setbits(base, EMAC_DMA_CTRL, DmaStartTx | DmaStartRx);

	return 1;
}

static void emac_halt(struct eth_device *dev)
{
	int base;

	if (dev) {
		base = dev->iobase;
		emac_clrbits(base, EMAC_MAC_TX_CTRL, MacTxEnable);
		emac_clrbits(base, EMAC_MAC_RX_CTRL, MacRxEnable);
		emac_clrbits(base, EMAC_DMA_CTRL, DmaStartTx | DmaStartRx);
	}
}
/*

static u32 rd_txstatistics_counter(struct eth_device *dev, int counter)
{
	int i = 0;
	u32 val;
	int base = dev->iobase;

	emac_wrreg(base, EMAC_MAC_TXSTAT_CTRL, TxStatReadBusy | counter);
	do {
		if (++i > 10000) {
			printf("GMII: Tx stat read timeout\n");
			return 0;
		}
	}
	while (emac_rdreg(base, EMAC_MAC_TXSTAT_CTRL) & TxStatReadBusy);
	val = emac_rdreg(base, EMAC_MAC_TXSTAT_DATA_HIGH) << 16;
	val |= (emac_rdreg(base, EMAC_MAC_TXSTAT_DATA_LOW) & 0xffff);
	return val;
}

static u32 rd_rxstatistics_counter(struct eth_device *dev, int counter)
{
	int i = 0;
	u32 val;
	int base = dev->iobase;

	emac_wrreg(base, EMAC_MAC_RXSTAT_CTRL, RxStatReadBusy | counter);
	do {
		if (++i > 10000) {
			printf("GMII: Rx stat read timeout\n");
			return 0;
		}
	}
	while (emac_rdreg(base, EMAC_MAC_RXSTAT_CTRL) & RxStatReadBusy);
	val = emac_rdreg(base, EMAC_MAC_RXSTAT_DATA_HIGH) << 16;
	val |= (emac_rdreg(base, EMAC_MAC_RXSTAT_DATA_LOW) & 0xffff);
	return val;
}



static void reset_block(struct eth_device *dev)
{
	emac_wrreg(RUBY_SYS_CTL_BASE_ADDR, SYSCTRL_RESET_MASK, SYSCTRL_ETHERNET_RUN);
	emac_wrreg(RUBY_SYS_CTL_BASE_ADDR, SYSCTRL_RESET, 0);
	emac_wrreg(RUBY_SYS_CTL_BASE_ADDR, SYSCTRL_RESET, SYSCTRL_ETHERNET_RUN);
	emac_resetx(dev, this_bd, 0);
}
*/


static int emac_send(struct eth_device *dev, volatile void *packet, int length)
{
	volatile struct emac_desc *ptx_desc;
	struct emac_private *priv;
	u32 base, now;
	if (!dev || !dev->priv) {
		printf("emac_send: NULL pointer\n");
		return 0;
	}

	base = dev->iobase;
	priv = (struct emac_private *)dev->priv;

	ptx_desc = priv->tx_descs;

	if (readl(&ptx_desc->status) & TxDescOwn) {
		printf("No buffers available\n");
		return 0;
	}

	/* This is a simplification - only handle packets <= 2kB */
	if (length > priv->tx_buf_size) {
		printf("Packet too big\n");
		return 0;
	}

	/* copy packet */
	memcpy((void*)bus_to_virt(ptx_desc->bufaddr1), (void*)packet, length);
	emac_cache_flush((ulong)bus_to_virt(ptx_desc->bufaddr1),
		(ulong)bus_to_virt(ptx_desc->bufaddr1) + length);

	/* do tx */
	writel(TxDescFirstSeg | TxDescLastSeg | TxDescEndOfRing | (length & TxDescBuf1SizeMask) << TxDescBuf1SizeShift,
		&ptx_desc->control);
	writel(TxDescOwn, &ptx_desc->status); /* Hand-off frame to Ethernet DMA engines.. */
	emac_wrreg(base, EMAC_DMA_TX_POLL_DEMAND, 1); /* restart TX */

	/* ..and wait for it to go */
	now = get_timer(0);
	while (readl(&ptx_desc->status) & TxDescOwn) {
		if (get_timer(now) > TX_TIMEOUT_IN_TICKS) {
			printf("Transmit timeout\n");
			writel(0, &ptx_desc->status);
			return 0;
		}
	}

	return length;
}

static int emac_recv(struct eth_device *dev)
{
	volatile struct emac_desc *prx_desc;
	u32 base, length;
	struct emac_private *priv;
	volatile u32 status;

	if (!dev || !dev->priv) {
		return 0;
	}

	base = dev->iobase;
	priv = (struct emac_private *)dev->priv;
	prx_desc = priv->rx_descs + priv->rx_index;

	if ((status = readl(&prx_desc->status)) & RxDescOwn) {
		/* Nothing received yet */
		return 0;
	}

	length = (status >> RxDescFrameLenShift) & RxDescFrameLenMask;
	if (length >= RX_BUF_SIZE) {
		board_reset("\n\n***** reset: emac_recv: oversize packet\n\n");
	}
	if (length > 0) {
		emac_cache_inv((ulong)bus_to_virt(prx_desc->bufaddr1),
			(ulong)bus_to_virt(prx_desc->bufaddr1) + length);
#ifdef ENABLE_LOOPBACK
		if (loopback) {
			//printf("echo back %d\n",length);
			emac_send(dev,ARC_SRAM_ADDRESS(prx_desc->bufaddr1), length);
		} else {
			NetReceive((unsigned char *)bus_to_virt(prx_desc->bufaddr1), length);
		}
#else
		NetReceive((unsigned char *)bus_to_virt(prx_desc->bufaddr1), length);
#endif
	}

	priv->rx_index++;
	if (priv->rx_index == NUM_RX_BUFS) {
		priv->rx_index = 0;
	}
	/* Give descriptor back to the DMA engines */
	writel(RxDescOwn, &prx_desc->status);
	emac_wrreg(base, EMAC_DMA_RX_POLL_DEMAND, 1);

	return 1;
}

int probe_phy(u32 mdio_base,int addr)
{
	int val;
	mdio_postrd(mdio_base, addr, PhyBMCR);
	if ((val = mdio_rdval(mdio_base, 1)) == (u32)-1) {
		printf("Read from MDIO failed.\n");
		return -1;
	}
	return val;
}

static void arasan_initialize_gpio_reset_pin(int pin)
{
	printf("qtn emac init GPIO pin %d reset sequence\n", pin);
	gpio_config(pin, GPIO_MODE_OUTPUT);
	gpio_output(pin, 1);
	udelay(100);
	gpio_output(pin, 0);
	udelay(100000);
	gpio_output(pin, 1);
}

static void arasan_initialize_gpio_reset(uint32_t emac_cfg)
{
	if (emac_cfg & EMAC_PHY_GPIO1_RESET) {
		arasan_initialize_gpio_reset_pin(RUBY_GPIO_PIN1);
	}

	if (emac_cfg & EMAC_PHY_GPIO13_RESET) {
		arasan_initialize_gpio_reset_pin(RUBY_GPIO_PIN13);
	}
}

#define RXTX_DELAY 0x1e0000
struct eth_device *g_eth_dev;
static struct eth_device __g_eth_dev;


u32 get_phy_id (u32 mdio_base,int addr)
{
	int phy_reg;
	u32 phy_id;


	mdio_postrd(mdio_base, addr, PhyPhysID1);
	if ((phy_reg = mdio_rdval(mdio_base, 1)) == (u32)-1) {
		printf("Read from MDIO failed.\n");
		return -1;
	}
	phy_id = (phy_reg & 0xffff) << 16;

	mdio_postrd(mdio_base, addr, PhyPhysID2);
	if ((phy_reg = mdio_rdval(mdio_base, 1)) == (u32)-1) {
		printf("Read from MDIO failed.\n");
		return -1;
	}

	phy_id |= (phy_reg & 0xffff);

	return phy_id;
}

int board_eth_init(bd_t *bis)
{
	DECLARE_GLOBAL_DATA_PTR;
	struct eth_device *dev;
	u32 base, mdio_base;
	int i;
	uint32_t rgmii_timing = board_config(gd->bd->bi_board_id, BOARD_CFG_RGMII_TIMING);
	uint32_t emac0_cfg = board_config(gd->bd->bi_board_id, BOARD_CFG_EMAC0);
	uint32_t emac1_cfg = board_config(gd->bd->bi_board_id, BOARD_CFG_EMAC1);
	uint32_t emac_cfg = emac0_cfg | emac1_cfg;
	u32 phy_id;

	dev = &__g_eth_dev;
	sprintf(dev->name, "QTN-EMAC");

	if (emac0_cfg & EMAC_IN_USE) {
		priv.phy_flags = emac0_cfg;
		dev->iobase = RUBY_ENET0_BASE_ADDR;
		priv.irq = RUBY_IRQ_ENET0;
		priv.phy_addr = board_config(gd->bd->bi_board_id, BOARD_CFG_PHY0_ADDR);
	} else if (emac1_cfg & EMAC_IN_USE) {
		priv.phy_flags = emac1_cfg;
		dev->iobase = RUBY_ENET1_BASE_ADDR;
		priv.irq = RUBY_IRQ_ENET1;
		priv.phy_addr = board_config(gd->bd->bi_board_id, BOARD_CFG_PHY1_ADDR);
	} else {
		printf("error: no emac enabled\n");
		return -1;
	}

	arasan_initialize_gpio_reset(emac_cfg);
	arasan_initialize_release_reset(emac0_cfg, emac1_cfg, rgmii_timing);

	dev->priv = (void *)&priv;
	dev->init = emac_reset;
	dev->halt = emac_halt;
	dev->send = emac_send;
	dev->recv = emac_recv;
	/* We have no ethernet address of our own, we rely on getting
	 * one from the U-Boot environment.
	 */
	for (i = 0; i < 6; i++) {
		dev->enetaddr[i] = 0;
	}

	eth_register(dev);

	emac_halt(dev);
	base = dev->iobase;
	mdio_base = ARASAN_MDIO_BASE;
	
	if (!(priv.phy_flags & EMAC_PHY_NOT_IN_USE)) {
		int found = 0;
		i=0;
		while (i++ < 100) {
			if (priv.phy_addr >= PHY_MAX_ADDR) {
				for (priv.phy_addr = 0;priv.phy_addr < PHY_MAX_ADDR;priv.phy_addr++) {
					int id;
					if ((id = probe_phy(mdio_base,priv.phy_addr)) != 0xffff) {
						printf("PHY found on MDIO addr:%x %d\n",id,priv.phy_addr);
						found = 1;
						break;
					}
					udelay(200);
				}
			} else {
				if (probe_phy(mdio_base,priv.phy_addr) != 0xffff) {
					found = 1;
					break;
				}
				udelay(200);
			}
		}
		if (!found) {
			printf("No PHY found on MDIO addr:%d\n",priv.phy_addr);
			return -1;
		}
		
		/* Reset the PHY which then kick-offs the autonegotiation */
		mdio_postwr(mdio_base, priv.phy_addr, PhyBMCR, PhySoftReset | PhyAutoNegEnable);

		//Turn off 125MHz and enable SSC for Realtek(RTL8211E) VB 
		phy_id = get_phy_id(mdio_base, priv.phy_addr);
		printf("phy ID 0x%x is probed\n",phy_id);
		if (phy_id == 0x1cc915){
			u32 val;
			mdio_postwr(mdio_base, priv.phy_addr, 31, 0);
			mdio_postwr(mdio_base, priv.phy_addr, 16, 0x17E);
			mdio_postwr(mdio_base, priv.phy_addr, 31, 7);
			mdio_postwr(mdio_base, priv.phy_addr, 30, 0xA0);
			mdio_postrd(mdio_base, priv.phy_addr, 26);
			if ((val = mdio_rdval(mdio_base, 1)) == (u32)-1) {
				printf("u-boot: Failed to read phy reg#26\n");
				return 0;
			}
			mdio_postwr(mdio_base, priv.phy_addr, 26, val&~4);
			mdio_postwr(mdio_base, priv.phy_addr, 31, 0);
			printf("Enable phy SSC\n");
			}

		/* This is a dummy read that ensures the write has happened */
		if (mdio_rdval(mdio_base, 1) == (u32)-1) {
			return -1;
		}
	} else if (priv.phy_flags & EMAC_PHY_AR8236) {
		// ignore error - it has already been reported,
		// not much else we can really do
		priv.phy_addr = ar8236_init(mdio_base,priv.phy_addr);
	} else if (priv.phy_flags & EMAC_PHY_AR8327) {
		// ignore error - it has already been reported,
		// not much else we can really do
		priv.phy_addr = ar8237_init(mdio_base,priv.phy_addr);
		//printf("call 8327 init mdio_base[0x%x],priv.phy_addr[0x%x] \r\n",mdio_base,priv.phy_addr);
	}

        // Pass all multicast packets because it should be support multiboot server
        emac_wrreg(dev->iobase, EMAC_MAC_TABLE1, 0xffff);
        emac_wrreg(dev->iobase, EMAC_MAC_TABLE2, 0xffff);
        emac_wrreg(dev->iobase, EMAC_MAC_TABLE3, 0xffff);
        emac_wrreg(dev->iobase, EMAC_MAC_TABLE4, 0xffff);
        emac_clrbits(dev->iobase, EMAC_MAC_ADDR_CTRL, MacPromiscuous);

	g_eth_dev = dev;
	return 1;
}

int do_mdio(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	u32 base = ARASAN_MDIO_BASE;
	if (argc < 4) {
		cmd_usage(cmdtp);
		return 1;
	}
	if (strcmp(argv[1],"read") == 0) {
		u32 a1,a2,val;
		a1 = simple_strtoul (argv[2], NULL, 10);
		a2 = simple_strtoul (argv[3], NULL, 16);
		mdio_postrd(base, a1,a2);
		val = mdio_rdval(base, 1);
		printf("phy:%d reg:%d=0x%x\n",a1,a2,val);
	} else if (strcmp(argv[1],"write") == 0) {
		u32 a1, a2, a3;
		a1 = simple_strtoul (argv[2], NULL, 10);
		a2 = simple_strtoul (argv[3], NULL, 10);
		a3 = simple_strtoul (argv[4], NULL, 16);
		mdio_postwr(base, a1,a2,a3);
		/* This is a dummy read that ensures the write has happened */
		if (mdio_rdval(base, 1) == (u32)-1) {
			return -1;
		}
	} else {
		return -1;
	}

	return 0;
}

#if defined(CONFIG_CMD_ETHLOOP)
int mdio_write(int reg, u16 val)
{
	u32 base = ARASAN_MDIO_BASE;
	int ret = -1;
	ret = mdio_postwr(base, priv.phy_addr, reg, val);
	/* This is a dummy read that ensures the write has happened */
	if (mdio_rdval(base, 1) == (u32)-1)
		return -1;

	return ret;
}

int mdio_read(int reg)
{
	u32 val, base = ARASAN_MDIO_BASE;
	mdio_postrd(base, priv.phy_addr, reg);
	val = mdio_rdval(base, 1);
	return val;
}

void enable_phy_loopback(void)
{
	u32 val;
	val = mdio_read(PhyBMCR);
	val |= PhyLoopback;  /* set loopback bit */
	mdio_write(PhyBMCR, val);
}

void disable_phy_loopback(void)
{
	u32 val;
	val = mdio_read(PhyBMCR);
	val &= ~PhyLoopback; /* reset loopback bit */
	mdio_write(PhyBMCR, val);
}
#endif

#if 0

#ifdef ENABLE_LOOPBACK
int do_emaclb(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	int a1;
    a1 = simple_strtoul (argv[1], NULL, 16);
    if (a1 == 0) {
    	loopback = 0;
    } else {
    	loopback = 1;
    }
    while (1) {
    		NetLoop (NETCONS);	/* kind of poll */
	}
    return 0;
}

U_BOOT_CMD(
	emaclb, CFG_MAXARGS, 2, do_emaclb,
	"emaclb - set emac loopback (0 or 1) \n",
	NULL
);
#endif
#endif
#define CFG_MAXARGS 5
U_BOOT_CMD(
	mdio, CFG_MAXARGS, 5, do_mdio,
	"read/write mdio",
	"mdio <read|write> <phy> <reg> <hex value>"
);

int do_emac(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	emac_stats(g_eth_dev);
	return 0;
}
U_BOOT_CMD(
	emac, CFG_MAXARGS, 3, do_emac,
	"emac read stats",
	NULL
);
#endif

