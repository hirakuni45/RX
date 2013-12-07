#pragma once
//=====================================================================//
/*!	@file
	@brief	文字列の書式と表示クラス @n
			Copyright 2013 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>



namespace utils {

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    /*!
        @brief  chout クラス
    */
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct chout {
		static const char endl = '\n';

	private:
		char		sup_ch_;
		char		hex_ch_;
		uint8_t		len_;

	public:
        //-----------------------------------------------------------------//
        /*!
            @brief  コンストラクター
			@param[in]	out	文字出力関数
        */
        //-----------------------------------------------------------------//
		chout() : sup_ch_('0'), hex_ch_('a'), len_(0) { }


        //-----------------------------------------------------------------//
        /*!
            @brief  16 進表示の英数字を大文字にする
			@param[in]	cap	「false」を指定すると小文字
        */
        //-----------------------------------------------------------------//
		void hexa_decimal_capital(bool cap = true) {
			if(cap) hex_ch_ = 'A'; else hex_ch_ = 'a';
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  表示文字数を指定
			@param[in]	len	表示文字数
        */
        //-----------------------------------------------------------------//
		void set_length(uint8_t len) { len_ = len; }


        //-----------------------------------------------------------------//
        /*!
            @brief  ゼロサプレス時の文字を指定
			@param[in]	ch	文字
        */
        //-----------------------------------------------------------------//
		void suppress_char(char ch) { sup_ch_ = ch; }


        //-----------------------------------------------------------------//
        /*!
            @brief  文字表示
			@param[in]	ch	文字
        */
        //-----------------------------------------------------------------//
		void put(char ch) const {
//			out_(ch);
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  文字列の表示
			@param[in]	str	文字列
        */
        //-----------------------------------------------------------------//
		void string(const char* str) const {
			char ch;
			while((ch = *str++) != 0) {
				put(ch);
			}
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  長さ指定文字列表示
			@param[in]	str	文字列
			@param[in]	len	長さ
        */
        //-----------------------------------------------------------------//
		void len_string(const char* str, uint8_t len) const {
			while(len_ > len) {
				put(sup_ch_);
				++len;
			}
			string(str);
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  16 進数の表示
			@param[in]	val	値
        */
        //-----------------------------------------------------------------//
		uint16_t hexa_decimal(uint32_t val) const {
			char tmp[8 + 1];
			uint16_t pos = sizeof(tmp);
			--pos;
			tmp[pos] = 0;
			do {
				--pos;
				char n = val & 15;
				if(n > 9) tmp[pos] = hex_ch_ - 10 + n;
				else tmp[pos] = '0' + n;
				val >>= 4;
			} while(val != 0) ;

			len_string(&tmp[pos], sizeof(tmp) - pos - 1);
			return sizeof(tmp) - pos - 1;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  10 進数の表示
			@param[in]	val	値
			@param[in]	minus	マイナス符号を表示する場合「true」
			@return	表示文字数
        */
        //-----------------------------------------------------------------//
		uint16_t decimal(uint32_t val, bool minus = false) const {
			char tmp[11 + 1];
			uint16_t pos = sizeof(tmp);
			--pos;
			tmp[pos] = 0;
			do {
				--pos;
				tmp[pos] = '0' + (val % 10);
				val /= 10;
			} while(val != 0) ;

			if(minus) {
				--pos;
				tmp[pos] = '-';
			}

			len_string(&tmp[pos], sizeof(tmp) - pos - 1);
			return sizeof(tmp) - pos - 1;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  符号付き 10 進数の表示
			@param[in]	val	値
			@return	表示文字数
        */
        //-----------------------------------------------------------------//
		uint16_t decimal(int32_t val) const {
			bool minus = false;
			if(val < 0) {
				minus = true;
				val = -val;
			}
			return decimal(static_cast<uint32_t>(val), minus);
		}


		chout& operator << (const uint32_t val) {
			decimal(val);
			return *this;
		}


		chout& operator << (const int32_t val) {
			decimal(val);
			return *this;
		}


		chout& operator << (const char* str) {
			string(str);
			return *this;
		}


		chout& operator << (const char ch) {
			put(ch);
			return *this;
		}
	};
}

