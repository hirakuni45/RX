#pragma once
//=====================================================================//
/*! @file
    @brief  format クラス @n
			・安全性を考慮した、printf 表示に準じたクラス
			・二進表記として、「%b」をサポート
			・固定小数点表示「%N.M:Ly」形式をサポート @n
			※ N：全桁数、M：小数部桁数、L：小数部のビット数 @n
			※ N には、小数点、符号が含まれる @n
			Ex: %1.2:8y ---> 256 で 1.00、128 で 0.50、384 で 1.50 と @n
			と表示される。
			Copyright 2013,2016 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
/// ８進数のサポート
/// #define WITH_OCTAL_FORMAT
/// 浮動小数点(float)のサポート
#define WITH_FLOAT_FORMAT
/// 浮動小数点(double)のサポート
/// #define WITH_DOUBLE_FORMAT

extern "C" {
	void sci_putch(char ch);
	void sci_puts(const char* str);
};

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

namespace utils {

#if 0
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  エラー・ケース
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class format_error : uint8_t {
		NULL_PTR,		///< 無効なポインター
		UNKNOWN_TYPE,	///< 不明な「型」
		DIFFERENT_TYPE,	///< 異なる「型」
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  エラー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class format_error_task {
	public:
		void operator() (format_error t) {
			switch(t) {
			case format_error::NULL_PTR:
				sci_puts("NULL ptr\n");
				break;
			case format_error::UNKNOWN_TYPE:
				sci_puts("Unknown type\n");
				break;
			case error_case::DIFFERENT_TYPE:
				sci_puts("Different type\n");
				break;
			}
		}
	};
#endif

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  簡易 format クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class format {

		enum class mode : uint8_t {
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
			EXPONENT_CAPS,	///< 浮動小数点 exp 形式(E)
			EXPONENT,	///< 浮動小数点 exp 形式(e)
			REAL_AUTO,	///< 浮動小数点自動
#endif
			NONE		///< 不明
		};

#ifdef ERROR_MESSAGE
		ERR			err_;	///< エラー関数クラス
#endif
		const char*	form_;

		char		buff_[34];

		uint8_t		num_;
		uint8_t		point_;
		uint8_t		bitlen_;
		mode		mode_;
		bool		zerosupp_;
		bool		sign_;

		void reset_() {
			num_ = 0;
			point_ = 0;
			bitlen_ = 0;
			mode_ = mode::NONE;
			zerosupp_ = false;
			sign_ = false;
		}

		void next_() {
			enum class apmd : uint8_t {
				none,
				num,    // 数字
				point,	// 小数点
				bitlen,	// 固定小数点、ビット長さ
			};

			if(form_ == nullptr) {
#ifdef ERROR_MESSAGE
				err_(error_case::NULL_PTR);
#endif
				return;
			}
			char ch;
			apmd md = apmd::none;
			while((ch = *form_++) != 0) {
				if(md != apmd::none) {
					if(ch == '+') {
						sign_ = true;
					} else if(ch >= '0' && ch <= '9') {
						ch -= '0';
						if(md == apmd::num) {
							if(num_ == 0 && ch == 0) {
								zerosupp_ = true;
							}
							num_ *= 10;
							num_ += static_cast<uint8_t>(ch);
						} else if(md == apmd::point) {
							point_ *= 10;
							point_ += static_cast<uint8_t>(ch);
						} else if(md == apmd::bitlen) {
							bitlen_ *= 10;
							bitlen_ += static_cast<uint8_t>(ch);
						}
					} else if(ch == '.') {
						md = apmd::point;
					} else if(ch == ':') {
						md = apmd::bitlen;
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
					} else if(ch == 'e') {
						mode_ = mode::EXPONENT;
						return;
					} else if(ch == 'E') {
						mode_ = mode::EXPONENT_CAPS;
						return;
					} else if(ch == 'g' || ch == 'G') {
						mode_ = mode::REAL_AUTO;
						return;
#endif
					} else if(ch == '%') {
						sci_putch(ch);
						md = apmd::none;
					} else if(ch == '-') {  // 無視する

					} else {
#ifdef ERROR_MESSAGE
						err_(error_case::UNKNOWN_TYPE);
#endif
						return;
					}
				} else if(ch == '%') {
					md = apmd::num;
				} else {
					sci_putch(ch);
				}
			}
		}

		void out_str_(const char* str, char sign, uint8_t n) {
			if(zerosupp_) {
				if(sign != 0) { sci_putch(sign); }
			}
			if(n && n < num_) {
				uint8_t spc = num_ - n;
				while(spc) {
					--spc;
					if(zerosupp_) sci_putch('0');
					else sci_putch(' ');
				}
			}
			if(!zerosupp_) {
				if(sign != 0) { sci_putch(sign); }
			}
			sci_puts(str);
		}

		void out_bin_(int32_t v) {
			char* p = &buff_[sizeof(buff_) - 1];
			*p = 0;
			uint8_t n = 0;
			do {
				--p;
				*p = (v & 1) + '0';
				v >>= 1;
				++n;
			} while(v != 0) ;
			out_str_(p, '+', n);
		}

#ifdef WITH_OCTAL_FORMAT
		void out_oct_(int32_t v) {
			char* p = &buff_[sizeof(buff_) - 1];
			*p = 0;
			uint8_t n = 0;
			do {
				--p;
				*p = (v & 3) + '0';
				v >>= 3;
				++n;
			} while(v != 0) ;
			out_str_(p, '+', n);
		}
#endif

		void out_udec_(uint32_t v, char sign) {
			char* p = &buff_[sizeof(buff_) - 1];
			*p = 0;
			uint8_t n = 0;
			do {
				--p;
				*p = (v % 10) + '0';
				v /= 10;
				++n;
			} while(v != 0) ;
			out_str_(p, sign, n);
		}


		void out_dec_(int32_t v) {
			char sign = 0;
			if(v < 0) { v = -v; sign = '-'; }
			else if(sign_) { sign = '+'; }
			out_udec_(v, sign);
		}


		void out_hex_(uint32_t v, char top) {
			char* p = &buff_[sizeof(buff_) - 1];
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
			out_str_(p, '+', n);
		}

		uint64_t make_mask_(uint8_t num) {
			uint64_t m = 0;
			while(num > 0) {
				m += m;
				++m;
				--num;
			}
			return m;
		}

		template <typename VAL>
		void out_fixed_point_(VAL v, uint8_t fixpoi, bool sign)
		{
// std::cout << "Shift: " << static_cast<int>(fixpoi) << std::endl;
			// 四捨五入処理用 0.5
			VAL m = 0;
			if(fixpoi < (sizeof(VAL) * 8 - 4)) {
				m = static_cast<VAL>(5) << fixpoi;
				uint8_t n = point_ + 1;
				while(n > 0) {
					m /= 10;
					--n;
				}
			}
			char sch = 0;
			if(sign) sch = '-';
			else if(sign_) sch = '+';
			v += m;
			if(num_ >= point_) num_ -= point_;
			if(num_ > 0 && sch != 0) --num_;
			if(num_ > 0 && point_ != 0) {
				--num_;
			}
			if(fixpoi < (sizeof(VAL) * 8 - 4)) {
				out_udec_(v >> fixpoi, sch);
			} else {
				out_udec_(0, sch);
			}

			if(point_ == 0) return;
			sci_putch('.');

			uint8_t l = 0;
			if(fixpoi < (sizeof(VAL) * 8 - 4)) {
				VAL dec = v & make_mask_(fixpoi);
				while(dec > 0) {
					dec *= 10;
					VAL n = dec >> fixpoi;
					sci_putch(n + '0');
					dec -= n << fixpoi;
					++l;
					if(l >= point_) break;
				}
			}
			while(l < point_) {
				sci_putch('0');
				++l;
			}
		}

#ifdef WITH_FLOAT_FORMAT
		void out_real_(float v, char e) {
			void* p = &v;
			uint32_t fpv = *(uint32_t*)p;
			bool sign = fpv >> 31;
			int16_t exp = (fpv >> 23) & 0xff;
			if(exp == 0xff) {
				if(sign) sci_putch('-');
				sci_puts("inf");
				return;
			}

			exp -= 127;	// bias (-127)
			int32_t val = fpv & 0x7fffff;	// 23 bits
			int16_t shift = 23;
			if(val == 0 && exp == -127) ; // [0.0]
			else {
				val |= 0x800000; // add offset 1.0
			}
			shift -= exp;

			// 64 ビットに拡張
			uint64_t v64 = static_cast<uint64_t>(val);
			if(shift < 28) {
				shift += 32;
				v64 <<= 32;
			}

			// エキスポーネント表記の場合
			int8_t dexp = 0;
			if(e != 0) {
				if(v64 > (static_cast<uint64_t>(2) << shift)) {  // 2.0 以上の場合
					while(v64 > (static_cast<uint64_t>(2) << shift)) {
						v64 /= 10;
						++dexp;
					}
				} else if(v64 < (static_cast<uint64_t>(1) << shift)) {  // 1.0 以下
					while(v64 < (static_cast<uint64_t>(1) << shift)) {
						v64 *= 10;
						--dexp;
					}
				}
			}

			out_fixed_point_<uint64_t>(v64, shift, sign);

			if(e) {
				sci_putch(e);
				zerosupp_ = true;
				sign_ = true;
				num_ = 3;
				out_dec_(dexp);
			}
		}
#endif

#ifdef WITH_DOUBLE_FORMAT
		void out_real_(double val, char e) {
		}
#endif

		void sign_int_(int32_t val) {
			bool sign = false;
			switch(mode_) {
			case mode::BINARY:
				out_bin_(val);
				break;
#ifdef WITH_OCTAL_FORMAT
			case mode::OCTAL:
				out_oct_(val);
				break;
#endif
			case mode::DECIMAL:
				out_dec_(val);
				break;
			case mode::HEX:
				out_hex_(static_cast<uint32_t>(val), 'a');
				break;
			case mode::HEX_CAPS:
				out_hex_(static_cast<uint32_t>(val), 'A');
				break;
			case mode::FIXED_REAL:
				if(num_ == 0) num_ = 6;
				if(val < 0) {
					sign = true;
					val = -val;
				}
#ifdef WITH_FLOAT_FORMAT
				out_fixed_point_<uint64_t>(val, bitlen_, sign);
#else
				out_fixed_point_<uint32_t>(val, bitlen_, sign);
#endif
				break;
			default:
#ifdef ERROR_MESSAGE
				err_(error_case::DIFFERENT_TYPE);
#endif
				break;
			}
			reset_();
			next_();
		}


		void unsign_int_(uint32_t val) {
			switch(mode_) {
			case mode::BINARY:
				out_bin_(val);
				break;
#ifdef WITH_OCTAL_FORMAT
			case mode::OCTAL:
				out_oct_(val);
				break;
#endif
			case mode::DECIMAL:
				out_dec_(val);
				break;
			case mode::U_DECIMAL:
				out_udec_(val, sign_ ? '+' : 0);
				break;
			case mode::HEX:
				out_hex_(val, 'a');
				break;
			case mode::HEX_CAPS:
				out_hex_(val, 'A');
				break;
			case mode::FIXED_REAL:
				if(num_ == 0) num_ = 6;
#ifdef WITH_FLOAT_FORMAT
				out_fixed_point_<uint64_t>(val, bitlen_, false);
#else
				out_fixed_point_<uint32_t>(val, bitlen_, false);
#endif
				break;
			default:
#ifdef ERROR_MESSAGE
				err_(error_case::DIFFERENT_TYPE);
#endif
				break;
			}
			reset_();
			next_();
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		format(const char* form) : form_(form), num_(0), point_(0), bitlen_(0),
			mode_(mode::NONE), zerosupp_(false), sign_(false) {
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
				sci_putch(val);
			} else {
#ifdef ERROR_MESSAGE
				err_(error_case::DIFFERENT_TYPE);
#endif
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
				const char* p = val;
				while((*p++) != 0) { ++n; }
				out_str_(val, 0, n);
			} else {
#ifdef ERROR_MESSAGE
				err_(error_case::DIFFERENT_TYPE);
#endif
			}
			reset_();
			next_();
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  オペレーター「%」（int）
			@param[in]	val	整数値
			@return	自分の参照
		*/
		//-----------------------------------------------------------------//
		format& operator % (int val) {
			sign_int_(static_cast<int32_t>(val));
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  オペレーター「%」（int16_t）
			@param[in]	val	整数値
			@return	自分の参照
		*/
		//-----------------------------------------------------------------//
		format& operator % (int16_t val) {
			sign_int_(static_cast<int32_t>(val));
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  オペレーター「%」int32_t
			@param[in]	val	整数値
			@return	自分の参照
		*/
		//-----------------------------------------------------------------//
		format& operator % (int32_t val) {
			sign_int_(val);
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  オペレーター「%」（unsigned int）
			@param[in]	val	符号無し整数値
			@return	自分の参照
		*/
		//-----------------------------------------------------------------//
		format& operator % (unsigned int val) {
			unsign_int_(static_cast<uint32_t>(val));
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  オペレーター「%」（uint16_t）
			@param[in]	val	符号無し整数値
			@return	自分の参照
		*/
		//-----------------------------------------------------------------//
		format& operator % (uint16_t val) {
			unsign_int_(static_cast<uint32_t>(val));
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  オペレーター「%」（UINT）
			@param[in]	val	符号無し整数値
			@return	自分の参照
		*/
		//-----------------------------------------------------------------//
		format& operator % (uint32_t val) {
			unsign_int_(static_cast<uint32_t>(val));
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
			if(num_ == 0 && !zerosupp_ && point_ == 0) {
				num_ = 6;
				point_ = 6;
			}
			switch(mode_) {
			case mode::REAL:
				out_real_(val, 0);
				break;
			case mode::EXPONENT_CAPS:
				out_real_(val, 'E');
				break;
			case mode::EXPONENT:
				out_real_(val, 'e');
				break;
			case mode::REAL_AUTO:
				out_real_(val, 0);
				break;
			default:
#ifdef ERROR_MESSAGE
				err_(error_case::DIFFERENT_TYPE);
#endif
				break;
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
			if(num_ == 0 && !zerosupp_) num_ = 6;
			if(mode_ == mode::REAL) {
				out_real_(val, 0);
			} else if(mode_ == mode::EXPONENT_CAPS) {
				out_real_(val, 'E');
			} else if(mode_ == mode::EXPONENT) {
				out_exp_(val, 'e');
			} else if(mode_ == mode::REAL_AUTO) {
				out_real_auto_(val, 0);
			} else {
#ifdef ERROR_MESSAGE
				err_(error_case::DIFFERENT_TYPE);
#endif
			}
			reset_();
			next_();
			return *this;
		}
#endif
	};
}
