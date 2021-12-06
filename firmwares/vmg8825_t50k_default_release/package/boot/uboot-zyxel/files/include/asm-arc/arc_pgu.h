/*
 * arc_pgu.h - Register definitions for the ARC pixel graphics unit.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 * 
 * THIS	 SOFTWARE  IS PROVIDED	  ``AS	IS'' AND   ANY	EXPRESS OR IMPLIED
 * WARRANTIES,	  INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.	 IN
 * NO EVENT  SHALL   THE AUTHOR	 BE  LIABLE FOR ANY   DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED	  TO, PROCUREMENT OF  SUBSTITUTE GOODS	OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN	 CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * You should have received a copy of the  GNU General Public License along
 * with this program; if not, write  to the Free Software Foundation, Inc.,
 * 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Copyright 2005 (C) ARC International (www.arc.com). 
 * 
 */

#ifndef _ASM_ARC_PGU_H
#define _ASM_ARC_PGU_H


/*--------------------------------------------------------------------------------------------*/

/* Ioctl selectors	      FIXME - make sure these are unique within the fb subsystem */
#define ARCPGUFB_GETYUV		0xffff0001
#define ARCPGUFB_SETYUV		0xffff0002
#define ARCPGUFB_FILLYUV	0xffff0003
#define ARCPGUFB_SWITCH_YUV	0xffff0004
#define ARCPGUFB_BKLGHT_OFF	0xffff0005
#define ARCPGUFB_BKLGHT_ON	0xffff0006
#define ARCPGUFB_START_DISPLAY	0xffff0007
#define ARCPGUFB_STOP_DISPLAY	0xffff0008
#define ARCPGUFB_GET_PGU_STATE	0xffff0009
#define ARCPGUFB_SET_PGU_STATE	0xffff000a
#define ARCPGUFB_GET_MAIN_MODE	0xffff000b
#define ARCPGUFB_SET_MAIN_MODE	0xffff000c
#define ARCPGUFB_SET_RGB_BUF	0xffff000d
#define ARCPGUFB_GET_RGB_BUF	0xffff000e
#define ARCPGUFB_GET_FB_MAIN	0xffff000f
#define ARCPGUFB_CHECKPOINT	0xffff0010
#define ARCPGUFB_RESTORE	0xffff0011
#define ARCPGUFB_RESET		0xffff0012
#define ARCPGUFB_SET_YUV_RES	0xffff0013
#define ARCPGUFB_GET_FB_INFO	0xffff0014
#define ARCPGUFB_SET_OL_MODE	0xffff0015
#define ARCPGUFB_GET_OL_MODE	0xffff0016
#define ARCPGUFB_GET_OL_COLKEY	0xffff0017
#define ARCPGUFB_SET_OL_COLKEY	0xffff0018
#define ARCPGUFB_GET_OL_START	0xffff0019
#define ARCPGUFB_SET_OL_START	0xffff001a
#define ARCPGUFB_GET_OL_END	0xffff001b
#define ARCPGUFB_SET_OL_END	0xffff001c
#define ARCPGUFB_SET_OL_OFFSET	0xffff001d
#define ARCPGUFB_GET_YUV_BASE	0xffff002c /* return address of yuv buffer n */

#ifdef CONFIG_ENABLE_CENTERING
#define ARCPGUFB_GET_ORIGIN	0xffff001e
#define ARCPGUFB_SET_ORIGIN	0xffff001f
#endif

#define ARCPGUFB_ALLOC		0xffff0020
#define ARCPGUFB_FREE		0xffff0021
#define ARCPGUFB_SEND		0xffff0022
#define ARCPGUFB_FRAMERATE_SET	0xffff0023
#define ARCPGUFB_QUEUE_LEN_GET	0xffff0024
#define ARCPGUFB_FLUSH		0xffff0025
#define ARCPGUFB_FRAME_DROP	0xffff0026
#define ARCPGUFB_PAUSE		0xffff0027
#define ARCPGUFB_RESUME		0xffff0028
#define ARCPGUFB_RESET_SYNC	0xffff0029
#define ARCPGUFB_NUM_FREE_BUFS	0xffff002a
#define ARCPGUFB_PAUSE_MS	0xffff002b

