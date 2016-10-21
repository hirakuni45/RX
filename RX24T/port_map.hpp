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

		static void sub_(peripheral t) {
			switch(t) {
			case peripheral::RIIC0:
				MPC::PB1PFS.PSEL = 0b01111;  // SCL0
				MPC::PB2PFS.PSEL = 0b01111;  // SDA0
				PORTB::PMR.B1 = 1;
				PORTB::PMR.B2 = 1;
				break;

			case peripheral::SCI1:
				PORTD::PDR.B3 = 1;  // TXD1
				PORTD::PDR.B5 = 0;  // RXD1
				MPC::PD3PFS.PSEL = 0b01010;
				MPC::PD5PFS.PSEL = 0b01010;
				PORTD::PMR.B3 = 1;
				PORTD::PMR.B5 = 1;
				break;
			case peripheral::SCI5:
				PORTB::PDR.B5 = 1;  // TXD5
				PORTB::PDR.B6 = 0;  // RXD5
				MPC::PB5PFS.PSEL = 0b01010;
				MPC::PB6PFS.PSEL = 0b01010;
				PORTB::PMR.B5 = 1;
				PORTB::PMR.B6 = 1;
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
			case peripheral::SCI1:
				break;
			case peripheral::SCI5:
				break;
			case peripheral::SCI6:
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}
	};
}

