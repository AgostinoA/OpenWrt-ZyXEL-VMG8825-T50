include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/version.mk

PKG_NAME:=u-boot-2016
PKG_RELEASE:=1

#PKG_SOURCE:=$(PKG_NAME).tar.bz2
#PKG_SOURCE_URL:=@ZyXEL_SITE/WIFI_DL

CURR_DIR:= $(shell pwd)
LOCAL_SRC:=$(CURR_DIR)/src

PKG_BUILD_DIR:=$(KERNEL_BUILD_DIR)/$(PKG_NAME)-$(BUILD_VARIANT)/$(PKG_NAME)
CONFIG_NAME=$(shell echo $(BUILD_VARIANT) | sed 's/.*-//')
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
include $(INCLUDE_DIR)/local-development.mk
endif
include $(INCLUDE_DIR)/package.mk

ifneq ($(CONFIG_TARGET_ar71xx),)
KCPPFLAGS+=$(foreach var,$(strip $(shell cat ./configs/$(shell echo $(BUILD_VARIANT) | sed 's/-qca95[0-9]x//')-$(BOARD)$(if $(SUBTARGET),_$(SUBTARGET)).mk)), -D${var})
endif

define Package/uboot-2016-ipq806x
  SECTION:=boot
  CATEGORY:=Boot Loaders
  DEPENDS:=@TARGET_ipq806x||TARGET_ipq
  TITLE:=U-boot for IPQ806x based platforms
  URL:=http://www.denx.de/wiki/U-Boot
  VARIANT:=ipq806x
endef

define Package/uboot-2016-ipq806x_standard
  SECTION:=boot
  CATEGORY:=Boot Loaders
  DEPENDS:=@TARGET_ipq806x||TARGET_ipq
  TITLE:=U-boot(Standard Variant) for IPQ806x based platforms
  URL:=http://www.denx.de/wiki/U-Boot
  VARIANT:=ipq806x_standard
endef

define Package/uboot-2016-ipq807x
  SECTION:=boot
  CATEGORY:=Boot Loaders
  DEPENDS:=@TARGET_ipq806x||TARGET_ipq807x||TARGET_ipq
  TITLE:=U-boot for IPQ807x based platforms
  URL:=http://www.denx.de/wiki/U-Boot
  VARIANT:=ipq807x
endef

define Package/uboot-2016-ipq40xx
  SECTION:=boot
  CATEGORY:=Boot Loaders
  DEPENDS:=@TARGET_ipq806x||TARGET_ipq
  TITLE:=U-boot for IPQ40xx based platforms
  URL:=http://www.denx.de/wiki/U-Boot
  VARIANT:=ipq40xx
endef

define Package/uboot-2016-ipq40xx_standard
  SECTION:=boot
  CATEGORY:=Boot Loaders
  DEPENDS:=@TARGET_ipq806x||TARGET_ipq
  TITLE:=U-boot(Standard Variant) for IPQ40xx based platforms
  URL:=http://www.denx.de/wiki/U-Boot
  VARIANT:=ipq40xx_standard
endef

define Package/uboot-2016-ar71xx/common
 define Package/uboot-2016-ar71xx-$(1)
  SECTION:=boot
  CATEGORY:=Boot Loaders
  TITLE:=U-boot for $(1) platform
  DEPENDS:=@TARGET_ar71xx
  URL:=http://www.denx.de/wiki/U-Boot
  VARIANT:=$(1)-$(2)
 endef
endef

define Package/uboot-2016-ar71xx/nor
 $(call Package/uboot-2016-ar71xx/common,$(1),$(2))

 define Package/uboot-2016-ar71xx-$(1)/install
	$(CP) $(PKG_BUILD_DIR)/u-boot $(BIN_DIR)/openwrt-ar71xx-u-boot-$(1).elf
	$(CP) $(PKG_BUILD_DIR)/u-boot.bin $(BIN_DIR)/openwrt-ar71xx-u-boot-$(1).bin
 endef
 $$(eval $$(call BuildPackage,uboot-2016-ar71xx-$(1)))
endef


define Build/Configure
	$(MAKE) -C $(PKG_BUILD_DIR) $(CONFIG_NAME)_defconfig
endef

define Build/Compile
	VERSION_CODE='$(VERSION_NICK) $(VERSION_NUMBER)' \
	REVISION='$(REVISION)' \
	$(MAKE) -C $(PKG_BUILD_DIR) HOSTSTRIP=true CROSS_COMPILE=$(TARGET_CROSS) \
		TARGETCC=$(TARGET_CC) \
		KCPPFLAGS="$(KCPPFLAGS)" \
		DTC=${LINUX_DIR}/scripts/dtc/dtc \
		all
