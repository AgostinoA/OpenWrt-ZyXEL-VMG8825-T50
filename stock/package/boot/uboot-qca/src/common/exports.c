#include <common.h>
#include <exports.h>
#include <spi.h>
#include <i2c.h>

DECLARE_GLOBAL_DATA_PTR;

__attribute__((unused)) static void dummy(void)
{
}

unsigned long get_version(void)
{
	return XF_VERSION;
}

#define EXPORT_FUNC(f, a, x, ...)  gd->jt->x = f;

#ifndef CONFIG_PHY_AQUANTIA
# define mdio_get_current_dev		dummy
# define phy_find_by_mask		dummy
# define mdio_phydev_for_ethname	dummy
# define miiphy_set_current_dev		dummy
#endif

void jumptable_init(void)
{
	gd->jt = malloc(sizeof(struct jt_funcs));
#include <_exports.h>
#ifdef CONFIG_ZYXEL_ZLOADER
#define SETUP_JUMP_TBL(x)	gd->jt->x = x
	SETUP_JUMP_TBL(memcmp);
	SETUP_JUMP_TBL(memset);
	SETUP_JUMP_TBL(memcpy);
    SETUP_JUMP_TBL(strcpy);
#if defined(CONFIG_CMD_NET)
	SETUP_JUMP_TBL(do_tftpb);
	SETUP_JUMP_TBL(eth_init);
	SETUP_JUMP_TBL(eth_rx);
	SETUP_JUMP_TBL(eth_halt);
//	SETUP_JUMP_TBL(NetSetHandler);
#endif
#ifdef CONFIG_ZYXEL_MULTIBOOT
//	SETUP_JUMP_TBL(NetPacketInit);
	SETUP_JUMP_TBL(getNetBootFileXferSize);
  #ifdef CONFIG_LZMA
//	SETUP_JUMP_TBL(lzmaBuffToBuffDecompress);
  #endif
#endif
#ifdef CONFIG_NET_MULTI
	SETUP_JUMP_TBL(eth_set_current);
#endif
	SETUP_JUMP_TBL(strlen);
	SETUP_JUMP_TBL(strncmp);
	SETUP_JUMP_TBL(sprintf);
	SETUP_JUMP_TBL(do_bootm);
	SETUP_JUMP_TBL(cli_readline);
	SETUP_JUMP_TBL(get_user_command_buffer);
    SETUP_JUMP_TBL(zflash_init);
    SETUP_JUMP_TBL(zflash_read);
    SETUP_JUMP_TBL(zflash_write);
    SETUP_JUMP_TBL(zflash_erase);
#ifdef CONFIG_CMD_NAND
    SETUP_JUMP_TBL(znand_init);
    SETUP_JUMP_TBL(znand_read);
    SETUP_JUMP_TBL(znand_write);
    SETUP_JUMP_TBL(znand_erase);
#endif
    SETUP_JUMP_TBL(saveenv);
    SETUP_JUMP_TBL(do_run);
    SETUP_JUMP_TBL(do_reset);
    SETUP_JUMP_TBL(flush_cache);
    SETUP_JUMP_TBL(image_check_hcrc);
    SETUP_JUMP_TBL(image_check_dcrc);
    SETUP_JUMP_TBL(clear_ctrlc);
    SETUP_JUMP_TBL(configure_pio);
    SETUP_JUMP_TBL(set_pio);
    SETUP_JUMP_TBL(get_pio);
    SETUP_JUMP_TBL(max_pio_num);
#endif /* #ifdef CONFIG_ZYXEL_ZLOADER */
}
