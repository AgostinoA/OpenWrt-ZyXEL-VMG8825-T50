/*
 ***************************************************************************
 * Ralink Tech Inc.
 * 4F, No. 2 Technology 5th Rd.
 * Science-based Industrial Park
 * Hsin-chu, Taiwan, R.O.C.
 *
 * (c) Copyright, Ralink Technology, Inc.
 *
 *  This program is free software; you can redistribute  it and/or modify it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License along
 *  with this program; if not, write  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *
 ***************************************************************************
 */
#include <common.h>
#include <command.h>

#ifdef CONFIG_RT2880_GPIO
#include "rt2880_gpio.h"
#include <zgpio.h>

#define MAX_GPIO_NUM        31

/*----------------------------------------------
 * GPIO export functions
 */
int configure_pio(int pio, int dir)
{
    unsigned long tmpCtrl, tmpOE;
    volatile unsigned long *gpioctrl;
    int gpioctrl_bits;

    if ( pio<0 || pio >MAX_GPIO_NUM ) {
        return -1;
    }
    gpioctrl_bits = pio;
    if ( pio > 15 ) {
        gpioctrl_bits -= 16;
        gpioctrl = (volatile unsigned long *)RALINK_REG_PIO3116DIR;
    } else {
        gpioctrl = (volatile unsigned long *)RALINK_REG_PIODIR;
    }
    /* clear: default to set GPIO as input pin */
    tmpCtrl = le32_to_cpu(*gpioctrl)&(~(0x3<<(gpioctrl_bits*2)));
    tmpOE   = le32_to_cpu(*(volatile unsigned long *)(RALINK_REG_GPIOOE))&(~(0x1<<pio));
    switch ( dir ) {
    case ZGPIO_CONFIG_OUTPUT:
        tmpCtrl |= 0x1<<(gpioctrl_bits*2);
        tmpOE   |= 0x1<<pio;
        break;
    case ZGPIO_CONFIG_INPUT:
        /* nothing need to do */
        break;
    default:
        return -2;
    }
    *gpioctrl = cpu_to_le32(tmpCtrl);
    *(volatile u32 *)(RALINK_REG_GPIOOE) = cpu_to_le32(tmpOE);
    return 0;
}

int set_pio(int pio, int level)
{
    unsigned long tmp;
    if ( pio<0 || pio >MAX_GPIO_NUM ) {
        return -1;
    }
    tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIODATA));
    switch (level) {
    case ZGPIO_LEVEL_LOW:
        tmp &= (~(1<<pio));
        break;
    case ZGPIO_LEVEL_HIGH:
        tmp |= (1<<pio);
        break;
    default:
        return -2;
    }
    *(volatile u32 *)(RALINK_REG_PIODATA) = cpu_to_le32(tmp);
    return 0;
}

int get_pio(int pio, int *level)
{
    if ( pio<0 || pio >MAX_GPIO_NUM ) {
        return -1;
    }
    *level = (le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIODATA))&(1<<pio))?ZGPIO_LEVEL_HIGH:ZGPIO_LEVEL_LOW;
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

