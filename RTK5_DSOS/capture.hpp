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
		@brief  キャプチャー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t CAPN>
	class capture {
	public:

	private:
		static capture_data	data_[CAPN];

		/// DMAC 終了割り込み
		class dmac_term_task {
		public:
			void operator() () {
//				device::DMAC0::DMCNT.DTE = 1;  // DMA を再スタート
			}
		};

//		typedef device::dmac_mgr<device::DMAC0, dmac_term_task> DMAC_MGR;
//		DMAC_MGR    dmac_mgr_;

		typedef device::S12AD  ADC0;
		typedef device::S12AD1 ADC1;

		static uint16_t	pos_;

		class tpu_task {
		public:
			void operator() () {
				data_[pos_].ch0_ = ADC0::ADDR(ADC0::analog::AIN000);
				data_[pos_].ch1_ = ADC1::ADDR(ADC1::analog::AIN114);
				++pos_;
				pos_ &= CAPN - 1;

				ADC0::ADCSR.ADST = 1;
				ADC1::ADCSR.ADST = 1;
			}
		};

		typedef device::tpu_io<device::TPU0, tpu_task> TPU0;
		TPU0        tpu0_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		capture() { }


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


		uint32_t get_pos() noexcept { return pos_; }


		const capture_data& get(uint32_t pos) noexcept
		{
			return data_[pos & (CAPN - 1)];
		}
	};

	template <uint32_t CAPN> uint16_t capture<CAPN>::pos_;
	template <uint32_t CAPN> capture_data capture<CAPN>::data_[CAPN];
}
