/*
 * Copyright (c) 2017-2018, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <common.h>
#include <malloc.h>
#include <asm/psci.h>
#include <cli.h>
#include <console.h>
#include <linux/linkage.h>

DECLARE_GLOBAL_DATA_PTR;

#define SECONDARY_CORE_STACKSZ (8 * 1024)
#define CPU_POWER_DOWN (1 << 16)

#define ARM_PSCI_TZ_FN_BASE		0x84000000
#define ARM_PSCI_TZ_FN(n)		(ARM_PSCI_TZ_FN_BASE + (n))

#define ARM_PSCI_TZ_FN_CPU_OFF		ARM_PSCI_TZ_FN(2)
#define ARM_PSCI_TZ_FN_CPU_ON		ARM_PSCI_TZ_FN(3)
#define ARM_PSCI_TZ_FN_AFFINITY_INFO	ARM_PSCI_TZ_FN(4)

struct cpu_entry_arg {
	void *stack_ptr;
	volatile void *gd_ptr;
	void *arg_ptr;
	int  cpu_up;
	int cmd_complete;
	int cmd_result;
	void *stack_top_ptr;
};

extern unsigned int __invoke_psci_fn_smc(unsigned int, unsigned int,
					 unsigned int, unsigned int);
extern void secondary_cpu_init(void);

static struct cpu_entry_arg core[NR_CPUS - 1];

void psci_cpu_off(unsigned int state)
{
	__invoke_psci_fn_smc(ARM_PSCI_TZ_FN_CPU_OFF, state, 0, 0);
}

asmlinkage void secondary_core_entry(char *argv, int *cmd_complete,
					int *cmd_result)
{
	unsigned int state = 0;

	if (!mmu_enabled()) {
		mmu_setup();
		cp_delay();
	}

	/* Update here as ncessary - secondary entry point */
	*cmd_result = cli_simple_run_command(argv, CMD_FLAG_SEC_CORE);
	*cmd_complete = 1;

	state = CPU_POWER_DOWN;
	psci_cpu_off(state);
}

int psci_cpu_on(unsigned int cpuid, unsigned int entry, unsigned int arg)
{
	int err;

	err = __invoke_psci_fn_smc(ARM_PSCI_TZ_FN_CPU_ON, cpuid, entry, arg);
	if (err) {
		printf("Enabling CPU%d via psci failed!\n", cpuid);
		return -1;
	}

	printf("Enabled CPU%d via psci successfully!\n", cpuid);
	return 0;
}

int is_psci_cpu_off(unsigned int cpuid)
{
	int err;

	err = __invoke_psci_fn_smc(ARM_PSCI_TZ_FN_AFFINITY_INFO, cpuid, 0, 0);

	return err;
}

int do_runmulticore(cmd_tbl_t *cmdtp,
			   int flag, int argc, char *const argv[])
{
	int j;
	int i;
	int ret;
	int delay = 0;
	int core_status = 0;
	int core_on_status = 0;
	char *ptr = NULL;

	if ((argc <= 1) || (argc > 4))
		return CMD_RET_USAGE;

	/* Setting up stack for secondary cores */
	memset(core, 0, sizeof(core));

	for (i = 1; i < argc; i++) {
		ptr = malloc(SECONDARY_CORE_STACKSZ);
		if (NULL == ptr) {
			j = i - 1;
			while (j >= 0) {
				free(core[i - 1].stack_ptr);
				j--;
			}
			printf("Memory allocation failure\n");
			return CMD_RET_FAILURE;
		}
		/* 0xf0 is the padding length */
		core[i - 1].stack_top_ptr = ptr;
		core[i - 1].stack_ptr = (ptr + (SECONDARY_CORE_STACKSZ) - 0xf0);

		core[i - 1].gd_ptr = gd;
		core[i - 1].arg_ptr = argv[i];
	}

	if (!mmu_enabled()) {
		mmu_setup();
		cp_delay();
	}

	/* Bringing up the secondary cores */
	for (i = 1; i < argc; i++) {
		printf("Scheduling Core %d\n", i);
		delay = 0;
		ret = psci_cpu_on(i, (unsigned int)secondary_cpu_init,
				(unsigned int)&(core[i - 1]));
		if (ret) {
			panic("PSCI failed for core %d\n",i);
		}

		while ((delay < 5) && (!(core[i - 1].cpu_up))) {
			mdelay(1000);
			delay++;
		}
		if (!(core[i - 1].cpu_up)) {
			panic("Can't bringup core %d\n",i);
		}

		core_status |= (BIT(i - 1));
		core_on_status |= (BIT(i - 1));
	}

	/* Waiting for secondary cores to complete the task */
	while (core_status) {
		for (i = 1; i < argc; i++) {
			if ((core_status & (BIT(i - 1))) &&
					(core[i - 1].cmd_complete)) {
				printf("Command on core %d is %s\n", i,
					core[i - 1].cmd_complete ?
					((core[i - 1].cmd_result == -1) ?
					"FAIL" : "PASS"):
					"INCOMPLETE");
				core_status &= (~BIT((i - 1)));
			}
		}
		if (ctrlc()) {
			run_command("reset", 0);
		}
	}

	for (i = 1; (core_status && (i < argc)); i++) {
		if (core_status & (BIT(i - 1))) {
			printf("Command on core %d is %s\n", i,
				core[i - 1].cmd_complete ?
				((core[i - 1].cmd_result == -1) ?
				 "FAIL" : "PASS"): "INCOMPLETE");
		}
	}

	/* Waiting for cores to powerdown */
	delay = 0;
	while (core_on_status) {
		for (i = 1; i < argc; i++) {
			if (core_on_status & (BIT(i - 1))) {
				if (is_psci_cpu_off(i) == 1) {
					printf("core %d powered off\n", i);
					core_on_status &= (~BIT((i - 1)));
				}
			}
		}
		mdelay(1000);
		delay++;
		if (delay > 5)
			panic("Some cores can't be powered off\n");
	}

	/* Free up all the stack */
	for (i = 1; i < argc; i++) {
		free(core[i - 1].stack_top_ptr);
	}

	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(runmulticore, 4, 0, do_runmulticore,
	   "Enable and schedule secondary cores",
	   "runmulticore <\"command to core1\"> [core2 core3 ...]");
