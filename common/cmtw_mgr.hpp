#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・CMTW 管理
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/intr_utils.hpp"
#include "common/vect.h"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CMTW ベースクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class cmtw_base {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CMTW ベースクラス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class MODE : uint8_t {
			COUNT,		///< 周期カウント
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CMTW 管理クラス
		@param[in]	CMTW	チャネルクラス
		@param[in]	FUNC	タイマー動作、ファンクタクラス型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CMTW, class FUNC = utils::null_task>
	class cmtw_mgr : public cmtw_base {

		uint8_t		level_;

		void sleep_() const { asm("nop"); }

		static FUNC	func_;

		static volatile uint32_t counter_;

		static INTERRUPT_FUNC void i_task_()
		{
			++counter_;
			func_();
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		cmtw_mgr() : level_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	freq	タイマー周波数
			@param[in]	level	割り込みレベル（０ならポーリング）
			@return レンジオーバーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t freq, uint8_t level = 0) noexcept
		{
			if(freq == 0) return false;

			uint32_t cmcor = CMTW::PCLK / freq / 4;
			++cmcor;
			cmcor >>= 1;

			uint8_t cks = 0;
			while(cmcor > 65536) {
				cmcor >>= 2;
				++cks;
			}
			if(cks > 3 || cmcor == 0) {
				return false;
			}

			level_ = level;

			power_mgr::turn(CMTW::get_peripheral());

			CMTW::CMWSTR = 0;

			CMTW::CMWCNT = 0;
		    CMTW::CMWCOR = cmcor - 1;

			counter_ = 0;

			auto vec = CMTW::get_ivec();
			if(level_ > 0) {
				icu_mgr::set_interrupt(vec, i_task_, level_);
			    CMTW::CMCR = CMTW::CMCR.CKS.b(cks) | CMTW::CMCR.CMIE.b();
			} else {
				icu_mgr::set_interrupt(vec, nullptr, 0);
			    CMTW::CMCR = CMTW::CMCR.CKS.b(cks);
			}
			CMTW::CMWSTR = 1;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  廃棄（割り込みを停止して、ユニットを停止）
		*/
		//-----------------------------------------------------------------//
		void destroy() noexcept
		{
		    CMTW::CMCR.CMIE = 0;
			CMTW::enable(false);
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
				auto ref = CMTW::CMWCNT();
				while(ref <= CMTW::CMWCNT()) sleep_();
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
			@brief  CMWCNT レジスターの値を取得
			@return CMWCNT レジスター
		*/
		//-----------------------------------------------------------------//
		auto get_cmt_count() const noexcept { return CMTW::CMWCNT(); }


		//-----------------------------------------------------------------//
		/*!
			@brief  CMWCOR レジスターの値を取得
			@return CMWCOR レジスター
		*/
		//-----------------------------------------------------------------//
		auto get_cmp_count() const noexcept { return CMTW::CMWCOR(); }


		//-----------------------------------------------------------------//
		/*!
			@brief  FUNC クラスの参照
			@return FUNC クラス
		*/
		//-----------------------------------------------------------------//
		static FUNC& at_func() noexcept { return func_; }
	};

	template <class CMTW, class FUNC> volatile uint32_t cmtw_io<CMTW, FUNC>::counter_ = 0;
	template <class CMTW, class FUNC> FUNC cmtw_io<CMTW, FUNC>::task_;
}
