#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M/RX65[1N]/RX72[MN] グループ・TPU 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2020 Kunihito Hiramatsu @n
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
		@brief  TPU 制御クラス
		@param[in]	TPU	チャネルクラス
		@param[in]	TASK	タイマー動作ファンクタ・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class TPU, class TASK = utils::null_task>
	class tpu_io {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマー・タイプ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class TYPE : uint8_t {
			MATCH_A,	///< TGRA コンペアマッチ
			MATCH_B,	///< TGRB コンペアマッチ
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  出力タイプ（コンペアマッチ）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OUTPUT : uint8_t {
			NONE  = 0b0000,		///< 出力しない
			IL_ML = 0b0001,		///< 初期出力はLow出力、コンペアマッチでLow出力
			IL_MH = 0b0010,		///< 初期出力はLow出力、コンペアマッチでHigh出力
			IL_MT = 0b0011,		///< 初期出力はLow出力、コンペアマッチでトグル出力
			IH_ML = 0b0101,		///< 初期出力はHigh出力、コンペアマッチでLow出力
			IH_MH = 0b0110,		///< 初期出力はHigh出力、コンペアマッチでHigh出力
			IH_MT = 0b0111		///< 初期出力はHigh出力、コンペアマッチでトグル出力
		};


	private:
		TYPE		type_;
		uint8_t		level_;
		uint8_t		shift_;
		uint32_t	rate_;

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
		tpu_io() noexcept : type_(TYPE::MATCH_A), level_(0), shift_(0), rate_(0),
			intr_vec_(ICU::VECTOR::NONE)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマー動作開始
			@param[in]	type	タイプ
			@param[in]	freq	タイマー周波数
			@param[in]	level	割り込みレベル（０ならポーリング）
			@param[in]	out		出力タイプ
			@return レンジオーバーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool start(TYPE type, uint32_t freq, uint8_t level, OUTPUT out = OUTPUT::NONE) noexcept
		{
			if(freq == 0) return false;

			type_ = type;
			rate_ = freq;
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
			shift_ = shift * 2;

			bool ret = true;
			power_mgr::turn(per);

			TPU::TMDR = 0;  // 通常モード、通常動作

			switch(type) {
			case TYPE::MATCH_A:  // TGRA のコンペアマッチ
				TPU::TCR = TPU::TCR.CCLR.b(0b001) | TPU::TCR.TPSC.b(tpsc);
				TPU::TGRA = cmt - 1;
				// ※本来「TIORH」は TPU0、TPU3 のレジスタとなっているが、現在の実装では、TPU 共通
				TPU::TIORH.IOA = static_cast<uint8_t>(out);
				break;
			case TYPE::MATCH_B:  // TGRB のコンペアマッチ
				TPU::TCR = TPU::TCR.CCLR.b(0b010) | TPU::TCR.TPSC.b(tpsc);
				TPU::TGRB = cmt - 1;
				// ※本来「TIORH」は TPU0、TPU3 のレジスタとなっているが、現在の実装では、TPU 共通
				TPU::TIORH.IOB = static_cast<uint8_t>(out);
				break;
			default:
				ret = false;
				break;
			}
			TPU::TCNT = 0x0000;

			if(level_ > 0) {  // 割り込み設定
				if(intr_vec_ == ICU::VECTOR::NONE) {
					intr_vec_ = icu_mgr::set_interrupt(TPU::RA_INN, tpu_task_, level_);
				}
				switch(type) {
				case TYPE::MATCH_A:
					TPU::TIER.TGIEA = 1;  // TGRA interrupt
					break;
				case TYPE::MATCH_B:
					TPU::TIER.TGIEB = 1;  // TGRB interrupt
					break;
				default:
					break;
				}
			} else {
				TPU::TIER.TGIEA = 0;
				TPU::TIER.TGIEB = 0;
			}

			TPU::enable();

			if(out != OUTPUT::NONE) {
				switch(type) {
				case TYPE::MATCH_A:  // TGRA のコンペアマッチ
					if(!port_map::turn(per, port_map::channel::A)) {
						ret = false;
					}
					break;
				case TYPE::MATCH_B:  // TGRB のコンペアマッチ
					if(!port_map::turn(per, port_map::channel::B)) {
						ret = false;
					}
					break;
				default:
					ret = false;
					break;
				}
			}

			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コンペアマッチＡ（出力を行わない）（レガシー）
			@param[in]	freq	タイマー周波数
			@param[in]	level	割り込みレベル（０ならポーリング）
			@return レンジオーバーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t freq, uint8_t level) noexcept
		{
			return start(TYPE::MATCH_A, freq, level, OUTPUT::NONE);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  廃棄
		*/
		//-----------------------------------------------------------------//
		void destroy() noexcept
		{
			icu_mgr::set_interrupt(TPU::RA_INN, nullptr, 0);
			intr_vec_ = 0;
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
				switch(type_) {
				case TYPE::MATCH_A:
					while(TPU::TSR.TGFA() == 0) sleep_();
					TPU::TSR.TGFA = 0;
					break;
				case TYPE::MATCH_B:
					while(TPU::TSR.TGFB() == 0) sleep_();
					TPU::TSR.TGFB = 0;
					break;
				}
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
			@brief	周期を取得
			@param[in]	real	「true」にした場合、内部で計算されたリアルな値
			@return 周期
		 */
		//-----------------------------------------------------------------//
		uint32_t get_rate(bool real = false) const noexcept
		{
			if(real) {
				uint32_t cmn = 0;
				switch(type_) {
				case TYPE::MATCH_A:
					cmn = TPU::TGRA();
					break;
				case TYPE::MATCH_B:
					cmn = TPU::TGRB();
					break;
				default:
					break;
				}
				uint32_t rate = (static_cast<uint32_t>(F_PCLKB) >> shift_) / (cmn + 1);
				return rate;
			} else {
				return rate_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  TASK クラスの参照
			@return TASK クラス
		*/
		//-----------------------------------------------------------------//
		static const TASK& get_task() noexcept { return task_; }


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
