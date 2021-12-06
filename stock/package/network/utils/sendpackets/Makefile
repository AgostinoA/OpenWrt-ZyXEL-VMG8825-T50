#
# Copyright (C) 2011-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=sendpackets
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/sendpackets
  SECTION:=net
  CATEGORY:=Network
  TITLE:=Utility to send packet to network interface.
  DEPENDS:=+libpcap
endef

define Package/sendpackets/description
 This package contains the small sendpackets utility to netork interface
endef

TARGET_CFLAGS += -I$(STAGING_DIR)/usr/include

define Build/Prepare
	$(INSTALL_DIR) $(PKG_BUILD_DIR)
	$(INSTALL_DATA) ./src/sendpackets.c $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(TARGET_CC) $(TARGET_CFLAGS) -Wall -lpcap \
		-o $(PKG_BUILD_DIR)/sendpackets $(PKG_BUILD_DIR)/sendpackets.c
endef

define Package/sendpackets/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/sendpackets $(1)/usr/bin/
endef

$(eval $(call BuildPackage,sendpackets))
