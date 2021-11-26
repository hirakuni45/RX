#pragma once
//=====================================================================//
/*!	@file
	@brief	RX66T グループ・ポート・マッピング (MTU) @n
			・MTU 型に従って、タイマー用ポートを設定 @n
			MTU0, MTU1, MTU2, MTU3, MTU4, MTU5, MTU6, MTU7, MTU8, MTU9
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX66T/peripheral.hpp"
#include "RX600/port.hpp"
#include "RX600/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_mtu : public port_map_order {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマー系・チャネル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CHANNEL : uint8_t {
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
		enum class GROUP : uint8_t {
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
		static bool mtu0_(CHANNEL ch, bool ena, bool neg, ORDER opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b000011 : 0b000001) : 0;
			switch(ch) {
			///< P31 ( )  MTIOC0A[#]
			///< PB3 ( )  MTIOC0A[#]
			case CHANNEL::A:
				switch(opt) {
				case ORDER::FIRST:
					PORT3::PMR.B1 = 0;
					MPC::P31PFS.PSEL = sel;
					PORT3::PMR.B1 = ena;
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
			///< P30 ( )  MTIOC0B[#]
			///< PB2 ( )  MTIOC0B[#]
			///< PC0 ( )  MTIOC0B[#]
			case CHANNEL::B:
				switch(opt) {
				case ORDER::FIRST:
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = sel;
					PORT3::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B2 = 0;
					MPC::PB2PFS.PSEL = sel;
					PORTB::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B0 = 0;
					MPC::PC0PFS.PSEL = sel;
					PORTC::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< P27 ( )  MTIOC0C[#]
			///< PB1 ( )  MTIOC0C[#]
			///< PC1 ( )  MTIOC0C[#]
			case CHANNEL::C:
				switch(opt) {
				case ORDER::FIRST:
					PORT2::PMR.B7 = 0;
					MPC::P27PFS.PSEL = sel;
					PORT2::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;
					PORTB::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = sel;
					PORTC::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< PB0 ( )  MTIOC0D[#]
			///< PC2 ( )  MTIOC0D[#]
			case CHANNEL::D:
				switch(opt) {
				case ORDER::FIRST:
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;
					PORTB::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = sel;
					PORTC::PMR.B2 = ena;
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


		static bool mtu1_(CHANNEL ch, bool ena, bool neg, ORDER opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b000011 : 0b000001) : 0;
			switch(ch) {
			///< P27 ( )  MTIOC1A[#]
			///< PA5 ( )  MTIOC1A[#]
			///< PC6 ( )  MTIOC1A[#]
			case CHANNEL::A:
				switch(opt) {
				case ORDER::FIRST:
					PORT2::PMR.B7 = 0;
					MPC::P27PFS.PSEL = sel;
					PORT2::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;
					PORTA::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;
					PORTC::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< PA4 ( )  MTIOC1B[#]
			///< PC5 ( )  MTIOC1B[#]
			case CHANNEL::B:
				switch(opt) {
				case ORDER::FIRST:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;
					PORTC::PMR.B5 = ena;
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


		static bool mtu2_(CHANNEL ch, bool ena, bool neg, ORDER opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b000011 : 0b000001) : 0;
			switch(ch) {
			///< P35 ( )  MTIOC2A[#]
			///< PA3 ( )  MTIOC2A[#]
			case CHANNEL::A:
				switch(opt) {
				case ORDER::FIRST:
					PORT3::PMR.B5 = 0;
					MPC::P35PFS.PSEL = sel;
					PORT3::PMR.B5 = ena;
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
			///< P34 ( )  MTIOC2A[#]
			///< PA2 ( )  MTIOC2A[#]
			case CHANNEL::B:
				switch(opt) {
				case ORDER::FIRST:
					PORT3::PMR.B4 = 0;
					MPC::P34PFS.PSEL = sel;
					PORT3::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = sel;
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


		static bool mtu3_(CHANNEL ch, bool ena, bool neg, ORDER opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b000011 : 0b000001) : 0;
			switch(ch) {
			///< P11 ( )  MTIOC3A[#]
			///< P33 ( )  MTIOC3A[#]
			case CHANNEL::A:
				switch(opt) {
				case ORDER::FIRST:
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = sel;
					PORT1::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;
					PORT3::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< P12 ( )  MTIOC3B[#]
			///< P71 ( )  MTIOC3B[#]
			case CHANNEL::B:
				switch(opt) {
				case ORDER::FIRST:
					PORT1::PMR.B2 = 0;
					MPC::P12PFS.PSEL = sel;
					PORT1::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B1 = 0;
					MPC::P71PFS.PSEL = sel;
					PORT7::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< P32 ( )  MTIOC3C[#]
			case CHANNEL::C:
				switch(opt) {
				case ORDER::FIRST:
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;
					PORT3::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
				default:
					ret = false;
					break;
				}
				break;
			///< P15 ( )  MTIOC3D[#]
			///< P74 ( )  MTIOC3D[#]
			case CHANNEL::D:
				switch(opt) {
				case ORDER::FIRST:
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;
					PORT1::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B4 = 0;
					MPC::P74PFS.PSEL = sel;
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


		static bool mtu4_(CHANNEL ch, bool ena, bool neg, ORDER opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b000011 : 0b000001) : 0;
			switch(ch) {
			///< P13 ( )  MTIOC4A[#]
			///< P72 ( )  MTIOC4A[#]
			case CHANNEL::A:
				switch(opt) {
				case ORDER::FIRST:
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;
					PORT1::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B2 = 0;
					MPC::P72PFS.PSEL = sel;
					PORT7::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< P14 ( )  MTIOC4B[#]
			///< P73 ( )  MTIOC4B[#]
			case CHANNEL::B:
				switch(opt) {
				case ORDER::FIRST:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;
					PORT1::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B3 = 0;
					MPC::P73PFS.PSEL = sel;
					PORT7::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< P16 ( )  MTIOC4C[#]
			///< P75 ( )  MTIOC4C[#]
			case CHANNEL::C:
				switch(opt) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B5 = 0;
					MPC::P75PFS.PSEL = sel;
					PORT7::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< P17 ( )  MTIOC4D[#]
			///< P76 ( )  MTIOC4D[#]
			case CHANNEL::D:
				switch(opt) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;
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


		static bool mtu5_(CHANNEL ch, bool ena, bool neg, ORDER opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b000011 : 0b000001) : 0;
			switch(ch) {
			///< P24 ( )  MTIC5U[#]
			///< P82 ( )  MTIC5U[#]
			case CHANNEL::U:
				switch(opt) {
				case ORDER::FIRST:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;
					PORT2::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B2 = 0;
					MPC::P82PFS.PSEL = sel;
					PORT8::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< P23 ( )  MTIC5V[#]
			///< P81 ( )  MTIC5V[#]
			case CHANNEL::V:
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
				default:
					ret = false;
					break;
				}
				break;
			///< P22 ( )  MTIC5W[#]
			///< P80 ( )  MTIC5W[#]
			case CHANNEL::W:
				switch(opt) {
				case ORDER::FIRST:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;
					PORT2::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B0 = 0;
					MPC::P80PFS.PSEL = sel;
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


		static bool mtu6_(CHANNEL ch, bool ena, bool neg, ORDER opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b000011 : 0b000001) : 0;
			switch(ch) {
			///< PA1 ( )  MTIOC6A[#]
			case CHANNEL::A:
				switch(opt) {
				case ORDER::FIRST:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;
					PORTA::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< P95 ( )  MTIOC6B[#]
			case CHANNEL::B:
				switch(opt) {
				case ORDER::FIRST:
					PORT9::PMR.B5 = 0;
					MPC::P95PFS.PSEL = sel;
					PORT9::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< PA0 ( )  MTIOC6C[#]
			case CHANNEL::C:
				switch(opt) {
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
			///< P92 ( )  MTIOC6D[#]
			case CHANNEL::D:
				switch(opt) {
				case ORDER::FIRST:
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


		static bool mtu7_(CHANNEL ch, bool ena, bool neg, ORDER opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b000011 : 0b000001) : 0;
			switch(ch) {
			///< P94 ( )  MTIOC7A[#]
			case CHANNEL::A:
				switch(opt) {
				case ORDER::FIRST:
					PORT9::PMR.B4 = 0;
					MPC::P94PFS.PSEL = sel;
					PORT9::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< P93 ( )  MTIOC7B[#]
			case CHANNEL::C:
				switch(opt) {
				case ORDER::FIRST:
					PORT9::PMR.B3 = 0;
					MPC::P93PFS.PSEL = sel;
					PORT9::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< P90 ( )  MTIOC7D[#]
			case CHANNEL::D:
				switch(opt) {
				case ORDER::FIRST:
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


		static bool mtu9_(CHANNEL ch, bool ena, bool neg, ORDER opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b000011 : 0b000001) : 0;
			switch(ch) {
			///< P00 ( )  MTIOC9A[#]
			///< P21 ( )  MTIOC9A[#]
			///< P26 ( )  MTIOC9A[#]
			///< P35 ( )  MTIOC9A[#]
			///< PD7 ( )  MTIOC9A[#]
			case CHANNEL::A:
				switch(opt) {
				case ORDER::FIRST:
					PORT0::PMR.B0 = 0;
					MPC::P00PFS.PSEL = sel;
					PORT0::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;
					PORT2::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					PORT2::PMR.B6 = 0;
					MPC::P26PFS.PSEL = sel;
					PORT2::PMR.B6 = ena;
					break;
				case ORDER::FOURTH:
					PORT3::PMR.B5 = 0;
					MPC::P35PFS.PSEL = ena ? (neg ? 0b000100 : 0b000010) : 0;
					PORT3::PMR.B5 = ena;
					break;
				case ORDER::FIFTH:
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;
					PORTD::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< P22 ( )  MTIOC9B
			///< P10 ( )  MTIOC9B(#)
			///< P34 ( )  MTIOC9B(#)
			///< PC4 ( )  MTIOC9B(#)
			///< PE0 ( )  MTIOC9B(#)
			case CHANNEL::B:
				switch(opt) {
				case ORDER::FIRST:
					if(neg) {
						ret = false;
						break;
					}
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = ena ? 0b001000 : 0;
					PORT2::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORT1::PMR.B0 = 0;
					MPC::P10PFS.PSEL = sel;
					PORT1::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
					PORT3::PMR.B4 = 0;
					MPC::P34PFS.PSEL = ena ? (neg ? 0b000100 : 0b000010) : 0;
					PORT3::PMR.B4 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;
					PORTC::PMR.B4 = ena;
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
			///< P01 ( )  MTIOC9C
			///< P20 ( )  MTIOC9C[#]
			///< P25 ( )  MTIOC9C[#]
			///< PC6 ( )  MTIOC9C[#]
			///< PD6 ( )  MTIOC9C[#]
			case CHANNEL::C:
				switch(opt) {
				case ORDER::FIRST:
					if(neg) {
						ret = false;
						break;
					}
					PORT0::PMR.B1 = 0;
					MPC::P01PFS.PSEL = sel;
					PORT0::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = sel;
					PORT2::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
					PORT2::PMR.B5 = 0;
					MPC::P25PFS.PSEL = sel;
					PORT2::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = ena ? (neg ? 0b000100 : 0b000010) : 0;
					PORTC::PMR.B6 = ena;
					break;
				case ORDER::FIFTH:
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;
					PORTD::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			///< P11 ( )  MTIOC9D
			///< PC3 ( )  MTIOC9D[#]
			///< PC5 ( )  MTIOC9D[#]
			///< PE1 ( )  MTIOC9D[#]
			///< PE5 ( )  MTIOC9D[#]
			case CHANNEL::D:
				switch(opt) {
				case ORDER::FIRST:
					if(neg) {
						ret = false;
						break;
					}
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = ena ? 0b001000 : 0;
					PORT1::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B3 = 0;
					MPC::PC3PFS.PSEL = sel;
					PORTC::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = ena ? (neg ? 0b000100 : 0b000010) : 0;
					PORTC::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = sel;
					PORTE::PMR.B1 = ena;
					break;
				case ORDER::FIFTH:
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

	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマー系、チャネル別ポート切り替え
			@param[in]	per	周辺機器タイプ
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合「false」
			@param[in]	odr	候補選択
			@param[in]	neg	反転入出力の場合「true」
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(peripheral per, CHANNEL ch, bool ena = true, ORDER odr = ORDER::FIRST, bool neg = false) noexcept
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
		static bool turn_clock(GROUP grp, CHANNEL ch, bool ena = true) noexcept
		{
			bool ret = true;

			return ret;
		}
	};
}

