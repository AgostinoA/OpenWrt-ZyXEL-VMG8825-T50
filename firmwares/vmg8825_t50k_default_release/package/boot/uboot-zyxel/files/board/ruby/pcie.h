/*
 * (C) Copyright 2010 Quantenna Communications Inc.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */


#define PCIE_REGION_BASE		0xB0000000
#define PCIE_REGION_END			0xCFFFFFFF

#define PCIE_CFG_MSI			1
#define PCIE_CFG_BAR64			0

#define PCIE_ROM_MASK_ADDR		0xE9001030

#define	PCIE_BAR_32			0
#define	PCIE_BAR_64			(RUBY_BIT(2))
#define	PCIE_BAR_PREFETCH		(RUBY_BIT(3))
#define	PCIE_BAR_CFG(bar64)		(PCIE_BAR_PREFETCH | ((bar64) ? PCIE_BAR_64 : PCIE_BAR_32))

#define	PCIE_BAR_SYSCTL			0
#define	PCIE_BAR_SYSCTL_LEN		0xFFFF
#define	PCIE_BAR_SYSCTL_LO		0xE0000000
#define	PCIE_BAR_SYSCTL_HI		0x00000000

#define	PCIE_BAR_SHMEM			2
#define	PCIE_BAR_SHMEM_LEN		(RUBY_PCIE_BDA_SIZE - 1)
#define	PCIE_BAR_SHMEM_LO		RUBY_PCIE_BDA_ADDR
#define	PCIE_BAR_SHMEM_HI		0x00000000


#define	PCIE_LINKUP		(RUBY_BIT(8)|RUBY_BIT(9))
#define PCIE_DEFAULT_CFG0		(0xff3c9410)

/* ATU defines */

#define PCIE_ATU_MEMREGION		0x00000000
#define PCIE_ATU_BAR_MATCH		0xC0000000
#define PCIE_ATU_BAR_MIN_SIZE		0x00010000 /* 64k */


#define	PCIE_ATU_BAR_EN(n)		(((n) << 8) | PCIE_ATU_BAR_MATCH)

/* Shared memory ATU BAR setup */
#define PCIE_SHMEM_REGION		RUBY_PCIE_ATU_IB_REGION(0)
#define PCIE_SHMEM_ENABLE		(PCIE_ATU_BAR_EN(PCIE_BAR_SHMEM))

/* Syscfg ATU BAR setup */
#define PCIE_SYSCTL_REGION		RUBY_PCIE_ATU_IB_REGION(1)
#define PCIE_SYSCTL_ENABLE		(PCIE_ATU_BAR_EN(PCIE_BAR_SYSCTL))


/* Size of MSI region */
#define PCIE_MSIMEM_SIZE		PCIE_ATU_BAR_MIN_SIZE
#define PCIE_MSIMEM_SIZE_MASK		(PCIE_ATU_BAR_MIN_SIZE - 1)

/* Outbound Host Memoory translation setup */
#define PCIE_HOSTMEM_EP_START		PCIE_REGION_BASE
#define PCIE_HOSTMEM_EP_END		(PCIE_REGION_END - PCIE_MSIMEM_SIZE)
#define PCIE_HOSTMEM_DMA_MASK		(PCIE_HOSTMEM_EP_END - PCIE_HOSTMEM_EP_START)
#define PCIE_HOSTMEM_REGION		(RUBY_PCIE_ATU_OB_REGION(1))
#define PCIE_HOSTMEM_EP_START_LO	PCIE_REGION_BASE
#define PCIE_HOSTMEM_EP_START_HI	0x00000000
#define PCIE_HOSTMEM_START_LO		0x00000000
#define PCIE_HOSTMEM_START_HI		0x00000000
#define PCIE_HOSTMEM_REGION_ENABLE	RUBY_PCIE_ATU_OB_ENABLE


/* Outbound MSI ATU setup */
/* MSI region is the upper 64kbytes of the PCIE slave area */

#define PCIE_MSI_BASE			0xE9000050
#define PCIE_MSI_CAP			(PCIE_MSI_BASE + 0x0)
#define PCIE_MSI_LOW_ADDR		(PCIE_MSI_BASE + 0x4)
#define PCIE_MSI_HIG_ADDR		(PCIE_MSI_BASE + 0x8)
#define PCIE_MSI_REGION			(RUBY_PCIE_ATU_OB_REGION(0))
#define PCIE_MSI_REGION_ENABLE		RUBY_PCIE_ATU_OB_ENABLE
#define MSI_EN				RUBY_BIT(0)
#define MSI_64_EN			RUBY_BIT(7)
#define PCIE_MSI_EP_END			PCIE_REGION_END
#define PCIE_MSI_EP_START_LO		(PCIE_REGION_END - PCIE_MSIMEM_SIZE_MASK)
#define PCIE_MSI_EP_START_HI		0x00000000
#define PCIE_MSI_ADDR_OFFSET(a)		((a) & 0xFFFF)
#define PCIE_MSI_ADDR_ALIGN(a)		((a) & (~0xFFFF))



/* Default pcie lzma load addr */
#define PCIE_FW_LZMA_LOAD		QTNBOOT_COPY_DRAM_ADDR

/* pcie boot control area */
#define PCIE_BDA			(0x80000000 + RUBY_PCIE_BDA_ADDR)
#define PCIE_BDA_LEN			RUBY_PCIE_BDA_SIZE

/* pcie Root Complex defines */
#define SYS_RST_PCIE			(0x00002000)
#define SYS_RST_IOSS			(0x00000020)
#define PCIE_CFG0_DEFAULT_VALUE		(0xff3c9400)
#define PCIE_CFG_RC_MODE		(0x14)

#define PCIE_IO_EN			RUBY_BIT(0)
#define PCIE_MEM_EN			RUBY_BIT(1)
#define PCIE_BUS_MASTER_EN		RUBY_BIT(2)
#define BUS_SCAN_TRY_MAX		1000
#define PCIE_DEV_LINKUP_MASK		0x700

#define PCIE_MSI_ENV			"MSI"
void board_pcie_init(size_t memsz, uint32_t flags );

