/*
 * Quantenna Board Provision configuraion file upload/update/show support
 */
#include <common.h>
#include <command.h>
#include <environment.h>
#include <malloc.h>
#include <net.h>

#include "ruby.h"
#include "spi_flash.h"
#include "board_cfg.h"
#include "ruby_config.h"
#include "ruby_board_cfg.h"
#include "ruby_board_db.h"
#include "shared_defs.h"

#define FAIL			(-1)
#define SUCCESS			(0)
#define CMD_BUFSIZE		256
#define TMP_BUFSIZE		256
#define QTN_HW_BOARD_CFG_BIN		"qtn_hw_board_config.bin"
#define QTN_HW_BOARD_DB_BIN		"qtn_hw_board_db.bin"

#define QTN_BOARD_HW_CFG_START			(0)
#define QTN_BOARD_HW_CFG_ID			(1)
#define QTN_BOARD_HW_CFG_NAME			(2)
#define QTN_BOARD_HW_CFG_DDR_TYPE		(3)
#define QTN_BOARD_HW_CFG_DDR_SPEED		(4)
#define QTN_BOARD_HW_CFG_DDR_SIZE		(5)
#define QTN_BOARD_HW_CFG_EMAC0			(6)
#define QTN_BOARD_HW_CFG_EMAC1			(7)
#define QTN_BOARD_HW_CFG_PHY0_ADDR		(8)
#define QTN_BOARD_HW_CFG_PHY1_ADDR		(9)
#define QTN_BOARD_HW_CFG_SPI0			(10)
#define QTN_BOARD_HW_CFG_WIFI_HW		(11)
#define QTN_BOARD_HW_CFG_UART1			(12)
#define QTN_BOARD_HW_CFG_PCIE			(13)
#define QTN_BOARD_HW_CFG_RGMII_TIMING		(14)
#define QTN_BOARD_HW_CFG_LNA_GAIN		(15)
#define QTN_BOARD_HW_CFG_TX_ANT			(16)
#define QTN_BOARD_HW_CFG_FLASH_SIZE		(17)
#define QTN_BOARD_HW_CFG_TX_ANT_GAIN		(18)
#define QTN_BOARD_HW_CFG_LNA_GAIN_5DB		(19)/* For short range fix board */



#define RUN(args...) _run(__FUNCTION__, args)

struct board_hw_config_tlv{
	uint16_t t;
	char v[0];
};

char board_config_name[20];
board_cfg_t board_hw_config;
uint32_t flash_size = 0;

char * type2name[] = {
	"bc_start",
	"bc_hwconfig_id",
	"bc_config_name",
	"bc_ddr_type",
	"bc_ddr_speed",
	"bc_ddr_size",
	"bc_emac0",
	"bc_emac1",
	"bc_phy0_addr",
	"bc_phy1_addr",
	"bc_spi1_enable",
	"bc_wifi_hw",
	"bc_uart1",
	"bc_pcie",
	"bc_rgmii_timing",
	"bc_lna_gain",
	"bc_num_of_antenna",
	"bc_flash_cfg",
	"bc_tx_antenna_gain",
	"bc_ext_lna_gain_5db"
};

static board_cfg_t	g_default_board_cfg = {
	.bc_board_id	= QTN_RUBY_UNIVERSAL_BOARD_ID,
	.bc_name	= "default board",
	.bc_ddr_type	= DEFAULT_DDR_CFG,
	.bc_ddr_speed	= DEFAULT_DDR_SPEED,
	.bc_ddr_size	= DDR_AUTO,
	.bc_emac0	= EMAC_NOT_IN_USE,
	.bc_emac1	= EMAC_NOT_IN_USE,
	.bc_phy0_addr = EMAC_PHY_ADDR_SCAN,
	.bc_phy1_addr = EMAC_PHY_ADDR_SCAN,
	.bc_spi1	= SPI1_IN_USE,
	.bc_wifi_hw	= QTN_RUBY_WIFI_NONE,
	.bc_uart1	= UART1_NOT_IN_USE,
	.bc_rgmii_timing = CONFIG_ARCH_RGMII_DEFAULT,
	};

static int _run(const char* function_name, ...)
{
	va_list args;
	char cmdbuf[CMD_BUFSIZE];
	sprintf(cmdbuf, args);
	return run_command(cmdbuf, 0);
}

