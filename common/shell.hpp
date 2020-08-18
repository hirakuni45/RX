#pragma once
//=====================================================================//
/*!	@file
	@brief	シェル：FatFs を利用したシェル風コマンド群 @n
			FileSystem コマンド解析、実行 @n
			・ls [-l] [file] @n
			・pwd @n
			・cd [file] @n
			・free
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/file_io.hpp"
#include "common/format.hpp"
#include "common/string_utils.hpp"

namespace utils {

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    /*!
        @brief  command class
		@param[in]	CMD		コマンド入力
    */
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CMD>
	class shell {

		CMD&	cmd_;

		char	prompt_[file_io::PATH_MAX_SIZE + 3];

		bool	state_;

		void make_prompt_(const char* src = nullptr)
		{
			if(src == nullptr) {
				utils::file_io::pwd(prompt_, sizeof(prompt_));
			} else {
				strcpy(prompt_, src);
			}
			strcat(prompt_, " # ");
			cmd_.set_prompt(prompt_);
		}

	public:
        //-----------------------------------------------------------------//
        /*!
            @brief  コンストラクター
        */
        //-----------------------------------------------------------------//
		shell(CMD& cmd) : cmd_(cmd), prompt_{ 0 }, state_(true)
		{ }


        //-----------------------------------------------------------------//
        /*!
            @brief  ＳＤ操作の完了を取得
			@return ＳＤ操作が正常なら「true」
        */
        //-----------------------------------------------------------------//
		bool get_status() const { return state_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  プロムプトの取得
			@return プロムプト
        */
        //-----------------------------------------------------------------//
		const char* get_prompt() { return prompt_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  基本ＦＳ操作コマンド解析
			@return ＦＳ操作にマッチしたら「true」
        */
        //-----------------------------------------------------------------//
		bool analize() noexcept
		{
			if(prompt_[0] == 0) {
				make_prompt_("/");
			}

            auto cmdn = cmd_.get_words();
            if(cmdn >= 1) {

				int opt = 0;
				int path = 0;
				for(uint32_t n = 1; n < cmd_.get_words(); ++n) {
					char tmp[16];
					cmd_.get_word(n, tmp, sizeof(tmp));
					if(tmp[0] == '-') opt = n;
					else path = n;
				}

                if(cmd_.cmp_word(0, "ls")) {  // ls [xxx]
					char tmp[utils::file_io::PATH_MAX_SIZE];
					bool ll = false;
					if(opt > 0 && cmd_.cmp_word(opt, "-l")) ll = true;
					if(path == 0) {
						if(!utils::file_io::pwd(tmp, sizeof(tmp))) {
							state_ = false;
						} else {
							state_ = utils::file_io::dir(tmp, ll);
						}
					} else {
						cmd_.get_word(path, tmp, sizeof(tmp));
						state_ = utils::file_io::dir(tmp, ll);
					}
				} else if(cmd_.cmp_word(0, "pwd")) {  // pwd
					char tmp[utils::file_io::PATH_MAX_SIZE];
					if(!utils::file_io::pwd(tmp, sizeof(tmp))) {
						state_ = false;
					} else {
						utils::format("%s\n") % tmp;
					}
				} else if(cmd_.cmp_word(0, "cd")) {  // cd [xxx]
					char tmp[utils::file_io::PATH_MAX_SIZE];
					if(path == 0) {
						strcpy(tmp, "/");
					} else {
						cmd_.get_word(1, tmp, sizeof(tmp));
					}
					state_ = utils::file_io::cd(tmp);
					if(state_) {
						make_prompt_();
					} else {
						utils::format("Illegal file path: '%s'\n") % tmp; 
					}
				} else if(cmd_.cmp_word(0, "free")) {  // free
					uint32_t fre;
					uint32_t max;
					if(utils::file_io::get_free_space(fre, max)) {
						uint32_t rate = fre * 1000 / max;
						utils::format("%u/%u [KB] (%u.%u%%)\n")
							% fre % max % (rate / 10) % (rate % 10);
						state_ = true;
					} else {
						state_ = false;
					}
				} else {
					return false;
				}
			}
			return true;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  HELP 表示
			@param[in]	spc0	初期空白数
			@param[in]	spc1	コマンド群文字数
        */
        //-----------------------------------------------------------------//
		void help(int spc0 = 4, int spc1 = 20) const {
			struct str_t {
				const char*	cmd;
				const char*	text;
			};
			static const str_t t[] = {
				{ "ls [-l] [file]", "list current directory (-l: long)" },
				{ "pwd",      "current directory path" },
				{ "cd [file]", "change current directory" },
				{ "free",     "list disk space" },
			};
			for(uint32_t i = 0; i < std::size(t); ++i) {
				for(int n = 0; n < spc0; ++n) {
					utils::format(" ");
				}
				utils::format("%s") % t[i].cmd;
				int n = strlen(t[i].cmd);
				while(n < spc1) { utils::format(" "); ++n; }
				utils::format("%s\n") % t[i].text;
			}
		}
	};
}
