/*
 * (C) Copyright 2006
 * Mindspeed Technologies, Inc. <www.mindspeed.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <common.h>
#include <config.h>
#include <command.h>
#include <asm/byteorder.h>
#include <asm/hardware.h>

#ifdef CONFIG_CMD_ELF
extern int valid_elf_image (unsigned long addr);
extern unsigned long load_elf_image (unsigned long addr);
#endif

DECLARE_GLOBAL_DATA_PTR;

struct _AIF_HEADER {
	u32 BL_DecompressCode;
	u32 BL_SelfRelocCode;
	u32 BL_DbgInitZeroInit;
	u32 EntryPointOffset;
	u32 ProgramExitInstr;
	u32 ImageReadOnlySize;
	u32 ImageReadWriteSize;
	u32 ImageDebugSize;
	u32 ImageZeroInitSize;
	u32 ImageDebugType;
	u32 ImageBase;
	u32 WorkSpace;
	u32 AddressMode;
	u32 DataBase;
	u32 FirstFatOffset;
	u32 Reserved2;
	u32 DebugInitInstr;
	u32 ZeroInitCode[15];
};

struct _FAT_AIF_HEADER {
	u32 NextFatOffset;
	u32 LoadAddress;
	u32 Size;
	u8 region_name[32];
};

/**
 * print_axf_hdr -
 *
 */
static void print_axf_hdr(ulong addr)
{
	struct _AIF_HEADER *aif_hdr = (struct _AIF_HEADER *)(addr);

	/* we assume that MSP image in memory is not less than the header size (_AIF_HEADER) */

	printf("code_offset=0x80\n");
	printf("code_base=%x\n", aif_hdr->ImageBase);
	printf("data_offset=%x\n", 0x80 + aif_hdr->ImageReadOnlySize);
	printf("code_size=%x\n", aif_hdr->ImageReadOnlySize);
	printf("data_base=%x\n", aif_hdr->ImageBase + aif_hdr->ImageReadOnlySize);
	printf("data_size=%x\n", aif_hdr->ImageReadWriteSize);
	printf("zeroinit_base=%x\n",
	       aif_hdr->ImageBase + aif_hdr->ImageReadOnlySize + aif_hdr->ImageReadWriteSize);
	printf("prog_entry=%x\n", aif_hdr->ImageBase + aif_hdr->EntryPointOffset);

	printf(" \n");
	printf("AIFHEADER:\n");
	printf("BL_DecompressCode=%x\n", aif_hdr->BL_DecompressCode);
	printf("BL_SelfRelocCode=%x\n", aif_hdr->BL_SelfRelocCode);
	printf("BL_DbgInitZeroInit=%x\n", aif_hdr->BL_DbgInitZeroInit);
	printf("EntryPointOffset=%x\n", aif_hdr->EntryPointOffset);
	printf("ProgramExitInstr=%x\n", aif_hdr->ProgramExitInstr);
	printf("ImageReadOnlySize=%x\n", aif_hdr->ImageReadOnlySize);
	printf("ImageReadWriteSize=%x\n", aif_hdr->ImageReadWriteSize);
	printf("ImageDebugSize=%x\n", aif_hdr->ImageDebugSize);
	printf("ImageZeroInitSize=%x\n", aif_hdr->ImageZeroInitSize);
	printf("ImageDebugType=%x\n", aif_hdr->ImageDebugType);
	printf("ImageBase=%x\n", aif_hdr->ImageBase);
	printf("WorkSpace=%x\n", aif_hdr->WorkSpace);
	printf("AddressMode=%x\n", aif_hdr->AddressMode);
	printf("DataBase=%x\n", aif_hdr->DataBase);
	printf("FirstFatOffset=%x\n", aif_hdr->FirstFatOffset);
	printf("Reserved2=%x\n", aif_hdr->Reserved2);
	printf("DebugInitInstr=%x\n", aif_hdr->DebugInitInstr);
	printf("ZeroInitCode[0]=%x\n", aif_hdr->ZeroInitCode[0]);
}

/**
 * check_load_addr -
 *
 */