static uint32_t qtn_board_get_end(void)
{
	char tmpBuf[TMP_BUFSIZE];
	uint32_t addr;
	int i;
	if ((i = getenv_r("config_data_end", tmpBuf, sizeof(tmpBuf))) <= 0) {
		/* the new bootcfg data will be first entry in system */
		addr = BOOT_CFG_DEF_START;
	} else {
		tmpBuf[i]='\0';
		addr = simple_strtoul(tmpBuf, NULL, 16);
	}
	return addr;
}

static long qtn_board_get_env_val(char *env)
{
	char tmpBuf[TMP_BUFSIZE];
	long val = 0;
	int i;
	if ((i = getenv_r(env, tmpBuf, sizeof(tmpBuf))) <= 0) {
		val = -1;
	} else {
		tmpBuf[i]='\0';
		val = simple_strtol(tmpBuf, NULL, 0);
	}

	return val;
}

static uint32_t qtn_board_get_load_addr(void)
{
	char tmpBuf[TMP_BUFSIZE];
	uint32_t addr;
	int i;
	if ((i = getenv_r("loadaddr", tmpBuf, sizeof(tmpBuf))) <= 0) {
		/* the new bootcfg data will be first entry in system */
		addr = RUBY_DRAM_FLIP_BEGIN;
	} else {
		tmpBuf[i]='\0';
		addr = simple_strtoul(tmpBuf, NULL, 16);
	}
	return addr;
}

uchar * qtn_get_file_env_ptr(char *filename)
{
	int retval;
	uint32_t offset;
	char tmp[64], *ch;
	uchar *env_ptr = NULL;

	retval = getenv_r(filename, tmp, sizeof(tmp));
	if (retval < 0) {
		printf("File %s don't exist, please update two files to flash first\n", filename);
		return NULL;
	}

	if(strstr(tmp, "cfg") == NULL) {
		printf("value of parameter is error!\n");
		return NULL;
	}

	/* skip the string "cfg " */
	ch = tmp;
	while(*ch != '0') ch++;

	offset = simple_strtoul(ch, NULL, 16);
	env_ptr = env_get_addr(0);

	return (env_ptr + offset - sizeof(u32));	/* Because bootcfg driver have 4 bytes offset against actual offset*/
}

uchar * qtn_get_board_config_by_type(uint16_t bc_type)
{
	uchar *config_addr = NULL, *database = NULL;
	uint16_t tlv_cnt = 0;
	struct board_hw_config_tlv * tlv_tmp = NULL;
	uint8_t data_len = 0, strlen = 0;
	char buf[100];
	int i = 0;

	config_addr = qtn_get_file_env_ptr(QTN_HW_BOARD_CFG_BIN);
	database = qtn_get_file_env_ptr(QTN_HW_BOARD_DB_BIN);
	memcpy(&tlv_cnt, (uint16_t *)database, sizeof(uint16_t));

	for (i = 0; i < tlv_cnt; i++) {

		memcpy(buf, config_addr, sizeof(buf));
		tlv_tmp = (struct board_hw_config_tlv *)buf;
		strlen = (uint8_t)tlv_tmp->v[0];
		data_len = tlv_tmp->v[sizeof(uint8_t) + strlen];

		if (tlv_tmp->t == bc_type) {
			break;
		}
		config_addr = (config_addr + data_len +strlen + 2*sizeof(uint8_t) + sizeof(uint16_t));
	}
	return config_addr;
}

static int qtn_get_emac_set(void)
{
	char *emac_set_str = NULL;
	char *emac_index = NULL;
	uint32_t emac_set = 0;
	int retval = 0;

	emac_index = getenv("emac_index");
	emac_set_str = getenv("emac_set");

	if (emac_index != NULL && emac_set_str != NULL) {
		if (simple_strtoul(emac_index, NULL, 0) == 0) {

			emac_set = simple_strtoul(emac_set_str, NULL, 0);
			g_default_board_cfg.bc_emac0 = (int)emac_set;
		}else if (simple_strtoul(emac_index, NULL, 0) == 1) {

			emac_set = simple_strtoul(emac_set_str, NULL, 0);
			g_default_board_cfg.bc_emac1 = (int)emac_set;
		}
	} else {
		printf("Please setup emac setting correctly for tftp load file\n");
		retval = FAIL;
	}

	return retval;
}

