/*
 * (C) Copyright 2006
 * Mindspeed Technologies, Inc. <www.mindspeed.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <common.h>
#include <asm/arch/hardware.h>
#include <asm/arch/bsp.h>

/*
* SoC_cs_cfg - configure Chip Select settings
*
* cs - chip select id
*
* enable - enable or disable the CS
*	1 = enable
*	0 = disable
*
* cfg - chip select configuration, ignored if enable = 0
*
*/
int SoC_cs_cfg(int cs, int enable, struct cs_cfg *cfg)
{
	u32 segment_size = 0;
	u32 baseaddr = 0; 
	u32 ext_baseaddr = 0;

	if ((cs != EXP_CSSD0) && (cs != EXP_CSSD1) && (cs != EXP_CSBOOT) &&
	    (cs != EXP_CSP0) && (cs != EXP_CSP1) && (cs != EXP_CSP2) &&
	    (cs != SDR_CSSD0) && (cs != SDR_CSSD1))
		goto err;

	if (enable == CS_DISABLE) {
		/* Disable the CS and exit */
		*(volatile u32 *) ASD_CSE &= ~(1 << cs);
		goto out;
	}

	if (cfg->memtype == CS_MEMTYPE_SDRAM) {
		/* Other CS don't support SDRAM */
		if ((cs != EXP_CSSD0) && (cs != SDR_CSSD0))
			goto err;
	}

	if ((cs == EXP_CSSD0) || (cs == EXP_CSSD1) || (cs == SDR_CSSD0) || (cs == SDR_CSSD1)) {
		baseaddr = cfg->baseaddr & 0x07FFFFFF;
		ext_baseaddr = cfg->baseaddr & 0xF8000000;

		if (ext_baseaddr) {
			/* Extended Memory */

			if ((ext_baseaddr & 0xc0000000) != 0x80000000)
				goto out;

			switch (cfg->size) {
			case 0x100000: segment_size = 0x8; /* 1MB */
				break;	

			case 0x200000: segment_size = 0x9; /* 2MB */
				break;	

			case 0x400000: segment_size = 0xa; /* 4MB */
				break;	

			case 0x800000: segment_size = 0xb;/* 8MB */
				break;	

			case 0x1000000: segment_size = 0xc;/* 16MB */
				break;	

			case 0x2000000: segment_size = 0xd; /* 32MB */
				break;	

			default:
				cfg->size = 0x4000000;
			case 0x4000000:
				segment_size = 0xe; /* 64MB */
				
				break;	

			case 0x8000000: segment_size = 0xf; /* 128MB */
				break;	

			case 0x10000000: segment_size = 0x0; /* 256MB */
				break;	

			case 0x20000000: segment_size = 0x1; /* 512MB */
				break;	

			case 0x40000000: segment_size = 0x2; /* 1Gb */
				break;	
			}

			/* Make sure the base address is aligned on size boundary */
			baseaddr &= ~(cfg->size - 1);

		} else {
			/* Low Memory */

			switch (cfg->size) {
			case 0x10000: segment_size = 0x0; /* 64KB */
				break;	

			case 0x20000: segment_size = 0x5; /* 128KB */
				break;	

			case 0x40000: segment_size = 0x6; /* 256KB */
				break;	

			case 0x80000: segment_size = 0x7; /* 512KB */
				break;	

			case 0x100000: segment_size = 0x8; /* 1MB */
				break;	

			case 0x200000: segment_size = 0x9; /* 2MB */
				break;	

			case 0x400000: segment_size = 0xa; /* 4MB */
				break;	

			case 0x800000: segment_size = 0xb; /* 8MB */
				break;	

			case 0x1000000: segment_size = 0xc; /* 16MB */
				break;	

			case 0x2000000: segment_size = 0xd; /* 32MB */
				break;	

			default:
			case 0x4000000:
				segment_size = 0xe; /* 64MB */
				cfg->size = 0x40000000;
				break;	

			case 0x8000000: segment_size = 0xf; /* 128MB */
				break;
			}

			/* Make sure the base address is aligned on size boundary */
			baseaddr &= ~(cfg->size - 1);
		}
	}
	
	switch (cs) {
	case EXP_CSSD0:

		*(volatile u32 *) ASD_MBA_EXP_CSSD0 = ((baseaddr >> 16) << 4) | segment_size;
		*(volatile u32 *) ASD_EXA_EXP_CSSD0 = (ext_baseaddr >> 27);

		if (cfg->memtype == CS_MEMTYPE_SDRAM) {
			*(volatile u32 *) SDC0_CSSD0_CFG = (((u32)cfg->memtype & 0x1) << 9);

			*(volatile u32 *) SDC0_SDRAM_CFG1 = (((u32)cfg->tras & 0x7) << 13) |
						(((u32)cfg->trc & 0xf) << 9) |
						(((u32)cfg->trcd & 0x7) << 6) |
						(((u32)cfg->trp & 0x7) << 3) |
						((u32)cfg->cl & 0x7);

			*(volatile u32 *) SDC0_SDRAM_REFRESH = (u32)cfg->refcnt & 0xfff;

			*(volatile u32 *) SDC0_SDRAM_POWERON = (u32)cfg->pwroncnt & 0xffff;

			*(volatile u32 *) SDC0_SDRAM_CFG2 = (((u32)cfg->memchip_dtype & 0x3) << 11) |
						(((u32)cfg->twr & 0x3) << 8) |
						(1 << 7) |
						(1 << 6) |
						(((u32)cfg->buswidth & 0x1) << 5) |
						(((u32)cfg->tmrd & 0x7) << 2) |
						((u32)cfg->trrd & 0x3);
		} else {
			*(volatile u32 *) SDC0_CSSD0_CFG = (((u32)cfg->buswidth & 0x3) << 11) |
					((((u32)cfg->addrsetup >> 2) & 0x1) << 10) |
					(((u32)cfg->memtype & 0x1) << 9) |
					(((u32)cfg->addrsetup & 0x3) << 7) |
					(((u32)cfg->level & 0x1) << 6) |
					(((u32)cfg->dqm_mode & 0x1) << 5) |
					(((u32)cfg->cmdwidth & 0xf) << 1);
		}

		*(volatile u32 *) ASD_CSE |= (1 << EXP_CSSD0);

		break;

	case EXP_CSSD1: 
		*(volatile u32 *) ASD_MBA_EXP_CSSD1 = ((baseaddr >> 16) << 4) | segment_size;
		*(volatile u32 *) ASD_EXA_EXP_CSSD1 = (ext_baseaddr >> 27);

		*(volatile u32 *) SDC0_CSSD1_CFG = (((u32)cfg->buswidth & 0x3) << 11) |
					((((u32)cfg->addrsetup >> 2) & 0x1) << 10) |
					(((u32)cfg->memtype & 0x1) << 9) |
					(((u32)cfg->addrsetup & 0x3) << 7) |
					(((u32)cfg->level & 0x1) << 6) |
					(((u32)cfg->dqm_mode & 0x1) << 5) |
					(((u32)cfg->cmdwidth & 0xf) << 1);

		*(volatile u32 *) ASD_CSE |= (1 << EXP_CSSD1);
	
		break;

	case EXP_CSBOOT:
		*(volatile u32 *)SDC0_CSBOOT_CFG = (((u32)cfg->buswidth & 0x3) << 11) |
					((((u32)cfg->addrsetup >> 2) & 0x1) << 10) |
					(((u32)cfg->memtype & 0x1) << 9) |
					(((u32)cfg->addrsetup & 0x3) << 7) |
					(((u32)cfg->level & 0x1) << 6) |
					(((u32)cfg->dqm_mode & 0x1) << 5) |
					(((u32)cfg->cmdwidth & 0xf) << 1);
		
		*(volatile u32 *)ASD_CSE |= (1 << EXP_CSBOOT);
		
		break;

	case EXP_CSP0:
		*(volatile u32 *)SDC0_CSP0_CFG = (((u32)cfg->buswidth & 0x3) << 11) |
					((((u32)cfg->addrsetup >> 2) & 0x1) << 10) |
					(((u32)cfg->memtype & 0x1) << 9) |
					(((u32)cfg->addrsetup & 0x3) << 7) |
					(((u32)cfg->level & 0x1) << 6) |
					(((u32)cfg->dqm_mode & 0x1) << 5) |
					(((u32)cfg->cmdwidth & 0xf) << 1);
		
		*(volatile u32 *)ASD_CSE |= (1 << EXP_CSP0);

		break;

	case EXP_CSP1:
		*(volatile u32 *)SDC0_CSP1_CFG = (((u32)cfg->buswidth & 0x3) << 11) |
					((((u32)cfg->addrsetup >> 2) & 0x1) << 10) |
					(((u32)cfg->memtype & 0x1) << 9) |
					(((u32)cfg->addrsetup & 0x3) << 7) |
					(((u32)cfg->level & 0x1) << 6) |
					(((u32)cfg->dqm_mode & 0x1) << 5) |
					(((u32)cfg->cmdwidth & 0xf) << 1);

		*(volatile u32 *)ASD_CSE |= (1 << EXP_CSP1);
		
		break;

	case EXP_CSP2:
		*(volatile u32 *)SDC0_CSP2_CFG = (((u32)cfg->buswidth & 0x3) << 11) |
					((((u32)cfg->addrsetup >> 2) & 0x1) << 10) |
					(((u32)cfg->memtype & 0x1) << 9) |
					(((u32)cfg->addrsetup & 0x3) << 7) |
					(((u32)cfg->level & 0x1) << 6) |
					(((u32)cfg->dqm_mode & 0x1) << 5) |
					(((u32)cfg->cmdwidth & 0xf) << 1);

		*(volatile u32 *)ASD_CSE |= (1 << EXP_CSP2);
		
		break;
	
	case SDR_CSSD0:
		*(volatile u32 *) ASD_MBA_SDR_CSSD0 = ((baseaddr >> 16) << 4) | segment_size;
		*(volatile u32 *) ASD_EXA_SDR_CSSD0 = (ext_baseaddr >> 27);

		if (cfg->memtype == CS_MEMTYPE_SDRAM) {

			*(volatile u32 *) SDC1_CSSD0_CFG = (((u32)cfg->memtype & 0x1) << 9);

			*(volatile u32 *) SDC1_SDRAM_CFG1 = (((u32)cfg->tras & 0x7) << 13) |
						(((u32)cfg->trc & 0xf) << 9) |
						(((u32)cfg->trcd & 0x7) << 6) |
						(((u32)cfg->trp & 0x7) << 3) |
						((u32)cfg->cl & 0x7);

			*(volatile u32 *) SDC1_SDRAM_REFRESH = (u32)cfg->refcnt & 0xfff;

			*(volatile u32 *) SDC1_SDRAM_POWERON = (u32)cfg->pwroncnt & 0xffff;

			*(volatile u32 *) SDC1_SDRAM_CFG2 = (((u32)cfg->memchip_dtype & 0x3) << 11) |
						(((u32)cfg->twr & 0x3) << 8) |
						(1 << 7) |
						(1 << 6) |
						(((u32)cfg->buswidth & 0x1) << 5) |
						(((u32)cfg->tmrd & 0x7) << 2) |
						((u32)cfg->trrd & 0x3);
		} else {
			*(volatile u32 *) SDC1_CSSD0_CFG = (((u32)cfg->buswidth & 0x3) << 11) |
					((((u32)cfg->addrsetup >> 2) & 0x1) << 10) |
					(((u32)cfg->memtype & 0x1) << 9) |
					(((u32)cfg->addrsetup & 0x3) << 7) |
					(((u32)cfg->level & 0x1) << 6) |
					(((u32)cfg->dqm_mode & 0x1) << 5) |
					(((u32)cfg->cmdwidth & 0xf) << 1);
		}

		*(volatile u32 *)ASD_CSE |= (1 << SDR_CSSD0);

		break;

	case SDR_CSSD1:
		*(volatile u32 *) ASD_MBA_SDR_CSSD1 = ((baseaddr >> 16) << 4) | segment_size;
		*(volatile u32 *) ASD_EXA_SDR_CSSD1 = (ext_baseaddr >> 27);

		*(volatile u32 *) SDC1_CSSD1_CFG = (((u32)cfg->buswidth & 0x3) << 11) |
					((((u32)cfg->addrsetup >> 2) & 0x1) << 10) |
					(((u32)cfg->memtype & 0x1) << 9) |
					(((u32)cfg->addrsetup & 0x3) << 7) |
					(((u32)cfg->level & 0x1) << 6) |
					(((u32)cfg->dqm_mode & 0x1) << 5) |
					(((u32)cfg->cmdwidth & 0xf) << 1);

		*(volatile u32 *)ASD_CSE |= (1 << SDR_CSSD1);
	
		break;
	}

out:
	return 0;

err:
	return -1;
}


