#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=samba

ifeq ($(CONFIG_ZYXEL_SUPPORT_SMB2),y)
PKG_VERSION:=3.6.25
PKG_RELEASE:=10
else
PKG_VERSION:=3.0.37
PKG_RELEASE:=1
endif

PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/network/services

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_INSTALL:=1
PATCH_DIR=patches_${PKG_VERSION}

include $(INCLUDE_DIR)/package.mk

ifeq ($(CONFIG_ZYXEL_SUPPORT_SMB2),y)
MAKE_PATH:=source3
CONFIGURE_PATH:=source3
else
MAKE_PATH:=source
CONFIGURE_PATH:=source
endif
PKG_BUILD_BIN:=$(PKG_BUILD_DIR)/$(MAKE_PATH)/bin
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
PATH_DIR=etc
else
PATH_DIR=var
endif
define Package/samba
  SECTION:=net
  CATEGORY:=Network
  TITLE:=samba - NetBIOS/SMB implementation
#  URL:=
endef

define Package/samba/description
	The Samba software suite is a collection of programs that implements the
	SMB protocol for unix systems, allowing you to serve files and printers to
	Windows, NT, OS/2 and DOS clients. This protocol is sometimes also referred
	to as the LanManager or Netbios protocol.
endef

#Disable Dependencies Check
define CheckDependencies
endef

ifeq ($(CONFIG_ZYXEL_SUPPORT_SMB2),y)
CONFIGURE_VARS += \
	ac_cv_lib_attr_getxattr=no \
	ac_cv_search_getxattr=no \
	ac_cv_file__proc_sys_kernel_core_pattern=yes \
	libreplace_cv_HAVE_C99_VSNPRINTF=yes \
	libreplace_cv_HAVE_GETADDRINFO=yes \
	libreplace_cv_HAVE_IFACE_IFCONF=yes \
	LINUX_LFS_SUPPORT=yes \
	samba_cv_CC_NEGATIVE_ENUM_VALUES=yes \
	samba_cv_HAVE_GETTIMEOFDAY_TZ=yes \
	samba_cv_HAVE_IFACE_IFCONF=yes \
	samba_cv_HAVE_KERNEL_OPLOCKS_LINUX=yes \
	samba_cv_HAVE_SECURE_MKSTEMP=yes \
	samba_cv_HAVE_WRFILE_KEYTAB=no \
	samba_cv_USE_SETREUID=yes \
	samba_cv_USE_SETRESUID=yes \
	samba_cv_have_setreuid=yes \
	samba_cv_have_setresuid=yes \
	ac_cv_header_libunwind_h=no \
	ac_cv_header_zlib_h=no \
	samba_cv_zlib_1_2_3=no \
	ac_cv_path_PYTHON="" \
	ac_cv_path_PYTHON_CONFIG=""

CONFIGURE_ARGS += \
	--exec-prefix=/usr \
	--prefix=/ \
	--disable-avahi \
	--disable-cups \
	--disable-external-libtalloc \
	--disable-pie \
	--disable-relro \
	--disable-static \
	--disable-swat \
	--disable-shared-libs \
	--with-libiconv="$(ICONV_PREFIX)" \
	--with-codepagedir=/var/samba \
	--with-configdir=/var/samba \
	--with-included-iniparser \
	--with-included-popt \
	--with-lockdir=/var/lock \
	--with-logfilebase=/var/log \
	--with-nmbdsocketdir=/var/samba/nmbd \
	--with-piddir=/var/run \
	--with-privatedir=/var/samba \
	--with-sendfile-support \
	--without-acl-support \
	--without-cluster-support \
	--without-ads \
	--without-krb5 \
	--without-ldap \
	--without-pam \
	--without-winbind \
	--without-libtdb \
	--without-libtalloc \
	--without-libnetapi \
	--without-libsmbclient \
	--without-libsmbsharemodes \
	--without-libtevent \
	--without-libaddns
