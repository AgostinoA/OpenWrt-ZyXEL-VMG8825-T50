#
# Copyright (C) 2002-2003 Erik Andersen <andersen@uclibc.org>
# Copyright (C) 2004 Manuel Novoa III <mjn3@uclibc.org>
# Copyright (C) 2005-2006 Felix Fietkau <nbd@nbd.name>
# Copyright (C) 2006-2013 OpenWrt.org
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

include $(TOPDIR)/rules.mk

PKG_NAME:=gcc
GCC_VERSION:=$(call qstrip,$(CONFIG_GCC_VERSION))
PKG_VERSION:=$(firstword $(subst +, ,$(GCC_VERSION)))
GCC_DIR:=$(PKG_NAME)-$(PKG_VERSION)

ifeq ($(findstring linaro, $(CONFIG_GCC_VERSION)),linaro)
    ifeq ($(CONFIG_GCC_VERSION),"4.6-linaro")
      PKG_REV:=4.6-2012.12
      PKG_VERSION:=4.6.4
      PKG_VERSION_MAJOR:=4.6
      PKG_MD5SUM:=6b6c6a4faa026edd1193cf6426309039
    endif
    ifeq ($(CONFIG_GCC_VERSION),"4.7-linaro")
      PKG_REV:=4.7-2013.03
      PKG_VERSION:=4.7.3
      PKG_VERSION_MAJOR:=4.7
      PKG_MD5SUM:=72e37ed0601f72e4d7e842d7e5373148
    endif
    ifeq ($(CONFIG_GCC_VERSION),"4.8-linaro")
      PKG_REV:=4.8-2014.04
      PKG_VERSION:=4.8.3
      PKG_VERSION_MAJOR:=4.8
      PKG_MD5SUM:=5ba2f3a449b1658ccc09d27cc7ab3c03
      PKG_COMP:=xz
    endif
    #PKG_SOURCE_URL:=http://launchpad.net/gcc-linaro/$(PKG_VERSION_MAJOR)/$(PKG_REV)/+download/
    PKG_SOURCE:=$(PKG_NAME)-linaro-$(PKG_REV).tar.$(PKG_COMP)
    GCC_DIR:=gcc-linaro-$(PKG_REV)
    HOST_BUILD_DIR:=$(BUILD_DIR_TOOLCHAIN)/$(GCC_DIR)
else
  #PKG_SOURCE_URL:=@GNU/gcc/gcc-$(PKG_VERSION)
  PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2

  ifeq ($(PKG_VERSION),4.4.7)
    PKG_MD5SUM:=295709feb4441b04e87dea3f1bab4281
  endif
  ifeq ($(PKG_VERSION),4.6.2)
    PKG_MD5SUM:=028115c4fbfb6cfd75d6369f4a90d87e
  endif
  ifeq ($(PKG_VERSION),4.6.3)
    PKG_MD5SUM:=773092fe5194353b02bb0110052a972e
  endif
  ifeq ($(PKG_VERSION),4.7.2)
    PKG_MD5SUM:=cc308a0891e778cfda7a151ab8a6e762
  endif
  ifeq ($(PKG_VERSION),4.8.0)
    PKG_MD5SUM:=e6040024eb9e761c3bea348d1fa5abb0
  endif
  ifeq ($(PKG_VERSION),5.3.0)
    PKG_MD5SUM:=c9616fd448f980259c31de613e575719
  endif
  ifeq ($(PKG_VERSION),5.5.0)
    PKG_MD5SUM:=d87af596eb9954385f64e2130580a558
  endif
endif

PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/toolchain/gcc

PATCH_DIR=../patches/$(GCC_VERSION)

BUGURL=https://dev.openwrt.org/
ifeq ($(findstring linaro, $(CONFIG_GCC_VERSION)),linaro)
  PKGVERSION=OpenWrt/Linaro GCC $(PKG_REV) $(REVISION)
else
  PKGVERSION=OpenWrt GCC $(PKG_VERSION) $(REVISION)
endif

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/toolchain-build.mk

HOST_SOURCE_DIR:=$(HOST_BUILD_DIR)
ifeq ($(GCC_VARIANT),minimal)
  GCC_BUILD_DIR:=$(HOST_BUILD_DIR)-$(GCC_VARIANT)
else
  HOST_BUILD_DIR:=$(HOST_BUILD_DIR)-$(GCC_VARIANT)
  GCC_BUILD_DIR:=$(HOST_BUILD_DIR)
