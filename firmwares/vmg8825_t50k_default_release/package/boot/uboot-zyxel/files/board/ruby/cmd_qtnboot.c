/*
 * Quantenna boot support
 */
#include <common.h>
#include <command.h>
#include <environment.h>

#include "ruby.h"
#include "spi_flash.h"

#define BUFSIZE 256

/* get all of the pointers, vaguely validate them, 1 on failure, 0 on success */
static int get_qtnboot_envvars(unsigned long *safety_addr, unsigned long *live_addr,
                               unsigned long *safety_size, unsigned long *live_size)
{
	char *safety_addr_str = getenv (SAFETY_IMG_ADDR_ARG);
	char *safety_size_str = getenv (SAFETY_IMG_SIZE_ARG);
	char *live_addr_str = getenv (LIVE_IMG_ADDR_ARG);
	char *live_size_str = getenv (LIVE_IMG_SIZE_ARG);

	if (safety_addr_str && safety_size_str && live_addr_str && live_size_str) {
		*safety_addr = simple_strtoul(safety_addr_str, NULL, 0);
		*safety_size = simple_strtoul(safety_size_str, NULL, 0);
		*live_addr = simple_strtoul(live_addr_str, NULL, 0);
		*live_size = simple_strtoul(live_size_str, NULL, 0);
		if (!(*safety_size > 0
		      && *live_addr >= *safety_addr + *safety_size
		      && *live_size >= *safety_size)) {
			printf("Variables: %s %s %s %s aren't valid\n",
			       SAFETY_IMG_ADDR_ARG,
			       SAFETY_IMG_SIZE_ARG,
			       LIVE_IMG_ADDR_ARG,
			       LIVE_IMG_SIZE_ARG);
			return 1;
		}

		const unsigned sector_size = spi_flash_sector_size();
		const unsigned flash_size = spi_flash_size();

		if ((*safety_size % sector_size) || (*live_size % sector_size)) {
			printf("partitions sizes not a multiple of sector size: %dk\n", sector_size / 1024);
			return 1;
		}

		if ((*safety_size + *live_size +
		     RUBY_MIN_DATA_PARTITION_SIZE +
		     UBOOT_TEXT_PARTITION_SIZE +
		     UBOOT_ENV_PARTITION_SIZE) > flash_size) {
			printf("Sizes exceed flash size: %dk, will not fit on device",
			       flash_size / 1024);
			return 1;
		}
	} else {
		printf("Variables: %s %s %s %s must be set\n",
		       SAFETY_IMG_ADDR_ARG,
		       SAFETY_IMG_SIZE_ARG,
		       LIVE_IMG_ADDR_ARG,
		       LIVE_IMG_SIZE_ARG);
		return 1;
	}

	printf("%s: vars: %s 0x%lx %s 0x%lx %s 0x%lx %s 0x%lx\n",
	       __FUNCTION__,
	       SAFETY_IMG_ADDR_ARG, *safety_addr,
	       SAFETY_IMG_SIZE_ARG, *safety_size,
	       LIVE_IMG_ADDR_ARG, *live_addr,
	       LIVE_IMG_SIZE_ARG, *live_size);

	return 0;
}

/* setup the mtdargs parameter to pass a partition table into linux */
static void set_mtdparts(unsigned long safety_size, unsigned long live_size)
{
	char mtdparts[BUFSIZE];

	sprintf(mtdparts, "spi_flash:%dk(uboot),%dk(uboot_env),%luk(linux_safety_image),%luk(linux_live_image),-(data)",
	        UBOOT_TEXT_PARTITION_SIZE / 1024,
	        UBOOT_ENV_PARTITION_SIZE / 1024,
	        safety_size / 1024,
	        live_size / 1024
	       );

	setenv("mtdparts", mtdparts);
}

int do_qtn_setmtdparts (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	unsigned long safety_addr = 0;
	unsigned long safety_size = 0;
	unsigned long live_addr = 0;
	unsigned long live_size = 0;

	if (get_qtnboot_envvars(&safety_addr, &live_addr, &safety_size, &live_size))
		return -1;
	set_mtdparts(safety_size, live_size);
	return 0;
}

U_BOOT_CMD(qtn_setmtdparts, CONFIG_SYS_MAXARGS, 0, do_qtn_setmtdparts,
           "set the environment variable 'mtdparts'",
           "sets mtdparts to a string appropriate for the mtdparts kernel \n"
           "command line argument. Partitions are derived from the environment\n"
           "variables: ${" LIVE_IMG_ADDR_ARG "}, ${" SAFETY_IMG_ADDR_ARG "},\n"
           "${" SAFETY_IMG_SIZE_ARG "} and ${" LIVE_IMG_SIZE_ARG "}\n"
          );

