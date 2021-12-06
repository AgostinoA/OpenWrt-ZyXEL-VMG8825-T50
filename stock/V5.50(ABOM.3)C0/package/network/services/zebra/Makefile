#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=zebra
ifeq ($(CONFIG_TARGET_brcm963xx),y)
PKG_VERSION:=0.93a-brcm
PATCH_DIR:= patches
else
PKG_VERSION:=0.93a
PATCH_DIR:= ECONET-patches
endif


PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
#PKG_SOURCE_URL:= \
	http://matt.ucc.asn.au/dropbear/releases/ \
	http://www.mirrors.wiretapped.net/security/cryptography/apps/ssh/dropbear/
#PKG_MD5SUM:=8c784baec3054cdb1bb4bfa792c87812
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/network/services

PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/zebra
  SECTION:=net
  CATEGORY:=Base system
  TITLE:=RIP daemon
endef

CONFIGURE_ARGS += \
		--disable-ipv6 \
		--disable-bgpd \
		--disable-ospfd \
		--disable-ospf6d \
		--disable-ripngd \
		--disable-bgp-announce

TARGET_CFLAGS += -g -O2 -Wall
ifeq ("$(strip ${CONFIG_TC_SDK_7_3_245_300})","y")
CONFIGURE_ARGS += --enable-netlink
TMP_CFLAGS := $(TARGET_CFLAGS)
TARGET_CFLAGS = $(filter-out -Os -O2, $(TMP_CFLAGS))
endif

ifeq ("$(strip ${ZCFG_PLATFORM})","BROADCOM")
define Build/Configure
endef
endif

define Package/zebra/install	
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/zebra/zebra $(1)/usr/bin/zebra
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ripd/ripd $(1)/usr/bin/ripd
endef


$(eval $(call BuildPackage,zebra))
