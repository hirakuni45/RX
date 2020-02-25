#pragma once
//=====================================================================//
/*!	@file
	@brief	USB Host クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  USB Host クラス
		@param[in]	USBIO	USB_IO クラス
		@param[in]	PMAP	電源管理、ポート・マップ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class USBIO, port_map::option PMAP = port_map::option::FIRST>
	class usb_host {

		USBIO&		usbio_;

		uint8_t		ilvl_;

		static INTERRUPT_FUNC void i_task_()
		{
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	usbio	USB_IO クラス（参照）
		*/
		//-----------------------------------------------------------------//
		usb_host(USBIO& usbio) noexcept : usbio_(usbio), ilvl_(0)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	ilvl	割り込みレベル
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start(uint8_t ilvl) noexcept
		{
			ilvl_ = ilvl;


			return true;
		}


	};
}
