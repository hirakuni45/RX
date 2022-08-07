#pragma once
//=========================================================================//
/*!	@file
	@brief	USB/KEYBOARD Class @n
			USB/KEYBOARD から送られて来るデータ列をデコードして ASCII コードを得る。 @n
			キーマップに従ったデータを管理する。 @n
			通常８バイトのデータが来る。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/fixed_fifo.hpp"

#include "tinyusb/src/class/hid/hid.h"

namespace usb {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  USB/KEYBOARD class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class keyboard {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  キー・マップ型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class MAP : uint8_t {
			NONE = HID_KEY_NONE,
			A = HID_KEY_A,
			B = HID_KEY_B,
			C = HID_KEY_C,
			D = HID_KEY_D,
			E = HID_KEY_E,
			F = HID_KEY_F,
			G = HID_KEY_G,
			H = HID_KEY_H,
			I = HID_KEY_I,
			J = HID_KEY_J,
			K = HID_KEY_K,
			L = HID_KEY_L,
			M = HID_KEY_M,
			N = HID_KEY_N,
			O = HID_KEY_O,
			P = HID_KEY_P,
			Q = HID_KEY_Q,
			R = HID_KEY_R,
			S = HID_KEY_S,
			T = HID_KEY_T,
			U = HID_KEY_U,
			V = HID_KEY_V,
			W = HID_KEY_W,
			X = HID_KEY_X,
			Y = HID_KEY_Y,
			Z = HID_KEY_Z,
			_1 = HID_KEY_1,
			_2 = HID_KEY_2,
			_3 = HID_KEY_3,
			_4 = HID_KEY_4,
			_5 = HID_KEY_5,
			_6 = HID_KEY_6,
			_7 = HID_KEY_7,
			_8 = HID_KEY_8,
			_9 = HID_KEY_9,
			_0 = HID_KEY_0,
			ENTER = HID_KEY_ENTER,
			ESCAPE = HID_KEY_ESCAPE,
			BACKSPACE = HID_KEY_BACKSPACE,
			TAB = HID_KEY_TAB,
			SPACE = HID_KEY_SPACE,
			MINUS = HID_KEY_MINUS,
			EQUAL = HID_KEY_EQUAL,
			BRACKET_LEFT = HID_KEY_BRACKET_LEFT,
			BRACKET_RIGHT = HID_KEY_BRACKET_RIGHT,
			BACKSLASH = HID_KEY_BACKSLASH,
			EUROPE_1 = HID_KEY_EUROPE_1,
			SEMICOLON = HID_KEY_SEMICOLON,
			APOSTROPHE = HID_KEY_APOSTROPHE,
			GRAVE = HID_KEY_GRAVE,
			COMMA = HID_KEY_COMMA,
			PERIOD = HID_KEY_PERIOD,
			SLASH = HID_KEY_SLASH,
			CAPS_LOCK = HID_KEY_CAPS_LOCK,
			F1 = HID_KEY_F1,
			F2 = HID_KEY_F2,
			F3 = HID_KEY_F3,
			F4 = HID_KEY_F4,
			F5 = HID_KEY_F5,
			F6 = HID_KEY_F6,
			F7 = HID_KEY_F7,
			F8 = HID_KEY_F8,
			F9 = HID_KEY_F9,
			F10 = HID_KEY_F10,
			F11 = HID_KEY_F11,
			F12 = HID_KEY_F12,
			PRINT_SCREEN = HID_KEY_PRINT_SCREEN,
			SCROLL_LOCK = HID_KEY_SCROLL_LOCK,
			PAUSE = HID_KEY_PAUSE,
			INSERT = HID_KEY_INSERT,
			HOME = HID_KEY_HOME,
			PAGE_UP = HID_KEY_PAGE_UP,
			DELETE = HID_KEY_DELETE,
			END = HID_KEY_END,
			PAGE_DOWN = HID_KEY_PAGE_DOWN,
			ARROW_RIGHT = HID_KEY_ARROW_RIGHT,
			ARROW_LEFT = HID_KEY_ARROW_LEFT,
			ARROW_DOWN = HID_KEY_ARROW_DOWN,
			ARROW_UP = HID_KEY_ARROW_UP,
			NUM_LOCK = HID_KEY_NUM_LOCK,
			KEYPAD_DIVIDE = HID_KEY_KEYPAD_DIVIDE,
			KEYPAD_MULTIPLY = HID_KEY_KEYPAD_MULTIPLY,
			KEYPAD_SUBTRACT = HID_KEY_KEYPAD_SUBTRACT,
			KEYPAD_ADD = HID_KEY_KEYPAD_ADD,
			KEYPAD_ENTER = HID_KEY_KEYPAD_ENTER,
			KEYPAD_1 = HID_KEY_KEYPAD_1,
			KEYPAD_2 = HID_KEY_KEYPAD_2,
			KEYPAD_3 = HID_KEY_KEYPAD_3,
			KEYPAD_4 = HID_KEY_KEYPAD_4,
			KEYPAD_5 = HID_KEY_KEYPAD_5,
			KEYPAD_6 = HID_KEY_KEYPAD_6,
			KEYPAD_7 = HID_KEY_KEYPAD_7,
			KEYPAD_8 = HID_KEY_KEYPAD_8,
			KEYPAD_9 = HID_KEY_KEYPAD_9,
			KEYPAD_0 = HID_KEY_KEYPAD_0,
			KEYPAD_DECIMAL = HID_KEY_KEYPAD_DECIMAL,
#if 0
#define HID_KEY_EUROPE_2                  0x64
#define HID_KEY_APPLICATION               0x65
#define HID_KEY_POWER                     0x66
#define HID_KEY_KEYPAD_EQUAL              0x67
#define HID_KEY_F13                       0x68
#define HID_KEY_F14                       0x69
#define HID_KEY_F15                       0x6A
#define HID_KEY_F16                       0x6B
#define HID_KEY_F17                       0x6C
#define HID_KEY_F18                       0x6D
#define HID_KEY_F19                       0x6E
#define HID_KEY_F20                       0x6F
#define HID_KEY_F21                       0x70
#define HID_KEY_F22                       0x71
#define HID_KEY_F23                       0x72
#define HID_KEY_F24                       0x73
#define HID_KEY_EXECUTE                   0x74
#define HID_KEY_HELP                      0x75
#define HID_KEY_MENU                      0x76
#define HID_KEY_SELECT                    0x77
#define HID_KEY_STOP                      0x78
#define HID_KEY_AGAIN                     0x79
#define HID_KEY_UNDO                      0x7A
#define HID_KEY_CUT                       0x7B
#define HID_KEY_COPY                      0x7C
#define HID_KEY_PASTE                     0x7D
#define HID_KEY_FIND                      0x7E
#define HID_KEY_MUTE                      0x7F
#define HID_KEY_VOLUME_UP                 0x80
#define HID_KEY_VOLUME_DOWN               0x81
#define HID_KEY_LOCKING_CAPS_LOCK         0x82
#define HID_KEY_LOCKING_NUM_LOCK          0x83
#define HID_KEY_LOCKING_SCROLL_LOCK       0x84
#define HID_KEY_KEYPAD_COMMA              0x85
#define HID_KEY_KEYPAD_EQUAL_SIGN         0x86
#define HID_KEY_KANJI1                    0x87
#define HID_KEY_KANJI2                    0x88
#define HID_KEY_KANJI3                    0x89
#define HID_KEY_KANJI4                    0x8A
#define HID_KEY_KANJI5                    0x8B
#define HID_KEY_KANJI6                    0x8C
#define HID_KEY_KANJI7                    0x8D
#define HID_KEY_KANJI8                    0x8E
#define HID_KEY_KANJI9                    0x8F
#define HID_KEY_LANG1                     0x90
#define HID_KEY_LANG2                     0x91
#define HID_KEY_LANG3                     0x92
#define HID_KEY_LANG4                     0x93
#define HID_KEY_LANG5                     0x94
#define HID_KEY_LANG6                     0x95
#define HID_KEY_LANG7                     0x96
#define HID_KEY_LANG8                     0x97
#define HID_KEY_LANG9                     0x98
#define HID_KEY_ALTERNATE_ERASE           0x99
#define HID_KEY_SYSREQ_ATTENTION          0x9A
#define HID_KEY_CANCEL                    0x9B
#define HID_KEY_CLEAR                     0x9C
#define HID_KEY_PRIOR                     0x9D
#define HID_KEY_RETURN                    0x9E
#define HID_KEY_SEPARATOR                 0x9F
#define HID_KEY_OUT                       0xA0
#define HID_KEY_OPER                      0xA1
#define HID_KEY_CLEAR_AGAIN               0xA2
#define HID_KEY_CRSEL_PROPS               0xA3
#define HID_KEY_EXSEL                     0xA4
#endif
		};

		/// 特殊キービット列定数
		static constexpr uint8_t SP_CTRL_LEFT   = KEYBOARD_MODIFIER_LEFTCTRL;		///< Left Control
		static constexpr uint8_t SP_SHIFT_LEFT  = KEYBOARD_MODIFIER_LEFTSHIFT;		///< Left Shift
		static constexpr uint8_t SP_ALT_LEFT    = KEYBOARD_MODIFIER_LEFTALT;		///< Left Alt
		static constexpr uint8_t SP_GUI_LEFT    = KEYBOARD_MODIFIER_LEFTGUI;		///< Left Window
		static constexpr uint8_t SP_CTRL_RIGHT  = KEYBOARD_MODIFIER_RIGHTCTRL;		///< Right Control
  		static constexpr uint8_t SP_SHIFT_RIGHT = KEYBOARD_MODIFIER_RIGHTSHIFT;		///< Right Shift
		static constexpr uint8_t SP_ALT_RIGHT   = KEYBOARD_MODIFIER_RIGHTALT;		///< Right Alt
		static constexpr uint8_t SP_GUI_RIGHT   = KEYBOARD_MODIFIER_RIGHTGUI;		///< Right Window

		/// LED ビット列定数
		static constexpr uint8_t LED_NUMLOCK    = KEYBOARD_LED_NUMLOCK;		///< Num Lock LED
		static constexpr uint8_t LED_CAPSLOCK   = KEYBOARD_LED_CAPSLOCK;	///< Caps Lock LED
		static constexpr uint8_t LED_SCROLLLOCK = KEYBOARD_LED_SCROLLLOCK;	///< Scroll Lock LED
		static constexpr uint8_t LED_COMPOSE    = KEYBOARD_LED_COMPOSE;		///< Composition Mode
		static constexpr uint8_t LED_KANA       = KEYBOARD_LED_KANA;		///< Kana mode

		struct key_t {
			char	code;
			MAP		map;
			key_t(char c = '\0', MAP m = MAP::NONE) noexcept : code(c), map(m) { } 
		};

		typedef utils::fixed_fifo<key_t, 16> FIFO;

	private:
		static constexpr uint8_t KEY_BUFF_NUM = 8;

		uint8_t		key_pad_[KEY_BUFF_NUM];
		bool		shift_;
		bool		ctrl_;
		bool		num_lock_;
		bool		caps_lock_;
		bool		scroll_lock_;
		bool		probe_;
		uint8_t		led_bits_;

		FIFO		fifo_;

		char convert_map_to_ascii_(uint8_t map)
		{
			char ch = 0;
			switch(static_cast<MAP>(map)) {
			case MAP::_1:
				if(shift_) ch = '!'; else ch = '1';
				break;
			case MAP::_2:
				if(shift_) ch = '@'; else ch = '2';
				break;
			case MAP::_3:
				if(shift_) ch = '#'; else ch = '3';
				break;
			case MAP::_4:
				if(shift_) ch = '$'; else ch = '4';
				break;
			case MAP::_5:
				if(shift_) ch = '%'; else ch = '5';
				break;
			case MAP::_6:
				if(shift_) ch = '^'; else ch = '6';
				break;
			case MAP::_7:
				if(shift_) ch = '&'; else ch = '7';
				break;
			case MAP::_8:
				if(shift_) ch = '*'; else ch = '8';
				break;
			case MAP::_9:
				if(shift_) ch = '('; else ch = '9';
				break;
			case MAP::_0:
				if(shift_) ch = ')'; else ch = '0';
				break;
			case MAP::MINUS:
				if(shift_) ch = '_'; else ch = '-';
				break;
			case MAP::EQUAL:
				if(shift_) ch = '+'; else ch = '=';
				break;
			case MAP::BRACKET_LEFT:
				if(shift_) ch = '{'; else ch = '[';
				break;
			case MAP::BRACKET_RIGHT:
				if(shift_) ch = '}'; else ch = ']';
				break;
			case MAP::BACKSLASH:
				if(shift_) ch = '|'; else ch = '\\';
				break;
			case MAP::SEMICOLON:
				if(shift_) ch = ':'; else ch = ';';
				break;
			case MAP::APOSTROPHE:
				if(shift_) ch = '"'; else ch = '\'';
				break;
			case MAP::COMMA:
				if(shift_) ch = '<'; else ch = ',';
				break;
			case MAP::PERIOD:
				if(shift_) ch = '>'; else ch = '.';
				break;
			case MAP::SLASH:
				if(shift_) ch = '?'; else ch = '/';
				break;
			case MAP::GRAVE:
				if(shift_) ch = '~'; else ch = '`';
				break; 
			case MAP::BACKSPACE: return 0x08;
			case MAP::TAB: return 0x09;
			case MAP::ESCAPE: return 0x1B;
			case MAP::ENTER: return 0x0D;
			case MAP::SPACE: return 0x20;
			case MAP::DELETE: return 0x7F;
			case MAP::NUM_LOCK:
				num_lock_ = !num_lock_;
				break;
			case MAP::CAPS_LOCK:
				caps_lock_ = !caps_lock_;
				break;
			case MAP::SCROLL_LOCK:
				scroll_lock_ = !scroll_lock_;
				break;
			case MAP::KEYPAD_DIVIDE: return '/';
			case MAP::KEYPAD_MULTIPLY: return '*';
			case MAP::KEYPAD_SUBTRACT: return '-';
			case MAP::KEYPAD_ADD: return '+';
			case MAP::KEYPAD_ENTER: return 0x0D;
			case MAP::KEYPAD_1: return '1';
			case MAP::KEYPAD_2: return '2';
			case MAP::KEYPAD_3: return '3';
			case MAP::KEYPAD_4: return '4';
			case MAP::KEYPAD_5: return '5';
			case MAP::KEYPAD_6: return '6';
			case MAP::KEYPAD_7: return '7';
			case MAP::KEYPAD_8: return '8';
			case MAP::KEYPAD_9: return '9';
			case MAP::KEYPAD_0: return '0';
			case MAP::KEYPAD_DECIMAL: return '.';
			default:
				if(map >= static_cast<uint8_t>(MAP::A) && map <= static_cast<uint8_t>(MAP::Z)) {
					ch = map - static_cast<uint8_t>(MAP::A) + 'a';
				}
				if(shift_) {
					if(!caps_lock_) ch -= 0x20;
				} else {
					if(caps_lock_) ch -= 0x20;
				}
				break;
			}
			if(ctrl_) {
				if(ch >= 0x40 && ch <= 0x5f) {
					ch -= 0x40;
				} else if(ch >= 0x60 && ch <= 0x7f) {
					ch -= 0x60;
				}
			}
			led_bits_ = 0;
			if(num_lock_) led_bits_ |= LED_NUMLOCK;
			if(caps_lock_) led_bits_ |= LED_CAPSLOCK;
			if(scroll_lock_) led_bits_ |= LED_SCROLLLOCK;
			return ch;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		keyboard() noexcept :
			key_pad_{ 0 }, shift_(false), ctrl_(false),
			num_lock_(false), caps_lock_(false), scroll_lock_(false), probe_(false), led_bits_(0),
			fifo_()
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  unmount（デバイスが、umount されたら呼ぶ）
		*/
		//-----------------------------------------------------------------//
		void unmount() noexcept
		{
			for(uint8_t i = 0; i < KEY_BUFF_NUM; ++i) {
				key_pad_[i] = 0;
			}
			shift_ = false;
			ctrl_ = false;
			num_lock_ = false;
			caps_lock_ = false;
			scroll_lock_ = false;
			probe_ = false;
			led_bits_ = 0;
			fifo_.clear();
		}


		void injection(const uint8_t* msg, uint16_t len) noexcept
		{
			if(len > KEY_BUFF_NUM) {
				len = KEY_BUFF_NUM;
			}

			if((msg[0] & (SP_CTRL_LEFT | SP_CTRL_RIGHT)) != 0) {
				ctrl_ = true;
			} else {
				ctrl_ = false;
			}
			if((msg[0] & (SP_SHIFT_LEFT | SP_SHIFT_RIGHT)) != 0) {
				shift_ = true;
			} else {
				shift_ = false;
			}

			for(uint8_t i = 2; i < len; ++i) {
				if(msg[i] != 0) {
					bool first = true;
					for(uint8_t j = 2; j < len; ++j) {
						if(key_pad_[j] == msg[i]) {
							first = false;
							break;
						}
					}
					if(first) {
						auto ch = convert_map_to_ascii_(msg[i]);
						if(ch != 0) {
							if(fifo_.length() >= (fifo_.size() - 1)) {
								fifo_.get();  // 先頭を捨てる
							}
							fifo_.put(key_t(ch, static_cast<MAP>(msg[i])));
						}
					}
				}
			}
			for(uint8_t i = 0; i < len; ++i) {
				key_pad_[i] = msg[i];
			}
			probe_ = true;
			// memcpy(key_pad_, msg, len);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  キーボードが接続されているか検査
			@return キーボードが接続されている場合「true」
		*/
		//-----------------------------------------------------------------//
		bool probe() const noexcept { return true; }


		//-----------------------------------------------------------------//
		/*!
			@brief  特殊キーの状態を取得 @n
					CTRL, SHIFT, ALT, GUI キーの状態
			@return 特殊キーの状態
		*/
		//-----------------------------------------------------------------//
		auto get_sp_key_state() const noexcept { return key_pad_[0]; }


		//-----------------------------------------------------------------//
		/*!
			@brief  LED の状態を取得
			@return LED の状態
		*/
		//-----------------------------------------------------------------//
		auto get_led_state() const noexcept { return led_bits_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  入力数を取得
			@return 入力数
		*/
		//-----------------------------------------------------------------//
		auto get_num() const noexcept { return fifo_.length(); }


		//-----------------------------------------------------------------//
		/*!
			@brief  入力キーを取得 @n
					文字が無い場合「０、MAP::NONE」が返る。
			@return 入力キー
		*/
		//-----------------------------------------------------------------//
		auto get_key() noexcept
		{
			if(fifo_.length() > 0) {
				return fifo_.get();
			} else {
				return key_t('\0', MAP::NONE);
			}
		}
	};
}
