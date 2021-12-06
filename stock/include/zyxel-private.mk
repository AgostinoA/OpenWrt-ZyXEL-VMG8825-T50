#
# Copyright (C) 2006-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
#

ifneq ($(CONFIG_USE_ZYXEL_WIFI_IMAGE_HEADER),)
ifeq "$(PROFILE)" ""
export ZY_IMG_PREFIX=$(shell echo $(SUBTARGET)|tr '[:upper:]' '[:lower:]')
FW_INFO_FILE=$(PLATFORM_SUBDIR)/FWHdr_Info
else
export ZY_IMG_PREFIX=$(shell echo $(PROFILE)|tr '[:upper:]' '[:lower:]')
FW_INFO_FILE=$(PLATFORM_SUBDIR)/fwhdr/FWHdr_Info.$(PROFILE)
endif

#ZYXEL_TOOLS_PRIVATE:=$(TOPDIR)/tools/private/zyxel
#ZYXEL_PACKAGE_PRIVATE:=$(TOPDIR)/package/private/zyxel
ZY_IMG_HDR_EXTEND_SIZE=$(shell grep 'HDR_EXTEND_SIZE' $(FW_INFO_FILE) |cut -f2 -d'=')

##generate firmware image include header info
define zyxel_tools/genImageHeader
	@echo;echo "!!! Generate $(shell grep "OUTPUT_NAME" $(FW_INFO_FILE)| cut -d '=' -f 2| tr -d \") FW !!!";echo
	@(cd $(BIN_DIR)/zyxel; \
	 if [ ! -f $(FW_INFO_FILE) ]; then \
		echo "Not found file '$(FW_INFO_FILE)'"; \
		echo "*** [genImgHdr] Error"; \
		exit 1; \
	 fi; \
	 if [ -f $(BIN_DIR)/zyxel/$(ZY_IMG_PREFIX)-rootfs.jffs2 ]; then \
		$(STAGING_DIR_HOST)/bin/genImgHdr -i $(BIN_DIR)/zyxel/$(ZY_IMG_PREFIX)-rootfs.jffs2 -v $(shell grep "FW_VERSION" $(FW_INFO_FILE)| cut -d '=' -f 2) -p $(shell grep "PROJECT_NAME" $(FW_INFO_FILE)| cut -d '=' -f 2) -s $(if $(ZY_IMG_HDR_EXTEND_SIZE),$(ZY_IMG_HDR_EXTEND_SIZE),0x10000) -o ras.bin.jffs2.header&&cp ras.bin.jffs2.header ras.bin.jffs2&&cat $(BIN_DIR)/zyxel/$(ZY_IMG_PREFIX)-rootfs.jffs2>>ras.bin.jffs2;\
	 fi; \
	 if [ -f $(BIN_DIR)/zyxel/$(ZY_IMG_PREFIX)-rootfs.squashfs ]; then \
		$(STAGING_DIR_HOST)/bin/genImgHdr -i $(BIN_DIR)/zyxel/$(ZY_IMG_PREFIX)-rootfs.squashfs -v $(shell grep "FW_VERSION" $(FW_INFO_FILE)| cut -d '=' -f 2) -p $(shell grep "PROJECT_NAME" $(FW_INFO_FILE)| cut -d '=' -f 2) -s $(if $(ZY_IMG_HDR_EXTEND_SIZE),$(ZY_IMG_HDR_EXTEND_SIZE),0x10000) -o ras.bin.squashfs.header&&cp ras.bin.squashfs.header ras.bin.squashfs&&cat $(BIN_DIR)/zyxel/$(ZY_IMG_PREFIX)-rootfs.squashfs>>ras.bin.squashfs; \
	 fi)
endef
endif
