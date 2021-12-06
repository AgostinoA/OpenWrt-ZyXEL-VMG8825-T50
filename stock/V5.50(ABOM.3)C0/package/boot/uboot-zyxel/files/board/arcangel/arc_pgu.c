#include <config.h>
#include <common.h>
#include <command.h>
#include <version.h>
#include <stdarg.h>
#include <linux/types.h>

#include <lcd.h>
#include <asm/arc_pgu.h>

#ifdef CONFIG_LCD

char lcd_is_enabled;

int lcd_line_length;
int lcd_color_fg = 0xffff;
int lcd_color_bg = 0x0;

/*
 * Frame buffer memory information
 */
void *lcd_base;		/* Start of framebuffer memory	*/
void *lcd_console_address;	/* Start of console buffer	*/

short console_col;
short console_row;
vidinfo_t panel_info = { 
	vl_col: 640, 
	vl_row: 480, 
	vl_bpix: 4, 
	hsync: 0x3f4f031f, 
	vsync: 0x020c01f0, 
	max_freq: 23850000
};

#define PGU_BASEADDR 0xC0FC8000 

static arc_pgu *pgu_ptr = (arc_pgu *)PGU_BASEADDR;

void lcd_setcolreg(ushort regno, ushort red, ushort green, ushort blue)
{
}

void lcd_ctrl_init(void *lcdbase)
{
    lcd_base = lcdbase;
    pgu_ptr->frm_start = (unsigned)lcdbase;
    pgu_ptr->disp_dim = ENCODE_PGU_DIMS(panel_info.vl_col, panel_info.vl_row);
    pgu_ptr->stride = 2 * panel_info.vl_col;

    pgu_ptr->statctrl = STATCTRL_CONT_B_MASK | STATCTRL_PIX_FMT_RGB555 | 
	STATCTRL_HPOL_MASK | STATCTRL_VPOL_MASK | STATCTRL_DPOL_MASK;
}

void lcd_enable(void)
{
    pgu_ptr->statctrl |= STATCTRL_REG_DISP_EN_MASK;
    while ((pgu_ptr->statctrl &	STATCTRL_DISP_BUSY_MASK) && 
	    (pgu_ptr->statctrl & STATCTRL_BU_BUSY_MASK));
}

#endif

