#pragma once
//=====================================================================//
/*!	@file
	@brief	A/D 変換スイッチ・サポート・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ADC_SWITCH テンプレートクラス
		@param[in]	ADC_IO	ADC I/O クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ADC_IO, class SWITCH_MAN>
	class ADC_SWITCH {

		ADC_IO&		adc_;
		SWITCH_MAN&	swman_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	adc	ADC_IO クラス（参照）
			@param[in]	swman	SWITCH_MAN クラス（参照）
		 */
		//-----------------------------------------------------------------//
		ADC_SWITCH(ADC_IO& adc, SWITCH_MAN& swman) : adc_(adc), swman_(swman) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	サービス
		 */
		//-----------------------------------------------------------------//
		void service() {
			adc_.start_scan(2);  // チャネル２から開始

			adc_.sync();

			// ４つのスイッチ判定（排他的）
			auto val = adc_.get(2);
			val >>= 6;   // 0 to 1023
			val += 128;  // 閾値のオフセット（1024 / 4(SWITCH) / 2）
			val /= 256;  // デコード（1024 / 4(SWITCH）

			switch_bits tmp;
			if(val < 4) {
				tmp.set(static_cast<SWITCH>(val));
			}

			// ２つのスイッチ判定（同時押し判定）
			val = adc_.get(3);
			val >>= 6;  // 0 to 1023
			if(val < 256) {
				tmp.set(SWITCH::A);
				tmp.set(SWITCH::B);
			} else if(val < 594) {
				tmp.set(SWITCH::A);
			} else if(val < 722) {
				tmp.set(SWITCH::B);
			}

			switch_man_.service(tmp);
		}
	};
}
