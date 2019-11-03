#pragma once
//=====================================================================//
/*!	@file
	@brief	PNG クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/glfw3_app/blob/master/LICENSE
*/
//=====================================================================//
#include "graphics/img.hpp"
#include "graphics/color.hpp"
#include "common/file_io.hpp"
#include "common/format.hpp"

#include "common/time.h"
#include "libpng/png.h"

namespace img {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	PicoJPEG デコード・クラス
		@param[in]	PLOT	描画ファンクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class PLOT>
	class png_in {

		PLOT&		plot_;

        bool        color_key_enable_;

        uint32_t    prgl_ref_;
        uint32_t    prgl_pos_;

	    static void read_func_(png_structp png_ptr, png_bytep buf, png_size_t size) {
        	utils::file_io* fin = (utils::file_io*)png_get_io_ptr(png_ptr);

        	size_t s = fin->read(buf, 1, size);
        	if(s != size) {
				char tmp[128];
				utils::sformat("png_io_read_func: error (read size: %d, request: %d)", tmp, sizeof(tmp))
                	% static_cast<int>(s) % static_cast<int>(size);
            	png_error(png_ptr, tmp);
        	}
    	}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	plot	描画ファンクタ
		*/
		//-----------------------------------------------------------------//
		png_in(PLOT& plot) noexcept : plot_(plot),
			color_key_enable_(false), prgl_ref_(0), prgl_pos_(0)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	ファイル拡張子を返す
			@return ファイル拡張子の文字列
		*/
		//-----------------------------------------------------------------//
		const char* get_file_ext() const noexcept { return "png"; }