static int check_load_addr(ulong addr)
{
	if ((addr > MSP_BOTTOM_MEMORY_RESERVED_SIZE) &&
#if defined(CONFIG_COMCERTO_530)
	    ((addr < ERAM_BASEADDR) || (addr >= IRAM_BASEADDR + IRAM_SIZE))
#elif defined(CONFIG_COMCERTO_515) || defined(CONFIG_COMCERTO_800)
	    ((addr < ERAM_BASEADDR) || (addr >= ARAM_BASEADDR + ARAM_SIZE))
#elif defined(CONFIG_COMCERTO_900)
	    ((addr < ERAM_BASEADDR) || (addr >= CRAM_BASEADDR + CRAM_SIZE))
#else
	    (1)
#endif
	)
		return -1;

	return 0;
}

/**
 * load_axf_zero -
 *
 */
static int load_axf_zero(ulong addr)
{
	struct _AIF_HEADER *aif_hdr = (struct _AIF_HEADER *)(addr);
	u32 m_data_base;
	u32 bytes_to_load;

	if (aif_hdr->DataBase)
		m_data_base = aif_hdr->DataBase;
	else
		m_data_base = aif_hdr->ImageBase + aif_hdr->ImageReadOnlySize;

	m_data_base = m_data_base + aif_hdr->ImageReadWriteSize;
	bytes_to_load = aif_hdr->ImageZeroInitSize / 2;

	if (check_load_addr(m_data_base + bytes_to_load) < 0) {
		printf("data section load address %x outside range\n", m_data_base + bytes_to_load);
		goto err;
	}

	memset((void *)m_data_base, 0, bytes_to_load);

	return 0;

err:
	return -1;
}

/**
 * load_axf_fat -
 */
static int load_axf_fat(ulong addr, ulong size)
{
	struct _AIF_HEADER *aif_hdr = (struct _AIF_HEADER *)(addr);
	struct _FAT_AIF_HEADER *fat_aif_hdr;
	u32 fat_offset;

	fat_offset = aif_hdr->FirstFatOffset;

	while (fat_offset > 0) {

		if ((fat_offset + sizeof(struct _FAT_AIF_HEADER)) > size) {
			printf("fat section header at %x outside image %lx\n", fat_offset, size);
			goto err;
		}

		fat_aif_hdr = (struct _FAT_AIF_HEADER *)(addr + fat_offset);

		if ((fat_offset + sizeof(struct _FAT_AIF_HEADER) + fat_aif_hdr->Size) > size) {
			printf("fat section size %x bigger than image size %lx\n", fat_offset + sizeof(struct _FAT_AIF_HEADER) + fat_aif_hdr->Size, size);
			goto err;
		}

		if (check_load_addr(fat_aif_hdr->LoadAddress + fat_aif_hdr->Size) < 0) {
			printf("fat section load address %x outside range\n", fat_aif_hdr->LoadAddress + fat_aif_hdr->Size);
			goto err;
		}

		memcpy((void *)fat_aif_hdr->LoadAddress,
		       (void *)(addr + fat_offset + sizeof(struct _FAT_AIF_HEADER)), fat_aif_hdr->Size);

		fat_offset = fat_aif_hdr->NextFatOffset;
	}

	return 0;

err:
	return -1;
}


/**
 * load_axf_data -
 */
static int load_axf_data(ulong addr, ulong size)
{
	struct _AIF_HEADER *aif_hdr = (struct _AIF_HEADER *)(addr);

	if (aif_hdr->ImageReadWriteSize) {

		if ((sizeof(struct _AIF_HEADER) + aif_hdr->ImageReadOnlySize + aif_hdr->ImageReadWriteSize) > size) {
			printf("data section size %x bigger than image size %lx\n", aif_hdr->ImageReadWriteSize, size);
			goto err;
		}

		if (aif_hdr->DataBase == 0) {
			if (check_load_addr(aif_hdr->ImageBase + aif_hdr->ImageReadOnlySize + aif_hdr->ImageReadWriteSize) < 0) {
				printf("data section load address %x outside range\n", aif_hdr->ImageBase + aif_hdr->ImageReadOnlySize + aif_hdr->ImageReadWriteSize);
				goto err;
			}

			memcpy((void *)(aif_hdr->ImageBase + aif_hdr->ImageReadOnlySize),
			       (void *)(addr + sizeof(struct _AIF_HEADER) + aif_hdr->ImageReadOnlySize),
			       aif_hdr->ImageReadWriteSize);
		} else {
			if (check_load_addr(aif_hdr->DataBase + aif_hdr->ImageReadWriteSize) < 0) {
				printf("data section load address %x outside range\n", aif_hdr->DataBase + aif_hdr->ImageReadWriteSize);
				goto err;
			}

			memcpy((void *)aif_hdr->DataBase,
			       (void *)(addr + sizeof(struct _AIF_HEADER) + aif_hdr->ImageReadOnlySize),
			       aif_hdr->ImageReadWriteSize);
		}

	} else {
		printf("data section size 0\n");
	}

	return 0;

err:
	return -1;
}


