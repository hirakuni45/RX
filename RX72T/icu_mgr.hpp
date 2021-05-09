#pragma once
//=====================================================================//
/*!	@file
	@brief	RX66T/RX72T グループ・割り込みマネージャー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX72T/peripheral.hpp"
#include "RX72T/icu.hpp"
#include "RX600/dmac.hpp"
#include "common/vect.h"
#include "common/dispatch.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  割り込みマネージャー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class _>
	class icu_mgr_ {

		typedef utils::dispatch<ICU::VECTOR::GROUPBE0, 2>  GROUPBE0_dispatch_t;
		typedef utils::dispatch<ICU::VECTOR::GROUPBL0, 32> GROUPBL0_dispatch_t;
		typedef utils::dispatch<ICU::VECTOR::GROUPBL1, 32> GROUPBL1_dispatch_t;
		typedef utils::dispatch<ICU::VECTOR::GROUPAL0, 22> GROUPAL0_dispatch_t;

		static GROUPBE0_dispatch_t GROUPBE0_dispatch_;
		static GROUPBL0_dispatch_t GROUPBL0_dispatch_;
		static GROUPBL1_dispatch_t GROUPBL1_dispatch_;
		static GROUPAL0_dispatch_t GROUPAL0_dispatch_;

	public:
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
			@brief  割り込みレベルを設定する
			@param[in]	vec	割り込み要因
			@param[in]	lvl	割り込みレベル（０の場合、割り込み禁止）
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		static bool set_level(ICU::VECTOR vec, uint8_t lvl) noexcept
		{
			bool ena = lvl != 0 ? true : false;
			switch(vec) {

			case ICU::VECTOR::BUSERR:
				ICU::IER.BUSERR = 0;
				ICU::IPR.BUSERR = lvl;
				ICU::IER.BUSERR = ena;
				break;

			case ICU::VECTOR::RAMERR:
				ICU::IER.RAMERR = 0;
				ICU::IPR.RAMERR = lvl;
				ICU::IER.RAMERR = ena;
				break;

			case ICU::VECTOR::FIFERR:
				ICU::IER.FIFERR = 0;
				ICU::IPR.FIFERR = lvl;
				ICU::IER.FIFERR = ena;
				break;

			case ICU::VECTOR::FRDYI:
				ICU::IER.FRDYI = 0;
				ICU::IPR.FRDYI = lvl;
				ICU::IER.FRDYI = ena;
				break;

			case ICU::VECTOR::SWINT2:
				ICU::IER.SWINT2 = 0;
				ICU::IPR.SWINT2 = lvl;
				ICU::IER.SWINT2 = ena;
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

			case ICU::VECTOR::D0FIFO0:
				ICU::IER.D0FIFO0 = 0;
				ICU::IPR.D0FIFO0 = lvl;
				ICU::IER.D0FIFO0 = ena;
				break;
			case ICU::VECTOR::D1FIFO0:
				ICU::IER.D1FIFO0 = 0;
				ICU::IPR.D1FIFO0 = lvl;
				ICU::IER.D1FIFO0 = ena;
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
			case ICU::VECTOR::IRQ8:
				ICU::IER.IRQ8 = 0;
				ICU::IPR.IRQ8 = lvl;
				ICU::IER.IRQ8 = ena;
				break;
			case ICU::VECTOR::IRQ9:
				ICU::IER.IRQ9 = 0;
				ICU::IPR.IRQ9 = lvl;
				ICU::IER.IRQ9 = ena;
				break;
			case ICU::VECTOR::IRQ10:
				ICU::IER.IRQ10 = 0;
				ICU::IPR.IRQ10 = lvl;
				ICU::IER.IRQ10 = ena;
				break;
			case ICU::VECTOR::IRQ11:
				ICU::IER.IRQ11 = 0;
				ICU::IPR.IRQ11 = lvl;
				ICU::IER.IRQ11 = ena;
				break;
			case ICU::VECTOR::IRQ12:
				ICU::IER.IRQ12 = 0;
				ICU::IPR.IRQ12 = lvl;
				ICU::IER.IRQ12 = ena;
				break;
			case ICU::VECTOR::IRQ13:
				ICU::IER.IRQ13 = 0;
				ICU::IPR.IRQ13 = lvl;
				ICU::IER.IRQ13 = ena;
				break;
			case ICU::VECTOR::IRQ14:
				ICU::IER.IRQ14 = 0;
				ICU::IPR.IRQ14 = lvl;
				ICU::IER.IRQ14 = ena;
				break;
			case ICU::VECTOR::IRQ15:
				ICU::IER.IRQ15 = 0;
				ICU::IPR.IRQ15 = lvl;
				ICU::IER.IRQ15 = ena;
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

			case ICU::VECTOR::USBR0:
				ICU::IER.USBR0 = 0;
				ICU::IPR.USBR0 = lvl;
				ICU::IER.USBR0 = ena;
				break;

			case ICU::VECTOR::IWUNI:
				ICU::IER.IWUNI = 0;
				ICU::IPR.IWUNI = lvl;
				ICU::IER.IWUNI = ena;
				break;
			case ICU::VECTOR::WUNI:
				ICU::IER.WUNI = 0;
				ICU::IPR.WUNI = lvl;
				ICU::IER.WUNI = ena;
				break;

			case ICU::VECTOR::RXI8:
				ICU::IER.RXI8 = 0;
				ICU::IPR.RXI8 = lvl;
				ICU::IER.RXI8 = ena;
				break;
			case ICU::VECTOR::TXI8:
				ICU::IER.TXI8 = 0;
				ICU::IPR.TXI8 = lvl;
				ICU::IER.TXI8 = ena;
				break;
			case ICU::VECTOR::RXI9:
				ICU::IER.RXI9 = 0;
				ICU::IPR.RXI9 = lvl;
				ICU::IER.RXI9 = ena;
				break;
			case ICU::VECTOR::TXI9:
				ICU::IER.TXI9 = 0;
				ICU::IPR.TXI9 = lvl;
				ICU::IER.TXI9 = ena;
				break;

			case ICU::VECTOR::GROUPBE0:
				ICU::IER.GROUPBE0 = 0;
				ICU::IPR.GROUPBE0 = lvl;
				ICU::IER.GROUPBE0 = ena;
				break;
			case ICU::VECTOR::GROUPBL0:
				ICU::IER.GROUPBL0 = 0;
				ICU::IPR.GROUPBL0 = lvl;
				ICU::IER.GROUPBL0 = ena;
				break;
			case ICU::VECTOR::GROUPBL1:
				ICU::IER.GROUPBL1 = 0;
				ICU::IPR.GROUPBL1 = lvl;
				ICU::IER.GROUPBL1 = ena;
				break;
			case ICU::VECTOR::GROUPAL0:
				ICU::IER.GROUPAL0 = 0;
				ICU::IPR.GROUPAL0 = lvl;
				ICU::IER.GROUPAL0 = ena;
				break;

			case ICU::VECTOR::RXI11:
				ICU::IER.RXI11 = 0;
				ICU::IPR.RXI11 = lvl;
				ICU::IER.RXI11 = ena;
				break;
			case ICU::VECTOR::TXI11:
				ICU::IER.TXI11 = 0;
				ICU::IPR.TXI11 = lvl;
				ICU::IER.TXI11 = ena;
				break;
			case ICU::VECTOR::RXI12:
				ICU::IER.RXI12 = 0;
				ICU::IPR.RXI12 = lvl;
				ICU::IER.RXI12 = ena;
				break;
			case ICU::VECTOR::TXI12:
				ICU::IER.TXI12 = 0;
				ICU::IPR.TXI12 = lvl;
				ICU::IER.TXI12 = ena;
				break;

			case ICU::VECTOR::DMAC0I:
				ICU::IER.DMAC0I = 0;
				ICU::IPR.DMAC0I = lvl;
				ICU::IER.DMAC0I = ena;
				break;
			case ICU::VECTOR::DMAC1I:
				ICU::IER.DMAC1I = 0;
				ICU::IPR.DMAC1I = lvl;
				ICU::IER.DMAC1I = ena;
				break;
			case ICU::VECTOR::DMAC2I:
				ICU::IER.DMAC2I = 0;
				ICU::IPR.DMAC2I = lvl;
				ICU::IER.DMAC2I = ena;
				break;
			case ICU::VECTOR::DMAC3I:
				ICU::IER.DMAC3I = 0;
				ICU::IPR.DMAC3I = lvl;
				ICU::IER.DMAC3I = ena;
				break;
			case ICU::VECTOR::DMAC74I:
				ICU::IER.DMAC74I = 0;
				ICU::IPR.DMAC74I = lvl;
				ICU::IER.DMAC74I = ena;
				break;

			case ICU::VECTOR::OSTDI:
				ICU::IER.OSTDI = 0;
				ICU::IPR.OSTDI = lvl;
				ICU::IER.OSTDI = ena;
				break;

			case ICU::VECTOR::S12ADI2:
				ICU::IER.S12ADI2 = 0;
				ICU::IPR.S12ADI2 = lvl;
				ICU::IER.S12ADI2 = ena;
				break;
			case ICU::VECTOR::S12GBADI2:
				ICU::IER.S12GBADI2 = 0;
				ICU::IPR.S12GBADI2 = lvl;
				ICU::IER.S12GBADI2 = ena;
				break;
			case ICU::VECTOR::S12GCADI2:
				ICU::IER.S12GCADI2 = 0;
				ICU::IPR.S12GCADI2 = lvl;
				ICU::IER.S12GCADI2 = ena;
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

			case ICU::VECTOR::RXF0:  // CAN0
				ICU::IER.RXF0 = 0;
				ICU::IPR.RXF0 = lvl;
				ICU::IER.RXF0 = ena;
				break;
			case ICU::VECTOR::TXF0:  // CAN0
				ICU::IER.TXF0 = 0;
				ICU::IPR.TXF0 = lvl;
				ICU::IER.TXF0 = ena;
				break;
			case ICU::VECTOR::RXM0:  // CAN0
				ICU::IER.RXM0 = 0;
				ICU::IPR.RXM0 = lvl;
				ICU::IER.RXM0 = ena;
				break;
			case ICU::VECTOR::TXM0:  // CAN0
				ICU::IER.TXM0 = 0;
				ICU::IPR.TXM0 = lvl;
				ICU::IER.TXM0 = ena;
				break;

			case ICU::VECTOR::USBI0:
				ICU::IER.USBI0 = 0;
				ICU::IPR.USBI0 = lvl;
				ICU::IER.USBI0 = ena;
				break;

			case ICU::VECTOR::ELSR18I:
				ICU::IER.ELSR18I = 0;
				ICU::IPR.ELSR18I = lvl;
				ICU::IER.ELSR18I = ena;
				break;
			case ICU::VECTOR::ELSR19I:
				ICU::IER.ELSR19I = 0;
				ICU::IPR.ELSR19I = lvl;
				ICU::IER.ELSR19I = ena;
				break;

			case ICU::VECTOR::RD:
				ICU::IER.RD = 0;
				ICU::IPR.RD = lvl;
				ICU::IER.RD = ena;
				break;
			case ICU::VECTOR::WR:
				ICU::IER.WR = 0;
				ICU::IPR.WR = lvl;
				ICU::IER.WR = ena;
				break;
			case ICU::VECTOR::ERR:
				ICU::IER.ERR = 0;
				ICU::IPR.ERR = lvl;
				ICU::IER.ERR = ena;
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
			case ICU::VECTOR::CMPC3:
				ICU::IER.CMPC3 = 0;
				ICU::IPR.CMPC3 = lvl;
				ICU::IER.CMPC3 = ena;
				break;
			case ICU::VECTOR::CMPC4:
				ICU::IER.CMPC4 = 0;
				ICU::IPR.CMPC4 = lvl;
				ICU::IER.CMPC4 = ena;
				break;
			case ICU::VECTOR::CMPC5:
				ICU::IER.CMPC5 = 0;
				ICU::IPR.CMPC5 = lvl;
				ICU::IER.CMPC5 = ena;
				break;

			default:
				return false;
			}
			return true;
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
			@param[in]	lvl	割り込みレベル（０の場合、割り込み禁止）
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
			@brief  割り込み設定（選択Ａベクター）
			@param[in]	sel		割り込み要因
			@param[in]	task	割り込みタスク
			@param[in]	lvl	割り込みレベル（０の場合、割り込み禁止）
			@return ベクター番号
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR set_interrupt(ICU::VECTOR_SELA sel, utils::TASK task, uint8_t lvl) noexcept
		{
			for(uint8_t i = 208; i <= 255; ++i) {
				auto idx = static_cast<ICU::VECTOR>(i);
				if(lvl > 0) {
					if(ICU::SLIAR[idx] == ICU::VECTOR_SELA::NONE) {
						ICU::IER.enable(idx, 0);
						set_task(idx, task);
						ICU::IPR[idx] = lvl;
						ICU::SLIAR[idx] = sel;
						ICU::IR[idx] = 0;
						ICU::IER.enable(idx, 1);
						return idx;
					}
				} else if(ICU::SLIAR[idx] == sel) {
					ICU::IER.enable(idx, 0);
					set_task(idx, nullptr);
					ICU::SLIAR[idx] = ICU::VECTOR_SELA::NONE;
					ICU::IPR[idx] = 0;
					ICU::IR[idx] = 0;
					return idx;
				}
			}
			return ICU::VECTOR::NONE;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  DMAC 要因の設定
			@param[in]	dma_per	DMAC ペリフェラル
			@param[in]	target	DMA 要因のベクター番号
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		static bool set_dmac(peripheral dma_per, ICU::VECTOR target) noexcept
		{
			switch(dma_per) {
			case peripheral::DMAC0:
				ICU::DMRSR0 = static_cast<uint8_t>(target);
				break;
			case peripheral::DMAC1:
				ICU::DMRSR1 = static_cast<uint8_t>(target);
				break;
			case peripheral::DMAC2:
				ICU::DMRSR2 = static_cast<uint8_t>(target);
				break;
			case peripheral::DMAC3:
				ICU::DMRSR3 = static_cast<uint8_t>(target);
				break;
			case peripheral::DMAC4:
				ICU::DMRSR4 = static_cast<uint8_t>(target);
				break;
			case peripheral::DMAC5:
				ICU::DMRSR5 = static_cast<uint8_t>(target);
				break;
			case peripheral::DMAC6:
				ICU::DMRSR6 = static_cast<uint8_t>(target);
				break;
			case peripheral::DMAC7:
				ICU::DMRSR7 = static_cast<uint8_t>(target);
				break;
			default:
				return false;
				break;
			}
			return true;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUPBE0（エッジ割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group_be0_handler_() noexcept
		{
			uint32_t bits = ICU::GRPBE0() & GROUPBE0_dispatch_.get_mask();
			uint32_t sign = 1;
			for(uint32_t idx = 0; idx < GROUPBE0_dispatch_.size(); ++idx) {
				if(bits & sign) {
					GROUPBE0_dispatch_.run_task(idx);
					ICU::GCRBE0 = sign;
				}
				sign <<= 1;
			}
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUPBL0（レベル割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group_bl0_handler_() noexcept
		{
			uint32_t bits = ICU::GRPBL0() & GROUPBL0_dispatch_.get_mask();
			uint32_t sign = 1;
			for(uint32_t idx = 0; idx < GROUPBL0_dispatch_.size(); ++idx) {
				if(bits & sign) {
					GROUPBL0_dispatch_.run_task(idx);
				}
				sign <<= 1;
			}
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUPBL1（レベル割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group_bl1_handler_() noexcept
		{
			uint32_t bits = ICU::GRPBL1() & GROUPBL1_dispatch_.get_mask();
			uint32_t sign = 1;
			for(uint32_t idx = 0; idx < GROUPBL1_dispatch_.size(); ++idx) {
				if(bits & sign) {
					GROUPBL1_dispatch_.run_task(idx);
				}
				sign <<= 1;
			}
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUPAL0（レベル割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group_al0_handler_() noexcept
		{
			uint32_t bits = ICU::GRPAL0() & GROUPAL0_dispatch_.get_mask();
			uint32_t sign = 1;
			for(uint32_t idx = 0; idx < GROUPAL0_dispatch_.size(); ++idx) {
				if(bits & sign) {
					GROUPAL0_dispatch_.run_task(idx);
				}
				sign <<= 1;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  GROUPBE0 割り込みタスクを登録する @n
					※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	idx		グループ内インデックス
			@param[in]	task	割り込みタスク（※nullptr なら無効）
			@return グループ割り込み以外なら「false」
		*/
		//-----------------------------------------------------------------//
		static bool install_group_task(ICU::VECTOR_BE0 idx, utils::TASK task) noexcept
		{
			bool ena = task != nullptr ? true : false;
			set_interrupt_task(group_be0_handler_, static_cast<uint32_t>(ICU::VECTOR::GROUPBE0));
			auto i = static_cast<uint32_t>(idx);
			bool ret = GROUPBE0_dispatch_.set_task(i, task);
			if(ret && ena) ICU::GENBE0 |= 1 << i;
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  GROUPBL0 割り込みタスクを登録する @n
					※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	idx		グループ内インデックス
			@param[in]	task	割り込みタスク（※nullptr なら無効）
			@return グループ割り込み以外なら「false」
		*/
		//-----------------------------------------------------------------//
		static bool install_group_task(ICU::VECTOR_BL0 idx, utils::TASK task) noexcept
		{
			bool ena = task != nullptr ? true : false;
			set_interrupt_task(group_bl0_handler_, static_cast<uint32_t>(ICU::VECTOR::GROUPBL0));
			auto i = static_cast<uint32_t>(idx);
			bool ret = GROUPBL0_dispatch_.set_task(i, task);
			if(ret && ena) ICU::GENBL0 |= 1 << i;
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  GROUPBL1 割り込みタスクを登録する @n
					※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	idx		グループ内インデックス
			@param[in]	task	割り込みタスク（※nullptr なら無効）
			@return グループ割り込み以外なら「false」
		*/
		//-----------------------------------------------------------------//
		static bool install_group_task(ICU::VECTOR_BL1 idx, utils::TASK task) noexcept
		{
			bool ena = task != nullptr ? true : false;
			set_interrupt_task(group_bl1_handler_, static_cast<uint32_t>(ICU::VECTOR::GROUPBL1));
			auto i = static_cast<uint32_t>(idx);
			bool ret = GROUPBL1_dispatch_.set_task(i, task);
			if(ret && ena) ICU::GENBL1 |= 1 << i;
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  GROUPAL0 割り込みタスクを登録する @n
					※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	idx		グループ内インデックス
			@param[in]	task	割り込みタスク（※nullptr なら無効）
			@return グループ割り込み以外なら「false」
		*/
		//-----------------------------------------------------------------//
		static bool install_group_task(ICU::VECTOR_AL0 idx, utils::TASK task) noexcept
		{
			bool ena = task != nullptr ? true : false;
			set_interrupt_task(group_al0_handler_, static_cast<uint32_t>(ICU::VECTOR::GROUPAL0));
			auto i = static_cast<uint32_t>(idx);
			bool ret = GROUPAL0_dispatch_.set_task(i, task);
			if(ret && ena) ICU::GENAL0 |= 1 << i;
			return ret;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み BE0 に対するベクタを返す
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static ICU::VECTOR get_group_vector(ICU::VECTOR_BE0 vec) noexcept {
			return ICU::VECTOR::GROUPBE0;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み BL0 に対するベクタを返す
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static ICU::VECTOR get_group_vector(ICU::VECTOR_BL0 vec) noexcept {
			return ICU::VECTOR::GROUPBL0;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み BL1 に対するベクタを返す
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static ICU::VECTOR get_group_vector(ICU::VECTOR_BL1 vec) noexcept {
			return ICU::VECTOR::GROUPBL1;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み AL0 に対するベクタを返す
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static ICU::VECTOR get_group_vector(ICU::VECTOR_AL0 vec) noexcept {
			return ICU::VECTOR::GROUPAL0;
		}
	};

	typedef icu_mgr_<void> icu_mgr;

	template <class _> typename icu_mgr_<_>::GROUPBE0_dispatch_t icu_mgr_<_>::GROUPBE0_dispatch_;
	template <class _> typename icu_mgr_<_>::GROUPBL0_dispatch_t icu_mgr_<_>::GROUPBL0_dispatch_;
	template <class _> typename icu_mgr_<_>::GROUPBL1_dispatch_t icu_mgr_<_>::GROUPBL1_dispatch_;
	template <class _> typename icu_mgr_<_>::GROUPAL0_dispatch_t icu_mgr_<_>::GROUPAL0_dispatch_;
}
