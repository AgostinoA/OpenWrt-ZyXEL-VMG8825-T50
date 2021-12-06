#include <common.h>
#include <asm/arch/hardware.h>
#include <asm/arch/scc.h>


void SoC_Check_Device(void)
{
	// This should run on a M829xx SoC, let's check it
	u32 devicetype = *(volatile u32*)(0x1008002C);
	if(devicetype != 0x140)
	{
		//error wrong device
		// TODO: what should we do?
	}
}
void SoC_PLL_init(void)
{
	//sys_write_control(CR_M | CR_V | CR_ASYNC);
	u32 i = 0;//CR_M | CR_V | CR_ASYNC;
	/* turn off I/D-cache */
	asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));
	i |= (CR_ASYNC);
	asm ("mcr p15, 0, %0, c1, c0, 0": :"r" (i));
	HAL_set_amba_clk(133000000);
	HAL_set_arm_clk(450000000);
}


//void SoC_mem_init(int controller, int base, int length)
void SoC_mem_init(void)
{
#if 0
	//*(volatile u32*)(0x10080010) = 0xD2db;
	//*(volatile u32*)(0x1008001c) = 0x42;
	//*(volatile u32*)(0x10080014) = 0xEA;
	*(volatile u32*)(0x10080010) = 0xD4E3;
	// Configure SDRAM CFG2
	*(volatile u32*)(0x10080014) = 0x00EA;
	//Configure SDRAM REFRESH
	*(volatile u32*)(0x10080018) = 0x0820;
	//Configure SDRAM PWRON
	*(volatile u32*)(0x1008001C) = 0x682B;

	*(volatile u32*)(0x10060000) = 0xF;
	*(volatile u32*)(0x1006000C) = 5;
#else
	if (1)//controller == 0)
	{
		//matisse only have one SDRAM controller so the first param is useless
		// The following settings is based on a SDRAM with clock rate 133 MHz and speed grade -7
		// Configure SDRAM CFG1
		*(volatile u32*)(0x10080010) = 0xD4E3;
		// Configure SDRAM CFG2
		*(volatile u32*)(0x10080014) = 0x00EA;
		//Configure SDRAM REFRESH
		*(volatile u32*)(0x10080018) = 0x0820;
		//Configure SDRAM PWRON
		*(volatile u32*)(0x1008001C) = 0x682B;
		
		
		
	#if 0
		// The following settings is based on a DDR-SDRAM with clock rate 133 MHz and speed grade -75z
		// Configure SDRAM CFG1
		*(volatile u32*)(0x10080010) = 0xD6DA;
		// Configure SDRAM CFG2
		*(volatile u32*)(0x10080014) = 0x03EA;
		//Configure SDRAM REFRESH
		*(volatile u32*)(0x10080018) = 0x0820;
		//Configure SDRAM PWRON
		*(volatile u32*)(0x1008001C) = 0x682B;
	#endif


	if (PHYS_SDRAM > (128*0x100000)) {	// high memory
		*(volatile u32*)(0x10060000) = (PHYS_SDRAM >>20)<<4;
		*(volatile u32*)(0x10060010) = (PHYS_SDRAM >>27);			
	}
	else {
		*(volatile u32*)(0x10060000) = (PHYS_SDRAM >>16)<<4;
	}

		switch (/*length*/PHYS_SDRAM_SIZE/0x100000)
		{
			case 8:
				*(volatile u32*)(0x10060000) |= 0xB;
				break;
			case 16:
				*(volatile u32*)(0x10060000) |= 0xC;
				break;
			case 32:
				*(volatile u32*)(0x10060000) |= 0xD;
				break;
			case 64:
				*(volatile u32*)(0x10060000) |= 0xE;
				break;
			case 128:
				*(volatile u32*)(0x10060000) |= 0xF;
				break;
		}			
		// Enable Chip select 0
		//*(volatile u32*)(0x1006000C) |= 0x1;
		//*(volatile u32*)(0x1006000C) = 0xC;
		if (PHYS_SDRAM > (128*0x100000))	// high memory : do ARAM remap to have memory @0x00000000		
			*(volatile u32*)(0x1006000C) = 0x115;
		else
			*(volatile u32*)(0x1006000C) = 0x05;
	}
#endif	
	
}

void SoC_flash_init(void)
{
	// Configure SDRAM CFG1
	*(volatile u32*)(0x10060004) = 0x0010000b;
	//*(volatile u32*)(0x10060014) = 0x10;
	*(volatile u32*)(0x10060014) = 0;
	*(volatile u32*)(0x10080004) = 0x0D92;
	*(volatile u32*)(0x1006000C) |= 2;

}

void SoC_nand_init(void)
{
	*(volatile u32*)(0x1008000C) = 0x0492;
	*(volatile u32*)(0x1006000C) |= 8;
}

