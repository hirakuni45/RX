#pragma once
//=====================================================================//
/*!	@file
	@brief	フォント定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include "graphics/afont.hpp"
#include "graphics/kfont.hpp"

namespace graphics {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	フォント定義
		@param[in]	AFONT	ASCII フォント
		@param[in]	KFONT	KANJI フォント	
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class AFONT, class KFONT>
	class font {
	public:
		static const int16_t height  = KFONT::height < AFONT::height
			? AFONT::height : KFONT::height;

		typedef AFONT a_type;
		typedef KFONT k_type;

	private:
		AFONT&	afont_;
		KFONT&	kfont_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		font(AFONT& afont, KFONT& kfont) noexcept : afont_(afont), kfont_(kfont) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	アスキーフォントの参照を返す
			@return アスキーフォントの参照
		*/
		//-----------------------------------------------------------------//
		AFONT& at_afont() noexcept { return afont_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	漢字フォントの参照を返す
			@return 漢字フォントの参照
		*/
		//-----------------------------------------------------------------//
		KFONT& at_kfont() noexcept { return kfont_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	フォント幅取得 (UTF-8)
			@param[in]	cha		文字コード
			@param[in]	prop	プロポーショナルの場合「true」
			@param[in]	back	背景を描画する場合「true」
			@return 文字の幅 (X)
		*/
		//-----------------------------------------------------------------//
		int16_t get_font_size(char cha, bool prop = false, bool back = false) noexcept
		{
			int16_t w = 0;
			if(static_cast<uint8_t>(cha) < 0x80) {
				uint8_t code = static_cast<uint8_t>(cha);
				if(prop) {
					w = AFONT::get_kern(code);
					w += AFONT::get_width(code);
				} else {
					w = AFONT::width;
				}
			} else {
				if(kfont_.injection_utf8(static_cast<uint8_t>(cha))) {
					auto code = kfont_.get_utf16();
					if(code >= 0x80) {
						w = KFONT::width;
					}
				}
			}
			return w;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	テキストの描画サイズを得る
			@param[in]	text	テキスト（UTF-8）
			@param[in]	prop	プロポーショナルの場合「true」
			@return 描画サイズ
		*/
		//-----------------------------------------------------------------//
		vtx::spos get_text_size(const char* text, bool prop = false) noexcept
		{
			char cha;
			vtx::spos sz(0);
			int16_t x = 0;
			while((cha = *text++) != 0) {
				if(cha == '\n') {
					if(sz.x < x) sz.x = x;
					x = 0;
					sz.y += height;
				} else {
					// 画面外を指定してサイズだけ取得
					x += get_font_size(cha, prop);
				}
			}
			if(sz.x < x) sz.x = x;
			if(sz.y == 0) sz.y = height;
			else if(x > 0) sz.y += height;
			return sz;
		}
	};

	typedef font<afont_null, kfont_null> font_null;
}
