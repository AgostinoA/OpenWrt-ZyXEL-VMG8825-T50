#
# Copyright (c) 2013 Mikhail Gusarov <dottedmag@dottedmag.net>
#
# This is a free software, licensed under GNU General Public License v2+.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=hfsprogs
PKG_VERSION:=332.25
PKG_RELEASE:=1

PKG_SOURCE:=diskdev_cmds-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/utils
PKG_BUILD_DIR:=$(BUILD_DIR)/diskdev_cmds-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/hfsprogs/Default
  SECTION:=utils
  CATEGORY:=Utilities
  URL:=http://opensource.apple.com/
  SUBMENU:=Filesystem
endef

define Package/hfs-fsck
  $(call Package/hfsprogs/Default)
  TITLE:=hfs-fsck
endef

define Package/hfs-fsck/description
  Utilities to create and check HFS and HFS+ filesystems.
  (fsck.hfs and fsck.hfsplus for checking integrity of HFS/HFS+ volumes)
endef

define Build/Configure
endef

CFLAGS = \
  -DDEBUG_BUILD=0 \
  -D_FILE_OFFSET_BITS=64 \
  -DLINUX=1 -DBSD=1 \
  -I$(PKG_BUILD_DIR)/include \
  $(TARGET_CFLAGS)

LDFLAGS = -Wl,--as-needed \
  $(TARGET_LDFLAGS)

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) -f Makefile.lnx CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" CC="$(TARGET_CC)" SUBDIRS=fsck_hfs.tproj
endef

define Package/hfs-fsck/install
	$(INSTALL_DIR) $(1)/lib/functions/fsck/
	$(INSTALL_DATA) ./files/hfs-fsck.sh $(1)/lib/functions/fsck/
	$(INSTALL_DIR) $(1)/usr/sbin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/fsck_hfs.tproj/fsck_hfs $(1)/usr/sbin/
	ln -sf fsck_hfs $(1)/usr/sbin/fsck.hfs
	ln -sf fsck_hfs $(1)/usr/sbin/fsck.hfsplus
endef

$(eval $(call BuildPackage,hfs-fsck))