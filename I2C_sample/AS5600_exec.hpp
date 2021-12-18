#pragma once
//=====================================================================//
/*!	@file
	@brief	AS5600 exec クラス
	@author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "chip/AS5600.hpp"

namespace AS5600 {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	BMP280 デバイス操作
		@param[in] I2C_IO	I2C I/O クラス
		@param[in] CMD_LIN	コマンドライン入力クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class I2C_IO, class CMD_LIN>
	class exec {

		typedef chip::AS5600<I2C_IO> AS5600;
		AS5600		AS5600_;

		CMD_LIN&	cmd_;

		uint16_t	mag_;
		uint8_t		notcnt_;
		bool		run_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in] i2c_io	I2C I/O クラス
			@param[in] cmd_		コマンドライン入力クラス
		*/
		//-----------------------------------------------------------------//
		exec(I2C_IO& i2c_io, CMD_LIN& cmd) : AS5600_(i2c_io), cmd_(cmd),
			mag_(0), notcnt_(0), run_(false)
		{ } 


		//-----------------------------------------------------------------//
		/*!
			@brief	AS5600 開始
			@param[in]	adr		I2C address
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool start(uint8_t adr)
		{
			if(!AS5600_.start(adr)) {
				utils::format("AS5600 Start fail...\n");
				return false;
			}
			mag_ = AS5600_.get_magnitude();
			run_ = false;
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	AS5600 サービス
		*/
		//-----------------------------------------------------------------//
		void service() noexcept
		{
			if(run_) {
				if(sci_length() > 0) {
					auto ch = sci_getch();
					if(ch == ('C' - 0x40)) {
						run_ = false;
						return;
					}					
				}
				if(!AS5600_.is_magnet_detected()) {
					++notcnt_;
					if(notcnt_ >= 60) {
						utils::format("Not Ditected...\n");
						notcnt_ = 0;
					}
					return;
				} else {
					notcnt_ = 0;
				}
				auto mag = AS5600_.get_magnitude();
				if(mag != mag_) {
					mag_ = mag;
					utils::format("%04d\n") % mag;
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	AS5600 コマンド解析
		*/
		//-----------------------------------------------------------------//
		void analize() noexcept
		{
			auto cmdn = cmd_.get_words();
			if(cmdn == 0) return;

			if(cmdn >= 1 && cmd_.cmp_word(0, "--help")) {
				utils::format("AS5600 operations\n");
				utils::format("    list     list values\n");
				utils::format("    run      list magnitude value ('CTRL-C' to stop)\n");
				utils::format("    --help\n");
				utils::format("\n");
			} else if(cmdn >= 1 && cmd_.cmp_word(0, "list")) {
				bool f = AS5600_.is_magnet_detected();
				utils::format("Ditected: %d\n") % static_cast<uint16_t>(f);
				f = AS5600_.is_magnet_too_strong();
				if(f) {
					utils::format("Too Strong!\n") % static_cast<uint16_t>(f);
				}
				f = AS5600_.is_magnet_too_weak();
				if(f) {
					utils::format("Too Weak!\n") % static_cast<uint16_t>(f);
				}
				auto mag = AS5600_.get_magnitude();
				utils::format("Magnitude: %04d\n") % mag;
			} else if(cmdn >= 1 && cmd_.cmp_word(0, "run")) {
				run_ = true;
			} else {
				char tmp[256];
				cmd_.get_word(0, tmp, sizeof(tmp));
				utils::format("AS5600 command error: '%s'\n") % tmp;
			}
		}
	};
}