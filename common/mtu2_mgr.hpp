#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ MTU2 制御 @n
			RX110/RX111/RX113 @n
			RX130/RX140 @n
			RX220/RX231 @n
			RX631/RX63N 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "renesas.hpp"
#include "common/intr_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU2 基本クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class mtu2_mgr_base {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アウトプット型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OUTPUT : uint8_t {
			NONE     = 0b0000,	///< 出力しない
			L_TO_H   = 0b0010,	///< 初期０で、マッチで１
			H_TO_L   = 0b0101,	///< 初期１で、マッチで０
			L_TOGGLE = 0b0011,	///< 初期０で、トグル出力
			H_TOGGLE = 0b0111,	///< 初期１で、トグル出力
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  キャプチャー型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CAPTURE : uint8_t {
			POSITIVE = 0b1000,	///< 立ち上がりエッジでキャプチャ
			NEGATIVE = 0b1001,	///< 立下りエッジでキャプチャ
			DUAL     = 0b1010,	///< 両エッジでキャプチャ
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  キャプチャー構造体
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct capture_t {
			volatile uint32_t	all_count_;
			volatile uint16_t	ovfw_limit_;	///< オーバーフローの最大値
			volatile uint16_t	ovfw_count_;

			capture_t() : all_count_(0),
				ovfw_limit_(0),   // タイムアウト１秒
				ovfw_count_(0)
			{ }

			void clear() {
				all_count_ = 0;
				ovfw_count_ = 0;
			}
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU2 制御クラス
		@param[in]	MTUX	MTU ユニット
		@param[in]	MTASK	メイン割り込みタスク
		@param[in]	OTASK	オーバーフロー割り込みタスク
		@param[in]	PSEL	入出力ポートオーダー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class MTUX, class MTASK = utils::null_task, class OTASK = utils::null_task,
		port_map_mtu::ORDER PSEL = port_map_mtu::ORDER::FIRST>
	struct mtu2_mgr : public mtu2_mgr_base {

		typedef MTUX mtu_type;
		typedef typename MTUX::CHANNEL CHANNEL;

	private:

		static MTASK mtask_;

		static INTERRUPT_FUNC void match_task_()
		{
//			++tt_.main_tick_;
			mtask_();
		}


		enum class MODE : uint8_t {
			NORMAL = 0b0000,
			PWM1   = 0b0010,
			PWM2   = 0b0011,
		};




		void set_interruptABCD_(typename MTUX::CHANNEL ch, ICU::LEVEL lvl) noexcept // ABCD の割り込み
		{
			auto cvec = MTUX::get_vector(ch);
			auto ivec = icu_mgr::set_interrupt(cvec, match_task_, lvl);
			if(ivec != ICU::VECTOR::NONE) {
				MTUX::TIER |= 1 << static_cast<uint8_t>(ch);  // ABCD の割り込み
			}
		}

		bool start_(CHANNEL ch, uint32_t freq, OUTPUT out, ICU::LEVEL lvl, MODE md) noexcept
		{
			if(!power_mgr::turn(MTUX::PERIPHERAL)) {
				return false;
			}

			MTUX::enable(false);
			MTUX::TIER = 0;
			MTUX::TIOR.disable();

//			channel_ = ch;
//			tt_.out_ = out;

			if(out != OUTPUT::NONE) {
				bool pena = true;
				port_map_mtu::turn(MTUX::PERIPHERAL, MTUX::get_port_map_channel(ch), pena, PSEL);
			}

			uint32_t match = 0;
//			if(!make_clock_(freq, match)) {
//				power_mgr::turn(MTUX::PERIPHERAL, false);
//				return false;
//			}

//			if(set_output_type_(ch, out)) {
//				bool mod = match & 1;
//				match /= 2;
//				if(mod) ++match;
//			}
//			if(!set_TCR_(ch)) {
//				power_mgr::turn(MTUX::PERIPHERAL, false);
//				return false;
//			}

			MTUX::TMDR = static_cast<uint8_t>(md);

			if(lvl != ICU::LEVEL::NONE) {
				set_interruptABCD_(ch, lvl);
			}

//			tt_.tgr_ = match;
			MTUX::TGR[ch] = match - 1;
			MTUX::TCNT = 0;

			return true;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		mtu2_mgr() noexcept 
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  ノーマル・モード（コンペア・マッチ・タイマー）
			@param[in]	ch		出力チャネル
			@param[in]	freq	出力周波数
			@param[in]	out		出力タイプ
			@param[in]	lvl		割り込みレベル
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start_normal(CHANNEL ch, uint32_t freq, OUTPUT out, ICU::LEVEL lvl = ICU::LEVEL::NONE) noexcept
		{
			static_assert(MTUX::PERIPHERAL != peripheral::MTU5, "Normal mode cannot select MTU5");

			auto ret = start_(ch, freq, out, lvl, MODE::NORMAL);
			if(ret) {
				MTUX::enable();
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  インターバルタイマー（ポート出力無し）
			@param[in]	freq	周波数
			@param[in]	lvl		割り込みレベル
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t freq, ICU::LEVEL lvl = ICU::LEVEL::NONE) noexcept
		{
			return start_normal(CHANNEL::A, freq, OUTPUT::NONE, lvl);
		}



	};
}
