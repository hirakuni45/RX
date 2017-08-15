#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ MTU3 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX24T/icu_mgr.hpp"
#include "RX24T/port_map.hpp"
#include "RX24T/power_cfg.hpp"
#include "RX24T/mtu3.hpp"
#include "common/intr_utils.hpp"
#include "common/vect.h"

#include "common/format.hpp"

/// F_PCLKA は変換パラメーター計算で必要で、設定が無いとエラーにします。
#ifndef F_PCLKA
#  error "mtu_io.hpp requires F_PCLKA to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU 制御クラス
		@param[in]	MTU	MTU ユニット
		@param[in]	MTASK	メイン割り込みタスク
		@param[in]	OTASK	オーバーフロー割り込みタスク
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class MTUX, class MTASK = utils::null_task, class OTASK = utils::null_task>
	class mtu_io {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  エッジ・タイプ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class edge_type : uint8_t {
			positive,	///< 立ち上がり
			negative,	///< 立下り
			dual,		///< 両エッジ
		};

	private:

		struct task_t {
			volatile uint16_t	cap_tick_;
			volatile uint16_t	ovf_tick_;
			volatile uint32_t	tgr_adr_;
			volatile uint32_t	cap_count_;
			volatile uint16_t	ovf_limit_;
			volatile uint16_t	ovf_count_;

			task_t() : cap_tick_(0), ovf_tick_(0),
				tgr_adr_(MTUX::TGRA.address()), cap_count_(0),
				ovf_limit_(1221), ovf_count_(0) { }

			void clear() {
				cap_tick_ = 0;
				ovf_tick_ = 0;
				cap_count_ = 0;
				ovf_count_ = 0;
			}

			void load_cap() {
				cap_count_ = rd16_(tgr_adr_);
				cap_count_ |= static_cast<uint32_t>(ovf_tick_) << 16;
			}
		};

		static task_t	task_t_;
		static MTASK	mtask_;
		static OTASK	otask_;

		uint32_t	clk_limit_;

		static INTERRUPT_FUNC void cap_task_()
		{
			++task_t_.cap_tick_;
			task_t_.load_cap();
			mtask_();
			task_t_.ovf_tick_ = 0;
		}

		static INTERRUPT_FUNC void ovf_task_()
		{
			++task_t_.ovf_tick_;
			if(task_t_.ovf_tick_ >= task_t_.ovf_limit_) {
				task_t_.ovf_tick_ = 0;
				MTUX::TCNT = 0;
				++task_t_.ovf_count_;
			}
			otask_();
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		mtu_io() : clk_limit_(F_PCLKA) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  リミット・クロックの設定
			@param[in]	clk	リミット・クロック
		*/
		//-----------------------------------------------------------------//
		void set_limit_clock(uint32_t clk) { clk_limit_ = clk; }


		//-----------------------------------------------------------------//
		/*!
			@brief  インプットキャプチャ開始 @n
					※カウントクロックは「set_limit_clock」により @n
					変更が可能。
			@param[in]	ch		入力チャネル
			@param[in]	et		エッジ・タイプ
			@param[in]	level	割り込みレベル
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start_capture(typename MTUX::channel ch, edge_type et, uint8_t level = 0)
		{
			if(MTUX::get_peripheral() == peripheral::MTU5) {  // MTU5 はインプットキャプチャとして利用不可
				return false;
			}

			uint8_t idx = static_cast<uint8_t>(ch);
			if(idx >= 4) return false; 

			power_cfg::turn(MTUX::get_peripheral());
			MTUX::enable_port(ch);

			uint8_t etd = 0;
			switch(et) {
			case edge_type::positive: etd = 0b1000; break;
			case edge_type::negative: etd = 0b1001; break;
			case edge_type::dual:     etd = 0b1011; break;
			default: break;
			}
			MTUX::TIOR.set(ch, etd);

			uint8_t dv = 0;
			static const uint8_t cclr[4] = { 0b001, 0b010, 0b101, 0b110 };
			// CKEG: 立ち上がりエッジでカウントアップ
			MTUX::TCR  = MTUX::TCR.TPSC.b(dv)
					   | MTUX::TCR.CKEG.b(0b00)
					   | MTUX::TCR.CCLR.b(cclr[idx]);  // ※インプットキャプチャ入力で TCNT はクリア
			MTUX::TCR2  = 0x00;
			MTUX::TMDR1 = 0x00;  // 通常動作

			if(level > 0) {
				set_interrupt_task(ovf_task_, static_cast<uint32_t>(MTUX::get_vec(MTUX::interrupt::OVF)));
				icu_mgr::set_level(MTUX::get_vec(MTUX::interrupt::OVF), level);
				ICU::VECTOR cvec = MTUX::get_vec(static_cast<typename MTUX::interrupt>(ch));
				set_interrupt_task(cap_task_, static_cast<uint32_t>(cvec));
				icu_mgr::set_level(MTUX::get_vec(static_cast<typename MTUX::interrupt>(ch)), level);
				MTUX::TIER = (1 << static_cast<uint8_t>(ch)) | MTUX::TIER.TCIEV.b();
			}

			task_t_.clear();

			// 各チャネルに相当するジャネラルレジスタ
			task_t_.tgr_adr_ = MTUX::TGRA.address() + static_cast<uint32_t>(ch) * 2;
			wr16_(task_t_.tgr_adr_, 0x0000);

			MTUX::TCNT = 0;

			MTUX::enable();

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  インプット・キャプチャ、リミットの設定
			@param[in]	limit	インプット・キャプチャ、リミット
		*/
		//-----------------------------------------------------------------//
		void set_capture_limit(uint16_t limit)
		{
			task_t_.limit_ovf_ = limit;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  インプット・キャプチャのオーバーフローカウント取得
			@return インプット・キャプチャのオーバーフローカウント
		*/
		//-----------------------------------------------------------------//
		uint16_t get_capture_ovf() const
		{
			return task_t_.ovf_count_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  インプット・キャプチャカウント取得
			@return インプット・キャプチャカウント
		*/
		//-----------------------------------------------------------------//
		uint16_t get_capture_tick() const
		{
			return task_t_.cap_tick_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  インプット・キャプチャ値を取得
			@return インプット・キャプチャ値
		*/
		//-----------------------------------------------------------------//
		uint32_t get_capture() const
		{
			return task_t_.cap_count_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  MTASK クラスの参照
			@return MTASK クラス
		*/
		//-----------------------------------------------------------------//
		static MTASK& at_main_task() { return mtask_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  OTASK クラスの参照
			@return OTASK クラス
		*/
		//-----------------------------------------------------------------//
		static OTASK& at_ovfl_task() { return otask_; }
	};

	template <class MTUX, class MTASK, class OTASK>
		typename mtu_io<MTUX, MTASK, OTASK>::task_t mtu_io<MTUX, MTASK, OTASK>::task_t_;
	template <class MTUX, class MTASK, class OTASK> MTASK mtu_io<MTUX, MTASK, OTASK>::mtask_;
	template <class MTUX, class MTASK, class OTASK> OTASK mtu_io<MTUX, MTASK, OTASK>::otask_;
}
