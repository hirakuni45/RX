#pragma once
//=========================================================================//
/*!	@file
	@brief	RX631/RX63N グループ・ポート・マッピング @n
			BOOT Mode Serial: @n
			  PF2/RXD1 (177/176 Pin), P30/RXD1(145, 144, 100, 64, 48 Pin)  @n
			  PF0/TXD1 (177/176 Pin), P26/RXD1(145, 144, 100, 64, 48 Pin) 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX63x/peripheral.hpp"
#include "RX63x/port.hpp"
#include "RX63x/mpc.hpp"
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
			// P12/SCL0
			// P13/SDA0
				{
					uint8_t sel = enable ? 0b0'1111 : 0;
					PORT1::PMR.B2 = 0;
					PORT1::PMR.B3 = 0;
					MPC::P12PFS.PSEL = sel;  // ok
					MPC::P13PFS.PSEL = sel;  // ok
					PORT1::PMR.B2 = enable;
					PORT1::PMR.B3 = enable;
				}
				break;
			case peripheral::RIIC1:
			// P21/SCL0
			// P20/SDA0
				{
					uint8_t sel = enable ? 0b0'1111 : 0;
					PORT2::PMR.B1 = 0;
					PORT2::PMR.B0 = 0;
					MPC::P21PFS.PSEL = sel;  // ok
					MPC::P20PFS.PSEL = sel;  // ok
					PORT2::PMR.B1 = enable;
					PORT2::PMR.B0 = enable;
				}
				break;
			case peripheral::RIIC2:
			// P16/SCL0
			// P17/SDA0
				{
					uint8_t sel = enable ? 0b0'1111 : 0;
					PORT1::PMR.B6 = 0;
					PORT1::PMR.B7 = 0;
					MPC::P16PFS.PSEL = sel;  // ok
					MPC::P17PFS.PSEL = sel;  // ok
					PORT1::PMR.B6 = enable;
					PORT1::PMR.B7 = enable;
				}
				break;
			case peripheral::RIIC3:
			// PC0/SCL0
			// PC1/SDA0
				{
					uint8_t sel = enable ? 0b0'1111 : 0;
					PORTC::PMR.B0 = 0;
					PORTC::PMR.B1 = 0;
					MPC::PC0PFS.PSEL = sel;  // ok
					MPC::PC1PFS.PSEL = sel;  // ok
					PORTC::PMR.B0 = enable;
					PORTC::PMR.B1 = enable;
				}
				break;

			case peripheral::CAN0:
			// P33/CRX0
			// P32/CTX0
				{
					uint8_t sel = enable ? 0b1'0000 : 0;
					PORT3::PMR.B3 = 0;
					PORT3::PMR.B2 = 0;
					MPC::P33PFS.PSEL = sel;  // ok
					MPC::P32PFS.PSEL = sel;  // ok
					PORT3::PMR.B3 = enable;
					PORT3::PMR.B2 = enable;
				}
				break;
			case peripheral::CAN1:
			// P15/CRX1
			// P14/CTX1
				{
					uint8_t sel = enable ? 0b1'0000 : 0;
					PORT1::PMR.B5 = 0;
					PORT1::PMR.B4 = 0;
					MPC::P15PFS.PSEL = sel;  // ok
					MPC::P14PFS.PSEL = sel;  // ok
					PORT1::PMR.B5 = enable;
					PORT1::PMR.B4 = enable;
				}
				break;
			case peripheral::CAN2:
			// ※ ROM 容量 1M バイト以下の製品には含まれない
			// P67/CRX2
			// P66/CTX2
				{
					uint8_t sel = enable ? 0b1'0000 : 0;
					PORT6::PMR.B7 = 0;
					PORT6::PMR.B6 = 0;
					MPC::P67PFS.PSEL = sel;  // ok
					MPC::P66PFS.PSEL = sel;  // ok
					PORT6::PMR.B7 = enable;
					PORT6::PMR.B6 = enable;
				}
				break;

			case peripheral::RSPI0:
			// PA5/RSPCKA
			// P16/MOSIA
			// P17/MISOA
				{
					uint8_t sel = enable ? 0b0'1101 : 0;
					PORTA::PMR.B5 = 0;
					PORT1::PMR.B6 = 0;
					PORT1::PMR.B7 = 0;
					MPC::PA5PFS.PSEL = sel;  // ok
					MPC::P16PFS.PSEL = sel;  // ok
					MPC::P17PFS.PSEL = sel;  // ok
					PORTA::PMR.B5 = enable;
					PORT1::PMR.B6 = enable;
					PORT1::PMR.B7 = enable;
				}
				break;
			case peripheral::RSPI1:
			// P27/RSPCKB
			// P26/MOSIB
			// P30/MISOB
				{
					uint8_t sel = enable ? 0b0'1110 : 0;
					PORT2::PMR.B7 = 0;
					PORT2::PMR.B6 = 0;
					PORT3::PMR.B0 = 0;
					MPC::P27PFS.PSEL = sel;  // ok
					MPC::P26PFS.PSEL = sel;  // ok
					MPC::P30PFS.PSEL = sel;  // ok
					PORT2::PMR.B7 = enable;
					PORT2::PMR.B6 = enable;
					PORT3::PMR.B0 = enable;
				}
				break;
			case peripheral::RSPI2:
			// PD3/RSPCKC
			// PD1/MOSIC
			// PD2/MISOC
				{
					uint8_t sel = enable ? 0b0'1110 : 0;
					PORTD::PMR.B3 = 0;
					PORTD::PMR.B1 = 0;
					PORTD::PMR.B2 = 0;
					MPC::PD3PFS.PSEL = sel;  // ok
					MPC::PD1PFS.PSEL = sel;  // ok
					MPC::PD2PFS.PSEL = sel;  // ok
					PORTD::PMR.B3 = enable;
					PORTD::PMR.B1 = enable;
					PORTD::PMR.B2 = enable;
				}
				break;

			case peripheral::SCI0:
			// P21/RXD0
			// P20/TXD0
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT2::PMR.B1 = 0;
					PORT2::PMR.B0 = 0;
					MPC::P21PFS.PSEL = sel;  // ok
					MPC::P20PFS.PSEL = sel;  // ok
					PORT2::PMR.B1 = enable;
					PORT2::PMR.B0 = enable;
				}
				break;
			case peripheral::SCI1:
			// P15/RXD1
			// P16/TXD1
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT1::PMR.B5 = 0;
					PORT1::PMR.B6 = 0;
					MPC::P15PFS.PSEL = sel;  // ok
					MPC::P16PFS.PSEL = sel;  // ok
					PORT1::PMR.B5 = enable;
					PORT1::PMR.B6 = enable;
				}
				break;
			case peripheral::SCI2:
			// P12/RXD2
			// P13/TXD2
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT1::PMR.B2 = 0;
					PORT1::PMR.B3 = 0;
					MPC::P12PFS.PSEL = sel;  // ok
					MPC::P13PFS.PSEL = sel;  // ok
					PORT1::PMR.B2 = enable;
					PORT1::PMR.B3 = enable;
				}
				break;
			case peripheral::SCI3:
			// P16/RXD3
			// P17/TXD3
				{
					uint8_t sel = enable ? 0b0'1011 : 0;
					PORT1::PMR.B6 = 0;
					PORT1::PMR.B7 = 0;
					MPC::P16PFS.PSEL = sel;  // ok
					MPC::P17PFS.PSEL = sel;  // ok
					PORT1::PMR.B6 = enable;
					PORT1::PMR.B7 = enable;
				}
				break;
			case peripheral::SCI4:
			// PB0/RXD4
			// PB1/TXD4
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORTB::PMR.B0 = 0;
					PORTB::PMR.B1 = 0;
					MPC::PB0PFS.PSEL = sel;  // ok
					MPC::PB1PFS.PSEL = sel;  // ok
					PORTB::PMR.B0 = enable;
					PORTB::PMR.B1 = enable;
				}
				break;
			case peripheral::SCI5:
			// PA2/RXD5
			// PA4/TXD5
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORTA::PMR.B2 = 0;
					PORTA::PMR.B4 = 0;
					MPC::PA2PFS.PSEL = sel;  // ok
					MPC::PA4PFS.PSEL = sel;  // ok
					PORTA::PMR.B2 = enable;
					PORTA::PMR.B4 = enable;
				}
				break;
			case peripheral::SCI6:
			// P01/RXD6
			// P00/TXD6
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT0::PMR.B1 = 0;
					PORT0::PMR.B0 = 0;
					MPC::P01PFS.PSEL = sel;  // ok
					MPC::P00PFS.PSEL = sel;  // ok
					PORT0::PMR.B1 = enable;
					PORT0::PMR.B0 = enable;
				}
				break;
			case peripheral::SCI7:
			// P92/RXD7
			// P90/TXD7
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT9::PMR.B2 = 0;
					PORT9::PMR.B0 = 0;
					MPC::P92PFS.PSEL = sel;  // ok
					MPC::P90PFS.PSEL = sel;  // ok
					PORT9::PMR.B2 = enable;
					PORT9::PMR.B0 = enable;
				}
				break;
			case peripheral::SCI8:
			// PC6/RXD8
			// PC7/TXD8
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORTC::PMR.B6 = 0;
					PORTC::PMR.B7 = 0;
					MPC::PC6PFS.PSEL = sel;  // ok
					MPC::PC7PFS.PSEL = sel;  // ok
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
					MPC::PB6PFS.PSEL = sel;  // ok
					MPC::PB7PFS.PSEL = sel;  // ok
					PORTB::PMR.B6 = enable;
					PORTB::PMR.B7 = enable;
				}
				break;
			case peripheral::SCI10:
			// P81/RXD10
			// P82/TXD10
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT8::PMR.B1 = 0;
					PORT8::PMR.B2 = 0;
					MPC::P81PFS.PSEL = sel;  // ok
					MPC::P82PFS.PSEL = sel;  // ok
					PORT8::PMR.B1 = enable;
					PORT8::PMR.B2 = enable;
				}
				break;
			case peripheral::SCI11:
			// P76/RXD11
			// P77/TXD11
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT7::PMR.B6 = 0;
					PORT7::PMR.B7 = 0;
					MPC::P76PFS.PSEL = sel;  // ok
					MPC::P77PFS.PSEL = sel;  // ok
					PORT7::PMR.B6 = enable;
					PORT7::PMR.B7 = enable;
				}
				break;
			case peripheral::SCI12:
			// PE2/RXD12
			// PE1/TXD12
				{
					uint8_t sel = enable ? 0b0'1100 : 0;
					PORTE::PMR.B2 = 0;
					PORTE::PMR.B1 = 0;
					MPC::PE2PFS.PSEL = sel;  // ok
					MPC::PE1PFS.PSEL = sel;  // ok
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
			case peripheral::CAN0:
			// PD2/CRX0
			// PD1/CTX0
				{
					uint8_t sel = enable ? 0b1'0000 : 0;
					PORTD::PMR.B2 = 0;
					PORTD::PMR.B1 = 0;
					MPC::PD2PFS.PSEL = sel;  // ok
					MPC::PD1PFS.PSEL = sel;  // ok
					PORTD::PMR.B2 = enable;
					PORTD::PMR.B1 = enable;
				}
				break;
			case peripheral::CAN1:
			// P55/CRX1
			// P54/CTX1
				{
					uint8_t sel = enable ? 0b1'0000 : 0;
					PORT5::PMR.B5 = 0;
					PORT5::PMR.B4 = 0;
					MPC::P55PFS.PSEL = sel;  // ok
					MPC::P54PFS.PSEL = sel;  // ok
					PORT5::PMR.B5 = enable;
					PORT5::PMR.B4 = enable;
				}
				break;

			case peripheral::RSPI0:
			// PB0/RSPCKA
			// PA6/MOSIA
			// PA7/MISOA
				{
					uint8_t sel = enable ? 0b0'1101 : 0;
					PORTB::PMR.B0 = 0;
					PORTA::PMR.B6 = 0;
					PORTA::PMR.B7 = 0;
					MPC::PB0PFS.PSEL = sel;  // ok
					MPC::PA6PFS.PSEL = sel;  // ok
					MPC::PA7PFS.PSEL = sel;  // ok
					PORTB::PMR.B0 = enable;
					PORTA::PMR.B6 = enable;
					PORTA::PMR.B7 = enable;
				}
				break;
			case peripheral::RSPI1:
			// PE1/RSPCKB
			// PE2/MOSIB
			// PE3/MISOB
				{
					PORTE::PMR.B1 = 0;
					PORTE::PMR.B2 = 0;
					PORTE::PMR.B3 = 0;
					MPC::PE1PFS.PSEL = enable ? 0b0'1110 : 0;  // ok
					MPC::PE2PFS.PSEL = enable ? 0b0'1110 : 0;  // ok
					MPC::PE3PFS.PSEL = enable ? 0b0'1101 : 0;  // ok
					PORTE::PMR.B1 = enable;
					PORTE::PMR.B2 = enable;
					PORTE::PMR.B3 = enable;
				}
				break;

			case peripheral::SCI0:
			// P33/RXD0
			// P32/TXD0
				{
					uint8_t sel = enable ? 0b0'1011 : 0;
					PORT3::PMR.B3 = 0;
					PORT3::PMR.B2 = 0;
					MPC::P33PFS.PSEL = sel;  // ok
					MPC::P32PFS.PSEL = sel;  // ok
					PORT3::PMR.B3 = enable;
					PORT3::PMR.B2 = enable;
				}
				break;
			case peripheral::SCI1:
			// P30/RXD1
			// P26/TXD1
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT3::PMR.B0 = 0;
					PORT2::PMR.B6 = 0;
					MPC::P30PFS.PSEL = sel;  // ok
					MPC::P26PFS.PSEL = sel;  // ok
					PORT3::PMR.B0 = enable;
					PORT2::PMR.B6 = enable;
				}
				break;
			case peripheral::SCI2:
			// P12/RXD2
			// P13/TXD2
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT1::PMR.B2 = 0;
					PORT1::PMR.B3 = 0;
					MPC::P12PFS.PSEL = sel;  // ok
					MPC::P13PFS.PSEL = sel;  // ok
					PORT1::PMR.B2 = enable;
					PORT1::PMR.B3 = enable;
				}
				break;
			case peripheral::SCI3:
			// P25/RXD2
			// P23/TXD2
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT2::PMR.B5 = 0;
					PORT2::PMR.B3 = 0;
					MPC::P25PFS.PSEL = sel;  // ok
					MPC::P23PFS.PSEL = sel;  // ok
					PORT2::PMR.B5 = enable;
					PORT2::PMR.B3 = enable;
				}
				break;
			case peripheral::SCI5:
			// PC2/RXD2
			// PC3/TXD2
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT2::PMR.B5 = 0;
					PORT2::PMR.B3 = 0;
					MPC::P25PFS.PSEL = sel;  // ok
					MPC::P23PFS.PSEL = sel;  // ok
					PORT2::PMR.B5 = enable;
					PORT2::PMR.B3 = enable;
				}
				break;
			case peripheral::SCI6:
			// P33/RXD2
			// P32/TXD2
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT2::PMR.B5 = 0;
					PORT2::PMR.B3 = 0;
					MPC::P25PFS.PSEL = sel;  // ok
					MPC::P23PFS.PSEL = sel;  // ok
					PORT2::PMR.B5 = enable;
					PORT2::PMR.B3 = enable;
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
					MPC::PC5PFS.PSEL = sel;  // ok
					MPC::PC6PFS.PSEL = sel;  // ok
					MPC::PC7PFS.PSEL = sel;  // ok
					PORTC::PMR.B5 = enable;
					PORTC::PMR.B6 = enable;
					PORTC::PMR.B7 = enable;
				}
				break;
			case peripheral::RSPI1:
			// PE5/RSPCKB
			// PE6/MOSIB
			// PE7/MISOB
				{
					uint8_t sel = enable ? 0b0'1110 : 0;
					PORTE::PMR.B5 = 0;
					PORTE::PMR.B6 = 0;
					PORTE::PMR.B7 = 0;
					MPC::PE5PFS.PSEL = sel;  // ok
					MPC::PE6PFS.PSEL = sel;  // ok
					MPC::PE7PFS.PSEL = sel;  // ok
					PORTE::PMR.B5 = enable;
					PORTE::PMR.B6 = enable;
					PORTE::PMR.B7 = enable;
				}
				break;

			case peripheral::SCI1:  // Serial Boot Mode
			// PF2/RXD1
			// PF0/TXD1
				{
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORTF::PMR.B2 = 0;
					PORTF::PMR.B0 = 0;
					MPC::PF2PFS.PSEL = sel;  // ok
					MPC::PF0PFS.PSEL = sel;  // ok
					PORTF::PMR.B2 = enable;
					PORTF::PMR.B0 = enable;
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
