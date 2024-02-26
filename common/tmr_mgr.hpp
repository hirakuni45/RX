#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600 グループ・TMR マネージャー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"
#include "common/intr_utils.hpp"
#include "common/vect.h"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  TMR マネージャー・クラス @
				※１６ビット・モードで利用する場合、TMR は、TMR0、又は、TMR2 を指定する事
		@param[in]	TMR		TMR チャネルクラス
		@param[in]	FUNC	タイマー動作ファンクタ・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class TMR, class FUNC = utils::null_task>
	class tmr_mgr {
	public:

		typedef TMR tmr_type;	///< TMR チャネル・クラス型
	
	private:

		static inline uint32_t counter_;
		static inline FUNC func_;

		uint32_t		freq_;
		uint8_t			shift_;


		void sleep_() const { asm("nop"); }


		static INTERRUPT_FUNC void match_task_()
		{
			++counter_;
			func_();
		}


		static constexpr bool calc_freq_(uint32_t freq, uint8_t& shift, uint32_t& match) noexcept
		{
			match = TMR::PCLK / freq;
			shift = 0;
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

			return true;
		}


		static constexpr uint32_t get_real_freq_(uint8_t shift, uint32_t match)
		{
			uint32_t rate = (TMR::PCLK >> shift) / match;
			return rate;
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		tmr_mgr() noexcept : freq_(0), shift_(0) 
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	設定周波数の誤差を検証
			@param[in]	freq	周波数
			@param[in]	thper	許容誤差（通常 1.0%） @n
								百分率を 10 倍した値を設定
			@return 誤差範囲なら「true」
		 */
		//-----------------------------------------------------------------//
		static constexpr bool probe_freq(uint32_t freq, uint32_t thper = 10) noexcept
		{
			uint8_t shift = 0;
			uint32_t match = 0;
			if(!calc_freq_(freq, shift, match)) {
				return false;
			}

			auto rate = get_real_freq_(shift, match);
			auto d = freq * thper;
			if((rate * 1000) < (freq * 1000 - d) || (freq * 1000 + d) < (rate * 1000)) {
				return false;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  開始（１６ビットインターバルタイマー）
			@param[in]	freq	タイマー周波数
			@param[in]	level	割り込みレベル（NONE ならポーリング）
			@return タイマー周波数が範囲を超えた場合「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t freq, ICU::LEVEL level = ICU::LEVEL::NONE) noexcept
		{
			// 16 bits バインドモードでは、TMR0、TMR2 以外はエラー
			static_assert(TMR::BIND16, "The TMR peripheral specifies TMR0 or TMR2.");

			uint32_t match = 0;
			uint8_t shift = 0;
			if(!calc_freq_(freq, shift, match)) {
				return false;
			}

			if(!device::power_mgr::turn(TMR::PERIPHERAL)) {
				return false;
			}

			shift_ = shift;
			freq_ = freq;

			TMR::TCCR = 0;
			if(TMR::BIND16) {
				device::TMR1::TCCR = 0;
			} else {
				device::TMR3::TCCR = 0;
			}

			counter_ = 0;
			TMR::TCR.CCLR = 0b01;  // CMP Match-A
			TMR::TCNT16 = 0;
			TMR::TCORA16 = match - 1;

			if(level != ICU::LEVEL::NONE) {
				icu_mgr::set_interrupt(TMR::CMIA, match_task_, level);
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
			if(TMR::BIND16) {
				device::TMR1::TCCR.CKS = cks[shift];
			} else {
				device::TMR3::TCCR.CKS = cks[shift];
			}
			TMR::TCCR.CSS = 0b11;
			if(TMR::BIND16) {
				device::TMR1::TCCR.CSS = 0b01;
			} else {
				device::TMR3::TCCR.CSS = 0b01;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みと同期
		*/
		//-----------------------------------------------------------------//
		void sync() const noexcept
		{
			if(icu_mgr::get_level(TMR::CMIA) != ICU::LEVEL::NONE) {
				volatile uint32_t cnt = counter_;
				while(cnt == counter_) sleep_();
			} else {
				auto ref = TMR::TCNT16();
				while(ref <= TMR::TCNT16()) sleep_();
				func_();
				++counter_;
			}
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
		auto get_intr_vec() const noexcept { return TMR::CMIA; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ファンクタ・クラスの参照
			@return ファンクタ・クラス
		*/
		//-----------------------------------------------------------------//
		static auto& at_func() noexcept { return func_; }
	};
}
