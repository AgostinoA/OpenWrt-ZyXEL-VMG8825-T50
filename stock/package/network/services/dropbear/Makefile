#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=dropbear

PKG_VERSION:=2018.76
#PKG_VERSION:=2012.55

ifeq ("$(strip $(PKG_VERSION))", "2018.76")
PKG_MD5SUM:=c3912f7fcdcc57c99937e4a79480d2c2
PKG_RELEASE:=4
else ifeq ("$(strip $(PKG_VERSION))", "2012.55")
PKG_MD5SUM:=8c784baec3054cdb1bb4bfa792c87812
PKG_RELEASE:=3
endif

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PATCH_DIR:=patches-$(PKG_VERSION)

#PKG_SOURCE_URL:= \
	http://matt.ucc.asn.au/dropbear/releases/ \
	http://www.mirrors.wiretapped.net/security/cryptography/apps/ssh/dropbear/
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/network/services

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE libtomcrypt/LICENSE libtommath/LICENSE

PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/dropbear/Default
  URL:=http://matt.ucc.asn.au/dropbear/
endef

define Package/dropbear
  $(call Package/dropbear/Default)
  SECTION:=net
  CATEGORY:=Base system
  TITLE:=Small SSH2 client/server
  DEPENDS:=+libzcfg_msg +libzcmd_tool +libjson +libzcfg_fe_rdm_access +libzcfg_fe_rdm_struct +libzyutil
endef

define Package/dropbear/description
 A small SSH2 server/client designed for small memory environments.
endef

define Package/dropbear/conffiles
/etc/dropbear/dropbear_rsa_host_key
/etc/dropbear/dropbear_dss_host_key 
/etc/config/dropbear 
endef

define Package/dropbearconvert
  $(call Package/dropbear/Default)
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Utility for converting SSH keys
endef

CONFIGURE_ARGS += \
	--with-shared \
	--disable-pam \
	--enable-openpty \
	--enable-syslog \
	$(if $(CONFIG_SHADOW_PASSWORDS),,--disable-shadow) \
	--disable-lastlog \
	--disable-utmp \
	--disable-utmpx \
	--disable-wtmp \
	--disable-wtmpx \
	--disable-loginfunc \
	--disable-pututline \
	--disable-pututxline \
	--disable-zlib \
	--enable-bundled-libtom

TARGET_CFLAGS += -DARGTYPE=3 -ffunction-sections -fdata-sections
TARGET_LDFLAGS += -Wl,--gc-sections
BUILD_APPS = scp
LN_SCP = ln -sf ../sbin/dropbear $(1)/usr/bin/scp
LN_DBCLIENT = ln -sf ../sbin/dropbear $(1)/usr/bin/dbclient
export BUILD_APPS
export LN_SCP
export LN_DBCLIENT

ifeq ($(CONFIG_ABOG_CUSTOMIZATION),y)
TARGET_CFLAGS += -DABOG_CUSTOMIZATION
endif

#Remote Access privilege feature
export CONFIG_ZYXEL_REMOTE_ACCESS_PRIVILEGE
export CONFIG_ZYXEL_REMOTE_ACCOUNT_ACCESS_PRIVILEGE
export CONFIG_ZYXEL_REMOMGMT_ONLY_HTTPS_ALLOWS_FOR_WLAN_CONNECT

#CLI idle timeout feature
export CONFIG_ZYXEL_CLI_IDLE_TIMEOUT

define Build/Compile
	+$(MAKE) $(PKG_JOBS) -C $(PKG_BUILD_DIR) \
		$(TARGET_CONFIGURE_OPTS) \
		PROGRAMS="dropbear dbclient dropbearkey $(BUILD_APPS)" \
		MULTI=1 SCPPROGRESS=1
#		PROGRAMS="dropbear dbclient dropbearkey scp" \
#		MULTI=1 SCPPROGRESS=1
#	+$(MAKE) $(PKG_JOBS) -C $(PKG_BUILD_DIR) \
		$(TARGET_CONFIGURE_OPTS) \
		PROGRAMS="dropbearconvert"
endef

define Package/dropbear/install	
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dropbearmulti $(1)/usr/sbin/dropbear
	$(INSTALL_DIR) $(1)/usr/bin
	$(LN_SCP)
	$(LN_DBCLIENT)
#	ln -sf ../sbin/dropbear $(1)/usr/bin/scp
#	ln -sf ../sbin/dropbear $(1)/usr/bin/ssh
#	ln -sf ../sbin/dropbear $(1)/usr/bin/dbclient
	ln -sf ../sbin/dropbear $(1)/usr/bin/dropbearkey
#	$(INSTALL_DIR) $(1)/etc/config
#	$(INSTALL_DATA) ./files/dropbear.config $(1)/etc/config/dropbear
#	$(INSTALL_DIR) $(1)/etc/init.d
#	$(INSTALL_BIN) ./files/dropbear.init $(1)/etc/init.d/dropbear
#	$(INSTALL_DIR) $(1)/usr/lib/opkg/info
#	$(INSTALL_DIR) $(1)/etc/dropbear
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/openssl.cnf $(1)/etc/config
#	touch $(1)/etc/dropbear/dropbear_rsa_host_key
#	touch $(1)/etc/dropbear/dropbear_dss_host_key
	$(INSTALL_DIR) -d -m 755 $(1)/etc/mycert
ifeq ("$(strip $(PKG_VERSION))", "2018.76")
	$(INSTALL_DIR) $(1)/etc/dropbear
	ln -s /data/dropbear/dropbear_dss_host_key $(1)/etc/dropbear/dropbear_dss_host_key
	ln -s /data/dropbear/dropbear_rsa_host_key $(1)/etc/dropbear/dropbear_rsa_host_key
	ln -s /data/dropbear/dropbear_rsa_host_key $(1)/etc/mycert/ssh.rsa
else ifeq ("$(strip $(PKG_VERSION))", "2012.55")
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dropbear_rsa_host_key.ZyXEL $(1)/etc/mycert/ssh.rsa
endif
endef

#define Package/dropbearconvert/install
#	$(INSTALL_DIR) $(1)/usr/bin
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dropbearconvert $(1)/usr/bin/dropbearconvert
#endef

$(eval $(call BuildPackage,dropbear))
#$(eval $(call BuildPackage,dropbearconvert))
