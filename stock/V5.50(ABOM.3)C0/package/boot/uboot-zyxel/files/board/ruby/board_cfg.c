/*
 * Copyright (c) 2010 Quantenna Communications, Inc.
 * All rights reserved.
 *
 *  file purpose
 *    Map board_id to coard configuration definitions
 */

////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////
#include "ruby.h"
#include "board_cfg.h"
#include "ddr.h"
#include <shared_defs.h>

/* Enable auto configured board ID based on uboot environment vars */
#define UBOOT_BOARD_AUTOCONFIG

#include "ruby_board_cfg.h"
#include "ruby_board_db.h"
#include "ruby_pcie_bda.h"

static const board_cfg_t	g_board_cfg_table[] = QTN_BOARD_DB;
static board_cfg_t		*custom_board = NULL;
extern uint32_t			flash_size;
static char			board_name[RUBY_BDA_NAMELEN];

extern board_cfg_t board_hw_config;

#define FLASH_SIZE(board_id, size)		((board_id == QTN_RUBY_UNIVERSAL_BOARD_ID) ? (size*1024*1024) : size)
/***************************************************************************
   Function:
   Purpose:
   Returns:
   Note: Code assumes parameter is within range
 **************************************************************************/

board_cfg_t *board_locate(int board_id, const board_cfg_t *table, int nentries)
{
	int i;

	if (board_id == QTN_RUBY_UNIVERSAL_BOARD_ID) {
		return &board_hw_config;
	}

	if (board_id == QTN_RUBY_AUTOCONFIG_ID) {
		return custom_board;
	}

	for (i=0; i < nentries; i++) {
		if (board_id == table[i].bc_board_id){
			return (board_cfg_t *)&table[i];
		}
	}
	return NULL;
}


int board_config(int board_id, int parameter)
{

	const int *ptr;
	board_cfg_t *board = board_locate(board_id, g_board_cfg_table, sizeof(g_board_cfg_table)/sizeof(board_cfg_t));

	if (board) {
		ptr = (int *)board;
		return ptr[parameter];
	}

	return -1;
}

int board_parse_tag_value(ruby_cfgstr_map_t *map, char *token, uint32_t *val)
{
	while (map && map->name) {
		if (!strcmp(map->name, token)) {
			*val = map->val;
			return 0;
		}
		map++;
	}

	printf("token=%s invalid\n", token);
	return -1;
}

const char *board_find_tag_name(ruby_board_param_t *params, uint32_t index, uint32_t val)
{
	while(params) {
		if (params->p_index == index){
			ruby_cfgstr_map_t *map = (ruby_cfgstr_map_t *)params->p_map;
			while(map) {
				if(map->val == val) {
					return map->name;
				}
				map++;
			}
			return NULL;
		}
		params++;
	}
	return NULL;
}
int board_parse_custom_cfg(void *addr)
{
	ruby_board_template_t	*tpl = &g_custom_board_template;
	ruby_board_param_t	*params = (ruby_board_param_t *)tpl->t_params;
	int			*ptr = (int *)tpl->t_board;
	char			*token = NULL;
	uint32_t		val = 0;

	custom_board = tpl->t_board;
	while (params && params->p_tag) {
		val = 0;
		token = getenv((char *)params->p_tag);
		if (token && (params->p_index == BOARD_CFG_NAME)) {
			uint32_t len = strlen(token);

			/* Copy the boardname string as we don't know if the buffer space from getenv() will be reused */
			memset(board_name, 0, RUBY_BDA_NAMELEN);
			memcpy(board_name, token, (len > (RUBY_BDA_NAMELEN - 1)) ? (RUBY_BDA_NAMELEN - 1) : len);

		} else if (token && !board_parse_tag_value(params->p_map, token, &val)) {
			if (params->p_index == BOARD_CFG_FLASH_SIZE) {
				flash_size = val;
			} else {
				ptr[params->p_index] = val;
			}
		};
		params++;
	}
	return 0;
}

