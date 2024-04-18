#pragma once
//=========================================================================//
/*!	@file
	@brief	RX72N グループ・ポート・マッピング @n
			・ペリフェラル型に従って、ポートの設定をグループ化して設定 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX72N/peripheral.hpp"
#include "RX72N/port.hpp"
#include "RX72N/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX72N ポート・マッピング・ユーティリティー
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
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT2::PMR.B1 = 0;
					PORT2::ODR.B1 = i2c;
					MPC::P21PFS.PSEL = sel;
					PORT2::PMR.B1 = enable;
					PORT2::PMR.B0 = 0;
					PORT2::ODR.B0 = i2c;
					MPC::P20PFS.PSEL = sel;
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
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT1::PMR.B5 = 0;
					PORT1::ODR.B5 = i2c;
					MPC::P15PFS.PSEL = sel;
					PORT1::PMR.B5 = enable;
					PORT1::PMR.B6 = 0;
					PORT1::ODR.B6 = i2c;
					MPC::P16PFS.PSEL = sel;
					PORT1::PMR.B6 = enable;
					if(spi) {
						PORT1::PMR.B7 = 0;
						MPC::P17PFS.PSEL = sel;
						PORT1::PMR.B7 = enable;
					}
				}
				break;
			case peripheral::SCI2:
				{   // (RX72N Envision Kit Serial port)
					// RXD2: P12
					// TXD2: P13
					// SCK2: P11
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT1::PMR.B2 = 0;
					PORT1::ODR.B2 = i2c;
					MPC::P12PFS.PSEL = sel;
					PORT1::PMR.B2 = enable;
					PORT1::PMR.B3 = 0;
					PORT1::ODR.B3 = i2c;
					MPC::P13PFS.PSEL = sel;
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
					uint8_t sel = enable ? 0b00'1011 : 0;  // ok
					PORT1::PMR.B6 = 0;
					PORT1::ODR.B6 = i2c;
					MPC::P16PFS.PSEL = sel;
					PORT1::PMR.B6 = enable;
					PORT1::PMR.B7 = 0;
					PORT1::ODR.B7 = i2c;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B7 = enable;
					if(spi) {
						PORT1::PMR.B5 = 0;
						MPC::P15PFS.PSEL = sel;
						PORT1::PMR.B5 = enable;
					}
				}
				break;
			case peripheral::SCI4:
				{   // 100 pin 未対応
					// RXD4: PB0
					// TXD4: PB1
					// SCK4: PB3
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
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
			case peripheral::SCI5:
				{
					// RXD5: PA2
					// TXD5: PA4
					// SCK5: PA1
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTA::PMR.B2 = 0;
					PORTA::ODR.B2 = i2c;
					MPC::PA2PFS.PSEL = sel;
					PORTA::PMR.B2 = enable;
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
					// RXD6: P01
					// TXD6: P00
					// SCK6: P02
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT0::PMR.B1 = 0;
					PORT0::ODR.B1 = i2c;
					MPC::P01PFS.PSEL = sel;
					PORT0::PMR.B1 = enable;
					PORT0::PMR.B0 = 0;
					PORT0::ODR.B0 = i2c;
					MPC::P00PFS.PSEL = sel;
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
					// RXD7: P57
					// TXD7: P55
					// SCK7: P56
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT5::PMR.B7 = 0;
					PORT5::ODR.B7 = i2c;
					MPC::P57PFS.PSEL = sel;
					PORT5::PMR.B7 = enable;
					PORT5::PMR.B5 = 0;
					PORT5::ODR.B5 = i2c;
					MPC::P55PFS.PSEL = sel;
					PORT5::PMR.B5 = enable;
					if(spi) {
						PORT5::PMR.B6 = 0;
						MPC::P56PFS.PSEL = sel;
						PORT5::PMR.B6 = enable;
					}
				}
				break;
			case peripheral::SCI8:
				{
					// RXD8: PC6
					// TXD8: PC7
					// SCK8: PC5
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTC::PMR.B6 = 0;
					PORTC::ODR.B6 = i2c;
					MPC::PC6PFS.PSEL = sel;
					PORTC::PMR.B6 = enable;
					PORTC::PMR.B7 = 0;
					PORTC::ODR.B7 = i2c;
					MPC::PC7PFS.PSEL = sel;
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
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTB::PMR.B6 = 0;
					PORTB::ODR.B6 = i2c;
					MPC::PB6PFS.PSEL = sel;
					PORTB::PMR.B6 = enable;
					PORTB::PMR.B7 = 0;
					PORTB::ODR.B7 = i2c;
					MPC::PB7PFS.PSEL = sel;
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
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT8::PMR.B1 = 0;
					PORT8::ODR.B1 = i2c;
					MPC::P81PFS.PSEL = sel;
					PORT8::PMR.B1 = enable;
					PORT8::PMR.B2 = 0;
					PORT8::ODR.B2 = i2c;
					MPC::P82PFS.PSEL = sel;
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
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT7::PMR.B6 = 0;
					PORT7::ODR.B6 = i2c;
					MPC::P76PFS.PSEL = sel;
					PORT7::PMR.B6 = enable;
					PORT7::PMR.B7 = 0;
					PORT7::ODR.B7 = i2c;
					MPC::P77PFS.PSEL = sel;
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
					uint8_t sel = enable ? 0b00'1100 : 0;  // ok
					PORTE::PMR.B2 = 0;
					PORTE::ODR.B2 = i2c;
					MPC::PE2PFS.PSEL = sel;
					PORTE::PMR.B2 = enable;
					PORTE::PMR.B1 = 0;
					PORTE::ODR.B1 = i2c;
					MPC::PE1PFS.PSEL = sel;
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
					uint8_t sel = enable ? 0b00'1111 : 0;  // ok
					PORT1::PMR.B2 = 0;
					MPC::P12PFS.PSEL = sel;  // SCL0 (P12 LQFP176: 53)
					PORT1::PMR.B2 = enable;
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;  // SDA0 (P13 LQFP176: 52)
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
					MPC::P16PFS.PSEL = sel;  // SCL2 (P16 LQFP176: 48)
					PORT1::PMR.B6 = enable;
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;  // SDA2 (P17 LQFP176: 46)
					PORT1::PMR.B7 = enable;
				}
				break;

			case peripheral::USB0:
				{
					uint8_t sel = enable ? 0b01'0011 : 0;
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;  // USB0_VBUSEN (P24 LQFP176: 40)
					PORT2::PMR.B4 = enable;
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;  // USB0_OVRCURB (P22 LQFP176: 43)
					PORT2::PMR.B2 = enable;
				}
				break;

			case peripheral::CAN0:
				{
					// CRX0: P33
					// CTX0: P32
					uint8_t sel = enable ? 0b01'0000 : 0;  // ok
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;  // CRX0 (P33 LQFP176: 28)
					PORT3::PMR.B3 = 1;
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;  // CTX0 (P32 LQFP176: 29)
					PORT3::PMR.B2 = 1;
				}
				break;
			case peripheral::CAN1:
				{
					// CRX1: P15
					// CTX1: P14
					uint8_t sel = enable ? 0b01'0000 : 0;  // ok
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;  // CRX1-DS (P15 LQFP176: 50)
					PORT1::PMR.B5 = 1;
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;  // CTX1    (P14 LQFP176: 51)
					PORT1::PMR.B4 = 1;
				}
				break;
			case peripheral::CAN2:
				{
					// CRX2: P67
					// CTX2: P66
					uint8_t sel = enable ? 0b01'0000 : 0;  // ok
					PORT6::PMR.B7 = 0;
					MPC::P67PFS.PSEL = sel;  // CRX2 (P67 LQFP176: 120)
					PORT6::PMR.B7 = enable;
					PORT6::PMR.B6 = 0;
					MPC::P66PFS.PSEL = sel;  // CTX2 (P66 LQFP176: 122)
					PORT6::PMR.B6 = enable;
				}
				break;

			case peripheral::RSPI0:
				{
					// RSPCKA: PA5
					// MOSIA:  PA6
					// MISOA:  PA7
					uint8_t sel = enable ? 0b00'1101 : 0;  // ok
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;  // RSPCKA-B (PA5 LQFP176: 108)
					PORTA::PMR.B5 = enable;
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = sel;  // MOSIA-B  (PA6 LQFP176: 107)
					PORTA::PMR.B6 = enable;
					PORTA::PMR.B7 = 0;
					MPC::PA7PFS.PSEL = sel;  // MISOA-B  (PA7 LQFP176: 106)
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
					// RSPCKC: P56
					// MOSIC:  P54
					// MISOC:  P55
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

			case peripheral::SSIE0:
				{
					// AUDIO_CLK: P00
					// SSIBCK0:   P01
					// SSILRCK0:  P21
					// SSIRXD0:   P20
					// SSITXD0:   P17
					uint8_t sel = enable ? 0b01'0111 : 0;
					PORT0::PMR.B0 = 0;
					MPC::P00PFS.PSEL = sel;
					PORT0::PMR.B0 = enable;
					PORT0::PMR.B1 = 0;
					MPC::P01PFS.PSEL = sel;
					PORT0::PMR.B1 = enable;
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;
					PORT2::PMR.B1 = enable;
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = sel;
					PORT2::PMR.B0 = enable;
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B7 = enable;
				}
				break;
			case peripheral::SSIE1:
				{   // RX72N Envision Kit Assign
					// AUDIO_CLK: P00
					// SSIBCK1:   P02
					// SSILRCK1:  P05
					// SSIDATA1:  P03
					uint8_t sel = enable ? 0b01'0111 : 0;
					PORT0::PMR.B0 = 0;
					MPC::P00PFS.PSEL = sel;
					PORT0::PMR.B0 = enable;
					PORT0::PMR.B2 = 0;
					MPC::P02PFS.PSEL = sel;
					PORT0::PMR.B2 = enable;
					PORT0::PMR.B5 = 0;
					MPC::P05PFS.PSEL = sel;
					PORT0::PMR.B5 = enable;
					PORT0::PMR.B3 = 0;
					MPC::P03PFS.PSEL = sel;
					PORT0::PMR.B3 = enable;
				}
				break;

			case peripheral::ETHERC0:  // only RMII mode, not use link status interrupt
				{
					uint8_t  mii = enable ? 0b010001 : 0;
					uint8_t rmii = enable ? 0b010010 : 0;
					PORT7::PMR.B1 = 0;
					PORT7::PMR.B2 = 0;
//					PORT7::PMR.B3 = 0;
					PORT7::PMR.B4 = 0;
					PORT7::PMR.B5 = 0;
					PORT7::PMR.B6 = 0;
					PORT7::PMR.B7 = 0;
//					MPC::P34PFS.PSEL = mii;   // ET0_LINKSTA
//					PORT3::PMR.B4 = enable;
					MPC::P71PFS.PSEL = mii;   // ET0_MDIO
					MPC::P72PFS.PSEL = mii;   // ET0_MDC
//					MPC::P73PFS.PSEL = mii;   // ET0_WOL
					MPC::P74PFS.PSEL = rmii;  // RMII0_RXD1
					MPC::P75PFS.PSEL = rmii;  // RMII0_RXD0
					MPC::P76PFS.PSEL = rmii;  // REF50CK0
					MPC::P77PFS.PSEL = rmii;  // RMII0_RX_ER
					PORT7::PMR.B1 = enable;
					PORT7::PMR.B2 = enable;
//					PORT7::PMR.B3 = enable;
					PORT7::PMR.B4 = enable;
					PORT7::PMR.B5 = enable;
					PORT7::PMR.B6 = enable;
					PORT7::PMR.B7 = enable;
					PORT8::PMR.B0 = 0;
					PORT8::PMR.B1 = 0;
					PORT8::PMR.B2 = 0;
					PORT8::PMR.B3 = 0;
					MPC::P80PFS.PSEL = rmii;  // RMII0_TXD_EN
					MPC::P81PFS.PSEL = rmii;  // RMII0_TXD0
					MPC::P82PFS.PSEL = rmii;  // RMII0_TXD1
					MPC::P83PFS.PSEL = rmii;  // RMII0_CRS_DV
					PORT8::PMR.B0 = enable;
					PORT8::PMR.B1 = enable;
					PORT8::PMR.B2 = enable;
					PORT8::PMR.B3 = enable;
					MPC::PFENET.PHYMODE0 = 0;  // for RMII mode chanel 0
				}
				break;

			case peripheral::ETHERCA:  // only RMII mode, not use link status interrupt
				{
					uint8_t  mii = enable ? 0b010001 : 0;
					uint8_t rmii = enable ? 0b010010 : 0;

///					PORT7::PMR.B3 = 0;
					PORT7::PMR.B2 = 0;
					PORT7::PMR.B1 = 0;
///					MPC::P73PFS.PSEL = mii;   // ET0_WOL  (144LQFP: 77)
					MPC::P72PFS.PSEL = mii;   // ET0_MDC  (144LQFP: 85)
					MPC::P71PFS.PSEL = mii;   // ET0_MDIO (144LQFP: 86)
///					PORT7::PMR.B3 = enable;
					PORT7::PMR.B2 = enable;
					PORT7::PMR.B1 = enable;

					PORTB::PMR.B7 = 0;
					PORTB::PMR.B6 = 0;
					PORTB::PMR.B5 = 0;
					PORTB::PMR.B4 = 0;
					PORTB::PMR.B3 = 0;
					PORTB::PMR.B2 = 0;
					PORTB::PMR.B1 = 0;
					PORTB::PMR.B0 = 0;
					MPC::PB7PFS.PSEL = rmii;  // RMII0_CRS_DV (144LQFP: 78)
					MPC::PB6PFS.PSEL = rmii;  // RMII0_TXD1   (144LQFP: 79)
					MPC::PB5PFS.PSEL = rmii;  // RMII0_TXD0   (144LQFP: 80)
					MPC::PB4PFS.PSEL = rmii;  // RMII0_TXD_EN (144LQFP: 81)
					MPC::PB3PFS.PSEL = rmii;  // RMII0_RX_ER  (144LQFP: 82)
					MPC::PB2PFS.PSEL = rmii;  // REF50CK0     (144LQFP: 83)
					MPC::PB1PFS.PSEL = rmii;  // RMII0_RXD0   (144LQFP: 84)
					MPC::PB0PFS.PSEL = rmii;  // RMII0_RXD1   (144LQFP: 87)
					PORTB::PMR.B7 = enable;
					PORTB::PMR.B6 = enable;
					PORTB::PMR.B5 = enable;
					PORTB::PMR.B4 = enable;
					PORTB::PMR.B3 = enable;
					PORTB::PMR.B2 = enable;
					PORTB::PMR.B1 = enable;
					PORTB::PMR.B0 = enable;
					MPC::PFENET.PHYMODE0 = 0;  // for RMII mode chanel 0
				}
				break;

			case peripheral::CMTW0:
				if(opt == OPTIONAL::CMTW_TOC0) {
					// PC7
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTC::PMR.B7 = enable;
				} else if(opt == OPTIONAL::CMTW_TIC0) {
					// PC6
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTC::PMR.B6 = enable;
				} else if(opt == OPTIONAL::CMTW_TOC1) {
					// PE7
					PORTE::PMR.B7 = 0;
					MPC::PE7PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTE::PMR.B7 = enable;
				} else if(opt == OPTIONAL::CMTW_TIC1) {
					// PE6
					PORTE::PMR.B6 = 0;
					MPC::PE6PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTE::PMR.B6 = enable;
				} else {
					return false;
				}
				break;
			case peripheral::CMTW1:
				if(opt == OPTIONAL::CMTW_TOC0) {
					// PD3
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTD::PMR.B3 = enable;
				} else if(opt == OPTIONAL::CMTW_TIC0) {
					// PD2
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTD::PMR.B2 = enable;
				} else if(opt == OPTIONAL::CMTW_TOC1) {
					// PE3
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTE::PMR.B3 = enable;
				} else if(opt == OPTIONAL::CMTW_TIC1) {
					// PE2
					PORTE::PMR.B2 = 0;
					MPC::PE2PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTE::PMR.B2 = enable;
				} else {
					return false;
				}
				break;

			case peripheral::GLCDC:
				{
					uint8_t sel = enable ? 0b100101 : 0;
					PORTB::PMR.B5 = 0;
					PORTB::PMR.B4 = 0;
					PORTB::PMR.B2 = 0;
					PORTB::PMR.B1 = 0;
					PORTB::PMR.B0 = 0;
					PORTB::PMR.B0 = 0;
					PORTA::PMR.B7 = 0;
					PORTA::PMR.B6 = 0;
					PORTA::PMR.B5 = 0;
					PORTA::PMR.B4 = 0;
					PORTA::PMR.B3 = 0;
					PORTA::PMR.B2 = 0;
					PORTA::PMR.B1 = 0;
					PORTA::PMR.B0 = 0;
					PORTE::PMR.B7 = 0;
					PORTE::PMR.B6 = 0;
					PORTE::PMR.B5 = 0;
					PORTE::PMR.B4 = 0;
					PORTE::PMR.B3 = 0;
					PORTE::PMR.B2 = 0;
					PORTE::PMR.B1 = 0;
					MPC::PB5PFS.PSEL = sel;  // LCD_CLK
					PORTB::PMR.B5 = enable;
					MPC::PB4PFS.PSEL = sel;  // LCD_TCON0
					PORTB::PMR.B4 = enable;
					MPC::PB2PFS.PSEL = sel;  // LCD_TCON2
					PORTB::PMR.B2 = enable;
					MPC::PB1PFS.PSEL = sel;  // LCD_TCON3
					PORTB::PMR.B1 = enable;
					MPC::PB0PFS.PSEL = sel;  // LCD_DATA0
					PORTB::PMR.B0 = enable;
					MPC::PA7PFS.PSEL = sel;  // LCD_DATA1
					PORTA::PMR.B7 = enable;
					MPC::PA6PFS.PSEL = sel;  // LCD_DATA2
					PORTA::PMR.B6 = enable;
					MPC::PA5PFS.PSEL = sel;  // LCD_DATA3
					PORTA::PMR.B5 = enable;
					MPC::PA4PFS.PSEL = sel;  // LCD_DATA4
					PORTA::PMR.B4 = enable;
					MPC::PA3PFS.PSEL = sel;  // LCD_DATA5
					PORTA::PMR.B3 = enable;
					MPC::PA2PFS.PSEL = sel;  // LCD_DATA6
					PORTA::PMR.B2 = enable;
					MPC::PA1PFS.PSEL = sel;  // LCD_DATA7
					PORTA::PMR.B1 = enable;
					MPC::PA0PFS.PSEL = sel;  // LCD_DATA8
					PORTA::PMR.B0 = enable;
					MPC::PE7PFS.PSEL = sel;  // LCD_DATA9
					PORTE::PMR.B7 = enable;
					MPC::PE6PFS.PSEL = sel;  // LCD_DATA10
					PORTE::PMR.B6 = enable;
					MPC::PE5PFS.PSEL = sel;  // LCD_DATA11
					PORTE::PMR.B5 = enable;
					MPC::PE4PFS.PSEL = sel;  // LCD_DATA12
					PORTE::PMR.B4 = enable;
					MPC::PE3PFS.PSEL = sel;  // LCD_DATA13
					PORTE::PMR.B3 = enable;
					MPC::PE2PFS.PSEL = sel;  // LCD_DATA14
					PORTE::PMR.B2 = enable;
					MPC::PE1PFS.PSEL = sel;  // LCD_DATA15
					PORTE::PMR.B1 = enable;
				}
				break;

			default:
				return false;
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
					uint8_t sel = enable ? 0b00'1011 : 0;  // ok
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
			case peripheral::SCI1:
				{
					// RXD1: P30
					// TXD1: P26
					// SCK1: P27
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT3::PMR.B0 = 0;
					PORT3::ODR.B0 = i2c;
					MPC::P30PFS.PSEL = sel;
					PORT3::PMR.B0 = enable;
					PORT2::PMR.B6 = 0;
					PORT2::ODR.B6 = i2c;
					MPC::P26PFS.PSEL = sel;
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
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
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
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT2::PMR.B5 = 0;
					PORT2::ODR.B5 = i2c;
					MPC::P25PFS.PSEL = sel;
					PORT2::PMR.B5 = enable;
					PORT2::PMR.B3 = 0;
					PORT2::ODR.B3 = i2c;
					MPC::P23PFS.PSEL = sel;
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
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
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
			case peripheral::SCI7:
				{
					// RXD7: P92
					// TXD7: P90
					// SCK7: P91
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT9::PMR.B2 = 0;
					PORT9::ODR.B2 = i2c;
					MPC::P92PFS.PSEL = sel;
					PORT9::PMR.B2 = enable;
					PORT9::PMR.B0 = 0;
					PORT9::ODR.B0 = i2c;
					MPC::P90PFS.PSEL = sel;
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
					// RXD8: PJ1
					// TXD8: PJ2
					// SCK8: PJ0
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTJ::PMR.B1 = 0;
					PORTJ::ODR.B1 = i2c;
					MPC::PJ1PFS.PSEL = sel;
					PORTJ::PMR.B1 = enable;
					PORTJ::PMR.B2 = 0;
					PORTJ::ODR.B2 = i2c;
					MPC::PJ2PFS.PSEL = sel;
					PORTJ::PMR.B2 = enable;
					if(spi) {
						PORTJ::PMR.B0 = 0;
						MPC::PJ0PFS.PSEL = sel;
						PORTJ::PMR.B0 = enable;
					}
				}
				break;
			case peripheral::SCI9:
				{
					// RXD8: PL1
					// TXD8: PL2
					// SCK8: PL0
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTL::PMR.B1 = 0;
					PORTL::ODR.B1 = i2c;
					MPC::PL1PFS.PSEL = sel;
					PORTL::PMR.B1 = enable;
					PORTL::PMR.B2 = 0;
					PORTL::ODR.B2 = i2c;
					MPC::PL2PFS.PSEL = sel;
					PORTL::PMR.B2 = enable;
					if(spi) {
						PORTL::PMR.B0 = 0;
						MPC::PL0PFS.PSEL = sel;
						PORTL::PMR.B0 = enable;
					}
				}
				break;
			case peripheral::SCI10:
				{
					// RXD10: P86
					// TXD10: P87
					// SCK10: P83
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT8::PMR.B6 = 0;
					PORT8::ODR.B6 = i2c;
					MPC::P86PFS.PSEL = sel;
					PORT8::PMR.B6 = enable;
					PORT8::PMR.B7 = 0;
					PORT8::ODR.B7 = i2c;
					MPC::P87PFS.PSEL = sel;
					PORT8::PMR.B7 = enable;
					if(spi) {
						PORT8::PMR.B3 = 0;
						MPC::P83PFS.PSEL = sel;
						PORT8::PMR.B3 = enable;
					}
				}
				break;
			case peripheral::SCI11:
				{
					// RXD11: PB6
					// TXD11: PB7
					// SCK11: PB5
					uint8_t sel = enable ? 0b10'0100 : 0;  // ok
					PORTB::PMR.B6 = 0;
					PORTB::ODR.B6 = i2c;
					MPC::PB6PFS.PSEL = sel;
					PORTB::PMR.B6 = enable;
					PORTB::PMR.B7 = 0;
					PORTB::ODR.B7 = i2c;
					MPC::PB7PFS.PSEL = sel;
					PORTB::PMR.B7 = enable;
					if(spi) {
						PORTB::PMR.B5 = 0;
						MPC::PB5PFS.PSEL = sel;
						PORTB::PMR.B5 = enable;
					}
				}
				break;

			case peripheral::USB0:
				{
					uint8_t sel = enable ? 0b010010 : 0;
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;  // USB0_VBUSEN (P16 for RX72N Envision Kit)
					PORT1::PMR.B6 = enable;
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;  // USB0_OVRCURA-DS (P14 for RX72N Envision Kit)
					PORT1::PMR.B4 = enable;
				}
				break;

			case peripheral::CAN0:
				{
					// CRX0: PD2
					// CTX0: PD1
					uint8_t sel = enable ? 0b01'0000 : 0;  // ok
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;  // CRX0 (PD2 LQFP176: 154)
					PORTD::PMR.B2 = enable;
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;  // CTX0 (PD1 LQFP176: 156)
					PORTD::PMR.B1 = enable;
				}
				break;
			case peripheral::CAN1:
				{
					// CRX1: P55
					// CTX1: P54
					uint8_t sel = enable ? 0b01'0000 : 0;  // ok
					PORT5::PMR.B5 = 0;
					MPC::P55PFS.PSEL = sel;  // CRX1 (P55 LQFP176: 65)
					PORT5::PMR.B5 = enable;
					PORT5::PMR.B4 = 0;
					MPC::P54PFS.PSEL = sel;  // CTX1 (P54 LQFP176: 66)
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
					MPC::PC5PFS.PSEL = sel;  // RSPCKA-A (PC5 LQFP176: 78)
					PORTC::PMR.B5 = enable;
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;  // MOSIA-A  (PC6 LQFP176: 77)
					PORTC::PMR.B6 = enable;
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;  // MISOA-A  (PC7 LQFP176: 76)
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
					// RSPCKC: PD3
					// MOSIC:  PD1
					// MISOC:  PD2
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

			case peripheral::CMTW0:
				if(opt == OPTIONAL::CMTW_TOC0) {
					// PH1
					PORTH::PMR.B1 = 0;
					MPC::PH1PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTH::PMR.B1 = enable;
				} else if(opt == OPTIONAL::CMTW_TIC0) {
					// PH0
					PORTH::PMR.B0 = 0;
					MPC::PH0PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTH::PMR.B0 = enable;
				} else if(opt == OPTIONAL::CMTW_TOC1) {
					// PK1
					PORTK::PMR.B1 = 0;
					MPC::PK1PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTK::PMR.B1 = enable;
				} else if(opt == OPTIONAL::CMTW_TIC1) {
					// PK0
					PORTK::PMR.B0 = 0;
					MPC::PK0PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTK::PMR.B0 = enable;
				} else {
					return false;
				}
				break;
			case peripheral::CMTW1:
				if(opt == OPTIONAL::CMTW_TOC0) {
					// PL1
					PORTL::PMR.B1 = 0;
					MPC::PL1PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTL::PMR.B1 = enable;
				} else if(opt == OPTIONAL::CMTW_TIC0) {
					// PL0
					PORTL::PMR.B0 = 0;
					MPC::PL0PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTL::PMR.B0 = enable;
				} else if(opt == OPTIONAL::CMTW_TOC1) {
					// PM1
					PORTH::PMR.B1 = 0;
					MPC::PH1PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTH::PMR.B1 = enable;
				} else if(opt == OPTIONAL::CMTW_TIC1) {
					// PM0
					PORTH::PMR.B0 = 0;
					MPC::PH0PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTH::PMR.B0 = enable;
				} else {
					return false;
				}
				break;

			default:
				return false;
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
			case peripheral::SCI1:
				{
					// RXD1: PF2
					// TXD1: PF0
					// SCK1: PF1
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTF::PMR.B2 = 0;
					PORTF::ODR.B2 = i2c;
					MPC::PF2PFS.PSEL = sel;
					PORTF::PMR.B2 = enable;
					PORTF::PMR.B0 = 0;
					PORTF::ODR.B0 = i2c;
					MPC::PF0PFS.PSEL = sel;
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
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
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
					uint8_t sel = enable ? 0b00'1011 : 0;  // ok
					PORTB::PMR.B1 = 0;
					PORTB::ODR.B1 = i2c;
					MPC::PB1PFS.PSEL = sel;
					PORTB::PMR.B1 = enable;
					PORTB::PMR.B0 = 0;
					PORTB::ODR.B0 = i2c;
					MPC::PB0PFS.PSEL = sel;
					PORTB::PMR.B0 = enable;
					if(spi) {
						PORTB::PMR.B3 = 0;
						MPC::PB3PFS.PSEL = sel;
						PORTB::PMR.B3 = enable;
					}
				}
				break;
			case peripheral::SCI7:
				{
					// RXD7: PH1
					// TXD7: PH2
					// SCK7: PH0
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTH::PMR.B1 = 0;
					PORTH::ODR.B1 = i2c;
					MPC::PH1PFS.PSEL = sel;
					PORTH::PMR.B1 = enable;
					PORTH::PMR.B2 = 0;
					PORTH::ODR.B2 = i2c;
					MPC::PH2PFS.PSEL = sel;
					PORTH::PMR.B2 = enable;
					if(spi) {
						PORTH::PMR.B0 = 0;
						MPC::PH0PFS.PSEL = sel;
						PORTH::PMR.B0 = enable;
					}
				}
				break;
			case peripheral::SCI8:
				{
					// RXD8: PK1
					// TXD8: PK2
					// SCK8: PK0
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTK::PMR.B1 = 0;
					PORTK::ODR.B1 = i2c;
					MPC::PK1PFS.PSEL = sel;
					PORTK::PMR.B1 = enable;
					PORTK::PMR.B2 = 0;
					PORTK::ODR.B2 = i2c;
					MPC::PK2PFS.PSEL = sel;
					PORTK::PMR.B2 = enable;
					if(spi) {
						PORTK::PMR.B0 = 0;
						MPC::PK0PFS.PSEL = sel;
						PORTK::PMR.B0 = enable;
					}
				}
				break;
			case peripheral::SCI10:
				{
					// RXD10: PC6
					// TXD10: PC7
					// SCK10: PC5
					uint8_t sel = enable ? 0b10'0100 : 0;  // ok
					PORTC::PMR.B6 = 0;
					PORTC::ODR.B6 = i2c;
					MPC::PC6PFS.PSEL = sel;
					PORTC::PMR.B6 = enable;
					PORTC::PMR.B7 = 0;
					PORTC::ODR.B7 = i2c;
					MPC::PC7PFS.PSEL = sel;
					PORTC::PMR.B7 = enable;
					if(spi) {
						PORTC::PMR.B5 = 0;
						MPC::PC5PFS.PSEL = sel;
						PORTC::PMR.B5 = enable;
					}
				}
				break;
			case peripheral::SCI11:
				{
					// RXD11: PQ1
					// TXD11: PQ2
					// SCK11: PQ0
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTQ::PMR.B1 = 0;
					PORTQ::ODR.B1 = i2c;
					MPC::PQ1PFS.PSEL = sel;
					PORTQ::PMR.B1 = enable;
					PORTQ::PMR.B2 = 0;
					PORTQ::ODR.B2 = i2c;
					MPC::PQ2PFS.PSEL = sel;
					PORTQ::PMR.B2 = enable;
					if(spi) {
						PORTQ::PMR.B0 = 0;
						MPC::PQ0PFS.PSEL = sel;
						PORTQ::PMR.B0 = enable;
					}
				}
				break;

			case peripheral::CAN1:
				{
					// CRX1: P15
					// CTX1: P23
					uint8_t sel = enable ? 0b01'0000 : 0;  // ok
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;
					PORT1::PMR.B5 = enable;
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;
					PORT2::PMR.B3 = enable;
				}
				break;

			case peripheral::RSPI0:
				{
					// RSPCKA: PH0
					// MOSIA:  PH1
					// MISOA:  PH2
					uint8_t sel = enable ? 0b00'1101 : 0;  // ok
					PORTH::PMR.B0 = 0;
					MPC::PH0PFS.PSEL = sel;
					PORTH::PMR.B0 = enable;
					PORTH::PMR.B1 = 0;
					MPC::PH1PFS.PSEL = sel;
					PORTH::PMR.B1 = enable;
					PORTH::PMR.B2 = 0;
					MPC::PH2PFS.PSEL = sel;
					PORTH::PMR.B2 = enable;
				}
				break;
			case peripheral::RSPI1:
				{
					// RSPCKB: PK0
					// MOSIB:  PK1
					// MISOB:  PK2
					uint8_t sel = enable ? 0b00'1101 : 0;  // ok
					PORTK::PMR.B0 = 0;
					MPC::PK0PFS.PSEL = sel;
					PORTK::PMR.B0 = enable;
					PORTK::PMR.B1 = 0;
					MPC::PK1PFS.PSEL = sel;
					PORTK::PMR.B1 = enable;
					PORTK::PMR.B2 = 0;
					MPC::PK2PFS.PSEL = sel;
					PORTK::PMR.B2 = enable;
				}
				break;
			case peripheral::RSPI2:
				{
					// RSPCKC: PL0
					// MOSIC:  PL1
					// MISOC:  PL2
					uint8_t sel = enable ? 0b00'1101 : 0;  // ok
					PORTL::PMR.B0 = 0;
					MPC::PL0PFS.PSEL = sel;
					PORTL::PMR.B0 = enable;
					PORTL::PMR.B1 = 0;
					MPC::PL1PFS.PSEL = sel;
					PORTL::PMR.B1 = enable;
					PORTL::PMR.B2 = 0;
					MPC::PL2PFS.PSEL = sel;
					PORTL::PMR.B2 = enable;
				}
				break;

			default:
				return false;
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
			case peripheral::SCI10:
				{
					// RXD10: PM1
					// TXD10: PM2
					// SCK10: PM0
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTM::PMR.B1 = 0;
					PORTM::ODR.B1 = i2c;
					MPC::PM1PFS.PSEL = sel;
					PORTM::PMR.B1 = enable;
					PORTM::PMR.B2 = 0;
					PORTM::ODR.B2 = i2c;
					MPC::PM2PFS.PSEL = sel;
					PORTM::PMR.B2 = enable;
					if(spi) {
						PORTM::PMR.B0 = 0;
						MPC::PM0PFS.PSEL = sel;
						PORTM::PMR.B0 = enable;
					}
				}
				break;

			case peripheral::CAN1:
				{
					// CRX1: P55
					// CTX1: P23
					uint8_t sel = enable ? 0b01'0000 : 0;  // ok
					PORT5::PMR.B5 = 0;
					MPC::P55PFS.PSEL = sel;
					PORT5::PMR.B5 = enable;
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;
					PORT2::PMR.B3 = enable;
				}
				break;
			default:
				return false;
			}
			return true;
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

		static inline USER_FUNC_TYPE	user_func_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  ユーザー設定関数設定
			@param[in]	func	ユーザー設定関数
		*/
		//-----------------------------------------------------------------//
		static void set_user_func(USER_FUNC_TYPE func) noexcept { user_func_ = func; }


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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  周辺機器に切り替える
			@param[in]	per		周辺機器タイプ
			@param[in]	ena		無効にする場合「false」
			@param[in]	odr		ポート・マップ候補
			@param[in]	opt		オプショナル設定を行う場合
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(peripheral per, bool ena = true, ORDER odr = ORDER::FIRST, OPTIONAL opt = OPTIONAL::NONE) noexcept
		{
			if(odr == ORDER::BYPASS) return false;

			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
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
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDHI ポート専用切り替え
			@param[in]	state	SHDI 候補
			@param[in]	order	ポート・マップ候補
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn_sdhi(SDHI_STATE state, ORDER order = ORDER::FIRST) noexcept
		{
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = 0;
			switch(order) {
			case ORDER::FIRST:
				ret = sdhi_1st_(state);
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDHI クロック・ポートの状態を取得
			@param[in]	order	ポート・マップ候補
			@return SDHI クロック・ポートの状態
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool probe_sdhi_clock(ORDER order) noexcept
		{
			bool ret = 0;
			switch(order) {
			case ORDER::FIRST:
				ret = PORT7::PIDR.B7();
				break;
			case ORDER::THIRD:
				ret = PORT2::PIDR.B1();
				break;
			default:
				break;
			}
			return ret;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CLKOUT25M 出力を許可する
			@param[in]	ena	不許可にする場合「false」
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static void turn_CLKOUT25M(bool ena = true) noexcept
		{
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			PORT5::PMR.B6 = 0;
			uint8_t sel = ena ? 0b101010 : 0;			
			MPC::P56PFS.PSEL = sel;
			PORT5::PMR.B6 = ena;

			MPC::PWPR = MPC::PWPR.B0WI.b();
		}
	};
}
