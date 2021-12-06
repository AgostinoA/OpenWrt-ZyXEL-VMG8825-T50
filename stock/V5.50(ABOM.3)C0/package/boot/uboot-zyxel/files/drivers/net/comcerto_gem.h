#ifndef __COMCERTO_GEM_H__
#define __COMCERTO_GEM_H__

/* An enumerated type for loopback values.  This can be one of three values, no
 * loopback -normal operation, local loopback with internal loopback module of
 * MAC or PHY loopback which is through the external PHY.
 */
#ifndef __MAC_LOOP_ENUM__
#define __MAC_LOOP_ENUM__
typedef enum { LB_NONE, LB_EXT, LB_LOCAL } MAC_LOOP;
#endif

/* The possible operating speeds of the MAC, currently supporting 10, 100 and
 * 1000Mb modes.
 */
#ifndef __MAC_SPEED_ENUM__
#define __MAC_SPEED_ENUM__
typedef enum { SPEED_10M, SPEED_100M, SPEED_1000M, SPEED_1000M_PCS } MAC_SPEED;
#endif

/* The possible AMBA AHB bus width of the MAC, currently supporting 32, 64 and
 * 128 bits.
 */
#ifndef __MAC_AHB_ENUM__
#define __MAC_AHB_ENUM__
typedef enum { AMBA_AHB_32, AMBA_AHB_64, AMBA_AHB_128 } MAC_AHB_WIDTH;
#endif

/* The possible MDC clock division of the MAC, currently supporting 8, 16 , 32,
 * 48, 64, 96, 128, 224.
 */
#ifndef __MAC_DMCDIV_ENUM__
#define __MAC_DMCDIV_ENUM__
typedef enum { MDC_DIV_8, MDC_DIV_16, MDC_DIV_32, MDC_DIV_48, MDC_DIV_64,
	MDC_DIV_96, MDC_DIV_128, MDC_DIV_224
} MAC_MDC_DIV;
#endif

#define MDIO_TIMEOUT            5000	/* instruction cycles? */

/* Specify whether the MDIO should be available, this is set so that for reset
 * function, appropriate options are setup.  To disable, use 0.
 */
#define GEM_MDIO_ENABLED (GEM_MDIO_EN)

/* Specify the default AMBA AHB bus width.  This simply defines
 * which of the bus width control bits are active.  By default, the bus
 * width is 32.
 */
#define GEM_DEF_AHB_WIDTH (AMBA_AHB_32)

/* Specify default duplex mode, for half duplex - specify 0. */
#ifndef GEM_DEF_DUPLEX
/* Allow the value to be specified as compiler option 
   0 - half-duplex, 
   GEM_FULL_DUPLEX - full-duplex
*/
#define GEM_DEF_DUPLEX (GEM_FULL_DUPLEX)
#endif

/* Specify default operating speed, 1 for 100Mb.  Note that this is left
 * shifted.  Also note that this simply asserts a signal to the PHY and has no
 * effect on the operation of the MAC.
 * For 10Mb/s mode, specify         SPEED_10M
 * For 100Mb/s mode, specify        SPEED_100M
 * For 1Gb/s mode, specify          SPEED_1000M
 * For 1Gb/s with PCS mode, specify SPEED_1000M_PCS
 */
#ifndef GEM_DEF_SPEED
/* Allow the value to be specified as compiler option */
#define GEM_DEF_SPEED (SPEED_1000M)
#endif

/* Specify default loopback mode.  LB_NONE for no loopback, other values are LB_MAC
 * and LB_PHY
 */
#define GEM_DEF_LOOP (LB_NONE)

/* Define some types for using with the HAL.  These types correspond to the
 * memory map and programming structure of the MAC device.
 * All structures are 'volatile' to indicate they can be changed by some non-
 * programming means - i.e. by the hardware itself.  This prevents the compiler
 * from making false assumptions on how to optimise the code.  Some elements
 * are also defined as 'const' to enforce some checks on the programmer.  These
 * are only for register fields that can only be changed by the hardware and are
 * not writable.
 */

