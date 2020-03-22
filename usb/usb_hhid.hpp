#pragma once
//=====================================================================//
/*!	@file
	@brief	USB/HHID Class
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/format.hpp"

#include "r_usb_hhid.h"
#include "r_usb_extern.h"
#include "r_usb_hhid_if.h"

namespace usb_host {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  HHID class
		@param[in]	USB_IO	USB 制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class USB_IO>
	class hhid {

		typedef utils::format format;

		static const uint16_t SET_PROTOCOL = USB_HID_SET_PROTOCOL | USB_HOST_TO_DEV | USB_CLASS | USB_INTERFACE;
		static const uint16_t SET_REPORT   = USB_HID_SET_REPORT   | USB_HOST_TO_DEV | USB_CLASS | USB_INTERFACE;
		static const uint16_t BOOT_PROTOCOL = 0;

		USB_IO&		usb_;

		usb_ctrl_t	ctrl_;

		uint16_t	type_;
		uint16_t	in_size_;
		uint16_t	out_size_;

		uint8_t		in_[64];
		uint8_t		out_[64];

		bool		configured_;

		void set_protocol_(uint8_t protocol)
		{
			ctrl_.type            = USB_REQUEST;
			ctrl_.setup.type      = SET_PROTOCOL; /* bRequestCode:SET_PROTOCOL, bmRequestType */
			ctrl_.setup.value     = protocol;     /* wValue: Protocol Type */
			ctrl_.setup.index     = 0x0000;       /* wIndex:Interface */
			ctrl_.setup.length    = 0x0000;       /* wLength:Zero */
			R_USB_Write(&ctrl_, (uint8_t *)USB_NULL, USB_NULL); /* Request Control transfer */
		}


		void parse_data_()
		{
			if(type_ == USB_HID_KEYBOARD) {
				format("KEY: ");
			} else if(type_ == USB_HID_MOUSE) {
				format("MOUSE: ");
			} else {
				format("OTHER: ");
			}
			for(uint16_t i = 0; i < in_size_; ++i) {
				format(" %02X") % static_cast<uint16_t>(in_[i]);
			}
			format("\n");
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	usb	USB_IO インスタンス
		*/
		//-----------------------------------------------------------------//
		hhid(USB_IO& usb) : usb_(usb), ctrl_(),
			type_(0), in_size_(0), out_size_(0), in_{ 0 }, out_{ 0 },
			configured_(false)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	タイプの取得
			@return タイプ
		 */
		//-----------------------------------------------------------------//
		auto get_type() const { return type_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	入力サイズの取得
			@return 入力サイズ
		 */
		//-----------------------------------------------------------------//
		auto in_size() const { return in_size_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	入力データの取得
			@return 入力データ
		 */
		//-----------------------------------------------------------------//
		const uint8_t* get_in_data() const { return in_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start() noexcept
		{
			ctrl_.module    = USB_IP0;
			ctrl_.type      = USB_HHID;

			usb_cfg_t cfg;
			cfg.usb_speed   = USB_FS;
			cfg.usb_mode    = USB_HOST;
			auto ret = R_USB_Open(&ctrl_, &cfg);
//			format("R_USB_Open: (%d)\n") % static_cast<int>(ret);

			configured_ = false;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	サービス
		 */
		//-----------------------------------------------------------------//
		void service() noexcept
		{
			auto event = R_USB_GetEvent(&ctrl_);
			switch (event) {
			case USB_STS_CONFIGURED:
				{
					uint8_t t = 0;
					R_USB_HhidGetType(&ctrl_, &t);
					type_ = t;
					uint16_t m;
					R_USB_HhidGetMxps(&ctrl_, &m, USB_IN);
					in_size_ = m;
					if(in_size_ > sizeof(in_)) {
						break;
					}
					R_USB_HhidGetMxps(&ctrl_, &m, USB_OUT);
					out_size_ = m;
					if(out_size_ > sizeof(out_)) {
						break;
					}
					configured_ = true;
					set_protocol_(BOOT_PROTOCOL);
				}
//				ip  = ctrl.module;
//				adr = ctrl.address;
				format("CONFIGURED: HHID, type: %d, in-size: %d, out-size: %d\n")
					% type_ % in_size_ % out_size_;
				break;

			case USB_STS_READ_COMPLETE:
				if(configured_) {
					parse_data_();
					R_USB_Read(&ctrl_, in_, in_size_);
				}
				break;

			case USB_STS_REQUEST_COMPLETE:
				if(configured_) {
					if(USB_HID_SET_PROTOCOL == (ctrl_.setup.type & USB_BREQUEST)) {
						ctrl_.type = USB_HHID;
						R_USB_Read(&ctrl_, in_, in_size_);
					}
				}
				break;
			
			case USB_STS_DETACH:
				format("DETACH: HHID\n");
				configured_ = false;
				break;

			case USB_STS_RESUME:
				break;

			default :
				break;
			}
		}
	};
}

