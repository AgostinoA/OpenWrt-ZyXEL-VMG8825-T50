#
# Copyright (C) 2006-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=external_kernel_toolchain

EXTERNAL_TOOLCHAIN_SOURCE:=OpenWrt-Toolchain-$(call qstrip,$(CONFIG_KERNEL_TOOLCHAIN_TARGET))-for-$(call qstrip,$(CONFIG_KERNEL_TOOLCHAIN_CPU_ARCH))-gcc-$(call qstrip,$(CONFIG_KERNEL_TOOLCHAIN_GCC_VERSION))_glibc-$(call qstrip,$(CONFIG_KERNEL_TOOLCHAIN_GLIBC_VERSION)).tar.bz2
PKG_SOURCE:=$(EXTERNAL_TOOLCHAIN_SOURCE)
#PKG_MD5SUM:=016cf2c5ed06adf7c601e3301a14e370
#PKG_SOURCE_URL:=http://launchpad.net/gdb-linaro/$(PKG_VERSION_MAJOR)/$(PKG_REV)/+download/
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/toolchain/prebuild_toolchain

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/toolchain-build.mk

define Host/Prepare
	echo $(TOPDIR)/staging_dir/$(PKG_NAME)
	if [ ! -d $(TOPDIR)/staging_dir/$(PKG_NAME) ]; then \
		mkdir -p $(TOPDIR)/staging_dir/$(PKG_NAME); \
	fi
	if [ ! -f $(DL_DIR)/$(EXTERNAL_TOOLCHAIN_SOURCE) ]; then \
		$(SCRIPT_DIR)/download.pl "$(DL_DIR)" "$(EXTERNAL_TOOLCHAIN_SOURCE)" "" "$(PKG_SOURCE_URL)"; \
	fi
	/bin/tar -jxf $(DL_DIR)/$(EXTERNAL_TOOLCHAIN_SOURCE) -C $(TOPDIR)/staging_dir/$(PKG_NAME)/ --strip-components=1
endef

define Host/Compile
endef

define Host/Install
endef

define Host/Clean
	$(RM) -rf $(TOPDIR)/staging_dir/$(PKG_NAME)
endef

$(eval $(call HostBuild))