/* The Address organisation for the MAC device.  All addresses are split into
 * two 32-bit register fields.  The first one (bottom) is the lower 32-bits of
 * the address and the other field are the high order bits - this may be 16-bits
 * in the case of MAC addresses, or 32-bits for the hash address.
 * In terms of memory storage, the first item (bottom) is assumed to be at a
 * lower address location than 'top'. i.e. top should be at address location of
 * 'bottom' + 4 bytes.
 */
#ifndef __MAC_ADDR_DEF__
#define __MAC_ADDR_DEF__
typedef struct {
	u32 bottom;		/* Lower 32-bits of address. */
	u32 top;		/* Upper 32-bits of address. */
} volatile MAC_ADDR;
#endif

/* The following is the organisation of the address filters section of the MAC
 * registers.  The Cadence MAC contains four possible specific address match
 * addresses, if an incoming frame corresponds to any one of these four
 * addresses then the frame will be copied to memory.
 * It is not necessary for all four of the address match registers to be
 * programmed, this is application dependant.
 */
#ifndef __SPEC_ADDR_DEF__
#define __SPEC_ADDR_DEF__
typedef struct {
	MAC_ADDR one;		/* Specific address register 1. */
	MAC_ADDR two;		/* Specific address register 2. */
	MAC_ADDR three;		/* Specific address register 3. */
	MAC_ADDR four;		/* Specific address register 4. */
} volatile SPEC_ADDR;
#endif

/* The set of statistics registers implemented in the Cadence MAC.
 * The statistics registers implemented are a subset of all the statistics
 * available, but contains all the compulsory ones.
 * For full descriptions on the registers, refer to the Cadence MAC programmers
 * guide or the IEEE 802.3 specifications.
 */
typedef struct {
	u32 octets_tx_bot;	/* Lower 32-bits for number of octets tx'd */
	u32 octets_tx_top;	/* Upper 16-bits for number of octets tx'd */
	u32 frames_tx;		/* Number of frames transmitted OK */
	u32 broadcast_tx;	/* Number of broadcast frames transmitted */
	u32 multicast_tx;	/* Number of multicast frames transmitted */
	u32 pause_tx;		/* Number of pause frames transmitted. */
	u32 frame64_tx;		/* Number of 64byte frames transmitted */
	u32 frame65_127_tx;	/* Number of 65-127 byte frames transmitted */
	u32 frame128_255_tx;	/* Number of 128-255 byte frames transmitted */
	u32 frame256_511_tx;	/* Number of 256-511 byte frames transmitted */
	u32 frame512_1023_tx;	/* Number of 512-1023 byte frames transmitted */
	u32 frame1024_1518_tx;	/* Number of 1024-1518 byte frames transmitted */
	u32 frame1519_tx;	/* Number of frames greater than 1518 bytes tx */
	u32 tx_urun;		/* Transmit underrun errors due to DMA */
	u32 single_col;		/* Number of single collision frames */
	u32 multi_col;		/* Number of multi collision frames */
	u32 excess_col;		/* Number of excessive collision frames. */
	u32 late_col;		/* Collisions occuring after slot time */
	u32 def_tx;		/* Frames deferred due to crs */
	u32 crs_errors;		/* Errors caused by crs not being asserted. */

	u32 octets_rx_bot;	/* Lower 32-bits for number of octets rx'd */
	u32 octets_rx_top;	/* Upper 16-bits for number of octets rx'd */
	u32 frames_rx;		/* Number of frames received OK */
	u32 broadcast_rx;	/* Number of broadcast frames received */
	u32 multicast_rx;	/* Number of multicast frames received */
	u32 pause_rx;		/* Number of pause frames received. */
	u32 frame64_rx;		/* Number of 64byte frames received */
	u32 frame65_127_rx;	/* Number of 65-127 byte frames received */
	u32 frame128_255_rx;	/* Number of 128-255 byte frames received */
	u32 frame256_511_rx;	/* Number of 256-511 byte frames received */
	u32 frame512_1023_rx;	/* Number of 512-1023 byte frames received */
	u32 frame1024_1518_rx;	/* Number of 1024-1518 byte frames received */
	u32 frame1519_rx;	/* Number of frames greater than 1518 bytes rx */
	u32 usize_frames;	/* Frames received less than min of 64 bytes */
	u32 excess_length;	/* Number of excessive length frames rx */
	u32 jabbers;		/* Excessive length + crc or align errors. */
	u32 fcs_errors;		/* Number of frames received with crc errors */
	u32 length_check_errors;	/* Number of frames with incorrect length */
	u32 rx_symbol_errors;	/* Number of times rx_er asserted during rx */
	u32 align_errors;	/* Frames received without integer no. bytes */
	u32 rx_res_errors;	/* Number of times buffers ran out during rx */
	u32 rx_orun;		/* Receive overrun errors due to DMA */

} volatile GEM_STATS;
#if 0
/* This is the memory map for the Cadence Enhanced MAC device.
 * For full descriptions on the registers, refer to the Cadence MAC programmers
 * guide or the IEEE 802.3 specifications.
 */
