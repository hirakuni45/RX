#pragma once
//=====================================================================//
/*!	@file
	@brief	RX72M グループ・ポート・マッピング (MTU) @n
			・MTU 型に従って、タイマー用ポートを設定 @n
			MTU0, MTU1, MTU2, MTU3, MTU4, MTU5, MTU6, MTU7, MTU8
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX72M/peripheral.hpp"
#include "RX600/port.hpp"
#include "RX600/mpc.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_mtu {
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
			FORCE,		///< 第４候補
			FIFTH,		///< 第５候補
			SIXTH,		///< 第６候補
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマー系・チャネル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class channel : uint8_t {
			A,		///< MTUx A (MTIOCxA)
			B,		///< MTUx B (MTIOCxB)
			C,		///< MTUx C (MTIOCxC)
			D,		///< MTUx D (MTIOCxD)
			U,		///< MTU5 U (MTIC5U)
			V,		///< MTU5 V (MTIC5V)
			W,		///< MTU5 W (MTIC5W)
			CLK_A,	///< MTCLKA
			CLK_B,	///< MTCLKB
			CLK_C,	///< MTCLKC
			CLK_D,	///< MTCLKD
			NONE,	///< 無効なチャネル
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマー系・クロック・グループ @n
					※タイマーのクロック系は、MTU 共通なので、識別子としてグループを使う
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class group : uint8_t {
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
		static bool mtu0_(channel ch, bool ena, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b000001 : 0;
			switch(ch) {
			///< P34 ( 27)  MTIOC0A
			///< PB3 ( 98)  MTIOC0A / MTIOC4A
			case channel::A:
				switch(opt) {
				case option::FIRST:
					PORT3::PMR.B4 = 0;
					MPC::P34PFS.PSEL = sel;
					PORT3::PMR.B4 = ena;
					break;
				case option::SECOND:
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;
					PORTB::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< P15 ( 50)  MTIOC0B / MTCLKB
			///< P13 ( 52)  MTIOC0B
			///< PA1 (114)  MTIOC0B / MTCLKC / MTIOC7B
			case channel::B:
				switch(opt) {
				case option::FIRST:
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;
					PORT1::PMR.B5 = ena;
					break;
				case option::SECOND:
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;
					PORT1::PMR.B3 = ena;
					break;
				case option::THIRD:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;
					PORTA::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< P32 ( 29)  MTIOC0C
			///< PB1 (100)  MTIOC0C / MTIOC4C
			case channel::C:
				switch(opt) {
				case option::FIRST:
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;
					PORT3::PMR.B2 = ena;
					break;
				case option::SECOND:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;
					PORTB::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< P33 ( 28)  MTIOC0D
			///< PA3 (110)  MTIOC0D / MTCLKD
			case channel::D:
				switch(opt) {
				case option::FIRST:
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;
					PORT3::PMR.B3 = ena;
					break;
				case option::SECOND:
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


		static bool mtu1_(channel ch, bool ena, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b000001 : 0;
			switch(ch) {
			///< P20 ( 45)  MTIOC1A
			///< P21 ( 44)  MTIOC1B / MTIOC4A
			///< PB5 ( 96)  MTIOC2A / MTIOC1B
			case channel::A:
				switch(opt) {
				case option::FIRST:
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = sel;
					PORT2::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case channel::B:
				switch(opt) {
				case option::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;
					PORT2::PMR.B1 = ena;
					break;
				case option::SECOND:
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


		static bool mtu2_(channel ch, bool ena, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b000001 : 0;
			switch(ch) {
			///< P26 ( 37)  MTIOC2A
			///< PB5 ( 96)  MTIOC2A / MTIOC1B
			///< P27 ( 36)  MTIOC2B
			case channel::A:
				switch(opt) {
				case option::FIRST:
					PORT2::PMR.B6 = 0;
					MPC::P26PFS.PSEL = sel;
					PORT2::PMR.B6 = ena;
					break;
				case option::SECOND:
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
				case option::FIRST:
					PORT2::PMR.B7 = 0;
					MPC::P27PFS.PSEL = sel;
					PORT2::PMR.B7 = ena;
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


		static bool mtu3_(channel ch, bool ena, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b000001 : 0;
			switch(ch) {
			///< P17 ( 46)  MTIOC3A / MTIOC3B / MTIOC4B
			///< P14 ( 51)  MTIOC3A / MTCLKA
			///< PC7 ( 76)  MTIOC3A / MTCLKB
			///< PC1 ( 89)  MTIOC3A
			case channel::A:
				switch(opt) {
				case option::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B7 = ena;
					break;
				case option::SECOND:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;
					PORT1::PMR.B4 = ena;
					break;
				case option::THIRD:
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;
					PORTC::PMR.B7 = ena;
					break;
				case option::FORCE:
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = sel;
					PORTC::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< P22 ( 43)  MTIOC3B / MTCLKC
			///< PC5 ( 78)  MTIOC3B / MTCLKD
			///< P80 ( 81)  MTIOC3B
			///< PB7 ( 94)  MTIOC3B
			case channel::B:
				switch(opt) {
				case option::FIRST:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;
					PORT2::PMR.B2 = ena;
					break;
				case option::SECOND:
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;
					PORTC::PMR.B5 = ena;
					break;
				case option::THIRD:
					PORT8::PMR.B0 = 0;
					MPC::P80PFS.PSEL = sel;
					PORT8::PMR.B0 = ena;
					break;
				case option::FORCE:
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;
					PORTB::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< PJ3 ( 13)  MTIOC3C
			///< P56 ( 64)  MTIOC3C
			///< P16 ( 48)  MTIOC3C / MTIOC3D
			///< PC6 ( 77)  MTIOC3C / MTCLKA
			///< PC0 ( 91)  MTIOC3C
			case channel::C:
				switch(opt) {
				case option::FIRST:
					PORTJ::PMR.B3 = 0;
					MPC::PJ3PFS.PSEL = sel;
					PORTJ::PMR.B3 = ena;
					break;
				case option::SECOND:
					PORT5::PMR.B6 = 0;
					MPC::P56PFS.PSEL = sel;
					PORT5::PMR.B6 = ena;
					break;
				case option::THIRD:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;
					PORT1::PMR.B6 = ena;
					break;
				case option::FORCE:
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;
					PORTC::PMR.B6 = ena;
					break;
				case option::FIFTH:
					PORTC::PMR.B0 = 0;
					MPC::PC0PFS.PSEL = sel;
					PORTC::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< P23 ( 42)  MTIOC3D / MTCLKD
			///< P81 ( 80)  MTIOC3D
			///< PC4 ( 82)  MTIOC3D / MTCLKC
			///< PB6 ( 95)  MTIOC3D
			///< PE0 (135)  MTIOC3D
			case channel::D:
				switch(opt) {
				case option::FIRST:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;
					PORT2::PMR.B3 = ena;
					break;
				case option::SECOND:
					PORT8::PMR.B1 = 0;
					MPC::P81PFS.PSEL = sel;
					PORT8::PMR.B1 = ena;
					break;
				case option::THIRD:
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;
					PORTC::PMR.B4 = ena;
					break;
				case option::FORCE:
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;
					PORTB::PMR.B6 = ena;
					break;
				case option::FIFTH:
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


		static bool mtu4_(channel ch, bool ena, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b000001 : 0;
			switch(ch) {
			///< P24 ( 40)  MTIOC4A / MTCLKA
			///< P82 ( 79)  MTIOC4A
			///< PA0 (118)  MTIOC4A / MTIOC6D
			///< PE2 (133)  MTIOC4A
			case channel::A:
				switch(opt) {
				case option::FIRST:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;
					PORT2::PMR.B4 = ena;
					break;
				case option::SECOND:
					PORT8::PMR.B2 = 0;
					MPC::P82PFS.PSEL = sel;
					PORT8::PMR.B2 = ena;
					break;
				case option::THIRD:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;
					PORTA::PMR.B0 = ena;
					break;
				case option::FORCE:
					PORTE::PMR.B2 = 0;
					MPC::PE2PFS.PSEL = sel;
					PORTE::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< P30 ( 33)  MTIOC4B
			///< P54 ( 66)  MTIOC4B
			///< PC2 ( 86)  MTIOC4B
			///< PE3 (132)  MTIOC4B
			///< PD1 (156)  MTIOC4B
			case channel::B:
				switch(opt) {
				case option::FIRST:
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = sel;
					PORT3::PMR.B0 = ena;
					break;
				case option::SECOND:
					PORT5::PMR.B4 = 0;
					MPC::P54PFS.PSEL = sel;
					PORT5::PMR.B4 = ena;
					break;
				case option::THIRD:
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = sel;
					PORTC::PMR.B2 = ena;
					break;
				case option::FORCE:
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = sel;
					PORTE::PMR.B3 = ena;
					break;
				case option::FIFTH:
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;
					PORTD::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< P25 ( 38)  MTIOC4C / MTCLKB
			///< P87 ( 47)  MTIOC4C
			///< P83 ( 74)  MTIOC4C
			///< PE5 (130)  MTIOC4C / MTIOC2B
			///< PE1 (134)  MTIOC4C / MTIOC3B
			case channel::C:
				switch(opt) {
				case option::FIRST:
					PORT2::PMR.B5 = 0;
					MPC::P25PFS.PSEL = sel;
					PORT2::PMR.B5 = ena;
					break;
				case option::SECOND:
					PORT8::PMR.B7 = 0;
					MPC::P87PFS.PSEL = sel;
					PORT8::PMR.B7 = ena;
					break;
				case option::THIRD:
					PORT8::PMR.B3 = 0;
					MPC::P83PFS.PSEL = sel;
					PORT8::PMR.B3 = ena;
					break;
				case option::FORCE:
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = sel;
					PORTE::PMR.B5 = ena;
					break;
				case option::FIFTH:
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = sel;
					PORTE::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< P31 ( 32)  MTIOC4D
			///< P86 ( 49)  MTIOC4D
			///< P55 ( 65)  MTIOC4D
			///< PC3 ( 83)  MTIOC4D
			///< PE4 (131)  MTIOC4D / MTIOC1A
			///< PD2 (154)  MTIOC4D
			case channel::D:
				switch(opt) {
				case option::FIRST:
					PORT3::PMR.B1 = 0;
					MPC::P31PFS.PSEL = sel;
					PORT3::PMR.B1 = ena;
					break;
				case option::SECOND:
					PORT8::PMR.B6 = 0;
					MPC::P86PFS.PSEL = sel;
					PORT8::PMR.B6 = ena;
					break;
				case option::THIRD:
					PORT5::PMR.B5 = 0;
					MPC::P55PFS.PSEL = sel;
					PORT5::PMR.B5 = ena;
					break;
				case option::FORCE:
					PORTC::PMR.B3 = 0;
					MPC::PC3PFS.PSEL = sel;
					PORTC::PMR.B3 = ena;
					break;
				case option::FIFTH:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = sel;
					PORTE::PMR.B4 = ena;
					break;
				case option::SIXTH:
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;
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


		static bool mtu5_(channel ch, bool ena, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b000001 : 0;
			switch(ch) {
			///< P12 ( 53)  MTIC5U
			///< PA4 (109)  MTIC5U / MTCLKA
			///< PD7 (143)  MTIC5U
			case channel::U:
				switch(opt) {
				case option::FIRST:
					PORT1::PMR.B2 = 0;
					MPC::P12PFS.PSEL = sel;
					PORT1::PMR.B2 = ena;
					break;
				case option::SECOND:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B4 = ena;
					break;
				case option::THIRD:
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;
					PORTD::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< P11 ( 67)  MTIC5V
			///< PA6 (107)  MTIC5V / MTCLKB
			///< PD6 (145)  MTIC5V / MTIOC8A
			case channel::V:
				switch(opt) {
				case option::FIRST:
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = sel;
					PORT1::PMR.B1 = ena;
					break;
				case option::SECOND:
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = sel;
					PORTA::PMR.B6 = ena;
					break;
				case option::THIRD:
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;
					PORTD::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< P10 ( 68)  MTIC5W
			///< PB0 (104)  MTIC5W
			///< PD5 (147)  MTIC5W / MTIOC8C / MTCLKA
			case channel::W:
				switch(opt) {
				case option::FIRST:
					PORT1::PMR.B0 = 0;
					MPC::P10PFS.PSEL = sel;
					PORT1::PMR.B0 = ena;
					break;
				case option::SECOND:
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;
					PORTB::PMR.B0 = ena;
					break;
				case option::THIRD:
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
			return ret;
		}


		static bool mtu6_(channel ch, bool ena, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b000001 : 0;
			switch(ch) {
			///< PJ1 ( 59)  MTIOC6A
			///< PE7 (125)  MTIOC6A
			///< PJ0 ( 60)  MTIOC6B
			///< PA5 (108)  MTIOC6B
			///< P85 ( 61)  MTIOC6C
			///< PE6 (126)  MTIOC6C
			///< P84 ( 62)  MTIOC6D
			case channel::A:
				switch(opt) {
				case option::FIRST:
//					PORTJ::PMR.B1 = 0;
//					MPC::PJ1PFS.PSEL = sel;
//					PORTJ::PMR.B1 = ena;
					break;
				case option::SECOND:
					PORTE::PMR.B7 = 0;
					MPC::PE7PFS.PSEL = sel;
					PORTE::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case channel::B:
				switch(opt) {
				case option::FIRST:
//					PORTJ::PMR.B0 = 0;
//					MPC::PJ0PFS.PSEL = sel;
//					PORTJ::PMR.B0 = ena;
					break;
				case option::SECOND:
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;
					PORTA::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case channel::C:
				switch(opt) {
				case option::FIRST:
					PORT8::PMR.B5 = 0;
					MPC::P85PFS.PSEL = sel;
					PORT8::PMR.B5 = ena;
					break;
				case option::SECOND:
					PORTE::PMR.B6 = 0;
					MPC::PE6PFS.PSEL = sel;
					PORTE::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case channel::D:
				switch(opt) {
				case option::FIRST:
					PORT8::PMR.B4 = 0;
					MPC::P84PFS.PSEL = sel;
					PORT8::PMR.B4 = ena;
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


		static bool mtu7_(channel ch, bool ena, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b000001 : 0;
			switch(ch) {
			///< PA2 (112)  MTIOC7A
			///< P67 (120)  MTIOC7C
			///< P66 (122)  MTIOC7D
			case channel::A:
				switch(opt) {
				case option::FIRST:
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = sel;
					PORTA::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case channel::C:
				switch(opt) {
				case option::FIRST:
//					PORT6::PMR.B7 = 0;
//					MPC::P67PFS.PSEL = sel;
//					PORT6::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case channel::D:
				switch(opt) {
				case option::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;
					PORT2::PMR.B1 = ena;
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


		static bool mtu8_(channel ch, bool ena, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b000001 : 0;
			switch(ch) {
			///< PD4 (148)  MTIOC8B
			///< PD3 (150)  MTIOC8D
			case channel::B:
				switch(opt) {
				case option::FIRST:
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;
					PORTD::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case channel::D:
				switch(opt) {
				case option::FIRST:
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = sel;
					PORTD::PMR.B3 = ena;
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
		static bool turn(peripheral per, channel ch, bool ena = true, option opt = option::FIRST) noexcept
		{
			if(opt == option::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = true;
			switch(per) {
			case peripheral::MTU0:
				ret = mtu0_(ch, ena, opt);
				break;
			case peripheral::MTU1:
				ret = mtu1_(ch, ena, opt);
				break;
			case peripheral::MTU2:
				ret = mtu2_(ch, ena, opt);
				break;
			case peripheral::MTU3:
				ret = mtu3_(ch, ena, opt);
				break;
			case peripheral::MTU4:
				ret = mtu4_(ch, ena, opt);
				break;
			case peripheral::MTU5:
				ret = mtu5_(ch, ena, opt);
				break;
			case peripheral::MTU6:
				ret = mtu6_(ch, ena, opt);
				break;
			case peripheral::MTU7:
				ret = mtu7_(ch, ena, opt);
				break;
			case peripheral::MTU8:
				ret = mtu8_(ch, ena, opt);
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
			bool ret = true;

			return ret;
		}
	};
}

