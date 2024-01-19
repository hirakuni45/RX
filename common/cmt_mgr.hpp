#pragma once
//=========================================================================//
/*!	@file
	@brief	RX マイコン・CMT I/O 制御 @n
			コンパイル時、設定周波数を検査して、範囲を超えたらコンパイルを止める事が出来ます。 @n
			Ex: 標準では、1% @n 
			  constexpr uint32_t freq = 1000; @n
			  static_assert(CMT_MGR::probe_freq(freq), "Failed rate accuracy test"); @n
			  ・0.5% にする場合 @n
			  static_assert(CMT_MGR::probe_freq(freq, 5), "Failed rate accuracy test");
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"
#include "common/intr_utils.hpp"
#include "common/time_base.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CMT マネージャー・クラス
		@param[in]	CMT		チャネルクラス
		@param[in]	FUNC	割り込みファンクタクラス型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CMT, class FUNC = utils::null_task>
	class cmt_mgr {
	public:
		typedef CMT cmt_type;	///< CMT チャネル・クラス型

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  レジスタ直接型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class DIRECT : uint16_t {
			MIN = 1,		///< 設定可能な最小値
			MAX = 65535,	///< 設定可能な最大値
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

	private:
		uint32_t	rate_;

		void sleep_() const { asm("nop"); }

		static inline FUNC	func_;

		static inline volatile uint32_t counter_ = 0;

		static INTERRUPT_FUNC void i_task_()
		{
			++counter_;
			func_();
		}

		static constexpr bool calc_freq_(uint32_t freq, uint8_t& cks, uint32_t& cmcor)
		{
			if(freq == 0) return false;

			cmcor = CMT::PCLK / freq / 4;
			cmcor++;
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
			uint32_t rate = CMT::PCLK / cmcor;
			rate /= 8 << (cks * 2);
			return rate;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		cmt_mgr() noexcept : rate_(0) { }


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
			@param[in]	direct	レジスタ直接設定値
			@param[in]	cks		分周器設定型
			@param[in]	level	割り込みレベル（０ならポーリング）
			@param[in]	task	割り込み時に起動する関数 (FreeRTOS 用) @n
								※割り込み関数は属性「INTERRUPT_FUNC」を付加する。
			@return タイマー周波数が範囲を超えた場合「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool start(DIRECT direct, DIVIDE cks, ICU::LEVEL level = ICU::LEVEL::NONE, void (*task)() = nullptr) noexcept
		{
			rate_ = 0;

			power_mgr::turn(CMT::PERIPHERAL);

			CMT::enable(false);

			CMT::CMCNT = 0;
		    CMT::CMCOR = static_cast<uint16_t>(direct);

			counter_ = 0;

			if(level != ICU::LEVEL::NONE) {
				if(task != nullptr) {
					icu_mgr::set_interrupt(CMT::CMI, task, level);
				} else {
					icu_mgr::set_interrupt(CMT::CMI, i_task_, level);
				}
			    CMT::CMCR = CMT::CMCR.CKS.b(static_cast<uint8_t>(cks)) | CMT::CMCR.CMIE.b();
			} else {
				icu_mgr::set_interrupt(CMT::CMI, nullptr, ICU::LEVEL::NONE);
			    CMT::CMCR = CMT::CMCR.CKS.b(static_cast<uint8_t>(cks));
			}
			CMT::enable();

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	freq	タイマー周期（周波数 [Hz]）
			@param[in]	level	割り込みレベル（０ならポーリング）
			@param[in]	task	割り込み時に起動する関数 @n
								※割り込み関数は属性「INTERRUPT_FUNC」を付加する事。
			@return タイマー周波数が範囲を超えた場合「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t freq, ICU::LEVEL level = ICU::LEVEL::NONE, void (*task)() = nullptr) noexcept
		{
			uint8_t cks;
			uint32_t cmcor;
			if(!calc_freq_(freq, cks, cmcor)) {
				return false;
			}

			auto ret = start(static_cast<DIRECT>(cmcor - 1), static_cast<DIVIDE>(cks), level, task);
			rate_ = freq;

			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  廃棄（割り込みを停止して、ユニットを停止）
			@param[in]	power	消費電力を低減しない場合「true」
		*/
		//-----------------------------------------------------------------//
		void destroy(bool power = false) noexcept
		{
		    CMT::CMCR.CMIE = 0;
			CMT::enable(false);
			power_mgr::turn(CMT::PERIPHERAL, power);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みと同期
		*/
		//-----------------------------------------------------------------//
		void sync() const noexcept
		{
			if(icu_mgr::get_level(CMT::CMI) != ICU::LEVEL::NONE) {
				volatile uint32_t cnt = counter_;
				while(cnt == counter_) sleep_();
			} else {
				auto ref = CMT::CMCNT();
				while(ref <= CMT::CMCNT()) sleep_();
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
			@brief	周期を取得
			@param[in]	real	「true」にした場合、設定されている実際の値
			@return 周期
		 */
		//-----------------------------------------------------------------//
		uint32_t get_rate(bool real = false) const noexcept
		{
			if(real) {
				return get_real_freq_(CMT::CMCR.CKS(), static_cast<uint32_t>(CMT::CMCOR()) + 1);
			} else {
				return rate_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターの取得
			@return 割り込みベクター
		*/
		//-----------------------------------------------------------------//
		auto get_intr_vec() const noexcept { return CMT::IVEC; }


		//-----------------------------------------------------------------//
		/*!
			@brief  FUNC クラスの参照
			@return FUNC クラス
		*/
		//-----------------------------------------------------------------//
		static FUNC& at_func() noexcept { return func_; }
	};
}
