#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include <config.h>

#if defined(CONFIG_COMCERTO_1000)
#include "comcerto_1000.h"
#elif defined(CONFIG_COMCERTO_100)
#include "comcerto_100.h"
#elif defined(CONFIG_COMCERTO_530)
#include "comcerto_530.h"
#elif defined(CONFIG_COMCERTO_515)
#include "comcerto_515.h"
#elif defined(CONFIG_COMCERTO_800)
#include "comcerto_800.h"
#elif defined(CONFIG_COMCERTO_900)
#include "comcerto_900.h"
#else
#error no architecture selected!!!
#endif


#define CSE_BOOT	4
#endif
