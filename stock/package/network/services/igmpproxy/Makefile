include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=igmpproxy
PKG_VERSION:=0.2.1
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/network/services
PATCH_DIR:=patches-$(PKG_VERSION)
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

ifeq ("$(strip ${ZCFG_PLATFORM})","ECONET")
PLATFORM_PREFIX=CONFIG_$(call qstrip, $(CONFIG_CUSTOM_SDK_PREFIX))_
endif
ifneq ($(strip $(PLATFORM_PREFIX)),)
$(foreach v, \
        $(shell grep "^$(PLATFORM_PREFIX)" $(TOPDIR)/.config), \
        $(eval $(shell echo $v|sed "s/$(PLATFORM_PREFIX)//"|cut -d'=' -f1)=$(shell echo $v|cut -d'=' -f2)))
endif

#PKG_FIXUP:=autoreconf
PKG_LICENSE:=GPL-2.0+

define Package/igmpproxy
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Routing and Redirection
  DEPENDS:=+USE_GLIBC:librt
  TITLE:=Multicast Routing Daemon
  URL:=http://sourceforge.net/projects/igmpproxy
endef

define Package/igmpproxy/description
	IGMPproxy is a simple dynamic Multicast Routing Daemon using
	only IGMP signalling (Internet Group Management Protocol).
endef

define Package/igmpproxy/conffiles
/etc/config/igmpproxy
endef

PACKAGE_CFLAGS = -Dlog=igmpproxy_log

PACKAGE_CFLAGS += -DTRENDCHIP -I$(LINUX_DIR)/user_headers/include
ifneq ($(TC_CFLAGS), )
	PACKAGE_CFLAGS += $(TC_CFLAGS)
endif

ifneq ($(strip $(TCSUPPORT_IGMP_QUICK_LEAVE)),)
	PACKAGE_CFLAGS += -DCONFIG_IGMP_SNOOPING
	PACKAGE_CFLAGS += -DCONFIG_BRIDGE_IGMP_SNOOPING
endif

ifneq ($(strip $(TCSUPPORT_CODE_SHRINK)),)
PACKAGE_CFLAGS += -Os
else
PACKAGE_CFLAGS += -O2
endif

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		CC="$(TARGET_CC)" \
		CFLAGS="$(PACKAGE_CFLAGS) -std=gnu99"
endef

define Package/igmpproxy/install
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./files/igmpproxy.config $(1)/etc/config/igmpproxy
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/igmpproxy.init $(1)/etc/init.d/igmpproxy
	$(INSTALL_DIR) $(1)/bin
	#$(CP) $(PKG_BUILD_DIR)/igmpproxy $(1)/bin/
	$(CP) $(PKG_BUILD_DIR)/src/igmpproxy $(1)/bin/
	$(INSTALL_DIR) $(1)/etc
	$(CP) $(PKG_BUILD_DIR)/igmpproxy.conf $(1)/etc/
endef

$(eval $(call BuildPackage,igmpproxy))
