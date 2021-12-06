include $(TOPDIR)/config.mk
ifneq ($(OBJTREE),$(SRCTREE))
$(shell mkdir -p $(obj)../common)
endif

export BOARD_EXTRA_OBJS_tmp =

BOARD_EXTRA_OBJS_tmp += extra.o
ifeq ($(BOOT_FROM_NAND),1)
BOARD_EXTRA_OBJS_tmp += ../common/ath_nand.o ../../../drivers/mtd/nand/nand_ids.o
endif

ifeq ($(COMPRESSED_UBOOT),1)
BOARD_EXTRA_OBJS = $(BOARD_EXTRA_OBJS_tmp)
endif

LIB	= $(obj)lib$(BOARD).a

COBJS-y	=			\
	$(BOARD).o		\
	flash.o			\
	../common/init-955x.o	\
	../common/serial.o	\
	../common/qca-eth-955x.o

COBJS-$(CONFIG_PCI) += ../common/ath_pci.o

#
# The files included in EXTRA_OBJS use some functions that are not
# available in the `bootstrap' portion of tuboot.bin resulting in
# compile/link errors. Hence have them separate (i.e. don't include
# into lib$(BOARD).a and include them only in `u-boot' portion of
# tuboot.bin.
#

ifeq ($(strip $(COMPRESSED_UBOOT)),0) #{
COBJS-y	+= $(BOARD_EXTRA_OBJS_tmp)
else
EXTRA_OBJS = $(BOARD_EXTRA_OBJS_tmp)
endif #}

ifeq ($(ATH_DUAL_FLASH),1)
#COBJS-y	+= ../common/ath_nand.o ../../../drivers/nand/nand_ids.o
COBJS-y	+= ../common/ath_nand.o
endif

ifndef BOOT_FROM_NAND
COBJS-y	+= ../common/ath_flash.o
endif

ifeq ($(ATH_RGMII_CAL),1)
COBJS-y	+= ../common/rgmii-cal-955x.o	
COBJS-y	+= ../common/athrs17_lpbk.o
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

ifeq ($(ETH_CONFIG2), _vir)
COBJS-y	+= ../common/athrs_vir_phy.o
endif

ifeq ($(ETH_CONFIG), _s27)
COBJS-y	+= ../common/athr_s27_phy.o
endif

ifeq ($(ETH_CONFIG2), _ar8033)
COBJS-y	+= ../common/athr_ar8033_phy.o
endif


SOBJS-y	= ../common/955x.o ../common/tap-955x.o

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

