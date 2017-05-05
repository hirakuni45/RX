#pragma once
//=====================================================================//
/*! @file
    @brief  プリファレンス・クラス@n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdio>
#include "common/format.hpp"

namespace seeda {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  write_file class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class preference {
	public:
		struct seeda_t {
			uint32_t	magic_;

			float		gain_[8];
			float		offset_[8];

			uint16_t	limit_lo_level_[8];
			uint16_t	limit_hi_level_[8];

			uint8_t		mode_[8];

			uint8_t		client_ip_[4];
			uint16_t	client_port_;

			char		write_path_[16];
			uint32_t	write_limit_;

			seeda_t() : magic_(0),
				gain_{ 1.0f }, offset_{ 0.0f },
				limit_lo_level_{ 30000 }, limit_hi_level_{ 40000 },
				mode_{ 0 },
#ifdef SEEDA
				client_ip_{ 192, 168, 1, 3 },
#else
				client_ip_{ 192, 168, 3, 7 },
#endif
				client_port_(3000),
				write_path_{ "test.csv" }, write_limit_(60) { }
		};

	private:
		seeda_t		seeda_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		preference() : seeda_() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	path	ファイル・パス
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool write(const char* path = "seeda03.pre")
		{
			FILE* fp = fopen(path, "wb");
			if(fp == nullptr) {
				utils::format("Can't write preference: '%s'\n") % path;
				return false;
			}

			seeda_.magic_ = sizeof(seeda_t);

			bool ret = true;
			if(fwrite(&seeda_, 1, sizeof(seeda_t), fp) != sizeof(seeda_t)) {
				utils::format("Write error preference: '%s'\n") % path;
				ret = false;
			}

			fclose(fp);

			return ret;
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
			FILE* fp = fopen(path, "rb");
			if(fp == nullptr) {
				utils::format("Can't read preference: '%s'\n") % path;
				return false;
			}

			bool ret = true;
			if(fread(&seeda_, 1, sizeof(seeda_t), fp) != sizeof(seeda_t)) {
				utils::format("Read error preference: '%s'\n") % path;
				ret = false;
			}

			if(seeda_.magic_ != sizeof(seeda_t)) {
				utils::format("Read error preference magic code: Ref(%d) : File(%d)\n") % sizeof(seeda_t) % seeda_.magic_;
				ret = false;
			}

			fclose(fp);

			return ret;
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
