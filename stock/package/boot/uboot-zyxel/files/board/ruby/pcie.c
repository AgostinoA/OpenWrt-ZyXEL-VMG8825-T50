/*
 * (C) Copyright 2011 Quantenna Communications Inc.
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

/*
 * Header file which describes Ruby PCI Express specific functions.
 */


#include <common.h>
#include <command.h>
#include <asm/arch/platform.h>
#include <environment.h>
#include "ruby.h"
#include "ruby_board_cfg.h"
#include "ruby_pcie_bda.h"
#include "pcie.h"
#include "board_cfg.h"


static inline void arc_write_uncached_32(volatile void *ptr, uint32_t data)
{
	uint32_t start = (unsigned long)ptr;
	invalidate_dcache_range(start, start + sizeof(uint32_t));
	_arc_write_uncached_32(ptr, data);
}

/*
 * for End Point mode
 * Allocate and setup BAR mapping for shared memory
 */
static int32_t setup_atu_shmem(void)
{
	uint32_t val = 0x0;

	/* Select shared mem region */
	writel(PCIE_SHMEM_REGION, RUBY_PCIE_ATU_VIEW);

	/* Bar mapped area in EP */
	writel(PCIE_BAR_SHMEM_LO, RUBY_PCIE_ATU_TARGET_LO);
	writel(PCIE_BAR_SHMEM_HI, RUBY_PCIE_ATU_TARGET_HI);

	/* Set BAR size to EP memory */
	writel(PCIE_BAR_SHMEM_LEN, RUBY_PCIE_ATU_BASE_LIMIT);

	/* Define region of type memory */
	writel(PCIE_ATU_MEMREGION, RUBY_PCIE_ATU_CTL1);

	/* Enable BAR mapped region */
	writel(PCIE_SHMEM_ENABLE, RUBY_PCIE_ATU_CTL2);
	val = readl(RUBY_PCIE_ATU_CTL2);
	printf("PCIe Shmem BAR%u=0x%x Len:%uk\n", PCIE_BAR_SHMEM,
		PCIE_BAR_SHMEM_LO, (PCIE_BAR_SHMEM_LEN >> 10) + 1);

	return 0;
}

/*
 * for End Point mode
 * Allocate and setup BAR mapping for syscontrol
 */
static int32_t setup_atu_sysctl(void)
{
	uint32_t val = 0x0;

	/* Select shared mem region */
	writel(PCIE_SYSCTL_REGION, RUBY_PCIE_ATU_VIEW);

	/* Bar mapped area in EP */
	writel(PCIE_BAR_SYSCTL_LO, RUBY_PCIE_ATU_TARGET_LO);
	writel(PCIE_BAR_SYSCTL_HI, RUBY_PCIE_ATU_TARGET_HI);

	/* Set size */
	writel(PCIE_BAR_SYSCTL_LEN, RUBY_PCIE_ATU_BASE_LIMIT);

	/* Define region of type memory */
	writel(PCIE_ATU_MEMREGION, RUBY_PCIE_ATU_CTL1);

	/* Enable BAR mapped region */
	writel(PCIE_SYSCTL_ENABLE, RUBY_PCIE_ATU_CTL2);
	val = readl(RUBY_PCIE_ATU_CTL2);

	printf("PCIe Sysctl BAR%u=0x%x Len:%uk\n", PCIE_BAR_SYSCTL,
		PCIE_BAR_SYSCTL_LO, ( PCIE_BAR_SYSCTL_LEN >> 10) + 1);

	return 0;
}

/*
 * for End Point mode *
 * map the host memory to target
 */
