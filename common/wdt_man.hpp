#pragma once
//=====================================================================//
/*!	@file
	@brief	WDT マネージャー・テンプレート
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

/// F_PCLKB はパラメーター計算で必要で、設定が無いとエラーにします。
#ifndef F_PCLKB
#  error "wdt_io.hpp requires F_PCLKB to be defined"
#endif

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	WDT マネージャー・クラス
		@param[in]	WDT	 ウォッチ・ドッグ・タイマー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class WDT>
	class wdt_man {

		bool	start_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		wdt_man() : start_(false) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	WDT 開始
		*/
		//-----------------------------------------------------------------//
		void start()
		{
			// 60MHz 35ms 以内にリフレッシュ
			// PCLK/512, 4096 cycle
			WDT::WDTCR = WDT::WDTCR.RPES.b(0b11) | WDT::WDTCR.RPSS.b(0b11) |
				WDT::WDTCR.TOPS.b(0b10) | WDT::WDTCR.CKS.b(0b0110);

			start_ = true;
			refresh();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	リフレッシュ（ダウンカウンタ再設定）
		*/
		//-----------------------------------------------------------------//
		void refresh()
		{
			if(start_) {
				WDT::WDTRR = 0x00;
				WDT::WDTRR = 0xFF;
			}
		}
	};
}
