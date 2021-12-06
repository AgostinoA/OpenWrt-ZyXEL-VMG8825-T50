/*
 * (C) Copyright Mindspeed Technologies Inc.
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
 */
#include <common.h>
#include <asm/hardware.h>

extern u32*  __training_data_start;

typedef struct {
	unsigned char rd0;
	unsigned char rd1;
	unsigned char rd2;
	unsigned char rd3;
} dll_rd;


u32 wr_loop(u8 dqs_index, u32 find_median);
dll_rd DLL_check(u8 dqs_index, u8 wr_index, u32 find_median);
u32 wr_rd_transaction(u32 transaction_size, u32 i,  u8 dqs_index, u8 wr_index,u8 rd_index, u32 mask);
u32 actual_transaction(u32 transaction_size, u32 i,  u32 mask, u32 ddr_addr, u32 dll_num);
u32 get_dll(u32 i);
u32 get_max_addr_space_bit(void);
void training_gbl_init(void);
u32 find_best(void);


u32 ddr_addr_offset;
u32 max_addr_space_bit;
u8 byte_list[16];
u16 half_word_list[16];
u32 word_list[16];
u64 dword_list[16];
u32 byte_mask[4];
u32 max_addr_bit_list[15];


#define SZ_1K	0x400
#define SZ_1M	0x100000
#define SZ_4K	SZ_1K * 4
#define SZ_8K	SZ_1K * 8
#define SZ_16K	SZ_1K * 16
#define SZ_32K	SZ_1K * 32
#define SZ_64K	SZ_1K * 64
#define SZ_128K	SZ_1K * 128
#define SZ_8M	SZ_1M * 8
#define SZ_16M	SZ_1M * 16
#define SZ_32M	SZ_1M * 32
#define SZ_64M	SZ_1M * 64

#define ADDR_JUMP_SIZE	SZ_128K


void start_training(void)
{
	//initialize global data
	training_gbl_init();

	//start DDR training
	find_best();
}

void training_gbl_init(void)
{
	u8 i = 0;
	u8 __byte_list[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x19, 0x2a, 0x3b, 0x4c, 0x5d, 0x6e, 0x7f};
	u16 __half_word_list[16] = {0x0000, 0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666, 0x7777, 0x0888, 0x1999, 0x2aaa, 0x3bbb, 0x4ccc, 0x5ddd, 0x6eee, 0x7fff};
	u32 __word_list[16] = {0x00000000, 0x11111111, 0x22222222, 0x33333333, 0x44444444, 0x55555555, 0x66666666, 0x77777777, 0x08888888, 0x19999999, 0x2aaaaaaa, 0x3bbbbbbb, 0x4ccccccc, 0x5ddddddd, 0x6eeeeeee, 0x7fffffff};
	u64 __dword_list[16] = {0x0000000000000000LL, 0x1111111111111111LL, 0x2222222222222222LL, 0x3333333333333333LL, 0x4444444444444444LL, 0x5555555555555555LL, 0x6666666666666666LL, 0x7777777777777777LL, 0x0888888888888888LL, 0x1999999999999999LL, 0x2aaaaaaaaaaaaaaaLL, 0x3bbbbbbbbbbbbbbbLL, 0x4cccccccccccccccLL, 0x5dddddddddddddddLL, 0x6eeeeeeeeeeeeeeeLL, 0x7fffffffffffffffLL};
	u32 __byte_mask[4]  = {0xff,0xff00,0xff0000,0xff000000}; 
	u32 __max_addr_bit_list[15] = {0x00100000, 0x00200000, 0x00400000, 0x00800000, 0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000};
	u32 __ddr_addr_offset = 0;
	u32 __max_addr_space_bit = 0;

	// remap global data to internal memory
	ddr_addr_offset = (u32)&__training_data_start;
	max_addr_space_bit = (u32)(&__training_data_start + sizeof(ddr_addr_offset));
	byte_list[i] = (u8)(&__training_data_start + sizeof(max_addr_space_bit));
	half_word_list[i] = (u16)(&__training_data_start + sizeof(byte_list));
	word_list[i] = (u32)(&__training_data_start + sizeof(half_word_list));
	dword_list[i] = (u64)(&__training_data_start + sizeof(word_list));


	ddr_addr_offset = __ddr_addr_offset;
	max_addr_space_bit = __max_addr_space_bit;

	for (i = 0; i < 16; i++)
	{
		byte_list[i] = __byte_list[i];
		half_word_list[i] = __half_word_list[i];
		word_list[i] = __word_list[i];
		dword_list[i] = __dword_list[i];
	}

	for (i = 0; i < 4; i++)
		byte_mask[i]  = __byte_mask[i]; 
	
	for (i = 0; i < 15; i++)
		max_addr_bit_list[i] = __max_addr_bit_list[i];

}

