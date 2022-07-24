#pragma once
//=============================================================================//
/*! @file
    @brief  utils::format クラス @n
			・安全性を考慮した、[s]printf 表示に準じたクラス @n
			・二進表記として、「%b」をサポート @n
			・固定小数点表示「%N.M:Ly」形式をサポート @n
			※ N：全桁数、M：小数部桁数、L：小数部のビット数 @n
			※ N には、小数点、符号が含まれる @n
			Ex: %3.2:8y ---> 256 で 1.00、128 で 0.50、384 で 1.50 @n
			と表示される。 @n
            ・NO_FLOAT_FORM を有効にすると、float 関係の機能を無効にでき @n
            メモリを節約出来る。@n
			・組み込みマイコンでは、64 ビット整数、倍精度浮動小数点など、リソースを @n
			多く消費する為、サポートしていません。（オプションでサポートを追加する予定）
			+ 2017/06/11 20:00- 標準文字出力クラスの再定義、実装 @n 
			+ 2017/06/11 21:00- 固定文字列クラス向け chaout、実装 @n
			+ 2017/06/12 14:50- memory_chaoutと、専用コンストラクター実装 @n
			+ 2017/06/14 05:34- memory_chaout size() のバグ修正 @n
			+ 2018/11/20 05:10- float を無効にするオプションを復活 @n
			+ 2019/05/04 14:44- %c を指定した場合、整数を全て受け付け、範囲を検査 @n
			+ 2019/05/04 15:33- %g、%G 末尾の桁に '0' がある場合除去する。@n
			+ 2019/12/02 10:50- write 関数の代わりに putchar へ切り替えるオプションを追加 @n
			! 2019/12/03 20:00- %nd の場合に、表示が重複する不具合修正。@n
			+ 2019/12/03 21:54- インクルードファイルの修追加。@n
			+ 2019/12/09 03:21- memory_chaout で出力先が設定されていない場合の安全性確保。@n
			! 2019/12/14 11:44- 符号の表示不具合修正。@n
			+ 2020/01/02 11:05- ポインター表示機能「%p」追加。 @n
			+ 2020/02/02 15:43- enum error など共有定義の継承。 @n
			! 2019/02/02 19:42- 符号文字カウントの不具合修正。 @n
			+ 2020/02/04 05:23- std::string 型追加。 @n
			+ 2020/04/25 07:45- stdout_buffered_chaout に、操作位置を返すメソッド pos() を追加。 @n
			! 2020/11/20 07:44- sformat 時の nega_ フラグの初期化漏れ @n
			! 2020/11/20 07:44- nega_ 符号表示の順番、不具合 @n
			! 2020/11/20 16:59- uint 型を削除 @n
			! 2022/06/13 15:03- 'static const' を 'static constexpr' に変更 @n
			! 2022/07/06 09:24- %6.0f の符号付きの場合に、スペースが足りなくなるバグ修正。(V95) @n
			! 2022/07/07 20:52- %g の自動（有効桁６桁）フォーマットの対応。(v96) @n
			! 2022/07/11 14:08- nan の識別と表示、及びテストの対応。(V97) @n
			! 2022/07/13 14:45- %Ng の自動（Ｎの有効桁がある場合）フォーマットの対応。(V98) @n
			! 2022/07/14 13:31- 内部処理で、’if’ 文 から 'switch' へ変更（速度改善？、見やすさに貢献）(V99) @n
			! 2022/07/24 17:48- V99 で変更した処理の不具合、'%%' の処理 (V100) 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include <type_traits>
#include <unistd.h>
#include <cstdint>
#include <cstring>
#include <string>

// 最終的な出力として putchar を使う場合有効にする（通常は write [stdout] 関数）
// #define USE_PUTCHAR

// float を無効にする場合（８ビット系マイコンでのメモリ節約用）
// #define NO_FLOAT_FORM

// ２進表示をサポートしない場合（メモリの節約）
// #define NO_BIN_FORM

// ８進表示をサポートしない場合（メモリの節約）
// #define NO_OCTAL_FORM

// 64 ビットの整数をサポートする場合（工事中）
#define USE_INT64

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
				※全ての動作を無効にして、機能を取り除く。 @n
				※最適化をしない場合、全てを取り除く事は出来ない。
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class null_chaout {
	public:
		typedef unsigned int uint;	// 通常 8/16 ビットマイコンでは 16 ビットサイズ

		void operator() (char ch) noexcept { }

		void clear() noexcept { };

		uint size() const noexcept { return 0; }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  サイズ出力ファンクタ @n
				※出力サイズを調査する場合などに使う。
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class size_chaout {
	public:
		typedef unsigned int uint;	// 通常 8/16 ビットマイコンでは 16 ビットサイズ

	private:
		uint	size_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		size_chaout() noexcept : size_(0) { } 

		void operator() (char ch) noexcept {
			++size_;
		}

		void clear() noexcept { size_ = 0; };

		uint size() const noexcept { return size_; }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  標準出力ファンクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class stdout_chaout {
	public:
		typedef unsigned int uint;	// 通常 8/16 ビットマイコンでは 16 ビットサイズ

	private:
		uint	size_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		stdout_chaout() noexcept : size_(0) { } 

		void operator() (char ch) noexcept
		{
#ifdef USE_PUTCHAR
			putchar(ch);
#else
			char tmp = ch;
			write(STDOUT_FILENO, &tmp, 1);
#endif
			++size_;
		}

		void clear() noexcept { size_ = 0; };

		uint size() const noexcept { return size_; }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  標準出力バッファリングファンクタ
		@param[in]	BFN		バッファサイズ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t BFN>
	class stdout_buffered_chaout {
	public:
		typedef unsigned int uint;	// 通常 8/16 ビットマイコンでは 16 ビットサイズ

	private:
		char	buff_[BFN];
		uint	pos_;
		uint	size_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		stdout_buffered_chaout() noexcept : pos_(0), size_(0) { } 

		void operator() (char ch) noexcept {
			buff_[pos_] = ch;
			++pos_;
			if(ch == '\n' || pos_ >= BFN) {
				flush();
			}
			++size_;
		}

		void clear() noexcept { size_ = 0; };

		auto size() const noexcept { return size_; }

		auto pos() const noexcept { return pos_; }

		void flush() noexcept
		{
			if(pos_ == 0) return;

#ifdef USE_PUTCHAR
			for(uint i = 0; i < pos_; ++i) {
				putchar(buff_[i]);
			}
#else
			write(STDOUT_FILENO, buff_, pos_);
#endif
			pos_ = 0;
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  標準出力ターミネーター・ファンクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class stdout_term {
	public:
		typedef unsigned int uint;	// 通常 8/16 ビットマイコンでは 16 ビットサイズ

		void operator() (const char* s, uint l) noexcept {
#ifdef USE_PUTCHAR
			for(uint i = 0; i < l; ++i) {
				putchar(s[i]);
			}
#else
			write(STDOUT_FILENO, s, l);
#endif
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  標準出力ターミネーター・ファンクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class null_term {
	public:
		typedef unsigned int uint;	// 通常 8/16 ビットマイコンでは 16 ビットサイズ

		void operator() (const char* s, uint l) { }
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
		string_chaout() noexcept : str_(), term_() { }

		void clear() noexcept {
			if(str_.size() > 0) {
				term_(str_.c_str(), str_.size());
			}
			str_.clear();
		}

		auto size() const noexcept { return str_.size(); }

		void flush() noexcept {
			if(str_.size() > 0) {
				term_(str_.c_str(), str_.size());
				str_.clear();
			}
		}

		STR& at_str() noexcept { return str_; }

		TERM& at_term() noexcept { return term_; }

		//-----------------------------------------------------------------//
		/*!
			@brief  ファンクタ用オペレータ
			@param[in]	ch	出力文字
		*/
		//-----------------------------------------------------------------//
		void operator () (char ch) noexcept {
			str_ += ch;
			if(str_.size() >= str_.capacity()) {
				term_(str_.c_str(), str_.size());
				str_.clear();
			}			
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  メモリー出力文字列クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class memory_chaout {
	public:
		typedef unsigned int uint;	// 通常 8/16 ビットマイコンでは 16 ビットサイズ
	private:
		char*	dst_;
		uint	limit_;
		uint	pos_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		memory_chaout() noexcept : dst_(nullptr), limit_(0), pos_(0) { }


		bool set(char* dst, uint limit) noexcept
		{
			if(dst == nullptr || limit <= 1) {
				return false;
			}
			limit--;

			// ポインター、サイズ、どちらか異なる場合は常にリセット
			if(dst_ != dst || limit_ != limit) {
				pos_ = 0;
			}
			dst_ = dst;
			limit_ = limit;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ファンクタ用オペレータ
			@param[in]	ch	出力文字
		*/
		//-----------------------------------------------------------------//
		void operator () (char ch) noexcept {
			if(pos_ < limit_) {
				dst_[pos_] = ch;
				++pos_;
				dst_[pos_] = 0;
			}
		}


		void clear() noexcept { pos_ = 0; }


		auto size() const noexcept { return pos_; }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	format 基本クラス定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class base_format {
	public:
		static constexpr uint16_t VERSION = 100;		///< バージョン番号（整数）

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  エラー種別
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class error : uint8_t {
			none,			///< エラー無し
			null,			///< 無効なポインター
			unknown,		///< 不明な「型」
			different,		///< 異なる「型」
			over,			///< 数値の領域外（%c で char が扱える数値以外）
			out_null,		///< 文字出力先が無効
			out_overflow,	///< 文字出力先がオーバーフローした場合
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  簡易 format クラス
		@param[in]	CHAOUT	文字出力ファンクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CHAOUT>
	class basic_format : public base_format {

		enum class mode : uint8_t {
			CHA,			///< 文字
			STR,			///< 文字列
			BINARY,			///< ２進
			OCTAL,			///< ８進
			DECIMAL,		///< １０進
			U_DECIMAL,		///< １０進（符号無し）
			HEX_CAPS,		///< １６進（大文字）
			HEX,			///< １６進（小文字）
			POINTER,		///< ポインター（１６進）
			FIXED_REAL,		///< 固定小数点
			REAL,			///< 浮動小数点
			EXPONENT_CAPS,	///< 浮動小数点 exp 形式(E)
			EXPONENT,		///< 浮動小数点 exp 形式(e)
			REAL_AUTO_CAPS,	///< 浮動小数点自動(G)
			REAL_AUTO,		///< 浮動小数点自動(g)
			NONE			///< 不明
		};

		static CHAOUT	chaout_;

		const char*	form_;

		char		buff_[34];  // uint32_t 型で二進表示に必要な大きさ

		uint16_t	num_;

		uint8_t		point_;
		uint8_t		bitlen_;
		uint8_t		udec_num_;
		error		error_;
		mode		mode_;
		bool		zerosupp_;
		bool		sign_;
		bool		nega_;
		bool		set_num_;
		bool		set_poi_;
		bool		auto_mode_;
		bool		exp_mode_;

		void str_(const char* str) noexcept {
			char ch;
			while((ch = *str++) != 0) chaout_(ch);
		}

		void reset_() noexcept {
			num_ = 0;
			point_ = 0;
			bitlen_ = 0;
			udec_num_ = 0;
			mode_ = mode::NONE;
			zerosupp_ = false;
			sign_ = false;
			nega_ = false;
			set_num_ = false;
			set_poi_ = false;
			auto_mode_ = false;
			exp_mode_ = false;
		}

		void next_() noexcept {
			enum class apmd : uint8_t {
				none,
				num,	// 数字
				point,	// 小数点
				bitlen	// 固定小数点、ビット長さ
			};

			if(form_ == nullptr) {
				error_ = error::null;
				return;
			}
			auto md = apmd::none;
			char ch;
			while((ch = *form_++) != 0) {
				if(md != apmd::none) {
					switch(ch) {
					case '+':
						sign_ = true;
						break;
					case '-':
						nega_ = true;
						break;
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						ch -= '0';
						if(md == apmd::num) {
							if(num_ == 0 && ch == 0) {
								zerosupp_ = true;
							}
							num_ *= 10;
							num_ += static_cast<uint8_t>(ch);
							set_num_ = true;
						} else if(md == apmd::point) {
							point_ *= 10;
							point_ += static_cast<uint8_t>(ch);
							set_poi_ = true;
						} else if(md == apmd::bitlen) {
							bitlen_ *= 10;
							bitlen_ += static_cast<uint8_t>(ch);
						}
						break;
					case '.':
						md = apmd::point;
						break;
					case ':':
						md = apmd::bitlen;
						break;
					case 's':
						mode_ = mode::STR;
						return;
					case 'c':
						mode_ = mode::CHA;
						return;
#ifndef NO_BIN_FORM
					case 'b':
						mode_ = mode::BINARY;
						return;
#endif
#ifndef NO_OCTAL_FORM
					case 'o':
						mode_ = mode::OCTAL;
						return;
#endif
					case 'd':
					case 'i':
						mode_ = mode::DECIMAL;
						return;
					case 'u':
						mode_ = mode::U_DECIMAL;
						return;
					case 'x':
						mode_ = mode::HEX;
						return;
					case 'X':
						mode_ = mode::HEX_CAPS;
						return;
					case 'y':
						mode_ = mode::FIXED_REAL;
						return;
					case 'f':
					case 'F':
						mode_ = mode::REAL;
						return;
					case 'e':
						mode_ = mode::EXPONENT;
						return;
					case 'E':
						mode_ = mode::EXPONENT_CAPS;
						return;
					case 'g':
						mode_ = mode::REAL_AUTO;
						return;
					case 'G':
						mode_ = mode::REAL_AUTO_CAPS;
						return;
					case 'p':
						mode_ = mode::POINTER;
						return;
					case '%':
						chaout_(ch);
						md = apmd::none;
						break;
					default:
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


		void out_str_(const char* str, char sign, uint16_t n) noexcept {
			if(nega_) {
				if(sign != 0) { chaout_(sign); }
				str_(str);
			}

			auto num = num_;
			if(sign != 0 && num > 0) { num--; } 
			if(n > 0 && n < num) {
				auto spc = num - n;
				if(zerosupp_) {
					if(sign != 0) { chaout_(sign); }
					while(spc) {
						--spc;
						chaout_('0');
					}
				} else {
					auto spc = num - n;
					while(spc) {
						--spc;
						chaout_(' ');
					}
					if(!nega_ && sign != 0) { chaout_(sign); }
				}
			} else {
				if(!nega_ && sign != 0) { chaout_(sign); }
			}

			if(!nega_) { str_(str); }
		}

#ifndef NO_BIN_FORM
		void out_bin_(uint32_t v) noexcept {
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
#endif

#ifndef NO_OCTAL_FORM
		void out_oct_(uint32_t v) noexcept {
			char* p = &buff_[sizeof(buff_) - 1];
			*p = 0;
			uint8_t n = 0;
			do {
				--p;
				*p = (v & 0b111) + '0';
				v >>= 3;
				++n;
			} while(v != 0) ;
			out_str_(p, 0, n);
		}
#endif

		char* build_udec_(uint32_t v) noexcept {
			char* p = &buff_[sizeof(buff_) - 1];
			*p = 0;
			udec_num_ = 0;
			do {
				--p;
				*p = (v % 10) + '0';
				v /= 10;
				++udec_num_;
			} while(v != 0) ;
			return p;
		}


		void out_dec_(int32_t v) noexcept {
			char sign = 0;
			if(v < 0) { v = -v; sign = '-'; }
			else if(sign_) { sign = '+'; }
			char* tmp = build_udec_(v);
			out_str_(tmp, sign, udec_num_);
		}


		void out_hex_(uint32_t v, char top) noexcept {
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


		void decimal_(int32_t val, bool sign) noexcept {
			switch(mode_) {
#ifndef NO_BIN_FORM
			case mode::BINARY:
				out_bin_(val);
				break;
#endif
#ifndef NO_OCTAL_FORM
			case mode::OCTAL:
				out_oct_(val);
				break;
#endif
			case mode::DECIMAL:
				out_dec_(val);
				break;
			case mode::U_DECIMAL:
				{
					auto tmp = build_udec_(val);
					out_str_(tmp, sign_ ? '+' : 0, udec_num_);
				}
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


		static uint64_t build_mask_(uint8_t num) noexcept {
			uint64_t m = 0;
			while(num > 0) {
				m += m;
				++m;
				--num;
			}
			return m;
		}


		template <typename VAL>
		void out_fixed_point_(VAL v, uint8_t fixpoi, bool sign) noexcept
		{
			// 四捨五入処理用 0.5
			VAL m = 0;
			if(fixpoi < (sizeof(VAL) * 8 - 4)) {
				m = static_cast<VAL>(5) << fixpoi;
				auto n = point_ + 1;
				while(n > 0) {
					m /= 10;
					--n;
				}
			}

			char sch = 0;
			if(sign) sch = '-';
			else if(sign_) sch = '+';
			v += m;
			if(!auto_mode_) {
				if(num_ >= point_) num_ -= point_;
				if(num_ > 0 && point_ != 0) {
					--num_;
				}
			}
			char* rnb_org;
			if(fixpoi < (sizeof(VAL) * 8 - 4)) {
				rnb_org = build_udec_(v >> fixpoi);
			} else {
				rnb_org = build_udec_(0);
			}

			if(mode_ == mode::REAL_AUTO || mode_ == mode::REAL_AUTO_CAPS) {
				// 指定が無い場合６桁を維持
				if(udec_num_ < 6) {
					point_ = 6 - udec_num_;
				} else {
					point_ = 0;
				}
				if(!set_num_) {
					num_ = udec_num_;
				}
			}

			if(point_ > 0) {  // 小数点以下の構築
				char* out = buff_;
				*out++ = '.';
				uint16_t l = 0;
				if(fixpoi < (sizeof(VAL) * 8 - 4)) {
					VAL dec = v & build_mask_(fixpoi);
					while(dec > 0) {
						dec *= 10;
						VAL n = dec >> fixpoi;
						*out++ = n + '0';
						dec -= n << fixpoi;
						++l;
						if(l >= point_) break;
					}
				}
				if(auto_mode_) {  // 後ろの「０」を除去
					while(out > &buff_[1]) {
						if(*(out - 1) == '0') --out;
						else break;
					}
					if(out == &buff_[1]) --out;  // '.'
				} else {
					while(l < point_) {
						*out++ = '0';
						++l;
					}
				}
				*out = 0;

				if(auto_mode_) {  // AUTO モード
					if(set_num_) {
						uint32_t unp = out - &buff_[0];  // 小数点以下の数（小数点を含む）
						uint32_t all = unp + udec_num_;
						if(exp_mode_) all += 4;
						if(sch != 0) ++all;
						if(num_ > all) {
							num_ -= all;  // 空白の数
							num_ += udec_num_;
							if(sch != 0) ++num_;
						} else {
							num_ = udec_num_;
						}
						if(unp == 0 && udec_num_ == 6) {
							
						}
					} else {
						num_ = udec_num_;
					}
				}
			}
			out_str_(rnb_org, sch, udec_num_);
			if(point_ > 0) {
				str_(buff_);
			}
		}


#ifndef NO_FLOAT_FORM
		void out_real_(float v, char e) noexcept
		{
			void* p = &v;
			uint32_t fpv = *(uint32_t*)p;
			bool sign = fpv >> 31;
			int16_t exp = (fpv >> 22) & 0x1ff;

			if(exp >= 0x1fe) {  // inf, nan の検出
				if(sign) chaout_('-');
				if(exp & 1) {
					out_str_("nan", 0, 3);
				} else {
					out_str_("inf", 0, 3);
				}
				return;
			}
			exp >>= 1;

			exp -= 127;	// bias (-127)
			int32_t val = fpv & 0x7fffff;	// 23 bits
			int16_t shift = 23;
			if(val == 0 && exp == -127) { // [0.0]
			} else {
				val |= 0x800000; // add offset 1.0
			}
			shift -= exp;

			// 64 ビットに拡張
			uint64_t v64 = static_cast<uint64_t>(val);
			if(shift < 28) {
				shift += 32;
				v64 <<= 32;
			}

			// エキスポーネント表記の場合に乗数を求める。
			int8_t decexp = 0;
			if(e != 0) {
				auto ref = static_cast<uint64_t>(1) << shift;
				if(v64 < ref) {  // 1.0 以下
					ref -= ref / 10;  // 0.99999 の場合を考慮する為、誤差分を引く
					while(v64 < ref) {  
						v64 *= 10;
						--decexp;
					}
				} else {
					auto ref = static_cast<uint64_t>(2) << shift;
					while(v64 >= ref) {  // 1.9999... 以上の場合
						v64 /= 10;
						++decexp;
					}
				}
			}

			out_fixed_point_<uint64_t>(v64, shift, sign);

			if(e != 0) {
				chaout_(e);
				zerosupp_ = true;
				sign_ = true;
				num_ = 3;
				out_dec_(decexp);
			}
		}


		static float abs_(float val) noexcept { if(val < 0.0f) return -val; else return val; }

		static float pow10_(int n) noexcept
		{
			switch(n) {
			case 4: return 1e4f;
			case 5: return 1e5f;
			case 6: return 1e6f;
			case 7: return 1e7f;
			case 8: return 1e8f;
			case 9: return 1e9f;
			case -4: return 1e-3f;
			case -5: return 1e-5f;
			case -6: return 1e-6f;
			case -7: return 1e-7f;
			case -8: return 1e-8f;
			case -9: return 1e-9f;
			default:
				break;
			}

			float v = 1.0f;
			if(n > 0) {
				while(n > 0) { v *= 10.0f; --n; }
			} else {
				while(n < 0) { v /= 10.0f; ++n; }
			}
			return v;
		}


		void out_auto_real_(float v, char e) noexcept
		{
			if(abs_(v) >= pow10_(6)) {
				exp_mode_ = true;
				out_real_(v, e);
			} else if(abs_(v) < pow10_(-(6 - 2))) {
				exp_mode_ = true;
				out_real_(v, e);
			} else {
				if(abs_(v) < 1.0f) {  // 小数点以下の場合
					// 小数点以下の有効桁を表示する為の全体の桁数を求める。
					int n = point_;
					if(n > 6) n = 6;
					for(int i = 1; i < 9; ++i) {
						if(abs_(v) >= pow10_(-i)) {
							point_ = i + n - 1;
							break;
						}
					}
					if(!set_num_) {
						num_ = point_ + 1;
					}
					mode_ = mode::REAL;
				}
				out_real_(v, 0);
			}
		}
#endif

		void str_sub_(const char* val) noexcept
		{
			if(mode_ == mode::STR) {
				if(val == nullptr) {
					static const char* nullstr = { "(nullptr)" };
					out_str_(nullstr, 0, std::strlen(nullstr));
					error_ = error::null;
				} else {
					zerosupp_ = false;
					out_str_(val, 0, std::strlen(val));
				}
			} else {
				error_ = error::different;
			}
		}


		void pointer_(const void* val) noexcept
		{
			auto v = reinterpret_cast<uint64_t>(val);
			if(sizeof(val) > 4) {
				zerosupp_ = true;
				num_ = 8;
				out_hex_(v >> 32, 'a');
			}
			zerosupp_ = true;
			num_ = 8;
			out_hex_(v, 'a');
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
			num_(0),
			point_(0),
			bitlen_(0),
			udec_num_(0),
			error_(error::none),
			mode_(mode::NONE), zerosupp_(false), sign_(false), nega_(false),
			set_num_(false), set_poi_(false), auto_mode_(false), exp_mode_(false)
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
			num_(0), point_(0),
			bitlen_(0),
			error_(error::none),
			mode_(mode::NONE), zerosupp_(false), sign_(false), nega_(false)
		{
			if(!chaout_.set(buff, size)) {
				error_ = error::out_null;
			}
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
		static CHAOUT& chaout() noexcept { return chaout_; }


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
			@brief  オペレーター「%」(const std::string&)
			@param[in]	val	値
			@return	自分の参照
		*/
		//-----------------------------------------------------------------//
		basic_format& operator % (const std::string& val) noexcept
		{
			if(error_ != error::none) {
				return *this;
			}

			if(mode_ == mode::STR) {
				str_sub_(val.c_str());
			} else {
				error_ = error::unknown;
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
		basic_format& operator % (const char* val) noexcept
		{
			if(error_ != error::none) {
				return *this;
			}

			if(mode_ == mode::STR) {
				str_sub_(val);
			} else if(mode_ == mode::POINTER) {
				pointer_(static_cast<const void*>(val));
			} else {
				error_ = error::unknown;
			}

			reset_();
			next_();
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  オペレーター「%」(char*)
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
				str_sub_(val);
			} else if(mode_ == mode::POINTER) {
				pointer_(static_cast<const void*>(val));
			} else {
				error_ = error::unknown;
			}

			reset_();
			next_();
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  オペレーター「%」(std::string&)
			@param[in]	val	値
			@return	自分の参照
		*/
		//-----------------------------------------------------------------//
		basic_format& operator % (std::string& val) noexcept
		{
			if(error_ != error::none) {
				return *this;
			}

			if(mode_ == mode::STR) {
				str_sub_(val.c_str());
			} else {
				error_ = error::unknown;
			}

			reset_();
			next_();
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  オペレーター「%」
			@param[in]	val	ポインター型
			@return	自分の参照
		*/
		//-----------------------------------------------------------------//
		template <typename T>
		basic_format& operator % (T* val) noexcept
		{
			if(error_ != error::none) {
				return *this;
			}

			if(mode_ == mode::POINTER) {
				pointer_(static_cast<const void*>(val));
			} else {
				error_ = error::unknown;
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
				if(mode_ == mode::CHA) {
					auto chn = static_cast<int32_t>(val);
					if(chn > -128 && chn < 128) {
						chaout_(chn);
					} else {  // over range
						error_ = error::over;
					}
				} else {
					decimal_(static_cast<int32_t>(val), std::is_signed<T>::value);
				}
#ifndef NO_FLOAT_FORM
			} else if(std::is_floating_point<T>::value) {
				if(!set_poi_) point_ = 6;
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
				case mode::REAL_AUTO_CAPS:
					auto_mode_ = true;
					out_auto_real_(val, 'E');
					break;
				case mode::REAL_AUTO:
					auto_mode_ = true;
					out_auto_real_(val, 'e');
					break;
				default:
					error_ = error::different;
					break;
				}
#endif
			} else {
				error_ = error::unknown;
			}

			reset_();
			next_();
			return *this;
		}
	};

	template <class CHAOUT> CHAOUT basic_format<CHAOUT>::chaout_;

	typedef basic_format<stdout_buffered_chaout<256> > format;
	typedef basic_format<stdout_chaout> nformat;
	typedef basic_format<memory_chaout> sformat;
	typedef basic_format<null_chaout> null_format;
	typedef basic_format<size_chaout> size_format;
}