/**
 * load_axf_code -
 *
 */
static int load_axf_code(ulong addr, ulong size)
{
	struct _AIF_HEADER *aif_hdr = (struct _AIF_HEADER *)(addr);

	if (aif_hdr->ImageReadOnlySize) {
		if ((sizeof(struct _AIF_HEADER) + aif_hdr->ImageReadOnlySize) > size) {
			printf("code section size %x bigger than image size %lx\n", aif_hdr->ImageReadOnlySize, size);
			goto err;
		}

		if (check_load_addr(aif_hdr->ImageBase + aif_hdr->ImageReadOnlySize) < 0) {
			printf("code section load address %x outside range\n", aif_hdr->ImageBase + aif_hdr->ImageReadOnlySize);
			goto err;
		}

		memcpy((void *)aif_hdr->ImageBase, (void *)(addr + sizeof(struct _AIF_HEADER)), aif_hdr->ImageReadOnlySize);
	} else {
		printf("code section size 0\n");
	}

	return 0;

err:
	return -1;
}

/**
 * load_axf_image -
 *
 */
static ulong load_axf_image(ulong addr, ulong size)
{
	struct _AIF_HEADER *aif_hdr = (struct _AIF_HEADER *) addr;

	printf ("## Downloading image at %08lx ...\n", addr);

	if (sizeof (struct _AIF_HEADER) > size) {
		printf("AXF header %x bigger than image size %lx\n", sizeof (struct _AIF_HEADER), size);
		goto err;
	}

	print_axf_hdr(addr);

	if (load_axf_code(addr, size)) {
		printf("download code failed\n");
		goto err;
	}

	if (load_axf_data(addr, size)) {
		printf("download data failed\n");
		goto err;
	}

	if (load_axf_fat(addr, size)) {
		printf("download fat failed\n");
		goto err;
	}

	if (load_axf_zero(addr)) {
		printf("zero init failed\n");
		goto err;
	}

//	printf ("## Booting image at %08lx ...\n", aif_hdr->ImageBase + aif_hdr->EntryPointOffset);

	return aif_hdr->ImageBase + aif_hdr->EntryPointOffset;

err:
	return (ulong)-1;
}

/**
 * strtoul_with_check - reads unsigned long hex value from string with checking
 *
 * ARGUMENTS:
 *    str:    the string to scan value from
 *    pvalue: pointer to the value location (if be NULL just checking will be
 *            performed)
 *    label:  optinal label for the typical error message (if NULL no message
 *            will be printed)
 *
 * RETURNS:
 *    0 success, -1 otherwise
 */
static int strtoul_with_check(const char *str, ulong *pvalue, const char *label)
{
	ulong value;
	char *end = NULL;

	value = simple_strtoul(str, &end, 16);
	if (str == end || *end != 0) {
		if (label)
			printf("Invalid %s given, please provide correct hex value.\n", label);
		return -1;
	}

	if (pvalue)
		*pvalue = value;

	return 0;
}

/**
 * do_loadmsp - loads MSP image, it may be in either ELF or AXF format. If image
 *    is successfully loaded, stores MSP entry in "msp_start_addr" env. variable.
 *
 * ARGUMENTS:
 *    standard set of U-Boot command arguments, user must pass image address
 *    and size (all in hex).
 *
 * RETURNS:
 *    0 - success, -1 otherwise
 */
