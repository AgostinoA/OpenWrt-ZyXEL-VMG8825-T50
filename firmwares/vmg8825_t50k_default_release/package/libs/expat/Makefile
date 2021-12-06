#
# Copyright (C) 2006-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
	
include $(TOPDIR)/rules.mk

#These lines concatanate the package name and list the URL location from which the package source code is to be downloaded
PKG_NAME:=expat
PKG_VERSION:=1.95.8
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/libs
DL_DIR:=$(TOPDIR)/dl

PKG_CAT:=zcat

PKG_INSTALL:=1

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=COPYING
PKG_MAINTAINER:=Felix Fietkau <nbd@openwrt.org>

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

CONFIGURE_PREFIX=$(PKG_BUILD_DIR)

#MAKE_FLAGS += \
        prefix=$(PKG_BUILD_DIR)\
	exec_prefix=$(PKG_BUILD_DIR)\
	bindir=$(PKG_BUILD_DIR)/bin\
	man1dir=$(PKG_BUILD_DIR)/man/man1

#These lines describe what your package does and its place in the menu config

define Package/expat
SECTION:=libs
CATEGORY:=Libraries
TITLE:= The Expat XML Parser 
endef

define Package/expat/description
Expat is an XML parser library written in C. It is a stream-oriented parser in which an application registers handlers for things the parser might find in the XML document (like start tags).
endef

#For the compile rules you need to specify the cross compiler which needs to be used :

#These lines describe where your binary images are to be installed ¡V its the equivalent to make install

# This particular package is a library and the installation rules reflect it

define Package/libs/expat/compile
	$(MAKE) -C $(PKG_BUILD_DIR)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/include/* $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/lib/libexpat.so* $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
endef

define Package/expat/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/lib/libexpat.so* $(1)/usr/lib
endef

$(eval $(call BuildPackage,expat))

