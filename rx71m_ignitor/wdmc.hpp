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
		WDM		wdm_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		wdmc() { }


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

	};
}