typedef struct {
	u32 net_control;	/* Network control 0x00 */
	u32 net_config;		/* Network config 0x04 */
	const volatile u32 net_status;	/* Network status, RO, 0x08 */
	volatile u32 user_io;	/* User IO 0x0C */
	volatile u32 dma;	/* DMA interface 0x10 */
	u32 tx_status;		/* Transmit status 0x14 */
	u32 rx_qptr;		/* Receive queue pointer 0x18 */
	u32 tx_qptr;		/* Transmit queue pointer 0x1C */
	u32 rx_status;		/* Receive status 0x20 */
	u32 irq_status;		/* Interrupt status 0x24 */
	u32 irq_enable;		/* Interrupt enable 0x28 */
	u32 irq_disable;	/* Interrupt disable 0x2C */
	const volatile u32 irq_mask;	/* Interrupt mask, RO, 0x30 */
	u32 phy_man;		/* PHY management 0x34 */
	const volatile u32 pause_time;	/* Pause time register 0x38 */
	u32 tx_pause_quant;	/* Transmit pause quantum 0x3C */
	u32 reserved[16];	/* Reserved */
	MAC_ADDR hash_addr;	/* Hash address 0x80 - 0x84 */
	SPEC_ADDR address;	/* Specific addresses 0x88 - 0xA4 */
	u32 id_check1;		/* Type ID check1 0xA8 */
	u32 id_check2;		/* Type ID check2 0xAC */
	u32 id_check3;		/* Type ID check3 0xB0 */
	u32 id_check4;		/* Type ID check4 0xB4 */
	u32 rsvd2[17];		/* Reserved */
	u32 rev_id;		/* Device Revision ID 0xFC */
	GEM_STATS stats;	/* MAC statistics 0x100 - 0x1A4 */
} volatile GEM_REG;
#endif

#define GEMAC_SW_CONF		(1 << 8) | (1 << 11)    // GEMAC configured by SW
#define GEMAC_PHY_CONF		0                       // GEMAC configured by phy lines (not for MII/GMII)
#define GEMAC_SW_FULL_DUPLEX	(1 << 9)
#define GEMAC_SW_SPEED_10M	(0 << 12)
#define GEMAC_SW_SPEED_100M	(1 << 12)
#define GEMAC_SW_SPEED_1G	(2 << 12)

#define CONFIG_COMCERTO_USE_MII		(1 << 0)
#define CONFIG_COMCERTO_USE_RMII	(1 << 1)
#define CONFIG_COMCERTO_USE_GMII	(1 << 2)
#define CONFIG_COMCERTO_USE_RGMII	(1 << 3)

// flags to be used for phy config
#define GEMAC_NO_PHY				(1 << 0)	/* GEMAC is not connected to PHY */
#define GEMAC_PHY_AUTONEG			(1 << 1)	/* Enable PHY autonegotiation */
#define GEMAC_GEM_DELAY_DISABLE			(1 << 2)	/* Disable delay on GEM Tx/Rx clocks */
#define GEMAC_M88E1111_PHY_RGMII_ADD_DELAY	(1 << 3)	/* Enable delay on Marvel 88E1111 PHY Tx/Rx clocks */