static int qtn_get_ddr_set(void)
{
	char ddr_set_str[TMP_BUFSIZE];
	char *ddr_set_type = NULL;
	char *ddr_set_speed = NULL;
	char *ddr_set_size = NULL;
	//uint32_t emac_set = 0;
	int retval = 0;
	int i;

	i = getenv_r("ddr_set", ddr_set_str, sizeof(ddr_set_str));

	if (i > 0) {
		ddr_set_str[i] = '\0';
		ddr_set_type = strtok(ddr_set_str, ",");
		ddr_set_speed = strtok(NULL, ",");
		ddr_set_size = strtok(NULL, ",");

		if (ddr_set_type == NULL || ddr_set_speed == NULL || ddr_set_size == NULL) {
			goto INVALID_DDR_SET;
		}
		g_default_board_cfg.bc_ddr_type = (int)simple_strtoul(ddr_set_type, NULL, 0);
		g_default_board_cfg.bc_ddr_speed = (int)simple_strtoul(ddr_set_speed, NULL, 0);
		g_default_board_cfg.bc_ddr_size = (int)simple_strtoul(ddr_set_size, NULL, 0);

		return retval;
	}

INVALID_DDR_SET:
	printf("Please setup ddr setting correctly for tftp load file\n");
	retval = FAIL;

	return retval;
}

int board_hw_config_read(void)
{
	uchar *config_addr = NULL, *database = NULL;
	uint16_t tlv_cnt = 0;
	struct board_hw_config_tlv * tlv_tmp = NULL;
	uint8_t data_len = 0, strlen = 0;
	char buf[100];
	char string[50];
	char data[5];
	int i = 0, need_save = 0;
	int lna_gain = 0, antenna_number = 0, antenna_gain = 0, lna_gain_5db = 0;

	config_addr = qtn_get_file_env_ptr(QTN_HW_BOARD_CFG_BIN);
	database = qtn_get_file_env_ptr(QTN_HW_BOARD_DB_BIN);

	if (config_addr == NULL || database == NULL) {

		if (qtn_get_emac_set() < 0) {
			return FAIL;
		}

		if (qtn_get_ddr_set() < 0) {
			return FAIL;
		}


		memcpy(&board_hw_config, &g_default_board_cfg, sizeof(board_cfg_t));
		return SUCCESS;
	}

	memcpy(&tlv_cnt, (uint16_t *)database, sizeof(uint16_t));

	for (i = 0; i < tlv_cnt; i++) {

		memset(buf, 0, sizeof(buf));
		memcpy(buf, config_addr, sizeof(buf));
		tlv_tmp = (struct board_hw_config_tlv *)buf;

		strlen = (uint8_t)tlv_tmp->v[0];
		memset(string, 0 , sizeof(string));
		memcpy(string, &(tlv_tmp->v[1]), strlen);

		data_len = tlv_tmp->v[sizeof(uint8_t) + strlen];
		memset(data, 0, sizeof(data));
		memcpy(data, &(tlv_tmp->v[2*sizeof(uint8_t) +strlen]), data_len);

		switch(tlv_tmp->t) {
		case QTN_BOARD_HW_CFG_ID:
			memcpy(&(board_hw_config.bc_board_id), data, data_len);
			break;
		case QTN_BOARD_HW_CFG_NAME:
			memcpy(board_config_name, string, strlen);
			board_hw_config.bc_name =  board_config_name;
			break;
		case QTN_BOARD_HW_CFG_DDR_TYPE:
			memcpy(&(board_hw_config.bc_ddr_type), data, data_len);
			break;
		case QTN_BOARD_HW_CFG_DDR_SPEED:
			memcpy(&(board_hw_config.bc_ddr_speed), data, data_len);
			break;
		case QTN_BOARD_HW_CFG_DDR_SIZE:
			memcpy(&(board_hw_config.bc_ddr_size), data, data_len);
			break;
		case QTN_BOARD_HW_CFG_EMAC0:
			memcpy(&(board_hw_config.bc_emac0), data, data_len);
			break;
		case QTN_BOARD_HW_CFG_EMAC1:
			memcpy(&(board_hw_config.bc_emac1), data, data_len);
			break;
		case QTN_BOARD_HW_CFG_PHY0_ADDR:
			memcpy(&(board_hw_config.bc_phy0_addr), data, data_len);
			break;
		case QTN_BOARD_HW_CFG_PHY1_ADDR:
			memcpy(&(board_hw_config.bc_phy1_addr), data, data_len);
			break;
		case QTN_BOARD_HW_CFG_SPI0:
			memcpy(&(board_hw_config.bc_spi1), data, data_len);
			break;
		case QTN_BOARD_HW_CFG_WIFI_HW:
			memcpy(&(board_hw_config.bc_wifi_hw), data, data_len);
			break;
		case QTN_BOARD_HW_CFG_UART1:
			memcpy(&(board_hw_config.bc_uart1), data, data_len);
			break;
		case QTN_BOARD_HW_CFG_PCIE:
			memcpy(&(board_hw_config.bc_pcie), data, data_len);
			break;
		case QTN_BOARD_HW_CFG_RGMII_TIMING:
			memcpy(&(board_hw_config.bc_rgmii_timing), data, data_len);
			break;
		case QTN_BOARD_HW_CFG_FLASH_SIZE:
			memcpy(&flash_size, data, data_len);
			break;
		case QTN_BOARD_HW_CFG_LNA_GAIN:
			memcpy(&lna_gain, data, data_len);
			if (qtn_board_get_env_val("ext_lna_gain") != lna_gain) {
				RUN("setenv ext_lna_gain %d", lna_gain);
				need_save = 1;
			}
			break;
		case QTN_BOARD_HW_CFG_TX_ANT:
			memcpy(&antenna_number, data, data_len);
			if (qtn_board_get_env_val("antenna_num") != antenna_number) {
				RUN("setenv antenna_num %d", antenna_number);
				need_save = 1;
			}
			break;
		case QTN_BOARD_HW_CFG_TX_ANT_GAIN:
			memcpy(&antenna_gain, data, data_len);
			if (qtn_board_get_env_val("antenna_gain") != antenna_gain) {
				RUN("setenv antenna_gain %d", antenna_gain);
				need_save = 1;
			}
			break;
		case QTN_BOARD_HW_CFG_LNA_GAIN_5DB:
			memcpy(&lna_gain_5db, data, data_len);
			if ((int8_t)(qtn_board_get_env_val("ext_lna_bypass_gain") - 256 ) != (int8_t)(lna_gain_5db - 256)) {
				RUN("setenv ext_lna_bypass_gain %d", (int8_t)(lna_gain_5db - 256));
				need_save = 1;
			}
			break;
		default:
			break;
		}

		config_addr = (config_addr + data_len +strlen + 2*sizeof(uint8_t) + sizeof(uint16_t));
	}

	if (need_save == 1) {
		saveenv();
	}
	return 0;
}

