/*
 * Copyright (c) 2015-2017 The Linux Foundation. All rights reserved.

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <common.h>
#include <command.h>
#include <image.h>
#include <nand.h>
#include <errno.h>
#include <asm/arch-qca-common/scm.h>
#include <part.h>
#include <linux/mtd/ubi.h>
#include <asm/arch-qca-common/smem.h>
#include <mmc.h>
#include <part_efi.h>
#include <fdtdec.h>
#include "fdt_info.h"
#include <asm/errno.h>
#include <nand.h>
#include <spi_flash.h>
#include <spi.h>
#include <asm/arch-qca-common/iomap.h>
#include <asm/io.h>

#define DLOAD_MAGIC_COOKIE 0x10
#define XMK_STR(x)#x
#define MK_STR(x)XMK_STR(x)
#define MAX_TFTP_SIZE 0x40000000

static int debug = 0;
static char mtdids[256];

DECLARE_GLOBAL_DATA_PTR;
static qca_smem_flash_info_t *sfi = &qca_smem_flash_info;
int ipq_fs_on_nand ;
extern int nand_env_device;
extern qca_mmc mmc_host;
extern void board_usb_deinit(int id);

#ifdef CONFIG_QCA_MMC
static qca_mmc *host = &mmc_host;
#endif

typedef struct {
	unsigned int image_type;
	unsigned int header_vsn_num;
	unsigned int image_src;
	unsigned char *image_dest_ptr;
	unsigned int image_size;
	unsigned int code_size;
	unsigned char *signature_ptr;
	unsigned int signature_size;
	unsigned char *cert_chain_ptr;
	unsigned int cert_chain_size;
} mbn_header_t;

typedef struct {
	unsigned int kernel_load_addr;
	unsigned int kernel_load_size;
} kernel_img_info_t;

kernel_img_info_t kernel_img_info;

char dtb_config_name[64];

__weak int scm_set_boot_addr(void)
{
	return -1;
}

static int krait_release_secondary(void)
{
	writel(0xa4, CPU1_APCS_SAW2_VCTL);
	barrier();
	udelay(512);

	writel(0x109, CPU1_APCS_CPU_PWR_CTL);
	writel(0x101, CPU1_APCS_CPU_PWR_CTL);
	barrier();
	udelay(1);

	writel(0x121, CPU1_APCS_CPU_PWR_CTL);
	barrier();
	udelay(2);

	writel(0x120, CPU1_APCS_CPU_PWR_CTL);
	barrier();
	udelay(2);

	writel(0x100, CPU1_APCS_CPU_PWR_CTL);
	barrier();
	udelay(100);

	writel(0x180, CPU1_APCS_CPU_PWR_CTL);
	barrier();

	return 0;
}

#ifdef CONFIG_QCA_APPSBL_DLOAD
static int tftpdump (int is_aligned_access, uint32_t memaddr, uint32_t size, char *name)
{
	char runcmd[128];
	char *dumpdir;

	if ((dumpdir = getenv("dumpdir")) != NULL) {
		printf("Using directory %s in TFTP server\n", dumpdir);
	} else {
		dumpdir = "";
		printf("Env 'dumpdir' not set. Using / dir in TFTP server\n");
	}

	if (is_aligned_access) {
		if (IPQ_TEMP_DUMP_ADDR) {
			snprintf(runcmd, sizeof(runcmd), "cp.l 0x%x 0x%x 0x%x", memaddr,
					IPQ_TEMP_DUMP_ADDR, size / 4);
			if (run_command(runcmd, 0) != CMD_RET_SUCCESS)
				return CMD_RET_FAILURE;

			memaddr = IPQ_TEMP_DUMP_ADDR;
		} else {
			printf("%s  needs aligned access and temp address is not defined. Skipping...", name);
			return CMD_RET_FAILURE;
		}
	}

	snprintf(runcmd, sizeof(runcmd), "tftpput 0x%x 0x%x %s/%s",
		memaddr, size, dumpdir, name);

	if (run_command(runcmd, 0) != CMD_RET_SUCCESS)
		return CMD_RET_FAILURE;

	return CMD_RET_SUCCESS;

}

static int do_dumpqca_data(void)
{
	char *serverip = NULL;
	/* dump to root of TFTP server if none specified */
	uint32_t memaddr;
	uint32_t remaining;
	int indx;
	int ebi_indx = 0;
	int ret = CMD_RET_FAILURE;
	char buf = 1;
	struct dumpinfo_t *dumpinfo = dumpinfo_n;
	int dump_entries = dump_entries_n;

	serverip = getenv("serverip");
	if (serverip != NULL) {
		printf("Using serverip from env %s\n", serverip);
	} else {
		printf("\nServer ip not found, run dhcp or configure\n");
		return CMD_RET_FAILURE;
	}

	ret = qca_scm_call(SCM_SVC_FUSE,
			   QFPROM_IS_AUTHENTICATE_CMD, &buf, sizeof(char));
	if (ret == 0 && buf == 1) {
		dumpinfo = dumpinfo_s;
		dump_entries = dump_entries_s;
	}

	if (scm_set_boot_addr() == 0) {
		/* Pull Core-1 out of reset, iff scm call succeeds */
		krait_release_secondary();
	}

	for (indx = 0; indx < dump_entries; indx++) {
		printf("\nProcessing %s:", dumpinfo[indx].name);

		if (dumpinfo[indx].is_redirected) {
			memaddr = *((uint32_t *)(dumpinfo[indx].start));
			if (!memaddr) {
				printf("Crashdump for %s is not available.\n",
					dumpinfo[indx].name);
				continue;
			}
		} else {
			memaddr = dumpinfo[indx].start;
		}

		if (dumpinfo[indx].offset)
			memaddr += dumpinfo[indx].offset;

		if (!strncmp(dumpinfo[indx].name, "EBICS", strlen("EBICS")))
		{
			if (!strncmp(dumpinfo[indx].name,
				     "EBICS0", strlen("EBICS0")))
				dumpinfo[indx].size = gd->ram_size;

			if (!strncmp(dumpinfo[indx].name,
				     "EBICS_S1", strlen("EBICS_S1")))
				dumpinfo[indx].size = gd->ram_size
						      - dumpinfo[indx - 1].size
						      - 0x400000;

			remaining = dumpinfo[indx].size;
			while (remaining > 0) {
				snprintf(dumpinfo[indx].name, sizeof(dumpinfo[indx].name), "EBICS%d.BIN", ebi_indx);

				if (remaining > MAX_TFTP_SIZE) {
					dumpinfo[indx].size = MAX_TFTP_SIZE;
				}
				else {
					dumpinfo[indx].size = remaining;
				}
				ret = tftpdump (dumpinfo[indx].is_aligned_access, memaddr, dumpinfo[indx].size, dumpinfo[indx].name);
				if (ret == CMD_RET_FAILURE)
					return CMD_RET_FAILURE;

				memaddr += dumpinfo[indx].size;
				remaining -= dumpinfo[indx].size;
				ebi_indx++;
			}
		}
		else
		{
			ret = tftpdump (dumpinfo[indx].is_aligned_access, memaddr, dumpinfo[indx].size, dumpinfo[indx].name);
			if (ret == CMD_RET_FAILURE)
				return CMD_RET_FAILURE;
		}

		udelay(10000); /* give some delay for server */
	}
	return CMD_RET_SUCCESS;
}

