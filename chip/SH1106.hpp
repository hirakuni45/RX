#pragma once
//=====================================================================//
/*!	@file
	@brief	SH1106 LCD ドライバー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SH1106 テンプレートクラス
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
			csi_.xchg(0xAE);    // display off
			csi_.xchg(0x02);    // set lower column address
			csi_.xchg(0x10);    // set higher column address
			csi_.xchg(0x40);    // set display start line
			csi_.xchg(0xB0);    // set page address
			csi_.xchg(0x81);    // contract control
			csi_.xchg(contrast);  // 128
			csi_.xchg(0xA1);    // set segment remap
			csi_.xchg(invertSetting);    // normal / reverse
			csi_.xchg(0xA8);    // multiplex ratio
			csi_.xchg(0x3F);    // duty = 1/32
			csi_.xchg(0xAD);    // set charge pump enable
			csi_.xchg(0x8B);    // external VCC
			csi_.xchg(0x30 | Vpp);    // 0X30---0X33  set VPP 9V liangdu!!!!
			csi_.xchg(0xC8);    // Com scan direction
			csi_.xchg(0xD3);    // set display offset
			csi_.xchg(0x00);	//   0x20
			csi_.xchg(0xD5);    // set osc division
			csi_.xchg(0x80);
			csi_.xchg(0xD9);    // set pre-charge period
			csi_.xchg(0x1F);    // 0x22
			csi_.xchg(0xDA);    // set COM pins
			csi_.xchg(0x12);
			csi_.xchg(0xDB);    // set vcomh
			csi_.xchg(0x40);
			csi_.xchg(0xAF);    // display ON

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
			@brief  コピー
			@param[in]	p	フレームバッファソース
			@param[in]	num	転送ページ数
			@param[in]	ofs	転送オフセット
		*/
		//-----------------------------------------------------------------//
		void copy(const uint8_t* src, uint8_t num, uint8_t ofs = 0) {
			chip_enable_();
			uint8_t x = 0;
			for(uint8_t page = ofs; page < (ofs + num); ++page) {
				reg_select_(0);
				csi_.xchg(0xB0 + j);          // set page address 0 to 7
				csi_.xchg(0x00 | (x & 0xF));  // lower collum start address
				csi_.xchg(0x10 | (x >> 4));   // higher collum start address
				reg_select_(1);
				csi_.send(src, 128);
				src += 128;
			}
			reg_select_(1);
			chip_enable_(false);
		}

	};
}
