#pragma once
//=========================================================================//
/*!	@file
	@brief	RX66N/RX72N/RX72M グループ・ポート・マッピング (GPTW0 - GPTW3) 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#if defined(SIG_RX66N)
#include "RX66N/peripheral.hpp"
#include "RX66N/port.hpp"
#include "RX66N/mpc.hpp"
#elif defined(SIG_RX72N)
#include "RX72N/peripheral.hpp"
#include "RX72N/port.hpp"
#include "RX72N/mpc.hpp"
#elif defined(SIG_RX72M)
#include "RX72M/peripheral.hpp"
#include "RX72N/port.hpp"
#include "RX72M/mpc.hpp"
#endif
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPTW ポート・マッピング
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_gptw : public port_map_order {

		static bool dsm_0_(ORDER odr, bool ena) noexcept
		{
			/// GTADSM0: (output)
			// P12 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			// PH4 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			// PK4 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			// PL4 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			// PM4 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B2 = 0;
				MPC::P12PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORT1::PMR.B2 = ena;
				break;
			case ORDER::SECOND:
				PORTH::PMR.B4 = 0;
				MPC::PH4PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTH::PMR.B4 = ena;
				break;
			case ORDER::THIRD:
				PORTK::PMR.B4 = 0;
				MPC::PK4PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTK::PMR.B4 = ena;
				break;
			case ORDER::FOURTH:
				PORTL::PMR.B4 = 0;
				MPC::PL4PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTL::PMR.B4 = ena;
				break;
			case ORDER::FIFTH:
				PORTM::PMR.B4 = 0;
				MPC::PM4PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTM::PMR.B4 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool dsm_1_(ORDER odr, bool ena) noexcept
		{
			// GTADSM1:
			// P13 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			// PH5 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			// PK5 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			// PL5 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			// PM5 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B3 = 0;
				MPC::P13PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORT1::PMR.B3 = ena;
				break;
			case ORDER::SECOND:
				PORTH::PMR.B5 = 0;
				MPC::PH5PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTH::PMR.B5 = ena;
				break;
			case ORDER::THIRD:
				PORTK::PMR.B5 = 0;
				MPC::PK5PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTK::PMR.B5 = ena;
				break;
			case ORDER::FOURTH:
				PORTL::PMR.B5 = 0;
				MPC::PL5PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTL::PMR.B5 = ena;
				break;
			case ORDER::FIFTH:
				PORTM::PMR.B5 = 0;
				MPC::PM5PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTM::PMR.B5 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool trg_a_(ORDER odr, bool ena) noexcept
		{
			// GTETRGA:
			// P15 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			// PH0 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			// PK0 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			// PL0 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			// PM0 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B5 = 0;
				MPC::P15PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORT1::PMR.B5 = ena;
				break;
			case ORDER::SECOND:
				PORTH::PMR.B0 = 0;
				MPC::PH0PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTH::PMR.B0 = ena;
				break;
			case ORDER::THIRD:
				PORTK::PMR.B0 = 0;
				MPC::PK0PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTK::PMR.B0 = ena;
				break;
			case ORDER::FOURTH:
				PORTL::PMR.B0 = 0;
				MPC::PL0PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTL::PMR.B0 = ena;
				break;
			case ORDER::FIFTH:
				PORTM::PMR.B0 = 0;
				MPC::PM0PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTM::PMR.B0 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool trg_b_(ORDER odr, bool ena) noexcept
		{
			// GTETRGB:
			// PA6 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			// PH1 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			// PK1 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			// PL1 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			// PM1 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			switch(odr) {
			case ORDER::FIRST:
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTA::PMR.B6 = ena;
				break;
			case ORDER::SECOND:
				PORTH::PMR.B1 = 0;
				MPC::PH1PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTH::PMR.B1 = ena;
				break;
			case ORDER::THIRD:
				PORTK::PMR.B1 = 0;
				MPC::PK1PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTK::PMR.B1 = ena;
				break;
			case ORDER::FOURTH:
				PORTL::PMR.B1 = 0;
				MPC::PL1PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTL::PMR.B1 = ena;
				break;
			case ORDER::FIFTH:
				PORTM::PMR.B1 = 0;
				MPC::PM1PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTM::PMR.B1 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool trg_c_(ORDER odr, bool ena) noexcept
		{
			// GTETRGC:
			// PC4 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			// PH2 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			// PK2 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			// PL2 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			// PM2 (LFQFP100:  ) (LFQFP144:  ) (LFQFP176:  )
			switch(odr) {
			case ORDER::FIRST:
				PORTC::PMR.B4 = 0;
				MPC::PC4PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTC::PMR.B4 = ena;
				break;
			case ORDER::SECOND:
				PORTH::PMR.B2 = 0;
				MPC::PH2PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTH::PMR.B2 = ena;
				break;
			case ORDER::THIRD:
				PORTK::PMR.B2 = 0;
				MPC::PK2PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTK::PMR.B2 = ena;
				break;
			case ORDER::FOURTH:
				PORTL::PMR.B2 = 0;
				MPC::PL2PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTL::PMR.B2 = ena;
				break;
			case ORDER::FIFTH:
				PORTM::PMR.B2 = 0;
				MPC::PM2PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTM::PMR.B2 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool trg_d_(ORDER odr, bool ena) noexcept
		{
			// GTETRGD:
			// P14
			// PH3
			// PK3
			// PL3
			// PM3
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B4 = 0;
				MPC::P14PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORT1::PMR.B4 = ena;
				break;
			case ORDER::SECOND:
				PORTH::PMR.B3 = 0;
				MPC::PH3PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTH::PMR.B3 = ena;
				break;
			case ORDER::THIRD:
				PORTK::PMR.B3 = 0;
				MPC::PK3PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTK::PMR.B3 = ena;
				break;
			case ORDER::FOURTH:
				PORTL::PMR.B3 = 0;
				MPC::PL3PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTL::PMR.B3 = ena;
				break;
			case ORDER::FIFTH:
				PORTM::PMR.B3 = 0;
				MPC::PM3PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTM::PMR.B3 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool gptw0_(CHANNEL ch, bool ena, ORDER opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1110 : 0;
			switch(ch) {
			/// GTIOC0A (入出力)
			///       224 176 144 100
			/// P23    ○   ○   ○   ○
			/// P83    ○   ○   ○   ×
			/// PA5    ○   ○   ○   ○
			/// PD3    ○   ○   ○   ○
			/// PE5    ○   ○   ○   ○
			/// PH6    ○   ×   ×   ×
			case CHANNEL::A:
				switch(opt) {
				case ORDER::FIRST:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;
					PORT2::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B3 = 0;
					MPC::P83PFS.PSEL = sel;
					PORT8::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;
					PORTA::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = sel;
					PORTD::PMR.B3 = ena;
					break;
				case ORDER::FIFTH:
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = sel;
					PORTE::PMR.B5 = ena;
					break;
				case ORDER::SIXTH:
					PORTH::PMR.B6 = 0;
					MPC::PH6PFS.PSEL = sel;
					PORTH::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// GTIOC0B (入出力)
			///       224 176 144 100
			/// P17    ○   ○   ○   ○
			/// P81    ○   ○   ○   ×
			/// PA0    ○   ○   ○   ○
			/// PD2    ○   ○   ○   ○
			/// PE2    ○   ○   ○   ○
			/// PH7    ○   ×   ×   ×
			case CHANNEL::B:
				switch(opt) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B1 = 0;
					MPC::P81PFS.PSEL = sel;
					PORT8::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;
					PORTA::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;
					PORTD::PMR.B2 = ena;
					break;
				case ORDER::FIFTH:
					PORTE::PMR.B2 = 0;
					MPC::PE2PFS.PSEL = sel;
					PORTE::PMR.B2 = ena;
					break;
				case ORDER::SIXTH:
					PORTH::PMR.B6 = 0;
					MPC::PH6PFS.PSEL = sel;
					PORTH::PMR.B6 = ena;
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

		static bool gptw1_(CHANNEL ch, bool ena, ORDER opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1110 : 0;
			switch(ch) {
			/// GTIOC1A (入出力)
			///       224 176 144 100
			/// P22    ○   ○   ○   ○
			/// PA2    ○   ○   ○   ○
			/// PC5    ○   ○   ○   ○
			/// PD1    ○   ○   ○   ○
			/// PE4    ○   ○   ○   ○
			/// PK6    ○   ×   ×   ×
			case CHANNEL::A:
				switch(opt) {
				case ORDER::FIRST:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;
					PORT2::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = sel;
					PORTA::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;
					PORTC::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;
					PORTD::PMR.B1 = ena;
					break;
				case ORDER::FIFTH:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = sel;
					PORTE::PMR.B4 = ena;
					break;
				case ORDER::SIXTH:
					PORTK::PMR.B6 = 0;
					MPC::PK6PFS.PSEL = sel;
					PORTK::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// GTIOC1B (入出力)
			///       224 176 144 100
			/// P67    ○   ○   ○   ×
			/// P87    ○   ○   ○   ×
			/// PC3    ○   ○   ○   ○
			/// PD0    ○   ○   ○   ○
			/// PE1    ○   ○   ○   ○
			/// PK7    ○   ×   ×   ×
			case CHANNEL::B:
				switch(opt) {
				case ORDER::FIRST:
					PORT6::PMR.B7 = 0;
					MPC::P67PFS.PSEL = sel;
					PORT6::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B7 = 0;
					MPC::P87PFS.PSEL = sel;
					PORT8::PMR.B7 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B3 = 0;
					MPC::PC3PFS.PSEL = sel;
					PORTC::PMR.B3 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B0 = 0;
					MPC::PD0PFS.PSEL = sel;
					PORTD::PMR.B0 = ena;
					break;
				case ORDER::FIFTH:
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = sel;
					PORTE::PMR.B1 = ena;
					break;
				case ORDER::SIXTH:
					PORTK::PMR.B7 = 0;
					MPC::PK7PFS.PSEL = sel;
					PORTK::PMR.B7 = ena;
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

		static bool gptw2_(CHANNEL ch, bool ena, ORDER opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1110 : 0;
			switch(ch) {
			/// GTIOC2A (入出力)
			///       224 176 144 100
			/// P21    ○   ○   ○   ○
			/// P82    ○   ○   ○   ×
			/// PA1    ○   ○   ○   ○
			/// PE3    ○   ○   ○   ○
			/// PL6    ○   ×   ×   ×
			case CHANNEL::A:
				switch(opt) {
				case ORDER::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;
					PORT2::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B2 = 0;
					MPC::P82PFS.PSEL = sel;
					PORT8::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;
					PORTA::PMR.B1 = ena;
					break;
				case ORDER::FOURTH:
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = sel;
					PORTE::PMR.B3 = ena;
					break;
				case ORDER::FIFTH:
					PORTL::PMR.B6 = 0;
					MPC::PL6PFS.PSEL = sel;
					PORTL::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// GTIOC2B (入出力)
			///       224 176 144 100
			/// P66    ○   ○   ○   ×
			/// P86    ○   ○   ○   ×
			/// PC2    ○   ○   ○   ○
			/// PE0    ○   ○   ○   ○
			/// PL7    ○   ×   ×   ×
			case CHANNEL::B:
				switch(opt) {
				case ORDER::FIRST:
					PORT6::PMR.B6 = 0;
					MPC::P66PFS.PSEL = sel;
					PORT6::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B6 = 0;
					MPC::P86PFS.PSEL = sel;
					PORT8::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = sel;
					PORTC::PMR.B2 = ena;
					break;
				case ORDER::FOURTH:
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = sel;
					PORTE::PMR.B0 = ena;
					break;
				case ORDER::FIFTH:
					PORTL::PMR.B7 = 0;
					MPC::PL7PFS.PSEL = sel;
					PORTL::PMR.B7 = ena;
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

		static bool gptw3_(CHANNEL ch, bool ena, ORDER opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1110 : 0;
			switch(ch) {
			/// GTIOC3A (入出力)
			///       224 176 144 100
			/// PC7    ○   ○   ○   ○
			/// PE7    ○   ○   ○   ○
			/// PM6    ○   ×   ×   ×
			case CHANNEL::A:
				switch(opt) {
				case ORDER::FIRST:
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;
					PORTC::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B7 = 0;
					MPC::PE7PFS.PSEL = sel;
					PORTE::PMR.B7 = ena;
					break;
				case ORDER::THIRD:
					PORTM::PMR.B6 = 0;
					MPC::PM6PFS.PSEL = sel;
					PORTM::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			/// GTIOC3B (入出力)
			///       224 176 144 100
			/// PC6    ○   ○   ○   ○
			/// PE6    ○   ○   ○   ○
			/// PM7    ○   ×   ×   ×
			case CHANNEL::B:
				switch(opt) {
				case ORDER::FIRST:
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;
					PORTC::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B6 = 0;
					MPC::PE6PFS.PSEL = sel;
					PORTE::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORTM::PMR.B7 = 0;
					MPC::PM7PFS.PSEL = sel;
					PORTM::PMR.B7 = ena;
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
			@brief  GPTW[0-9]、チャネル別ポート切り替え
			@param[in]	per		周辺機器タイプ型
			@param[in]	ch		チャネル型
			@param[in]	ena		無効にする場合「false」
			@param[in]	order	候補を選択する場合
			@param[in]	neg		反転入出力の場合「true」
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(peripheral per, CHANNEL ch, bool ena = true, ORDER order = ORDER::FIRST, bool neg = false) noexcept
		{
            // RX72N 系は「neg」が無い
            if(neg) return false;

			if(order == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			switch(per) {
			case peripheral::GPTW0:
				ret = gptw0_(ch, ena, order);
				break;
			case peripheral::GPTW1:
				ret = gptw1_(ch, ena, order);
				break;
			case peripheral::GPTW2:
				ret = gptw2_(ch, ena, order);
				break;
			case peripheral::GPTW3:
				ret = gptw3_(ch, ena, order);
				break;
			default:
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GPTW クロック入出力切り替え
			@param[in]	clk	クロック形
			@param[in]	ena	無効にする場合場合「false」
			@param[in]	odr	候補選択
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn_clock(CHANNEL clk, bool ena = true, ORDER odr = ORDER::FIRST) noexcept
		{
			if(odr == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			switch(clk) {
			case CHANNEL::DSM0:
				ret = dsm_0_(odr, ena);
				break;
			case CHANNEL::DSM1:
				ret = dsm_1_(odr, ena);
				break;
			case CHANNEL::TRGA:
				ret = trg_a_(odr, ena);
				break;
			case CHANNEL::TRGB:
				ret = trg_b_(odr, ena);
				break;
			case CHANNEL::TRGC:
				ret = trg_c_(odr, ena);
				break;
			case CHANNEL::TRGD:
				ret = trg_d_(odr, ena);
				break;
			default:
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}
    };
}
