CROSS_COMPILE ?= arc-linux-uclibc-

STANDALONE_LOAD_ADDR ?= 0x80000000 -L -T arc.lds

PLATFORM_CPPFLAGS += -DCONFIG_ARC -D__ARC__

# Quantenna's Ruby
# PLATFORM_CPPFLAGS+= -D__ARC__ -mA7 -mno-sdata -O0 -g -mno-volatile-cache -fomit-frame-pointer
# Enable optimization. Disable cache bypassing for "volatile" references.
# It is bad design to enable cache bypassing for "volatile" references - readX()/writeX() has to be used.
PLATFORM_CPPFLAGS_PATH = -I$(TOPDIR)/quantenna/common -I$(TOPDIR)/quantenna/include/qtn
PLATFORM_CPPFLAGS += -D__ARC__ -mA7 -mno-sdata -Os -g -mvolatile-cache -fomit-frame-pointer $(PLATFORM_CPPFLAGS_PATH)

