#/******************************************************************************/
#/*
#*  Copyright (C) 2012 ZyXEL Communications, Corp.
#*  All Rights Reserved.
#*
#* ZyXEL Confidential; Need to Know only.
#* Protected as an unpublished work.
#*
#* The computer program listings, specifications and documentation
#* herein are the property of ZyXEL Communications, Corp. and
#* shall not be reproduced, copied, disclosed, or used in whole or
#* in part for any reason without the prior express written permission of
#* ZyXEL Communications, Corp.
#*/
#/******************************************************************************/

BUILD_APPS = librest-c.so 

CFLAGS += -I$(USRINCDIR) -std=gnu99 -Wall -g -fno-omit-frame-pointer -O2
CFLAGS += -Werror
SRC_OBJS:= librest-c.c

LDFLAGS += -lcurl -L$(USRLIBDIR) -ljson-c

all: $(BUILD_APPS) rest-c

clone:
	echo Building directories...
	mkdir -pv $(PKG_BUILD_DIR)
	ls -al 
	cp -rf . $(PKG_BUILD_DIR)

.c.o:
	@$(CC) $(CFLAGS) -fPIC -Wall -std=gnu99 -c $< -o $@
	
$(BUILD_APPS): $(SRC_OBJS)
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -fPIC -shared -o $@

rest-c: rest-c.c 
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -L. -lrest-c -o $@

clean:
	@rm -f *.o *.so rest-c
	@echo "==> clean"

