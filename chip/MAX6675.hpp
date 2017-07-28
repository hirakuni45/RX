#pragma once
//=====================================================================//
/*!	@file
	@brief	MAX6675 クラス @n
			Cold-Junction-Compensated @n
			K-Thermocouple to Digital Converter 0℃ to 1024℃ @n
			Vcc: 3.3V、5.0V
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cmath>

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MAX6675 テンプレートクラス
		@param[in]	SPI	spi クラス
		@param[in]	CS	チップ・セレクト
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SPI, class CS>
	class MAX6675 {

		SPI&	spi_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクタ
		 */
		//-----------------------------------------------------------------//
		MAX6675(SPI& spi) noexcept : spi_(spi) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
		 */
		//-----------------------------------------------------------------//
		void start() noexcept
		{
			CS::DIR = 1;
			CS::P = 1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	値取得
			@return 値、変換温度 (0 to 4095) 0.25℃ (0℃ to 1024℃)
		 */
		//-----------------------------------------------------------------//
		uint16_t get() noexcept
		{
			CS::P = 0;
			// delay 100ns
			utils::delay::nano_second(100);
			uint8_t tmp[2];
			spi_.recv(tmp, 2);
			uint16_t v = (static_cast<uint16_t>(tmp[0]) << 5) | (static_cast<uint16_t>(tmp[1]) >> 3);
			CS::P = 1;
			return v;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	温度取得
			@return 温度
		 */
		//-----------------------------------------------------------------//
		float get_temp() noexcept
		{
			return static_cast<float>(get()) * 0.25f;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	() オペレーター
			@return 変換温度 (0 to 4095) 0.25℃ (0℃ to 1024℃)
		 */
		//-----------------------------------------------------------------//
		uint16_t operator () ()
		{
			return get();
		}
	};
}
