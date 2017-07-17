#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・割り込みマネージャー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016,2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
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
			case peripheral::SCI1C:
				ICU::IPR.SCI1 = lvl;
				ICU::IER.RXI1 = ena;
				ICU::IER.TEI1 = ena;
				break;
			case peripheral::SCI5:
			case peripheral::SCI5C:
				ICU::IPR.SCI5 = lvl;
				ICU::IER.RXI5 = ena;
				ICU::IER.TEI5 = ena;
				break;
			case peripheral::SCI6:
			case peripheral::SCI6C:
				ICU::IPR.SCI6 = lvl;
				ICU::IER.RXI6 = ena;
				ICU::IER.TEI6 = ena;
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
				ICU::IPR.S12ADI = lvl;
				ICU::IPR.GBADI  = lvl;
				ICU::IPR.GCADI  = lvl;
				ICU::IER.S12ADI = ena;
				ICU::IER.GBADI  = ena;
				ICU::IER.GCADI  = ena;
				break;
			case peripheral::S12AD1:
				ICU::IPR.S12ADI1 = lvl;
				ICU::IPR.GBADI1  = lvl;
				ICU::IPR.GCADI1  = lvl;
				ICU::IER.S12ADI1 = ena;
				ICU::IER.GBADI1  = ena;
				ICU::IER.GCADI1  = ena;
				break;
			case peripheral::S12AD2:
				ICU::IPR.S12ADI2 = lvl;
				ICU::IPR.GBADI2  = lvl;
				ICU::IPR.GCADI2  = lvl;
				ICU::IER.S12ADI2 = ena;
				ICU::IER.GBADI2  = ena;
				ICU::IER.GCADI2  = ena;
				break;

			default:
				break;
			}
		}
	};
}
