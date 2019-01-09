#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ USB 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"
#include "common/vect.h"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  USB I/O 制御クラス
		@param[in]	USB		USB 型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class USB>
	class usb_io {


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		usb_io() noexcept { }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start() noexcept
		{
			power_mgr::turn(USB::get_peripheral());




			return true;
		}

	};
}
