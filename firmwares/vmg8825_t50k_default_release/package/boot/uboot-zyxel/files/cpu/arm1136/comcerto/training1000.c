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

//#define DDR_TRAINING_MODE_DEBUG_PRINTS  1
#undef  DDR_TRAINING_MODE_DEBUG_PRINTS

#define SZ_1K	        0x400
#define SZ_128K         (SZ_1K * 128)
#define ADDR_JUMP_SIZE  SZ_128K

#define MT_ADDR1_DST  (DDR_BASEADDR + 0xff00)
#define MT_ADDR2_DST  (DDR_BASEADDR + (PHYS_SDRAM_SIZE >> 1) + 0xff00) 

/* Controller register defines used in training */
#define DENALI_WR_DQS_DELAY0		*((volatile u8 *)(DDR_CONFIG_BASEADDR + 0x11B))
#define DENALI_WR_DQS_DELAY1		*((volatile u8 *)(DDR_CONFIG_BASEADDR + 0x11C))
#define DENALI_WR_DQS_DELAY2		*((volatile u8 *)(DDR_CONFIG_BASEADDR + 0x11D))
#define DENALI_WR_DQS_DELAY3		*((volatile u8 *)(DDR_CONFIG_BASEADDR + 0x11E))

#define DENALI_SW_LEVELING_START	*((volatile u8 *)(DDR_CONFIG_BASEADDR + 0x278))
#define DENALI_SW_LEVELING_MODE		*((volatile u8 *)(DDR_CONFIG_BASEADDR + 0x279))
#define DENALI_SW_LEVELING_LOAD		*((volatile u8 *)(DDR_CONFIG_BASEADDR + 0x276))

#define DENALI_DLL_MADJ0		*((volatile u8 *)(DDR_CONFIG_BASEADDR + 0x148))
#define DENALI_DLL_ADJ0		        *((volatile u8 *)(DDR_CONFIG_BASEADDR + 0x149))

#define DENALI_DLL_ADJ1_DS0		*((volatile u8 *)(DDR_CONFIG_BASEADDR + 0x14A))
#define DENALI_DLL_ADJ1_DS1		*((volatile u8 *)(DDR_CONFIG_BASEADDR + 0x14E))
#define DENALI_DLL_ADJ1_DS2		*((volatile u8 *)(DDR_CONFIG_BASEADDR + 0x152))
#define DENALI_DLL_ADJ1_DS3		*((volatile u8 *)(DDR_CONFIG_BASEADDR + 0x156))

#define DENALI_DLL_ADJ0_DS0             *((volatile u8 *)(DDR_CONFIG_BASEADDR + 0x149))
#define DENALI_DLL_ADJ0_DS1             *((volatile u8 *)(DDR_CONFIG_BASEADDR + 0x14D))
#define DENALI_DLL_ADJ0_DS2             *((volatile u8 *)(DDR_CONFIG_BASEADDR + 0x151))
#define DENALI_DLL_ADJ0_DS3             *((volatile u8 *)(DDR_CONFIG_BASEADDR + 0x155))

#define DENALI_DLL_ADJ3_DS0             *((volatile u8 *)(DDR_CONFIG_BASEADDR + 0x159))
#define DENALI_DLL_ADJ3_DS1             *((volatile u8 *)(DDR_CONFIG_BASEADDR + 0x15D))
#define DENALI_DLL_ADJ3_DS2             *((volatile u8 *)(DDR_CONFIG_BASEADDR + 0x161))
#define DENALI_DLL_ADJ3_DS3             *((volatile u8 *)(DDR_CONFIG_BASEADDR + 0x165))

static u8 do_wr_rd_transaction(u32 ddr_addr_offset, u64*, u32*, u16 mode);
static int mdma_test(u64 *);

extern void arm_write64(u64 data,volatile u64 *p);
extern int mdma_memcpy(void *src, void *dst, int len, unsigned int *crc);

extern int serial_init(void);
extern void serial_puts(const char *s);
extern void serial_putc(const char c);

typedef struct adj2_ds_s
{
  u8 win_start;
  u8 win_end;
  u8 win;

  u8 gWin;
  u8 gWin_start;
  u8 gWin_end;
  u8 inx; 
}adj2_ds_t;

