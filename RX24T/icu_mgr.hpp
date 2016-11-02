#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・割り込みマネージャー @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "RX24T/icu.hpp"
#include "RX24T/peripheral.hpp"

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
			case peripheral::CMT0:
				ICU::IPR.CMI0 = lvl;
				ICU::IER.CMI0 = ena;
				break;
			case peripheral::CMT1:
				ICU::IPR.CMI1 = lvl;
				ICU::IER.CMI1 = ena;
				break;

			case peripheral::RSPI0:
				ICU::IPR.RSPI0 = lvl;
				ICU::IER.SPRI0 = ena;
				ICU::IER.SPTI0 = ena;
				break;

			case peripheral::SCI1:
				ICU::IPR.SCI1 = lvl;
				ICU::IER.RXI1 = ena;
				ICU::IER.TXI1 = ena;
				break;
			case peripheral::SCI5:
				ICU::IPR.SCI5 = lvl;
				ICU::IER.RXI5 = ena;
				ICU::IER.TXI5 = ena;
				break;
			case peripheral::SCI6:
				ICU::IPR.SCI6 = lvl;
				ICU::IER.RXI6 = ena;
				ICU::IER.TXI6 = ena;
				break;

			case peripheral::RIIC0:
				ICU::IPR.EEI0 = lvl;
				ICU::IPR.RXI0 = lvl;
				ICU::IPR.TXI0 = lvl;
				ICU::IPR.TEI0 = lvl;
				ICU::IER.EEI0 = ena;
				ICU::IER.RXI0 = ena;
				ICU::IER.TXI0 = ena;
				ICU::IER.TEI0 = ena;
				break;

			case peripheral::S12AD:
//				ICU::IPR.EEI0 = lvl;
				break;
			case peripheral::S12AD1:

				break;
			case peripheral::S12AD2:

				break;

			default:
				break;
			}
		}
	};
}
