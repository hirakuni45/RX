#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M グループ・ポート・マッピング @n
			Copyright 2016, 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
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

		static void sub_(peripheral t, bool enable) {
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
					PORTA::PDR.B2 = 0;  	// RXD5
					MPC::PA4PFS.PSEL = sel;
					MPC::PA2PFS.PSEL = sel;
					PORTA::PMR.B4 = enable;
					PORTA::PMR.B2 = enable;
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

			case peripheral::RSPI:
				{
					uint8_t sel = enable ? 0b001101 : 0;
					MPC::PC7PFS.PSEL = sel;  // PC7/MISOA
					MPC::PC6PFS.PSEL = sel;  // PC6/MOSIA
					MPC::PC5PFS.PSEL = sel;  // PC5/RSPCKA
					PORTC::PMR.B7 = enable;
					PORTC::PMR.B6 = enable;
					PORTC::PMR.B5 = enable;
				}
				break;

			case peripheral::SDHI:
				{
					uint8_t sel = enable ? 0b011010 : 0;
					MPC::P80PFS.PSEL = sel;  // SDHI_WP
					MPC::P81PFS.PSEL = sel;  // SDHI_CD
					PORT8::PMR.B0 = enable;
					PORT8::PMR.B2 = enable;
					MPC::PC2PFS.PSEL = sel;  // SDHI_D3
					MPC::PC3PFS.PSEL = sel;  // SDHI_D0
					MPC::PC4PFS.PSEL = sel;  // SDHI_D1
					PORTC::PMR.B2 = enable;
					PORTC::PMR.B3 = enable;
					PORTC::PMR.B4 = enable;
   					MPC::P75PFS.PSEL = sel;  // SDHI_D2
					MPC::P76PFS.PSEL = sel;  // SDHI_CMD
					MPC::P77PFS.PSEL = sel;  // SDHI_CLK
					PORT7::PMR.B5 = enable;
					PORT7::PMR.B6 = enable;
					PORT7::PMR.B7 = enable;
				}
				break;

			case peripheral::ETHERC0:  // only RMII mode
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

			case peripheral::ETHERC1:
				break;

			default:
				break;
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  周辺機器に切り替える
			@param[in]	t	周辺機器タイプ
		*/
		//-----------------------------------------------------------------//
		static void turn(peripheral t)
		{
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			sub_(t, true);

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  周辺機器をリセット（ポートに戻す）
			@param[in]	t	周辺機器タイプ
		*/
		//-----------------------------------------------------------------//
		static void reset(peripheral t) {
			MPC::PWPR.B0WI = 0;				// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;			// PxxPFS 書き込み許可

			sub_(t, false);

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}
	};
}

