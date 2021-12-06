#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=syslog-ng
#PKG_VERSION:=3.0.4
PKG_VERSION:=2.0.10
#PKG_VERSION:=3.1.0
PKG_RELEASE:=1
#PKG_VERSION:=1.6.12
#PKG_RELEASE:=6
#PKG_MD5SUM:=a3cbfdb6e1e5beea181a7349749719f3

#PKG_SOURCE_URL:= \
	http://www.balabit.com/downloads/files/syslog-ng/sources/1.6/src \
	http://www.balabit.com/downloads/files/syslog-ng/stable/src
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/utils

PKG_SOURCE:=$(PKG_NAME)_$(PKG_VERSION).tar.gz

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/syslog-ng
  SECTION:=admin
  CATEGORY:=Administration
  TITLE:=A powerful syslog daemon
  URL:=http://www.balabit.com/products/syslog_ng/
endef

define Package/syslog-ng/config
	select PACKAGE_libzcfg_msg if PACKAGE_zcfg
	select PACKAGE_libzcmd_tool if PACKAGE_zcfg
	select PACKAGE_libjson if PACKAGE_zcfg
	select PACKAGE_libzcfg_fe_rdm_access if PACKAGE_zcfg
	select PACKAGE_libzcfg_fe_rdm_struct if PACKAGE_zcfg
	select PACKAGE_libzcfg_fe_dal if PACKAGE_zcfg
endef

define Package/syslog-ng/description
	syslog-ng reads and logs messages to the system console, log
	files, other machines and/or users as specified by its
	configuration file.
endef

#CONFIGURE_ARGS += \
	--sysconfdir=/etc \
	--disable-spoof-source \
	--disable-dependency-tracking \
	--enable-ipv6

#CONFIGURE_VARS += \
	blb_cv_static_glib=yes

#Disable Dependencies Check
define CheckDependencies
endef

ifeq ("$(strip ${ZCFG_PLATFORM})","BROADCOM")
ifeq ("$(strip ${BRCM_SDK_VERSION})","502L04")
TARGET_CFLAGS += -DSUPPORT_502L04
endif
endif


define Build/Configure
	$(call Build/Configure/Default, \
		--disable-dependency-tracking \
		--sysconfdir=/etc \
		--disable-spoof-source \
		--enable-ipv6 \
		--enable-dynamic-linking \
		--enable-glibtest=no \
		CPPFLAGS="-I$(STAGING_DIR)/usr/include $(TARGET_CPPFLAGS)" \
		LDFLAGS="-L$(STAGING_DIR)/usr/lib $(TARGET_LDFLAGS)" \
		LIBS="-ljson -lzcfg_msg -lzcmd_tool -lzcfg_fe_rdm_access -lzcfg_fe_rdm_struct" \
		GLIB_CFLAGS="-I$(STAGING_DIR)/usr/include $(TARGET_CPPFLAGS)" \
		GLIB_LIBS="$(STAGING_DIR)/usr/lib/libglib-2.0.so" \
		EVTLOG_CFLAGS="-I$(STAGING_DIR)/usr/include/eventlog $(TARGET_CPPFLAGS)" \
		EVTLOG_LIBS="$(STAGING_DIR)/usr/lib/libevtlog.so" \
	)
endef

define Package/syslog-ng/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/syslog-ng $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc/syslog-ng
	$(INSTALL_DATA) ./files/syslog-ng_init.conf $(1)/etc/syslog-ng/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_DIR) $(1)/etc/rc3.d
	$(CP) ./files/syslog-ng.sh $(1)/etc/init.d
	ln -s ../init.d/syslog-ng.sh $(1)/etc/rc3.d/S46syslog-ng
	$(CP) ./files/crond.sh $(1)/etc/init.d
	ln -s ../init.d/crond.sh $(1)/etc/rc3.d/S46crond
endef

$(eval $(call BuildPackage,syslog-ng))
