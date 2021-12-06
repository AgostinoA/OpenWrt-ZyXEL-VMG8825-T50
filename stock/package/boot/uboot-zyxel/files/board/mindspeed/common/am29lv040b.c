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
#include <config.h>
#include <asm/hardware.h>

#ifdef CFG_FLASH_AM040_DRIVER

#define AM29LV040B_SIZE		(512 * 1024)
#define AM29LV040B_SECTOR_SIZE	(64 * 1024)

#define AM29LV040B_SECTORS	(AM29LV040B_SIZE / AM29LV040B_SECTOR_SIZE)


/* Am29LV040B Codes */
#define CMD_RESET		0xF0
#define CMD_AUTO_SELECT		0x90
#define CMD_UNLOCK1		0xAA
#define CMD_UNLOCK2		0x55
#define CMD_ERASE_SETUP		0x80
#define CMD_ERASE_CONFIRM	0x30
#define CMD_PROGRAM		0xA0
#define CMD_UNLOCK_BYPASS	0x20
#define CMD_SECTOR_UNLOCK	0x70

#define MEM_FLASH_ADDR1		0x555
#define MEM_FLASH_ADDR2		0x2AA

#define BIT_ERASE_DONE		0x80
#define BIT_RDY_MASK		0x80


#if defined(CFG_FLASH_PROTECTION)
int am29lv040b_flash_real_protect(flash_info_t *info, long sector, int prot)
{
	/* do nothing for now */
	return ERR_INVAL;
}
#endif

int am29lv040b_flash_erase(flash_info_t * info, int s_first, int s_last)
{
	volatile u8 *base = (u8 *)info->start[0];
	volatile u8 *addr = base;
	int flag, erased, prot, sect;
	ulong start, now, last;

	/* first look for protection bits */

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

	base[MEM_FLASH_ADDR1] = CMD_UNLOCK1;
	base[MEM_FLASH_ADDR2] = CMD_UNLOCK2;
	base[MEM_FLASH_ADDR1] = CMD_ERASE_SETUP;
	base[MEM_FLASH_ADDR1] = CMD_UNLOCK1;
	base[MEM_FLASH_ADDR2] = CMD_UNLOCK2;

	/* Start erase on unprotected sectors */
	for (sect = s_first; sect <= s_last; sect++) {
		if (info->protect[sect] == 0) { /* not protected */
			addr = (u8 *)(info->start[sect]);

			addr[0] = CMD_ERASE_CONFIRM;
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
	while ((addr[0] & BIT_ERASE_DONE) != BIT_ERASE_DONE) {
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
	base[0] = CMD_RESET;

	return ERR_OK;
}

int am29lv040b_write_buff(flash_info_t *info, uchar *src, ulong dest, ulong cnt)
{
	volatile u8 *base = (u8 *)(info->start[0]);
	volatile u8 *addr = (u8 *)dest;
	u8 *wbuf = src;
	ulong last, now, start;

	last = get_timer(0);
	for (; (cnt > 0); cnt--, addr++, wbuf++) {
		if (*addr != *wbuf) {
			base[MEM_FLASH_ADDR1] = CMD_UNLOCK1;
			base[MEM_FLASH_ADDR2] = CMD_UNLOCK2;
			base[MEM_FLASH_ADDR1] = CMD_PROGRAM;
			*addr = *wbuf;

			start = get_timer (0);
			while ((*addr & BIT_RDY_MASK) != (*wbuf & BIT_RDY_MASK)) {
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

				base[0] = CMD_RESET;   /* Reset */

				return ERR_TIMOUT;
			}
		}
	}

	printf("ok\n");

	return ERR_OK;
}


static ulong am29lv040b_get_size(flash_info_t *info, ulong base_addr)
{
	volatile u8 *base = (u8 *)base_addr;
	volatile u8 *addr;
	u8 manuf_id, device_id;
	int i;

	base[MEM_FLASH_ADDR1] = CMD_UNLOCK1;
	base[MEM_FLASH_ADDR2] = CMD_UNLOCK2;
	base[MEM_FLASH_ADDR1] = CMD_AUTO_SELECT;

	manuf_id = base[0];
	device_id = base[1];

	if (manuf_id != (AMD_MANUFACT & 0xff))
		return 0;

	if (device_id != AMD_ID_LV040B)
		return 0;

	printf("found AM29LV040B flash at %08X\n", base_addr);

	info->flash_id = FLASH_MAN_AMD | FLASH_AM040;
	info->size = AM29LV040B_SIZE;
	info->sector_count = AM29LV040B_SECTORS;

	memset(info->protect, 0, info->sector_count);

	for (i = 0; i < info->sector_count; i++) {
		info->start[i] = base_addr + i * AM29LV040B_SECTOR_SIZE;

		addr = (u8 *)info->start[i];
		info->protect[i] = addr[2] & 0x1;
	}

	/* Reset flash */
	base[0] = CMD_RESET;

	return info->size;
}

ulong am29lv040b_flash_init(flash_info_t * info)
{
	ulong base_addr[CONFIG_SYS_MAX_FLASH_BANKS] = CONFIG_SYS_FLASH_BANKS_LIST;
	ulong size = 0;
	int i;

	for (i = 0; i < CONFIG_SYS_MAX_FLASH_BANKS; i++) {
		if (info[i].flash_id == FLASH_UNKNOWN)
			size += am29lv040b_get_size(&info[i], base_addr[i]);
	}

	return size;
}
#endif
