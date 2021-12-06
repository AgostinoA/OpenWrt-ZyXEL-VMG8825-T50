#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=binutils
PKG_VERSION:=$(call qstrip,$(CONFIG_BINUTILS_VERSION))
BIN_VERSION:=$(PKG_VERSION)

#PKG_SOURCE_URL:=@GNU/binutils/
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/toolchain/binutils

ifeq ($(PKG_VERSION),2.19.1)
  PKG_MD5SUM:=09a8c5821a2dfdbb20665bc0bd680791
endif
ifeq ($(PKG_VERSION),2.19.92)
  PKG_MD5SUM:=85155272f0cca1ae177abea86a9c67d0
endif
ifeq ($(PKG_VERSION),2.20.1)
  PKG_MD5SUM:=9cdfb9d6ec0578c166d3beae5e15c4e5
endif
ifeq ($(PKG_VERSION),2.21)
  PKG_MD5SUM:=c84c5acc9d266f1a7044b51c85a823f5
endif
ifeq ($(PKG_VERSION),2.21.1)
  PKG_MD5SUM:=bde820eac53fa3a8d8696667418557ad
endif
ifeq ($(PKG_VERSION),2.22)
  PKG_MD5SUM:=ee0f10756c84979622b992a4a61ea3f5
endif
ifeq ($(PKG_VERSION),2.23.1)
  PKG_MD5SUM:=33adb18c3048d057ac58d07a3f1adb38
endif
ifeq ($(PKG_VERSION),2.25.1)
  PKG_MD5SUM:=ac493a78de4fee895961d025b7905be4
endif
ifeq ($(PKG_VERSION),2.28.1)
  PKG_MD5SUM:=f400864569446f94468d8ef25a0c1f7a
endif

HOST_BUILD_PARALLEL:=1

PATCH_DIR:=./patches/$(PKG_VERSION)

REAL_STAGING_DIR_HOST:=$(STAGING_DIR_HOST)

include $(INCLUDE_DIR)/toolchain-build.mk

BINUTILS_CONFIGURE:= \
	$(HOST_CONFIGURE_VARS) ./configure \
		--prefix=$(TOOLCHAIN_DIR) \
		--build=$(GNU_HOST_NAME) \
		--host=$(GNU_HOST_NAME) \
		--target=$(REAL_GNU_TARGET_NAME) \
		--with-sysroot=$(TOOLCHAIN_DIR) \
		--disable-werror \
		$(GRAPHITE_CONFIGURE) \
		$(call qstrip,$(CONFIG_EXTRA_BINUTILS_CONFIG_OPTIONS)) 

ifeq ($(CONFIG_BINUTILS_VERSION_2_25_1)$(CONFIG_BINUTILS_VERSION_2_28_1),y)
  BINUTILS_CONFIGURE+= \
		--disable-sim \
		--disable-gdb
ifeq ($(CONFIG_BINUTILS_VERSION_2_25_1),y)
  BINUTILS_CONFIGURE+= \
		--enable-deterministic-archives
endif
ifeq ($(CONFIG_BINUTILS_VERSION_2_28_1),y)
  BINUTILS_CONFIGURE+= \
		--disable-gtk-doc \
		--disable-gtk-doc-html \
		--disable-doc \
		--disable-docs \
		--disable-documentation \
		--disable-debug \
		--with-xmlto=no \
		--with-fop=no \
		--enable-poison-system-directories
endif
ifneq ("_$(call qstrip,$(CONFIG_arm)$(CONFIG_aarch64))_$(CONFIG_TARGET_brcm963xx)_","_y_y_")
  BINUTILS_CONFIGURE+= \
		--enable-plugins \
		--disable-nls
else
  BINUTILS_CONFIGURE+= \
		--enable-plugins \
		--disable-dependency-tracking \
		--disable-option-checking
endif
endif

ifeq ("_$(call qstrip,$(CONFIG_arm)$(CONFIG_aarch64))_$(CONFIG_TARGET_brcm963xx)_","_y_y_")
  BINUTILS_CONFIGURE+= \
		--enable-shared \
		--disable-static \
		--disable-shared \
		--enable-static
