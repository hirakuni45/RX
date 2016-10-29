#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・ポート・マッピング @n
			Copyright 2016 Kunihito Hiramatsu
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
					MPC::PB1PFS.PSEL = sel;  // SCL0
					MPC::PB2PFS.PSEL = sel;  // SDA0
					PORTB::PMR.B1 = enable;
					PORTB::PMR.B2 = enable;
				}
				break;

			case peripheral::RSPI0:
				{
					uint8_t sel = enable ? 0b01101 : 0;
					MPC::P22PFS.PSEL = sel;  // MISOA
					MPC::P23PFS.PSEL = sel;  // MOSIA
					MPC::P24PFS.PSEL = sel;  // RSPCKA
					PORT2::PMR.B2 = enable;
					PORT2::PMR.B3 = enable;
					PORT2::PMR.B4 = enable;
				}
				break;

			case peripheral::SCI1:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PD3PFS.PSEL = sel;
					MPC::PD5PFS.PSEL = sel;
					PORTD::PMR.B3 = enable;
					PORTD::PMR.B5 = enable;
				}
				break;
			case peripheral::SCI5:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PB5PFS.PSEL = sel;
					MPC::PB6PFS.PSEL = sel;
					PORTB::PMR.B5 = enable;
					PORTB::PMR.B6 = enable;
				}
				break;
			case peripheral::SCI6:
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

