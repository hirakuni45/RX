#pragma once
//=====================================================================//
/*!	@file
	@brief	exec_cmd クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "EEPROM_exec.hpp"
#include "DS3231_exec.hpp"
#include "BMP280_exec.hpp"

#include "common/format.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	exec_base クラス
	 */
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct exec_base {

		enum class DEV : uint8_t {
			NONE,
			EEPROM,
			DS3231,
			BMP280,
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	exec_cmd クラス
		@param[in] I2C_IO	i2c I/O クラス
		@param[in] CMD_LIN	コマンドライン入力クラス		
	 */
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class I2C_IO, class CMD_LIN>
	class exec_cmd : public exec_base {

		DEV				dev_;

		typedef EEPROM::exec<I2C_IO, CMD_LIN> EEPROM_EXEC;
		EEPROM_EXEC		EEPROM_EXEC_;
		typedef DS3231::exec<I2C_IO, CMD_LIN> DS3231_EXEC;
		DS3231_EXEC		DS3231_EXEC_;
		typedef BMP280::exec<I2C_IO, CMD_LIN> BMP280_EXEC;
		BMP280_EXEC		BMP280_EXEC_;

		CMD_LIN			cmd_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		exec_cmd(I2C_IO& i2c_io, CMD_LIN& cmd) :
			dev_(DEV::NONE),
			EEPROM_EXEC_(i2c_io, cmd),
			DS3231_EXEC_(i2c_io, cmd),
			BMP280_EXEC_(i2c_io, cmd),
			cmd_(cmd)
		{ }


		//-------------------------------------------------------------//
		/*!
			@brief	開始
			@param[in]	adr		I2C address
			@param[in]	dev		デバイス型
			@return 正常に開始出来たら「true」
		*/
		//-------------------------------------------------------------//
		bool start(uint8_t adr, DEV dev)
		{
			bool ret = false;
			if(dev_ != dev) {
				switch(dev) {
				case DEV::EEPROM:
					ret = EEPROM_EXEC_.start(adr);
					break;
				case DEV::DS3231:
					ret = DS3231_EXEC_.start(adr);
					break;
				case DEV::BMP280:
					ret = BMP280_EXEC_.start(adr);
					break;
				default:
					break;
				}
				if(ret) {
					dev_ = dev;
				} else {
					utils::format("Start fail I2C: \n");
				}
			}
			return ret;
		}



    };
}
