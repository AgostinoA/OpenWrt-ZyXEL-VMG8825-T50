#
# Copyright (C) 2008-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=uci
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
UCI_VERSION=2015-08-27
UCI_RELEASE=1
PKG_REV:=2cd94fd505b293e657278e31deb32a7d66d20714
PKG_MIRROR_MD5SUM:=
else
UCI_VERSION=2012-11-09
UCI_RELEASE=1
PKG_REV:=e81961bde820a84bf67ccd5e40b29f7952dd1f77
PKG_MIRROR_MD5SUM:=b6a82d18e6b4e40847a52336589e666b
endif
PATCH_DIR:=patches-$(PKG_VERSION)
PKG_VERSION:=$(UCI_VERSION)$(if $(UCI_RELEASE),.$(UCI_RELEASE))
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
#PKG_SOURCE_URL:=git://nbd.name/uci.git
#PKG_SOURCE_SUBDIR:=uci-$(PKG_VERSION)
#PKG_SOURCE_VERSION:=$(PKG_REV)
#PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/config

PKG_LICENSE:=LGPLv2.1 GPLv2
PKG_LICENSE_FILES:=

PKG_MAINTAINER:=Felix Fietkau <nbd@openwrt.org>

PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

# set to 1 to enable debugging
DEBUG=

define Package/libuci
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=C library for the Unified Configuration Interface (UCI)
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
  DEPENDS:=+libubox
endif
endef

define Package/uci
  SECTION:=base
  CATEGORY:=Base system
  DEPENDS:=+libuci
  TITLE:=Utility for the Unified Configuration Interface (UCI)
endef

define Package/libuci-lua
  SECTION=libs
  CATEGORY=Libraries
  DEPENDS:=+libuci +liblua
  TITLE:=Lua plugin for UCI
endef

TARGET_CFLAGS += -I$(STAGING_DIR)/usr/include
TARGET_LDFLAGS += -L$(STAGING_DIR)/usr/lib

CMAKE_OPTIONS = \
	-DLUAPATH=/usr/lib/lua \
	$(if $(DEBUG),-DUCI_DEBUG=ON)

define Package/libuci/install
	$(INSTALL_DIR) $(1)/lib
	$(CP) $(PKG_BUILD_DIR)/libuci.so* $(1)/lib/
endef

define Package/libuci-lua/install
	$(INSTALL_DIR) $(1)/usr/lib/lua
	$(CP) $(PKG_BUILD_DIR)/lua/uci.so $(1)/usr/lib/lua/
endef

define Package/uci/install
	$(INSTALL_DIR) $(1)/etc/uci-defaults
	$(INSTALL_DIR) $(1)/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/uci $(1)/sbin/
	$(CP) ./files/* $(1)/
endef
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/uci{,_config,_blob,map}.h $(1)/usr/include
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/libuci.so* $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/libucimap.a $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/libucimap.a $(1)/usr/lib
endef
else
define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/uci{,_config,map}.h $(1)/usr/include
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/libuci.so* $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/libuci.a $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/libucimap.a $(1)/usr/lib
endef
endif

$(eval $(call BuildPackage,uci))
$(eval $(call BuildPackage,libuci))
$(eval $(call BuildPackage,libuci-lua))
