#pragma once
//=====================================================================//
/*!	@file
	@brief	PHY ベース・クラス @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  PHY リンク・ステート
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class phy_link_state {
		NO_LINK = 0,	///< リンク無し
		LINK_10H,		///< 10MBPS / Half
		LINK_10F,		///< 10MBPS / Full
		LINK_100H,		///< 100MBPS / Half
		LINK_100F,		///< 100MBPS / Full
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  EUI-48/EUI-64 テンプレートクラス
		@param[in]	SPI	SPI クラス
		@param[in]	CS	チップ・セレクト
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SPI, class CS>
	class phy_base {


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  PHY 初期化
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool init(void)
		{

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  PHY 自動速度調整
		*/
		//-----------------------------------------------------------------//
		void start_autonegotiate()
		{
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  PHY 自動速度調整結果取得
			@param[out]	line_speed_duplex	both the line speed and the duplex
			@param[out]	local_pause			store the local pause bits
			@param[out]	partner_pause		store the partner pause bits
			@return		正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool get_autonegotiate(uint16_t* line_speed_duplex, uint16_t* local_pause, uint16_t* partner_pause)
		{

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  PHY リンクステータス取得
			@return -1 if links is down, 0 otherwise 
		*/
		//-----------------------------------------------------------------//
		bool get_link_status()
		{

			return true;
		}
	};
}
