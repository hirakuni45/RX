#pragma once
//=====================================================================//
/*!	@file
	@brief	Arithmetic テンプレート @n
			※テキストの数式を展開して、計算結果を得る。@n
			NVAL には、Boost Multiprecision Library を利用する事を前提にしている。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2015, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include "common/bitset.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	Arithmetic クラス
		@param[in]	NVAL	基本型
		@param[in]	SYMBOL	変数クラス
		@param[in]	FUNC	関数クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class NVAL, class SYMBOL, class FUNC>
	struct basic_arith {

		static const uint32_t NUMBER_NUM = 50;  // 最大桁数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	エラー・タイプ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class error : uint8_t {
			fatal,				///< エラー
			number_fatal,		///< 数字の変換に関するエラー
			zero_divide,		///< ０除算エラー
			binary_fatal,		///< ２進データの変換に関するエラー
			octal_fatal,		///< ８進データの変換に関するエラー
			hexdecimal_fatal,	///< １６進データの変換に関するエラー
			num_fatal,			///< 数値の変換に関するエラー
			symbol_fatal,		///< シンボルデータの変換に関するエラー
			func_fatal,			///< 関数の変換に関するエラー
		};

		typedef bitset<uint16_t, error> error_t;

	private:

		SYMBOL&		symbol_;
		FUNC&		func_;

		const char*		tx_;
		char			ch_;

		error_t		error_;

		NVAL		value_;


		// スペース、TAB を取り除く
		void skip_space_() noexcept
		{
			while(ch_ == ' ' || ch_ == '\t') {
				ch_ = *tx_++;
			}
		}


		// 関数内パラメーターの取得
		bool param_(char* dst, uint32_t len)
		{
			if(ch_ != '(') return false;

			while(ch_ != 0) {
				--len;
				if(len == 0) break;
			}

			return true;
		}


		NVAL number_()
		{
			bool minus = false;
			char tmp[NUMBER_NUM];

			skip_space_();

			// 符号、反転の判定
			if(ch_ == '-') {
				minus = true;
				ch_ = *tx_++;
			} else if(ch_ == '+') {
				ch_ = *tx_++;
			}

			skip_space_();

			NVAL nval;
			if(static_cast<uint8_t>(ch_) >= 0x80) {  // symbol?, func?
				if(static_cast<uint8_t>(ch_) >= 0xC0) {  // func ?
					auto fc = static_cast<typename FUNC::NAME>(ch_);
					ch_ = *tx_++;
					if(ch_ == '(') {
						ch_ = *tx_++;
						auto param = expression_();
						if(ch_ == ')') {
							ch_ = *tx_++;
							if(!func_(fc, param, nval)) {
								error_.set(error::func_fatal);
							}
						} else {
							error_.set(error::fatal);
						}
					} else {
						error_.set(error::func_fatal);
					}
				} else {  // to symbol
					if(symbol_(static_cast<typename SYMBOL::NAME>(ch_), nval)) {
						ch_ = *tx_++;	
					} else {
						error_.set(error::symbol_fatal);
					}
				}
				if(minus) { nval = -nval; }
				return nval;
			}

			if(ch_ == '(') {
				nval = factor_();
			} else {
				uint32_t idx = 0;
				while(ch_ != 0) {
					if(ch_ == ' ' || ch_ == '\t') continue;
					else if(ch_ == '+') break;
					else if(ch_ == '-') break;
					else if(ch_ == '*') break;
					else if(ch_ == '/') break;
					else if(ch_ == ')') break;
					else if(ch_ == '^') break;
					else if((ch_ >= '0' && ch_ <= '9') || ch_=='.' || ch_=='e' || ch_=='E') {
						tmp[idx] = ch_;
						idx++;
					} else {
						error_.set(error::fatal);
						break;
					}
					ch_ = *tx_++;
				}
				tmp[idx] = 0;
				if(error_() == 0) {
					nval.assign(tmp);
				}
			}

			if(minus) { nval = -nval; }

			return nval;
		}


		auto factor_()
		{
			NVAL v(0);
			if(ch_ == '(') {
				ch_ = *tx_++;
				v = expression_();
				if(ch_ == ')') {
					ch_ = *tx_++;
				} else {
					error_.set(error::fatal);
				}
			} else {
				v = number_();
				if(ch_ == '^') {  // べき乗
					ch_ = *tx_++;
					auto n = number_();
					v.pow(n);
				}
			}
			return v;
		}


		NVAL term_() {
			NVAL v = factor_();
			NVAL tmp;
			while(error_() == 0) {
				switch(ch_) {
				case ' ':
				case '\t':
					ch_ = *tx_++;
					break;
				case '*':
					ch_ = *tx_++;
					v *= factor_();
					break;
#if 0
				case '%':
					ch_ = *tx_++;
					tmp = factor_();
					if(tmp == 0) {
						error_.set(error::zero_divide);
						break;
					}
					v %= tmp;
					break;
#endif
				case '/':
					ch_ = *tx_++;
					if(ch_ == '/') {
						ch_ = *tx_++;
						tmp = factor_();
						if(tmp == 0) {
							error_.set(error::zero_divide);
							break;
						}
					} else {
						tmp = factor_();
						if(tmp == 0) {
							error_.set(error::zero_divide);
							break;
						}
						v /= tmp;
					}
					break;
#if 0
				case '<':
					ch_ = *tx_++;
					if(ch_ == '<') {
						ch_ = *tx_++;
						v <<= factor_();
					} else {
						error_.set(error::fatal);
					}
					break;
				case '>':
					ch_ = *tx_++;
					if(ch_ == '>') {
						ch_ = *tx_++;
						v <<= factor_();
					} else {
						error_.set(error::fatal);
					}
					break;
#endif
				default:
					return v;
					break;
				}
			}
			return v;
		}


		NVAL expression_() {
			NVAL v = term_();
			while(error_() == 0) {
				switch(ch_) {
				case ' ':
				case '\t':
					ch_ = *tx_++;
					break;
				case '+':
					ch_ = *tx_++;
					v += term_();
					break;
				case '-':
					ch_ = *tx_++;
					v -= term_();
					break;
#if 0
				case '&':
					ch_ = *tx_++;
					v &= term_();
					break;
				case '^':
					ch_ = *tx_++;
					v ^= term_();
					break;
				case '|':
					ch_ = *tx_++;
					v |= term_();
					break;
#endif
				default:
					return v;
					break;
				}
			}
			return v;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	func	関数クラス
		*/
		//-----------------------------------------------------------------//
		basic_arith(SYMBOL& symbol, FUNC& func) noexcept : symbol_(symbol), func_(func),
			tx_(nullptr), ch_(0), error_(), value_()
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	解析を開始
			@param[in]	text	解析テキスト
			@return	文法にエラーがあった場合、「false」
		*/
		//-----------------------------------------------------------------//
		bool analize(const char* text)
		{
			if(text == nullptr) {
				error_.set(error::fatal);
				return false;
			}
			tx_ = text;

			error_.clear();

			ch_ = *tx_++;
			if(ch_ != 0) {
				value_ = expression_();
			} else {
				error_.set(error::fatal);
			}

			if(error_() != 0) {
				return false;
			} else if(ch_ != 0) {
				error_.set(error::fatal);
				return false;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	エラーを受け取る
			@return エラー
		*/
		//-----------------------------------------------------------------//
		const error_t& get_error() const { return error_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	エラーメッセージを取得
			@return エラーメッセージ
		*/
		//-----------------------------------------------------------------//
		template <class STR>
		STR get_error() const {
			STR str;
			return str;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	埋め込まれた、シンボル、関数名を展開
			@param[in]	in		入力文字列
			@param[out]	out		展開文字列
			@param[in]	len		展開文字列サイズ
			@return	成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool parse(const char* in, char* out, uint32_t len) const
		{
			char ch;
			while(len > 1 && (ch = *in++) != 0) {
				uint8_t n = static_cast<uint8_t>(ch);
				if(n < 0x80) {
					*out++ = ch;
					len--;
				} else if(n < 0xc0) {  // シンボル

				} else {  // 関数

				}
			}
			*out = 0;
			return len > 1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	() で結果を取得
			@return	結果
		*/
		//-----------------------------------------------------------------//
		NVAL operator() () const { return value_; }
	};
}
