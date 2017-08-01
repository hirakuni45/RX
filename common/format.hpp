#pragma once
//=====================================================================//
/*! @file
    @brief  format クラス @n
			・安全性を考慮した、[s]printf 表示に準じたクラス
			・二進表記として、「%b」をサポート
			・固定小数点表示「%N.M:Ly」形式をサポート @n
			※ N：全桁数、M：小数部桁数、L：小数部のビット数 @n
			※ N には、小数点、符号が含まれる @n
			Ex: %1.2:8y ---> 256 で 1.00、128 で 0.50、384 で 1.50 と @n
			と表示される。@n
			+ 2017/06/11 20:00- 標準文字出力クラスの再定義、実装 @n 
			+ 2017/06/11 21:00- 固定文字列クラス向け chaout、実装 @n
			+ 2017/06/12 14:50- memory_chaoutと、専用コンストラクター実装 @n
			+ 2017/06/14 05:34- memory_chaout size() のバグ修正
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <type_traits>
#include <unistd.h>
#include <cstring>

/* 
  e, E
     double 引き数を丸めて [-]d.ddde±dd の形に変換する。 小数点の前には一桁の数字があり、
     小数点以下の桁数は精度で指定された桁数 になる。精度は指定されなかった場合 6 とみなされる。
     精度が 0 の場合には、 小数点以下は表示されない。E 変換では、指数を表現するときに 
     (e で はなく) E が使われる。指数部分は少なくとも 2桁表示される。つまり、 指数の値が 0
     の場合には、00 と表示される。 

  f, F
    double 引き数を丸めて [-]ddd.ddd の形の10進表現に変換する。 小数点の後の桁数は、精度で
    指定された値となる。 精度が指定されていない場合には 6 として扱われる。 精度として明示的
    に 0 が指定されたときには、小数点以下は表示されない。 小数点を表示する際には、小数点の
    前に少なくとも一桁は数字が表示される。

    (SUSv2 では、F は規定されておらず、無限や NaN に関する文字列表現を 行ってもよいことになっている。
     C99 標準では、f 変換では、無限は "[-]inf" か "[-]infinity" と表示し、 NaN は文字列の先頭
    に `nan をつけて表示するように規定されている。 F 変換の場合は
    "[-]INF", "[-]INFINITY", "NAN*" と表示される。) 

  g, G
    double 引き数を f か e (G 変換の場合は F か E) の形式に変換する。 精度は表示する桁数を
    指定する。 精度が指定されない場合は、6桁とみなされる。 精度が 0 の場合は、1桁とみなされる。
    変換される値の指数が、 -4 より小さいか、精度以上の場合に、 e 形式が使用される。
    変換された結果の小数部分の末尾の 0 は削除される。小数点が表示されるのは、 小数点以下に
    数字が少なくとも一つある場合にだけである。 
*/

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  無効出力ファンクタ @n
				※全ての動作が無効
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class null_chaout {
	public:

		void operator() (char ch) {
		}

		void clear() { };

		uint32_t size() const { return 0; }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  サイズ出力ファンクタ @n
				※出力サイズのみ有効
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class size_chaout {

		uint32_t	size_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		size_chaout() : size_(0) { } 

		void operator() (char ch) {
			++size_;
		}

		void clear() { size_ = 0; };

		uint32_t size() const { return size_; }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  標準出力ファンクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class stdout_chaout {

		uint32_t	size_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		stdout_chaout() : size_(0) { } 

		void operator() (char ch) {
			char tmp = ch;
			write(1, &tmp, 1);  // FD by stdout
			++size_;
		}

		void clear() { size_ = 0; };

		uint32_t size() const { return size_; }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  標準出力ターミネーター・ファンクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class stdout_term {
	public:
		void operator() (const char* s, uint16_t l) {
			write(1, s, l);  // FD by stdout
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  標準出力ターミネーター・ファンクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class null_term {
	public:
		void operator() (const char* s, uint16_t l) { }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  文字列クラス、出力ファンクタ
		@param[in]	STR		文字列クラス
		@param[in]	TERM	ターミネーター・ファンクタ	
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class STR, class TERM>
	class string_chaout {

		STR		str_;
		TERM	term_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		string_chaout() : str_(), term_() { }

		void operator () (char ch) {
			str_ += ch;
			if(str_.size() >= str_.capacity()) {
				term_(str_.c_str(), str_.size());
				str_.clear();
			}			
		}

		void clear() {
			if(str_.size() > 0) {
				term_(str_.c_str(), str_.size());
			}
			str_.clear();
		}

		uint32_t size() const { return str_.size(); }

		void flush() {
			if(str_.size() > 0) {
				term_(str_.c_str(), str_.size());
				str_.clear();
			}
		}

		STR& at_str() { return str_; }

		TERM& at_term() { return term_; }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  メモリー文字列クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class memory_chaout {

		char*		dst_;
		uint32_t	limit_;
		uint32_t	pos_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		memory_chaout() : dst_(nullptr), limit_(0), pos_(0) { }

		void set(char* dst, uint32_t limit)
		{
			if(dst_ != dst || limit_ != limit) {  // ポインター、サイズ、どちらか異なる場合は常にリセット
				pos_ = 0;
			}
			dst_ = dst;
			limit_ = limit;
		}

		void operator () (char ch) {
			if(pos_ < (limit_ - 1)) {
				dst_[pos_] = ch;
				++pos_;
				dst_[pos_] = 0;
			}
		}

		void clear() { pos_ = 0; }

		uint32_t size() const { return pos_; }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  簡易 format クラス
		@param[in]	CHAOUT	文字出力ファンクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CHAOUT>
	class basic_format {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  エラー種別
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class error : uint8_t {
			none,		///< エラー無し
			null,		///< 無効なポインター
			unknown,	///< 不明な「型」
			different,	///< 異なる「型」
		};

	private:
		enum class mode : uint8_t {
			CHA,		///< 文字
			STR,		///< 文字列
			BINARY,		///< ２進
			OCTAL,		///< ８進
			DECIMAL,	///< １０進
			U_DECIMAL,	///< １０進（符号無し）
			HEX_CAPS,	///< １６進（大文字）
			HEX,		///< １６進（小文字）
			FIXED_REAL,	///< 固定小数点
			REAL,		///< 浮動小数点
			EXPONENT_CAPS,	///< 浮動小数点 exp 形式(E)
			EXPONENT,	///< 浮動小数点 exp 形式(e)
			REAL_AUTO,	///< 浮動小数点自動
			NONE		///< 不明
		};

		static CHAOUT	chaout_;

		const char*	form_;

		char		buff_[34];

		error		error_;

		uint8_t		num_;
		uint8_t		point_;
		uint8_t		bitlen_;
		mode		mode_;
		bool		zerosupp_;
		bool		sign_;

		void str_(const char* str) {
			char ch;
			while((ch = *str++) != 0) chaout_(ch);
		}

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
				error_ = error::null;
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
					} else if(ch == 'o') {
						mode_ = mode::OCTAL;
						return;
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
					} else if(ch == '%') {
						chaout_(ch);
						md = apmd::none;
					} else if(ch == '-') {  // 無視する

					} else {
						error_ = error::unknown;
						return;
					}
				} else if(ch == '%') {
					md = apmd::num;
				} else {
					chaout_(ch);
				}
			}
		}


		void out_str_(const char* str, char sign, uint8_t n) {
			if(zerosupp_) {
				if(sign != 0) { chaout_(sign); }
			}
			if(n && n < num_) {
				uint8_t spc = num_ - n;
				while(spc) {
					--spc;
					if(zerosupp_) chaout_('0');
					else chaout_(' ');
				}
			}
			if(!zerosupp_) {
				if(sign != 0) { chaout_(sign); }
			}
			str_(str);
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
			out_str_(p, 0, n);
		}


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
			out_str_(p, 0, n);
		}


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
			out_str_(p, 0, n);
		}


		void decimal_(int32_t val, bool sign) {
			switch(mode_) {
			case mode::BINARY:
				out_bin_(val);
				break;
			case mode::OCTAL:
				out_oct_(val);
				break;
			case mode::DECIMAL:
				out_dec_(val);
				break;
			case mode::U_DECIMAL:
				out_udec_(val, sign_ ? '+' : 0);
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
				out_fixed_point_<uint64_t>(val, bitlen_, sign);
				break;
			default:
				error_ = error::different;
				break;
			}
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
			chaout_('.');

			uint8_t l = 0;
			if(fixpoi < (sizeof(VAL) * 8 - 4)) {
				VAL dec = v & make_mask_(fixpoi);
				while(dec > 0) {
					dec *= 10;
					VAL n = dec >> fixpoi;
					chaout_(n + '0');
					dec -= n << fixpoi;
					++l;
					if(l >= point_) break;
				}
			}
			while(l < point_) {
				chaout_('0');
				++l;
			}
		}


		void out_real_(float v, char e) {
			void* p = &v;
			uint32_t fpv = *(uint32_t*)p;
			bool sign = fpv >> 31;
			int16_t exp = (fpv >> 23) & 0xff;
			if(exp == 0xff) {
				if(sign) chaout_('-');
				str_("inf");
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
				chaout_(e);
				zerosupp_ = true;
				sign_ = true;
				num_ = 3;
				out_dec_(dexp);
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	form	フォーマット式
		*/
		//-----------------------------------------------------------------//
		basic_format(const char* form) noexcept :
			form_(form),
			error_(error::none),
			num_(0), point_(0),
			bitlen_(0),
			mode_(mode::NONE), zerosupp_(false), sign_(false)
		{
			next_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	form	フォーマット式
			@param[in]	buff	文字バッファ
			@param[in]	size	文字バッファサイズ
			@param[in]	append	文字バッファに追加する場合「true」
		*/
		//-----------------------------------------------------------------//
		basic_format(const char* form, char* buff, uint32_t size, bool append = false) noexcept :
			form_(form),
			error_(error::none),
			num_(0), point_(0),
			bitlen_(0),
			mode_(mode::NONE), zerosupp_(false), sign_(false)
		{
			chaout_.set(buff, size);
			if(!append) {
				chaout_.clear();

			}
			next_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  出力ファンクタの参照
			@return 出力ファンクタ
		*/
		//-----------------------------------------------------------------//
		static CHAOUT& chaout() { return chaout_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  エラー種別を返す
			@return エラー
		*/
		//-----------------------------------------------------------------//
		error get_error() const noexcept { return error_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  変換ステータスを返す
			@return 変換が全て正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool status() const noexcept { return error_ == error::none; }


		//-----------------------------------------------------------------//
		/*!
			@brief  出力サイズを返す
			@return 出力サイズ
		*/
		//-----------------------------------------------------------------//
		int size() const noexcept { return chaout_.size(); }


		//-----------------------------------------------------------------//
		/*!
			@brief  オペレーター「%」(const char*)
			@param[in]	val	値
			@return	自分の参照
		*/
		//-----------------------------------------------------------------//
		basic_format& operator % (const char* val) noexcept
		{
			if(error_ != error::none) {
				return *this;
			}

			if(mode_ == mode::STR) {
				if(val == nullptr) {
					static const char* nullstr = { "(nullptr)" };
					out_str_(nullstr, 0, std::strlen(nullstr));					
				} else {
					zerosupp_ = false;
					uint8_t n = 0;
					const char* p = val;
					while((*p++) != 0) { ++n; }
					out_str_(val, 0, n);
				}
			} else {
				error_ = error::different;
			}

			reset_();
			next_();
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  オペレーター「%」(const char*)
			@param[in]	val	値
			@return	自分の参照
		*/
		//-----------------------------------------------------------------//
		basic_format& operator % (char* val) noexcept
		{
			if(error_ != error::none) {
				return *this;
			}

			if(mode_ == mode::STR) {
				if(val == nullptr) {
					static const char* nullstr = { "(nullptr)" };
					out_str_(nullstr, 0, strlen(nullstr));					
				} else {
					zerosupp_ = false;
					uint8_t n = 0;
					const char* p = val;
					while((*p++) != 0) { ++n; }
					out_str_(val, 0, n);
				}
			} else {
				error_ = error::different;
			}

			reset_();
			next_();
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  オペレーター「%」
			@param[in]	val	値
			@return	自分の参照
		*/
		//-----------------------------------------------------------------//
		template <typename T>
		basic_format& operator % (T val) noexcept
		{
			if(error_ != error::none) {
				return *this;
			}

			if(std::is_integral<T>::value) {
				if(mode_ == mode::CHA && sizeof(T) == 1) {
					chaout_(val);
				} else {
					decimal_(static_cast<int32_t>(val), std::is_signed<T>::value);
				}
			} else if(std::is_floating_point<T>::value) {
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
					error_ = error::different;
					break;
				}
			} else {
				error_ = error::unknown;
			}

			reset_();
			next_();
			return *this;
		}
	};

	template <class CHAOUT> CHAOUT basic_format<CHAOUT>::chaout_;

	typedef basic_format<stdout_chaout> format;
	typedef basic_format<memory_chaout> sformat;
	typedef basic_format<null_chaout> null_format;
	typedef basic_format<size_chaout> size_format;
}
