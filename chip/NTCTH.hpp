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
		@brief  NTCTH テンプレートクラス
		@param[in]	ADNUM	A/D 変換値の量子化最大値
		@param[in]	REFR	分圧基準抵抗（10K オームなら 10.0f）
		@param[in]	THB		サーミスタ B 定数
		@param[in]	thup	サーミスタが VCC 側の場合「true」、GND 側の場合「false」
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint16_t ADNUM, bool thup>
	class NTCTH {

		// サーミスターが VCC 側
		static float thermistor_upper_(uint16_t raw)
		{
			static const float THB  = 3452.0f;   ///< サーミスタＢ定数
			static const float T0   = 298.15f;   ///< 絶対温度
			static const float TR25 = 10.0f;     ///< R25 サーミスタ２５℃基準抵抗値
			static const float REFR = 10.0f;     ///< 分圧抵抗 

			float thr = (REFR * static_cast<float>(ADNUM) * (1.0f / static_cast<float>(raw))) - REFR;
			float t = 1.0f / (std::log(thr / TR25) / THB + (1.0f / T0));
			return t - 273.15f;
		}

		// サーミスターが GND 側
		static float thermistor_lower_(uint16_t raw)
		{
			static const float THB  = 3452.0f;   ///< サーミスタＢ定数
			static const float T0   = 298.15f;   ///< 絶対温度
			static const float TR25 = 10.0f;     ///< R25 サーミスタ２５℃基準抵抗値
			static const float REFR = 10.0f;     ///< 分圧抵抗 

			float thr = REFR * static_cast<float>(raw) / static_cast<float>(ADNUM - raw);
			float t = 1.0f / (std::log(thr / TR25) / THB + (1.0f / T0));
			return t - 273.15f;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	() オペレーター
			@param[in]	adn		A/D 変換値
		 */
		//-----------------------------------------------------------------//
		float operator () (uint16_t adn) const {
			if(thup) return thermistor_upper_(adn);
			return thermistor_lower_(adn);
		}
	};
}
