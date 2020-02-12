#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600, RX200 グループ・CMT I/O 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/intr_utils.hpp"
#include "common/vect.h"

/// F_PCLKB は周期パラメーター計算で必要で、設定が無いとエラーにします。
#ifndef F_PCLKB
#  error "cmt_io.hpp requires F_PCLKB to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CMT I/O クラス
		@param[in]	CMT	チャネルクラス
		@param[in]	TASK	タイマー動作クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CMT, class TASK = utils::null_task>
	class cmt_io {

		uint8_t		level_;

		void sleep_() const { asm("nop"); }

		static TASK	task_;

		static volatile uint32_t counter_;

		static INTERRUPT_FUNC void i_task_()
		{
			++counter_;
			task_();
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		cmt_io() : level_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	freq	タイマー周波数
			@param[in]	level	割り込みレベル（０ならポーリング）
			@return レンジオーバーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t freq, uint8_t level = 0, void (*task)() = nullptr) noexcept
		{
			if(freq == 0) return false;

			uint32_t cmcor = F_PCLKB / freq / 4;
			if(cmcor & 1) {
				cmcor >>= 1;
				++cmcor;
			} else {
				cmcor >>= 1;
			}

			uint8_t cks = 0;
			while(cmcor > 65536) {
				cmcor >>= 2;
				++cks;
			}
			if(cks > 3 || cmcor == 0) {
				return false;
			}

			level_ = level;

			power_mgr::turn(CMT::get_peripheral());

			CMT::enable(false);

			CMT::CMCNT = 0;
		    CMT::CMCOR = cmcor - 1;

			counter_ = 0;

			auto vec = CMT::get_ivec();
			if(level_ > 0) {
				if(task != nullptr) {
					icu_mgr::set_interrupt(vec, task, level_);
				} else {
					icu_mgr::set_interrupt(vec, i_task_, level_);
				}
			    CMT::CMCR = CMT::CMCR.CKS.b(cks) | CMT::CMCR.CMIE.b();
			} else {
				icu_mgr::set_interrupt(vec, nullptr, 0);
			    CMT::CMCR = CMT::CMCR.CKS.b(cks);
			}
			CMT::enable();

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  廃棄（割り込みを停止して、ユニットを停止）
		*/
		//-----------------------------------------------------------------//
		void destroy() noexcept
		{
		    CMT::CMCR.CMIE = 0;
			CMT::enable(false);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みと同期
		*/
		//-----------------------------------------------------------------//
		void sync() const noexcept
		{
			if(level_ > 0) {
				volatile uint32_t cnt = counter_;
				while(cnt == counter_) sleep_();
			} else {
				auto ref = CMT::CMCNT();
				while(ref <= CMT::CMCNT()) sleep_();
				task_();
				++counter_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みカウンターの値を設定
			@param[in]	n	割り込みカウンターの値
		*/
		//-----------------------------------------------------------------//
		static void set_counter(uint32_t n) noexcept { counter_ = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みカウンターの値を取得
			@return 割り込みカウンターの値
		*/
		//-----------------------------------------------------------------//
		static uint32_t get_counter() noexcept { return counter_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  CMCNT レジスターの値を取得
			@return CMCNT レジスター
		*/
		//-----------------------------------------------------------------//
		uint16_t get_cmt_count() const noexcept { return CMT::CMCNT(); }


		//-----------------------------------------------------------------//
		/*!
			@brief  CMCOR レジスターの値を取得
			@return CMCOR レジスター
		*/
		//-----------------------------------------------------------------//
		uint16_t get_cmp_count() const noexcept { return CMT::CMCOR(); }


		//-----------------------------------------------------------------//
		/*!
			@brief  TASK クラスの参照
			@return TASK クラス
		*/
		//-----------------------------------------------------------------//
		static TASK& at_task() noexcept { return task_; }
	};

	template <class CMT, class TASK> volatile uint32_t cmt_io<CMT, TASK>::counter_ = 0;
	template <class CMT, class TASK> TASK cmt_io<CMT, TASK>::task_;
}
