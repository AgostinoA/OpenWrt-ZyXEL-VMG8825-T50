/*------------------------------------------------------------------------------
 *
 *                                       Copyright (c) 2003
 *            CADENCE                    CADENCE DESIGN FOUNDRY
 *                                       All rights reserved.
 *
 *------------------------------------------------------------------------------
 *
 *   Filename       :   gem_AL.c
 *
 *   Author         :   Steven Ho, DICS, LDC
 *
 *   Date           :   9th Oct 2001
 *
 *   Limitations    :   Due to the use of bit-fields, only little endian
 *                      architectures is currently supported.  The header file
 *                      will need to be updated for other architectures.
 *
 *------------------------------------------------------------------------------
 *   Description    :   A Hardware Abstraction Layer for the Cadence Gigabit
 *                      Ethernet MAC (gem).
 *                      This comprises of a set of functions and macros to
 *                      provide a simple abstracted view to operating the MAC
 *                      enabling the MAC software development in the minimal
 *                      amount of time.
 *
 *------------------------------------------------------------------------------
 *   Revision Control
 *
 *------------------------------------------------------------------------------
 */

#include <common.h>
#include <config.h>
#include <asm/arch/hardware.h>
#include <asm/byteorder.h>
#include <malloc.h>
#include <net.h>
#include <command.h>

#if defined(CONFIG_COMCERTO_GEMAC)
#include "comcerto_gem.h"
/******************************************************************************/

/* Some functions to set/reset and get specific bits in the MAC registers
 * Note that all functions operate on a read-modify-write basis
 */

/******************************************************************************/
/*
 * Function to start transmission on the specified device.  The parameter to
 * this function is simply a pointer to the struct gemac_dev structure.
 * This function should be called after the relevant queues and data has been
 * set up, however it will check if the number of queue elements is zero first.
 * Note that this function will also enable tx even if it was previously not set
 *
 * Return value:
 *  0   :   OK
 *  -1  :   Transmit queue not valid.
 */
/******************************************************************************/
int gem_start_tx(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) |= __cpu_to_le32(GEM_TX_START | GEM_TX_EN);
	return 0;
}

/******************************************************************************/

/******************************************************************************/
/*
 * Halt transmission after current frame has completed.  This is accomplished
 * simply by writing to the GEM_TX_HALT bit in the network control register,
 * which should cause the MAC to complete its current frame then stop.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_stop_tx(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) |= __cpu_to_le32(GEM_TX_HALT);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Abort transmission immediately WITHOUT waiting for completion of any current
 * frame.
 * Note that after this operation, the transmit buffer descriptor will be reset
 * to point to the first buffer in the descriptor list!
 *
 * There is no return value.
 */
/******************************************************************************/
void gem_abort_tx(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) &= __cpu_to_le32(~(GEM_TX_START | GEM_TX_EN));
}

/******************************************************************************/

/******************************************************************************/
/*
 * Obtains status of transmission circuitry, whether it is transmitting or idle.
 *
 * Return value:
 *  0   :   Transmitter is idle.
 *  1   :   Transmitter active.
 */
/******************************************************************************/
int gem_transmitting(struct gemac_dev *gemac)
{
	return (__le32_to_cpu(*(volatile u32 *)(gemac->registers + GEM_TX_STATUS) & __cpu_to_le32(GEM_TX_GO)) == GEM_TX_GO);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Enable the receive circuitry.  This should be performed only after the
 * buffers and the descriptor queues have been set up, otherwise unpredictable
 * results may occur.
 *
 * Return value:
 *  0   :   OK
 *  -1  :   Receive queue not valid.
 */
/******************************************************************************/
int gem_enable_rx(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) |= __cpu_to_le32(GEM_RX_EN);
	return 0;
}

/******************************************************************************/

/******************************************************************************/
/*
 * Disable the receive circuitry.  This will stop reception of any frame
 * immediately, note that the descriptor pointer is not changed.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_disable_rx(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) &= __cpu_to_le32(~GEM_RX_EN);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Obtain the status of the receive circuitry, whether it is enabled.
 *
 * Return value:
 *  0   :   Receive circuitry disabled.
 *  -1  :   Receive circuits enabled.
 */
/******************************************************************************/
int gem_receive_on(struct gemac_dev *gemac)
{
	return (__le32_to_cpu(*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) & __cpu_to_le32(GEM_RX_EN)) == GEM_RX_EN);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Set the loopback mode of the MAC.  This can be either no loopback for normal
 * operation, local loopback through MAC internal loopback module or PHY
 * loopback for external loopback through a PHY.  This asserts the external loop
 * pin.
 * The function parameters are a pointer to the device and an enumerated type
 * specifying the type of loopback required.
 *
 * Note: if an invalid loopback mode is specified, loop back will be disabled.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_set_loop(struct gemac_dev *gemac,	/* Pointer to the device structure. */
		  MAC_LOOP gem_loop	/* Loopback mode. */
    ) {
	switch (gem_loop) {
	case LB_LOCAL:
		*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) &= __cpu_to_le32(~GEM_LB_PHY);
		*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) |= __cpu_to_le32(GEM_LB_MAC);
		break;
	case LB_EXT:
		*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) &= __cpu_to_le32(~GEM_LB_MAC);
		*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) |= __cpu_to_le32(GEM_LB_PHY);
		break;
	default:
		*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) &= __cpu_to_le32(~(GEM_LB_MAC | GEM_LB_PHY));
	}
}

/******************************************************************************/

/******************************************************************************/
/*
 * Get the loopback mode of the MAC.  This can be either no loopback for normal
 * operation, local loopback through MAC internal loopback module or PHY
 * loopback for external loopback through a PHY.  This asserts the external loop
 * pin.
 * The function parameters are a pointer to the device.
 *
 * Return value:
 *  LB_LOCAL    :   Local loop back active.
 *  LB_EXT      :   External loop back active.
 *  LB_NONE     :   Loop back disabled.
 *  -1          :   Unknown mode.
 */
/******************************************************************************/
MAC_LOOP gem_get_loop(struct gemac_dev *gemac)
{
	u32 lb_mode;

	lb_mode = *(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) & (GEM_LB_PHY | GEM_LB_MAC);

	switch (lb_mode) {
	case GEM_LB_MAC:
		return LB_LOCAL;
		break;
	case GEM_LB_PHY:
		return LB_EXT;
		break;
	case 0:
		return LB_NONE;
		break;
	default:
		return -1;
	}
}

/******************************************************************************/

