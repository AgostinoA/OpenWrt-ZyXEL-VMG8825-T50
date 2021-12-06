/*
 * Copyright (c) 2014, 2015-2017 The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <common.h>
#include <pci.h>

#include <linux/sizes.h>
#include <asm/io.h>
#include <asm/errno.h>
#include <asm/arch-qca-common/gpio.h>
#include <asm/arch-qca-common/iomap.h>
#include <fdtdec.h>
#include <dm.h>

DECLARE_GLOBAL_DATA_PTR;

#define PCIE_RST_CTRL_PIPE_ARES			0x4
#define PCIE_RST_CTRL_PIPE_STICKY_ARES		0x100
#define PCIE_RST_CTRL_PIPE_PHY_AHB_ARES		0x800
#define PCIE_RST_CTRL_AXI_M_ARES		0x1
#define PCIE_RST_CTRL_AXI_M_STICKY_ARES		0x80
#define PCIE_RST_CTRL_AXI_S_ARES		0x2
#define PCIE_RST_CTRL_AHB_ARES			0x400


#define PCI_CFG0_RDWR			0x4
#define PCI_CFG1_RDWR			0x5
#define RD				0
#define WR 				1

#define MSM_PCIE_DEV_CFG_ADDR                   0x01000000
#define PCIE20_PLR_IATU_VIEWPORT		0x900
#define PCIE20_PLR_IATU_CTRL1			0x904
#define PCIE20_PLR_IATU_CTRL2			0x908
#define PCIE20_PLR_IATU_LBAR			0x90C
#define PCIE20_PLR_IATU_UBAR			0x910
#define PCIE20_PLR_IATU_LAR			0x914
#define PCIE20_PLR_IATU_LTAR			0x918
#define PCIE20_PLR_IATU_UTAR			0x91c

/* PCIE20_PARF_PHYS Registers */
#define PARF_SLV_ADDR_SPACE_SIZE		0x16C
#define SLV_ADDR_SPACE_SZ			0x40000000
#define PCIE_0_PCIE20_PARF_LTSSM		0x1B0
#define LTSSM_EN				(1 << 8)
/* PCIE20_PHYS Registers */
#define PCIE_0_PORT_FORCE_REG			0x708
#define PCIE_0_ACK_F_ASPM_CTRL_REG		0x70C
#define L1_ENTRANCE_LATENCY(x)			(x << 27)
#define L0_ENTRANCE_LATENCY(x)			(x << 24)
#define COMMON_CLK_N_FTS(x)			(x << 16)
#define ACK_N_FTS(x)				(x << 8)

#define PCIE_0_GEN2_CTRL_REG			0x80C
#define FAST_TRAINING_SEQ(x)			(x << 0)
#define NUM_OF_LANES(x)				(x << 8)
#define DIRECT_SPEED_CHANGE			(1 << 17)

#define PCIE_0_TYPE0_STATUS_COMMAND_REG_1	0x004
#define PCI_TYPE0_BUS_MASTER_EN			(1 << 2)

#define PCIE_0_MISC_CONTROL_1_REG		0x8BC
#define DBI_RO_WR_EN				(1 << 0)

#define PCIE_0_LINK_CAPABILITIES_REG		0x07C
#define PCIE_CAP_ASPM_OPT_COMPLIANCE		(1 << 22)
#define PCIE_CAP_LINK_BW_NOT_CAP		(1 << 21)
#define PCIE_CAP_DLL_ACTIVE_REP_CAP		(1 << 20)
#define PCIE_CAP_L1_EXIT_LATENCY(x)		(x << 15)
#define PCIE_CAP_L0S_EXIT_LATENCY(x)		(x << 12)
#define PCIE_CAP_MAX_LINK_WIDTH(x)		(x << 4)
#define PCIE_CAP_MAX_LINK_SPEED(x)		(x << 0)

#define PCIE_0_DEVICE_CONTROL2_DEVICE_STATUS2_REG	0x098
#define PCIE_CAP_CPL_TIMEOUT_DISABLE			(1 << 4)
#define PCIE_0_TYPE0_LINK_CONTROL_LINK_STATUS_REG_1	0x080
#define PCIE20_AXI_MSTR_RESP_COMP_CTRL0                 0x818
#define PCIE20_AXI_MSTR_RESP_COMP_CTRL1                 0x81c

#define PCIE20_SIZE   			SZ_4K
#define PCIE_AXI_CONF_SIZE   		SZ_1M

