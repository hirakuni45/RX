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
		@param[in]	INP	文字入力クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class INP>
	class basic_input {

		const char*	form_;

		INP			inp_;

		enum class mode : uint8_t {
			NONE,
			BIN,
			OCT,
			DEC,
			HEX,
			FLOAT,
		};
		mode	mode_;
		bool	err_;

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


		float real_() {
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
				} else if(ch == '.') {
					b = a;
					a = 0;
					c = 1;
					p = true;
				} else {
					break;
				}
			}
			if(p) {
				return static_cast<float>(b) + static_cast<float>(a) / static_cast<float>(c);
			} else {
				return static_cast<float>(a); 
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
					if(ch >= 0x60) ch -= 0x20;
					if(ch == 'B') {
						mode_ = mode::BIN;
					} else if(ch == 'O') {
						mode_ = mode::OCT;
					} else if(ch == 'D') {
						mode_ = mode::DEC;
					} else if(ch == 'X') {
						mode_ = mode::HEX;
					} else if(ch == 'F') {
						mode_ = mode::FLOAT;
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


		bool neg_() {
			bool neg = false;
			auto s = inp_();
			if(s == '-') { neg = true; }
			else if(s == '+') { neg = false; }
			else inp_.unget();
			return neg;
		}


		int32_t nb_int_(bool sign = true)
		{
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
				err_ = true;
				break;
			}
			if(!err_) {
				inp_.unget();
				next_();
				if(!err_) ++num_;
			}
			if(sign && neg) return -static_cast<int32_t>(v);
			else return static_cast<int32_t>(v);
		}


		float nb_real_()
		{
			bool neg = neg_();

			float v = 0.0f;
			switch(mode_) {
			case mode::FLOAT:
				v = real_();
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
			@brief  変換ステータスを返す
			@return 変換が全て正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool status() const { return !err_; }


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

			if(std::is_floating_point<T>::value) {
				val = nb_real_();
			} else {
				val = nb_int_(std::is_signed<T>::value);
			}
			return *this;
		}
	};

	typedef basic_input<def_chainp> input;
}