static int do_loadmsp (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	ulong addr, size;
	char buf[32];

	if (argc < 3) {
		goto err;
	}

	if (strtoul_with_check(argv[1], &addr, "image address"))
		goto err;

	if (strtoul_with_check(argv[2], &size, "image size"))
		goto err;

#ifdef CONFIG_CMD_ELF
	if (valid_elf_image(addr))
		addr = load_elf_image(addr);
	else
		addr = load_axf_image(addr, size);
#else
	addr = load_axf_image(addr, size);
#endif

	if (addr == (ulong)-1)
		goto err;

	/* store MSP start addr in environment (we will need it do_bootcomcerto) */
	sprintf(buf, "%lx", addr);
	setenv("msp_start_addr", buf);
	printf("image loaded at %lx\n", addr);
	return 0;

err:
	printf("error loading image\n");
	return -1;
}


U_BOOT_CMD(
	loadmsp,  3, 0, do_loadmsp,
	"loadmsp - load MSP image (AXF or ELF format) and save MSP start address\n",
	"address size\n"
	"    - 'address' (hex) points to MSP image location.\n"
	"      'size' (hex) specifies image size.\n"
	"      See also 'bootcomcerto' command.\n"
);


extern char __arm1_init_start, __arm1_init_end;
extern u32 _arm1_start_addr, _arm1_r0, _arm1_r1, _arm1_r2;

/**
 * set_arm1_init - copies ARM1 startup code to reset location and sets CSP
 *    image startup address
 *
 * ARGUMENTS:
 *    addr:     CSP entry point
 *    r0,r1,r2: values for the corresponding ARM1 registers
 */
static void set_arm1_init(ulong addr, ulong r0, ulong r1, ulong r2)
{
	_arm1_start_addr = addr;
	_arm1_r0 = r0;
	_arm1_r1 = r1;
	_arm1_r2 = r2;

	printf("Copying ARM1 startup code from %p, start address %08lx\n",
		&__arm1_init_start, addr);

	memcpy(0, &__arm1_init_start, &__arm1_init_end - &__arm1_init_start);
}

#if !defined(CONFIG_COMCERTO_1000) && !defined(CONFIG_COMCERTO_100)
/* This code only applies to Carrier/Access platforms, where ARM0 is running
 * the MSP and ARM1 the CSP
 */
extern image_header_t header;
extern void do_bootm_linux (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[],
		     ulong addr, ulong *len_ptr, int verify);

#define BOOT_ETH_BASE_ADDRESS	(IRAM_BASEADDR + 0x1250)
#define MAGIC_NUM_ADDRESS_IRAM	(BOOT_ETH_BASE_ADDRESS + 0x10)
#define FLAGS_ADDRESS_IRAM	(BOOT_ETH_BASE_ADDRESS + 0x14)
#define M1_ADDRESS_IRAM		(BOOT_ETH_BASE_ADDRESS + 0x18)
#define M5_ADDRESS_IRAM		(BOOT_ETH_BASE_ADDRESS + 0x24)

#define MAGIC_NUM_IRAM		0x98765432
#define ETHADDR_IRAM_MASK	(1 << 0)

static void msp_boot_eth_hdr_setup(bd_t * bd)
{
	struct eth_hdr {
		u8 hostmac[6];
		u8 mspmac[6];
		u8 padding;
		u16 packet_type;
	} __attribute__((packed)) *hdr;

	/* The MSP expects an ethernet header at this IRAM address */
	/* at boot time */

	hdr = (struct eth_hdr *)(BOOT_ETH_BASE_ADDRESS + 1);
	
	hdr->hostmac[0] = 0x00;
	hdr->hostmac[1] = 0x11;
	hdr->hostmac[2] = 0x22;
	hdr->hostmac[3] = 0x33;
	hdr->hostmac[4] = 0x44;
	hdr->hostmac[5] = 0x55;

	hdr->mspmac[0] = 0x00;
	hdr->mspmac[1] = 0x1a;
	hdr->mspmac[2] = 0x1b;
	hdr->mspmac[3] = 0x1c;
	hdr->mspmac[4] = 0x1d;
	hdr->mspmac[5] = 0x1e;

	hdr->packet_type = 0x889b;
}