else
ifeq ("_$(CONFIG_mips)_$(CONFIG_TARGET_en75xx)_$(CONFIG_UCLIBC_VERSION_0_9_33)_","_y_y_y_")
  BINUTILS_CONFIGURE+= \
		--enable-shared \
		--disable-static \
		--disable-shared \
		--enable-static
else
  BINUTILS_CONFIGURE+= \
		$(if $(CONFIG_BINUTILS_DISABLE_NLS),--disable-nls) \
		$(SOFT_FLOAT_CONFIG_OPTION)
endif
endif

ifeq ($(CONFIG_RTK_SDK_2_1_2_41872_BINUTILS_PATCH),y)
  BINUTILS_CONFIGURE+= \
		--with-pkgversion='Realtek MSDK-4.3.6 Build 104' \
		--enable-multilib \
		--with-dwarf2
else
  BINUTILS_CONFIGURE+= \
		--disable-multilib
endif

ifneq ($(CONFIG_SSP_SUPPORT),)
  BINUTILS_CONFIGURE+= \
		--enable-libssp
else
 ifneq ("_$(call qstrip,$(CONFIG_arm)$(CONFIG_aarch64))_$(CONFIG_TARGET_brcm963xx)_","_y_y_")
 ifneq ("_$(CONFIG_mips)_$(CONFIG_TARGET_en75xx)_$(CONFIG_UCLIBC_VERSION_0_9_33)_","_y_y_y_")
   BINUTILS_CONFIGURE+= \
		--disable-libssp
 endif
 endif
endif

ifneq ($(CONFIG_EXTRA_TARGET_ARCH),)
  BINUTILS_CONFIGURE+= \
		--enable-targets=$(call qstrip,$(CONFIG_EXTRA_TARGET_ARCH_NAME))-linux-$(TARGET_SUFFIX)
endif

define Host/Prepare
	$(call Host/Prepare/Default)
	ln -snf $(notdir $(HOST_BUILD_DIR))  $(BUILD_DIR_TOOLCHAIN)/$(PKG_NAME)
	$(CP) $(SCRIPT_DIR)/config.{guess,sub} $(HOST_BUILD_DIR)/
	$(SED) 's, " Linaro.*,,' $(HOST_BUILD_DIR)/bfd/version.h
endef

define Host/Configure
	(cd $(HOST_BUILD_DIR); \
		$(BINUTILS_CONFIGURE) \
	);
endef

define Host/Compile
	+$(MAKE) $(HOST_JOBS) -C $(HOST_BUILD_DIR) all
endef

define Host/Install
	mkdir -p $(TOOLCHAIN_DIR)/initial
	$(MAKE) -C $(HOST_BUILD_DIR) \
		prefix=$(TOOLCHAIN_DIR)/initial \
		install
	$(MAKE) -C $(HOST_BUILD_DIR) \
		prefix=$(TOOLCHAIN_DIR) \
		install
	$(call FixupLibdir,$(TOOLCHAIN_DIR)/initial)
	$(RM) $(TOOLCHAIN_DIR)/initial/lib/libiberty.a
	$(CP) $(TOOLCHAIN_DIR)/bin/$(REAL_GNU_TARGET_NAME)-readelf $(REAL_STAGING_DIR_HOST)/bin/readelf
	# ARC gcc requires extlib.
	# If extlib is not available in "initial" folder
	# initial gcc will fail to build libc.
	if [ -d $(TOOLCHAIN_DIR)/extlib ]; then \
		$(CP) -r $(TOOLCHAIN_DIR)/extlib $(TOOLCHAIN_DIR)/initial/; \
	fi
endef

define Host/Clean
	rm -rf \
		$(HOST_BUILD_DIR) \
		$(BUILD_DIR_TOOLCHAIN)/$(PKG_NAME)
endef

$(eval $(call HostBuild))
