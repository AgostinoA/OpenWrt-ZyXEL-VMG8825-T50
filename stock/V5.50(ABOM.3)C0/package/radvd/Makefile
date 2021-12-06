include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=radvd
PKG_VERSION:=1.8
#PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/network/services
DL_DIR:=$(TOPDIR)/dl

PKG_CAT:=zcat

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

#IPv6 Ready Logo Conformance
export CONFIG_ZYXEL_IPV6_READYLOGO_CONFORMANCE

#BRCM_LIBS:=+libatmctl +libxdslctl +libcms_boardctl +libcms_util

define Package/radvd/Default
  SECTION:=ipv6
  CATEGORY:=IPv6
  TITLE:=IPv6 Routing Advertisement
  URL:=http://v6web.litech.org/radvd/
  DEPENDS:=+kmod-ipv6
endef

#########################################3
define Package/radvd
  $(call Package/radvd/Default)
  TITLE+= Daemon
endef

define Package/radvd/description
radvd is the router advertisement daemon for IPv6. It listens to router
solicitations and sends router advertisements as described in "Neighbor
Discovery for IP Version 6 (IPv6)" (RFC 4861).  With these advertisements hosts
can automatically configure their addresses and some other parameters. They also
can choose a default router based on these advertisements.
endef

define Package/radvdump
  $(call Package/radvd/Default)
  TITLE+= Dumper
endef

define Package/radvdump/description
radvdump prints out the contents of incoming router advertisements sent by radvd
or some other software implementing (parts of) "Neighbor Discovery for IP
Version 6 (IPv6)" (RFC 4861).
endef

CONFIGURE_ARGS += \
	--with-configfile=/etc/radvd.conf \
	--with-logfile=/var/log/radvd.log \
	--with-pidfile=/var/run/radvd.pid

#define Package/radvd/conffiles
#/etc/config/radvd
#endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		CC="$(TARGET_CROSS)gcc" \
		USRLIBDIR=$(STAGING_DIR)/usr/lib \
		PLATFORM=broadcom \
		BCM_INSTALL_DIR=$(BCM_BUILD_DIR)/targets/$(PROFILE)/fs.install \
		BUILD_DIR=$(BCM_BUILD_DIR) \
		ZYXEL=y
endef

#define Package/radvd/install
#	$(INSTALL_DIR) $(1)/etc/config
#	$(INSTALL_CONF) ./files/radvd.config $(1)/etc/config/radvd
#	$(INSTALL_DIR) $(1)/etc/init.d
#	$(INSTALL_BIN) ./files/radvd.init $(1)/etc/init.d/radvd
#	$(INSTALL_DIR) $(1)/etc/hotplug.d/iface
#	$(INSTALL_DATA) ./files/radvd.hotplug $(1)/etc/hotplug.d/iface/05-radvd
#	$(INSTALL_DIR) $(1)/usr/sbin
#	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/radvd $(1)/usr/sbin/
#endef

define Package/radvd/install
	$(INSTALL_DIR) $(1)/bin
	$(CP) $(PKG_BUILD_DIR)/radvd $(1)/bin
endef

define Package/radvdump/install
	$(INSTALL_DIR) $(1)/bin
	$(CP) $(PKG_BUILD_DIR)/radvdump $(1)/bin
	#$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/radvdump $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,radvd))
$(eval $(call BuildPackage,radvdump))
########################################

