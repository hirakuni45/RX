#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M グループ・割り込みマネージャー @n
			Copyright 2016, 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "RX64M/icu.hpp"
#include "RX64M/peripheral.hpp"
#include "common/vect.h"

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
				ICU::IER.CMI0 = 0;
				ICU::IPR.CMI0 = lvl;
				ICU::IER.CMI0 = ena;
				break;
			case peripheral::CMT1:
				ICU::IER.CMI1 = 0;
				ICU::IPR.CMI1 = lvl;
				ICU::IER.CMI1 = ena;
				break;

			case peripheral::RIIC0:
				ICU::IPR.RIIC_RXI0 = lvl;
				ICU::IER.RIIC_RXI0 = ena;
				ICU::IPR.RIIC_TXI0 = lvl;
				ICU::IER.RIIC_TXI0 = ena;
				break;
			case peripheral::RIIC2:
				ICU::IPR.RIIC_RXI2 = lvl;
				ICU::IER.RIIC_RXI2 = ena;
				ICU::IPR.RIIC_TXI2 = lvl;
				ICU::IER.RIIC_TXI2 = ena;
				break;

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

			case peripheral::ETHERC0:

				break;
			case peripheral::ETHERC1:

				break;
			default:
				break;
			}
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUPBE0
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group_be0_handler_()
		{
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUPBL0
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group_bl0_handler_()
		{

		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUPBL1
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group_bl1_handler_()
		{
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUPAL0
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group_al0_handler_()
		{
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUPAL1
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group_al1_handler_()
		{
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  グループ割り込みを設定する
			@param[in]	vec	グループ割り込み・インデックス
			@param[in]	lvl	割り込みレベル（０なら割り込み禁止）
		*/
		//-----------------------------------------------------------------//
		static void set_group_vector(ICU::VECTOR vec, uint8_t lvl)
		{
			bool ena = lvl != 0 ? true : false;
			switch(vec) {
			case ICU::VECTOR::GROUPBE0:
				set_interrupt_task(group_be0_handler_, static_cast<uint32_t>(vec));
				ICU::IPR.GROUPBE0 = lvl;
				ICU::IER.GROUPBE0 = ena;
				break;
			case ICU::VECTOR::GROUPBL0:
				set_interrupt_task(group_bl0_handler_, static_cast<uint32_t>(vec));
				ICU::IPR.GROUPBL0 = lvl;
				ICU::IER.GROUPBL0 = ena;
				break;
			case ICU::VECTOR::GROUPBL1:
				set_interrupt_task(group_bl1_handler_, static_cast<uint32_t>(vec));
				ICU::IPR.GROUPBL1 = lvl;
				ICU::IER.GROUPBL1 = ena;
				break;
			case ICU::VECTOR::GROUPAL0:
				set_interrupt_task(group_al0_handler_, static_cast<uint32_t>(vec));
				ICU::IPR.GROUPAL0 = lvl;
				ICU::IER.GROUPAL0 = ena;
				break;
			case ICU::VECTOR::GROUPAL1:
				set_interrupt_task(group_al1_handler_, static_cast<uint32_t>(vec));
				ICU::IPR.GROUPAL1 = lvl;
				ICU::IER.GROUPAL1 = ena;
				break;
			default:
				break;
			}
		}
	};
}
