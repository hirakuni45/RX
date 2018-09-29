#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・ポート・マッピング @n
			コメントのピン番号は、LQFP100 パッケージの場合
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX600/port.hpp"
#include "RX24T/mpc.hpp"
#include "RX24T/peripheral.hpp"

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
			FIRST,		///< 第１候補 (XXX-A グループ)
			SECOND,		///< 第２候補 (XXX-B グループ)
			THIRD,		///< 第３候補
			FORCE,		///< 第４候補
			FIRST_I2C,	///< SCI ポートを簡易 I2C として使う場合
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  MTUx（マルチ・ファンクション・タイマ） チャネル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class channel : uint8_t {
			A,	///< MTUx A (MTIOCxA)
			B,	///< MTUx B (MTIOCxB)
			C,	///< MTUx C (MTIOCxC)
			D,	///< MTUx D (MTIOCxD)

			U,	///< MTU5 U (MTIC5U) P24
			V,	///< MTU5 V (MTIC5V) P23
			W,	///< MTU5 W (MTIC5W) P22
			U2,	///< MTU5 U (MTIC5U) P82
			V2,	///< MTU5 V (MTIC5V) P81
			W2,	///< MTU5 W (MTIC5W) P80
		};

	private:

		static bool sub_1st_(peripheral t, bool enable) noexcept
		{
			switch(t) {

			case peripheral::RIIC0:
				{
					uint8_t sel = enable ? 0b01111 : 0;
					MPC::PB1PFS.PSEL = sel;  // PB1/SCL0 (34/100)
					MPC::PB2PFS.PSEL = sel;  // PB2/SDA0 (33/100)
					PORTB::PMR.B1 = enable;
					PORTB::PMR.B2 = enable;
				}
				break;

			case peripheral::RSPI0:
				{
					uint8_t sel = enable ? 0b01101 : 0;
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
					MPC::PD4PFS.PSEL = sel;  // PD4/SCK1 (21/100)
					PORTD::PMR.B4 = enable;
				}
			case peripheral::SCI1:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PD3PFS.PSEL = sel;  // PD3/TXD1 (22/100)
					MPC::PD5PFS.PSEL = sel;  // PD5/RXD1 (20/100)
					PORTD::PMR.B3 = enable;
					PORTD::PMR.B5 = enable;
				}
				break;

			case peripheral::SCI5C:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PB7PFS.PSEL = sel;  // PB7/SCK5 (26/100)
					PORTB::PMR.B7 = enable;
				}
			case peripheral::SCI5:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PB5PFS.PSEL = sel;  // PB5/TXD5 (28/100)
					MPC::PB6PFS.PSEL = sel;  // PB6/RXD5 (27/100)
					PORTB::PMR.B5 = enable;
					PORTB::PMR.B6 = enable;
				}
				break;

			case peripheral::SCI6C:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PA4PFS.PSEL = sel;  // PA4/SCK6 (37/100)
					PORTA::PMR.B4 = enable;
				}
			case peripheral::SCI6:
				{
					uint8_t sel = enable ? 0b01010 : 0;
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
			case peripheral::SCI5:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PE0PFS.PSEL = sel;  // PE0/TXD5 (17/100)
					MPC::PD7PFS.PSEL = sel;  // PD7/RXD5 (18/100)
					PORTE::PMR.B0 = enable;
					PORTD::PMR.B7 = enable;
				}
				break;

			case peripheral::SCI6C:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PB3PFS.PSEL = sel;  // PB3/SCK6 (32/100)
					PORTB::PMR.B3 = enable;
				}
			case peripheral::SCI6:
				{
					uint8_t sel = enable ? 0b01010 : 0;
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


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマー関係、チャネル別ポート切り替え
			@param[in]	t	周辺機器タイプ
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral t, channel ch, bool ena = true) noexcept
		{
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = true;
			uint8_t sel = ena ? 0b00001 : 0;
			switch(t) {
			case peripheral::MTU0:
				switch(ch) {
				case channel::A:					
					MPC::PB3PFS.PSEL = sel;  // MTIOC0A (32/100)
					PORTB::PMR.B3 = ena;
					break;
				case channel::B:
					MPC::PB2PFS.PSEL = sel;  // MTIOC0B (33/100)
					PORTB::PMR.B2 = ena;
					break;
				case channel::C:
					MPC::PB1PFS.PSEL = sel;  // MTIOC0C (34/100)
					PORTB::PMR.B1 = ena;
					break;
				case channel::D:
					MPC::PB0PFS.PSEL = sel;  // MTIOC0D (35/100)
					PORTB::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU1:
				switch(ch) {
				case channel::A:					
					MPC::PA5PFS.PSEL = sel;  // MTIOC1A (36/100)
					PORTA::PMR.B5 = ena;
					break;
				case channel::B:
					MPC::PA4PFS.PSEL = sel;  // MTIOC1B (37/100)
					PORTA::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU2:
				switch(ch) {
				case channel::A:					
					MPC::PA3PFS.PSEL = sel;  // MTIOC2A (38/100)
					PORTA::PMR.B3 = ena;
					break;
				case channel::B:
					MPC::PA2PFS.PSEL = sel;  // MTIOC2B (39/100)
					PORTA::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU3:
				switch(ch) {
				case channel::A:					
					MPC::P33PFS.PSEL = sel;  // MTIOC3A (58/100)
					PORT3::PMR.B3 = ena;
					break;
				case channel::B:
					MPC::P71PFS.PSEL = sel;  // MTIOC3B (56/100)
					PORT7::PMR.B1 = ena;
					break;
				case channel::C:
					MPC::P32PFS.PSEL = sel;  // MTIOC3C (59/100)
					PORT3::PMR.B2 = ena;
					break;
				case channel::D:
					MPC::P74PFS.PSEL = sel;  // MTIOC3D (53/100)
					PORT7::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU4:
				switch(ch) {
				case channel::A:					
					MPC::P72PFS.PSEL = sel;  // MTIOC4A (55/100)
					PORT7::PMR.B2 = ena;
					break;
				case channel::B:
					MPC::P73PFS.PSEL = sel;  // MTIOC4B (54/100)
					PORT7::PMR.B3 = ena;
					break;
				case channel::C:
					MPC::P75PFS.PSEL = sel;  // MTIOC4C (52/100)
					PORT7::PMR.B5 = ena;
					break;
				case channel::D:
					MPC::P76PFS.PSEL = sel;  // MTIOC4D (51/100)
					PORT7::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU5:
				switch(ch) {
				case channel::U:
					MPC::P24PFS.PSEL = sel;  // MTIOC5U (64/100)
					PORT2::PMR.B4 = ena;
					break;
				case channel::V:
					MPC::P23PFS.PSEL = sel;  // MTIOC5V (65/100)
					PORT2::PMR.B3 = ena;
					break;
				case channel::W:
					MPC::P22PFS.PSEL = sel;  // MTIOC5W (66/100)
					PORT2::PMR.B2 = ena;
					break;
				case channel::U2:
					MPC::P82PFS.PSEL = sel;  // MTIOC5U (96/100)
					PORT8::PMR.B2 = ena;
					break;
				case channel::V2:
					MPC::P81PFS.PSEL = sel;  // MTIOC5V (97/100)
					PORT8::PMR.B1 = ena;
					break;
				case channel::W2:
					MPC::P80PFS.PSEL = sel;  // MTIOC5W (98/100)
					PORT8::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU6:
				switch(ch) {
				case channel::A:
					MPC::PA1PFS.PSEL = sel;  // MTIOC6A (40/100)
					PORTA::PMR.B1 = ena;
					break;
				case channel::B:
					MPC::P95PFS.PSEL = sel;  // MTIOC6B (45/100)
					PORT9::PMR.B5 = ena;
					break;
				case channel::C:
					MPC::PA0PFS.PSEL = sel;  // MTIOC6C (41/100)
					PORTA::PMR.B0 = ena;
					break;
				case channel::D:
					MPC::P92PFS.PSEL = sel;  // MTIOC6D (48/100)
					PORT9::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU7:
				switch(ch) {
				case channel::A:
					MPC::P94PFS.PSEL = sel;  // MTIOC7A (46/100)
					PORT9::PMR.B4 = ena;
					break;
				case channel::B:
					MPC::P93PFS.PSEL = sel;  // MTIOC7B (47/100)
					PORT9::PMR.B3 = ena;
					break;
				case channel::C:
					MPC::P91PFS.PSEL = sel;  // MTIOC7C (49/100)
					PORT9::PMR.B1 = ena;
					break;
				case channel::D:
					MPC::P90PFS.PSEL = sel;  // MTIOC7D (50/100)
					PORT9::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU9:
				switch(ch) {
				case channel::A:
					MPC::PD7PFS.PSEL = sel;  // MTIOC9A (18/100)
					PORTD::PMR.B7 = ena;
					break;
				case channel::B:
					MPC::PE0PFS.PSEL = sel;  // MTIOC9B (17/100)
					PORTE::PMR.B0 = ena;
					break;
				case channel::C:
					MPC::PD6PFS.PSEL = sel;  // MTIOC9C (19/100)
					PORTD::PMR.B6 = ena;
					break;
				case channel::D:
					MPC::PE1PFS.PSEL = sel;  // MTIOC9D (16/100)
					PORTE::PMR.B1 = ena;
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

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
