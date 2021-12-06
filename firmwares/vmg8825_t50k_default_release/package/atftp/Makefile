#
# Copyright (C) 2006-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=atftp
PKG_VERSION:=0.7.1
PKG_RELEASE:=5
PKG_LICENSE:=GPL-2.0

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/network/services
PATCH_DIR=patches

include $(INCLUDE_DIR)/package.mk

define Package/atftp/Default
  SECTION:=net
  CATEGORY:=Network
  TITLE:=TFTP
  SUBMENU:=File Transfer
endef

define Package/atftp
  $(call Package/atftp/Default)
  DEPENDS:=+libreadline +libncurses
  TITLE+= client
endef

define Package/atftpd
  $(call Package/atftp/Default)
  DEPENDS:=+libpthread
  TITLE+= server
endef

CONFIGURE_ARGS += \
	--disable-libwrap

define Package/atftp/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/atftp $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc
	ln -s /tmp/hosts $(1)/etc/hosts
endef

define Package/atftpd/install
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/atftpd $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,atftp))
$(eval $(call BuildPackage,atftpd))
