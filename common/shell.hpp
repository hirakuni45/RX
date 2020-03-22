#pragma once
//=====================================================================//
/*!	@file
	@brief	シェル：FatFs を利用したシェル風コマンド群 @n
			FileSystem コマンド解析、実行 @n
			・dir [xxx] @n
			・pwd @n
			・cd [xxx] @n
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

		bool	state_;

	public:
        //-----------------------------------------------------------------//
        /*!
            @brief  コンストラクター
        */
        //-----------------------------------------------------------------//
		shell(CMD& cmd) : cmd_(cmd), state_(true)
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
            @brief  基本ＦＳ操作コマンド解析
			@return ＦＳ操作にマッチしたら「true」
        */
        //-----------------------------------------------------------------//
		bool analize() noexcept
		{
            auto cmdn = cmd_.get_words();
            if(cmdn >= 1) {
                if(cmd_.cmp_word(0, "ls")) {  // ls [xxx]
					char tmp[FF_MAX_LFN + 1];
					if(cmdn == 1) {
						if(!utils::file_io::pwd(tmp, sizeof(tmp))) {
							state_ = false;
						} else {
							state_ = utils::file_io::dir(tmp);
						}
					} else {
						cmd_.get_word(1, tmp, sizeof(tmp));
						state_ = utils::file_io::dir(tmp);
					}
				} else if(cmd_.cmp_word(0, "pwd")) {  // pwd
					char tmp[FF_MAX_LFN + 1];
					if(!utils::file_io::pwd(tmp, sizeof(tmp))) {
						state_ = false;
					} else {
						utils::format("%s\n") % tmp;
					}
				} else if(cmd_.cmp_word(0, "cd")) {  // cd [xxx]
					char tmp[FF_MAX_LFN + 1];
					if(cmdn == 1) {
						strcpy(tmp, "/");
					} else {
						cmd_.get_word(1, tmp, sizeof(tmp));
					}
					state_ = utils::file_io::cd(tmp);
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
			static const char* t[] = {
				"ls [xxx]", "list current directory (-l: long)",
				"pwd",      "current directory path",
				"cd [xxx]", "change current directory",
				"free",     "list disk space",
			};
			for(int i = 0; i < 4; ++i) {
				for(int n = 0; n < spc0; ++n) {
					utils::format(" ");
				}
				utils::format("%s") % t[i * 2];
				int n = strlen(t[i * 2]);
				while(n < spc1) { utils::format(" "); ++n; }
				utils::format("%s\n") % t[i * 2 + 1];
			}
		}
	};
}
