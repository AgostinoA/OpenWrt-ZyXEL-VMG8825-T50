/*****************************************************************************
 * Copyright (C) ZyXEL Communications, Corp.
 * All Rights Reserved.
 *
 * ZyXEL Confidential; Need to Know only.
 * Protected as an unpublished work.
 *
 * The computer program listings, specifications and documentation
 * herein are the property of ZyXEL Communications, Corp. and
 * shall not be reproduced, copied, disclosed, or used in whole or
 * in part for any reason without the prior express written permission of
 * ZyXEL Communications, Corp.
 *****************************************************************************/
#ifndef _ZLOADER_FLASH_DRIVER_
#define _ZLOADER_FLASH_DRIVER_


extern int zflash_init(void);
extern int zflash_read(unsigned long offs, unsigned long len, char *buf);
extern int zflash_write(unsigned long offs, unsigned long len, char *buf);
extern int zflash_erase(unsigned long offs, unsigned long len);

extern int znand_init(void);
extern int znand_read(unsigned long offs, unsigned long len, char *buf);
extern int znand_write(unsigned long offs, unsigned long len, char *buf);
extern int znand_erase(unsigned long offs, unsigned long len);
#endif

