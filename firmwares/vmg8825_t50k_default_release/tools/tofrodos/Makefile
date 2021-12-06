# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=tofrodos
PKG_VERSION:=1.7.13

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
#PKG_SOURCE_URL:=http://downloads.openwrt.org/sources/
#PKG_MD5SUM:=434e51a018b4c8ef377bf81520a53af0
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/tools/editor

HOST_BUILD_DIR:=$(BUILD_DIR_HOST)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/host-build.mk

define Host/Compile
	$(MAKE) -C $(HOST_BUILD_DIR)
endef

define Host/Install
	$(INSTALL_DIR) $(STAGING_DIR_HOST)/bin
	$(INSTALL_BIN) $(HOST_BUILD_DIR)/fromdos $(STAGING_DIR_HOST)/bin/
	ln -sf fromdos $(STAGING_DIR_HOST)/bin/todos
	ln -sf fromdos $(STAGING_DIR_HOST)/bin/dos2unix
	ln -sf fromdos $(STAGING_DIR_HOST)/bin/unix2dos
endef

define Host/Clean
endef

$(eval $(call HostBuild))

