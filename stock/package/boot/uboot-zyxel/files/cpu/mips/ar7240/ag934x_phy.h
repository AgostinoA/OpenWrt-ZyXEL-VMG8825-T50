#ifndef _AG7240_PHY_H
#define _AG7240_PHY_H

static inline void ag7240_phy_setup(int unit)
{
#ifdef CONFIG_AR7242_S16_PHY
    if ((is_ar7242() || is_wasp()) && (unit==0)) {
        athrs16_phy_setup(unit);
    } else
#endif
#ifdef CONFIG_ATHRS17_PHY
    if (unit == 0) {
        athrs17_phy_setup(unit);
    } else
#endif
    {
#ifdef CFG_ATHRS27_PHY
        athrs27_phy_setup(unit);
#endif
#ifdef CFG_ATHRS26_PHY
        athrs26_phy_setup(unit);
#endif
#if defined(CONFIG_F1E_PHY) || defined(CONFIG_F2E_PHY)
        athr_phy_setup(unit);
#endif
#ifdef CONFIG_VIR_PHY
        athr_vir_phy_setup(unit);
#endif

    }
}

static inline void ag7240_phy_link(int unit, u32 *link)
{
#ifdef CONFIG_AR7242_S16_PHY
    if ((is_ar7242() || is_wasp()) && (unit==0)) {
         *link = athrs16_phy_is_up(unit);
    } else
#endif
#ifdef CONFIG_ATHRS17_PHY
    if (unit == 0) {
         *link = athrs17_phy_is_up(unit);
    } else
#endif
    {
#ifdef CFG_ATHRS27_PHY
         *link = athrs27_phy_is_up(unit);
#endif
#ifdef CFG_ATHRS26_PHY
         *link = athrs26_phy_is_up(unit);
#endif
#if defined(CONFIG_F1E_PHY) || defined(CONFIG_F2E_PHY)
         *link = athr_phy_is_up(unit);
#endif
#ifdef CONFIG_VIR_PHY
         *link = athr_vir_phy_is_up(unit);
#endif
    }
}

static inline void ag7240_phy_duplex(int unit, u32 *duplex)
{
#ifdef CONFIG_AR7242_S16_PHY
    if ((is_ar7242() || is_wasp()) && (unit==0)) {
        *duplex = athrs16_phy_is_fdx(unit);
    } else
#endif
#ifdef CONFIG_ATHRS17_PHY
    if (unit == 0) {
        *duplex = athrs17_phy_is_fdx(unit);
    } else
#endif
   {
#ifdef CFG_ATHRS27_PHY
        *duplex = athrs27_phy_is_fdx(unit, 0/* FIXME */);
#endif
#ifdef CFG_ATHRS26_PHY
        *duplex = athrs26_phy_is_fdx(unit);
#endif
#if defined(CONFIG_F1E_PHY) || defined(CONFIG_F2E_PHY)
        *duplex = athr_phy_is_fdx(unit);
#endif
#ifdef CONFIG_VIR_PHY
        *duplex = athr_vir_phy_is_fdx(unit);
#endif
    }
}

static inline void ag7240_phy_speed(int unit, u32 *speed)
{
#ifdef CONFIG_AR7242_S16_PHY
    if ((is_ar7242() || is_wasp()) && (unit==0)) {
        *speed = athrs16_phy_speed(unit);
    } else
#endif
#ifdef CONFIG_ATHRS17_PHY
    if (unit == 0) {
        *speed = athrs17_phy_speed(unit);
    } else
#endif
    {
#ifdef CFG_ATHRS27_PHY
        *speed = athrs27_phy_speed(unit, 0/* FIXME */);
#endif
#ifdef CFG_ATHRS26_PHY
        *speed = athrs26_phy_speed(unit);
#endif
#if defined(CONFIG_F1E_PHY) || defined(CONFIG_F2E_PHY)
        *speed = athr_phy_speed(unit);
#endif
#ifdef CONFIG_VIR_PHY
        *speed = athr_vir_phy_speed(unit);
#endif
    }
}

#endif /*_AG7240_PHY_H*/
