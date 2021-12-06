#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

FORCE_USE_EXTERNAL_KERNAL_TOOLCHAIN=y
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=ebtables

ifeq ("$(strip ${ZCFG_PLATFORM})","BROADCOM")
PKG_VERSION:=2.0.10-4
else ifeq ("$(strip ${ZCFG_PLATFORM})","ECONET")
PKG_VERSION:=2.0.8-2
else ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
PKG_VERSION:=2.0.10-4
endif

#PRODUCT_NAME:=$(word 1, $(subst -,_,$(call qstrip, $(CONFIG_MRD_PRODUCT_NAME))))
#export SUBTARGET

PATCH_DIR:=patches-$(PKG_VERSION)/$(ZCFG_PLATFORM)
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-v$(PKG_VERSION).tar.gz
#PKG_SOURCE_URL:=@SF/ebtables
#PKG_MD5SUM:=506742a3d44b9925955425a659c1a8d0
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/network/utils

PKG_BUILD_DIR:=$(BUILD_DIR)/ebtables-v$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/ebtables
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Firewall
  DEPENDS:=+kmod-ebtables
  TITLE:=Ethernet bridge firewall administration utility
  URL:=http://ebtables.sourceforge.net/
endef

define Package/ebtables-utils
  $(call Package/ebtables)
  DEPENDS += ebtables
  TITLE:=ebtables save/restore utilities
endef

define Package/ebtables/description
	The ebtables program is a filtering tool for a bridging firewall. The
	filtering is focussed on the Link Layer Ethernet frame fields. Apart
	from filtering, it also gives the ability to alter the Ethernet MAC
	addresses and implement a brouter.
endef

define Package/ebtables-utils/description
	$(call Package/ebtables/description)
endef

MAKE_VARS += EXT_LIBSI="$(LIBGCC_S)"

export BUILD_DIR
export CONFIG_KERNEL_BRIDGE_EBT_NFQUEUE

ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
CFLAGS="$(TARGET_CFLAGS)"

export CFLAGS

MAKE_FLAGS += \
	LIBDIR="/usr/lib/ebtables" \
	EBT_EXT_FUNC="ip ip6 standard vlan mark_m mark time ftos skiplog AUTOMAP policer zextmark_m zextmark"
else
export CONFIG_TC_SDK_VERSION

#CFLAGS="$(TARGET_CFLAGS)"

#export CFLAGS

ECONET_CFLAGS=$(TC_CFLAGS)
ifneq ($(strip $(TCSUPPORT_CODE_SHRINK)),)
ECONET_CFLAGS += -Os
endif

MAKE_FLAGS += \
	ECONET_CFLAGS="$(ECONET_CFLAGS)" \
	LIBDIR="/usr/lib/ebtables" \
	EBT_EXT_FUNC="ip ip6 standard vlan mark_m mark time ftos skiplog AUTOMAP policer zextmark_m zextmark"

endif
define Package/ebtables/install
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/ethertypes $(1)/etc/
	$(INSTALL_DIR) $(1)/usr/lib/ebtables
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/lib*.so $(1)/usr/lib/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/extensions/*.so $(1)/usr/lib/ebtables/
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ebtables $(1)/usr/sbin/
endef

define Package/ebtables-utils/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ebtables-save $(1)/usr/sbin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ebtables-restore $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,ebtables))
$(eval $(call BuildPackage,ebtables-utils))
