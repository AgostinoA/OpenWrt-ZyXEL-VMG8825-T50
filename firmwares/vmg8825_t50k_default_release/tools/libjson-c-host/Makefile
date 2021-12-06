#
# Copyright (C) 2006-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=json-c
PKG_VERSION:=0.9
PKG_RELEASE:=2

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
#PKG_SOURCE_URL:=http://oss.metaparadigm.com/json-c/
PKG_MD5SUM:=3a13d264528dcbaf3931b0cede24abae
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/libs

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=COPYING

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

PKG_MAINTAINER:=Felix Fietkau <nbd@openwrt.org>

include $(INCLUDE_DIR)/host-build.mk

TARGET_CFLAGS += $(FPIC)

HOST_CFLAGS += -DBUILD_JSON_C_HOST

$(eval $(call HostBuild))
