#
# Copyright (C) 2007-2012 OpenWrt.org
# Copyright (C) 2010 Vertical Communications
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/version.mk

PKG_NAME:=base-files-econet
PKG_RELEASE:=1

PKG_FILE_DEPENDS:=$(PLATFORM_DIR)/
PKG_BUILD_DEPENDS:=opkg/host

include $(INCLUDE_DIR)/package.mk

ifneq ($(DUMP),1)
  TARGET:=-$(BOARD)
  ifneq ($(wildcard $(PLATFORM_DIR)/$(PKG_NAME)-$(PROFILE) $(PLATFORM_SUBDIR)/$(PKG_NAME)-$(PROFILE)),)
    TARGET:=$(TARGET)-$(PROFILE)
  endif
endif

define Package/$(PKG_NAME)
  SECTION:=base
  CATEGORY:=Base system
  DEPENDS:=+libc
  TITLE:=Base filesystem for Econdet SDK
  URL:=
  VERSION:=$(PKG_RELEASE)-$(REVISION)
endef

define Package/$(PKG_NAME)/conffiles
/usr/etc/hosts
/usr/etc/inittab
/usr/etc/group
/usr/etc/passwd
/usr/etc/shadow
/usr/etc/profile
/usr/etc/shells
$(call $(TARGET)/conffiles)
endef

define Package/$(PKG_NAME)/description
 This package contains a base filesystem and system scripts.
endef

ifneq ($(CONFIG_PREINITOPT),)
define ImageConfigOptions
	mkdir -p $(1)/lib/preinit
	echo 'pi_suppress_stderr="$(CONFIG_TARGET_PREINIT_SUPPRESS_STDERR)"' >$(1)/lib/preinit/00_preinit.conf
	echo 'fs_failsafe_wait_timeout=$(if $(CONFIG_TARGET_PREINIT_TIMEOUT),$(CONFIG_TARGET_PREINIT_TIMEOUT),2)' >>$(1)/lib/preinit/00_preinit.conf
	echo 'pi_init_path=$(if $(CONFIG_TARGET_INIT_PATH),$(CONFIG_TARGET_INIT_PATH),"/bin:/sbin:/usr/bin:/usr/sbin")' >>$(1)/lib/preinit/00_preinit.conf
	echo 'pi_init_env=$(if $(CONFIG_TARGET_INIT_ENV),$(CONFIG_TARGET_INIT_ENV),"")' >>$(1)/lib/preinit/00_preinit.conf
	echo 'pi_init_cmd=$(if $(CONFIG_TARGET_INIT_CMD),$(CONFIG_TARGET_INIT_CMD),"/sbin/init")' >>$(1)/lib/preinit/00_preinit.conf
	echo 'pi_init_suppress_stderr="$(CONFIG_TARGET_INIT_SUPPRESS_STDERR)"' >>$(1)/lib/preinit/00_preinit.conf
	echo 'pi_ifname=$(if $(CONFIG_TARGET_PREINIT_IFNAME),$(CONFIG_TARGET_PREINIT_IFNAME),"")' >>$(1)/lib/preinit/00_preinit.conf
	echo 'pi_ip=$(if $(CONFIG_TARGET_PREINIT_IP),$(CONFIG_TARGET_PREINIT_IP),"192.168.1.1")' >>$(1)/lib/preinit/00_preinit.conf
	echo 'pi_netmask=$(if $(CONFIG_TARGET_PREINIT_NETMASK),$(CONFIG_TARGET_PREINIT_NETMASK),"255.255.255.0")' >>$(1)/lib/preinit/00_preinit.conf
	echo 'pi_broadcast=$(if $(CONFIG_TARGET_PREINIT_BROADCAST),$(CONFIG_TARGET_PREINIT_BROADCAST),"192.168.1.255")' >>$(1)/lib/preinit/00_preinit.conf
	echo 'pi_preinit_net_messages="$(CONFIG_TARGET_PREINIT_SHOW_NETMSG)"' >>$(1)/lib/preinit/00_preinit.conf
	echo 'pi_preinit_no_failsafe_netmsg="$(CONFIG_TARGET_PREINIT_SUPPRESS_FAILSAFE_NETMSG)"' >>$(1)/lib/preinit/00_preinit.conf