int do_qtn_show_board_hw_config(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	uchar *config_addr = NULL, *database = NULL;
	uint16_t tlv_cnt = 0;
	struct board_hw_config_tlv * tlv_tmp = NULL;
	uint8_t data_len = 0, strlen = 0;
	char buf[100];
	char string[50];
	char data[5];
	int i = 0;

	config_addr = qtn_get_file_env_ptr(QTN_HW_BOARD_CFG_BIN);
	database = qtn_get_file_env_ptr(QTN_HW_BOARD_DB_BIN);

	if (config_addr == NULL || database == NULL) {
		return 0;
	}

	memcpy(&tlv_cnt, (uint16_t *)database, sizeof(uint16_t));

	printf("##############current board Hardware configuration########################\n");
	printf("Total %d configuration types\n", tlv_cnt);
	for (i = 0; i < tlv_cnt; i++) {

		memset(buf, 0, sizeof(buf));
		memcpy(buf, config_addr, sizeof(buf));
		tlv_tmp = (struct board_hw_config_tlv *)buf;

		strlen = (uint8_t)tlv_tmp->v[0];
		memset(string, 0 , sizeof(string));
		memcpy(string, &(tlv_tmp->v[1]), strlen);

		data_len = tlv_tmp->v[sizeof(uint8_t) + strlen];
		memset(data, 0, sizeof(data));
		memcpy(data, &(tlv_tmp->v[2*sizeof(uint8_t) + strlen]), data_len);

		if (tlv_tmp->t != 0) {
			printf("%d: %s:\n",i, type2name[tlv_tmp->t]);

			if (data_len == 0) {
				printf("  %s\n", string);
			} else {
				printf("  %s;0x%08x\n",
						string,
						(data_len == 1) ?
						data[0] : ((data_len == 2) ?
						*(uint16_t *)data :
						*(uint32_t *)data));
			}
		}
		config_addr = (config_addr + data_len + strlen + 2*sizeof(uint8_t) + sizeof(uint16_t));
	}

	return 0;
}

