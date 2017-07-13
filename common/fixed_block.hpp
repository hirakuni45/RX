#pragma once
//=====================================================================//
/*!	@file
	@brief	固定サイズ・ブロック管理・クラス @n
			※最大３２個までのブロックを管理 @n
			※排他制御用ロック・ビットを含んでいる
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  固定サイズ・ブロック管理・クラス
		@param[in]	UNIT	格納形
		@param[in]	SIZE	サイズ（最大３２個）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class UNIT, uint32_t SIZE>
	class fixed_block {

		volatile uint32_t	flags_;
		volatile uint32_t	lock_;

		uint32_t	idx_;

		UNIT		unit_[SIZE];

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		fixed_block() noexcept : flags_(0), lock_(-1), idx_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  格納可能な最大サイズを返す
			@return 格納可能な最大サイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t capacity() const noexcept { return SIZE; }


		//-----------------------------------------------------------------//
		/*!
			@brief  空の検査
			@return 空の場合「true」
		*/
		//-----------------------------------------------------------------//
		bool empty() const noexcept { return flags_ == 0; }


		//-----------------------------------------------------------------//
		/*!
			@brief  全体クリア
		*/
		//-----------------------------------------------------------------//
		void clear() { flags_ = 0; lock_ = -1; }


		//-----------------------------------------------------------------//
		/*!
			@brief  利用サイズを返す
			@return 利用サイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t size() const noexcept
		{
			uint32_t n = 0;
			uint32_t tmp = 1;
			for(uint32_t i = 0; i < SIZE; ++i) {
				if(tmp & flags_) {
					++n;
				}
				tmp <<= 1;
			}
			return n;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  領域を確保して、インデックスを返す
			@return 空きが無い場合、「SIZE」となる。
		*/
		//-----------------------------------------------------------------//
		uint32_t alloc() noexcept
		{
			uint32_t idx = idx_;
			for(uint32_t i = 0; i < SIZE; ++i) {
				uint32_t mask = 1 << idx;
				if(!(mask & flags_)) {
					lock_  |= mask;  // ロックした状態にする
					flags_ |= mask;
					++idx_;
					if(idx_ >= SIZE) idx_ = 0;
					return idx;
				}
				++idx;
				if(idx >= SIZE) idx = 0;
			}
			return SIZE;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  領域の状態を取得
			@param[in]	idx	インデックス
			@return 利用中「true」、フリー「false」、エラー「false」
		*/
		//-----------------------------------------------------------------//
		bool is_alloc(uint32_t idx) const noexcept
		{
			if(idx >= SIZE) {
				return false;
			}
			return (flags_ & (1 << idx)) != 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ロックを取得
			@param[in]	idx	インデックス
			@return ロック「true」、アンロック「false」、エラー「false」
		*/
		//-----------------------------------------------------------------//
		bool is_lock(uint32_t idx) const noexcept
		{
			if(idx >= SIZE) {
				return false;
			}
			if(!is_alloc(idx)) return false; 
			return (lock_ & (1 << idx)) != 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ロックを設定
			@param[in]	idx	インデックス
			@return ロック「true」、アンロック「false」、エラー「false」
		*/
		//-----------------------------------------------------------------//
		bool lock(uint32_t idx, bool lock = true) noexcept
		{
			if(idx >= SIZE) {
				return false;
			}
			if(!is_alloc(idx)) return false; 
			if(lock) {
				lock_ |=  (1 << idx);
			} else {
				lock_ &= ~(1 << idx);
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  アン・ロックを設定
			@param[in]	idx	インデックス
			@return ロック「true」、アンロック「false」、エラー「false」
		*/
		//-----------------------------------------------------------------//
		bool unlock(uint32_t idx) noexcept { return lock(idx, false); }


		//-----------------------------------------------------------------//
		/*!
			@brief  領域を消去 @n
					※ロック状態に関係無く消去する @n
			@param[in]	idx	インデックス
			@return idx が不正、又は、既に開放されていた場合「false」
		*/
		//-----------------------------------------------------------------//
		bool erase(uint32_t idx) noexcept
		{
			if(idx >= SIZE) {
				return false;
			}
			uint32_t f = 1 << idx;
			if(flags_ & f) {
				flags_ &= ~f;
				return true;
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ユニットの参照
			@return ユニット
		*/
		//-----------------------------------------------------------------//
		UNIT& at(uint32_t idx) noexcept
		{
			return unit_[idx];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ユニットの取得
			@return ユニット
		*/
		//-----------------------------------------------------------------//
		const UNIT& get(uint32_t idx) const noexcept
		{
			return unit_[idx];
		}
	};
}
