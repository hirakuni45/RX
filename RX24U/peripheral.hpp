#pragma once
//=====================================================================//
/*!	@file
	@brief	Peripheral Type / ペリフェラル種別 (RX24U)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	Peripheral Type / ペリフェラル型（種別）
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
		MTU6,	///< Multi-Function Timer Pulse Unit 6 / マルチファンクションタイマパルスユニット６
		MTU7,	///< Multi-Function Timer Pulse Unit 7 / マルチファンクションタイマパルスユニット７
		MTU9,	///< Multi-Function Timer Pulse Unit 9 / マルチファンクションタイマパルスユニット９

		POE3,	///< Port Output Enable 3 / ポートアウトプットイネーブル３

		GPT0,	///< General PWM Timer 0 / 汎用 PWM タイマ０
		GPT1,	///< General PWM Timer 1 / 汎用 PWM タイマ１
		GPT2,	///< General PWM Timer 2 / 汎用 PWM タイマ２
		GPT3,	///< General PWM Timer 3 / 汎用 PWM タイマ３

		TMR0,	///< 8-Bit Timer 0 / 8 ビットタイマ０
		TMR1,	///< 8-Bit Timer 1 / 8 ビットタイマ１
		TMR2,	///< 8-Bit Timer 2 / 8 ビットタイマ２
		TMR3,	///< 8-Bit Timer 3 / 8 ビットタイマ３
		TMR4,	///< 8-Bit Timer 4 / 8 ビットタイマ４
		TMR5,	///< 8-Bit Timer 5 / 8 ビットタイマ５
		TMR6,	///< 8-Bit Timer 6 / 8 ビットタイマ６
		TMR7,	///< 8-Bit Timer 7 / 8 ビットタイマ７

		CMT0,	///< Compare Match Timer 0 / コンペアマッチタイマー０
		CMT1,	///< Compare Match Timer 1 / コンペアマッチタイマー１
		CMT2,	///< Compare Match Timer 2 / コンペアマッチタイマー２
		CMT3,	///< Compare Match Timer 3 / コンペアマッチタイマー３

		IWDT,	///< Independent Watchdog Timer / 独立ウォッチドッグタイマ

		SCI1,	///< Serial Communications Interface 1 / シリアルコミュニケーションインタフェース０
		SCI5,	///< Serial Communications Interface 5 / シリアルコミュニケーションインタフェース５
		SCI6,	///< Serial Communications Interface 6 / シリアルコミュニケーションインタフェース６
		SCI8,	///< Serial Communications Interface 8 / シリアルコミュニケーションインタフェース８
		SCI9,	///< Serial Communications Interface 9 / シリアルコミュニケーションインタフェース９
		SCI11,	///< Serial Communications Interface 11 / シリアルコミュニケーションインタフェース１１

		RIIC0,	///< I2C-bus Interface 0 / I2C バスインタフェース０

		///（※Ｂバージョンのみ）
		RSCAN,	///< RSCAN Module / RSCAN モジュール

		RSPI0,	///< Serial Peripheral Interface 0 / シリアルペリフェラルインタフェース０

		CRC,	///< CRC Calculator / CRC 演算器

		S12AD,	///< 12-Bit A/D Converter / 12 ビット A/D コンバータ
		S12AD1,	///< 12-Bit A/D Converter 1 / 12 ビット A/D コンバータ１
		S12AD2,	///< 12-Bit A/D Converter 2 / 12 ビット A/D コンバータ２

		DA,		///< 8-Bit D/A Converter / 8 ビット D/A コンバータ

		CMPC0,	///< Comparator C0 / コンパレータＣ０
		CMPC1,	///< Comparator C1 / コンパレータＣ１
		CMPC2,	///< Comparator C2 / コンパレータＣ２
		CMPC3,	///< Comparator C3 / コンパレータＣ３

		DOC,	///< Data Operation Circuit / データ演算回路
	};
}
