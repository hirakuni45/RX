#pragma once
//=====================================================================//
/*!	@file
	@brief	RX72T グループ・ポート・マッピング @n
			・ポートの選択は「候補」に従うポリシーを採用している。@n
			・単独で指定する場合や、グループで指定する場合などがある。@n
			・独自に指定する場合、「BYPASS」を選択する事が出来る。@n
			・RX72T の場合、メインストリームは100ピンと考え、100ピンを基準にしている。@n
			・「候補」の順番は、ハードウェアーマニュアル MPC の解説に準拠している。@n
			※上記ルールに従っていない場合もあるので注意が必要（工事中）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX600/port.hpp"
#include "RX66T/mpc.hpp"
#include "RX72T/peripheral.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map : public port_map_order {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  MTUx（マルチ・ファンクション・タイマ） チャネル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class channel : uint8_t {
			A,		///< MTUx A (MTIOCxA)
			B,		///< MTUx B (MTIOCxB)
			C,		///< MTUx C (MTIOCxC)
			D,		///< MTUx D (MTIOCxD)

			U,		///< MTU5 U (MTIC5U) P24
			V,		///< MTU5 V (MTIC5V) P23
			W,		///< MTU5 W (MTIC5W) P22
			U2,		///< MTU5 U (MTIC5U) P82
			V2,		///< MTU5 V (MTIC5V) P81
			W2,		///< MTU5 W (MTIC5W) P80

			CLK_AB,	///< MTCLKA, MTCLKB 1ST: P33/P32, 2ND: P21/P20 
			CLK_CD,	///< MTCLKC, MTCLKD 1ST: P31/P30, 2ND: P11/P10, 3RD: PE4/PE3
		};

	private:

		static bool sci1_(ORDER opt, bool enable, bool clock)
		{
			uint8_t sel = enable ? 0b001010 : 0;
			switch(opt) {
			case ORDER::FIRST:
			// PD5/RXD1 (20/100) (25/144)
			// PD4/SCK1 (21/100) (26/144)
			// PD3/TXD1 (22/100) (27/144)
				if(clock) {
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;
					PORTD::PMR.B4 = enable;
				}
				PORTD::PMR.B3 = 0;
				PORTD::PMR.B5 = 0;
				MPC::PD3PFS.PSEL = sel;
				MPC::PD5PFS.PSEL = sel;
				PORTD::PMR.B3 = enable;
				PORTD::PMR.B5 = enable;
				break;
			case ORDER::SECOND:
			// P25/SCK1 (94/144)
			// PC4/TXD1 (98/144)
			// PC3/RXD1 (99/144)
				if(clock) {
					PORT2::PMR.B5 = 0;
					MPC::P25PFS.PSEL = sel;
					PORT2::PMR.B5 = enable;
				}
				PORTC::PMR.B4 = 0;
				PORTC::PMR.B3 = 0;
				MPC::PC4PFS.PSEL = sel;
				MPC::PC3PFS.PSEL = sel;
				PORTC::PMR.B4 = enable;
				PORTC::PMR.B3 = enable;
				break;
			default:
				return false;
			}
			return true;
		}


		static bool sci5_(ORDER opt, bool enable, bool clock)
		{
			uint8_t sel = enable ? 0b001010 : 0;
			switch(opt) {
			case ORDER::FIRST:
			// PE0/RXD5 (17/100) (22/144)
			// PD7/TXD5 (18/100) (23/144)
			// PD2/SCK5 (23/100) (28/144)
				if(clock) {
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;
					PORTD::PMR.B2 = enable;
				}
				PORTE::PMR.B0 = 0;
				PORTD::PMR.B7 = 0;
				MPC::PE0PFS.PSEL = sel;
				MPC::PD7PFS.PSEL = sel;
				PORTE::PMR.B0 = enable;
				PORTD::PMR.B7 = enable;
				break;
			case ORDER::SECOND:
			// PD2/SCK5 (23/100) (28/144)
			// PB6/RXD5 (27/100) (40/144)
			// PB5/TXD5 (28/100) (41/144)
				if(clock) {
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;
					PORTD::PMR.B2 = enable;
				}
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


		static bool sci6_(ORDER opt, bool enable, bool clock)
		{
			uint8_t sel = enable ? 0b001010 : 0;
			switch(opt) {
			case ORDER::FIRST:
			// PB3/SCK6 (32/100) (48/144)
			// PB2/TXD6 (33/100) (49/144)
			// PB1/RXD6 (34/100) (50/144)
				if(clock) {
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;
					PORTB::PMR.B3 = enable;
				}
				PORTB::PMR.B2 = 0;
				PORTB::PMR.B1 = 0;
				MPC::PB2PFS.PSEL = sel;
				MPC::PB1PFS.PSEL = sel;
				PORTB::PMR.B2 = enable;
				PORTB::PMR.B1 = enable;
				break;
			case ORDER::SECOND:
			// PB0/TXD6 (35/100) (51/144)
			// PA5/RXD6 (36/100) (54/144)
			// PA4/SCK6 (37/100) (55/144)
				if(clock) {
					PORTA::PMR.B4 = 0;
					MPC::PA3PFS.PSEL = sel;
					PORTA::PMR.B4 = enable;
				}
				PORTB::PMR.B0 = 0;
				PORTA::PMR.B5 = 0;
				MPC::PB0PFS.PSEL = sel;
				MPC::PA5PFS.PSEL = sel;
				PORTB::PMR.B0 = enable;
				PORTA::PMR.B5 = enable;
				break;
			case ORDER::THIRD:
			// P82/SCK6 (96/100) (137/144)
			// P81/TXD6 (97/100) (138/144)
			// P80/RXD6 (98/100) (139/144)
				if(clock) {
					PORT8::PMR.B2 = 0;
					MPC::P82PFS.PSEL = sel;
					PORT8::PMR.B2 = enable;
				}
				PORT8::PMR.B1 = 0;
				PORT8::PMR.B0 = 0;
				MPC::P81PFS.PSEL = sel;
				MPC::P80PFS.PSEL = sel;
				PORT8::PMR.B1 = enable;
				PORT8::PMR.B0 = enable;
				break;
			default:
				return false;
			}
			return true;
		}


		static bool sci8_(ORDER opt, bool enable, bool clock)
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


		static bool sci9_(ORDER opt, bool enable, bool clock)
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


		static bool sci11_(ORDER opt, bool enable, bool clock)
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


		static bool sci12_(ORDER opt, bool enable, bool clock)
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


		/// RIIC0 ポート候補（順番は、MPC の解説に準拠）
		static bool riic0_(ORDER opt, bool enable)
		{
			uint8_t sel = enable ? 0b001111 : 0;
			switch(opt) {
			case ORDER::FIRST:
				// PB1/SCL0 (50/144) (34/100)
				// PB2/SDA0 (49/144) (33/100)
				PORTB::PMR.B1 = 0;
				PORTB::PMR.B2 = 0;
				MPC::PB1PFS.PSEL = sel;
				MPC::PB2PFS.PSEL = sel;
				PORTB::PMR.B1 = enable;
				PORTB::PMR.B2 = enable;
				break;
			default:
				return false;
			}
			return true;
		}


		/// CAN0 ポート候補（順番は、MPC の解説に準拠）
		static bool can0_(ORDER opt, bool enable)
		{
			uint8_t sel = enable ? 0b010000 : 0;
			switch(opt) {
			case ORDER::FIRST:
				// P22/CRX0 (97/144) (67/100)
				// P23/CTX0 (96/144) (66/100)
				PORT2::PMR.B2 = 0;
				PORT2::PMR.B3 = 0;
				MPC::P22PFS.PSEL = sel;
				MPC::P23PFS.PSEL = sel;
				PORT2::PMR.B2 = enable;
				PORT2::PMR.B3 = enable;
				break;
			case ORDER::SECOND:
				// PA1/CRX0 (58/144) (40/100)
				// PA0/CTX0 (59/144) (41/100)
				PORTA::PMR.B1 = 0;
				PORTA::PMR.B0 = 0;
				MPC::PA1PFS.PSEL = sel;
				MPC::PA0PFS.PSEL = sel;
				PORTA::PMR.B1 = enable;
				PORTA::PMR.B0 = enable;
				break;
			case ORDER::THIRD:
				// PA7/CRX0 (52/144) (-/100)
				// PA6/CTX0 (53/144) (-/100)
				PORTA::PMR.B7 = 0;
				PORTA::PMR.B6 = 0;
				MPC::PA7PFS.PSEL = sel;
				MPC::PA6PFS.PSEL = sel;
				PORTA::PMR.B7 = enable;
				PORTA::PMR.B6 = enable;
				break;
			case ORDER::FOURTH:
				// PB6/CRX0 (40/144) (27/100)
				// PB5/CTX0 (41/144) (28/100)
				PORTB::PMR.B6 = 0;
				PORTB::PMR.B5 = 0;
				MPC::PB6PFS.PSEL = sel;
				MPC::PB5PFS.PSEL = sel;
				PORTB::PMR.B6 = enable;
				PORTB::PMR.B5 = enable;
				break;
			case ORDER::FIFTH:
				// PC6/CRX0 (62/144) (-/100)
				// PC5/CTX0 (63/144) (-/100)
				PORTC::PMR.B6 = 0;
				PORTC::PMR.B5 = 0;
				MPC::PC6PFS.PSEL = sel;
				MPC::PC5PFS.PSEL = sel;
				PORTC::PMR.B6 = enable;
				PORTC::PMR.B5 = enable;
				break;
			case ORDER::SIXTH:
				// PE0/CRX0 (22/144) (17/100)
				// PD7/CTX0 (23/144) (18/100)
				PORTE::PMR.B0 = 0;
				PORTD::PMR.B7 = 0;
				MPC::PE0PFS.PSEL = sel;
				MPC::PD7PFS.PSEL = sel;
				PORTE::PMR.B0 = enable;
				PORTD::PMR.B7 = enable;
				break;
			case ORDER::SEVENTH:
				// PF3/CRX0 (31/144) (-/100)
				// PF2/CTX0 (32/144) (-/100)
				PORTF::PMR.B3 = 0;
				PORTF::PMR.B2 = 0;
				MPC::PF3PFS.PSEL = sel;
				MPC::PF3PFS.PSEL = sel;
				PORTF::PMR.B3 = enable;
				PORTF::PMR.B2 = enable;
				break;
			default:
				return false;
			}
			return true;
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
				switch(odr) {
				// PC0 o
				// PD2 o
				case ORDER::FIRST:
					PORTC::PMR.B0 = 0;
					MPC::PC0PFS.PSEL = ena ? 0b010001 : 0;
					PORTC::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = ena ? 0b010001 : 0;
					PORTD::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::EXICEN:
				// PA0 o
				// PC1 o
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = ena ? 0b010001 : 0;
					PORTA::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = ena ? 0b010001 : 0;
					PORTC::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::VBUSEN:
				// PA0 o
				// PC1 o
				// PB5 o
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = ena ? 0b010010 : 0;
					PORTA::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = ena ? 0b010010 : 0;
					PORTC::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = ena ? 0b010001 : 0;
					PORTB::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::OVRCURA:
				// PA1 o
				// PB6 o
				// PC2 o
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = ena ? 0b010010 : 0;
					PORTA::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = ena ? 0b010001 : 0;
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = ena ? 0b010010 : 0;
					PORTC::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::OVRCURB:
				// P34 o
				// PB4 o
				// PB7 o
				// PE0 o
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B4 = 0;
					MPC::P34PFS.PSEL = ena ? 0b010001 : 0;
					PORT3::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B4 = 0;
					MPC::PB4PFS.PSEL = ena ? 0b010001 : 0;
					PORTB::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = ena ? 0b010001 : 0;
					PORTB::PMR.B7 = ena;
					break;
				case ORDER::FOURTH:
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = ena ? 0b010001 : 0;
					PORTE::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::ID:
				// PA1 o
				// PC2 o
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = ena ? 0b010001 : 0;
					PORTA::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = ena ? 0b010001 : 0;
					PORTC::PMR.B2 = ena;
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
			bool clock = false;
			switch(per) {
			case peripheral::SCI1C:
				clock = true;
			case peripheral::SCI1:
				ret = sci1_(odr, ena, clock);
				break;
			case peripheral::SCI5C:
				clock = true;
			case peripheral::SCI5:
				ret = sci5_(odr, ena, clock);
				break;
			case peripheral::SCI6C:
				clock = true;
			case peripheral::SCI6:
				ret = sci6_(odr, ena, clock);
				break;
			case peripheral::SCI8C:
				clock = true;
			case peripheral::SCI8:
				ret = sci8_(odr, ena, clock);
				break;
			case peripheral::SCI9C:
				clock = true;
			case peripheral::SCI9:
				ret = sci9_(odr, ena, clock);
				break;
			case peripheral::SCI11C:
				clock = true;
			case peripheral::SCI11:
				ret = sci11_(odr, ena, clock);
				break;
			case peripheral::SCI12:
				ret = sci12_(odr, ena, clock);
				break;

			case peripheral::RSPI0:
				ret = rspi0_(odr, ena);
				break;
			case peripheral::RIIC0:
				ret = riic0_(odr, ena);
				break;
			case peripheral::CAN0:
				ret = can0_(odr, ena);
				break;

			case peripheral::USB0:
				if(odr == ORDER::FIRST) {  // RX72N hira_kuni_board
					ret = turn_usb(USB_PORT::VBUSEN,  ena, ORDER::THIRD);  // PB5
					if(ret) {
						ret = turn_usb(USB_PORT::OVRCURB, ena, ORDER::SECOND);  // PB6
					}
				}
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  MTU3 関係、チャネル別ポート切り替え
			@param[in]	per	周辺機器タイプ
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合場合「false」
			@param[in]	odr	候補を選択する場合
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral per, channel ch, bool ena = true, ORDER odr = ORDER::FIRST)
			noexcept
		{
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = true;
			uint8_t sel = 0;
			switch(per) {
			case peripheral::MTU0:
				sel = ena ? 0b00001 : 0;
				switch(ch) {
				case channel::A:
					MPC::PB3PFS.PSEL = sel;  // MTIOC0A (32/100)
					PORTB::PMR.B3 = ena;
					break;
				case channel::B:
					MPC::PB2PFS.PSEL = sel;  // MTIOC0B (33/100)
					PORTB::PMR.B2 = ena;
					break;
				case channel::C:
					MPC::PB1PFS.PSEL = sel;  // MTIOC0C (34/100)
					PORTB::PMR.B1 = ena;
					break;
				case channel::D:
					MPC::PB0PFS.PSEL = sel;  // MTIOC0D (35/100)
					PORTB::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU1:
				switch(ch) {
				case channel::A:
					sel = ena ? 0b00001 : 0;
					MPC::PA5PFS.PSEL = sel;  // MTIOC1A (36/100)
					PORTA::PMR.B5 = ena;
					break;
				case channel::B:
					sel = ena ? 0b00001 : 0;
					MPC::PA4PFS.PSEL = sel;  // MTIOC1B (37/100)
					PORTA::PMR.B4 = ena;
					break;
				case channel::CLK_AB:
					sel = ena ? 0b00010 : 0;
					if(odr == ORDER::FIRST) {
						MPC::P33PFS.PSEL = sel;
						PORT3::PMR.B3 = ena;
						MPC::P32PFS.PSEL = sel;
						PORT3::PMR.B2 = ena;
					} else if(odr == ORDER::SECOND) {
						MPC::P21PFS.PSEL = sel;
						PORT2::PMR.B1 = ena;
						MPC::P20PFS.PSEL = sel;
						PORT2::PMR.B0 = ena;
					} else {
						ret = false;
					}
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU2:
				switch(ch) {
				case channel::A:					
					MPC::PA3PFS.PSEL = sel;  // MTIOC2A (38/100)
					PORTA::PMR.B3 = ena;
					break;
				case channel::B:
					MPC::PA2PFS.PSEL = sel;  // MTIOC2B (39/100)
					PORTA::PMR.B2 = ena;
					break;
				case channel::CLK_AB:
					sel = ena ? 0b00010 : 0;
					if(odr == ORDER::FIRST) {
						MPC::P33PFS.PSEL = sel;  // 
						PORT3::PMR.B3 = ena;
						MPC::P32PFS.PSEL = sel;
						PORT3::PMR.B2 = ena;
					} else if(odr == ORDER::SECOND) {
						MPC::P21PFS.PSEL = sel;
						PORT2::PMR.B1 = ena;
						MPC::P20PFS.PSEL = sel;
						PORT2::PMR.B0 = ena;
					} else {
						ret = false;
					}
					break;
				case channel::CLK_CD:
					sel = ena ? 0b00010 : 0;
					if(odr == ORDER::FIRST) {
						MPC::P31PFS.PSEL = sel;
						PORT3::PMR.B1 = ena;
						MPC::P30PFS.PSEL = sel;
						PORT3::PMR.B0 = ena;
					} else if(odr == ORDER::SECOND) {
						MPC::P11PFS.PSEL = sel;
						PORT1::PMR.B1 = ena;
						MPC::P10PFS.PSEL = sel;
						PORT1::PMR.B0 = ena;
					} else if(odr == ORDER::THIRD) {
						MPC::PE4PFS.PSEL = sel;
						PORTE::PMR.B4 = ena;
						MPC::PE3PFS.PSEL = sel;
						PORTE::PMR.B3 = ena;
					} else {
						ret = false;
					}
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU3:
				switch(ch) {
				case channel::A:					
					MPC::P33PFS.PSEL = sel;  // MTIOC3A (58/100)
					PORT3::PMR.B3 = ena;
					break;
				case channel::B:
					MPC::P71PFS.PSEL = sel;  // MTIOC3B (56/100)
					PORT7::PMR.B1 = ena;
					break;
				case channel::C:
					MPC::P32PFS.PSEL = sel;  // MTIOC3C (59/100)
					PORT3::PMR.B2 = ena;
					break;
				case channel::D:
					MPC::P74PFS.PSEL = sel;  // MTIOC3D (53/100)
					PORT7::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU4:
				switch(ch) {
				case channel::A:					
					MPC::P72PFS.PSEL = sel;  // MTIOC4A (55/100)
					PORT7::PMR.B2 = ena;
					break;
				case channel::B:
					MPC::P73PFS.PSEL = sel;  // MTIOC4B (54/100)
					PORT7::PMR.B3 = ena;
					break;
				case channel::C:
					MPC::P75PFS.PSEL = sel;  // MTIOC4C (52/100)
					PORT7::PMR.B5 = ena;
					break;
				case channel::D:
					MPC::P76PFS.PSEL = sel;  // MTIOC4D (51/100)
					PORT7::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU5:
				switch(ch) {
				case channel::U:
					MPC::P24PFS.PSEL = sel;  // MTIOC5U (64/100)
					PORT2::PMR.B4 = ena;
					break;
				case channel::V:
					MPC::P23PFS.PSEL = sel;  // MTIOC5V (65/100)
					PORT2::PMR.B3 = ena;
					break;
				case channel::W:
					MPC::P22PFS.PSEL = sel;  // MTIOC5W (66/100)
					PORT2::PMR.B2 = ena;
					break;
				case channel::U2:
					MPC::P82PFS.PSEL = sel;  // MTIOC5U (96/100)
					PORT8::PMR.B2 = ena;
					break;
				case channel::V2:
					MPC::P81PFS.PSEL = sel;  // MTIOC5V (97/100)
					PORT8::PMR.B1 = ena;
					break;
				case channel::W2:
					MPC::P80PFS.PSEL = sel;  // MTIOC5W (98/100)
					PORT8::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU6:
				switch(ch) {
				case channel::A:
					MPC::PA1PFS.PSEL = sel;  // MTIOC6A (40/100)
					PORTA::PMR.B1 = ena;
					break;
				case channel::B:
					MPC::P95PFS.PSEL = sel;  // MTIOC6B (45/100)
					PORT9::PMR.B5 = ena;
					break;
				case channel::C:
					MPC::PA0PFS.PSEL = sel;  // MTIOC6C (41/100)
					PORTA::PMR.B0 = ena;
					break;
				case channel::D:
					MPC::P92PFS.PSEL = sel;  // MTIOC6D (48/100)
					PORT9::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU7:
				switch(ch) {
				case channel::A:
					MPC::P94PFS.PSEL = sel;  // MTIOC7A (46/100)
					PORT9::PMR.B4 = ena;
					break;
				case channel::B:
					MPC::P93PFS.PSEL = sel;  // MTIOC7B (47/100)
					PORT9::PMR.B3 = ena;
					break;
				case channel::C:
					MPC::P91PFS.PSEL = sel;  // MTIOC7C (49/100)
					PORT9::PMR.B1 = ena;
					break;
				case channel::D:
					MPC::P90PFS.PSEL = sel;  // MTIOC7D (50/100)
					PORT9::PMR.B0 = ena;
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

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
