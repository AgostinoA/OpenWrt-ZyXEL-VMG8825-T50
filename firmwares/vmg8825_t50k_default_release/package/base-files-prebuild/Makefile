
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/zyxel-private.mk

PKG_NAME:=base-files-prebuild
PKG_VERSION:=0.2

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)
PKG_BUILD_DEPENDS:=opkg/host

PREBUILD_BASE_DIR=./files
# for store bootloader`s images
PREBUILD_BOOTLOADER_DIR=$(PREBUILD_BASE_DIR)/bootloader
# for store host tools/files
PREBUILD_STAGING_DIR_HOST=$(PREBUILD_BASE_DIR)/staging_dir/host
# for store the target files which packed as ipk format. (will be install to rootfs)
PREBUILD_IPK_DIR=$(PREBUILD_BASE_DIR)/ipk_files
# for store the target files (will be install to rootfs)
PREBUILD_TARGET_FILES_DIR=$(PREBUILD_BASE_DIR)/rootfs

# for store included header files in compile time in staging_dir
PREBUILD_STAGING_DIR=$(PREBUILD_BASE_DIR)/staging_dir/target-$(ARCH)$(ARCH_SUFFIX)$(DIR_SUFFIX)$(if $(BUILD_SUFFIX),_$(BUILD_SUFFIX))
PREBUILD_STAGING_DIR_USR=$(PREBUILD_STAGING_DIR)/usr
PREBUILD_STAGING_DIR_USR_INC=$(PREBUILD_STAGING_DIR_USR)/include

define Package/base-files-prebuild
SECTION:=release
CATEGORY:=Zyxel Packages
TITLE:=This is a release package
endef

#Disable Dependencies Check
define CheckDependencies
endef

ifeq ($(CONFIG_TARGET_en75xx),y)
TARGET_BOOTLOADER_DIR=en75xx-loader
else
TARGET_BOOTLOADER_DIR=brcm-cfe
endif

define restore_prebuild_bootloader
	mkdir -p $(BIN_DIR)/$(TARGET_BOOTLOADER_DIR)
	$(CP) $(PREBUILD_BOOTLOADER_DIR)/* $(BIN_DIR)/$(TARGET_BOOTLOADER_DIR)/
endef


ifneq ($(wildcard $(PREBUILD_BOOTLOADER_DIR)),)
__need_restore_prebuild_bootloader=$(call restore_prebuild_bootloader)
endif

define restore_prebuild_host_tools
	$(INSTALL_DIR) $(STAGING_DIR_HOST)
	$(CP) $(PREBUILD_STAGING_DIR_HOST)/* $(STAGING_DIR_HOST)/
endef

define restore_prebuild_staging_usr_include
	$(INSTALL_DIR) $(STAGING_DIR)/usr/include
	$(CP) $(PREBUILD_STAGING_DIR_USR_INC)/* $(STAGING_DIR)/usr/include/
endef

ifneq ($(wildcard $(PREBUILD_STAGING_DIR_HOST)),)
__need_restore_prebuild_host_tools=$(call restore_prebuild_host_tools)
endif

ifneq ($(wildcard $(PREBUILD_STAGING_DIR_USR_INC)),)
__need_restore_prebuild_staging_usr_include=$(call restore_prebuild_staging_usr_include)
endif

define restore_prebuild_ipk_preapre
	mkdir -p $(PKG_BUILD_DIR)/rootfs
	mkdir -p $(PKG_BUILD_DIR)/tmp
	cd "$(PREBUILD_IPK_DIR)"; \
	for i in $$$$( ls ) ; do \
		tar -xf $$$$i -C $(PKG_BUILD_DIR)/tmp; \
		tar -zxf $(PKG_BUILD_DIR)/tmp/data.tar.gz -C $(PKG_BUILD_DIR)/rootfs; \
	done; cd -
	rm -fr $(PKG_BUILD_DIR)/tmp
endef

ifneq ($(wildcard $(PREBUILD_IPK_DIR)),)
__need_restore_prebuild_ipk_preapre=$(call restore_prebuild_ipk_preapre)
endif


define Build/Prepare
	$(__need_restore_prebuild_host_tools)
	$(__need_restore_prebuild_staging_usr_include)
	$(__need_restore_prebuild_ipk_preapre)
endef

define Build/Compile
endef
	
define Package/base-files-prebuild/install
	$(__need_restore_prebuild_bootloader)
	$(INSTALL_DIR) $(1)/
	if [ -d "$(PKG_BUILD_DIR)/rootfs" ]; then \
		$(CP) $(PKG_BUILD_DIR)/rootfs/* $(1)/; \
	fi
	if [ -d "$(PREBUILD_TARGET_FILES_DIR)" ]; then \
		$(CP) $(PREBUILD_TARGET_FILES_DIR)/* $(1)/; \
	fi
endef

$(eval $(call BuildPackage,base-files-prebuild))