#define PCIE_USB3_PCS_POWER_DOWN_CONTROL		0x804
#define QSERDES_COM_BIAS_EN_CLKBUFLR_EN			0x34
#define QSERDES_COM_CLK_ENABLE1				0x38
#define QSERDES_COM_BG_TRIM				0x70
#define QSERDES_COM_LOCK_CMP_EN				0xC8
#define QSERDES_COM_VCO_TUNE_MAP			0x128
#define QSERDES_COM_VCO_TUNE_TIMER1			0x144
#define QSERDES_COM_VCO_TUNE_TIMER2			0x144
#define QSERDES_COM_CMN_CONFIG				0x194
#define QSERDES_COM_PLL_IVCO				0x48
#define QSERDES_COM_HSCLK_SEL				0x178
#define QSERDES_COM_SVS_MODE_CLK_SEL			0x19C
#define QSERDES_COM_CORE_CLK_EN				0x18C
#define QSERDES_COM_CORECLK_DIV				0x184
#define QSERDES_COM_RESETSM_CNTRL			0xB4
#define QSERDES_COM_BG_TIMER				0xC
#define QSERDES_COM_SYSCLK_EN_SEL			0xAC
#define QSERDES_COM_DEC_START_MODE0			0xD0
#define QSERDES_COM_DIV_FRAC_START3_MODE0		0xE4
#define QSERDES_COM_DIV_FRAC_START2_MODE0		0xE0
#define QSERDES_COM_DIV_FRAC_START1_MODE0		0xDC
#define QSERDES_COM_LOCK_CMP3_MODE0			0x54
#define QSERDES_COM_LOCK_CMP2_MODE0			0x50
#define QSERDES_COM_LOCK_CMP1_MODE0			0x4C
#define QSERDES_COM_CLK_SELECT				0x174
#define QSERDES_COM_SYS_CLK_CTRL			0x3C
#define QSERDES_COM_SYSCLK_BUF_ENABLE			0x40
#define QSERDES_COM_CP_CTRL_MODE0			0x78
#define QSERDES_COM_PLL_RCTRL_MODE0			0x84
#define QSERDES_COM_PLL_CCTRL_MODE0			0x90
#define QSERDES_COM_INTEGLOOP_GAIN1_MODE0		0x10C
#define QSERDES_COM_INTEGLOOP_GAIN0_MODE0		0x108
#define QSERDES_COM_BIAS_EN_CTRL_BY_PSM			0xA8
#define QSERDES_COM_VCO_TUNE_CTRL			0xC
#define QSERDES_COM_SSC_EN_CENTER			0x10
#define QSERDES_COM_SSC_PER1				0x1C
#define QSERDES_COM_SSC_PER2				0x20
#define QSERDES_COM_SSC_ADJ_PER1			0x14
#define QSERDES_COM_SSC_ADJ_PER2			0x18
#define QSERDES_COM_SSC_STEP_SIZE1			0x24
#define QSERDES_COM_SSC_STEP_SIZE2			0x28
#define QSERDES_TX_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN     0x268
#define QSERDES_TX_LANE_MODE                            0x294
#define QSERDES_TX_RES_CODE_LANE_OFFSET                 0x254
#define QSERDES_TX_RCV_DETECT_LVL_2                     0x2AC
#define QSERDES_RX_SIGDET_ENABLES                       0x510
#define QSERDES_RX_SIGDET_DEGLITCH_CNTRL                0x51C
#define QSERDES_RX_RX_EQU_ADAPTOR_CNTRL2                0x4D8
#define QSERDES_RX_RX_EQU_ADAPTOR_CNTRL3                0x4DC
#define QSERDES_RX_RX_EQU_ADAPTOR_CNTRL4                0x4E0
#define QSERDES_RX_UCDR_SO_SATURATION_AND_ENABLE        0x448
#define QSERDES_RX_UCDR_SO_GAIN                         0x41C
#define QSERDES_RX_UCDR_SO_GAIN_HALF                    0x410
#define QSERDES_COM_CLK_EP_DIV                          0x74
#define PCIE_USB3_PCS_ENDPOINT_REFCLK_DRIVE             0x854
#define PCIE_USB3_PCS_OSC_DTCT_ACTIONS                  0x9AC
#define PCIE_USB3_PCS_PWRUP_RESET_DLY_TIME_AUXCLK       0x8A0
#define PCIE_USB3_PCS_L1SS_WAKEUP_DLY_TIME_AUXCLK_MSB   0x9E0
#define PCIE_USB3_PCS_L1SS_WAKEUP_DLY_TIME_AUXCLK_LSB   0x9DC
#define PCIE_USB3_PCS_PLL_LOCK_CHK_DLY_TIME_AUXCLK_LSB  0x9A8
#define PCIE_USB3_PCS_LP_WAKEUP_DLY_TIME_AUXCLK         0x8A4
#define PCIE_USB3_PCS_PLL_LOCK_CHK_DLY_TIME             0x8A8
#define QSERDES_RX_SIGDET_CNTRL                         0x514
#define PCIE_USB3_PCS_RX_SIGDET_LVL                     0x9D8
#define PCIE_USB3_PCS_TXDEEMPH_M6DB_V0                  0x824
#define PCIE_USB3_PCS_TXDEEMPH_M3P5DB_V0                0x828
#define PCIE_USB3_PCS_SW_RESET                          0x800
#define PCIE_USB3_PCS_START_CONTROL                     0x808

#define PCIE20_PARF_PHY_CTRL		0x40
#define PHY_CTRL_PHY_TX0_TERM_OFFSET_MASK       (0x1f << 16)
#define PHY_CTRL_PHY_TX0_TERM_OFFSET(x)         (x << 16)

#define PCIE20_PARF_PHY_REFCLK		0x4C
#define REF_SSP_EN				BIT(16)
#define REF_USE_PAD				BIT(12)

#define PCIE20_PARF_PCS_DEEMPH		0x34
#define PCIE20_PARF_PCS_DEEMPH_TX_DEEMPH_GEN1(x) (x << 16)
#define PCIE20_PARF_PCS_DEEMPH_TX_DEEMPH_GEN2_3_5DB(x) (x << 8)
#define PCIE20_PARF_PCS_DEEMPH_TX_DEEMPH_GEN2_6DB(x) (x << 0)

