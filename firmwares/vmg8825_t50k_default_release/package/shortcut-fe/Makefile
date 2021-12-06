#
# Copyright (c) 2013 Qualcomm Atheros, Inc..
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=shortcut-fe
#PKG_SOURCE_PROTO:=git
#PKG_SOURCE_URL:=ssh://qca-git01.qualcomm.com:29418/oss/lklm/shortcut-fe
PKG_SOURCE_URL:=@ZyXEL_SITE/public/Qualcomm/network/drivers
PKG_BRANCH:=master
PKG_RELEASE:=1

#include $(INCLUDE_DIR)/local-development.mk
#ifeq ($(DUMP)$(PKG_VERSION),)
  PKG_REV:=2eeabf3
  PKG_VERSION:=g2eeabf3
#endif

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=$(PKG_REV)

include $(INCLUDE_DIR)/package.mk

define KernelPackage/shortcut-fe
  SECTION:=kernel
  CATEGORY:=Kernel modules
  SUBMENU:=Network Support
  DEPENDS:=
  TITLE:=Kernel driver for SFE
  FILES:=$(PKG_BUILD_DIR)/shortcut-fe/shortcut-fe.ko
  AUTOLOAD:=$(call AutoLoad,50,shortcut-fe)
endef

define KernelPackage/shortcut-fe/Description
Shortcut is an in-Linux-kernel IP packet forwarding engine.
endef

define KernelPackage/shortcut-fe-cm
  SECTION:=kernel
  CATEGORY:=Kernel modules
  SUBMENU:=Network Support
  DEPENDS:=+kmod-shortcut-fe
  TITLE:=Kernel driver for SFE
  FILES:=$(PKG_BUILD_DIR)/shortcut-fe/shortcut-fe-cm.ko
  KCONFIG:=CONFIG_NF_CONNTRACK_EVENTS=y
  AUTOLOAD:=$(call AutoLoad,51,shortcut-fe-cm)
endef

define KernelPackage/shortcut-fe-cm/Description
Simple connection manager for the Shortcut forwarding engine.
endef

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		ARCH="$(LINUX_KARCH)" \
		SUBDIRS="$(PKG_BUILD_DIR)/shortcut-fe" \
		EXTRA_CFLAGS="$(EXTRA_CFLAGS)" \
		modules
endef

$(eval $(call KernelPackage,shortcut-fe))
$(eval $(call KernelPackage,shortcut-fe-cm))
