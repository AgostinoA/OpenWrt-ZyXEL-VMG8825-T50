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
#include <asm/arch/bsp.h>

#define SZ_1K	0x400
#define SZ_128K  (SZ_1K * 128)
#define ADDR_JUMP_SIZE  SZ_128K
#define MIN_VALID_WINDOW_SIZE 5

#define NO_OF_PATTERNS   16 

#define WQS_START  0x30 
#define WQS_END    0x60
#define DOS_START  0x55
#define DOS_END    0x75
#define DDD_START  0x9
#define DDD_END    0x30

static int do_wr_rd_verify(u64 *);

u32 do_wr_rd_transaction(u32, u32*, u64*);
u32 do_wr_rd_transaction64(u32 ddr_address_offset, u64*);

extern int serial_init(void);
extern void serial_puts(const char *s);
extern void serial_putc(const char c);

#if 0
/* belongs in utility.c */
static char *simple_itoa(unsigned int i)
{
    /* 21 digits plus null terminator, good for 64-bit or smaller ints */
    static char local[22];
    char *p = &local[21];
    *p-- = '\0';
    do {
        *p-- = '0' + i % 10;
        i /= 10;
    } while (i > 0);
    return p + 1;
}
#endif


extern int mdma_memcpy(void *src, void *dst, int len, unsigned int *crc);
/*
 * On success returns 0 
 */ 
static int mdma_test(u64 *dword_list)
{
  int ii,j;
  unsigned int *mdma_data = (u32 *)0x81000000;
  unsigned int ddr_tmp = 0x80002000;
  unsigned int ddr_dst;
  unsigned int crc1, crc2;
  unsigned short data_len[] = {1024, 1032, 1048, 1064};

  /* init mdma data, at this point we are sure that 32bit wr/rd operations are good */
  u32 *dataPtr = (u32 *)dword_list;
  for(j=0; j < 9; j++)
  {
    for(ii=0; ii < 32; ii++)
      mdma_data[32*j + ii] = __cpu_to_le32(dataPtr[ii]);
  }

  for(ii=0; ii < 4; ii++)
  {
      ddr_dst = (ii % 2) ? 0x8000ff00 : 0x8300ff00;

      //CRC for write
      mdma_memcpy((void *)mdma_data, (void *)ddr_dst, data_len[ii], &crc1);

      //CRC for read
      mdma_memcpy((void *)ddr_dst, (void *)ddr_tmp, data_len[ii], &crc2);

      if(crc1 != crc2)
       return 1;
  }

  return 0; //MDMA test pass
}


/************************************************************************
 * Function: start_training
 * Description:
 *   Do the DDR training and configures the best values.
 * No return value
 ************************************************************************/
