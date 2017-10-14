#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M グループ・ポート・マッピング @n
			・ペリフェラル型に従って、ポートの設定をグループ化 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX600/port.hpp"
#include "RX64M/mpc.hpp"
#include "RX64M/peripheral.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map {

		static bool sub_(peripheral t, bool enable) {
			bool ret = true;
			switch(t) {
			// ※シリアルポートの MPC 設定では、PDR を制御する必要は無いが、
			// 出力ポートのインピーダンス制御の一環として入れてある。
			case peripheral::SCI0:
				{
					uint8_t sel = enable ? 0b001010 : 0;
					PORT2::PDR.B0 = enable; // TXD0
					PORT2::PDR.B1 = 0;  	// RXD0
					MPC::P20PFS.PSEL = sel;
					MPC::P21PFS.PSEL = sel;
					PORT2::PMR.B0 = enable;
					PORT2::PMR.B1 = enable;
				}
				break;
			case peripheral::SCI1:
				{
					uint8_t sel = enable ? 0b001010 : 0;
					PORTF::PDR.B0 = enable; // TXD1
					PORTF::PDR.B2 = 0;  	// RXD1
					MPC::PF0PFS.PSEL = sel;
					MPC::PF2PFS.PSEL = sel;
					PORTF::PMR.B0 = enable;
					PORTF::PMR.B2 = enable;
				}
				break;
			case peripheral::SCI2:
				{
					uint8_t sel = enable ? 0b001010 : 0;
					PORT1::PDR.B3 = enable; // TXD2
					PORT1::PDR.B2 = 0;  	// RXD2
					MPC::P13PFS.PSEL = sel;
					MPC::P12PFS.PSEL = sel;
					PORT1::PMR.B3 = enable;
					PORT1::PMR.B2 = enable;
				}
				break;
			case peripheral::SCI3:
				{
					uint8_t sel = enable ? 0b001010 : 0;
					PORT2::PDR.B3 = enable; // TXD3
					PORT2::PDR.B5 = 0;  	// RXD3
					MPC::P23PFS.PSEL = sel;
					MPC::P25PFS.PSEL = sel;
					PORT2::PMR.B3 = enable;
					PORT2::PMR.B5 = enable;
				}
				break;
			case peripheral::SCI4:
				{
					uint8_t sel = enable ? 0b001010 : 0;
					PORTB::PDR.B1 = enable; // TXD4
					PORTB::PDR.B0 = 0;  	// RXD4
					MPC::PB1PFS.PSEL = sel;
					MPC::PB0PFS.PSEL = sel;
					PORTB::PMR.B1 = enable;
					PORTB::PMR.B0 = enable;
				}
				break;
			case peripheral::SCI5:
				{
					uint8_t sel = enable ? 0b001010 : 0;
					PORTA::PDR.B4 = enable; // TXD5
					PORTA::PDR.B3 = 0;  	// RXD5
					MPC::PA4PFS.PSEL = sel;
					MPC::PA3PFS.PSEL = sel;
					PORTA::PMR.B4 = enable;
					PORTA::PMR.B3 = enable;
				}
				break;
			case peripheral::SCI6:
				{
					uint8_t sel = enable ? 0b001010 : 0;
					PORT0::PDR.B0 = enable; // TXD6
					PORT0::PDR.B1 = 0;  	// RXD6
					MPC::P00PFS.PSEL = sel;
					MPC::P01PFS.PSEL = sel;
					PORT0::PMR.B0 = enable;
					PORT0::PMR.B1 = enable;
				}
				break;
			case peripheral::SCI7:
				{
					uint8_t sel = enable ? 0b001010 : 0;
					PORT9::PDR.B0 = enable; // TXD7
					PORT9::PDR.B2 = 0;  	// RXD7
					MPC::P90PFS.PSEL = sel;
					MPC::P92PFS.PSEL = sel;
					PORT9::PMR.B0 = enable;
					PORT9::PMR.B2 = enable;
				}
				break;

			case peripheral::SCI12:
				{
					uint8_t sel = enable ? 0b001100 : 0;
					PORTE::PDR.B2 = enable; // TXD12
					PORTE::PDR.B1 = 0;  	// RXD12
					MPC::PE2PFS.PSEL = sel;
					MPC::PE1PFS.PSEL = sel;
					PORTE::PMR.B2 = enable;
					PORTE::PMR.B1 = enable;
				}
				break;

			case peripheral::RSPI:
				{
					uint8_t sel = enable ? 0b001101 : 0;
//					PORTC::PCR.B7 = 1;		// pull-up
//					PORTC::PDR.B7 = 0;		// MISOA
//					PORTC::PDR.B6 = 1;		// MOSIA
//					PORTC::PDR.B5 = 1;		// RSPCKA
					MPC::PC7PFS.PSEL = sel;  // MISOA
					MPC::PC6PFS.PSEL = sel;  // MOSIA
					MPC::PC5PFS.PSEL = sel;  // RSPCKA
					PORTC::PMR.B7 = enable;
					PORTC::PMR.B6 = enable;
					PORTC::PMR.B5 = enable;
				}
				break;

			case peripheral::SDHI:
				{
					uint8_t sel = enable ? 0b011010 : 0;
					MPC::P80PFS.PSEL = sel;  // SDHI_WP (81)
					PORT8::PMR.B0 = enable;
//					PORT8::PCR.B0 = 1;
					MPC::P81PFS.PSEL = sel;  // SDHI_CD (80)
					PORT8::PMR.B1 = enable;
//					PORT8::PCR.B1 = 1;
					MPC::PC2PFS.PSEL = sel;  // SDHI_D3 (86)
					PORTC::PMR.B2 = enable;
//					PORTC::PCR.B2 = 1;
					MPC::PC3PFS.PSEL = sel;  // SDHI_D0 (83)
					PORTC::PMR.B3 = enable;
//					PORTC::PCR.B3 = 1;
					MPC::PC4PFS.PSEL = sel;  // SDHI_D1 (82)
					PORTC::PMR.B4 = enable;
//					PORTC::PCR.B4 = 1;
   					MPC::P75PFS.PSEL = sel;  // SDHI_D2 (87)
					PORT7::PMR.B5 = enable;
//					PORT7::PCR.B5 = 1;
					MPC::P76PFS.PSEL = sel;  // SDHI_CMD (85)
					PORT7::PMR.B6 = enable;
//					PORT7::PCR.B6 = 1;
					MPC::P77PFS.PSEL = sel;  // SDHI_CLK (84)
					PORT7::PMR.B7 = enable;
//					PORT7::PCR.B7 = 1;
				}
				break;

			case peripheral::ETHERC0:  // only RMII mode, not use link status interrupt
				{
					uint8_t  mii = enable ? 0b010001 : 0;
					uint8_t rmii = enable ? 0b010010 : 0;
//					MPC::P34PFS.PSEL = mii;   // ET0_LINKSTA
//					PORT3::PMR.B4 = enable;
					MPC::P71PFS.PSEL = mii;   // ET0_MDIO
					MPC::P72PFS.PSEL = mii;   // ET0_MDC
//					MPC::P73PFS.PSEL = mii;   // ET0_WOL
					MPC::P74PFS.PSEL = rmii;  // RMII0_RXD1
					MPC::P75PFS.PSEL = rmii;  // RMII0_RXD0
					MPC::P76PFS.PSEL = rmii;  // REF50CK0
					MPC::P77PFS.PSEL = rmii;  // RMII0_RX_ER
					PORT7::PMR.B1 = enable;
					PORT7::PMR.B2 = enable;
//					PORT7::PMR.B3 = enable;
					PORT7::PMR.B4 = enable;
					PORT7::PMR.B5 = enable;
					PORT7::PMR.B6 = enable;
					PORT7::PMR.B7 = enable;
					MPC::P80PFS.PSEL = rmii;  // RMII0_TXD_EN
					MPC::P81PFS.PSEL = rmii;  // RMII0_TXD0
					MPC::P82PFS.PSEL = rmii;  // RMII0_TXD1
					MPC::P83PFS.PSEL = rmii;  // RMII0_CRS_DV
					PORT8::PMR.B0 = enable;
					PORT8::PMR.B1 = enable;
					PORT8::PMR.B2 = enable;
					PORT8::PMR.B3 = enable;
					MPC::PFENET.PHYMODE0 = 0;  // for RMII mode chanel 0
				}
				break;

			case peripheral::ETHERCA:  // only RMII mode, not use link status interrupt
				{
					uint8_t  mii = enable ? 0b010001 : 0;
					uint8_t rmii = enable ? 0b010010 : 0;
///					MPC::P73PFS.PSEL = mii;   // ET0_WOL  (144LQFP: 77)
					MPC::P72PFS.PSEL = mii;   // ET0_MDC  (144LQFP: 85)
					MPC::P71PFS.PSEL = mii;   // ET0_MDIO (144LQFP: 86)
///					PORT7::PMR.B3 = enable;
					PORT7::PMR.B2 = enable;
					PORT7::PMR.B1 = enable;
					MPC::PB7PFS.PSEL = rmii;  // RMII0_CRS_DV (144LQFP: 78)
					MPC::PB6PFS.PSEL = rmii;  // RMII0_TXD1   (144LQFP: 79)
					MPC::PB5PFS.PSEL = rmii;  // RMII0_TXD0   (144LQFP: 80)
					MPC::PB4PFS.PSEL = rmii;  // RMII0_TXD_EN (144LQFP: 81)
					MPC::PB3PFS.PSEL = rmii;  // RMII0_RX_ER  (144LQFP: 82)
					MPC::PB2PFS.PSEL = rmii;  // REF50CK0     (144LQFP: 83)
					MPC::PB1PFS.PSEL = rmii;  // RMII0_RXD0   (144LQFP: 84)
					MPC::PB0PFS.PSEL = rmii;  // RMII0_RXD1   (144LQFP: 87)
					PORTB::PMR.B7 = enable;
					PORTB::PMR.B6 = enable;
					PORTB::PMR.B5 = enable;
					PORTB::PMR.B4 = enable;
					PORTB::PMR.B3 = enable;
					PORTB::PMR.B2 = enable;
					PORTB::PMR.B1 = enable;
					PORTB::PMR.B0 = enable;
					MPC::PFENET.PHYMODE0 = 0;  // for RMII mode chanel 0
				}
				break;

			default:
				ret = false;
				break;
			}
			return ret;
		}

	public:

		//-----------------------------------------------------------------//
		/*!
			@brief  周辺機器に切り替える
			@param[in]	t	周辺機器タイプ
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral t, bool ena = true) noexcept
		{
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			auto ret = sub_(t, ena);

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  SDHI クロック端子のソフト制御
			@param[in]	t	周辺機器タイプ
			@param[in]	ena	SDHI のクロック端子にする場合「true」
			@param[in]	out	SDHI クロック出力設定
			@return 周辺機器型が異なる場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn_sdhi_clk(peripheral t, bool ena, bool out)
		{
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			if(t == peripheral::SDHI) {
				if(ena) {
					MPC::P77PFS.PSEL = 0b011010;  // enable SDHI_CLK
					PORT7::PMR.B7 = 1;
				} else {
					MPC::P77PFS.PSEL = 0;  		  // disable SDHI_CLK
					PORT7::PMR.B7 = 0;
					PORT7::PCR.B7 = 0;  // pullup offline
					PORT7::PDR.B7 = 1;  // output
					PORT7::PODR.B7 = out;
				}
				ret = true;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}

