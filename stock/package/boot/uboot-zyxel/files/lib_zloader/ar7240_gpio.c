#include <common.h>
#include <command.h>

#if defined(CONFIG_AR7240_GPIO) || defined(CONFIG_QCA955X_GPIO)
#include <asm/addrspace.h>

#ifdef CONFIG_AR7240_GPIO
  #include <ar7240_soc.h>
  #define MAX_GPIO_NUM		CONFIG_AR7240_MAX_GPIO_NUM
  #define REG_GPIO_OE		AR7240_GPIO_OE
  #define REG_GPIO_SET		AR7240_GPIO_SET
  #define REG_GPIO_CLEAR	AR7240_GPIO_CLEAR
  #define REG_GPIO_IN		AR7240_GPIO_IN
  #define REG_GPIO_OUT		AR7240_GPIO_OUT
  #define REG_GPIO_FUNC0	AR7240_GPIO_FUNC0
  #define REG_GPIO_FUNC		AR7240_GPIO_FUNC
  #define REG_GPIO_ENABLE0	AR7240_GPIO_ENABLE0
  #define REG_GPIO_ENABLE1	AR7240_GPIO_ENABLE1
  #define REG_GPIO_ENABLE4	AR7240_GPIO_ENABLE4
  #define REG_GPIO_ENABLE9	AR7240_GPIO_ENABLE9
  #define ATH_REG_READ		ar7240_reg_rd
  #define ATH_REG_WRITE		ar7240_reg_wr_nf
#elif defined(CONFIG_QCA955X_GPIO)
  #include <atheros.h>
  #define MAX_GPIO_NUM		CONFIG_QCA955X_MAX_GPIO_NUM
  #define REG_GPIO_OE		GPIO_OE_ADDRESS
  #define REG_GPIO_SET		GPIO_SET_ADDRESS
  #define REG_GPIO_CLEAR	GPIO_CLEAR_ADDRESS
  #define REG_GPIO_IN		GPIO_IN_ADDRESS
  #define REG_GPIO_OUT		GPIO_OUT_ADDRESS
  #define REG_GPIO_FUNC0	GPIO_OUT_FUNCTION0_ADDRESS
  #define REG_GPIO_FUNC		GPIO_FUNCTION_ADDRESS
  #define REG_GPIO_ENABLE0	GPIO_IN_ENABLE0_ADDRESS
  #define REG_GPIO_ENABLE1	GPIO_IN_ENABLE1_ADDRESS
  #define REG_GPIO_ENABLE4	GPIO_IN_ENABLE4_ADDRESS
  #define REG_GPIO_ENABLE9	GPIO_IN_ENABLE9_ADDRESS
  #define ATH_REG_READ		ath_reg_rd
  #define ATH_REG_WRITE		ath_reg_wr_nf
#endif
#include <zgpio.h>


int ar7240_configure_pio(int pio, int dir, unsigned char out_type)
{
    switch ( dir ) {
    case ZGPIO_CONFIG_OUTPUT:
    {   int shift;
        unsigned long reg = REG_GPIO_FUNC0;
        //printf("GPIO_FUNC0=0x%08X + 0x%X(shift %d bits)", REG_GPIO_FUNC0, (pio/4)*4, (pio % 4)*8);
        reg += ((pio / 4)*4);
        shift = (pio % 4)*8;
        ATH_REG_WRITE(REG_GPIO_OE, ATH_REG_READ(REG_GPIO_OE)&(~(1UL<<pio)));
        ATH_REG_WRITE(reg, ATH_REG_READ(reg)&(~(0xffUL<<shift)));
        if ( out_type ) {
            ATH_REG_WRITE(reg, ATH_REG_READ(reg)|((unsigned long)out_type<<shift));
        }
        break;
    }
    case ZGPIO_CONFIG_INPUT:
        ATH_REG_WRITE(REG_GPIO_OE, ATH_REG_READ(REG_GPIO_OE)|(1UL<<pio));
        /* TODO: clear GPIO_IN_ENABLEn (n=0~9)*/
        break;
    default:
        return -2;
    }
    udelay(1000);
    return 0;
}

/*----------------------------------------------
 * GPIO export functions
 */
int configure_pio(int pio, int dir)
{
    return ar7240_configure_pio(pio, dir, 0);
}

int set_pio(int pio, int level)
{
    if ( pio<0 || pio >MAX_GPIO_NUM ) {
        return -1;
    }
#if 1
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
#if 1
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
}
#endif

#endif

