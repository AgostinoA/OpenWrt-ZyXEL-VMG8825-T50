#
# Copyright (C) 2007-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
FORCE_USE_EXTERNAL_KERNAL_TOOLCHAIN=y
include $(TOPDIR)/rules.mk
PKG_NAME:=external-kernel-toolchain
PKG_RELEASE:=1

PKG_MAINTAINER:=Felix Fietkau <nbd@openwrt.org>

include $(INCLUDE_DIR)/package.mk

LIBC_VERSION:=$(call qstrip,$(CONFIG_KERNEL_TOOLCHAIN_GLIBC_VERSION))
LIBGCC_VERSION:=$(call qstrip,$(CONFIG_KERNEL_TOOLCHAIN_GCC_VERSION))

LIB_SUFFIX:=64

define Package/external-kernel-gcc/Default
  SECTION:=libs
  CATEGORY:=Base system
  URL:=http://gcc.gnu.org/
  VERSION:=$(LIBGCC_VERSION)-$(PKG_RELEASE)
  DEPENDS:=@EXTERNAL_KERNEL_TOOLCHAIN
endef

define Package/external-kernel-libgcc
$(call Package/external-kernel-gcc/Default)
  TITLE:=External kernel gcc support library
endef

define Package/external-kernel-libgcc/config
	menu "Configuration"
		depends on EXTERNAL_KERNEL_TOOLCHAIN && PACKAGE_external-kernel-libgcc

	config EXTERNAL_KERNAL_LIBGCC_FILE_SPEC
		string
		prompt "libgcc shared library files (use wildcards)"
		depends on EXTERNAL_KERNEL_TOOLCHAIN && PACKAGE_external-kernel-libgcc
		default "./lib/libgcc_s.so.*"

	endmenu
endef


define Package/external-kernel-libssp
$(call Package/external-kernel-gcc/Default)
  TITLE:=external-kernel-gcc support library
endef

define Package/external-kernel-libssp/config
	menu "Configuration"
		depends on EXTERNAL_KERNEL_TOOLCHAIN && PACKAGE_external-kernel-libssp

	config EXTERNAL_KERNAL_LIBSSP_FILE_SPEC
		string
		prompt "libssp shared library files (use wildcards)"
		depends on EXTERNAL_KERNEL_TOOLCHAIN && PACKAGE_external-kernel-libssp
		default "./lib/libssp.so.*"

	endmenu
endef


define Package/external-kernel-libstdcpp
$(call Package/external-kernel-gcc/Default)
  NAME:=external-kernel-libstdc++
  TITLE:=GNU Standard C++ Library v3
endef

define Package/external-kernel-libstdcpp/config
	menu "Configuration"
	depends on EXTERNAL_KERNEL_TOOLCHAIN && PACKAGE_external-kernel-libstdcpp

	config EXTERNAL_KERNAL_LIBSTDCPP_FILE_SPEC
		string
		prompt "libstdc++ shared library files (use wildcards)"
		depends on EXTERNAL_KERNEL_TOOLCHAIN && PACKAGE_external-kernel-libstdcpp
		default "./lib/libstdc++.so.*"

	endmenu
endef


define Package/external-kernel-libc/Default
  SECTION:=libs
  CATEGORY:=Base system
  VERSION:=$(LIBC_VERSION)-$(PKG_RELEASE)
  DEPENDS:=+external-kernel-libgcc
  URL:=$(LIBC_URL)
  PKG_FLAGS:=hold essential
endef


define Package/external-kernel-libc
$(call Package/external-kernel-libc/Default)
  TITLE:=External kernel C library
endef

define Package/external-kernel-libc/config
	menu "Configuration"
	depends on EXTERNAL_KERNEL_TOOLCHAIN && PACKAGE_external-kernel-libc

	config EXTERNAL_KERNAL_LIBC_FILE_SPEC
		string
		prompt "external-kernel-libc shared library files (use wildcards)"
		depends on EXTERNAL_KERNEL_TOOLCHAIN && PACKAGE_external-kernel-libc
		default "./lib/lib{anl,c,uClibc,cidn,crypt,dl,m,nsl,nss_dns,nss_files,util}{-*.so,.so.*}"

	endmenu
endef


define Package/external-kernel-libpthread
$(call Package/external-kernel-libc/Default)
  TITLE:=POSIX thread library
endef

