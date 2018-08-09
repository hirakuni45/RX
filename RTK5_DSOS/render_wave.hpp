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
			@brief  アップ・デート
		*/
		//-----------------------------------------------------------------//
		void update() noexcept
		{
			int16_t ofs = 272 / 2;
			for(int16_t x = 0; x < (RENDER::width - 1); ++x) {
				const auto& d0 = capture_.get(x);
				int16_t y0 = d0.ch0_;
				y0 -= 2048;
				y0 /= -15;
				const auto& d1 = capture_.get(x + 1);
				int16_t y1 = d1.ch0_;
				y1 -= 2048;
				y1 /= -15;
				render_.line(x, ofs + y0, x + 1, ofs + y1, 0xffff);  
			}
		}
	};
}
