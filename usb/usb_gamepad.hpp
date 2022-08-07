#pragma once
//=========================================================================//
/*!	@file
	@brief	USB/GAMEPAD Class
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "tinyusb/src/class/hid/hid.h"

namespace usb {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  USB/GAMEPAD class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class gamepad {


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		gamepad() noexcept { }


		//-----------------------------------------------------------------//
		/*!
			@brief  unmount（デバイスが、umount されたら呼ぶ）
		*/
		//-----------------------------------------------------------------//
		void unmount() noexcept
		{
		}


		void injection(const uint8_t* msg, uint16_t len) noexcept
		{

		}

	};
}
