#include <config.h>
#include <asm/regdef.h>
#include <asm/mipsregs.h>
#include <asm/arch/rt_mmap.h>

#if defined(RT6855A_FPGA_BOARD) || defined(RT6855A_ASIC_BOARD)
#define SDRAM_CFG0_REG RALINK_MEMCTRL_BASE+ 0x0
#define SDRAM_CFG1_REG RALINK_MEMCTRL_BASE+ 0x4
#else
#define SDRAM_CFG0_REG RALINK_SYSCTL_BASE + 0x0300
#define SDRAM_CFG1_REG RALINK_SYSCTL_BASE + 0x0304
#endif
#define SDRAM_CFG0_ALWAYS_ONE ( 1 << 31)
#define SDRAM_CFG1_SDRAM_INIT_START ( 1 << 31)
#define SDRAM_CFG1_SDRAM_INIT_DONE ( 1 << 30)
#if defined(RT6855A_FPGA_BOARD) || defined(RT6855A_ASIC_BOARD)
#define SDRAM_CFG0_MIPSREG		s7
#define SDRAM_CFG1_MIPSREG		s8

#define DDR_CFG0_MIPSREG		s7
#define DDR_CFG1_MIPSREG		s8
#endif
#if defined(RT6855A_FPGA_BOARD) || defined(RT6855A_ASIC_BOARD)
#define DELAY_USEC(us)				((700*(us))/3)
#else
#define DELAY_USEC(us)				((500*(us))/3)
#endif

	.globl lowlevel_init
	.ent lowlevel_init
lowlevel_init:
	/* SDR and DDR initialization: delay 200us
	 */
	li t0, DELAY_USEC(200+40)
	li t1, 0x1
1:
	sub t0, t0, t1
	bnez t0, 1b
	nop

#if defined(ON_BOARD_DDR1)||defined(ON_BOARD_DDR2)
        

#if defined(RT6855_FPGA_BOARD)||defined(RT6855_ASIC_BOARD) || \
    defined(RT6352_FPGA_BOARD)||defined(RT6352_ASIC_BOARD) || \
    defined(RT71100_FPGA_BOARD)||defined(RT71100_ASIC_BOARD)

	/* Use default SYSCFG1 setting */
#elif defined (RT6855A_FPGA_BOARD) || defined (RT6855A_ASIC_BOARD)
	/* set DRAM IO PAD for DDR2 */
#if defined(ON_BOARD_DDR2)

#if 0
	la t0, RALINK_SYSCTL_BASE + 0x4
	lw t1, 0(t0)
	li t2, 1<<23
	or t1, t1, t2
	sw t1, 0(t0)
	nop
#endif
/*ODT ON*/
#if 1 
	la t0, RALINK_SYSCTL_BASE + 0x4
	lw t1, 0(t0)
	li t1, 0x000cc0d4
	sw t1, 0(t0)
	nop
#endif

#endif	
#else
	/* DDR initialization: reg SYSCFG1[25:16]: 
	 * ODT disabled, LVCMOS=1, half drive, turn ON RT3662 DDR IO ODT as 150 ohm when read DRAM
	 */
	li t1, RALINK_SYSCTL_BASE + 0x14
	lw t2, 0(t1)
	nop
	and t2, ~(0x3FF<<16)
	or t2, (0x361<<16)
	sw t2, 0(t1)
	nop
#endif
	/* DDR initialization: reset pin to 0
	 */
#if defined(RT6855A_FPGA_BOARD) || defined(RT6855A_ASIC_BOARD)
	li t1, RALINK_SYSCTL_BASE + 0x40
#else
	li t1, RALINK_SYSCTL_BASE + 0x34
#endif
	sw zero, 0(t1)
	nop

#if defined(RT6855A_FPGA_BOARD) || defined(RT6855A_ASIC_BOARD)
	li t0, DELAY_USEC(200+40)
	li t1, 0x1
1:
	sub t0, t0, t1
	bnez t0, 1b
	nop
#endif
	/* DDR initialization: wait til reg DDR_CFG1 bit 21 equal to 1 (ready)
	 */
DDR_READY:
	li t1, RALINK_MEMCTRL_BASE + 0x44 	//DDR_CFG1
	lw t0, 0(t1)
	nop
	and t2, t0, (1<<21)
	beqz t2, DDR_READY
	nop

	/* DDR initialization:
	 */
#if defined(RT6855_FPGA_BOARD)||defined(RT6855_ASIC_BOARD) || \
    defined(RT6352_FPGA_BOARD)||defined(RT6352_ASIC_BOARD) || \
    defined(RT71100_FPGA_BOARD)||defined(RT71100_ASIC_BOARD)
	 /*   fpga/asic: reg DDR_CFG2 -- set bit[30]=0 as DDR1 mode when DDR1
	  *   fpga/asic: reg DDR_CFG2 -- set bit[30]=1 as DDR2 mode when DDR2
	  *   fpga/asic: reg DDR_CFG2 -- set bit[6:4]=3'b011 when DDR1
	  *   fpga/asic: reg DDR_CFG2 -- set bit[6:4]=3'b100 when DDR2
	  */
	li t1, RALINK_MEMCTRL_BASE + 0x48	//DDR_CFG2
	lw t0, 0(t1)
	nop
	and t0, ~(1<<30)
#if ON_BOARD_DDR2
	and t0, ~(7<<4)
	or t0, (4<<4)
	or t0, (1<<30)
#elif ON_BOARD_DDR1
	and t0, ~(7<<4)
	or t0, (3<<4)
#endif
	sw t0, 0(t1)
	nop
#endif /* defined(RT6855_FPGA_BOARD)||defined(RT6855_ASIC_BOARD) */

/* RT3883 and RT6855 will share below setting, RT3352 no boot from NOR */
	/*
	 *   fpga: reg DDR_CFG3 -- disable DLL
	 *   asic: reg DDR_CFG3 -- ODT enable (bit 6,2) = 2'b10 when 6855/3883 DDR2
	 *   fpga/asic: reg DDR_CFG3 -- ODT enable (bit 6,2) = 2'b00 when 6855 DDR1
	 *   fpga/asic: reg DDR_CFG3[10][5:3] = 4'b0000 when 6855 DDR1
	 */
	li t1, RALINK_MEMCTRL_BASE + 0x4c 	////DDR_CFG3
	lw t2, 0(t1)
#ifdef ON_BOARD_DDR2
	#disable ODT; reference board ok, ev board fail
	#and t2, ~(1<<6)

	#enable ODT; both ok
	or t2, (1<<6)
	and t2, ~(1<<2)
#elif ON_BOARD_DDR1
	and t2, ~(1<<10)
	and t2, ~(7<<3)
