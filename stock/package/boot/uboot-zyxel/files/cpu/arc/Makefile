#
#  Copyright Codito Technologies (www.codito.com)
#
#  cpu/arc/Makefile
#
#  Copyright (C) 
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
# 
# Authors : Sandeep Patil (sandeep.patil@codito.com) 
# 			Pradeep Sawlani (pradeep.sawlani@codito.com) 
#


include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(CPU).a

START	= start.o
COBJS	= cpu.o interrupts.o cache.o
SOBJS	=

SRCS    := $(START:.o=.S) $(SOBJS:.o=.S) $(COBJS-y:.o=.c)
OBJS    := $(addprefix $(obj),$(COBJS) $(SOBJS))
START   := $(addprefix $(obj),$(START))


all:	$(obj).depend $(START) $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
