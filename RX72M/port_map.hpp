#pragma once
//=========================================================================//
/*!	@file
	@brief	RX72M グループ・ポート・マッピング @n
			・ペリフェラル型に従って、ポートの設定をグループ化して設定 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX72M/peripheral.hpp"
#include "RX72N/port.hpp"
#include "RX72M/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map : public port_map_order {

		static bool sub_1st_(peripheral t, bool enable, ORDER opt)
		{
			bool ret = true;
			bool i2c = false;
			bool spi = false;
			switch(t) {
			case peripheral::USB0:
				{
					uint8_t sel = enable ? 0b010011 : 0;
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;  // USB0_VBUSEN (P24 LQFP176: 40)
					PORT2::PMR.B4 = enable;
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;  // USB0_OVRCURB (P22 LQFP176: 43)
					PORT2::PMR.B2 = enable;
				}
				break;
			// ※シリアルポートの MPC 設定では、PDR を制御する必要は無いが、
			// 出力ポートのインピーダンス制御の一環として入れてある。
			case peripheral::SCI0:
				{
					if(i2c) {
						PORT2::ODR0.B0 = 1;  // P20 N-OpenDrain
						PORT2::ODR0.B2 = 1;  // P21 N-OpenDrain
						PORT2::PDR.B0 = 1;
						PORT2::PDR.B1 = 1;
						PORT2::PODR.B0 = 1;
						PORT2::PODR.B1 = 1;
					}
					uint8_t sel = enable ? 0b001010 : 0;
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = sel;  // TXD0/SMISO0/SSCL0 (P20 LQFP176: 45)
					PORT2::PMR.B0 = enable;
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;  // RXD0/SMOSI0/SSDA0 (P21 LQFP176: 44)
					PORT2::PMR.B1 = enable;
					if(spi) {
						PORT2::PMR.B2 = 0;
						MPC::P22PFS.PSEL = sel;  // SCK0 (P22 LQFP176: 43)
						PORT2::PMR.B2 = enable;
					}
				}
				break;
			case peripheral::SCI1:
				{
					if(i2c) {
						PORTF::ODR0.B0 = 1;  // PF0 N-OpenDrain
						PORTF::ODR0.B4 = 1;  // PF2 N-OpenDrain
						PORTF::PDR.B0 = 1;
						PORTF::PDR.B2 = 1;
						PORTF::PODR.B0 = 1;
						PORTF::PODR.B2 = 1;
					}
					uint8_t sel = enable ? 0b001010 : 0;
					PORTF::PMR.B0 = 0;
					MPC::PF0PFS.PSEL = sel;  // TXD1/SMISO1/SSCL1 (PF0 LQFP176: 35)
					PORTF::PMR.B0 = enable;
					PORTF::PMR.B2 = 0;
					MPC::PF2PFS.PSEL = sel;  // RXD1/SMOSI1/SSDA1 (PF2 LQFP176: 31)
					PORTF::PMR.B2 = enable;
					if(spi) {
						PORTF::PMR.B1 = 0;
						MPC::PF1PFS.PSEL = sel;  // SCK1 (PF1 LQFP176: 34)
						PORTF::PMR.B1 = enable;
					}
				}
				break;
			case peripheral::SCI2:
				{
					if(i2c) {
						PORT1::ODR0.B6 = 1;  // P13 N-OpenDrain
						PORT1::ODR0.B4 = 1;  // P12 N-OpenDrain
						PORT1::PDR.B3 = 1;
						PORT1::PDR.B2 = 1;
						PORT1::PODR.B3 = 1;
						PORT1::PODR.B2 = 1;
					}
					uint8_t sel = enable ? 0b001010 : 0;
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;  // TXD2/SMISO2/SSCL2 (P13 LQFP176: 52)
					PORT1::PMR.B3 = enable;
					PORT1::PMR.B2 = 0;
					MPC::P12PFS.PSEL = sel;  // RXD2/SMOSI2/SSDA2 (P12 LQFP176: 53)
					PORT1::PMR.B2 = enable;
					if(spi) {
						PORT1::PMR.B1 = 0;
						MPC::P11PFS.PSEL = sel;  // SCK2 (P11 LQFP176: 67)
						PORT1::PMR.B1 = enable;
					}
				}
				break;
			case peripheral::SCI3:
				{
					if(i2c) {
						PORT2::ODR0.B6 = 1;  // P23 N-OpenDrain
						PORT2::ODR1.B2 = 1;  // P25 N-OpenDrain
						PORT2::PDR.B3 = 1;
						PORT2::PDR.B5 = 1;
						PORT2::PODR.B3 = 1;
						PORT2::PODR.B5 = 1;
					}
					uint8_t sel = enable ? 0b001010 : 0;
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;  // TXD3/SMISO3/SSCL3 (P23 LQFP176: 42)
					PORT2::PMR.B3 = enable;
					PORT2::PMR.B5 = 0;
					MPC::P25PFS.PSEL = sel;  // RXD3/SMOSI3/SSDA3 (P25 LQFP176: 38)
					PORT2::PMR.B5 = enable;
					if(spi) {
						PORT2::PMR.B4 = 0;
						MPC::P24PFS.PSEL = sel;  // SCK3 (P24 LQFP176: 40)
						PORT2::PMR.B4 = enable;
					}
				}
				break;
			case peripheral::SCI4:
				{
					if(i2c) {
						PORTB::ODR0.B2 = 1;  // PB1 N-OpenDrain
						PORTB::ODR0.B0 = 1;  // PB0 N-OpenDrain
						PORTB::PDR.B1 = 1;
						PORTB::PDR.B0 = 1;
						PORTB::PODR.B1 = 1;
						PORTB::PODR.B0 = 1;
					}
					uint8_t sel = enable ? 0b001010 : 0;
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;  // TXD4/SMISO4/SSCL4 (PB1 LQFP176: 100)
					PORTB::PMR.B1 = enable;
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;  // RXD4/SMOSI4/SSDA4 (PB0 LQFP176: 104)
					PORTB::PMR.B0 = enable;
					if(spi) {
						PORTB::PMR.B3 = 0;
						MPC::PB3PFS.PSEL = sel;  // SCK4 (PB3 LQFP176: 98)
						PORTB::PMR.B3 = enable;
					}
				}
				break;
			case peripheral::SCI5:
				{
					if(i2c) {
						PORTA::ODR1.B0 = 1;  // PA4 N-OpenDrain
						PORTA::ODR0.B6 = 1;  // PA3 N-OpenDrain
						PORTA::PDR.B4 = 1;
						PORTA::PDR.B3 = 1;
						PORTA::PODR.B4 = 1;
						PORTA::PODR.B3 = 1;
					}
					uint8_t sel = enable ? 0b001010 : 0;
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;  // TXD5/SMISO5/SSCL5 (PA4 LQFP176: 109)
					PORTA::PMR.B4 = enable;
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = sel;  // RXD5/SMOSI5/SSDA5 (PA3 LQFP176: 110)
					PORTA::PMR.B3 = enable;
					if(spi) {
						PORTA::PMR.B1 = 0;
						MPC::PA1PFS.PSEL = sel;  // SCK5 (PA1 LQFP176: 114)
						PORTA::PMR.B1 = enable;
					}
				}
				break;
			case peripheral::SCI6:
				{
					if(i2c) {
						PORT0::ODR0.B0 = 1;  // P00 N-OpenDrain
						PORT0::ODR0.B2 = 1;  // P01 N-OpenDrain
						PORT0::PDR.B0 = 1;
						PORT0::PDR.B1 = 1;
						PORT0::PODR.B0 = 1;
						PORT0::PODR.B1 = 1;
					}
					uint8_t sel = enable ? 0b001010 : 0;
					PORT0::PMR.B0 = 0;
					MPC::P00PFS.PSEL = sel;  // TXD6/SMISO6/SSCL6 (P00 LQFP176: 8)
					PORT0::PMR.B0 = enable;
					PORT0::PMR.B1 = 0;
					MPC::P01PFS.PSEL = sel;  // RXD6/SMOSI6/SSDA6 (P01 LQFP176: 7)
					PORT0::PMR.B1 = enable;
					if(spi) {
						PORT0::PMR.B2 = 0;
						MPC::P02PFS.PSEL = sel;  // SCK6 (P02 LQFP176: 6)
						PORT0::PMR.B2 = enable;
					}
				}
				break;
			case peripheral::SCI7:
				{
					if(i2c) {
						PORT9::ODR0.B0 = 1;  // P90 N-OpenDrain
						PORT9::ODR0.B4 = 1;  // P92 N-OpenDrain
						PORT9::PDR.B0 = 1;
						PORT9::PDR.B2 = 1;
						PORT9::PODR.B0 = 1;
						PORT9::PODR.B2 = 1;
					}
					uint8_t sel = enable ? 0b001010 : 0;
					PORT9::PMR.B0 = 0;
					MPC::P90PFS.PSEL = sel;  // TXD7/SMISO7/SSCL7 (P90 LQFP176: 163)
					PORT9::PMR.B0 = enable;
					PORT9::PMR.B2 = 0;
					MPC::P92PFS.PSEL = sel;  // RXD7/SMOSI7/SSDA7 (P92 LQFP176: 160)
					PORT9::PMR.B2 = enable;
					if(spi) {
						PORT9::PMR.B1 = 0;
						MPC::P91PFS.PSEL = sel;  // SCK7 (P91 LQFP176: 161)
						PORT9::PMR.B1 = enable;
					}
				}
				break;

			case peripheral::SCI8:
				{
					if(i2c) {
						PORTC::ODR1.B6 = 1;  // PC7 N-OpenDrain
						PORTC::ODR1.B4 = 1;  // PC6 N-OpenDrain
						PORTC::PDR.B7 = 1;
						PORTC::PDR.B6 = 1;
						PORTC::PODR.B7 = 1;
						PORTC::PODR.B6 = 1;
					}
					uint8_t sel = enable ? 0b001010 : 0;
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;  // TXD(F)8/SMISO8/SSCL8 (PC7 LQFP176: 76)
					PORTC::PMR.B7 = enable;
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;  // RXD(F)8/SMOSI8/SSDA8 (PC6 LQFP176: 77)
					PORTC::PMR.B6 = enable;
					if(spi) {
						PORTC::PMR.B5 = 0;
						MPC::PC5PFS.PSEL = sel;  // SCK8 (PC5 LQFP176: 78)
						PORTC::PMR.B5 = enable;
					}
				}
				break;

			case peripheral::SCI9:
				{
					if(i2c) {
						PORTB::ODR1.B6 = 1;  // PB7 N-OpenDrain
						PORTB::ODR1.B4 = 1;  // PB6 N-OpenDrain
						PORTB::PDR.B7 = 1;
						PORTB::PDR.B6 = 1;
						PORTB::PODR.B7 = 1;
						PORTB::PODR.B6 = 1;
					}
					uint8_t sel = enable ? 0b001010 : 0;
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;  // TXD(F)9/SMISO9/SSCL9 (PB7 LQFP176: 94)
					PORTB::PMR.B7 = enable;
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;  // RXD(F)9/SMOSI9/SSDA9 (PB6 LQFP176: 95)
					PORTB::PMR.B6 = enable;
					if(spi) {
						PORTB::PMR.B5 = 0;
						MPC::PB5PFS.PSEL = sel;  // SCK9 (PB5 LQFP176: 96)
						PORTB::PMR.B5 = enable;
					}
				}
				break;

			case peripheral::SCI10:
				{
					if(i2c) {
						PORT8::ODR1.B6 = 1;  // P87 N-OpenDrain
						PORT8::ODR1.B4 = 1;  // P86 N-OpenDrain
						PORT8::PDR.B7 = 1;
						PORT8::PDR.B6 = 1;
						PORT8::PODR.B7 = 1;
						PORT8::PODR.B6 = 1;
					}
					uint8_t sel = enable ? 0b001010 : 0;
					PORT8::PMR.B7 = 0;
					MPC::P87PFS.PSEL = sel;  // TXD(F)10/SMISO10/SSCL10 (P86 LQFP176: 47)
					PORT8::PMR.B7 = enable;
					PORT8::PMR.B6 = 0;
					MPC::P86PFS.PSEL = sel;  // RXD(F)10/SMOSI10/SSDA10 (P87 LQFP176: 49)
					PORT8::PMR.B6 = enable;
					if(spi) {
						ret = false;
					}
				}
				break;

			case peripheral::SCI11:
				{
					if(i2c) {
						PORT7::ODR1.B6 = 1;  // P77 N-OpenDrain
						PORT7::ODR1.B4 = 1;  // P76 N-OpenDrain
						PORT7::PDR.B7 = 1;
						PORT7::PDR.B6 = 1;
						PORT7::PODR.B7 = 1;
						PORT7::PODR.B6 = 1;
					}
					uint8_t sel = enable ? 0b001010 : 0;
					PORT7::PMR.B7 = 0;
					MPC::P77PFS.PSEL = sel;  // TXD(F)11/SMISO11/SSCL11 (P77 LQFP176: 84)
					PORT7::PMR.B7 = enable;
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;  // RXD(F)11/SMOSI11/SSDA11 (P76 LQFP176: 85)
					PORT7::PMR.B6 = enable;
					if(spi) {
						PORT7::PMR.B5 = 0;
						MPC::P75PFS.PSEL = sel;  // SCK11 (P75 LQFP176: 87)
						PORT7::PMR.B5 = enable;
					}
				}
				break;

			case peripheral::SCI12:
				{
					if(i2c) {
						PORTE::ODR0.B4 = 1;  // PE2 N-OpenDrain
						PORTE::ODR0.B2 = 1;  // PE1 N-OpenDrain
						PORTE::PDR.B2 = 1;
						PORTE::PDR.B1 = 1;
						PORTE::PODR.B2 = 1;
						PORTE::PODR.B1 = 1;
					}
					uint8_t sel = enable ? 0b001100 : 0;
					PORTE::PMR.B2 = 0;
					MPC::PE2PFS.PSEL = sel;  // RXD12/SMISO12/SSCL12 (PE2 LQFP176: 133)
					PORTE::PMR.B2 = enable;
					PORTE::PMR.B1 = 0;
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
					uint8_t sel = enable ? 0b001111 : 0;
					PORT1::PMR.B2 = 0;
					MPC::P12PFS.PSEL = sel;  // SCL0 (P12 LQFP176: 53)
					PORT1::PMR.B2 = enable;
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;  // SDA0 (P13 LQFP176: 52)
					PORT1::PMR.B3 = enable;
				}
				break;

			case peripheral::RIIC1:
				{  // 100ピン未満未対応
					uint8_t sel = enable ? 0b001111 : 0;
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = sel;  // SCL1 (P20 LQFP176: 45)
					PORT2::PMR.B0 = enable;
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;  // SDA1 (P21 LQFP176: 44)
					PORT2::PMR.B1 = enable;
				}
				break;
			case peripheral::RIIC2:
				{
					uint8_t sel = enable ? 0b001111 : 0;
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;  // SCL2 (P16 LQFP176: 48)
					PORT1::PMR.B6 = enable;
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;  // SDA2 (P17 LQFP176: 46)
					PORT1::PMR.B7 = enable;
				}
				break;

			case peripheral::RSPI0:
				{
					uint8_t sel = enable ? 0b001101 : 0;
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;  // MISOA-A  (PC7 LQFP176: 76)
					PORTC::PMR.B7 = enable;
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;  // MOSIA-A  (PC6 LQFP176: 77)
					PORTC::PMR.B6 = enable;
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;  // RSPCKA-A (PC5 LQFP176: 78)
					PORTC::PMR.B5 = enable;
				}
				break;

			case peripheral::CAN0:
				{
					uint8_t sel = enable ? 0b010000 : 0;
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;  // CTX0 (P32 LQFP176: 29)
					PORT3::PMR.B2 = 1;
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;  // CRX0 (P33 LQFP176: 28)
					PORT3::PMR.B3 = 1;
				}
				break;
			case peripheral::CAN1:
				{
					uint8_t sel = enable ? 0b010000 : 0;
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;  // CTX1    (P14 LQFP176: 51)
					PORT1::PMR.B4 = 1;
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;  // CRX1-DS (P15 LQFP176: 50)
					PORT1::PMR.B5 = 1;
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
				ret = false;
				break;
			}
			return ret;
		}


		static bool sub_2nd_(peripheral t, bool enable, ORDER opt)
		{
			bool ret = true;
			bool i2c = false;
			bool spi = false;
			switch(t) {
			case peripheral::SCI0:
				{
					if(i2c) {
						PORT3::ODR0.B4 = 1;  // P32 N-OpenDrain
						PORT3::ODR0.B6 = 1;  // P33 N-OpenDrain
						PORT3::PDR.B2 = 1;
						PORT3::PDR.B3 = 1;
						PORT3::PODR.B2 = 1;
						PORT3::PODR.B3 = 1;
					}
					uint8_t sel = enable ? 0b001010 : 0;
					PORT3::PMR.B2 = 0;
					PORT3::PMR.B3 = 0;
					MPC::P32PFS.PSEL = sel;  // TXD0/SMOSI0/SSDA0 (P32 LQFP176: 29)
					MPC::P33PFS.PSEL = sel;  // RXD0/SMISO0/SSCL0 (P33 LQFP176: 28)
					PORT3::PMR.B2 = enable;
					PORT3::PMR.B3 = enable;
					if(spi) {
						PORT3::PMR.B4 = 0;
						MPC::P34PFS.PSEL = sel;  // SCK0 (P34 LQFP176: 27)
						PORT3::PMR.B4 = enable;
					}
				}
				break;

			case peripheral::SCI2:
				{
					if(i2c) {
						PORT5::ODR0.B0 = 1;  // P50 N-OpenDrain
						PORT5::ODR0.B4 = 1;  // P52 N-OpenDrain
						PORT5::PDR.B0 = 1;
						PORT5::PDR.B2 = 1;
						PORT5::PODR.B0 = 1;
						PORT5::PODR.B2 = 1;
					}
					uint8_t sel = enable ? 0b001010 : 0;
					PORT5::PMR.B0 = 0;
					PORT5::PMR.B2 = 0;
					MPC::P50PFS.PSEL = sel;  // TXD2/SMOSI2/SSDA2 (P50 LQFP176: 72)
					MPC::P52PFS.PSEL = sel;  // RXD2/SMISO2/SSCL2 (P52 LQFP176: 70)
					PORT5::PMR.B0 = enable;
					PORT5::PMR.B2 = enable;
					if(spi) {
						PORT5::PMR.B1 = 0;
						MPC::P51PFS.PSEL = sel;  // SCK2 (P52 LQFP176: 71)
						PORT5::PMR.B1 = enable;
					}
				}
				break;

			case peripheral::SCI3:
				{
					if(i2c) {
						PORT1::ODR1.B6 = 1;  // P17 N-OpenDrain
						PORT1::ODR1.B4 = 1;  // P16 N-OpenDrain
						PORT1::PDR.B7 = 1;
						PORT1::PDR.B6 = 1;
						PORT1::PODR.B7 = 1;
						PORT1::PODR.B6 = 1;
					}
					uint8_t sel = enable ? 0b001010 : 0;
					PORT1::PMR.B7 = 0;
					PORT1::PMR.B6 = 0;
					MPC::P17PFS.PSEL = sel;  // TXD3/SMOSI3/SSDA3 (P17 LQFP176: 46)
					MPC::P16PFS.PSEL = sel;  // RXD3/SMISO3/SSCL3 (P16 LQFP176: 48)
					PORT1::PMR.B7 = enable;
					PORT1::PMR.B6 = enable;
					if(spi) {
						PORT1::PMR.B5 = 0;
						MPC::P15PFS.PSEL = sel;  // SCK3 (P15 LQFP176: 50)
						PORT1::PMR.B5 = enable;
					}
				}
				break;

			case peripheral::SCI6:
				{
					if(i2c) {
						PORTB::ODR0.B2 = 1;  // PB1 N-OpenDrain
						PORTB::ODR0.B0 = 1;  // PB0 N-OpenDrain
						PORTB::PDR.B1 = 1;
						PORTB::PDR.B0 = 1;
						PORTB::PODR.B1 = 1;
						PORTB::PODR.B0 = 1;
					}
					uint8_t sel = enable ? 0b001010 : 0;
					PORTB::PMR.B1 = 0;
					PORTB::PMR.B0 = 0;
					MPC::PB1PFS.PSEL = sel;  // TXD6/SMOSI6/SSDA6 (PB1 LQFP176: 100)
					MPC::PB0PFS.PSEL = sel;  // RXD6/SMISO6/SSCL6 (PB0 LQFP176: 104)
					PORTB::PMR.B1 = enable;
					PORTB::PMR.B0 = enable;
					if(spi) {
						PORTB::PMR.B3 = 0;
						MPC::PB3PFS.PSEL = sel;  // SCK6 (PB3 LQFP176: 98)
						PORTB::PMR.B3 = enable;
					}
				}
				break;

			case peripheral::RSPI0:
				{
					uint8_t sel = enable ? 0b001101 : 0;
					PORTA::PMR.B7 = 0;
					MPC::PA7PFS.PSEL = sel;  // MISOA-B  (PA7 LQFP176: 106)
					PORTA::PMR.B7 = enable;
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = sel;  // MOSIA-B  (PA6 LQFP176: 107)
					PORTA::PMR.B6 = enable;
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;  // RSPCKA-B (PA5 LQFP176: 108)
					PORTA::PMR.B5 = enable;
				}
				break;

			case peripheral::CAN0:
				{
					uint8_t sel = enable ? 0b010000 : 0;
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;  // CTX0 (PD1 LQFP176: 156)
					PORTD::PMR.B1 = enable;
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;  // CRX0 (PD2 LQFP176: 154)
					PORTD::PMR.B2 = enable;
				}
				break;
			case peripheral::CAN1:
				{
					uint8_t sel = enable ? 0b010000 : 0;
					PORT5::PMR.B4 = 0;
					MPC::P54PFS.PSEL = sel;  // CTX1 (P54 LQFP176: 66)
					PORT5::PMR.B4 = enable;
					PORT5::PMR.B5 = 0;
					MPC::P55PFS.PSEL = sel;  // CRX1 (P55 LQFP176: 65)
					PORT5::PMR.B5 = enable;
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

	public:
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
			@brief  SDHI ポート専用切り替え
			@param[in]	state	SHDI 状態
			@param[in]	order	ポート・マップ・オプション候補
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
			@brief  周辺機器に切り替える
			@param[in]	per	周辺機器タイプ
			@param[in]	ena	無効にする場合「false」
			@param[in]	opt	ポート・マップ・オプション
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(peripheral per, bool ena = true, ORDER opt = ORDER::FIRST) noexcept
		{
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			switch(opt) {
			case ORDER::FIRST:
				ret = sub_1st_(per, ena, opt);
				break;
			case ORDER::SECOND:
				ret = sub_2nd_(per, ena, opt);
				break;
			default:
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
