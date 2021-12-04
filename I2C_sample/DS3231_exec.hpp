#pragma once
//=====================================================================//
/*!	@file
	@brief	DS3231 exec クラス
	@author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "chip/DS3231.hpp"

namespace DS3231 {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	BMP280 デバイス操作
		@param[in] I2C_IO	I2C I/O クラス
		@param[in] CMD_LIN	コマンドライン入力クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class I2C_IO, class CMD_LIN>
	class exec {

		typedef chip::DS3231<I2C_IO> I2C_DEV;
		I2C_DEV		I2C_DEV_;

		CMD_LIN&	cmd_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in] i2c_io	I2C I/O クラス
			@param[in] cmd_		コマンドライン入力クラス
		*/
		//-----------------------------------------------------------------//
		exec(I2C_IO& i2c_io, CMD_LIN& cmd) : I2C_DEV_(i2c_io), cmd_(cmd) { } 


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@param[in]	adr		I2C address
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool start(uint8_t adr)
		{
			return true;
		}

#if 0
		if(!start_i2c_dev_) {
			if(!DS3231_.start()) {
				utils::format("DS3231 Start fail.\n");
				exec_common_(true);
				return;
			}
			start_i2c_dev_ = true;
		}

		uint32_t cmdn = cmd_.get_words();
		if(cmdn == 0) return;

		if(exec_common_()) {
			return;
		}

		if(cmdn >= 1 && cmd_.cmp_word(0, "--help")) {
			utils::format("DS3231 operations\n");
			utils::format("    --help\n");
			utils::format("\n");
		} else {
			char tmp[256];
			cmd_.get_word(0, tmp, sizeof(tmp));
			utils::format("DS3231 command error: '%s'\n") % tmp;
		}
#endif
	};
}