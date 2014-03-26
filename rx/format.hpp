#pragma once
//=====================================================================//
/*! @file
    @brief  簡易 format クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <unistd.h>

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  エラー・ケース
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct error_case {
		enum type {
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
		OUT		out_;

		void str_(const char* str) {
			char ch;
			while((ch = *str++) != 0) {
				out_(ch);
			}
		}
	public:
		void operator() (error_case::type t) {
			if(t == error_case::UNKNOWN_TYPE) {
				str_("Unknown type\n");
			} else if(t == error_case::DIFFERENT_TYPE) {
				str_("Different type\n");
			}
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
			OCTAL,		///< ８進
			DECIMAL,	///< １０進
			U_DECIMAL,	///< １０進（符号無し）
			HEX_CAPS,	///< １６進（大文字）
			HEX,		///< １６進（小文字）
			REAL,		///< 浮動小数点
			NONE_		///< 不明
		};

		OUT			out_;
		ERR			err_;

		const char*	form_;

		uint16_t	real_;
		uint16_t	decimal_;
		uint8_t		mode_;
		bool		zerosupp_;
		bool		sign_;

		void reset_() {
			real_ = decimal_ = 0;
			zerosupp_ = false;
			sign_ = false;
			mode_ = mode::NONE_;
		}

		void next_() {
			char ch;
			bool fm = false;
			bool point = false;
			uint8_t n = 0;
			while((ch = *form_++) != 0) {
				if(fm) {
					if(ch == '+') {
						sign_ = true;
					} else if(ch >= '0' && ch <= '9') {
						if(n == 0 && ch == '0') {
							zerosupp_ = true;
						} else if(point) {
							if(decimal_ < 6553) {
								decimal_ *= 10;
								decimal_ += static_cast<uint16_t>(ch - '0');
							}
						} else {
							if(real_ < 6553) {
								real_ *= 10;
								real_ += static_cast<uint16_t>(ch - '0');
							}
						}
						++n;
					} else if(ch == '.') {
						point = true;
					} else if(ch == 's' || ch == 'S') {
						mode_ = mode::STR;
						return;
					} else if(ch == 'c' || ch == 'C') {
						mode_ = mode::CHA;
						return;
					} else if(ch == 'b' || ch == 'B') {
						mode_ = mode::BINARY;
						return;
					} else if(ch == 'o' || ch == 'O') {
						mode_ = mode::OCTAL;
						return;
					} else if(ch == 'd' || ch == 'D') {
						mode_ = mode::DECIMAL;
						return;
					} else if(ch == 'u' || ch == 'U') {
						mode_ = mode::U_DECIMAL;
						return;
					} else if(ch == 'x') {
						mode_ = mode::HEX;
						return;
					} else if(ch == 'X') {
						mode_ = mode::HEX_CAPS;
						return;
					} else if(ch == 'f' || ch == 'F') {
						mode_ = mode::REAL;
						return;
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
			while((ch = *str++) != 0) {
				out_(ch);
			}
		}

		void out_bin_(int v) {
			char tmp[34];
			char* p = &tmp[34 - 1];
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

		void out_oct_(int v) {
			char tmp[14];
			char* p = &tmp[14 - 1];
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

		void out_dec_(int v) {
			char tmp[12];
			char* p = &tmp[12 - 1];
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
			char* p = &tmp[12 - 1];
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
			char* p = &tmp[10 - 1];
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

		void out_real_(float v) {
			char tmp[16];
			char* p = &tmp[16 - 1];
			*p = 0;
			uint8_t n = 0;


			out_str_(p, n);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		format(const char* form) : form_(form), real_(0), decimal_(0),
			mode_(mode::NONE_), zerosupp_(false), sign_(false) { next_(); }


		//-----------------------------------------------------------------//
		/*!
			@brief  オペレーター「%」
			@param[in]	val	文字
			@return	自分の参照
		*/
		//-----------------------------------------------------------------//
		format& operator % (const char val) {
			if(mode_ == mode::CHA) {
				out_(val);
			} else {

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
			} else if(mode_ == mode::OCTAL) {
				out_oct_(val);
			} else if(mode_ == mode::DECIMAL) {
				out_dec_(val);
			} else if(mode_ == mode::HEX) {
				out_hex_(static_cast<unsigned int>(val), 'a');
			} else if(mode_ == mode::HEX_CAPS) {
				out_hex_(static_cast<unsigned int>(val), 'A');
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
			} else if(mode_ == mode::OCTAL) {
				out_oct_(val);
			} else if(mode_ == mode::DECIMAL) {
				out_dec_(val);
			} else if(mode_ == mode::U_DECIMAL) {
				out_dec_(val);
			} else if(mode_ == mode::HEX) {
				out_hex_(val, 'a');
			} else if(mode_ == mode::HEX_CAPS) {
				out_hex_(val, 'A');
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
			@param[in]	val	浮動小数点
			@return	自分の参照
		*/
		//-----------------------------------------------------------------//
		format& operator % (float val) {
			if(mode_ == mode::REAL) {
				out_real_(val);
			} else {
				err_(error_case::DIFFERENT_TYPE);
			}
			reset_();
			next_();
			return *this;
		}
	};
}
