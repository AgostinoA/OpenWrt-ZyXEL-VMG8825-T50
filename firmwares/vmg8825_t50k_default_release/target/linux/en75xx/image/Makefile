# 
# Copyright (C) 2006-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/image.mk

ifeq ($(CONFIG_TARGET_ROOTFS_INITRAMFS),y)
VMLINUX_ELF_FILE=$(IMG_PREFIX)-vmlinux-initramfs.elf
VMLINUX_BIN_FILE=$(IMG_PREFIX)-vmlinux-initramfs.bin
define Image/BuildKernel
endef
else
VMLINUX_ELF_FILE=$(IMG_PREFIX)-vmlinux.elf
VMLINUX_BIN_FILE=$(IMG_PREFIX)-vmlinux.bin
endif

ifeq "$(CONFIG_KERNEL_COMPRESS_MODE_NONE)" "y"
	KERNEL_COMPRESS_MODE=none
	COMPRESSION_SUFFIX=
  define compressKernel
	echo "Uncompressed kernel image"
  endef
endif

ifeq "$(CONFIG_KERNEL_COMPRESS_MODE_LZMA)" "y"
	KERNEL_COMPRESS_MODE=lzma
	COMPRESSION_SUFFIX=.lzma
  define compressKernel
	$(STAGING_DIR_HOST)/bin/lzma e $(BIN_DIR)/$(1) $(BIN_DIR)/$(1)$(COMPRESSION_SUFFIX) -lc0 -lp2
  endef
endif

ifeq "$(CONFIG_KERNEL_COMPRESS_MODE_GZIP)" "y"
	KERNEL_COMPRESS_MODE=gzip
	COMPRESSION_SUFFIX=.gz
  define compressKernel
	gzip -9c $(BIN_DIR)/$(1) > $(BIN_DIR)/$(1)$(COMPRESSION_SUFFIX)
  endef
endif

# Get load address from kernel image(ELF)
define getLoadAddress
0x`readelf -a $(BIN_DIR)/$(VMLINUX_ELF_FILE)|grep "\[ 1\]"|tr -s ' '|cut -d' ' -f6`
endef
# Get entry point from kernel image(ELF)
define getEntryPoint
`readelf -a $(BIN_DIR)/$(VMLINUX_ELF_FILE)|grep "Entry point address"|cut -d":" -f2`
endef 

# create uImage
# Usage: mkKernelImage
define mkKerneluImage
	$(STAGING_DIR_HOST)/bin/mkimage -A mips -O linux -T kernel -C $(KERNEL_COMPRESS_MODE) \
		-a $(call getLoadAddress) \
		-e $(call getEntryPoint) \
		-n 'Linux Kernel Image' \
		-d $(BIN_DIR)/$(VMLINUX_BIN_FILE)$(COMPRESSION_SUFFIX) \
		$(BIN_DIR)/$(VMLINUX_BIN_FILE)$(COMPRESSION_SUFFIX).uImage
endef

define Image/Prepare
	$(CP) $(KDIR)/vmlinux.elf $(BIN_DIR)/$(VMLINUX_ELF_FILE)
	$(CP) $(KDIR)/vmlinux $(BIN_DIR)/$(VMLINUX_BIN_FILE)
	$(call compressKernel,$(VMLINUX_BIN_FILE))
	$(call mkKerneluImage)
endef

# __ZYXEL__start,
# Replace 'CONFIG_ECONETSDK_' for menuconfig only supports a single prompt problem.
PLATFORM_PREFIX=CONFIG_$(call qstrip, $(CONFIG_CUSTOM_SDK_PREFIX))
# __ZYXEL__end

