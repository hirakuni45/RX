#pragma once
//=====================================================================//
/*! @file
    @brief  演算コマンドライン
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cmath>
#include <cstring>
#include <string>
#include <cstring>

// #define USE_BOOST_UMAP
#ifdef USE_BOOST_UMAP
#include <boost/unordered_map.hpp>
#else
#include "common/fixed_map.hpp"
#endif

#include "common/basic_arith.hpp"
#include "common/mpfr.hpp"
#include "common/fixed_string.hpp"

#include "calc_func.hpp"
#include "calc_symbol.hpp"

namespace app {

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    /*!
        @brief  calc cmd クラス
    */
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    struct calc_cmd {

		static constexpr uint32_t ANS_NUM = 30;  			///< 表示桁
		// 内部演算を大きくしないと、最下位の表示が曖昧になる・・
		static constexpr uint32_t CALC_NUM = ANS_NUM * 4;	///< 内部演算

		// 数値クラス
		typedef mpfr::value<CALC_NUM> NVAL;

#ifdef USE_BOOST_UMAP
		typedef boost::unordered_map<utils::STR8, uint8_t> MAP;
#else
		typedef utils::fixed_map<utils::STR8, uint8_t, 64> MAP;
#endif
		typedef utils::calc_symbol<NVAL, MAP> SYMBOL;
		typedef utils::calc_func<NVAL, MAP> FUNC;
		typedef utils::basic_arith<NVAL, SYMBOL, FUNC> ARITH;

	private:
		MAP		map_;
		SYMBOL	symbol_;
		FUNC	func_;
		ARITH	arith_;

		void (*out_func_)(const char* str);

		int		shift_;
		bool	disp_separate_;

		void sep_(const char* src, int len, int mod, int spn) noexcept
		{
			char sub[8];

			if(mod == 0) mod = spn;
			while(len > 0) {
				strncpy(sub, src, mod);
				if(len > spn) {
					sub[mod] = '\'';
					sub[mod + 1] = 0;
				} else {
					sub[mod] = 0;
				}
				out_func_(sub);
				len -= mod;
				src += mod;
				mod = spn;
			}
		}

		void disp_(NVAL& ans) noexcept
		{
			char cnv = 'f';
			uint32_t spn = 3;
			if(func_.get_vtype() == FUNC::VTYPE::Hex) {
				cnv = 'A';
				spn = 4;
			} else if(func_.get_vtype() == FUNC::VTYPE::Bin) {
				cnv = 'b';
				spn = 4;
			}

			if(shift_ != 0) {
				auto exp = NVAL::exp10(NVAL(shift_));
				ans *= exp;
			}

			char tmp[ANS_NUM * 4 + 8];  // 2 進表示用に 4 倍を確保 + α
			ans(ANS_NUM, tmp, sizeof(tmp), cnv);

			if(disp_separate_) {
				const char* s = tmp;
				if(*s == '-') {
					out_func_("-");
					++s;
				} else if(*s == '+') {
					out_func_("+");
					++s;
				}
				if(cnv == 'A') {
					if(s[0] == '0' && s[1] == 'x') {
						s += 2;
						out_func_("0x");
					}
				} else if(cnv == 'b') {
					if(s[0] == '0' && s[1] == 'b') {
						s += 2;
						out_func_("0b");
					}
				}

				const char* p = strchr(s, '.');
				int l;
				if(p != nullptr) {
					l = p - s;
				} else {
					l = strlen(s);
				}
				auto m = l % spn;
				sep_(s, l, m, spn);
				if(p != nullptr) {
					out_func_(".");
					++p;
					int l = strlen(p);
					sep_(p, l, 0, spn);
				}
			} else {
				out_func_(tmp);
			}
			out_func_("\n");
		}

		void list_sym_() noexcept
		{
			for(auto id = SYMBOL::NAME::V0; id < SYMBOL::NAME::V9; SYMBOL::next(id)) {
				out_func_(symbol_.get_name(id).c_str());
				out_func_(": ");
				NVAL val;
				symbol_(id, val);
				disp_(val);
			}
		}

		bool def_func_(const char* org, uint32_t n) noexcept
		{
			return true;
		}

	public:
		//-------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-------------------------------------------------------------//
		calc_cmd() noexcept :
			map_(), symbol_(map_), func_(map_), arith_(symbol_, func_),
			out_func_(nullptr),
			shift_(0), disp_separate_(true)
		{ }


		//-------------------------------------------------------------//
		/*!
			@brief  出力先を設定
			@param[in]	func	文字列出力関数
		*/
		//-------------------------------------------------------------//
		void set_out(void (*func)(const char* str)) noexcept
		{
			out_func_ = func;
		}


		//-------------------------------------------------------------//
		/*!
			@brief  ファンクタ
			@param[in] cmd		コマンドライン文字列
		*/
		//-------------------------------------------------------------//
		void operator () (const char* cmd) noexcept
		{
			if(out_func_ == nullptr) return;

			if(strcmp(cmd, "help") == 0 || strcmp(cmd, "?") == 0) {
				out_func_("  'PI'       constant symbol\n");	// 円周率シンボル
				out_func_("  'LOG2'     constant symbol\n");	// 自然数シンボル
				out_func_("  'EULER'    constant symbol\n");	// オイラー数シンボル
				out_func_("  'ANS'      constant symbol\n");	// 前の計算の答え
				out_func_("  'V[0-9]'   Memory symbol 0..9\n");	// ユーザー定数
				out_func_("  Min[0-9]   Memory In 0..9\n");		// ANS の値をユーザー定数へ設定
				out_func_("  ListSym    List symbol\n");		// シンボルのリスト
				out_func_("  Rad        0 to 2*PI\n");			// 角度法をラジアンへ
				out_func_("  Grad       0 to 400\n");			// 角度法をグラジアンへ
				out_func_("  Deg        0 to 360\n");			// 角度法をデグリへ
				out_func_("  Dec        Decimal mode\n");		// １０進表示モード
				out_func_("  Hex        Hexadecimal mode\n");	// １６進表示モード
				out_func_("  Bin        Binary mode\n");		// ２進表示モード
				out_func_("  Sep        Separate mode\n");		// セパレート表示モード(On/Off)１０進、３桁毎の表示
				out_func_("  Unit [cmd] Unit conversion mode\n");	// 単位変換表示モードの選択

				for(auto id = FUNC::NAME::org; id != FUNC::NAME::last; FUNC::next(id)) {
					out_func_("  ");
					out_func_(func_.get_name(static_cast<FUNC::NAME>(id)).c_str());
					out_func_("(x)\n");
				}
				return;

			} else if(strncmp(cmd, "Min", 3) == 0) {
				if(cmd[3] >= '0' && cmd[3] <= '9') {
					NVAL val;
					symbol_(SYMBOL::NAME::ANS, val);
					auto vi = SYMBOL::NAME::V0;
					vi = static_cast<SYMBOL::NAME>(static_cast<uint8_t>(vi) + (cmd[3] - '0'));
					symbol_.set_value(vi, val);
				} else {
					out_func_("Min number fail.\n");
				}
				return;
			} else if(strcmp(cmd, "ListSym") == 0) {
				list_sym_();
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
			} else if(strcmp(cmd, "Dec") == 0) {
				func_.set_vtype(FUNC::VTYPE::Dec);
				return;
			} else if(strcmp(cmd, "Hex") == 0) {
				func_.set_vtype(FUNC::VTYPE::Hex);
				return;
			} else if(strcmp(cmd, "Bin") == 0) {
				func_.set_vtype(FUNC::VTYPE::Bin);
				return;
			} else if(strcmp(cmd, "Sep") == 0) {
				disp_separate_ = !disp_separate_;
				out_func_(disp_separate_ ? "Separate: ON" : "Separate: OFF");
				out_func_("\n");
				return;
			} else if(strncmp(cmd, "Unit", 4) == 0) {

				return;
			}

			const auto p = strchr(cmd, ':');
			if(p != nullptr) {  // 関数定義
				def_func_(cmd, p - cmd);
			} else if(arith_.analize(cmd)) {
				auto ans = arith_();
				if(shift_ == 0) symbol_.set_value(SYMBOL::NAME::ANS, ans);
				disp_(ans);
			} else {
				char tmp[ANS_NUM + 16];
				utils::sformat("Fail: %s\n", tmp, sizeof(tmp)) % cmd;
				out_func_(tmp);
			}
		}


		//-------------------------------------------------------------//
		/*!
			@brief  calc_symbol クラスへの参照
			@return	calc_symbol クラス
		*/
		//-------------------------------------------------------------//
		auto& at_symbol() { return symbol_; }


		//-------------------------------------------------------------//
		/*!
			@brief  calc_func クラスへの参照
			@return	calc_func クラス
		*/
		//-------------------------------------------------------------//
		auto& at_func() { return func_; }


		//-------------------------------------------------------------//
		/*!
			@brief  arith クラスへの参照
			@return	arith クラス
		*/
		//-------------------------------------------------------------//
		auto& at_arith() { return arith_; }
	};
}
