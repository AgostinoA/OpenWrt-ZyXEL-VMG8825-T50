/*
 * (C) Copyright 2010 Quantenna Communications Inc.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */


#ifndef __RUBY_H
#define __RUBY_H

/* MuC/DSP section names */
#define UC_TEXT_SECTION_NAME	".text.uc"
#define UC_DATA_SECTION_NAME	".data.uc"
#define UC_BSS_SECTION_NAME	".bss.uc"


#ifndef __ASSEMBLY__

/***************************************************************************/

#include <linux/types.h>
#include <config.h>
#include <common.h>

#include <asm/io.h>
#include <asm/global_data.h>
#include <asm/uboot-arc.h>
#include <asm/arcregs.h>
#include <asm/arch/platform.h>



/***************************************************************************/

void board_timer_init(void);
void board_ddr_init(void);
void board_serial_init(void);
void board_intr_init(void);
void board_progress_init(void);
void board_spi_flash_init(void);
void board_info_init(void);

int board_update_uboot_version(void);

/***************************************************************************/

void gpio_config(u32 pin, u32 cfg);
void gpio_output(u32 pin, u32 state);
u32 gpio_input(u32 pin);

/***************************************************************************/

void __attribute__ ((noreturn)) board_reset(const char *reason);

/***************************************************************************/

int get_stage2_image(uint32_t method_req, uint32_t *method_used);
void qtn_parse_early_flash_config(int overwrite);

/***************************************************************************/

int serial_tx_done(void);

/***************************************************************************/

/* Defined in linker script */
extern char __uboot_begin;
extern char __bss_start;
extern char __uboot_end;
/* Defined in assembler - MuC code entry point */
extern char __muc_start_begin;
extern char __muc_start_end;
/* Defined in assembler - DSP code entry point */
extern char __dsp_start_begin;
extern char __dsp_start_end;
/* Defined in assembler - MuC/DSP BSS section */
extern char __uc_bss_begin;
extern char __uc_bss_end;

struct early_flash_config {
#define RUBY_BOOT_METHOD_TRYLOOP	0
#define RUBY_BOOT_METHOD_TFTP		1
#define RUBY_BOOT_METHOD_BOOTP		2
#define RUBY_BOOT_METHOD_MAX		3
	uint32_t method;
	uint32_t ipaddr;
	uint32_t serverip;
};

static inline struct early_flash_config *get_early_flash_config(unsigned long text_base)
{
	extern char early_flash_config_start;
	return (void*)(&early_flash_config_start - &__uboot_begin + text_base);
}

/***************************************************************************/

#endif // #ifndef __ASSEMBLY__

/***************************************************************************/

#ifdef __ASSEMBLY__
	#define UC_ENTRY_SLOT	__uboot_begin
#else
	#define UC_ENTRY_SLOT	(&__uboot_begin)
#endif

/***************************************************************************/

#define UC_TEXT_SECTION		__attribute__((section(UC_TEXT_SECTION_NAME)))
#define UC_DATA_SECTION		__attribute__((section(UC_DATA_SECTION_NAME)))
#define UC_BSS_SECTION		__attribute__((section(UC_BSS_SECTION_NAME)))

/***************************************************************************/

#define arc_read_uncached_32(ptr)                   \
({                                  \
    unsigned int __ret;                     \
    __asm__ __volatile__ ("ld.di %0, [%1]":"=r"(__ret):"r"(ptr));   \
    __ret;                              \
})

#define _arc_write_uncached_32(ptr, data)                \
({                                  \
    __asm__ __volatile__ ("st.di %0, [%1]"::"r"(data), "r"(ptr));   \
})

#endif // #ifndef __RUBY_H


