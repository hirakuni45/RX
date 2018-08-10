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

		static const int16_t GRID = 40;

		RENDER&		render_;
		CAPTURE&	capture_;
		TOUCH&		touch_;

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

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
			@param[in]	render	描画クラス
			@param[in]	capture	キャプチャー・クラス
		*/
		//-----------------------------------------------------------------//
		render_wave(RENDER& render, CAPTURE& capture, TOUCH& touch) noexcept :
			render_(render), capture_(capture), touch_(touch),
			ch0_vpos_(0), ch0_vorg_(0), ch1_vpos_(0), ch1_vorg_(0),
			rate_div_(11), ch0_div_(3), ch1_div_(3)
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
			for(int16_t i = x; i <= (x + w); i += unit) {
				uint32_t mask;
				if(i == x || i == (x + w)) {
					mask = -1;
				} else {
					mask = 0b11000000110000001100000011000000;
				}
				render_.set_stipple(mask);
				render_.line(i, y, i, y + h, RENDER::COLOR::Aqua);
			}
			for(int16_t i = y; i <= (y + h); i += unit) {
				uint32_t mask;
				if(i == y || i == (y + h)) {
					mask = -1;
				} else {
					mask = 0b11000000110000001100000011000000;
				}
				render_.set_stipple(mask);
				render_.line(x, i, x + w, i, RENDER::COLOR::Aqua);
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

			char tmp[64];
			utils::sformat("%s (%s)", tmp, sizeof(tmp)) % freq[rate_div_] % rate[rate_div_];
			render_.draw_text(0, 0, tmp);
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
				render_.fill(  0, 272 - 16 + 1, 15, 15, RENDER::COLOR::Lime);
				utils::sformat("CH0: %s [V]", tmp, sizeof(tmp)) % divs[ch0_div_];
				render_.draw_text(  16, 272 - 16 + 1, tmp);
			} else {
				render_.fill(240, 272 - 16 + 1, 15, 15, RENDER::COLOR::Fuchsi);
				utils::sformat("CH1: %s [V]", tmp, sizeof(tmp)) % divs[ch1_div_];
				render_.draw_text(240 + 16, 272 - 16 + 1, tmp);
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
			if(num == 0) return false;

			if(num == 1) {
				const auto& p = touch_.get_touch_pos(0);
				if(p.event == TOUCH::EVENT::DOWN) {
					ch0_vorg_ = ch0_vpos_;
					ch1_vorg_ = ch1_vpos_;
				} else if(p.event == TOUCH::EVENT::CONTACT) {
					int16_t dx = p.x - p.org_x;
					int16_t dy = p.y - p.org_y;
					if(0 <= p.x && p.x < 220) {
						ch0_vpos_ = ch0_vorg_ + dy;
					} else if(220 <= p.x && p.x < 440) {
						ch1_vpos_ = ch1_vorg_ + dy;
					}
				}
			} else if(num == 2) {
return false;
			} else {
return false;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  アップ・デート
		*/
		//-----------------------------------------------------------------//
		void update() noexcept
		{
			render_.clear(RENDER::COLOR::Black);

			draw_grid(0, 16, 440, 240, GRID);

			draw_sampling_info();

			for(int16_t i = 0; i < 6; ++i) {
				render_.fill(441, 16 + GRID * i + 1, GRID - 1, GRID - 1, RENDER::COLOR::Olive);
			}

			render_.draw_text(441 + 7, 16 + GRID * 0 + 1 + 11, "CH0");
			render_.draw_text(441 + 7, 16 + GRID * 1 + 1 + 11, "CH1");
			render_.draw_text(441 + 7, 16 + GRID * 2 + 1 + 11, "Trg");
			render_.draw_text(441 + 7, 16 + GRID * 3 + 1 + 11, "Smp");
			render_.draw_text(441 + 7, 16 + GRID * 4 + 1 + 11, "Mes");
			render_.draw_text(441 + 7, 16 + GRID * 5 + 1 + 11, "Opt");

			draw_channel_info(0);
			draw_channel_info(1);

			for(int16_t x = 0; x < (440 - 1); ++x) {
				const auto& d0 = capture_.get(x);
				const auto& d1 = capture_.get(x + 1);
				{
					int16_t ofs = ch0_vpos_ + 272 / 2;
					int16_t y0 = d0.ch0_;
					y0 -= 2048;
					y0 /= -17;
					int16_t y1 = d1.ch0_;
					y1 -= 2048;
					y1 /= -17;
					render_.line(x, ofs + y0, x + 1, ofs + y1, RENDER::COLOR::Lime);
				}
				{
					int16_t ofs = ch1_vpos_ + 272 / 2;
					int16_t y0 = d0.ch1_;
					y0 -= 2048;
					y0 /= -17;
					int16_t y1 = d1.ch1_;
					y1 -= 2048;
					y1 /= -17;
					render_.line(x, ofs + y0, x + 1, ofs + y1, RENDER::COLOR::Fuchsi);
				}
			}
		}
	};
}
