#pragma once
//=========================================================================//
/*!	@file
	@brief	RX62N/RX621 グループ・ボード・プロファイル @n
            基板の基本的な定義 @n
			- LED port order @n
			- SCI channel, port_map order @n
			- CMT channel @n
			- RIIC channel @n
			- CAN channel
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
				- FRK-RX62N(CQ 出版社) @n
				- BlueBoard-RX62N_100pin
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
  #if defined(CQ_FRK)
    // FRK-RX62N(CQ 出版社) 基板シグネチュア
	static const char system_str_[] = "RX62N FRK-RX62N";

	/// LED インジケーター
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT1, device::bitpos::B5, LED_ACTIVE> LED;

	// SCI ポートの定義
	typedef device::SCI1 SCI_CH;
	static constexpr auto SCI_ORDER = device::port_map::ORDER::FIRST;
  #else
    // BlueBoard-RX62N_100pin 基板シグネチュア
	static const char system_str_[] = "RX62N BlueBoard-RX62N_100pin";

	/// LED インジケーター
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B5, LED_ACTIVE> LED;
  
  	// SCI ポートの定義
	typedef device::SCI1 SCI_CH;
	static constexpr auto SCI_ORDER = device::port_map::ORDER::FIRST;
  #endif

	// インターバル・タイマーの定義
	typedef device::CMT0 CMT_CH;

	// RIIC ポートの定義
	typedef device::RIIC0 RIIC_CH;

	// CAN ポートの定義
	typedef device::CAN CAN0_CH;
	static constexpr auto CAN0_PORT = device::port_map::ORDER::FIRST;
}