#define PCIE20_PARF_PCS_SWING		0x38
#define PCIE20_PARF_PCS_SWING_TX_SWING_FULL(x)	(x << 8)
#define PCIE20_PARF_PCS_SWING_TX_SWING_LOW(x)	(x << 0)

#define PCIE20_PARF_CONFIG_BITS		0x50

#define PCIE_SFAB_AXI_S5_FCLK_CTL 	0x00902154

#define PCIE20_ELBI_SYS_CTRL		0x04

static unsigned int local_buses[] = { 0, 0 };
struct pci_controller pci_hose[PCI_MAX_DEVICES];
static int phy_initialised;

enum pcie_verion{
	PCIE_V0,
	PCIE_V1,
	PCIE_V2,
};

static const struct udevice_id pcie_ver_ids[] = {
	{ .compatible = "qcom,ipq806x-pcie", .data = PCIE_V0 },
	{ .compatible = "qcom,ipq40xx-pcie", .data = PCIE_V1 },
	{ .compatible = "qcom,ipq807x-pcie", .data = PCIE_V2 },
	{ },
};

struct phy_regs {
	u32 reg_offset;
	u32 val;
};

struct ipq_pcie {
	struct pci_controller hose;
	struct fdt_resource pci_dbi;
	struct fdt_resource parf;
	struct fdt_resource elbi;
	struct fdt_resource axi_conf;
	struct fdt_resource axi_bars;
	struct fdt_resource pci_rst;
	struct fdt_resource pci_phy;

	int rst_gpio;
	int linkup;
	int version;
};

static void ipq_pcie_write_mask(uint32_t addr,
				uint32_t clear_mask, uint32_t set_mask)
{
	uint32_t val;

	val = (readl(addr) & ~clear_mask) | set_mask;
	writel(val, addr);
}

static void ipq_pcie_parf_reset(uint32_t addr, int domain, int assert)

{
	if (assert)
		ipq_pcie_write_mask(addr, 0, domain);
	else
		ipq_pcie_write_mask(addr, domain, 0);
}

void ipq_pcie_config_cfgtype(uint32_t phyaddr)
{
	uint32_t bdf, cfgtype;

	cfgtype = PCI_CFG0_RDWR;
	bdf = MSM_PCIE_DEV_CFG_ADDR;

	writel(0, phyaddr + PCIE20_PLR_IATU_VIEWPORT);

	/* Program Bdf Address */
	writel(bdf, phyaddr + PCIE20_PLR_IATU_LTAR);

	/* Write Config Request Type */
	writel(cfgtype, phyaddr + PCIE20_PLR_IATU_CTRL1);
}

int ipq_pcie_rd_conf_byte(struct  pci_controller *hose, pci_dev_t dev,
				     int offset, u8 *val)
{
	int bus = PCI_BUS (dev);
	uint32_t addr;
	uint32_t word_offset, byte_offset, mask;
	uint32_t rd_val;

	word_offset = offset & ~0x3;
	byte_offset = offset & 0x3;
	mask = (~0 >> (8 * (4 - 1))) << (8 * byte_offset);

	ipq_pcie_config_cfgtype(hose->regions[0].phys_start);
	if ((bus == local_buses[0]) || (bus == local_buses[1])) {
		addr = hose->regions[0].phys_start;
	} else {
		addr = hose->regions[1].phys_start;
	}
	rd_val = readl(addr + word_offset);
	*val = ((rd_val & mask) >> (8 * byte_offset));

	return 0;
}

int ipq_pcie_rd_conf_word(struct  pci_controller *hose, pci_dev_t dev,
				     int offset, u16 *val)
{
	int bus = PCI_BUS (dev);
	uint32_t addr;
	uint32_t word_offset, byte_offset, mask;
	uint32_t rd_val;

	word_offset = offset & ~0x3;
	byte_offset = offset & 0x3;
	mask = (~0 >> (8 * (4 - 2))) << (8 * byte_offset);

	ipq_pcie_config_cfgtype(hose->regions[0].phys_start);
	if ((bus == local_buses[0]) || (bus == local_buses[1])) {
		addr = hose->regions[0].phys_start;
	} else {
		addr = hose->regions[1].phys_start;
	}
	rd_val = readl(addr + word_offset);
	*val = ((rd_val & mask) >> (8 * byte_offset));

	return 0;
}
int ipq_pcie_rd_conf_dword(struct  pci_controller *hose, pci_dev_t dev,
				     int offset, u32 *val)
{
	int bus = PCI_BUS (dev);
	uint32_t addr;
	uint32_t word_offset, byte_offset, mask;
	uint32_t rd_val;

	word_offset = offset & ~0x3;
	byte_offset = offset & 0x3;
	mask = (~0 >> (8 * (4 - 4))) << (8 * byte_offset);

	ipq_pcie_config_cfgtype(hose->regions[0].phys_start);
	if ((bus == local_buses[0]) || (bus == local_buses[1])) {
		addr = hose->regions[0].phys_start;
	} else {
		addr = hose->regions[1].phys_start;
	}
	rd_val = readl(addr + word_offset);
	*val = ((rd_val & mask) >> (8 * byte_offset));

	return 0;
}

