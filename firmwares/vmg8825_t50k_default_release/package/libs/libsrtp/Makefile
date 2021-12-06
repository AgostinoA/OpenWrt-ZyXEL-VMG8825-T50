#
# Copyright (C) 2006-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libsrtp
PKG_VERSION:=1.4.2
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
#PKG_SOURCE_URL:=http://oss.metaparadigm.com/json-c/
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/libs

PATCH_DIR:=patches-$(PKG_VERSION)

PKG_LICENSE:=BSD
PKG_LICENSE_FILES:=LICENSE

#PKG_FIXUP:=autoreconf
#PKG_INSTALL:=1

PKG_MAINTAINER:=David A. McGrew <mcgrew@cisco.com>

include $(INCLUDE_DIR)/package.mk

###Michael.20180319.001: Make the SRTP Library support to be well-compiled for the BRCM New SDK 502L04-based Image of the ARM-architecture Platform (BCM63138/63137/63136-based VMG8823-Bx0B) by NOT using the INLINE function(s).
### PLATFORM: BRCM (963XX).-------------------------------------------------------------------------------
define Convert_BRCM_SDK_VERSION_To_NUMBER
$(shell B=$$((`echo $(1) | cut -f 1 -d 'L'` / 100)); R=$$((`echo $(1) | cut -f 1 -d 'L'` % 100)); C=$$((`echo $(1) | cut -f 2 -d 'L' | sed 's/[^0-9]*//g' | cut -c 1-2`)); M=`echo $(1) | cut -f 2 -d 'L' | sed 's/[^A-Fa-f]*//g' | cut -c 1`; E=$$((`[ "$$M" != "" ] && printf "%d" "0x$$M" || printf 0`)); V=$$(( $$((B << 20)) + $$((R << 12)) + $$((C << 4)) + $$((E)) )); echo $$V;)
endef

ifneq ("$(strip $(CONFIG_TARGET_brcm963xx))","")

	ifneq ("$(strip $(BRCM_SDK_VERSION))","")
		BRCM_SDK_VER_NUM=$(call Convert_BRCM_SDK_VERSION_To_NUMBER, $(BRCM_SDK_VERSION))
	else
		BRCM_SDK_VER_NUM=$(call Convert_BRCM_SDK_VERSION_To_NUMBER, $(CONFIG_BRCM_SDK_VERSION))
	endif

	BRCM_SDK_VER_NUM_500L01=$(call Convert_BRCM_SDK_VERSION_To_NUMBER, "500L01")

	ifeq ($(shell test $(BRCM_SDK_VER_NUM) -ge $(BRCM_SDK_VER_NUM_500L01); echo $$?),0)
		ifeq ($(CONFIG_ARCH), "mips")
			TARGET_CONFIGURE_OPTS += FUNC_INLINE=no
		else ifeq ($(CONFIG_arm), y)
			TARGET_CONFIGURE_OPTS += FUNC_INLINE=no
		endif
	endif
endif
### ------------------------------------------------------------------------------------------------------

TARGET_CFLAGS += $(FPIC)

define Package/libsrtp
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=SRTP Library
endef


define Package/libsrtp/description
 This package contains a library for SRTP.
endef


define Build/Compile
        $(MAKE) -C $(PKG_BUILD_DIR)
endef


### Michael.20150318.002: Modify to change the Voice/VoIP-related OpenWRT-based Common Reference Resources (Header file + Library) Install Path/Directory.
#define Build/InstallDev
#	$(INSTALL_DIR) $(STAGING_DIR)/usr/include/libsrtp/include
#	$(INSTALL_DIR) $(STAGING_DIR)/usr/include/libsrtp/crypto/include
#	
#	$(CP) $(PKG_BUILD_DIR)/include/*.h  $(STAGING_DIR)/usr/include/libsrtp/include
#	$(CP) $(PKG_BUILD_DIR)/crypto/include/*.h  $(STAGING_DIR)/usr/include/libsrtp/crypto/include
#endef
define Build/InstallDev
	$(INSTALL_DIR) $(STAGING_DIR)/usr/include/voice/srtp
	$(CP) $(PKG_BUILD_DIR)/include/*.h  $(STAGING_DIR)/usr/include/voice/srtp/

	$(INSTALL_DIR) $(STAGING_DIR)/usr/include/voice/srtp/crypto
	$(CP) $(PKG_BUILD_DIR)/crypto/include/*.h  $(STAGING_DIR)/usr/include/voice/srtp/crypto/
endef


### Michael.20150318.002: Modify to change the Voice/VoIP-related OpenWRT-based Common Reference Resources (Header file + Library) Install Path/Directory.
#define Package/libsrtp/install
#	$(CP) $(PKG_BUILD_DIR)/libsrtp.a  $(STAGING_DIR)/usr/lib/
#endef
define Package/libsrtp/install
	$(CP) $(PKG_BUILD_DIR)/libsrtp.a  $(STAGING_DIR)/usr/lib/voice/
endef


$(eval $(call BuildPackage,libsrtp))
