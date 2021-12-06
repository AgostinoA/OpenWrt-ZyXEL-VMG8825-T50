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

#if defined(CONFIG_COMCERTO_1000)

#define MDMA_GBL_CTRL_CFG           *((volatile u32 *)(MDMA_BASEADDR + 0x0))
#define MDMA_TX1_PATH_HEAD          *((volatile u32 *)(MDMA_BASEADDR + 0x4))
#define MDMA_TX1_PATH_CTR           *((volatile u32 *)(MDMA_BASEADDR + 0x8))
#define MDMA_RX1_PATH_HEAD          *((volatile u32 *)(MDMA_BASEADDR + 0x14))
#define MDMA_RX1_PATH_CTR           *((volatile u32 *)(MDMA_BASEADDR + 0x18))
#define MDMA_INT_MASK_REG           *((volatile u32 *)(MDMA_BASEADDR + 0x28))
#define MDMA_INT_STATUS_REG0        *((volatile u32 *)(MDMA_BASEADDR + 0x2c))
#define MDMA_INT_STATUS_REG1        *((volatile u32 *)(MDMA_BASEADDR + 0x30))

typedef struct mdma_desc_s
{
  u32 dataBufAddr;
  u32 control;
  u32 msg1;
  u32 msg2;
} mdma_desc_t;

/*****************************************************************************
 * Function: mdma_memcpy
 * Desction:
 *   Implemenation of memcpy function using MDMA.
 *   No CRC mechanism supported in C1K.
 * Paramters:
 *   src: Source address
 *   dst: Destination address
 *   len: length of the data to be copied.
 *   crc: Not used
 *****************************************************************************/
int mdma_memcpy(void *src, void *dst, int len, unsigned int *crc)
{
  u32 stat;
  int i;
  unsigned char temp1[64];
  unsigned char temp2[64];

  //descriptor memset to zero
  for(i=0; i < 64; i++)
  {
	temp1[i] = 0;
 	temp2[i] = 0;
  }

  len = len - (len % 8);
  
  //Disable MDMA
  MDMA_GBL_CTRL_CFG = __cpu_to_le32(0);

  //Make it 16byte align
  mdma_desc_t *txDesc = (mdma_desc_t *)(((u32)(temp1 + 16)) & ~0xf);
  mdma_desc_t *rxDesc = (mdma_desc_t *)(((u32)(temp2 + 16)) & ~0xf);

  txDesc->dataBufAddr = __cpu_to_le32((u32)src);
  txDesc->control = __cpu_to_le32((u32)(0x41002000 | (len & 0x1fff)));
  txDesc->msg1 = txDesc->msg2 = __cpu_to_le32(0);
  MDMA_TX1_PATH_HEAD = __cpu_to_le32((u32)txDesc);
  MDMA_TX1_PATH_CTR = __cpu_to_le32(1);

  rxDesc->dataBufAddr = __cpu_to_le32((u32)dst);
  rxDesc->control = __cpu_to_le32((u32)(0x41002000 | (len & 0x1fff))); 
  rxDesc->msg1 = rxDesc->msg2 = __cpu_to_le32(0);
  MDMA_RX1_PATH_HEAD = __cpu_to_le32((u32)rxDesc);
  MDMA_RX1_PATH_CTR = __cpu_to_le32(1);

  MDMA_INT_MASK_REG = __cpu_to_le32(0);
  MDMA_GBL_CTRL_CFG = __cpu_to_le32(1);  //Enable MDMA 

  /* wait until dma done */
  while((stat = __le32_to_cpu(MDMA_RX1_PATH_CTR)) != 0);

  //Memcpy done, disable MDMA
  MDMA_GBL_CTRL_CFG = __cpu_to_le32(0);

  return 0;
}

#elif defined(CONFIG_COMCERTO_100)

