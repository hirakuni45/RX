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

			if(strcmp(cmd, "help") == 0 || strcmp(cmd, "?") == 0) {
				utils::format("  PI\n");
				utils::format("  LOG2\n");
				utils::format("  EULER\n");
				utils::format("  ANS\n");
				utils::format("  V[0-9]     Memory symbol 0..9\n");
				utils::format("  Min[0-9]   Memory In 0..9\n");
				utils::format("  Rad        0 to 2*PI\n");
				utils::format("  Grad       0 to 400\n");
				utils::format("  Deg        0 to 360\n");
				utils::format("  sin(x)\n");
				utils::format("  cos(x)\n");
				utils::format("  tan(x)\n");
				utils::format("  asin(x)\n");
				utils::format("  acos(x)\n");
				utils::format("  atan(x)\n");
				utils::format("  sqrt(x)\n");
				utils::format("  log(x)\n");
				utils::format("  ln(x)\n");
				utils::format("  exp10(x)\n");
				return;
			} else if(strncmp(cmd, "Min", 3) == 0) {
				if(cmd[3] >= '0' && cmd[3] <= '9') {
					NVAL val;
					symbol_(SYMBOL::NAME::ANS, val);
					auto vi = SYMBOL::NAME::V0;
					vi = static_cast<SYMBOL::NAME>(static_cast<uint8_t>(vi) + (cmd[3] - '0'));
					symbol_.set_value(vi, val);
				} else {
					utils::format("Min number fail.\n");
				}
				return;
			} else if(strcmp(cmd, "Rad") == 0) {
				func_.set_atype(FUNC::ATYPE::Rad);
				return;
			} else if(strcmp(cmd, "Grad") == 0) {
				func_.set_atype(FUNC::ATYPE::Grad);
				return;
			} else if(strcmp(cmd, "Deg") == 0) {
				func_.set_atype(FUNC::ATYPE::Deg);
				return;
			}

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
