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
		@param[in]	TASK	割り込みタスク
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class MTUX, class TASK = utils::null_task>
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
			dual = 2,	///< 両エッジ
		};

	private:

		struct task_t {
			volatile uint16_t	cap_cnt_;
			volatile uint16_t	ovf_cnt_;

			task_t() : cap_cnt_(0), ovf_cnt_(0) { }
		};
		static task_t	task_t_;
		static TASK		task_;

		uint32_t	clk_limit_;
		uint32_t	tgr_adr_;

		static INTERRUPT_FUNC void cap_task_()
		{
			++task_t_.cap_cnt_;
		}

		static INTERRUPT_FUNC void ovf_task_()
		{
			++task_t_.ovf_cnt_;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		mtu_io() : clk_limit_(F_PCLKA), tgr_adr_(MTUX::TGRA.address()) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  リミット・クロックの設定
			@param[in]	clk	リミット・クロック
		*/
		//-----------------------------------------------------------------//
		void set_limit_clock(uint32_t clk) { clk_limit_ = clk; }


		//-----------------------------------------------------------------//
		/*!
			@brief  インプットキャプチャ開始
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

			power_cfg::turn(MTUX::get_peripheral());

			MTUX::enable(ch);  // ポートを有効にする

			uint8_t cclr = 0;
			ICU::VECTOR cvec;
			switch(static_cast<uint8_t>(ch)) {
			case 0:
				cclr = 0b001;
				cvec = MTUX::get_vec(MTUX::interrupt::A);
				MTUX::TIOR = MTUX::TIOR.IOA.b(0b1000);
				break;
			case 1:
				cclr = 0b010;
				cvec = MTUX::get_vec(MTUX::interrupt::B);
				MTUX::TIOR = MTUX::TIOR.IOB.b(0b1000);
				break;
			case 2:
				cclr = 0b101;
				cvec = MTUX::get_vec(static_cast<typename MTUX::interrupt>(2));
//				MTUX::TIORL = MTUX::TIORL.IOC.b(0b1000);
				break;
			case 3:
				cclr = 0b110;
				cvec = MTUX::get_vec(static_cast<typename MTUX::interrupt>(3));
//				MTUX::TIORL = MTUX::TIORL.IOD.b(0b1000);
				break;
			default:
				return false;
			}
			uint8_t dv = 0;
			MTUX::TCR  = MTUX::TCR.TPSC.b(dv)
					   | MTUX::TCR.CKEG.b(static_cast<uint8_t>(et))
					   | MTUX::TCR.CCLR.b(cclr);
			MTUX::TCR2  = 0x00;
			MTUX::TMDR1 = 0x00;
			MTU::TMDR2A = 0x00;
			MTU::TMDR2B = 0x00;

			if(level > 0) {
				MTUX::TIER = (1 << static_cast<uint8_t>(ch)) | MTUX::TIER.TCIEV.b();
				set_interrupt_task(ovf_task_, static_cast<uint32_t>(MTUX::get_vec(MTUX::interrupt::OVF)));
				set_interrupt_task(cap_task_, static_cast<uint32_t>(cvec));
				icu_mgr::set_level(MTUX::get_peripheral(), level);
			}

			task_t_.cap_cnt_ = 0;
			task_t_.ovf_cnt_ = 0;

			tgr_adr_ = MTUX::TGRA.address() + static_cast<uint32_t>(ch) * 2;
// utils::format("TGR: 0x%08X\n") % tgr_adr_;
			wr16_(tgr_adr_, 0x0000);

			MTUX::TCNT = 0;

			switch(MTUX::get_peripheral()) {
			case peripheral::MTU0:
				MTU::TSTRA.CST0 = 1;
				break;
			case peripheral::MTU1:
				MTU::TSTRA.CST1 = 1;
				break;
			case peripheral::MTU2:
				MTU::TSTRA.CST2 = 1;
				break;
			case peripheral::MTU3:
				MTU::TSTRA.CST3 = 1;
				break;
			case peripheral::MTU4:
				MTU::TSTRA.CST4 = 1;
				break;
			case peripheral::MTU6:
				MTU::TSTRB.CST6 = 1;
				break;
			case peripheral::MTU7:
				MTU::TSTRB.CST7 = 1;
				break;
			case peripheral::MTU9:
				MTU::TSTRA.CST9 = 1;
				break;
			default:
				return false;
				break;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  インプット・キャプチャをリセット
		*/
		//-----------------------------------------------------------------//
		void reset_capture()
		{
			MTUX::TCNT = 0;
			task_t_.ovf_cnt_ = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  インプット・キャプチャのオーバーフローカウント取得
			@return インプット・キャプチャのオーバーフローカウント
		*/
		//-----------------------------------------------------------------//
		uint16_t get_capture_ovf() const {
			return task_t_.ovf_cnt_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  インプット・キャプチャ値を取得
			@return インプット・キャプチャ値
		*/
		//-----------------------------------------------------------------//
		uint32_t get_capture() const {
			uint32_t cap = rd16_(tgr_adr_);
			return (static_cast<uint32_t>(task_t_.ovf_cnt_) << 16) | cap;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  TASK クラスの参照
			@return TASK クラス
		*/
		//-----------------------------------------------------------------//
		static TASK& at_task() { return task_; }
	};

	template <class MTUX, class TASK> typename mtu_io<MTUX, TASK>::task_t mtu_io<MTUX, TASK>::task_t_;
	template <class MTUX, class TASK> TASK mtu_io<MTUX, TASK>::task_;
}