typedef struct adj2_val_s
{
  adj2_ds_t ds0;
  adj2_ds_t ds1;
  adj2_ds_t ds2;
  adj2_ds_t ds3;
}adj2_val_t;

#ifdef DDR_TRAINING_MODE_DEBUG_PRINTS
/* use to print only byte */
static char *simple_itoa1(unsigned int i, char *s)
{
    char local[5];
    char *p = &local[4];
    *p-- = '\0';
	 i = i & 0xff;
    do {
        *p-- = '0' + i % 10;
        i /= 10;
    } while (i > 0);
    memcpy(s, p+1, 4);
    return s;
}
#endif

static void adj2_dsx_calculate_window(u8 result, u8 dll_val, u8 dqs_index, adj2_ds_t *adj2)
{
	u8 win;
#ifdef  DDR_TRAINING_MODE_DEBUG_PRINTS
	char s[5];
	u8 dsx = 0;
#endif

	if (!result) /* success */ 
	{
	  	/* its first time success, start counting from here */
		if (adj2->win_start == 0)
		{
			adj2->win_start = adj2->win_end = dll_val;
		}
		else  {
			adj2->win_end++;
			/* close the window, if we reach the end point of adj1 range */
			if (dll_val == ADJ1_MAX_VAL)  {
				win = (adj2->win_end - adj2->win_start) + 1;
			        if (adj2->win < win)
					adj2->win = win;

				/* is this window bigger than the previous one, then take it */
				if (adj2->gWin < win)
				{
					adj2->gWin = win;
					adj2->gWin_start = adj2->win_start;
					adj2->gWin_end = adj2->win_end;
					adj2->inx = dqs_index; 
				}
			}
		}
	}
	else /* failure */
	{
		if (adj2->win_start == 0)
		{
			//window not yet started, so nothing to do 
		}
		else
		{
			//this window ends here,calculate window size
			win = (adj2->win_end - adj2->win_start) + 1;

#ifdef  DDR_TRAINING_MODE_DEBUG_PRINTS
	    		serial_putc('\n');
			if (result & 0x1)
				dsx = 0;
			else if (result & 0x2)
				dsx = 1;
			else if (result & 0x4)
				dsx = 2;
			else if (result & 0x8)
				dsx = 3;
	    		serial_putc('[');
			serial_puts("ds");
	    		serial_puts(simple_itoa1(dsx,s));
	    		serial_putc(':');
	    		serial_puts(simple_itoa1(adj2->win_start,s));
	    		serial_putc('-');
	    		serial_puts(simple_itoa1(adj2->win_end,s));
	    		serial_putc('=');
	    		serial_puts(simple_itoa1(win,s));
	    		serial_putc(']');
#endif

			if (adj2->win < win)
			{
				adj2->win = win;
			}

			//is this window bigger than the previous one, then take it
			if (adj2->gWin < win)
			{
				adj2->gWin = win;
				adj2->gWin_start = adj2->win_start;
				adj2->gWin_end = adj2->win_end;
				adj2->inx = dqs_index; 
			}

			/* reset window pointer to measure next window */
			adj2->win_start = adj2->win_end = 0;
		}
	} /* failure */

	return;
}	

