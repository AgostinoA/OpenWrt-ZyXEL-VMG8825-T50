/*
 * (C) Copyright 2000-2006
 * ARC International
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 * AA4 IDE intitialization code cribed from arc_cobalt
 *
 */


#include <common.h>

#ifdef CONFIG_CMD_IDE

static unsigned p_base_addr = (CONFIG_SYS_ATA_BASE_ADDR - 0x9000);
/* ------------------------------------------------------------------------- */

#define IDE_ID              (* (volatile unsigned long *) (p_base_addr + 0x00009000))
#define IDE_PIO             (* (volatile unsigned long *) (p_base_addr + 0x00009004))
#define IDE_STAT            (* (volatile unsigned long *) (p_base_addr + 0x00009008))
#define IDE_PIO_ACC         (* (volatile unsigned long *) (p_base_addr + 0x000090A0))
#define IDE_ERROR_REG       (* (volatile unsigned long *) (p_base_addr + 0x000090A4))
#define IDE_SEC_CNT         (* (volatile unsigned long *) (p_base_addr + 0x000090A8))
#define IDE_LBA_LOW         (* (volatile unsigned long *) (p_base_addr + 0x000090AC))
#define IDE_LBA_MID         (* (volatile unsigned long *) (p_base_addr + 0x000090B0))
#define IDE_LBA_HIGH        (* (volatile unsigned long *) (p_base_addr + 0x000090B4))
#define IDE_DEVICE_REG      (* (volatile unsigned long *) (p_base_addr + 0x000090B8))
#define IDE_CMD_REG         (* (volatile unsigned long *) (p_base_addr + 0x000090BC))
#define IDE_DEV_HEAD_CNTRL  (* (volatile unsigned long *) (p_base_addr + 0x000090D8))
#define IDE_ERROR_REG       (* (volatile unsigned long *) (p_base_addr + 0x000090A4))
#define IDE_ALT_STAT        (* (volatile unsigned long *) (p_base_addr + 0x000090D8))

void WaitForReady(void)
{
    // Bit 6 of the status register is the ready bit.
    // Command register when read acts as the status register
    unsigned long rdy;
    do
    {
        rdy = IDE_CMD_REG;
    }
    while(!((rdy >> 6) & 0x01));
}

void WaitForBusyClear(void)
{
    int i=0;
    // Bit 6 of the status register is the ready bit.
    // Command register when read acts as the status register
    unsigned long busy;
    do
    {
        busy = IDE_CMD_REG;
	if (i++ > 1000000)
	{
	    printf("timeout in WaitForBusyClear, IDE_CMD_REG=%x\n", IDE_CMD_REG);
	    break;
	}
    }
    while((busy >> 7) & 0x01);
}


void Delay_ms(int x)
{
	udelay (1000 * x);
}

#define PCMCIA_SHT(t)	((t & 0xff)<<16)	/* Strobe Hold	Time	*/
#define PCMCIA_SST(t)	((t & 0xff)<<8)	/* Strobe Setup Time	*/
#define PCMCIA_SL(t)    (t & 0xff) /* Strobe Length	*/

static unsigned cy(unsigned x)
{
    return (x * (CONFIG_SYS_HZ/1000000))/1000;
}

int ide_preinit(void)
{
    unsigned pio_setup, pio_length, pio_hold, pio_total, timings;
    
    printf("Resetting IDE device...\n");
    
    /* setup PIO mode 0 */
    pio_setup=cy(70);
    pio_length=cy(165);
    pio_hold=cy(30);
    pio_total=cy(600);

#   define UNDER (pio_setup + pio_length + pio_hold < pio_total)
    while (UNDER)
    {
	pio_length++;
	if (UNDER) pio_setup++;
	if (UNDER) pio_length++;
    }
    
    timings = PCMCIA_SHT(pio_hold)
	    | PCMCIA_SST(pio_setup)
	    | PCMCIA_SL (pio_length)
	    ;
    printf("pio mode 0 timings (%u, %u %u) = %x\n", pio_setup, pio_length, pio_hold, timings);

    

    // Set up the PIO Timing register
    IDE_PIO = timings;

    // Issue the hardware reset and wait for some cycle for the
    // reset to complete.
    // Bit 2 in the control register is the reset bit
    // Writing 0 to it will reset it
    IDE_STAT = 0x00;

    // wait for the reset to complete
    Delay_ms (5);

    // Clear the IDE bus reset-line
    IDE_STAT = 0x04;

    // Wait for Busy bit to clear
    WaitForBusyClear();


    // Now set the software reset bit in the IDE
    IDE_DEV_HEAD_CNTRL = 0x04;

    // Wait for 5 ms
    Delay_ms (5);

    // Clear the S/W reset
    IDE_DEV_HEAD_CNTRL = 0x00;

    // Wait for Busy bit to clear
    WaitForBusyClear();

    // Chack if the device is ready
    WaitForReady();

    // Set the head number as 0 and the device to be master
    // bits 3..0 of this register hold the head number (0..15) for a
    // transfer. The bit 4 is to be written 0 for access to the IDE
    // master device, 1 for access to the IDE slave device. The bits
    // 7..5 are fixed at 101B in the traditional interface.
    IDE_DEVICE_REG = 0x00;

    WaitForReady();

    // Wait for Busy bit to clear
    WaitForBusyClear();

    printf("IDE device reset OK.\n");
    return 0;
}

#endif
