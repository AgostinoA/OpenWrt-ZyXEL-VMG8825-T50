#
# Copyright (C) 2006-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libedit
PKG_VERSION:=20080712-2.11

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
#PKG_SOURCE_URL:=@GNU/ncurses
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/libs
#PKG_MD5SUM:=cce05daf61a64501ef6cd8da1f727ec6

PKG_LICENSE:=FREE
PKG_LICENSE_FILES:=README

PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/libedit
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Edit Line library
  DEPENDS:= +libncurses
endef

TARGET_CFLAGS += $(FPIC)
TARGET_LDFLAGS += -lncurses

ifeq ($(CONFIG_ZYXEL_CLI_IDLE_TIMEOUT),y)
TARGET_CFLAGS += -DZYXEL_CLI_IDLE_TIMEOUT
endif

CONFIGURE_ARGS = \
	--host=mips-linux \
	ac_cv_lib_ncurses_tgetent=yes \
	ac_cv_lib_curses_tgetent=no

#MAKE_FLAGS += \
	BUILD_CC="$(HOSTCC)" \
	HOSTCC="$(HOSTCC)" \
	HOSTCCFLAGS="" \
	libs

define Build/Install/Default
	$(MAKE_VARS) \
	$(MAKE) -C $(PKG_BUILD_DIR)/$(MAKE_PATH) \
		$(MAKE_INSTALL_FLAGS) \
		$(1) install;
endef

define Package/libedit/install
	$(INSTALL_DIR) $(1)/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/local/lib/libedit.so* $(1)/lib/
#	$(INSTALL_DIR) $(1)/usr/lib
#	$(CP) $(PKG_INSTALL_DIR)/usr/local/lib/libedit.so* $(1)/usr/lib/
#	$(CP) $(PKG_INSTALL_DIR)/usr/local/lib/libedit.{a,so*} $(1)/usr/lib/
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/local/include/*.h $(1)/usr/include/

	$(INSTALL_DIR) $(1)/usr/include/editline
	$(CP) $(PKG_INSTALL_DIR)/usr/local/include/editline/*.h $(1)/usr/include/editline/

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/local/lib/libedit.{a,so*} $(1)/usr/lib/

endef

$(eval $(call BuildPackage,libedit))
