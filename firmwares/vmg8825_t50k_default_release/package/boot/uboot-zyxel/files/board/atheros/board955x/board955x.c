#include <common.h>
#include <command.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <config.h>
#include <version.h>
#include <atheros.h>

extern int ath_ddr_initial_config(uint32_t refresh);
extern int ath_ddr_find_size(void);

#ifdef COMPRESSED_UBOOT
#	define prmsg(...)
#	define args		char *s
#	define board_str(a)	do {			\
	char ver[] = "0";				\
	strcpy(s, a " - Scorpion 1.");			\
	ver[0] += ath_reg_rd(RST_REVISION_ID_ADDRESS)	\
						& 0xf;	\
	strcat(s, ver);					\
} while (0)
#else
#	define prmsg	printf
#	define args		void
#	define board_str(a)				\
	printf(a " - Scorpion 1.%d\n", ath_reg_rd		\
			(RST_REVISION_ID_ADDRESS) & 0xf)
#endif

void
ath_usb1_initial_config(void)
{
#define unset(a)	(~(a))

	ath_reg_wr_nf(SWITCH_CLOCK_SPARE_ADDRESS,
		ath_reg_rd(SWITCH_CLOCK_SPARE_ADDRESS) |
		SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_SET(5));
	udelay(1000);

	ath_reg_rmw_set(RST_RESET_ADDRESS,
				RST_RESET_USB_PHY_SUSPEND_OVERRIDE_SET(1));
	udelay(1000);
	ath_reg_rmw_clear(RST_RESET_ADDRESS, RST_RESET_USB_PHY_RESET_SET(1));
	udelay(1000);
	ath_reg_rmw_clear(RST_RESET_ADDRESS, RST_RESET_USB_PHY_ARESET_SET(1));
	udelay(1000);
	ath_reg_rmw_clear(RST_RESET_ADDRESS, RST_RESET_USB_HOST_RESET_SET(1));
	udelay(1000);

	ath_reg_rmw_clear(RST_RESET_ADDRESS, RST_RESET_USB_PHY_PLL_PWD_EXT_SET(1));
	udelay(10);

	ath_reg_rmw_set(RST_RESET2_ADDRESS, RST_RESET2_USB1_EXT_PWR_SEQ_SET(1));
	udelay(10);
}

void
ath_usb2_initial_config(void)
{
	if (is_drqfn()) {
		return;
	}

	ath_reg_rmw_set(RST_RESET2_ADDRESS, RST_RESET2_USB2_MODE_SET(1));
	udelay(10);
	ath_reg_rmw_set(RST_RESET2_ADDRESS,
				RST_RESET2_USB_PHY2_SUSPEND_OVERRIDE_SET(1));
	udelay(1000);
	ath_reg_rmw_clear(RST_RESET2_ADDRESS, RST_RESET2_USB_PHY2_RESET_SET(1));
	udelay(1000);
	ath_reg_rmw_clear(RST_RESET2_ADDRESS, RST_RESET2_USB_PHY2_ARESET_SET(1));
	udelay(1000);
	ath_reg_rmw_clear(RST_RESET2_ADDRESS, RST_RESET2_USB_HOST2_RESET_SET(1));
	udelay(1000);

	ath_reg_rmw_clear(RST_RESET2_ADDRESS, RST_RESET2_USB_PHY2_PLL_PWD_EXT_SET(1));
	udelay(10);

	ath_reg_rmw_set(RST_RESET2_ADDRESS, RST_RESET2_USB2_EXT_PWR_SEQ_SET(1));
	udelay(10);
}

