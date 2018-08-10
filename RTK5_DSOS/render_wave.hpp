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

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  波形描画クラス
		@param[in]	RENDER	描画クラス
		@param[in]	CAPTURE	キャプチャー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RENDER, class CAPTURE>
	class render_wave {

		RENDER&		render_;
		CAPTURE&	capture_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
			@param[in]	render	描画クラス
			@param[in]	capture	キャプチャー・クラス
		*/
		//-----------------------------------------------------------------//
		render_wave(RENDER& render, CAPTURE& capture) noexcept :
			render_(render), capture_(capture)
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
			@brief  アップ・デート
		*/
		//-----------------------------------------------------------------//
		void update() noexcept
		{
			render_.clear(RENDER::COLOR::Black);

			draw_grid(0, 16, 440, 240, 40);

			render_.fill(0, 0, 480, 16, RENDER::COLOR::Green);
			for(int16_t i = 0; i < 6; ++i) {
				render_.fill(441, 16 + 40 * i + 1, 39, 39, RENDER::COLOR::Olive);
			}
			render_.fill(0, 272 - 16 + 1, 480, 15, RENDER::COLOR::Green);

			render_.draw_text(441 + 7, 16 + 40 * 0 + 1 + 11, "CH0");
			render_.draw_text(441 + 7, 16 + 40 * 1 + 1 + 11, "CH1");
			render_.draw_text(441 + 7, 16 + 40 * 2 + 1 + 11, "Trg");
			render_.draw_text(441 + 7, 16 + 40 * 3 + 1 + 11, "Smp");
			render_.draw_text(441 + 7, 16 + 40 * 4 + 1 + 11, "Mes");
			render_.draw_text(441 + 7, 16 + 40 * 5 + 1 + 11, "Opt");

			int16_t ofs = 272 / 2;
			for(int16_t x = 0; x < (440 - 1); ++x) {
				const auto& d0 = capture_.get(x);
				const auto& d1 = capture_.get(x + 1);
				{
					int16_t y0 = d0.ch0_;
					y0 -= 2048;
					y0 /= -17;
					int16_t y1 = d1.ch0_;
					y1 -= 2048;
					y1 /= -17;
					render_.line(x, ofs + y0, x + 1, ofs + y1, RENDER::COLOR::Lime);
				}
				{
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
