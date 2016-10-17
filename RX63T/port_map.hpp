#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63T グループ・ポート・マッピング @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "RX600/port.hpp"
#include "RX63T/mpc.hpp"

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
			SCI0,  //
			SCI1,  // （PD5:RXD1:input, PD3:TXD1:output）
			SCI2,  //
			SCI3,  //
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
				break;
			case type::SCI1:
				PORTD::PDR.B3 = 1;	// TXD1
				PORTD::PDR.B5 = 0;  // RXD1
				MPC::PD3PFS.PSEL = 0b01010;
				MPC::PD5PFS.PSEL = 0b01010;
				PORTD::PMR.B3 = 1;
				PORTD::PMR.B5 = 1;
				break;
			case type::SCI2:
				break;
			case type::SCI3:
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
				break;
			case type::SCI1:
				PORTD::PDR.B3 = 0;	// TXD1
				PORTD::PDR.B5 = 0;  // RXD1
				MPC::PD3PFS.PSEL = 0b00000;
				MPC::PD5PFS.PSEL = 0b00000;
				PORTD::PMR.B3 = 0;
				PORTD::PMR.B5 = 0;
				break;
			case type::SCI2:
				break;
			case type::SCI3:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}
	};
}

