# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

#These lines concatanate the package name and list the URL location from which the package source code is to be downloaded
PKG_NAME:=libzyutil
PKG_VERSION:=1.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
#PKG_SOURCE_URL:=http://www.cs.uh.edu/~vivekian/downloads/
PKG_SOURCE_URL:=@ZyXEL_SITE/public/ZyXEL
DL_DIR:=$(TOPDIR)/dl/public/zyxel

PKG_CAT:=zcat

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PRODUCT_NAME:=$(call qstrip, $(CONFIG_MRD_PRODUCT_NAME))

include $(INCLUDE_DIR)/package.mk

#These lines describe what your package does and its place in the menu config

export CONFIG_ELISA_CUSTOMIZATION PRODUCT_NAME CONFIG_ZYXEL_RMA_FW_SUPPORT
export CONFIG_ZYXEL_IPV6_UPLOAD_DIAG_ENABLE
export CONFIG_WIND_ITALY_CUSTOMIZATION
export CONFIG_EN7516SDK_ZYXEL_DETECT_PRODUCT_TYPE

PKG_BUILD_DEPENDS:=zcfg libjson libopenssl libzlog libzos libzcfg_msg

define Package/libzyutil
SECTION:=net
CATEGORY:=Zyxel Packages
TITLE:= ZyXEL Configuration Management Utility Library
DESCRIPTION:=
#DEPENDS:=zcfg +libjson
endef

#Disable Dependencies Check
define CheckDependencies
endef

ifneq ("$(CONFIG_BRCM_SDK_VERSION)","")
EXTRA_CFLAGS += -DBCM_SDK_$(CONFIG_BRCM_SDK_VERSION)
endif

ifeq ($(CONFIG_BRCM_SDK_VERSION), "414L04")
EXTRA_CFLAGS += -DNEW_MTD_DRIVER
endif

ifeq ($(CONFIG_BRCM_SDK_VERSION), "416L01RC1")
EXTRA_CFLAGS += -DNEW_MTD_DRIVER
endif

ifeq ($(CONFIG_BRCM_SDK_VERSION), "416L01")
EXTRA_CFLAGS += -DNEW_MTD_DRIVER
endif

ifeq ($(CONFIG_BRCM_SDK_VERSION), "416L02")
EXTRA_CFLAGS += -DNEW_MTD_DRIVER
endif

ifeq ($(CONFIG_BRCM_SDK_VERSION), "416L02A")
EXTRA_CFLAGS += -DNEW_MTD_DRIVER
endif

ifeq ($(CONFIG_BRCM_SDK_VERSION), "416L04")
EXTRA_CFLAGS += -DNEW_MTD_DRIVER
endif

ifeq ($(CONFIG_BRCM_SDK_VERSION), "416L05")
EXTRA_CFLAGS += -DNEW_MTD_DRIVER
endif

ifeq ($(CONFIG_BRCM_SDK_VERSION), "502L04")
EXTRA_CFLAGS += -DNEW_MTD_DRIVER
endif

ifeq ($(CONFIG_BRCM_SDK_VERSION), "502L05")
EXTRA_CFLAGS += -DNEW_MTD_DRIVER
endif

ifeq ($(CONFIG_BRCM_SDK_VERSION), "502L06")
EXTRA_CFLAGS += -DNEW_MTD_DRIVER
endif

ifneq ($(strip $(TCSUPPORT_BOOTROM_LARGE_SIZE)),)
EXTRA_CFLAGS += -DBOOTROM_LARGE_SIZE
endif

ifeq ($(CONFIG_ABOG_CUSTOMIZATION),y)
EXTRA_CFLAGS += -DABOG_CUSTOMIZATION
endif


ifeq ("$(CONFIG_EXTERNAL_KERNEL_TOOLCHAIN)","")
EXTRA_CFLAGS += -I$(LINUX_DIR)/user_headers/include
else
EXTRA_CFLAGS += -I$(TOOLCHAIN_DIR)/include
endif

# Zyxel Feature Bits
ifeq ($(CONFIG_ZYXEL_FEATURE_BITS),y)
EXTRA_CFLAGS += -DZYXEL_FEATURE_BITS
EXTRA_CFLAGS += -I$(LINUX_DIR)/include/uapi
endif

ifeq ("$(strip ${ZCFG_PLATFORM})","ECONET")
ifneq ($($(shell echo CONFIG_$(CONFIG_CUSTOM_SDK_PREFIX)_ZYXEL_LAN_WAN_WLAN_SHARE_THE_SAME_MAC)),)
EXTRA_CFLAGS += -DZYXEL_LAN_WAN_WLAN_SHARE_THE_SAME_MAC
endif
ifeq ($(CONFIG_TC_SDK_7_3_245_300),y)
EXTRA_CFLAGS += -DNEW_MTD_DRIVER
endif
endif

ifeq ($(CONFIG_ZCFG_LOG_USE_DEBUGCFG),y)
EXTRA_CFLAGS += -DZCFG_LOG_USE_DEBUGCFG
endif

ifeq ($(CONFIG_SAME_FW_FOR_TWO_BOARD),y)
EXTRA_CFLAGS += -DSAME_FW_FOR_TWO_BOARD
endif

ifeq ($(CONFIG_TARGET_ROOTFS_UBIFS),y)
EXTRA_CFLAGS += -DTARGET_ROOTFS_UBIFS
endif

ifeq ($(CONFIG_ZYXEL_AT_SET_KEY),y)
EXTRA_CFLAGS += -DZYXEL_AT_SET_KEY
endif

ifeq ($(CONFIG_ZYXEL_BOARD_DETECT_BY_GPIO),y)
EXTRA_CFLAGS += -DZYXEL_BOARD_DETECT_BY_GPIO
endif

#Sunrise
export CONFIG_SUNRISE_RELEASE_DHCP_PPP_BEFORE_IFDOWN

export CONFIG_ZYXEL_HASH_ACCOUNT_PASSWORD_BY_SHA512

ifeq ($(ZCFG_PLATFORM),BROADCOM)
define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		BUILD_DIR=$(BCM_BUILD_DIR) \
		EXTRA_CFLAGS="$(EXTRA_CFLAGS)"
endef
else ifeq ($(ZCFG_PLATFORM),ECONET)
define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		$(TARGET_CONFIGURE_OPTS) \
		CROSS_COMPILE=$(TARGET_CROSS) \
		EXTRA_CFLAGS="$(EXTRA_CFLAGS)" \
		STAGING_DIR_HOST=$(STAGING_DIR_HOST)
endef
else ifeq ("$(ZCFG_PLATFORM)","QUALCOMM")
define Build/Compile
	$(call Build/Compile/Default, EXTRA_CFLAGS="-DNEW_MTD_DRIVER")
endef
endif


define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/*.h $(1)/usr/include/
	$(CP) $(PKG_BUILD_DIR)/libzyutil_encrypt/*.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/libzyutil.so $(1)/usr/lib/
endef

define Package/libzyutil/install
	$(INSTALL_DIR) $(1)/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(PKG_NAME).so $(1)/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libdebug.a $(STAGING_DIR)/usr/lib
#	$(INSTALL_DIR) $(1)/lib/public
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libzyutil.so $(1)/lib/public
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libdebug.a $(STAGING_DIR)/usr/lib
#	ln -s /lib/public/libzyutil.so $(1)/lib/libzyutil.so
endef

$(eval $(call BuildPackage,libzyutil))