/**
 * Inovke the dump routine and in case of failure, do not stop unless the user
 * requested to stop
 */
void dump_func(void)
{
	uint64_t etime;

#ifdef CONFIG_IPQ_ETH_INIT_DEFER
	puts("\nNet:   ");
	eth_initialize();
#endif

	etime = get_timer_masked() + (10 * CONFIG_SYS_HZ);
	printf("\nHit any key within 10s to stop dump activity...");
	while (!tstc()) {       /* while no incoming data */
		if (get_timer_masked() >= etime) {
			if (do_dumpqca_data() == CMD_RET_FAILURE)
				printf("Crashdump saving failed!\n");
			break;
		}
	}
	/* reset the system, some images might not be loaded
	 * when crashmagic is found
	 */
	run_command("reset", 0);
}
#endif

/*
 * Set the root device and bootargs for mounting root filesystem.
 */
static int set_fs_bootargs(int *fs_on_nand)
{
	char *bootargs;
	unsigned int active_part = 0;

#define nand_rootfs "ubi.mtd=" QCA_ROOT_FS_PART_NAME " root=mtd:ubi_rootfs rootfstype=squashfs"

	if (sfi->flash_type == SMEM_BOOT_SPI_FLASH) {
		if (get_which_flash_param("rootfs") ||
		    sfi->flash_secondary_type == SMEM_BOOT_NAND_FLASH) {
			bootargs = nand_rootfs;
			*fs_on_nand = 1;

			if (sfi->rootfs.offset == 0xBAD0FF5E) {
				sfi->rootfs.offset = 0;
				sfi->rootfs.size = IPQ_NAND_ROOTFS_SIZE;
			}

			fdt_setprop(gd->fdt_blob, 0, "nor_nand_available", fs_on_nand, sizeof(int));
			snprintf(mtdids, sizeof(mtdids),
				 "nand%d=nand%d,nand%d=" QCA_SPI_NOR_DEVICE,
				 is_spi_nand_available(),
				 is_spi_nand_available(),
				CONFIG_SPI_FLASH_INFO_IDX
				);

			if (getenv("fsbootargs") == NULL)
				setenv("fsbootargs", bootargs);
		} else {
			if (smem_bootconfig_info() == 0) {
				active_part = get_rootfs_active_partition();
				if (active_part) {
					bootargs = "rootfsname=rootfs_1";
				} else {
					bootargs = "rootfsname=rootfs";
				}
			} else {
				bootargs = "rootfsname=rootfs";
			}
			*fs_on_nand = 0;

			snprintf(mtdids, sizeof(mtdids), "nand%d="
				QCA_SPI_NOR_DEVICE, CONFIG_SPI_FLASH_INFO_IDX);

			if (getenv("fsbootargs") == NULL)
				setenv("fsbootargs", bootargs);
		}
	} else if (sfi->flash_type == SMEM_BOOT_NAND_FLASH) {
		bootargs = nand_rootfs;
		if (getenv("fsbootargs") == NULL)
			setenv("fsbootargs", bootargs);
		*fs_on_nand = 1;

		snprintf(mtdids, sizeof(mtdids), "nand0=nand0");

#ifdef CONFIG_QCA_MMC
	} else if (sfi->flash_type == SMEM_BOOT_MMC_FLASH) {
		if (smem_bootconfig_info() == 0) {
			active_part = get_rootfs_active_partition();
			if (active_part) {
				bootargs = "rootfsname=rootfs_1 gpt";
			} else {
				bootargs = "rootfsname=rootfs gpt";
			}
		} else {
			bootargs = "rootfsname=rootfs gpt";
		}

		*fs_on_nand = 0;
		if (getenv("fsbootargs") == NULL)
			setenv("fsbootargs", bootargs);
#endif
	} else {
		printf("bootipq: unsupported boot flash type\n");
		return -EINVAL;
	}
	//return run_command("setenv bootargs ${bootargs} ${fsbootargs} rootwait", 0);
	setenv("bootargs", bootargs);
	return 0;
}

int config_select(unsigned int addr, char *rcmd, int rcmd_size)
{
	/* Selecting a config name from the list of available
	 * config names by passing them to the fit_conf_get_node()
	 * function which is used to get the node_offset with the
	 * config name passed. Based on the return value index based
	 * or board name based config is used.
	 */

	int soc_version = 0;
	const char *config = getenv("config_name");

	if (config) {
		printf("Manual device tree config selected!\n");
		strlcpy(dtb_config_name, config, sizeof(dtb_config_name));
	} else {
		config = fdt_getprop(gd->fdt_blob, 0, "config_name", NULL);

		if(config == NULL) {
			printf("Failed to get config_name\n");
			return -1;
		}

		snprintf((char *)dtb_config_name,
			 sizeof(dtb_config_name), "%s", config);

		ipq_smem_get_socinfo_version((uint32_t *)&soc_version);
		if(SOCINFO_VERSION_MAJOR(soc_version) >= 2) {
			snprintf(dtb_config_name + strlen("config@"),
				 sizeof(dtb_config_name) - strlen("config@"),
				 "v%d.0-%s",
				 SOCINFO_VERSION_MAJOR(soc_version),
				 config + strlen("config@"));
		}
	}

	char *tok = strtok(dtb_config_name, ",");

	while(tok != NULL){
		if (fit_conf_get_node((void *)addr, tok) >= 0) {
			snprintf(rcmd, rcmd_size, "bootm 0x%x#%s\n",
				 addr, tok);
			return 0;
		}
		tok = strtok(NULL, ",");
	}

	printf("Config not availabale\n");
	return -1;
}

