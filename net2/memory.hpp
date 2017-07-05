#pragma once
//=====================================================================//
/*!	@file
	@brief	ネット、メモリー・テンプレート @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include "common/net_tools.hpp"

namespace net {

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    /*!
        @brief  memory(fifo) クラス
		@param[in]	SIZE	バッファサイズ（最大６５５３６）
    */
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t SIZE>
	class memory {

		volatile uint16_t	get_;
		volatile uint16_t	put_;

		uint8_t	buff_[SIZE];

	public:
        //-----------------------------------------------------------------//
        /*!
            @brief  コンストラクター
        */
        //-----------------------------------------------------------------//
		memory() noexcept : get_(0), put_(0) { }


        //-----------------------------------------------------------------//
        /*!
            @brief  バッファのサイズを返す
			@return	バッファのサイズ
        */
        //-----------------------------------------------------------------//
		uint32_t size() const noexcept { return SIZE; }


        //-----------------------------------------------------------------//
        /*!
            @brief  長さを返す
			@return	長さ
        */
        //-----------------------------------------------------------------//
		uint32_t length() const noexcept {
			if(put_ >= get_) return (put_ - get_);
			else return (SIZE + put_ - get_);
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  クリア
        */
        //-----------------------------------------------------------------//
		void clear() noexcept { get_ = put_ = 0; }


        //-----------------------------------------------------------------//
        /*!
            @brief  格納ポイントの移動
			@param[in]	n	移動量
        */
        //-----------------------------------------------------------------//
		inline void put_go(uint16_t n) noexcept {
			volatile uint16_t put = put_;
			put += n;
			if(put >= SIZE) {
				put -= SIZE;
			}
			put_ = put;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  値の格納
			@param[in]	src	ソース
			@param[in]	len	長さ
			@param[in]	go	ポインターを更新しない場合「false」
        */
        //-----------------------------------------------------------------//
		void put(const void* src, uint16_t len, bool go = true) noexcept {
			uint16_t all = len;
			uint16_t fsz = SIZE - put_;
			uint16_t pos = put_;
			if(fsz <= len) {
				std::memcpy(&buff_[pos], src, fsz);
				len -= fsz;
				pos += fsz;
				if(pos >= SIZE) pos -= SIZE;
				src = static_cast<const void*>(static_cast<const uint8_t*>(src) + fsz);
			}
			if(len > 0) {
				std::memcpy(&buff_[pos], src, len);
			}
			if(go) put_go(all);
		}




        //-----------------------------------------------------------------//
        /*!
            @brief  取得ポイントの移動
			@param[in]	n	移動量
        */
        //-----------------------------------------------------------------//
		inline void get_go(uint16_t n) noexcept {
			volatile uint16_t get = get_;
			get += n;
			if(get >= SIZE) {
				get -= SIZE;
			}
			get_ = get;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  値の取得
			@param[out]	dst	コピー先
			@param[in]	len	長さ
			@param[in]	go	ポインターを更新しない場合「false」
        */
        //-----------------------------------------------------------------//
		void get(void* dst, uint16_t len, bool go = true) noexcept {
			uint16_t all = len;
			uint16_t fsz = SIZE - get_;
			uint16_t pos = get_;
			if(fsz <= len) {
				std::memcpy(dst, &buff_[pos], fsz);
				len -= fsz;
				pos += fsz;
				if(pos >= SIZE) pos -= SIZE;
				dst = static_cast<void*>(static_cast<uint8_t*>(dst) + fsz);
			}
			if(len > 0) {
				std::memcpy(dst, &buff_[pos], len);
			}
			if(go) get_go(all);
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  get 位置を返す
			@return	位置
        */
        //-----------------------------------------------------------------//
		uint16_t pos_get() const noexcept { return get_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  put 位置を返す
			@return	位置
        */
        //-----------------------------------------------------------------//
		uint16_t pos_put() const noexcept { return put_; }
	};
}
