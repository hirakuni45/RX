#pragma once
//=====================================================================//
/*!	@file
	@brief	RX66T グループ・割り込みマネージャー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX66T/peripheral.hpp"
#include "RX66T/icu.hpp"
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
			@param[in]	icu	割り込み要因
			@param[in]	lvl	割り込みレベル（０の場合、割り込み禁止）
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		static bool set_level(ICU::VECTOR vec, uint8_t lvl) noexcept
		{
			bool ena = lvl != 0 ? true : false;
			switch(vec) {

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
			@return 成功なら「true」
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

			case peripheral::SCI1:
				ICU::IPR.RXI1 = lvl;
				ICU::IER.RXI1 = ena;
				ICU::IPR.TXI1 = lvl;
				ICU::IER.TXI1 = ena;
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

			case peripheral::SCI8:
				ICU::IPR.RXI8 = lvl;
				ICU::IER.RXI8 = ena;
				ICU::IPR.TXI8 = lvl;
				ICU::IER.TXI8 = ena;
				break;
			case peripheral::SCI9:
				ICU::IPR.RXI9 = lvl;
				ICU::IER.RXI9 = ena;
				ICU::IPR.TXI9 = lvl;
				ICU::IER.TXI9 = ena;
				break;

			case peripheral::SCI11:
				ICU::IPR.RXI11 = lvl;
				ICU::IER.RXI11 = ena;
				ICU::IPR.TXI11 = lvl;
				ICU::IER.TXI11 = ena;
				break;
			case peripheral::SCI12:
				ICU::IPR.RXI12 = lvl;
				ICU::IER.RXI12 = ena;
				ICU::IPR.TXI12 = lvl;
				ICU::IER.TXI12 = ena;
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


#if 0
		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターの取得
			@param[in]	per	周辺機器タイプ
			@param[in]	id	割り込み要因
			@return 割り込みベクター（マッチするベクターが無ければ「VEC0」を返す）
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
				return ICU::VECTOR::VEC0;
			}

			return ICU::VECTOR::INTB128;
		}
#endif


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
