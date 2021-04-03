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
#include "RX600/port.hpp"
#include "RX600/mpc.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_gptw {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ポート・マッピング・オプション型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class option : uint8_t {
			BYPASS,		///< ポートマップの設定をバイパスする場合
			FIRST,		///< 第１候補
			SECOND,		///< 第２候補
			THIRD,		///< 第３候補
			FOURTH,		///< 第４候補
			FIFTH,		///< 第５候補
			SIXTH,		///< 第６候補
			SEVENTH,	///< 第７候補
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GPTWx チャネル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class channel : uint8_t {
			A,		///< GPTWx A (GTIOCxA)
			B,		///< GPTWx B (GTIOCxB)
		};

	private:
		static bool gptw0_(channel ch, bool ena, bool neg, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			/// 0A: P12(0), P71(0), PD2(1), PD7(0), PG1(1)
			case channel::A:
				switch(opt) {
				case option::FIRST:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT1::PMR.B2 = 0;
					MPC::P12PFS.PSEL = sel;
					PORT1::PMR.B2 = ena;
					break;
				case option::SECOND:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT7::PMR.B1 = 0;
					MPC::P71PFS.PSEL = sel;
					PORT7::PMR.B1 = ena;
					break;
				case option::THIRD:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;
					PORTD::PMR.B2 = ena;
					break;
				case option::FOURTH:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;
					PORTD::PMR.B7 = ena;
					break;
				case option::FIFTH:
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
			/// 0B: P15(0), P74(0), PD1(1), PD6(0), PG2(1)
			case channel::B:
				switch(opt) {
				case option::FIRST:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;
					PORT1::PMR.B5 = ena;
					break;
				case option::SECOND:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT7::PMR.B4 = 0;
					MPC::P74PFS.PSEL = sel;
					PORT7::PMR.B4 = ena;
					break;
				case option::THIRD:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;
					PORTD::PMR.B1 = ena;
					break;
				case option::FOURTH:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;
					PORTD::PMR.B6 = ena;
					break;
				case option::FIFTH:
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


		static bool gptw1_(channel ch, bool ena, bool neg, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			/// 1A: P13(0), P72(0), PD0(1), PD5(0), PK2(1)
			case channel::A:
				switch(opt) {
				case option::FIRST:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;
					PORT1::PMR.B3 = ena;
					break;
				case option::SECOND:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT7::PMR.B2 = 0;
					MPC::P72PFS.PSEL = sel;
					PORT7::PMR.B2 = ena;
					break;
				case option::THIRD:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORTD::PMR.B0 = 0;
					MPC::PD0PFS.PSEL = sel;
					PORTD::PMR.B0 = ena;
					break;
				case option::FOURTH:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORTD::PMR.B5 = 0;
					MPC::PD5PFS.PSEL = sel;
					PORTD::PMR.B5 = ena;
					break;
				case option::FIFTH:
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
			/// 1B: P16(0), P75(0), PB7(0), PD4(0), PG0(1)
			case channel::B:
				switch(opt) {
				case option::FIRST:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;
					PORT1::PMR.B6 = ena;
					break;
				case option::SECOND:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT7::PMR.B5 = 0;
					MPC::P75PFS.PSEL = sel;
					PORT7::PMR.B5 = ena;
					break;
				case option::THIRD:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;
					PORTB::PMR.B7 = ena;
					break;
				case option::FOURTH:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;
					PORTD::PMR.B4 = ena;
					break;
				case option::FIFTH:
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


		static bool gptw2_(channel ch, bool ena, bool neg, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			/// 2A: P14(0), P73(0), PB6(0), PD3(0), PK0(1)
			case channel::A:
				switch(opt) {
				case option::FIRST:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;
					PORT1::PMR.B4 = ena;
					break;
				case option::SECOND:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT7::PMR.B3 = 0;
					MPC::P73PFS.PSEL = sel;
					PORT7::PMR.B3 = ena;
					break;
				case option::THIRD:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT8::PMR.B6 = 0;
					MPC::P86PFS.PSEL = sel;
					PORT8::PMR.B6 = ena;
					break;
				case option::FOURTH:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = sel;
					PORTD::PMR.B3 = ena;
					break;
				case option::FIFTH:
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
			/// 2B: P17(0), P76(0), PB5(0), PD2(0), PK1(1)
			case channel::B:
				switch(opt) {
				case option::FIRST:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B7 = ena;
					break;
				case option::SECOND:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;
					PORT7::PMR.B6 = ena;
					break;
				case option::THIRD:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = sel;
					PORTB::PMR.B5 = ena;
					break;
				case option::FOURTH:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;
					PORTD::PMR.B2 = ena;
					break;
				case option::FIFTH:
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


		static bool gptw3_(channel ch, bool ena, bool neg, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			/// 3A: P32(0), PD1(0), PD7(1), PE5(0)
			case channel::A:
				switch(opt) {
				case option::FIRST:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;
					PORT3::PMR.B2 = ena;
					break;
				case option::SECOND:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;
					PORTD::PMR.B1 = ena;
					break;
				case option::THIRD:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;
					PORTD::PMR.B7 = ena;
					break;
				case option::FOURTH:
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
			/// 3B: P11(0), P33(0), PD0(0), PD6(1)
			case channel::B:
				switch(opt) {
				case option::FIRST:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = sel;
					PORT1::PMR.B1 = ena;
					break;
				case option::SECOND:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;
					PORT3::PMR.B3 = ena;
					break;
				case option::THIRD:
					sel = ena ? (neg ? 0b010110 : 0b010100) : 0;
					PORTD::PMR.B0 = 0;
					MPC::PD0PFS.PSEL = sel;
					PORTD::PMR.B0 = ena;
					break;
				case option::FOURTH:
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


		static bool gptw4_(channel ch, bool ena, bool neg, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			/// 4A: P71, P95
			case channel::A:
				switch(opt) {
				case option::FIRST:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORT7::PMR.B1 = 0;
					MPC::P71PFS.PSEL = sel;
					PORT7::PMR.B1 = ena;
					break;
				case option::SECOND:
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
			/// 4B: P74, P92
			case channel::B:
				switch(opt) {
				case option::FIRST:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORT7::PMR.B4 = 0;
					MPC::P74PFS.PSEL = sel;
					PORT7::PMR.B4 = ena;
					break;
				case option::SECOND:
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


		static bool gptw5_(channel ch, bool ena, bool neg, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			/// 5A: P72, P94
			case channel::A:
				switch(opt) {
				case option::FIRST:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORT7::PMR.B2 = 0;
					MPC::P72PFS.PSEL = sel;
					PORT7::PMR.B2 = ena;
					break;
				case option::SECOND:
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
			/// 5B: P75, P91
			case channel::B:
				switch(opt) {
				case option::FIRST:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORT7::PMR.B5 = 0;
					MPC::P75PFS.PSEL = sel;
					PORT7::PMR.B5 = ena;
					break;
				case option::SECOND:
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


		static bool gptw6_(channel ch, bool ena, bool neg, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			/// 6A: P73, P93
			case channel::A:
				switch(opt) {
				case option::FIRST:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORT7::PMR.B3 = 0;
					MPC::P73PFS.PSEL = sel;
					PORT7::PMR.B3 = ena;
					break;
				case option::SECOND:
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
			/// 6B: P76, P90
			case channel::B:
				switch(opt) {
				case option::FIRST:
					sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;
					PORT7::PMR.B6 = ena;
					break;
				case option::SECOND:
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


		static bool gptw7_(channel ch, bool ena, bool neg, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
			switch(ch) {
			/// 7A: P12, P95
			case channel::A:
				switch(opt) {
				case option::FIRST:
					PORT1::PMR.B2 = 0;
					MPC::P12PFS.PSEL = sel;
					PORT1::PMR.B2 = ena;
					break;
				case option::SECOND:
					PORT9::PMR.B5 = 0;
					MPC::P95PFS.PSEL = sel;
					PORT9::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// 7B: P76, P90
			case channel::B:
				switch(opt) {
				case option::FIRST:
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;
					PORT7::PMR.B6 = ena;
					break;
				case option::SECOND:
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


		static bool gptw8_(channel ch, bool ena, bool neg, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
			switch(ch) {
			/// 8A: P13, P94
			case channel::A:
				switch(opt) {
				case option::FIRST:
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;
					PORT1::PMR.B3 = ena;
					break;
				case option::SECOND:
					PORT9::PMR.B4 = 0;
					MPC::P94PFS.PSEL = sel;
					PORT9::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// 8B: P16, P91
			case channel::B:
				switch(opt) {
				case option::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;
					PORT1::PMR.B6 = ena;
					break;
				case option::SECOND:
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


		static bool gptw9_(channel ch, bool ena, bool neg, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b010111 : 0b010101) : 0;
			switch(ch) {
			/// 9A: P14, P93
			case channel::A:
				switch(opt) {
				case option::FIRST:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;
					PORT1::PMR.B4 = ena;
					break;
				case option::SECOND:
					PORT9::PMR.B3 = 0;
					MPC::P93PFS.PSEL = sel;
					PORT9::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// 9B: P17, P90
			case channel::B:
				switch(opt) {
				case option::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B7 = ena;
					break;
				case option::SECOND:
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


	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GPTW[0-9]、チャネル別ポート切り替え
			@param[in]	per	周辺機器タイプ
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合「false」
			@param[in]	neg	反転入出力の場合「true」
			@param[in]	opt	候補を選択する場合
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(peripheral per, channel ch, bool ena = true, bool neg = false, option opt = option::FIRST) noexcept
		{
			if(opt == option::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = true;
			switch(per) {
			case peripheral::GPTW0:
				ret = gptw0_(ch, ena, neg, opt);
				break;
			case peripheral::GPTW1:
				ret = gptw1_(ch, ena, neg, opt);
				break;
			case peripheral::GPTW2:
				ret = gptw2_(ch, ena, neg, opt);
				break;
			case peripheral::GPTW3:
				ret = gptw3_(ch, ena, neg, opt);
				break;
			case peripheral::GPTW4:
				ret = gptw4_(ch, ena, neg, opt);
				break;
			case peripheral::GPTW5:
				ret = gptw5_(ch, ena, neg, opt);
				break;
			case peripheral::GPTW6:
				ret = gptw6_(ch, ena, neg, opt);
				break;
			case peripheral::GPTW7:
				ret = gptw7_(ch, ena, neg, opt);
				break;
			case peripheral::GPTW8:
				ret = gptw8_(ch, ena, neg, opt);
				break;
			case peripheral::GPTW9:
				ret = gptw9_(ch, ena, neg, opt);
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