#endif
#if defined(RT3883_FPGA_BOARD) || defined(RT6855_FPGA_BOARD) || defined(RT6352_FPGA_BOARD) || defined(RT71100_FPGA_BOARD)
	or t2, 0x1
#endif
#if !defined(RT6855A_ASIC_BOARD)	
	sw t2, 0(t1)
	nop
#endif	

#ifdef RALINK_DDR_OPTIMIZATION
	/* DDR: set Burst Length=4 in 32 bits dram bus for better performance
	 *          Burst Length=8 in non 32 bits dram bus
	 */
	li	t0, RALINK_MEMCTRL_BASE + 0x48
	lw	t1, 0(t0)
	nop
	and	t1, 0xffffff88
	or	t1, (CAS_VALUE<<CAS_OFFSET)
	or	t1, (BL_VALUE<<BL_OFFSET)
	sw	t1, 0(t0)
        nop

	li	t0, RALINK_MEMCTRL_BASE + 0x4c
	lw	t1, 0(t0)
	nop
	and	t1, 0xffffffc7
	or	t1, (AdditiveLatency_VALUE<<AdditiveLatency_OFFSET)
	sw	t1, 0(t0)
#endif

#if defined (RT3352_FPGA_BOARD) || defined (RT3883_FPGA_BOARD) || defined (RT6855_FPGA_BOARD) || defined(RT6352_FPGA_BOARD) || defined(RT71100_FPGA_BOARD)
	/* DDR initialization: DDR_CFG0 bit 12:0 (refresh interval) to 0x64
	 * Note. this may have a bad affect on efficiency if the clock rate is 40MHz
	 */
	li t1, RALINK_MEMCTRL_BASE + 0x40
	lw t2, 0(t1)
	nop
	and t2, ~(0xfff)
#if defined(ON_BOARD_DDR1)
	li t2, 0x21086141
#else
	or t2, 0x64
#endif	
	sw t2, 0(t1)
	nop
#endif

#if 0
	/* data output (DQ) delay */
	li t1, RALINK_MEMCTRL_BASE + 0x60
	li t2, 0xffffffff
	sw t2, 0(t1)
	nop
	li t1, RALINK_MEMCTRL_BASE + 0x64
	li t2, 0xffffffff
	sw t2, 0(t1)
	nop
#endif

	/* DDR initialization: config size and width on reg DDR_CFG1
	 */
#if defined(ON_BOARD_DDR2)
#if defined (RT6855_ASIC_BOARD) || defined(RT6352_ASIC_BOARD) || defined(RT71100_ASIC_BOARD)
#ifdef ON_BOARD_128M_DRAM_COMPONENT
        li t6, 0x332A3525
#elif defined (ON_BOARD_256M_DRAM_COMPONENT)
        li t6, 0x222e2424
#elif defined (ON_BOARD_512M_DRAM_COMPONENT)
        li t6, 0x22322424 
#elif defined (ON_BOARD_1024M_DRAM_COMPONENT)
        li t6, 0x22362424
#elif defined (ON_BOARD_2048M_DRAM_COMPONENT)
		li t6, 0x223a2424		
#else
        DRAM Component not defined
#endif
#elif defined (RT6855_FPGA_BOARD) || defined(RT6352_FPGA_BOARD) || defined(RT71100_FPGA_BOARD)
#ifdef ON_BOARD_128M_DRAM_COMPONENT
        li t6, 0x122A3121
#elif defined (ON_BOARD_256M_DRAM_COMPONENT)
        li t6, 0x222e2323	//0x122E3121
#elif defined (ON_BOARD_512M_DRAM_COMPONENT)
        li t6, 0x12323121
#elif defined (ON_BOARD_1024M_DRAM_COMPONENT)
        li t6, 0x12363121
#endif

#elif defined (RT3352_FPGA_BOARD) || defined(RT3883_FPGA_BOARD) || defined (RT3352_ASIC_BOARD) || defined(RT3883_ASIC_BOARD)
#ifdef ON_BOARD_128M_DRAM_COMPONENT
	li t6, 0x222A3323
#elif defined (ON_BOARD_256M_DRAM_COMPONENT)
	li t6, 0x222E3323
#elif defined (ON_BOARD_512M_DRAM_COMPONENT)
	li t6, 0x22323323
#elif defined (ON_BOARD_1024M_DRAM_COMPONENT)
	li t6, 0x22363323
#else
	DRAM Component not defined
#endif

#else /* RT6855A setting in below lookup table*/

#endif

#elif defined(ON_BOARD_DDR1)

#if defined(RT6855_ASIC_BOARD) || defined(RT6352_ASIC_BOARD) || defined(RT71100_ASIC_BOARD)
#ifdef ON_BOARD_128M_DRAM_COMPONENT
        li t6, 0x332A3525
#elif defined (ON_BOARD_256M_DRAM_COMPONENT)
        li t6, 0x332e2434
#elif defined (ON_BOARD_512M_DRAM_COMPONENT)
        li t6, 0x33322434
#elif defined (ON_BOARD_1024M_DRAM_COMPONENT)
        li t6, 0x33362434
#endif
#elif defined(RT6855_FPGA_BOARD) || defined(RT6352_FPGA_BOARD) || defined(RT71100_FPGA_BOARD)
#ifdef ON_BOARD_128M_DRAM_COMPONENT
        li t6, 0x122A3111
#elif defined (ON_BOARD_256M_DRAM_COMPONENT)
        li t6, 0x222e2113	//0x122E3111
#elif defined (ON_BOARD_512M_DRAM_COMPONENT)
        li t6, 0x12323111
#elif defined (ON_BOARD_1024M_DRAM_COMPONENT)
        li t6, 0x12363111
#endif

#else /* RT6855A setting in below lookup table*/

#endif

#endif /* end of setting DDR_CFG1 */

#ifdef ON_BOARD_DDR_WIDTH_16
	or t6, (1<<17)
	and t6, ~(1<<16)
#elif defined (ON_BOARD_DDR_WIDTH_8)
	and t6, ~(1<<17)
	or t6, (1<<16)
#else
	DDR width not defined
#endif
	/* CONFIG DDR_CFG1[13:12] about TOTAL WIDTH */
	and t6, ~(3<<12)
#ifdef ON_BOARD_32BIT_DRAM_BUS
	or t6, (3<<12)
#elif defined (ON_BOARD_16BIT_DRAM_BUS)
	or t6, (2<<12)
#else
	DRAM bus not defined
#endif
#if !defined(RT6855A_ASIC_BOARD)	
	li t5, RALINK_MEMCTRL_BASE + 0x44
	sw t6, 0(t5)
	nop
