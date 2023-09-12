#pragma once
//=========================================================================//
/*!	@file
	@brief	RX26T グループ・ポート・マッピング @n
			・ポートの選択は「候補」に従うポリシーを採用している。 @n
			・単独で指定する場合や、グループで指定する場合などがある。 @n
			・独自に指定する場合、「BYPASS」を選択する事が出来る。 @n
			・「候補」の順番は、ハードウェアーマニュアル MPC の解説に準拠している。 @n
			※上記ルールに従っていない場合もあるので注意が必要（工事中）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX26T/peripheral.hpp"
#include "RX26T/port.hpp"
#include "RX26T/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map : public port_map_order {
	private:

		static bool sci1_(ORDER opt, bool enable)
		{
			uint8_t sel = enable ? 0b00'1010 : 0;
			switch(opt) {
			case ORDER::FIRST_I2C:
			case ORDER::FIRST_SPI:
			// PD4/SCK1
				PORTD::PMR.B4 = 0;
				MPC::PD4PFS.PSEL = sel;
				PORTD::PMR.B4 = enable;
			case ORDER::FIRST:
			// PD5/RXD1
				PORTD::PMR.B3 = 0;
				MPC::PD3PFS.PSEL = sel;
				PORTD::PMR.B3 = enable;
			// PD3/TXD1
				PORTD::PMR.B5 = 0;
				MPC::PD5PFS.PSEL = sel;
				PORTD::PMR.B5 = enable;
				break;
			default:
				return false;
			}
			return true;
		}


		static bool sci5_(ORDER opt, bool enable)
		{
			uint8_t sel = enable ? 0b00'1010 : 0;
			switch(opt) {
			case ORDER::FIRST_I2C:
			case ORDER::FIRST_SPI:
			// P70/SCK5
				PORT7::PMR.B0 = 0;
				MPC::P70PFS.PSEL = sel;
				PORT7::PMR.B0 = enable;
			case ORDER::FIRST:
			// P37/RXD5
				PORT3::PMR.B7 = 0;
				MPC::P37PFS.PSEL = sel;
				PORT3::PMR.B7 = enable;
			// P36/TXD5
				PORT3::PMR.B6 = 0;
				MPC::P36PFS.PSEL = sel;
				PORT3::PMR.B6 = enable;
				break;
			case ORDER::SECOND_I2C:
			case ORDER::SECOND_SPI:
			// P70/SCK5
				PORT7::PMR.B0 = 0;
				MPC::P70PFS.PSEL = sel;
				PORT7::PMR.B0 = enable;
			case ORDER::SECOND:
			// P91/RXD5
				PORT9::PMR.B1 = 0;
				MPC::P91PFS.PSEL = sel;
				PORT9::PMR.B1 = enable;
			// P90/TXD5
				PORT9::PMR.B0 = 0;
				MPC::P90PFS.PSEL = sel;
				PORT9::PMR.B0 = enable;
				break;
			case ORDER::THIRD_I2C:
			case ORDER::THIRD_SPI:
			// PB7/SCK5
				PORTB::PMR.B7 = 0;
				MPC::PB7PFS.PSEL = sel;
				PORTB::PMR.B7 = enable;
			case ORDER::THIRD:
			// PB6/RXD5
				PORTB::PMR.B6 = 0;
				MPC::PB6PFS.PSEL = sel;
				PORTB::PMR.B6 = enable;
			// PB5/TXD5
				PORTB::PMR.B5 = 0;
				MPC::PB5PFS.PSEL = sel;
				PORTB::PMR.B5 = enable;
				break;
			case ORDER::FOURTH_I2C:
			case ORDER::FOURTH_SPI:
			// PD2/SCK5
				PORTD::PMR.B2 = 0;
				MPC::PD2PFS.PSEL = sel;
				PORTD::PMR.B2 = enable;
			case ORDER::FOURTH:
			// PE0/RXD5
				PORTE::PMR.B0 = 0;
				MPC::PE0PFS.PSEL = sel;
				PORTE::PMR.B0 = enable;
			// PD7/TXD5
				PORTD::PMR.B7 = 0;
				MPC::PD7PFS.PSEL = sel;
				PORTD::PMR.B7 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sci6_(ORDER opt, bool enable)
		{
			uint8_t sel = enable ? 0b00'1010 : 0;
			switch(opt) {
			case ORDER::FIRST_I2C:
			case ORDER::FIRST_SPI:
			// P82/SCK6
				PORT8::PMR.B2 = 0;
				MPC::P82PFS.PSEL = sel;
				PORT8::PMR.B2 = enable;
			case ORDER::FIRST:
			// P80/RXD6
				PORT8::PMR.B0 = 0;
				MPC::P80PFS.PSEL = sel;
				PORT8::PMR.B0 = enable;
			// P81/TXD6
				PORT8::PMR.B1 = 0;
				MPC::P81PFS.PSEL = sel;
				PORT8::PMR.B1 = enable;
				break;
			case ORDER::SECOND_I2C:
			case ORDER::SECOND_SPI:
			// PA4/SCK5
				PORTA::PMR.B4 = 0;
				MPC::PA4PFS.PSEL = sel;
				PORTA::PMR.B4 = enable;
			case ORDER::SECOND:
			// P95/RXD5
				PORT9::PMR.B5 = 0;
				MPC::P95PFS.PSEL = sel;
				PORT9::PMR.B5 = enable;
			// PB0/TXD5
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;
				PORTB::PMR.B0 = enable;
				break;
			case ORDER::THIRD_I2C:
			case ORDER::THIRD_SPI:
			// PB3/SCK5
				PORTB::PMR.B3 = 0;
				MPC::PB3PFS.PSEL = sel;
				PORTB::PMR.B3 = enable;
			case ORDER::THIRD:
			// PB1/RXD5
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = sel;
				PORTB::PMR.B1 = enable;
			// PB2/TXD5
				PORTB::PMR.B2 = 0;
				MPC::PB2PFS.PSEL = sel;
				PORTB::PMR.B2 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

#if 0
		static bool rsci8_(ORDER opt, bool enable)
		{
			uint8_t sel;
			switch(opt) {
			case ORDER::FIRST:
			// PA5/RXD8 (36/100) (54/144)
			// PA4/TXD8 (37/100) (55/144)
			// PA3/SCK8 (38/100) (56/144)
				sel = enable ? 0b001011 : 0;
				if(clock) {
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = sel;
					PORTA::PMR.B3 = enable;
				}
				PORTA::PMR.B5 = 0;
				PORTA::PMR.B4 = 0;
				MPC::PA5PFS.PSEL = sel;
				MPC::PA4PFS.PSEL = sel;
				PORTA::PMR.B5 = enable;
				PORTA::PMR.B4 = enable;
				break;
			case ORDER::SECOND:
			// P24/SCK8 (65/100) (95/144)
			// P23/TXD8 (66/100) (96/144)
			// P22/RXD8 (67/100) (97/144)
				if(clock) {
					sel = enable ? 0b01011 : 0;
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;
					PORT2::PMR.B4 = enable;
				}
				sel = enable ? 0b001010 : 0;
				PORT2::PMR.B3 = 0;
				PORT2::PMR.B2 = 0;
				MPC::P23PFS.PSEL = sel;
				MPC::P22PFS.PSEL = sel;
				PORT2::PMR.B3 = enable;
				PORT2::PMR.B2 = enable;
				break;
			case ORDER::THIRD:
			// PD2/SCK8 (28/144)
			// PD1/RXD8 (29/144)
			// PD0/TXD8 (30/144)
				sel = enable ? 0b001011 : 0;
				if(clock) {
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = sel;
					PORT3::PMR.B0 = enable;
				}
				PORT2::PMR.B3 = 0;
				PORT2::PMR.B2 = 0;
				MPC::P23PFS.PSEL = sel;
				MPC::P22PFS.PSEL = sel;
				PORT2::PMR.B3 = enable;
				PORT2::PMR.B2 = enable;
				break;
			case ORDER::FOURTH:
			// PC2/SCK8 (45/144)
			// PC1/TXD8 (46/144)
			// PC0/RXD8 (47/144)
				sel = enable ? 0b001011 : 0;
				if(clock) {
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = sel;
					PORTC::PMR.B2 = enable;
				}
				PORTC::PMR.B1 = 0;
				PORTC::PMR.B0 = 0;
				MPC::PC1PFS.PSEL = sel;
				MPC::PC0PFS.PSEL = sel;
				PORTC::PMR.B1 = enable;
				PORTC::PMR.B0 = enable;
				break;

			default:
				return false;
			}
			return true;
		}


		static bool rsci9_(ORDER opt, bool enable)
		{
			uint8_t sel;
			switch(opt) {
			case ORDER::FIRST:
			// PE4/SCK9 (1/100) (13/144)
			// P00/RXD9 (4/100) ( 9/144)
			// P01/TXD9 (7/100) (12/144)
				sel = enable ? 0b001010 : 0; 
				if(clock) {
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = sel;
					PORTE::PMR.B5 = enable;
				}
				PORT0::PMR.B0 = 0;
				PORT0::PMR.B1 = 0;
				MPC::P00PFS.PSEL = sel;
				MPC::P01PFS.PSEL = sel;
				PORT0::PMR.B0 = enable;
				PORT0::PMR.B1 = enable;
				break;
			case ORDER::SECOND:
			// PA2/RXD9 (39/100) (57/144)
			// PA1/TXD9 (40/100) (58/144)
			// PA0/SCK9 (41/100) (59/144)
				sel = enable ? 0b001010 : 0;
				if(clock) {
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;
					PORTA::PMR.B0 = enable;
				}
				PORTA::PMR.B2 = 0;
				PORTA::PMR.B1 = 0;
				MPC::PA2PFS.PSEL = enable ? 0b001011 : 0;
				MPC::PA1PFS.PSEL = sel;
				PORTA::PMR.B2 = enable;
				PORTA::PMR.B1 = enable;
				break;
			case ORDER::THIRD:
			// PG2/SCK9 (80/144)
			// PG1/TXD9 (81/144)
			// PG0/RXD9 (82/144)
				sel = enable ? 0b001010 : 0;
				if(clock) {
					PORTG::PMR.B2 = 0;
					MPC::PG2PFS.PSEL = sel;
					PORTG::PMR.B2 = enable;
				}
				PORTG::PMR.B1 = 0;
				PORTG::PMR.B0 = 0;
				MPC::PG1PFS.PSEL = sel;
				MPC::PG0PFS.PSEL = sel;
				PORTG::PMR.B1 = enable;
				PORTG::PMR.B2 = enable;
				break;

			default:
				return false;
			}
			return true;
		}


		static bool rsci11_(ORDER opt, bool enable)
		{
			uint8_t sel;
			switch(opt) {
			case ORDER::FIRST:
			// PB6/RXD11 (27/100) (40/144)
			// PB5/TXD11 (28/100) (41/144)
			// PB4/SCK11 (30/100) (43/144)
				sel = enable ? 0b001011 : 0; 
				if(clock) {
					PORTB::PMR.B4 = 0;
					MPC::PB4PFS.PSEL = sel;
					PORTB::PMR.B4 = enable;
				}
				PORTB::PMR.B6 = 0;
				PORTB::PMR.B5 = 0;
				MPC::PB6PFS.PSEL = sel;
				MPC::PB5PFS.PSEL = sel;
				PORTB::PMR.B6 = enable;
				PORTB::PMR.B5 = enable;
				break;
			case ORDER::SECOND:
			// PA2/SCK11 (39/100) (57/144)
			// PA1/RXD11 (40/100) (58/144)
			// PA0/TXD11 (41/100) (59/144)
				sel = enable ? 0b001011 : 0;
				if(clock) {
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = sel;
					PORTA::PMR.B2 = enable;
				}
				PORTA::PMR.B1 = 0;
				PORTA::PMR.B0 = 0;
				MPC::PA1PFS.PSEL = sel;
				MPC::PA0PFS.PSEL = sel;
				PORTA::PMR.B1 = enable;
				PORTA::PMR.B0 = enable;
				break;
			case ORDER::THIRD:
			// PD5/RXD11 (25/144)
			// PD4/SCK11 (26/144)
			// PD3/TXD11 (27/144)
				sel = enable ? 0b001011 : 0;
				if(clock) {
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;
					PORTD::PMR.B4 = enable;
				}
				PORTD::PMR.B5 = 0;
				PORTD::PMR.B3 = 0;
				MPC::PD5PFS.PSEL = sel;
				MPC::PD3PFS.PSEL = sel;
				PORTD::PMR.B5 = enable;
				PORTD::PMR.B3 = enable;
				break;
			case ORDER::FOURTH:
			// PF2/SCK11 (32/144)
			// PF1/RXD11 (33/144)
			// PF0/TXD11 (34/144)
				sel = enable ? 0b001010 : 0;
				if(clock) {
					PORTF::PMR.B2 = 0;
					MPC::PF2PFS.PSEL = sel;
					PORTF::PMR.B2 = enable;
				}
				PORTF::PMR.B1 = 0;
				PORTF::PMR.B0 = 0;
				MPC::PF1PFS.PSEL = sel;
				MPC::PF0PFS.PSEL = sel;
				PORTF::PMR.B1 = enable;
				PORTF::PMR.B0 = enable;
				break;
			case ORDER::FIFTH:
			// PB7/SCK11 (39/144)
			// PB6/RXD11 (40/144)
			// PB5/TXD11 (41/144)
				sel = enable ? 0b001011 : 0;
				if(clock) {
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;
					PORTB::PMR.B7 = enable;
				}
				PORTB::PMR.B6 = 0;
				PORTB::PMR.B5 = 0;
				MPC::PB6PFS.PSEL = sel;
				MPC::PB5PFS.PSEL = sel;
				PORTB::PMR.B6 = enable;
				PORTB::PMR.B5 = enable;
				break;
			case ORDER::SIXTH:
			// PA7/RXD11 (52/144)
			// PA6/TXD11 (53/144)
			// PA2/SCK11 (57/144)
				if(clock) {
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = enable ? 0b001100 : 0;
					PORTA::PMR.B2 = enable;
				}
				sel = enable ? 0b001010 : 0;
				PORTA::PMR.B7 = 0;
				PORTA::PMR.B6 = 0;
				MPC::PA7PFS.PSEL = sel;
				MPC::PA6PFS.PSEL = sel;
				PORTA::PMR.B7 = enable;
				PORTA::PMR.B6 = enable;
				break;
			case ORDER::SEVENTH:
			// PC6/RXD11 (62/144)
			// PC5/TXD11 (63/144)
				sel = enable ? 0b001010 : 0;
				PORTC::PMR.B6 = 0;
				PORTC::PMR.B5 = 0;
				MPC::PC6PFS.PSEL = sel;
				MPC::PC5PFS.PSEL = sel;
				PORTC::PMR.B6 = enable;
				PORTC::PMR.B5 = enable;
				break;
			default:
				return false;
			}
			return true;
		}


		static bool sci12_(ORDER opt, bool enable)
		{
			uint8_t sel;
			switch(opt) {
			case ORDER::FIRST:
			// P00/RXD12 (4/100) (/144)
			// P01/TXD12 (7/100) (/144)
				sel = enable ? 0b001011 : 0; 
				PORTB::PMR.B6 = 0;
				PORTB::PMR.B5 = 0;
				MPC::PB6PFS.PSEL = sel;
				MPC::PB5PFS.PSEL = sel;
				PORTB::PMR.B6 = enable;
				PORTB::PMR.B5 = enable;
				break;
			default:
				return false;
			}
			return true;
		}


		static bool rspi0_(ORDER opt, bool enable)
		{
			uint8_t sel = enable ? 0b001101 : 0;
			switch(opt) {

			case ORDER::FIRST:
				// P22/MISOA  (67/100) ( 97/100)
				// P21/MOSIA  (68/100) (100/144)
				// P20/RSPCKA (69/100) (101/144)
				{
					PORT2::PMR.B2 = 0;
					PORT2::PMR.B1 = 0;
					PORT2::PMR.B0 = 0;
					MPC::P22PFS.PSEL = sel;
					MPC::P21PFS.PSEL = sel;
					MPC::P20PFS.PSEL = sel;
					PORT2::PMR.B2 = enable;
					PORT2::PMR.B1 = enable;
					PORT2::PMR.B0 = enable;
				}
				break;
			case ORDER::SECOND:
				// P24/RSPCKA (65/100) (95/144)
				// P23/MOSIA  (66/100) (96/144)
				// P22/MISOA  (67/100) (97/144)
				{
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
			case ORDER::THIRD:
				// PB0/MOSIA  (35/100) (51/144)
				// PA5/MISOA  (36/100) (54/144)
				// PA4/RSPCKA (37/100) (55/144)
				{
					PORTB::PMR.B0 = 0;
					PORTA::PMR.B5 = 0;
					PORTA::PMR.B4 = 0;
					MPC::PB0PFS.PSEL = sel;
					MPC::PA5PFS.PSEL = sel;
					MPC::PA4PFS.PSEL = sel;
					PORTB::PMR.B0 = enable;
					PORTA::PMR.B5 = enable;
					PORTA::PMR.B4 = enable;
				}
				break;
			case ORDER::FOURTH:
				// PB3/RSPCKA (48/144)
				// PB0/MOSIA  (51/144)
				// PA5/MISOA  (54/144)
				{
					PORTD::PMR.B2 = 0;
					PORTD::PMR.B1 = 0;
					PORTD::PMR.B0 = 0;
					MPC::PD2PFS.PSEL = sel;
					MPC::PD1PFS.PSEL = sel;
					MPC::PD0PFS.PSEL = sel;
					PORTD::PMR.B2 = enable;
					PORTD::PMR.B1 = enable;
					PORTD::PMR.B0 = enable;
				}
				break;
			case ORDER::FIFTH:
				// PD2/MOSIA  (28/144) (28/144)
				// PD1/MISOA  (29/144) (29/144)
				// PD0/RSPCKA (30/144) (30/144)
				{
					PORTD::PMR.B2 = 0;
					PORTD::PMR.B1 = 0;
					PORTD::PMR.B0 = 0;
					MPC::PD2PFS.PSEL = sel;
					MPC::PD1PFS.PSEL = sel;
					MPC::PD0PFS.PSEL = sel;
					PORTD::PMR.B2 = enable;
					PORTD::PMR.B1 = enable;
					PORTD::PMR.B0 = enable;
				}
				break;
			default:
				return false;
			}
			return true;
		}


		static bool rspia0_(ORDER opt, bool enable)
		{
			uint8_t sel = enable ? 0b001101 : 0;
			switch(opt) {

			case ORDER::FIRST:
				// P22/MISOA  (67/100) ( 97/100)
				// P21/MOSIA  (68/100) (100/144)
				// P20/RSPCKA (69/100) (101/144)
				{
					PORT2::PMR.B2 = 0;
					PORT2::PMR.B1 = 0;
					PORT2::PMR.B0 = 0;
					MPC::P22PFS.PSEL = sel;
					MPC::P21PFS.PSEL = sel;
					MPC::P20PFS.PSEL = sel;
					PORT2::PMR.B2 = enable;
					PORT2::PMR.B1 = enable;
					PORT2::PMR.B0 = enable;
				}
				break;
			default:
				return false;
			}
			return true;
		}

#endif

		/// RIIC0 ポート候補（順番は、MPC の解説に準拠）
		static bool riic0_(ORDER opt, bool enable)
		{
			uint8_t sel = enable ? 0b00'1111 : 0;
			switch(opt) {
			case ORDER::FIRST:
				// PB1/SCL0
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = sel;
				PORTB::PMR.B1 = enable;
				// PB2/SDA0
				PORTB::PMR.B2 = 0;
				MPC::PB2PFS.PSEL = sel;
				PORTB::PMR.B2 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		/// RIIC0 ポート候補（順番は、MPC の解説に準拠）
		static bool ri3c0_(ORDER opt, bool enable)
		{
			uint8_t sel = enable ? 0b11'0010 : 0;
			switch(opt) {
			case ORDER::FIRST:
				// PB1/SCL0
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = sel;
				PORTB::PMR.B1 = enable;
				// PB2/SDA0
				PORTB::PMR.B2 = 0;
				MPC::PB2PFS.PSEL = sel;
				PORTB::PMR.B2 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		/// CANFD ポート候補（順番は、MPC の解説に準拠）
		static bool canfd0_(ORDER opt, bool enable)
		{
			uint8_t sel = enable ? 0b01'0000 : 0;
			switch(opt) {
			case ORDER::FIRST:
				// P22/CRX0
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;
				PORT2::PMR.B2 = enable;
				// P23/CTX0
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;
				PORT2::PMR.B3 = enable;
				break;
			case ORDER::SECOND:
				// P93/CRX0
				PORT9::PMR.B3 = 0;
				MPC::P93PFS.PSEL = sel;
				PORT9::PMR.B3 = enable;
				// P92/CTX0
				PORT9::PMR.B2 = 0;
				MPC::P92PFS.PSEL = sel;
				PORT9::PMR.B2 = enable;
				break;
			case ORDER::THIRD:
				// PA1/CRX0
				PORTA::PMR.B1 = 0;
				MPC::PA1PFS.PSEL = sel;
				PORTA::PMR.B1 = enable;
				// PA0/CTX0
				PORTA::PMR.B0 = 0;
				MPC::PA0PFS.PSEL = sel;
				PORTA::PMR.B0 = enable;
				break;
			case ORDER::FOURTH:
				// PB4/CRX0
				PORTB::PMR.B4 = 0;
				MPC::PB4PFS.PSEL = sel;
				PORTB::PMR.B4 = enable;
				// PB3/CTX0
				PORTB::PMR.B3 = 0;
				MPC::PB3PFS.PSEL = sel;
				PORTB::PMR.B3 = enable;
				break;
			case ORDER::FIFTH:
				// PB6/CRX0
				PORTB::PMR.B6 = 0;
				MPC::PB6PFS.PSEL = sel;
				PORTB::PMR.B6 = enable;
				// PB5/CTX0
				PORTB::PMR.B5 = 0;
				MPC::PB5PFS.PSEL = sel;
				PORTB::PMR.B5 = enable;
				break;
			case ORDER::SIXTH:
				// PE0/CRX0
				PORTE::PMR.B0 = 0;
				MPC::PE0PFS.PSEL = sel;
				PORTE::PMR.B0 = enable;
				// PD7/CTX0
				PORTD::PMR.B7 = 0;
				MPC::PD7PFS.PSEL = sel;
				PORTD::PMR.B7 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  周辺機器別ポート切り替え
			@param[in]	per	周辺機器タイプ
			@param[in]	ena	無効にする場合「false」
			@param[in]	odr	候補を選択する場合
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral per, bool ena = true, ORDER odr = ORDER::FIRST) noexcept
		{
			if(odr == ORDER::BYPASS) return false;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			switch(per) {
			case peripheral::SCI1:
				ret = sci1_(odr, ena);
				break;
			case peripheral::SCI5:
				ret = sci5_(odr, ena);
				break;
			case peripheral::SCI6:
				ret = sci6_(odr, ena);
				break;
#if 0
			case peripheral::RSCI8:
				ret = rsci8_(odr, ena);
				break;
			case peripheral::RSCI9:
				ret = rsci9_(odr, ena);
				break;
			case peripheral::RSCI11:
				ret = rsci11_(odr, ena);
				break;
			case peripheral::SCI12:
				ret = sci12_(odr, ena);
				break;

			case peripheral::RSPI0:
				ret = rspi0_(odr, ena);
				break;
			case peripheral::RSPIA0:
				ret = rspia0_(odr, ena);
				break;
#endif
			case peripheral::RIIC0:
				ret = riic0_(odr, ena);
				break;
			case peripheral::RI3C0:
				ret = ri3c0_(odr, ena);
				break;

			case peripheral::CANFD0:
				ret = canfd0_(odr, ena);
				break;

			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
