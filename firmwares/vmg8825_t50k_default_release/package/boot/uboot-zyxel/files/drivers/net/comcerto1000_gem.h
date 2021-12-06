#ifndef __COMCERTO_GEM1000_H__
#define __COMCERTO_GEM1000_H__


/* Specify the default PCLK divisor for generating MDC.  This simply defines
 * which of the divisor control bits are active.  By default, the clock
 * division is 32.
 */
#define GEM_DEF_PCLK_DIV (MDC_DIV_96)

////////////////////////////////////////////////////////////
//      GEMAC IP wrapper                                                                                    //
////////////////////////////////////////////////////////////

#define GEM_SCH_CTL			0x8004
#define	GEM_SCH_PKT_QUEUED		0x8008

#define GEM_IP				0xE000
#define GEM_CFG				0xF000
#define GEM_MBIST			0xF004
#define GEM_SENSE_AMP_DELAY_ADJ		0xF008
#define GEM_DELAY_ELEMENT_CTRL		0xF00C
#define ADMITTANCE			0x4000

#define GEM_CONF_MODE_SEL_PIN		(0 << 0)
#define GEM_CONF_MODE_SEL_GEM		(1 << 0)

#define GEM_CONF_MODE_GEM_MASK		(7 << 1)
#define GEM_CONF_MODE_GEM_RGMII		(0 << 1)
#define GEM_CONF_MODE_GEM_RMII		(1 << 1)
#define GEM_CONF_MODE_GEM_MII		(2 << 1)
#define GEM_CONF_MODE_GEM_GMII		(3 << 1)

#define GEM_CONF_MODE_PIN_MASK		(7 << 4)
#define GEM_CONF_MODE_PIN_RGMII		(0 << 4)
#define GEM_CONF_MODE_PIN_RMII		(1 << 4)
#define GEM_CONF_MODE_PIN_MII		(2 << 4)
#define GEM_CONF_MODE_PIN_GMII		(3 << 4)

#define GEM_CONF_DUPLEX_SEL_PHY		(0 << 8)
#define GEM_CONF_DUPLEX_SEL_GEM		(1 << 8)
#define GEM_CONF_DUPLEX_GEM_HALF	(0 << 9)
#define GEM_CONF_DUPLEX_GEM_FULL	(1 << 9)
#define GEM_CONF_DUPLEX_PHY_HALF	(0 << 10)
#define GEM_CONF_DUPLEX_PHY_FULL	(1 << 10)
#define GEM_CONF_SPEED_SEL_PHY		(0 << 11)
#define GEM_CONF_SPEED_SEL_GEM		(1 << 11)

#define GEM_CONF_SPEED_MASK		(3 << 12)
#define GEM_CONF_SPEED_GEM_10M		(0 << 12)
#define GEM_CONF_SPEED_GEM_100M		(1 << 12)
#define GEM_CONF_SPEED_GEM_1G		(2 << 12)
#define GEM_CONF_SPEED_PHY_10M		(0 << 14)
#define GEM_CONF_SPEED_PHY_100M		(1 << 14)
#define GEM_CONF_SPEED_PHY_1G		(2 << 14)

#define GEM_CONF_PHY_LINK_DOWN		(0 << 16)
#define GEM_CONF_PHY_LINK_UP		(1 << 16)
#define GEM_CONF_GEM_LOOPBACK		(1 << 17)


/* Define some bit positions for registers. */

