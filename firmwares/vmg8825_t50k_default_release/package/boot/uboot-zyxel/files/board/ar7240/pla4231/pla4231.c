#include <common.h>
#include <command.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <config.h>
#include <version.h>
#include "ar7240_soc.h"

extern int wasp_ddr_initial_config(uint32_t refresh);
extern int ar7240_ddr_find_size(void);

#ifdef COMPRESSED_UBOOT
#	define prmsg(...)
#else
#	define prmsg	printf
#endif

void _machine_restart(void)
{
    ar7240_cpu_reset();
}

void
wasp_usb_initial_config(void)
{
#define unset(a)	(~(a))

	if ((ar7240_reg_rd(WASP_BOOTSTRAP_REG) & WASP_REF_CLK_25) == 0) {
		ar7240_reg_wr_nf(AR934X_SWITCH_CLOCK_SPARE,
			ar7240_reg_rd(AR934X_SWITCH_CLOCK_SPARE) |
			SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_SET(2));
	} else {
		ar7240_reg_wr_nf(AR934X_SWITCH_CLOCK_SPARE,
			ar7240_reg_rd(AR934X_SWITCH_CLOCK_SPARE) |
			SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_SET(5));
	}

	udelay(1000);
	ar7240_reg_wr(AR7240_RESET,
		ar7240_reg_rd(AR7240_RESET) |
		RST_RESET_USB_PHY_SUSPEND_OVERRIDE_SET(1));
	udelay(1000);
	ar7240_reg_wr(AR7240_RESET,
		ar7240_reg_rd(AR7240_RESET) &
		unset(RST_RESET_USB_PHY_RESET_SET(1)));
	udelay(1000);
	ar7240_reg_wr(AR7240_RESET,
		ar7240_reg_rd(AR7240_RESET) &
		unset(RST_RESET_USB_PHY_ARESET_SET(1)));
	udelay(1000);
	ar7240_reg_wr(AR7240_RESET,
		ar7240_reg_rd(AR7240_RESET) &
		unset(RST_RESET_USB_HOST_RESET_SET(1)));
	udelay(1000);
	if ((ar7240_reg_rd(AR7240_REV_ID) & 0xf) == 0) {
		/* Only for WASP 1.0 */
		ar7240_reg_wr(0xb8116c84 ,
			ar7240_reg_rd(0xb8116c84) & unset(1<<20));
	}
}

void wasp_gpio_config(void)
{
#if defined(CONFIG_ZYXEL_ZLOADER) && defined(CONFIG_BOARD_PLA4231)
	#include <zgpio.h>
	extern int ar7240_configure_pio(int pio, int dir, unsigned char out_type);
	/* Initial GPIO for internal switch LED of port1 & port2 */
	ar7240_configure_pio(SWITCH_PORT1_LED_GPIO_NO, ZGPIO_CONFIG_OUTPUT, 42);
	ar7240_configure_pio(SWITCH_PORT2_LED_GPIO_NO, ZGPIO_CONFIG_OUTPUT, 43);
#else
        /*  Enable switch port1 & port2 LED on GPIO 20 & 19 */
    ar7240_reg_wr (AR7240_GPIO_FUNC4, ((ar7240_reg_rd(AR7240_GPIO_FUNC4) & 0x00ffffff)) | 0x2b000000);
    ar7240_reg_wr (AR7240_GPIO_FUNC5, ((ar7240_reg_rd(AR7240_GPIO_FUNC5) & 0xffffff00)) | 0x2a);
    ar7240_reg_wr (AR7240_GPIO_OE, (ar7240_reg_rd(AR7240_GPIO_OE) & 0xffe7ffff));
#endif
#if 0
	/* Disable clock obs */
	ar7240_reg_wr (AR7240_GPIO_FUNC, (ar7240_reg_rd(AR7240_GPIO_FUNC) & 0xffe7e0ff));
	/* Enable eth Switch LEDs */
#ifdef CONFIG_K31
	ar7240_reg_wr (AR7240_GPIO_FUNC, (ar7240_reg_rd(AR7240_GPIO_FUNC) | 0xd8));
#else
	ar7240_reg_wr (AR7240_GPIO_FUNC, (ar7240_reg_rd(AR7240_GPIO_FUNC) | 0xfa));
#endif
#endif
}

void ath_set_tuning_caps(void)
{
	typedef struct {
		u_int8_t	pad[0x28],
				params_for_tuning_caps[2],
				featureEnable;
	} __attribute__((__packed__)) ar9300_eeprom_t;

	ar9300_eeprom_t	*eep = (ar9300_eeprom_t *)WLANCAL;
	uint32_t	val;


	val = 0;
	/* checking feature enable bit 6 and caldata is valid */
	if ((eep->featureEnable & 0x40) && (eep->pad[0x0] != 0xff)) {
		/* xtal_capin -bit 17:23 and xtag_capout -bit 24:30*/
		val = (eep->params_for_tuning_caps[0] & 0x7f) << 17;
		val |= (eep->params_for_tuning_caps[0] & 0x7f) << 24;
	} else {
		/* default when no caldata available*/
		/* checking clock in bit 4 */
		if (ar7240_reg_rd(RST_BOOTSTRAP_ADDRESS) & 0x10) {
			val = (0x1020 << 17);  /*default 0x2040 for 40Mhz clock*/
		} else {
			val = (0x2040 << 17); /*default 0x4080 for 25Mhz clock*/
		}
	}
	val |= (ar7240_reg_rd(XTAL_ADDRESS) & (((1 << 17) - 1) | (1 << 31)));
	ar7240_reg_wr(XTAL_ADDRESS, val);
	//prmsg("Setting 0xb8116290 to 0x%x\n", val);
	prmsg("(XTAL=0x%x) ", val);
	return;
}

phys_size_t wasp_mem_config(void)
{
	unsigned int type, reg32;

	type = wasp_ddr_initial_config(CFG_DDR_REFRESH_VAL);

	/* Take WMAC out of reset */
	reg32 = ar7240_reg_rd(AR7240_RESET);
	reg32 = reg32 &  ~AR7240_RESET_WMAC;
	ar7240_reg_wr_nf(AR7240_RESET, reg32);

	/* Switching regulator settings */
	ar7240_reg_wr_nf(0x18116c40, 0x633c8176); /* AR_PHY_PMU1 */
#if !defined(CONFIG_ATH_NAND_FL)
	if (ar7240_reg_rd(AR7240_REV_ID) & 0xf) {
		if (type == 2) {
			// ddr1
			ar7240_reg_wr_nf(0x18116c44, 0x10000000); /* AR_PHY_PMU2 */
		} else {
			// ddr2 & sdram
			ar7240_reg_wr_nf(0x18116c44, 0x10380000); /* AR_PHY_PMU2 */
		}
	} else {
		ar7240_reg_wr_nf(0x18116c44, 0x10380000); /* AR_PHY_PMU2 */
	}
#endif

	wasp_usb_initial_config();

	wasp_gpio_config();

	ath_set_tuning_caps(); /* Needed here not to mess with Ethernet clocks */ 

	reg32 = ar7240_ddr_find_size();

	return reg32;
}

phys_size_t initdram(int board_type)
{
	return (wasp_mem_config());
}

int	checkboard(void)
{
	puts("Board: " CONFIG_BOARD_NAME "\n");
	return 0;
}
