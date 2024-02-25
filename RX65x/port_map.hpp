#pragma once
//=========================================================================//
/*!	@file
	@brief	RX651/RX65N グループ・ポート・マッピング @n
			・ペリフェラル型に従って、ポートの設定をグループ化して設定 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX65x/peripheral.hpp"
#include "RX64M/port.hpp"
#include "RX65x/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX651/RX65N ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map : public port_map_order {

		static bool sub_1st_(peripheral t, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			bool ret = true;
			switch(t) {
			case peripheral::SCI0:
				{
					// RXD0: P21
					// TXD0: P20
					// SCK0: P22
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT2::PMR.B1 = 0;
					PORT2::PDR.B1 = i2c;
					MPC::P21PFS.PSEL = sel;  // RXD0/SMOSI0/SSDA0 (P21 LQFP176: 44)
					PORT2::PMR.B1 = enable;
					PORT2::PMR.B0 = 0;
					PORT2::ODR.B0 = i2c;
					MPC::P20PFS.PSEL = sel;  // TXD0/SMISO0/SSCL0 (P20 LQFP176: 45)
					PORT2::PMR.B0 = enable;
					if(spi) {
						PORT2::PMR.B2 = 0;
						MPC::P22PFS.PSEL = sel;  // SCK0 (P22 LQFP176: 43)
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
					PORT1::PDR.B5 = i2c;
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
				{
					// RXD2: P12
					// TXD2: P13
					// SCK2: P11
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT1::PMR.B2 = 0;
					PORT1::ODR.B2 = i2c;
					MPC::P12PFS.PSEL = sel;  // RXD2/SMOSI2/SSDA2 (P12 LQFP176: 53)
					PORT1::PMR.B2 = enable;
					PORT1::PMR.B3 = 0;
					PORT1::ODR.B3 = i2c;
					MPC::P13PFS.PSEL = sel;  // TXD2/SMISO2/SSCL2 (P13 LQFP176: 52)
					PORT1::PMR.B3 = enable;
					if(spi) {
						PORT1::PMR.B1 = 0;
						MPC::P11PFS.PSEL = sel;  // SCK2 (P11 LQFP176: 67)
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
					MPC::P16PFS.PSEL = sel;  // RXD3/SMISO3/SSCL3 (P16 LQFP176: 48)
					PORT1::PMR.B6 = enable;
					PORT1::PMR.B7 = 0;
					PORT1::ODR.B7 = i2c;
					MPC::P17PFS.PSEL = sel;  // TXD3/SMOSI3/SSDA3 (P17 LQFP176: 46)
					PORT1::PMR.B7 = enable;
					if(spi) {
						PORT1::PMR.B5 = 0;
						MPC::P15PFS.PSEL = sel;  // SCK3 (P15 LQFP176: 50)
						PORT1::PMR.B5 = enable;
					}
				}
				break;
			case peripheral::SCI4:
				{
					// RXD4: PB0
					// TXD4: PB1
					// SCK4: PB3
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTB::PMR.B0 = 0;
					PORTB::ODR.B0 = i2c;
					MPC::PB0PFS.PSEL = sel;  // RXD4/SMOSI4/SSDA4 (PB0 LQFP176: 104)
					PORTB::PMR.B0 = enable;
					PORTB::PMR.B1 = 0;
					PORTB::ODR.B1 = i2c;
					MPC::PB1PFS.PSEL = sel;  // TXD4/SMISO4/SSCL4 (PB1 LQFP176: 100)
					PORTB::PMR.B1 = enable;
					if(spi) {
						PORTB::PMR.B3 = 0;
						MPC::PB3PFS.PSEL = sel;  // SCK4 (PB3 LQFP176: 98)
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
					MPC::P01PFS.PSEL = sel;  // RXD6/SMOSI6/SSDA6 (P01 LQFP176: 7)
					PORT0::PMR.B1 = enable;
					PORT0::PMR.B0 = 0;
					PORT0::ODR.B0 = i2c;
					MPC::P00PFS.PSEL = sel;  // TXD6/SMISO6/SSCL6 (P00 LQFP176: 8)
					PORT0::PMR.B0 = enable;
					if(spi) {
						PORT0::PMR.B2 = 0;
						MPC::P02PFS.PSEL = sel;  // SCK6 (P02 LQFP176: 6)
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
					MPC::PC6PFS.PSEL = sel;  // RXD(F)8/SMOSI8/SSDA8 (PC6 LQFP176: 77)
					PORTC::PMR.B6 = enable;
					PORTC::PMR.B7 = 0;
					PORTC::ODR.B7 = i2c;
					MPC::PC7PFS.PSEL = sel;  // TXD(F)8/SMISO8/SSCL8 (PC7 LQFP176: 76)
					PORTC::PMR.B7 = enable;
					if(spi) {
						PORTC::PMR.B5 = 0;
						MPC::PC5PFS.PSEL = sel;  // SCK8 (PC5 LQFP176: 78)
						PORTC::PMR.B5 = enable;
					}
				}
				break;
			case peripheral::SCI9:  // RX65N Envision Kit Pmod_9(TXD9), Pmod_10(RXD9)
				{
					// RXD9: PB6
					// TXD9: PB7
					// SCK9: PB5
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTB::PMR.B6 = 0;
					PORTB::ODR.B6 = i2c;
					MPC::PB6PFS.PSEL = sel;  // RXD(F)9/SMOSI9/SSDA9 (PB6 LQFP176: 95)
					PORTB::PMR.B6 = enable;
					PORTB::PMR.B7 = 0;
					PORTB::ODR.B7 = i2c;
					MPC::PB7PFS.PSEL = sel;  // TXD(F)9/SMISO9/SSCL9 (PB7 LQFP176: 94)
					PORTB::PMR.B7 = enable;
					if(spi) {
						PORTB::PMR.B5 = 0;
						MPC::PB5PFS.PSEL = sel;  // SCK9 (PB5 LQFP176: 96)
						PORTB::PMR.B5 = enable;
					}
				}
				break;
			case peripheral::SCI10:
				{
					// RXD10: P81
					// TXD10: P82
					// SCK10: P80
					uint8_t sel = enable ? 0b00'1010 : 0;
					PORTB::PMR.B1 = 0;
					PORTB::ODR.B1 = i2c;
					MPC::PB1PFS.PSEL = sel;
					PORTB::PMR.B1 = enable;
					PORTB::PMR.B2 = 0;
					PORTB::ODR.B2 = i2c;
					MPC::PB2PFS.PSEL = sel;
					PORTB::PMR.B2 = enable;
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
					MPC::P76PFS.PSEL = sel;  // RXD(F)11/SMOSI11/SSDA11 (P76 LQFP176: 85)
					PORT7::PMR.B6 = enable;
					PORT7::PMR.B7 = 0;
					PORT7::ODR.B7 = i2c;
					MPC::P77PFS.PSEL = sel;  // TXD(F)11/SMISO11/SSCL11 (P77 LQFP176: 84)
					PORT7::PMR.B7 = enable;
					if(spi) {
						PORT7::PMR.B5 = 0;
						MPC::P75PFS.PSEL = sel;  // SCK11 (P75 LQFP176: 87)
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
					MPC::PE2PFS.PSEL = sel;  // RXD12/SMISO12/SSCL12 (PE2 LQFP176: 133)
					PORTE::PMR.B2 = enable;
					PORTE::PMR.B1 = 0;
					PORTE::ODR.B1 = i2c;
					MPC::PE1PFS.PSEL = sel;  // TXD12/SMOSI12/SSDA12 (PE1 LQFP176: 134)
					PORTE::PMR.B1 = enable;
					if(spi) {
						PORTE::PMR.B0 = 0;
						MPC::PE0PFS.PSEL = sel;  // SCK12 (PE0 LQFP176: 135)
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
				{   // コードフラッシュメモリ容量が1Mバイト以下の製品は未対応
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

			case peripheral::USB0:
				{
					uint8_t sel = enable ? 0b010010 : 0;
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;  // USB0_OVRCURB (P14 LQFP176: 51)
					PORT1::PMR.B4 = enable;
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;  // USB0_VBUSEN (P16 LQFP176: 48)
					PORT1::PMR.B6 = enable;
				}
				break;

			case peripheral::QSPI:
				{
					// QSPCLK:   P77
					// QSSL:     P76
					// QMO/QIO0: PC3  (100ピンは未対応)
					// QMI/QIO1: PC4  (100ピンは未対応)
					// QIO2:     P80
					// QIO3:     P81
					uint8_t sel = enable ? 0b01'1011 : 0;  // ok
					PORT7::PMR.B7 = 0;
					MPC::P77PFS.PSEL = sel;  // QSPCLK-A (P77 LQFP176: 84)
					PORT7::PMR.B7 = enable;
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;  // QSPSSL-A (P76 LQFP176: 85)
					PORT7::PMR.B6 = enable;
					PORTC::PMR.B3 = 0;
					MPC::PC3PFS.PSEL = sel;  // QIO0-A   (PC3 LQFP176: 83)
					PORTC::PMR.B3 = enable;
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;  // QIO1-A   (PC4 LQFP176: 82)
					PORTC::PMR.B4 = enable;
					PORT8::PMR.B0 = 0;
					MPC::P80PFS.PSEL = sel;  // QIO2-A   (P80 LQFP176: 81)
					PORT8::PMR.B0 = enable;
					PORT8::PMR.B1 = 0;
					MPC::P81PFS.PSEL = sel;  // QIO3-A   (P81 LQFP176: 80)
					PORT8::PMR.B1 = enable;
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

#if 0
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
#endif
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
					MPC::PB5PFS.PSEL = sel;  // LCD_CLK-B
					PORTB::PMR.B5 = enable;
					MPC::PB4PFS.PSEL = sel;  // LCD_TCON0-B
					PORTB::PMR.B4 = enable;
					MPC::PB2PFS.PSEL = sel;  // LCD_TCON2-B
					PORTB::PMR.B2 = enable;
					MPC::PB1PFS.PSEL = sel;  // LCD_TCON3-B
					PORTB::PMR.B1 = enable;
					MPC::PB0PFS.PSEL = sel;  // LCD_DATA0-B
					PORTB::PMR.B0 = enable;
					MPC::PA7PFS.PSEL = sel;  // LCD_DATA1-B
					PORTA::PMR.B7 = enable;
					MPC::PA6PFS.PSEL = sel;  // LCD_DATA2-B
					PORTA::PMR.B6 = enable;
					MPC::PA5PFS.PSEL = sel;  // LCD_DATA3-B
					PORTA::PMR.B5 = enable;
					MPC::PA4PFS.PSEL = sel;  // LCD_DATA4-B
					PORTA::PMR.B4 = enable;
					MPC::PA3PFS.PSEL = sel;  // LCD_DATA5-B
					PORTA::PMR.B3 = enable;
					MPC::PA2PFS.PSEL = sel;  // LCD_DATA6-B
					PORTA::PMR.B2 = enable;
					MPC::PA1PFS.PSEL = sel;  // LCD_DATA7-B
					PORTA::PMR.B1 = enable;
					MPC::PA0PFS.PSEL = sel;  // LCD_DATA8-B
					PORTA::PMR.B0 = enable;
					MPC::PE7PFS.PSEL = sel;  // LCD_DATA9-B
					PORTE::PMR.B7 = enable;
					MPC::PE6PFS.PSEL = sel;  // LCD_DATA10-B
					PORTE::PMR.B6 = enable;
					MPC::PE5PFS.PSEL = sel;  // LCD_DATA11-B
					PORTE::PMR.B5 = enable;
					MPC::PE4PFS.PSEL = sel;  // LCD_DATA12-B
					PORTE::PMR.B4 = enable;
					MPC::PE3PFS.PSEL = sel;  // LCD_DATA13-B
					PORTE::PMR.B3 = enable;
					MPC::PE2PFS.PSEL = sel;  // LCD_DATA14-B
					PORTE::PMR.B2 = enable;
					MPC::PE1PFS.PSEL = sel;  // LCD_DATA15-B
					PORTE::PMR.B1 = enable;
				}
				break;

			default:
				ret = false;
				break;
			}
			return ret;
		}


		static bool sub_2nd_(peripheral per, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			bool ret = true;
			switch(per) {
			case peripheral::SCI0:
				{
					// RXD0: P33
					// TXD0: P32
					// SCK0: P34
					uint8_t sel = enable ? 0b00'1011 : 0;  // ok
					PORT3::PMR.B3 = 0;
					PORT3::ODR.B3 = i2c;
					MPC::P33PFS.PSEL = sel;  // RXD0/SMISO0/SSCL0 (P33 LQFP176: 28)
					PORT3::PMR.B3 = enable;
					PORT3::PMR.B2 = 0;
					PORT3::ODR.B2 = i2c;
					MPC::P32PFS.PSEL = sel;  // TXD0/SMOSI0/SSDA0 (P32 LQFP176: 29)
					PORT3::PMR.B2 = enable;
					if(spi) {
						PORT3::PMR.B4 = 0;
						MPC::P34PFS.PSEL = sel;  // SCK0 (P34 LQFP176: 27)
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
					MPC::P52PFS.PSEL = sel;  // RXD2/SMISO2/SSCL2 (P52 LQFP176: 70)
					PORT5::PMR.B2 = enable;
					PORT5::PMR.B0 = 0;
					PORT5::ODR.B0 = i2c;
					MPC::P50PFS.PSEL = sel;  // TXD2/SMOSI2/SSDA2 (P50 LQFP176: 72)
					PORT5::PMR.B0 = enable;
					if(spi) {
						PORT5::PMR.B1 = 0;
						MPC::P51PFS.PSEL = sel;  // SCK2
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
					MPC::P25PFS.PSEL = sel;  // RXD3/SMOSI3/SSDA3 (P25 LQFP176: 38)
					PORT2::PMR.B5 = enable;
					PORT2::PMR.B3 = 0;
					PORT2::ODR.B3 = i2c;
					MPC::P23PFS.PSEL = sel;  // TXD3/SMISO3/SSCL3 (P23 LQFP176: 42)
					PORT2::PMR.B3 = enable;
					if(spi) {
						PORT2::PMR.B4 = 0;
						MPC::P24PFS.PSEL = sel;  // SCK3 (P24 LQFP176: 40)
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
			case peripheral::SCI7:
				{
					// RXD7: P92
					// TXD7: P90
					// SCK7: P91
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT9::PMR.B2 = 0;
					PORT9::ODR.B2 = i2c;
					MPC::P92PFS.PSEL = sel;  // RXD7/SMOSI7/SSDA7 (P92 LQFP176: 160)
					PORT9::PMR.B2 = enable;
					PORT9::PMR.B0 = 0;
					PORT9::ODR.B0 = i2c;
					MPC::P90PFS.PSEL = sel;  // TXD7/SMISO7/SSCL7 (P90 LQFP176: 163)
					PORT9::PMR.B0 = enable;
					if(spi) {
						PORT9::PMR.B1 = 0;
						MPC::P91PFS.PSEL = sel;  // SCK7 (P91 LQFP176: 161)
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

			case peripheral::QSPI:  // QSPI-B
				{
					// QSPCLK:   PD5
					// QSSL:     PD4
					// QMO/QIO0: PD6
					// QMI/QIO1: PD7
					// QIO2:     PD2
					// QIO3:     PD3
					uint8_t sel = enable ? 0b01'1011 : 0;  // ok
					PORTD::PMR.B5 = 0;
					MPC::PD5PFS.PSEL = sel;  // QSPCLK-B (PD5 LQFP176: 147)
					PORTD::PMR.B5 = enable;
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;  // QSSL-B   (PD4 LQFP176: 142)
					PORTD::PMR.B4 = enable;
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;  // QIO0-B   (PD6 LQFP176: 145)
					PORTD::PMR.B6 = enable;
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;  // QIO1-B   (PD7 LQFP176: 143)
					PORTD::PMR.B7 = enable;
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;  // QIO2-B   (PD2 LQFP176: 154)
					PORTD::PMR.B2 = enable;
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = sel;  // QIO3-B   (PD3 LQFP176: 150)
					PORTD::PMR.B3 = enable;
				}
				break;

			default:
				ret = false;
				break;
			}
			return ret;
		}


		static bool sub_3rd_(peripheral per, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			bool ret = true;
			switch(per) {
			case peripheral::SCI1:
				{
					// RXD1: PF2
					// TXD1: PF0
					// SCK1: PF1
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTF::PMR.B2 = 0;
					PORTF::ODR.B2 = i2c;
					MPC::PF2PFS.PSEL = sel;  // RXD1/SMOSI1/SSDA1 (PF2 LQFP176: 31)
					PORTF::PMR.B2 = enable;
					PORTF::PMR.B0 = 0;
					PORTF::ODR.B0 = i2c;
					MPC::PF0PFS.PSEL = sel;  // TXD1/SMISO1/SSCL1 (PF0 LQFP176: 35)
					PORTF::PMR.B0 = enable;
					if(spi) {
						PORTF::PMR.B1 = 0;
						MPC::PF1PFS.PSEL = sel;  // SCK1 (PF1 LQFP176: 34)
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
					uint8_t sel = enable ? 0b00'1011 : 0;  // ok
					PORTB::PMR.B1 = 0;
					PORTB::ODR.B1 = i2c;
					MPC::PB1PFS.PSEL = sel;  // TXD6/SMOSI6/SSDA6 (PB1 LQFP176: 100)
					PORTB::PMR.B1 = enable;
					PORTB::PMR.B0 = 0;
					PORTB::ODR.B0 = i2c;
					MPC::PB0PFS.PSEL = sel;  // RXD6/SMISO6/SSCL6 (PB0 LQFP176: 104)
					PORTB::PMR.B0 = enable;
					if(spi) {
						PORTB::PMR.B3 = 0;
						MPC::PB3PFS.PSEL = sel;  // SCK6 (PB3 LQFP176: 98)
						PORTB::PMR.B3 = enable;
					}
				}
				break;
			case peripheral::SCI10:
				{
					// RXD10: PC6
					// TXD10: PC7
					// SCK10: PC5
					uint8_t sel = enable ? 0b01'0100 : 0;  // ok
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

			default:
				ret = false;
				break;
			}
			return ret;
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
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = sel;  // SDHI_WP P24(33)
				PORT2::PMR.B4 = enable;
				PORT2::PMR.B5 = 0;
				MPC::P25PFS.PSEL = sel;  // SDHI_CD P25(32)
				PORT2::PMR.B5 = enable;
#if 0
				PORT2::PMR.B2 = 0;
				PORT2::PDR.B2 = 1;
				PORT2::PODR.B2 = 0;
				PORT2::PMR.B3 = 0;
				PORT2::PDR.B3 = 1;
				PORT2::PODR.B3 = 0;
				PORT8::PMR.B7 = 0;
				PORT8::PDR.B7 = 1;
				PORT8::PODR.B7 = 0;
				PORT1::PMR.B7 = 0;
				PORT1::PDR.B7 = 1;
				PORT1::PODR.B7 = 1;
#endif
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
#if 0
				PORT2::PMR.B2 = 0;
				PORT2::PDR.B2 = 0;
				PORT2::PODR.B2 = 0;
				PORT2::PMR.B3 = 0;
				PORT2::PDR.B3 = 0;
				PORT2::PODR.B3 = 0;
				PORT8::PMR.B7 = 0;
				PORT8::PDR.B7 = 0;
				PORT8::PODR.B7 = 0;
				PORT1::PMR.B7 = 0;
				PORT1::PDR.B7 = 0;
				PORT1::PODR.B7 = 0;
#endif
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
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = sel;  // SDHI_WP P24(33)
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
			@param[in]	state	SHDI 状態
			@param[in]	order	ポート・マップ・オプション（ポート候補）
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
	};
}