/* Bit positions for network control register */
#define GEM_READ_SNAP       (1<<14)	/* Read snapshot register */
#define GEM_TAKE_SNAP       (1<<13)	/* Take a snapshot */
#define GEM_TX_0Q_PAUSE     (1<<12)	/* Transmit zero quantum pause frame */
#define GEM_TX_PAUSE        (1<<11)	/* Transmit pause frame */
#define GEM_TX_HALT         (1<<10)	/* Halt transmission after curr frame */
#define GEM_TX_START        (1<<9)	/* Start tx (tx_go) */
#define GEM_STATS_WR_EN     (1<<7)	/* Enable writing to stat registers */
#define GEM_STATS_INC       (1<<6)	/* Increment statistic registers */
#define GEM_STATS_CLR       (1<<5)	/* Clear statistic registers */
#define GEM_MDIO_EN         (1<<4)	/* Enable MDIO port */
#define GEM_TX_EN           (1<<3)	/* Enable transmit circuits */
#define GEM_RX_EN           (1<<2)	/* Enable receive circuits */
#define GEM_LB_MAC          (1<<1)	/* Perform local loopback at MAC */
#define GEM_LB_PHY          (1<<0)	/* Perform ext loopback through PHY */

/* Bit positions for network configuration register */
#define GEM_RX_NO_PAUSE     (1<<23)	/* Do not copy pause frames to memory */
#define GEM_MDC_DIV2        (1<<20)	/* PCLK divisor for MDC, bit 2 */
#define GEM_MDC_DIV1        (1<<19)	/* PCLK divisor for MDC, bit 1 */
#define GEM_MDC_DIV0        (1<<18)	/* PCLK divisor for MDC, bit 0 */
#define GEM_RX_NO_FCS       (1<<17)	/* Discard FCS from received frames. */
#define GEM_RX_LEN_CHK      (1<<16)	/* Receive length check. */
#define GEM_RX_PAUSE_EN     (1<<13)	/* Enable pause reception */
#define GEM_RETRY_TEST      (1<<12)	/* Retry test for speeding up debug */
#define GEM_PCS_SEL         (1<<11)	/* Select PCS */
#define GEM_EAM_EN          (1<<9)	/* External address match enable */
#define GEM_FRAME_1536      (1<<8)	/* Enable 1536 byte frames reception */
#define GEM_UNICAST_EN      (1<<7)	/* Receive unicast hash frames */
#define GEM_MULTICAST_EN    (1<<6)	/* Receive multicast hash frames */
#define GEM_NO_BROADCAST    (1<<5)	/* Do not receive broadcast frames */
#define GEM_COPY_ALL        (1<<4)	/* Copy all frames */
#define GEM_RX_JUMBO        (1<<3)	/* Allow jumbo frame reception */
#define GEM_VLAN_ONLY       (1<<2)	/* Receive only VLAN frames */

/* Bit positions for network status register */
#define GEM_PHY_IDLE        (1<<2)	/* PHY management is idle */
#define GEM_MDIO_IN         (1<<1)	/* Status of mdio_in pin */
#define GEM_LINK_STATUS     (1<<0)	/* Status of link pin */

/* Bit positions for transmit status register */
#define GEM_TX_HRESP        (1<<8)	/* Transmit hresp not OK */
#define GEM_LATE_COL        (1<<7)	/* Late collision */
#define GEM_TX_URUN         (1<<6)	/* Transmit underrun occurred */
#define GEM_TX_COMPLETE     (1<<5)	/* Transmit completed OK */
#define GEM_TX_BUF_EXH      (1<<4)	/* Transmit buffs exhausted mid frame */
#define GEM_TX_GO           (1<<3)	/* Status of tx_go internal variable */
#define GEM_TX_RETRY_EXC    (1<<2)	/* Retry limit exceeded */
#define GEM_TX_COL          (1<<1)	/* Collision occurred during frame tx */
#define GEM_TX_USED         (1<<0)	/* Used bit read in tx buffer */

/* Bit positions for receive status register */
#define GEM_RX_HRESP        (1<<3)	/* Receive hresp not OK */
#define GEM_RX_ORUN         (1<<2)	/* Receive overrun occurred */
#define GEM_RX_DONE         (1<<1)	/* Frame successfully received */
#define GEM_RX_BUF_USED     (1<<0)	/* Receive buffer used bit read */

