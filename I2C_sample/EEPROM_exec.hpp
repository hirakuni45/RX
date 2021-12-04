#pragma once
//=====================================================================//
/*!	@file
	@brief	EEPROM exec クラス
	@author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "chip/EEPROM.hpp"

namespace EEPROM {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	BMP280 デバイス操作
		@param[in] I2C_IO	I2C I/O クラス
		@param[in] CMD_LIN	コマンドライン入力クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class I2C_IO, class CMD_LIN>
	class exec {

		typedef chip::EEPROM<I2C_IO> I2C_DEV;
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
			auto id = static_cast<typename I2C_DEV::M64KB>(adr & 7);
			I2C_DEV_.start(id, 32);
			return true;
		}

		//-----------------------------------------------------------------//
		/*!
			@brief	解析
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool analize()
		{
			uint32_t cmdn = cmd_.get_words();
			if(cmdn == 0) return true;  // 入力が無い場合はエラー無しとする

//			if(exec_common_()) {
//				return;
//			}

			if(cmdn >= 2 && cmd_.cmp_word(0, "read")) {
				int32_t org = 0;
				if(!cmd_.get_integer(1, org, true)) {
					utils::format("EEPROM ORG invalid.\n");
					return false;
				}
				int32_t end = org + 16;
				if(cmdn >= 3) {
					if(!cmd_.get_integer(2, end, true)) {
						utils::format("EEPROM END invalid.\n");
						return false;
					}
					++end;
				}
				while(org < end) {
					uint8_t tmp[16];
					auto len = end - org;
					if(len > 16) len = 16;
					if(!I2C_DEV_.read(org, tmp, len)) {
						utils::format("EEPROM read error.\n");
					}
					utils::format("%04X- ") % org;
					utils::str::dump_hex(tmp, len, 16);
					if(len < 16) {
						utils::format("\n");
					}
					org += len;
				}
			} else if(cmdn >= 3 && cmd_.cmp_word(0, "write")) {
				int32_t org = 0;
				if(!cmd_.get_integer(1, org, true)) {
					utils::format("EEPROM ORG invalid.\n");
					return false;
				}
				uint32_t l = 0;
				uint8_t tmp[32];
				if(cmdn >= (32 + 2)) {
					utils::format("EEPROM DATA too match. (limit 32)\n");
					return false;
				}
				while(l < (cmdn - 2)) {
					int32_t val = 1;
					if(cmd_.get_integer(l + 2, val, true)) {
						tmp[l] = val;
					} else {
						utils::format("EEPROM DATA invalid.\n");
						return false;
					}
					++l;
				}
				if(!I2C_DEV_.write(org, tmp, l)) {
					utils::format("EEPROM write error.\n");
					return false;
				}
			} else if(cmdn >= 1 && cmd_.cmp_word(0, "--help")) {
				utils::format("EEPROM operations\n");
				utils::format("    read ORG [END=+16]\n");
				utils::format("    write ORG DATA...\n");
				utils::format("    --help\n");
				utils::format("\n");
			} else {
				char tmp[256];
				cmd_.get_word(0, tmp, sizeof(tmp));
				utils::format("EEPROM command error: '%s'\n") % tmp;
				return false;
			}
			return true;
		}
	};
}
