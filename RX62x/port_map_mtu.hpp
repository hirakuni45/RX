#pragma once
//=========================================================================//
/*!	@file
	@brief	RX621/RX62N グループ・ポート・マッピング (MTU2 系)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX62x/peripheral.hpp"
#include "RX62x/port.hpp"
#include "RX62x/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_mtu : public port_map_order {
	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  MTU2 関係、チャネル別ポート切り替え
			@param[in]	per	周辺機器タイプ
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合場合「false」
			@param[in]	odr	候補を選択する場合
			@param[in]	neg	反転機能を使う場合「true」
			@param[in]	inp	入力端子として利用する場合「true」
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral per, CHANNEL ch, bool ena = true, ORDER odr = ORDER::FIRST, bool neg = false, bool inp = false) noexcept
		{
			if(odr == ORDER::BYPASS) return true;

			if(neg) return false;
			if(odr != ORDER::FIRST && odr != ORDER::SECOND) return false;

			bool ret = true;
			switch(per) {
			case peripheral::MTU0:
				switch(ch) {
				case CHANNEL::A:  // MTIOC0A:
				// P34 (LFQFP144:  25)
					PORT3::ICR.B4 = inp;
					break;
				case CHANNEL::B:  // MTIOC0B:
				// P15 (LFQFP144:  42)
					PORT1::ICR.B5 = inp;
					break;
				case CHANNEL::C:  // MTIOC0C:
				// P32 (LFQFP144:  27)
					PORT3::ICR.B2 = inp;
					break;
				case CHANNEL::D:  // MTIOC0D:
				// P33 (LFQFP144:  26)
					PORT3::ICR.B3 = inp;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU1:
				switch(ch) {
				case CHANNEL::A:  // MTIOC1A:
				// P20 (LFQFP144:  37)
					PORT2::ICR.B0 = inp;
					break;
				case CHANNEL::B:  // MTIOC1B:
				// P21 (LFQFP144:  36)
					PORT2::ICR.B1 = inp;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU2:
				switch(ch) {
				case CHANNEL::A:  // MTIOC2A:
				// P26 (LFQFP144:  31)
					PORT2::ICR.B6 = inp;
					break;
				case CHANNEL::B:  // MTIOC2B:
				// P27 (LFQFP144:  30)
					PORT2::ICR.B7 = inp;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU3:
				switch(ch) {
				case CHANNEL::A:  // MTIOC3A:
				// P17 (LFQFP144:  38)
					PORT1::ICR.B7 = inp;
					break;
				case CHANNEL::B:  // MTIOC3B:
				// P22 (LFQFP144:  35)
				// P80 (LFQFP144:  65)
					MPC::PFCMTU.MTUS3 = (odr != ORDER::FIRST);
					PORT2::ICR.B2 = inp;
					break;
				case CHANNEL::C:  // MTIOC3C:
				// P16 (LFQFP144:  40)
				// P56 (LFQFP144:  50)
					MPC::PFCMTU.MTUS2 = (odr != ORDER::FIRST);
					PORT1::ICR.B6 = inp;
					break;
				case CHANNEL::D:  // MTIOC3D:
				// P23 (LFQFP144:  34)
				// P81 (LFQFP144:  64)
					MPC::PFCMTU.MTUS3 = (odr != ORDER::FIRST);
					PORT2::ICR.B3 = inp;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU4:
				switch(ch) {
				case CHANNEL::A:  // MTIOC4A:
				// P24 (LFQFP144:  33)
				// P82 (LFQFP144:  63)
					MPC::PFCMTU.MTUS4 = (odr != ORDER::FIRST);
					PORT2::ICR.B4 = inp;
					break;
				case CHANNEL::B:  // MTIOC4B:
				// P30 (LFQFP144:  29)
				// P54 (LFQFP144:  52)
					MPC::PFCMTU.MTUS5 = (odr != ORDER::FIRST);
					PORT3::ICR.B0 = inp;
					break;
				case CHANNEL::C:  // MTIOC4C:
				// P25 (LFQFP144:  32)
				// P83 (LFQFP144:  58)
					MPC::PFCMTU.MTUS4 = (odr != ORDER::FIRST);
					PORT2::ICR.B5 = inp;
					break;
				case CHANNEL::D:  // MTIOC4D:
				// P31 (LFQFP144:  28)
				// P55 (LFQFP144:  51)
					MPC::PFCMTU.MTUS5 = (odr != ORDER::FIRST);
					PORT3::ICR.B1 = inp;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU5:
				switch(ch) {
				case CHANNEL::U:  // MTIOC5U:
				// P12 (LFQFP144:  45)
				// PD7 (LFQFP144: 119)
					MPC::PFCMTU.MTUS6 = (odr != ORDER::FIRST);
					PORT1::ICR.B2 = inp;
					break;
				case CHANNEL::V:  // MTIOC5V:
				// P11 (LFQFP144: ---)
				// PD6 (LFQFP144: 120)
					MPC::PFCMTU.MTUS6 = (odr != ORDER::FIRST);
					PORT1::ICR.B1 = inp;
					break;
				case CHANNEL::W:  // MTIOC5W:
				// P10 (LFQFP144: ---)
				// PD5 (LFQFP144: 121)
					MPC::PFCMTU.MTUS6 = (odr != ORDER::FIRST);
					PORT1::ICR.B0 = inp;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU6:
				switch(ch) {
				case CHANNEL::A:  // MTIOC6A:
				// PA0 (LFQFP144:  97)
					PORTA::ICR.B0 = inp;
					break;
				case CHANNEL::B:  // MTIOC6B:
				// PA1 (LFQFP144:  96)
					PORTA::ICR.B1 = inp;
					break;
				case CHANNEL::C:  // MTIOC6C:
				// PA2 (LFQFP144:  95)
					PORTA::ICR.B2 = inp;
					break;
				case CHANNEL::D:  // MTIOC6D:
				// PA3 (LFQFP144:  94)
					PORTA::ICR.B3 = inp;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU7:
				switch(ch) {
				case CHANNEL::A:  // MTIOC7A:
				// PA4 (LFQFP144:  92)
					PORTA::ICR.B4 = inp;
					break;
				case CHANNEL::B:  // MTIOC7B:
				// PA5 (LFQFP144:  90)
					PORTA::ICR.B5 = inp;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU8:
				switch(ch) {
				case CHANNEL::A:  // MTIOC8A:
				// PA6 (LFQFP144:  89)
					PORTA::ICR.B6 = inp;
					break;
				case CHANNEL::B:  // MTIOC8B:
				// PA7 (LFQFP144:  88)
					PORTA::ICR.B7 = inp;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU9:
				switch(ch) {
				case CHANNEL::A:  // MTIOC9A:
				// PB0 (LFQFP144:  87)
					PORTB::ICR.B0 = inp;
					break;
				case CHANNEL::B:  // MTIOC9B:
				// PB2 (LFQFP144:  83)
					PORTB::ICR.B2 = inp;
					break;
				case CHANNEL::C:  // MTIOC9C:
				// PB1 (LFQFP144:  84)
					PORTB::ICR.B1 = inp;
					break;
				case CHANNEL::D:  // MTIOC9D:
				// PB3 (LFQFP144:  82)
					PORTB::ICR.B3 = inp;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU10:
				switch(ch) {
				case CHANNEL::A:  // MTIOC10A:
				// PB4 (LFQFP144:  81)
					PORTB::ICR.B4 = inp;
					break;
				case CHANNEL::B:  // MTIOC10B:
				// PB6 (LFQFP144:  79)
					PORTB::ICR.B6 = inp;
					break;
				case CHANNEL::C:  // MTIOC10C:
				// PB5 (LFQFP144:  80)
					PORTB::ICR.B5 = inp;
					break;
				case CHANNEL::D:  // MTIOC10D:
				// PB7 (LFQFP144:  78)
					PORTB::ICR.B7 = inp;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU11:
				switch(ch) {
				case CHANNEL::U:  // MTIOC11U:
				// PC7 (LFQFP144:  60)
				// PD4 (LFQFP144: 122)
					MPC::PFDMTU.MTUS6 = (odr != ORDER::FIRST);
					PORTC::ICR.B7 = inp;
					break;
				case CHANNEL::V:	// MTIOC11V:
				// PC6 (LFQFP144:  61)
				// PD3 (LFQFP144: 123)
					MPC::PFDMTU.MTUS6 = (odr != ORDER::FIRST);
					PORTC::ICR.B6 = inp;
					break;
				case CHANNEL::W:  // MTIOC11W:
				// PC5 (LFQFP144:  62)
				// PD2 (LFQFP144: 124)
					MPC::PFDMTU.MTUS6 = (odr != ORDER::FIRST);
					PORTC::ICR.B5 = inp;
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
			switch(odr) {
			case ORDER::FIRST:  // MTCLKA-A:
			// P24 (LFQFP144:  33)
				MPC::PFCMTU.TCLKS = 0;
				PORT2::ICR.B4 = ena;
				break;
			case ORDER::SECOND:  // MTCLKA-B
			// PC6 (LFQFP144:  61)
				MPC::PFCMTU.TCLKS = 1;
				PORTC::ICR.B6 = ena;
				break;
			default:
				return false;
				break;
			}
			return true;
		}

		static bool clk_b_(ORDER odr, bool ena) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:   // MTCLKB-A
			// P25 (LFQFP144:  32)
				MPC::PFCMTU.TCLKS = 0;
				PORT2::ICR.B5 = ena;
				break;
			case ORDER::SECOND:  // MTCLKB-B
			// PC7 (LFQFP144:  60)
				MPC::PFCMTU.TCLKS = 1;
				PORTC::ICR.B7 = ena;
				break;
			default:
				return false;
				break;
			}
			return true;
		}

		static bool clk_c_(ORDER odr, bool ena) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:  // MTCLKC-A
			// P22 (LFQFP144:  35)
				MPC::PFCMTU.TCLKS = 0;
				PORT2::ICR.B2 = ena;
				break;
			case ORDER::SECOND:  // MTCLKC-B
			// PC4 (LFQFP144:  66)
				MPC::PFCMTU.TCLKS = 1;
				PORTC::ICR.B4 = ena;
				break;
			default:
				return false;
				break;
			}
			return true;
		}

		static bool clk_d_(ORDER odr, bool ena) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:   // MTCLKD-A
			// P23 (LFQFP144:  34)
				MPC::PFCMTU.TCLKS = 0;
				PORT2::ICR.B3 = ena;
				break;
			case ORDER::SECOND:  // MTCLKD-B
			// PC5 (LFQFP144:  62)
				MPC::PFCMTU.TCLKS = 1;
				PORTC::ICR.B5 = ena;
				break;
			default:
				return false;
				break;
			}
			return true;
		}

		static bool clk_e_(ORDER odr, bool ena) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:   // MTCLKE-A
			// PC2 (LFQFP144:  70)
				MPC::PFDMTU.TCLKS = 0;
				PORTC::ICR.B2 = ena;
				break;
			case ORDER::SECOND:  // MTCLKE-B
			// PB4 (LFQFP144:  81)
				MPC::PFDMTU.TCLKS = 1;
				PORTB::ICR.B4 = ena;
				break;
			default:
				return false;
				break;
			}
			return true;
		}

		static bool clk_f_(ORDER odr, bool ena) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:   // MTCLKF-A
			// PC3 (LFQFP144:  67)
				MPC::PFDMTU.TCLKS = 0;
				PORTC::ICR.B3 = ena;
				break;
			case ORDER::SECOND:  // MTCLKF-B
			// PB5 (LFQFP144:  80)
				MPC::PFDMTU.TCLKS = 1;
				PORTB::ICR.B5 = ena;
				break;
			default:
				return false;
				break;
			}
			return true;
		}

		static bool clk_g_(ORDER odr, bool ena) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:   // MTCLKG-A
			// PC0 (LFQFP144:  75)
				MPC::PFDMTU.TCLKS = 0;
				PORTC::ICR.B0 = ena;
				break;
			case ORDER::SECOND:  // MTCLKG-B
			// PB2 (LFQFP144:  83)
				MPC::PFDMTU.TCLKS = 1;
				PORTB::ICR.B2 = ena;
				break;
			default:
				return false;
				break;
			}
			return true;
		}

		static bool clk_h_(ORDER odr, bool ena) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:  // MTCLKH-A
			// PC1 (LFQFP144:  73)
				MPC::PFDMTU.TCLKS = 0;
				PORTC::ICR.B1 = ena;
				break;
			case ORDER::SECOND:  // MTCLKH-B
			// PB3 (LFQFP144:  82)
				MPC::PFDMTU.TCLKS = 1;
				PORTB::ICR.B3 = ena;
				break;
			default:
				return false;
				break;
			}
			return true;
		}

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマー系、クロックポート切り替え
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合場合「false」
			@param[in]	odr	候補選択
			@param[in]	neg	反転入出力の場合「true」
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn_clock(CHANNEL ch, bool ena = true, ORDER odr = ORDER::FIRST, bool neg = false) noexcept
		{
			if(neg) return false;

			bool ret = true;

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
			case CHANNEL::CLKE:
				ret = clk_e_(odr, ena);
				break;
			case CHANNEL::CLKF:
				ret = clk_f_(odr, ena);
				break;
			case CHANNEL::CLKG:
				ret = clk_g_(odr, ena);
				break;
			case CHANNEL::CLKH:
				ret = clk_h_(odr, ena);
				break;
			default:
				ret = false;
				break;
			}

			return ret;
		}
	};
}

