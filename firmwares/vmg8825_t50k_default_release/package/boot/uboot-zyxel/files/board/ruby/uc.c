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

#include "ruby.h"

#ifdef CONFIG_CMD_UC

/****************************************************/

/* Helper macros */
#define MUC_ENTRY_CODE		(&__muc_start_begin)
#define MUC_ENTRY_CODE_SIZE	(&__muc_start_end - &__muc_start_begin)
#define DSP_ENTRY_CODE		(&__dsp_start_begin)
#define DSP_ENTRY_CODE_SIZE	(&__dsp_start_end - &__dsp_start_begin)
#define UC_BSS			((unsigned long)(&__uc_bss_begin))
#define UC_BSS_SIZE		(&__uc_bss_end - &__uc_bss_begin)
/* MuC/DSP sections.
 * MuC/DSP function can call only other MuC/DSP functions -
 * at least until we have memmap flip feature (unfortunately).
 */
#define UC_TEXT_SECTION __attribute__((section(UC_TEXT_SECTION_NAME)))
#define UC_DATA_SECTION __attribute__((section(UC_DATA_SECTION_NAME)))
#define UC_BSS_SECTION __attribute__((section(UC_BSS_SECTION_NAME)))

/****************************************************/

/* Defined in assembler - MuC code entry point */
extern char __muc_start_begin;
extern char __muc_start_end;
/* Defined in assembler - DSP code entry point */
extern char __dsp_start_begin;
extern char __dsp_start_end;
/* Defined in assembler - MuC/DSP BSS section */
extern char __uc_bss_begin;
extern char __uc_bss_end;

/****************************************************/

UC_BSS_SECTION volatile unsigned long uc_trace_num = 0;
UC_BSS_SECTION volatile unsigned long uc_trace_done = 0;

/****************************************************/

static int trigger_irq(unsigned long mask, unsigned long reg, int sec)
{
	int ret = -1;
	const unsigned long irq_num = 0x0;
	int i;

	writel(1 << irq_num, mask);
	writel(1 << irq_num, reg);

	for(i = 0; i < sec; ++i) {
		unsigned long stamp = get_timer(0);
		while(1) {
			if(!readl(reg)) {
				ret = 0;
				goto done;
			} else if (get_timer(stamp) > CONFIG_SYS_HZ) {
				break;
			}
		}
	}

done:
	writel(0x0, mask);

	return ret;
}

static void switch_uc(int enable, unsigned  long reset_val)
{
	const unsigned long reset = reset_val;
	writel(reset, RUBY_SYS_CTL_CPU_VEC_MASK);
	writel(enable ? reset : 0, RUBY_SYS_CTL_CPU_VEC);
	writel(0, RUBY_SYS_CTL_CPU_VEC_MASK);
}

inline static void switch_muc(int enable)
{
	switch_uc(enable, RUBY_SYS_CTL_RESET_MUC_ALL);
}

inline static void switch_dsp(int enable)
{
	switch_uc(enable, RUBY_SYS_CTL_RESET_DSP_ALL);
}

static void prepare_uc_code(void *code_begin, unsigned long code_size)
{
	/* Copy instructions to place from which MuC/DSP start execution */
	memmove(UC_ENTRY_SLOT, code_begin, code_size);
	flush_cache(
		virt_to_phys(UC_ENTRY_SLOT),
		virt_to_phys(UC_ENTRY_SLOT + code_size));

	/* Cleanup BSS section */
	memset(bus_to_virt(UC_BSS), 0, UC_BSS_SIZE);
	flush_cache(
		virt_to_phys(bus_to_virt(UC_BSS)),
		virt_to_phys(bus_to_virt(UC_BSS)) + UC_BSS_SIZE);
}

static int set_muc_start_addr(void *addr)
{
	/* Check that we have correct address. */
	if ((unsigned long)addr & (RUBY_BIT(RUBY_SYS_CTL_MUC_REMAP_SHIFT) - 1)) {
		return -1;
	}

	/* Tells MuC from which address start execution */
	writel(RUBY_SYS_CTL_MUC_REMAP_VAL(virt_to_bus(addr)),
		RUBY_SYS_CTL_MUC_REMAP);

	return 0;
}

static int prepare_muc_code(void)
{
	prepare_uc_code(MUC_ENTRY_CODE, MUC_ENTRY_CODE_SIZE);
	return set_muc_start_addr(UC_ENTRY_SLOT);
}

static int set_dsp_start_addr(void *addr)
{
	/* Check that we have correct address. */
	if ((unsigned long)addr & (RUBY_BIT(RUBY_SYS_CTL_DSP_REMAP_SHIFT) - 1)) {
		return -1;
	}

	/* Tells DSP from which address start execution */
	writel(RUBY_SYS_CTL_DSP_REMAP_VAL(virt_to_bus(addr)),
		RUBY_SYS_CTL_DSP_REMAP);

	return 0;
}

static int prepare_dsp_code(void)
{
	prepare_uc_code(DSP_ENTRY_CODE, DSP_ENTRY_CODE_SIZE);
	return set_dsp_start_addr(UC_ENTRY_SLOT);
}

