#pragma once
//=====================================================================//
/*!	@file
	@brief	DS3231 RTC ドライバー
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include "common/iica_io.hpp"
#include "common/time.h"

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DS3231 RTC テンプレートクラス
		@param[in]	I2C_IO	i2c I/O クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class I2C_IO>
	class DS3231 {

		// R/W ビットを含まない７ビット値
		static const uint8_t DS3231_ADR_ = 0x68;

		I2C_IO& i2c_io_;

		struct reg_t {
			uint8_t	reg[7];
			bool operator != (const reg_t& t) {
				for(uint8_t i = 0; i < 7; ++i) {
					if(reg[i] != t.reg[i]) return true;
				}
				return false;
			}
		};

		bool get_time_(reg_t& t) const {
			uint8_t reg[1];
			reg[0] = 0x00;	// set address
			if(!i2c_io_.send(DS3231_ADR_, reg, 1)) {
				return false;
			}
			if(!i2c_io_.recv(DS3231_ADR_, &t.reg[0], 7)) {
				return false;
			}
			return true;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	i2c	iica_io クラスを参照で渡す
		 */
		//-----------------------------------------------------------------//
		DS3231(I2C_IO& i2c) : i2c_io_(i2c) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@return エラーなら「false」を返す
		 */
		//-----------------------------------------------------------------//
		bool start() {
			uint8_t reg[2];
			reg[0] = 0x0e;	/// internal register address
			reg[1] = 0x00;
			return i2c_io_.send(DS3231_ADR_, reg, 2);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	DS3231 時間設定
			@param[in]	t	時間
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool set_time(time_t t) const {
			const tm* tp = gmtime(&t);
			uint8_t reg[7];
			reg[0] = ((tp->tm_sec  / 10) << 4) | (tp->tm_sec  % 10);  // 0 to 59
			reg[1] = ((tp->tm_min  / 10) << 4) | (tp->tm_min  % 10);  // 0 to 59
			reg[2] = ((tp->tm_hour / 10) << 4) | (tp->tm_hour % 10);  // 0 to 23
			reg[3] = tp->tm_wday + 1;  // 1 to 7
			reg[4] = ((tp->tm_mday / 10) << 4) | (tp->tm_mday % 10);  // 1 to 31
			uint8_t mon = tp->tm_mon + 1;
			reg[5] = ((mon / 10) << 4) | (mon % 10);  // 1 to 12
			uint16_t y = tp->tm_year % 100;
			reg[6] = ((y / 10) << 4) | (y % 10);  // 0 to 99
			return i2c_io_.send(DS3231_ADR_, 0x00, reg, 7);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	DS3231 時間呼び出し
			@param[in]	tp	取得時間
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool get_time(time_t& tp) const {
			reg_t t;
			reg_t tmp;
			tm ts;
			// 二度読んで、同じだったら正しい時間とする
			uint8_t n = 5; // ５回ループして正常に読めなかったら、エラーとする
			do {
				tmp = t;
				if(!get_time_(t)) return false;
				--n;
				if(n == 0) {
					return false;
				}
			} while(t != tmp) ;

			ts.tm_sec  = ((t.reg[0] >> 4) * 10) + (t.reg[0] & 0xf);
			ts.tm_min  = ((t.reg[1] >> 4) * 10) + (t.reg[1] & 0xf);
			ts.tm_hour = ((t.reg[2] >> 4) * 10) + (t.reg[2] & 0xf);
			ts.tm_mday = ((t.reg[4] >> 4) * 10) + (t.reg[4] & 0xf);
			ts.tm_mon  = ((((t.reg[5] & 0x10) >> 4) * 10) + (t.reg[5] & 0xf)) - 1;
			ts.tm_year = ((t.reg[6] >> 4) * 10) + (t.reg[6] & 0xf);
			ts.tm_year += 100;
			tp = mktime(&ts);
			return true;
		}
	};
}
