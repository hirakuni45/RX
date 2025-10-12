#pragma once
//=========================================================================//
/*!	@file
	@brief	RX24U グループ・ポート・マッピング @n
			RX24U は 144 ピン版があるので、RX24T から分離
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX24U/peripheral.hpp"
#include "RX24U/port.hpp"
#include "RX24U/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX24T ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map : public port_map_order {

		static bool sci1_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:  // for Serial BOOT interface
			// RXD1: PD5 (LFQFP100:  20) (LFQFP144:  27)
			// TXD1: PD3 (LFQFP100:  22) (LFQFP144:  29)
			// SCK1: PD4 (LFQFP100:  21) (LFQFP144:  28)
				PORTD::PMR.B5 = 0;
				PORTD::ODR.B5 = i2c;
				MPC::PD5PFS.PSEL = sel;  // ok
				PORTD::PMR.B5 = enable;
				PORTD::PMR.B3 = 0;
				PORTD::ODR.B3 = i2c;
				MPC::PD3PFS.PSEL = sel;  // ok
				PORTD::PMR.B3 = enable;
				if(spi) {
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;  // ok
					PORTD::PMR.B4 = enable;
				}
				break;
			case ORDER::SECOND:
			// RXD1: PC3 (LFQFP100: ---) (LFQFP144:  98)
			// TXD1: PC4 (LFQFP100: ---) (LFQFP144:  97)
			// SCK1: P25 (LFQFP100: ---) (LFQFP144:  93)
				PORTC::PMR.B3 = 0;
				PORTC::ODR.B3 = i2c;
				MPC::PC3PFS.PSEL = sel;  // ok
				PORTC::PMR.B3 = enable;
				PORTC::PMR.B4 = 0;
				PORTC::ODR.B4 = i2c;
				MPC::PC4PFS.PSEL = sel;  // ok
				PORTC::PMR.B4 = enable;
				if(spi) {
					PORT2::PMR.B5 = 0;
					MPC::P25PFS.PSEL = sel;  // ok
					PORT2::PMR.B5 = enable;
				}
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sci5_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD5: PB6 (LFQFP100:  27) (LFQFP144:  38)
			// TXD5: PB5 (LFQFP100:  28) (LFQFP144:  39)
			// SCK5: PB7 (LFQFP100:  26) (LFQFP144:  37)
				PORTB::PMR.B6 = 0;
				PORTB::ODR.B6 = i2c;
				MPC::PB6PFS.PSEL = sel;  // ok
				PORTB::PMR.B6 = enable;
				PORTB::PMR.B5 = 0;
				PORTB::ODR.B5 = i2c;
				MPC::PB5PFS.PSEL = sel;  // ok
				PORTB::PMR.B5 = enable;
				if(spi) {
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;  // ok
					PORTB::PMR.B7 = enable;
				}
				break;
			case ORDER::SECOND:  // Only B Version
			// RXD5: PE0 (LFQFP100:  17) (LFQFP144:  24)
			// TXD5: PD7 (LFQFP100:  18) (LFQFP144:  25)
			// SCK5: PD2 (LFQFP100:  23) (LFQFP144:  30)
				PORTE::PMR.B0 = 0;
				PORTE::ODR.B0 = i2c;
				MPC::PE0PFS.PSEL = sel;  // ok
				PORTE::PMR.B0 = enable;
				PORTD::PMR.B7 = 0;
				PORTD::ODR.B7 = i2c;
				MPC::PD7PFS.PSEL = sel;  // ok
				PORTD::PMR.B7 = enable;
				if(spi) {
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;  // ok
					PORTD::PMR.B2 = enable;
				}
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sci6_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD6: P80 (LFQFP100:  98) (LFQFP144: 139)
			// TXD6: P81 (LFQFP100:  97) (LFQFP144: 138)
			// SCK6: P82 (LFQFP100:  96) (LFQFP144: 137)
				PORT8::PMR.B0 = 0;
				PORT8::ODR.B0 = i2c;
				MPC::P80PFS.PSEL = sel;  // ok
				PORT8::PMR.B0 = enable;
				PORT8::PMR.B1 = 0;
				PORT8::ODR.B1 = i2c;
				MPC::P81PFS.PSEL = sel;  // ok
				PORT8::PMR.B1 = enable;
				if(spi) {
					PORT8::PMR.B2 = 0;
					MPC::P82PFS.PSEL = sel;  // ok
					PORT8::PMR.B2 = enable;
				}
				break;
			case ORDER::SECOND:
			// RXD6: PA5 (LFQFP100:  36) (LFQFP144:  53)
			// TXD6: PB0 (LFQFP100:  35) (LFQFP144:  50)
			// SCK6: PA4 (LFQFP100:  37) (LFQFP144:  54)
				PORTA::PMR.B5 = 0;
				PORTA::ODR.B5 = i2c;
				MPC::PA5PFS.PSEL = sel;  // ok
				PORTA::PMR.B5 = enable;
				PORTB::PMR.B0 = 0;
				PORTB::ODR.B0 = i2c;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
				if(spi) {
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;  // ok
					PORTA::PMR.B4 = enable;
				}
				break;
			case ORDER::THIRD:
			// RXD6: PB1 (LFQFP100:  34) (LFQFP144:  49)
			// TXD6: PB2 (LFQFP100:  33) (LFQFP144:  48)
			// SCK6: PB3 (LFQFP100:  32) (LFQFP144:  47)
				PORTB::PMR.B2 = 0;
				PORTB::ODR.B2 = i2c;
				MPC::PB2PFS.PSEL = sel;  // ok
				PORTB::PMR.B2 = enable;
				PORTB::PMR.B1 = 0;
				PORTB::ODR.B1 = i2c;
				MPC::PB1PFS.PSEL = sel;  // ok
				PORTB::PMR.B1 = enable;
				if(spi) {
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;  // ok
					PORTB::PMR.B3 = enable;
				}
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sci8_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD8: P83 (LFQFP100: ---) (LFQFP144: 136)
			// TXD8: P84 (LFQFP100: ---) (LFQFP144: 135)
			// SCK8: PC2 (LFQFP100: ---) (LFQFP144:  44)
				PORT8::PMR.B3 = 0;
				PORT8::ODR.B3 = i2c;
				MPC::P83PFS.PSEL = sel;
				PORT8::PMR.B3 = enable;  // ok
				PORT8::PMR.B4 = 0;
				PORT8::ODR.B4 = i2c;
				MPC::P84PFS.PSEL = sel;
				PORT8::PMR.B4 = enable;  // ok
				if(spi) {
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = sel;
					PORTC::PMR.B2 = enable;  // ok
				}
				break;
			case ORDER::SECOND:
			// RXD8: PC0 (LFQFP100: ---) (LFQFP144:  46)
			// TXD8: PC1 (LFQFP100: ---) (LFQFP144:  45)
			// SCK8: PC2 (LFQFP100: ---) (LFQFP144:  44)
				PORTC::PMR.B0 = 0;
				PORTC::ODR.B0 = i2c;
				MPC::PC0PFS.PSEL = sel;
				PORTC::PMR.B0 = enable;  // ok
				PORTC::PMR.B1 = 0;
				PORTC::ODR.B1 = i2c;
				MPC::PC1PFS.PSEL = sel;
				PORTC::PMR.B1 = enable;  // ok
				if(spi) {
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = sel;
					PORTC::PMR.B2 = enable;  // ok
				}
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sci9_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD9: PG0 (LFQFP100: ---) (LFQFP144:  82)
			// TXD9: PG1 (LFQFP100: ---) (LFQFP144:  81)
			// SCK9: PG2 (LFQFP100: ---) (LFQFP144:  80)
				PORTG::PMR.B0 = 0;
				PORTG::ODR.B0 = i2c;
				MPC::PG0PFS.PSEL = sel;
				PORTG::PMR.B0 = enable;  // ok
				PORTG::PMR.B1 = 0;
				PORTG::ODR.B1 = i2c;
				MPC::PG1PFS.PSEL = sel;
				PORTG::PMR.B1 = enable;  // ok
				if(spi) {
					PORTG::PMR.B2 = 0;
					MPC::PG2PFS.PSEL = sel;
					PORTG::PMR.B2 = enable;  // ok
				}
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sci11_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1011 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD11: PC6 (LFQFP100: ---) (LFQFP144:  61)
			// TXD11: PC5 (LFQFP100: ---) (LFQFP144:  62)
			// SCK11: PD4 (LFQFP100:  21) (LFQFP144:  28)
				PORTC::PMR.B6 = 0;
				PORTC::ODR.B6 = i2c;
				MPC::PC6PFS.PSEL = sel;
				PORTC::PMR.B6 = enable;  // ok
				PORTC::PMR.B5 = 0;
				PORTC::ODR.B5 = i2c;
				MPC::PC5PFS.PSEL = sel;
				PORTC::PMR.B5 = enable;  // ok
				if(spi) {
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;
					PORTD::PMR.B4 = enable;  // ok
				}
				break;
			case ORDER::SECOND:
			// RXD11: PD5 (LFQFP100:  20) (LFQFP144:  27)
			// TXD11: PD3 (LFQFP100:  22) (LFQFP144:  29)
			// SCK11: PD4 (LFQFP100:  21) (LFQFP144:  28)
				PORTD::PMR.B5 = 0;
				PORTD::ODR.B5 = i2c;
				MPC::PD5PFS.PSEL = sel;
				PORTD::PMR.B5 = enable;  // ok
				PORTD::PMR.B3 = 0;
				PORTD::ODR.B3 = i2c;
				MPC::PD3PFS.PSEL = sel;
				PORTD::PMR.B3 = enable;  // ok
				if(spi) {
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;
					PORTD::PMR.B4 = enable;  // ok
				}
				break;
			case ORDER::THIRD:
			// RXD11: PF1 (LFQFP100: ---) (LFQFP144:  35)
			// TXD11: PF0 (LFQFP100: ---) (LFQFP144:  36)
			// SCK11: PF2 (LFQFP100: ---) (LFQFP144:  34)
				PORTF::PMR.B1 = 0;
				PORTF::ODR.B1 = i2c;
				MPC::PF1PFS.PSEL = sel;
				PORTF::PMR.B1 = enable;  // ok
				PORTF::PMR.B0 = 0;
				PORTF::ODR.B0 = i2c;
				MPC::PF0PFS.PSEL = sel;
				PORTF::PMR.B0 = enable;  // ok
				if(spi) {
					PORTF::PMR.B2 = 0;
					MPC::PF2PFS.PSEL = sel;
					PORTF::PMR.B2 = enable;  // ok
				}
				break;
			default:
				return false;
			}
			return true;
		}

		static bool riic0_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b0'1111 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// SCL0: PB1 (LFQFP100:  34) (LFQFP144:  49)
			// SDA0: PB2 (LFQFP100:  33) (LFQFP144:  48)
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = sel;  // ok  
				PORTB::PMR.B1 = enable;
				PORTB::PMR.B2 = 0;
				MPC::PB2PFS.PSEL = sel;  // ok
				PORTB::PMR.B2 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rscan_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b1'0000 : 0;
			switch(odr) {
			case ORDER::FIRST:  // Only Version B
			// CTXD0: PA0 (LFQFP100:  41) (LFQFP144:  58)
				PORTA::PMR.B0 = 0;
				MPC::PA0PFS.PSEL = sel;  // ok
				PORTA::PMR.B0 = enable;
			// CRXD0: PA1 (LFQFP100:  40) (LFQFP144:  57)
				PORTA::PMR.B1 = 0;
				MPC::PA1PFS.PSEL = sel;  // ok
				PORTA::PMR.B1 = enable;
				break;
			case ORDER::SECOND:
			// CTXD0: PF2 (LFQFP100: ---) (LFQFP144:  34)
				PORTF::PMR.B2 = 0;
				MPC::PF2PFS.PSEL = sel;  // ok
				PORTF::PMR.B2 = enable;
			// CRXD0: PF3 (LFQFP100: ---) (LFQFP144:  33)
				PORTF::PMR.B3 = 0;
				MPC::PF3PFS.PSEL = sel;  // ok
				PORTF::PMR.B3 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rspi0_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b0'1101 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RSPCKA: P24 (LFQFP100:  65) (LFQFP144:  94)
			// MOSIA:  P23 (LFQFP100:  66) (LFQFP144:  95)
			// MISOA:  P22 (LFQFP100:  67) (LFQFP144:  96)
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = sel;  // ok
				PORT2::PMR.B4 = enable;
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;  // ok
				PORT2::PMR.B3 = enable;
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;  // ok
				PORT2::PMR.B2 = enable;
				break;
			case ORDER::SECOND:
			// RSPCKA: PB3 (LFQFP100:  32) (LFQFP144:  47)
			// MOSIA:  PB0 (LFQFP100:  35) (LFQFP144:  50)
			// MISOA:  PA5 (LFQFP100:  36) (LFQFP144:  53)
				PORTB::PMR.B3 = 0;
				MPC::PB3PFS.PSEL = sel;  // ok
				PORTB::PMR.B3 = enable;
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
				PORTA::PMR.B5 = 0;
				MPC::PA5PFS.PSEL = sel;  // ok
				PORTA::PMR.B5 = enable;
				break;
			case ORDER::THIRD:
			// RSPCKA: PD0 (LFQFP100:  25) (LFQFP144:  32)
			// MOSIA:  PD2 (LFQFP100:  23) (LFQFP144:  30)
			// MISOA:  PD1 (LFQFP100:  24) (LFQFP144:  31)
				PORTD::PMR.B0 = 0;
				MPC::PD0PFS.PSEL = sel;  // ok
				PORTD::PMR.B0 = enable;
				PORTD::PMR.B2 = 0;
				MPC::PD2PFS.PSEL = sel;  // ok
				PORTD::PMR.B2 = enable;
				PORTD::PMR.B1 = 0;
				MPC::PD1PFS.PSEL = sel;  // ok
				PORTD::PMR.B1 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rspi0_ssl_(RSPI ssl, ORDER odr, bool enable) noexcept
		{
			bool ret = true;
			uint8_t sel = enable ? 0b00'1101 : 0;  // ok
			switch(ssl) {
			case RSPI::SSL0:
				// SSLA0: P30 (LFQFP100:  63) (LFQFP144:  90)
				// SSLA0: PA3 (LFQFP100:  38) (LFQFP144:  55)
				// SSLA0: PD6 (LFQFP100:  19) (LFQFP144:  26)
				if(odr == ORDER::FIRST) {
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = sel;
					PORT3::PMR.B0 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = sel;
					PORTA::PMR.B3 = enable;
				} else if(odr == ORDER::THIRD) {
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;
					PORTD::PMR.B6 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL1:
				// SSLA1: P31 (LFQFP100:  61) (LFQFP144:  87)
				// SSLA1: PA2 (LFQFP100:  39) (LFQFP144:  56)
				// SSLA1: PD7 (LFQFP100:  18) (LFQFP144:  25)
				if(odr == ORDER::FIRST) {
					PORT3::PMR.B1 = 0;
					MPC::P31PFS.PSEL = sel;
					PORT3::PMR.B1 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = sel;
					PORTA::PMR.B2 = enable;
				} else if(odr == ORDER::THIRD) {
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;
					PORTD::PMR.B7 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL2:
				// SSLA2: P32 (LFQFP100:  59) (LFQFP144:  84)
				// SSLA2: PA1 (LFQFP100:  40) (LFQFP144:  57)
				// SSLA2: PE0 (LFQFP100:  17) (LFQFP144:  24)
				if(odr == ORDER::FIRST) {
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;
					PORT3::PMR.B2 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;
					PORTA::PMR.B1 = enable;
				} else if(odr == ORDER::THIRD) {
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = sel;
					PORTE::PMR.B0 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL3:
				// SSLA3: P33 (LFQFP100:  58) (LFQFP144:  83)
				// SSLA3: PA0 (LFQFP100:  41) (LFQFP144:  58)
				// SSLA3: PE1 (LFQFP100:  16) (LFQFP144:  23)
				if(odr == ORDER::FIRST) {
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;
					PORT3::PMR.B3 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;
					PORTA::PMR.B0 = enable;
				} else if(odr == ORDER::THIRD) {
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = sel;
					PORTE::PMR.B1 = enable;
				} else {
					ret = false;
				}
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static inline USER_FUNC_TYPE	user_func_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  ユーザー設定関数設定
			@param[in]	func	ユーザー設定関数
		*/
		//-----------------------------------------------------------------//
		static void set_user_func(USER_FUNC_TYPE func) noexcept { user_func_ = func; }


		//-----------------------------------------------------------------//
		/*!
			@brief  RSPIx/SSL ポート有効／無効
			@param[in]	per		周辺機器タイプ
			@param[in]	ssl		SSLx 選択
			@param[in]	ena		無効にする場合「false」
			@param[in]	odr		候補を選択する場合
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral per, RSPI ssl, bool ena = true, ORDER odr = ORDER::FIRST) noexcept
		{
			if(odr == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			if(per == peripheral::RSPI0) {
				ret = rspi0_ssl_(ssl, odr, ena);
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  周辺機器別ポート切り替え
			@param[in]	per		周辺機器タイプ
			@param[in]	ena		無効にする場合「false」
			@param[in]	odr		候補を選択する場合
			@param[in]	opt		オプショナル設定を行う場合
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral per, bool ena = true, ORDER odr = ORDER::FIRST, OPTIONAL opt = OPTIONAL::NONE) noexcept
		{
			if(odr == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			if(odr == ORDER::USER) {
				ret = user_func_(per, ena);
			} else {
				switch(per) {
				case peripheral::SCI1:
					ret = sci1_(odr, ena, opt);
					break;
				case peripheral::SCI5:
					ret = sci5_(odr, ena, opt);
					break;
				case peripheral::SCI6:
					ret = sci6_(odr, ena, opt);
					break;
				case peripheral::SCI8:
					ret = sci8_(odr, ena, opt);
					break;
				case peripheral::SCI9:
					ret = sci9_(odr, ena, opt);
					break;
				case peripheral::SCI11:
					ret = sci11_(odr, ena, opt);
					break;
				case peripheral::RIIC0:
					ret = riic0_(odr, ena);
					break;
				case peripheral::RSCAN:
					ret = rscan_(odr, ena);
					break;
				case peripheral::RSPI0:
					ret = rspi0_(odr, ena);
					break;
				default:
					break;
				}
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
