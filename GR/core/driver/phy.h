#pragma once
//=====================================================================//
/*!	@file
	@brief	PHY 制御 @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <stdint.h>

/* PHY return definitions */
#define R_PHY_OK        (0)
#define R_PHY_ERROR     (-1)

#if 0
#define MICREL_KSZ8041NL  /* Please define the macro when you use KSZ8041NL of the Micrel, Inc. */
#endif

enum LinkStatE
{
    PHY_NO_LINK = 0,
    PHY_LINK_10H,
    PHY_LINK_10F,
    PHY_LINK_100H,
    PHY_LINK_100F,
};

typedef enum LinkStatE linkstat_e;


int16_t phy_init(void);
void phy_start_autonegotiate(void);
int16_t phy_set_autonegotiate(uint16_t *line_speed_duplex, uint16_t *local_pause, uint16_t *partner_pause);
int16_t phy_get_link_status(void);