/* for basing on adj2 min value logic support */
static int get_adj2_adjusted_value(unsigned int *adj2_dsx, adj2_val_t *adj2, u16 ddr16bit_mode)
{
  u8 i, adj2_val;
  u16 ds, shift;
  u8 win_start, win_end, win;
  u8 gwin_start, gwin_end, gwin;
#ifdef  DDR_TRAINING_MODE_DEBUG_PRINTS
  unsigned char s[5];
#endif

  for(ds=0; ds < 4; ds++) {

    if ((ds == 2) && (ddr16bit_mode))
      goto done;

    shift = ds * 8;

    win_start = win_end = win = 0;
    gwin_start = gwin_end = gwin = 0;

#ifdef  DDR_TRAINING_MODE_DEBUG_PRINTS
    serial_puts("ds");
    serial_puts(simple_itoa1(ds, s));
    serial_putc('\n');
#endif

    for(i=ADJ2_MIN_VAL; i <= ADJ2_MAX_VAL; i++) {

       adj2_val = (u8)((adj2_dsx[i] >> shift) & 0xff);

        /* if, adj2 val is accepted */
       if (adj2_val >= ADJ1_MIN_ACCEPTED_WINDOW)  {
          if (win_start == 0)  {
	    win_start = win_end = i;
          }
          else {
	    win_end++;
	    /* close the window, if we reach the end of adj2 range */
	    if (i == ADJ2_MAX_VAL)  {
              win = win_end - win_start + 1;
	      if (gwin < win) {
	        gwin = win;
	        gwin_start = win_start;
	        gwin_end = win_end;
	      }

#ifdef  DDR_TRAINING_MODE_DEBUG_PRINTS
    	     serial_puts(simple_itoa1(win_start, s));
             serial_putc('-');
    	     serial_puts(simple_itoa1(win_end, s));
             serial_putc('=');
    	     serial_puts(simple_itoa1(win, s));
    	     serial_putc('\n');
#endif

	  }
        }
      }
      else  {
        /* if (win_start == 0) do nothing */
        if (win_start != 0)  {
	  win = win_end - win_start + 1;
	  if (gwin < win) {
	    gwin = win;
	    gwin_start = win_start;
	    gwin_end = win_end;
	  }

#ifdef  DDR_TRAINING_MODE_DEBUG_PRINTS
    	  serial_puts(simple_itoa1(win_start, s));
          serial_putc('-');
    	  serial_puts(simple_itoa1(win_end, s));
          serial_putc('=');
    	  serial_puts(simple_itoa1(win, s));
    	  serial_putc('\n');
#endif

	  win_start = win_end = 0;
        }
      }
    } /* end of for (adj2 for a given ds) */

    /* check for adj2 range size */
    if (gwin < ADJ2_MIN_ACCEPTED_RANGE)  {
	return -1;
    }
    else if (gwin < ADJ2_ACCEPTED_RANGE) {
        serial_puts("\nWARNING - DDR Training results may be Marginal\n");
    }

    switch (ds) {
      case 0 :
        adj2->ds0.inx = (gwin_start + gwin_end) >> 1;
        adj2->ds0.gWin = adj2_dsx[adj2->ds0.inx] & 0xff;
	break;
      case 1 : 
        adj2->ds1.inx = (gwin_start + gwin_end) >> 1;
        adj2->ds1.gWin = (adj2_dsx[adj2->ds1.inx] & 0xff00) >> 8;
	break;
      case 2 :
        adj2->ds2.inx = (gwin_start + gwin_end) >> 1;
        adj2->ds2.gWin = (adj2_dsx[adj2->ds2.inx] & 0xff0000) >> 16;
	break;
      case 3:
        adj2->ds3.inx = (gwin_start + gwin_end) >> 1;
        adj2->ds3.gWin = (adj2_dsx[adj2->ds3.inx] & 0xff000000) >> 24;
      default:
	break;
    }
  } /* end of for(ds) */

done:
  if (ddr16bit_mode)  {
     if ((adj2->ds0.gWin < ADJ1_ACCEPTED_WINDOW) || (adj2->ds1.gWin < ADJ1_ACCEPTED_WINDOW))   {
       goto warning;
     }
  }
  else {
     if ((adj2->ds0.gWin < ADJ1_ACCEPTED_WINDOW) || (adj2->ds1.gWin < ADJ1_ACCEPTED_WINDOW) ||
         (adj2->ds2.gWin < ADJ1_ACCEPTED_WINDOW) || (adj2->ds3.gWin < ADJ1_ACCEPTED_WINDOW))   {
       goto warning;
     }
  }
  return 0;

warning:
  serial_puts("\nWARNING - DDR Training results may be Marginal\n");
  return 0;
}