#if defined(CONFIG_COMCERTO_100)
#include "comcerto100_gem.h"
#else
#include "comcerto1000_gem.h"
#endif

/******************************************************************************/
/*
 * Prototypes for functions of HAL
*/
/******************************************************************************/

/* Re-initialise device and check reset values. */
int gem_reset(struct gemac_dev *gemac);

/* Device setup. */

void gem_set_loop(struct gemac_dev *gemac, MAC_LOOP gem_loop);
MAC_LOOP gem_get_loop(struct gemac_dev *gemac);

void gem_enable_eam(struct gemac_dev *gemac);
void gem_disable_eam(struct gemac_dev *gemac);

void gem_enable_fcs_rx(struct gemac_dev *gemac);
void gem_disable_fcs_rx(struct gemac_dev *gemac);

void gem_enable_1536_rx(struct gemac_dev *gemac);
void gem_disable_1536_rx(struct gemac_dev *gemac);

void gem_full_duplex(struct gemac_dev *gemac);
void gem_half_duplex(struct gemac_dev *gemac);

void gem_set_speed(struct gemac_dev *gemac, MAC_SPEED gem_speed);
MAC_SPEED gem_get_speed(struct gemac_dev *gemac);

void gem_set_ahb_width(struct gemac_dev *gemac, MAC_AHB_WIDTH gem_buswidth);
MAC_AHB_WIDTH gem_get_ahb_width(struct gemac_dev *gemac);

void gem_set_mdc_div(struct gemac_dev *gemac, MAC_MDC_DIV gem_mdcdiv);
MAC_MDC_DIV gem_get_mdc_div(struct gemac_dev *gemac);

/* Pause control. */
void gem_enable_pause_rx(struct gemac_dev *gemac);
void gem_disable_pause_rx(struct gemac_dev *gemac);

u32 gem_pause_time(struct gemac_dev *gemac);

void gem_enable_pause_cpy(struct gemac_dev *gemac);
void gem_disable_pause_cpy(struct gemac_dev *gemac);

void gem_send_0q_pause(struct gemac_dev *gemac);
void gem_send_pause(struct gemac_dev *gemac);

void gem_set_tx_pause_q(struct gemac_dev *gemac, u32 gem_pause);
u32 gem_get_tx_pause_q(struct gemac_dev *gemac);

/* PHY management control. */
void gem_enable_MDIO(struct gemac_dev *gemac);
void gem_disable_MDIO(struct gemac_dev *gemac);

int gem_phy_man_wr(struct gemac_dev *gemac, u8 phy_addr, u8 reg_addr, u32 data);
int gem_phy_man_rd(struct gemac_dev *gemac, u8 phy_addr, u8 reg_addr);
u32 gem_phy_man_data(struct gemac_dev *gemac);

int gem_phy_man_idle(struct gemac_dev *gemac);

int gem_link_status(struct gemac_dev *gemac);

/* Address setup and control. */
void gem_enable_unicast(struct gemac_dev *gemac);
void gem_disable_unicast(struct gemac_dev *gemac);

void gem_enable_multicast(struct gemac_dev *gemac);
void gem_disable_multicast(struct gemac_dev *gemac);

void gem_allow_broadcast(struct gemac_dev *gemac);
void gem_no_broadcast(struct gemac_dev *gemac);

void gem_enable_copy_all(struct gemac_dev *gemac);
void gem_disable_copy_all(struct gemac_dev *gemac);

void gem_set_hash(struct gemac_dev *gemac, MAC_ADDR *hash_addr);
MAC_ADDR gem_get_hash(struct gemac_dev *gemac);

void gem_set_address(struct gemac_dev *gemac, SPEC_ADDR *spec_addr);
SPEC_ADDR gem_get_address(struct gemac_dev *gemac);

/* Functions to convert between address formats. */
int gem_enet_addr_byte_mac(u8 *enet_byte_addr, MAC_ADDR *enet_addr);
int gem_enet_addr_mac_byte(u8 *enet_byte_addr, MAC_ADDR *enet_addr);

