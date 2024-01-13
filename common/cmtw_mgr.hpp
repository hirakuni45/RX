#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・CMTW 管理
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2023 Kunihito Hiramatsu @n
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
		@param[in]	CMTW	チャネル・クラス
		@param[in]	FUNC	割り込みファンクタクラス型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CMTW, class FUNC = utils::null_task>
	class cmtw_mgr : public cmtw_base {
	public:

		typedef CMTW value_type;	///< チャネル・クラス型

	private:
		uint8_t		level_;

		void sleep_() const { asm("nop"); }

		static FUNC	func_;

		static volatile uint32_t counter_;

		static INTERRUPT_FUNC void i_task_()
		{
			++counter_;
			func_();
		}

		static constexpr bool calc_freq_(uint32_t freq, uint8_t& cks, uint32_t& cmcor)
		{
			if(freq == 0) return false;

			cmcor = CMTW::PCLK / freq / 4;
			++cmcor;
			cmcor >>= 1;

			cks = 0;
			while(cmcor > 65536) {
				cmcor >>= 2;
				++cks;
			}
			if(cks > 3 || cmcor == 0) {
				return false;
			}

			return true;
		}

		static constexpr uint32_t get_real_freq_(uint8_t cks, uint32_t cmcor)
		{
			uint32_t rate = CMTW::PCLK / cmcor;
			rate /= 8 << (cks * 2);
			return rate;
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
			@brief	設定周波数の誤差を検証
			@param[in]	freq	周波数
			@param[in]	thper	許容誤差（通常 1.0%） @n
								百分率を 10 倍した値を設定
			@return 誤差範囲なら「true」
		 */
		//-----------------------------------------------------------------//
		static constexpr bool probe_freq(uint32_t freq, uint32_t thper = 10) noexcept
		{
			uint8_t cks = 0;
			uint32_t cmcor = 0;
			if(!calc_freq_(freq, cks, cmcor)) {
				return false;
			}

			auto rate = get_real_freq_(cks, cmcor);
			auto d = freq * thper;
			if((rate * 1000) < (freq * 1000 - d) || (freq * 1000 + d) < (rate * 1000)) {
				return false;
			}

			return true;
		}


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
			uint8_t cks;
			uint32_t cmcor;
			if(!calc_freq_(freq, cks, cmcor)) {
				return false;
			}

			level_ = level;

			power_mgr::turn(CMTW::PERIPHERAL);

			CMTW::CMWSTR = 0;

			CMTW::CMWCNT = 0;
		    CMTW::CMWCOR = cmcor - 1;

			counter_ = 0;

			auto vec = CMTW::IVEC;
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

	template <class CMTW, class FUNC> volatile uint32_t cmtw_mgr<CMTW, FUNC>::counter_ = 0;
	template <class CMTW, class FUNC> FUNC cmtw_mgr<CMTW, FUNC>::func_;
}
