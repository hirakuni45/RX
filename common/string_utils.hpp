#pragma once
//=====================================================================//
/*!	@file
	@brief	文字列操作ユーティリティー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstring>
#include "ff12b/src/ff.h"
#include "common/time.h"
#include "common/format.hpp"

/// string, vector が使える環境
// #define STRING_VECTOR
#ifdef STRING_VECTOR
#include <string>
#include <vector>
#endif

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  文字列操作クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct str {

		//-----------------------------------------------------------------//
		/*!
			@brief  １６進数ダンプ
			@param[in]	src	ソース
			@param[in]	num	数
			@param[in]	lin	１行辺りの表示数
		*/
		//-----------------------------------------------------------------//
		static void hex_dump(char* src, uint16_t num, uint8_t lin)
		{
			uint8_t l = 0;
			for(uint16_t i = 0; i < num; ++i) {
				auto n = *src++;
				utils::format("%02X") % static_cast<uint16_t>(n);
				++l;
				if(l == lin) {
					utils::format("\n");
					l = 0;
				} else {
					utils::format(" ");
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  UTF-8 から UTF-16 への変換
			@param[in]	src	ソース
			@param[in]	dst	変換先
		*/
		//-----------------------------------------------------------------//
		static void utf8_to_utf16(const char* src, WCHAR* dst)
		{
			uint8_t cnt = 0;
			uint16_t code = 0;
			char tc;
			while((tc = *src++) != 0) {
				uint8_t c = static_cast<uint8_t>(tc);
				if(c < 0x80) { code = c; cnt = 0; }
				else if((c & 0xf0) == 0xe0) { code = (c & 0x0f); cnt = 2; }
				else if((c & 0xe0) == 0xc0) { code = (c & 0x1f); cnt = 1; }
				else if((c & 0xc0) == 0x80) {
					code <<= 6;
					code |= c & 0x3f;
					cnt--;
					if(cnt == 0 && code < 0x80) {
						code = 0;	// 不正なコードとして無視
						break;
					} else if(cnt < 0) {
						code = 0;
					}
				}
				if(cnt == 0 && code != 0) {
					*dst++ = code;
					code = 0;
				}
			}
			*dst = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  UTF-16 から UTF-8 への変換
			@param[in]	code	UTF-16 コード
			@param[in]	dst	変換先
			@return 変換先の最終ポインター
		*/
		//-----------------------------------------------------------------//
		static char* utf16_to_utf8(uint16_t code, char* dst)
		{
			if(code < 0x0080) {
				*dst++ = code;
			} else if(code >= 0x0080 && code <= 0x07ff) {
				*dst++ = 0xc0 | ((code >> 6) & 0x1f);
				*dst++ = 0x80 | (code & 0x3f);
			} else if(code >= 0x0800) {
				*dst++ = 0xe0 | ((code >> 12) & 0x0f);
				*dst++ = 0x80 | ((code >> 6) & 0x3f);
				*dst++ = 0x80 | (code & 0x3f);
			}
			return dst;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  UTF-16 から UTF-8 への変換
			@param[in]	src	ソース
			@param[in]	dst	変換先
		*/
		//-----------------------------------------------------------------//
		static void utf16_to_utf8(const WCHAR* src, char* dst) 
		{
			uint16_t code;
			while((code = static_cast<uint16_t>(*src++)) != 0) {
				dst = utf16_to_utf8(code, dst);
			}
			*dst = 0;
		}

#if _USE_LFN != 0
		//-----------------------------------------------------------------//
		/*!
			@brief  sjis から UTF-8 への変換
			@param[in]	src	ソース
			@param[in]	dst	変換先
		*/
		//-----------------------------------------------------------------//
		static void sjis_to_utf8(const char* src, char* dst)
		{
			if(src == nullptr) return;
			uint16_t wc = 0;
			char ch;
			while((ch = *src++) != 0) {
				uint8_t c = static_cast<uint8_t>(ch);
				if(wc) {
					if(0x40 <= c && c <= 0x7e) {
						wc <<= 8;
						wc |= c;
						dst = utf16_to_utf8(ff_convert(wc, 1), dst);
					} else if(0x80 <= c && c <= 0xfc) {
						wc <<= 8;
						wc |= c;
						dst = utf16_to_utf8(ff_convert(wc, 1), dst);
					}
					wc = 0;
				} else {
					if(0x81 <= c && c <= 0x9f) wc = c;
					else if(0xe0 <= c && c <= 0xfc) wc = c;
					else {
						dst = utf16_to_utf8(ff_convert(c, 1), dst);
					}
				}
			}
			*dst = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  UTF-8 から sjis への変換
			@param[in]	src	ソース
			@param[in]	dst	変換先
		*/
		//-----------------------------------------------------------------//
		static void utf8_to_sjis(const char* src, char* dst)
		{
			int8_t cnt = 0;
			uint16_t code = 0;
			char tc;
			while((tc = *src++) != 0) {
				uint8_t c = static_cast<uint8_t>(tc);
				if(c < 0x80) { *dst++ = tc; code = 0; }
				else if((c & 0xf0) == 0xe0) { code = (c & 0x0f); cnt = 2; }
				else if((c & 0xe0) == 0xc0) { code = (c & 0x1f); cnt = 1; }
				else if((c & 0xc0) == 0x80) {
					code <<= 6;
					code |= c & 0x3f;
					cnt--;
					if(cnt == 0 && code < 0x80) {
						code = 0;	// 不正なコードとして無視
						break;
					} else if(cnt < 0) {
						code = 0;
					}
				}
				if(cnt == 0 && code != 0) {
					auto wc = ff_convert(code, 0);
					*dst++ = static_cast<char>(wc >> 8);
					*dst++ = static_cast<char>(wc & 0xff);
					code = 0;
				}			
			}
			*dst = 0;
		}
#endif

		//-----------------------------------------------------------------//
		/*!
			@brief	FatFS が使う時間取得関数
			@param[in]	t	グリニッチ標準時間
			@return	FatFS 形式の時刻ビットフィールドを返す。@n
			        現在のローカル・タイムがDWORD値にパックされて返されます。@n
					ビット・フィールドは次に示すようになります。@n
					bit31:25 ---> 1980年を起点とした年が 0..127 で入ります。@n
					bit24:21 ---> 月が 1..12 の値で入ります。@n
					bit20:16 ---> 日が 1..31 の値で入ります。@n
					bit15:11 ---> 時が 0..23 の値で入ります。@n
					bit10:5 ---> 分が 0..59 の値で入ります。@n
					bit4:0 ---> 秒/2が 0..29 の値で入ります。
		*/
		//-----------------------------------------------------------------//
		static DWORD get_fattime(time_t t)
		{
			time_t ttt = t - (9 * 60 * 60);  // 何故かズレ
			struct tm *tp = gmtime(&ttt);

#ifdef DEBUG_
			format("get_fattime: (source) %4d/%d/%d/ %02d:%02d:%02d\n")
				% (tp->tm_year + 1900) % (tp->tm_mon + 1) % tp->tm_mday
				% tp->tm_hour % tp->tm_min % tp->tm_sec;
#endif

			DWORD tt = 0;
			tt |= static_cast<DWORD>((tp->tm_sec % 60) >> 1);
			tt |= static_cast<DWORD>(tp->tm_min % 60) << 5;
			tt |= static_cast<DWORD>(tp->tm_hour % 24) << 11;

			tt |= static_cast<DWORD>(tp->tm_mday & 31) << 16;
			tt |= static_cast<DWORD>(tp->tm_mon + 1) << 21;
			if(tp->tm_year >= 80) {
				tt |= (static_cast<DWORD>(tp->tm_year) - 80) << 25;
			}

			return tt;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	FatFS が扱う時間値から、time_t への変換
			@param[in]	date	日付
			@param[in]	time	時間
			@return GMT 標準時間値
		*/
		//-----------------------------------------------------------------//
		static time_t fatfs_time_to(WORD date, WORD time)
		{
			struct tm ttm;
			// ftime
			// ファイルの変更された時刻、またはディレクトリの作成された時刻が格納されます。
			// bit15:11 ---> 時が 0..23 の値で入ります。
			// bit10:5  ---> 分が 0..59 の値で入ります。
			// bit4:0   ---> 秒/2が 0..29 の値で入ります。
			ttm.tm_sec  =  time & 0x1f;
			ttm.tm_min  = (time >> 5) & 0x3f;
			ttm.tm_hour = (time >> 11) & 0x1f;

			// fdate
			// ファイルの変更された日付、またはディレクトリの作成された日付が格納されます。
			// bit15:9 ---> 1980年を起点とした年が 0..127 で入ります。
			// bit8:5  ---> 月が 1..12 の値で入ります。
			// bit4:0  ---> 日が 1..31 の値で入ります。
			ttm.tm_mday =  date & 0x1f;
			ttm.tm_mon  = ((date >> 5) & 0xf) - 1;
			ttm.tm_year = ((date >> 9) & 0x7f) + 1980 - 1900;

			return mktime_gmt(&ttm);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  URL エンコード文字列を通常文字列へ変換
			@param[in]	src	ソース
			@param[out]	dst	出力
			@param[in]	len	出力長（０の場合サイズ検査無し）
			@return 出力数
		*/
		//-----------------------------------------------------------------//
		static uint32_t url_encode_to_str(const char* src, char* dst, uint32_t len = 0)
		{
			char ch;
			uint8_t hex = 0;
			uint8_t hv = 0;
			uint32_t l = 0;
			while((ch = *src++) != 0) {
				if(hex > 0) {
					hv <<= 4;
					if(ch >= '0' && ch <= '9') hv |= ch - '0';
					else if(ch >= 'A' && ch <= 'F') hv |= ch - 'A' + 10;
					else if(ch >= 'a' && ch <= 'f') hv |= ch - 'a' + 10;
					--hex;
					if(hex == 0) ch = hv;
					else continue;
				}
				if(ch == '%') {
					hex = 2;
				} else {
					if(ch == '+') ch = ' ';
					if(len > 0 && l >= (len - 1)) break;
					*dst = ch;
					++dst;
					++l;
				}
			}
			*dst = 0;
			return l + 1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  通常文字列を URL デコード文字列へ変換
			@param[in]	src	ソース
			@param[out]	dst	出力
			@param[in]	len	出力長（０の場合サイズ検査無し）
			@return 出力数
		*/
		//-----------------------------------------------------------------//
		static uint32_t url_decode_to_str(const char* src, char* dst, uint32_t len = 0)
		{
			char ch;
			uint32_t l = 0;
			while((ch = *src++) != 0) {
				if(ch == ' ') ch = '+';
				else if(ch >= '0' && ch <= '9') ;
				else if(ch >= 'A' && ch <= 'Z') ;
				else if(ch >= 'a' && ch <= 'z') ;
				else {
					if(len > 0 && l >= (len - 1)) break;
					*dst++ = '%';
					++l;
					uint8_t v = static_cast<uint8_t>(ch) >> 4;
					if(len > 0 && l >= (len - 1)) break;
					*dst++ = v < 10 ? (v + '0') : (v + 'A' - 10);
					++l;
					v = static_cast<uint8_t>(ch) & 0xf;
					ch = v < 10 ? (v + '0') : (v + 'A' - 10);
				}

				if(len > 0 && l >= (len - 1)) break;
				*dst++ = ch;
				++l;
			}
			*dst = 0;
			return l + 1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  パスワード隠し文字へ変換
			@param[in]	cha	隠しキャラクター
			@param[in]	src	ソース
			@param[out]	dst	出力
			@param[in]	len	出力長（０の場合サイズ検査無し）
			@return 出力数
		*/
		//-----------------------------------------------------------------//
		static uint32_t conv_pass_cha(char cha, const char* src, char* dst, uint32_t len = 0)
		{
			char ch;
			uint32_t l = 0;
			while((ch = *src++) != 0) {
				if(len > 0 && l >= (len - 1)) break;
				*dst++ = cha;
				++l;
			}
			*dst = 0;
			return l + 1;
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CGI POST のパース
		@param[in]	buff_size	バッファの最大サイズ
		@param[in]	unit_size	ユニットの最大サイズ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t buff_size, uint32_t unit_size>
	class parse_cgi_post {
	public:
		struct unit_t {
			const char* key;
			const char* val;
			unit_t() : key(nullptr), val(nullptr) { }
		};

	private:
		char				buff_[buff_size];
		unit_t				units_[unit_size];
		uint32_t			size_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		parse_cgi_post() : size_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	クリア
		*/
		//-----------------------------------------------------------------//
		void clear() {
			size_ = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	パース
			@param[in]	src	ソース
			@return パースに失敗（メモリー不足）したら「false」
		*/
		//-----------------------------------------------------------------//
		bool parse(const char* src)
		{
			uint32_t n = 0;
			uint32_t s = 0;
			char ch;
			char bch = 0;
			while((ch = *src) != 0) {
				if(bch == '=') {
					units_[s].val = &buff_[n];
				} else if(bch == 0) {
					units_[s].key = &buff_[n];
				}
				if(bch == '&') {
					if(s < (unit_size - 1)) {
						++s;
					} else {
						size_ = 0;
						return false;
					}
					units_[s].key = &buff_[n];
				}
				if(n < (buff_size - 1)) {
					if(ch == '=') { bch = ch; ch = 0; }
					else if(ch == '&') { bch = ch; ch = 0; }
					else bch = ch;
					buff_[n] = ch;
					++n;
				} else {
					size_ = 0;
					return false;
				}
				++src;
			}

			buff_[n] = 0;
			size_ = s + 1;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ユニット・サイズを取得
			@return ユニット・サイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t size() const { return size_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ユニットを取得
			@param[in]	idx	インデックス
			@return ユニット
		*/
		//-----------------------------------------------------------------//
		const unit_t& get_unit(uint32_t idx) const {
			static const unit_t null_unit;
			if(idx >= size_) return null_unit;
			return units_[idx];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	リスト
		*/
		//-----------------------------------------------------------------//
		void list() const {
			utils::format("Size: %d\n") % size_;
			for(uint32_t i = 0; i < size(); ++i) {
				utils::format("Key: '%s' - Value: '%s'\n") % units_[i].key % units_[i].val;
			}
		}		
	};



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  行管理クラス
		@param[in]	buff_size	バッファの最大サイズ
		@param[in]	line_size	行の最大サイズ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t buff_size, uint32_t line_size>
	class line_manage {

		char		spch_;
		char		back_;

		char		buff_[buff_size];
		uint32_t	buff_pos_;

		const char* line_[line_size];
		uint32_t	line_pos_;

		bool set_term_() {
			if(line_pos_ < line_size) {
				buff_[buff_pos_] = 0;
				++buff_pos_;
				++line_pos_;
				back_ = 0;
				return true;
			} else {
				return false;
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	spch	分離キャラクター
			@param[in]	noch	無視するキャラクター
		*/
		//-----------------------------------------------------------------//
		line_manage(char spch) : spch_(spch), back_(0),
			buff_pos_(0), line_pos_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	クリア
		*/
		//-----------------------------------------------------------------//
		void clear()
		{
			back_ = 0;
			buff_pos_ = 0;
			line_pos_ = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	行の収集サイズを返す
			@return 行の収集サイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t size() const { return line_pos_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	行の収集サイズが殻か？
			@return 行の収集サイズが殻なら「true」
		*/
		//-----------------------------------------------------------------//
		bool empty() const { return line_pos_ == 0; }


		//-----------------------------------------------------------------//
		/*!
			@brief	終端を設定
			@return 追加出来ない（割り当てオーバー）場合「false」
		*/
		//-----------------------------------------------------------------//
		bool set_term() {
			if(back_ == 0) {
				line_[line_pos_] = &buff_[buff_pos_];
			}
			return set_term_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	追加
			@param[in]	ch	キャラクター
			@return 追加出来ない（割り当てオーバー）場合「false」
		*/
		//-----------------------------------------------------------------//
		bool add(char ch)
		{
			if(back_ == 0 && ch != 0) {
				line_[line_pos_] = &buff_[buff_pos_];
			}

			if(back_ != spch_ && ch == spch_) {
				return set_term_();
			}

			if(buff_pos_ < (buff_size - 1)) {
				buff_[buff_pos_] = ch;
				++buff_pos_;
				back_ = ch;
				return true;
			} else {
				return false;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	[] オペレーター
			@return 行ポインター
		*/
		//-----------------------------------------------------------------//
		const char* operator[] (uint32_t idx) const {
			if(idx >= line_pos_) return nullptr;
			return line_[idx];
		}
	};


#ifdef STRING_VECTOR
	//-----------------------------------------------------------------//
	/*!
		@brief	キャラクター・リスト中のコードで分割する
		@param[in]	src		入力文字列
		@param[in]	list	分割するキャラクター列
		@param[in]	inhc	分割を無効にするキャラクター列
		@param[in]	limit	分割する最大数を設定する場合正の値
		@return	文字列リスト
	*/
	//-----------------------------------------------------------------//
	template <class SS>
	SS split_textT(const typename SS::value_type& src,
				   const typename SS::value_type& list,
				   const typename SS::value_type& inhc,
				   int limit = 0) noexcept
	{
		SS dst;
		bool tab_back = true;
		typename SS::value_type word;
		typename SS::value_type::value_type ihc = 0;
		for(auto ch : src) {
			bool tab = false;
			if(limit <= 0 || static_cast<int>(dst.size()) < (limit - 1)) {
				if(ihc == 0 && list.find(ch) != std::string::npos) {
					tab = true;
				}
			}
			if(tab_back && !tab && !word.empty()) {
				dst.push_back(word);
				word.clear();
				ihc = 0;
			}
			if(!tab) {
				if(!inhc.empty()) {
					if(word.empty() && inhc.find(ch) != std::string::npos) {
						ihc = ch;
					} else if(ch == ihc) {
						ihc = 0;
					}
				}
				word += ch;
			}
			tab_back = tab;
		}
		if(!word.empty()) {
			dst.push_back(word);
		}
		return dst;
	}

	typedef std::vector<std::string> strings;

	inline strings split_text(const std::string& src, const std::string& list, const std::string& inhc = "",
		int limit = 0) noexcept {
		return split_textT<strings>(src, list, inhc, limit);
	}
#endif
}
