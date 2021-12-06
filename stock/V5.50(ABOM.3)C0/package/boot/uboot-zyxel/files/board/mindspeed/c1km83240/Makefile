#
# (C) Copyright 2006
# Mindspeed Technologies, Inc. <www.mindspeed.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

include $(TOPDIR)/config.mk
ifneq ($(OBJTREE),$(SRCTREE))
$(shell mkdir -p $(obj)../common)
endif

LIB	= $(obj)lib$(BOARD).a

COBJS-y = board.o reset.o

ifneq ($(CONFIG_SYS_NO_FLASH),y)
COBJS-y += ../common/flash.o ../common/am29lv040b.o ../common/amlv640u.o
endif

ifeq ($(CONFIG_CMD_NAND),y)
COBJS-y += ../common/nand.o
endif

ifeq ($(CONFIG_CMD_I2C),y)
COBJS-y += ../common/i2c.o
endif

COBJS-y += ../common/cmd_bootcomcerto.o
		
SOBJS	:=

gcclibdir := $(shell dirname `$(CC) -print-libgcc-file-name`)

LOAD_ADDR = 0x10400000
LDSCRIPT = $(TOPDIR)/board/$(BOARDDIR)/u-boot.lds

HOST_CFLAGS = -Wall -pedantic -I$(TOPDIR)/include

OBJS    := $(addprefix $(obj),$(COBJS))
SOBJS   := $(addprefix $(obj),$(SOBJS))

SRCS    := $(SOBJS:.o=.S) $(COBJS-y:.o=.c)
OBJS    := $(addprefix $(obj),$(COBJS-y))
SOBJS   := $(addprefix $(obj),$(SOBJS-y))

$(LIB):	$(obj).depend $(OBJS) $(SOBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS) $(SOBJS)

board.o: board.c
	$(CC) $(CFLAGS) -fpic -c -o $@ $<

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
