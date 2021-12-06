include $(TOPDIR)/rules.mk

PKG_NAME:=librest-c
PKG_VERSION:=1.0
PKG_RELEASE:=1

#PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
#PKG_SOURCE_URL:=@ZyXEL_SITE/private/ZyXEL
PKG_SOURCE:=
PKG_SOURCE_URL:=
DL_DIR:=$(TOPDIR)/dl/public

PKG_CAT:=zcat

CURR_DIR=$(shell pwd)
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)


PKG_SRC_DIR:=$(CURR_DIR)/src/$(PKG_NAME)-$(PKG_VERSION)

# PACKAGE_DIR:=$(BIN_DIR)/packages/private

include $(INCLUDE_DIR)/package.mk

define Package/librest-c
	@echo "==> Package/librest-c"
  CATEGORY:= ZyXEL Packages
  TITLE:= ZyXEL Configuration Debugging library
  DESCRIPTION:=
  DEPENDS:= +zcfg +curl +libjson
endef

#Disable Dependencies Check
#define CheckDependencies
#endef

#CFLAGS += -DREST_DEBUG


define Package/librest-c/config
	config ZYXEL_LIB_RESTFUL_API
		bool "librest-c support"
		depends on PACKAGE_librest-c
		default y
endef


define Build/Prepare
	$(MAKE) -C $(PKG_SRC_DIR) \
		CC="$(TARGET_CROSS)gcc" \
		INSTALL_DIR="$(PKG_INSTALL_DIR)" \
		BUILD_DIR="$(BUILD_DIR)" \
		PKG_BUILD_DIR="$(PKG_BUILD_DIR)" \
		clone
endef

define Build/Compile
	@echo "==> Build/Compile"
	$(MAKE) -C $(PKG_BUILD_DIR) \
		CC="$(TARGET_CROSS)gcc" \
		STAGING_DIR=$(STAGING_DIR) \
		USRLIBDIR=$(STAGING_DIR)/usr/lib \
		USRINCDIR=$(STAGING_DIR)/usr/include \
		BUILD_DIR=$(BUILD_DIR) \
		PKG_BUILD_DIR="$(PKG_BUILD_DIR)" \
		INSTALL_DIR="$(PKG_INSTALL_DIR)"
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/librest-c.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/librest-c.so $(1)/usr/lib/
endef

define Package/librest-c/install
	@echo "==> Package/librest-c/install"
	$(INSTALL_DIR) $(1)/lib
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_DIR) $(1)/lib/public
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/librest-c.so $(1)/lib/public
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/rest-c $(1)/bin/rest-c
	ln -s /lib/public/librest-c.so $(1)/lib/librest-c.so
	
endef

define Build/Clean
	@echo "==> Build/Clean"
	-$(MAKE) -C $(PKG_BUILD_DIR) clean
endef

$(eval $(call BuildPackage,librest-c))

