include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(SOC).a

COBJS-y	= meminit.o

ifeq ($(BOARD), ap121)
COBJS-y	+= hornet_serial.o
SOBJS	+= hornet_ddr_init.o
else
COBJS-y	+= ar7240_serial.o
endif

ifneq ($(BUILD_EMU), )
COBJS-y += hornet_ag7240.o
else
ifneq ($(CONFIG_SOC_AG934X),)
COBJS-y += ag934x.o
else
COBJS-y += ag7240.o
endif
endif

SRCS	:= $(SOBJS:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS) $(COBJS-y))

all:	$(obj).depend $(LIB)

$(LIB):	$(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
