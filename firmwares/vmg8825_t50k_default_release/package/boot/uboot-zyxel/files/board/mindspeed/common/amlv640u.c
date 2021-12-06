/*
 * (C) Copyright 2002
 * Robert Schwebel, Pengutronix, <r.schwebel@pengutronix.de>
 *
 * (C) Copyright 2000-2004
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
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
#include <config.h>
#include <asm/hardware.h>

#ifdef CFG_FLASH_AMLV640U_DRIVER

#define AMLV640U_SECTOR_SIZE	0x00010000      /* 64 KB sectors */
#define AMLV640U_SECTORS	(CFG_FLASH_AMLV640U_SIZE / AMLV640U_SECTOR_SIZE)

#define FTIMEOUT		16000000

/* Functions */
int amlv640u_flash_erase (flash_info_t *info, int s_first, int s_last);
int amlv640u_write_buff (flash_info_t *info, uchar *src, ulong addr, ulong cnt);

#if defined(CFG_FLASH_PROTECTION)
int amlv640u_flash_real_protect(flash_info_t *info, long sector, int prot)
{
	/* do nothing for now */
	return ERR_INVAL;
}
#endif


/*-----------------------------------------------------------------------
 */

int amlv640u_flash_erase (flash_info_t *info, int s_first, int s_last)
{
	volatile u16 *base = (u16 *)info->start[0];
	volatile u16 *addr = base;
	int flag, prot, sect, erased;
	ulong start, now, last;

	prot = 0;
	for (sect = s_first; sect <= s_last; ++sect) {
		if (info->protect[sect]) {
			prot++;
		}
	}

	if (prot) {
		printf ("- Warning: %d protected sectors will not be erased!\n", prot);
	} else {
		printf ("\n");
	}

	erased = 0;

	/* Disable interrupts which might cause a timeout here */
	flag = disable_interrupts();

	base[0x555] = 0xAA;
	base[0x2AA] = 0x55;
	base[0x555] = 0x80;
	base[0x555] = 0xAA;
	base[0x2AA] = 0x55;

	/* Start erase on unprotected sectors */
	for (sect = s_first; sect <= s_last; sect++) {
		if (info->protect[sect] == 0) {	/* not protected */
			addr = (u16 *)info->start[sect];
			addr[0] = 0x30;
			erased++;
		}
	}

	/* re-enable interrupts if necessary */
	if (flag)
		enable_interrupts();

	/* wait at least 50us - let's wait 100 us */
	udelay (100);

	if (erased == 0)
		goto out;

	printf ("Erasing %d sectors... ", erased);

	start = get_timer (0);
	last = start;
	while ((addr[0] & 0x80) != 0x80) {
		now = get_timer(start);
		if (now > (erased * CONFIG_SYS_FLASH_ERASE_TOUT)) {
			printf ("timeout\n");
			return ERR_TIMOUT;
		}
		/* show that we're waiting */
		if ((now - last) > (1 * CONFIG_SYS_HZ)) {	/* every second */
			putc ('.');
			last = now;
		}
	}

	printf ("ok\n");

out:
	/* reset to read mode */
	base[0] = 0xF0;

	return ERR_OK;
}

/*-----------------------------------------------------------------------
 * Copy memory to flash, returns:
 * 0 - OK
 * 1 - write timeout
 * 2 - Flash not erased
 */

int amlv640u_write_buff (flash_info_t *info, uchar *src, ulong dest, ulong cnt)
{
	volatile u16 *base = (u16 *)(info->start[0]);
	volatile u16 *addr = (u16 *)dest;
	u16 *wbuf = (u16 *)src;
	ulong last, now, start;

	last = get_timer(0);
	for (cnt >>= 1; (cnt > 0); cnt--, addr++, wbuf++) {
		if (*addr != *wbuf) {
			base[0x555] = 0xAA;
			base[0x2AA] = 0x55;
			base[0x555] = 0xA0;
			*addr = *wbuf;

			start = get_timer (0);
			while ((*addr & 0x80) != (*wbuf & 0x80)) {
				now = get_timer(0);
				if ((now - start) > CONFIG_SYS_FLASH_WRITE_TOUT) {
					printf ("timeout ");
					break;
				}

				/* show that we're waiting */
				if ((now - last) > (1 * CONFIG_SYS_HZ)) {	/* every second */
					putc ('.');
					last = now;
				}
			}

			if (*addr != *wbuf) {
				printf("write failed, address %08lx -> %x(%x)\n",
						(unsigned long)addr, *wbuf, *addr);

				base[0] = 0xF0;   /* Reset */

				return ERR_TIMOUT;
			}
		}
	}

	printf("ok\n");

	return ERR_OK;
}


/*
 * The following code cannot be run from FLASH!
 */

static ulong amlv640u_get_size (flash_info_t *info, ulong base_addr)
{
	volatile u16 *base = (u16 *)base_addr;
	volatile u16 *addr;
	u16 manuf_id, device_id1, device_id2, device_id3;
	int i;

        /* Write auto select command: read Manufacturer ID */
	base[0x555] = 0xAA;
        base[0x2AA] = 0x55;
	base[0x555] = 0x90;

	manuf_id = base[0];
	device_id1 = base[1];
	device_id2 = base[14];
	device_id3 = base[15];

	if (manuf_id != (AMD_MANUFACT & 0xffff))
		return 0;

	if (device_id1 != (AMD_ID_MIRROR & 0xffff) ||
	    device_id2 != (AMD_ID_LV640U_2 & 0xffff) ||
	    device_id3 != (AMD_ID_LV640U_3 & 0xffff))
		return 0;

	printf("found AMLV640U flash at %08X\n", base_addr);

	info->flash_id = FLASH_MAN_AMD | FLASH_AMLV640U;
	info->size = CFG_FLASH_AMLV640U_SIZE;
	info->sector_count = AMLV640U_SECTORS;

	memset (info->protect, 0, info->sector_count);

	for (i = 0; i < info->sector_count; i++) {
		info->start[i] = base_addr + i * AMLV640U_SECTOR_SIZE;

		addr = (u16 *)info->start[i];
		info->protect[i] = addr[2] & 0x1;
	}

	/* Reset flash */
	base[0] = 0xF0;

	return info->size;
}


ulong amlv640u_flash_init (flash_info_t * info)
{
	ulong base_addr[CONFIG_SYS_MAX_FLASH_BANKS] = CONFIG_SYS_FLASH_BANKS_LIST;
	ulong size = 0;
	int i;

	for (i = 0; i < CONFIG_SYS_MAX_FLASH_BANKS; i++) {
		if (info[i].flash_id == FLASH_UNKNOWN) {
			size += amlv640u_get_size(&info[i], base_addr[i]);
		}
	}

	return size;
}
#endif
