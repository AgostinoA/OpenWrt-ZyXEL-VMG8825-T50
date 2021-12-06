include $(TOPDIR)/config.mk
ifneq ($(OBJTREE),$(SRCTREE))
$(shell mkdir -p $(obj)../common)
endif

LIB	= $(obj)lib$(BOARD).a

COBJS-y	= ../common/ar7240_reset.o $(BOARD).o flash.o
COBJS-$(CONFIG_PCI) += ../common/ar7240_pci.o

ifdef BOOT_FROM_NAND
COBJS-y	+= ../common/ath_nand_flash.o 
else
COBJS-y	+= ../common/ar7240_flash.o
endif

ifeq ($(ETH_CONFIG2), _s17)
COBJS-y	+= ../common/athrs17_phy.o
endif

ifeq ($(ETH_CONFIG), _s17)
COBJS-y	+= ../common/athrs17_phy.o
endif

ifeq ($(ETH_CONFIG2), _s17_hwaccel)
COBJS-y	+= ../common/athrs17_phy.o
endif

ifeq ($(ETH_CONFIG), _s17_hwaccel)
COBJS-y	+= ../common/athrs17_phy.o
endif

ifeq ($(ETH_CONFIG), _s16)
COBJS-y	+= ../common/athrs16_phy.o
endif 

ifeq ($(ETH_CONFIG), _f1e)
COBJS-y	+= ../common/athrsf1_phy.o 
endif

ifeq ($(ETH_CONFIG), _f2e)
COBJS-y	+= ../common/athrsf2_phy.o 
endif

ifeq ($(ETH_CONFIG), _vir)
COBJS-y	+= ../common/athrs_vir_phy.o
endif

ifeq ($(ETH_CONFIG), _s27)
COBJS-y	+= ../common/athr_s27_phy.o
endif

SOBJS-y	= ../common/lowlevel_init_934x.o
SOBJS-y	+= ../common/lowlevel_init_934x-1.1.o

SRCS    := $(SOBJS:.o=.S) $(COBJS-y:.o=.c)
OBJS    := $(addprefix $(obj),$(COBJS-y))
SOBJS   := $(addprefix $(obj),$(SOBJS-y))

$(LIB):	$(obj).depend $(OBJS) $(SOBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS) $(SOBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