static int32_t setup_atu_host(uint32_t addr_mask)
{
	uint32_t val = 0x0;

	/* Select shared mem region */
	writel(PCIE_HOSTMEM_REGION, RUBY_PCIE_ATU_VIEW);

	/* Memory mapped area in EP )*/
	writel(PCIE_HOSTMEM_EP_START_LO, RUBY_PCIE_ATU_BASE_LO);
	writel(PCIE_HOSTMEM_EP_START_HI, RUBY_PCIE_ATU_BASE_HI);

	/* Memory mapped area in Host*/
	writel(PCIE_HOSTMEM_START_LO, RUBY_PCIE_ATU_TARGET_LO);
	writel(PCIE_HOSTMEM_START_HI, RUBY_PCIE_ATU_TARGET_HI);

	/* Set size */
	writel(PCIE_HOSTMEM_EP_START_LO + addr_mask, RUBY_PCIE_ATU_BASE_LIMIT);

	/* Define region of type memory */
	writel(PCIE_ATU_MEMREGION, RUBY_PCIE_ATU_CTL1);

	/* Enable BAR mapped region */
	writel(PCIE_HOSTMEM_REGION_ENABLE, RUBY_PCIE_ATU_CTL2);
	val = readl(RUBY_PCIE_ATU_CTL2);
	printf("%u:Mem: EP(0x%x->0x%x) Host(0x%x->0x%x)\n", PCIE_HOSTMEM_REGION,
		PCIE_HOSTMEM_EP_START_LO,PCIE_HOSTMEM_EP_START_LO + addr_mask,
		PCIE_HOSTMEM_START_LO,PCIE_HOSTMEM_START_LO + addr_mask);

	return 0;
}


/*
 * for End Point mode
 * Setup 64KB region ATU for target to access host msi register
 */
static int setup_atu_msi(volatile ruby_pcie_bda_t *bda, uint32_t end_addr)
{
	uint16_t flag = 0;
	uint32_t msi_addr = 0x0;
	uint32_t msi_addr_up = 0x0;
	uint32_t val = 0x0;
	uint32_t msi64;

	flag = readl(PCIE_MSI_CAP) >> 16;
	msi_addr = readl(PCIE_MSI_LOW_ADDR);
	msi64 = (flag & MSI_64_EN);

	/* Exit if MSI is not enabled */
	if (!(flag & MSI_EN)) {
			return 1;
	}
	/* If address range of of MSI data area is within primary ATU region, we can use one ATU for both  */
	if ((msi_addr + 2) <= end_addr)
	{
		/* Setup EP MSI address */
		arc_write_uncached_32(&bda->bda_msi_addr,PCIE_MSI_EP_START_LO + PCIE_MSI_ADDR_OFFSET(msi_addr));
		return 1;
	}
	/* Enable ATU viewport */
	writel(PCIE_MSI_REGION, RUBY_PCIE_ATU_VIEW);

	/* mapped region area in EP */
	writel(PCIE_MSI_EP_START_LO, RUBY_PCIE_ATU_BASE_LO);
	writel(PCIE_MSI_EP_START_HI, RUBY_PCIE_ATU_BASE_HI);

	writel(PCIE_MSI_EP_END, RUBY_PCIE_ATU_BASE_LIMIT);

	/* Set host side msi addr */
	writel(PCIE_MSI_ADDR_ALIGN(msi_addr), RUBY_PCIE_ATU_TARGET_LO);
	arc_write_uncached_32(&bda->bda_flags,PCIE_BDA_MSI| arc_read_uncached_32(&bda->bda_flags));
	if (msi64) {
		msi_addr_up = readl(PCIE_MSI_HIG_ADDR);
		writel(msi_addr_up, RUBY_PCIE_ATU_TARGET_HI);
	} else {
		writel(0x00000000, RUBY_PCIE_ATU_TARGET_HI);
	}

	/* Setup EP MSI address */
	arc_write_uncached_32(&bda->bda_msi_addr,PCIE_MSI_EP_START_LO + PCIE_MSI_ADDR_OFFSET(msi_addr));

	/* Define region of type memory */
	writel(PCIE_ATU_MEMREGION, RUBY_PCIE_ATU_CTL1);

	/* Enable region */
	writel(PCIE_MSI_REGION_ENABLE, RUBY_PCIE_ATU_CTL2);
	val = readl(RUBY_PCIE_ATU_CTL2);

	printf("%u:MSI%s: Host:0x%x%x EP:0x%x\n",PCIE_MSI_REGION, (msi64) ? "64" : "",
		msi_addr_up, msi_addr, bda->bda_msi_addr);

	return 0;
}

/*
 * for End Point mode
 */
