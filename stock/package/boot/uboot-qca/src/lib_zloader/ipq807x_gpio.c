#include <common.h>
#include <command.h>

#include <asm/arch-qca-common/iomap.h>
#include <asm/arch-qca-common/gpio.h>
#include <asm/io.h>

#define MAX_GPIO_NUM		0xFF //?
#define REG_GPIO_OE		    AR7240_GPIO_OE
#define REG_GPIO_SET		AR7240_GPIO_SET
#define REG_GPIO_CLEAR	    AR7240_GPIO_CLEAR
#define REG_GPIO_IN		    AR7240_GPIO_IN
#define REG_GPIO_OUT		AR7240_GPIO_OUT
#define REG_GPIO_FUNC0	    AR7240_GPIO_FUNC0
#define REG_GPIO_FUNC		AR7240_GPIO_FUNC
#define REG_GPIO_ENABLE0	AR7240_GPIO_ENABLE0
#define REG_GPIO_ENABLE1	AR7240_GPIO_ENABLE1
#define REG_GPIO_ENABLE4	AR7240_GPIO_ENABLE4
#define REG_GPIO_ENABLE9	AR7240_GPIO_ENABLE9
#define ATH_REG_READ		ar7240_reg_rd
#define ATH_REG_WRITE		ar7240_reg_wr_nf
#include <zgpio.h>



/*----------------------------------------------
 * GPIO export functions
 */

/*
/*******************************************************
Function description: configure GPIO functinality
Arguments :
unsigned int gpio - Gpio number
unsigned int func - Functionality number
unsigned int dir  - direction 0- i/p, 1- o/p
unsigned int pull - pull up/down, no pull range(0-3)
unsigned int drvstr - range (0 - 7)-> (2- 16)MA steps of 2
unsigned int oe - 0 - Disable, 1- Enable.
void gpio_tlmm_config(unsigned int gpio, unsigned int func,
                      unsigned int out, unsigned int pull,
                      unsigned int drvstr, unsigned int oe)
*/
int configure_pio(int pio, int dir)
{
    printf("Set GPIO %d to %d\n", pio, dir);
    //gpio_tlmm_config(pio, 1, dir, GPIO_NO_PULL, GPIO_10MA, GPIO_OE_ENABLE);
    return 0;
}

int set_pio(int pio, int level)
{
    if ( pio<0 || pio >MAX_GPIO_NUM ) {
        return -1;
    }
#if 0
    if ( ATH_REG_READ(REG_GPIO_OE) & (1UL<<pio) ) { /* input */
        /* GPIO configure as input pin */
        return -3;
    }
    switch (level) {
    case ZGPIO_LEVEL_LOW:
        ATH_REG_WRITE(REG_GPIO_CLEAR, 1UL<<pio);
        break;
    case ZGPIO_LEVEL_HIGH:
        ATH_REG_WRITE(REG_GPIO_SET, 1UL<<pio);
        break;
    default:
        return -2;
    }
#endif
    return 0;
}

int get_pio(int pio, int *level)
{
    unsigned long value;
    if ( pio<0 || pio >MAX_GPIO_NUM ) {
        return -1;
    }
#if 0
    if ( ATH_REG_READ(REG_GPIO_OE) & (1UL<<pio) ) { /* input */
        value = ATH_REG_READ(REG_GPIO_IN);
    } else { /* output */
        value = ATH_REG_READ(REG_GPIO_OUT);
    }
    *level = (value&(1UL<<pio))?ZGPIO_LEVEL_HIGH:ZGPIO_LEVEL_LOW;
#endif
    return 0;
}

int max_pio_num(void)
{
    return MAX_GPIO_NUM;
}

#ifdef CONFIG_ZGPIO_CMD
void dump_pio_regs(void)
{
#if 0
    int i;
    printf("GPIO_OE        =0x%08X\n", ATH_REG_READ(REG_GPIO_OE));
    printf("GPIO_IN        =0x%08X\n", ATH_REG_READ(REG_GPIO_IN));
    printf("GPIO_OUT       =0x%08X\n", ATH_REG_READ(REG_GPIO_OUT));
    printf("GPIO_FUNCTION  =0x%08X\n", ATH_REG_READ(REG_GPIO_FUNC));
    for (i=0; i<6; i++) {
        printf("GPIO_OUT_FUN%d  =0x%08X\n", i, ATH_REG_READ(REG_GPIO_FUNC0+i*4));
    }
    printf("GPIO_IN_ENABLE0=0x%08X\n", ATH_REG_READ(REG_GPIO_ENABLE0));
    printf("GPIO_IN_ENABLE1=0x%08X\n", ATH_REG_READ(REG_GPIO_ENABLE1));
    printf("GPIO_IN_ENABLE4=0x%08X\n", ATH_REG_READ(REG_GPIO_ENABLE4));
    printf("GPIO_IN_ENABLE9=0x%08X\n", ATH_REG_READ(REG_GPIO_ENABLE9));
#endif
}
#endif

