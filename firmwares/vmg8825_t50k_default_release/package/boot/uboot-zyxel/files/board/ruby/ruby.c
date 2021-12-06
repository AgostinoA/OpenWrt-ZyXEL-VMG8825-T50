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

#include "ruby.h"
#include "ddr.h"
#include <shared_defs.h>
#include "ruby_board_cfg.h"
#include "ruby_board_db.h"
#include "ruby_pcie_bda.h"
#include "board_cfg.h"
#include "pcie.h"

extern int board_hw_config_read(void);
/* use spare register for saving gd pointer - used for EXPORT_FUNC() */
static void board_global_data_init(void)
{
	DECLARE_GLOBAL_DATA_PTR;
	gd->cpu_clk = RUBY_FIXED_CPU_CLK;
	gd->bus_clk = RUBY_FIXED_DEV_CLK;
	gd->baudrate = RUBY_SERIAL_BAUD;
	gd->bd->bi_memsize = RUBY_MIN_DRAM_SIZE;
	gd->bd->bi_boot_params = 0x0;
	writel((int)gd,0xe00000bc);
}

int board_init(void)
{
	board_global_data_init();
	board_serial_init();
	board_info_init();
	board_intr_init();
	board_timer_init();
	board_spi_flash_init();
	return 0;
}

static void dump_muc_stack(const struct ruby_crumbs *crumbs)
{
	uint32_t sp_muc;
	const uint32_t *sp_virt;
	const uint32_t * const sp_virt_end = (void*)CONFIG_ARC_MUC_STACK_INIT;

	printf("\tMuC stack candidates:\n");
	printf("\t\tdram text: 0x%08lx - 0x%08lx\n",
			crumbs->muc_dram.start,
			crumbs->muc_dram.end);
	printf("\t\tsram text: 0x%08lx - 0x%08lx\n",
			crumbs->muc_sram.start,
			crumbs->muc_sram.end);

	sp_muc = crumbs->muc.sp;
	if (!sp_muc) {
		/*
		 * if the MuC isn't recording prolog crumbs,
		 * use the lowest part of the MuC stack
		 */
		sp_muc = virt_to_bus((void*)CONFIG_ARC_STACK_BEGIN);
	}
	sp_virt = (void*)bus_to_virt(sp_muc);
	if (sp_virt == RUBY_BAD_VIRT_ADDR) {
		printf("%s: could not get sp_virt, sp_muc = 0x%08x\n", __FUNCTION__, sp_muc);
		return;
	}
	if (sp_muc % 4 != 0 || ((uint32_t)sp_virt) % 4 != 0) {
		printf("%s: misaligned stack pointer muc 0x%08x\n", __FUNCTION__, sp_muc);
		return;
	}

	while (sp_virt <= sp_virt_end) {
		/*
		 * read muc stack contents at *sp, compare value with muc text sections
		 */
		uint32_t val = *sp_virt;
		int in_sram = val >= crumbs->muc_sram.start && val <= crumbs->muc_sram.end;
		int in_dram = val >= crumbs->muc_dram.start && val <= crumbs->muc_dram.end;
		if (val && (in_sram || in_dram)) {
			printf("\t\tsp 0x%08x\tfn 0x%08x\n", sp_muc, val);
		}
		sp_muc += 4;
		sp_virt++;
	}
}

static void dump_core_crumbs(const char* core, const struct ruby_crumbs_percore *core_crumbs)
{
	printf("\t%s:\tblink 0x%lx status32 0x%lx sp 0x%lx\n",
			core,
			core_crumbs->blink,
			core_crumbs->status32,
			core_crumbs->sp);
}

static void dump_ruby_crumbs(const struct ruby_crumbs *crumbs)
{
	dump_core_crumbs("lhost", &crumbs->lhost);
	dump_core_crumbs("DSP", &crumbs->dsp);
	dump_core_crumbs("MuC", &crumbs->muc);
}

static void init_ruby_crumbs(void)
{
	struct ruby_crumbs *crumbs = (struct ruby_crumbs*)RUBY_CRUMBS_ADDR;
	char *crumb_env;
	int show_crumbs = 0;
	int magic_valid =  crumbs->magic == RUBY_CRUMBS_MAGIC;

	crumb_env = getenv("dump_crumbs");
	if (crumb_env != NULL) {
		show_crumbs = simple_strtoul(crumb_env, NULL, 10);
	}

	if (show_crumbs) {
		printf("Info: last core activity: \n");
		if (magic_valid) {
			dump_ruby_crumbs(crumbs);
			dump_muc_stack(crumbs);
		} else {
			printf("***Crumbs magic token is incorrect, values are probably invalid\n");
			dump_ruby_crumbs(crumbs);
		}
		printf("\n");
	}

	/* clear the crumbs structure */
	memset(crumbs, 0, sizeof(*crumbs));
}

int board_late_init(void)
{
	DECLARE_GLOBAL_DATA_PTR;
	u32 ddr_speed = DEFAULT_DDR_SPEED;
	u32 ddr_type = DEFAULT_DDR_CFG;
	u32 ddr_size = DEFAULT_DDR_SIZE;
	char *s;
	int board_id = 0;
#ifdef CONFIG_CMD_PCIEBOOT
	int pcie_flags;
#endif
	int retval = 0;

	init_ruby_crumbs();

	/*
	 * Figure out our board type from
	 * env and configure properly
	 */
	s = getenv("hw_config_id");
	if (s == NULL) {
		printf("\"hw_config_id\" not set, using default value of 0\n");
	} else {
		board_id = simple_strtoul (s, NULL, 10);
	}

	if (board_id == QTN_RUBY_AUTOCONFIG_ID) {
		board_parse_custom_cfg((void *)CONFIG_ARC_CONF_BASE);
	}

	if (board_id == QTN_RUBY_UNIVERSAL_BOARD_ID) {
		retval = board_hw_config_read();

		if (retval < 0) {
			return 0;
		}
	}

	gd->bd->bi_board_id = board_id;

	if (board_config(board_id, BOARD_CFG_ID) != board_id) {
		printf("error: board configuration not found\n");
		return 0;
	} else {
		char *s = (char *)board_config(board_id,BOARD_CFG_NAME);
		if (s != NULL) {
			printf("board config:%s\n",s);
		}
	}

	ddr_type = board_config(board_id,BOARD_CFG_DDR_TYPE);
	ddr_speed = board_config(board_id,BOARD_CFG_DDR_SPEED);
	ddr_size = board_config(board_id,BOARD_CFG_DDR_SIZE);

	gd->bd->bi_memsize = ddr_size;
	ddr_init(ddr_type,ddr_speed,ddr_size);
	board_setup_bda((void *)CONFIG_ARC_CONF_BASE, board_id);
#ifdef CONFIG_CMD_PCIEBOOT
	if ((pcie_flags = board_config(board_id,BOARD_CFG_PCIE)) & PCIE_IN_USE) {
		printf("Init pcie link\n");
		board_pcie_init(gd->bd->bi_memsize, pcie_flags);
	}
#endif
	if (board_update_uboot_version() && gd->env_valid) {
		saveenv();
	}

	qtn_parse_early_flash_config(0);

	return 0;
}