#else
	/* RT6855A DDR configurations */
	/* abstract DRAM_SPEED */
	la		t0, RALINK_SYSCTL_BASE+0x8C
	lw		t6, 0(t0)
	nop

	srl		t5, t6, 26
	andi	t5, t5, 0x1
	
	srl		t8, t6, 8
	andi	t8, t8, 0x3
	addiu	t7, zero, 2
	sub		t8, t8, t7
	bgez	t8, 1f			/* Large package size*/
	nop
	addiu	t5, t5, 2		/* t5 is column index, DDR 166MHZ and 125MHZ shoud add 2
					  ftom DRAM_SPEED for RT6855 case */
1:					  
#if defined(ON_BOARD_DDR1)	
	sll		t5, t5, 2
	lui		t0, %hi(DDR1_CFG2_TBL)
	ori		t0, t0, %lo(DDR1_CFG2_TBL)
	addu	t0, t0, t5
	lw		t1, 0(t0)
	nop
	la		t0, RALINK_DDR_CFG2
	sw		t1, 0(t0)
	nop
	lui		t0, %hi(DDR1_CFG3_TBL)
	ori		t0, t0, %lo(DDR1_CFG3_TBL)
	addu	t0, t0, t5
	lw		t1, 0(t0)
	la		t0, RALINK_DDR_CFG3
	sw		t1, 0(t0)
	nop

	/* DQS delay use table value */	
	lui		t0, %hi(DDR1_CFG4_TBL)
	ori		t0, t0, %lo(DDR1_CFG4_TBL)
	addu	t0, t0, t5
	lw		t1, 0(t0)
	nop
#if 0 
	/* DQS delay use DLL detected value then fixed the delay with a constant delay 8 */
	la		t0, RALINK_SYSCTL_BASE + 0x18
	lw		t2, 0(t0)
	andi	t3,	t2, 0x1F
	srl		t2, t2, 5
	addiu	t6, zero, 5
	mul		t0, t2, t6	
	addu	t0, t0, t3
	subu	t0, t0, 8
	div		t0, t6
	mflo	t2	
	mfhi	t3
	nop
	nop
	sll		t2, t2, 5
	or		t2, t2, t3
	sll		t4, t2, 9
	or		t2, t2, t4
	sll		t2, t2, 5
	li		t3, ~(((0x1FF<<9)|0x1FF)<<5)
	and		t1, t1, t3
	or		t1, t1, t2
#endif
	la		t0, RALINK_DDR_CFG4
	sw		t1, 0(t0)
	nop

#endif	
#if defined(ON_BOARD_DDR2)
	sll		t5, t5, 2
	lui		t0, %hi(DDR2_CFG2_TBL)
	ori		t0, t0, %lo(DDR2_CFG2_TBL)
	addu	t0, t0, t5
	lw		t1, 0(t0)
	nop
	la		t0, RALINK_DDR_CFG2
	sw		t1, 0(t0)
	nop
	lui		t0, %hi(DDR2_CFG3_TBL)
	ori		t0, t0, %lo(DDR2_CFG3_TBL)
	addu	t0, t0, t5
	lw		t1, 0(t0)
	nop
	
	la		t0, RALINK_DDR_CFG3
#if 1
	lw		t1, 0(t0)
	/*enable 100% drive strength*/
	//and		t1, ~(0x1<<1)
	/*enable 60% drive strength*/
	or		t1, (0x1<<1)
#endif
	sw		t1, 0(t0)
	nop
	
	/* DQS delay use table value */	
	lui		t0, %hi(DDR2_CFG4_TBL)
	ori		t0, t0, %lo(DDR2_CFG4_TBL)
	addu	t0, t0, t5
	lw		t1, 0(t0)
	nop
#if 0
	/* DQS delay use DLL detected value then fixed the delay with a constant delay 8 */
	la		t0, RALINK_SYSCTL_BASE + 0x18
	lw		t2, 0(t0)
	andi	t3,	t2, 0x1F
	srl		t2, t2, 5
	addiu	t6, zero, 5
	mul		t0, t2, t6	
	addu	t0, t0, t3
	subu	t0, t0, 8
	div		t0, t6
	mflo	t2	
	mfhi	t3
	nop
	nop
	sll		t2, t2, 5
	or		t2, t2, t3
	sll		t4, t2, 9
	or		t2, t2, t4
	sll		t2, t2, 5
	li		t3, ~(((0x1FF<<9)|0x1FF)<<5)
	and		t1, t1, t3
	or		t1, t1, t2
#endif
	la		t0, RALINK_DDR_CFG4
	sw		t1, 0(t0)
	nop
#if 0	
	la		t0, RALINK_DDR_CFG9
	li		t1, 0x88880000
	sw		t1, 0(t0)
	nop
#endif
#endif		
2:	

#if defined(ON_BOARD_DDR1)	
#ifdef ON_BOARD_64M_DRAM_COMPONENT
	addiu 	t4, zero, 1
#elif ON_BOARD_128M_DRAM_COMPONENT
	addiu 	t4, zero, 2
#elif defined (ON_BOARD_256M_DRAM_COMPONENT)
	addiu 	t4, zero, 3
#elif defined (ON_BOARD_512M_DRAM_COMPONENT)
	addiu 	t4, zero, 4
#else
	DRAM Component not defined
#endif
#endif
#if defined(ON_BOARD_DDR2)	
#if defined (ON_BOARD_256M_DRAM_COMPONENT)
	addiu 	t4, zero, 3
#elif defined (ON_BOARD_512M_DRAM_COMPONENT)
	addiu 	t4, zero, 4
#elif defined (ON_BOARD_1024M_DRAM_COMPONENT)
	addiu 	t4, zero, 5
#elif defined (ON_BOARD_2048M_DRAM_COMPONENT)
	addiu 	t4, zero, 6
#else
#error	"DRAM Component not defined"
#endif
#endif
	srl		t3, t6, 24
	andi	t3, t3, 0x3
	subu	t3, t3, 2	
	srl		t5, t6, 26
	andi	t5, t5, 0x1
	bgez	t8, 1f
	nop
	addiu	t5, t5, 2	/* t5 is column index, DDR 166MZH and 125MHZ shoud add 2
					   ftom DRAM_SPEED for RT6855 case */
1:
#if defined(ON_BOARD_DDR1)
	addiu	t6, zero, 4
	subu	t4, t4, 1
	mul		t2, t4, t6
	nop
	addu	t2, t2, t5
	sll		t2, t2, 2
	lui		t0, %hi(DDR1_CFG0_TBL)
	ori		t0, t0, %lo(DDR1_CFG0_TBL)
	addu	t0, t0, t2
	lw		DDR_CFG0_MIPSREG, 0(t0)
	nop
	lui		t0, %hi(DDR1_CFG1_TBL)
	ori		t0, t0, %lo(DDR1_CFG1_TBL)
	addu	t0, t0, t2
	lw		DDR_CFG1_MIPSREG, 0(t0)
	nop
