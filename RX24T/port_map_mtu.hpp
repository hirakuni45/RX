#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・ポート・マッピング (MTU3d) @n
			・MTU 型に従って、タイマー用ポートを設定 @n
			・A、B バージョンの違いに注意 @n
			MTU0, MTU1, MTU2, MTU3, MTU4, MTU5, MTU6, MTU7, MTU9
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX24T/peripheral.hpp"
#include "RX24T/port.hpp"
#include "RX24T/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_mtu : public port_map_order {

		static bool mtu0_(CHANNEL ch, bool ena, bool neg, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b00011 : 0b00001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC0A[#]
			// P31 ( 61/100)
			// PB3 ( 32/100)
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
			// P30 ( 63/100)
			// PB2 ( 33/100)
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
			case CHANNEL::C:  // MTIOC0C[#]
			// PB1 ( 34/100)
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
			case CHANNEL::D:  // MTIOC0D[#]
			// PB0 (35/100)
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


		static bool mtu1_(CHANNEL ch, bool ena, bool neg, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b00011 : 0b00001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC1A
			// PA5 ( 36/100)
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
			// PA4 ( 37/100)
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


		static bool mtu2_(CHANNEL ch, bool ena, bool neg, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b00011 : 0b00001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC2A
			// PA3 ( 38/100)
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
			// PA2 ( 39/100)
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


		static bool mtu3_(CHANNEL ch, bool ena, bool neg, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b00011 : 0b00001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC3A
			// P11 ( 99/100)
			// P33 ( 58/100)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = sel;
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
			case CHANNEL::B:  // MTIOC3B
			// P71 ( 56/100)
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
			// P32 ( 59/100)
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
			// P74 ( 53/100)
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


		static bool mtu4_(CHANNEL ch, bool ena, bool neg, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b00011 : 0b00001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC4A[#]
			// P72 ( 55/100)
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
			case CHANNEL::B:  // MTIOC4B[#]
			// P73 ( 54/100)
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
			case CHANNEL::C:  // MTIOC4C[#]
			// P75 ( 52/100)
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
			case CHANNEL::D:  // MTIOC4D[#]
			// P76 ( 51/100)
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


		static bool mtu5_(CHANNEL ch, bool ena, bool neg, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b00011 : 0b00001) : 0;
			switch(ch) {
			case CHANNEL::U:  // MTIOC5U[#]
			// P24 ( 64/100)
			// P82 ( 96/100)
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
			case CHANNEL::V:  // MTIOC5V[#]
			// P23 ( 65/100)
			// P81 ( 97/100)
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
			case CHANNEL::W:  // MTIOC5W[#]
			// P22 ( 66/100)
			// P80 ( 98/100)
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
			uint8_t sel = ena ? (neg ? 0b00011 : 0b00001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC6A[#]
			// PA1 ( 40/100)
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
			// P95 ( 45/100)
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
			// PA0 ( 41/100)
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
			// P92 ( 48/100)
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
			uint8_t sel = ena ? (neg ? 0b00011 : 0b00001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC7A[#]
			// P94 ( 46/100)
				switch(odr) {
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
			// P93 ( 47/100)
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
			// P91 ( 49/100)
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
			// P90 ( 50/100)
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
			uint8_t sel = ena ? (neg ? 0b00011 : 0b00001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC9A[#]
			// P21 ( 67/100)
			// PD7 ( 18/100)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;  // ok
					PORT2::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;  // ok
					PORTD::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC9B[#]
			// P10 (100/100)
			// PE0 ( 17/100)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B0 = 0;
					MPC::P10PFS.PSEL = sel;  // ok
					PORT1::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
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
			// P20 ( 68/100)
			// PD6 ( 19/100)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = sel;  // ok
					PORT2::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
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
			// P02 (  2/100)
			// PE1 ( 16/100)
				switch(odr) {
				case ORDER::FIRST:
					PORT0::PMR.B2 = 0;
					MPC::P02PFS.PSEL = sel;  // ok
					PORT0::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = sel;  // ok
					PORTE::PMR.B1 = ena;
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


		static bool clk_a_(ORDER odr, bool ena, bool neg) noexcept
		{
			// P21 ( 67/100)
			// P33 ( 58/100)
			uint8_t sel = ena ? (neg ? 0b000100 : 0b000010) : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORT2::PMR.B1 = 0;
				MPC::P21PFS.PSEL = sel;  // ok
				PORT2::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORT3::PMR.B3 = 0;
				MPC::P33PFS.PSEL = sel;  // ok
				PORT3::PMR.B3 = ena;
				break;
			default:
				return false;
				break;
			}
			return true;
		}


		static bool clk_b_(ORDER odr, bool ena, bool neg) noexcept
		{
			// P20 ( 68/100)
			// P32 ( 59/100)
			uint8_t sel = ena ? (neg ? 0b000100 : 0b000010) : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORT2::PMR.B0 = 0;
				MPC::P20PFS.PSEL = sel;  // ok
				PORT2::PMR.B0 = ena;
				break;
			case ORDER::SECOND:
				PORT3::PMR.B2 = 0;
				MPC::P32PFS.PSEL = sel;  // ok
				PORT3::PMR.B2 = ena;
				break;
			default:
				return false;
				break;
			}
			return true;
		}


		static bool clk_c_(ORDER odr, bool ena, bool neg) noexcept
		{
			// P11 ( 99/100)
			// P31 ( 61/100)
			// PE4 (  8/100)
			uint8_t sel = ena ? (neg ? 0b000100 : 0b000010) : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B1 = 0;
				MPC::P11PFS.PSEL = sel;  // ok
				PORT1::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORT3::PMR.B1 = 0;
				MPC::P31PFS.PSEL = sel;  // ok
				PORT3::PMR.B1 = ena;
				break;
			case ORDER::THIRD:
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


		static bool clk_d_(ORDER odr, bool ena, bool neg) noexcept
		{
			// P10 (100/100)
			// P30 ( 63/100)
			// PE3 (  9/100)
			uint8_t sel = ena ? (neg ? 0b000100 : 0b000010) : 0;
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
			@param[in]	neg	反転入出力の場合「true」 @n
						B バージョンチップのみサポート、A バージョンでは設定不可
			@param[in]	inp	入力として利用する場合「true」（無視される）
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
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

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマー系、クロックポート切り替え
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合場合「false」
			@param[in]	odr	候補選択
			@param[in]	neg	反転入出力の場合「true」 @n
						B バージョンチップのみサポート、A バージョンでは設定不可
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn_clock(CHANNEL ch, bool ena = true, ORDER odr = ORDER::FIRST, bool neg = false) noexcept
		{
			bool ret = true;

			if(odr == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			switch(ch) {
			case CHANNEL::CLK_A:
				ret = clk_a_(odr, ena, neg);
				break;
			case CHANNEL::CLK_B:
				ret = clk_b_(odr, ena, neg);
				break;
			case CHANNEL::CLK_C:
				ret = clk_c_(odr, ena, neg);
				break;
			case CHANNEL::CLK_D:
				ret = clk_d_(odr, ena, neg);
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

