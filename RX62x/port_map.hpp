#pragma once
//=====================================================================//
/*!	@file
	@brief	RX621/RX62N グループ・ポート・マッピング @n
			コメントのピン番号は、LQFP100 パッケージの場合
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX62x/peripheral.hpp"
#include "RX62x/port.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・クラス @n
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
			@param[in]	odr	候補を選択する場合
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral t, bool f = true, ORDER odr = ORDER::FIRST) noexcept
		{
			if(odr == ORDER::BYPASS) return false;

			bool ret = false;
			if(odr == ORDER::FIRST) {
				ret = sub_1st_(t, f);
			} else if(odr == ORDER::SECOND) {
				ret = sub_2nd_(t, f);
			}

			return ret;
		}

	};
}
