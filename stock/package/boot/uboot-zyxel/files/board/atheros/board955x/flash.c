#include <common.h>
#include <config.h>
#include <asm/types.h>
#include <flash.h>

#ifndef CONFIG_ATH_NAND_BR
/*
 * sets up flash_info and returns size of FLASH (bytes)
 */
unsigned long
flash_get_geom (flash_info_t *flash_info)
{
	int i;

	/* XXX this is hardcoded until we figure out how to read flash id */

	flash_info->flash_id = FLASH_M25P64;
	flash_info->size = CFG_FLASH_SIZE; /* bytes */
	flash_info->sector_count = flash_info->size / CFG_FLASH_SECTOR_SIZE;

	for (i = 0; i < flash_info->sector_count; i++) {
		flash_info->start[i] = CONFIG_SYS_FLASH_BASE +
					(i * CFG_FLASH_SECTOR_SIZE);
		flash_info->protect[i] = 0;
	}

	//printf ("flash size %dMB, sector count = %d\n", \
			FLASH_SIZE, flash_info->sector_count);

	return (flash_info->size);
}
#endif /* CONFIG_ATH_NAND_BR */
