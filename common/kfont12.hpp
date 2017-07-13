#pragma once
//=====================================================================//
/*!	@file
	@brief	１２×１２漢字フォント・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include "ff12a/src/ff.h"

namespace graphics {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	漢字フォント・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint8_t CASH_SIZE>
	class kfont12 {

		struct kanji_cash {
			uint16_t	code;
			uint8_t		bitmap[18];
		};
		kanji_cash cash_[CASH_SIZE];
		uint8_t cash_idx_;

		bool	mount_;

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
		kfont12() : cash_idx_(0), mount_(false) {
			for(uint8_t i = 0; i < CASH_SIZE; ++i) {
				cash_[i].code = 0;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	文字の横幅
		*/
		//-----------------------------------------------------------------//
		static const int8_t width = 12;


		//-----------------------------------------------------------------//
		/*!
			@brief	文字の高さ
		*/
		//-----------------------------------------------------------------//
		static const int8_t height = 12;


		//-----------------------------------------------------------------//
		/*!
			@brief	マウント状態の設定
		*/
		//-----------------------------------------------------------------//
		void set_mount(bool f) { mount_ = f; }


		//-----------------------------------------------------------------//
		/*!
			@brief	文字のビットマップを取得
			@param[in]	code	文字コード（unicode）
			@return 文字のビットマップ
		*/
		//-----------------------------------------------------------------//
		const uint8_t* get(uint16_t code) {

			if(code == 0) return nullptr;

			// キャッシュ内検索
			int8_t n = -1;
			for(uint8_t i = 0; i < CASH_SIZE; ++i) {
				if(cash_[i].code == code) {
					return &cash_[i].bitmap[0];
				} else if(cash_[i].code == 0) {
					n = i;
				}
			}
			if(n >= 0) cash_idx_ = n;
			else {
				for(uint8_t i = 0; i < CASH_SIZE; ++i) {
					++cash_idx_;
					if(cash_idx_ >= CASH_SIZE) cash_idx_ = 0;
					if(cash_[cash_idx_].code != 0) {
						break;
					}
				}
			}

			if(!mount_) return nullptr;

			uint32_t lin = sjis_to_liner_(ff_convert(code, 0));

			if(lin == 0xffff) {
				return nullptr;
			}

			FIL fp;
			if(f_open(&fp, "/kfont12.bin", FA_READ) != FR_OK) {
				return nullptr;
			}
 
			if(f_lseek(&fp, lin * 18) != FR_OK) {
				f_close(&fp);
				return nullptr;
			}

			UINT rs;
			if(f_read(&fp, &cash_[cash_idx_].bitmap[0], 18, &rs) != FR_OK) {
				f_close(&fp);
				return nullptr;
			}
			cash_[cash_idx_].code = code;

			f_close(&fp);

			return &cash_[cash_idx_].bitmap[0];
		}
	};
}