int SoC_high_mem_cfg (int cs)
{
	switch (cs) {
	case EXP_CSSD0:
		*(volatile u32 *)ASD_CSE &= ~((1 << 7) | (1 << 11));

		break;

	case EXP_CSSD1:
		*(volatile u32 *)ASD_CSE |= (1 << 7);
		*(volatile u32 *)ASD_CSE &= ~(1 << 11);

		break;

	case SDR_CSSD0:
		*(volatile u32 *)ASD_CSE &= ~(1 << 7);
		*(volatile u32 *)ASD_CSE |= (1 << 11);

		break;

	case SDR_CSSD1:
		*(volatile u32 *)ASD_CSE |= (1 << 7) | (1 << 11);

		break;

	default:
		goto err;
	}

	return 0;

err:
	return -1;
}


int SoC_mem_divider_cfg (u32 address, int sdc)
{
	switch (sdc) {
	case BELLOW_MEM_SDC0:
		*(volatile u32 *)ASD_CSE &= ~(1 << 12);

		break;

	case BELLOW_MEM_SDC1:
		*(volatile u32 *)ASD_CSE |= (1 << 12);
		break;

	default:
		goto err;
	}

	*(volatile u32 *)ASD_MEM_DIVIDER = (address & 0xFF800000) >> 16;

	return 0;

err:
	return -1;
}