static void setup_atu_outbound(volatile ruby_pcie_bda_t *bda)
{
	uint32_t dma_mask = 0;
	uint32_t region_size_mask = (PCIE_REGION_END - PCIE_REGION_BASE);
	if (setup_atu_msi(bda, region_size_mask)){
		dma_mask = region_size_mask ;
	} else {
		dma_mask = region_size_mask - PCIE_MSIMEM_SIZE;
	}
	setup_atu_host(dma_mask);
	arc_write_uncached_32(&bda->bda_dma_mask, dma_mask);
}

/*
 * for End Point mode
 */
static void setup_atu_inbound(void)
{
	setup_atu_shmem();
	setup_atu_sysctl();
}

static int bootpoll(volatile ruby_pcie_bda_t *bda, uint32_t state)
{
	while (arc_read_uncached_32(&bda->bda_bootstate) != state)
	{
		if (arc_read_uncached_32(&bda->bda_flags) & PCIE_BDA_ERROR_MASK)
			return -1;
		udelay(1000);
	}
	return 0;
}

static void set_bootstate(volatile ruby_pcie_bda_t *bda, uint32_t state)
{
	arc_write_uncached_32(&bda->bda_bootstate, state);
}

static void booterror(volatile ruby_pcie_bda_t *bda)
{
	if (PCIE_BDA_HOST_NOFW_ERR & arc_read_uncached_32(&bda->bda_flags))
		printf("There is no firmware in host file system!\n");
	else if (PCIE_BDA_HOST_MEMALLOC_ERR & arc_read_uncached_32(&bda->bda_flags))
		printf("Host alloc memory block for firmware download failed!\n");
	else if (PCIE_BDA_HOST_MEMMAP_ERR & arc_read_uncached_32(&bda->bda_flags))
		printf("Host do dma map for share memory block failed!\n");
	else
		printf("Other error found in host side , bda flag: 0x%x!\n", bda->bda_flags);
}

#define RUN(args...) _run(__FUNCTION__, args)
static int _run(const char* function_name, ...)
{
	va_list args;
	char cmdbuf[64];
	sprintf(cmdbuf, args);
	printf("%s: %s\n", function_name, cmdbuf);
	return run_command(cmdbuf, 0);
}

/*
 * for End Point mode
 */
int do_flash_boot (volatile ruby_pcie_bda_t *bda)
{
	unsigned long live_addr = 0;
	unsigned long live_size = 0;
	const unsigned long mem_addr = QTNBOOT_COPY_DRAM_ADDR;
	char *live_addr_str = getenv (LIVE_IMG_ADDR_ARG);
	char *live_size_str = getenv (LIVE_IMG_SIZE_ARG);


	printf("do flash boot\n");
	set_bootstate(bda,RUBY_BDA_FW_FLASH_BOOT);
	if (live_addr_str && live_size_str) {
		live_addr = simple_strtoul(live_addr_str, NULL, 0);
		live_size = simple_strtoul(live_size_str, NULL, 0);
	} else {
		printf("Variables: %s %s must be set\n",
		       LIVE_IMG_ADDR_ARG,
		       LIVE_IMG_SIZE_ARG);
		arc_write_uncached_32(&bda->bda_flags, PCIE_BDA_TARGET_FBOOT_ERR | arc_read_uncached_32(&bda->bda_flags));
		return 1;
	}

	/* attempt to load the live image into memory and boot it. */
	RUN("spi_flash read 0x%08lx 0x%08lx 0x%08lx", live_addr, mem_addr, live_size);
	RUN("bootm 0x%08lx", mem_addr);

	/* never gets to here */
	arc_write_uncached_32(&bda->bda_flags, PCIE_BDA_TARGET_FBOOT_ERR | arc_read_uncached_32(&bda->bda_flags));
	printf("flash boot error!\n");
	return 0;
}

/*
 * for End Point mode
 */