int ipq_pcie_wr_conf_byte(struct  pci_controller *hose, pci_dev_t dev,
				     int offset, u8 val)
{
	int bus = PCI_BUS (dev);
	uint32_t addr;
	uint32_t word_offset, byte_offset, mask;
	uint32_t rd_val, wr_val;

	word_offset = offset & ~0x3;
	byte_offset = offset & 0x3;
	mask = (~0 >> (8 * (4 - 1))) << (8 * byte_offset);

	ipq_pcie_config_cfgtype(hose->regions[0].phys_start);
	if ((bus == local_buses[0]) || (bus == local_buses[1])) {
		addr = hose->regions[0].phys_start;
	} else {
		addr = hose->regions[1].phys_start;
	}
	rd_val = readl(addr + word_offset);
	wr_val = (rd_val & ~mask) |((val << (8 * byte_offset)) & mask);
	writel(wr_val, addr + word_offset);

	return 0;
}

int ipq_pcie_wr_conf_word(struct  pci_controller *hose, pci_dev_t dev,
				     int offset, u16 val)
{
	int bus = PCI_BUS (dev);
	uint32_t addr;
	uint32_t word_offset, byte_offset, mask;
	uint32_t rd_val, wr_val;

	word_offset = offset & ~0x3;
	byte_offset = offset & 0x3;
	mask = (~0 >> (8 * (4 - 2))) << (8 * byte_offset);

	ipq_pcie_config_cfgtype(hose->regions[0].phys_start);
	if ((bus == local_buses[0]) || (bus == local_buses[1])) {
		addr = hose->regions[0].phys_start;
	} else {
		addr = hose->regions[1].phys_start;
	}
	rd_val = readl(addr + word_offset);
	wr_val = (rd_val & ~mask) |((val << (8 * byte_offset)) & mask);
	writel(wr_val, addr + word_offset);

	return 0;
}

int ipq_pcie_wr_conf_dword(struct  pci_controller *hose, pci_dev_t dev,
				     int offset, u32 val)
{
	int bus = PCI_BUS (dev);
	uint32_t addr;
	uint32_t word_offset, byte_offset, mask;
	uint32_t rd_val, wr_val;

	word_offset = offset & ~0x3;
	byte_offset = offset & 0x3;
	mask = (~0 >> (8 * (4 - 4))) << (8 * byte_offset);

	ipq_pcie_config_cfgtype(hose->regions[0].phys_start);
	if ((bus == local_buses[0]) || (bus == local_buses[1])) {
		addr = hose->regions[0].phys_start;
	} else {
		addr = hose->regions[1].phys_start;
	}
	rd_val = readl(addr + word_offset);
	wr_val = (rd_val & ~mask) |((val << (8 * byte_offset)) & mask);
	writel(wr_val, addr + word_offset);

	return 0;
}

static void ipq_pcie_config_controller(struct ipq_pcie *pcie)
{

	/*
	 * program and enable address translation region 0 (device config
	 * address space); region type config;
	 * axi config address range to device config address range
	 */
	writel(0, pcie->pci_dbi.start + PCIE20_PLR_IATU_VIEWPORT);

	writel(4, pcie->pci_dbi.start + PCIE20_PLR_IATU_CTRL1);
	writel((1 << 31), pcie->pci_dbi.start + PCIE20_PLR_IATU_CTRL2);
	writel(pcie->axi_conf.start , pcie->pci_dbi.start + PCIE20_PLR_IATU_LBAR);
	writel(0, pcie->pci_dbi.start + PCIE20_PLR_IATU_UBAR);
	writel((pcie->axi_conf.start + pcie->axi_conf.end - 1),
				pcie->pci_dbi.start + PCIE20_PLR_IATU_LAR);
	writel(MSM_PCIE_DEV_CFG_ADDR,
				pcie->pci_dbi.start + PCIE20_PLR_IATU_LTAR);
	writel(0, pcie->pci_dbi.start + PCIE20_PLR_IATU_UTAR);

	/*
	 * program and enable address translation region 2 (device resource
	 * address space); region type memory;
	 * axi device bar address range to device bar address range
	 */
	writel(2, pcie->pci_dbi.start + PCIE20_PLR_IATU_VIEWPORT);

	writel(0, pcie->pci_dbi.start + PCIE20_PLR_IATU_CTRL1);
	writel((1 << 31), pcie->pci_dbi.start + PCIE20_PLR_IATU_CTRL2);
	writel(pcie->axi_bars.start, pcie->pci_dbi.start + PCIE20_PLR_IATU_LBAR);
	writel(0, pcie->pci_dbi.start + PCIE20_PLR_IATU_UBAR);
	writel((pcie->axi_bars.start + pcie->axi_bars.end
		- pcie->axi_conf.end - 1), pcie->pci_dbi.start+ PCIE20_PLR_IATU_LAR);
	writel(pcie->axi_bars.start, pcie->pci_dbi.start + PCIE20_PLR_IATU_LTAR);
	writel(0, pcie->pci_dbi.start + PCIE20_PLR_IATU_UTAR);

	/* 1K PCIE buffer setting */
	writel(0x3, pcie->pci_dbi.start + PCIE20_AXI_MSTR_RESP_COMP_CTRL0);
	writel(0x1, pcie->pci_dbi.start + PCIE20_AXI_MSTR_RESP_COMP_CTRL1);
}