/* Bit positions for interrupts */
#define GEM_IRQ_PCS_AN      (1<<16)	/* PCS autonegotiation complete */
#define GEM_IRQ_EXT_INT     (1<<15)	/* External interrupt pin triggered */
#define GEM_IRQ_PAUSE_TX    (1<<14)	/* Pause frame transmitted */
#define GEM_IRQ_PAUSE_0     (1<<13)	/* Pause time has reached zero */
#define GEM_IRQ_PAUSE_RX    (1<<12)	/* Pause frame received */
#define GEM_IRQ_HRESP       (1<<11)	/* hresp not ok */
#define GEM_IRQ_RX_ORUN     (1<<10)	/* Receive overrun occurred */
#define GEM_IRQ_PCS_LINK    (1<<9)	/* Status of PCS link changed */
#define GEM_IRQ_TX_DONE     (1<<7)	/* Frame transmitted ok */
#define GEM_IRQ_TX_ERROR    (1<<6)	/* Transmit err occurred or no buffers */
#define GEM_IRQ_RETRY_EXC   (1<<5)	/* Retry limit exceeded */
#define GEM_IRQ_TX_URUN     (1<<4)	/* Transmit underrun occurred */
#define GEM_IRQ_TX_USED     (1<<3)	/* Tx buffer used bit read */
#define GEM_IRQ_RX_USED     (1<<2)	/* Rx buffer used bit read */
#define GEM_IRQ_RX_DONE     (1<<1)	/* Frame received ok */
#define GEM_IRQ_MAN_DONE    (1<<0)	/* PHY management operation complete */
#define GEM_IRQ_ALL         (0xFFFFFFFF)	/* Everything! */

/* Revision ID Register */
#define GEM_REV_ID_MODEL_MASK   (0x000F0000)	/* Model ID */
#define GEM_REV_ID_MODEL_BASE   (16)	/* For Shifting */
#define GEM_REV_ID_REG_MODEL    (0x00020000)	/* GEM module ID */
#define GEM_REV_ID_REV_MASK     (0x0000FFFF)	/* Revision ID */

/* Define some memory offsets for easier direct access to memory map. */
#define GEM_NET_CONTROL         (0x00)
#define GEM_NET_CONFIG          (0x04)
#define GEM_NET_STATUS          (0x08)
#define GEM_USER_IO             (0x0C)
#define GEM_DMA_CONFIG		(0x10)
#define GEM_TX_STATUS           (0x14)
#define GEM_RX_QPTR             (0x18)
#define GEM_RX_OFFSET           (0x1C)
#define GEM_RX_STATUS           (0x20)
#define GEM_IRQ_STATUS          (0x24)
#define GEM_IRQ_ENABLE          (0x28)
#define GEM_IRQ_DISABLE         (0x2C)
#define GEM_IRQ_MASK            (0x30)
#define GEM_PHY_MAN             (0x34)
#define GEM_RX_PAUSE_TIME       (0x38)
#define GEM_TX_PAUSE_QUANT      (0x3C)

#define GEM_HASH_BOT            (0x80)
#define GEM_HASH_TOP            (0x84)
#define GEM_LADDR1_BOT          (0x88)
#define GEM_LADDR1_TOP          (0x8C)
#define GEM_LADDR2_BOT          (0x90)
#define GEM_LADDR2_TOP          (0x94)
#define GEM_LADDR3_BOT          (0x98)
#define GEM_LADDR3_TOP          (0x9C)
#define GEM_LADDR4_BOT          (0xA0)
#define GEM_LADDR4_TOP          (0xA4)
#define GEM_ID_CHECK1           (0x320)
#define GEM_ID_CHECK2           (0x324)
#define GEM_ID_CHECK3           (0x328)
#define GEM_ID_CHECK4           (0x32C)
#define GEM_REV_ID              (0xFC)

