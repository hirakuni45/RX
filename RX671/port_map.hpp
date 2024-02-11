#pragma once
//=========================================================================//
/*!	@file
	@brief	RX671 グループ・ポート・マッピング @n
			・ペリフェラル型に従って、ポートの設定をグループ化して設定 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX671/peripheral.hpp"
#include "RX671/port.hpp"
#include "RX671/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map : public port_map_order {

		static bool sub_1st_(peripheral pre, bool enable, ORDER opt)
		{
			bool ret = true;
			switch(pre) {
			case peripheral::SCI0:
				{
					// RXD0: P21
					// TXD0: P20
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;
					PORT2::PMR.B1 = enable;
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = sel;
					PORT2::PMR.B0 = enable;
				}
				break;
			case peripheral::SCI1:
				{
					// RXD1: P15
					// TXD1: P16
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;
					PORT1::PMR.B5 = enable;
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;
					PORT1::PMR.B6 = enable;
				}
				break;
			case peripheral::SCI2:
				{
					// RXD2: P12
					// TXD2: P13
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT1::PMR.B2 = 0;
					MPC::P12PFS.PSEL = sel;
					PORT1::PMR.B2 = enable;
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;
					PORT1::PMR.B3 = enable;
				}
				break;
			case peripheral::SCI3:
				{
					// RXD3: P16
					// TXD3: P17
					uint8_t sel = enable ? 0b00'1011 : 0;  // ok
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;
					PORT1::PMR.B6 = enable;
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B7 = enable;
				}
				break;
			case peripheral::SCI4:
				{
					// RXD4: PB0
					// TXD4: PB1
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;
					PORTB::PMR.B0 = enable;
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;
					PORTB::PMR.B1 = enable;
				}
				break;
			case peripheral::SCI5:
				{
					// RXD5: PA2
					// TXD5: PA4
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = sel;
					PORTA::PMR.B2 = enable;
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B4 = enable;
				}
				break;
			case peripheral::SCI6:
				{
					// RXD6: P01
					// TXD6: P00
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT0::PMR.B1 = 0;
					MPC::P01PFS.PSEL = sel;
					PORT0::PMR.B1 = enable;
					PORT0::PMR.B0 = 0;
					MPC::P00PFS.PSEL = sel;
					PORT0::PMR.B0 = enable;
				}
				break;
			case peripheral::SCI7:
				{
					// RXD7: P92
					// TXD7: P55
					uint8_t sel = enable ? 0b00'1010 : 0;
					PORT9::PMR.B2 = 0;
					MPC::P92PFS.PSEL = sel;  // ok
					PORT9::PMR.B2 = enable;
					PORT5::PMR.B5 = 0;
					MPC::P55PFS.PSEL = sel;  // ok
					PORT5::PMR.B5 = enable;
				}
				break;
			case peripheral::SCI8:
				{
					// RXD8: PC6
					// TXD8: PC7
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;
					PORTC::PMR.B6 = enable;
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;
					PORTC::PMR.B7 = enable;
				}
				break;
			case peripheral::SCI9:
				{
					// RXD9: PB6
					// TXD9: PB7
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;
					PORTB::PMR.B6 = enable;
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;
					PORTB::PMR.B7 = enable;
				}
				break;
			case peripheral::SCI10:
				{
					// RXD10: P81
					// TXD10: P82
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT8::PMR.B1 = 0;
					MPC::P81PFS.PSEL = sel;
					PORT8::PMR.B1 = enable;
					PORT8::PMR.B2 = 0;
					MPC::P82PFS.PSEL = sel;
					PORT8::PMR.B2 = enable;
				}
				break;

			case peripheral::SCI11:
				{
					// RXD11: P76
					// TXD11: P77
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;
					PORT7::PMR.B6 = enable;
					PORT7::PMR.B7 = 0;
					MPC::P77PFS.PSEL = sel;
					PORT7::PMR.B7 = enable;
				}
				break;
			case peripheral::SCI12:
				{
					// RXD12: PE2
					// TXD12: PE1
					uint8_t sel = enable ? 0b00'1100 : 0;  // ok
					PORTE::PMR.B2 = 0;
					MPC::PE2PFS.PSEL = sel;
					PORTE::PMR.B2 = enable;
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = sel;
					PORTE::PMR.B1 = enable;
				}
				break;

			case peripheral::RSCI10:
				{
					// RXD010: P81
					// TXD010: P82
					uint8_t sel = enable ? 0b10'1100 : 0;  // ok
					PORT8::PMR.B1 = 0;
					MPC::P81PFS.PSEL = sel;
					PORT8::PMR.B1 = enable;
					PORT8::PMR.B2 = 0;
					MPC::P82PFS.PSEL = sel;
					PORT8::PMR.B2 = enable;
				}
				break;
			case peripheral::RSCI11:
				{
					// RXD011: P76
					// TXD011: P77
					uint8_t sel = enable ? 0b10'1100 : 0;  // ok
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;
					PORT7::PMR.B6 = enable;
					PORT7::PMR.B7 = 0;
					MPC::P77PFS.PSEL = sel;
					PORT7::PMR.B7 = enable;
				}
				break;

			case peripheral::RIIC0:
				{
					// SCL0: P12
					// SDA0: P13
					uint8_t sel = enable ? 0b00'1111 : 0;  // ok
					PORT1::PMR.B2 = 0;
					MPC::P12PFS.PSEL = sel;
					PORT1::PMR.B2 = enable;
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;
					PORT1::PMR.B3 = enable;
				}
				break;
			case peripheral::RIIC1:
				{
					// SCL1: P21
					// SDA1: P20
					uint8_t sel = enable ? 0b00'1111 : 0;  // ok
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;
					PORT2::PMR.B1 = enable;
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = sel;
					PORT2::PMR.B0 = enable;
				}
				break;
			case peripheral::RIIC2:
				{
					// SCL2: P16
					// SDA2: P17
					uint8_t sel = enable ? 0b00'1111 : 0;  // ok
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;
					PORT1::PMR.B6 = enable;
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B7 = enable;
				}
				break;

			case peripheral::CAN0:
				{
					// CRX0: P33
					// CTX0: P32
					uint8_t sel = enable ? 0b01'0000 : 0;  // ok
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;
					PORT3::PMR.B3 = enable;
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;
					PORT3::PMR.B2 = enable;
				}
				break;
			case peripheral::CAN1:
				{
					// CRX1-DS: P15
					// CTX1:    P14
					uint8_t sel = enable ? 0b01'0000 : 0;  // ok
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;
					PORT1::PMR.B5 = enable;
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;
					PORT1::PMR.B4 = enable;
				}
				break;

			case peripheral::RSPI0:
				{
					// RSPCKA: PA5
					// MOSIA:  PA6
					// MISOA:  PA7
					uint8_t sel = enable ? 0b00'1101 : 0;  // ok
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;
					PORTA::PMR.B5 = enable;
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = sel;
					PORTA::PMR.B6 = enable;
					PORTA::PMR.B7 = 0;
					MPC::PA7PFS.PSEL = sel;
					PORTA::PMR.B7 = enable;
				}
				break;
			case peripheral::RSPI1:
				{
					// RSPCKB: P27
					// MOSIB:  P26
					// MISOB:  P30
					uint8_t sel = enable ? 0b00'1101 : 0;  // ok
					PORT2::PMR.B7 = 0;
					MPC::P27PFS.PSEL = sel;
					PORT2::PMR.B7 = enable;
					PORT2::PMR.B6 = 0;
					MPC::P26PFS.PSEL = sel;
					PORT2::PMR.B6 = enable;
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = sel;
					PORT3::PMR.B0 = enable;
				}
				break;
			case peripheral::RSPI2:
				{
					// RSPCKA: P56
					// MOSIA:  P54
					// MISOA:  P55
					uint8_t sel = enable ? 0b00'1101 : 0;  // ok
					PORT5::PMR.B6 = 0;
					MPC::P56PFS.PSEL = sel;
					PORT5::PMR.B6 = enable;
					PORT5::PMR.B4 = 0;
					MPC::P54PFS.PSEL = sel;
					PORT5::PMR.B4 = enable;
					PORT5::PMR.B5 = 0;
					MPC::P55PFS.PSEL = sel;
					PORT5::PMR.B5 = enable;
				}
				break;
			case peripheral::RSPIA0:
				{
					// RSPCK0: PA5
					// MOSI0:  PA6
					// MISO0:  PA7
					uint8_t sel = enable ? 0b00'1110 : 0;  // ok
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;
					PORTA::PMR.B5 = enable;
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = sel;
					PORTA::PMR.B6 = enable;
					PORTA::PMR.B7 = 0;
					MPC::PA7PFS.PSEL = sel;
					PORTA::PMR.B7 = enable;
				}
				break;


#if 0
			case peripheral::SSIE0:
				{
					uint8_t sel = enable ? 0b010111 : 0;
					PORT0::PMR.B0 = 0;
					MPC::P00PFS.PSEL = sel;  // AUDIO_CLK
					PORT0::PMR.B0 = enable;
					PORT0::PMR.B1 = 0;
					MPC::P01PFS.PSEL = sel;  // SSIBCK0
					PORT0::PMR.B1 = enable;
					PORTF::PMR.B5 = 0;
					MPC::PF5PFS.PSEL = sel;  // SSILRCK0
					PORTF::PMR.B5 = enable;
					PORTJ::PMR.B5 = 0;
					MPC::PJ5PFS.PSEL = sel;  // SSIRXD0
					PORTJ::PMR.B5 = enable;
					PORTJ::PMR.B3 = 0;
					MPC::PJ3PFS.PSEL = sel;  // SSITXD0
					PORTJ::PMR.B3 = enable;
				}
				break;

			case peripheral::QSPIX:
				{
					uint8_t sel = enable ? 0b011011 : 0;
					PORT8::PMR.B1 = 0;
					MPC::P81PFS.PSEL = sel;  // QIO3-A   (P81 LQFP176: 80)
					PORT8::PMR.B1 = enable;
					PORT8::PMR.B0 = 0;
					MPC::P80PFS.PSEL = sel;  // QIO2-A   (P80 LQFP176: 81)
					PORT8::PMR.B0 = enable;
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;  // QIO1-A   (PC4 LQFP176: 82)
					PORTC::PMR.B4 = enable;
					PORTC::PMR.B3 = 0;
					MPC::PC3PFS.PSEL = sel;  // QIO0-A   (PC3 LQFP176: 83)
					PORTC::PMR.B3 = enable;
					PORT7::PMR.B7 = 0;
					MPC::P77PFS.PSEL = sel;  // QSPCLK-A (P77 LQFP176: 84)
					PORT7::PMR.B7 = enable;
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;  // QSPSSL-A (P76 LQFP176: 85)
					PORT7::PMR.B6 = enable;
				}
				break;
#endif
			default:
				ret = false;
				break;
			}
			return ret;
		}


		static bool sub_2nd_(peripheral t, bool enable, ORDER opt)
		{
			bool ret = true;
			switch(t) {
			case peripheral::SCI0:
				{
					// RXD0: P33
					// TXD0: P32
					uint8_t sel = enable ? 0b00'1011 : 0;  // ok
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;
					PORT3::PMR.B3 = enable;
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;
					PORT3::PMR.B2 = enable;
				}
				break;
			case peripheral::SCI1:
				{
					// RXD1: P30
					// TXD1: P26
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = sel;
					PORT3::PMR.B0 = enable;
					PORT2::PMR.B6 = 0;
					MPC::P26PFS.PSEL = sel;
					PORT2::PMR.B6 = enable;
				}
				break;
			case peripheral::SCI2:
				{
					// RXD2: P52
					// TXD2: P50
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT5::PMR.B2 = 0;
					MPC::P52PFS.PSEL = sel;
					PORT5::PMR.B2 = enable;
					PORT5::PMR.B0 = 0;
					MPC::P50PFS.PSEL = sel;
					PORT5::PMR.B0 = enable;
				}
				break;
			case peripheral::SCI3:
				{
					// RXD3: P25
					// TXD3: P23
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT2::PMR.B5 = 0;
					MPC::P25PFS.PSEL = sel;
					PORT2::PMR.B5 = enable;
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;
					PORT2::PMR.B3 = enable;
				}
				break;
			case peripheral::SCI5:
				{
					// RXD5: PA3
					// TXD5: PC3
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = sel;
					PORTA::PMR.B3 = enable;
					PORTC::PMR.B3 = 0;
					MPC::PC3PFS.PSEL = sel;
					PORTC::PMR.B3 = enable;
				}
				break;
			case peripheral::SCI6:
				{
					// RXD6: P33
					// TXD6: P32
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;
					PORT3::PMR.B3 = enable;
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;
					PORT3::PMR.B2 = enable;
				}
				break;
			case peripheral::SCI7:
				{
					// RXD7: P92
					// TXD7: P90
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT9::PMR.B2 = 0;
					MPC::P92PFS.PSEL = sel;
					PORT9::PMR.B2 = enable;
					PORT9::PMR.B0 = 0;
					MPC::P90PFS.PSEL = sel;
					PORT9::PMR.B0 = enable;
				}
				break;
			case peripheral::SCI10:
				{
					// RXD10: P86
					// TXD10: P87
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT8::PMR.B6 = 0;
					MPC::P86PFS.PSEL = sel;
					PORT8::PMR.B6 = enable;
					PORT8::PMR.B7 = 0;
					MPC::P87PFS.PSEL = sel;
					PORT8::PMR.B7 = enable;
				}
				break;
			case peripheral::SCI11:
				{
					// RXD11: PB6
					// TXD11: PB7
					uint8_t sel = enable ? 0b10'0100 : 0;  // ok
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;
					PORTB::PMR.B6 = enable;
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;
					PORTB::PMR.B7 = enable;
				}
				break;
			case peripheral::SCI12:
				{
					// RXD12: PA2
					// TXD12: PA4
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = sel;
					PORTA::PMR.B2 = enable;
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B4 = enable;
				}
				break;

			case peripheral::RSCI10:
				{
					// RXD010: P86
					// TXD010: P87
					uint8_t sel = enable ? 0b10'1100 : 0;  // ok
					PORT8::PMR.B6 = 0;
					MPC::P86PFS.PSEL = sel;
					PORT8::PMR.B6 = enable;
					PORT8::PMR.B7 = 0;
					MPC::P87PFS.PSEL = sel;
					PORT8::PMR.B7 = enable;
				}
				break;
			case peripheral::RSCI11:
				{
					// RXD011: PB6
					// TXD011: PB7
					uint8_t sel = enable ? 0b10'1100 : 0;  // ok
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;
					PORTB::PMR.B6 = enable;
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;
					PORTB::PMR.B7 = enable;
				}
				break;

			case peripheral::CAN0:
				{
					// CRX0: PD2
					// CTX0: PD1
					uint8_t sel = enable ? 0b01'0000 : 0;  // ok
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;
					PORTD::PMR.B2 = enable;
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;
					PORTD::PMR.B1 = enable;
				}
				break;
			case peripheral::CAN1:
				{
					// CRX1: P55
					// CTX1: P54
					uint8_t sel = enable ? 0b01'0000 : 0;  // ok
					PORT5::PMR.B5 = 0;
					MPC::P55PFS.PSEL = sel;
					PORT5::PMR.B5 = enable;
					PORT5::PMR.B4 = 0;
					MPC::P54PFS.PSEL = sel;
					PORT5::PMR.B4 = enable;
				}
				break;

			case peripheral::RSPI0:
				{
					// RSPCKA: PC5
					// MOSIA:  PC6
					// MISOA:  PC7
					uint8_t sel = enable ? 0b00'1101 : 0;  // ok
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;
					PORTC::PMR.B5 = enable;
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;
					PORTC::PMR.B6 = enable;
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;
					PORTC::PMR.B7 = enable;
				}
				break;
			case peripheral::RSPI1:
				{
					// RSPCKB: PE5
					// MOSIB:  PE6
					// MISOB:  PE7
					uint8_t sel = enable ? 0b00'1101 : 0;  // ok
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = sel;
					PORTE::PMR.B5 = enable;
					PORTE::PMR.B6 = 0;
					MPC::PE6PFS.PSEL = sel;
					PORTE::PMR.B6 = enable;
					PORTE::PMR.B7 = 0;
					MPC::PE7PFS.PSEL = sel;
					PORTE::PMR.B7 = enable;
				}
				break;
			case peripheral::RSPI2:
				{
					// RSPCKA: PD3
					// MOSIA:  PD1
					// MISOA:  PD2
					uint8_t sel = enable ? 0b00'1101 : 0;  // ok
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = sel;
					PORTD::PMR.B3 = enable;
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;
					PORTD::PMR.B1 = enable;
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;
					PORTD::PMR.B2 = enable;
				}
				break;
			case peripheral::RSPIA0:
				{
					// RSPCK0: PC5
					// MOSI0:  PC6
					// MISO0:  PC7
					uint8_t sel = enable ? 0b00'1110 : 0;  // ok
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;
					PORTC::PMR.B5 = enable;
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;
					PORTC::PMR.B6 = enable;
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;
					PORTC::PMR.B7 = enable;
				}
				break;
#if 0
			case peripheral::QSPI:  // QSPI-B
				{
					uint8_t sel = enable ? 0b011011 : 0;
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;  // QIO1-B   (PD7 LQFP176: 143)
					PORTD::PMR.B7 = enable;
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;  // QIO0-B   (PD6 LQFP176: 145)
					PORTD::PMR.B6 = enable;
					PORTD::PMR.B5 = 0;
					MPC::PD5PFS.PSEL = sel;  // QSPCLK-B (PD5 LQFP176: 147)
					PORTD::PMR.B5 = enable;
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = sel;  // QIO3-B   (PD3 LQFP176: 150)
					PORTD::PMR.B3 = enable;
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;  // QIO2-B   (PD2 LQFP176: 154)
					PORTD::PMR.B2 = enable;
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;  // QSSL-B   (PD4 LQFP176: 142)
					PORTD::PMR.B4 = enable;
				}
				break;
#endif
			default:
				ret = false;
				break;
			}
			return ret;
		}


		static bool sub_3rd_(peripheral per, bool enable, ORDER opt)
		{
			bool ret = true;
			switch(per) {
			case peripheral::SCI5:
				{
					// RXD5: PC2
					// TXD5: PC3
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = sel;
					PORTC::PMR.B2 = enable;
					PORTC::PMR.B3 = 0;
					MPC::PC3PFS.PSEL = sel;
					PORTC::PMR.B3 = enable;
				}
				break;
			case peripheral::SCI6:
				{
					// RXD6: PB0
					// TXD6: PB1
					uint8_t sel = enable ? 0b00'1011 : 0;  // ok
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;
					PORTB::PMR.B0 = enable;
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;
					PORTB::PMR.B1 = enable;
				}
				break;
			case peripheral::SCI10:
				{
					// RXD10: PC6
					// TXD10: PC7
					uint8_t sel = enable ? 0b01'0100 : 0;  // ok
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;
					PORTC::PMR.B6 = enable;
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;
					PORTC::PMR.B7 = enable;
				}
				break;

			case peripheral::RSCI10:
				{
					// RXD010: PC6
					// TXD010: PC7
					uint8_t sel = enable ? 0b10'1100 : 0;  // ok
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;
					PORTC::PMR.B6 = enable;
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;
					PORTC::PMR.B7 = enable;
				}
				break;
			case peripheral::RSCI11:
				{
					// RXD011: PC0
					// TXD011: PC1
					uint8_t sel = enable ? 0b10'1100 : 0;  // ok
					PORTC::PMR.B0 = 0;
					MPC::PC0PFS.PSEL = sel;
					PORTC::PMR.B0 = enable;
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = sel;
					PORTC::PMR.B1 = enable;
				}
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}


		static bool sdhi_1st_(SDHI_STATE state) noexcept
		{
			bool ret = true;
			bool enable = true;
			uint8_t sel = enable ? 0b011010 : 0;
			switch(state) {
			case SDHI_STATE::START:
				MPC::P80PFS.PSEL = sel;  // SDHI_WP (81)
				PORT8::PMR.B0 = enable;
				MPC::P81PFS.PSEL = sel;  // SDHI_CD (80)
				PORT8::PMR.B1 = enable;
				break;

			case SDHI_STATE::EJECT:
				enable = 0;
				sel = 0;
			case SDHI_STATE::INSERT:
				MPC::PC2PFS.PSEL = sel;  // SDHI_D3 (86)
				PORTC::PMR.B2 = enable;
				MPC::PC3PFS.PSEL = sel;  // SDHI_D0 (83)
				PORTC::PMR.B3 = enable;
				MPC::PC4PFS.PSEL = sel;  // SDHI_D1 (82)
				PORTC::PMR.B4 = enable;
				MPC::P75PFS.PSEL = sel;  // SDHI_D2 (87)
				PORT7::PMR.B5 = enable;
				MPC::P76PFS.PSEL = sel;  // SDHI_CMD (85)
				PORT7::PMR.B6 = enable;
				MPC::P77PFS.PSEL = sel;  // SDHI_CLK (84)
				PORT7::PMR.B7 = enable;
				break;

			case SDHI_STATE::DESTROY:
				enable = 0;
				sel = 0;
				PORT8::PMR.B0 = enable;
				MPC::P80PFS.PSEL = sel;  // SDHI_WP (81)
				PORT8::PMR.B1 = enable;
				MPC::P81PFS.PSEL = sel;  // SDHI_CD (80)
				PORTC::PMR.B2 = enable;
				MPC::PC2PFS.PSEL = sel;  // SDHI_D3 (86)
				PORTC::PMR.B3 = enable;
				MPC::PC3PFS.PSEL = sel;  // SDHI_D0 (83)
				PORTC::PMR.B4 = enable;
				MPC::PC4PFS.PSEL = sel;  // SDHI_D1 (82)
				PORT7::PMR.B5 = enable;
				MPC::P75PFS.PSEL = sel;  // SDHI_D2 (87)
				PORT7::PMR.B6 = enable;
				MPC::P76PFS.PSEL = sel;  // SDHI_CMD (85)
				PORT7::PMR.B7 = enable;
				MPC::P77PFS.PSEL = sel;  // SDHI_CLK (84)
				break;

			default:
				ret = false;
			}
			return ret;
		}


		static bool sdhi_2nd_(SDHI_STATE state) noexcept
		{
			bool ret = true;
			bool enable = true;
			uint8_t sel = 0b011010;
			switch(state) {
			case SDHI_STATE::START:
				PORT2::PMR.B5 = 0;
				MPC::P25PFS.PSEL = sel;  // SDHI_CD P25(32)
				PORT2::PMR.B5 = enable;
				break;

			case SDHI_STATE::INSERT:
				PORT2::PMR.B0 = 0;
				MPC::P20PFS.PSEL = sel;  // SDHI_CMD-C P20(37)
				PORT2::PMR.B0 = enable;
				PORT2::PMR.B1 = 0;
				MPC::P21PFS.PSEL = sel;  // SDHI_CLK-C P21(36)
				PORT2::PMR.B1 = enable;
				break;

			case SDHI_STATE::BUS:
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;  // SDHI_D0-C  P22(35)
				PORT2::PMR.B2 = enable;
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;  // SDHI_D1-C  P23(34)
				PORT2::PMR.B3 = enable;
				PORT8::PMR.B7 = 0;
				MPC::P87PFS.PSEL = sel;  // SDHI_D2-C  P87(39)
				PORT8::PMR.B7 = enable;
				PORT1::PMR.B7 = 0;
				MPC::P17PFS.PSEL = sel;  // SDHI_D3-C  P17(38)
				PORT1::PMR.B7 = enable;
				break;

			case SDHI_STATE::DESTROY:
				sel = 0;
///				PORT2::PMR.B4 = 0;
///				MPC::P24PFS.PSEL = sel;  // SDHI_WP P24(33)
				PORT2::PMR.B5 = 0;
				MPC::P25PFS.PSEL = sel;  // SDHI_CD P25(32)

			case SDHI_STATE::EJECT:
				sel = 0;
				PORT2::PMR.B0 = 0;
				MPC::P20PFS.PSEL = sel;  // SDHI_CMD-C P20(37)
				PORT2::PMR.B1 = 0;
				MPC::P21PFS.PSEL = sel;  // SDHI_CLK-C P21(36)
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;  // SDHI_D0-C  P22(35)
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;  // SDHI_D1-C  P23(34)
				PORT8::PMR.B7 = 0;
				MPC::P87PFS.PSEL = sel;  // SDHI_D2-C  P87(39)
				PORT1::PMR.B7 = 0;
				MPC::P17PFS.PSEL = sel;  // SDHI_D3-C  P17(38)
				break;

			default:
				ret = false;
			}
			return ret;
		}


		static bool sdhi_3rd_(SDHI_STATE state) noexcept
		{
			bool ret = true;
			bool enable = true;
			uint8_t sel = 0b011010;
			switch(state) {
			case SDHI_STATE::START:
///				PORT2::PMR.B4 = 0;
///				MPC::P24PFS.PSEL = sel;  // SDHI_WP P24(33)
///				PORT2::PMR.B4 = enable;
				PORT2::PMR.B5 = 0;
				MPC::P25PFS.PSEL = sel;  // SDHI_CD P25(32)
				PORT2::PMR.B5 = enable;
				break;

			case SDHI_STATE::INSERT:
				PORT2::PMR.B0 = 0;
				MPC::P20PFS.PSEL = sel;  // SDHI_CMD-C P20(37)
				PORT2::PMR.B0 = enable;
				PORT2::PMR.B1 = 0;
				MPC::P21PFS.PSEL = sel;  // SDHI_CLK-C P21(36)
				PORT2::PMR.B1 = enable;
				break;

			case SDHI_STATE::BUS:
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;  // SDHI_D0-C  P22(35)
				PORT2::PMR.B2 = enable;
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;  // SDHI_D1-C  P23(34)
				PORT2::PMR.B3 = enable;
				PORT8::PMR.B7 = 0;
				MPC::P87PFS.PSEL = sel;  // SDHI_D2-C  P87(39)
				PORT8::PMR.B7 = enable;
				PORT1::PMR.B7 = 0;
				MPC::P17PFS.PSEL = sel;  // SDHI_D3-C  P17(38)
				PORT1::PMR.B7 = enable;
				break;

			case SDHI_STATE::DESTROY:
				sel = 0;
///				PORT2::PMR.B4 = 0;
///				MPC::P24PFS.PSEL = sel;  // SDHI_WP P24(33)
				PORT2::PMR.B5 = 0;
				MPC::P25PFS.PSEL = sel;  // SDHI_CD P25(32)

			case SDHI_STATE::EJECT:
				sel = 0;
				PORT2::PMR.B0 = 0;
				MPC::P20PFS.PSEL = sel;  // SDHI_CMD-C P20(37)
				PORT2::PMR.B1 = 0;
				MPC::P21PFS.PSEL = sel;  // SDHI_CLK-C P21(36)
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;  // SDHI_D0-C  P22(35)
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;  // SDHI_D1-C  P23(34)
				PORT8::PMR.B7 = 0;
				MPC::P87PFS.PSEL = sel;  // SDHI_D2-C  P87(39)
				PORT1::PMR.B7 = 0;
				MPC::P17PFS.PSEL = sel;  // SDHI_D3-C  P17(38)
				break;

			default:
				ret = false;
			}
			return ret;
		}

	public:
#if 0
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  USB ポート専用切り替え
			@param[in]	sel		USB ポート選択
			@param[in]	ena		無効にする場合「false」
			@param[in]	odr		ポート・マップ・オプション（ポート候補）
			@return 無効な場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn_usb(USB_PORT sel, bool ena = true, ORDER odr = ORDER::FIRST) noexcept
		{
			if(odr == ORDER::BYPASS) return false;

			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = true;
			switch(sel) {
			case USB_PORT::VBUS:
				// P16 o
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = ena ? 0b010001 : 0;
					PORT1::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::EXICEN:
				// P21 o
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = ena ? 0b010011 : 0;
					PORT2::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::VBUSEN:
				// P16 o
				// P24 o
				// P32 o
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = ena ? 0b010010 : 0;
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = ena ? 0b010011 : 0;
					PORT2::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = ena ? 0b010011 : 0;
					PORT3::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::OVRCURA:
				// P14 o
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = ena ? 0b010010 : 0;
					PORT1::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::OVRCURB:
				// P16 o
				// P22 o
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = ena ? 0b010011 : 0;
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = ena ? 0b010011 : 0;
					PORT2::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::ID:
				// P20 o
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = ena ? 0b010011 : 0;
					PORT2::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			default:
				ret = false;
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}
#endif
		//-----------------------------------------------------------------//
		/*!
			@brief  周辺機器に切り替える
			@param[in]	per	周辺機器タイプ
			@param[in]	ena	無効にする場合「false」
			@param[in]	odr	ポート・マップ・オーダー
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral per, bool ena = true, ORDER odr = ORDER::FIRST) noexcept
		{
			if(odr == ORDER::BYPASS) return false;

			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			switch(odr) {
			case ORDER::FIRST:
				ret = sub_1st_(per, ena, odr);
				break;
			case ORDER::SECOND:
				ret = sub_2nd_(per, ena, odr);
				break;
			case ORDER::THIRD:
				ret = sub_3rd_(per, ena, odr);
				break;
			default:
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  SDHI ポート専用切り替え
			@param[in]	sit		SHDI 候補
			@param[in]	odr		ポート・マップ候補
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn_sdhi(SDHI_STATE state, ORDER odr = ORDER::FIRST) noexcept
		{
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = 0;
			switch(odr) {
			case ORDER::FIRST:
				ret = sdhi_1st_(state);
				break;
			case ORDER::SECOND:
				ret = sdhi_2nd_(state);
				break;
			case ORDER::THIRD:
				ret = sdhi_3rd_(state);
				break;
			default:
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  SDHI クロック・ポートの状態を取得
			@param[in]	odr		ポート・マップ候補
			@return SDHI クロック・ポートの状態
		*/
		//-----------------------------------------------------------------//
		static bool probe_sdhi_clock(ORDER odr) noexcept
		{
			bool ret = 0;
			switch(odr) {
			case ORDER::FIRST:
				ret = PORT2::PIDR.B1();
				break;
			case ORDER::SECOND:
				ret = PORT7::PIDR.B7();
				break;
			case ORDER::THIRD:
				ret = PORTD::PIDR.B5();
				break;
			default:
				break;
			}
			return ret;
		}
	};
}