#endif	
#if defined(ON_BOARD_DDR2)
	addiu	t6, zero, 4
	subu	t4, t4, 3
	mul		t2, t4, t6
	nop
	addu	t2, t2, t5
	sll		t2, t2, 2
	lui		t0, %hi(DDR2_CFG0_TBL)
	ori		t0, t0, %lo(DDR2_CFG0_TBL)
	addu	t0, t0, t2
	lw		DDR_CFG0_MIPSREG, 0(t0)
	nop
	lui		t0, %hi(DDR2_CFG1_TBL)
	ori		t0, t0, %lo(DDR2_CFG1_TBL)
	addu	t0, t0, t2
	lw		DDR_CFG1_MIPSREG, 0(t0)
	nop
#endif	
2:
	la		t5, RALINK_DDR_CFG0
	sw		DDR_CFG0_MIPSREG, 0(t5)
	nop
	la		t5, RALINK_DDR_CFG1
	sw		DDR_CFG1_MIPSREG, 0(t5)
	nop
#endif
	j SDRAM_INIT_DOWN
	nop
#endif /* defined(ON_BOARD_DDR1)||defined(ON_BOARD_DDR2) */


#ifdef ON_BOARD_SDR
SDR_INIT:
#if defined(RT6855A_FPGA_BOARD) || defined(RT6855A_ASIC_BOARD)
	li t1, RALINK_SYSCTL_BASE + 0x40
	sw zero, 0(t1)
	nop
#endif
	/* SDR initialization: SDRAM_CFG0
	 */
	li t5, SDRAM_CFG0_REG
	lw t6, 0(t5)
	nop
	and t6, 0xF0000000
#ifdef FPGA_BOARD
#ifdef RT2880_FPGA_BOARD
#ifdef RT2880_MP
	nop
	or t6, 0x01825282
	//or t6, 0x01815282
	nop	
#else /* RT2880_SHUTTLE */
	or t6, 0x91825282
	//or t6, 0x91815282
#endif
#elif defined(RT6855_FPGA_BOARD) || defined (RT6352_FPGA_BOARD) || defined (RT71100_FPGA_BOARD)
	or t6, 0xD1825272
	//or t6, 0xD1916292
#else //2883, 3052, 3352, 3883, 5350 fpga
	nop
	or t6, 0xD1825272
	//or t6, 0x01815282
	nop	
#endif
#else //ASIC_BOARD
#if defined(RT6855_ASIC_BOARD) || defined (RT6352_ASIC_BOARD) || defined (RT71100_ASIC_BOARD)
        or t6, 0xD1916292
#else	
	or t6, 0xD1825272
#endif
#endif
	nop
#if !defined(RT6855A_ASIC_BOARD)	
	sw t6, 0(t5)
	nop
#endif

	li t5, SDRAM_CFG1_REG
#ifdef ASIC_BOARD
/*
 *	Turn on SDRAM RBC (BIT 29 in SDRAM_CFG1, offset 0x4) in RT3052.
 *	  RT2880 RBC bit is Reserved bit, and change the same value for RT2880 and RT3052
 *	  Original 0x81xx0600 -> 0xa1xx0600
 *		by bobtseng, 2008.7.7.
 */
#if defined (ON_BOARD_16M_DRAM_COMPONENT)
	li t6, 0xa0000668
#elif defined (ON_BOARD_64M_DRAM_COMPONENT)
	li t6, 0xa1010600
#elif defined (ON_BOARD_128M_DRAM_COMPONENT)
	li t6, 0xa1110600
#elif defined (ON_BOARD_256M_DRAM_COMPONENT)
	li t6, 0xa1120300
#elif defined (ON_BOARD_512M_DRAM_COMPONENT)
	li t6, 0xa1220600
#elif defined(ON_BOARD_DDR1)||defined(ON_BOARD_DDR2)
#else
	DRAM Component not defined
#endif
#ifdef ON_BOARD_32BIT_DRAM_BUS
	and t6, 0xFEFFFFFF
	or t6, (1<<24)
#elif defined ON_BOARD_16BIT_DRAM_BUS
	and t6, 0xFEFFFFFF
#else
	DRAM bus not defined
#endif

#else /* not ASIC_BOARD */

#ifdef ON_BOARD_64M_DRAM_COMPONENT
	li t6, 0xa1010096
#elif defined (ON_BOARD_128M_DRAM_COMPONENT)
	li t6, 0xa1110096
#elif defined (ON_BOARD_256M_DRAM_COMPONENT)
	li t6, 0xa112004B
#elif defined (ON_BOARD_512M_DRAM_COMPONENT)
	li t6, 0xa1220096
#else
	DRAM Component not defined
#endif

#ifdef ON_BOARD_32BIT_DRAM_BUS
	and t6, 0xFEFFFFFF
	or t6, (1<<24)
#elif defined (ON_BOARD_16BIT_DRAM_BUS)
	and t6, 0xFEFFFFFF
#else
	DRAM bus not defined
#endif
#endif



DO_SDRINIT:
	nop
#if !defined(RT6855A_ASIC_BOARD)		
	sw 		t6, 0(t5)
	nop
#endif

#if defined(RT6855A_ASIC_BOARD)
	move	t1, zero	/* force to 140Mhz case */
#if defined (ON_BOARD_16M_DRAM_COMPONENT)
	addiu	t4, zero, 0
#elif defined (ON_BOARD_64M_DRAM_COMPONENT)
	addiu	t4, zero, 1
#elif defined (ON_BOARD_128M_DRAM_COMPONENT)
	addiu	t4, zero, 2
#elif defined (ON_BOARD_256M_DRAM_COMPONENT)
	addiu	t4, zero, 3
#else
	DRAM Component not defined
#endif	
	lui		t0, %hi(SDR_CFG0_TBL)
	ori		t0, t0, %lo(SDR_CFG0_TBL)
	sll		t3, t1, 2
	addu	t0, t0, t3
	lw		SDRAM_CFG0_MIPSREG, 0(t0)
	nop
	addiu	t3, zero, 2
	mul		t2, t4, t3
	nop
	addu	t2, t2, t1
	sll		t2, t2, 2
	lui		t0, %hi(SDR_CFG1_TBL)
	ori		t0, t0, %lo(SDR_CFG1_TBL)
	addu	t0, t0, t2
	lw		SDRAM_CFG1_MIPSREG, 0(t0)
	nop
	la		t0, SDRAM_CFG0_REG
    sw		SDRAM_CFG0_MIPSREG, 0(t0)
	nop
	la		t0, SDRAM_CFG1_REG
	sw		SDRAM_CFG1_MIPSREG, 0(t0)
	nop	