/*
* SoC_pll_cfg - used to configure ARM and AMBA bus clock frequencies
*
* mode - ARM clock mode,
*	1 = async, independent ARM and AMBA bus clock frequencies (PLL2 used for bus clock).
*	0 = sync, AMBA bus clock half ARM clock frequency (PLL2 not used)
*
* arm_clk - ARM clock frequency in Hz
*
* bus_clk - AMBA BUS clock frequency in Hz
*
*/
int SoC_pll_cfg (int mode, unsigned int arm_clk, unsigned int bus_clk)
{
	volatile u32 delay_count;
	u32 clkf;
	u32 i;

	if (mode == CLK_MODE_ASYNC) {
		/* set ARM async clock mode */
		asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));
		i |= 0xC0000000;
		asm ("mcr p15, 0, %0, c1, c0, 0": :"r" (i));

		/* async mode */
		clkf = (4 * bus_clk) / CFG_REFCLKFREQ;

		/* bus setup */
		/* set PLL into BYPASS mode */
		*(volatile u32 *)CLKCORE_AMBA_PLL |= PLL_BYPASS;

		/* wait 500us for PLL to lock */
		delay_count = 1000;
		while (delay_count--);

		/* Disable the PLL, by writing PLL Control Register bit 25 = 1. */
		*(volatile u32 *)CLKCORE_AMBA_PLL |= PLL_POWER; 
	
		/* Program the PLL to the desired value and enable the PLL, by writing PLL Control Register fields W, X, and Y,  */
		*(volatile u32 *)CLKCORE_AMBA_PLL = PLL_BYPASS | PLL_POWER | (clkf & 0x7f);

		/* and writing bit 25 = 0. */
		*(volatile u32 *)CLKCORE_AMBA_PLL = PLL_MUXSEL | (clkf & 0x7f);
	} else {
		/* set ARM sync clock mode */
		asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));
		i |= 0x40000000;
		asm ("mcr p15, 0, %0, c1, c0, 0": :"r" (i));
	}

	/* ARM setup */
	clkf = (2 * arm_clk) / CFG_REFCLKFREQ;
	
	/* set PLL into BYPASS mode */
	*(volatile u32 *)CLKCORE_ARM_PLL |= PLL_BYPASS;

	/* wait 500us for PLL to lock */
	delay_count = 1000;
	while (delay_count--);

	/* Disable the PLL, by writing PLL Control Register bit 25 = 1. */
	*(volatile u32 *)CLKCORE_ARM_PLL |= PLL_POWER; 
	
	/* Program the PLL to the desired value and enable the PLL, by writing PLL Control Register fields W, X, and Y */
	*(volatile u32 *)CLKCORE_ARM_PLL = PLL_BYPASS | PLL_POWER | (clkf & 0x7f); 

	/*and writing bit 25 = 0. */
	*(volatile u32 *)CLKCORE_ARM_PLL &= ~PLL_POWER; 

	/* Take the PLL out of bypass mode, by writing PLL Control Register bit 24 = 0. */
	*(volatile u32 *)CLKCORE_ARM_PLL &= ~PLL_BYPASS;

	// Ref: 
	// 1) PLL Initialization Procedure  (82XXX-ERR-001-A.pdf )
	// 2) M825xx PLL Registers chapter.pdf

	return 0;
}

