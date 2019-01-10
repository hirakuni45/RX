#pragma once
//=====================================================================//
/*!	@file
	@brief	PNG クラス
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
	class png_in {

		PLOT&		plot_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	plot	描画ファンクタ
		*/
		//-----------------------------------------------------------------//
		png_in(PLOT& plot) noexcept : plot_(plot)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	ステータスの取得（Error code）
			@return ステータス
		*/
		//-----------------------------------------------------------------//
//		uint8_t get_status() const noexcept { return status_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	PNG ファイルか確認する
			@param[in]	fin	file_io クラス
			@return エラーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool probe(utils::file_io& fin) noexcept
		{
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
