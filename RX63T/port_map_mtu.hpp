#pragma once
//=========================================================================//
/*!	@file
	@brief	RX63T グループ・ポート・マッピング (MTU3) @n
			・MTU 型に従って、タイマー用ポートを設定 @n
			MTU0, MTU1, MTU2, MTU3, MTU4, MTU5, MTU6, MTU7
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX63T/peripheral.hpp"
#include "RX63T/port.hpp"
#include "RX63T/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_mtu : public port_map_order {

		static bool mtu0_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC0A
			// P31 (/100)
			// PB3 (/100)
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
			case CHANNEL::B:  // MTIOC0B
			// P30 (---/100)
			// PB2 (---/100)
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
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC0C
			// PB1 (---/100)
				switch(odr) {
				case ORDER::FIRST:
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
			// PB0 (/100)
				switch(odr) {
				case ORDER::FIRST:
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;  // ok
					PORTB::PMR.B0 = ena;
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
			uint8_t sel = ena ? 0b0'0001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC1A
			// PA5 (/100)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;  // ok
					PORTA::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC1B
			// PA4 (/100)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;  // ok
					PORTA::PMR.B4 = ena;
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
			uint8_t sel = ena ? 0b0'0001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC2A
			// PA3 (/100)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = sel;  // ok
					PORTA::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC2B
			// PA2 (/100)
				switch(odr) {
				case ORDER::FIRST:
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


		static bool mtu3_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC3A
			// P33 (/100)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;  // ok
					PORT3::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC3B
			// P71 (/100)
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B1 = 0;
					MPC::P71PFS.PSEL = sel;  // ok
					PORT7::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC3C
			// P32 (/100)
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
			case CHANNEL::D:  // MTIOC3D
			// P74 (/100)
				switch(odr) {
				case ORDER::FIRST:
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


		static bool mtu4_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC4A
			// P72 (/100)
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B2 = 0;
					MPC::P72PFS.PSEL = sel;  // ok
					PORT7::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC4B
			// P73 (/100)
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B3 = 0;
					MPC::P73PFS.PSEL = sel;  // ok
					PORT7::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC4C
			// P75 (/100)
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B5 = 0;
					MPC::P75PFS.PSEL = sel;  // ok
					PORT7::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC4D
			// P76 (/100)
				switch(odr) {
				case ORDER::FIRST:
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


		static bool mtu5_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0001 : 0;
			switch(ch) {
			case CHANNEL::U:  // MTIOC5U
			// P24 (/100)
			// P82 (/100)
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
			case CHANNEL::V:  // MTIOC5V
			// P23 (/100)
			// P81 (/100)
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
			case CHANNEL::W:  // MTIOC5W
			// P22 (/100)
			// P80 (/100)
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


		static bool mtu6_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC6A
			// P33
			// PA1 (/100)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;
					PORT3::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;  // ok
					PORTA::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC6B
			// P71
			// P95 (/100)
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B1 = 0;
					MPC::P71PFS.PSEL = sel;
					PORT7::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B5 = 0;
					MPC::P95PFS.PSEL = sel;  // ok
					PORT9::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC6C
			// P32
			// PA0 (/100)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;
					PORT3::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;  // ok
					PORTA::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC6D
			// P74
			// P92 (/100)
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B4 = 0;
					MPC::P74PFS.PSEL = sel;
					PORT7::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
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


		static bool mtu7_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC7A
			// P72
			// P94 (/100)
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B2 = 0;
					MPC::P72PFS.PSEL = sel;
					PORT7::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B4 = 0;
					MPC::P94PFS.PSEL = sel;  // ok
					PORT9::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC7B
			// P73
			// P93 (/100)
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B3 = 0;
					MPC::P73PFS.PSEL = sel;  // ok
					PORT7::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B3 = 0;
					MPC::P93PFS.PSEL = sel;  // ok
					PORT9::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC7C
			// P75
			// P91 (/100)
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B5 = 0;
					MPC::P75PFS.PSEL = sel;  // ok
					PORT7::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B1 = 0;
					MPC::P91PFS.PSEL = sel;  // ok
					PORT9::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC7D
			// P76
			// P90 (/100)
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;
					PORT7::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
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


		static bool clk_a_(ORDER odr, bool ena) noexcept
		{
			// P21 (/100)
			// P22
			// P33 (/100)
			// PB3
			uint8_t sel = ena ? 0b00'0010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORT2::PMR.B1 = 0;
				MPC::P21PFS.PSEL = sel;  // ok
				PORT2::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;
				PORT2::PMR.B2 = ena;
				break;
			case ORDER::THIRD:
				PORT3::PMR.B3 = 0;
				MPC::P33PFS.PSEL = sel;  // ok
				PORT3::PMR.B3 = ena;
				break;
			case ORDER::FOURTH:
				PORTB::PMR.B3 = 0;
				MPC::PB3PFS.PSEL = sel;
				PORTB::PMR.B3 = ena;
				break;
			default:
				return false;
				break;
			}
			return true;
		}


		static bool clk_b_(ORDER odr, bool ena) noexcept
		{
			// P20 (/100)
			// P23
			// P32 (/100)
			// PB2
			uint8_t sel = ena ? 0b00'0010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORT2::PMR.B0 = 0;
				MPC::P20PFS.PSEL = sel;  // ok
				PORT2::PMR.B0 = ena;
				break;
			case ORDER::SECOND:
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;
				PORT2::PMR.B3 = ena;
				break;
			case ORDER::THIRD:
				PORT3::PMR.B2 = 0;
				MPC::P32PFS.PSEL = sel;  // ok
				PORT3::PMR.B2 = ena;
				break;
			case ORDER::FOURTH:
				PORTB::PMR.B2 = 0;
				MPC::PB2PFS.PSEL = sel;
				PORTB::PMR.B2 = ena;
				break;
			default:
				return false;
				break;
			}
			return true;
		}


		static bool clk_c_(ORDER odr, bool ena) noexcept
		{
			// P11 (/100)
			// P24
			// P31 (/100)
			// PE4 (/100)
			uint8_t sel = ena ? 0b00'0010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B1 = 0;
				MPC::P11PFS.PSEL = sel;  // ok
				PORT1::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = sel;
				PORT2::PMR.B4 = ena;
				break;
			case ORDER::THIRD:
				PORT3::PMR.B1 = 0;
				MPC::P31PFS.PSEL = sel;  // ok
				PORT3::PMR.B1 = ena;
				break;
			case ORDER::FOURTH:
				PORTE::PMR.B4 = 0;
				MPC::PE4PFS.PSEL = sel;  // ok
				PORTE::PMR.B4 = ena;
				break;
			default:
				return false;
				break;
			}
			return true;
		}


		static bool clk_d_(ORDER odr, bool ena) noexcept
		{
			// P10 (/100)
			// P30 (/100)
			// PE3 (/100)
			uint8_t sel = ena ? 0b00'0010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B0 = 0;
				MPC::P10PFS.PSEL = sel;  // ok
				PORT1::PMR.B0 = ena;
				break;
			case ORDER::SECOND:
				PORT3::PMR.B0 = 0;
				MPC::P30PFS.PSEL = sel;  // ok
				PORT3::PMR.B0 = ena;
				break;
			case ORDER::THIRD:
				PORTE::PMR.B3 = 0;
				MPC::PE3PFS.PSEL = sel;  // ok
				PORTE::PMR.B3 = ena;
				break;
			default:
				return false;
				break;
			}
			return true;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  MTU3d 関係、チャネル別ポート切り替え
			@param[in]	per	周辺機器タイプ
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合「false」
			@param[in]	odr	候補選択
			@param[in]	neg	反転入出力の場合「true」（サポートしない）
			@param[in]	inp	入力として利用する場合「true」（無視される）
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral per, CHANNEL ch, bool ena = true, ORDER odr = ORDER::FIRST, bool neg = false, bool inp = false) noexcept
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
			default:
				ret = false;
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマー系、クロックポート切り替え
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合場合「false」
			@param[in]	odr	候補選択
			@param[in]	neg	反転入出力の場合「true」（サポートしない）
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn_clock(CHANNEL ch, bool ena = true, ORDER odr = ORDER::FIRST, bool neg = false) noexcept
		{
			bool ret = true;

			if(odr == ORDER::BYPASS) return true;
			if(neg) return false;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			switch(ch) {
			case CHANNEL::CLKA:
				ret = clk_a_(odr, ena);
				break;
			case CHANNEL::CLKB:
				ret = clk_b_(odr, ena);
				break;
			case CHANNEL::CLKC:
				ret = clk_c_(odr, ena);
				break;
			case CHANNEL::CLKD:
				ret = clk_d_(odr, ena);
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

