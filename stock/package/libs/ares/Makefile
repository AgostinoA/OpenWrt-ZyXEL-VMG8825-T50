include $(TOPDIR)/rules.mk

PKG_NAME:=ares
PKG_RELEASE:=1
PKG_VERSION:=1.1.1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/libs
DL_DIR:=$(TOPDIR)/dl

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PATCH_DIR:=patches-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk


define Package/ares
 SECTION:=libs
 CATEGORY:=Libraries
 TITLE:= dnssrv library
 URL:=
 DEPENDS:=
endef


### Michael.20150318.002: Modify to change the Voice/VoIP-related OpenWRT-based Common Reference Resources (Header file + Library) Install Path/Directory.
#define Build/InstallDev
#	$(CP) $(PKG_BUILD_DIR)/ares.h $(STAGING_DIR)/usr/include
#	$(CP) $(PKG_BUILD_DIR)/ares_dns.h $(STAGING_DIR)/usr/include
#	$(CP) $(PKG_BUILD_DIR)/zylist.h $(STAGING_DIR)/usr/include
#	$(CP) $(PKG_BUILD_DIR)/ares_private.h $(STAGING_DIR)/usr/include
#endef
define Build/InstallDev
	$(INSTALL_DIR) $(STAGING_DIR)/usr/include/voice/ares
	$(CP) $(PKG_BUILD_DIR)/ares.h  $(STAGING_DIR)/usr/include/voice/ares/
	$(CP) $(PKG_BUILD_DIR)/ares_dns.h  $(STAGING_DIR)/usr/include/voice/ares/
	$(CP) $(PKG_BUILD_DIR)/zylist.h  $(STAGING_DIR)/usr/include/voice/ares/
	$(CP) $(PKG_BUILD_DIR)/ares_private.h  $(STAGING_DIR)/usr/include/voice/ares/
endef


### Michael.20150318.002: Modify to change the Voice/VoIP-related OpenWRT-based Common Reference Resources (Header file + Library) Install Path/Directory.
#define Package/ares/install
#	$(INSTALL_DIR) $(1)/usr/lib/
#	$(CP)  $(PKG_BUILD_DIR)/libares.a $(STAGING_DIR)/usr/lib
#endef
define Package/ares/install
	$(INSTALL_DIR) $(1)/usr/lib/

	$(INSTALL_DIR) $(STAGING_DIR)/usr/lib/voice
	$(CP)  $(PKG_BUILD_DIR)/libares.a  $(STAGING_DIR)/usr/lib/voice/
endef


$(eval $(call BuildPackage,ares))