endif

HOST_STAMP_PREPARED:=$(HOST_BUILD_DIR)/.prepared
HOST_STAMP_BUILT:=$(GCC_BUILD_DIR)/.built
HOST_STAMP_CONFIGURED:=$(GCC_BUILD_DIR)/.configured
HOST_STAMP_INSTALLED:=$(STAGING_DIR_HOST)/stamp/.gcc_$(GCC_VARIANT)_installed

SEP:=,
TARGET_LANGUAGES:="c$(if $(CONFIG_INSTALL_LIBSTDCPP),$(SEP)c++)$(if $(CONFIG_INSTALL_LIBGCJ),$(SEP)java)$(if $(CONFIG_INSTALL_GFORTRAN),$(SEP)fortran)"

export libgcc_cv_fixed_point=no
ifdef CONFIG_USE_UCLIBC
  export glibcxx_cv_c99_math_tr1=no
endif

ifdef CONFIG_GCC_USE_GRAPHITE
  ifdef CONFIG_GCC_VERSION_4_8
    GRAPHITE_CONFIGURE=--with-cloog=$(REAL_STAGING_DIR_HOST)
  else
    GRAPHITE_CONFIGURE=--with-isl=$(REAL_STAGING_DIR_HOST)
  endif
else
  GRAPHITE_CONFIGURE=--without-isl --without-cloog
endif

GCC_CONFIGURE:= \
	SHELL="$(BASH)" \
	$(if $(shell gcc --version 2>&1 | grep LLVM), \
		CFLAGS="-O2 -fbracket-depth=512 -pipe" \
		CXXFLAGS="-O2 -fbracket-depth=512 -pipe" \
	) \
	$(HOST_SOURCE_DIR)/configure \
		--with-bugurl=$(BUGURL) \
		--with-pkgversion="$(PKGVERSION)" \
		--prefix=$(TOOLCHAIN_DIR) \
		--build=$(GNU_HOST_NAME) \
		--host=$(GNU_HOST_NAME) \
		--target=$(REAL_GNU_TARGET_NAME) \
		--with-gnu-ld \
		--enable-target-optspace \
		--disable-libgomp \
		$(GRAPHITE_CONFIGURE) \
		$(SOFT_FLOAT_CONFIG_OPTION) \
		$(call qstrip,$(CONFIG_EXTRA_GCC_CONFIG_OPTIONS)) \
		$(if $(CONFIG_mips64)$(CONFIG_mips64el),--with-arch=mips64 \
			--with-abi=$(call qstrip,$(CONFIG_MIPS64_ABI))) \
		--with-gmp=$(TOPDIR)/staging_dir/host \
		--with-mpfr=$(TOPDIR)/staging_dir/host \
		--with-mpc=$(TOPDIR)/staging_dir/host \
		--disable-decimal-float

ifeq ("_$(CONFIG_arm)_$(CONFIG_TARGET_brcm963xx)_","_y_y_")
  GCC_CONFIGURE += \
		--with-abi=aapcs-linux \
		--with-tune=cortex-a9 \
		--enable-tls
ifneq ($(CONFIG_GCC_VERSION_5_3_0)$(CONFIG_GCC_VERSION_5_5_0),)
ifeq ($(GCC_VARIANT),final)
  GCC_CONFIGURE += \
		--enable-static
endif
  GCC_CONFIGURE += \
		--with-mode=arm \
		--disable-libmudflap \
		--disable-libquadmath \
		--disable-nls
ifneq ($(CONFIG_GCC_VERSION_5_5_0),)
  GCC_CONFIGURE += \
		--with-float=soft \
		--disable-option-checking
endif
endif
else
ifeq ("_$(CONFIG_aarch64)_$(CONFIG_TARGET_brcm963xx)_","_y_y_")
  GCC_CONFIGURE += \
		--with-abi=lp64 \
		--with-cpu=cortex-a53 \
		--enable-tls
ifneq ($(CONFIG_GCC_VERSION_5_3_0)$(CONFIG_GCC_VERSION_5_5_0),)
ifeq ($(GCC_VARIANT),final)
  GCC_CONFIGURE += \
		--enable-static
endif
ifneq ($(GCC_VARIANT),final)
  GCC_CONFIGURE += \
		--disable-nls
endif
  GCC_CONFIGURE += \
		--disable-libmudflap \
		--disable-libquadmath