__weak int switch_ce_channel_buf(unsigned int channel_id)
{
	return 0;
}

static int do_boot_signedimg(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	char runcmd[256];
	int ret,i;
	unsigned int request;
#ifdef CONFIG_QCA_MMC
	block_dev_desc_t *blk_dev;
	disk_partition_t disk_info;
	unsigned int active_part = 0;
#endif

	if (argc == 2 && strncmp(argv[1], "debug", 5) == 0)
		debug = 1;

	if ((ret = set_fs_bootargs(&ipq_fs_on_nand)))
		return ret;

	/* check the smem info to see which flash used for booting */
	if (sfi->flash_type == SMEM_BOOT_SPI_FLASH) {
		if (debug) {
			printf("Using nand device %d\n", CONFIG_SPI_FLASH_INFO_IDX);
		}
		snprintf(runcmd, sizeof(runcmd),
			 "nand device %d", CONFIG_SPI_FLASH_INFO_IDX);
		run_command(runcmd, 0);

	} else if (sfi->flash_type == SMEM_BOOT_NAND_FLASH) {
		if (debug) {
			printf("Using nand device 0\n");
		}
	} else if (sfi->flash_type == SMEM_BOOT_MMC_FLASH) {
		if (debug) {
			printf("Using MMC device\n");
		}
	} else {
		printf("Unsupported BOOT flash type\n");
		return -1;
	}
	if (debug) {
		run_command("printenv bootargs", 0);
		printf("Booting from flash\n");
	}

	request = CONFIG_SYS_LOAD_ADDR;
	kernel_img_info.kernel_load_addr = request;

	if (ipq_fs_on_nand) {
		/*
		 * The kernel will be available inside a UBI volume
		 */
		snprintf(runcmd, sizeof(runcmd),
			 "nand device %d && "
			 "setenv mtdids nand%d=nand%d && "
			 "setenv mtdparts mtdparts=nand%d:0x%llx@0x%llx(fs),${msmparts} && "
			 "ubi part fs && "
			 "ubi read 0x%x kernel && ", is_spi_nand_available(),
			 is_spi_nand_available(),
			 is_spi_nand_available(),
			 is_spi_nand_available(),
			 sfi->rootfs.size, sfi->rootfs.offset,
			 request);

		if (debug)
			printf("%s", runcmd);

		if (run_command(runcmd, 0) != CMD_RET_SUCCESS)
			return CMD_RET_FAILURE;

		kernel_img_info.kernel_load_size =
			(unsigned int)ubi_get_volume_size("kernel");
#ifdef CONFIG_QCA_MMC
	} else if (sfi->flash_type == SMEM_BOOT_MMC_FLASH ||
			((sfi->flash_type == SMEM_BOOT_SPI_FLASH) &&
			(sfi->rootfs.offset == 0xBAD0FF5E))) {
		blk_dev = mmc_get_dev(host->dev_num);
		if (smem_bootconfig_info() == 0) {
			active_part = get_rootfs_active_partition();
			if (active_part) {
				ret = get_partition_info_efi_by_name(blk_dev,
						"0:HLOS_1", &disk_info);
			} else {
				ret = get_partition_info_efi_by_name(blk_dev,
						"0:HLOS", &disk_info);
			}
		} else {
			ret = get_partition_info_efi_by_name(blk_dev,
						"0:HLOS", &disk_info);
		}

		if (ret == 0) {
			snprintf(runcmd, sizeof(runcmd), "mmc read 0x%x 0x%X 0x%X",
				 CONFIG_SYS_LOAD_ADDR,
				 (uint)disk_info.start, (uint)disk_info.size);

			if (run_command(runcmd, 0) != CMD_RET_SUCCESS)
				return CMD_RET_FAILURE;

			kernel_img_info.kernel_load_size = disk_info.size * disk_info.blksz;
		}
#endif
	} else {
		/*
		 * Kernel is in a separate partition
		 */
		snprintf(runcmd, sizeof(runcmd),
			 /* NOR is treated as psuedo NAND */
			 "nand read 0x%x 0x%llx 0x%llx && ",
			 request, sfi->hlos.offset, sfi->hlos.size);

		if (debug)
			printf("%s", runcmd);

		if (run_command(runcmd, 0) != CMD_RET_SUCCESS)
			return CMD_RET_FAILURE;

		kernel_img_info.kernel_load_size =  sfi->hlos.size;
	}

	setenv("mtdids", mtdids);

	request += sizeof(mbn_header_t);

	/* This sys call will switch the CE1 channel to register usage */
	ret = switch_ce_channel_buf(0);

	if (ret)
		return CMD_RET_FAILURE;

	ret = qca_scm_auth_kernel(&kernel_img_info,
			sizeof(kernel_img_info));

	if (ret) {
		printf("Kernel image authentication failed \n");
		BUG();
	}

	/*
	* This sys call will switch the CE1 channel to ADM usage
	* so that HLOS can use it.
	*/
	ret = switch_ce_channel_buf(1);

	if (ret)
		return CMD_RET_FAILURE;

	dcache_enable();

	board_pci_deinit();
#ifdef CONFIG_USB_XHCI_IPQ
	usb_stop();
        for (i=0; i<CONFIG_USB_MAX_CONTROLLER_COUNT; i++) {
		board_usb_deinit(i);
        }
#endif

	ret = config_select(request, runcmd, sizeof(runcmd));

	if (debug)
		printf("%s", runcmd);

	if (ret < 0 || run_command(runcmd, 0) != CMD_RET_SUCCESS) {
#ifdef CONFIG_QCA_MMC
		mmc_initialize(gd->bd);
#endif
#ifdef CONFIG_USB_XHCI_IPQ
		ipq_board_usb_init();
#endif
		dcache_disable();
		return CMD_RET_FAILURE;
	}

#ifndef CONFIG_QCA_APPSBL_DLOAD
	reset_crashdump();
#endif
	return CMD_RET_SUCCESS;
}