define Package/external-kernel-libpthread/config
	menu "Configuration"
	depends on EXTERNAL_KERNEL_TOOLCHAIN && PACKAGE_external-kernel-libpthread

	config EXTERNAL_KERNAL_LIBPTHREAD_FILE_SPEC
		string
		prompt "external-kernel-libpthread shared library files (use wildcards)"
		depends on EXTERNAL_KERNEL_TOOLCHAIN && PACKAGE_external-kernel-libpthread
		default "./lib/libpthread{-*.so,.so.*}"

	endmenu
endef


define Package/external-kernel-libthread-db
$(call Package/external-kernel-libc/Default)
  TITLE:=POSIX thread library debugging support
endef

define Package/external-kernel-librt
$(call Package/external-kernel-libc/Default)
  TITLE:=POSIX.1b RealTime extension library
  DEPENDS:=+external-kernel-libpthread +external-kernel-libc
endef

define Package/external-kernel-librt/config
	menu "Configuration"
	depends on EXTERNAL_KERNEL_TOOLCHAIN && PACKAGE_external-kernel-librt

	config EXTERNAL_KERNAL_LIBRT_FILE_SPEC
		string
		prompt "external-kernel-librt shared library files (use wildcards)"
		depends on EXTERNAL_KERNEL_TOOLCHAIN && PACKAGE_external-kernel-librt
		default "./lib/librt{-*.so,.so.*}"

	endmenu
endef

define Package/external-kernel-libresolv
$(call Package/external-kernel-libc/Default)
  TITLE:=resolver library
endef

define Package/external-kernel-libresolv/config
	menu "Configuration"
	depends on EXTERNAL_KERNEL_TOOLCHAIN && PACKAGE_external-kernel-libresolv

	config EXTERNAL_KERNAL_LIBRESOLV_FILE_SPEC
		string
		prompt "external-kernel-libresolv shared library files (use wildcards)"
		depends on EXTERNAL_KERNEL_TOOLCHAIN && PACKAGE_external-kernel-libresolv
		default "./lib/libresolv{-*.so,.so.*}"

	endmenu
endef

define Package/external-kernel-ldd
$(call Package/external-kernel-libc/Default)
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=LDD trace utility
endef

define Package/external-kernel-ldd/config
	menu "Configuration"
		depends on EXTERNAL_KERNEL_TOOLCHAIN && PACKAGE_external-kernel-ldd

	config EXTERNAL_KERNAL_LDD_FILE_SPEC
		string
		prompt "ldd trace utility file"
		depends on EXTERNAL_KERNEL_TOOLCHAIN && PACKAGE_external-kernel-ldd
		default "./usr/bin/ldd"

	endmenu
endef


define Package/external-kernel-ldconfig
$(call Package/external-kernel-libc/Default)
  DEPENDS:=@EXTERNAL_KERNEL_TOOLCHAIN
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Shared library path configuration
endef

define Package/external-kernel-ldconfig/config
	menu "Configuration"
		depends on EXTERNAL_KERNEL_TOOLCHAIN && PACKAGE_external-kernel-ldconfig

	config EXTERNAL_KERNAL_LDCONFIG_FILE_SPEC
		string
		prompt "ldconfig file"
		depends on EXTERNAL_KERNEL_TOOLCHAIN && PACKAGE_external-kernel-ldconfig
		default "./sbin/ldconfig"

	endmenu
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

LIBGCC_A=$(wildcard $(KERNEL_TOOLCHAIN_DIR)/lib/gcc/*/*/libgcc_pic.a)
LIBGCC_MAP=$(wildcard $(KERNEL_TOOLCHAIN_DIR)/lib/gcc/*/*/libgcc.map)
LIBGCC_SO=$(wildcard $(KERNEL_TOOLCHAIN_DIR)/lib/libgcc_s.so.*)

define Build/Compile/Default
	$(CP) $(LIBGCC_SO) $(PKG_BUILD_DIR)/
endef
Build/Compile = $(Build/Compile/Default)


define Package/external-kernel-libgcc/install
	for file in $(call qstrip,$(CONFIG_EXTERNAL_KERNAL_LIBGCC_FILE_SPEC)); do \
		$(INSTALL_DIR) $(1)/lib$(LIB_SUFFIX) ; \
		$(CP) $(call qstrip,$(KERNEL_TOOLCHAIN_DIR))/$$$$file $(1)/lib$(LIB_SUFFIX)/ ; \
	done ; \
	exit 0
endef

