include $(TOPDIR)/rules.mk

PKG_NAME:=p0f
PKG_VERSION:=3.08b
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tgz
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/network/utils
DL_DIR:=$(TOPDIR)/dl

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/p0f
 SECTION:=net
 CATEGORY:=Network
 TITLE:=Passive OS Fingerprinting
 DEPENDS:=@ZYXEL_ONECONNECT +libpcap +SSP_SUPPORT:libssp
endef

define Package/p0f/description
	p0f is a versatile passive OS fingerprinting tool.
endef

define Package/p0f/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/p0f $(1)/usr/bin/p0f
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/p0f.fp $(1)/usr/bin/p0f.fp
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/tools/p0f-client $(1)/usr/bin/p0f-client
endef

$(eval $(call BuildPackage,p0f))
