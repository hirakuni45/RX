#pragma once
//=====================================================================//
/*!	@file
	@brief	TGA 画像ファイルを扱うクラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include "common/file_io.hpp"
#include "common/vtx.hpp"
#include "graphics/img.hpp"

namespace img {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	TGA 形式ファイルクラス
		@param[in]	PLOT	描画ファンクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class PLOT>
	class tga_in {

		PLOT&		plot_;

		struct tga_t {
			static const uint32_t HEADER_SIZE = 18;

			typedef std::vector<rgba8>	clut_type;

			struct tga_info {
				uint8_t		id_length;	// image id length
				uint8_t		clut_t;		// CLUT type
				uint8_t		image_t;	// image type
				uint16_t	clut_first;	// index of first CLUT entry
				uint16_t	clut_num;	// number of entries in CLUT
				uint8_t		clut_depth;	// depth of CLUT
				uint16_t	x;			// x-coordinate
				uint16_t	y;			// y-coordinate
				uint16_t	w;			// width of image
				uint16_t	h;			// height of image
				uint8_t		depth;		// pixel-depth of image
				uint8_t		alpha;		// alpha bits
				bool		h_flip;		// horizontal orientation
				bool		v_flip;		// vertical orientation

				tga_info() noexcept : id_length(0),
					clut_t(0), image_t(0),
					clut_first(0), clut_num(0), clut_depth(0),
					x(0), y(0), w(0), h(0), depth(0), alpha(0),
					h_flip(false), v_flip(false) { }

				bool get(utils::file_io& fio) noexcept {
					uint8_t t[HEADER_SIZE];
					if(fio.read(t, HEADER_SIZE) != HEADER_SIZE) {
						return false;
					}
					id_length = t[0];
					clut_t    = t[1];
					image_t   = t[2];
					clut_first = t[3] | (t[4] << 8);
					clut_num   = t[5] | (t[6] << 8);
					clut_depth = t[7];
					x = t[ 8] | (t[ 9] << 8);
					y = t[10] | (t[11] << 8);
					w = t[12] | (t[13] << 8);
					h = t[14] | (t[15] << 8);
					depth = t[16];
					alpha = t[17] & 0x0f;
					h_flip = (t[17] & 0x10) ? true : false;
					v_flip = (t[17] & 0x20) ? false : true;

					return true;
				}

				bool put(utils::file_io& fio) noexcept {
					uint8_t t[HEADER_SIZE];
					t[0] = id_length;
					t[1] = clut_t;
					t[2] = image_t;
					t[3] = clut_first; t[4] = clut_first >> 8;
					t[5] = clut_num; t[6] = clut_num >> 8;
					t[7] = clut_depth;
					t[8] = x; t[9] = x >> 8;
					t[10] = y; t[11] = y >> 8;
					t[12] = w; t[13] = w >> 8;
					t[14] = h; t[15] = h >> 8;
					t[16] = depth; 
					t[17] = alpha | (h_flip << 4) | (v_flip << 5);

					if(fio.write(t, HEADER_SIZE) != HEADER_SIZE) {
						return false;
					}
					return true;
				}
			};


			bool read_info_(img::img_info& fo) noexcept
			{
				if(!fio_.seek(utils::file_io::SEEK::SET, offset_)) {
					return false;
				}

				if(!info_.get(fio_)) {
					return false;
				}

				// Indexed color
				if(info_.clut_t == 0) ;
				else if(info_.clut_t == 1) {
					fo.i_depth  = info_.depth;
					fo.clut_num = info_.clut_num;
					if(info_.clut_depth == 15) {
						fo.r_depth = 5;
						fo.g_depth = 5;
						fo.b_depth = 5;
						fo.a_depth = 0;
					} else if(info_.clut_depth == 16) {
						fo.r_depth = 5;
						fo.g_depth = 6;
						fo.b_depth = 5;
						fo.a_depth = 0;
					} else if(info_.clut_depth == 24) {
						fo.r_depth = 8;
						fo.g_depth = 8;
						fo.b_depth = 8;
						fo.a_depth = 0;
					} else if(info_.clut_depth == 32) {
						fo.r_depth = 8;
						fo.g_depth = 8;
						fo.b_depth = 8;
						fo.a_depth = 8;
					} else {
						return false;
					}
					fo.grayscale = false;
				} else {
					return false;
				}

				if(info_.image_t == 1 || info_.image_t == 9) ;
				else if(info_.image_t == 2 || info_.image_t == 10) {
					if(info_.depth == 24) {
						fo.r_depth = 8;
						fo.g_depth = 8;
						fo.b_depth = 8;
						fo.a_depth = 0;
					} else if(info_.depth == 32) {
						fo.r_depth = 8;
						fo.g_depth = 8;
						fo.b_depth = 8;
						fo.a_depth = 8;
					}
					fo.i_depth = 0;
					fo.clut_num = 0;
					fo.grayscale = false;
				} else if(info_.image_t == 3 || info_.image_t == 11) {
					fo.r_depth = 0;
					fo.g_depth = 0;
					fo.b_depth = 0;
					fo.a_depth = info_.alpha;
					fo.i_depth = info_.depth;
					fo.clut_num = 0;
					fo.grayscale = true;
				} else {
					return false;
				}

				fo.width  = info_.w;
				fo.height = info_.h;
				fo.mipmap_level = 0;
				fo.multi_level  = 0;

				rle_ = (info_.image_t & 0x08) ? true : false;

				return true;
			}
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	plot	描画ファンクタ
		*/
		//-----------------------------------------------------------------//
		tga_in(PLOT& plot) noexcept : plot_(plot)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	ファイル拡張子を返す
			@return ファイル拡張子の文字列
		*/
		//-----------------------------------------------------------------//
		const char* get_file_ext() const noexcept { return "tga"; }


		//-----------------------------------------------------------------//
		/*!
			@brief	BMP ファイルか確認する
			@param[in]	fin	file_io クラス
			@return エラーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool probe(utils::file_io& fin) noexcept
		{
			img::img_info fo;
			return info(fin, fo);
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
			auto org = fin.tell();

			tga_t tga_(fin);
			bool f = tga_.read_info(fo);

			fin.seek(utils::file_io::SEEK::SET, org);

			return f;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	BMP ファイルをロードする
			@param[in]	fin	ファイル I/O クラス
			@param[in]	opt	フォーマット固有の設定文字列
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool load(utils::file_io& fin, const char* opt = nullptr) noexcept
		{
			tga_t tga_(fin);

			img::img_info fo;
			if(!tga_.read_info(fo)) {
				return false;
			}

			prgl_pos_ = 0;
			prgl_ref_ = fo.height;

			bool alpha = false;
			if(fo.a_depth) alpha = true;

			if(fo.clut_num) {
				tga::clut_type clut;
				if(!tga_.read_clut(clut)) {
					return false;
				}

				img_ = shared_img(new img_idx8);
				img_->create(vtx::spos(fo.width, fo.height), alpha);

				for(int i = 0; i < fo.clut_num; ++i) {
					img_->put_clut(i, clut[i]);
				}

				if(!tga_.decode(img_, prgl_pos_)) {
					return false;
				}

			} else {
				img_ = shared_img(new img_rgba8);
				img_->create(vtx::spos(fo.width, fo.height), alpha);

				if(!tga_.decode(img_, prgl_pos_)) {
					return false;
				}
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	BMP ファイルをロードする
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
