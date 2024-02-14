#pragma once
//=========================================================================//
/*!	@file
	@brief	RX220 グループ・ポート・マッピング
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX220/peripheral.hpp"
#include "RX220/port.hpp"
#include "RX220/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX220 ポート・マッピング・ユーティリティー
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
			case peripheral::RIIC0:
				{
					// SCL0: P16 (LQFP64:18)
					// SDA0: P17 (LQFP64:17)
					uint8_t sel = enable ? 0b0'1111 : 0;  // ok
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;
					PORT1::PMR.B6 = enable;
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B7 = enable;
				}
				break;
			case peripheral::RSPI0:
				{
					// RSPCKA: PA5
					// MOSIA:  PA6
					// MISOA:  PA7
					uint8_t sel = enable ? 0b0'1101 : 0;  // ok
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;
					PORTA::PMR.B5 = enable;
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = sel;
					PORTA::PMR.B6 = enable;
					PORTA::PMR.B7 = 0;
					MPC::PA7PFS.PSEL = sel;
					PORTA::PMR.B7 = enable;
				}
				break;
			case peripheral::SCI1:
				{
					// RXD1: P15 (LQFP64:19)
					// TXD1: P16 (LQFP64:18)
					// SCK1: P17
					uint8_t sel = enable ? 0b0'1010 : 0;  // ok
					PORT1::PMR.B5 = 0;
					PORT1::ODR.B5 = i2c;
					MPC::P15PFS.PSEL = sel;
					PORT1::PMR.B5 = enable;
					PORT1::PMR.B6 = 0;
					PORT1::ODR.B6 = i2c;
					MPC::P16PFS.PSEL = sel;
					PORT1::PMR.B6 = enable;
					if(spi) {
						PORT1::PMR.B7 = 0;
						MPC::P17PFS.PSEL = sel;
						PORT1::PMR.B7 = enable;
					}
				}
				break;
			case peripheral::SCI5:
			case peripheral::IrDA:
				{
					// RXD5: PA2
					// TXD5: PA4
					// SCK5: PA1
					uint8_t sel = enable ? 0b0'1010 : 0;  // ok
					PORTA::PMR.B2 = 0;
					PORTA::ODR.B2 = i2c;
					MPC::PA2PFS.PSEL = sel;
					PORTA::PMR.B2 = enable;
					PORTA::PMR.B4 = 0;
					PORTA::ODR.B4 = i2c;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B4 = enable;
					if(spi) {
						PORTA::PMR.B1 = 0;
						MPC::PA1PFS.PSEL = sel;
						PORTA::PMR.B1 = enable;
					}
				}
				break;
			case peripheral::SCI6:
				{
					// RXD6: P33
					// TXD6: P32
					// SCK6: P34
					uint8_t sel = enable ? 0b0'1011 : 0;  // ok
					PORT3::PMR.B3 = 0;
					PORT3::ODR.B3 = i2c;
					MPC::P33PFS.PSEL = sel;
					PORT3::PMR.B3 = enable;
					PORT3::PMR.B2 = 0;
					PORT3::ODR.B2 = i2c;
					MPC::P32PFS.PSEL = sel;
					PORT3::PMR.B2 = enable;
					if(spi) {
						PORT3::PMR.B4 = 0;
						MPC::P34PFS.PSEL = sel;
						PORT3::PMR.B4 = enable;
					}
				}
				break;
			case peripheral::SCI9:
				{
					// RXD9: PB6
					// TXD9: PB7
					// SCK9: PB5
					uint8_t sel = enable ? 0b0'1010 : 0;  // ok
					PORTB::PMR.B6 = 0;
					PORTB::ODR.B6 = i2c;
					MPC::PB6PFS.PSEL = sel;
					PORTB::PMR.B6 = enable;
					PORTB::PMR.B7 = 0;
					PORTB::ODR.B7 = i2c;
					MPC::PB7PFS.PSEL = sel;
					PORTB::PMR.B7 = enable;
					if(spi) {
						PORTB::PMR.B5 = 0;
						MPC::PB5PFS.PSEL = sel;
						PORTB::PMR.B5 = enable;
					}
				}
				break;
			case peripheral::SCI12:
				{
					// RXD12: PE2
					// TXD12: PE1
					// SCK12: PE0
					uint8_t sel = enable ? 0b0'1100 : 0;  // ok
					PORTE::PMR.B2 = 0;
					PORTE::ODR.B2 = i2c;
					MPC::PE2PFS.PSEL = sel;
					PORTE::PMR.B2 = enable;
					PORTE::PMR.B1 = 0;
					PORTE::ODR.B1 = i2c;
					MPC::PE1PFS.PSEL = sel;
					PORTE::PMR.B1 = enable;
					if(spi) {
						PORTE::PMR.B0 = 0;
						MPC::PE0PFS.PSEL = sel;
						PORTE::PMR.B0 = enable;
					}
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
			case peripheral::RIIC0:
				{
					// SCL0: P12
					// SDA0: P13
					uint8_t sel = enable ? 0b0'1111 : 0;  // ok
					PORT1::PMR.B2 = 0;
					MPC::P12PFS.PSEL = sel;
					PORT1::PMR.B2 = enable;
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;
					PORT1::PMR.B3 = enable;
				}
				break;

			case peripheral::RSPI0:
				{
					// RSPCKA: PB0
					// MOSIA:  P16
					// MISOA:  P17
					uint8_t sel = enable ? 0b0'1101 : 0;  // ok
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;
					PORTB::PMR.B0 = enable;
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;
					PORT1::PMR.B6 = enable;
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B7 = enable;
				}
				break;

			case peripheral::SCI1:  // for BOOT serial port
				{
					// RXD1: P30
					// TXD1: P26
					// SCK1: P27
					uint8_t sel = enable ? 0b0'1010 : 0;  // ok
					PORT3::PMR.B0 = 0;
					PORT3::ODR.B0 = i2c;
					MPC::P30PFS.PSEL = sel;
					PORT3::PMR.B0 = enable;
					PORT2::PMR.B6 = 0;
					PORT2::ODR.B6 = i2c;
					MPC::P26PFS.PSEL = sel;
					PORT2::PMR.B6 = enable;
					if(spi) {
						PORT2::PMR.B7 = 0;
						MPC::P27PFS.PSEL = sel;
						PORT2::PMR.B7 = enable;
					}
				}
				break;
			case peripheral::SCI5:
			case peripheral::IrDA:
				{
					// RXD5: PA3
					// TXD5: PA4
					// SCK5: PA1
					uint8_t sel = enable ? 0b0'1010 : 0;  // ok
					PORTA::PMR.B3 = 0;
					PORTA::ODR.B3 = i2c;
					MPC::PA3PFS.PSEL = sel;
					PORTA::PMR.B3 = enable;
					PORTA::PMR.B4 = 0;
					PORTA::ODR.B4 = i2c;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B4 = enable;
					if(spi) {
						PORTA::PMR.B1 = 0;
						MPC::PA1PFS.PSEL = sel;
						PORTA::PMR.B1 = enable;
					}
				}
				break;
			case peripheral::SCI6:
				{
					// RXD6: PB0
					// TXD6: PB1
					// SCK6: PB3
					uint8_t sel = enable ? 0b0'1011 : 0;
					PORTB::PMR.B0 = 0;
					PORTB::ODR.B0 = i2c;
					MPC::PB0PFS.PSEL = sel;
					PORTB::PMR.B0 = enable;
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
			case peripheral::RSPI0:
				{
					// RSPCKA: PC5
					// MOSIA:  PC6
					// MISOA:  PC7
					uint8_t sel = enable ? 0b0'1101 : 0;
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;
					PORTC::PMR.B5 = enable;
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;
					PORTC::PMR.B6 = enable;
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;
					PORTC::PMR.B7 = enable;
				}
				break;

			case peripheral::SCI5:
			case peripheral::IrDA:
				{
					// RXD5: PC2
					// TXD5: PC3
					// SCK5: PC4
					uint8_t sel = enable ? 0b0'1010 : 0;  // ok
					PORTA::PMR.B3 = 0;
					PORTA::ODR.B3 = i2c;
					MPC::PA3PFS.PSEL = sel;
					PORTA::PMR.B3 = enable;
					PORTA::PMR.B4 = 0;
					PORTA::ODR.B4 = i2c;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B4 = enable;
					if(spi) {
						PORTC::PMR.B4 = 0;
						MPC::PC4PFS.PSEL = sel;
						PORTC::PMR.B4 = enable;
					}
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
				ret = false;
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
