# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$
	
include $(TOPDIR)/rules.mk

#These lines concatanate the package name and list the URL location from which the package source code is to be downloaded
PKG_NAME:=libzcfg_fe_rdm_access
PKG_VERSION:=1.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
#PKG_SOURCE_URL:=http://www.cs.uh.edu/~vivekian/downloads/
PKG_SOURCE_URL:=@ZyXEL_SITE/public/ZyXEL
DL_DIR:=$(TOPDIR)/dl/public/zyxel

#md5 can be computed using the md5sum utility available on linux

PKG_CAT:=zcat

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

PKG_BUILD_DEPENDS:=zcfg libzcfg_msg libzcmd_tool

#These lines describe what your package does and its place in the menu config

define Package/libzcfg_fe_rdm_access
SECTION:=net
CATEGORY:=Zyxel Packages
TITLE:= ZyXEL Configuration Management Frontend Data Model Access Library 
DESCRIPTION:=
#DEPENDS:=zcfg +libzcfg_msg +libzcmd_tool
endef

#Disable Dependencies Check
define CheckDependencies
endef

#For the compile rules you need to specify the cross compiler which needs to be used :


#These lines describe where your binary images are to be installed ¡V its the equivalent to make install

# This particular package is a library and the installation rules reflect it

define Package/libzcfg_fe_rdm_access/compile
	$(MAKE) -C $(PKG_BUILD_DIR)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/*.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/libzcfg_fe_rdm_access.so $(1)/usr/lib/
endef

define Package/libzcfg_fe_rdm_access/install
	$(INSTALL_DIR) $(1)/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(PKG_NAME).so $(1)/lib
#	$(INSTALL_DIR) $(1)/lib/public
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libzcfg_fe_rdm_access.so $(1)/lib/public
#	ln -s /lib/public/libzcfg_fe_rdm_access.so $(1)/lib/libzcfg_fe_rdm_access.so
endef

$(eval $(call BuildPackage,libzcfg_fe_rdm_access))

