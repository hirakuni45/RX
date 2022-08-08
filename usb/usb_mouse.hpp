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
#include "common/vtx.hpp"

#include "tinyusb/src/class/hid/hid.h"

namespace usb {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  USB/MOUSE class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class mouse {
	public:

		static constexpr uint8_t LEFT_BUTTON     = MOUSE_BUTTON_LEFT;      ///< Left button
  		static constexpr uint8_t RIGHT_BUTTON    = MOUSE_BUTTON_RIGHT;     ///< Right button
  		static constexpr uint8_t MIDDLE_BUTTON   = MOUSE_BUTTON_MIDDLE;    ///< Middle button
  		static constexpr uint8_t BACKWARD_BUTTON = MOUSE_BUTTON_BACKWARD;  ///< Backward button,
  		static constexpr uint8_t FORWARD_BUTTON  = MOUSE_BUTTON_FORWARD;   ///< Forward button,

		struct state_t {
			bool		mount;

			vtx::ipos	min;
			vtx::ipos	max;
			vtx::ipos	pos;

			int16_t		wheel;

			uint8_t		level;
			uint8_t		positive;
			uint8_t		negative;

			state_t() noexcept : mount(false),
				min(0), max(0), pos(0), wheel(0),
				level(0), positive(0), negative(0) { }
		};

	private:

		uint16_t	vid_;
		uint16_t	pid_;

		uint32_t	count_;

		state_t		state_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		mouse() noexcept : vid_(0), pid_(0), count_(0), state_()
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  mount（デバイスが、umount されたら呼ぶ）
			@param[in]	vid		デバイスの VID
			@param[in]	pid		デバイスの PID
		*/
		//-----------------------------------------------------------------//
		void mount(uint16_t vid, uint16_t pid) noexcept
		{
			vid_ = vid;
			pid_ = pid;

			state_.mount = true;

			state_.min = vtx::ipos(0);
			state_.max = vtx::ipos(2048 * 100);
			state_.pos = vtx::ipos(0);

			state_.level = 0;
			state_.positive = 0;
			state_.negative = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  unmount（デバイスが、umount されたら呼ぶ）
		*/
		//-----------------------------------------------------------------//
		void unmount() noexcept
		{
			state_.mount = false;
		}


		void injection(const uint8_t* msg, uint16_t len) noexcept
		{
			if(len <= sizeof(hid_mouse_report_t)) {
				hid_mouse_report_t t;
				memcpy(&t, msg, len);

				state_.pos.x += t.x;
				state_.pos.x = std::min(state_.max.x, state_.pos.x);
				state_.pos.x = std::max(state_.min.x, state_.pos.x);
				state_.pos.y += t.y;
				state_.pos.y = std::min(state_.max.y, state_.pos.y);
				state_.pos.y = std::max(state_.min.y, state_.pos.y);
				if(len > 3) {
					state_.wheel += t.wheel;
					// t.pan;
				}

				auto back = state_.level;
				state_.level = t.buttons;
				state_.positive = ~back &  t.buttons;
				state_.negative =  back & ~t.buttons;  

				++count_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  移動量の最小値の参照
			@return 移動量の最小値
		*/
		//-----------------------------------------------------------------//
		auto& at_min() noexcept { return state_.min; }


		//-----------------------------------------------------------------//
		/*!
			@brief  移動量の最大値の参照
			@return 移動量の最大値
		*/
		//-----------------------------------------------------------------//
		auto& at_max() noexcept { return state_.max; }


		//-----------------------------------------------------------------//
		/*!
			@brief  状態の取得
			@return 状態
		*/
		//-----------------------------------------------------------------//
		const auto& get_state() const noexcept { return state_; }
	};
}
