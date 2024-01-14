#pragma once
//=========================================================================//
/*!	@file
	@brief	RX231 グループ・ポート・マッピング
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX231/peripheral.hpp"
#include "RX231/port.hpp"
#include "RX231/mpc.hpp"
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
			// P16/SCL (LQFP64:18)
			// P17/SDA (LQFP64:17)
				{
					uint8_t sel = enable ? 0b0'1111 : 0;
					PORT1::PMR.B6 = 0;
					PORT1::PMR.B7 = 0;
					MPC::P16PFS.PSEL = sel;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B6 = enable;
					PORT1::PMR.B7 = enable;
				}
				break;
			case peripheral::RSPI0:
			// PA5/RSPCKA
			// PA6/MOSIA
			// PA7/MISOA
				{
					uint8_t sel = enable ? 0b0'1101 : 0;
					PORTA::PMR.B5 = 0;
					PORTA::PMR.B6 = 0;
					PORTA::PMR.B7 = 0;
					MPC::PA5PFS.PSEL = sel;
					MPC::PA6PFS.PSEL = sel;
					MPC::PA7PFS.PSEL = sel;
					PORTA::PMR.B5 = enable;
					PORTA::PMR.B6 = enable;
					PORTA::PMR.B7 = enable;
				}
				break;
			case peripheral::SCI0:
			// P21/RXD0
			// P20/TXD0
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT2::PMR.B1 = 0;
					PORT2::PMR.B0 = 0;
					MPC::P21PFS.PSEL = sel;
					MPC::P20PFS.PSEL = sel;
					PORT2::PMR.B1 = enable;
					PORT2::PMR.B0 = enable;
				}
				break;
			case peripheral::SCI1:
			// P15/RXD1 (LQFP64:19)
			// P16/TXD1 (LQFP64:18)
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT1::PMR.B5 = 0;
					PORT1::PMR.B6 = 0;
					MPC::P15PFS.PSEL = sel;
					MPC::P16PFS.PSEL = sel;
					PORT1::PMR.B5 = enable;
					PORT1::PMR.B6 = enable;
				}
				break;
			case peripheral::SCI5:
			case peripheral::IrDA:
			// PA3/RXD5/IRRXD5 (LQFP64:43)
			// PA4/TXD5/IRTXD5 (LQFP64:42)
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORTA::PMR.B3 = 0;
					PORTA::PMR.B4 = 0;
					MPC::PA3PFS.PSEL = sel;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B3 = enable;
					PORTA::PMR.B4 = enable;
				}
				break;
			case peripheral::SCI6:
			// P33/RXD6
			// P32/TXD6
				{
					uint8_t sel = enable ? 0b0'1011 : 0;
					PORT3::PMR.B3 = 0;
					PORT3::PMR.B2 = 0;
					MPC::P33PFS.PSEL = sel;
					MPC::P32PFS.PSEL = sel;
					PORT3::PMR.B3 = enable;
					PORT3::PMR.B2 = enable;
				}
				break;
			case peripheral::SCI8:
			// PC6/RXD8
			// PC7/TXD8
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORTC::PMR.B6 = 0;
					PORTC::PMR.B7 = 0;
					MPC::PC6PFS.PSEL = sel;
					MPC::PC7PFS.PSEL = sel;
					PORTC::PMR.B6 = enable;
					PORTC::PMR.B7 = enable;
				}
				break;
			case peripheral::SCI9:
			// PB6/RXD9
			// PB7/TXD9
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORTB::PMR.B6 = 0;
					PORTB::PMR.B7 = 0;
					MPC::PB6PFS.PSEL = sel;
					MPC::PB7PFS.PSEL = sel;
					PORTB::PMR.B6 = enable;
					PORTB::PMR.B7 = enable;
				}
				break;
			case peripheral::SCI12:
			// PE2/RXD12
			// PE1/TXD12
				{
					uint8_t sel = enable ? 0b0'1100 : 0;
					PORTE::PMR.B2 = 0;
					PORTE::PMR.B1 = 0;
					MPC::PE2PFS.PSEL = sel;
					MPC::PE1PFS.PSEL = sel;
					PORTE::PMR.B2 = enable;
					PORTE::PMR.B1 = enable;
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
			case peripheral::RIIC0:
			// P12/SCL
			// P13/SDA
				{
					uint8_t sel = enable ? 0b0'1111 : 0;
					PORT1::PMR.B2 = 0;
					PORT1::PMR.B3 = 0;
					MPC::P12PFS.PSEL = sel;
					MPC::P13PFS.PSEL = sel;
					PORT1::PMR.B2 = enable;
					PORT1::PMR.B3 = enable;
				}
				break;
#if 0
			case peripheral::RSPI0:
			// PC5/RSPCKA
			// P16/MOSIA
			// P17/MISOA
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
#endif
			case peripheral::SCI1:  // for BOOT serial port
			// P30/RXD1
			// P26/TXD1
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT3::PMR.B0 = 0;
					PORT2::PMR.B6 = 0;
					MPC::P30PFS.PSEL = sel;
					MPC::P26PFS.PSEL = sel;
					PORT3::PMR.B0 = enable;
					PORT2::PMR.B6 = enable;
				}
				break;
			case peripheral::SCI5:
			case peripheral::IrDA:
			// PC2/RXD5
			// PC3/TXD5
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORTC::PMR.B2 = 0;
					PORTC::PMR.B3 = 0;
					MPC::PC2PFS.PSEL = sel;
					MPC::PC3PFS.PSEL = sel;
					PORTC::PMR.B2 = enable;
					PORTC::PMR.B3 = enable;
				}
				break;
			case peripheral::SCI6:
			// PB0/RXD6
			// PB1/TXD6
				{
					uint8_t sel = enable ? 0b0'1011 : 0;
					PORTB::PMR.B0 = 0;
					PORTB::PMR.B1 = 0;
					MPC::PB0PFS.PSEL = sel;
					MPC::PB1PFS.PSEL = sel;
					PORTB::PMR.B0 = enable;
					PORTB::PMR.B1 = enable;
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
			case peripheral::RSPI0:
			// PC5/RSPCKA
			// PC6/MOSIA
			// PC7/MISOA
				{
					uint8_t sel = enable ? 0b0'1101 : 0;
					PORTC::PMR.B5 = 0;
					PORTC::PMR.B6 = 0;
					PORTC::PMR.B7 = 0;
					MPC::PC5PFS.PSEL = sel;
					MPC::PC6PFS.PSEL = sel;
					MPC::PC7PFS.PSEL = sel;
					PORTC::PMR.B5 = enable;
					PORTC::PMR.B6 = enable;
					PORTC::PMR.B7 = enable;
				}
				break;
			case peripheral::SCI5:
			case peripheral::IrDA:
			// PA3/RXD5
			// PA4/TXD5
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORTA::PMR.B3 = 0;
					PORTA::PMR.B4 = 0;
					MPC::PA3PFS.PSEL = sel;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B3 = enable;
					PORTA::PMR.B4 = enable;
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
