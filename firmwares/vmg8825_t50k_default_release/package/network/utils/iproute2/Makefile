#
# Copyright (C) 2006-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
FORCE_USE_EXTERNAL_KERNAL_TOOLCHAIN=y
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=iproute2
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
PKG_VERSION:=4.0.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
#PKG_SOURCE_URL:=http://kernel.org/pub/linux/utils/net/iproute2/
PKG_SOURCE_URL:=@ZyXEL_SITE/WIFI_Router
PKG_MD5SUM:=3adc263ade4ee76c35032e8f50b54108
else
PKG_VERSION:=2.6.33
PKG_RELEASE:=100224

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
#PKG_SOURCE_URL:=http://kernel.org/pub/linux/utils/net/iproute2/
#PKG_MD5SUM:=308e7145218dd552c2766fe527e239e1
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/network/utils
endif
DL_DIR:=$(TOPDIR)/dl
PATCH_DIR:=patches-$(PKG_VERSION)
FILES_DIR:=files-$(PKG_VERSION)
PKG_BUILD_PARALLEL:=1
#PKG_INSTALL:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/iproute2-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
define Package/iproute2/Default
  TITLE:=Routing control utility ($(2))
  SECTION:=net
  CATEGORY:=Network
  URL:=http://www.linuxfoundation.org/collaborate/workgroups/networking/iproute2
  SUBMENU:=Routing and Redirection
  MAINTAINER:=Russell Senior <russell@personaltelco.net>
  DEPENDS:= +libnl-tiny
  VARIANT:=$(1)
endef

define Package/ip
$(call Package/iproute2/Default,tiny,Minimal)
  CONFLICTS:=ip-full
endef

Package/ip-full=$(call Package/iproute2/Default,full,Full)
else
define Package/iproute2/Default
  TITLE:=Routing control utility ($(2))
  SECTION:=net
  CATEGORY:=Network
  URL:=http://linux-net.osdl.org/index.php/Iproute2
endef

define Package/ip
$(call Package/iproute2/Default)
  SUBMENU:=Routing and Redirection
ifeq ("$(CONFIG_KERNEL_ZYXEL_EXT_MARK)", "y")
  DEPENDS:= +libnl
else
  DEPENDS:= +libnl-tiny
endif
  TITLE:=Routing control utility
endef
endif
define Package/ip/conffiles
/etc/iproute2/rt_tables
endef

define Package/ip-full/conffiles
$(Package/ip/conffiles)
endef

define Package/tc
$(call Package/iproute2/Default)
  TITLE:=Traffic control utility
  DEPENDS:=+kmod-sched-core
endef

define Package/genl
$(call Package/iproute2/Default)
  TITLE:=General netlink utility frontend
endef

define Package/ip-bridge
$(call Package/iproute2/Default)
  TITLE:=Bridge configuration utility from iproute2
endef

define Package/ss
$(call Package/iproute2/Default)
  TITLE:=Socket statistics utility
endef

ifeq ($(BUILD_VARIANT),tiny)
  IP_CONFIG_TINY:=y
endif
ifeq ("$(strip ${PKG_VERSION})","4.0.0")
define Build/Configure
	$(SED) "s,-I/usr/include/db3,," $(PKG_BUILD_DIR)/Makefile
	$(SED) "s,^KERNEL_INCLUDE.*,KERNEL_INCLUDE=$(LINUX_DIR)/include," \
		$(PKG_BUILD_DIR)/Makefile
	$(SED) "s,^LIBC_INCLUDE.*,LIBC_INCLUDE=$(STAGING_DIR)/include," \
		$(PKG_BUILD_DIR)/Makefile
	echo "static const char SNAPSHOT[] = \"$(PKG_VERSION)-$(PKG_RELEASE)-openwrt\";" \
		> $(PKG_BUILD_DIR)/include/SNAPSHOT.h
endef
endif
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
#TARGET_CFLAGS += -DHAVE_SETNS
TARGET_CFLAGS += -ffunction-sections -fdata-sections

MAKE_FLAGS += \
	EXTRA_CCOPTS="$(TARGET_CFLAGS) -I../include -I$(STAGING_DIR)/usr/include/libnl-tiny" \
	KERNEL_INCLUDE="$(LINUX_DIR)/include" \
	SHARED_LIBS="" \
	LDFLAGS="-Wl,--gc-sections $(TARGET_LDFLAGS)" \
	IP_CONFIG_TINY=$(IP_CONFIG_TINY) \
	FPIC="$(FPIC)"
else
ifdef CONFIG_USE_GLIBC
  TARGET_CFLAGS += -DHAVE_SETNS
endif
ifeq ("$(CONFIG_KERNEL_ZYXEL_EXT_MARK)", "y")
MAKE_FLAGS += \
	EXTRA_CCOPTS="$(TARGET_CFLAGS) -I../include -I$(STAGING_DIR)/usr/include/libnl" \
	KERNEL_DIR="$(LINUX_DIR)" \
	ARCH="$(LINUX_KARCH)" \
	FPIC="$(FPIC)"
else
MAKE_FLAGS += \
	EXTRA_CCOPTS="$(TARGET_CFLAGS) -I../include -I$(STAGING_DIR)/usr/include/libnl-tiny" \
	KERNEL_DIR="$(LINUX_DIR)" \
	ARCH="$(LINUX_KARCH)" \
	FPIC="$(FPIC)"
endif

MAKE_FLAGS += ZCFG_PLATFORM=ECONET
ifeq ("$(strip ${ZCFG_PLATFORM})","ECONET")
ifeq ("$(strip $(CONFIG_$(subst $\",,$(CONFIG_CUSTOM_SDK_PREFIX))_TCSUPPORT_3_18_21_KERNEL))","y")
MAKE_FLAGS += TCSUPPORT_3_18_21_KERNEL=y
endif
endif
endif
define Build/Compile
	+$(MAKE_VARS) $(MAKE) $(PKG_JOBS) -C $(PKG_BUILD_DIR) $(MAKE_FLAGS)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/include/libnetlink.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/lib/libnetlink.a $(1)/usr/lib/
endef

define Package/ip/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_DIR) $(1)/etc/iproute2
	ln -s /var/iproute2/rt_tables $(1)/etc/iproute2/rt_tables
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ip/ip $(1)/usr/sbin/
endef

define Package/ip-$(BUILD_VARIANT)/install
	$(Package/ip/install)
endef

define Package/tc/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/tc/tc $(1)/usr/sbin/
ifeq ("$(strip ${PKG_VERSION})","4.0.0")
	$(INSTALL_DIR) $(1)/etc/hotplug.d/iface
	$(INSTALL_BIN) ./$(FILES_DIR)/15-teql $(1)/etc/hotplug.d/iface/
endif
endef

define Package/genl/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/genl/genl $(1)/usr/sbin/
endef

define Package/ip-bridge/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bridge/bridge $(1)/usr/sbin/
endef

define Package/ss/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/misc/ss $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,ip))

$(eval $(call BuildPackage,tc))
$(eval $(call BuildPackage,genl))

$(eval $(call BuildPackage,ss))
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
$(eval $(call BuildPackage,ip-bridge))
$(eval $(call BuildPackage,ip-full))
endif