void ath_gpio_config(void)
{
#if defined(CONFIG_BOARD_NBG6716) || defined(CONFIG_BOARD_NBG6616)
	/* set GPIO 4,12,13,15,16,17,18,19 as output */
	ath_reg_rmw_clear(GPIO_OE_ADDRESS, \
		((1 << 4)|(1 << 12)|(1 << 13)|(1 << 15)|(1 << 16)|(1 << 17)|(1 << 18)|(1 << 19)));
	ath_reg_rmw_clear(GPIO_OUT_FUNCTION1_ADDRESS, GPIO_OUT_FUNCTION1_ENABLE_GPIO_4_MASK);
	ath_reg_rmw_clear(GPIO_OUT_FUNCTION3_ADDRESS, \
		(GPIO_OUT_FUNCTION3_ENABLE_GPIO_12_MASK| \
		 GPIO_OUT_FUNCTION3_ENABLE_GPIO_13_MASK| \
		 GPIO_OUT_FUNCTION3_ENABLE_GPIO_15_MASK));
	ath_reg_rmw_clear(GPIO_OUT_FUNCTION4_ADDRESS, \
		(GPIO_OUT_FUNCTION4_ENABLE_GPIO_16_MASK| \
		 GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_MASK| \
		 GPIO_OUT_FUNCTION4_ENABLE_GPIO_18_MASK| \
		 GPIO_OUT_FUNCTION4_ENABLE_GPIO_19_MASK));	
	ath_reg_wr_nf(GPIO_SET_ADDRESS, \
		((1 << 4)|(1 << 12)|(1 << 13)|(1 << 15)|(1 << 16)|(1 << 17)|(1 << 18)|(1 << 19)));
  #if defined(CONFIG_BOARD_NBG6616)
	/* disable JTAG */
	ath_reg_rmw_set(GPIO_FUNCTION_ADDRESS, 2);
	/* Set GPIO 0 as output */
	ath_reg_rmw_clear(GPIO_OE_ADDRESS, 1);
	/* turn off USB2 LED */
	ath_reg_wr_nf(GPIO_SET_ADDRESS, 1);
  #endif
#else
	/* disable the CLK_OBS on GPIO_4 and set GPIO4 as input */
	ath_reg_rmw_clear(GPIO_OE_ADDRESS, (1 << 4));
	ath_reg_rmw_clear(GPIO_OUT_FUNCTION1_ADDRESS, GPIO_OUT_FUNCTION1_ENABLE_GPIO_4_MASK);
	ath_reg_rmw_set(GPIO_OUT_FUNCTION1_ADDRESS, GPIO_OUT_FUNCTION1_ENABLE_GPIO_4_SET(0x80));
	ath_reg_rmw_set(GPIO_OE_ADDRESS, (1 << 4));
	/* Set GPIO 13 as input for LED functionality to be OFF during bootup */
	ath_reg_rmw_set(GPIO_OE_ADDRESS, (1 << 13));
	/* Turn off JUMPST_LED and 5Gz LED during bootup */
	ath_reg_rmw_set(GPIO_OE_ADDRESS, (1 << 15));
	ath_reg_rmw_set(GPIO_OE_ADDRESS, (1 << 12));
#endif
}

int
ath_mem_config(void)
{
	unsigned int type, reg32, *tap;
	extern uint32_t *ath_ddr_tap_cal(void);

#if !defined(CONFIG_ATH_EMULATION)

#if !(defined(CONFIG_ATH_NAND_BR)||defined(CONFIG_SKIP_LOWLEVEL_INIT))
	type = ath_ddr_initial_config(CFG_DDR_REFRESH_VAL);

	tap = ath_ddr_tap_cal();
//	prmsg("tap = 0x%p\n", tap);

	tap = (uint32_t *)0xbd007f10;
//	prmsg("Tap (low, high) = (0x%x, 0x%x)\n", tap[0], tap[1]);

	tap = (uint32_t *)TAP_CONTROL_0_ADDRESS;
//	prmsg("Tap values = (0x%x, 0x%x, 0x%x, 0x%x)\n", \
		tap[0], tap[2], tap[2], tap[3]);

	/* Take WMAC out of reset */
	reg32 = ath_reg_rd(RST_RESET_ADDRESS);
	reg32 = reg32 & ~RST_RESET_RTC_RESET_SET(1);
	ath_reg_wr_nf(RST_RESET_ADDRESS, reg32);
#endif

#if 1 /* must do it because linux kernel(atheros SDK) doesn't configure USB interface */
	ath_usb1_initial_config();
	ath_usb2_initial_config();
#endif
	ath_gpio_config();
#endif /* !defined(CONFIG_ATH_EMULATION) */

	return ath_ddr_find_size();
}

phys_size_t initdram(int board_type)
{
	return (ath_mem_config());
}

int	checkboard(args)
{
	board_str(CONFIG_BOARD_NAME);
	return 0;
}
