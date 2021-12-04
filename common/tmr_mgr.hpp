#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・TMR マネージャー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/intr_utils.hpp"
#include "common/vect.h"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  TMR マネージャー・クラス @
				１６ビット・モードで利用する場合、TMR は、TMR0、又は、TMR2 を指定
		@param[in]	TMR		TMR チャネルクラス
		@param[in]	TASK	タイマー動作クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class TMR, class TASK = utils::null_task>
	class tmr_mgr {

		static TASK		task_;

		ICU::VECTOR		intr_vec_;
		uint32_t		freq_;
		uint8_t			shift_;

		static INTERRUPT_FUNC void match_task_()
		{
			task_();
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		tmr_mgr() noexcept :
			intr_vec_(ICU::VECTOR::NONE), freq_(0), shift_(0) 
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始（１６ビットインターバルタイマー）
			@param[in]	freq	タイマー周波数
			@param[in]	level	割り込みレベル（０ならポーリング）
			@return タイマー周波数が範囲を超えた場合「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t freq, uint8_t level = 0) noexcept
		{
			// 16 bits バインドでは、奇数は NG
			if(TMR::PERIPHERAL == device::peripheral::TMR1 || TMR::PERIPHERAL == device::peripheral::TMR3) {
				return false;
			}

			freq_ = freq;

			auto match = TMR::PCLK / freq;
			uint8_t shift = 0;
			while(match > 65536) {
				match /= 2;
				++shift;
				if(match <= 1 || shift > 13) {
					return false;
				}
			}
			while(shift == 2 || shift == 4 || shift == 7 || shift == 8 || shift == 9 || shift == 11 || shift == 12) {
				match /= 2;
				++shift;
			}
			if(match <= 1) return false;
			shift_ = shift;

			if(!device::power_mgr::turn(TMR::PERIPHERAL)) {
				return false;
			}

			TMR::TCCR = 0;
			if(TMR::PERIPHERAL == device::peripheral::TMR0) {
				device::TMR1::TCCR = 0;
			} else {
				device::TMR3::TCCR = 0;
			}

			TMR::TCR.CCLR = 0b01;  // CMP Match-A
			TMR::TCNT16 = 0;
			TMR::TCORA16 = match - 1;

			if(level > 0) {
				intr_vec_ = icu_mgr::set_interrupt(TMR::CMIA_VEC, match_task_, level);
				TMR::TCR.CMIEA = 1;
			}

// utils::format("Shift: %u\n") % static_cast<uint16_t>(shift);
// utils::format("Match: %u\n") % match;

			static constexpr uint8_t cks[] = {
				0b000,  // shift:0   PCLK/1
				0b001,  // shift:1,  PCLK/2
				0b010,  // shift:2,  PCLK/4    NS (PCLK/8)
				0b010,  // shift:3,  PCLK/8
				0b011,  // shift:4,  PCLK/16   NS (PCLK/32)
				0b011,  // shift:5,  PCLK/32
				0b100,  // shift:6,  PCLK/64
				0b101,  // shift:7,  PCLK/128  NS (PCLK/1024)
				0b101,  // shift:8,  PCLK/256  NS (PCLK/1024)
				0b101,  // shift:9,  PCLK/512  NS (PCLK/1024)
				0b101,  // shift:10, PCLK/1024
				0b110,  // shift:11, PCLK/2048 NS (PCLK/8192)
				0b110,  // shift:12, PCLK/4096 NS (PCLK/8192)
				0b110,  // shift:13, PCLK/8192
			};
			// 16 ビットカウンタモード（カウント開始）
			if(TMR::PERIPHERAL == device::peripheral::TMR0) {
				device::TMR1::TCCR.CKS = cks[shift];
			} else {
				device::TMR3::TCCR.CKS = cks[shift];
			}
			TMR::TCCR.CSS = 0b11;
			if(TMR::PERIPHERAL == device::peripheral::TMR0) {
				device::TMR1::TCCR.CSS = 0b01;
			} else {
				device::TMR3::TCCR.CSS = 0b01;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	周期を取得
			@param[in]	real	「true」にした場合、実際の値
			@return 周期
		 */
		//-----------------------------------------------------------------//
		uint32_t get_rate(bool real = false) noexcept
		{
			if(real) {
				uint32_t rate = (TMR::PCLK >> shift_) / (TMR::TCORA16() + 1);
				return rate;
			} else {
				return freq_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターの取得
			@return 割り込みベクター
		*/
		//-----------------------------------------------------------------//
		auto get_intr_vec() const noexcept { return intr_vec_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  TASK クラスの参照
			@return TASK クラス
		*/
		//-----------------------------------------------------------------//
		static auto& at_task() noexcept { return task_; }
	};
	template <class TMR, class TASK> TASK tmr_mgr<TMR, TASK>::task_;
}
