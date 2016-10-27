#pragma once
//=====================================================================//
/*!	@file
	@brief	コマンド入力クラス
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstring>

extern "C" {
	void sci_putch(char ch);
	void sci_puts(const char *str);
	char sci_getch(void);
	uint16_t sci_length(void);
};

namespace utils {

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    /*!
        @brief  command class
		@param[in]	buffsize	バッファサイズ（最小でも９）
    */
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <int16_t buffsize>
	class command {
		char	buff_[buffsize];
		int16_t	bpos_;
		int16_t	pos_;
		int16_t	len_;
		int16_t tab_top_;

		const char*	prompt_;

		bool	tab_;

		// VT-100 ESC シーケンス 
		static void clear_line_() {
			sci_putch(0x1b);
			sci_putch('[');
			sci_putch('0');
			sci_putch('J');
		}

		static void save_cursor_() {
			sci_putch(0x1b);
			sci_putch('7');
		}

		static void load_cursor_() {
			sci_putch(0x1b);
			sci_putch('8');
		}

		static void crlf_() {
			sci_putch('\r');	///< CR
			sci_putch('\n');	///< LF
		}
	public:
        //-----------------------------------------------------------------//
        /*!
            @brief  コンストラクター
        */
        //-----------------------------------------------------------------//
		command() : bpos_(-1), pos_(0), len_(0), tab_top_(-1),
			prompt_(nullptr), tab_(false) { buff_[0] = 0; }


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
			tab_ = false;
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
				case '\r':	// Enter キー
					buff_[pos_] = 0;
					len_ = pos_;
					clear_line_();
					crlf_();
					pos_ = 0;
					bpos_ = -1;
					tab_top_ = -1;
					return true;

				case 0x08:	// バックスペース
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

				case '\t':  // TAB キー
					if(tab_top_ < 0) {
						tab_top_ = pos_;
						save_cursor_();
					}
					tab_ = true;
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
					buff_[pos_] = 0;
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
            @brief  ワード数を取得
			@return ワード数を返す
        */
        //-----------------------------------------------------------------//
		uint8_t get_words() const {
			const char* p = buff_;
			char bc = ' ';
			uint8_t n = 0;
			while(1) {
				char ch = *p++;
				if(ch == 0) break;
				if(bc == ' ' && ch != ' ') {
					++n;
				}
				bc = ch;
			}
			return n;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  ワードを取得
			@param[in]	argc	ワード位置
			@param[in]	limit	ワード文字列リミット数
			@param[out]	word	ワード文字列格納ポインター
			@return 取得できたら「true」を返す
        */
        //-----------------------------------------------------------------//
		bool get_word(uint8_t argc, uint8_t limit, char* word) const {
			const char* p = buff_;
			char bc = ' ';
			const char* wd = p;
			while(1) {
				char ch = *p;
				if(bc == ' ' && ch != ' ') {
					wd = p;
				}
				if(bc != ' ' && (ch == ' ' || ch == 0)) {
					if(argc == 0) {
						uint8_t i;
						for(i = 0; i < (p - wd); ++i) {
							--limit;
							if(limit == 0) break;
							word[i] = wd[i];
						}
						word[i] = 0;
						return true;
					}
					--argc;
				}
				if(ch == 0) break;
				bc = ch;
				++p;
			}
			return false;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  ワードを比較
			@param[in]	argc	ワード位置
			@param[in]	key		比較文字列
			@return 
        */
        //-----------------------------------------------------------------//
		bool cmp_word(uint8_t argc, const char* key) const {
			const char* p = buff_;
			char bc = ' ';
			const char* top;
			while(1) {
				char ch = *p;
				if(bc == ' ' && ch != ' ') {
					top = p;
				}
				if(bc != ' ' && (ch == ' ' || ch == 0)) {
					if(argc == 0) {
						return std::strncmp(key, top, p - top) == 0;
					}
					--argc;
				}
				if(ch == 0) break;
				bc = ch;
				++p;
			}
			return false;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  TAB キーが押されたか
			@return 押されたら「true」
        */
        //-----------------------------------------------------------------//
		bool probe_tab() const { return tab_; } 


        //-----------------------------------------------------------------//
        /*!
            @brief  TAB 注入位置のリセット
        */
        //-----------------------------------------------------------------//
		void reset_tab() { tab_top_ = -1; } 


        //-----------------------------------------------------------------//
        /*!
            @brief  TAB キーの候補を注入
			@param[in]	key	注入文字列
        */
        //-----------------------------------------------------------------//
		void injection_tab(const char* key) {
			if(tab_top_ < 0) return;
			std::strcpy(&buff_[tab_top_], key);

			load_cursor_();
			sci_puts(key);
		}
	};
}
