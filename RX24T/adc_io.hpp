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

		port_map::analog	org_;
		port_map::analog	end_;
		uint8_t	level_;

		static volatile uint16_t value_[ADCU::analog_num_];

		static inline void sleep_() { asm("nop"); }

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		adc_io() : org_(ADCU::analog_org_), end_(ADCU::analog_end_), level_(0) {
			for(uint32_t i = 0; i < ADCU::analog_num_; ++i) value_[i] = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	スタート
			@param[in]	org		変換開始アナログ入力
			@param[in]	end		変換終了アナログ入力
			@param[in]	level	割り込みレベル、０の場合はポーリング
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool start(port_map::analog org, port_map::analog end, uint8_t level = 0)
		{
			if(ADCU::analog_org_ <= org && org <= ADCU::analog_end_) ;
			else if(ADCU::analog_org_ <= end && end <= ADCU::analog_end_) ;
			else {
				return false;
			}
			org_ = org;
			end_ = end;
			level_ = level;

			for(auto i = org; i <= end; i = static_cast<port_map::analog>(static_cast<uint32_t>(i) + 1)) {
				port_map::turn(i);
			}
			power_cfg::turn(ADCU::get_peripheral());



			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	読み込み同期（ポーリングの場合は無視される）
		 */
		//-----------------------------------------------------------------//
		void sync() const {
			if(level_ == 0) return;
///			while(ADS() < NUM) sleep_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換結果を取得
			@param[in]	ch	変換チャネル
			@return 変換結果（上位１０ビットが有効な値）
		 */
		//-----------------------------------------------------------------//
		uint16_t get(port_map::analog ch)
		{
			if(ADCU::analog_org_ <= ch && ch <= ADCU::analog_end_) {
				uint32_t idx = static_cast<uint32_t>(ch) - static_cast<uint32_t>(ADCU::analog_org_);
				if(level_) {
					return value_[idx];
				} else {
					ADCU::select_analog_a(ch);
					ADCU::ADCSR = ADCU::ADCSR.ADST.b();
					while(ADCU::ADCSR.ADST() != 0) sleep_();
					return ADCU::get_data(ch);
				}
			}
			return 0;
		}
	};

	template<class ADCU, class TASK>
	volatile uint16_t adc_io<ADCU, TASK>::value_[ADCU::analog_num_]; 
}
