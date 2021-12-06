#ifndef __FILE__H__
#define __FILE__H__
/*
 * Copyright (c) 2010 Quantenna Communications, Inc.
 * All rights reserved.
 *
 *  Board configuration definitions that only apply to the boot loader.
 *
 *  Most definitions have been moved to common/ruby_config.h
 *
 */

////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////

#ifndef BIT
#define BIT(x) 				(1L << (x))
#endif


////////////////////////////////////////////////////////////////////////////
// Typedefs
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////
/***************************************************************************
   Function:
   Purpose:
   Returns:
   Note: Code assumes parameter is within range
 **************************************************************************/
struct ruby_board_template;

int board_config(int board_id, int parameter);
int board_parse_custom_cfg(void *addr);
void board_setup_bda(void *addr, int board_id);

#endif // __BOARD_CFG_H__