/* re-calculate the win_start and win_end values for the choosen adj2 */
void recalculate_adj1_window(u8 ddr16bit_mode, adj2_val_t *adj2,
			   u64 *dword_list, u32 *word_list)
{
  u8 dll_val;
  u8 ds;
  u32 result;
  u32 dqs_index;
  u32 ddr_addr_offset = 0;
  u64 dqs_value;
  
  /* Reset window pointers */
  adj2->ds0.win_start = adj2->ds0.win_end = 0;
  adj2->ds1.win_start = adj2->ds1.win_end = 0;
  adj2->ds2.win_start = adj2->ds2.win_end = 0;
  adj2->ds3.win_start = adj2->ds3.win_end = 0;

  adj2->ds0.win = 0;
  adj2->ds1.win = 0;
  adj2->ds2.win = 0;
  adj2->ds3.win = 0;

  adj2->ds0.gWin = 0;
  adj2->ds1.gWin = 0;
  adj2->ds2.gWin = 0;
  adj2->ds3.gWin = 0;

  for(ds = 0; ds < 4; ds++) {
    
    if ((ds == 2) && (ddr16bit_mode))
       return;

    if (ds == 0)
       dqs_index = adj2->ds0.inx;
    else if (ds == 1)
       dqs_index = adj2->ds1.inx;
    else if (ds == 2)
       dqs_index = adj2->ds2.inx;
    else if (ds == 3)
       dqs_index = adj2->ds3.inx;

    /* Configure the WRLVL_DELAY_X values */
    if (ddr16bit_mode) {
      dqs_value = __le64_to_cpu((*(volatile u64*)(DENALI_CTL_35_DATA))) & 0xffffff0000ffffffULL;
      dqs_value |= (u64)(((u64)dqs_index << 24) | ((u64)dqs_index << 32) );
    }
    else {
      dqs_value = __le64_to_cpu((*(volatile u64*)(DENALI_CTL_35_DATA))) & 0xff00000000ffffffULL;
      dqs_value |= (u64)(((u64)dqs_index << 24) | ((u64)dqs_index << 32) | ((u64)dqs_index << 40) | ((u64)dqs_index << 48));
    }
    arm_write64(dqs_value, (volatile u64 *)DENALI_CTL_35_DATA); //should be 64bit write

    //set sw leveling mode
    *(volatile u64*)(DENALI_CTL_67_DATA) = __cpu_to_le64((u64)DENALI_CTL_67_VAL_CFG1 | (1LL << 8));
    //sw leveling load
    *(volatile u64*)(DENALI_CTL_66_DATA) = __cpu_to_le64((u64)DENALI_CTL_66_VAL_CFG1 | (1LL << 48));
    //reset sw leveling mode
    *(volatile u64*)(DENALI_CTL_67_DATA) = __cpu_to_le64((u64)DENALI_CTL_67_VAL_CFG1);

    /* Looping through ADJ_1 range */
    for (dll_val = ADJ1_MIN_VAL; dll_val <= ADJ1_MAX_VAL; dll_val++)
    {
      /* Configure dll write click adj-1 values */
      DENALI_DLL_ADJ1_DS0 = (u8)dll_val;
      DENALI_DLL_ADJ1_DS1 = (u8)dll_val;
      if (!ddr16bit_mode)  {
        DENALI_DLL_ADJ1_DS2 = (u8)dll_val;
        DENALI_DLL_ADJ1_DS3 = (u8)dll_val;
      }

      result = do_wr_rd_transaction(ddr_addr_offset,dword_list,word_list, ddr16bit_mode);
      ddr_addr_offset = (ddr_addr_offset + ADDR_JUMP_SIZE) & (PHYS_SDRAM_SIZE -1);

      if (ds == 0)
        adj2_dsx_calculate_window((result & 0x1), dll_val, adj2->ds0.inx, &adj2->ds0);
      else if (ds == 1)
        adj2_dsx_calculate_window((result & 0x2), dll_val, adj2->ds1.inx, &adj2->ds1);
      else if (ds == 2)	
          adj2_dsx_calculate_window((result & 0x4), dll_val, adj2->ds2.inx, &adj2->ds2);
      else if (ds == 3)
          adj2_dsx_calculate_window((result & 0x8), dll_val, adj2->ds3.inx, &adj2->ds3);
    } /* for loop from dll min to max (ADJ_1) */ 

  } /* for each ds */

  return;
}

/* find the a bigger dll clk window for the given dqs value */
/* find a dll wr clk window for a given dqs_index,
 * this function updates the global dll and dqs values, if its finds any bigger window
 * than previous window, and then finally it configures the identified dqs and dll values
 * to DDR controller  */