static int do_pcieboot (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	int rc = 0;
	volatile ruby_pcie_bda_t *bda = (ruby_pcie_bda_t *)(PCIE_BDA);
	void *start = (void *)PCIE_FW_LZMA_LOAD;
	void *dstaddr = start;
	uint32_t size, i=0;
	volatile void  *srcaddr;
	char *local_args[2];
	char load_addr[16];
	char *s;

	extern int do_bootm (cmd_tbl_t *, int, int, char *[]);

	/* set the flash_present flag if env indicate we have firmware in flash */
	s = getenv("flash_img");
	if (s && (*s == '1')) {
		arc_write_uncached_32(&bda->bda_flags,PCIE_BDA_FLASH_PRESENT| arc_read_uncached_32(&bda->bda_flags));
	}
	/* Wait for host ready */
	bootpoll(bda, RUBY_BDA_FW_HOST_RDY);

	setup_atu_outbound(bda);
	set_bootstate(bda,RUBY_BDA_FW_TARGET_RDY);
	bootpoll(bda, RUBY_BDA_FW_TARGET_BOOT);
	/* boot from flash */
	if (PCIE_BDA_FLASH_BOOT & arc_read_uncached_32((void *)&bda->bda_flags)) {
		do_flash_boot(bda);
		return rc;
	}
	set_bootstate(bda,RUBY_BDA_FW_LOAD_RDY);

	printf("Ready to load firmware....\n");
	if (bootpoll(bda, RUBY_BDA_FW_HOST_LOAD)) {
		booterror(bda);
		return -1;
	}
	set_bootstate(bda,RUBY_BDA_FW_EP_RDY);

	bootpoll(bda, RUBY_BDA_FW_BLOCK_RDY);

	srcaddr = (void *)arc_read_uncached_32(&bda->bda_img);
	size = arc_read_uncached_32(&bda->bda_img_size);

	dcache_disable();

	/* Keep loading until we see a zero sized block */
	while(srcaddr && size){
		printf("PCIe Load FW[%u] 0x%x->0x%x Sz:%u...\n", i++, (uint32_t)srcaddr, (uint32_t)dstaddr, size);
		memcpy_fromio(dstaddr, srcaddr, size);

		/* No error checking done, do_bootm() performs the CRC32 check */

		/* Block done, inform host */
		set_bootstate(bda, RUBY_BDA_FW_BLOCK_DONE);

		/* Wait for next block */
		bootpoll(bda, RUBY_BDA_FW_BLOCK_RDY);
		srcaddr = (void *)arc_read_uncached_32(&bda->bda_img);
		dstaddr += size;
		size = arc_read_uncached_32(&bda->bda_img_size);
	}

	/* Invalidate i-cache */
	invalidate_icache_range((int)start, (int)(dstaddr - 1));

	/* Acknowledge the last zero sized block */
	set_bootstate(bda, RUBY_BDA_FW_BLOCK_DONE);

	/* Wait for bootload end message */
	bootpoll(bda, RUBY_BDA_FW_BLOCK_END);

	/* Tell host we are done */
	set_bootstate(bda, RUBY_BDA_FW_LOAD_DONE);

	dcache_enable();

	sprintf(load_addr,"0x%08lx", (unsigned long)PCIE_FW_LZMA_LOAD);
	local_args[0] = argv[0];
	local_args[1] = load_addr;

	printf("PCIe Loadaddr:%s\n",load_addr);
	rc = do_bootm(cmdtp, 0 , 2 ,local_args);

	if (rc) {
		set_bootstate(bda, RUBY_BDA_FW_LOAD_FAIL);
		arc_write_uncached_32(&bda->bda_flags, PCIE_BDA_TARGET_FWLOAD_ERR | arc_read_uncached_32(&bda->bda_flags));
	}
	return rc;
}

static int on_off (const char *s)
{
	if (strcmp(s, "on") == 0) {
		return (1);
	} else if (strcmp(s, "off") == 0) {
		return (0);
	}
	return (-1);
};

static void msi_enable(void)
{
	ulong var=0;
	var = readl(PCIE_MSI_CAP);
	writel(var|RUBY_PCIE_MSI_ENABLE, PCIE_MSI_CAP);
	printf("msi enabled\n");
}

static void msi_disable(void)
{
	ulong var=0;
	var = readl(PCIE_MSI_CAP);
	writel(var&~RUBY_PCIE_MSI_ENABLE, PCIE_MSI_CAP);
	printf("msi disabled\n");
}

