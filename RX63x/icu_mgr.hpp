#pragma once
//=====================================================================//
/*!	@file
	@brief	RX631/RX63N グループ・割り込みマネージャー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"
#include "RX600/icu_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  割り込みマネージャー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class _>
	class icu_mgr_ {

		typedef icu_utils::dispatch<ICU::GROUP0> GROUP0_dispatch_t;
		typedef icu_utils::dispatch<ICU::GROUP1> GROUP1_dispatch_t;
		typedef icu_utils::dispatch<ICU::GROUP2> GROUP2_dispatch_t;
		typedef icu_utils::dispatch<ICU::GROUP3> GROUP3_dispatch_t;
		typedef icu_utils::dispatch<ICU::GROUP4> GROUP4_dispatch_t;
		typedef icu_utils::dispatch<ICU::GROUP5> GROUP5_dispatch_t;
		typedef icu_utils::dispatch<ICU::GROUP6> GROUP6_dispatch_t;
		typedef icu_utils::dispatch<ICU::GROUP12> GROUP12_dispatch_t;

		static GROUP0_dispatch_t GROUP0_dispatch_;
		static GROUP1_dispatch_t GROUP1_dispatch_;
		static GROUP2_dispatch_t GROUP2_dispatch_;
		static GROUP3_dispatch_t GROUP3_dispatch_;
		static GROUP4_dispatch_t GROUP4_dispatch_;
		static GROUP5_dispatch_t GROUP5_dispatch_;
		static GROUP6_dispatch_t GROUP6_dispatch_;
		static GROUP12_dispatch_t GROUP12_dispatch_;

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
			@brief  通常割り込みに対するベクタを返す（ダミー）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static ICU::VECTOR get_group_vector(ICU::VECTOR vec) noexcept {
			return ICU::VECTOR::NONE;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み GROUP0 に対するベクタを返す
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static ICU::VECTOR get_group_vector(ICU::GROUP0 vec) noexcept {
			return ICU::VECTOR::GROUP0;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み GROUP1 に対するベクタを返す
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static ICU::VECTOR get_group_vector(ICU::GROUP1 vec) noexcept {
			return ICU::VECTOR::GROUP1;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み GROUP2 に対するベクタを返す
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static ICU::VECTOR get_group_vector(ICU::GROUP2 vec) noexcept {
			return ICU::VECTOR::GROUP2;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み GROUP3 に対するベクタを返す
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static ICU::VECTOR get_group_vector(ICU::GROUP3 vec) noexcept {
			return ICU::VECTOR::GROUP3;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み GROUP4 に対するベクタを返す
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static ICU::VECTOR get_group_vector(ICU::GROUP4 vec) noexcept {
			return ICU::VECTOR::GROUP4;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み GROUP5 に対するベクタを返す
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static ICU::VECTOR get_group_vector(ICU::GROUP5 vec) noexcept {
			return ICU::VECTOR::GROUP5;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み GROUP6 に対するベクタを返す
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static ICU::VECTOR get_group_vector(ICU::GROUP6 vec) noexcept {
			return ICU::VECTOR::GROUP6;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み GROUP12 に対するベクタを返す
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static ICU::VECTOR get_group_vector(ICU::GROUP12 vec) noexcept {
			return ICU::VECTOR::GROUP12;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUP0（レベル割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group0_handler_() noexcept
		{
			GROUP0_dispatch_.run<ICU::GCR00_>(ICU::GCR00, ICU::GRP00());
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUP1（レベル割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group1_handler_() noexcept
		{
			GROUP1_dispatch_.run<ICU::GCR01_>(ICU::GCR01, ICU::GRP01());
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUP2（レベル割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group2_handler_() noexcept
		{
			GROUP2_dispatch_.run<ICU::GCR02_>(ICU::GCR02, ICU::GRP02());
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUP3（レベル割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group3_handler_() noexcept
		{
			GROUP3_dispatch_.run<ICU::GCR03_>(ICU::GCR03, ICU::GRP03());
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUP4（レベル割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group4_handler_() noexcept
		{
			GROUP4_dispatch_.run<ICU::GCR04_>(ICU::GCR04, ICU::GRP04());
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUP5（レベル割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group5_handler_() noexcept
		{
			GROUP5_dispatch_.run<ICU::GCR05_>(ICU::GCR05, ICU::GRP05());
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUP6（レベル割り込み）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static INTERRUPT_FUNC void group6_handler_() noexcept
		{
			GROUP6_dispatch_.run<ICU::GCR06_>(ICU::GCR06, ICU::GRP06());
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み・ハンドラ GROUP12（エッジ割り込み）
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
			@param[in]	task	割り込みタスク（※nullptr なら無効）
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
					※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	grpv	GROUP0 グループ割り込み要因
			@param[in]	task	割り込みタスク（nullptr なら不許可にする）
		*/
		//-----------------------------------------------------------------//
		static void install_group_task(ICU::GROUP0 grpv, icu_utils::GTASK task) noexcept
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
			@brief  GROUP1 割り込みタスクを登録する @n
					※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	grpv	GROUP1 グループ割り込み要因
			@param[in]	task	割り込みタスク（nullptr なら不許可にする）
		*/
		//-----------------------------------------------------------------//
		static void install_group_task(ICU::GROUP1 grpv, icu_utils::GTASK task) noexcept
		{
			ICU::GEN01.set(grpv, false);
			set_task(get_group_vector(grpv), group1_handler_);
			GROUP1_dispatch_.set_task(grpv, task);
			if(task != nullptr) {
				ICU::GEN01.set(grpv);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  GROUP2 割り込みタスクを登録する @n
					※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	grpv	GROUP2 グループ割り込み要因
			@param[in]	task	割り込みタスク（nullptr なら不許可にする）
		*/
		//-----------------------------------------------------------------//
		static void install_group_task(ICU::GROUP2 grpv, icu_utils::GTASK task) noexcept
		{
			ICU::GEN02.set(grpv, false);
			set_task(get_group_vector(grpv), group2_handler_);
			GROUP2_dispatch_.set_task(grpv, task);
			if(task != nullptr) {
				ICU::GEN02.set(grpv);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  GROUP3 割り込みタスクを登録する @n
					※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	grpv	GROUP3 グループ割り込み要因
			@param[in]	task	割り込みタスク（nullptr なら不許可にする）
		*/
		//-----------------------------------------------------------------//
		static void install_group_task(ICU::GROUP3 grpv, icu_utils::GTASK task) noexcept
		{
			ICU::GEN03.set(grpv, false);
			set_task(get_group_vector(grpv), group3_handler_);
			GROUP3_dispatch_.set_task(grpv, task);
			if(task != nullptr) {
				ICU::GEN03.set(grpv);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  GROUP4 割り込みタスクを登録する @n
					※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	grpv	GROUP4 グループ割り込み要因
			@param[in]	task	割り込みタスク（nullptr なら不許可にする）
		*/
		//-----------------------------------------------------------------//
		static void install_group_task(ICU::GROUP4 grpv, icu_utils::GTASK task) noexcept
		{
			ICU::GEN04.set(grpv, false);
			set_task(get_group_vector(grpv), group4_handler_);
			GROUP4_dispatch_.set_task(grpv, task);
			if(task != nullptr) {
				ICU::GEN04.set(grpv);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  GROUP5 割り込みタスクを登録する @n
					※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	grpv	GROUP5 グループ割り込み要因
			@param[in]	task	割り込みタスク（nullptr なら不許可にする）
		*/
		//-----------------------------------------------------------------//
		static void install_group_task(ICU::GROUP5 grpv, icu_utils::GTASK task) noexcept
		{
			ICU::GEN05.set(grpv, false);
			set_task(get_group_vector(grpv), group5_handler_);
			GROUP5_dispatch_.set_task(grpv, task);
			if(task != nullptr) {
				ICU::GEN05.set(grpv);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  GROUP6 割り込みタスクを登録する @n
					※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	grpv	GROUP6 グループ割り込み要因
			@param[in]	task	割り込みタスク（nullptr なら不許可にする）
		*/
		//-----------------------------------------------------------------//
		static void install_group_task(ICU::GROUP6 grpv, icu_utils::GTASK task) noexcept
		{
			ICU::GEN06.set(grpv, false);
			set_task(get_group_vector(grpv), group6_handler_);
			GROUP6_dispatch_.set_task(grpv, task);
			if(task != nullptr) {
				ICU::GEN06.set(grpv);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  GROUP12 割り込みタスクを登録する @n
					※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	grpv	GROUP12 グループ割り込み要因
			@param[in]	task	割り込みタスク（nullptr なら不許可にする）
		*/
		//-----------------------------------------------------------------//
		static void install_group_task(ICU::GROUP12 grpv, icu_utils::GTASK task) noexcept
		{
			ICU::GEN12.set(grpv, false);
			set_task(get_group_vector(grpv), group12_handler_);
			GROUP12_dispatch_.set_task(grpv, task);
			if(task != nullptr) {
				ICU::GEN12.set(grpv);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み設定（グループ GROUP0）
			@param[in]	grpv	GROUP0 グループ割り込み要因
			@param[in]	task	割り込みタスク @n
								※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	lvl		割り込みレベル @n
								※グループ割り込みレベルが、設定レベルより高い場合に設定される。
			@return ベクター番号
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR set_interrupt(ICU::GROUP0 grpv, icu_utils::GTASK task, ICU::LEVEL lvl) noexcept
		{
			install_group_task(grpv, task);
			if(get_level(ICU::VECTOR::GROUP0) < lvl) {
				set_level(ICU::VECTOR::GROUP0, lvl);
			}
			return ICU::VECTOR::GROUP0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み設定（グループ GROUP1）
			@param[in]	grpv	GROUP1 グループ割り込み要因
			@param[in]	task	割り込みタスク @n
								※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	lvl		割り込みレベル @n
								※グループ割り込みレベルが、設定レベルより高い場合に設定される。
			@return ベクター番号
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR set_interrupt(ICU::GROUP1 grpv, icu_utils::GTASK task, ICU::LEVEL lvl) noexcept
		{
			install_group_task(grpv, task);
			if(get_level(ICU::VECTOR::GROUP1) < lvl) {
				set_level(ICU::VECTOR::GROUP1, lvl);
			}
			return ICU::VECTOR::GROUP1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み設定（グループ GROUP2）
			@param[in]	grpv	GROUP2 グループ割り込み要因
			@param[in]	task	割り込みタスク @n
								※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	lvl		割り込みレベル @n
								※グループ割り込みレベルが、設定レベルより高い場合に設定される。
			@return ベクター番号
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR set_interrupt(ICU::GROUP2 grpv, icu_utils::GTASK task, ICU::LEVEL lvl) noexcept
		{
			install_group_task(grpv, task);
			if(get_level(ICU::VECTOR::GROUP2) < lvl) {
				set_level(ICU::VECTOR::GROUP2, lvl);
			}
			return ICU::VECTOR::GROUP2;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み設定（グループ GROUP3）
			@param[in]	grpv	GROUP3 グループ割り込み要因
			@param[in]	task	割り込みタスク @n
								※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	lvl		割り込みレベル @n
								※グループ割り込みレベルが、設定レベルより高い場合に設定される。
			@return ベクター番号
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR set_interrupt(ICU::GROUP3 grpv, icu_utils::GTASK task, ICU::LEVEL lvl) noexcept
		{
			install_group_task(grpv, task);
			if(get_level(ICU::VECTOR::GROUP3) < lvl) {
				set_level(ICU::VECTOR::GROUP3, lvl);
			}
			return ICU::VECTOR::GROUP3;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み設定（グループ GROUP4）
			@param[in]	grpv	GROUP4 グループ割り込み要因
			@param[in]	task	割り込みタスク @n
								※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	lvl		割り込みレベル @n
								※グループ割り込みレベルが、設定レベルより高い場合に設定される。
			@return ベクター番号
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR set_interrupt(ICU::GROUP4 grpv, icu_utils::GTASK task, ICU::LEVEL lvl) noexcept
		{
			install_group_task(grpv, task);
			if(get_level(ICU::VECTOR::GROUP4) < lvl) {
				set_level(ICU::VECTOR::GROUP4, lvl);
			}
			return ICU::VECTOR::GROUP4;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み設定（グループ GROUP5）
			@param[in]	grpv	GROUP5 グループ割り込み要因
			@param[in]	task	割り込みタスク @n
								※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	lvl		割り込みレベル @n
								※グループ割り込みレベルが、設定レベルより高い場合に設定される。
			@return ベクター番号
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR set_interrupt(ICU::GROUP5 grpv, icu_utils::GTASK task, ICU::LEVEL lvl) noexcept
		{
			install_group_task(grpv, task);
			if(get_level(ICU::VECTOR::GROUP5) < lvl) {
				set_level(ICU::VECTOR::GROUP5, lvl);
			}
			return ICU::VECTOR::GROUP5;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み設定（グループ GROUP6）
			@param[in]	grpv	GROUP6 グループ割り込み要因
			@param[in]	task	割り込みタスク @n
								※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	lvl		割り込みレベル @n
								※グループ割り込みレベルが、設定レベルより高い場合に設定される。
			@return ベクター番号
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR set_interrupt(ICU::GROUP6 grpv, icu_utils::GTASK task, ICU::LEVEL lvl) noexcept
		{
			install_group_task(grpv, task);
			if(get_level(ICU::VECTOR::GROUP6) < lvl) {
				set_level(ICU::VECTOR::GROUP6, lvl);
			}
			return ICU::VECTOR::GROUP6;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み設定（グループ GROUP12）
			@param[in]	grpv	GROUP12 グループ割り込み要因
			@param[in]	task	割り込みタスク @n
								※ここで登録するタスクは「割り込みアトリビュート」無しの関数を登録する事
			@param[in]	lvl		割り込みレベル @n
								※グループ割り込みレベルが、設定レベルより高い場合に設定される。
			@return ベクター番号
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR set_interrupt(ICU::GROUP12 grpv, icu_utils::GTASK task, ICU::LEVEL lvl) noexcept
		{
			install_group_task(grpv, task);
			if(get_level(ICU::VECTOR::GROUP12) < lvl) {
				set_level(ICU::VECTOR::GROUP12, lvl);
			}
			return ICU::VECTOR::GROUP12;
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
	template <class _> typename icu_mgr_<_>::GROUP0_dispatch_t icu_mgr_<_>::GROUP0_dispatch_;
	template <class _> typename icu_mgr_<_>::GROUP1_dispatch_t icu_mgr_<_>::GROUP1_dispatch_;
	template <class _> typename icu_mgr_<_>::GROUP2_dispatch_t icu_mgr_<_>::GROUP2_dispatch_;
	template <class _> typename icu_mgr_<_>::GROUP3_dispatch_t icu_mgr_<_>::GROUP3_dispatch_;
	template <class _> typename icu_mgr_<_>::GROUP4_dispatch_t icu_mgr_<_>::GROUP4_dispatch_;
	template <class _> typename icu_mgr_<_>::GROUP5_dispatch_t icu_mgr_<_>::GROUP5_dispatch_;
	template <class _> typename icu_mgr_<_>::GROUP6_dispatch_t icu_mgr_<_>::GROUP6_dispatch_;
	template <class _> typename icu_mgr_<_>::GROUP12_dispatch_t icu_mgr_<_>::GROUP12_dispatch_;


	typedef icu_mgr_<void> icu_mgr;
}