void start_training(void)
{
  u32 word_list[16]  = { 0xffffffff, 0x00000000, 0x12345678, 0x9abcdef0,
			 0xf7f70202, 0xdfdf2020, 0x80407fbf, 0x08040204,
                         0x8080fdfd, 0x0808dfdf, 0xa5a55a5a, 0x5a5aa5a5,
			 0xaaaa5555, 0x5555aaaa, 0x0000ffff, 0x0000ffff};

  u64 dword_list[16]  = {0xffffffff00000000ULL, 0xffffffff00000000ULL, 
                         0x1234567876543210ULL, 0x0123456789abcdefULL,
			 0xf7f7f7f702020202ULL, 0xdfdfdfdf20202020ULL,
 		         0x804020107fbfdfefULL, 0x0804020110204080ULL,
                         0x80808080fdfdfdfdULL, 0x08080808dfdfdfdfULL,
			 0xa5a5a5a55a5a5a5aULL, 0x5a5a5a5aa5a5a5a5ULL,
			 0xaaaaaaaa55555555ULL, 0x55555555aaaaaaaaULL,
			 0x00000000ffffffffULL, 0x00000000ffffffffULL
                        };

  u8 dll_val;
  u8 result;
  u8 dqs_index;
  u32 ddr_addr_offset = 0;
  u64 dqs_value;
  adj2_val_t adj2;
  u16 ddr16bit_mode = 0;

  unsigned char sb[] = "\nDDR Training";
  unsigned char sd[] = "Done";
  unsigned char sf[] = "Fail";

#ifdef DDR_TRAINING_MODE_DEBUG_PRINTS
  unsigned char adj2_s[] = "\nAdj2:";
  char s[5];
  u8 i; 
#endif

  unsigned int adj2_dsx[256];

  /* Init of UART will be done later through main init sequence,
   * so doing init twice does it make any harm????, I think NO */
  serial_init();

  serial_puts(sb);

  /* check for 16bit mode */
  if(__le64_to_cpu(*(volatile u64*)(DENALI_CTL_18_DATA)) & 0x0000000001000000ULL)
    ddr16bit_mode = 1;

  adj2.ds0.gWin = 0;
  adj2.ds1.gWin = 0;
  adj2.ds2.gWin = 0;
  adj2.ds3.gWin = 0;

    /* Looping through ADJ_2 range */
    for(dqs_index = ADJ2_MIN_VAL; dqs_index <= ADJ2_MAX_VAL; dqs_index++)
    {
#ifdef  DDR_TRAINING_MODE_DEBUG_PRINTS
      serial_puts(adj2_s);
      serial_puts(simple_itoa1(dqs_index, s));
      serial_putc(':');
#endif
      serial_putc('.');

      /* Configure the WRLVL_DELAY_X values */
      if (ddr16bit_mode) {
        dqs_value = __le64_to_cpu((*(volatile u64*)(DENALI_CTL_35_DATA))) & 0xffffff0000ffffffULL;
        dqs_value |= (u64)(((u64)dqs_index << 24) | ((u64)dqs_index << 32) );
      }
      else {
        dqs_value = __le64_to_cpu((*(volatile u64*)(DENALI_CTL_35_DATA))) & 0xff00000000ffffffULL;
        dqs_value |= (u64)(((u64)dqs_index << 24) | ((u64)dqs_index << 32) | ((u64)dqs_index << 40) | ((u64)dqs_index << 48));
      }
      arm_write64(dqs_value, (volatile u64 *)DENALI_CTL_35_DATA); //should be 64bit write

      //set sw leveling mode
      *(volatile u64*)(DENALI_CTL_67_DATA) = __cpu_to_le64((u64)DENALI_CTL_67_VAL_CFG1 | (1LL << 8));
      //sw leveling load
      *(volatile u64*)(DENALI_CTL_66_DATA) = __cpu_to_le64((u64)DENALI_CTL_66_VAL_CFG1 | (1LL << 48));
      //reset sw leveling mode
      *(volatile u64*)(DENALI_CTL_67_DATA) = __cpu_to_le64((u64)DENALI_CTL_67_VAL_CFG1);

      /* Reset window pointers */
      adj2.ds0.win_start = adj2.ds0.win_end = 0;
      adj2.ds1.win_start = adj2.ds1.win_end = 0;
      adj2.ds2.win_start = adj2.ds2.win_end = 0;
      adj2.ds3.win_start = adj2.ds3.win_end = 0;
      adj2.ds0.win = 0;
      adj2.ds1.win = 0;
      adj2.ds2.win = 0;
      adj2.ds3.win = 0;

      /* Looping through ADJ_1 range */
      for (dll_val = ADJ1_MIN_VAL; dll_val <= ADJ1_MAX_VAL; dll_val++)
      {
        /* Configure dll write click adj-1 values */
        DENALI_DLL_ADJ1_DS0 = (u8)dll_val;
        DENALI_DLL_ADJ1_DS1 = (u8)dll_val;
	if (!ddr16bit_mode)  {
          DENALI_DLL_ADJ1_DS2 = (u8)dll_val;
          DENALI_DLL_ADJ1_DS3 = (u8)dll_val;
	}

        result = do_wr_rd_transaction(ddr_addr_offset,dword_list,word_list, ddr16bit_mode);
        ddr_addr_offset = (ddr_addr_offset + ADDR_JUMP_SIZE) & (PHYS_SDRAM_SIZE -1);

	adj2_dsx_calculate_window((result & 0x1), dll_val, dqs_index, &adj2.ds0);
	adj2_dsx_calculate_window((result & 0x2), dll_val, dqs_index, &adj2.ds1);
	if (!ddr16bit_mode)  {
	  adj2_dsx_calculate_window((result & 0x4), dll_val, dqs_index, &adj2.ds2);
	  adj2_dsx_calculate_window((result & 0x8), dll_val, dqs_index, &adj2.ds3);
	}
      } /* for loop from dll min to max (ADJ_1) */ 

      /* store the adj2 win values */
      if (ddr16bit_mode)
        adj2_dsx[dqs_index] = (adj2.ds1.win << 8) | (adj2.ds0.win);
      else
        adj2_dsx[dqs_index] = (adj2.ds3.win << 24) | (adj2.ds2.win << 16) | (adj2.ds1.win << 8) | (adj2.ds0.win);

    } //End of ADJ_2

#ifdef DDR_TRAINING_MODE_DEBUG_PRINTS
  serial_putc('\n');
  serial_puts(simple_itoa1(adj2.ds0.gWin,s));
  serial_putc('-');
  serial_puts(simple_itoa1(adj2.ds0.inx,s));
  serial_putc('\n');
  serial_puts(simple_itoa1(adj2.ds1.gWin,s));
  serial_putc('-');
  serial_puts(simple_itoa1(adj2.ds1.inx,s));
  serial_putc('\n');
  if (!ddr16bit_mode)  {
    serial_puts(simple_itoa1(adj2.ds2.gWin,s));
    serial_putc('-');
    serial_puts(simple_itoa1(adj2.ds2.inx,s));
    serial_putc('\n');
    serial_puts(simple_itoa1(adj2.ds3.gWin,s));
    serial_putc('-');
    serial_puts(simple_itoa1(adj2.ds3.inx,s));
    serial_putc('-');
  }

  serial_putc('\n');
  /* ds0 */
  for (i=ADJ2_MIN_VAL; i <= ADJ2_MAX_VAL; i++) {
  	serial_puts(simple_itoa1((adj2_dsx[i] & 0xff),s));
  	serial_putc(',');
  }
  serial_putc('\n');

  /* ds1 */
  serial_putc('\n');
  for (i=ADJ2_MIN_VAL; i <= ADJ2_MAX_VAL; i++) {
  	serial_puts(simple_itoa1((adj2_dsx[i] & 0xff00) >> 8,s));
  	serial_putc(',');
  }
  serial_putc('\n');

  if (!ddr16bit_mode)  {
    /* ds2 */
    serial_putc('\n');
    for (i=ADJ2_MIN_VAL; i <= ADJ2_MAX_VAL; i++) {
  	serial_puts(simple_itoa1((adj2_dsx[i] & 0xff0000) >> 16,s));
  	serial_putc(',');
    }
    serial_putc('\n');

    /* ds3 */
    serial_putc('\n');
    for (i=ADJ2_MIN_VAL; i <= ADJ2_MAX_VAL; i++) {
  	serial_puts(simple_itoa1((adj2_dsx[i] & 0xff000000) >> 24,s));
  	serial_putc(',');
    }
    serial_putc('\n');
  }
#endif

  if (get_adj2_adjusted_value(adj2_dsx, &adj2, ddr16bit_mode) < 0)
     goto error;

#ifdef DDR_TRAINING_MODE_DEBUG_PRINTS
  serial_puts(simple_itoa1(adj2.ds0.gWin,s));
  serial_putc('-');
  serial_puts(simple_itoa1(adj2.ds0.inx,s));
  serial_putc('\n');
  serial_puts(simple_itoa1(adj2.ds1.gWin,s));
  serial_putc('-');
  serial_puts(simple_itoa1(adj2.ds1.inx,s));
  serial_putc('\n');
  if (!ddr16bit_mode) {
    serial_puts(simple_itoa1(adj2.ds2.gWin,s));
    serial_putc('-');
    serial_puts(simple_itoa1(adj2.ds2.inx,s));
    serial_putc('\n');
    serial_puts(simple_itoa1(adj2.ds3.gWin,s));
    serial_putc('-');
    serial_puts(simple_itoa1(adj2.ds3.inx,s));
    serial_putc('-');
  }
#endif

  recalculate_adj1_window(ddr16bit_mode, &adj2, dword_list, word_list);

  /* Configure the WRLVL_DELAY_X values (ADJ_2) */
  if (ddr16bit_mode) {
    dqs_value = __le64_to_cpu((*(volatile u64*)(DENALI_CTL_35_DATA))) & 0xffffff0000ffffffULL;
    dqs_value |= (u64)(((u64)(adj2.ds0.inx) << 24) | 
		     ((u64)(adj2.ds1.inx) << 32));
  }
  else {
    dqs_value = __le64_to_cpu((*(volatile u64*)(DENALI_CTL_35_DATA))) & 0xff00000000ffffffULL;
    dqs_value |= (u64)(((u64)(adj2.ds0.inx) << 24) | 
		     ((u64)(adj2.ds1.inx) << 32) | 
		     ((u64)(adj2.ds2.inx) << 40) | 
		     ((u64)(adj2.ds3.inx) << 48));
  }
  arm_write64(dqs_value, (volatile u64 *)DENALI_CTL_35_DATA); //should be 64bit write

  //set sw leveling mode
  *(volatile u64*)(DENALI_CTL_67_DATA) = __cpu_to_le64((u64)DENALI_CTL_67_VAL_CFG1 | (1LL << 8));
  //sw leveling load
  *(volatile u64*)(DENALI_CTL_66_DATA) = __cpu_to_le64((u64)DENALI_CTL_66_VAL_CFG1 | (1LL << 48));
  //reset sw leveling mode
  *(volatile u64*)(DENALI_CTL_67_DATA) = __cpu_to_le64((u64)DENALI_CTL_67_VAL_CFG1);

  /* Configure wr_clk ADJ_1 */
  DENALI_DLL_ADJ1_DS0 = (u8)((adj2.ds0.gWin_start + adj2.ds0.gWin_end) >> 1);
  DENALI_DLL_ADJ1_DS1 = (u8)((adj2.ds1.gWin_start + adj2.ds1.gWin_end) >> 1);
  if (!ddr16bit_mode)  {
    DENALI_DLL_ADJ1_DS2 = (u8)((adj2.ds2.gWin_start + adj2.ds2.gWin_end) >> 1);
    DENALI_DLL_ADJ1_DS3 = (u8)((adj2.ds3.gWin_start + adj2.ds3.gWin_end) >> 1);
  }

  /* training verification using MDMA transfers */
  if (mdma_test(dword_list))
  {
    goto error;
  }

  serial_puts(sd);
  return;

error:
  serial_puts(sf);
  //watch dog reset
  //*(volatile unsigned int *)TIMER_WDT_HIGH_BOUND = 1;
  //*(volatile unsigned int *)TIMER_WDT_CONTROL = 1;
  while(1);

  return;
}

