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

LIB	= lib$(SOC).a

OBJS	= emac.o interrupts.o serial.o bsp.o spi.o
SOBJS	= lowlevel_init.o

all: .depend $(LIB)

$(LIB): $(OBJS) $(SOBJS)
	$(AR) crv $@ $(OBJS) $(SOBJS)

bsp.o: bsp.c
	$(CC) $(CFLAGS) -fpic -c -o $@ $<

interrupts.c: interrupts530.c interrupts800.c

serial.c: serial-16550.c serial530.c


#########################################################################

.depend: Makefile $(SOBJS:.o=.S) $(OBJS:.o=.c)
	$(CC) -M $(CFLAGS) $(SOBJS:.o=.S) $(OBJS:.o=.c) > $@

sinclude .depend

#########################################################################
