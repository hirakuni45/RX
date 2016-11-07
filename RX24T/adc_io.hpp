#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ A/D 制御 @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/vect.h"
#include "RX24T/port_map.hpp"
#include "RX24T/power_cfg.hpp"

/// F_PCKD は変換パラメーター計算で必要で、設定が無いとエラーにします。
#ifndef F_PCKD
#  error "adc_io.hpp requires F_PCKD to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  A/D 制御クラス
		@param[in]	ADCU	A/D チャネル・ユニット
		@param[in]	TASK	割り込みタスク
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ADCU, class TASK>
	class adc_io {
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

		uint8_t	level_;

		static inline void sleep_() { asm("nop"); }

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		adc_io() : level_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	スタート
			@param[in]	ana		アナログ入力
			@param[in]	level	割り込みレベル、０の場合はポーリング
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool start(typename ADCU::analog ana, uint8_t level = 0)
		{
			level_ = level;

			// 基本変換時間（１マイクロ秒）＋マージン
			uint32_t n = F_PCKD / 1000000 + 10;
			if(n > 255) return false;

			power_cfg::turn(ADCU::get_peripheral());
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
			if(level_) {
			}
			ADCU::ADCSR = ADCU::ADCSR.ADST.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	読み込み同期
		 */
		//-----------------------------------------------------------------//
		void sync() const {
			if(level_) {
			} else {
				while(ADCU::ADCSR.ADST() != 0) sleep_();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換結果を取得
			@param[in]	an	変換チャネル
			@return 変換結果（上位１０ビットが有効な値）
		 */
		//-----------------------------------------------------------------//
		uint16_t get(typename ADCU::analog an)
		{
			return ADCU::ADDR(an);
		}
	};

//	template<class ADCU, class TASK>
//	volatile uint16_t adc_io<ADCU, TASK>::value_[ADCU::analog_num_]; 
}