int do_qtn_show_board_hw_db(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	uchar *config_addr = NULL, *database = NULL;
	uint16_t tlv_cnt = 0, v_cnt = 0;
	struct board_hw_config_tlv * tlv_tmp = NULL;
	uint8_t data_len = 0, strlen = 0;
	char buf[500];
	char string[50];
	char data[5];
	int i = 0, j = 0;
	uint8_t total_strlen =0, total_datalen = 0;

	database = qtn_get_file_env_ptr(QTN_HW_BOARD_DB_BIN);

	if (database == NULL) {
		return 0;
	}

	memcpy(&tlv_cnt, (uint16_t *)database, sizeof(uint16_t));
	database += sizeof(uint16_t);

	printf("##############current board Hardware database########################\n");
	printf("Total %d configuration types\n", tlv_cnt);
	for (i = 0; i < tlv_cnt; i++) {

		total_strlen =0;
		total_datalen = 0;
		memset(buf, 0, sizeof(buf));
		memcpy(buf, database, sizeof(buf));
		tlv_tmp = (struct board_hw_config_tlv *)buf;
		v_cnt = *(uint16_t *)tlv_tmp->v;

		printf("%d: %s:\n",i, type2name[tlv_tmp->t]);
		if (v_cnt >= 100)
			break;
		config_addr = (uchar *)&tlv_tmp->v[2];
		for (j = 0; j < v_cnt; j++) {
			strlen = config_addr[0];
			memset(string, 0, sizeof(string));
			memcpy(string, &(config_addr[1]), strlen);

			data_len = config_addr[sizeof(uint8_t) + strlen];
			memset(data, 0, sizeof(data));
			memcpy(data, &(config_addr[strlen + 2*sizeof(uint8_t)]), data_len);
			if (data_len == 0) {
				if (j == (v_cnt -1)) {
					printf("  %s\n", string);
				} else {
					printf("  %s;\n", string);
				}

			} else {
				if (j == v_cnt -1) {
				printf("  %s,0x%08x\n",
						string, (data_len == 1) ? data[0] : ((data_len == 2) ? *(uint16_t *)data : *(uint32_t *)data));
				} else {
				printf("  %s,0x%08x;\n",
						string, (data_len == 1) ? data[0] : ((data_len == 2) ? *(uint16_t *)data : *(uint32_t *)data));
				}
			}

			config_addr = config_addr + strlen + data_len + 2*sizeof(uint8_t);
			total_strlen += strlen;
			total_datalen += data_len;

		}

		database = (database + total_strlen + total_datalen + v_cnt*(2*sizeof(uint8_t)) + 2*sizeof(uint16_t));
	}
	return 0;
}

int do_qtn_upload_file(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	if (argc < 2) {
		printf("Help:\n");
		printf("qtn_upload_file <file_name>\n");
		return 0;
	}

	char *file_name = argv[1];
	uint32_t mem_addr = qtn_board_get_load_addr();
	int retval = 0;
	uchar *data = NULL;

	retval = RUN("tftpboot %s", file_name);

	if ((qtn_board_get_end() + NetBootFileXferSize) > BOOT_CFG_DATA_SIZE) {
		printf("error - len out of range");
		return 0;
	}

	if (retval >= 0 && NetBootFileXferSize > 0) {
		retval = RUN("setenv %s cfg 0x%08x 0x%08x", file_name, (qtn_board_get_end()), NetBootFileXferSize);
		if (retval >= 0) {
			retval = RUN("setenv config_data_end 0x%08x", (qtn_board_get_end() + NetBootFileXferSize + sizeof(u32))); /* Because bootcfg driver have 4 bytes offset against actual offset*/
			if (retval < 0) {
				printf("setenv config_data_end error\n");
				return 0;
			}
		} else {
			printf("setenv %s error\n", file_name);
			return 0;
		}
	} else {
		printf("TFTP file size error, please try again\n");
		return 0;
	}

	data = qtn_get_file_env_ptr(file_name);
	if (data != NULL) {
		memcpy((data), (void *)mem_addr, NetBootFileXferSize);
	} else {
		printf("error data address\n");
		return 0;
	}
	env_crc_update();
	saveenv();
	return 0;
}

U_BOOT_CMD(qtn_upload_file, CONFIG_SYS_MAXARGS, 0, do_qtn_upload_file,
		"Upload file from memory to flash",
		"Quantenna universal board config. Attempts to upload file from memory to flash\n"
 );

U_BOOT_CMD(qtn_show_board_config, CONFIG_SYS_MAXARGS, 0, do_qtn_show_board_hw_config,
			  "Show board hw configuration",
			  "Quantenna universal board config.\n"
);
U_BOOT_CMD(qtn_show_board_database, CONFIG_SYS_MAXARGS, 0, do_qtn_show_board_hw_db,
			  "Show board hw configuration database content",
			  "Quantenna universal board config.\n"
);