void start_training(void)
{

  u32 word_list[NO_OF_PATTERNS]  = { 0xffffffff, 0x00000000, 0x12345678, 0x9abcdef0,
			 0xf7f70202, 0xdfdf2020, 0x80407fbf, 0x08040204,
                         0x8080fdfd, 0x0808dfdf, 0xa5a55a5a, 0x5a5aa5a5,
			 0xaaaa5555, 0x5555aaaa, 0x0000ffff, 0x0000ffff};


  u64 dword_list[NO_OF_PATTERNS]  = {0xffffffff00000000ULL, 0xffffffff00000000ULL, 
                         0x1234567876543210ULL, 0x0123456789abcdefULL,
			 0xf7f7f7f702020202ULL, 0xdfdfdfdf20202020ULL,
 		         0x804020107fbfdfefULL, 0x0804020110204080ULL,
                         0x80808080fdfdfdfdULL, 0x08080808dfdfdfdfULL,
			 0xa5a5a5a55a5a5a5aULL, 0x5a5a5a5aa5a5a5a5ULL,
			 0xaaaaaaaa55555555ULL, 0x55555555aaaaaaaaULL,
			 0x00000000ffffffffULL, 0x00000000ffffffffULL
                        };

  unsigned char gbl_wqs_Vstart, gbl_wqs_Vend, cfg_wqs_Vstart, cfg_wqs_Vend, wqs_inx, wqs_Vstart;
  unsigned char gbl_dos,cfg_dos, dos_inx;
  unsigned char gbl_ddd_Vstart,gbl_ddd_Vend, ddd_Vstart, ddd_inx,ddd_median;
  int result;
  u32 ddr_addr_offset = 0xff00;
  unsigned char sb[] = "DDR Training";
  unsigned char sf[] = "Fail";
  unsigned char sd[] = "Done";
  unsigned char ch = '.';

  /* Init of UART will be done later through main init sequence,
   * so doing init twice does it make any harm????, I think NO */
  serial_init();

  serial_puts(sb);

  gbl_ddd_Vstart = gbl_ddd_Vend = ddd_Vstart = 0;
  cfg_wqs_Vstart = cfg_wqs_Vend = 0;
  gbl_dos = cfg_dos = 0;

  for(ddd_inx = DDD_START; ddd_inx <= DDD_END; ddd_inx++)  
  {
    serial_putc(ch);

    gbl_wqs_Vend = gbl_wqs_Vstart = 0;

    /* Configure DDD value */
    DENALI_DQS_DELAY0 = ddd_inx;
    DENALI_DQS_DELAY1 = ddd_inx;
    DENALI_DQS_DELAY2 = ddd_inx;
    DENALI_DQS_DELAY3 = ddd_inx;

    for (dos_inx = DOS_START; dos_inx <= DOS_END; dos_inx++)  
    {
      /* configure DOS value */
      DENALI_DQS_OUT  = dos_inx;

      wqs_Vstart = 0;
      for (wqs_inx = WQS_START; wqs_inx <= WQS_END; wqs_inx++) 
      {
        /* Configure WQS value */
	DENALI_WR_DQS   = wqs_inx;

	result =  do_wr_rd_transaction(ddr_addr_offset,word_list, dword_list);

        ddr_addr_offset = (ddr_addr_offset + ADDR_JUMP_SIZE) & (PHYS_SDRAM_SIZE - 1);

	if (result) 
        {  //result == FAIL 
	  /* check is this a window closing */
	  if (wqs_Vstart == 0)  
          { //No valid window started 
	    //Do nothing
	  }
	  else  
          {  //end of a valid window 
             if ((wqs_inx - wqs_Vstart) > (gbl_wqs_Vend - gbl_wqs_Vstart))  
             {
	       gbl_wqs_Vstart = wqs_Vstart;
	       gbl_wqs_Vend   = wqs_inx;
	       gbl_dos = dos_inx;
	     }
	     //else  Do nothing
             //{
             //}
	     wqs_Vstart = 0;
          }
	}
        else  
        { //results == SUCCESS
          if (wqs_Vstart == 0) 
          { //check is this a begining of valid window
	    wqs_Vstart = wqs_inx;
	  }
	  //else 
          //{ 
	    //Do nothing
	  //}
	}
      } //wqs_loop end

    } //dos_loop end

    if ((gbl_wqs_Vend - gbl_wqs_Vstart) > MIN_VALID_WINDOW_SIZE)  
    { //accepted window range 
      if (ddd_Vstart == 0) 
      {  //valid ddd window not yet started
	ddd_Vstart = ddd_inx;
      }
      //else 
      //{
        //do nothing
      //}
    }
    else 
    {
      if (ddd_Vstart == 0) 
      { //no accepted window range & no accepted window started till now
	//Do nothing
      }
      else 
      {
        if ((gbl_ddd_Vend - gbl_ddd_Vstart) < (ddd_inx - ddd_Vstart)) 
        {
	  gbl_ddd_Vend = ddd_inx;
	  gbl_ddd_Vstart = ddd_Vstart;
	}
	//else 
        //{
	  //Do nothing
	//}
	ddd_Vstart = 0;
      }
    }

    if ( (gbl_wqs_Vend - gbl_wqs_Vstart) > (cfg_wqs_Vend - cfg_wqs_Vstart)) 
    {
      cfg_wqs_Vend = gbl_wqs_Vend;
      cfg_wqs_Vstart = gbl_wqs_Vstart;
      cfg_dos      = gbl_dos;
    }
  } //ddd_loop end


  if ((cfg_wqs_Vend - cfg_wqs_Vstart) < MIN_VALID_WINDOW_SIZE)
  {
    serial_puts(sf);
    while(1);
  }

  ddd_median = (gbl_ddd_Vend + gbl_ddd_Vstart) >> 1;
  DENALI_DQS_DELAY0 = ddd_median;
  DENALI_DQS_DELAY1 = ddd_median;
  DENALI_DQS_DELAY2 = ddd_median;
  DENALI_DQS_DELAY3 = ddd_median;

  DENALI_DQS_OUT  = cfg_dos;
  DENALI_WR_DQS   = (cfg_wqs_Vend + cfg_wqs_Vstart) >> 1;

  /* Do verify the training values */
  /* 8Bit,16bit,32bit,64bit wr/rd */
  result = do_wr_rd_verify(dword_list);

  /* MDMA wr/rd */ 
  if (!result)
    result = mdma_test(dword_list);

  if (result)
  {
    serial_puts(sf);
    while(1);
  }

  serial_puts(sd);
  return;
}

