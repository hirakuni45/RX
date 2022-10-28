#pragma once
//=====================================================================//
/*!	@file
	@brief	RX66T/RX72T グループ・ポート・マッピング (MTU) @n
			・MTU 型に従って、タイマー用ポートを設定 @n
			MTU0, MTU1, MTU2, MTU3, MTU4, MTU5, MTU6, MTU7, MTU8, MTU9
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX72T/peripheral.hpp"
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
			MTU0,	///< MTU0 系グループ
			MTU1,	///< MTU1 系グループ
			MTU2,	///< MTU2 系グループ
			MTU3,	///< MTU3 系グループ
			MTU4,	///< MTU4 系グループ
			MTU5,	///< MTU5 系グループ
			MTU6,	///< MTU6 系グループ
			MTU7,	///< MTU7 系グループ
			NONE,	///< 無効なグループ
		};

	private:
		static bool mtu0_(CHANNEL ch, bool ena, bool neg, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b000011 : 0b000001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC0A[#]
			// P31 ( 61/100), ( 89/144)  
			// PB3 ( 32/100), ( 48/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B1 = 0;
					MPC::P31PFS.PSEL = sel;  // ok
					PORT3::PMR.B1 = ena;
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
			case CHANNEL::B:  // MTIOC0B[#]
			// P30 ( 63/100), ( 91/144)
			// PB2 ( 33/100), ( 49/144)
			// PC0 (---/100), ( 47/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = sel;  // ok
					PORT3::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B2 = 0;
					MPC::PB2PFS.PSEL = sel;  // ok
					PORTB::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B0 = 0;
					MPC::PC0PFS.PSEL = sel;
					PORTC::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC0C[#]
			// P27 ( 64/100), ( 92/144)
			// PB1 ( 34/100), ( 50/144)
			// PC1 (---/100), ( 46/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B7 = 0;
					MPC::P27PFS.PSEL = ena ? (neg ? 0b000100 : 0b000010) : 0;  // ok
					PORT2::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;  // ok
					PORTB::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = sel;  // ok
					PORTC::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC0D[#]
			// PB0 ( 35/100), ( 51/144)
			// PC2 (---/100), ( 45/144)
				switch(odr) {
				case ORDER::FIRST:
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;  // ok
					PORTB::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = sel;  // ok
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
			return ret;
		}


		static bool mtu1_(CHANNEL ch, bool ena, bool neg, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b000011 : 0b000001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC1A[#]
			// P27 ( 64/100), ( 92/144)
			// PA5 ( 36/100), ( 54/144)
			// PC6 (---/100), ( 62/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B7 = 0;
					MPC::P27PFS.PSEL = sel;  // ok
					PORT2::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;  // ok
					PORTA::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;  // ok
					PORTC::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC1B[#]
			// PA4 ( 37/100), ( 55/144)
			// PC5 (---/100), ( 63/144)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;  // ok
					PORTA::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;  // ok
					PORTC::PMR.B5 = ena;
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


		static bool mtu2_(CHANNEL ch, bool ena, bool neg, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b000011 : 0b000001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC2A[#]
			// P35 (---/100), ( 60/144)
			// PA3 ( 38/100), ( 56/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B5 = 0;
					MPC::P35PFS.PSEL = sel;  // ok
					PORT3::PMR.B5 = ena;
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
			case CHANNEL::B:  // MTIOC2B[#]
			// P34 (---/100), ( 61/144) 
			// PA2 ( 39/100), ( 57/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B4 = 0;
					MPC::P34PFS.PSEL = sel;  // ok
					PORT3::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = sel;  // ok
					PORTA::PMR.B2 = ena;
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


		static bool mtu3_(CHANNEL ch, bool ena, bool neg, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b000011 : 0b000001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC3A[#]
			// P11 ( 99/100), (140/144)
			// P33 ( 58/100), ( 86/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = sel;  // ok
					PORT1::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;  // ok
					PORT3::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC3B[#]
			// P12 (---/100), (  3/144)
			// P71 ( 56/100), ( 78/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B2 = 0;
					MPC::P12PFS.PSEL = sel;  // ok
					PORT1::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B1 = 0;
					MPC::P71PFS.PSEL = sel;  // ok
					PORT7::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC3C[#]
			// P32 ( 59/100), ( 87/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;  // ok
					PORT3::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC3D[#]
			// P15 (---/100), (144/144)
			// P74 ( 53/100), ( 75/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;  // ok
					PORT1::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B4 = 0;
					MPC::P74PFS.PSEL = sel;  // ok
					PORT7::PMR.B4 = ena;
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


		static bool mtu4_(CHANNEL ch, bool ena, bool neg, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b000011 : 0b000001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC4A[#]
			// P13 (---/100), (  2/144)
			// P72 ( 55/100), ( 77/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;  // ok
					PORT1::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B2 = 0;
					MPC::P72PFS.PSEL = sel;  // ok
					PORT7::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC4B[#]
			// P14 (---/100), (  1/144)
			// P73 ( 54/100), ( 76/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;  // ok
					PORT1::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B3 = 0;
					MPC::P73PFS.PSEL = sel;  // ok
					PORT7::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC4C[#]
			// P16 (---/100), (143/144)
			// P75 ( 52/100), ( 74/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;  // ok
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B5 = 0;
					MPC::P75PFS.PSEL = sel;  // ok
					PORT7::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC4D[#]
			// P17 (---/100), (142/144)
			// P76 ( 51/100), ( 73/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;  // ok
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;  // ok
					PORT7::PMR.B6 = ena;
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


		static bool mtu5_(CHANNEL ch, bool ena, bool neg, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b000011 : 0b000001) : 0;
			switch(ch) {
			case CHANNEL::U:  // MTIC5U[#]
			// P24 ( 65/100), ( 95/144)
			// P82 ( 96/100), (137/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;  // ok
					PORT2::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B2 = 0;
					MPC::P82PFS.PSEL = sel;  // ok
					PORT8::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::V:  // MTIC5V[#]
			// P23 ( 66/100), ( 96/144)
			// P81 ( 97/100), (138/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;  // ok
					PORT2::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B1 = 0;
					MPC::P81PFS.PSEL = sel;  // ok
					PORT8::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::W:  // MTIC5W[#]
			// P22 ( 67/100), ( 97/144)
			// P80 ( 98/100), (139/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;  // ok
					PORT2::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B0 = 0;
					MPC::P80PFS.PSEL = sel;  // ok
					PORT8::PMR.B0 = ena;
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


		static bool mtu6_(CHANNEL ch, bool ena, bool neg, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b000011 : 0b000001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC6A[#]
			// PA1 ( 40/100), ( 58/144)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;  // ok
					PORTA::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC6B[#]
			// P95 ( 45/100), ( 67/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B5 = 0;
					MPC::P95PFS.PSEL = sel;  // ok
					PORT9::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC6C[#]
			// PA0 ( 41/100), ( 59/144)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;  // ok
					PORTA::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC6D[#]
			// P92 ( 48/100), ( 70/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B2 = 0;
					MPC::P92PFS.PSEL = sel;  // ok
					PORT9::PMR.B2 = ena;
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


		static bool mtu7_(CHANNEL ch, bool ena, bool neg, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b000011 : 0b000001) : 0;
			switch(ch) {
			case CHANNEL::A:
			// P94 ( 46/100), ( 68/144)
				switch(odr) {  // MTIOC7A[#]
				case ORDER::FIRST:
					PORT9::PMR.B4 = 0;
					MPC::P94PFS.PSEL = sel;  // ok
					PORT9::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC7B[#]
			// P93 ( 47/100), ( 69/144)  
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B3 = 0;
					MPC::P93PFS.PSEL = sel;  // ok
					PORT9::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC7C[#]
			// P91 ( 49/100), ( 71/144)  
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B1 = 0;
					MPC::P91PFS.PSEL = sel;  // ok
					PORT9::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC7D[#]
			// P90 ( 50/100), ( 72/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B0 = 0;
					MPC::P90PFS.PSEL = sel;  // ok
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
			return ret;
		}


		static bool mtu9_(CHANNEL ch, bool ena, bool neg, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b000011 : 0b000001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC9A[#]
			// P00 (  4/100), (  9/144)
			// P21 ( 68/100), (100/144)
			// P26 (---/100), ( 93/144)
			// P35 (---/100), ( 60/144)
			// PD7 ( 18/100), ( 23/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT0::PMR.B0 = 0;
					MPC::P00PFS.PSEL = sel;  // ok
					PORT0::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;  // ok
					PORT2::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					PORT2::PMR.B6 = 0;
					MPC::P26PFS.PSEL = sel;  // ok
					PORT2::PMR.B6 = ena;
					break;
				case ORDER::FOURTH:
					PORT3::PMR.B5 = 0;
					MPC::P35PFS.PSEL = ena ? (neg ? 0b000100 : 0b000010) : 0;  // ok
					PORT3::PMR.B5 = ena;
					break;
				case ORDER::FIFTH:
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;  // ok
					PORTD::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC9B(#)
			// P22 ( 67/100), ( 97/144) #:NG
			// P10 (100/100), (141/144)
			// P34 (---/100), ( 61/144)
			// PC4 (---/100), ( 98/144)
			// PE0 ( 17/100), ( 22/144)
				switch(odr) {
				case ORDER::FIRST:
					if(neg) {
						ret = false;
						break;
					}
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = ena ? 0b001000 : 0;  // ok
					PORT2::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORT1::PMR.B0 = 0;
					MPC::P10PFS.PSEL = sel;  // ok
					PORT1::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
					PORT3::PMR.B4 = 0;
					MPC::P34PFS.PSEL = ena ? (neg ? 0b000100 : 0b000010) : 0;  // ok
					PORT3::PMR.B4 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;  // ok
					PORTC::PMR.B4 = ena;
					break;
				case ORDER::FIFTH:
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = sel;  // ok
					PORTE::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC9C[#]
			// P01 (  7/100), ( 12/144)
			// P20 ( 69/100), (101/144)
			// P25 (---/100), ( 94/144)
			// PC6 (---/100), ( 62/144)
			// PD6 ( 19/100), ( 24/144)
				switch(odr) {
				case ORDER::FIRST:
					PORT0::PMR.B1 = 0;
					MPC::P01PFS.PSEL = sel;  // ok
					PORT0::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = sel;  // ok
					PORT2::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
					PORT2::PMR.B5 = 0;
					MPC::P25PFS.PSEL = sel;  // ok
					PORT2::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = ena ? (neg ? 0b000100 : 0b000010) : 0;
					PORTC::PMR.B6 = ena;
					break;
				case ORDER::FIFTH:
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;  // ok
					PORTD::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC9D[#]
			// P11 ( 99/100), (140/144) #:NG
			// PC3 (---/100), ( 99/144)
			// PC5 (---/100), ( 63/144)
			// PE1 ( 16/100), ( 21/144)
			// PE5 (  1/100), (  5/144)
				switch(odr) {
				case ORDER::FIRST:
					if(neg) {
						ret = false;
						break;
					}
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = ena ? 0b001000 : 0;  // ok
					PORT1::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B3 = 0;
					MPC::PC3PFS.PSEL = sel;  // ok
					PORTC::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = ena ? (neg ? 0b000100 : 0b000010) : 0;  // 
					PORTC::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = sel;  // ok
					PORTE::PMR.B1 = ena;
					break;
				case ORDER::FIFTH:
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = sel;  // ok
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

	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマー系、チャネル別ポート切り替え
			@param[in]	per	周辺機器タイプ
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合「false」
			@param[in]	odr	候補選択
			@param[in]	neg	反転入出力の場合「true」
			@param[in]	inp	入力として利用する場合「true」（無視される）
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(peripheral per, CHANNEL ch, bool ena = true, ORDER odr = ORDER::FIRST, bool neg = false, bool inp = false) noexcept
		{
			if(odr == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = true;
			switch(per) {
			case peripheral::MTU0:
				ret = mtu0_(ch, ena, neg, odr);
				break;
			case peripheral::MTU1:
				ret = mtu1_(ch, ena, neg, odr);
				break;
			case peripheral::MTU2:
				ret = mtu2_(ch, ena, neg, odr);
				break;
			case peripheral::MTU3:
				ret = mtu3_(ch, ena, neg, odr);
				break;
			case peripheral::MTU4:
				ret = mtu4_(ch, ena, neg, odr);
				break;
			case peripheral::MTU5:
				ret = mtu5_(ch, ena, neg, odr);
				break;
			case peripheral::MTU6:
				ret = mtu6_(ch, ena, neg, odr);
				break;
			case peripheral::MTU7:
				ret = mtu7_(ch, ena, neg, odr);
				break;
			case peripheral::MTU9:
				ret = mtu9_(ch, ena, neg, odr);
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
			bool ret = true;

			return ret;
		}
	};
}

