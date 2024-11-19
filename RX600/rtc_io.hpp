#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・RTC 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/time.h"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RTC 制御クラス
		@param[in]	RTC		RTC 型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RTC>
	class rtc_io {

		static uint32_t get_() noexcept {
			uint32_t t;
			t  = static_cast<uint32_t>(RTC::BCNT0());
			t |= static_cast<uint32_t>(RTC::BCNT1()) << 8;
			t |= static_cast<uint32_t>(RTC::BCNT2()) << 16;
			t |= static_cast<uint32_t>(RTC::BCNT3()) << 24;
			return t;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		rtc_io() noexcept { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始 @n
					※バイナリーカウントモードが無い場合、失敗する。
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool start() noexcept
		{
			if(!RTC::BINARY) {
				return false;
			}

			RTC::RCR3 = RTC::RCR3.RTCEN.b(1) | RTC::RCR3.RTCDV.b(0b110);
			RTC::RCR4 = 0x00;
			RTC::RCR2 = RTC::RCR2.START.b(1)
					  | RTC::RCR2.RESET.b(1)
					  | RTC::RCR2.CNTMD.b(1);  // binary counter
			RTC::RCR1 = 0x00;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	時間設定
			@param[in]	t	時間
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool set_time(time_t t) const noexcept
		{
			RTC::RCR2.START = 0;
			RTC::BCNT0 = t & 0xff;
			RTC::BCNT1 = (t >> 8)  & 0xff;
			RTC::BCNT2 = (t >> 16) & 0xff;
			RTC::BCNT3 = (t >> 24) & 0xff;
			RTC::RCR2.START = 1;
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	バイナリー時間呼び出し
			@param[in]	tp	取得時間
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool get_time(time_t& tp) const noexcept
		{
			auto a = get_();
			auto b = a;
			for(int i = 0; i < 5; ++i) {
				b = get_();
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
