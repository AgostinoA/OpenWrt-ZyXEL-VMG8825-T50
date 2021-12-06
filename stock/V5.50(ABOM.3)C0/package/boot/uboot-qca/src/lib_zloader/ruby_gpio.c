#include <common.h>
#include <command.h>

#ifdef CONFIG_RUBY_GPIO
#include <asm/io.h>
#include <asm/global_data.h>
#include <asm/uboot-arc.h>
#include <asm/arcregs.h>
#include <asm/arch/platform.h>

#include <zgpio.h>

#define MAX_GPIO_NUM        RUBY_GPIO_MAX
extern void gpio_config(u32 pin, u32 cfg);
extern void gpio_output(u32 pin, u32 state);
extern u32 gpio_input(u32 pin);

/*----------------------------------------------
 * GPIO export functions
 */
int configure_pio(int pio, int dir)
{
    if ( pio<0 || pio >MAX_GPIO_NUM ) {
        return -1;
    }

    switch ( dir ) {
    case ZGPIO_CONFIG_OUTPUT:
        gpio_config(pio, RUBY_GPIO_MODE_OUTPUT);
        break;
    case ZGPIO_CONFIG_INPUT:
        gpio_config(pio, RUBY_GPIO_MODE_INPUT);
        break;
    default:
        return -2;
    }
    return 0;
}

int set_pio(int pio, int level)
{
    if ( pio<0 || pio >MAX_GPIO_NUM ) {
        return -1;
    }

    switch (level) {
    case ZGPIO_LEVEL_LOW:
	gpio_output(pio, 0);
        break;
    case ZGPIO_LEVEL_HIGH:
	gpio_output(pio, 1);
        break;
    default:
        return -2;
    }
    return 0;
}

int get_pio(int pio, int *level)
{
    if ( pio<0 || pio >MAX_GPIO_NUM ) {
        return -1;
    }
    *level = gpio_input(pio)?ZGPIO_LEVEL_HIGH:ZGPIO_LEVEL_LOW;
    return 0;
}

int max_pio_num(void)
{
    return MAX_GPIO_NUM;
}

#ifdef CONFIG_ZGPIO_CMD
void dump_pio_regs(void)
{
    puts("Not support!");
}
#endif

#endif

