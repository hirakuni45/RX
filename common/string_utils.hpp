#pragma once
//=====================================================================//
/*!	@file
	@brief	文字列操作ユーティリティー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstring>
#ifdef FAT_FS
#include "ff13c/source/ff.h"
#endif
#include "common/time.h"
#include "common/format.hpp"
#include "common/input.hpp"

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
		static void hex_dump(char* src, uint16_t num, uint8_t lin) noexcept
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
			@brief  半角相当文字数を数える @n
					※半角： +1、全角： +2
			@param[in]	src	ソース
			@return 半角相当文字数
		*/
		//-----------------------------------------------------------------//
		static uint32_t utf8_string_length(const char* src) noexcept
		{
			uint32_t len = 0;
			if(src == nullptr) return len;

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
					if(code < 256) len += 1;
					else len += 2;
					code = 0;
				}
			}
			return len;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  UTF-8 から UTF-16 への変換
			@param[in]	src	ソース
			@param[in]	dst	変換先
			@param[in]	dsz	変換先のサイズ（バイトサイズ）
			@return 正常終了なら「true」
		*/
		//-----------------------------------------------------------------//
		static bool utf8_to_utf16(const char* src, uint16_t* dst, uint32_t dsz) noexcept
		{
			uint32_t len = dsz / 2;
			if(len <= 1) return false;
 
			uint8_t cnt = 0;
			uint16_t code = 0;
			char tc;
			while((tc = *src++) != 0 && len > 1) {
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
					--len;
					code = 0;
				}
			}
			*dst = 0;
			return len >= 1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  UTF-16 から UTF-8 への変換
			@param[in]	code	UTF-16 コード
			@param[in]	dst	変換先
			@param[in]	dsz	変換先のサイズ（バイトサイズ）
			@return 格納サイズ（０の場合エラー）
		*/
		//-----------------------------------------------------------------//
		static uint32_t utf16_to_utf8(uint16_t code, char* dst, uint32_t dsz) noexcept
		{
			uint32_t len = 0;
			if(code < 0x0080) {
				if(dsz >= 1) {
					*dst++ = code;
					len = 1;
				}
			} else if(code >= 0x0080 && code <= 0x07ff) {
				if(dsz >= 2) {
					*dst++ = 0xc0 | ((code >> 6) & 0x1f);
					*dst++ = 0x80 | (code & 0x3f);
					len = 2;
				}
			} else if(code >= 0x0800) {
				if(dsz >= 3) {
					*dst++ = 0xe0 | ((code >> 12) & 0x0f);
					*dst++ = 0x80 | ((code >> 6) & 0x3f);
					*dst++ = 0x80 | (code & 0x3f);
					len = 3;
				}
			}
			return len;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  UTF-16 から UTF-8 への変換
			@param[in]	src	ソース
			@param[in]	dst	変換先
			@param[in]	dsz	変換先のサイズ（バイトサイズ）
			@return 正常終了なら「true」
		*/
		//-----------------------------------------------------------------//
		static bool utf16_to_utf8(const uint16_t* src, char* dst, uint32_t dsz) noexcept
		{
			if(dsz <= 1) return false;

			uint16_t code;
			while((code = *src++) != 0) {
				auto len = utf16_to_utf8(code, dst, dsz);
				if(dsz > len) {
					dsz -= len;
					dst += len;
				} else {
					break;
				}
			}
			*dst = 0;
			return dsz >= 1;
		}

#if FF_USE_LFN != 0
		//-----------------------------------------------------------------//
		/*!
			@brief  OEM code から UTF-8 への変換
			@param[in]	src	ソース
			@param[in]	dst	変換先
			@param[in]	dsz	変換先のサイズ
			@return 正常終了なら「true」
		*/
		//-----------------------------------------------------------------//
		static bool oemc_to_utf8(const char* src, char* dst, uint32_t dsz) noexcept
		{
			if(src == nullptr) return false;

			uint16_t wc = 0;
			char ch;
			while((ch = *src++) != 0 && dsz > 1) {
				uint8_t c = static_cast<uint8_t>(ch);
				if(wc) {
					if(0x40 <= c && c <= 0x7e) {
						wc <<= 8;
						wc |= c;
						uint16_t tmp = ff_oem2uni(wc, FF_CODE_PAGE);
						auto len = utf16_to_utf8(tmp, dst, dsz);
						if(len == 0) break;
						dst += len;
						dsz -= len;
					} else if(0x80 <= c && c <= 0xfc) {
						wc <<= 8;
						wc |= c;
						uint16_t tmp = ff_oem2uni(wc, FF_CODE_PAGE);
						auto len = utf16_to_utf8(tmp, dst, dsz);
						if(len == 0) break;
						dst += len;
						dsz -= len;
					}
					wc = 0;
				} else {
					if(0x81 <= c && c <= 0x9f) wc = c;
					else if(0xe0 <= c && c <= 0xfc) wc = c;
					else {
						*dst++ = c;
						dsz -= 1;
					}
				}
			}
			*dst = 0;
			return dsz > 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  UTF-8 から OEM code への変換
			@param[in]	src	ソース
			@param[out]	dst	変換先
			@param[in]	dsz	変換先のサイズ
			@return 正常終了なら「true」
		*/
		//-----------------------------------------------------------------//
		static bool utf8_to_oemc(const char* src, char* dst, uint32_t dsz) noexcept
		{
			int8_t cnt = 0;
			uint16_t code = 0;
			char tc;
			while((tc = *src++) != 0) {
				uint8_t c = static_cast<uint8_t>(tc);
				if(c < 0x80) {
					if(dsz <= 1) break;
					*dst++ = tc;
					code = 0;
					--dsz;
				} else if((c & 0xf0) == 0xe0) {
					code = (c & 0x0f);
					cnt = 2;
				} else if((c & 0xe0) == 0xc0) {
					code = (c & 0x1f);
					cnt = 1;
				} else if((c & 0xc0) == 0x80) {
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
					if(dsz <= 3) break;
					auto wc = ff_uni2oem(code, FF_CODE_PAGE);
					*dst++ = static_cast<char>(wc >> 8);
					*dst++ = static_cast<char>(wc & 0xff);
					dsz -= 2;
					code = 0;
				}			
			}
			*dst = 0;
			return dsz > 0;
		}
#endif

#ifdef FAT_FS
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
		static DWORD get_fattime(time_t t) noexcept
		{
			struct tm *tp = localtime(&t);

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
		static time_t fatfs_time_to(WORD date, WORD time) noexcept
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

			return mktime(&ttm);
		}
#endif

		//-----------------------------------------------------------------//
		/*!
			@brief	標準的なフォーマットで日付、時間、年表示
			@param[in]	gt	GMT 時間
			@return GMT 標準時間値
		*/
		//-----------------------------------------------------------------//
		static void print_date_time(time_t gt) noexcept
		{
                struct tm *m = localtime(&gt);
                utils::format("%s %s %d %02d:%02d:%02d  %4d\n")
                    % get_wday(m->tm_wday)
                    % get_mon(m->tm_mon)
                    % static_cast<uint32_t>(m->tm_mday)
                    % static_cast<uint32_t>(m->tm_hour)
                    % static_cast<uint32_t>(m->tm_min)
                    % static_cast<uint32_t>(m->tm_sec)
                    % static_cast<uint32_t>(m->tm_year + 1900);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  時間の作成
			@param[in]	date	日付 xx/xx/xx 形式
			@param[in]	time	時間 xx:xx[:xx] 形式
			@return GMT 時間
		*/
		//-----------------------------------------------------------------//
		static time_t make_time(const char* date, const char* time) noexcept
		{
			time_t t;
			struct tm *m = localtime(&t);
			m->tm_year = 2019 - 1900;
			m->tm_mon  = 10 - 1;  // Oct
			m->tm_mday = 1;       // day of 1
			int vs[3];
			if(date == nullptr) {
			} else if((utils::input("%d/%d/%d", date) % vs[0] % vs[1] % vs[2]).status()) {
				if(vs[0] >= 1900 && vs[0] < 2100) m->tm_year = vs[0] - 1900;
				if(vs[1] >= 1 && vs[1] <= 12) m->tm_mon = vs[1] - 1;
				if(vs[2] >= 1 && vs[2] <= 31) m->tm_mday = vs[2];
			}

			m->tm_hour = 0;
			m->tm_min  = 0;
			m->tm_sec  = 0;
			if(time == nullptr) {
			} else if((utils::input("%d:%d:%d", time) % vs[0] % vs[1] % vs[2]).status()) {
				if(vs[0] >= 0 && vs[0] < 24) m->tm_hour = vs[0];
				if(vs[1] >= 0 && vs[1] < 60) m->tm_min = vs[1];
				if(vs[2] >= 0 && vs[2] < 60) m->tm_sec = vs[2];
			} else if((utils::input("%d:%d", time) % vs[0] % vs[1]).status()) {
				if(vs[0] >= 0 && vs[0] < 24) m->tm_hour = vs[0];
				if(vs[1] >= 0 && vs[1] < 60) m->tm_min = vs[1];
				m->tm_sec = 0;
			}
			return mktime(m);
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  文字列中の「単語」数を取得 @n
					※バックスラッシュによる除外を行う
			@param[in]	src		ソース
			@param[in]	sch		単語分離キャラクタ
			@return ワード数を返す
        */
        //-----------------------------------------------------------------//
		static uint32_t get_words(const char* src, char sch = ' ') noexcept
		{
			if(src == nullptr) return 0;

			uint32_t n = 0;
			char bc = sch;
			bool bsc = false;
			while(1) {
				char ch = *src++;
				if(ch == '\\') {
					bsc = true;
					continue;
				} else if(bsc) {
					bsc = false;
				} else {
					if(ch == 0) break;
					if(bc == sch && ch != sch) { 
						++n;
					}
					bc = ch;
				}
			}
			return n;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  ワードを取得 @n
					※バックスラッシュによる除外を行う
			@param[in]	src	ソース
			@param[in]	argc	ワード位置
			@param[out]	dst		ワード文字列格納ポインター
			@param[in]	size	ワード文字列サイズ
			@param[in]	sch		分離キャラクタ
			@return 取得できたら「true」を返す
        */
        //-----------------------------------------------------------------//
		static bool get_word(const char* src, uint32_t argc, char* dst, uint32_t dstlen,
			char sch = ' ') noexcept 
		{
			if(src == nullptr || dst == nullptr || dstlen == 0) return false;

			uint32_t n = 0;
			char bc = sch;
			bool bsc = false;
			bool out = false;
			while(1) {
				char ch = *src++;
				if(ch == '\\') {
					bsc = true;
					continue;
				} else if(bsc) {
					bsc = false;
				} else {
					if(bc == sch && ch != sch) {
						if(n == argc) {
							out = true;
						}
						++n;
					} else if(bc != sch && ch == sch) {
						if(out) {
							break;
						}
					}
					if(ch == 0) break;
					bc = ch;
				}
				if(out && dstlen > 1) {
					*dst++ = ch;
					dstlen--;
				}
			}
			*dst = 0;
			return out;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  ワードを比較
			@param[in]	src	ソース
			@param[in]	argc	ワード位置
			@param[in]	key		比較文字列
			@param[in]	sch		分離キャラクタ
			@return マッチした場合「true」
        */
        //-----------------------------------------------------------------//
		static bool cmp_word(const char* src, uint32_t argc, const char* key, char sch = ' ') noexcept
		{
			if(src == nullptr || key == nullptr) return false;

			uint32_t n = 0;
			char bc = sch;
			bool bsc = false;
			bool out = false;
			while(1) {
				char ch = *src++;
				if(ch == '\\') {
					bsc = true;
					continue;
				} else if(bsc) {
					bsc = false;
				} else {
					if(bc == sch && ch != sch) {
						if(n == argc) {
							out = true;
						}
						++n;
					} else if(bc != sch && ch == sch) {
						if(out) {
							break;
						}
					}
					if(ch == 0) break;
					bc = ch;
				}
				if(out) {
					if(ch != *key) return false;
					++key; 
				}
			}
			if(*key == 0) return true;
			else return false;
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
		static uint32_t url_encode_to_str(const char* src, char* dst, uint32_t len = 0) noexcept
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
		static uint32_t url_decode_to_str(const char* src, char* dst, uint32_t len = 0) noexcept
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
		static uint32_t conv_pass_cha(char cha, const char* src, char* dst, uint32_t len = 0) noexcept
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


		//-----------------------------------------------------------------//
		/*!
			@brief  大文字、小文字を区別しない文字列の比較 @n
					※安全性を確保する貯め、NULL チェックを入れてある。 @n
					※最新のコンパイラでは、NULL チェックが二重になっても最適化で無くなる。
			@param[in]	src		文字列
			@param[in]	cmp		比較文字列
			@param[in]	len		比較文字数を指定する場合（０の場合必ず成功「０」する）
			@return 「strcmp」と同等の結果
		*/
		//-----------------------------------------------------------------//
		static int strcmp_no_caps(const char* src, const char* cmp, int len = -1) noexcept
		{
			if(src == nullptr || cmp == nullptr) return -1;

			char c1 = 0;
			char c2 = 0;
			if(len < 0) {
				do {
					c1 = *src++;
					if(c1 >= 'a' && c1 <= 'z') c1 -= 0x20; 
					c2 = *cmp++;
					if(c2 >= 'a' && c2 <= 'z') c2 -= 0x20; 
					if(c1 == '\0') {
						break;
					}
				} while(c1 == c2) ;
			} else {
				while(len > 0) {
					c1 = *src++;
					if(c1 >= 'a' && c1 <= 'z') c1 -= 0x20; 
					c2 = *cmp++;
					if(c2 >= 'a' && c2 <= 'z') c2 -= 0x20; 
					if(c1 == '\0' || c1 != c2) {
						break;
					}
					--len;
				}
			}
			return static_cast<uint8_t>(c1) - static_cast<uint8_t>(c2);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  小文字を大文字に変換
			@param[in]	src		元
			@param[out]	dst		先
			@param[in]	len		先の大きさ	
		*/
		//-----------------------------------------------------------------//
		static void to_caps(const char* src, char* dst, uint32_t len) {
			char ch;
			while((ch = *src++) != 0) {
				if(len <= 1) break;
				if(ch >= 'a' && ch <= 'z') ch -= 0x20;
				*dst++ = ch;
				--len;
			}
			if(len > 0) *dst = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  大文字を小文字に変換
			@param[in]	src		元
			@param[out]	dst		先
			@param[in]	len		先の大きさ	
		*/
		//-----------------------------------------------------------------//
		static void no_caps(const char* src, char* dst, uint32_t len) {
			char ch;
			while((ch = *src++) != 0) {
				if(len <= 1) break;
				if(ch >= 'A' && ch <= 'Z') ch += 0x20;
				*dst++ = ch;
				--len;
			}
			if(len > 0) *dst = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  拡張子を識別
			@param[in]	filename	ファイル名（フルパス）
			@param[in]	exts		拡張子テーブル（「,」で区切られた文字列）
			@return 有効な拡張子なら「true」
		*/
		//-----------------------------------------------------------------//
		static bool scan_ext(const char* filename, const char* exts) noexcept
		{
			if(filename == nullptr || exts == nullptr) return false;

			auto src = strrchr(filename, '.');
			if(src == nullptr) return false;
			++src;

			auto ext = strchr(exts, ',');
			if(ext == nullptr) {
				return strcmp_no_caps(src, exts) == 0;
			} else {
				auto org = exts;
				while(ext != nullptr) {
					if(strcmp_no_caps(src, org, ext - org) == 0) return true;
					++ext;
					org = ext;
					ext = strchr(org, ',');
				}
				return strcmp_no_caps(src, org) == 0;
			}
			return false;
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
		char		buff_[buff_size];
		unit_t		units_[unit_size];
		uint32_t	size_;

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
				buff_[buff_size - 1] = 0;
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