static void test_uc_trace_prepare(void)
{
	writel(0, bus_to_virt((unsigned long)&uc_trace_num));
	writel(0, bus_to_virt((unsigned long)&uc_trace_done));
}

static unsigned long get_test_uc_trace_num(void)
{
	return readl(bus_to_virt((unsigned long)&uc_trace_num));
}

static unsigned long is_test_uc_trace_done(void)
{
	return readl(bus_to_virt((unsigned long)&uc_trace_done));
}

static int test_uc_wait(int sec)
{
	int ret = -1;
	int i;

	for(i = 0; i < sec; ++i) {
		unsigned long stamp = get_timer(0);
		while(1) {
			if(is_test_uc_trace_done()) {
				ret = 0;
				printf("Success: execution time: %d sec, %lu ticks\n",
					(int)i, (unsigned long)get_timer(stamp));
				goto done;
			} else if (get_timer(stamp) > CONFIG_SYS_HZ) {
				break;
			}
		}
	}

done:
	printf("uC trace number: %u\n", (unsigned)get_test_uc_trace_num());
	if (ret) {
		printf("Failure: %d\n", ret);
	}
	return ret;
}

static int test_uc_irq(unsigned long mask, unsigned long irq, int sec, int attempts)
{
	int ret = 0;
	int i;

	for (i = 0; i < attempts; ++i) {
		ret = trigger_irq(mask, irq, sec);
		if (ret) {
			ret = -1;
			printf("uC irq triggering failed: ret=%d num=%u\n",
				ret, (unsigned)get_test_uc_trace_num());
			break;
		}
		printf("uC trace number after IRQ: %u\n",
			(unsigned)get_test_uc_trace_num());
	}

	return ret;
}

static int test_muc(int sec)
{
	int ret = 0;

	switch_muc(0);
	udelay(100000);

	ret = prepare_muc_code();
	if (ret) {
		printf("MuC code preparation failed: ret=%d\n", ret);
		return -1;
	}

	test_uc_trace_prepare();

	switch_muc(1);

	ret = test_uc_wait(sec);
	if (ret) {
		printf("MuC wait failed: ret=%d\n", ret);
		return -2;
	}

	ret = test_uc_irq(RUBY_SYS_CTL_L2M_INT_MASK, RUBY_SYS_CTL_L2M_INT, sec, 10);
	if (ret) {
		printf("MuC L2M irq triggering failed: ret=%d\n", ret);
		return -3;
	}

	printf("MuC test: SUCCESS!\n");

	return 0;
}

static int test_dsp(int sec)
{
	int ret = 0;

	switch_dsp(0);
	udelay(100000);

	ret = prepare_dsp_code();
	if (ret) {
		printf("DSP code preparation failed: ret=%d\n", ret);
		return -1;
	}

	test_uc_trace_prepare();

	switch_dsp(1);

	ret = test_uc_wait(sec);
	if (ret) {
		printf("DSP wait failed: ret=%d\n", ret);
		return -2;
	}

	ret = test_uc_irq(RUBY_SYS_CTL_L2D_INT_MASK, RUBY_SYS_CTL_L2D_INT, sec, 10);
	if (ret) {
		printf("DSP L2D irq triggering failed: ret=%d\n", ret);
		return -3;
	}

	printf("DSP test: SUCCESS!\n");

	return 0;
}

static int run_muc(void *addr)
{
	int ret = 0;

	switch_muc(0);
	udelay(100000);

	ret = set_muc_start_addr(addr);
	if (ret) {
		printf("Start address is bad: ret=%d\n", ret);
	} else {
		switch_muc(1);
	}

	return 0;
}

static int run_dsp(void *addr)
{
	int ret = 0;

	switch_dsp(0);
	udelay(100000);

	ret = set_dsp_start_addr(addr);
	if (ret) {
		printf("Start address is bad: ret=%d\n", ret);
	} else {
		switch_dsp(1);
	}

	return 0;
}

/****************************************************/

static int do_uc_test(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[])
{
	int ret = 0;

	if (argc != 2) {
		ret = -1;
	} else if (!strcmp(argv[1], "dsp")) {
		ret = test_dsp(5/*sec timeout*/);
	} else if (!strcmp(argv[1], "muc")) {
		ret = test_muc(5/*sec timeout*/);
	} else {
		ret = -2;
	}

	return ret;
}

static int do_uc_run(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[])
{
	int ret = 0;

	if (argc != 3) {
		ret = -1;
	} else {
		unsigned long addr = simple_strtoul(argv[2], NULL, 0);

		printf("Run code from 0x%lx\n", addr);

		if (!strcmp(argv[1], "dsp")) {
			ret = run_dsp((void*)addr);
		} else if (!strcmp(argv[1], "muc")) {
			ret = run_muc((void*)addr);
		} else {
			ret = -2;
		}
	}

	return ret;
}

U_BOOT_CMD(uc_test, 2, 0, do_uc_test,
		"MuC/DSP test",
		"uc_test dsp|muc - perform test (beware, it changes uboot in-RAM image!)\n"
);

U_BOOT_CMD(uc_run, 3, 0, do_uc_run,
		"MuC/DSP code run",
		"uc_run dsp|muc addr - run code\n"
);

/****************************************************/

#endif // #ifdef CONFIG_CMD_UC

