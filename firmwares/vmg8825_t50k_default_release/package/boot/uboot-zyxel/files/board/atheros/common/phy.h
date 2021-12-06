#ifndef _PHY_H
#define _PHY_H

#include <config.h>

#if defined(CFG_ATH_SWAP_ETHACT)
#define ath_gmac_unit2name(_unit) (_unit ?  "eth0" : "eth1")
#else
#define ath_gmac_unit2name(_unit) (_unit ?  "eth1" : "eth0")
#endif

extern int ath_gmac_miiphy_read(char *devname, uint32_t phaddr, uint8_t reg);
extern int ath_gmac_miiphy_write(char *devname, uint32_t phaddr, uint8_t reg, uint16_t data);

#define phy_reg_read(base, addr, reg)	\
	ath_gmac_miiphy_read(ath_gmac_unit2name(base), addr, reg)

#define phy_reg_write(base, addr, reg, data)	\
	ath_gmac_miiphy_write(ath_gmac_unit2name(base), addr, reg, data)

#endif
