/*
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/* #define	DEBUG	*/

#include <common.h>
#include <autoboot.h>
#include <cli.h>
#include <console.h>
#include <version.h>

DECLARE_GLOBAL_DATA_PTR;
#include <config.h>
/*
 * Board-specific Platform code can reimplement show_boot_progress () if needed
 */
__weak void show_boot_progress(int val) {}

static void modem_init(void)
{
#ifdef CONFIG_MODEM_SUPPORT
	debug("DEBUG: main_loop:   gd->do_mdm_init=%lu\n", gd->do_mdm_init);
	if (gd->do_mdm_init) {
		char *str = getenv("mdm_cmd");

		setenv("preboot", str);  /* set or delete definition */
		mdm_init(); /* wait for modem connection */
	}
#endif  /* CONFIG_MODEM_SUPPORT */
}

static void run_preboot_environment_command(void)
{
#ifdef CONFIG_PREBOOT
	char *p;

	p = getenv("preboot");
	if (p != NULL) {
# ifdef CONFIG_AUTOBOOT_KEYED
		int prev = disable_ctrlc(1);	/* disable Control C checking */
# endif

		run_command_list(p, -1, 0);

# ifdef CONFIG_AUTOBOOT_KEYED
		disable_ctrlc(prev);	/* restore Control C checking */
# endif
	}
#endif /* CONFIG_PREBOOT */
}

#ifdef CONFIG_ZYXEL_ZLOADER
void fake_sys_halt(void)
{
//bypass this first
    int i=0;
    char passwd[]={'q','u','i','t'}, ch;
    ulong timer;
    printf("Reset your board! system halt...");
    return;
    timer=get_timer(0);
    do {
        if ( tstc() ) {
            ch=getc();
            if (ch==passwd[i]) {
                i++;
                timer=get_timer(0);
            } else {
                i=0;
            }
        }
        if ( get_timer(timer)>160 /*ms*/ ) {
            i=0;
            timer = get_timer(0);
        }
    } while (i<sizeof(passwd));
    putc('\n');
}
#endif

/* We come here after U-Boot is initialised and ready to process commands */
void main_loop(void)
{
	const char *s;
	int rtn = 0;
   
	bootstage_mark_name(BOOTSTAGE_ID_MAIN_LOOP, "main_loop");

#ifndef CONFIG_SYS_GENERIC_BOARD
	puts("Warning: Your board does not use generic board. Please read\n");
	puts("doc/README.generic-board and take action. Boards not\n");
	puts("upgraded by the late 2014 may break or be removed.\n");
#endif

	modem_init();
#ifdef CONFIG_VERSION_VARIABLE
	setenv("ver", version_string);  /* set version variable */
#endif /* CONFIG_VERSION_VARIABLE */

	cli_init();

	run_preboot_environment_command();

#if defined(CONFIG_UPDATE_TFTP)
	update_tftp(0UL, NULL, NULL);
#endif /* CONFIG_UPDATE_TFTP */

	s = bootdelay_process();
	if (cli_process_fdt(&s))
		cli_secure_boot_cmd(s);

	autoboot_command(s);

#ifdef CONFIG_ZYXEL_ZLOADER
 #include <zgpio.h>
    //gd->flags |= GD_FLG_DISABLE_CONSOLE;
    
    /* load & boot zloader */
 #ifdef CONFIG_ZFLASH_CMD
    printf("run zflash_init\n");
    zflash_init();
 #endif
    s = getenv("boot_zld");
    if (!s)
        setenv("boot_zld", CONFIG_BOOT_ZLOADER_CMD);
    rtn = run_command("run boot_zld", 0); 
    if ( rtn != 0 ) {
        //gd->flags &= (~GD_FLG_DISABLE_CONSOLE);
        printf("\n!!!!! fail to boot zloader !!!!!\n");
        /* should not return here */
        //ZLOADER_EXEC_FAILED_LED_INDICATE;
        fake_sys_halt();
    }
#endif
    setenv("ethrotate", "no");
    setenv("netretry", "no");
    setenv("ethact", "eth0");

    net_init();
    int ret = 0;
    eth_halt();
    eth_set_current();
    ret = eth_init();
    if (ret < 0) {
        printf("eth_init failed in main.c!\n");
        eth_halt();
        return ret;
    }
    cli_loop();
}
#ifdef CONFIG_ZYXEL_ZLOADER
char  *get_user_command_buffer(void)
{
	return &console_buffer[0];
}
#endif