# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$
	
include $(TOPDIR)/rules.mk

#These lines concatanate the package name and list the URL location from which the package source code is to be downloaded
PKG_NAME:=libzcfg_fe_dal
PKG_VERSION:=1.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_SOURCE_URL:=@ZyXEL_SITE/public/ZyXEL
DL_DIR:=$(TOPDIR)/dl/public/zyxel
PKG_CAT:=zcat

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

#These lines describe what your package does and its place in the menu config

define Package/libzcfg_fe_dal
SECTION:=net
CATEGORY:=Zyxel Packages
TITLE:= ZyXEL Configuration Management Data Access Library
DESCRIPTION:=
DEPENDS:=+libzcfg_fe_rdm_string +libzcfg_fe_rdm_struct +libzcfg_fe_schema +libzyutil +libzlog
endef

#For the compile rules you need to specify the cross compiler which needs to be used :


#These lines describe where your binary images are to be installed ¡V its the equivalent to make install

# This particular package is a library and the installation rules reflect it

define CheckDependencies
endef

ifeq ("$(strip ${ZCFG_PLATFORM})","BROADCOM")
# support DSL bonding
ifeq ($(CONFIG_BRCMSDK$(shell echo $(CONFIG_BRCM_SDK_VERSION))_BRCM_PHY_BONDING),y)
export SUPPORT_DSL_BONDING=y
endif
ifneq ("$(CONFIG_BRCMSDK$(shell echo $(CONFIG_BRCM_SDK_VERSION))_BRCM_CHIP)",)
BRCM_CHIP = $(CONFIG_BRCMSDK$(shell echo $(CONFIG_BRCM_SDK_VERSION))_BRCM_CHIP)
EXTRA_CFLAGS += -DCONFIG_BCM9$(BRCM_CHIP)
endif
#EthWanAsLan
ifeq ($(CONFIG_BRCMSDK$(shell echo $(CONFIG_BRCM_SDK_VERSION))_ZYXEL_SUPPORT_ETHWAN_AS_LAN),y)
EXTRA_CFLAGS += -DZYXEL_SUPPORT_ETHWAN_AS_LAN
endif

EXTRA_CFLAGS += -DBROADCOM_PLATFORM
endif

ifeq ($(CONFIG_HAWAIIAN_TELCOM),y)
export HAWAIIAN_TELCOM=y
endif

EXTRA_CFLAGS += -DWAN_INTERFACES=$(CONFIG_ZYXEL_WEB_GUI_NUM_OF_WAN_INTF)

export CONFIG_ZYXEL_TR69_SUPPLEMENTAL_ACS

# WAN MAC for Ethernet WAN
export CONFIG_ZYXEL_WAN_MAC
export CONFIG_ZyXEL_WEB_GUI_SINGLE_IGMP_MLD
export CONFIG_ZYXEL_VDSL_Support_30A
export CONFIG_ZYXEL_VDSL_Support_35B
export CONFIG_CBT_CUSTOMIZATION
export CONFIG_ZYXEL_WEB_WIRELESS_NEW_VERSION_ONE
export CONFIG_ZYXEL_WEB_NETWORK_MAP_NEW_STYLE
export CONFIG_ZyXEL_WEB_GUI_SHOW_PON
export CONFIG_ISKON_CUSTOMIZATION
export CONFIG_ABOG_CUSTOMIZATION
export CONFIG_ZYXEL_AP_STEERING
export CONFIG_WIND_ITALY_CUSTOMIZATION
export CONFIG_ZCFG_VMG8825_B50B_WIND
export CONFIG_PACKAGE_ZyIMS
export CONFIG_TARGET_en75xx
export CONFIG_ZYXEL_WEB_GUI_ECONET_QoS_STYLE
export CONFIG_ZYXEL_WEB_GUI_SHOW_QOS_CLS_TARGET_INTF
export CONFIG_PACKAGE_webgui_vue
export CONFIG_ZYXEL_GUIVUE_USB_INFO_SHOW_SYSINFO
export CONFIG_ZyXEL_WEB_GUI_SHOW_WWAN
export CONFIG_PACKAGE_mos
export CONFIG_ZYXEL_LED_SWITCH_ACTIVE

#NAT log recorded feature
export CONFIG_ZYXEL_PPP_AUTH_MENU_CHAP_PAP_CTL
export CONFIG_ZYXEL_NAT_LOG
export CONFIG_ZYXEL_SUPPORT_8021X
# Support Econet platform portmirror use
export ECONET_PLATFORM

export CONFIG_ZYXEL_ONESSID

