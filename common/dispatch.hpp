#pragma once
//=====================================================================//
/*!	@file
	@brief	ディスパッチ・クラス @n
			グループ割り込みの分類を行うサポート用
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX600/peripheral.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  dispatch class
		@param[in]	PER	ペリフェラル
		@param[in]	NUM	分岐数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<device::peripheral PER, uint32_t NUM>
	class dispatch {

		void*	task_[NUM];

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		dispatch() noexcept : task_{ nullptr } { }


		//-----------------------------------------------------------------//
		/*!
			@brief	分岐タスクを登録
			@param[in]	task	タスク
		*/
		//-----------------------------------------------------------------//
		void set_task(void* task, uint32_t index) noexcept
		{
			if(index < NUM) {
				task_[index] = task;
			}
		}
	};
}