endef
endif

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Compile/Default

endef
Build/Compile = $(Build/Compile/Default)

define Package/$(PKG_NAME)/install
	$(CP) ./files/* $(1)/
	if [ -d $(PLATFORM_DIR)/$(PKG_NAME)/. ]; then \
		$(CP) $(PLATFORM_DIR)/$(PKG_NAME)/* $(1)/; \
	fi
	if [ -d $(PLATFORM_DIR)/$(PKG_NAME)-$(PROFILE)/. ]; then \
		$(CP) $(PLATFORM_DIR)/$(PKG_NAME)-$(PROFILE)/* $(1)/; \
	fi
	if [ -d $(PLATFORM_DIR)/$(PROFILE)$(PKG_NAME)/. ]; then \
		$(CP) $(PLATFORM_DIR)/$(PROFILE)$(PKG_NAME)/* $(1)/; \
	fi
	$(if $(filter-out $(PLATFORM_DIR),$(PLATFORM_SUBDIR)), \
		if [ -d $(PLATFORM_SUBDIR)/$(PKG_NAME)/. ]; then \
			$(CP) $(PLATFORM_SUBDIR)/$(PKG_NAME)/* $(1)/; \
		fi; \
		if [ -d $(PLATFORM_SUBDIR)/$(PKG_NAME)-$(PROFILE)/. ]; then \
			$(CP) $(PLATFORM_SUBDIR)/$(PKG_NAME)-$(PROFILE)/* $(1)/; \
		fi; \
		if [ -d $(PLATFORM_SUBDIR)/$(PROFILE)/$(PKG_NAME)/. ]; then \
			$(CP) $(PLATFORM_SUBDIR)/$(PROFILE)/$(PKG_NAME)/* $(1)/; \
		fi \
	)

	$(ZYXEL_VERSION_SED) \
		$(1)/usr/etc/banner

	mkdir -p $(1)/CONTROL
	mkdir -p $(1)/dev
	mkdir -p $(1)/etc/crontabs
	mkdir -p $(1)/etc/rc.d
	mkdir -p $(1)/lib/firmware
	$(if $(LIB_SUFFIX),-ln -s lib $(1)/lib$(LIB_SUFFIX))
	mkdir -p $(1)/mnt
	mkdir -p $(1)/proc
	mkdir -p $(1)/tmp
	mkdir -p $(1)/usr/lib
	$(if $(LIB_SUFFIX),-ln -s lib $(1)/usr/lib$(LIB_SUFFIX))
	mkdir -p $(1)/usr/bin
	mkdir -p $(1)/sys
	mkdir -p $(1)/root
	ln -sf /proc/mounts $(1)/usr/etc/mtab
	#rm -fr $(1)/var
	#ln -sf /tmp/var $(1)/var
	mkdir -p $(1)/etc
	mkdir -p $(1)/data
	
	# force use dnsmasq as cpe dns proxy server.
	echo "nameserver 127.0.0.1" > $(1)/etc/resolv.conf

	#chmod 0600 $(1)/usr/etc/shadow

	$(call ImageConfigOptions,$(1))
	$(call Package/$(PKG_NAME)/install-target,$(1))
	for conffile in $(1)/etc/config/*; do \
		if [ -f "$$$$conffile" ]; then \
			grep "$$$${conffile##$(1)}" $(1)/CONTROL/conffiles || \
				echo "$$$${conffile##$(1)}" >> $(1)/CONTROL/conffiles; \
		fi \
	done
endef

ifneq ($(DUMP),1)
  -include $(PLATFORM_DIR)/$(PKG_NAME).mk
endif

$(eval $(call BuildPackage,$(PKG_NAME)))
