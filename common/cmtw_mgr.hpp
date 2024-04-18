#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600/RX700 グループ・CMTW マネージャー @n
			※仕様として、1Hz 以下の周波数を設定出来ない。（改善の余地）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"
#include "common/intr_utils.hpp"
#include "common/vect.h"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CMTW ベースクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct cmtw_base {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  レジスタ直接型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class DIRECT : uint32_t {
			MIN = 1,			///< 設定可能な最小値
			MAX = 0xffff'ffff,	///< 設定可能な最大値
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  分周器型（逆数）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class DIVIDE : uint8_t {
			I8,		///< 1/8
			I32,	///< 1/32
			I128,	///< 1/128
			I512,	///< 1/512
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CMTW モード型
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
		uint32_t		rate_;
		ICU::LEVEL		level_;

		void sleep_() const { asm("nop"); }

		static inline FUNC	func_;

		static inline volatile uint32_t counter_;

		static INTERRUPT_FUNC void i_task_()
		{
			++counter_;
			func_();
		}

		static constexpr bool calc_freq_(uint32_t freq, uint8_t& cks, uint64_t& cmcor)
		{
			if(freq == 0) return false;

			cmcor = static_cast<uint64_t>(CMTW::PCLK) / freq / 4;
			++cmcor;
			cmcor >>= 1;
			cks = 0;
			while(cmcor > 0x1'0000'0000) {
				cmcor >>= 2;
				++cks;
			}
			if(cks > 3 || cmcor == 0) {
				return false;
			}

			return true;
		}

		static constexpr uint32_t get_real_freq_(uint8_t cks, uint64_t cmcor)
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
		cmtw_mgr() noexcept : rate_(0), level_(ICU::LEVEL::NONE) { }


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
			uint64_t cmcor = 0;
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
			@brief  レジスタ直、開始
			@param[in]	direct	レジスタ直接設定値
			@param[in]	cks		分周器設定型
			@param[in]	level	割り込みレベル（０ならポーリング）
			@return タイマー周波数が範囲を超えた場合「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool start(DIRECT direct, DIVIDE cks, ICU::LEVEL level = ICU::LEVEL::NONE) noexcept
		{
			rate_ = 0;

			level_ = level;

			power_mgr::turn(CMTW::PERIPHERAL);

			CMTW::CMWSTR = 0;

			CMTW::CMWCNT = 0;
		    CMTW::CMWCOR = static_cast<uint32_t>(direct) - 1;

			counter_ = 0;

			CMTW::CMWIOR.CMWE = 1;

			auto vec = CMTW::CMWI;
			if(level_ != ICU::LEVEL::NONE) {
				icu_mgr::set_interrupt(vec, i_task_, level_);
			    CMTW::CMWCR = CMTW::CMWCR.CKS.b(static_cast<uint8_t>(cks)) | CMTW::CMWCR.CMWIE.b();
			} else {
				icu_mgr::set_interrupt(vec, nullptr, ICU::LEVEL::NONE);
			    CMTW::CMWCR = CMTW::CMWCR.CKS.b(static_cast<uint8_t>(cks));
			}
			CMTW::CMWSTR.STR = 1;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  インターバル・タイマー開始
			@param[in]	freq	タイマー周波数
			@param[in]	level	割り込みレベル（NONE ならポーリング）
			@return レンジオーバーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t freq, ICU::LEVEL level = ICU::LEVEL::NONE) noexcept
		{
			uint8_t cks;
			uint64_t cmwcor;
			if(!calc_freq_(freq, cks, cmwcor)) {
				return false;
			}

			auto ret = start(static_cast<DIRECT>(cmwcor - 1), static_cast<DIVIDE>(cks), level);

			rate_ = freq;

			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  許可／不許可（再開／停止）
			@param[in] ena	停止の場合「false」
		*/
		//-----------------------------------------------------------------//
		void enable(bool ena = true) noexcept
		{
			if(CMTW::CMSTR.STR() != ena) {
				CMTW::CMSTR.STR = ena;
			} 
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  廃棄（割り込みを停止して、ユニットを停止）
			@param[in]	power	消費電力を低減しない場合「true」
		*/
		//-----------------------------------------------------------------//
		void destroy(bool power = false) noexcept
		{
		    CMTW::CMWCR.CMWIE = 0;
			CMTW::CMSTR = 0;
			power_mgr::turn(CMTW::PERIPHERAL, power);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みと同期
		*/
		//-----------------------------------------------------------------//
		void sync() const noexcept
		{
			if(level_ != ICU::LEVEL::NONE) {
				volatile uint32_t cnt = counter_;
				while(cnt == counter_) sleep_();
			} else {
				auto ref = CMTW::CMWCNT();
				while(ref <= CMTW::CMWCNT()) sleep_();
				func_();
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
			@brief	周期を取得
			@param[in]	real	「true」にした場合、設定されている実際の値
			@return 周期
		 */
		//-----------------------------------------------------------------//
		uint32_t get_rate(bool real = false) const noexcept
		{
			if(real) {
				return get_real_freq_(CMTW::CMWCR.CKS(), CMTW::CMWCOR() + 1);
			} else {
				return rate_;
			}
		}


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
}
