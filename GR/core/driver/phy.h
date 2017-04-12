#pragma once
//=====================================================================//
/*!	@file
	@brief	PHY 制御 @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <stdint.h>

#if 0
#define MICREL_KSZ8041NL  /* Please define the macro when you use KSZ8041NL of the Micrel, Inc. */
#endif

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
/*!
	@brief  PHY ステート
*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
#define R_PHY_OK        (0)
#define R_PHY_ERROR     (-1)


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
/*!
	@brief  リンク・ステート
*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
enum LinkStatE
{
    PHY_NO_LINK = 0,
    PHY_LINK_10H,
    PHY_LINK_10F,
    PHY_LINK_100H,
    PHY_LINK_100F,
};
typedef enum LinkStatE linkstat_e;

//-----------------------------------------------------------------//
/*!
	@brief  PHY 初期化
	@return R_PHY_ERROR, R_PHY_OK
*/
//-----------------------------------------------------------------//
int16_t phy_init(void);


//-----------------------------------------------------------------//
/*!
	@brief  PHY 自動速度調整
*/
//-----------------------------------------------------------------//
void phy_start_autonegotiate(void);


//-----------------------------------------------------------------//
/*!
	@brief  PHY 速度調整取得
	@param[in]	line_speed_duplex	both the line speed and the duplex
	@param[in]	local_pause			store the local pause bits
	@param[in]	partner_pause		store the partner pause bits
	@return		R_PHY_ERROR, R_PHY_OK
*/
//-----------------------------------------------------------------//
int16_t phy_get_autonegotiate(uint16_t *line_speed_duplex, uint16_t *local_pause, uint16_t *partner_pause);


//-----------------------------------------------------------------//
/*!
	@brief  PHY リンクステータス取得
	@return -1 if links is down, 0 otherwise 
*/
//-----------------------------------------------------------------//
int16_t phy_get_link_status(void);
