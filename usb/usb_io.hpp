#pragma once
//=====================================================================//
/*!	@file
	@brief	USB I/O 制御クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "r_usb_basic_if.h"

extern "C" {
	void usb_hstd_usb_handler(void);
	void hw_usb_pclear_sts_resm(void);
};

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  USB 基本Ｉ／Ｏ制御クラス
		@param[in]	USB_CH	USB チャネル
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class USB_CH>
	class usb_io {

		typedef utils::format format;

		uint8_t			ilvl_;

		ICU::VECTOR		ivec_;

		int32_t			event_;

		uint32_t		cnt_;

		static INTERRUPT_FUNC void i_task_()
		{
			usb_hstd_usb_handler(); /* Call interrupt routine */
		}


		static INTERRUPT_FUNC void r_task_()
		{
///			hw_usb_pclear_sts_resm();
///			ICU.IPR[ilvl_] = 0x00; /* Priority Resume1=0 */
///			ICU.IR[ilvl_] = 0; /* Interrupt Request USB_resume USBR0 Clear */
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		usb_io() : ilvl_(0), ivec_(ICU::VECTOR::NONE),
			event_(-1)
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

			// VBUSEN, OVERCURA ピンの設定
			if(!port_map::turn(USB_CH::get_peripheral())) {
				return false;
			}

			return true;
		}


		void enable_mod(bool ena = true) noexcept
		{
			format("USB0: enable_mod (%d)...\n") % static_cast<int>(ena);
			power_mgr::turn(USB_CH::get_peripheral(), ena);
		}


		void init_intr() noexcept
		{
			auto no = USB_CH::get_i_vec();
			ivec_ = icu_mgr::set_interrupt(no, i_task_, ilvl_);
			format("USB0: init_intr(Vec: %d, No: %d, Lvl: %d)...\n")
				% static_cast<int>(ivec_) % static_cast<int>(no) % static_cast<int>(ilvl_);
		}


		void enable_intr(bool ena = true) noexcept
		{
///			format("USB0: enable_intr(%d)...\n") % static_cast<int>(ena);
			ICU::IER.enable(static_cast<uint8_t>(ivec_), ena);
		}
	};

//	template <class USB_CH> volatile uint32_t usb_io<USB_CH>::int_cnt_ = 0;
}
