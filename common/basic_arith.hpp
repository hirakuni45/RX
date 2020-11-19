#pragma once
//=====================================================================//
/*!	@file
	@brief	Arithmetic テンプレート @n
			※テキストの数式を展開して、計算結果を得る。@n
			演算式解析
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2015, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/R8C/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include "common/bitset.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	Arithmetic クラス
		@param[in]	VTYPE	基本型
		@param[in]	SYMBOL	シンボルクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <typename VTYPE>
	struct basic_arith {

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
		};

		typedef bitset<uint16_t, error> error_t;

	private:

		const char*		tx_;
		char			ch_;

		error_t		error_;

		VTYPE		value_;

		void skip_space_() {
			while(ch_ == ' ' || ch_ == '\t') {
				ch_ = *tx_++;
			}
		}

		VTYPE number_() {
			bool inv = false;
///			bool neg = false;
			bool point = false;
			int32_t v = 0;
			uint32_t fp = 0;
			uint32_t fs = 1;

			skip_space_();

			// 符号、反転の判定
			if(ch_ == '-') {
				inv = true;
				ch_ = *tx_++;
			} else if(ch_ == '+') {
				ch_ = *tx_++;
//			} else if(ch_ == '!' || ch_ == '~') {
//				neg = true;
//				ch_ = *tx_++;
			}

			skip_space_();

			if(ch_ == '(') {
				v = factor_();
			} else {
				skip_space_();

//				if(ch_ >= 'A' && ch_ <= 'Z') symbol = true;
//				else if(ch_ >= 'a' && ch_ <= 'z') symbol = true;
//				else if(ch_ == '_' || ch_ == '?') symbol = true;

				while(ch_ != 0) {
					if(ch_ == '+') break;
					else if(ch_ == '-') break;
					else if(ch_ == '*') break;
					else if(ch_ == '/') break;
//					else if(ch_ == '&') break;
//					else if(ch_ == '^') break;
//					else if(ch_ == '|') break;
//					else if(ch_ == '%') break;
					else if(ch_ == ')') break;
//					else if(ch_ == '<') break;
//					else if(ch_ == '>') break;
//					else if(ch_ == '!') break;
//					else if(ch_ == '~') break;
					else if(ch_ == '.') {
						if(point) {
							error_.set(error::fatal);
							break;
						} else {
							point = true;
						}
					} else if(ch_ >= '0' && ch_ <= '9') {
						if(point) {
							fp *= 10;
							fp += ch_ - '0';
							fs *= 10;
						} else {
							v *= 10;
							v += ch_ - '0';
						}
					} 
					ch_ = *tx_++;
				}

#if 0
				if(symbol) {
					symbol_map_cit cit = symbol_.find(sym);
					if(cit != symbol_.end()) {
						v = (*cit).second;
					} else {
						error_.set(error::symbol_fatal);
					}
				}
#endif
			}

			if(inv) { v = -v; }
///			if(neg) { v = ~v; }
			if(point) {
				return static_cast<VTYPE>(v) + static_cast<VTYPE>(fp) / static_cast<VTYPE>(fs);
			} else {
				return static_cast<VTYPE>(v);
			}
		}


		VTYPE factor_() {
			VTYPE v = 0;
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
			}
			return v;
		}


		VTYPE term_() {
			VTYPE v = factor_();
			VTYPE tmp;
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
///						v %= tmp;
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


		VTYPE expression_() {
			VTYPE v = term_();
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
		*/
		//-----------------------------------------------------------------//
		basic_arith() : tx_(nullptr), ch_(0), error_(), value_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	解析を開始
			@param[in]	text	解析テキスト
			@return	文法にエラーがあった場合、「false」
		*/
		//-----------------------------------------------------------------//
		bool analize(const char* text) {
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
			@brief	結果を取得
			@return	結果
		*/
		//-----------------------------------------------------------------//
		VTYPE get() const { return value_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	() で結果を取得
			@return	結果
		*/
		//-----------------------------------------------------------------//
		VTYPE operator() () const { return value_; }
	};
}
