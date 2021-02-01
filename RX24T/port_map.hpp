#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・ポート・マッピング @n
			コメントのピン番号は、LQFP100 パッケージの場合
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX24T/peripheral.hpp"
#include "RX600/port.hpp"
#include "RX24T/mpc.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ポート・マッピング・オプション型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class option : uint8_t {
			BYPASS,		///< ポートマップの設定をバイパスする場合
			FIRST,		///< 第１候補 (XXX-A グループ)
			SECOND,		///< 第２候補 (XXX-B グループ)
			THIRD,		///< 第３候補
			FORCE,		///< 第４候補
			FIRST_I2C,	///< SCI ポートを簡易 I2C として使う場合、第１候補
			SECOND_I2C,	///< SCI ポートを簡易 I2C として使う場合、第２候補
			THIRD_I2C,	///< SCI ポートを簡易 I2C として使う場合、第３候補
			FIRST_SPI,	///< SCI ポートを簡易 SPI として使う場合、第１候補
			SECOND_SPI,	///< SCI ポートを簡易 SPI として使う場合、第２候補
			THIRD_SPI,	///< SCI ポートを簡易 SPI として使う場合、第３候補
		};

	private:

		static bool sub_1st_(peripheral t, bool enable) noexcept
		{
			switch(t) {

			case peripheral::CAN0:  // Only Version B
				{
					uint8_t sel = enable ? 0b10000 : 0;
					PORTA::PMR.B0 = 0;
					PORTA::PMR.B1 = 0;
					MPC::PA0PFS.PSEL = sel;  // PA0/CTXD0 (41/100)
					MPC::PA1PFS.PSEL = sel;  // PA1/CRXD0 (40/100)
					PORTA::PMR.B0 = enable;
					PORTA::PMR.B1 = enable;
				}
				break;

			case peripheral::RIIC0:
				{
					uint8_t sel = enable ? 0b01111 : 0;
					PORTB::PMR.B1 = 0;
					PORTB::PMR.B2 = 0;
					MPC::PB1PFS.PSEL = sel;  // PB1/SCL0 (34/100)
					MPC::PB2PFS.PSEL = sel;  // PB2/SDA0 (33/100)
					PORTB::PMR.B1 = enable;
					PORTB::PMR.B2 = enable;
				}
				break;

			case peripheral::RSPI0:
				{
					uint8_t sel = enable ? 0b01101 : 0;
					PORT2::PMR.B2 = 0;
					PORT2::PMR.B3 = 0;
					PORT2::PMR.B4 = 0;
					MPC::P22PFS.PSEL = sel;  // P22/MISOA  (66/100)
					MPC::P23PFS.PSEL = sel;  // P23/MOSIA  (65/100)
					MPC::P24PFS.PSEL = sel;  // P24/RSPCKA (64/100)
					PORT2::PMR.B2 = enable;
					PORT2::PMR.B3 = enable;
					PORT2::PMR.B4 = enable;
				}
				break;

			case peripheral::SCI1C:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;  // PD4/SCK1 (21/100)
					PORTD::PMR.B4 = enable;
				}
			case peripheral::SCI1:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					PORTD::PMR.B3 = 0;
					PORTD::PMR.B5 = 0;
					MPC::PD3PFS.PSEL = sel;  // PD3/TXD1 (22/100)
					MPC::PD5PFS.PSEL = sel;  // PD5/RXD1 (20/100)
					PORTD::PMR.B3 = enable;
					PORTD::PMR.B5 = enable;
				}
				break;

			case peripheral::SCI5C:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;  // PB7/SCK5 (26/100)
					PORTB::PMR.B7 = enable;
				}
			case peripheral::SCI5:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					PORTB::PMR.B5 = 0;
					PORTB::PMR.B6 = 0;
					MPC::PB5PFS.PSEL = sel;  // PB5/TXD5 (28/100)
					MPC::PB6PFS.PSEL = sel;  // PB6/RXD5 (27/100)
					PORTB::PMR.B5 = enable;
					PORTB::PMR.B6 = enable;
				}
				break;

			case peripheral::SCI6C:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;  // PA4/SCK6 (37/100)
					PORTA::PMR.B4 = enable;
				}
			case peripheral::SCI6:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					PORTB::PMR.B0 = 0;
					PORTA::PMR.B5 = 0;
					MPC::PB0PFS.PSEL = sel;  // PB0/TXD6 (35/100)
					MPC::PA5PFS.PSEL = sel;  // PA5/RXD6 (36/100)
					PORTB::PMR.B0 = enable;
					PORTA::PMR.B5 = enable;
				}
				break;

			default:
				return false;
				break;
			}
			return true;
		}


		static bool sub_2nd_(peripheral t, bool enable) noexcept
		{
			switch(t) {
//			case peripheral::SCI5C:
//				{
//					uint8_t sel = enable ? 0b01010 : 0;
//					MPC::PB7PFS.PSEL = sel;  // PB7/SCK5 (26/100)
//					PORTB::PMR.B7 = enable;
//				}
			case peripheral::SCI5:  // Version B device only
				{
					uint8_t sel = enable ? 0b01010 : 0;
					PORTE::PMR.B0 = 0;
					PORTD::PMR.B7 = 0;
					MPC::PE0PFS.PSEL = sel;  // PE0/TXD5 (17/100)
					MPC::PD7PFS.PSEL = sel;  // PD7/RXD5 (18/100)
					PORTE::PMR.B0 = enable;
					PORTD::PMR.B7 = enable;
				}
				break;

			case peripheral::SCI6C:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;  // PB3/SCK6 (32/100)
					PORTB::PMR.B3 = enable;
				}
			case peripheral::SCI6:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					PORTB::PMR.B2 = 0;
					PORTB::PMR.B1 = 0;
					MPC::PB2PFS.PSEL = sel;  // PB2/TXD6 (33/100)
					MPC::PB1PFS.PSEL = sel;  // PB1/RXD6 (34/100)
					PORTB::PMR.B2 = enable;
					PORTB::PMR.B1 = enable;
				}
				break;

			default:
				return false;
				break;
			}
			return true;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  周辺機器別ポート切り替え
			@param[in]	t	周辺機器タイプ
			@param[in]	f	無効にする場合「false」
			@param[in]	opt	候補を選択する場合
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral t, bool f = true, option opt = option::FIRST) noexcept
		{
			if(opt == option::BYPASS) return false;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			if(opt == option::FIRST) {
				ret = sub_1st_(t, f);
			} else if(opt == option::SECOND) {
				ret = sub_2nd_(t, f);
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}

	};
}
