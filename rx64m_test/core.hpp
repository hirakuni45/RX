#pragma once
//=====================================================================//
/*! @file
    @brief  SEEDA03 (RX64M) コア
	@copyright Copyright 2017 Kunihito Hiramatsu All Right Reserved.
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "main.hpp"

#include "common/cmt_io.hpp"
#include "common/fifo.hpp"
#include "common/sci_io.hpp"

namespace seeda {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  コア・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct core {

		class cmt_task {
			void (*task_10ms_)();

			volatile unsigned long millis_;
			volatile unsigned long delay_;
			volatile uint32_t millis10x_;
			volatile uint32_t cmtdiv_;

		public:
			cmt_task() : task_10ms_(nullptr),
				millis_(0), delay_(0), millis10x_(0), cmtdiv_(0) { }

			void operator() () {

				eadc_server();

				++millis_;
				++cmtdiv_;
				if(cmtdiv_ >= 10) {
					if(task_10ms_ != nullptr) (*task_10ms_)();
					cmtdiv_ = 0;
					++millis10x_;
				}
				if(delay_) {
					--delay_;
				}
				
			}

			void set_task_10ms(void (*task)(void)) {
				task_10ms_ = task;
			}

			void sync_100hz()
			{
				volatile uint32_t tmp = millis10x_;
				while(tmp == millis10x_) ;
			}

			volatile unsigned long get_millis() const { return millis_; }

			volatile unsigned long get_delay() const { return delay_; }

			void set_delay(volatile unsigned long n) { delay_ = n; }
		};

		typedef device::cmt_io<device::CMT0, cmt_task> CMT0;
		CMT0	cmt0_;

		typedef utils::fifo<uint8_t, 2048> BUFFER;
#ifdef SEEDA
		typedef device::sci_io<device::SCI12, BUFFER, BUFFER> SCI;
#else
		typedef device::sci_io<device::SCI7, BUFFER, BUFFER> SCI;
#endif
		SCI		sci_;

		// 内臓 A/D 変換 タスク
		struct adc_task {
			void operator () () {
			}
		};

		typedef device::S12AD ADC;
		typedef device::adc_io<ADC, adc_task> ADC_IO;
		ADC_IO	adc_io_;

		uint32_t	list_cnt_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		core() : list_cnt_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  初期化
		*/
		//-----------------------------------------------------------------//
		void init()
		{
#ifdef SEEDA
			{  // DIP-SW プルアップ
				SW1::DIR = 0;  // input
				SW2::DIR = 0;  // input
				SW1::PU = 1;
				SW2::PU = 1;
			}
#endif
			{  // タイマー設定、１０００Ｈｚ（１ｍｓ）
				uint8_t int_level = 5;
				cmt0_.start(1000, int_level);
			}

			{  // SCI 設定
				uint8_t int_level = 1;
				sci_.start(115200, int_level);
			}

			{  // 内臓 A/D 変換設定
				uint8_t intr_level = 0;
				adc_io_.start(ADC::analog::AIN005, intr_level);
				adc_io_.start(ADC::analog::AIN006, intr_level);
				adc_io_.start(ADC::analog::AIN007, intr_level);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  初期化
		*/
		//-----------------------------------------------------------------//
		void title()
		{
			// タイトル・コール
#ifdef SEEDA
			utils::format("\nStart Seeda03 Build: %u Version %d.%02d\n") % build_id_
				% (seeda_version_ / 100) % (seeda_version_ % 100);
#else
			utils::format("\nStart GR-KAEDE Build: %u\n") % build_id_;
#endif
			uint8_t mde = device::SYSTEM::MDE.MDE();
			utils::format("Endian: %3b (%s)") % static_cast<uint32_t>(mde) % (mde == 0b111 ? "Little" : "Big");
			utils::format(", PCLKA: %u [Hz]") % static_cast<uint32_t>(F_PCLKA);
			utils::format(", PCLKB: %u [Hz]\n") % static_cast<uint32_t>(F_PCLKB);
			utils::format("DIP-Switch-2 (Dev): %s\n") % (get_develope() ? "Enable" : "Disable");
			utils::format("DIP-Switch-1 (CH):  %d\n") % get_channel_num();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス同期
		*/
		//-----------------------------------------------------------------//
		void sync()
		{
			cmt0_.at_task().sync_100hz();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//-----------------------------------------------------------------//
		void service()
		{
#if 0
			++list_cnt_;
			if(list_cnt_ >= 100) {
				auto val = adc_io_.get(ADC::analog::AIN005);
				utils::format("AIN005: %d\n") % static_cast<int>(val);
				list_cnt_ = 0;
			}
#endif
			adc_io_.scan();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値の取得
			@param[in]	ch	チャネル（５、６、７）
			@return A/D 変換値
		*/
		//-----------------------------------------------------------------//
		uint16_t get_adc(uint32_t ch) const {
			return adc_io_.get(static_cast<ADC::analog>(ch));
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマークラスのカウンター値の取得（１ｍｓ）
			@return カウンター値
		*/
		//-----------------------------------------------------------------//
		uint32_t get_cmt_counter() const {
			return cmt0_.get_counter();
		}
	};
}