u32 find_best(void)
{
	u8 dqs_ind = FAILURE; // dqs indication initialize to failure
	u8 dqs_min_val = UNSET, dqs_max_val = UNSET, dqs_median = UNSET; 
	u8 dqs_index;
	u8 wr_median_val, rd_median, rslt= FAILURE;
	u32 i;
	u32 wr_rslt = FAILURE;
	u32 dll_num; 
	register int reg_0 __asm__ ("r3");
	register int reg_1 __asm__ ("r4");
	u32 max_mem_reg;
	u64 *dst, *src;
	dll_rd rd;

  	ddr_addr_offset = 0; // init
  	if ((__le64_to_cpu(*(&CS_MAP)) & 0x3) == 3) {
  		max_addr_space_bit = get_max_addr_space_bit();
  	}

	for(dqs_index = LOW_DQS_OUT; dqs_index <= HIGH_DQS_OUT; dqs_index++) {// DQS loop
		wr_rslt = wr_loop(dqs_index, 0);
		// set min/max values;
		if (wr_rslt  == FAILURE) {
			if ((dqs_min_val != UNSET) && (dqs_min_val==(dqs_index-1))) {
				dqs_min_val = UNSET;
			}
			if ((dqs_min_val!=UNSET) && (dqs_max_val==UNSET)){
				dqs_max_val = dqs_index-1; 
				break;
			}
		} else { // SUCCESS
			if (dqs_min_val==UNSET) {
				dqs_min_val = dqs_index; 
				dqs_ind = SUCCESS;
			}
		} 
	} 

	if (dqs_ind == FAILURE) {
		wr_median_val = HIGH_DQS_OUT;
		dqs_median    = HIGH_WR_DQS;
		rd.rd0        = HIGH_RD0;
		rd.rd1        = HIGH_RD1;
		rd.rd2        = HIGH_RD2;
		rd.rd3        = HIGH_RD3;
		DENALI_WR_DQS  = wr_median_val;
		DENALI_DQS_OUT = dqs_median;
		DENALI_DQS_DELAY0 = rd.rd0;
		DENALI_DQS_DELAY1 = rd.rd1;
		DENALI_DQS_DELAY2 = rd.rd2;
		DENALI_DQS_DELAY3 = rd.rd3;
		return 0xffff;
	} else { //SUCCESS
		if ((dqs_min_val!=UNSET) && (dqs_max_val==UNSET)){
			dqs_max_val = dqs_index-1;
		}
		dqs_median = (dqs_min_val + dqs_max_val)/2;
	}

	// end procedure
	wr_median_val = wr_loop(dqs_median,1);
	rd = DLL_check(dqs_median,wr_median_val,1);
	if ((rd.rd0==0) || (rd.rd1==0) || (rd.rd2==0) || (rd.rd3==0)) {
		wr_median_val = HIGH_DQS_OUT;
		dqs_median    = HIGH_WR_DQS;
		rd.rd0        = HIGH_RD0;
		rd.rd1        = HIGH_RD1;
		rd.rd2        = HIGH_RD2;
		rd.rd3        = HIGH_RD3;
		DENALI_WR_DQS  = wr_median_val;
		DENALI_DQS_OUT = dqs_median;
		DENALI_DQS_DELAY0 = rd.rd0;
		DENALI_DQS_DELAY1 = rd.rd1;
		DENALI_DQS_DELAY2 = rd.rd2;
		DENALI_DQS_DELAY3 = rd.rd3;
		return 0xffff; // failure
	}

	//configure median values
	DENALI_WR_DQS  = wr_median_val;
	DENALI_DQS_OUT = dqs_median;
	DENALI_DQS_DELAY0 = rd.rd0;
	DENALI_DQS_DELAY1 = rd.rd1;
	DENALI_DQS_DELAY2 = rd.rd2;
	DENALI_DQS_DELAY3 = rd.rd3;


	max_mem_reg = __le64_to_cpu(*(&AHB_MAX_MEM_REG)) & (0x80000000 - ADDR_JUMP_SIZE);
	i=0;
	while (ddr_addr_offset<max_mem_reg) {
		i+=1;
		if ((i&0xc)==0) {
			rd_median = rd.rd0;
			dll_num=0;
		} else if ((i&0xc)==1) { 
			rd_median = rd.rd1;
			dll_num=1;
		} else if ((i&0xc)==2) { 
			rd_median = rd.rd2;
			dll_num=2;
		} else {
			rd_median = rd.rd3;
			dll_num=3;
		}
		if ((__le64_to_cpu(*(&REDUC)&0x1)==1) && ((dll_num==2) || (dll_num==3)))  {
			//REDUC 
			//half datapath mode in which DLL2 and 3 are not used.
			continue;
		}

		switch (i & 0x3) {
			case 0: 
				rslt = wr_rd_transaction(BYTE_SZ, dll_num, dqs_median, wr_median_val, rd_median,0);
				break;
			case 1: 
				rslt = wr_rd_transaction(HALF_WORD, dll_num, dqs_median, wr_median_val, rd_median,0);
				break;
			case 2: 
				rslt = wr_rd_transaction(WORD, dll_num, dqs_median, wr_median_val, rd_median,0);
				break;
			case 3: 
				rslt = wr_rd_transaction(DOUBLE_WORD, dll_num, dqs_median, wr_median_val, rd_median,0);
				break;
		};

		if (rslt == FAILURE) {
			wr_median_val = HIGH_DQS_OUT;
			dqs_median    = HIGH_WR_DQS;
			rd.rd0        = HIGH_RD0;
			rd.rd1        = HIGH_RD1;
			rd.rd2        = HIGH_RD2;
			rd.rd3        = HIGH_RD3;
			DENALI_WR_DQS  = wr_median_val;
			DENALI_DQS_OUT = dqs_median;
			DENALI_DQS_DELAY0 = rd.rd0;
			DENALI_DQS_DELAY1 = rd.rd1;
			DENALI_DQS_DELAY2 = rd.rd2;
			DENALI_DQS_DELAY3 = rd.rd3;
			return 0xffff;
		}
	};



	//*** burst ***
	for (i=0;i<16;i++) {
		src = &dword_list[i];
		dst = 0;
		 __asm__ __volatile__ ("ldmia %0, {%1,%2}" \
	        	  : "+r" (src), "=r" (reg_0), "=r" (reg_1) \
        	  );

		 __asm__ __volatile__ ("stmia %0, {%1,%2}" \
		          : "+r" (dst), "=r" (reg_0), "=r" (reg_1) \
	          );

		if (*src!=*dst)  {
			wr_median_val = HIGH_DQS_OUT;
			dqs_median    = HIGH_WR_DQS;
			rd.rd0        = HIGH_RD0;
			rd.rd1        = HIGH_RD1;
			rd.rd2        = HIGH_RD2;
			rd.rd3        = HIGH_RD3;
			DENALI_WR_DQS  = wr_median_val;
			DENALI_DQS_OUT = dqs_median;
			DENALI_DQS_DELAY0 = rd.rd0;
			DENALI_DQS_DELAY1 = rd.rd1;
			DENALI_DQS_DELAY2 = rd.rd2;
			DENALI_DQS_DELAY3 = rd.rd3;
			return 0xffff; //failure
		}
	}

	return SUCCESS;
}


