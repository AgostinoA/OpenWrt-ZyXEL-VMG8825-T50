#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=dnsmasq
ifeq ($(CONFIG_dnsmasq_releaseno),"2.78")
PKG_VERSION:=2.78
#COPTS:=HAVE_DBUS
else
PKG_VERSION:=2.67
endif

COPTS:=
PKG_BUILD_DEPENDS:=PACKAGE_zcfg:esmd


PKG_RELEASE:=3

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
#PKG_SOURCE_URL:=http://thekelleys.org.uk/dnsmasq
#PKG_MD5SUM:=f47e5cb8f5bac6343f24b2dbe317ab40
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/network/services
DL_DIR:=$(TOPDIR)/dl

PKG_LICENSE:=GPLv2
PKG_LICENSE_FILES:=COPYING

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(BUILD_VARIANT)/$(PKG_NAME)-$(PKG_VERSION)

PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

PATCH_DIR=patches_$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

ifeq ($(CONFIG_dnsmasq_dnssec),y)
COPTS += -DHAVE_DNSSEC -DNO_GMP -DNO_NETTLE_ECC
#PKG_BUILD_DEPENDS += PACKAGE_nettle:nettle
endif

define Package/dnsmasq/Default
  SECTION:=net
  CATEGORY:=Base system
  TITLE:=A lightweight DNS and DHCP server
  URL:=http://www.thekelleys.org.uk/dnsmasq/
  DEPENDS:=+dnsmasq_dnssec:nettle
endef

define Package/dnsmasq
$(call Package/dnsmasq/Default)
  VARIANT:=nodhcpv6
  MENU:=1
endef

define Package/dnsmasq/config
	select PACKAGE_libzcfg_msg if PACKAGE_zcfg
	select PACKAGE_esmd if PACKAGE_zcfg
	select PACKAGE_nettle if dnsmasq_dnssec
	deselect PACKAGE_nettle if !dnsmasq_dnssec
	deselect dnsmasq_dnssec if dnsmasq_releaseno=2.67
	source "$(SOURCE)/Config.in"
endef

#Disable Dependencies Check
define CheckDependencies
endef

define Package/dnsmasq-dhcpv6
$(call Package/dnsmasq/Default)
  TITLE += (with DHCPv6 support)
  DEPENDS:=@IPV6 +kmod-ipv6
  VARIANT:=dhcpv6
endef

define Package/dnsmasq/description
  It is intended to provide coupled DNS and DHCP service to a LAN.
endef

define Package/dnsmasq-dhcpv6/description
$(call Package/dnsmasq/description)

This is a variant with DHCPv6 support
endef

define Package/dnsmasq/conffiles
/etc/config/dhcp
/etc/dnsmasq.conf
endef

Package/dnsmasq-dhcpv6/conffiles = $(Package/dnsmasq/conffiles)

TARGET_CFLAGS += \
	-ffunction-sections -fdata-sections \
	$(if $(CONFIG_IPV6),,-DNO_IPV6)

ifeq ($(BUILD_VARIANT),nodhcpv6)
  TARGET_CFLAGS += -DNO_DHCP6
endif

TARGET_CFLAGS += -DZYXEL_PATCH

ifeq ($(CONFIG_ZYXEL_DNS_TRAFFIC_ROUTE),y)
TARGET_CFLAGS += -DDNS_TRAFFIC_ROUTE
endif

ifeq ($(CONFIG_ZyXEL_DHCP_OPTION125),y)
TARGET_CFLAGS += -DZyXEL_DHCP_OPTION125
endif

MAKE_FLAGS := \
	COPTS="$(COPTS)" \
	$(TARGET_CONFIGURE_OPTS) \
	CFLAGS="$(TARGET_CFLAGS) -g -Werror" \
	LDFLAGS="-lzcfg_msg -Wl,--gc-sections" \
	PREFIX="/usr"

define Package/dnsmasq/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(CP) $(PKG_INSTALL_DIR)/usr/sbin/dnsmasq $(1)/usr/sbin/
#	$(INSTALL_DIR) $(1)/etc/config
#	$(INSTALL_DATA) ./files/dhcp.conf $(1)/etc/config/dhcp
	$(INSTALL_DIR) $(1)/etc
ifeq ($(strip $(CONFIG_ISKON_CUSTOMIZATION)),y)
	$(INSTALL_DATA) ./files/dnsmasq.conf.ZyXEL.isKon $(1)/etc/dnsmasq.conf
else
	$(INSTALL_DATA) ./files/dnsmasq.conf.ZyXEL $(1)/etc/dnsmasq.conf
endif
	$(INSTALL_DATA) ./files/trust-anchors.conf $(1)/etc/trust-anchors.conf
	$(INSTALL_DIR) $(1)/etc/init.d
ifeq ($(strip $(CONFIG_ISKON_CUSTOMIZATION)),y)
	$(INSTALL_BIN) ./files/dnsmasq.sh.ZyXEL.isKon $(1)/etc/init.d/dnsmasq.sh
else
	$(INSTALL_BIN) ./files/dnsmasq.sh.ZyXEL $(1)/etc/init.d/dnsmasq.sh
endif
	$(INSTALL_DIR) $(1)/etc/rc3.d
	ln -s ../init.d/dnsmasq.sh $(1)/etc/rc3.d/S48dnsmasq
#	$(INSTALL_BIN) ./files/dnsmasq.init $(1)/etc/init.d/dnsmasq
endef

Package/dnsmasq-dhcpv6/install = $(Package/dnsmasq/install)

$(eval $(call BuildPackage,dnsmasq))
$(eval $(call BuildPackage,dnsmasq-dhcpv6))
