#pragma once
//=========================================================================//
/*!	@file
	@brief	RX660/RX671 ポート・マッピング (IRQ) @n
			IRQx-DS 端子は、ディープスタンバイからの復帰が有効な端子 @n
			  通常割り込み入力としても使え、通常「ORDER::FIRST」で選択する。 @n
			  詳しくは、MPC の解説を参照する事。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  IRQ ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_irq : public port_map_order {

		static bool irq0_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {
			// P30 (DS)
			// P50
			// P60
			// P70
			// P90
			// PA0
			// PD0
			// PH1
			case ORDER::FIRST:
				PORT3::PMR.B0 = 0;
				MPC::P30PFS.PSEL = 0;
				MPC::P30PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT5::PMR.B0 = 0;
				MPC::P50PFS.PSEL = 0;
				MPC::P50PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT6::PMR.B0 = 0;
				MPC::P60PFS.PSEL = 0;
				MPC::P60PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT7::PMR.B0 = 0;
				MPC::P70PFS.PSEL = 0;
				MPC::P70PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORT9::PMR.B0 = 0;
				MPC::P90PFS.PSEL = 0;
				MPC::P90PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTA::PMR.B0 = 0;
				MPC::PA0PFS.PSEL = 0;
				MPC::PA0PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
				PORTD::PMR.B0 = 0;
				MPC::PD0PFS.PSEL = 0;
				MPC::PD0PFS.ISEL = ena;
				break;
			case ORDER::EIGHTH:
				PORTH::PMR.B1 = 0;
				MPC::PH1PFS.PSEL = 0;
				MPC::PH1PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq1_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {
			// P31 (DS)
			// P51
			// P61
			// P71
			// PD1
			// PH2
			case ORDER::FIRST:
				PORT3::PMR.B1 = 0;
				MPC::P31PFS.PSEL = 0;
				MPC::P31PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT5::PMR.B1 = 0;
				MPC::P51PFS.PSEL = 0;
				MPC::P51PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT6::PMR.B1 = 0;
				MPC::P61PFS.PSEL = 0;
				MPC::P61PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT7::PMR.B1 = 0;
				MPC::P71PFS.PSEL = 0;
				MPC::P71PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORTD::PMR.B1 = 0;
				MPC::PD1PFS.PSEL = 0;
				MPC::PD1PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTH::PMR.B2 = 0;
				MPC::PH2PFS.PSEL = 0;
				MPC::PH2PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq2_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {
			// P32 (DS)
			// P12
			// P52
			// P62
			// P82
			// PB2
			// PD2
			case ORDER::FIRST:
				PORT3::PMR.B2 = 0;
				MPC::P32PFS.PSEL = 0;
				MPC::P32PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B2 = 0;
				MPC::P12PFS.PSEL = 0;
				MPC::P12PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT5::PMR.B2 = 0;
				MPC::P52PFS.PSEL = 0;
				MPC::P52PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT6::PMR.B2 = 0;
				MPC::P62PFS.PSEL = 0;
				MPC::P62PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORT8::PMR.B2 = 0;
				MPC::P82PFS.PSEL = 0;
				MPC::P82PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTB::PMR.B2 = 0;
				MPC::PB2PFS.PSEL = 0;
				MPC::PB2PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
				PORTD::PMR.B2 = 0;
				MPC::PD2PFS.PSEL = 0;
				MPC::PD2PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq3_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {
			// P33 (DS)
			// P13
			// P23
			// P53
			// P63
			// P83
			// PB3
			// PD3
			case ORDER::FIRST:
				PORT3::PMR.B3 = 0;
				MPC::P33PFS.PSEL = 0;
				MPC::P33PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B3 = 0;
				MPC::P13PFS.PSEL = 0;
				MPC::P13PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = 0;
				MPC::P23PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT5::PMR.B3 = 0;
				MPC::P53PFS.PSEL = 0;
				MPC::P53PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORT6::PMR.B3 = 0;
				MPC::P63PFS.PSEL = 0;
				MPC::P63PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORT8::PMR.B3 = 0;
				MPC::P83PFS.PSEL = 0;
				MPC::P83PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
				PORTB::PMR.B3 = 0;
				MPC::PB3PFS.PSEL = 0;
				MPC::PB3PFS.ISEL = ena;
				break;
			case ORDER::EIGHTH:
				PORTD::PMR.B3 = 0;
				MPC::PD3PFS.PSEL = 0;
				MPC::PD3PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq4_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {
			// PB1 (DS)
			// P14
			// P34
			// P54
			// P64
			// PB4
			// PD4
			// PF5
			case ORDER::FIRST:
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = 0;
				MPC::PB1PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B4 = 0;
				MPC::P14PFS.PSEL = 0;
				MPC::P14PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT3::PMR.B4 = 0;
				MPC::P34PFS.PSEL = 0;
				MPC::P34PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT5::PMR.B4 = 0;
				MPC::P54PFS.PSEL = 0;
				MPC::P54PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORT6::PMR.B4 = 0;
				MPC::P64PFS.PSEL = 0;
				MPC::P64PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTB::PMR.B4 = 0;
				MPC::PB4PFS.PSEL = 0;
				MPC::PB4PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
				PORTD::PMR.B4 = 0;
				MPC::PD4PFS.PSEL = 0;
				MPC::PD4PFS.ISEL = ena;
				break;
			case ORDER::EIGHTH:
				PORTF::PMR.B5 = 0;
				MPC::PF5PFS.PSEL = 0;
				MPC::PF5PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq5_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {
			// PA4 (DS)
			// P15
			// P25
			// PA5
			// PC5
			// PD5
			// PE5
			case ORDER::FIRST:
				PORTA::PMR.B4 = 0;
				MPC::PA4PFS.PSEL = 0;
				MPC::PA4PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B5 = 0;
				MPC::P15PFS.PSEL = 0;
				MPC::P15PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT2::PMR.B5 = 0;
				MPC::P25PFS.PSEL = 0;
				MPC::P25PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTA::PMR.B5 = 0;
				MPC::PA5PFS.PSEL = 0;
				MPC::PA5PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORTC::PMR.B5 = 0;
				MPC::PC5PFS.PSEL = 0;
				MPC::PC5PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTD::PMR.B5 = 0;
				MPC::PD5PFS.PSEL = 0;
				MPC::PD5PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
				PORTE::PMR.B5 = 0;
				MPC::PE5PFS.PSEL = 0;
				MPC::PE5PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq6_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {
			// PA3 (DS)
			// P16
			// P26
			// P56
			// PB6
			// PD6
			// PE6
			case ORDER::FIRST:
				PORTA::PMR.B3 = 0;
				MPC::PA3PFS.PSEL = 0;
				MPC::PA3PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B6 = 0;
				MPC::P16PFS.PSEL = 0;
				MPC::P16PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT2::PMR.B6 = 0;
				MPC::P26PFS.PSEL = 0;
				MPC::P26PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT5::PMR.B6 = 0;
				MPC::P56PFS.PSEL = 0;
				MPC::P56PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORTB::PMR.B6 = 0;
				MPC::PB6PFS.PSEL = 0;
				MPC::PB6PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTD::PMR.B6 = 0;
				MPC::PD6PFS.PSEL = 0;
				MPC::PD6PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
				PORTE::PMR.B6 = 0;
				MPC::PE6PFS.PSEL = 0;
				MPC::PE6PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq7_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {
			// PE2 (DS)
			// P17
			// P27
			// P77
			// PA7
			// PD7
			// PE7
			case ORDER::FIRST:
				PORTE::PMR.B2 = 0;
				MPC::PE2PFS.PSEL = 0;
				MPC::PE2PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B7 = 0;
				MPC::P17PFS.PSEL = 0;
				MPC::P17PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT2::PMR.B7 = 0;
				MPC::P27PFS.PSEL = 0;
				MPC::P27PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT7::PMR.B7 = 0;
				MPC::P77PFS.PSEL = 0;
				MPC::P77PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORTA::PMR.B7 = 0;
				MPC::PA7PFS.PSEL = 0;
				MPC::PA7PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTD::PMR.B7 = 0;
				MPC::PD7PFS.PSEL = 0;
				MPC::PD7PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
				PORTE::PMR.B7 = 0;
				MPC::PE7PFS.PSEL = 0;
				MPC::PE7PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq8_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {
			// P40 (DS)
			// P00
			// P20
			// P73
			// P80
			// PE0
			case ORDER::FIRST:
				MPC::P40PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT0::PMR.B0 = 0;
				MPC::P00PFS.PSEL = 0;
				MPC::P00PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT2::PMR.B0 = 0;
				MPC::P20PFS.PSEL = 0;
				MPC::P20PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT7::PMR.B3 = 0;
				MPC::P73PFS.PSEL = 0;
				MPC::P73PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORT8::PMR.B0 = 0;
				MPC::P80PFS.PSEL = 0;
				MPC::P80PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTE::PMR.B0 = 0;
				MPC::PE0PFS.PSEL = 0;
				MPC::PE0PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq9_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {
			// P41 (DS)
			// P01
			// P21
			// P81
			// P91
			// PE1
			case ORDER::FIRST:
				MPC::P41PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT0::PMR.B1 = 0;
				MPC::P01PFS.PSEL = 0;
				MPC::P01PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT2::PMR.B1 = 0;
				MPC::P21PFS.PSEL = 0;
				MPC::P21PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT8::PMR.B1 = 0;
				MPC::P81PFS.PSEL = 0;
				MPC::P81PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORT9::PMR.B1 = 0;
				MPC::P91PFS.PSEL = 0;
				MPC::P91PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTE::PMR.B1 = 0;
				MPC::PE1PFS.PSEL = 0;
				MPC::PE1PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq10_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {
			// P42 (DS)
			// P02
			// P55
			// P72
			// P92
			// PA2
			// PC2
			case ORDER::FIRST:
				MPC::P42PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT0::PMR.B2 = 0;
				MPC::P02PFS.PSEL = 0;
				MPC::P02PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT5::PMR.B5 = 0;
				MPC::P55PFS.PSEL = 0;
				MPC::P55PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT7::PMR.B2 = 0;
				MPC::P72PFS.PSEL = 0;
				MPC::P72PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORT9::PMR.B2 = 0;
				MPC::P92PFS.PSEL = 0;
				MPC::P92PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTA::PMR.B2 = 0;
				MPC::PA2PFS.PSEL = 0;
				MPC::PA2PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
				PORTC::PMR.B2 = 0;
				MPC::PC2PFS.PSEL = 0;
				MPC::PC2PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq11_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {
			// P43 (DS)
			// P03
			// P93
			// PA1
			// PC3
			// PE3
			// PJ3
			case ORDER::FIRST:
				MPC::P43PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT0::PMR.B3 = 0;
				MPC::P03PFS.PSEL = 0;
				MPC::P03PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT9::PMR.B3 = 0;
				MPC::P93PFS.PSEL = 0;
				MPC::P93PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTA::PMR.B1 = 0;
				MPC::PA1PFS.PSEL = 0;
				MPC::PA1PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORTC::PMR.B3 = 0;
				MPC::PC3PFS.PSEL = 0;
				MPC::PC3PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTE::PMR.B3 = 0;
				MPC::PE3PFS.PSEL = 0;
				MPC::PE3PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
				PORTJ::PMR.B3 = 0;
				MPC::PJ3PFS.PSEL = 0;
				MPC::PJ3PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq12_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {
			// P44 (DS)
			// P24
			// P74
			// PB0
			// PC1
			// PC4
			// PE4
			case ORDER::FIRST:
				MPC::P44PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = 0;
				MPC::P24PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT7::PMR.B4 = 0;
				MPC::P74PFS.PSEL = 0;
				MPC::P74PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = 0;
				MPC::PB0PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORTC::PMR.B1 = 0;
				MPC::PC1PFS.PSEL = 0;
				MPC::PC1PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTC::PMR.B4 = 0;
				MPC::PC4PFS.PSEL = 0;
				MPC::PC4PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
				PORTE::PMR.B4 = 0;
				MPC::PE4PFS.PSEL = 0;
				MPC::PE4PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq13_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {
			// P45 (DS)
			// P05
			// P65
			// P75
			// PB5
			// PC6
			// PJ5
			case ORDER::FIRST:
				MPC::P45PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT0::PMR.B5 = 0;
				MPC::P05PFS.PSEL = 0;
				MPC::P05PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT6::PMR.B5 = 0;
				MPC::P65PFS.PSEL = 0;
				MPC::P65PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT7::PMR.B5 = 0;
				MPC::P75PFS.PSEL = 0;
				MPC::P75PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORTB::PMR.B5 = 0;
				MPC::PB5PFS.PSEL = 0;
				MPC::PB5PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTC::PMR.B6 = 0;
				MPC::PC6PFS.PSEL = 0;
				MPC::PC6PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
				PORTJ::PMR.B5 = 0;
				MPC::PJ5PFS.PSEL = 0;
				MPC::PJ5PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq14_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {
			// P46 (DS)
			// P66
			// P76
			// P86
			// PA6
			// PC0
			// PC7
			case ORDER::FIRST:
				MPC::P46PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT6::PMR.B6 = 0;
				MPC::P66PFS.PSEL = 0;
				MPC::P66PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT7::PMR.B6 = 0;
				MPC::P76PFS.PSEL = 0;
				MPC::P76PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT8::PMR.B6 = 0;
				MPC::P86PFS.PSEL = 0;
				MPC::P86PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = 0;
				MPC::PA6PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTC::PMR.B0 = 0;
				MPC::PC0PFS.PSEL = 0;
				MPC::PC0PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
				PORTC::PMR.B7 = 0;
				MPC::PC7PFS.PSEL = 0;
				MPC::PC7PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq15_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {
			// P47 (DS)
			// P07
			// P22
			// P67
			// P87
			// PB7
			case ORDER::FIRST:
				MPC::P47PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT0::PMR.B7 = 0;
				MPC::P07PFS.PSEL = 0;
				MPC::P07PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = 0;
				MPC::P22PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT6::PMR.B7 = 0;
				MPC::P67PFS.PSEL = 0;
				MPC::P67PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORT8::PMR.B7 = 0;
				MPC::P87PFS.PSEL = 0;
				MPC::P87PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTB::PMR.B7 = 0;
				MPC::PB7PFS.PSEL = 0;
				MPC::PB7PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  IRQ ポート切り替え
			@param[in]	irqv	IRQ ベクター
			@param[in]	ena		無効にする場合「false」
			@param[in]	odr		候補選択
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(ICU::VECTOR irqv, bool ena = true, ORDER odr = ORDER::FIRST) noexcept
		{
			if(odr == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = true;
			switch(irqv) {
			case ICU::VECTOR::IRQ0:
				ret = irq0_(ena, odr);
				break;
			case ICU::VECTOR::IRQ1:
				ret = irq1_(ena, odr);
				break;
			case ICU::VECTOR::IRQ2:
				ret = irq2_(ena, odr);
				break;
			case ICU::VECTOR::IRQ3:
				ret = irq3_(ena, odr);
				break;
			case ICU::VECTOR::IRQ4:
				ret = irq4_(ena, odr);
				break;
			case ICU::VECTOR::IRQ5:
				ret = irq5_(ena, odr);
				break;
			case ICU::VECTOR::IRQ6:
				ret = irq6_(ena, odr);
				break;
			case ICU::VECTOR::IRQ7:
				ret = irq7_(ena, odr);
				break;
			case ICU::VECTOR::IRQ8:
				ret = irq8_(ena, odr);
				break;
			case ICU::VECTOR::IRQ9:
				ret = irq9_(ena, odr);
				break;
			case ICU::VECTOR::IRQ10:
				ret = irq10_(ena, odr);
				break;
			case ICU::VECTOR::IRQ11:
				ret = irq11_(ena, odr);
				break;
			case ICU::VECTOR::IRQ12:
				ret = irq12_(ena, odr);
				break;
			case ICU::VECTOR::IRQ13:
				ret = irq13_(ena, odr);
				break;
			case ICU::VECTOR::IRQ14:
				ret = irq14_(ena, odr);
				break;
			case ICU::VECTOR::IRQ15:
				ret = irq15_(ena, odr);
				break;
			default:
				ret = false;
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
