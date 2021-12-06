
CC=gcc
CFLAGS += -DMTKSOC
OBJS=trx.o
EXECS=trx

ifeq ($(BOOTROM_LARGE_SIZE), 1)
CFLAGS += -DBOOTROM_LARGE_SIZE
endif

all: trx

.c.o:
	$(CC) -c $(CFLAGS) $<

cc: $(OBJS) $(MIPSLIBS)
	$(CC) -o $@ $(OBJS)

clean:
	rm -f *.o *.a $(EXECS)
