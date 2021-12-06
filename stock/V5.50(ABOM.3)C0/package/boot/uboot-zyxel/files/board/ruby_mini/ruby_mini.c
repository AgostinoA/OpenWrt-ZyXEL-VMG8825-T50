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

#include <common.h>
#include <config.h>
#include <command.h>
#include <linux/ctype.h>
#include <linux/types.h>
#include <asm/types.h>
#include <asm/cache.h>
#include <net.h>
#include <timestamp.h>

#include "ruby.h"
#include "board_cfg.h"
#include <shared_defs.h>
#include "ruby_board_cfg.h"
#include "ruby_board_db.h"
#include "ruby_version.h"

gd_t *gd;
gd_t *global_data;

unsigned long load_addr = RUBY_SRAM_BEGIN;

/*
 * tftp environment variables (ipaddr, serverip, bootfile) are set dynamically
 * before attempting tftp. They are cleared before attempting bootp. Bootp will
 * not work if ipaddr is set, as the udp receive routines reject packets whose
 * destination address does not match ipaddr
 */
uchar __env[CONFIG_ENV_SIZE] = {
	"ethaddr="	MKSTR(CONFIG_ETHADDR)	"\0"
	"ipaddr="	MKSTR(CONFIG_IPADDR)	"\0"
	"serverip="	MKSTR(CONFIG_SERVERIP)	"\0"
	"bootfile="	MKSTR(CONFIG_BOOTFILE)	"\0"
	"\0"
};

// rgmii daughter board
static const board_cfg_t mini_board_conf = {
	.bc_emac0	= EMAC_NOT_IN_USE,
	.bc_emac1	= EMAC_IN_USE | EMAC_PHY_FORCE_1000MB | EMAC_PHY_NOT_IN_USE,
	.bc_phy0_addr	= EMAC_PHY_ADDR_SCAN,
	.bc_phy1_addr	= EMAC_PHY_ADDR_SCAN,
	.bc_rgmii_timing = 0x0,
};

int console_assign(int file, char *devname) {
	return 0;
}

int getc(void) {
	return 0;
}

void putc(char c) {
	serial_putc(c);
}

void puts(const char *s) {
	serial_puts(s);
}

void printf (const char *fmt, ...)
{
	va_list args;
	uint i;
	char printbuffer[256];

	va_start (args, fmt);

	/* For this to work, printbuffer must be larger than
	 * anything we ever want to print.
	 */
	i = vsprintf (printbuffer, fmt, args);
	va_end (args);

	/* Print the string */
	puts (printbuffer);
}

void vprintf (const char *fmt, va_list args)
{
	uint i;
	char printbuffer[256];

	/* For this to work, printbuffer must be larger than
	 * anything we ever want to print.
	 */
	i = vsprintf (printbuffer, fmt, args);

	/* Print the string */
	puts (printbuffer);
}

void show_boot_progress(int status)
{
	printf("Boot reached stage %d\n", status);
}

uchar env_get_char (int index)
{
	return __env[index];
}

uchar *env_get_addr (int index)
{
	return &__env[index];
}

void env_crc_update(void) {}

int cpu_init(void)
{
	disable_interrupts();
	return 0;
}

static void board_global_data_init(void)
{
	DECLARE_GLOBAL_DATA_PTR;
	gd->cpu_clk = RUBY_FIXED_CPU_CLK;
	gd->bus_clk = RUBY_FIXED_DEV_CLK;
	gd->baudrate = RUBY_SERIAL_BAUD;
	gd->bd->bi_boot_params = 0x0;
}

int board_init(void)
{
	board_global_data_init();
	board_serial_init();
	board_timer_init();
	return 0;
}

int  env_init(void)
{
	gd->env_addr  = (ulong)&__env[0];
	gd->env_valid = 1;
	return 0;
}

int console_init_f(void)
{
	gd->have_console = 0;
	return 0;
}

typedef int (init_fnc_t) (void);
init_fnc_t *init_sequence[] = {
	cpu_init,		/* cpu specific initialisations*/
	board_init,
	serial_init,            /* serial communications setup */
	env_init,		/* intialise environment */
	console_init_f,         /* stage 1 init of console */
	NULL,
};

void __attribute__ ((noreturn)) hang(void)
{
	board_reset("hang called\n");
}

int ctrlc(void)
{
	return 0;
}

int had_ctrlc(void)
{
	return 0;
}

int cmd_usage(cmd_tbl_t *cmdtp)
{
	return 0;
}

void *ar8236_init(unsigned long baseAddr, unsigned long phy_addr)
{
	return NULL;
}

void *ar8237_init(unsigned long baseAddr, unsigned long phy_addr)
{
	return NULL;
}

int board_config(int board_id, int parameter)
{
	int* ptr = (int *)&mini_board_conf;
	return ptr[parameter];
}

void print_size (phys_size_t s, const char * c) {}

void do_bootm(void){}

static void get_stage2(void)
{
	uint32_t method_used;
	int ret = get_stage2_image(get_early_flash_config(TEXT_BASE)->method, &method_used);

	if (ret == 0) {
		void (*jump_stage2)(void) = (void*)load_addr;
		struct early_flash_config *stage2ef = get_early_flash_config(load_addr);

		/* provide a boot method, ip and server to 2nd stage u-boot */
		stage2ef->method = method_used;
		stage2ef->ipaddr = NetOurIP;
		stage2ef->serverip = NetServerIP;

		eth_halt();

		flush_and_inv_dcache_all();
		invalidate_icache_all();

		jump_stage2();
	}
}

void start_arcboot(void)
{
	DECLARE_GLOBAL_DATA_PTR;
	static gd_t gd_data;
	static bd_t bd_data;
	init_fnc_t **init_fnc_ptr;

	gd = global_data = &gd_data;
	gd->bd = &bd_data;
	gd->bd->bi_board_id = 0;

	for (init_fnc_ptr = init_sequence; *init_fnc_ptr; ++init_fnc_ptr) {
		if ((*init_fnc_ptr)() != 0) {
			hang();
		}
	}

	printf("Quantenna Mini U-Boot\n");
	printf("Version: %s Built: %s at %s\n",
			RUBY_UBOOT_VERSION, U_BOOT_DATE, U_BOOT_TIME);

#if defined(CONFIG_CMD_NET)
	/*IP Address */
	gd->bd->bi_ip_addr = getenv_IPaddr ("ipaddr");
	/* MAC Address */
	{
		int i;
		ulong reg;
		char *s, *e;
		char tmp[64];
		i = getenv_r ("ethaddr", tmp, sizeof(tmp));
		s = (i > 0) ? tmp : NULL;
		for (reg = 0; reg < 6; ++reg) {
			gd->bd->bi_enetaddr[reg] = s ? simple_strtoul (s, &e, 16) : 0;
			if (s) {
				s = (*e) ? e + 1 : e;
			}
		}
	}
	/* Boot file */
	{
		char *s;
		if ((s = getenv("bootfile")) != NULL) {
			copy_filename(BootFile, s, sizeof(BootFile));
		}
	}
#endif

#ifdef CONFIG_CMD_NET
	eth_initialize(gd->bd);
#endif
	qtn_parse_early_flash_config(1);

	get_stage2();

	board_reset("get_stage2 returned");
}


