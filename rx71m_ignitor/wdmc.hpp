#pragma once
//=====================================================================//
/*! @file
    @brief  RX71M イグナイター WDM クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "main.hpp"

#define W24_MODE

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  WDM class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class wdmc {

		// WDM interface (RSPI, SECOND)
		typedef device::PORT<device::PORTA, device::bitpos::B4> WDM_SEL;
		typedef device::rspi_io<device::RSPI, device::port_map::option::SECOND> WDM;
		WDM			wdm_;

		uint16_t output_(uint8_t a, uint8_t b, uint8_t c)
		{
			WDM_SEL::P = 0;
			uint16_t d;
#ifdef W24_MODE
			uint32_t out = a;
			out <<= 8;
			out |= b;
			out <<= 8;
			out |= c;
			d = wdm_.xchg32(out);
#else
			wdm_.xchg(a);
			d  = wdm_.xchg(b);
			d <<= 8;
			d |= wdm_.xchg(c);
#endif
			WDM_SEL::P = 1;
			return d;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		wdmc() : wdm_() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
		*/
		//-----------------------------------------------------------------//
		void start()
		{
			{
			// RSPI (for WDM) 2.5M bps
			// ※RS-422 ドライバーの遅延が３５ｎｓくらいあるので、高ビット
			// レートは難しい・・・
#ifdef W24_MODE
//				wdm_.start(7500000, WDM::PHASE::TYPE1, WDM::DLEN::W24);
				wdm_.start(2000000, WDM::PHASE::TYPE1, WDM::DLEN::W24);
#else
				wdm_.start(2000000, WDM::PHASE::TYPE1, WDM::DLEN::W8);
#endif
				WDM_SEL::DIR = 1;  // select output;
			}
//  RSPI test
#if 0
			while(1) {
				get_status();
			}
#endif
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ステータスの取得
			@return ステータス
		*/
		//-----------------------------------------------------------------//
		uint16_t get_status()
		{
#ifdef W24_MODE
			WDM_SEL::P = 0;
			auto st = wdm_.xchg32(0x800000);
			WDM_SEL::P = 1;
			return st;
#else
			WDM_SEL::P = 0;
			wdm_.xchg(0x80);
			uint16_t st1 = wdm_.xchg(0);
			uint16_t st2 = wdm_.xchg(0);
			WDM_SEL::P = 1;
			return (st1 << 8) | st2;
#endif
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  出力
			@param[in]	cmd		２４ビットのデータ出力
		*/
		//-----------------------------------------------------------------//
		void output(uint32_t cmd)
		{
			utils::format("%08X\n") % cmd;
#ifdef W24_MODE
			WDM_SEL::P = 0;
			wdm_.xchg32(cmd);
#else
			wdm_.xchg((cmd >> 16) & 0xff);
			wdm_.xchg((cmd >> 8) & 0xff);
			wdm_.xchg(cmd & 0xff);
#endif
			WDM_SEL::P = 1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  波形の取得
			@param[in]	ch		チャネル（１、２、３、４）
			@param[in]	pos		波形位置
			@return 波形
		*/
		//-----------------------------------------------------------------//
		void set_wave_pos(uint32_t ch, int32_t pos)
		{
			output_(0b00110000 | ch, 0b10001000 | ((pos >> 8) & 0x7), pos & 0xff);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  波形の取得
			@param[in]	ch		チャネル（１、２、３、４）
			@return 波形
		*/
		//-----------------------------------------------------------------//
		uint16_t get_wave(uint32_t ch)
		{
			return output_(0b10000000 | ch, 0, 0);
		}
	};
}
