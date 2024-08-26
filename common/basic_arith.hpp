#pragma once
//=====================================================================//
/*!	@file
	@brief	Arithmetic テンプレート @n
			- テキストの数式を展開して、計算結果を得る。 @n
			- 0x, 0X で１６進数と認識する @n
			- 0b, 0B で２進数と認識する @n
			- A-Z、a-z、_ などがある場合、シンボル、又は関数と認識する
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2015, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include "bitset.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	Arithmetic クラス
		@param[in]	NVAL	基本型
		@param[in]	SYMBOL	変数クラス型
		@param[in]	FUNC	関数クラス型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class NVAL, class SYMBOL, class FUNC>
	struct basic_arith {

		static constexpr uint32_t NUMBER_NUM = 50;  	///< 最大桁数
		static constexpr uint32_t NEST_MAX   = 20;  	///< 最大ネスト深度
		static constexpr uint8_t CODE_SYM    = 0x80;	///< 変数の短縮コード（64個）
		static constexpr uint8_t CODE_FUNC   = 0xC0;	///< 関数の短縮コード（64個）

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	エラー・タイプ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class error : uint8_t {
			fatal,				///< エラー
			buffer_fatal,		///< バッファーに関するエラー
			number_fatal,		///< 数字の変換に関するエラー
			binary_fatal,		///< ２進データの変換に関するエラー
			hexadecimal_fatal,	///< １６進データの変換に関するエラー
			zero_divide,		///< ０除算エラー
			nest_fatal,			///< 深度が制限を超えたエラー
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

		uint32_t	nest_;


		// 関数内パラメーターの取得
		bool param_(char* dst, uint32_t len) noexcept
		{
			if(ch_ != '(') return false;

			while(ch_ != 0) {
				--len;
				if(len == 0) break;
			}

			return true;
		}


		void func_sub_(typename FUNC::NAME fc, NVAL& nval)
		{
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
		}


		NVAL number_() noexcept
		{
			++nest_;
			if(nest_ >= NEST_MAX) {
				error_.set(error::nest_fatal);
			}

			bool minus = false;

			// 符号、反転の判定
			if(ch_ == '-') {
				minus = true;
				ch_ = *tx_++;
			} else if(ch_ == '+') {
				ch_ = *tx_++;
			}

			NVAL nval;
			if((ch_ >= '0' && ch_ <= '9') || ch_ == '.' || ch_ == '(') {  // 数値のチェック

			} else if(static_cast<uint8_t>(ch_) <= 0x7f) {  // 通常の文字列の場合
				typename SYMBOL::NAME sc;
				auto tmp = symbol_.get_code(tx_ - 1, sc);
				if(sc == SYMBOL::NAME::NONE) ;
				else if(SYMBOL::probe(sc)) {
					if(symbol_(sc, nval)) {
						tx_ = tmp;
						ch_ = *tx_++;
						if(minus) { nval = -nval; }
						return nval;
					}
				} else {
					tx_ = tmp;
					func_sub_(static_cast<typename FUNC::NAME>(sc), nval);
					if(minus) { nval = -nval; }
					return nval;
				}
				error_.set(error::symbol_fatal);
				return nval;
			} else if(static_cast<uint8_t>(ch_) >= CODE_SYM) {  // 短縮コード symbol, func
				if(static_cast<uint8_t>(ch_) >= CODE_FUNC) {  // func ?
					auto fc = static_cast<typename FUNC::NAME>(ch_);
					func_sub_(fc, nval);
				} else {  // to symbol
					if(symbol_(static_cast<typename SYMBOL::NAME>(ch_), nval)) {
						ch_ = *tx_++;
					} else {
						error_.set(error::symbol_fatal);
					}
				}
				if(minus) { nval = -nval; }
				return nval;
			} else {
				error_.set(error::number_fatal);
			}

			if(error_() != 0) {

			} else if(ch_ == '(') {
				nval = factor_();
			} else {  // 0 - 9 .
				char tmp[NUMBER_NUM];
				uint32_t idx = 0;
				auto base = NVAL::BASE::DEC;
				char back = 0;
				do {
					if(ch_ == '+' || ch_ == '-') {
						if(base == NVAL::BASE::DEC && (back == 'E' || back == 'e')) {
							tmp[idx] = ch_;
							++idx;
						} else {
							break;
						}
					} else if(ch_ == '*' || ch_ == '/' || ch_ == ')' || ch_ == '^') {
						break;
					} else {
						if(idx == 1 && back == '0') {
							if(ch_ == 'X' || ch_ == 'x') {
								base = NVAL::BASE::HEX;
								ch_ = *tx_++;
								continue;
							} else if(ch_ == 'B' || ch_ == 'b') {
								base = NVAL::BASE::BIN;
								ch_ = *tx_++;
								continue;
							}
						}
						if(base == NVAL::BASE::DEC) {
							if((ch_ >= '0' && ch_ <= '9') || ch_=='.' || ch_=='e' || ch_=='E') {
								tmp[idx] = ch_;
								idx++;
							} else {
								error_.set(error::number_fatal);
								break;
							}
						} else if(base == NVAL::BASE::HEX) {
							if((ch_ >= '0' && ch_ <= '9') || (ch_ >= 'A' && ch_ <= 'F')
								|| (ch_ >= 'a' && ch_ <= 'f') || ch_ == '.') {
								tmp[idx] = ch_;
								idx++;
							} else {
								error_.set(error::number_fatal);
								break;
							}
						} else if(base == NVAL::BASE::BIN) {
							if(ch_ == '0' || ch_ == '1' || ch_ == '.') {
								tmp[idx] = ch_;
								idx++;
							} else {
								error_.set(error::number_fatal);
								break;
							}
						}
					}
					if(idx >= (NUMBER_NUM - 1)) {
						error_.set(error::buffer_fatal);
						break;
					}
					back = ch_;
					ch_ = *tx_++;
				} while(ch_ != 0) ;
				tmp[idx] = 0;
				if(error_() == 0) {
					nval.assign(tmp, base);
				}
			}
			if(minus) { nval = -nval; }
			return nval;
		}


		auto factor_() noexcept
		{
			++nest_;
			if(nest_ >= NEST_MAX) {
				error_.set(error::nest_fatal);
			}
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
			}
			return v;
		}


		NVAL term_() noexcept
		{
			++nest_;
			if(nest_ >= NEST_MAX) {
				error_.set(error::nest_fatal);
			}
			NVAL v = factor_();
			while(error_() == 0) {
				switch(ch_) {
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
						auto tmp = factor_();
						if(tmp == 0) {
							error_.set(error::zero_divide);
							break;
						}
					} else {
						auto tmp = factor_();
						if(tmp == 0) {
							error_.set(error::zero_divide);
							break;
						}
						v /= tmp;
					}
					break;
				case '^':
					ch_ = *tx_++;
					{
						auto n = factor_();
						v.pow(n);
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


		NVAL expression_() noexcept
		{
			++nest_;
			if(nest_ >= NEST_MAX) {
				error_.set(error::nest_fatal);
			}
			NVAL v = term_();
			while(error_() == 0) {
				switch(ch_) {
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
			@param[in]	symbol	シンボル・クラス（変数）
			@param[in]	func	関数クラス
		*/
		//-----------------------------------------------------------------//
		basic_arith(SYMBOL& symbol, FUNC& func) noexcept : symbol_(symbol), func_(func),
			tx_(nullptr), ch_(0), error_(), value_(), nest_(0)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	解析を開始 @n
					高速化の場合、シンボル名、関数名は修飾コードを使う事が出来る。 @n
					※スペースは取り除く事
			@param[in]	str		解析文字列
			@return	文法にエラーがあった場合、「false」
		*/
		//-----------------------------------------------------------------//
		bool analize(const char* str) noexcept
		{
			if(str == nullptr) {
				error_.set(error::fatal);
				return false;
			}

			tx_ = str;
			error_.clear();
			nest_ = 0;

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
			@brief	エラーを取得
			@return エラー
		*/
		//-----------------------------------------------------------------//
		const error_t& get_error() const noexcept { return error_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	エラーメッセージを取得
			@param[in]	STR	文字列クラス型
			@return エラーメッセージ
		*/
		//-----------------------------------------------------------------//
		template <class STR>
		STR get_error() const noexcept {
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
		bool parse(const char* in, char* out, uint32_t len) const noexcept
		{
			char ch;
			while(len > 1 && (ch = *in++) != 0) {
				auto n = static_cast<uint8_t>(ch);
				if(n < CODE_SYM) {
					*out++ = ch;
					len--;
				} else if(n < CODE_FUNC) {  // シンボル

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
		NVAL operator() () const noexcept { return value_; }
	};
}