static int do_boot_unsignedimg(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	int ret,i;
	char runcmd[256];
#ifdef CONFIG_QCA_MMC
	block_dev_desc_t *blk_dev;
	disk_partition_t disk_info;
	unsigned int active_part = 0;
#endif

	if (argc == 2 && strncmp(argv[1], "debug", 5) == 0)
		debug = 1;

	if ((ret = set_fs_bootargs(&ipq_fs_on_nand)))
		return ret;

	if (debug) {
		run_command("printenv bootargs", 0);
		printf("Booting from flash\n");
	}

	if (sfi->flash_type == SMEM_BOOT_NAND_FLASH) {
		if (debug) {
			printf("Using nand device 0\n");
		}

		/*
		 * The kernel is in seperate partition
		 */
		if (sfi->rootfs.offset == 0xBAD0FF5E) {
			printf(" bad offset of hlos");
			return -1;
		}

		snprintf(runcmd, sizeof(runcmd),
			 "setenv mtdids nand0=nand0 && "
			 "setenv mtdparts mtdparts=nand0:0x%llx@0x%llx(fs),${msmparts} && "
			 "ubi part fs && "
			 "ubi read 0x%x kernel && ",
			 sfi->rootfs.size, sfi->rootfs.offset,
			 CONFIG_SYS_LOAD_ADDR);

	} else if (sfi->flash_type == SMEM_BOOT_SPI_FLASH &&
		   (sfi->rootfs.offset != 0xBAD0FF5E) || ipq_fs_on_nand) {
		if (get_which_flash_param("rootfs") || ipq_fs_on_nand) {
			snprintf(runcmd, sizeof(runcmd),
				 "nand device %d && "
				 "setenv mtdids nand%d=nand%d && "
				 "setenv mtdparts mtdparts=nand%d:0x%llx@0x%llx(fs),${msmparts} && "
				 "ubi part fs && "
				 "ubi read 0x%x kernel && ",
				 is_spi_nand_available(),
				 is_spi_nand_available(),
				 is_spi_nand_available(),
				 is_spi_nand_available(),
				 sfi->rootfs.size, sfi->rootfs.offset,
				 CONFIG_SYS_LOAD_ADDR);
		} else {
			/*
			 * Kernel is in a separate partition
			 */
			snprintf(runcmd, sizeof(runcmd),
				 "sf probe &&"
				 "sf read 0x%x 0x%x 0x%x && ",
				 CONFIG_SYS_LOAD_ADDR, (uint)sfi->hlos.offset, (uint)sfi->hlos.size);
		}
#ifdef CONFIG_QCA_MMC
	} else if ((sfi->flash_type == SMEM_BOOT_MMC_FLASH) ||
			((sfi->flash_type == SMEM_BOOT_SPI_FLASH) &&
			(sfi->rootfs.offset == 0xBAD0FF5E))) {
		if (debug) {
			printf("Using MMC device\n");
		}
		blk_dev = mmc_get_dev(host->dev_num);
		if (smem_bootconfig_info() == 0) {
			active_part = get_rootfs_active_partition();
			if (active_part) {
				ret = get_partition_info_efi_by_name(blk_dev,
						"0:HLOS_1", &disk_info);
			} else {
				ret = get_partition_info_efi_by_name(blk_dev,
						"0:HLOS", &disk_info);
			}
		} else {
			ret = get_partition_info_efi_by_name(blk_dev,
						"0:HLOS", &disk_info);
		}

		if (ret == 0) {
			snprintf(runcmd, sizeof(runcmd), "mmc read 0x%x 0x%x 0x%x",
				 CONFIG_SYS_LOAD_ADDR,
				 (uint)disk_info.start, (uint)disk_info.size);
		}

#endif   /* CONFIG_QCA_MMC   */
	} else {
		printf("Unsupported BOOT flash type\n");
		return -1;
	}

	if (run_command(runcmd, 0) != CMD_RET_SUCCESS) {
#ifdef CONFIG_QCA_MMC
		mmc_initialize(gd->bd);
#endif
		return CMD_RET_FAILURE;
	}

	dcache_enable();

	board_pci_deinit();

#ifdef CONFIG_USB_XHCI_IPQ
	usb_stop();
        for (i=0; i<CONFIG_USB_MAX_CONTROLLER_COUNT; i++) {
		board_usb_deinit(i);
        }
#endif

	setenv("mtdids", mtdids);

	ret = genimg_get_format((void *)CONFIG_SYS_LOAD_ADDR);
	if (ret == IMAGE_FORMAT_FIT) {
		ret = config_select(CONFIG_SYS_LOAD_ADDR,
				    runcmd, sizeof(runcmd));
	} else if (ret == IMAGE_FORMAT_LEGACY) {
		snprintf(runcmd, sizeof(runcmd),
			 "bootm 0x%x\n", CONFIG_SYS_LOAD_ADDR);
	} else {
		ret = genimg_get_format((void *)CONFIG_SYS_LOAD_ADDR +
					sizeof(mbn_header_t));
		if (ret == IMAGE_FORMAT_FIT) {
			ret = config_select((CONFIG_SYS_LOAD_ADDR
					     + sizeof(mbn_header_t)),
					    runcmd, sizeof(runcmd));
		} else if (ret == IMAGE_FORMAT_LEGACY) {
			snprintf(runcmd, sizeof(runcmd),
				 "bootm 0x%x\n", (CONFIG_SYS_LOAD_ADDR +
						  sizeof(mbn_header_t)));
		} else {
			dcache_disable();
			return CMD_RET_FAILURE;
		}
	}


	if (ret < 0 || run_command(runcmd, 0) != CMD_RET_SUCCESS) {
#ifdef CONFIG_USB_XHCI_IPQ
		ipq_board_usb_init();
#endif
		dcache_disable();
		return CMD_RET_FAILURE;
	}
#ifndef CONFIG_QCA_APPSBL_DLOAD
	reset_crashdump();
#endif
	return CMD_RET_SUCCESS;
}