/*
 * for End Point mode
 */
static int msi_config (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	switch (argc) {
	case 2:			/* on / off	*/
		switch (on_off(argv[1])) {
		case 1:
			msi_enable();
			break;
		case 0:
			msi_disable();
			break;
		default: cmd_usage(cmdtp);
			return 1;
		}
		break;
	case 1:			/* default on	*/
		msi_enable();
		break;
	default: cmd_usage(cmdtp);
		return 1;
	}
	return 0;
}


/*
  * Exported functions - visible outside of this module
  */

 /* enable or disable MSI */
U_BOOT_CMD(
	msi_cfg,   2,   1,     msi_config,
	"enable or disable msi",
	"[on, off]\n"
	"    - enable or disable msi with cmd msi_cfg [on, off]\n"
);

/* pcieboot */
U_BOOT_CMD(pcieboot,CONFIG_SYS_MAXARGS, 0, do_pcieboot,
		"boot from pcie.  Waits for host to load memory and then calls bootm",
		NULL);

/*
 * maybe move this later, for now we just need to remove pcie reset and set link
 * flags will be used to do any back door init we might require
 */
void pcie_ep_init(size_t memsz, uint32_t flags )
{

	uint32_t i = 0;
	uint32_t bar64 = PCIE_CFG_BAR64;
	uint32_t msi = PCIE_CFG_MSI;
	volatile ruby_pcie_bda_t *bda = (ruby_pcie_bda_t *)(PCIE_BDA);
	char *msi_en;

	/* PCIe init */
	writel(RUBY_SYS_CTL_RESET_IOSS|RUBY_SYS_CTL_RESET_PCIE,RUBY_SYS_CTL_CPU_VEC_MASK);
	writel(0,RUBY_SYS_CTL_CPU_VEC);
	udelay(10);
	writel(RUBY_SYS_CTL_RESET_IOSS|RUBY_SYS_CTL_RESET_PCIE,RUBY_SYS_CTL_CPU_VEC);

	/* Zero out boot data area */
	memset((void *)bda, 0, PCIE_BDA_LEN);
	arc_write_uncached_32(&bda->bda_flags, (RUBY_PCIE_BDA_VERSION << 4));
	arc_write_uncached_32(&bda->bda_dma_offset, PCIE_HOSTMEM_EP_START_LO);
	set_bootstate(bda, RUBY_BDA_PCIE_INIT);

	/* Disable all BARs */
	for (i = 0 ; i < RUBY_PCIE_BAR_NUM; i++)
	{
		writel(1, RUBY_PCIE_BAR_MASK(i));
		writel(0x0, RUBY_PCIE_BAR_MASK(i));
	}

	/* Disable expansion ROM */
	writel(1, PCIE_ROM_MASK_ADDR);
	writel(0x0, PCIE_ROM_MASK_ADDR);

	/* Setup Sysctl BAR */
	writel(1, RUBY_PCIE_BAR_MASK(PCIE_BAR_SYSCTL));
	writel(PCIE_BAR_SYSCTL_LEN, RUBY_PCIE_BAR_MASK(PCIE_BAR_SYSCTL));
	writel(PCIE_BAR_CFG(bar64), RUBY_PCIE_BAR(PCIE_BAR_SYSCTL));

	/* Setup Shared memory BAR  */
	writel(1, RUBY_PCIE_BAR_MASK(PCIE_BAR_SHMEM));
	writel(PCIE_BAR_SHMEM_LEN, RUBY_PCIE_BAR_MASK(PCIE_BAR_SHMEM));
	writel(PCIE_BAR_CFG(bar64), RUBY_PCIE_BAR(PCIE_BAR_SHMEM));

	/* Check to see if MSI override has been added to uboot env */
	msi_en = getenv(PCIE_MSI_ENV);
	if (msi_en) {
		msi = simple_strtoul(msi_en, NULL, 0);
	}
	
	/* Enable MSI */
	if (msi) {
		uint32_t var = readl(PCIE_MSI_CAP);
		writel(var|RUBY_PCIE_MSI_ENABLE, PCIE_MSI_CAP);
	}
	/* Setup ATU  Inbound BAR mappings*/
	setup_atu_inbound();
	/* Enable and wait for link up */
	writel(PCIE_DEFAULT_CFG0,RUBY_SYS_CTL_PCIE_CFG0);
	printf("polling for PCIe Link up\n");
	while (1) {
		if (readl(RUBY_SYS_CTL_CSR) & PCIE_LINKUP)
			break;
		udelay(10); /* Delay. */
	}
	set_bootstate(bda, RUBY_BDA_PCIE_RDY);

}

