#
#   source code makefile
#
LIB_NAME    = libzcfg_msg
OBJS        = zcfg_msg.o
CURRENT_DIR = $(shell pwd)

LINK_LIB = -lzlog -lzos
#LIBS_PATH =
LDFLAGS += $(LIBS_PATH) $(LINK_LIB)

#CFLAGS += -I$(TOOLCHAIN)/include -I. -std=gnu99
CFLAGS += -I. -std=gnu99

.PHONY : $(LIB_NAME)

all: clean $(LIB_NAME)

.c.o:
	$(CC) $(CFLAGS) -Wall -Werror -fPIC -c $< -o $@

$(LIB_NAME) : $(OBJS)
	$(CC) $(LDFLAGS) -shared -o $(LIB_NAME).so $(OBJS)

clean:
	rm -rf *.o
	rm -rf *.so
