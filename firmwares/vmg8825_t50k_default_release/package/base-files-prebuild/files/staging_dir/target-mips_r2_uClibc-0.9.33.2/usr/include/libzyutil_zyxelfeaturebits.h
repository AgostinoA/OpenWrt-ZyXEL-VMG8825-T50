/*
 *	libzyutil_zyxelfeaturebits.h - Public APIs of Zyxel Feature Bits.
 *	Copyright (C) 2017 Zyxel Communications Corp.
 */

#ifndef _LIBZYUTIL_ZYXELFEATUREBITS_H
#define _LIBZYUTIL_ZYXELFEATUREBITS_H

#include "zcfg_common.h"

#define PROC_ZY_FEATURE_BITS    "/proc/zyxel/zy_feature_bits"

/*!
 *  ZYFEATUREBITS_XXX :
 *  Zyxel Feature Bits offset are defined in linux header
 *  /linux-brcm963xx_xxx/linux-3.4.11/include/linux/zy_feature_bits.h,
 *  which is used by /bcmdrivers/opensource/include/bcm963xx/board.h
 *  and
 *  /libzyutil-1.0/libzyutil_zyxelfeaturebits.h
 */

/*!
 *  Check if it support ADSL Annex A.
 *
 *  @param[out] value       1:support, 0:not support.
 *  @return zcfgRet_t       ZCFG_SUCCESS:success(0), ZCFG_INTERNAL_ERROR:fail(-5).
 */
zcfgRet_t libzyutil_zyxelfeaturebits_adslAnnexAGet(int *value);
/*!
 *  Check if it support ADSL Annex B.
 *
 *  @param[out] value       1:support, 0:not support.
 *  @return zcfgRet_t       ZCFG_SUCCESS:success(0), ZCFG_INTERNAL_ERROR:fail(-5).
 */
zcfgRet_t libzyutil_zyxelfeaturebits_adslAnnexBGet(int *value);
/*!
 *  Check if it support ADSL Annex C.
 *
 *  @param[out] value       1:support, 0:not support.
 *  @return zcfgRet_t       ZCFG_SUCCESS:success(0), ZCFG_INTERNAL_ERROR:fail(-5).
 */
zcfgRet_t libzyutil_zyxelfeaturebits_adslAnnexCGet(int *value);
/*!
 *  Check if it support VDSL 17a.
 *
 *  @param[out] value       1:support, 0:not support.
 *  @return zcfgRet_t       ZCFG_SUCCESS:success(0), ZCFG_INTERNAL_ERROR:fail(-5).
 */
zcfgRet_t libzyutil_zyxelfeaturebits_vdsl17aGet(int *value);
/*!
 *  Check if it support VDSL 35b.
 *
 *  @param[out] value       1:support, 0:not support.
 *  @return zcfgRet_t       ZCFG_SUCCESS:success(0), ZCFG_INTERNAL_ERROR:fail(-5).
 */
zcfgRet_t libzyutil_zyxelfeaturebits_vdsl35bGet(int *value);
/*!
 *  Check if it support VDSL G.fast.
 *
 *  @param[out] value       1:support, 0:not support.
 *  @return zcfgRet_t       ZCFG_SUCCESS:success(0), ZCFG_INTERNAL_ERROR:fail(-5).
 */
zcfgRet_t libzyutil_zyxelfeaturebits_vdslGfastGet(int *value);
/*!
 *  Check if it support Wifi 2.4G.
 *
 *  @param[out] value       1:support, 0:not support.
 *  @return zcfgRet_t       ZCFG_SUCCESS:success(0), ZCFG_INTERNAL_ERROR:fail(-5).
 */
zcfgRet_t libzyutil_zyxelfeaturebits_wifi24GGet(int *value);
/*!
 *  Check if it support Wifi 2.4G FEM.
 *
 *  @param[out] value       1:support, 0:not support.
 *  @return zcfgRet_t       ZCFG_SUCCESS:success(0), ZCFG_INTERNAL_ERROR:fail(-5).
 */
zcfgRet_t libzyutil_zyxelfeaturebits_wifi24GFemGet(int *value);
/*!
 *  Check if it support Wifi 2.4G external antenna.
 *
 *  @param[out] value       1:support, 0:not support.
 *  @return zcfgRet_t       ZCFG_SUCCESS:success(0), ZCFG_INTERNAL_ERROR:fail(-5).
 */
zcfgRet_t libzyutil_zyxelfeaturebits_wifi24GExAntGet(int *value);
/*!
 *  Check if it support Wifi 5G.
 *
 *  @param[out] value       1:support, 0:not support.
 *  @return zcfgRet_t       ZCFG_SUCCESS:success(0), ZCFG_INTERNAL_ERROR:fail(-5).
 */
zcfgRet_t libzyutil_zyxelfeaturebits_wifi5GGet(int *value);
/*!
 *  Check if it support Wifi 5G FEM.
 *
 *  @param[out] value       1:support, 0:not support.
 *  @return zcfgRet_t       ZCFG_SUCCESS:success(0), ZCFG_INTERNAL_ERROR:fail(-5).
 */
zcfgRet_t libzyutil_zyxelfeaturebits_wifi5GFemGet(int *value);
/*!
 *  Check if it support Wifi 5G external antenna.
 *
 *  @param[out] value       1:support, 0:not support.
 *  @return zcfgRet_t       ZCFG_SUCCESS:success(0), ZCFG_INTERNAL_ERROR:fail(-5).
 */
zcfgRet_t libzyutil_zyxelfeaturebits_wifi5GExAntGet(int *value);
/*!
 *  Check if it support VoIP.
 *
 *  @param[out] value       1:support, 0:not support.
 *  @return zcfgRet_t       ZCFG_SUCCESS:success(0), ZCFG_INTERNAL_ERROR:fail(-5).
 */
zcfgRet_t libzyutil_zyxelfeaturebits_voipGet(int *value);
/*!
 *  Check if it only support single VoIP.
 *
 *  @param[out] value       1:single voip, 0:dobule voip(default).
 *  @return zcfgRet_t       ZCFG_SUCCESS:success(0), ZCFG_INTERNAL_ERROR:fail(-5).
 */
zcfgRet_t libzyutil_zyxelfeaturebits_voipSinglePortGet(int *value);
/*!
 *  Check if it support ZigBee.
 *
 *  @param[out] value       1:support, 0:not support.
 *  @return zcfgRet_t       ZCFG_SUCCESS:success(0), ZCFG_INTERNAL_ERROR:fail(-5).
 */
zcfgRet_t libzyutil_zyxelfeaturebits_zigbeeGet(int *value);

#endif	/* _LIBZYUTIL_ZYXELFEATUREBITS_H */
