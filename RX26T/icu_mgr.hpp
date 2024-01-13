#pragma once
//=========================================================================//
/*!	@file
	@brief	RX26T グループ・割り込みマネージャー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX26T/peripheral.hpp"
#include "RX26T/icu.hpp"
#include "RX600/dmac.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  割り込みマネージャー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class _>
	class icu_mgr_ {

		typedef icu_utils::dispatch<ICU::GROUPBL0> GROUPBL0_dispatch_t;
		typedef icu_utils::dispatch<ICU::GROUPBL1> GROUPBL1_dispatch_t;
		typedef icu_utils::dispatch<ICU::GROUPBL2> GROUPBL2_dispatch_t;
		typedef icu_utils::dispatch<ICU::GROUPAL0> GROUPAL0_dispatch_t;
		typedef icu_utils::dispatch<ICU::GROUPAL1> GROUPAL1_dispatch_t;

		static GROUPBL0_dispatch_t GROUPBL0_dispatch_;
		static GROUPBL1_dispatch_t GROUPBL1_dispatch_;
		static GROUPBL2_dispatch_t GROUPBL2_dispatch_;
		static GROUPAL0_dispatch_t GROUPAL0_dispatch_;
		static GROUPAL1_dispatch_t GROUPAL1_dispatch_;

		static constexpr uint8_t SELECTA_ORG = 208;
		static constexpr uint8_t SELECTA_END = 255;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みタスクを設定
			@param[in]	vec		割り込み要因
			@param[in]	task	割り込みタスク
		*/
		//-----------------------------------------------------------------//
		static void set_task(ICU::VECTOR vec, icu_utils::ITASK task) noexcept {
			set_interrupt_task(task, static_cast<uint32_t>(vec));
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みレベルを設定する
			@param[in]	vec	通常割り込みベクター型
			@param[in]	lvl	割り込みレベル（０の場合、割り込み禁止）
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		static void set_level(ICU::VECTOR vec, ICU::LEVEL lvl) noexcept
		{
			bool ena = lvl != ICU::LEVEL::NONE ? true : false;
			ICU::IER.enable(vec, 0);
			ICU::IPR[vec] = static_cast<uint8_t>(lvl);
			ICU::IER.enable(vec, ena);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みレベルを取得する
			@param[in]	vec	割り込み要因
			@return 割り込みレベル
		*/
		//-----------------------------------------------------------------//
		static auto get_level(ICU::VECTOR vec) noexcept {
			return static_cast<ICU::LEVEL>(ICU::IPR[vec]);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  選択型割り込みレベルを取得する
			@param[in]	vec	割り込み要因
			@return 割り込みレベル
		*/
		//-----------------------------------------------------------------//
		static auto get_level(ICU::SELECTA sel) noexcept {

			return get_level(icu_utils::get_interruptSELA<ICU, ICU::SELECTA, SELECTA_ORG, SELECTA_END>(sel));
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み設定（通常ベクター）
			@param[in]	vec		割り込み要因
			@param[in]	task	割り込みタスク
			@param[in]	lvl	割り込みレベル（０の場合、割り込み禁止）
			@return ベクター番号
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR set_interrupt(ICU::VECTOR vec, icu_utils::ITASK task, ICU::LEVEL lvl) noexcept {
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
		static ICU::VECTOR set_interrupt(ICU::SELECTA sel, icu_utils::ITASK task, ICU::LEVEL lvl) noexcept
		{
			return icu_utils::set_interruptSELA<ICU, ICU::SELECTA, SELECTA_ORG, SELECTA_END>(sel, task, lvl);
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
			@brief  通常割り込みに対するベクタを返す（ダミー）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static ICU::VECTOR get_group_vector(ICU::VECTOR vec) noexcept {
			return ICU::VECTOR::NONE;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み BL0 に対するベクタを返す
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static ICU::VECTOR get_group_vector(ICU::GROUPBL0 vec) noexcept {
			return ICU::VECTOR::GROUPBL0;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み BL1 に対するベクタを返す
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static ICU::VECTOR get_group_vector(ICU::GROUPBL1 vec) noexcept {
			return ICU::VECTOR::GROUPBL1;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み BL2 に対するベクタを返す
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static ICU::VECTOR get_group_vector(ICU::GROUPBL2 vec) noexcept {
			return ICU::VECTOR::GROUPBL2;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み AL0 に対するベクタを返す
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static ICU::VECTOR get_group_vector(ICU::GROUPAL0 vec) noexcept {
			return ICU::VECTOR::GROUPAL0;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み AL0 に対するベクタを返す
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static ICU::VECTOR get_group_vector(ICU::GROUPAL1 vec) noexcept {
			return ICU::VECTOR::GROUPAL1;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUPBL0（レベル割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group_bl0_handler_() noexcept
		{
			GROUPBL0_dispatch_.run(ICU::GRPBL0());
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUPBL1（レベル割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group_bl1_handler_() noexcept
		{
			GROUPBL1_dispatch_.run(ICU::GRPBL1());
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUPBL2（レベル割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group_bl2_handler_() noexcept
		{
			GROUPBL1_dispatch_.run(ICU::GRPBL2());
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUPAL0（レベル割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group_al0_handler_() noexcept
		{
			GROUPAL0_dispatch_.run(ICU::GRPAL0());
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUPAL1（レベル割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group_al1_handler_() noexcept
		{
			GROUPAL1_dispatch_.run(ICU::GRPAL1());
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  GROUPBL0 割り込みタスクを登録する @n
					※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	grpv	BL0 グループ割り込み要因
			@param[in]	task	割り込みタスク（※nullptr なら無効）
		*/
		//-----------------------------------------------------------------//
		static void install_group_task(ICU::GROUPBL0 grpv, icu_utils::GTASK task) noexcept
		{
			ICU::GENBL0.set(grpv, false);
			set_task(get_group_vector(grpv), group_bl0_handler_);
			GROUPBL0_dispatch_.set_task(grpv, task);
			if(task != nullptr) {
				ICU::GENBL0.set(grpv);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  GROUPBL1 割り込みタスクを登録する @n
					※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	grpv	BL1 グループ割り込み要因
			@param[in]	task	割り込みタスク（※nullptr なら無効）
		*/
		//-----------------------------------------------------------------//
		static void install_group_task(ICU::GROUPBL1 grpv, icu_utils::GTASK task) noexcept
		{
			ICU::GENBL1.set(grpv, false);
			set_task(get_group_vector(grpv), group_bl1_handler_);
			GROUPBL1_dispatch_.set_task(grpv, task);
			if(task != nullptr) {
				ICU::GENBL1.set(grpv);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  GROUPBL2 割り込みタスクを登録する @n
					※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	grpv	BL2 グループ割り込み要因
			@param[in]	task	割り込みタスク（※nullptr なら無効）
		*/
		//-----------------------------------------------------------------//
		static void install_group_task(ICU::GROUPBL2 grpv, icu_utils::GTASK task) noexcept
		{
			ICU::GENBL2.set(grpv, false);
			set_task(get_group_vector(grpv), group_bl2_handler_);
			GROUPBL2_dispatch_.set_task(grpv, task);
			if(task != nullptr) {
				ICU::GENBL2.set(grpv);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  GROUPAL0 割り込みタスクを登録する @n
					※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	grpv	AL0 グループ割り込み要因
			@param[in]	task	割り込みタスク（※nullptr なら無効）
		*/
		//-----------------------------------------------------------------//
		static void install_group_task(ICU::GROUPAL0 grpv, icu_utils::GTASK task) noexcept
		{
			ICU::GENAL0.set(grpv, false);
			set_task(get_group_vector(grpv), group_al0_handler_);
			GROUPAL0_dispatch_.set_task(grpv, task);
			if(task != nullptr) {
				ICU::GENAL0.set(grpv);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  GROUPAL1 割り込みタスクを登録する @n
					※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	grpv	AL1 グループ割り込み要因
			@param[in]	task	割り込みタスク（※nullptr なら無効）
		*/
		//-----------------------------------------------------------------//
		static void install_group_task(ICU::GROUPAL1 grpv, icu_utils::GTASK task) noexcept
		{
			ICU::GENAL1.set(grpv, false);
			set_task(get_group_vector(grpv), group_al1_handler_);
			GROUPAL1_dispatch_.set_task(grpv, task);
			if(task != nullptr) {
				ICU::GENAL1.set(grpv);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み設定（グループ BL0）
			@param[in]	grpv	BL0 グループ割り込み要因
			@param[in]	task	割り込みタスク @n
								※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	lvl		割り込みレベル @n
								※グループ割り込みレベルが、設定レベルより高い場合に設定される。
			@return ベクター番号
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR set_interrupt(ICU::GROUPBL0 grpv, icu_utils::GTASK task, ICU::LEVEL lvl) noexcept
		{
			install_group_task(grpv, task);
			if(get_level(ICU::VECTOR::GROUPBL0) < lvl) {
				set_level(ICU::VECTOR::GROUPBL0, lvl);
			}
			return ICU::VECTOR::GROUPBL0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み設定（グループ BL1）
			@param[in]	grpv	BL1 グループ割り込み要因
			@param[in]	task	割り込みタスク @n
								※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	lvl		割り込みレベル @n
								※グループ割り込みレベルが、設定レベルより高い場合に設定される。
			@return ベクター番号
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR set_interrupt(ICU::GROUPBL1 grpv, icu_utils::GTASK task, ICU::LEVEL lvl) noexcept
		{
			install_group_task(grpv, task);
			if(get_level(ICU::VECTOR::GROUPBL1) < lvl) {
				set_level(ICU::VECTOR::GROUPBL1, lvl);
			}
			return ICU::VECTOR::GROUPBL1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み設定（グループ BL2）
			@param[in]	grpv	BL2 グループ割り込み要因
			@param[in]	task	割り込みタスク @n
								※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	lvl		割り込みレベル @n
								※グループ割り込みレベルが、設定レベルより高い場合に設定される。
			@return ベクター番号
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR set_interrupt(ICU::GROUPBL2 grpv, icu_utils::GTASK task, ICU::LEVEL lvl) noexcept
		{
			install_group_task(grpv, task);
			if(get_level(ICU::VECTOR::GROUPBL2) < lvl) {
				set_level(ICU::VECTOR::GROUPBL2, lvl);
			}
			return ICU::VECTOR::GROUPBL2;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み設定（グループ AL0）
			@param[in]	grpv	AL0 グループ割り込み要因
			@param[in]	task	割り込みタスク @n
								※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	lvl		割り込みレベル @n
								※グループ割り込みレベルが、設定レベルより高い場合に設定される。
			@return ベクター番号
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR set_interrupt(ICU::GROUPAL0 grpv, icu_utils::GTASK task, ICU::LEVEL lvl) noexcept
		{
			install_group_task(grpv, task);
			if(get_level(ICU::VECTOR::GROUPAL0) < lvl) {
				set_level(ICU::VECTOR::GROUPAL0, lvl);
			}
			return ICU::VECTOR::GROUPAL0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み設定（グループ AL1）
			@param[in]	grpv	AL1 グループ割り込み要因
			@param[in]	task	割り込みタスク @n
								※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	lvl		割り込みレベル @n
								※グループ割り込みレベルが、設定レベルより高い場合に設定される。
			@return ベクター番号
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR set_interrupt(ICU::GROUPAL1 grpv, icu_utils::GTASK task, ICU::LEVEL lvl) noexcept
		{
			install_group_task(grpv, task);
			if(get_level(ICU::VECTOR::GROUPAL1) < lvl) {
				set_level(ICU::VECTOR::GROUPAL1, lvl);
			}
			return ICU::VECTOR::GROUPAL1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  高速割り込み設定
			@param[in]	vec		割り込み要因
			@param[in]	ena		不許可にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable_fast_interrupt(ICU::VECTOR vec, bool ena = true) noexcept
		{
			if(ena) {
				ICU::FIR = ICU::FIR.FVCT.b(static_cast<uint8_t>(vec)) | ICU::FIR.FIEN.b();
			} else {
				ICU::FIR = 0;
			}
		}
	};
	template <class _> typename icu_mgr_<_>::GROUPBL0_dispatch_t icu_mgr_<_>::GROUPBL0_dispatch_;
	template <class _> typename icu_mgr_<_>::GROUPBL1_dispatch_t icu_mgr_<_>::GROUPBL1_dispatch_;
	template <class _> typename icu_mgr_<_>::GROUPBL2_dispatch_t icu_mgr_<_>::GROUPBL2_dispatch_;
	template <class _> typename icu_mgr_<_>::GROUPAL0_dispatch_t icu_mgr_<_>::GROUPAL0_dispatch_;
	template <class _> typename icu_mgr_<_>::GROUPAL1_dispatch_t icu_mgr_<_>::GROUPAL1_dispatch_;

	typedef icu_mgr_<void> icu_mgr;
}