define Image/mkfs/prepare
	rm -fr $(TARGET_DIR)/etc/modules-boot.d/ $(TARGET_DIR)/etc/modules.d/ $(TARGET_DIR)/overlay

	#no need to touch these files, they should be created at run time.
	#touch $(TARGET_DIR)/var/modules.dep
	#touch $(TARGET_DIR)/var/modules.symbols
	#touch $(TARGET_DIR)/var/modules.alias
	ln -fs /var/modules.dep $(TARGET_DIR)/lib/modules/$(LINUX_VERSION)/
	ln -fs /var/modules.symbols $(TARGET_DIR)/lib/modules/$(LINUX_VERSION)/
	ln -fs /var/modules.alias $(TARGET_DIR)/lib/modules/$(LINUX_VERSION)/

	@if [ -d $(TARGET_DIR)/etc ]; then \
	$(CP) $(TARGET_DIR)/etc $(TARGET_DIR)/usr/; \
	rm -fr $(TARGET_DIR)/etc; \
	ln -sf /tmp/etc $(TARGET_DIR)/etc; \
	fi
	
	@if [ -d $(TARGET_DIR)/var ]; then \
	$(CP) $(TARGET_DIR)/var $(TARGET_DIR)/usr/; \
	rm -fr $(TARGET_DIR)/var; \
	ln -sf /tmp/var $(TARGET_DIR)/var; \
	fi
	
	ln -sf /tmp/var/home $(TARGET_DIR)/home; \
	
	ln -sf /data/cferam $(TARGET_DIR)/cferam; \

	$(CP) `find $(LINUX_DIR) -name *.ko` $(TARGET_DIR)/$(TARGET_MODULES_DIR)/
	$(INSTALL_DIR) $(TARGET_DIR)/userfs
	$(SCRIPT_DIR)/extractVendorSDKCfg.sh $(PLATFORM_PREFIX) $(TOPDIR)/.config \
		$(TARGET_DIR)/userfs/profile.cfg

	$(call Image/mkfs/prepare/default)
endef

# create image for Econet format
define getImgSize
`stat -c%s $(1)`
endef
# flag TCSUPPORT_FREE_BOOTBASE & START_ADDR are export from target/linux/en75xx/$(CONFIG_TC_RULE_MAK)
# check file 'target/linux/en75xx/en7512/target.mk'
ifneq ($(TCSUPPORT_FREE_BOOTBASE),)
	TRX_IMG_OPT=-u $(START_ADDR)
endif
KERNEL_IMG=$(BIN_DIR)/$(VMLINUX_BIN_FILE)$(COMPRESSION_SUFFIX)
ROOTFS_IMG=$(KDIR)/root.squashfs
ifneq ($(ZYXEL_SUPPORT_DEFCFG),)
DEFCFG_IMG=$(PLATFORM_DIR)/$(SUBTARGET)/defconfig/$(ZYXEL_DEFCFG_FILENAME)
endif
#KERNEL_IMG=/home/chlee/workspace/vendor/mtk/tclinux_phoenix/apps/private/tclinux_builder/linux.7z
#ROOTFS_IMG=/home/chlee/workspace/vendor/mtk/tclinux_phoenix/apps/private/tclinux_builder/rootfs
define Image/Build/trx_image
	cat $(KERNEL_IMG) $(ROOTFS_IMG) > $(BIN_DIR)/tclinux
	$(STAGING_DIR_HOST)/bin/econet-trx -k $(call getImgSize,$(KERNEL_IMG)) \
		-r $(call getImgSize,$(ROOTFS_IMG)) $(TRX_IMG_OPT) \
		-f $(BIN_DIR)/tclinux -o $(BIN_DIR)/tclinux.bin \
		-c $(STAGING_DIR_HOST)/bin/econet-trx_config
	rm -f $(BIN_DIR)/tclinux
endef

define Image/Build/zy_trx_image
	cat $(KERNEL_IMG) $(ROOTFS_IMG) $(DEFCFG_IMG) > $(BIN_DIR)/tclinux
	$(STAGING_DIR_HOST)/bin/econet-trx \
		-T ZYXEL \
		-K $(KERNEL_IMG) \
		-R $(ROOTFS_IMG) \
		-C $(DEFCFG_IMG) \
		-P $(TCPLATFORM) \
		-I $(CONFIG_MRD_MODEL_ID) \
		-S $(CONFIG_ZYXEL_FIRMWARE_VERSION) \
		-s $(CONFIG_ZYXEL_FIRMWARE_VERSION) \
		$(TRX_IMG_OPT) \
		-f $(BIN_DIR)/tclinux -o $(BIN_DIR)/ras.bin \
		-c $(STAGING_DIR_HOST)/bin/econet-trx_config
	rm -f $(BIN_DIR)/tclinux
endef

