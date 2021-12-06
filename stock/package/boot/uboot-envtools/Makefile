#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=uboot-envtools
PKG_DISTNAME:=u-boot
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
PKG_VERSION:=2014.10
PKG_RELEASE:=2
PKG_MD5SUM:=3ddcaee2f05b7c464778112ec83664b5
PKG_BUILD_DIR:=$(BUILD_DIR)/u-boot-$(PKG_VERSION)
else
PKG_VERSION:=2012.04.01
PKG_RELEASE:=1
PKG_MD5SUM:=192bb231082d9159fb6e16de3039b6b2
endif

PKG_SOURCE:=$(PKG_DISTNAME)-$(PKG_VERSION).tar.bz2
#PKG_SOURCE_URL:=ftp://ftp.denx.de/pub/u-boot
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/loader
PATCH_DIR:=patches-$(PKG_VERSION)
FILES_DIR:=files-$(PKG_VERSION)
include $(INCLUDE_DIR)/package.mk

ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
PKG_BUILD_DEPENDS:=+fstools
else
TAR_OPTIONS+= --strip-components=3 -C $(PKG_BUILD_DIR) $(PKG_DISTNAME)-$(PKG_VERSION)/tools/env
PKG_BUILD_DEPENDS:=zlib
endif

define Package/uboot-envtools
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=read/modify U-Boot bootloader environment
  URL:=http://www.denx.de/wiki/U-Boot
endef

define Package/uboot-envtools/description
 This package includes tools to read and modify U-Boot bootloader environment.
endef

ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
define Package/uboot-envtools/config
	source "$(SOURCE)/Config.in"
endef

define Build/Configure
	touch $(PKG_BUILD_DIR)/include/config.mk
	touch $(PKG_BUILD_DIR)/include/config.h
endef
endif

TARGET_CFLAGS += -I$(STAGING_DIR)/usr/include

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		TARGET_CFLAGS="$(TARGET_CFLAGS)" \
		HOSTLDFLAGS="-znow -zrelro" \
		UBI="$(CONFIG_UBOOT_ENVTOOLS_UBI)" \
		env
endef

ifneq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	tar xvjf $(DL_DIR)/$(PKG_SOURCE) --strip-components=2 -C $(PKG_BUILD_DIR) $(PKG_DISTNAME)-$(PKG_VERSION)/lib/crc32.c
	$(call Build/Prepare/Default)
endef
endif

define Package/uboot-envtools/conffiles
/etc/config/ubootenv
/etc/fw_env.config
endef

define Package/uboot-envtools/install
	$(INSTALL_DIR) $(1)/usr/sbin
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/tools/env/fw_printenv $(1)/usr/sbin
else
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/fw_printenv $(1)/usr/sbin
endif
	ln -s fw_printenv $(1)/usr/sbin/fw_setenv
	$(INSTALL_DIR) $(1)/lib
	$(INSTALL_DATA) ./$(FILES_DIR)/uboot-envtools.sh $(1)/lib
ifneq ($(CONFIG_TARGET_ar71xx),)
	$(INSTALL_DIR) $(1)/etc/uci-defaults
	$(INSTALL_BIN) ./$(FILES_DIR)/ar71xx $(1)/etc/uci-defaults/uboot-envtools
endif
ifneq ($(CONFIG_TARGET_kirkwood),)
	$(INSTALL_DIR) $(1)/etc/uci-defaults
	$(INSTALL_BIN) ./$(FILES_DIR)/kirkwood $(1)/etc/uci-defaults/uboot-envtools
endif
ifneq ($(CONFIG_TARGET_lantiq),)
	$(INSTALL_DIR) $(1)/etc/uci-defaults
	$(INSTALL_BIN) ./$(FILES_DIR)/lantiq $(1)/etc/uci-defaults/uboot-envtools
endif
ifneq ($(CONFIG_TARGET_ramips),)
	$(INSTALL_DIR) $(1)/etc/uci-defaults
	$(INSTALL_BIN) ./$(FILES_DIR)/ramips $(1)/etc/uci-defaults/uboot-envtools
endif
ifneq ($(CONFIG_TARGET_ipq806x)$(CONFIG_TARGET_ipq),)
	$(INSTALL_DIR) $(1)/etc/uci-defaults
	$(INSTALL_BIN) ./$(FILES_DIR)/ipq806x $(1)/etc/uci-defaults/uboot-envtools
endif
endef

$(eval $(call BuildPackage,uboot-envtools))
