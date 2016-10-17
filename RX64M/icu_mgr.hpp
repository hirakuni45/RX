#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M グループ・割り込みマネージャー @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "RX64M/icu.hpp"
#include "RX64M/peripheral.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  割り込みマネージャー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct intr_mgr {

		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みを設定する
			@param[in]	t	周辺機器タイプ
			@param[in]	lvl	割り込みレベル（０の場合、割り込み禁止）
		*/
		//-----------------------------------------------------------------//
		static void set_level(peripheral t, uint8_t lvl)
		{
			bool ena = lvl != 0 ? true : false;
			switch(t) {
			case peripheral::SCI0:
				ICU::IPR.RXI0 = lvl;
				ICU::IER.RXI0 = ena;
				ICU::IPR.TXI0 = lvl;
				ICU::IER.TXI0 = ena;
				break;
			case peripheral::SCI1:
				ICU::IPR.RXI1 = lvl;
				ICU::IER.RXI1 = ena;
				ICU::IPR.TXI1 = lvl;
				ICU::IER.TXI1 = ena;
				break;
			case peripheral::SCI2:
				ICU::IPR.RXI2 = lvl;
				ICU::IER.RXI2 = ena;
				ICU::IPR.TXI2 = lvl;
				ICU::IER.TXI2 = ena;
				break;
			case peripheral::SCI3:
				ICU::IPR.RXI3 = lvl;
				ICU::IER.RXI3 = ena;
				ICU::IPR.TXI3 = lvl;
				ICU::IER.TXI3 = ena;
				break;
			case peripheral::SCI4:
				ICU::IPR.RXI4 = lvl;
				ICU::IER.RXI4 = ena;
				ICU::IPR.TXI4 = lvl;
				ICU::IER.TXI4 = ena;
				break;
			case peripheral::SCI5:
				ICU::IPR.RXI5 = lvl;
				ICU::IER.RXI5 = ena;
				ICU::IPR.TXI5 = lvl;
				ICU::IER.TXI5 = ena;
				break;
			case peripheral::SCI6:
				ICU::IPR.RXI6 = lvl;
				ICU::IER.RXI6 = ena;
				ICU::IPR.TXI6 = lvl;
				ICU::IER.TXI6 = ena;
				break;
			case peripheral::SCI7:
				ICU::IPR.RXI7 = lvl;
				ICU::IER.RXI7 = ena;
				ICU::IPR.TXI7 = lvl;
				ICU::IER.TXI7 = ena;
				break;
			default:
				break;
			}
		}
	};
}
