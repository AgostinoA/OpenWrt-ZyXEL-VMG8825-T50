#
# Copyright (C) 2007-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=iw
ifeq ("$(strip ${ZCFG_PLATFORM})", $(filter "$(strip ${ZCFG_PLATFORM})","QUALCOMM" "BROADCOM"))
PKG_VERSION:=4.3
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
#PKG_SOURCE_URL:=https://www.kernel.org/pub/software/network/iw
PKG_SOURCE_URL:=@ZyXEL_SITE/WIFI_Router
PKG_MD5SUM:=7adec72e91ebdd9c55429fa34a23a6f5

PKG_MAINTAINER:=Felix Fietkau <nbd@openwrt.org>
PKG_LICENSE:=GPL-2.0
else
PKG_VERSION:=3.6
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
#PKG_SOURCE_URL:=http://wireless.kernel.org/download/iw/
PKG_MD5SUM:=1c18bfbbc8773629e5e8ac733a39540c
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/network/utils

PKG_MAINTAINER:=Felix Fietkau <nbd@openwrt.org>

endif
PATCH_DIR:=patches-$(PKG_VERSION)
include $(INCLUDE_DIR)/package.mk

define Package/iw
  SECTION:=net
  CATEGORY:=Network
  TITLE:=cfg80211 interface configuration utility
  URL:=http://wireless.kernel.org/en/users/Documentation/iw
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
  DEPENDS:= +libnl-tiny
else
ifeq ($(CONFIG_PACKAGE_libnl),y)
  DEPENDS:= +libnl @(!(TARGET_avr32||TARGET_etrax)||BROKEN)
else
  DEPENDS:= +libnl-tiny @(!(TARGET_avr32||TARGET_etrax)||BROKEN)
endif
endif
endef

define Build/Configure
	echo "const char iw_version[] = \"$(PKG_VERSION)\";" > $(PKG_BUILD_DIR)/version.c
	rm -f $(PKG_BUILD_DIR)/version.sh
	touch $(PKG_BUILD_DIR)/version.sh
	chmod +x $(PKG_BUILD_DIR)/version.sh
endef


ifeq ($(CONFIG_PACKAGE_libnl),y)
LIB_NL:=$(STAGING_DIR)/usr/include/libnl
LIB_NLLIBNAME:="libnl"
LIB_LIBS:="-lm -lnl"
else
LIB_NL:=$(STAGING_DIR)/usr/include/libnl-tiny
LIB_NLLIBNAME:="libnl-tiny"
LIB_LIBS:="-lm -lnl-tiny"

endif

TARGET_CPPFLAGS:= \
	-I$(LIB_NL) \
	$(TARGET_CPPFLAGS) \
	-DCONFIG_LIBNL20 \
	-D_GNU_SOURCE
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
MAKE_FLAGS += \
	CFLAGS="$(TARGET_CPPFLAGS) $(TARGET_CFLAGS) -ffunction-sections -fdata-sections" \
	LDFLAGS="$(TARGET_LDFLAGS) -Wl,--gc-sections" \
	NL1FOUND="" NL2FOUND=Y \
	NLLIBNAME=$(LIB_NLLIBNAME) \
	LIBS=$(LIB_LIBS) \
	V=1
else
MAKE_FLAGS += \
	CFLAGS="$(TARGET_CPPFLAGS) $(TARGET_CFLAGS)" \
	LDFLAGS="$(TARGET_LDFLAGS)" \
	NL1FOUND="" NL2FOUND=Y \
	NLLIBNAME=$(LIB_NLLIBNAME) \
	LIBS=$(LIB_LIBS) \
	V=1

endif
define Package/iw/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/iw $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,iw))
