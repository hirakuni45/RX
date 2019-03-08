#pragma once
//=====================================================================//
/*!	@file
	@brief	漢字フォント・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include "ff12b/src/ff.h"

// 漢字フォントデータをＳＤカード上に置いて、キャッシュアクセスする場合有効にする
// #define CASH_KFONT

#ifdef CASH_KFONT
extern "C" {
	int fatfs_get_mount();
};
#endif

namespace graphics {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	漢字 無効フォント定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class kfont_null {
	public:
		static const int8_t width = 0;
		static const int8_t height = 0;
		const uint8_t* get(uint16_t code) noexcept { return nullptr; }
		bool injection_utf8(uint8_t ch) noexcept { return true; }
		uint16_t get_utf16() const noexcept { return 0x0000; } 
	};

#ifndef CASH_KFONT
	struct kfont_bitmap {
		static const uint8_t kfont_start[];
	};
#endif

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	漢字フォント・テンプレート・クラス
		@param[in]	WIDTH	フォントの横幅
		@param[in]	HEIGHT	フォントの高さ
		@param[in]	CASHN	キャッシュ数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
#ifdef CASH_KFONT
	template <int8_t WIDTH, int8_t HEIGHT, uint8_t CASHN>
#else
	template <int8_t WIDTH, int8_t HEIGHT>
#endif
	class kfont {

		static const uint32_t FONTS = ((WIDTH * HEIGHT) + 7) / 8;

		uint16_t	code_;
		int8_t		cnt_;

#ifdef CASH_KFONT
		struct kanji_cash {
			uint16_t	code;
			uint8_t		bitmap[FONTS];
			kanji_cash() noexcept : code(0), bitmap{ 0 } { }
		};
		kanji_cash cash_[CASHN];
		uint8_t cash_idx_;
#endif

		static uint16_t sjis_to_liner_(uint16_t sjis)
		{
			uint16_t code;
			uint8_t up = sjis >> 8;
			uint8_t lo = sjis & 0xff;
			if(0x81 <= up && up <= 0x9f) {
				code = up - 0x81;
			} else if(0xe0 <= up && up <= 0xef) {
				code = (0x9f + 1 - 0x81) + up - 0xe0;
			} else {
				return 0xffff;
			}
			uint16_t loa = (0x7e + 1 - 0x40) + (0xfc + 1 - 0x80);
			if(0x40 <= lo && lo <= 0x7e) {
				code *= loa;
				code += lo - 0x40;
			} else if(0x80 <= lo && lo <= 0xfc) {
				code *= loa;
				code += 0x7e + 1 - 0x40;
				code += lo - 0x80;
			} else {
				return 0xffff;
			}
			return code;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		kfont() noexcept : code_(0), cnt_(0) 
#ifdef CASH_KFONT
			, cash_(), cash_idx_(0)
#endif
			{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	文字の横幅
		*/
		//-----------------------------------------------------------------//
		static const int8_t width = WIDTH;


		//-----------------------------------------------------------------//
		/*!
			@brief	文字の高さ
		*/
		//-----------------------------------------------------------------//
		static const int8_t height = HEIGHT;


		//-----------------------------------------------------------------//
		/*!
			@brief	文字のビットマップを取得
			@param[in]	code	文字コード（unicode）
			@return 文字のビットマップ
		*/
		//-----------------------------------------------------------------//
		const uint8_t* get(uint16_t code) noexcept {

			if(code == 0) return nullptr;

#ifdef CASH_KFONT
			// キャッシュ内検索
			int8_t n = -1;
			for(uint8_t i = 0; i < CASHN; ++i) {
				if(cash_[i].code == code) {
					return &cash_[i].bitmap[0];
				} else if(cash_[i].code == 0) {
					n = i;
				}
			}
			if(n >= 0) cash_idx_ = n;
			else {
				for(uint8_t i = 0; i < CASHN; ++i) {
					++cash_idx_;
					if(cash_idx_ >= CASHN) cash_idx_ = 0;
					if(cash_[cash_idx_].code != 0) {
						break;
					}
				}
			}

			if(fatfs_get_mount() == 0) return nullptr;
#endif
			uint32_t lin = sjis_to_liner_(ff_convert(code, 0));

			if(lin == 0xffff) {
				return nullptr;
			}
#ifdef CASH_KFONT
			FIL fp;
			if(f_open(&fp, "/kfont16.bin", FA_READ) != FR_OK) {
				return nullptr;
			}
 
			if(f_lseek(&fp, lin * FONTS) != FR_OK) {
				f_close(&fp);
				return nullptr;
			}

			UINT rs;
			if(f_read(&fp, &cash_[cash_idx_].bitmap[0], FONTS, &rs) != FR_OK) {
				f_close(&fp);
				return nullptr;
			}
			cash_[cash_idx_].code = code;

			f_close(&fp);

			return &cash_[cash_idx_].bitmap[0];
#else
			return &kfont_bitmap::kfont_start[lin * FONTS];
#endif
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	UTF-8 コードを押し込む
			@return UTF-16 コードが完了した場合「true」
		*/
		//-----------------------------------------------------------------//
		bool injection_utf8(uint8_t ch) noexcept
		{
			if(ch < 0x80) {
				code_ = ch;
				return true;
			} else if((ch & 0xf0) == 0xe0) {
				code_ = (ch & 0x0f);
				cnt_ = 2;
				return false;
			} else if((ch & 0xe0) == 0xc0) {
				code_ = (ch & 0x1f);
				cnt_ = 1;
				return false;
			} else if((ch & 0xc0) == 0x80) {
				code_ <<= 6;
				code_ |= ch & 0x3f;
				cnt_--;
				if(cnt_ <= 0 && code_ < 0x80) {
					code_ = 0;	// 不正なコードとして無視
					return true;
				}
			}
			if(cnt_ == 0 && code_ != 0) {
				return true;
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	UTF-16 コードを取得
			@return UTF-16 コード
		*/
		//-----------------------------------------------------------------//
		uint16_t get_utf16() const noexcept { return code_; }
	};
}
