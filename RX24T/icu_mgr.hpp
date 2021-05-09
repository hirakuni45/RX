#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・割り込みマネージャー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016,2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"
#include "common/vect.h"
#include "common/dispatch.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  割り込みマネージャー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct icu_mgr {

		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みタスクを設定
			@param[in]	vec		割り込み要因
			@param[in]	task	割り込みタスク
		*/
		//-----------------------------------------------------------------//
		static void set_task(ICU::VECTOR vec, utils::TASK task) noexcept {
			set_interrupt_task(task, static_cast<uint32_t>(vec));
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みを設定する（ベクター別）
			@param[in]	vec	割り込みベクター
			@param[in]	lvl	割り込みレベル（０の場合、割り込み禁止）
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//
		static bool set_level(ICU::VECTOR vec, uint8_t lvl) noexcept
		{
			bool ret = true;
			bool ena = lvl != 0 ? true : false;
			switch(vec) {

			case ICU::VECTOR::BUSERR:
				ICU::IER.BUSERR = 0;
				ICU::IPR.BUSERR = lvl;
				ICU::IER.BUSERR = ena;
				break;

			case ICU::VECTOR::FRDYI:
				ICU::IER.FRDYI = 0;
				ICU::IPR.FRDYI = lvl;
				ICU::IER.FRDYI = ena;
				break;

			case ICU::VECTOR::SWINT:
				ICU::IER.SWINT = 0;
				ICU::IPR.SWINT = lvl;
				ICU::IER.SWINT = ena;
				break;
			case ICU::VECTOR::CMI0:
				ICU::IER.CMI0 = 0;
				ICU::IPR.CMI0 = lvl;
				ICU::IER.CMI0 = ena;
				break;
			case ICU::VECTOR::CMI1:
				ICU::IER.CMI1 = 0;
				ICU::IPR.CMI1 = lvl;
				ICU::IER.CMI1 = ena;
				break;
			case ICU::VECTOR::CMI2:
				ICU::IER.CMI2 = 0;
				ICU::IPR.CMI2 = lvl;
				ICU::IER.CMI2 = ena;
				break;
			case ICU::VECTOR::CMI3:
				ICU::IER.CMI3 = 0;
				ICU::IPR.CMI3 = lvl;
				ICU::IER.CMI3 = ena;
				break;

			case ICU::VECTOR::FERRF:
				ICU::IER.FERRF = 0;
				ICU::IPR.FERRF = lvl;
				ICU::IER.FERRF = ena;
				break;
			case ICU::VECTOR::MENDF:
				ICU::IER.MENDF = 0;
				ICU::IPR.MENDF = lvl;
				ICU::IER.MENDF = ena;
				break;
			case ICU::VECTOR::OVFF:
				ICU::IER.OVFF = 0;
				ICU::IPR.OVFF = lvl;
				ICU::IER.OVFF = ena;
				break;

			case ICU::VECTOR::ETGIN:
				ICU::IER.ETGIN = 0;
				ICU::IPR.ETGIN = lvl;
				ICU::IER.ETGIN = ena;
				break;
			case ICU::VECTOR::ETGIP:
				ICU::IER.ETGIP = 0;
				ICU::IPR.ETGIP = lvl;
				ICU::IER.ETGIP = ena;
				break;

			case ICU::VECTOR::SPEI0:
				ICU::IER.SPEI0 = 0;
				ICU::IPR.SPEI0 = lvl;
				ICU::IER.SPEI0 = ena;
				break;
			case ICU::VECTOR::SPRI0:
				ICU::IER.SPRI0 = 0;
				ICU::IPR.SPRI0 = lvl;
				ICU::IER.SPRI0 = ena;
				break;
			case ICU::VECTOR::SPTI0:
				ICU::IER.SPTI0 = 0;
				ICU::IPR.SPTI0 = lvl;
				ICU::IER.SPTI0 = ena;
				break;
			case ICU::VECTOR::SPII0:
				ICU::IER.SPII0 = 0;
				ICU::IPR.SPII0 = lvl;
				ICU::IER.SPII0 = ena;
				break;

			case ICU::VECTOR::GTCIA0:
				ICU::IER.GTCIA0 = 0;
				ICU::IPR.GTCIA0 = lvl;
				ICU::IER.GTCIA0 = ena;
				break;
			case ICU::VECTOR::GTCIB0:
				ICU::IER.GTCIB0 = 0;
				ICU::IPR.GTCIB0 = lvl;
				ICU::IER.GTCIB0 = ena;
				break;
			case ICU::VECTOR::GTCIC0:
				ICU::IER.GTCIC0 = 0;
				ICU::IPR.GTCIC0 = lvl;
				ICU::IER.GTCIC0 = ena;
				break;
			case ICU::VECTOR::GTCID0:
				ICU::IER.GTCID0 = 0;
				ICU::IPR.GTCID0 = lvl;
				ICU::IER.GTCID0 = ena;
				break;
			case ICU::VECTOR::GDTE0:
				ICU::IER.GDTE0 = 0;
				ICU::IPR.GDTE0 = lvl;
				ICU::IER.GDTE0 = ena;
				break;
			case ICU::VECTOR::GTCIE0:
				ICU::IER.GTCIE0 = 0;
				ICU::IPR.GTCIE0 = lvl;
				ICU::IER.GTCIE0 = ena;
				break;
			case ICU::VECTOR::GTCIF0:
				ICU::IER.GTCIF0 = 0;
				ICU::IPR.GTCIF0 = lvl;
				ICU::IER.GTCIF0 = ena;
				break;
			case ICU::VECTOR::GTCIV0:
				ICU::IER.GTCIV0 = 0;
				ICU::IPR.GTCIV0 = lvl;
				ICU::IER.GTCIV0 = ena;
				break;
			case ICU::VECTOR::GTCIU0:
				ICU::IER.GTCIU0 = 0;
				ICU::IPR.GTCIU0 = lvl;
				ICU::IER.GTCIU0 = ena;
				break;

			case ICU::VECTOR::DOPCF:
				ICU::IER.DOPCF = 0;
				ICU::IPR.DOPCF = lvl;
				ICU::IER.DOPCF = ena;
				break;

			case ICU::VECTOR::COMFRXINT:
				ICU::IER.COMFRXINT = 0;
				ICU::IPR.COMFRXINT = lvl;
				ICU::IER.COMFRXINT = ena;
				break;
			case ICU::VECTOR::RXFINT:
				ICU::IER.RXFINT = 0;
				ICU::IPR.RXFINT = lvl;
				ICU::IER.RXFINT = ena;
				break;
			case ICU::VECTOR::TXINT:
				ICU::IER.TXINT = 0;
				ICU::IPR.TXINT = lvl;
				ICU::IER.TXINT = ena;
				break;
			case ICU::VECTOR::CHERRINT:
				ICU::IER.CHERRINT = 0;
				ICU::IPR.CHERRINT = lvl;
				ICU::IER.CHERRINT = ena;
				break;
			case ICU::VECTOR::GLERRINT:
				ICU::IER.GLERRINT = 0;
				ICU::IPR.GLERRINT = lvl;
				ICU::IER.GLERRINT = ena;
				break;

			case ICU::VECTOR::IRQ0:
				ICU::IER.IRQ0 = 0;
				ICU::IPR.IRQ0 = lvl;
				ICU::IER.IRQ0 = ena;
				break;
			case ICU::VECTOR::IRQ1:
				ICU::IER.IRQ1 = 0;
				ICU::IPR.IRQ1 = lvl;
				ICU::IER.IRQ1 = ena;
				break;
			case ICU::VECTOR::IRQ2:
				ICU::IER.IRQ2 = 0;
				ICU::IPR.IRQ2 = lvl;
				ICU::IER.IRQ2 = ena;
				break;
			case ICU::VECTOR::IRQ3:
				ICU::IER.IRQ3 = 0;
				ICU::IPR.IRQ3 = lvl;
				ICU::IER.IRQ3 = ena;
				break;
			case ICU::VECTOR::IRQ4:
				ICU::IER.IRQ4 = 0;
				ICU::IPR.IRQ4 = lvl;
				ICU::IER.IRQ4 = ena;
				break;
			case ICU::VECTOR::IRQ5:
				ICU::IER.IRQ5 = 0;
				ICU::IPR.IRQ5 = lvl;
				ICU::IER.IRQ5 = ena;
				break;
			case ICU::VECTOR::IRQ6:
				ICU::IER.IRQ6 = 0;
				ICU::IPR.IRQ6 = lvl;
				ICU::IER.IRQ6 = ena;
				break;
			case ICU::VECTOR::IRQ7:
				ICU::IER.IRQ7 = 0;
				ICU::IPR.IRQ7 = lvl;
				ICU::IER.IRQ7 = ena;
				break;

			case ICU::VECTOR::LVD1:
				ICU::IER.LVD1 = 0;
				ICU::IPR.LVD1 = lvl;
				ICU::IER.LVD1 = ena;
				break;
			case ICU::VECTOR::LVD2:
				ICU::IER.LVD2 = 0;
				ICU::IPR.LVD2 = lvl;
				ICU::IER.LVD2 = ena;
				break;

			case ICU::VECTOR::GTCIA1:
				ICU::IER.GTCIA1 = 0;
				ICU::IPR.GTCIA1 = lvl;
				ICU::IER.GTCIA1 = ena;
				break;
			case ICU::VECTOR::GTCIB1:
				ICU::IER.GTCIB1 = 0;
				ICU::IPR.GTCIB1 = lvl;
				ICU::IER.GTCIB1 = ena;
				break;
			case ICU::VECTOR::GTCIC1:
				ICU::IER.GTCIC1 = 0;
				ICU::IPR.GTCIC1 = lvl;
				ICU::IER.GTCIC1 = ena;
				break;
			case ICU::VECTOR::GTCID1:
				ICU::IER.GTCID1 = 0;
				ICU::IPR.GTCID1 = lvl;
				ICU::IER.GTCID1 = ena;
				break;

			case ICU::VECTOR::S12ADI:
				ICU::IER.S12ADI = 0;
				ICU::IPR.S12ADI = lvl;
				ICU::IER.S12ADI = ena;
				break;
			case ICU::VECTOR::GBADI:
				ICU::IER.GBADI = 0;
				ICU::IPR.GBADI = lvl;
				ICU::IER.GBADI = ena;
				break;
			case ICU::VECTOR::GCADI:
				ICU::IER.GCADI = 0;
				ICU::IPR.GCADI = lvl;
				ICU::IER.GCADI = ena;
				break;
			case ICU::VECTOR::S12ADI1:
				ICU::IER.S12ADI1 = 0;
				ICU::IPR.S12ADI1 = lvl;
				ICU::IER.S12ADI1 = ena;
				break;
			case ICU::VECTOR::GBADI1:
				ICU::IER.GBADI1 = 0;
				ICU::IPR.GBADI1 = lvl;
				ICU::IER.GBADI1 = ena;
				break;
			case ICU::VECTOR::GCADI1:
				ICU::IER.GCADI1 = 0;
				ICU::IPR.GCADI1 = lvl;
				ICU::IER.GCADI1 = ena;
				break;

			case ICU::VECTOR::CMPC0:
				ICU::IER.CMPC0 = 0;
				ICU::IPR.CMPC0 = lvl;
				ICU::IER.CMPC0 = ena;
				break;
			case ICU::VECTOR::CMPC1:
				ICU::IER.CMPC1 = 0;
				ICU::IPR.CMPC1 = lvl;
				ICU::IER.CMPC1 = ena;
				break;
			case ICU::VECTOR::CMPC2:
				ICU::IER.CMPC2 = 0;
				ICU::IPR.CMPC2 = lvl;
				ICU::IER.CMPC2 = ena;
				break;

			case ICU::VECTOR::S12ADI2:
				ICU::IER.S12ADI2 = 0;
				ICU::IPR.S12ADI2 = lvl;
				ICU::IER.S12ADI2 = ena;
				break;
			case ICU::VECTOR::GBADI2:
				ICU::IER.GBADI2 = 0;
				ICU::IPR.GBADI2 = lvl;
				ICU::IER.GBADI2 = ena;
				break;
			case ICU::VECTOR::GCADI2:
				ICU::IER.GCADI2 = 0;
				ICU::IPR.GCADI2 = lvl;
				ICU::IER.GCADI2 = ena;
				break;

			case ICU::VECTOR::TGIA0:
				ICU::IER.TGIA0 = 0;
				ICU::IPR.TGIA0 = lvl;
				ICU::IER.TGIA0 = ena;
				break;
			case ICU::VECTOR::TGIB0:
				ICU::IER.TGIB0 = 0;
				ICU::IPR.TGIB0 = lvl;
				ICU::IER.TGIB0 = ena;
				break;
			case ICU::VECTOR::TGIC0:
				ICU::IER.TGIC0 = 0;
				ICU::IPR.TGIC0 = lvl;
				ICU::IER.TGIC0 = ena;
				break;
			case ICU::VECTOR::TGID0:
				ICU::IER.TGID0 = 0;
				ICU::IPR.TGID0 = lvl;
				ICU::IER.TGID0 = ena;
				break;
			case ICU::VECTOR::TCIV0:
				ICU::IER.TCIV0 = 0;
				ICU::IPR.TCIV0 = lvl;
				ICU::IER.TCIV0 = ena;
				break;
			case ICU::VECTOR::TGIE0:
				ICU::IER.TGIE0 = 0;
				ICU::IPR.TGIE0 = lvl;
				ICU::IER.TGIE0 = ena;
				break;
			case ICU::VECTOR::TGIF0:
				ICU::IER.TGIF0 = 0;
				ICU::IPR.TGIF0 = lvl;
				ICU::IER.TGIF0 = ena;
				break;

			case ICU::VECTOR::TGIA1:
				ICU::IER.TGIA1 = 0;
				ICU::IPR.TGIA1 = lvl;
				ICU::IER.TGIA1 = ena;
				break;
			case ICU::VECTOR::TGIB1:
				ICU::IER.TGIB1 = 0;
				ICU::IPR.TGIB1 = lvl;
				ICU::IER.TGIB1 = ena;
				break;
			case ICU::VECTOR::TCIV1:
				ICU::IER.TCIV1 = 0;
				ICU::IPR.TCIV1 = lvl;
				ICU::IER.TCIV1 = ena;
				break;
			case ICU::VECTOR::TCIU1:
				ICU::IER.TCIU1 = 0;
				ICU::IPR.TCIU1 = lvl;
				ICU::IER.TCIU1 = ena;
				break;

			case ICU::VECTOR::TGIA2:
				ICU::IER.TGIA2 = 0;
				ICU::IPR.TGIA2 = lvl;
				ICU::IER.TGIA2 = ena;
				break;
			case ICU::VECTOR::TGIB2:
				ICU::IER.TGIB2 = 0;
				ICU::IPR.TGIB2 = lvl;
				ICU::IER.TGIB2 = ena;
				break;
			case ICU::VECTOR::TCIV2:
				ICU::IER.TCIV2 = 0;
				ICU::IPR.TCIV2 = lvl;
				ICU::IER.TCIV2 = ena;
				break;
			case ICU::VECTOR::TCIU2:
				ICU::IER.TCIU2 = 0;
				ICU::IPR.TCIU2 = lvl;
				ICU::IER.TCIU2 = ena;
				break;

			case ICU::VECTOR::TGIA3:
				ICU::IER.TGIA3 = 0;
				ICU::IPR.TGIA3 = lvl;
				ICU::IER.TGIA3 = ena;
				break;
			case ICU::VECTOR::TGIB3:
				ICU::IER.TGIB3 = 0;
				ICU::IPR.TGIB3 = lvl;
				ICU::IER.TGIB3 = ena;
				break;
			case ICU::VECTOR::TGIC3:
				ICU::IER.TGIC3 = 0;
				ICU::IPR.TGIC3 = lvl;
				ICU::IER.TGIC3 = ena;
				break;
			case ICU::VECTOR::TGID3:
				ICU::IER.TGID3 = 0;
				ICU::IPR.TGID3 = lvl;
				ICU::IER.TGID3 = ena;
				break;
			case ICU::VECTOR::TCIV3:
				ICU::IER.TCIV3 = 0;
				ICU::IPR.TCIV3 = lvl;
				ICU::IER.TCIV3 = ena;
				break;

			case ICU::VECTOR::TGIA4:
				ICU::IER.TGIA4 = 0;
				ICU::IPR.TGIA4 = lvl;
				ICU::IER.TGIA4 = ena;
				break;
			case ICU::VECTOR::TGIB4:
				ICU::IER.TGIB4 = 0;
				ICU::IPR.TGIB4 = lvl;
				ICU::IER.TGIB4 = ena;
				break;
			case ICU::VECTOR::TGIC4:
				ICU::IER.TGIC4 = 0;
				ICU::IPR.TGIC4 = lvl;
				ICU::IER.TGIC4 = ena;
				break;
			case ICU::VECTOR::TGID4:
				ICU::IER.TGID4 = 0;
				ICU::IPR.TGID4 = lvl;
				ICU::IER.TGID4 = ena;
				break;
			case ICU::VECTOR::TCIV4:
				ICU::IER.TCIV4 = 0;
				ICU::IPR.TCIV4 = lvl;
				ICU::IER.TCIV4 = ena;
				break;

			case ICU::VECTOR::TGIU5:
				ICU::IER.TGIU5 = 0;
				ICU::IPR.TGIU5 = lvl;
				ICU::IER.TGIU5 = ena;
				break;
			case ICU::VECTOR::TGIV5:
				ICU::IER.TGIV5 = 0;
				ICU::IPR.TGIV5 = lvl;
				ICU::IER.TGIV5 = ena;
				break;
			case ICU::VECTOR::TGIW5:
				ICU::IER.TGIW5 = 0;
				ICU::IPR.TGIW5 = lvl;
				ICU::IER.TGIW5 = ena;
				break;

			case ICU::VECTOR::TGIA6:
				ICU::IER.TGIA6 = 0;
				ICU::IPR.TGIA6 = lvl;
				ICU::IER.TGIA6 = ena;
				break;
			case ICU::VECTOR::TGIB6:
				ICU::IER.TGIB6 = 0;
				ICU::IPR.TGIB6 = lvl;
				ICU::IER.TGIB6 = ena;
				break;
			case ICU::VECTOR::TGIC6:
				ICU::IER.TGIC6 = 0;
				ICU::IPR.TGIC6 = lvl;
				ICU::IER.TGIC6 = ena;
				break;
			case ICU::VECTOR::TGID6:
				ICU::IER.TGID6 = 0;
				ICU::IPR.TGID6 = lvl;
				ICU::IER.TGID6 = ena;
				break;
			case ICU::VECTOR::TCIV6:
				ICU::IER.TCIV6 = 0;
				ICU::IPR.TCIV6 = lvl;
				ICU::IER.TCIV6 = ena;
				break;

			case ICU::VECTOR::TGIA7:
				ICU::IER.TGIA7 = 0;
				ICU::IPR.TGIA7 = lvl;
				ICU::IER.TGIA7 = ena;
				break;
			case ICU::VECTOR::TGIB7:
				ICU::IER.TGIB7 = 0;
				ICU::IPR.TGIB7 = lvl;
				ICU::IER.TGIB7 = ena;
				break;
			case ICU::VECTOR::TGIC7:
				ICU::IER.TGIC7 = 0;
				ICU::IPR.TGIC7 = lvl;
				ICU::IER.TGIC7 = ena;
				break;
			case ICU::VECTOR::TGID7:
				ICU::IER.TGID7 = 0;
				ICU::IPR.TGID7 = lvl;
				ICU::IER.TGID7 = ena;
				break;
			case ICU::VECTOR::TCIV7:
				ICU::IER.TCIV7 = 0;
				ICU::IPR.TCIV7 = lvl;
				ICU::IER.TCIV7 = ena;
				break;

			case ICU::VECTOR::TGIA9:
				ICU::IER.TGIA9 = 0;
				ICU::IPR.TGIA9 = lvl;
				ICU::IER.TGIA9 = ena;
				break;
			case ICU::VECTOR::TGIB9:
				ICU::IER.TGIB9 = 0;
				ICU::IPR.TGIB9 = lvl;
				ICU::IER.TGIB9 = ena;
				break;
			case ICU::VECTOR::TGIC9:
				ICU::IER.TGIC9 = 0;
				ICU::IPR.TGIC9 = lvl;
				ICU::IER.TGIC9 = ena;
				break;
			case ICU::VECTOR::TGID9:
				ICU::IER.TGID9 = 0;
				ICU::IPR.TGID9 = lvl;
				ICU::IER.TGID9 = ena;
				break;
			case ICU::VECTOR::TCIV9:
				ICU::IER.TCIV9 = 0;
				ICU::IPR.TCIV9 = lvl;
				ICU::IER.TCIV9 = ena;
				break;
			case ICU::VECTOR::TGIE9:
				ICU::IER.TGIE9 = 0;
				ICU::IPR.TGIE9 = lvl;
				ICU::IER.TGIE9 = ena;
				break;
			case ICU::VECTOR::TGIF9:
				ICU::IER.TGIF9 = 0;
				ICU::IPR.TGIF9 = lvl;
				ICU::IER.TGIF9 = ena;
				break;

			case ICU::VECTOR::OEI1:
				ICU::IER.OEI1 = 0;
				ICU::IPR.OEI1 = lvl;
				ICU::IER.OEI1 = ena;
				break;
			case ICU::VECTOR::OEI2:
				ICU::IER.OEI2 = 0;
				ICU::IPR.OEI2 = lvl;
				ICU::IER.OEI2 = ena;
				break;
			case ICU::VECTOR::OEI3:
				ICU::IER.OEI3 = 0;
				ICU::IPR.OEI3 = lvl;
				ICU::IER.OEI3 = ena;
				break;
			case ICU::VECTOR::OEI4:
				ICU::IER.OEI4 = 0;
				ICU::IPR.OEI4 = lvl;
				ICU::IER.OEI4 = ena;
				break;
			case ICU::VECTOR::OEI5:
				ICU::IER.OEI5 = 0;
				ICU::IPR.OEI5 = lvl;
				ICU::IER.OEI5 = ena;
				break;

			case ICU::VECTOR::CMPC3:
				ICU::IER.CMPC3 = 0;
				ICU::IPR.CMPC3 = lvl;
				ICU::IER.CMPC3 = ena;
				break;

			case ICU::VECTOR::CMIA0:
				ICU::IER.CMIA0 = 0;
				ICU::IPR.CMIA0 = lvl;
				ICU::IER.CMIA0 = ena;
				break;
			case ICU::VECTOR::CMIB0:
				ICU::IER.CMIB0 = 0;
				ICU::IPR.CMIB0 = lvl;
				ICU::IER.CMIB0 = ena;
				break;
			case ICU::VECTOR::OVI0:
				ICU::IER.OVI0 = 0;
				ICU::IPR.OVI0 = lvl;
				ICU::IER.OVI0 = ena;
				break;
			case ICU::VECTOR::CMIA1:
				ICU::IER.CMIA1 = 0;
				ICU::IPR.CMIA1 = lvl;
				ICU::IER.CMIA1 = ena;
				break;
			case ICU::VECTOR::CMIB1:
				ICU::IER.CMIB1 = 0;
				ICU::IPR.CMIB1 = lvl;
				ICU::IER.CMIB1 = ena;
				break;
			case ICU::VECTOR::OVI1:
				ICU::IER.OVI1 = 0;
				ICU::IPR.OVI1 = lvl;
				ICU::IER.OVI1 = ena;
				break;
			case ICU::VECTOR::CMIA2:
				ICU::IER.CMIA2 = 0;
				ICU::IPR.CMIA2 = lvl;
				ICU::IER.CMIA2 = ena;
				break;
			case ICU::VECTOR::CMIB2:
				ICU::IER.CMIB2 = 0;
				ICU::IPR.CMIB2 = lvl;
				ICU::IER.CMIB2 = ena;
				break;
			case ICU::VECTOR::OVI2:
				ICU::IER.OVI2 = 0;
				ICU::IPR.OVI2 = lvl;
				ICU::IER.OVI2 = ena;
				break;
			case ICU::VECTOR::CMIA3:
				ICU::IER.CMIA3 = 0;
				ICU::IPR.CMIA3 = lvl;
				ICU::IER.CMIA3 = ena;
				break;
			case ICU::VECTOR::CMIB3:
				ICU::IER.CMIB3 = 0;
				ICU::IPR.CMIB3 = lvl;
				ICU::IER.CMIB3 = ena;
				break;
			case ICU::VECTOR::OVI3:
				ICU::IER.OVI3 = 0;
				ICU::IPR.OVI3 = lvl;
				ICU::IER.OVI3 = ena;
				break;
			case ICU::VECTOR::CMIA4:
				ICU::IER.CMIA4 = 0;
				ICU::IPR.CMIA4 = lvl;
				ICU::IER.CMIA4 = ena;
				break;
			case ICU::VECTOR::CMIB4:
				ICU::IER.CMIB4 = 0;
				ICU::IPR.CMIB4 = lvl;
				ICU::IER.CMIB4 = ena;
				break;
			case ICU::VECTOR::OVI4:
				ICU::IER.OVI4 = 0;
				ICU::IPR.OVI4 = lvl;
				ICU::IER.OVI4 = ena;
				break;
			case ICU::VECTOR::CMIA5:
				ICU::IER.CMIA5 = 0;
				ICU::IPR.CMIA5 = lvl;
				ICU::IER.CMIA5 = ena;
				break;
			case ICU::VECTOR::CMIB5:
				ICU::IER.CMIB5 = 0;
				ICU::IPR.CMIB5 = lvl;
				ICU::IER.CMIB5 = ena;
				break;
			case ICU::VECTOR::OVI5:
				ICU::IER.OVI5 = 0;
				ICU::IPR.OVI5 = lvl;
				ICU::IER.OVI5 = ena;
				break;
			case ICU::VECTOR::CMIA6:
				ICU::IER.CMIA6 = 0;
				ICU::IPR.CMIA6 = lvl;
				ICU::IER.CMIA6 = ena;
				break;
			case ICU::VECTOR::CMIB6:
				ICU::IER.CMIB6 = 0;
				ICU::IPR.CMIB6 = lvl;
				ICU::IER.CMIB6 = ena;
				break;
			case ICU::VECTOR::OVI6:
				ICU::IER.OVI6 = 0;
				ICU::IPR.OVI6 = lvl;
				ICU::IER.OVI6 = ena;
				break;
			case ICU::VECTOR::CMIA7:
				ICU::IER.CMIA7 = 0;
				ICU::IPR.CMIA7 = lvl;
				ICU::IER.CMIA7 = ena;
				break;
			case ICU::VECTOR::CMIB7:
				ICU::IER.CMIB7 = 0;
				ICU::IPR.CMIB7 = lvl;
				ICU::IER.CMIB7 = ena;
				break;
			case ICU::VECTOR::OVI7:
				ICU::IER.OVI7 = 0;
				ICU::IPR.OVI7 = lvl;
				ICU::IER.OVI7 = ena;
				break;

			case ICU::VECTOR::GDTE1:
				ICU::IER.GDTE0 = 0;
				ICU::IPR.GDTE0 = lvl;
				ICU::IER.GDTE0 = ena;
				break;
			case ICU::VECTOR::GTCIE1:
				ICU::IER.GTCIE0 = 0;
				ICU::IPR.GTCIE0 = lvl;
				ICU::IER.GTCIE0 = ena;
				break;
			case ICU::VECTOR::GTCIF1:
				ICU::IER.GTCIF0 = 0;
				ICU::IPR.GTCIF0 = lvl;
				ICU::IER.GTCIF0 = ena;
				break;
			case ICU::VECTOR::GTCIV1:
				ICU::IER.GTCIV0 = 0;
				ICU::IPR.GTCIV0 = lvl;
				ICU::IER.GTCIV0 = ena;
				break;
			case ICU::VECTOR::GTCIU1:
				ICU::IER.GTCIU0 = 0;
				ICU::IPR.GTCIU0 = lvl;
				ICU::IER.GTCIU0 = ena;
				break;

			case ICU::VECTOR::GTCIA2:
				ICU::IER.GTCIA2 = 0;
				ICU::IPR.GTCIA2 = lvl;
				ICU::IER.GTCIA2 = ena;
				break;
			case ICU::VECTOR::GTCIB2:
				ICU::IER.GTCIB2 = 0;
				ICU::IPR.GTCIB2 = lvl;
				ICU::IER.GTCIB2 = ena;
				break;
			case ICU::VECTOR::GTCIC2:
				ICU::IER.GTCIC2 = 0;
				ICU::IPR.GTCIC2 = lvl;
				ICU::IER.GTCIC2 = ena;
				break;
			case ICU::VECTOR::GTCID2:
				ICU::IER.GTCID2 = 0;
				ICU::IPR.GTCID2 = lvl;
				ICU::IER.GTCID2 = ena;
				break;
			case ICU::VECTOR::GDTE2:
				ICU::IER.GDTE2 = 0;
				ICU::IPR.GDTE2 = lvl;
				ICU::IER.GDTE2 = ena;
				break;
			case ICU::VECTOR::GTCIE2:
				ICU::IER.GTCIE2 = 0;
				ICU::IPR.GTCIE2 = lvl;
				ICU::IER.GTCIE2 = ena;
				break;
			case ICU::VECTOR::GTCIF2:
				ICU::IER.GTCIF2 = 0;
				ICU::IPR.GTCIF2 = lvl;
				ICU::IER.GTCIF2 = ena;
				break;
			case ICU::VECTOR::GTCIV2:
				ICU::IER.GTCIV2 = 0;
				ICU::IPR.GTCIV2 = lvl;
				ICU::IER.GTCIV2 = ena;
				break;
			case ICU::VECTOR::GTCIU2:
				ICU::IER.GTCIU2 = 0;
				ICU::IPR.GTCIU2 = lvl;
				ICU::IER.GTCIU2 = ena;
				break;

			case ICU::VECTOR::GTCIA3:
				ICU::IER.GTCIA3 = 0;
				ICU::IPR.GTCIA3 = lvl;
				ICU::IER.GTCIA3 = ena;
				break;
			case ICU::VECTOR::GTCIB3:
				ICU::IER.GTCIB3 = 0;
				ICU::IPR.GTCIB3 = lvl;
				ICU::IER.GTCIB3 = ena;
				break;

			case ICU::VECTOR::ERI1:
				ICU::IER.ERI1 = 0;
				ICU::IPR.ERI1 = lvl;
				ICU::IER.ERI1 = ena;
				break;
			case ICU::VECTOR::RXI1:
				ICU::IER.RXI1 = 0;
				ICU::IPR.RXI1 = lvl;
				ICU::IER.RXI1 = ena;
				break;
			case ICU::VECTOR::TXI1:
				ICU::IER.TXI1 = 0;
				ICU::IPR.TXI1 = lvl;
				ICU::IER.TXI1 = ena;
				break;
			case ICU::VECTOR::TEI1:
				ICU::IER.TEI1 = 0;
				ICU::IPR.TEI1 = lvl;
				ICU::IER.TEI1 = ena;
				break;

			case ICU::VECTOR::ERI5:
				ICU::IER.ERI5 = 0;
				ICU::IPR.ERI5 = lvl;
				ICU::IER.ERI5 = ena;
				break;
			case ICU::VECTOR::RXI5:
				ICU::IER.RXI5 = 0;
				ICU::IPR.RXI5 = lvl;
				ICU::IER.RXI5 = ena;
				break;
			case ICU::VECTOR::TXI5:
				ICU::IER.TXI5 = 0;
				ICU::IPR.TXI5 = lvl;
				ICU::IER.TXI5 = ena;
				break;
			case ICU::VECTOR::TEI5:
				ICU::IER.TEI5 = 0;
				ICU::IPR.TEI5 = lvl;
				ICU::IER.TEI5 = ena;
				break;

			case ICU::VECTOR::ERI6:
				ICU::IER.ERI6 = 0;
				ICU::IPR.ERI6 = lvl;
				ICU::IER.ERI6 = ena;
				break;
			case ICU::VECTOR::RXI6:
				ICU::IER.RXI6 = 0;
				ICU::IPR.RXI6 = lvl;
				ICU::IER.RXI6 = ena;
				break;
			case ICU::VECTOR::TXI6:
				ICU::IER.TXI6 = 0;
				ICU::IPR.TXI6 = lvl;
				ICU::IER.TXI6 = ena;
				break;
			case ICU::VECTOR::TEI6:
				ICU::IER.TEI6 = 0;
				ICU::IPR.TEI6 = lvl;
				ICU::IER.TEI6 = ena;
				break;

			case ICU::VECTOR::GTCIC3:
				ICU::IER.GTCIC3 = 0;
				ICU::IPR.GTCIC3 = lvl;
				ICU::IER.GTCIC3 = ena;
				break;
			case ICU::VECTOR::GTCID3:
				ICU::IER.GTCID3 = 0;
				ICU::IPR.GTCID3 = lvl;
				ICU::IER.GTCID3 = ena;
				break;
			case ICU::VECTOR::GDTE3:
				ICU::IER.GDTE3 = 0;
				ICU::IPR.GDTE3 = lvl;
				ICU::IER.GDTE3 = ena;
				break;
			case ICU::VECTOR::GTCIE3:
				ICU::IER.GTCIE3 = 0;
				ICU::IPR.GTCIE3 = lvl;
				ICU::IER.GTCIE3 = ena;
				break;
			case ICU::VECTOR::GTCIF3:
				ICU::IER.GTCIF3 = 0;
				ICU::IPR.GTCIF3 = lvl;
				ICU::IER.GTCIF3 = ena;
				break;
			case ICU::VECTOR::GTCIV3:
				ICU::IER.GTCIV3 = 0;
				ICU::IPR.GTCIV3 = lvl;
				ICU::IER.GTCIV3 = ena;
				break;
			case ICU::VECTOR::GTCIU3:
				ICU::IER.GTCIU3 = 0;
				ICU::IPR.GTCIU3 = lvl;
				ICU::IER.GTCIU3 = ena;
				break;

			case ICU::VECTOR::RIIC_EEI0:
				ICU::IER.RIIC_EEI0 = 0;
				ICU::IPR.RIIC_EEI0 = lvl;
				ICU::IER.RIIC_EEI0 = ena;
				break;
			case ICU::VECTOR::RIIC_RXI0:
				ICU::IER.RIIC_RXI0 = 0;
				ICU::IPR.RIIC_RXI0 = lvl;
				ICU::IER.RIIC_RXI0 = ena;
				break;
			case ICU::VECTOR::RIIC_TXI0:
				ICU::IER.RIIC_TXI0 = 0;
				ICU::IPR.RIIC_TXI0 = lvl;
				ICU::IER.RIIC_TXI0 = ena;
				break;
			case ICU::VECTOR::RIIC_TEI0:
				ICU::IER.RIIC_TEI0 = 0;
				ICU::IPR.RIIC_TEI0 = lvl;
				ICU::IER.RIIC_TEI0 = ena;
				break;

			default:
				ret = false;
				break;
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みレベルを取得する
			@param[in]	vec	割り込み要因
			@return 割り込みレベル
		*/
		//-----------------------------------------------------------------//
		static uint8_t get_level(ICU::VECTOR vec) noexcept { return ICU::IPR[vec]; }


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み設定（通常ベクター）
			@param[in]	vec		割り込み要因
			@param[in]	task	割り込みタスク
			@param[in]	lvl		割り込みレベル（０の場合、割り込み禁止）
			@return ベクター番号
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR set_interrupt(ICU::VECTOR vec, utils::TASK task, uint8_t lvl) noexcept {
			set_task(vec, task);
			set_level(vec, lvl);
			return vec;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  グループ割り込み設定のダミー
			@param[in]	idx		インデックス
			@param[in]	task	割り込みタスク（※nullptr なら無効）
			@return グループ割り込み以外なら「false」
		*/
		//-----------------------------------------------------------------//
		static bool install_group_task(ICU::VECTOR idx, utils::TASK task) noexcept
		{
			return false;
		}
	};
}
