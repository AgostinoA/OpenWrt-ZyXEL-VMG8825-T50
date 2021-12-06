include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=logrotate
PKG_VERSION:=3.7.1
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/utils
DL_DIR:=$(TOPDIR)/dl

PKG_CAT:=zcat

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/logrotate
SECTION:=base
CATEGORY:=Base system
TITLE:=Utility which generates a lot of log files
DESCRIPTION:=
DEPENDS:=+libpopt
endef
ifeq ($(strip $(CONFIG_ISKON_CUSTOMIZATION)),y)
ADSLINFOSTR= echo "*/15 * * * * /bin/xdslctl info --ikstats > /var/adslinfo" >> $(1)/etc/crontab; 
else
ADSLINFOSTR= 
endif

#define Build/Compile
#	$(MAKE) -C $(PKG_BUILD_DIR) \
#		CC="$(TARGET_CROSS)gcc"
#endef

define Package/logrotate/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(CP) $(PKG_BUILD_DIR)/logrotate $(1)/usr/sbin
	if [ ! -d $(1)/etc/logrotate.d ]; then \
		mkdir -m 755 -p $(1)/etc/logrotate.d ; \
	fi
	install -m 755 $(PKG_BUILD_DIR)/zyxel.etc/sys_logrotate.conf $(1)/etc/logrotate.d
	install -m 755 $(PKG_BUILD_DIR)/zyxel.etc/voip_logrotate.conf $(1)/etc/logrotate.d
	if [ ! -f $(1)/etc/crontab ]; then \
		touch $(1)/etc/crontab ; \
	fi
	if [ -z "`cat $(1)/etc/crontab | grep sys_logrotate.conf`" ]; then \
		echo "*/5 * * * * /usr/sbin/logrotate /etc/logrotate.d/sys_logrotate.conf " >> $(1)/etc/crontab; \
		$(ADSLINFOSTR) \
	fi

endef

$(eval $(call BuildPackage,logrotate))

