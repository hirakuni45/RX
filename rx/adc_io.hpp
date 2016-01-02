#pragma once
//=====================================================================//
/*!	@file
	@brief	RX グループ・A/D I/O 制御 @n
			Copyright 2013 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "rx63x/s12ad.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  A/D I/O 制御クラス
		@param[in]	ADC	ADCx定義クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ADC>
	class adc_io {

		void sleep_() const { }
	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		adc_io() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  機能を開始
			@param[in]	bits	変換チャネルフラグ
		*/
		//-----------------------------------------------------------------//
		void start(uint8_t bits) const {
			S12AD::ADANSA = bits;

			// GPT による変換開始
			S12AD::ADCSR = S12AD::ADCSR.TRGE.b() | S12AD::ADCSR.EXTRG.b();
			S12AD::ADSTRGR.TRSA = 0b10001;	// GPT0 要因

			S12AD::ADCSR.ADST = 1;	// 変換開始
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  変換終了か検査
			@return 変換終了なら「true」
		*/
		//-----------------------------------------------------------------//
		bool state_end() const { return !S12AD::ADCSR.ADST(); }


		//-----------------------------------------------------------------//
		/*!
			@brief  変換終了を待つ
		*/
		//-----------------------------------------------------------------//
		void sync() const {
			while(S12AD::ADCSR.ADST() == true) sleep_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  変換結果を取得
		*/
		//-----------------------------------------------------------------//
		uint16_t get(uint8_t chanel) const {
			switch(chanel) {
			case 0:
				return S12AD::ADDR0();
			case 1:
				return S12AD::ADDR1();
			case 2:
				return S12AD::ADDR2();
			case 3:
				return S12AD::ADDR3();
			case 4:
				return S12AD::ADDR4();
			case 5:
				return S12AD::ADDR5();
			case 6:
				return S12AD::ADDR6();
			case 7:
				return S12AD::ADDR7();
			default:
				return 0;
			}
		}
	};
}