void pcie_linkup(struct ipq_pcie *pcie)
{
	int j, val;

	if (pcie->version != PCIE_V2)
	{
		writel(SLV_ADDR_SPACE_SZ, pcie->parf.start + PARF_SLV_ADDR_SPACE_SIZE);
		mdelay(100);
	}

	writel(0x0, pcie->pci_dbi.start + PCIE_0_PORT_FORCE_REG);
	val = (L1_ENTRANCE_LATENCY(3) |
		L0_ENTRANCE_LATENCY(3) |
		COMMON_CLK_N_FTS(128) |
		ACK_N_FTS(128));
	writel(val, pcie->pci_dbi.start + PCIE_0_ACK_F_ASPM_CTRL_REG);

	val = (FAST_TRAINING_SEQ(128) |
		NUM_OF_LANES(2) |
		DIRECT_SPEED_CHANGE);
	writel(val, pcie->pci_dbi.start + PCIE_0_GEN2_CTRL_REG);
	writel(PCI_TYPE0_BUS_MASTER_EN,
		pcie->pci_dbi.start + PCIE_0_TYPE0_STATUS_COMMAND_REG_1);

	writel(DBI_RO_WR_EN, pcie->pci_dbi.start + PCIE_0_MISC_CONTROL_1_REG);
	writel(0x0002FD7F, pcie->pci_dbi.start + 0x84);

	val = (PCIE_CAP_ASPM_OPT_COMPLIANCE |
		PCIE_CAP_LINK_BW_NOT_CAP |
		PCIE_CAP_DLL_ACTIVE_REP_CAP |
		PCIE_CAP_L1_EXIT_LATENCY(4) |
		PCIE_CAP_L0S_EXIT_LATENCY(4) |
		PCIE_CAP_MAX_LINK_WIDTH(1) |
		PCIE_CAP_MAX_LINK_SPEED(1));
	writel(val, pcie->pci_dbi.start + PCIE_0_LINK_CAPABILITIES_REG);

	writel(PCIE_CAP_CPL_TIMEOUT_DISABLE,
		pcie->pci_dbi.start + PCIE_0_DEVICE_CONTROL2_DEVICE_STATUS2_REG);

	writel(0x10110008, pcie->pci_dbi.start + PCIE_0_TYPE0_LINK_CONTROL_LINK_STATUS_REG_1);

	writel(LTSSM_EN, pcie->parf.start + PCIE_0_PCIE20_PARF_LTSSM);

	mdelay(200);

	for (j = 0; j < 400; j++) {
		val = readl(pcie->pci_dbi.start + PCIE_0_TYPE0_LINK_CONTROL_LINK_STATUS_REG_1);
		if (val & (1 << 29)) {
			printf("PCI Link Intialized\n");
			pcie->linkup = 1;
			break;
		}
		udelay(100);
	}
	ipq_pcie_config_controller(pcie);
}

void pcie_v0_linkup(struct ipq_pcie *pcie, int id)
{
	int j;
	uint32_t val;
	/* assert PCIe PARF reset while powering the core */
	ipq_pcie_parf_reset(pcie->pci_rst.start, BIT(6), 0);

	ipq_pcie_parf_reset(pcie->pci_rst.start, BIT(2), 1);
	board_pcie_clock_init(id);
	/*
	 * de-assert PCIe PARF reset;
	 * wait 1us before accessing PARF registers
	 */
	ipq_pcie_parf_reset(pcie->pci_rst.start, BIT(2), 0);
	udelay(1);

	/* enable PCIe clocks and resets */
	val = (readl(pcie->parf.start + PCIE20_PARF_PHY_CTRL) & ~BIT(0));
	writel(val, pcie->parf.start + PCIE20_PARF_PHY_CTRL);

	ipq_pcie_write_mask(pcie->parf.start + PCIE20_PARF_PHY_CTRL,
				PHY_CTRL_PHY_TX0_TERM_OFFSET_MASK,
				PHY_CTRL_PHY_TX0_TERM_OFFSET(0));

	/* PARF programming */
	writel(PCIE20_PARF_PCS_DEEMPH_TX_DEEMPH_GEN1(0x18) |
			PCIE20_PARF_PCS_DEEMPH_TX_DEEMPH_GEN2_3_5DB(0x18) |
			PCIE20_PARF_PCS_DEEMPH_TX_DEEMPH_GEN2_6DB(0x22),
			pcie->parf.start + PCIE20_PARF_PCS_DEEMPH);

	writel(PCIE20_PARF_PCS_SWING_TX_SWING_FULL(0x78) |
			PCIE20_PARF_PCS_SWING_TX_SWING_LOW(0x78),
			pcie->parf.start + PCIE20_PARF_PCS_SWING);

	writel((4<<24), pcie->parf.start + PCIE20_PARF_CONFIG_BITS);

	ipq_pcie_write_mask(pcie->parf.start + PCIE20_PARF_PHY_REFCLK,
				REF_USE_PAD, REF_SSP_EN);

	/* enable access to PCIe slave port on system fabric */
	if (id == 0) {
		writel(BIT(4), PCIE_SFAB_AXI_S5_FCLK_CTL);
	}

	udelay(1);
	/* de-assert PICe PHY, Core, POR and AXI clk domain resets */
	ipq_pcie_parf_reset(pcie->pci_rst.start, BIT(5), 0);
	ipq_pcie_parf_reset(pcie->pci_rst.start, BIT(4), 0);
	ipq_pcie_parf_reset(pcie->pci_rst.start, BIT(3), 0);
	ipq_pcie_parf_reset(pcie->pci_rst.start, BIT(0), 0);

	/* enable link training */
	ipq_pcie_write_mask( pcie->elbi.start + PCIE20_ELBI_SYS_CTRL, 0,
			BIT(0));
	udelay(500);

	for (j = 0; j < 10; j++) {
		val = readl(pcie->pci_dbi.start +
				PCIE_0_TYPE0_LINK_CONTROL_LINK_STATUS_REG_1);
		if (val & BIT(29)) {
			printf("PCI%d Link Intialized\n", id);
			pcie->linkup = 1;
			break;
		}
		udelay(10000);
	}
	ipq_pcie_config_controller(pcie);

}

