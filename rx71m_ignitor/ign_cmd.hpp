#pragma once
//=====================================================================//
/*! @file
    @brief  RX71M イグナイター・コマンド解析、応答
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/string_utils.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  コマンド解析、応答
		@param[in]	TELNTES	TELNET サーバー型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class TELNETS>
	class ign_cmd {

		TELNETS&	telnets_;

		uint32_t	pos_;
		char		line_[256];

		void analize_()
		{
			utils::format("command: '%s'\n") % line_;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	telnets	TELNETサーバー・インスタンス
		*/
		//-----------------------------------------------------------------//
		ign_cmd(TELNETS& telnets) : telnets_(telnets),
			pos_(0), line_{ 0 } { }


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			if(!telnets_.probe()) return;

			auto len = telnets_.length();
			if(len == 0) return;

			char tmp[len];
			uint32_t n = 0;
			while(len > 0) {
				tmp[n] = telnets_.getch();
				++n;
				--len;
			}

			for(uint32_t i = 0; i < n; ++i) {
				char ch = tmp[i];
//				utils::format("%c") % ch;
				if(ch == '\n') {  // LF
					continue;
				} else if(ch == '\r') {  // CR code
					analize_();
					pos_ = 0;
					line_[pos_] = 0;
				} else {
					line_[pos_] = ch;
					++pos_;
					line_[pos_] = 0;
				}
				if(pos_ >= (sizeof(line_) - 1)) {
					analize_();
					pos_ = 0;
					line_[pos_] = 0;
				}
			}
		}
	};
}
