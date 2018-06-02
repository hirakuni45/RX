#pragma once
//=====================================================================//
/*!	@file
	@brief	ファイル・入出力クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RL78/blob/master/LICENSE
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


		bool close()
		{
			if(!open_) {
				return false;
			}
			open_ = false;
			return f_close(&fp_) == FR_OK;
		}


		int read(void* ptr, uint32_t block, uint32_t num)
		{
			if(!open_) return 0; 
			UINT sz = 0;
			f_read(&fp_, ptr, block * num, &sz);
			return sz;
		}


		uint32_t tell()
		{
			return f_tell(&fp_);
		}


		bool eof()
		{
			if(!open_) return false;
			return f_eof(&fp_);
		}


		uint32_t get_file_size() const
		{
			if(!open_) return 0;
			return f_size(&fp_);
		}

	};
}