define Package/external-kernel-libssp/install
	for file in $(call qstrip,$(CONFIG_EXTERNAL_KERNAL_LIBSSP_FILE_SPEC)); do \
		dir=`dirname $$$$file` ; \
		$(INSTALL_DIR) $(1)/lib$(LIB_SUFFIX) ; \
		$(CP) $(call qstrip,$(KERNEL_TOOLCHAIN_DIR))/$$$$file $(1)/lib$(LIB_SUFFIX)/ ; \
	done ; \
	exit 0
endef

define Package/external-kernel-libstdcpp/install
	for file in $(call qstrip,$(CONFIG_EXTERNAL_KERNAL_LIBSTDCPP_FILE_SPEC)); do \
		$(INSTALL_DIR) $(1)/lib$(LIB_SUFFIX) ; \
		$(CP) $(call qstrip,$(KERNEL_TOOLCHAIN_DIR))/$$$$file $(1)/lib$(LIB_SUFFIX)/ ; \
	done ; \
	exit 0
endef

define Package/external-kernel-libc/install
	$(INSTALL_DIR) $(1)/lib
	cp $(call qstrip,$(KERNEL_TOOLCHAIN_DIR))/lib/ld-linux*.so.* $(1)/lib/

	for file in $(call qstrip,$(CONFIG_EXTERNAL_KERNAL_LIBC_FILE_SPEC)); do \
		$(INSTALL_DIR) $(1)/lib$(LIB_SUFFIX) ; \
		$(CP) $(call qstrip,$(KERNEL_TOOLCHAIN_DIR))/$$$$file $(1)/lib$(LIB_SUFFIX)/ ; \
	done ; \
	exit 0
endef

define Package/external-kernel-libpthread/install
	for file in $(call qstrip,$(CONFIG_EXTERNAL_KERNAL_LIBPTHREAD_FILE_SPEC)); do \
		$(INSTALL_DIR) $(1)/lib$(LIB_SUFFIX) ; \
		$(CP) $(call qstrip,$(KERNEL_TOOLCHAIN_DIR))/$$$$file $(1)/lib$(LIB_SUFFIX)/ ; \
	done ; \
	exit 0
endef

define Package/external-kernel-librt/install
	for file in $(call qstrip,$(CONFIG_EXTERNAL_KERNAL_LIBRT_FILE_SPEC)); do \
		$(INSTALL_DIR) $(1)/lib$(LIB_SUFFIX) ; \
		$(CP) $(call qstrip,$(KERNEL_TOOLCHAIN_DIR))/$$$$file $(1)/lib$(LIB_SUFFIX)/ ; \
	done ; \
	exit 0
endef

define Package/external-kernel-libresolv/install
	for file in $(call qstrip,$(CONFIG_EXTERNAL_KERNAL_LIBRESOLV_FILE_SPEC)); do \
		$(INSTALL_DIR) $(1)/lib$(LIB_SUFFIX) ; \
		$(CP) $(call qstrip,$(KERNEL_TOOLCHAIN_DIR))/$$$$file $(1)/lib$(LIB_SUFFIX)/ ; \
	done ; \
	exit 0
endef

define Package/external-kernel-ldd/install
	for file in $(call qstrip,$(CONFIG_EXTERNAL_KERNAL_LDD_FILE_SPEC)); do \
		$(INSTALL_DIR) $(1)/lib$(LIB_SUFFIX) ; \
		$(CP) $(call qstrip,$(KERNEL_TOOLCHAIN_DIR))/$$$$file $(1)/lib$(LIB_SUFFIX)/ ; \
	done ; \
	exit 0
endef

define Package/external-kernel-ldconfig/install
	for file in $(call qstrip,$(CONFIG_EXTERNAL_KERNAL_LDCONFIG_FILE_SPEC)); do \
		$(INSTALL_DIR) $(1)/lib$(LIB_SUFFIX) ; \
		$(CP) $(call qstrip,$(KERNEL_TOOLCHAIN_DIR))/$$$$file $(1)/lib$(LIB_SUFFIX)/ ; \
	done ; \
	exit 0
endef

$(eval $(call BuildPackage,external-kernel-libc))
$(eval $(call BuildPackage,external-kernel-libgcc))
$(eval $(call BuildPackage,external-kernel-libssp))
$(eval $(call BuildPackage,external-kernel-libstdcpp))
$(eval $(call BuildPackage,external-kernel-libpthread))
$(eval $(call BuildPackage,external-kernel-libthread-db))
$(eval $(call BuildPackage,external-kernel-librt))
$(eval $(call BuildPackage,external-kernel-libresolv))
$(eval $(call BuildPackage,external-kernel-ldd))
$(eval $(call BuildPackage,external-kernel-ldconfig))
