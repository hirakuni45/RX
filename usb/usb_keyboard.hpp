#pragma once
//=====================================================================//
/*!	@file
	@brief	USB/KEYBOARD Class
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/fixed_fifo.hpp"

namespace usb {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  KEYBOARD class
		@param[in]	USB_IO	USB 制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class keyboard {
	public:
		typedef utils::fixed_fifo<char, 16> FIFO;

	private:

		static const uint8_t BITS_CTRL_LEFT   = 0b00000001;
		static const uint8_t BITS_SHIFT_LEFT  = 0b00000010;
		static const uint8_t BITS_ALT_LEFT    = 0b00000100;
		static const uint8_t BITS_WIN_LEFT    = 0b00001000;
		static const uint8_t BITS_CTRL_RIGHT  = 0b00010000;
		static const uint8_t BITS_SHIFT_RIGHT = 0b00100000;
		static const uint8_t BITS_ALT_RIGHT   = 0b01000000;
		static const uint8_t BITS_WIN_RIGHT   = 0b10000000;

		static const uint8_t BITS_SHIFT       = BITS_SHIFT_LEFT | BITS_SHIFT_RIGHT;
		static const uint8_t BITS_CTRL        = BITS_CTRL_LEFT | BITS_CTRL_RIGHT;
		static const uint8_t BITS_ALT         = BITS_ALT_LEFT | BITS_ALT_RIGHT;
		static const uint8_t BITS_WIN         = BITS_WIN_LEFT | BITS_WIN_RIGHT;

		FIFO		fifo_;

		uint8_t		bits_;
		bool		caps_lock_;

		void put_(char code) {
			fifo_.put(code);
		}

		void put_(char normal, char shift) {
			if((bits_ & BITS_SHIFT) != 0) {
				fifo_.put(shift);
			} else {
				fifo_.put(normal);
			}
		}

		void puta_(char code) {
			if((bits_ & BITS_CTRL) != 0) {
				fifo_.put(code - 0x40);
				return;
			}

			if((bits_ & BITS_SHIFT) != 0) {
				fifo_.put(code += 0x20);
			} else {
				fifo_.put(code);
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		keyboard() : fifo_(), bits_(0), caps_lock_(false)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  パース
			@param[in]	bits	制御ビット（[0])
			@param[in]	code	コード（[2])
		*/
		//-----------------------------------------------------------------//
		void parse(uint8_t bits, uint8_t code)
		{
			if(bits != 0) {
				bits_ ^= bits;
			}

			if(code >= 0x04 && code <= 0x1D) {  // A to Z
				puta_('A' + code - 0x04);
				return;
			} else if(code >= 0x3A && code <= 0x45) {  // F1 to F12
				put_(0xA0 + code - 0x3A);
				return;
			}

			switch(code) {

			case 0x29: put_(0x1b); break;  // ESC

			case 0x49: put_(0x01); break;  // INS
			case 0x4C: put_(0x7F); break;  // DEL

			case 0x3A: put_('`', '~'); break;
			case 0x1E: put_('1', '!'); break;
			case 0x1F: put_('2', '@'); break;
			case 0x20: put_('3', '#'); break;
			case 0x21: put_('4', '$'); break;
			case 0x22: put_('5', '%'); break;
			case 0x23: put_('6', '^'); break;
			case 0x24: put_('7', '&'); break;
			case 0x25: put_('8', '*'); break;
			case 0x26: put_('9', '('); break;
			case 0x27: put_('0', ')'); break;
			case 0x2D: put_('-', '_'); break;
			case 0x2E: put_('=', '+'); break;
			case 0x2A: put_(0x08); break;  // BS
			case 0x2B: put_(0x09); break;  // TAB

			case 0x2F: put_('[', '{'); break;
			case 0x30: put_(']', '}'); break;
			case 0x31: put_('\\', '|'); break;

			case 0x39: caps_lock_ = !caps_lock_; break;  // CapsLock
			case 0x33: put_(';', ':'); break;
			case 0x34: put_('\'', '"'); break;
			case 0x28: put_(0x0D); break;  // Enter

			case 0x36: put_(',', '<'); break;
			case 0x37: put_('.', '>'); break;
			case 0x38: put_('/', '?'); break;

			case 0x4F: put_(0x81); break;  // ARROW-RIGHT
			case 0x50: put_(0x82); break;  // ARROW-LEFT
			case 0x51: put_(0x83); break;  // ARROW-DOWN
			case 0x52: put_(0x84); break;  // ARROW-UP

			case 0x47: put_(0x85); break;  // ScrollLock
			case 0x4A: put_(0x86); break;  // HOME
			case 0x4B: put_(0x87); break;  // PageUp
			case 0x4E: put_(0x88); break;  // PageDown
			case 0x4D: put_(0x89); break;  // END
			case 0x53: put_(0x8A); break;  // NumLock
			case 0x65: put_(0x8B); break;  // Menu

			case 0x2C: put_(0x20); break;  // SPC

			default: break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  バッファを参照
			@return バッファ
		*/
		//-----------------------------------------------------------------//
		const auto& get() const { return fifo_; }
	};
}
