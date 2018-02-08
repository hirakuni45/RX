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

		uint32_t	ch_;
		int32_t		pos_;

		uint16_t output_(uint8_t a, uint8_t b, uint8_t c)
		{
			uint16_t d;
			WDM_SEL::P = 0;
			wdm_.xchg(a);
			d  = wdm_.xchg(b);
			d <<= 8;
			d |= wdm_.xchg(c);
			WDM_SEL::P = 1;
			return d;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		wdmc() : wdm_(), ch_(0), pos_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
		*/
		//-----------------------------------------------------------------//
		void start()
		{
			{  // RSPI (for WDM) 7.5M bps
				wdm_.start(7500000, WDM::PHASE::TYPE1, WDM::DLEN::W8);
				WDM_SEL::DIR = 1;  // select output;
			}
//  RSPI test
#if 0
			while(1) {
				WDM_SEL::P = !WDM_SEL::P();
				wdm_.xchg(0xaa);
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
			WDM_SEL::P = 0;
			wdm_.xchg(0x80);
			uint16_t st1 = wdm_.xchg(0);
			uint16_t st2 = wdm_.xchg(0);
			WDM_SEL::P = 1;
			return (st1 << 8) | st2;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  出力
			@param[in]	cmd		２４ビットのデータ出力
		*/
		//-----------------------------------------------------------------//
		void output(uint32_t cmd)
		{
			WDM_SEL::P = 0;
			wdm_.xchg((cmd >> 16) & 0xff);
			wdm_.xchg((cmd >> 8) & 0xff);
			wdm_.xchg(cmd & 0xff);
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
		uint16_t get_wave(uint32_t ch, int32_t pos)
		{
			if(pos != pos_ || ch != ch_) {
				pos_ = pos;
				ch_ = ch;
				output_(0b00110000 | ch, 0b10001000 | ((pos >> 8) & 0x7), pos & 0xff);
			}

			auto data = output_(0b10000000 | ch, 0, 0);
			++pos_;
			return data;
		}
	};
}
