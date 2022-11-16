#pragma once
//=====================================================================//
/*!	@file
	@brief	割り込み・ユーティリティー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/R8C/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  null タスク
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class null_task {
	public:

		//-----------------------------------------------------------------//
		/*!
			@brief  ファンクタ
		*/
		//-----------------------------------------------------------------//
		void operator () () {
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  カウント・タスク
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class count_task {
		volatile uint32_t	count_;
	public:

		count_task() noexcept : count_(0) { }

		//-----------------------------------------------------------------//
		/*!
			@brief  ファンクタ
		*/
		//-----------------------------------------------------------------//
		void operator () () {
			++count_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  同期
		*/
		//-----------------------------------------------------------------//
		void sync() const noexcept
		{
			auto tmp = count_;
			while(tmp == count_) {

			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  カウンタの取得
			@return カウンタ
		*/
		//-----------------------------------------------------------------//
		auto get_count() const noexcept { return count_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  カウンタの設定
			@param[in]	count	カウント値
		*/
		//-----------------------------------------------------------------//
		void set_count(uint32_t count) noexcept { count_ = count; }
	};
}
