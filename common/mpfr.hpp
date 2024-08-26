#pragma once
//=========================================================================//
/*! @file
    @brief  mpfr ラッパークラス @n
			GNU mpfr の C++ ラッパー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cmath>
#include <mpfr.h>
#include <cstring>
#ifdef EMU
#include "utils/input.hpp"
#else
#include "common/input.hpp"
#endif

namespace mpfr {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  value_base クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct value_base {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  BASE 型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class BASE : uint8_t {
			BIN = 2,
			DEC = 10,
			HEX = 16
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  mpfr オブジェクト
		@param[in]	NUM		有効桁数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t NUM>
	class value : public value_base {

		mpfr_t		t_;
		mpfr_rnd_t	rnd_;

		static inline uint32_t ref_count_;

		void shift_right_(char* org)
		{
			auto l = strlen(org);
			memmove(org + 1, org, l + 1);
		}

		// hex float C99 仕様の指数表示から、指数を除く
		void convert_c99_float_binhex_(char cnv, char* out, uint32_t len) noexcept
		{
			// hex float C99 Style から一般的な 16 進表示へ変換
			int step = 0;
			if(cnv == 'a' || cnv == 'A') {  // 16 進表示
				step = 4;
			} else if(cnv == 'b') {  // 2 進表示
				step = 1;
			} else {
				return;
			}

			char* t = strchr(out, (cnv > 0x60 ? 'p' : 'P'));  // 指数表示ポイント
			if(t == nullptr) {
				return;
			}
			int num = 0;
			if(!(utils::input("%d", t + 1) % num).status()) {  // 指数の取得
				return;
			}
			char* p = strchr(out, '.');
			if(num >= 0) {  // 指数がプラス
				if(p == nullptr) {  // '.' が無い場合 '0' を追加
					while(num > 0) {
						*t++ = '0';
						num -= step;
					}
					*t = 0;
				} else {  // 小数点を右に動かす
					*t = 0;
					while(num > 0) {
						if(p[1] != 0) {
							*p = p[1];
							p[1] = '.';
						} else {  // 小数点が終端なら’０’を足す
							*p = '0';
							p[1] = '.';
							p[2] = 0;
						}
						++p;
						num -= step;
					}
					if(p[0] == '.' && p[1] == 0) p[0] = 0;
				}
			} else if(num < 0) {  // 指数がマイナス
				if(p == nullptr) {  // '.' が無い場合 ’０’ を追加
					*t = 0;
					--t;
					shift_right_(t);
					*t = '.';
					shift_right_(t);
					*t = '0';
					num += step;
					t += 2;
					while(num < 0) {
						shift_right_(t);
						*t = '0';
						num += step;
					}
				} else {  // 小数点を左に動かす
					*t = 0;
					--p;
					p[1] = p[0];
					p[0] = '.';
					shift_right_(p);
					*p = '0';
					num += step;
					p += 2;
					while(num < 0) {
						shift_right_(p);
						*p = '0';
						num += step;
					}
				}
			}
		}

		static void zerosup_(char* org, char ech) noexcept
		{
			// 指数表示の場合スルー
			if(strrchr(org, ech) != nullptr) return;

			// 小数点が無い場合スルー
			if(strrchr(org, '.') == nullptr) return;

			auto l = strlen(org);
			while(l > 0) {
				--l;
				if(org[l] != '0') break;
				else {
					org[l] = 0;
				}
			}
			if(l > 0) {
				if(org[l] == '.') {
					org[l] = 0;
				}
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	rnd	丸めパラメータ
		*/
		//-----------------------------------------------------------------//
		value(mpfr_rnd_t rnd = MPFR_RNDN) noexcept : t_(), rnd_(rnd)
		{
			mpfr_init2(t_, NUM);
			++ref_count_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	rnd	丸めパラメータ
		*/
		//-----------------------------------------------------------------//
		value(const value& t, mpfr_rnd_t rnd = MPFR_RNDN) noexcept : rnd_(rnd)
		{
			mpfr_init2(t_, NUM);
			mpfr_set(t_, t.t_, rnd_);
			++ref_count_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター(int)
			@param[in]	iv	初期値
			@param[in]	rnd	丸めパラメータ
		*/
		//-----------------------------------------------------------------//
		explicit value(int iv, mpfr_rnd_t rnd = MPFR_RNDN) noexcept : rnd_(rnd)
		{
			mpfr_init2(t_, NUM);
			mpfr_set_si(t_, iv, rnd);
			++ref_count_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター(float)
			@param[in]	iv	初期値
			@param[in]	rnd	丸めパラメータ
		*/
		//-----------------------------------------------------------------//
		explicit value(float iv, mpfr_rnd_t rnd = MPFR_RNDN) noexcept : rnd_(rnd)
		{
			mpfr_init2(t_, NUM);
			mpfr_set_flt(t_, iv, rnd);
			++ref_count_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター(double)
			@param[in]	iv	初期値
			@param[in]	rnd	丸めパラメータ
		*/
		//-----------------------------------------------------------------//
		explicit value(double iv, mpfr_rnd_t rnd = MPFR_RNDN) noexcept : rnd_(rnd)
		{
			mpfr_init2(t_, NUM);
			mpfr_set_d(t_, iv, rnd);
			++ref_count_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター(文字列)
			@param[in]	iv	初期値
			@param[in]	rnd	丸めパラメータ
		*/
		//-----------------------------------------------------------------//
		explicit value(const char* iv, mpfr_rnd_t rnd = MPFR_RNDN) noexcept : rnd_(rnd)
		{
			mpfr_init2(t_, NUM);
			mpfr_set_str(t_, iv, 10, rnd);
			++ref_count_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  デストラクター
		*/
		//-----------------------------------------------------------------//
		~value()
		{
			mpfr_clear(t_);
			--ref_count_;
			if(ref_count_ == 0) {
				mpfr_free_cache();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  mpfr_ptr を取得
			@return mpfr_ptr
		*/
		//-----------------------------------------------------------------//
		mpfr_ptr get() noexcept { return t_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  mpfr_rnd_t を取得
			@return mpfr_rnd_t
		*/
		//-----------------------------------------------------------------//
		auto get_rnd() const noexcept { return rnd_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  円周率を取得
			@return 円周率
		*/
		//-----------------------------------------------------------------//
		static const auto get_pi() noexcept
		{
			value tmp;
			mpfr_const_pi(tmp.t_, tmp.get_rnd());
			return tmp;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ２の自然対数を取得
			@return ２の自然対数
		*/
		//-----------------------------------------------------------------//
		static const auto get_log2() noexcept
		{
			value tmp;
			mpfr_const_log2(tmp.t_, tmp.get_rnd());
			return tmp;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  Euler数を取得
			@return Euler数
		*/
		//-----------------------------------------------------------------//
		static const auto get_euler() noexcept
		{
			value tmp;
			mpfr_const_euler(tmp.t_, tmp.get_rnd());
			return tmp;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	数値文字列の入力
			@param[in]	str		数値文字列
			@param[in]	base	基底数
		*/
		//-----------------------------------------------------------------//
		void assign(const char* str, BASE base = BASE::DEC) noexcept
		{
			mpfr_set_str(t_, str, static_cast<int>(base), rnd_);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  整数部と小数部の分離
			@param[in]	src	ソース
			@param[out]	iop	整数部
			@param[out]	fop	小数部
		*/
		//-----------------------------------------------------------------//
		static void fmod(const value& src, value& iop, value& fop) noexcept
		{
			mpfr_modf(iop.t_, fop.t_, src.t_, fop.get_rnd());
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  整数除算(x/y)における余り
			@param[in]	x	分子
			@param[in]	y	分母
			@param[out]	m	余り
		*/
		//-----------------------------------------------------------------//
		static void mod(const value& x, const value& y, value& m) noexcept
		{
			mpfr_fmod(m.t_, x.t_, y.t_, m.get_rnd());
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	絶対値
			@param[in]	in	入力
			@return	in に対する絶対値
		*/
		//-----------------------------------------------------------------//
		static value abs(const value& in) noexcept
		{
			value out;
			mpfr_abs(out.t_, in.t_, in.rnd_);
			return out;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	整数部（round、丸め付き）
			@param[in]	in	入力
			@return	in に対する絶対値
		*/
		//-----------------------------------------------------------------//
		static value rint(const value& in) noexcept
		{
			value out;
			mpfr_rint(out.t_, in.t_, in.rnd_);
			return out;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	小数部
			@param[in]	in	入力
			@return	in に対する絶対値
		*/
		//-----------------------------------------------------------------//
		static value frac(const value& in) noexcept
		{
			value out;
			mpfr_frac(out.t_, in.t_, in.rnd_);
			return out;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	べき乗 (this = this ^ n)
			@param[in]	n	n 乗
		*/
		//-----------------------------------------------------------------//
		void pow(const value& n) noexcept
		{
			mpfr_pow(t_, t_, n.t_, rnd_);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  交換
			@param[in]	th	交換クラス
		*/
		//-----------------------------------------------------------------//
		void swap(value& th) noexcept
		{
			mpfr_swap(t_, th.t_);
		}


		bool operator == (int v) const noexcept { return mpfr_cmp_si(t_, v) == 0; }
		bool operator != (int v) const noexcept { return mpfr_cmp_si(t_, v) != 0; }
		bool operator == (long v) const noexcept { return mpfr_cmp_si(t_, v) == 0; }
		bool operator != (long v) const noexcept { return mpfr_cmp_si(t_, v) != 0; }
		bool operator == (double v) const noexcept { return mpfr_cmp_d(t_, v) == 0; }
		bool operator != (double v) const noexcept { return mpfr_cmp_d(t_, v) != 0; }


		value& operator = (const value& th) noexcept {
			mpfr_set(t_, th.t_, rnd_);
			return *this;
		}
		value& operator = (long v) noexcept {
			mpfr_set_si(t_, v, rnd_);
			return *this;
		}	
		value& operator = (double v) noexcept {
			mpfr_set_d(t_, v, rnd_);
			return *this;
		}


		const value operator - () noexcept
		{
			value tmp(*this);
			mpfr_neg(tmp.t_, tmp.t_, rnd_);
			return tmp;
		}


		value& operator += (const value& th) noexcept
		{
			mpfr_add(t_, t_, th.t_, rnd_);
			return *this;
		}

		value& operator -= (const value& th) noexcept
		{
			mpfr_sub(t_, t_, th.t_, rnd_);
			return *this;
		}

		value& operator *= (const value& th) noexcept
		{
			mpfr_mul(t_, t_, th.t_, rnd_);
			return *this;
		}

		value& operator /= (const value& th) noexcept
		{
			mpfr_div(t_, t_, th.t_, rnd_);
			return *this;
		}

		value operator + (const value& th) const noexcept { return value(*this) += th; }
		value operator - (const value& th) const noexcept { return value(*this) -= th; }
		value operator * (const value& th) const noexcept { return value(*this) *= th; }
		value operator / (const value& th) const noexcept { return value(*this) /= th; }


		//-----------------------------------------------------------------//
		/*!
			@brief  数値文字列を取得
			@param[in]	upn		小数点以下の文字数
			@param[out]	out		格納文字列ポインター
			@param[in]	len		格納文字列数
			@param[in]	cnv		変換文字（a, A, b, f, F） @n
								a: hexadecimal @n
								A: HEXADECIMAL @n
								b: binary @n
								f: decimal @n
								F: DECIMAL
		*/
		//-----------------------------------------------------------------//
		void operator() (int upn, char* out, uint32_t len, char cnv = 'f') noexcept
		{
			char form[16];
			char ech;
			if(cnv == 'a' || cnv == 'A' || cnv == 'b') {  // Bin, Hex
				utils::sformat("%%RN%c", form, sizeof(form)) % cnv;
				ech = 'p';
			} else {
				utils::sformat("%%.%dRN%c", form, sizeof(form)) % upn % cnv;
				ech = 'e';
			}
//			mpfr_snprintf(out, len, "%.50RNf", t_);
			auto p = out;
			auto l = len;
			if(cnv == 'b') {
				p += 2;
				l -= 2;
			}

			mpfr_snprintf(p, l, form, t_);

			if(cnv == 'b') {  // 二進数では、"0b" を追加
				if(p[0] == '-' || p[0] == '+') {
					out[0] = p[0];
					out[1] = '0';
					out[2] = 'b';
				} else {
					out[0] = '0';
					out[1] = 'b';
				}
			} else if(cnv == 'A') {  // １６進で "0X" を "0x" に変換
				if(p[0] == '-' || p[1] == '+') {
					if(p[2] == 'X') p[2] = 'x';
				} else {
					if(p[1] == 'X') p[1] = 'x';
				}
			}

			convert_c99_float_binhex_(cnv, out, len);
			zerosup_(out, ech);
		}


		/// 三角関数 sin
		static value sin(const value& in) noexcept
		{
			value out;
			mpfr_sin(out.t_, in.t_, out.get_rnd());
			return out;
		}

		/// 三角関数 asin
		static value asin(const value& in) noexcept
		{
			value out;
			mpfr_asin(out.t_, in.t_, out.get_rnd());
			return out;
		}

		/// 三角関数 sinh
		static value sinh(const value& in) noexcept
		{
			value out;
			mpfr_sinh(out.t_, in.t_, out.get_rnd());
			return out;
		}

		/// 三角関数 asinh
		static value asinh(const value& in) noexcept
		{
			value out;
			mpfr_asinh(out.t_, in.t_, out.get_rnd());
			return out;
		}

		/// 三角関数 cos
		static value cos(const value& in) noexcept
		{
			value out;
			mpfr_cos(out.t_, in.t_, out.get_rnd());
			return out;
		}

		/// 三角関数 acos
		static value acos(const value& in) noexcept
		{
			value out;
			mpfr_acos(out.t_, in.t_, out.get_rnd());
			return out;
		}

		/// 三角関数 cosh
		static value cosh(const value& in) noexcept
		{
			value out;
			mpfr_cosh(out.t_, in.t_, out.get_rnd());
			return out;
		}

		/// 三角関数 acosh
		static value acosh(const value& in) noexcept
		{
			value out;
			mpfr_acosh(out.t_, in.t_, out.get_rnd());
			return out;
		}

		/// 三角関数 tan
		static value tan(const value& in) noexcept
		{
			value out;
			mpfr_tan(out.t_, in.t_, out.get_rnd());
			return out;
		}

		/// 三角関数 atan
		static value atan(const value& in) noexcept
		{
			value out;
			mpfr_atan(out.t_, in.t_, out.get_rnd());
			return out;
		}

		/// 三角関数 tanh
		static value tanh(const value& in) noexcept
		{
			value out;
			mpfr_tanh(out.t_, in.t_, out.get_rnd());
			return out;
		}

		/// 三角関数 atanh
		static value atanh(const value& in) noexcept
		{
			value out;
			mpfr_atanh(out.t_, in.t_, out.get_rnd());
			return out;
		}

		/// 指数積分 eint
		static value eint(const value& in) noexcept
		{
			value out;
			mpfr_eint(out.t_, in.t_, out.get_rnd());
			return out;
		}

		/// 対数（基数 10）
		static value log10(const value& in) noexcept
		{
			value out;
			mpfr_log10(out.t_, in.t_, out.get_rnd());
			return out;
		}

		/// 自然対数
		static value log(const value& in) noexcept
		{
			value out;
			mpfr_log(out.t_, in.t_, out.get_rnd());
			return out;
		}

		/// スクエア・ルート
		static value sqrt(const value& in) noexcept
		{
			value out;
			mpfr_sqrt(out.t_, in.t_, out.get_rnd());
			return out;
		}

		/// エキスポーネント（基数：10）
		static value exp10(const value& in) noexcept
		{
			value out;
			mpfr_exp10(out.t_, in.t_, out.get_rnd());
			return out;
		}

		/// ガンマ関数（Gamma）
		static value gamma(const value& in) noexcept
		{
			value out;
			mpfr_gamma(out.t_, in.t_, out.get_rnd());
			return out;
		}

		/// ゼータ関数（Riemann Zeta）
		static value zeta(const value& in) noexcept
		{
			value out;
			mpfr_zeta(out.t_, in.t_, out.get_rnd());
			return out;
		}
	};
}
