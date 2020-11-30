#pragma once
//=====================================================================//
/*! @file
    @brief  四則演算コマンドライン
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cmath>
#include <cstring>
#include "common/command.hpp"

#include "common/format.hpp"
#include "common/fixed_string.hpp"

#include "common/basic_arith.hpp"
#include "common/mpfr.hpp"
#include "calc_func.hpp"
#include "calc_symbol.hpp"

namespace app {

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    /*!
        @brief  calc cmd クラス
    */
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    class calc_cmd {

		static const uint32_t CALC_NUM = 250;  ///< 250 桁

		static const uint32_t ANS_NUM = 60;

		typedef utils::command<256> CMD;
		CMD		cmd_;

		// 数値クラス
		typedef mpfr::value<CALC_NUM> NVAL;

		typedef utils::calc_symbol<NVAL> SYMBOL;
		SYMBOL	symbol_;

		typedef utils::calc_func<NVAL> FUNC;
		FUNC	func_;

		typedef utils::basic_arith<NVAL, SYMBOL, FUNC> ARITH;
		ARITH	arith_;

		typedef utils::fixed_string<256> STR;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-------------------------------------------------------------//
		calc_cmd() noexcept : cmd_(),
			symbol_(), func_(), arith_(symbol_, func_)
		{ }


		//-------------------------------------------------------------//
		/*!
			@brief  初期化
		*/
		//-------------------------------------------------------------//
		void start() noexcept
		{
			cmd_.set_prompt("# ");
		}


		//-------------------------------------------------------------//
		/*!
			@brief  アップデート
		*/
		//-------------------------------------------------------------//
		void update() noexcept
		{
			auto ret = cmd_.service();
			if(!ret) return;

			const auto* cmd =  cmd_.get_command();
			if(cmd[0] == 0) return;

			if(arith_.analize(cmd)) {

				auto ans = arith_();
				symbol_.set_value(SYMBOL::NAME::ANS, ans);

				char tmp[ANS_NUM+1];
				ans(ANS_NUM, tmp, sizeof(tmp));
				// zero supless
				auto l = strlen(tmp);
				while(l > 0) {
					--l;
					if(tmp[l] != '0') break;
					else {
						tmp[l] = 0;
					}
				}
				if(l > 0) { if(tmp[l] == '.') tmp[l] = 0; }

				utils::format(" %s\n") % tmp;

			} else {
				utils::format("Fail: %s\n") % cmd;
			}
		}
	};
}
