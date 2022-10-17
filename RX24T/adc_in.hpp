#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ A/D 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"
#include "common/vect.h"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  A/D 制御クラス
		@param[in]	ADCU	A/D チャネル・ユニット
		@param[in]	TASK	割り込みタスク
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ADCU, class TASK>
	class adc_in {
	public:

		typedef ADCU value_type;

		//-----------------------------------------------------------------//
		/*!
			@brief	変換モード
		 */
		//-----------------------------------------------------------------//
		enum class cnv_type : uint8_t {
			
		};


	private:
		static TASK task_;

		static INTERRUPT_FUNC void adi_task_()
		{
			task_();
		}

		uint8_t	level_;

		static inline void sleep_() { asm("nop"); }

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		adc_in() : level_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	スタート
			@param[in]	ana		アナログ入力
			@param[in]	level	割り込みレベル、０の場合はポーリング
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool start(typename ADCU::ANALOG ana, uint8_t level = 0)
		{
			level_ = level;

			// 基本変換時間（１マイクロ秒）＋マージン
			uint32_t n = clock_profile::PCLKD / 1000000 + 10;
			if(n > 255) return false;

			power_mgr::turn(ADCU::PERIPHERAL);
			ADCU::enable(ana);
			ADCU::ADANSA.set(ana);
			ADCU::ADSSTR.set(ana, n);

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	スキャン開始
		 */
		//-----------------------------------------------------------------//
		void scan() {
			if(level_ > 0) {
				icu_mgr::set_task(ADCU::S12ADI, adi_task_);
				icu_mgr::set_level(ADCU::S12ADI, level_);
				ADCU::ADCSR = ADCU::ADCSR.ADST.b() | ADCU::ADCSR.ADIE.b();
			} else {
				ADCU::ADCSR = ADCU::ADCSR.ADST.b();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	変換状態の取得
			@return 変換中なら「true」
		 */
		//-----------------------------------------------------------------//
		bool get_state() const {
			return ADCU::ADCSR.ADST();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	読み込み同期
		 */
		//-----------------------------------------------------------------//
		void sync() const {
			while(ADCU::ADCSR.ADST() != 0) sleep_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換結果を取得
			@param[in]	an	変換チャネル
			@return 変換結果（上位１０ビットが有効な値）
		 */
		//-----------------------------------------------------------------//
		uint16_t get(typename ADCU::ANALOG an) const {
			return ADCU::ADDR(an);
		}
	};

	template <class ADCU, class TASK> TASK adc_in<ADCU, TASK>::task_;
}
