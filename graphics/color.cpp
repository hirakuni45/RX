//=====================================================================//
/*!	@file
	@brief	グラフィックス・カラー定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "graphics/color.hpp"

namespace graphics {
	share_color const def_color::Black   = { 0, 0, 0 };
	share_color const def_color::Maroon  = { 128,   0,   0 };
	share_color const def_color::Green   = {   0, 128,   0 };
	share_color const def_color::Olive   = { 128, 128,   0 };
	share_color const def_color::Navy    = {   0,   0, 128 };
	share_color const def_color::Purple  = { 128,   0, 128 };
	share_color const def_color::Teal    = {   0, 128, 128 };
	share_color const def_color::Silver  = { 192, 192, 192 };
	share_color const def_color::Gray    = { 128, 128, 128 };  // 米国
	share_color const def_color::Grey    = { 128, 128, 128 };  // 英国
	share_color const def_color::Midgray = {  96,  96,  96 };
	share_color const def_color::Darkgray= {  64,  64,  64 };
	share_color const def_color::Red     = { 255,   0,   0 };
	share_color const def_color::Lime    = {   0, 255,   0 };
	share_color const def_color::Yellow  = { 255, 255,   0 };
	share_color const def_color::Blue    = {   0,   0, 255 };
	share_color const def_color::Fuchsi  = { 255,   0, 255 };  // 赤紫色
	share_color const def_color::Aqua    = {   0, 255, 255 };
	share_color const def_color::White   = { 255, 255, 255 };

	share_color const def_color::Orange       = { 255, 165,   0 };  // オレンジ
	share_color const def_color::SafeColor    = {  51, 204, 255 };  // セーフカラー（水色）
	share_color const def_color::EmeraldGreen = {   0, 164, 116 };
	share_color const def_color::LightPink    = { 255, 182, 193 };
}
