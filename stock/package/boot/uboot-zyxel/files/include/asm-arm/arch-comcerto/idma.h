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

#ifndef _IDMA_H
#define _IDMA_H

#define HDMA_SOFT_RESET			(IDMA_BASEADDR + 0x0000)

#define IDMA_EMAC0_BASEADDR		(IDMA_BASEADDR + 0x0100)

#define MMPU_START			(IDMA_BASEADDR + 0x0200)
#define MMPU_HEAD			(IDMA_BASEADDR + 0x0204)
#define MMPU_BURST			(IDMA_BASEADDR + 0x0208)
#define MMPU_SOFT_RESET			(IDMA_BASEADDR + 0x0220)

#define PUMM_START			(IDMA_BASEADDR + 0x0280)
#define PUMM_HEAD			(IDMA_BASEADDR + 0x0284)
#define PUMM_BURST			(IDMA_BASEADDR + 0x0288)
#define PUMM_SOFT_RESET			(IDMA_BASEADDR + 0x02A0)

#define MMFIFO_START			(IDMA_BASEADDR + 0x0300)
#define MMFIFO_HEAD			(IDMA_BASEADDR + 0x0304)
#define MMFIFO_BURST			(IDMA_BASEADDR + 0x0308)
#define MMFIFO_SOFT_RESET		(IDMA_BASEADDR + 0x0320)

#define FIFOMM_START			(IDMA_BASEADDR + 0x0380)
#define FIFOMM_HEAD			(IDMA_BASEADDR + 0x0384)
#define FIFOMM_BURST			(IDMA_BASEADDR + 0x0388)
#define FIFOMM_SOFT_RESET		(IDMA_BASEADDR + 0x03A0)

#define IDMA_EMAC1_BASEADDR		(IDMA_BASEADDR + 0x0700)

/* Memory to EMAC register offsets */
#define MMEM_START			0x00
#define MMEM_HEAD			0x04
#define MMEM_BURST			0x08
#define MMEM_SOFT_RESET			0x20


/* EMAC to Memory register offsets */
#define EMMM_START			0x80
#define EMMM_HEAD			0x84
#define EMMM_BURST			0x88
#define EMMM_SOFT_RESET			0xA0



#define	FDESC_ALIGN_BYTES		0x10

//************ IDMA registers and masks *****************
#define IDMA_FSTATUS_FRAME_DONE_MASK	0x80000000
#define IDMA_FSTATUS_STATUS_MASK			0x03FFFFFF

#define IDMA_FCONTROL_PHY_NB_MASK		0x00000070
#define IDMA_FCONTROL_PHY_OFFSET			0x00000004

#define IDMA_FCONTROL_IRQEN				0x00000004
#define IDMA_FCONTROL_FLAST				0x00000002
#define IDMA_FCONTROL_FREADY				0x00000001

#define IDMA_BCONTROL_BLAST				0x00010000
#define IDMA_BCONTROL_BLEN_MASK			0x0000FFFF

#define IDMA_FSTATUS_FDONE				0x80000000
#define IDMA_FSTATUS_BIT27					0x08000000
#define IDMA_FSTATUS_FKEEP				0x04000000


#define IDMA_START							0x00000001
#define IDMA_BURST_MASK					0x000000FF
#define IDMA_PRTY_MASK						0x00000700
#endif
