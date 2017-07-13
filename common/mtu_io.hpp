#pragma once
//=====================================================================//
/*!	@file
	@brief	RX グループ MTU3 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

/// F_PCLKA は変換パラメーター計算で必要で、設定が無いとエラーにします。
#ifndef F_PCLKA
#  error "mtu_io.hpp requires F_PCLKA to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU 制御クラス
		@param[in]	MTU	MTU ユニット
		@param[in]	TASK	割り込みタスク
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class MTU, class TASK>
	class mtu_io {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  機能タイプ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class functions : uint8_t {
			PWM,	///< PWM
		};

	private:

		static TASK	task_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		mtu_io() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	func	機能選択
			@param[in]	level	割り込みレベル
		*/
		//-----------------------------------------------------------------//
		bool start(functions func, uint8_t level)
		{
			power_cfg::turn(MTU::get_peripheral());





			return true;
		}



		//-----------------------------------------------------------------//
		/*!
			@brief  TASK クラスの参照
			@return TASK クラス
		*/
		//-----------------------------------------------------------------//
		static TASK& at_task() { return task_; }
	};

	template <class MTU, class TASK> TASK mtu_io<MTU, TASK>::task_;

}

