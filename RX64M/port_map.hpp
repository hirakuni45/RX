#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M グループ・ポート・マッピング @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "RX600/port.hpp"
#include "RX64M/mpc.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct port_map {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ペリフェラル種別
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class type {
			SCI0,  // (P20:TXD0, P21:RXD0)
			SCI1,  // (PF0:TXD1, PF2:RXD1)
			SCI2,  // (P13:TXD2, P12:RXD2)
			SCI3,  // (P23:TXD3, P25:RXD3)
			SCI4,  // (PB1:TXD4, PB0:RXD4)
			SCI5,  // (PA4:TXD5, PA2:RXD5)
			SCI6,  // (P00:TXD6, P01:RXD6)
			SCI7,  // (P90:TXD7, P92:RXD7)
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  周辺機器に切り替える
			@param[in]	t	周辺機器タイプ
		*/
		//-----------------------------------------------------------------//
		static void turn(type t)
		{
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			switch(t) {
			case type::SCI0:
				PORT2::PDR.B0 = 1;  // TXD0
				PORT2::PDR.B1 = 0;  // RXD0
				MPC::P20PFS.PSEL = 0b001010;
				MPC::P21PFS.PSEL = 0b001010;
				PORT2::PMR.B0 = 1;
				PORT2::PMR.B1 = 1;
				break;
			case type::SCI1:
				PORTF::PDR.B0 = 1;  // TXD1
				PORTF::PDR.B2 = 0;  // RXD1
				MPC::PF0PFS.PSEL = 0b001010;
				MPC::PF2PFS.PSEL = 0b001010;
				PORTF::PMR.B0 = 1;
				PORTF::PMR.B2 = 1;
				break;
			case type::SCI2:
				PORT1::PDR.B3 = 1;  // TXD2
				PORT1::PDR.B2 = 0;  // RXD2
				MPC::P13PFS.PSEL = 0b001010;
				MPC::P12PFS.PSEL = 0b001010;
				PORT1::PMR.B3 = 1;
				PORT1::PMR.B2 = 1;
				break;
			case type::SCI3:
				PORT2::PDR.B3 = 1;  // TXD3
				PORT2::PDR.B5 = 0;  // RXD3
				MPC::P23PFS.PSEL = 0b001010;
				MPC::P25PFS.PSEL = 0b001010;
				PORT2::PMR.B3 = 1;
				PORT2::PMR.B5 = 1;
				break;
			case type::SCI4:
				PORTB::PDR.B1 = 1;  // TXD4
				PORTB::PDR.B0 = 0;  // RXD4
				MPC::PB1PFS.PSEL = 0b001010;
				MPC::PB0PFS.PSEL = 0b001010;
				PORTB::PMR.B1 = 1;
				PORTB::PMR.B0 = 1;
				break;
			case type::SCI5:
				PORTA::PDR.B4 = 1;  // TXD5
				PORTA::PDR.B2 = 0;  // RXD5
				MPC::PA4PFS.PSEL = 0b001010;
				MPC::PA2PFS.PSEL = 0b001010;
				PORTA::PMR.B4 = 1;
				PORTA::PMR.B2 = 1;
				break;
			case type::SCI6:
				PORT0::PDR.B0 = 1;  // TXD6
				PORT0::PDR.B1 = 0;  // RXD6
				MPC::P00PFS.PSEL = 0b001010;
				MPC::P01PFS.PSEL = 0b001010;
				PORT0::PMR.B0 = 1;
				PORT0::PMR.B1 = 1;
				break;
			case type::SCI7:
				PORT9::PDR.B0 = 1;  // TXD7
				PORT9::PDR.B2 = 0;  // RXD7
				MPC::P90PFS.PSEL = 0b001010;
				MPC::P92PFS.PSEL = 0b001010;
				PORT9::PMR.B0 = 1;
				PORT9::PMR.B2 = 1;
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  周辺機器をリセット（ポートに戻す）
			@param[in]	t	周辺機器タイプ
		*/
		//-----------------------------------------------------------------//
		static void reset(type t) {
			MPC::PWPR.B0WI = 0;				// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;			// PxxPFS 書き込み許可

			switch(t) {
			case type::SCI0:
				PORT2::PDR.B0 = 0;  // TXD0
				PORT2::PDR.B1 = 0;  // RXD0
				MPC::P20PFS.PSEL = 0b000000;
				MPC::P21PFS.PSEL = 0b000000;
				PORT2::PMR.B0 = 0;
				PORT2::PMR.B1 = 0;
				break;
			case type::SCI1:
				PORTF::PDR.B0 = 0;	// TXD1
				PORTF::PDR.B2 = 0;	// RXD1
				MPC::PF0PFS.PSEL = 0b000000;
				MPC::PF2PFS.PSEL = 0b000000;
				PORTF::PMR.B0 = 0;				// 周辺機能として使用
				PORTF::PMR.B2 = 0;				// 周辺機能として使用
				break;
			case type::SCI2:
				PORT1::PDR.B3 = 0;  // TXD2
				PORT1::PDR.B2 = 0;  // RXD2
				MPC::P13PFS.PSEL = 0b000000;
				MPC::P12PFS.PSEL = 0b000000;
				PORT1::PMR.B3 = 0;
				PORT1::PMR.B2 = 0;
				break;
			case type::SCI3:
				PORT2::PDR.B3 = 0;  // TXD3
				PORT2::PDR.B5 = 0;  // RXD3
				MPC::P23PFS.PSEL = 0b000000;
				MPC::P25PFS.PSEL = 0b000000;
				PORT2::PMR.B3 = 0;
				PORT2::PMR.B5 = 0;
				break;
			case type::SCI4:
				PORTB::PDR.B1 = 0;  // TXD4
				PORTB::PDR.B0 = 0;  // RXD4
				MPC::PB1PFS.PSEL = 0b000000;
				MPC::PB0PFS.PSEL = 0b000000;
				PORTB::PMR.B1 = 0;
				PORTB::PMR.B0 = 0;
				break;
			case type::SCI5:
				PORTA::PDR.B4 = 0;  // TXD5
				PORTA::PDR.B2 = 0;  // RXD5
				MPC::PA4PFS.PSEL = 0b000000;
				MPC::PA2PFS.PSEL = 0b000000;
				PORTA::PMR.B4 = 0;
				PORTA::PMR.B2 = 0;
				break;
			case type::SCI6:
				PORT0::PDR.B0 = 0;  // TXD6
				PORT0::PDR.B1 = 0;  // RXD6
				MPC::P00PFS.PSEL = 0b000000;
				MPC::P01PFS.PSEL = 0b000000;
				PORT0::PMR.B0 = 0;
				PORT0::PMR.B1 = 0;
				break;
			case type::SCI7:
				PORT9::PDR.B0 = 0;  // TXD7
				PORT9::PDR.B2 = 0;  // RXD7
				MPC::P90PFS.PSEL = 0b000000;
				MPC::P92PFS.PSEL = 0b000000;
				PORT9::PMR.B0 = 0;
				PORT9::PMR.B2 = 0;
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}
	};
}

