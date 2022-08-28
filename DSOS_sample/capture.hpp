#pragma once
//=====================================================================//
/*! @file
    @brief  A/D 変換、キャプチャー制御クラス @n
			最大サンプルレート 2MHz (RX65N/RX72N) @n
			※「GLFW_SIM」を有効にする事で、キャプチャー動作をシュミレートする。
    @author 平松邦仁 (hira@rvf-rc45.net)
    @copyright  Copyright (C) 2018, 2022 Kunihito Hiramatsu @n
                Released under the MIT license @n
                https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
// GLFW_SIM for simulate A/D conversion
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
		@param[in]	CAPN	キャプチャー最大数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t CAPN>
	class capture : public render_base {

#ifndef GLFW_SIM
		typedef device::S12AD  ADC0;
		typedef device::S12AD1 ADC1;
#if defined(SIG_RX65N)
		static constexpr auto ADC_CH0 = ADC0::ANALOG::AIN000;  ///< P40 CN10(1)
		static constexpr auto ADC_CH1 = ADC1::ANALOG::AIN114;  ///< P90 CN10(5)
		typedef device::PORT<device::PORT6, device::bitpos::B0> CH0_SA;
		typedef device::PORT<device::PORT6, device::bitpos::B1> CH0_SB;
		typedef device::PORT<device::PORT6, device::bitpos::B2> CH0_DC;
		typedef device::PORT<device::PORT3, device::bitpos::B6> CH1_SA;
		typedef device::PORT<device::PORT3, device::bitpos::B7> CH1_SB;
		typedef device::PORT<device::PORT5, device::bitpos::B3> CH1_DC;
#elif defined(SIG_RX72N)
		static constexpr auto ADC_CH0 = ADC0::ANALOG::AIN007;  ///< P47 Pmod2(10) CN6
		static constexpr auto ADC_CH1 = ADC1::ANALOG::AIN108;  ///< PD0 Pmod2( 7) CN6
		typedef device::PORT<device::PORT9, device::bitpos::B0> CH0_SA;		///< P90 Pmod2( 2) CN6
		typedef device::PORT<device::PORT9, device::bitpos::B1> CH0_SB;		///< P91 Pmod2( 4) CN6
		typedef device::PORT<device::PORT9, device::bitpos::B2> CH0_DC;		///< P92 Pmod2( 3) CN6
		typedef device::PORT<device::PORT5, device::bitpos::B1> CH1_SA;		///< P51 Pmod1( 4) CN5
		typedef device::PORT<device::PORT5, device::bitpos::B4> CH1_SB;		///< P54 Pmod1( 1) CN5
		typedef device::PORT<device::PORT5, device::bitpos::B5> CH1_DC;		///< P55 Pmod1( 7) CN5
#endif
#endif

		enum class DIVIDER : uint8_t {
			HIGH,		///<  1/1 1:1 +-1.65V, 10:1 +-16.5V
			MIDDLE,		///<  1/4 1:1 +-6.60V, 10:1 +-66.6V
			LOW,		///< 1/20 1:1 +-33.0V, 10:1 +-330V
			GND,		///< GND(0V) level
		};

		static void select_divider_ch0_(DIVIDER n) noexcept
		{
			CH0_SA::P =  static_cast<uint8_t>(n) & 1;
			CH0_SB::P = (static_cast<uint8_t>(n) >> 1) & 1;
		}

		static void select_divider_ch1_(DIVIDER n) noexcept
		{
			CH1_SA::P =  static_cast<uint8_t>(n) & 1;
			CH1_SB::P = (static_cast<uint8_t>(n) >> 1) & 1;
		}

	public:

		static constexpr float VOLT_GAIN_HIGH   =  1.65f;	///< 1:1 Probe (+-1.65V) Max: +1.65V, Min: -1.65V
		static constexpr float VOLT_GAIN_MIDDLE =  6.6f;	///< 1:1 Probe (+-6.60V) Max: +1.65V, Min: -6.60V
		static constexpr float VOLT_GAIN_LOW    = 33.0f;	///< 1:1 Probe (+-33.0V) Max: +33.0V, Min: -33.0V

		static constexpr uint32_t ADC_QUANTIZE = 2048;  ///< A/D 変換量子化の半分
		static constexpr int16_t ADC_MAX =  2047 - 5;	///< 扱える最高値（オーバーレンジの検出）
		static constexpr int16_t ADC_MIN = -2048 + 5;	///< 扱える最低値（オーバーレンジの検出）
		// x:ch0, y:ch1
		typedef vtx::spos DATA;

		static constexpr uint32_t CAP_NUM = CAPN;	///< キャプチャー数
		static constexpr int16_t CAP_OFS  = 2048;	///< 12bit A/D offset（中間）

		// キャプチャー・タスク
		class cap_task {
		public:
			DATA				data_[CAPN];

			volatile uint32_t	pos_;
			volatile uint32_t	before_count_;
			volatile uint32_t	after_count_;
			volatile uint16_t	cycle_;	
			volatile int16_t	trg_ref_;
			volatile uint32_t	trg_pos_;
			volatile TRG_MODE	trg_mode_main_;
			volatile TRG_MODE	trg_mode_;
			DIVIDER				divider_ch0_;
			DIVIDER				divider_ch1_;

			DATA	min_;
			DATA	max_;

#ifdef GLFW_SIM
			DATA	adv_;
#endif

			cap_task() noexcept :
				data_ { { CAP_OFS, CAP_OFS } }, pos_(0),
				before_count_(0), after_count_(0), cycle_(0),
				trg_ref_(0), trg_pos_(0),
				trg_mode_main_(TRG_MODE::STOP), trg_mode_(TRG_MODE::STOP),
				divider_ch0_(DIVIDER::LOW), divider_ch1_(DIVIDER::LOW),
				min_(4096 - 1), max_(0)
			{ }

			void operator() ()
			{
#ifdef GLFW_SIM
				DATA t = adv_;
#else
				DATA t(ADC0::ADDR(ADC_CH0) - CAP_OFS, ADC1::ADDR(ADC_CH1) - CAP_OFS);
				// プリアンプで、入力信号を反転しているので、元に戻す。
				t.x = -t.x;
				t.y = -t.y;
				ADC0::ADCSR = ADC0::ADCSR.ADCS.b(0b01) | ADC0::ADCSR.ADST.b();
				ADC1::ADCSR = ADC1::ADCSR.ADCS.b(0b01) | ADC1::ADCSR.ADST.b();
#endif
				switch(trg_mode_) {
				case TRG_MODE::STOP:
					// オートゲイン制御
					if(t.x >= ADC_MAX || t.x <= ADC_MIN) {  // Over voltage CH0
//						select_divider_ch0_(DIVIDER::LOW);
//						divider_ch0_ = DIVIDER::LOW;
					}
					if(t.y >= ADC_MAX || t.y <= ADC_MIN) {  // Over voltage CH1
						select_divider_ch1_(DIVIDER::LOW);
						divider_ch1_ = DIVIDER::LOW;
					}
					break;
				case TRG_MODE::_BEFORE:  // 入力されている電圧を監視して、セレクタを切り替える。
					break;
				case TRG_MODE::SINGLE:
				case TRG_MODE::AUTO:
					data_[pos_] = t;
					++pos_;
					pos_ &= CAPN - 1;
					if(pos_ == (CAPN - 1)) {
						if(trg_mode_ == TRG_MODE::SINGLE) {
							trg_mode_ = TRG_MODE::STOP;
						}
						trg_pos_ = CAPN / 4;
						pos_ = 0;
						++cycle_;
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
					++pos_;
					pos_ &= CAPN - 1;
					if(t.x < trg_ref_) {
						trg_mode_ = TRG_MODE::_CH0_POSA;
					}
					break;
				case TRG_MODE::_CH0_POSA:
					data_[pos_] = t;
					if(t.x >= trg_ref_) {
						trg_pos_ = pos_;
						trg_mode_ = TRG_MODE::_TRG_AFTER;
					}
					++pos_;
					pos_ &= CAPN - 1;
					break;

				case TRG_MODE::CH1_POS:
					data_[pos_] = t;
					++pos_;
					pos_ &= CAPN - 1;
					if(t.y < trg_ref_) {
						trg_mode_ = TRG_MODE::_CH1_POSA;
					}
					break;
				case TRG_MODE::_CH1_POSA:
					data_[pos_] = t;
					if(t.y >= trg_ref_) {
						trg_pos_ = pos_;
						trg_mode_ = TRG_MODE::_TRG_AFTER;
					}
					++pos_;
					pos_ &= CAPN - 1;
					break;

				case TRG_MODE::CH0_NEG:
					data_[pos_] = t;
					++pos_;
					pos_ &= CAPN - 1;
					if(t.x > trg_ref_) {
						trg_mode_ = TRG_MODE::_CH0_NEGA;
					}
					break;
				case TRG_MODE::_CH0_NEGA:
					data_[pos_] = t;
					if(t.x <= trg_ref_) {
						trg_pos_ = pos_;
						trg_mode_ = TRG_MODE::_TRG_AFTER;
					}
					++pos_;
					pos_ &= CAPN - 1;
					break;

				case TRG_MODE::CH1_NEG:
					data_[pos_] = t;
					++pos_;
					pos_ &= CAPN - 1;
					if(t.y > trg_ref_) {
						trg_mode_ = TRG_MODE::_CH1_NEGA;
					}
					break;
				case TRG_MODE::_CH1_NEGA:
					data_[pos_] = t;
					if(t.y <= trg_ref_) {
						trg_pos_ = pos_;
						trg_mode_ = TRG_MODE::_TRG_AFTER;
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
						trg_mode_ = TRG_MODE::STOP;
						++cycle_;
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
		uint32_t	capture_samplerate_;
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


		static float fsqu_(float in) noexcept
		{
			auto a = fmod(in, 1.0f);
			if(a < 0.5f) {
				return 1.0f;
			} else {
				return -1.0f;
			}
		}


		static float fsquf_(float in, float& back) noexcept
		{
			auto a = fsqu_(in);
			auto d = (a - back) * 0.707f;
			auto ans = back + d;
			back = a; 
			return ans;
		}


		static int16_t pwave_(PWAVE_TYPE pw, float phase, float gain) noexcept
		{
			static float fsqu_s_ = 0;
			static float fsqu_c_ = 0;
			int16_t ret = 0;
			switch(pw) {
			case PWAVE_TYPE::SIN:
				ret = static_cast<int16_t>(sinf(phase * vtx::radian_f_) * gain);
				break;
			case PWAVE_TYPE::COS:
				ret = static_cast<int16_t>(cosf(phase * vtx::radian_f_) * gain);
				break;
			case PWAVE_TYPE::TRI_C:
				ret = static_cast<int16_t>(ftri_(phase) * gain);
				break;
			case PWAVE_TYPE::TRI_S:
				ret = static_cast<int16_t>(ftri_(phase + 0.25f) * gain);
				break;
			case PWAVE_TYPE::SQU_C:
				ret = static_cast<int16_t>(fsqu_(phase) * gain);
				break;
			case PWAVE_TYPE::SQU_S:
				ret = static_cast<int16_t>(fsqu_(phase + 0.25f) * gain);
				break;
			case PWAVE_TYPE::FSQU_C:
				ret = static_cast<int16_t>(fsquf_(phase, fsqu_c_) * gain);
				break;
			case PWAVE_TYPE::FSQU_S:
				ret = static_cast<int16_t>(fsquf_(phase + 0.25f, fsqu_s_) * gain);
				break;
			default:
				break;
			}
			return ret;
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		capture() noexcept : samplerate_(2'000'000), capture_samplerate_(2'000'000),
			trg_mode_(TRG_MODE::STOP)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  サンプリング周波数の設定
			@param[in]	freq	サンプリング周波数
		*/
		//-----------------------------------------------------------------//
		void set_samplerate(uint32_t freq) noexcept
		{
#ifndef GLFW_SIM
			uint8_t intr_level = 5;
			if(!tpu0_.start(freq, intr_level)) {
				utils::format("TPU0 start error...\n");
			} else {
				auto vec = tpu0_.get_intr_vec();
				// スーパーバイザーモード中に、MVTC xxx,FINTV で割り込みベクタアドレスを設定する必要がある。
//				device::ICU::IER.enable(vec, false);
//				device::icu_mgr::enable_fast_interrupt(vec);
//				device::ICU::IER.enable(vec);
			}
#endif
			samplerate_ = freq;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  キャプチャーしたサンプリング周波数の取得
			@return	キャプチャーしたサンプリング周波数
		*/
		//-----------------------------------------------------------------//
		auto get_capture_samplerate() const noexcept { return capture_samplerate_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  電圧ゲインの取得
			@param[in]	ch		チャネル
			@return 電圧ゲイン
		*/
		//-----------------------------------------------------------------//
		auto get_voltage_gain(uint32_t ch) const noexcept {
			DIVIDER divider = DIVIDER::GND;
			if(ch == 0) {
				divider = get_cap_task().divider_ch0_;
			} else {
				divider = get_cap_task().divider_ch1_;
			}
			float gain = VOLT_GAIN_LOW;
			switch(divider) {
			case DIVIDER::HIGH:   gain = VOLT_GAIN_HIGH; break;
			case DIVIDER::MIDDLE: gain = VOLT_GAIN_MIDDLE; break;
			default:
				break;
			}
			return gain;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  直流、交流、GND の切り替え
			@param[in]	ch		チャネル
			@param[in]	mode	チャネルモード
		*/
		//-----------------------------------------------------------------//
		void turn_ch_mode(uint32_t ch, CH_MODE mode) noexcept
		{
			if(ch == 0) {
				if(mode == CH_MODE::DC) {
					CH0_DC::P = 1;
// select_divider_ch0_(DIVIDER::MIDDLE);
// at_cap_task().divider_ch0_ = DIVIDER::MIDDLE;
select_divider_ch0_(DIVIDER::HIGH);
at_cap_task().divider_ch0_ = DIVIDER::HIGH;
				} else if(mode == CH_MODE::AC) {
					CH0_DC::P = 0;
// select_divider_ch0_(DIVIDER::MIDDLE);
// at_cap_task().divider_ch0_ = DIVIDER::MIDDLE;
select_divider_ch0_(DIVIDER::HIGH);
at_cap_task().divider_ch0_ = DIVIDER::HIGH;
				} else if(mode == CH_MODE::GND) {
					CH0_DC::P = 0;  // GND 時 AC に切り替える。
					select_divider_ch0_(DIVIDER::GND);
				}
			} else {
				if(mode == CH_MODE::DC) {
					CH1_DC::P = 1;
select_divider_ch1_(DIVIDER::HIGH);
at_cap_task().divider_ch1_ = DIVIDER::HIGH;
				} else if(mode == CH_MODE::AC) {
					CH1_DC::P = 0;
select_divider_ch1_(DIVIDER::HIGH);
at_cap_task().divider_ch1_ = DIVIDER::HIGH;
				} else if(mode == CH_MODE::GND) {
					CH1_DC::P = 0;  // GND 時 AC に切り替える。
					select_divider_ch1_(DIVIDER::GND);
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	freq	サンプリング周波数
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t freq) noexcept
		{
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
			CH0_SA::OUTPUT();
			CH0_SB::OUTPUT();
			select_divider_ch0_(DIVIDER::GND);
			CH0_DC::OUTPUT();
			CH0_DC::P = 0;  // AC

			CH1_SA::OUTPUT();
			CH1_SB::OUTPUT();
			select_divider_ch1_(DIVIDER::GND);
			CH1_DC::OUTPUT();
			CH1_DC::P = 0;  // AC

			// 順番が重要！（A/D の初期化後に呼ぶ事）
			set_samplerate(freq);

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
			@brief  最低値、最大値を検出
			@param[in]	org		開始位置
			@param[in]	end		終端位置
			@param[out]	min		最小値
			@param[in]	max		最大値
		*/
		//-----------------------------------------------------------------//
		void get_min_max(int32_t org, int32_t end, DATA& min, DATA& max) const noexcept
		{
			if(end < org) end += CAP_NUM;

			min.x = get(org).x;
			max.x = get(org).x;
			min.y = get(org).y;
			max.y = get(org).y;
			for(int32_t i = org + 1; i < end; ++i) {
				min.x = std::min(min.x, get(i).x);
				max.x = std::max(max.x, get(i).x);
				min.y = std::min(min.y, get(i).y);
				max.y = std::max(max.y, get(i).y);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  トリガー前キャプチャー数の取得
			@return トリガー前キャプチャー数
		*/
		//-----------------------------------------------------------------//
		auto get_before_count() const noexcept { return CAP_NUM / 4; }


		//-----------------------------------------------------------------//
		/*!
			@brief  トリガー後キャプチャー数の取得
			@return トリガー後キャプチャー数
		*/
		//-----------------------------------------------------------------//
		auto get_after_count() const noexcept { return CAPN / 2 + CAPN / 4; }


		//-----------------------------------------------------------------//
		/*!
			@brief  トリガー型設定（キャプチャー開始）
			@param[in]	trg		トリガー型
			@param[in]	ref		トリガー基準値
		*/
		//-----------------------------------------------------------------//
		void set_trg_mode(TRG_MODE trg_mode, int16_t ref) noexcept
		{
			at_cap_task().trg_ref_ = limit_(ref);
			at_cap_task().pos_ = 0;
			at_cap_task().before_count_ = get_before_count();
			at_cap_task().after_count_  = get_after_count();
			at_cap_task().trg_mode_main_ = trg_mode;
			trg_mode_ = trg_mode;
			if(trg_mode == TRG_MODE::CH0_POS || trg_mode == TRG_MODE::CH1_POS
				|| trg_mode == TRG_MODE::CH0_NEG || trg_mode == TRG_MODE::CH1_NEG) {
				at_cap_task().trg_mode_ = TRG_MODE::_TRG_BEFORE;
			} else {
				at_cap_task().trg_mode_ = trg_mode;
			}
			capture_samplerate_ = samplerate_;
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
			@brief  キャプチャー・サイクルの取得
			@return キャプチャー・サイクル
		*/
		//-----------------------------------------------------------------//
		auto get_capture_cycle() const noexcept { return get_cap_task().cycle_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  波形値を取得（A/D 変換された値、０～４０９６）
			@return 波形値
		*/
		//-----------------------------------------------------------------//
		const auto& get(uint32_t pos) const noexcept
		{
			return get_cap_task().data_[(pos + get_cap_task().trg_pos_) & (CAP_NUM - 1)];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  自動トリガー解析(CH0)
		*/
		//-----------------------------------------------------------------//
		void auto_analize() noexcept
		{
			DATA min;
			DATA max;
			uint32_t org = 0;
			uint32_t end = CAP_NUM / 4;
			get_min_max(org, end, min, max);

			auto th = (min.x + max.x) / 2;
			bool next = false;
			for(uint32_t i = CAP_NUM / 4; i < CAP_NUM; ++i) {
				if(!next) {
					if(th > get_cap_task().data_[i].x) next = true;
				} else {
					if(th < get_cap_task().data_[i].x) {
						at_cap_task().trg_pos_ = i;
						break;
					}
				}
			}
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
			@param[in]	ch0		CH0 波形型
			@param[in]	ch1		CH1 波形型
		*/
		//-----------------------------------------------------------------//
		void make_wave(uint32_t freq, float ppv, uint32_t num, PWAVE_TYPE ch0, PWAVE_TYPE ch1) noexcept
		{
			static int32_t count = 0;
			auto smpl = samplerate_;
			auto& task = at_cap_task();
			auto unit = static_cast<float>(smpl) / static_cast<float>(freq);
			auto vgain0 = voltage_to_value(0, ppv);
			auto vgain1 = voltage_to_value(1, ppv);
			for(uint32_t i = 0; i < num; ++i) {
				auto a = static_cast<float>(count % static_cast<int32_t>(unit)) / unit;
				task.adv_.x = -pwave_(ch0, a, vgain0);
				task.adv_.y = -pwave_(ch1, a, vgain1);
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
			@brief  解析
			@param[in]	org		開始ポイント
			@param[in]	end		終了ポイント
			@param[out]	ch0		CH0 情報
			@param[out]	ch1		CH1 情報
		*/
		//-----------------------------------------------------------------//
		void analize(int32_t org, int32_t end, wave_info& ch0, wave_info& ch1) const noexcept
		{
			if(end < org) end += CAP_NUM;
			if((end - org) > static_cast<int32_t>(CAP_NUM)) end = org + CAP_NUM;
///			utils::format("Cap win width: %d\n") % static_cast<int>(end - org);

			DATA min;
			DATA max;
			get_min_max(org, end, min, max);
			ch0.min_ = min.x;
			ch0.max_ = max.x;
			ch1.min_ = min.y;
			ch1.max_ = max.y;

			ch0.setup();
			ch1.setup();
			for(int32_t i = org + 1; i < end; ++i) {
				ch0.update(get(i).x, i);
				ch1.update(get(i).y, i);
				if(ch0.probe() && ch1.probe()) break;
			}
			ch0.build(get_capture_samplerate());
			ch1.build(get_capture_samplerate());
		}
	};
}
