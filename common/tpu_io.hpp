#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M/RX65[1N]/RX72[MN] TPU 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/intr_utils.hpp"
#include "common/vect.h"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  TPU 制御ベース・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class tpu_io_base {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマー・タイプ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class TYPE : uint8_t {
			NONE,		///< 無し
			MATCH_A,	///< TGRA コンペアマッチ（TPU0, TPU1, TPU2, TPU3, TPU4, TPU5）
			MATCH_B,	///< TGRB コンペアマッチ（TPU0, TPU1, TPU2, TPU3, TPU4, TPU5）
			MATCH_C,	///< TGRC コンペアマッチ（TPU0, TPU3）
			MATCH_D,	///< TGRD コンペアマッチ（TPU0, TPU3）
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入力タイプ（インプットキャプチャ）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class INPUT : uint8_t {
			NEG  = 0b00,	///< 立ち下がりエッジでカウント
			POS  = 0b01,	///< 立ち上がりエッジでカウント
			BOTH = 0b10,	///< 両エッジでカウント
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  TPU 制御クラス
		@param[in]	TPU		TPU チャネル・クラス
		@param[in]	TASK	タイマー動作ファンクタ・クラス
		@param[in]	ORDER	ポート・マップ候補型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class TPU, class TASK = utils::null_task, port_map_order::ORDER ORDER = port_map_order::ORDER::FIRST>
	class tpu_io : public tpu_io_base {

		TYPE		type_;
		uint8_t		level_;
		uint8_t		shift_;
		uint32_t	rate_;

		ICU::VECTOR	intr_vec_;

		static TASK	task_;

		static INTERRUPT_FUNC void tpu_task_() noexcept {
//		static void tpu_task_() noexcept {
//			asm("save #0");
			task_();
//			asm("rstr #0");
//			asm("rte");
		}

		void sleep_() const noexcept { asm("nop"); }

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		tpu_io() noexcept : type_(TYPE::NONE), level_(0), shift_(0), rate_(0),
			intr_vec_(ICU::VECTOR::NONE)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  コンペアマッチ動作開始
			@param[in]	type	タイマータイプ型
			@param[in]	freq	タイマー周波数
			@param[in]	level	割り込みレベル（０ならポーリング）
			@param[in]	out		出力タイプ
			@return レンジオーバーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool start(TYPE type, uint32_t freq, uint8_t level, OUTPUT out = OUTPUT::NONE) noexcept
		{
			if(freq == 0) return false;

			// TPU0, TPU3 以外は、MATCH_C, MATCH_D が無いのでエラーとする。
			if(type == TYPE::MATCH_C || type == TYPE::MATCH_D) {
				switch(TPU::PERIPHERAL) {
				case peripheral::TPU0: break;
				case peripheral::TPU3: break;
				default:
					return false;
				}
			}

			type_ = type;
			rate_ = freq;
			level_ = level;

			uint32_t cmt = device::clock_profile::PCLKB / freq;
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

			if(!power_mgr::turn(per)) {
				return false;
			}

			bool ret = true;
			TPU::TSTR = 0;	// 再設定の時に止める～
			TPU::TIER = 0;
			TPU::TMDR = 0;  // 通常モード、通常動作

			switch(type) {
			case TYPE::MATCH_A:  // TGRA のコンペアマッチ
				TPU::TCR = TPU::TCR.CCLR.b(0b001) | TPU::TCR.TPSC.b(tpsc);
				TPU::TGRA = cmt - 1;
				TPU::TIORH.IOA = static_cast<uint8_t>(out);
				break;
			case TYPE::MATCH_B:  // TGRB のコンペアマッチ
				TPU::TCR = TPU::TCR.CCLR.b(0b010) | TPU::TCR.TPSC.b(tpsc);
				TPU::TGRB = cmt - 1;
				TPU::TIORH.IOB = static_cast<uint8_t>(out);
				break;
			case TYPE::MATCH_C:  // TGRC のコンペアマッチ
				TPU::TCR = TPU::TCR.CCLR.b(0b101) | TPU::TCR.TPSC.b(tpsc);
				TPU::TGRC = cmt - 1;
				TPU::TIORL.IOC = static_cast<uint8_t>(out);
				break;
			case TYPE::MATCH_D:  // TGRD のコンペアマッチ
				TPU::TCR = TPU::TCR.CCLR.b(0b110) | TPU::TCR.TPSC.b(tpsc);
				TPU::TGRD = cmt - 1;
				TPU::TIORL.IOD = static_cast<uint8_t>(out);
				break;
			default:
				ret = false;
				break;
			}
			TPU::TCNT = 0x0000;

			if(level_ > 0) {  // 割り込み設定
				intr_vec_ = icu_mgr::set_interrupt(TPU::RA_INN, tpu_task_, level_);
				switch(type) {
				case TYPE::MATCH_A:
					TPU::TIER.TGIEA = 1;
					break;
				case TYPE::MATCH_B:
					TPU::TIER.TGIEB = 1;
					break;
				case TYPE::MATCH_C:
					TPU::TIER.TGIEC = 1;
					break;
				case TYPE::MATCH_D:
					TPU::TIER.TGIED = 1;
					break;
				default:
					break;
				}
			} else {
				TPU::TIER.TGIEA = 0;
				TPU::TIER.TGIEB = 0;
			}

			// 出力設定
			switch(type) {
			case TYPE::NONE:  // 出力無し
				break;
			case TYPE::MATCH_A:
				ret = port_map_tpu::turn(per, port_map_tpu::channel::A, true, ORDER);
				break;
			case TYPE::MATCH_B:
				ret = port_map_tpu::turn(per, port_map_tpu::channel::B, true, ORDER);
				break;
			case TYPE::MATCH_C:
				ret = port_map_tpu::turn(per, port_map_tpu::channel::C, true, ORDER);
				break;
			case TYPE::MATCH_D:
				ret = port_map_tpu::turn(per, port_map_tpu::channel::D, true, ORDER);
				break;
			default:
				ret = false;
				break;
			}

			TPU::enable();

			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コンペアマッチＡ（MATCH_A, 出力を行わない）（レガシー）
			@param[in]	freq	タイマー周波数
			@param[in]	level	割り込みレベル（０ならポーリング）
			@return レンジオーバーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t freq, uint8_t level) noexcept
		{
			return start(TYPE::MATCH_A, freq, level);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  インプットキャプチャー動作開始
			@param[in]	type	タイマータイプ型
			@param[in]	level	割り込みレベル（０ならポーリング）
			@param[in]	inp		入力タイプ
			@return レンジオーバーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool start(TYPE type, uint8_t level, INPUT inp) noexcept
		{

			return false;
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
				uint32_t rate = (device::clock_profile::PCLKB >> shift_) / (cmn + 1);
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

	template <class TPU, class TASK, port_map_order::ORDER PMAP> TASK tpu_io<TPU, TASK, PMAP>::task_;
}
