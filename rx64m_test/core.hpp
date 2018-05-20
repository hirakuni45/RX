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
#include "common/tpu_io.hpp"
#include "common/fifo.hpp"
#include "common/sci_io.hpp"
#ifdef WATCH_DOG
#include "common/wdt_man.hpp"
#endif

namespace seeda {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  コア・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct core {

		class timer_task {

			volatile unsigned long millis_;
			volatile unsigned long delay_;

		public:
			timer_task() : millis_(0), delay_(0) { }

			volatile unsigned long get_millis() const { return millis_; }

			volatile unsigned long get_delay() const { return delay_; }

			void set_delay(volatile unsigned long n) { delay_ = n; }

			void operator() ()
			{
// LED::P = !LED::P();
// LED::P = 1;
				eadc_server();

				++millis_;

				if(delay_ != 0) {
					--delay_;
				}
// LED::P = 0;
			}
		};

		typedef device::tpu_io<device::TPU0, timer_task> TPU0;
		TPU0		tpu0_;

		class cmt_task {

			void (*task_10ms_)();

			volatile uint32_t millis10x_;
#ifdef WATCH_DOG
			utils::wdt_man<device::WDT> wdt_man_;

			volatile uint32_t	wdt_count_;
			volatile uint32_t	wdt_limit_;
			volatile bool		wdt_enable_;
			volatile bool		wdt_stop_;
#endif
		public:
			cmt_task() : task_10ms_(nullptr),
				millis10x_(0)
#ifdef WATCH_DOG
				, wdt_man_(), wdt_count_(0), wdt_limit_(10 * 60 * 100), wdt_enable_(false), wdt_stop_(false)
#endif
				{ }

			void set_task_10ms(void (*task)(void)) {
				task_10ms_ = task;
			}

			void sync()
			{
				volatile uint32_t tmp = millis10x_;
				while(tmp == millis10x_) ;
			}

#ifdef WATCH_DOG
			void start_wdt() { wdt_man_.start(); }

			void clear_wdt() { wdt_count_ = 0; }

			void stop_wdt(bool stop = true) { wdt_stop_ = stop; }

			void enable_wdt(bool ena = true) { wdt_enable_ = ena; }

			void limit_wdt(uint32_t lim) { wdt_limit_ = lim; }
#endif
			void operator() ()
			{
#ifdef WATCH_DOG
				if(wdt_stop_) {
					// リフレッシュが止まり、強制リセット
				} else if(wdt_enable_) {
					++wdt_count_;
					if(wdt_count_ < wdt_limit_) {
						wdt_man_.refresh();
					}
				} else {
					// WDT 無効： 常にリフレッシュ
					wdt_man_.refresh();
				}
#endif
				if(task_10ms_ != nullptr) (*task_10ms_)();
				++millis10x_;
			}
		};

		typedef device::cmt_io<device::CMT0, cmt_task> CMT0;
		CMT0		cmt0_;

		typedef utils::fifo<uint8_t, 1024> BUFFER;
#ifdef SEEDA
		typedef device::sci_io<device::SCI12, BUFFER, BUFFER> SCI;
#else
		typedef device::sci_io<device::SCI7, BUFFER, BUFFER> SCI;
#endif
		SCI			sci_;

		typedef device::S12AD ADC;
		typedef device::adc_io<ADC, utils::null_task> ADC_IO;
		ADC_IO		adc_io_;

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
			{  // SCI 設定
				uint8_t int_level = 1;
				sci_.start(115200, int_level);
			}

			{  // タイマー設定、１００Ｈｚ（１０ｍｓ）
				uint8_t int_level = 5;
				cmt0_.start(100, int_level);
#ifdef WATCH_DOG
				cmt0_.at_task().start_wdt();
#endif
			}

			{  // タイマー設定、１０００Ｈｚ（１ｍｓ）
				uint8_t int_level = 6;
				if(!tpu0_.start(1000, int_level)) {
					utils::format("TPU0 not start ...\n");
				}
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
			utils::format("Endian: %3b (%s)")
				% static_cast<uint32_t>(mde) % (mde == 0b111 ? "Little" : "Big");
			utils::format(", PCLKA: %u [Hz]") % static_cast<uint32_t>(F_PCLKA);
			utils::format(", PCLKB: %u [Hz]\n") % static_cast<uint32_t>(F_PCLKB);
			static const char* vdsel[4] = { "---", "2.94V", "2.87V", "2.80V" };
			utils::format("OFS1: VDSEL: %s, LVDAS: %s, HOCOEN: %s\n")
				% vdsel[device::SYSTEM::OFS1.VDSEL()]
				% (device::SYSTEM::OFS1.LVDAS() ? "Disable" : "Enable")
				% (device::SYSTEM::OFS1.HOCOEN() ? "Disable" : "Enable");
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
			cmt0_.at_task().sync();
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

#ifdef WATCH_DOG
		//-----------------------------------------------------------------//
		/*!
			@brief  ウオッチ・ドッグをクリア
		*/
		//-----------------------------------------------------------------//
		void clear_wdt()
		{
			cmt0_.at_task().clear_wdt();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ウオッチ・ドッグ、リフレッシュを停止 @n
					※強制リセット
		*/
		//-----------------------------------------------------------------//
		void stop_wdt()
		{
			cmt0_.at_task().stop_wdt();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ウオッチ・ドッグを許可
			@param[in]	ena	「false」の場合無効
		*/
		//-----------------------------------------------------------------//
		void enable_wdt(bool ena = true)
		{
			cmt0_.at_task().enable_wdt(ena);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ウオッチ・ドッグ制限時間の設定
			@param[in]	lim	制限時間「ミリ秒」
		*/
		//-----------------------------------------------------------------//
		void limit_wdt(uint32_t lim)
		{
			cmt0_.at_task().limit_wdt(lim);
		}
#endif
	};
}
