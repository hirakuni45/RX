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
#include "main.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  コマンド解析、応答
		@param[in]	TELNTES	TELNET サーバー型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class TELNETS>
	class ign_cmd {

		static const uint32_t VERSION = 20;

		TELNETS&	telnets_;

		uint32_t	pos_;
		char		line_[256];

		char		crm_ans_[16];
		uint32_t	crm_ans_pos_;

		void filter9_(char* buf)
		{
			uint32_t len = strlen(buf);
			for(uint32_t i = len; i < 9; ++i) {
				buf[i] = 0x20;
			}
			buf[9] = 0;
		}

		void analize_()
		{
			auto n = str::get_words(line_);
			if(n >= 1) {
				char cmd[128];
				if(!str::get_word(line_, 0, cmd, sizeof(cmd))) {
					return;
				}
				char para[64];
				char para9[64];
				para[0] = 0;
				if(n >= 2 && str::get_word(line_, 1, para, sizeof(para))) {
					strcpy(para9, para);
					filter9_(para9);
//					utils::format("%s: '%s'\n") % cmd % para;
					para9[9] = '\n';
					para9[10] = 0;
				}

				if(strcmp(cmd, "help") == 0) {
					utils::format("Ignitor command shell Version %d.%02d\n")
						% (VERSION / 100) % (VERSION % 100);
					utils::format("  help\n");
					utils::format("  crm ...\n");
					utils::format("  wdm ...\n");
					utils::format("  dc2 ...\n");
					utils::format("  dc1 ...\n");
					utils::format("  wgm ...\n");
					utils::format("  icm ...\n");
				} else if(strcmp(cmd, "crm") == 0) {
					crm_out(para9);
				} else if(strcmp(cmd, "wdm") == 0) {
// utils::format("%s\n") % para;
					uint32_t cmd = 0;
					utils::input("%x", para) % cmd;
					wdm_out(cmd);
				} else if(strcmp(cmd, "dc2") == 0) {
					dc2_out(para9);
				} else if(strcmp(cmd, "dc1") == 0) {
					dc1_out(para9);
				} else if(strcmp(cmd, "wgm") == 0) {
					wgm_out(para9);
				} else if(strcmp(cmd, "icm") == 0) {
					icm_out(para9);
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
			pos_(0), line_{ 0 }, crm_ans_{ 0, }, crm_ans_pos_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			{
				while(crm_len() > 0) {
					char ch = crm_inp();
					crm_ans_[crm_ans_pos_] = ch;
					++crm_ans_pos_;
					if(crm_ans_pos_ >= sizeof(crm_ans_)) {
						crm_ans_pos_ = 0;
						break;
					}
					if(ch == '\n') {
						crm_ans_[crm_ans_pos_] = 0;
						telnets_.puts(crm_ans_);
						utils::format("CRM ANS: %s") % crm_ans_;
						crm_ans_pos_ = 0;
					}
				}
			}

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
