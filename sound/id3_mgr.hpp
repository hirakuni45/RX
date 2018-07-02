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
#include "common/string_utils.hpp"
#include "sound/tag.hpp"

namespace audio {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	MP3/ID3 タグ・デコード・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class id3_mgr {

		enum class ID {
			NA,		///< 未知の ID

			TIT2,	///< 曲名
			TPE1,	///< アーティスト
			TALB,	///< アルバム名
			TYER,	///< 年
			TRCK,	///< トラック
		};

		uint32_t	org_pos_;
		uint16_t	ver_;
		uint8_t		flag_;
		uint32_t	size_;

		tag_t		tag_;

		static ID scan_id_(char* id) noexcept
		{
			if(strncmp(id, "TIT2", 4) == 0) return ID::TIT2;
			if(strncmp(id, "TT2", 3) == 0) return ID::TIT2;
			if(strncmp(id, "TPE1", 4) == 0) return ID::TPE1;
			if(strncmp(id, "TP1", 3) == 0) return ID::TPE1;
			if(strncmp(id, "TALB", 4) == 0) return ID::TALB;
			if(strncmp(id, "TAL", 3) == 0) return ID::TALB;
			if(strncmp(id, "TYER", 4) == 0) return ID::TYER;
			if(strncmp(id, "TYE", 3) == 0) return ID::TYER;
			if(strncmp(id, "TRCK", 4) == 0) return ID::TRCK;
			if(strncmp(id, "TRK", 3) == 0) return ID::TRCK;
			return ID::NA;
		}


		bool set_info_(ID id, utils::file_io& fin, uint32_t len) noexcept
		{
			char* dst = nullptr;
			uint32_t dstlen = 0;
			switch(id) {
			case ID::TIT2:
				dst = tag_.title_;
				dstlen = sizeof(tag_.title_);
				break;
			case ID::TPE1:
				dst = tag_.artist_;
				dstlen = sizeof(tag_.artist_);
				break;
			case ID::TALB:
				dst = tag_.album_;
				dstlen = sizeof(tag_.album_);
				break;
			case ID::TYER:
				dst = tag_.year_;
				dstlen = sizeof(tag_.year_);
				break;
			case ID::TRCK:
				dst = tag_.track_;
				dstlen = sizeof(tag_.track_);
				break;
			default:
				break;
			}

			uint8_t code;
			if(fin.read(&code, 1) != 1) {
				return false;
			}
			--len;

			if(dst == nullptr) {
				utils::format("No load, Code: %d\n") % static_cast<uint16_t>(code);
				fin.seek(utils::file_io::SEEK::CUR, len);
				return false;
			}

			if(code == 0x00) {  // ISO-8859-1
				char tmp[len + 1];
				if(fin.read(tmp, len) != len) {
					return false;
				}
				tmp[len] = 0;
				utils::str::sjis_to_utf8(tmp, dst, dstlen); 
			} else if(code == 0x01) {  // UTF-16 (with BOM)
				WCHAR tmp[len / 2 + 1];
				if(fin.read(tmp, len) != len) {
					return false;
				}
				tmp[len / 2] = 0;
				utils::str::utf16_to_utf8(&tmp[1], dst, dstlen);
			} else if(code == 0x02) {  // UTF-16BE (no BOM)
				WCHAR tmp[len / 2 + 1];
				if(fin.read(tmp, len) != len) {
					return false;
				}
				char* p = reinterpret_cast<char*>(&tmp[0]);
				for(uint32_t i = 0; i < len; i += 2) {
					std::swap(p[0], p[1]);
					p += 2;
				}
				tmp[len / 2] = 0;
				utils::str::utf16_to_utf8(tmp, dst, dstlen);
			} else if(code == 0x03) {  // UTF-8
				if(len > dstlen) {
					return false;
				}
				if(fin.read(dst, len) != len) {
					return false;
				}
				dst[len] = 0;
			} else {
				fin.seek(utils::file_io::SEEK::CUR, len);
				return false;
			}

			return true;
		}


		static uint32_t get16_(const void* org) noexcept
		{
			const uint8_t* p = static_cast<const uint8_t*>(org);
			uint32_t sz = 0;
			sz  = static_cast<uint32_t>(p[0]) << 8;
			sz |= static_cast<uint32_t>(p[1]);
			return sz;
		}


		static uint32_t get_size_syncsafe_(const void* org) noexcept
		{
			const uint8_t* p = static_cast<const uint8_t*>(org);
			uint32_t sz = 0;
			sz  = (static_cast<uint32_t>(p[0]) & 0x7f) << 21;
			sz |= (static_cast<uint32_t>(p[1]) & 0x7f) << 14;
			sz |= (static_cast<uint32_t>(p[2]) & 0x7f) << 7;
			sz |= (static_cast<uint32_t>(p[3]) & 0x7f);
			return sz;
		}


