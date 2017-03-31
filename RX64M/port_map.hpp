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

		static void sub_(peripheral t) {
			switch(t) {
			case peripheral::SCI0:
				PORT2::PDR.B0 = 1;  // TXD0
				PORT2::PDR.B1 = 0;  // RXD0
				MPC::P20PFS.PSEL = 0b001010;
				MPC::P21PFS.PSEL = 0b001010;
				PORT2::PMR.B0 = 1;
				PORT2::PMR.B1 = 1;
				break;
			case peripheral::SCI1:
				PORTF::PDR.B0 = 1;  // TXD1
				PORTF::PDR.B2 = 0;  // RXD1
				MPC::PF0PFS.PSEL = 0b001010;
				MPC::PF2PFS.PSEL = 0b001010;
				PORTF::PMR.B0 = 1;
				PORTF::PMR.B2 = 1;
				break;
			case peripheral::SCI2:
				PORT1::PDR.B3 = 1;  // TXD2
				PORT1::PDR.B2 = 0;  // RXD2
				MPC::P13PFS.PSEL = 0b001010;
				MPC::P12PFS.PSEL = 0b001010;
				PORT1::PMR.B3 = 1;
				PORT1::PMR.B2 = 1;
				break;
			case peripheral::SCI3:
				PORT2::PDR.B3 = 1;  // TXD3
				PORT2::PDR.B5 = 0;  // RXD3
				MPC::P23PFS.PSEL = 0b001010;
				MPC::P25PFS.PSEL = 0b001010;
				PORT2::PMR.B3 = 1;
				PORT2::PMR.B5 = 1;
				break;
			case peripheral::SCI4:
				PORTB::PDR.B1 = 1;  // TXD4
				PORTB::PDR.B0 = 0;  // RXD4
				MPC::PB1PFS.PSEL = 0b001010;
				MPC::PB0PFS.PSEL = 0b001010;
				PORTB::PMR.B1 = 1;
				PORTB::PMR.B0 = 1;
				break;
			case peripheral::SCI5:
				PORTA::PDR.B4 = 1;  // TXD5
				PORTA::PDR.B2 = 0;  // RXD5
				MPC::PA4PFS.PSEL = 0b001010;
				MPC::PA2PFS.PSEL = 0b001010;
				PORTA::PMR.B4 = 1;
				PORTA::PMR.B2 = 1;
				break;
			case peripheral::SCI6:
				PORT0::PDR.B0 = 1;  // TXD6
				PORT0::PDR.B1 = 0;  // RXD6
				MPC::P00PFS.PSEL = 0b001010;
				MPC::P01PFS.PSEL = 0b001010;
				PORT0::PMR.B0 = 1;
				PORT0::PMR.B1 = 1;
				break;
			case peripheral::SCI7:
				PORT9::PDR.B0 = 1;  // TXD7
				PORT9::PDR.B2 = 0;  // RXD7
				MPC::P90PFS.PSEL = 0b001010;
				MPC::P92PFS.PSEL = 0b001010;
				PORT9::PMR.B0 = 1;
				PORT9::PMR.B2 = 1;
				break;

			case peripheral::SDHI:
				MPC::P80PFS.PSEL = 0b011010;  // SDHI_WP
				MPC::P81PFS.PSEL = 0b011010;  // SDHI_CD
				PORT8::PMR.B0 = 1;
				PORT8::PMR.B2 = 1;
				MPC::PC2PFS.PSEL = 0b011010;  // SDHI_D3
				MPC::PC3PFS.PSEL = 0b011010;  // SDHI_D0
				MPC::PC4PFS.PSEL = 0b011010;  // SDHI_D1
				PORTC::PMR.B2 = 1;
				PORTC::PMR.B3 = 1;
				PORTC::PMR.B4 = 1;
   				MPC::P75PFS.PSEL = 0b011010;  // SDHI_D2
				MPC::P76PFS.PSEL = 0b011010;  // SDHI_CMD
				MPC::P77PFS.PSEL = 0b011010;  // SDHI_CLK
				PORT7::PMR.B5 = 1;
				PORT7::PMR.B6 = 1;
				PORT7::PMR.B7 = 1;
				break;

			case peripheral::ETHERC0:
//				MPC::P34PFS.PSEL = 0b010001;  // ET0_LINKSTA
//				PORT3::PMR.B4 = 1;
				MPC::P71PFS.PSEL = 0b010001;  // ET0_MDIO
				MPC::P72PFS.PSEL = 0b010001;  // ET0_MDC
//				MPC::P73PFS.PSEL = 0b010001;  // ET0_WOL
				MPC::P74PFS.PSEL = 0b010010;  // RMII0_RXD1
				MPC::P75PFS.PSEL = 0b010010;  // RMII0_RXD0
				MPC::P76PFS.PSEL = 0b010010;  // REF50CK0
				MPC::P77PFS.PSEL = 0b010010;  // RMII0_RX_ER
				PORT7::PMR.B1 = 1;
				PORT7::PMR.B2 = 1;
//				PORT7::PMR.B3 = 1;
				PORT7::PMR.B4 = 1;
				PORT7::PMR.B5 = 1;
				PORT7::PMR.B6 = 1;
				PORT7::PMR.B7 = 1;
				MPC::P80PFS.PSEL = 0b010010;  // RMII0_TXD_EN
				MPC::P81PFS.PSEL = 0b010010;  // RMII0_TXD0
				MPC::P82PFS.PSEL = 0b010010;  // RMII0_TXD1
				MPC::P83PFS.PSEL = 0b010010;  // RMII0_CRS_DV
				PORT8::PMR.B0 = 1;
				PORT8::PMR.B1 = 1;
				PORT8::PMR.B2 = 1;
				PORT8::PMR.B3 = 1;
				MPC::PFENET.PHYMODE0 = 0;  // for RMII mode chanel 0
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

			sub_(t);

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

			switch(t) {
			case peripheral::SCI0:
				PORT2::PDR.B0 = 0;  // TXD0
				PORT2::PDR.B1 = 0;  // RXD0
				MPC::P20PFS.PSEL = 0b000000;
				MPC::P21PFS.PSEL = 0b000000;
				PORT2::PMR.B0 = 0;
				PORT2::PMR.B1 = 0;
				break;
			case peripheral::SCI1:
				PORTF::PDR.B0 = 0;	// TXD1
				PORTF::PDR.B2 = 0;	// RXD1
				MPC::PF0PFS.PSEL = 0b000000;
				MPC::PF2PFS.PSEL = 0b000000;
				PORTF::PMR.B0 = 0;				// 周辺機能として使用
				PORTF::PMR.B2 = 0;				// 周辺機能として使用
				break;
			case peripheral::SCI2:
				PORT1::PDR.B3 = 0;  // TXD2
				PORT1::PDR.B2 = 0;  // RXD2
				MPC::P13PFS.PSEL = 0b000000;
				MPC::P12PFS.PSEL = 0b000000;
				PORT1::PMR.B3 = 0;
				PORT1::PMR.B2 = 0;
				break;
			case peripheral::SCI3:
				PORT2::PDR.B3 = 0;  // TXD3
				PORT2::PDR.B5 = 0;  // RXD3
				MPC::P23PFS.PSEL = 0b000000;
				MPC::P25PFS.PSEL = 0b000000;
				PORT2::PMR.B3 = 0;
				PORT2::PMR.B5 = 0;
				break;
			case peripheral::SCI4:
				PORTB::PDR.B1 = 0;  // TXD4
				PORTB::PDR.B0 = 0;  // RXD4
				MPC::PB1PFS.PSEL = 0b000000;
				MPC::PB0PFS.PSEL = 0b000000;
				PORTB::PMR.B1 = 0;
				PORTB::PMR.B0 = 0;
				break;
			case peripheral::SCI5:
				PORTA::PDR.B4 = 0;  // TXD5
				PORTA::PDR.B2 = 0;  // RXD5
				MPC::PA4PFS.PSEL = 0b000000;
				MPC::PA2PFS.PSEL = 0b000000;
				PORTA::PMR.B4 = 0;
				PORTA::PMR.B2 = 0;
				break;
			case peripheral::SCI6:
				PORT0::PDR.B0 = 0;  // TXD6
				PORT0::PDR.B1 = 0;  // RXD6
				MPC::P00PFS.PSEL = 0b000000;
				MPC::P01PFS.PSEL = 0b000000;
				PORT0::PMR.B0 = 0;
				PORT0::PMR.B1 = 0;
				break;
			case peripheral::SCI7:
				PORT9::PDR.B0 = 0;  // TXD7
				PORT9::PDR.B2 = 0;  // RXD7
				MPC::P90PFS.PSEL = 0b000000;
				MPC::P92PFS.PSEL = 0b000000;
				PORT9::PMR.B0 = 0;
				PORT9::PMR.B2 = 0;
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}
	};
}

