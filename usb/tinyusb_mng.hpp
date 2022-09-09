#pragma once
//=========================================================================//
/*!	@file
	@brief	TinyUSB マネージャー・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"
#include "common/format.hpp"

#include "tusb.h"

#include "usb/usb_keyboard.hpp"
#include "usb/usb_mouse.hpp"
#include "usb/usb_gamepad.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  TinyUSB ベース・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class _>
	struct tinyusb_base {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  HID 接続種別型（ヒューマン・インターフェース・デバイス）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class HID_TYPE : uint8_t {
			NONE,				///< 接続無し
			KEYBOARD,			///< キーボード
			MOUSE,				///< マウス
			GENERIC_KEYBOARD,	///< GENERIC::DESK TOP キーボード
			GENERIC_MOUSE,		///< GENERIC::DESK TOP マウス
			GENERIC_GAMEPAD,	///< GENERIC::DESK TOP ゲームパッド
		};


		typedef utils::format format;
//		typedef utils::null_format format;


		static constexpr uint32_t MAX_REPORT = 4;

		struct hid_info_t {
			uint8_t report_count;
			tuh_hid_report_info_t report_info[MAX_REPORT];
		};

		struct holder_t {
			hid_info_t hid_info[CFG_TUH_HID];
			tuh_hid_report_info_t* rpt_info;
			bool		first_id;
			uint8_t		hid_num;
			uint16_t	vid[CFG_TUH_HID];
			uint16_t	pid[CFG_TUH_HID];
			uint8_t		dev_addr[CFG_TUH_HID];
			uint8_t		instance[CFG_TUH_HID];
			HID_TYPE	hid_type[CFG_TUH_HID];

			uint8_t		key_pad[8];
			uint8_t		led_bits;

			uint8_t		mouse_pad[5];

			ICU::VECTOR		ivec;

			bool		send_led;
//			uint8_t		leds_pad;

			holder_t() noexcept : hid_info{}, rpt_info(nullptr),
				first_id(false),
				hid_num(0),
				vid{ 0 }, pid{ 0 }, dev_addr{ 0 }, instance{ 0 },
				hid_type{ HID_TYPE::NONE },
				key_pad{ 0 }, led_bits(0),
				mouse_pad{ 0 },
				send_led(false)
				{ }
		};
		static holder_t holder_;


		static void dump_(const uint8_t* src, uint16_t len)
		{
			static uint8_t tmp[64];
			bool print = true;
			if(len <= sizeof(tmp)) {
				if(memcmp(tmp, src, len) == 0) {
					print = false;
				}
				memcpy(tmp, src, len);
			}
			if(print) {
				uint8_t n = 0;
				for(uint16_t i = 0; i < len; ++i) {
					format("0x%02X(%d) ") % static_cast<uint16_t>(src[i]) % static_cast<uint16_t>(src[i]);
					++n;
					if(n == 8) {
						format("\n");
						n = 0;
					}
				}
				if(n != 0) format("\n");
			}
		}


		static void set_intr(ICU::VECTOR ivec)
		{
			holder_.ivec = ivec;
		}


		static void enable_intr(bool ena)
		{
			ICU::IER.enable(holder_.ivec, ena);
		}


		static void generic_probe_(uint16_t instance, const uint8_t* desc_report, uint16_t desc_len)
		{
			holder_.hid_info[instance].report_count = tuh_hid_parse_report_descriptor(holder_.hid_info[instance].report_info, MAX_REPORT, desc_report, desc_len);
			uint8_t const rpt_count = holder_.hid_info[instance].report_count;
			tuh_hid_report_info_t* rpt_info_arr = holder_.hid_info[instance].report_info;

			holder_.first_id = false;
			if(rpt_count == 1 && rpt_info_arr[0].report_id == 0) {
				// Simple report without report ID as 1st byte
				holder_.rpt_info = &rpt_info_arr[0];
			} else {
				// Composite report, 1st byte is report ID, data starts from 2nd byte
				uint8_t const rpt_id = desc_report[0];
				// Find report id in the arrray
				for(uint8_t i = 0; i < rpt_count; i++) {
					if(rpt_id == rpt_info_arr[i].report_id) {
						holder_.rpt_info = &rpt_info_arr[i];
						break;
					}
				}
				holder_.first_id = true;
			}
		}


		static void hid_mount_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* desc_report, uint16_t desc_len)
		{
			uint16_t vid, pid;
			tuh_vid_pid_get(dev_addr, &vid, &pid);

			format("HID device address = %d, instance = %d is mounted\r\n")
				% static_cast<uint16_t>(dev_addr) % static_cast<uint16_t>(instance);
			format("VID = %04x, PID = %04x\r\n") % vid % pid;

			holder_.dev_addr[instance] = dev_addr;
			holder_.instance[instance] = instance;
			holder_.vid[instance] = vid;
			holder_.pid[instance] = pid;

			holder_.hid_type[instance] = HID_TYPE::NONE;

			auto itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);
			switch (itf_protocol) {
			case HID_ITF_PROTOCOL_KEYBOARD:
				format("Detected KEYBOARD\n");
				holder_.hid_type[instance] = HID_TYPE::KEYBOARD;
				for(uint8_t i = 0; i < sizeof(holder_.key_pad); ++i) {
					holder_.key_pad[i] = 0;
				}
				break;

			case HID_ITF_PROTOCOL_MOUSE:
				format("Detected MOUSE\n");
				holder_.hid_type[instance] = HID_TYPE::MOUSE;
				for(uint8_t i = 0; i < sizeof(holder_.mouse_pad); ++i) {
					holder_.mouse_pad[i] = 0;
				}
				break;

			case HID_ITF_PROTOCOL_NONE:
				// Generic report requires matching ReportID and contents with previous parsed report info
				format("Detected GENERIC\n");
				{
					generic_probe_(instance, desc_report, desc_len);
					if(holder_.first_id) {
						desc_report++;
						desc_len--;
					}
					if(holder_.rpt_info == nullptr) {
						format("Couldn't find the report info for this report !\n");
					} else {
						format("  HID has %u reports\n") % holder_.hid_info[instance].report_count;
						// For complete list of Usage Page & Usage checkout src/class/hid/hid.h. For examples:
						// - Keyboard                     : Desktop, Keyboard
						// - Mouse                        : Desktop, Mouse
						// - Gamepad                      : Desktop, Gamepad
						// - Consumer Control (Media Key) : Consumer, Consumer Control
						// - System Control (Power key)   : Desktop, System Control
						// - Generic (vendor)             : 0xFFxx, xx
						if(holder_.rpt_info->usage_page == HID_USAGE_PAGE_DESKTOP) {
							switch (holder_.rpt_info->usage) {
							case HID_USAGE_DESKTOP_KEYBOARD:
								format("  HID DESKTOP KEYBOARD\r\n");
								holder_.hid_type[instance] = HID_TYPE::GENERIC_KEYBOARD;
								break;
							case HID_USAGE_DESKTOP_MOUSE:
								format("  HID DESKTOP MOUSE\r\n");
								holder_.hid_type[instance] = HID_TYPE::GENERIC_MOUSE;
								break;
							case HID_USAGE_DESKTOP_GAMEPAD:
								format("  HID DESKTOP GAMEPAD\r\n");
								holder_.hid_type[instance] = HID_TYPE::GENERIC_GAMEPAD;
								break;
							default:
								format("  HID Other..\r\n");
								break;
							}
						}
					}
				}
				break;

			default:
				// By default host stack will use activate boot protocol on supported interface.
				// Therefore for this simple example, we only need to parse generic report descriptor (with built-in parser)
				format("Detected ???\n");
				break;
			}

			if(!tuh_hid_receive_report(dev_addr, instance)) {
				format("Error: cannot request to receive report\r\n");
			}
			++holder_.hid_num;
		}


		static void hid_umount_cb(uint8_t dev_addr, uint8_t instance)
		{
			format("HID device address = %d, instance = %d is unmounted\r\n")
				% static_cast<uint16_t>(dev_addr) % static_cast<uint16_t>(instance);
			holder_.hid_type[instance] = HID_TYPE::NONE;
			holder_.hid_num--;
		}


		static void hid_report_received_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* report, uint16_t len)
		{
			static uint8_t cnt = 0;

			auto itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);
			switch (itf_protocol) {
			case HID_ITF_PROTOCOL_KEYBOARD:
				if(len <= sizeof(holder_.key_pad)) {
					memcpy(holder_.key_pad, report, len);
				}
				break;

			case HID_ITF_PROTOCOL_MOUSE:
				if(len <= sizeof(holder_.mouse_pad)) {
					memcpy(holder_.mouse_pad, report, len);
				}
				break;

			default:
				if(holder_.first_id) {
					report++;
					len--;
				}
				if(holder_.rpt_info != nullptr && holder_.rpt_info->usage_page == HID_USAGE_PAGE_DESKTOP) {
					if(holder_.rpt_info->usage == HID_USAGE_DESKTOP_GAMEPAD) {
						// 20, 22 for 0
						if(len >= 19) {
							len = 19;
						}
					}
					dump_(report, len);
				} else {
					static uint16_t tmplen = 0;
					if(tmplen != len) {
						format("Generic: %d bytes\n") % len;
						tmplen = len;
					}
					dump_(report, len);
				}
				break;
			}

			// continue to request to receive report
			if(!tuh_hid_receive_report(dev_addr, instance)) {
				format("Error: cannot request to receive report\r\n");
			}
		}


		static void hid_app_task()
		{
#if 0
			if(holder_.send_led) {
				if(!tuh_hid_set_report(holder_.dev_addr, holder_.instance, 0, HID_REPORT_TYPE_OUTPUT, &holder_.led_bits, sizeof(holder_.led_bits))) {
					format("tuh_hid_set_report: fail...\n");
				}
				holder_.send_led = false;
			}
#endif
		}
	};
	template<class _> typename tinyusb_base<_>::holder_t tinyusb_base<_>::holder_;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  TinyUSB マネージャー・クラス
		@param[in]	USB_CH	USB チャネル
		@param[in]	PSEL	USB 制御ポート
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class USB_CH, port_map::ORDER PSEL = port_map::ORDER::FIRST>
	class tinyusb_mng : public tinyusb_base<void> {
	public:
		typedef tinyusb_base<void> BASE;

		typedef usb::keyboard KEYBOARD;
		typedef usb::mouse MOUSE;

		static constexpr uint8_t HID_MAX = CFG_TUH_HID;		///< HID の同時マウント数

	private:
		uint8_t			hid_num_;
		HID_TYPE		hid_type_[HID_MAX];

		KEYBOARD		keyboard_;
		MOUSE			mouse_;
		usb::gamepad	gamepad_;


		static INTERRUPT_FUNC void i_task_()
		{
#if CFG_TUH_ENABLED
			tuh_int_handler(0);
#endif
#if CFG_TUD_ENABLED
			tud_int_handler(0);
#endif
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		tinyusb_mng() noexcept :
			hid_num_(0), hid_type_{ HID_TYPE::NONE },
			keyboard_(), gamepad_()
		{}


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	ilvl	割り込みレベル
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start(uint8_t ilvl) noexcept
		{
			if(ilvl == 0) {  // 割り込み無しはエラー
				return false;
			}

			power_mgr::turn(USB_CH::PERIPHERAL);

			// VBUSEN, OVERCURA ピンの設定
			if(!port_map::turn(USB_CH::PERIPHERAL, true, PSEL)) {
				return false;
			}

			tuh_init(BOARD_TUH_RHPORT);

			{
				auto ivec = icu_mgr::set_interrupt(USB_CH::I_VEC, i_task_, ilvl);
//			utils::format("USB clock divider: 0b%04b\n") % static_cast<uint16_t>(device::SYSTEM::SCKCR2.UCK());
//			utils::format("USB0 interrupt vector: %u\n") % static_cast<uint16_t>(ivec_);

				ICU::IER.enable(ivec, false);
				set_intr(ivec);
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  tinyusb の統合サービス
		*/
		//-----------------------------------------------------------------//
		void service() noexcept
		{
			tuh_task();  // call tinyusb handler

#if CFG_TUH_CDC
			BASE::cdc_task();
#endif

#if CFG_TUH_HID
			hid_num_ = BASE::holder_.hid_num;
			for(uint8_t i = 0; i < hid_num_; ++i) {  // HID デバイスのディスパッチ
				auto back = hid_type_[i];
				hid_type_[i] = BASE::holder_.hid_type[i];
				auto instance = BASE::holder_.instance[i];
				switch(hid_type_[i]) {
				case HID_TYPE::KEYBOARD:
					if(back != HID_TYPE::KEYBOARD) {
						keyboard_.mount(holder_.vid[instance], holder_.pid[instance]);
					}
					keyboard_.injection(BASE::holder_.key_pad, sizeof(BASE::holder_.key_pad));
					{
						auto led_back = holder_.led_bits;
						holder_.led_bits = keyboard_.get_led_state();
						if(led_back != holder_.led_bits) {
							holder_.send_led = true;
						}
					}
					break;
				case HID_TYPE::MOUSE:
					if(back != HID_TYPE::MOUSE) {
						mouse_.mount(holder_.vid[instance], holder_.pid[instance]);
					}
					mouse_.injection(BASE::holder_.mouse_pad, sizeof(BASE::holder_.mouse_pad));
					break;
				case HID_TYPE::GENERIC_GAMEPAD:
					break;
				default:
					break;
				}
				switch(back) {
				case HID_TYPE::KEYBOARD:
					if(hid_type_[i] != HID_TYPE::KEYBOARD) {
						keyboard_.unmount();
					}
					break;
				case HID_TYPE::MOUSE:
					if(hid_type_[i] != HID_TYPE::MOUSE) {
						mouse_.unmount();
					}
					break;
				case HID_TYPE::GENERIC_GAMEPAD:
					if(hid_type_[i] != HID_TYPE::GENERIC_GAMEPAD) {
						gamepad_.unmount();
					}
					break;
				default:
					break;
				}
			}
			BASE::hid_app_task();
#endif
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  HID デバイス数取得（インスタンス数）
			@return HID デバイス数 
		*/
		//-----------------------------------------------------------------//
		auto get_hid_num() const noexcept { return hid_num_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  HID デバイスの種別取得
			@param[in]	instance	HID デバイスのインスタンス（整数）
			@return HID デバイスの種別 
		*/
		//-----------------------------------------------------------------//
		auto get_hid_type(uint8_t instance) const noexcept
		{
			if(instance < hid_num_) {
				return hid_type_[instance];
			} else {
				return HID_TYPE::NONE;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  キーボード・クラスの参照
			@return キーボードクラスの参照
		*/
		//-----------------------------------------------------------------//
		auto& at_keyboard() noexcept { return keyboard_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  マウス・クラスの参照
			@return マウスクラスの参照
		*/
		//-----------------------------------------------------------------//
		auto& at_mouse() noexcept { return mouse_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ゲームパッド・クラスの参照
			@return ゲームパッドクラスの参照
		*/
		//-----------------------------------------------------------------//
		auto& at_gamepad() noexcept { return gamepad_; }
	};

//	template <class USB_CH, port_map::ORDER PSEL> volatile uint32_t tinyusb_mng<USB_CH, PSEL>::intr_tick_ = 0;
}


extern "C" {

#if CFG_TUH_ENABLED
	void hcd_int_enable(uint8_t rhport)
	{
		device::tinyusb_base<void>::enable_intr(true);
	}


	void hcd_int_disable(uint8_t rhport)
	{
		device::tinyusb_base<void>::enable_intr(false);
	}
#endif

#if CFG_TUH_HID
	void tuh_hid_mount_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* desc_report, uint16_t desc_len)
	{
		device::tinyusb_base<void>::hid_mount_cb(dev_addr, instance, desc_report, desc_len);
	}


	void tuh_hid_umount_cb(uint8_t dev_addr, uint8_t instance)
	{
		device::tinyusb_base<void>::hid_umount_cb(dev_addr, instance);
	}


	void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* report, uint16_t len)
	{
		device::tinyusb_base<void>::hid_report_received_cb(dev_addr, instance, report, len);
	}
#endif

#if 0
	void tuh_cdc_xfer_isr(uint8_t dev_addr, xfer_result_t event, cdc_pipeid_t pipe_id, uint32_t xferred_bytes)
	{
	}
#endif
}