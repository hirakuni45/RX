#pragma once
//=====================================================================//
/*!	@file
	@brief	Peripheral Type / ペリフェラル種別 (RX21A)
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
		@brief  ペリフェラル型（種別）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class peripheral : uint8_t {

		CAC,	///< Clock Frequency Accuracy Measurement Circuit / クロック周波数精度測定回路

		DMAC0,	///< DMA Controller channel 0 / DMA コントローラー０
		DMAC1,	///< DMA Controller channel 1 / DMA コントローラー１
		DMAC2,	///< DMA Controller channel 2 / DMA コントローラー２
		DMAC3,	///< DMA Controller channel 3 / DMA コントローラー３
		DTC,	///< Data Transfer Controller / データトランスファコントローラ

		ELC,	///< Event Link Controller / イベントリンクコントローラ

		MTU0,	///< Multi-Function Timer Pulse Unit 0 / マルチファンクションタイマパルスユニット０
		MTU1,	///< Multi-Function Timer Pulse Unit 1 / マルチファンクションタイマパルスユニット１
		MTU2,	///< Multi-Function Timer Pulse Unit 2 / マルチファンクションタイマパルスユニット２
		MTU3,	///< Multi-Function Timer Pulse Unit 3 / マルチファンクションタイマパルスユニット３
		MTU4,	///< Multi-Function Timer Pulse Unit 4 / マルチファンクションタイマパルスユニット４
		MTU5,	///< Multi-Function Timer Pulse Unit 5 / マルチファンクションタイマパルスユニット５

		POE2,	///< Port Output Enable 2 / ポートアウトプットイネーブル２

		TMR0,	///< 8-Bit Timer 0 / 8 ビットタイマ０
		TMR1,	///< 8-Bit Timer 1 / 8 ビットタイマ１
		TMR2,	///< 8-Bit Timer 2 / 8 ビットタイマ２
		TMR3,	///< 8-Bit Timer 3 / 8 ビットタイマ３

		CMT0,	///< Compare Match Timer 0 / コンペアマッチタイマー０
		CMT1,	///< Compare Match Timer 1 / コンペアマッチタイマー１
		CMT2,	///< Compare Match Timer 2 / コンペアマッチタイマー２
		CMT3,	///< Compare Match Timer 3 / コンペアマッチタイマー３

		RTC,	///< Realtime Clock / リアルタイムクロック

		IWDT,	///< Independent Watchdog Timer / 独立ウォッチドッグタイマ

		SCI1,	///< Serial Communications Interface 1 / シリアルコミュニケーションインタフェース１
		SCI5,	///< Serial Communications Interface 5 / シリアルコミュニケーションインタフェース５
		SCI6,	///< Serial Communications Interface 6 / シリアルコミュニケーションインタフェース６
		SCI8,	///< Serial Communications Interface 8 / シリアルコミュニケーションインタフェース８
		SCI9,	///< Serial Communications Interface 9 / シリアルコミュニケーションインタフェース９

		IrDA,	///< IrDA Interface / IrDA インタフェース

		RIIC0,	///< I2C-bus Interface 0 / I2C バスインタフェース０
		RIIC1,	///< I2C-bus Interface 1 / I2C バスインタフェース１

		RSPI0,	///< Serial Peripheral Interface 0 / シリアルペリフェラルインタフェース０
		RSPI1,	///< Serial Peripheral Interface 1 / シリアルペリフェラルインタフェース１

		CRC,	///< CRC Calculator / CRC 演算器

		DSAD,	///< 24-bits ∆ΣA/D Converter / 24 ビット ∆ΣA/D コンバータ

		AD,		///< 10-Bit A/D Converter / 10 ビット A/D コンバータ

		DA,		///< 10-Bits D/A Converter / 10 ビット D/A コンバータ

		TEMPS,	///< 温度センサ

		CMPA,	///< Comparator A / コンパレータＡ
		CMPB,	///< Comparator B / コンパレータＢ

		DOC,	///< Data Operation Circuit / データ演算回路
	};
}
