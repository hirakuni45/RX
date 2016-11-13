#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ MTU 制御 @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/vect.h"
#include "RX24T/port_map.hpp"
#include "RX24T/power_cfg.hpp"

/// F_PCKD は変換パラメーター計算で必要で、設定が無いとエラーにします。
#ifndef F_PCKA
#  error "mtu_io.hpp requires F_PCKD to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU 制御クラス
		@param[in]	MTUx	MTUx ユニット(0 to 7, 9)
		@param[in]	TASK	割り込みタスク
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class MTUx, class TASK>
	class mtu_io {
	public:


	private:
		TASK	task_;

		uint8_t	level_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		mtu_io() : level_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	PWM1 スタート(MTU0, MTU1, MTU2, MTU3, MTU4, MTU6, MTU7, MTU9)
			@param[in]	cksrc	クロックソース
			@param[in]	level	割り込みレベル、０の場合はポーリング
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool start_pwm1(typename MTUx::clock_source cksrc, uint8_t level = 0)
		{
			level_ = level;

			MTUx::TCR.TPSC   = static_cast<uint8_t>(cksrc) & 0b111;
			MTUx::TCR2.TPSC2 = static_cast<uint8_t>(cksrc) >> 3;

			MTUx::TMDR1.MD = 0b0010;  // PWM モード１



			return true;
		}

	};
}