void gem_set_laddr1(struct gemac_dev *gemac, MAC_ADDR *address);
void gem_set_laddr2(struct gemac_dev *gemac, MAC_ADDR *address);
void gem_set_laddr3(struct gemac_dev *gemac, MAC_ADDR *address);
void gem_set_laddr4(struct gemac_dev *gemac, MAC_ADDR *address);
MAC_ADDR gem_get_laddr1(struct gemac_dev *gemac);
MAC_ADDR gem_get_laddr2(struct gemac_dev *gemac);
MAC_ADDR gem_get_laddr3(struct gemac_dev *gemac);
MAC_ADDR gem_get_laddr4(struct gemac_dev *gemac);

void gem_set_id_check1(struct gemac_dev *gemac, u32 id_check);
void gem_set_id_check2(struct gemac_dev *gemac, u32 id_check);
void gem_set_id_check3(struct gemac_dev *gemac, u32 id_check);
void gem_set_id_check4(struct gemac_dev *gemac, u32 id_check);
u32 gem_get_id_check1(struct gemac_dev *gemac);
u32 gem_get_id_check2(struct gemac_dev *gemac);
u32 gem_get_id_check3(struct gemac_dev *gemac);
u32 gem_get_id_check4(struct gemac_dev *gemac);

void gem_enable_len_check(struct gemac_dev *gemac);
void gem_disable_len_check(struct gemac_dev *gemac);

/* Interrupt handling and masking. */
void gem_set_irq_stat(struct gemac_dev *gemac, u32 irq_status);
u32 gem_get_irq_stat(struct gemac_dev *gemac);

void gem_enable_irq(struct gemac_dev *gemac, u32 irq_en);
void gem_mask_irq(struct gemac_dev *gemac, u32 irq_mask);
u32 gem_get_irq_mask(struct gemac_dev *gemac);

/* Transmit control. */
int gem_start_tx(struct gemac_dev *gemac);
void gem_stop_tx(struct gemac_dev *gemac);
void gem_abort_tx(struct gemac_dev *gemac);
int gem_restart_tx(struct gemac_dev *gemac);
int gem_transmitting(struct gemac_dev *gemac);
u32 gem_get_tx_stat(struct gemac_dev *gemac);
void gem_reset_tx_stat(struct gemac_dev *gemac, u32 rst_status);
void gem_reset_tx_q(struct gemac_dev *gemac);

/* Receive control. */
int gem_enable_rx(struct gemac_dev *gemac);
void gem_disable_rx(struct gemac_dev *gemac);
void gem_reset_rx_q(struct gemac_dev *gemac);

int gem_receive_on(struct gemac_dev *gemac);
u32 gem_get_rx_stat(struct gemac_dev *gemac);
void gem_reset_rx_stat(struct gemac_dev *gemac, u32 rst_status);

void gem_enable_rx_jmb(struct gemac_dev *gemac);
void gem_disable_rx_jmb(struct gemac_dev *gemac);

void gem_enable_vlan_only(struct gemac_dev *gemac);
void gem_disable_vlan_only(struct gemac_dev *gemac);

/* Snapshot of statistic registers */
void gem_enable_rd_snap(struct gemac_dev *gemac);
void gem_disable_rd_snap(struct gemac_dev *gemac);
void gem_take_snap(struct gemac_dev *gemac);

/* Debug options. */
void gem_stats_wr_en(struct gemac_dev *gemac);
void gem_stats_wr_off(struct gemac_dev *gemac);
void gem_stats_inc(struct gemac_dev *gemac);
void gem_stats_clr(struct gemac_dev *gemac);

void gem_enable_bp(struct gemac_dev *gemac);
void gem_disable_bp(struct gemac_dev *gemac);

void gem_en_retry_test(struct gemac_dev *gemac);
void gem_dis_retry_test(struct gemac_dev *gemac);

GEM_STATS gem_get_stats(struct gemac_dev *gemac);
void gem_set_stats(struct gemac_dev *gemac, GEM_STATS *stats);

/* Generic register access interface. */
u32 gem_register_rd(struct gemac_dev *gemac, u32 reg_addr);
int gem_register_wr(struct gemac_dev *gemac, u32 reg_addr, u32 data);

/******************************************************************************/

#endif
