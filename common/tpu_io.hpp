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

#include "common/format.hpp"

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

		uint8_t		level_;

		static TASK	task_;

		static volatile uint32_t counter_;

		static INTERRUPT_FUNC void tpu_task_() {
			++counter_;
			task_();
		}

		void sleep_() const { asm("nop"); }

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		tpu_io() : level_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  動作開始					
			@param[in]	freq	タイマー周波数
			@param[in]	level	割り込みレベル（０ならポーリング）
			@return レンジオーバーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t freq, uint8_t level = 0)
		{
			if(freq == 0) return false;

			level_ = level;

			uint32_t cmt = F_PCLKB / freq;

			uint8_t cks = 0;
			while(cmt > 65536) {
				cmt >>= 1;
				++cks;
			}

			// プリスケーラーの算出 cks
			// 1: 1/2, 2: 1/4, 3: 1/8, ...
			// TPU0: 1/1(0), 1/4(2), 1/16(4), 1/64(6) 
			uint8_t prs = 0;
			switch(cks) {
			case 1:
				cmt >>= 1;
			case 2:
				prs = 1;
				break;
			case 3:
				cmt >>= 1;
			case 4:
				prs = 2;
				break;
			case 5:
				cmt >>= 1;
			case 6:
				prs = 3;
				break;
			default:
				return false;
				break;
			}

			power_cfg::turn(TPU::get_peripheral());

			TPU::TCR = TPU::TCR.CCLR.b(1) | TPU::TCR.TPSC.b(prs);  // TGRA のコンペアマッチ
			if(cmt > 0) cmt--;
			TPU::TGRA = cmt;
			TPU::TCNT = 0x0000;

			if(level_ > 0) {  // 割り込み設定
				bool ena = level_ != 0 ? true : false;

				set_interrupt_task(tpu_task_, static_cast<uint32_t>(ICU::VECTOR::INTB128));
				ICU::SLIBXR128 = TPU::get_TGIA();
				ICU::IPR.INTB128 = level_;
				ICU::IER.INTB128 = ena;

				TPU::TIER.TGIEA = 1;  // TGRA interrupt
			} else {
				TPU::TIER.TGIEA = 0;
			}

			TPU::enable();

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマー同期
		*/
		//-----------------------------------------------------------------//
		void sync() const
		{
			if(level_ > 0) {
				volatile uint32_t cnt = counter_;
				while(cnt == counter_) sleep_();
			} else {
				while(TPU::TSR.TGFA() == 0) sleep_();
				TPU::TSR.TGFA = 0;
				task_();
				++counter_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みカウンターの値を取得
			@return 割り込みカウンターの値
		*/
		//-----------------------------------------------------------------//
		uint32_t get_counter() const { return counter_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  TASK クラスの参照
			@return TASK クラス
		*/
		//-----------------------------------------------------------------//
		static TASK& at_task() { return task_; }
	};

	template <class TPU, class TASK> volatile uint32_t tpu_io<TPU, TASK>::counter_ = 0;
	template <class TPU, class TASK> TASK tpu_io<TPU, TASK>::task_;

}