#define ARCPGUFB_GET_STATCTRL	0xffff00fe
#define ARCPGUFB_SET_STATCTRL	0xffff00ff

/*--------------------------------------------------------------------------------------------*/

/* YUV buffer layout - all sizes and offsets in bytes. Note that base addresses tend to be 
   passed around as unsigned longs, in which case you'll need to typecast before applying 
   any offsets. */

struct yuv_info {
  unsigned int displayed_buffer;
  unsigned long phys_base;
  unsigned long virt_base;
  unsigned long yuv_size;
  unsigned long alignment;
  unsigned long num_buffers;
  unsigned long start_offset;
  unsigned long width;
  unsigned long height;
  unsigned long u_offset;
  unsigned long v_offset;
  unsigned long y_stride;
  unsigned long u_stride;
  unsigned long v_stride;
#ifdef CONFIG_ARC_PGU_CROPPING
  unsigned long cropped_width;
  unsigned long cropped_height;
  unsigned long x_offset;
  unsigned long y_offset;
#endif
};

/*--------------------------------------------------------------------------------------------*/

/* Register definitions */

/*	Base+0x00    PGU_MODULE_ID   Register containing read only module ID and
 *				     Revision numbers */
#define PGU_MODULE_ID_OFFSET 0x0
#define PGU_DISPLAY_TYPE_MASK 0x1000000
#define PGU_VERSION_MASK 0xff0000
#define PGU_VERSION_SHIFT 16

/*	 Base+0x08    CLK_CFG_REG     Clock Configuration register. It is used to
 *				      Define the clock divider value, and the
 *				      pulse width (high cycle) in clock cycles:
 *				      [ 7: 0] CLK_DIV  : clock divider value - 1
 *				      [23:16] CLK_HIGH : High pulse width - 1 */
#define CLK_CFG_REG_OFFSET 0x8
#define CLK_CFG_REG_CLK_DIV_MASK 0xff
#define CLK_CFG_REG_CLK_HIGH_MASK 0xff0000
#define GET_CLK_CFG_REG_CLK_HIGH_VAL(x) (x & CLK_CFG_REG_CLK_HIGH_MASK) >> 16
#define SET_CLK_CFG_REG_CLK_HIGH_VAL(x, y) (x & !CLK_CFG_REG_CLK_HIGH_MASK) | ((y << 16) & CLK_CFG_REG_CLK_HIGH_MASK)

/*	Base+0x10    DISP_DIM_REG    Display Dimensions register. This specify
 *				     the dimensions of the actual display.
 *				     [10: 0] PGU_X_RES : X dimension - 1
 *				     [26:16] PGU_Y_RES : Y dimension - 1 */

#define DISP_DIM_REG_OFFSET 0x10
#define DISP_DIM_REG_PGU_X_RES_MASK 0x3ff
#define DISP_DIM_REG_PGU_Y_RES_MASK 0x3ff0000
#define DISP_DIM_Y_SHIFT 16
#define ENCODE_PGU_DIMS(x,y) ((x & DISP_DIM_REG_PGU_X_RES_MASK) | ((y &	 DISP_DIM_REG_PGU_X_RES_MASK) * 0x10000))

/*	Base+0x18    HSYNC_CFG_REG   Hsync Configuration register. This is used
 *				     to specify various hsync related timings in
 *				     clock cycles:
 *				     [11: 0] HSYNC_CYC	 : Hsync period - 1
 *				     [23:16] H_BCK_PORTH : Back porth width - 1
 *				     [31:23] HSYNC_WIDTH : Hsync low width - 1 */

#define PGU_SYNC_REGS_CYC_MASK 0xfff
#define PGU_SYNC_REGS_PORCH_MASK 0xff0000
#define PGU_SYNC_REGS_WIDTH_MASK 0xff000000
#define PGU_SYNC_REGS_PORCH_OFFSET 16
#define PGU_SYNC_REGS_WIDTH_OFFSET 24

#define HSYNC_CFG_REG_OFFSET 0x18

/*	Base+0x20    VSYNC_CFG_REG   Vsync Configuration register. This is used
 *				     to specify various Vsync related timings in
 *				     Hsync cycles:
 *				     [11: 0] VSYNC_CYC	 : Vsync period - 1
 *				     [23:16] V_BCK_PORTH : Back porth width - 1
 *				     [31:23] VSYNC_WIDTH : Hsync low width */