static int ipq_pcie_parse_dt(const void *fdt, int id,
			       struct ipq_pcie *pcie)
{
	int err, rst_gpio, node;
	char name[16];

	snprintf(name, sizeof(name), "pci%d", id);
	node = fdt_path_offset(fdt, name);
	if (node < 0) {
		printf("PCI%d is not defined in the device tree\n", id);
		return node;
	}

	err = fdt_get_named_resource(fdt, node, "reg", "reg-names", "pci_dbi",
				     &pcie->pci_dbi);
	if (err < 0) {
		error("resource \"pads\" not found");
		return err;
	}

	err = fdt_get_named_resource(fdt, node, "reg", "reg-names", "parf",
				     &pcie->parf);
	if (err < 0) {
		error("resource \"afi\" not found");
		return err;
	}

	err = fdt_get_named_resource(fdt, node, "reg", "reg-names", "elbi",
				     &pcie->elbi);
	if (err < 0) {
		error("resource \"cs\" not found");
		return err;
	}

	err = fdt_get_named_resource(fdt, node, "reg", "reg-names", "axi_bars",
				     &pcie->axi_bars);
	if (err < 0) {
		error("resource \"cs\" not found");
		return err;
	}

	err = fdt_get_named_resource(fdt, node, "reg", "reg-names", "axi_conf",
				     &pcie->axi_conf);
	if (err < 0) {
		error("resource \"cs\" not found");
		return err;
	}

	err = fdt_get_named_resource(fdt, node, "reg", "reg-names", "pci_rst",
				     &pcie->pci_rst);
	if (err < 0) {
		error("resource \"cs\" not found");
		return err;
	}

	if(pcie->version == PCIE_V2) {
		err = fdt_get_named_resource(fdt, node, "reg", "reg-names", "pci_phy",
					     &pcie->pci_phy);
		if (err < 0) {
			error("resource \"cs\" not found");
			return err;
		}
	}
	rst_gpio = fdtdec_get_int(fdt, node, "perst_gpio", 0);
	if (rst_gpio <= 0) {
		debug("PCI: Can't get perst_gpio\n");
		return -1;
	}
	pcie->rst_gpio = rst_gpio;

	return 0;
}

void pci_controller_init_v1(struct ipq_pcie *pcie)
{
	uint32_t val;

	/* Assert cc_pcie20_mstr_axi_ares */
	val = readl(pcie->pci_rst.start);
	val |= PCIE_RST_CTRL_AXI_M_ARES;
	writel(val, pcie->pci_rst.start);

	/* Assert cc_pcie20_slv_axi_ares */
	val = readl(pcie->pci_rst.start);
	val |= PCIE_RST_CTRL_AXI_S_ARES;
	writel(val, pcie->pci_rst.start);

	/* Assert cc_pcie20_core_ares */
	writel(PCIE_RST_CTRL_PIPE_ARES, pcie->pci_rst.start);

	/* Assert cc_pcie20_core_sticky_area */
	val = readl(pcie->pci_rst.start);
	val |= PCIE_RST_CTRL_PIPE_STICKY_ARES;
	writel(val, pcie->pci_rst.start);

	/* Assert cc_pcie20_phy_ahb_ares */
	val = readl(pcie->pci_rst.start);
	val |= PCIE_RST_CTRL_PIPE_PHY_AHB_ARES;
	writel(val, pcie->pci_rst.start);

	/* Assert cc_pcie20_mstr_sticky_ares */
	val = readl(pcie->pci_rst.start);
	val |= PCIE_RST_CTRL_AXI_M_STICKY_ARES;
	writel(val, pcie->pci_rst.start);

	gpio_set_value(pcie->rst_gpio, GPIO_OUT_LOW);

	/* Assert cc_pcie20_ahb_ares;  */
	val = readl(pcie->pci_rst.start);
	val |= PCIE_RST_CTRL_AHB_ARES;
	writel(val, pcie->pci_rst.start);

	/* DeAssert cc_pcie20_ahb_ares */
	val = readl(pcie->pci_rst.start);
	val &= ~(PCIE_RST_CTRL_PIPE_PHY_AHB_ARES);
	writel(val, pcie->pci_rst.start);

	/* DeAssert cc_pcie20_pciephy_phy_ares*/
	val = readl(pcie->pci_rst.start);
	val &= ~(PCIE_RST_CTRL_PIPE_ARES);
	writel(val, pcie->pci_rst.start);

	/* DeAssert cc_pcie20_core_sticky_ares */
	val = readl(pcie->pci_rst.start);
	val &= ~(PCIE_RST_CTRL_PIPE_STICKY_ARES);
	writel(val, pcie->pci_rst.start);

	mdelay(5);

	gpio_set_value(pcie->rst_gpio, GPIO_OUT_HIGH);

	/* DeAssert cc_pcie20_mstr_axi_ares */
	val = readl(pcie->pci_rst.start);
	val &= ~(PCIE_RST_CTRL_AXI_M_ARES);
	writel(val, pcie->pci_rst.start);

	/* DeAssert cc_pcie20_mstr_axi_ares */
	val = readl(pcie->pci_rst.start);
	val &= ~(PCIE_RST_CTRL_AXI_M_STICKY_ARES);
	writel(val, pcie->pci_rst.start);

	/* DeAssert cc_pcie20_slv_axi_ares */
	val = readl(pcie->pci_rst.start);
	val &= ~(PCIE_RST_CTRL_AXI_S_ARES);
	writel(val, pcie->pci_rst.start);

	/* DeAssert cc_pcie20_phy_ahb_ares  */
	val = readl(pcie->pci_rst.start);
	val &= ~(PCIE_RST_CTRL_AHB_ARES);
	writel(val, pcie->pci_rst.start);
}

