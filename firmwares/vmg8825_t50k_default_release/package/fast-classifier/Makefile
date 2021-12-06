#
# Copyright (c) 2013 Qualcomm Atheros, Inc..
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=fast-classifier
#PKG_SOURCE_PROTO:=git
#PKG_SOURCE_URL:=ssh://qca-git01.qualcomm.com:29418/oss/lklm/shortcut-fe
PKG_SOURCE_URL:=@ZyXEL_SITE/public/Qualcomm/network/drivers
PKG_BRANCH:=master
PKG_RELEASE:=1

#LOCAL_SRC:=$(TOPDIR)/qca/src/shortcut-fe
#include $(INCLUDE_DIR)/local-development.mk
#ifeq ($(DUMP)$(PKG_VERSION),)
  PKG_REV:=2eeabf3
  PKG_VERSION:=g2eeabf3
#endif

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=$(PKG_REV)

include $(INCLUDE_DIR)/package.mk

define KernelPackage/fast-classifier
  SECTION:=kernel
  CATEGORY:=Kernel modules
  SUBMENU:=Network Support
  DEPENDS:=+libnl-bf +kmod-shortcut-fe
  TITLE:=Kernel driver for FAST Classifier
  FILES:=$(PKG_BUILD_DIR)/fast-classifier/fast-classifier.ko
  AUTOLOAD:=$(call AutoLoad,51,fast-classifier)
endef

define KernelPackage/fast-classifier/Description
FAST Classifier talks to SFE to make decisions about offloading connections
endef

define Package/fast-classifier-example
  TITLE:=Example user space program for fast-classifier
  DEPENDS:=+libnl +libfast-classifier
endef

define Package/libfast-classifier
  SECTION:=libs
  TITLE:=Library to invoke fast-classifier offload
  CATEGORY:=Libraries
endef

define Package/fast-classifier-example/description
Example user space program that communicates with fast
classifier kernel module
endef

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		CONFIG_FAST_CLASSIFIER=m \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		ARCH="$(LINUX_KARCH)" \
		SUBDIRS="$(PKG_BUILD_DIR)/fast-classifier" \
		EXTRA_CFLAGS="$(EXTRA_CFLAGS)" \
		modules

	$(TARGET_CC) -Wall -fPIC -c $(PKG_BUILD_DIR)/fast-classifier/fast-classifier-lib.c \
				-I$(LINUX_DIR)/user_headers/include \
				-I$(STAGING_DIR)/usr/include/libnl3 \
				-o $(PKG_BUILD_DIR)/fast-classifier/fast-classifier-lib.o

	$(TARGET_CC) -shared -Wl,-soname,libfast-classifier.so -o \
		$(PKG_BUILD_DIR)/fast-classifier/libfast-classifier.so \
		$(PKG_BUILD_DIR)/fast-classifier/fast-classifier-lib.o

	$(TARGET_CC) -o $(PKG_BUILD_DIR)/userspace_fast_classifier \
		-I $(PKG_BUILD_DIR)/fast-classifier \
		-L $(PKG_BUILD_DIR)/fast-classifier \
		-lfast-classifier -lnl-genl-3 \
		$(PKG_BUILD_DIR)/fast-classifier/userspace_example.c
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/fast-classifier/fast-classifier.h $(1)/usr/include/

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/fast-classifier/libfast-classifier.so $(1)/usr/lib/
endef

define Package/libfast-classifier/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/fast-classifier/libfast-classifier.so $(1)/usr/lib/
endef

define Package/fast-classifier-example/install
	$(INSTALL_DIR) $(1)/sbin
	$(CP) $(PKG_BUILD_DIR)/userspace_fast_classifier $(1)/sbin/
endef

$(eval $(call KernelPackage,fast-classifier))
$(eval $(call BuildPackage,fast-classifier-example))
$(eval $(call BuildPackage,libfast-classifier))
