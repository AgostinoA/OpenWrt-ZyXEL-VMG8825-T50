#
# Copyright (C) 2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=u-boot
PKG_VERSION:=2009.11
PKG_MD5SUM:=d94700614225f53c853dfe714eb5fa47
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(KERNEL_BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/loader
PKG_TARGETS:=bin

include $(INCLUDE_DIR)/package.mk

define Package/uboot-zyxel
  SECTION:=boot
  CATEGORY:=Boot Loaders
  TITLE:=U-Boot for ZyXEL reference boards
  DEPENDS:=
  URL:=http://www.denx.de/wiki/U-Boot
  MENU:=1
endef

define old_prepare
	$(call Build/Prepare/Default)
	$(CP) ./files/* $(PKG_BUILD_DIR)
	find $(PKG_BUILD_DIR) -name .svn | $(XARGS) rm -rf
endef

define Build/Prepare
	$(PKG_UNPACK)
	cp -r $(CP_OPTS) $(FILES_DIR)/* $(PKG_BUILD_DIR)/
	$(Build/Patch)
	find $(PKG_BUILD_DIR) -name .svn | $(XARGS) rm -rf
endef

UBOOT_ZYXEL_TARGET:=$(call qstrip,$(CONFIG_UBOOT_ZYXEL_TARGET))
UBOOT_MAX_SIZE:=$(if $(CONFIG_UBOOT_ZYXEL_ZLOADER_OFFSET),$(CONFIG_UBOOT_ZYXEL_ZLOADER_OFFSET),131072)

ifneq ($(CONFIG_EMBEDDED_KERNEL_IN_ROOTFS),)
        EMBEDDED_KERNEL_IN_ROOTFS:="CONFIG_EMBEDDED_KERNEL_IN_ROOTFS=y"
endif

ifneq ($(CONFIG_UBOOT_ZYXEL_SUPPORT_ZLOADER),)
	SUPPORT_ZLOADER:="CONFIG_UBOOT_SUPPORT_ZLOADER=y"
endif

ifneq ($(CONFIG_UBOOT_ZYXEL_SUPPORT_ROMD),)
	SUPPORT_ROM_D:="CONFIG_UBOOT_SUPPORT_ROMD=y"
endif

UBOOT_MAKE_OPTS:= \
	CROSS_COMPILE=$(TARGET_CROSS) \
	$(EMBEDDED_KERNEL_IN_ROOTFS) \
	$(SUPPORT_ZLOADER) \
	$(SUPPORT_ROM_D)

define Package/uboot-zyxel/config
	source "$(SOURCE)/Config.in"
endef

define Build/Configure/Target
	$(MAKE) -C $(PKG_BUILD_DIR) \
		$(UBOOT_MAKE_OPTS) \
		O=$(PKG_BUILD_DIR)/$(1) \
		$(1)_config
endef

define Build/Configure
	$(call Build/Configure/Target,$(UBOOT_ZYXEL_TARGET))
ifeq ($(CONFIG_UBOOT_ZYXEL_RAMBOOT),y)
	$(call Build/Configure/Target,$(UBOOT_ZYXEL_TARGET)_ramboot)
endif
endef

# Get load address from image of u-boot
define getLoadAddress
0x`readelf -a $(1)/u-boot|grep "\[ 1\]"|tr -s ' '|cut -d' ' -f6`
endef
# Get entry point from image of u-boot
define getEntryPoint
`readelf -a $(1)/u-boot|grep "Entry point address"|cut -d":" -f2`
endef 

# Usage: mkUbootuImage(path,input_img,img_name)
define mkUbootuImage
        $(STAGING_DIR_HOST)/bin/mkimage -A $(LINUX_KARCH) -T standalone -C none \
        -a $(call getLoadAddress,$(1)) \
        -e $(call getEntryPoint,$(1)) \
        -n $(3) \
        -d $(1)/$(2) \
        $(1)/$(2).uImage
endef


define Build/Compile/Target
	$(MAKE) -C $(PKG_BUILD_DIR) \
		$(UBOOT_MAKE_OPTS) \
		O=$(PKG_BUILD_DIR)/$(1) \
		all
endef

define Build/Compile
	$(call Build/Compile/Target,$(UBOOT_ZYXEL_TARGET))
ifeq ($(CONFIG_UBOOT_ZYXEL_RAMBOOT),y)
	$(call Build/Compile/Target,$(UBOOT_ZYXEL_TARGET)_ramboot)
endif
endef

define CreateTargetImage
	mkdir -p $(1)/$(2)
	$(CP) $(PKG_BUILD_DIR)/$(2)/u-boot.bin $(1)/$(2)/
	$(SCRIPT_DIR)/imgAlignment.sh $(1)/$(2)/u-boot.bin $(UBOOT_MAX_SIZE)
endef

ifneq ($(CONFIG_UBOOT_ZYXEL_SUPPORT_ZLOADER),)
define Build/InstallDev
# share standlone library for ZyBoot
	$(INSTALL_DIR) $(1)/usr/include/uboot-zyxel
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/$(CONFIG_UBOOT_ZYXEL_TARGET)/examples/standalone/libstubs.a $(1)/usr/lib
	$(CP) -L $(PKG_BUILD_DIR)/include/* $(1)/usr/include/uboot-zyxel/
	$(CP) -L $(PKG_BUILD_DIR)/$(CONFIG_UBOOT_ZYXEL_TARGET)/include/* $(1)/usr/include/uboot-zyxel/
	$(CP) -L $(PKG_BUILD_DIR)/$(CONFIG_UBOOT_ZYXEL_TARGET)/include2/* $(1)/usr/include/uboot-zyxel/
endef
endif

define Package/uboot-zyxel/install
	$(call CreateTargetImage,$(1),$(UBOOT_ZYXEL_TARGET))
	$(CP) $(PKG_BUILD_DIR)/$(UBOOT_ZYXEL_TARGET)/u-boot $(1)/$(UBOOT_ZYXEL_TARGET)/
	$(CP) $(PKG_BUILD_DIR)/$(UBOOT_ZYXEL_TARGET)/u-boot.map $(1)/$(UBOOT_ZYXEL_TARGET)/
ifeq ($(CONFIG_UBOOT_ZYXEL_RAMBOOT),y)
	$(call CreateTargetImage,$(1),$(UBOOT_ZYXEL_TARGET)_ramboot)
	$(CP) $(PKG_BUILD_DIR)/$(UBOOT_ZYXEL_TARGET)_ramboot/u-boot $(1)/$(UBOOT_ZYXEL_TARGET)_ramboot/
	$(CP) $(PKG_BUILD_DIR)/$(UBOOT_ZYXEL_TARGET)_ramboot/u-boot.map $(1)/$(UBOOT_ZYXEL_TARGET)_ramboot/
	$(call mkUbootuImage,$(1)/$(UBOOT_ZYXEL_TARGET)_ramboot,u-boot.bin,uboot-ram)
endif
ifneq ($(CONFIG_UBOOT_ZYXEL_SUPPORT_ZLOADER),)
	@( \
		if [ `stat -c %s $(1)/$(UBOOT_ZYXEL_TARGET)/u-boot.bin` -ne $(UBOOT_MAX_SIZE) ]; then \
			echo "The size of uboot must be equal to $(UBOOT_MAX_SIZE) if you want to support zloader!"; \
			echo "Current size is `stat -c %s $(PKG_BUILD_DIR)/$(UBOOT_ZYXEL_TARGET)/u-boot.bin`"; \
			exit 1; \
		fi;\
	)	
endif
endef

$(eval $(call BuildPackage,uboot-zyxel))

