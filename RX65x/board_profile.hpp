#pragma once
//=========================================================================//
/*!	@file
	@brief	RX65N/RX651 グループ・ボード・プロファイル @n
            基板の基本的な定義 @n
			- LED port order @n
			- SCI channel, port_map order @n
			- CMT channel
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace board_profile {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  基板プロファイル空間 @n
				Renesas RX65N Envision Kit				
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

	// 基板シグネチュア
	static const char system_str_[] = "RX65N Envision Kit";

	/// LED インジケーター
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT7, device::bitpos::B0, LED_ACTIVE> LED;

	// SCI ポートの定義
	typedef device::SCI9 SCI_CH;
	static constexpr auto SCI_ORDER = device::port_map::ORDER::FIRST;

	// インターバル・タイマーの定義
	typedef device::CMT0 CMT_CH;

	// RIIC ポートの定義
	typedef device::RIIC0 RIIC_CH;

	// QSPI ポートの定義
	static constexpr auto QSPI_PORT = device::port_map_order::RX65N_ENVISION_KIT::QSPI;

	// SDHI 定義
    typedef device::PORT<device::PORT6, device::bitpos::B4, 0> SDC_POWER;	///< '0'でＯＮ
    typedef device::NULL_PORT SDC_WP;		///< 書き込み禁止は使わない
    // RX65N Envision Kit の SDHI ポートは、候補３で指定できる
    static constexpr auto SDHI_ORDER = device::port_map::ORDER::THIRD;

	// GLCDC, touch panel 定義
	typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;
	static constexpr auto LCD_ORG = reinterpret_cast<uint16_t*>(0x0000'0100);
	typedef device::PORT<device::PORT0, device::bitpos::B7> FT5206_RESET;
	typedef device::SCI6 FT5206_SCI_CH;
	static constexpr auto FT5206_SCI_ORDER = device::port_map::ORDER::FIRST;
}
