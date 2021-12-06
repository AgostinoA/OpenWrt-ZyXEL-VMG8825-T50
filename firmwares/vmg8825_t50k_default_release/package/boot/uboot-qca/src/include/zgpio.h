#ifndef __ZLOADER_GPIO_H__
#define __ZLOADER_GPIO_H__

#define ZGPIO_CONFIG_OUTPUT     1
#define ZGPIO_CONFIG_INPUT      2

#define ZGPIO_LEVEL_HIGH        1
#define ZGPIO_LEVEL_LOW         0

extern int configure_pio(int pio, int dir);
extern int set_pio(int pio, int level);
extern int get_pio(int pio, int *level);
extern int max_pio_num(void);
extern void dump_pio_regs(void);
#endif