static const struct phy_regs pcie_phy_regs[] = {
	{ PCIE_USB3_PCS_POWER_DOWN_CONTROL,			0x00000003 },
	{ QSERDES_COM_BIAS_EN_CLKBUFLR_EN,			0x00000018 },
	{ QSERDES_COM_CLK_ENABLE1,				0x00000010 },
	{ QSERDES_COM_BG_TRIM,					0x0000000f },
	{ QSERDES_COM_LOCK_CMP_EN,				0x00000001 },
	{ QSERDES_COM_VCO_TUNE_MAP,				0x00000000 },
	{ QSERDES_COM_VCO_TUNE_TIMER1,				0x000000ff },
	{ QSERDES_COM_VCO_TUNE_TIMER2,				0x0000001f },
	{ QSERDES_COM_CMN_CONFIG,				0x00000006 },
	{ QSERDES_COM_PLL_IVCO,					0x0000000f },
	{ QSERDES_COM_HSCLK_SEL,				0x00000000 },
	{ QSERDES_COM_SVS_MODE_CLK_SEL,				0x00000001 },
	{ QSERDES_COM_CORE_CLK_EN,				0x00000020 },
	{ QSERDES_COM_CORECLK_DIV,				0x0000000a },
	{ QSERDES_COM_RESETSM_CNTRL,				0x00000020 },
	{ QSERDES_COM_BG_TIMER,					0x00000009 },
	{ QSERDES_COM_SYSCLK_EN_SEL,				0x0000000a },
	{ QSERDES_COM_DEC_START_MODE0,				0x00000082 },
	{ QSERDES_COM_DIV_FRAC_START3_MODE0,			0x00000003 },
	{ QSERDES_COM_DIV_FRAC_START2_MODE0,			0x00000055 },
	{ QSERDES_COM_DIV_FRAC_START1_MODE0,			0x00000055 },
	{ QSERDES_COM_LOCK_CMP3_MODE0,				0x00000000 },
	{ QSERDES_COM_LOCK_CMP2_MODE0,				0x0000000D },
	{ QSERDES_COM_LOCK_CMP1_MODE0,				0x00000D04 },
	{ QSERDES_COM_CLK_SELECT,				0x00000033 },
	{ QSERDES_COM_SYS_CLK_CTRL,				0x00000002 },
	{ QSERDES_COM_SYSCLK_BUF_ENABLE,			0x0000001f },
	{ QSERDES_COM_CP_CTRL_MODE0,				0x0000000b },
	{ QSERDES_COM_PLL_RCTRL_MODE0,				0x00000016 },
	{ QSERDES_COM_PLL_CCTRL_MODE0,				0x00000028 },
	{ QSERDES_COM_INTEGLOOP_GAIN1_MODE0,			0x00000000 },
	{ QSERDES_COM_INTEGLOOP_GAIN0_MODE0,			0x00000080 },
	{ QSERDES_COM_BIAS_EN_CTRL_BY_PSM,			0x00000001 },
	{ QSERDES_COM_VCO_TUNE_CTRL,				0x0000000a },
	{ QSERDES_COM_SSC_EN_CENTER,				0x00000001 },
	{ QSERDES_COM_SSC_PER1,					0x00000031 },
	{ QSERDES_COM_SSC_PER2,					0x00000001 },
	{ QSERDES_COM_SSC_ADJ_PER1,				0x00000002 },
	{ QSERDES_COM_SSC_ADJ_PER2,				0x00000000 },
	{ QSERDES_COM_SSC_STEP_SIZE1,				0x0000002f },
	{ QSERDES_COM_SSC_STEP_SIZE2,				0x00000019 },
	{ QSERDES_TX_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN,		0x00000045 },
	{ QSERDES_TX_LANE_MODE,					0x00000006 },
	{ QSERDES_TX_RES_CODE_LANE_OFFSET,			0x00000002 },
	{ QSERDES_TX_RCV_DETECT_LVL_2,				0x00000012 },
	{ QSERDES_RX_SIGDET_ENABLES,				0x0000001c },
	{ QSERDES_RX_SIGDET_DEGLITCH_CNTRL,			0x00000014 },
	{ QSERDES_RX_RX_EQU_ADAPTOR_CNTRL2,			0x00000001 },
	{ QSERDES_RX_RX_EQU_ADAPTOR_CNTRL3,			0x00000000 },
	{ QSERDES_RX_RX_EQU_ADAPTOR_CNTRL4,			0x000000db },
	{ QSERDES_RX_UCDR_SO_SATURATION_AND_ENABLE,		0x0000004b },
	{ QSERDES_RX_UCDR_SO_GAIN,				0x00000004 },
	{ QSERDES_RX_UCDR_SO_GAIN_HALF,				0x00000004 },
	{ QSERDES_COM_CLK_EP_DIV,				0x00000019 },
	{ PCIE_USB3_PCS_ENDPOINT_REFCLK_DRIVE,			0x00000004 },
	{ PCIE_USB3_PCS_OSC_DTCT_ACTIONS,			0x00000000 },
	{ PCIE_USB3_PCS_PWRUP_RESET_DLY_TIME_AUXCLK,		0x00000040 },
	{ PCIE_USB3_PCS_L1SS_WAKEUP_DLY_TIME_AUXCLK_MSB,	0x00000000 },
	{ PCIE_USB3_PCS_L1SS_WAKEUP_DLY_TIME_AUXCLK_LSB,	0x00000040 },
	{ PCIE_USB3_PCS_PLL_LOCK_CHK_DLY_TIME_AUXCLK_LSB,	0x00000000 },
	{ PCIE_USB3_PCS_LP_WAKEUP_DLY_TIME_AUXCLK,		0x00000040 },
	{ PCIE_USB3_PCS_PLL_LOCK_CHK_DLY_TIME,			0x00000073 },
	{ QSERDES_RX_SIGDET_CNTRL,				0x00000007 },
	{ PCIE_USB3_PCS_RX_SIGDET_LVL,				0x00000099 },
	{ PCIE_USB3_PCS_TXDEEMPH_M6DB_V0,			0x00000015 },
	{ PCIE_USB3_PCS_TXDEEMPH_M3P5DB_V0,			0x0000000e },
	{ PCIE_USB3_PCS_SW_RESET,				0x00000000 },
	{ PCIE_USB3_PCS_START_CONTROL,				0x00000003 },
};