		//-----------------------------------------------------------------//
		/*!
			@brief	PNG ファイルか確認する
			@param[in]	fin	file_io クラス
			@return エラーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool probe(utils::file_io& fin) noexcept
		{
			static const int PNG_BYTES_TO_CHECK = 4;
			uint8_t sig[PNG_BYTES_TO_CHECK];

			auto ofs = fin.tell();
			auto len = fin.read(sig, PNG_BYTES_TO_CHECK);
			fin.seek(utils::file_io::SEEK::SET, ofs);
			if(len == PNG_BYTES_TO_CHECK) {
				if(png_check_sig(sig, PNG_BYTES_TO_CHECK)) {
					return true;
				}
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	画像ファイルの情報を取得する
			@param[in]	fin	file_io クラス
			@param[in]	fo	情報を受け取る構造体
			@return エラーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool info(utils::file_io& fin, img::img_info& fo) noexcept
		{
			auto ofs = fin.tell();

			if(probe(fin) == false) {
				fin.seek(utils::file_io::SEEK::SET, ofs);
				return false;
			}

			//	png_ptr 構造体を確保・初期化します
			png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
			if(png_ptr == NULL) {
				fin.seek(utils::file_io::SEEK::SET, ofs);
				return false;
			}
			//  info_ptr 構造体を確保・初期化します
			png_infop info_ptr = png_create_info_struct(png_ptr);
			if(info_ptr == NULL) {
				fin.seek(utils::file_io::SEEK::SET, ofs);
				return false;
			}

			png_set_read_fn(png_ptr, (png_voidp)&fin, read_func_);
			png_read_info(png_ptr, info_ptr);

			//  IHDRチャンク情報を取得します
			png_uint_32	width, height;
			int bit_depth;
			int color_type;
			int interlace_type;
			png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, NULL, NULL);
			fo.width  = width;
			fo.height = height;
//			fo.mipmap_level = 0;
//			fo.multi_level = 0;
			fo.grayscale = false;

			fo.r_depth = bit_depth;
			fo.g_depth = bit_depth;
			fo.b_depth = bit_depth;
			fo.a_depth = 0;
			if(color_type & PNG_COLOR_MASK_PALETTE) {
				fo.i_depth = bit_depth;
				png_bytep ta;
				int nt;
				png_color_16p tc;
				png_get_tRNS(png_ptr, info_ptr, &ta, &nt, &tc);
				if(nt) fo.a_depth = bit_depth;
			} else {
				fo.i_depth = 0;
				if(color_type & PNG_COLOR_MASK_ALPHA) {
					fo.a_depth = bit_depth;
				}
			}

			png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);

			fin.seek(utils::file_io::SEEK::SET, ofs);

			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	PNG ファイル、ロード
			@param[in]	fin	file_io クラス
			@param[in]	opt	フォーマット固有の設定文字列
			@return エラーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool load(utils::file_io& fin, const char* opt = nullptr)
		{
			if(probe(fin) == false) {
				return false;
			}

			//	png_ptr 構造体を確保・初期化します
			png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
			if(png_ptr == NULL) {
				return false;
			}
			//  info_ptr 構造体を確保・初期化します
			png_infop info_ptr = png_create_info_struct(png_ptr);
			if(info_ptr == NULL) {
				return false;
			}

			png_set_read_fn(png_ptr, (png_voidp)&fin, read_func_);
			png_read_info(png_ptr, info_ptr);

			//  IHDRチャンク情報を取得します
			png_uint_32	width, height;
			int bit_depth;
			int color_type;
			int interlace_type;
			int comp_type;
			int filter_type;
			png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
				&interlace_type, &comp_type, &filter_type);

// フィルタータイプの取得
//			png_read_update_info(png_ptr, info_ptr);
//			png_byte ft = png_get_filter_type(png_ptr, info_ptr);
///			std::cout << "Compression: " << comp_type << std::endl;
///			std::cout << "Filter: " << filter_type << std::endl;

			prgl_ref_ = height;
			prgl_pos_ = 0;

			int ch;
			bool alpha;
			bool gray = false;
			bool indexed = false;
   			png_bytep ta = nullptr;
		   	int nt = 0;
		   	png_color_16p tc = 0;
			if(color_type == PNG_COLOR_TYPE_GRAY) {
				ch = 4;
				gray = true;
				alpha = false;
///				img_ = shared_img(new img_rgba8);
///				img_->create(vtx::spos(width, height), alpha);
			} else if(color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
				ch = 4;
				gray = true;
				alpha = true;
///				img_ = shared_img(new img_rgba8);
///				img_->create(vtx::spos(width, height), alpha);
			} else if(color_type & PNG_COLOR_MASK_PALETTE) {
				ch = 1;
				png_get_tRNS(png_ptr, info_ptr, &ta, &nt, &tc);
				if(nt) alpha = true; else alpha = false;
				indexed = true;
///				img_ = shared_img(new img_idx8);
///				img_->create(vtx::spos(width, height), alpha);
			} else if(color_type & PNG_COLOR_MASK_ALPHA) {
				ch = 4;
				alpha = true;
///				img_ = shared_img(new img_rgba8);
///				img_->create(vtx::spos(width, height), alpha);
			} else {
				ch = 3;
				alpha = false;
///				img_ = shared_img(new img_rgba8);
///				img_->create(vtx::spos(width, height), alpha);
			}

			uint32_t skip = 1;
			if(bit_depth > 8) {
				skip = 2;
			}

			png_colorp clut_ptr;
			int clut_num = 0;
			if(indexed) {  // カラーパレットの読み込み
				png_get_PLTE(png_ptr, info_ptr, &clut_ptr, &clut_num);
//				for(int i = 0; i < num; ++i) {
//					uint8_t a = 255;
//					if(ta && i < nt) { // アルファチャネル
//						a = ta[i];
//					}
//					const png_color* clut = &pal[i];
///					rgba8 c(clut->red, clut->green, clut->blue, a);
///					img_->put_clut(i, c);
//				}
			}

			png_byte* iml = new png_byte[width * ch * skip];
			vtx::spos pos;
			for(pos.y = 0; pos.y < static_cast<int16_t>(height); ++pos.y) {
				png_read_row(png_ptr, iml, nullptr);
				png_byte* p = iml;
				for(pos.x = 0; pos.x < static_cast<int16_t>(width); ++pos.x) {
					graphics::rgba8_t c;
					if(indexed) {
						uint8_t i = *p;
						p += skip;
						if(i < clut_num) {
							const png_color* clut = &clut_ptr[i];
							uint8_t a = 255;
							if(alpha) {
								a = ta[i];
							}
							plot_(pos.x, pos.y, clut->red, clut->green, clut->blue, a);
						}
					} else {
						if(gray) {
							c.r = c.g = c.b = *p;
							p += skip;
							if(alpha) { c.a = *p; p += skip; }
							else c.a = 255;
						} else {
							c.r = *p;
							p += skip;
							c.g = *p;
							p += skip;
							c.b = *p;
							p += skip;
							if(alpha) { c.a = *p; p += skip; }
							else c.a = 255;
						}
						if(color_key_enable_) {
							png_bytep ta;
							int nt;
							png_color_16p tc;
							png_get_tRNS(png_ptr, info_ptr, &ta, &nt, &tc);
							if(static_cast<unsigned short>(c.r) == tc->red
							   && static_cast<unsigned short>(c.g) == tc->green
							   && static_cast<unsigned short>(c.b) == tc->blue) {
								c.a = 0;
							}
						}
						plot_(pos.x, pos.y, c.r, c.g, c.b, c.a);
					}
				}
				prgl_pos_ = pos.y;
			}
			delete[] iml;

			png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);

			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	PNG ファイルをロードする
			@param[in]	fin	ファイル I/O クラス
			@param[in]	opt	フォーマット固有の設定文字列
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool load(const char* fname, const char* opt = nullptr) noexcept
		{
			if(fname == nullptr) return false;

			utils::file_io fin;
			if(!fin.open(fname, "rb")) {
				return false;
			}
			auto ret = load(fin, opt);
			fin.close();
			return ret;
		}
	};
}
