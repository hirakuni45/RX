#pragma once
//=====================================================================//
/*!	@file
	@brief	ログ・マネージャー・クラス @n
			・バックアップ可能な、領域を使ったログメモリー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace utils {

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    /*!
        @brief  log_man クラス
		@param[in]	MEMIO	メモリー入出力
    */
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class MEMIO>
	class log_man {

		static const uint32_t offset_ = 8;
		static const uint32_t uniq_id_ = 0x1a3c5976;  // 初期化判定ユニークコード

		struct area_t {
			uint32_t	id_;
			uint16_t	pos_;
			uint16_t	len_;
		};

		area_t		area_;

	public:
        //-----------------------------------------------------------------//
        /*!
            @brief  コンストラクター
        */
        //-----------------------------------------------------------------//
		log_man() noexcept { }


        //-----------------------------------------------------------------//
        /*!
            @brief  消去
        */
        //-----------------------------------------------------------------//
		void clear() noexcept
		{
			area_.id_ = uniq_id_;
			area_.pos_ = 0;
			area_.len_ = 0;
			MEMIO::copy(&area_, sizeof(area_t), 0x0000);
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  開始 @n
					※ワークメモリーが無効状態なら初期化する。
			@return ワークメモリーが有効なら「true」
        */
        //-----------------------------------------------------------------//
		bool start() noexcept
		{
			MEMIO::start();
			MEMIO::copy(0x0000, sizeof(area_t), &area_);
			if(area_.id_ == uniq_id_) {
				return true;
			}
			clear();
			return false;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  文字追加
			@param[in]	ch	文字
        */
        //-----------------------------------------------------------------//
		void putch(char ch) noexcept
		{
			MEMIO::put(sizeof(area_t) + area_.pos_, ch);
			++area_.pos_;
			uint16_t limit = MEMIO::SIZE - sizeof(area_t);
			if(area_.pos_ >= limit) area_.pos_ = 0;
			++area_.len_;
			if(area_.len_ > limit) area_.len_ = limit;
			MEMIO::copy(&area_, sizeof(area_t), 0x0000);
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  文字列追加
			@param[in]	s	文字列
        */
        //-----------------------------------------------------------------//
		void puts(const char* s) noexcept
		{
			if(s == nullptr) return;

			char ch;
			while((ch = *s) != 0) {
				putch(ch);
				++s;
			}
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  記録長の取得
			@return 記録長
        */
        //-----------------------------------------------------------------//
		uint16_t get_length() const noexcept { return area_.len_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  文字の取得
			@param[in]	pos	取得位置
			@return 文字
        */
        //-----------------------------------------------------------------//
		char getch(uint16_t pos) const noexcept
		{
			if(area_.len_ == 0) return 0;

			pos += area_.pos_ - area_.len_;
			pos %= MEMIO::SIZE - sizeof(area_t);
			uint8_t data;
			if(MEMIO::get(pos + sizeof(area_t), data)) {
				return static_cast<char>(data);
			} else {
				return 0;
			}
		}
	};
}
