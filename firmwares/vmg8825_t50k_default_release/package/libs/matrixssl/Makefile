#
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=matrixssl
PKG_VERSION:=1-8
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-open.tar.gz
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/libs
PKG_MD5SUM:=28dc5a21be816738a89507d76cc52de6

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)-open

PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

# __ZYXEL__start,
# Replace 'CONFIG_ECONETSDK_' for menuconfig only supports a single prompt problem.
ifeq ("$(strip ${ZCFG_PLATFORM})","ECONET")
PLATFORM_PREFIX=CONFIG_$(call qstrip, $(CONFIG_CUSTOM_SDK_PREFIX))_
endif
ifneq ($(strip $(PLATFORM_PREFIX)),)
$(foreach v, \
        $(shell grep "^$(PLATFORM_PREFIX)" $(TOPDIR)/.config), \
        $(eval $(shell echo $v|sed "s/$(PLATFORM_PREFIX)//"|cut -d'=' -f1)=$(shell echo $v|cut -d'=' -f2)))
endif
# __ZYXEL__end

define Package/libmatrixssl
  SECTION:=libs
  SUBMENU:=SSL
  CATEGORY:=Libraries
  DEPENDS:=+libpthread
  TITLE:=Embedded SSL implementation
  URL:=http://www.matrixssl.org/
endef

define Build/Configure
endef

TARGET_CFLAGS += $(FPIC)
DFLAGS = "$(TARGET_CFLAGS) -Wall"

ifneq ($(CONFIG_MATRIXSSL_SUPPORT_ECONET_SDK),)
ECONET_SDK_FLAGS = SUPPORT_ECONET_SDK=y
DFLAGS = -mips32r2 -msoft-float -O3 -fPIC
ifneq ($(strip $(TCSUPPORT_CWMP_SSL_MULTICA)),)
ECONET_SDK_FLAGS += CWMP_MULTI_CA=1
endif
endif

define Package/libmatrixssl/config
        config MATRIXSSL_SUPPORT_ECONET_SDK
                bool "support Econet SDK"
                depends on PACKAGE_libmatrixssl
                default n
endef

define Build/Compile
	+$(MAKE) $(PKG_JOBS) -C $(PKG_BUILD_DIR)/src \
		$(TARGET_CONFIGURE_OPTS) \
		$(ECONET_SDK_FLAGS) \
		DFLAGS="$(DFLAGS)"
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include/matrixSsl
	$(CP) $(PKG_BUILD_DIR)/matrixSsl.h $(1)/usr/include/matrixSsl/
	ln -sf matrixSsl/matrixSsl.h $(1)/usr/include/matrixSsl.h
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/src/libmatrixssl.so* $(1)/usr/lib/
endef

define Package/libmatrixssl/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/src/libmatrixssl.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libmatrixssl))
