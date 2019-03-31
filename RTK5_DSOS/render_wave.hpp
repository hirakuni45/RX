#pragma once
//=====================================================================//
/*! @file
    @brief  波形描画クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
    @copyright  Copyright (C) 2018 Kunihito Hiramatsu @n
                Released under the MIT license @n
                https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include "common/enum_utils.hpp"
#include "common/intmath.hpp"
#include "graphics/color.hpp"
#include "graphics/dialog.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  波形描画クラス
		@param[in]	RENDER	描画クラス
		@param[in]	CAPTURE	キャプチャー・クラス
		@param[in]	TOUCH	タッチ・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RENDER, class CAPTURE, class TOUCH>
	class render_wave {

		static const int16_t GRID             = 40;
		static constexpr float   GRID_SCALE   = 1.0f / static_cast<float>(GRID);
		static const int16_t MENU_SIZE        = 40;
		static const int16_t TIME_SCROLL_AREA = RENDER::font_height + GRID;
		static const int16_t CH0_MOVE_AREA    = (RENDER::glc_type::width - MENU_SIZE) / 2;
		static const int16_t CH1_MOVE_AREA    = RENDER::glc_type::width - MENU_SIZE;
		static const int16_t TIME_BEGIN_POS   = RENDER::font_height;
		static const int16_t TIME_LIMIT_POS   = RENDER::glc_type::height - RENDER::font_height - 1;
		static const int16_t VOLT_BEGIN_POS   = 0;
		static const int16_t VOLT_LIMIT_POS   = RENDER::glc_type::width - MENU_SIZE;

		typedef gui::dialog<RENDER, TOUCH> DIALOG;

		RENDER&		render_;
		CAPTURE&	capture_;
		TOUCH&		touch_;
		DIALOG		dialog_;

		int16_t		time_pos_;
		int16_t		time_org_;

		int16_t		ch0_vpos_;
		int16_t		ch0_vorg_;
		int16_t		ch1_vpos_;
		int16_t		ch1_vorg_;

		// 100Hz, 250Hz, 500Hz,
		// 1KHz, 5KHz, 10KHz, 25KHz, 50KHz,
		// 100KHz, 250KHz, 500KHz, 1MHz, 2MHz
		uint16_t	rate_div_;

		//	Volt/div "0.05", "0.1", "0.25", "0.5", "1.0", "2.5", "5.0", "10.0" 
		uint16_t	ch0_div_;
		uint16_t	ch1_div_;

		enum class MENU : uint8_t {
			NONE,
			CH0,
			CH1,
			TRG,
			SMP,
			MES,
			OPT
		};

		MENU		menu_;
		MENU		menu_run_;

		enum class MEASERE : uint8_t {
			NONE,
			TIME,
			VOLT,
		};
		MEASERE		measere_;
		int16_t		mes_time_begin_;
		int16_t		mes_time_size_;
		int16_t		mes_time_org_;
		int16_t		mes_volt_begin_;
		int16_t		mes_volt_size_;
		int16_t		mes_volt_org_;
		int16_t		mes_ref_size_;
		int16_t		mes_ref_len_;

		bool		touch_down_;
		uint8_t		touch_num_;

		typedef graphics::def_color DEF_COLOR;


		void update_measere_() noexcept
		{
			render_.set_fore_color(DEF_COLOR::White);
			if(measere_ == MEASERE::TIME) {
				auto org = mes_time_begin_;
				render_.line(vtx::spos(org, TIME_BEGIN_POS), vtx::spos(org, TIME_LIMIT_POS));
				auto end = mes_time_begin_ + mes_time_size_;
				if(0 < end && end < VOLT_LIMIT_POS) {
					render_.line(vtx::spos(end, TIME_BEGIN_POS), vtx::spos(end, TIME_LIMIT_POS));
				}
			} else if(measere_ == MEASERE::VOLT) {
				auto org = mes_volt_begin_;
				render_.line(vtx::spos(VOLT_BEGIN_POS, org), vtx::spos(VOLT_LIMIT_POS, org));
				auto end = mes_volt_begin_ + mes_volt_size_;
				if(0 < end && end < VOLT_LIMIT_POS) {
					
					render_.line(vtx::spos(VOLT_BEGIN_POS, end), vtx::spos(VOLT_LIMIT_POS, end)); 
				}
			}
		}


		void auto_scale_(float a, char unit, char* out, uint32_t len)
		{
			char sc = 0;
			if(a < 1e-6) {
				a *= 1e9;
				sc = 'n';
			} else if(a < 1e-3) {
				a *= 1e6;
				sc = 'u';
			} else if(a < 1.0f) {
				a *= 1e3;
				sc = 'm';
			}
			if(sc != 0) {
				utils::sformat("%4.3f [%c%c]", out, len) % a % sc % unit;
			} else {
				utils::sformat("%4.3f [%c]", out, len) % a % unit;
			}
		}


		void freq_scale_(float a, char* out, uint32_t len)
		{
			char sc = 0;
			if(a >= 1e6) {
				a /= 1e6;
				sc = 'M';
			} else if(a >= 1e3) {
				a /= 1e3;
				sc = 'K';
			}
			if(sc != 0) {
				utils::sformat("%3.2f [%cHz]", out, len) % a % sc;
			} else {
				utils::sformat("%3.2f [Hz]", out, len) % a;
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
			@param[in]	render	描画クラス
			@param[in]	capture	キャプチャー・クラス
		*/
		//-----------------------------------------------------------------//
		render_wave(RENDER& render, CAPTURE& capture, TOUCH& touch) noexcept :
			render_(render), capture_(capture), touch_(touch), dialog_(render, touch),
			time_pos_(0), time_org_(0),
			ch0_vpos_(0), ch0_vorg_(0), ch1_vpos_(0), ch1_vorg_(0),
			rate_div_(11), ch0_div_(3), ch1_div_(3),
			menu_(MENU::NONE), menu_run_(MENU::NONE),
			measere_(MEASERE::NONE),
			mes_time_begin_(0), mes_time_size_(40), mes_time_org_(0),
			mes_volt_begin_(0), mes_volt_size_(40), mes_volt_org_(0),
			mes_ref_size_(0), mes_ref_len_(0),
			touch_down_(false), touch_num_(0)
		{ }


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
			@brief  サンプリング情報描画
			@param[in]	ch	チャネル
		*/
		//-----------------------------------------------------------------//
		void draw_sampling_info() noexcept
		{
			static const char* freq[] = {
				"100Hz", "250Hz", "500Hz",
				"1KHz", "5KHz", "10KHz", "25KHz", "50KHz",
				"100KHz", "250KHz", "500KHz", "1MHz", "2MHz"
			};
			static const char* rate[] = {
				"10mS", "4mS", "2mS",
				"1mS", "200uS", "100uS", "40uS", "20uS",
				"10uS", "4uS", "2uS", "1uS", "500nS"
			};
			static const float rate_f[] = {
				10e-3, 4e-3, 2e-3,
				1e-3, 200e-6, 100e-6, 40e-6, 20e-6,
				10e-6, 4e-6, 2e-6, 1e-6, 500e-9
			};

			char tmp[64];
			utils::sformat("%s (%s)", tmp, sizeof(tmp)) % freq[rate_div_] % rate[rate_div_];
			render_.set_fore_color(DEF_COLOR::Black);
			render_.fill_box(vtx::srect(0, 0, 480, 16));
			render_.set_fore_color(DEF_COLOR::White);
			auto x = render_.draw_text(vtx::spos(0, 0), tmp);

			// 計測モード時結果
			if(measere_ == MEASERE::TIME) {
				float a = static_cast<float>(mes_time_size_) * GRID_SCALE * rate_f[rate_div_];
				auto_scale_(a, 'S', tmp, sizeof(tmp));
				x = render_.draw_text(vtx::spos(x + 8, 0), tmp);
				freq_scale_(1.0f / a, tmp, sizeof(tmp));
				render_.draw_text(vtx::spos(x + 8, 0), tmp);
			} else if(measere_ == MEASERE::VOLT) {
//				float a = static_cast<float>(mes_time_size_) * GRID_SCALE * rate_f[rate_div_];
//				utils::sformat("%4.3f", tmp, sizeof(tmp)) % a;
//				render_.draw_text(x + 8, 0, tmp);
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
			static const char* divs[] = {
				"0.05", "0.1", "0.25", "0.5", "1.0", "2.5", "5.0", "10.0" 
			};

			char tmp[32];
			if(ch == 0) {
				render_.set_fore_color(DEF_COLOR::Lime);
				render_.fill_box(vtx::srect(  0, 272 - 16 + 1, 15, 15));
				render_.set_fore_color(DEF_COLOR::Black);
				render_.fill_box(vtx::srect( 16, 272 - 16 + 1, 240 - 16, 15));
				render_.set_fore_color(DEF_COLOR::White);
				utils::sformat("CH0: %s [V]", tmp, sizeof(tmp)) % divs[ch0_div_];
				render_.draw_text(vtx::spos(  16, 272 - 16 + 1), tmp);
			} else {
				render_.set_fore_color(DEF_COLOR::Fuchsi);
				render_.fill_box(vtx::srect(240, 272 - 16 + 1, 15, 15));
				utils::sformat("CH1: %s [V]", tmp, sizeof(tmp)) % divs[ch1_div_];
				render_.set_fore_color(DEF_COLOR::Black);
				render_.fill_box(vtx::srect(240 + 16, 272 - 16 + 1, 240 - 16, 15));
				render_.set_fore_color(DEF_COLOR::White);
				render_.draw_text(vtx::spos(240 + 16, 272 - 16 + 1), tmp);
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
					menu_run_ = menu_;
					menu_ = MENU::NONE;
					if(menu_run_ == MENU::TRG) {
						// とりあえず、シングル・トリガー
						capture_.set_trigger(utils::capture_trigger::SINGLE);
					} else if(menu_run_ == MENU::MES) {
						measere_ = enum_utils::inc(measere_, MEASERE::NONE, MEASERE::VOLT);
					}
					return true;
				} else {
					return false;
				}
			}

			if(num == 1) {
				if(p.event == TOUCH::EVENT::DOWN) {
					time_org_ = time_pos_;
					ch0_vorg_ = ch0_vpos_;
					ch1_vorg_ = ch1_vpos_;
					mes_time_org_ = mes_time_begin_;
					mes_volt_org_ = mes_volt_begin_;
				} else if(p.event == TOUCH::EVENT::CONTACT) {
					int16_t dx = p.x - p.org_x;
					int16_t dy = p.y - p.org_y;
					if(CH1_MOVE_AREA <= p.x && p.x < RENDER::glc_type::width) {
						menu_ = static_cast<MENU>((p.y - 16) / MENU_SIZE + 1);
					} else if(measere_ == MEASERE::TIME) {
						if(TIME_BEGIN_POS <= p.y && p.y < TIME_LIMIT_POS
							&& VOLT_BEGIN_POS <= p.x && p.x < VOLT_LIMIT_POS) {
							mes_time_begin_ = mes_time_org_ + dx;
							if(mes_time_begin_ < 0) mes_time_begin_ = 0;
							else if(mes_time_begin_ >= 440) mes_time_begin_ = 440;
						}
					} else if(measere_ == MEASERE::VOLT) {
						if(TIME_BEGIN_POS <= p.y && p.y < TIME_LIMIT_POS
							&& VOLT_BEGIN_POS <= p.x && p.x < VOLT_LIMIT_POS) {
							mes_volt_begin_ = mes_volt_org_ + dy;
							if(mes_volt_begin_ < 16) mes_volt_begin_ = 16;
							else if(mes_volt_begin_ >= (272 - 16)) mes_volt_begin_ = 272 - 16 - 1;
						}
					} else {
						if(0 <= p.y && p.y < TIME_SCROLL_AREA) {
							time_pos_ = time_org_ + dx;
							touch_down_ = true;
						} else if(0 <= p.x && p.x < CH0_MOVE_AREA) {
							ch0_vpos_ = ch0_vorg_ + dy;
							touch_down_ = true;
						} else if(CH0_MOVE_AREA <= p.x && p.x < CH1_MOVE_AREA) {
							ch1_vpos_ = ch1_vorg_ + dy;
							touch_down_ = true;
						}
					}
				}
			} else if(num == 2) {
				const auto& p2 = touch_.get_touch_pos(1);
				if(measere_ == MEASERE::TIME) {
					auto dx = p.x - p2.x;
					auto dy = p.y - p2.y;
					auto len = intmath::sqrt16(dx * dx + dy * dy);
					if(p2.event == TOUCH::EVENT::DOWN) {
						mes_ref_size_ = mes_time_size_;
						mes_ref_len_  = len.val;
					} else {
						mes_time_size_ = mes_ref_size_
							+ static_cast<int16_t>(len.val) - mes_ref_len_;
						if(mes_time_size_ < 0) mes_time_size_ = 0;
					}
				} else if(measere_ == MEASERE::VOLT) {
					auto dx = p.x - p2.x;
					auto dy = p.y - p2.y;
					auto len = intmath::sqrt16(dx * dx + dy * dy);
					if(p2.event == TOUCH::EVENT::DOWN) {
						mes_ref_size_ = mes_volt_size_;
						mes_ref_len_  = len.val;
					} else {
						mes_volt_size_ = mes_ref_size_
							+ static_cast<int16_t>(len.val) - mes_ref_len_;
						if(mes_volt_size_ < 0) mes_volt_size_ = 0;
					}
				} else {

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
			draw_grid(0, 16, 440, 240, GRID);

			if(measere_ != MEASERE::NONE) {
				update_measere_();
			} else if(touch_down_) {
				render_.set_fore_color(DEF_COLOR::Red);
				render_.line(vtx::spos(0, TIME_SCROLL_AREA),
							 vtx::spos(CH1_MOVE_AREA, TIME_SCROLL_AREA));				 
				render_.line(vtx::spos(CH0_MOVE_AREA, TIME_SCROLL_AREA),
							 vtx::spos(CH0_MOVE_AREA, 272 - 16));
				render_.line(vtx::spos(CH1_MOVE_AREA, TIME_SCROLL_AREA),
							 vtx::spos(CH1_MOVE_AREA, 272 - 16));
			}

			// メニュー・ボタンの描画
			{
				static const char* menu[] = {
					"CH0", "CH1", "Trg", "Smp", "Mes", "Opt" };
				for(int16_t i = 0; i < 6; ++i) {
					auto c = DEF_COLOR::Olive;
					if(static_cast<MENU>(i + 1) == menu_) c = DEF_COLOR::Yellow;
					render_.set_back_color(c);
					dialog_.draw_button(vtx::srect(441, 16 + GRID * i + 1, GRID - 1, GRID - 1), menu[i]);
				}
			}

			for(int16_t x = 0; x < (440 - 1); ++x) {
				int16_t p0 = time_pos_ + x;
				int16_t p1 = time_pos_ + x + 1;
				if(p1 >= static_cast<int16_t>(CAPTURE::CAP_NUM)) {
					break;
				}
				const auto& d0 = capture_.get(p0);
				const auto& d1 = capture_.get(p1);
				{
					int16_t ofs = ch0_vpos_ + 272 / 2;
					int16_t y0 = d0.ch0_;
					y0 -= 2048;
					y0 /= -17;
					int16_t y1 = d1.ch0_;
					y1 -= 2048;
					y1 /= -17;
					render_.set_fore_color(DEF_COLOR::Lime);
					render_.line(vtx::spos(x, ofs + y0), vtx::spos(x + 1, ofs + y1));
				}
				{
					int16_t ofs = ch1_vpos_ + 272 / 2;
					int16_t y0 = d0.ch1_;
					y0 -= 2048;
					y0 /= -17;
					int16_t y1 = d1.ch1_;
					y1 -= 2048;
					y1 /= -17;
					render_.set_fore_color(DEF_COLOR::Fuchsi);
					render_.line(vtx::spos(x, ofs + y0), vtx::spos(x + 1, ofs + y1));
				}
			}

			draw_sampling_info();
			draw_channel_info(0);
			draw_channel_info(1);
		}
	};
}
