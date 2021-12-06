#include <common.h>
#include <command.h>

#include <asm/arch/rt_mmap.h>

#define SOFTRES_REG (RALINK_SYSCTL_BASE + 0x0034)
#define GORESET		(0x01)

unsigned long mips_cpu_feq;
unsigned long mips_bus_feq;

void _machine_restart(void)
{
#if defined(RT6855A_FPGA_BOARD) || defined(RT6855A_ASIC_BOARD)
    ra_outl(RALINK_TIMER_BASE + 0x2c, 0x1);		//timer3 load value
    ra_or(RALINK_TIMER_BASE, (1 << 5) | (1 << 25));	//timer3 enabled as watchdog
#else
    *(volatile unsigned int*)(SOFTRES_REG) = GORESET;
#endif
}

void rt2880_freq_calculate(void)
{
	u32 reg;
#ifdef ASIC_BOARD
	u8	clk_sel, clk_sel2;
#endif
	reg = RALINK_REG(RT2880_SYSCFG_REG);
		
	/* 
	 * CPU_CLK_SEL (bit 21:20)
	 */
#ifdef RT2880_FPGA_BOARD
	mips_cpu_feq = 25 * 1000 *1000;
	mips_bus_feq = mips_cpu_feq/2;
#elif defined (RT2883_FPGA_BOARD) || defined (RT3052_FPGA_BOARD) || defined (RT3352_FPGA_BOARD) || defined (RT5350_FPGA_BOARD)
	mips_cpu_feq = 40 * 1000 *1000;
	mips_bus_feq = mips_cpu_feq/3;
#elif defined (RT6855A_FPGA_BOARD)
	mips_cpu_feq = 50 * 1000 *1000;
	mips_bus_feq = mips_cpu_feq/2;
#elif defined (RT3883_FPGA_BOARD)
	mips_cpu_feq = 40 * 1000 *1000;
	mips_bus_feq = mips_cpu_feq;
#elif defined (RT6855_FPGA_BOARD) || defined (RT6352_FPGA_BOARD) || defined (RT71100_FPGA_BOARD)
	/* FIXME */
	mips_cpu_feq = 50 * 1000 *1000;
	mips_bus_feq = mips_cpu_feq/4;
#elif defined (RT2883_ASIC_BOARD) 
	clk_sel = (reg>>20) & 0x03;
	switch(clk_sel) {
		case 0:
			mips_cpu_feq = (380*1000*1000);
			break;
		case 1:
			mips_cpu_feq = (400*1000*1000);
			break;
		case 2:
			mips_cpu_feq = (420*1000*1000);
			break;
		case 3:
			mips_cpu_feq = (430*1000*1000);
			break;
	}
	mips_bus_feq = mips_cpu_feq/2;
#elif defined(RT3052_ASIC_BOARD)
#if defined(RT3350_ASIC_BOARD) 
	//MA10 is floating
	mips_cpu_feq = (320*1000*1000);
#else
        clk_sel = (reg>>18) & 0x01;
        switch(clk_sel) {
                case 0:
                        mips_cpu_feq = (320*1000*1000);
                        break;
                case 1:
                        mips_cpu_feq = (384*1000*1000);
                        break;
        }
#endif
        mips_bus_feq = mips_cpu_feq / 3;
#elif defined(RT3352_ASIC_BOARD)
	clk_sel = (reg>>8) & 0x01;
	switch(clk_sel) {
		case 0:
			mips_cpu_feq = (384*1000*1000);
			break;
		case 1:
			mips_cpu_feq = (400*1000*1000);
			break;
	}
	mips_bus_feq = (133*1000*1000);
#elif defined(RT5350_ASIC_BOARD)
	clk_sel2 = (reg>>10) & 0x01;
	clk_sel = ((reg>>8) & 0x01) + (clk_sel2 * 2);
	switch(clk_sel) {
		case 0:
			mips_cpu_feq = (360*1000*1000);
			mips_bus_feq = (120*1000*1000);
			break;
		case 1:
			//reserved
			break;
		case 2:
			mips_cpu_feq = (320*1000*1000);
			mips_bus_feq = (80*1000*1000);
			break;
		case 3:
			mips_cpu_feq = (300*1000*1000);
			mips_bus_feq = (100*1000*1000);
			break;
	}
#elif defined(RT6855_ASIC_BOARD)
	mips_cpu_feq = (400*1000*1000);
	mips_bus_feq = (133*1000*1000);
#elif defined (RT6855A_ASIC_BOARD)
	/* FPGA is 25/32Mhz
	 * ASIC RT6856/RT6856A: DDR(0): 233.33, DDR(1): 175, SDR: 140
	 *      RT6855/RT6855A: DDR(0): 166.67, DDR(1): 125, SDR: 140 */
	reg = RALINK_REG(RT2880_SYSCFG_REG);
	if ((reg & (1 << 25)) == 0) { /* SDR */
		if ((reg & (1 << 9)) != 0)
			mips_cpu_feq = (560*1000*1000);
		else {
			if ((reg & (1 << 26)) != 0)	
				mips_cpu_feq = (560*1000*1000);
			else
				mips_cpu_feq = (420*1000*1000);
		}	
		mips_bus_feq = (140*1000*1000);
	} else { /* DDR */
		if ((reg & (1 << 9)) != 0) {
			mips_cpu_feq = (700*1000*1000);
			if ((reg & (1 << 26)) != 0)
				mips_bus_feq = (175*1000*1000);
			else
				mips_bus_feq = 233333333;
		} else {
			mips_cpu_feq = (500*1000*1000);
			if ((reg & (1 << 26)) != 0)
				mips_bus_feq = (125*1000*1000);
			else
				mips_bus_feq = 166666667;
		}
	}
#elif defined(RT6352_ASIC_BOARD)
	/* FIXME */
	mips_cpu_feq = (600*1000*1000);
	mips_bus_feq = (133*1000*1000);
#elif defined(RT71100_ASIC_BOARD)
	/* FIXME */
	mips_cpu_feq = (800*1000*1000);
	mips_bus_feq = (133*1000*1000);
#elif defined (RT3883_ASIC_BOARD) 
	clk_sel = (reg>>8) & 0x03;
	switch(clk_sel) {
		case 0:
			mips_cpu_feq = (250*1000*1000);
			break;
		case 1:
			mips_cpu_feq = (384*1000*1000);
			break;
		case 2:
			mips_cpu_feq = (480*1000*1000);
			break;
		case 3:
			mips_cpu_feq = (500*1000*1000);
			break;
	}
#if defined (CFG_ENV_IS_IN_SPI)
	if ((reg>>17) & 0x1) { //DDR2
		switch(clk_sel) {
			case 0:
				mips_bus_feq = (125*1000*1000);
				break;
			case 1:
				mips_bus_feq = (128*1000*1000);
				break;
			case 2:
				mips_bus_feq = (160*1000*1000);
				break;
			case 3:
				mips_bus_feq = (166*1000*1000);
				break;
		}
	}
	else {
		switch(clk_sel) {
			case 0:
				mips_bus_feq = (83*1000*1000);
				break;
			case 1:
				mips_bus_feq = (96*1000*1000);
				break;
			case 2:
				mips_bus_feq = (120*1000*1000);
				break;
			case 3:
				mips_bus_feq = (125*1000*1000);
				break;
		}
	}
#elif defined ON_BOARD_SDR
	switch(clk_sel) {
		case 0:
			mips_bus_feq = (83*1000*1000);
			break;
		case 1:
			mips_bus_feq = (96*1000*1000);
			break;
		case 2:
			mips_bus_feq = (120*1000*1000);
			break;
		case 3:
			mips_bus_feq = (125*1000*1000);
			break;
	}
#elif defined ON_BOARD_DDR2
	switch(clk_sel) {
		case 0:
			mips_bus_feq = (125*1000*1000);
			break;
		case 1:
			mips_bus_feq = (128*1000*1000);
			break;
		case 2:
			mips_bus_feq = (160*1000*1000);
			break;
		case 3:
			mips_bus_feq = (166*1000*1000);
			break;
	}
#else
#error undef SDR or DDR
#endif
#else /* RT2880 ASIC version */
	clk_sel = (reg>>20) & 0x03;
	switch(clk_sel) {
		#ifdef RT2880_MP
			case 0:
			mips_cpu_feq = (250*1000*1000);
			break;
		case 1:
			mips_cpu_feq = (266*1000*1000);
			break;
		case 2:
			mips_cpu_feq = (280*1000*1000);
			break;
		case 3:
			mips_cpu_feq = (300*1000*1000);
			break;
		#else
			case 0:
			mips_cpu_feq = (233*1000*1000);
			break;
		case 1:
			mips_cpu_feq = (250*1000*1000);
			break;
		case 2:
			mips_cpu_feq = (266*1000*1000);
			break;
		case 3:
			mips_cpu_feq = (280*1000*1000);
			break;
		
		#endif
	}
	mips_bus_feq = mips_cpu_feq/2;
#endif

   	//RALINK_REG(RT2880_SYSCFG_REG) = reg;

	/* in general, the spec define 8192 refresh cycles/64ms
	 * 64ms/8192 = 7.8us
	 * 7.8us * 106.7Mhz(SDRAM clock) = 832
	 * the value of refresh cycle shall smaller than 832. 
	 * so we config it at 0x300 (suggested by ASIC)
	 */
#if defined(ON_BOARD_SDR) && defined(ON_BOARD_256M_DRAM_COMPONENT)
	{
	u32 tREF;
	tREF = RALINK_REG(SDRAM_CFG1_REG);
	tREF &= 0xffff0000;
#if defined(ASIC_BOARD)
	tREF |= 0x00000300;
#elif defined(FPGA_BOARD) 
	tREF |= 0x000004B;
#else
#error "not exist"
#endif
	RALINK_REG(SDRAM_CFG1_REG) = tREF;
	}
#endif
	printf("CPU frequency: %lu\n", mips_cpu_feq);
}


