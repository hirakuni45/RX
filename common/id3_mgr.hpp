#pragma once
//=====================================================================//
/*!	@file
	@brief	MP3/ID3 タグ・デコード・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/file_io.hpp"
#include "common/format.hpp"

namespace audio {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	MP3/ID3 タグ・デコード・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class id3_mgr {

		uint32_t	org_pos_;
		uint16_t	ver_;
		uint8_t		flag_;
		uint32_t	size_;

		uint32_t get16_(const void* org) noexcept
		{
			const uint8_t* p = static_cast<const uint8_t*>(org);
			uint32_t sz = 0;
			sz  = static_cast<uint32_t>(p[0]) << 8;
			sz |= static_cast<uint32_t>(p[1]);
			return sz;
		}

		uint32_t get_size_(const void* org) noexcept
		{
			const uint8_t* p = static_cast<const uint8_t*>(org);
			uint32_t sz = 0;
			sz  = (static_cast<uint32_t>(p[0]) & 0x7f) << 21;
			sz |= (static_cast<uint32_t>(p[1]) & 0x7f) << 14;
			sz |= (static_cast<uint32_t>(p[2]) & 0x7f) << 7;
			sz |= (static_cast<uint32_t>(p[3]) & 0x7f);
			return sz;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		id3_mgr() noexcept : org_pos_(0), ver_(0), flag_(0), size_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	解析
			@param[in]	fin		「file_io」
			@return	成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool analize(utils::file_io& fin) noexcept
		{
			if(!fin.is_open()) {
				return false;
			}

			org_pos_ = fin.tell();
			char tmp[10];
			if(fin.read(tmp, 1, 10) != 10) {
				fin.seek(utils::file_io::SEEK::SET, org_pos_);
				return false;
			}
			if(strncmp(tmp, "ID3", 3) != 0) {
				fin.seek(utils::file_io::SEEK::SET, org_pos_);
				return false;
			}
			ver_ = get16_(&tmp[3]);
			flag_ = static_cast<uint8_t>(tmp[5]);
			size_ = get_size_(&tmp[6]);

			utils::format("ID3v2: %d\n") % size_;

			if(!fin.seek(utils::file_io::SEEK::CUR, size_)) {
				return false;
			}

			return true;
		}

	};
}

