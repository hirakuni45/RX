#pragma once
//=====================================================================//
/*!	@file
	@brief	RX72T グループ・ポート・マッピング (GPTW0 - GPTW9) 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX72T/peripheral.hpp"
#include "RX66T/port.hpp"
#include "RX66T/mpc.hpp"
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
			/// GTIOC0A:
			/// P12[0] ( 3/144) (--/100)
			/// P71[0] (78/144) (56/100)
			/// PD2[1] (28/144) (23/100)
			/// PD7[0] (23/144) (18/100)
			/// PG1[1] (81/144) (--/100)
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT1::PMR.B2 = 0;
					MPC::P12PFS.PSEL = sel;
					PORT1::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT7::PMR.B1 = 0;
					MPC::P71PFS.PSEL = sel;
					PORT7::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;
					PORTD::PMR.B2 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;
					PORTD::PMR.B7 = ena;
					break;
				case ORDER::FIFTH:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORTG::PMR.B1 = 0;
					MPC::PG1PFS.PSEL = sel;
					PORTG::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// GTIOC0B:
			/// P15[0] (144/144) (--/100)
			/// P74[0] ( 75/144) (53/100)
			/// PD1[1] ( 29/144) (--/100) (24/100)
			/// PD6[0] ( 24/144) (19/100)
			/// PG2[1] ( 81/144) (--/100)
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;
					PORT1::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT7::PMR.B4 = 0;
					MPC::P74PFS.PSEL = sel;
					PORT7::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;
					PORTD::PMR.B1 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;
					PORTD::PMR.B6 = ena;
					break;
				case ORDER::FIFTH:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORTG::PMR.B2 = 0;
					MPC::PG2PFS.PSEL = sel;
					PORTG::PMR.B2 = ena;
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
			/// GTIOC1A:
			/// P13[0] ( 2/144) (--/100)
			/// P72[0] (77/144) (55/100)
			/// PD0[1] (30/144) (--/100) (25/100) 
			/// PD5[0] (25/144) (20/100)
			/// PK2[1] (83/144) (--/100)
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;
					PORT1::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT7::PMR.B2 = 0;
					MPC::P72PFS.PSEL = sel;
					PORT7::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORTD::PMR.B0 = 0;
					MPC::PD0PFS.PSEL = sel;
					PORTD::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORTD::PMR.B5 = 0;
					MPC::PD5PFS.PSEL = sel;
					PORTD::PMR.B5 = ena;
					break;
				case ORDER::FIFTH:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORTK::PMR.B2 = 0;
					MPC::PK2PFS.PSEL = sel;
					PORTK::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// GTIOC1B:
			/// P16[0] (143/144) (111/112)
			/// P75[0] ( 74/144)
			/// PB7[0] ( 39/144)
			/// PD4[0] ( 26/144)
			/// PG0[1] ( 82/144)
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT7::PMR.B5 = 0;
					MPC::P75PFS.PSEL = sel;
					PORT7::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;
					PORTB::PMR.B7 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;
					PORTD::PMR.B4 = ena;
					break;
				case ORDER::FIFTH:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORTG::PMR.B0 = 0;
					MPC::PG0PFS.PSEL = sel;
					PORTG::PMR.B0 = ena;
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
			/// GTIOC2A:
			/// P14[0] ( 1/144)
			/// P73[0] (76/144)
			/// PB6[0] (40/144)
			/// PD3[0] (27/144)
			/// PK0[1] (85/144)
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;
					PORT1::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT7::PMR.B3 = 0;
					MPC::P73PFS.PSEL = sel;
					PORT7::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = sel;
					PORTD::PMR.B3 = ena;
					break;
				case ORDER::FIFTH:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORTK::PMR.B0 = 0;
					MPC::PK0PFS.PSEL = sel;
					PORTK::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// GTIOC2B:
			/// P17[0] (142/144)
			/// P76[0] ( 73/144)
			/// PB5[0] ( 41/144)
			/// PD2[0] ( 28/144)
			/// PK1[1] ( 84/144)
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;
					PORT7::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = sel;
					PORTB::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;
					PORTD::PMR.B2 = ena;
					break;
				case ORDER::FIFTH:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORTK::PMR.B1 = 0;
					MPC::PK1PFS.PSEL = sel;
					PORTK::PMR.B1 = ena;
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
			/// GTIOC3A:
			/// P32[0] (87/144)
			/// PD1[0] (29/144)
			/// PD7[1] (23/144)
			/// PE5[0] ( 5/144)
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;
					PORT3::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;
					PORTD::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;
					PORTD::PMR.B7 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = sel;
					PORTE::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// GTIOC3B:
			/// P11[0] (140/144)
			/// P33[0] ( 86/144)
			/// PD0[0] ( 30/144)
			/// PD6[1] ( 24/144)
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = sel;
					PORT1::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;
					PORT3::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORTD::PMR.B0 = 0;
					MPC::PD0PFS.PSEL = sel;
					PORTD::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;
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
			/// GTIOC4A:
			/// P71[1] (78/144)
			/// P95[0] (67/144)
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORT7::PMR.B1 = 0;
					MPC::P71PFS.PSEL = sel;
					PORT7::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT9::PMR.B5 = 0;
					MPC::P95PFS.PSEL = sel;
					PORT9::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// GTIOC4B:
			/// P74[1] (75/144)
			/// P92[0] (70/144)
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORT7::PMR.B4 = 0;
					MPC::P74PFS.PSEL = sel;
					PORT7::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT9::PMR.B2 = 0;
					MPC::P92PFS.PSEL = sel;
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
			/// GTIOC5A:
			/// P72[1] (77/144)
			/// P94[0] (68/144)
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORT7::PMR.B2 = 0;
					MPC::P72PFS.PSEL = sel;
					PORT7::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT9::PMR.B4 = 0;
					MPC::P94PFS.PSEL = sel;
					PORT9::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// GTIOC5B:
			/// P75[1] (74/144)
			/// P91[0] (71/144)
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORT7::PMR.B5 = 0;
					MPC::P75PFS.PSEL = sel;
					PORT7::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT9::PMR.B1 = 0;
					MPC::P91PFS.PSEL = sel;
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
			/// GTIOC6A:
			/// P73[1] (76/144)
			/// P93[0] (69/144)
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORT7::PMR.B3 = 0;
					MPC::P73PFS.PSEL = sel;
					PORT7::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT9::PMR.B3 = 0;
					MPC::P93PFS.PSEL = sel;
					PORT9::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// GTIOC6B:
			/// P76[1] (73/144)
			/// P90[0] (72/144)
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;
					PORT7::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT9::PMR.B0 = 0;
					MPC::P90PFS.PSEL = sel;
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
			uint8_t sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
			switch(ch) {
			/// GTIOC7A:
			/// P12[1] ( 3/144)
			/// P95[1] (67/144)
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B2 = 0;
					MPC::P12PFS.PSEL = sel;
					PORT1::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B5 = 0;
					MPC::P95PFS.PSEL = sel;
					PORT9::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// GTIOC7B:
			/// P15[1]
			/// P92[1]
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;
					PORT1::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B2 = 0;
					MPC::P92PFS.PSEL = sel;
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


		static bool gptw8_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
			switch(ch) {
			/// GTIOC8A:
			/// P13[1] ( 2/144)
			/// P94[1] (68/144)
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;
					PORT1::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B4 = 0;
					MPC::P94PFS.PSEL = sel;
					PORT9::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// GTIOC8B:
			/// P16[1] (143/144)
			/// P91[1] ( 71/144)
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B1 = 0;
					MPC::P91PFS.PSEL = sel;
					PORT9::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			default:
				ret = false;
			}
			return ret;
		}


		static bool gptw9_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
			switch(ch) {
			/// GTIOC9A:
			/// P14[1] ( 1/144)
			/// P93[1] (69/144)
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;
					PORT1::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B3 = 0;
					MPC::P93PFS.PSEL = sel;
					PORT9::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// GTIOC9B:
			/// P17[1] (142/144)
			/// P90[1] ( 72/144)
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B0 = 0;
					MPC::P90PFS.PSEL = sel;
					PORT9::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			default:
				ret = false;
			}
			return ret;
		}


		static bool gptw_(CHANNEL ch, bool ena, ORDER order) noexcept
		{
			bool ret = true;
#if 0
			switch(ch) {
			case CHANNEL::RA:
				switch(order) {
				case ORDER::FIRST:
					break;
				case ORDER::SECOND:
					break;
				case ORDER::THIRD:
					break;
				case ORDER::FOURTH:
					break;
				case ORDER::FIFTH:
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::RB:

				break;
			case CHANNEL::RC:

				break;
			case CHANNEL::RD:

				break;
			default:
				ret = false;
				break;
			}
#endif
			return ret;
		}

	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GPTW[0-9]、チャネル別ポート切り替え
			@param[in]	per	周辺機器タイプ型
			@param[in]	ch	チャネル型
			@param[in]	ena	無効にする場合「false」
			@param[in]	order	候補を選択する場合
			@param[in]	neg	反転入出力の場合「true」
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(peripheral per, CHANNEL ch, bool ena = true, ORDER order = ORDER::FIRST, bool neg = false) noexcept
		{
			if(order == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
#if 0
			if(ch == CHANNEL::RA || ch == CHANNEL::RB || ch == CHANNEL::RC || ch == CHANNEL::RD) {
				switch(per) {
				case peripheral::GPTW0:
				case peripheral::GPTW1:
				case peripheral::GPTW2:
				case peripheral::GPTW3:
				case peripheral::GPTW4:
				case peripheral::GPTW5:
				case peripheral::GPTW6:
				case peripheral::GPTW7:
				case peripheral::GPTW8:
				case peripheral::GPTW9:
					ret = gptw_(ch, ena, order);
					break;
				default:
					break;
				}
			} else {
#endif
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
				case peripheral::GPTW8:
					ret = gptw8_(ch, ena, neg, order);
					break;
				case peripheral::GPTW9:
					ret = gptw9_(ch, ena, neg, order);
					break;
				default:
					break;
				}
//			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