export CONFIG_ZYXEL_EASYMESH

#SONiQ Steering
export CONFIG_ZYXEL_SONIQ

#DHCPv6 option 64
export CONFIG_ZYXEL_DHCPV6_OPTION64

#Auto Detect Wan
export CONFIG_ELISA_NAT_PORTFORWARD_CUSTOMIZATION

#DMZ Management
export CONFIG_ZYXEL_SUPPORT_DMZ_MANAGEMENT

export CONFIG_ZY_WIFI_ONESSID_SECURITY_SYNC

export CONFIG_ZYXEL_REMOTE_ACCESS_PRIVILEGE
export CONFIG_ZYXEL_REMOTE_ACCOUNT_ACCESS_PRIVILEGE
export CONFIG_ZYXEL_REMOMGMT_SEPARATE_LAN_WLAN_PRIVILEGE
export CONFIG_ZYXEL_WLAN_SCHEDULER_AUTO_SWITCH_RADIO_ON
#Support PPTP VPN
export CONFIG_KERNEL_ZYXEL_PPTP_SUPPORT

#Support WiFi Security Mode WPA/WPA2-PSK
export CONFIG_ZYXEL_WIFI_SUPPORT_WPA_MIX_MODE

#Support Second Lan IP Alias
export CONFIG_ZYXEL_SECOND_LAN_IP_ALIAS

#Customization
export CONFIG_INTERNET_LED_DEPEND_ON_DEFAULT_GW CONFIG_ELISA_NETWORKMAP_CUSTOMIZATION CONFIG_ZYXEL_SYNC_CCWAN_TO_ALL_DEFGW
export CONFIG_SAME_FW_FOR_TWO_BOARD
export CONFIG_ZYXEL_USA_PRODUCT
export CONFIG_CODETEL_CUSTOMIZATION
export CONFIG_CLARO_CUSTOMIZATION

#Support Feature Bits
export CONFIG_ZYXEL_FEATURE_BITS

#Support fake IP 169.254.X.X/16 when WAN doesn't get IP
export CONFIG_ZYXEL_FAKE_IP_169_254_X_X

#zlog
export CONFIG_ZLOG_USE_DEBUG

#cybersecurity
export CONFIG_ZYXEL_HOME_CYBER_SECURITY_FSECURE

# Zyxel GRE Tunnel
export CONFIG_ZYXEL_GRE

# zupnp
export CONFIG_PACKAGE_zupnp

# miniupnpd
export CONFIG_PACKAGE_miniupnpd


# Avast agent package support
export CONFIG_ZYXEL_AVAST_AGENT_SUPPORT

ifeq ($(CONFIG_ZYXEL_HOME_CYBER_SECURITY_FSECURE),y)
CFLAGS += -DCONFIG_ZYXEL_HOME_CYBER_SECURITY_FSECURE=y
CONFIG_ZYXEL_ZY_LICENSE_CMD:=y
endif
export CONFIG_ZYXEL_HOME_CYBER_SECURITY
ifeq ($(CONFIG_ZYXEL_HOME_CYBER_SECURITY),y)
CFLAGS += -DCONFIG_ZYXEL_HOME_CYBER_SECURITY=y
CONFIG_ZYXEL_ZY_LICENSE_CMD:=y
endif

ifeq ($(CONFIG_ZYXEL_ZY_LICENSE_CMD),y)
CONFIG_ZYXEL_ZY_LICENSE_CMD:=y
export CONFIG_ZYXEL_ZY_LICENSE_CMD
endif


#NEW GUI
export CONFIG_ZCFG_VMG4927_B50A_Generic
export CONFIG_ZCFG_EMG6726_B10A_Generic

#Co-FW
export CONFIG_ZYXEL_BOARD_DETECT_BY_GPIO
export CONFIG_SAME_FW_FOR_PROJECTS

#SFP Power mgmt
export CONFIG_ZYXEL_SFP_POWER_MGMT

define Package/libzcfg_fe_dal/compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		EXTRA_CFLAGS="$(EXTRA_CFLAGS)"
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/*.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/libzcfg_fe_dal.so $(1)/usr/lib/
endef

define Package/libzcfg_fe_dal/install
	$(INSTALL_DIR) $(1)/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(PKG_NAME).so $(1)/lib
#	$(INSTALL_DIR) $(1)/lib/public
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libzcfg_fe_dal.so $(1)/lib/public
#	ln -s /lib/public/libzcfg_fe_dal.so $(1)/lib/libzcfg_fe_dal.so
endef

$(eval $(call BuildPackage,libzcfg_fe_dal))

