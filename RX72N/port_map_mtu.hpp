#pragma once
//=========================================================================//
/*!	@file
	@brief	RX72N グループ・ポート・マッピング (MTU3a) @n
			・MTU 型に従って、タイマー用ポートを設定 @n
			MTU0, MTU1, MTU2, MTU3, MTU4, MTU5, MTU6, MTU7, MTU8 @n
			RX651/RX65N とほぼ同じだが、オーダーが一部異なるので注意！ @n
			オーダーの順番は、ハードウェアーマニュアルに準拠してある。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX72N/peripheral.hpp"
#include "RX600/port.hpp"
#include "RX600/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_mtu : public port_map_order {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマー系・クロック・グループ @n
					※タイマーのクロック系は、MTU 共通なので、識別子としてグループを使う
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GROUP : uint8_t {
			AREA0,	///< エリア０
			AREA1,	///< エリア１
			AREA2,	///< エリア２
			AREA3,	///< エリア３
			AREA4,	///< エリア４
			AREA5,	///< 
			AREA6,	///< 
			AREA7,	///< 
			NONE,	///< 無効なグループ
		};

	private:

		static bool mtu0_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b000001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC0A
			// P34 ( 27/176) ( 25/144)
			// PB3 ( 98/176) ( 82/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B4 = 0;
					MPC::P34PFS.PSEL = sel;  // ok
					PORT3::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;  // ok
					PORTB::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC0B
			// P13 ( 52/176) ( 44/144)
			// P15 ( 50/176) ( 42/144)
			// PA1 (114/176) ( 96/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;  // ok
					PORT1::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;  // ok
					PORT1::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;  // ok
					PORTA::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC0C
			// P32 ( 29/176) ( 27/144)
			// PB1 (100/176) ( 84/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;  // ok
					PORT3::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;  // ok
					PORTB::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC0D
			// P33 ( 28/176) ( 26/144)
			// PA3 (110/176) ( 94/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;  // ok
					PORT3::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = sel;  // ok
					PORTA::PMR.B3 = ena;
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
			return ret;
		}


		static bool mtu1_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b000001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC1A
			// P20 ( 45/176) ( 37/144)
			// PE4 (131/176) (107/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = sel;  // ok
					PORT2::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = ena ? 0b000010 : 0;  // ok
					PORTE::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC1B
			// P21 ( 44/176) ( 36/144)
			// PB5 ( 96/176) ( 80/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;  // ok
					PORT2::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = ena ? 0b000010 : 0;  // ok
					PORTB::PMR.B5 = ena;
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
			return ret;
		}


		static bool mtu2_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b000001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC2A
			// P26 ( 37/176) ( 31/144)
			// PB5 ( 96/176) ( 80/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B6 = 0;
					MPC::P26PFS.PSEL = sel;  // ok
					PORT2::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = sel;  // ok
					PORTB::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC2B
			// P27 ( 36/176) ( 30/144)
			// PE5 (130/176) (106/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B7 = 0;
					MPC::P27PFS.PSEL = sel;  // ok
					PORT2::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = ena ? 0b000010 : 0;  // ok
					PORTE::PMR.B5 = ena;
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
			return ret;
		}


		static bool mtu3_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b000001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC3A
			// P14 ( 51/176) ( 43/144)
			// P17 ( 46/176) ( 38/144)
			// PC1 ( 89/176) ( 73/144)
			// PC7 ( 76/176) ( 60/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;  // ok
					PORT1::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;  // ok
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = sel;  // ok
					PORTC::PMR.B1 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;  // ok
					PORTC::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC3B
			// P17 ( 46/176) ( 28/144)
			// P22 ( 43/176) ( 35/144)
			// P80 ( 81/176) ( 65/144)
			// PB7 ( 94/176) ( 78/144)
			// PC5 ( 78/176) ( 62/144)
			// PE1 (134/176) (110/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = ena ? 0b000010 : 0;  // ok
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;  // ok
					PORT2::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORT8::PMR.B0 = 0;
					MPC::P80PFS.PSEL = sel;  // ok
					PORT8::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;  // ok
					PORTB::PMR.B7 = ena;
					break;
				case ORDER::FIFTH:
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;  // ok
					PORTC::PMR.B5 = ena;
					break;
				case ORDER::SIXTH:
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = ena ? 0b001000 : 0;  // ok
					PORTE::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC3C
			// P16 ( 48/176) ( 40/144)
			// P56 ( 64/176) ( 50/144)
			// PC0 ( 91/176) ( 75/144)
			// PC6 ( 77/176) ( 61/144)
			// PJ3 ( 13/176) ( 13/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;  // ok
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT5::PMR.B6 = 0;
					MPC::P56PFS.PSEL = sel;  // ok
					PORT5::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B0 = 0;
					MPC::PC0PFS.PSEL = sel;  // ok
					PORTC::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;  // ok
					PORTC::PMR.B6 = ena;
					break;
				case ORDER::FIFTH:
					PORTJ::PMR.B3 = 0;
					MPC::PJ3PFS.PSEL = sel;  // ok
					PORTJ::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC3D
			// P16 ( 48/176) ( 40/144)
			// P23 ( 42/176) ( 34/144)
			// P81 ( 80/176) ( 64/144)
			// PB6 ( 95/176) ( 79/144)
			// PC4 ( 82/176) ( 66/144)
			// PE0 (135/176) (111/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = ena ? 0b000010 : 0;  // ok
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;  // ok
					PORT2::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORT8::PMR.B1 = 0;
					MPC::P81PFS.PSEL = sel;  // ok
					PORT8::PMR.B1 = ena;
					break;
				case ORDER::FOURTH:
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;  // ok
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::FIFTH:
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;  // ok
					PORTC::PMR.B4 = ena;
					break;
				case ORDER::SIXTH:
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = ena ? 0b001000 : 0;  // ok
					PORTE::PMR.B0 = ena;
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
			return ret;
		}


		static bool mtu4_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b000001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC4A
			// P21 ( 44/176) ( 36/144)
			// P24 ( 40/176) ( 33/144)
			// P82 ( 79/176) ( 63/144)
			// PA0 (118/176) ( 97/144)
			// PB3 ( 98/176) ( 82/144)
			// PE2 (133/176) (109/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = ena ? 0b001000 : 0;  // ok
					PORT2::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;  // ok
					PORT2::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORT8::PMR.B2 = 0;
					MPC::P82PFS.PSEL = sel;  // ok
					PORT8::PMR.B2 = ena;
					break;
				case ORDER::FOURTH:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;  // ok
					PORTA::PMR.B0 = ena;
					break;
				case ORDER::FIFTH:
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = ena ? 0b000010 : 0;  // ok
					PORTB::PMR.B3 = ena;
					break;
				case ORDER::SIXTH:
					PORTE::PMR.B2 = 0;
					MPC::PE2PFS.PSEL = sel;  // ok
					PORTE::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC4B
			// P17 ( 46/176) ( 38/144)
			// P30 ( 33/176) ( 29/144)
			// P54 ( 66/176) ( 52/144)
			// PC2 ( 86/176) ( 70/144)
			// PD1 (156/176) (125/144)
			// PE3 (132/176) (108/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = ena ? 0b001000 : 0;  // ok
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = sel;  // ok
					PORT3::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
					PORT5::PMR.B4 = 0;
					MPC::P54PFS.PSEL = sel;  // ok
					PORT5::PMR.B4 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = sel;  // ok
					PORTC::PMR.B2 = ena;
					break;
				case ORDER::FIFTH:
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;  // ok
					PORTD::PMR.B1 = ena;
					break;
				case ORDER::SIXTH:
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = sel;  // ok
					PORTE::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC4C
			// P25 ( 38/176) ( 32/144)
			// P83 ( 74/176) ( 58/144)
			// P87 ( 47/176) ( 39/144)
			// PB1 (100/176) ( 84/144)
			// PE1 (134/176) (110/144)
			// PE5 (130/176) (106/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B5 = 0;
					MPC::P25PFS.PSEL = sel;  // ok
					PORT2::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B3 = 0;
					MPC::P83PFS.PSEL = sel;  // ok
					PORT8::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORT8::PMR.B7 = 0;
					MPC::P87PFS.PSEL = ena ? 0b000010 : 0;  // ok
					PORT8::PMR.B7 = ena;
					break;
				case ORDER::FOURTH:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = ena ? 0b000010 : 0;  // ok
					PORTB::PMR.B1 = ena;
					break;
				case ORDER::FIFTH:
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = sel;  // ok
					PORTE::PMR.B1 = ena;
					break;
				case ORDER::SIXTH:
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = sel;  // ok
					PORTE::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC4D
			// P31 ( 32/176) ( 28/144)
			// P55 ( 65/176) ( 51/144)
			// P86 ( 49/176) ( 41/144)
			// PC3 ( 83/176) ( 67/144)
			// PD2 (154/176) (124/144)
			// PE4 (131/176) (107/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B1 = 0;
					MPC::P31PFS.PSEL = sel;  // ok
					PORT3::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT5::PMR.B5 = 0;
					MPC::P55PFS.PSEL = sel;  // ok
					PORT5::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					PORT8::PMR.B6 = 0;
					MPC::P86PFS.PSEL = ena ? 0b000010 : 0;  // ok
					PORT8::PMR.B6 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B3 = 0;
					MPC::PC3PFS.PSEL = sel;  // ok
					PORTC::PMR.B3 = ena;
					break;
				case ORDER::FIFTH:
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;  // ok
					PORTD::PMR.B2 = ena;
					break;
				case ORDER::SIXTH:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = sel;  // ok
					PORTE::PMR.B4 = ena;
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
			return ret;
		}


		static bool mtu5_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b000001 : 0;
			switch(ch) {
			case CHANNEL::U:  // MTIC5U
			// P12 ( 53/176) (---/144)
			// PA4 (109/176) ( 92/144)
			// PD7 (143/176) (119/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B2 = 0;
					MPC::P12PFS.PSEL = sel;  // ok
					PORT1::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;  // ok
					PORTA::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;  // ok
					PORTD::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::V:  // MTIC5V
			// P11 ( 67/176) (---/144)
			// PA6 (107/176) ( 89/144)
			// PD6 (145/176) (120/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = sel;  // ok
					PORT1::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = sel;  // ok
					PORTA::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;  // ok
					PORTD::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::W:  // MTIC5W
			// P10 ( 68/176) (---/144)
			// PB0 (104/176) ( 65/144)
			// PD5 (147/176) (121/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B0 = 0;
					MPC::P10PFS.PSEL = sel;  // ok
					PORT1::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;  // ok
					PORTB::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
					PORTD::PMR.B5 = 0;
					MPC::PD5PFS.PSEL = sel;  // ok
					PORTD::PMR.B5 = ena;
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
			return ret;
		}


		static bool mtu6_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b000001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC6A
			// PE7 (125/176) (101/144)
			// PJ1 ( 59/176) (---/144)
				switch(odr) {
				case ORDER::FIRST:
					PORTE::PMR.B7 = 0;
					MPC::PE7PFS.PSEL = ena ? 0b001000 : 0;  // ok
					PORTE::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTJ::PMR.B1 = 0;
					MPC::PJ1PFS.PSEL = sel;  // ok
					PORTJ::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC6B
			// PA5 (108/176) ( 90/144)
			// PJ0 ( 60/176) (---/144)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = ena ? 0b001000 : 0;  // ok
					PORTA::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORTJ::PMR.B0 = 0;
					MPC::PJ0PFS.PSEL = sel;  // ok
					PORTJ::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC6C
			// P85 ( 61/176) (---/144)
			// PE6 (126/176) (102/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT8::PMR.B5 = 0;
					MPC::P85PFS.PSEL = sel;  // ok
					PORT8::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B6 = 0;
					MPC::PE6PFS.PSEL = ena ? 0b001000 : 0;  // ok
					PORTE::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC6D
			// P84 ( 62/176) (---/144)
			// PA0 (118/176) ( 97/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT8::PMR.B4 = 0;
					MPC::P84PFS.PSEL = sel;  // ok
					PORT8::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = ena ? 0b001000 : 0;  // ok
					PORTA::PMR.B0 = ena;
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
			return ret;
		}


		static bool mtu7_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b001000 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC7A
			// PA2 (112/176) ( 95/144)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = ena;  // ok
					PORTA::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC7B
			// PA1 (114/176) ( 96/144)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = ena;  // ok
					PORTA::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC7C
			// P67 (120/176) ( 98/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT6::PMR.B7 = 0;
					MPC::P67PFS.PSEL = ena;  // ok
					PORT6::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC7D
			// P66 (122/176) ( 99/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT6::PMR.B6 = 0;
					MPC::P66PFS.PSEL = ena;  // ok
					PORT6::PMR.B6 = ena;
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
			return ret;
		}


		static bool mtu8_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b001000 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC8A
			// PD6 (145/176) (120/144)
				switch(odr) {
				case ORDER::FIRST:
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;  // ok
					PORTD::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC8B
			// PD4 (148/176) (122/144)
				switch(odr) {
				case ORDER::FIRST:
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;  // ok
					PORTD::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC8C
			// PD5 (147/176) (121/144)
				switch(odr) {
				case ORDER::FIRST:
					PORTD::PMR.B5 = 0;
					MPC::PD5PFS.PSEL = sel;  // ok
					PORTD::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC8D
			// PD3 (150/176) (123/144)
				switch(odr) {
				case ORDER::FIRST:
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = sel;  // ok
					PORTD::PMR.B3 = ena;
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
			return ret;
		}

	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマー系、チャネル別ポート切り替え
			@param[in]	per	周辺機器タイプ
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合場合「false」
			@param[in]	odr	候補を選択する場合
			@param[in]	neg	反転入出力の場合「true」（サポートしない）
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(peripheral per, CHANNEL ch, bool ena = true, ORDER odr = ORDER::FIRST, bool neg = false) noexcept
		{
			if(odr == ORDER::BYPASS) return true;
			if(neg) return false;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = true;
			switch(per) {
			case peripheral::MTU0:
				ret = mtu0_(ch, ena, odr);
				break;
			case peripheral::MTU1:
				ret = mtu1_(ch, ena, odr);
				break;
			case peripheral::MTU2:
				ret = mtu2_(ch, ena, odr);
				break;
			case peripheral::MTU3:
				ret = mtu3_(ch, ena, odr);
				break;
			case peripheral::MTU4:
				ret = mtu4_(ch, ena, odr);
				break;
			case peripheral::MTU5:
				ret = mtu5_(ch, ena, odr);
				break;
			case peripheral::MTU6:
				ret = mtu6_(ch, ena, odr);
				break;
			case peripheral::MTU7:
				ret = mtu7_(ch, ena, odr);
				break;
			case peripheral::MTU8:
				ret = mtu8_(ch, ena, odr);
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
			@brief  タイマー系、クロックポート切り替え
			@param[in]	grp	チャネル・グループ
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合場合「false」
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn_clock(GROUP grp, CHANNEL ch, bool ena = true) noexcept
		{
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			uint8_t sel = ena ? 0b000010 : 0;
			bool ret = true;
			switch(grp) {
			/// P15 ( 50)  MTIOC0B / MTCLKB
			/// PA1 (114)  MTIOC0B / MTCLKC / MTIOC7B
			/// PA3 (110)  MTIOC0D / MTCLKD
			case GROUP::AREA0:
				switch(ch) {
				case CHANNEL::CLK_B:
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;
					PORT1::PMR.B5 = ena;
					break;
				case CHANNEL::CLK_C:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;
					PORTA::PMR.B1 = ena;
					break;
				case CHANNEL::CLK_D:
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = sel;
					PORTA::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// P14 ( 51)  MTIOC3A / MTCLKA
			/// PC7 ( 76)  MTIOC3A / MTCLKB
			/// P22 ( 43)  MTIOC3B / MTCLKC
			/// PC5 ( 78)  MTIOC3B / MTCLKD
			case GROUP::AREA1:
				switch(ch) {
				case CHANNEL::CLK_A:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;
					PORT1::PMR.B4 = ena;
					break;
				case CHANNEL::CLK_B:
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;
					PORTC::PMR.B7 = ena;
					break;
				case CHANNEL::CLK_C:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;
					PORT2::PMR.B2 = ena;
					break;
				case CHANNEL::CLK_D:
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;
					PORTC::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// PC6 ( 77)  MTIOC3C / MTCLKA
			/// P23 ( 42)  MTIOC3D / MTCLKD
			/// PC4 ( 82)  MTIOC3D / MTCLKC
			case GROUP::AREA2:
				switch(ch) {
				case CHANNEL::CLK_A:
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;
					PORTC::PMR.B6 = ena;
					break;
				case CHANNEL::CLK_C:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;
					PORT2::PMR.B3 = ena;
					break;
				case CHANNEL::CLK_D:
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;
					PORTC::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// P24 ( 40)  MTIOC4A / MTCLKA
			/// P25 ( 38)  MTIOC4C / MTCLKB
			case GROUP::AREA3:
				switch(ch) {
				case CHANNEL::CLK_A:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;
					PORT2::PMR.B4 = ena;
					break;
				case CHANNEL::CLK_B:
					PORT2::PMR.B5 = 0;
					MPC::P25PFS.PSEL = sel;
					PORT2::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// PA4 (109)  MTIC5U / MTCLKA
			/// PA6 (107)  MTIC5V / MTCLKB
			case GROUP::AREA4:
				switch(ch) {
				case CHANNEL::CLK_A:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B4 = ena;
					break;
				case CHANNEL::CLK_B:
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = sel;
					PORTA::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// PD5 (147)  MTIC5W / MTIOC8C / MTCLKA
			case GROUP::AREA5:
				switch(ch) {
				case CHANNEL::CLK_A:
					PORTD::PMR.B5 = 0;
					MPC::PD5PFS.PSEL = sel;
					PORTD::PMR.B5 = ena;
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
	};
}

