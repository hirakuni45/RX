#pragma once
//=====================================================================//
/*!	@file
	@brief	コマンド入力クラス
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>

extern "C" {
	void sci_putch(char ch);
	void sci_puts(const char *str);
	char sci_getch(void);
	uint32_t sci_length(void);
};

namespace utils {

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    /*!
        @brief  command class
		@param[in]	buffsize	バッファサイズ（最小でも９）
    */
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <int buffsize>
	class command {
		char	buff_[buffsize];
		short	bpos_;
		short	pos_;
		short	len_;

		const char*	prompt_;

		void clear_line_() {
			// VT-100 ESC シーケンス 
			sci_putch(0x1b);
			sci_putch('[');
			sci_putch('0');
			sci_putch('J');
		}

		void crlf_() {
			sci_putch('\r');	///< CR
			sci_putch('\n');	///< LF
		}
	public:
        //-----------------------------------------------------------------//
        /*!
            @brief  コンストラクター
        */
        //-----------------------------------------------------------------//
		command() : bpos_(-1), pos_(0), len_(0), prompt_(0) { buff_[0] = 0; }


        //-----------------------------------------------------------------//
        /*!
            @brief  プロムプト文字列を設定
			@param[in]	text	文字列
        */
        //-----------------------------------------------------------------//
		void set_prompt(const char* text) { prompt_ = text; }


        //-----------------------------------------------------------------//
        /*!
            @brief  サービス @n
					定期的に呼び出す
			@return 「Enter」キーが押されたら「true」
        */
        //-----------------------------------------------------------------//
		bool service() {
			if(bpos_ < 0 && pos_ == 0) {
				if(prompt_) sci_puts(prompt_);
			}
			bpos_ = pos_;
			while(sci_length()) {
				if(pos_ >= (buffsize - 1)) {	///< バッファが溢れた・・
					sci_putch('\\');		///< バックスラッシュ
					buff_[buffsize - 1] = 0;
					pos_ = 0;
					bpos_ = -1;
					crlf_();
					return false;
				} else if(pos_ >= (buffsize - 8)) {	///< バッファが溢れそうな警告
					sci_putch('G' - 0x40);	///< Ctrl-G
				}

				char ch = sci_getch();
				switch(ch) {
				case '\r':	///< Enter キー
					buff_[pos_] = 0;
					len_ = pos_;
					clear_line_();
					crlf_();
					pos_ = 0;
					bpos_ = -1;
					return true;
				case 0x08:	///< バックスペース
					if(pos_) {
						--pos_;
						sci_putch(0x08);
						if(buff_[pos_] < 0x20) {
							sci_putch(0x08);
						}
					} else {
						pos_ = 0;
						bpos_ = -1;
						crlf_();
					}
					break;
				default:
					if(ch < 0x20) {	///< 他の ctrl コード
						buff_[pos_] = ch;
						++pos_;
						sci_putch('^');
						sci_putch(ch + 0x40);
					} else {
						buff_[pos_] = ch;
						++pos_;
						sci_putch(ch);
					}
					break;
				}
			}
			return false;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  コマンド行を取得
			@return コマンド行
        */
        //-----------------------------------------------------------------//
		const char* get_command() const { return buff_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  ワードを取得
			@param[in]	argc	ワード位置
			@param[in]	limit	ワード文字列リミット数
			@param[out]	word	ワード文字列格納ポインター
			@return 取得できたら「true」を返す
        */
        //-----------------------------------------------------------------//
		bool get_word(short n, short limit, char* word) {
			const char* p = buff_;
			char bc = ' ';
			const char* wd = p;
			while(1) {
				char ch = *p;
				if(bc == ' ' && ch != ' ') {
					wd = p;
				}
				if(bc != ' ' && (ch == ' ' || ch == 0)) {
					if(n == 0) {
						short i;
						for(i = 0; i < (p - wd); ++i) {
							--limit;
							if(limit == 0) break;
							word[i] = wd[i];
						}
						word[i] = 0;
						return true;
					}
					--n;
				}
				if(ch == 0) break;
				bc = ch;
				++p;
			}
			return false;
		}
	};
}
