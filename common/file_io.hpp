#pragma once
//=====================================================================//
/*!	@file
	@brief	ファイル・入出力クラス @n
			※ fopen 系の機能を提供するクラス。@n
			※ FATFS が必要
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#ifndef FAT_FS
#  error "file_io.hpp requires FAT_FS to be defined and include FATFS module"
#endif

#include "ff12b/src/diskio.h"
#include "ff12b/src/ff.h"

extern "C" {
	int make_full_path(const char* src, char* dst, uint16_t dsz);
	void utf8_to_sjis(const char* src, char* dst, uint32_t dsz);
};

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ファイル入出力クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class file_io {
	public:

        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
        /*!
            @brief  SEEK タイプ
        */
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
        enum class SEEK {
			SET,	///< 先頭からのオフセット
			CUR,	///< 現在位置からのオフセット
			END		///< 終端からのオフセット
        };

	private: 
		FIL			fp_;
		bool		open_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		file_io() noexcept :
			fp_(),
			open_(false)
		{ }


		//-------------------------------------------------------------//
		/*!
			@brief	デストラクター
		*/
		//-------------------------------------------------------------//
		~file_io() { close(); }


		//-------------------------------------------------------------//
		/*!
			@brief	ファイルを開く
			@param[in]	filename	ファイル名
			@param[in]	mode		オープン・モード
			@return 成功なら「true」
		*/
		//-------------------------------------------------------------//
		bool open(const char* filename, const char* mode) noexcept
		{
			if(filename == nullptr || mode == nullptr) return false;

			BYTE mdf = 0;
			if(strchr(mode, 'r') != nullptr) {
				mdf = FA_READ | FA_OPEN_EXISTING;
			}
			if(strchr(mode, 'w') != nullptr) {
				mdf = FA_WRITE;
				mdf |= FA_CREATE_NEW;
//				if(flags & O_TRUNC) mode |= FA_CREATE_ALWAYS;
			}
//			else if(rwm == O_RDWR) mode = FA_READ | FA_WRITE;
			if(strchr(mode, 'a') != nullptr) {
				mdf |= FA_OPEN_APPEND;
			}

			char tmp[_MAX_LFN + 1];
			if(!make_full_path(filename, tmp, sizeof(tmp))) {
				return false;
			}

			utf8_to_sjis(tmp, tmp, sizeof(tmp));
			FRESULT res = f_open(&fp_, tmp, mdf);
			if(res != FR_OK) {
				return false;
			}
			open_ = true;
			return true;
		}


		//-------------------------------------------------------------//
		/*!
			@brief	ファイル・ディスクリプタへの参照
			@return ファイル・ディスクリプタ
		*/
		//-------------------------------------------------------------//
		FIL& at_fd() noexcept { return fp_; }


		//-------------------------------------------------------------//
		/*!
			@brief	オープンの確認
			@return オープンなら「true」
		*/
		//-------------------------------------------------------------//
		bool is_open() const noexcept { return open_; }


		//-------------------------------------------------------------//
		/*!
			@brief	ファイルをクローズする
			@return 成功なら「true」
		*/
		//-------------------------------------------------------------//
		bool close() noexcept
		{
			if(!open_) {
				return false;
			}
			open_ = false;
			return f_close(&fp_) == FR_OK;
		}


		//-------------------------------------------------------------//
		/*!
			@brief	リード
			@param[out]	dst		読込先
			@param[in]	num		読み込みサイズ
			@return 読み込みサイズ
		*/
		//-------------------------------------------------------------//
		uint32_t read(void* dst, uint32_t len) noexcept
		{
			if(!open_) return 0; 

			UINT rl = 0;
			FRESULT res = f_read(&fp_, dst, len, &rl);
			if(res != FR_OK) {
				return 0;
			}
			return rl;
		}


		//-------------------------------------------------------------//
		/*!
			@brief	リード
			@param[out]	dst		読込先
			@param[in]	block	ブロックサイズ
			@param[in]	num		個数
			@return 読み込みサイズ
		*/
		//-------------------------------------------------------------//
		uint32_t read(void* dst, uint32_t block, uint32_t num) noexcept
		{
			return read(dst, block * num);
		}


		//-------------------------------------------------------------//
		/*!
			@brief	１文字取得
			@param[out]	ch	文字（参照）
			@return 正常なら「true」
		*/
		//-------------------------------------------------------------//
		bool get_char(char& ch) noexcept
		{
			char tmp[1];
			if(read(tmp, 1) != 1) {
				return false;
			}
			ch = tmp[0];
			return true;
		}


		//-------------------------------------------------------------//
		/*!
			@brief	ライト
			@param[in]	src		ソース
			@param[in]	num		書き込みサイズ
			@return 書き込みサイズ
		*/
		//-------------------------------------------------------------//
		uint32_t write(const void* src, uint32_t len) noexcept
		{
			if(!open_) return 0; 

			UINT wl = 0;
			FRESULT res = f_write(&fp_, src, len, &wl);
			if(res != FR_OK) {
				return 0;
			}
			return wl;
		}


		//-------------------------------------------------------------//
		/*!
			@brief	シーク（fseek 準拠）
			@param[in]	seek	シーク形式
			@param[in]	ofs		オフセット
			@return 成功なら「true」
		*/
		//-------------------------------------------------------------//
		bool seek(SEEK seek, int32_t ofs) noexcept
		{
			if(!open_) return false;
			FRESULT ret;
			switch(seek) {
			case SEEK::SET:
				ret = f_lseek(&fp_, ofs);
				break;
			case SEEK::CUR:
				{
					int32_t pos = tell();
					pos += ofs;
					ret = f_lseek(&fp_, pos);
				}
				break;
			case SEEK::END:
				{
					int32_t pos = get_file_size();
					pos -= ofs;
					ret = f_lseek(&fp_, pos);
				}
				break;
			default:
				return false;
				break;
			}
			return ret == FR_OK;
		}


		//-------------------------------------------------------------//
		/*!
			@brief	ファイル位置を返す
			@return ファイル位置
		*/
		//-------------------------------------------------------------//
		uint32_t tell() const noexcept
		{
			if(!open_) return false;
			return f_tell(&fp_);
		}


		//-------------------------------------------------------------//
		/*!
			@brief	ファイルの終端か検査
			@return ファイルの終端なら「true」
		*/
		//-------------------------------------------------------------//
		bool eof() const noexcept
		{
			if(!open_) return false;
			return f_eof(&fp_);
		}


		//-------------------------------------------------------------//
		/*!
			@brief	ファイルサイズを返す
			@return ファイルサイズ
		*/
		//-------------------------------------------------------------//
		uint32_t get_file_size() const noexcept
		{
			if(!open_) return 0;
			return f_size(&fp_);
		}
	};
}
