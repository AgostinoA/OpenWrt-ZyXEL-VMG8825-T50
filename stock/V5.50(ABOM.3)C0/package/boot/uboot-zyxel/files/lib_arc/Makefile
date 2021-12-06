#
# Copyright Codito Technologies (www.codito.com)
#
#  lib_arc/Makefile
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

LIB	= $(obj)lib$(ARCH).a

SOBJS-y	=

COBJS-y	= board.o arclinux.o

SRCS	:= $(SOBJS-y:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS-y) $(COBJS-y))

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
