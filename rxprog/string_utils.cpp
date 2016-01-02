//=====================================================================//
/*!	@file
	@brief	文字列操作ユーティリティー
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "string_utils.hpp"
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include "sjis_utf16.hpp"

#include <iostream>

namespace utils {

	using namespace std;

	bool string_to_hex(const std::string& src, uint32_t& dst)
	{
		uint32_t v = 0;
		for(auto ch : src) {
			v <<= 4;
			if(ch >= '0' && ch <= '9') v |= ch - '0';
			else if(ch >= 'A' && ch <= 'F') v |= ch - 'A' + 10;
			else if(ch >= 'a' && ch <= 'f') v |= ch - 'a' + 10;
			else return false;
		}
		dst = v;
		return true;
	}


	bool string_to_hex(const std::string& src, std::vector<uint32_t>& dst, const std::string& spc)
	{
		string s;
		for(auto ch : src) {
			if(string_strchr(spc, ch) != nullptr) {
				uint32_t v;
				if(string_to_hex(s, v)) {
					dst.push_back(v);
					s.clear();
				} else {
					return false;
				}
			} else {
				s += ch;
			}
		}
		if(!s.empty()) {
			uint32_t v;
			if(string_to_hex(s, v)) {
				dst.push_back(v);
			} else {
				return false;
			}
		}
		return true;
	}


	bool string_to_int(const std::string& src, int32_t& dst)
	{
		try {
			dst = boost::lexical_cast<int32_t>(src);
		} catch(boost::bad_lexical_cast& bad) {
			return false;
		}
		return true;
	}


	bool string_to_int(const std::string& src, std::vector<int32_t>& dst, const std::string& spc)
	{
		try {
			string s;
			for(auto ch : src) {
				if(string_strchr(spc, ch) != nullptr) {
					int32_t v = boost::lexical_cast<int32_t>(s);
					dst.push_back(v);
					s.clear();
				} else {
					s += ch;
				}
			}
			if(!s.empty()) {
				int32_t v = boost::lexical_cast<int32_t>(s);
				dst.push_back(v);
			}
		} catch(boost::bad_lexical_cast& bad) {
			return false;
		}
		return true;
	}


	bool string_to_float(const std::string& src, float& dst)
	{
		try {
			dst = boost::lexical_cast<float>(src);
		} catch(boost::bad_lexical_cast& bad) {
			return false;
		}
		return true;
	}


	bool string_to_float(const std::string& src, std::vector<float>& dst, const std::string& spc)
	{
		try {
			string s;
			for(auto ch : src) {
				if(string_strchr(spc, ch) != nullptr) {
					float v = boost::lexical_cast<float>(s);
					dst.push_back(v);
					s.clear();
				} else {
					s += ch;
				}
			}
			if(!s.empty()) {
				float v = boost::lexical_cast<float>(s);
				dst.push_back(v);
			}
		} catch(boost::bad_lexical_cast& bad) {
			return false;
		}
		return true;
	}

#if 0
	bool string_to_matrix4x4(const std::string& src, mtx::fmat4& dst)
	{
		std::vector<float> vv;
		if(!string_to_float(src, vv)) {
			return false;
		}
		if(vv.size() == 16) {
			for(int i = 0; i < 16; ++i) {
				int j = ((i & 3) << 2) | ((i >> 2) & 3);
				dst[j] = vv[i];
			}
			return true;
		} else {
			return false;
		}
	}
#endif

	//-----------------------------------------------------------------//
	/*!
		@brief	UTF-8 から UTF-16 への変換
		@param[in]	src	UTF-8 ソース
		@param[out]	dst	UTF-16（追記）
		@return 変換エラーが無ければ「true」
	*/
	//-----------------------------------------------------------------//
	bool utf8_to_utf16(const std::string& src, wstring& dst) noexcept
	{
		if(src.empty()) return true;

		bool f = true;
		int cnt = 0;
		uint16_t code = 0;
		for(auto tc : src) {
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
					f = false;
				} else if(cnt < 0) {
					code = 0;
				}
			}
			if(cnt == 0 && code != 0) {
				dst += code;
				code = 0;
			}
		}
		return f;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	UTF-8 から UTF-32 への変換
		@param[in]	src	UTF-8 ソース
		@param[out]	dst	UTF-32（追記）
		@return 変換が正常なら「true」
	*/
	//-----------------------------------------------------------------//
	bool utf8_to_utf32(const std::string& src, lstring& dst) noexcept
	{
		if(src.empty()) return false;

		bool f = true;
		int cnt = 0;
		uint32_t code = 0;
		for(auto tc : src) {
			uint8_t c = static_cast<uint8_t>(tc);
			if(c < 0x80) { code = c; cnt = 0; }
			else if((c & 0xfe) == 0xfc) { code = (c & 0x03); cnt = 5; }
			else if((c & 0xfc) == 0xf8) { code = (c & 0x07); cnt = 4; }
			else if((c & 0xf8) == 0xf0) { code = (c & 0x0e); cnt = 3; }
			else if((c & 0xf0) == 0xe0) { code = (c & 0x0f); cnt = 2; }
			else if((c & 0xe0) == 0xc0) { code = (c & 0x1f); cnt = 1; }
			else if((c & 0xc0) == 0x80) {
				code <<= 6;
				code |= c & 0x3f;
				cnt--;
				if(cnt == 0 && code < 0x80) {
					code = 0;	// 不正なコードとして無視
					f = false;
				} else if(cnt < 0) {
					code = 0;
				}
			}
			if(cnt == 0 && code != 0) {
				dst += code;
				code = 0;
			}
		}
		return f;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	UTF-16 から UTF-8 への変換
		@param[in]	src	UTF-16 ソース
		@param[out]	dst	UTF-8（追記）
		@return 変換が正常なら「true」
	*/
	//-----------------------------------------------------------------//
	bool utf16_to_utf8(const wstring& src, std::string& dst) noexcept
	{
		if(src.empty()) return false;

		bool f = true;
		for(auto code : src) {
			if(code < 0x0080) {
				dst += code;
			} else if(code >= 0x0080 && code <= 0x07ff) {
				dst += 0xc0 | ((code >> 6) & 0x1f);
				dst += 0x80 | (code & 0x3f);
			} else if(code >= 0x0800) {
				dst += 0xe0 | ((code >> 12) & 0x0f);
				dst += 0x80 | ((code >> 6) & 0x3f);
				dst += 0x80 | (code & 0x3f);
			} else {
				f = false;
			}
		}
		return f;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	UTF-32 から UTF-8 への変換
		@param[in]	src	UTF-32 ソース
		@param[out]	dst	UTF-8（追記）
		@return 変換が正常なら「true」
	*/
	//-----------------------------------------------------------------//
	bool utf32_to_utf8(const lstring& src, std::string& dst) noexcept
	{
		if(src.empty()) return false;

		bool f = true;
		for(auto code : src) {
			if(code < 0x0080) {
				dst += code;
			} else if(code >= 0x0080 && code <= 0x07ff) {
				dst += 0xc0 | ((code >> 6) & 0x1f);
				dst += 0x80 | (code & 0x3f);
			} else if(code >= 0x0800 && code <= 0xffff) {
				dst += 0xe0 | ((code >> 12) & 0x0f);
				dst += 0x80 | ((code >> 6) & 0x3f);
				dst += 0x80 | (code & 0x3f);
			} else if(code >= 0x00010000 && code <= 0x001fffff) {
				dst += 0xf0 | ((code >> 18) & 0x07); 
				dst += 0x80 | ((code >> 12) & 0x3f);
				dst += 0x80 | ((code >> 6) & 0x3f);
				dst += 0x80 | (code & 0x3f);
			} else if(code >= 0x00200000 && code <= 0x03ffffff) {
				dst += 0xF8 | ((code >> 24) & 0x03);
				dst += 0x80 | ((code >> 18) & 0x3f);
				dst += 0x80 | ((code >> 12) & 0x3f);
				dst += 0x80 | ((code >> 6) & 0x3f);
				dst += 0x80 | (code & 0x3f);
			} else if(code >= 0x04000000 && code <= 0x7fffffff) {
				dst += 0xfc | ((code >> 30) & 0x01);
				dst += 0x80 | ((code >> 24) & 0x3f);
				dst += 0x80 | ((code >> 18) & 0x3f);
				dst += 0x80 | ((code >> 12) & 0x3f);
				dst += 0x80 | ((code >> 6) & 0x3f);
				dst += 0x80 | (code & 0x3f);
			} else {
				f = false;
			}
		}
		return f;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	Shift-JIS から UTF-8(ucs2) への変換
		@param[in]	src	Shift-JIS ソース
		@param[out]	dst	UTF-8（追記）
		@return 変換が正常なら「true」
	*/
	//-----------------------------------------------------------------//
	bool sjis_to_utf8(const std::string& src, std::string& dst) noexcept
	{
		if(src.empty()) return false;
		wstring ws;
		uint16_t wc = 0;
		for(auto ch : src) {
			uint8_t c = static_cast<uint8_t>(ch);
			if(wc) {
				if(0x40 <= c && c <= 0x7e) {
					wc <<= 8;
					wc |= c;
					ws += sjis_to_utf16(wc);
				} else if(0x80 <= c && c <= 0xfc) {
					wc <<= 8;
					wc |= c;
					ws += sjis_to_utf16(wc);
				}
				wc = 0;
			} else {
				if(0x81 <= c && c <= 0x9f) wc = c;
				else if(0xe0 <= c && c <= 0xfc) wc = c;
				else ws += sjis_to_utf16(c);
			}
		}
		utf16_to_utf8(ws, dst);
		return true;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	Shift-JIS から UTF-16 への変換
		@param[in]	src	Shift-JIS	ソース
		@param[out]	dst	UTF-16（追記）
		@return 変換が正常なら「true」
	*/
	//-----------------------------------------------------------------//
	bool sjis_to_utf16(const std::string& src, wstring& dst) noexcept
	{
		if(src.empty()) return false;
		std::string tmp;
		bool f = sjis_to_utf8(src, tmp);
		if(f) utf8_to_utf16(tmp, dst);
		return f;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	UTF-8 から Shift-JIS への変換
		@param[in]	src	UTF8 ソース
		@param[out]	dst	Shift-JIS（追記）
		@return 変換が正常なら「true」
	*/
	//-----------------------------------------------------------------//
	bool utf8_to_sjis(const std::string& src, std::string& dst) noexcept
	{
		if(src.empty()) return false;

		wstring ws;
		utf8_to_utf16(src, ws);
		for(auto wc : ws) {
			uint16_t ww = utf16_to_sjis(wc);
			if(ww <= 255) {
				dst += ww;
			} else {
				dst += ww >> 8;
				dst += ww & 0xff;
			}
		}
		return true;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	UTF-16 から Shift-JIS への変換
		@param[in]	src	UTF16 ソース
		@param[out]	dst	Shift-JIS（追記）
		@return 変換が正常なら「true」
	*/
	//-----------------------------------------------------------------//
	bool utf16_to_sjis(const wstring& src, std::string& dst) noexcept
	{
		if(src.empty()) return false;

		std::string tmp;
		utf16_to_utf8(src, tmp);
		utf8_to_sjis(tmp, dst);
		return true;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	文字列の評価変換
		@param[in]	src	ソース文字列
		@param[out]	dst 変換後の文字列
		@return 変換された文字数
	*/
	//-----------------------------------------------------------------//
	int string_conv(const lstring& src, lstring& dst)
	{
		if(src.empty()) return 0;

		static const lstring tbl = {
			0x0009, ' ',	/// TAB ---> SPACE
			0x3000, ' ',	/// 全角スペース ---> SPACE
		};

		lstring s;
		int n = code_conv(src, tbl, s);

		lstring spc = { ' ' };
		lstrings ss = split_text(s, spc);

		for(const auto& l : ss) {
			dst += l;
			dst += ' ';
		}

		return n;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	文字列の評価比較
		@param[in]	srca	ソース文字列 A
		@param[in]	srcb	ソース文字列 B
		@return 正確に一致したら 1.0 を返す
	*/
	//-----------------------------------------------------------------//
	float compare(const lstring& srca, const lstring& srcb)
	{
		if(srca.empty() || srcb.empty()) return 0.0f;

		lstring a;
		string_conv(srca, a);
		lstring b;
		string_conv(srcb, b);

		lstring spcs = { ' ' };
		lstrings aa = split_text(a, spcs);
		lstrings bb = split_text(b, spcs);

		uint32_t anum = 0;
		for(const auto& s : aa) {
			anum += s.size();
		}
		uint32_t bnum = 0;
		for(const auto& s : bb) {
			bnum += s.size();
		}

		float ans = 0.0f;
		uint32_t n = aa.size();
		uint32_t num = anum;
		if(n > bb.size()) {
			n = bb.size();
			num = bnum;
		}
		for(uint32_t i = 0; i < n; ++i) {
			if(aa[i] == bb[i]) {
				ans += static_cast<float>(aa[i].size()) / static_cast<float>(num);
			}
		}
		return ans;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	フルパスか、相対パスか検査する
		@param[in]	path	ファイルパス
		@return フル・パスなら「true」
	*/
	//-----------------------------------------------------------------//
	bool probe_full_path(const std::string& path)
	{
		if(path.empty()) return false;

		char ch = path[0];
#ifdef WIN32
		// WIN32 ではドライブレターの検査
		if(path.size() >= 3 && path[1] == ':' &&
			((path[0] >= 'A' && path[0] <= 'Z') || (path[0] >= 'a' && path[0] <= 'z'))) {
			ch = path[2];
		} else {
			ch = 0;
		}
#endif
		if(ch != 0 && ch == '/') {
			return true;
		}
		return false;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	階層を一つ戻ったパスを得る
		@param[in]	src	ソースパス
		@return 戻ったパス
	*/
	//-----------------------------------------------------------------//
	std::string previous_path(const std::string& src)
	{
		std::string dst;
		if(src.empty()) {
			return dst;
		}
		auto tmp = strip_last_of_delimita_path(src);
		std::string::size_type n = tmp.find_last_of('/');
		if(n == std::string::npos) {
			return dst;
		}
		dst = tmp.substr(0, n);
		// ルートの場合
		if(dst.find('/') == std::string::npos) {
			dst += '/';
		}
		return dst;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	パスを追加
		@param[in]	src	ソースパス
		@param[in]	add	追加パス
		@return 合成パス（エラーならempty）
	*/
	//-----------------------------------------------------------------//
	std::string append_path(const std::string& src, const std::string& add)
	{
		if(src.empty() || add.empty()) return std::string();
		std::string dst;
		if(add[0] == '/') {	// 新規パスとなる
			if(add.size() > 1) {
				dst = add;
			} else {
				return std::string();
			}
		} else {
			auto tmp = strip_last_of_delimita_path(src);
			dst = tmp + '/' + add;
		}
		return dst;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	デリミタを変換
		@param[in]	src	ソースパス
		@param[in]	org_ch 元のキャラクター
		@param[in]	cnv_ch  変換後のキャラクター
		@return 出力パス
	*/
	//-----------------------------------------------------------------//
	std::string convert_delimiter(const std::string& src, char org_ch, char cnv_ch)
	{
		char back = 0;
		std::string dst;
		for(auto ch : src) {
			if(ch == org_ch) {
				if(back != 0 && back != cnv_ch) ch = cnv_ch;
			}
			if(back) dst += back;
			back = ch;
		}
		if(back) dst += back;

		return dst;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	拡張子フィルター
		@param[in]	src	ソース
		@param[in]	ext	拡張子（「,」で複数指定）
		@param[in]	cap	「false」なら大文字小文字を判定する
		@return リスト
	*/
	//-----------------------------------------------------------------//
	strings ext_filter_path(const strings& src, const std::string& ext, bool cap) noexcept
	{
		strings dst;
		strings exts = split_text(ext, ",");
		for(const auto& s : src) {
			std::string src_ext = get_file_ext(s);
			for(const auto& ex : exts) {
				if(cap) {
					if(no_capital_strcmp(src_ext, ex) == 0) {
						dst.push_back(s);
					}
				} else {
					if(ex == src_ext) {
						dst.push_back(s);
					}
				}
			}
		}
		return dst;
	}

}
