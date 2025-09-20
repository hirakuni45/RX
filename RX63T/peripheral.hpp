#pragma once
//=====================================================================//
/*!	@file
	@brief	Peripheral Type / ペリフェラル種別 (RX63T)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Peripheral Type / ペリフェラル型（種別）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class peripheral : uint8_t {

		CAC,	///< Clock Frequency Accuracy Measurement Circuit / クロック周波数精度測定回路

		DMAC0,	///< DMA Controller channel 0 / DMA コントローラ０
		DMAC1,	///< DMA Controller channel 1 / DMA コントローラ１
		DMAC2,	///< DMA Controller channel 2 / DMA コントローラ２
		DMAC3,	///< DMA Controller channel 3 / DMA コントローラ３
		DTC,	///< Data Transfer Controller / データトランスファコントローラ

		MTU0,	///< Multi-Function Timer Pulse Unit 0 / マルチファンクションタイマパルスユニット０
		MTU1,	///< Multi-Function Timer Pulse Unit 1 / マルチファンクションタイマパルスユニット１
		MTU2,	///< Multi-Function Timer Pulse Unit 2 / マルチファンクションタイマパルスユニット２
		MTU3,	///< Multi-Function Timer Pulse Unit 3 / マルチファンクションタイマパルスユニット３
		MTU4,	///< Multi-Function Timer Pulse Unit 4 / マルチファンクションタイマパルスユニット４
		MTU5,	///< Multi-Function Timer Pulse Unit 5 / マルチファンクションタイマパルスユニット５
		MTU6,	///< Multi-Function Timer Pulse Unit 6 / マルチファンクションタイマパルスユニット６
		MTU7,	///< Multi-Function Timer Pulse Unit 7 / マルチファンクションタイマパルスユニット７

		POE3,	///< Port Output Enable 3 / ポートアウトプットイネーブル

		GPT0,	///< General PWM Timer 0 / 汎用 PWM タイマ０
		GPT1,	///< General PWM Timer 1 / 汎用 PWM タイマ１
		GPT2,	///< General PWM Timer 2 / 汎用 PWM タイマ２
		GPT3,	///< General PWM Timer 3 / 汎用 PWM タイマ３
		GPT4,	///< General PWM Timer 4 / 汎用 PWM タイマ４
		GPT5,	///< General PWM Timer 5 / 汎用 PWM タイマ５
		GPT6,	///< General PWM Timer 6 / 汎用 PWM タイマ６
		GPT7,	///< General PWM Timer 7 / 汎用 PWM タイマ７

		CMT0,	///< Compare Match Timer 0 / コンペアマッチタイマー０
		CMT1,	///< Compare Match Timer 1 / コンペアマッチタイマー１
		CMT2,	///< Compare Match Timer 2 / コンペアマッチタイマー２
		CMT3,	///< Compare Match Timer 3 / コンペアマッチタイマー３

		WDTA,	///< Watchdog Timer / ウォッチドッグタイマ
		IWDT,	///< Independent Watchdog Timer / 独立ウォッチドッグタイマ

		USB0,	///< USB 2.0 Host/Function Module / USB 2.0 ホスト/ファンクションモジュール

		SCI0,	///< Serial Communications Interface 0 / シリアルコミュニケーションインタフェース０
		SCI1,	///< Serial Communications Interface 1 / シリアルコミュニケーションインタフェース１
		SCI2,	///< Serial Communications Interface 2 / シリアルコミュニケーションインタフェース２
		SCI3,	///< Serial Communications Interface 3 / シリアルコミュニケーションインタフェース３
		SCI12,	///< Serial Communications Interface 12 / シリアルコミュニケーションインタフェース１２

		RIIC0,	///< I2C-bus Interface 0 / I2C バスインタフェース０
		RIIC1,	///< I2C-bus Interface 1 / I2C バスインタフェース１

		CAN1,	///< CAN Module 1 / CAN モジュール１

		RSPI0,	///< Serial Peripheral Interface 0 / シリアルペリフェラルインタフェース０
		RSPI1,	///< Serial Peripheral Interface 1 / シリアルペリフェラルインタフェース１

		CRC,	///< CRC Calculator / CRC 演算器

		S12AD,	///< 12-Bit A/D Converter / 12 ビット A/D コンバータ（64/48 ピン版）
		S12AD0,	///< 12-Bit A/D Converter 0 / 12 ビット A/D コンバータ０（144/120/112/100 ピン版）
		S12AD1,	///< 12-Bit A/D Converter 1 / 12 ビット A/D コンバータ１（144/120/112/100 ピン版）

		AD,		///< 10-Bit A/D Converter / 10 ビット A/D コンバータ

		DA,		///< 10-Bit D/A Converter / 10 ビット　D/A コンバータ

		DOC,	///< Data Operation Circuit / データ演算回路

		DPC0,	///< Digital Power Supply Controller 0 / デジタル電源制御演算器０
		DPC1,	///< Digital Power Supply Controller 1 / デジタル電源制御演算器１
		DPC2,	///< Digital Power Supply Controller 2 / デジタル電源制御演算器２
		DPC3,	///< Digital Power Supply Controller 3 / デジタル電源制御演算器３
	};
}
