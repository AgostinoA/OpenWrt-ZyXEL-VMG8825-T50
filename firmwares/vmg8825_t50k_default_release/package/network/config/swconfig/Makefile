#
# Copyright (C) 2008-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=swconfig
PKG_RELEASE:=10

PKG_MAINTAINER:=Felix Fietkau <nbd@openwrt.org>

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

define Package/swconfig
  SECTION:=base
  CATEGORY:=Base system
ifeq ($(CONFIG_PACKAGE_libnl),y)
  DEPENDS:=@!TARGET_brcm47xx +libuci +libnl
else
  DEPENDS:=@!TARGET_brcm47xx +libuci +libnl-tiny
endif
  TITLE:=Switch configuration utility
endef

ifeq ($(CONFIG_PACKAGE_libnl),y)
LIB_NL:=$(STAGING_DIR)/usr/include/libnl
else
LIB_NL:=$(STAGING_DIR)/usr/include/libnl-tiny 
endif

ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
FILES_DIR:=files-qca
TARGET_CPPFLAGS := \
	-D_GNU_SOURCE \
	-I$(STAGING_DIR)/usr/include/libnl-tiny \
	-I$(PKG_BUILD_DIR) \
	$(TARGET_CPPFLAGS) \
	-I$(LINUX_DIR)/user_headers/include

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src-qca/* $(PKG_BUILD_DIR)/
endef
else
FILES_DIR:=files-opal
TARGET_CPPFLAGS := \
	-D_GNU_SOURCE \
	-I$(LIB_NL) \
	-I$(PKG_BUILD_DIR) \
	$(TARGET_CPPFLAGS)

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src-opal/* $(PKG_BUILD_DIR)/
endef
endif

define Build/Compile
	CFLAGS="$(TARGET_CPPFLAGS) $(TARGET_CFLAGS)" \
	$(MAKE) -C $(PKG_BUILD_DIR) \
		$(TARGET_CONFIGURE_OPTS) \
ifeq ($(CONFIG_PACKAGE_libnl),y)
		LIBS="$(TARGET_LDFLAGS) -lnl -lm -luci"
else
		LIBS="$(TARGET_LDFLAGS) -lnl-tiny -lm -luci"
endif
endef

define Package/swconfig/install
	$(INSTALL_DIR) $(1)/sbin $(1)/lib/network
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/swconfig $(1)/sbin/swconfig
	$(INSTALL_DATA) ./$(FILES_DIR)/switch.sh $(1)/lib/network/
endef

$(eval $(call BuildPackage,swconfig))
