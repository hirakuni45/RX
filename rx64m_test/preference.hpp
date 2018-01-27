#pragma once
//=====================================================================//
/*! @file
    @brief  プリファレンス・クラス
	@copyright Copyright 2017 Kunihito Hiramatsu All Right Reserved.
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdio>
#include "common/renesas.hpp"
#include "common/format.hpp"

namespace seeda {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  preference class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class preference {

#ifdef DEBUG
		typedef utils::format debug_format;
#else
		typedef utils::null_format debug_format;
#endif

		typedef device::flash_io FLASH_IO;

	public:
#ifndef PREFER_SD
		struct seeda_h {
			uint32_t	index_;
			uint32_t	magic_;
		};
#endif

		struct seeda_t {
#ifndef PREFER_SD
			uint32_t	index_;
#endif
			uint32_t	magic_;

			float		gain_[8];

			uint16_t	limit_lo_level_[8];
			uint16_t	limit_hi_level_[8];
			uint16_t	center_[8];

			uint8_t		mode_[8];

			uint8_t		client_ip_[4];
			uint16_t	client_port_;

			char		write_path_[16];
			uint8_t		write_enable_;	// write_limit_ を廃止
			uint8_t		dummy[3];

			uint8_t		client_enable_;

			uint8_t		watchdog_enable_;
			uint16_t	watchdog_time_;

			seeda_t() :
#ifndef PREFER_SD
				index_(0),
#endif
				magic_(0),
				gain_{ 1.0f },
				limit_lo_level_{ 30000 }, limit_hi_level_{ 40000 },
				center_{ 0 },
				mode_{ 0 },
#ifdef SEEDA
				client_ip_{ 192, 168, 1, 3 },
#else
				client_ip_{ 192, 168, 3, 7 },
#endif
				client_port_(3000),
				write_path_{ "/00000" }, write_enable_(0),

				client_enable_(1),
				watchdog_enable_(0),
				watchdog_time_(5)
			{ }

			void dump() const
			{
				utils::format("Index: %d\n") % index_;
				utils::format("Magic: %08X\n") % magic_;
				for(int i = 0; i < 8; ++i) {
					utils::format("(%d) Gain: %f, ") % i % gain_[i];
					utils::format("LimitL: %d, ") % limit_lo_level_[i];
					utils::format("LimitH: %d, ") % limit_hi_level_[i];
					utils::format("Center: %d, ") % center_[i];
					utils::format("Mode: %d\n") % static_cast<uint16_t>(mode_[i]);
				}
				utils::format("Write path: '%s', ") % write_path_;
				utils::format("enable: %d\n") % static_cast<uint16_t>(write_enable_);
				utils::format("\n");
			}
		};

	private:
		seeda_t		seeda_;

		FLASH_IO	fio_;

#ifndef PREFER_SD

		uint32_t block_size_()
		{
			uint32_t size = sizeof(seeda_t);
			uint32_t mask = FLASH_IO::data_flash_block - 1;
			if(size & mask) {
				size |= mask;
				++size;
			}
			return size;
		}

		uint32_t scan_flash_()
		{
			auto size = block_size_();

			uint32_t pos = 0;
			while(pos < FLASH_IO::data_flash_size) {
				if(fio_.erase_check(pos, size)) {
					return pos;
				}
				pos += size;
			}
			return FLASH_IO::data_flash_size;
		}


		uint32_t erase_flash_()
		{
			auto size = block_size_();

			uint32_t pos = 0;
			while(pos < FLASH_IO::data_flash_size) {
				if(!fio_.erase_check(pos, size)) {
					for(uint32_t p = pos; p < size; p += FLASH_IO::data_flash_block) {
						fio_.erase(p);
					}
					return pos;
				}
				pos += size;
			}
			debug_format("Flash (preference) erase: %06X\n") % pos;
			return FLASH_IO::data_flash_size;
		}


		uint32_t scan_new_file_(seeda_h& h)
		{
			auto size = block_size_();

			h.index_ = 0;
			h.magic_ = sizeof(seeda_t);

			uint32_t back = FLASH_IO::data_flash_size;
			uint32_t pos = 0;
			while(pos < FLASH_IO::data_flash_size) {
				if(!fio_.erase_check(pos, size)) {  // 使われているブロック
					seeda_h tmp;
					if(fio_.read(pos, &tmp, sizeof(seeda_h))) {
						if(tmp.magic_ == sizeof(seeda_t) && tmp.index_ >= h.index_) {
							h = tmp;
							back = pos;
						}
					}
				}
				pos += size;
			}
			debug_format("Flash (preference) scan: %06X\n") % back;
			return back;
		}


		bool read_flash_()
		{
			seeda_h h;
			h.index_ = 0;
			h.magic_ = sizeof(seeda_t);
			auto pos = scan_new_file_(h);
			if(pos >= FLASH_IO::data_flash_size) {
				debug_format("Flash (preference) read: can't find\n");

				return false;
			}
			debug_format("Flash (preference) read: %06X\n") % pos;
			auto ret = fio_.read(pos, &seeda_, sizeof(seeda_t));

			seeda_.dump();

			return ret;
		}


		bool write_flash_(uint32_t pos)
		{
			seeda_h h;
			h.index_ = 0;
			h.magic_ = sizeof(seeda_t);
			if(scan_new_file_(h) < FLASH_IO::data_flash_size) {
				seeda_.index_ = h.index_ + 1;
			} else {
				seeda_.index_ = 0;
			}
			seeda_.magic_ = sizeof(seeda_t);
			debug_format("Flash (preference) write: %06X\n") % pos;
			auto ret = fio_.write(pos, &seeda_, sizeof(seeda_t));

			seeda_.dump();

			return ret;
		}

#endif

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		preference() : seeda_() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュＩ／Ｏへの参照
			@return フラッシュＩ／Ｏ
		*/
		//-----------------------------------------------------------------//
		FLASH_IO& at_fio() { return fio_; }		


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
		*/
		//-----------------------------------------------------------------//
		void start()
		{
			fio_.start();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  削除
			@param[in]	path	ファイル・パス
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool remove(const char* path = "seeda03.pre")
		{
#ifdef PREFER_SD
			char tmp[16];
			tmp[0] = '/';
			std::strcpy(&tmp[1], path);
			auto f = at_sdc().remove(tmp);
#else
			auto f = fio_.erase_all();
#endif
			if(f) {
				seeda_t	tmp;
				seeda_ = tmp;
			}
			return f;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	path	ファイル・パス
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool write(const char* path = "seeda03.pre")
		{
#ifdef PREFER_SD
			FILE* fp = fopen(path, "wb");
			if(fp == nullptr) {
				debug_format("Can't write preference: '%s'\n") % path;
				return false;
			}

			seeda_.magic_ = sizeof(seeda_t);

			bool ret = true;
			if(fwrite(&seeda_, 1, sizeof(seeda_t), fp) != sizeof(seeda_t)) {
				debug_format("Write error preference: '%s'\n") % path;
				ret = false;
			}

			fclose(fp);

			return ret;
#else
			auto pos = scan_flash_();  // save area + index
			if(pos >= FLASH_IO::data_flash_size) {  // no space
				pos = erase_flash_();
			}

			return write_flash_(pos);
#endif
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  読み込み
			@param[in]	path	ファイル・パス
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool read(const char* path = "seeda03.pre")
		{
#ifdef PREFER_SD
			FILE* fp = fopen(path, "rb");
			if(fp == nullptr) {
				debug_format("Can't read preference: '%s'\n") % path;
				return false;
			}

			bool ret = true;
			if(fread(&seeda_, 1, sizeof(seeda_t), fp) != sizeof(seeda_t)) {
				debug_format("Read error preference: '%s'\n") % path;
				ret = false;
			}

			if(seeda_.magic_ != sizeof(seeda_t)) {
				debug_format("Read error preference magic code: Ref(%d) : File(%d)\n")
					% sizeof(seeda_t) % seeda_.magic_;
				ret = false;
			}

			fclose(fp);

			return ret;
#else
			return read_flash_();
#endif
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  プリファレンスの取得
			@return プリファレンス
		*/
		//-----------------------------------------------------------------//
		const seeda_t& get() const { return seeda_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  プリファレンスへの参照
			@return プリファレンス
		*/
		//-----------------------------------------------------------------//
		seeda_t& at() { return seeda_; }
	};
}