static int do_bootipq(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	int ret;
	char buf = 0;
	/*
	 * set fdt_high parameter so that u-boot will not load
	 * dtb above CONFIG_IPQ40XX_FDT_HIGH region.
	 */
	if (run_command("setenv fdt_high " MK_STR(CONFIG_IPQ_FDT_HIGH) "\n", 0)
	    != CMD_RET_SUCCESS) {
		return CMD_RET_FAILURE;
	}

	ret = qca_scm_call(SCM_SVC_FUSE, QFPROM_IS_AUTHENTICATE_CMD, &buf, sizeof(char));

	aquantia_phy_reset_init_done();

	if (ret == 0 && buf == 1) {
		ret = do_boot_signedimg(cmdtp, flag, argc, argv);
	} else if (ret == 0 || ret == -EOPNOTSUPP) {
		ret = do_boot_unsignedimg(cmdtp, flag, argc, argv);
	}

	if (ret == CMD_RET_FAILURE) {
#ifdef CONFIG_IPQ_ETH_INIT_DEFER
		puts("\nNet:   ");
		eth_initialize();
#endif
	}
	return ret;
}

U_BOOT_CMD(bootipq, 2, 0, do_bootipq,
	   "bootipq from flash device",
	   "bootipq [debug] - Load image(s) and boots the kernel\n");

#ifdef CONFIG_QCA_APPSBL_DLOAD
#define MAX_UNAME_SIZE			1024
#define QCA_WDT_SCM_TLV_TYPE_SIZE	1
#define QCA_WDT_SCM_TLV_LEN_SIZE	2
#define QCA_WDT_SCM_TLV_TYPE_LEN_SIZE (QCA_WDT_SCM_TLV_TYPE_SIZE +\
						QCA_WDT_SCM_TLV_LEN_SIZE)
#define MAX_NAND_PAGE_SIZE		2048
#define MAX_EMMC_BLK_LEN		1024

#ifndef CONFIG_CRASHDUMP_SPI_SPEED
#define CONFIG_CRASHDUMP_SPI_SPEED	1000000
#endif

#ifndef CONFIG_CRASHDUMP_SPI_MODE
#define CONFIG_CRASHDUMP_SPI_MODE	SPI_MODE_3
#endif

#ifndef CONFIG_SYS_MMC_CRASHDUMP_DEV
#define CONFIG_SYS_MMC_CRASHDUMP_DEV	0
#endif

/* Type in TLV for crashdump data type */
enum {
	QCA_WDT_LOG_DUMP_TYPE_INVALID,
	QCA_WDT_LOG_DUMP_TYPE_UNAME,
};

/* This will be used for parsing the TLV data */
struct qca_wdt_scm_tlv_msg {
	unsigned char *msg_buffer;
	unsigned char *cur_msg_buffer_pos;
	unsigned int len;
};

/* Actual crashdump related data */
struct qca_wdt_crashdump_data {
	unsigned char uname[MAX_UNAME_SIZE];
	unsigned int uname_length;
	unsigned char *cpu_context;
};

/* Context for NAND Flash memory */
struct crashdump_flash_nand_cxt {
	loff_t start_crashdump_offset;
	loff_t cur_crashdump_offset;
	int cur_page_data_len;
	int write_size;
	unsigned char temp_data[MAX_NAND_PAGE_SIZE];
};

/* Context for SPI NOR Flash memory */
struct crashdump_flash_spi_cxt {
	loff_t start_crashdump_offset;
	loff_t cur_crashdump_offset;
};

#ifdef CONFIG_QCA_MMC
/* Context for EMMC Flash memory */
struct crashdump_flash_emmc_cxt {
	loff_t start_crashdump_offset;
	loff_t cur_crashdump_offset;
	int cur_blk_data_len;
	int write_size;
	unsigned char temp_data[MAX_EMMC_BLK_LEN];
};
#endif

static struct spi_flash *crashdump_spi_flash;
static struct crashdump_flash_nand_cxt crashdump_nand_cnxt;
static struct crashdump_flash_spi_cxt crashdump_flash_spi_cnxt;
#ifdef CONFIG_QCA_MMC
static struct mmc *mmc;
static struct crashdump_flash_emmc_cxt crashdump_emmc_cnxt;
#endif
static struct qca_wdt_crashdump_data g_crashdump_data;

/* Extracts the type and length in TLV for current offset */
static int qca_wdt_scm_extract_tlv_info(
		struct qca_wdt_scm_tlv_msg *scm_tlv_msg,
		unsigned char *type,
		unsigned int *size)
{
	unsigned char *x = scm_tlv_msg->cur_msg_buffer_pos;
	unsigned char *y = scm_tlv_msg->msg_buffer +
				scm_tlv_msg->len;

	if ((x + QCA_WDT_SCM_TLV_TYPE_LEN_SIZE) >= y)
		return -EINVAL;

	*type = x[0];
	*size = x[1] | (x[2] << 8);

	return 0;
}

/* Extracts the value from TLV for current offset */
static int qca_wdt_scm_extract_tlv_data(
		struct qca_wdt_scm_tlv_msg *scm_tlv_msg,
		unsigned char *data,
		unsigned int size)
{
	unsigned char *x = scm_tlv_msg->cur_msg_buffer_pos;
	unsigned char *y = scm_tlv_msg->msg_buffer + scm_tlv_msg->len;

	if ((x + QCA_WDT_SCM_TLV_TYPE_LEN_SIZE + size) >= y)
		return -EINVAL;

	memcpy(data, x + 3, size);

	scm_tlv_msg->cur_msg_buffer_pos +=
		(size + QCA_WDT_SCM_TLV_TYPE_LEN_SIZE);

	return 0;
}

