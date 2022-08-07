#pragma once
//=========================================================================//
/*!	@file
	@brief	USB/MOUSE Class
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/fixed_fifo.hpp"

#include "tinyusb/src/class/hid/hid.h"

namespace usb {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  USB/MOUSE class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class mouse {

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		mouse() noexcept { }


		//-----------------------------------------------------------------//
		/*!
			@brief  unmount（デバイスが、umount されたら呼ぶ）
		*/
		//-----------------------------------------------------------------//
		void unmount() noexcept
		{
		}

	};
}
