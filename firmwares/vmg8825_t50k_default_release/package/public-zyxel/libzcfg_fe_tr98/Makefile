# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$
	
include $(TOPDIR)/rules.mk

#These lines concatanate the package name and list the URL location from which the package source code is to be downloaded

PKG_BUILD_DEPENDS:=zcfg CONFIG_ZYXEL_ONECONNECT:libsqlite3

PKG_NAME:=libzcfg_fe_tr98
PKG_VERSION:=1.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_SOURCE_URL:=@ZyXEL_SITE/public/ZyXEL
DL_DIR:=$(TOPDIR)/dl/public/zyxel
PKG_CAT:=zcat

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

#Generic
export CONFIG_ZYXEL_SUPPORT_TR98_LOGIN_ACCOUNT CONFIG_PACKAGE_tmsctl CONFIG_ZYXEL_DL_DIAG_CALCULATION CONFIG_ZYXEL_SUPPORT_TR098_BRCM_BONDING_LINE CONFIG_ZYXEL_SUPPORT_DMZ_MANAGEMENT CONFIG_ZYXEL_TR69_SUPPLEMENTAL_ACS

#Sunrise
export CONFIG_SUNRISE_TR98_CUSTOMIZATION CONFIG_SUNRISE_STB_PROVISION CONFIG_SUNRISE_RANDOM_PASSWORD CONFIG_SUNRISE_BRIDGE_INDEX_CUSTOMIZATION CONFIG_ZCFG_RUNNING_WANDEV_INDEX_CUSTOMIZATION CONFIG_PACKAGE_ZyIMS

#SuperOnline
export CONFIG_SOL_TR69_AUTO_CHANGE_DHCP_POOL CONFIG_SOL_TR69_FIREWALL_CONTROL CONFIG_SOL_TR69_3G_Backup CONFIG_SOL_TR69_TRUSTDOMAIN CONFIG_SOL_TR69_LOGINACCOUNT CONFIG_SOL_TR69_NO_LAN_HOST CONFIG_ZyXEL_DHCP_OPTION125 CONFIG_ZyXEL_IPP_PRINTSERVER

#Wind
export CONFIG_BUILD_ZYXEL_VOICE_CONFIG_TR069_FAXT38_ENABLE_MAPPING_TO_FAXMODE

#CBT
export CONFIG_CBT_CUSTOMIZATION

#One Connect
export CONFIG_ZYXEL_ONECONNECT CONFIG_ZYXEL_HOSTPOLLING

#WIND
export CONFIG_WIND_CUSTOMIZATION

export CONFIG_WIND_ITALY_CUSTOMIZATION

#ISKON
export CONFIG_USE_OLD_VOIP_PREFIX
export CONFIG_ISKON_CUSTOMIZATION

#TISCALI
export CONFIG_TISCALI_CUSTOMIZATION

# ELISA
export CONFIG_ELISA_TR69_WANDSL_CUSTOMIZATION CONFIG_ELISA_CUSTOMIZATION

#SONiQ Steering
export CONFIG_ZYXEL_SONIQ
export CONFIG_ZYXEL_WIFI_NUM_OF_24G_SSID_INTERFACE
export CONFIG_ZYXEL_WIFI_NUM_OF_5G_SSID_INTERFACE

#Easy Mesh
export CONFIG_ZYXEL_EASYMESH

#ONESSID
export CONFIG_ZYXEL_ONESSID

#VMG1312-T20A for BRAZIL
export CONFIG_BRAZIL_CUSTOMIZATION

#TR69 standard phone binding
export CONFIG_BUILD_ZYXEL_VOICE_CONFIG_TR069_SIP_PHONE_MAPPING_BY_STD_PHY_REFERENCE_LIST

#TR69 Data Usage
export CONFIG_ZYXEL_TR69_DATA_USAGE

#Landing Page
export CONFIG_ZYXEL_LANDING_PAGE_FEATURE

#ZYXEL_WiFi_SingleSKU
export CONFIG_ZYXEL_WIFI_SingleSKU

#AP Steering
export CONFIG_ZYXEL_AP_STEERING

#Proximity Sensor
export CONFIG_PROXIMITY_SENSOR_SUPPORT

#Support WPA2-Enterprise/WPA2-EAP
export CONFIG_ZYXEL_SUPPORT_WL_WPA2_EAP

#support SFP MODULE
export CONFIG_ZYXEL_SFP_MODULE_SUPPORT

#SP DOMAIN TIMER
export CONFIG_ZYXEL_SP_DOMAIN_TIMER

#Support Avast agent package
export CONFIG_ZYXEL_AVAST_AGENT_SUPPORT

DEPLIBS=
ifeq ($(CONFIG_ZYXEL_ONECONNECT),y)
	DEPLIBS +=libsqlite3
endif

#XPON
export CONFIG_XPON_SUPPORT

export CONFIG_GENERIC_TR98_LAN_IP_ALIAS

export CONFIG_PACKAGE_ztr64
#These lines describe what your package does and its place in the menu config

export CONFIG_ZCFG_TR98_PARAM_GUARD

export CONFIG_ZCFG_QUERY_TR98_PARM_ATTR_LIST

export CONFIG_ZCFG_TR098181_OBJECT_MAPPING_NUM_NAME_CONVERT

export CONFIG_ZCFG_APPLY_RPC_METHOD_AND_SUBSEQUENT_ROUT

export CONFIG_ZYXEL_ELIMINATE_DHCP_LEASE

export CONFIG_ZCFG_LOG_USE_DEBUGCFG

export CONFIG_ZYXEL_WLAN_MAXBITRATE

#Oi
export CONFIG_ZYXEL_TR98_IPV6SPECIFIC

export CONFIG_ZYXEL_GRE

export CONFIG_ZYXEL_SUPPORT_8021X

export CONFIG_ZYXEL_SFP_POWER_MGMT

define Package/libzcfg_fe_tr98
SECTION:=net
CATEGORY:=Zyxel Packages
TITLE:= ZyXEL Configuration Management Frontend TR-098 Data Model Access Library
DESCRIPTION:=
DEPENDS:=+$(DEPLIBS)
endef

define Package/libzcfg_fe_tr98/config
	select PACKAGE_libzcfg_fe_rdm_string if PACKAGE_zcfg
	select PACKAGE_libzcfg_fe_rdm_struct if PACKAGE_zcfg
endef
#Disable Dependencies Check
define CheckDependencies
endef

#For the compile rules you need to specify the cross compiler which needs to be used :


#These lines describe where your binary images are to be installed ¡V its the equivalent to make install

# This particular package is a library and the installation rules reflect it

define Package/libzcfg_fe_tr98/compile
	$(MAKE) -C $(PKG_BUILD_DIR)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/*.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/libzcfg_fe_tr98.so $(1)/usr/lib/
endef

define Package/libzcfg_fe_tr98/install
	$(INSTALL_DIR) $(1)/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(PKG_NAME).so $(1)/lib
#	$(INSTALL_DIR) $(1)/lib/public
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libzcfg_fe_tr98.so $(1)/lib/public
endef

$(eval $(call BuildPackage,libzcfg_fe_tr98))
