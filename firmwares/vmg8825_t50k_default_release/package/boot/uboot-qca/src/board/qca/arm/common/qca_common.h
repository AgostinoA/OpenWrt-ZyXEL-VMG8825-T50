/*
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.

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


typedef struct {
	uint base;
	uint clk_mode;
	struct mmc *mmc;
	int dev_num;
} qca_mmc;

int qca_mmc_init(bd_t *, qca_mmc *);
void board_mmc_deinit(void);

int get_eth_mac_address(uchar *enetaddr, uint no_of_macs);
void set_ethmac_addr(void);

#define MSM_SDC1_BASE		0x7824000
#define MMC_IDENTIFY_MODE	0
#define MMC_DATA_TRANSFER_MODE	1
#define MMC_MODE_HC		0x800

#endif  /*  __QCA_COMMON_H_ */
