include $(TOPDIR)/rules.mk

PKG_NAME:=procd
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
PKG_VERSION:=2015-10-29.1
PKG_SOURCE_VERSION1:=d5fddd91b966424bb63e943e789704d52382cc18
else
PKG_VERSION:=2012-12-20
PKG_SOURCE_VERSION1:=d343dd9e9a64d4ae7d225ea29169e97fa8d116a1
endif
PATCH_DIR:=patches-$(PKG_VERSION)
FILES_DIR:=files-$(PKG_VERSION)
PKG_RELEASE=$(PKG_SOURCE_VERSION)

#PKG_SOURCE_PROTO:=git
#PKG_SOURCE_URL:=git://nbd.name/luci2/procd.git
#PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION1).tar.gz
CMAKE_INSTALL:=1
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/misc

PKG_LICENSE:=GPLv2
PKG_LICENSE_FILES:=

PKG_MAINTAINER:=Felix Fietkau <nbd@openwrt.org>

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
TARGET_LDFLAGS += $(if $(CONFIG_USE_GLIBC),-lrt)

define Package/procd
  SECTION:=base
  CATEGORY:=Base system
  DEPENDS:=+ubusd +ubus +libjson-script +ubox +USE_GLIBC:librt +libubox +libubus +NAND_SUPPORT:procd-nand
  TITLE:=OpenWrt system process manager
endef
else
define Package/procd
  SECTION:=base
  CATEGORY:=Base system
  DEPENDS:=+ubusd +ubus
  TITLE:=OpenWrt system process manager
endef
endif

define Package/procd-ujail
  SECTION:=base
  CATEGORY:=Base system
  DEPENDS:=@KERNEL_NAMESPACES +@KERNEL_UTS_NS +@KERNEL_IPC_NS +@KERNEL_PID_NS +libubox +libblobmsg-json
  TITLE:=OpenWrt process jail helper
endef

define Package/procd-seccomp
  SECTION:=base
  CATEGORY:=Base system
  DEPENDS:=@arm||@armeb||@mips||@mipsel||@i386||@x86_64 @!TARGET_uml @KERNEL_SECCOMP +libubox +libblobmsg-json
  TITLE:=OpenWrt process seccomp helper + utrace
endef

define Package/procd-nand
  SECTION:=utils
  CATEGORY:=Utilities
  DEPENDS:=@NAND_SUPPORT +ubi-utils
  TITLE:=OpenWrt sysupgrade nand helper
endef

define Package/procd-nand-firstboot
  SECTION:=utils
  CATEGORY:=Utilities
  DEPENDS:=procd-nand
  TITLE:=OpenWrt firstboot nand helper
endef

define Package/procd/config
menu "Configuration"
	depends on PACKAGE_procd

config PROCD_SHOW_BOOT
	bool
	default n
	prompt "Print the shutdown to the console as well as logging it to syslog"

config PROCD_ZRAM_TMPFS
	bool
	default n
	prompt "Mount /tmp using zram."
endmenu
endef


ifeq ($(CONFIG_NAND_SUPPORT),y)
  CMAKE_OPTIONS += -DBUILD_UPGRADED=1
endif

ifeq ($(CONFIG_PROCD_SHOW_BOOT),y)
  CMAKE_OPTIONS += -DSHOW_BOOT_ON_CONSOLE=1
endif

ifeq ($(CONFIG_PROCD_ZRAM_TMPFS),y)
  CMAKE_OPTIONS += -DZRAM_TMPFS=1
endif

ifeq ($(CONFIG_TARGET_ipq_ipq807x),y)
  CMAKE_OPTIONS += -DIPQ_807X=1
endif

ifdef CONFIG_PACKAGE_procd-ujail
  CMAKE_OPTIONS += -DJAIL_SUPPORT=1
endif

ifdef CONFIG_PACKAGE_procd-seccomp
  CMAKE_OPTIONS += -DSECCOMP_SUPPORT=1 -DUTRACE_SUPPORT=1
endif

ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
define Package/procd/install
	$(INSTALL_DIR) $(1)/sbin $(1)/etc $(1)/lib/functions

	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/{init,procd,askfirst,udevtrigger} $(1)/sbin/
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/libsetlbf.so $(1)/lib
	$(INSTALL_BIN) ./$(FILES_DIR)/reload_config $(1)/sbin/
	$(INSTALL_DATA) ./$(FILES_DIR)/hotplug*.json $(1)/etc/
	$(INSTALL_DATA) ./$(FILES_DIR)/procd.sh $(1)/lib/functions/
endef
else
define Package/procd/install
	$(INSTALL_DIR) $(1)/sbin $(1)/lib/functions $(1)/etc/init.d

	$(CP) $(PKG_INSTALL_DIR)/usr/sbin/procd $(1)/sbin/
	$(INSTALL_BIN) ./$(FILES_DIR)/procd.init $(1)/etc/init.d/procd
	$(INSTALL_DATA) ./$(FILES_DIR)/procd.sh $(1)/lib/functions/
endef
endif

define Package/procd-ujail/install
	$(INSTALL_DIR) $(1)/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/ujail $(1)/sbin/
endef

define Package/procd-seccomp/install
	$(INSTALL_DIR) $(1)/sbin $(1)/lib
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/libpreload-seccomp.so $(1)/lib
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/utrace $(1)/sbin/
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/libpreload-trace.so $(1)/lib
endef

define Package/procd-nand/install
	$(INSTALL_DIR) $(1)/sbin $(1)/lib/upgrade

	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/upgraded $(1)/sbin/
	$(INSTALL_DATA) ./$(FILES_DIR)/nand.sh $(1)/lib/upgrade/
endef

define Package/procd-nand-firstboot/install
	$(INSTALL_DIR) $(1)/lib/preinit

	$(INSTALL_DATA) ./$(FILES_DIR)/nand-preinit.sh $(1)/lib/preinit/60-nand-firstboot.sh
endef

$(eval $(call BuildPackage,procd))
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
$(eval $(call BuildPackage,procd-ujail))
$(eval $(call BuildPackage,procd-seccomp))
$(eval $(call BuildPackage,procd-nand))
endif
$(eval $(call BuildPackage,procd-nand-firstboot))
