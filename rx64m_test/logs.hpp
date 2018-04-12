#pragma once
//=====================================================================//
/*! @file
    @brief  ログ・クラス
	@copyright Copyright 2018 Kunihito Hiramatsu All Right Reserved.
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/format.hpp"
#include "common/time.h"

namespace seeda {

	device::standby_ram& at_sram();

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ログ・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class logs {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ログ構造体
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct log_t {
			time_t	time_;		///< 発生時間
///			char	msg_[64];	///< 内容
			char	msg_[4];	///< 内容
			log_t() : time_(0), msg_{ 0 } { }
		};

	private:
		static const uint32_t LOG_NUM = 16;

		static const uint16_t LOG_SIZE = 8;
		static const uint16_t LOG_POS  = 12;
		static const uint16_t LOG_T    = 16;

//		log_t		log_[LOG_NUM];
//		uint32_t	size_;
//		uint32_t	pos_;

		log_t		log_tmp_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		logs() : /* log_(nullptr), size_(0), pos_(0) */ log_tmp_() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  キャパシティを返す
			@return キャパシティ
		*/
		//-----------------------------------------------------------------//
		uint32_t capacity() const { return LOG_NUM; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ログの消去
		*/
		//-----------------------------------------------------------------//
		void clear()
		{
			at_sram().put32(LOG_SIZE, 0x0000);
			at_sram().put32(LOG_POS,  0x0000);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ログのサイズを返す
			@return ログのサイズ
		*/
		//-----------------------------------------------------------------//
//		uint32_t size() const { return size_; }
		uint32_t size() {
			uint32_t sz;
			at_sram().get32(LOG_SIZE, sz);
			if(sz > LOG_NUM) {
				clear();
				sz = 0;
			}
			return sz;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  カレント位置を返す
			@return カレント位置
		*/
		//-----------------------------------------------------------------//
		uint32_t current() const
		{
			uint32_t pos;
			at_sram().get32(LOG_POS, pos);
			return pos;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  文書を追加
			@param[in]	t	時間
			@param[in]	msg	ログ文書
			@param[in]	ftc	２０秒以内のログ追加を抑制する場合「true」
		*/
		//-----------------------------------------------------------------//
		void add(time_t t, const char* msg, bool ftc = false)
		{
			if(msg == nullptr) return;

			uint32_t pos;
			at_sram().get32(LOG_POS, pos);

			if(ftc && size() >= 7) {  // 7 個以上の記録がある場合
				// 一つ手前のログから２０秒以内の場合
				uint32_t np = (pos + LOG_NUM - 1) % LOG_NUM;
				log_t tmp = get(np);
				if(t < (tmp.time_ + 20)) {
					tmp.time_ = t;
					if(strlen(tmp.msg_) <= 2) {
						// strcat(tmp.msg_, "+");
					}
					at_sram().copy(&tmp, sizeof(log_t), LOG_T + sizeof(log_t) * np);
					return;
				}
			}

			log_t tmp;
			tmp.time_ = t;
			strncpy(tmp.msg_, msg, sizeof(log_t::msg_));
			at_sram().copy(&tmp, sizeof(log_t), LOG_T + sizeof(log_t) * pos);

			uint32_t sz = size();
			++sz;
			if(sz > LOG_NUM) sz = LOG_NUM;
			at_sram().put32(LOG_SIZE, sz);
			++pos;
			if(pos >= LOG_NUM) pos = 0;
			at_sram().put32(LOG_POS, pos);
#if 0
			log_[pos_].time_ = t;
 			strncpy(log_[pos_].msg_, msg, sizeof(log_t::msg_));
			++size_;
			if(size_ > LOG_NUM) size_ = LOG_NUM;
			++pos_;
			if(pos_ >= LOG_NUM) pos_ = 0;
#endif
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ログの参照
			@param[in]	pos	ログの位置
			@return ログ
		*/
		//-----------------------------------------------------------------//
		const log_t& get(uint32_t pos) {
#if 0
			if(pos >= size_) {
				return log_[0];
			}
			return log_[pos];
#endif
			if(pos >= size()) {
				return log_tmp_;
			}
			at_sram().copy(LOG_T + sizeof(log_t) * pos, sizeof(log_t), &log_tmp_);
			return log_tmp_;
		}
	};
}
