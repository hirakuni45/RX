#pragma once
//=====================================================================//
/*!	@file
	@brief	UC1701 LCD ドライバー @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include "common/delay.hpp"

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  UC1701 テンプレートクラス
		@param[in]	CSI_IO	CSI(SPI) 制御クラス
		@param[in]	CS	デバイス選択、レジスター選択、制御クラス
		@param[in]	A0	制御切り替え、レジスター選択、制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CSI_IO, class CS, class A0>
	class UC1701 {

		CSI_IO&	csi_;

		inline void write_(uint8_t cmd) {
			csi_.xchg(cmd);
		}

		inline void chip_enable_(bool f = true) const {
			CS::P = !f;
		}

		inline void reg_select_(bool f) const {
			A0::P = f;
		}


		void init_() {
			reg_select_(0);
			chip_enable_();

			// Set the LCD parameters...
   			write_(0xE2);  // System Reset
			write_(0x40);  // Set display start line to 0 
			write_(0xA1);  // Set SEG Direction
			write_(0xC0);  // Set COM Direction
			write_(0xA2);  // Set Bias = 1/9
			write_(0x2C);  // Boost ON
			write_(0x2E);  // Voltage Regular On
			write_(0x2F);  // Voltage Follower On
			write_(0xF8);  // Set booster ratio to 
			write_(0x00);  // 4x
			write_(0x23);  // Set Resistor Ratio = 3
			write_(0x81);
			write_(0x28);  // Set Electronic Volume = 40
			write_(0xAC);  // Set Static indicator off
			write_(0x00);
//			write_(0xA6);  // Disable inverse

			write_(0xAF);  // Set Display Enable
			utils::delay::milli_second(100);
			write_(0xA5);  // display all points
			utils::delay::milli_second(200);
			write_(0xA4);  // normal display
		}

		void set_pointer_(uint8_t x, uint8_t y)
		{
			x += 4;

			uint8_t i = (x & 0xF0)>>4;
			uint8_t j = x & 0x0F;
			// digitalWrite(this->pin_cs1, LOW);
			write_(0xB0 + y);  // 0 to 7 
			write_(0x10 + i); 
			write_(j);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		UC1701(CSI_IO& csi) : csi_(csi) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	contrast コントラスト
			@param[in]	comrvs	コモンライン・リバースの場合：true
		*/
		//-----------------------------------------------------------------//
		void start(uint8_t contrast, bool comrvs = false)
		{
			CS::DIR = 1;  // (/CS) output
			A0::DIR = 1;  // (A0) output

			reg_select_(0);
			chip_enable_(false);

			utils::delay::milli_second(100);

			init_();

			chip_enable_(false);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コピー
			@param[in]	src	フレームバッファソース
			@param[in]	num	転送ページ数
			@param[in]	ofs	転送オフセット
		*/
		//-----------------------------------------------------------------//
		void copy(const uint8_t* src, uint8_t num, uint8_t ofs = 0) {
			chip_enable_();
			uint8_t ox = 0x00;
			for(uint8_t page = ofs; page < (ofs + num); ++page) {
				reg_select_(0);
				set_pointer_(ox, page);
				reg_select_(1);
				csi_.send(src, 128);
				src += 128;
			}
			reg_select_(0);
			chip_enable_(false);
		}

	};
}
