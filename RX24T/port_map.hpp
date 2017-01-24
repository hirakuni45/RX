#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・ポート・マッピング @n
			Copyright 2016,2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "RX600/port.hpp"
#include "RX24T/mpc.hpp"
#include "RX24T/peripheral.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map {

		static void sub_(peripheral t, bool enable) {
			switch(t) {
			case peripheral::RIIC0:
				{
					uint8_t sel = enable ? 0b01111 : 0;
					MPC::PB1PFS.PSEL = sel;  // PB1/SCL0 (34)
					MPC::PB2PFS.PSEL = sel;  // PB2/SDA0 (33)
					PORTB::PMR.B1 = enable;
					PORTB::PMR.B2 = enable;
				}
				break;

			case peripheral::RSPI0:
				{
					uint8_t sel = enable ? 0b01101 : 0;
					MPC::P22PFS.PSEL = sel;  // P22/MISOA  (66)
					MPC::P23PFS.PSEL = sel;  // P23/MOSIA  (65)
					MPC::P24PFS.PSEL = sel;  // P24/RSPCKA (64)
					PORT2::PMR.B2 = enable;
					PORT2::PMR.B3 = enable;
					PORT2::PMR.B4 = enable;
				}
				break;
			case peripheral::SCI1C:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PD4PFS.PSEL = sel;  // PD4/SCK1 (21)
					PORTD::PMR.B4 = enable;
				}
			case peripheral::SCI1:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PD3PFS.PSEL = sel;  // PD3/TXD1 (22)
					MPC::PD5PFS.PSEL = sel;  // PD5/RXD1 (20)
					PORTD::PMR.B3 = enable;
					PORTD::PMR.B5 = enable;
				}
				break;
			case peripheral::SCI5C:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PB7PFS.PSEL = sel;  // PB7/SCK5 (26)
					PORTB::PMR.B7 = enable;
				}
			case peripheral::SCI5:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PB5PFS.PSEL = sel;  // PB5/TXD5 (28)
					MPC::PB6PFS.PSEL = sel;  // PB6/RXD5 (27)
					PORTB::PMR.B5 = enable;
					PORTB::PMR.B6 = enable;
				}
				break;
			case peripheral::SCI6C:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PA4PFS.PSEL = sel;  // PA4/SCK6 (37)
					PORTA::PMR.B4 = enable;
				}
			case peripheral::SCI6:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PB0PFS.PSEL = sel;  // PB0/TXD6 (35)
					MPC::PA5PFS.PSEL = sel;  // PA5/RXD6 (36)
					PORTB::PMR.B0 = enable;
					PORTA::PMR.B5 = enable;
				}
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
			@param[in]	f	周辺機能を使わない場合「false」
		*/
		//-----------------------------------------------------------------//
		static void turn(peripheral t, bool f = true)
		{
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			sub_(t, f);

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}
	};
}

