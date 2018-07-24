#pragma once
//=====================================================================//
/*!	@file
	@brief	JPEG 画像クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/glfw3_app/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdio>
#include <cstdlib>
extern "C" {
#include <jpeglib.h>
#include <jerror.h>
};
#include "common/file_io.hpp"
#include "common/format.hpp"

extern "C" { void gr_plot(int16_t x, int16_t y, uint8_t r, uint8_t g, uint8_t b); };

namespace img {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	JPEG 画像クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class jpeg_in {

		int		error_code_;

		static const uint32_t INPUT_BUF_SIZE = 4096;

		struct fio_src_mgr {
			struct jpeg_source_mgr	pub;		// public fields

			utils::file_io*	infile;				// source stream

			JOCTET*			buffer;
			bool			start_of_file;
			bool			err_empty;
			bool			wrn_eof;
		};

		typedef fio_src_mgr* fio_src_ptr;

		METHODDEF(void) init_source_(j_decompress_ptr cinfo)
		{
			fio_src_ptr src = (fio_src_ptr) cinfo->src;

			/* We reset the empty-input-file flag for each image,
			 * but we don't clear the input buffer.
			 * This is correct behavior for reading a series of images from one source.
			 */
			src->start_of_file = true;

			src->err_empty = false;
			src->wrn_eof = false;
		}


		METHODDEF(boolean) fill_input_buffer_(j_decompress_ptr cinfo)
		{
			fio_src_ptr src = (fio_src_ptr)cinfo->src;

			uint32_t nbytes = src->infile->read(src->buffer, INPUT_BUF_SIZE);

			if(nbytes == 0) {
				if(src->start_of_file) {
					// Treat empty input file as fatal error
//					ERREXIT(cinfo, JERR_INPUT_EMPTY);
					src->err_empty = true;
				}
//				WARNMS(cinfo, JWRN_JPEG_EOF);
				src->wrn_eof = true;

				// Insert a fake EOI marker
				src->buffer[0] = (JOCTET) 0xFF;
				src->buffer[1] = (JOCTET) JPEG_EOI;
				nbytes = 2;
			}

			src->pub.next_input_byte = src->buffer;
			src->pub.bytes_in_buffer = nbytes;
			src->start_of_file = false;

			return TRUE;
		}


		METHODDEF(void) skip_input_data_(j_decompress_ptr cinfo, long num_bytes)
		{
			fio_src_ptr src = (fio_src_ptr)cinfo->src;

			/* Just a dumb implementation for now.  Could use fseek() except
			 * it doesn't work on pipes.  Not clear that being smart is worth
			 * any trouble anyway --- large skips are infrequent.
			 */
			if(num_bytes > 0) {
				while(num_bytes > (long) src->pub.bytes_in_buffer) {
					num_bytes -= (long) src->pub.bytes_in_buffer;
					(void)fill_input_buffer_(cinfo);
					/* note we assume that fill_input_buffer will never return FALSE,
					 * so suspension need not be handled.
					 */
				}
				src->pub.next_input_byte += (size_t) num_bytes;
				src->pub.bytes_in_buffer -= (size_t) num_bytes;
			}
		}


		METHODDEF(void) term_source_(j_decompress_ptr cinfo)
		{
		}


		GLOBAL(void) fio_jpeg_file_io_src_(j_decompress_ptr cinfo, utils::file_io* infile)
		{
			if(cinfo->src == NULL) {	/* first time for this JPEG object? */
				cinfo->src = (struct jpeg_source_mgr *)
					(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
					sizeof(fio_src_mgr));
				fio_src_ptr src = (fio_src_ptr) cinfo->src;
				src->buffer = (JOCTET *)
				(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
					INPUT_BUF_SIZE * sizeof(JOCTET));
			}

			fio_src_ptr src = (fio_src_ptr) cinfo->src;
			src->pub.init_source		= init_source_;
			src->pub.fill_input_buffer	= fill_input_buffer_;
			src->pub.skip_input_data	= skip_input_data_;
			src->pub.resync_to_restart	= jpeg_resync_to_restart;	// use default method
			src->pub.term_source		= term_source_;
			src->infile					= infile;
			src->pub.bytes_in_buffer = 0;		// forces fill_input_buffer on first read
			src->pub.next_input_byte = NULL;	// until buffer loaded
		}


		METHODDEF(void) error_exit_task_(jpeg_common_struct *st)
		{
///			error_code_ = 1;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		jpeg_in() { }


		//-----------------------------------------------------------------//
		/*!
			@brief	JPEG ファイルか確認する
			@param[in]	fin	file_io クラス
			@return エラーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool probe(utils::file_io& fin)
		{
			uint8_t sig[2];
			uint32_t pos = fin.tell();
			uint32_t l = fin.read(sig, 2);
			fin.seek(utils::file_io::SEEK::SET, pos);
			if(l == 2) {
				if(sig[0] == 0xff && sig[1] == 0xd8) {
					return true;
				}
			}
			return false;
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
			if(probe(fin) == false) {
				return false;
			}

			struct jpeg_decompress_struct cinfo;
			struct jpeg_error_mgr errmgr;
			memset(&cinfo, 0, sizeof(cinfo));
			memset(&errmgr, 0, sizeof(errmgr));

			// エラーのハンドリング
			cinfo.err = jpeg_std_error(&errmgr);
			errmgr.error_exit = error_exit_task_;

		    // 構造体の初期設定
			jpeg_create_decompress(&cinfo);

///			cinfo.mem->alloc_small = my_malloc;

			// file_io クラス設定
			fio_jpeg_file_io_src_(&cinfo, &fin);

			// ファイルの情報ヘッダの読込み
			error_code_ = 0;
			jpeg_read_header(&cinfo, TRUE);
			if(error_code_) {
				utils::format("JPEG decode error: 'header'(%d)\n") % error_code_;
				jpeg_destroy_decompress(&cinfo);
				return false;
			}
#if 0
			cinfo.two_pass_quantize = FALSE;
			cinfo.dither_mode = JDITHER_ORDERED;
			if (! cinfo.quantize_colors) /* don't override an earlier -colors */
				cinfo.desired_number_of_colors = 216;
			cinfo.dct_method = JDCT_FASTEST;
			cinfo.do_fancy_upsampling = FALSE;
#endif
			utils::format("%d, %d\n") % cinfo.image_width % cinfo.image_height;

			// 解凍の開始
			error_code_ = 0;

			jpeg_start_decompress(&cinfo);
			if(error_code_) {
				utils::format("JPEG decode error: 'decompress'(%d)\n") % error_code_;
				jpeg_finish_decompress(&cinfo);
				jpeg_destroy_decompress(&cinfo);
				return false;
			}

			/// cinfo.in_color_space
			if(cinfo.output_components == 1) {
//				img_ = shared_img(new img_rgba8);
//				img_->create(vtx::spos(cinfo.image_width, cinfo.image_height), true);
			} else if(cinfo.output_components == 3) {
//				img_ = shared_img(new img_rgba8);
//				img_->create(vtx::spos(cinfo.image_width, cinfo.image_height), true);
			} else if(cinfo.output_components == 4) {
//				img_ = shared_img(new img_rgba8);
//				img_->create(vtx::spos(cinfo.image_width, cinfo.image_height), true);
			} else {
//				img_ = 0;
				utils::format("JPEG decode error: Can not support components: %d\n") % 
					static_cast<int>(cinfo.output_components);
				jpeg_finish_decompress(&cinfo);
				jpeg_destroy_decompress(&cinfo);
				return false;
			}

			uint8_t line[cinfo.output_components * cinfo.image_width];
			uint8_t* lines[1];
			lines[0] = &line[0];
			for(uint32_t y = 0; y < cinfo.image_height; ++y) {
				jpeg_read_scanlines(&cinfo, (JSAMPLE**)lines, 1);
				uint8_t* p = &line[0];
				if(cinfo.output_components == 4) {
					for(uint32_t x = 0; x < cinfo.image_width; ++x) {
						gr_plot(x, y, p[0], p[1], p[2]);
						p += 4;
					}
				} else if(cinfo.output_components == 3) {
					for(uint32_t x = 0; x < cinfo.image_width; ++x) {
						gr_plot(x, y, p[0], p[1], p[2]);
						p += 3;
					}
				} else if(cinfo.output_components == 1) {
					for(uint32_t x = 0; x < cinfo.image_width; ++x) {
						gr_plot(x, y, p[0], p[0], p[0]);
						++p;
					}
				}
			}

			jpeg_finish_decompress(&cinfo);
			jpeg_destroy_decompress(&cinfo);

			fio_src_ptr src = (fio_src_ptr)cinfo.src;
			if(src->err_empty) {
				return false;
			} else {
				return true;
			}
		}
	};
}


