#pragma once
//=========================================================================//
/*!	@file
	@brief	RX230/RX231 グループ・ポート・マッピング (TPUa) @n
			・TPU 型に従って、タイマー用ポートを設定 @n
			TPU0, TPU1, TPU2, TPU3, TPU4, TPU5
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX231/peripheral.hpp"
#include "RX231/port.hpp"
#include "RX231/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_tpu : public port_map_order {

		static bool tpu0_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b00'0011 : 0;
			switch(ch) {
			case CHANNEL::A:  // TIOCA0:
			// PA0 (LFQFP64: 45) (LFQFP100:  70)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;
					PORTA::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // TIOCB0:
			// P17 (LFQFP64: 17) (LFQFP100:  29)
			// PA1 (LFQFP64: 44) (LFQFP100:  69)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;
					PORTA::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // TIOCC0:
			// P32 (LFQFP64: --) (LFQFP100:  18)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;
					PORT3::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // TIOCD0:
			// P33 (LFQFP64: --) (LFQFP100:  17)
			// PA3 (LFQFP64: 43) (LFQFP100:  67)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;
					PORT3::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = sel;
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

		static bool tpu1_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b00'0011 : 0;
			switch(ch) {
			case CHANNEL::A:  // TIOCA1:
			// PA4 (LFQFP64: 42) (LFQFP100:  66)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // TIOCB1:
			// P16 (LFQFP64: 18) (LFQFP100:  30)
			// PA5 (LFQFP64: --) (LFQFP100:  65)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;
					PORTA::PMR.B5 = ena;
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

		static bool tpu2_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b00'0011 : 0;
			switch(ch) {
			case CHANNEL::A:  // TIOCA2:
			// PA6 (LFQFP64: 41) (LFQFP100:  64)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = sel;
					PORTA::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // TIOCB2:
			// P15 (LFQFP64: 19) (LFQFP100:  31)
			// PA7 (LFQFP64: --) (LFQFP100:  63)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;
					PORT1::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B7 = 0;
					MPC::PA7PFS.PSEL = sel;
					PORTA::PMR.B7 = ena;
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

		static bool tpu3_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b00'0011 : 0;
			switch(ch) {
			case CHANNEL::A:  // TIOCA3:
			// P21 (LFQFP64: --) (LFQFP100:  27)
			// PB0 (LFQFP64: 39) (LFQFP100:  61)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;
					PORT2::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;
					PORTB::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // TIOCB3:
			// P20 (LFQFP64: --) (LFQFP100:  28)
			// PB1 (LFQFP64: 37) (LFQFP100:  59)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = sel;
					PORT2::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;
					PORTB::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // TIOCC3:
			// P22 (LFQFP64: --) (LFQFP100:  26)
			// PB2 (LFQFP64: --) (LFQFP100:  58)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;
					PORT2::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B2 = 0;
					MPC::PB2PFS.PSEL = sel;
					PORTB::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // TIOCD3:
			// P23 (LFQFP64: --) (LFQFP100:  25)
			// PB3 (LFQFP64: 36) (LFQFP100:  57)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;
					PORT2::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;
					PORTB::PMR.B3 = ena;
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

		static bool tpu4_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b00'0011 : 0;
			switch(ch) {
			case CHANNEL::A:  // TIOCA4:
			// P25 (LFQFP64: --) (LFQFP100:  23)
			// PB4 (LFQFP64: --) (LFQFP100:  56)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B5 = 0;
					MPC::P25PFS.PSEL = sel;
					PORT2::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B4 = 0;
					MPC::PB4PFS.PSEL = sel;
					PORTB::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // TIOCB4:
			// P24 (LFQFP64: --) (LFQFP100:  24)
			// PB5 (LFQFP64: 35) (LFQFP100:  55)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;
					PORT2::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = sel;
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

		static bool tpu5_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b00'0011 : 0;
			switch(ch) {
			case CHANNEL::A:  // TIOCA5:
			// P13 (LFQFP64: --) (LFQFP100:  33)
			// PB6 (LFQFP64: 34) (LFQFP100:  54)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;
					PORT1::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;
					PORTB::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // TIOCB5:
			// P14 (LFQFP64: 20) (LFQFP100:  32)
			// PB7 (LFQFP64: 33) (LFQFP100:  53)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;
					PORT1::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;
					PORTB::PMR.B7 = ena;
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
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(peripheral per, CHANNEL ch, bool ena = true, ORDER odr = ORDER::FIRST) noexcept
		{
			if(odr == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			switch(per) {
			case peripheral::TPU0:
				ret = tpu0_(ch, ena, odr);
				break;
			case peripheral::TPU1:
				ret = tpu1_(ch, ena, odr);
				break;
			case peripheral::TPU2:
				ret = tpu2_(ch, ena, odr);
				break;
			case peripheral::TPU3:
				ret = tpu3_(ch, ena, odr);
				break;
			case peripheral::TPU4:
				ret = tpu4_(ch, ena, odr);
				break;
			case peripheral::TPU5:
				ret = tpu5_(ch, ena, odr);
				break;
			default:
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  TPU クロック入力切り替え
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
			case CHANNEL::CLKA:  // TCLKA:
			// P14 (LFQFP64: 20) (LFQFP100:  32)
			// PC2 (LFQFP64: 32) (LFQFP100:  50)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = ena ? 0b00'0100 : 0;
					PORT1::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = ena ? 0b00'0011 : 0;
					PORTC::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::CLKB:  // TCLKB:
			// P15 (LFQFP64: 19) (LFQFP100:  31)
			// PA3 (LFQFP64: 43) (LFQFP100:  67)
			// PC3 (LFQFP64: 31) (LFQFP100:  49)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = ena ? 0b00'0100 : 0;
					PORT1::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = ena ? 0b00'0100 : 0;
					PORTA::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B3 = 0;
					MPC::PC3PFS.PSEL = ena ? 0b00'0011 : 0;
					PORTC::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::CLKC:  // TCLKC:
			// P16 (LFQFP64: 18) (LFQFP100:  30)
			// PB2 (LFQFP64: --) (LFQFP100:  58)
			// PC0 (LFQFP64: --) (LFQFP100:  52)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = ena ? 0b00'0100 : 0;
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B2 = 0;
					MPC::PB2PFS.PSEL = ena ? 0b00'0100 : 0;
					PORTB::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B0 = 0;
					MPC::PC0PFS.PSEL = ena ? 0b00'0011 : 0;
					PORTC::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::CLKD:  // TCLKD:
			// P17 (LFQFP64: 17) (LFQFP100:  29)
			// PB3 (LFQFP64: 36) (LFQFP100:  57)
			// PC1 (LFQFP64: --) (LFQFP100:  51)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = ena ? 0b00'0100 : 0;
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = ena ? 0b00'0100 : 0;
					PORTB::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = ena ? 0b00'0011 : 0;
					PORTC::PMR.B1 = ena;
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
