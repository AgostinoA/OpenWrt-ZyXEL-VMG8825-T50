#
# Copyright (C) 2006-2012 OpenWrt.org
#    GPLv2 license, read COPYING
#

include $(TOPDIR)/rules.mk

PKG_NAME:=p910nd
PKG_VERSION:=0.97
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/network/services
PKG_MD5SUM:=69461a6c54dca0b13ecad5b83864b43e

PKG_LICENSE:=GPLv2
PKG_LICENSE_FILES:=COPYING

PATCH_DIR=patches_$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/p910nd
  SECTION:=net
  CATEGORY:=Base system
  TITLE:=p910nd is a small daemon that copies any data received to the corresponding printer port
  URL:=https://sources.openwrt.org/
endef


define Package/p910nd/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(CP) $(PKG_BUILD_DIR)/p910nd $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,p910nd))
