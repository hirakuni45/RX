#pragma once
//=====================================================================//
/*!	@file
	@brief	BMP280 exec クラス
	@author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "chip/BMP280.hpp"

namespace BMP280 {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	BMP280 デバイス操作
		@param[in] I2C_IO	I2C I/O クラス
		@param[in] CMD_LIN	コマンドライン入力クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class I2C_IO, class CMD_LIN>
	class exec {

		typedef chip::BMP280<I2C_IO> BMP280;
		BMP280		BMP280_;

		CMD_LIN&	cmd_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in] i2c_io	I2C I/O クラス
			@param[in] cmd_		コマンドライン入力クラス
		*/
		//-----------------------------------------------------------------//
		exec(I2C_IO& i2c_io, CMD_LIN& cmd) : BMP280_(i2c_io), cmd_(cmd) { } 


		//-----------------------------------------------------------------//
		/*!
			@brief	BMP280 開始
			@param[in]	adr		I2C address
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool start(uint8_t adr)
		{
			if(!BMP280_.start(adr)) {
				utils::format("BMP280 Start fail...\n");
				return false;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	BMP280 コマンド解析
		*/
		//-----------------------------------------------------------------//
		void analize() noexcept
		{
			auto cmdn = cmd_.get_words();
			if(cmdn == 0) return;

			if(cmdn >= 1 && cmd_.cmp_word(0, "--help")) {
				utils::format("BMP280 operations\n");
				utils::format("    list\n");
				utils::format("    --help\n");
				utils::format("\n");
			} else if(cmdn >= 1 && cmd_.cmp_word(0, "list")) {
				auto t = BMP280_.get_temperature();
				utils::format("Temperature: %5.2f C\n") % (static_cast<float>(t) / 100.0f);
				auto p = BMP280_.get_pressure();
				utils::format("Pressure: %7.2f hPa\n") % (static_cast<float>(p) / 100.0f);
				auto a = BMP280_.get_altitude();
				utils::format("Altitude: %7.2f m\n") % a;
			} else {
				char tmp[256];
				cmd_.get_word(0, tmp, sizeof(tmp));
				utils::format("BMP280 command error: '%s'\n") % tmp;
			}
		}
	};
}