#define VSYNC_CFG_REG_OFFSET 0x20

/*	Base+0x28   FRMSTART_REG     Frame Start Address. This 32 bit address
 *				     specifies the start of the display frame
 *				     in memory. Must be at least 2 byte aligned
 *				     for 16 bit per pixel format. */

#define FRMSTART_REG_OFFSET 0x28

/*	Base+0x30   STRIDE_REG	     Line Stride Address. This 32 bit address
 *				     specifies the different in address between
 *				     the first pixels of adjecent display lines
 *				     in memory. Must be at least 2 byte aligned
 *				     for 16 bit per pixel format. */

#define STRIDE_REG_OFFSET 0x30

/*	Base+0x38   FRM_DIM_REG	     Frame Dimension register. This register
 *				     defines the frame size of the display in
 *				     memory and can be smaller than the display.
 *				     [10:0] FRM_WTH  : frame line width in
 *						       pixels. Must be <=
 *						       PGU_X_RES without x2 mode
 *						       or <= PGU_X_RES/2 in x2 
 *						       mode.
 *				     [26:16] FRM_LNS : frame number of lines
 *						       Must be <= PGU_X_RES 
 *						       without x2 mode or <= 
 *						       PGU_X_RES/2 in x2 mode. */

#define FRM_DIM_REG_OFFSET 0x38
#define FRM_DIM_REG_FRM_WTH_MASK 0x7ff
#define FRM_DIM_REG_FRM_LNS_MASK 0x7ff
						   
/*
 *	Base+0x40   STATCTRL_REG     Status and Control register. This register
 *				     is used to control the display module and
 *				     monitor its status: */
#define STATCTRL_REG_OFFSET 0x40
/*				     [0] DISP_EN   : Display enable bit. When
 *						     set to high, starts the
 *						     display. It then clears 
 *						     after a few cycles, if
 *						     the CONT bit is not set,
 *						     hence allowing the display
 *						     to do the frame once. */
#define STATCTRL_REG_DISP_EN_MASK 1
/*				     [1] INTR_EN   : Interrupt Enable. Active
 *						     high. */
#define STATCTRL_INTR_EN_MASK 2
/*				     [2] INTR_CLR  : Interrupt Clear. Set to 
 *						     high to clear the interrupt
 *						     flag/request. Always reads
 *						     as zeros */
#define STATCTRL_INTR_CLR_MASK 4
/*				     [3] CONT	   : Continuous mode. When set,
 *						     will not allow the DISP_EN
 *						     bit to be cleared by itself
 *						     and as long as DISP_EN is
 *						     not cleared manually, the
 *						     Dispaly will drive the PGU
 *						     continuously, frame after
 *						     frame. */
#define STATCTRL_CONT_B_MASK 8
/*				     [5:4] PIX_FMT   Pixel Format. Select the
 *						     pixel format:
 *						     "00" - RGB555
 *						     "01" - YUV420 (aka YV12)
 *						     "10" - reserved
 *						     "11" - reserved */
#define STATCTRL_PIX_FMT_MASK 0x30
#define STATCTRL_PIX_FMT_OFFSET 4
#define STATCTRL_PIX_FMT_RGB555 0
#define STATCTRL_PIX_FMT_YUV420 0x10
/*				     [6] BACKLIGHT   Active high backlight 
 *						     enable. When set to high,
 *						     sets the back light control
 *						     signal to high to turn on
 *						     the backlight of the PGU. */
#define STATCTRL_BACKLIGHT_MASK 0x40
/*				     [7] X2	     Zoom 2 mode. when set, 
 *						     every pixel in the frame is
 *						     display twice in a line &
 *						     the line is displayed twice
 *						     therefore enlarging the
 *						     picture. */
#define STATCTRL_X2_MASK 0x80
/*				     [8] REV_LN_SCAN Reverse line scan. When set
 *						     the display displays the
 *						     last line first, back 
 *						     towards the first */