/*
* This function parses the TLV message and stores the actual values
* in crashdump_data. For each TLV, It first determines the type and
* length, then it extracts the actual value and stores in the appropriate
* field in crashdump_data.
*/
static int qca_wdt_extract_crashdump_data(
		struct qca_wdt_scm_tlv_msg *scm_tlv_msg,
		struct qca_wdt_crashdump_data *crashdump_data)
{
	unsigned char cur_type = QCA_WDT_LOG_DUMP_TYPE_INVALID;
	unsigned int cur_size;
	int ret_val;

	do {
		ret_val = qca_wdt_scm_extract_tlv_info(scm_tlv_msg,
				&cur_type, &cur_size);

		if (ret_val)
			break;

		switch (cur_type) {
                case QCA_WDT_LOG_DUMP_TYPE_UNAME:
			crashdump_data->uname_length = cur_size;
			ret_val = qca_wdt_scm_extract_tlv_data(scm_tlv_msg,
					crashdump_data->uname, cur_size);

			break;

		case QCA_WDT_LOG_DUMP_TYPE_INVALID:
			break;

		default:
			ret_val = -EINVAL;
			break;
		}

		if (ret_val != 0)
			break;

	} while (cur_type != QCA_WDT_LOG_DUMP_TYPE_INVALID);

	return ret_val;
}

/*
* Init function for NAND flash writing. It intializes its own context
* and erases the required sectors
*/
int init_crashdump_nand_flash_write(void *cnxt, loff_t offset,
					unsigned int total_size)
{
	nand_erase_options_t nand_erase_options;
	struct crashdump_flash_nand_cxt *nand_cnxt = cnxt;
	int ret;

	nand_cnxt->start_crashdump_offset = offset;
	nand_cnxt->cur_crashdump_offset = offset;
	nand_cnxt->cur_page_data_len = 0;
	nand_cnxt->write_size = nand_info[0].writesize;

	if (nand_info[0].writesize > MAX_NAND_PAGE_SIZE) {
		printf("nand page write size is more than configured size\n");
		return -ENOMEM;
	}

	memset(&nand_erase_options, 0, sizeof(nand_erase_options));

	nand_erase_options.length = total_size;
	nand_erase_options.offset = offset;

	ret = nand_erase_opts(&nand_info[0],
			&nand_erase_options);
	if (ret)
		return ret;

	return 0;
}

/*
* Deinit function for NAND flash writing. It writes the remaining data
* stored in temp buffer to NAND.
*/
int deinit_crashdump_nand_flash_write(void *cnxt)
{
	struct crashdump_flash_nand_cxt *nand_cnxt = cnxt;
	unsigned int cur_nand_write_len = nand_cnxt->cur_page_data_len;
	int ret_val = 0;
	int remaining_bytes = nand_cnxt->write_size -
			nand_cnxt->cur_page_data_len;

	if (cur_nand_write_len) {
		/*
		* Make the write data in multiple of page write size
		* and write remaining data in NAND flash
		*/
		memset(nand_cnxt->temp_data + nand_cnxt->cur_page_data_len,
			0xFF, remaining_bytes);

		cur_nand_write_len = nand_cnxt->write_size;
		ret_val = nand_write(&nand_info[0],
				nand_cnxt->cur_crashdump_offset,
				&cur_nand_write_len, nand_cnxt->temp_data);
	}

	return ret_val;
}

/*
* Write function for NAND flash. NAND writing works on page basis so
* this function writes the data in mulitple of page size and stores the
* remaining data in temp buffer. This temp buffer data will be appended
* with next write data.
*/
int crashdump_nand_flash_write_data(void *cnxt,
		unsigned char *data, unsigned int size)
{
	struct crashdump_flash_nand_cxt *nand_cnxt = cnxt;
	unsigned char *cur_data_pos = data;
	unsigned int remaining_bytes;
	unsigned int total_bytes;
	unsigned int cur_nand_write_len;
	unsigned int remaining_len_cur_page;
	int ret_val;

	remaining_bytes = total_bytes = nand_cnxt->cur_page_data_len + size;

	/*
	* Check for minimum write size and store the data in temp buffer if
	* the total size is less than it
	*/
	if (total_bytes < nand_cnxt->write_size) {
		memcpy(nand_cnxt->temp_data + nand_cnxt->cur_page_data_len,
					data, size);
		nand_cnxt->cur_page_data_len += size;

		return 0;
	}

	/*
	* Append the remaining length of data for complete nand page write in
	* currently stored data and do the nand write
	*/
	remaining_len_cur_page = nand_cnxt->write_size -
			nand_cnxt->cur_page_data_len;
	cur_nand_write_len = nand_cnxt->write_size;

	memcpy(nand_cnxt->temp_data + nand_cnxt->cur_page_data_len, data,
			remaining_len_cur_page);

	ret_val = nand_write(&nand_info[0], nand_cnxt->cur_crashdump_offset,
				&cur_nand_write_len,
				nand_cnxt->temp_data);

	if (ret_val)
		return ret_val;

	cur_data_pos += remaining_len_cur_page;
	nand_cnxt->cur_crashdump_offset += cur_nand_write_len;

	/*
	* Calculate the write length in multiple of page length and do the nand
	* write for same length
	*/
	cur_nand_write_len = ((data + size - cur_data_pos) /
				nand_cnxt->write_size) * nand_cnxt->write_size;

	if (cur_nand_write_len > 0) {
		ret_val = nand_write(&nand_info[0],
				nand_cnxt->cur_crashdump_offset,
				&cur_nand_write_len,
				cur_data_pos);

		if (ret_val)
			return ret_val;
	}

	cur_data_pos += cur_nand_write_len;
	nand_cnxt->cur_crashdump_offset += cur_nand_write_len;

	/* Store the remaining data in temp data */
	remaining_bytes = data + size - cur_data_pos;

	memcpy(nand_cnxt->temp_data, cur_data_pos, remaining_bytes);

	nand_cnxt->cur_page_data_len = remaining_bytes;

	return 0;
}

