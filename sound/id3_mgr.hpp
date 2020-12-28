#pragma once
//=====================================================================//
/*!	@file
	@brief	MP3/ID3 タグ・デコード・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/file_io.hpp"
#include "common/format.hpp"
#include "common/string_utils.hpp"
#include "sound/tag.hpp"

namespace sound {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	MP3/ID3 タグ・デコード・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class id3_mgr {

		enum class ID {
			NA,		///< 未知の ID

			TIT2,	///< 曲名
			TPE1,	///< 1st アーティスト
			TPE2,	///< 2nd アーティスト
			TALB,	///< アルバム名
			TYER,	///< 年
			TDAT,	///< 日付
			TPOS,	///< Part Of Set
			TRCK,	///< トラック
			COMM,	///< コメント
			APIC,	///< アルバム画像
		};

		uint32_t	org_pos_;
		uint16_t	ver_;
		uint8_t		flag_;
		bool		id3v1_;
		uint32_t	size_;

		tag_t		tag_;

		static ID scan_id_(char* id) noexcept
		{
			if(strncmp(id, "TIT2", 4) == 0) return ID::TIT2;
			if(strncmp(id, "TT2", 3) == 0) return ID::TIT2;
			if(strncmp(id, "TPE1", 4) == 0) return ID::TPE1;
			if(strncmp(id, "TP1", 3) == 0) return ID::TPE1;
			if(strncmp(id, "TPE2", 4) == 0) return ID::TPE2;
			if(strncmp(id, "TP2", 3) == 0) return ID::TPE2;
			if(strncmp(id, "TALB", 4) == 0) return ID::TALB;
			if(strncmp(id, "TAL", 3) == 0) return ID::TALB;
			if(strncmp(id, "TYER", 4) == 0) return ID::TYER;
			if(strncmp(id, "TYE", 3) == 0) return ID::TYER;
			if(strncmp(id, "TDAT", 4) == 0) return ID::TDAT;
			if(strncmp(id, "DAT", 3) == 0) return ID::TDAT;
			if(strncmp(id, "TPOS", 4) == 0) return ID::TPOS;
			if(strncmp(id, "TRCK", 4) == 0) return ID::TRCK;
			if(strncmp(id, "TRK", 3) == 0) return ID::TRCK;
			if(strncmp(id, "COM", 3) == 0) return ID::COMM;
			if(strncmp(id, "COMM", 4) == 0) return ID::COMM;
			if(strncmp(id, "APIC", 4) == 0) return ID::APIC;
			if(strncmp(id, "PIC", 3) == 0) return ID::APIC;
			return ID::NA;
		}


		static bool get_text64_(utils::file_io& fin, char* dst, uint32_t& len) noexcept
		{
			for(int i = 0; i < 63; ++i) {
				char ch;
				if(fin.read(&ch, 1) != 1) return false;
				len--;
				dst[i] = ch;
				if(ch == 0) return true;
			}
			return false;
		}


		static bool skip_text_(uint8_t code, utils::file_io& fin, uint32_t& len) noexcept
		{
			for(int i = 0; i < 64; ++i) {
				switch(code) {
				case 0:  // ISO-8859-1
				case 3:  // UTF-8
					{
						char ch;
						if(fin.read(&ch, 1) != 1) return false;
						len--;
						if(ch == 0) return true;
					}
					break;
				case 1:  // UTF-16 ( With BOM )
				case 2:  // UTF-16
					{
						uint16_t ch;
						if(fin.read(&ch, 2) != 2) return false;
						len -= 2;
						if(ch == 0) return true;
					}
					break;
				}
			}
			return false;
		}

		bool set_apic_(utils::file_io& fin, uint32_t len, bool v2_3) noexcept
		{
			uint8_t code;
			if(fin.read(&code, 1) != 1) {
				return false;
			}
			len--;

			if(v2_3) {
				char tmp[64];
				if(!get_text64_(fin, tmp, len)) {
					return false;
				}
				if(strlen(tmp) < 5) {  // ヘッダーが微妙に違う場合の強引な回避策・・
					if(!get_text64_(fin, tmp, len)) {
						return false;
					}
				}
				if(strcmp(tmp, "image/jpeg") == 0) {
					strcpy(tag_.at_apic().ext_, "jpg");
				} else if(strcmp(tmp, "image/png") == 0) {
					strcpy(tag_.at_apic().ext_, "png");
				} else if(strcmp(tmp, "image/bmp") == 0) {
					strcpy(tag_.at_apic().ext_, "bmp");
				}
				if(fin.read(&tag_.at_apic().typ_, 1) != 1) {
					return false;
				}
				len--;
				utils::format("V2.3: '%s'\n") % tmp;
			} else {
				if(fin.read(tag_.at_apic().ext_, 3) != 3) {
					return false;
				}
				len -= 3;
				if(fin.read(&tag_.at_apic().typ_, 1) != 1) {
					return false;
				}
				len--;
				utils::format("V2.2: '%s'\n") % tag_.get_apic().ext_;
			}
			auto ret = skip_text_(code, fin, len);
			if(!ret) {
				utils::format("ID3 APIC skip text error\n");
			}
			tag_.at_apic().ofs_ = fin.tell();
			tag_.at_apic().len_ = len;
			fin.seek(utils::file_io::SEEK::CUR, len);
			return ret;
		}


		bool set_info_(ID id, utils::file_io& fin, uint32_t len, bool v2_3) noexcept
		{
			if(len == 0) {
				// len が「０」のタグ検査
				return false;
			}

			if(id == ID::APIC) {
				return set_apic_(fin, len, v2_3);
			}

			uint8_t code;
			if(fin.read(&code, 1) != 1) {
				return false;
			}
			len--;
			char dst[128];
			auto dstlen = sizeof(dst);
			if(code == 0x00) {  // ISO-8859-1
				char tmp[len + 1];
				if(fin.read(tmp, len) != len) {
					return false;
				}
				tmp[len] = 0;
				utils::str::oemc_to_utf8(tmp, dst, dstlen); 
			} else if(code == 0x01) {  // UTF-16 (with BOM)
				uint16_t tmp[len / 2 + 1];
				if(fin.read(tmp, len) != len) {
					return false;
				}
				tmp[len / 2] = 0;
				utils::str::utf16_to_utf8(&tmp[1], dst, dstlen);
			} else if(code == 0x02) {  // UTF-16BE (no BOM)
				uint16_t tmp[len / 2 + 1];
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

			bool ret = true;
			switch(id) {
			case ID::TIT2:
				tag_.at_title() = dst;
				break;
			case ID::TPE1:
				tag_.at_artist() = dst;
				break;
			case ID::TPE2:
				tag_.at_writer() = dst;
				break;
			case ID::TALB:
				tag_.at_album() = dst;
				break;
			case ID::TYER:
				tag_.at_year() = dst;
				break;
			case ID::TDAT:
				tag_.at_date() = dst;
				break;
			case ID::TPOS:
				tag_.at_disc() = dst;
				break;
			case ID::TRCK:
				tag_.at_track() = dst;
				break;
			case ID::COMM:
				tag_.at_comment() = dst;
				break;
			default:
				ret = false;
				break;
			}

			return ret;
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
			id = scan_id_(&tmp[0]);

//			utils::format("ID: %c%c%c%c\n") % tmp[0] % tmp[1] % tmp[2] % tmp[3];
//			utils::format("Flag: %04X, ") % get16_(&tmp[8]);
//			utils::format("%d bytes\n") % size;

			set_info_(id, fin, size, true);

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

			id = scan_id_(&tmp[0]);

//			utils::format("ID: %c%c%c, ") % tmp[0] % tmp[1] % tmp[2];
//			utils::format("%d bytes\n") % size;

			set_info_(id, fin, size, false);

			return true;
		}


		bool parse_v1_(utils::file_io& fin) noexcept
		{
			if(!fin.seek(utils::file_io::SEEK::END, 128)) {
				return false;
			}

			char tmp[128];
			if(fin.read(tmp, 128) != 128) {
				return false;
			}
			if(strncmp(tmp, "TAG", 3) != 0) {
				return false;
			}

			tag_.clear();

			tag_.at_album() = &tmp[63];
			tag_.at_title() = &tmp[3];
			tag_.at_artist() = &tmp[33];

			tag_.at_comment() = &tmp[97];

			tmp[93+4] = 0;
			tag_.at_date() = &tmp[93];

			return true;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		id3_mgr() noexcept : org_pos_(0), ver_(0), flag_(0), id3v1_(false), size_(0), tag_()
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	ID3 タグを検出したらスキップする
			@param[in]	fin		「file_io」
			@return	成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool skip_header(utils::file_io& fin) noexcept
		{
			auto org = fin.tell();

			char tmp[10];
			if(fin.read(tmp, 10) != 10) {
				fin.seek(utils::file_io::SEEK::SET, org);
				return false;
			}
			if(strncmp(tmp, "ID3", 3) != 0) {
				fin.seek(utils::file_io::SEEK::SET, org);
				return false;
			}
//			ver = get16_(&tmp[3]);
//			flag = static_cast<uint8_t>(tmp[5]);
			auto size = get_size_syncsafe_(&tmp[6]);

			if(!fin.seek(utils::file_io::SEEK::SET, org + 10 + size)) {
				fin.seek(utils::file_io::SEEK::SET, org);
				return false;
			}

			fin.seek(utils::file_io::SEEK::SET, org);
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	パース
			@param[in]	fin		「file_io」
			@return	成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool parse(utils::file_io& fin) noexcept
		{
			if(!fin.is_open()) {
				return false;
			}

			id3v1_ = false;

			org_pos_ = fin.tell();
			char tmp[10];
			if(fin.read(tmp, 10) != 10) {
				fin.seek(utils::file_io::SEEK::SET, org_pos_);
				return false;
			}
			if(strncmp(tmp, "ID3", 3) != 0) {  // V2 が無い場合、
				auto ret = parse_v1_(fin);  // V1 がある場合、パース
				fin.seek(utils::file_io::SEEK::SET, org_pos_);
				if(ret) id3v1_ = true;
				return ret;
			}
			tag_.clear(tag_.serial_ + 1);
			uint32_t org = fin.tell();
			ver_ = get16_(&tmp[3]);
			flag_ = static_cast<uint8_t>(tmp[5]);
			size_ = get_size_syncsafe_(&tmp[6]);

///			utils::format("FS: %d\n") % fin.get_file_size();

			utils::format("ID3v2: Ver: %04X, Flag: %02X (%d)\n")
				% ver_ % static_cast<uint16_t>(flag_) % size_;

			if(flag_ & 0b01000000) {  // EXT header
				if(fin.read(tmp, 4) != 4) {
					fin.seek(utils::file_io::SEEK::SET, org_pos_);
					return false;
				}
				uint32_t size;
				if(ver_ >= 0x400) {  // v2.4
//					size = get_size_syncsafe_(&tmp[4]);
					size = get_size_syncsafe_(tmp);
				} else {
//					size = get_size_32_(&tmp[4]);
					size = get_size_32_(tmp);
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
			@brief	V1 タグか検査
			@return V1 タグの場合「true」
		*/
		//-----------------------------------------------------------------//
		auto is_v1() const noexcept { return id3v1_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	タグ情報を取得
			@return タグ情報
		*/
		//-----------------------------------------------------------------//
		const tag_t& get_tag() const noexcept { return tag_; }
	};
}