#endif
WAIT_SDRAM_INIT_DOWN:	
	lw t6, 0(t5)
	nop
	and  	t6, t6, SDRAM_CFG1_SDRAM_INIT_DONE
	beqz	t6, WAIT_SDRAM_INIT_DOWN
	nop

#endif // ON_BOARD_SDR //

SDRAM_INIT_DOWN:
#if defined(RT3883_FPGA_BOARD) || defined(RT3883_ASIC_BOARD)
  #ifdef ON_BOARD_DDR2
        /* DDR initialization: reg SYSCFG1[25:16]: 
	 * ODT disabled, LVCMOS=1, half drive, turn ON RT3662 DDR IO ODT as 150 ohm when read DRAM
	 */
        li t1, RALINK_SYSCTL_BASE + 0x14
	lw t2, 0(t1)
	nop
	and t2, ~(0x3FF<<16)
	or t2, (0x361<<16)
	sw t2, 0(t1)
	nop
  #endif
#endif

#ifdef RT3352_ASIC_BOARD
	/* adjust the SW reg voltage level higher */
            li t1, RALINK_SYSCTL_BASE + 0x88
	    li t2, 0xECC340
	    sw t2, 0(t1)
            nop
	
	/* set LDODIG 1.24V */
            li t1, RALINK_SYSCTL_BASE + 0x8c
	    li t2, 0x9B82
	    sw t2, 0(t1)
            nop

	/* 
	 * Enable spreading spectrum clock 
	 * SSC_MODUMAG=7: +/-1.00% for center; -2.00% for down
	 */
	    li t1, RALINK_SYSCTL_BASE + 0x54
	    li t2, 0x71
	    nop
	    sw t2, 0(t1)

  #ifdef ON_BOARD_DDR2
  #if 0
	/* RT3883 EVB board with Nanya 1G DDR shall enable this */
	/* data output (DQ) delay */
	li t1, RALINK_MEMCTRL_BASE + 0x60
	li t2, 0
	sw t2, 0(t1)
	nop
	li t1, RALINK_MEMCTRL_BASE + 0x64
	li t2, 0
	sw t2, 0(t1)
	nop
  #endif
  #if 0
	/* RT3352 EVB board with 32bits DDR shall enable this */
	/* data output (DQ) delay */
	li t1, RALINK_MEMCTRL_BASE + 0x60
	li t2, 0xffffffff
	sw t2, 0(t1)
	nop
	li t1, RALINK_MEMCTRL_BASE + 0x64
	li t2, 0xffffffff
	sw t2, 0(t1)
	nop
  #endif
  #if 0
	/* RT3352 EVB board with 16/32 bits DDR shall enable this */
	/*
	 * DDR_PAD_DRV_1=00 (full drive)
	 * DDR_PAD_DS=0 (DDR2 differential RX application)
	 * DDR_PAD_LVCMO=0 (DDR default)
	 * DDR_PAD_DRV_0=00 (full drive)
	 */
	li t1, RALINK_SYSCTL_BASE + 0x14
	and t2, ~(0x33F00000) 
	sw t2, 0(t1)
	nop
  #endif
  #endif /* ON_BOARD_DDR2 */
#endif /* RT3352_ASIC_BOARD */
#if defined(ON_BOARD_DDR1) || defined(ON_BOARD_DDR2)
#if defined(RT3883_FPGA_BOARD) || defined(RT3883_ASIC_BOARD)
	/* get cpu frequency from SYSCFG0 bit 9:8, and adjust tRFC accordingly
	 */
	li	t0, RALINK_SYSCTL_BASE + 0x10
	lw	t1, 0(t0)
	nop
	and	t1, (0x3 << 8)
	bne	t1, (0x3 << 8), tRFC480
	nop

	/* DDR initialization: DDR_CFG0: adjust tRFC according to size and cpu clock
	 *      for a better performance
	 *	applied for both rom and ram version (SPI and NAND flash)
	 */
#ifdef ON_BOARD_64M_DRAM_COMPONENT
	li t4, 0x2498E4F0
#elif defined (ON_BOARD_128M_DRAM_COMPONENT)
	li t4, 0x2498E4F0
#elif defined (ON_BOARD_256M_DRAM_COMPONENT)
	li t4, 0x2498E4F0
#elif defined (ON_BOARD_512M_DRAM_COMPONENT)
	li t4, 0x249924F0
#elif defined (ON_BOARD_1024M_DRAM_COMPONENT)
	li t4, 0x249964F0
#elif defined (ON_BOARD_2048M_DRAM_COMPONENT)
	li t4, 0x249924F0
#else
	DRAM Component not defined
#endif
	j tRFCinit
	nop
tRFC480:
	bne	t1, (0x2 << 8), tRFC250
	nop
#ifdef ON_BOARD_64M_DRAM_COMPONENT
	li t4, 0x2498E4C0
#elif defined (ON_BOARD_128M_DRAM_COMPONENT)
	li t4, 0x2498E4C0
#elif defined (ON_BOARD_256M_DRAM_COMPONENT)
	li t4, 0x2498E4C0
#elif defined (ON_BOARD_512M_DRAM_COMPONENT)
	li t4, 0x249924C0
#elif defined (ON_BOARD_1024M_DRAM_COMPONENT)
	li t4, 0x249964C0
#elif defined (ON_BOARD_2048M_DRAM_COMPONENT)
	li t4, 0x249924C0
#else
	DRAM Component not defined
#endif
	j tRFCinit
	nop
tRFC250:
#ifdef ON_BOARD_64M_DRAM_COMPONENT
	li t4, 0x2498A3B0
#elif defined (ON_BOARD_128M_DRAM_COMPONENT)
	li t4, 0x2498A3B0
#elif defined (ON_BOARD_256M_DRAM_COMPONENT)
	li t4, 0x2498A3B0
#elif defined (ON_BOARD_512M_DRAM_COMPONENT)
	li t4, 0x2499C3B0
#elif defined (ON_BOARD_1024M_DRAM_COMPONENT)
	li t4, 0x249903B0
#elif defined (ON_BOARD_2048M_DRAM_COMPONENT)
	li t4, 0x2499A3B0
#else
	DRAM Component not defined
#endif

#elif defined(RT3352_FPGA_BOARD) || defined(RT3352_ASIC_BOARD)

#if defined (ON_BOARD_256M_DRAM_COMPONENT)
	li t4, 0x2498E400
#elif defined (ON_BOARD_512M_DRAM_COMPONENT)
	li t4, 0x24992400
#elif defined (ON_BOARD_1024M_DRAM_COMPONENT)
	li t4, 0x24996400
#elif defined (ON_BOARD_2048M_DRAM_COMPONENT)
	li t4, 0x249A2400
#else
	DRAM Component not defined
#endif

