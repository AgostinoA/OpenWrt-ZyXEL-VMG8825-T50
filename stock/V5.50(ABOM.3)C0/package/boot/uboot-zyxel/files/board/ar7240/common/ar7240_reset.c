#include <common.h>
#include <asm/addrspace.h>
#include <ar7240_soc.h>

void ar7240_cpu_reset(void)
{
	for (;;) {
#ifdef CONFIG_WASP
		if (ar7240_reg_rd(AR7240_REV_ID) & 0xf) {
			ar7240_reg_wr(AR7240_RESET,
				(AR7240_RESET_FULL_CHIP | AR7240_RESET_DDR));
		} else {
			/*
			 * WAR for full chip reset spi vs. boot-rom selection
			 * bug in wasp 1.0
			 */
			ar7240_reg_wr (AR7240_GPIO_OE,
				ar7240_reg_rd(AR7240_GPIO_OE) & (~(1 << 17)));
		}
#else
		ar7240_reg_wr(AR7240_RESET,
			(AR7240_RESET_FULL_CHIP | AR7240_RESET_DDR));
#endif
	}
}

