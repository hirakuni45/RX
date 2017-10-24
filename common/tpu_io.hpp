#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・TPU I/O 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/intr_utils.hpp"
#include "common/vect.h"

/// F_PCLKB は周期パラメーター計算で必要で、設定が無いとエラーにします。
#ifndef F_PCLKB
#  error "tpu_io.hpp requires F_PCLKB to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  TPU I/O クラス
		@param[in]	TPU	チャネルクラス
		@param[in]	TASK	タイマー動作クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class TPU, class TASK = utils::null_task>
	class tpu_io {


		static TASK	task_;

		static volatile uint32_t counter_;

		static INTERRUPT_FUNC void tpu_task_() {
			++counter_;
			task_();
		}

		void set_vector_(ICU::VECTOR vec) {
			set_interrupt_task(tpu_task_, static_cast<uint32_t>(vec));
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		tpu_io() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	freq	タイマー周波数
			@param[in]	level	割り込みレベル（０ならポーリング）
			@return レンジオーバーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t freq, uint8_t level = 0)
		{
			if(freq == 0) return false;

			uint32_t cmcor = F_PCLKB;

			uint8_t cks = 0;
			while(cmcor > 65536) {
				cmcor >>= 1;
				++cks;
			}
			if(cks > 3) {
				return false;
			}

			power_cfg::turn(TPU::get_peripheral());





			return true;
		}

	};

	template <class TPU, class TASK> volatile uint32_t tpu_io<TPU, TASK>::counter_ = 0;
	template <class TPU, class TASK> TASK tpu_io<TPU, TASK>::task_;

}