static void msp_iram_flags_setup(bd_t * bd)
{
	int i;
	ulong reg;
	char *s, *e;
	char tmp[64];
				
	/* pass miscellaneous params to the MSP via IRAM
	   Since these are not passed by all boot loaders use a magic number
	   to tell the MSP that if parameters are present */
	*(u32 *)MAGIC_NUM_ADDRESS_IRAM = MAGIC_NUM_IRAM;

	/* the next word is a bit-map that tells the MSP which parameters are present,
           this allows params to be added and different versions of bootloader and MSP
           to inter-operate */

	/* always have ethaddr; even if user does not specify it (which is an error), we have a default */
	*(u32 *)FLAGS_ADDRESS_IRAM = ETHADDR_IRAM_MASK;

	/* write ethernet address */
	memcpy((u8 *)M1_ADDRESS_IRAM, bd->bi_enetaddr, 6);

	i = getenv_r ("eth1addr", tmp, sizeof (tmp));
	s = (i > 0) ? tmp : NULL;
	for (reg = 0; reg < 6; ++reg) {
		*(u8 *) (M5_ADDRESS_IRAM + reg) = s ? simple_strtoul (s, &e, 16) : 0;
		if (s)
			s = (*e) ? e + 1 : e;
	}
}

/**
 * do_bootcomcerto - checks if MSP image was loaded, then loads CSP image which
 *    may be in either binary or ELF format and boots MSP.
 *
 * ARGUMENTS:
 *    standard set of U-Boot command arguments, user must pass CSP image address
 *
 * RETURNS:
 *    doesn't return on success
 */
static int do_bootcomcerto (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	ulong csp_start_addr, msp_start_addr;
	int csp_is_elf = 0;
	bd_t *bd = gd->bd;
	char *str;

	if (argc < 2) {
		return -1;
	}

	str = getenv("msp_start_addr");
	if (!str) {
		printf("MSP start address is not set, see 'loadmsp' command\n");
		return -1;
	}

	if (strtoul_with_check(str, &msp_start_addr, NULL)) {
		printf("Invalid MSP address, aborting\n");
		return -1;
	}

	if (strtoul_with_check(argv[1], &csp_start_addr, "image address"))
		return -1;

#ifdef CONFIG_CMD_ELF
	if ((csp_is_elf = valid_elf_image(csp_start_addr)) != 0)
		csp_start_addr = load_elf_image(csp_start_addr);
#endif

	/* Setup MSP boot args in IRAM */
	msp_boot_eth_hdr_setup(bd);
	msp_iram_flags_setup(bd);

	if (csp_is_elf == 0) {
		/* CSP image is in binary format, assuming Linux */

		/* Fake header to keep do_bootm_linux() happy
		 * No ramdisk support for now
		 */
		header.ih_ep = htonl(msp_start_addr);	/* This is actually the MSP entry point */
		header.ih_type = IH_TYPE_KERNEL;
#if 0
		hdr->ih_magic = htonl(IH_MAGIC);
		hdr->ih_hcrc = htonl(0);	/* FIXME calculate the checksum */
		hdr->ih_size = htonl(0);
#endif

		set_arm1_init(csp_start_addr, 0, bd->bi_arch_number, bd->bi_boot_params);
		do_bootm_linux(cmdtp, 0, argc, argv, 0, NULL, 0);
	}
	else {
		/* CSP image is in ELF, assuming VxWorks */

		set_arm1_init(csp_start_addr, (unsigned int)getenv("bootargs"), 0, 0);
		((void(*)(void))msp_start_addr)();
	}

	printf("Unexpected return to bootloader!\n");

	return 0;
}


U_BOOT_CMD(
	bootcomcerto, 2, 0, do_bootcomcerto,
	"bootcomcerto - load CSP image (binary or ELF format) and start Comcerto device\n",
	"address\n"
	"    - 'address'(hex) points to CSP image location.\n"
	"      See also 'loadmsp' command, which must be run before this one.\n"
);
#endif
