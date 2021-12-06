#include <common.h>
#include <command.h>

#ifdef CONFIG_ZGPIO_CMD
#include <zgpio.h>
int do_zgpio(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    int pio, val;
    
    if ( argc == 2 && argv[1][0]=='d' ) {
        dump_pio_regs();
        return 0;
    }
    if ( argc <3 ) {
        return -1;
    }
    pio = simple_strtoul(argv[2], NULL, 0);
    if ( pio > max_pio_num() ) {
        return -1;
    }
    if ( argc > 3 ) {
        val = simple_strtoul(argv[3], NULL, 0);
        if ( argv[1][0]=='s') {
            if ( configure_pio(pio, val?ZGPIO_CONFIG_INPUT:ZGPIO_CONFIG_OUTPUT) ) {
                printf("Fail to configure PIO %d as %s\n", pio, val?"Input":"Output");
                return -1;
            }
            printf("Configure PIO %d as %s\n", pio, val?"Input":"Output");
        } else if ( argv[1][0]=='w') {
            if (set_pio(pio, val?ZGPIO_LEVEL_HIGH:ZGPIO_LEVEL_LOW)) {
                printf("Fail to set PIO %d to %s\n", pio, val?"High":"Low");
                return -1;
            }
            printf("Set PIO %d to %s\n", pio, val?"High":"Low");
        }
    } else if ( argv[1][0]=='r' ) {
        if ( get_pio(pio, &val) ) {
            printf("Fail to read PIO %d\n", pio);
            return -1;
        }
        printf("PIO %d is %s\n", pio, val?"High":"Low");
    } else {
        return -1;
    }
    return 0;
}

U_BOOT_CMD(
	zgpio, 4, 0, do_zgpio,
    "GPIO access",
    "s <pio> <dir>  - PIO setup\n"
    "zgpio w <pio> <0|1>  - PIO output\n"
    "zgpio r <pio>        - PIO input\n"
    "zgpio d              - dump PIO registers\n"
);
#endif

