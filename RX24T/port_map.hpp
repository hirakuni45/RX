#pragma once
//=========================================================================//
/*!	@file
	@brief	RX13T/RX24T/RX24U グループ・ポート・マッピング @n
			コメントのピン番号は、LQFP100 パッケージの場合
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#if defined(SIG_RX13T)
#include "RX13T/peripheral.hpp"
#include "RX13T/port.hpp"
#elif defined(SIG_RX24T)
#include "RX24T/peripheral.hpp"
#include "RX24T/port.hpp"
#elif defined(SIG_RX24U)
#include "RX24U/peripheral.hpp"
#include "RX24T/port.hpp"
#endif
#include "RX24T/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX24T ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map : public port_map_order {

		static bool sub_1st_(peripheral per, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			switch(per) {
			case peripheral::RSCAN:  // Only Version B
				{
					// CTXD0: PA0 (41/100)
					// CRXD0: PA1 (40/100)
					uint8_t sel = enable ? 0b1'0000 : 0;  // ok
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;
					PORTA::PMR.B0 = enable;
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;
					PORTA::PMR.B1 = enable;
				}
				break;

			case peripheral::SCI1:  // for Serial BOOT interface
				{
					// RXD1: PD5
					// TXD1: PD3
					// SCK1: PD4
					uint8_t sel = enable ? 0b0'1010 : 0;  // ok
					PORTD::PMR.B5 = 0;
					PORTD::ODR.B5 = i2c;
					MPC::PD5PFS.PSEL = sel;
					PORTD::PMR.B5 = enable;
					PORTD::PMR.B3 = 0;
					PORTD::ODR.B3 = i2c;
					MPC::PD3PFS.PSEL = sel;
					PORTD::PMR.B3 = enable;
					if(spi) {
						PORTD::PMR.B4 = 0;
						MPC::PD4PFS.PSEL = sel;
						PORTD::PMR.B4 = enable;
					}
				}
				break;

			case peripheral::SCI5:
				{
					// RXD5: PB6
					// TXD5: PB5
					// SCK5: PB7
					uint8_t sel = enable ? 0b0'1010 : 0;  // ok
					PORTB::PMR.B6 = 0;
					PORTB::ODR.B6 = i2c;
					MPC::PB6PFS.PSEL = sel;
					PORTB::PMR.B6 = enable;
					PORTB::PMR.B5 = 0;
					PORTB::ODR.B5 = i2c;
					MPC::PB5PFS.PSEL = sel;
					PORTB::PMR.B5 = enable;
					if(spi) {
						PORTB::PMR.B7 = 0;
						MPC::PB7PFS.PSEL = sel;
						PORTB::PMR.B7 = enable;
					}
				}
				break;

			case peripheral::SCI6:
				{
					// RXD6: P80
					// TXD6: P81
					// SCK6: P82
					uint8_t sel = enable ? 0b0'1010 : 0;  // ok
					PORT8::PMR.B0 = 0;
					PORT8::ODR.B0 = i2c;
					MPC::P80PFS.PSEL = sel;
					PORT8::PMR.B0 = enable;
					PORT8::PMR.B1 = 0;
					PORT8::ODR.B1 = i2c;
					MPC::P81PFS.PSEL = sel;
					PORT8::PMR.B1 = enable;
					if(spi) {
						PORT8::PMR.B2 = 0;
						MPC::P82PFS.PSEL = sel;
						PORT8::PMR.B2 = enable;
					}
				}
				break;

			case peripheral::RIIC0:
				{
					// SCL0: PB1 (34/100)
					// SDA0: PB2 (33/100)
					uint8_t sel = enable ? 0b0'1111 : 0;  // ok
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;  
					PORTB::PMR.B1 = enable;
					PORTB::PMR.B2 = 0;
					MPC::PB2PFS.PSEL = sel;
					PORTB::PMR.B2 = enable;
				}
				break;

			case peripheral::RSPI0:
				{
					// RSPCKA: P24 (64/100)
					// MOSIA:  P23 (65/100)
					// MISOA:  P22 (66/100)
					uint8_t sel = enable ? 0b0'1101 : 0;  // ok
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;
					PORT2::PMR.B4 = enable;
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;
					PORT2::PMR.B3 = enable;
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;
					PORT2::PMR.B2 = enable;
				}
				break;

			default:
				return false;
				break;
			}
			return true;
		}


		static bool sub_2nd_(peripheral per, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			switch(per) {
			case peripheral::SCI5:  // Only B Version
				{
					// RXD5: PE0
					// TXD5: PD7
					// SCK5: PD2
					uint8_t sel = enable ? 0b0'1010 : 0;  // ok
					PORTE::PMR.B0 = 0;
					PORTE::ODR.B0 = i2c;
					MPC::PE0PFS.PSEL = sel;
					PORTE::PMR.B0 = enable;
					PORTD::PMR.B7 = 0;
					PORTD::ODR.B7 = i2c;
					MPC::PD7PFS.PSEL = sel;
					PORTD::PMR.B7 = enable;
					if(spi) {
						PORTD::PMR.B2 = 0;
						MPC::PD2PFS.PSEL = sel;
						PORTD::PMR.B2 = enable;
					}
				}
				break;

			case peripheral::SCI6:
				{
					// RXD6: PA5
					// TXD6: PB0
					// SCK6: PA4
					uint8_t sel = enable ? 0b0'1010 : 0;  // ok
					PORTA::PMR.B5 = 0;
					PORTA::ODR.B5 = i2c;
					MPC::PA5PFS.PSEL = sel;
					PORTA::PMR.B5 = enable;
					PORTB::PMR.B0 = 0;
					PORTB::ODR.B0 = i2c;
					MPC::PB0PFS.PSEL = sel;
					PORTB::PMR.B0 = enable;
					if(spi) {
						PORTA::PMR.B4 = 0;
						MPC::PA4PFS.PSEL = sel;
						PORTA::PMR.B4 = enable;
					}
				}
				break;

			case peripheral::RSPI0:
				{
					// RSPCKA: PB3
					// MOSIA:  PB0
					// MISOA:  PA5
					uint8_t sel = enable ? 0b0'1101 : 0;  // ok
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;
					PORTB::PMR.B3 = enable;
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;
					PORTB::PMR.B0 = enable;
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;
					PORTA::PMR.B5 = enable;
				}
				break;

			default:
				return false;
				break;
			}
			return true;
		}


		static bool sub_3rd_(peripheral per, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			switch(per) {
			case peripheral::SCI6:
				{
					// RXD6: PB1
					// TXD6: PB2
					// SCK6: PB3
					uint8_t sel = enable ? 0b0'1010 : 0;  // ok
					PORTB::PMR.B2 = 0;
					PORTB::ODR.B2 = i2c;
					MPC::PB2PFS.PSEL = sel;
					PORTB::PMR.B2 = enable;
					PORTB::PMR.B1 = 0;
					PORTB::ODR.B1 = i2c;
					MPC::PB1PFS.PSEL = sel;
					PORTB::PMR.B1 = enable;
					if(spi) {
						PORTB::PMR.B3 = 0;
						MPC::PB3PFS.PSEL = sel;
						PORTB::PMR.B3 = enable;
					}
				}
				break;

			case peripheral::RSPI0:
				{
					// RSPCKA: PD0
					// MOSIA:  PD2
					// MISOA:  PD1
					uint8_t sel = enable ? 0b0'1101 : 0;  // ok
					PORTD::PMR.B0 = 0;
					MPC::PD0PFS.PSEL = sel;
					PORTD::PMR.B0 = enable;
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;
					PORTD::PMR.B2 = enable;
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;
					PORTD::PMR.B1 = enable;
				}
				break;
			default:
				return false;
				break;
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
			switch(odr) {
			case ORDER::FIRST:
				ret = sub_1st_(per, ena, opt);
				break;
			case ORDER::SECOND:
				ret = sub_2nd_(per, ena, opt);
				break;
			case ORDER::THIRD:
				ret = sub_3rd_(per, ena, opt);
				break;
			case ORDER::USER:
				ret = user_func_(per, ena);
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}

	};
}