#define MDMA_MMFIFO_START           *((volatile u32 *)(MDMA_BASEADDR + 0x100))
#define MDMA_MMFIFO_HEADPTR         *((volatile u32 *)(MDMA_BASEADDR + 0x104))
#define MDMA_MMFIFO_LOCK_TSFR_SIZE  *((volatile u32 *)(MDMA_BASEADDR + 0x108))
#define MDMA_MMFIFO_SOFT_RESET      *((volatile u32 *)(MDMA_BASEADDR + 0x120))

#define MDMA_FIFOMM_START           *((volatile u32 *)(MDMA_BASEADDR + 0x180))
#define MDMA_FIFOMM_HEADPTR         *((volatile u32 *)(MDMA_BASEADDR + 0x184)) 
#define MDMA_FIFOMM_LOCK_TSFR_SIZE  *((volatile u32 *)(MDMA_BASEADDR + 0x188))
#define MDMA_FIFOMM_SOFT_RESET      *((volatile u32 *)(MDMA_BASEADDR + 0x1A0))

typedef struct mdma_bPtr_s
{
  u32 Bpointer;
  u32 Bcontrol;
}mdma_bPtr_t;

typedef struct mdma_Fdesc_s
{
  u32 Fnext;
  u32 Fsystem;
  u32 Fstatus;
  u32 Fcontrol;

  mdma_bPtr_t Bdesc;

}mdma_Fdesc_t;


int mdma_memcpy(void *src, void *dst, int len, unsigned int *crc)
{
  unsigned char temp1[64];
  unsigned char temp2[64];
  volatile unsigned int val;
  int i;

  //Make it 16byte align
  mdma_Fdesc_t *mmfifo = (mdma_Fdesc_t *)(((u32)(temp1 + 16)) & ~0xf);
  mdma_Fdesc_t *fifomm = (mdma_Fdesc_t *)(((u32)(temp2 + 16)) & ~0xf);

  //descriptor memset to zero
  for(i=0; i < 64; i++)
  {
	temp1[i] = 0;
 	temp2[i] = 0;
  }

  /* memory to FIFO */
  mmfifo->Fnext = __cpu_to_le32(0x0);
  mmfifo->Fsystem = __cpu_to_le32(0);
  mmfifo->Fstatus = __cpu_to_le32(0);
  mmfifo->Fcontrol = __cpu_to_le32(0x83);
  mmfifo->Bdesc.Bpointer = __cpu_to_le32((u32)src);
  mmfifo->Bdesc.Bcontrol = __cpu_to_le32((0x10000 | (len & 0xffff)));

  /* FIFO to memory */
  fifomm->Fnext = __cpu_to_le32(0x0);
  fifomm->Fsystem = __cpu_to_le32(0x0);
  fifomm->Fstatus = __cpu_to_le32(0x0);
  fifomm->Fcontrol = __cpu_to_le32(0x83);
  fifomm->Bdesc.Bpointer = __cpu_to_le32((u32)dst);
  fifomm->Bdesc.Bcontrol = __cpu_to_le32(len & 0xffff);

  MDMA_MMFIFO_SOFT_RESET = __cpu_to_le32(1);
  MDMA_FIFOMM_SOFT_RESET = __cpu_to_le32(1);

  MDMA_MMFIFO_HEADPTR = __cpu_to_le32((u32)mmfifo);
  MDMA_MMFIFO_LOCK_TSFR_SIZE = __cpu_to_le32(64);

  MDMA_FIFOMM_HEADPTR = __cpu_to_le32((u32)fifomm);
  MDMA_FIFOMM_LOCK_TSFR_SIZE = __cpu_to_le32(64);

  MDMA_MMFIFO_START = __cpu_to_le32(0x1);
  MDMA_FIFOMM_START = __cpu_to_le32(0x1);

  while ((val = __le32_to_cpu(mmfifo->Fstatus)) == 0);
  while ((val = __le32_to_cpu(fifomm->Fstatus)) == 0);

  /* Return the CRC value */
  *crc = __le32_to_cpu(fifomm->Fsystem);

  return 0;
}
#endif