		static uint32_t get_size_32_(const void* org) noexcept
		{
			const uint8_t* p = static_cast<const uint8_t*>(org);
			uint32_t sz = 0;
			sz  = (static_cast<uint32_t>(p[0])) << 24;
			sz |= (static_cast<uint32_t>(p[1])) << 16;
			sz |= (static_cast<uint32_t>(p[2])) << 8;
			sz |= (static_cast<uint32_t>(p[3]));
			return sz;
		}


		static uint32_t get_size_24_(const void* org) noexcept
		{
			const uint8_t* p = static_cast<const uint8_t*>(org);
			uint32_t sz = 0;
			sz |= (static_cast<uint32_t>(p[0])) << 16;
			sz |= (static_cast<uint32_t>(p[1])) << 8;
			sz |= (static_cast<uint32_t>(p[2]));
			return sz;
		}


		static bool check_id_(char id) noexcept
		{
			if('0' <= id && id <= '9') return true;
			if('A' <= id && id <= 'Z') return true;
			return false;
		}


		bool parse_frame_v2_3_(utils::file_io& fin, ID& id) noexcept
		{
			char tmp[10];
			if(fin.read(tmp, 10) != 10) {
				return false;
			}

			if(!check_id_(tmp[0])) return false;
			if(!check_id_(tmp[1])) return false;
			if(!check_id_(tmp[2])) return false;
			// V2.3 なのにＩＤが３文字の場合の対処
			if(tmp[3] == ' ' || tmp[3] == 0) ;
			else if(!check_id_(tmp[3])) return false;

			uint32_t size;
			if(ver_ >= 0x400) {  // v2.4
				size = get_size_syncsafe_(&tmp[4]);
			} else {
				size = get_size_32_(&tmp[4]);
			}
			if(size == 0) return false;

			id = scan_id_(&tmp[0]);

			utils::format("ID: %c%c%c%c, ") % tmp[0] % tmp[1] % tmp[2] % tmp[3];
			utils::format("Flag: %04X, ") % get16_(&tmp[8]);
			utils::format("%d bytes\n") % size;

			set_info_(id, fin, size);

			return true;
		}


		bool parse_frame_v2_2_(utils::file_io& fin, ID& id) noexcept
		{
			char tmp[6];
			if(fin.read(tmp, 6) != 6) {
				return false;
			}

			if(!check_id_(tmp[0])) return false;
			if(!check_id_(tmp[1])) return false;
			if(!check_id_(tmp[2])) return false;

			auto size = get_size_24_(&tmp[3]);
			if(size == 0) return false;

			id = scan_id_(&tmp[0]);

//			utils::format("ID: %c%c%c, ") % tmp[0] % tmp[1] % tmp[2];
//			utils::format("%d bytes\n") % size;

			set_info_(id, fin, size);

			return true;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		id3_mgr() noexcept : org_pos_(0),
			ver_(0), flag_(0), size_(0), tag_()
		{ }


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
			if(fin.read(tmp, 10) != 10) {
				fin.seek(utils::file_io::SEEK::SET, org_pos_);
				return false;
			}
			if(strncmp(tmp, "ID3", 3) != 0) {
				fin.seek(utils::file_io::SEEK::SET, org_pos_);
				return false;
			}
			uint32_t org = fin.tell();
			ver_ = get16_(&tmp[3]);
			flag_ = static_cast<uint8_t>(tmp[5]);
			size_ = get_size_syncsafe_(&tmp[6]);

			utils::format("ID3v2: Ver: %04X, Flag: %02X (%d)\n")
				% ver_ % static_cast<uint16_t>(flag_) % size_;

			if(flag_ & 0b01000000) {  // EXT header
				if(fin.read(tmp, 4) != 4) {
					fin.seek(utils::file_io::SEEK::SET, org_pos_);
					return false;
				}
				uint32_t size;
				if(ver_ >= 0x400) {  // v2.4
					size = get_size_syncsafe_(&tmp[4]);
				} else {
					size = get_size_32_(&tmp[4]);
				}
				fin.seek(utils::file_io::SEEK::CUR, size - 4);
			}

			while(fin.tell() < (org + size_)) {
				bool f;
				ID id = ID::NA;
				if(ver_ >= 0x300) {
					f = parse_frame_v2_3_(fin, id);
				} else {
					f = parse_frame_v2_2_(fin, id);
				}
				if(!f) {
					break;
				}
			}

			if(!fin.seek(utils::file_io::SEEK::SET, org + size_)) {
				return false;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	タグ情報を取得
			@return タグ情報
		*/
		//-----------------------------------------------------------------//
		const tag_t& get_tag() const noexcept { return tag_; }
	};
}
