#
# Copyright (C) 2011-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=mxml
PKG_VERSION:=2.4
PKG_RELEASE:=1
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/libs
PKG_MD5SUM:=8dfa3d25d9a0146bd24324f5111d9db0
PKG_MAINTAINER:=Michael R. Sweet. <mxml@msweet.org>
PKG_FIXUP:=autoreconf
PKG_INSTALL:=1
PKG_LICENSE:=LGPLv2
PKG_LICENSE_FILES:=COPYING

include $(INCLUDE_DIR)/package.mk

define Package/libmxml
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Tiny XML parsing library
  URL:=http://www.msweet.org/downloads.php/Mini-XML
endef

define Package/libmxml/description
  Mini-XML is a small XML library that you can use to read and write XML and XML-like data 
  files in your application without requiring large non-standard libraries. Mini-XML only 
  requires an ANSI C compatible compiler (GCC works, as do most vendors' ANSI C compilers) 
  and a 'make' program.

  Mini-XML supports reading of UTF-8 and UTF-16 and writing of UTF-8 encoded XML files and 
  strings. Data is stored in a linked-list tree structure, preserving the XML data hierarchy,
  and arbitrary element names, attributes, and attribute values are supported with no preset 
  limits, just available memory.
endef

CONFIGURE_ARGS+= \
	--enable-shared \
	--enable-static

ifeq ($(CONFIG_MXML_DISABLE_MULTI_THREAD),y)
	CONFIGURE_ARGS += --disable-threads
endif

define Package/libmxml/config
	config MXML_DISABLE_MULTI_THREAD
		bool "disable multi-threading support"
		depends on PACKAGE_libmxml
		default n
	config MXML_REDUCE_SIZE_FOR_ECONET_SDK
		bool "reduce size for Econet SDK"
		depends on PACKAGE_libmxml
		default n
endef

ifeq ($(CONFIG_MXML_REDUCE_SIZE_FOR_ECONET_SDK),y)
define Build/Prepare
	$(call Build/Prepare/Default)
	sed -i 's/@OPTIM@/@OPTIM@ -DREDUCE_SIZE_FOR_ECONET_SDK/g' $(PKG_BUILD_DIR)/Makefile.in
endef
endif

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/mxml.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libmxml.{a,so*} $(1)/usr/lib/
endef

define Package/libmxml/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libmxml.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libmxml))
