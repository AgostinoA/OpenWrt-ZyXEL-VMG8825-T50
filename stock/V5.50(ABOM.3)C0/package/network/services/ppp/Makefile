#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ppp
PKG_VERSION:=2.4.3
PKG_RELEASE:=7

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
#PKG_SOURCE_URL:=ftp://ftp.samba.org/pub/ppp/
#PKG_MD5SUM:=4621bc56167b6953ec4071043fe0ec57
PKG_MAINTAINER:=Felix Fietkau <nbd@openwrt.org>
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/network/services
DL_DIR:=$(TOPDIR)/dl

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(BUILD_VARIANT)/$(PKG_NAME)-$(PKG_VERSION)

PKG_BUILD_DEPENDS:=libpcap

PKG_BUILD_PARALLEL:=1
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

define Package/ppp/Default
  SECTION:=net
  CATEGORY:=Network
  MAINTAINER:=Jo-Philipp Wich <xm@subsignal.org>
  URL:=http://ppp.samba.org/
endef

define Package/ppp
$(call Package/ppp/Default)
  DEPENDS:=+libjson +libzcfg_msg +kmod-ppp
  TITLE:=PPP daemon
  VARIANT:=default
endef

define Package/ppp/description
This package contains the PPP (Point-to-Point Protocol) daemon.
endef

define Package/ppp-mod-pppoa
$(call Package/ppp/Default)
  DEPENDS:=@(PACKAGE_ppp) +libjson +libzcfg_msg +linux-atm +kmod-pppoa
  TITLE:=PPPoA plugin
endef

define Package/ppp-mod-pppoa/description
This package contains a PPPoA (PPP over ATM) plugin for ppp.
endef

define Package/ppp-mod-pppoe
$(call Package/ppp/Default)
  DEPENDS:=@(PACKAGE_ppp) +libjson +libzcfg_msg +kmod-pppoe
  TITLE:=PPPoE plugin
endef

define Package/ppp-mod-pppoe/description
This package contains a PPPoE (PPP over Ethernet) plugin for ppp.
endef

define Package/ppp-mod-radius
$(call Package/ppp/Default)
  DEPENDS:=@(PACKAGE_ppp)
  TITLE:=RADIUS plugin
endef

define Package/ppp-mod-radius/description
This package contains a RADIUS (Remote Authentication Dial-In User Service)
plugin for ppp.
endef

define Package/chat
$(call Package/ppp/Default)
  DEPENDS:=@(PACKAGE_ppp) +libjson +libzcfg_msg 
  TITLE:=Establish conversation with a modem
endef

define Package/chat/description
This package contains an utility to establish conversation with other PPP servers
(via a modem).
endef

define Package/pppdump
$(call Package/ppp/Default)
  DEPENDS:=@(PACKAGE_ppp)
  TITLE:=Read PPP record file
endef

define Package/pppdump/description
This package contains an utility to read PPP record file.
endef

define Package/pppstats
$(call Package/ppp/Default)
  DEPENDS:=@(PACKAGE_ppp)
  TITLE:=Report PPP statistics
endef

define Package/pppstats/description
This package contains an utility to report PPP statistics.
endef

define Build/Configure
$(call Build/Configure/Default,, \
	UNAME_S="Linux" \
	UNAME_R="$(LINUX_VERSION)" \
	UNAME_M="$(ARCH)" \
)
endef

TARGET_LDFLAGS += -ljson -lzcfg_msg
#TARGET_CFLAGS += -I$(LINUX_DIR) -DCONFIG_MIPS_BRCM -DCONFIG_BCM_KF_ATM_BACKEND

ifeq ("$(strip ${ZCFG_PLATFORM})","BROADCOM")
TARGET_CFLAGS += -I$(LINUX_DIR) -DCONFIG_MIPS_BRCM -DCONFIG_BCM_KF_ATM_BACKEND
endif

ifeq ("$(strip ${ZCFG_PLATFORM})","ECONET")
TARGET_CFLAGS += -I$(LINUX_DIR)/user_headers/include \
					$(TARGET_CFLAGS)
endif

TARGET_CFLAGS += -D$(ZCFG_PLATFORM)_PLATFORM

ifeq ($(CONFIG_ZYXEL_USA_PRODUCT),y)
TARGET_CFLAGS += -DUSA_PRODUCT
endif

ifeq ($(CONFIG_ZYXEL_FAKE_IP_169_254_X_X),y)
TARGET_CFLAGS += -DZYXEL_FAKE_IP_169_254_X_X
endif

ifeq ($(CONFIG_KERNEL_ZYXEL_PPTP_SUPPORT),y)
TARGET_CFLAGS += -DCONFIG_PPTP_SUPPORT
endif

ifeq ($(CONFIG_SEND_PADT_BEFORE_DISCOVERY),y)
TARGET_CFLAGS += -DSEND_PADT_BEFORE_DISCOVERY
endif

ifeq ($(CONFIG_WIND_ITALY_CUSTOMIZATION),y)
TARGET_CFLAGS += -DWIND_ITALY_CUSTOMIZATION
endif

ifeq ($(CONFIG_XPON_SUPPORT),y)
TARGET_CFLAGS += -DXPON_SUPPORT
endif

ifeq ($(CONFIG_ABOG_CUSTOMIZATION),y)
TARGET_CFLAGS += -DABOG_CUSTOMIZATION
endif

export CONFIG_ZyXEL_WEB_REDIRECT CONFIG_ZyXEL_PPP_LCP_ECHO

MAKE_FLAGS += COPTS="$(TARGET_CFLAGS)" \
		LDOPTS="$(TARGET_LDFLAGS)" \
		PRECOMPILED_FILTER=1 \
		STAGING_DIR="$(STAGING_DIR)"

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/include/pppd $(1)/usr/include/
endef

define Package/ppp/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/sbin/pppd $(1)/bin/
endef

define Package/ppp-mod-pppoa/install
	$(INSTALL_DIR) $(1)/lib
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/lib/pppd/$(PKG_VERSION)/pppoatm.so $(1)/lib
endef

define Package/ppp-mod-pppoe/install
	$(INSTALL_DIR) $(1)/lib
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/lib/pppd/$(PKG_VERSION)/rp-pppoe.so $(1)/lib
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/sbin/pppoe-discovery $(1)/bin/
endef

define Package/ppp-mod-radius/install
	$(INSTALL_DIR) $(1)/lib
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/lib/pppd/$(PKG_VERSION)/radius.so $(1)/lib
endef

define Package/chat/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/sbin/chat $(1)/bin/
endef

define Package/pppdump/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/sbin/pppdump $(1)/bin/
endef

define Package/pppstats/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/sbin/pppstats $(1)/bin/
endef

$(eval $(call BuildPackage,ppp))
$(eval $(call BuildPackage,ppp-mod-pppoa))
$(eval $(call BuildPackage,ppp-mod-pppoe))
$(eval $(call BuildPackage,ppp-mod-radius))
$(eval $(call BuildPackage,chat))
$(eval $(call BuildPackage,pppdump))
$(eval $(call BuildPackage,pppstats))
