#pragma once
//=====================================================================//
/*!	@file
	@brief	RX72N グループ・ポート・マッピング (TPU) @n
			・TPU 型に従って、タイマー用ポートを設定 @n
			TPU0, TPU1, TPU2, TPU3
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
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
	class port_map_tpu : public port_map_order {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマー系・チャネル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class channel : uint8_t {
			A,		///< TPUx A (TIOCxA)
			B,		///< TPUx B (TIOCxB)
			C,		///< TPUx C (TIOCxC)
			D,		///< TPUx D (TIOCxD)
			NONE,	///< 無効なチャネル
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマー系・クロック・グループ @n
					※タイマーのクロック系は、TPU 共通なので、識別子としてグループを使う
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class group : uint8_t {
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

/// P33 ( 28)  TIOCD0
/// P32 ( 29)  TIOCC0
/// P25 ( 38)  TIOCA4
/// P24 ( 40)  TIOCB4
/// P23 ( 42)  TIOCD3
/// P22 ( 43)  TIOCC3
/// P21 ( 44)  TIOCA3
/// P20 ( 45)  TIOCB3
/// P17 ( 46)  TIOCB0 / TCLKD
/// P87 ( 47)  TIOCA2
/// P16 ( 48)  TIOCB1 / TCLKC
/// P86 ( 49)  TIOCA0
/// P15 ( 50)  TIOCB2 / TCLKB
/// P14 ( 51)  TIOCB5 / TCLKA
/// P13 ( 52)  TIOCA5
/// P85 ( 61)  TIOCC0
/// P56 ( 64)  TIOCA1
/// PC2 ( 86)  TCLKA
/// PC1 ( 89)  TCLKD
/// PC0 ( 91)  TCLKC
/// PB7 ( 94)  TIOCB5
/// PB6 ( 95)  TIOCA5
/// PB5 ( 96)  TIOCB4
/// PB4 ( 97)  TIOCA4
/// PB3 ( 98)  TIOCD3 / TCLKD
/// PB2 ( 99)  TIOCC3 / TCLKC
/// PB1 (100)  TIOCB3
/// PB0 (104)  TIOCA3
/// PA7 (106)  TIOCB2
/// PA6 (107)  TIOCA2
/// PA5 (108)  TIOCB1
/// PA4 (109)  TIOCA1
/// PA3 (110)  TIOCD0 / TCLKB
/// PA1 (113)  TIOCB0
/// PA0 (118)  TIOCA0

		static bool tpu0_(channel ch, bool ena, ORDER opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b000001 : 0;
			switch(ch) {

			case channel::A:
				switch(opt) {
				case ORDER::FIRST:
					PORT3::PMR.B4 = 0;
					MPC::P34PFS.PSEL = sel;
					PORT3::PMR.B4 = ena;
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

			case channel::B:
				switch(opt) {
				case ORDER::FIRST:
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;
					PORT1::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;
					PORT1::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;
					PORTA::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case channel::C:
				switch(opt) {
				case ORDER::FIRST:
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;
					PORT3::PMR.B2 = ena;
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

			case channel::D:
				switch(opt) {
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


		static bool tpu1_(channel ch, bool ena, ORDER opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b000001 : 0;
			switch(ch) {

			case channel::A:
				switch(opt) {
				case ORDER::FIRST:
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = sel;
					PORT2::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = sel;
					PORTE::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case channel::B:
				switch(opt) {
				case ORDER::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;
					PORT2::PMR.B1 = ena;
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


		static bool tpu2_(channel ch, bool ena, ORDER opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b000001 : 0;
			switch(ch) {

			case channel::A:
				switch(opt) {
				case ORDER::FIRST:
					PORT2::PMR.B6 = 0;
					MPC::P26PFS.PSEL = sel;
					PORT2::PMR.B6 = ena;
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

			case channel::B:
				switch(opt) {
				case ORDER::FIRST:
					PORT2::PMR.B7 = 0;
					MPC::P27PFS.PSEL = sel;
					PORT2::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = sel;
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


		static bool tpu3_(channel ch, bool ena, ORDER opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b000001 : 0;
			switch(ch) {

			case channel::A:
				switch(opt) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;
					PORT1::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;
					PORTC::PMR.B7 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = sel;
					PORTC::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case channel::B:
				switch(opt) {
				case ORDER::FIRST:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;
					PORT2::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;
					PORTC::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					PORT8::PMR.B0 = 0;
					MPC::P80PFS.PSEL = sel;
					PORT8::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;
					PORTB::PMR.B7 = ena;
					break;
				case ORDER::FIFTH:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SIXTH:
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = sel;
					PORTE::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case channel::C:
				switch(opt) {
				case ORDER::FIRST:
					PORTJ::PMR.B3 = 0;
					MPC::PJ3PFS.PSEL = sel;
					PORTJ::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT5::PMR.B6 = 0;
					MPC::P56PFS.PSEL = sel;
					PORT5::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;
					PORTC::PMR.B6 = ena;
					break;
				case ORDER::FIFTH:
					PORTC::PMR.B0 = 0;
					MPC::PC0PFS.PSEL = sel;
					PORTC::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case channel::D:
				switch(opt) {
				case ORDER::FIRST:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;
					PORT2::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B1 = 0;
					MPC::P81PFS.PSEL = sel;
					PORT8::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;
					PORTC::PMR.B4 = ena;
					break;
				case ORDER::FOURTH:
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::FIFTH:
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = sel;
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

	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマー系、チャネル別ポート切り替え
			@param[in]	per	周辺機器タイプ
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合場合「false」
			@param[in]	opt	候補を選択する場合
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(peripheral per, channel ch, bool ena = true, ORDER opt = ORDER::FIRST) noexcept
		{
			if(opt == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = true;
			switch(per) {
			case peripheral::TPU0:
				ret = tpu0_(ch, ena, opt);
				break;
			case peripheral::TPU1:
				ret = tpu1_(ch, ena, opt);
				break;
			case peripheral::TPU2:
				ret = tpu2_(ch, ena, opt);
				break;
			case peripheral::TPU3:
				ret = tpu3_(ch, ena, opt);
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
		static bool turn_clock(group grp, channel ch, bool ena = true) noexcept
		{
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			uint8_t sel = ena ? 0b000010 : 0;
			bool ret = true;
#if 0
			switch(grp) {
			/// P15 ( 50)  MTIOC0B / MTCLKB
			/// PA1 (114)  MTIOC0B / MTCLKC / MTIOC7B
			/// PA3 (110)  MTIOC0D / MTCLKD
			case group::AREA0:
				switch(ch) {
				case channel::CLK_B:
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;
					PORT1::PMR.B5 = ena;
					break;
				case channel::CLK_C:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;
					PORTA::PMR.B1 = ena;
					break;
				case channel::CLK_D:
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
			case group::AREA1:
				switch(ch) {
				case channel::CLK_A:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;
					PORT1::PMR.B4 = ena;
					break;
				case channel::CLK_B:
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;
					PORTC::PMR.B7 = ena;
					break;
				case channel::CLK_C:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;
					PORT2::PMR.B2 = ena;
					break;
				case channel::CLK_D:
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
			case group::AREA2:
				switch(ch) {
				case channel::CLK_A:
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;
					PORTC::PMR.B6 = ena;
					break;
				case channel::CLK_C:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;
					PORT2::PMR.B3 = ena;
					break;
				case channel::CLK_D:
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
			case group::AREA3:
				switch(ch) {
				case channel::CLK_A:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;
					PORT2::PMR.B4 = ena;
					break;
				case channel::CLK_B:
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
			case group::AREA4:
				switch(ch) {
				case channel::CLK_A:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B4 = ena;
					break;
				case channel::CLK_B:
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
			case group::AREA5:
				switch(ch) {
				case channel::CLK_A:
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
#endif
			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}

