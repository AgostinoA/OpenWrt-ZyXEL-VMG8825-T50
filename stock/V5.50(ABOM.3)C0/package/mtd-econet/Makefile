# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=mtd-econet
PKG_RELEASE:=6

PKG_BUILD_DIR := $(KERNEL_BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

# __ZYXEL__start,
# Replace 'CONFIG_ECONETSDK_' for menuconfig only supports a single prompt problem.
ifeq ("$(strip ${ZCFG_PLATFORM})","ECONET")
PLATFORM_PREFIX=CONFIG_$(call qstrip, $(CONFIG_CUSTOM_SDK_PREFIX))_
endif
ifneq ($(strip $(PLATFORM_PREFIX)),)
$(foreach v, \
        $(shell grep "^$(PLATFORM_PREFIX)" $(TOPDIR)/.config), \
        $(eval $(shell echo $v|sed "s/$(PLATFORM_PREFIX)//"|cut -d'=' -f1)=$(shell echo $v|cut -d'=' -f2)))
endif
# __ZYXEL__end

define Package/mtd-econet
  SECTION:=utils
  CATEGORY:=Base system
  TITLE:=Update utility for trx firmware images
endef

define Package/mtd-econet/description
 This package contains an utility useful to upgrade from other firmware or 
 older OpenWrt releases.
endef

MTD_CFLAGS =
ifneq ($(strip $(TCSUPPORT_CODE_SHRINK)),)
MTD_CFLAGS+=-Os
endif
ifneq ($(strip $(CONFIG_TARGET_mt75xx)$(CONFIG_TARGET_en75xx)),)
MTD_CFLAGS+=-DTRENDCHIP $(TC_CFLAGS)
COMMON_MAKE_OPTS = CROSS="$(TARGET_CROSS)" \
		STAGING_DIR_HOST="$(STAGING_DIR_HOST)" \
		MTD_CFLAGS="$(MTD_CFLAGS)" \
		KERNEL_DIR="$(LINUX_DIR)/user_headers/" \
		$(TARGET_CONFIGURE_OPTS)
endif

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		$(TARGET_CONFIGURE_OPTS) \
		$(COMMON_MAKE_OPTS) \
		CFLAGS="-Dtarget_$(BOARD)=1"
endef

define Package/mtd-econet/install
	$(INSTALL_DIR) $(1)/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mtd $(1)/sbin/
endef

$(eval $(call BuildPackage,mtd-econet))
