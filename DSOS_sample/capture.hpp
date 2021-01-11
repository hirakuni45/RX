#pragma once
//=====================================================================//
/*! @file
    @brief  A/D 変換、キャプチャー制御クラス @n
			※「GLFW_SIM」を有効にする事で、キャプチャー動作をシュミレートする。
    @author 平松邦仁 (hira@rvf-rc45.net)
    @copyright  Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
                Released under the MIT license @n
                https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#ifndef GLFW_SIM
#include "common/renesas.hpp"
#endif

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  キャプチャー・ベースクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct capture_base {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  キャプチャー・データ構造体
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct data_t {
			uint16_t	ch0_;
			uint16_t	ch1_;
			data_t(uint16_t v = 0) noexcept : ch0_(v), ch1_(v) { }
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  キャプチャー・トリガー型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class TRIGGER : uint8_t {
			NONE,		///< 何もしない
			FREE,		///< フリーラン取得
			CH0_P_TRG,	///< CH0 ポジティブ・トリガー
			CH1_P_TRG,	///< CH1 ポジティブ・トリガー
			CH0_N_TRG,	///< CH0 ネガティブ・トリガー
			CH1_N_TRG,	///< CH1 ネガティブ・トリガー
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  キャプチャー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t CAPN>
	class capture : public capture_base {

#ifndef GLFW_SIM
		typedef device::S12AD  ADC0;
		typedef device::S12AD1 ADC1;
#if defined(SIG_RX65N)
		static const auto ADC_CH0 = ADC0::analog::AIN000;
		static const auto ADC_CH1 = ADC1::analog::AIN114;
#elif defined(SIG_RX72N)
		static const auto ADC_CH0 = ADC0::analog::AIN007;  ///< P47 Pmod2(10) CN6
		static const auto ADC_CH1 = ADC1::analog::AIN108;  ///< PD0 Pmod2( 7) CN6
#endif
#endif

	public:
		static const uint32_t CAP_NUM = CAPN;

		// キャプチャー・タスク
		class cap_task {
		public:
			data_t	min_;
			data_t	max_;

#ifdef GLFW_SIM
			data_t	adv_;
#endif

			cap_task() noexcept : min_(0), max_(0) { }

			void operator() ()
			{
				switch(trigger_) {
				case TRIGGER::NONE:
#ifndef GLFW_SIM
					ADC0::ADCSR = ADC0::ADCSR.ADCS.b(0b01) | ADC0::ADCSR.ADST.b();
					ADC1::ADCSR = ADC1::ADCSR.ADCS.b(0b01) | ADC1::ADCSR.ADST.b();
#endif
					break;
				case TRIGGER::FREE:
#ifdef GLFW_SIM
					data_[pos_] = adv_;
#else
					data_[pos_].ch0_ = ADC0::ADDR(ADC_CH0);
					data_[pos_].ch1_ = ADC1::ADDR(ADC_CH1);
					ADC0::ADCSR = ADC0::ADCSR.ADCS.b(0b01) | ADC0::ADCSR.ADST.b();
					ADC1::ADCSR = ADC1::ADCSR.ADCS.b(0b01) | ADC1::ADCSR.ADST.b();
#endif
					++pos_;
					if(pos_ >= CAPN) {
						trigger_ = TRIGGER::NONE;
						++tic_;
					}
					break;
				default:
					break;
				}
			}
		};

	private:
		static data_t				data_[CAPN];

		static volatile uint32_t	tic_;
		static volatile uint16_t	pos_;
		static volatile TRIGGER		trigger_;

#ifndef GLFW_SIM
		typedef device::tpu_io<device::TPU0, cap_task> TPU0;
		TPU0        tpu0_;
#else
		cap_task	cap_task_;
#endif

		uint32_t	samplerate_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		capture() noexcept : samplerate_(2'000'000) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  サンプルレートの設定
			@param[in]	freq	サンプリング周波数
		*/
		//-----------------------------------------------------------------//
		void set_samplerate(uint32_t freq) noexcept
		{
			samplerate_ = freq;
#ifndef GLFW_SIM
			uint8_t intr_level = 5;
			if(!tpu0_.start(freq, intr_level)) {
				utils::format("TPU0 start error...\n");
			}
#endif
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サンプルレートの取得
			@return	サンプリング周波数
		*/
		//-----------------------------------------------------------------//
		auto get_samplerate() const noexcept { return samplerate_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	freq	サンプリング周波数
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t freq) noexcept
		{
			set_samplerate(freq);

#ifndef GLFW_SIM
			{  // A/D 設定
				device::power_mgr::turn(ADC0::PERIPHERAL);
				ADC0::enable(ADC_CH0);
				ADC0::ADANSA.set(ADC_CH0);
				ADC0::ADSSTR.set(ADC_CH0, 11);
				ADC0::ADSTRGR = ADC0::ADSTRGR.TRSA.b(0b100000) | ADC0::ADSTRGR.TRSB.b(0b111111);
				ADC0::ADSAM.SAM = 0;
				ADC0::ADCSR.ADCS = 0b01;

				device::power_mgr::turn(ADC1::PERIPHERAL);
				ADC1::enable(ADC_CH1);
				ADC1::ADANSA.set(ADC_CH1);
				ADC1::ADSSTR.set(ADC_CH1, 11);
				ADC1::ADSTRGR = ADC1::ADSTRGR.TRSA.b(0b100000) | ADC1::ADSTRGR.TRSB.b(0b111111);
				ADC1::ADSAM.SAM = 1;
				ADC1::ADCSR.ADCS = 0b01;
			}
#endif

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


#ifdef GLFW_SIM
		//-----------------------------------------------------------------//
		/*!
			@brief  キャプチャー・タスク参照
			@return キャプチャー・タスク
		*/
		//-----------------------------------------------------------------//
		auto& at_cap_task() noexcept { return cap_task_; }
#else
		auto& at_cap_task() noexcept { return tpu0_.at_task(); }
#endif


		//-----------------------------------------------------------------//
		/*!
			@brief  トリガー設定
			@param[in]	trg		トリガー種別
		*/
		//-----------------------------------------------------------------//
		void set_trigger(TRIGGER trigger) noexcept
		{
			pos_ = 0;
			trigger_ = trigger;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タスク・カウンタの取得
			@return タスク・カウンタ
		*/
		//-----------------------------------------------------------------//
		auto get_capture_tic() const noexcept { return tic_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  波形を取得
		*/
		//-----------------------------------------------------------------//
		const auto& get(uint32_t pos) noexcept
		{
			return data_[pos & (CAPN - 1)];
		}
	};

	template <uint32_t CAPN> capture_base::data_t capture<CAPN>::data_[CAPN] = { 2048 };
	template <uint32_t CAPN> volatile uint32_t capture<CAPN>::tic_ = 0;
	template <uint32_t CAPN> volatile uint16_t capture<CAPN>::pos_ = 0;
	template <uint32_t CAPN>
	volatile capture_base::TRIGGER capture<CAPN>::trigger_ = capture_base::TRIGGER::NONE;
}
