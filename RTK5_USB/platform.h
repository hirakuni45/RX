#pragma once

#include <stdint.h>

#if defined(SIG_RX65N)
#define BSP_MCU_RX65N
#elif defined(SIG_RX64M)
#define BSP_MCU_RX64M
#elif defined(SIG_RX71M)
#define BSP_MCU_RX71M
#endif

// #define BSP_CFG_RTOS_USED 1

#ifndef __cplusplus
#define bool _Bool
#define false 0
#define true 1
#endif

#define __evenaccess

#include "r_usb/iodefine.h"



