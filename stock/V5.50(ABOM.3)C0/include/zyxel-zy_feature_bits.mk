#
# Copyright (C) 2006-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
#

## For MRD Feature Bits using >>>
ifneq ($(call qstrip,$(CONFIG_ZYXEL_FEATURE_BITS)),)
ZYXEL_FEATURE_BITS=1
else
ZYXEL_FEATURE_BITS=0
endif

#mrd_feature_byte[8]
ifneq ($(call qstrip,$(CONFIG_MRD_SUPPORT_VOICE)),)
MRD_SUPPORT_VOICE=$(shell MRD_SUPPORT_VOICE=$$(( 0x1 << 0 ));echo $$MRD_SUPPORT_VOICE)
else
MRD_SUPPORT_VOICE=0x0
endif
ifneq ($(call qstrip,$(CONFIG_MRD_SUPPORT_VOICE_SINGLE)),)
MRD_SUPPORT_VOICE_SINGLE=$(shell MRD_SUPPORT_VOICE_SINGLE=$$(( 0x1 << 1 ));echo $$MRD_SUPPORT_VOICE_SINGLE)
else
MRD_SUPPORT_VOICE_SINGLE=0x0
endif
export MRD_FEATURE_BITS_VOICE=$(shell MRD_FEATURE_BITS_VOICE=$$(( $(MRD_SUPPORT_VOICE)|$(MRD_SUPPORT_VOICE_SINGLE) ));echo $$MRD_FEATURE_BITS_VOICE)

#mrd_feature_byte[9]
ifneq ($(call qstrip,$(CONFIG_MRD_SUPPORT_2_4_G)),)
MRD_SUPPORT_2_4_G=$(shell MRD_SUPPORT_2_4_G=$$(( 0x1 << 0 ));echo $$MRD_SUPPORT_2_4_G)
else
MRD_SUPPORT_2_4_G=0x0
endif
ifneq ($(call qstrip,$(CONFIG_MRD_SUPPORT_FEM_2_4_G)),)
MRD_SUPPORT_FEM_2_4_G=$(shell MRD_SUPPORT_FEM_2_4_G=$$(( 0x1 << 2 ));echo $$MRD_SUPPORT_FEM_2_4_G)
else
MRD_SUPPORT_FEM_2_4_G=0x0
endif
ifneq ($(call qstrip,$(CONFIG_MRD_SUPPORT_EXTANT_2_4_G)),)
MRD_SUPPORT_EXTANT_2_4_G=$(shell MRD_SUPPORT_EXTANT_2_4_G=$$(( 0x1 << 4 ));echo $$MRD_SUPPORT_EXTANT_2_4_G)
else
MRD_SUPPORT_EXTANT_2_4_G=0x0
endif
ifneq ($(call qstrip,$(CONFIG_MRD_SUPPORT_5G)),)
MRD_SUPPORT_5G=$(shell MRD_SUPPORT_5G=$$(( 0x1 << 1 ));echo $$MRD_SUPPORT_5G)
else
MRD_SUPPORT_5G=0x0
endif
ifneq ($(call qstrip,$(CONFIG_MRD_SUPPORT_FEM_5G)),)
MRD_SUPPORT_FEM_5G=$(shell MRD_SUPPORT_FEM_5G=$$(( 0x1 << 3 ));echo $$MRD_SUPPORT_FEM_5G)
else
MRD_SUPPORT_FEM_5G=0x0
endif
ifneq ($(call qstrip,$(CONFIG_MRD_SUPPORT_EXTANT_5G)),)
MRD_SUPPORT_EXTANT_5G=$(shell MRD_SUPPORT_EXTANT_5G=$$(( 0x1 << 5 ));echo $$MRD_SUPPORT_EXTANT_5G)
else
MRD_SUPPORT_EXTANT_5G=0x0
endif
export MRD_FEATURE_BITS_WIFI=$(shell MRD_FEATURE_BITS_WIFI=$$(( $(MRD_SUPPORT_2_4_G)|$(MRD_SUPPORT_FEM_2_4_G)|$(MRD_SUPPORT_EXTANT_2_4_G)|$(MRD_SUPPORT_5G)|$(MRD_SUPPORT_FEM_5G)|$(MRD_SUPPORT_EXTANT_5G) ));echo $$MRD_FEATURE_BITS_WIFI)

