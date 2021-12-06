#
# Copyright (C) 2006-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

ifneq ($(__rules_inc),1)
__rules_inc=1

ifeq ($(DUMP),)
  -include $(TOPDIR)/.config
  -include $(TOPDIR)/private_config
endif
include $(TOPDIR)/include/debug.mk
include $(TOPDIR)/include/verbose.mk

TMP_DIR:=$(TOPDIR)/tmp

GREP_OPTIONS=
export GREP_OPTIONS

qstrip=$(strip $(subst ",,$(1)))
#"))

empty:=
space:= $(empty) $(empty)
merge=$(subst $(space),,$(1))
confvar=$(call merge,$(foreach v,$(1),$(if $($(v)),y,n)))
strip_last=$(patsubst %.$(lastword $(subst .,$(space),$(1))),%,$(1))

define sep

endef

_SINGLE=export MAKEFLAGS=$(space);
CFLAGS:=
ARCH:=$(subst i486,i386,$(subst i586,i386,$(subst i686,i386,$(call qstrip,$(CONFIG_ARCH)))))
ARCH_PACKAGES:=$(call qstrip,$(CONFIG_TARGET_ARCH_PACKAGES))
BOARD:=$(call qstrip,$(CONFIG_TARGET_BOARD))
TARGET_OPTIMIZATION:=$(call qstrip,$(CONFIG_TARGET_OPTIMIZATION))
TARGET_SUFFIX=$(call qstrip,$(CONFIG_TARGET_SUFFIX))
BUILD_SUFFIX:=$(call qstrip,$(CONFIG_BUILD_SUFFIX))
SUBDIR:=$(patsubst $(TOPDIR)/%,%,${CURDIR})
export SHELL:=/usr/bin/env bash

OPTIMIZE_FOR_CPU=$(subst i386,i486,$(ARCH))

ifeq ($(ARCH),powerpc)
  FPIC:=-fPIC
else
  FPIC:=-fpic
endif

HOST_FPIC:=-fPIC

ARCH_SUFFIX:=
GCC_ARCH:=

ifneq ($(filter -march=armv%,$(TARGET_OPTIMIZATION)),)
  ARCH_SUFFIX:=_$(patsubst -march=arm%,%,$(filter -march=armv%,$(TARGET_OPTIMIZATION)))
  GCC_ARCH:=$(patsubst -march=%,%,$(filter -march=armv%,$(TARGET_OPTIMIZATION)))
endif
ifneq ($(filter -mips%r2,$(TARGET_OPTIMIZATION)),)
  ARCH_SUFFIX:=_r2
endif
ifdef CONFIG_USE_MIPS16
   TARGET_OPTIMIZATION+= -minterlink-mips16 -mips16
endif
ifneq ($(findstring -mips16,$(TARGET_OPTIMIZATION)),)
  TARGET_ASFLAGS_OVERRIDE:=-mno-mips16
  ARCH_SUFFIX:= $(ARCH_SUFFIX)_m16
endif
ifdef CONFIG_HAS_SPE_FPU
  TARGET_SUFFIX:=$(TARGET_SUFFIX)spe
endif
ifdef CONFIG_MIPS64_ABI
  ifneq ($(CONFIG_MIPS64_ABI_O32),y)
     ARCH_SUFFIX:=$(ARCH_SUFFIX)_$(subst ",,$(CONFIG_MIPS64_ABI))
  endif
endif
ifeq ($(CONFIG_TARGET_ipq_ipq807x),y)
  ARCH_SUFFIX:=$(call qstrip,$(CONFIG_CPU_TYPE))
  ifneq ($(ARCH_SUFFIX),)
    ARCH_SUFFIX:=_$(ARCH_SUFFIX)
  endif
endif

#ifeq (_$(CONFIG_EXTERNAL_KERNEL_TOOLCHAIN)_$(FORCE_USE_EXTERNAL_KERNAL_TOOLCHAIN)_,_y_y_)
#ARCH:=$(call qstrip,$(CONFIG_KERNEL_TOOLCHAIN_CPU_ARCH))
#TARGET_OPTIMIZATION:=$(call qstrip,$(CONFIG_KERNEL_TOOLCHAIN_TARGET_OPTIMIZATION))
#TARGET_SUFFIX:=$(call qstrip,$(CONFIG_KERNEL_TOOLCHAIN_TARGET_SUFFIX))
#ARCH_SUFFIX:=
#endif

DL_DIR:=$(if $(call qstrip,$(CONFIG_DOWNLOAD_FOLDER)),$(call qstrip,$(CONFIG_DOWNLOAD_FOLDER)),$(TOPDIR)/dl)
BIN_DIR:=$(TOPDIR)/bin/$(BOARD)
INCLUDE_DIR:=$(TOPDIR)/include
SCRIPT_DIR:=$(TOPDIR)/scripts
BUILD_DIR_BASE:=$(TOPDIR)/build_dir
BUILD_DIR_HOST:=$(BUILD_DIR_BASE)/host
STAGING_DIR_HOST:=$(TOPDIR)/staging_dir/host
ifeq ($(CONFIG_EXTERNAL_TOOLCHAIN),)
  GCCV:=$(call qstrip,$(CONFIG_GCC_VERSION))
  LIBC:=$(call qstrip,$(CONFIG_LIBC))
  LIBCV:=$(call qstrip,$(CONFIG_LIBC_VERSION))
  REAL_GNU_TARGET_NAME=$(OPTIMIZE_FOR_CPU)-openwrt-linux$(if $(TARGET_SUFFIX),-$(TARGET_SUFFIX))
  GNU_TARGET_NAME=$(OPTIMIZE_FOR_CPU)-openwrt-linux
  DIR_SUFFIX:=_$(LIBC)-$(LIBCV)$(if $(CONFIG_arm),_eabi)
  BIN_DIR:=$(BIN_DIR)$(if $(CONFIG_USE_UCLIBC),,-$(LIBC))
  BUILD_DIR:=$(BUILD_DIR_BASE)/target-$(ARCH)$(ARCH_SUFFIX)$(DIR_SUFFIX)$(if $(BUILD_SUFFIX),_$(BUILD_SUFFIX))
  STAGING_DIR:=$(TOPDIR)/staging_dir/target-$(ARCH)$(ARCH_SUFFIX)$(DIR_SUFFIX)$(if $(BUILD_SUFFIX),_$(BUILD_SUFFIX))
  BUILD_DIR_TOOLCHAIN:=$(BUILD_DIR_BASE)/toolchain-$(ARCH)$(ARCH_SUFFIX)_gcc-$(GCCV)$(DIR_SUFFIX)
  TOOLCHAIN_DIR:=$(TOPDIR)/staging_dir/toolchain-$(ARCH)$(ARCH_SUFFIX)_gcc-$(GCCV)$(DIR_SUFFIX)
  PACKAGE_DIR:=$(BIN_DIR)/packages
else
  ifeq ($(CONFIG_NATIVE_TOOLCHAIN),)
    GNU_TARGET_NAME=$(call qstrip,$(CONFIG_TARGET_NAME))
  else
    GNU_TARGET_NAME=$(shell gcc -dumpmachine)
  endif
  REAL_GNU_TARGET_NAME=$(GNU_TARGET_NAME)
  BUILD_DIR:=$(BUILD_DIR_BASE)/target-$(GNU_TARGET_NAME)$(if $(BUILD_SUFFIX),_$(BUILD_SUFFIX))
  STAGING_DIR:=$(TOPDIR)/staging_dir/target-$(GNU_TARGET_NAME)$(if $(BUILD_SUFFIX),_$(BUILD_SUFFIX))
  BUILD_DIR_TOOLCHAIN:=$(BUILD_DIR_BASE)/toolchain-$(GNU_TARGET_NAME)
  TOOLCHAIN_DIR:=$(TOPDIR)/staging_dir/toolchain-$(GNU_TARGET_NAME)
  PACKAGE_DIR:=$(BIN_DIR)/packages
endif

ifneq ("$(CONFIG_EXTERNAL_KERNEL_TOOLCHAIN)","")
  KERNEL_TOOLCHAIN_TARGET_OPTIMIZATION:=$(call qstrip,$(CONFIG_KERNEL_TOOLCHAIN_TARGET_OPTIMIZATION))
  KERNEL_TOOLCHAIN_TARGET_SUFFIX:=$(call qstrip,$(CONFIG_KERNEL_TOOLCHAIN_TARGET_SUFFIX))
  KERNEL_TOOLCHAIN_ARCH_SUFFIX:=
  KERNEL_TOOLCHAIN_ARCH:=$(call qstrip,$(CONFIG_KERNEL_TOOLCHAIN_CPU_ARCH))
  KERNEL_TOOLCHAIN_GCCV:=$(call qstrip,$(CONFIG_KERNEL_TOOLCHAIN_GCC_VERSION))
  KERNEL_TOOLCHAIN_LIBC:=glibc
  KERNEL_TOOLCHAIN_LIBCV:=$(call qstrip,$(CONFIG_KERNEL_TOOLCHAIN_GLIBC_VERSION))
  KERNEL_TOOLCHAIN_REAL_GNU_TARGET_NAME=$(KERNEL_TOOLCHAIN_ARCH)-openwrt-linux$(if $(KERNEL_TOOLCHAIN_TARGET_SUFFIX),-$(KERNEL_TOOLCHAIN_TARGET_SUFFIX))
  KERNEL_TOOLCHAIN_GNU_TARGET_NAME=$(KERNEL_TOOLCHAIN_ARCH)-openwrt-linux
  KERNEL_TOOLCHAIN_DIR_SUFFIX:=_$(KERNEL_TOOLCHAIN_LIBC)-$(KERNEL_TOOLCHAIN_LIBCV)
  KERNEL_TOOLCHAIN_BUILD_DIR:=$(BUILD_DIR_BASE)/target-$(KERNEL_TOOLCHAIN_ARCH)$(KERNEL_TOOLCHAIN_ARCH_SUFFIX)$(KERNEL_TOOLCHAIN_DIR_SUFFIX)$(if $(BUILD_SUFFIX),_$(BUILD_SUFFIX))
  KERNEL_TOOLCHAIN_STAGING_DIR:=$(TOPDIR)/staging_dir/target-$(KERNEL_TOOLCHAIN_ARCH)$(KERNEL_TOOLCHAIN_ARCH_SUFFIX)$(KERNEL_TOOLCHAIN_DIR_SUFFIX)$(if $(BUILD_SUFFIX),_$(BUILD_SUFFIX))
  KERNEL_TOOLCHAIN_DIR:=$(TOPDIR)/staging_dir/external_kernel_toolchain/toolchain-$(call qstrip,$(CONFIG_KERNEL_TOOLCHAIN_CPU_ARCH))_gcc-$(call qstrip,$(CONFIG_KERNEL_TOOLCHAIN_GCC_VERSION))_glibc-$(call qstrip,$(CONFIG_KERNEL_TOOLCHAIN_GLIBC_VERSION))
else
  KERNEL_TOOLCHAIN_DIR:=NULL
endif

STAMP_DIR:=$(BUILD_DIR)/stamp
STAMP_DIR_HOST=$(BUILD_DIR_HOST)/stamp
TARGET_ROOTFS_DIR?=$(if $(call qstrip,$(CONFIG_TARGET_ROOTFS_DIR)),$(call qstrip,$(CONFIG_TARGET_ROOTFS_DIR)),$(BUILD_DIR))
TARGET_DIR:=$(TARGET_ROOTFS_DIR)/root-$(BOARD)
STAGING_DIR_ROOT:=$(STAGING_DIR)/root-$(BOARD)
BUILD_LOG_DIR:=$(TOPDIR)/logs
PKG_INFO_DIR := $(STAGING_DIR)/pkginfo

TARGET_PATH:=$(STAGING_DIR_HOST)/bin:$(subst $(space),:,$(filter-out .,$(filter-out ./,$(subst :,$(space),$(PATH)))))
TARGET_CFLAGS:=$(TARGET_OPTIMIZATION)$(if $(CONFIG_DEBUG), -g3)
TARGET_CXXFLAGS = $(TARGET_CFLAGS)
TARGET_ASFLAGS = $(TARGET_CFLAGS) $(TARGET_ASFLAGS_OVERRIDE)
TARGET_CPPFLAGS:=-I$(STAGING_DIR)/usr/include -I$(STAGING_DIR)/include
TARGET_LDFLAGS:=-L$(STAGING_DIR)/usr/lib -L$(STAGING_DIR)/lib
ifneq ($(CONFIG_EXTERNAL_TOOLCHAIN),)
LIBGCC_S_PATH=$(realpath $(wildcard $(call qstrip,$(CONFIG_LIBGCC_ROOT_DIR))/$(call qstrip,$(CONFIG_LIBGCC_FILE_SPEC))))
LIBGCC_S=$(if $(LIBGCC_S_PATH),-L$(dir $(LIBGCC_S_PATH)) -lgcc_s)
LIBGCC_A=$(realpath $(lastword $(wildcard $(dir $(LIBGCC_S_PATH))/gcc/*/*/libgcc.a)))
else
LIBGCC_A=$(lastword $(wildcard $(TOOLCHAIN_DIR)/lib/gcc/*/*/libgcc.a))
LIBGCC_S=$(if $(wildcard $(TOOLCHAIN_DIR)/lib/libgcc_s.so),-L$(TOOLCHAIN_DIR)/lib -lgcc_s,$(LIBGCC_A))
endif

ifeq (_$(CONFIG_EXTERNAL_KERNEL_TOOLCHAIN)_$(FORCE_USE_EXTERNAL_KERNAL_TOOLCHAIN)_,_y_y_)
GNU_TARGET_NAME=$(KERNEL_TOOLCHAIN_GNU_TARGET_NAME)
TARGET_CFLAGS:=$(KERNEL_TOOLCHAIN_TARGET_OPTIMIZATION)$(if $(CONFIG_DEBUG), -g3)
TARGET_CXXFLAGS = $(TARGET_CFLAGS)
TARGET_ASFLAGS = $(TARGET_CFLAGS) $(TARGET_ASFLAGS_OVERRIDE)
TARGET_CPPFLAGS:=-I$(KERNEL_TOOLCHAIN_DIR)/usr/include -I$(KERNEL_TOOLCHAIN_DIR)/include
TARGET_LDFLAGS:=-L$(KERNEL_TOOLCHAIN_DIR)/usr/lib -L$(KERNEL_TOOLCHAIN_DIR)/lib
LIBGCC_S_PATH=$(realpath $(wildcard $(call qstrip,$(KERNEL_TOOLCHAIN_DIR))/$(call qstrip,$(CONFIG_EXTERNAL_KERNAL_LIBGCC_FILE_SPEC))))
LIBGCC_S=$(if $(LIBGCC_S_PATH),-L$(dir $(LIBGCC_S_PATH)) -lgcc_s)
LIBGCC_A=$(realpath $(lastword $(wildcard $(dir $(LIBGCC_S_PATH))/gcc/*/*/libgcc.a)))
endif

LIBRPC=-lrpc
LIBRPC_DEPENDS=+librpc

ifeq ($(CONFIG_ARCH_64BIT),y)
  LIB_SUFFIX:=64
endif

ifndef DUMP
  ifneq ($(CONFIG_EXTERNAL_KERNEL_TOOLCHAIN),)
    #TARGET_PATH:=$(KERNEL_TOOLCHAIN_DIR)/bin:$(TARGET_PATH)
    #KERNEL_TOOLCHAIN_ROOT_DIR:=$(call qstrip,$(CONFIG_KERNEL_TOOLCHAIN_ROOT))
    KERNEL_TOOLCHAIN_ROOT_DIR:=$(KERNEL_TOOLCHAIN_DIR)
    KERNEL_TOOLCHAIN_BIN_DIRS:=$(patsubst ./%,$(KERNEL_TOOLCHAIN_ROOT_DIR)/%,$(call qstrip,$(CONFIG_KERNEL_TOOLCHAIN_BIN_PATH)))
    KERNEL_TARGET_CROSS:=$(call qstrip,$(CONFIG_KERNEL_TOOLCHAIN_PREFIX))-
    KERNEL_TOOLCHAIN_INC_DIRS:=$(patsubst ./%,$(KERNEL_TOOLCHAIN_ROOT_DIR)/%,$(call qstrip,$(CONFIG_KERNEL_TOOLCHAIN_INC_PATH)))
    KERNEL_TOOLCHAIN_LIB_DIRS:=$(patsubst ./%,$(KERNEL_TOOLCHAIN_ROOT_DIR)/%,$(call qstrip,$(CONFIG_KERNEL_TOOLCHAIN_LIB_PATH)))
    ifneq ($(KERNEL_TOOLCHAIN_BIN_DIRS),)
      TARGET_PATH:=$(subst $(space),:,$(KERNEL_TOOLCHAIN_BIN_DIRS)):$(TARGET_PATH)
    endif
  endif

  ifeq ($(CONFIG_EXTERNAL_TOOLCHAIN),)
    -include $(TOOLCHAIN_DIR)/info.mk
    export GCC_HONOUR_COPTS:=0
  ifeq (_$(CONFIG_EXTERNAL_KERNEL_TOOLCHAIN)_$(FORCE_USE_EXTERNAL_KERNAL_TOOLCHAIN)_,_y_y_)
    #BUILD_DIR:=$(KERNEL_TOOLCHAIN_BUILD_DIR)
    #STAGING_DIR:=$(KERNEL_TOOLCHAIN_STAGING_DIR)
    #STAMP_DIR:=$(KERNEL_TOOLCHAIN_BUILD_DIR)/stamp
    #PKG_INFO_DIR:=$(KERNEL_TOOLCHAIN_STAGING_DIR)/pkginfo
    TOOLCHAIN_DIR:=$(KERNEL_TOOLCHAIN_DIR)
    TARGET_CROSS:=$(KERNEL_TARGET_CROSS)
    TARGET_CFLAGS+= -fhonour-copts $(if $(CONFIG_GCC_VERSION_4_3)$(CONFIG_GCC_VERSION_4_4)$(CONFIG_GCC_VERSION_4_5),,-Wno-error=unused-but-set-variable)
    ifneq ($(KERNEL_TOOLCHAIN_INC_DIRS),)
      TARGET_CPPFLAGS+= $(patsubst %,-I%,$(KERNEL_TOOLCHAIN_INC_DIRS))
    endif
    ifneq ($(KERNEL_TOOLCHAIN_LIB_DIRS),)
      TARGET_LDFLAGS+= $(patsubst %,-L%,$(KERNEL_TOOLCHAIN_LIB_DIRS))
    endif
    TARGET_PATH:=$(KERNEL_TOOLCHAIN_DIR)/bin:$(TARGET_PATH)
  else

    TARGET_CROSS:=$(if $(TARGET_CROSS),$(TARGET_CROSS),$(OPTIMIZE_FOR_CPU)-openwrt-linux$(if $(TARGET_SUFFIX),-$(TARGET_SUFFIX))-)
    TARGET_CFLAGS+= -fhonour-copts $(if $(CONFIG_GCC_VERSION_4_3)$(CONFIG_GCC_VERSION_4_4)$(CONFIG_GCC_VERSION_4_5),,-Wno-error=unused-but-set-variable)
    TARGET_CPPFLAGS+= -I$(TOOLCHAIN_DIR)/usr/include -I$(TOOLCHAIN_DIR)/include
    TARGET_LDFLAGS+= -L$(TOOLCHAIN_DIR)/usr/lib -L$(TOOLCHAIN_DIR)/lib
    TARGET_PATH:=$(TOOLCHAIN_DIR)/bin:$(TARGET_PATH)
  endif
  else
    ifeq ($(CONFIG_NATIVE_TOOLCHAIN),)
      TOOLCHAIN_ROOT_DIR:=$(call qstrip,$(CONFIG_TOOLCHAIN_ROOT))
      TOOLCHAIN_BIN_DIRS:=$(patsubst ./%,$(TOOLCHAIN_ROOT_DIR)/%,$(call qstrip,$(CONFIG_TOOLCHAIN_BIN_PATH)))
      TARGET_CROSS:=$(call qstrip,$(TOOLCHAIN_ROOT_DIR)/bin/$(CONFIG_TOOLCHAIN_PREFIX))
      TOOLCHAIN_INC_DIRS:=$(patsubst ./%,$(TOOLCHAIN_ROOT_DIR)/%,$(call qstrip,$(CONFIG_TOOLCHAIN_INC_PATH)))
      TOOLCHAIN_LIB_DIRS:=$(patsubst ./%,$(TOOLCHAIN_ROOT_DIR)/%,$(call qstrip,$(CONFIG_TOOLCHAIN_LIB_PATH)))
      ifneq ($(TOOLCHAIN_BIN_DIRS),)
        TARGET_PATH:=$(subst $(space),:,$(TOOLCHAIN_BIN_DIRS)):$(TARGET_PATH)
      endif
      ifneq ($(TOOLCHAIN_INC_DIRS),)
        TARGET_CPPFLAGS+= $(patsubst %,-I%,$(TOOLCHAIN_INC_DIRS))
      endif
      ifneq ($(TOOLCHAIN_LIB_DIRS),)
        TARGET_LDFLAGS+= $(patsubst %,-L%,$(TOOLCHAIN_LIB_DIRS))
      endif
      TARGET_PATH:=$(TOOLCHAIN_DIR)/bin:$(TARGET_PATH)
    endif
  endif
endif
TARGET_PATH_PKG:=$(STAGING_DIR)/host/bin:$(TARGET_PATH)

ifeq ($(CONFIG_SOFT_FLOAT),y)
  SOFT_FLOAT_CONFIG_OPTION:=--with-float=soft
  ifeq ($(CONFIG_arm),y)
    TARGET_CFLAGS+= -mfloat-abi=soft
  else
    TARGET_CFLAGS+= -msoft-float
  endif
else
  SOFT_FLOAT_CONFIG_OPTION:=
  ifeq ($(CONFIG_arm),y)
    TARGET_CFLAGS+= -mfloat-abi=hard
  endif
endif

export PATH:=$(TARGET_PATH)
export STAGING_DIR
export SH_FUNC:=. $(INCLUDE_DIR)/shell.sh;

PKG_CONFIG:=$(STAGING_DIR_HOST)/bin/pkg-config

export PKG_CONFIG

HOSTCC:=gcc
HOSTCXX:=g++
HOST_CPPFLAGS:=-I$(STAGING_DIR_HOST)/include
HOST_CFLAGS:=-O2 $(HOST_CPPFLAGS)
HOST_LDFLAGS:=-L$(STAGING_DIR_HOST)/lib

ifeq ($(CONFIG_GCC_VERSION_4_3)$(CONFIG_GCC_VERSION_4_4)$(CONFIG_GCC_VERSION_4_6)$(CONFIG_EXTERNAL_TOOLCHAIN)$(CONFIG_GCC_VERSION_4_8),)
  TARGET_AR:=$(TARGET_CROSS)gcc-ar
  TARGET_RANLIB:=$(TARGET_CROSS)gcc-ranlib
  TARGET_NM:=$(TARGET_CROSS)gcc-nm
else
  TARGET_AR:=$(TARGET_CROSS)ar
  TARGET_RANLIB:=$(TARGET_CROSS)ranlib
  TARGET_NM:=$(TARGET_CROSS)nm
endif

ifneq ($(CONFIG_EXTERNAL_KERNEL_TOOLCHAIN),)
  KERNEL_TARGET_CC:=$(KERNEL_TARGET_CROSS)gcc
endif

TARGET_CC:=$(TARGET_CROSS)gcc
TARGET_CXX:=$(if $(CONFIG_INSTALL_LIBSTDCPP),$(TARGET_CROSS)g++,no)
KPATCH:=$(SCRIPT_DIR)/patch-kernel.sh
SED:=$(STAGING_DIR_HOST)/bin/sed -i -e
CP:=cp -fpR
LN:=ln -sf

INSTALL_BIN:=install -m0755
INSTALL_DIR:=install -d -m0755
INSTALL_DATA:=install -m0644
INSTALL_CONF:=install -m0600

TARGET_CC_NOCACHE:=$(TARGET_CC)
TARGET_CXX_NOCACHE:=$(TARGET_CXX)
HOSTCC_NOCACHE:=$(HOSTCC)
HOSTCXX_NOCACHE:=$(HOSTCXX)
export TARGET_CC_NOCACHE
export TARGET_CXX_NOCACHE
export HOSTCC_NOCACHE

ifneq ($(CONFIG_CCACHE),)
  TARGET_CC:= ccache_cc
  TARGET_CXX:= ccache_cxx
  HOSTCC:= ccache $(HOSTCC)
  HOSTCXX:= ccache $(HOSTCXX)
endif

TARGET_CONFIGURE_OPTS = \
  AR="$(TARGET_AR)" \
  AS="$(TARGET_CC) -c $(TARGET_ASFLAGS)" \
  LD=$(TARGET_CROSS)ld \
  NM="$(TARGET_NM)" \
  CC="$(TARGET_CC)" \
  GCC="$(TARGET_CC)" \
  CXX="$(TARGET_CXX)" \
  RANLIB="$(TARGET_RANLIB)" \
  STRIP=$(TARGET_CROSS)strip \
  OBJCOPY=$(TARGET_CROSS)objcopy \
  OBJDUMP=$(TARGET_CROSS)objdump \
  SIZE=$(TARGET_CROSS)size

# strip an entire directory
ifneq ($(CONFIG_NO_STRIP),)
  RSTRIP:=:
  STRIP:=:
else
  ifneq ($(CONFIG_USE_STRIP),)
    ifneq ($(CONFIG_EXTERNAL_KERNEL_TOOLCHAIN),)
      #ZYXEL, add for RSTRIP 64-bits
      STRIP:=$(KERNEL_TARGET_CROSS)strip $(call qstrip,$(CONFIG_STRIP_ARGS))
    else
      STRIP:=$(TARGET_CROSS)strip $(call qstrip,$(CONFIG_STRIP_ARGS))
    endif
  else
    ifneq ($(CONFIG_USE_SSTRIP),)
      STRIP:=$(STAGING_DIR_HOST)/bin/sstrip
    endif
  endif
  
  ifneq ($(CONFIG_EXTERNAL_KERNEL_TOOLCHAIN),)
      #ZYXEL, add for RSTRIP 64-bits
      RSTRIP:= \
        export CROSS="$(KERNEL_TARGET_CROSS)" \
            $(if $(CONFIG_KERNEL_KALLSYMS),NO_RENAME=1) \
            $(if $(CONFIG_KERNEL_PROFILING),KEEP_SYMBOLS=1); \
        NM="$(KERNEL_TARGET_CROSS)nm" \
        STRIP="$(STRIP)" \
        STRIP_KMOD="$(SCRIPT_DIR)/strip-kmod.sh" \
        $(SCRIPT_DIR)/rstrip.sh
  else
      RSTRIP:= \
        export CROSS="$(TARGET_CROSS)" \
            $(if $(CONFIG_KERNEL_KALLSYMS),NO_RENAME=1) \
            $(if $(CONFIG_KERNEL_PROFILING),KEEP_SYMBOLS=1); \
        NM="$(TARGET_CROSS)nm" \
        STRIP="$(STRIP)" \
        STRIP_KMOD="$(SCRIPT_DIR)/strip-kmod.sh" \
        $(SCRIPT_DIR)/rstrip.sh
  endif
endif

#CROSS_PLATFORM
ifeq ($(CONFIG_TARGET_brcm963xx),y)
	ZCFG_PLATFORM=BROADCOM
else
	ifneq ($(CONFIG_TARGET_mt75xx)$(CONFIG_TARGET_en75xx),)
		ZCFG_PLATFORM=ECONET
		ECONET_SDK_VERSION=$(call qstrip,$(CONFIG_TC_SDK_VERSION))
		ECONET_TARGET_VERSION=$(call qstrip,$(CONFIG_TARGET_BOARD))
		export ECONET_TARGET_VERSION
		export ECONET_SDK_VERSION
	endif
endif
ifeq ($(CONFIG_TARGET_ipq_ipq807x),y)
  ZCFG_PLATFORM=QUALCOMM
  QUALCOMM_SDK_VERSION=$(call qstrip,$(CONFIG_QUALCOMM_SDK_VERSION))
  export QUALCOMM_SDK_VERSION
endif

ifeq ($(CONFIG_TARGET_ramips)$,y)
	ZCFG_PLATFORM=MTKSOC
endif

export ZCFG_PLATFORM

#SDK UPGRADE
ifeq ($(CONFIG_TARGET_brcm963xx),y)
        BRCM_SDK_VERSION=$(call qstrip,$(CONFIG_BRCM_SDK_VERSION))
        export BRCM_SDK_VERSION
ifeq ($(CONFIG_BRCM_CFE_CHIP_6858),y)
        BRCM_CHIP="6858"
        export BRCM_CHIP
endif        
ifeq ($(CONFIG_BRCM_CFE_CHIP_6856),y)
        BRCM_CHIP="6856"
        export BRCM_CHIP
endif
ifeq ($(CONFIG_BRCM_CFE_CHIP_63158),y)
        BRCM_CHIP="63158"
        export BRCM_CHIP
endif   
endif

#RMA firmware
ifeq ($(CONFIG_ZYXEL_RMA_FW_SUPPORT),y)
    export CONFIG_ZYXEL_RMA_FW_SUPPORT
endif

#sys fwur command
ifeq ($(CONFIG_ZYXEL_SYS_FWUR_SUPPORT),y)
    export CONFIG_ZYXEL_SYS_FWUR_SUPPORT
endif

ifeq ($(CONFIG_ENABLE_LOCALE),true)
  DISABLE_NLS:=--enable-nls
else
  DISABLE_NLS:=--disable-nls
endif

ifeq ($(CONFIG_IPV6),y)
  DISABLE_IPV6:=
else
  DISABLE_IPV6:=--disable-ipv6
endif

ifeq ($(CONFIG_TAR_VERBOSITY),y)
  TAR_OPTIONS:=-xvf -
else
  TAR_OPTIONS:=-xf -
endif

ifeq ($(CONFIG_BUILD_LOG),y)
  BUILD_LOG:=1
endif

define shvar
V_$(subst .,_,$(subst -,_,$(subst /,_,$(1))))
endef

define shexport
$(call shvar,$(1))=$$(call $(1))
export $(call shvar,$(1))
endef

define include_mk
$(eval -include $(if $(DUMP),,$(STAGING_DIR)/mk/$(strip $(1))))
endef

# Execute commands under flock
# $(1) => The shell expression.
# $(2) => The lock name. If not given, the global lock will be used.
define locked
	SHELL= \
	$(STAGING_DIR_HOST)/bin/flock \
		$(TMP_DIR)/.$(if $(2),$(strip $(2)),global).flock \
		-c '$(subst ','\'',$(1))'
endef

# Recursively copy paths into another directory, purge dangling
# symlinks before.
# $(1) => File glob expression
# $(2) => Destination directory
define file_copy
	for src_dir in $(sort $(foreach d,$(wildcard $(1)),$(dir $(d)))); do \
		( cd $$src_dir; find -type f -or -type d ) | \
			( cd $(2); while :; do \
				read FILE; \
				[ -z "$$FILE" ] && break; \
				[ -L "$$FILE" ] || continue; \
				echo "Removing symlink $(2)/$$FILE"; \
				rm -f "$$FILE"; \
			done; ); \
	done; \
	$(CP) $(1) $(2)
endef

#
#   CP, 2018-01-08 13:48:29
#
#   link all files in the folder and sub-folders to the destination
#       parameter 1 is the source directory
#       parameter 2 is the destination directory
#
define link_files
	for src_dir in `find $(1) -type d -print`; do \
	( \
		if [[ $$src_dir != "." ]]; \
		then \
			mkdir -p $(2)/$$src_dir; \
			for src_file in `find $$src_dir -maxdepth 1 -type f -print`; do \
			( \
				ln -f $$src_file $2/$$src_dir; \
			); \
			done \
		fi \
	); \
	done
endef

ZYXEL_PUBLIC_PACKAGE  := $(TOPDIR)/package/public-zyxel
ZYXEL_PRIVATE_PACKAGE := $(TOPDIR)/package/private/zyxel

export ZYXEL_PUBLIC_PACKAGE
export ZYXEL_PRIVATE_PACKAGE


# file extension
ext=$(word $(words $(subst ., ,$(1))),$(subst ., ,$(1)))

all:
FORCE: ;
.PHONY: FORCE

val.%:
	@$(if $(filter undefined,$(origin $*)),\
		echo "$* undefined" >&2, \
		echo '$(subst ','"'"',$($*))' \
	)

var.%:
	@$(if $(filter undefined,$(origin $*)),\
		echo "$* undefined" >&2, \
		echo "$*='"'$(subst ','"'\"'\"'"',$($*))'"'" \
	)

endif #__rules_inc
