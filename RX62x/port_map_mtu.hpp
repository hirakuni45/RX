#pragma once
//=========================================================================//
/*!	@file
	@brief	RX621/RX62N グループ・ポート・マッピング (MTU2 系)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX62x/peripheral.hpp"
#include "RX62x/port.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_mtu : public port_map_order {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマー系・クロック・グループ @n
					※タイマーのクロック系は、MTU 共通なので、識別子としてグループを使う
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GROUP : uint8_t {
			MTU0,	///< MTU0 系グループ
			MTU1,	///< MTU1 系グループ
			MTU2,	///< MTU2 系グループ
			MTU3,	///< MTU3 系グループ
			MTU4,	///< MTU4 系グループ
			MTU5,	///< MTU5 系グループ
			MTU6,	///< MTU6 系グループ
			MTU7,	///< MTU7 系グループ
			NONE,	///< 無効なグループ
		};

	private:

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  MTU2 関係、チャネル別ポート切り替え
			@param[in]	t	周辺機器タイプ
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合場合「false」
			@param[in]	odr	候補を選択する場合
			@param[in]	neg	反転機能を使う場合「true」
			@param[in]	inp	入力端子として利用する場合「true」
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral t, CHANNEL ch, bool ena = true, ORDER odr = ORDER::FIRST, bool neg = false, bool inp = false) noexcept
		{
			if(odr == ORDER::BYPASS) return true;

			if(neg) return false;

			bool ret = true;
			switch(t) {
			case peripheral::MTU0:
				switch(ch) {
				case CHANNEL::A:  // P34
					PORT3::ICR.B4 = inp;
					break;
				case CHANNEL::B:  // P15
					PORT1::ICR.B5 = inp;
					break;
				case CHANNEL::C:  // P32
					PORT3::ICR.B2 = inp;
					break;
				case CHANNEL::D:  // P33
					PORT3::ICR.B3 = inp;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU1:
				switch(ch) {
				case CHANNEL::A:  // P20
					PORT2::ICR.B0 = inp;
					break;
				case CHANNEL::B:  // P21
					PORT2::ICR.B1 = inp;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU2:
				switch(ch) {
				case CHANNEL::A:  // P26
					PORT2::ICR.B6 = inp;
					break;
				case CHANNEL::B:  // P27
					PORT2::ICR.B7 = inp;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU3:
				switch(ch) {
				case CHANNEL::A:  // P17
					PORT1::ICR.B7 = inp;
					break;
				case CHANNEL::B:  // P22(FIRST), P80(SECOND)
					MPC::PFCMTU.MTUS3 = (odr != ORDER::FIRST);
					PORT2::ICR.B2 = inp;
					break;
				case CHANNEL::C:  // P16(FIRST), P56(SECOND)
					MPC::PFCMTU.MTUS2 = (odr != ORDER::FIRST);
					PORT1::ICR.B6 = inp;
					break;
				case CHANNEL::D:  // P23(FIRST)、P81(SECOND)
					MPC::PFCMTU.MTUS3 = (odr != ORDER::FIRST);
					PORT2::ICR.B3 = inp;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU4:
				switch(ch) {
				case CHANNEL::A:  // P24(FIRST), P82(SECOND)
					MPC::PFCMTU.MTUS4 = (odr != ORDER::FIRST);
					PORT2::ICR.B4 = inp;
					break;
				case CHANNEL::B:  // P30(FIRST), P54(SECOND)
					MPC::PFCMTU.MTUS5 = (odr != ORDER::FIRST);
					PORT3::ICR.B0 = inp;
					break;
				case CHANNEL::C:  // P25(FIRST), P83(SECOND)
					MPC::PFCMTU.MTUS4 = (odr != ORDER::FIRST);
					PORT2::ICR.B5 = inp;
					break;
				case CHANNEL::D:  // P31(FIRST), P55(SECOND)
					MPC::PFCMTU.MTUS5 = (odr != ORDER::FIRST);
					PORT3::ICR.B1 = inp;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU5:
				switch(ch) {
				case CHANNEL::U:  // P12(FIRST), PD7(SECOND)
					MPC::PFCMTU.MTUS6 = (odr != ORDER::FIRST);
					PORT1::ICR.B2 = inp;
					break;
				case CHANNEL::V:  // P11(FIRST), PD6(SECOND)
					MPC::PFCMTU.MTUS6 = (odr != ORDER::FIRST);
					PORT1::ICR.B1 = inp;
					break;
				case CHANNEL::W:  // P10(FIRST), PD5(SECOND)
					MPC::PFCMTU.MTUS6 = (odr != ORDER::FIRST);
					PORT1::ICR.B0 = inp;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU6:
				switch(ch) {
				case CHANNEL::A:  // PA0
					PORTA::ICR.B0 = inp;
					break;
				case CHANNEL::B:  // PA1
					PORTA::ICR.B1 = inp;
					break;
				case CHANNEL::C:  // PA2
					PORTA::ICR.B2 = inp;
					break;
				case CHANNEL::D:  // PA3
					PORTA::ICR.B3 = inp;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU7:
				switch(ch) {
				case CHANNEL::A:  // PA4
					PORTA::ICR.B4 = inp;
					break;
				case CHANNEL::B:  // PA5
					PORTA::ICR.B5 = inp;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU8:
				switch(ch) {
				case CHANNEL::A:  // PA6
					PORTA::ICR.B6 = inp;
					break;
				case CHANNEL::B:  // PA7
					PORTA::ICR.B7 = inp;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU9:
				switch(ch) {
				case CHANNEL::A:  // PB0
					PORTB::ICR.B0 = inp;
					break;
				case CHANNEL::B:  // PB2
					PORTB::ICR.B2 = inp;
					break;
				case CHANNEL::C:  // PB1
					PORTB::ICR.B1 = inp;
					break;
				case CHANNEL::D:  // PB3
					PORTB::ICR.B3 = inp;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU10:
				switch(ch) {
				case CHANNEL::A:  // PB4
					PORTB::ICR.B4 = inp;
					break;
				case CHANNEL::B:  // PB6
					PORTB::ICR.B6 = inp;
					break;
				case CHANNEL::C:  // PB5
					PORTB::ICR.B5 = inp;
					break;
				case CHANNEL::D:  // PB7
					PORTB::ICR.B7 = inp;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU11:
				switch(ch) {
				case CHANNEL::U:  // PC7(FIRST), PD4(SECOND)
					MPC::PFDMTU.MTUS6 = (odr != ORDER::FIRST);
					PORTC::ICR.B7 = inp;
					break;
				case CHANNEL::V:  // PC6(FIRST), PD3(SECOND)
					MPC::PFDMTU.MTUS6 = (odr != ORDER::FIRST);
					PORTC::ICR.B6 = inp;
					break;
				case CHANNEL::W:  // PC5(FIRST), PD2(SECOND)
					MPC::PFDMTU.MTUS6 = (odr != ORDER::FIRST);
					PORTC::ICR.B5 = inp;
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマー系、クロックポート切り替え
			@param[in]	grp	チャネル・グループ
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合場合「false」
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn_clock(GROUP grp, CHANNEL ch, bool ena = true) noexcept
		{
			bool ret = true;

			return ret;
		}
	};
}

