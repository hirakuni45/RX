#pragma once
//=====================================================================//
/*!	@file
	@brief	画像ローダー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include "graphics/bmp_in.hpp"
#include "graphics/picojpeg_in.hpp"
#include "graphics/png_in.hpp"

// PNG のロードを有効にする場合
#define ENABLE_PNG

namespace img {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	画像ローダー
		@param[in]	PLOT	描画ファンクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class PLOT>
	class img_in {

		typedef bmp_in<PLOT> BMP;
		typedef picojpeg_in<PLOT> JPEG;

		BMP			bmp_;
		JPEG		jpeg_;

#ifdef ENABLE_PNG
		typedef png_in<PLOT> PNG;
		PNG			png_;
#endif

		enum class TYPE : uint8_t {
			NONE,
			BMP,
			JPEG,
			PNG,
		};
		TYPE		type_;

		bool img_switch_(const char* fname)
		{
			type_ = TYPE::NONE;
			bool ret = false;
			auto ext = strrchr(fname, '.');
			if(ext != nullptr) {
				if(utils::str::scan_ext(ext, bmp_.get_file_ext())) {
					type_ = TYPE::BMP;
					ret = true;
				} else if(utils::str::scan_ext(ext, jpeg_.get_file_ext())) {
					type_ = TYPE::JPEG;
					ret = true;
#ifdef ENABLE_PNG
				} else if(utils::str::scan_ext(ext, png_.get_file_ext())) {
					type_ = TYPE::JPEG;
					ret = true;
#endif
				}
			} else {
				// 拡張子が無い・・
			}
			return ret;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	plot	描画ファンクタ
		*/
		//-----------------------------------------------------------------//
		img_in(PLOT& plot) noexcept : bmp_(plot), jpeg_(plot),
#ifdef ENABLE_PNG
			png_(plot),
#endif
			type_(TYPE::NONE) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	画像ファイルか確認する
			@param[in]	fin	file_io クラス
			@return エラーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool probe(utils::file_io& fin) noexcept {
			switch(type_) {
			case TYPE::BMP:
				return bmp_.probe(fin);
			case TYPE::JPEG:
				return jpeg_.probe(fin);
#ifdef ENABLE_PNG
			case TYPE::PNG:
				return png_.probe(fin);
#endif
			default:
				break;
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	画像ファイルか確認する
			@param[in]	fname	ファイル名
			@return エラーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool probe(const char* fname) noexcept {
			if(fname == nullptr) return false;

			if(!img_switch_(fname)) {
				return false;
			}

			utils::file_io fin;
			if(!fin.open(fname, "rb")) {
				return false;
			}
			auto ret = probe(fin);
			fin.close();
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	画像ファイルの情報を取得する
			@param[in]	fin	file_io クラス
			@param[in]	fo	情報を受け取る構造体
			@return エラーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool info(utils::file_io& fin, img::img_info& fo) noexcept {
			switch(type_) {
			case TYPE::BMP:
				return bmp_.info(fin, fo);
			case TYPE::JPEG:
				return jpeg_.info(fin, fo);
#ifdef ENABLE_PNG
			case TYPE::PNG:
				return png_.info(fin, fo);
#endif
			default:
				break;
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	画像ファイルの情報を取得する
			@param[in]	fname	ファイル名
			@param[in]	fo	情報を受け取る構造体
			@return エラーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool info(const char* fname, img::img_info& fo) noexcept {
			if(fname == nullptr) return false;

			if(!img_switch_(fname)) {
				return false;
			}

			utils::file_io fin;
			if(!fin.open(fname, "rb")) {
				return false;
			}
			auto ret = info(fin, fo);
			fin.close();
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	画像ファイルをロードする
			@param[in]	fin	ファイル I/O クラス
			@param[in]	opt	フォーマット固有の設定文字列
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool load(utils::file_io& fin, const char* opt = nullptr) noexcept {
			switch(type_) {
			case TYPE::BMP:
				return bmp_.load(fin, opt);
			case TYPE::JPEG:
				return jpeg_.load(fin, opt);
#ifdef ENABLE_PNG
			case TYPE::PNG:
				return png_.load(fin, opt);
#endif
			default:
				break;
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	画像ファイルをロードする
			@param[in]	fname	ファイル名
			@param[in]	opt		フォーマット固有の設定文字列
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool load(const char* fname, const char* opt = nullptr) noexcept
		{
			if(fname == nullptr) return false;

			if(!img_switch_(fname)) {
				return false;
			}

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