u32 do_wr_rd_transaction(u32 ddr_addr_offset, u32 *word, u64 *dword_list)
{
    u32 i;

    /* Do 64bit wr+rd */
    if (do_wr_rd_transaction64(ddr_addr_offset,dword_list))
	    return 1; //failure

    /* Do 32bit wr+rd */
    for (i=0; i < NO_OF_PATTERNS; i++)
    {
      *((volatile u32 *)(DDR_BASEADDR + ddr_addr_offset) + i) = __cpu_to_le32(*word);

      if (__le32_to_cpu(*((volatile u32 *)(DDR_BASEADDR + ddr_addr_offset) + i)) != *word)
      {
        //reassign to zero 
        *((volatile u32 *)(DDR_BASEADDR + ddr_addr_offset) + i) = __cpu_to_le32(0);

	return 1; //failure
      }
      word++;

      //reassign to zero 
      *((volatile u32 *)(DDR_BASEADDR + ddr_addr_offset) + i) = __cpu_to_le32(0);
    }

    return 0; //success
}

u32 do_wr_rd_transaction64(u32 ddr_address_offset, u64 *dword_list)
{
  u8 j;
  register int reg_0 __asm__ ("r3");
  register int reg_1 __asm__ ("r4");
  u64 *src,*dst,*dval;
  u64 dword_store[NO_OF_PATTERNS];

  /* 64bit burst write */
  dst = ((volatile u64 *) (DDR_BASEADDR + ddr_address_offset));
  src = dword_list;
  for(j=0; j < NO_OF_PATTERNS; j++)
  {
    __asm__ __volatile__ ("ldmia %0, {%1,%2}" \
          : "+r" (src), "=r" (reg_0), "=r" (reg_1) \
	  );

    __asm__ __volatile__ ("stmia %0, {%1,%2}" \
          : "+r" (dst), "=r" (reg_0), "=r" (reg_1) \
	  );

    if (*src != (*dst))
      return 0x1;

    src++;
    dst++;
  }

  /* 64bit burst read 16 times */
  src = ((u64 *)(DDR_BASEADDR + ddr_address_offset));
  dst = dword_store;
  dval = dword_list;
  for(j=0; j < NO_OF_PATTERNS; j++)
  {
    __asm__ __volatile__ ("ldmia %0, {%1,%2}" \
          : "+r" (src), "=r" (reg_0), "=r" (reg_1) \
	  );

    __asm__ __volatile__ ("stmia %0, {%1,%2}" \
          : "+r" (dst), "=r" (reg_0), "=r" (reg_1) \
	  );

    if (*dval != *dst)
    {
      //reassign to zero
      *src = __cpu_to_le64(0x0ULL);

      return 0x1;
    }

    //reassign to zero
    *src = __cpu_to_le64(0x0ULL);

    src++;
    dst++;
    dval++;
  }

  return 0;
}

static int do_wr_rd_verify(u64 *dword_list)
{
  u8 i;
  u32 ddr_addr_offset = 0xffff00;
  u8 *list8 = (u8 *)dword_list;
  u16 *list16 = (u16 *)dword_list;
  u32 *list32 = (u32 *)dword_list;
  u64 *src_aram, *dst_ddr;
  register int reg_0 __asm__ ("r3");
  register int reg_1 __asm__ ("r4");

  src_aram = dword_list;
  dst_ddr = ((u64 *)(DDR_BASEADDR + ddr_addr_offset));
  for (i=0; i < NO_OF_PATTERNS; i++)
  {
    //8bit
    *((volatile u8 *)(DDR_BASEADDR + ddr_addr_offset) + i) = *(list8+i);
    if (*((volatile u8 *)(DDR_BASEADDR + ddr_addr_offset) + i) != *(list8+i))
      return 0x1;

    //16bit
    *((volatile u16 *)(DDR_BASEADDR + ddr_addr_offset) + i) = __cpu_to_le16(*(list16+i));
    if (__le16_to_cpu(*((volatile u16 *)(DDR_BASEADDR + ddr_addr_offset) + i)) != *(list16+i))
      return 0x1;

    //32bit
    *((volatile u32 *)(DDR_BASEADDR + ddr_addr_offset) + i) = __cpu_to_le32(*(list32+i));
    if (__le32_to_cpu(*((volatile u32 *)(DDR_BASEADDR + ddr_addr_offset) + i)) != *(list32+i))
      return 0x1;

    //64bit
    __asm__ __volatile__ ("ldmia %0, {%1,%2}" \
          : "+r" (src_aram), "=r" (reg_0), "=r" (reg_1) \
	  );

    __asm__ __volatile__ ("stmia %0, {%1,%2}" \
          : "+r" (dst_ddr), "=r" (reg_0), "=r" (reg_1) \
	  );

    if (*src_aram != (*dst_ddr))
      return 0x1;

    dst_ddr++;
    src_aram++;

    ddr_addr_offset = (ddr_addr_offset + ADDR_JUMP_SIZE) & (PHYS_SDRAM_SIZE - 1);
  }
  return 0;
}