static u8 do_wr_rd_transaction(u32 ddr_address_offset, u64 *dword_list, u32 *word, u16 ddr16bit_mode)
{
  u8 j;
  register int reg_0 __asm__ ("r3");
  register int reg_1 __asm__ ("r4");
  u64 *src, *dst;
  u32 read_val;
  u8 ret_val = 0;

  ddr_address_offset &= ~0x3;

    /* Do 64bit wr+rd */
    dst = (u64 *)(DDR_BASEADDR+ddr_address_offset);
    src = dword_list;
    for(j=0; j < 16; j++)
    {
      __asm__ __volatile__ ("ldmia %0, {%1,%2}" \
          : "+r" (src), "=r" (reg_0), "=r" (reg_1) \
	  );

      __asm__ __volatile__ ("stmia %0, {%1,%2}" \
          : "+r" (dst), "=r" (reg_0), "=r" (reg_1) \
	  );

      if ((*src & 0x000000ff000000ffLL) != (*dst & 0x000000ff000000ffLL))
      {
        ret_val |= 1;
      }
      if ((*src & 0x0000ff000000ff00LL) != (*dst & 0x0000ff000000ff00LL))
      {
        ret_val |= 1 << 1;
      }

      if (!ddr16bit_mode)  {
        if ((*src & 0x00ff000000ff0000LL) != (*dst & 0x00ff000000ff0000LL))
        {
          ret_val |= 1 << 2;
        }
        if ((*src & 0xff000000ff000000LL) != (*dst & 0xff000000ff000000LL))
        {
          ret_val |= 1 << 3;
        }
      }
      *dst = __cpu_to_le64(0); //clear location

      dst++; 
      src++;
    }

    /* Do 32bit wr+rd */
    for (j=0; j < 16; j++)
    {
      *(((volatile u32 *)(DDR_BASEADDR+ddr_address_offset)) + j) = __cpu_to_le32(*word);

      read_val = __le32_to_cpu(*(((volatile u32 *)(DDR_BASEADDR+ddr_address_offset)) + j));
      if ((read_val & 0x000000FF) != (*word & 0x000000ff))
      {
	      ret_val |= 1;
      }
      if ((read_val & 0x0000ff00) != (*word & 0x0000ff00))
      {
	      ret_val |= 1 << 1;
      }
      if (!ddr16bit_mode)  {
        if ((read_val & 0x00ff0000) != (*word & 0x00ff0000))
        {
	      ret_val |= 1 << 2;
        }
        if ((read_val & 0xff000000) != (*word & 0xff000000))
        {
	      ret_val |= 1 << 3;
        }
      }

      *(((volatile u32 *)(DDR_BASEADDR+ddr_address_offset)) + j) = __cpu_to_le32(0); //clear location
      word++;
      ddr_address_offset = (ddr_address_offset + ADDR_JUMP_SIZE) & (PHYS_SDRAM_SIZE -1);
    }

    return ret_val;
}

/*
 * On success returns 0 
 */ 
static int mdma_test(u64 *dword_list)
{
  int ii,j;
  unsigned int *mdma_data = (u32 *)0x81000000;
  unsigned int *ddr_dst;
  unsigned int data_len[] = {1024, 1032, 1048, 1064};

  /* init mdma data, at this point we are sure that 32bit wr/rd operations are good */
  u32 *dataPtr = (u32 *)dword_list;
  for(j=0; j < 9; j++)
  {
    for(ii=0; ii < 32; ii++)
      mdma_data[32*j + ii] = __cpu_to_le32(dataPtr[ii]);
  }

  for(j=0; j < 4; j++)
  {
      ddr_dst = (unsigned int *)((j % 2) ? MT_ADDR1_DST : MT_ADDR2_DST);
      dataPtr = mdma_data;

      mdma_memcpy((void *)mdma_data, (void *)ddr_dst, data_len[j], NULL);

      for(ii=0; ii < data_len[j] >> 2; ii++)
        if (__le32_to_cpu(*dataPtr++) != __le32_to_cpu(*ddr_dst++))
	  return 1;
  }

  return 0; //MDMA test pass
}
