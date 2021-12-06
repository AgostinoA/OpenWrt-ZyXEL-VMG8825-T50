#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

ifeq ($(CONFIG_TARGET_ar71xx),y)
PRODUCT_NAME=$(shell echo $(PROFILE)|tr '[:lower:]' '[:upper:]')
else
PRODUCT_NAME=$(shell echo $(SUBTARGET)|tr '[:lower:]' '[:upper:]')
endif
$(warning product_name-->$(PRODUCT_NAME))

PKG_NAME:=miniupnpd
PKG_VERSION:=1.6.20110730
PKG_RELEASE:=4

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_MD5SUM:=8bd5c0447b6dc1101b96e958ee67d3ea
PKG_SOURCE_URL:=@ZyXEL_SITE/WIFI_Router
#PKG_SOURCE_PROTO:=svn_pkg
#PKG_SOURCE_VERSION:=HEAD

PATCH_DIR:=patches

include $(INCLUDE_DIR)/package.mk

define Package/miniupnpd
  SECTION:=net
  CATEGORY:=Network
  DEPENDS:=+iptables +libip4tc
  TITLE:=Lightweight UPnP daemon
  SUBMENU:=Firewall
  URL:=http://miniupnp.free.fr/
  MAINTAINER:=Daniel Dickinson <openwrt@cshore.neomailbox.net>
endef

define Package/miniupnpd/conffiles
/etc/config/upnpd
endef

UPNP_LDFLAGS=-L$(STAGING_DIR)/usr/lib -L $(STAGING_DIR)/lib
ifeq ($(CONFIG_BE8_MODE),y)
UPNP_LDFLAGS+=-Xlinker -EB -Xlinker --be8
endif

ifeq ($(CONFIG_UBOOT_ZYXEL_TARGET),"emg6765abhr")
	addFLAGS = -DEMG6765abhr
else
	addFLAGS = 
endif

define Build/Compile
	echo "OpenWRT/$(OPENWRTVERSION)" | tr \(\)\  _ >$(PKG_BUILD_DIR)/os.openwrt
	$(MAKE) -C $(PKG_BUILD_DIR) -f Makefile.linux \
		$(TARGET_CONFIGURE_OPTS) \
		STAGING_DIR="$(STAGING_DIR)" \
		CC="$(TARGET_CC)" \
		TARGET_OPENWRT=1 \
		CFLAGS="$(TARGET_CFLAGS) -I$(STAGING_DIR)/usr/include -I$(firstword $(wildcard $(KERNEL_BUILD_DIR)/iptables-*/include)) -DIPTABLES_143 $(addFLAGS)" \
		LDFLAGS="$(UPNP_LDFLAGS)" \
		LIBS="$(STAGING_DIR)/usr/lib/libip4tc.a"
endef

define Package/miniupnpd/install
	$(INSTALL_DIR) $(1)/usr/sbin $(1)/etc/init.d $(1)/etc/config $(1)/etc/hotplug.d/iface #$(1)/etc/hotplug.d/firewall
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/miniupnpd $(1)/usr/sbin/miniupnpd
	$(INSTALL_BIN) ./files/miniupnpd.init $(1)/etc/init.d/miniupnpd
	$(INSTALL_CONF) ./files/upnpd.config $(1)/etc/config/upnpd
	$(INSTALL_DATA) ./files/miniupnpd.hotplug $(1)/etc/hotplug.d/iface/14-miniupnpd
#	$(INSTALL_DATA) ./files/miniupnpd.firewall.hotplug $(1)/etc/hotplug.d/firewall/50-miniupnpd
	$(INSTALL_DIR) $(1)/usr/share/miniupnpd
	$(INSTALL_DIR) $(1)/sbin
	
ifeq ($(CONFIG_UBOOT_ZYXEL_TARGET),"emg6765abhr")
	$(INSTALL_BIN) ./files/act_miniupnpd_emg6765abhr $(1)/sbin/act_miniupnpd
	$(INSTALL_CONF) ./files/upnpd.config_emg6765abhr $(1)/etc/config/upnpd	
else
	$(INSTALL_BIN) ./files/act_miniupnpd $(1)/sbin/act_miniupnpd
	$(INSTALL_CONF) ./files/upnpd.config $(1)/etc/config/upnpd
endif
endef

$(eval $(call BuildPackage,miniupnpd))