ifneq ($(CONFIG_GCC_VERSION_5_5_0),)
  GCC_CONFIGURE += --disable-option-checking
endif
endif
else
ifeq ("_$(CONFIG_mips)_$(CONFIG_TARGET_en75xx)_$(CONFIG_UCLIBC_VERSION_0_9_33)_","_y_y_y_")
  GCC_CONFIGURE += \
		--with-abi=32 \
		--with-tune=mips32r2 \
		--disable-nls \
		--enable-tls
ifeq ("$(CONFIG_TC_SDK_7_3_245_300)","y")
  GCC_CONFIGURE += --disable-libmudflap
endif
else
  GCC_CONFIGURE += \
		--disable-libmudflap \
		--disable-nls \
		--with-host-libstdcxx=-lstdc++
endif
endif
endif

ifneq ($(CONFIG_mips)$(CONFIG_mipsel),)
 ifeq ($(CONFIG_UCLIBC_VERSION_0_9_29)$(CONFIG_UCLIBC_VERSION_0_9_30_3)$(CONFIG_UCLIBC_VERSION_0_9_33),)
  GCC_CONFIGURE += --with-mips-plt
 endif
endif

  GCC_CONFIGURE += --disable-multilib

ifndef GCC_VERSION_4_8
  GCC_CONFIGURE += --with-diagnostics-color=auto-if-env
endif

ifneq ($(CONFIG_SSP_SUPPORT),)
  GCC_CONFIGURE+= \
		--enable-libssp
else
  GCC_CONFIGURE+= \
		--disable-libssp
endif

ifneq ($(CONFIG_TLS_UNSUPPORTED),)
  GCC_CONFIGURE+= \
		--disable-tls
endif

ifneq ($(CONFIG_EXTRA_TARGET_ARCH),)
  GCC_CONFIGURE+= \
		--enable-biarch \
		--enable-targets=$(call qstrip,$(CONFIG_EXTRA_TARGET_ARCH_NAME))-linux-$(TARGET_SUFFIX)
endif

ifdef CONFIG_sparc
  GCC_CONFIGURE+= \
		--enable-targets=all \
		--with-long-double-128
endif

ifeq ($(LIBC),uClibc)
  GCC_CONFIGURE+= \
		--disable-__cxa_atexit
else
ifneq ("_$(CONFIG_aarch64)_$(CONFIG_TARGET_brcm963xx)_$(CONFIG_GCC_VERSION_5_5_0)_","_y_y_y_")
  GCC_CONFIGURE+= \
		--enable-__cxa_atexit
endif
endif



ifneq ($(GCC_ARCH),)
ifeq ($(GCC_VARIANT),final)
ifneq ("_$(call qstrip,$(CONFIG_arm)$(CONFIG_aarch64))_$(CONFIG_TARGET_brcm963xx)_","_y_y_")
ifneq ($(CONFIG_GCC_VERSION_5_3_0)$(CONFIG_GCC_VERSION_5_5_0),y)
  GCC_CONFIGURE+= --with-arch=$(GCC_ARCH)
endif
endif
endif
endif


ifneq ($(CONFIG_SOFT_FLOAT),y)
  ifeq ($(CONFIG_arm),y)
    GCC_CONFIGURE+= \
		--with-float=hard
  endif
endif

GCC_MAKE:= \
	export SHELL="$(BASH)"; \
	$(MAKE) \
		CFLAGS="$(HOST_CFLAGS)" \
		CFLAGS_FOR_TARGET="$(TARGET_CFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(TARGET_CFLAGS)"

define Host/Prepare
	mkdir -p $(GCC_BUILD_DIR)
endef

define Host/Configure
	(cd $(GCC_BUILD_DIR) && rm -f config.cache; \
		$(GCC_CONFIGURE) \
	);
endef

define Host/Clean
	rm -rf \
		$(STAGING_DIR_HOST)/stamp/.gcc_* \
		$(STAGING_DIR_HOST)/stamp/.binutils_* \
		$(GCC_BUILD_DIR) \
		$(BUILD_DIR_TOOLCHAIN)/$(PKG_NAME) \
		$(TOOLCHAIN_DIR)/$(REAL_GNU_TARGET_NAME) \
		$(TOOLCHAIN_DIR)/bin/$(REAL_GNU_TARGET_NAME)-gc* \
		$(TOOLCHAIN_DIR)/bin/$(REAL_GNU_TARGET_NAME)-c*
endef
