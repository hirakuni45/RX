#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600 グループ・ICU ユーティリティー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
// #include <functional>
#include "common/io_utils.hpp"
#include "common/vect.h"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  割り込みユーティリテー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct icu_utils {

		typedef void (*ITASK)();
//		typedef std::function<void ()> GTASK;
		typedef void (*GTASK)();

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  dispatch class
			@param[in]	GRPV	グループ・ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<typename GRPV>
		class dispatch {

			GTASK	task_[static_cast<uint32_t>(GRPV::NUM_)];

		public:
			//-----------------------------------------------------------------//
			/*!
				@brief	コンストラクター
			*/
			//-----------------------------------------------------------------//
			dispatch() noexcept : task_{ nullptr } { }


			//-----------------------------------------------------------------//
			/*!
				@brief	分岐タスクを登録
				@param[in]	grpv	グループベクター型
				@param[in]	task	タスク
			*/
			//-----------------------------------------------------------------//
			void set_task(GRPV grpv, GTASK task) noexcept
			{
				task_[static_cast<uint32_t>(grpv)] = task;
			}


			//-----------------------------------------------------------------//
			/*!
				@brief	分岐タスクを取得
				@param[in]	grpv	グループベクター型
				@return 分岐タスク
			*/
			//-----------------------------------------------------------------//
			auto get_task(GRPV grpv) const noexcept
			{
				return task_[static_cast<uint32_t>(grpv)];
			}


			//-----------------------------------------------------------------//
			/*!
				@brief	タスクを実行、クリアオブジェクト付き
				@param[in]	clr		クリア・オブジェクト
				@param[in]	togo	起動フラグ
			*/
			//-----------------------------------------------------------------//
			template<class CLR>
			void run(CLR& clr, uint32_t togo) const noexcept
			{
				for(uint32_t i = 0; i < static_cast<uint32_t>(GRPV::NUM_); ++i) {
					if((togo & (1 << i)) != 0 && task_[i] != nullptr) {
						(*task_[i])();
						clr.set(static_cast<GRPV>(i), false);
					}
					togo &= ~(1 << i);
					if(togo == 0) break;
				}
			}


			//-----------------------------------------------------------------//
			/*!
				@brief	タスクを実行
				@param[in]	togo	起動フラグ
			*/
			//-----------------------------------------------------------------//
			void run(uint32_t togo) const noexcept
			{
				for(uint32_t i = 0; i < static_cast<uint32_t>(GRPV::NUM_); ++i) {
					if((togo & (1 << i)) != 0 && task_[i] != nullptr) {
						(*task_[i])();
					}
					togo &= ~(1 << i);
					if(togo == 0) break;
				}
			}
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み要因選択レジスタ・テンプレート
			@param[in]	base		ベース・アドレス
			@param[in]	VECTOR		割り込みベクター型
			@param[in]	INTR_SEL	割り込み要因型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base, typename VECTOR, typename INTR_SEL>
		struct slixr_t {

			void set(VECTOR vec, INTR_SEL sel) noexcept {
				wr8_(base + static_cast<uint8_t>(vec), static_cast<uint8_t>(sel));
			}

			INTR_SEL get(VECTOR vec) noexcept {
				return static_cast<INTR_SEL>(rd8_(base + static_cast<uint8_t>(vec)));
			}

			volatile INTR_SEL& operator [] (VECTOR vec) {
				return *reinterpret_cast<volatile INTR_SEL*>(base + static_cast<uint8_t>(vec));
			}
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  選択型割り込みＡ設定テンプレート
			@param[in]	ICU			ICU クラス
			@param[in]	VEC_TYPE	割り込み要因型
			@param[in]	TASK_TYPE	タスクタイプ
			@param[in]	sel			割り込み要因
			@param[in]	task		割り込みタスク
			@param[in]	lvl			割り込みレベル
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		template <class ICU, typename VEC_TYPE, typename TASK_TYPE, uint16_t org, uint16_t end>
		static typename ICU::VECTOR set_interruptSELA(VEC_TYPE sel, TASK_TYPE task, uint8_t lvl) noexcept
		{
			// sel 要因があれば消す。
			for(uint16_t i = org; i < (end + 1); ++i) {
				auto idx = static_cast<typename ICU::VECTOR>(i);
				if(ICU::SLIAR[idx] == sel) {
					ICU::IER.enable(idx, 0);
					set_interrupt_task(nullptr, i);
					ICU::IPR[idx] = 0;
					ICU::SLIAR[idx] = VEC_TYPE::NONE;
					ICU::IR[idx] = 0;
				}
			}
			if(lvl == 0 || task == nullptr) return ICU::VECTOR::NONE;

			for(uint16_t i = org; i < (end + 1); ++i) {
				auto idx = static_cast<typename ICU::VECTOR>(i);
				if(ICU::SLIAR[idx] == VEC_TYPE::NONE) {
					ICU::IER.enable(idx, 0);
					set_interrupt_task(task, i);
					ICU::IPR[idx] = lvl;
					ICU::SLIAR[idx] = sel;
					ICU::IR[idx] = 0;
					ICU::IER.enable(idx, 1);
					return idx;
				}
			}

			return ICU::VECTOR::NONE;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  選択型割り込みＢ設定テンプレート
			@param[in]	ICU			ICU クラス
			@param[in]	VEC_TYPE	割り込み要因型
			@param[in]	TASK_TYPE	タスクタイプ
			@param[in]	sel			割り込み要因
			@param[in]	task		割り込みタスク
			@param[in]	lvl			割り込みレベル
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		template <class ICU, typename VEC_TYPE, typename TASK_TYPE, uint16_t org, uint16_t end>
		static typename ICU::VECTOR set_interruptSELB(VEC_TYPE sel, TASK_TYPE task, uint8_t lvl) noexcept
		{
			// sel 要因があれば消す。
			for(uint16_t i = org; i < (end + 1); ++i) {
				auto idx = static_cast<typename ICU::VECTOR>(i);
				if(ICU::SLIBR[idx] == sel) {
					ICU::IER.enable(idx, 0);
					set_interrupt_task(nullptr, i);
					ICU::IPR[idx] = 0;
					ICU::SLIBR[idx] = VEC_TYPE::NONE;
					ICU::IR[idx] = 0;
				}
			}
			if(lvl == 0 || task == nullptr) return ICU::VECTOR::NONE;

			for(uint16_t i = org; i < (end + 1); ++i) {
				auto idx = static_cast<typename ICU::VECTOR>(i);
				if(ICU::SLIBR[idx] == VEC_TYPE::NONE) {
					ICU::IER.enable(idx, 0);
					set_interrupt_task(task, i);
					ICU::IPR[idx] = lvl;
					ICU::SLIBR[idx] = sel;
					ICU::IR[idx] = 0;
					ICU::IER.enable(idx, 1);
					return idx;
				}
			}

			return ICU::VECTOR::NONE;
		}
	};
}
