#pragma once
//=====================================================================//
/*!	@file
	@brief	固定サイズ・リスト・クラス @n
			※作業中
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  固定サイズ・リスト・クラス
		@param[in]	ITEM	格納型
		@param[in]	SIZE	リスト・サイズ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ITEM, uint32_t SIZE>
	struct fixed_list {

		typedef ITEM value_type;

	private:

		struct list_t {
			list_t*	back_;
			ITEM	item_;
			list_t*	next_;
			list_t() : back_(nullptr), item_(), next_(nullptr) { }
		};

		list_t		list_[SIZE];
		uint32_t	count_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		fixed_list() noexcept : list_{ }, count_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  格納可能な最大サイズを返す
			@return 格納可能な最大サイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t capacity() const noexcept { return SIZE; }


		//-----------------------------------------------------------------//
		/*!
			@brief  現在のサイズを返す
			@return 現在のサイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t size() const noexcept { return count_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  リストをクリア（リセット）
		*/
		//-----------------------------------------------------------------//
///		void clear() noexcept { pos_ = 0; }


		bool insert(const ITEM& item)
		{
			list_[count_].item_ = item;
			++count_;

		}


	};
}
