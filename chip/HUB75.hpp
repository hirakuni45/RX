#pragma once
//=====================================================================//
/*!	@file
	@brief	HUB75 RGB LED Panel Driver クラス @n
				R[01], G[01], B[01], SCLK, LATCH, BLANK(/OE), ADR[0-3] @n
				note: http://bikerglen.com/projects/lighting/led-panel-1up/#Required_Hardware @n
				 1: R1      2: G1    @n
				 3: B1      4: GND   @n
				 5: R2      6: G2    @n
				 7: B2      8: GND   @n
				 9: A      10: B     @n
				11: C      12: D     @n
				13: CLK    14: LAT   @n
				15: /OE    16: GND
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cmath>

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  HUB75 カラム選択ポート・クラス
		@param[in]	a	デコーダーＡ
		@param[in]	b	デコーダーＢ
		@param[in]	c	デコーダーＣ
		@param[in]	d	デコーダーＤ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <PORT a, PORT b, PORT c, PORT d>
	class PORTS {
	public:
		static void init() {
			a::DIR = 1;
			b::DIR = 1;
			c::DIR = 1;
			d::DIR = 1;
		}

		static void out(uint32_t v) {
			a::P = v & 1;
			b::P = (v >> 1) & 1;
			c::P = (v >> 2) & 1;
			d::P = (v >> 3) & 1;
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  HUB75 テンプレートクラス
		@param[in]	red		赤シリアル・ポート
		@param[in]	green	緑シリアル・ポート
		@param[in]	blue	青シリアル・ポート
		@param[in]	sclk	シリアル・クロック・ポート
		@param[in]	latch	ラッチ・ポート
		@param[in]	blank	ブランキング・ポート
		@param[in]	adr		カラム・デコーダー・ポート		
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <PORT red, PORT green, PORT blue, PORT sclk, PORT latch, PORT blank, PORTS adr>
	class HUB75 {
	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	開始
		 */
		//-----------------------------------------------------------------//
		void start()
		{
			red::DIR = 1;
			green::DIR = 1;
			blue::DIR = 1;
			sclk::DIR = 1;
			latch::DIR = 1;
			blank::DIR = 1;
			adr::init();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	コピー
			@param[in]	src		ソース
		 */
		//-----------------------------------------------------------------//
		void copy(const void* src)
		{
		}
	};
}
