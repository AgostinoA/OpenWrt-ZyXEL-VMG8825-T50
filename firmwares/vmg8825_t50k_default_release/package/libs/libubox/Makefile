include $(TOPDIR)/rules.mk

PKG_NAME:=libubox
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
PKG_VERSION:=2015-11-08
PKG_MIRROR_MD5SUM:=
PKG_RELEASE=$(PKG_SOURCE_VERSION)
PKG_SOURCE_VERSION:=10429bccd0dc5d204635e110a7a8fae7b80d16cb
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.gz
PKG_LICENSE:=ISC
else
PKG_VERSION:=2012-12-18
#PKG_RELEASE=$(PKG_SOURCE_VERSION)

#PKG_SOURCE_PROTO:=git
#PKG_SOURCE_URL:=git://nbd.name/luci2/libubox.git
#PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
#PKG_SOURCE_VERSION:=4d0a00c82c77a9395c992841237e2c06c4606a5e
#PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.gz
PKG_MIRROR_MD5SUM:=e56ec05c389edbf74a40a2889fc23103
PKG_RELEASE=4d0a00c82c77a9395c992841237e2c06c4606a5e
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE).tar.gz
PKG_LICENSE:=GPLv2
endif
PATCH_DIR:=patches-$(PKG_VERSION)
FILES_DIR:=files-$(PKG_VERSION)
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/libs
CMAKE_INSTALL:=1

PKG_LICENSE_FILES:=

PKG_MAINTAINER:=Felix Fietkau <nbd@openwrt.org>

PKG_BUILD_DEPENDS:=lua

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/libubox
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Basic utility library
  DEPENDS:=
endef

define Package/libblobmsg-json
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=blobmsg <-> json conversion library
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
  DEPENDS:=+libjson-c +libubox
else
  DEPENDS:=+libjson +libubox
endif
endef

define Package/jshn
  SECTION:=utils
  CATEGORY:=Utilities
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
  DEPENDS:=+libjson-c +libubox +libblobmsg-json
else
  DEPENDS:=+libjson
endif
  TITLE:=JSON SHell Notation
endef

define Package/jshn/description
  Library for parsing and generating JSON from shell scripts
endef
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
define Package/libjson-script
  SECTION:=utils
  CATEGORY:=Utilities
  DEPENDS:=+libubox
  TITLE:=Minimalistic JSON based scripting engine
endef

define Package/libubox-lua
  SECTION:=libs
  CATEGORY:=Libraries
  DEPENDS:=+libubox +liblua
  TITLE:=Lua binding for the OpenWrt Basic utility library
endef
endif
TARGET_CFLAGS += -I$(STAGING_DIR)/usr/include
CMAKE_OPTIONS = \
	-DLUAPATH=/usr/lib/lua

define Package/libubox/install
	$(INSTALL_DIR) $(1)/lib/
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/libubox.so $(1)/lib/
endef

define Package/libblobmsg-json/install
	$(INSTALL_DIR) $(1)/lib/
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/libblobmsg_json.so $(1)/lib/
endef

define Package/jshn/install
	$(INSTALL_DIR) $(1)/usr/bin $(1)/usr/share/libubox
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/jshn $(1)/usr/bin
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/share/libubox/jshn.sh $(1)/usr/share/libubox
endef
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
define Package/libjson-script/install
	$(INSTALL_DIR) $(1)/lib/
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/libjson_script.so $(1)/lib/
endef

define Package/libubox-lua/install
	$(INSTALL_DIR) $(1)/usr/lib/lua
	$(CP) $(PKG_BUILD_DIR)/lua/uloop.so $(1)/usr/lib/lua/
endef
endif

$(eval $(call BuildPackage,libubox))
$(eval $(call BuildPackage,libblobmsg-json))
$(eval $(call BuildPackage,jshn))
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
$(eval $(call BuildPackage,libjson-script))
$(eval $(call BuildPackage,libubox-lua))
endif