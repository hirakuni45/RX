#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ高分解能 PWM マネージャー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  HRPWM マネージャー・クラス
        @param[in] HRPWMX   HRPWM 型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    template <class HRPWMX>
	class hrpwm_mgr {

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
        hrpwm_mgr() noexcept
        {
        }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
            @param[in]  gptw0   有効の場合「true」
            @param[in]  gptw1   有効の場合「true」
            @param[in]  gptw2   有効の場合「true」
            @param[in]  gptw3   有効の場合「true」
		*/
		//-----------------------------------------------------------------//
        bool start(bool gptw0, bool gptw1, bool gptw2, bool gptw3) noexcept
        {
            if(!power_mgr::turn(HRPWMX::PERIPHERAL)) {
				return false;
			}

            // クロック選択
            HRPWMX::set_base_clock();

            HRPWMX::HROCR.DLLEN = 0;
            HRPWMX::HROCR.HRRST = 1;
            if(gptw0) {
                HRPWMX::HROCR2.HRSEL0 = 0;
            }
            if(gptw1) {
                HRPWMX::HROCR2.HRSEL1 = 0;
            }
            if(gptw2) {
                HRPWMX::HROCR2.HRSEL2 = 0;
            }
            if(gptw3) {
                HRPWMX::HROCR2.HRSEL3 = 0;
            }

            HRPWMX::HROCR.DLLEN = 1;

            utils::delay::micro_second(20);

            HRPWMX::HROCR.HRRST = 0;

            auto m = device::clock_profile::ICLK / device::clock_profile::PCLKC;
            if(m == 0) m = 1;
            utils::delay::loop(12 * m);  // PCLKC, 12 cycle

            if(gptw0) {
                HRPWMX::HROCR2.HRSEL0 = 1;
            }
            if(gptw1) {
                HRPWMX::HROCR2.HRSEL1 = 1;
            }
            if(gptw2) {
                HRPWMX::HROCR2.HRSEL2 = 1;
            }
            if(gptw3) {
                HRPWMX::HROCR2.HRSEL3 = 1;
            }

            return true;
        }


		//-----------------------------------------------------------------//
		/*!
			@brief  立ち上がり遅延を設定（Ａ）
            @param[in]  ch      チャネル（０～３）
            @param[in]  delay   遅延数（０～３１）
		*/
		//-----------------------------------------------------------------//
        void set_positive_delay_a(uint32_t ch, uint8_t delay) noexcept
        {
            switch(ch) {
            case 0:
                HRPWMX::HRREAR0A = delay;
                break;
            case 1:
                HRPWMX::HRREAR1A = delay;
                break;
            case 2:
                HRPWMX::HRREAR2A = delay;
                break;
            case 3:
                HRPWMX::HRREAR3A = delay;
                break;
            default:
                break;
            }
        }


		//-----------------------------------------------------------------//
		/*!
			@brief  立ち上がり遅延を設定（Ｂ）
            @param[in]  ch      チャネル（０～３）
            @param[in]  delay   遅延数（０～３１）
		*/
		//-----------------------------------------------------------------//
        void set_positive_delay_b(uint32_t ch, uint8_t delay) noexcept
        {
            switch(ch) {
            case 0:
                HRPWMX::HRREAR0B = delay;
                break;
            case 1:
                HRPWMX::HRREAR1B = delay;
                break;
            case 2:
                HRPWMX::HRREAR2B = delay;
                break;
            case 3:
                HRPWMX::HRREAR3B = delay;
                break;
            default:
                break;
            }
        }


		//-----------------------------------------------------------------//
		/*!
			@brief  立ち下がり遅延を設定（Ａ）
            @param[in]  ch      チャネル（０～３）
            @param[in]  delay   遅延数（０～３１）
		*/
		//-----------------------------------------------------------------//
        void set_negative_delay_a(uint32_t ch, uint8_t delay) noexcept
        {
            switch(ch) {
            case 0:
                HRPWMX::HRFEAR0A = delay;
                break;
            case 1:
                HRPWMX::HRFEAR1A = delay;
                break;
            case 2:
                HRPWMX::HRFEAR2A = delay;
                break;
            case 3:
                HRPWMX::HRFEAR3A = delay;
                break;
            default:
                break;
            }
        }


		//-----------------------------------------------------------------//
		/*!
			@brief  立ち下がり遅延を設定（Ｂ）
            @param[in]  ch      チャネル（０～３）
            @param[in]  delay   遅延数（０～３１）
		*/
		//-----------------------------------------------------------------//
        void set_negative_delay_b(uint32_t ch, uint8_t delay) noexcept
        {
            switch(ch) {
            case 0:
                HRPWMX::HRFEAR0B = delay;
                break;
            case 1:
                HRPWMX::HRFEAR1B = delay;
                break;
            case 2:
                HRPWMX::HRFEAR2B = delay;
                break;
            case 3:
                HRPWMX::HRFEAR3B = delay;
                break;
            default:
                break;
            }
        }
    };
}