/* Init function for SPI NOR flash writing. It erases the required sectors */
int init_crashdump_spi_flash_write(void *cnxt,
			loff_t offset,
			unsigned int total_size)
{
	int ret;
	unsigned int required_erase_size;
	struct crashdump_flash_spi_cxt *spi_flash_cnxt = cnxt;

	spi_flash_cnxt->start_crashdump_offset = offset;
	spi_flash_cnxt->cur_crashdump_offset = offset;

	if (total_size & (sfi->flash_block_size - 1))
		required_erase_size = (total_size &
					~(sfi->flash_block_size - 1)) +
					sfi->flash_block_size;
	else
		required_erase_size = total_size;

	ret = spi_flash_erase(crashdump_spi_flash,
				offset,
				required_erase_size);

	return ret;
}

/* Write function for SPI NOR flash */
int crashdump_spi_flash_write_data(void *cnxt,
		unsigned char *data, unsigned int size)
{
	struct crashdump_flash_spi_cxt *spi_flash_cnxt = cnxt;
	unsigned int cur_size = size;
	int ret;

	ret = spi_flash_write(crashdump_spi_flash,
			spi_flash_cnxt->cur_crashdump_offset,
			cur_size, data);

	if (!ret)
		spi_flash_cnxt->cur_crashdump_offset += cur_size;

	return ret;
}

/* Deinit function for SPI NOR flash writing. */
int deinit_crashdump_spi_flash_write(void *cnxt)
{
	return 0;
}

#ifdef CONFIG_QCA_MMC
/* Init function for EMMC. It initialzes the EMMC */
static int crashdump_init_mmc(struct mmc *mmc)
{
	int ret;

	if (!mmc) {
		puts("No MMC card found\n");
		return -EINVAL;
	}

	ret = mmc_init(mmc);

	if (ret)
		puts("MMC init failed\n");

	return ret;
}

/*
* Init function for EMMC flash writing. It initialzes its
* own context and EMMC
*/
int init_crashdump_emmc_flash_write(void *cnxt, loff_t offset,
						unsigned int total_size)
{
	struct crashdump_flash_emmc_cxt *emmc_cnxt = cnxt;

	emmc_cnxt->start_crashdump_offset = offset;
	emmc_cnxt->cur_crashdump_offset = offset;
	emmc_cnxt->cur_blk_data_len = 0;
	emmc_cnxt->write_size =  mmc->write_bl_len;

	if (mmc->write_bl_len > MAX_EMMC_BLK_LEN) {
		printf("mmc block length is more than configured size\n");
		return -ENOMEM;
	}

	return 0;
}

/*
* Deinit function for EMMC flash writing. It writes the remaining data
* stored in temp buffer to EMMC
*/
int deinit_crashdump_emmc_flash_write(void *cnxt)
{
	struct crashdump_flash_emmc_cxt *emmc_cnxt = cnxt;
	unsigned int cur_blk_write_len = emmc_cnxt->cur_blk_data_len;
	int ret_val = 0;
	int n;
	int remaining_bytes = emmc_cnxt->write_size -
			emmc_cnxt->cur_blk_data_len;

	if (cur_blk_write_len) {
		/*
		* Make the write data in multiple of block length size
		* and write remaining data in emmc
		*/
		memset(emmc_cnxt->temp_data + emmc_cnxt->cur_blk_data_len,
			0xFF, remaining_bytes);

		cur_blk_write_len = emmc_cnxt->write_size;
		n = mmc->block_dev.block_write(CONFIG_SYS_MMC_CRASHDUMP_DEV,
						emmc_cnxt->cur_crashdump_offset,
						1,
						(u_char *)emmc_cnxt->temp_data);

		ret_val = (n == 1) ? 0 : -ENOMEM;
	}

	return ret_val;
}

/*
* Write function for EMMC flash. EMMC writing works on block basis so
* this function writes the data in mulitple of block length and stores
* remaining data in temp buffer. This temp buffer data will be appended
* with next write data.
*/
int crashdump_emmc_flash_write_data(void *cnxt,
		unsigned char *data, unsigned int size)
{
	struct crashdump_flash_emmc_cxt *emmc_cnxt = cnxt;
	unsigned char *cur_data_pos = data;
	unsigned int remaining_bytes;
	unsigned int total_bytes;
	unsigned int cur_emmc_write_len;
	unsigned int cur_emmc_blk_len;
	unsigned int remaining_len_cur_page;
	int ret_val;
	int n;

	remaining_bytes = total_bytes = emmc_cnxt->cur_blk_data_len + size;

	/*
	* Check for block size and store the data in temp buffer if
	* the total size is less than it
	*/
	if (total_bytes < emmc_cnxt->write_size) {
		memcpy(emmc_cnxt->temp_data + emmc_cnxt->cur_blk_data_len,
				data, size);
		emmc_cnxt->cur_blk_data_len += size;

		return 0;
	}

	/*
	* Append the remaining length of data for complete emmc block write in
	* currently stored data and do the block write
	*/
	remaining_len_cur_page = emmc_cnxt->write_size -
			emmc_cnxt->cur_blk_data_len;
	cur_emmc_write_len = emmc_cnxt->write_size;

	memcpy(emmc_cnxt->temp_data + emmc_cnxt->cur_blk_data_len, data,
			remaining_len_cur_page);

	n = mmc->block_dev.block_write(CONFIG_SYS_MMC_CRASHDUMP_DEV,
					emmc_cnxt->cur_crashdump_offset,
					1,
					(u_char *)emmc_cnxt->temp_data);

	ret_val = (n == 1) ? 0 : -ENOMEM;

	if (ret_val)
		return ret_val;

	cur_data_pos += remaining_len_cur_page;
	emmc_cnxt->cur_crashdump_offset += 1;
	/*
	* Calculate the write length in multiple of block length and do the
	* emmc block write for same length
	*/
	cur_emmc_blk_len = ((data + size - cur_data_pos) /
				emmc_cnxt->write_size);
	cur_emmc_write_len = cur_emmc_blk_len * emmc_cnxt->write_size;

	if (cur_emmc_write_len > 0) {
		n = mmc->block_dev.block_write(CONFIG_SYS_MMC_CRASHDUMP_DEV,
						emmc_cnxt->cur_crashdump_offset,
						cur_emmc_blk_len,
						(u_char *)cur_data_pos);

		ret_val = (n == cur_emmc_blk_len) ? 0 : -1;

		if (ret_val)
			return ret_val;
	}

	cur_data_pos += cur_emmc_write_len;
	emmc_cnxt->cur_crashdump_offset += cur_emmc_blk_len;

	/* Store the remaining data in temp data */
	remaining_bytes = data + size - cur_data_pos;

	memcpy(emmc_cnxt->temp_data, cur_data_pos, remaining_bytes);

	emmc_cnxt->cur_blk_data_len = remaining_bytes;

	return 0;
}
#endif

