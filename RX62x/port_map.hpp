#pragma once
//=============================================================================//
/*!	@file
	@brief	RX621/RX62N グループ・ポート・マッピング @n
			このマイコンは、初期のデザインな為、ポートをアサインする仕組みにおいて @n
			かなり制限された機能しかありません、その為、他のシリーズと異なる挙動と @n
			なる場合があるので、注意を要します。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "RX62x/peripheral.hpp"
#include "RX62x/port.hpp"
#include "RX62x/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX621/RX62N ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map : public port_map_order {

		static bool sci0_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:
			//	RxD0: P21 (LFQFP144:  36)
			//	TxD0: P20 (LFQFP144:  37)
			//	SCK0: P22 (LFQFP144:  35)
				PORT2::ICR.B1 = enable;  ///< RxD0
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sci1_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:
			//	RxD1-A: P30 (LFQFP144:  29)
			//	TxD1-A: P26 (LFQFP144:  31)
			//	SCK1-A: P27 (LFQFP144:  30)
				MPC::PFFSCI.SCI1S = 0;
				PORT3::ICR.B0 = enable;  ///< RxD1-A
				break;
			case ORDER::SECOND:
			//	RxD1-B: PF2 (LFQFP144: ---)
			//	TxD1-B: PF0 (LFQFP144: ---)
			//	SCK1-B: PF1 (LFQFP144: ---)
				MPC::PFFSCI.SCI1S = 1;
				PORTF::ICR.B2 = enable;  ///< RxD1-B
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sci2_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:
			//	RxD2-A: P12 (LFQFP144:  45)
			//	TxD2-A: P13 (LFQFP144:  44)
			//	SCK2-A: P11 (LFQFP144: ---)
				MPC::PFFSCI.SCI2S = 0;
				PORT1::ICR.B2 = enable;  ///< RxD2-A
				break;
			case ORDER::SECOND:
			//	RxD2-B: P52 (LFQFP144:  54)
			//	TxD2-B: P50 (LFQFP144:  56)
			//	SCK2-B: P51 (LFQFP144:  55)
				MPC::PFFSCI.SCI2S = 1;
				PORT5::ICR.B2 = enable;  ///< RxD2-B
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sci3_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:
			//	RxD3-A: P16 (LFQFP144:  40)
			//	TxD3-A: P17 (LFQFP144:  38)
			//	SCK3-A: P15 (LFQFP144:  42)
				MPC::PFFSCI.SCI3S = 0;
				PORT1::ICR.B6 = enable;  ///< RxD3-A
				break;
			case ORDER::SECOND:
			//	RxD3-B: P25 (LFQFP144:  32)
			//	TxD3-B: P23 (LFQFP144:  34)
			//	SCK3-B: P24 (LFQFP144:  33)
				MPC::PFFSCI.SCI3S = 1;
				PORT2::ICR.B5 = enable;  ///< RxD3-B
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sci5_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:
			//	RxD5: PC2 (LFQFP144:  70)
			//	TxD5: PC3 (LFQFP144:  67)
			//	SCK5: PC1 (LFQFP144:  73)
				PORTC::ICR.B2 = enable;  ///< RxD5
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sci6_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:
			//	RxD6-A: P01 (LFQFP144:   7)
			//	TxD6-A: P00 (LFQFP144:   8)
			//	SCK6-A: P02 (LFQFP144:   6)
				MPC::PFFSCI.SCI6S = 0;
				PORT0::ICR.B1 = enable;  ///< RxD6-A
				break;
			case ORDER::SECOND:
			//	RxD6-B: P33 (LFQFP144:  26)
			//	TxD6-B: P32 (LFQFP144:  27)
			//	SCK6-B: P34 (LFQFP144:  25)
				MPC::PFFSCI.SCI6S = 1;
				PORT3::ICR.B3 = enable;  ///< RxD6-B
				break;
			default:
				return false;
			}
			return true;
		}

		static bool riic0_(ORDER odr, bool enable) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:
			// SCL0: P12 (LFQFP144:  45)
			// SDA0: P13 (LFQFP144:  44)
				// 設定は特に無し（SCL/SDA 入出力として扱う）
				break;
			default:
				return false;
			}
			return true;
		}

		static bool riic1_(ORDER odr, bool enable) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:
			// SCL1: P21 (LFQFP144:  36)
			// SDA1: P20 (LFQFP144:  37)
				// 設定は特に無し（SCL/SDA 入出力として扱う）
				break;
			default:
				return false;
			}
			return true;
		}

		static bool can0_(ORDER odr, bool enable) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:
			// CRX0: P33 (LFQFP144:  26)
			// CTX0: P32 (LFQFP144:  27)
				MPC::PFJCAN.CAN0E = enable;
				PORT3::ICR.B3 =  enable;
				PORT3::ICR.B2 = !enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rspi0_(ORDER odr, bool enable) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:
			// RSPCKA-A: PC5 (LFQFP144:  62)
			// MOSIA-A:  PC6 (LFQFP144:  61)
			// MISOA-A:  PC7 (LFQFP144:  60)
				MPC::PFGSPI.RSPIS = 0;
				MPC::PFGSPI.RSPCKE = enable;
				MPC::PFGSPI.MOSIE = enable;
				MPC::PFGSPI.MISOE = enable;
				break;
			case ORDER::SECOND:
			// RSPCKA-B: PA5 (LFQFP144:  90)
			// MOSIA-B:  PA6 (LFQFP144:  89)
			// MISOA-B:  PA7 (LFQFP144:  88)
				MPC::PFGSPI.RSPIS = 1;
				MPC::PFGSPI.RSPCKE = enable;
				MPC::PFGSPI.MOSIE = enable;
				MPC::PFGSPI.MISOE = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rspi0_ssl_(RSPI ssl, ORDER odr, bool enable) noexcept
		{
			bool ret = true;
			switch(ssl) {
			case RSPI::SSL0:
			// SSLA0: PC4 (LFQFP144:  66)
			// SSLA0: PA4 (LFQFP144:  92)
				if(odr == ORDER::FIRST) {
					MPC::PFGSPI.RSPIS = 0;
					MPC::PFGSPI.SSL0E = enable;
				} else if(odr == ORDER::SECOND) {
					MPC::PFGSPI.RSPIS = 1;
					MPC::PFGSPI.SSL0E = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL1:
			// SSLA1: PC0 (LFQFP144:  75)
			// SSLA1: PA0 (LFQFP144:  97)
				if(odr == ORDER::FIRST) {
					MPC::PFGSPI.RSPIS = 0;
					MPC::PFGSPI.SSL1E = enable;
				} else if(odr == ORDER::SECOND) {
					MPC::PFGSPI.RSPIS = 1;
					MPC::PFGSPI.SSL1E = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL2:
			// SSLA2: PC1 (LFQFP144:  73)
			// SSLA2: PA1 (LFQFP144:  96)
				if(odr == ORDER::FIRST) {
					MPC::PFGSPI.RSPIS = 0;
					MPC::PFGSPI.SSL2E = enable;
				} else if(odr == ORDER::SECOND) {
					MPC::PFGSPI.RSPIS = 1;
					MPC::PFGSPI.SSL2E = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL3:
			// SSLA3: PC2 (LFQFP144:  70)
			// SSLA3: PA2 (LFQFP144:  95)
				if(odr == ORDER::FIRST) {
					MPC::PFGSPI.RSPIS = 0;
					MPC::PFGSPI.SSL3E = enable;
				} else if(odr == ORDER::SECOND) {
					MPC::PFGSPI.RSPIS = 1;
					MPC::PFGSPI.SSL3E = enable;
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

		static bool rspi1_(ORDER odr, bool enable) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:
			// RSPCKB-A: P27 (LFQFP144:  30)
			// MOSIB-A:  P26 (LFQFP144:  31)
			// MISOB-A:  P30 (LFQFP144:  29)
				MPC::PFHSPI.RSPIS = 0;
				MPC::PFHSPI.RSPCKE = enable;
				MPC::PFHSPI.MOSIE = enable;
				MPC::PFHSPI.MISOE = enable;
				break;
			case ORDER::SECOND:
			// RSPCKB-B: PE5 (LFQFP144: 106)
			// MOSIB-B:  PE6 (LFQFP144: 102)
			// MISOB-B:  PE7 (LFQFP144: 101)
				MPC::PFHSPI.RSPIS = 1; 
				MPC::PFHSPI.RSPCKE = enable;
				MPC::PFHSPI.MOSIE = enable;
				MPC::PFHSPI.MISOE = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rspi1_ssl_(RSPI ssl, ORDER odr, bool enable) noexcept
		{
			bool ret = true;
			switch(ssl) {
			case RSPI::SSL0:
			// SSLB0: P31 (LFQFP144:  28)
			// SSLB0: PE4 (LFQFP144: 107)
				if(odr == ORDER::FIRST) {
					MPC::PFHSPI.RSPIS = 0;
					MPC::PFHSPI.SSL0E = enable;
				} else if(odr == ORDER::SECOND) {
					MPC::PFHSPI.RSPIS = 1;
					MPC::PFHSPI.SSL0E = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL1:
			// SSLB1: P50 (LFQFP144:  56)
			// SSLB1: PE0 (LFQFP144: 111)
				if(odr == ORDER::FIRST) {
					MPC::PFHSPI.RSPIS = 0;
					MPC::PFHSPI.SSL1E = enable;
				} else if(odr == ORDER::SECOND) {
					MPC::PFHSPI.RSPIS = 1;
					MPC::PFHSPI.SSL1E = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL2:
			// SSLA2: P51 (LFQFP144:  55)
			// SSLA2: PE1 (LFQFP144: 110)
				if(odr == ORDER::FIRST) {
					MPC::PFHSPI.RSPIS = 0;
					MPC::PFHSPI.SSL2E = enable;
				} else if(odr == ORDER::SECOND) {
					MPC::PFHSPI.RSPIS = 1;
					MPC::PFHSPI.SSL2E = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL3:
			// SSLA3: P52 (LFQFP144:  54)
			// SSLA3: PE2 (LFQFP144: 109)
				if(odr == ORDER::FIRST) {
					MPC::PFHSPI.RSPIS = 0;
					MPC::PFHSPI.SSL3E = enable;
				} else if(odr == ORDER::SECOND) {
					MPC::PFHSPI.RSPIS = 1;
					MPC::PFHSPI.SSL3E = enable;
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

		static bool etherc_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:
			// RMII/MII Ethernet
				if(opt == OPTIONAL::ETH_RMII) {
					MPC::PFENET.PHYMODE = 0;
				} else if(opt == OPTIONAL::ETH_MII) {
					MPC::PFENET.PHYMODE = 0;
				} else {
					return false;
				}
				MPC::PFENET.EE = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		//----------------------------------------------------------------

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

			bool ret = false;
			if(per == peripheral::RSPI0) {
				ret = rspi0_ssl_(ssl, odr, ena);
			} else if(per == peripheral::RSPI1) {
				ret = rspi1_ssl_(ssl, odr, ena);
			}

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
			if(odr == ORDER::BYPASS) return false;

			bool ret = false;
			if(odr == ORDER::USER) {
				ret = user_func_(per, ena);
			} else {
				switch(per) {
				case peripheral::SCI0:
					ret = sci0_(odr, ena, opt);
					break;
				case peripheral::SCI1:
					ret = sci1_(odr, ena, opt);
					break;
				case peripheral::SCI2:
					ret = sci2_(odr, ena, opt);
					break;
				case peripheral::SCI3:
					ret = sci3_(odr, ena, opt);
					break;
				case peripheral::SCI5:
					ret = sci5_(odr, ena, opt);
					break;
				case peripheral::SCI6:
					ret = sci6_(odr, ena, opt);
					break;
				case peripheral::RIIC0:
					ret = riic0_(odr, ena);
					break;
				case peripheral::RIIC1:
					ret = riic1_(odr, ena);
					break;
				case peripheral::RSPI0:
					ret = rspi0_(odr, ena);
					break;
				case peripheral::RSPI1:
					ret = rspi1_(odr, ena);
					break;
				case peripheral::CAN:
					ret = can0_(odr, ena);
					break;
				case peripheral::ETHERC:
					ret = etherc_(odr, ena, opt);
					break;
				default:
					break;
				}
			}

			return ret;
		}
	};
}
