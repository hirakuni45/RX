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

		typedef chip::DS3231<I2C_IO> DS3231;
		DS3231		DS3231_;

		CMD_LIN&	cmd_;

		time_t get_time_()
		{
			time_t t = 0;
			if(!DS3231_.get_time(t)) {
				utils::format("Stall RTC read\n");
			}
			return t;
		}


		void disp_time_(time_t t)
		{
			struct tm *m = localtime(&t);
			utils::format("%s %s %d %02d:%02d:%02d  %4d\n")
				% get_wday(m->tm_wday)
				% get_mon(m->tm_mon)
				% static_cast<uint32_t>(m->tm_mday)
				% static_cast<uint32_t>(m->tm_hour)
				% static_cast<uint32_t>(m->tm_min)
				% static_cast<uint32_t>(m->tm_sec)
				% static_cast<uint32_t>(m->tm_year + 1900);
		}


		const char* get_dec_(const char* p, char tmch, int& value)
		{
			int v = 0;
			char ch;
			while((ch = *p) != 0) {
				++p;
				if(ch == tmch) {
					break;
				} else if(ch >= '0' && ch <= '9') {
					v *= 10;
					v += ch - '0';
				} else {
					return nullptr;
				}
			}
			value = v;
			return p;
		}


		void set_time_date_()
		{
			time_t t = get_time_();
			if(t == 0) return;

			struct tm *m = localtime(&t);
			bool err = false;
			if(cmd_.get_words() == 3) {
				char buff[12];
				if(cmd_.get_word(1, buff, sizeof(buff))) {
					const char* p = buff;
					int vs[3];
					uint8_t i;
					for(i = 0; i < 3; ++i) {
						p = get_dec_(p, '/', vs[i]);
						if(p == nullptr) {
							break;
						}
					}
					if(p != nullptr && p[0] == 0 && i == 3) {
						if(vs[0] >= 1900 && vs[0] < 2100) m->tm_year = vs[0] - 1900;
						if(vs[1] >= 1 && vs[1] <= 12) m->tm_mon = vs[1] - 1;
						if(vs[2] >= 1 && vs[2] <= 31) m->tm_mday = vs[2];		
					} else {
						err = true;
					}
				}

				if(cmd_.get_word(2, buff, sizeof(buff))) {
					const char* p = buff;
					int vs[3];
					uint8_t i;
					for(i = 0; i < 3; ++i) {
						p = get_dec_(p, ':', vs[i]);
						if(p == nullptr) {
							break;
						}
					}
					if(p != nullptr && p[0] == 0 && (i == 2 || i == 3)) {
						if(vs[0] >= 0 && vs[0] < 24) m->tm_hour = vs[0];
						if(vs[1] >= 0 && vs[1] < 60) m->tm_min = vs[1];
						if(i == 3 && vs[2] >= 0 && vs[2] < 60) m->tm_sec = vs[2];
						else m->tm_sec = 0;
					} else {
						err = true;
					}
				}
			}

			if(err) {
				utils::format("Can't analize Time/Date input.\n");
				return;
			}

			time_t tt = mktime(m);
			if(!DS3231_.set_time(tt)) {
				utils::format("Stall RTC write...\n");
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in] i2c_io	I2C I/O クラス
			@param[in] cmd_		コマンドライン入力クラス
		*/
		//-----------------------------------------------------------------//
		exec(I2C_IO& i2c_io, CMD_LIN& cmd) noexcept : DS3231_(i2c_io), cmd_(cmd) { } 


		//-----------------------------------------------------------------//
		/*!
			@brief	DS3231 開始
			@param[in]	adr		I2C address
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool start(uint8_t adr)
		{
			if(!DS3231_.start()) {
				utils::format("DS3231 Start fail.\n");
				return false;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	DS3231 解析
		*/
		//-----------------------------------------------------------------//
		void analize() noexcept
		{
			auto cmdn = cmd_.get_words();
			if(cmdn == 0) return;

			if(cmdn >= 1) {
				if(cmd_.cmp_word(0, "date")) {
					if(cmdn == 1) {
						time_t t = get_time_();
						if(t != 0) {
							disp_time_(t);
						}
					} else {
						set_time_date_();
					}
				} else if(cmd_.cmp_word(0, "--help")) {
					utils::format("DS3231 operations\n");
					utils::format("    date\n");
					utils::format("    date yyyy/mm/dd hh:mm[:ss]\n");
					utils::format("    --help\n");
					utils::format("\n");
				} else {
					char tmp[256];
					cmd_.get_word(0, tmp, sizeof(tmp));
					utils::format("DS3231 command error: '%s'\n") % tmp;
				}
			}
		}
	};
}