#pragma once
//=====================================================================//
/*! @file
    @brief  input クラス @n
			数値、文字列などの入力クラス @n
			%b ---> ２進の数値 @n
			%o ---> ８進の数値 @n
			%d ---> １０進の数値 @n
			%u ---> 符号無し１０進（v111 で廃止、%d で自動対応） @n
			%x ---> １６進の数値 @n
			%f ---> 浮動小数点数（float、double） @n
			%c ---> １文字のキャラクター @n
			%a ---> 自動、２進(bnnn)、８進(onnn)、１０進、１６進(xnnn)、浮動小数点を判別 @n
			Exsample: @n
				int v; @n
				if(!(input("%d", parse_text) % v).status()) { @n
					// Parse error. @n
				} else { @n
					// Parse OK! @n
					format("%d\n") % v; @n
				} @n
			・変換時、オーバーフローした場合は、直前の値が出力される。 @n
			・それ以外のエラーの場合、値は出力されない。 @n
			・C++17 以降のコンパイラが必須 @n
			・リトルエンディアン専用 @n
			+ 2019/12/26 15:30- 数値のオート入力機能追加 @n
			! 2020/01/05 02:52- 変換が失敗した場合に、引数の値を保持する @n
			! 2020/01/05 03:22- %c の変換で、変換数カウントが変化しない不具合修正 @n
			! 2020/01/05 06:16- %u 符号無し整数機能を追加（v111 で廃止） @n
			+ 2020/01/15 10:03- std::string 型を定義 @n
			+ 2020/01/24 15:15- 浮動小数点オーバーフローした場合のリミッター追加 @n
			+ 2020/01/24 15:50- 整数変換でオーバーフローが発生したらエラーとする @n
			+ 2020/01/25 17:33- 特殊制御文字を除外する「\」（バックスラッシュ）機能 @n
			+ 2020/02/02 19:47- enum error など共有定義を継承 @n
			! 2022/06/13 15:15- static const を static constexpr へ変更 @n
			+ 2024/08/14 08:57- add header file (cstdint) @n
			+ 2024/12/29 10:40+ cleanup @n
			+ 2024/12/29 17:15+ Support 64 bits integer conversion (v110) @n
			! 2024/12/30 23:50+ '%u' を廃止、エラーステートも一部廃止 (v111) @n
			+ 2024/12/31 14:00+ '%a' における、浮動小数点を受け付け機能 (v112)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <type_traits>
#include <unistd.h>
#include <cmath>
#include <string>
#include <cstdint>
#if (__cplusplus >= 201703L)
#include <string_view>
#endif

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  標準入力ファンクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class def_chainp {
		const char* str_;
		char		last_;
		bool		unget_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	str		入力文字列（省力された場合「sci_getch」を使う）
		*/
		//-----------------------------------------------------------------//
		def_chainp(const char* str = nullptr) : str_(str), last_(0), unget_(false) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  １文字戻す
		*/
		//-----------------------------------------------------------------//
		void unget() {
			unget_ = true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ファンクタ（文字取得）
			@return 文字
		*/
		//-----------------------------------------------------------------//
		char operator() () {
			if(unget_) {
				unget_ = false;
			} else {
				if(str_ == nullptr) {
					char ch;
					if(read(STDIN_FILENO, &ch, 1) == 1) {
						if(ch == '\n') ch = 0;
						last_ = ch;
					} else {
						last_ = 0;
					}
				} else {
					last_ = *str_;
					if(last_ != 0) { ++str_; }
				}
			}
			return last_;
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  汎用入力クラス・ベースクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class input_base {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  エラー種別
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class error : uint8_t {
			none,			///< エラー無し
			cha_sets,		///< 文字セットの不一致
			partition,		///< 分離キャラクターの不一致
			input_type,		///< 無効な入力タイプ
			not_integer,	///< 整数型の不一致
			sign_type,		///< 符号無し整数にマイナス符号
			not_float,		///< 浮動小数点型の不一致
			terminate,		///< 終端文字の不一致
			overflow,		///< オーバーフロー
		};
	};

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  汎用入力クラス
		@param[in]	INP	文字入力クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class INP>
	struct basic_input : public input_base {

		static constexpr uint16_t VERSION = 112;	///< クラス・バージョン

	private:
		const char*	form_;

		INP			inp_;

		enum class mode : uint8_t {
			NONE,
			CHA,
			BIN,
			OCT,
			DEC,
			HEX,
			REAL,
			AUTO,
		};
		mode	mode_;
		error	error_;
		uint8_t	nbc_;
		bool	ovf_;
		int		num_;

		template <typename T>
		T bin_() noexcept {
			T a = 0;
			constexpr auto lim = static_cast<T>(1) << (sizeof(T) * 8 - 1);
			char ch;
			while((ch = inp_()) != 0) {
				if(ch >= '0' && ch <= '1') {
					if((a & lim) != 0) {
						ovf_ = true;
					}
					if(!ovf_) {
						a <<= 1;
						a += ch - '0';
					}
				} else if(nbc_ != 0 && ch == ' ') {
					// 文字数指定がある場合「スペース」は '0' と同等に扱う
				} else {
					break;
				}
				if(nbc_ > 0) {
					nbc_--;
					if(nbc_ == 0) break;
				}
			}
			return a;
		}

		template <typename T>
		T oct_() noexcept {
			T a = 0;
			constexpr auto lim = static_cast<T>(0b111) << (sizeof(T) * 8 - 4);
			char ch;
			while((ch = inp_()) != 0) {
				if(ch >= '0' && ch <= '7') {
					if((a & lim) != 0) {
						ovf_ = true;
					}
					if(!ovf_) {
						a <<= 3;
						a += ch - '0';
					}
				} else if(nbc_ != 0 && ch == ' ') {
					// 文字数指定がある場合「スペース」は '0' と同等に扱う
				} else {
					break;
				}
				if(nbc_ > 0) {
					nbc_--;
					if(nbc_ == 0) break;
				}
			}
			return a;
		}

		template <typename T>
		T dec_() noexcept {
			T a = 0;
			char ch;
			while((ch = inp_()) != 0) {
				if(!ovf_ && ch >= '0' && ch <= '9') {
					if constexpr (std::is_signed<T>::value) {
						a *= 10;
						a += ch - '0';
						if(a < 0) {
							ovf_ = true;
						}
					} else {
						auto b = a;
						a *= 10;
						a += ch - '0';
						if(b > a) {
							ovf_ = true;
						}
					}
				} else if(nbc_ != 0 && ch == ' ') {
					// 文字数指定がある場合「スペース」は '0' と同等に扱う
				} else {
					break;
				}
				if(nbc_ > 0) {
					nbc_--;
					if(nbc_ == 0) break;
				}
			}
			return a;
		}

		template <typename T>
		T hex_() noexcept {
			T a = 0;
			constexpr auto lim = static_cast<T>(0b1111) << (sizeof(T) * 8 - 4);
			char ch;
			while((ch = inp_()) != 0) {
				auto ovf = (a & lim) != 0;
				if(ch >= 'a') { ch -= 0x20; }
				if(ch >= '0' && ch <= '9') {
					if(ovf) { ovf_ = true; }
					if(!ovf_) {
						a <<= 4;
						a += ch - '0';
					}
				} else if(ch >= 'A' && ch <= 'F') {
					if(ovf) { ovf_ = true; }
					if(!ovf_) {
						a <<= 4;
						a += ch - 'A' + 10;
					}
				} else if(nbc_ != 0 && ch == ' ') {
					// 文字数指定がある場合「スペース」は '0' と同等に扱う
				} else {
					break;
				}
				if(nbc_ > 0) {
					nbc_--;
					if(nbc_ == 0) break;
				}
			}
			return a;
		}

		template <typename T>
		T auto_num_() noexcept
		{
			enum class TYPE : uint8_t {
				dec,
				bin,
				oct,
				hex,
			};

			typedef typename std::make_unsigned<T>::type U;

			char ch = inp_();
			if(ch != '0') {  // 最初に０がある場合無視
				inp_.unget();
			}
			ch = inp_();
			if(ch >= 0x60) { ch -= 0x20; }
			T v = 0;
			TYPE t(TYPE::dec);
			if(ch == 'B') {
				t = TYPE::bin;
			} else if(ch == 'X') {
				t = TYPE::hex;
			} else if(ch == 'O') {
				t = TYPE::oct;
			} else {
				inp_.unget();
			}
			switch(t) {
			case TYPE::bin:
				v = bin_<U>();
				break;
			case TYPE::oct:
				v = oct_<U>();
				break;
			case TYPE::hex:
				v = hex_<U>();
				break;
			default:
				v = dec_<T>();
				break;
			}
			return v;
		}

		template<typename T>
		T real_() noexcept
		{
			struct real_t {
				uint32_t	a;
				uint32_t	b;
				uint32_t	c;
				bool		sign;
				bool		p;
				bool		ovf;

				real_t() : a(0), b(0), c(1), sign(false), p(false), ovf(false) { }

				void set_sign(bool sig = true) {
					sign = sig;
				}

				void add(char ch)
				{
					if(c >= (0xffff'ffff / 10)) {
						if(!p) ovf = true;
					} else {
						a *= 10;
						a += static_cast<uint32_t>(ch - '0');
						c *= 10;
					}
				}

				void point() {
					b = a;
					a = 0;
					c = 1;
					p = true;
				}

				T get() const {
					if(p) {
						T tmp = static_cast<T>(b) + static_cast<T>(a) / static_cast<T>(c);
						if(sign) return -tmp;
						return tmp;
					} else {
						T tmp = static_cast<T>(a);
						if(sign) return -tmp;
						else return tmp;
					}				
				}
			};

			real_t	base;
			real_t	exp;
			bool expf = false;
			char ch;
			while((ch = inp_()) != 0) {
				if(ch == '+') {
					if(expf) {
						if(exp.a != 0) break; 
						exp.set_sign(false);
					} else {
						if(base.a != 0) break;
						base.set_sign(false);
					}
				} else if(ch == '-') {
					if(expf) {
						if(exp.a != 0) break; 
						exp.set_sign();
					} else {
						if(base.a != 0) break;
						base.set_sign();
					}
				} else if(ch >= '0' && ch <= '9') {
					if(expf) {
						exp.add(ch);
					} else { 
						base.add(ch);
					}
				} else if(ch == '.') {
					if(expf) {
						if(exp.p) break;
						exp.point();
					} else {
						if(base.p) break;
						base.point();
					}
				} else if(ch == 'e' || ch == 'E') {
					if(expf) break;
					expf = true;
				} else {
					break;
				}
			}

			if(base.ovf || exp.ovf) {
				ovf_ = true;
			}

			if(expf) {
				return base.get() * pow(static_cast<T>(10), exp.get());
			} else {
				return base.get();
			}
		}

		void next_() noexcept
		{
			enum class fmm : uint8_t {
				none,
				type,
			};
			fmm cm = fmm::none;

			char ch;
			bool esc = false;
			while((ch = *form_++) != 0) {
				switch(cm) {
				case fmm::none:
					if(esc) {
						esc = false;
						if(ch != inp_()) {
							error_ = error::partition;
							return;
						}
						break;
					}
					if(ch == '\\') {
						esc = true;
					} else if(ch == '[') {
						auto a = inp_();
						const char* p = form_;
						bool ok = false;
						while((ch = *p++) != 0 && ch != ']') {
							if(ch == a) ok = true;
						}
						if(ch == 0) --p;
						form_ = p;
						if(!ok) {
							error_ = error::cha_sets;
							return;
						}
					} else if(ch == '%' && *form_ != '%') {
						cm = fmm::type;
						nbc_ = 0;
					} else if(ch != inp_()) {
						error_ = error::partition;
						return;
					}
					break;

				case fmm::type:
					if(ch >= 'a') ch -= 0x20;
					if(ch >= '0' && ch <= '9') {
						nbc_ *= 10;
						nbc_ += ch - '0';
					} else if(ch == 'B') {
						mode_ = mode::BIN;
						return;
					} else if(ch == 'O') {
						mode_ = mode::OCT;
						return;
					} else if(ch == 'D') {
						mode_ = mode::DEC;
						return;
					} else if(ch == 'X') {
						mode_ = mode::HEX;
						return;
					} else if(ch == 'F') {
						mode_ = mode::REAL;
						return;
					} else if(ch == 'C') {
						mode_ = mode::CHA;
						return;
					} else if(ch == 'A') {
						mode_ = mode::AUTO;
						return;
					} else {
						error_ = error::input_type;
						return;
					}
				}
			}
			if(ch == 0 && inp_() == 0) {

			} else {
				error_ = error::terminate;
			}
		}

		bool neg_() noexcept {
			bool neg = false;
			auto s = inp_();
			if(s == '-') {
				neg = true;
				if(nbc_ > 0) nbc_--;
			} else if(s == '+') {
				neg = false;
				if(nbc_ > 0) nbc_--;
			} else {
				inp_.unget();
			}
			return neg;
		}

		template <typename T>
		T nb_dec_() noexcept
		{
			typedef typename std::make_unsigned<T>::type U;
			typedef typename std::make_signed<T>::type S;

			auto nbc = nbc_;
			auto neg = neg_();
			if(nbc > 0 && nbc_ == 0) {
				error_ = error::not_integer;
				return 0;
			}

			auto sign = std::is_signed<T>::value;
			T v = 0;
			switch(mode_) {
			case mode::BIN:
				v = bin_<U>();
				break;
			case mode::OCT:
				v = oct_<U>();
				break;
			case mode::DEC:
				if(!sign) {
					if(neg) {  // 符号無しにマイナス符号を付けた場合
						error_ = error::sign_type;
						return 0;
					}
				}
				v = dec_<T>();
				break;
			case mode::HEX:
				v = hex_<U>();
				break;
			case mode::AUTO:
				v = auto_num_<T>();
				break;
			default:
				error_ = error::not_integer;
				break;
			}
			if(error_ == error::none) {
				if(nbc == 0) {
					inp_.unget();
				}
				next_();
			}
			if(neg) {
				return -static_cast<S>(v);
			} else {
				return static_cast<S>(v);
			}
		}

		template <typename T>
		T nb_real_() noexcept
		{
			bool neg = neg_();

			T v = 0.0f;
			switch(mode_) {
			case mode::REAL:
			case mode::AUTO:
				v = real_<T>();
				break;
			default:
				error_ = error::not_float;
				break;
			}
			if(error_ == error::none) {
				inp_.unget();
				next_();
			}
			if(neg) return -v;
			else return v;			
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	form	フォーマット式
			@param[in]	inp		変換文字列（nullptrの場合、sci_getch で取得）
		*/
		//-----------------------------------------------------------------//
		basic_input(const char* form, const char* inp = nullptr) noexcept :
			form_(form), inp_(inp),
			mode_(mode::NONE), error_(error::none), nbc_(0), ovf_(false), num_(0)
		{
			next_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター std::string
			@param[in]	form	フォーマット式
			@param[in]	inp		変換文字列（nullptrの場合、sci_getch で取得）
		*/
		//-----------------------------------------------------------------//
		basic_input(const std::string& form, const::std::string& inp) noexcept :
			basic_input(form.c_str(), (inp.empty() ? nullptr : inp.c_str())) { }

#if (__cplusplus >= 201703L)
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター std::string_view
			@param[in]	form	フォーマット式
			@param[in]	inp		変換文字列（nullptrの場合、sci_getch で取得）
		*/
		//-----------------------------------------------------------------//
		basic_input(const std::string_view& form, const::std::string_view& inp) noexcept :
			basic_input(form.data(), (inp.empty() ? nullptr : inp.data())) { }
#endif

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
		bool status() const noexcept {
			return error_ == error::none;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  正常変換数を取得
			@return 正常変換数
		*/
		//-----------------------------------------------------------------//
		int num() const noexcept { return num_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  テンプレート・オペレーター「%」
			@param[in]	val	整数型
			@return	自分の参照
		*/
		//-----------------------------------------------------------------//
		template <typename T>
		basic_input& operator % (T& val) noexcept
		{
			if(error_ != error::none) return *this;

			if constexpr(std::is_floating_point<T>::value) {
				auto tmp = nb_real_<T>();
				if(error_ == error::none) {
					++num_;
					val = tmp;
				}
			} else {
				if constexpr(sizeof(T) == 1) {
					if(mode_ == mode::CHA) {
						auto tmp = inp_(); 
						if(error_ == error::none) {
							++num_;
							val = tmp;
						}
						next_();
					} else {
						error_ = error::input_type;
					}
				} else {
					T tmp = nb_dec_<T>();
					if(error_ == error::none) {
						++num_;
						val = tmp;
					}
				}
			}
			if(ovf_) {
				error_ = error::overflow;
				ovf_ = false;
			}
			return *this;
		}
	};

	typedef basic_input<def_chainp> input;
}
