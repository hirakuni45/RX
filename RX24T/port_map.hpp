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

		static void sci_(peripheral t) {
			switch(t) {
			case peripheral::SCI1:
				PORTD::PDR.B3 = 1;  // TXD0
				PORTD::PDR.B5 = 0;  // RXD0
				MPC::PD3PFS.PSEL = 0b01010;
				MPC::PD5PFS.PSEL = 0b01010;
				PORTD::PMR.B3 = 1;
				PORTD::PMR.B5 = 1;
				break;
			case peripheral::SCI5:

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

			sci_(t);

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

