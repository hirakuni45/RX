#pragma once
//=====================================================================//
/*! @file
    @brief  簡易 format クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <unistd.h>

/// ８進数のサポート
/// #define WITH_OCTAL_FORMAT
/// 浮動小数点(float)のサポート
/// #define WITH_FLOAT_FORMAT
/// 浮動小数点(double)のサポート
/// #define WITH_DOUBLE_FORMAT

/// エラーのメッセージ出力
// #define ERROR_MESSAGE

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  エラー・ケース
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct error_case {
		enum type {
			NULL_PTR,		///< 無効なポインター
			UNKNOWN_TYPE,	///< 不明な「型」
			DIFFERENT_TYPE,	///< 違う「型」
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  エラー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class OUT>
	class error {
#ifdef ERROR_MESSAGE
		OUT		out_;
		void str_(const char* str) {
			char ch;
			while((ch = *str++) != 0) {
				out_(ch);
			}
		}
#endif
	public:
		void operator() (error_case::type t) {
#ifdef ERROR_MESSAGE
			if(t == error_case::UNKNOWN_TYPE) {
				str_("Unknown type\n");
			} else if(t == error_case::DIFFERENT_TYPE) {
				str_("Different type\n");
			}
#endif
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  簡易 format クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class OUT, class ERR = error<OUT> >
	class format {

		enum mode {
			CHA,		///< 文字
			STR,		///< 文字列
			BINARY,		///< ２進
#ifdef WITH_OCTAL_FORMAT
			OCTAL,		///< ８進
#endif
			DECIMAL,	///< １０進
			U_DECIMAL,	///< １０進（符号無し）
			HEX_CAPS,	///< １６進（大文字）
			HEX,		///< １６進（小文字）
			FIXED_REAL,	///< 固定小数点
#if defined(WITH_FLOAT_FORMAT) | defined(WITH_DOUBLE_FORMAT)
			REAL,		///< 浮動小数点
			EXPONENT,	///< 浮動小数点 exp 形式
			REAL_AUTO,	///< 浮動小数点自動
#endif
			NONE_		///< 不明
		};

		OUT			out_;	///< 出力関数クラス
		ERR			err_;	///< エラー関数クラス

		const char*	form_;

		uint8_t		real_;
		uint8_t		decimal_;
		uint8_t		ppos_;
		uint8_t		mode_;
		bool		zerosupp_;
		bool		sign_;

		void reset_() {
			real_ = 0;
			decimal_ = 0;
			ppos_ = 0;
			zerosupp_ = false;
			sign_ = false;
			mode_ = mode::NONE_;
		}

		void next_() {
			if(form_ == 0) {
				err_(error_case::NULL_PTR);
				return;
			}
			char ch;
			bool fm = false;
			bool point = false;
			bool ppos = false;
			uint8_t n = 0;
			while((ch = *form_++) != 0) {
				if(fm) {
					if(ch == '+') {
						sign_ = true;
					} else if(ch >= '0' && ch <= '9') {
						if(n == 0 && ch == '0') {
							zerosupp_ = true;
						} else if(point || ppos) {
							if(point) {
								decimal_ *= 10;
								decimal_ += static_cast<uint8_t>(ch - '0');
							} else {
								ppos_ *= 10;
								ppos_ += static_cast<uint8_t>(ch - '0');
							}
						} else {
							real_ *= 10;
							real_ += static_cast<uint8_t>(ch - '0');
						}
						++n;
					} else if(ch == '.') {
						ppos = false;
						point = true;
					} else if(ch == ':') {
						ppos = true;
						point = false;
					} else if(ch == 's') {
						mode_ = mode::STR;
						return;
					} else if(ch == 'c') {
						mode_ = mode::CHA;
						return;
					} else if(ch == 'b') {
						mode_ = mode::BINARY;
						return;
#ifdef WITH_OCTAL_FORMAT
					} else if(ch == 'o') {
						mode_ = mode::OCTAL;
						return;
#endif
					} else if(ch == 'd') {
						mode_ = mode::DECIMAL;
						return;
					} else if(ch == 'u') {
						mode_ = mode::U_DECIMAL;
						return;
					} else if(ch == 'x') {
						mode_ = mode::HEX;
						return;
					} else if(ch == 'X') {
						mode_ = mode::HEX_CAPS;
						return;
					} else if(ch == 'y') {
						mode_ = mode::FIXED_REAL;
						return;
#if defined(WITH_FLOAT_FORMAT) | defined(WITH_DOUBLE_FORMAT)
					} else if(ch == 'f' || ch == 'F') {
						mode_ = mode::REAL;
						return;
					} else if(ch == 'e' || ch == 'E') {
						mode_ = mode::EXPONENT;
						return;
					} else if(ch == 'g' || ch == 'G') {
						mode_ = mode::REAL_AUTO;
						return;
#endif
					} else if(ch == '%') {
						out_(ch);
						fm = false;
					} else {
						err_(error_case::UNKNOWN_TYPE);
						return;
					}
				} else if(ch == '%') {
					fm = true;
				} else {
					out_(ch);
				}
			}
		}

		void out_s_(const char* str) {
			char ch;
			while((ch = *str++) != 0) {
				out_(ch);
			}
		}

		void out_str_(const char* str, uint8_t n = 0) {
			char ch;
			if(n && n < real_) {
				uint8_t spc = real_ - n;
				while(spc) {
					--spc;
					if(zerosupp_) out_('0');
					else out_(' ');
				}
			}
			out_s_(str);
		}

		void out_bin_(int v) {
			char tmp[34];
			char* p = &tmp[sizeof(tmp) - 1];
			*p = 0;
			uint8_t n = 0;
			do {
				--p;
				*p = (v & 1) + '0';
				v >>= 1;
				++n;
			} while(v != 0) ;
			if(sign_) { --p; ++n; *p = '+'; }
			out_str_(p, n);
		}

#ifdef WITH_OCTAL_FORMAT
		void out_oct_(int v) {
			char tmp[14];
			char* p = &tmp[sizeof(tmp) - 1];
			*p = 0;
			uint8_t n = 0;
			do {
				--p;
				*p = (v & 3) + '0';
				v >>= 3;
				++n;
			} while(v != 0) ;
			if(sign_) { --p; ++n; *p = '+'; }
			out_str_(p, n);
		}
#endif

		void out_dec_(int v) {
			char tmp[12];
			char* p = &tmp[sizeof(tmp) - 1];
			*p = 0;
			uint8_t n = 0;
			char sign = 0;
			if(v < 0) { v = -v; sign = '-'; }
			else if(sign_) { sign = '+'; }
			do {
				--p;
				*p = (v % 10) + '0';
				v /= 10;
				++n;
			} while(v != 0) ;
			if(sign) { --p; ++n; *p = sign; }
			out_str_(p, n);
		}

		void out_dec_(unsigned int v) {
			char tmp[12];
			char* p = &tmp[sizeof(tmp) - 1];
			*p = 0;
			uint8_t n = 0;
			do {
				--p;
				*p = (v % 10) + '0';
				v /= 10;
				++n;
			} while(v != 0) ;
			if(sign_) { --p; ++n; *p = '+'; }
			out_str_(p, n);
		}

		void out_hex_(unsigned int v, char top) {
			char tmp[10];
			char* p = &tmp[sizeof(tmp) - 1];
			*p = 0;
			uint8_t n = 0;
			do {
				--p;
				char ch = v & 15;
				if(ch >= 10) ch += top - 10;
				else ch += '0';
				*p = ch;
				v >>= 4;
				++n;
			} while(v != 0) ;
			if(sign_) { --p; ++n; *p = '+'; }
			out_str_(p, n);
		}

		uint32_t make_mask_(uint8_t num) {
			uint32_t m = 0;
			while(num > 0) {
				m += m;
				++m;
				--num;
			}
			return m;
		}

		void out_fixed_point_(int v, uint8_t fixpoi) {

			out_dec_(v >> fixpoi);
			out_('.');

			uint32_t d;
			if(v < 0) { d = -v; } else { d = v; }
			uint32_t dec = d & make_mask_(fixpoi);

			int l = 0;
			char buff[24];
			if(decimal_ > (sizeof(buff) - 1)) decimal_ = sizeof(buff) - 1;
			while(dec > 0) {
				dec *= 10;
				uint32_t n = dec >> fixpoi;
				buff[l] = n + '0';
				dec -= n << fixpoi;
				++l;
				if(l >= decimal_ || l >= (sizeof(buff) - 1)) break;
			}
			while(l < decimal_) {
				buff[l] = '0';
				++l;
			}
			buff[l] = 0;
			out_s_(buff);
		}

#if 0
e, E
    double 引き数を丸めて [-]d.ddde±dd の形に変換する。 小数点の前には一桁の数字があり、小数点以下の桁数は精度で指定された桁数 になる。精度は指定されなかった場合 6 とみなされる。 精度が 0 の場合には、 小数点以下は表示されない。E 変換では、指数を表現するときに (e で はなく) E が使われる。指数部分は少なくとも 2桁表示される。つまり、 指数の値が 0 の場合には、00 と表示される。 

f, F
    double 引き数を丸めて [-]ddd.ddd の形の10進表現に変換する。 小数点の後の桁数は、精度で指定された値となる。 精度が指定されていない場合には 6 として扱われる。 精度として明示的に 0 が指定されたときには、小数点以下は表示されない。 小数点を表示する際には、小数点の前に少なくとも一桁は数字が表示される。

    (SUSv2 では、F は規定されておらず、無限や NaN に関する文字列表現を 行ってもよいことになっている。
     C99 標準では、f 変換では、無限は "[-]inf" か "[-]infinity" と表示し、 NaN は文字列の先頭に `nan をつけて表示するように規定されている。 F 変換の場合は "[-]INF", "[-]INFINITY", "NAN*" と表示される。) 
g, G
    double 引き数を f か e (G 変換の場合は F か E) の形式に変換する。 精度は表示する桁数を指定する。 精度が指定されない場合は、6桁とみなされる。 精度が 0 の場合は、1桁とみなされる。 変換される値の指数が、 -4 より小さいか、精度以上の場合に、 e 形式が使用される。 変換された結果の小数部分の末尾の 0 は削除される。小数点が表示されるのは、 小数点以下に数字が少なくとも一つある場合にだけである。 

#endif

#ifdef WITH_FLOAT_FORMAT
		void out_real_(float v) {

			uint32_t fpv = *(reinterpret_cast<uint32_t*>(&v));
			bool sign = fpv >> 31;
			int32_t exp = (fpv >> 23) & 0xff;
			exp -= 127;	// bias (-127)
			int val = fpv & 0x7fffff;	// 23 bits
			int shift = 23;
			if(sign) val = -val;
			if(val == 0 && exp == -127) ; // [0.0]
			else {
				val |= 0x800000; // add offset 1.0
			}
#if 0
std::cout << "Real: " << v << std::endl;
std::cout << "S: " << static_cast<int>(sign) << std::endl;
std::cout << "E: " << static_cast<int>(exp) << std::endl;
std::cout << "P: " << static_cast<int>(val) << std::endl;
#endif

			if(exp > 0) {
				shift -= exp;
			} else if(exp < 0) {
				shift -= exp;
			}

			if(decimal_ == 0) decimal_ = 6;
			out_fixed_point_(val, shift);
		}

		void out_exp_(float v) {
		}

		void out_real_auto_(float v) {

		}
#endif

#ifdef WITH_DOUBLE_FORMAT
		void out_real_(double val) {
		}

		void out_exp_(double v) {
		}

		void out_real_auto_(double v) {

		}
#endif

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		format(const char* form) : out_(), err_(), form_(form), real_(0), decimal_(0), ppos_(0),
			mode_(mode::NONE_), zerosupp_(false), sign_(false) {
			next_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  オペレーター「%」
			@param[in]	val	文字
			@return	自分の参照
		*/
		//-----------------------------------------------------------------//
		format& operator % (char val) {
			if(mode_ == mode::CHA) {
				out_(val);
			} else {
				err_(error_case::DIFFERENT_TYPE);
			}
			reset_();
			next_();
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  オペレーター「%」
			@param[in]	val	文字列
			@return	自分の参照
		*/
		//-----------------------------------------------------------------//
		format& operator % (const char* val) {
			if(mode_ == mode::STR) {
				zerosupp_ = false;
				uint8_t n = 0;
				if(real_) {
					const char* p = val;
					while((*p++) != 0) { ++n; }
				}
				out_str_(val, n);
			} else {
				err_(error_case::DIFFERENT_TYPE);
			}
			reset_();
			next_();
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  オペレーター「%」
			@param[in]	val	整数値
			@return	自分の参照
		*/
		//-----------------------------------------------------------------//
		format& operator % (int val) {
			if(mode_ == mode::BINARY) {
				out_bin_(val);
#ifdef WITH_OCTAL_FORMAT
			} else if(mode_ == mode::OCTAL) {
				out_oct_(val);
#endif
			} else if(mode_ == mode::DECIMAL) {
				out_dec_(val);
			} else if(mode_ == mode::HEX) {
				out_hex_(static_cast<unsigned int>(val), 'a');
			} else if(mode_ == mode::HEX_CAPS) {
				out_hex_(static_cast<unsigned int>(val), 'A');
			} else if(mode_ == mode::FIXED_REAL) {
				if(decimal_ == 0) decimal_ = 3;
				out_fixed_point_(val, ppos_);
			} else {
				err_(error_case::DIFFERENT_TYPE);
			}
			reset_();
			next_();
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  オペレーター「%」
			@param[in]	val	符号無し整数値
			@return	自分の参照
		*/
		//-----------------------------------------------------------------//
		format& operator % (unsigned int val) {
			if(mode_ == mode::BINARY) {
				out_bin_(val);
#ifdef WITH_OCTAL_FORMAT
			} else if(mode_ == mode::OCTAL) {
				out_oct_(val);
#endif
			} else if(mode_ == mode::DECIMAL) {
				out_dec_(val);
			} else if(mode_ == mode::U_DECIMAL) {
				out_dec_(val);
			} else if(mode_ == mode::HEX) {
				out_hex_(val, 'a');
			} else if(mode_ == mode::HEX_CAPS) {
				out_hex_(val, 'A');
			} else if(mode_ == mode::FIXED_REAL) {
				if(decimal_ == 0) decimal_ = 3;
				out_fixed_point_(val, ppos_);
			} else {
				err_(error_case::DIFFERENT_TYPE);
			}
			reset_();
			next_();
			return *this;
		}


#ifdef WITH_FLOAT_FORMAT
		//-----------------------------------------------------------------//
		/*!
			@brief  オペレーター「%」
			@param[in]	val	浮動小数点(float)
			@return	自分の参照
		*/
		//-----------------------------------------------------------------//
		format& operator % (float val) {
			if(mode_ == mode::REAL) {
				out_real_(val);
			} else if(mode_ == mode::EXPONENT) {
				out_exp_(val);
			} else if(mode_ == mode::REAL_AUTO) {
				out_real_auto_(val);
			} else {
				err_(error_case::DIFFERENT_TYPE);
			}
			reset_();
			next_();
			return *this;
		}
#endif

#ifdef WITH_DOUBLE_FORMAT
		//-----------------------------------------------------------------//
		/*!
			@brief  オペレーター「%」
			@param[in]	val	浮動小数点(double)
			@return	自分の参照
		*/
		//-----------------------------------------------------------------//
		format& operator % (double val) {
			if(mode_ == mode::REAL) {
				out_real_(val);
			} else if(mode_ == mode::EXPONENT) {
				out_exp_(val);
			} else if(mode_ == mode::REAL_AUTO) {
				out_real_auto_(val);
			} else {
				err_(error_case::DIFFERENT_TYPE);
			}
			reset_();
			next_();
			return *this;
		}
#endif
	};
}
