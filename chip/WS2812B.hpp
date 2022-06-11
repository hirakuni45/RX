#pragma once
//=========================================================================//
/*!	@file
	@brief	WS2812B class @n
			WorldSemi @n
			Intelligent control LED integrated light source @n
			http://www.world-semi.com/Certifications/WS2812B.html
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=========================================================================//
#include <cstdint>

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  WS2812B テンプレートクラス
		@param[in]	MTU_IO	MTU/GPT I/O クラス（PWM)
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class MTU_IO>
	class WS2812B {

		MTU_IO&		mtu_io_;

		void output_(uint8_t n)
		{
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクタ
			@param[in]	mtu_io		MTU/GPT I/O クラス
		 */
		//-----------------------------------------------------------------//
		WS2812B(MTU_IO& mtu_io) noexcept : mtu_io_(mtu_io)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@return エラーがあれば「false」を返す。
		 */
		//-----------------------------------------------------------------//
		bool start() noexcept
		{
			// PWM 周期設定（800KHz）
			// mtu_io_.


			return true;
		}
	};

}