#mrd_feature_byte[10]
ifneq ($(call qstrip,$(CONFIG_MRD_SUPPORT_VDSL_17A)),)
MRD_SUPPORT_VDSL_17A=$(shell MRD_SUPPORT_VDSL_17A=$$(( 0x1 << 0 ));echo $$MRD_SUPPORT_VDSL_17A)
else
MRD_SUPPORT_VDSL_17A=0x0
endif
ifneq ($(call qstrip,$(CONFIG_MRD_SUPPORT_VDSL_35B)),)
MRD_SUPPORT_VDSL_35B=$(shell MRD_SUPPORT_VDSL_35B=$$(( 0x1 << 1 ));echo $$MRD_SUPPORT_VDSL_35B)
else
MRD_SUPPORT_VDSL_35B=0x0
endif
ifneq ($(call qstrip,$(CONFIG_MRD_SUPPORT_GFAST)),)
MRD_SUPPORT_GFAST=$(shell MRD_SUPPORT_GFAST=$$(( 0x1 << 2 ));echo $$MRD_SUPPORT_GFAST)
else
MRD_SUPPORT_GFAST=0x0
endif
export MRD_FEATURE_BITS_VDSL_PROFILE=$(shell MRD_FEATURE_BITS_VDSL_PROFILE=$$(( $(MRD_SUPPORT_VDSL_17A)|$(MRD_SUPPORT_VDSL_35B)|$(MRD_SUPPORT_GFAST) ));echo $$MRD_FEATURE_BITS_VDSL_PROFILE)

#mrd_feature_byte[11]
ifeq ($(call qstrip,$(CONFIG_MRD_SUPPORT_ANNEX_A)),y)
export MRD_FEATURE_BITS_ADSL_TYPE=$(shell MRD_FEATURE_BITS_ADSL_TYPE=$$(( 0x1 << 0 ));echo $$MRD_FEATURE_BITS_ADSL_TYPE)
else ifeq ($(call qstrip,$(CONFIG_MRD_SUPPORT_ANNEX_B)),y)
export MRD_FEATURE_BITS_ADSL_TYPE=$(shell MRD_FEATURE_BITS_ADSL_TYPE=$$(( 0x1 << 1 ));echo $$MRD_FEATURE_BITS_ADSL_TYPE)
else ifeq ($(call qstrip,$(CONFIG_MRD_SUPPORT_ANNEX_C)),y)
export MRD_FEATURE_BITS_ADSL_TYPE=$(shell MRD_FEATURE_BITS_ADSL_TYPE=$$(( 0x1 << 2 ));echo $$MRD_FEATURE_BITS_ADSL_TYPE)
else
export MRD_FEATURE_BITS_ADSL_TYPE=$(shell MRD_FEATURE_BITS_ADSL_TYPE=$$(( 0x0 << 0 ));echo $$MRD_FEATURE_BITS_ADSL_TYPE)
endif

#mrd_feature_byte[12..13]
# reserved

#mrd_feature_byte[14]
ifneq ($(call qstrip,$(CONFIG_MRD_SUPPORT_ZIGBEE)),)
MRD_SUPPORT_ZIGBEE=$(shell MRD_SUPPORT_ZIGBEE=$$(( 0x1 << 0 ));echo $$MRD_SUPPORT_ZIGBEE)
else
MRD_SUPPORT_ZIGBEE=0x0
endif
export MRD_FEATURE_BITS_ZIGBEE=$(shell MRD_FEATURE_BITS_ZIGBEE=$$(( $(MRD_SUPPORT_ZIGBEE) ));echo $$MRD_FEATURE_BITS_ZIGBEE)

#mrd_feature_byte[15]
# reserved

## For MRD Feature Bits using <<<
