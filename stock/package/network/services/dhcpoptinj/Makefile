#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=dhcpoptinj
PKG_VERSION:=1.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/network/services
DL_DIR:=$(TOPDIR)/dl

PKG_LICENSE:=GPLv2
PKG_LICENSE_FILES:=COPYING

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

#LIBS_ZCFG = +libzcfg_msg +libzcmd_tool +libjson +libzcfg_fe_rdm_access +libzcfg_fe_rdm_struct

include $(INCLUDE_DIR)/package.mk

define Package/dhcpoptinj
  SECTION:=net
  CATEGORY:=Base system
  TITLE:=An embedded DHCP client and server
  DEPENDS:=$(LIBS_ZCFG)
endef

define Package/$(PKG_NAME)
  SECTION:=net
  CATEGORY:=Base system
  TITLE:= A deamon to receive and handle dhcp opt82 insertion via NF_QUEUE
  DESCRIPTION:=
  DEPENDS:= +libnfnetlink +libnetfilter_queue $(LIBS_ZCFG)
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		CC="$(TARGET_CROSS)gcc" \
		STRIP="$(TARGET_CROSS)strip" \
		INSTALL_DIR="$(BCM_INSTALL_DIR)"
endef

define Package/dhcpoptinj/install
	$(INSTALL_DIR) $(1)/bin
	$(CP) $(PKG_BUILD_DIR)/dhcpoptinj $(1)/bin
	$(TARGET_CROSS)strip $(1)/bin/dhcpoptinj
endef

$(eval $(call BuildPackage,dhcpoptinj))
