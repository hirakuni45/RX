#pragma once
//=====================================================================//
/*!	@file
	@brief	RX72T グループ・ポート・マッピング (SCIx) 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX72T/peripheral.hpp"
#include "RX600/port.hpp"
#include "RX600/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCI ポート・マッピング
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_sci : public port_map_order {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SCI チャネル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CHANNEL : uint8_t {
			CTS,	///< CTSx#
			RTS,	///< RTSx#
			RXD,	///< RXDx
			SCK,	///< SCKx
			TXD,	///< TXDx
		};

	private:


		static bool sci1_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = 0;
			switch(ch) {
			case CHANNEL::CTS:
			case CHANNEL::RTS:
				// P26
				// PD6
				sel = ena ? 0b001011 : 0;
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B6 = 0;
					MPC::P26PFS.PSEL = sel;
					PORT2::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;
					PORTD::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::RXD:
				// P34
				// PC3
				// PD5
				sel = ena ? 0b001010 : 0;
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B4 = 0;
					MPC::P34PFS.PSEL = sel;
					PORT3::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B3 = 0;
					MPC::PC3PFS.PSEL = sel;
					PORTC::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORTD::PMR.B5 = 0;
					MPC::PD5PFS.PSEL = sel;
					PORTD::PMR.B5 = ena;
					break;
				default:
					break;
				}
			case CHANNEL::SCK:
				// P25
				// PD4
				sel = ena ? 0b001010 : 0;
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B5 = 0;
					MPC::P25PFS.PSEL = sel;
					PORT2::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;
					PORTD::PMR.B4 = ena;
					break;
				default:
					break;
				}
			case CHANNEL::TXD:
				// P35
				// PC4
				// PD3
				sel = ena ? 0b001010 : 0;
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B5 = 0;
					MPC::P35PFS.PSEL = sel;
					PORT3::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;
					PORTC::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = sel;
					PORTD::PMR.B3 = ena;
					break;
				default:
					break;
				}
			default:
				ret = false;
				break;
			}
			return ret;
		}


		static bool sci5_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = 0;
			switch(ch) {
			case CHANNEL::CTS:
			case CHANNEL::RTS:
				// PB4
				// PE1
				sel = ena ? 0b001011 : 0;
				switch(odr) {
				case ORDER::FIRST:
					PORTB::PMR.B4 = 0;
					MPC::PB4PFS.PSEL = sel;
					PORTB::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = sel;
					PORTE::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::RXD:
				// PB6
				// PE0
				// PK0
				sel = ena ? 0b001010 : 0;
				switch(odr) {
				case ORDER::FIRST:
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = sel;
					PORTE::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
					PORTK::PMR.B0 = 0;
					MPC::PK0PFS.PSEL = sel;
					PORTK::PMR.B0 = ena;
					break;
				default:
					break;
				}
			case CHANNEL::SCK:
				// PB7
				// PD2
				// PK2
				sel = ena ? 0b001010 : 0;
				switch(odr) {
				case ORDER::FIRST:
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;
					PORTB::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;
					PORTD::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORTK::PMR.B2 = 0;
					MPC::PK2PFS.PSEL = sel;
					PORTK::PMR.B2 = ena;
					break;
				default:
					break;
				}
			case CHANNEL::TXD:
				// PB5
				// PD7
				// PK1
				sel = ena ? 0b001010 : 0;
				switch(odr) {
				case ORDER::FIRST:
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = sel;
					PORTB::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;
					PORTD::PMR.B7 = ena;
					break;
				case ORDER::THIRD:
					PORTK::PMR.B1 = 0;
					MPC::PK1PFS.PSEL = sel;
					PORTK::PMR.B1 = ena;
					break;
				default:
					break;
				}
			default:
				ret = false;
				break;
			}
			return ret;
		}


		static bool sci6_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = 0;
			switch(ch) {
			case CHANNEL::CTS:
			case CHANNEL::RTS:
				// P10
				// PA2
				sel = ena ? 0b001011 : 0;
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B0 = 0;
					MPC::P10PFS.PSEL = sel;
					PORT1::PMR.B0 = ena;
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
			case CHANNEL::RXD:
				// P80
				// PA5
				// PB1
				sel = ena ? 0b001010 : 0;
				switch(odr) {
				case ORDER::FIRST:
					PORT8::PMR.B0 = 0;
					MPC::P80PFS.PSEL = sel;
					PORT8::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;
					PORTA::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;
					PORTB::PMR.B1 = ena;
					break;
				default:
					break;
				}
			case CHANNEL::SCK:
				// P82
				// PA4
				// PB3
				sel = ena ? 0b001010 : 0;
				switch(odr) {
				case ORDER::FIRST:
					PORT8::PMR.B2 = 0;
					MPC::P82PFS.PSEL = sel;
					PORT8::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;
					PORTB::PMR.B3 = ena;
					break;
				default:
					break;
				}
			case CHANNEL::TXD:
				// P81
				// PB0
				// PB2
				sel = ena ? 0b001010 : 0;
				switch(odr) {
				case ORDER::FIRST:
					PORT8::PMR.B1 = 0;
					MPC::P81PFS.PSEL = sel;
					PORT8::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;
					PORTB::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B2 = 0;
					MPC::PB2PFS.PSEL = sel;
					PORTB::PMR.B2 = ena;
					break;
				default:
					break;
				}
			default:
				ret = false;
				break;
			}
			return ret;
		}


		static bool sci8_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = 0;
			switch(ch) {
			case CHANNEL::CTS:
			case CHANNEL::RTS:
				// P20
				// P24
				// P30
				// P35
				// P96
				// PK1
				sel = ena ? 0b001011 : 0;
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = sel;
					PORT2::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;
					PORT2::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = sel;
					PORT3::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORT3::PMR.B5 = 0;
					MPC::P35PFS.PSEL = sel;
					PORT3::PMR.B5 = ena;
					break;
				case ORDER::FIFTH:
					PORT9::PMR.B6 = 0;
					MPC::P96PFS.PSEL = sel;
					PORT9::PMR.B6 = ena;
					break;
				case ORDER::SIXTH:
					PORTK::PMR.B1 = 0;
					MPC::PK1PFS.PSEL = sel;
					PORTK::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::RXD:
				// P22
				// PA5
				// PC0
				// PD1
				sel = ena ? 0b001010 : 0;
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;
					PORT2::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;
					PORTA::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B0 = 0;
					MPC::PC0PFS.PSEL = sel;
					PORTC::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;
					PORTD::PMR.B1 = ena;
					break;
				default:
					break;
				}
				break;
			case CHANNEL::SCK:
				// P20
				// P24
				// P30
				// PA3
				// PC2
				// PD2
				sel = ena ? 0b001010 : 0;
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = sel;
					PORT2::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;
					PORT2::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = sel;
					PORT3::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = sel;
					PORTA::PMR.B3 = ena;
					break;
				case ORDER::FIFTH:
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = sel;
					PORTC::PMR.B2 = ena;
					break;
				case ORDER::SIXTH:
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;
					PORTD::PMR.B2 = ena;
					break;
				default:
					break;
				}
				break;
			case CHANNEL::TXD:
				// P21
				// P23
				// PA4
				// PC1
				// PD0
				sel = ena ? 0b001010 : 0;
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;
					PORT2::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;
					PORT2::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B4 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = sel;
					PORTC::PMR.B1 = ena;
					break;
				case ORDER::FIFTH:
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;
					PORTD::PMR.B1 = ena;
					break;
				default:
					break;
				}
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}


		static bool sci9_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			switch(ch) {
			case CHANNEL::CTS:
			case CHANNEL::RTS:
				// P34
				// P70
				// PE3
				// PE5
				// PK2
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B4 = 0;
					MPC::P34PFS.PSEL = ena ? 0b001011 : 0;
					PORT3::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B0 = 0;
					MPC::P70PFS.PSEL = ena ? 0b001011 : 0;
					PORT7::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = ena ? 0b001011 : 0;
					PORTE::PMR.B3 = ena;
					break;
				case ORDER::FOURTH:
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = ena ? 0b001011 : 0;
					PORTE::PMR.B5 = ena;
					break;
				case ORDER::FIFTH:
					PORTK::PMR.B2 = 0;
					MPC::PK2PFS.PSEL = ena ? 0b001011 : 0;
					PORTK::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::RXD:
				// P00
				// PA2
				// PG0
				switch(odr) {
				case ORDER::FIRST:
					PORT0::PMR.B0 = 0;
					MPC::P00PFS.PSEL = ena ? 0b001010 : 0;
					PORT0::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = ena ? 0b001010 : 0;
					PORTA::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORTG::PMR.B0 = 0;
					MPC::PG0PFS.PSEL = ena ? 0b001010 : 0;
					PORTG::PMR.B0 = ena;
					break;
				default:
					break;
				}
			case CHANNEL::SCK:
				// PA0
				// PE4
				// PE5
				// PG2
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = ena ? 0b001010 : 0;
					PORTA::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = ena ? 0b001010 : 0;
					PORTE::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = ena ? 0b001010 : 0;
					PORTE::PMR.B5 = ena;
					break;
				case ORDER::FIFTH:
					PORTG::PMR.B2 = 0;
					MPC::PG2PFS.PSEL = ena ? 0b001010 : 0;
					PORTG::PMR.B2 = ena;
					break;
				default:
					break;
				}
			case CHANNEL::TXD:
				// P01
				// PA1
				// PA3
				// PG1
				switch(odr) {
				case ORDER::FIRST:
					PORT0::PMR.B1 = 0;
					MPC::P01PFS.PSEL = ena ? 0b001010 : 0;
					PORT0::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = ena ? 0b001010 : 0;
					PORTA::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = ena ? 0b001010 : 0;
					PORTA::PMR.B3 = ena;
					break;
				case ORDER::FOURTH:
					PORTG::PMR.B1 = 0;
					MPC::PG1PFS.PSEL = ena ? 0b001010 : 0;
					PORTG::PMR.B1 = ena;
					break;
				default:
					break;
				}
			default:
				ret = false;
				break;
			}
			return ret;
		}


		static bool sci11_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			switch(ch) {
			case CHANNEL::CTS:
			case CHANNEL::RTS:
				// PB0
				// PB4
				// PD6
				// PF3
				switch(odr) {
				case ORDER::FIRST:
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = ena ? 0b100100 : 0;
					PORTB::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B4 = 0;
					MPC::PB4PFS.PSEL = ena ? 0b001011 : 0;
					PORTB::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = ena ? 0b001011 : 0;
					PORTD::PMR.B6 = ena;
					break;
				case ORDER::FOURTH:
					PORTF::PMR.B3 = 0;
					MPC::PF3PFS.PSEL = ena ? 0b001011 : 0;
					PORTF::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::RXD:
				// PA1
				// PA7
				// PB6
				// PC6
				// PD5
				// PF1
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = ena ? 0b001010 : 0;
					PORTA::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B7 = 0;
					MPC::PA7PFS.PSEL = ena ? 0b100100 : 0;
					PORTA::PMR.B7 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = ena ? 0b001010 : 0;
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = ena ? 0b001011 : 0;
					PORTC::PMR.B6 = ena;
					break;
				case ORDER::FIFTH:
					PORTD::PMR.B5 = 0;
					MPC::PD5PFS.PSEL = ena ? 0b001011 : 0;
					PORTD::PMR.B5 = ena;
					break;
				case ORDER::SIXTH:
					PORTF::PMR.B1 = 0;
					MPC::PF1PFS.PSEL = ena ? 0b001011 : 0;
					PORTF::PMR.B1 = ena;
					break;
				default:
					break;
				}
			case CHANNEL::SCK:
				// PA2
				// PB4
				// PB7
				// PD4
				// PF2
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = ena ? 0b100100 : 0;
					PORTA::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B4 = 0;
					MPC::PB4PFS.PSEL = ena ? 0b001010 : 0;
					PORTB::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = ena ? 0b001010 : 0;
					PORTB::PMR.B7 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = ena ? 0b001011 : 0;
					PORTD::PMR.B4 = ena;
					break;
				case ORDER::FIFTH:
					PORTF::PMR.B2 = 0;
					MPC::PF2PFS.PSEL = ena ? 0b001011 : 0;
					PORTF::PMR.B2 = ena;
					break;
				default:
					break;
				}
			case CHANNEL::TXD:
				// PA0
				// PA6
				// PB5
				// PC5
				// PD3
				// PF0
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = ena ? 0b001010 : 0;
					PORTA::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = ena ? 0b100100 : 0;
					PORTA::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = ena ? 0b001010 : 0;
					PORTB::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = ena ? 0b001011 : 0;
					PORTC::PMR.B5 = ena;
					break;
				case ORDER::FIFTH:
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = ena ? 0b001011 : 0;
					PORTD::PMR.B3 = ena;
					break;
				case ORDER::SIXTH:
					PORTF::PMR.B0 = 0;
					MPC::PF0PFS.PSEL = ena ? 0b001011 : 0;
					PORTF::PMR.B0 = ena;
					break;
				default:
					break;
				}
			default:
				ret = false;
				break;
			}
			return ret;
		}


		static bool sci12_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b001100 : 0;
			switch(ch) {
			case CHANNEL::CTS:
			case CHANNEL::RTS:
				// PE3
				switch(odr) {
				case ORDER::FIRST:
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = sel;
					PORTE::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::RXD:
				// PE2
				switch(odr) {
				case ORDER::FIRST:
					PORTE::PMR.B2 = 0;
					MPC::PE2PFS.PSEL = sel;
					PORTE::PMR.B2 = ena;
					break;
				default:
					break;
				}
			case CHANNEL::SCK:
				// PE0
				switch(odr) {
				case ORDER::FIRST:
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = sel;
					PORTE::PMR.B0 = ena;
					break;
				default:
					break;
				}
			case CHANNEL::TXD:
				// PE1
				switch(odr) {
				case ORDER::FIRST:
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = sel;
					PORTE::PMR.B1 = ena;
					break;
				default:
					break;
				}
			default:
				ret = false;
				break;
			}
			return ret;
		}

	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SCIx、チャネル別ポート切り替え
			@param[in]	per		周辺機器タイプ型
			@param[in]	ch		チャネル
			@param[in]	ena		無効にする場合「false」
			@param[in]	order	候補を選択する場合
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(peripheral per, CHANNEL ch, bool ena = true, ORDER order = ORDER::FIRST) noexcept
		{
			if(order == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			switch(per) {
			case peripheral::SCI1:
				ret = sci1_(ch, ena, order);
				break;
			case peripheral::SCI5:
				ret = sci5_(ch, ena, order);
				break;
			case peripheral::SCI6:
				ret = sci6_(ch, ena, order);
				break;
			case peripheral::SCI8:
				ret = sci8_(ch, ena, order);
				break;
			case peripheral::SCI9:
				ret = sci9_(ch, ena, order);
				break;
			case peripheral::SCI11:
				ret = sci11_(ch, ena, order);
				break;
			case peripheral::SCI12:
				ret = sci12_(ch, ena, order);
				break;
			default:
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
