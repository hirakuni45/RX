#pragma once
//=====================================================================//
/*!	@file
	@brief	CPU 内蔵 D/A ストリームクラス（割り込みによる転送） @n
			内蔵 D/A に、連続した値を流す。 @n
			MTU を基準タイマーとして利用する。 @n
			出力の GND レベルは中心電圧とする。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "sound/sound_out.hpp"
#include "common/mtu_io.hpp"
#include "RX600/dmac_mgr.hpp"

namespace sound {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	D/A Stream class
		@param[in]	DAC			D/A 変換器クラス
		@param[in]	ITV			インターバルタイマーデバイスクラス
		@param[in]	SOUND_OUT	サウンド出力クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class DAC, class ITV, class SOUND_OUT>
	class dac_stream_intr {

		SOUND_OUT&	sound_out_;

		struct itv_t {
			SOUND_OUT&	sound_out_;
			volatile uint32_t wpos_;

			itv_t(SOUND_OUT& sound_out) noexcept : sound_out_(sound_out), wpos_(0) { }
		};
		itv_t		itv_t_;

		static inline void* itv_t_ptr_;

		// ITM 割り込み、SAMPLE_DIV 毎に、ソースバッファから波形メモリに転送
		class itv_task {
		public:
			void operator() () {
				auto p = static_cast<itv_t*>(itv_t_ptr_);
				uint32_t tmp = p->wpos_;
				++p->wpos_;
				if((tmp ^ p->wpos_) & SOUND_OUT::OUTS_SIZE) {
					p->sound_out_.service(SOUND_OUT::OUTS_SIZE);
				}
			}
		};

		typedef device::mtu_io<ITV, itv_task> ITV_MGR;
		ITV_MGR		itv_mgr_;

		// Internal D/A
		typedef device::dac_out<DAC> DAC_OUT;
		DAC_OUT		dac_out_;

		uint32_t	sample_rate_;

		device::ICU::LEVEL	itv_intl_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	sound_out	サウンドバッファの参照
		*/
		//-----------------------------------------------------------------//
		dac_stream_intr(SOUND_OUT& sound_out) noexcept :
			sound_out_(sound_out), itv_t_(sound_out), itv_mgr_(),
			dac_out_(), sample_rate_(48'000), itv_intl_(device::ICU::LEVEL::NONE)
		{
			itv_t_ptr_ = &itv_t_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@param[in]	sample_rate	初期サンプルレート
			@param[in]	itv_intl	MTU の割り込みレベル
			@param[in]	amp_ena		D/A アンプを無効にする場合「false」
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t sample_rate, device::ICU::LEVEL itv_intl, bool amp_ena = true) noexcept
		{
			{  // 内臓 D/A の設定
				bool amp_ena = true;
				dac_out_.start(DAC_OUT::output::CH0_CH1, amp_ena);
				dac_out_.out0(0x8000);
				dac_out_.out1(0x8000);
			}

			// 波形メモリーの無音状態初期化
			sound_out_.mute();

			itv_intl_ = itv_intl;
			set_sample_rate(sample_rate);

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	サンプルレートを設定
			@param[in]	freq	サンプルレート
		*/
		//-----------------------------------------------------------------//
		void set_sample_rate(uint32_t freq) noexcept
		{
    	    if(!itv_mgr_.start(freq, itv_intl_)) {
 //       	    utils::format("ITV start error...\n");
        	} else {
#if 0
				utils::format("ITV intr vector: %d\n") % static_cast<int>(itv_mgr_.get_intr_vec());
				utils::format("ITV rate (set):  %d [Hz]\n") % itv_mgr_.get_rate();
				auto rate = 1.0f - static_cast<float>(itv_mgr_.get_rate()) / itv_mgr_.get_rate(true);
				rate *= 100.0f;
				utils::format("ITV rate (real): %d [Hz] (%3.2f [%%])\n")
					% itv_mgr_.get_rate(true) % rate;
#endif
			}
			sample_rate_ = freq;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	サンプルレートを取得
			@return	サンプルレート
		*/
		//-----------------------------------------------------------------//
		uint32_t get_sample_rate() const noexcept { return sample_rate_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	サンプル位置を取得
			@return	サンプル位置
		*/
		//-----------------------------------------------------------------//
		uint32_t get_sample_pos() const noexcept { return itv_t_.wpos_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	サンプルバッファサイズを返す
			@return	サンプルバッファサイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t get_sample_size() const noexcept { return sound_out_.get_sample_size(); }
	};
}
