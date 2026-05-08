#pragma once
//=====================================================================//
/*!	@file
	@brief	Peripheral Type / ペリフェラル種別 (RX14T)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2026 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  peripheral enum class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class peripheral : uint8_t {

		CAC,	///< Clock Frequency Accuracy Measurement Circuit / クロック周波数精度測定回路

		DTC,	///< Data Transfer Controller / データトランスファコントローラ

		MTU0,	///< Multi-Function Timer Pulse Unit 0 / マルチファンクションタイマパルスユニット０
		MTU1,	///< Multi-Function Timer Pulse Unit 1 / マルチファンクションタイマパルスユニット１
		MTU2,	///< Multi-Function Timer Pulse Unit 2 / マルチファンクションタイマパルスユニット２
		MTU3,	///< Multi-Function Timer Pulse Unit 3 / マルチファンクションタイマパルスユニット３
		MTU4,	///< Multi-Function Timer Pulse Unit 4 / マルチファンクションタイマパルスユニット４
		MTU5,	///< Multi-Function Timer Pulse Unit 5 / マルチファンクションタイマパルスユニット５

		POE3E,	///< Port Output Enable 3 / ポートアウトプットイネーブル３

		GPTW0,	///< General PWM Timer 0 / 汎用 PWM タイマ０
		GPTW1,	///< General PWM Timer 1 / 汎用 PWM タイマ１
		GPTW2,	///< General PWM Timer 2 / 汎用 PWM タイマ２

		POEG,	///< Port Output Enable GPTW / GPTW 用ポートアウトプットイネーブル

		TMR0,	///< 8-Bit Timer 0 / 8 ビットタイマ０
		TMR1,	///< 8-Bit Timer 1 / 8 ビットタイマ１
		TMR2,	///< 8-Bit Timer 2 / 8 ビットタイマ２
		TMR3,	///< 8-Bit Timer 3 / 8 ビットタイマ３

		CMT0,	///< Compare Match Timer 0 / コンペアマッチタイマー０
		CMT1,	///< Compare Match Timer 1 / コンペアマッチタイマー１

		IWDT,	///< Independent Watchdog Timer / 独立ウォッチドッグタイマ

		SCI1,	///< Serial Communications Interface 1 / シリアルコミュニケーションインタフェース１
		SCI5,	///< Serial Communications Interface 5 / シリアルコミュニケーションインタフェース５
		SCI6,	///< Serial Communications Interface 6 / シリアルコミュニケーションインタフェース６
		SCI12,	///< Serial Communications Interface 12 / シリアルコミュニケーションインタフェース１２

		RIIC0,	///< I2C-bus Interface 0 / I2C バスインタフェース０

		CRC,	///< CRC Calculator / CRC 演算器

		S12AD,	///< 12-Bit A/D Converter / 12 ビット A/D コンバータ
		S12AD1,	///< 12-Bit A/D Converter 1 / 12 ビット A/D コンバータ１

		DA,		///< 8-Bit D/A Converter / 8 ビット D/A コンバータ

		TEMPS,	///<　Temperature Sensor / 温度センサ

		CMPC0,	///< Comparator C0 / コンパレータＣ０
		CMPC1,	///< Comparator C1 / コンパレータＣ１
		CMPC2,	///< Comparator C2 / コンパレータＣ２

		DOC,	///< Data Operation Circuit / データ演算回路
	};
}
