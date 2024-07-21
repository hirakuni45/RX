#pragma once
//=========================================================================//
/*!	@file
	@brief	RX63N/RX631 グループ・ボード・プロファイル @n
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
				RX631 GR-CITRUS
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

	// RX631 GR-CITRUS board シグネチュア
	static const char system_str_[] = "RX631 GR-CITRUS";

	/// LED インジケーター	
	static constexpr bool LED_ACTIVE = 1;
	typedef device::PORT<device::PORTA, device::bitpos::B0, LED_ACTIVE> LED;

	// SCI ポートの定義
	typedef device::SCI1 SCI_CH;
	static constexpr auto SCI_ORDER = device::port_map::ORDER::SECOND;

	// インターバル・タイマーの定義
	typedef device::CMT0 CMT_CH;

	// RIIC ポートの定義
	typedef device::RIIC0 RIIC_CH;

	// CAN ポートの定義
	typedef device::CAN0 CAN0_CH;
	static constexpr auto CAN0_PORT = device::port_map::ORDER::FIRST;
}
