/*
 * (C) Copyright Mindspeed Technologies Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
#include <common.h>
flash_info_t flash_info[CONFIG_SYS_MAX_FLASH_BANKS];

#ifdef CONFIG_FLASH_CFI_DRIVER

#define FLASH_MAN_CFI		0x01000000

#ifdef CONFIG_SYS_FLASH_PROTECTION
extern int cfi_flash_real_protect(flash_info_t *info, long sector, int prot);
#endif

extern int cfi_flash_erase(flash_info_t * info, int s_first, int s_last);
extern int cfi_write_buff (flash_info_t * info, uchar * src, ulong addr, ulong cnt);
extern void cfi_flash_print_info(flash_info_t *info);
extern unsigned long cfi_flash_init(void);
#endif


#ifdef CFG_FLASH_AM040_DRIVER
#ifdef CONFIG_SYS_FLASH_PROTECTION
int am29lv040b_flash_real_protect(flash_info_t *info, long sector, int prot);
#endif
int am29lv040b_flash_erase(flash_info_t * info, int s_first, int s_last);
int am29lv040b_write_buff(flash_info_t * info, uchar * src, ulong addr, ulong cnt);
ulong am29lv040b_flash_init(flash_info_t * info);
#endif

#ifdef CFG_FLASH_AMLV640U_DRIVER
int amlv640u_flash_erase (flash_info_t *info, int s_first, int s_last);
int amlv640u_write_buff (flash_info_t *info, uchar *src, ulong addr, ulong cnt);
ulong amlv640u_flash_init(flash_info_t * info);
#endif

int flash_erase(flash_info_t * info, int s_first, int s_last)
{
	if (info->flash_id == FLASH_UNKNOWN) {
		printf ("missing or unknown FLASH type\n");
		return ERR_UNKNOWN_FLASH_TYPE;
	}

	if ((s_first < 0) || (s_first > s_last) || (s_last >= info->sector_count)) {
		return ERR_INVAL;
	}

#ifdef CONFIG_FLASH_CFI_DRIVER
	if (info->flash_id == FLASH_MAN_CFI)
		return cfi_flash_erase(info, s_first, s_last);
#endif

#ifdef CFG_FLASH_AM040_DRIVER
	if ((info->flash_id & FLASH_TYPEMASK) == FLASH_AM040)
		return am29lv040b_flash_erase(info, s_first, s_last);
#endif

#ifdef CFG_FLASH_AMLV640U_DRIVER
	if ((info->flash_id & FLASH_TYPEMASK) == FLASH_AMLV640U)
		return amlv640u_flash_erase(info, s_first, s_last);
#endif

	return ERR_UNKNOWN_FLASH_TYPE;
}

#ifdef CONFIG_SYS_FLASH_PROTECTION
int flash_real_protect(flash_info_t *info, long sector, int prot)
{
	if (info->flash_id == FLASH_UNKNOWN) {
		printf ("missing or unknown FLASH type\n");
		return ERR_UNKNOWN_FLASH_TYPE;
	}

	if ((sector < 0) || (sector >= info->sector_count)) {
		return ERR_INVAL;
	}

#ifdef CONFIG_FLASH_CFI_DRIVER
	if (info->flash_id == FLASH_MAN_CFI)
		return cfi_flash_real_protect(info, sector, prot);
#endif

#ifdef CFG_FLASH_AM040_DRIVER
	if ((info->flash_id & FLASH_TYPEMASK) == FLASH_AM040)
		return am29lv040b_flash_real_protect(info, sector, prot);
#endif

#ifdef CFG_FLASH_AMLV640U_DRIVER
	if ((info->flash_id & FLASH_TYPEMASK) == FLASH_AMLV640U)
		return amlv640u_flash_real_protect(info, sector, prot);
#endif

	return ERR_UNKNOWN_FLASH_TYPE;
}
#endif

int write_buff(flash_info_t *info, uchar *src, ulong addr, ulong cnt)
{
	if (info->flash_id == FLASH_UNKNOWN) {
		printf ("missing or unknown FLASH type\n");
		return ERR_UNKNOWN_FLASH_TYPE;
	}

#ifdef CONFIG_FLASH_CFI_DRIVER
	if (info->flash_id == FLASH_MAN_CFI)
		return cfi_write_buff(info, src, addr, cnt);
#endif

#ifdef CFG_FLASH_AM040_DRIVER
	if ((info->flash_id & FLASH_TYPEMASK) == FLASH_AM040)
		return am29lv040b_write_buff(info, src, addr, cnt);
#endif

#ifdef CFG_FLASH_AMLV640U_DRIVER
	if ((info->flash_id & FLASH_TYPEMASK) == FLASH_AMLV640U)
		return amlv640u_write_buff(info, src, addr, cnt);
#endif

	return ERR_UNKNOWN_FLASH_TYPE;
}


/*-----------------------------------------------------------------------
 */
void flash_print_info(flash_info_t *info)
{
	int i;

	if (info->flash_id == FLASH_UNKNOWN) {
		printf ("missing or unknown FLASH type\n");
		return;
	}

#ifdef CONFIG_FLASH_CFI_DRIVER
	if (info->flash_id == FLASH_MAN_CFI) {
		cfi_flash_print_info(info);
		return;
	}
#endif

	switch (info->flash_id & FLASH_VENDMASK) {
	case FLASH_MAN_AMD:
		printf ("AMD ");
		break;

	case FLASH_MAN_FUJ:
		printf ("FUJITSU ");
		break;

	/* Add other supported flash vendors here */

	default:
		printf ("Unknown Vendor ");
		return;
		break;
	}

	switch (info->flash_id & FLASH_TYPEMASK) {
	case FLASH_AM040:
		printf("AM29LV040B (4Mbit, uniform sector size)\n");
		break;

	case FLASH_AMLV640U:
		printf ("AM29LV640ML/S29GL064M (64Mbit, uniform sector size)\n");
		break;

	default:
		printf ("Unknown Chip Type\n");
		return;
		break;
	}

	if ((info->size >> 20) > 0)
		printf ("  Size: %ld MiB in %d Sectors\n", info->size >> 20, info->sector_count);
	else
		printf ("  Size: %ld KiB in %d Sectors\n", info->size >> 10, info->sector_count);

	printf ("  Sector Start Addresses:");
	for (i = 0; i < info->sector_count; ++i) {
		if ((i % 5) == 0)
			printf ("\n   ");

		printf (" %08lX%s",
			info->start[i],
			info->protect[i] ? " (RO)" : "     "
		);
	}

	printf ("\n");

	return;
}

unsigned long flash_init(void)
{
	unsigned long size = 0;
	int i;

	printf("Comcerto Flash Subsystem Initialization\n");

	/* Init: no Flashes known */
	for (i = 0; i < CONFIG_SYS_MAX_FLASH_BANKS; i++) {
		flash_info[i].flash_id = FLASH_UNKNOWN;
	}

#ifdef CONFIG_FLASH_CFI_DRIVER
	/* CFI compatible flash detection */
	/* must be done first */
	size += cfi_flash_init();
#endif

#ifdef CFG_FLASH_AM040_DRIVER
	size += am29lv040b_flash_init(flash_info);
#endif

#ifdef CFG_FLASH_AMLV640U_DRIVER
	size += amlv640u_flash_init(flash_info);
#endif

	return size;
}
