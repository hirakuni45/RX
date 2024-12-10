#pragma once
//=========================================================================//
/*!	@file
	@brief	RX72N グループ・ボード・プロファイル @n
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
				Renesas RX72N Envision Kit				
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

	// 基板シグネチュア
	static const char system_str_[] = "RX72N Envision Kit";

	/// LED インジケーター
	// Renesas RX72N Envision Kit
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT4, device::bitpos::B0, LED_ACTIVE> LED;

	// SCI ポートの定義
	typedef device::SCI2 SCI_CH;
	static constexpr auto SCI_ORDER = device::port_map::ORDER::FIRST;

	// インターバル・タイマーの定義
	typedef device::CMT0 CMT_CH;

	// RIIC ポートの定義
	typedef device::RIIC0 RIIC_CH;

	// CAN ポートの定義
	typedef device::CAN1 CAN0_CH;
	static constexpr auto CAN0_PORT = device::port_map::ORDER::SECOND;

	// QSPI ポートの定義
	static constexpr auto QSPI_PORT = device::port_map_order::RX72N_ENVISION_KIT::_;

	// MTU ポートの定義
	// Pmod2 (8): PD1_RESET (MTIOC4B)
	typedef device::MTU4 MTU_CH;
	static constexpr auto MTU_ORDER = device::port_map_mtu::ORDER::FIFTH;

	// SDHI 定義
	typedef device::PORT<device::PORT4, device::bitpos::B2> SDC_POWER;	///< '1'でＯＮ
	typedef device::NULL_PORT SDC_WP;	///< カード書き込み禁止ポート設定
    // RX72N Envision Kit の SDHI ポートは、候補３で指定できる
	static constexpr auto SDHI_ORDER = device::port_map::ORDER::THIRD;

	// GLCDC, touch panel 定義
	typedef device::PORT<device::PORTB, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B7> LCD_LIGHT;
	static constexpr uint32_t LCD_ORG = 0x0080'0000;
	typedef device::PORT<device::PORT6, device::bitpos::B6> FT5206_RESET;
	typedef device::SCI6 FT5206_SCI_CH;
	static constexpr auto FT5206_SCI_ORDER = device::port_map::ORDER::SECOND;

	// Ethernet ハードウェアー定義 (ET0_RMII)
	static constexpr device::port_map_order::ether_mii_t ETHER0(device::port_map_order::RX72N_ENVISION_KIT _);
}
