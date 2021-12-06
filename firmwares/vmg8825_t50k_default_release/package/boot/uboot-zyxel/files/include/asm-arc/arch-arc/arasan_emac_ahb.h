/*
 *  include/asm-arc/arch-arc/arasan_emac_ahb.h
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
 *
 * This file only defines those settings that are specific to U-Boot.
 * All the common definitions are stored in ruby_arasan_emac_ahb.
 *
 */

#ifndef __ASM_ARCH_ARASAN_EMAC_AHB_H
#define __ASM_ARCH_ARASAN_EMAC_AHB_H	1

#define TX_BUF_SIZE	2048
#define NUM_RX_BUFS	4
#define RX_BUF_SIZE	2048

#define TX_TIMEOUT_IN_TICKS (CONFIG_SYS_HZ)

/* All the common defines for the Ethernet controller */
//#include "../../../../common/ruby_arasan_emac_ahb.h"
#include "ruby_arasan_emac_ahb.h"

#ifndef __ASSEMBLY__

/* Shortened version of the equivalent Linux structure - U-Boot does not 
 * need most of the members that Linux does.
*/
struct emac_private {
	int tx_ring_elements; /* = number of buffers = number of descriptors */
	int rx_ring_elements; /* = number of buffers = number of descriptors */
	
	u32 rx_bufs;
	u32 tx_bufs;
	volatile struct emac_desc *rx_descs;
	volatile struct emac_desc *tx_descs;
	u32 rx_buf_size;
	u32 tx_buf_size;	
	int rx_index;
	int tx_index;
	
	// pointer to switch device
	void *ar8236dev;

	// board specific cfg
	int irq;
	int phy_addr;
	int phy_flags;
};

#endif /* __ASSEMBLY__ */

#endif
