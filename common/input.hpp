#pragma once
//=====================================================================//
/*! @file
    @brief  input クラス @n
			数値、文字列などの入力クラス @n
			%b ---> ２進の数値 @n
			%o ---> ８進の数値 @n
			%d ---> １０進の数値 @n
			%x ---> １６進の数値 @n
			%f ---> 浮動小数点数（float、double） @n
			%c ---> １文字のキャラクター @n
			%% ---> '%' のキャラクター
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <type_traits>
#include <unistd.h>

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
					if(read(0, &ch, 1) == 1) {
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
		@brief  汎用入力クラス
		@param[in]	INP	文字入力クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class INP>
	class basic_input {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  エラー種別
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class error : uint8_t {
			none,			///< エラー無し
			cha_sets,		///< 文字セットの不一致
			partition,		///< 仕切りキャラクターの不一致
			input_type,		///< 無効な入力タイプ
			not_integer,	///< 整数の不一致
			not_float,		///< 浮動小数点の不一致
			terminate,		///< 終端文字の不一致
		};

	private:
		const char*	form_;

		INP			inp_;

		enum class mode : uint8_t {
			NONE,
			BIN,
			OCT,
			DEC,
			HEX,
			REAL,
			CHA,
		};
		mode	mode_;
		error	error_;
		int		num_;

		uint32_t bin_() {
			uint32_t a = 0;
			char ch;
			while((ch = inp_()) != 0 && ch >= '0' && ch <= '1') {
				a <<= 1;
				a += ch - '0';
			}
			return a;
		}

		uint32_t oct_() {
			uint32_t a = 0;
			char ch;
			while((ch = inp_()) != 0 && ch >= '0' && ch <= '7') {
				a <<= 3;
				a += ch - '0';
			}
			return a;
		}

		uint32_t dec_() {
			uint32_t a = 0;
			char ch;
			while((ch = inp_()) != 0 && ch >= '0' && ch <= '9') {
				a *= 10;
				a += ch - '0';
			}
			return a;
		}

		uint32_t hex_() {
			uint32_t a = 0;
			char ch;
			while((ch = inp_()) != 0) {
				if(ch >= '0' && ch <= '9') {
					a <<= 4;
					a += ch - '0';
				} else if(ch >= 'A' && ch <= 'F') {
					a <<= 4;
					a += ch - 'A' + 10;
				} else if(ch >= 'a' && ch <= 'f') {
					a <<= 4;
					a += ch - 'a' + 10;
				} else {
					break;
				}
			}
			return a;
		}


		template<typename T>
		T real_() {
			uint32_t a = 0;
			uint32_t b = 0;
			uint32_t c = 1;
			char ch;
			bool p = false;
			while((ch = inp_()) != 0) {
				if(ch >= '0' && ch <= '9') {
					a *= 10;
					a += ch - '0';
					c *= 10;
				} else if(!p && ch == '.') {
					b = a;
					a = 0;
					c = 1;
					p = true;
				} else {
					break;
				}
			}
			if(p) {
				return static_cast<T>(b) + (static_cast<T>(a) / static_cast<T>(c));
			} else {
				return static_cast<T>(a); 
			}
		}


		void next_()
		{
			enum class fmm : uint8_t {
				none,
				type,
			};
			fmm cm = fmm::none;

			char ch;
			while((ch = *form_++) != 0) {
				switch(cm) {
				case fmm::none:
					if(ch == '[') {
						auto a = inp_();
						const char* p = form_;
						bool ok = false;
						while((ch = *p++) != 0 && ch != ']') {
							if(ch == a) ok = true;
						}
						form_ = p;
						if(!ok) {
							error_ = error::cha_sets;
							return;
						}
					} else if(ch == '%' && *form_ != '%') {
						cm = fmm::type;
					} else if(ch != inp_()) {
						error_ = error::partition;
						return;
					}
					break;

				case fmm::type:
					switch(ch) {
					case 'b':
						mode_ = mode::BIN;
						break;
					case 'o':
						mode_ = mode::OCT;
						break;
					case 'd':
						mode_ = mode::DEC;
						break;
					case 'x':
						mode_ = mode::HEX;
						break;
					case 'f':
						mode_ = mode::REAL;
						break;
					case 'c':
						mode_ = mode::CHA;
						break;
					default:
						error_ = error::input_type;
						break;
					}
					return;
				}
			}
			if(ch == 0 && inp_() == 0) ;
			else {
				error_ = error::terminate;
			}
		}


		bool neg_() {
			bool neg = false;
			auto s = inp_();
			if(s == '-') { neg = true; }
			else if(s == '+') { neg = false; }
			else inp_.unget();
			return neg;
		}


		void skip_space_() {
			while(1) {
				char ch = inp_();
				if(ch != ' ') {
					inp_.unget();
					return;
				}
			}
		}


		int32_t nb_int_(bool sign = true)
		{
			skip_space_();
			auto neg = neg_();

			uint32_t v = 0;
			switch(mode_) {
			case mode::BIN:
				v = bin_();
				break;
			case mode::OCT:
				v = oct_();
				break;
			case mode::DEC:
				v = dec_();
				break;
			case mode::HEX:
				v = hex_();
				break;
			default:
				error_ = error::not_integer;
				break;
			}
			if(error_ == error::none) {
				inp_.unget();
				next_();
				if(error_ == error::none) ++num_;
			}
			if(sign && neg) return -static_cast<int32_t>(v);
			else return static_cast<int32_t>(v);
		}


		template <typename T>
		T nb_real_()
		{
			skip_space_();
			bool neg = neg_();

			T v = 0.0f;
			switch(mode_) {
			case mode::REAL:
				v = real_<T>();
				break;
			default:
				error_ = error::not_float;
				break;
			}
			if(error_ == error::none) {
				inp_.unget();
				next_();
				if(error_ == error::none) ++num_;
			}
			if(neg) return -v;
			else return v;			
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	form	入力形式
			@param[in]	inp		変換文字列（nullptrの場合、sci_getch で取得）
		*/
		//-----------------------------------------------------------------//
		basic_input(const char* form, const char* inp = nullptr) : form_(form), inp_(inp),
			mode_(mode::NONE), error_(error::none), num_(0)
		{
			next_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  エラー種別を返す
			@return エラー
		*/
		//-----------------------------------------------------------------//
		error get_error() const { return error_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  変換ステータスを返す
			@return 変換が全て正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool status() const { return error_ == error::none; }


		//-----------------------------------------------------------------//
		/*!
			@brief  正常変換数を取得
			@return 正常変換数
		*/
		//-----------------------------------------------------------------//
		int num() const { return num_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  テンプレート・オペレーター「%」
			@param[in]	val	整数型
			@return	自分の参照
		*/
		//-----------------------------------------------------------------//
		template <typename T>
		basic_input& operator % (T& val)
		{
			if(error_ != error::none) return *this;

			if(std::is_floating_point<T>::value) {
				val = nb_real_<T>();
			} else {
				if(mode_ == mode::CHA) {
					val = inp_();
					next_();
				} else {
					val = nb_int_(std::is_signed<T>::value);
				}
			}
			return *this;
		}
	};

	typedef basic_input<def_chainp> input;
}
