#pragma once
//=====================================================================//
/*!	@file
	@brief	遅延ユーティリティー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"
#ifdef RTOS
#include "FreeRTOS.h"
#include "task.h"
#endif

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ソフトウェアー遅延
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct delay {

		//-----------------------------------------------------------------//
		/*!
			@brief  単純ループ
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
					あまり正確では無く、速度に関連する設定に依存します。 @n
					※キャッシュ有効、最高速度での物理計測によるパラメータ
			@param[in]	us	待ち時間（マイクロ秒）
		*/
		//-----------------------------------------------------------------//
		static void micro_second(uint32_t us)
		{
			while(us > 0) {
				// RXv2 コア（最大 80MHz）
				for(uint32_t n = 0; n < device::clock_profile::DELAY_MS; ++n) {
					asm("nop");
				}
				--us;
			}
			if(device::clock_profile::DELAY_T1) { asm("nop"); }
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
