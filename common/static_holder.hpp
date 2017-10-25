#pragma once
//=====================================================================//
/*!	@file
	@brief	スタティック・ホルダー・テンプレート・クラス
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
		@brief  スタティック・ホルダー・テンプレート・クラス
		@param[in]	ST	構造体
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ST>
	class static_holder {

		static ST	st_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  参照（RO）
			@return 参照
		*/
		//-----------------------------------------------------------------//
		const ST& get() { return st_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  参照
			@return 参照
		*/
		//-----------------------------------------------------------------//
		ST& at() { return st_; }
	};
	template <class ST> ST static_holder<ST>::st_;

}