u32 get_max_addr_space_bit(void) {
	u32 max_mem_reg;
	max_mem_reg = __le32_to_cpu(*(&AHB_MAX_MEM_REG));
	
	if ((max_mem_reg & 0x40000000) != 0) {
		return 31;
	} else if ((max_mem_reg & 0x20000000) != 0) {
		return 30;
	} else if ((max_mem_reg & 0x10000000) != 0) {
		return 29;
	} else if ((max_mem_reg & 0x08000000) != 0) {
		return 28;
	} else if ((max_mem_reg & 0x04000000) != 0) {
		return 27;
	} else if ((max_mem_reg & 0x02000000) != 0) {
		return 26;
	} else if ((max_mem_reg & 0x01000000) != 0) {
		return 25;
	} else if ((max_mem_reg & 0x00800000) != 0) {
		return 24;
	} else if ((max_mem_reg & 0x00400000) != 0) {
		return 23;
	} else if ((max_mem_reg & 0x00200000) != 0) {
		return 22;
	} else if ((max_mem_reg & 0x00100000) != 0) {
		return 21;
	};
	return 0;
}

u32 wr_loop(u8 dqs_index, u32 find_median) {
	u8 wr_index;
	u32 rd_rslt = FAILURE; //  rd indication initialize to failure: Failure or Success
	u8 wr_min_val = UNSET , wr_max_val = UNSET;
	u8 wr_median_val = FAILURE;
	dll_rd rd;

	for(wr_index = LOW_WR_DQS; wr_index <= HIGH_WR_DQS; wr_index++) { /* WR loop */
		rd = DLL_check(dqs_index, wr_index,find_median);
		rd_rslt = ((rd.rd0>0) && (rd.rd1>0) && (rd.rd2>0) && (rd.rd3>0)) ? SUCCESS : FAILURE;

		if (rd_rslt == FAILURE) {
			if (find_median == 1) {
				if ((wr_min_val != UNSET) && (wr_min_val==(wr_index-1))) {
					wr_min_val = UNSET;
				}
				if ((wr_min_val!=UNSET) && (wr_max_val==UNSET)) {
					wr_max_val = wr_index-1;
				}
				if ((wr_min_val!=UNSET) && (wr_max_val!=UNSET)) {
					wr_median_val = (wr_min_val+wr_max_val)/2;
					return wr_median_val;
				}
			}
		} else { // SUCCESS
			if (find_median == 1) {
				if (wr_min_val==UNSET) {
					wr_min_val = wr_index;
				}
			} else {
				return SUCCESS;
			}
		}	 
	}
	
	if (find_median == 1) {
		if ((wr_min_val!=UNSET) && (wr_max_val==UNSET)) {
			wr_max_val = wr_index-1;
			wr_median_val = (wr_min_val+wr_max_val)/2;
		}
	};

	return wr_median_val;
}

