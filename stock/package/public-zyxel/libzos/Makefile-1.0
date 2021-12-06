#
#   OpenWRT makefile
#
#   This is free software, licensed under the GNU General Public License v2.
#   See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

#
#   package information
#
PKG_NAME      := libzos
PKG_VERSION   := 1.0
PKG_RELEASE   := 1

PKG_NAME_VER  := $(PKG_NAME)-$(PKG_VERSION)
PKG_SRC_DIR   := $(ZYXEL_PUBLIC_PACKAGE)/$(PKG_NAME)/$(PKG_NAME_VER)
PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME_VER)

#
#   Must be after package information
#   Otherwise, the above variables will be incorrect
#
include $(INCLUDE_DIR)/package.mk

#
#   Package information
#
define Package/$(PKG_NAME)
	SECTION     := net
	CATEGORY    := Zyxel public package
	TITLE       := OS porting layer
	DEPENDS     := +libzlog
endef

#
#   Clear the build dir
#
define Build/Clean
	rm -rf $(PKG_BUILD_DIR)
endef

#
#   Prepare the package
#   1. create the same dir including sub-dir under build dir
#   2. link files to the same dir and sub-dir
#
define Build/Prepare
	rm -rf $(PKG_BUILD_DIR)
	$$(call link_files,$(PKG_NAME_VER),$(BUILD_DIR))
endef

#
#   Compile the build dir
#
define Package/$(PKG_NAME)/compile
	$(MAKE) -C $(PKG_BUILD_DIR)
endef

#
#   Install the package to be accessed by other later-compiled packages
#   1. copy header files to staging dir
#   2. copy library to staging dir
#
define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/*.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/$(PKG_NAME).so $(1)/usr/lib/
endef

#
#   Disable Dependencies Check
#
define CheckDependencies
endef

#
#   Install the package to linux file system
#
define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(PKG_NAME).so $(1)/lib
#	$(INSTALL_DIR) $(1)/lib/public
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(PKG_NAME).so $(1)/lib/public
#	ln -s /lib/public/$(PKG_NAME).so $(1)/lib/$(PKG_NAME).so
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
