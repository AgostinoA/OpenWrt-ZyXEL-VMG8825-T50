#
# Copyright (C) 2006-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk


#MD5SUM_2.19 = 42dad4edd3bcb38006d13b5640b00b38
#REVISION_2.19 = 25243
#
#MD5SUM_2.21 = 76050a65c444d58b5c4aa0d6034736ed
#REVISION_2.21 = 16d0a0c
#
#MD5SUM_2.22 = b575850e77b37d70f96472285290b391
MD5SUM_2.22 = 3168120497c81b663a76c952f7722da2
#REVISION_2.22 = b995d95
#
MD5SUM_2.24 = 3177c254b15eee0d0a81bfe480ea7e80
#REVISION_2.24 = fdfc926
#
MD5SUM_2.26 = c3488005598dac84c5a56cb7af6b3dbc
#REVISION_2.26 =

PKG_NAME:=glibc
PKG_VERSION:=$(call qstrip,$(CONFIG_GLIBC_VERSION))

#PKG_REVISION:=$(REVISION_$(PKG_VERSION))
#PKG_MIRROR_MD5SUM:=$(MD5SUM_$(PKG_VERSION))
PKG_MD5SUM=$(MD5SUM_$(PKG_VERSION))

#PKG_SOURCE_PROTO:=git
#PKG_SOURCE_URL:=git://sourceware.org/git/glibc.git
#PKG_SOURCE_VERSION:=$(PKG_REVISION)
#PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_REVISION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_SOURCE_SUBDIR).tar.bz2
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/toolchain/glibc

GLIBC_PATH:=

PATCH_DIR:=$(PATH_PREFIX)/patches/$(PKG_VERSION)

HOST_BUILD_DIR:=$(BUILD_DIR_TOOLCHAIN)/$(PKG_SOURCE_SUBDIR)
CUR_BUILD_DIR:=$(HOST_BUILD_DIR)-$(VARIANT)

include $(INCLUDE_DIR)/toolchain-build.mk

HOST_STAMP_PREPARED:=$(HOST_BUILD_DIR)/.prepared
HOST_STAMP_CONFIGURED:=$(CUR_BUILD_DIR)/.configured
HOST_STAMP_BUILT:=$(CUR_BUILD_DIR)/.built
HOST_STAMP_INSTALLED:=$(TOOLCHAIN_DIR)/stamp/.glibc_$(VARIANT)_installed

ifeq ($(ARCH),mips64)
  ifdef CONFIG_MIPS64_ABI_N64
    TARGET_CFLAGS += -mabi=64
  endif
  ifdef CONFIG_MIPS64_ABI_N32
    TARGET_CFLAGS += -mabi=n32
  endif
  ifdef CONFIG_MIPS64_ABI_O32
    TARGET_CFLAGS += -mabi=32
  endif
endif

GLIBC_CONFIGURE:= \
	BUILD_CC="$(HOSTCC)" \
	$(TARGET_CONFIGURE_OPTS) \
	CFLAGS="$(TARGET_CFLAGS)" \
	libc_cv_slibdir="/lib" \
	use_ldconfig=no \
	$(HOST_BUILD_DIR)/$(GLIBC_PATH)configure \
		--prefix= \
		--build=$(GNU_HOST_NAME) \
		--host=$(REAL_GNU_TARGET_NAME) \
		--with-headers=$(TOOLCHAIN_DIR)/include \
		--disable-profile \
		--disable-werror \
		--without-gd \
		--without-cvs \
		--enable-add-ons \
		--$(if $(CONFIG_SOFT_FLOAT),without,with)-fp

ifeq ($(CONFIG_GLIBC_USE_VERSION_2_24)$(CONFIG_GLIBC_USE_VERSION_2_26),y)
ifeq ("_$(call qstrip,$(CONFIG_arm)$(CONFIG_aarch64))_$(CONFIG_TARGET_brcm963xx)_","_y_y_")
GLIBC_CONFIGURE+= \
	libc_cv_forced_unwind=yes \
	--enable-shared \
	--enable-obsolete-rpc
ifeq ($(CONFIG_GLIBC_USE_VERSION_2_26),y)
GLIBC_CONFIGURE+= \
	libc_cv_ssp=no
endif
endif
endif

export libc_cv_ssp=no
export ac_cv_header_cpuid_h=yes
export HOST_CFLAGS := $(HOST_CFLAGS) -idirafter $(CURDIR)/$(PATH_PREFIX)/include

define Host/SetToolchainInfo
	$(SED) 's,^\(LIBC_TYPE\)=.*,\1=$(PKG_NAME),' $(TOOLCHAIN_DIR)/info.mk
	$(SED) 's,^\(LIBC_URL\)=.*,\1=http://www.gnu.org/software/libc/,' $(TOOLCHAIN_DIR)/info.mk
	$(SED) 's,^\(LIBC_VERSION\)=.*,\1=$(PKG_VERSION),' $(TOOLCHAIN_DIR)/info.mk
	$(SED) 's,^\(LIBC_SO_VERSION\)=.*,\1=$(PKG_VERSION),' $(TOOLCHAIN_DIR)/info.mk
endef

define Host/Configure
	[ -f $(HOST_BUILD_DIR)/.autoconf ] || { \
		cd $(HOST_BUILD_DIR)/$(GLIBC_PATH); \
		autoconf --force && \
		touch $(HOST_BUILD_DIR)/.autoconf; \
	}
	mkdir -p $(CUR_BUILD_DIR)
	( cd $(CUR_BUILD_DIR); rm -f config.cache; \
		$(GLIBC_CONFIGURE) \
	);
endef

define Host/Prepare
	$(call Host/Prepare/Default)
	ln -snf $(PKG_SOURCE_SUBDIR) $(BUILD_DIR_TOOLCHAIN)/$(PKG_NAME)
endef

define Host/Clean
	rm -rf $(CUR_BUILD_DIR)* \
		$(BUILD_DIR_TOOLCHAIN)/$(LIBC)-dev \
		$(BUILD_DIR_TOOLCHAIN)/$(PKG_NAME)
endef
