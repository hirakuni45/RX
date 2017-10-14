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
			area_.id_ = uniq_id_;
			area_.pos_ = 0;
			area_.len_ = 0;
			MEMIO::copy(&area_, sizeof(area_t), 0x0000);
			return false;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  文字列追加
			@param[in]	s	文字列
        */
        //-----------------------------------------------------------------//
		void puts(const char* s) noexcept
		{

		}


        //-----------------------------------------------------------------//
        /*!
            @brief  文字追加
			@param[in]	ch	文字
        */
        //-----------------------------------------------------------------//
		void putch(char ch) noexcept
		{
			uint32_t pos = sizeof(area_t) + area_.pos_;
			MEMIO::put(pos, ch);
			++pos;
			if(pos >= (MEMIO::SIZE - sizeof(area_t))) pos = 0;
			area_.pos_ = pos;
		}
	};
}

