# $Id: //BBN_Linux/Branch/Branch_for_ASB_120_Project_20141009/tclinux_phoenix/apps/public/mtd/Makefile#1 $

#CROSS=mips-linux-gnu-
#CROSS=mips-linux-
#CC=$(CROSS)gcc
#AR=$(CROSS)ar
#LD=$(CROSS)ld
#STRIP=$(CROSS)strip
#RANLIB=$(CROSS)ranlib
#SIZE=$(CROSS)size

#CFLAGS= -DTRENDCHIP
#ifneq ($(strip $(TCSUPPORT_CODE_SHRINK)),)
#CFLAGS += -Os
#endif
#CFLAGS= -mips32r2 -msoft-float -DTRENDCHIP -muclibc
ifneq ($(MTD_CFLAGS),)
    EXTRA_CFLAGS+=$(MTD_CFLAGS)
endif


INCLUDE = -I$(KERNEL_DIR)/include

all: mtd

%.o: %.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $(INCLUDE) -c -o $@ $^

mtd: mtd.o
	$(CC) -o $@ $^
	$(CC) -static -o mtd-static $^
	$(STRIP) $@
	$(STRIP) mtd-static

clean:
	rm -f *.o mtd