#define GEM_OCT_TX_BOT          (0x100)
#define GEM_OCT_TX_TOP          (0x104)
#define GEM_STATS_FRAMES_TX     (0x108)
#define GEM_BROADCAST_TX        (0x10C)
#define GEM_MULTICAST_TX        (0x110)
#define GEM_STATS_PAUSE_TX      (0x114)
#define GEM_FRAME64_TX          (0x118)
#define GEM_FRAME65_TX          (0x11C)
#define GEM_FRAME128_TX         (0x120)
#define GEM_FRAME256_TX         (0x124)
#define GEM_FRAME512_TX         (0x128)
#define GEM_FRAME1024_TX        (0x12C)
#define GEM_FRAME1519_TX        (0x130)
#define GEM_STATS_TX_URUN       (0x134)
#define GEM_STATS_SINGLE_COL    (0x138)
#define GEM_STATS_MULTI_COL     (0x13C)
#define GEM_STATS_EXCESS_COL    (0x140)
#define GEM_STATS_LATE_COL      (0x144)
#define GEM_STATS_DEF_TX        (0x148)
#define GEM_STATS_CRS_ERRORS    (0x14C)
#define GEM_OCT_RX_BOT          (0x150)
#define GEM_OCT_RX_TOP          (0x154)
#define GEM_STATS_FRAMES_RX     (0x158)
#define GEM_BROADCAST_RX        (0x15C)
#define GEM_MULTICAST_RX        (0x160)
#define GEM_STATS_PAUSE_RX      (0x164)
#define GEM_FRAME64_RX          (0x168)
#define GEM_FRAME65_RX          (0x16C)
#define GEM_FRAME128_RX         (0x170)
#define GEM_FRAME256_RX         (0x174)
#define GEM_FRAME512_RX         (0x178)
#define GEM_FRAME1024_RX        (0x17C)
#define GEM_FRAME1519_RX        (0x180)
#define GEM_STATS_USIZE_FRAMES  (0x184)
#define GEM_STATS_EXCESS_LEN    (0x188)
#define GEM_STATS_JABBERS       (0x18C)
#define GEM_STATS_FCS_ERRORS    (0x190)
#define GEM_STATS_LENGTH_ERRORS (0x194)
#define GEM_STATS_RX_SYM_ERR    (0x198)
#define GEM_STATS_ALIGN_ERRORS  (0x19C)
#define GEM_STATS_RX_RES_ERR    (0x1a0)
#define GEM_STATS_RX_ORUN       (0x1a4)

#define GEM_REG_TOP             (0x23C)

#define	GEM_QUEUE_BASE0		(0x300)
#define	GEM_QUEUE_BASE1		(0x304)
#define	GEM_QUEUE_BASE2		(0x308)
#define	GEM_QUEUE_BASE3		(0x30C)
#define	GEM_QUEUE_BASE4		(0x310)
#define	GEM_QUEUE_BASE5		(0x314)
#define	GEM_QUEUE_BASE6		(0x318)
#define	GEM_QUEUE_BASE7		(0x31C)

#define GEM_ID_CHECK5           (0x320)
#define GEM_ID_CHECK6           (0x324)
#define GEM_ID_CHECK7           (0x328)
#define GEM_ID_CHECK8           (0x32C)
 
// memory offsets for admittance registers
#define ADM_CFG			(0x00C)

struct gemac_info_struct {
	unsigned int baseaddr;
	unsigned int phyaddr;
	unsigned int gemacconfig;
	u32 mode;
	u32 phyflags;		// to indicate if gigabit supported or not
	unsigned int phyregidx;
};

struct rx_desc {
	volatile u32 data;
	volatile u32 status;
	volatile u32 extstatus;
	u32 pad;
};
//gemac rx controls
// Wrap flag - marks last descriptor in a queue when set
// goes to the status word (offset 0x4)
#define GEMRX_WRAP 	(1<<28)
// Ownership flag - when 0 gem can use the descriptor
// goes to the extended status word (offset 0x8)
#define GEMRX_OWN	(1<<15)

