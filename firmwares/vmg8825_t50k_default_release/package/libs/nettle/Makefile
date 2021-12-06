include $(TOPDIR)/rules.mk

PKG_NAME:=nettle
PKG_VERSION:=3.4.1
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/libs
DL_DIR:=$(TOPDIR)/dl/


PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PACKAGE_DIR:=$(BIN_DIR)/packages/

PKG_INSTALL:=1
PKG_LICENSE:=LGPL-3+

include $(INCLUDE_DIR)/package.mk


PKG_LIBS:=$(PKG_BUILD_DIR)/libnettle.a $(PKG_BUILD_DIR)/libhogweed.a


define Package/$(PKG_NAME)
SECTION:=libs
CATEGORY:=Libraries
TITLE:= nettle library
#DESCRIPTION:=
#DEPENDS:=+librt +libm
endef

CONFIGURE_ARGS+= --enable-mini-gmp --enable-static --disable-shared
#CONFIGURE_ARGS+= --enable-static --disable-shared


#define Build/Compile
#	$(MAKE) -C $(PKG_BUILD_DIR) \
#		CC="$(TARGET_CROSS)gcc" \
#		USRLIBDIR=$(STAGING_DIR)/usr/lib \
#		PLATFORM=$(PLATFORM) \
#		BCM_INSTALL_DIR=$(BCM_BUILD_DIR)/targets/$(PROFILE)/fs.install \
#endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include/nettle
	$(CP) $(PKG_INSTALL_DIR)/usr/include/nettle/*.h $(1)/usr/include/nettle
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/*.a $(1)/usr/lib
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/nettle.pc $(1)/usr/lib/pkgconfig/
endef

#define Package/$(PKG_NAME)/install
#	$(INSTALL_DIR) $(1)/bin
#	$(CP) $(PKG_LIBS) $(1)/bin
#	$(CP) $(PKG_LIBS) $(1)/bin
#endef

$(eval $(call BuildPackage,$(PKG_NAME)))