dll_rd DLL_check(u8 dqs_index, u8 wr_index, u32 find_median) {
	u32 transaction_size;
	u32 rslt = FAILURE, dll0_rslt = FAILURE, dll1_rslt = FAILURE, dll2_rslt = FAILURE, dll3_rslt = FAILURE;
	u8 rd_index;
	u32 i;
	dll_rd rd;
	u8 rd0_min_val=UNSET, rd1_min_val=UNSET, rd2_min_val=UNSET, rd3_min_val=UNSET;
	u8 rd0_max_val=UNSET, rd1_max_val=UNSET, rd2_max_val=UNSET, rd3_max_val=UNSET;
	u8 rd0_median=UNSET, rd1_median=UNSET, rd2_median=UNSET, rd3_median=UNSET;
	
	// byte order per DLL
	///////////////////////
	//  0     1     2     3
	//  4     5     6     7
	// DLL0  DLL1  DLL2  DLL4
	/////////// DLL0 //////////////
	for (rd_index = LOW_RD0; rd_index <= HIGH_RD0; rd_index++) {
		transaction_size = BYTE_SZ;   // byte (8 bits) 
		for(i = 0; i <= 15; i=i+4){ 
			rslt = wr_rd_transaction(transaction_size, i, dqs_index,wr_index,rd_index,1);
			if (rslt == FAILURE) continue;
			else if (rslt == SUCCESS) break;
		}
		if (rslt == SUCCESS) { // only for SUCCESS continue checking for the next transaction width	       
			transaction_size = DOUBLE_WORD;   // double-word (64 bits) 
			for(i = 0; i <= 15; i=i+16){ 
				rslt = wr_rd_transaction(transaction_size, i, dqs_index,wr_index,rd_index,1);
				if (rslt == FAILURE) continue;
				else if (rslt == SUCCESS) break;
			}// end of transaction_size DOUBLE_WORD
		} // end of transaction_size BYTE_SZ
 
		// find results of dll run
		if (find_median == 1) { 
			if (rslt == FAILURE) {
				if ((rd0_min_val != UNSET) && (rd0_min_val==(rd_index-1))) {
					rd0_min_val = UNSET;
				}
				if ((rd0_min_val != UNSET)  && (rd0_max_val == UNSET)) {
					rd0_max_val = rd_index-1;
					dll0_rslt = SUCCESS;
					break;
				}
				} else if (rslt == SUCCESS) {
					if (rd0_min_val == UNSET) {
						rd0_min_val = rd_index;
					}
				}
		} else {
			if (rslt == FAILURE) continue;
			else if (rslt == SUCCESS) break;// one SUCCESS is enough when no median calculation is needed
		} // dll0 median
	} // DLL0

	if (rslt == SUCCESS) dll0_rslt = SUCCESS;
	
	if (find_median == 1) { 
		if ((rd0_min_val != UNSET)  && (rd0_max_val == UNSET)) {
			rd0_max_val = rd_index-1;
		}
		rd0_median = (rd0_min_val + rd0_max_val)/2;
	}

	/////////// DLL1 //////////////
	for (rd_index = LOW_RD1; rd_index <= HIGH_RD1; rd_index++) {
		transaction_size = BYTE_SZ;   // byte (8 bits) 
		for(i = 1; i <= 15; i=i+4){ 
			rslt = wr_rd_transaction(transaction_size, i, dqs_index,wr_index,rd_index,1);
			if (rslt == FAILURE) continue;
			else if (rslt == SUCCESS) break;
		}
		if (rslt == SUCCESS) { // only for SUCCESS continue checking for the next transaction width
			transaction_size = DOUBLE_WORD;   // double-word (64 bits) 
			for(i = 1; i <= 15; i=i+16){ 
				rslt = wr_rd_transaction(transaction_size, i, dqs_index,wr_index,rd_index,1);
				if (rslt == FAILURE) continue;
				else if (rslt == SUCCESS) break;
			}// end of transaction_size DOUBLE_WORD
		} // end of transaction_size BYTE_SZ
	 
		// find results of dll run
		if (find_median == 1) { 
			if (rslt == FAILURE) {
				if ((rd1_min_val != UNSET) && (rd1_min_val==(rd_index-1))) {
					rd1_min_val = UNSET;
				}
				if ((rd1_min_val != UNSET)  && (rd1_max_val == UNSET)) {
					rd1_max_val = rd_index-1;
					dll1_rslt = SUCCESS;
					break;
				}
			} else if (rslt == SUCCESS) {
				if (rd1_min_val == UNSET) {
					rd1_min_val = rd_index;
				}
			}
		} else {
			if (rslt == FAILURE) continue;
			else if (rslt == SUCCESS) break;// one SUCCESS is enough when no median calculation is needed
		} // dll1 median
	} // DLL1


	if (rslt == SUCCESS) dll1_rslt = SUCCESS;

	if (find_median == 1) { 
		if ((rd1_min_val != UNSET)  && (rd1_max_val == UNSET)) {
			rd1_max_val = rd_index-1;
		}
		rd1_median = (rd1_min_val + rd1_max_val)/2;
	}

	if ((__le64_to_cpu(*(&REDUC))&0x1)==1)  {
		dll2_rslt = SUCCESS;
		dll3_rslt = SUCCESS;
	} else {
		/////////// DLL2 //////////////
		for (rd_index = LOW_RD2; rd_index <= HIGH_RD2; rd_index++) {
			transaction_size = BYTE_SZ;   // byte (8 bits) 
			for(i = 2; i <= 15; i=i+4){ 
				rslt = wr_rd_transaction(transaction_size, i, dqs_index,wr_index,rd_index,1);
				if (rslt == FAILURE) continue;
				else if (rslt == SUCCESS) break;
			}
			if (rslt == SUCCESS) { // only for SUCCESS continue checking for the next transaction width
				transaction_size = DOUBLE_WORD;   // double-word (64 bits) 
				for(i = 2; i <= 15; i=i+16){ 
					rslt = wr_rd_transaction(transaction_size, i, dqs_index,wr_index,rd_index,1);
					if (rslt == FAILURE) continue;
					else if (rslt == SUCCESS) break;
				}// end of transaction_size DOUBLE_WORD
			} // end of transaction_size BYTE_SZ
		
			// find results of dll run
			if (find_median == 1) { 
				if (rslt == FAILURE) {
					if ((rd2_min_val != UNSET) && (rd2_min_val==(rd_index-1))) {
						rd2_min_val = UNSET;
					}
					if ((rd2_min_val != UNSET)  && (rd2_max_val == UNSET)) {
						rd2_max_val = rd_index-1;
						dll2_rslt = SUCCESS;
						break;
					}
				} else if (rslt == SUCCESS) {
					if (rd2_min_val == UNSET) {
						rd2_min_val = rd_index;
					}
				}
			} else {
				if (rslt == FAILURE) continue;
				else if (rslt == SUCCESS) break;// one SUCCESS is enough when no median calculation is needed
			} // dll2 median
		} // DLL2
		
		if (rslt == SUCCESS) dll2_rslt = SUCCESS;
		
		if (find_median == 1) { 
			if ((rd2_min_val != UNSET)  && (rd2_max_val == UNSET)) {
				rd2_max_val = rd_index-1;
			}
			rd2_median = (rd2_min_val + rd2_max_val)/2;
		}
		
		/////////// DLL3 //////////////
		for (rd_index = LOW_RD3; rd_index <= HIGH_RD3; rd_index++) {
			transaction_size = BYTE_SZ;   // byte (8 bits) 
			for(i = 3; i <= 15; i=i+4){ 
				rslt = wr_rd_transaction(transaction_size, i, dqs_index,wr_index,rd_index,1);
				if (rslt == FAILURE) continue;
				else if (rslt == SUCCESS) break;
			}
			if (rslt == SUCCESS) { // only for SUCCESS continue checking for the next transaction width
				transaction_size = DOUBLE_WORD;   // double-word (64 bits) 
				for(i = 3; i <= 15; i=i+16){ 
					rslt = wr_rd_transaction(transaction_size, i, dqs_index,wr_index,rd_index,1);
					if (rslt == FAILURE) continue;
					else if (rslt == SUCCESS) break;
				}// end of transaction_size DOUBLE_WORD
			} // end of transaction_size BYTE_SZ
		
			// find results of dll run
			if (find_median == 1) { 
				if (rslt == FAILURE) {
					if ((rd3_min_val != UNSET) && (rd3_min_val==(rd_index-1))) {
						rd3_min_val = UNSET;
					}
				if ((rd3_min_val != UNSET)  && (rd3_max_val == UNSET)) {
					rd3_max_val = rd_index-1;
					dll3_rslt = SUCCESS;
					break;
				}
				} else if (rslt == SUCCESS) {
					if (rd3_min_val == UNSET) {
						rd3_min_val = rd_index;
					}
				}
			} else {
				if (rslt == FAILURE) continue;
				else if (rslt == SUCCESS) break;// one SUCCESS is enough when no median calculation is needed
			} // dll3 median
		} // DLL3
		if (rslt == SUCCESS) dll3_rslt = SUCCESS;
		if (find_median == 1) { 
			if ((rd3_min_val != UNSET)  && (rd3_max_val == UNSET)) {
				rd3_max_val = rd_index-1;
			}
			rd3_median = (rd3_min_val + rd3_max_val)/2;
		}
	}; // REDUC

	// all dll found a success values for current dqs and wr values.
	// For initialization: 0s indicates Failure
	rd.rd0 = 0;
	rd.rd1 = 0;
	rd.rd2 = 0;
	rd.rd3 = 0;
	if ((dll0_rslt & dll1_rslt & dll2_rslt & dll3_rslt & 0x1) == 1) {//return SUCCESS;
		if (find_median == 1) {
			rd.rd0 = rd0_median;
			rd.rd1 = rd1_median;
			rd.rd2 = rd2_median;
			rd.rd3 = rd3_median;
		} else {
			// 1s indicates Success
			rd.rd0 = 1;
			rd.rd1 = 1;
			rd.rd2 = 1;
			rd.rd3 = 1;
		}
	} 
	
	return rd; // 0s indicate Failure
}

