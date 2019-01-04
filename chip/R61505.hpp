#pragma once
//=========================================================================//
/*!	@file
	@brief	R61505V, R61505W class @n
			Renesas SP @n
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
		@brief  R61505V/W テンプレートクラス
		@param[in]	RW	Read/Write クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RW>
	class R61505 {

		RW&		rw_;

		static const uint16_t DELAY = 0xffff;

		void write_list_(const uint16_t* list, uint16_t size)
		{
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
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	rw	RW 制御クラスを参照で渡す
		 */
		//-----------------------------------------------------------------//
		R61505(RW& rw) : rw_(rw) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始（初期化）
			@return デバイスを認識出来ない場合「false」
		 */
		//-----------------------------------------------------------------//
		bool start()
		{
			rw_.write(0x00, 0);  // command register index
			auto id = rw_.read();
			utils::format("ID: %04X\n") % id;

			switch(id) {
			case 0xB505:  // R61505V
			case 0xC505:  // R61505W
				break;
			default:
				return false;
			}


			static const uint16_t R61505_init_list_[] = {
				//R61505W (TFT1N3204-E)
				0x0000, 0x0001,
				0x0007, 0x0000,
				0x0010, 0x0410,
				0x0011, 0x0237,
				0x0012, 0x0199,
				0x0013, 0x1100,
				DELAY,  150,
				0x0012, 0x01b9,
				0x0002, 0x0200,
// #if LCD_ALIGNMENT == VERTICAL
//				0x0001, 0x0100,
//				0x0003, 0x1030,
// #elif LCD_ALIGNMENT == HORIZONTAL
				0x0001, 0x0000,
				0x0003, 0x1028,
//#endif
				0x0008, 0x0808,
				0x0009, 0x0001,
				0x000A, 0x0000,
				0x000C, 0x0000,    // interface?
				0x000D, 0x0000,
				0x000E, 0x0030,
				0x0030, 0x0214,
				0x0031, 0x3715,
				0x0032, 0x0604,
				0x0033, 0x0e16,
				0x0034, 0x2211,
				0x0035, 0x1500,
				0x0036, 0x8507,
				0x0037, 0x1407,
				0x0038, 0x1403,
				0x0039, 0x0020,
				0x0050, 0x0000,
				0x0051, 0x00ef,
				0x0052, 0x0000,
				0x0053, 0x013f,
				0x0060, 0x2700,
				0x0061, 0x0003,
				0x006a, 0x0000,
				0x0090, 0x0015,
				0x0092, 0x0100,
				0x0093, 0x0701,
				0x0020, 0x0000,
				0x0021, 0x0000,
				DELAY,  80,
				0x0007, 0x0100,
			};
#if 0
			static const uint16_t R61505_init_list_[] = {
				0x0000, 0x0000,
				0x0000, 0x0000,
				0x0000, 0x0000,
				0x0000, 0x0001,
				0x00A4, 0x0001,     //CALB=1
				DELAY,  10,
				0x0060, 0x2700,     //NL
				0x0008, 0x0808,     //FP & BP
				0x0030, 0x0214,     //Gamma settings
				0x0031, 0x3715,
				0x0032, 0x0604,
				0x0033, 0x0E16,
				0x0034, 0x2211,
				0x0035, 0x1500,
				0x0036, 0x8507,
				0x0037, 0x1407,
				0x0038, 0x1403,
				0x0039, 0x0020,
				0x0090, 0x0015,     //DIVI & RTNI
				0x0010, 0x0410,     //BT=4,AP=1
				0x0011, 0x0237,     //DC1=2,DC0=3, VC=7
				0x0029, 0x0046,     //VCM1=70
				0x002A, 0x0046,     //VCMSEL=0,VCM2=70
				// Sleep mode IN sequence
				0x0007, 0x0000,
				//0x0012, 0x0000,   //PSON=0,PON=0
				// Sleep mode EXIT sequence 
				0x0012, 0x0189,     //VCMR=1,PSON=0,PON=0,VRH=9
				0x0013, 0x1100,     //VDV=17
				DELAY,  150,
				0x0012, 0x01B9,     //VCMR=1,PSON=1,PON=1,VRH=9 [018F]
				0x0001, 0x0100,     //SS=1 Other mode settings
				0x0002, 0x0200,     //BC0=1--Line inversion
				0x0003, 0x1030,
				0x0009, 0x0001,     //ISC=1 [0000]
				0x000A, 0x0000,     // [0000]
				//            0x000C, 0x0001,   //RIM=1 [0000]
				0x000D, 0x0000,     // [0000]
				0x000E, 0x0030,     //VEM=3 VCOM equalize [0000]
				0x0061, 0x0001,
				0x006A, 0x0000,
				0x0080, 0x0000,
				0x0081, 0x0000,
				0x0082, 0x005F,
				0x0092, 0x0100,
				0x0093, 0x0701,
				DELAY,  80,
				0x0007, 0x0100,     //BASEE=1--Display O
	        };
//				0x000C, 0x0001,     // 16bits interface
#endif
			write_list_(R61505_init_list_, sizeof(R61505_init_list_) / sizeof(uint16_t) / 2);

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

			rw_.write(0x22, 0);  // Frame Memory Data Write (16bits)
			rw_.write(c, 1);
		}
	};
}