void pcie_phy_init(struct ipq_pcie *pcie)
{
	int i;
	const struct phy_regs *regs = pcie_phy_regs;

	if (!phy_initialised) {
		writel(0x10000000, pcie->parf.start + 0x358);
		writel(0x10000000, pcie->parf.start + 0x8358);
		mdelay(100);
		phy_initialised = 1;
	}
	for (i = 0; i < ARRAY_SIZE(pcie_phy_regs); i++)
		writel(regs[i].val, pcie->pci_phy.start + regs[i].reg_offset);

}

static int pci_ipq_ofdata_to_platdata(int id, struct ipq_pcie *pcie)
{

	if (ipq_pcie_parse_dt(gd->fdt_blob, id, pcie))
		return -EINVAL;

	board_pci_init(id);
	switch(pcie->version) {
		case PCIE_V0:
			pcie_v0_linkup(pcie, id);
			break;
		case PCIE_V1:
			pci_controller_init_v1(pcie);
			pcie_linkup(pcie);
			break;
		case PCIE_V2:
			pcie_phy_init(pcie);
			pcie_linkup(pcie);
			break;
		default:
			break;
	}

	return 0;
}

__weak void ipq_wifi_pci_power_enable()
{
	return;
}

void pci_init_board (void)
{
	struct ipq_pcie *pcie;
	int i, bus = 0, ret;
	const struct udevice_id *of_match = pcie_ver_ids;

	pcie = malloc(sizeof(*pcie));
	if (pcie == NULL) {
		printf("PCI: Init failed. Could't allocate memory\n");
		return;
	}

	while (of_match->compatible) {
		ret = fdt_node_offset_by_compatible(gd->fdt_blob, 0,
						of_match->compatible);
		if (ret < 0) {
			of_match++;
			continue;
		}
		pcie->version = of_match->data;
		break;
	}

	ipq_wifi_pci_power_enable();
	for (i = 0; i < PCI_MAX_DEVICES; i++) {
		pcie->linkup = 0;
		pci_ipq_ofdata_to_platdata(i, pcie);
		if (pcie->linkup) {
			pci_hose[i].first_busno = bus;
			pci_hose[i].last_busno = 0xff;
			local_buses[0] = pci_hose[i].first_busno;

			/* PCI memory space */
			pci_set_region (pci_hose[i].regions + 0,
					pcie->pci_dbi.start,
					pcie->pci_dbi.start,
					PCIE20_SIZE, PCI_REGION_MEM);

			/* PCI device confgiuration  space */
			pci_set_region (pci_hose[i].regions + 1,
					pcie->axi_conf.start,
					pcie->axi_conf.start,
				(PCIE_AXI_CONF_SIZE - 1), PCI_REGION_MEM);

			pci_hose[i].region_count = 2;
			pci_register_hose (&pci_hose[i]);
			pci_set_ops (&pci_hose[i],
				ipq_pcie_rd_conf_byte,
				ipq_pcie_rd_conf_word,
				ipq_pcie_rd_conf_dword,
				ipq_pcie_wr_conf_byte,
				ipq_pcie_wr_conf_word,
				ipq_pcie_wr_conf_dword);

			pci_hose[i].last_busno = pci_hose[i].first_busno + 1;
			bus = pci_hose[i].last_busno + 1;
		}
	}
}
