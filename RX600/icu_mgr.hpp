#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・割り込みマネージャー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2018 Kunihito Hiramatsu @n
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
	class icu_mgr {

		static utils::dispatch<ICU::VECTOR::GROUPBE0, 2>  GROUPBE0_dispatch_;
		static utils::dispatch<ICU::VECTOR::GROUPBL0, 32> GROUPBL0_dispatch_;
		static utils::dispatch<ICU::VECTOR::GROUPBL1, 32> GROUPBL1_dispatch_;
		static utils::dispatch<ICU::VECTOR::GROUPAL0, 22> GROUPAL0_dispatch_;
		static utils::dispatch<ICU::VECTOR::GROUPAL1, 12> GROUPAL1_dispatch_;

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

			case ICU::VECTOR::CMWI0:
				ICU::IER.CMWI0 = 0;
				ICU::IPR.CMWI0 = lvl;
				ICU::IER.CMWI0 = ena;
				break;
			case ICU::VECTOR::CMWI1:
				ICU::IER.CMWI1 = 0;
				ICU::IPR.CMWI1 = lvl;
				ICU::IER.CMWI1 = ena;
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
			case ICU::VECTOR::GROUPAL1:
				ICU::IER.GROUPAL1 = 0;
				ICU::IPR.GROUPAL1 = lvl;
				ICU::IER.GROUPAL1 = ena;
				break;
			default:
				return false;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みレベルを設定する（選択型Ｂ）
			@param[in]	icu	割り込み要因
			@param[in]	lvl	割り込みレベル（０の場合、割り込み禁止）
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		static bool set_level(ICU::VECTOR_SELB vec, uint8_t lvl) noexcept
		{
			bool ena = lvl != 0 ? true : false;
			switch(vec) {
			case ICU::VECTOR_SELB::CMI2:
//				ICU::IER.CMI0 = 0;
//				ICU::IPR.CMI0 = lvl;
//				ICU::IER.CMI0 = ena;
				break;
			case ICU::VECTOR_SELB::CMI3:
				break;
			default:
				return false;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みレベルを設定する
			@param[in]	per	周辺機器タイプ
			@param[in]	lvl	割り込みレベル（０の場合、割り込み禁止）
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		static bool set_level(peripheral per, uint8_t lvl) noexcept
		{
			bool ena = lvl != 0 ? true : false;
			switch(per) {
			case peripheral::DMAC0:
				ICU::IER.DMAC0I = 0;
				ICU::IPR.DMAC0I = lvl;
				ICU::IER.DMAC0I = ena;
				break;
			case peripheral::DMAC1:
				ICU::IER.DMAC1I = 0;
				ICU::IPR.DMAC1I = lvl;
				ICU::IER.DMAC1I = ena;
				break;
			case peripheral::DMAC2:
				ICU::IER.DMAC2I = 0;
				ICU::IPR.DMAC2I = lvl;
				ICU::IER.DMAC2I = ena;
				break;
			case peripheral::DMAC3:
				ICU::IER.DMAC3I = 0;
				ICU::IPR.DMAC3I = lvl;
				ICU::IER.DMAC3I = ena;
				break;
			case peripheral::DMAC4:
			case peripheral::DMAC5:
			case peripheral::DMAC6:
			case peripheral::DMAC7:
				ICU::IER.DMAC74I = 0;
				ICU::IPR.DMAC74I = lvl;
				ICU::IER.DMAC74I = ena;
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
			case peripheral::SCIF8:
				ICU::IPR.RXIF8 = lvl;
				ICU::IER.RXIF8 = ena;
				ICU::IPR.TXIF8 = lvl;
				ICU::IER.TXIF8 = ena;
				break;
			case peripheral::SCIF9:
				ICU::IPR.RXIF9 = lvl;
				ICU::IER.RXIF9 = ena;
				ICU::IPR.TXIF9 = lvl;
				ICU::IER.TXIF9 = ena;
				break;
			case peripheral::SCIF10:
				ICU::IPR.RXIF10 = lvl;
				ICU::IER.RXIF10 = ena;
				ICU::IPR.TXIF10 = lvl;
				ICU::IER.TXIF10 = ena;
				break;
			case peripheral::SCIF11:
				ICU::IPR.RXIF11 = lvl;
				ICU::IER.RXIF11 = ena;
				ICU::IPR.TXIF11 = lvl;
				ICU::IER.TXIF11 = ena;
				break;
			case peripheral::SCI12:
				ICU::IPR.RXI12 = lvl;
				ICU::IER.RXI12 = ena;
				ICU::IPR.TXI12 = lvl;
				ICU::IER.TXI12 = ena;
				break;

			case peripheral::TPU0:
			case peripheral::TPU1:
			case peripheral::TPU2:
			case peripheral::TPU3:
			case peripheral::TPU4:
			case peripheral::TPU5:
				break;

			case peripheral::ETHERC0:
				break;
			case peripheral::ETHERC1:
				break;

			case peripheral::IRQ0:
				ICU::IPR.IRQ0 = lvl;
				ICU::IR.IRQ0 = 0;
				ICU::IER.IRQ0 = ena;
				break;
			case peripheral::IRQ1:
				ICU::IPR.IRQ1 = lvl;
				ICU::IR.IRQ1 = 0;
				ICU::IER.IRQ1 = ena;
				break;
			case peripheral::IRQ2:
				ICU::IPR.IRQ2 = lvl;
				ICU::IR.IRQ2 = 0;
				ICU::IER.IRQ2 = ena;
				break;
			case peripheral::IRQ3:
				ICU::IPR.IRQ3 = lvl;
				ICU::IR.IRQ3 = 0;
				ICU::IER.IRQ3 = ena;
				break;
			case peripheral::IRQ4:
				ICU::IPR.IRQ4 = lvl;
				ICU::IR.IRQ4 = 0;
				ICU::IER.IRQ4 = ena;
				break;
			case peripheral::IRQ5:
				ICU::IPR.IRQ5 = lvl;
				ICU::IR.IRQ5 = 0;
				ICU::IER.IRQ5 = ena;
				break;
			case peripheral::IRQ6:
				ICU::IPR.IRQ6 = lvl;
				ICU::IR.IRQ6 = 0;
				ICU::IER.IRQ6 = ena;
				break;
			case peripheral::IRQ7:
				ICU::IPR.IRQ7 = lvl;
				ICU::IR.IRQ7 = 0;
				ICU::IER.IRQ7 = ena;
				break;

			default:
				return false;
				break;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターの取得
			@param[in]	per	周辺機器タイプ
			@param[in]	id	割り込み要因
			@return 割り込みベクター（マッチするベクターが無ければ「NONE」を返す）
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_vector(peripheral per, uint8_t id) noexcept
		{
			switch(per) {
			case peripheral::TPU0:
			case peripheral::TPU1:
			case peripheral::TPU2:
			case peripheral::TPU3:
			case peripheral::TPU4:
			case peripheral::TPU5:
				// INTB128 to INTB207
				for(uint8_t i = 128; i <= 207; ++i) {
					
				}
				break;
			default:
				return ICU::VECTOR::NONE;
			}

			return ICU::VECTOR::INTB128;
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

#if defined(SIG_RX65N)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUPBL2（レベル割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group_bl2_handler_() noexcept
		{
			uint32_t bits = ICU::GRPBL2() & GROUPBL2_dispatch_.get_mask();
			uint32_t sign = 1;
			for(uint32_t idx = 0; idx < GROUPBL2_dispatch_.size(); ++idx) {
				if(bits & sign) {
					GROUPBL2_dispatch_.run_task(idx);
				}
				sign <<= 1;
			}
		}
#endif

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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUPAL1（レベル割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group_al1_handler_() noexcept
		{
			uint32_t bits = ICU::GRPAL1() & GROUPAL1_dispatch_.get_mask();
			uint32_t sign = 1;
			for(uint32_t idx = 0; idx < GROUPAL1_dispatch_.size(); ++idx) {
				if(bits & sign) {
					GROUPAL1_dispatch_.run_task(idx);
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

#if defined(SIG_RX65N)
		//-----------------------------------------------------------------//
		/*!
			@brief  GROUPBL2 割り込みタスクを登録する @n
					※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	idx		グループ内インデックス
			@param[in]	task	割り込みタスク（※nullptr なら無効）
			@return グループ割り込み以外なら「false」
		*/
		//-----------------------------------------------------------------//
		static bool install_group_task(ICU::VECTOR_BL2 idx, utils::TASK task) noexcept
		{
			bool ena = task != nullptr ? true : false;
			set_interrupt_task(group_bl2_handler_, static_cast<uint32_t>(ICU::VECTOR::GROUPBL2));
			auto i = static_cast<uint32_t>(idx);
			bool ret = GROUPBL2_dispatch_.set_task(i, task);
			if(ret && ena) ICU::GENBL2 |= 1 << i;
			return ret;
		}
#endif


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


		//-----------------------------------------------------------------//
		/*!
			@brief  GROUPAL1 割り込みタスクを登録する @n
					※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	idx		グループ内インデックス
			@param[in]	task	割り込みタスク（※nullptr なら無効）
			@return グループ割り込み以外なら「false」
		*/
		//-----------------------------------------------------------------//
		static bool install_group_task(ICU::VECTOR_AL1 idx, utils::TASK task) noexcept
		{
			bool ena = task != nullptr ? true : false;
			set_interrupt_task(group_al1_handler_, static_cast<uint32_t>(ICU::VECTOR::GROUPAL1));
			auto i = static_cast<uint32_t>(idx);
			bool ret = GROUPAL1_dispatch_.set_task(i, task);
			if(ret && ena) ICU::GENAL1 |= 1 << i;
			return ret;
		}
	};
}