/******************************************************************************/
/*
 * Activate the Management interface.  This is required to program the PHY
 * registers through the MDIO port.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_enable_MDIO(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) |= __cpu_to_le32(GEM_MDIO_EN);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Disable the Management interface.  In this state, the MDIO is placed in a
 * high impedance state and the MDC clock is driven low.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_disable_MDIO(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) &= __cpu_to_le32(~GEM_MDIO_EN);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Enable writing to the statistic registers.  This is for debug purposes only
 * and should not be active during normal operation.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_stats_wr_en(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) |= __cpu_to_le32(GEM_STATS_WR_EN);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Disable writing to the statistic registers.  Under normal operation this is
 * not necessary as the writing to statistics registers should be off by default
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_stats_wr_off(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) &= __cpu_to_le32(~GEM_STATS_WR_EN);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Increment all the statistic registers by 1.  This is for debug purposes only.
 * Note that the statistic registers are automatically cleared on read!
 *
 * No return value.
 */
/******************************************************************************/
void gem_stats_inc(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) |= __cpu_to_le32(GEM_STATS_INC);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Clear all the statistic registers.
 *
 * No return value.
 */
/******************************************************************************/
void gem_stats_clr(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) |= __cpu_to_le32(GEM_STATS_CLR);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Enable pause frame reception.  With this enabled, if a valid pause frame is
 * received, transmission will halt for the specified time after the current
 * frame has completed transmission.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_enable_pause_rx(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) |= __cpu_to_le32(GEM_RX_PAUSE_EN);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Disable pause frame reception.  Incoming pause frames are ignored.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_disable_pause_rx(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32(~GEM_RX_PAUSE_EN);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Enable copy of received pause frame.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_enable_pause_cpy(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32(~GEM_RX_NO_PAUSE);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Disable copy of received pause frame.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_disable_pause_cpy(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) |= __cpu_to_le32(GEM_RX_NO_PAUSE);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Send a pause frame with zero quantum.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_send_0q_pause(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) |= __cpu_to_le32(GEM_TX_0Q_PAUSE);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Send a normal pause frame.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_send_pause(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) |= __cpu_to_le32(GEM_TX_PAUSE);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Set transmit pause quantum.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_set_tx_pause_q(struct gemac_dev *gemac, u32 gem_pause)
{
	*(volatile u32 *)(gemac->registers + GEM_TX_PAUSE_QUANT) = __cpu_to_le32(gem_pause);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Read transmit pause quantum.
 *
 * Return values:
 * 0-65535: transmit pause quantum.
 */
/******************************************************************************/
u32 gem_get_tx_pause_q(struct gemac_dev *gemac)
{
	return (__le32_to_cpu(*(volatile u32 *)(gemac->registers + GEM_TX_PAUSE_QUANT)));
}

/******************************************************************************/

/******************************************************************************/
/*
 * Set retry test bit, this is used for debug purposes only to speed up testing.
 * This should not be enabled for normal operation.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_en_retry_test(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) |= __cpu_to_le32(GEM_RETRY_TEST);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Disable retry test bit.  For normal operation this bit should not be set.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_dis_retry_test(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32(~GEM_RETRY_TEST);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Enable external address match via the eam pin, which when active will copy
 * the current frame to memory.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_enable_eam(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) |= __cpu_to_le32(GEM_EAM_EN);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Disable external address match capability.  The MAC will ignore the status of
 * the eam pin.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_disable_eam(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32(~GEM_EAM_EN);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Enable storing of the receive frame check sequence into memory.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_enable_fcs_rx(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32(~GEM_RX_NO_FCS);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Disable storing of the receive frame check sequence into memory.  The last 4
 * bytes from the incoming frame will be checked for valid CRC, however this
 * will not be stored into memory.  The frame length will be updated
 * accordingly.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_disable_fcs_rx(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) |= __cpu_to_le32(GEM_RX_NO_FCS);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Enable reception of long frames up to 1536 bytes in length.
 * These are not standard IEEE 802.3 frames.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_enable_1536_rx(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) |= __cpu_to_le32(GEM_FRAME_1536);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Disable reception of frames greater than 1518 bytes in length.
 * This is normal operation mode for the MAC for compatibility with IEEE 802.3
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_disable_1536_rx(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32(~GEM_FRAME_1536);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Enable reception of unicast hashed frames.  The frame will be received when
 * the 6 bit hash function of the frame's destination address points a bit that
 * is set in the 64-bit hash register and is signalled as a unicast frame.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_enable_unicast(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) |= __cpu_to_le32(GEM_UNICAST_EN);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Disable reception of unicast hashed frames.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_disable_unicast(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32(~GEM_UNICAST_EN);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Enable reception of multicast hashed frames.  The frame will be received when
 * the 6 bit hash function of the frame's destination address points a bit that
 * is set in the 64-bit hash register and is signalled as a multicast frame.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_enable_multicast(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) |= __cpu_to_le32(GEM_MULTICAST_EN);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Disable reception of multicast hashed frames.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_disable_multicast(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32(~GEM_MULTICAST_EN);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Allow reception of broadcast frames (frames with address set to all 1's)
 * This is normal operating mode for the MAC.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_allow_broadcast(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32(~GEM_NO_BROADCAST);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Do not allow reception of broadcast frames, such frames will be ignored.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_no_broadcast(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) |= __cpu_to_le32(GEM_NO_BROADCAST);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Enable copy all frames.  In this mode, the MAC will copy all valid received
 * frames to memory regardless of the destination address.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_enable_copy_all(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) |= __cpu_to_le32(GEM_COPY_ALL);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Do not copy all frames.  Normal operating mode for the MAC, frames will only
 * be copied to memory if it matches one of the specific or hash addresses.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_disable_copy_all(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32(~GEM_COPY_ALL);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Set MAC into full duplex mode.  The crs and col signals will be ignored in
 * this mode.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_full_duplex(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->baseaddr + GEM_CFG) |= __cpu_to_le32(GEM_CONF_DUPLEX_GEM_FULL);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Set MAC into half duplex mode.  The crs and col signals are used to detect
 * collisions and perform deference where necessary.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_half_duplex(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->baseaddr + GEM_CFG) &= __cpu_to_le32(~GEM_CONF_DUPLEX_GEM_FULL);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Set the operating speed of the MAC, for 10 and 100Mb modes, this has no
 * effect on the MAC functionality, but simply asserts an external speed pin
 * accordingly.
 * For 1G modes, this will set the MAC into the appropriate operating mode by
 * switching to either the GMII or TBI interface depending on required mode.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_set_speed(struct gemac_dev *gemac, MAC_SPEED gem_speed)
{
	switch (gem_speed) {
	case SPEED_10M:
		*(volatile u32 *)(gemac->baseaddr + GEM_CFG) = (*(volatile u32 *)(gemac->baseaddr + GEM_CFG) & __cpu_to_le32(~GEM_CONF_SPEED_MASK)) | __cpu_to_le32(GEM_CONF_SPEED_SEL_GEM | GEM_CONF_SPEED_GEM_10M);
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32(~GEM_PCS_SEL);
		break;
	case SPEED_100M:
		*(volatile u32 *)(gemac->baseaddr + GEM_CFG) = (*(volatile u32 *)(gemac->baseaddr + GEM_CFG) & __cpu_to_le32(~GEM_CONF_SPEED_MASK)) | __cpu_to_le32(GEM_CONF_SPEED_SEL_GEM | GEM_CONF_SPEED_GEM_100M);
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32(~GEM_PCS_SEL);
		break;
	case SPEED_1000M:
		*(volatile u32 *)(gemac->baseaddr + GEM_CFG) = (*(volatile u32 *)(gemac->baseaddr + GEM_CFG) & __cpu_to_le32(~GEM_CONF_SPEED_MASK)) | __cpu_to_le32(GEM_CONF_SPEED_SEL_GEM | GEM_CONF_SPEED_GEM_1G);
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32(~GEM_PCS_SEL);
		break;
	case SPEED_1000M_PCS:
		*(volatile u32 *)(gemac->baseaddr + GEM_CFG) = (*(volatile u32 *)(gemac->baseaddr + GEM_CFG) & __cpu_to_le32(~GEM_CONF_SPEED_MASK)) | __cpu_to_le32(GEM_CONF_SPEED_SEL_GEM | GEM_CONF_SPEED_GEM_1G);
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) |= __cpu_to_le32(GEM_PCS_SEL);
		break;
	default:
		*(volatile u32 *)(gemac->baseaddr + GEM_CFG) = (*(volatile u32 *)(gemac->baseaddr + GEM_CFG) & __cpu_to_le32(~GEM_CONF_SPEED_MASK)) | __cpu_to_le32(GEM_CONF_SPEED_SEL_GEM | GEM_CONF_SPEED_GEM_100M);
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32(~GEM_PCS_SEL);
	}
}

/******************************************************************************/

/******************************************************************************/
/*
 * Get the operating speed of the MAC, currently this has no functional effect
 * on the MAC.
 *
 * This function returns an enumerated value cast into an int.  This is for
 * backward compatibility with the macb driver.
 *
 * Return value:
 *  SPEED_10M   :   MAC in 10Mb/s mode.
 *  SPEED_100M  :   MAC in 100Mb/s mode.
 *  SPEED_1000M :   MAC in 1G mode with GMII interface.
 *  SPEED_1000M_PCS :   MAC in 1G mode with PCS interface.
 */
/******************************************************************************/
MAC_SPEED gem_get_speed(struct gemac_dev *gemac)
{

	if (*(volatile u32 *)(gemac->baseaddr + GEM_CFG) & __cpu_to_le32(GEM_CONF_SPEED_SEL_GEM)) {
		if (*(volatile u32 *)(gemac->baseaddr + GEM_CFG) & __cpu_to_le32(GEM_CONF_SPEED_GEM_1G)) {
			if (*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) & __cpu_to_le32(GEM_PCS_SEL))
				return (SPEED_1000M_PCS);
			else
				return (SPEED_1000M);
		} else {
			if (*(volatile u32 *)(gemac->baseaddr + GEM_CFG) & __cpu_to_le32(GEM_CONF_SPEED_GEM_100M))
				return (SPEED_100M);
			else
				return (SPEED_10M);
		}
	} else {
		if (*(volatile u32 *)(gemac->baseaddr + GEM_CFG) & __cpu_to_le32(GEM_CONF_SPEED_PHY_1G)) {
			if (*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) & __cpu_to_le32(GEM_PCS_SEL))
				return (SPEED_1000M_PCS);
			else
				return (SPEED_1000M);
		} else {
			if (*(volatile u32 *)(gemac->baseaddr + GEM_CFG) & __cpu_to_le32(GEM_CONF_SPEED_PHY_100M))
				return (SPEED_100M);
			else
				return (SPEED_10M);
		}
	}
}

/******************************************************************************/
#if defined(CONFIG_COMCERTO_100)
/******************************************************************************/
/*
 * Set AMBA AHB bus width.
 * AMBA_AHB_32:
 * AMBA_AHB_64:
 * AMBA_AHB_128:
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_set_ahb_width(struct gemac_dev *gemac, MAC_AHB_WIDTH gem_buswidth)
{
	switch (gem_buswidth) {
	case AMBA_AHB_128:
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) |= __cpu_to_le32(GEM_AHB_WIDTH1);
		break;
	case AMBA_AHB_64:
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32(~GEM_AHB_WIDTH1);
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) |= __cpu_to_le32(GEM_AHB_WIDTH0);
		break;
	case AMBA_AHB_32:
	default:
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32((~GEM_AHB_WIDTH1) & (~GEM_AHB_WIDTH0));
	}
}

/******************************************************************************/

/******************************************************************************/
/*
 * Get AMBA AHB bus width. 
 * It returns one of the following values:
 * AMBA_AHB_32, AMBA_AHB_64, AMBA_AHB_128,
 */
/******************************************************************************/
MAC_AHB_WIDTH gem_get_ahb_width(struct gemac_dev *gemac)
{
	if (*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) & __cpu_to_le32(GEM_AHB_WIDTH1)) {
		return AMBA_AHB_128;
	} else {
		if (*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) & __cpu_to_le32(GEM_AHB_WIDTH0)) {
			return AMBA_AHB_64;
		} else {
			return AMBA_AHB_32;
		}
	}
}