/*
 * init for root complex mode
 */
void pcie_rc_init(void)
{
	/* set as RC mode */
	writel(SYS_RST_PCIE|SYS_RST_IOSS, RUBY_SYS_CTL_CPU_VEC_MASK);
	writel(SYS_RST_PCIE|SYS_RST_IOSS, RUBY_SYS_CTL_CPU_VEC);
	writel(PCIE_CFG0_DEFAULT_VALUE, RUBY_SYS_CTL_PCIE_CFG0); /* reset */
	writel(PCIE_CFG0_DEFAULT_VALUE|PCIE_CFG_RC_MODE, RUBY_SYS_CTL_PCIE_CFG0); /* RC-mode */

	/* pci config space map: Define outbound region-0 that maps PCIE slave region to PCI config space */
	writel(RUBY_PCIE_ATU_OB_REGION(0), RUBY_PCIE_ATU_VIEW);
	writel(RUBY_PCIE_CONFIG_REGION, RUBY_PCIE_ATU_BASE_LO);
	writel(0x00000000, RUBY_PCIE_ATU_BASE_HI);
	writel(RUBY_PCIE_CONFIG_REGION + (RUBY_PCI_RC_CFG_SIZE - 1), RUBY_PCIE_ATU_BASE_LIMIT );
	writel(0x00000000, RUBY_PCIE_ATU_TARGET_LO);
	writel(0, RUBY_PCIE_ATU_TARGET_HI);
	writel(4, RUBY_PCIE_ATU_CTL1);
	writel(RUBY_PCIE_ATU_OB_ENABLE|RUBY_PCIE_ATU_CFG_SHIFT, RUBY_PCIE_ATU_CTL2);

	/* pci memory space map: Define outbound region-1 that maps PCIE slave region to PCI mem space */
	writel(RUBY_PCIE_ATU_OB_REGION(1), RUBY_PCIE_ATU_VIEW);
	writel(RUBY_PCI_RC_MEM_START, RUBY_PCIE_ATU_BASE_LO);
	writel(0x00000000, RUBY_PCIE_ATU_BASE_HI);
	writel(RUBY_PCI_RC_MEM_START + (RUBY_PCI_RC_MEM_WINDOW - 1), RUBY_PCIE_ATU_BASE_LIMIT );
	writel(0xc0000000, RUBY_PCIE_ATU_TARGET_LO);
	writel(0, RUBY_PCIE_ATU_TARGET_HI);
	writel(0, RUBY_PCIE_ATU_CTL1);
	writel(RUBY_PCIE_ATU_OB_ENABLE, RUBY_PCIE_ATU_CTL2);

	/* pci access enable */
	//writel(RUBY_PCI_RC_MEM_START, RUBY_PCIE_BAR(0));
	writel(PCIE_MEM_EN | PCIE_IO_EN | PCIE_BUS_MASTER_EN, RUBY_PCIE_CMD_REG);

	/* Set up msi generation info */
	writel(RUBY_PCIE_MSI_REGION, RUBY_MSI_ADDR_LOWER);
	writel(0, RUBY_MSI_ADDR_UPPER);
	writel(BIT(0), RUBY_MSI_INT_ENABLE);
	writel(0, RUBY_PCIE_MSI_MASK);
}

void board_pcie_init(size_t memsz, uint32_t flags )
{
	if (flags & PCIE_RC_MODE) {
		printf("init board as PCIe Root Complex mode\n");
		pcie_rc_init();
	} else {
		printf("init board as PCIe End Point mode\n");
		pcie_ep_init(memsz, 0);
	}
}

