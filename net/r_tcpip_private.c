//=====================================================================//
/*! @file
    @brief  r_tcpip_private.c @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <stdint.h>
#include "r_t4_itcpip.h"
#include "r_tcpip_private.h"

extern uint16_t get_tcpudp_time(void);

void get_random_number(uint8_t *data, uint16_t len)
{
    static uint32_t y = 2463534242;
    uint32_t res;
    uint32_t lp;
    uint8_t *bPtr;

    y += get_tcpudp_time();
    res = len / 4;
    for (lp = 0; lp < res; lp++)
    {
        y = y ^ (y << 13);
        y = y ^ (y >> 17);
        y = y ^ (y << 5);
        bPtr = (uint8_t*) & y;
#ifdef LITTLE_ENDIAN
        *((uint32_t *)data) = (*(bPtr + 3) << 24) | (*(bPtr + 2) << 16) | (*(bPtr + 1) << 8) | *(bPtr + 0);
#else
        *((uint32_t *)data) = y;
#endif
        data += 4;
    }
    y = y ^ (y << 13);
    y = y ^ (y >> 17);
    y = y ^ (y << 5);
    res = (uint32_t)len % 4;
    bPtr = (uint8_t*) & y;
    switch (res)
    {
        case 3:
#ifdef LITTLE_ENDIAN
            *data++ = bPtr[3];
            *data++ = bPtr[2];
            *data++ = bPtr[1];
#else
            *data++ = bPtr[0];
            *data++ = bPtr[1];
            *data++ = bPtr[2];
#endif
            break;

        case 2:
#ifdef LITTLE_ENDIAN
            *data++ = bPtr[3];
            *data++ = bPtr[2];
#else
            *data++ = bPtr[0];
            *data++ = bPtr[1];
#endif
            break;

        case 1:
#ifdef LITTLE_ENDIAN
            *data++ = bPtr[3];
#else
            *data++ = bPtr[0];
#endif
            break;

        default:
            /* no op */
            break;
    }
}
