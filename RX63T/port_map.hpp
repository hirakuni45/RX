#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63T グループ・ポート・マッピング
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX63T/peripheral.hpp"
#include "RX63T/port.hpp"
#include "RX63T/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map : public port_map_order {

		static bool sub_1st_(peripheral per, bool enable) noexcept
		{
			switch(per) {

			case peripheral::RIIC0:
			// PB1/SCL0
			// PB2/SDA0
				{
					uint8_t sel = enable ? 0b0'1111 : 0;
					PORTB::PMR.B1 = 0;
					PORTB::PMR.B2 = 0;
					MPC::PB1PFS.PSEL = sel;
					MPC::PB2PFS.PSEL = sel;
					PORTB::PMR.B1 = enable;
					PORTB::PMR.B2 = enable;
				}
				break;
			case peripheral::RIIC1:
			// P25/SCL1
			// P26/SDA1
				{
					uint8_t sel = enable ? 0b0'1111 : 0;
					PORT2::PMR.B5 = 0;
					PORT2::PMR.B6 = 0;
					MPC::P25PFS.PSEL = sel;
					MPC::P26PFS.PSEL = sel;
					PORT2::PMR.B5 = enable;
					PORT2::PMR.B6 = enable;
				}
				break;

			case peripheral::RSPI0:
			// P24/RSPCKA
			// P23/MOSIA
			// P22/MISOA
				{
					uint8_t sel = enable ? 0b0'1101 : 0;
					PORT2::PMR.B4 = 0;
					PORT2::PMR.B3 = 0;
					PORT2::PMR.B2 = 0;
					MPC::P24PFS.PSEL = sel;
					MPC::P22PFS.PSEL = sel;
					MPC::P23PFS.PSEL = sel;
					PORT2::PMR.B4 = enable;
					PORT2::PMR.B2 = enable;
					PORT2::PMR.B3 = enable;
				}
				break;
			case peripheral::RSPI1:
			// P24/RSPCKB
			// P23/MOSIB
			// P22/MISOB
				{
					uint8_t sel = enable ? 0b0'1110 : 0;
					PORT2::PMR.B4 = 0;
					PORT2::PMR.B3 = 0;
					PORT2::PMR.B2 = 0;
					MPC::P24PFS.PSEL = sel;
					MPC::P23PFS.PSEL = sel;
					MPC::P22PFS.PSEL = sel;
					PORT2::PMR.B4 = enable;
					PORT2::PMR.B3 = enable;
					PORT2::PMR.B2 = enable;
				}
				break;

			case peripheral::SCI0:
			// P22/RXD0
			// P23/TXD0
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT2::PMR.B2 = 0;
					PORT2::PMR.B3 = 0;
					MPC::P22PFS.PSEL = sel;
					MPC::P23PFS.PSEL = sel;
					PORT2::PMR.B2 = enable;
					PORT2::PMR.B3 = enable;
				}
				break;
			case peripheral::SCI1:
			// P93/RXD1
			// P26/TXD1
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT9::PMR.B3 = 0;
					PORT2::PMR.B6 = 0;
					MPC::P93PFS.PSEL = sel;
					MPC::P26PFS.PSEL = sel;
					PORT9::PMR.B3 = enable;
					PORT2::PMR.B6 = enable;
				}
				break;
			case peripheral::SCI2:
			// P03/RXD2
			// P02/TXD2
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT0::PMR.B3 = 0;
					PORT0::PMR.B2 = 0;
					MPC::P03PFS.PSEL = sel;
					MPC::P02PFS.PSEL = sel;
					PORT0::PMR.B3 = enable;
					PORT0::PMR.B2 = enable;
				}
				break;
			case peripheral::SCI3:
			// P34/RXD3
			// P35/TXD3
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT3::PMR.B4 = 0;
					PORT3::PMR.B5 = 0;
					MPC::P34PFS.PSEL = sel;
					MPC::P35PFS.PSEL = sel;
					PORT3::PMR.B4 = enable;
					PORT3::PMR.B5 = enable;
				}
				break;

			default:
				return false;
				break;
			}
			return true;
		}


		static bool sub_2nd_(peripheral per, bool enable) noexcept
		{
			switch(per) {

			case peripheral::RSPI0:
			// P24/RSPCKA
			// P23/MOSIA
			// P22/MISOA
				{
					uint8_t sel = enable ? 0b0'1101 : 0;
					PORT2::PMR.B4 = 0;
					PORT2::PMR.B3 = 0;
					PORT2::PMR.B2 = 0;
					MPC::P24PFS.PSEL = sel;
					MPC::P22PFS.PSEL = sel;
					MPC::P23PFS.PSEL = sel;
					PORT2::PMR.B4 = enable;
					PORT2::PMR.B2 = enable;
					PORT2::PMR.B3 = enable;
				}
				break;
			case peripheral::RSPI1:
			// P24/RSPCKB
			// P23/MOSIB
			// P22/MISOB
				{
					uint8_t sel = enable ? 0b0'1110 : 0;
					PORT2::PMR.B4 = 0;
					PORT2::PMR.B3 = 0;
					PORT2::PMR.B2 = 0;
					MPC::P24PFS.PSEL = sel;
					MPC::P23PFS.PSEL = sel;
					MPC::P22PFS.PSEL = sel;
					PORT2::PMR.B4 = enable;
					PORT2::PMR.B3 = enable;
					PORT2::PMR.B2 = enable;
				}
				break;

			default:
				return false;
				break;
			}
			return true;
		}


		static bool sub_3rd_(peripheral per, bool enable) noexcept
		{
			switch(per) {
			case peripheral::SCI1:
			// PD5/RXD1
			// PD3/TXD1
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORTD::PMR.B5 = 0;
					PORTD::PMR.B3 = 0;
					MPC::PD5PFS.PSEL = sel;
					MPC::PD3PFS.PSEL = sel;
					PORTD::PMR.B5 = enable;
					PORTD::PMR.B3 = enable;
				}
				break;
			default:
				return false;
				break;
			}
			return true;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  周辺機器別ポート切り替え
			@param[in]	per		周辺機器タイプ
			@param[in]	ena		無効にする場合「false」
			@param[in]	odr		候補を選択する場合
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral per, bool ena = true, ORDER odr = ORDER::FIRST) noexcept
		{
			if(odr == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			switch(odr) {
			case ORDER::FIRST:
				ret = sub_1st_(per, ena);
				break;
			case ORDER::SECOND:
				ret = sub_2nd_(per, ena);
				break;
			case ORDER::THIRD:
				ret = sub_3rd_(per, ena);
				break;
			default:
				ret = false;
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
