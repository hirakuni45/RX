#pragma once
//=====================================================================//
/*!	@file
	@brief	コマンド入力クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/string_utils.hpp"
#include "common/input.hpp"

// SCI（文字入出力）コンテキストとして、以下の API を定義する必要がある。
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
		@param[in]	BUFN	バッファサイズ（最小でも９）
    */
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint16_t BUFN>
	class command {
		char		buff_[BUFN];
		int16_t		bpos_;
		int16_t		pos_;
		uint16_t	len_;
		int16_t		tab_top_;

		const char*	prompt_;

		bool	tab_;
		bool	esc_;
		uint8_t	esc_step_;

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
			prompt_(nullptr), tab_(false), esc_(false), esc_step_(false)
		{ buff_[0] = 0; }


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
					※文字取得バッファが溢れない程度に呼び出す。
			@return 「Enter」キーが押されたら「true」
        */
        //-----------------------------------------------------------------//
		bool service()
		{
			if(bpos_ < 0 && pos_ == 0) {
				if(prompt_ != nullptr) sci_puts(prompt_);
			}
			bpos_ = pos_;
			tab_ = false;
			while(sci_length()) {
				if(pos_ >= (BUFN - 1)) {	///< バッファが溢れた・・
					sci_putch('\\');		///< バックスラッシュ
					buff_[BUFN - 1] = 0;
					pos_ = 0;
					bpos_ = -1;
					crlf_();
					return false;
				} else if(pos_ >= (BUFN - 8)) {	///< バッファが溢れそうな警告
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

				case 0x1B:  // ESC キー
					esc_ = true;
					esc_step_ = 0;
					break;

				default:
					if(esc_) {
						if(esc_step_ == 0) {
							if(ch == '[') {
								++esc_step_;
							} else {
								esc_ = false;
							}
						} else if(esc_step_ == 1) {
							if(ch == 'A') ;  // Up
							else if(ch == 'B') ;  // Down
							else if(ch == 'C') ;  // Right
							else if(ch == 'D') ;  // Left
							esc_ = false;
						}
					} else {
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
            @brief  ワード数を取得
			@param[in]	sch		単語分離キャラクタ
			@return ワード数を返す
        */
        //-----------------------------------------------------------------//
		uint32_t get_words(char sch = ' ') const {
			return str::get_words(buff_, sch);
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  ワードを取得
			@param[in]	argc	ワード位置
			@param[out]	dst		ワード文字列格納ポインター
			@param[in]	dstlen	ワード文字列リミット数
			@param[in]	sch		単語分離キャラクタ
			@return 取得できたら「true」を返す
        */
        //-----------------------------------------------------------------//
		bool get_word(uint32_t argc, char* dst, uint32_t dstlen, char sch = ' ') const {
			return str::get_word(buff_, argc, dst, dstlen);
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  ワードを比較
			@param[in]	argc	ワード位置
			@param[in]	key		比較文字列
			@param[in]	sch		単語分離キャラクタ
			@return 同じ場合「true」
        */
        //-----------------------------------------------------------------//
		bool cmp_word(uint32_t argc, const char* key, char sch = ' ') const {
			return str::cmp_word(buff_, argc, key, sch);
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  整数を取得
			@param[in]	argc	ワード位置
			@param[out]	out		整数
			@param[in]	fix		２進、８進、１６進などで入力可能にする場合「false」
			@return 取得できたら「true」を返す
        */
        //-----------------------------------------------------------------//
		bool get_integer(uint8_t argc, int32_t& out, bool fix = true) const
		{
			char tmp[32];
			if(!get_word(argc, tmp, sizeof(tmp))) return false;

			char form[3];
			form[0] = '%';
			form[1] = fix ? 'a' : 'd';
			form[2] = 0;
			return (utils::input(form, tmp) % out).status();
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  小数を取得
			@param[in]	argc	ワード位置
			@param[out]	out		小数
			@return 取得できたら「true」を返す
        */
        //-----------------------------------------------------------------//
		bool get_float(uint8_t argc, float& out) const
		{
			char tmp[32];
			if(!get_word(argc, tmp, sizeof(tmp))) return false;

			return (utils::input("%f", tmp) % out).status();
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
