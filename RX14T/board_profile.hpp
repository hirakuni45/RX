#pragma once
//=========================================================================//
/*!	@file
	@brief	RX14T board-profile / ボード・プロファイル @n
            ハードウェアの基本的な定義 @n
			- LED port order @n
			- SCI channel, port_map order @n
			- CMT channel
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2026 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace board_profile {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  基板プロファイル空間 @n
				- DIY RX14T board @n
				- Renesas FPB-RX14T
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

#if 0
	// 基板シグネチュア (RX14T DIY)
	static constexpr char system_str_[] = "RX14T DIY";

	/// LED インジケーター
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B0, LED_ACTIVE> LED;

#else
	// 基板シグネチュア (Renesas FPB-RX14T)
	static constexpr char system_str_[] = "Renesas FPB-RX14T";

	/// LED インジケーター (FPB-RX14T: P32, P92)
	static constexpr bool LED_ACTIVE = 1;
	typedef device::PORT<device::PORT3, device::bitpos::B2, LED_ACTIVE> LED;
	typedef device::PORT<device::PORT9, device::bitpos::B2, LED_ACTIVE> LED2;
#endif

	// SCI ポートの定義
	typedef device::SCI1 SCI_CH;
	static constexpr auto SCI_ORDER = device::port_map::ORDER::SECOND;

	// インターバル・タイマーの定義
	typedef device::CMT0 CMT_CH;

	// RIIC ポートの定義
	typedef device::RIIC0 RIIC_CH;
	
}
