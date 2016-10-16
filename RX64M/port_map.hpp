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
			SCI0,  // (TXD0, RXD0)
			SCI1,  // (TXD1, RXD1)
			SCI2,  // (TXD2, RXD2)
			SCI3,  // (TXD3, RXD3)
			SCI4,  // (TXD4, RXD4)
			SCI5,  // (TXD5, RXD5)
			SCI6,  // (TXD6, RXD6)
			SCI7,  // (TXD7, RXD7)
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  周辺機器に切り替える
			@param[in]	t	周辺機器タイプ
		*/
		//-----------------------------------------------------------------//
		static void turn(type t)
		{
			MPC::PWPR.B0WI = 0;				// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;			// PxxPFS 書き込み許可

			switch(t) {
			case type::SCI0:
				break;
			case type::SCI1:
				PORTF::PDR.B0 = 1;              // TXD1
				PORTF::PDR.B2 = 0;              // RXD1
				MPC::PF0PFS.PSEL = 0b001010;	// TXD1 設定
				MPC::PF2PFS.PSEL = 0b001010;	// RXD1 設定
				PORTF::PMR.B0 = 1;				// 周辺機能として使用
				PORTF::PMR.B2 = 1;				// 周辺機能として使用
				break;
			case type::SCI2:
				break;
			case type::SCI3:
				break;
			case type::SCI4:
				break;
			case type::SCI5:
				break;
			case type::SCI6:
				break;
			case type::SCI7:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();	// MPC 書き込み禁止
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  周辺機器をリセット（ポートに戻す）
			@param[in]	t	周辺機器タイプ
		*/
		//-----------------------------------------------------------------//
		static void reset(type t) {
			switch(t) {
			case type::SCI0:
				break;
			case type::SCI1:
				PORTF::PDR.B0 = 0;              // TXD1
				PORTF::PDR.B2 = 0;              // RXD1
				MPC::PF0PFS.PSEL = 0b000000;
				MPC::PF2PFS.PSEL = 0b000000;
				PORTF::PMR.B0 = 0;				// 周辺機能として使用
				PORTF::PMR.B2 = 0;				// 周辺機能として使用
				break;
			case type::SCI2:
				break;
			case type::SCI3:
				break;
			case type::SCI4:
				break;
			case type::SCI5:
				break;
			case type::SCI6:
				break;
			case type::SCI7:
				break;
			}
		}
	};
}

