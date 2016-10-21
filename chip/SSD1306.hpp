#pragma once
//=====================================================================//
/*!	@file
	@brief	SSD1306 LCD ドライバー
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include "G13/port.hpp"
#include "common/csi_io.hpp"

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SSD1306 テンプレートクラス
		@param[in]	CSI_IO	CSI(SPI) 制御クラス
		@param[in]	CS	デバイス選択、レジスター選択、制御クラス
		@param[in]	A0	制御切り替え、レジスター選択、制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CSI_IO, class CS, class A0>
	class SSD1306 {

		CSI_IO&	csi_;

		inline void chip_enable_(bool f = true) const {
			CS::P = !f;
		}

		inline void reg_select_(bool f) const {
			A0::P = f;
		}

		void init_(uint8_t contrast, bool comrvs)
		{
			chip_enable_(false);
			utils::delay::milli_second(250);

			reg_select_(0);
			chip_enable_();
			csi_.xchg(0xAE);	// Set Display Off
			csi_.xchg(0xD5);	// display divide ratio/osc. freq. mode
			csi_.xchg(0x80);
			csi_.xchg(0xA8);	// multiplex ration mode:63
			csi_.xchg(0x3F);
			csi_.xchg(0xD3);	// Set Display Offset
			csi_.xchg(0x00);
			csi_.xchg(0x40);	// Set Display Start Line
			csi_.xchg(0x8D);	// Set Display Offset
			// csi_.xchg(0x10);
			csi_.xchg(0x14);
			csi_.xchg(0xA1);	// Segment Remap

			// Sst COM Output Scan Direction
			if(comrvs) {
				csi_.xchg(0xC8);
			} else {
				csi_.xchg(0xC0);
			}
			csi_.xchg(0xDA);	// common pads hardware: alternative
			csi_.xchg(0x12);
			csi_.xchg(0x81);	// contrast control 
//			csi_.xchg(0x9F);
			csi_.xchg(0x66);
			csi_.xchg(0xD9);	// set pre-charge period
//			csi_.xchg(0x22);	// set period 1:1;period 2:15
			csi_.xchg(0xF1);
			csi_.xchg(0xDB);	// VCOM deselect level mode
			csi_.xchg(0x40);	// set Vvcomh=0.83*Vcc
			csi_.xchg(0xA4);	// Set Entire Display On/Off
			csi_.xchg(0xA6);	// Set Normal Display
			csi_.xchg(0xAF);	// Set Display On
			reg_select_(1);
			chip_enable_(false);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		SSD1306(CSI_IO& csi) : csi_(csi) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  ブライトネス設定
			@param[in]	val	ブライトネス値
		*/
		//-----------------------------------------------------------------//
		void set_brightness(uint8_t val)
		{
//    		write_(CMD::SET_VOLUME_FIRST);
//    		write_(CMD::SET_VOLUME_SECOND, (val & 0x3f));
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	contrast コントラスト
			@param[in]	comrvs	コモン・リバースの場合「true」
		*/
		//-----------------------------------------------------------------//
		void start(uint8_t contrast, bool comrvs)
		{
			CS::PMC = 0;  // (/CS) output
			CS::PM = 0;

			A0::PMC = 0;  // (A0) output
			A0::PM = 0;

			reg_select_(0);
			chip_enable_(false);

			utils::delay::milli_second(100);

			init_(contrast, comrvs);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  初期化
			@param[in]	comrvs	コモン・リバースの場合「true」
		*/
		//-----------------------------------------------------------------//


		//-----------------------------------------------------------------//
		/*!
			@brief  コピー
			@param[in]	p	フレームバッファソース
		*/
		//-----------------------------------------------------------------//
		void copy(const uint8_t* p) {
			chip_enable_();
			reg_select_(0);
			utils::delay::micro_second(1);
			for(uint8_t j = 0; j < 8; ++j) {
				csi_.xchg(0xb0 + j);	// set page address 0 to 7
				csi_.xchg(0x00);		// lower collum start address
				csi_.xchg(0x10);		// higher collum start address
				utils::delay::micro_second(1);
				reg_select_(1);
				utils::delay::micro_second(1);
				for(uint8_t i = 0; i < 128; ++i) {
					csi_.xchg(*p++);
				}
				utils::delay::micro_second(1);
				reg_select_(0);
			}
			reg_select_(1);
			chip_enable_(false);
		}

	};
}
