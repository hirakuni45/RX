#pragma once
//=====================================================================//
/*! @file
    @brief  波形描画クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
    @copyright  Copyright (C) 2018, 2022 Kunihito Hiramatsu @n
                Released under the MIT license @n
                https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include "common/enum_utils.hpp"
#include "common/intmath.hpp"
#include "graphics/color.hpp"

#include "render_base.hpp"
#include "resource.hpp"

namespace dsos {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  波形描画クラス
		@param[in]	RENDER	描画クラス
		@param[in]	TOUCH	タッチ・クラス
		@param[in]	CAPTURE	キャプチャー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RENDER, class TOUCH, class CAPTURE>
	class render_wave : public render_base {

		static constexpr int16_t GRID = 40;					///< グリッド単位数
		static constexpr int16_t TIME_SIZE = GRID * 11;		///< 時間軸サイズ(440)
		static constexpr int16_t VOLT_SIZE = GRID * 6;		///< 電圧軸サイズ(240)

		static constexpr float   GRID_SCALE       = 1.0f / static_cast<float>(GRID);
		static constexpr int16_t MENU_SIZE        = 40;
		// static constexpr int16_t TIME_SCROLL_AREA = RENDER::font_type::height + GRID;
		static constexpr int16_t CH0_MOVE_AREA    = (RENDER::glc_type::width - MENU_SIZE) / 2;
		static constexpr int16_t CH1_MOVE_AREA    = RENDER::glc_type::width - MENU_SIZE;
		static constexpr int16_t TIME_BEGIN_POS   = RENDER::font_type::height;
		static constexpr int16_t TIME_LIMIT_POS   = RENDER::glc_type::height - RENDER::font_type::height - 1;
		static constexpr int16_t VOLT_BEGIN_POS   = 0;
		static constexpr int16_t VOLT_LIMIT_POS   = RENDER::glc_type::width - MENU_SIZE;

		static constexpr int16_t VOLT_OFS = 16 + VOLT_SIZE / 2;		///< 電圧軸オフセット（画像の中心）

		static constexpr int16_t ARROW_AREA_W   = 24;  ///< 矢印を操作する幅
		static constexpr vtx::srect WAVE_AREA  = { 0, 16, TIME_SIZE - ARROW_AREA_W, VOLT_SIZE };  // 上下の文字枠を除く
		static constexpr vtx::srect TRG_AREA  = { TIME_SIZE - ARROW_AREA_W, 16, ARROW_AREA_W, VOLT_SIZE };

		static constexpr vtx::srect MES_AREA_TIME_0 = { 0, 0, TIME_SIZE, 16 + 20 };
		static constexpr vtx::srect MES_AREA_TIME_1 = { 0, 272 - 16 - 20, TIME_SIZE, 16 + 20 };
		static constexpr vtx::srect MES_AREA_VOLT_0 = { 0, 16, 30, VOLT_SIZE };
		static constexpr vtx::srect MES_AREA_VOLT_1 = { TIME_SIZE - 30, 16, 30, VOLT_SIZE };

		RENDER&		render_;
		TOUCH&		touch_;
		CAPTURE&	capture_;

		TARGET		target_;

		int16_t		time_org_;
		int16_t		time_pos_;
		int16_t		ch0_vorg_;
		int16_t		ch0_vpos_;
		int16_t		ch1_vorg_;
		int16_t		ch1_vpos_;
		int16_t		trg_org_;
		int16_t		trg_pos_;

		CH_MULT		ch0_mult_;
		CH_MODE		ch0_mode_;
		CH_MODE		ch0_mode_back_;
		CH_VOLT		ch0_volt_;
		CH_MULT		ch1_mult_;
		CH_MODE		ch1_mode_;
		CH_MODE		ch1_mode_back_;
		CH_VOLT		ch1_volt_;
		SMP_MODE	smp_mode_;

		MEASERE		measere_;
		int16_t		mes_time_0_org_;
		int16_t		mes_time_0_pos_;
		int16_t		mes_time_1_org_;
		int16_t		mes_time_1_pos_;
		int16_t		mes_volt_0_org_;
		int16_t		mes_volt_0_pos_;
		int16_t		mes_volt_1_org_;
		int16_t		mes_volt_1_pos_;

		uint8_t		touch_num_;

		uint16_t	trg_wait_;
		uint32_t	trg_update_;

		uint32_t	cap_cycle_;
		SMP_MODE	cur_smp_mode_;
		typedef typename CAPTURE::wave_info WAVE_INFO;
		WAVE_INFO	wave_info0_;
		WAVE_INFO	wave_info1_;
		uint16_t	ch_info_count_;

		enum class AREA {
			NONE,
			WAVE,
			TRG,
			MES_TIME_0,
			MES_TIME_1,
			MES_VOLT_0,
			MES_VOLT_1,
		};
		AREA		area_;

		int32_t		cap_win_org_;
		int32_t		cap_win_end_;
		vtx::spos	volt_min_[2];
		vtx::spos	volt_max_[2];


		void scan_area_(const vtx::spos& pos) noexcept
		{
			if(measere_ == MEASERE::TIME_SUB) {
				if(MES_AREA_TIME_0.is_focus(pos)) {
					area_ = AREA::MES_TIME_0;
					mes_time_0_org_ = pos.x;
				} else if(MES_AREA_TIME_1.is_focus(pos)) {
					area_ = AREA::MES_TIME_1;
					mes_time_1_org_ = pos.x;
				}
			} else if(measere_ == MEASERE::TIME_ABS) {
				if(MES_AREA_TIME_0.is_focus(pos)) {
					area_ = AREA::MES_TIME_0;
					mes_time_0_org_ = pos.x;
				}
			} else if(measere_ == MEASERE::CH0_SUB || measere_ == MEASERE::CH1_SUB) {
				if(MES_AREA_VOLT_0.is_focus(pos)) {
					area_ = AREA::MES_VOLT_0;
					mes_volt_0_org_ = pos.y;
				} else if(MES_AREA_VOLT_1.is_focus(pos)) {
					area_ = AREA::MES_VOLT_1;
					mes_volt_1_org_ = pos.y;
				}
			} else if(measere_ == MEASERE::CH0_ABS || measere_ == MEASERE::CH1_ABS) {
				if(MES_AREA_VOLT_0.is_focus(pos)) {
					area_ = AREA::MES_VOLT_0;
					mes_volt_0_org_ = pos.y;
				}
			} else {
				if(TRG_AREA.is_focus(pos)) {
					area_ = AREA::TRG;
					trg_org_ = trg_pos_;
				} else if(WAVE_AREA.is_focus(pos)) {
					area_ = AREA::WAVE;
					if(target_ == TARGET::CH0) {
						ch0_vorg_ = ch0_vpos_;
						trg_org_ = trg_pos_;
						time_org_ = time_pos_;
					} else if(target_ == TARGET::CH1) {
						ch1_vorg_ = ch1_vpos_;
						trg_org_ = trg_pos_;
						time_org_ = time_pos_;
					}
				} else {
					area_ = AREA::NONE;
				}
			}
		}


		void make_volt_(int16_t val, int32_t unit_mv, char* tmp, uint32_t len) noexcept
		{
			auto n = static_cast<float>(val * unit_mv) / static_cast<float>(GRID);
			if(std::abs(n) >= 1000.0f) {
				n /= 1000.0f;
				utils::sformat("%4.3fV", tmp, len) % n;
			} else {
				utils::sformat("%3.2fmv", tmp, len) % n;
			}
		}


		void make_rate_(int16_t val, int32_t unit_us, char* str, uint32_t len) noexcept
		{
			float n = static_cast<float>(val * unit_us) / static_cast<float>(GRID);
			if(std::abs(n) >= 1000.0f) {
				n /= 1000.0f;
				utils::sformat("%3.2fms", str, len) % n;
			} else {
				utils::sformat("%3.2fus", str, len) % n;
			}
		}


		void make_freq_(int16_t val, int32_t unit_us, char* str, uint32_t len) noexcept
		{
			if(val == 0) {
				str[0] = 0;
				return;
			}
			auto a = 1.0f / (static_cast<float>(val * unit_us) / static_cast<float>(GRID) * 1e-6);
			if(a < 1000.0f) {
				utils::sformat("%3.2fHz", str, len) % a;
			} else if(a < 1e6) {
				a *= 1e-3;
				utils::sformat("%2.1fKHz", str, len) % a;
			} else {
				a *= 1e-6;
				utils::sformat("%2.1fMHz", str, len) % a;
			}
		}


		void make_freq_(float freq, char* str, uint32_t len)
		{
			if(freq == 0.0f) {
				utils::sformat("---Hz", str, len);
			} else if(freq < 1000.0f) {
				utils::sformat("%3.2fHz", str, len) % freq;
			} else if(freq < 1000000.0f) {
				freq /= 1e3;
				utils::sformat("%4.3fKHz", str, len) % freq;
			} else {
				freq /= 1e6;
				utils::sformat("%4.3fMHz", str, len) % freq;
			}
		}


		void make_ch_voltage_(const WAVE_INFO& info, float gain, char* str, uint32_t len) const noexcept
		{
			auto min = gain * static_cast<float>(info.min_) / static_cast<float>(CAPTURE::ADC_QUANTIZE);
			auto max = gain * static_cast<float>(info.max_) / static_cast<float>(CAPTURE::ADC_QUANTIZE);
			auto vol = max - min;
			if(std::abs(vol) < 1e-3) {
				vol /= 1e-3;
	 			utils::sformat("%2.1fmVpp, ", str, len) % vol;
			} else {
	 			utils::sformat("%3.2fVpp, ", str, len) % vol;
			}
			if(std::abs(min) < 1e-3) {
				min /= 1e-3;
	 			utils::sformat("%2.1fmV", str, len, true) % min;
			} else {
	 			utils::sformat("%3.2fV", str, len, true) % min;
			}
			if(std::abs(max) < 1e-3) {
				max /= 1e-3;
	 			utils::sformat(" to %2.1fmV", str, len, true) % max;
			} else {
	 			utils::sformat(" to %3.2fV", str, len, true) % max;
			}
		}


		void draw_ch_arrow_(int16_t vpos) noexcept
		{
			if(vpos < 16) {
				vpos = 16;
				render_.draw_mobj(vtx::spos(0, vpos), resource::bitmap::dir_3_, false);
			} else if(vpos >= (272 - 16)) {
				vpos = 272 - 16 - 1;
				render_.draw_mobj(vtx::spos(0, vpos - 14), resource::bitmap::dir_1_, false);
			} else {
				render_.draw_mobj(vtx::spos(0, vpos - 7), resource::bitmap::dir_2_, false);
			}
		}


		void draw_trg_gate_(int16_t vpos) noexcept
		{
			if(vpos < 16) {
				render_.draw_mobj(vtx::spos(440 - 14, 16), resource::bitmap::dir_3_, false);
			} else if(vpos >= (272 - 16)) {
				vpos = 272 - 16 - 1;
				render_.draw_mobj(vtx::spos(440 - 14, vpos - 14), resource::bitmap::dir_1_, false);
			} else {
				if(area_ == AREA::TRG) {  // トリガー電圧操作中に基準ラインを引く
					render_.line(vtx::spos(0, trg_pos_), vtx::spos(440, trg_pos_));
				}
				render_.draw_mobj(vtx::spos(440 - 14, vpos - 7), resource::bitmap::dir_0_, false);
			}
		}


		void draw_time_gate_(int16_t pos) noexcept
		{
			if(pos < 0) {
				render_.draw_mobj(vtx::spos(0, 16), resource::bitmap::dir_0_, false);
			} else if(pos >= TIME_SIZE) {
				render_.draw_mobj(vtx::spos(440 - 14, 16), resource::bitmap::dir_2_, false);
			} else {
				render_.draw_mobj(vtx::spos(pos - 7, 16), resource::bitmap::dir_1_, false);
				render_.line(vtx::spos(pos, 16), vtx::spos(pos, 272-16));
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
			@param[in]	render	描画クラス
			@param[in]	touch	タッチ・クラス
			@param[in]	capture	キャプチャー・クラス
		*/
		//-----------------------------------------------------------------//
		render_wave(RENDER& render, TOUCH& touch, CAPTURE& capture) noexcept :
			render_(render), touch_(touch), capture_(capture),
			target_(TARGET::CH0),
			time_org_(TIME_SIZE / 2), time_pos_(TIME_SIZE / 2),
			ch0_vorg_(VOLT_OFS), ch0_vpos_(VOLT_OFS),
			ch1_vorg_(VOLT_OFS), ch1_vpos_(VOLT_OFS),
			trg_org_(VOLT_OFS), trg_pos_(VOLT_OFS),
			ch0_mult_(CH_MULT::X1),
			ch0_mode_(CH_MODE::AC), ch0_mode_back_(CH_MODE::AC),
			ch0_volt_(CH_VOLT::_10V),
			ch1_mult_(CH_MULT::X1),
			ch1_mode_(CH_MODE::AC), ch1_mode_back_(CH_MODE::AC),
			ch1_volt_(CH_VOLT::_10V),
			smp_mode_(SMP_MODE::_1us),
			measere_(MEASERE::OFF),
			mes_time_0_org_(TIME_SIZE / 2), mes_time_0_pos_(TIME_SIZE / 2),
			mes_time_1_org_(TIME_SIZE / 2), mes_time_1_pos_(TIME_SIZE / 2),
			mes_volt_0_org_(VOLT_OFS), mes_volt_0_pos_(VOLT_OFS),
			mes_volt_1_org_(VOLT_OFS), mes_volt_1_pos_(VOLT_OFS),
			touch_num_(0), trg_wait_(0), trg_update_(0),
			cap_cycle_(0), cur_smp_mode_(SMP_MODE::_1us), wave_info0_(), wave_info1_(),
			ch_info_count_(0),
			area_(AREA::NONE),
			cap_win_org_(0), cap_win_end_(0), volt_min_(), volt_max_()
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  操作設定
			@param[in]	target	ターゲット型
		*/
		//-----------------------------------------------------------------//
		void set_target(TARGET target) noexcept { target_ = target; }


		//-----------------------------------------------------------------//
		/*!
			@brief  CH0 倍率設定
			@param[in]	mult	チャネル倍率型
		*/
		//-----------------------------------------------------------------//
		void set_ch0_mult(CH_MULT mult) noexcept { ch0_mult_ = mult; }


		//-----------------------------------------------------------------//
		/*!
			@brief  CH1 倍率設定
			@param[in]	mult	チャネル倍率型
		*/
		//-----------------------------------------------------------------//
		void set_ch1_mult(CH_MULT mult) noexcept { ch1_mult_ = mult; }


		//-----------------------------------------------------------------//
		/*!
			@brief  CH0 モード設定
			@param[in]	mode	チャネル・モード型
		*/
		//-----------------------------------------------------------------//
		void set_ch0_mode(CH_MODE mode) noexcept { ch0_mode_ = mode; }


		//-----------------------------------------------------------------//
		/*!
			@brief  CH0 電圧レンジ設定
			@param[in]	volt	電圧レンジ型
		*/
		//-----------------------------------------------------------------//
		void set_ch0_volt(CH_VOLT volt) noexcept { ch0_volt_ = volt; }


		//-----------------------------------------------------------------//
		/*!
			@brief  CH1 モード設定
			@param[in]	mode	チャネル・モード型
		*/
		//-----------------------------------------------------------------//
		void set_ch1_mode(CH_MODE mode) noexcept { ch1_mode_ = mode; }


		//-----------------------------------------------------------------//
		/*!
			@brief  CH1 電圧レンジ設定
			@param[in]	volt	電圧レンジ型
		*/
		//-----------------------------------------------------------------//
		void set_ch1_volt(CH_VOLT volt) noexcept { ch1_volt_ = volt; }


		//-----------------------------------------------------------------//
		/*!
			@brief  時間型設定
			@param[in]	tim	時間型
		*/
		//-----------------------------------------------------------------//
		void set_smp_mode(SMP_MODE smp) noexcept { smp_mode_ = smp; }


		//-----------------------------------------------------------------//
		/*!
			@brief  メジャー（計測）モードの設定
			@param[in]	mes	計測型
		*/
		//-----------------------------------------------------------------//
		void set_measere(MEASERE mes) noexcept { measere_ = mes; }


		//-----------------------------------------------------------------//
		/*!
			@brief  グリッドの描画
			@param[in]	x		開始Ｘ
			@param[in]	y		開始Ｙ
			@param[in]	w		横幅
			@param[in]	h		高さ
			@param[in]	unit	ユニット・ピクセル
		*/
		//-----------------------------------------------------------------//
		void draw_grid(int16_t x, int16_t y, int16_t w, int16_t h, int16_t unit) noexcept
		{
			render_.set_fore_color(DEF_COLOR::Aqua);
			render_.set_back_color(DEF_COLOR::Black);
			for(int16_t i = x; i <= (x + w); i += unit) {
				uint32_t mask;
				if(i == x || i == (x + w)) {
					mask = -1;
				} else {
					mask = 0b00111111001111110011111100111111;
				}
				render_.set_stipple(mask);
				render_.line_v(i, y, h);
			}
			for(int16_t i = y; i <= (y + h); i += unit) {
				uint32_t mask;
				if(i == y || i == (y + h)) {
					mask = -1;
				} else {
					mask = 0b00111111001111110011111100111111;
				}
				render_.set_stipple(mask);
				render_.line_h(i, x, w);
			}
			render_.set_stipple();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サンプリング情報描画 @n
					※上段の情報ライン
			@param[in]	ch	チャネル
		*/
		//-----------------------------------------------------------------//
		void draw_sampling_info() noexcept
		{
			render_.set_fore_color(DEF_COLOR::Black);
			render_.fill_box(vtx::srect(0, 0, 480, 16));

			render_.set_fore_color(DEF_COLOR::White);
			switch(measere_) {
			case MEASERE::OFF:
				{
					auto trg = capture_.get_trg_mode();
					char tmp[32];
					utils::sformat("%s/div, ", tmp, sizeof(tmp)) % get_smp_str(smp_mode_);
					auto x = render_.draw_text(vtx::spos(0, 0), tmp);
					auto sr = capture_.get_capture_samplerate() / 1000;  // KHz
					if(sr >= 1000) {
						sr /= 1000;
						utils::sformat("%dMHz/sec, ", tmp, sizeof(tmp)) % sr;
					} else {
						utils::sformat("%dKHz/sec, ", tmp, sizeof(tmp)) % sr;
					}
					x = render_.draw_text(vtx::spos(x, 0), tmp);
					x = render_.draw_text(vtx::spos(x, 0), capture_.get_trigger_str());
					if(trg == TRG_MODE::CH0_POS || trg == TRG_MODE::CH0_NEG) {
						x = render_.draw_text(vtx::spos(x, 0), ": ");
						auto v = ch0_vpos_ - trg_pos_;
						make_volt_(v, get_mvolt(ch0_volt_), tmp, sizeof(tmp));
						x = render_.draw_text(vtx::spos(x, 0), tmp);
					} else if(trg == TRG_MODE::CH1_POS || trg == TRG_MODE::CH1_NEG) {
						x = render_.draw_text(vtx::spos(x, 0), ": ");
						auto v = ch1_vpos_ - trg_pos_;
						make_volt_(v, get_mvolt(ch1_volt_), tmp, sizeof(tmp));
						x = render_.draw_text(vtx::spos(x, 0), tmp);
					}

					// vpos の位置、time_pos の位置を表示
					if(area_ == AREA::WAVE) {
						if(target_ == TARGET::CH0) {
							auto v = ch0_vpos_ - 272 / 2;
							make_volt_(-v, get_mvolt(ch0_volt_), tmp, sizeof(tmp));
							x = render_.draw_text(vtx::spos(x + 8, 0), tmp);
							make_rate_(time_pos_, get_smp_rate(smp_mode_), tmp, sizeof(tmp));
							x = render_.draw_text(vtx::spos(x + 8, 0), tmp);
						} else if(target_ == TARGET::CH1) {
							auto v = ch1_vpos_ - 272 / 2;
							make_volt_(-v, get_mvolt(ch1_volt_), tmp, sizeof(tmp));
							x = render_.draw_text(vtx::spos(x + 8, 0), tmp);
							make_rate_(time_pos_, get_smp_rate(smp_mode_), tmp, sizeof(tmp));
							x = render_.draw_text(vtx::spos(x + 8, 0), tmp);
						}
					}
				}
				break;
			case MEASERE::CH0_SUB:
				{
					auto d = mes_volt_1_pos_ - mes_volt_0_pos_;
					auto x = render_.draw_text(vtx::spos(0, 0), "CH0: ");
					char tmp[16];
					make_volt_(d, get_mvolt(ch0_volt_), tmp, sizeof(tmp));
					x = render_.draw_text(vtx::spos(x, 0), tmp);
				}
				break;
			case MEASERE::CH1_SUB:
				{
					auto d = mes_volt_1_pos_ - mes_volt_0_pos_;
					auto x = render_.draw_text(vtx::spos(0, 0), "CH1: ");
					char tmp[16];
					make_volt_(d, get_mvolt(ch1_volt_), tmp, sizeof(tmp));
					x = render_.draw_text(vtx::spos(x, 0), tmp);
				}
				break;
			case MEASERE::CH0_ABS:
				{
					auto d = ch0_vpos_ - mes_volt_0_pos_;
					auto x = render_.draw_text(vtx::spos(0, 0), "CH0: ");
					char tmp[16];
					make_volt_(d, get_mvolt(ch0_volt_), tmp, sizeof(tmp));
					x = render_.draw_text(vtx::spos(x, 0), tmp);
				}
				break;
			case MEASERE::CH1_ABS:
				{
					auto d = ch1_vpos_ - mes_volt_0_pos_;
					auto x = render_.draw_text(vtx::spos(0, 0), "CH1: ");
					char tmp[16];
					make_volt_(d, get_mvolt(ch1_volt_), tmp, sizeof(tmp));
					x = render_.draw_text(vtx::spos(x, 0), tmp);
				}
				break;
			case MEASERE::TIME_SUB:
				{
					auto d = mes_time_1_pos_ - mes_time_0_pos_;
					char tmp[16];
					make_rate_(d, get_smp_rate(smp_mode_), tmp, sizeof(tmp));
					auto x = render_.draw_text(vtx::spos(0, 0), tmp);
					make_freq_(d, get_smp_rate(smp_mode_), tmp, sizeof(tmp));
					x += 8;
					x = render_.draw_text(vtx::spos(x, 0), tmp);
				}
				break;
			case MEASERE::TIME_ABS:  // CH0 の電圧、計測ポイント０
				{
					auto d = mes_time_0_pos_ - time_pos_;
					char tmp[16];
					make_rate_(d, get_smp_rate(smp_mode_), tmp, sizeof(tmp));
					auto x = render_.draw_text(vtx::spos(0, 0), tmp);
					make_freq_(d, get_smp_rate(smp_mode_), tmp, sizeof(tmp));
					x += 8;
					x = render_.draw_text(vtx::spos(x, 0), tmp);
				}
				break;
			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  チャネル情報描画
			@param[in]	ch	チャネル
			@return 情報更新があれば「true」
		*/
		//-----------------------------------------------------------------//
		bool draw_channel_info(uint32_t ch) noexcept
		{
			char tmp[64];
			if(ch == 0) {
				render_.set_fore_color(DEF_COLOR::Black);
				render_.fill_box(vtx::srect(0, 272 - 16 + 1, 240, 15));

				render_.set_fore_color(CH0_COLOR);
				if(ch_info_count_ < (60*2*3)) {
					utils::sformat("%s %s %s/div ", tmp, sizeof(tmp)) % get_ch_mult_str(ch0_mult_)
						% get_ch_mode_str(ch0_mode_) % get_ch_volt_str(ch0_volt_);
					auto x = render_.draw_text(vtx::spos(0, 272 - 16 + 1), tmp);
					make_freq_(wave_info0_.freq_, tmp, sizeof(tmp));
					render_.draw_text(vtx::spos(x, 272 - 16 + 1), tmp);
				} else {
					auto gain = capture_.get_voltage_gain(0);
					if(ch0_mult_ == CH_MULT::X10) {
						gain *= 10.0f;
					}
					make_ch_voltage_(wave_info0_, gain, tmp, sizeof(tmp));
					render_.draw_text(vtx::spos(0, 272 - 16 + 1), tmp);
				}
			} else {
				render_.set_fore_color(DEF_COLOR::Black);
				render_.fill_box(vtx::srect(240, 272 - 16 + 1, 240, 15));

				render_.set_fore_color(CH1_COLOR);
				if(ch_info_count_ < (60*2*3)) {
					utils::sformat("%s %s %s/div ", tmp, sizeof(tmp)) % get_ch_mult_str(ch1_mult_)
						% get_ch_mode_str(ch1_mode_) % get_ch_volt_str(ch1_volt_);
					auto x = render_.draw_text(vtx::spos(240, 272 - 16 + 1), tmp);
					make_freq_(wave_info1_.freq_, tmp, sizeof(tmp));
					render_.draw_text(vtx::spos(x, 272 - 16 + 1), tmp);
				} else {
					auto gain = capture_.get_voltage_gain(1);
					if(ch1_mult_ == CH_MULT::X10) {
						gain *= 10.0f;
					}
					make_ch_voltage_(wave_info1_, gain, tmp, sizeof(tmp));
					render_.draw_text(vtx::spos(240, 272 - 16 + 1), tmp);
				}
			}
			++ch_info_count_;
			if(ch_info_count_ >= (60*4*3)) {
				ch_info_count_ = 0;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  UI 操作サービス
			@return 更新が必要なら「true」を返す。
		*/
		//-----------------------------------------------------------------//
		bool ui_service() noexcept
		{
			auto num = touch_.get_touch_num();
			auto num_back = touch_num_;
			touch_num_ = num;
			const auto& p = touch_.get_touch_pos(0);

			bool draw = false;
			// チャネルモードが変更になったら、vpos をリセットする。
			if(ch0_mode_back_ != ch0_mode_) {
				ch0_vpos_ = VOLT_OFS;
				draw = true;
			}
			ch0_mode_back_ = ch0_mode_;
			if(ch1_mode_back_ != ch1_mode_) {
				ch1_vpos_ = VOLT_OFS;
				draw = true;
			}
			ch1_mode_back_ = ch1_mode_;

			if(num == 0) {
				if(p.before == TOUCH::EVENT::CONTACT && p.event == TOUCH::EVENT::UP) {
					if(area_ == AREA::TRG) {
						++trg_update_;
					}
					area_ = AREA::NONE;
					draw = true;
				}
			}

			if(num == 1) {
				if(p.event == TOUCH::EVENT::DOWN) {
					scan_area_(p.pos);
				} else if(p.event == TOUCH::EVENT::CONTACT) {
					auto d = p.pos - p.org;
					switch(area_) {
					case AREA::WAVE:
						if(target_ == TARGET::CH0) {
							ch0_vpos_ = ch0_vorg_ + d.y;
							auto trg = capture_.get_trg_mode();
							if(trg == TRG_MODE::CH0_POS || trg == TRG_MODE::CH0_NEG) {
								trg_pos_ = trg_org_ + d.y;
							}
							time_pos_ = time_org_ + d.x;
						} else if(target_ == TARGET::CH1) {
							ch1_vpos_ = ch1_vorg_ + d.y;
							auto trg = capture_.get_trg_mode();
							if(trg == TRG_MODE::CH1_POS || trg == TRG_MODE::CH1_NEG) {
								trg_pos_ = trg_org_ + d.y;
							}
							time_pos_ = time_org_ + d.x;
						}
						break;
					case AREA::TRG:
						trg_pos_ = trg_org_ + d.y;
						if(trg_pos_ < 16) trg_pos_ = 16;
						else if(trg_pos_ >= (272-16)) trg_pos_ = 272-16;
						break;
					case AREA::MES_TIME_0:
						mes_time_0_pos_ = mes_time_0_org_ + d.x;
						if(mes_time_0_pos_ < 0) mes_time_0_pos_ = 0;
						else if(mes_time_0_pos_ >= TIME_SIZE) mes_time_0_pos_ = TIME_SIZE;
						break;
					case AREA::MES_TIME_1:
						mes_time_1_pos_ = mes_time_1_org_ + d.x;
						if(mes_time_1_pos_ < 0) mes_time_1_pos_ = 0;
						else if(mes_time_1_pos_ >= TIME_SIZE) mes_time_1_pos_ = TIME_SIZE;
						break;
					case AREA::MES_VOLT_0:
						mes_volt_0_pos_ = mes_volt_0_org_ + d.y;
						if(mes_volt_0_pos_ < 16) mes_volt_0_pos_ = 16;
						else if(mes_volt_0_pos_ >= (272-16)) mes_volt_0_pos_ = 272-16;
						break;
					case AREA::MES_VOLT_1:
						mes_volt_1_pos_ = mes_volt_1_org_ + d.y;
						if(mes_volt_1_pos_ < 16) mes_volt_1_pos_ = 16;
						else if(mes_volt_1_pos_ >= (272-16)) mes_volt_1_pos_ = 272-16;
						break;
					default:
						break;
					}
					draw = true;
				}
			} else if(num == 2) {  // 二本タッチの場合
				const auto& p2 = touch_.get_touch_pos(1);
#if 0
				if(measere_ == MEASERE::TIME) {
					auto d = p.pos - p2.pos;
					auto len = intmath::sqrt16(d.x * d.x + d.y * d.y);
					if(p2.event == TOUCH::EVENT::DOWN) {
						mes_ref_size_ = mes_time_size_;
						mes_ref_len_  = len.val;
					} else {
						mes_time_size_ = mes_ref_size_
							+ static_cast<int16_t>(len.val) - mes_ref_len_;
						if(mes_time_size_ < 0) mes_time_size_ = 0;
					}
				} else if(measere_ == MEASERE::VOLT) {
					auto d = p.pos - p2.pos;
					auto len = intmath::sqrt16(d.x * d.x + d.y * d.y);
					if(p2.event == TOUCH::EVENT::DOWN) {
						mes_ref_size_ = mes_volt_size_;
						mes_ref_len_  = len.val;
					} else {
						mes_volt_size_ = mes_ref_size_
							+ static_cast<int16_t>(len.val) - mes_ref_len_;
						if(mes_volt_size_ < 0) mes_volt_size_ = 0;
					}
				} else {
#endif
					{
				}
			} else if(num == 3) {

			}

			return draw;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  アップ・デート（波形の描画）
		*/
		//-----------------------------------------------------------------//
		void update() noexcept
		{
			render_.set_fore_color(DEF_COLOR::Black);
			render_.fill_box(vtx::srect(0, 16, 440, 240));

			draw_grid(0, 16, 440, 240, GRID);

			auto sr = static_cast<float>(get_smp_rate(smp_mode_) * 1e-6 / static_cast<float>(GRID));
			auto step = sr / (1.0f / static_cast<float>(capture_.get_capture_samplerate()));
			auto istep = static_cast<int32_t>(step * 16384.0f);
			int32_t pos = 0;
			auto tofs = static_cast<int32_t>(static_cast<float>(time_pos_) * -step);

			auto ch0 = static_cast<float>(get_mvolt(ch0_volt_)) * 1e-3;  // mV to V
			auto ch1 = static_cast<float>(get_mvolt(ch1_volt_)) * 1e-3;  // mV to V
			auto grid = static_cast<float>(GRID);
			ch0 /= grid;
			ch1 /= grid;
			auto gain0 = capture_.get_voltage_gain(0);
			if(ch0_mult_ == CH_MULT::X10) {
				gain0 *= 10.0f;
			}
			auto gain1 = capture_.get_voltage_gain(1);
			if(ch1_mult_ == CH_MULT::X10) {
				gain1 *= 10.0f;
			}
			int32_t ich0 = gain0 / ch0 * 16384.0f / static_cast<float>(CAPTURE::ADC_QUANTIZE);
			int32_t ich1 = gain1 / ch1 * 16384.0f / static_cast<float>(CAPTURE::ADC_QUANTIZE);
			int32_t p0;
			int16_t ch0_y;
			int16_t ch1_y;
			for(int16_t x = 0; x < (TIME_SIZE - 1); ++x) {  // ピクセル単位
				if(x == 0) {
					p0 = tofs + (pos >> 14);
					cap_win_org_ = p0;
				}
				const auto& d0 = capture_.get(p0);
				int32_t p1 = tofs + (pos >> 14);
				const auto& d1 = capture_.get(p1);
				pos += istep;
				auto d1x = d1.x;
				auto d1y = d1.y;
				bool clipout = false;
				if(p0 <= -static_cast<int32_t>(capture_.get_before_count()) || p0 >= static_cast<int32_t>(capture_.get_after_count())) {
					clipout = true;
				}
				p0 = p1;
				if(ch0_mode_ != CH_MODE::OFF) {
					if(x == 0) {
						ch0_y = (static_cast<int32_t>(d0.x) * ich0) >> 14;
					}
					int16_t y1 = (static_cast<int32_t>(d1x) * ich0) >> 14;
					if(!clipout) {
						render_.set_fore_color(CH0_COLOR);
						int16_t ofs = ch0_vpos_;
						render_.line(vtx::spos(x, ofs - ch0_y), vtx::spos(x + 1, ofs - y1));
					}
					ch0_y = y1;
				}
				if(ch1_mode_ != CH_MODE::OFF) {
					if(x == 0) {
						ch1_y = (static_cast<int32_t>(d0.y) * ich1) >> 14;
					}
					int16_t y1 = (static_cast<int32_t>(d1y) * ich1) >> 14;
					if(!clipout) {
						render_.set_fore_color(CH1_COLOR);
						int16_t ofs = ch1_vpos_;
						render_.line(vtx::spos(x, ofs - ch1_y), vtx::spos(x + 1, ofs - y1));
					}
					ch1_y = y1;
				}
			}
			cap_win_end_ = p0;

			// 最後に押されたボタン（CH0,CH1,SMP）により操作対象が変化する、それに合わせて、表示（ゲート）を切り替える。
			switch(target_) {
			case TARGET::CH0:
				render_.set_fore_color(SMP_COLOR);
				draw_time_gate_(time_pos_);
				if(ch0_mode_ != CH_MODE::OFF) {
					render_.set_fore_color(CH0_COLOR);
					draw_ch_arrow_(ch0_vpos_);
				}
				render_.set_fore_color(SMP_COLOR);
				draw_time_gate_(time_pos_);
				break;
			case TARGET::CH1:
				render_.set_fore_color(SMP_COLOR);
				draw_time_gate_(time_pos_);
				if(ch1_mode_ != CH_MODE::OFF) {
					render_.set_fore_color(CH1_COLOR);
					draw_ch_arrow_(ch1_vpos_);
				}
				render_.set_fore_color(SMP_COLOR);
				draw_time_gate_(time_pos_);
				break;
			}

			switch(measere_) {  // 計測モードの場合
			case MEASERE::TIME_SUB:
				render_.set_fore_color(MES_COLOR);
				render_.draw_mobj(vtx::spos(mes_time_0_pos_ - 7, 16), resource::bitmap::dir_1_, false);
				render_.line(vtx::spos(mes_time_0_pos_, 16+14), vtx::spos(mes_time_0_pos_, 272-16));
				render_.draw_mobj(vtx::spos(mes_time_1_pos_ - 7, 272-16-14), resource::bitmap::dir_3_, false);
				render_.line(vtx::spos(mes_time_1_pos_, 16), vtx::spos(mes_time_1_pos_, 272-16-14));
				break;
			case MEASERE::TIME_ABS:
				render_.set_fore_color(MES_COLOR);
				render_.draw_mobj(vtx::spos(mes_time_0_pos_ - 7, 16), resource::bitmap::dir_1_, false);
				render_.line(vtx::spos(mes_time_0_pos_, 16+14), vtx::spos(mes_time_0_pos_, 272-16));
				break;
			case MEASERE::CH0_SUB:
			case MEASERE::CH1_SUB:
				render_.set_fore_color(MES_COLOR);
				render_.draw_mobj(vtx::spos(0, mes_volt_0_pos_ - 7), resource::bitmap::dir_2_, false);
				render_.line(vtx::spos(14, mes_volt_0_pos_), vtx::spos(440, mes_volt_0_pos_));
				render_.draw_mobj(vtx::spos(440-14, mes_volt_1_pos_ - 7), resource::bitmap::dir_0_, false);
				render_.line(vtx::spos(0, mes_volt_1_pos_), vtx::spos(440-14, mes_volt_1_pos_));
				break;
			case MEASERE::CH0_ABS:
			case MEASERE::CH1_ABS:
				render_.set_fore_color(MES_COLOR);
				render_.draw_mobj(vtx::spos(0, mes_volt_0_pos_ - 7), resource::bitmap::dir_2_, false);
				render_.line(vtx::spos(14, mes_volt_0_pos_), vtx::spos(440, mes_volt_0_pos_));
				break;
			default:  // 計測モード以外
				// トリガー位置調整
				render_.set_fore_color(TRG_COLOR);
				draw_trg_gate_(trg_pos_);
				break;
			}

			draw_sampling_info();

			{  // キャプチャー動作完了を検出したら、基本解析を行う
				auto cycle = capture_.get_capture_cycle();
				// キャプチャー更新、カレントのサンプリング周期変更？
				if(cycle != cap_cycle_ || smp_mode_ != cur_smp_mode_) {
					cap_cycle_ = cycle;
					cur_smp_mode_ = smp_mode_;
					// 見えている倍の領域をスキャン
					auto end = cap_win_end_ + (cap_win_end_ - cap_win_org_);
					capture_.analize(cap_win_org_, end, wave_info0_, wave_info1_);
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  チャネル情報関係、アップ・デート
			@return 情報更新があれば「true」
		*/
		//-----------------------------------------------------------------//
		bool update_info() noexcept
		{
			uint32_t n = 0;
			if(draw_channel_info(0)) ++n;
			if(draw_channel_info(1)) ++n;
			return n != 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  トリガー値の取得（A/D 変換値）
			@return トリガー値
		*/
		//-----------------------------------------------------------------//
		int16_t get_trg_value() const noexcept
		{
			float val = 0;
			auto trg = capture_.get_trg_mode();
			switch(trg) {
			case TRG_MODE::CH0_POS:
			case TRG_MODE::CH0_NEG:
				{
					float d = static_cast<float>(ch0_vpos_ - trg_pos_) * get_mvolt(ch0_volt_);
					d /= static_cast<float>(GRID);
					val = capture_.voltage_to_value(0, d * 1e-3);
					if(ch0_mult_ == CH_MULT::X10) {
						val /= 10.0f;
					}
				}
				break;
			case TRG_MODE::CH1_POS:
			case TRG_MODE::CH1_NEG:
				{
					float d = static_cast<float>(ch1_vpos_ - trg_pos_) * get_mvolt(ch1_volt_);
					d /= static_cast<float>(GRID);
					val = capture_.voltage_to_value(1, d * 1e-3);
					if(ch1_mult_ == CH_MULT::X10) {
						val /= 10.0f;
					}
				}
				break;
			default:
				break;
			}
			return val;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  トリガー電圧を変更した場合の取得 @n
					トリガー電圧変更で、「trg_update_」がインクリメント
			@return トリガー電圧変更カウンタ
		*/
		//-----------------------------------------------------------------//
		auto get_trg_update() const noexcept { return trg_update_; }
	};
}
