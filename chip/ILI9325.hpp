#pragma once
//=========================================================================//
/*!	@file
	@brief	ILI9325 class
			TFT Display Controller Driver
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstdint>
#include "common/delay.hpp"

#include "common/format.hpp"

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ILI9325 テンプレートクラス
		@param[in]	RW	Read/Write クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RW>
	class ILI9325 {

		RW&		rw_;

		static const uint16_t DELAY = 0xffff;

		void write_list_(const uint16_t* list, uint16_t size)
		{
			rw_.enable();
			for(uint16_t i = 0; i < size; ++i) {
				auto cmd = *list++;
				auto dat = *list++;
				if(cmd == DELAY) {
					utils::delay::milli_second(dat);
				} else {
					rw_.write(cmd, 0);
					rw_.write(dat, 1);
				}
			}
			rw_.enable(false);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	rw	RW 制御クラスを参照で渡す
		 */
		//-----------------------------------------------------------------//
		ILI9325(RW& rw) : rw_(rw) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始（初期化）
			@return デバイスを認識出来ない場合「false」
		 */
		//-----------------------------------------------------------------//
		bool start()
		{
//			rw_.write(0x00, 0);  // command register index
//			auto id = rw_.read();
//			utils::format("ID: %04X\n") % id;

//			switch(id) {
//				break;
//			default:
//				return false;
//			}

			static const uint16_t init_list_[] = {
				0x01, 0x0100,  //Driver output control VT (1)
				0x03, 0x1030,  //Entry mode

//				0x01, 0x0000,  //Driver output control HT (1)
//				0x03, 0x1028,  //Entry mode

				0x02, 0x0700, //LCD driving control
				0x04, 0x0000, //Resize control
				0x08, 0x0202, //Display control (2)
				0x09, 0x0000, //Display control (3)
				0x10, 0x0000,
				0x11, 0x0007, //power control 2 DC, VC
				0x12, 0x0000, //power control 3 VRH
				0x13, 0x0000, //power control 4 VCOM amplitude
				DELAY, 200,
				0x10, 0x16B0,             //power control 1 BT,AP
				0x11, 0x0227,             //power control 2 DC,VC
				DELAY, 50,
				0x12, 0x001c,             //power control 3 VRH
				DELAY, 50,
				0x13, 0x0A00,             //power control 4 vcom amplitude
				0x29, 0x000F,             //power control 7 VCOMH
				0x2b, 0x000d,             //Frame rate
				DELAY, 50,
				0x20, 0x0000,              //Horizontal GRAM Address Set
				0x21, 0x0000,              //Vertical GRAM Address Set
				0x50, 0x0000,              //Horizontal Address Start Position
				0x51, 0x00EF,              //Horizontal Address end Position (239)
				0x52, 0x0000,              //Vertical Address Start Position
				0x53, 0x013F,              //Vertical Address end Position (319)
				0x60, 0xa700,              //Driver Output Control 2
			//  0x61, 0x0001,              //Base Image Display Control
				0x61, 0x0003,              //Base Image Display Control
				0x6a, 0x0000,              //Base Image Display Control
				0x90, 0x0010,              //Panel Interface Control 1
				0x92, 0x0000,              //Panel Interface Control 2
				0x93, 0x0000,              //Panel Interface Control 3
				0x30, 0x0007,
				0x31, 0x0403,
				0x32, 0x0404,
				0x35, 0x0002,
				0x36, 0x0707,
				0x37, 0x0606,
				0x38, 0x0106,
				0x39, 0x0007,
				0x3c, 0x0700,
				0x3d, 0x0707,
				0x07, 0x0173,
			};
			write_list_(init_list_, sizeof(init_list_) / sizeof(uint16_t) / 2);

			utils::delay::milli_second(30);

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	点を描画
			@param[in] x	X 位置
			@param[in] y	Y 位置
			@param[in] c	カラー（RGB565）
		 */
		//-----------------------------------------------------------------//
		void plot(int16_t x, int16_t y, uint16_t c) noexcept
		{
			rw_.write(0x20, 0);  // Horizontal Address (8 bits)
			rw_.write(y, 1);
			rw_.write(0x21, 0);  // Vertical Address (9 bits)
			rw_.write(x, 1);

//			rw_.write(0x50, 0);
//			rw_.write(y, 1);
//			rw_.write(0x52, 0);
//			rw_.write(x, 1);

			rw_.write(0x22, 0);  // Frame Memory Data Write (18bits)
			rw_.write(c, 1);
		}
	};
}
