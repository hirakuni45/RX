#pragma once
//=========================================================================//
/*!	@file
	@brief	RX140 グループ・ポート・マッピング
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX140/peripheral.hpp"
#include "RX140/port.hpp"
#include "RX140/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX140 ポート・マッピング・ユーティリティー
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
			case ORDER::FIRST:
				// RXD1: P15 (LFQFP48: 15) (LFQFP64: 19) (LFQFP80: 25)
				// TXD1: P16 (LFQFP48: 14) (LFQFP64: 18) (LFQFP80: 24)
				// SCK1: P17 (LFQFP48: 13) (LFQFP64: 17) (LFQFP80: 23)
				PORT1::PMR.B5 = 0;
				PORT1::ODR.B5 = i2c;
				MPC::P15PFS.PSEL = sel;  // ok
				PORT1::PMR.B5 = enable;
				PORT1::PMR.B6 = 0;
				PORT1::ODR.B6 = i2c;
				MPC::P16PFS.PSEL = sel;  // ok
				PORT1::PMR.B6 = enable;
				if(spi) {
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;  // ok
					PORT1::PMR.B7 = enable;
				}
				break;
			case ORDER::SECOND:  // for BOOT serial port
				// RXD1: P30 (LFQFP48: 10) (LFQFP64: 14) (LFQFP80: 18)
				// TXD1: P26 (LFQFP48: 12) (LFQFP64: 16) (LFQFP80: 20)
				// SCK1: P27 (LFQFP48: 11) (LFQFP64: 15) (LFQFP80: 19)
				PORT3::PMR.B0 = 0;
				PORT3::ODR.B0 = i2c;
				MPC::P30PFS.PSEL = sel;  // ok
				PORT3::PMR.B0 = enable;
				PORT2::PMR.B6 = 0;
				PORT2::ODR.B6 = i2c;
				MPC::P26PFS.PSEL = sel;  // ok
				PORT2::PMR.B6 = enable;
				if(spi) {
					PORT2::PMR.B7 = 0;
					MPC::P27PFS.PSEL = sel;  // ok
					PORT2::PMR.B7 = enable;
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
				// RXD5: PA2 (LFQFP48: --) (LFQFP64: --) (LFQFP80: 55)
				// TXD5: PA4 (LFQFP48: 32) (LFQFP64: 42) (LFQFP80: 53)
				// SCK5: PA1 (LFQFP48: 34) (LFQFP64: 44) (LFQFP80: 56)
				PORTA::PMR.B2 = 0;
				PORTA::ODR.B2 = i2c;
				MPC::PA2PFS.PSEL = sel;  // ok
				PORTA::PMR.B2 = enable;
				PORTA::PMR.B4 = 0;
				PORTA::ODR.B4 = i2c;
				MPC::PA4PFS.PSEL = sel;  // ok
				PORTA::PMR.B4 = enable;
				if(spi) {
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;  // ok
					PORTA::PMR.B1 = enable;
				}
				break;
			case ORDER::SECOND:
				// RXD5: PA3 (LFQFP48: 33) (LFQFP64: 43) (LFQFP80: 54)
				// TXD5: PA4 (LFQFP48: 32) (LFQFP64: 42) (LFQFP80: 53)
				// SCK5: PA1 (LFQFP48: 34) (LFQFP64: 44) (LFQFP80: 56)
				PORTA::PMR.B3 = 0;
				PORTA::ODR.B3 = i2c;
				MPC::PA3PFS.PSEL = sel;  // ok
				PORTA::PMR.B3 = enable;
				PORTA::PMR.B4 = 0;
				PORTA::ODR.B4 = i2c;
				MPC::PA4PFS.PSEL = sel;  // ok
				PORTA::PMR.B4 = enable;
				if(spi) {
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;  // ok
					PORTA::PMR.B1 = enable;
				}
				break;
			case ORDER::THIRD:
				// RXD5: PC2 (LFQFP48: 26) (LFQFP64: 32) (LFQFP80: 40)
				// TXD5: PC3 (LFQFP48: 25) (LFQFP64: 31) (LFQFP80: 39)
				// SCK5: PC4 (LFQFP48: 24) (LFQFP64: 30) (LFQFP80: 38)
				PORTA::PMR.B3 = 0;
				PORTA::ODR.B3 = i2c;
				MPC::PA3PFS.PSEL = sel;  // ok
				PORTA::PMR.B3 = enable;
				PORTA::PMR.B4 = 0;
				PORTA::ODR.B4 = i2c;
				MPC::PA4PFS.PSEL = sel;  // ok
				PORTA::PMR.B4 = enable;
				if(spi) {
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;  // ok
					PORTC::PMR.B4 = enable;
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
			uint8_t sel = enable ? 0b0'1011 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD6: PB0 (LFQFP48: 29) (LFQFP64: 39) (LFQFP80: 49)
				// TXD6: PB1 (LFQFP48: 27) (LFQFP64: 37) (LFQFP80: 47)
				// SCK6: PB3 (LFQFP48: 26) (LFQFP64: 36) (LFQFP80: 45)
				PORTB::PMR.B0 = 0;
				PORTB::ODR.B0 = i2c;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
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
			case ORDER::SECOND:
				// RXD6: PD1 (LFQFP48: --) (LFQFP64: --) (LFQFP80: 65)
				// TXD6: PD0 (LFQFP48: --) (LFQFP64: --) (LFQFP80: 66)
				// SCK6: PD2 (LFQFP48: --) (LFQFP64: --) (LFQFP80: 64)
				PORTD::PMR.B1 = 0;
				PORTD::ODR.B1 = i2c;
				MPC::PD1PFS.PSEL = sel;  // ok
				PORTD::PMR.B1 = enable;
				PORTD::PMR.B0 = 0;
				PORTD::ODR.B0 = i2c;
				MPC::PD0PFS.PSEL = sel;  // ok
				PORTD::PMR.B0 = enable;
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

		static bool sci8_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD8: PC6 (LFQFP48: 22) (LFQFP64: 28) (LFQFP80: 36)
				// TXD8: PC7 (LFQFP48: 21) (LFQFP64: 27) (LFQFP80: 35)
				// SCK8: PC5 (LFQFP48: 23) (LFQFP64: 29) (LFQFP80: 37)
				PORTC::PMR.B6 = 0;
				PORTC::ODR.B6 = i2c;
				MPC::PC6PFS.PSEL = sel;  // ok
				PORTC::PMR.B6 = enable;
				PORTC::PMR.B7 = 0;
				PORTC::ODR.B7 = i2c;
				MPC::PC7PFS.PSEL = sel;  // ok
				PORTC::PMR.B7 = enable;
				if(spi) {
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;  // ok
					PORTC::PMR.B5 = enable;
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
				// RXD9: PB6 (LFQFP48: --) (LFQFP64: 34) (LFQFP80: 42)
				// TXD9: PB7 (LFQFP48: --) (LFQFP64: 33) (LFQFP80: 41)
				// SCK9: PB5 (LFQFP48: 25) (LFQFP64: 35) (LFQFP80: 43)
				PORTB::PMR.B6 = 0;
				PORTB::ODR.B6 = i2c;
				MPC::PB6PFS.PSEL = sel;  // ok
				PORTB::PMR.B6 = enable;
				PORTB::PMR.B7 = 0;
				PORTB::ODR.B7 = i2c;
				MPC::PB7PFS.PSEL = sel;  // ok
				PORTB::PMR.B7 = enable;
				if(spi) {
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = sel;  // ok
					PORTB::PMR.B5 = enable;
				}
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sci12_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1100 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD12: PE2 (LFQFP48: 37) (LFQFP64: 49) (LFQFP80: 61)
				// TXD12: PE1 (LFQFP48: 38) (LFQFP64: 50) (LFQFP80: 62)
				// SCK12: PE0 (LFQFP48: --) (LFQFP64: 51) (LFQFP80: 63)
				PORTE::PMR.B2 = 0;
				PORTE::ODR.B2 = i2c;
				MPC::PE2PFS.PSEL = sel;  // ok
				PORTE::PMR.B2 = enable;
				PORTE::PMR.B1 = 0;
				PORTE::ODR.B1 = i2c;
				MPC::PE1PFS.PSEL = sel;  // ok
				PORTE::PMR.B1 = enable;
				if(spi) {
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = sel;  // ok
					PORTE::PMR.B0 = enable;
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
				// SCL0: P16 (LFQFP48: 14) (LFQFP64: 18) (LFQFP80: 24)
				// SDA0: P17 (LFQFP48: 13) (LFQFP64: 17) (LFQFP80: 23)
				PORT1::PMR.B6 = 0;
				MPC::P16PFS.PSEL = sel;  // ok
				PORT1::PMR.B6 = enable;
				PORT1::PMR.B7 = 0;
				MPC::P17PFS.PSEL = sel;  // ok
				PORT1::PMR.B7 = enable;
				break;
			case ORDER::SECOND:
				// SCL0: P12 (LFQFP48: --) (LFQFP64: --) (LFQFP80: 28)
				// SDA0: P13 (LFQFP48: --) (LFQFP64: --) (LFQFP80: 27)
				PORT1::PMR.B2 = 0;
				MPC::P12PFS.PSEL = sel;  // ok
				PORT1::PMR.B2 = enable;
				PORT1::PMR.B3 = 0;
				MPC::P13PFS.PSEL = sel;  // ok
				PORT1::PMR.B3 = enable;
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
			case ORDER::FIRST:
				// CRXD0: P15 (LFQFP48: 15) (LFQFP64: 19) (LFQFP80: 25)
				// CTXD0: P14 (LFQFP48: 16) (LFQFP64: 20) (LFQFP80: 26)
				PORT1::PMR.B5 = 0;
				MPC::P15PFS.PSEL = sel;  // ok
				PORT1::PMR.B5 = enable;
				PORT1::PMR.B4 = 0;
				MPC::P14PFS.PSEL = sel;  // ok
				PORT1::PMR.B4 = enable;
				break;
			case ORDER::SECOND:
				// CRXD0: P55 (LFQFP48: --) (LFQFP64: --) (LFQFP80: 33)
				// CTXD0: P54 (LFQFP48: --) (LFQFP64: --) (LFQFP80: 34)
				PORT5::PMR.B5 = 0;
				MPC::P55PFS.PSEL = sel;  // ok
				PORT5::PMR.B5 = enable;
				PORT5::PMR.B4 = 0;
				MPC::P54PFS.PSEL = sel;  // ok
				PORT5::PMR.B4 = enable;
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
				// RSPCKA: PA5 (LFQFP48: --) (LFQFP64: --) (LFQFP80: 52)
				// MOSIA:  PA6 (LFQFP48: 31) (LFQFP64: 41) (LFQFP80: 51)
				// MISOA:  PC7 (LFQFP48: 21) (LFQFP64: 27) (LFQFP80: 35)
				PORTA::PMR.B5 = 0;
				MPC::PA5PFS.PSEL = sel;  // ok
				PORTA::PMR.B5 = enable;
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = sel;  // ok
				PORTA::PMR.B6 = enable;
				PORTC::PMR.B7 = 0;
				MPC::PC7PFS.PSEL = sel;  // ok
				PORTC::PMR.B7 = enable;
				break;
			case ORDER::SECOND:
				// RSPCKA: PB0 (LFQFP48: 29) (LFQFP64: 39) (LFQFP80: 49)
				// MOSIA:  P16 (LFQFP48: 14) (LFQFP64: 18) (LFQFP80: 24)
				// MISOA:  P17 (LFQFP48: 13) (LFQFP64: 17) (LFQFP80: 23)
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
				PORT1::PMR.B6 = 0;
				MPC::P16PFS.PSEL = sel;  // ok
				PORT1::PMR.B6 = enable;
				PORT1::PMR.B7 = 0;		
				MPC::P17PFS.PSEL = sel;  // ok
				PORT1::PMR.B7 = enable;
				break;
			case ORDER::THIRD:
				// RSPCKA: PC5 (LFQFP48: 23) (LFQFP64: 29) (LFQFP80: 37)
				// MOSIA:  PC6 (LFQFP48: 22) (LFQFP64: 28) (LFQFP80: 36)
				// MISOA:  PC7 (LFQFP48: 21) (LFQFP64: 27) (LFQFP80: 35)
				PORTC::PMR.B5 = 0;
				MPC::PC5PFS.PSEL = sel;  // ok
				PORTC::PMR.B5 = enable;
				PORTC::PMR.B6 = 0;
				MPC::PC6PFS.PSEL = sel;  // ok
				PORTC::PMR.B6 = enable;
				PORTC::PMR.B7 = 0;
				MPC::PC7PFS.PSEL = sel;  // ok
				PORTC::PMR.B7 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rspi0_ssl_(RSPI ssl, ORDER odr, bool enable) noexcept
		{
			bool ret = true;
			uint8_t sel = enable ? 0b0'1101 : 0;  // ok
			switch(ssl) {
			case RSPI::SSL0:
				// SSLA0: PA4 (LFQFP48: 32) (LFQFP64: 42) (LFQFP80: 53)
				// SSLA0: PC4 (LFQFP48: 24) (LFQFP64: 30) (LFQFP80: 38)
				if(odr == ORDER::FIRST) {
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B4 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;
					PORTC::PMR.B4 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL1:
				// SSLA1: PA0 (LFQFP48: --) (LFQFP64: 45) (LFQFP80: 57)
				if(odr == ORDER::FIRST) {
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;
					PORTA::PMR.B0 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL2:
				// SSLA2: PA1 (LFQFP48: 34) (LFQFP64: 44) (LFQFP80: 56)
				if(odr == ORDER::FIRST) {
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;
					PORTA::PMR.B1 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL3:
				// SSLA3: PA2 (LFQFP48: --) (LFQFP64: --) (LFQFP80: 55)
				// SSLA3: PC2 (LFQFP48: 26) (LFQFP64: 32) (LFQFP80: 40)
				if(odr == ORDER::FIRST) {
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = sel;
					PORTA::PMR.B2 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = sel;
					PORTC::PMR.B2 = enable;
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

		static bool lpt_(ORDER odr, bool enable) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:
				// LPTO:: P26 (LFQFP48: 12) (LFQFP64: 16) (LFQFP80: 20)
				PORT2::PMR.B6 = 0;
				MPC::P26PFS.PSEL = enable ? 0b1'1011 : 0;  // ok
				PORT2::PMR.B6 = enable;
				break;
			case ORDER::SECOND:
				// LPTO:: PB3 (LFQFP48: 26) (LFQFP64: 36) (LFQFP80: 45)
				PORTB::PMR.B3 = 0;
				MPC::PB3PFS.PSEL = enable ? 0b1'1011 : 0;  // ok
				PORTB::PMR.B3 = enable;
				break;
			case ORDER::THIRD:
				// LPTO:: PC7 (LFQFP48: 21) (LFQFP64: 27) (LFQFP80: 35)
				PORTC::PMR.B7 = 0;
				MPC::PC7PFS.PSEL = enable ? 0b1'1011 : 0;  // ok
				PORTC::PMR.B7 = enable;
				break;
			default:
				return false;
			}
			return true;
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
				case peripheral::SCI12:
					ret = sci12_(odr, ena, opt);
					break;
				case peripheral::RIIC0:
					ret = riic0_(odr, ena);
					break;
				case peripheral::RSPI0:
					ret = rspi0_(odr, ena);
					break;
				case peripheral::LPT:
					ret = lpt_(odr, ena);
					break;
				case peripheral::RSCAN:
					ret = rscan_(odr, ena);
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
