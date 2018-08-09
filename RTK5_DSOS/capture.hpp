#pragma once
//=====================================================================//
/*! @file
    @brief  A/D 変換、キャプチャー制御クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
    @copyright  Copyright (C) 2018 Kunihito Hiramatsu @n
                Released under the MIT license @n
                https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  キャプチャー・データ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct capture_data {
		uint16_t	ch0_;
		uint16_t	ch1_;
		capture_data() : ch0_(0), ch1_(0) { }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  キャプチャー・トリガー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class capture_trigger : uint8_t {
		NONE,		///< 何もしない
		SINGLE,		///< シングル取り込み
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  キャプチャー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t CAPN>
	class capture {

		/// DMAC 終了割り込み
		class dmac_term_task {
		public:
			void operator() () {
//				device::DMAC0::DMCNT.DTE = 1;  // DMA を再スタート
			}
		};

//		typedef device::dmac_mgr<device::DMAC0, dmac_term_task> DMAC_MGR;
//		DMAC_MGR    dmac_mgr_;

		static capture_data				data_[CAPN];

		typedef device::S12AD  ADC0;
		typedef device::S12AD1 ADC1;

		static volatile uint16_t		pos_;
		static volatile capture_trigger	trigger_;

		class tpu_task {
		public:
			void operator() ()
			{
				switch(trigger_) {
				case capture_trigger::NONE:
					ADC0::ADCSR = ADC0::ADCSR.ADCS.b(0b01) | ADC0::ADCSR.ADST.b();
					ADC1::ADCSR = ADC1::ADCSR.ADCS.b(0b01) | ADC1::ADCSR.ADST.b();
					break;
				case capture_trigger::SINGLE:
					data_[pos_].ch0_ = ADC0::ADDR(ADC0::analog::AIN000);
					data_[pos_].ch1_ = ADC1::ADDR(ADC1::analog::AIN114);
					ADC0::ADCSR = ADC0::ADCSR.ADCS.b(0b01) | ADC0::ADCSR.ADST.b();
					ADC1::ADCSR = ADC1::ADCSR.ADCS.b(0b01) | ADC1::ADCSR.ADST.b();
					++pos_;
					if(pos_ >= CAPN) {
						trigger_ = capture_trigger::NONE;
					}
				}
			}
		};

		typedef device::tpu_io<device::TPU0, tpu_task> TPU0;
		TPU0        tpu0_;

		bool		start_cap_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		capture() noexcept : start_cap_(false) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	freq	サンプリング周波数
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t freq) noexcept
		{
			uint8_t intr_level = 5;
			if(!tpu0_.start(freq, intr_level)) {
				utils::format("TPU0 start error...\n");
			}

			{  // A/D 設定
				device::power_cfg::turn(ADC0::get_peripheral());
				ADC0::enable(ADC0::analog::AIN000);
				ADC0::ADANSA.set(ADC0::analog::AIN000);
				ADC0::ADSSTR.set(ADC0::analog::AIN000, 11);
				ADC0::ADSTRGR = ADC0::ADSTRGR.TRSA.b(0b100000) | ADC0::ADSTRGR.TRSB.b(0b111111);
				ADC0::ADSAM.SAM = 0;
				ADC0::ADCSR.ADCS = 0b01;

				device::power_cfg::turn(ADC1::get_peripheral());
				ADC1::enable(ADC1::analog::AIN114);
				ADC1::ADANSA.set(ADC1::analog::AIN114);
				ADC1::ADSSTR.set(ADC1::analog::AIN114, 11);
				ADC1::ADSTRGR = ADC1::ADSTRGR.TRSA.b(0b100000) | ADC1::ADSTRGR.TRSB.b(0b111111);
				ADC1::ADSAM.SAM = 1;
				ADC1::ADCSR.ADCS = 0b01;
			}

#if 0
			{  // DMAC マネージャー開始
				uint8_t intr_level = 4;
				auto ret = dmac_mgr_.start(tpu0_.get_intr_vec(), DMAC_MGR::trans_type::SP_DN_32,
					reinterpret_cast<uint32_t>(sound_out_.get_wave()),
					DAC::DADR0.address(),
					sound_out_.size(), intr_level);
				if(!ret) {
					utils::format("DMAC Not start...\n");
				}
			}
#endif
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  トリガー設定
			@param[in]	trg		トリガー種別
		*/
		//-----------------------------------------------------------------//
		void set_trigger(capture_trigger trigger) noexcept
		{
			pos_ = 0;
			trigger_ = trigger;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  トリガー取得
			@return トリガー
		*/
		//-----------------------------------------------------------------//
		capture_trigger  get_trigger() const noexcept { return trigger_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  波形を取得
		*/
		//-----------------------------------------------------------------//
		const capture_data& get(uint32_t pos) noexcept
		{
			return data_[pos & (CAPN - 1)];
		}
	};

	template <uint32_t CAPN> capture_data capture<CAPN>::data_[CAPN];
	template <uint32_t CAPN> volatile uint16_t capture<CAPN>::pos_ = 0;
	template <uint32_t CAPN>
	volatile capture_trigger capture<CAPN>::trigger_ = capture_trigger::NONE;
}