#elif defined(RT6855_ASIC_BOARD) || defined (RT6352_ASIC_BOARD) || defined (RT71100_ASIC_BOARD)
#if defined(ON_BOARD_DDR1)
	/* below 0x2419C640 is base on CLK = 200Mhz setting */	
	li t4, 0x2419C640
#elif defined(ON_BOARD_DDR2)
	/* below 0x35AEA823 is base on CLK = 266Mhz setting */	
	li t4, 0x35AEA823
#endif

#elif defined(RT6855_FPGA_BOARD) || defined (RT6352_FPGA_BOARD) || defined (RT71100_FPGA_BOARD)
#if defined(ON_BOARD_DDR1)
	/* below 0x21086140 is base on CLK = 40Mhz setting */
        li t4, 0x21086140
#elif defined(ON_BOARD_DDR2)
/* below 0x21090138 is base on CLK = 40Mhz setting */
        li t4, 0x21090138
#endif
#elif defined(RT6855A_FPGA_BOARD) || defined(RT6855A_ASIC_BOARD)

#else
error	"DRAM Component not defined"
#endif

tRFCinit:
#if 0
	li t3, RALINK_MEMCTRL_BASE + 0x40
	sw t4, 0(t3)
	nop
#endif

#if defined(RT3352_FPGA_BOARD) || defined(RT3352_ASIC_BOARD)
#if defined(RALINK_DDR_POWERSAVE)
	/* DDR: enable self auto refresh for power saving
	 * enable it by default for both RAM and ROM version (for CoC)
	 */
	li	t0, RALINK_MEMCTRL_BASE + 0x1C
	lw	t1, 0(t0)
	nop
	and	t1, 0xff000000
	or	t1, 0x01
	sw	t1, 0(t0)
	nop
	li	t0, RALINK_MEMCTRL_BASE + 0x18
	lw	t1, 0(t0)
	nop
	or	t1, 0x10
	sw	t1, 0(t0)
	nop
#endif
#endif // defined(RT3352_FPGA_BOARD) || defined(RT3352_ASIC_BOARD) //
#else // SDR //
#if defined(RT3352_FPGA_BOARD) || defined(RT3352_ASIC_BOARD) || \
    defined (RT5350_FPGA_BOARD) || defined (RT5350_ASIC_BOARD)
#if defined(RALINK_SDR_POWERSAVE)
	/* SDR:enable precharge power saving
	 */
	li	t0, RALINK_MEMCTRL_BASE + 0x1C
	lw	t1, 0(t0)
	nop
	and	t1, 0xff000000
	or	t1, 0x01
	sw	t1, 0(t0)
	nop
	li	t0, RALINK_MEMCTRL_BASE + 0x04
	lw	t1, 0(t0)
	nop
	or	t1, 0x10000000
	sw	t1, 0(t0)
	nop
#endif // RALINK_MEMORY_POWER_SAVE  //
#endif  // defined(RT3352_FPGA_BOARD) || defined (RT3352_ASIC_BOARD)
#endif /* defined(ON_BOARD_DDR1)||defined(ON_BOARD_DDR2) */
#if defined(RT3352_FPGA_BOARD) || defined(RT3352_ASIC_BOARD) || \
    defined (RT5350_FPGA_BOARD) || defined (RT5350_ASIC_BOARD)
#if defined (RALINK_CPU_AUTOFREQUENCY)
	/* auto freq adjustment 3352,5350 support
	 */
	li	t0, RALINK_SYSCTL_BASE + 0x44
	li	t1, 0x1f0112
	sw	t1, 0(t0)
	nop
	li	t0, RALINK_SYSCTL_BASE + 0x3c
	li	t1, 0x3040101
	sw	t1, 0(t0)
	nop
	li	t0, RALINK_SYSCTL_BASE + 0x40
	li	t1, 0x80035f41
	sw	t1, 0(t0)
	nop

#endif
#endif  // defined(RT3352_FPGA_BOARD) || defined (RT3352_ASIC_BOARD) //
	//gpiomode for non 6855A
#if !defined(RT6855A_FPGA_BOARD) && !defined(RT6855A_ASIC_BOARD)
	li t5, RALINK_SYSCTL_BASE + 0x0060
	lw t6, 0(t5)
	nop
	or t6, 0x03

#if defined (RT2880_ASIC_BOARD) || defined (RT2880_FPGA_BOARD)
	/* enable normal function i2c, spi, uartl, jtag, mdio, sdram */
	and t6, ~(0x1<<0)
	and t6, ~(0x1<<2)
	and t6, ~(0x1<<3)
	and t6, ~(0x1<<4)
	and t6, ~(0x1<<5)
	and t6, ~(0x1<<6)
#else
	/* enable normal function i2c, spi, uartl, jtag, mdio, ge1 */
	and t6, ~(0xf<<7)
	and t6, ~(0x3<<5)
	and t6, ~(0x3)
	/* LNA_G_SHARE_MODE and LNA_A_SHARE_MODE at normal function, not GPIO mode */
	and t6, ~(0xf<<16)
#endif

#if defined(RT3052_ASIC_BOARD) || defined(RT3352_ASIC_BOARD) || defined(RT6855_ASIC_BOARD) || defined(RT6352_ASIC_BOARD) || defined(RT71100_ASIC_BOARD)
#if defined(P5_MAC_TO_PHY_MODE)
	//set mdio pin to normal mode
	and t6, ~0x80
#else
	//set mdio pin to gpio mode
	or t6, 0x80
#endif

#if defined(ON_BOARD_16BIT_DRAM_BUS)
	//set SDRAM pin to gpio mode
	or t6, 0x100
#endif
#if defined(UARTF_AT_GPIO_FUNC)
	//configure UARTF pin to gpio mode (GPIO7~GPIO14)
	or t6, 0x1c
#endif

#endif

#ifdef MAC_TO_VITESSE_MODE
	//set spi pin to normal mode
#if defined (RT2880_FGPA_BOARD) || defined (RT2880_ASIC_BOARD)
	and t6, ~(1<<2)
#else
	and t6, ~(1<<1)
#endif
#endif
#ifdef PCI_AT_GPIO_FUNC
	or t6, 1<<7
#endif

#if defined(RT3883_FPGA_BOARD) || defined(RT3883_ASIC_BOARD)
	//PCI share mode for NOR flash read/write
#if 0
	//old PCI share mode: 3'b010
	and t6, ~(7<<11)
	or t6, 2<<11
#else
	//new PCI share mode: 3'b011
	and t6, ~(7<<11)
	or t6, 3<<11
#endif

#endif

	//set GPIOMODE
	nop
	sw t6, 0(t5)
	nop