else
CONFIGURE_VARS+= \
	SMB_BUILD_CC_NEGATIVE_ENUM_VALUES=yes \
	samba_cv_USE_SETEUID=no \
	samba_cv_have_setresuid=yes \
	samba_cv_USE_SETRESUID=yes \
	samba_cv_HAVE_C99_VSNPRINTF=yes \
	samba_cv_have_longlong=yes \
	ac_cv_type_long_long=yes \
	samba_cv_HAVE_KERNEL_OPLOCKS_LINUX=yes
ifeq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
CONFIGURE_ARGS+= \
	--with-configdir=/etc/samba \
	--with-codepagedir=/etc/samba \
	--with-included-iniparser \
	--with-included-popt \
	--with-lockdir=/var/lock \
	--with-logfilebase=/var/log \
	--with-nmbdsocketdir=/var/nmbd \
	--with-piddir=/var/run \
	--with-privatedir=/etc/samba \
	--with-aio-support \
	--with-sendfile-support \
	--with-sys-quotas=no \
	--enable-cups=no \
	--enable-iprint=no \
	--enable-largefile \
	--without-krb5 \
	--without-ads \
	--without-ldap \
	--without-pam \
	--without-winbind \
	--without-libtdb \
	--without-libtalloc \
	--without-libnetapi \
	--without-libsmbclient \
	--without-libsmbsharemodes \
	--without-libaddns 
else	
CONFIGURE_ARGS+= \
	--with-configdir=/etc/samba \
	--with-codepagedir=/var/samba \
	--with-configdir=/var/samba \
	--with-included-iniparser \
	--with-included-popt \
	--with-lockdir=/var/lock \
	--with-logfilebase=/var/log \
	--with-nmbdsocketdir=/var/samba/nmbd \
	--with-piddir=/var/run \
	--with-privatedir=/var/samba \
	--with-aio-support \
	--with-sendfile-support \
	--with-sys-quotas=no \
	--enable-cups=no \
	--enable-iprint=no \
	--enable-largefile \
	--without-krb5 \
	--without-ads \
	--without-ldap \
	--without-pam \
	--without-winbind \
	--without-libtdb \
	--without-libtalloc \
	--without-libnetapi \
	--without-libsmbclient \
	--without-libsmbsharemodes \
	--without-libaddns
endif
endif
ZCFLAGS += -DZYXEL_PATCH
	
TARGET_CFLAGS += -DAVM_SMALLER -DAVM_NO_PRINTING -DMAX_DEBUG_LEVEL=2 $(ZCFLAGS)
	
MAKE_FLAGS += OWRT_NO_PRINTING=1 OWRT_SMALLER=1

# define Build/Compile
	# $(MAKE) -C $(PKG_BUILD_DIR)/source
# endef

define Package/samba/install
	$(INSTALL_DIR) $(1)/$(PATH_DIR)/samba
ifeq ($(CONFIG_ZYXEL_SUPPORT_SMB2),y)
	$(INSTALL_DIR) $(1)/var/samba/nmbd
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/codepages/lowcase.dat $(1)/var/samba
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/codepages/upcase.dat $(1)/var/samba
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/codepages/valid.dat $(1)/var/samba
else
ifneq ("$(strip ${ZCFG_PLATFORM})","QUALCOMM")
	$(INSTALL_DIR) $(1)/$(PATH_DIR)/samba/nmbd
endif
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/$(MAKE_PATH)/codepages/lowcase.dat $(1)/$(PATH_DIR)/samba
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/$(MAKE_PATH)/codepages/upcase.dat $(1)/$(PATH_DIR)/samba
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/$(MAKE_PATH)/codepages/valid.dat $(1)/$(PATH_DIR)/samba
endif
	$(INSTALL_DIR) $(1)/usr/lib
#	$(INSTALL_BIN) $(PKG_BUILD_BIN)/libtalloc.so.1 $(1)/usr/lib
#	$(INSTALL_BIN) $(PKG_BUILD_BIN)/libtdb.so.1 $(1)/usr/lib
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_BIN)/smbpasswd $(1)/usr/sbin/
	$(INSTALL_BIN) $(PKG_BUILD_BIN)/smbd $(1)/usr/sbin/
	$(STRIP) $(1)/usr/sbin/smbpasswd
	$(STRIP) $(1)/usr/sbin/smbd
endef

$(eval $(call BuildPackage,samba))