/******************************************************************************/
#endif
/******************************************************************************/
/*
 * Set MDC clock division.
 * MDC_DIV_8:
 * MDC_DIV_16:
 * MDC_DIV_32:
 * MDC_DIV_48:
 * MDC_DIV_64:
 * MDC_DIV_96:
 * MDC_DIV_128:
 * MDC_DIV_224:
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_set_mdc_div(struct gemac_dev *gemac, MAC_MDC_DIV gem_mdcdiv)
{
	switch (gem_mdcdiv) {
	case MDC_DIV_8:
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32((~GEM_MDC_DIV2) & (~GEM_MDC_DIV1) & (~GEM_MDC_DIV0));
		break;
	case MDC_DIV_16:
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32((~GEM_MDC_DIV2) & (~GEM_MDC_DIV1));
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) |= __cpu_to_le32(GEM_MDC_DIV0);
		break;
	case MDC_DIV_32:
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32((~GEM_MDC_DIV2) & (~GEM_MDC_DIV0));
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) |= __cpu_to_le32(GEM_MDC_DIV1);
		break;
	case MDC_DIV_48:
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) |= __cpu_to_le32(GEM_MDC_DIV1 | GEM_MDC_DIV0);
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32(~GEM_MDC_DIV2);
		break;
	case MDC_DIV_64:
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32((~GEM_MDC_DIV1) & (~GEM_MDC_DIV0));
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) |= __cpu_to_le32(GEM_MDC_DIV2);
		break;
	case MDC_DIV_96:
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) |= __cpu_to_le32(GEM_MDC_DIV2 | GEM_MDC_DIV0);
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32(~GEM_MDC_DIV1);
		break;
	case MDC_DIV_128:
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) |= __cpu_to_le32(GEM_MDC_DIV2 | GEM_MDC_DIV1);
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32(~GEM_MDC_DIV0);
		break;
	case MDC_DIV_224:
		*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) |= __cpu_to_le32(GEM_MDC_DIV2 | GEM_MDC_DIV1 | GEM_MDC_DIV0);
		break;
	}
}

/******************************************************************************/

