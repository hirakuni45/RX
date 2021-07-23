#pragma once
//=====================================================================//
/*!	@file
	@brief	RX72N グループ・ポート・マッピング (MTU) @n
			・MTU 型に従って、タイマー用ポートを設定 @n
			MTU0, MTU1, MTU2, MTU3, MTU4, MTU5, MTU6, MTU7, MTU8 @n
			ポート候補は、MPC の解説順番（ソートされた）による @n
			※候補のポリシーが変わった為「候補型」を変更する。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2021 Kunihito Hiramatsu @n
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

		static bool mtu0_(CHANNEL ch, bool ena, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b000001 : 0;
			switch(ch) {
			/// MTIOC0A (入出力)
			///      224  176  144  100
			/// P34    ○   27   25   16
			/// PB3    ○   98   82   57
			case CHANNEL::A:
				switch(order) {
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
			/// MTIOC0B (入出力)
			///      224  176  144  100
			/// P13    ○   52   44   33
			/// P15    ○   50   42   31
			/// PA1    ○  114   96   69
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;
					PORT1::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;
					PORT1::PMR.B5 = ena;
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
			/// MTIOC0C (入出力)
			///      224  176  144  100
			/// P32    ○   29   27   18
			/// PB1    ○  100   84   59
			case CHANNEL::C:
				switch(order) {
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
			/// MTIOC0D (入出力)
			///       224 176 144 100
			/// P33     ○  28  26  17
			/// PA3     ○ 110  94  67
			case CHANNEL::D:
				switch(order) {
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


		static bool mtu1_(CHANNEL ch, bool ena, ORDER order) noexcept
		{
			bool ret = true;
			switch(ch) {
			/// MTIOC1A (入出力)
			///      224  176  144  100
			/// P20    ○   45   37   28
			/// PE4'   ○  131  107   74
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = ena ? 0b000001 : 0;
					PORT2::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = ena ? 0b000010 : 0;
					PORTE::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// MTIOC1B (入出力)
			///       224 176 144 100
			/// P21     ○  44  36  27
			/// PB5'    ○  96  80  55
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = ena ? 0b000001 : 0;
					PORT2::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = ena ? 0b000010 : 0;
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


		static bool mtu2_(CHANNEL ch, bool ena, ORDER order) noexcept
		{
			bool ret = true;
			switch(ch) {
			/// MTIOC2A (入出力)
			///      224  176  144  100
			/// P26    ○   37   31   22
			/// PB5    ○   96   80   55
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					PORT2::PMR.B6 = 0;
					MPC::P26PFS.PSEL = ena ? 0b000001 : 0;
					PORT2::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = ena ? 0b000001 : 0;
					PORTB::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// MTIOC2B (入出力)
			///      224  176  144  100
			/// P27    ○   36   30   21
			/// PE5'   ○  130  106   73
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					PORT2::PMR.B7 = 0;
					MPC::P27PFS.PSEL = ena ? 0b000001 : 0;
					PORT2::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = ena ? 0b000010 : 0;
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


		static bool mtu3_(CHANNEL ch, bool ena, ORDER order) noexcept
		{
			bool ret = true;
			switch(ch) {
			/// MTIOC3A (入出力)
			///      224  176  144  100
			/// P14    ○   51   43   32
			/// P17    ○   46   38   29
			/// PC1    ○   89   73   51
			/// PC7    ○   76   60   45
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = ena ? 0b000001 : 0;
					PORT1::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = ena ? 0b000001 : 0;
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = ena ? 0b000001 : 0;
					PORTC::PMR.B1 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = ena ? 0b000001 : 0;
					PORTC::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// MTIOC3B (入出力)
			///      224  176  144  100
			/// P17'   ○   46   38   29
			/// P22    ○   43   35   26
			/// P80    ○   81   65    x
			/// PB7    ○   94   78   53
			/// PC5    ○   78   62   47
			/// PE1''  ○  134  110   77
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = ena ? 0b000010 : 0;
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = ena ? 0b000001 : 0;
					PORT2::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORT8::PMR.B0 = 0;
					MPC::P80PFS.PSEL = ena ? 0b000001 : 0;
					PORT8::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = ena ? 0b000001 : 0;
					PORTB::PMR.B7 = ena;
					break;
				case ORDER::FIFTH:
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = ena ? 0b000001 : 0;
					PORTC::PMR.B5 = ena;
					break;
				case ORDER::SIXTH:
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = ena ? 0b001000 : 0;
					PORTE::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// MTIOC3C (入出力)
			///      224  176  144  100
			/// P16    ○   48   40   30
			/// P56    ○   64   50    x
			/// PC0    ○   91   75   52
			/// PC6    ○   77   61   46
			/// PJ3    ○   13   13    4
			case CHANNEL::C:
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = ena ? 0b000001 : 0;
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT5::PMR.B6 = 0;
					MPC::P56PFS.PSEL = ena ? 0b000001 : 0;
					PORT5::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B0 = 0;
					MPC::PC0PFS.PSEL = ena ? 0b000001 : 0;
					PORTC::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = ena ? 0b000001 : 0;
					PORTC::PMR.B6 = ena;
					break;
				case ORDER::FIFTH:
					PORTJ::PMR.B3 = 0;
					MPC::PJ3PFS.PSEL = ena ? 0b000001 : 0;
					PORTJ::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// MTIOC3D (入出力)
			///      224  176  144  100
			/// P16    ○   48   40   30
			/// P23    ○   42   34   25
			/// P81    ○   80   64    x
			/// PB6    ○   95   79   54
			/// PC4    ○   82   66   48
			/// PE0    ○  135  111   78
			case CHANNEL::D:
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = ena ? 0b000010 : 0;
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = ena ? 0b000001 : 0;
					PORT2::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORT8::PMR.B1 = 0;
					MPC::P81PFS.PSEL = ena ? 0b000001 : 0;
					PORT8::PMR.B1 = ena;
					break;
				case ORDER::FOURTH:
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = ena ? 0b000001 : 0;
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::FIFTH:
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = ena ? 0b000001 : 0;
					PORTC::PMR.B4 = ena;
					break;
				case ORDER::SIXTH:
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = ena ? 0b001000 : 0;
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


		static bool mtu4_(CHANNEL ch, bool ena, ORDER order) noexcept
		{
			bool ret = true;
			switch(ch) {
			/// MTIOC4A (入出力)
			///      224  176  144  100
			/// P21    ○   44   36   27
			/// P24    ○   40   33   24
			/// P82    ○   79   63    x
			/// PA0    ○  118   97   70
			/// PB3    ○   98   82   57
			/// PE2    ○  133  109   76
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = ena ? 0b001000 : 0;
					PORT2::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = ena ? 0b000001 : 0;
					PORT2::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORT8::PMR.B2 = 0;
					MPC::P82PFS.PSEL = ena ? 0b000001 : 0;
					PORT8::PMR.B2 = ena;
					break;
				case ORDER::FOURTH:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = ena ? 0b000001 : 0;
					PORTA::PMR.B0 = ena;
					break;
				case ORDER::FIFTH:
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = ena ? 0b000010 : 0;
					PORTB::PMR.B3 = ena;
					break;
				case ORDER::SIXTH:
					PORTE::PMR.B2 = 0;
					MPC::PE2PFS.PSEL = ena ? 0b000001 : 0;
					PORTE::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// MTIOC4B (入出力)
			///      224  176  144  100
			/// P17    ○   46   38   29
			/// P30    ○   33   29   20
			/// P54    ○   66   52   40
			/// PC2    ○   86   70   50
			/// PD1    ○  156  125   85
			/// PE3    ○  132  108   75
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = ena ? 0b001000 : 0;
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = ena ? 0b000001 : 0;
					PORT3::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
					PORT5::PMR.B4 = 0;
					MPC::P54PFS.PSEL = ena ? 0b000001 : 0;
					PORT5::PMR.B4 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = ena ? 0b000001 : 0;
					PORTC::PMR.B2 = ena;
					break;
				case ORDER::FIFTH:
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = ena ? 0b000001 : 0;
					PORTD::PMR.B1 = ena;
					break;
				case ORDER::SIXTH:
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = ena ? 0b000001 : 0;
					PORTE::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// MTIOC4C (入出力)
			///      224  176  144  100
			/// P25    ○   38   32   23
			/// P83    ○   74   58    x
			/// P87    ○   47   39    x
			/// PB1    ○  100   84   59
			/// PE1    ○  134  110   77
			/// PE5    ○  130  106   73
			case CHANNEL::C:
				switch(order) {
				case ORDER::FIRST:
					PORT2::PMR.B5 = 0;
					MPC::P25PFS.PSEL = ena ? 0b000001 : 0;
					PORT2::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B3 = 0;
					MPC::P83PFS.PSEL = ena ? 0b000001 : 0;
					PORT8::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORT8::PMR.B7 = 0;
					MPC::P87PFS.PSEL = ena ? 0b001000 : 0;
					PORT8::PMR.B7 = ena;
					break;
				case ORDER::FOURTH:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = ena ? 0b000010 : 0;
					PORTB::PMR.B1 = ena;
					break;
				case ORDER::FIFTH:
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = ena ? 0b000001 : 0;
					PORTE::PMR.B1 = ena;
					break;
				case ORDER::SIXTH:
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = ena ? 0b000001 : 0;
					PORTE::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// MTIOC4D (入出力)
			///      224  176  144  100
			/// P31    ○   32   28   19
			/// P55    ○   65   51   39
			/// P86    ○   49   41    x
			/// PC3    ○   83   67   49
			/// PD2    ○  154  124   84
			/// PE4    ○  131  107   74
			case CHANNEL::D:
				switch(order) {
				case ORDER::FIRST:
					PORT3::PMR.B1 = 0;
					MPC::P31PFS.PSEL = ena ? 0b000001 : 0;
					PORT3::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT5::PMR.B5 = 0;
					MPC::P55PFS.PSEL = ena ? 0b000001 : 0;
					PORT5::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					PORT8::PMR.B6 = 0;
					MPC::P86PFS.PSEL = ena ? 0b001000 : 0;
					PORT8::PMR.B6 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B3 = 0;
					MPC::PC3PFS.PSEL = ena ? 0b000001 : 0;
					PORTC::PMR.B3 = ena;
					break;
				case ORDER::FIFTH:
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = ena ? 0b000001 : 0;
					PORTD::PMR.B2 = ena;
					break;
				case ORDER::SIXTH:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = ena ? 0b000001 : 0;
					PORTE::PMR.B4 = ena;
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


		static bool mtu5_(CHANNEL ch, bool ena, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b000001 : 0;
			switch(ch) {
			/// MTIOC5U (入出力)
			///      224  176  144  100
			/// P12    ○   53   45    x
			/// PA4    ○  109   92   66
			/// PD7    ○  143  119   79
			case CHANNEL::U:
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B2 = 0;
					MPC::P12PFS.PSEL = sel;
					PORT1::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;
					PORTD::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// MTIOC5V (入出力)
			///      224  176  144  100
			/// P11    ○   67    x    x
			/// PA6    ○  107   89   64
			/// PD6    ○  145  120   80
			case CHANNEL::V:
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = sel;
					PORT1::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = sel;
					PORTA::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;
					PORTD::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// MTIOC5W (入出力)
			///      224  176  144  100
			/// P10    ○   68    x    x
			/// PB0    ○  104   87   61
			/// PD5    ○  147  121   81
			case CHANNEL::W:
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B0 = 0;
					MPC::P10PFS.PSEL = sel;
					PORT1::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;
					PORTB::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
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


		static bool mtu6_(CHANNEL ch, bool ena, ORDER order) noexcept
		{
			bool ret = true;
			switch(ch) {
			/// MTIOC6A (入出力)
			///      224  176  144  100
			/// PE7    ○  125  101   71
			/// PJ1    ○   59    x    x
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					PORTE::PMR.B7 = 0;
					MPC::PE7PFS.PSEL = ena ? 0b001000 : 0;
					PORTE::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTJ::PMR.B1 = 0;
					MPC::PJ1PFS.PSEL = ena ? 0b000001 : 0;
					PORTJ::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// MTIOC6B (入出力)
			///      224  176  144  100
			/// PA5    ○  108   90   65
			/// PJ0    ○   60    x    x
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = ena ? 0b001000 : 0;
					PORTA::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORTJ::PMR.B0 = 0;
					MPC::PJ0PFS.PSEL = ena ? 0b000001 : 0;
					PORTJ::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// MTIOC6C (入出力)
			///      224  176  144  100
			/// P85    ○   61    x    x
			/// PE6    ○  126  102   72
			case CHANNEL::C:
				switch(order) {
				case ORDER::FIRST:
					PORT8::PMR.B5 = 0;
					MPC::P85PFS.PSEL = ena ? 0b000001 : 0;
					PORT8::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B6 = 0;
					MPC::PE6PFS.PSEL = ena ? 0b001000 : 0;
					PORTE::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// MTIOC6D (入出力)
			///      224  176  144  100
			/// P84    ○   62    x    x
			/// PA0    ○  118   97   70
			case CHANNEL::D:
				switch(order) {
				case ORDER::FIRST:
					PORT8::PMR.B4 = 0;
					MPC::P84PFS.PSEL = ena ? 0b000001 : 0;
					PORT8::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = ena ? 0b001000 : 0;
					PORTA::PMR.B0 = ena;
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


		static bool mtu7_(CHANNEL ch, bool ena, ORDER order) noexcept
		{
			bool ret = true;
			switch(ch) {
			/// MTIOC7A (入出力)
			///      224  176  144  100
			/// PA2    ○  112   95   68
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = ena ? 0b001000 : 0;
					PORTA::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// MTIOC7B (入出力)
			///      224  176  144  100
			/// PA1    ○  114   96   69
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = ena ? 0b001000 : 0;
					PORTA::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// MTIOC7C (入出力)
			///      224  176  144  100
			/// P67    ○  120   98    x
			case CHANNEL::C:
				switch(order) {
				case ORDER::FIRST:
					PORT6::PMR.B7 = 0;
					MPC::P67PFS.PSEL = ena ? 0b001000 : 0;
					PORT6::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// MTIOC7D (入出力)
			///      224  176  144  100
			/// P66    ○  122   99    x
			case CHANNEL::D:
				switch(order) {
				case ORDER::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = ena ? 0b001000 : 0;
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


		static bool mtu8_(CHANNEL ch, bool ena, ORDER order) noexcept
		{
			bool ret = true;
			switch(ch) {
			/// MTIOC8A (入出力)
			///      224  176  144  100
			/// PD6    ○  145  120   80
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = ena ? 0b001000 : 0;
					PORTD::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// MTIOC8B (入出力)
			///      224  176  144  100
			/// PD4    ○  148  122   82
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = ena ? 0b001000 : 0;
					PORTD::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// MTIOC8C (入出力)
			///      224  176  144  100
			/// PD5    ○  147  121   81
			case CHANNEL::C:
				switch(order) {
				case ORDER::FIRST:
					PORTD::PMR.B5 = 0;
					MPC::PD5PFS.PSEL = ena ? 0b001000 : 0;
					PORTD::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// MTIOC8D (入出力)
			///      224  176  144  100
			/// PD3    ○  150  123   83
			case CHANNEL::D:
				switch(order) {
				case ORDER::FIRST:
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = ena ? 0b001000 : 0;
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
			@param[in]	order	候補を選択する場合
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(peripheral per, CHANNEL ch, bool ena = true, ORDER order = ORDER::FIRST) noexcept
		{
			if(order == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = true;
			switch(per) {
			case peripheral::MTU0:
				ret = mtu0_(ch, ena, order);
				break;
			case peripheral::MTU1:
				ret = mtu1_(ch, ena, order);
				break;
			case peripheral::MTU2:
				ret = mtu2_(ch, ena, order);
				break;
			case peripheral::MTU3:
				ret = mtu3_(ch, ena, order);
				break;
			case peripheral::MTU4:
				ret = mtu4_(ch, ena, order);
				break;
			case peripheral::MTU5:
				ret = mtu5_(ch, ena, order);
				break;
			case peripheral::MTU6:
				ret = mtu6_(ch, ena, order);
				break;
			case peripheral::MTU7:
				ret = mtu7_(ch, ena, order);
				break;
			case peripheral::MTU8:
				ret = mtu8_(ch, ena, order);
				break;

			default:
				ret = false;
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}


// under constructions!
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
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			uint8_t sel = ena ? 0b000010 : 0;
			bool ret = true;
			switch(grp) {
			/// P15 ( 50)  MTIOC0B / MTCLKB
			/// PA1 (114)  MTIOC0B / MTCLKC / MTIOC7B
			/// PA3 (110)  MTIOC0D / MTCLKD
			case GROUP::AREA0:
				switch(ch) {
				case CHANNEL::CLK_B:
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;
					PORT1::PMR.B5 = ena;
					break;
				case CHANNEL::CLK_C:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;
					PORTA::PMR.B1 = ena;
					break;
				case CHANNEL::CLK_D:
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
			case GROUP::AREA1:
				switch(ch) {
				case CHANNEL::CLK_A:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;
					PORT1::PMR.B4 = ena;
					break;
				case CHANNEL::CLK_B:
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;
					PORTC::PMR.B7 = ena;
					break;
				case CHANNEL::CLK_C:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;
					PORT2::PMR.B2 = ena;
					break;
				case CHANNEL::CLK_D:
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
			case GROUP::AREA2:
				switch(ch) {
				case CHANNEL::CLK_A:
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;
					PORTC::PMR.B6 = ena;
					break;
				case CHANNEL::CLK_C:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;
					PORT2::PMR.B3 = ena;
					break;
				case CHANNEL::CLK_D:
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
			case GROUP::AREA3:
				switch(ch) {
				case CHANNEL::CLK_A:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;
					PORT2::PMR.B4 = ena;
					break;
				case CHANNEL::CLK_B:
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
			case GROUP::AREA4:
				switch(ch) {
				case CHANNEL::CLK_A:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B4 = ena;
					break;
				case CHANNEL::CLK_B:
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
			case GROUP::AREA5:
				switch(ch) {
				case CHANNEL::CLK_A:
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

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
