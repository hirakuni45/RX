#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600, RX200 グループ・CMT I/O 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"
#include "common/intr_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CMT マネージャー・クラス
		@param[in]	CMT	チャネルクラス
		@param[in]	TASK	タイマー動作クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CMT, class TASK = utils::null_task>
	class cmt_mgr {
	public:
		typedef CMT value_type;		///< CMT チャネル・クラス型

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
		uint8_t		level_;
		uint32_t	rate_;

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
		cmt_mgr() noexcept : level_(0), rate_(0) { }


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
		bool start(DIRECT direct, DIVIDE cks, uint8_t level = 0, void (*task)() = nullptr) noexcept
		{
			rate_ = 0;
			level_ = level;

			power_mgr::turn(CMT::PERIPHERAL);

//			CMT::CMCR.CMIE = 0;
//			icu_mgr::set_interrupt(CMT::IVEC, nullptr, 0);
			CMT::enable(false);

			CMT::CMCNT = 0;
		    CMT::CMCOR = static_cast<uint16_t>(direct);

			counter_ = 0;

			if(level_ > 0) {
				if(task != nullptr) {
					icu_mgr::set_interrupt(CMT::IVEC, task, level_);
				} else {
					icu_mgr::set_interrupt(CMT::IVEC, i_task_, level_);
				}
			    CMT::CMCR = CMT::CMCR.CKS.b(static_cast<uint8_t>(cks)) | CMT::CMCR.CMIE.b();
			} else {
				icu_mgr::set_interrupt(CMT::IVEC, nullptr, 0);
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
		bool start(uint32_t freq, uint8_t level = 0, void (*task)() = nullptr) noexcept
		{
			if(freq == 0) return false;

			uint32_t cmcor = CMT::PCLK / freq / 4;
			cmcor++;
			cmcor >>= 1;

			uint8_t cks = 0;
			while(cmcor > 65536) {
				cmcor >>= 2;
				++cks;
			}

			if(cks > 3 || cmcor == 0) {
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
			@brief	周期を取得
			@param[in]	real	「true」にした場合、内部で計算されたリアルな値
			@return 周期
		 */
		//-----------------------------------------------------------------//
		uint32_t get_rate(bool real = false) const noexcept
		{
			if(real) {
				uint32_t rate = CMT::PCLK / (static_cast<uint32_t>(CMT::CMCOR()) + 1);
				rate /= 8 << (CMT::CMCR.CKS() * 2);
				return rate;
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
			@brief  TASK クラスの参照
			@return TASK クラス
		*/
		//-----------------------------------------------------------------//
		static TASK& at_task() noexcept { return task_; }
	};

	template <class CMT, class TASK> volatile uint32_t cmt_mgr<CMT, TASK>::counter_ = 0;
	template <class CMT, class TASK> TASK cmt_mgr<CMT, TASK>::task_;
}
