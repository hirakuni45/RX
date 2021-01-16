#pragma once
//=====================================================================//
/*! @file
    @brief  A/D 変換、キャプチャー制御クラス @n
			最大サンプルレート 2MHz (RX65N/RX72N) @n
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

#include "render_base.hpp"
#include "common/vtx.hpp"
#include "common/string_utils.hpp"

namespace dsos {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  キャプチャー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t CAPN>
	class capture : public render_base {

		typedef vtx::spos DATA;

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
			DATA				data_[CAPN];

			volatile uint32_t	tic_;
			volatile uint16_t	pos_;
			uint16_t	count_;
			volatile TRG_MODE	trg_mode_;
			volatile uint16_t	trg_pos_;

			DATA	min_;
			DATA	max_;
			DATA	cmp_;
			DATA	dlt_;
			DATA	back_;

#ifdef GLFW_SIM
			DATA	adv_;
#endif

			cap_task() noexcept :
				data_ { { 2048, 2048 } }, tic_(0), pos_(0), count_(0),
				trg_mode_(TRG_MODE::NONE), trg_pos_(0),
				min_(4096 - 1), max_(0), cmp_(100), dlt_(10), back_(0)
			{ }

			void operator() ()
			{
#ifndef GLFW_SIM
				DATA t(ADC0::ADDR(ADC_CH0), ADC1::ADDR(ADC_CH1));
				t.x -= 2048;
				t.y -= 2048;
				ADC0::ADCSR = ADC0::ADCSR.ADCS.b(0b01) | ADC0::ADCSR.ADST.b();
				ADC1::ADCSR = ADC1::ADCSR.ADCS.b(0b01) | ADC1::ADCSR.ADST.b();
#else
				DATA t = adv_;
#endif
				switch(trg_mode_) {
				case TRG_MODE::NONE:
					break;
				case TRG_MODE::ONE:
				case TRG_MODE::RUN:
					data_[pos_] = t;
					++pos_;
					pos_ &= CAPN - 1;
					if(pos_ == (CAPN - 1)) {
						if(trg_mode_ == TRG_MODE::ONE) {
							trg_mode_ = TRG_MODE::NONE;
						}
						trg_pos_ = pos_;
						pos_ = 0;
						++tic_;
					}
					break;
				case TRG_MODE::CH0_POS:
					data_[pos_] = t;
					dlt_ += t - back_;
					back_ = t;
					++pos_;
					pos_ &= CAPN - 1;
					if(count_ > 0) {
						count_--;
						if(count_ == 0) {
							trg_mode_ = TRG_MODE::NONE;
							++tic_;
						}
					} else if(dlt_.x > cmp_.x) {
						trg_pos_ = pos_;
						count_ = CAPN / 2;
					}
					break;
				case TRG_MODE::CH1_POS:
					data_[pos_] = t;
					dlt_ += t - back_;
					back_ = t;
					++pos_;
					pos_ &= CAPN - 1;
					if(count_ > 0) {
						count_--;
						if(count_ == 0) {
							trg_mode_ = TRG_MODE::NONE;
							++tic_;
						}
					} else if(dlt_.y > cmp_.y) {
						trg_pos_ = pos_;
						count_ = CAPN / 2;
					}
					break;
				case TRG_MODE::CH0_NEG:
					data_[pos_] = t;
					dlt_ += t - back_;
					back_ = t;
					++pos_;
					pos_ &= CAPN - 1;
					if(count_ > 0) {
						count_--;
						if(count_ == 0) {
							trg_mode_ = TRG_MODE::NONE;
							++tic_;
						}
					} else if(dlt_.x < cmp_.x) {
						trg_pos_ = pos_;
						count_ = CAPN / 2;
					}
					break;
				case TRG_MODE::CH1_NEG:
					data_[pos_] = t;
					dlt_ += t - back_;
					back_ = t;
					++pos_;
					pos_ &= CAPN - 1;
					if(count_ > 0) {
						count_--;
						if(count_ == 0) {
							trg_mode_ = TRG_MODE::NONE;
							++tic_;
						}
					} else if(dlt_.y > cmp_.y) {
						trg_pos_ = pos_;
						count_ = CAPN / 2;
					}
					break;
				default:
					break;
				}
			}
		};

	private:

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


		//-----------------------------------------------------------------//
		/*!
			@brief  キャプチャー・タスク参照
			@return キャプチャー・タスク
		*/
		//-----------------------------------------------------------------//
#ifdef GLFW_SIM
		auto& at_cap_task() noexcept { return cap_task_; }
#else
		auto& at_cap_task() noexcept { return tpu0_.at_task(); }
#endif


		//-----------------------------------------------------------------//
		/*!
			@brief  キャプチャー・タスク参照(RO)
			@return キャプチャー・タスク
		*/
		//-----------------------------------------------------------------//
#ifdef GLFW_SIM
		const auto& get_cap_task() const noexcept { return cap_task_; }
#else
		const auto& get_cap_task() const noexcept { return tpu0_.get_task(); }
#endif

		//-----------------------------------------------------------------//
		/*!
			@brief  トリガー設定
			@param[in]	trg		トリガー種別
		*/
		//-----------------------------------------------------------------//
		const char* get_trigger_str() noexcept
		{
			static char tmp[16];
			auto pos = static_cast<uint32_t>(get_cap_task().trg_mode_);
			utils::str::get_word(TRG_MODE_STR, pos, tmp, sizeof(tmp), ',');
			return tmp;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  トリガー設定
			@param[in]	trg		トリガー種別
		*/
		//-----------------------------------------------------------------//
		void set_trigger(TRG_MODE trg_mode) noexcept
		{
			at_cap_task().pos_ = 0;
			at_cap_task().dlt_ = 0;
			at_cap_task().count_ = 0;
			at_cap_task().trg_mode_ = trg_mode;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タスク・カウンタの取得
			@return タスク・カウンタ
		*/
		//-----------------------------------------------------------------//
		auto get_capture_tic() const noexcept { return get_cap_task().tic_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  波形を取得
		*/
		//-----------------------------------------------------------------//
		const auto& get(uint32_t pos) noexcept
		{
			return at_cap_task().data_[(pos + get_cap_task().trg_pos_) & (CAPN - 1)];
		}
	};
}
