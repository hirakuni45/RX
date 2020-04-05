#pragma once
//=====================================================================//
/*!	@file
	@brief	遅延ユーティリティー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#ifdef RTOS
#include "FreeRTOS.h"
#include "task.h"
#endif

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
					あまり正確では無く、速度に関連する設定に依存します。@n
					※キャッシュ有効、最高速度での物理計測によるパラメータ
			@param[in]	us	待ち時間（マイクロ秒）
		*/
		//-----------------------------------------------------------------//
		static void micro_second(uint32_t us)
		{
			while(us > 0) {
#if defined(SIG_RX64M) || defined(SIG_RX63T) || defined(SIG_RX71M) || defined(SIG_RX72M)
				for(uint32_t n = 0; n < (F_ICLK / 4285714); ++n) {
					asm("nop");
				}
#elif defined(SIG_RX65N)
				for(uint32_t n = 0; n < (F_ICLK / 4444444); ++n) {
					asm("nop");
				}
#elif defined(SIG_RX24T)
				for(uint32_t n = 0; n < (F_ICLK / 4444444); ++n) {
					asm("nop");
				}
#elif defined(SIG_RX66T)
				for(uint32_t n = 0; n < (F_ICLK / 3346666); ++n) {
					asm("nop");
				}
#elif defined(SIG_RX72T)
				for(uint32_t n = 0; n < (F_ICLK / 3346666); ++n) {
					asm("nop");
				}
#elif defined(SIG_RX72N)
				for(uint32_t n = 0; n < (F_ICLK / 3346666); ++n) {
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
#ifdef RTOS
			vTaskDelay(ms / portTICK_PERIOD_MS);
#else
			for(uint32_t i = 0; i < ms; ++i) {
				micro_second(1000);
			}
#endif
		}
	};
}
