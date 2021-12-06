#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libnl-tiny
PKG_VERSION:=0.1
ifeq ("$(strip ${ZCFG_PLATFORM})", $(filter "$(strip ${ZCFG_PLATFORM})","QUALCOMM" "BROADCOM"))
PKG_RELEASE:=4

PKG_LICENSE:=LGPL-2.1
else
PKG_RELEASE:=3

PKG_LICENSE:=GPLv2 LGPLv2.1
PKG_LICENSE_FILES:=

endif
SRC_DIR:=src-$(PKG_VERSION).$(PKG_RELEASE)
PKG_MAINTAINER:=Felix Fietkau <nbd@openwrt.org>

include $(INCLUDE_DIR)/package.mk

define Package/libnl-tiny
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=netlink socket library
endef

define Package/libnl-tiny/description
 This package contains a stripped down version of libnl
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./$(SRC_DIR)/* $(PKG_BUILD_DIR)/
endef

TARGET_CFLAGS += $(FPIC)

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		$(TARGET_CONFIGURE_OPTS) \
		CFLAGS="$(TARGET_CFLAGS)" \
		all
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig $(1)/usr/include/
	$(CP) $(PKG_BUILD_DIR)/include/* $(1)/usr/include/
	$(CP) $(PKG_BUILD_DIR)/libnl-tiny.so $(1)/usr/lib/
	$(CP) ./files/libnl-tiny.pc $(1)/usr/lib/pkgconfig
endef

define Package/libnl-tiny/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/libnl-tiny.so $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libnl-tiny))
