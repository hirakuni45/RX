#pragma once
//=====================================================================//
/*! @file
    @brief  描画ベースクラス
    @author 平松邦仁 (hira@rvf-rc45.net)
    @copyright  Copyright (C) 2020 Kunihito Hiramatsu @n
                Released under the MIT license @n
                https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "graphics/color.hpp"

namespace dsos {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  波形描画ベース・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct render_base {

		typedef graphics::def_color DEF_COLOR;

		const graphics::share_color&	CH0_COLOR;
		const graphics::share_color&	CH1_COLOR;
		const graphics::share_color&	TRG_COLOR;

		render_base() noexcept :
			CH0_COLOR(DEF_COLOR::Yellow),
			CH1_COLOR(DEF_COLOR::Fuchsi),
			TRG_COLOR(DEF_COLOR::Orange)
		{ }
	};
}