// gemac rx status
#define RX_STA_BCAST		(1UL<<31)
#define RX_STA_MCAST		(1<<30)
#define RX_STA_UM		(1<<29)
#define RX_MAC_MATCH_FLAG 	(0x4<<25)
#define RX_MAC_MATCH_NUM_MASK	(0x3<<25)
#define RX_MAC_MATCH_POS 	25
#define RX_INT 			(1<<24)
#define RX_IPSEC_OUT		(1<<23)
#define RX_IPSEC_IN	 	(1<<22)
#define RX_STA_VLAN 		(1<<21)
#define RX_STA_VLAN_802p 	(1<<20)
#define RX_STA_VLAN_PRI_MASK	(7<<17)
#define RX_STA_VLAN_PRI_POS	17
#define RX_STA_VLAN_CFI		(1<<16)
#define RX_STA_SOF		(1<<15)
#define RX_STA_EOF		(1<<14)
#define RX_STA_PACKET		(RX_STA_SOF|RX_STA_EOF)
#define RX_STA_CRCERR		(1<<13)
#define RX_STA_LEN_MASK		0x1fff
#define RX_STA_LEN_POS		0
#define	RX_CHECK_ERROR		RX_STA_CRCERR
// gemac rx extended status(word2)
#define RX_STA_L4OFF_MASK	(0xff<<24)
#define RX_STA_L4OFF_POS	24
#define RX_STA_L3OFF_MASK	(0xff<<16)
#define RX_STA_L3OFF_POS	16

#define RX_STA_L3_CKSUM		(1<<11)
#define RX_STA_L3_GOOD		(1<<12)
#define RX_STA_L4_CKSUM		(1<<13)
#define RX_STA_L4_GOOD		(1<<14)

#define RX_STA_TCP		(1<<9)
#define RX_STA_UDP		(1<<8)
#define RX_STA_IPV6		(1<<7)
#define RX_STA_IPV4		(1<<6)
#define RX_STA_PPPOE		(1<<5)
#define RX_STA_WILLHANDLE	(RX_STA_IPV6 | RX_STA_IPV4)
#define RX_STA_QinQ		(1<<4)
#define RX_STA_TYPEID_MATCH_FLAG (0x8 << 0)
#define RX_STA_TYPEID		(0x7 << 0)
#define RX_STA_TYPEID_POS	0

struct tx_desc {
	volatile u32 data;
	volatile u32 ctl;
};

#define TX_DESC_WORD1_USED	(BIT31)
#define TX_DESC_WORD1_WRAP	(BIT30)
#define TX_DESC_WORD1_INT	(BIT29)
#define TX_DESC_WORD1_ERR1	(BIT28)
#define TX_DESC_WORD1_ERR2	(BIT27)
#define TX_DESC_WORD1_TXCSUM_MASK	(BIT26|BIT25)
#define	TX_DESC_CSUM(a)		((a&(TX_DESC_WORD1_TXCSUM_MASK))<<25)
#define TX_DESC_WORD1_FCS	(BIT24)
#define TX_DESC_WORD1_LAST	(BIT15)
#define TX_DESC_WORD1_POOLB	(BIT14)
#define TX_DESC_WORD1_BUFRET	(BIT13)
#define TX_DESC_WORD1_LEGTH_MASK (0x1FFF)

/* This is a structure that will be passed and used for all HAL operations, it
 * consists of pointers to the various MAC structures such as the MAC register
 * block and the first descriptor element for the rx and tx buffer queues.
 * Other internal variables declared for use in function calls and to keep track
 * of where things are.
 */
struct gemac_dev {
	void *registers;	/* Pointer to the MAC address space. */
	void *phyregisters;	/* Pointer to the MAC address space controlling the phy */

	void *baseaddr;
	struct phy_info *phyinfo;
	u32 phyaddr;
	u32 mode;
	u32 phyflags;
	struct eth_device *dev;
};

#endif
