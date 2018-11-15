#pragma once
//=====================================================================//
/*!	@file
	@brief	PicoJPEG クラス @n
			picojpeg.[hc] の C++ ラッパー @n
			https://github.com/richgel999/picojpeg を参照
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/glfw3_app/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdio>
#include <cstdlib>
#include "graphics/img.hpp"
#include "graphics/picojpeg.h"
#include "common/file_io.hpp"
#include "common/format.hpp"

namespace img {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	PicoJPEG デコード・クラス
		@param[in]	PLOT	描画ファンクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class PLOT>
	class picojpeg_in {

		PLOT&		plot_;

		pjpeg_image_info_t	image_info_;

		uint8_t		status_;
		bool		reduce_;

		int16_t		width_;
		int16_t		height_;

		struct data_t {
			utils::file_io&	fin_;
			uint32_t		file_ofs_;
			uint32_t		file_size_;
			data_t(utils::file_io& fin) : fin_(fin), file_ofs_(0), file_size_(0) { }
		};


		static uint8_t pjpeg_callback_(uint8_t* dst, uint8_t size, uint8_t* acr, void *pdata)
		{
			data_t* t = static_cast<data_t*>(pdata);
			auto len = std::min(t->file_size_ - t->file_ofs_, static_cast<uint32_t>(size));
			auto rl = t->fin_.read(dst, len);
			// utils::format("Read: %d (%d)\n") % len % rl;
			*acr = rl;
			t->file_ofs_ += rl;
			return 0;
		}


		bool pixel_(utils::file_io& fin) noexcept
		{
			int16_t xt = 0;
			int16_t yt = 0;
			while((status_ = pjpeg_decode_mcu()) == 0) {

				if(reduce_) {
					auto row_blocks = image_info_.m_MCUWidth  >> 3;
					auto col_blocks = image_info_.m_MCUHeight >> 3;
					int16_t xx = xt * row_blocks;
					int16_t yy = yt * col_blocks;
					if(image_info_.m_scanType == PJPG_GRAYSCALE) {
						auto gs = image_info_.m_pMCUBufR[0];
						plot_(xx, yy, gs, gs, gs);
					} else {
						for(int16_t y = 0; y < col_blocks; ++y) {
							auto ofs = y * 128;
							for(int16_t x = 0; x < row_blocks; ++x) {
								auto r = image_info_.m_pMCUBufR[ofs];
								auto g = image_info_.m_pMCUBufG[ofs];
								auto b = image_info_.m_pMCUBufB[ofs];
								ofs += 64;
								plot_(xx + x, yy + y, r, g, b);
							}
						}
					}
				} else {
					auto xx = xt * image_info_.m_MCUWidth;
					auto yy = yt * image_info_.m_MCUHeight;
					for(int16_t y = 0; y < image_info_.m_MCUHeight; y += 8) {
						auto by_limit = std::min(8,
							image_info_.m_height - (yt * image_info_.m_MCUHeight + y));
						for(int16_t x = 0; x < image_info_.m_MCUWidth; x += 8) {
							auto bx_limit = std::min(8,
								image_info_.m_width - (xt * image_info_.m_MCUWidth + x));
							auto ofs = (x * 8) + (y * 16);
							if(image_info_.m_scanType == PJPG_GRAYSCALE) {
								const uint8_t* pGS = image_info_.m_pMCUBufR + ofs;
								for(int16_t by = 0; by < by_limit; ++by) {
									for(int16_t bx = 0; bx < bx_limit; ++bx) {
										auto gs = *pGS++;
										plot_(x + xx + bx, y + yy + by, gs, gs, gs);
									}
									pGS += (8 - bx_limit);
								}
							} else {
								const uint8_t* pR = image_info_.m_pMCUBufR + ofs;
								const uint8_t* pG = image_info_.m_pMCUBufG + ofs;
								const uint8_t* pB = image_info_.m_pMCUBufB + ofs;
								for(int16_t by = 0; by < by_limit; ++by) {
									for(int16_t bx = 0; bx < bx_limit; ++bx) {
										auto r = *pR++; 
										auto g = *pG++; 
										auto b = *pB++;
										plot_(x + xx + bx, y + yy + by, r, g, b);
									}
									pR += (8 - bx_limit);
									pG += (8 - bx_limit);
									pB += (8 - bx_limit);
								}
							}
						}
					}
				}
				++xt;
				if(xt >= image_info_.m_MCUSPerRow) {
					xt = 0;
					++yt;
///					if(yt >= image_info_.m_MCUSPerCol) {
///						break;
///					}
				}
			}
			if(status_ != PJPG_NO_MORE_BLOCKS) {
				utils::format("pjpeg_decode_mcu() failed with status: %d\n") % status_;
				return false;
			}
			return true;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	plot	描画ファンクタ
		*/
		//-----------------------------------------------------------------//
		picojpeg_in(PLOT& plot) noexcept : plot_(plot),
			image_info_(),
			status_(0), reduce_(false),
			width_(0), height_(0)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	ステータスの取得（Error code）
			@return ステータス
		*/
		//-----------------------------------------------------------------//
		uint8_t get_status() const noexcept { return status_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	JPEG ファイルか確認する
			@param[in]	fin	file_io クラス
			@return エラーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool probe(utils::file_io& fin) noexcept
		{
			uint8_t sig[2];
			uint32_t pos = fin.tell();
			uint32_t l = fin.read(sig, 2);
			fin.seek(utils::file_io::SEEK::SET, pos);
			if(l == 2) {
				if(sig[0] == 0xff && sig[1] == 0xd8) {  // SOI Marker, Start image
					return true;
				}
			}
			utils::format("JPEG SOI Marker fail: %02X, %02X\n")
				% static_cast<uint16_t>(sig[0]) % static_cast<uint16_t>(sig[1]);
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
			auto pos = fin.tell();

			data_t t(fin);
			t.file_ofs_  = 0;
			t.file_size_ = fin.get_file_size();
			status_ = pjpeg_decode_init(&image_info_, pjpeg_callback_, &t, false);

			fin.seek(utils::file_io::SEEK::SET, pos);

			if(status_ != 0) {
				return false;
			}

			fo.width  = image_info_.m_width;
			fo.height = image_info_.m_height;
			switch(image_info_.m_comps) {
			case 1:
				fo.grayscale = true;
				fo.i_depth = 0;
				fo.r_depth = 8;
				fo.g_depth = 8;
				fo.b_depth = 8;
				fo.a_depth = 0;
				fo.clut_num = 0;
				break;
			case 3:
				fo.grayscale = false;
				fo.i_depth = 0;
				fo.r_depth = 8;
				fo.g_depth = 8;
				fo.b_depth = 8;
				fo.a_depth = 0;
				fo.clut_num = 0;
				break;
			case 4:
				fo.grayscale = false;
				fo.i_depth = 0;
				fo.r_depth = 8;
				fo.g_depth = 8;
				fo.b_depth = 8;
				fo.a_depth = 8;
				fo.clut_num = 0;
				break;
			default:
				fo.i_depth = 0;
				fo.r_depth = 0;
				fo.g_depth = 0;
				fo.b_depth = 0;
				fo.a_depth = 0;
				fo.clut_num = 0;
				return false;
				break;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	JPEG ファイル、ロード
			@param[in]	fin	file_io クラス
			@param[in]	opt	フォーマット固有の設定文字列
			@return エラーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool load(utils::file_io& fin, const char* opt = nullptr)
		{
			// とりあえず、ヘッダーの検査
			if(!probe(fin)) {
				return false;
			}

			reduce_ = false;

			data_t t(fin);
			t.file_ofs_  = 0;
			t.file_size_ = fin.get_file_size();
			status_ = pjpeg_decode_init(&image_info_, pjpeg_callback_, &t, reduce_);
			if(status_) {
				if(status_ == PJPG_UNSUPPORTED_MODE) {
					utils::format("Progressive JPEG files are not supported.\n");
				} else {
//					utils::format("pjpeg_decode_init() failed with status: %d\n") % status_;
				}
				return false;
			}

			// In reduce mode output 1 pixel per 8x8 block.
			width_  = reduce_ ?
				(image_info_.m_MCUSPerRow * image_info_.m_MCUWidth)  / 8 : image_info_.m_width;
			height_ = reduce_ ?
				(image_info_.m_MCUSPerCol * image_info_.m_MCUHeight) / 8 : image_info_.m_height;

			return pixel_(fin);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	JPEG ファイルをロードする
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
