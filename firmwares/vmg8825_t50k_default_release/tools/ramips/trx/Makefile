
include $(TOPDIR)/rules.mk

PKG_NAME := ramips-trx

#PKG_VERSION:=$(call qstrip,$(CONFIG_TC_SDK_VERSION))
#PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
#PKG_SOURCE_URL:=@ZyXEL_SITE/private/Trendchip/tools
#DL_DIR:=$(TOPDIR)/dl/private
#PATCH_DIR:=patches-$(PKG_VERSION)

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk

define Host/Compile
	-mkdir -p $(HOST_BUILD_DIR)/tools/trx
	$(CP) ./src/* $(HOST_BUILD_DIR)/tools/trx
	$(MAKE) -C $(HOST_BUILD_DIR)/tools/trx \
                CC="$(HOSTCC)" \
                CXX="$(CXX) $(HOST_STATIC_LINKING)" \
		clean
	CFLAGS="-O2 -Wall" $(MAKE) -C $(HOST_BUILD_DIR)/tools/trx \
	        CC="$(HOSTCC)" \
                CXX="$(CXX) $(HOST_STATIC_LINKING)"
endef

define Host/Install
	$(CP) $(HOST_BUILD_DIR)/tools/trx/trx $(STAGING_DIR_HOST)/bin/$(PKG_NAME)
	$(CP) $(HOST_BUILD_DIR)/tools/trx/trx_config $(STAGING_DIR_HOST)/bin/$(PKG_NAME)_config
	$(INSTALL_DIR) $(STAGING_DIR)/usr/include/trx
	$(CP) $(HOST_BUILD_DIR)/tools/trx/trx.h $(STAGING_DIR)/usr/include/trx/trx.h
	$(CP) $(HOST_BUILD_DIR)/tools/trx/mrd.h $(STAGING_DIR)/usr/include/mrd.h
	$(CP) $(HOST_BUILD_DIR)/tools/trx/mrd_env.h $(STAGING_DIR)/usr/include/mrd_env.h
endef

define Host/Clean
	rm -f $(STAGING_DIR_HOST)/bin/$(PKG_NAME)
	rm -f $(STAGING_DIR)/usr/include/trx/trx.h
	rm -f $(STAGING_DIR)/usr/include/mrd.h
	rm -f $(STAGING_DIR)/usr/include/mrd_env.h

endef

$(eval $(call HostBuild))
