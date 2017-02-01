#pragma once
//=====================================================================//
/*! @file
    @brief  input クラス @n
			数値、文字列などの入力クラス
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <type_traits>

extern "C" {

	char sci_getch(void);

};

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
		def_chainp(const char* str = nullptr) : str_(str), last_(0), unget_(false) { }

		void unget() {
			unget_ = true;
		}

		char operator() () {
			if(unget_) {
				unget_ = false;
			} else {
				if(str_ == nullptr) {
					last_ = sci_getch();
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
		@param[in]	INP	入力クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class INP>
	class basic_input {

		const char*	form_;

		INP			inp_;

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

		enum class mode : uint8_t {
			NONE,
			BIN,
			OCT,
			DEC,
			HEX,
		};
		mode	mode_;
		bool	err_;

		int		num_;

		enum class fmm : uint8_t {
			none,
			type,

		};

		void next_()
		{
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
							err_ = true;
							return;
						}
					} else if(ch == '%' && *form_ != '%') {
						cm = fmm::type;
					} else if(ch != inp_()) {
						err_ = true;
						return;
					}
					break;
				case fmm::type:
					if(ch == 'b' || ch == 'B') {
						mode_ = mode::BIN;
					} else if(ch == 'o' || ch == 'O') {
						mode_ = mode::OCT;
					} else if(ch == 'd' || ch == 'D') {
						mode_ = mode::DEC;
					} else if(ch == 'x' || ch == 'X') {
						mode_ = mode::HEX;
					} else {
						err_ = true;
					}
					return;
				}
			}
			if(ch == 0 && inp_() == 0) ;
			else {
				err_ = true;
			}
		}


		int32_t nb_(bool sign = true)
		{
			bool neg = false;
			if(sign) {
				auto s = inp_();
				if(s == '-') { neg = true; }
				else if(s == '+') { neg = false; }
				else inp_.unget();
			}
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
				err_ = true;
				break;
			}
			if(!err_) {
				inp_.unget();
				next_();
				if(!err_) ++num_;
			}
			if(neg) return -static_cast<int32_t>(v);
			else return static_cast<int32_t>(v);
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
			mode_(mode::NONE), err_(false), num_(0)
		{
			next_();
		}


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
			if(err_) return *this;
			val = nb_(!std::is_signed<T>::value);
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  オペレーター「=」
		*/
		//-----------------------------------------------------------------//
		basic_input& operator = (const basic_input& in) { return *this; }
	};

	typedef basic_input<def_chainp> input;

}
