#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=updatedd
PKG_VERSION:=2.6
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/network/services
DL_DIR:=$(TOPDIR)/dl

PKG_LICENSE:=GPLv2
PKG_LICENSE_FILES:=COPYING

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

#CONFIGURE_PREFIX=$(STAGING_DIR_ROOT)/usr

define Package/updatedd
  SECTION:=net
  CATEGORY:=Base system
  DEPENDS:=+libresolv
  TITLE:=A client to update a dynamic DNS
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/lib/$(PKG_NAME)
	$(CP) $(PKG_BUILD_DIR)/src/plugins/.libs/*.so* $(1)/usr/lib/$(PKG_NAME)
endef

define Package/updatedd/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/updatedd $(1)/usr/bin/	
#	$(CP) $(PKG_BUILD_DIR)/src/$(PKG_NAME) $(1)/usr/bin/
	$(INSTALL_DIR) $(1)/usr/lib/$(PKG_NAME)
	$(CP) $(PKG_BUILD_DIR)/src/plugins/.libs/*.so* $(1)/usr/lib/$(PKG_NAME)
endef

$(eval $(call BuildPackage,updatedd))
