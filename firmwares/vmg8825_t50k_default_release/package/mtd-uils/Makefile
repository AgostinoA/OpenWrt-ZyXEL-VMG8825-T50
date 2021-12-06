#
# Copyright (C) 2009-2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=mtd-utils
PKG_VERSION:=2.0.2
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_CAT:=zcat

PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/tools
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)

PKG_INSTALL:=1
PKG_FIXUP:=autoreconf

PKG_FLAGS:=nonshared

#PKG_BUILD_DEPENDS:=util-linux lzo zlib
#Start, ZyXEL, use zlib, not use lzo
PKG_BUILD_DEPENDS:=util-linux zlib
#End, ZyXEL

PKG_LICENSE:=GPLv2
PKG_LICENSE_FILES:=

include $(INCLUDE_DIR)/package.mk
FILES:=

ifneq ($(CONFIG_LINUX_2_4),y)
FILES += \
	ubiattach \
	ubicrc32 \
	ubiblock \
	ubidetach \
	ubiformat \
	ubimkvol \
	ubinfo \
	ubinize \
	ubirename \
	ubirmvol \
	ubirsvol \
	ubiupdatevol \
	flash_erase \
	nanddump \
	nandwrite \
	nandtest \
	mtdinfo
endif

define PartGen
define Package/mtd-utils-$(subst _,-,$(1))
  TITLE:=MTD $(1)
  URL:=http://www.linux-mtd.infradead.org/
  SECTION:=utils
  CATEGORY:=Utilities
  DEPENDS:=mtd-utils +zlib +libuuid
endef
endef

# +libext2fs
define Package/mtd-utils
  TITLE:=Utilities for flash info/debug
  SECTION:=utils
  CATEGORY:=Utilities
  MENU:=1
endef

define Package/mtd-utils/description
  Utilities for manipulating memory technology devices.
endef

define Package/mtd-utils/install
	true
endef

$(foreach file,$(FILES),$(eval $(call PartGen,$(file))))
MAKE_FLAGS += LDLIBS+="$(LIBGCC_S)"
MAKE_FLAGS += \
	DESTDIR="$(PKG_INSTALL_DIR)" \
	BUILDDIR="$(PKG_BUILD_DIR)" \
	LDLIBS+="$(LIBGCC_S) -L$(PKG_BUILD_DIR)/lib -lmtd " \
	CFLAGS+="$(CFLAGS)" \
	WITHOUT_XATTR=1 WITHOUT_LZO=1 WITHOUT_XZ=1

CONFIGURE_ARGS += \
	--disable-tests \
	--without-xattr \
	--without-lzo

TARGET_CFLAGS += -ffunction-sections -fdata-sections
TARGET_LDFLAGS += -Wl,--gc-sections

define PartInstall
define Package/mtd-utils-$(subst _,-,$(1))/install
	$(INSTALL_DIR) \
		$$(1)/usr/sbin

	$(INSTALL_BIN) \
		$(PKG_BUILD_DIR)/$(1) \
		$$(1)/usr/sbin/
endef
endef

define Build/Prepare
	$(PKG_UNPACK)
	$(Build/Patch)
endef

$(foreach file,$(FILES),$(eval $(call PartInstall,$(file))))

$(eval $(call BuildPackage,mtd-utils))
$(foreach file,$(FILES),$(eval $(call BuildPackage,mtd-utils-$(subst _,-,$(file)))))