u32 wr_rd_transaction(u32 transaction_size, u32 i, u8 dqs_index, u8 wr_index, u8 rd_index, u32 mask) {
	u32 dll_num;
	u32 ddr_addr, limit_addr;

 	// set values for current transaction
	DENALI_WR_DQS  = wr_index;
 	DENALI_DQS_OUT = dqs_index;
	dll_num = get_dll(i);
 	switch (dll_num) {
 		case 0:DENALI_DQS_DELAY0 = rd_index;break;
 		case 1:DENALI_DQS_DELAY1 = rd_index;break;
 		case 2:DENALI_DQS_DELAY2 = rd_index;break;
 		case 3:DENALI_DQS_DELAY3 = rd_index;break;
 	};
	
	limit_addr = __le64_to_cpu(*(&AHB_MAX_MEM_REG)) & 0x7fffffff;
	ddr_addr_offset = (ddr_addr_offset + ADDR_JUMP_SIZE) & limit_addr; // limit the address space to ahb configured value.
	
	// the address is shifted by 8 to ensure 64 byte transaction in region.
	// 0x80000000 + dll_num + offset *2^ (0 for byte, 1 for half word , 2 for word, 3 for double word.) 

	if ((__le64_to_cpu(*(&CS_MAP)) & 0x3) == 3) {
		ddr_addr = ddr_addr_offset;
		// default cs#0
		ddr_addr &= (~(max_addr_bit_list[max_addr_space_bit-21]));
 		if (actual_transaction(transaction_size, i, mask, ddr_addr, dll_num) == SUCCESS) {
			// set cs#1
			ddr_addr |= max_addr_bit_list[max_addr_space_bit-21];
			return actual_transaction(transaction_size, i, mask, ddr_addr, dll_num);
		} else {
			return FAILURE;
		}
	} else {
		return actual_transaction(transaction_size, i, mask, ddr_addr_offset, dll_num);
	} 
}

