#pragma once
//=========================================================================//
/*!	@file
	@brief	RX26T グループ・ポート・マッピング (GPTW0 - GPTW7)  @n
			（クロック関係は実装中・・・）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023, 2025 Kunihito Hiramatsu @n
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
		@brief  GPTW ポート・マッピング
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_gptw : public port_map_order {

		static bool gptw0_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			case CHANNEL::A:  // GTIOC0A:
				// P71 # ( 56/100)
				// PD2 # ( 23/100)
				// PD7 # ( 18/100)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT7::PMR.B1 = 0;
					MPC::P71PFS.PSEL = sel;  // OK
					PORT7::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;  // OK
					PORTD::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;  // OK
					PORTD::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC0B:
				// P74 # ( 53/100)
				// PD1 # ( 24/100)
				// PD6 # ( 19/100)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT7::PMR.B4 = 0;
					MPC::P74PFS.PSEL = sel;  // OK
					PORT7::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;  // OK
					PORTD::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;  // OK
					PORTD::PMR.B6 = ena;
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


		static bool gptw1_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			case CHANNEL::A:  // GTIOC1A:
				// P72 # ( 55/100)
				// PD0 # ( 25/100)
				// PD5 # ( 20/100)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT7::PMR.B2 = 0;
					MPC::P72PFS.PSEL = sel;  // OK
					PORT7::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b0'10111 : 0b01'0101) : 0;
					PORTD::PMR.B0 = 0;
					MPC::PD0PFS.PSEL = sel;  // OK
					PORTD::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B5 = 0;
					MPC::PD5PFS.PSEL = sel;  // OK
					PORTD::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC1B:
				// P75 # ( 52/100)
				// PB7 # ( 26/100)
				// PD4 # ( 21/100)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT7::PMR.B5 = 0;
					MPC::P75PFS.PSEL = sel;  // OK
					PORT7::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;  // OK
					PORTB::PMR.B7 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;  // OK
					PORTD::PMR.B4 = ena;
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


		static bool gptw2_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			case CHANNEL::A:  // GTIOC2A:
				// P73 # ( 54/100)
				// PB6 # ( 27/100)
				// PD3 # ( 22/100)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT7::PMR.B3 = 0;
					MPC::P73PFS.PSEL = sel;  // OK
					PORT7::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;  // OK
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = sel;  // OK
					PORTD::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC2B:
				// P76 # ( 51/100)
				// PB5 # ( 28/100)
				// PD2 # ( 23/100)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;  // OK
					PORT7::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = sel;  // OK
					PORTB::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;  // OK
					PORTD::PMR.B2 = ena;
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


		static bool gptw3_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			case CHANNEL::A:  // GTIOC3A:
				// P10 # (100/100)
				// P32 # ( 59/100)
				// PB6 # ( 27/100)
				// PD1 # ( 24/100)
				// PD7 # ( 18/100)
				// PE5 # (  1/100)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT1::PMR.B0 = 0;
					MPC::P10PFS.PSEL = sel;  // OK
					PORT1::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;  // OK
					PORT3::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;  // OK
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;  // OK
					PORTD::PMR.B1 = ena;
					break;
				case ORDER::FIFTH:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;  // OK
					PORTD::PMR.B7 = ena;
					break;
				case ORDER::SIXTH:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = sel;  // OK
					PORTE::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC3B:
				// P11 # ( 99/100)
				// P33 # ( 58/100)
				// PB5 # ( 28/100)
				// PD0 # ( 25/100)
				// PD6 # ( 19/100)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = sel;  // OK
					PORT1::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;  // OK
					PORT3::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = sel;  // OK
					PORTB::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B0 = 0;
					MPC::PD0PFS.PSEL = sel;  // OK
					PORTD::PMR.B0 = ena;
					break;
				case ORDER::FIFTH:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;  // OK
					PORTD::PMR.B6 = ena;
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


		static bool gptw4_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			case CHANNEL::A:  // GTIOC4A:
				// P71 # ( 56/100)
				// P95 # ( 45/100)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORT7::PMR.B1 = 0;
					MPC::P71PFS.PSEL = sel;  // OK
					PORT7::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT9::PMR.B5 = 0;
					MPC::P95PFS.PSEL = sel;  // OK
					PORT9::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC4B:
				// P74 # ( 53/100)
				// P92 # ( 48/100)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORT7::PMR.B4 = 0;
					MPC::P74PFS.PSEL = sel;  // OK
					PORT7::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT9::PMR.B2 = 0;
					MPC::P92PFS.PSEL = sel;  // OK
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


		static bool gptw5_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			case CHANNEL::A:  /// GTIOC5A:
				// P72 # ( 55/100)
				// P94 # ( 46/100)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORT7::PMR.B2 = 0;
					MPC::P72PFS.PSEL = sel;  // OK
					PORT7::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT9::PMR.B4 = 0;
					MPC::P94PFS.PSEL = sel;  // OK
					PORT9::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC5B:
				// P75 # ( 52/100)
				// P91 # ( 49/100)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORT7::PMR.B5 = 0;
					MPC::P75PFS.PSEL = sel;  // OK
					PORT7::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT9::PMR.B1 = 0;
					MPC::P91PFS.PSEL = sel;  // OK
					PORT9::PMR.B1 = ena;
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


		static bool gptw6_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			case CHANNEL::A:  // GTIOC6A:
				// P73 # ( 54/100)
				// P93 # ( 47/100)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORT7::PMR.B3 = 0;
					MPC::P73PFS.PSEL = sel;  // OK
					PORT7::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT9::PMR.B3 = 0;
					MPC::P93PFS.PSEL = sel;  // OK
					PORT9::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC6B:
				// P76 # ( 51/100)
				// P90 # ( 50/100)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;  // OK
					PORT7::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT9::PMR.B0 = 0;
					MPC::P90PFS.PSEL = sel;  // OK
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


		static bool gptw7_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC7A:
				// P32 # ( 59/100)
				// P95 # ( 45/100)
				// PB2 # ( 33/100)
				// PD5   ( 20/100)
				switch(order) {
				case ORDER::FIRST:
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;  // OK
					PORT3::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B5 = 0;
					MPC::P95PFS.PSEL = sel;  // OK
					PORT9::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B2 = 0;
					MPC::PB2PFS.PSEL = sel;  // OK
					PORTB::PMR.B2 = ena;
					break;
				case ORDER::FOURTH:
					if(neg) {
						ret = false;
					} else {
						PORTD::PMR.B5 = 0;
						MPC::PD5PFS.PSEL = ena ? 0b01'0111 : 0;  // OK
						PORTD::PMR.B5 = ena;
					}
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC7B:
				// P33 # ( 58/100)
				// P92 # ( 48/100)
				// PB1 # ( 34/100)
				// PD3   ( 22/100)
				switch(order) {
				case ORDER::FIRST:
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;  // OK
					PORT3::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B2 = 0;
					MPC::P92PFS.PSEL = sel;  // OK
					PORT9::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;  // OK
					PORTB::PMR.B1 = ena;
					break;
				case ORDER::FOURTH:
					if(neg) {
						ret = false;
					} else {
						PORTD::PMR.B3 = 0;
						MPC::PD3PFS.PSEL = ena ? 0b01'0111 : 0;  // OK
						PORTD::PMR.B3 = ena;
					}
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
			@brief  GPTW[0-7]、チャネル別ポート切り替え
			@param[in]	per		周辺機器タイプ
			@param[in]	ch		チャネル
			@param[in]	ena		無効にする場合「false」
			@param[in]	order	候補を選択する場合
			@param[in]	neg		反転入出力の場合「true」
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(peripheral per, CHANNEL ch, bool ena = true, ORDER order = ORDER::FIRST, bool neg = false) noexcept
		{
			if(order == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			switch(per) {
			case peripheral::GPTW0:
				ret = gptw0_(ch, ena, neg, order);
				break;
			case peripheral::GPTW1:
				ret = gptw1_(ch, ena, neg, order);
				break;
			case peripheral::GPTW2:
				ret = gptw2_(ch, ena, neg, order);
				break;
			case peripheral::GPTW3:
				ret = gptw3_(ch, ena, neg, order);
				break;
			case peripheral::GPTW4:
				ret = gptw4_(ch, ena, neg, order);
				break;
			case peripheral::GPTW5:
				ret = gptw5_(ch, ena, neg, order);
				break;
			case peripheral::GPTW6:
				ret = gptw6_(ch, ena, neg, order);
				break;
			case peripheral::GPTW7:
				ret = gptw7_(ch, ena, neg, order);
				break;
			default:
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GPTW クロック入出力切り替え
			@param[in]	clk	クロック型
			@param[in]	ena	無効にする場合場合「false」
			@param[in]	odr	候補を選択する場合
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn_clock(CHANNEL clk, bool ena = true, ORDER odr = ORDER::FIRST) noexcept
		{
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = true;
			switch(clk) {
			case CHANNEL::TRGA:  // GTETRGA
				// P01
				// P11
				// P70
				// P96
				// PB4
				// PD5
				// PE3
				// PE4
				switch(odr) {
				case ORDER::FIRST:
					PORT0::PMR.B1 = 0;
					MPC::P01PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
					PORT0::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
					PORT1::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					PORT7::PMR.B0 = 0;
					MPC::P70PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
					PORT7::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORT9::PMR.B6 = 0;
					MPC::P96PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
					PORT9::PMR.B6 = ena;
					break;
				case ORDER::FIFTH:
					PORTB::PMR.B4 = 0;
					MPC::PB4PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
					PORTB::PMR.B4 = ena;
					break;
				case ORDER::SIXTH:
					PORTD::PMR.B5 = 0;
					MPC::PD5PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
					PORTD::PMR.B5 = ena;
					break;
				case ORDER::SEVENTH:
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
					PORTE::PMR.B3 = ena;
					break;
				case ORDER::EIGHTH:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
					PORTE::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TRGB:  // GTETRGB
				// P01
				// P10
				// P70
				// P96
				// PB4
				// PD4
				// PE3
				// PE4
				// PE5
				switch(odr) {
				case ORDER::FIRST:
					PORT0::PMR.B1 = 0;
					MPC::P01PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
					PORT0::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT1::PMR.B0 = 0;
					MPC::P10PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
					PORT1::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
					PORT7::PMR.B0 = 0;
					MPC::P70PFS.PSEL = ena ? 0b01'0101 : 0;  // ok 
					PORT7::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORT9::PMR.B6 = 0;
					MPC::P96PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
					PORT9::PMR.B6 = ena;
					break;
				case ORDER::FIFTH:
					PORTB::PMR.B4 = 0;
					MPC::PB4PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
					PORTB::PMR.B4 = ena;
					break;
				case ORDER::SIXTH:
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
					PORTD::PMR.B4 = ena;
					break;
				case ORDER::SEVENTH:
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
					PORTE::PMR.B3 = ena;
					break;
				case ORDER::EIGHTH:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
					PORTE::PMR.B4 = ena;
					break;
				case ORDER::NINTH:
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
					PORTE::PMR.B5 = ena;
					break;

				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TRGC:  // GTETRGC
				// P01
				// P11
				// P70
				// P96
				// PB4
				// PD3
				// PE3
				// PE4
				switch(odr) {
				case ORDER::FIRST:
					PORT0::PMR.B1 = 0;
					MPC::P01PFS.PSEL = ena ? 0b01'0110 : 0;  // ok
					PORT0::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = ena ? 0b01'0111 : 0;  // ok
					PORT1::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					PORT7::PMR.B0 = 0;
					MPC::P70PFS.PSEL = ena ? 0b01'0110 : 0;  // ok
					PORT7::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORT9::PMR.B6 = 0;
					MPC::P96PFS.PSEL = ena ? 0b01'0110 : 0;  // ok
					PORT9::PMR.B6 = ena;
					break;
				case ORDER::FIFTH:
					PORTB::PMR.B4 = 0;
					MPC::PB4PFS.PSEL = ena ? 0b01'0110 : 0;  // ok
					PORTB::PMR.B4 = ena;
					break;
				case ORDER::SIXTH:
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
					PORTD::PMR.B3 = ena;
					break;
				case ORDER::SEVENTH:
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = ena ? 0b01'0110 : 0;  // ok
					PORTE::PMR.B3 = ena;
					break;
				case ORDER::EIGHTH:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = ena ? 0b01'0110 : 0;  // ok
					PORTE::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TRGD:  // GTETRGD
				// P01
				// P10
				// P70
				// P96
				// PB4
				// PE3
				// PE4
				// PE5
				switch(odr) {
				case ORDER::FIRST:
					PORT0::PMR.B1 = 0;
					MPC::P01PFS.PSEL = ena ? 0b01'0111 : 0;  // ok
					PORT0::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT1::PMR.B0 = 0;
					MPC::P10PFS.PSEL = ena ? 0b01'0111 : 0;  // ok
					PORT1::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
					PORT7::PMR.B0 = 0;
					MPC::P70PFS.PSEL = ena ? 0b01'0111 : 0;  // ok
					PORT7::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORT9::PMR.B6 = 0;
					MPC::P96PFS.PSEL = ena ? 0b01'0111 : 0;  // ok
					PORT9::PMR.B6 = ena;
					break;
				case ORDER::FIFTH:
					PORTB::PMR.B4 = 0;
					MPC::PB4PFS.PSEL = ena ? 0b01'0111 : 0;  // ok
					PORTB::PMR.B4 = ena;
					break;
				case ORDER::SIXTH:
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = ena ? 0b01'0111 : 0;  // ok
					PORTE::PMR.B3 = ena;
					break;
				case ORDER::SEVENTH:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = ena ? 0b01'0111 : 0;  // ok
					PORTE::PMR.B4 = ena;
					break;
				case ORDER::EIGHTH:
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = ena ? 0b01'0110 : 0;  // ok
					PORTE::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::DSM0:  // GTADSM0
				// P94
				// PA3
				// PB2
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B4 = 0;
					MPC::P94PFS.PSEL = ena ? 0b01'0100 : 0;
					PORT9::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = ena ? 0b01'0100 : 0;
					PORTA::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B2 = 0;
					MPC::PB2PFS.PSEL = ena ? 0b01'0100 : 0;
					PORTB::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::DSM1:  // GTADSM1
				// PA2
				// PB1
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = ena ? 0b01'0100 : 0;
					PORTA::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = ena ? 0b01'0100 : 0;
					PORTB::PMR.B1 = ena;
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
