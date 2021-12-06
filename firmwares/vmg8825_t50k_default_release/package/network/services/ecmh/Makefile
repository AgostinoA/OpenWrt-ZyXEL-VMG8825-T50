include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=ecmh
PKG_VERSION:=2005.02.09

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/network/services
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
PKG_LICENSE:=GPL-2.0+

define Package/ecmh
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Routing and Redirection
  TITLE:=IPV6 Multicast Routing Daemon
  DEPENDS:=+ip +librt
  DEPENDS+=+@IPV6
endef

define Package/ecmh/description
	Easy Cast du Multi Hub (ecmh) is a networking daemon 
	that acts as a full IPv6 MLDv1 and MLDv2 Multicast "Router".
endef

PACKAGE_CFLAGS += -DTRENDCHIP -I$(LINUX_DIR)/include
MAKE_FLAGS += LINUX_DIR=$(LINUX_DIR)
MAKE_FLAGS += ZCFG_PLATFORM=ECONET
ifeq ("$(strip ${ZCFG_PLATFORM})","ECONET")
ifeq ("$(strip $(CONFIG_$(subst $\",,$(CONFIG_CUSTOM_SDK_PREFIX))_TCSUPPORT_3_18_21_KERNEL))","y")
MAKE_FLAGS += TCSUPPORT_3_18_21_KERNEL=y
endif
endif

define Package/ecmh/install
	$(INSTALL_DIR) $(1)/userfs/bin
	$(CP) $(PKG_BUILD_DIR)/src/ecmh $(1)/userfs/bin
endef

$(eval $(call BuildPackage,ecmh))
