#pragma once
//=====================================================================//
/*!	@file
	@brief	delay ユーティリティー (RX) @n
			Copyright 2016, 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>

#ifndef F_ICLK
#  error "delay.hpp requires F_ICLK to be defined"
#endif

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ソフトウェアー待ち
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct delay {

		//-----------------------------------------------------------------//
		/*!
			@brief  ループ
			@param[in]	cnt	ループ回数
		*/
		//-----------------------------------------------------------------//
		static void loop(uint32_t cnt)
		{
			while(cnt > 0) {
				asm("nop");
				--cnt;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  マイクロ秒単位の待ち @n
					あまり正確では無く、速度に関連する設定に依存します。
			@param[in]	us	待ち時間（マイクロ秒）
		*/
		//-----------------------------------------------------------------//
		static void micro_second(uint32_t us)
		{
			while(us > 0) {
#if defined(SIG_RX64M) || defined(SIG_RX63T)
				for(uint32_t n = 0; n < (F_ICLK / 4285714); ++n) {
					asm("nop");
				}
#elif defined(SIG_RX24T)
				for(uint32_t n = 0; n < (F_ICLK / 5333333); ++n) {
					asm("nop");
				}
#else
#  error "delay.hpp requires tune dummy operations"
#endif
				--us;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ミリ秒単位の待ち
			@param[in]	ms	待ち時間（ミリ秒）
		*/
		//-----------------------------------------------------------------//
		static void milli_second(uint32_t ms)
		{
			for(uint32_t i = 0; i < ms; ++i) {
				micro_second(1000);
			}
		}
	};
}
