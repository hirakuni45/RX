#pragma once
//=====================================================================//
/*! @file
    @brief  波形描画クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
    @copyright  Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
                Released under the MIT license @n
                https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include "common/enum_utils.hpp"
#include "common/intmath.hpp"
#include "graphics/color.hpp"
#include "graphics/simple_dialog.hpp"

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

		static constexpr float GRID_SCALE     = 1.0f / static_cast<float>(CAPTURE::GRID);
		static const int16_t MENU_SIZE        = 40;
		static const int16_t TIME_SCROLL_AREA = RENDER::font_type::height + CAPTURE::GRID;
		static const int16_t CH0_MOVE_AREA    = (RENDER::glc_type::width - MENU_SIZE) / 2;
		static const int16_t CH1_MOVE_AREA    = RENDER::glc_type::width - MENU_SIZE;
		static const int16_t TIME_BEGIN_POS   = RENDER::font_type::height;
		static const int16_t TIME_LIMIT_POS   = RENDER::glc_type::height - RENDER::font_type::height - 1;
		static const int16_t VOLT_BEGIN_POS   = 0;
		static const int16_t VOLT_LIMIT_POS   = RENDER::glc_type::width - MENU_SIZE;

		static constexpr vtx::srect TIME_AREA = { 0, 0, 440-20, 16+40 };
		static constexpr vtx::srect CH0_AREA  = { 0, 16+40, (440-16)/2, 272-16-16-40 };
		static constexpr vtx::srect CH1_AREA  = { (440-16)/2, 16+40, (440-16)/2, 272-16-16-40 };
		static constexpr vtx::srect TRG_AREA  = { 440-20, 16, 20, 272-16*2 };

		static constexpr vtx::srect MES_AREA_TIME_0 = { 0, 0, 440, 16+20 };
		static constexpr vtx::srect MES_AREA_TIME_1 = { 0, 272-16-20, 440, 16+20 };
		static constexpr vtx::srect MES_AREA_VOLT_0 = { 0, 16, 40, 272-16*2 };
		static constexpr vtx::srect MES_AREA_VOLT_1 = { 440-20, 16, 40, 272-16*2 };

		typedef gui::simple_dialog<RENDER, TOUCH> DIALOG;

		RENDER&		render_;
		TOUCH&		touch_;
		CAPTURE&	capture_;

		DIALOG		dialog_;

		int16_t		time_org_;
		int16_t		time_pos_;
		int16_t		ch0_vorg_;
		int16_t		ch0_vpos_;
		int16_t		ch1_vorg_;
		int16_t		ch1_vpos_;
		int16_t		trg_org_;
		int16_t		trg_pos_;

//		CH_MULT		ch0_mult_;
		CH_MODE		ch0_mode_;
		CH_VOLT		ch0_volt_;
//		CH_MULT		ch1_mult_;
		CH_MODE		ch1_mode_;
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

		bool		touch_down_;
		uint8_t		touch_num_;

		uint16_t	trg_wait_;
		uint32_t	trg_update_;

		enum class AREA {
			NONE,
			TIME,
			CH0,
			CH1,
			TRG,
			MES_TIME_0,
			MES_TIME_1,
			MES_VOLT_0,
			MES_VOLT_1,
		};
		AREA		area_;


		void scan_area_(const vtx::spos& pos) noexcept
		{
			if(measere_ == MEASERE::TIME) {
				if(MES_AREA_TIME_0.is_focus(pos)) {
					area_ = AREA::MES_TIME_0;
					mes_time_0_org_ = pos.x;
				} else if(MES_AREA_TIME_1.is_focus(pos)) {
					area_ = AREA::MES_TIME_1;
					mes_time_1_org_ = pos.x;
				}
			} else if(measere_ == MEASERE::CH0_VOLT || measere_ == MEASERE::CH1_VOLT) {
				if(MES_AREA_VOLT_0.is_focus(pos)) {
					area_ = AREA::MES_VOLT_0;
					mes_volt_0_org_ = pos.y;
				} else if(MES_AREA_VOLT_1.is_focus(pos)) {
					area_ = AREA::MES_VOLT_1;
					mes_volt_1_org_ = pos.y;
				}
			} else {
				if(TRG_AREA.is_focus(pos)) {
					area_ = AREA::TRG;
					trg_org_ = trg_pos_;
				} else if(CH0_AREA.is_focus(pos)) {
					area_ = AREA::CH0;
					ch0_vorg_ = ch0_vpos_;
					trg_org_ = trg_pos_;
				} else if(CH1_AREA.is_focus(pos)) {
					area_ = AREA::CH1;
					ch1_vorg_ = ch1_vpos_;
					trg_org_ = trg_pos_;
				} else if(TIME_AREA.is_focus(pos)) {
					area_ = AREA::TIME;
					time_org_ = time_pos_;
				} else {
					area_ = AREA::NONE;
				}
			}
		}


		void update_measere_() noexcept
		{
		}


		void make_volt_(int16_t val, int32_t unit_mv, char* tmp, uint32_t len)
		{
			auto n = static_cast<float>(val * unit_mv) / static_cast<float>(GRID);
			if(std::abs(n) >= 1000.0f) {
				n /= 1000.0f;
				utils::sformat("%4.3fV", tmp, len) % n;
			} else {
				utils::sformat("%3.2fmv", tmp, len) % n;
			}
		}


		void make_rate_(int16_t val, int32_t unit_us, char* str, uint32_t len)
		{
			int32_t n = val * unit_us / GRID;
			int32_t div = 1;
			const char* units = "us";
			if(std::abs(n) >= 1000) {
				div = 1000;
				n /= div;
				units = "ms";
			}
			int32_t m = std::abs(val * unit_us * 100 / div / GRID) % 100;
			utils::sformat("%d.%d%s", str, len) % n % m % units;
		}


		void make_freq_(int16_t val, int32_t unit_us, char* str, uint32_t len)
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
			dialog_(render, touch),
			time_org_(0), time_pos_(0),
			ch0_vorg_(272/2), ch0_vpos_(272/2),
			ch1_vorg_(272/2), ch1_vpos_(272/2),
			trg_org_(272/2), trg_pos_(272/2),
//			ch0_mult_(CH_MULT::X1),
			ch0_mode_(CH_MODE::AC), ch0_volt_(CH_VOLT::_10V),
//			ch1_mult_(CH_MULT::X1),
			ch1_mode_(CH_MODE::AC), ch1_volt_(CH_VOLT::_10V),
			smp_mode_(SMP_MODE::_1us),
			measere_(MEASERE::OFF),
			mes_time_0_org_(220), mes_time_0_pos_(220), mes_time_1_org_(220), mes_time_1_pos_(220),
			mes_volt_0_org_(272/2), mes_volt_0_pos_(272/2), mes_volt_1_org_(272/2), mes_volt_1_pos_(272/2),
			touch_down_(false), touch_num_(0), trg_wait_(0), trg_update_(0),
			area_(AREA::NONE)
		{ }


#if 0
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
#endif


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
		void set_ch0_volt(CH_VOLT volt) noexcept {
			ch0_volt_ = volt;
#if 0
			if((static_cast<float>(get_volt(ch0_volt_)) * 1e-3) < VOLT_DIV_H) {
				capture_.set_voltage_gain(0, VOLT_DIV_H);
			} else {
				capture_.set_voltage_gain(0, VOLT_DIV_L);
			}
#endif 
		}


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
		void set_ch1_volt(CH_VOLT volt) noexcept {
			ch1_volt_ = volt;
#if 0
			if((static_cast<float>(get_volt(ch1_volt_)) * 1e-3) < VOLT_DIV_H) {
				capture_.set_voltage_gain(1, VOLT_DIV_H);
			} else {
				capture_.set_voltage_gain(1, VOLT_DIV_L);
			}
#endif
		}


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
			for(int16_t i = x; i <= (x + w); i += unit) {
				uint32_t mask;
				if(i == x || i == (x + w)) {
					mask = -1;
				} else {
					mask = 0b11000000110000001100000011000000;
				}
				render_.set_stipple(mask);
				render_.line(vtx::spos(i, y), vtx::spos(i, y + h));
			}
			for(int16_t i = y; i <= (y + h); i += unit) {
				uint32_t mask;
				if(i == y || i == (y + h)) {
					mask = -1;
				} else {
					mask = 0b11000000110000001100000011000000;
				}
				render_.set_stipple(mask);
				render_.line(vtx::spos(x, i), vtx::spos(x + w, i));
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
			if(measere_ == MEASERE::OFF) {
				bool disp = true;
				if(capture_.get_trg_mode(true) != TRG_MODE::NONE) {
					++trg_wait_;
					if(trg_wait_ >= 30) {
						trg_wait_ = 0;
					}
					if(trg_wait_ < 10) {
						disp = false;
					}
				}
				if(disp) {
					auto trg = capture_.get_trg_mode();
					char tmp[16];
					utils::sformat("%s/div, ", tmp, sizeof(tmp)) % get_smp_str(smp_mode_);
					auto x = render_.draw_text(vtx::spos(0, 0), tmp);
					x = render_.draw_text(vtx::spos(x, 0), capture_.get_trigger_str());
					if(trg == TRG_MODE::CH0_POS || trg == TRG_MODE::CH0_NEG) {
						x = render_.draw_text(vtx::spos(x, 0), ": ");
						auto v = ch0_vpos_ - trg_pos_;
						make_volt_(v, get_volt(ch0_volt_), tmp, sizeof(tmp));
						x = render_.draw_text(vtx::spos(x, 0), tmp);
					} else if(trg == TRG_MODE::CH1_POS || trg == TRG_MODE::CH1_NEG) {
						x = render_.draw_text(vtx::spos(x, 0), ": ");
						auto v = ch1_vpos_ - trg_pos_;
						make_volt_(v, get_volt(ch1_volt_), tmp, sizeof(tmp));
						x = render_.draw_text(vtx::spos(x, 0), tmp);
					}
				}
			} else if(measere_ == MEASERE::CH0_VOLT) {
				auto d = mes_volt_1_pos_ - mes_volt_0_pos_;
				auto x = render_.draw_text(vtx::spos(0, 0), "CH0: ");
				char tmp[16];
				make_volt_(d, get_volt(ch0_volt_), tmp, sizeof(tmp));
				x = render_.draw_text(vtx::spos(x, 0), tmp);
			} else if(measere_ == MEASERE::CH1_VOLT) {
				auto d = mes_volt_1_pos_ - mes_volt_0_pos_;
				auto x = render_.draw_text(vtx::spos(0, 0), "CH1: ");
				char tmp[16];
				make_volt_(d, get_volt(ch1_volt_), tmp, sizeof(tmp));
				x = render_.draw_text(vtx::spos(x, 0), tmp);
			} else if(measere_ == MEASERE::TIME) {
				auto d = mes_time_1_pos_ - mes_time_0_pos_;
				char tmp[16];
				make_rate_(d, get_smp_rate(smp_mode_), tmp, sizeof(tmp));
				auto x = render_.draw_text(vtx::spos(0, 0), tmp);
				make_freq_(d, get_smp_rate(smp_mode_), tmp, sizeof(tmp));
				x += 8;
				x = render_.draw_text(vtx::spos(x, 0), tmp);
				x += 8;
				// CH0 の電圧、計測ポイント０
				
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  チャネル情報描画
			@param[in]	ch	チャネル
		*/
		//-----------------------------------------------------------------//
		void draw_channel_info(uint32_t ch) noexcept
		{
			char tmp[32];
			if(ch == 0) {
				render_.set_fore_color(DEF_COLOR::Black);
				render_.fill_box(vtx::srect(0, 272 - 16 + 1, 240, 15));
				render_.set_fore_color(CH0_COLOR);
//				utils::sformat("0.%s: %s, %s/div", tmp, sizeof(tmp)) % get_ch_mult_str(ch0_mult_)
				utils::sformat("0: %s, %s/div", tmp, sizeof(tmp))
					% get_ch_mode_str(ch0_mode_) % get_ch_volt_str(ch0_volt_);
				render_.draw_text(vtx::spos(0, 272 - 16 + 1), tmp);
			} else {
				render_.set_fore_color(DEF_COLOR::Black);
				render_.fill_box(vtx::srect(240, 272 - 16 + 1, 240, 15));
				render_.set_fore_color(CH1_COLOR);
//				utils::sformat("1.%s: %s, %s/div", tmp, sizeof(tmp)) % get_ch_mult_str(ch1_mult_)
				utils::sformat("1: %s, %s/div", tmp, sizeof(tmp))
					% get_ch_mode_str(ch1_mode_) % get_ch_volt_str(ch1_volt_);
				render_.draw_text(vtx::spos(240, 272 - 16 + 1), tmp);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  UI 操作サービス
			@return 更新が必要なら「true」
		*/
		//-----------------------------------------------------------------//
		bool ui_service() noexcept
		{
			auto num = touch_.get_touch_num();
			auto num_back = touch_num_;
			touch_num_ = num;
			const auto& p = touch_.get_touch_pos(0);

			if(num == 0) {
				touch_down_ = false;
				if(p.before == TOUCH::EVENT::CONTACT && p.event == TOUCH::EVENT::UP) {
					if(area_ == AREA::TRG) {
						++trg_update_;
					}
					area_ = AREA::NONE;
					return true;
				} else {
					return false;
				}
			}

			if(num == 1) {
				if(p.event == TOUCH::EVENT::DOWN) {
					scan_area_(p.pos);
				} else if(p.event == TOUCH::EVENT::CONTACT) {
					auto d = p.pos - p.org;
					switch(area_) {
					case AREA::TIME:
						time_pos_ = time_org_ + d.x;
						touch_down_ = true;
						break;
					case AREA::CH0:
						ch0_vpos_ = ch0_vorg_ + d.y;
						{
							auto trg = capture_.get_trg_mode();
							if(trg == TRG_MODE::CH0_POS || trg == TRG_MODE::CH0_NEG) {
								trg_pos_ = trg_org_ + d.y;
							}
						}
						touch_down_ = true;
						break;
					case AREA::CH1:
						ch1_vpos_ = ch1_vorg_ + d.y;
						{
							auto trg = capture_.get_trg_mode();
							if(trg == TRG_MODE::CH1_POS || trg == TRG_MODE::CH1_NEG) {
								trg_pos_ = trg_org_ + d.y;
							}
						}
						touch_down_ = true;
						break;
					case AREA::TRG:
						trg_pos_ = trg_org_ + d.y;
						if(trg_pos_ < 16) trg_pos_ = 16;
						else if(trg_pos_ >= (272-16)) trg_pos_ = 272-16;
						touch_down_ = true;
						break;
					case AREA::MES_TIME_0:
						mes_time_0_pos_ = mes_time_0_org_ + d.x;
						if(mes_time_0_pos_ < 0) mes_time_0_pos_ = 0;
						else if(mes_time_0_pos_ >= 440) mes_time_0_pos_ = 440;
						break;
					case AREA::MES_TIME_1:
						mes_time_1_pos_ = mes_time_1_org_ + d.x;
						if(mes_time_1_pos_ < 0) mes_time_1_pos_ = 0;
						else if(mes_time_1_pos_ >= 440) mes_time_1_pos_ = 440;
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
				}
			} else if(num == 2) {
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
					return false;
				}
			} else if(num == 3) {

				return false;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  アップ・デート（再描画）
		*/
		//-----------------------------------------------------------------//
		void update() noexcept
		{
			render_.set_fore_color(DEF_COLOR::Black);
			render_.fill_box(vtx::srect(0, 16, 440, 240));
			draw_grid(0, 16, 440, 240, CAPTURE::GRID);

			if(touch_down_) {
				render_.set_fore_color(DEF_COLOR::Red);
				render_.line(vtx::spos(0, TIME_SCROLL_AREA),
							 vtx::spos(CH1_MOVE_AREA, TIME_SCROLL_AREA));				 
				render_.line(vtx::spos(CH0_MOVE_AREA, TIME_SCROLL_AREA),
							 vtx::spos(CH0_MOVE_AREA, 272 - 16));
				render_.line(vtx::spos(CH1_MOVE_AREA, TIME_SCROLL_AREA),
							 vtx::spos(CH1_MOVE_AREA, 272 - 16));
				render_.set_fore_color(TRG_COLOR);
				render_.line(vtx::spos(0, trg_pos_), vtx::spos(440-14, trg_pos_));
			}

			auto sr = static_cast<float>(get_smp_rate(smp_mode_) * 1e-6
				/ static_cast<float>(GRID));
			auto step = sr / (1.0f / static_cast<float>(capture_.get_samplerate()));
			int32_t istep = static_cast<int32_t>(step * 65536.0f);
			int32_t pos = 0;
			auto iofs = static_cast<int16_t>(static_cast<float>(time_pos_) * -step);

			// VOLT_DIV_L/H
			float ch0 = static_cast<float>(get_volt(ch0_volt_)) * 1e-3;  // mV to V
			float ch1 = static_cast<float>(get_volt(ch1_volt_)) * 1e-3;  // mV to V
			float grid = static_cast<float>(GRID);
			ch0 /= grid;
			ch1 /= grid;
			float div0 = capture_.get_voltage_gain(0) / 2048.0f;
			float div1 = capture_.get_voltage_gain(1) / 2048.0f;
			int32_t ich0 = div0 / ch0 * 65536.0f;
			int32_t ich1 = div1 / ch1 * 65536.0f;
			int16_t p0;
			int16_t ch0_y;
			int16_t ch1_y;
			for(int16_t x = 0; x < (TIME_SIZE - 1); ++x) {
				if(x == 0) {
					p0 = iofs + (pos >> 16);
				}
				const auto& d0 = capture_.get(p0);
				pos += istep;
				int16_t p1 = iofs + (pos >> 16);
				const auto& d1 = capture_.get(p1);
				p0 = p1;
				if(ch0_mode_ != CH_MODE::OFF) {
					if(x == 0) {
						ch0_y = (static_cast<int32_t>(-d0.x) * ich0) >> 16;
					}
					int16_t y1 = (static_cast<int32_t>(-d1.x) * ich0) >> 16;
					render_.set_fore_color(CH0_COLOR);
					int16_t ofs = ch0_vpos_;
					render_.line(vtx::spos(x, ofs + ch0_y), vtx::spos(x + 1, ofs + y1));
					ch0_y = y1;
				}
				if(ch1_mode_ != CH_MODE::OFF) {
					if(x == 0) {
						ch1_y = (static_cast<int32_t>(-d0.y) * ich1) >> 16;
					}
					int16_t y1 = (static_cast<int32_t>(-d1.y) * ich1) >> 16;
					render_.set_fore_color(CH1_COLOR);
					int16_t ofs = ch1_vpos_;
					render_.line(vtx::spos(x, ofs + ch1_y), vtx::spos(x + 1, ofs + y1));
					ch1_y = y1;
				}
			}

			if(measere_ == MEASERE::TIME) {
				render_.set_fore_color(MES_COLOR);
				render_.draw_mobj(vtx::spos(mes_time_0_pos_ - 7, 16),
					resource::bitmap::dir_1_, false);
				render_.line(vtx::spos(mes_time_0_pos_, 16+14), vtx::spos(mes_time_0_pos_, 272-16));
				render_.draw_mobj(vtx::spos(mes_time_1_pos_ - 7, 272-16-14),
					resource::bitmap::dir_3_, false);
				render_.line(vtx::spos(mes_time_1_pos_, 16), vtx::spos(mes_time_1_pos_, 272-16-14));
			} else if(measere_ == MEASERE::CH0_VOLT || measere_ == MEASERE::CH1_VOLT) {
				render_.set_fore_color(MES_COLOR);
				render_.draw_mobj(vtx::spos(0, mes_volt_0_pos_ - 7),
					resource::bitmap::dir_2_, false);
				render_.line(vtx::spos(14, mes_volt_0_pos_), vtx::spos(440, mes_volt_0_pos_));
				render_.draw_mobj(vtx::spos(440-14, mes_volt_1_pos_ - 7),
					resource::bitmap::dir_0_, false);
				render_.line(vtx::spos(0, mes_volt_1_pos_), vtx::spos(440-14, mes_volt_1_pos_));
			} else {
				// トリガー基準
				render_.set_fore_color(TRG_COLOR);
				render_.draw_mobj(vtx::spos(440-14, trg_pos_ - 7),
					resource::bitmap::dir_0_, false);
			}

			// トリガー位置（時間）表示
			{
				auto pos = time_pos_;
				if(pos >= 0 && pos < TIME_SIZE) {
					render_.set_fore_color(TRG_COLOR);
					render_.line(vtx::spos(pos, 16), vtx::spos(pos, 272-16));
				}
			}

			draw_sampling_info();
			draw_channel_info(0);
			draw_channel_info(1);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  トリガー値の取得（A/D 変換値）
			@return トリガー値
		*/
		//-----------------------------------------------------------------//
		int16_t get_trg_value() const noexcept
		{
			int16_t val = 0;
			auto trg = capture_.get_trg_mode();
			if(trg == TRG_MODE::CH0_POS || trg == TRG_MODE::CH0_NEG) {
				float d = static_cast<float>(ch0_vpos_ - trg_pos_) * get_volt(ch0_volt_);
				d /= static_cast<float>(GRID);
				val = capture_.voltage_to_value(0, d * 1e-3);
			} else if(trg == TRG_MODE::CH1_POS || trg == TRG_MODE::CH1_NEG) {
				float d = static_cast<float>(ch1_vpos_ - trg_pos_) * get_volt(ch1_volt_);
				d /= static_cast<float>(GRID);
				val = capture_.voltage_to_value(1, d * 1e-3);
			}
			return val;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  トリガー電圧変更の取得
			@return トリガー電圧変更
		*/
		//-----------------------------------------------------------------//
		auto get_trg_update() const noexcept { return trg_update_; }

	};
}
