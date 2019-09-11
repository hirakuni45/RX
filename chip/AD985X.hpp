#pragma once
//=====================================================================//
/*!	@file
	@brief	AD985X class @n
			ANALOG DEVICES @n
			Interface: SPI, Vcc: 2.7V to 5V @n
			  Vcc: 2.7V ---> MAX 100MHz @n
			  Vcc: 3.3V ---> MAX 125MHz @n
			  Vcc: 5.0V ---> MAX 180MHz @n
			AD9850: Up to 125MHz @n
			AD9851: Up to 180MHz
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cmath>
#include "common/delay.hpp"

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  AD985X テンプレートクラス
		@param[in]	D7		ポート・クラス
		@param[in]	W_CLK	ポート・クラス
		@param[in]	FQ_UD	ポート・クラス（FQ_UpdDate)
		@param[in]	RESET	ポート・クラス
		@param[in]	BASEC	ベースクロック（AD9850:125, AD9851:180）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class D7, class W_CLK, class FQ_UD, class RESET, uint32_t BASEC>
	class AD985X {

		void write_byte_(uint8_t d) {
			for(uint8_t i = 0; i < 8; ++i) {
				D7::P = d & 1;
				d >>= 1;
				W_CLK::P = 1;
				utils::delay::micro_second(1);
				W_CLK::P = 0;
				utils::delay::micro_second(1);
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクタ
		 */
		//-----------------------------------------------------------------//
		AD985X() noexcept
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
		 */
		//-----------------------------------------------------------------//
		void start() noexcept
		{
			RESET::DIR = 1;
			RESET::P = 0;
			W_CLK::DIR = 1;
			W_CLK::P = 0;
			FQ_UD::DIR = 1;
			FQ_UD::P = 0;
			D7::DIR = 1;
			D7::P = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	リセット
		 */
		//-----------------------------------------------------------------//
		void reset() noexcept
		{
			W_CLK::P = 0;
			FQ_UD::P = 0;

			// RESET signal
			RESET::P = 0;
			utils::delay::micro_second(1);
			RESET::P = 1;
			utils::delay::micro_second(1);
			RESET::P = 0;
			// W_CLK signal
			W_CLK::P = 0;
			utils::delay::micro_second(1);
			W_CLK::P = 1;
			utils::delay::micro_second(1);
			W_CLK::P = 0;
			// FQ_UD signal
			FQ_UD::P = 0;
			utils::delay::micro_second(1);
			FQ_UD::P = 1;
			utils::delay::micro_second(1);
			FQ_UD::P = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	レジスタを設定
			@param[in]	w0		W0 レジスタ
			@param[in]	wx		周波数 レジスタ
		 */
		//-----------------------------------------------------------------//
		void set_reg(uint8_t w0, uint32_t wx) noexcept
		{
			write_byte_(wx);
			wx >>= 8;
			write_byte_(wx);
			wx >>= 8;
			write_byte_(wx);
			wx >>= 8;
			write_byte_(wx);
			write_byte_(w0);

			FQ_UD::P = 1;
			utils::delay::micro_second(1);
			FQ_UD::P = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	周波数を設定
			@param[in]	w0		W0 レジスター値
			@param[in]	freq	周波数
		 */
		//-----------------------------------------------------------------//
		void set_frq(uint8_t w0, float freq) noexcept
		{
			double x = 4294967295.0 / static_cast<double>(BASEC);
			double frequence = static_cast<double>(freq) / 1000000.0;
			uint32_t wx = static_cast<uint32_t>(frequence * x);
			set_reg(w0, wx);
		}
	};
}
