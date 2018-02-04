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
			auto n = str::get_words(line_);
			if(n >= 1) {
				char cmd[128];
				if(!str::get_word(line_, 0, cmd, sizeof(cmd))) {
					return;
				}
				if(strcmp(cmd, "help") == 0) {
					utils::format("Ignitor command shell\n");
					utils::format("  help\n");
					utils::format("  crm\n");
					utils::format("  wdm\n");
					utils::format("  dc2\n");
					utils::format("  dc1\n");
					utils::format("  wgm\n");
					utils::format("  icm\n");
				} else if(strcmp(cmd, "crm") == 0) {

				} else if(strcmp(cmd, "wdm") == 0) {

				} else if(strcmp(cmd, "dc2") == 0) {

				} else if(strcmp(cmd, "dc1") == 0) {

				} else if(strcmp(cmd, "wgm") == 0) {

				} else if(strcmp(cmd, "icm") == 0) {

				} else {
					utils::format("Command error: '%s'\n") % cmd;
				}
			}

//			utils::format("recv command: '%s'\n") % line_;
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

			while(len > 0) {
				char ch = telnets_.getch();
				--len;
				if(ch == '\r') continue;
				else if(ch == '\n') {  // LF code
					ch = 0;
				}
				line_[pos_] = ch;
				++pos_;
				if(ch == 0 || pos_ >= (sizeof(line_) - 1)) {
					analize_();
					pos_ = 0;
					line_[pos_] = 0;
				}
			}
		}
	};
}
