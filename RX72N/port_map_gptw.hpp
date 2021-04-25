#pragma once
//=====================================================================//
/*!	@file
	@brief	RX72N グループ・ポート・マッピング (GPTW0 - GPTW3) 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX72N/peripheral.hpp"
#include "RX600/port.hpp"
#include "RX600/mpc.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPTW ポート・マッピング
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
			@brief  GPTW チャネル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class channel : uint8_t {
			A,		///< GPTWx A (GTIOCxA)
			B,		///< GPTWx B (GTIOCxB)
		};

    private:
		static bool gptw0_(channel ch, bool ena, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b011110 : 0;
			switch(ch) {
            /// GTIOC0A (入出力)
            ///       224 176 144 100
            /// P23     ○   ○   ○   ○
            /// P83     ○   ○   ○   ×
            /// PA5     ○   ○   ○   ○
            /// PD3     ○   ○   ○   ○
            /// PE5     ○   ○   ○   ○
            /// PH6     ○   ×   ×   ×
			case channel::A:
				switch(opt) {
				case option::FIRST:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;
					PORT2::PMR.B3 = ena;
					break;
				case option::SECOND:
					PORT8::PMR.B3 = 0;
					MPC::P83PFS.PSEL = sel;
					PORT8::PMR.B3 = ena;
					break;
				case option::THIRD:
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;
					PORTA::PMR.B5 = ena;
					break;
				case option::FOURTH:
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = sel;
					PORTD::PMR.B3 = ena;
					break;
				case option::FIFTH:
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = sel;
					PORTE::PMR.B5 = ena;
					break;
#if 0
				case option::SIXTH:
					PORTH::PMR.B6 = 0;
					MPC::PH6PFS.PSEL = sel;
					PORTH::PMR.B6 = ena;
					break;
#endif
				default:
					ret = false;
					break;
				}
				break;
            /// GTIOC0B (入出力)
            ///       224 176 144 100
            /// P17     ○   ○   ○   ○
            /// P81     ○   ○   ○   ×
            /// PA0     ○   ○   ○   ○
            /// PD2     ○   ○   ○   ○
            /// PE2     ○   ○   ○   ○
            /// PH7     ○   ×   ×   ×
			case channel::B:
				switch(opt) {
				case option::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B7 = ena;
					break;
				case option::SECOND:
					PORT8::PMR.B1 = 0;
					MPC::P81PFS.PSEL = sel;
					PORT8::PMR.B1 = ena;
					break;
				case option::THIRD:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;
					PORTA::PMR.B0 = ena;
					break;
				case option::FOURTH:
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;
					PORTD::PMR.B2 = ena;
					break;
				case option::FIFTH:
					PORTE::PMR.B2 = 0;
					MPC::PE2PFS.PSEL = sel;
					PORTE::PMR.B2 = ena;
					break;
#if 0
				case option::SIXTH:
					PORTH::PMR.B6 = 0;
					MPC::PH6PFS.PSEL = sel;
					PORTH::PMR.B6 = ena;
					break;
#endif
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

		static bool gptw1_(channel ch, bool ena, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b011110 : 0;
			switch(ch) {
            /// GTIOC1A (入出力)
            ///       224 176 144 100
            /// P22     ○   ○   ○   ○
            /// PA2     ○   ○   ○   ○
            /// PC5     ○   ○   ○   ○
            /// PD1     ○   ○   ○   ○
            /// PE4     ○   ○   ○   ○
            /// PK6     ○   ×   ×   ×
			case channel::A:
				switch(opt) {
				case option::FIRST:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;
					PORT2::PMR.B2 = ena;
					break;
				case option::SECOND:
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = sel;
					PORTA::PMR.B2 = ena;
					break;
				case option::THIRD:
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;
					PORTC::PMR.B5 = ena;
					break;
				case option::FOURTH:
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;
					PORTD::PMR.B1 = ena;
					break;
				case option::FIFTH:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = sel;
					PORTE::PMR.B4 = ena;
					break;
#if 0
				case option::SIXTH:
					PORTK::PMR.B6 = 0;
					MPC::PK6PFS.PSEL = sel;
					PORTK::PMR.B6 = ena;
					break;
#endif
				default:
					ret = false;
					break;
				}
				break;
            /// GTIOC1B (入出力)
            ///       224 176 144 100
            /// P67     ○   ○   ○   ×
            /// P87     ○   ○   ○   ×
            /// PC3     ○   ○   ○   ○
            /// PD0     ○   ○   ○   ○
            /// PE1     ○   ○   ○   ○
            /// PK7     ○   ×   ×   ×
			case channel::B:
				switch(opt) {
				case option::FIRST:
					PORT6::PMR.B7 = 0;
					MPC::P67PFS.PSEL = sel;
					PORT6::PMR.B7 = ena;
					break;
				case option::SECOND:
					PORT8::PMR.B7 = 0;
					MPC::P87PFS.PSEL = sel;
					PORT8::PMR.B7 = ena;
					break;
				case option::THIRD:
					PORTC::PMR.B3 = 0;
					MPC::PC3PFS.PSEL = sel;
					PORTC::PMR.B3 = ena;
					break;
				case option::FOURTH:
					PORTD::PMR.B0 = 0;
					MPC::PD0PFS.PSEL = sel;
					PORTD::PMR.B0 = ena;
					break;
				case option::FIFTH:
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = sel;
					PORTE::PMR.B1 = ena;
					break;
#if 0
				case option::SIXTH:
					PORTK::PMR.B7 = 0;
					MPC::PK7PFS.PSEL = sel;
					PORTK::PMR.B7 = ena;
					break;
#endif
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


		static bool gptw2_(channel ch, bool ena, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b011110 : 0;
			switch(ch) {
            /// GTIOC2A (入出力)
            ///       224 176 144 100
            /// P21     ○   ○   ○   ○
            /// P82     ○   ○   ○   ×
            /// PA1     ○   ○   ○   ○
            /// PE3     ○   ○   ○   ○
            /// PL6     ○   ×   ×   ×
			case channel::A:
				switch(opt) {
				case option::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;
					PORT2::PMR.B1 = ena;
					break;
				case option::SECOND:
					PORT8::PMR.B2 = 0;
					MPC::P82PFS.PSEL = sel;
					PORT8::PMR.B2 = ena;
					break;
				case option::THIRD:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;
					PORTA::PMR.B1 = ena;
					break;
				case option::FOURTH:
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = sel;
					PORTE::PMR.B3 = ena;
					break;
#if 0
				case option::FIFTH:
					PORTL::PMR.B6 = 0;
					MPC::PL6PFS.PSEL = sel;
					PORTL::PMR.B6 = ena;
					break;
#endif
				default:
					ret = false;
					break;
				}
				break;
            /// GTIOC2B (入出力)
            ///       224 176 144 100
            /// P66     ○   ○   ○   ×
            /// P86     ○   ○   ○   ×
            /// PC2     ○   ○   ○   ○
            /// PE0     ○   ○   ○   ○
            /// PL7     ○   ×   ×   ×
			case channel::B:
				switch(opt) {
				case option::FIRST:
					PORT6::PMR.B6 = 0;
					MPC::P66PFS.PSEL = sel;
					PORT6::PMR.B6 = ena;
					break;
				case option::SECOND:
					PORT8::PMR.B6 = 0;
					MPC::P86PFS.PSEL = sel;
					PORT8::PMR.B6 = ena;
					break;
				case option::THIRD:
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = sel;
					PORTC::PMR.B2 = ena;
					break;
				case option::FOURTH:
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = sel;
					PORTE::PMR.B0 = ena;
					break;
#if 0
				case option::FIFTH:
					PORTL::PMR.B7 = 0;
					MPC::PL7PFS.PSEL = sel;
					PORTL::PMR.B7 = ena;
					break;
#endif
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


		static bool gptw3_(channel ch, bool ena, option opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b011110 : 0;
			switch(ch) {
            /// GTIOC3A (入出力)
            ///       224 176 144 100
            /// PC7     ○   ○   ○   ○
            /// PE7     ○   ○   ○   ○
            /// PM6     ○   ×   ×   ×
			case channel::A:
				switch(opt) {
				case option::FIRST:
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;
					PORTC::PMR.B7 = ena;
					break;
				case option::SECOND:
					PORTE::PMR.B7 = 0;
					MPC::PE7PFS.PSEL = sel;
					PORTE::PMR.B7 = ena;
					break;
#if 0
				case option::THIRD:
					PORTM::PMR.B6 = 0;
					MPC::PM6PFS.PSEL = sel;
					PORTM::PMR.B6 = ena;
					break;
#endif
				default:
					ret = false;
					break;
				}
				break;
            /// GTIOC3B (入出力)
            ///       224 176 144 100
            /// PC6     ○   ○   ○   ○
            /// PE6     ○   ○   ○   ○
            /// PM7     ○   ×   ×   ×
			case channel::B:
				switch(opt) {
				case option::FIRST:
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;
					PORTC::PMR.B6 = ena;
					break;
				case option::SECOND:
					PORTE::PMR.B6 = 0;
					MPC::PE6PFS.PSEL = sel;
					PORTE::PMR.B6 = ena;
					break;
#if 0
				case option::THIRD:
					PORTM::PMR.B7 = 0;
					MPC::PM7PFS.PSEL = sel;
					PORTM::PMR.B7 = ena;
					break;
#endif
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
			@brief  GPTW[0-3]、チャネル別ポート切り替え
			@param[in]	per	周辺機器タイプ
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合「false」
			@param[in]	neg	反転入出力の場合「true」(RX72N では neg は無効)
			@param[in]	opt	候補を選択する場合
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(peripheral per, channel ch, bool ena = true, bool neg = false, option opt = option::FIRST) noexcept
		{
            // RX72N 系は「neg」が無い
            if(neg) return false;

			if(opt == option::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			switch(per) {
			case peripheral::GPTW0:
				ret = gptw0_(ch, ena, opt);
				break;
			case peripheral::GPTW1:
				ret = gptw1_(ch, ena, opt);
				break;
			case peripheral::GPTW2:
				ret = gptw2_(ch, ena, opt);
				break;
			case peripheral::GPTW3:
				ret = gptw3_(ch, ena, opt);
				break;
			default:
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}
    };
}