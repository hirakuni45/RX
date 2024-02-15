#pragma once
//=========================================================================//
/*!	@file
	@brief	RX631/RX63N グループ・ポート・マッピング @n
			BOOT Mode Serial: @n
			  PF2/RXD1 (177/176 Pin), P30/RXD1(145, 144, 100, 64, 48 Pin)  @n
			  PF0/TXD1 (177/176 Pin), P26/RXD1(145, 144, 100, 64, 48 Pin) 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
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
		@brief  RX631/RX63N ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map : public port_map_order {

		static bool sub_1st_(peripheral per, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			switch(per) {
			case peripheral::SCI0:
				{
					// RXD0: P21
					// TXD0: P20
					// SCK0: P22
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT2::PMR.B1 = 0;
					PORT2::ODR.B1 = i2c;
					MPC::P21PFS.PSEL = sel;  // ok
					PORT2::PMR.B1 = enable;
					PORT2::PMR.B0 = 0;
					PORT2::ODR.B0 = i2c;
					MPC::P20PFS.PSEL = sel;  // ok
					PORT2::PMR.B0 = enable;
					if(spi) {
						PORT2::PMR.B2 = 0;
						MPC::P22PFS.PSEL = sel;
						PORT2::PMR.B2 = enable;
					}
				}
				break;
			case peripheral::SCI1:
				{
					// RXD1: P15
					// TXD1: P16
					// SCK1: P17
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT1::PMR.B5 = 0;
					PORT1::ODR.B5 = i2c;
					MPC::P15PFS.PSEL = sel;  // ok
					PORT1::PMR.B5 = enable;
					PORT1::PMR.B6 = 0;
					PORT1::ODR.B6 = i2c;
					MPC::P16PFS.PSEL = sel;  // ok
					PORT1::PMR.B6 = enable;
					if(spi) {
						PORT1::PMR.B7 = 0;
						MPC::P17PFS.PSEL = sel;
						PORT1::PMR.B7 = enable;
					}
				}
				break;
			case peripheral::SCI2:
				{
					// RXD2: P12
					// TXD2: P13
					// SCK2: P11
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT1::PMR.B2 = 0;
					PORT1::ODR.B2 = i2c;
					MPC::P12PFS.PSEL = sel;  // ok
					PORT1::PMR.B2 = enable;
					PORT1::PMR.B3 = 0;
					PORT1::ODR.B3 = i2c;
					MPC::P13PFS.PSEL = sel;  // ok
					PORT1::PMR.B3 = enable;
					if(spi) {
						PORT1::PMR.B1 = 0;
						MPC::P11PFS.PSEL = sel;
						PORT1::PMR.B1 = enable;
					}
				}
				break;
			case peripheral::SCI3:
				{
					// RXD3: P16
					// TXD3: P17
					// SCK3: P15
					uint8_t sel = enable ? 0b0'1011 : 0;
					PORT1::PMR.B6 = 0;
					PORT1::ODR.B6 = i2c;
					MPC::P16PFS.PSEL = sel;  // ok
					PORT1::PMR.B6 = enable;
					PORT1::PMR.B7 = 0;
					PORT1::ODR.B7 = i2c;
					MPC::P17PFS.PSEL = sel;  // ok
					PORT1::PMR.B7 = enable;
					if(spi) {
						PORT1::PMR.B5 = 0;
						MPC::P15PFS.PSEL = sel;
						PORT1::PMR.B5 = enable;
					}
				}
				break;
			case peripheral::SCI4:
				{
					// RXD4: PB0
					// TXD4: PB1
					// SCK4: PB3
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORTB::PMR.B0 = 0;
					PORTB::ODR.B0 = i2c;
					MPC::PB0PFS.PSEL = sel;  // ok
					PORTB::PMR.B0 = enable;
					PORTB::PMR.B1 = 0;
					PORTB::ODR.B1 = i2c;
					MPC::PB1PFS.PSEL = sel;  // ok
					PORTB::PMR.B1 = enable;
					if(spi) {
						PORTB::PMR.B3 = 0;
						MPC::PB3PFS.PSEL = sel;
						PORTB::PMR.B3 = enable;
					}
				}
				break;
			case peripheral::SCI5:
				{
					// RXD5: PA2
					// TXD5: PA4
					// SCK5: PA1
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORTA::PMR.B2 = 0;
					PORTA::ODR.B2 = i2c;
					MPC::PA2PFS.PSEL = sel;  // ok
					PORTA::PMR.B2 = enable;
					PORTA::PMR.B4 = 0;
					PORTA::ODR.B4 = i2c;
					MPC::PA4PFS.PSEL = sel;  // ok
					PORTA::PMR.B4 = enable;
					if(spi) {
						PORTA::PMR.B1 = 0;
						MPC::PA1PFS.PSEL = sel;
						PORTA::PMR.B1 = enable;
					}
				}
				break;
			case peripheral::SCI6:
				{
					// RXD6: P01
					// TXD6: P00
					// SCK6: P02
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT0::PMR.B1 = 0;
					PORT0::ODR.B1 = i2c;
					MPC::P01PFS.PSEL = sel;  // ok
					PORT0::PMR.B1 = enable;
					PORT0::PMR.B0 = 0;
					PORT0::ODR.B0 = i2c;
					MPC::P00PFS.PSEL = sel;  // ok
					PORT0::PMR.B0 = enable;
					if(spi) {
						PORT0::PMR.B2 = 0;
						MPC::P02PFS.PSEL = sel;
						PORT0::PMR.B2 = enable;
					}
				}
				break;
			case peripheral::SCI7:
				{
					// RXD7: P92
					// TXD7: P90
					// SCK7: P91
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT9::PMR.B2 = 0;
					PORT9::ODR.B2 = i2c;
					MPC::P92PFS.PSEL = sel;  // ok
					PORT9::PMR.B2 = enable;
					PORT9::PMR.B0 = 0;
					PORT9::ODR.B0 = i2c;
					MPC::P90PFS.PSEL = sel;  // ok
					PORT9::PMR.B0 = enable;
					if(spi) {
						PORT9::PMR.B1 = 0;
						MPC::P91PFS.PSEL = sel;
						PORT9::PMR.B1 = enable;
					}
				}
				break;
			case peripheral::SCI8:
				{
					// RXD8: PC6
					// TXD8: PC7
					// SCK8: PC5
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORTC::PMR.B6 = 0;
					PORTC::ODR.B6 = i2c;
					MPC::PC6PFS.PSEL = sel;  // ok
					PORTC::PMR.B6 = enable;
					PORTC::PMR.B7 = 0;
					PORTC::ODR.B7 = i2c;
					MPC::PC7PFS.PSEL = sel;  // ok
					PORTC::PMR.B7 = enable;
					if(spi) {
						PORTC::PMR.B5 = 0;
						MPC::PC5PFS.PSEL = sel;
						PORTC::PMR.B5 = enable;
					}
				}
				break;
			case peripheral::SCI9:
				{
					// RXD9: PB6
					// TXD9: PB7
					// SCK9: PB5
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORTB::PMR.B6 = 0;
					PORTB::ODR.B6 = i2c;
					MPC::PB6PFS.PSEL = sel;  // ok
					PORTB::PMR.B6 = enable;
					PORTB::PMR.B7 = 0;
					PORTB::ODR.B7 = i2c;
					MPC::PB7PFS.PSEL = sel;  // ok					
					PORTB::PMR.B7 = enable;
					if(spi) {
						PORTB::PMR.B5 = 0;
						MPC::PB5PFS.PSEL = sel;
						PORTB::PMR.B5 = enable;
					}
				}
				break;
			case peripheral::SCI10:
				{
					// RXD10: P81
					// TXD10: P82
					// SCK10: P80
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT8::PMR.B1 = 0;
					PORTB::ODR.B1 = i2c;
					MPC::P81PFS.PSEL = sel;  // ok
					PORT8::PMR.B1 = enable;
					PORT8::PMR.B2 = 0;
					PORTB::ODR.B2 = i2c;
					MPC::P82PFS.PSEL = sel;  // ok
					PORT8::PMR.B2 = enable;
					if(spi) {
						PORT8::PMR.B0 = 0;
						MPC::P80PFS.PSEL = sel;
						PORT8::PMR.B0 = enable;
					}
				}
				break;
			case peripheral::SCI11:
				{
					// RXD11: P76
					// TXD11: P77
					// SCK11: P75
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT7::PMR.B6 = 0;
					PORT7::ODR.B6 = i2c;
					MPC::P76PFS.PSEL = sel;  // ok
					PORT7::PMR.B6 = enable;
					PORT7::PMR.B7 = 0;
					PORT7::ODR.B7 = i2c;
					MPC::P77PFS.PSEL = sel;  // ok
					PORT7::PMR.B7 = enable;
					if(spi) {
						PORT7::PMR.B5 = 0;
						MPC::P75PFS.PSEL = sel;
						PORT7::PMR.B5 = enable;
					}
				}
				break;
			case peripheral::SCI12:
				{
					// RXD12: PE2
					// TXD12: PE1
					// SCK12: PE0
					uint8_t sel = enable ? 0b0'1100 : 0;
					PORTE::PMR.B2 = 0;
					PORTE::ODR.B2 = i2c;
					MPC::PE2PFS.PSEL = sel;  // ok
					PORTE::PMR.B2 = enable;
					PORTE::PMR.B1 = 0;
					PORTE::ODR.B1 = i2c;
					MPC::PE1PFS.PSEL = sel;  // ok
					PORTE::PMR.B1 = enable;
					if(spi) {
						PORTE::PMR.B0 = 0;
						MPC::PE0PFS.PSEL = sel;
						PORTE::PMR.B0 = enable;
					}
				}
				break;

			case peripheral::RIIC0:
				{
					// SCL0: P12
					// SDA0: P13
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
				{
					// SCL1: P21
					// SDA1: P20
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
				{
					// SCL2: P16
					// SDA2: P17
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
				{
					// SCL3: PC0
					// SDA3: PC1
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
				{
					// CRX0: P33
					// CTX0: P32
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
				{
					// CRX1: P15
					// CTX1: P14
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
				{
					// ※ ROM 容量 1M バイト以下の製品には含まれない
					// CRX2: P67
					// CTX2: P66
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
				{
					// RSPCKA: PA5
					// MOSIA:  P16
					// MISOA:  P17
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
				{
					// RSPCKB: P27
					// MOSIB:  P26
					// MISOB:  P30
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
				{
					// RSPCKC: PD3
					// MOSIC:  PD1
					// MISOC:  PD2
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
			default:
				return false;
				break;
			}
			return true;
		}


		static bool sub_2nd_(peripheral per, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			switch(per) {
			case peripheral::SCI0:
				{
					// RXD0: P33
					// TXD0: P32
					// SCK0: P34
					uint8_t sel = enable ? 0b0'1011 : 0;
					PORT3::PMR.B3 = 0;
					PORT3::ODR.B3 = i2c;
					MPC::P33PFS.PSEL = sel;  // ok
					PORT3::PMR.B3 = enable;
					PORT3::PMR.B2 = 0;
					PORT3::ODR.B2 = i2c;
					MPC::P32PFS.PSEL = sel;  // ok
					PORT3::PMR.B2 = enable;
					if(spi) {
						PORT3::PMR.B4 = 0;
						MPC::P34PFS.PSEL = sel;
						PORT3::PMR.B4 = enable;
					}
				}
				break;
			case peripheral::SCI1:  // for Serial BOOT (145/144/100/64/48 pin)
				{
					// RXD1: P30
					// TXD1: P26
					// SCK1: P27
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT3::PMR.B0 = 0;
					PORT3::ODR.B0 = i2c;
					MPC::P30PFS.PSEL = sel;  // ok
					PORT3::PMR.B0 = enable;
					PORT2::PMR.B6 = 0;
					PORT2::ODR.B6 = i2c;
					MPC::P26PFS.PSEL = sel;  // ok
					PORT2::PMR.B6 = enable;
					if(spi) {
						PORT2::PMR.B7 = 0;
						MPC::P27PFS.PSEL = sel;
						PORT2::PMR.B7 = enable;
					}
				}
				break;
			case peripheral::SCI2:
				{
					// RXD2: P52
					// TXD2: P50
					// SCK2: P51
					uint8_t sel = enable ? 0b0'1010 : 0;  // ok
					PORT5::PMR.B2 = 0;
					PORT5::ODR.B2 = i2c;
					MPC::P52PFS.PSEL = sel;
					PORT5::PMR.B2 = enable;
					PORT5::PMR.B0 = 0;
					PORT5::ODR.B0 = i2c;
					MPC::P50PFS.PSEL = sel;
					PORT5::PMR.B0 = enable;
					if(spi) {
						PORT5::PMR.B1 = 0;
						MPC::P51PFS.PSEL = sel;
						PORT5::PMR.B1 = enable;
					}
				}
				break;
			case peripheral::SCI3:
				{
					// RXD3: P25
					// TXD3: P23
					// SCK3: P24
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORT2::PMR.B5 = 0;
					PORT2::ODR.B5 = i2c;
					MPC::P25PFS.PSEL = sel;  // ok
					PORT2::PMR.B5 = enable;
					PORT2::PMR.B3 = 0;
					PORT2::ODR.B3 = i2c;
					MPC::P23PFS.PSEL = sel;  // ok
					PORT2::PMR.B3 = enable;
					if(spi) {
						PORT2::PMR.B4 = 0;
						MPC::P24PFS.PSEL = sel;
						PORT2::PMR.B4 = enable;
					}
				}
				break;
			case peripheral::SCI5:
				{
					// RXD5: PA3
					// TXD5: PA4
					// SCK5: PA1
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORTA::PMR.B3 = 0;
					PORTA::ODR.B3 = i2c;
					MPC::PA3PFS.PSEL = sel;
					PORTA::PMR.B3 = enable;
					PORTA::PMR.B4 = 0;
					PORTA::ODR.B4 = i2c;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B4 = enable;
					if(spi) {
						PORTA::PMR.B1 = 0;
						MPC::PA1PFS.PSEL = sel;
						PORTA::PMR.B1 = enable;
					}
				}
				break;
			case peripheral::SCI6:
				{
					// RXD6: P33
					// TXD6: P32
					// SCK6: P34
					uint8_t sel = enable ? 0b0'1010 : 0;  // ok
					PORT3::PMR.B3 = 0;
					PORT3::ODR.B3 = i2c;
					MPC::P33PFS.PSEL = sel;
					PORT3::PMR.B3 = enable;
					PORT3::PMR.B2 = 0;
					PORT3::ODR.B2 = i2c;
					MPC::P32PFS.PSEL = sel;
					PORT3::PMR.B2 = enable;
					if(spi) {
						PORT3::PMR.B4 = 0;
						MPC::P34PFS.PSEL = sel;
						PORT3::PMR.B4 = enable;
					}
				}
				break;

			case peripheral::CAN0:
				{
					// PD2/CRX0
					// PD1/CTX0
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
				{
					// CRX1: P55
					// CTX1: P54
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
				{
					// RSPCKA: PB0
					// MOSIA:  PA6
					// MISOA:  PA7
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
				{
					// RSPCKB: PE1
					// MOSIB:  PE2
					// MISOB:  PE3
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
			default:
				return false;
				break;
			}
			return true;
		}


		static bool sub_3rd_(peripheral per, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			switch(per) {

			case peripheral::SCI1:  // Serial Boot Mode (177/176 pin)
				{
					// RXD1: PF2
					// TXD1: PF0
					// SCK1: PF1
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORTF::PMR.B2 = 0;
					PORTF::ODR.B2 = i2c;
					MPC::PF2PFS.PSEL = sel;  // ok
					PORTF::PMR.B2 = enable;
					PORTF::PMR.B0 = 0;
					PORTF::ODR.B0 = i2c;
					MPC::PF0PFS.PSEL = sel;  // ok
					PORTF::PMR.B0 = enable;
					if(spi) {
						PORTF::PMR.B1 = 0;
						MPC::PF1PFS.PSEL = sel;
						PORTF::PMR.B1 = enable;
					}
				}
				break;
			case peripheral::SCI5:
				{
					// RXD5: PC2
					// TXD5: PC3
					// SCK5: PC1
					uint8_t sel = enable ? 0b0'1010 : 0;
					PORTC::PMR.B2 = 0;
					PORTC::ODR.B2 = i2c;
					MPC::PC2PFS.PSEL = sel;
					PORTC::PMR.B2 = enable;
					PORTC::PMR.B3 = 0;
					PORTC::ODR.B3 = i2c;
					MPC::PC3PFS.PSEL = sel;
					PORTC::PMR.B3 = enable;
					if(spi) {
						PORTC::PMR.B1 = 0;
						MPC::PC1PFS.PSEL = sel;
						PORTC::PMR.B1 = enable;
					}
				}
				break;
			case peripheral::SCI6:
				{
					// RXD6: PB0
					// TXD6: PB1
					// SCK6: PB3
					uint8_t sel = enable ? 0b0'1011 : 0;  // ok
					PORTB::PMR.B0 = 0;
					PORTB::ODR.B0 = i2c;
					MPC::PB0PFS.PSEL = sel;
					PORTB::PMR.B0 = enable;
					PORTB::PMR.B1 = 0;
					PORTB::ODR.B1 = i2c;
					MPC::PB1PFS.PSEL = sel;
					PORTB::PMR.B1 = enable;
					if(spi) {
						PORTB::PMR.B3 = 0;
						MPC::PB3PFS.PSEL = sel;
						PORTB::PMR.B3 = enable;
					}
				}
				break;

			case peripheral::RSPI0:
				{
					// RSPCKA: PC5
					// MOSIA:  PC6
					// MISOA:  PC7
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
				{
					// RSPCKB: PE5
					// MOSIB:  PE6
					// MISOB:  PE7
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

			default:
				return false;
				break;
			}
			return true;
		}


		static bool sub_4th_(peripheral per, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			switch(per) {
			case peripheral::SCI5:
				{
					// RXD5: PC2
					// TXD5: PC3
					// SCK5: PC4
					uint8_t sel = enable ? 0b0'1010 : 0;  // ok
					PORTC::PMR.B2 = 0;
					PORTC::ODR.B2 = i2c;
					MPC::PC2PFS.PSEL = sel;
					PORTC::PMR.B2 = enable;
					PORTC::PMR.B3 = 0;
					PORTC::ODR.B3 = i2c;
					MPC::PC3PFS.PSEL = sel;
					PORTC::PMR.B3 = enable;
					if(spi) {
						PORTC::PMR.B4 = 0;
						MPC::PC4PFS.PSEL = sel;
						PORTC::PMR.B4 = enable;
					}
				}
				break;
			default:
				return false;
				break;
			}
			return true;
		}

		static inline USER_FUNC_TYPE	user_func_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  ユーザー設定関数設定
			@param[in]	func	ユーザー設定関数
		*/
		//-----------------------------------------------------------------//
		static void set_user_func(USER_FUNC_TYPE func) noexcept { user_func_ = func; }


		//-----------------------------------------------------------------//
		/*!
			@brief  周辺機器別ポート切り替え
			@param[in]	per		周辺機器タイプ
			@param[in]	ena		無効にする場合「false」
			@param[in]	odr		候補を選択する場合
			@param[in]	opt		オプショナル設定を行う場合
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral per, bool ena = true, ORDER odr = ORDER::FIRST, OPTIONAL opt = OPTIONAL::NONE) noexcept
		{
			if(odr == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			switch(odr) {
			case ORDER::FIRST:
				ret = sub_1st_(per, ena, opt);
				break;
			case ORDER::SECOND:
				ret = sub_2nd_(per, ena, opt);
				break;
			case ORDER::THIRD:
				ret = sub_3rd_(per, ena, opt);
				break;
			case ORDER::FOURTH:
				ret = sub_4th_(per, ena, opt);
				break;
			case ORDER::USER:
				ret = user_func_(per, ena);
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
