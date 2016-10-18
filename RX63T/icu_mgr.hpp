#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63T グループ・割り込みマネージャー @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "RX63T/icu.hpp"
#include "RX63T/peripheral.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  割り込みマネージャー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct icu_mgr {

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
				ICU::IPR.SCI0 = lvl;
				ICU::IER.RXI0 = ena;
				ICU::IER.TXI0 = ena;
				break;
			case peripheral::SCI1:
				ICU::IPR.SCI1 = lvl;
				ICU::IER.RXI1 = ena;
				ICU::IER.TXI1 = ena;
				break;
			case peripheral::SCI2:
				ICU::IPR.SCI2 = lvl;
				ICU::IER.RXI2 = ena;
				ICU::IER.TXI2 = ena;
				break;
			case peripheral::SCI3:
				ICU::IPR.SCI3 = lvl;
				ICU::IER.RXI3 = ena;
				ICU::IER.TXI3 = ena;
				break;
			case peripheral::CMT0:
				ICU::IPR.CMI0 = lvl;
				ICU::IER.CMI0 = ena;
				break;
			case peripheral::CMT1:
				ICU::IPR.CMI1 = lvl;
				ICU::IER.CMI1 = ena;
				break;
			default:
				break;
			}
		}
	};
}
