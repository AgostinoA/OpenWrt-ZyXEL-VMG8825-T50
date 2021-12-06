# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$
	
include $(TOPDIR)/rules.mk

#These lines concatanate the package name and list the URL location from which the package source code is to be downloaded
PKG_NAME:=libzcfg_fe_rdm_string
PKG_VERSION:=1.0
PKG_RELEASE:=1


#ifeq ($(CONFIG_ZCFG_LOG_USE_DEBUGCFG),y)
#ZCFLAGS:=-DZCFG_LOG_USE_DEBUGCFG
#endif

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_SOURCE_URL:=@ZyXEL_SITE/public/ZyXEL
DL_DIR:=$(TOPDIR)/dl/public/zyxel

PKG_CAT:=zcat

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

export CONFIG_ZCFG_LOG_USE_DEBUGCFG

include $(INCLUDE_DIR)/package.mk

#These lines describe what your package does and its place in the menu config


define Package/libzcfg_fe_rdm_string
SECTION:=net
CATEGORY:=Zyxel Packages
TITLE:= ZyXEL Configuration Management Frontend Data Model Access Library By Using Json String
DESCRIPTION:=
#DEPENDS:=+zcfg +libzcfg_msg +libzcfg_fe_rdm_access +libjson
DEPENDS:=+libzcfg_msg +libzcfg_fe_rdm_access +libjson
endef

PKG_BUILD_DEPENDS:=PACKAGE_zcfg:zcfg

define Package/libzcfg_fe_rdm_string/config
    select PACKAGE_libzcfg_msg if PACKAGE_zcfg
	select PACKAGE_libzcfg_fe_rdm_access if PACKAGE_zcfg
	select PACKAGE_libjson if PACKAGE_zcfg
endef


#For the compile rules you need to specify the cross compiler which needs to be used :


#These lines describe where your binary images are to be installed �V its the equivalent to make install

# This particular package is a library and the installation rules reflect it

define Package/libzcfg_fe_rdm_string/compile
	$(MAKE) -C $(PKG_BUILD_DIR)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/*.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/libzcfg_fe_rdm_string.so $(1)/usr/lib/
endef

define Package/libzcfg_fe_rdm_string/install
	$(INSTALL_DIR) $(1)/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(PKG_NAME).so $(1)/lib
#	$(INSTALL_DIR) $(1)/lib/public
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libzcfg_fe_rdm_string.so $(1)/lib/public
#	ln -s /lib/public/libzcfg_fe_rdm_string.so $(1)/lib/libzcfg_fe_rdm_string.so
endef

$(eval $(call BuildPackage,libzcfg_fe_rdm_string))

