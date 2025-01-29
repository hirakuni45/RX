#pragma once
//=========================================================================//
/*!	@file
	@brief	RX23W グループ・ポート・マッピング
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX23W/peripheral.hpp"
#include "RX23W/port.hpp"
#include "RX23W/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX23W ポート・マッピング・ユーティリティー
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
				// RXD1: P15 (LQFP64:19)
				// TXD1: P16 (LQFP64:18)
				// SCK1: P17
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
				// RXD1: P30
				// TXD1: P26
				// SCK1: P27
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
				// RXD5: PC2
				// TXD5: PC3
				// SCK5: PC4
				PORTC::PMR.B2 = 0;
				PORTC::ODR.B2 = i2c;
				MPC::PC2PFS.PSEL = sel;  // ok
				PORTC::PMR.B2 = enable;
				PORTC::PMR.B3 = 0;
				PORTC::ODR.B3 = i2c;
				MPC::PC3PFS.PSEL = sel;  // ok
				PORTC::PMR.B3 = enable;
				if(spi) {
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;
					PORTC::PMR.B4 = enable;
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
				// RXD8: PC6
				// TXD8: PC7
				// SCK8: PC5
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

		static bool sci12_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1100 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD12: PE2
				// TXD12: PE1
				// SCK12: PE0
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
				// SCL0: P16 (LQFP64:18)
				// SDA0: P17 (LQFP64:17)
				PORT1::PMR.B6 = 0;
				MPC::P16PFS.PSEL = sel;  // ok
				PORT1::PMR.B6 = enable;
				PORT1::PMR.B7 = 0;
				MPC::P17PFS.PSEL = sel;  // ok
				PORT1::PMR.B7 = enable;
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
				// RSPCKA: PB0
				// MOSIA:  P16
				// MISOA:  P17
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
			case ORDER::SECOND:
				// RSPCKA: PC5
				// MOSIA:  PC6
				// MISOA:  PC7
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


#if 0
		static bool sdhi_1st_(SDHI_STATE state, bool wp) noexcept
		{
			// CLK: PB1
			// CMD: PB0
			// D0:  PC3
			// D1:  PB6
			// D2:  PB7
			// D3:  PC2
			// CD:  PB5
			// WP:  PB3
			bool ret = true;
			bool enable = true;
			uint8_t sel = enable ? 0b01'1010 : 0;
			switch(state) {
			case SDHI_STATE::START:
				if(wp) {
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;  // SDHI_WP
					PORTB::PMR.B3 = enable;
				}
				PORTB::PMR.B5 = 0;
				MPC::PB5PFS.PSEL = sel;  // SDHI_CD
				PORTB::PMR.B5 = enable;
				break;

			case SDHI_STATE::INSERT:
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = sel;  // SDHI_CLK
				PORTB::PMR.B1 = enable;
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // SDHI_CMD
				PORTB::PMR.B0 = enable;
				break;
			case SDHI_STATE::BUS:
				PORTC::PMR.B3 = 0;
				MPC::PC3PFS.PSEL = sel;  // SDHI_D0
				PORTC::PMR.B3 = enable;
				PORTB::PMR.B6 = 0;
				MPC::PB6PFS.PSEL = sel;  // SDHI_D1
				PORTB::PMR.B6 = enable;
				PORTB::PMR.B7 = 0;
				MPC::PB7PFS.PSEL = sel;  // SDHI_D2
				PORTB::PMR.B7 = enable;
				PORTC::PMR.B2 = 0;
				MPC::PC2PFS.PSEL = sel;  // SDHI_D3
				PORTC::PMR.B2 = enable;
				break;

			case SDHI_STATE::DESTROY:
				sel = 0;
				enable = 0;
				if(wp) {
					MPC::PB3PFS.PSEL = sel;  // SDHI_WP
					PORTB::PMR.B3 = enable;
				}
				MPC::PB5PFS.PSEL = sel;  // SDHI_CD
				PORTB::PMR.B5 = enable;
			case SDHI_STATE::EJECT:
				sel = 0;
				enable = 0;
				MPC::PB1PFS.PSEL = sel;  // SDHI_CLK
				PORTB::PMR.B1 = enable;
				MPC::PB0PFS.PSEL = sel;  // SDHI_CMD
				PORTB::PMR.B0 = enable;
				MPC::PC3PFS.PSEL = sel;  // SDHI_D0
				PORTB::PMR.B6 = enable;
				MPC::PB6PFS.PSEL = sel;  // SDHI_D1
				PORTB::PMR.B6 = enable;
				MPC::PB7PFS.PSEL = sel;  // SDHI_D2
				PORTB::PMR.B7 = enable;
				MPC::PC2PFS.PSEL = sel;  // SDHI_D3
				PORTC::PMR.B2 = enable;
				break;
			default:
				ret = false;
			}
			return ret;
		}


		static bool sdhi_2nd_(SDHI_STATE state, bool wp) noexcept
		{
			// CLK: PB1
			// CMD: PB0
			// D0:  PC3
			// D1:  PC4
			// D2:  PB7
			// D3:  PC2
			// CD:  PB5
			// WP:  PB3
			bool ret = true;
			bool enable = true;
			uint8_t sel = enable ? 0b01'1010 : 0;
			switch(state) {
			case SDHI_STATE::START:
				if(wp) {
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;  // SDHI_WP
					PORTB::PMR.B3 = enable;
				}
				PORTB::PMR.B5 = 0;
				MPC::PB5PFS.PSEL = sel;  // SDHI_CD
				PORTB::PMR.B5 = enable;
				break;

			case SDHI_STATE::INSERT:
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = sel;  // SDHI_CLK
				PORTB::PMR.B1 = enable;
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // SDHI_CMD
				PORTB::PMR.B0 = enable;
				break;
			case SDHI_STATE::BUS:
				PORTC::PMR.B3 = 0;
				MPC::PC3PFS.PSEL = sel;  // SDHI_D0
				PORTC::PMR.B3 = enable;
				PORTC::PMR.B4 = 0;
				MPC::PC4PFS.PSEL = sel;  // SDHI_D1
				PORTC::PMR.B4 = enable;
				PORTB::PMR.B7 = 0;
				MPC::PB7PFS.PSEL = sel;  // SDHI_D2
				PORTB::PMR.B7 = enable;
				PORTC::PMR.B2 = 0;
				MPC::PC2PFS.PSEL = sel;  // SDHI_D3
				PORTC::PMR.B2 = enable;
				break;

			case SDHI_STATE::DESTROY:
				sel = 0;
				enable = 0;
				if(wp) {
					MPC::PB3PFS.PSEL = sel;  // SDHI_WP
					PORTB::PMR.B3 = enable;
				}
				MPC::PB5PFS.PSEL = sel;  // SDHI_CD
				PORTB::PMR.B5 = enable;
			case SDHI_STATE::EJECT:
				sel = 0;
				enable = 0;
				MPC::PB1PFS.PSEL = sel;  // SDHI_CLK
				PORTB::PMR.B1 = enable;
				MPC::PB0PFS.PSEL = sel;  // SDHI_CMD
				PORTB::PMR.B0 = enable;
				MPC::PC3PFS.PSEL = sel;  // SDHI_D0
				PORTC::PMR.B3 = enable;
				MPC::PC4PFS.PSEL = sel;  // SDHI_D1
				PORTC::PMR.B4 = enable;
				MPC::PB7PFS.PSEL = sel;  // SDHI_D2
				PORTB::PMR.B7 = enable;
				MPC::PC2PFS.PSEL = sel;  // SDHI_D3
				PORTC::PMR.B2 = enable;
				break;

			default:
				ret = false;
			}
			return ret;
		}
#endif
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
				case peripheral::SCI8:
					ret = sci8_(odr, ena, opt);
					break;
				case peripheral::SCI12:
					ret = sci12_(odr, ena, opt);
					break;
				case peripheral::IrDA:
					ret = sci5_(odr, ena, OPTIONAL::NONE);
					break;
				case peripheral::RIIC0:
					ret = riic0_(odr, ena);
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


		//-----------------------------------------------------------------//
		/*!
			@brief  SDHI ポート専用切り替え
			@param[in]	state	SHDI シチュエーション
			@param[in]	odr		ポート・マップ・オーダー
			@param[in]	wp		WP 端子を利用する場合「true」
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn_sdhi(SDHI_STATE state, ORDER odr = ORDER::FIRST, bool wp = false) noexcept
		{
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = 0;
			switch(odr) {
			case ORDER::FIRST:
//				ret = sdhi_1st_(state, wp);
				break;
			case ORDER::SECOND:
//				ret = sdhi_2nd_(state, wp);
				break;
			default:
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  SDHI クロック・ポートの状態を取得
			@param[in]	odr		ポート・マップ・オーダー
			@return SDHI クロック・ポートの状態
		*/
		//-----------------------------------------------------------------//
		static bool probe_sdhi_clock(ORDER odr) noexcept
		{
			bool ret = 0;
			switch(odr) {
			case ORDER::FIRST:
				ret = PORTB::PIDR.B1();
				break;
			default:
				break;
			}
			return ret;
		}
	};
}
