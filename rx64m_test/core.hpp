#pragma once
//=====================================================================//
/*! @file
    @brief  SEEDA03 (RX64M) コア @n
			Copyright 2017 Kunihito Hiramatsu
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

		static const int seeda_version_ = 17;
		static const uint32_t build_id_ = B_ID;

		class cmt_task {
			volatile unsigned long millis_;
			volatile unsigned long delay_;
			volatile uint32_t millis10x_;
			volatile uint32_t cmtdiv_;

		public:
			cmt_task() : millis_(0), delay_(0), millis10x_(0), cmtdiv_(0) { }

			void operator() () {
				++millis_;
				++cmtdiv_;
				if(cmtdiv_ >= 10) {
					cmtdiv_ = 0;
					++millis10x_;
				}
				if(delay_) {
					--delay_;
				}
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

		typedef utils::fifo<uint8_t, 1024> BUFFER;
		typedef device::sci_io<device::SCI5, BUFFER, BUFFER> SCI;
		SCI		sci_;

		typedef device::PORT<device::PORT6, device::bitpos::B7> SW1;
		typedef device::PORT<device::PORT6, device::bitpos::B6> SW2;

		uint8_t get_switch_()
		{
			return static_cast<uint8_t>(!SW1::P()) | (static_cast<uint8_t>(!SW2::P()) << 1);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		core() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  初期化
		*/
		//-----------------------------------------------------------------//
		void init()
		{
			{  // DIP-SW プルアップ
				SW1::DIR = 0;  // input
				SW2::DIR = 0;  // input
				SW1::PU = 1;
				SW2::PU = 1;
			}

			{  // タイマー設定、１０００Ｈｚ（１ｍｓ）
				uint8_t int_level = 1;
				cmt0_.start(1000, int_level);
			}

			{  // SCI 設定
				uint8_t int_level = 2;
				sci_.start(115200, int_level);
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
			utils::format("\nStart Seeda03 Build: %u Version %d.%02d\n") % build_id_
				% (seeda_version_ / 100) % (seeda_version_ % 100);
			uint8_t mde = device::SYSTEM::MDE.MDE();
			utils::format("Endian: %3b (%s)") % static_cast<uint32_t>(mde) % (mde == 0b111 ? "Little" : "Big");
			utils::format(", PCKA: %u [Hz]") % static_cast<uint32_t>(F_PCKA);
			utils::format(", PCKB: %u [Hz]\n") % static_cast<uint32_t>(F_PCKB);
			utils::format("DIP-Switch: %d\n") % static_cast<int>(get_switch_());
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
		}		
	};
}
