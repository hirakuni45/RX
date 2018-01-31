#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・RTC 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX600/rtc.hpp"
#include "RX600/system.hpp"
#include "common/time.h"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RTC 制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class rtc_io {

		static uint32_t get_() {
			uint32_t t;
			t  = static_cast<uint32_t>(device::RTC.BCNT0());
			t |= static_cast<uint32_t>(device::RTC.BCNT1()) << 8;
			t |= static_cast<uint32_t>(device::RTC.BCNT2()) << 16;
			t |= static_cast<uint32_t>(device::RTC.BCNT3()) << 24;
			return t;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		rtc_io() { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool start() {
			device::SYSTEM::SOSCCR.SOSTP = 0;

			device::RTC.RCR3 = device::RTC.RCR3.RTCEN.b(1) | device::RTC.RCR3.RTCDV.b(0b110);
			device::RTC.RCR4 = 0x00;
			device::RTC.RCR2 = device::RTC.RCR2.START.b(1)
							| device::RTC.RCR2.RESET.b(1)
							| device::RTC.RCR2.CNTMD.b(1);  // binary counter
			device::RTC.RCR1 = 0x00;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	時間設定
			@param[in]	t	時間
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool set_time(time_t t) const {
			device::RTC.RCR2.START = 0;
			device::RTC.BCNT0 = t & 0xff;
			device::RTC.BCNT1 = (t >> 8)  & 0xff;
			device::RTC.BCNT2 = (t >> 16) & 0xff;
			device::RTC.BCNT3 = (t >> 24) & 0xff;
			device::RTC.RCR2.START = 1;
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	時間呼び出し
			@param[in]	tp	取得時間
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool get_time(time_t& tp) const {
			auto a = get_();
			for(int i = 0; i < 5; ++i) {
				auto b = get_();
				if(a == b) {
					tp = static_cast<time_t>(a);
					return true;
				}
				a = b;
			}
			return false;
		}
	};
}
