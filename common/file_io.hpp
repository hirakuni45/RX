#pragma once
//=====================================================================//
/*!	@file
	@brief	ファイル・入出力クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/sdc_man.hpp"

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
		sdc_man&	sdcman_;
		FIL			fp_;

		bool		open_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		file_io(sdc_man& sdcman) noexcept :
			sdcman_(sdcman),
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
		bool open(const char* filename, const char* mode)
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

			if(!sdcman_.open(&fp_, filename, mdf)) {
				return false;
			}

			open_ = true;

			return true;
		}


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
		bool close()
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
		*/
		//-------------------------------------------------------------//
		int read(void* ptr, uint32_t block, uint32_t num)
		{
			if(!open_) return 0; 
			UINT sz = 0;
			f_read(&fp_, ptr, block * num, &sz);
			return sz;
		}


		bool seek(SEEK sek, int32_t ofs) noexcept
		{
			FRESULT ret;
			switch(sek) {
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
		uint32_t tell()
		{
			return f_tell(&fp_);
		}


		//-------------------------------------------------------------//
		/*!
			@brief	ファイルの終端か検査
			@return ファイルの終端なら「true」
		*/
		//-------------------------------------------------------------//
		bool eof()
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
		uint32_t get_file_size() const
		{
			if(!open_) return 0;
			return f_size(&fp_);
		}
	};
}
