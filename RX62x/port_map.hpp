#pragma once
//=========================================================================//
/*!	@file
	@brief	RX621/RX62N グループ・ポート・マッピング @n
			このマイコンは、初期のデザインな為、ポートをアサインする仕組みにおいて @n
			かなり制限された機能しかありません、その為、他のシリーズと異なる挙動と @n
			なる場合があるので、注意を要します。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX62x/peripheral.hpp"
#include "RX62x/port.hpp"
#include "RX62x/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX621/RX62N ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map : public port_map_order {

		static bool sub_1st_(peripheral t, bool enable) noexcept
		{
			switch(t) {
			///	SCK0:   P22
			///	TxD0:   P20
			///	RxD0:   P21
			case peripheral::SCI0:
				PORT2::ICR.B1 = enable;  ///< RxD0
				break;
			///	SCK1-A: P27
			///	TxD1-A: P26
			///	RxD1-A: P30
			case peripheral::SCI1:
				MPC::PFFSCI.SCI1S = 0;
				PORT3::ICR.B0 = enable;  ///< RxD1-A
				break;
			///	SCK2-A: P11
			///	TxD2-A: P13
			///	RxD2-A: P12
			case peripheral::SCI2:
				MPC::PFFSCI.SCI2S = 0;
				PORT1::ICR.B2 = enable;  ///< RxD2-A
				break;
			///	SCK3-A: P15
			///	TxD3-A: P17
			///	RxD3-A: P16
			case peripheral::SCI3:
				MPC::PFFSCI.SCI3S = 0;
				PORT1::ICR.B6 = enable;  ///< RxD3-A
				break;
			///	SCK5:   PC1
			///	TxD5:   PC3
			///	RxD5:   PC2
			case peripheral::SCI5:
				PORTC::ICR.B2 = enable;  ///< RxD5
				break;
			///	SCK6-A: P02
			///	TxD6-A: P00
			///	RxD6-A: P01
			case peripheral::SCI6:
				MPC::PFFSCI.SCI6S = 0;
				PORT0::ICR.B1 = enable;  ///< RxD6-A
				break;

			/// SCL0: P12
			/// SDA0: P13
			case peripheral::RIIC0:
				// 設定は特に無し（SCL/SDA 入出力として扱う）
				break;
			/// SCL1: P21
			/// SDA1: P20
			case peripheral::RIIC1:
				// 設定は特に無し（SCL/SDA 入出力として扱う）
				break;

			/// RSPCKA-A: PC5
			/// MOSIA-A:  PC6
			/// MISOA-A:  PC7
			case peripheral::RSPI0:
				MPC::PFGSPI.RSPIS = 0;
				MPC::PFGSPI.RSPCKE = enable;
				MPC::PFGSPI.MOSIE = enable;
				MPC::PFGSPI.MISOE = enable;
				break;
			/// RSPCKB-A: P27
			/// MOSIB-A:  P26
			/// MISOB-A:  P30
			case peripheral::RSPI1:
				MPC::PFHSPI.RSPIS = 0;
				MPC::PFHSPI.RSPCKE = enable;
				MPC::PFHSPI.MOSIE = enable;
				MPC::PFHSPI.MISOE = enable;
				break;

			/// CTX0: P32
			/// CRX0: P33
			case peripheral::CAN:
				MPC::PFJCAN.CAN0E = enable;
				PORT3::ICR.B3 = enable;  ///< CRX0
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
			///	SCK1-B: PF1
			///	TxD1-B: PF0
			///	RxD1-B: PF2
			case peripheral::SCI1:
				MPC::PFFSCI.SCI1S = 1;
				PORTF::ICR.B2 = enable;  ///< RxD1-B
				break;
			///	SCK2-B: P51
			///	TxD2-B: P50 
			///	RxD2-B: P52
			case peripheral::SCI2:
				MPC::PFFSCI.SCI2S = 1;
				PORT5::ICR.B2 = enable;  ///< RxD2-B
				break;
			///	SCK3-B: P24
			///	TxD3-B: P23
			///	RxD3-B: P25
			case peripheral::SCI3:
				MPC::PFFSCI.SCI3S = 1;
				PORT2::ICR.B5 = enable;  ///< RxD3-B
				break;
			///	SCK6-B: P34
			///	TxD6-B: P32
			///	RxD6-B: P33
			case peripheral::SCI6:
				MPC::PFFSCI.SCI6S = 1;
				PORT3::ICR.B3 = enable;  ///< RxD6-B
				break;

			/// RSPCKA-B: PA5
			/// MOSIA-B:  PA6
			/// MISOA-B:  PA7
			case peripheral::RSPI0:
				MPC::PFGSPI.RSPIS = 1;
				MPC::PFGSPI.RSPCKE = enable;
				MPC::PFGSPI.MOSIE = enable;
				MPC::PFGSPI.MISOE = enable;
				break;
			/// RSPCKB-B: PE5
			/// MOSIB-B:  PE6
			/// MISOB-B:  PE7
			case peripheral::RSPI1:
				MPC::PFHSPI.RSPIS = 1; 
				MPC::PFHSPI.RSPCKE = enable;
				MPC::PFHSPI.MOSIE = enable;
				MPC::PFHSPI.MISOE = enable;
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
			if(odr == ORDER::BYPASS) return false;

			bool ret = false;
			switch(odr) {
			case ORDER::FIRST:
				ret = sub_1st_(per, ena);
				break;
			case ORDER::SECOND:
				ret = sub_2nd_(per, ena);
				break;
			case ORDER::USER:
				ret = user_func_(per, ena);
				break;
			default:
				break;
			}

			return ret;
		}
	};
}