#define STATCTRL_REV_LN_SCAN_MASK 0x100
/*				     [9] HPOL	     HSync signal polarity */
#define STATCTRL_HPOL_MASK 0x200
/*				     [10] VPOL	     VSync signal polarity */
#define STATCTRL_VPOL_MASK 0x400
/*				     [11] DPOL	     Data enable signal polarity */
#define STATCTRL_DPOL_MASK 0x800
/*				     [12] OL_EN	     Overlay enable */
#define STATCTRL_OL_EN_MASK 0x1000
/*				     [13-15] OL_FMT  Overlay format:
 *						     "00" - RGBA4444
 *						     "01" - RGBA5551
 *						     "10" - RGB555 with colour keying */
#define STATCTRL_OL_FMT_MASK 0x6000
#define STATCTRL_OL_FMT_OFFSET 13
#define STATCTRL_OL_FMT_RGBA4444 0
#define STATCTRL_OL_FMT_RGBA5551 0x2000
#define STATCTRL_OL_FMT_RGB555 0x4000
/*				     [16] DISP_BUSY  Display Busy status. Active
 *						     High. When set indicates 
 *						     that the display is 
 *						     currently scanning out 
 *						     pixel data, or generating 
 *						     syncs for the current 
 *						     display */
#define STATCTRL_DISP_BUSY_MASK 0x10000
/*				     [17] BU_BUSY    Burst Unit busy. Active 
 *						     high. When set indicates
 *						     that the burst unit is
 *						     busy fetching pixel data. */
#define STATCTRL_BU_BUSY_MASK 0x20000
/*				     [18] INTR_FLG   Interrupt flag. Refelects
 *						     the interrupt signal.
 *						     Active low level interrupt. */
#define STATCTRL_INTR_FLAG 0x40000
/*				     [19-20] IL_MD   Interface mode select
 *						     "00" - Non-interlaced
 *						     "01" - Frame mode interlace
 *						     "10" - Even field interlace
 *						     "11" - Odd field interlace */
#define STATCTRL_IL_MODE_MASK 0x180000
#define STATCTRL_IL_NONE 0
#define STATCTRL_IL_FRAME 0x80000
#define STATCTRL_IL_EVEN 0x100000
#define STATCTRL_IL_ODD 0x180000

/*--------------------------------------------------------------------------------------------*/

typedef volatile struct	 {
  volatile unsigned long pgu_id;	 /* Identity register */
  volatile unsigned long padding1;
  volatile unsigned long clk_cfg;	 /* Clock control */
  volatile unsigned long padding2;
  volatile unsigned long disp_dim;	 /* Display dimension */
  volatile unsigned long padding3;
  volatile unsigned long hsync_cfg;	 /* HSYNC */
  volatile unsigned long padding4;
  volatile unsigned long vsync_cfg;	 /* VSYNC */
  volatile unsigned long padding5;
  volatile unsigned long frm_start;	 /* Frame start */
  volatile unsigned long padding6;
  volatile unsigned long stride;	 /* Frame stride */
  volatile unsigned long padding7;
  volatile unsigned long frm_dim;	 /* Frame dimension */
  volatile unsigned long padding8;
  volatile unsigned long statctrl;	 /* Status and control */
  volatile unsigned long padding9;
  volatile unsigned long cru_frm_st;	 /* Chroma U frame start */
  volatile unsigned long padding10;
  volatile unsigned long cru_stride;	 /* Chroma U stride */
  volatile unsigned long padding11;
  volatile unsigned long crv_frm_st;	 /* Chroma V frame start */
  volatile unsigned long padding12;
  volatile unsigned long crv_stride;	 /* Chroma V stride */

#ifdef CONFIG_ENABLE_ARCPGU_OVERLAY
  volatile unsigned long padding13;
  volatile unsigned long ol_frm_st;	 /* Overlay frame start */
  volatile unsigned long padding14;
  volatile unsigned long ol_stride;	 /* Overlay stride */
  volatile unsigned long padding15;
  volatile unsigned long ol_scn_line;	 /* Overlay start and end line numbers */
  volatile unsigned long padding16;
  volatile unsigned long ol_col_key;	 /* Overlay transparency colour key - RGB 555 */
#endif

#ifdef CONFIG_ENABLE_CENTERING
  volatile unsigned long padding17;
  volatile unsigned long centreoffsets;	 /* X, Y offsets for centering */
#endif
} arc_pgu;

/*--------------------------------------------------------------------------------------------*/

#endif	/* _ASM_ARC_PGU_H */
