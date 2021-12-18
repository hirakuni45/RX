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
#include "AS5600_exec.hpp"

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
			AS5600,
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
		uint8_t			adr_;

		typedef EEPROM::exec<I2C_IO, CMD_LIN> EEPROM_EXEC;
		EEPROM_EXEC		EEPROM_EXEC_;
		typedef DS3231::exec<I2C_IO, CMD_LIN> DS3231_EXEC;
		DS3231_EXEC		DS3231_EXEC_;
		typedef BMP280::exec<I2C_IO, CMD_LIN> BMP280_EXEC;
		BMP280_EXEC		BMP280_EXEC_;
		typedef AS5600::exec<I2C_IO, CMD_LIN> AS5600_EXEC;
		AS5600_EXEC		AS5600_EXEC_;

		CMD_LIN&		cmd_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		exec_cmd(I2C_IO& i2c_io, CMD_LIN& cmd) noexcept :
			dev_(DEV::NONE), adr_(0),
			EEPROM_EXEC_(i2c_io, cmd),
			DS3231_EXEC_(i2c_io, cmd),
			BMP280_EXEC_(i2c_io, cmd),
			AS5600_EXEC_(i2c_io, cmd),
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
		bool start(uint8_t adr, DEV dev) noexcept
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
				case DEV::AS5600:
					ret = BMP280_EXEC_.start(adr);
					break;
				default:
					utils::format("Under construction...\n");
					break;
				}
				if(ret) {
					dev_ = dev;
					adr_ = adr;
				} else {
					utils::format("Start fail I2C: \n");
				}
			}
			return ret;
		}


		//-------------------------------------------------------------//
		/*!
			@brief	各 I2C デバイスのサービス
		*/
		//-------------------------------------------------------------//
		void service() noexcept
		{
			switch(dev_) {
			case DEV::EEPROM:
				EEPROM_EXEC_.service();
				break;
			case DEV::DS3231:
				DS3231_EXEC_.service();
				break;
			case DEV::BMP280:
				BMP280_EXEC_.service();
				break;
			case DEV::AS5600:
				AS5600_EXEC_.service();
				break;
			default:
				break;
			}
		}


		//-------------------------------------------------------------//
		/*!
			@brief	各 I2C デバイスの解析
			@return 終了の場合「true」
		*/
		//-------------------------------------------------------------//
		bool analize() noexcept
		{
			auto cmdn = cmd_.get_words();
			if(cmdn >= 1) {
				if(cmd_.cmp_word(0, "exit")) {
					dev_ = DEV::NONE;
					adr_ = 0;
					return true;
				}
			}

			switch(dev_) {
			case DEV::EEPROM:
				EEPROM_EXEC_.analize();
				break;
			case DEV::DS3231:
				DS3231_EXEC_.analize();
				break;
			case DEV::BMP280:
				BMP280_EXEC_.analize();
				break;
			case DEV::AS5600:
				AS5600_EXEC_.analize();
				break;
			default:
				break;
			}
			return false;
		}
    };
}
