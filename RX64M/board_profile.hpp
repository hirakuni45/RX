#pragma once
//=========================================================================//
/*!	@file
	@brief	RX64M グループ・ボード・プロファイル @n
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
				DIY RX64M board
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	// GR-KAEDE の場合有効にする。
//	#define GR_KAEDE

#ifdef GR_KAEDE
	// 基板シグネチュア
	static constexpr char system_str_[] = "RX64M GR-KAEDE";

	/// LED インジケーター
	typedef device::PORT<device::PORT0, device::bitpos::B3> LED;
//	typedef device::PORT<device::PORT0, device::bitpos::B2> LED1;
	typedef device::PORT<device::PORTC, device::bitpos::B0> LED2;
//	typedef device::PORT<device::PORTC, device::bitpos::B1> LED3;

	// SCI ポートの定義
	typedef device::SCI7 SCI_CH;
	static constexpr auto SCI_ORDER = device::port_map::ORDER::FIRST;
#else
	// 基板シグネチュア
	static constexpr char system_str_[] = "RX64M DIY";

	/// LED インジケーター
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B7, LED_ACTIVE> LED;

	// SCI ポートの定義
	typedef device::SCI1 SCI_CH;
	static constexpr auto SCI_ORDER = device::port_map::ORDER::THIRD;
#endif

	// インターバル・タイマーの定義
	typedef device::CMT0 CMT_CH;

	// RIIC ポートの定義
	typedef device::RIIC0 RIIC_CH;

	// CAN ポートの定義
	typedef device::CAN0 CAN0_CH;
	typedef device::CAN1 CAN1_CH;
	static constexpr auto CAN0_PORT = device::port_map::ORDER::FIRST;
	static constexpr auto CAN1_PORT = device::port_map::ORDER::FIRST;

}