void board_setup_bda(void *addr, int board_id)
{
	ruby_pcie_bda_t *bda = (ruby_pcie_bda_t *)addr;
	board_cfg_t *board = (board_id == QTN_RUBY_AUTOCONFIG_ID) ? custom_board :((board_id == QTN_RUBY_UNIVERSAL_BOARD_ID) ? &board_hw_config :
						board_locate(board_id, g_board_cfg_table, sizeof(g_board_cfg_table)/sizeof(board_cfg_t)));
	char *name = (board_id == QTN_RUBY_AUTOCONFIG_ID) ? board_name : board->bc_name;

	uint32_t len = strlen(name);

	bda->bda_len = sizeof(ruby_pcie_bda_t);
	bda->bda_version = RUBY_PCIE_BDA_VERSION;

	printf("BDA at 0x%x\n", (int)addr);

	memcpy(&bda->bda_boardcfg, board, sizeof(board_cfg_t));
	memset(bda->bda_boardname, 0 , RUBY_BDA_NAMELEN);
	memcpy(bda->bda_boardname, name, (len > (RUBY_BDA_NAMELEN-1)) ? (RUBY_BDA_NAMELEN -1) : len);

	bda->bda_flashsz = FLASH_SIZE(board_id, flash_size);

}

int do_list_board_options(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[])
{
	const ruby_board_param_t	*params = g_custom_board_template.t_params;

	printf("HW config Board options:\n");
	while (params && params->p_tag) {
		const ruby_cfgstr_map_t *map = params->p_map;

		printf("%s=(", params->p_tag);
		while(map && map->name) {
			printf("%s,",  map->name);
			map++;
		}

		printf(")\n");
		params++;
	}
	return 0;

}

int do_list_board_cfg(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[])
{
	board_cfg_t *board = NULL;
	int board_id = 0;
	char *token = (argc == 2) ? argv[1] : getenv("hw_config_id");;
	ruby_board_param_t *params = (ruby_board_param_t *)g_custom_board_template.t_params;
	
	if(!token) {
		printf("\"hw_config_id\" not set\n");
		return -1;
	}

	board_id = simple_strtoul (token, NULL, 10);
	if (board_id < 0) {
		printf("\"Invalid board: %s\n", token);
		return -1;
	}
	board = board_locate(board_id, g_board_cfg_table, sizeof(g_board_cfg_table)/sizeof(board_cfg_t));

	if(!board) {
		printf("Board ID:%d not valid.\n", board_id);
		return -1;
	}
	if (argc == 2) {
		printf("Board config for ID:%d\n", board_id);
	} else {
		printf("Current board config:\n");
	}
	printf("\tID:\t%d\n", board->bc_board_id);
	printf("\tName:\t%s\n", board->bc_name);
	printf("\tDDR:\t%s %dMHz %dM\n",
		board_find_tag_name(params, BOARD_CFG_DDR_TYPE, board->bc_ddr_type), 
						board->bc_ddr_speed, board->bc_ddr_size >> 20);
	printf("\tEMAC0:\t%s\n", board_find_tag_name(params, BOARD_CFG_EMAC0, board->bc_emac0));	
	printf("\tEMAC1:\t%s\n", board_find_tag_name(params, BOARD_CFG_EMAC1, board->bc_emac1));
	printf("\tRFPA:\t%s\n", board_find_tag_name(params, BOARD_CFG_WIFI_HW, board->bc_wifi_hw));
	printf("\tRGMII:\t0x%x\n", board->bc_rgmii_timing);

	printf("\tSPI1:\t%s\n", board->bc_spi1 ? "Enabled" : "Disabled");
	printf("\tUART1:\t%s\n", board->bc_uart1 ? "Enabled" : "Disabled");
	printf("\tPCIe:\t%s\n", board->bc_pcie ? "Enabled" : "Disabled");

	return 0;

}

int do_list_board(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[])
{
	int i;
	printf("HW config  Board Name\n");
	printf("--------  ------------------------------\n");
	for (i=0;i<sizeof(g_board_cfg_table)/sizeof(board_cfg_t);i++) {
		printf("%8d  %s\n",g_board_cfg_table[i].bc_board_id,
			g_board_cfg_table[i].bc_name);
	}
	printf("\n");

	return 0;
}

U_BOOT_CMD(boardcfg, 2, 0, do_list_board_cfg,"list current board config",NULL);

U_BOOT_CMD(boardopts, 1, 0, do_list_board_options,"list board config options",NULL);

U_BOOT_CMD(lsid, 1, 0, do_list_board,"list board IDs",NULL);

