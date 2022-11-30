#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63T グループ・割り込みマネージャー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"
#include "common/vect.h"
#include "RX600/icu_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  割り込みマネージャー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class _>
	class icu_mgr_ {

		typedef icu_utils::dispatch<ICU::VECTOR_GROUP0> GROUP0_dispatch_t;
		typedef icu_utils::dispatch<ICU::VECTOR_GROUP12> GROUP12_dispatch_t;

		static GROUP0_dispatch_t GROUP0_dispatch_;
		static GROUP12_dispatch_t GROUP12_dispatch_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みタスクを設定
			@param[in]	vec		割り込み要因
			@param[in]	task	割り込みタスク
		*/
		//-----------------------------------------------------------------//
		static void set_task(ICU::VECTOR vec, icu_utils::ITASK task) noexcept
		{
			set_interrupt_task(task, static_cast<uint32_t>(vec));
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みを設定する（ベクター別）
			@param[in]	vec	割り込みベクター
			@param[in]	lvl	割り込みレベル（０の場合、割り込み禁止）
		*/
		//-----------------------------------------------------------------//
		static void set_level(ICU::VECTOR vec, uint8_t lvl) noexcept
		{
			bool ena = lvl != 0 ? true : false;
			ICU::IER.enable(vec, 0);
			ICU::IPR[vec] = lvl;
			ICU::IER.enable(vec, ena);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みレベルを取得する
			@param[in]	vec	割り込み要因
			@return 割り込みレベル
		*/
		//-----------------------------------------------------------------//
		static uint8_t get_level(ICU::VECTOR vec) noexcept
		{
			return ICU::IPR[vec];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み設定（通常ベクター）
			@param[in]	vec		割り込み要因
			@param[in]	task	割り込みタスク
			@param[in]	lvl		割り込みレベル（０の場合、割り込み禁止）
			@return ベクター番号
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR set_interrupt(ICU::VECTOR vec, icu_utils::ITASK task, uint8_t lvl) noexcept
		{
			set_task(vec, task);
			set_level(vec, lvl);
			return vec;
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
			default:
				return false;
				break;
			}
			return true;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  通常割り込みに対するグループベクタを返す
			@return グループベクターでは無いので「NONE]を返す。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static ICU::VECTOR get_group_vector(ICU::VECTOR vec) noexcept
		{
			return ICU::VECTOR::NONE;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUP0 ベクターの取得
			@param[in]	gvec	グループベクター型
			@return グループベクター
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static ICU::VECTOR get_group_vector(ICU::VECTOR_GROUP0 gvec) noexcept
		{
			return ICU::VECTOR::GROUP0;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUP12 ベクターの取得
			@param[in]	gvec	グループベクター型
			@return グループベクター
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static ICU::VECTOR get_group_vector(ICU::VECTOR_GROUP12 gvec) noexcept
		{
			return ICU::VECTOR::GROUP12;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUP0（エッジ割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group0_handler_() noexcept
		{
			GROUP12_dispatch_.run<ICU::GCR00_>(ICU::GCR00, ICU::GRP00());
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUP12（レベル割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group12_handler_() noexcept
		{
			GROUP12_dispatch_.run(ICU::GRP12());
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  グループ割り込み設定のダミー
			@param[in]	vec		割り込みベクター型
			@param[in]	task	割り込みタスク
			@return グループ割り込み以外なら「false」
		*/
		//-----------------------------------------------------------------//
		static bool install_group_task(ICU::VECTOR vec, icu_utils::GTASK task) noexcept
		{
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  GROUP0 割り込みタスクを登録する @n
					※ここで登録するタスクは「割り込みアトリビュート」無しの通常関数を登録する事
			@param[in]	grpv	グループベクター型
			@param[in]	task	割り込みタスク
		*/
		//-----------------------------------------------------------------//
		static void install_group_task(ICU::VECTOR_GROUP0 grpv, icu_utils::GTASK task) noexcept
		{
			ICU::GEN00.set(grpv, false);
			set_task(get_group_vector(grpv), group0_handler_);
			GROUP0_dispatch_.set_task(grpv, task);
			if(task != nullptr) {
				ICU::GEN00.set(grpv);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  GROUPBL0 割り込みタスクを登録する @n
					※ここで登録するタスクは「割り込みアトリビュート」無しの通常関数を登録する事
			@param[in]	grpv	グループベクター型
			@param[in]	task	割り込みタスク
		*/
		//-----------------------------------------------------------------//
		static void install_group_task(ICU::VECTOR_GROUP12 grpv, icu_utils::GTASK task) noexcept
		{
			ICU::GEN12.set(grpv, false);
			set_task(get_group_vector(grpv), group12_handler_);
			GROUP12_dispatch_.set_task(grpv, task);
			if(task != nullptr) {
				ICU::GEN12.set(grpv);
			}
		}
	};
	template <class _> typename icu_mgr_<_>::GROUP0_dispatch_t icu_mgr_<_>::GROUP0_dispatch_;
	template <class _> typename icu_mgr_<_>::GROUP12_dispatch_t icu_mgr_<_>::GROUP12_dispatch_;

	typedef icu_mgr_<void> icu_mgr;
}