/******************************************************************************/
/*
 * Get MDC clock division.
 * It returns one of this values:
 * MDC_DIV_8, MDC_DIV_16, MDC_DIV_32, MDC_DIV_48, MDC_DIV_64, MDC_DIV_96,
 * MDC_DIV_128, MDC_DIV_224.
 */
/******************************************************************************/
MAC_MDC_DIV gem_get_mdc_div(struct gemac_dev *gemac)
{
	if (*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) & __cpu_to_le32(GEM_MDC_DIV2)) {
		if (*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) & __cpu_to_le32(GEM_MDC_DIV1)) {
			if (*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) & __cpu_to_le32(GEM_MDC_DIV0)) {
				return MDC_DIV_224;
			} else {
				return MDC_DIV_128;
			}
		} else {
			if (*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) & __cpu_to_le32(GEM_MDC_DIV0)) {
				return MDC_DIV_96;
			} else {
				return MDC_DIV_64;
			}
		}
	} else {
		if (*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) & __cpu_to_le32(GEM_MDC_DIV1)) {
			if (*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) & __cpu_to_le32(GEM_MDC_DIV0)) {
				return MDC_DIV_48;
			} else {
				return MDC_DIV_32;
			}
		} else {
			if (*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) & __cpu_to_le32(GEM_MDC_DIV0)) {
				return MDC_DIV_16;
			} else {
				return MDC_DIV_8;
			}
		}
	}
}

/******************************************************************************/

/******************************************************************************/
/*
 * Enable to read snapshot values of statistic registers.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_enable_rd_snap(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) |= __cpu_to_le32(GEM_READ_SNAP);
}

/******************************************************************************/
/*
 * Disable to read snapshot values of statistic registers.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_disable_rd_snap(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) &= __cpu_to_le32(~GEM_READ_SNAP);
}

/******************************************************************************/
/*
 * Take snapshot of statistic registers. Writing a one will record the current 
 * value of all statistics registers in the snapshot registers and clear the 
 * statistics registers.
 *
 * There is no return value for this function.
 */
/******************************************************************************/
void gem_take_snap(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) |= __cpu_to_le32(GEM_TAKE_SNAP);
}

/******************************************************************************/
/*
 * Get the current link status as returned by the PHY
 *
 * Return value:
 *  0   :   Link is down.
 *  1   :   Link active.
 */
