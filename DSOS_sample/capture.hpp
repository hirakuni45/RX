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
		static const uint32_t CAP_NUM = CAPN;	///< キャプチャー数
		static const int16_t CAP_OFS = 2048;	///< 12bit A/D offset

		// キャプチャー・タスク
		class cap_task {
		public:
			DATA				data_[CAPN];

			volatile uint32_t	tic_;
			volatile uint16_t	pos_;
			uint16_t			before_count_;
			uint16_t			after_count_;
			volatile int16_t	trg_ref_;
			volatile int16_t	trg_nois_;
			volatile TRG_MODE	trg_mode_main_;
			volatile TRG_MODE	trg_mode_;
			volatile uint16_t	trg_pos_;

			DATA	min_;
			DATA	max_;
			DATA	back_;

#ifdef GLFW_SIM
			DATA	adv_;
#endif

			cap_task() noexcept :
				data_ { { 2048, 2048 } }, tic_(0), pos_(0),
				before_count_(0), after_count_(0),
				trg_ref_(0), trg_nois_(10),
				trg_mode_main_(TRG_MODE::NONE), trg_mode_(TRG_MODE::NONE),
				trg_pos_(0),
				min_(4096 - 1), max_(0), back_(0)
			{ }

			void operator() ()
			{
#ifndef GLFW_SIM
				DATA t(ADC0::ADDR(ADC_CH0), ADC1::ADDR(ADC_CH1));
				t.x -= CAP_OFS;
				t.y -= CAP_OFS;
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
						trg_pos_ = CAPN / 4;
						pos_ = 0;
						++tic_;
					}
					break;
				case TRG_MODE::_TRG_BEFORE:
					data_[pos_] = t;
					++pos_;
					pos_ &= CAPN - 1;
					if(before_count_ > 0) {
						before_count_--;
					} else {
						trg_mode_ = trg_mode_main_;
					}
					break;
				case TRG_MODE::CH0_POS:
					data_[pos_] = t;
					if(back_.x < trg_ref_ && trg_ref_ <= t.x) {
						if(trg_nois_ < std::abs(back_.x - t.x)) {
							trg_pos_ = pos_;
							trg_mode_ = TRG_MODE::_TRG_AFTER;
						}
					}
					++pos_;
					pos_ &= CAPN - 1;
					break;
				case TRG_MODE::CH1_POS:
					data_[pos_] = t;
					if(back_.y < trg_ref_ && trg_ref_ <= t.y) {
						if(trg_nois_ < std::abs(back_.y - t.y)) {
							trg_pos_ = pos_;
							trg_mode_ = TRG_MODE::_TRG_AFTER;
						}
					}
					++pos_;
					pos_ &= CAPN - 1;
					break;
				case TRG_MODE::CH0_NEG:
					data_[pos_] = t;
					if(back_.x > trg_ref_ && trg_ref_ >= t.x) {
						if(trg_nois_ < std::abs(back_.x - t.x)) {
							trg_pos_ = pos_;
							trg_mode_ = TRG_MODE::_TRG_AFTER;
						}
					}
					++pos_;
					pos_ &= CAPN - 1;
					break;
				case TRG_MODE::CH1_NEG:
					data_[pos_] = t;
					if(back_.y > trg_ref_ && trg_ref_ >= t.y) {
						if(trg_nois_ < std::abs(back_.y - t.y)) {
							trg_pos_ = pos_;
							trg_mode_ = TRG_MODE::_TRG_AFTER;
						}
					}
					++pos_;
					pos_ &= CAPN - 1;
					break;
				case TRG_MODE::_TRG_AFTER:
					data_[pos_] = t;
					++pos_;
					pos_ &= CAPN - 1;
					if(after_count_ > 0) {
						after_count_--;
					} else {
						trg_mode_ = TRG_MODE::NONE;
						++tic_;
					}
					break;
				default:
					break;
				}
				back_ = t;
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

		float		volt_gain_[2];

		TRG_MODE	trg_mode_;


		static int16_t limit_(int16_t val) noexcept
		{
			if(val >= CAP_OFS) val = CAP_OFS - 1;
			else if(val < -CAP_OFS) val = -CAP_OFS;
			return val;
		}


		static float ftri_(float in) noexcept
		{
			auto a = fmod(in, 1.0f);
			if(a >= 0.5f) {
				a = 1.0f - a;
			}
			a -= 0.25f;
		   	return a * 4.0f;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		capture() noexcept : samplerate_(2'000'000), volt_gain_{ VOLT_DIV_L, VOLT_DIV_L },
			trg_mode_(TRG_MODE::NONE) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  サンプルレートの設定
			@param[in]	freq	サンプリング周波数
		*/
		//-----------------------------------------------------------------//
		void set_samplerate(uint32_t freq) noexcept
		{
#ifndef GLFW_SIM
			uint8_t intr_level = 5;
			if(!tpu0_.start(freq, intr_level)) {
				utils::format("TPU0 start error...\n");
			}
#endif
			samplerate_ = freq;
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
			@brief  電圧ゲインの設定
			@param[in]	ch		チャネル
			@param[in]	gain	電圧ゲイン
		*/
		//-----------------------------------------------------------------//
		void set_voltage_gain(uint32_t ch, float gain) noexcept {
			bool cap = false;
			if(volt_gain_[ch & 1] != gain) {
				cap = true;
			}
			volt_gain_[ch & 1] = gain;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  電圧ゲインの取得
			@param[in]	ch		チャネル
			@return 電圧ゲイン
		*/
		//-----------------------------------------------------------------//
		auto get_voltage_gain(uint32_t ch) const noexcept { return volt_gain_[ch & 1]; }


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
			@brief  トリガー型設定
			@param[in]	trg		トリガー型
			@param[in]	ref		トリガー基準値
		*/
		//-----------------------------------------------------------------//
		void set_trg_mode(TRG_MODE trg_mode, int16_t ref) noexcept
		{
// utils::format("Trg value: %d\n") % ref;
			at_cap_task().trg_ref_ = limit_(ref);
			at_cap_task().pos_ = 0;
			at_cap_task().before_count_ = CAP_NUM / 4;
			at_cap_task().after_count_  = CAPN / 2 + CAPN / 4;
			at_cap_task().trg_mode_main_ = trg_mode;
			trg_mode_ = trg_mode;
			if(trg_mode == TRG_MODE::CH0_POS || trg_mode == TRG_MODE::CH1_POS
				|| trg_mode == TRG_MODE::CH0_NEG || trg_mode == TRG_MODE::CH1_NEG) {
				at_cap_task().trg_mode_ = TRG_MODE::_TRG_BEFORE;
			} else {
				at_cap_task().trg_mode_ = trg_mode;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  トリガー型を取得
			@param[in]	real	現在の状態を知りたい場合「true」
			@return トリガー型
		*/
		//-----------------------------------------------------------------//
		auto get_trg_mode(bool real = false) const noexcept {
			if(real) {
				return get_cap_task().trg_mode_;
			} else {
				return trg_mode_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  トリガー設定文字列の取得
			@param[in]	real	現在の状態を知りたい場合「true」
			@return トリガー設定文字列
		*/
		//-----------------------------------------------------------------//
		const char* get_trigger_str(bool real = false) noexcept
		{
			static char tmp[16];
			auto pos = static_cast<uint32_t>(get_trg_mode(real));
			utils::str::get_word(TRG_MODE_STR, pos, tmp, sizeof(tmp), ',');
			return tmp;
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


		//-----------------------------------------------------------------//
		/*!
			@brief  電圧を A/D 値に変換
			@param[in]	ch		チャネル（０，１）
			@param[in]	volt	電圧[V]
		*/
		//-----------------------------------------------------------------//
		int16_t voltage_to_value(int32_t ch, float volt) noexcept
		{
			return volt / get_voltage_gain(ch) * static_cast<float>(CAP_OFS);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  SIN/COS 波形を生成
			@param[in]	freq	周波数
			@param[in]	ppv		電圧 (peak to peak)
			@param[in]	num		生成数
		*/
		//-----------------------------------------------------------------//
		void make_sincos_wave(uint32_t freq, float ppv, uint32_t num) noexcept
		{
			static int32_t count = 0;
			auto smpl = get_samplerate();
			auto& task = at_cap_task();
			auto unit = static_cast<float>(smpl) / static_cast<float>(freq);
			auto vgain0 = voltage_to_value(0, ppv);
			auto vgain1 = voltage_to_value(1, ppv);
			for(uint32_t i = 0; i < num; ++i) {
				auto a = static_cast<float>(count % static_cast<int32_t>(unit)) / unit;
				task.adv_.x = static_cast<int16_t>(sinf(a * vtx::radian_f_) * vgain0);
				task.adv_.y = static_cast<int16_t>(cosf(a * vtx::radian_f_) * vgain1);
				if(task.adv_.x < -CAP_OFS) task.adv_.x = -CAP_OFS;
				else if(task.adv_.x > (CAP_OFS-1)) task.adv_.x = CAP_OFS-1;
				if(task.adv_.y < -CAP_OFS) task.adv_.y = -CAP_OFS;
				else if(task.adv_.y > (CAP_OFS-1)) task.adv_.y = CAP_OFS-1;
				task();
				++count;
				if(count >= CAP_NUM) {
					count = 0;
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  三角波を生成
			@param[in]	freq	周波数
			@param[in]	ppv		電圧 (peak to peak)
			@param[in]	num		生成数
		*/
		//-----------------------------------------------------------------//
		void make_triangle_wave(uint32_t freq, float ppv, uint32_t num) noexcept
		{
			static int32_t count = 0;
			auto smpl = get_samplerate();
			auto& task = at_cap_task();
			auto unit = static_cast<float>(smpl) / static_cast<float>(freq);
			auto vgain0 = voltage_to_value(0, ppv);
			auto vgain1 = voltage_to_value(1, ppv);
			for(uint32_t i = 0; i < num; ++i) {
				auto a = static_cast<float>(count % static_cast<int32_t>(unit)) / unit;
				task.adv_.x = static_cast<int16_t>(ftri_(a) * vgain0);
				task.adv_.y = static_cast<int16_t>(ftri_(a + 0.5f) * vgain1);
				if(task.adv_.x < -CAP_OFS) task.adv_.x = -CAP_OFS;
				else if(task.adv_.x > (CAP_OFS-1)) task.adv_.x = CAP_OFS-1;
				if(task.adv_.y < -CAP_OFS) task.adv_.y = -CAP_OFS;
				else if(task.adv_.y > (CAP_OFS-1)) task.adv_.y = CAP_OFS-1;
				task();
				++count;
				if(count >= CAP_NUM) {
					count = 0;
				}
			}
		}
	};
}
