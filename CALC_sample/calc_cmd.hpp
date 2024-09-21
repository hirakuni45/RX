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
// #include "common/string_utils.hpp"

#include "calc_func.hpp"
#include "calc_symbol.hpp"
#include "calc_unit.hpp"

namespace app {

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    /*!
        @brief  演算コマンドライン・クラス
    */
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    struct calc_cmd {

		static constexpr uint32_t ANS_NUM = 30;  			///< 表示桁
		// 内部演算を大きくしないと、最下位の表示が曖昧になる・・
		static constexpr uint32_t CALC_NUM = ANS_NUM * 4;	///< 内部演算

		// 基数値クラス
		typedef mpfr::value<CALC_NUM> NVAL;

#ifdef USE_BOOST_UMAP
		typedef boost::unordered_map<utils::STR8, uint8_t> MAP;
#else
		typedef utils::fixed_map<utils::STR8, uint8_t, 64> MAP;
#endif
		typedef utils::calc_symbol<NVAL, MAP> SYMBOL;
		typedef utils::calc_func<NVAL, MAP> FUNC;
		typedef unit<NVAL> UNIT;

		typedef utils::basic_arith<NVAL, SYMBOL, FUNC> ARITH;

	private:
		MAP		map_;
		SYMBOL	symbol_;
		FUNC	func_;
		UNIT	unit_;
		ARITH	arith_;

		void (*out_func_)(const char* str);

		int		shift_;

		bool	disp_separate_;

		typedef utils::str STR;

		void sep_(const char* src, int len, int mod, int spn) const noexcept
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

		void disp_(NVAL& ans) const noexcept
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
			if(unit_.get_type() != UNIT::TYPE::NIL) {
				out_func_(" [");
				out_func_(unit_.get_ext(unit_.get_out()));
				out_func_("]");
			}
			out_func_("\n");
		}

		void list_sym_() const noexcept
		{
			for(auto id = SYMBOL::NAME::V0; id < SYMBOL::NAME::V9; SYMBOL::next(id)) {
				out_func_(symbol_.get_name(id).c_str());
				out_func_(": ");
				NVAL val;
				symbol_(id, val);
				disp_(val);
			}
		}

		void unit_type_(const char* cmd, uint32_t n) noexcept
		{
			if(n > 1) {
				if(STR::cmp_word(cmd, 1, "NIL")) {
					unit_.set_type(UNIT::TYPE::NIL);
				} else if(STR::cmp_word(cmd, 1, "LENGTH")) {
					unit_.set_type(UNIT::TYPE::LENGTH);
				} else if(STR::cmp_word(cmd, 1, "SPEED")) {
					unit_.set_type(UNIT::TYPE::SPEED);
				} else if(STR::cmp_word(cmd, 1, "WEIGHT")) {
					unit_.set_type(UNIT::TYPE::WEIGHT);
				} else if(STR::cmp_word(cmd, 1, "MONEY")) {
					unit_.set_type(UNIT::TYPE::MONEY);
				} else {
					out_func_("Fail: UnitType '");
					out_func_(cmd);
					out_func_("'\n");
				}
			} else {
				out_func_("Unit type: ");
				switch(unit_.get_type()) {
				case UNIT::TYPE::NIL:
					out_func_("NIL");
					break;
				case UNIT::TYPE::LENGTH:
					out_func_("LENGTH");
					break;
				case UNIT::TYPE::SPEED:
					out_func_("SPEED");
					break;
				case UNIT::TYPE::WEIGHT:
					out_func_("WEIGHT");
					break;
				case UNIT::TYPE::MONEY:
					out_func_("MONEY");
					break;
				default:
					break;
				}
				out_func_(" (NIL, LENGTH, SPEED, WEIGHT, MONEY)\n");
			}
		}