u32 get_dll(u32 i) {
	u32 rslt=0;
	switch (i) {
		case 0: case 4: case 8: case 12 : rslt = 0;break;
		case 1: case 5: case 9: case 13 : rslt = 1;break;
		case 2: case 6: case 10: case 14: rslt = 2;break;
		case 3: case 7: case 11: case 15: rslt = 3;break;
	};
	return rslt;
}

u32 actual_transaction(u32 transaction_size, u32 i, u32 mask, u32 ddr_addr, u32 dll_num) {
	u32 rslt = FAILURE;

	// per transaction width, write and read transaction.
	switch (transaction_size) {
	
	case BYTE_SZ: 
	if (mask == 1) {
		*(&WRITE_VAL_U8+i+ddr_addr) = 0x00;
		*(&WRITE_VAL_U8+i+0x10+ddr_addr) = 0xaa;
		*(&WRITE_VAL_U8+i+0x20+ddr_addr) = 0x55;
		if (((*(&WRITE_VAL_U8+i+ddr_addr)) & 0xff)==0x00) {
			if (((*(&WRITE_VAL_U8+i+0x10+ddr_addr)) & 0xff)==0xaa) {
				if (((*(&WRITE_VAL_U8+i+0x20+ddr_addr)) & 0xff)==0x55) {
					rslt = SUCCESS; // per dll
				}
			}
		}
		*(&WRITE_VAL_U8+i+ddr_addr) = 0;//clear
		*(&WRITE_VAL_U8+i+0x10+ddr_addr) = 0;//clear
		*(&WRITE_VAL_U8+i+0x20+ddr_addr) = 0;//clear
	} else {
		*(&WRITE_VAL_U8+ddr_addr) = 0x00;
		*(&WRITE_VAL_U8+0x10+ddr_addr) = 0xaa;
		*(&WRITE_VAL_U8+0x20+ddr_addr) = 0x55;
		if (*(&WRITE_VAL_U8+ddr_addr) == 0x00) {
			if (*(&WRITE_VAL_U8+0x10+ddr_addr) == 0xaa) {
				if (*(&WRITE_VAL_U8+0x20+ddr_addr) == 0x55) {
					rslt = SUCCESS;
				}
			}
		}
		*(&WRITE_VAL_U8+ddr_addr) = 0; //clear
		*(&WRITE_VAL_U8+i+0x10+ddr_addr) = 0;//clear
		*(&WRITE_VAL_U8+i+0x20+ddr_addr) = 0;//clear
	}
	break;
	
	case HALF_WORD:  // no masking option
	*(&WRITE_VAL_U16+ddr_addr) = __cpu_to_le16(0x0000);
	*(&WRITE_VAL_U16+0x10+ddr_addr) = __cpu_to_le16(0xaaaa);
	*(&WRITE_VAL_U16+0x20+ddr_addr) = __cpu_to_le16(0x5555);
	if (__le16_to_cpu(*(&WRITE_VAL_U16+ddr_addr)) == 0x0000) {
		if (__le16_to_cpu(*(&WRITE_VAL_U16+0x10+ddr_addr)) == 0xaaaa) {
			if (__le16_to_cpu(*(&WRITE_VAL_U16+0x20+ddr_addr)) == 0x5555) {
				rslt = SUCCESS;
			}
		}
	}
	*(&WRITE_VAL_U16+ddr_addr) = __cpu_to_le16(0); //clear
	*(&WRITE_VAL_U16+i+0x10+ddr_addr) = __cpu_to_le16(0);//clear
	*(&WRITE_VAL_U16+i+0x20+ddr_addr) = __cpu_to_le16(0);//clear
	break;
	
	case WORD:// no masking option
	*(&WRITE_VAL_U32+ddr_addr) = __cpu_to_le32(0x00000000);
	*(&WRITE_VAL_U32+0x10+ddr_addr) = __cpu_to_le32(0xaaaaaaaa);
	*(&WRITE_VAL_U32+0x20+ddr_addr) = __cpu_to_le32(0x55555555);
	if (__le32_to_cpu(*(&WRITE_VAL_U32+ddr_addr)) == 0x00000000) {
		if (__le32_to_cpu(*(&WRITE_VAL_U32+0x10+ddr_addr)) == 0xaaaaaaaa) {
			if (__le32_to_cpu(*(&WRITE_VAL_U32+0x20+ddr_addr)) == 0x55555555) {
				rslt = SUCCESS;
			}
		}
	}
	*(&WRITE_VAL_U32+ddr_addr) = __cpu_to_le32(0); //clear
	*(&WRITE_VAL_U32+0x10+ddr_addr) = __cpu_to_le32(0); //clear
	*(&WRITE_VAL_U32+0x20+ddr_addr) = __cpu_to_le32(0); //clear
	break;
	
	case DOUBLE_WORD: // no masking : full 64 bits
	*(&WRITE_VAL_U64+ddr_addr) = __cpu_to_le64(0x0000000000000000LL);
	*(&WRITE_VAL_U64+0x10+ddr_addr) = __cpu_to_le64(0x2aaaaaaaaaaaaaaaLL);
	*(&WRITE_VAL_U64+0x20+ddr_addr) = __cpu_to_le64(0x5555555555555555LL);
	if (__le64_to_cpu(*(&WRITE_VAL_U64+ddr_addr)) == 0x0000000000000000LL) {
		if (__le64_to_cpu(*(&WRITE_VAL_U64+0x10+ddr_addr)) == 0x2aaaaaaaaaaaaaaaLL) {
			if (__le64_to_cpu(*(&WRITE_VAL_U64+0x20+ddr_addr)) == 0x5555555555555555LL) {
				rslt = SUCCESS;
			}
		}
	}
	*(&WRITE_VAL_U64+ddr_addr) = __cpu_to_le64(0); //clear
	*(&WRITE_VAL_U64+0x10+ddr_addr) = __cpu_to_le64(0); //clear
	*(&WRITE_VAL_U64+0x20+ddr_addr) = __cpu_to_le64(0); //clear
	break;
	
	}; // switch transaction_size

	return rslt;
}


