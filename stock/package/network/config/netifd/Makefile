include $(TOPDIR)/rules.mk

ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=netifd
PKG_VERSION:=2015-12-16
PKG_RELEASE=$(PKG_SOURCE_VERSION)
PKG_SOURCE_VERSION=245527193e90906451be35c2b8e972b8712ea6ab
PKG_SOURCE_URL:=@ZyXEL_SITE/WIFI_Router

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.gz
else
PKG_NAME:=netifd
PKG_VERSION:=2012-12-17.1
PKG_RELEASE=$(PKG_SOURCE_VERSION)

#PKG_SOURCE_PROTO:=git
#PKG_SOURCE_URL:=git://nbd.name/luci2/netifd.git
#PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION1:=2eca28705a27ab37ee902308af2c134c64c95e61
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION1).tar.gz
PKG_MAINTAINER:=Felix Fietkau <nbd@openwrt.org>
# PKG_MIRROR_MD5SUM:=
# CMAKE_INSTALL:=1
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/network/config
endif
PATCH_DIR:=patches-$(PKG_VERSION)
FILES_DIR:=files-$(PKG_VERSION)
PKG_MAINTAINER:=Felix Fietkau <nbd@openwrt.org>
# PKG_MIRROR_MD5SUM:=
# CMAKE_INSTALL:=1

PKG_LICENSE:=GPL-2.0
PKG_LICENSE_FILES:=

PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/netifd
  SECTION:=base
  CATEGORY:=Base system
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
  DEPENDS:=+libuci +libnl-tiny +libubus +ubus +ubusd +jshn +libubox
else
ifeq ($(CONFIG_PACKAGE_libnl),y)
  DEPENDS:=+libuci +libnl +libubus +ubus +ubusd +jshn
else
  DEPENDS:=+libuci +libnl-tiny +libubus +ubus +ubusd +jshn
endif
endif
  TITLE:=OpenWrt Network Interface Configuration Daemon
endef


ifeq ($(CONFIG_PACKAGE_libnl),y)
LIB_NL:=$(STAGING_DIR)/usr/include/libnl
LIB_LIBS:=-lnl
else
LIB_NL:=$(STAGING_DIR)/usr/include/libnl-tiny
LIB_LIBS:=-lnl-tiny
endif

TARGET_CFLAGS += \
	-I$(LIB_NL) \
	-I$(STAGING_DIR)/usr/include

CMAKE_OPTIONS += \
	-DLIBNL_LIBS=$(LIB_LIBS) \
	-DDEBUG=1

define Package/netifd/install
	$(INSTALL_DIR) $(1)/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/netifd $(1)/sbin/
	$(CP) ./$(FILES_DIR)/* $(1)/
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
	$(CP) $(PKG_BUILD_DIR)/scripts/* $(1)/lib/netifd/
else
	$(CP) $(PKG_BUILD_DIR)/dummy/netifd-proto.sh $(1)/lib/netifd/
endif
endef

$(eval $(call BuildPackage,netifd))