endef

define Package/uboot-2016-ipq806x/install
	$(INSTALL_DIR) $(1)
	$(CP) $(PKG_BUILD_DIR)/u-boot $(BIN_DIR)/openwrt-ipq806x-u-boot-2016.elf
	$(CP) $(PKG_BUILD_DIR)/u-boot.bin $(BIN_DIR)/openwrt-ipq806x-u-boot-2016.img
	$(CP) $(PKG_BUILD_DIR)/u-boot.mbn $(BIN_DIR)/openwrt-ipq806x-u-boot-2016.mbn
endef

define Package/uboot-2016-ipq806x_standard/install
	$(INSTALL_DIR) $(1)
	$(CP) $(PKG_BUILD_DIR)/u-boot $(BIN_DIR)/openwrt-ipq806x_standard-u-boot-2016.elf
	$(CP) $(PKG_BUILD_DIR)/u-boot.bin $(BIN_DIR)/openwrt-ipq806x_standard-u-boot-2016.img
	$(CP) $(PKG_BUILD_DIR)/u-boot.mbn $(BIN_DIR)/openwrt-ipq806x_standard-u-boot-2016.mbn
endef

define Package/uboot-2016-ipq807x/install
	$(INSTALL_DIR) $(1)
	$(CP) $(PKG_BUILD_DIR)/u-boot $(BIN_DIR)/openwrt-ipq807x-u-boot.elf
	$(CP) $(PKG_BUILD_DIR)/u-boot $(BIN_DIR)/openwrt-ipq807x-u-boot-stripped.elf
	$(STRIP) $(BIN_DIR)/openwrt-ipq807x-u-boot-stripped.elf
	$(CP) $(PKG_BUILD_DIR)/u-boot.bin $(BIN_DIR)/openwrt-ipq807x-u-boot.img
endef

define Package/uboot-2016-ipq40xx/install
	$(INSTALL_DIR) $(1)
	$(CP) $(PKG_BUILD_DIR)/u-boot $(BIN_DIR)/openwrt-ipq40xx-u-boot-2016.elf
	$(CP) $(PKG_BUILD_DIR)/u-boot $(BIN_DIR)/openwrt-ipq40xx-u-boot-2016-stripped.elf
	$(STRIP) $(BIN_DIR)/openwrt-ipq40xx-u-boot-2016-stripped.elf
	$(CP) $(PKG_BUILD_DIR)/u-boot.bin $(BIN_DIR)/openwrt-ipq40xx-u-boot-2016.img
endef

define Package/uboot-2016-ipq40xx_standard/install
	$(INSTALL_DIR) $(1)
	$(CP) $(PKG_BUILD_DIR)/u-boot $(BIN_DIR)/openwrt-ipq40xx_standard-u-boot-2016.elf
	$(CP) $(PKG_BUILD_DIR)/u-boot $(BIN_DIR)/openwrt-ipq40xx_standard-u-boot-2016-stripped.elf
	$(STRIP) $(BIN_DIR)/openwrt-$(BUILD_VARIANT)-u-boot-2016-stripped.elf
	$(CP) $(PKG_BUILD_DIR)/u-boot.bin $(BIN_DIR)/openwrt-ipq40xx_standard-u-boot-2016.img
endef

$(eval $(call BuildPackage,uboot-2016-ipq807x))
$(eval $(call BuildPackage,uboot-2016-ipq40xx))
$(eval $(call BuildPackage,uboot-2016-ipq40xx_standard))
$(eval $(call BuildPackage,uboot-2016-ipq806x))
$(eval $(call BuildPackage,uboot-2016-ipq806x_standard))
$(eval $(call Package/uboot-2016-ar71xx/nor,ap147-8M,qca953x))
$(eval $(call Package/uboot-2016-ar71xx/nor,ap147-16M,qca953x))
$(eval $(call Package/uboot-2016-ar71xx/nor,ap135,qca955x))
$(eval $(call Package/uboot-2016-ar71xx/nor,ap152-8M,qca956x))
$(eval $(call Package/uboot-2016-ar71xx/nor,ap152-16M,qca956x))
$(eval $(call Package/uboot-2016-ar71xx/nor,ap151-8M,qca956x))
$(eval $(call Package/uboot-2016-ar71xx/nor,ap151-16M,qca956x))