define Image/Build/zy_trx_image_without_defcfg
	cat $(KERNEL_IMG) $(ROOTFS_IMG) > $(BIN_DIR)/tclinux
	$(STAGING_DIR_HOST)/bin/econet-trx \
		-T ZYXEL \
		-K $(KERNEL_IMG) \
		-R $(ROOTFS_IMG) \
		-P $(TCPLATFORM) \
		-I $(CONFIG_MRD_MODEL_ID) \
		-S $(CONFIG_ZYXEL_FIRMWARE_VERSION) \
		-s $(CONFIG_ZYXEL_FIRMWARE_VERSION) \
		$(TRX_IMG_OPT) \
		-f $(BIN_DIR)/tclinux -o $(BIN_DIR)/ras.bin \
		-c $(STAGING_DIR_HOST)/bin/econet-trx_config
	rm -f $(BIN_DIR)/tclinux
endef

define Image/Build/Initramfs
  # all things be done by "Image/Prepare"
endef

define Image/Build/jffs2-64k
	dd if=$(KDIR)/root.jffs2-64k of=$(BIN_DIR)/$(IMG_PREFIX)-jffs2-64k.img bs=64k conv=sync
endef

define Image/Build/jffs2-128k
	dd if=$(KDIR)/root.jffs2-128k of=$(BIN_DIR)/$(IMG_PREFIX)-jffs2-128k.img bs=128k conv=sync
endef

define Image/Build/squashfs
	$(call prepare_generic_squashfs,$(KDIR)/root.squashfs)
	dd if=$(KDIR)/root.squashfs of=$(BIN_DIR)/$(IMG_PREFIX)-squashfs.img bs=128k conv=sync
# Temporarily using original TRX. for original ECONET firmware style.
ifneq ($(ZYXEL),)
ifneq ($(ZYXEL_SUPPORT_DEFCFG),)
	$(call Image/Build/zy_trx_image)
else
	$(call Image/Build/zy_trx_image_without_defcfg)
endif
	$(INSTALL_DIR) $(BIN_DIR)/zyxel
	$(CP) $(BIN_DIR)/ras.bin $(BIN_DIR)/zyxel
ifeq ($(CONFIG_ZYXEL_FW_SIGNATURE_SUPPORT),y)
	$(CP) $(TOPDIR)/$(SUBDIR)/../$(SUBTARGET)/rsa_private.key $(BIN_DIR)/rsa_private.key
	tail -c +373 $(BIN_DIR)/ras.bin > $(BIN_DIR)/ras_tmp.bin
	openssl dgst -sign $(BIN_DIR)/rsa_private.key -sha256 -out $(BIN_DIR)/sha256_rsa_file.sign $(BIN_DIR)/ras_tmp.bin	
	cat $(BIN_DIR)/ras.bin $(BIN_DIR)/sha256_rsa_file.sign > $(BIN_DIR)/ras_signatured.bin
	$(CP) $(BIN_DIR)/ras_signatured.bin $(BIN_DIR)/zyxel
endif
else
	$(call Image/Build/trx_image)
	$(CP) $(BIN_DIR)/tclinux.bin $(BIN_DIR)/zyxel
endif
endef

define Image/Build/merge_firmware

ifneq ($(ZYXEL),)
ifneq ($(ZYXEL_SUPPORT_DEFCFG),)
	$(call Image/Build/zy_trx_image)
else
	$(call Image/Build/zy_trx_image_without_defcfg)
endif
	$(INSTALL_DIR) $(BIN_DIR)/zyxel
	$(CP) $(BIN_DIR)/ras.bin $(BIN_DIR)/zyxel
ifeq ($(CONFIG_ZYXEL_FW_SIGNATURE_SUPPORT),y)
	$(CP) $(TOPDIR)/$(SUBDIR)/../$(SUBTARGET)/rsa_private.key $(BIN_DIR)/rsa_private.key
	tail -c +373 $(BIN_DIR)/ras.bin > $(BIN_DIR)/ras_tmp.bin
	openssl dgst -sign $(BIN_DIR)/rsa_private.key -sha256 -out $(BIN_DIR)/sha256_rsa_file.sign $(BIN_DIR)/ras_tmp.bin	
	cat $(BIN_DIR)/ras.bin $(BIN_DIR)/sha256_rsa_file.sign > $(BIN_DIR)/ras_signatured.bin
	$(CP) $(BIN_DIR)/ras_signatured.bin $(BIN_DIR)/zyxel
endif
else
	$(call Image/Build/trx_image)
endif

endef

define Image/Build
	$(call Image/Build/$(1))
endef

$(eval $(call BuildImage))
