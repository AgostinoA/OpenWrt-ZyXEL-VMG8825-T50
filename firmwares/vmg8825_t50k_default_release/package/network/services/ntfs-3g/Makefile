#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ntfs-3g
PKG_VERSION:=2013.1.13
PKG_RELEASE:=1

PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/network/services

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tgz

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

# MAKE_PATH:=test
# CONFIGURE_PATH:=test

define Package/ntfs-3g
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Stable Read/Write NTFS Driver
  SUBMENU:=Filesystem
  DEPENDS:= +libpthread
#  URL:=
endef

define Package/ntfs-3g/description
	Ntfs-3g is a NTFS driver, which can create, remove, rename,
	move files, directories, hard links, and streams. It can read
	and write files, including streams and sparse files. It can
	handle special files like symbolic links, devices, and FIFOs.
	Moreover it can also read transparently compressed files.
endef

#Disable Dependencies Check
define CheckDependencies
endef

define Package/ntfs-3g/config
endef

CONFIGURE_ARGS += \
		--enable-shared \
		--enable-static \

MAKE_FLAGS += DYNEXP=

# define Build/Compile
	# $(MAKE) -C $(PKG_BUILD_DIR)/
# endef

define Package/ntfs-3g/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_DIR) $(1)/usr/bin
	$(CP) $(PKG_BUILD_DIR)/libntfs-3g/.libs/libntfs-3g.so* $(1)/usr/lib/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/.libs/ntfs-3g $(1)/usr/bin/
	$(STRIP) $(1)/usr/bin/ntfs-3g
endef

$(eval $(call BuildPackage,ntfs-3g))