#ifdef PCI_AT_GPIO_FUNC
	/* output high */
	li t5, 0xa0300674
	li t6, 0xffffffff
	nop
	sw t6,0(t5)
	nop

	li t5, 0xa0300670
	li t6, 0xffffffff
	nop
	sw t6, 0(t5)
	nop
#endif
	/* SPI_HOLD should not set as GPIO output */	
	//set all GPIO to output high
        li t5, RALINK_PIO_BASE + 0x24
        li t6, 0xffffbfff
        nop
        sw t6, 0(t5)
        nop
        li t5, RALINK_PIO_BASE + 0x2C
        li t6, 0xffffffff
        nop
        sw t6, 0(t5)
        nop
		
#if defined(RT3052_ASIC_BOARD) || defined (RT3052_FPGA_BOARD)
#if defined(ON_BOARD_16BIT_DRAM_BUS)
	//if sdram bus is 16bits,set gpio24~gpio39 to output high
	li t6, 0xffff
	nop
        sw t6, 0(t5)
        nop
        li t5, RALINK_PIO_BASE + 0x54
	li t6, 0xffff
	nop
        sw t6, 0(t5)
        nop
#endif
#endif

#if defined(RT5350_ASIC_BOARD)
	// set default LED polarity value for RT5350 REF board
	// Active status:
	// EPHY_LED0  H: Light
	// EPHY_LED1  H: Light
	// EPHY_LED2  H: Light
	// EPHY_LED3  L: Light
	// EPHY_LED4  H: Light

	li t5, RALINK_ETH_SW_BASE + 0x168
	li t6, 0x17
	nop
	sw t6, 0(t5)
	nop

	// set default LED polarity value for RT5350 REF board
	li t5, RALINK_11N_MAC_BASE + 0x102c
	li t6, 0x40000000
	nop
	sw t6, 0(t5)
	nop

#endif		

#if defined(RT2880_ASIC_BOARD)
	//turn on power LED (GPIO 12)
	li t5, RALINK_PIO_BASE + 0x24
	lw t6, 0(t5)
	nop
	or t6, 1<<12
	sw t6, 0(t5)
	nop
	li t5, RALINK_PIO_BASE + 0x30
	li t6, 1<<12
	nop
	sw t6, 0(t5)
	nop
#elif defined(RT2883_ASIC_BOARD)
	//turn on power LED (GPIO 8)
	li t5, RALINK_PIO_BASE + 0x24
	lw t6, 0(t5)
	nop
	or t6, 1<<8
	sw t6, 0(t5)
	nop
	li t5, RALINK_PIO_BASE + 0x30
	li t6, 1<<8
	nop
	sw t6, 0(t5)
	nop
#elif defined(RT3052_ASIC_BOARD)
	//turn on power LED (GPIO 9)
	li t5, RALINK_PIO_BASE + 0x24
	lw t6, 0(t5)
	nop
	or t6, 1<<9
	sw t6, 0(t5)
	nop
	li t5, RALINK_PIO_BASE + 0x30
	li t6, 1<<9
	nop
	sw t6, 0(t5)
	nop
#elif defined(RT3352_ASIC_BOARD)
	//turn on power LED (GPIO ?)
#elif defined(RT5350_ASIC_BOARD)
	//turn on power LED (GPIO ?)
#elif defined(RT6855_ASIC_BOARD) || defined(RT6352_ASIC_BOARD) || defined(RT71100_ASIC_BOARD)
	//turn on power LED (GPIO ?)
#elif defined(RT3883_ASIC_BOARD)
	//turn on power LED (GPIO ?)
#endif
#endif

	/* config SYSCFG or SYSCFG1 register accordingly
	 */
#if defined(RT2880_ASIC_BOARD) || defined(RT2880_FPGA_BOARD)
	// Need to remap the vector memory to 0x0 if no memory there
	li	t0, RALINK_SYSCTL_BASE + 0x0010
	li	t1, 0x00C10084 //prefetch off 
	
	sw	t1, 0(t0)
#endif
#if defined(RT2883_ASIC_BOARD) || defined(RT2883_FPGA_BOARD)
	//set PCIe to RC mode
	li	t0, RALINK_SYSCTL_BASE + 0x10
	lw	t1, 0(t0)
	nop
	or	t1, t1, (1 << 23)
	sw	t1, 0(t0)
        nop
#endif
#if defined(RT3883_ASIC_BOARD) || defined(RT3883_FPGA_BOARD)
	//FIXME: read from SYSCFG
	li	t0, RALINK_SYSCTL_BASE + 0x14
	lw	t2, 0(t0)
	nop
	and	t2, ~(3 << 14)	//GE2 to RGMII mode
	and	t2, ~(3 << 12)	//GE1 to RGMII mode
	or	t2, (1 << 8)	//PCIe to RC mode (for ethernet)
	or	t2, (1 << 7)	//PCI to Host mode (for ethernet)
	sw	t2, 0(t0)
	nop
#endif

    jr              ra
	.end            lowlevel_init



#if defined(RT6855A_ASIC_BOARD)
	.global         rt6855A_cpu_pll
	.ent            rt6855A_cpu_pll
rt6855A_cpu_pll:
	la              t0, RALINK_SYSCTL_BASE + 0x8C
	lw              t1, 0(t0)
	nop
	srl             t2, t1, 9
	andi            t2, t2, 0x1
	bnez            t2, TFBGA_PACKAGE_DOWN
	nop
	srl             t2, t1, 26
	andi            t2, t2, 0x1
	beqz            t2, LQFP_PACKAGE_DOWN
	nop
LQFP_PACKAGE_UP:
	/* 500Mhz up to 560Mhz */
	la              t0, RALINK_SYSCTL_BASE+0x1D0
	addiu           t3, zero, 100-1         /* t3=DIVF */
	li              t4, 2<<8                /* t4=DIVQ */
	//addiu           t6, zero, 0           /* t6=DIVR */
	li              t6, ~((0x0FF<<16)|(0x7<<8)|0x1F)
1:
	lw              t8, 0(t0)
	nop
	and             t8, t8, t6
	or              t8, t8, t4
	sll             t7, t3, 16
	or              t8, t8, t7
	sw              t8, 0(t0)
	nop
	/* wait at least 50 usec for PLL lock */
	li              t5, ((50*(500+50))/3)
3:
	subu            t5, t5, 1
	bgtz            t5, 3b
	nop

	addiu           t3, t3, 1
	addiu           t7, zero, 112-1
	subu            t8, t7, t3
	bgez            t8, 1b
	nop
	j               PLL_DONE
	nop
LQFP_PACKAGE_DOWN:
	/* 500Mhz down to 420Mhz */
	la              t0, RALINK_SYSCTL_BASE+0x1D0
	addiu           t3, zero, 100-1         /* t3=DIVF */
	li              t4, 2<<8                /* t4=DIVQ */
	//addiu           t6, zero, 0             /* t6=DIVR */
	li              t6, ~((0x0FF<<16)|(0x7<<8)|0x1F)