		void unit_inp_(const char* cmd, uint32_t n) noexcept
		{
			if(unit_.get_type() == UNIT::TYPE::NIL) {
				out_func_("Unit Inp: NIL..\n");
				return;
			}
			if(n > 1) {
				char tmp[8];
				STR::get_word(cmd, 1, tmp, sizeof(tmp));
				UNIT::UNIT u;
				if(unit_.match_ext(tmp, u)) {
					unit_.set_inp(u);
				} else {
					out_func_("Input unit type miss match: '");
					out_func_(tmp);
					out_func_("'\n");
				}
			} else {
				out_func_("Unit Inp: ");
				auto ext = unit_.get_ext(unit_.get_inp());
				out_func_(ext);
				out_func_("\n");
				for(uint32_t i = 0; i < unit_.get_num(); ++i) {
					UNIT::UNIT u;
					u.val = i;
					auto s = unit_.get_ext(u);
					if(i != 0) {
						out_func_(", ");
					}
					out_func_(s);
				}
				out_func_("\n");
			}
		}

		void unit_out_(const char* cmd, uint32_t n) noexcept
		{
			if(unit_.get_type() == UNIT::TYPE::NIL) {
				out_func_("Unit Out: NIL..\n");
				return;
			}
			if(n > 1) {
				char tmp[8];
				STR::get_word(cmd, 1, tmp, sizeof(tmp));
				UNIT::UNIT u;
				if(unit_.match_ext(tmp, u)) {
					unit_.set_out(u);
				} else {
					out_func_("Output unit type miss match: '");
					out_func_(tmp);
					out_func_("'\n");
				}
			} else {
				out_func_("Unit Out: ");
				auto ext = unit_.get_ext(unit_.get_type(), unit_.get_out());
				out_func_(ext);
				out_func_("\n");
				for(uint32_t i = 0; i < unit_.get_num(); ++i) {
					UNIT::UNIT u;
					u.val = i;
					auto s = unit_.get_ext(u);
					if(i != 0) {
						out_func_(", ");
					}
					out_func_(s);
				}
				out_func_("\n");
			}
		}

		void money_rate_(const char* cmd, uint32_t n) noexcept
		{
			if(n == 1) {
				out_func_("Money type: ");
				auto num = unit_.get_num(UNIT::TYPE::MONEY);
				for(uint32_t i = 0; i < num; ++i) {
					UNIT::UNIT u;
					u.val = i;
					out_func_(unit_.get_ext(UNIT::TYPE::MONEY, u));
					if(i < (num - 1)) {
						out_func_(", ");
					}
				}
				out_func_("\n");
			} else if(n >= 2) {
				char tmp[12];
				STR::get_word(cmd, 1, tmp, sizeof(tmp));
				UNIT::UNIT u;
				if(unit_.match_ext(UNIT::TYPE::MONEY, tmp, u)) {
					if(n == 2) {
						out_func_(unit_.get_ext(UNIT::TYPE::MONEY, u));
						out_func_(": ");
						out_func_(unit_.get_rate(u.money));
						out_func_("\n");
					} else {
						char rt[12];
						STR::get_word(cmd, 2, rt, sizeof(rt));
						if(unit_.set_rate(u.money, rt)) {

						} else {
							out_func_("Money set rate fail: '");
							out_func_(rt);
							out_func_("'\n");
						}
					}
				} else {
					out_func_("Money type miss match: '");
					out_func_(tmp);
					out_func_("'\n");
				}
			}
		}

		bool def_math_(const char* org, uint32_t n) noexcept
		{
			if((org[0] >= 'A' && org[0] <= 'Z') || (org[0] >= 'a' && org[0] >= 'z')) { 
				

				return true;
			}  else {
				return false;
			}
		}

	public:
		//-------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-------------------------------------------------------------//
		calc_cmd() noexcept :
			map_(), symbol_(map_), func_(map_), unit_(),
			arith_(symbol_, func_),
			out_func_(nullptr),
			shift_(0), disp_separate_(true)
		{ }


		//-------------------------------------------------------------//
		/*!
			@brief  初期化
		*/
		//-------------------------------------------------------------//
		void init() noexcept
		{
		}


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

			auto n = STR::get_words(cmd);
			if(n == 0) return;

