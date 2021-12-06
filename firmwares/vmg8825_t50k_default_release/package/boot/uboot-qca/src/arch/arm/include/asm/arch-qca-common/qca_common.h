/*
 * Copyright (c) 2015-2017, The Linux Foundation. All rights reserved.

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef ___QCA_COMMON_H_
#define ___QCA_COMMON_H_
#include <asm/u-boot.h>
#include <asm/arch-qca-common/smem.h>

#ifdef CONFIG_IPQ807x
#include <asm/arch-ipq807x/clk.h>
#endif

#ifdef CONFIG_IPQ40xx
#include <asm/arch-ipq40xx/clk.h>
#endif


#ifdef CONFIG_IPQ806x
#include <asm/arch-ipq806x/clock.h>
#endif

struct ipq_i2c_platdata {
	int type;
};

typedef struct {
	uint base;
	uint clk_mode;
	struct mmc *mmc;
	int dev_num;
} qca_mmc;

/* Reserved-memory node names and register value*/
typedef struct {
	const char *nodename;
	u32 val[2];
} add_node_t;

int qca_mmc_init(bd_t *, qca_mmc *);
void board_mmc_deinit(void);

void set_flash_secondary_type(qca_smem_flash_info_t *);
void dump_func(void);
int do_dumpqca_flash_data(const char *);
int apps_iscrashed(void);

struct dumpinfo_t{
	char name[16]; /* use only file name in 8.3 format */
	uint32_t start;
	uint32_t size;
	int is_aligned_access; /* non zero represent 4 byte access */
	uint32_t is_redirected; /* If this flag is set, 'start' is considered a ptr
			    * to address to be dumped
			    */
	uint32_t offset; /* offset to be added to start address */
};
extern struct dumpinfo_t dumpinfo_n[];
extern int dump_entries_n;

extern struct dumpinfo_t dumpinfo_s[];
extern int dump_entries_s;

#define MSM_SDC1_BASE		0x7824000
#define MSM_SDC1_MCI_HC_MODE	0x7824078
#define MSM_SDC1_SDHCI_BASE		0x7824900
#define MMC_IDENTIFY_MODE	0
#define MMC_DATA_TRANSFER_MODE	1
#define MMC_DATA_TRANSFER_SDHCI_MODE 2
#define MMC_MODE_HC		0x800

#define SPI_DEFAULT_ADDR_LEN	3
#define SPI_MAX_ADDR_LEN	4
#endif  /*  __QCA_COMMON_H_ */
