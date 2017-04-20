#pragma once
//=====================================================================//
/*!	@file
	@brief	NTC サーミスタ 温度計算 クラス @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cmath>

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  サーミスタ型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class thermistor {
		NT103,	///< THB:4126, TR25:10K
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  NTCTH テンプレートクラス
		@param[in]	ADNUM	A/D 変換値の量子化最大値
		@param[in]	THM		サーミスタの型
		@param[in]	REFR	分圧抵抗値
		@param[in]	thup	サーミスタが VCC 側の場合「true」、GND 側の場合「false」
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint16_t ADNUM, thermistor THM, uint16_t REFR, bool thup>
	class NTCTH {

		// サーミスタの型に応じたパラメーター
		// THB:  B 定数
		// TR25: ２５度における基準抵抗値
		static void get_para_(float& THB, float& TR25)
		{
			switch(THM) {
			case thermistor::NT103:
				THB  = 4126.0f;  ///< サーミスタＢ定数
				TR25 = 10e3;     ///< R25 サーミスタ２５℃基準抵抗値
				break;
			default:
				break;
			}
		}

		// サーミスターが VCC 側
		static float thermistor_upper_(uint16_t raw)
		{
			float thr = (static_cast<float>(REFR * ADNUM) / static_cast<float>(raw)) - static_cast<float>(REFR);
			return thr;
		}

		// サーミスターが GND 側
		static float thermistor_lower_(uint16_t raw)
		{
			float thr = static_cast<float>(REFR * raw) / static_cast<float>(ADNUM - raw);
			return thr;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	() オペレーター
			@param[in]	adn		A/D 変換値
		 */
		//-----------------------------------------------------------------//
		float operator () (uint16_t adn) const
		{
			float thr;
			if(thup) {
				thr = thermistor_upper_(adn);
			} else {
				thr = thermistor_lower_(adn);
			}
			float THB;
			float TR25;
			get_para_(THB, TR25);
			static const float T0   = 298.15f;   ///< 絶対温度
			float t = 1.0f / (std::log(thr / TR25) / THB + (1.0f / T0));
			return t - 273.15f;
		}
	};
}
