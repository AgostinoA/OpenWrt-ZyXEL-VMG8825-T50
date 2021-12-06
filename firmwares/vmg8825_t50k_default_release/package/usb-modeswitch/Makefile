include $(TOPDIR)/rules.mk

PKG_NAME:=usb-modeswitch
PKG_VERSION:=2.1.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/utils
DL_DIR:=$(TOPDIR)/dl

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/usb-modeswitch
 SECTION:=utils
 CATEGORY:=Utilities
 TITLE:=USB ModeSwitch
 DEPENDS:=+libusb-1.0
endef

define Package/usb-modeswitch/description
	A mode switching tool for controlling "flip flop" (multiple device) USB gear.
endef

define Package/usb-modeswitch/install
	$(INSTALL_DIR) $(1)/bin
	cp -f $(PKG_BUILD_DIR)/usb_modeswitch $(1)/bin
endef

$(eval $(call BuildPackage,usb-modeswitch))