1:
	lw              t8, 0(t0)
	nop
	and             t8, t8, t6
	or              t8, t8, t4
	sll             t7, t3, 16
	or              t8, t8, t7
	sw              t8, 0(t0)
	nop

	/* wait at least 50 usec for PLL lock */
	li              t5, ((50*(500+50))/3)
3:
	subu            t5, t5, 1
	bgtz            t5, 3b
	nop

	subu            t3, t3, 1
	addiu           t7, zero, 84-1
	subu            t8, t3, t7
	bgez            t8, 1b
	nop
	j               PLL_DONE
	nop
TFBGA_PACKAGE_DOWN:
	/* 665Mhz down to 560Mhz */
	la              t0, RALINK_SYSCTL_BASE+0x1CC
	addiu           t3, zero, 133-1         /* t3=DIVF */
	li              t4, 1<<8                /* t4=DIVQ */
	addiu           t6, zero, 1             /* t6=DIVR */
	li              t1, ~((0x0FF<<16)|(0x7<<8)|0x1F)

1:
	lw              t8, 0(t0)
	nop
	and             t8, t8, t1
	or              t8, t8, t4
	or              t8, t8, t6
	sll             t7, t3, 16
	or              t8, t8, t7
	sw              t8, 0(t0)
	nop

	/* wait at least 50 usec for PLL lock */
	li              t5, ((50*(700+70))/3)
3:
	subu            t5, t5, 1
	bgtz            t5, 3b
	nop

	subu            t3, t3, 1
	addiu           t7, zero, 120-1
	subu            t8, t3, t7
	bgez            t8, 1b
	nop
	addiu           t3, zero, 238-1
	li              t4, 2<<8

2:
	lw              t8, 0(t0)
	nop
	and             t8, t8, t1
	or              t8, t2, t4
	or              t8, t8, t6
	sll             t7, t3, 16
	or              t8, t8, t7
	sw              t8, 0(t0)
	nop
	/* wait at least 50 usec for PLL lock */
	li              t5, ((50*(600+60))/3)
4:
	subu            t5, t5, 1
	bgtz            t5, 4b
	nop

	subu            t3, t3, 1*2
	addiu           t7, zero, 224-1
	subu            t8, t3, t7
	bgez            t8, 2b
	nop
PLL_DONE:
	jr              ra
	nop
	.end            rt6855A_cpu_pll

		.text
		.global SDR_CFG0_TBL
		.align  3
SDR_CFG0_TBL:
			/* 140MHZ */    /* 105MHZ */
		.word   0x11925282,     0x11623161
		.text
		.global SDR_CFG1_TBL
		.align  3
SDR_CFG1_TBL:	
			/* 140MHZ */    /* 105MHZ */
		.word   0x8000088B,     0x80000668      /* 2MB */
		.word   0x8001088B,     0x80010668      /* 8MB */
		.word   0x8011088B,     0x80110668      /* 16MB */
		.word   0x80120445,     0x80120334      /* 32MB */

		.text
		.global	DDR1_CFG0_TBL
		.align	3
DDR1_CFG0_TBL:
			/* 233MHZ */	/* 175MHZ */	       /* 166MHZ */	       /* 125MHZ */
		.word	0x352A2E34, 	0x3421AAAF,		0x23998A20,		0x2319279E	/* 8MB */
		.word	0x352A2E34, 	0x3421AAAF,		0x23998A20,		0x2319279E	/* 16MB */
		.word	0x352A271A, 	0x3421A558,		0x2399850E,		0x231923CF	/* 32MB */
		.word	0x352A271A, 	0x3421A558,		0x2399850E,		0x231923CF	/* 64MB */
		
		.text
		.global	DDR1_CFG1_TBL
		.align	3
DDR1_CFG1_TBL:
			/* 233MHZ */	/* 175MHZ */	       /* 166MHZ */	       /* 125MHZ */
		.word	0x20262424, 	0x20262324,		0x20262323,		0x20262223	/* 8MB */
		.word	0x202A2424, 	0x202A2324,		0x202A2323,		0x202A2223	/* 16MB */
		.word	0x202E2424, 	0x202E2324,		0x202E2323,		0x202E2223	/* 32MB */
		.word	0x20322424, 	0x20322324,		0x20322323,		0x20322223	/* 64MB */
		
		.text
		.align	3
			/* 233MHZ */	/* 175MHZ */	        /* 166MHZ */	       /* 125MHZ */
DDR1_CFG2_TBL:
		.word	0x00000033, 	0x00000033,		0x00000033,		0x00000063	
DDR1_CFG3_TBL:
		.word	0x00000000, 	0x00000000,		0x00000000,		0x00000002
DDR1_CFG4_TBL:
		.word	0x00000000, 	0x00000000,		0x00000000,		0x00000000
				
		.text
		.global	DDR2_CFG0_TBL
		.align	3
DDR2_CFG0_TBL:
			/* 233MHZ */	/* 175MHZ */	        /* 166MHZ */    	/* 125MHZ */
		.word	0x35A2438D, 	0x2419C2AB,		0x2419A287,		0x231941E7	/* 32MB */
		.word	0x35A3238D, 	0x241A62AB,		0x241A4287,		0x2319C1E7	/* 64MB */
		.word	0x35A3C38D, 	0x241AE2AB,		0x241AC287,		0x231A01E7	/* 128MB */
		.word	0x35A5E38D, 	0x241C62AB,		0x241C2287,		0x231B21E7	/* 256MB */
		
		.text
		.global	DDR2_CFG1_TBL
		.align	3
DDR2_CFG1_TBL:
			/* 233MHZ */	/* 175MHZ */	        /* 166MHZ */	        /* 125MHZ */
		.word	0x222E2424, 	0x222E2324,		0x222E2324,		0x212E2223	/* 32MB */
		.word	0x22322424, 	0x22322324,		0x22322324,		0x21322223	/* 64MB */
		.word	0x22362424, 	0x22362324,		0x22362324,		0x21362223	/* 128MB */
		.word	0x223A2424, 	0x223A2324,		0x223A2324,		0x213A2223	/* 256MB */
		
		.text
		.align	3
			/* 233MHZ */	/* 175MHZ */	       /* 166MHZ */	        /* 125MHZ */
DDR2_CFG2_TBL:
		.word	0x68000E43, 	0x40000C43,		0x40000C43,		0x40000843
DDR2_CFG3_TBL:
		.word	0x10000400, 	0x00000400,		0x00000402,		0x00000402
DDR2_CFG4_TBL:
		.word	0x0010080C, 	0x0000000B,		0x0000000B,		0x0000000B
#endif	
