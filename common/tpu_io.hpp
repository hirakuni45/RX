#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・TPU I/O 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2019 Kunihito Hiramatsu @n
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
		@param[in]	TASK	タイマー動作ファンクタ・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class TPU, class TASK = utils::null_task>
	class tpu_io {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイプ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class TYPE : uint8_t {
			MATCH,	///< コンペアー・マッチ
		};

	private:
		uint8_t		level_;

		ICU::VECTOR	intr_vec_;

		static volatile uint32_t counter_;

		static TASK	task_;

		static INTERRUPT_FUNC void tpu_task_() noexcept {
///			if(TPU::TSR.TGFA()) TPU::TSR.TGFA = 0;
			++counter_;
			task_();
		}

		void sleep_() const noexcept { asm("nop"); }

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		tpu_io() noexcept : level_(0), intr_vec_(ICU::VECTOR::NONE) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマー動作開始
			@param[in]	freq	タイマー周波数
			@param[in]	level	割り込みレベル（０ならポーリング）
			@return レンジオーバーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t freq, uint8_t level = 0) noexcept
		{
			if(freq == 0) return false;

			level_ = level;

			uint32_t cmt = F_PCLKB / freq;
			uint8_t shift = 0;
			while(cmt > 65536) {
				cmt >>= 2;
				++shift;
			}
			if(cmt == 0) return false;

			auto per = TPU::PERIPHERAL;

			// プリスケーラーの算出と指定 (shift)
			// 1: 1/2, 2: 1/4, 3: 1/8, ...
			// TPU0: 1/1(0), 1/4(1), 1/16(2), 1/64(3) 
			// TPU1: 1/1(0), 1/4(1), 1/16(2), 1/64(3), 1/256(4)
 			// TPU2: 1/1(0), 1/4(1), 1/16(2), 1/64(3), 1/1024(5)
 			// TPU3: 1/1(0), 1/4(1), 1/16(2), 1/64(3), 1/256(4), 1/1024(5), 1/4096(6)
			// TPU4: 1/1(0), 1/4(1), 1/16(2), 1/64(3), 1/1024(5)
			// TPU5: 1/1(0), 1/4(1), 1/16(2), 1/64(3), 1/256(4)
			uint8_t tpsc = 0;
			if(shift == 0) {
			} else if(shift == 1) {
				tpsc = 0b001;
			} else if(shift == 2) {
				tpsc = 0b010;
			} else if(shift == 3) {
				tpsc = 0b011;
			} else if(shift == 6) {
				if(per == peripheral::TPU3) {  // 1/4096
					tpsc = 0b111;
				} else {
					return false;
				}
			} else if(shift == 5) {
				if(per == peripheral::TPU2) {
					tpsc = 0b111;
				} else if(per == peripheral::TPU3) {
					tpsc = 0b101;
				} else if(per == peripheral::TPU4) {
					tpsc = 0b110;
				} else {
					return false;
				}
			} else if(shift == 4) {
				if(per == peripheral::TPU1 || per == peripheral::TPU3 || per == peripheral::TPU5) {
					tpsc = 0b110;
				} else {
					return false;
				}
			} else {
				return false;
			}

			power_mgr::turn(per);

			TPU::TCR = TPU::TCR.CCLR.b(1) | TPU::TCR.TPSC.b(tpsc);  // TGRA のコンペアマッチ
			TPU::TGRA = cmt - 1;
			TPU::TCNT = 0x0000;

			if(level_ > 0) {  // 割り込み設定
#if (defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N))
				intr_vec_ = ICU::VECTOR::INTB128;
				icu_mgr::set_task(intr_vec_, tpu_task_);
				ICU::SLIBXR128 = TPU::RA_INN;
				ICU::IPR.INTB128 = level_;
				ICU::IER.INTB128 = true;
#endif
				TPU::TIER.TGIEA = 1;  // TGRA interrupt
			} else {
				TPU::TIER.TGIEA = 0;
			}

			TPU::enable();

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  廃棄
		*/
		//-----------------------------------------------------------------//
		void destroy() noexcept
		{
			TPU::TIER = 0;
			TPU::enable(false);
			power_mgr::turn(TPU::PERIPHERAL, false);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマー同期
		*/
		//-----------------------------------------------------------------//
		void sync() const noexcept
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
		uint32_t get_counter() const noexcept { return counter_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  TCNT レジスターの値を取得
			@return TCNT レジスター
		*/
		//-----------------------------------------------------------------//
		uint16_t get_tcnt_count() const noexcept { return TPU::TCNT(); }


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターの取得
			@return 割り込みベクター
		*/
		//-----------------------------------------------------------------//
		ICU::VECTOR get_intr_vec() const noexcept { return intr_vec_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  TASK クラスの参照
			@return TASK クラス
		*/
		//-----------------------------------------------------------------//
		static TASK& at_task() noexcept { return task_; }
	};

	template <class TPU, class TASK> volatile uint32_t tpu_io<TPU, TASK>::counter_ = 0;
	template <class TPU, class TASK> TASK tpu_io<TPU, TASK>::task_;
}
