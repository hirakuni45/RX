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
			@brief  グループ割り込み dispatch クラス
			@param[in]	GRPV	グループ・ベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<typename GRPV>
		class dispatch {

			static constexpr auto NUM = static_cast<uint32_t>(GRPV::NUM_);
			uint32_t	bits_[NUM];
			GTASK		task_[NUM];

		public:
			//-----------------------------------------------------------------//
			/*!
				@brief	コンストラクター
			*/
			//-----------------------------------------------------------------//
			constexpr dispatch() noexcept :
				bits_{ 0 }, task_{ nullptr }
			{ }


			//-----------------------------------------------------------------//
			/*!
				@brief	タスクを登録
				@param[in]	grpv	グループベクター型
				@param[in]	task	タスク
			*/
			//-----------------------------------------------------------------//
			void set_task(GRPV grpv, GTASK task) noexcept
			{
				uint32_t bits = 1 << static_cast<uint32_t>(grpv);
				for(uint32_t i = 0; i < NUM; ++i) {
					if(bits_[i] == bits) {
						bits_[i] = 0;
						task_[i] = nullptr;
						break;
					}
				}
				for(uint32_t i = 0; i < NUM; ++i) {
					if(bits_[i] == 0) {
						bits_[i] = bits;
						task_[i] = task;
						break;
					}
				}
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
				for(uint32_t i = 0; i < NUM; ++i) {
					if(bits_[i] == 0) break;
					if((bits_[i] & togo) != 0 && task_[i] != nullptr) {
						(*task_[i])();
						clr.set(static_cast<GRPV>(i), false);
					}
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
				for(uint32_t i = 0; i < NUM; ++i) {
					if(bits_[i] == 0) break;
					if((bits_[i] & togo) != 0 && task_[i] != nullptr) {
						(*task_[i])();
					}
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
			@brief  選択型割り込みＡベクターの取得
			@param[in]	ICU		ICU クラス
			@param[in]	SELT	割り込み要因型
			@param[in]	org		開始ベクタ
			@param[in]	end		終了ベクタ
			@return 割り込みベクター（要因が無ければ、NONE を返す）
		*/
		//-----------------------------------------------------------------//
		template <class ICU, typename SELT, uint16_t org, uint16_t end>
		static typename ICU::VECTOR get_interruptSELA(SELT sel) noexcept
		{
			for(uint16_t i = org; i < (end + 1); ++i) {
				auto vec = static_cast<typename ICU::VECTOR>(i);
				if(ICU::SLIAR[vec] == sel) {
					return vec;
				}
			}
			return ICU::VECTOR::NONE;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  選択型割り込みＢベクターの取得
			@param[in]	ICU		ICU クラス
			@param[in]	SELT	割り込み要因型
			@param[in]	org		開始ベクタ
			@param[in]	end		終了ベクタ
			@return 割り込みベクター（要因が無ければ、NONE を返す）
		*/
		//-----------------------------------------------------------------//
		template <class ICU, typename SELT, uint16_t org, uint16_t end>
		static typename ICU::VECTOR get_interruptSELB(SELT sel) noexcept
		{
			for(uint16_t i = org; i < (end + 1); ++i) {
				auto vec = static_cast<typename ICU::VECTOR>(i);
				if(ICU::SLIBR[vec] == sel) {
					return vec;
				}
			}
			return ICU::VECTOR::NONE;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  選択型割り込みＡ設定テンプレート
			@param[in]	ICU		ICU クラス
			@param[in]	SELT	割り込み要因型
			@param[in]	org		開始ベクタ
			@param[in]	end		終了ベクタ
			@param[in]	sel		割り込み要因
			@param[in]	task	割り込みタスク
			@param[in]	lvl		割り込みレベル
			@return 成功なら、選択した割り込みベクターを返す
		*/
		//-----------------------------------------------------------------//
		template <class ICU, typename SELT, uint16_t org, uint16_t end>
		static typename ICU::VECTOR set_interruptSELA(SELT sel, ITASK task, typename ICU::LEVEL lvl) noexcept
		{
			// sel 要因があれば消す。
			for(uint16_t i = org; i < (end + 1); ++i) {
				auto idx = static_cast<typename ICU::VECTOR>(i);
				if(ICU::SLIAR[idx] == sel) {
					ICU::IER.enable(idx, 0);
					set_interrupt_task(nullptr, i);
					ICU::IPR[idx] = 0;
					ICU::SLIAR[idx] = SELT::NONE;
					ICU::IR[idx] = 0;
				}
			}
			if(lvl == ICU::LEVEL::NONE || task == nullptr) return ICU::VECTOR::NONE;

			for(uint16_t i = org; i < (end + 1); ++i) {
				auto idx = static_cast<typename ICU::VECTOR>(i);
				if(ICU::SLIAR[idx] == SELT::NONE) {
					ICU::IER.enable(idx, 0);
					set_interrupt_task(task, i);
					ICU::IPR[idx] = static_cast<uint8_t>(lvl);
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
			@param[in]	ICU		ICU クラス
			@param[in]	SELT	割り込み要因型
			@param[in]	org		開始ベクタ
			@param[in]	end		終了ベクタ
			@param[in]	sel		割り込み要因
			@param[in]	task	割り込みタスク
			@param[in]	lvl		割り込みレベル
			@return 成功なら、選択した割り込みベクターを返す
		*/
		//-----------------------------------------------------------------//
		template <class ICU, typename SELT, uint16_t org, uint16_t end>
		static typename ICU::VECTOR set_interruptSELB(SELT sel, ITASK task, typename ICU::LEVEL lvl) noexcept
		{
			// sel 要因があれば消す。
			for(uint16_t i = org; i < (end + 1); ++i) {
				auto idx = static_cast<typename ICU::VECTOR>(i);
				if(ICU::SLIBR[idx] == sel) {
					ICU::IER.enable(idx, 0);
					set_interrupt_task(nullptr, i);
					ICU::IPR[idx] = 0;
					ICU::SLIBR[idx] = SELT::NONE;
					ICU::IR[idx] = 0;
				}
			}
			if(lvl == ICU::LEVEL::NONE || task == nullptr) return ICU::VECTOR::NONE;

			for(uint16_t i = org; i < (end + 1); ++i) {
				auto idx = static_cast<typename ICU::VECTOR>(i);
				if(ICU::SLIBR[idx] == SELT::NONE) {
					ICU::IER.enable(idx, 0);
					set_interrupt_task(task, i);
					ICU::IPR[idx] = static_cast<uint8_t>(lvl);
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
