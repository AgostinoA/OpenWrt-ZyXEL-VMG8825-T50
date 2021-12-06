GCC_VARIANT:=initial

include ../common.mk

ifeq ($(CONFIG_GCC_VERSION_5_5_0),y)
GCC_CONFIGURE += \
		--enable-shared \
		--enable-shared \
		--disable-static \
		--disable-gtk-doc \
		--disable-gtk-doc-html \
		--disable-doc \
		--disable-docs \
		--disable-documentation \
		--disable-debug \
		--with-xmlto=no \
		--with-fop=no \
		--disable-__cxa_atexit \
		--enable-threads
endif

GCC_CONFIGURE += \
	--with-newlib \
	--with-sysroot=$(TOOLCHAIN_DIR) \
	--enable-languages=c \
	--disable-shared \
	--disable-threads \

ifeq ($(CONFIG_GCC_VERSION_5_3_0)$(CONFIG_GCC_VERSION_5_5_0),y)
ifeq ("_$(call qstrip,$(CONFIG_arm)$(CONFIG_aarch64))_$(CONFIG_TARGET_brcm963xx)_","_y_y_")
GCC_CONFIGURE += \
		--disable-dependency-tracking \
		--without-headers \
		--disable-nls \
		--disable-largefile
endif
endif

define Host/Compile
	$(CP) $(BUILD_DIR_TOOLCHAIN)/linux-dev/* $(BUILD_DIR_TOOLCHAIN)/$(LIBC)-dev/
	+$(GCC_MAKE) $(HOST_JOBS) -C $(GCC_BUILD_DIR) \
		all-build-libiberty \
		all-gcc \
		all-target-libgcc
endef

define Host/Install
	$(GCC_MAKE) -C $(GCC_BUILD_DIR) \
		prefix="$(TOOLCHAIN_DIR)/initial" \
		install-gcc \
		install-target-libgcc

	# XXX: glibc insists on linking against libgcc_eh
	( cd $(TOOLCHAIN_DIR)/initial/lib/gcc/$(REAL_GNU_TARGET_NAME)/$(PKG_VERSION) ; \
		[ -e libgcc_eh.a ] || ln -sf libgcc.a libgcc_eh.a ; \
		cp libgcc.a libgcc_initial.a; \
	)

	$(call FixupLibdir,$(TOOLCHAIN_DIR)/initial)
	$$(call file_copy,$(TOOLCHAIN_DIR)/initial/.,$(TOOLCHAIN_DIR)/)
endef

$(eval $(call HostBuild))