/******************************************************************************/
int gem_link_status(struct gemac_dev *gemac)
{
	return (__le32_to_cpu(*(volatile u32 *)(gemac->registers + GEM_NET_STATUS) & __cpu_to_le32(GEM_LINK_STATUS)) == GEM_LINK_STATUS);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Check if the PHY management logic is idle, i.e. completed management
 * operation.
 *
 * Return value:
 *  0   :   PHY management not-idle.
 *  1   :   PHY management completed.
 */
/******************************************************************************/
int gem_phy_man_idle(struct gemac_dev *gemac)
{
	return (__le32_to_cpu(*(volatile u32 *)(gemac->phyregisters + GEM_NET_STATUS) & __cpu_to_le32(GEM_PHY_IDLE)) == GEM_PHY_IDLE);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Get the value of the transmit status register.
 * The return value is an unsigned 32-bit integer containing the contents of the
 * register.  This should be masked appropriately to obtain the relevant status.
 *
 * Return value:
 * Returns current value of transmit status register.
 */
/******************************************************************************/
u32 gem_get_tx_stat(struct gemac_dev *gemac)
{
	return (__le32_to_cpu(*(volatile u32 *)(gemac->registers + GEM_TX_STATUS)));
}

/******************************************************************************/

/******************************************************************************/
/*
 * Reset the specified bits of the transmit status register.
 *
 * There is no return value.
 */
/******************************************************************************/
void gem_reset_tx_stat(struct gemac_dev *gemac,	/* Pointer to device structure. */
		       u32 rst_status	/* Status to reset. */
    ) {
	*(volatile u32 *)(gemac->registers + GEM_TX_STATUS) |= __cpu_to_le32(rst_status);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Get the value of the receive status register.
 * The return value is an unsigned 32-bit integer containing the contents of the
 * register.  This should be masked appropriately to obtain the relevant status.
 *
 * Returns current receive status.
 */
/******************************************************************************/
u32 gem_get_rx_stat(struct gemac_dev *gemac)
{
	return (__le32_to_cpu(*(volatile u32 *)(gemac->registers + GEM_RX_STATUS)));
}

/******************************************************************************/

/******************************************************************************/
/*
 * Reset the specified bits of the receive status register.
 *
 * There is no return value.
 */
/******************************************************************************/
void gem_reset_rx_stat(struct gemac_dev *gemac,	/* Pointer to device structure. */
		       u32 rst_status	/* Status to reset. */
    ) {
	*(volatile u32 *)(gemac->registers + GEM_RX_STATUS) |= __cpu_to_le32(rst_status);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Enable jumbo frames to be accepted.
 *
 * There is no return value.
 */
/******************************************************************************/
void gem_enable_rx_jmb(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) |= __cpu_to_le32(GEM_RX_JUMBO);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Disable jumbo frames to be accepted.
 *
 * There is no return value.
 */
/******************************************************************************/
void gem_disable_rx_jmb(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32(~GEM_RX_JUMBO);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Enable only VLAN frames to be accepted, all other frames will be discarded.
 *
 * There is no return value.
 */
/******************************************************************************/
void gem_enable_vlan_only(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) |= __cpu_to_le32(GEM_VLAN_ONLY);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Disable VLAN frame only mode. All frames will be accepted.
 *
 * There is no return value.
 */
/******************************************************************************/
void gem_disable_vlan_only(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32(~GEM_VLAN_ONLY);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Read the interrupt status register.
 * This returns an unsigned 32-bit integer with the current interrupt status,
 * this should be masked appropriately to get the required status.
 * Note that the interrupt status register is automatically reset on read, so
 * the returned value should be stored if further processing required.
 *
 * Returns the current interrupt status.
 */
/******************************************************************************/
u32 gem_get_irq_stat(struct gemac_dev *gemac)
{
	return (__le32_to_cpu(*(volatile u32 *)(gemac->registers + GEM_IRQ_STATUS)));
}

/******************************************************************************/

/******************************************************************************/
/*
 * Set specified bits in the interrupt status register.
 * This can be used for debug purposes to manually activate an interrupt.
 *
 * There is no return value.
 */
/******************************************************************************/
void gem_set_irq_stat(struct gemac_dev *gemac, u32 irq_status)
{
	*(volatile u32 *)(gemac->registers + GEM_IRQ_STATUS) |= __cpu_to_le32(irq_status);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Enable specified interrupts.
 * The specified interrupt bits are enabled by unmasking them.
 * Note that this appends to the existing interrupt enable list.
 *
 * There is no return value.
 */
/******************************************************************************/
void gem_enable_irq(struct gemac_dev *gemac, u32 irq_en)
{
	*(volatile u32 *)(gemac->registers + GEM_IRQ_ENABLE) |= __cpu_to_le32(irq_en);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Disable specified interrupts.
 * The specified interrupts are masked out so that they do not generate an
 * interrupt.
 * Note that this appends to the existing interrupt mask list.
 *
 * There is no return value.
 */
/******************************************************************************/
void gem_mask_irq(struct gemac_dev *gemac, u32 irq_mask)
{
	*(volatile u32 *)(gemac->registers + GEM_IRQ_DISABLE) |= __cpu_to_le32(irq_mask);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Obtain the current interrupt mask value.
 * The return value indicates which interrupts are currently masked out i.e. do
 * not generate an interrupt.
 *
 * Returns the interrupt mask status.
 */
/******************************************************************************/
u32 gem_get_irq_mask(struct gemac_dev *gemac)
{
	return (__le32_to_cpu(*(volatile u32 *)(gemac->registers + GEM_IRQ_MASK)));
}

/******************************************************************************/

/******************************************************************************/
/*
 * Write to the PHY management registers.
 * This function simply sets off the PHY management operation, completion will
 * be indicated by an interrupt.
 * The input parameters are the PHY address, register address, and the 16-bit
 * data to be written.
 * Note that the MDIO enable register must be on.
 *
 * Return value:
 *  0   :   OK
 *  -1  :   Invalid input range.
 */
/******************************************************************************/
int gem_phy_man_wr(struct gemac_dev *gemac, u8 phy_addr, u8 reg_addr, u32 data) {
	u32 write_data;

	if ((phy_addr > 0x1F) || (reg_addr > 0x1F) || (data > 0xFFFF)) {
		return -1;
	} else {
		write_data = 0x50020000;
		write_data |= ((phy_addr << 23) | (reg_addr << 18) | data);
		*(volatile u32 *)(gemac->phyregisters + GEM_PHY_MAN) = __cpu_to_le32(write_data);
		return 0;
	}
}

/******************************************************************************/

/******************************************************************************/
/*
 * Perform PHY management register read operation.
 * This function simply sets off the PHY management operation, completion will
 * be indicated by an interrupt.
 * The input parameters are the PHY address and the register address to be read
 *
 * Return value:
 *  0   :   OK
 *  -1  :   Invalid input range.
 */
/******************************************************************************/
int gem_phy_man_rd(struct gemac_dev *gemac, u8 phy_addr, u8 reg_addr) {
	u32 write_data;

	if ((phy_addr > 0x1F) || (reg_addr > 0x1F)) {
		return -1;
	} else {
		write_data = 0x60020000;
		write_data |= ((phy_addr << 23) | (reg_addr << 18));
		*(volatile u32 *)(gemac->phyregisters + GEM_PHY_MAN) = __cpu_to_le32(write_data);
		return 0;
	}
}

/******************************************************************************/

/******************************************************************************/
/*
 * Read the data section of the PHY management register.  After a read operation
 * the data from the PHY will be stored here.
 *
 * Return value is the lower 16-bits of the PHY management register.
 */
/******************************************************************************/
u32 gem_phy_man_data(struct gemac_dev *gemac)
{
	return (__le32_to_cpu(*(volatile u32 *)(gemac->phyregisters + GEM_PHY_MAN) & __cpu_to_le32(0xFFFF)));
}

/******************************************************************************/

/******************************************************************************/
/*
 * Read the pause time register.
 *
 * Returns the current value in the pause time register which will
 * decrement when the MAC has gone into pause mode.
 */
/******************************************************************************/
u32 gem_pause_time(struct gemac_dev *gemac)
{
	return (__le32_to_cpu(*(volatile u32 *)(gemac->registers + GEM_RX_PAUSE_TIME)));
}

/******************************************************************************/

/******************************************************************************/
/*
 * Set the id-check registers of the MAC.
 * These registers are used to check the type-id field of the incoming frames, 
 * if matched, the appropriate status bit will be set in word 1 of the receive
 * descriptor for that frame.
 * The input parameter is truncated to 16-bits.
 *
 * There is no return value.
 */
/******************************************************************************/
void gem_set_id_check1(struct gemac_dev *gemac, u32 id_check) {
	*(volatile u32 *)(gemac->registers + GEM_ID_CHECK1) = __cpu_to_le32(id_check & 0xFFFF);
}

void gem_set_id_check2(struct gemac_dev *gemac, u32 id_check) {
	*(volatile u32 *)(gemac->registers + GEM_ID_CHECK2) = __cpu_to_le32(id_check & 0xFFFF);
}

void gem_set_id_check3(struct gemac_dev *gemac, u32 id_check) {
	*(volatile u32 *)(gemac->registers + GEM_ID_CHECK3) = __cpu_to_le32(id_check & 0xFFFF);
}

void gem_set_id_check4(struct gemac_dev *gemac, u32 id_check) {
	*(volatile u32 *)(gemac->registers + GEM_ID_CHECK4) = __cpu_to_le32(id_check & 0xFFFF);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Get the value of the id-check registers in the MAC.
 *
 * Return value:
 *  Value of ID check register.
 */
/******************************************************************************/
u32 gem_get_id_check1(struct gemac_dev *gemac)
{
	return (__le32_to_cpu(*(volatile u32 *)(gemac->registers + GEM_ID_CHECK1)));
}

u32 gem_get_id_check2(struct gemac_dev *gemac)
{
	return (__le32_to_cpu(*(volatile u32 *)(gemac->registers + GEM_ID_CHECK2)));
}

u32 gem_get_id_check3(struct gemac_dev *gemac)
{
	return (__le32_to_cpu(*(volatile u32 *)(gemac->registers + GEM_ID_CHECK3)));
}

u32 gem_get_id_check4(struct gemac_dev *gemac)
{
	return (__le32_to_cpu(*(volatile u32 *)(gemac->registers + GEM_ID_CHECK4)));
}

/******************************************************************************/

/******************************************************************************/
/*
 * Set the hash register of the MAC.
 * This register is used for matching unicast and multicast frames.
 * The parameter of this function should be a pointer to type MAC_ADDR as
 * defined in the header file.
 *
 * There is no return value.
 */
/******************************************************************************/
void gem_set_hash(struct gemac_dev *gemac, MAC_ADDR *hash_addr) {
	*(volatile u32 *)(gemac->registers + GEM_HASH_BOT) = hash_addr->bottom;
	*(volatile u32 *)(gemac->registers + GEM_HASH_TOP) = hash_addr->top;
}

/******************************************************************************/

/******************************************************************************/
/*
 * Get the current value of the hash registers of the MAC.
 *
 * This function returns a value of type MAC_ADDR
 */
/******************************************************************************/
MAC_ADDR gem_get_hash(struct gemac_dev *gemac)
{
	MAC_ADDR addr;

	addr.bottom = *(volatile u32 *)(gemac->registers + GEM_HASH_BOT);
	addr.top = *(volatile u32 *)(gemac->registers + GEM_HASH_TOP);

	return addr;
}

/******************************************************************************/

/******************************************************************************/
/*
 * Setup all the specific address registers for the MAC.
 * These registers are matched against incoming frames to determine whether the
 * frame should be copied to memory.
 * The input parameter to this function should be a pointer to type SPEC_ADDR
 * as defined in the header file.
 *
 * There is no return value.
 */
/******************************************************************************/
void gem_set_address(struct gemac_dev *gemac, SPEC_ADDR *spec_addr)
{
	*(volatile u32 *)(gemac->registers + GEM_LADDR1_BOT) = spec_addr->one.bottom;
	*(volatile u32 *)(gemac->registers + GEM_LADDR1_TOP) = spec_addr->one.top;
	*(volatile u32 *)(gemac->registers + GEM_LADDR2_BOT) = spec_addr->two.bottom;
	*(volatile u32 *)(gemac->registers + GEM_LADDR2_TOP) = spec_addr->two.top;
	*(volatile u32 *)(gemac->registers + GEM_LADDR3_BOT) = spec_addr->three.bottom;
	*(volatile u32 *)(gemac->registers + GEM_LADDR3_TOP) = spec_addr->three.top;
	*(volatile u32 *)(gemac->registers + GEM_LADDR4_BOT) = spec_addr->four.bottom;
	*(volatile u32 *)(gemac->registers + GEM_LADDR4_TOP) = spec_addr->four.top;
}

/******************************************************************************/

/******************************************************************************/
/*
 * Get the current set of specific match addresses for the MAC.
 * Note that a pointer is not returned as this would give direct access to the
 * MAC address space which may cause unpredictable behaviour if wrongly used.
 *
 * Return type is of type SPEC_ADDR as defined in the header file.
 */
/******************************************************************************/
SPEC_ADDR gem_get_address(struct gemac_dev *gemac)
{
        SPEC_ADDR spec_addr;

	spec_addr.one.bottom = *(volatile u32 *)(gemac->registers + GEM_LADDR1_BOT);
	spec_addr.one.top = *(volatile u32 *)(gemac->registers + GEM_LADDR1_TOP);
	spec_addr.two.bottom = *(volatile u32 *)(gemac->registers + GEM_LADDR2_BOT);
	spec_addr.two.top = *(volatile u32 *)(gemac->registers + GEM_LADDR2_TOP);
	spec_addr.three.bottom = *(volatile u32 *)(gemac->registers + GEM_LADDR3_BOT);
	spec_addr.three.top = *(volatile u32 *)(gemac->registers + GEM_LADDR3_TOP);
	spec_addr.four.bottom = *(volatile u32 *)(gemac->registers + GEM_LADDR4_BOT);
	spec_addr.four.top = *(volatile u32 *)(gemac->registers + GEM_LADDR4_TOP);

        return spec_addr;
}

/******************************************************************************/

/******************************************************************************/
/*
 * Set specific local addresses of the MAC.
 * Rather than setting up all four specific addresses, this function sets them
 * up individually.  The input parameter should be a pointer to type MAC_ADDR.
 *
 * There are no return values.
 */
/******************************************************************************/
void gem_set_laddr1(struct gemac_dev *gemac, MAC_ADDR *address)
{
	*(volatile u32 *)(gemac->registers + GEM_LADDR1_BOT) = address->bottom;
	*(volatile u32 *)(gemac->registers + GEM_LADDR1_TOP) = address->top;
}

void gem_set_laddr2(struct gemac_dev *gemac, MAC_ADDR *address)
{
	*(volatile u32 *)(gemac->registers + GEM_LADDR2_BOT) = address->bottom;
	*(volatile u32 *)(gemac->registers + GEM_LADDR2_TOP) = address->top;
}

void gem_set_laddr3(struct gemac_dev *gemac, MAC_ADDR *address)
{
	*(volatile u32 *)(gemac->registers + GEM_LADDR3_BOT) = address->bottom;
	*(volatile u32 *)(gemac->registers + GEM_LADDR3_TOP) = address->top;
}

void gem_set_laddr4(struct gemac_dev *gemac, MAC_ADDR *address)
{
	*(volatile u32 *)(gemac->registers + GEM_LADDR4_BOT) = address->bottom;
	*(volatile u32 *)(gemac->registers + GEM_LADDR4_TOP) = address->top;
}

/******************************************************************************/

/******************************************************************************/
/*
 * Get specific local addresses of the MAC.
 * This allows returning of a single specific address stored in the MAC.
 *
 * Return value if of type MAC_ADDR as defined in the header file.
 */
/******************************************************************************/
MAC_ADDR gem_get_laddr1(struct gemac_dev *gemac)
{
	MAC_ADDR addr;

	addr.bottom = *(volatile u32 *)(gemac->registers + GEM_LADDR1_BOT);
	addr.top = *(volatile u32 *)(gemac->registers + GEM_LADDR1_TOP);

	return addr;
}

MAC_ADDR gem_get_laddr2(struct gemac_dev *gemac)
{
	MAC_ADDR addr;

	addr.bottom = *(volatile u32 *)(gemac->registers + GEM_LADDR2_BOT);
	addr.top = *(volatile u32 *)(gemac->registers + GEM_LADDR2_TOP);

	return addr;
}

MAC_ADDR gem_get_laddr3(struct gemac_dev *gemac)
{
	MAC_ADDR addr;

	addr.bottom = *(volatile u32 *)(gemac->registers + GEM_LADDR3_BOT);
	addr.top = *(volatile u32 *)(gemac->registers + GEM_LADDR3_TOP);

	return addr;
}

MAC_ADDR gem_get_laddr4(struct gemac_dev *gemac)
{
	MAC_ADDR addr;

	addr.bottom = *(volatile u32 *)(gemac->registers + GEM_LADDR4_BOT);
	addr.top = *(volatile u32 *)(gemac->registers + GEM_LADDR4_TOP);

	return addr;
}

/******************************************************************************/

/******************************************************************************/
/*
 * Obtain the statistics registers structure.
 * type GEM_STATS as defined in the header file.
 * Note that this operation is relatively slow as it is copying all the
 * statistics register values rather than providing a pointer reference to them.
 * Note also that the statistics registers will all be automatically cleared
 * after this operation.
 *
 * Returns the entire statistics register block for the MAC in a structure of
 * type GEM_STATS
 */
/******************************************************************************/
GEM_STATS gem_get_stats(struct gemac_dev *gemac)
{
	return (*(GEM_STATS *)(gemac->registers + GEM_OCT_TX_BOT));
}

/******************************************************************************/

/******************************************************************************/
/*
 * Set the values of the statistics registers.
 * This is for debug only and allows reading and writing to the statistic
 * registers to verify functionality.
 *
 * There is no return value.
 */
/******************************************************************************/
void gem_set_stats(struct gemac_dev *gemac, GEM_STATS *stats)
{
//	gemac->registers->stats = *stats;
}

/******************************************************************************/

/******************************************************************************/
/*
 * Write to a specific MAC memory address.  The defines in the header file
 * should be used for this.
 * Note: care should be taken when using this function so as not to pass null
 * pointers or write to read only registers etc.
 *
 * Return value:
 *  0   :   OK
 *  -1  :   Invalid input range.
 */
/******************************************************************************/
int gem_register_wr(struct gemac_dev *gemac, u32 reg_addr, u32 data)
{
	if (reg_addr > GEM_REG_TOP) {
		return -1;
	} else {
		*(volatile u32 *)(gemac->registers + reg_addr) = __cpu_to_le32(data);
		return 0;
	}
}

/******************************************************************************/

/******************************************************************************/
/*
 * Read from a specific MAC memory address. The defines in the header file
 * should be used for this.
 * Note that the range of the address requested is not checked.
 *
 * Returns register contents.
 */
/******************************************************************************/
u32 gem_register_rd(struct gemac_dev *gemac, u32 reg_addr)
{
	return (__le32_to_cpu(*(volatile u32 *)(gemac->registers + reg_addr)));
}

/******************************************************************************/
/*
 * Reset the MAC device to its default value and load up the MAC address stored
 * in the header file into specific address 1.  The MAC will be held in
 * quiescent state.
 * This function should be called to initialise and check the device prior to
 * setting up the buffer queues and enabling the MAC.  If it is called mid way
 * through operation, the MAC is reset to default value and any pending frames
 * will be lost.
 * Note that the values in the struct gemac_dev software structure are not reset, only
 * the MAC registers are reset.  This is to allow, if necessary to recover the
 * buffers and reload them into the MAC, however prior to doing this, they
 * should be cleared first.
 *
 * Return value:
 *  0   :   OK
 *  -1  :   Error in write/read check on initialisation.
 */
/******************************************************************************/
int gem_reset(struct gemac_dev *gemac)
{
	MAC_ADDR zero_address = { 0x00000000, 0x00000000 };
	MAC_ADDR enet_address = zero_address;
	int stats_length;
	int loop_i;

	stats_length = sizeof(GEM_STATS) / 4;

	/* Write to registers and set default values. */
	*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) = __cpu_to_le32(GEM_STATS_CLR | GEM_MDIO_ENABLED);
#if defined(CONFIG_COMCERTO_100)
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) = __cpu_to_le32(GEM_DEF_DUPLEX);
#else
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) = __cpu_to_le32(0);
#endif
	gem_set_loop(gemac, GEM_DEF_LOOP);
	gem_set_mdc_div(gemac, GEM_DEF_PCLK_DIV);
	gem_set_speed(gemac, GEM_DEF_SPEED);
#if defined(CONFIG_COMCERTO_100)
	gem_set_ahb_width(gemac, GEM_DEF_AHB_WIDTH);
#endif

	*(volatile u32 *)(gemac->registers + GEM_TX_STATUS) = __cpu_to_le32(0xFFFFFFFF);
	*(volatile u32 *)(gemac->registers + GEM_RX_QPTR) = __cpu_to_le32(0x00000000);
#if defined(CONFIG_COMCERTO_100)
	*(volatile u32 *)(gemac->registers + GEM_TX_QPTR) = __cpu_to_le32(0x00000000);
#endif
	*(volatile u32 *)(gemac->registers + GEM_RX_STATUS) = __cpu_to_le32(0xFFFFFFFF);
	*(volatile u32 *)(gemac->registers + GEM_IRQ_DISABLE) = __cpu_to_le32(0xFFFFFFFF);
	*(volatile u32 *)(gemac->registers + GEM_IRQ_STATUS) = __cpu_to_le32(0x00000000);

	gem_set_hash(gemac, &zero_address);
	gem_set_laddr1(gemac, &enet_address);
	gem_set_laddr2(gemac, &zero_address);
	gem_set_laddr3(gemac, &zero_address);
	gem_set_laddr4(gemac, &zero_address);

	*(volatile u32 *)(gemac->registers + GEM_ID_CHECK1) = __cpu_to_le32(0x00000000);
	*(volatile u32 *)(gemac->registers + GEM_ID_CHECK2) = __cpu_to_le32(0x00000000);
	*(volatile u32 *)(gemac->registers + GEM_ID_CHECK3) = __cpu_to_le32(0x00000000);
	*(volatile u32 *)(gemac->registers + GEM_ID_CHECK4) = __cpu_to_le32(0x00000000);

	/* Now read back values and return if not correct. */
	if ((*(volatile u32 *)(gemac->registers + GEM_ID_CHECK1) != __cpu_to_le32(0x00000000)) ||
	    (*(volatile u32 *)(gemac->registers + GEM_ID_CHECK2) != __cpu_to_le32(0x00000000)) ||
	    (*(volatile u32 *)(gemac->registers + GEM_ID_CHECK3) != __cpu_to_le32(0x00000000)) ||
	    (*(volatile u32 *)(gemac->registers + GEM_ID_CHECK4) != __cpu_to_le32(0x00000000)) ||
	    (*(volatile u32 *)(gemac->registers + GEM_LADDR4_BOT) != zero_address.bottom) ||
	    (*(volatile u32 *)(gemac->registers + GEM_LADDR4_TOP) != zero_address.top) ||
	    (*(volatile u32 *)(gemac->registers + GEM_LADDR3_BOT) != zero_address.bottom) ||
	    (*(volatile u32 *)(gemac->registers + GEM_LADDR3_TOP) != zero_address.top) ||
	    (*(volatile u32 *)(gemac->registers + GEM_LADDR2_BOT) != zero_address.bottom) ||
	    (*(volatile u32 *)(gemac->registers + GEM_LADDR2_TOP) != zero_address.top) ||
	    (*(volatile u32 *)(gemac->registers + GEM_LADDR1_BOT) != enet_address.bottom) ||
	    (*(volatile u32 *)(gemac->registers + GEM_LADDR1_TOP) != enet_address.top) ||
	    (*(volatile u32 *)(gemac->registers + GEM_HASH_BOT) != zero_address.bottom) ||
	    (*(volatile u32 *)(gemac->registers + GEM_HASH_TOP) != zero_address.top) ||
	    (*(volatile u32 *)(gemac->registers + GEM_IRQ_STATUS) != __cpu_to_le32(0x00000000)) ||
	    (*(volatile u32 *)(gemac->registers + GEM_IRQ_MASK) != __cpu_to_le32(0x0003FFFF)) ||
	    (*(volatile u32 *)(gemac->registers + GEM_RX_STATUS) != __cpu_to_le32(0x00000000)) ||
#if defined(CONFIG_COMCERTO_100)
	    (*(volatile u32 *)(gemac->registers + GEM_TX_QPTR) != __cpu_to_le32(0x00000000)) ||
#endif
	    (*(volatile u32 *)(gemac->registers + GEM_RX_QPTR) != __cpu_to_le32(0x00000000)) ||
	    (*(volatile u32 *)(gemac->registers + GEM_TX_STATUS) != __cpu_to_le32(0x00000000))
	    ) {
		return -1;
	} else if ((__le32_to_cpu((*(volatile u32 *)(gemac->registers + GEM_NET_CONTROL) & __cpu_to_le32(GEM_MDIO_EN))) != (0x00000000 | GEM_MDIO_ENABLED)) ||
		   (gem_get_loop(gemac) != GEM_DEF_LOOP) ||
		   //           (gem_get_speed(gemac) != GEM_DEF_SPEED)  ||
		   (gem_get_mdc_div(gemac) != GEM_DEF_PCLK_DIV)
	    ) {
		return -1;
	} else {
		for (loop_i = 0; loop_i < stats_length; loop_i++) {
			if (__le32_to_cpu(*(volatile u32 *)(gemac->registers + GEM_OCT_TX_BOT + 4 * loop_i)) != 0x00000000) {
				return -1;
			}
		}

		return 0;
	}
}

/******************************************************************************/

/******************************************************************************/
/*
 * Enable length field checking feature.
 * The length field check feature automatically discards frames that has a frame
 * length smaller than that reported in the length field of the header.
 *
 * Note that in accordance with the IEEE spec, frames that are longer than that
 * reported in length field is still accepted as a valid frame.
 *
 * This function has no return value.
 */
/******************************************************************************/
void gem_enable_len_check(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) |= __cpu_to_le32(GEM_RX_LEN_CHK);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Disable length field checking feature.
 *
 * This function has no return value.
 */
/******************************************************************************/
void gem_disable_len_check(struct gemac_dev *gemac)
{
	*(volatile u32 *)(gemac->registers + GEM_NET_CONFIG) &= __cpu_to_le32(~GEM_RX_LEN_CHK);
}

/******************************************************************************/

/******************************************************************************/
/*
 * Convert standard byte style ethernet address to format compatible with MAC.
 *
 * Input    :   Pointer to beginning of 6 byte address.
 *              Pointer to MAC_ADDR structure.
 * Return values:
 *  0   :   OK
 *  -1  :   Invalid inputs.
 */
/******************************************************************************/
int gem_enet_addr_byte_mac(u8 *enet_byte_addr, MAC_ADDR *enet_addr)
{
	if ((enet_byte_addr == NULL) || (enet_addr == NULL)) {
		return -1;
	}
    else
    {
#if defined(BE8_MODE)
        enet_addr->bottom = ((enet_byte_addr[0] << 24) |
                             (enet_byte_addr[1] << 16) |
                             (enet_byte_addr[2] << 8) |
                             enet_byte_addr[3]);
        enet_addr->top = ((enet_byte_addr[4] << 24) |
                          (enet_byte_addr[5] << 16));
#else
        enet_addr->bottom = enet_byte_addr[0] |
                            (enet_byte_addr[1] << 8) |
                            (enet_byte_addr[2] << 16) |
                            (enet_byte_addr[3] << 24);
        enet_addr->top = enet_byte_addr[4] |
                         (enet_byte_addr[5] << 8);
#endif
        return 0;
    }
}

/******************************************************************************/

/******************************************************************************/
/*
 * Convert MAC type ethernet address to standard byte style ethernet address.
 *
 * Input    :   Pointer to beginning of free space for 6 byte address.
 *              Pointer to MAC_ADDR structure.
 * Return values:
 *  0   :   OK
 *  -1  :   Invalid inputs.
 */
/******************************************************************************/
int gem_enet_addr_mac_byte(u8 *enet_byte_addr, MAC_ADDR *enet_addr)
{
	if ((enet_byte_addr == NULL) || (enet_addr == NULL)) {
		return -1;
	} 
    else
    {
#if defined(BE8_MODE)
        enet_byte_addr[0] = (enet_addr->bottom >> 24) & 0xFF;
        enet_byte_addr[1] = (enet_addr->bottom >> 16) & 0xFF;
        enet_byte_addr[2] = (enet_addr->bottom >> 8) & 0xFF;
        enet_byte_addr[3] = (enet_addr->bottom) & 0xFF;
        enet_byte_addr[4] = (enet_addr->top >> 24) & 0xFF;
        enet_byte_addr[5] = (enet_addr->top >> 16) & 0xFF;
#else
        enet_byte_addr[0] = enet_addr->bottom & 0xFF;
        enet_byte_addr[1] = (enet_addr->bottom >> 8) & 0xFF;
        enet_byte_addr[2] = (enet_addr->bottom >> 16) & 0xFF;
        enet_byte_addr[3] = (enet_addr->bottom >> 24) & 0xFF;

        enet_byte_addr[4] = enet_addr->top & 0xFF;
        enet_byte_addr[5] = (enet_addr->top >> 8) & 0xFF;
#endif

        return 0;
    }
}

/******************************************************************************/

#endif