/*
* SoC_gpio_cfg - configure GPIO pins as input or output pins
*
* gpio - gpio pin
*
* mode - gpio pin mode
*	GPIO_TYPE_OUTPUT = output
*	GPIO_TYPE_INPUT = input
*
*/
int SoC_gpio_cfg(int gpio, int mode)
{

	if ((gpio < 0) || (gpio > 31))
		goto err;

	switch (mode) {
	case GPIO_TYPE_INPUT:
		*(volatile u32 *) GPIO_OUTPUT_ENABLE &= ~(1 << gpio);

		break;

	case GPIO_TYPE_OUTPUT:
		if ((gpio == 18) || (gpio == 19))
			goto err;

		*(volatile u32 *) GPIO_OUTPUT_ENABLE |= 1 << gpio;

		break;

	default:
		goto err;
		break;
	}

	return 0;

err:
	return -1;
}

int SoC_ioctrl_cfg(int resource, int enable)
{
	u32 bitmask;
	u32 val;

	switch (resource) {
	case IOCTRL_SPI_BUS:
		bitmask = (0x3 << 4);
		break;

	case IOCTRL_UART0:
		bitmask = (0x3 << 12);
		break;

	case IOCTRL_UART1:
		bitmask = (0x3 << 14);
		break;

	case IOCTRL_EXPA21_A22:
		bitmask = (0x3 << 24);
		break;

	default:
		goto err;
	}

	if (enable) {
		do {
			val = *(volatile u32 *)GPIO_IOCTRL | bitmask;
			*(volatile u32 *)GPIO_LOCK = 0x55555555;	/* remove lock */
			*(volatile u32 *)GPIO_IOCTRL = val;
		} while ((*(volatile u32 *)GPIO_IOCTRL & bitmask) != bitmask);
	} else {
		do {
			val = *(volatile u32 *)GPIO_IOCTRL & ~bitmask;
			*(volatile u32 *)GPIO_LOCK = 0x55555555;	/* remove lock */
			*(volatile u32 *)GPIO_IOCTRL = val;
		} while ((*(volatile u32 *)GPIO_IOCTRL & bitmask));
	}

	return 0;

err:
	return -1;
}

