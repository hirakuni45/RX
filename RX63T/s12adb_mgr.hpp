#pragma once
//=========================================================================//
/*!	@file
	@brief	RX63T S12ADB (A/D) マネージャークラス @n
			ピン数により、「A/D コンバーター定義クラス」が異なる。 @n
			A/D 変換の機能が異なり、能力に違いがある。 @n
			144/120/112/100 ピン版： S12ADB0(4 CH), S12ADB1(4 CH) @n
			64/48 ピン版： S12ADB(8 CH)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX63T/s12adb.hpp"
#include "common/adc_base.hpp"
#include "common/intr_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  A/D 変換マネージャークラス
		@param[in]	ADC		A/D コンバーター定義クラス
		@param[in]	TASK	割り込みタスク
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ADC, class TASK = utils::null_task>
	struct s12adb_mgr : public adc_base {

		typedef typename ADC::ANALOG ANALOG;
		typedef channels_t<ANALOG> CHANNELS;

	private:
		static TASK		task_;

		CHANNELS	channels_;

		static INTERRUPT_FUNC void intr_task_() noexcept
		{
			task_();
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		s12adb_mgr() noexcept :
			channels_()
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換設定開始
			@param[in]	cht		有効チャネル
			@param[in]	intr	割り込みレベル
			@return 正常なら[true」
		*/
		//-----------------------------------------------------------------//
		bool start(const CHANNELS& cht, uint8_t intr = 0) noexcept
		{
			if(!power_mgr::turn(ADC::PERIPHERAL)) {
				return false;
			}

			channels_ = cht;
			uint8_t num = 0;
			// 変換時間： 0.4 us(RX63T)
			// 13 ～ 255 の範囲
			uint32_t t = (ADC::PCLK << 2) / (1'000'000'000 / ADC::CONV_TIME_NS);
			t += 3;
			t >>= 2;
			if(t < 13) t = 13;
			else if(t > 255) t = 255;
			for(uint8_t i = 0; i < ADC::ANALOG_NUM; ++i) {
				auto an = static_cast<ANALOG>(i);
				if(channels_(an)) {
					ADC::enable(an);  // アナログポート有効
					ADC::ADANSA.set(an, true);  // アナログ入力選択
					ADC::ADDSSTR.set(an, t);  // 変換時間設定
					++num;
				}
			}

			if(intr > 0) {
				icu_mgr::set_interrupt(ADC::S12ADI, intr_task_, intr);
				ADC::ADCSR.ADIE = 1;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換設定（シングル）
			@param[in]	ana		アナログチャネル
			@param[in]	intr	割り込みレベル
			@return 正常なら[true」
		*/
		//-----------------------------------------------------------------//
		bool start(ANALOG ana, uint8_t intr = 0) noexcept
		{
			CHANNELS t;
			t.set(ana);
			return start(t, intr);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換開始
		*/
		//-----------------------------------------------------------------//
		void scan() noexcept
		{
			uint8_t adcs = 0b00;  // 1 cycle conversion
			ADC::ADCSR.ADCS(adcs);
			ADC::ADCSR.ADST = 1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換終了か検査
			@return 変換中なら「true」
		*/
		//-----------------------------------------------------------------//
		bool status() const noexcept
		{
			return ADC::ADCSR.ADST() != 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換終了を待つ
		*/
		//-----------------------------------------------------------------//
		void sync() const noexcept
		{
			while(status()) ;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換結果の取得
			@param[in]	an		アナログチャネル
			@return 変換結果
		*/
		//-----------------------------------------------------------------//
		uint16_t get(ANALOG an) noexcept
		{
			return ADC::ADDR(an);
		}

		uint16_t operator () (ANALOG an) const noexcept { return get(an); }
	};
}