/*
* This function writes the crashdump data in flash memory.
* It has function pointers for init, deinit and writing. These
* function pointers are being initialized with respective flash
* memory writing routines.
*/
static int qca_wdt_write_crashdump_data(
		struct qca_wdt_crashdump_data *crashdump_data,
		int flash_type, loff_t crashdump_offset)
{
	int ret = 0;
	void *crashdump_cnxt;
	int (*crashdump_flash_write)(void *cnxt, unsigned char *data,
					unsigned int size);
	int (*crashdump_flash_write_init)(void *cnxt, loff_t offset,
					unsigned int total_size);
	int (*crashdump_flash_write_deinit)(void *cnxt);
	unsigned int required_size;

	/*
	* Determine the flash type and initialize function pointer for flash
	* operations and its context which needs to be passed to these functions
	*/
	if (flash_type == SMEM_BOOT_NAND_FLASH) {
		crashdump_cnxt = (void *)&crashdump_nand_cnxt;
		crashdump_flash_write_init = init_crashdump_nand_flash_write;
		crashdump_flash_write = crashdump_nand_flash_write_data;
		crashdump_flash_write_deinit =
			deinit_crashdump_nand_flash_write;
#ifdef CONFIG_QCA_SPI
	} else if (flash_type == SMEM_BOOT_SPI_FLASH) {
		if (!crashdump_spi_flash) {
			crashdump_spi_flash = spi_flash_probe(sfi->flash_index,
				sfi->flash_chip_select,
				CONFIG_CRASHDUMP_SPI_SPEED,
				CONFIG_CRASHDUMP_SPI_MODE);

			if (!crashdump_spi_flash) {
				printf("spi_flash_probe() failed");
				return -EIO;
			}
		}

		crashdump_cnxt = (void *)&crashdump_flash_spi_cnxt;
		crashdump_flash_write = crashdump_spi_flash_write_data;
		crashdump_flash_write_init = init_crashdump_spi_flash_write;
		crashdump_flash_write_deinit =
			deinit_crashdump_spi_flash_write;
#endif
#ifdef CONFIG_QCA_MMC
	} else if (flash_type == SMEM_BOOT_MMC_FLASH) {
		mmc = find_mmc_device(CONFIG_SYS_MMC_CRASHDUMP_DEV);

		ret = crashdump_init_mmc(mmc);

		if (ret)
			return ret;

		crashdump_cnxt = (void *)&crashdump_emmc_cnxt;
		crashdump_flash_write_init = init_crashdump_emmc_flash_write;
		crashdump_flash_write = crashdump_emmc_flash_write_data;
		crashdump_flash_write_deinit =
			deinit_crashdump_emmc_flash_write;
#endif
	} else {
		return -EINVAL;
	}

	/* Start writing cpu context and uname in flash */
	required_size = CONFIG_CPU_CONTEXT_DUMP_SIZE +
				crashdump_data->uname_length;

	ret = crashdump_flash_write_init(crashdump_cnxt,
			crashdump_offset,
			required_size);

	if (ret)
		return ret;

	ret = crashdump_flash_write(crashdump_cnxt,
			crashdump_data->cpu_context,
			CONFIG_CPU_CONTEXT_DUMP_SIZE);

	if (!ret)
		ret = crashdump_flash_write(crashdump_cnxt,
			crashdump_data->uname,
			crashdump_data->uname_length);

	if (!ret)
		ret = crashdump_flash_write_deinit(crashdump_cnxt);

	return ret;
}

/*
* Function for collecting the crashdump data in flash. It extracts the
* crashdump TLV(Type Length Value) data and CPU context information from
* page allocated by kernel for crashdump data collection. It determines
* the type of boot flash memory and writes all these crashdump information
* in provided offset in flash memory.
*/
int do_dumpqca_flash_data(const char *offset)
{
	unsigned char *kernel_crashdump_address =
		(unsigned char *) CONFIG_QCA_KERNEL_CRASHDUMP_ADDRESS;
	struct qca_wdt_scm_tlv_msg tlv_msg;
	int flash_type;
	int ret_val;
	loff_t crashdump_offset;


	if (sfi->flash_type == SMEM_BOOT_NAND_FLASH) {
		flash_type = SMEM_BOOT_NAND_FLASH;
	} else if (sfi->flash_type == SMEM_BOOT_SPI_FLASH) {
		flash_type = SMEM_BOOT_SPI_FLASH;
#ifdef CONFIG_QCA_MMC
	} else if (sfi->flash_type == SMEM_BOOT_MMC_FLASH) {
		flash_type = SMEM_BOOT_MMC_FLASH;
#endif
	} else {
		printf("command not supported for this flash memory\n");
		return -EINVAL;
	}

	ret_val = str2off(offset, &crashdump_offset);

	if (!ret_val)
		return -EINVAL;

	g_crashdump_data.cpu_context = kernel_crashdump_address;
	tlv_msg.msg_buffer = kernel_crashdump_address + CONFIG_CPU_CONTEXT_DUMP_SIZE;
	tlv_msg.cur_msg_buffer_pos = tlv_msg.msg_buffer;
	tlv_msg.len = CONFIG_TLV_DUMP_SIZE;

	ret_val = qca_wdt_extract_crashdump_data(&tlv_msg, &g_crashdump_data);

	if (!ret_val)
		ret_val = qca_wdt_write_crashdump_data(&g_crashdump_data,
				flash_type, crashdump_offset);

	if (ret_val) {
		printf("crashdump data writing in flash failure\n");
		return -EPERM;
	}

	printf("crashdump data writing in flash successful\n");

	return 0;
}
#endif