#define RUN(args...) _run(__FUNCTION__, args)
static int _run(const char* function_name, ...)
{
	va_list args;
	char cmdbuf[BUFSIZE];
	sprintf(cmdbuf, args);
	printf("%s: %s\n", function_name, cmdbuf);
	return run_command(cmdbuf, 0);
}

int do_qtnboot (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	unsigned long safety_addr = 0;
	unsigned long safety_size = 0;
	unsigned long live_addr = 0;
	unsigned long live_size = 0;
	const unsigned long mem_addr = QTNBOOT_COPY_DRAM_ADDR;

	if (get_qtnboot_envvars(&safety_addr, &live_addr, &safety_size, &live_size)) {
		return -1;
	}

	set_mtdparts(safety_size, live_size);
	RUN("setenv bootargs ${bootargs} mtdparts=${mtdparts}");

	// attempt to load the live image into memory and boot it.
	RUN("spi_flash read 0x%08lx 0x%08lx 0x%08lx", live_addr, mem_addr, live_size);
	RUN("bootm 0x%08lx", mem_addr);

	// if control returns, it failed
	// load the safety image into memory, copy it over the live image, then boot/reset
	RUN("spi_flash read 0x%08lx 0x%08lx 0x%08lx", safety_addr, mem_addr, safety_size);

	// run_command returns -1 for errors, or repeatability, rather than return codes
	if (RUN("imi 0x%08lx", mem_addr) < 0) {
		printf("FATAL: safety image at 0x%08lx appears corrupt\n", safety_addr);
		return -1;
	}

	RUN("spi_flash unlock");
	RUN("spi_flash erase 0x%08lx 0x%08lx", live_addr, live_size);
	RUN("spi_flash write 0x%08lx 0x%08lx 0x%08lx", live_addr, mem_addr, safety_size);
	RUN("sleep 2");
	RUN("reset");

	// never gets to here
	return 0;
}

U_BOOT_CMD(qtnboot, CONFIG_SYS_MAXARGS, 0, do_qtnboot,
		"boot from live image, recover safety image if necessary",
		"Quantenna dual boot with recovery. Attempts to boot the live image\n"
		"found at address ${" LIVE_IMG_ADDR_ARG "}. If the checksum fails, \n"
		"the safety image at ${" SAFETY_IMG_ADDR_ARG "} is copied over the \n"
		"live image, then booted.\n"
	  );

int do_bootselect(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	unsigned long safety_addr = 0;
	unsigned long safety_size = 0;
	unsigned long live_addr = 0;
	unsigned long live_size = 0;
	unsigned long addr;
	unsigned long size;
	const unsigned long mem_addr = QTNBOOT_COPY_DRAM_ADDR;
	unsigned long bootsel_val = 0;
	const char* bootsel_str = NULL;

	if (get_qtnboot_envvars(&safety_addr, &live_addr, &safety_size, &live_size)) {
		return -1;
	}

	bootsel_str = getenv("bootselect");
	if (bootsel_str) {
		bootsel_val = simple_strtoul(bootsel_str, NULL, 0);
	}

	if (bootsel_val) {
		addr = safety_addr;
		size = safety_size;
	} else {
		addr = live_addr;
		size = live_size;
	}

	RUN("spi_flash read 0x%08lx 0x%08lx 0x%08lx", addr, mem_addr, size);
	RUN("bootm 0x%08lx", mem_addr);
}

U_BOOT_CMD(bootselect, CONFIG_SYS_MAXARGS, 0, do_bootselect,
		"boot live/safety depending on value of 'bootselect'",
		"If env variable 'bootselect' is 1, boot from image at safety address;\n"
		"Otherwise boot from image at live address\n"
	  );

#define RUBY_SPI1_BASE_ADDR              0xF2000000
#define RUBY_SPI1_EXT                 0xc


int do_setgpio(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	unsigned long ngpio;
	unsigned long value;

	if (argc < 2) {
		cmd_usage(cmdtp);
		return 1;
	}

	ngpio = simple_strtoul(argv[1], NULL, 10);
	if (ngpio >= RUBY_GPIO_MAX)
		return 1;

	if (argc > 2) {
		value = simple_strtoul(argv[2], NULL, 10);
		value = !!value;
	} else
		value = 1;

	gpio_output(ngpio, value);
	gpio_config(ngpio, RUBY_GPIO_MODE_OUTPUT);

	return 0;
}

U_BOOT_CMD(setgpio, CONFIG_SYS_MAXARGS, 2, do_setgpio,
	"Configure gpio as output and set the output value",
	"ngpio [value], drive the ngpio to 'value'\n"
	"drive the ngpio to 1 if value is absent\n"
);