			if(STR::cmp_word(cmd, 0, "help") || STR::cmp_word(cmd, 0, "?")) {
				out_func_("  ListFunc    list function\n");		// 関数のリスト表示
				out_func_("  'PI'        constant symbol\n");	// 円周率シンボル
				out_func_("  'LOG2'      constant symbol\n");	// 自然数シンボル
				out_func_("  'EULER'     constant symbol\n");	// オイラー数シンボル
				out_func_("  'ANS'       constant symbol\n");	// 前の計算の答え
				out_func_("  'V[0-9]'    Memory symbol 0..9\n"); // ユーザー定数
				out_func_("  Min[0-9]    Memory In 0..9\n");	// ANS の値をユーザー定数へ設定
				out_func_("  ListSym     List symbol\n");		// シンボルのリスト
				out_func_("  Rad         0 to 2*PI\n");			// 角度法をラジアンへ
				out_func_("  Grad        0 to 400\n");			// 角度法をグラジアンへ
				out_func_("  Deg         0 to 360\n");			// 角度法をデグリへ
				out_func_("  Dec         Decimal mode\n");		// １０進表示モード
				out_func_("  Hex         Hexadecimal mode\n");	// １６進表示モード
				out_func_("  Bin         Binary mode\n");		// ２進表示モード
				out_func_("  Sep         Separate mode\n");		// セパレート表示モード(On/Off)１０進、３桁毎の表示
				out_func_("  UnitType [type]  Set unit type\n");	// 単位変換の選択
				out_func_("  UnitInp [unit]   Set input unit\n");	// 入力変換型の選択
				out_func_("  UnitOut [unit]   Set output unit\n");	// 出力変換型の選択
				out_func_("  MoneyRate [type] [rate]   Set money rate\n");	// 貨幣レートの設定
				return;
			} else if(STR::cmp_word(cmd, 0, "ListFunc")) {
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
			} else if(STR::cmp_word(cmd, 0, "ListSym")) {
				list_sym_();
				return;
			} else if(STR::cmp_word(cmd, 0, "Rad")) {
				func_.set_atype(FUNC::ATYPE::Rad);
				return;
			} else if(STR::cmp_word(cmd, 0, "Grad")) {
				func_.set_atype(FUNC::ATYPE::Grad);
				return;
			} else if(STR::cmp_word(cmd, 0, "Deg")) {
				func_.set_atype(FUNC::ATYPE::Deg);
				return;
			} else if(STR::cmp_word(cmd, 0, "Dec")) {
				func_.set_vtype(FUNC::VTYPE::Dec);
				return;
			} else if(STR::cmp_word(cmd, 0, "Hex")) {
				func_.set_vtype(FUNC::VTYPE::Hex);
				return;
			} else if(STR::cmp_word(cmd, 0, "Bin")) {
				func_.set_vtype(FUNC::VTYPE::Bin);
				return;
			} else if(STR::cmp_word(cmd, 0, "Sep")) {
				disp_separate_ = !disp_separate_;
				out_func_(disp_separate_ ? "Separate: ON" : "Separate: OFF");
				out_func_("\n");
				return;
			} else if(STR::cmp_word(cmd, 0, "UnitType")) {
				unit_type_(cmd, n);
				return;
			} else if(STR::cmp_word(cmd, 0, "UnitInp")) {
				unit_inp_(cmd, n);
				return;
			} else if(STR::cmp_word(cmd, 0, "UnitOut")) {
				unit_out_(cmd, n);
				return;
			} else if(STR::cmp_word(cmd, 0, "MoneyRate")) {
				money_rate_(cmd, n);
				return;
			}

			const auto p = strchr(cmd, '=');
			if(p != nullptr) {  // 数式定義
				if(!def_math_(cmd, p - cmd)) {
					out_func_("Math fail: ");
					out_func_(cmd);
					out_func_("\n");
				}
				return;
			}

			if(arith_.analize(cmd)) {
				auto a = arith_();
				if(shift_ == 0) symbol_.set_value(SYMBOL::NAME::ANS, a);
				auto b = unit_(a);
				disp_(b);
			} else {
				out_func_("Fail: ");
				out_func_(cmd);
				out_func_("\n");
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


		//-------------------------------------------------------------//
		/*!
			@brief  unit クラスへの参照
			@return	unit クラス
		*/
		//-------------------------------------------------------------//
		auto& at_unit() { return unit_; }
	};
}
