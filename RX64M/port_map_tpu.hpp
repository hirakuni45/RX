#pragma once
//=========================================================================//
/*!	@file
	@brief	RX64M/RX71M グループ・ポート・マッピング (TPU) @n
			・TPU 型に従って、タイマー用ポートを設定 @n
			TPU0, TPU1, TPU2, TPU3, TPU4, TPU5
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX64M/peripheral.hpp"
#include "RX64M/port.hpp"
#include "RX64M/mpc.hpp"
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
			// P86 (LFQFP100: ---) (LFQFP144:  41) (LFQFP176:  49)
			// PA0 (LFQFP100:  70) (LFQFP144:  97) (LFQFP176: 118)
				switch(odr) {
				case ORDER::FIRST:
					PORT8::PMR.B6 = 0;
					MPC::P86PFS.PSEL = sel;
					PORT8::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
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
			// P17 (LFQFP100:  29) (LFQFP144:  38) (LFQFP176:  46)
			// PA1 (LFQFP100:  69) (LFQFP144:  96) (LFQFP176: 114)
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
			// P32 (LFQFP100:  18) (LFQFP144:  27) (LFQFP176:  29)
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
			// P33 (LFQFP100:  17) (LFQFP144:  26) (LFQFP176:  28)
			// PA3 (LFQFP100:  67) (LFQFP144:  94) (LFQFP176: 110)
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
			// P56 (LFQFP100: ---) (LFQFP144:  50) (LFQFP176: ---)
			// PA4 (LFQFP100:  66) (LFQFP144:  92) (LFQFP176: 109)
				switch(odr) {
				case ORDER::FIRST:
					PORT5::PMR.B6 = 0;
					MPC::P56PFS.PSEL = sel;
					PORT5::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
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
			// P16 (LFQFP100:  30) (LFQFP144:  40) (LFQFP176:  48)
			// PA5 (LFQFP100:  65) (LFQFP144:  90) (LFQFP176: 108)
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
			// P87 (LFQFP100: ---) (LFQFP144:  39) (LFQFP176:  47)
			// PA6 (LFQFP100:  64) (LFQFP144:  89) (LFQFP176: 107)
				switch(odr) {
				case ORDER::FIRST:
					PORT8::PMR.B7 = 0;
					MPC::P87PFS.PSEL = sel;
					PORT8::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
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
			// P15 (LFQFP100:  31) (LFQFP144:  41) (LFQFP176:  50)
			// PA7 (LFQFP100:  63) (LFQFP144:  88) (LFQFP176: 106)
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
			// P21 (LFQFP100:  27) (LFQFP144:  36) (LFQFP176:  44)
			// PB0 (LFQFP100:  61) (LFQFP144:  87) (LFQFP176: 104)
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
			// P20 (LFQFP100:  28) (LFQFP144:  37) (LFQFP176:  45)
			// PB1 (LFQFP100:  59) (LFQFP144:  84) (LFQFP176: 100)
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
			// P22 (LFQFP100:  26) (LFQFP144:  35) (LFQFP176:  43)
			// PB2 (LFQFP100:  58) (LFQFP144:  83) (LFQFP176:  99)
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
			// P23 (LFQFP100:  25) (LFQFP144:  34) (LFQFP176:  42)
			// PB3 (LFQFP100:  57) (LFQFP144:  82) (LFQFP176:  98)
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
			// P25 (LFQFP100:  23) (LFQFP144:  32) (LFQFP176:  38)
			// PB4 (LFQFP100:  56) (LFQFP144:  81) (LFQFP176:  97)
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
			// P24 (LFQFP100:  24) (LFQFP144:  33) (LFQFP176:  40)
			// PB5 (LFQFP100:  55) (LFQFP144:  80) (LFQFP176:  96)
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
			// P13 (LFQFP100:  33) (LFQFP144:  44) (LFQFP176:  52)
			// PB6 (LFQFP100:  54) (LFQFP144:  79) (LFQFP176:  95)
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
			// P14 (LFQFP100:  32) (LFQFP144:  43) (LFQFP176:  51)
			// PB7 (LFQFP100:  53) (LFQFP144:  78) (LFQFP176:  94)
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
			// P14 (LFQFP100:  32) (LFQFP144:  43) (LFQFP176:  51)
			// PC2 (LFQFP100:  50) (LFQFP144:  70) (LFQFP176:  86)
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
			// P15 (LFQFP100:  31) (LFQFP144:  42) (LFQFP176:  50)
			// PA3 (LFQFP100:  67) (LFQFP144:  94) (LFQFP176: 110)
			// PC3 (LFQFP100:  49) (LFQFP144:  67) (LFQFP176:  83)
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
			// P16 (LFQFP100:  30) (LFQFP144:  40) (LFQFP176:  48)
			// PB2 (LFQFP100:  58) (LFQFP144:  83) (LFQFP176:  99)
			// PC0 (LFQFP100:  52) (LFQFP144:  75) (LFQFP176:  91)
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
			// P17 (LFQFP100:  29) (LFQFP144:  38) (LFQFP176:  46)
			// PB3 (LFQFP100:  57) (LFQFP144:  82) (LFQFP176:  98)
			// PC1 (LFQFP100:  51) (LFQFP144:  73) (LFQFP176:  89)
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
